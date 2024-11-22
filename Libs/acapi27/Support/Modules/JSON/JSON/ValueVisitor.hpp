
// *****************************************************************************
//
// Declaration of ValueVisitor class
//
// Module:			JSON
// Namespace:		JSON
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef JSON_VALUEVISITOR_HPP
#define JSON_VALUEVISITOR_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "JSON/JSONExport.hpp"


namespace GS { class UniString; }


namespace JSON {

class Value;
class NullValue;
class BoolValue;
class NumberValue;
class StringValue;
class ObjectValue;
class ArrayValue;

class JSON_API ValueVisitor {

public:
	ValueVisitor ();
	virtual ~ValueVisitor ();

	virtual void Visit (NullValue& value) = 0;
	virtual void Visit (BoolValue& value) = 0;
	virtual void Visit (NumberValue& value) = 0;
	virtual void Visit (StringValue& value) = 0;

	virtual void StartVisit (ObjectValue& value) = 0;
	virtual void VisitName (const GS::UniString& name) = 0;
	virtual void EndVisit (ObjectValue& value) = 0;
	
	virtual void StartVisit (ArrayValue& value) = 0;
	virtual void EndVisit (ArrayValue& value) = 0;

};

}

#endif

