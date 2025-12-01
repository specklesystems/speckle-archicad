
// *****************************************************************************
//
// Declaration of HttpClientRequest related utility functions
//
// Module:			CommunicationClient
// Namespace:		Communication::Client::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_HTTP_HTTPCLIENTREQUESTUTILS_HPP
#define COMMUNICATION_CLIENT_HTTP_HTTPCLIENTREQUESTUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/Http/HttpClientRequest.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {
namespace Client {
namespace Http {

// -----------------------------------------------------------------------------
// CheckHttpClientRequest
// -----------------------------------------------------------------------------

inline void		CheckHttpClientRequest (const HttpClientRequestRef& request, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (request == nullptr)) {
		throw GS::IllegalArgumentException ("Invalid http request: request is null.", sourceFile, sourceLine);
	}
}

}
}
}

#endif // COMMUNICATION_CLIENT_HTTP_HTTPCLIENTREQUESTUTILS_HPP