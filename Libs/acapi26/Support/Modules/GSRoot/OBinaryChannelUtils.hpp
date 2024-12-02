
// *****************************************************************************
//
// Declaration of OBinaryChannel related utility functions
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_OBINARYCHANNELUTILS_HPP
#define GS_OBINARYCHANNELUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "OBinaryChannel.hpp"



// --- Inline utility functions ------------------------------------------------

namespace GS {

// -----------------------------------------------------------------------------
// CheckOutputChannel
// -----------------------------------------------------------------------------

inline void		CheckOutputChannel (const OBinaryChannelRef& outputChannel, const char* sourceFile, UInt32 sourceLine)
{
	if (DBERROR (outputChannel == nullptr)) {
		throw IllegalArgumentException ("Invalid output channel: channel is null.", sourceFile, sourceLine);
	}
}

// -----------------------------------------------------------------------------
// CheckSourceBuffer
// -----------------------------------------------------------------------------

inline void		CheckSourceBuffer (const char* source, USize sourceSize, const char* sourceFile, UInt32 sourceLine)
{
	if (DBERROR (source == nullptr)) {
		throw IllegalArgumentException ("Invalid source buffer: source buffer is null.", sourceFile, sourceLine);
	}
	if (DBERROR (sourceSize == 0)) {
		throw IllegalArgumentException ("Invalid source buffer: buffer size is 0.", sourceFile, sourceLine);
	}
}

}

#endif // GS_OBINARYCHANNELUTILS_HPP