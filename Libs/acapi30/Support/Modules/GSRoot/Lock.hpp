
// *****************************************************************************
//
// Declaration of Lock class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_LOCK_HPP
#define GS_LOCK_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Definitions.hpp"
#include "Lockable.hpp"



// --- Forward declarations ----------------------------------------------------

namespace GS {

class FifoLockImpl;

}



// --- Lock class --------------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT Lock : public Lockable {

// Data members:
private:
	FifoLockImpl*		m_impl;

// Construction / destruction:
public:
			 Lock ();
private:
			 Lock (const Lock&); // Disabled
public:
	virtual ~Lock ();

// Operator overloading:
private:
	const Lock&			operator = (const Lock&); // Disabled

// Lockable interface implementation:
public:
	virtual void		Acquire (bool interruptible = true) override;
	virtual bool		TryAcquire (const Timeout& timeout, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual bool		TryAcquire (UInt32 timeout = 0, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual void		Release () override;

};

}

#endif // GS_LOCK_HPP
