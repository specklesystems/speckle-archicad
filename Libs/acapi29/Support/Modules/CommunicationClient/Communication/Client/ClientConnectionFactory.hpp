
// *****************************************************************************
//
// Declaration of ClientConnectionFactory interface
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTCONNECTIONFACTORY_HPP
#define COMMUNICATION_CLIENT_CLIENTCONNECTIONFACTORY_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientConnection.hpp"
#include "Communication/Client/ClientSslContext.hpp"



// --- ClientConnectionFactory class -------------------------------------------

namespace Communication {
namespace Client {

class COMMUNICATIONCLIENT_API ClientConnectionFactory {

// Construction / destruction:
protected:
			 ClientConnectionFactory () = default;
			 ClientConnectionFactory (const ClientConnectionFactory&) = default;
public:
	virtual ~ClientConnectionFactory ();

// Operator overloading:
protected:
	ClientConnectionFactory&		operator = (const ClientConnectionFactory&) = default;

// Operations:
public:
	virtual ClientConnectionRef		CreateConnectionByUri (const GS::UniString& connectionUri, const ClientSslContextRef& sslContext = nullptr) const = 0;
	virtual bool					SupportsConnectionUri (const GS::UniString& connectionUri) const = 0;

// Static operation:
public:
	static ClientConnectionRef		CreateConnection (const GS::UniString& connectionUri, const ClientSslContextRef& sslContext = nullptr);

};

typedef GS::Ref<ClientConnectionFactory, GS::Counter> ClientConnectionFactoryRef;

}
}

#endif // COMMUNICATION_CLIENT_CLIENTCONNECTIONFACTORY_HPP