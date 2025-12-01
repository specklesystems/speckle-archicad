#ifndef	ISWCORE_HPP
#define	ISWCORE_HPP

#include "GraphixDefinitions.hpp"

#define PTR_SIZE_UINT GS::UIntPtr


class	GRAPHIX_DLL_EXPORT	ISwCore
{
public:

	// --- Base HRGN rasterizer class -------------------------------------------------------------
	class		GRAPHIX_DLL_EXPORT	RegionRasterizer
	{
	private:
		HRGN	region;

	public:
		RegionRasterizer (HRGN region):
			region	(region)
			{
			}

		bool	Do ();
		virtual bool	RasterizeRect (const RECT& rect) = 0;
	};

	// --- Utility functions for 32bit dibsections ------------------------------------------------
	virtual	HBITMAP		CreateDIBSection (UINT width, UINT height, UINT bitPP, const void* bitmapData = nullptr, void** diBitmapPointer = nullptr,
											Int32* bytesPerRow = nullptr, bool getPtrForBottomToTop = false) = 0;
	virtual	HBITMAP		Create32BitDIBSection (UINT width, UINT height, const DWORD* bitmapData = nullptr, DWORD** diBitmapPointer = nullptr,
												Int32* bytesPerRow = nullptr, bool getPtrForBottomToTop = false) = 0;

	virtual	bool		SwBlit (HDC dstDC, HDC srcDC, const RECT& srcRect, Int32 dstX, Int32 dstY, RECT* dirtyRect) = 0;

	virtual	void		Fill (HBITMAP hBitmap, HRGN hRgn, const RECT& rect, UInt32 color) = 0;


	// --- Functions for 32bit bitmaps ------------------------------------------------------------
	
	// componentSwizzle: 11100100b		ARGB -> ARGB
	// componentSwizzle: 11000110b		ARGB -> ABGR
	// componentSwizzle: 10010011b		ARGB -> RGBA
	// componentSwizzle: 00011011b		ARGB -> BGRA
	// all other is						ARGB -> ARGB

	virtual	void	CopyBuffer (const DWORD* srcPtr, DWORD* dstPtr, PTR_SIZE_UINT width, PTR_SIZE_UINT height,
								Int32 srcPitch, Int32 dstPitch, UInt8 componentSwizzle) = 0;
	
	virtual	void	AlphaBlendBuffers (const DWORD* srcPtr, DWORD* dstPtr, PTR_SIZE_UINT width, PTR_SIZE_UINT height,
									   Int32 srcPitch, Int32 dstPitch, DWORD alpha, DWORD srcAlphaXorMask, DWORD dstAlphaXorMask, bool srcIsPerpixelAlpha,
									   bool blendWithSrcAlpha) = 0;

	virtual	void	AlphaBlendBuffersWithColorMatrix (const DWORD* srcPtr, DWORD* dstPtr, PTR_SIZE_UINT width, PTR_SIZE_UINT height,
													 Int32 srcPitch, Int32 dstPitch, DWORD alpha, DWORD srcAlphaXorMask, DWORD dstAlphaXorMask,
													 const float (&matrix)[4*5], bool srcIsPerpixelAlpha, bool blendWithSrcAlpha) = 0;

	virtual	void	FillBuffer (const DWORD* ptr, PTR_SIZE_UINT width, PTR_SIZE_UINT height, Int32 pitch, DWORD argbColor) = 0;


	virtual	void	AlterBufferAlpha (const DWORD* ptr, PTR_SIZE_UINT width, PTR_SIZE_UINT height, Int32 pitch, DWORD alphaMask, bool xor_) = 0;

	virtual	void	BlendPlainText (const DWORD* srcPtr, DWORD* dstPtr, PTR_SIZE_UINT width, PTR_SIZE_UINT height,
									Int32 srcPitch, Int32 dstPitch, DWORD argbColor, DWORD alphaXorMask,
									bool blendWithSrcAlpha) = 0;

	virtual	void	BlendMultiColorText (const DWORD* srcPtr, DWORD* dstPtr, PTR_SIZE_UINT width, PTR_SIZE_UINT height,
										 Int32 srcPitch, Int32 dstPitch, DWORD alphaXorMask, bool blendWithSrcAlpha) = 0;
};


#endif