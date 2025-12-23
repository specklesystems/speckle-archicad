
// *****************************************************************************
//
// Declaration of OtherRange class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_OTHERRANGE_HPP
#define COMMUNICATION_HTTP_OTHERRANGE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/Range.hpp"



// --- OtherRange class --------------------------------------------------------

namespace Communication {
namespace Http {

class COMMUNICATIONCOMMON_API OtherRange : public Range {

// Data members:
private:
	GS::UniString			m_value;
	RangeUnit				m_unit;

// Construction / destruction:
public:
	OtherRange ();
	OtherRange (const RangeUnit& unit, const GS::UniString& value);

// Operator overloading:
public:
	bool					operator == (const OtherRange& rhs) const;
	bool					operator != (const OtherRange& rhs) const;

// Operations:
public:
	void					SetValue (const GS::UniString& value);
	const GS::UniString&	GetValue () const;

	void					SetUnit (const RangeUnit& unit);

// Range interface implementation:
public:
	virtual RangeUnit		GetUnit () const override;

	virtual bool			Equals (const Range& rhs) const override;

	virtual GS::UniString	ToString () const override;
	virtual GS::UniString	Format () const override;

	virtual bool			IsValid () const override;

// Static operations:
public:
	static bool				Parse (const GS::UniString& otherRangeString,
								OtherRange& otherRangeParsed);

};

////////////////////////////////////////////////////////////////////////////////
// OtherRange inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline OtherRange::OtherRange () :
	m_value (),
	m_unit ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline OtherRange::OtherRange (const RangeUnit& unit, const GS::UniString& value) :
	m_value (value),
	m_unit (unit)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		OtherRange::operator == (const OtherRange& rhs) const
{
	if (this != &rhs) {
		return (m_value.IsEqual (rhs.m_value, GS::CaseInsensitive) && m_unit == rhs.m_unit);
	}

	return true;
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		OtherRange::operator != (const OtherRange& rhs) const
{
	return !operator == (rhs);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// SetValue
// -----------------------------------------------------------------------------

inline void		OtherRange::SetValue (const GS::UniString& value)
{
	m_value = value;
}

// -----------------------------------------------------------------------------
// GetValue
// -----------------------------------------------------------------------------

inline const GS::UniString&		OtherRange::GetValue () const
{
	return m_value;
}

// -----------------------------------------------------------------------------
// SetUnit
// -----------------------------------------------------------------------------

inline void		OtherRange::SetUnit (const RangeUnit& unit)
{
	m_unit = unit;
}

}
}

#endif // COMMUNICATION_HTTP_OTHERRANGE_HPP