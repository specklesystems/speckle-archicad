
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
			 HttpClientRequestContext () = default;
			 HttpClientRequestContext (const HttpClientRequestContext&) = default;
public:
	virtual ~HttpClientRequestContext ();

// Operator overloading:
protected:
	HttpClientRequestContext&	operator = (const HttpClientRequestContext&) = default;

// Operations:
public:
	virtual void				SetRequestLine (const RequestLine& requestLine) = 0;
	virtual const RequestLine&	GetRequestLine () const = 0;

};

}
}
}

#endif // COMMUNICATION_CLIENT_HTTP_HTTPCLIENTREQUESTCONTEXT_HPP