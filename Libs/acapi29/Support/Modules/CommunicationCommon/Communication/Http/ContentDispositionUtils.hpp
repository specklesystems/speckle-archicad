
// *****************************************************************************
//
// Declaration of ContentDisposition related utility functions
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_CONTENTDISPOSITIONUTILS_HPP
#define COMMUNICATION_HTTP_CONTENTDISPOSITIONUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/ContentDisposition.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {
namespace Http {

// -----------------------------------------------------------------------------
// CheckContentDispositionDispositionType
// -----------------------------------------------------------------------------

inline void		CheckContentDispositionDispositionType (const GS::UniString& dispositionType, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (dispositionType.IsEmpty ())) {
		throw GS::IllegalArgumentException ("Invalid content disposition disposition type: type is empty.", sourceFile, sourceLine);
	}
}

// -----------------------------------------------------------------------------
// CheckContentDisposition
// -----------------------------------------------------------------------------

inline void		CheckContentDisposition (const ContentDisposition& contentDisposition, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (contentDisposition.IsValid () == false)) {
		throw GS::IllegalArgumentException ("Invalid content disposition: content disposition is not valid.", sourceFile, sourceLine);
	}
}

}
}

#endif // COMMUNICATION_HTTP_CONTENTDISPOSITIONUTILS_HPP