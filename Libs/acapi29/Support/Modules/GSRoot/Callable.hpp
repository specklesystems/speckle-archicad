
// *****************************************************************************
//
// Declaration of Callable interface
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_CALLABLE_HPP
#define GS_CALLABLE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Object.hpp"



// --- Callable interface ------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT Callable {

// Construction / destruction:
protected:
			 Callable ();
			 Callable (const Callable&);
public:
	virtual ~Callable ();

// Operator overloading:
protected:
	const Callable&		operator = (const Callable&);

// Interface methods:
public:
	virtual Object*		Call () = 0;

};

////////////////////////////////////////////////////////////////////////////////
// Callable inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline Callable::Callable ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline Callable::Callable (const Callable&)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const Callable&	Callable::operator = (const Callable&)
{
	return *this;
}

}

#endif // GS_CALLABLE_HPP
