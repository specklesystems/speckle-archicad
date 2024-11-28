/****************************************************************************/
/*																			*/
/*								GSPixMap DEFINITION							*/
/*																			*/
/****************************************************************************/

#ifndef	_GSPixMap_H_
#define	_GSPixMap_H_

#pragma once

#define	DIBROWBYTES(pixels, width)	(4 * (((Int32) (pixels) * (Int32) (width) + 31) / 32))

#include	"GSRoot.hpp"
#include	"GSPix.h"
#include	"Graphics2D.h"
#include	"GXExport.h"

class GX_DLL_EXPORT_NOT_C PixMapHandleGuard
{
public:
	explicit PixMapHandleGuard (const GSPixMapHandle pixMapHdl);
	explicit PixMapHandleGuard (Int32 hSiz, Int32 vSiz, Int32 hres = 72, Int32 vres = 72, GSPixelType pixelType = GSPT_ARGB);
	~PixMapHandleGuard ();

	GSPixMapHandle&			GetPixMapHandle ();
	const GSPixMapHandle&	GetPixMapHandle () const;

	GSPixMapHandle&			operator() ();
	const GSPixMapHandle&	operator() () const;

private:
	GSPixMapHandle pixMapHdl;
};

/*
The structure of the GSPixMap:
- the header (GSPixMap structure)
- the pixel information
*/

struct GSPixMap
{
private:
	GSSize						headerSize;			/*  4 */	/* size of this struct = sizeof (GSPixMap)	*/
	GSSize						rowBytes;			/*  4 */	/* offset to next line						*/
	Int32						height;				/*  4 */	/* must be non negative						*/
	Int32						width;				/*  4 */	/* must be non negative						*/
	Int32						hRes;				/*  4 */	/* horiz. resolution (ppi)					*/
	Int32						vRes;				/*  4 */	/* vert. resolution (ppi)					*/
	unsigned char				pixelType;			/*  1 */	/* pixel's type int the pixmap (GSPixelType)*/
	unsigned char				pmReserved0;		/*  1 */	/* for future use. MUST BE 0				*/
	short						pmReserved1;		/*  2 */	/* for future use. MUST BE 0				*/
	Int32						pmReserved2;		/*  4 */	/* for future use. MUST BE 0				*/
public:
	GSPixMap ():
		headerSize (0),
		rowBytes (0),
		height (0),
		width (0),
		hRes (0),
		vRes (0),
		pixelType (0),
		pmReserved0 (0),
		pmReserved1 (0),
		pmReserved2 (0)
	{
	}

	GSSize GetHeaderSize () { return headerSize; }
	GSSize GetBytesPerRow () { return rowBytes; }

	UInt32	GetWidth () { return width; }
	UInt32	GetHeight () { return height; }

	void SetHResolution (Int32 res) { hRes = res; }
	Int32 GetHResolution () { return hRes; }
	void SetVResolution (Int32 res) { vRes = res; }
	Int32 GetVResolution () { return vRes; }

	void SetPixelType (unsigned char actPixelType)
	{
		pixelType = actPixelType;
	}
	unsigned char GetPixelType () { return pixelType; }

	void Create (GSSize actRowBytes, Int32 hSiz, Int32 vSiz, Int32 vres, Int32 hres, GSPixelType actPixelType)
	{
		DBASSERT (headerSize == 0 && rowBytes == 0 && height == 0 && width == 0 && hRes == 0 && vRes == 0 && pixelType == 0 && pmReserved0 == 0 && pmReserved1 == 0 && pmReserved2 == 0);
		DBASSERT (actRowBytes > 0 && hSiz > 0 && vSiz > 0 && vres > 0 && hres > 0);

		if (actPixelType != GSPT_ARGB &&
			actPixelType != GSPT_ALongRGB &&
			actPixelType != GSPT_BlackWhite &&
			actPixelType != GSPT_256Gray) {
				DBBREAK_STR ("GXCreateGSPixMap: unknown pixelType");
				throw GS::IllegalArgumentException ("GXCreateGSPixMap: unknown pixelType", __FILE__, __LINE__);
		}

		headerSize		= sizeof (GSPixMap);
		rowBytes		= actRowBytes;
		height			= vSiz;
		width			= hSiz;
		hRes			= hres;
		vRes			= vres;
		pixelType		= static_cast <unsigned char> (actPixelType);
		pmReserved0		= 0;
		pmReserved1		= 0;
		pmReserved2		= 0;
	}

	bool operator== (const GSPixMap& other) const
	{
		if (headerSize != other.headerSize)
			return false;
		if (rowBytes != other.rowBytes)
			return false;
		if (width != other.width)
			return false;
		if (height != other.height)
			return false;
		if (hRes != other.hRes)
			return false;
		if (vRes != other.vRes)
			return false;
		if (pixelType != other.pixelType)
			return false;
		return true;
	}

	bool operator!= (const GSPixMap& other) const
	{
		return !(*this == other);
	}
};

extern bool ClipRects (Int32 width, Int32 height, const GSRect& r1, const GSRect& r2, GSRect* newR1, GSRect* newR2);
extern GSErr StretchPixMapLowLev (GSPixMapHandle source, GSPixMapHandle dest, const GSRect& srcRect, const GSRect& dstRect,
								  AlphaChannelUsage acUsage);
extern GSErr RotatePixMapLowLev (GSPixMapHandle source, GSPixMapHandle dest, const GSRect& srcRect, double blX, double blY, double angle,
								 double co, double si, bool mirr, AlphaChannelUsage acUsage);

#endif
