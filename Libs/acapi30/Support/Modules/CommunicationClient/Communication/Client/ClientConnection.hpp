
// *****************************************************************************
//
// Declaration of ClientConnection interface
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTCONNECTION_HPP
#define COMMUNICATION_CLIENT_CLIENTCONNECTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientConnectionAddressResolutionException.hpp"
#include "Communication/Client/ClientConnectionClosedException.hpp"
#include "Communication/Client/ClientConnectionConnectTimeoutException.hpp"
#include "Communication/Client/ClientConnectionFailedException.hpp"
#include "Communication/Client/ClientConnectionProgressListener.hpp"
#include "Communication/Client/ClientConnectionReadTimeoutException.hpp"
#include "Communication/Client/ClientConnectionStateException.hpp"
#include "Communication/Client/ClientConnectionStatistics.hpp"
#include "Communication/Client/ClientConnectionWriteTimeoutException.hpp"
#include "Communication/Client/ClientFilterSet.hpp"
#include "Communication/Client/ClientRequest.hpp"
#include "Communication/Client/ClientRequestFilter.hpp"
#include "Communication/Client/ClientResponse.hpp"
#include "Communication/Client/ClientResponseFilter.hpp"
#include "Communication/Client/ClientSslSession.hpp"

	// from CommunicationCommon
#include "Communication/Address.hpp"



// --- Forward declarations ----------------------------------------------------

namespace Communication {
namespace Client {

class ClientConnectionAccessor;
class ClientConnectionWrapper;

}
}



// --- ClientConnection class --------------------------------------------------

namespace Communication {
namespace Client {

class COMMUNICATIONCLIENT_API ClientConnection {

// Friend classes:
friend class ClientConnectionAccessor;
friend class ClientConnectionWrapper;

// Construction / destruction:
protected:
			 ClientConnection () = default;
			 ClientConnection (const ClientConnection&) = default;
public:
	virtual ~ClientConnection ();

// Operator overloading:
protected:
	ClientConnection&						operator = (const ClientConnection&) = default;

// Operations:
public:
	virtual GS::UniString					GetConnectionUri () const = 0;

	virtual const Address&					GetRemoteAddress () const = 0;
	virtual const Address&					GetLocalAddress () const = 0;

	virtual const ClientSslSessionRef		GetSslSession () const = 0;


	virtual GS::USize						GetResponseFilters (GS::PagedArray<ClientResponseFilterRef>& responseFilters) const = 0;

	virtual GS::USize						GetResponseFilterCount () const = 0;

	virtual const ClientResponseFilterRef&	GetResponseFilter (GS::UIndex index) const = 0;

	virtual void							InsertResponseFilter (GS::UIndex index, const ClientResponseFilterRef& responseFilter) = 0;
	virtual void							AppendResponseFilter (const ClientResponseFilterRef& responseFilter) = 0;
	virtual bool							RemoveResponseFilter (const ClientResponseFilterRef& responseFilter) = 0;
	virtual void							RemoveResponseFilter (GS::UIndex index) = 0;
	
	virtual void							ClearResponseFilters () = 0;


	virtual GS::USize						GetRequestFilters (GS::PagedArray<ClientRequestFilterRef>& requestFilters) const = 0;

	virtual GS::USize						GetRequestFilterCount () const = 0;

	virtual const ClientRequestFilterRef&	GetRequestFilter (GS::UIndex index) = 0;

	virtual void							InsertRequestFilter (GS::UIndex index, const ClientRequestFilterRef& requestFilter) = 0;
	virtual void							AppendRequestFilter (const ClientRequestFilterRef& requestFilter) = 0;
	virtual bool							RemoveRequestFilter (const ClientRequestFilterRef& requestFilter) = 0;
	virtual void							RemoveRequestFilter (GS::UIndex index) = 0;
	
	virtual void							ClearRequestFilters () = 0;

	
	virtual void							AppendFilterSet (const ClientFilterSet& filterSet);
	virtual void							RemoveFilterSet (const ClientFilterSet& filterSet);


	virtual ClientResponseRef				CreateResponse () const = 0;
	virtual ClientRequestRef				CreateRequest () const = 0;


	virtual ClientResponseRef				GetResponse () = 0;
	virtual void							Receive (const ClientResponseRef& response) = 0;
	virtual void							Send (const ClientRequestRef& request) = 0;


	virtual void							GetStatistics (ClientConnectionStatistics& statistics) const = 0;


	virtual bool							IsAttached (ClientConnectionProgressListener* listener) const = 0;

	virtual bool							Attach (ClientConnectionProgressListener* listener) = 0;
	virtual bool							Detach (ClientConnectionProgressListener* listener) = 0;


	virtual void							SetTimeout (GS::UInt32 timeout) = 0;
	virtual GS::UInt32						GetTimeout () = 0;


	virtual bool							IsClosed () const = 0;
	virtual void							Close () = 0;

// Implementation:
protected:
	virtual void							StartResponse (ClientResponse& response, MessageContentIBinaryChannelRef& rawContentChannel, MessageContentIBinaryChannelRef& contentChannel) = 0;
	virtual void							EndResponse (ClientResponse& response) = 0;

	virtual bool							IsRequestAbortable (const ClientRequest& request) const = 0;

	virtual void							StartRequest (ClientRequest& request, MessageContentOBinaryChannelRef& rawContentChannel, MessageContentOBinaryChannelRef& contentChannel) = 0;
	virtual void							AbortRequest (ClientRequest& request, const GS::UniString& message = GS::UniString ()) = 0;
	virtual void							EndRequest (ClientRequest& request) = 0;

};

typedef GS::Ref<ClientConnection, GS::AtomicCounter> ClientConnectionRef;

}
}

#endif // COMMUNICATION_CLIENT_CLIENTCONNECTION_HPP