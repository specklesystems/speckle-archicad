
// *****************************************************************************
//
// Declaration of HttpClientRequest interface
//
// Module:			CommunicationClient
// Namespace:		Communication::Client::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_HTTP_HTTPCLIENTREQUEST_HPP
#define COMMUNICATION_CLIENT_HTTP_HTTPCLIENTREQUEST_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientRequest.hpp"

	// from CommunicationCommon
#include "Communication/Http/RequestLine.hpp"



// --- Imports -----------------------------------------------------------------

namespace Communication {
namespace Client {
namespace Http {

using Communication::Http::ProtocolVersion;
using Communication::Http::ProtocolVersionsNotComparableException;
using Communication::Http::RequestLine;

}
}
}



// --- HttpClientRequest class -------------------------------------------------

namespace Communication {
namespace Client {
namespace Http {

class COMMUNICATIONCLIENT_API HttpClientRequest : public ClientRequest {

// Construction / destruction:
protected:
			 HttpClientRequest ();
			 HttpClientRequest (const HttpClientRequest& rhs);
public:
	virtual ~HttpClientRequest ();

// Operator overloading:
protected:
	const HttpClientRequest&	operator = (const HttpClientRequest& rhs);

// Operations:
public:
	virtual void				SetRequestLine (const RequestLine& requestLine) = 0;
	virtual const RequestLine&	GetRequestLine () const = 0;

};

typedef GS::Ref<HttpClientRequest, GS::Counter> HttpClientRequestRef;


////////////////////////////////////////////////////////////////////////////////
// HttpClientRequest inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline HttpClientRequest::HttpClientRequest () :
	ClientRequest ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline HttpClientRequest::HttpClientRequest (const HttpClientRequest& rhs) :
	ClientRequest (rhs)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const HttpClientRequest&		HttpClientRequest::operator = (const HttpClientRequest& rhs)
{
	if (this != &rhs) {
		ClientRequest::operator = (rhs);
	}

	return *this;
}

}
}
}

#endif // COMMUNICATION_CLIENT_HTTP_HTTPCLIENTREQUEST_HPP