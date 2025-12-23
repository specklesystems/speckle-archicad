
// *****************************************************************************
//
// Declaration and implementation of ConditionImpl class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_CONDITIONIMPL_HPP
#define GS_CONDITIONIMPL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "FastLock.hpp"
#include "FastLockGuard.hpp"
#include "InterruptedException.hpp"
#include "Lockable.hpp"
#include "System.hpp"
#include "ThreadImplList.hpp"
#include "ThreadMonitorGuard.hpp"



// --- ConditionImpl class -----------------------------------------------------

namespace GS {

template<typename List>
class ConditionImpl {

// Data members:
private:
	Lockable&				m_extLock;		// External lock passed at construction time
	FastLock				m_intLock;		// Internal lock for serializing access to internal state
	List					m_waiters;		// The threads waiting for this condition

// Construction / destruction:
public:
	explicit ConditionImpl (Lockable& lock);
private:
			 ConditionImpl (const ConditionImpl&); // Disabled
public:
			~ConditionImpl ();

// Operator overloading:
private:
	const ConditionImpl&	operator = (const ConditionImpl&); // Disabled

// Operations:
public:
	bool					Wait (UInt32 timeout, bool interruptible = true, UInt32* remaining = nullptr);
	void					Wait (bool interruptible = true);

	void					Notify ();
	void					NotifyAll ();

};

////////////////////////////////////////////////////////////////////////////////
// ConditionImpl implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename List>
inline ConditionImpl<List>::ConditionImpl (Lockable& lock) :
	m_extLock (lock),
	m_intLock (),
	m_waiters ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------

template<typename List>
inline ConditionImpl<List>::~ConditionImpl ()
{
	if (DBERROR (m_waiters.GetSize () > 0)) {
		DBPRINTF ("Destroying a condition while in use.\n");
	}
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Wait
// -----------------------------------------------------------------------------

template<typename List>
inline bool		ConditionImpl<List>::Wait (UInt32 timeout, bool interruptible, UInt32* remaining)
{
	ThreadImpl*	current = ThreadImpl::GetCurrent ();

	UInt64 start = 0;
	if (remaining != nullptr) {
		start = System::GetCurrentTimeMillis ();
	}

	ThreadMonitor& monitor = current->GetMonitor ();

	ThreadMonitorState state;
	fast_lock (m_intLock) { // Serialize access to the internal state...
		// Release the external lock.

		m_extLock.Release ();

		// Add the current thread to the list of the waiting threads.

		m_waiters.Add (current);

		// Wait for the thread monitor of the current thread.

		takeownership (monitor) {
			fast_unlock (m_intLock) {
				state = monitor.Wait (timeout, interruptible);
			}
		}

		// Remove the current thread from the list of the waiting threads.

		m_waiters.Remove (current);
	}

	// Reacquire the external lock. Note: interruption is deferred until
	// external lock is acquired.

	m_extLock.Acquire (false);

	bool succeeded = false;
	switch (state) {
		case ThreadMonitorState::Signaled: {
			succeeded = true;
			break;
		}

		case ThreadMonitorState::Interrupted:
			DBASSERT (interruptible);
			throw InterruptedException (
				"Thread interrupted while waiting for condition.",
				__FILE__,
				__LINE__);

		case ThreadMonitorState::Timedout: {
			succeeded = false;
			break;
		}

		default:
			throw SynchronizationException (
				"Internal error occurred while waiting for condition.",
				__FILE__,
				__LINE__);

	}

	if (remaining != nullptr) {
		*remaining = timeout - Min<UInt32> (timeout, UInt32 (System::GetCurrentTimeMillis () - start));
	}

	return succeeded;
}

// -----------------------------------------------------------------------------
// Wait
// -----------------------------------------------------------------------------

template<typename List>
inline void		ConditionImpl<List>::Wait (bool interruptible)
{
	ThreadImpl*	current = ThreadImpl::GetCurrent ();

	ThreadMonitor& monitor = current->GetMonitor ();

	ThreadMonitorState state;
	fast_lock (m_intLock) { // Serialize access to the internal state...
		// Release the external lock.

		m_extLock.Release ();

		// Add the current thread to the list of the waiting threads.

		m_waiters.Add (current);

		// Wait for the thread monitor of the current thread.

		takeownership (monitor) {
			fast_unlock (m_intLock) {
				state = monitor.Wait (interruptible);
			}
		}

		// Remove the current thread from the list of the waiting threads.

		m_waiters.Remove (current);
	}

	// Reacquire the external lock. Note: interruption is deferred until external
	// lock is acquired.

	m_extLock.Acquire (false);

	switch (state) {
		case ThreadMonitorState::Signaled:
			break;

		case ThreadMonitorState::Interrupted:
			DBASSERT (interruptible);
			throw InterruptedException (
				"Thread interrupted while waiting for condition.",
				__FILE__,
				__LINE__);

		default:
			throw SynchronizationException (
				"Internal error occurred while waiting for condition.",
				__FILE__,
				__LINE__);

	}
}

// -----------------------------------------------------------------------------
// Notify
// -----------------------------------------------------------------------------

template<typename List>
inline void		ConditionImpl<List>::Notify ()
{
	fast_lock (m_intLock) { // Serialize access to the internal state...
		// Enumerate the list of the waiter threads and attempt to signal a waiter.

		if (m_waiters.GetSize () > 0) {
			for (;;) {
				for (typename List::Iterator i = m_waiters.Enumerate (); i != nullptr; ) {
					// Try to take ownership of the thread monitor of the waiter thread,
					// if it cant be acquired then skip to the next waiter.

					ThreadMonitor& monitor = (*i)->GetMonitor ();
					if (monitor.TryAcquire ()) {
						// Remove the waiter thread from the list of waiting threads
						// regardless  of the notify status so time isn't wasted checking
						// it again.

						m_waiters.Remove (*i);

						// Try to wake up the waiter thread. Note: notify can because
						// the wait operation has already been ended (thread killed,
						// interrupted or already notified).

						bool woke = monitor.Notify ();
						monitor.Release ();
						if (woke) {
							return;
						}
					} else {
						++ i;
					}
				}

				if (m_waiters.GetSize () == 0) {
					return;
				}

				// Back-off & retry.

				fast_unlock (m_intLock) {
					ThreadImpl::Yield ();
				}
			}
		}
	}
}

// -----------------------------------------------------------------------------
// NotifyAll
// -----------------------------------------------------------------------------

template<typename List>
inline void		ConditionImpl<List>::NotifyAll ()
{
	fast_lock (m_intLock) { // Serialize access to the internal state...
		// Enumerate the list of the waiter threads and attempt to signal all waiter.

		if (m_waiters.GetSize () > 0) {
			for (;;) {
				for (typename List::Iterator i = m_waiters.Enumerate (); i != nullptr; ) {
					// Try to take ownership of the thread monitor of the waiter thread,
					// if it cant be acquired then skip to the next waiter.

					ThreadMonitor& monitor = (*i)->GetMonitor ();
					if (monitor.TryAcquire ()) {
						// Remove the waiter thread from the list of waiting threads
						// regardless of the notify status so time isn't wasted checking
						// it again.

						m_waiters.Remove (*i);

						// Try to wake up the waiter thread. Note: notify can because
						// the wait operation has already been ended (thread killed,
						// interrupted or already notified).

						monitor.Notify ();
						monitor.Release ();
					} else {
						++ i;
					}
				}

				if (m_waiters.GetSize () == 0) {
					return;
				}

				// Back-off & retry.

				fast_unlock (m_intLock) {
					ThreadImpl::Yield ();
				}
			}
		}
	}
}

}

#endif // GS_CONDITIONIMPL_HPP
