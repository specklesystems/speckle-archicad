
// *****************************************************************************
//
// Declaration of RequestStartLine class
//
// Module:			HTTP
// Namespace:		HTTP::MessageHeader
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_MESSAGEHEADER_REQUESTSTARTLINE_HPP
#define HTTP_MESSAGEHEADER_REQUESTSTARTLINE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/HTTPExport.hpp"
#include "HTTP/MessageHeader/StartLine.hpp"
#include "HTTP/MessageHeader/Method.hpp"

#include "UniString.hpp"


namespace HTTP {
namespace MessageHeader {


class HTTP_API RequestStartLine: public StartLine {

private:
	Method::Id					m_method;
	GS::UniString				m_requestURI;

public:
	RequestStartLine ();
	RequestStartLine (Method::Id method, const GS::UniString requestUri, const HTTPVersion& version);
	virtual ~RequestStartLine ();

	inline Method::Id			GetMethod () const;
	inline GS::UniString		GetMethodStr () const;
	inline void					SetMethod (Method::Id method);

	inline const GS::UniString&	GetRequestURI () const;
	inline void					SetRequestURI (const GS::UniString& requestURI);
	inline void					AppendRequestURI (const GS::UniString& requestURI);

	inline GS::UniString		ToString () const;
	inline void					Clear ();
	bool						IsValid ();

};


// -----------------------------------------------------------------------------
// GetMethod
// -----------------------------------------------------------------------------

inline Method::Id RequestStartLine::GetMethod () const
{
	return m_method;
}


// -----------------------------------------------------------------------------
// GetMethodStr
// -----------------------------------------------------------------------------

inline GS::UniString RequestStartLine::GetMethodStr () const
{
	return Method::ToString (m_method);
}


// -----------------------------------------------------------------------------
// SetMethod
// -----------------------------------------------------------------------------

inline void RequestStartLine::SetMethod (Method::Id method)
{
	this->m_method = method;
}


// -----------------------------------------------------------------------------
// GetRequestURI
// -----------------------------------------------------------------------------

inline const GS::UniString& RequestStartLine::GetRequestURI () const
{
	return m_requestURI;
}


// -----------------------------------------------------------------------------
// SetRequestURI
// -----------------------------------------------------------------------------

inline void RequestStartLine::SetRequestURI (const GS::UniString& requestURI)
{
	this->m_requestURI = requestURI;
}


// -----------------------------------------------------------------------------
// AppendRequestURI
// -----------------------------------------------------------------------------

inline void RequestStartLine::AppendRequestURI (const GS::UniString& requestURI)
{
	this->m_requestURI += requestURI;
}


// -----------------------------------------------------------------------------
// ToString
// -----------------------------------------------------------------------------

inline GS::UniString RequestStartLine::ToString () const
{
	return GetMethodStr () + " " +  
		   GetRequestURI () + " " + 
		   "HTTP/" + GS::UniString::Printf ("%d", GetHTTPVersion ().majorVersion) + "." + GS::UniString::Printf ("%d", GetHTTPVersion ().minorVersion);
}


// -----------------------------------------------------------------------------
// Clear
// -----------------------------------------------------------------------------

inline void RequestStartLine::Clear ()
{	
	SetHTTPVersion (0, 0);
	SetMethod (Method::Unknown);
	SetRequestURI ("");
}

}
}

#endif
