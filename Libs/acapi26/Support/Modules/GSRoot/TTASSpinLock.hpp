
// *****************************************************************************
//
// Declaration and implementation of TTASSpinLock class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_TTASSPINLOCK_HPP
#define GS_TTASSPINLOCK_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "ExponentialBackoff.hpp"
#include "SpinLockBase.hpp"

#if defined (WINDOWS)
#pragma warning (push)
#pragma warning (disable :4324)
#endif

#include <atomic>



// --- TTASSpinLock class ------------------------------------------------------

namespace GS {

template<UInt32 MinBackoffSpinCount = 32, UInt32 MaxBackoffSpinCount = 8192, UInt32 MaxWaitSpinCount = 65536>
class TTASSpinLock : private SpinLockBase { // Test and Test-And-Set spin lock with exponential back off

// Type definitions:
private:
	typedef ExponentialBackoff<MinBackoffSpinCount, MaxBackoffSpinCount> ExponentialBackoff;
	typedef std::atomic<bool> AtomicBool;

// Data members:
private:
	alignas (CacheLineSize) AtomicBool	m_lock;	// Align to cache line to prevent false sharing....

// Construction / destruction:
public:
	 TTASSpinLock ();
	 TTASSpinLock (const TTASSpinLock&) = delete;
	~TTASSpinLock ();

// Operator overloading:
public:
	TTASSpinLock&						operator = (const TTASSpinLock&) = delete;

// Operations:
public:
	void								Acquire ();
	void								Release ();

// Implementation:
private:
	void								WaitUntilFree ();
	bool								TryAcquire ();

	void								Backoff (UInt32 currentBackoffSpinCount);

	void								Spin (UInt32& spinCount);

};

////////////////////////////////////////////////////////////////////////////////
// TTASSpinLock implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

template<UInt32 MinBackoffSpinCount, UInt32 MaxBackoffSpinCount, UInt32 MaxWaitSpinCount>
inline TTASSpinLock<MinBackoffSpinCount, MaxBackoffSpinCount, MaxWaitSpinCount>::TTASSpinLock () :
	m_lock (false)
{
	// Empty constructor body
}
	 
// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------

template<UInt32 MinBackoffSpinCount, UInt32 MaxBackoffSpinCount, UInt32 MaxWaitSpinCount>
inline TTASSpinLock<MinBackoffSpinCount, MaxBackoffSpinCount, MaxWaitSpinCount>::~TTASSpinLock ()
{
	DBASSERT (m_lock.load (std::memory_order_acquire) == false);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Acquire
// -----------------------------------------------------------------------------

template<UInt32 MinBackoffSpinCount, UInt32 MaxBackoffSpinCount, UInt32 MaxWaitSpinCount>
inline void		TTASSpinLock<MinBackoffSpinCount, MaxBackoffSpinCount, MaxWaitSpinCount>::Acquire ()
{
	UInt32 currentBackoffSpinCount = MinBackoffSpinCount;

	for (;;) {
		WaitUntilFree ();
		if (TryAcquire () == false) {
			currentBackoffSpinCount = ExponentialBackoff::GetNextBackoffSpinCount (currentBackoffSpinCount);
			Backoff (currentBackoffSpinCount);
		} else {
			return;
		}
	}
}

// -----------------------------------------------------------------------------
// Release
// -----------------------------------------------------------------------------

template<UInt32 MinBackoffSpinCount, UInt32 MaxBackoffSpinCount, UInt32 MaxWaitSpinCount>
inline void		TTASSpinLock<MinBackoffSpinCount, MaxBackoffSpinCount, MaxWaitSpinCount>::Release ()
{
	m_lock.store (false, std::memory_order_release);
}

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// WaitUntilFree
// -----------------------------------------------------------------------------

template<UInt32 MinBackoffSpinCount, UInt32 MaxBackoffSpinCount, UInt32 MaxWaitSpinCount>
inline void		TTASSpinLock<MinBackoffSpinCount, MaxBackoffSpinCount, MaxWaitSpinCount>::WaitUntilFree ()
{
	UInt32 spinCount = 0;
	while (m_lock.load (std::memory_order_relaxed)) {
		Spin (++ spinCount);
	}
}

// -----------------------------------------------------------------------------
// TryAcquire
// -----------------------------------------------------------------------------

template<UInt32 MinBackoffSpinCount, UInt32 MaxBackoffSpinCount, UInt32 MaxWaitSpinCount>
inline bool		TTASSpinLock<MinBackoffSpinCount, MaxBackoffSpinCount, MaxWaitSpinCount>::TryAcquire ()
{
	return (m_lock.exchange (true, std::memory_order_acquire) == false);
}

// -----------------------------------------------------------------------------
// Backoff
// -----------------------------------------------------------------------------

template<UInt32 MinBackoffSpinCount, UInt32 MaxBackoffSpinCount, UInt32 MaxWaitSpinCount>
inline void		TTASSpinLock<MinBackoffSpinCount, MaxBackoffSpinCount, MaxWaitSpinCount>::Backoff (UInt32 currentBackoffSpinCount)
{
	for (UInt32 spinCount = 0; spinCount < currentBackoffSpinCount; spinCount ++) {
		SpinLockBase::Pause ();
	}
}

// -----------------------------------------------------------------------------
// Spin
// -----------------------------------------------------------------------------

template<UInt32 MinBackoffSpinCount, UInt32 MaxBackoffSpinCount, UInt32 MaxWaitSpinCount>
inline void		TTASSpinLock<MinBackoffSpinCount, MaxBackoffSpinCount, MaxWaitSpinCount>::Spin (UInt32& spinCount)
{
	if (spinCount >= MaxWaitSpinCount) {
		SpinLockBase::Sleep ();
	} else {
		SpinLockBase::Pause ();
		spinCount++;
	}
}

}

#if defined (WINDOWS)
#pragma warning (pop)
#endif

#endif // GS_TTASSPINLOCK_HPP