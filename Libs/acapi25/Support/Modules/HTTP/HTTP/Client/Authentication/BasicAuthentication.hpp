
// *****************************************************************************
//
// Declaration of BasicAuthentication class
//
// Module:			HTTP
// Namespace:		HTTP::Client::Authentication
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_CLIENT_AUTHENTICATION_BASICAUTHENTICATION_HPP
#define HTTP_CLIENT_AUTHENTICATION_BASICAUTHENTICATION_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/Client/Authentication/Authentication.hpp"


namespace HTTP {
namespace Client {
namespace Authentication {

class HTTP_API BasicAuthentication: public Authentication
{

private:
	GS::UniString		m_username;
	GS::UniString		m_password;

public:
	BasicAuthentication (const GS::UniString& username, const GS::UniString& password, bool proxyAuthentication = false);
	virtual ~BasicAuthentication ();

	void 					SetUserName (const GS::UniString& username);
	const GS::UniString&	GetUserName () const;
	void					SetPassword (const GS::UniString& password);
	const GS::UniString&	GetPassword () const;

	virtual void	HandleRequestHeaderFieldCollection (HTTP::MessageHeader::RequestHeaderFieldCollection& requestHeaderFields) override;
	virtual void	HandleResponseHeaderFieldCollection (HTTP::MessageHeader::ResponseHeaderFieldCollection& responseHeaderFields) override;
	virtual bool	CanResendRequest () override;

};

// -----------------------------------------------------------------------------
// SetUserName
// -----------------------------------------------------------------------------

inline void BasicAuthentication::SetUserName (const GS::UniString& username)
{
	m_username = username;
}

// -----------------------------------------------------------------------------
// GetUserName
// -----------------------------------------------------------------------------

inline const GS::UniString& BasicAuthentication::GetUserName () const
{
	return m_username;
}

// -----------------------------------------------------------------------------
// SetPassword
// -----------------------------------------------------------------------------

inline void BasicAuthentication::SetPassword (const GS::UniString& password)
{
	m_password = password;
}

// -----------------------------------------------------------------------------
// GetPassword
// -----------------------------------------------------------------------------

inline const GS::UniString& BasicAuthentication::GetPassword () const
{
	return m_password;
}

}
}
}

#endif