// *********************************************************************************************************************
// File:			DGImage.hpp
//
// Description:		Icon and other image related classes and functions
// *********************************************************************************************************************

#ifndef DGIMAGE_HPP
#define DGIMAGE_HPP

#pragma once

// --- Includes --------------------------------------------------------------------------------------------------------

#include "Definitions.hpp"
#include "DGDefs.h"
#include "DGDLLExport.h"
#include "NativeImage.hpp"
#include "RSTypes.hpp"

#if defined (WINDOWS)
#include "DGWImageCache.hpp"
#endif

#include <utility>

namespace GS {
	class ObjectState;
	class UniString;
}

namespace Gfx {
	class Color;
}

namespace RS {
	class Icon;
}

namespace DG {
	class Rect;
}

namespace DG {

// === class Image =====================================================================================================

class DG_DLL_EXPORT Image
{
protected:
	GSResModule	resModule;
	short		resId;
	const void*	data;

public:
	enum {
		NoImage = DG_NO_IMAGE
	};

	Image ();
	Image (GSResModule resModule, short resId);
	explicit Image (const void* data);
	virtual	~Image ();

	bool	operator== (const Image& rightOp) const;
	bool	operator!= (const Image& rightOp) const;

	GSResModule		GetResourceModule (void) const;
	short			GetResourceId (void) const;
	const void*		GetData (void) const;

	bool			IsEmpty (void) const;
	virtual bool	IsValid (void) const;

	virtual GSErrCode	Store (GS::ObjectState& os) const;
};


// === class Icon ======================================================================================================

class DG_DLL_EXPORT Icon: public Image
{
public:
	enum {
		NoIcon				= DG_NO_ICON,

		Error				= DG_ERROR_ICON,
		Information			= DG_INFORMATION_ICON,
		Warning				= DG_WARNING_ICON,

		File				= DG_FILE_ICON,
		TextFile			= DG_TEXTFILE_ICON,
		Folder				= DG_FOLDER_ICON,
		OpenedFolder		= DG_FOLDEROPEN_ICON,
		MyDocFolder			= DG_MYDOCFOLDER_ICON,
		Favorites			= DG_FAVORITES_ICON,
		Floppy				= DG_FLOPPY_ICON,
		CDDrive				= DG_CDDRIVE_ICON,
		HDDrive				= DG_HDD_ICON,
		NetDrive			= DG_NETDRIVE_ICON,
		Desktop				= DG_DESKTOP_ICON,
		RecycleBin			= DG_RECYCLEBIN_ICON,
		EntireNetwork		= DG_ENTIRENETWORK_ICON,
		FilledArrowLeft		= DG_FILLED_LEFT_ICON,
		FilledArrowRight	= DG_FILLED_RIGHT_ICON,
		FilledArrowDown		= DG_FILLED_DOWN_ICON,
		FishBoneArrowLeft	= DG_FISHBONE_LEFT_ICON,
		FishBoneArrowRight	= DG_FISHBONE_RIGHT_ICON,
		FishBoneArrowDown	= DG_FISHBONE_DOWN_ICON
	};

			 Icon ();
			 Icon (GSResModule resModule, short resId);
			 Icon (const RS::Icon& icon);
	explicit Icon (const void* data);
	virtual	~Icon ();

	virtual bool	IsValid (void) const override;

	GSErrCode		Store (GS::ObjectState& os) const override;

	std::pair<Int32, Int32>	GetSize () const;

	static short	GetIdFromString (const GS::UniString& iconIdStr);
};


// === class Picture ===================================================================================================

class DG_DLL_EXPORT Picture: public Image
{
public:
	enum {
		NoPicture = DG_NO_IMAGE
	};

	Picture ();
	Picture (GSResModule resModule, short resId);
	explicit Picture (const void* data);
	virtual	~Picture ();

	GSErrCode	Store (GS::ObjectState& os) const override;
};


// === class NativeImage ===============================================================================================

class DG_DLL_EXPORT NativeImage
{
private:
	NewDisplay::NativeImage nativeImage;

#if defined (WINDOWS)
	HICON hIcon;
	UInt32 dpi;
	DG::ImageCache::Image image;
#endif

public:
	NativeImage ();
	NativeImage (const void* data, double resolutionFactor);
	NativeImage (GSResModule module, GSResID resID, double resolutionFactor);
	NativeImage (GSResModule module, GSResID resID, UInt32 desiredSizeX, UInt32 desiredSizeY, double resolutionFactor);
	NativeImage (const DG::Image& icon, double resolutionFactor);

	NativeImage (const NativeImage& other);
	NativeImage& operator= (const NativeImage& other);

	virtual ~NativeImage ();

	NewDisplay::NativeImage		GetNativeImage (void);
};


// === class NativeImageIcon ===========================================================================================

// NativeImageIcon creates a native HICON/NSImage from a NativeImage, or takes the ownership of an existing
// HICON or NSImage. The native HICON/NSImage is destroyed by the destructor.

class DG_DLL_EXPORT NativeImageIcon: public DG::Icon
{
public:
	NativeImageIcon (const NewDisplay::NativeImage& nativeImage);
	NativeImageIcon (const void* nativeIcon);
	NativeImageIcon (NativeImageIcon&& source);
	NativeImageIcon& operator= (NativeImageIcon&& other);
	virtual ~NativeImageIcon ();

	NativeImageIcon (const NativeImageIcon& other) = delete;
	NativeImageIcon& operator= (const NativeImageIcon& other) = delete;
};


// == Utility functions ================================================================================================

DG_DLL_EXPORT DG::Icon	CreateIconFromNativeImage (const NewDisplay::NativeImage& nativeImage);
DG_DLL_EXPORT DG::Icon	CreateIconFromPict (const DG::Picture& picture, const Gfx::Color& transparentColor);

DG_DLL_EXPORT std::pair<Int32, Int32>	GetIconSize (const DG::Icon& icon); // Width and height in logical units

DG_DLL_EXPORT void	DestroyDGIcon (Icon& icon);
DG_DLL_EXPORT void	ReleaseNativeImage (void* image);

DG_DLL_EXPORT void	DrawIcon (void* drawContext, const DG::Rect& contextRect, const DG::Icon& icon, double resolutionFactor = 1.0, bool isDisabled = false, short hAlignment = DG_IS_CENTER, short vAlignment = DG_IS_VCENTER);
DG_DLL_EXPORT void	DrawIcon (NewDisplay::NativeContext& context, const DG::Rect& rect, const NewDisplay::NativeImage& nativeImage, bool isDisabled = false, short hAlignment = DG_IS_CENTER, short vAlignment = DG_IS_VCENTER);
DG_DLL_EXPORT void	DrawIcon (NewDisplay::NativeContext& context, const DG::Rect& rect, const DG::Icon& icon, bool isDisabled = false, short hAlignment = DG_IS_CENTER, short vAlignment = DG_IS_VCENTER);


// === Mac specific functions ==========================================================================================

#if defined (macintosh)

DG_DLL_EXPORT void	DrawIconIntoRect (void* drawContext, const DG::Rect& rect, const DG::Icon& icon, bool isDisabled = false, short hAlignment = DG_IS_CENTER,  short vAlignment = DG_IS_VCENTER);
DG_DLL_EXPORT void	DrawBestIconIntoRect (void* drawContext, const DG::Rect& rect, const DG::Icon& icon, bool isDisabled = false, short hAlignment = DG_IS_CENTER,  short vAlignment = DG_IS_VCENTER);
DG_DLL_EXPORT void	DrawNativeImageIntoRect (void* drawContext, const DG::Rect& rect, const void* image, bool isDisabled = false);

typedef enum ImageTypeHint {
	ImgType_Icon = 0,
	ImgType_Picture = 1,
	ImgType_Cursor = 2
} ImageTypeHint;

typedef double CGFloat;

DG_DLL_EXPORT void* GetNativeImage (short imageId, GSResModule resModule, ImageTypeHint hint = DG::ImgType_Picture);
DG_DLL_EXPORT void*	GetNativeMaskedImage (void* image, const Gfx::Color* transparentColor);
DG_DLL_EXPORT void* GetNativeIconImage (short imageId, GSResModule resModule);
DG_DLL_EXPORT NewDisplay::NativeImage	CreateNativeImageFromImageData (GSHandle imageData, double resolutionFactor = 1.0);

DG_DLL_EXPORT void	GetNativeImageSize (const void* image, Int32* pWidth, Int32* pHeight);

DG_DLL_EXPORT void 	CompositeImages (void **dest, CGFloat w, CGFloat h, void *src1, CGFloat x1, CGFloat y1, CGFloat w1, CGFloat h1, void *src2, CGFloat x2, CGFloat y2, CGFloat w2, CGFloat h2);

#endif


// === Windows specific functions ======================================================================================

#if defined (WINDOWS)

DG_DLL_EXPORT bool	GetIconData (const HICON hIcon, Int32* width, Int32* height, bool* isColor = nullptr, HBITMAP* hcBmp = nullptr, _Outptr_opt_ HBITMAP* hmBmp = nullptr);
DG_DLL_EXPORT void	DrawIcon (HDC hDC, const DG::Rect& rc, const HICON hIcon, bool isDisabled = false, short hAlignment = DG_IS_CENTER, short vAlignment = DG_IS_VCENTER);
DG_DLL_EXPORT void	DrawIcon (HICON hIcon, HDC hDC, const RECT *rc);
DG_DLL_EXPORT BOOL	DrawIcon (HDC hDC, UINT xDst, UINT yDst, UINT cxDst, UINT cyDst, HICON hIcon, UINT xSrc, UINT ySrc, BOOL disabled);
DG_DLL_EXPORT BOOL	DrawIconCenter (HDC hDC, RECT *rcDst, HICON hIcon, UINT xSrc, UINT ySrc, UINT cxSrc, UINT cySrc, BOOL disabled);

DG_DLL_EXPORT HICON	PrepareIconForDisabledDraw (HICON hIcon);

#endif

} // namespace DG

#endif
