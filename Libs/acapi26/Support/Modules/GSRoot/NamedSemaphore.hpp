
// *****************************************************************************
//
// Declaration of NamedSemaphore class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SZCS
//
// *****************************************************************************

#ifndef GS_NAMEDSEMAPHORE_HPP
#define GS_NAMEDSEMAPHORE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Lockable.hpp"




// --- Forward declarations ----------------------------------------------------

namespace GS {

class NamedSemaphoreImpl;


}



// --- NamedSemaphore class ----------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT NamedSemaphore : public Lockable {

// Data members:
private:
	NamedSemaphoreImpl*		m_pImpl;

// Construction / destruction:
public:
	explicit NamedSemaphore (const char* name, UInt32 initialCount = 1);
	virtual ~NamedSemaphore ();
private:
	NamedSemaphore (const NamedSemaphore&); // Disabled

// Operator overloading:
private:
	const NamedSemaphore&	operator = (const NamedSemaphore&); // Disabled

// Lockable interface implementation:
public:
	virtual void			Acquire (bool interruptible = true) override;
	virtual bool			TryAcquire (const Timeout& timeout, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual bool			TryAcquire (UInt32 timeout = 0, bool interrupible = true, UInt32* remaining = nullptr) override;
	virtual void			Release () override;

};

}

#endif // GS_NAMEDSEMAPHORE_HPP
