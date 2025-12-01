
// *****************************************************************************
//
// Declaration of ThreadingException class
//
// Module:          GSRoot
// Namespace:       GS
// Contact person:  SN
//
// *****************************************************************************

#ifndef GS_THREADINGEXCEPTION_HPP
#define GS_THREADINGEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "GSException.hpp"



// --- ThreadingException class ------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT ThreadingException : public virtual Exception {

// Construction / destruction:
public:
	explicit ThreadingException (const char* msg, const char* fName, UInt32 lNumber, const Exception& cause);
	explicit ThreadingException (const char* msg = nullptr, const char* fName = nullptr, UInt32 lNumber = 0);
	explicit ThreadingException (const UniString& msg, const char* fName, UInt32 lNumber, const Exception& cause);
	explicit ThreadingException (const UniString& msg, const char* fName = nullptr, UInt32 lNumber = 0);

// Exception overrides:
public:
	virtual const char*		GetName () const override;
	virtual Exception*		Clone () const override;

};

////////////////////////////////////////////////////////////////////////////////
// ThreadingException inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline ThreadingException::ThreadingException (const char* msg, const char* fName, UInt32 lNumber, const Exception& cause) :
	Exception (msg, fName, lNumber, cause, Error)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline ThreadingException::ThreadingException (const char* msg, const char* fName, UInt32 lNumber) :
	Exception (msg, fName, lNumber, nullptr, Error)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline ThreadingException::ThreadingException (const UniString& msg, const char* fName, UInt32 lNumber, const Exception& cause) :
	Exception (msg, fName, lNumber, cause, Error)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline ThreadingException::ThreadingException (const UniString& msg, const char* fName, UInt32 lNumber) :
	Exception (msg, fName, lNumber, nullptr, Error)
{
	// Empty constructor body
}

}

#endif // GS_THREADINGEXCEPTION_HPP
