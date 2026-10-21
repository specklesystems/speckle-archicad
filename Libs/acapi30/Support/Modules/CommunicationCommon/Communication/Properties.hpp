
// *****************************************************************************
//
// Declaration of Properties class
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_PROPERTIES_HPP
#define COMMUNICATION_PROPERTIES_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/PropertyObject.hpp"

	// from GSRoot
#include "HashTable.hpp"
#include "UniString.hpp"



// --- Properties class --------------------------------------------------------

namespace Communication {

class COMMUNICATIONCOMMON_API Properties {

// Type definitions:
private:
	typedef GS::HashTable<GS::UniString, PropertyObjectRef> PropertyMap;

// Data members:
private:
	PropertyMap			m_properties;

// Operations:
public:
	GS::USize			GetSize () const;

	GS::USize			GetPropertyNames (GS::PagedArray<GS::UniString>& propertyNames) const;

	bool				ContainsProperty (const GS::UniString& propertyName) const;

	PropertyObjectRef	GetProperty (const GS::UniString& propertyName) const;
	void				SetProperty (const GS::UniString& propertyName, const PropertyObjectRef& propertyValue);

	bool				ClearProperty (const GS::UniString& propertyName);

	void				Clear ();

};

}

#endif // COMMUNICATION_PROPERTIES_HPP