
// *****************************************************************************
//
// Declaration of Header class
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HEADER_HPP
#define COMMUNICATION_HEADER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/CommunicationCommonExport.hpp"

	// from GSRoot
#include "UniString.hpp"



// --- Header class ------------------------------------------------------------

namespace Communication {

class COMMUNICATIONCOMMON_API Header {

// Data members:
private:
	GS::UniString			m_name;
	GS::UniString			m_value;

// Construction / destruction:
public:
	Header ();
	Header (const GS::UniString& name, const GS::UniString& value);

// Operator overloading:
public:
	bool					operator == (const Header& rhs) const;
	bool					operator != (const Header& rhs) const;

// Operations:
public:
	const GS::UniString&	GetName () const;

	void					SetValue (const GS::UniString& value);
	const GS::UniString&	GetValue () const;

	bool					IsValid () const;

};

////////////////////////////////////////////////////////////////////////////////
// Header inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline Header::Header () :
	m_name (),
	m_value ()
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		Header::operator == (const Header& rhs) const
{
	if (this != &rhs) {
		return (m_name == rhs.m_name && m_value == rhs.m_value);
	}

	return true;
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		Header::operator != (const Header& rhs) const
{
	return !operator == (rhs);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetName
// -----------------------------------------------------------------------------

inline const GS::UniString&		Header::GetName () const
{
	return m_name;
}

// -----------------------------------------------------------------------------
// SetValue
// -----------------------------------------------------------------------------

inline void		Header::SetValue (const GS::UniString& value)
{
	m_value = value;
}

// -----------------------------------------------------------------------------
// GetValue
// -----------------------------------------------------------------------------

inline const GS::UniString&		Header::GetValue () const
{
	return m_value;
}

}

#endif // COMMUNICATION_HEADER_HPP