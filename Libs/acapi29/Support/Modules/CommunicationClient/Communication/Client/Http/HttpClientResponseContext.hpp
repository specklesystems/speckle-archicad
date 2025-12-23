
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
			 HttpClientResponseContext () = default;
			 HttpClientResponseContext (const HttpClientResponseContext&) = default;
public:
	virtual ~HttpClientResponseContext ();

// Operator overloading:
protected:
	HttpClientResponseContext&	operator = (const HttpClientResponseContext&) = default;

// Operations:
public:
	virtual void				SetStatusLine (const StatusLine& statusLine) = 0;
	virtual const StatusLine&	GetStatusLine () const = 0;

};

}
}
}

#endif // COMMUNICATION_CLIENT_HTTP_HTTPCLIENTRESPONSECONTEXT_HPP