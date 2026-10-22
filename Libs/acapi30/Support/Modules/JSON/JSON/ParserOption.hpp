
// *****************************************************************************
//
// Declaration of ParserOption enum class
//
// Module:			JSON
// Namespace:		JSON
// Contact person:	SN
//
// *****************************************************************************

#ifndef JSON_PARSEROPTION_HPP
#define JSON_PARSEROPTION_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "JSON/JSONExport.hpp"


namespace JSON {

// ------------------------------- ParserOption --------------------------------

enum class ParserOption {

	ParseNumbersAsStrings,
	ParseComments

};

}

#endif