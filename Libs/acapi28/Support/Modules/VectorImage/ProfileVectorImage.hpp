#ifndef PROFILEVECTORIMAGE_HPP
#define PROFILEVECTORIMAGE_HPP

#pragma once

// from GSRoot
#include "ThreadSafeLazyData.hpp"

// from VectorImage
#include "VectorImage.hpp"
#include "ProfileVectorImageParameter.hpp"
#include "Anchor.hpp"
#include "DimensionControlTool.hpp"
#include "StretchData.hpp"
#include "EdgeOverrideData.hpp"
#include "StructureComponentId.hpp"

struct ProfileItem;
typedef GS::HashTable<Geometry::PolyId, ProfileEdgeData>	ProfileEdgeDataTable;

namespace VI {
namespace HatchPriority {
	class HatchPriorityComparer;
}
}

namespace Geometry {
class Transformation2D;
}


class VI_DLL_CLASS_EXPORT ProfileVectorImage
{
public: 
	typedef GS::HashTable<PVI::ProfileParameterId, GS::HashSet<PVI::ProfileParameterSetupId>>	ParameterToDefinitionsTableType;

private:

	friend class ProfileVectorImageIterator;
	friend class ConstProfileVectorImageIterator;

	VectorImage																			image;
	ParameterToDefinitionsTableType														parameterToDefinitionsTable;
	GS::HashTable<PVI::ProfileParameterSetupId, PVI::ProfileVectorImageParameter>		parameterDefinitions;
	GS::HashTable<PVI::ProfileAnchorId, PVI::Anchor>									anchorDefinitions;
	GS::HashTable<PVI::ProfileDimControlToolId, PVI::DimensionControlTool>				dimControls;
	PVI::StretchData																	stretchData;
	PVI::EdgeOverrideData																overrideData;
	GS::HashTable<GS::Guid, StructureComponentId>										hatchUniqeIdToStructureComponentIdTable;
	GS::HashTable<GS::Guid, PVI::HatchVertexId>											associatedHotspotsTable;


	struct ProfileVectorImageBounds
	{
		Box2DData	buildingBounds;
		Box2DData	coreBuildingBounds;
		Box2DData	noFinishBuildingBounds;
	};

	GS::ThreadSafeLazyData<ProfileVectorImageBounds>	m_bounds;

	void							InvalidateBounds ();
	const ProfileVectorImageBounds&	GetProfileVectorImageBounds () const;

	GSErrCode						WriteVersion1 (GS::OChannel& channel, const GS::OutputFrame& frame) const;
	GSErrCode						ReadVersion1 (GS::IChannel& channel, const GS::InputFrame& frame);
	GSErrCode						WriteVersion2 (GS::OChannel& channel, const GS::OutputFrame& frame) const;
	GSErrCode						ReadVersion2 (GS::IChannel& channel, const GS::InputFrame& frame);

	bool							CheckProfileItemVersionsConsistency () const;
	bool							CheckAssociatedHotspotsTable () const;
	bool							CheckHatchUniqueIdToStructureComponentIdTable () const;
	StructureComponentId			NewValidStructureComponentId () const;
	void							StoreWithNewStructureComponentId (const GS::Guid& newHatchGuid);

public:
	ProfileVectorImage ();

	bool							operator== (const ProfileVectorImage& other) const;
	bool							operator!= (const ProfileVectorImage& other) const;

	const PVI::StretchData&			GetStretchData () const;
	void							SetStretchData (const PVI::StretchData& newStrechData);

	const GS::HashTable<GS::Guid, PVI::HatchVertexId>&	GetAssociatedHotspotsTable () const;

	void							SetDrawQueueUsing ();
	void							SetScale (Int32 defScaleIn);

	GSErrCode						SetStructureComponentId (const GS::Guid& hatchGuid, const StructureComponentId& structureComponentId);
	StructureComponentId			GetStructureComponentId (const GS::Guid& hatchGuid) const;
	const GS::HashTable<GS::Guid, StructureComponentId>&	GetHatchUniqeIdToStructureComponentIdTable () const;
	GS::Array<const HatchObject*>	GetHatchesToStructureComponentId (const StructureComponentId& structureComponentId) const;


	void				ConvertFromVectorImage (const VectorImage& source);
	void				Clear ();
	bool				Compare (const ProfileVectorImage& op) const;
	bool				Compare (const ProfileVectorImage& op, double eps, const VectorImageDataMask& compareMask) const;

	GSErrCode			WriteForChecksum (GS::OChannel& oc) const;
	GSErrCode			WriteForChecksum (GS::OChannel& oc, double eps, const VectorImageDataMask& mask) const;

	GSErrCode			CheckAndRepair ();
	bool				IsEmpty () const;

	ULong				GetItemCountOfType (SyEnum typeID) const;
	GSErrCode			GetItemPointsOfType (SyEnum typeID, GS::Array<Coord>& points) const;
	Box2DData			GetBounds (bool withoutHotspots = false) const;
	Box2DData			GetBuildingBounds () const;
	Box2DData			GetCoreBuildingBounds () const;
	Box2DData			GetWithoutFinishBuildingBounds () const;
	void				AppendImage (const ProfileVectorImage&	oper,
									 IGetGradientFillType*		getFillType,
									 const VI::Transformer&		transformer);

	GSErrCode			Write (GS::OChannel& channel) const;
	GSErrCode			WriteAC21 (GS::OChannel& channel) const;
	GSErrCode			Read (GS::IChannel& channel);
	GSErrCode			WriteXML (GS::XMLOChannel& channel) const;
	GSErrCode			ReadXML (GS::XMLIChannel& channel);

	GSErrCode			AddHatchFromPolygon (Sy_HatchType&												hatchRef,					// can throw
											 HatchObject&												hatchObj,
											 const Geometry::IrregularPolygon2D&						polygon,
											 const IPolygonDrawingDirection*							drawingDirection,
											 const ProfileItem*											profileItem,
											 const ProfileEdgeDataTable*	profileEdgeData);

	GSErrCode			AddHatch (Sy_HatchType& hatchRef, HatchObject& hatchObj);

	void				AddHatchObsolete (bool					contVis,
								  const VBAttr::ExtendedPen&	contPen,
								  const ADB::AttributeIndex&	contLTyp,
								  const ADB::AttributeIndex&	buildMatIdx,
								  const ADB::AttributeIndex&	fillind,
								  VBAttr::OverriddenExtendedPen	fillPen,
								  VBAttr::OverriddenPen			bkgPen,
								  GX::Pattern::HatchTran		hatchTrafo,
								  Int32							npb,
								  const UInt32*					boends,
								  Int32							npc,
								  const Coord*					coords,
								  const double*					angles,
								  short							fillTypeDetermination,
								  GSConstHandle					addInfo,
								  const StructureComponentId*	structureComponentId,
								  const GS::Optional<GS::Guid>&	requiredId = GS::NoValue);

	void				AddSplineRecConst (const Sy_SplineType&			spline,
										   const char*					pCoordPtr,
										   const char*					pSDirsPtr,
										   const Geometry::Vector2d*	offsCo);

	void				AddRichTextRec (const Sy_RichTextType* richtext);
	void				AddPixMapRec (const Sy_PixMapType& pixHeader, GSConstHandle pixMemoHdl, const char*	mimeType);
	void				AddLineRec (const Sy_LinType& line);
	void				AddHotspotRec (const Sy_HotType& hotspot);
	void				AddFontRec (const Sy_FontType& font, const GS::UniString& fontName);
	void				AddArcRec (const Sy_ArcType& arc);

	GSErrCode			AddParameterTable (const ParameterToDefinitionsTableType& newParTable);
	GSErrCode			AddProfileParameter (const PVI::ProfileParameterId& paramID);
	GSErrCode			AddProfileParameterDef (const PVI::ProfileParameterId& paramID, 
												const PVI::ProfileParameterSetupId& id, const PVI::ProfileVectorImageParameter& newParameter);
	GSErrCode			AddProfileParameterDef (const PVI::ProfileParameterSetupId& id, const PVI::ProfileVectorImageParameter& newParameter);
	GSErrCode			AddAnchor (const PVI::ProfileAnchorId& id, const PVI::Anchor& newAnchor);
	GSErrCode			ReplaceAnchor (const PVI::ProfileAnchorId& id, const PVI::Anchor& newAnchor);
	GSErrCode			AddDimControlTool (const PVI::ProfileDimControlToolId& dimToolID, const PVI::DimensionControlTool& tool);
	GSErrCode			ReplaceDimControlTool (const PVI::ProfileDimControlToolId& dimToolID, const PVI::DimensionControlTool& tool);

	void				AddEdgeOverrideData (const PVI::EdgeOverrideData edgeOverrideData);

	void				DetectAndSetupAssociativehotspots (const VI::HatchPriority::HatchPriorityComparer& comparer);


	const ParameterToDefinitionsTableType&													GetParameterTable () const { return parameterToDefinitionsTable; }

	bool																					HasParameter (const PVI::ProfileParameterId& parameterID) const;
	const GS::HashSet<PVI::ProfileParameterSetupId>&										GetSetupIDs (const PVI::ProfileParameterId& parameterID) const;
	const GS::HashTable<PVI::ProfileParameterSetupId, PVI::ProfileVectorImageParameter>&	GetParameterDefs () const;
	const PVI::ProfileVectorImageParameter&													GetParameterDef (const PVI::ProfileParameterSetupId& paramId) const;

	GS::Optional<PVI::Anchor>																GetAnchor (const PVI::ProfileAnchorId& anchorId) const;
	void 																					GetAnchors (GS::HashTable<PVI::ProfileAnchorId, PVI::Anchor>& anchors) const;

	GS::Optional<PVI::DimensionControlTool>													GetDimensionControlTool (const PVI::ProfileDimControlToolId& dimId) const;
	void																					GetDimensionControlTools (GS::HashTable<PVI::ProfileDimControlToolId, PVI::DimensionControlTool>& dims) const;

	void												GetStretchLimits (double& horLowLimit, double& horHighLimit,
																		  double& vertLowLimit, double& vertHighLimit) const;
	const PVI::EdgeOverrideData&						GetEdgeOverrideData () const;

	const GS::HashTable<GS::Guid, HatchObject>&			GetConstHatchObjects (void) const;
	const HatchObject*									GetHatchObject (const GS::Guid& hatchId) const;
	const HatchObject&									GetHatchObject (const Sy_HatchType& hatchRef) const;
	HatchObject&										GetHatchObject (const Sy_HatchType& hatchRef);

	void												Transform (const Geometry::Transformation2D& tran, ProfileVectorImage& resultingImage) const;
	void												Transform (const TRANMAT& tran, ProfileVectorImage& resultingImage) const;
	void												Transform (const VI::Transformer& transformer);
	void												OffsetImage (const Geometry::Vector2d& offset);
	void												Copy (ProfileVectorImage& target, IVectorImagePartialCopy& callback) const;

	const VectorImage&									GetVectorImage () const;
	friend class VectorImageAccessGuard;				// Use this for write access of the VectorImage

private:
	GS::Optional<PVI::Anchor>							GetBuiltInAnchor (const PVI::ProfileAnchorId& anchorId) const;
	GS::Optional<PVI::DimensionControlTool>				GetBuiltInDimensionControlTool (const PVI::ProfileDimControlToolId& dimId) const;
	void												AddBuiltInAnchor (const PVI::ProfileAnchorId& anchorId, GS::HashTable<PVI::ProfileAnchorId, PVI::Anchor>& anchors) const;
	void												AddBuiltInDimTool (const PVI::ProfileDimControlToolId& dimId, GS::HashTable<PVI::ProfileDimControlToolId, PVI::DimensionControlTool>& dims) const;

	bool CheckParameter	(const PVI::ProfileParameterSetupId& id, const PVI::ProfileVectorImageParameter& parameter) const;
	bool CheckNewParameter (const PVI::ProfileParameterSetupId& id, const PVI::ProfileVectorImageParameter& newParameter) const;
	bool IsVertexExists (const PVI::HatchVertexId& vertexId) const;
	bool IsEdgeExists (const PVI::HatchEdgeId& edgeId) const;
};

class VI_DLL_CLASS_EXPORT VectorImageAccessGuard {
private:
	ProfileVectorImage* profileImage;
public:
	explicit VectorImageAccessGuard (ProfileVectorImage* pvi);

	~VectorImageAccessGuard (); //Called after the VectorImage write access is revoked
	
	operator VectorImage&();
};

#endif
