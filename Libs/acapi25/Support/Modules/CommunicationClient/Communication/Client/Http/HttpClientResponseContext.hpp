
// *****************************************************************************
//
// Declaration of HttpClientResponseContext interface
//
// Module:			CommunicationClient
// Namespace:		Communication::Client::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_HTTP_HTTPCLIENTRESPONSECONTEXT_HPP
#define COMMUNICATION_CLIENT_HTTP_HTTPCLIENTRESPONSECONTEXT_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientResponseContext.hpp"

	// from CommunicationCommon
#include "Communication/GenericPropertyObject.hpp"
#include "Communication/Http/StatusLine.hpp"




// --- Includes ----------------------------------------------------------------

namespace Communication {
namespace Client {
namespace Http {

using Communication::Http::ProtocolVersion;
using Communication::Http::ProtocolVersionsNotComparableException;
using Communication::Http::StatusLine;

}
}
}



// --- HttpClientResponseContext class -----------------------------------------

namespace Communication {
namespace Client {
namespace Http {

class COMMUNICATIONCLIENT_API HttpClientResponseContext : public ClientResponseContext {

// Construction / destruction:
protected:
			 HttpClientResponseContext ();
			 HttpClientResponseContext (const HttpClientResponseContext& rhs);
public:
	virtual ~HttpClientResponseContext ();

// Operator overloading:
protected:
	const HttpClientResponseContext&	operator = (const HttpClientResponseContext& rhs);

// Operations:
public:
	virtual void						SetStatusLine (const StatusLine& statusLine) = 0;
	virtual const StatusLine&			GetStatusLine () const = 0;

};

////////////////////////////////////////////////////////////////////////////////
// HttpClientResponseContext inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline HttpClientResponseContext::HttpClientResponseContext () :
	ClientResponseContext ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline HttpClientResponseContext::HttpClientResponseContext (const HttpClientResponseContext& rhs) :
	ClientResponseContext (rhs)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const HttpClientResponseContext&		HttpClientResponseContext::operator = (const HttpClientResponseContext& rhs)
{
	if (this != &rhs) {
		ClientResponseContext::operator = (rhs);
	}

	return *this;
}

}
}
}

#endif // COMMUNICATION_CLIENT_HTTP_HTTPCLIENTRESPONSECONTEXT_HPP