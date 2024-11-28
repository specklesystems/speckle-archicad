
// *****************************************************************************
//
// Declaration of ClientSslSession class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTSSLSESSION_HPP
#define COMMUNICATION_CLIENT_CLIENTSSLSESSION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/CommunicationClientExport.hpp"

	// from CommunicationCommon
#include "Communication/SslSession.hpp"



// --- ClientSslSession class --------------------------------------------------

namespace Communication {
namespace Client {

class COMMUNICATIONCLIENT_API ClientSslSession : public SslSession {

// Construction / destruction:
public:
			 ClientSslSession ();
	virtual ~ClientSslSession ();

};

typedef GS::Ref<ClientSslSession, GS::Counter> ClientSslSessionRef;

}
}

#endif // COMMUNICATION_CLIENT_CLIENTSSLSESSION_HPP