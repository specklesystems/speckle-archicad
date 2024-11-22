
// *****************************************************************************
//
// Declaration of HttpClientConnection interface
// 
// Module:			CommunicationClient
// Namespace:		Communication::Client::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_HTTP_HTTPCLIENTCONNECTION_HPP
#define COMMUNICATION_CLIENT_HTTP_HTTPCLIENTCONNECTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientConnection.hpp"



// --- HttpClientConnection class ----------------------------------------------

namespace Communication {
namespace Client {
namespace Http {

class COMMUNICATIONCLIENT_API HttpClientConnection : public ClientConnection {

// Construction / destruction:
protected:
			 HttpClientConnection () = default;
			 HttpClientConnection (const HttpClientConnection&) = default;
public:
	virtual ~HttpClientConnection ();

// Operator overloading:
protected:
	HttpClientConnection&		operator = (const HttpClientConnection&) = default;

// Operations:
public:
	virtual GS::UniString		GetProxyHost () const = 0;
	virtual GS::UInt32			GetProxyPort () const = 0;

};

typedef GS::Ref<HttpClientConnection, GS::AtomicCounter> HttpClientConnectionRef;

}
}
}

#endif // COMMUNICATION_CLIENT_HTTP_HTTPCLIENTCONNECTION_HPP