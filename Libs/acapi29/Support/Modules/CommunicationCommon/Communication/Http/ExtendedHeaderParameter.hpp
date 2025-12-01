
// *****************************************************************************
//
// Declaration of ExtendedHeaderParameter class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_EXTENDEDHEADERPARAMETER_HPP
#define COMMUNICATION_HTTP_EXTENDEDHEADERPARAMETER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/HeaderParameter.hpp"



// --- ExtendedHeaderParameter class -------------------------------------------

namespace Communication {
namespace Http {

class COMMUNICATIONCOMMON_API ExtendedHeaderParameter { // RFC5987

// Data members:
private:
	GS::Optional<GS::UniString>		m_language;
	GS::Optional<GS::UniString>		m_value;

	GS::UniString					m_charset;
	GS::UniString					m_name;

// Construction / destruction:
public:
	ExtendedHeaderParameter ();
	ExtendedHeaderParameter (const GS::UniString& name, const GS::UniString& language, const GS::UniString& charset, const GS::UniString& value);
	ExtendedHeaderParameter (const GS::UniString& name, const GS::UniString& charset, const GS::UniString& value);
	ExtendedHeaderParameter (const GS::UniString& name, const GS::UniString& charset);

// Operator overloading:
public:
	bool							operator == (const ExtendedHeaderParameter& rhs) const;
	bool							operator != (const ExtendedHeaderParameter& rhs) const;

// Operations:
public:
	bool							GetLanguage (GS::UniString& language) const;
	bool							HasLanguage () const;

	const GS::UniString&			GetCharset () const;

	bool							GetValue (GS::UniString& value) const;
	bool							HasValue () const;

	const GS::UniString&			GetName () const;

	HeaderParameter					ToHeaderParameter () const;

	bool							IsValid () const;

// Static operations:
public:
	static bool						IsExtendedHeaderParameter (const HeaderParameter& headerParameter);

	static bool						FromHeaderParameter (const HeaderParameter& headerParameter,
										ExtendedHeaderParameter& extendedHeaderParameter);

};

////////////////////////////////////////////////////////////////////////////////
// ExtendedHeaderParameter inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ExtendedHeaderParameter::ExtendedHeaderParameter () :
	m_language (),
	m_charset (),
	m_value (),
	m_name ()
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		ExtendedHeaderParameter::operator == (const ExtendedHeaderParameter& rhs) const
{
	if (this != &rhs) {
		return (m_name.IsEqual (rhs.m_name, GS::CaseInsensitive) &&
				m_language == rhs.m_language &&
				m_charset == rhs.m_charset &&
				m_value == rhs.m_value);
	}

	return true;
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		ExtendedHeaderParameter::operator != (const ExtendedHeaderParameter& rhs) const
{
	return !operator == (rhs);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetLanguage
// -----------------------------------------------------------------------------

inline bool		ExtendedHeaderParameter::GetLanguage (GS::UniString& language) const
{
	if (m_language.HasValue () == false) {
		return false;
	}

	language = m_language.Get ();

	return true;
}

// -----------------------------------------------------------------------------
// HasLanguage
// -----------------------------------------------------------------------------

inline bool		ExtendedHeaderParameter::HasLanguage () const
{
	return m_language.HasValue ();
}

// -----------------------------------------------------------------------------
// GetCharset
// -----------------------------------------------------------------------------

inline const GS::UniString&		ExtendedHeaderParameter::GetCharset () const
{
	return m_charset;
}

// -----------------------------------------------------------------------------
// GetValue
// -----------------------------------------------------------------------------

inline bool		ExtendedHeaderParameter::GetValue (GS::UniString& value) const
{
	if (m_value.HasValue () == false) {
		return false;
	}

	value = m_value.Get ();

	return true;
}

// -----------------------------------------------------------------------------
// HasValue
// -----------------------------------------------------------------------------

inline bool		ExtendedHeaderParameter::HasValue () const
{
	return m_value.HasValue ();
}

// -----------------------------------------------------------------------------
// GetName
// -----------------------------------------------------------------------------

inline const GS::UniString&		ExtendedHeaderParameter::GetName () const
{
	return m_name;
}

}
}

#endif // COMMUNICATION_HTTP_EXTENDEDHEADERPARAMETER_HPP