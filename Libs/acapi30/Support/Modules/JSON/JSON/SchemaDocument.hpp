// *****************************************************************************
//
// Declaration of SchemaDocument class
//
// Module:			JSON
// Namespace:		JSON
// Contact person:	SzaM
//
// *****************************************************************************

#ifndef JSON_SCHEMADOCUMENT_HPP
#define JSON_SCHEMADOCUMENT_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "JSON/JSONExport.hpp"
#include "JSON/JSONException.hpp"

#include "JSON/Value.hpp"

namespace {
	class RemoteSchemaDocumentProvider;
}

namespace JSON {

// -------------------------------- SchemaDocument ----------------------------

class JSON_API SchemaDocument {
	friend class SAJParser;

private:
	GS::UniString resultStr;
	RemoteSchemaDocumentProvider* documentProvider = nullptr;
	void* nativeSchemaDocument = nullptr;

	typedef std::function<GS::UniString (const GS::UniString&)> ProviderFunctionType;

	void* GetNativeSchemaDocument () const;

public:
	SchemaDocument ();
	SchemaDocument (GS::UniString schemaText, ProviderFunctionType remoteSchemaProvider = ProviderFunctionType ());
	~SchemaDocument ();

	void Load (GS::UniString schemaText, ProviderFunctionType remoteSchemaProvider = ProviderFunctionType ());

private:
	SchemaDocument& operator= (const SchemaDocument& source);	// disabled
	SchemaDocument (const SchemaDocument& source);				// disabled
};


}

#endif // JSON_SCHEMADOCUMENT_HPP
