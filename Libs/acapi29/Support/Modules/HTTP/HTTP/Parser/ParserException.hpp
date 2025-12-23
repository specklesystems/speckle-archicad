// *****************************************************************************
//
// Declaration of ParserException class
//
// Module:			HTTP
// Namespace:		HTTP::Parser
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_PARSER_PARSEREXCEPTION_HPP
#define HTTP_PARSER_PARSEREXCEPTION_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/HTTPExport.hpp"
#include "HTTP/HTTPException.hpp"
#include "HTTP/Parser/ParserError.hpp"
	

namespace HTTP {
namespace Parser {

class HTTP_API ParserException : public HTTP::HTTPException {

private:
	GS::UInt32				m_errorCode;
	GS::UInt32				m_position;

public:
	ParserException (ParserError::Error errorCode, UInt32 position, const char* sourceFile, UInt32 sourceLine, const GS::Exception& cause = GS::NoCauseException);

public:
	inline UInt32			GetErrorCode () const;
	inline USize 			GetPosition () const;

	virtual GS::Exception*	Clone () const override;

};

// -----------------------------------------------------------------------------
// GetErrorCode
// -----------------------------------------------------------------------------

inline GS::UInt32 ParserException::GetErrorCode () const
{
	return m_errorCode;
}

// -----------------------------------------------------------------------------
// GetPosition
// -----------------------------------------------------------------------------

inline GS::UInt32 ParserException::GetPosition () const
{
	return m_position;
}

}
}

#endif
