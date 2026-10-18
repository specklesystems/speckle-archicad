
// *****************************************************************************
//
// Declaration of Semaphore class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_SEMAPHORE_HPP
#define GS_SEMAPHORE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Lockable.hpp"



// --- Forward declarations ----------------------------------------------------

namespace GS {

class FifoSemaphoreImpl;

}



// --- Semaphore class ---------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT Semaphore : public Lockable {

// Data members:
private:
	FifoSemaphoreImpl*	m_impl;

// Construction / destruction:
public:
	explicit Semaphore (UInt32 initialCount = 1, UInt32 maximumCount = 1);
private:
			 Semaphore (const Semaphore&); // Disabled
public:
	virtual ~Semaphore ();

// Operator overloading:
private:
	const Semaphore&	operator = (const Semaphore&); // Disabled

// Lockable interface implementation:
public:
	virtual void		Acquire (bool interruptible = true) override;
	virtual bool		TryAcquire (const Timeout& timeout, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual bool		TryAcquire (UInt32 timeout = 0, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual void		Release () override;

};

}

#endif // GS_SEMAPHORE_HPP
