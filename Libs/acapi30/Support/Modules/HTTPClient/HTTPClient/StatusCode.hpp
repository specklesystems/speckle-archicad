// *****************************************************************************
//
// HTTPClient StatusCode
//
// Contact person: KI
//
// *****************************************************************************

#ifndef GS_HTTPCLIENT_STATUSCODE_HPP
#define GS_HTTPCLIENT_STATUSCODE_HPP

// from GSRoot
#include "Definitions.hpp"

// from HTTPClient
#include "Export.hpp"

namespace HTTPClient {

using StatusCodeT = UInt16;

enum class StandardStatusCode : StatusCodeT {
	Continue                                 = 100,
	Switchingprotocols                       = 101,
	Processing                               = 102,
	EarlyHints                               = 103,

	OK                                       = 200,
	Created                                  = 201,
	Accepted                                 = 202,
	NonAuthoritativeInformation              = 203,
	NoContent                                = 204,
	ResetContent                             = 205,
	PartialContent                           = 206,
	MultiStatus                              = 207,
	AlreadyReported                          = 208,
	IMUsed                                   = 226,

	MultipleChoices                          = 300,
	MovedPermanently                         = 301,
	Found                                    = 302,
	MovedTemporarily                         = 302,
	SeeOther                                 = 303,
	NotModified                              = 304,
	UseProxy                                 = 305,
	SwitchProxy                              = 306,
	TemporaryRedirect                        = 307,
	PermanentRedirect                        = 308,
	
	BadRequest                               = 400,
	Unauthorized                             = 401,
	PaymentRequired                          = 402,
	Forbidden                                = 403,
	NotFound                                 = 404,
	MethodNotAllowed                         = 405,
	NotAcceptable                            = 406,
	ProxyAuthenticationRequired              = 407,
	RequestTimeout                           = 408,
	Conflict                                 = 409,
	Gone                                     = 410,
	LengthRequired                           = 411,
	PreconditionFailed                       = 412,
	PayloadTooLarge                          = 413,
	URITooLong                               = 414,
	UnsupportedMediaType                     = 415,
	RangeNotSatisfiable                      = 416,
	ExpectationFailed                        = 417,
	ImaTeapot                                = 418,
	MisdirectedRequest                       = 421,
	UnprocessableEntity                      = 422,
	Locked                                   = 423,
	FailedDependency                         = 424,
	TooEarly                                 = 425,
	UpgradeRequired                          = 426,
	PreconditionRequired                     = 428,
	TooManyRequests                          = 429,
	RequestHeaderFieldsTooLarge              = 431,
	UnavailableForLegalReasons               = 451,

	InternalServerError                      = 500,
	NotImplemented                           = 501,
	BadGateway                               = 502,
	ServiceUnavailable                       = 503,
	GatewayTimeout                           = 504,
	HTTPVersionNotSupported                  = 505,
	VariantAlsoNegotiates                    = 506,
	InsufficientStorage                      = 507,
	LoopDetected                             = 508,
	NotExtended                              = 510,
	NetworkAuthenticationRequired            = 511,
};

class HTTPCLIENT_EXPORTED StatusCode {
public:
	StatusCode (StatusCodeT statusCode);
	StatusCode (StandardStatusCode);
	
	operator StandardStatusCode () const;
	operator StatusCodeT () const;

private:
	StatusCodeT m_statusCodeValue;
};

};	// namespace HTTPClient

#endif	// GS_HTTPCLIENT_STATUSCODE_HPP