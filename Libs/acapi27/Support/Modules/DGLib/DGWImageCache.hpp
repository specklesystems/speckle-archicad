// *********************************************************************************************************************
// File:			DGWImageCache.hpp
//
// Description:		Image cache for DG.
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Contact person:	VM
// *********************************************************************************************************************

#ifndef DGWIMAGECACHE_HPP
#define DGWIMAGECACHE_HPP

#pragma once

// Includes ------------------------------------------------------------------------------------------------------------

#include "Win32Interface.hpp"

#include "DG.h"
#include "HashCommon.hpp"
#include "HashTable.hpp"
#include "RS.hpp"


namespace DG {

// === class ImageCache ================================================================================================

class DG_DLL_EXPORT ImageCache
{
public:
	class DG_DLL_EXPORT Image
	{
	friend class DG::ImageCache;
	private:
		GSResModule	resModule;
		short		imageId;
		UInt32		dpi;
		HICON		hIcon;
		short		cx;
		short		cy;
		Int32		developerId;
		Int32		localId;

	public:
		Image ();
		Image (GSResModule resModule, short imageId, short cx = 0, short cy = 0, Int32 developerId = 0, Int32 localId = 0);
		Image (Icon icon, short cx = 0, short cy = 0, Int32 developerId = 0, Int32 localId = 0);
		Image (HICON _hIcon);
		Image (const Image& image);

		virtual ~Image ();

		Image& 	operator= 	(const Image& source);
		bool 	operator== 	(const Image& source) const;
		bool 	operator!= 	(const Image& source) const;

		void	Set (GSResModule resModule, short imageId, short cx = 0, short cy = 0, Int32 developerId = 0, Int32 localId = 0);
		void	Set (HICON hIcon);
		void 	Set (const DG::Image& icon, short cx = 0, short cy = 0, Int32 developerId = 0, Int32 localId = 0);

		void	Pin (Int32 developerId, Int32 localId);
		void	Release (void);

		GSResModule		GetResModule (void) const;
		short			GetImageId (void) const;
		HICON			GetIcon (UInt32 dpi);
		Icon 			GetDGIcon (void) const;
		bool			IsEmpty (void) const;
	};

private:
	class CacheItem
	{
	friend class DG::ImageCache;
	private:
		GSResModule	resModule;
		short		imageId;
		UInt32		dpi;
		HICON		hIcon;
		Int32 		refCounter;
		Int32		developerId;
		Int32		localId;
		bool		isPinned;

		Int32		width;	// Filled by GetImageSize
		Int32		height;	// Filled by GetImageSize

		CacheItem ();	// Disable default constructor
		bool 	operator== (const CacheItem& source);	// Disable
#if defined (DEBUVERS_VM)
		void	Dump (void) const
		{
			DBPRINTF ("CacheItem rm:0x%X, id:%d, dpi:%d, hIcn:0x%X, refCnt:%d, devId:0x%X, locId:0x%X, pinned:%d, w:%d, h:%d\n",
					  resModule, imageId, dpi, hIcon, refCounter, developerId, localId, isPinned, width, height);
		}
#endif

	public:
		CacheItem (UInt32 dpi, GSResModule resModule, short imageId, HICON hIcon, Int32 refCounter, Int32 developerId = 0, Int32 localId = 0, bool isPinned = false);
		~CacheItem ();
	};

	struct SystemImage
	{
		HINSTANCE hModule;
		LPWSTR resName;
		Int32 width;
		Int32 height;

		SystemImage (HINSTANCE _hModule, LPWSTR _resName, Int32 _width, Int32 _height):
			hModule (_hModule),
			resName (_resName),
			width (_width),
			height (_height)
		{
		}

		bool	operator== (const SystemImage& other) const
		{
			return hModule == other.hModule && resName == other.resName && width == other.width && height == other.height;
		}

		ULong	GenerateHashValue () const
		{
			return GS::CalculateHashValue (hModule, resName, width, height);
		}
	};

	GS::Array<CacheItem> cache;
	GS::Array<HICON> unreferencedIcons;
	GS::HashTable<SystemImage, HICON> systemIcons;

	static HICON	RequestImage (UInt32 dpi, GSResModule resModule, short imageId, short cx = 0, short cy = 0, Int32 developerId = 0, Int32 localId = 0);
	static void		ReleaseImage (Image& image);

	static void		RemoveUnreferencedImage (HICON hIcon);

	static bool		GetImageIdentifiers (HICON hIcon, UInt32* dpi, GSResModule* resModule, short* imageId, Int32* developerId, Int32* localId, bool* isPinned, Int32* cacheIndex = NULL);

	static void		PinImage (GSResModule resModule, short imageId, Int32 developerId, Int32 localId);

public:
	ImageCache ();
	~ImageCache ();

	static bool		GetImageSize (HICON hIcon, Int32* width, Int32* height);

	static void		ReleasePinnedImages (Int32 developerId, Int32 localId);

	static HICON	GetSystemIcon (HINSTANCE hModule, LPWSTR resName, Int32 width, Int32 height);

	static void		GetInfo (DWORD& cachedImageCount, DWORD& usedImageCount);

#if defined (DEBUVERS_VM)
	static void		DumpCacheContent (void);
#endif
};

} // namespace DG

#endif
