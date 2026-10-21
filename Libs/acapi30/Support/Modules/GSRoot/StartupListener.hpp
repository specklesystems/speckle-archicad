
// *****************************************************************************
//
// Declaration of StartupListener interface
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_STARTUPLISTENER_HPP
#define GS_STARTUPLISTENER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "GSRootExport.hpp"



// --- StartupListener class ---------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT StartupListener {

// Construction / destruction:
protected:
			 StartupListener ();
			 StartupListener (const StartupListener&);
public:
	virtual ~StartupListener ();

// Operator overloading:
protected:
	const StartupListener&	operator = (const StartupListener&);

// Operations:
public:
	virtual void			BeforeStartup () = 0;
	virtual void			AfterStartup () = 0;

};

////////////////////////////////////////////////////////////////////////////////
// StartupListener inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline StartupListener::StartupListener ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline StartupListener::StartupListener (const StartupListener&)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const StartupListener&	StartupListener::operator = (const StartupListener&)
{
	return *this;
}

}

#endif // GS_STARTUPLISTENER_HPP