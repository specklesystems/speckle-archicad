
// *****************************************************************************
//
// Declaration of Range class
//
// Module:			HTTP
// Namespace:		HTTP::MessageHeader::RangeField
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_MESSAGEHEADER_RANGEFIELD_RANGE_HPP
#define HTTP_MESSAGEHEADER_RANGEFIELD_RANGE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/HTTPExport.hpp"


namespace HTTP {
namespace MessageHeader {
namespace RangeField {

class HTTP_API Range {

public:
	static const GS::Int64	UndefinedValue;

private:
	GS::Int64		m_from;
	GS::Int64		m_to;

public:
	Range ();
	Range (GS::Int64 from, GS::Int64 to);
	~Range ();

	bool			operator== (const Range& rhs) const; 
	bool			operator!= (const Range& rhs) const;

	GS::Int64		GetFrom () const;
	void 			SetFrom (GS::Int64 from);
	GS::Int64		GetTo () const;
	void 			SetTo (GS::Int64 to);

};

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool  Range::operator== (const Range& rhs) const
{
	return ((m_from == rhs.m_from) && (m_to == rhs.m_to));
}

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool  Range::operator!= (const Range& rhs) const
{
	return !(*this == rhs);
}

// -----------------------------------------------------------------------------
// GetFrom
// -----------------------------------------------------------------------------

inline GS::Int64 Range::GetFrom () const
{
	return m_from;
}

// -----------------------------------------------------------------------------
// SetFrom
// -----------------------------------------------------------------------------

inline void Range::SetFrom (GS::Int64 from)
{
	m_from = from;
}

// -----------------------------------------------------------------------------
// GetTo
// -----------------------------------------------------------------------------

inline GS::Int64 Range::GetTo () const
{
	return m_to;
}

// -----------------------------------------------------------------------------
// SetTo
// -----------------------------------------------------------------------------

inline void Range::SetTo (GS::Int64 to)
{
	m_to = to;
}

}
}
}

#endif

