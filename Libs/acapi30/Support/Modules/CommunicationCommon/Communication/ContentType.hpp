
// *****************************************************************************
//
// Declaration of ContentType class
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CONTENTTYPE_HPP
#define COMMUNICATION_CONTENTTYPE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/HeaderParameter.hpp"

	// from GSRoot
#include "HashTable.hpp"



// --- ContentType class -------------------------------------------------------

namespace Communication {

class COMMUNICATIONCOMMON_API ContentType {

// Type definitions:
private:
	typedef GS::HashTable<GS::UniString, HeaderParameter> ParameterMap;

// Data members:
private:
	ParameterMap			m_parameters;

	GS::UniString			m_mediaType;
	GS::UniString			m_charset;

// Construction / destruction:
public:
	ContentType ();
	ContentType (const GS::UniString& mediaType, const GS::UniString& charset, const GS::PagedArray<HeaderParameter>& parameters);
	ContentType (const GS::UniString& mediaType, const GS::UniString& charset);
	ContentType (const GS::UniString& mediaType, const GS::PagedArray<HeaderParameter>& parameters);
	ContentType (const GS::UniString& mediaType);

// Operator overloading:
public:
	bool					operator == (const ContentType& rhs) const;
	bool					operator != (const ContentType& rhs) const;

// Operations:
public:
	bool					GetParameter (const GS::UniString& parameterName, GS::UniString& value) const;

	const GS::UniString&	GetMediaType () const;
	const GS::UniString&	GetCharset () const;

	GS::UniString			ToString () const;
	GS::UniString			Format () const;

	void					Swap (ContentType& rhs);

	bool					IsValid () const;

// Implementation:
private:
	void					Init (const GS::PagedArray<HeaderParameter>& parameters);

// Static operations:
public:
	static bool				Parse (const GS::UniString& contentTypeString,
								ContentType& contentTypeParsed);

};

////////////////////////////////////////////////////////////////////////////////
// ContentType inlines

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ContentType::ContentType () :
	m_parameters (),
	m_mediaType (),
	m_charset ()
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		ContentType::operator != (const ContentType& rhs) const
{
	return !operator == (rhs);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetMediaType
// -----------------------------------------------------------------------------

inline const GS::UniString&		ContentType::GetMediaType () const
{
	return m_mediaType;
}

// -----------------------------------------------------------------------------
// GetCharset
// -----------------------------------------------------------------------------

inline const GS::UniString&		ContentType::GetCharset () const
{
	return m_charset;
}

}

#endif // COMMUNICATION_CONTENTTYPE_HPP