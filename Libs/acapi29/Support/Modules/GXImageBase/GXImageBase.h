#if !defined (GXIMAGEBASE_H)
#define GXIMAGEBASE_H

#pragma once

#include	"Location.hpp"
#include	"File.hpp"
#include	"FileTypeManager.hpp"

#include	"Pair.hpp"

#include	"GSPix.h"

#include	"GXImageBaseExport.hpp"

// =============================================================================
//
// Image I/O
//
// =============================================================================

namespace GX {

class ImageSaveOptions;

class GXIMAGEBASE_DLL_EXPORT ImageBase
{
public:

	static GSErrCode Init ();
	static GSErrCode Exit ();

	static GSErrCode GetGroupID (FTM::GroupID* groupId);

	static GSErrCode GetFileInfo (	const IO::Location&		fileLoc,
									Int32*					hSize,
									Int32*					vSize,
									Int32*					hRes,	// dpi
									Int32*					vRes,	// dpi
									Int32*					pixelBitNum);

	static GSErrCode ReadFile (	const IO::Location&		fileLoc,
								GSPixMapHandle*			pixHdl,
								GSPixelType				outputFormat = GSPT_Unknown);

	static GSErrCode WriteFile (	const IO::Location&		fileLoc,
									const FTM::TypeID&		fileType,
									GSPixMapHandle			pixHdl,
									const ImageSaveOptions*	saveOptions = nullptr);

	static GSErrCode GetInfo (	GSHandle				imageHandle,
								Int32*					hSize,
								Int32*					vSize,
								Int32*					hRes,	// dpi
								Int32*					vRes,	// dpi
								Int32*					pixelBitNum,
								const FTM::TypeID&		inputFormat = FTM::UnknownType);

	static GSErrCode GetType (	GSHandle				imageHandle,
								FTM::TypeID*			imageType);

	static GSErrCode Convert (	GSHandle	sourceImage,
								const char* sourceTypeMime,
								GSHandle*	targetImage,
								const char* targetTypeMime,
								short		quality);

	static GSErrCode ConvertToPixMap (	GSHandle				imageHandle,
										GSPixMapHandle*			pixHdl,
										const FTM::TypeID&		inputFormat = FTM::UnknownType,
										GSPixelType				outputFormat = GSPT_Unknown);

	static GSErrCode ConvertToPixMapArray (	GSHandle										imageHandle,
											GS::Array<GS::Pair<GSPixMapHandle, double>>*	pixHdlArray,
											const FTM::TypeID&								inputFormat = FTM::UnknownType,
											GSPixelType										outputFormat = GSPT_Unknown);

	static GSErrCode ConvertFromPixMap (	GSPixMapHandle			pixmapHandle,
											const FTM::TypeID&		targetFormat,
											GSHandle*				target,
											const ImageSaveOptions*	saveOptions = nullptr);

	static bool SupportsSettings (const FTM::TypeID& targetFormat);


	static bool IsPreferredStorageType (const FTM::TypeID&		fileTypeID,
										FTM::TypeID*			preferredFType = nullptr);

	static GSErrCode ModifyFileTypeParameters (	const FTM::TypeID&		imageType,
												const char*				description,
												const char*				fileExt,
												UInt32					macType);

	static	void* CountComponents (	void*			componentinst,
									bool			importers,
									char*			description,
									char*			fileExt,
									UInt32*			creator,
									UInt32*			macType,
									GSHandle*		mimeTypeList);

};

}

#endif

