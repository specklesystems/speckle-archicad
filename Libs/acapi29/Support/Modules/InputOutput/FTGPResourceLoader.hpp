// *********************************************************************************************************************
// File:			FTGPResourceLoader.hpp
//
// Description:		FTGP Resource Loader class
//
// Project:			InputOutput (IO)
//
// Contact person:	BL
// *********************************************************************************************************************

#ifndef FTGPRESOURCE_LOADER
#define FTGPRESOURCE_LOADER

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "JSON/Value.hpp"
#include "Optional.hpp"
#include "ResourceLoader.hpp"
#include "UniString.hpp"


namespace IO {

// === class FTGPResource ==============================================================================================

class IO_DLL_EXPORT FTGPResource
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

	char* pFTGP = nullptr;
#endif

public:
	struct FTGPGroupItem	{
		Int32			itemId = 0;
		GS::UniString	mime;
	};

	struct FTYPGroupItem	{
		Int32			itemId = 0;
		GS::UniString	mime;
	};

private:
	short			resourceId = 0;
	GSResModule		resourceModule = InvalidResModule;
	GS::UniString	mimeType;
	GS::UniString	description;
	GS::Array<FTGPGroupItem>	FTGPGroup;
	GS::Array<FTYPGroupItem>	FTYPGroup;

	JSON::ObjectValueRef jsonResourceData;

public:
	FTGPResource () = delete;
#ifndef NO_LEGACY_RESOURCE_LOADING
	FTGPResource (GSResModule resModule, short resId);
#endif
	FTGPResource (GSResModule resModule, JSON::ObjectValueRef jsonResourceData);

	bool			IsValid () const;
	short			GetResId () const;
	GSResModule		GetResModule () const;
	GS::UniString	GetMimeType () const;
	GS::UniString	GetDescription () const;
	UInt32			GetFTGPGroupItemCount () const;
	UInt32			GetFTYPGroupItemCount () const;
	FTGPGroupItem	GetFTGPGroupItem (UInt32 itemIndex) const;
	FTYPGroupItem	GetFTYPGroupItem (UInt32 itemIndex) const;
};


// === class FTGPResourceLoader ========================================================================================

class IO_DLL_EXPORT FTGPResourceLoader: public RS::ResourceLoader
{
private:
	FTGPResourceLoader&		operator= (const FTGPResourceLoader& source) = delete;	// disabled
	FTGPResourceLoader (const FTGPResourceLoader& source) = delete;					// disabled

	FTGPResourceLoader ();
	GS::Optional<FTGPResource>	LoadHelper (GSResModule module, const GS::UniString& resourceID) const;

public:
	virtual ~FTGPResourceLoader ();

	static GS::Optional<FTGPResource>	Load (GSResModule module, const GS::UniString& resourceID);
};

}	// namespace IO

#endif // FTGPRESOURCE_LOADER
