// *****************************************************************************
//
//                                Class Image
//
// Module:			QGDrawing
// Namespace:		QG
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************

#if !defined QGIMAGE_HPP
#define QGIMAGE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "FileTypeManager.hpp"
#include "QGBase.hpp"
#include "QGTypes.hpp"
#include "QGBitmap.hpp"
#include "SourceCacheData.hpp"

// ============================== class Image ==============================

namespace QG {

class Bitmap;
class IImage;
class Context;

class QG_DLL_EXPORT Image {

friend class Context;

private:
	FTM::TypeID		typeID;
	IImage*			imp;

	GS::Optional<SourceCacheData>	sourceCacheData;

	Image (const Image&);
	Image& operator=(const Image&);

public:
	Image (const FTM::TypeID& imgTypeID, const unsigned char* imgData, const Int32 numBytes);
	Image (const QG::Bitmap& bitmap);
	virtual	~Image ();

	virtual	Int32					GetPixelWidth (void) const;
	virtual	Int32					GetPixelHeight (void) const;
	virtual	Int32					GetRowBytes (void) const;
	virtual	FTM::TypeID				GetFormat (void) const;

	void							SetSourceCacheData (const GS::Optional<SourceCacheData>& sourceCashData);
	void							SetIsInSourceCache (bool isInSourceCache);
	GS::Optional<SourceCacheData>	GetSourceCacheData () const;

	IImage*		GetImageImp (void) const { return imp; };
};


}	// namespace QG
// ______________________________ class Image ______________________________

#endif	// QGIMAGE_HPP
