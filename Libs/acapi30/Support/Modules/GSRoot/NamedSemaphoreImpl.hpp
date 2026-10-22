
// *****************************************************************************
//
// Declaration of NamedSemaphoreImpl class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SZCS
//
// *****************************************************************************

#ifndef GS_NAMEDSEMAPHOREIMPL_HPP
#define GS_NAMEDSEMAPHOREIMPL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Definitions.hpp"



// --- NamedSemaphoreImpl class ------------------------------------------------

namespace GS {

class NamedSemaphoreImpl {

// Construction / destruction:
protected:
			 NamedSemaphoreImpl ();
			 NamedSemaphoreImpl (const NamedSemaphoreImpl& source);
public:
	virtual ~NamedSemaphoreImpl ();

// Operator overloading:
protected:
	const NamedSemaphoreImpl&	operator = (const NamedSemaphoreImpl& source);

// Operations:
public:
	virtual void				Acquire (bool interruptible = true) = 0;
	virtual bool				TryAcquire (UInt32 timeout = 0, bool interruptible = true, GS::UInt32* remaining = nullptr) = 0;
	virtual void				Release () = 0;

// Static operations:
public:
	static NamedSemaphoreImpl*	Create (const char* name, UInt32 initialCount);

};

////////////////////////////////////////////////////////////////////////////////
// NamedSemaphoreImpl inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline NamedSemaphoreImpl::NamedSemaphoreImpl ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline NamedSemaphoreImpl::NamedSemaphoreImpl (const NamedSemaphoreImpl& /*source*/)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const NamedSemaphoreImpl&	NamedSemaphoreImpl::operator = (const NamedSemaphoreImpl& /*source*/)
{
	return *this;
}

}

#endif // GS_NAMEDSEMAPHOREIMPL_HPP
