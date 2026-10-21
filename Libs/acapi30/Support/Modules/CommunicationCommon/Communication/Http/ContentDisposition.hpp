
// *****************************************************************************
//
// Declaration of ContentDisposition class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_CONTENTDISPOSITION_HPP
#define COMMUNICATION_HTTP_CONTENTDISPOSITION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/HeaderParameter.hpp"

	// from GSRoot
#include "HashTable.hpp"



// --- ContentDisposition class ------------------------------------------------

namespace Communication {
namespace Http {

class COMMUNICATIONCOMMON_API ContentDisposition { // RFC2183

// Type definitions:
private:
	typedef GS::HashTable<GS::UniString, HeaderParameter> ParameterMap;

// Data members:
private:
	GS::UniString			m_dispositionType;

	ParameterMap			m_parameters;

// Construction / destruction:
public:
	ContentDisposition ();
	ContentDisposition (const GS::UniString& dispositionType, const GS::PagedArray<HeaderParameter>& parameters);
	ContentDisposition (const GS::UniString& dispositionType);

// Operator overloading:
public:
	bool					operator == (const ContentDisposition& rhs) const;
	bool					operator != (const ContentDisposition& rhs) const;

// Operations:
public:
	bool					GetParameter (const GS::UniString& parameterName, GS::UniString& value) const;

	const GS::UniString&	GetDispositionType () const;

	GS::UniString			ToString () const;
	
	GS::UniString			FormatFor (const GS::UniString& userAgent) const;
	GS::UniString			Format () const;

	void					Swap (ContentDisposition& rhs);

	bool					IsValid () const;

// Static operations:
public:
	static bool				Parse (const GS::UniString& contentDispositionString,
								ContentDisposition& contentDispositionParsed);

};

////////////////////////////////////////////////////////////////////////////////
// ContentDisposition inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ContentDisposition::ContentDisposition () :
	m_dispositionType (),
	m_parameters ()
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		ContentDisposition::operator != (const ContentDisposition& rhs) const
{
	return !operator == (rhs);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetDispositionType
// -----------------------------------------------------------------------------

inline const GS::UniString&		ContentDisposition::GetDispositionType () const
{
	return m_dispositionType;
}

}
}

#endif // COMMUNICATION_HTTP_CONTENTDISPOSITION_HPP