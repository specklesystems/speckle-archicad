
// *****************************************************************************
//
// Declaration of ClientSslContextFactory class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTSSLCONTEXTFACTORY_HPP
#define COMMUNICATION_CLIENT_CLIENTSSLCONTEXTFACTORY_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientSslContext.hpp"



// --- ClientSslContextFactory class -------------------------------------------

namespace Communication {
namespace Client {

class COMMUNICATIONCLIENT_API ClientSslContextFactory {

// Static operations:
public:
	static ClientSslContextRef		CreateSslContext ();

};


}
}

#endif // COMMUNICATION_CLIENT_CLIENTSSLCONTEXTFACTORY_HPP