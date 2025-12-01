
// *****************************************************************************
//
// Declaration of IBinaryChannel related utility functions
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_IBINARYCHANNELUTILS_HPP
#define GS_IBINARYCHANNELUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "IBinaryChannel.hpp"



// --- Inline utility functions ------------------------------------------------

namespace GS {

// -----------------------------------------------------------------------------
// CheckInputChannel
// -----------------------------------------------------------------------------

inline void		CheckInputChannel (const IBinaryChannelRef& inputChannel, const char* sourceFile, UInt32 sourceLine)
{
	if (DBERROR (inputChannel == nullptr)) {
		throw IllegalArgumentException ("Invalid input channel: channel is null.", sourceFile, sourceLine);
	}
}

// -----------------------------------------------------------------------------
// CheckTargetBuffer
// -----------------------------------------------------------------------------

inline void		CheckTargetBuffer (char* target, USize targetSize, const char* sourceFile, UInt32 sourceLine)
{
	if (DBERROR (target == nullptr)) {
		throw IllegalArgumentException ("Invalid target buffer: target buffer is null.", sourceFile, sourceLine);
	}
	if (DBERROR (targetSize == 0)) {
		throw IllegalArgumentException ("Invalid target buffer: buffer size is 0.", sourceFile, sourceLine);
	}
}

}

#endif // GS_IBINARYCHANNELUTILS_HPP