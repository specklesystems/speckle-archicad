
// *****************************************************************************
//
// Declaration of HttpClientRequestContext interface
//
// Module:			CommunicationClient
// Namespace:		Communication::Client::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_HTTP_HTTPCLIENTREQUESTCONTEXT_HPP
#define COMMUNICATION_CLIENT_HTTP_HTTPCLIENTREQUESTCONTEXT_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientRequestContext.hpp"

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



// --- HttpClientRequestContext class ------------------------------------------

namespace Communication {
namespace Client {
namespace Http {

class COMMUNICATIONCLIENT_API HttpClientRequestContext : public ClientRequestContext {

// Construction / destruction:
protected:
			 HttpClientRequestContext ();
			 HttpClientRequestContext (const HttpClientRequestContext& rhs);
public:
	virtual ~HttpClientRequestContext ();

// Operator overloading:
protected:
	const HttpClientRequestContext&		operator = (const HttpClientRequestContext& rhs);

// Operations:
public:
	virtual void						SetRequestLine (const RequestLine& requestLine) = 0;
	virtual const RequestLine&			GetRequestLine () const = 0;

};

////////////////////////////////////////////////////////////////////////////////
// HttpClientRequestContext inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline HttpClientRequestContext::HttpClientRequestContext () :
	ClientRequestContext ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline HttpClientRequestContext::HttpClientRequestContext (const HttpClientRequestContext& rhs) :
	ClientRequestContext (rhs)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const HttpClientRequestContext&	HttpClientRequestContext::operator = (const HttpClientRequestContext& rhs)
{
	if (this != &rhs) {
		ClientRequestContext::operator = (rhs);
	}

	return *this;
}

}
}
}

#endif // COMMUNICATION_CLIENT_HTTP_HTTPCLIENTREQUESTCONTEXT_HPP