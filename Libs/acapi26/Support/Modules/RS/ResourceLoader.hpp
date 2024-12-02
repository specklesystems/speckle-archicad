// *********************************************************************************************************************
// Description:		GRAPHISOFT Resource Manager
//
// Namespaces:		-
// Contact persons:	SzaM
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef RESOURCELOADER_HPP
#define	RESOURCELOADER_HPP

#pragma once

// --- Predeclarations	------------------------------------------------------------------------------------------------


// --- Includes	--------------------------------------------------------------------------------------------------------

#include	"HashTable.hpp"
#include	"JSON/SchemaDocument.hpp"
#include	"JSON/Value.hpp"
#include	"RS.hpp"

// =====================================================================================================================
// Interface definition
// =====================================================================================================================

namespace RS {

class RS_DLL_EXPORT ResourceLoader
{
private:
	mutable GS::Ref<JSON::SchemaDocument> schemaDocument;
	mutable GS::HashTable<GSResModule, GS::HashTable<GS::UniString, JSON::ObjectValueRef>> cache;

	GS::UniString name;
	GSResModule resourceOwnerResModule;
	bool storeInCache;

protected:
	bool wantsAssertationForMissingResource = true;
	bool isInstantResourceLoadingEnabled = false;

private:
	GS::UniString GetResourceSchema () const;
	virtual GS::UniString GetResourceRemoteSchema (const GS::UniString& remoteSchemaName) const;

protected:
	JSON::ValueRef ReadResourceData (const GS::UniString& resourceData) const; // this is protected for testing only!

	JSON::ValueRef LoadResourceToJSON (GSResModule module, const GS::UniString& resourceID) const;
	JSON::ValueRef LoadResourceToJSON (GSResModule module, GSResID resourceID) const;
	JSON::ValueRef LoadInstantResourceToJSON (GSResModule module, const GS::UniString& resourceID) const;

public:
	ResourceLoader (GSResModule resourceOwnerResModule, const GS::UniString& name, bool storeInCache = true);
	virtual ~ResourceLoader ();
};

}

#endif	// RESOURCELOADER_HPP
