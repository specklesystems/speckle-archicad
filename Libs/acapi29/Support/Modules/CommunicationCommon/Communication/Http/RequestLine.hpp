
// *****************************************************************************
//
// Declaration of RequestLine class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_REQUESTLINE_HPP
#define COMMUNICATION_HTTP_REQUESTLINE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/ProtocolVersion.hpp"



// --- RequestLine class -------------------------------------------------------

namespace Communication {
namespace Http {

class COMMUNICATIONCOMMON_API RequestLine {

// Data members:
private:
	ProtocolVersion			m_protocolVersion;
	GS::UniString			m_method;
	GS::UniString			m_uri;

// Construction / destruction:
public:
	RequestLine ();
	RequestLine (const ProtocolVersion& protocolVersion, const GS::UniString& method, const GS::UniString& uri);

// Operator overloading:
public:
	bool					operator == (const RequestLine& rhs) const;
	bool					operator != (const RequestLine& rhs) const;

// Operations:
public:
	const ProtocolVersion&	GetProtocolVersion () const;
	const GS::UniString&	GetMethod () const;
	const GS::UniString&	GetUri () const;

	GS::UniString			ToString () const;

	bool					IsValid () const;

};

////////////////////////////////////////////////////////////////////////////////
// RequestLine inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline RequestLine::RequestLine () :
	m_protocolVersion (),
	m_method (),
	m_uri ()
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		RequestLine::operator == (const RequestLine& rhs) const
{
	if (this != &rhs) {
		return (m_protocolVersion == rhs.m_protocolVersion &&
				m_method == rhs.m_method &&
				m_uri == rhs.m_uri);
	}

	return true;
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		RequestLine::operator != (const RequestLine& rhs) const
{
	return !operator == (rhs);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetProtocolVersion
// -----------------------------------------------------------------------------

inline const ProtocolVersion&	RequestLine::GetProtocolVersion () const
{
	return m_protocolVersion;
}

// -----------------------------------------------------------------------------
// GetMethod
// -----------------------------------------------------------------------------

inline const GS::UniString&		RequestLine::GetMethod () const
{
	return m_method;
}

// -----------------------------------------------------------------------------
// GetUri
// -----------------------------------------------------------------------------

inline const GS::UniString&		RequestLine::GetUri () const
{
	return m_uri;
}

// -----------------------------------------------------------------------------
// IsValid
// -----------------------------------------------------------------------------

inline bool		RequestLine::IsValid () const
{
	return (m_protocolVersion.IsValid () && 
			m_method.GetLength () > 0 &&
			m_uri.GetLength () > 0);
}

}
}

#endif // COMMUNICATION_HTTP_REQUESTLINE_HPP