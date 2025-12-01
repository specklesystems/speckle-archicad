// *********************************************************************************************************************
// Description:		Base64 <-> char* converter
//
// Module:			GSXML
// Contact person:	PP
//
// ********************************************************************************************************************* 

#ifndef BASE64CONVERTER_HPP
#define BASE64CONVERTER_HPP

#include "GSXMLUtilsExport.hpp"
#include "Array.hpp"
#include "UniString.hpp"


namespace	Base64Converter
{
	GSXMLUTILS_EXPORT	GS::UniString	Encode (const char* str, const USize len);	// Creates a Base64 encoding of the parameter string; the alphabet is: [A-Za-z0-9+/];
																					// result will be fragmented into (max) 60-character long lines with \n characters!

	GSXMLUTILS_EXPORT	GS::Array<char>	Decode (const GS::UniString& base64Str);	// Creates a char array of the Base4 encoded parameter string (mind the proper alphabet!); 
																					// whitespaces and \n characters are ignored in the source string
};

#endif // BASE64CONVERTER_HPP
