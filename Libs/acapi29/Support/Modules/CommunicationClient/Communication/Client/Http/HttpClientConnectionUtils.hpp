
// *****************************************************************************
//
// Declaration of HttpClientConnection related utility functions
//
// Module:			CommunicationClient
// Namespace:		Communication::Client::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_HTTP_HTTPCLIENTCONNECTIONUTILS_HPP
#define COMMUNICATION_CLIENT_HTTP_HTTPCLIENTCONNECTIONUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/Http/HttpClientConnection.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {
namespace Client {
namespace Http {

// -----------------------------------------------------------------------------
// CheckHttpClientConnection
// -----------------------------------------------------------------------------

inline void		CheckHttpClientConnection (const HttpClientConnectionRef& connection, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (connection == nullptr)) {
		throw GS::IllegalArgumentException ("Invalid http connection: connection is null", sourceFile, sourceLine);
	}
}

}
}
}

#endif // COMMUNICATION_CLIENT_HTTP_HTTPCLIENTCONNECTIONUTILS_HPP