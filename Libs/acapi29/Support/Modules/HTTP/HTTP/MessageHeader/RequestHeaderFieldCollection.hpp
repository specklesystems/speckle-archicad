
// *****************************************************************************
//
// Declaration of RequestHeaderFieldCollection class
//
// Module:			HTTP
// Namespace:		HTTP::MessageHeader
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_MESSAGEHEADER_REQUESTHEADERFIELDCOLLECTION_HPP
#define HTTP_MESSAGEHEADER_REQUESTHEADERFIELDCOLLECTION_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/MessageHeader/HeaderFieldCollection.hpp"


namespace HTTP {
namespace MessageHeader {

class HTTP_API RequestHeaderFieldCollection: public HeaderFieldCollection {

public:
	static const UShort		DefaultHostHTTPPort = 80;

public:
	RequestHeaderFieldCollection ();
	virtual ~RequestHeaderFieldCollection ();

	void	SetHost (GS::UniString host, UInt32 port = DefaultHostHTTPPort, bool overwrite = true);
	bool	GetHost (GS::UniString& host, UInt32& port) const;
	void	SetExpect100Continue ();
	bool	IsExpect100Continue () const;

};

}
}


#endif

