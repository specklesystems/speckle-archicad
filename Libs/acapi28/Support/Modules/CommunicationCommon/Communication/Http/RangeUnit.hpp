
// *****************************************************************************
//
// Declaration of RangeUnit class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_RANGEUNIT_HPP
#define COMMUNICATION_HTTP_RANGEUNIT_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/CommunicationCommonExport.hpp"

	// from GSRoot
#include "UniString.hpp"



// --- RangeUnit class ---------------------------------------------------------

namespace Communication {
namespace Http {

class COMMUNICATIONCOMMON_API RangeUnit {

// Data members:
private:
	GS::UniString			m_name;
	
	bool					m_valid;

// Construction / destruction:
public:
			 RangeUnit ();
	explicit RangeUnit (const GS::UniString& name);

// Operator overloading:
public:
	bool					operator == (const RangeUnit& rhs) const;
	bool					operator != (const RangeUnit& rhs) const;

// Operations:
public:
	void					SetName (const GS::UniString& name);
	const GS::UniString&	GetName () const;

	GS::UniString			ToString () const;

	bool					IsValid () const;

// Implementation:
private:
	void					Validate ();

// Static operations:
public:
	static bool				IsValid (const GS::UniString& name);

// Static implementation:
private:
	static bool				IsValidChar (const GS::UniChar& ch);

};

////////////////////////////////////////////////////////////////////////////////
// RangeUnit inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline RangeUnit::RangeUnit () :
	m_name (), m_valid (false)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline RangeUnit::RangeUnit (const GS::UniString& name) :
	m_name (), m_valid (false)
{
	SetName (name);
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		RangeUnit::operator == (const RangeUnit& rhs) const
{
	if (this != &rhs) {
		return (m_name.IsEqual (rhs.m_name, GS::CaseInsensitive));
	}

	return true;
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		RangeUnit::operator != (const RangeUnit& rhs) const
{
	return !operator == (rhs);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetName
// -----------------------------------------------------------------------------

inline const GS::UniString&		RangeUnit::GetName () const
{
	return m_name;
}

}
}

#endif // COMMUNICATION_HTTP_RANGEUNIT_HPP