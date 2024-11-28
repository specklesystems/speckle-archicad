
// *****************************************************************************
//
// Declaration of HttpRequestRedirectInformation class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client::Http::HttpProperties
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_HTTP_HTTPPROPERTIES_HTTPREQUESTREDIRECTINFORMATION_HPP
#define COMMUNICATION_CLIENT_HTTP_HTTPPROPERTIES_HTTPREQUESTREDIRECTINFORMATION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/CommunicationClientExport.hpp"

	// from CommunicationCommon
#include "Communication/GenericPropertyObject.hpp"

	// from GSRoot
#include "UniString.hpp"


// --- HttpRequestRedirectInformation class ------------------------------------

namespace Communication {
namespace Client {
namespace Http {
namespace HttpProperties {

class COMMUNICATIONCLIENT_API HttpRequestRedirectInformation {

// Data members:

private:
	GS::UniString	m_originalRequestUrl;
	GS::UniString	m_finalRequestUrl;

// Construction / destruction:
public:
	HttpRequestRedirectInformation ();
	HttpRequestRedirectInformation (const GS::UniString& originalRequestUrl,
									const GS::UniString& finalRequestUrl);

	~HttpRequestRedirectInformation ();

// Operator overloading:
public:
	bool operator == (const HttpRequestRedirectInformation& rhs) const;

// Operations:
public:
	const GS::UniString&		GetOriginalRequestUrl () const;
	const GS::UniString&		GetFinalRequestUrl () const;

};

// --- HttpRequestRedirectInformation class ------------------------------------

class COMMUNICATIONCLIENT_API HttpRequestRedirectInformationProperty : public GenericPropertyObject <HttpRequestRedirectInformation>
{
	
// Construction / destruction:
public:
	explicit HttpRequestRedirectInformationProperty (const HttpRequestRedirectInformation& value);

	virtual ~HttpRequestRedirectInformationProperty ();
};

////////////////////////////////////////////////////////////////////////////////
// HttpRequestRedirectInformation inlines

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		HttpRequestRedirectInformation::operator == (const HttpRequestRedirectInformation& rhs) const
{
	if (this != &rhs) {
		return (m_originalRequestUrl.IsEqual (rhs.m_originalRequestUrl, GS::CaseInsensitive) &&
				m_finalRequestUrl.IsEqual (rhs.m_finalRequestUrl, GS::CaseInsensitive));
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetOriginalRequestUrl
// -----------------------------------------------------------------------------

inline const GS::UniString&		HttpRequestRedirectInformation::GetOriginalRequestUrl () const
{
	return m_originalRequestUrl;
}

// -----------------------------------------------------------------------------
// GetFinalRequestUrl
// -----------------------------------------------------------------------------

inline const GS::UniString&		HttpRequestRedirectInformation::GetFinalRequestUrl () const
{
	return m_finalRequestUrl;
}

////////////////////////////////////////////////////////////////////////////////
// HttpRequestRedirectInformationProperty inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline HttpRequestRedirectInformationProperty::HttpRequestRedirectInformationProperty (const HttpRequestRedirectInformation& value) :
	GenericPropertyObject (value)
{
}

}
}
}
}

#endif // COMMUNICATION_CLIENT_HTTP_HTTPPROPERTIES_HTTPREQUESTREDIRECTINFORMATION_HPP