
// *****************************************************************************
//
// Declaration of ProtocolVersion class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_PROTOCOLVERSION_HPP
#define COMMUNICATION_HTTP_PROTOCOLVERSION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/ProtocolVersionsNotComparableException.hpp"

	// from GSRoot
#include "UniString.hpp"



// --- ProtocolVersion class ---------------------------------------------------

namespace Communication {
namespace Http {

class COMMUNICATIONCOMMON_API ProtocolVersion {

// Data members:
private:
	GS::UniString			m_protocol;
	
	GS::UInt32				m_major;
	GS::UInt32				m_minor;

// Construction / destruction:
public:
	ProtocolVersion ();
	ProtocolVersion (const GS::UniString& protocol, GS::UInt32 major, GS::UInt32 minor);

// Operator overloading:
public:
	bool					operator == (const ProtocolVersion& rhs) const;
	bool					operator != (const ProtocolVersion& rhs) const;

// Operations:
public:
	bool					IsComparableWith (const ProtocolVersion& rhs) const;
	int						CompareTo (const ProtocolVersion& rhs) const;

	const GS::UniString&	GetProtocol () const;
	
	GS::UInt32				GetMajor () const;
	GS::UInt32				GetMinor () const;

	GS::UniString			ToString () const;

	bool					IsValid () const;

};

////////////////////////////////////////////////////////////////////////////////
// ProtocolVersion inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ProtocolVersion::ProtocolVersion () :
	m_protocol (),
	m_major (0),
	m_minor (0)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		ProtocolVersion::operator == (const ProtocolVersion& rhs) const
{
	if (this != &rhs) {
		return (m_protocol == rhs.m_protocol &&
				m_major == rhs.m_major &&
				m_minor == rhs.m_minor);
	}

	return true;
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		ProtocolVersion::operator != (const ProtocolVersion& rhs) const
{
	return !operator == (rhs);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// IsComparableWith
// -----------------------------------------------------------------------------

inline bool		ProtocolVersion::IsComparableWith (const ProtocolVersion& rhs) const
{
	return (m_protocol == rhs.m_protocol);
}

// -----------------------------------------------------------------------------
// GetProtocol
// -----------------------------------------------------------------------------

inline const GS::UniString&		ProtocolVersion::GetProtocol () const
{
	return m_protocol;
}
	
// -----------------------------------------------------------------------------
// GetMajor
// -----------------------------------------------------------------------------

inline GS::UInt32	ProtocolVersion::GetMajor () const
{
	return m_major;
}

// -----------------------------------------------------------------------------
// GetMinor
// -----------------------------------------------------------------------------

inline GS::UInt32	ProtocolVersion::GetMinor () const
{
	return m_minor;
}

// -----------------------------------------------------------------------------
// IsValid
// -----------------------------------------------------------------------------

inline bool		ProtocolVersion::IsValid () const
{
	return (m_protocol.GetLength () > 0);
}

}
}

#endif // COMMUNICATION_HTTP_PROTOCOLVERSION_HPP