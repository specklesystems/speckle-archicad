// *****************************************************************************
//
// Declaration of JDOMParser class
//
// Module:			JSON
// Namespace:		JSON
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef JSON_JDOMPARSER_HPP
#define JSON_JDOMPARSER_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "JSON/JSONExport.hpp"
#include "JSON/JSONException.hpp"
#include "JSON/ParserOption.hpp"
#include "JSON/SchemaDocument.hpp"
#include "JSON/Value.hpp"

#include "IBinaryChannel.hpp"


namespace JSON {

// -------------------------------- JDOMParser ---------------------------------

class JSON_API JDOMParser {

public:
	JDOMParser ();
	~JDOMParser ();

	ValueRef Parse (GS::IBinaryChannel& source, std::initializer_list<ParserOption> parserOptions);
	ValueRef Parse (GS::IBinaryChannel& source, bool parseComments = false);
	ValueRef Parse (GS::IBinaryChannel& source, const SchemaDocument& schemaDocument, bool parseComments = false);

private:
	JDOMParser& operator= (const JDOMParser& source);	// disabled
	JDOMParser (const JDOMParser& source);				// disabled

};

// ------------------------------ JDOMStringParser ------------------------------

class JSON_API JDOMStringParser {

public:
	JDOMStringParser ();
	~JDOMStringParser ();

	ValueRef Parse (const GS::UniString& source);
	ValueRef Parse (const GS::UniString& source, const SchemaDocument& schemaDocument);

private:
	JDOMStringParser& operator= (const JDOMStringParser& source);	// disabled
	JDOMStringParser (const JDOMStringParser& source);				// disabled

};

}

#endif
