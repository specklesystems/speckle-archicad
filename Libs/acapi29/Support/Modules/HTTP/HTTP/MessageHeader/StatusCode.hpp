
// *****************************************************************************
//
// Declaration of StatusCode class
//
// Module:			HTTP
// Namespace:		HTTP::MessageHeader
// Contact person:	KOVA
//
// ***************************************************************************** 

#ifndef HTTP_MESSAGEHEADER_STATUSCODE_HPP
#define HTTP_MESSAGEHEADER_STATUSCODE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/HTTPExport.hpp"

#include "UniString.hpp"


namespace HTTP {
namespace MessageHeader {

class HTTP_API StatusCode 
{

public:
	enum Id
	{
		Unknown							= 0,

		Continue						= 100,
		SwitchingProtocols				= 101,
		Processing						= 102,

		OK								= 200,
		Created							= 201,
		Accepted						= 202,
		NonAuthoritativeInformation		= 203,
		NoContent						= 204,
		ResetContent					= 205,
		PartialContent					= 206,
		MultiStatus						= 207,
		AlreadyReported					= 208,
		ContentDifferent				= 210,
		IMUsed							= 226,

		MultipleChoices					= 300,		// Ambiguous
		MovedPermanently				= 301,		// Moved
		Found							= 302,		// Redirect, MovedTemporarily
		SeeOther						= 303,		// RedirectMethod
		NotModified						= 304,
		UserProxy						= 305,
		// UNUSED: 306
		TemporaryRedirect				= 307,		// RedirectKeepVerb

		BadRequest						= 400,
		Unauthorized					= 401,
		PaymentRequired					= 402,
		Forbidden						= 403,
		NotFound						= 404,
		MethodNotAllowed				= 405,
		NotAcceptable					= 406,
		ProxyAuthenticationRequired		= 407,
		RequestTimeout					= 408,
		Conflict						= 409,
		Gone							= 410,
		LengthRequired					= 411,
		PreconditionFailed				= 412,
		RequestEntityTooLarge			= 413,
		RequestURITooLong				= 414,
		UnsupportedMediaType			= 415,
		RequestedRangeNotSatisfiable	= 416,
		ExpectationFailed				= 417,
		UnprocessableEntity				= 422,
		Locked							= 423,
		MethodFailure					= 424,		// Failed Dependency
		UpgradeRequired					= 426,

		InternalServerError				= 500,
		NotImplemented					= 501,
		BadGateway						= 502,
		ServiceUnavailable				= 503,
		GatewayTimeout					= 504,
		VersionNotSupported				= 505,
		InsufficientStorage				= 507,
		LoopDetected					= 508

	};

	static const char*	ToString (Id statusCode);

	static bool			MustNotContainBody (Id statusCode);
};

}
}

#endif
