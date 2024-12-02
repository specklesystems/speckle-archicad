
// *****************************************************************************
//
// Declaration of Process related utility functions
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_PROCESSUTILS_HPP
#define GS_PROCESSUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Process.hpp"



// --- Inline utility functions ------------------------------------------------

namespace GS {

// -----------------------------------------------------------------------------
// CheckProcess
// -----------------------------------------------------------------------------

inline void		CheckProcess (const Process& process, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (process.IsValid () == false)) {
		throw IllegalArgumentException ("Invalid process: process is not valid.", sourceFile, sourceLine);
	}
}

}

#endif // GS_PROCESSUTILS_HPP