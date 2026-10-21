
// *****************************************************************************
//
// Declaration of ResponseHeaderFieldCollection class
//
// Module:			HTTP
// Namespace:		HTTP::MessageHeader
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_MESSAGEHEADER_RESPONSEHEADERFIELDCOLLECTION_HPP
#define HTTP_MESSAGEHEADER_RESPONSEHEADERFIELDCOLLECTION_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/MessageHeader/HeaderFieldCollection.hpp"

#include "PagedArray.hpp"


namespace HTTP {
namespace MessageHeader {

class HTTP_API ResponseHeaderFieldCollection: public HeaderFieldCollection {

public:
	ResponseHeaderFieldCollection ();
	virtual ~ResponseHeaderFieldCollection ();

};

}
}

#endif
