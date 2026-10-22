
// *****************************************************************************
//
// Declaration of HeaderFieldName class
//
// Module:			HTTP
// Namespace:		HTTP::MessageHeader
// Contact person:	KOVA
//
// ***************************************************************************** 

#ifndef HTTP_MESSAGEHEADER_HEADERFIELDNAME_HPP
#define HTTP_MESSAGEHEADER_HEADERFIELDNAME_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/HTTPExport.hpp"


namespace HTTP {
namespace MessageHeader {

class HTTP_API HeaderFieldName {

public:

	// General fields
	static const char* CacheControl;
	static const char* Connection;
	static const char* Date;
	static const char* Pragma;
	static const char* Trailer;
	static const char* TransferEncoding;
	static const char* Upgrade;
	static const char* Via;
	static const char* Warning;

	// Request fields
	static const char* Accept;
	static const char* AcceptCharset;
	static const char* AcceptEncoding;
	static const char* AcceptLanguage;
	static const char* Authorization;
	static const char* Expect;
	static const char* From;
	static const char* Host;
	static const char* IfMatch;
	static const char* IfModifiedSince;
	static const char* IfNoneMatch;
	static const char* IfRange;
	static const char* IfUnmodifiedSince;
	static const char* MaxForwards;
	static const char* ProxyAuthorization;
	static const char* Range;
	static const char* Referer;
	static const char* TE;
	static const char* UserAgent;

	// Response fields
	static const char* AcceptRanges;
	static const char* Age;
	static const char* ETag;
	static const char* Location;
	static const char* ProxyAuthenticate;
	static const char* RetryAfter;
	static const char* Server;
	static const char* Vary;
	static const char* WWWAuthenticate;

	// Entity fields
	static const char* Allow;
	static const char* ContentLanguage;
	static const char* ContentLength;
	static const char* ContentLocation;
	static const char* ContentMD5;
	static const char* ContentRange;
	static const char* ContentType;
	static const char* Expires;

	// Request and entity header field
	static const char* ContentEncoding;

	// Response and entity header field
	static const char* LastModified;

	// WebDav fields
	static const char* AllowRename;
	static const char* Brief;
	static const char* CallBack;
	static const char* DAV;
	static const char* Depth;
	static const char* Destination;
	static const char* If;
	static const char* LockToken;
	static const char* NotificationDelay;
	static const char* NotificationType;
	static const char* Overwrite;
	static const char* StatusURI;
	static const char* SubscriptionID;
	static const char* SubscriptionLifetime;
	static const char* Timeout;
	static const char* Transaction;

};

}
}

#endif
