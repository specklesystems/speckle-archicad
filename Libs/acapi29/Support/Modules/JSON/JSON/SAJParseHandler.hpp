// *****************************************************************************
//
// Declaration of SAJParseHandler class
//
// Module:			JSON
// Namespace:		JSON
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef JSON_SAJPARSEHANDLER_HPP
#define JSON_SAJPARSEHANDLER_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "JSON/JSONExport.hpp"


namespace JSON {

class JSON_API SAJParseHandler {

public:
	SAJParseHandler ();
	virtual ~SAJParseHandler ();

	virtual void StartDocument ();
	virtual void EndDocument ();
	virtual void ParserError (const char* errorMessage, UInt32 position);

	virtual void NullValue ();
	virtual void BoolValue (bool value);
	virtual void Int64Value (Int64 value);
	virtual void UInt64Value (UInt64 value);
	virtual void DoubleValue (double value);
	virtual void StringValue (const GS::UniString& value);

	virtual void StartObject ();
	virtual void Name (const GS::UniString& name);
	virtual void EndObject ();

	virtual void StartArray ();
	virtual void EndArray ();

private:
	SAJParseHandler& operator= (const SAJParseHandler& source);	// disabled
	SAJParseHandler (const SAJParseHandler& source);			// disabled
};

}

#endif
