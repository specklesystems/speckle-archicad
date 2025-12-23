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
#include	"EventReceiver.hpp"

// =====================================================================================================================
// Interface definition
// =====================================================================================================================

namespace RS {

// ----------------------- ResourceLoader --------------------------------------------------

class RS_DLL_EXPORT ResourceLoader : public GS::EventReceiver
{
private:
	mutable GS::HashTable<GSResModule, GS::HashTable<GS::UniString, JSON::ObjectValueRef>> cache;

	GS::UniString name;
	bool storeInCache;

protected:
	bool wantsAssertationForMissingResource = true;
	bool isInstantResourceLoadingEnabled = false;

protected:
	JSON::ValueRef	ReadResourceData (const GS::UniString& resourceData) const; // this is protected for testing only!

	JSON::ValueRef	LoadResourceToJSON (GSResModule module, const GS::UniString& resourceID) const;
	JSON::ValueRef	LoadResourceToJSON (GSResModule module, GSResID resourceID) const;
	JSON::ValueRef	LoadInstantResourceToJSON (GSResModule module, const GS::UniString& resourceID) const;

	virtual void	OnDisposeModuleCaches (GSResModule);

public:
	ResourceLoader (const GS::UniString& name, bool storeInCache = true);
	virtual ~ResourceLoader ();
};

}

#endif	// RESOURCELOADER_HPP
