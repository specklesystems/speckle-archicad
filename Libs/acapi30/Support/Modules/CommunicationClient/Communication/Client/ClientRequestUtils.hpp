
// *****************************************************************************
//
// Declaration of ClientRequest related utility functions
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTREQUESTUTILS_HPP
#define COMMUNICATION_CLIENT_CLIENTREQUESTUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientRequest.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {
namespace Client {

// -----------------------------------------------------------------------------
// CheckClientRequest
// -----------------------------------------------------------------------------

inline void		CheckClientRequest (const ClientRequestRef& request, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (request == nullptr)) {
		throw GS::IllegalArgumentException ("Invalid request: request is null.", sourceFile, sourceLine);
	}
}

}
}

#endif // COMMUNICATION_CLIENT_CLIENTREQUESTUTILS_HPP