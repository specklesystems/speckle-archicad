
// *****************************************************************************
//
// Declaration and implementation of SemaphoreImpl class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_SEMAPHOREIMPL_HPP
#define GS_SEMAPHOREIMPL_HPP

#pragma once


// --- Includes ---------------------------------------------------------------

#include "FastLock.hpp"
#include "FastLockGuard.hpp"
#include "InterruptedException.hpp"
#include "System.hpp"
#include "ThreadImplList.hpp"
#include "ThreadMonitorGuard.hpp"



// --- SemaphoreImpl class -----------------------------------------------------

namespace GS {

template<typename List>
class SemaphoreImpl {

// Data members:
private:
	List					m_waiters;			// The threads waiting for this semaphore
	mutable FastLock		m_lock;				// Lock for serializing access to internal state
	volatile UInt32			m_count;			// The current count of this semaphore
	UInt32					m_maximumCount;		// The maximum count of this semaphore
	volatile UInt32			m_waiterCount;		// The number of threads waiting for this semaphore

// Construction / destruction:
public:
	 SemaphoreImpl (UInt32 initialCount, UInt32 maximumCount);
private:
	 SemaphoreImpl (const SemaphoreImpl&); // Disabled
public:
	~SemaphoreImpl ();

// Operator overloading:
private:
	const SemaphoreImpl&	operator = (const SemaphoreImpl&); // Disabled

// Operations:
public:
	UInt32					GetCount () const;

	void					Acquire (bool interruptible = true);
	bool					TryAcquire (UInt32 timeout, bool interruptible = true, UInt32* remaining = nullptr);
	void					Release ();

};

////////////////////////////////////////////////////////////////////////////////
// SemaphoreImpl implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename List>
inline SemaphoreImpl<List>::SemaphoreImpl (UInt32 initialCount, UInt32 maximumCount) :
	m_waiters (),
	m_lock (),
	m_count (initialCount),
	m_maximumCount (maximumCount),
	m_waiterCount (0)
{
	DBASSERT (maximumCount > 0);
	DBASSERT (maximumCount >= initialCount);
}

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------

template<typename List>
inline SemaphoreImpl<List>::~SemaphoreImpl ()
{
	if (DBERROR (m_waiters.GetSize () > 0)) {
		DBPRINTF ("Destroying semaphore while in use.");
	}
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetCount
// -----------------------------------------------------------------------------

template<typename List>
inline UInt32	SemaphoreImpl<List>::GetCount () const
{
	fast_lock (m_lock) { // Serialize access to the internal state...
		return m_count;
	}
}

// -----------------------------------------------------------------------------
// Acquire
// -----------------------------------------------------------------------------

template<typename List>
inline void		SemaphoreImpl<List>::Acquire (bool interruptible)
{
	// Decrement the count and block the current (caller) thread if the updated
	// count becomes 0.

	fast_lock (m_lock) { // Serialize access to the internal state...
		if (m_count > 0 && m_waiterCount == 0) { // No wait required return immediately...
			m_count --;
		} else {
			// Add the current thread to the list of waiting threads and wait for
			// a signal from a thread releasing the semaphore.

			ThreadImpl*	current = ThreadImpl::GetCurrent ();

			m_waiters.Add (current);
			m_waiterCount ++;

			ThreadMonitorState state;

			ThreadMonitor& monitor = current->GetMonitor ();
			takeownership (monitor) { // Take the ownership of the thread monitor...
				fast_unlock (m_lock) { // Release the internal lock while blocking...
					state = monitor.Wait (interruptible);
				}
			}

			// Remove the current thread from the list of waiting threads regardless
			// of the returned wait status.

			m_waiterCount --;
			m_waiters.Remove (current);

			switch (state) {
				case ThreadMonitorState::Signaled: { // The thread is waken up by a signal, so decrement the count...
					m_count --;
					break;
				}

				case ThreadMonitorState::Interrupted: { // The thread is interrupted while waiting for the lock...
					DBASSERT (interruptible);
					throw InterruptedException (
						"Thread interruptible while acquiring semaphore.",
						__FILE__,
						__LINE__);
				}

				default: { // Invalid state...
					throw SynchronizationException (
						"Internal error occurred while acquiring semaphore.",
						__FILE__,
						__LINE__);
				}

			}
		}
	}
}

// -----------------------------------------------------------------------------
// TryAcquire
// -----------------------------------------------------------------------------

template<typename List>
inline bool		SemaphoreImpl<List>::TryAcquire (UInt32 timeout, bool interruptible, UInt32* remaining)
{
	// Decrement the count and block the current (caller) thread if the updated
	// count becomes 0.

	UInt64 start = 0;
	if (remaining != nullptr) {
		start = System::GetCurrentTimeMillis ();
	}

	bool acquired = false;

	fast_lock (m_lock) { // Serialize access to the internal state...
		if (m_count > 0 && m_waiterCount == 0) { // No wait required return immediately...
			acquired = true;
			m_count --;
		} else if (timeout > 0) {
			// Add the current thread to the list of waiting threads and wait for
			// a signal from a thread releasing the semaphore.

			ThreadImpl* current = ThreadImpl::GetCurrent ();

			m_waiters.Add (current);
			m_waiterCount ++;

			ThreadMonitorState state;

			ThreadMonitor& monitor = current->GetMonitor ();
			takeownership (monitor) { // Take the ownership of the thread monitor...
				fast_unlock (m_lock) { // Release the internal lock while blocking...
					state = monitor.Wait (timeout, interruptible);
				}
			}

			// Remove the current thread from the list of waiting threads regardless
			// of the returned wait status.

			m_waiterCount --;
			m_waiters.Remove (current);

			switch (state) {
				case ThreadMonitorState::Signaled: { // The thread is waken up by a signal, so decrement the count...
					acquired = true;
					m_count --;
					break;
				}

				case ThreadMonitorState::Interrupted: { // The thread is interrupted while waiting for the lock...
					DBASSERT (interruptible);
					throw InterruptedException (
						"Thread interrupted while acquiring semaphore.",
						__FILE__,
						__LINE__);
				}

				case ThreadMonitorState::Timedout: { // Wait timed out...
					acquired = false;
					break;
				}

				default: { // Invalid state...
					throw SynchronizationException (
						"Internal error occurred while acquiring semaphore.",
						__FILE__,
						__LINE__);
				}

			}
		} else {
			acquired = false;
		}
	}

	if (remaining != nullptr) {
		*remaining = timeout - Min<UInt32> (timeout, UInt32 (System::GetCurrentTimeMillis () - start));
	}

	return acquired;
}

// -----------------------------------------------------------------------------
// Release
// -----------------------------------------------------------------------------

template<typename List>
inline void		SemaphoreImpl<List>::Release ()
{
	// Increment the count and signal a waiter thread if there are any. Because
	// the semaphore is bounded an exception will be raised if the maximum count
	// is about to be exceeded.

	fast_lock (m_lock) { // Serialize access to the internal state...
		if (DBERROR (m_count == m_maximumCount)) {
			throw SynchronizationException (
				"Failed to release semaphore: the maximum count of the semaphore exceeded.",
				__FILE__,
				__LINE__);
		}

		// Increment the count.

		m_count ++;

		// Enumerate the list of the waiting threads and attempt to signal a waiter.

		if (m_waiters.GetSize () > 0) {
			for (;;) {
				for (typename List::Iterator i = m_waiters.Enumerate (); i != nullptr; ) {
					// Try to take ownership of the thread monitor of the waiting thread,
					// if it cant be acquired then skip to the next waiter.

					ThreadMonitor& monitor = (*i)->GetMonitor ();
					if (monitor.TryAcquire ()) {
						// Try to wake up the waiting thread. Note: notify can because
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

				fast_unlock (m_lock) {
					ThreadImpl::Yield ();
				}
			}
		}
	}
}

}

#endif // GS_SEMAPHOREIMPL_HPP
