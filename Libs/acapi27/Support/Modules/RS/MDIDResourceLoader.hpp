// *********************************************************************************************************************
// File:			MDIDResourceLoader.hpp
//
// Description:		MDID Resource Loader class
//
// Project:			Resource Manager (RS)
//
// Contact person:	BL
// *********************************************************************************************************************

#ifndef MDIDRESOURCE_LOADER
#define MDIDRESOURCE_LOADER

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "JSON/Value.hpp"
#include "Optional.hpp"
#include "ResourceLoader.hpp"
#include "UniString.hpp"


namespace RS {

// === class MDIDResource ==============================================================================================

class RS_DLL_EXPORT MDIDResource
{
private:
#ifndef NO_LEGACY_RESOURCE_LOADING
	class ResHandle
	{
	private:
		GSHandle handle = nullptr;

	public:
		ResHandle (GSHandle handle): handle (handle) { }
		~ResHandle () { BMKillHandle (&handle); }
		bool	IsNull () { return handle == nullptr; }
	};

	GS::Ref<ResHandle> resHandle;

	UInt32* pMDID = nullptr;
#endif

	short			resourceId = 0;
	GSResModule		resourceModule = InvalidResModule;
	UInt32			developerId = 0;
	UInt32			localId = 0;

	JSON::ObjectValueRef jsonResourceData;

public:
	MDIDResource () = delete;
#ifndef NO_LEGACY_RESOURCE_LOADING
	MDIDResource (GSResModule resModule, short resId);
#endif
	MDIDResource (GSResModule resModule, JSON::ObjectValueRef jsonResourceData);

	bool			IsValid () const;
	short			GetResId () const;
	GSResModule		GetResModule () const;
	UInt32			GetDeveloperId () const;
	UInt32			GetLocalId () const;
};


// === class MDIDResourceLoader ========================================================================================

class RS_DLL_EXPORT MDIDResourceLoader: public RS::ResourceLoader
{
private:
	MDIDResourceLoader&		operator= (const MDIDResourceLoader& source) = delete;	// disabled
	MDIDResourceLoader (const MDIDResourceLoader& source) = delete;					// disabled

	MDIDResourceLoader ();
	GS::Optional<MDIDResource>	LoadHelper (GSResModule module, const GS::UniString& resourceID) const;

public:
	virtual ~MDIDResourceLoader ();

	static GS::Optional<MDIDResource>	Load (GSResModule module, const GS::UniString& resourceID);
};

}	// namespace DG

#endif // MDIDRESOURCE_LOADER
