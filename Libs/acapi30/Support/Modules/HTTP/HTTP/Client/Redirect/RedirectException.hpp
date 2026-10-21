// *****************************************************************************
//
// Declaration of RedirectException class
//
// Module:			HTTP
// Namespace:		HTTP::Client::Redirect
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_CLIENT_REDIRECT_REDIRECTEXCEPTION_HPP
#define HTTP_CLIENT_REDIRECT_REDIRECTEXCEPTION_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "HTTP/Client/Request.hpp"
#include "HTTP/Client/Response.hpp"
#include "HTTP/HTTPException.hpp"


namespace HTTP {
namespace Client {
namespace Redirect {


class HTTP_API RedirectException : public HTTPException {

private:
	GS::Ref<Request>		m_request;
	GS::Ref<Response>		m_response;

public:
	RedirectException	(const GS::UniString& errorMessage, const Request* request, const Response* response, const char* sourceFile, GS::UInt32 sourceLine, const GS::Exception& cause = GS::NoCauseException);
	virtual ~RedirectException	();

public:
	GS::Ref<Request>		GetRequest();
	GS::Ref<Response>		GetResponse ();

public:
	virtual GS::Exception*	Clone () const override;

};

// -----------------------------------------------------------------------------
// GetRequest
// -----------------------------------------------------------------------------

inline GS::Ref<Request>	RedirectException::GetRequest ()
{
	return m_request;
}

// -----------------------------------------------------------------------------
// GetResponse
// -----------------------------------------------------------------------------

inline GS::Ref<Response>	RedirectException::GetResponse ()
{
	return m_response;
}

}
}
}

#endif