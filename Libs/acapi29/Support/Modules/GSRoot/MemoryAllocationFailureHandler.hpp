
// *****************************************************************************
//
// Declaration of MemoryAllocationFailureHandler interface
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_MEMORYALLOCATIONFAILUREHANDLER_HPP
#define GS_MEMORYALLOCATIONFAILUREHANDLER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "GSRootExport.hpp"
#include <stddef.h>



// --- MemoryAllocationFailureHandler class ------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT MemoryAllocationFailureHandler {

// Construction / destruction:
protected:
			 MemoryAllocationFailureHandler ();
			 MemoryAllocationFailureHandler (const MemoryAllocationFailureHandler&);
public:
	virtual ~MemoryAllocationFailureHandler ();

// Operator overloading:
protected:
	const MemoryAllocationFailureHandler&	operator = (const MemoryAllocationFailureHandler&);

// Operations:
public:
	virtual bool							AllocationFailed (size_t size) = 0;

};

////////////////////////////////////////////////////////////////////////////////
// MemoryAllocationFailureHandler inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline MemoryAllocationFailureHandler::MemoryAllocationFailureHandler ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline MemoryAllocationFailureHandler::MemoryAllocationFailureHandler (const MemoryAllocationFailureHandler&)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const MemoryAllocationFailureHandler&	MemoryAllocationFailureHandler::operator = (const MemoryAllocationFailureHandler&)
{
	return *this;
}

}

#endif // GS_MEMORYALLOCATIONFAILUREHANDLER_HPP
