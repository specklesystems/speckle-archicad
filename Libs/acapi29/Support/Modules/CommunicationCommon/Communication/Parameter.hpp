
// *****************************************************************************
//
// Declaration of Parameter class
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_PARAMETER_HPP
#define COMMUNICATION_PARAMETER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/CommunicationCommonExport.hpp"

	// from GSRoot
#include "UniString.hpp"



// --- Parameter class ---------------------------------------------------------

namespace Communication {
	
class COMMUNICATIONCOMMON_API Parameter {

// Data members:
private:
	GS::UniString			m_name;
	GS::UniString			m_value;

// Construction / destruction:
public:
	Parameter ();
	Parameter (const GS::UniString& name, const GS::UniString& value);
	Parameter (const GS::UniString& name, GS::UInt64 value);
	Parameter (const GS::UniString& name, GS::Int64 value);
	Parameter (const GS::UniString& name, GS::UInt32 value);
	Parameter (const GS::UniString& name, GS::Int32 value);
	Parameter (const GS::UniString& name, GS::UInt16 value);
	Parameter (const GS::UniString& name, GS::Int16 value);
	Parameter (const GS::UniString& name, double value);
	Parameter (const GS::UniString& name, float value);
	Parameter (const GS::UniString& name, bool value);

// Operator overloading:
public:
	bool					operator == (const Parameter& rhs) const;
	bool					operator != (const Parameter& rhs) const;

// Operations:
public:
	const GS::UniString&	GetName () const;

	void					SetValue (const GS::UniString& value);
	void					SetValue (GS::UInt64 value);
	void					SetValue (GS::Int64 value);
	void					SetValue (GS::UInt32 value);
	void					SetValue (GS::Int32 value);
	void					SetValue (GS::UInt16 value);
	void					SetValue (GS::Int16 value);
	void					SetValue (double value);
	void					SetValue (float value);
	void					SetValue (bool value);

	bool					GetValue (GS::UInt64& value) const;
	bool					GetValue (GS::Int64& value) const;
	bool					GetValue (GS::UInt32& value) const;
	bool					GetValue (GS::Int32& value) const;
	bool					GetValue (GS::UInt16& value) const;
	bool					GetValue (GS::Int16& value) const;
	bool					GetValue (double& value) const;
	bool					GetValue (float& value) const;
	bool					GetValue (bool& value) const;

	const GS::UniString&	GetValue () const;

	bool					IsValid () const;
};

////////////////////////////////////////////////////////////////////////////////
// Parameter inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline Parameter::Parameter () :
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

inline bool		Parameter::operator == (const Parameter& rhs) const
{
	if (this != &rhs) {
		return (m_name == rhs.m_name && m_value == rhs.m_value);
	}

	return true;
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		Parameter::operator != (const Parameter& rhs) const
{
	return !operator == (rhs);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetName
// -----------------------------------------------------------------------------

inline const GS::UniString&		Parameter::GetName () const
{
	return m_name;
}

// -----------------------------------------------------------------------------
// SetValue
// -----------------------------------------------------------------------------

inline void		Parameter::SetValue (const GS::UniString& value)
{
	m_value = value;
}

// -----------------------------------------------------------------------------
// GetValue
// -----------------------------------------------------------------------------

inline const GS::UniString&		Parameter::GetValue () const
{
	return m_value;
}

}

#endif // COMMUNICATION_PARAMETER_HPP