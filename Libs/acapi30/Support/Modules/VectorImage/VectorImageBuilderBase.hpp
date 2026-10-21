#ifndef VECTORIMAGEBUILDERBASE_HPP
#define VECTORIMAGEBUILDERBASE_HPP

#pragma once

// from VectorImage
#include "IVectorImageBuilder.hpp"

class Sy_PixMapType;
class Sy_HatchType;
class HatchObject;
class Sy_HotType;
class Sy_LinType;
class Sy_PolyLinType;
class Sy_ArcType;
class Sy_SplineType;
class Sy_RichTextType;
class Sy_FontType;
class VectorImage;

class VI_DLL_CLASS_EXPORT VectorImageBuilderBase : public IVectorImageBuilder
{
public:
	virtual ~VectorImageBuilderBase ();

	virtual GSErrCode			AddPixMap (const Sy_PixMapType& pixHeader, GSConstHandle pixMemoHdl, const char* mimeType) override;
	virtual GSErrCode			AddHatch (Sy_HatchType& hatchRef, HatchObject& hatch, const Geometry::Vector2d* offsCo) override;
	virtual GSErrCode			AddHotspot (const Sy_HotType& hotspot) override;
	virtual GSErrCode			AddPolyLine (const Sy_PolyLinType& syPolyLine, const Geometry::Polyline2D& polyline) override;
	virtual GSErrCode			AddLine (const Sy_LinType& line) override;
	virtual GSErrCode			AddArc (const Sy_ArcType& arc) override;
	virtual GSErrCode			AddSpline (const Sy_SplineType&			spline,
										   const char*					pCoordPtr,
										   const char*					pSDirsPtr,
										   const Geometry::Vector2d*	offsCo) override;
	virtual GSErrCode			AddRichText (const Sy_RichTextType* richtext) override;
	virtual GSErrCode			AddFont (const Sy_FontType&	font, const GS::UniString& fontName) override;

private:
	virtual VectorImage& GetVectorImageRef () = 0;
};

#endif
