
// *****************************************************************************
//
// Declaration of Response class
//
// Module:			HTTP
// Namespace:		HTTP::Client
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_CLIENT_RESPONSE_HPP
#define HTTP_CLIENT_RESPONSE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/MessageHeader/ResponseStartLine.hpp"
#include "HTTP/MessageHeader/ResponseHeaderFieldCollection.hpp"


namespace HTTP {
namespace Client {

class HTTP_API Response
{

private:
	HTTP::MessageHeader::ResponseStartLine				m_responseStartLine;
	HTTP::MessageHeader::ResponseHeaderFieldCollection	m_requestHeaderFieldCollection;

public:
	Response ();
	~Response ();

	MessageHeader::HTTPVersion									GetVersion () const;
	void														SetVersion (const MessageHeader::HTTPVersion& httpVersion);
	MessageHeader::StatusCode::Id								GetStatusCode () const;
	void														SetStatusCode (MessageHeader::StatusCode::Id statusCode);
	GS::UniString												GetReason () const;
	void														SetReason (const GS::UniString& reason);
	HTTP::MessageHeader::ResponseStartLine&						GetRequestStartLine ();
	HTTP::MessageHeader::ResponseHeaderFieldCollection&			GetResponseHeaderFieldCollection ();
	const HTTP::MessageHeader::ResponseHeaderFieldCollection&	GetResponseHeaderFieldCollection () const;

	void	Clear ();

};

// -----------------------------------------------------------------------------
// GetVersion
// -----------------------------------------------------------------------------

inline MessageHeader::HTTPVersion Response::GetVersion () const
{
	return m_responseStartLine.GetHTTPVersion ();
}

// -----------------------------------------------------------------------------
// SetVersion
// -----------------------------------------------------------------------------

inline void  Response::SetVersion (const MessageHeader::HTTPVersion& httpVersion)
{
	m_responseStartLine.SetHTTPVersion (httpVersion);
}

// -----------------------------------------------------------------------------
// GetStatus
// -----------------------------------------------------------------------------

inline MessageHeader::StatusCode::Id Response::GetStatusCode () const
{
	return m_responseStartLine.GetStatusCode ();
}

// -----------------------------------------------------------------------------
// SetStatus
// -----------------------------------------------------------------------------

inline void Response::SetStatusCode	(MessageHeader::StatusCode::Id statusCode)
{
	m_responseStartLine.SetStatusCode (statusCode);
}

// -----------------------------------------------------------------------------
// GetReason
// -----------------------------------------------------------------------------

inline GS::UniString Response::GetReason () const
{
	return m_responseStartLine.GetReason (true);
}

// -----------------------------------------------------------------------------
// SetReason
// -----------------------------------------------------------------------------

inline void Response::SetReason (const GS::UniString& reason)
{
	m_responseStartLine.SetReason (reason);
}

// -----------------------------------------------------------------------------
// GetRequestStartLine
// -----------------------------------------------------------------------------

inline HTTP::MessageHeader::ResponseStartLine&	Response::GetRequestStartLine ()
{
	return m_responseStartLine;
}

// -----------------------------------------------------------------------------
// GetResponseHeaderFieldCollection
// -----------------------------------------------------------------------------

inline HTTP::MessageHeader::ResponseHeaderFieldCollection& Response::GetResponseHeaderFieldCollection ()
{
	return m_requestHeaderFieldCollection;
}

// -----------------------------------------------------------------------------
// GetResponseHeaderFieldCollection
// -----------------------------------------------------------------------------

inline const HTTP::MessageHeader::ResponseHeaderFieldCollection& Response::GetResponseHeaderFieldCollection () const
{
	return m_requestHeaderFieldCollection;
}

}
}

#endif