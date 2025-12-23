
// *****************************************************************************
//
// Declaration of ClientFilterSet related utility functions
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTFILTERSETUTILS_HPP
#define COMMUNICATION_CLIENT_CLIENTFILTERSETUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientFilterSet.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {
namespace Client {

// -----------------------------------------------------------------------------
// CheckClientFilterSet
// -----------------------------------------------------------------------------

inline void		CheckClientFilterSet (const ClientFilterSet& clientFilterSet, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (clientFilterSet.IsValid () == false)) {
		throw GS::IllegalArgumentException ("Invalid client filter set: set is not valid.", sourceFile, sourceLine);
	}
}

}
}

#endif // COMMUNICATION_CLIENT_CLIENTFILTERSETUTILS_HPP