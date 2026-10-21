
// *****************************************************************************
//
// Declaration of HttpClientResponseWrapper class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_HTTP_HTTPCLIENTRESPONSEWRAPPER_HPP
#define COMMUNICATION_CLIENT_HTTP_HTTPCLIENTRESPONSEWRAPPER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/Http/HttpClientResponse.hpp"



// --- HttpClientResponseWrapper class -----------------------------------------

namespace Communication {
namespace Client {
namespace Http {

class COMMUNICATIONCLIENT_API HttpClientResponseWrapper : public HttpClientResponse {

// Data members:
protected:
	HttpClientResponseRef						m_responseRef;
	HttpClientResponse*							m_response;

// Construction / destruction:
public:
	explicit HttpClientResponseWrapper (const HttpClientResponseRef& response);
	explicit HttpClientResponseWrapper (HttpClientResponse& response);

// HttpClientResponse interface implementation:
public:
	virtual const ClientConnectionRef&			GetConnection () const override;

	virtual void								SetId (const GS::UniString& id) override;
	virtual const GS::UniString&				GetId () const override;

	virtual GS::USize							GetParameterCount () const override;

	virtual bool								GetFirstParameter (const GS::UniString& parameterName, Parameter& parameter) const override;
	virtual bool								GetLastParameter (const GS::UniString& parameterName, Parameter& parameter) const override;

	virtual ConstParameterIterator				GetParameters (const GS::UniString& parameterName) const override;
	virtual ConstParameterIterator				GetParameters () const override;

	virtual bool								RemoveParameters (const GS::UniString& parameterName) override;
	virtual bool								RemoveParameter (const Parameter& parameter) override;

	virtual void								AddParameter (const GS::UniString& parameterName, const GS::UniString& parameterValue) override;
	virtual void								AddParameter (const Parameter& parameter) override;

	virtual void								SetParameter (const GS::UniString& parameterName, const GS::UniString& parameterValue) override;
	virtual void								SetParameter (const Parameter& parameter) override;

	virtual void								ClearParameters () override;

	virtual GS::USize							GetHeaderCount () const override;

	virtual bool								GetFirstHeader (const GS::UniString& headerName, Header& header) const override;
	virtual bool								GetLastHeader (const GS::UniString& headerName, Header& header) const override;

	virtual ConstHeaderIterator					GetHeaders (const GS::UniString& headerName) const override;
	virtual ConstHeaderIterator					GetHeaders () const override;

	virtual bool								RemoveHeaders (const GS::UniString& headerName) override;
	virtual bool								RemoveHeader (const Header& header) override;

	virtual void								AddHeader (const GS::UniString& headerName, const GS::UniString& headerValue) override;
	virtual void								AddHeader (const Header& header) override;

	virtual void								SetHeader (const GS::UniString& headerName, const GS::UniString& headerValue) override;
	virtual void								SetHeader (const Header& header) override;

	virtual void								ClearHeaders () override;

	virtual MessageContentIBinaryChannelRef		GetRawContentChannel () override;
	virtual MessageContentIBinaryChannelRef		GetContentChannel () override;

	virtual void								SetStatusLine (const StatusLine& statusLine) override;
	virtual const StatusLine&					GetStatusLine () const override;

	virtual bool								IsStarted () const override;
	virtual bool								IsEnded () const override;

	virtual void								Start () override;
	virtual void								End () override;

// Operations:
public:
	const HttpClientResponse&					GetResponse () const;
	HttpClientResponse&							GetResponse ();

};

////////////////////////////////////////////////////////////////////////////////
// HttpClientResponseWrapper inlines

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetResponse
// -----------------------------------------------------------------------------

inline const HttpClientResponse&	HttpClientResponseWrapper::GetResponse () const
{
	return (*m_response);
}

// -----------------------------------------------------------------------------
// GetResponse
// -----------------------------------------------------------------------------

inline HttpClientResponse&	HttpClientResponseWrapper::GetResponse ()
{
	return (*m_response);
}

}
}
}

#endif // COMMUNICATION_CLIENT_HTTP_HTTPCLIENTRESPONSEWRAPPER_HPP