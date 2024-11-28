
// *****************************************************************************
//
// Declaration of ClientConnectionWrapper class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTCONNECTIONWRAPPER_HPP
#define COMMUNICATION_CLIENT_CLIENTCONNECTIONWRAPPER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientConnection.hpp"



// --- ClientConnectionWrapper class --------------------------------------------------

namespace Communication {
namespace Client {

class COMMUNICATIONCLIENT_API ClientConnectionWrapper: public ClientConnection {

// Data members:
protected:
	ClientConnectionRef						m_connectionRef;
	ClientConnection*						m_connection;

// Construction / destruction:
public:
	explicit ClientConnectionWrapper (const ClientConnectionRef& connection);
	explicit ClientConnectionWrapper (ClientConnection& connection);

// ClientConnection interface implementation:
public:
	virtual GS::UniString					GetConnectionUri () const override;

	virtual const Address&					GetRemoteAddress () const override;
	virtual const Address&					GetLocalAddress () const override;

	virtual const ClientSslSessionRef		GetSslSession () const override;


	virtual GS::USize						GetResponseFilters (GS::PagedArray<ClientResponseFilterRef>& responseFilters) const override;

	virtual GS::USize						GetResponseFilterCount () const override;

	virtual const ClientResponseFilterRef&	GetResponseFilter (GS::UIndex index) const override;

	virtual void							InsertResponseFilter (GS::UIndex index, const ClientResponseFilterRef& responseFilter) override;
	virtual void							AppendResponseFilter (const ClientResponseFilterRef& responseFilter) override;
	virtual bool							RemoveResponseFilter (const ClientResponseFilterRef& responseFilter) override;
	virtual void							RemoveResponseFilter (GS::UIndex index) override;
	
	virtual void							ClearResponseFilters () override;


	virtual GS::USize						GetRequestFilters (GS::PagedArray<ClientRequestFilterRef>& requestFilters) const override;

	virtual GS::USize						GetRequestFilterCount () const override;

	virtual const ClientRequestFilterRef&	GetRequestFilter (GS::UIndex index) override;

	virtual void							InsertRequestFilter (GS::UIndex index, const ClientRequestFilterRef& requestFilter) override;
	virtual void							AppendRequestFilter (const ClientRequestFilterRef& requestFilter) override;
	virtual bool							RemoveRequestFilter (const ClientRequestFilterRef& requestFilter) override;
	virtual void							RemoveRequestFilter (GS::UIndex index) override;
	
	virtual void							ClearRequestFilters () override;

	virtual void							AppendFilterSet (const ClientFilterSet& filterSet) override;
	virtual void							RemoveFilterSet (const ClientFilterSet& filterSet) override;


	virtual ClientResponseRef				CreateResponse () const override;
	virtual ClientRequestRef				CreateRequest () const override;


	virtual void							StartResponse (ClientResponse& response, MessageContentIBinaryChannelRef& rawContentChannel, MessageContentIBinaryChannelRef& contentChannel) override;
	virtual void							EndResponse (ClientResponse& response) override;

	virtual bool							IsRequestAbortable (const ClientRequest& request) const override;

	virtual void							StartRequest (ClientRequest& request, MessageContentOBinaryChannelRef& rawContentChannel, MessageContentOBinaryChannelRef& contentChannel) override;
	virtual void							AbortRequest (ClientRequest& request, const GS::UniString& message = GS::UniString ()) override;
	virtual void							EndRequest (ClientRequest& request) override;

	virtual ClientResponseRef				GetResponse () override;
	virtual void							Receive (const ClientResponseRef& response) override;
	virtual void							Send (const ClientRequestRef& request) override;


	virtual void							GetStatistics (ClientConnectionStatistics& statistics) const override;


	virtual bool							IsAttached (ClientConnectionProgressListener* listener) const override;

	virtual bool							Attach (ClientConnectionProgressListener* listener) override;
	virtual bool							Detach (ClientConnectionProgressListener* listener) override;


	virtual void							SetTimeout (GS::UInt32 timeout) override;
	virtual GS::UInt32						GetTimeout () override;


	virtual bool							IsClosed () const override;
	virtual void							Close () override;

// Operations:
public:
	const ClientConnection&					GetConnection () const;
	ClientConnection&						GetConnection ();

};

typedef GS::Ref<ClientConnectionWrapper, GS::AtomicCounter> ClientConnectionWrapperRef;

////////////////////////////////////////////////////////////////////////////////
// ClientConnectionWrapper inlines

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetConnection
// -----------------------------------------------------------------------------

inline const ClientConnection&	ClientConnectionWrapper::GetConnection () const
{
	return (*m_connection);
}

// -----------------------------------------------------------------------------
// GetConnection
// -----------------------------------------------------------------------------

inline ClientConnection&	ClientConnectionWrapper::GetConnection ()
{
	return (*m_connection);
}

}
}

#endif // COMMUNICATION_CLIENT_CLIENTCONNECTIONWRAPPER_HPP