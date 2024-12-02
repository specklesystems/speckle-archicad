
// *****************************************************************************
//
// Declaration of Cancelable interface
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_CANCELABLE_HPP
#define GS_CANCELABLE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "GSRootExport.hpp"



// --- Cancelable interface ----------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT Cancelable {

// Construction / destruction:
protected:
			 Cancelable ();
			 Cancelable (const Cancelable&);
public:
	virtual ~Cancelable ();

// Operator overloading:
protected:
	const Cancelable&	operator = (const Cancelable&);

// Interface methods:
public:
	virtual bool		IsCanceled () const = 0;
	virtual void		Cancel () = 0;

};

////////////////////////////////////////////////////////////////////////////////
// Cancelable inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline Cancelable::Cancelable ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline Cancelable::Cancelable (const Cancelable&)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const Cancelable&	Cancelable::operator = (const Cancelable&)
{
	return *this;
}

}

#endif // GS_CANCELABLE_HPP
