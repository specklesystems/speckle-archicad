
// *****************************************************************************
//
// Declaration of ByteContentRange related utility functions
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_BYTECONTENTRANGEUTILS_HPP
#define COMMUNICATION_HTTP_BYTECONTENTRANGEUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/ByteContentRange.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {
namespace Http {

// -----------------------------------------------------------------------------
// CheckByteContentRange
// -----------------------------------------------------------------------------

inline void		CheckByteContentRange (const ByteContentRange& byteContentRange, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (byteContentRange.IsValid () == false)) {
		throw GS::IllegalArgumentException ("Invalid byte content range: range is not valid.", sourceFile, sourceLine);
	}
}

}
}

#endif // COMMUNICATION_HTTP_BYTECONTENTRANGEUTILS_HPP