
// *****************************************************************************
//
// Declaration of ShutdownListener interface
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_SHUTDOWNLISTENER_HPP
#define GS_SHUTDOWNLISTENER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "GSRootExport.hpp"



// --- ShutdownListener class --------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT ShutdownListener {

// Construction / destruction:
protected:
			 ShutdownListener ();
			 ShutdownListener (const ShutdownListener&);
public:
	virtual ~ShutdownListener ();

// Operator overloading:
protected:
	const ShutdownListener&		operator = (const ShutdownListener&);

// Operations:
public:
	virtual void				BeforeShutdown () = 0;
	virtual void				AfterShutdown () = 0;

};

////////////////////////////////////////////////////////////////////////////////
// ShutdownListener inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ShutdownListener::ShutdownListener ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline ShutdownListener::ShutdownListener (const ShutdownListener&)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const ShutdownListener&	ShutdownListener::operator = (const ShutdownListener&)
{
	return *this;
}

}

#endif // GS_SHUTDOWNLISTENER_HPP
