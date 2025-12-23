
// *****************************************************************************
//
// Declaration of ParserError class
//
// Module:			HTTP
// Namespace:		HTTP::Parser
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_PARSER_PARSERERROR_HPP
#define HTTP_PARSER_PARSERERROR_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/HTTPExport.hpp"

#include "UniString.hpp"


namespace HTTP {
namespace Parser {


class HTTP_API ParserError {

public:

	enum Error {
		OK							= 0,

		ResponseNotAllowed			= 100,
		RequestNotAllowed			= 101,
		CallbackMessageBegin		= 102,
		CallbackMethod				= 103,
		CallbackPath				= 104,
		CallbackQueryString			= 105,
		CallbackURL					= 106,
		CallbackResponseVersion		= 107,
		CallbackRequestVersion		= 108,
		CallbackStatusCode			= 109,
		CallbackFragment			= 110,
		InvalidVersion				= 111,
		InvalidStatus				= 112,
		InvalidMethod				= 113,
		InvalidURL					= 114,
		InvalidHost					= 115,
		InvalidPort					= 116,
		InvalidPath					= 117,
		InvalidQueryString			= 118,
		InvalidFragment				= 119,
		LFExpectedRequestStartLine	= 120,
		InvalidConstantStartLine1	= 121,
		InvalidConstantStartLine2	= 122,
		InvalidConstantStartLine3	= 123,

		CallbackHeaderField			= 200,
		CallbackHeaderValue			= 202,
		CallbackHeaderComplete		= 203,
		HeaderOverflow				= 204,
		InvalidHeaderToken			= 205,
		InvalidContentLength		= 206,
		InvalidValueQuality			= 207,
		InvalidDecimalValue			= 208,
		InvalidRange				= 209,
		InvalidContentRange			= 210,

		CallbackBody				= 300,
		InvalidChunkSize			= 301,
		InvalidChunkBodyTooLong		= 302,
		InvalidChunkInfo			= 303,
		InvalidChunkExtension		= 304,
		InvalidInternalState		= 305,
		InvalidChunkTrailer			= 306,

		CallbackMessageComplete		= 400,
		InvalidEOFState				= 401,
		ER_CLOSED_CONNECTION		= 402,

		Strict						= 500,

		Unknown						= 600
	};

	static GS::UniString ToString (Error error);

};

}
}

#endif
