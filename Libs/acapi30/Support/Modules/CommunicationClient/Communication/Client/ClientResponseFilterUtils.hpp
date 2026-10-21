
// *****************************************************************************
//
// Declaration of ClientResponseFilter related utility functions
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTRESPONSEFILTERUTILS_HPP
#define COMMUNICATION_CLIENT_CLIENTRESPONSEFILTERUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientResponseFilter.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {
namespace Client {

// -----------------------------------------------------------------------------
// CheckClientResponseFilter
// -----------------------------------------------------------------------------

inline void		CheckClientResponseFilter (const ClientResponseFilterRef& responseFilter, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (responseFilter == nullptr)) {
		throw GS::IllegalArgumentException ("Invalid client response filter: filter is null.", sourceFile, sourceLine);
	}
}

}
}

#endif // COMMUNICATION_CLIENT_CLIENTRESPONSEFILTERUTILS_HPP