
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
			 PropertyObject ();
			 PropertyObject (const PropertyObject&);
public:
	virtual ~PropertyObject ();

// Operator overloading:
protected:
	const PropertyObject&		operator = (const PropertyObject&);

// Operations:
public:
	virtual bool				Equals (const PropertyObject& rhs) const = 0;
	
	virtual PropertyObject*		Clone () const = 0;

};

typedef GS::Ref<PropertyObject, GS::Counter> PropertyObjectRef;

////////////////////////////////////////////////////////////////////////////////
// PropertyObject inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline PropertyObject::PropertyObject ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline PropertyObject::PropertyObject (const PropertyObject&)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const PropertyObject&	PropertyObject::operator = (const PropertyObject&)
{
	return *this;
}

}

#endif // COMMUNICATION_PROPERTYOBJECT_HPP