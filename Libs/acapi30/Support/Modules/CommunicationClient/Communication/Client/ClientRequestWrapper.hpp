
// *****************************************************************************
//
// Declaration of ClientRequestWrapper class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTREQUESTWRAPPER_HPP
#define COMMUNICATION_CLIENT_CLIENTREQUESTWRAPPER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientRequest.hpp"



// --- ClientRequestWrapper class ----------------------------------------------

namespace Communication {
namespace Client {

class COMMUNICATIONCLIENT_API ClientRequestWrapper : public ClientRequest {

// Data members:
protected:
	ClientRequestRef							m_requestRef;
	ClientRequest*								m_request;

// Construction / destruction:
public:
	explicit ClientRequestWrapper (const ClientRequestRef& request);
	explicit ClientRequestWrapper (ClientRequest& request);

// ClientRequest interface implementation:
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

	virtual bool								IsStarted () const override;
	virtual bool								IsAborted () const override;
	virtual bool								IsEnded () const override;

	virtual void								Start () override;
	virtual void								Abort (const GS::UniString& message = GS::UniString ()) override;
	virtual void								End () override;

// Operations:
public:
	const ClientRequest&						GetRequest () const;
	ClientRequest&								GetRequest ();

};

////////////////////////////////////////////////////////////////////////////////
// ClientRequestWrapper inlines

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetRequest
// -----------------------------------------------------------------------------

inline const ClientRequest&		ClientRequestWrapper::GetRequest () const
{
	return (*m_request);
}

// -----------------------------------------------------------------------------
// GetRequest
// -----------------------------------------------------------------------------

inline ClientRequest&	ClientRequestWrapper::GetRequest ()
{
	return (*m_request);
}

}
}

#endif // COMMUNICATION_CLIENT_CLIENTREQUESTWRAPPER_HPP