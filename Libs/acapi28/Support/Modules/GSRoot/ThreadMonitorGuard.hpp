
// *****************************************************************************
//
// Declaration and implementation of ThreadMonitorGuard
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_THREADMONITORGUARD_HPP
#define GS_THREADMONITORGUARD_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Guard.hpp"
#include "ThreadMonitor.hpp"



// --- ThreadMonitorGuard class ------------------------------------------------

namespace GS {

template<class LockingPolicy = LockedLockingPolicy>
class [[nodiscard]] ThreadMonitorGuard : public LockHolder<ThreadMonitor> {

// Data members:
private:
	LockingPolicy				m_lockingPolicy;		// The locking policy of the thread monitor guard

// Construction / destruction:
public:
	 ThreadMonitorGuard (ThreadMonitor& monitor);
	 ThreadMonitorGuard (ThreadMonitor& monitor, UInt32 timeout);
	 ThreadMonitorGuard (const ThreadMonitorGuard& rhs);
	~ThreadMonitorGuard ();

// Operator overloading:
private:
	const ThreadMonitorGuard&	operator = (const ThreadMonitorGuard&); // Disabled
public:
								operator bool () const;

};

////////////////////////////////////////////////////////////////////////////////
// Guard<LockT, LockingPolicy> inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<class LockingPolicy>
inline ThreadMonitorGuard<LockingPolicy>::ThreadMonitorGuard (ThreadMonitor& monitor) :
	LockHolder<ThreadMonitor> (monitor),
	m_lockingPolicy ()
{
	m_lockingPolicy.CreateScope (*this);
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<class LockingPolicy>
inline ThreadMonitorGuard<LockingPolicy>::ThreadMonitorGuard (ThreadMonitor& monitor, UInt32 timeout) :
	LockHolder<ThreadMonitor> (monitor),
	m_lockingPolicy ()
{
	m_lockingPolicy.CreateScope (*this, timeout);
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

template<class LockingPolicy>
inline ThreadMonitorGuard<LockingPolicy>::ThreadMonitorGuard (const ThreadMonitorGuard<LockingPolicy>& rhs) :
	LockHolder<ThreadMonitor> (rhs),
	m_lockingPolicy (rhs.m_lockingPolicy)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------

template<class LockingPolicy>
inline ThreadMonitorGuard<LockingPolicy>::~ThreadMonitorGuard ()
{
	try {
		m_lockingPolicy.DeleteScope (*this);
	}
	catch (...) {
		// Empty handler
	}
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator bool
// -----------------------------------------------------------------------------

template<class LockingPolicy>
inline ThreadMonitorGuard<LockingPolicy>::operator bool () const
{
	return false;
}

}



// --- Macro definitions -------------------------------------------------------

namespace GS {

// TODO: CTC workaround, revisit when upgrading CTC (use these types directly in the macros)
using Guard_for_takeownership = GS::ThreadMonitorGuard<GS::LockedLockingPolicy>;
using Guard_for_releaseownership = GS::ThreadMonitorGuard<GS::UnlockedLockingPolicy>;

}

#define takeownership(monitor)		if (GS::Guard_for_takeownership LINENAME(g) = monitor) { for (;;); } else
#define releaseownership(monitor)	if (GS::Guard_for_releaseownership LINENAME(g) = monitor) { for (;;); } else

#endif // GS_THREADMONITORGUARD_HPP
