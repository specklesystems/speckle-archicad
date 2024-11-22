
// *****************************************************************************
//
// Declaration of RedirectManager class
//
// Module:			HTTP
// Namespace:		HTTP::Client::Redirect
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_CLIENT_REDIRECT_REDIRECTMANAGER_HPP
#define HTTP_CLIENT_REDIRECT_REDIRECTMANAGER_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/Client/Redirect/RedirectException.hpp"
#include "HTTP/HTTPExport.hpp"

#include "Ref.hpp"
#include "UniString.hpp"


namespace HTTP {
namespace Client {
	class ClientConnection;
	class Request;
	class Response;
}
}

namespace HTTP {
namespace Client {
namespace Redirect {

struct HTTP_API RedirectInformation {

public:
	IO::URI::URI	newRequestUrl;
};

class HTTP_API RedirectManager
{

public:
	RedirectManager ();
	virtual ~RedirectManager ();

	virtual void	PreSend (HTTP::Client::Request& request, HTTP::Client::ClientConnection& connection) = 0;
	virtual bool	RedirectNeccessary (const HTTP::Client::Request& request, HTTP::Client::Response& response, HTTP::Client::ClientConnection& connection) = 0;
	virtual void	CreateRedirectRequest (HTTP::Client::Request& request, HTTP::Client::Response& response, HTTP::Client::ClientConnection& connection, RedirectInformation& redirectInformation) = 0;

protected:
	virtual bool	GetNewDestinationFromLocation (HTTP::Client::Response& response, HTTP::Client::ClientConnection& connection, RedirectInformation& redirectInformation);

};

typedef GS::Ref<RedirectManager, GS::AtomicCounter> RedirectManagerRef;

}
}
}

#endif