// *********************************************************************************************************************
// File:			FTYPResourceLoader.hpp
//
// Description:		FTYP Resource Loader class
//
// Project:			InputOutput (IO)
//
// Contact person:	BL
// *********************************************************************************************************************

#ifndef FTYPRESOURCE_LOADER
#define FTYPRESOURCE_LOADER

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "JSON/Value.hpp"
#include "Optional.hpp"
#include "ResourceLoader.hpp"
#include "UniString.hpp"


namespace IO {

// === class FTYPResource ==============================================================================================

class IO_DLL_EXPORT FTYPResource
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

	char* pFTYP = nullptr;
#endif

	short			resourceId = 0;
	GSResModule		resourceModule = InvalidResModule;
	GS::UniString	mimeTypes;
	GS::UniString	description;
	GS::UniString	fileExtensions;
	Int32			creator = 0;
	Int32			type = 0;
	short			iconId = 0;

	JSON::ObjectValueRef jsonResourceData;

public:
	FTYPResource () = delete;
#ifndef NO_LEGACY_RESOURCE_LOADING
	FTYPResource (GSResModule resModule, short resId);
#endif
	FTYPResource (GSResModule resModule, JSON::ObjectValueRef jsonResourceData);

	bool			IsValid () const;
	short			GetResId () const;
	GSResModule		GetResModule () const;
	GS::UniString	GetMimeTypes () const;
	GS::UniString	GetDescription () const;
	GS::UniString	GetFileExtensions () const;
	Int32			GetCreator () const;
	Int32			GetType () const;
	short			GetIconId () const;
};


// === class FTYPResourceLoader ========================================================================================

class IO_DLL_EXPORT FTYPResourceLoader: public RS::ResourceLoader
{
private:
	FTYPResourceLoader&		operator= (const FTYPResourceLoader& source) = delete;	// disabled
	FTYPResourceLoader (const FTYPResourceLoader& source) = delete;					// disabled

	FTYPResourceLoader ();
	GS::Optional<FTYPResource>	LoadHelper (GSResModule module, const GS::UniString& resourceID) const;

public:
	virtual ~FTYPResourceLoader ();

	static GS::Optional<FTYPResource>	Load (GSResModule module, const GS::UniString& resourceID);
};

}	// namespace IO

#endif // FTYPRESOURCE_LOADER
