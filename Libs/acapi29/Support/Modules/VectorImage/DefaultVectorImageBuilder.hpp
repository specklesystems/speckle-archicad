#ifndef DEFAULTVECTORIMAGEBUILDER_HPP
#define DEFAULTVECTORIMAGEBUILDER_HPP

#pragma once

// from GSRoot
#include "GSRoot.hpp"

// from Pattern
#include "PolygonDrawingDirection.hpp"

// from VectorImage
#include "IVectorImageBuilder.hpp"

class Sy_HatchType;
class HatchObject;
struct ProfileItem;
class ProfileEdgeData;
class VectorImage;

class VI_DLL_CLASS_EXPORT DefaultVectorImageBuilder : public IVectorImageBuilder
{
public:
	DefaultVectorImageBuilder (VectorImage& inImage);
	virtual ~DefaultVectorImageBuilder ();

	virtual GSErrCode AddArc (const Sy_ArcType& arc) override;
	virtual GSErrCode AddFont (const Sy_FontType& font, const GS::UniString& fontName) override;
	virtual GSErrCode AddHatch (Sy_HatchType& hatchRef, HatchObject& hatch, const Geometry::Vector2d* offsCo) override;
	virtual GSErrCode AddHatchFromPolygon ( Sy_HatchType&											hatchRef,
											HatchObject&											syHatch,
											const Geometry::IrregularPolygon2D&						polygon,
											const IPolygonDrawingDirection*							drawingDirection,
											const Geometry::Vector2d*								offsCo,
											const ProfileItem*										profileItem,
											const ProfileEdgeDataTable*	profileEdgeData) override;
	virtual GSErrCode AddHotspot (const Sy_HotType& hotspot) override;
	virtual GSErrCode AddLine (const Sy_LinType& line) override;
	virtual GSErrCode AddPixMap (const Sy_PixMapType& pixHeader, GSConstHandle pixMemoHdl, const char* mimeType) override;
	virtual GSErrCode AddPolyLine (const Sy_PolyLinType& syPolyLine, const Geometry::Polyline2D& polyline) override;
	virtual GSErrCode AddRichText (const Sy_RichTextType* richtext) override;
	virtual GSErrCode AddSpline (const Sy_SplineType& spline, const char* pCoordPtr, const char* pSDirsPtr, const Geometry::Vector2d* offsCo) override;

	virtual void SetDrawQueueUsing () override;
	virtual void SetScale (Int32 defScaleIn) override;

private:
	VectorImage& image;

};

#endif
