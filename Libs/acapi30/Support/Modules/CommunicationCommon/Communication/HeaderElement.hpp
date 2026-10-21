
// *****************************************************************************
//
// Declaration of HeaderElement class
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HEADERELEMENT_HPP
#define COMMUNICATION_HEADERELEMENT_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/HeaderParameter.hpp"

	// from GSRoot
#include "HashTable.hpp"



// --- HeaderElement class -----------------------------------------------------

namespace Communication {

class COMMUNICATIONCOMMON_API HeaderElement {

// Type definitions:
private:
	typedef GS::HashTable<GS::UniString, HeaderParameter> ParameterMap;
public:
	typedef ParameterMap::ConstValueIterator ConstParameterIterator;

// Data members:
private:
	ParameterMap					m_parameters;
	
	GS::Optional<GS::UniString>		m_value;
	GS::UniString					m_name;

// Construction / destruction:
public:
	HeaderElement ();
	HeaderElement (const GS::UniString& name, const GS::UniString& value, const GS::PagedArray<HeaderParameter>& parameters);
	HeaderElement (const GS::UniString& name, const GS::UniString& value);
	HeaderElement (const GS::UniString& name, const GS::PagedArray<HeaderParameter>& parameters);
	HeaderElement (const GS::UniString& name);

// Operator overloading:
public:
	bool							operator == (const HeaderElement& rhs) const;
	bool							operator != (const HeaderElement& rhs) const;
	
// Operations:
public:
	GS::USize						GetParameterCount () const;

	GS::USize						EnumerateParameters (const std::function<void (const HeaderParameter&)>& processor) const;
	ConstParameterIterator			EnumerateParameters ();

	bool							GetParameter (const GS::UniString& parameterName, HeaderParameter& parameter) const;
	bool							HasParameter (const GS::UniString& parameterName);

	bool							GetValue (GS::UniString& value) const;
	bool							HasValue () const;

	const GS::UniString&			GetName () const;

	bool							IsValid () const;

// Implementation:
private:
	void							Init (const GS::PagedArray<HeaderParameter>& parameters);

};

////////////////////////////////////////////////////////////////////////////////
// HeaderElement inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline HeaderElement::HeaderElement () :
	m_parameters (),
	m_value (),
	m_name ()
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		HeaderElement::operator != (const HeaderElement& rhs) const
{
	return !operator == (rhs);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetParameterCount
// -----------------------------------------------------------------------------

inline GS::USize	HeaderElement::GetParameterCount () const
{
	return m_parameters.GetSize ();
}

// -----------------------------------------------------------------------------
// GetValue
// -----------------------------------------------------------------------------

inline bool		HeaderElement::GetValue (GS::UniString& value) const
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

inline bool		HeaderElement::HasValue () const
{
	return m_value.HasValue ();
}

// -----------------------------------------------------------------------------
// GetName
// -----------------------------------------------------------------------------

inline const GS::UniString&		HeaderElement::GetName () const
{
	return m_name;
}

}

#endif // COMMUNICATION_HEADERELEMENT_HPP