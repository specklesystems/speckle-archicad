
// *****************************************************************************
//
// Declaration of StatusLine class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_STATUSLINE_HPP
#define COMMUNICATION_HTTP_STATUSLINE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/ProtocolVersion.hpp"



// --- StatusLine class --------------------------------------------------------

namespace Communication {
namespace Http {

class COMMUNICATIONCOMMON_API StatusLine {

// Data members:
private:
	ProtocolVersion			m_protocolVersion;
	GS::UInt32				m_statusCode;
	GS::UniString			m_reasonPhrase;

// Construction / destruction:
public:
	StatusLine ();
	StatusLine (const ProtocolVersion& protocolVersion, GS::UInt32 statusCode, const GS::UniString& reasonPhrase);

// Operator overloading:
public:
	bool					operator == (const StatusLine& rhs) const;
	bool					operator != (const StatusLine& rhs) const;

// Operations:
public:
	const ProtocolVersion&	GetProtocolVersion () const;
	const GS::UniString&	GetReasonPhrase () const;
	GS::UInt32				GetStatusCode () const;

	GS::UniString			ToString () const;

	bool					IsValid () const;

};

////////////////////////////////////////////////////////////////////////////////
// StatusLine inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline StatusLine::StatusLine () :
	m_protocolVersion (),
	m_statusCode (0),
	m_reasonPhrase ()
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		StatusLine::operator == (const StatusLine& rhs) const
{
	if (this != &rhs) {
		return (m_protocolVersion == rhs.m_protocolVersion &&
				m_statusCode == rhs.m_statusCode &&
				m_reasonPhrase == rhs.m_reasonPhrase);
	}

	return true;
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		StatusLine::operator != (const StatusLine& rhs) const
{
	return !operator == (rhs);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetProtocolVersion
// -----------------------------------------------------------------------------

inline const ProtocolVersion&	StatusLine::GetProtocolVersion () const
{
	return m_protocolVersion;
}

// -----------------------------------------------------------------------------
// GetReasonPhrase
// -----------------------------------------------------------------------------

inline const GS::UniString&		StatusLine::GetReasonPhrase () const
{
	return m_reasonPhrase;
}

// -----------------------------------------------------------------------------
// GetStatusCode
// -----------------------------------------------------------------------------

inline GS::UInt32	StatusLine::GetStatusCode () const
{
	return m_statusCode;
}

// -----------------------------------------------------------------------------
// IsValid
// -----------------------------------------------------------------------------

inline bool		StatusLine::IsValid () const
{
	return (m_protocolVersion.IsValid ());
}

}
}

#endif // COMMUNICATION_HTTP_STATUSLINE_HPP