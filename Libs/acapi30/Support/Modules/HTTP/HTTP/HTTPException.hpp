
// *****************************************************************************
//
// Declaration of HTTP exception class
//
// Module:			HTTP
// Namespace:		HTTP
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_HTTPEXCEPTION_HPP
#define HTTP_HTTPEXCEPTION_HPP

// --------------------------------- Includes ----------------------------------

#include "HTTP/HTTPExport.hpp"

#include "GSException.hpp"


namespace HTTP {

DECLARE_EXCEPTION_CLASS (HTTPException, GS::GeneralException, Error, HTTP_API)
DECLARE_EXCEPTION_CLASS (HTTPNoMoreServerDataException, HTTPException, Error, HTTP_API)

}

#endif
