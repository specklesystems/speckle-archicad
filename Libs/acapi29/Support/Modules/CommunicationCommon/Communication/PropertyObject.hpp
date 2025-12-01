
// *****************************************************************************
//
// Declaration of PropertyObject abstract class
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_PROPERTYOBJECT_HPP
#define COMMUNICATION_PROPERTYOBJECT_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/CommunicationCommonExport.hpp"

	// from GSRoot
#include "Ref.hpp"



// --- PropertyObject class ----------------------------------------------------

namespace Communication {

class COMMUNICATIONCOMMON_API PropertyObject {

// Construction / destruction:
protected:
			 PropertyObject () = default;
			 PropertyObject (const PropertyObject&) = default;
public:
	virtual ~PropertyObject ();

// Operator overloading:
protected:
	PropertyObject&				operator = (const PropertyObject&) = default;

// Operations:
public:
	virtual bool				Equals (const PropertyObject& rhs) const = 0;
	
	virtual PropertyObject*		Clone () const = 0;

};

typedef GS::Ref<PropertyObject, GS::Counter> PropertyObjectRef;

}

#endif // COMMUNICATION_PROPERTYOBJECT_HPP