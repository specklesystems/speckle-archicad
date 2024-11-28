#ifndef GS_VI_SECTIONIMAGE_HPP
#define GS_VI_SECTIONIMAGE_HPP

#include "VectorImageExport.h"
#include "VectorImage.hpp"
#include "VectorImageIterator.hpp"
#include "OverriddenAttributes.hpp"
#include "Transformation2D.hpp"

namespace VI {

class SectionHotspot;

class VI_DLL_CLASS_EXPORT SectionImage {
private:
	DECLARE_ROOT_CLASS_INFO

	VectorImage		vectorImage;

public:
	virtual				~SectionImage ();

	void				Clear ();

	void				Copy (SectionImage& target) const;
	SectionImage		Sort () const;

	GSErrCode			GetItemFramePoints (const Box2DData& frame, GS::Array<Coord>& points, bool withoutHotspots = false) const;
	Box2DData			GetBounds (bool withoutHotspots = false) const;
	USize				GetSizeInBytes () const;
	GSErrCode			WriteForChecksum (GS::OChannel& oc) const;

	GSErrCode			CheckAndRepair ();
	bool				AreThereAnyHotspotsOutOfModel () const;

	Int32				GetScale () const;

	void				SetGeneratedWithOverrides (bool generatedWithOverrides);
	void				SetScale (Int32 defScale);

	SectionImage& operator= (const SectionImage& other);

	GSErrCode						Read (GS::IChannel& ic);
	GSErrCode						Write (GS::OChannel& oc) const;

private:
	GSErrCode						ReadVersion1 (GS::IChannel& ic);
	GSErrCode						WriteVersion1 (GS::OChannel& oc) const;

public:
	GSErrCode						ReadXML (GS::XMLIChannel& channel);
	GSErrCode						WriteXML (GS::XMLOChannel& channel) const;
	
	ULong							GetItemCount () const;

	UInt32							GetLineCount () const;
	void							ForEachLine (const std::function<bool (Sy_LinType&)>& processor);
	void							ForEachLine (const std::function<bool (const Sy_LinType&)>& processor) const;

	void							ForEachPolyLine (const std::function<bool (const Sy_PolyLinType&)>& processor) const;

	UInt32										GetHatchCount () const;
	const GS::HashTable<GS::Guid, HatchObject>& GetConstHatchObjects () const;


	UInt32							GetHotspotCount () const;
	void							AddHotspot (const SectionHotspot& hotspot);
	void							AddHotspots (const GS::Array<SectionHotspot>& hotspots);
	void							ForEachHotspot (const std::function<bool (SectionHotspot&)>& processor);
	void							ForEachHotspot (const std::function<bool (const SectionHotspot&)>& processor) const;
	void							DeleteAllHotspots ();

	bool							IsEmpty () const;

	void							Transform (const Geometry::Transformation2D& transformation);

	VectorImage						ConvertToVectorImage () const;
	void							CreateFromVectorImage (const VectorImage& other);

	void				GetUsedAttributes (GS::Array<ADB::AttributeIndex>& lineTypes, GS::Array<ADB::AttributeIndex>& fills, GS::Array<ADB::AttributeIndex>& buildingMaterials, GS::Array<ADB::AttributeIndex>& surfaces) const;

	void				ReindexUsedAttributes (const GS::HashTable<ADB::AttributeIndex, ADB::AttributeIndex>& lineTypeMapping,
											   const GS::HashTable<ADB::AttributeIndex, ADB::AttributeIndex>& fillMapping,
											   const GS::HashTable<ADB::AttributeIndex, ADB::AttributeIndex>& buildingMaterialMapping,
											   const GS::HashTable<ADB::AttributeIndex, ADB::AttributeIndex>& surfaceMapping);

	void							AddLineRec (const Sy_LinType& line);

	void							AddPointCloud (/*OWNERSHIP*/ PointCloudObject* object, DrawIndex drwIndex, short sy_fragmentIdx);

	void							AddPolyLine (const Sy_PolyLinType& syPolyLine, const Geometry::Polyline2D& polyline);

	GS::Guid						AddHatchWhole (const VBAttr::ExtendedPen&	fillPen,
												   short						bkgPen,
												   DrawIndex					drwIndex,
												   GX::Pattern::HatchTran		hatchTrafo,
												   const ADB::AttributeIndex&	fillind,
												   const GS::Array<UInt32>&		contourEndList,
												   const GS::Array<Coord>&		coordList,
												   const PlaneEq&				plane,
												   UInt32						displayOrder,
												   const OverriddenOpacity&		overriddenOpacity,
												   short						fillTypeDetermination /* = 0 */,
												   const GS_RGBColor*			bkgColorRGB /* = nullptr */,
												   const GS_RGBColor*			fgColorRGB /* = nullptr */,
												   char							specFor3D /*= SySymbolic*/);

	GSErrCode						AddHatchRec (Sy_HatchType& hatchRef, HatchObject& hatchObj);

	GSErrCode						AddHatchRec (Sy_HatchType& hatchRef,
												 HatchObject& hatchObj,
												 const Geometry::IrregularPolygon2D& polygon,
												 const IPolygonDrawingDirection* drawingDirection);
};


}
#endif