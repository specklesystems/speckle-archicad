#ifndef SYHATCH_HPP
#define SYHATCH_HPP

#pragma once

#include "ISymbol.hpp"
#include "DrawIndex.hpp"
#include "PolygonDrawingDirection.hpp"

// from CADInfrastructureBase
#include "ADBAttributeIndex.hpp"

static const UInt32 DefaultDisplayOrder = 0;


//A kesobbi AddPolygon, ami Geometry::Polygon2D-t kap ez alapjan tudja milyen a rajzolasi irany.
class VI_DLL_CLASS_EXPORT DefaultDrawingDirection : public IPolygonDrawingDirection
{
public:
	virtual ~DefaultDrawingDirection ();

	virtual bool IsDefaultDrawingDirection (const Geometry::Polygon2D& /*polygon*/, const Geometry::Polygon2D::ConstContourIterator& /*contourIter*/) const override
	{
		return true;
	}

	virtual bool IsDefaultDrawingDirection (const Geometry::IrregularPolygon2D& /*polygon*/, const Geometry::IrregularPolygon2D::ConstContourIterator& /*contourIter*/) const override
	{
		return true;
	}
};


//A Vector image-bol kiszedett Geometry::Polygon2D (SyHatchToPolygon2D) egy ilyen class-t ad vissza a rajzolasi irany meghatarozasahoz
class VI_DLL_CLASS_EXPORT DrawingDirectionBasedOnVertexEdgeId : public IPolygonDrawingDirection
{
public:
	virtual bool IsDefaultDrawingDirection (const Geometry::Polygon2D& polygon, const Geometry::Polygon2D::ConstContourIterator& contourIter) const override;
	virtual bool IsDefaultDrawingDirection (const Geometry::IrregularPolygon2D& polygon, const Geometry::IrregularPolygon2D::ConstContourIterator& contourIter) const override;
};


enum SyHatchFlag {
	SyHatchFlag_MillionColorBkg				= 0x0001,		// use bkgColorRGB, what is a valid RGB color
	SyHatchFlag_MillionColorFg				= 0x0002,		// use fgColorRGB, what is a valid RGB color
	SyHatchFlag_SelectionOnlyHatch			= 0x0004		// the hatch should not be drawn, exploded, but should participate in area selection.
};


enum SyHatchBuildingMaterialAndSurfaceFlag {
	SyHatchFlag_FillHatch					= 0x0001,		// fillIdx is an index to the Fill Attribute
	SyHatchFlag_BuildingMaterialHatch		= 0x0002,		// buildMatIdx is an index to the Building Material Attribute
	SyHatchFlag_OverrideBkgPen				= 0x0004,		// use fillBkgPen instead of pen from building material / surface
	SyHatchFlag_OverrideFgPen				= 0x0008,		// use fillFgPen  instead of pen from building material / surface

	SyHatchFlag_SurfaceHatch				= 0x0010		// surfaceIndex is an index to the Surface Attribute
};


class VI_DLL_CLASS_EXPORT IGetGradientFillType {
public:
	virtual GSErrCode operator () (const ADB::AttributeIndex& fillPat, GradientFillType* fillType) = 0;
	virtual ~IGetGradientFillType ();
};

class HatchObject;

class VI_DLL_CLASS_EXPORT Sy_HatchType
{
	GSErrCode	Read_Version36 (GS::IChannel& ic, HatchObject& referredHatch);
	GSErrCode	Read_Version37 (GS::IChannel& ic);
	GSErrCode	Write_Version38 (GS::OChannel& oc) const;
	GSErrCode	Read_Version38 (GS::IChannel& ic);

	static const short actVersion;
	static const short previousVersion;

public:
	Int32			item_Len;
	unsigned char	item_Typ;
	DrawIndex		drwIndex;
	short			sy_fragmentIdx;

private:
	UInt32			conversionOnly_iInObjectArray;
	Int32			filler;
	GS::Guid		keyInObjectArray;

public:
	Sy_HatchType ();

	bool		IsNear (const Sy_HatchType& other) const;

	GSErrCode	WriteGeometryForChecksum (GS::OChannel& oc, double eps) const;
	GSErrCode	WriteSettingsForChecksum (GS::OChannel& oc) const;

	bool		CheckAndRepair (void);
	short		GetFragmentIndex () const;
	void		SetFragmentIndex (short inFragmentIndex);

	GS::Guid	GetKeyInObjectArray () const;
	void		SetKeyInObjectArray (GS::Guid inKeyInObjectArray);
	UInt32		GetObsoleteIndexInObjectArray () const;

	SyEnum		GetType () const;
	GSErrCode	ReadBin (GS::IChannel& oc, short version, HatchObject& referredHatch);

	GSErrCode	Write (GS::OChannel& oc, short version) const;
	GSErrCode	Read (GS::IChannel& oc, short version, HatchObject& referredHatch);

	static short GetActVersion () { return actVersion; }
	static short GetPreviousVersion () { return previousVersion; }
	static Int32 GetConvertedSize (Int32 ac19ItemLen);
};


#endif // SYHATCH_HPP