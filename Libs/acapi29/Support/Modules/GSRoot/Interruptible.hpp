
// *****************************************************************************
//
// Declaration of the Interruptible interface.
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN, FM
//
// *****************************************************************************

#ifndef GS_INTERRUPTIBLE_HPP
#define GS_INTERRUPTIBLE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "GSRootExport.hpp"



// --- Interruptible interface -------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT Interruptible {

// Construction / destruction:
protected:
			 Interruptible ();
			 Interruptible (const Interruptible&);
public:
	virtual ~Interruptible ();

// Operator overloading:
protected:
	const Interruptible&	operator = (const Interruptible&);

// Interface methods:
public:
	virtual void			Interrupt () = 0;

};

////////////////////////////////////////////////////////////////////////////////
// Interruptible inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline Interruptible::Interruptible ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline Interruptible::Interruptible (const Interruptible&)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const Interruptible&		Interruptible::operator = (const Interruptible&)
{
	return *this;
}

}

#endif // GS_INTERRUPTIBLE_HPP
