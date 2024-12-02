
// *****************************************************************************
//
// Declaration of HttpClientResponse interface
//
// Module:			CommunicationClient
// Namespace:		Communication::Client::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_HTTP_HTTPCLIENTRESPONSE_HPP
#define COMMUNICATION_CLIENT_HTTP_HTTPCLIENTRESPONSE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientResponse.hpp"

	// from CommunicationCommon
#include "Communication/Http/StatusLine.hpp"



// --- Imports -----------------------------------------------------------------

namespace Communication {
namespace Client {
namespace Http {

using Communication::Http::ProtocolVersion;
using Communication::Http::ProtocolVersionsNotComparableException;
using Communication::Http::StatusLine;

}
}
}



// --- HttpClientResponse class ------------------------------------------------

namespace Communication {
namespace Client {
namespace Http {

class COMMUNICATIONCLIENT_API HttpClientResponse : public ClientResponse {

// Construction / destruction:
protected:
			 HttpClientResponse ();
			 HttpClientResponse (const HttpClientResponse& rhs);
public:
	virtual ~HttpClientResponse ();

// Operator overloading:
protected:
	const HttpClientResponse&	operator = (const HttpClientResponse& rhs);

// Operations:
public:
	virtual void				SetStatusLine (const StatusLine& statusLine) = 0;
	virtual const StatusLine&	GetStatusLine () const = 0;

};

typedef GS::Ref<HttpClientResponse, GS::Counter> HttpClientResponseRef;


////////////////////////////////////////////////////////////////////////////////
// HttpClientResponse inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline HttpClientResponse::HttpClientResponse () :
	ClientResponse ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline HttpClientResponse::HttpClientResponse (const HttpClientResponse& rhs) :
	ClientResponse (rhs)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const HttpClientResponse&	HttpClientResponse::operator = (const HttpClientResponse& rhs)
{
	if (this != &rhs) {
		ClientResponse::operator = (rhs);
	}

	return *this;
}

}
}
}

#endif // COMMUNICATION_CLIENT_HTTP_HTTPCLIENTRESPONSE_HPP