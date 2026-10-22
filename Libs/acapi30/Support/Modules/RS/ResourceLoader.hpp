// *********************************************************************************************************************
// Description:		GRAPHISOFT Resource Manager
//
// Namespaces:		RS
// Contact persons:	Antlia squad
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef GS_RESOURCELOADER_HPP
#define	GS_RESOURCELOADER_HPP

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
	static bool forceInstantReload;

protected:
	bool wantsAssertationForMissingResource = true;

private:
	JSON::ValueRef	LoadInstantResourceToJSON (GSResModule module, const GS::UniString& resourceID) const;
	JSON::ValueRef	LoadCompiledResourceToJSON (GSResModule module, const GS::UniString& resourceID) const;


protected:
	JSON::ValueRef	ReadResourceData (const GS::UniString& resourceData) const; // this is protected for testing only!

	JSON::ValueRef	LoadResourceToJSON (GSResModule module, const GS::UniString& resourceID) const;
	JSON::ValueRef	LoadResourceToJSON (GSResModule module, GSResID resourceID) const;

	virtual void	OnDisposeModuleCaches (GSResModule);

public:
	ResourceLoader (const GS::UniString& name, bool storeInCache = true);
	virtual ~ResourceLoader ();

	static bool IsInstantResourceLoadingEnabled ();
	static void SetInstantReloadStatus (bool isEnabled);
};

}

#endif	// RESOURCELOADER_HPP
