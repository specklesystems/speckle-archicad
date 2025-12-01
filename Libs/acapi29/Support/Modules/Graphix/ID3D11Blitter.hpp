// *****************************************************************************
// File:			ID3D11Blitter.hpp
//
// Description:		Direct3D11 2D Blitting interface
//
// Contact person:	DG
//
// SG compatible
// *****************************************************************************

#ifndef	ID3D11BLITTER_HPP
#define	ID3D11BLITTER_HPP

// --- Includes ----------------------------------------------------------------

#include "GraphixDefinitions.hpp"		// GRAPHIX_DLL_EXPORT
#include <windows.h>
#include "D3D11Interface.h"
#include "Point.hpp"
#include "BlitEffects.hpp"

// --- D3D11 blitter interface -------------------------------------------------

class	GRAPHIX_DLL_EXPORT	ID3D11Blitter
{
public:
	struct AuxTextureEntry	{
		ID3D11Texture2D*			pTexture;
		ID3D11RenderTargetView*		pRtv;
		ID3D11ShaderResourceView*	pSrv;
		UINT						width;
		UINT						height;
		bool						perPixelAlpha;
		const void*					internalData;

		AuxTextureEntry ():
			pTexture		(nullptr),
			width			(0),
			height			(0),
			perPixelAlpha	(false),
			internalData	(nullptr)
			{
			}
	};

public:
	// === Blitting functions (threadsafe) ==============================================

	virtual	void					FillSurface (UInt32 deviceIndex,
												 ID3D11Texture2D* pTexture, ID3D11Texture2D* pDepthStencilTexture,
												 ID3D11RenderTargetView* pRTV, ID3D11DepthStencilView* pDSV, const RECT* rect, UInt32 argbColor) = 0;

	virtual	bool					SimpleBlitHw2Hw (UInt32 deviceIndex,
													 ID3D11Texture2D* pDstTexture, ID3D11Texture2D* pSrcTexture,
													 ID3D11RenderTargetView* pDstRTV, ID3D11ShaderResourceView* pSrcSRV,
													 const RECT* srcRect, const RECT* dstClipRect, Int32 dstX, Int32 dstY, RECT* pDirtyRect = nullptr) = 0;

	virtual	bool					SimpleBlitInterDeviceHw2Hw (UInt32 dstDeviceIndex, UInt32 srcDeviceIndex,
																ID3D11Texture2D* pDstTexture, ID3D11Texture2D* pSrcTexture, ID3D11RenderTargetView* pDstRTV,
																const RECT* srcRect, const RECT* dstClipRect, Int32 dstX, Int32 dstY, RECT* pDirtyRect = nullptr) = 0;

	virtual	bool					SimpleBlitHw2Sw (UInt32 deviceIndex,
													 HBITMAP dstBuffer, ID3D11Texture2D* pSrcTexture, 
													 const RECT* srcRect, const RECT* dstClipRect,
													 Int32 dstX, Int32 dstY, bool invertedDstAlpha, RECT* pDirtyRect = nullptr) = 0;

	virtual bool					BlitHw2Hw (UInt32 deviceIndex,
											   ID3D11Texture2D* pDstTexture, ID3D11Texture2D* pSrcTexture, ID3D11Texture2D* pDepthStencilTexture,
 											   ID3D11RenderTargetView* pDstRTV, ID3D11ShaderResourceView* pSrcSRV, ID3D11DepthStencilView* pDsDSV,
											   const RECT* pSrcRect, const RECT* pDstClipRect,
											   float dstX, float dstY, DWORD alpha, float scaleX, float scaleY, float rotation, bool blendWithAlpha,
											   bool linearFilter = true, const NewDisplay::BlitEffect* effect = nullptr, RECT* pDirtyRect = nullptr) = 0;

	virtual	bool					BlitSw2Hw (UInt32 deviceIndex,
											   ID3D11Texture2D* pDstTexture, HBITMAP srcBitmap, ID3D11Texture2D* pDepthStencilTexture,
											   ID3D11RenderTargetView* pDstRTV, ID3D11DepthStencilView* pDsDSV,
											   const RECT* srcRect, const RECT* dstClipRect,
											   float dstX, float dstY, DWORD alpha, float scaleX, float scaleY, float rotation,
											   bool blendWithAlpha, bool srcIsPerpixelAlpha, bool invertedSrcAlpha,
											   bool linearFilter = true, const NewDisplay::BlitEffect* effect = nullptr,
											   RECT* pDirtyRect = nullptr) = 0;

	virtual	bool					CopyDepthStencilView (UInt32 deviceIndex, ID3D11Texture2D* pDstDepthStencilTexture, ID3D11Texture2D* pSrcDepthStencilTexture,
														  RECT* pDirtyRect = nullptr) = 0;

	// --- Cached helper surfaces for custom implementations of complex blittings

	virtual	AuxTextureEntry			GetAuxTexture (UInt32 deviceIndex, UInt32 width, UInt32 height, bool perPixelAlpha, bool swSurface) = 0;
	virtual	void					ReleaseAuxTexture (const AuxTextureEntry& entry) = 0;

	virtual bool					MapTexture (UInt32 deviceIndex, ID3D11Texture2D* pTexture, D3D11_MAPPED_SUBRESOURCE& mapInfo) = 0;
	virtual void					UnmapTexture (UInt32 deviceIndex, ID3D11Texture2D* pTexture) = 0;
	virtual void					CopySubResourceRegion (UInt32 deviceIndex, ID3D11Texture2D* pTextureTo, ID3D11Texture2D* pTextureFrom,
														   UInt32 dstX, UInt32 dstY, const D3D11_BOX* pSrcBox) = 0;
};

#endif
