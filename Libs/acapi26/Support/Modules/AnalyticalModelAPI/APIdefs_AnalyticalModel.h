#ifndef GS_APIDEFS_ANALYTICALMODEL_H
#define GS_APIDEFS_ANALYTICALMODEL_H

// from ARCHICADAPI
#include "APIdefs_Base.h"
#include "APIdefs_AnalyticalElements.h"

// from VectorImage
#include "ProfileVectorImage.hpp"


extern "C" {


/* === AnalyticalModelVariation ===================================================================================== */

struct API_AnalyticalModelVariation {
	API_Guid									renovationFilterGuid;
	GS::HashTable<API_AttributeIndex, Int32>	layerConnectionClassIds;
};


/* === API_AnalyticalMemberType ===================================================================================== */

enum class API_AnalyticalMemberType : UInt16 {
	Unknown, Beam, Column, Roof, Slab, Wall
};


/* === CurveMember ================================================================================================== */

typedef enum {
	API_CrossSection_Rectangle,
	API_CrossSection_Circle,
	API_CrossSection_Attribute,
	API_CrossSection_Custom,
} API_AnalyticalCrossSectionType;

typedef enum {
	API_Analytical1DFEM_Standard,
	API_Analytical1DFEM_AxialForceOnly,
	API_Analytical1DFEM_CompressionOnly,
	API_Analytical1DFEM_TensionOnly
} API_Analytical1DFEMType;

enum class API_AnalyticalAlignmentType {
	TopLeft, Top, TopRight,
	Left, Center, Right,
	BottomLeft, Bottom, BottomRight,
	None
};

struct API_AnalyticalCrossSection {
	API_AnalyticalCrossSectionType		crossSectionType;
	double								width;
	double								height;
	double								veneerThickness;
	API_AttributeIndex					profileAttrIndex;

	// This container may contain an arbitrary number of elements, but there are 3 cases
	// 1. Rectangular/Circular 1D member, with finish/other veneer -> 1 material
	// 2. Rectangular/Circular 1D member, with core veneer (in this case the veneerThickness is > 0.0) -> 2 material (we rely on the order of them being pushed)
	// 3. 1D member with a Profile -> arbitrary number of materials which are stored together with the Polygon2Ds when exported as a General Cross Section
	GS::Array<API_AttributeIndex>		materialAttrIndices;
	GS::HashTable<API_Guid, double>		profileParameters;
	GS::Optional<ProfileVectorImage>	profileImage;
	API_AnalyticalAlignmentType			alignment = API_AnalyticalAlignmentType::None;
};


struct API_AnalyticalVaryingSegment {
	API_AnalyticalCrossSection					begProfile;
	GS::Optional<API_AnalyticalCrossSection>	endProfile; // Has value if segment is tapered.
	double										span = 0.0;
};


struct API_AnalyticalCurveMember {
	API_AnalyticalMemberType				analyticalMemberType;
	API_Guid								elemGuid;
	API_AnalyticalCrossSection				crossSection;
	API_AnalyticalCurve						curve;
	GS::Array<API_AnalyticalNode>			internalNodes;
	double									rotationAngle;
	double									ey;
	API_Vector3D							eyVector;
	double									ez;
	API_Vector3D							ezVector;
	API_AttributeIndex						layerAttrIndex;
	API_Analytical1DFEMType					FEMType;
	GS::Array<API_AnalyticalVaryingSegment>	varyingSegmentList;
};


/* === SurfaceMember ================================================================================================ */

typedef enum {
	API_AnalyticalSurface_PlaneType,
	API_AnalyticalSurface_CylinderType,
} API_AnalyticalSurfaceType;

typedef enum {
	API_Analytical2DFEM_Plate,
	API_Analytical2DFEM_Wall,
	API_Analytical2DFEM_Shell
} API_Analytical2DFEMType;

typedef struct {
	API_Coord3D		basePoint;
	API_Vector3D	normalVector;
} API_AnalyticalPlaneSurface;

typedef struct {
	API_Coord3D		basePoint;
	API_Vector3D	axisDirection;
	API_Vector3D	referenceRay;
} API_AnalyticalCylinderSurface;

typedef struct {
	API_AnalyticalSurfaceType				surfaceType;
	API_AnalyticalPlaneSurface				planeSurface;
	API_AnalyticalCylinderSurface			cylinderSurface;
} API_AnalyticalSurface;

struct API_AnalyticalSurfaceMember {
	API_AnalyticalMemberType					analyticalMemberType;
	API_Guid									elemGuid;
	API_AnalyticalSurface						surface;
	GS::Array<API_AnalyticalCurve>				contour;
	GS::Array<GS::Array<API_AnalyticalCurve>>	holeContours;
	GS::Array<API_AnalyticalNode>				internalNodes;
	double										thickness;
	API_Vector3D								lcsXVector;
	double										ez;
	API_Vector3D								ezVector;
	API_AttributeIndex							materialAttrIndex;
	API_AttributeIndex							layerAttrIndex;
	API_Analytical2DFEMType						FEMType;
	API_Guid									groupId;
};

typedef struct {
	API_Vector3D	xVector;
	API_Vector3D	yVector;
} API_CoordinateSystem;


/* === Export ID Mapping ============================================================================================ */

class API_AnalyticalElemPartId {
public:
	API_Guid	memberGuid;			// possibly part of group
	UIndex		contourIndex;
	UIndex		edgeOrVertexIndex;

	ULong	GenerateHashValue () const
	{
		return GS::CalculateHashValue (memberGuid, contourIndex, edgeOrVertexIndex);
	}

	bool	operator== (const API_AnalyticalElemPartId& right) const
	{
		return memberGuid == right.memberGuid
			&& contourIndex == right.contourIndex
			&& edgeOrVertexIndex == right.edgeOrVertexIndex;
	}
};


using API_ExportMappingTable = GS::HashTable<API_InternalAnalyticalMemberPartId, GS::Array<API_AnalyticalElemPartId>>;


typedef struct {
	API_ExportMappingTable	edges;
	API_ExportMappingTable	vertices;
} API_ExportIdMappingType;
	

using API_ImportMappingTable = GS::HashTable<API_AnalyticalElemPartId, API_AnalyticalMemberPartRef>;


typedef struct {
	API_ImportMappingTable		edges;
	API_ImportMappingTable		vertices;
} API_ImportIdMappingType;


/* === AnalyticalRelease ============================================================================================ */

typedef struct {
	API_AnalyticalRigidityType			ux;
	double								stiffnessX;
	API_AnalyticalRigidityType			uy;
	double								stiffnessY;
	API_AnalyticalRigidityType			uz;
	double								stiffnessZ;
	API_AnalyticalRigidityType			fix;
	double								stiffnessFix;
	API_AnalyticalRigidityType			fiy;
	double								stiffnessFiy;
	API_AnalyticalRigidityType			fiz;
	double								stiffnessFiz;
	API_AnalyticalMemberPartRef			amPartRef;
} API_AnalyticalReleaseDescription;

typedef struct {
	API_Guid									guid;
	GS::Array<API_AnalyticalReleaseDescription>	releaseDescriptions;
} API_AnalyticalReleaseType;


/* === Analytical Load Case ========================================================================================= */

typedef enum {
	API_AnalyticalLoadCase_PermanentAction,
	API_AnalyticalLoadCase_VariableAction,
	API_AnalyticalLoadCase_AccidentalAction,
} API_AnalyticalLoadCaseActionType;

typedef enum {
	API_AnalyticalLoadCase_SelfWeightLoad,
	API_AnalyticalLoadCase_PrestressLoad,
	API_AnalyticalLoadCase_DynamicLoad,
	API_AnalyticalLoadCase_StaticLoad,
	API_AnalyticalLoadCase_TemperatureLoad,
	API_AnalyticalLoadCase_WindLoad,
	API_AnalyticalLoadCase_SnowLoad,
	API_AnalyticalLoadCase_MaintenanceLoad,
	API_AnalyticalLoadCase_FireLoad,
	API_AnalyticalLoadCase_MovingLoad,
	API_AnalyticalLoadCase_SeismicLoad,
	API_AnalyticalLoadCase_StandardLoad,
	API_AnalyticalLoadCase_OthersLoad,
} API_AnalyticalLoadCaseLoadType;

typedef enum {
	API_AnalyticalLoadCase_LongDuration,
	API_AnalyticalLoadCase_MediumDuration,
	API_AnalyticalLoadCase_ShortDuration,
	API_AnalyticalLoadCase_InstantaneousDuration,
} API_AnalyticalLoadCaseDuration;

typedef struct {
	GS::UniString									name;
	GS::UniString									description;
	API_AnalyticalLoadCaseActionType				actionType;
	API_Guid										loadGroupGuid;
	API_AnalyticalLoadCaseLoadType					loadType;
	GS::Optional<API_AnalyticalLoadCaseDuration>	duration;
	API_Guid										loadCaseGuid;
} API_AnalyticalLoadCase;


/* === Analytical Load Group ======================================================================================== */

typedef enum {
	API_AnalyticalLoadGroup_PermanentLoad,
	API_AnalyticalLoadGroup_VariableLoad,
	API_AnalyticalLoadGroup_AccidentalLoad,
	API_AnalyticalLoadGroup_SeismicLoad,
	API_AnalyticalLoadGroup_MovingLoad,
	API_AnalyticalLoadGroup_TensioningLoad,
	API_AnalyticalLoadGroup_FireLoad,
} API_AnalyticalLoadGroupType;


typedef enum {
	API_AnalyticalLoadGroup_ExclusiveRelation,
	API_AnalyticalLoadGroup_StandardRelation,
	API_AnalyticalLoadGroup_TogetherRelation,
} API_AnalyticalLoadGroupRelation;

typedef struct {
	GS::UniString						name;
	API_AnalyticalLoadGroupType			groupType;
	API_AnalyticalLoadGroupRelation		relation;
	GS::UniString						loadType;
	API_Guid							guid;
} API_AnalyticalLoadGroup;


/* === Analytical Load Combination ================================================================================== */

typedef enum {
	API_AnalyticalLoadCombination_ULS,
	API_AnalyticalLoadCombination_SLS,
	API_AnalyticalLoadCombination_ALS,
	API_AnalyticalLoadCombination_ANS,
	API_AnalyticalLoadCombination_NotDefined,
} API_AnalyticalLoadCombinationCategory;


typedef enum {
	API_AnalyticalLoadNationalStandard_ENULSSTRGEOSetB,
	API_AnalyticalLoadNationalStandard_ENULSSTRGEOSetC,
	API_AnalyticalLoadNationalStandard_ENAccidental1,
	API_AnalyticalLoadNationalStandard_ENAccidental2,
	API_AnalyticalLoadNationalStandard_ENSeismic,
	API_AnalyticalLoadNationalStandard_ENSLSCharacteristic,
	API_AnalyticalLoadNationalStandard_ENSLSFrequent,
	API_AnalyticalLoadNationalStandard_ENSLSQuasipermanent,
	API_AnalyticalLoadNationalStandard_IBCLRFDultimate,
	API_AnalyticalLoadNationalStandard_IBCASDultimate,
	API_AnalyticalLoadNationalStandard_IBCASDserviceability,
	API_AnalyticalLoadNationalStandard_IBCASDseismic,
	API_AnalyticalLoadNationalStandard_IBCLRFDseismic,
} API_AnalyticalLoadCombinationNationalStandard;


typedef struct {
	API_Guid				loadCaseGuid;
	GS::Optional<double>	factor;
	double					multiplier;
} API_AnalyticalLoadFactor;


typedef struct {
	GS::UniString												name;
	GS::UniString												description;
	API_AnalyticalLoadCombinationCategory						category;
	GS::Optional<API_AnalyticalLoadCombinationNationalStandard>	nationalStandard;
	GS::Array<API_AnalyticalLoadFactor>							loadFactors;
	API_Guid													guid;
} API_AnalyticalLoadCombination;


/* === Analytical Visibility Settings ================================================================================== */

enum class API_AM_VisibilityMode {
	AnalyticalModelOnly,
	AnalyticalModelWithinEntireModel,
};


enum class API_LoadVisibilityMode {
	API_LoadVisibilityMode_FilterByActive,
	API_LoadVisibilityMode_HideAll,
	API_LoadVisibilityMode_ShowAll,
};


struct API_AM_VisibilitySettings {
	API_AM_VisibilityMode	visibilityMode					= API_AM_VisibilityMode::AnalyticalModelOnly;

	bool					isAnalyticalModelVisible		= false;

	bool					areMembersTransparent			= false;
	bool					areSymbolsTransparent			= false;

	bool					areNodesVisible					= false;
	bool					areReleasesVisible				= false;
	bool					areCrossSectionsVisible			= false;
	bool					areCoordinationProfilesVisible	= false;
	bool					areLocalCoordSystemsVisible		= false;

	API_LoadVisibilityMode	loadVisibilityMode;
};


} // extern "C"


#endif /* GS_APIDEFS_ANALYTICALMODEL_H */
