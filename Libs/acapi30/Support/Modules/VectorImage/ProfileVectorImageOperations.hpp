#ifndef PROFILE_VECTORIMAGE_OPERATIONS_HPP
#define PROFILE_VECTORIMAGE_OPERATIONS_HPP

#pragma once

// === Includes ========================================================================================================

#include "VectorImageExport.h"
#include "VectorImageTypedefs.hpp"
#include "Polygon2D.hpp"
#include "AssociatedEdgeId.hpp"

#include "GSUtilsDefs.h"

// from CADInfrastructureBase
#include "ADBAttributeIndex.hpp"

// === Predeclarations =================================================================================================

class Box2DData;
class VectorImage;
class ProfileVectorImage;
class ProfileEdgeData;
class HatchObject;
struct ProfileItem;
class IPolygonDrawingDirection;
namespace PVI
{
	class HatchVertexId;
	class HatchEdgeId;
	class StretchData;
	class ProfileVectorImageParameter;
	class EdgeOffsetParameter;
	class Anchor;
	class DimensionControlTool;
	enum class DimProjectionType;
}


class VI_DLL_CLASS_EXPORT AnchorGeometry
{
public:
	AnchorGeometry ();

	bool isPointAnchor;
	Coord anchorPoint;
	Sector anchorEdgeSector; //Should be constructed so that positive direction is always on the right!
};


// =====================================================================================================================

class VI_DLL_CLASS_EXPORT ProfileVectorImageOperations
{
public:
	struct Dimensions
	{
		double width;
		double height;
	};

	static Dimensions CalculateBuildingDimensions (const ProfileVectorImage& profileImage);
	static Dimensions CalculateNominalDimensions (const ProfileVectorImage& profileImage);

	static void CalculateBounds (const ProfileVectorImage& profileImage,
								 Box2DData* buildingBounds, 
								 Box2DData* coreBuildingBounds = nullptr, 
								 Box2DData* withoutFinishBuildingBounds = nullptr);

	static bool HasCoreSkin				(const ProfileVectorImage& profileImage);


	static GS::Optional<Coord>						GetVertex	(const ProfileVectorImage& profileImage, const PVI::HatchVertexId& vertexId);
	static GS::Optional<Sector>						GetEdge		(const ProfileVectorImage& profileImage, const PVI::HatchEdgeId& edgeId);

	static GS::Optional<PVI::ProfileParameterId>	GetParameterToHatchEdgeId (const ProfileVectorImage& profileImage, const PVI::HatchEdgeId& edgeId);

	static PVI::AssociatedEdge::DirectionFlag		ResolveEdgeDirFlag (const ProfileVectorImage& profileImage, const PVI::HatchEdgeId& edgeID);
	static GS::Optional<AnchorGeometry>				ResolveAnchorGeometry (const ProfileVectorImage& profileImage, const PVI::ProfileAnchorId& anchorID);
	static GS::Optional<double>						CalculateParameterValue (const ProfileVectorImage& profileImage, const PVI::ProfileParameterId& parameterId);

	static void EnumerateHatchObjects				(const ProfileVectorImage& profileImage, const std::function<void (const HatchObject& hatch)> enumerator);
	static void EnumerateHatchObjectsNotConst		(ProfileVectorImage& profileImage, const std::function<void (HatchObject& hatch)> enumerator);
	static void EnumerateProfileEdgeDataNotConst	(ProfileVectorImage& profileImage, const std::function<void (const PVI::HatchEdgeId& edgeId, ProfileEdgeData& edgeData)>& enumerator);
	static void EnumerateProfileItemsNotConst		(ProfileVectorImage& profileImage, const std::function<void (const GS::Guid& hatchId, ProfileItem& profileItem)>& enumerator);

	static constexpr short GetDedicatedConstructionLayer ()			{ return 1; }
	static constexpr short GetDedicatedDraftingLayer ()				{ return 2; }
	static constexpr short GetDedicatedOpeningReferenceLineLayer ()	{ return 3; }
	static constexpr short GetDedicatedStretchLayer ()				{ return 4; }
	static bool	 IsAcceptedProfileVectorImageLayer (short layerIndex);

	static void UpdateInnerOuterLinesByTypeAndVisibility (ProfileVectorImage& profileImage);
	static GS::Array<ADB::AttributeIndex> GetBuildingMaterialIndexList (const ProfileVectorImage& profileImage);

	static UIndex		CorrigateVertexIndexByDrawingDirection (const Geometry::IrregularPolygon2D& polygon, const IPolygonDrawingDirection& polygonDrawingDirection, UIndex originalVertexIndex);
	static UIndex		CorrigateEdgeIndexByDrawingDirection (const Geometry::IrregularPolygon2D& polygon, const IPolygonDrawingDirection& polygonDrawingDirection, UIndex originalEdgeIndex);

	static VectorImage	StretchDataToVectorImage (const PVI::StretchData& stretchData, const Box2DData& profileBounds);
	static void			AddBoundingStretchZones (ProfileVectorImage& profileImage);
	static void			AddBoundingOpeningLines (ProfileVectorImage& profileImage);
	static void			AddBoundingHotSpots		(ProfileVectorImage& profileImage, UIndex firstAddedHotspotIdx = 0);
	static void			AddBoundingSideHotSpots (ProfileVectorImage& profileImage, UIndex firstAddedHotspotIdx = 0, bool addToCenter = true);

	static bool			GetOpeningPosition (const ProfileVectorImage& profileImage, double height, double* minX, double* angleAtMinX, double* maxX, double* angleAtMaxX);

	static void			CorrigateStretchZones (ProfileVectorImage& profileImage);
	static bool			ExplodeHatches (const ProfileVectorImage& vectorImg, GS::Array<ProfileVectorImage>& result);
	static void			DetectAndSetupProfileEdgeSideFlags (ProfileVectorImage& profileImage, bool* wasModifiedSideFlag = nullptr);

	static GSErrCode	AddOffsetParameter (ProfileVectorImage& profileImage, const PVI::ProfileParameterId& paramID);
	static GSErrCode	AddOffsetParameterSetup (ProfileVectorImage& profileImage, const PVI::ProfileParameterId& paramID,
												 const GS::Array<PVI::AssociatedEdge>& offsetEdgeDefs, 
												 const PVI::Anchor& begAnchor, const PVI::Anchor& endAnchor,
												 const PVI::DimProjectionType projType,
												 const double projAngleRad,
												 PVI::ProfileDimControlToolId* outDimId = nullptr);


	static PVI::ProfileDimControlToolId GetDimensionControlToolId (const PVI::ProfileBuiltInParameterId& BIParamID);
	static GS::Optional<PVI::DimensionControlTool>
						GetDimensionControlToolOfBIParam (const ProfileVectorImage& profileImage, const PVI::ProfileBuiltInParameterId& BIParamID);
	static bool			IsBuiltInParameterControlable (const ProfileVectorImage& profileImage, const PVI::ProfileBuiltInParameterId& BIParamID);
	static bool			IsParameterControlable (const ProfileVectorImage& profileImage, const PVI::ProfileParameterId& paramID);
	static void			DisableControlViaParameter (ProfileVectorImage& profileImage, const PVI::ProfileParameterId& paramID);

	
	static void			AddNominalSizeAnchors (ProfileVectorImage& profileImage, const PVI::Anchor& left, const PVI::Anchor& right, const PVI::Anchor& bottom, const PVI::Anchor& top);
	static GS::Optional<double>
						CalculateBIParamValue (const ProfileVectorImage& profileImage, const PVI::ProfileBuiltInParameterId& BIParamID);
	static void			GetNominalBounds (const ProfileVectorImage& profileImage, Box2DData& nominalBox);

	static void			CalculateBoundingBoxDeterminerPoints (const ProfileVectorImage& profileImage, 
															  GS::Array<Coord>& leftCoords, 
															  GS::Array<Coord>& rightCoords,
															  GS::Array<Coord>& bottomCoords,
															  GS::Array<Coord>& topCoords,
															  const std::function<bool (const HatchObject& hatch)>& filter);

private: 
	static GS::Optional<double>						CalculateDimValue (const ProfileVectorImage& profileImage, const PVI::ProfileParameterId& paramID, const PVI::ProfileDimControlToolId& dimID);


};


#endif
