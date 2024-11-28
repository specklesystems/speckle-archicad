
// *****************************************************************************
//
// Declaration of HeaderParameter class
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HEADERPARAMETER_HPP
#define COMMUNICATION_HEADERPARAMETER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/CommunicationCommonExport.hpp"

	// from GSRoot
#include "Optional.hpp"
#include "UniString.hpp"



// --- HeaderParameter class ---------------------------------------------------

namespace Communication {

class COMMUNICATIONCOMMON_API HeaderParameter {

// Data members:
private:
	GS::Optional<GS::UniString>		m_value;
	GS::UniString					m_name;

// Construction / destruction:
public:
	HeaderParameter ();
	HeaderParameter (const GS::UniString& name, const GS::UniString& value);
	HeaderParameter (const GS::UniString& name);

// Operator overloading:
public:
	bool							operator == (const HeaderParameter& rhs) const;
	bool							operator != (const HeaderParameter& rhs) const;

// Operations:
public:
	bool							GetValue (GS::UniString& value) const;
	bool							HasValue () const;

	const GS::UniString&			GetName () const;

	bool							IsValid () const;

};

////////////////////////////////////////////////////////////////////////////////
// HeaderParameter inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline HeaderParameter::HeaderParameter () :
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

inline bool		HeaderParameter::operator == (const HeaderParameter& rhs) const
{
	if (this != &rhs) {
		return (m_name.IsEqual (rhs.m_name, GS::CaseInsensitive) && m_value == rhs.m_value);
	}

	return true;
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		HeaderParameter::operator != (const HeaderParameter& rhs) const
{
	return !operator == (rhs);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetValue
// -----------------------------------------------------------------------------

inline bool		HeaderParameter::GetValue (GS::UniString& value) const
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

inline bool		HeaderParameter::HasValue () const
{
	return m_value.HasValue ();
}

// -----------------------------------------------------------------------------
// GetName
// -----------------------------------------------------------------------------

inline const GS::UniString&		HeaderParameter::GetName () const
{
	return m_name;
}

}

#endif // COMMUNICATION_HEADERPARAMETER_HPP