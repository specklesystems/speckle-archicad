// *********************************************************************************************************************
// Description:		Abstract Image
//
// Module:
// Namespace:
// Contact person:
//
// *********************************************************************************************************************


#ifndef GXIMAGE_HPP
#define GXIMAGE_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

#include "GXImageBase.h"
#include "GXImageExport.hpp"
#include "FileTypeManager.hpp"
#include "Ref.hpp"
#include "GSPix.h"
#include "ImageFileRef.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace NewDisplay {
class NativeImage;
}

// --- Type definitions	------------------------------------------------------------------------------------------------

namespace GX {

class	Image;
class	ImageSaveOptions;
class	ImageSaveOptionsMask;

typedef GS::Ref<Image> ImageRef;

class GXIMAGE_DLL_EXPORT Image : public GS::Object, public ImageBase
{
	DECLARE_DYNAMIC_CLASS_INFO (Image)
private:
	GS::Ref<GS::Object>	impl;

public:
	Image ();
	explicit Image (const GSPixMapHandle picHandle);
	explicit Image (const NewDisplay::NativeImage& nativeImage);
	explicit Image (GSHandle sourceImage, const FTM::TypeID& fileFormat);
	explicit Image (IO::Location fileLoc);
	~Image ();

	void						GetDPI (Int32* hRes, Int32* vRes) const;
	void						SetDPI (Int32 hRes, Int32 vRes);

	UInt32						GetWidth (bool scaleByDPI = false) const;
	UInt32						GetHeight (bool scaleByDPI = false) const;

	UInt32						GetColorDepth () const;
	FTM::TypeID					GetTypeID () const;

	bool						IsEmpty () const;
	bool						Compare (const ImageRef& other) const;

	NewDisplay::NativeImage		ToNativeImage (double resolutionFactor = 1., bool inGrayScale = false) const;
	GSHandle					ToEncodedData (const FTM::TypeID& targetFormat, short pixelDepth) const;
	GSPixMapHandle				ToGSPixMapHandle () const;
	void*						ToDGIcon () const;
	void*						ToDGPicture () const;

	GSErrCode					WriteToFile (const IO::Location& fileLoc, const FTM::TypeID& fileFormat, const GX::ImageSaveOptions *saveOptions = nullptr) const;

	void						Add (GS::Ref<ImageFileRef> imageFile);
	void						Add (GSPixMapHandle pixMap);
	GS::Ref<ImageFileRef>		GetImageFileRef ();

	virtual GSErrCode			Read (GS::IChannel& ic) override;
	virtual GSErrCode			Write (GS::OChannel& oc) const override;

private:
	GSErrCode					ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode					WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
};

}

#endif