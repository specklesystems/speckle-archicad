
// *****************************************************************************
//
// Declaration of Waitable interface
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_WAITABLE_HPP
#define GS_WAITABLE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Definitions.hpp"
#include "Timeout.hpp"



// --- Waitable interface ------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT Waitable {

// Construction / destruction:
protected:
			 Waitable ();
			 Waitable (const Waitable&);
public:
	virtual ~Waitable ();

// Operator overloading:
protected:
	const Waitable&		operator = (const Waitable&);

// Interface methods:
public:
	virtual bool		Wait (const Timeout& timeout, bool interruptible = true, UInt32* remaining = nullptr);
	virtual bool		Wait (UInt32 timeout, bool interruptible = true, UInt32* remaining = nullptr) = 0;
	virtual void		Wait (bool interruptible = true) = 0;

};

////////////////////////////////////////////////////////////////////////////////
// Waitable inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline Waitable::Waitable ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline Waitable::Waitable (const Waitable&)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const Waitable&	Waitable::operator = (const Waitable&)
{
	return *this;
}

}

#endif // GS_WAITABLE_HPP
