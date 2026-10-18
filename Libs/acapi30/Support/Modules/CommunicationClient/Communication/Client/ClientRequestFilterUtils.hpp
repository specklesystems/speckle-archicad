
// *****************************************************************************
//
// Declaration of ClientRequestFilter related utility functions
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTREQUESTFILTERUTILS_HPP
#define COMMUNICATION_CLIENT_CLIENTREQUESTFILTERUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientRequestFilter.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {
namespace Client {

// -----------------------------------------------------------------------------
// CheckClientRequestFilter
// -----------------------------------------------------------------------------

inline void		CheckClientRequestFilter (const ClientRequestFilterRef& requestFilter, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (requestFilter == nullptr)) {
		throw GS::IllegalArgumentException ("Invalid client request filter: filter is null.", sourceFile, sourceLine);
	}
}

}
}

#endif // COMMUNICATION_CLIENT_CLIENTREQUESTFILTERUTILS_HPP