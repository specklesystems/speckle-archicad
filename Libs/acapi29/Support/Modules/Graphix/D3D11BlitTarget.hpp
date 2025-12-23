// *****************************************************************************
// File:			D3D11BlitTarget.hpp
//
// Description:		D3D11 implementation of BlitTarget
//
// Contact person:	DG
//
// SG compatible
// ***************************************************************************** 

#ifndef	D3D11BLITTARGET_HPP
#define	D3D11BLITTARGET_HPP

#include "IBlit.hpp"
#include "D3D11Interface.h"

class	D3D11BlitTarget:	public NewDisplay::BlitTarget
{
public:
	enum BufferType	{
		ColorBuffer	=	0,
		ZStencil
	};

public:
	BufferType					bufferType;
	UInt32						deviceIndex;
	float						originX;				// Blit target origin
	float						originY;
	const RECT					boundRect;				// physical boundrect
	ID3D11RenderTargetView*		pRenderTargetView;
	ID3D11ShaderResourceView*	pTextureView;
	const RECT*					clipBoundRect;			// physical clip boundrect
	ID3D11DepthStencilView*		pDepthStencilView;		// clip relative to the origin
	bool						perPixelAlpha;
	bool						invertedAlpha;
	bool						antialias;

D3D11BlitTarget (BufferType bufferType, UInt32 deviceIndex, float originX, float	originY, const RECT boundRect, ID3D11RenderTargetView* pRenderTargetView,
					ID3D11ShaderResourceView* pTextureView, const RECT* clipBoundRect, ID3D11DepthStencilView* pDepthStencilView,
					bool perPixelAlpha, bool invertedAlpha, bool antialias):
	BlitTarget			(true),
	bufferType			(bufferType),
	deviceIndex			(deviceIndex),
	originX				(originX),
	originY				(originY),
	boundRect			(boundRect),
	pRenderTargetView	(pRenderTargetView),
	pTextureView		(pTextureView),
	clipBoundRect		(clipBoundRect),
	pDepthStencilView	(pDepthStencilView),
	perPixelAlpha		(perPixelAlpha),
	invertedAlpha		(invertedAlpha),
	antialias			(antialias)
	{
	}
};

#endif