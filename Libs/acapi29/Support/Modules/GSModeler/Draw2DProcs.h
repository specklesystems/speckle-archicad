#if !defined (DRAW2DPROCS_H)
#define DRAW2DPROCS_H

#pragma once

#include	"GSModelerExport.h"
#include	"GSPix.h"
#include	"GSTime.hpp"
#include	"Graphics2D.h"
#include	"DrawingContext.hpp"

#include	"PointCloudView.hpp"

class GSMODELER_DLL_EXPORT GraphicsContext
{
public:
	virtual				~GraphicsContext ();

	virtual GSRect		GetBounds () const = 0;
	virtual GSErr		BeginDraw (short hSize, short vSize) = 0;
	virtual GSErr		EndDraw () = 0;

	virtual void		SetColor (const GS_RGBColor& rgb) = 0;
	virtual void		SetAlpha (unsigned char alpha) = 0;
	virtual void		SetLineWidth (short lWidth) = 0;
	virtual GSErr		DrawSector (double x1, double y1, double x2, double y2) = 0;

	virtual void		FillRect (const GSRect& rect, const GSPattern& pat) = 0;
	virtual void		FillPoly (Int32 nPoints, const GSPoint* points, const GSPattern& pat) = 0;

	virtual GSErr		SetTextAttributes (Int32 textSize) = 0;
	virtual GSErr		DrawText (Int32 x, Int32 y, const char* text) = 0;

	virtual GSErr		DrawGSPixMap (GSPixMapHandle pixMap, const GSRect& dstRect, AlphaChannelUsage acUsage = CopyAlphaChannel) = 0;
	virtual GSErr		DrawGSPixMapPart (GSPixMapHandle pixMap, const GSRect& srcRect,const GSRect& dstRect,
										AlphaChannelUsage acUsage = CopyAlphaChannel) = 0;

	virtual GSErr		DrawPointCloudView (const PointCloud::ConstViewPtr& pointCloudView,
											const PC::Matrix* viewMatrix, const PC::Matrix* projectionMatrix,
											const GSRect& viewportRect, const GSRect& clipRect)	= 0;

	virtual GSErr		UpdateScreen (bool force) = 0;
	virtual GSErr		GetNativeGraphContext (ModelerAPI::DrawingContext* nativeGraphContext) = 0;
	virtual GSErr		ReleaseNativeGraphContext (ModelerAPI::DrawingContext* nativeGraphContext) = 0;
	virtual GSErr		Suspend (ModelerAPI::DrawingContext* nativeGraphContext) = 0;
	virtual GSErr		Resume (ModelerAPI::DrawingContext* nativeGraphContext) = 0;
};

class GSMODELER_DLL_EXPORT NULLGraphicsContext : public GraphicsContext
{
	GSRect	GetBounds () const  override { GSRect r = { 0, 0, 0, 0 }; return r; }
	GSErr	BeginDraw (short, short)  override { return NoError; }
	GSErr	EndDraw ()  override { return NoError; }

	void	SetColor (const GS_RGBColor&)  override {}
	void	SetAlpha (unsigned char)  override {}
	void	SetLineWidth (short)  override {}
	GSErr	DrawSector (double, double, double, double)  override { return NoError; }

	void	FillRect (const GSRect&, const GSPattern&)  override {}
	void	FillPoly (Int32, const GSPoint*, const GSPattern&)  override {}

	GSErr	SetTextAttributes (Int32)  override { return NoError; }
	GSErr	DrawText (Int32, Int32, const char*)  override { return NoError; }

	GSErr	DrawGSPixMap (GSPixMapHandle, const GSRect&, AlphaChannelUsage)  override { return NoError; }
	GSErr	DrawGSPixMapPart (GSPixMapHandle, const GSRect&,const GSRect&, AlphaChannelUsage)  override { return NoError; }

	GSErr	DrawPointCloudView (const PointCloud::ConstViewPtr&,
								const PC::Matrix*, const PC::Matrix*,
								const GSRect&, const GSRect&) override	 { return NoError; }

	GSErr	UpdateScreen (bool) override { return NoError; }
	GSErr	GetNativeGraphContext (ModelerAPI::DrawingContext* nativeGraphContext) override
				{ *nativeGraphContext = ModelerAPI::DrawingContext () ; return NoError; }
	GSErr	ReleaseNativeGraphContext (ModelerAPI::DrawingContext* /*nativeGraphContext*/) override
				{ return NoError; }
	GSErr	Suspend (ModelerAPI::DrawingContext* /*nativeGraphContext*/) override { return NoError; }
	GSErr	Resume (ModelerAPI::DrawingContext* /*nativeGraphContext*/) override { return NoError; }
public:
    virtual ~NULLGraphicsContext ();
};

GSMODELER_DLL_EXPORT extern NULLGraphicsContext NullGraphicsContext;


#endif
