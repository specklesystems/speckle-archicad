
// *****************************************************************************
//
// Declaration of OtherContentRange class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_OTHERCONTENTRANGE_HPP
#define COMMUNICATION_HTTP_OTHERCONTENTRANGE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/ContentRange.hpp"



// --- OtherContentRange class -------------------------------------------------

namespace Communication {
namespace Http {

class COMMUNICATIONCOMMON_API OtherContentRange : public ContentRange {

// Data members:
private:
	GS::UniString			m_value;
	RangeUnit				m_unit;

// Construction / destruction:
public:
	OtherContentRange ();
	OtherContentRange (const RangeUnit& unit, const GS::UniString& value);

// Operator overloading:
public:
	bool					operator == (const OtherContentRange& rhs) const;
	bool					operator != (const OtherContentRange& rhs) const;

// Operations:
public:
	void					SetValue (const GS::UniString& value);
	const GS::UniString&	GetValue () const;

	void					SetUnit (const RangeUnit& unit);

// ContentRange interface implementation:
public:
	virtual RangeUnit		GetUnit () const override;

	virtual bool			Equals (const ContentRange& rhs) const override;

	virtual GS::UniString	ToString () const override;
	virtual GS::UniString	Format () const override;

	virtual bool			IsValid () const override;

// Static operations:
public:
	static bool				Parse (const GS::UniString& otherContentRangeString,
								OtherContentRange& otherContentRangeParsed);

};

////////////////////////////////////////////////////////////////////////////////
// OtherContentRange inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline OtherContentRange::OtherContentRange () :
	m_value (),
	m_unit ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline OtherContentRange::OtherContentRange (const RangeUnit& unit, const GS::UniString& value) :
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

inline bool		OtherContentRange::operator == (const OtherContentRange& rhs) const
{
	if (this != &rhs) {
		return (m_value.IsEqual (rhs.m_value, GS::CaseInsensitive) && m_unit == rhs.m_unit);
	}

	return true;
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		OtherContentRange::operator != (const OtherContentRange& rhs) const
{
	return !operator == (rhs);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// SetValue
// -----------------------------------------------------------------------------

inline void		OtherContentRange::SetValue (const GS::UniString& value)
{
	m_value = value;
}

// -----------------------------------------------------------------------------
// GetValue
// -----------------------------------------------------------------------------

inline const GS::UniString&		OtherContentRange::GetValue () const
{
	return m_value;
}

// -----------------------------------------------------------------------------
// SetUnit
// -----------------------------------------------------------------------------

inline void		OtherContentRange::SetUnit (const RangeUnit& unit)
{
	m_unit = unit;
}

}
}

#endif // COMMUNICATION_HTTP_OTHERCONTENTRANGE_HPP