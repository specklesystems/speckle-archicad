
// *****************************************************************************
//
// Declaration of JDOMWriter class
//
// Module:			JSON
// Namespace:		JSON
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef JSON_DOMWRITER_HPP
#define JSON_DOMWRITER_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "JSON/JSONExport.hpp"
#include "JSON/JSONException.hpp"
#include "JSON/Value.hpp"

#include "OBinaryChannel.hpp"


namespace JSON {

// -------------------------------- JDOMWriter ---------------------------------

class JSON_API JDOMWriter {

public:
	JDOMWriter (const Value& value, GS::OBinaryChannel& destination, bool formatOutput = false, int numberOfDigits = 10);
	~JDOMWriter ();

private:
	JDOMWriter& operator= (const JDOMWriter& source);	// disabled
	JDOMWriter (const JDOMWriter& source);				// disabled

};

// ----------------------------- JDOMStringWriter ------------------------------

class JSON_API JDOMStringWriter {

private:
	GS::UniString&		m_output;

public:
	JDOMStringWriter (const Value& value, GS::UniString& destination, bool formatOutput = false, int numberOfDigits = 10);
	~JDOMStringWriter ();

	const GS::UniString&	GetOutput ();

private:
	JDOMStringWriter& operator= (const JDOMStringWriter& source);	// disabled
	JDOMStringWriter (const JDOMStringWriter& source);				// disabled

};

}

#endif
