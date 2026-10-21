
// *****************************************************************************
//
// Declaration of Runnable interface
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_RUNNABLE_HPP
#define GS_RUNNABLE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "GSRootExport.hpp"



// --- Runnable interface ------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT Runnable {

// Construction / destruction:
protected:
			 Runnable ();
			 Runnable (const Runnable&);
public:
	virtual ~Runnable ();

// Operator overloading:
protected:
	const Runnable&		operator = (const Runnable&);

// Interface methods:
public:
	virtual void		Run () = 0;

};

////////////////////////////////////////////////////////////////////////////////
// Runnable inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline Runnable::Runnable ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline Runnable::Runnable (const Runnable&)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const Runnable&	Runnable::operator = (const Runnable&)
{
	return *this;
}

}

#endif // GS_RUNNABLE_HPP
