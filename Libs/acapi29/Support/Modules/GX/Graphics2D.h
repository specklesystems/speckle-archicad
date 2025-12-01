// *****************************************************************************
// Low level 2D graphics functions (lowest level in the Graphics)
// Module / project name, platform
//
// Namespaces:        Contact person:
//                      FGY
//
// *****************************************************************************
#if !defined (GRAPHICS2D_H)
#define GRAPHICS2D_H

#pragma once

#include	"GXExport.h"

#include	"GSPix.h"
#include	"GSTime.hpp"

struct  DESC;

GX_DLL_EXPORT
GSErr	GX_CALL	GXInitRect (GSRect* rect, Int32 left, Int32 top, Int32 right, Int32 bottom);

GX_DLL_EXPORT
void	GX_CALL	GXInsetRect (GSRect* rect, Int32 dh, Int32 dv);

GX_DLL_EXPORT
bool	GX_CALL	GXSectRect (const GSRect& srcRect1, const GSRect& srcRect2, GSRect* dstRect);

// =============================================================================
//
// PROTOTYPES for GSPixMap
//
// =============================================================================

enum AlphaChannelUsage { CopyAlphaChannel, AlphaChannelBlending };

GX_DLL_EXPORT
UInt32 GX_CALL GXPixelSizeFromPixelType (GSPixelType pixelType);

GX_DLL_EXPORT
GSPixelType GX_CALL GXPixelTypeFromPixelSize (UInt32 pixelSize);

GX_DLL_EXPORT
GSPixMapHandle GX_CALL GXCreateGSPixMapLogical (Int32 hSiz, Int32 vSiz, const double resolutionFactor, GSPixelType pixelType = GSPT_ARGB);

GX_DLL_EXPORT
GSPixMapHandle GX_CALL GXCreateGSPixMap (Int32 hSiz, Int32 vSiz, Int32 hres = 72, Int32 vres = 72, GSPixelType pixelType = GSPT_ARGB);

GX_DLL_EXPORT
void GX_CALL GXDeleteGSPixMap (GSPixMapHandle rendPixs);

GX_DLL_EXPORT
GSErr GX_CALL GXCopyGSPixMap (GSPixMapHandle* target, GSPixMapHandle source);

GX_DLL_EXPORT
bool GX_CALL GXIsSameGSPixMap (GSPixMapHandle pixMapH1, GSPixMapHandle pixMapH2);

GX_DLL_EXPORT
GSPtr GX_CALL GXGetGSPixMapBaseAddr (GSPixMapHandle pixMapH);

GX_DLL_EXPORT
UInt32 GX_CALL GXGetGSPixMapBytesPerRow (GSPixMapHandle pixMapH);

GX_DLL_EXPORT
UInt32 GX_CALL GXGetGSPixMapPixelSize (GSPixMapHandle pixMapH);

GX_DLL_EXPORT
UInt32 GX_CALL GXGetGSPixMapHResolution (GSPixMapHandle pixMapH);

GX_DLL_EXPORT
UInt32 GX_CALL GXGetGSPixMapVResolution (GSPixMapHandle pixMapH);

GX_DLL_EXPORT
void GX_CALL GXSetGSPixMapHResolution (GSPixMapHandle pixMapH, UInt32 res);

GX_DLL_EXPORT
void GX_CALL GXSetGSPixMapVResolution (GSPixMapHandle pixMapH, UInt32 res);

GX_DLL_EXPORT
void GX_CALL GXSetGSPixMapPixelType (GSPixMapHandle pixMapH, GSPixelType pixelType);

GX_DLL_EXPORT
GSPixelType GX_CALL GXGetGSPixMapPixelType (GSPixMapHandle pixMapH);

GX_DLL_EXPORT
GSErr GX_CALL GXGetGSPixMapBounds (GSPixMapHandle pixMapH, GSRect* boundsRect);

GX_DLL_EXPORT
GSErr GX_CALL GXCalcPixMapColorTable (GSPixMapHandle pixMapH, UInt32 numDesiredColor, DESC* colortab);

GX_DLL_EXPORT
UInt32 GX_CALL GXGetGSPixMapWidth  (GSPixMapHandle pixMapH);

GX_DLL_EXPORT
UInt32 GX_CALL GXGetGSPixMapHeight (GSPixMapHandle pixMapH);

GX_DLL_EXPORT
void GX_CALL GXGetGSPixMapPixel (GSPixMapHandle pixMapH, Int32 h, Int32 v, GX_ARGBColor *argb);

GX_DLL_EXPORT
void GX_CALL GXSetGSPixMapPixel (GSPixMapHandle pixMapH, const Int32 h, const Int32 v, const GX_ARGBColor& argb);

GX_DLL_EXPORT
bool GX_CALL GXGSPixMapIsAllAlphaEqual (GSPixMapHandle pixMapH, unsigned char* value = nullptr);

GX_DLL_EXPORT
void GX_CALL GXFillGSPixMapAlphaChannel (GSPixMapHandle pixMapH, unsigned char value = 0);

GX_DLL_EXPORT
void GX_CALL GXFillGSPixMap (GSPixMapHandle offPixMap, const GX_ARGBColor& argb);

GX_DLL_EXPORT
GSErr GX_CALL GXStretchGSPixMap (GSPixMapHandle srcPixMap, GSPixMapHandle dstPixMap, const GSRect& srcRect, const GSRect& dstRect,
								 AlphaChannelUsage acUsage = CopyAlphaChannel);

GX_DLL_EXPORT
GSErr GX_CALL GXRotateGSPixMap (GSPixMapHandle srcPixMap, GSPixMapHandle dstPixMap, const GSRect& srcRect,
								Int32 bottomLeftX, Int32 bottomLeftY, double angle, bool mirr, AlphaChannelUsage acUsage = CopyAlphaChannel);

GX_DLL_EXPORT
void GX_CALL GXGetRotatedGSPixMapWidthHeight (Int32* dWidth, Int32* dHeight, double angle, const GSRect* sClip, const GSRect* dClip,
											  Int32* f0h, Int32* f0v);

GX_DLL_EXPORT
GSErr GX_CALL GXRotateGSPixMap_OldParList (GSPixMapHandle srcPixMap, GSPixMapHandle dstPixMap, double angle, bool mirr,
										   const GSRect* sClip, Int32 f0h, Int32 f0v);

GX_DLL_EXPORT
void GX_CALL GXInitDefaultPattern (GSPattern *pat, unsigned short transpar);

GX_DLL_EXPORT
void GX_CALL GXInitDefaultTransparentPattern (GSPattern *pat, double transpar);

GX_DLL_EXPORT
GSPixMapHandle GX_CALL GXCreateARGBGSPixMap (GSPixMapHandle pixMap);

GX_DLL_EXPORT
GSErr GX_CALL GXCropGSPixMap (GSPixMapHandle srcPixMap, GSPixMapHandle* dstPixMap, const GSRect& rect);

#endif
