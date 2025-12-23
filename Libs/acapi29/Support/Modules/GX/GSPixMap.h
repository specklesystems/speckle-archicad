/****************************************************************************/
/*																			*/
/*								GSPixMap DEFINITION							*/
/*																			*/
/****************************************************************************/

#ifndef	_GSPixMap_H_
#define	_GSPixMap_H_

#pragma once

#define	DIBROWBYTES(pixels, width)	(4 * (((Int32) (pixels) * (Int32) (width) + 31) / 32))

#include "GXExport.h"
#include "Graphics2D.h"
#include "GSPix.h"

// from GSRoot
#include "GSRoot.hpp"


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

struct GSPixMap {
private:
	GSSize			headerSize	= 0;	/*  4 */	/* size of this struct = sizeof (GSPixMap)	*/
	GSSize			rowBytes	= 0;	/*  4 */	/* offset to next line						*/
	Int32			height		= 0;	/*  4 */	/* must be non negative						*/
	Int32			width		= 0;	/*  4 */	/* must be non negative						*/
	Int32			hRes		= 0;	/*  4 */	/* horiz. resolution (ppi)					*/
	Int32			vRes		= 0;	/*  4 */	/* vert. resolution (ppi)					*/
	unsigned char	pixelType	= 0;	/*  1 */	/* pixel's type int the pixmap (GSPixelType)*/
	unsigned char	pmReserved0	= 0;	/*  1 */	/* for future use. MUST BE 0				*/
	short			pmReserved1	= 0;	/*  2 */	/* for future use. MUST BE 0				*/
	Int32			pmReserved2	= 0;	/*  4 */	/* for future use. MUST BE 0				*/

public:

	void Create (GSSize actRowBytes, Int32 hSiz, Int32 vSiz, Int32 vres, Int32 hres, GSPixelType actPixelType);

	bool operator== (const GSPixMap& other) const;
	bool operator!= (const GSPixMap& other) const;

	GSSize	GetHeaderSize () const;
	GSSize	GetBytesPerRow () const;

	UInt32	GetWidth () const;
	UInt32	GetHeight () const;

	void	SetHResolution (Int32 res);
	Int32	GetHResolution () const;

	void	SetVResolution (Int32 res);
	Int32	GetVResolution () const;

	void			SetPixelType (unsigned char actPixelType);
	unsigned char	GetPixelType () const;
};


inline void		GSPixMap::Create (GSSize actRowBytes, Int32 hSiz, Int32 vSiz, Int32 vres, Int32 hres, GSPixelType actPixelType)
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


inline bool		GSPixMap::operator== (const GSPixMap& other) const
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


inline bool		GSPixMap::operator!= (const GSPixMap& other) const
{
	return !operator== (other);
}


inline GSSize	GSPixMap::GetHeaderSize () const
{
	return headerSize;
}


inline GSSize	GSPixMap::GetBytesPerRow () const
{
	return rowBytes;
}


inline UInt32	GSPixMap::GetWidth () const
{
	return width;
}


inline UInt32	GSPixMap::GetHeight () const
{
	return height;
}


inline void		GSPixMap::SetHResolution (Int32 res)
{
	hRes = res;
}


inline Int32	GSPixMap::GetHResolution () const
{
	return hRes;
}


inline void		GSPixMap::SetVResolution (Int32 res)
{
	vRes = res;
}


inline Int32	GSPixMap::GetVResolution () const
{
	return vRes;
}


inline void		GSPixMap::SetPixelType (unsigned char actPixelType)
{
	pixelType = actPixelType;
}


inline unsigned char	GSPixMap::GetPixelType () const
{
	return pixelType;
}


bool	ClipRects (Int32 width, Int32 height, const GSRect& r1, const GSRect& r2, GSRect* newR1, GSRect* newR2);

GSErr	StretchPixMapLowLev (GSPixMapHandle source, GSPixMapHandle dest, const GSRect& srcRect, const GSRect& dstRect,
							 AlphaChannelUsage acUsage);

GSErr	RotatePixMapLowLev (GSPixMapHandle source, GSPixMapHandle dest, const GSRect& srcRect, double blX, double blY, double angle,
							double co, double si, bool mirr, AlphaChannelUsage acUsage);

#endif
