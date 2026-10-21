
// *****************************************************************************
//
// Declaration of Authentication class
//
// Module:			HTTP
// Namespace:		HTTP::Client::Authentication
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_CLIENT_AUTHENTICATION_AUTHENTICATION_HPP
#define HTTP_CLIENT_AUTHENTICATION_AUTHENTICATION_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/HTTPExport.hpp"

#include "HTTP/MessageHeader/RequestHeaderFieldCollection.hpp"
#include "HTTP/MessageHeader/ResponseHeaderFieldCollection.hpp"

#include "Ref.hpp"


namespace HTTP {
namespace Client {
namespace Authentication {

class HTTP_API Authentication
{

protected:
	bool			m_proxyAuthentication;

public:
	Authentication (bool proxyAuthentication = false);
	virtual ~Authentication ();

	virtual void	HandleRequestHeaderFieldCollection (HTTP::MessageHeader::RequestHeaderFieldCollection& requestHeaderFields) = 0;
	virtual void	HandleResponseHeaderFieldCollection (HTTP::MessageHeader::ResponseHeaderFieldCollection& responseHeaderFields) = 0;
	virtual bool	CanResendRequest () = 0;

	void			SetProxyAuthentication (bool proxyAuthentication);
	bool			GetProxyAuthentication () const;

};

typedef GS::Ref<Authentication, GS::AtomicCounter> AuthenticationRef;

// -----------------------------------------------------------------------------
// SetProxyAuthentication
// -----------------------------------------------------------------------------

inline void	Authentication::SetProxyAuthentication (bool proxyAuthentication)
{
	m_proxyAuthentication = proxyAuthentication;
}

// -----------------------------------------------------------------------------
// GetProxyAuthentication
// -----------------------------------------------------------------------------

inline bool	Authentication::GetProxyAuthentication () const
{
	return m_proxyAuthentication;
}

}
}
}

#endif