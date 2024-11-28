
// *****************************************************************************
//
// Declaration of ResponseStartLine class
//
// Module:			HTTP
// Namespace:		HTTP::MessageHeader
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_MESSAGEHEADER_RESPONSESTARTLINE_HPP
#define HTTP_MESSAGEHEADER_RESPONSESTARTLINE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/HTTPExport.hpp"
#include "HTTP/MessageHeader/StartLine.hpp"
#include "HTTP/MessageHeader/StatusCode.hpp"

#include "UniString.hpp"


namespace HTTP {
namespace MessageHeader {

class HTTP_API ResponseStartLine: public StartLine {

private:
	StatusCode::Id				m_statusCode;
	GS::UniString				m_reason;

public:
	ResponseStartLine ();
	ResponseStartLine (const HTTPVersion& version, StatusCode::Id status, const GS::UniString& reason);
	ResponseStartLine (const HTTPVersion& version, StatusCode::Id status);

	virtual ~ResponseStartLine	();

	inline StatusCode::Id		GetStatusCode () const;
	inline void					SetStatusCode (StatusCode::Id statusCode);
	
	inline GS::UniString		GetReason (bool getDefault = false) const;
	inline void					SetReason (const GS::UniString& reason);

	inline GS::UniString		ToString () const;
	inline void					Clear ();	

};


// -----------------------------------------------------------------------------
// GetStatusCode
// -----------------------------------------------------------------------------

inline StatusCode::Id ResponseStartLine::GetStatusCode () const
{
	return m_statusCode;
}


// -----------------------------------------------------------------------------
// SetStatusCode
// -----------------------------------------------------------------------------

inline void ResponseStartLine::SetStatusCode (StatusCode::Id statusCode)
{
	m_statusCode = statusCode;
}


// -----------------------------------------------------------------------------
// GetReason
// -----------------------------------------------------------------------------

inline GS::UniString ResponseStartLine::GetReason (bool getDefault /*= false*/) const
{
	if (!m_reason.IsEmpty ()) {
		return m_reason;
	}

	if (getDefault) {
		return StatusCode::ToString (m_statusCode);
	}

	return "";
}


// -----------------------------------------------------------------------------
// SetReason
// -----------------------------------------------------------------------------

inline void ResponseStartLine::SetReason (const GS::UniString& reason)
{
	m_reason = reason;
}


// -----------------------------------------------------------------------------
// ToString
// -----------------------------------------------------------------------------

inline GS::UniString ResponseStartLine::ToString () const
{
	return "HTTP/" + GS::UniString::Printf ("%d", GetHTTPVersion ().majorVersion) + "." + GS::UniString::Printf ("%d", GetHTTPVersion ().minorVersion) + " " +  
		   GS::UniString::Printf ("%d", GetStatusCode ()) + " " + 
		   GetReason (true);
}


// -----------------------------------------------------------------------------
// Clear
// -----------------------------------------------------------------------------

inline void ResponseStartLine::Clear ()
{
	SetHTTPVersion (0, 0);
	SetStatusCode (StatusCode::Unknown);
	SetReason ("");
}


}
}

#endif
