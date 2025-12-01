
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
			 HttpClientResponse () = default;
			 HttpClientResponse (const HttpClientResponse&) = default;
public:
	virtual ~HttpClientResponse ();

// Operator overloading:
protected:
	HttpClientResponse&			operator = (const HttpClientResponse&) = default;

// Operations:
public:
	virtual void				SetStatusLine (const StatusLine& statusLine) = 0;
	virtual const StatusLine&	GetStatusLine () const = 0;

};

typedef GS::Ref<HttpClientResponse, GS::Counter> HttpClientResponseRef;

}
}
}

#endif // COMMUNICATION_CLIENT_HTTP_HTTPCLIENTRESPONSE_HPP