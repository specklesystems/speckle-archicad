
// *****************************************************************************
//
// Declaration of Request class
//
// Module:			HTTP
// Namespace:		HTTP::Client
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_CLIENT_REQUEST_HPP
#define HTTP_CLIENT_REQUEST_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/MessageHeader/RequestStartLine.hpp"
#include "HTTP/MessageHeader/RequestHeaderFieldCollection.hpp"

#include "URI.hpp"


namespace HTTP {
namespace Client {

class HTTP_API Request {

private:
	HTTP::MessageHeader::RequestStartLine				m_requestStartLine;
	HTTP::MessageHeader::RequestHeaderFieldCollection	m_requestHeaderFieldCollection;

public:
	Request (HTTP::MessageHeader::Method::Id method, const GS::UniString& rawRequestUri, const HTTP::MessageHeader::HTTPVersion& version = HTTP::MessageHeader::HTTPVersion::Version11);
	Request (HTTP::MessageHeader::Method::Id method, const IO::URI::URI& requestUri, const HTTP::MessageHeader::HTTPVersion& version = HTTP::MessageHeader::HTTPVersion::Version11);
	~Request ();

	inline HTTP::MessageHeader::Method::Id							GetMethod () const;
	inline GS::UniString											GetMethodStr () const;
	inline void														SetMethod (HTTP::MessageHeader::Method::Id method);
	inline const GS::UniString&										GetRequestRawURI () const;
	inline void														SetRequestRawURI (const GS::UniString& rawRequestURI);
	IO::URI::URI													GetRequestURI () const;
	void															SetRequestURI (const IO::URI::URI& requestURI);
	inline const HTTP::MessageHeader::RequestStartLine&				GetRequestStartLine () const;
	inline HTTP::MessageHeader::RequestHeaderFieldCollection&		GetRequestHeaderFieldCollection ();
	inline const HTTP::MessageHeader::RequestHeaderFieldCollection&	GetRequestHeaderFieldCollection () const;

	void	Clear ();
	bool	IsValid ();

};

// -----------------------------------------------------------------------------
// GetMethod
// -----------------------------------------------------------------------------

inline HTTP::MessageHeader::Method::Id	Request::GetMethod () const
{
	return m_requestStartLine.GetMethod ();
}

// -----------------------------------------------------------------------------
// GetMethodStr
// -----------------------------------------------------------------------------

inline GS::UniString	Request::GetMethodStr () const
{
	return m_requestStartLine.GetMethodStr ();
}

// -----------------------------------------------------------------------------
// SetMethod
// -----------------------------------------------------------------------------

inline void	Request::SetMethod (HTTP::MessageHeader::Method::Id method)
{
	m_requestStartLine.SetMethod (method);
}

// -----------------------------------------------------------------------------
// GetRequestRawURI
// -----------------------------------------------------------------------------

inline const GS::UniString&	Request::GetRequestRawURI () const
{
	return m_requestStartLine.GetRequestURI ();
}

// -----------------------------------------------------------------------------
// SetRequestRawURI
// -----------------------------------------------------------------------------

inline void	Request::SetRequestRawURI (const GS::UniString& rawRequestURI)
{
	m_requestStartLine.SetRequestURI (rawRequestURI);
}

// -----------------------------------------------------------------------------
// GetRequestStartLine
// -----------------------------------------------------------------------------

inline const HTTP::MessageHeader::RequestStartLine& Request::GetRequestStartLine () const
{
	return m_requestStartLine;
}

// -----------------------------------------------------------------------------
// GetRequestHeaderFieldCollection
// -----------------------------------------------------------------------------

inline HTTP::MessageHeader::RequestHeaderFieldCollection& Request::GetRequestHeaderFieldCollection ()
{
	return m_requestHeaderFieldCollection;
}

// -----------------------------------------------------------------------------
// GetRequestHeaderFieldCollection
// -----------------------------------------------------------------------------

inline const HTTP::MessageHeader::RequestHeaderFieldCollection& Request::GetRequestHeaderFieldCollection () const
{
	return m_requestHeaderFieldCollection;
}

}
}

#endif