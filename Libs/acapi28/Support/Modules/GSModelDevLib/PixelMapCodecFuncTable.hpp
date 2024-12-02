// *****************************************************************************
// Rendering Add-On interface types
// GSModeler, Platform independent
//
// Namespaces:        Contact person:
//                         FGY, PCS
//
// SG compatible
// *****************************************************************************

#if !defined (GS_GSMODELER_PIXELMAPCODECFUNCTABLE_HPP)
#define GS_GSMODELER_PIXELMAPCODECFUNCTABLE_HPP


#pragma once


// ----------------------- Includes --------------------------------------------

#include "MPIFuncTableHead.hpp"
#include "GSRoot.hpp"


// ----------------------- Predeclarations -------------------------------------

namespace ModelerAPI {
	class PixelMapCodecImp;
	struct PixelMapFuncTable;
	class PixelMap;
}
// ----------------------- Types -----------------------------------------------

namespace ModelerAPI {

inline constexpr short PixelMapCodecVersionBase = 4;

enum {
	PixelMapCodecVersion = PixelMapCodecVersionBase + MPIAddOnVersion
	// 4: 2016.04.12 BoZ v20 RC1
	// 5: 2017.04.28 MCs v21 RC1
	// 6: 2018.04.24 PP  v22 RC1
	// 7: 2019.08.08 HaB v23 RC1
	// 8: 2020.05.12 HaB v24 RC1
	// 9: 2021.11.04 HaB v25 UP3
	// 10: 2022.02.11 SA v26 RC1
};

typedef GSErrCode MPI_ADD_ON_CALL SetGSPixelMapInterfaceFunc (PixelMapFuncTable* funcTable);

typedef GSErrCode MPI_ADD_ON_CALL CanExportMimeTypeFunc (
											PixelMapCodecImp*	itself,
											const char*			mimeType,
											bool*				canExport);

typedef GSErrCode MPI_ADD_ON_CALL ExportPixMapToImageFunc (
											PixelMapCodecImp*	itself,
											const PixelMap*		pixelMap,
											const char*			mimeType,
											void**				imageDataPtr,
											Int32*				exportedSize);

typedef GSErrCode MPI_ADD_ON_CALL CanImportMimeTypeFunc (
											PixelMapCodecImp*	itself,
											const char*			mimeType,
											bool*				canImport);

typedef GSErrCode MPI_ADD_ON_CALL GetImageInfoFunc (
											PixelMapCodecImp*	itself,
											const void*			imageData,
											Int32				imageDataSize,
											Int32*				hSize,
											Int32*				vSize,
											Int32*				hRes,	// dpi
											Int32*				vRes,	// dpi
											Int32*				pixelBitNum,
											const char*			mimeTypeHint);

typedef GSErrCode MPI_ADD_ON_CALL ImportImageToPixMapFunc (
											PixelMapCodecImp*	itself,
											const void*			imageData,
											Int32				imageDataSize,
											PixelMap*			pixelMap,
											const char*			mimeTypeHint);

struct PixelMapCodecFuncTable {
	MPI::FuncTableHead			head;

	SetGSPixelMapInterfaceFunc*	setGSPixelMapInterface;

	CanExportMimeTypeFunc*		canExportMimeType;
	ExportPixMapToImageFunc*	exportPixMapToImage;
	CanImportMimeTypeFunc*		canImportMimeType;
	GetImageInfoFunc*			getImageInfo;
	ImportImageToPixMapFunc*	importImageToPixMap;
};


} // namespace ModelerAPI


#endif
