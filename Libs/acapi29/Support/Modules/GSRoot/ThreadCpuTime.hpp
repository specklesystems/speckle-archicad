
// *****************************************************************************
//
// Declaration of ThreadCpuTime class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_THREADCPUTIME_HPP
#define GS_THREADCPUTIME_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Definitions.hpp"
#include "GSRootExport.hpp"



// --- ThreadCpuTime class -----------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT ThreadCpuTime {

// Static operations:
public:
	static UInt64	GetCurrentThreadCpuTimeInMillis ();
	static UInt64	GetCurrentThreadCpuTimeInNanos ();

};

}

#endif // GS_THREADCPUTIME_HPP