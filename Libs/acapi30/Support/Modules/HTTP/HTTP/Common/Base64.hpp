
// *****************************************************************************
//
// Declaration of Connection class
// (based on Teamwork::Common::Base64 )

// Module:			HTTP
// Namespace:		HTTP::Common
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_BASE64_HPP
#define HTTP_BASE64_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

	// from HTTP
#include "HTTP/HTTPExport.hpp"

	// from GSRoot
#include "GSException.hpp"
#include "UniCHar.hpp"

namespace HTTP {
namespace Common {

class HTTP_API Base64 {

public:
	static void		Encode (const char* source, GS::USize sourceSize, char** target, GS::USize* targetSize);
	static void		Decode (const char* source, GS::USize sourceSize, char** target, GS::USize* targetSize);

};

}
}

#endif