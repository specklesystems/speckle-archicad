
// *****************************************************************************
//
// Declaration of Ranges class
//
// Module:			HTTP
// Namespace:		HTTP::MessageHeader::RangeField
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_MESSAGEHEADER_RANGEFIELD_RANGES_HPP
#define HTTP_MESSAGEHEADER_RANGEFIELD_RANGES_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/HTTPExport.hpp"
#include "HTTP/MessageHeader/RangeField/Range.hpp"
#include "HTTP/Parser/ParserException.hpp"

#include "PagedArray.hpp"
#include "UniString.hpp"


namespace HTTP {
namespace MessageHeader {
namespace RangeField {

class HTTP_API Ranges {

private:
	GS::UniString		m_unit;
	GS::Array <Range>	m_ranges;

public:
	Ranges ();
	Ranges (const GS::UniString& unit, const GS::Array <Range>& ranges);
	~Ranges ();

	const GS::UniString&	GetUnit () const;
	void					SetUnit (const GS::UniString& unit);
	GS::Array <Range>&		GetRanges ();
	void					SetRanges (GS::Array <Range>& ranges);

	void					Parse (const GS::UniString& ranges);
	void					ToRangeValue (GS::UniString& rangeValue) const;

	void					Clear ();

};

// -----------------------------------------------------------------------------
// GetUnit
// -----------------------------------------------------------------------------

inline const GS::UniString& Ranges::GetUnit () const
{
	return m_unit;
}

// -----------------------------------------------------------------------------
// SetUnit
// -----------------------------------------------------------------------------

inline void Ranges::SetUnit (const GS::UniString& unit)
{
	m_unit = unit;
}

// -----------------------------------------------------------------------------
// GetRanges
// -----------------------------------------------------------------------------

inline GS::Array<Range>& Ranges::GetRanges ()
{
	return m_ranges;
}

// -----------------------------------------------------------------------------
// SetRanges
// -----------------------------------------------------------------------------

inline void Ranges::SetRanges (GS::Array <Range>& ranges)
{
	m_ranges = ranges;
}

}
}
}

#endif

