#ifndef JSONFORMATTING_HPP
#define JSONFORMATTING_HPP

#pragma once


#include "JSONConversionExport.hpp"
#include "UniString.hpp"


namespace JSON {

JSON_CONVERSION_API GSErrCode	ReformatJSON (const GS::UniString&	unformattedJSON,
											  GS::UniString&		formattedJSON,
											  bool					formatOutput = false,
											  int					numberOfDigits = 10);

}	// namespace JSON


#endif
