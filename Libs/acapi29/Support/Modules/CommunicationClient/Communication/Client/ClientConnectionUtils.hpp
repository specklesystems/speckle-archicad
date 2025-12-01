
// *****************************************************************************
//
// Declaration of ClientConnection related utility functions
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTCONNECTIONUTILS_HPP
#define COMMUNICATION_CLIENT_CLIENTCONNECTIONUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientConnection.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {
namespace Client {

// -----------------------------------------------------------------------------
// CheckClientConnectionUri
// -----------------------------------------------------------------------------

inline void		CheckClientConnectionUri (const GS::UniString& connectionUri, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (connectionUri.IsEmpty ())) {
		throw GS::IllegalArgumentException ("Invalid connection uri: uri is empty.", sourceFile, sourceLine);
	}
}

// -----------------------------------------------------------------------------
// CheckClientConnection
// -----------------------------------------------------------------------------

inline void		CheckClientConnection (const ClientConnectionRef& connection, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (connection == nullptr)) {
		throw GS::IllegalArgumentException ("Invalid connection: connection is null.", sourceFile, sourceLine);
	}
}

}
}

#endif // COMMUNICATION_CLIENT_CLIENTCONNECTIONUTILS_HPP