
// *****************************************************************************
//
// Declaration of HttpClientResponse related utility functions
//
// Module:			CommunicationClient
// Namespace:		Communication::Client::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_HTTP_HTTPCLIENTRESPONSEUTILS_HPP
#define COMMUNICATION_CLIENT_HTTP_HTTPCLIENTRESPONSEUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/Http/HttpClientResponse.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {
namespace Client {
namespace Http {

// -----------------------------------------------------------------------------
// CheckHttpClientResponse
// -----------------------------------------------------------------------------

inline void		CheckHttpClientResponse (const HttpClientResponseRef& response, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (response == nullptr)) {
		throw GS::IllegalArgumentException ("Invalid http response: response is null.", sourceFile, sourceLine);
	}
}

}
}
}

#endif // COMMUNICATION_CLIENT_HTTP_HTTPCLIENTRESPONSEUTILS_HPP