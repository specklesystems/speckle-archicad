
// *****************************************************************************
//
// Declaration of System class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_SYSTEM_HPP
#define GS_SYSTEM_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Definitions.hpp"
#include "GSRootExport.hpp"



// --- System class ------------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT System {

// Construction / destruction:
public:
	System () = delete;
	System (const System&) = delete;

// Operator overloading:
public:
	System&			operator = (const System&) = delete;

// Static operations:
public:
	static UInt32	GetNumberOfActiveProcessors ();

	static UInt64	GetPhysicalMemorySize ();
	static UInt64	GetVirtualMemorySize ();

	static USize	GetPageSize ();

	static UInt64	GetCurrentTimeMillis ();
	static UInt64	GetCurrentTimeNanos ();

// Static implementation:
private:
	static UInt32	GetForcedProcessors ();

};

}

#endif // GS_SYSTEM_HPP
