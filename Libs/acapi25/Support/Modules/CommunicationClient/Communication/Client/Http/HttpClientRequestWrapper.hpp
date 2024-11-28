
// *****************************************************************************
//
// Declaration of HttpClientRequestWrapper class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_HTTP_HTTPCLIENTREQUESTWRAPPER_HPP
#define COMMUNICATION_CLIENT_HTTP_HTTPCLIENTREQUESTWRAPPER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/Http/HttpClientRequest.hpp"



// --- HttpClientRequestWrapper class ------------------------------------------

namespace Communication {
namespace Client {
namespace Http {

class COMMUNICATIONCLIENT_API HttpClientRequestWrapper : public HttpClientRequest {

// Data members:
protected:
	HttpClientRequestRef						m_requestRef;
	HttpClientRequest*							m_request;

// Construction / destruction:
public:
	explicit HttpClientRequestWrapper (const HttpClientRequestRef& request);
	explicit HttpClientRequestWrapper (HttpClientRequest& request);

// HttpClientRequest interface implementation:
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

	virtual MessageContentOBinaryChannelRef		GetRawContentChannel () override;
	virtual MessageContentOBinaryChannelRef		GetContentChannel () override;

	virtual void								SetContent (const MessageContentRef& content) override;
	virtual const MessageContentRef&			GetContent () const override;

	virtual void								SetRequestLine (const RequestLine& requestLine) override;
	virtual const RequestLine&					GetRequestLine () const override;

	virtual bool								IsStarted () const override;
	virtual bool								IsAborted () const override;
	virtual bool								IsEnded () const override;

	virtual void								Start () override;
	virtual void								Abort (const GS::UniString& message) override;
	virtual void								End () override;

// Operations:
public:
	const HttpClientRequest&					GetRequest () const;
	HttpClientRequest&							GetRequest ();

};

////////////////////////////////////////////////////////////////////////////////
// HttpClientRequestWrapper inlines

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetRequest
// -----------------------------------------------------------------------------

inline const HttpClientRequest&		HttpClientRequestWrapper::GetRequest () const
{
	return (*m_request);
}

// -----------------------------------------------------------------------------
// GetRequest
// -----------------------------------------------------------------------------

inline HttpClientRequest&	HttpClientRequestWrapper::GetRequest ()
{
	return (*m_request);
}

}
}
}

#endif // COMMUNICATION_CLIENT_HTTP_HTTPCLIENTREQUESTWRAPPER_HPP