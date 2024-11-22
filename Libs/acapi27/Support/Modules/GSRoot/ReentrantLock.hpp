
// *****************************************************************************
//
// Declaration of ReentrantLock class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_REENTRANTLOCK_HPP
#define GS_REENTRANTLOCK_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Definitions.hpp"
#include "Lockable.hpp"



// --- Forward declarations ----------------------------------------------------

namespace GS {

class FifoReentrantLockImpl;

}



// --- ReentrantLock class -----------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT ReentrantLock : public Lockable {

// Data members:
private:
	FifoReentrantLockImpl*	m_impl;

// Construction / destruction:
public:
			 ReentrantLock ();
private:
			 ReentrantLock (const ReentrantLock&); // Disabled
public:
	virtual ~ReentrantLock ();

// Operator overloading:
private:
	const ReentrantLock&	operator = (const ReentrantLock&); // Disabled

// Lockable interface implementation:
public:
	virtual void			Acquire (bool interruptible = true) override;
	virtual bool			TryAcquire (const Timeout& timeout, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual bool			TryAcquire (UInt32 timeout = 0, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual void			Release () override;

};

}

#endif // GS_REENTRANTLOCK_HPP
