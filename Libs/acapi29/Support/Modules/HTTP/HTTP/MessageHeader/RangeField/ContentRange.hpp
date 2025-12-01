
// *****************************************************************************
//
// Declaration of ContentRange class
//
// Module:			HTTP
// Namespace:		HTTP::MessageHeader::RangeField
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_MESSAGEHEADER_RANGEFIELD_CONTENTRANGE_HPP
#define HTTP_MESSAGEHEADER_RANGEFIELD_CONTENTRANGE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/HTTPExport.hpp"
#include "HTTP/Parser/ParserException.hpp"

#include "UniString.hpp"


namespace HTTP {
namespace MessageHeader {
namespace RangeField {

class HTTP_API ContentRange {

public:
	static const GS::Int64	UndefinedValue;

private:
	GS::UniString			m_unit;
	GS::Int64				m_from;
	GS::Int64				m_to;
	GS::Int64				m_length;

public:
	ContentRange ();
	ContentRange (const GS::UniString& unit, GS::Int64 from, GS::Int64 to, GS::Int64 length);
	~ContentRange ();

	bool					operator== (const ContentRange& rhs) const; 
	bool					operator!= (const ContentRange& rhs) const;

	const GS::UniString&	GetUnit () const;
	void					SetUnit (const GS::UniString& unit);
	GS::Int64				GetFrom () const;
	void 					SetFrom (GS::Int64 from);
	GS::Int64				GetTo () const;
	void 					SetTo (GS::Int64 to);
	bool					IsRangeSpecified () const;
	GS::Int64				GetLength () const;
	void 					SetLength (GS::Int64 length);
	bool					IsLengthSpecified () const;

	void					Parse (const GS::UniString& contentRange);
	void					ToRangeValue (GS::UniString& value) const;

	void					Clear ();

};

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool  ContentRange::operator== (const ContentRange& rhs) const
{
	return ((m_unit == rhs.m_unit) && (m_from == rhs.m_from) && (m_to == rhs.m_to) && (m_length == rhs.m_length));
}

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool  ContentRange::operator!= (const ContentRange& rhs) const
{
	return !(*this == rhs);
}

// -----------------------------------------------------------------------------
// GetUnit
// -----------------------------------------------------------------------------

inline const GS::UniString& ContentRange::GetUnit () const
{
	return m_unit;
}

// -----------------------------------------------------------------------------
// SetUnit
// -----------------------------------------------------------------------------

inline void ContentRange::SetUnit (const GS::UniString& unit)
{
	m_unit = unit;
}


// -----------------------------------------------------------------------------
// GetFrom
// -----------------------------------------------------------------------------

inline GS::Int64 ContentRange::GetFrom () const
{
	return m_from;
}

// -----------------------------------------------------------------------------
// SetFrom
// -----------------------------------------------------------------------------

inline void ContentRange::SetFrom (GS::Int64 from)
{
	m_from = from;
}

// -----------------------------------------------------------------------------
// GetTo
// -----------------------------------------------------------------------------

inline GS::Int64 ContentRange::GetTo () const
{
	return m_to;
}

// -----------------------------------------------------------------------------
// SetTo
// -----------------------------------------------------------------------------

inline void ContentRange::SetTo (GS::Int64 to)
{
	m_to = to;
}

// -----------------------------------------------------------------------------
// IsRangeSpecified
// -----------------------------------------------------------------------------

inline bool ContentRange::IsRangeSpecified () const
{
	return ((m_from != UndefinedValue) && (m_to != UndefinedValue));
}

// -----------------------------------------------------------------------------
// GetLength
// -----------------------------------------------------------------------------

inline GS::Int64 ContentRange::GetLength () const
{
	return m_length;
}

// -----------------------------------------------------------------------------
// SetLength
// -----------------------------------------------------------------------------

inline void ContentRange::SetLength (GS::Int64 length)
{
	m_length = length;
}

// -----------------------------------------------------------------------------
// IsLengthSpecified
// -----------------------------------------------------------------------------

inline bool  ContentRange::IsLengthSpecified () const
{
	return (m_length != UndefinedValue);
}

}
}
}

#endif

