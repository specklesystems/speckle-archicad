
// *****************************************************************************
//
// Declaration of SpinLock class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_SPINLOCK_HPP
#define GS_SPINLOCK_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Definitions.hpp"
#include "Lockable.hpp"



// --- SpinLock class ----------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT SpinLock : public Lockable {

// Data members:
private:
	volatile Int32 		m_lock;

// Construction / destruction:
public:
			 SpinLock ();
private:
			 SpinLock (const SpinLock&); // Disabled
public:
	virtual ~SpinLock ();

// Operator overloading:
private:
	const SpinLock&		operator = (const SpinLock&); // Disabled

// Lockable interface implementation:
public:
	virtual void		Acquire (bool interruptible = true) override;
	virtual bool		TryAcquire (const Timeout& timeout, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual bool		TryAcquire (UInt32 timeout = 0, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual void		Release () override;

};

////////////////////////////////////////////////////////////////////////////////
// SpinLock inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline SpinLock::SpinLock () :
	m_lock (0)
{
	// Empty constructor body
}

}

#endif // GS_SPINLOCK_HPP
