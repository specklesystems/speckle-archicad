#ifndef	SWBLITTARGET_HPP
#define	SWBLITTARGET_HPP

#include "IBlit.hpp"

namespace NewDisplay {

class	SwBlitTarget:	public BlitTarget
{
public:
	HBITMAP				tempBitmap;
	HDC					hdc;
	Gdiplus::Graphics*	graphics;

public:
	float				originX;				// Blit target origin
	float				originY;
	//RECT				boundRect;				// physical boundrect
	HBITMAP				bitmap;
	HBITMAP				texture;
	const RECT*			clipBoundRect;			// clip boundrect relative to the origin
	HRGN				clipRgn;
	bool				perPixelAlpha;
	bool				invertedAlpha;
	bool				antialias;

public:
	SwBlitTarget (HDC hdc, const RECT* clipRect = nullptr, NewDisplay::NativeContextImpl* dstContext = nullptr);
	SwBlitTarget (Gdiplus::Graphics* graphics, const RECT* clipRect = nullptr, NewDisplay::NativeContextImpl* dstContext = nullptr);
	SwBlitTarget (float	originX, float originY, HBITMAP bitmap, HBITMAP texture, const RECT* clipBoundRect, HRGN clipRgn,
				  bool perPixelAlpha, bool invertedAlpha, bool antialias, NewDisplay::NativeContextImpl* dstContext = nullptr);

	~SwBlitTarget ();


	virtual bool	GetPtrToDstRect (const GS::Rect<Int32>& rect, void** ptr, Int32* pitch) override;
	virtual bool	MergeSrc (const void* srcPtr, Int32 pitch, bool srcIsPerpixelAlpha, UInt32 width, UInt32 height, Int32 dstPosX, Int32 dstPosY) override;
};

};

#endif