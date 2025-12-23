
// *****************************************************************************
//
// Declaration of HeaderFieldValue class
//
// Module:			HTTP
// Namespace:		HTTP::MessageHeader
// Contact person:	KOVA
//
// ***************************************************************************** 

#ifndef HTTP_MESSAGEHEADER_HEADERFIELDVALUE_HPP
#define HTTP_MESSAGEHEADER_HEADERFIELDVALUE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/HTTPExport.hpp"

#include "Pair.hpp"
#include "UniString.hpp"


namespace HTTP {
namespace MessageHeader {

class HTTP_API HeaderFieldValue {

public:

class ValueWithQuality {

private:
	GS::UniString	m_value;
	double			m_quality;

public:	
	ValueWithQuality (const GS::UniString& value, double quality = 1.0);
	
	const GS::UniString&		GetValue () const;
	double						GetQuality () const;

};

private:
	GS::UniString	m_value;

public:
	HeaderFieldValue ();
	explicit HeaderFieldValue (const GS::UniString& value);
	~HeaderFieldValue ();

	const GS::UniString&		GetAsString () const;
	void						SetAsString (const GS::UniString& value);
	bool						IsEqual (const GS::UniString& value, GS::CaseComparison caseComparsion = GS::CaseInsensitive);

	ValueWithQuality			GetAsValueWithQuality () const;
	void						SetAsValueWithQuality (const ValueWithQuality& valueWithQuality);
	void						SetAsValueWithQuality (const GS::UniString& value, double quality);

	UInt64						GetAsDecimalValue () const;
	void						SetAsDecimalValue (UInt64 value);

};

// -----------------------------------------------------------------------------
// GetAsString
// -----------------------------------------------------------------------------

inline const GS::UniString&	HeaderFieldValue::GetAsString () const
{
	return m_value;
}

// -----------------------------------------------------------------------------
// SetAsString
// -----------------------------------------------------------------------------

inline void HeaderFieldValue::SetAsString (const GS::UniString& value)
{
	m_value = value;
}

// -----------------------------------------------------------------------------
// GetValue
// -----------------------------------------------------------------------------

inline const GS::UniString& HeaderFieldValue::ValueWithQuality::GetValue () const
{
	return m_value;
}

// -----------------------------------------------------------------------------
// GetQuality
// -----------------------------------------------------------------------------

inline double HeaderFieldValue::ValueWithQuality::GetQuality () const
{
	return m_quality;
}

}
}

#endif

