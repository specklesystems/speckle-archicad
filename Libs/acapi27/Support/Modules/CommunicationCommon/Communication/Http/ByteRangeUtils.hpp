
// *****************************************************************************
//
// Declaration of ByteRange related utility functions
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_BYTERANGEUTILS_HPP
#define COMMUNICATION_HTTP_BYTERANGEUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/ByteRange.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {
namespace Http {

// -----------------------------------------------------------------------------
// CheckByteRange
// -----------------------------------------------------------------------------

inline void		CheckByteRange (const ByteRange& byteRange, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (byteRange.IsValid () == false)) {
		throw GS::IllegalArgumentException ("Invalid byte range: range is not valid.", sourceFile, sourceLine);
	}
}

}
}

#endif // COMMUNICATION_HTTP_BYTERANGEUTILS_HPP