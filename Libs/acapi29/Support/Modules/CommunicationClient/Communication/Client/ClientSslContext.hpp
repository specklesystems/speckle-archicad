
// *****************************************************************************
//
// Declaration of ClientSslContext class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTSSLCONTEXT_HPP
#define COMMUNICATION_CLIENT_CLIENTSSLCONTEXT_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/CommunicationClientExport.hpp"

	// from CommunicationCommon
#include "Communication/SslContext.hpp"



// --- ClientSslContext class --------------------------------------------------

namespace Communication {
namespace Client {

class COMMUNICATIONCLIENT_API ClientSslVerificaiton {

public:
	enum Verify {
		None = 0x01,
		Peer = 0x02
	};
};


class COMMUNICATIONCLIENT_API ClientSslContext : public SslContext {

// Data members:
private:
	ClientSslVerificaiton::Verify		m_verify;

// Construction / destruction:
protected:
			 ClientSslContext ();
public:
	virtual ~ClientSslContext ();

// Operations:
public:
	ClientSslVerificaiton::Verify		GetVerification () const;
	void 								SetVerification (ClientSslVerificaiton::Verify verify);

};

typedef GS::Ref<ClientSslContext, GS::Counter> ClientSslContextRef;

}
}

#endif // COMMUNICATION_CLIENT_CLIENTSSLCONTEXT_HPP