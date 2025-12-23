
// *****************************************************************************
//
// Declaration of Lockable interface
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_LOCKABLE_HPP
#define GS_LOCKABLE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Timeout.hpp"



// --- Lockable interface ------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT Lockable {

// Construction / destruction:
protected:
			 Lockable ();
			 Lockable (const Lockable&);
public:
	virtual ~Lockable ();

// Operator overloading:
protected:
	const Lockable&		operator = (const Lockable&);

// Interface methods:
public:
	virtual void		Acquire (bool interruptible = true) = 0;
	virtual bool		TryAcquire (const Timeout& timeout, bool interruptible = true, UInt32* remaining = nullptr);
	virtual bool		TryAcquire (UInt32 timeout = 0, bool interrupible = true, UInt32* remaining = nullptr) = 0;
	virtual void		Release () = 0;

};

////////////////////////////////////////////////////////////////////////////////
// Lockable inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline Lockable::Lockable ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline Lockable::Lockable (const Lockable&)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const Lockable&	Lockable::operator = (const Lockable&)
{
	return *this;
}

}

#endif // GS_LOCKABLE_HPP
