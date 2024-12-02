
// *****************************************************************************
//
// Declaration of AsyncResult interface
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_ASYNCRESULT_HPP
#define GS_ASYNCRESULT_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Cancelable.hpp"
#include "Object.hpp"
#include "Waitable.hpp"


// --- AsyncResult interface ---------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT AsyncResult : public Cancelable, public Waitable {

// Construction / destruction:
protected:
			 AsyncResult ();
			 AsyncResult (const AsyncResult&);
public:
	virtual ~AsyncResult ();

// Operator overloading:
protected:
	const AsyncResult&	operator = (const AsyncResult&);

// Interface methods:
public:
	virtual bool		IsCompleted () const = 0;

	virtual Object*		Get (const Timeout& timeout, bool interruptible = true, UInt32* remaining = nullptr);
	virtual Object*		Get (UInt32 timeout, bool interruptible = true, UInt32* remaining = nullptr) = 0;
	virtual	Object*		Get (bool interruptible = true) = 0;

};

////////////////////////////////////////////////////////////////////////////////
// AsyncResult inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline AsyncResult::AsyncResult ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline AsyncResult::AsyncResult (const AsyncResult&)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const AsyncResult&	AsyncResult::operator = (const AsyncResult&)
{
	return *this;
}

}

#endif // GS_ASYNCRESULT_HPP
