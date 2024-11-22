
// *****************************************************************************
//
// Declaration of ClientResponse related utility functions
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTRESPONSEUTILS_HPP
#define COMMUNICATION_CLIENT_CLIENTRESPONSEUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientResponse.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {
namespace Client {

// -----------------------------------------------------------------------------
// CheckClientResponse
// -----------------------------------------------------------------------------

inline void		CheckClientResponse (const ClientResponseRef& response, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (response == nullptr)) {
		throw GS::IllegalArgumentException ("Invalid response: response is null.", sourceFile, sourceLine);
	}
}

}
}

#endif // COMMUNICATION_CLIENT_CLIENTRESPONSEUTILS_HPP