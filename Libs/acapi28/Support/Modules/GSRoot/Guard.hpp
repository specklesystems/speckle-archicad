
// *****************************************************************************
//
// Declaration and implementation of Guard class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_GUARD_HPP
#define GS_GUARD_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "TimeoutException.hpp"



// --- LockHolder class --------------------------------------------------------

namespace GS {

template<class LockT>
class LockHolder {

// Data members:
private:
	LockT&				m_lock;

// Construction:
public:
	explicit LockHolder (LockT& lock);
			 LockHolder (const LockHolder& rhs);

// Operator overloading:
private:
	const LockHolder&	operator = (const LockHolder&); // Disabled

// Operations:
public:
	LockT&				GetLock ();

};

////////////////////////////////////////////////////////////////////////////////
// LockHolder implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<class LockT>
LockHolder<LockT>::LockHolder (LockT& lock) :
	m_lock (lock)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

template<class LockT>
LockHolder<LockT>::LockHolder (const LockHolder<LockT>& rhs) :
	m_lock (rhs.m_lock)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetLock
// -----------------------------------------------------------------------------

template<class LockT>
LockT&	LockHolder<LockT>::GetLock ()
{
	return m_lock;
}

}



// --- LockedLockingPolicy class -----------------------------------------------

namespace GS {

class LockedLockingPolicy {

// Operations:
public:
	template<class LockT> void	CreateScope (LockHolder<LockT>& lockHolder);
	template<class LockT> void	CreateScope (LockHolder<LockT>& lockHolder, UInt32 timeout);
	template<class LockT> void	DeleteScope (LockHolder<LockT>& lockHolder);

};

////////////////////////////////////////////////////////////////////////////////
// LockedLockingPolicy implementation

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// CreateScope
// -----------------------------------------------------------------------------

template<class LockT>
void	LockedLockingPolicy::CreateScope (LockHolder<LockT>& lockHolder)
{
	lockHolder.GetLock ().Acquire ();
}

// -----------------------------------------------------------------------------
// CreateScope
// -----------------------------------------------------------------------------

template<class LockT>
void	LockedLockingPolicy::CreateScope (LockHolder<LockT>& lockHolder, UInt32 timeout)
{
	lockHolder.GetLock ().TryAcquire (timeout);
}

// -----------------------------------------------------------------------------
// DeleteScope
// -----------------------------------------------------------------------------

template<class LockT>
void	LockedLockingPolicy::DeleteScope (LockHolder<LockT>& lockHolder)
{
	lockHolder.GetLock ().Release ();
}

}



// --- LockedLockingPolicyEx class ---------------------------------------------

namespace GS {

class LockedLockingPolicyEx {

// Operations:
public:
	template<class LockT> void	CreateScope (LockHolder<LockT>& lockHolder, bool interruptible = true);
	template<class LockT> void	CreateScope (LockHolder<LockT>& lockHolder, UInt32 timeout, bool interruptible = true);
	template<class LockT> void	DeleteScope (LockHolder<LockT>& lockHolder, bool interruptible = true);

};

////////////////////////////////////////////////////////////////////////////////
// LockedLockingPolicyEx implementation

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// CreateScope
// -----------------------------------------------------------------------------

template<class LockT>
void	LockedLockingPolicyEx::CreateScope (LockHolder<LockT>& lockHolder, bool interruptible)
{
	lockHolder.GetLock ().Acquire (interruptible);
}

// -----------------------------------------------------------------------------
// CreateScope
// -----------------------------------------------------------------------------

template<class LockT>
void	LockedLockingPolicyEx::CreateScope (LockHolder<LockT>& lockHolder, UInt32 timeout, bool interruptible)
{
	lockHolder.GetLock ().TryAcquire (timeout, interruptible);
}

// -----------------------------------------------------------------------------
// DeleteScope
// -----------------------------------------------------------------------------

template<class LockT>
void	LockedLockingPolicyEx::DeleteScope (LockHolder<LockT>& lockHolder, bool /*interruptible*/)
{
	lockHolder.GetLock ().Release ();
}

}



// --- UnlockedLockingPolicy class ---------------------------------------------

namespace GS {

class UnlockedLockingPolicy {

// Operations:
public:
	template<class LockT> void	CreateScope (LockHolder<LockT>& lockHolder);
	template<class LockT> void	DeleteScope (LockHolder<LockT>& lockHolder);

};

////////////////////////////////////////////////////////////////////////////////
// UnlockedLockingPolicy implementation

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// CreateScope
// -----------------------------------------------------------------------------

template<class LockT>
void	UnlockedLockingPolicy::CreateScope (LockHolder<LockT>& lockHolder)
{
	lockHolder.GetLock ().Release ();
}

// -----------------------------------------------------------------------------
// DeleteScope
// -----------------------------------------------------------------------------

template<class LockT>
void	UnlockedLockingPolicy::DeleteScope (LockHolder<LockT>& lockHolder)
{
	lockHolder.GetLock ().Acquire ();
}

}



// --- UnlockedLockingPolicyEx class -------------------------------------------

namespace GS {

class UnlockedLockingPolicyEx {

// Operations:
public:
	template<class LockT> void	CreateScope (LockHolder<LockT>& lockHolder, bool interruptible = true);
	template<class LockT> void	DeleteScope (LockHolder<LockT>& lockHolder, bool interruptible = true);

};

////////////////////////////////////////////////////////////////////////////////
// UnlockedLockingPolicyEx implementation

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// CreateScope
// -----------------------------------------------------------------------------

template<class LockT>
void	UnlockedLockingPolicyEx::CreateScope (LockHolder<LockT>& lockHolder, bool /*interruptible*/)
{
	lockHolder.GetLock ().Release ();
}

// -----------------------------------------------------------------------------
// DeleteScope
// -----------------------------------------------------------------------------

template<class LockT>
void	UnlockedLockingPolicyEx::DeleteScope (LockHolder<LockT>& lockHolder, bool interruptible)
{
	lockHolder.GetLock ().Acquire (interruptible);
}

}



// --- TimedLockingPolicy class ------------------------------------------------

namespace GS {

template<UInt32 timeout>
class TimedLockingPolicy {

// Operations:
public:
	template<class LockT> void	CreateScope (LockHolder<LockT>& lockHolder);
	template<class LockT> void	DeleteScope (LockHolder<LockT>& lockHolder);

};

////////////////////////////////////////////////////////////////////////////////
// TimedLockingPolicy implementation

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// CreateScope
// -----------------------------------------------------------------------------

template<UInt32 timeout>
template<class LockT>
void	TimedLockingPolicy<timeout>::CreateScope (LockHolder<LockT>& lockHolder)
{
	if (DBERROR (lockHolder.GetLock ().TryAcquire (timeout) == false)) { // Timeout expired...
		throw TimeoutException ("Timeout expired.", __FILE__, __LINE__);
	}
}

// -----------------------------------------------------------------------------
// DeleteScope
// -----------------------------------------------------------------------------

template<UInt32 timeout>
template<class LockT>
void	TimedLockingPolicy<timeout>::DeleteScope (LockHolder<LockT>& lockHolder)
{
	lockHolder.GetLock ().Release ();
}

}



// --- TimedLockingPolicyEx class ----------------------------------------------

namespace GS {

template<UInt32 timeout>
class TimedLockingPolicyEx {

// Operations:
public:
	template<class LockT> void	CreateScope (LockHolder<LockT>& lockHolder, bool interruptible = true);
	template<class LockT> void	DeleteScope (LockHolder<LockT>& lockHolder, bool interruptible = true);

};

////////////////////////////////////////////////////////////////////////////////
// TimedLockingPolicy implementation

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// CreateScope
// -----------------------------------------------------------------------------

template<UInt32 timeout>
template<class LockT>
void	TimedLockingPolicyEx<timeout>::CreateScope (LockHolder<LockT>& lockHolder, bool interruptible)
{
	if (DBERROR (lockHolder.GetLock ().TryAcquire (timeout, interruptible) == false)) { // Timeout expired...
		throw TimeoutException ("Timeout expired.", __FILE__, __LINE__);
	}
}

// -----------------------------------------------------------------------------
// DeleteScope
// -----------------------------------------------------------------------------

template<UInt32 timeout>
template<class LockT>
void	TimedLockingPolicyEx<timeout>::DeleteScope (LockHolder<LockT>& lockHolder, bool /*interruptible*/)
{
	lockHolder.GetLock ().Release ();
}

}



// --- Guard class -------------------------------------------------------------

namespace GS {

template<class LockT, class LockingPolicy = LockedLockingPolicy>
class [[nodiscard]] Guard : public LockHolder<LockT> {

// Data members:
private:
	LockingPolicy	m_lockingPolicy;

// Construction / destruction:
public:
	 Guard (LockT& lock);
	 Guard (volatile LockT& lock);
	 Guard (LockT& lock, UInt32 timeout);
	 Guard (const Guard& rhs);
public:
	~Guard ();

// Operator overloading:
private:
	const Guard&	operator = (const Guard&); // Disabled
public:
					operator bool () const;

};

////////////////////////////////////////////////////////////////////////////////
// Guard implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<class LockT, class LockingPolicy>
Guard<LockT, LockingPolicy>::Guard (LockT& lock) :
	LockHolder<LockT> (lock),
	m_lockingPolicy ()
{
	m_lockingPolicy.CreateScope (*this);
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<class LockT, class LockingPolicy>
Guard<LockT, LockingPolicy>::Guard (volatile LockT& lock) :
	LockHolder<LockT> (const_cast<LockT&> (lock)),
	m_lockingPolicy ()
{
	m_lockingPolicy.CreateScope (*this);
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<class LockT, class LockingPolicy>
Guard<LockT, LockingPolicy>::Guard (LockT& lock, UInt32 timeout) :
	LockHolder<LockT> (lock),
	m_lockingPolicy ()
{
	m_lockingPolicy.CreateScope (*this, timeout);
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

template<class LockT, class LockingPolicy>
Guard<LockT, LockingPolicy>::Guard (const Guard<LockT, LockingPolicy>& rhs) :
	LockHolder<LockT> (rhs),
	m_lockingPolicy (rhs.m_lockingPolicy)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------

template<class LockT, class LockingPolicy>
Guard<LockT, LockingPolicy>::~Guard ()
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

template<class LockT, class LockingPolicy>
Guard<LockT, LockingPolicy>::operator bool () const
{
	return false;
}

}



// --- GuardEx class -----------------------------------------------------------

namespace GS {

template<class LockT, class LockingPolicyEx = LockedLockingPolicyEx>
class [[nodiscard]] GuardEx : public LockHolder<LockT> {

// Data members:
private:
	LockingPolicyEx	m_lockingPolicy;
	bool			m_interruptible;

// Construction / destruction:
public:
	 GuardEx (LockT& lock, bool interruptible = true);
	 GuardEx (LockT& lock, UInt32 timeout, bool interruptible = true);
	 GuardEx (const GuardEx& rhs);
public:
	~GuardEx ();

// Operator overloading:
private:
	const GuardEx&	operator = (const GuardEx&); // Disabled
public:
					operator bool () const;

};

////////////////////////////////////////////////////////////////////////////////
// GuardEx implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<class LockT, class LockingPolicyEx>
GuardEx<LockT, LockingPolicyEx>::GuardEx (LockT& lock, bool interruptible) :
	LockHolder<LockT> (lock),
	m_lockingPolicy (),
	m_interruptible (interruptible)
{
	m_lockingPolicy.CreateScope (*this, interruptible);
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<class LockT, class LockingPolicyEx>
GuardEx<LockT, LockingPolicyEx>::GuardEx (LockT& lock, UInt32 timeout, bool interruptible) :
	LockHolder<LockT> (lock),
	m_lockingPolicy (),
	m_interruptible (interruptible)
{
	m_lockingPolicy.CreateScope (*this, timeout, interruptible);
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

template<class LockT, class LockingPolicyEx>
GuardEx<LockT, LockingPolicyEx>::GuardEx (const GuardEx<LockT, LockingPolicyEx>& rhs) :
	LockHolder<LockT> (rhs),
	m_lockingPolicy (rhs.m_lockingPolicy),
	m_interruptible (rhs.m_interruptible)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------

template<class LockT, class LockingPolicyEx>
GuardEx<LockT, LockingPolicyEx>::~GuardEx ()
{
	try {
		m_lockingPolicy.DeleteScope (*this, m_interruptible);
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

template<class LockT, class LockingPolicyEx>
GuardEx<LockT, LockingPolicyEx>::operator bool () const
{
	return false;
}

}



// --- Macro definitions -------------------------------------------------------

#define _LINENAME_CAT(name, line) name##line
#define _LINENAME(name, line) _LINENAME_CAT(name, line)
#define LINENAME(name) _LINENAME(name, __LINE__)

namespace GS {

class Lockable;

// TODO: CTC workaround, revisit when upgrading CTC (use these types directly in the macros)
using Guard_for_synchronized_uninterruptible = GS::GuardEx<GS::Lockable, GS::LockedLockingPolicyEx>;
using Guard_for_synchronized_interruptible = GS::GuardEx<GS::Lockable, GS::LockedLockingPolicyEx>;
using Guard_for_synchronizedex = GS::GuardEx<GS::Lockable, GS::LockedLockingPolicyEx>;
using Guard_for_synchronized = GS::Guard<GS::Lockable, GS::LockedLockingPolicy>;

}

#define synchronized_uninterruptible(lockable)	\
	if (GS::Guard_for_synchronized_uninterruptible LINENAME(g) = GS::GuardEx<GS::Lockable, GS::LockedLockingPolicyEx> (lockable, false)) { for (;;); } else
#define synchronized_interruptible(lockable)	\
	if (GS::Guard_for_synchronized_interruptible LINENAME(g) = GS::GuardEx<GS::Lockable, GS::LockedLockingPolicyEx> (lockable, true)) { for (;;); } else
#define synchronizedex(lockable, interruptible)	\
	if (GS::Guard_for_synchronizedex LINENAME(g) = GS::GuardEx<GS::Lockable, GS::LockedLockingPolicyEx> (lockable, interruptible)) { for (;;); } else
#define synchronized(lockable)					\
	if (GS::Guard_for_synchronized LINENAME(g) = lockable) { for (;;); } else


namespace GS {

template <typename Function>
decltype (auto)		Synchronize (GS::Lockable& lockable, Function&& function)
{
	GS::Guard<GS::Lockable, GS::LockedLockingPolicy> guard (lockable);

	return std::forward<Function> (function) ();
}

}	// namespace GS


#endif // GS_GUARD_HPP
