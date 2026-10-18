
// *****************************************************************************
//
// Declaration of ProcessId related utility functions
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_PROCESSIDUTILS_HPP
#define GS_PROCESSIDUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "GSException.hpp"
#include "ProcessId.hpp"



// --- Inline utility functions ------------------------------------------------

namespace GS {

// -----------------------------------------------------------------------------
// CheckProcessId
// -----------------------------------------------------------------------------

inline void		CheckProcessId (ProcessId processId, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (processId == 0)) {
		throw IllegalArgumentException ("Invalid process id: id is 0.", sourceFile, sourceLine);
	}
}

}

#endif // GS_PROCESSIDUTILS_HPP