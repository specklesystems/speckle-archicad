
// *****************************************************************************
//
// Declaration and implementation of ReentrantLockImpl class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_REENTRANTLOCKIMPL_HPP
#define GS_REENTRANTLOCKIMPL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "DeadlockException.hpp"
#include "FastLock.hpp"
#include "FastLockGuard.hpp"
#include "InterruptedException.hpp"
#include "System.hpp"
#include "ThreadImplList.hpp"
#include "ThreadMonitorGuard.hpp"



// --- ReentrantLockImpl class -------------------------------------------------

namespace GS {

template<typename List>
class ReentrantLockImpl {

// Data members:
private:
	volatile IntPtr				m_owner;		// The current owner thread of this reentrant lock
	volatile UInt32				m_counter;		// Counter to count recursive locking of this reentrant lock
	volatile UInt32				m_acquired;		// Counter to count non-recursive acquisitions of this reentrant lock
	List						m_waiters;		// The threads waiting for this reentrant lock
	FastLock					m_lock;			// Lock for serializing the access to the internal state of this reentrant lock

// Construction / destruction:
public:
	 ReentrantLockImpl ();
private:
	 ReentrantLockImpl (const ReentrantLockImpl&); // Disabled
public:
	~ReentrantLockImpl ();

// Operator overloading:
private:
	const ReentrantLockImpl&	operator = (const ReentrantLockImpl&); // Disabled

// Operations:
public:
	void						Acquire (bool interruptible = true);
	bool						TryAcquire (UInt32 timeout = 0, bool interruptible = true, UInt32* remaining = nullptr);
	void						Release ();

};

////////////////////////////////////////////////////////////////////////////////
// ReentrantLockImpl implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

template<typename List>
inline ReentrantLockImpl<List>::ReentrantLockImpl () :
	m_owner (0),
	m_counter (0),
	m_acquired (0),
	m_waiters (),
	m_lock ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------

template<typename List>
inline ReentrantLockImpl<List>::~ReentrantLockImpl ()
{
	if (DBERROR (m_waiters.GetSize () > 0)) {
		DBPRINTF ("Destroying a lock while in use.\n");
	}
	if (DBERROR (m_owner != 0)) {
		DBPRINTF ("Destroying an acquired lock.\n");
	}
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Acquire
// -----------------------------------------------------------------------------

template<typename List>
inline void		ReentrantLockImpl<List>::Acquire (bool interruptible)
{
	IntPtr currentThreadId = ThreadImpl::GetCurrentThreadId ();

	fast_lock (m_lock) { // Serialize access to the internal state...
		if (m_owner == currentThreadId) {
			//  If the current thread is the owner then increment counter and
			// continue immediately.

			m_counter ++;
		} else if (m_owner == 0 && m_waiters.GetSize () == 0) {
			// If the lock is free and there are no waiting threads then acquire
			// the lock immediately

			DBASSERT (m_counter == 0);

			m_owner = currentThreadId;
			m_acquired ++;
			m_counter ++;
		} else {
			// If the lock is not free then wait for a signal from a thread
			// releasing its ownership of the lock.

			ThreadImpl* currentThread = ThreadImpl::GetCurrent ();

			m_waiters.Add (currentThread);

			ThreadMonitorState state;

			try {
				ThreadMonitor& monitor = currentThread->GetMonitor ();
				takeownership (monitor) { // The the ownership of the thread monitor...
					fast_unlock (m_lock) { // Release the internal lock while blocking...
						state = monitor.Wait (interruptible);
					}
				}

			}
			catch (Exception&) {
				m_waiters.Remove (currentThread);
				throw;
			}

			// Remove the current thread from the list of waiting threads regardless
			// of the returned wait status.

			m_waiters.Remove (currentThread);

			switch (state) {
				case ThreadMonitorState::Signaled: { // The thread is waken up by a signal, so take the ownership of the lock...
					DBASSERT (m_owner == 0);
					DBASSERT (m_counter == 0);

					m_owner = currentThreadId;
					m_acquired ++;
					m_counter ++;

					break;
				}

				case ThreadMonitorState::Interrupted: { // The thread is interrupted while waiting for the lock...
					DBASSERT (interruptible);
					throw InterruptedException (
						"Thread interrupted while acquiring reentrant lock.",
						__FILE__,
						__LINE__);
				}

				default: { // Invalid state...
					throw SynchronizationException (
						"Internal error occurred while acquiring reentrant lock.",
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
inline bool		ReentrantLockImpl<List>::TryAcquire (UInt32 timeout, bool interruptible, UInt32* remaining)
{
	UInt64 start = 0;
	if (remaining != nullptr) {
		start = System::GetCurrentTimeMillis ();
	}

	IntPtr currentThreadId = ThreadImpl::GetCurrentThreadId ();

	bool acquired = false;

	fast_lock (m_lock) { // Serialize access to the internal state...
		if (m_owner == currentThreadId) {
			//  If the current thread is the owner then increment counter and
			// continue immediately.

			m_counter ++;

			acquired = true;
		} else if (m_owner == 0 && m_waiters.GetSize () == 0) {
			// If the lock is free and there are no waiting threads then acquire
			// the lock immediately.

			DBASSERT (m_counter == 0);

			m_owner = currentThreadId;
			m_acquired ++;
			m_counter ++;

			acquired = true;
		} else if (timeout > 0) {
			// If the lock is not free then wait for a signal from a thread
			// releasing its ownership of the lock.

			ThreadImpl* currentThread = ThreadImpl::GetCurrent ();

			m_waiters.Add (currentThread);

			ThreadMonitorState state;

			try {
				ThreadMonitor& monitor = currentThread->GetMonitor ();
				takeownership (monitor) { // Serialize access to the thread monitor...
					fast_unlock (m_lock) { // Release the internal lock while blocking...
						state = monitor.Wait (timeout, interruptible);
					}
				}
			}
			catch (Exception&) {
				m_waiters.Remove (currentThread);
				throw;
			}

			// Remove the current thread from the list of waiting threads regardless
			// of the returned wait status.

			m_waiters.Remove (currentThread);

			switch (state) {
				case ThreadMonitorState::Signaled: { // The thread is waken up by a signal, so take the ownership of the lock...
					DBASSERT (m_owner == 0);
					DBASSERT (m_counter == 0);

					m_owner = currentThreadId;
					m_acquired ++;
					m_counter ++;

					acquired = true;

					break;
				}

				case ThreadMonitorState::Interrupted: { // The thread is interrupted while waiting for the lock...
					DBASSERT (interruptible);
					throw InterruptedException (
						"Thread interrupted while trying to acquire reentrant lock.",
						__FILE__,
						__LINE__);
				}

				case ThreadMonitorState::Timedout: { // Wait timed out...
					acquired = false;
					break;
				}

				default: { // Invalid state...
					throw SynchronizationException (
						"Internal error occurred while trying to acquire reentrant lock.",
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
inline void		ReentrantLockImpl<List>::Release ()
{
	IntPtr currentThreadId = ThreadImpl::GetCurrentThreadId ();

	fast_lock (m_lock) { // Serialize access to the internal state...
		if (DBERROR (m_owner != currentThreadId)) {
			throw SynchronizationException (
				"Attempting to release an unowned lock.",
				__FILE__,
				__LINE__);
		}

		// Update counter and it has reached 0, wake another waiter.

		if (-- m_counter == 0) {
			// Release the ownership of the lock.

			m_owner = 0;

			// Enumerate the list of the waiter threads and attempt to signal a
			// waiter.

			if (m_waiters.GetSize () > 0) {
				UInt32 acquired = m_acquired;
				for (;;) {
					// If acquisition counter is not equal with the saved one then
					// acquisition occurred so there is no need to wake up waiters.

					if (m_acquired != acquired) {
						return;
					}

					for (typename List::Iterator i = m_waiters.Enumerate (); i != nullptr; ) {
						// Try to take ownership of the thread monitor of the waiting
						// thread, if it cant be acquired then skip to the next waiter.

						ThreadMonitor& monitor = (*i)->GetMonitor ();
						if (monitor.TryAcquire ()) {
							// Try to wake up the waiting thread. Note: notify can
							// fail because the wait operation has already been ended
							// (thread killed, interrupted or already notified).

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

					// Release lock and yield processor to give a chance for interrupted threads
					// to come out from TryAcquire/Acquire.

					fast_unlock (m_lock) {
						ThreadImpl::Yield ();
					}
				}
			}
		}
	}
}

}

#endif // GS_REENTRANTLOCKIMPL_HPP
