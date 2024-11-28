
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
			 HttpClientConnection ();
			 HttpClientConnection (const HttpClientConnection& rhs);
public:
	virtual ~HttpClientConnection ();

// Operator overloading:
protected:
	HttpClientConnection&		operator = (const HttpClientConnection& rhs);

// Operations:
public:
	virtual GS::UniString		GetProxyHost () const = 0;
	virtual GS::UInt32			GetProxyPort () const = 0;

};

typedef GS::Ref<HttpClientConnection, GS::AtomicCounter> HttpClientConnectionRef;

////////////////////////////////////////////////////////////////////////////////
// HttpClientConnection inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline HttpClientConnection::HttpClientConnection () :
	ClientConnection ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline HttpClientConnection::HttpClientConnection (const HttpClientConnection& rhs) :
	ClientConnection (rhs)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline HttpClientConnection&	HttpClientConnection::operator = (const HttpClientConnection& rhs)
{
	if (this != &rhs) {
		ClientConnection::operator = (rhs);
	}

	return *this;
}

}
}
}

#endif // COMMUNICATION_CLIENT_HTTP_HTTPCLIENTCONNECTION_HPP