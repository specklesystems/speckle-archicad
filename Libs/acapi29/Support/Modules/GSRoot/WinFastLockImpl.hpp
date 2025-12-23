
// *****************************************************************************
//
// Declaration and implementation of FastLock class (Windows)
//
// Module:          GSRoot
// Namespace:       GS
// Contact person:  SN
//
// *****************************************************************************

#ifndef GS_FASTLOCKIMPL_HPP
#define GS_FASTLOCKIMPL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "SynchronizationException.hpp"
#include "Win32Interface.hpp"



// --- FastLock class ----------------------------------------------------------

namespace GS {

class FastLock {

// Data members:
private:
	CRITICAL_SECTION    m_lock;

// Construction / destruction:
public:
	 FastLock ();
private:
	 FastLock (const FastLock&); // Disabled
public:
	~FastLock ();

// Operator overloading:
private:
	const FastLock&		operator = (const FastLock&); // Disabled

// Operations:
public:
	void				Acquire ();
	bool				TryAcquire ();
	void				Release ();

};

////////////////////////////////////////////////////////////////////////////////
// FastLock implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline FastLock::FastLock ()
{
	::memset (&m_lock, 0, sizeof (CRITICAL_SECTION));
	if (::InitializeCriticalSectionAndSpinCount (&m_lock, 0L) == FALSE) {
		throw SynchronizationException (
			"Failed to create fast lock: failed to create critical section.",
			__FILE__,
			__LINE__);
	}
}

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------

inline FastLock::~FastLock ()
{
	::DeleteCriticalSection (&m_lock);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Acquire
// -----------------------------------------------------------------------------

inline void	FastLock::Acquire ()
{
	__try {
		::EnterCriticalSection (&m_lock);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		throw SynchronizationException (
			"Failed to acquire fast lock: failed to enter critical section.",
			__FILE__,
			__LINE__);
	}
}

// -----------------------------------------------------------------------------
// TryAcquire
// -----------------------------------------------------------------------------

inline bool	FastLock::TryAcquire ()
{
	return (::TryEnterCriticalSection (&m_lock) != FALSE);
}

// -----------------------------------------------------------------------------
// Release
// -----------------------------------------------------------------------------

inline void	FastLock::Release ()
{
	::LeaveCriticalSection (&m_lock);
}

}

#endif // GS_FASTLOCKIMPL_HPP
