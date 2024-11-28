
// *****************************************************************************
//
// Declaration of ContentType related utility functions
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CONTENTTYPEUTILS_HPP
#define COMMUNICATION_CONTENTTYPEUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/ContentType.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {

// -----------------------------------------------------------------------------
// CheckContentType
// -----------------------------------------------------------------------------

inline void		CheckContentType (const ContentType& contentType, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (contentType.IsValid () == false)) {
		throw GS::IllegalArgumentException ("Invalid content type: type is not valid.", sourceFile, sourceLine);
	}
}
// -----------------------------------------------------------------------------
// CheckMediaType
// -----------------------------------------------------------------------------

inline void		CheckMediaType (const GS::UniString& mediaType, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (mediaType.IsEmpty ())) {
		throw GS::IllegalArgumentException ("Invalid media type: type is empty.", sourceFile, sourceLine);
	}
}

// -----------------------------------------------------------------------------
// CheckCharset
// -----------------------------------------------------------------------------

inline void		CheckCharset (const GS::UniString& charset, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (charset.IsEmpty ())) {
		throw GS::IllegalArgumentException ("Invalid charset: charset is empty.", sourceFile, sourceLine);
	}
}


}

#endif // COMMUNICATION_CONTENTTYPEUTILS_HPP