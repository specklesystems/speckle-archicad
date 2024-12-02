
// *****************************************************************************
//
// Declaration of Method class
//
// Module:			HTTP
// Namespace:		HTTP::MessageHeader
// Contact person:	KOVA
//
// ***************************************************************************** 

#ifndef HTTP_MESSAGEHEADER_METHOD_HPP
#define HTTP_MESSAGEHEADER_METHOD_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/HTTPExport.hpp"

#include "UniString.hpp"


namespace HTTP {
namespace MessageHeader {

class HTTP_API Method {

public:

	enum Id {
		Delete,
		Get,
		Head,
		Post,
		Put,
		/* pathological */
		Connect,
		Options,
		Trace,
		/* webdav */
		Copy,
		Lock,
		MKCol,
		Move,
		PropFind,
		PropPatch,
		Unlock,

		Unknown
	};

	static const char* ToString (Id id);
};

}
}

#endif
