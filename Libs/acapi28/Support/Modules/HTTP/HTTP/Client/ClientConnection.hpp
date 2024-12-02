// *****************************************************************************
//
// Declaration of ClientConnection class
//
// Module:			HTTP
// Namespace:		HTTP::Client
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_CLIENT_CLIENTCONNECTION_HPP
#define HTTP_CLIENT_CLIENTCONNECTION_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/HTTPExport.hpp"
#include "HTTP/HTTPException.hpp"
#include "HTTP/Client/Request.hpp"
#include "HTTP/Client/Response.hpp"
#include "HTTP/Client/Authentication/Authentication.hpp"
#include "HTTP/Client/Redirect/RedirectManager.hpp"
#include "HTTP/Common/Channels/CountingIBinaryChannel.hpp"
#include "HTTP/Common/Channels/CountingOBinaryChannel.hpp"
#include "HTTP/Common/HostPatternList.hpp"
#include "HTTP/MessageHeader/Method.hpp"
#include "HTTP/Encoding/BodyIBinaryChannel.hpp"
#include "HTTP/Encoding/BodyOBinaryChannel.hpp"
#include "HTTP/Encoding/RereadableIBinaryChannel.hpp"

#include "ClientSecureChannel.hpp"
#include "ClientSecureChannelParameter.hpp"

#include "URI.hpp"
#include "IBinaryChannel.hpp"
#include "OBinaryChannel.hpp"
#include "Socket.hpp"


namespace HTTP {
namespace Client {

class HTTP_API ClientConnection {

public:
	static const UShort		DefaultHTTPPort = 80;
	static const UShort		DefaultHTTPSPort = 443;
	static const ULong		DefaultIdleTimeOut = 15000;
	static const ULong		DefaultServiceUnavailableRetryInterval = 100;

private:
	class ConnectionStatus {

	public:
		enum Status {
			Connected,
			Sending,
			Receiving,
			Closed,
			Aborted
		};
	};

	class ProxyType {

	public:
		enum Type {
			NoProxy,
			ManualProxy,
			SystemProxy
		};
	};

	IO::URI::URI													m_connectionUrl;
	GS::UniString													m_proxyHost;
	UShort															m_proxyPort;
	Network::Socket::SocketRef										m_socket;
	HTTP::Common::Channels::CountingIBinaryChannelRef				m_socketCountingIChannel;
	HTTP::Common::Channels::CountingOBinaryChannelRef				m_socketCountingOChannel;
	GS::UInt64														m_dataReceived;
	GS::UInt64														m_dataSent;
	GS::IBinaryChannelRef											m_socketBufferedIChannel;
	GS::OBinaryChannelRef											m_socketBufferedOChannel;
	SecureCommunication::Client::ClientSecureChannelRef				m_secureChannel;
	Int32															m_secureChannelLastVerifyResult;
	SecureCommunication::Client::ClientSecureChannelParameterRef	m_secureChannelParameter;
	bool															m_proxyConnection;
	HTTP::Encoding::RereadableIBinaryChannel						m_rereadableIBinaryChannel;
	HTTP::Encoding::BodyOBinaryChannel								m_bodyOBinaryChannel;
	HTTP::Encoding::BodyIBinaryChannel								m_bodyIBinaryChannel;
	ConnectionStatus::Status										m_connectionStatus;
	Authentication::AuthenticationRef								m_authentication;
	Authentication::AuthenticationRef								m_proxyAuthentication;
	bool															m_authenticationAllowed;
	bool															m_responseBodyAllowed;
	bool															m_closeConnection;
	bool															m_followRedirect;
	UInt32															m_maximumRedirection;
	Redirect::RedirectManagerRef									m_redirectManager;
	Request															m_lastRequest;
	IO::URI::URI													m_lastSentRequestUri;
	bool															m_keepAlive;
	bool															m_sendConnection;
	bool															m_defaultPersistentConnection;
	ULong															m_timeOut;
	ULong															m_idleTimeOut;
	ULong															m_serviceUnavailableRetryInterval;
	UInt64															m_lastActivity;
	ProxyType::Type													m_proxyType;
	HTTP::Common::HostPatternListRef								m_byPassPatternList;
	bool															m_httpsConnectInProgress;
	bool															m_logCallStack;

public:
	ClientConnection (const IO::URI::URI& connectionUrl);
	ClientConnection (const IO::URI::URI& connectionUrl, bool useSystemProxy);
	ClientConnection (const IO::URI::URI& connectionUrl, const GS::UniString& proxyHost, UShort proxyPort = 0, const GS::UniString byPass = "localhost");
	virtual ~ClientConnection ();

private:
	ClientConnection (const ClientConnection& source);				// disabled
	ClientConnection&	operator= (const ClientConnection& source);	// disabled

public:
	void					Connect ();
	void					Abort ();
	void					Close (bool forceCloseSocket);

	void					SetKeepAlive (bool keepAlive);
	bool					GetKeepAlive () const;
	void					SetSendConnection (bool sendConnection);
	bool					GetSendConnection () const;

	void					SetDefaultPersistentConnection (bool defaultPersistentConnection);
	bool					GetDefaultPersistentConnection () const;

	void					SetTimeout (ULong timeOut);
	ULong					GetTimeout () const;
	void					SetIdleTimeOut (ULong idleTimeOut);
	ULong					GetIdleTimeOut () const;
	void					SetServiceUnavailableRetryInterval (ULong serviceUnavailableRetryInterval);
	ULong					GetServiceUnavailableRetryInterval () const;
	UInt64					GetLastActivity () const;

	const IO::URI::URI&		GetConnectionUrl () const;
	UShort					GetPort () const;

	void					SetProxyHost (const GS::UniString& proxyHost);
	GS::UniString			GetProxyHost () const;
	void					SetProxyPort (UShort proxyPort);
	UShort					GetProxyPort () const;

	Network::Socket::InternetAddressRef		GetLocalInternetAddress () const;
	UShort					GetLocalPort () const;
	Network::Socket::InternetAddressRef		GetRemoteInternetAddress () const;
	GS::UniString			GetRemoteHost () const;
	UShort					GetRemotePort () const;

	void					SetSecureConnection (bool secureConnection);
	bool					IsSecureConnection () const;
	void					SetSecureChannelParameter (SecureCommunication::Client::ClientSecureChannelParameterRef secureChannelParameter);
	SecureCommunication::Client::ClientSecureChannelParameterRef	GetSecureChannelParameter ();
	Int32					GetVerifyResult ();

	UInt64					GetReceivedDataCount ();
	UInt64					GetSentDataCount ();

	void					SetBodyBufferSize (GS::USize maxBodyBufferSize);
	GS::USize 				GetBodyBufferSize () const;

	void										SetAuthentication (const Authentication::AuthenticationRef& authentication);
	const Authentication::AuthenticationRef&	GetAuthentication () const;
	void										RemoveAuthentication ();

	void										SetProxyAuthentication (const Authentication::AuthenticationRef& proxyAuthentication);
	const Authentication::AuthenticationRef&	GetProxyAuthentication () const;
	void										RemoveProxyAuthentication ();

	void								SetFollowRedirect (bool followRedirect);
	bool								GetFollowRedirect ();
	void								SetMaximumRedirection (UInt32 maximumRedirection);
	UInt32								GetMaximumRedirection ();
	void								SetRedirectManager (const Redirect::RedirectManagerRef& redirectManager);
	const Redirect::RedirectManagerRef&	GetRedirectManager () const;
	void								RemoveRedirectManager ();

	void								Send (Request& request);
	void								Send (Request& request, const char* body, USize length);
	HTTP::Encoding::BodyOBinaryChannel&	BeginSend (Request& request);
	void								FinishSend ();
	
	void								Receive (Response& response);
	HTTP::Encoding::BodyIBinaryChannel&	BeginReceive (Response& response);
	void								FinishReceive ();

	bool								GetCallStackLogEnable () const;
	void								SetCallStackLogEnable (bool enabled);

private:
	void								SetCommonRequestHeaderFields (Request& request);
	void								SendRequestHeader (Request& request);
	bool								StoreLastRequest ();
	void								ResendModifiedLastRequest (Response& response, bool sentBody = true);
	void								ReceiveResponseHeader (Response& response);
	void								ReceiveFinalResponseHeader (Response& response, bool bodySent = true);
	void								ReceiveExpectResponse ();
	GS::IBinaryChannel&					GetNetworkIBinaryChannel ();
	GS::OBinaryChannel&					GetNetworkOBinaryChannel ();
	void								ResetChannels ();
	void								CloseSocket (bool forceCloseSocket);
	Redirect::RedirectManager*			GetUsedRedirectManager ();
	void								WriteRequestHeader (Request& request, HTTP::MessageHeader::RequestHeaderFieldCollection requestHeaderFieldCollection);
	UShort								GetPortWithDefaultPortSolution (UShort port) const;

	GS::UniString						GetProxyConnectionLog ();
	GS::UniString						GetProxyTypeLog ();
};

typedef GS::Ref<ClientConnection, GS::Counter> ClientConnectionRef;

// -----------------------------------------------------------------------------
// SetKeepAlive
// -----------------------------------------------------------------------------

inline void ClientConnection::SetKeepAlive (bool keepAlive)
{
	m_keepAlive = keepAlive;
}

// -----------------------------------------------------------------------------
// GetKeepAlive
// -----------------------------------------------------------------------------

inline bool ClientConnection::GetKeepAlive () const
{
	return m_keepAlive;
}

// -----------------------------------------------------------------------------
// SetSendConnection
// -----------------------------------------------------------------------------

inline void ClientConnection::SetSendConnection (bool sendConnection)
{
	m_sendConnection = sendConnection;
}

// -----------------------------------------------------------------------------
// GetSendConnection
// -----------------------------------------------------------------------------

inline bool ClientConnection::GetSendConnection () const
{
	return m_sendConnection;
}

// -----------------------------------------------------------------------------
// SetDefaultPersistentConnection
// -----------------------------------------------------------------------------

inline void		ClientConnection::SetDefaultPersistentConnection (bool defaultPersistentConnection)
{
	m_defaultPersistentConnection = defaultPersistentConnection;
}

// -----------------------------------------------------------------------------
// GetDefaultPersistentConnection
// -----------------------------------------------------------------------------

inline bool		ClientConnection::GetDefaultPersistentConnection () const
{
	return m_defaultPersistentConnection;
}

// -----------------------------------------------------------------------------
// GetConnectionUrl
// -----------------------------------------------------------------------------

inline const IO::URI::URI&	ClientConnection::GetConnectionUrl () const
{
	return m_connectionUrl;
}

// -----------------------------------------------------------------------------
// GetPort
// -----------------------------------------------------------------------------

inline UShort ClientConnection::GetPort () const
{
	return GetPortWithDefaultPortSolution (m_connectionUrl.GetPort ());
}

// -----------------------------------------------------------------------------
// SetProxyHost
// -----------------------------------------------------------------------------

inline void ClientConnection::SetProxyHost (const GS::UniString& proxyHost)
{
	m_proxyHost = proxyHost;
}

// -----------------------------------------------------------------------------
// GetProxyHost
// -----------------------------------------------------------------------------

inline GS::UniString ClientConnection::GetProxyHost () const
{
	return m_proxyHost;
}

// -----------------------------------------------------------------------------
// SetProxyPort
// -----------------------------------------------------------------------------

inline void ClientConnection::SetProxyPort (UShort proxyPort)
{
	m_proxyPort = proxyPort;
}

// -----------------------------------------------------------------------------
// GetProxyPort
// -----------------------------------------------------------------------------

inline UShort ClientConnection::GetProxyPort () const
{
	if (m_proxyPort == 0 && m_proxyHost.IsEmpty ()) {
		return 0;
	}

	return GetPortWithDefaultPortSolution (m_proxyPort);
}

// -----------------------------------------------------------------------------
// SetSecureConnection
// -----------------------------------------------------------------------------

inline void  ClientConnection::SetSecureConnection (bool secureConnection)
{
	m_connectionUrl.SetScheme (secureConnection ? "https" : "http");
}

// -----------------------------------------------------------------------------
// IsSecureConnection
// -----------------------------------------------------------------------------

inline bool  ClientConnection::IsSecureConnection () const
{
	return m_connectionUrl.GetScheme ().IsEqual ("https", GS::CaseInsensitive);
}

// -----------------------------------------------------------------------------
// SetSecureChannelParameter
// -----------------------------------------------------------------------------

inline void	ClientConnection::SetSecureChannelParameter (SecureCommunication::Client::ClientSecureChannelParameterRef secureChannelParameter)
{
	m_secureChannelParameter = secureChannelParameter;
}

// -----------------------------------------------------------------------------
// GetSecureChannelParameter
// -----------------------------------------------------------------------------

inline SecureCommunication::Client::ClientSecureChannelParameterRef	ClientConnection::GetSecureChannelParameter ()
{
	return m_secureChannelParameter;
}

}
}

#endif
