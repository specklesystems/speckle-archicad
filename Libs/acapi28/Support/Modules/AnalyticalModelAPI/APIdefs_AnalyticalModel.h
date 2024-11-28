#ifndef GS_APIDEFS_ANALYTICALMODEL_H
#define GS_APIDEFS_ANALYTICALMODEL_H

// from ARCHICADAPI
#include "APIdefs_Base.h"
#include "APIdefs_AnalyticalElements.h"

// from VectorImage
#include "ProfileVectorImage.hpp"


extern "C" {


/* === AnalyticalModelVariation ===================================================================================== */

/**
 * @brief Describes the Model Variation that is used for creating the Structural Analytical Model.
 * @struct API_AnalyticalModelVariation
 * @ingroup Analytical
 * @since Archicad 26
 */
struct API_AnalyticalModelVariation {

/**
 * @brief The unique identifier of the model state defining an analytical model variation.
 * @var amVariationGuid
 */
	API_Guid									amVariationGuid;
};


/* === API_AnalyticalMemberType ===================================================================================== */

/**
 * @brief Describes the Structural Analytical Model Member type.
 * @enum API_AnalyticalMemberType
 * @ingroup Analytical
 * @since Archicad 25
 */
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

/**
 * @brief Describes the alignment of a Cross Section.
 * @enum API_AnalyticalAlignmentType
 * @ingroup Analytical
 * @since Archicad 26
 */
enum class API_AnalyticalAlignmentType {
	TopLeft, Top, TopRight,
	Left, Center, Right,
	BottomLeft, Bottom, BottomRight,
	None
};

/**
 * @brief Describes or references an Structural Analytical Model Cross Section for Curve Members.
 * @struct API_AnalyticalCrossSection
 * @ingroup Analytical
 * @since Archicad 26
 * @remarks In Circle profiles, the `width` and `height` represent the circle diameter.
 * 			In the case of simple type profiles with no/finish/other veneers, it contains the attribute index of the core material.
 * 			Simple type profiles with core veneer contain the attribute index of the veneer's material on the first position, and the core's on the second.
 * 			In predefined type profiles, it contains as many attribute indices as the profile's materials.
 */
struct API_AnalyticalCrossSection {

/**
 * @brief The type of the Structural Analytical Model Cross Section (simple, custom, or predefined).
 * @var crossSectionType
 */
	API_AnalyticalCrossSectionType		crossSectionType;

/**
 * @brief The width of the profile.
 * @var width
 */
	double								width;

/**
 * @brief The height of the profile.
 * @var height
 */
	double								height;

/**
 * @brief The thickness of core-type veneer in case of simple type.
 * @var veneerThickness
 */
	double								veneerThickness;

/**
 * @brief The attribute index in case of predefined type.
 * @var profileAttrIndex
 */
	API_AttributeIndex					profileAttrIndex;

	// This container may contain an arbitrary number of elements, but there are 3 cases
	// 1. Rectangular/Circular 1D member, with finish/other veneer -> 1 material
	// 2. Rectangular/Circular 1D member, with core veneer (in this case the veneerThickness is > 0.0) -> 2 material (we rely on the order of them being pushed)
	// 3. 1D member with a Profile -> arbitrary number of materials which are stored together with the Polygon2Ds when exported as a General Cross Section

/**
 * @brief The attribute indices of the profile (see the Remarks below).
 * @var materialAttrIndices
 */
	GS::Array<API_AttributeIndex>		materialAttrIndices;

/**
 * @brief Contains the GUID of the profile modifiers and the parameter values.
 * @var profileParameters
 */
	GS::HashTable<API_Guid, double>		profileParameters;

/**
 * @brief Contains the ProfileVectorImage of the profile if it is an Attribute Profile, or Custom Profile.
 * @var profileImage
 */
	GS::Optional<ProfileVectorImage>	profileImage;

/**
 * @brief Describes the alignment of a Cross Section.
 * @var alignment
 */
	API_AnalyticalAlignmentType			alignment = API_AnalyticalAlignmentType::None;

};


/**
 * @brief Describes a Structural Analytical Model Varying Segment for Curve Members.
 * @struct API_AnalyticalVaryingSegment
 * @ingroup Analytical
 * @since Archicad 26
 */
struct API_AnalyticalVaryingSegment {

/**
 * @brief The begin profile of the segment. If the segment is not tapered, this is also the end profile.
 * @var begProfile
 */
	API_AnalyticalCrossSection					begProfile;

/**
 * @brief If the segment is tapared, this describes the end profile of the segment.
 * @var endProfile
 */
	GS::Optional<API_AnalyticalCrossSection>	endProfile; // Has value if segment is tapered.

/**
 * @brief The span of the Varying Segment. It should be between 0 and 1.
 * @var span
 */
	double										span = 0.0;

};


/**
 * @brief Describes an Structural Analytical Model Curve Member.
 * @struct API_AnalyticalCurveMember
 * @ingroup Analytical
 * @since Archicad 26
 */
struct API_AnalyticalCurveMember {

/**
 * @brief The type of the represented element.
 * @var analyticalMemberType
 */
	API_AnalyticalMemberType				analyticalMemberType;

/**
 * @brief The unique identifier of the represented element.
 * @var elemGuid
 */
	API_Guid								elemGuid;

/**
 * @brief The Structural Analytical Model Cross Section type.
 * @var crossSection
 */
	API_AnalyticalCrossSection				crossSection;

/**
 * @brief The curve definition.
 * @var curve
 */
	API_AnalyticalCurve						curve;

/**
 * @brief List of eventual Internal Nodes set on this Structural Analytical Model Curve Member.
 * @var internalNodes
 */
	GS::Array<API_AnalyticalNode>			internalNodes;

/**
 * @brief The rotation angle.
 * @var rotationAngle
 */
	double									rotationAngle;

/**
 * @brief The structure eccentricity on the Y axis.
 * @var ey
 */
	double									ey;

/**
 * @brief The Y axis of its local coordinate system.
 * @var eyVector
 */
	API_Vector3D							eyVector;

/**
 * @brief The structure eccentricity on the Z axis.
 * @var ez
 */
	double									ez;

/**
 * @brief The Z axis of its local coordinate system.
 * @var ezVector
 */
	API_Vector3D							ezVector;

/**
 * @brief The containing layer's attribute index.
 * @var layerAttrIndex
 */
	API_AttributeIndex						layerAttrIndex;

/**
 * @brief The FEM type of the curve member.
 * @var FEMType
 */
	API_Analytical1DFEMType					FEMType;

/**
 * @brief Describes the profiles of the segments, if the Member represents a multisegmented Beam/Column. The sum of the span values of the segments should be equal to 1.
 * @var varyingSegmentList
 */
	GS::Array<API_AnalyticalVaryingSegment>	varyingSegmentList;

};


/* === SurfaceMember ================================================================================================ */

/**
 * @brief Describes the Structural Analytical Model Surface type.
 * @enum API_AnalyticalSurfaceType
 * @ingroup Analytical
 * @since Archicad 24
 */
typedef enum {
	API_AnalyticalSurface_PlaneType,
	API_AnalyticalSurface_CylinderType,

} API_AnalyticalSurfaceType;

typedef enum {
	API_Analytical2DFEM_Plate,
	API_Analytical2DFEM_Wall,
	API_Analytical2DFEM_Shell
} API_Analytical2DFEMType;

/**
 * @brief TBD
 * @struct API_AnalyticalPlaneSurface
 * @ingroup Analytical
 * @since Archicad 24
 */
struct API_AnalyticalPlaneSurface {

/**
 * @brief The base point of the plane surface.
 * @var basePoint
 */
	API_Coord3D		basePoint;

/**
 * @brief The normal vector of the plane surface.
 * @var normalVector
 */
	API_Vector3D	normalVector;

};

/**
 * @brief TBD
 * @struct API_AnalyticalCylinderSurface
 * @ingroup Analytical
 * @since Archicad 24
 */
struct API_AnalyticalCylinderSurface {

/**
 * @brief The base point of the cylinder surface.
 * @var basePoint
 */
	API_Coord3D		basePoint;

/**
 * @brief The axis direction of the cylinder surface.
 * @var axisDirection
 */
	API_Vector3D	axisDirection;

/**
 * @brief The reference ray of the cylinder surface.
 * @var referenceRay
 */
	API_Vector3D	referenceRay;

};

/**
 * @brief Describes the Structural Analytical Model Surface of a Structural Analytical Model Surface Member.
 * @struct API_AnalyticalSurface
 * @ingroup Analytical
 * @since Archicad 24
 */
struct API_AnalyticalSurface {

/**
 * @brief Type of the surface's geometry.
 * @var surfaceType
 */
	API_AnalyticalSurfaceType				surfaceType;

/**
 * @brief Describes the geometry of the surface by a plane. Only used when the surfaceType is API_AnalyticalSurface_PlaneType.
 * @var planeSurface
 */
	API_AnalyticalPlaneSurface				planeSurface;

/**
 * @brief Describes the geometry of the surface by a cylinder. Only used when the surfaceType is API_AnalyticalSurface_CylinderType.
 * @var cylinderSurface
 */
	API_AnalyticalCylinderSurface			cylinderSurface;

};

/**
 * @brief Describes a Structural Analytical Model Surface Member.
 * @struct API_AnalyticalSurfaceMember
 * @ingroup Analytical
 * @since Archicad 25
 */
struct API_AnalyticalSurfaceMember {

/**
 * @brief The type of the represented element.
 * @var analyticalMemberType
 */
	API_AnalyticalMemberType					analyticalMemberType;

/**
 * @brief The unique identifier of the represented element.
 * @var elemGuid
 */
	API_Guid									elemGuid;

/**
 * @brief The type of the surface.
 * @var surface
 */
	API_AnalyticalSurface						surface;

/**
 * @brief The contour as a list of Structural Analytical Model Curves.
 * @var contour
 */
	GS::Array<API_AnalyticalCurve>				contour;

/**
 * @brief The list of eventual holes as a list of hole contours.
 * @var holeContours
 */
	GS::Array<GS::Array<API_AnalyticalCurve>>	holeContours;

/**
 * @brief List of eventual Internal Nodes set on this Structural Analytical Model Curve Member.
 * @var internalNodes
 */
	GS::Array<API_AnalyticalNode>				internalNodes;

/**
 * @brief The structure thickness.
 * @var thickness
 */
	double										thickness;

/**
 * @brief The X axis of the local coordinate system.
 * @var lcsXVector
 */
	API_Vector3D								lcsXVector;

/**
 * @brief The structure eccentricity.
 * @var ez
 */
	double										ez;

/**
 * @brief The structure eccentricity vector.
 * @var ezVector
 */
	API_Vector3D								ezVector;

/**
 * @brief The material attribute index that references the material in the system.
 * @var materialAttrIndex
 */
	API_AttributeIndex							materialAttrIndex;

/**
 * @brief The containing layer's attribute index.
 * @var layerAttrIndex
 */
	API_AttributeIndex							layerAttrIndex;

/**
 * @brief The FEM type of the surface member.
 * @var FEMType
 */
	API_Analytical2DFEMType						FEMType;

/**
 * @brief The unique identifier of the group containing the element.
 * @var groupId
 */
	API_Guid									groupId;

};

/**
 * @brief Describes a coordinate system.
 * @struct API_CoordinateSystem
 * @ingroup Analytical
 * @since Archicad 24
 */
struct API_CoordinateSystem {

/**
 * @brief x direction of the coordinate system
 * @var xVector
 */
	API_Vector3D	xVector;

/**
 * @brief y direction of the coordinate system
 * @var yVector
 */
	API_Vector3D	yVector;

};


/* === Export ID Mapping ============================================================================================ */

/**
 * @brief Describes the guid, contour and edge/vertex id triplet that is used for creating the API_ExportIdMappingType.
 * @class API_AnalyticalElemPartId
 * @ingroup Analytical
 * @since Archicad 24
 */
class API_AnalyticalElemPartId {
public:
/**
 * @brief This value represents the guid of the member.
 * @var memberGuid
 */
	API_Guid	memberGuid;			// possibly part of group

/**
 * @brief This value represents the index of the contour.
 * @var contourIndex
 */
	UIndex		contourIndex;

/**
 * @brief This value represents the index of the edge or vertex.
 * @var edgeOrVertexIndex
 */
	UIndex		edgeOrVertexIndex;

/**
 * @brief Generates a hash value in order to use API_AnalyticalElemPartId type in GSRoot containers.
 * @return A hash value.
 */
	ULong	GenerateHashValue () const
	{
		return GS::CalculateHashValue (memberGuid, contourIndex, edgeOrVertexIndex);
	}

/**
 * @brief Comparison operator for API_AnalyticalElemPartId.
 * @param right The other API_AnalyticalElemPartId object.
 * @return True if the two objects are equal.
 */
	bool	operator== (const API_AnalyticalElemPartId& right) const
	{
		return memberGuid == right.memberGuid
			&& contourIndex == right.contourIndex
			&& edgeOrVertexIndex == right.edgeOrVertexIndex;
	}

};


using API_ExportMappingTable = GS::HashTable<API_InternalAnalyticalMemberPartId, GS::Array<API_AnalyticalElemPartId>>;


/**
 * @brief Describes the connection between the unsegmented surface member's and the created segment's edges and vertices.
 * @struct API_ExportIdMappingType
 * @ingroup Analytical
 * @since Archicad 24
 */
struct API_ExportIdMappingType {

/**
 * @brief The mapping between edges and the segment edges.
 * @var edges
 */
	API_ExportMappingTable	edges;

/**
 * @brief The mapping between vertices and the segment vertices.
 * @var vertices
 */
	API_ExportMappingTable	vertices;

};


using API_ImportMappingTable = GS::HashTable<API_AnalyticalElemPartId, API_AnalyticalMemberPartRef>;


/**
 * @brief Describes the connection between the (un)segmented surface segments and the created member's edges and vertices.
 * @struct API_ImportIdMappingType
 * @ingroup Analytical
 * @since Archicad 24
 */
struct API_ImportIdMappingType {

/**
 * @brief The mapping between edge's partID and the Surface Element Member Part Reference.
 * @var edges
 */
	API_ImportMappingTable		edges;

/**
 * @brief The mapping between vertex's partID and the Surface Element Member Part Reference.
 * @var vertices
 */
	API_ImportMappingTable		vertices;

};


/* === AnalyticalRelease ============================================================================================ */

/**
 * @brief Contains the Structural Analytical Model Analytical Member Release values.
 * @struct API_AnalyticalReleaseDescription
 * @ingroup Analytical
 * @since Archicad 24
 */
struct API_AnalyticalReleaseDescription {

/**
 * @brief Translation type in X direction.
 * @var ux
 */
	API_AnalyticalRigidityType			ux;

/**
 * @brief Translation value in X direction in case of Custom type.
 * @var stiffnessX
 */
	double								stiffnessX;

/**
 * @brief Translation type in Y direction.
 * @var uy
 */
	API_AnalyticalRigidityType			uy;

/**
 * @brief Translation value in Y direction in case of Custom type.
 * @var stiffnessY
 */
	double								stiffnessY;

/**
 * @brief Translation type in Z direction.
 * @var uz
 */
	API_AnalyticalRigidityType			uz;

/**
 * @brief Translation value in Z direction in case of Custom type.
 * @var stiffnessZ
 */
	double								stiffnessZ;

/**
 * @brief Rotation type in X direction.
 * @var fix
 */
	API_AnalyticalRigidityType			fix;

/**
 * @brief Rotation value in X direction in case of Custom type.
 * @var stiffnessFix
 */
	double								stiffnessFix;

/**
 * @brief Rotation type in Y direction.
 * @var fiy
 */
	API_AnalyticalRigidityType			fiy;

/**
 * @brief Rotation value in Y direction in case of Custom type.
 * @var stiffnessFiy
 */
	double								stiffnessFiy;

/**
 * @brief Rotation type in Z direction.
 * @var fiz
 */
	API_AnalyticalRigidityType			fiz;

/**
 * @brief Rotation value in Z direction in case of Custom type.
 * @var stiffnessFiz
 */
	double								stiffnessFiz;

/**
 * @brief The Structural Analytical Member part referenced.
 * @var amPartRef
 */
	API_AnalyticalMemberPartRef			amPartRef;

};

/**
 * @brief Describes a Structural Analytical Model Member release.
 * @struct API_AnalyticalReleaseType
 * @ingroup Analytical
 * @since Archicad 24
 */
struct API_AnalyticalReleaseType {

/**
 * @brief The identifier of the Structural Analytical Member referenced.
 * @var guid
 */
	API_Guid									guid;

/**
 * @brief Relase settings.
 * @var releaseDescriptions
 */
	GS::Array<API_AnalyticalReleaseDescription>	releaseDescriptions;

};


/* === Analytical Load Case ========================================================================================= */

/**
 * @brief Describes the Structural Analytical Load Case Action type.
 * @enum API_AnalyticalLoadCaseActionType
 * @ingroup Analytical
 * @since Archicad 25
 */
typedef enum {
	API_AnalyticalLoadCase_PermanentAction,
	API_AnalyticalLoadCase_VariableAction,
	API_AnalyticalLoadCase_AccidentalAction,

} API_AnalyticalLoadCaseActionType;

/**
 * @brief Describes the Structural Analytical Load Case Load type.
 * @enum API_AnalyticalLoadCaseLoadType
 * @ingroup Analytical
 * @since Archicad 25
 */
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

/**
 * @brief Describes the Structural Analytical Load Case duration.
 * @enum API_AnalyticalLoadCaseDuration
 * @ingroup Analytical
 * @since Archicad 25
 */
typedef enum {
	API_AnalyticalLoadCase_LongDuration,
	API_AnalyticalLoadCase_MediumDuration,
	API_AnalyticalLoadCase_ShortDuration,
	API_AnalyticalLoadCase_InstantaneousDuration,

} API_AnalyticalLoadCaseDuration;

/**
 * @brief Describes a Structural Analytical Load Case.
 * @struct API_AnalyticalLoadCase
 * @ingroup Analytical
 * @since Archicad 25
 */
struct API_AnalyticalLoadCase {

/**
 * @brief Name of the load case.
 * @var name
 */
	GS::UniString									name;

/**
 * @brief Description of the load case.
 * @var description
 */
	GS::UniString									description;

/**
 * @brief Action type of the load case.
 * @var actionType
 */
	API_AnalyticalLoadCaseActionType				actionType;

/**
 * @brief A unique identifier of the load group which contains the represented load case.
 * @var loadGroupGuid
 */
	API_Guid										loadGroupGuid;

/**
 * @brief Load type of the load case.
 * @var loadType
 */
	API_AnalyticalLoadCaseLoadType					loadType;

/**
 * @brief Duration of the load case.
 * @var duration
 */
	GS::Optional<API_AnalyticalLoadCaseDuration>	duration;

/**
 * @brief A unique identifier of the represented load case.
 * @var loadCaseGuid
 */
	API_Guid										loadCaseGuid;

};


/* === Analytical Load Group ======================================================================================== */

/**
 * @brief Describes the Structural Analytical Load Group type.
 * @enum API_AnalyticalLoadGroupType
 * @ingroup Analytical
 * @since Archicad 25
 */
typedef enum {
	API_AnalyticalLoadGroup_PermanentLoad,
	API_AnalyticalLoadGroup_VariableLoad,
	API_AnalyticalLoadGroup_AccidentalLoad,
	API_AnalyticalLoadGroup_SeismicLoad,
	API_AnalyticalLoadGroup_MovingLoad,
	API_AnalyticalLoadGroup_TensioningLoad,
	API_AnalyticalLoadGroup_FireLoad,

} API_AnalyticalLoadGroupType;


/**
 * @brief Describes the relation of load cases in the particular load group.
 * @enum API_AnalyticalLoadGroupRelation
 * @ingroup Analytical
 * @since Archicad 25
 */
typedef enum {
	API_AnalyticalLoadGroup_ExclusiveRelation,
	API_AnalyticalLoadGroup_StandardRelation,
	API_AnalyticalLoadGroup_TogetherRelation,

} API_AnalyticalLoadGroupRelation;

/**
 * @brief Describes a Structural Analytical Load Group.
 * @struct API_AnalyticalLoadGroup
 * @ingroup Analytical
 * @since Archicad 25
 */
struct API_AnalyticalLoadGroup {

/**
 * @brief Name of the load group.
 * @var name
 */
	GS::UniString						name;

/**
 * @brief Group type of the load group.
 * @var groupType
 */
	API_AnalyticalLoadGroupType			groupType;

/**
 * @brief Relation of the load cases in the load group.
 * @var relation
 */
	API_AnalyticalLoadGroupRelation		relation;

/**
 * @brief Load type of the load group.
 * @var loadType
 */
	GS::UniString						loadType;

/**
 * @brief A unique identifier of the represented load group.
 * @var guid
 */
	API_Guid							guid;

};


/* === Analytical Load Combination ================================================================================== */

/**
 * @brief Describes the category of the Structural Analytical Load Combination.
 * @enum API_AnalyticalLoadCombinationCategory
 * @ingroup Analytical
 * @since Archicad 25
 */
typedef enum {
	API_AnalyticalLoadCombination_ULS,
	API_AnalyticalLoadCombination_SLS,
	API_AnalyticalLoadCombination_ALS,
	API_AnalyticalLoadCombination_ANS,
	API_AnalyticalLoadCombination_NotDefined,

} API_AnalyticalLoadCombinationCategory;


/**
 * @brief Describes the National code application of the Structural Analytical Load Combination.
 * @enum API_AnalyticalLoadCombinationNationalStandard
 * @since Archicad 25
 */
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


enum class API_LoadCombinationType {
	API_LoadCombinationType_Envelope,
	API_LoadCombinationType_Linear,
	API_LoadCombinationType_Nonlinear
};


/**
 * @brief Describes how a Load Case belongs to a Load Combination
 * @struct API_AnalyticalLoadFactor
 * @ingroup Analytical
 * @since Archicad 25
 */
struct API_AnalyticalLoadFactor {

/**
 * @brief Guid of Load Case.
 * @var loadCaseGuid
 */
	API_Guid				loadCaseGuid;

/**
 * @brief Load factor of the load case.
 * @var factor
 */
	GS::Optional<double>	factor;

/**
 * @brief A multiplier for e.g. increase the selfweight of the structure.
 * @var multiplier
 */
	double					multiplier;

};


/**
 * @brief Describes a Structural Analytical Load Combination.
 * @struct API_AnalyticalLoadCombination
 * @ingroup Analytical
 * @since Archicad 25
 */
struct API_AnalyticalLoadCombination {

/**
 * @brief Name of the load combination.
 * @var name
 */
	GS::UniString												name;

/**
 * @brief Description of the load combination.
 * @var description
 */
	GS::UniString												description;

/**
 * @brief The category of the load combination.
 * @var category
 */
	API_AnalyticalLoadCombinationCategory						category;

/**
 * @brief The National code application of the load combination.
 * @var nationalStandard
 */
	GS::Optional<API_AnalyticalLoadCombinationNationalStandard>	nationalStandard;

/**
 * @brief The type of the load combination.
 * @var type
 */
	GS::Optional<API_LoadCombinationType>						type;

/**
 * @brief An array which contains the load cases (and the adherent coeffients) of the load combinations.
 * @var loadFactors
 */
	GS::Array<API_AnalyticalLoadFactor>							loadFactors;

/**
 * @brief A unique identifier of the represented load combination.
 * @var guid
 */
	API_Guid													guid;

};


/* === Analytical Visibility Settings ================================================================================== */

/**
 * @brief Describes the Analytical Model Visiblity Mode
 * @enum API_AM_VisibilityMode
 * @ingroup Analytical
 * @since Archicad 26
 */
enum class API_AM_VisibilityMode {
	AnalyticalModelOnly,
	AnalyticalModelWithinEntireModel,

};


/**
 * @brief Describes the Load Visiblity Mode
 * @enum API_LoadVisibilityMode
 * @ingroup Analytical
 * @since Archicad 26
 */
enum class API_LoadVisibilityMode {
	API_LoadVisibilityMode_FilterByActive,
	API_LoadVisibilityMode_HideAll,
	API_LoadVisibilityMode_ShowAll,

};


/**
 * @brief Describes the Analytical Model Visiblity Settings
 * @struct API_AM_VisibilitySettings
 * @ingroup Analytical
 * @since Archicad 26
 */
struct API_AM_VisibilitySettings {
/**
 * @brief Describes the Analytical Model Visiblity Mode.
 * @var visibilityMode
 */
	API_AM_VisibilityMode	visibilityMode					= API_AM_VisibilityMode::AnalyticalModelOnly;

/**
 * @brief Describes whether the Analytical Model is visible.
 * @var isAnalyticalModelVisible
 */
	bool					isAnalyticalModelVisible		= false;

/**
 * @brief Describes whether the Members of the Analytical Model are transparent.
 * @var areMembersTransparent
 */
	bool					areMembersTransparent			= false;

/**
 * @brief Describes whether the Symbols of the Analytical Model are transparent.
 * @var areSymbolsTransparent
 */
	bool					areSymbolsTransparent			= false;

/**
 * @brief Describes whether the Nodes of the Analytical Model are visible.
 * @var areNodesVisible
 */
	bool					areNodesVisible					= false;

/**
 * @brief Describes whether the Releases of the Analytical Model are visible.
 * @var areReleasesVisible
 */
	bool					areReleasesVisible				= false;

/**
 * @brief Describes whether the Cross Sections of the Analytical Model are visible.
 * @var areCrossSectionsVisible
 */
	bool					areCrossSectionsVisible			= false;

/**
 * @brief Describes whether the Coordination Profiles of the Analytical Model are visible.
 * @var areCoordinationProfilesVisible
 */
	bool					areCoordinationProfilesVisible	= false;

/**
 * @brief Describes whether the Local Coordination Systems of the Analytical Model are visible.
 * @var areLocalCoordSystemsVisible
 */
	bool					areLocalCoordSystemsVisible		= false;

/**
 * @brief Visiblity mode of the Loads in the Analytical Model.
 * @var loadVisibilityMode
 */
	API_LoadVisibilityMode	loadVisibilityMode;

};


} // extern "C"


#endif /* GS_APIDEFS_ANALYTICALMODEL_H */
