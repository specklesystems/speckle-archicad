
// *****************************************************************************
//
// Declaration of RequestLine related utility functions
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_REQUESTLINEUTILS_HPP
#define COMMUNICATION_HTTP_REQUESTLINEUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/RequestLine.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {
namespace Http {

// -----------------------------------------------------------------------------
// CheckRequestMethod
// -----------------------------------------------------------------------------

inline void		CheckRequestMethod (const GS::UniString& requestMethod, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (requestMethod.IsEmpty ())) {
		throw GS::IllegalArgumentException ("Invalid request method: method is empty.", sourceFile, sourceLine);
	}
}

// -----------------------------------------------------------------------------
// CheckRequestLine
// -----------------------------------------------------------------------------

inline void		CheckRequestLine (const RequestLine& requestLine, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (requestLine.IsValid () == false)) {
		throw GS::IllegalArgumentException ("Invalid request line: request line is not valid.", sourceFile, sourceLine);
	}
}

// -----------------------------------------------------------------------------
// CheckRequestUri
// -----------------------------------------------------------------------------

inline void		CheckRequestUri (const GS::UniString& requestUri, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (requestUri.IsEmpty ())) {
		throw GS::IllegalArgumentException ("Invalid request uri: uri is empty.", sourceFile, sourceLine);
	}
}

}
}

#endif // COMMUNICATION_HTTP_REQUESTLINEUTILS_HPP