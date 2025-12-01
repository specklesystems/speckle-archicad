#ifndef IVECTORIMAGEBUILDER_HPP
#define IVECTORIMAGEBUILDER_HPP

#pragma once

// from Geometry
#include "Polyline2D.hpp"

// from VectorImage
#include "VectorImageExport.h"

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
struct ProfileItem;
class ProfileEdgeData;
class IPolygonDrawingDirection;

typedef GS::HashTable<Geometry::PolyId, ProfileEdgeData>	ProfileEdgeDataTable;

class VI_DLL_CLASS_EXPORT IVectorImageBuilder
{
public:
	virtual ~IVectorImageBuilder ();

	virtual GSErrCode	AddArc (const Sy_ArcType& arc) = 0;
	virtual GSErrCode	AddFont (const Sy_FontType&	font, const GS::UniString& fontName) = 0;
	virtual GSErrCode	AddHatch (Sy_HatchType& hatchRef, HatchObject& hatch, const Geometry::Vector2d* offsCo) = 0;
	virtual GSErrCode	AddHatchFromPolygon (Sy_HatchType&												hatchRef,
											 HatchObject&												syHatch,
											 const Geometry::IrregularPolygon2D&						polygon,
											 const IPolygonDrawingDirection*							drawingDirection,
											 const Geometry::Vector2d*									offsCo,
											 const ProfileItem*											profileItem,
											 const ProfileEdgeDataTable*								profileEdgeData) = 0;
	virtual GSErrCode	AddHotspot (const Sy_HotType& hotspot) = 0;
	virtual GSErrCode	AddLine (const Sy_LinType& line) = 0;
	virtual GSErrCode	AddPixMap (const Sy_PixMapType& pixHeader, GSConstHandle pixMemoHdl, const char* mimeType) = 0;
	virtual GSErrCode	AddPolyLine (const Sy_PolyLinType& syPolyLine, const Geometry::Polyline2D& polyline) = 0;
	virtual GSErrCode	AddRichText (const Sy_RichTextType* richtext) = 0;
	virtual GSErrCode	AddSpline (const Sy_SplineType&			spline,
								   const char*					pCoordPtr,
								   const char*					pSDirsPtr,
								   const Geometry::Vector2d*	offsCo) = 0;

	virtual	void		SetDrawQueueUsing () = 0;
	virtual void		SetScale (Int32 defScaleIn) = 0;
};

#endif
