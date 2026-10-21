#if !defined (APIDEFS_ANALYTICALELEMENTS_H)
#define APIDEFS_ANALYTICALELEMENTS_H

#include "AnalyticalModelAPIExport.hpp"

//from GSRoot
#include "Array.hpp"
#include "HashCommon.hpp"

//from ARCHICADAPI
#include "APIdefs_Base.h"
#include "APIdefs_Elements.h"


extern "C" {


ANALYTICALMODELAPI_EXPORT extern const API_Guid API_AnalyticalSupportID;
ANALYTICALMODELAPI_EXPORT extern const API_Guid API_AnalyticalLinkID;
ANALYTICALMODELAPI_EXPORT extern const API_Guid API_AnalyticalPointLoadID;
ANALYTICALMODELAPI_EXPORT extern const API_Guid API_AnalyticalEdgeLoadID;
ANALYTICALMODELAPI_EXPORT extern const API_Guid API_AnalyticalSurfaceLoadID;


/**
 * @brief Describes the type of the Structural Analytical Model Member Part Ref.
 * @ingroup Analytical
 * @since Archicad 25
 */
enum API_AnalyticalMemberPartRefType : UInt16 {

	/** References the beginning node of a curve or an arbitrary node of a surface. */
	API_AMPartRef_BegVertex		= 1,

	/** References the ending node. */
	API_AMPartRef_EndVertex		= 2,

	/** References an internal node. */
	API_AMPartRef_CustomVertex	= 3,

	/** References an edge. */
	API_AMPartRef_Edge			= 4,

	/** References a part of an edge. */
	API_AMPartRef_RatioEdge		= 5,

	/** References a surface. */
	API_AMPartRef_Surface		= 6,

	/** References a subregion of a surface. */
	API_AMPartRef_CustomSurface = 7,

	/** References a custom edge of a surface. */
	API_AMPartRef_CustomEdge	= 8

};

/**
 * @brief Describes a Structural Analytical Model Analytical Member part.
 * @class API_InternalAnalyticalMemberPartId
 * @ingroup Analytical
 * @since Archicad 25
 */
class API_InternalAnalyticalMemberPartId {
public:
/**
 * @brief This value represents the index of the contour.
 * @var contourIdx
 */
	UIndex contourIdx;

/**
 * @brief This value represents the index of the edge or vertex.
 * @var edgeOrVertexIdx
 */
	UIndex edgeOrVertexIdx;

/**
 * @brief This value represents the index of the edge fragment.
 * @var edgeFragmentIndex
 */
	UIndex edgeFragmentIndex;

/**
 * @brief Comparison operator for API_InternalAnalyticalMemberPartId.
 * @param right The other API_InternalAnalyticalMemberPartId object.
 * @return True if the two objects are equal.
 */
	bool	operator==	(const API_InternalAnalyticalMemberPartId& right) const
	{
		return contourIdx			== right.contourIdx
			&& edgeOrVertexIdx		== right.edgeOrVertexIdx
			&& edgeFragmentIndex	== right.edgeFragmentIndex;
	}

/**
 * @brief Generates a hash value to use API_InternalAnalyticalMemberPartId type in GSRoot containers.
 * @return A hash value.
 */
	ULong	GenerateHashValue () const
	{
		return GS::CalculateHashValue (contourIdx, edgeOrVertexIdx, edgeFragmentIndex);
	}

};


/**
 * @brief Describes a vertex when the analytical member part has the custom vertex type.
 * @struct API_AMPartRefCustomVertexData
 * @ingroup Analytical
 * @since Archicad 25
 */
struct API_AMPartRefCustomVertexData {

/**
 * @brief The global coordinate of the referenced internal node of the member. This member's GUID is stored in API_AnalyticalMemberPartRef.
 * @var customVertexCoord
 */
	API_Coord3D							customVertexCoord;

};


/**
 * @brief Describes the ratios when the analytical member part has the ratio edge type.
 * @struct API_AMPartRefRatioEdgeData
 * @ingroup Analytical
 * @since Archicad 25
 */
struct API_AMPartRefRatioEdgeData {

/**
 * @brief This value represents the location of the start node on the edge (percentage).
 * @var ratioStart
 */
	double								ratioStart;

/**
 * @brief This value represents the location of the end node on the edge (percentage).
 * @var ratioEnd
 */
	double								ratioEnd;

};


/**
 * @brief Describes a Structural Analytical Model Analytical Member part reference.
 * @struct API_AnalyticalMemberPartRef
 * @ingroup Analytical
 * @since Archicad 25
 */
struct API_AnalyticalMemberPartRef {

/**
 * @brief The referenced Structural Analytical Model Member.
 * @var elemGuid
 */
	API_Guid							elemGuid;

/**
 * @brief The type of the reference.
 * @var partRefType
 */
	API_AnalyticalMemberPartRefType		partRefType;

/**
 * @brief Identifies the edge or the vertex.
 * @var partId
 */
	API_InternalAnalyticalMemberPartId	partId;

/**
 * @brief Contains the vertex coordinate when partRefType is API_AMPartRef_CustomVertex.
 * @var customVertexData
 */
	API_AMPartRefCustomVertexData		customVertexData;

/**
 * @brief Contains the ratios when partRefType is API_AMPartRef_RatioEdge.
 * @var ratioEdgeData
 */
	API_AMPartRefRatioEdgeData			ratioEdgeData;

};

// --- AnalyticalNode ----------------------------------------------------------

/**
 * @brief Describes a Structural Analytical Node.
 * @struct API_AnalyticalNode
 * @ingroup Element
 * @since Archicad 25
 */
struct API_AnalyticalNode {

/**
 * @brief Unique identifier of the Structural Analytical Node.
 * @var nodeId
 */
	UInt32					nodeId;

/**
 * @brief The 3D coordinate of the Structural Analytical Node.
 * @var coord
 */
	API_Coord3D				coord;

};

// --- AnalyticalCurve ---------------------------------------------------------

/**
 * @brief Describes the type of the Structural Analytical Model Curve.
 * @ingroup Element
 * @since Archicad 25
 */
typedef enum {
	/** The Structural Analytical Model Curve is a simple line segment. */
	API_AnalyticalCurve_LineType,

	/** The Structural Analytical Model Curve is an arc segment. */
	API_AnalyticalCurve_ArcType,

	/** The Structural Analytical Model Curve is a spline multi point segment. */
	API_AnalyticalCurve_SplineType,

	/** The Structural Analytical Model Curve is a Bezier arc segment. */
	API_AnalyticalCurve_BezierType,

	/** The Structural Analytical Model Curve is an ellipse arc segment. */
	API_AnalyticalCurve_EllipseType,

} API_AnalyticalCurveType;

/**
 * @brief Describes a Structural Analytical Model Curve that is either a line segment between two Structural Analytical Model Nodes, or an arc segment with a specified intermediate point.
 * @struct API_AnalyticalCurve
 * @ingroup Element
 * @since Archicad 25
 * @remarks The midCoords member holds valid data only in the case of arc or multi-point segments. Its content is undefined for line segments.
 */
struct API_AnalyticalCurve {

/**
 * @brief The type of the Structural Analytical Model Curve.
 * @var type
 */
	API_AnalyticalCurveType			type;

/**
 * @brief The beginning Node of the Structural Analytical Model Curve.
 * @var begNode
 */
	API_AnalyticalNode				begNode;

/**
 * @brief The ending Node of the Structural Analytical Model Curve.
 * @var endNode
 */
	API_AnalyticalNode 				endNode;

/**
 * @brief The intermediate point coordinates in the case of arc or multi-point segments.
 * @var midCoords
 */
	GS::Array<API_Coord3D>			midCoords;

};


// Analytical Support

/**
 * @brief Describes the type of the Structural Analytical Model coordinate system.
 * @ingroup Analytical
 * @since Archicad 25
 */
enum API_AnalyticalCoordSysDirection : UInt16 {

	/** Represented in the global coordinate system. */
	API_Global	= 1,

	/** Represented in the local coordinate system. */
	API_Local	= 2,

};

/**
 * @brief Describes the type of the Structural Analytical Model rigidity class.
 * @ingroup Analytical
 * @since Archicad 25
 */
enum API_AnalyticalRigidityType : UInt16 {

	/** The element is free for translation or rotation. */
	API_FreeType					= 1,

	/** The element is rigid against translation or rotation. */
	API_RigidType					= 2,

	/** The element allows translation or rotation with a specific value. */
	API_CustomType					= 3,

	/** The element is rigid against compression. */
	API_RigidCompressionOnlyType	= 4,

	/** The element is rigid against tension. */
	API_RigidTensionOnlyType		= 5,

	/** The element allows compression until a certain amount of force is applied. */
	API_CustomCompressionOnlyType	= 6,

	/** The element allows tension until a certain amount of force is applied. */
	API_CustomTensionOnlyType		= 7,

};

/**
 * @brief Describes the type of the Structural Analytical Model Analytical Support.
 * @ingroup Analytical
 * @since Archicad 25
 */
enum API_AnalyticalSupport_SupportType : UInt16 {

	/** Support at a simple point. */
	API_SimplePoint = 1,

	/** Support along a curve. */
	API_SingleLine	= 2,

	/** Support on a surface. */
	API_Surface		= 3

};

/**
 * @brief Contains the Structural Analytical Model Analytical Support values.
 * @struct API_AnalyticalSupport_SupportValues
 * @ingroup Analytical
 * @since Archicad 25
 */
struct API_AnalyticalSupport_SupportValues {

/**
 * @brief Translation type in the X direction.
 * @var xType
 */
	API_AnalyticalRigidityType				xType;

/**
 * @brief Translation value in the X direction in case of Custom type.
 * @var xValue
 */
	double									xValue;

/**
 * @brief Translation type in the Y direction.
 * @var yType
 */
	API_AnalyticalRigidityType				yType;

/**
 * @brief Translation value in the Y direction in case of Custom type.
 * @var yValue
 */
	double									yValue;

/**
 * @brief Translation type in the Z direction.
 * @var zType
 */
	API_AnalyticalRigidityType				zType;

/**
 * @brief Translation value in the Z direction in case of Custom type.
 * @var zValue
 */
	double									zValue;

/**
 * @brief Rotation type in the X direction.
 * @var rxType
 */
	API_AnalyticalRigidityType				rxType;

/**
 * @brief Rotation value in the X direction in case of Custom type.
 * @var rxValue
 */
	double									rxValue;

/**
 * @brief Rotation type in the Y direction.
 * @var ryType
 */
	API_AnalyticalRigidityType				ryType;

/**
 * @brief Rotation value in the Y direction in case of Custom type.
 * @var ryValue
 */
	double									ryValue;

/**
 * @brief Rotation type in the Z direction.
 * @var rzType
 */
	API_AnalyticalRigidityType				rzType;

/**
 * @brief Rotation value in the Z direction in case of Custom type.
 * @var rzValue
 */
	double									rzValue;

};

/**
 * @brief Describes the Structural Analytical Model Analytical Support settings.
 * @struct API_AnalyticalSupport_Settings
 * @ingroup Analytical
 * @since Archicad 25
 */
struct API_AnalyticalSupport_Settings {

/**
 * @brief The type of the Analytical Support.
 * @var supportType
 */
	API_AnalyticalSupport_SupportType		supportType;

/**
 * @brief The Analytical Support values.
 * @var supportValues
 */
	API_AnalyticalSupport_SupportValues		supportValues;

/**
 * @brief The coordinate system definition.
 * @var coordinateSystem
 */
	API_AnalyticalCoordSysDirection			coordinateSystem;

};

/**
 * @brief Describes a Structural Analytical Model Member Support.
 * @struct API_AnalyticalSupportType
 * @ingroup Analytical
 * @since Archicad 25
 */
struct API_AnalyticalSupportType {

/**
 * @brief The Analytical Support settings.
 * @var supportSettings
 */
	API_AnalyticalSupport_Settings	supportSettings;

/**
 * @brief The Analytical Member part reference where the Analytical Support is applied.
 * @var supportedMemberPartRef
 */
	API_AnalyticalMemberPartRef		supportedMemberPartRef;

};


/**
 * @brief Describes a Structural Analytical Model Analytical Support Geometry.
 * @struct API_AnalyticalSupportGeometry
 * @ingroup Analytical
 * @since Archicad 25
 */
struct API_AnalyticalSupportGeometry {

/**
 * @brief Positions of the analytical support
 * @var coordinates
 */
	GS::Array<API_Coord3D>		coordinates;

/**
 * @brief Support's translation stiffness vector in the start member's coordinate system.
 * @var translationStiffnessVector
 */
	API_Vector3D				translationStiffnessVector;

/**
 * @brief Support's rotation stiffness vector in the start member's coordinate system.
 * @var rotationStiffnessVector
 */
	API_Vector3D				rotationStiffnessVector;

};


// Analytical Link

/**
 * @brief Describes the type of the Structural Analytical Model Analytical Link.
 * @ingroup Analytical
 * @since Archicad 25
 */
enum API_AnalyticalLink_LinkType : UInt16 {

	/** The Structural Analytical Model Analytical Link is of rigid type. */
	API_Rigid	= 1,

	/** The Structural Analytical Model Analytical Link is of spring type. */
	API_Spring	= 2,

};

/**
 * @brief Describes the geometry of the Structural Analytical Model Analytical Link.
 * @ingroup Analytical
 * @since Archicad 25
 */
enum API_AnalyticalLink_LinkGeometry : UInt16 {

	/** A virtual connection between two nodes */
	API_Link1D	 = 1,

	/** A rigid connection between two entities. */
	API_Link2D	 = 2

};

/**
 * @brief Describes the type of the Structural Analytical Model Analytical Rigid Link connection.
 * @ingroup Analytical
 * @since Archicad 25
 */
enum API_AnalyticalLink_RigidLinkConnectionType : UInt16 {

	/** Connection is of rigid type. */
	API_RigidConnection = 1,

	/** Connection is of hinge type. */
	API_HingeConnection = 2,

};

/**
 * @brief Describes the translation of an analytical link.
 * @struct API_AnalyticalLink_Translation
 * @ingroup Analytical
 * @since Archicad 25
 */
struct API_AnalyticalLink_Translation {

/**
 * @brief Rigidity type in the X direction.
 * @var kxType
 */
	API_AnalyticalRigidityType		kxType;

/**
 * @brief Rigidity value in the X direction.
 * @var kxValue
 */
	double							kxValue;

/**
 * @brief Rigidity type in the Y direction.
 * @var kyType
 */
	API_AnalyticalRigidityType		kyType;

/**
 * @brief Rigidity value in the Y direction.
 * @var kyValue
 */
	double							kyValue;

/**
 * @brief Rigidity type in the Z direction.
 * @var kzType
 */
	API_AnalyticalRigidityType		kzType;

/**
 * @brief Rigidity value in the Z direction.
 * @var kzValue
 */
	double							kzValue;

/**
 * @brief Resistance value along the X axis.
 * @var resistanceFx
 */
	bool							resistanceFx;

/**
 * @brief Resistance value along the Y axis.
 * @var resistanceFy
 */
	bool							resistanceFy;

/**
 * @brief Resistance value along the Z axis.
 * @var resistanceFz
 */
	bool							resistanceFz;

/**
 * @brief Rotation value in the X direction.
 * @var fxValue
 */
	double							fxValue;

/**
 * @brief Rotation value in the Y direction.
 * @var fyValue
 */
	double							fyValue;

/**
 * @brief Rotation value in the Z direction.
 * @var fzValue
 */
	double							fzValue;

};

/**
 * @brief Contains the Structural Analytical Model Analytical Link Rotation values.
 * @struct API_AnalyticalLink_Rotation
 * @ingroup Analytical
 * @since Archicad 25
 */
struct API_AnalyticalLink_Rotation {

/**
 * @brief Rigidity type in the X direction.
 * @var kxxType
 */
	API_AnalyticalRigidityType		kxxType;

/**
 * @brief Rigidity value in the X direction.
 * @var kxxValue
 */
	double							kxxValue;

/**
 * @brief Rigidity type in the Y direction.
 * @var kyyType
 */
	API_AnalyticalRigidityType		kyyType;

/**
 * @brief Rigidity value in the Y direction.
 * @var kyyValue
 */
	double							kyyValue;

/**
 * @brief Rigidity type in the Z direction.
 * @var kzzType
 */
	API_AnalyticalRigidityType		kzzType;

/**
 * @brief Rigidity value in the Z direction.
 * @var kzzValue
 */
	double							kzzValue;

/**
 * @brief Resistance value along the X axis.
 * @var resistanceMx
 */
	bool							resistanceMx;

/**
 * @brief Resistance value along the Y axis.
 * @var resistanceMy
 */
	bool							resistanceMy;

/**
 * @brief Resistance value along the Z axis.
 * @var resistanceMz
 */
	bool							resistanceMz;

/**
 * @brief Rotation value in the X direction.
 * @var mxValue
 */
	double							mxValue;

/**
 * @brief Rotation value in the Y direction.
 * @var myValue
 */
	double							myValue;

/**
 * @brief Rotation value in the Z direction.
 * @var mzValue
 */
	double							mzValue;

};

/**
 * @brief Describes the rigidity settings on both sides of the Structural Analytical Model Analytical Link element.
 * @struct API_AnalyticalLink_RigidSettings
 * @ingroup Analytical
 * @since Archicad 25
 */
struct API_AnalyticalLink_RigidSettings {

/**
 * @brief The start connection type.
 * @var startConnectionType
 */
	API_AnalyticalLink_RigidLinkConnectionType startConnectionType;

/**
 * @brief The end connection type.
 * @var endConnectionType
 */
	API_AnalyticalLink_RigidLinkConnectionType endConnectionType;

};

/**
 * @brief Describes the spring settings of the Structural Analytical Model Analytical Link element.
 * @struct API_AnalyticalLink_SpringSettings
 * @ingroup Analytical
 * @since Archicad 25
 */
struct API_AnalyticalLink_SpringSettings {

/**
 * @brief Coordinate system direction settings.
 * @var direction
 */
	API_AnalyticalCoordSysDirection		direction;

/**
 * @brief Translation settings.
 * @var translation
 */
	API_AnalyticalLink_Translation		translation;

/**
 * @brief Rotation settings.
 * @var rotation
 */
	API_AnalyticalLink_Rotation			rotation;

};

/**
 * @brief Describes the Structural Analytical Model Analytical Link settings.
 * @struct API_AnalyticalLink_Settings
 * @ingroup Analytical
 * @since Archicad 25
 */
struct API_AnalyticalLink_Settings {

/**
 * @brief The category of the link's geometry.
 * @var geometry
 */
	API_AnalyticalLink_LinkGeometry		geometry;

/**
 * @brief The type of the Analytical Link.
 * @var type
 */
	API_AnalyticalLink_LinkType			type;

/**
 * @brief The rigidity settings if the Analytical Link is of rigid type.
 * @var rigidSettings
 */
	API_AnalyticalLink_RigidSettings	rigidSettings;

/**
 * @brief The spring settings if the Analytical Link is of spring type.
 * @var springSettings
 */
	API_AnalyticalLink_SpringSettings	springSettings;

};

/**
 * @brief Describes a Structural Analytical Model Analytical Link.
 * @struct API_AnalyticalLinkType
 * @ingroup Analytical
 * @since Archicad 25
 */
struct API_AnalyticalLinkType {

/**
 * @brief The Analytical Link settings.
 * @var linkSettings
 */
	API_AnalyticalLink_Settings			linkSettings;

/**
 * @brief The Analytical Member reference on one side.
 * @var startElementPartRef
 */
	API_AnalyticalMemberPartRef			startElementPartRef;

/**
 * @brief The Analytical Member reference on the other side.
 * @var endElementPartRef
 */
	API_AnalyticalMemberPartRef			endElementPartRef;

};

/**
 * @brief Describes a Structural Analytical Model Analytical Link Geometry.
 * @struct API_AnalyticalLinkGeometry
 * @ingroup Analytical
 * @since Archicad 25
 */
struct API_AnalyticalLinkGeometry {

/**
 * @brief Positions of the analytical link.
 * @var coordinates
 */
	GS::Array<API_Coord3D>			coordinates;

/**
 * @brief Describes the joining ends of a 2D link (if they are not connected to a vertex).
 * @var curves
 */
	GS::Array<API_AnalyticalCurve>	curves;

/**
 * @brief Link's translation stiffness vector in the start member's coordinate system.
 * @var translationStiffnessVector
 */
	API_Vector3D					translationStiffnessVector;

/**
 * @brief Link's rotation stiffness vector in the start member's coordinate system.
 * @var rotationStiffnessVector
 */
	API_Vector3D					rotationStiffnessVector;

};


// Loads

/**
 * @brief Describes the Structural Analytical Load force.
 * @ingroup Analytical
 * @since Archicad 25
 */
enum API_AnalyticalLoad_LoadForceType : UInt16 {

	/** Force type. */
	API_Force	= 1,

	/** Load momentum. */
	API_Moment	= 2

};

/**
 * @brief Describes the Structural Analytical Model Analytical Point Load settings.
 * @struct API_AnalyticalPointLoad_Settings
 * @ingroup Analytical
 * @since Archicad 25
 */
struct API_AnalyticalPointLoad_Settings {

/**
 * @brief The GUID of the connected Load Case.
 * @var loadCaseId
 */
	API_Guid									loadCaseId;

/**
 * @brief The force type of the Analytical Point Load. The point force can be defined in three main directions (global or local coordinate system). A node of the structure may be subject to a moment load. The load is defined by the direction and size of the moment.
 * @var loadForceType
 */
	API_AnalyticalLoad_LoadForceType			loadForceType;

/**
 * @brief The coordinate system type of the Analytical Point Load.
 * @var coordinateSystemType
 */
	API_AnalyticalCoordSysDirection				coordinateSystemType;

/**
 * @brief The force/moment value in the X direction of the Analytical Point Load.
 * @var xValue
 */
	double										xValue;

/**
 * @brief The force/moment value in the Y direction of the Analytical Point Load.
 * @var yValue
 */
	double										yValue;

/**
 * @brief The force/moment value in the Z direction of the Analytical Point Load.
 * @var zValue
 */
	double										zValue;

};

/**
 * @brief Describes a Structural Analytical Model Member Point Load.
 * @struct API_AnalyticalPointLoadType
 * @ingroup Analytical
 * @since Archicad 25
 * @remarks A Point Load element can be created using ACAPI_Element_Create and removed using ACAPI_Element_Delete. Currently, the ACAPI_Element_Change function is unavailable for Analytical Point Loads.
 */
struct API_AnalyticalPointLoadType {
/**
 * @brief Describes the Structural Analytical Model Analytical Point Load settings.
 * @var analyticalPointLoadSettings
 */
	API_AnalyticalPointLoad_Settings	analyticalPointLoadSettings;

/**
 * @brief Describes a Structural Analytical Model Analytical Member part.
 * @var loadedMemberPartRef
 */
	API_AnalyticalMemberPartRef			loadedMemberPartRef;

};

/**
 * @brief Describes a Structural Analytical Model Analytical Point Load Geometry.
 * @struct API_AnalyticalPointLoadGeometry
 * @ingroup Analytical
 * @since Archicad 25
 */
struct API_AnalyticalPointLoadGeometry {

/**
 * @brief Position of the Analytical Point Load.
 * @var coordinate
 */
	API_Coord3D					coordinate;

};


/**
 * @brief Describes the distribution type of the Structural Analytical Edge Load. The load may be either constant along the 1D member or linearly variable (trapezoidal).
 * @ingroup Analytical
 * @since Archicad 25
 */
enum API_AnalyticalLoad_LoadDistributionType : UInt16 {

	/** The load is constant along the 1D member. */
	API_Uniform		= 1,

	/** The load is linearly variable. */
	API_Trapezoid	= 2

};

/**
 * @brief Describes the Structural Analytical Model Analytical Edge Load settings.
 * @struct API_AnalyticalEdgeLoad_Settings
 * @ingroup Analytical
 * @since Archicad 25
 */
struct API_AnalyticalEdgeLoad_Settings {

/**
 * @brief The GUID of the connected Load Case.
 * @var loadCaseId
 */
	API_Guid									loadCaseId;

/**
 * @brief The force type of the Analytical Edge Load. The edge force can be defined in three main directions (global or local coordinate system). An edge of the structure may be subject to a moment load. The load is defined by the direction and size of the moment.
 * @var loadForceType
 */
	API_AnalyticalLoad_LoadForceType			loadForceType;

/**
 * @brief The load may be either constant along the 1D member or linearly variable (trapezoidal).
 * @var loadDistributionType
 */
	API_AnalyticalLoad_LoadDistributionType		loadDistributionType;

/**
 * @brief Defines the coordinate system of the member in which the load is applied. For "Local", the coordinate system is defined by the member where the load is applied.
 * @var coordinateSystemType
 */
	API_AnalyticalCoordSysDirection				coordinateSystemType;

/**
 * @brief The start force/moment value of the Analytical Edge Load in the X, Y, and Z directions.
 * @var startValue
 */
	API_Vector3D								startValue;

/**
 * @brief The end force/moment value of the Analytical Edge Load in the X, Y, and Z directions.
 * @var endValue
 */
	API_Vector3D								endValue;

};


/**
 * @brief Describes a Structural Analytical Model Member Edge Load.
 * @struct API_AnalyticalEdgeLoadType
 * @ingroup Analytical
 * @since Archicad 25
 * @remarks An Edge Load element can be created using ACAPI_Element_Create and removed using ACAPI_Element_Delete. Currently, the ACAPI_Element_Change function is unavailable for Analytical Edge Loads.
 */
struct API_AnalyticalEdgeLoadType {
/**
 * @brief Describes the Structural Analytical Model Analytical Edge Load settings.
 * @var analyticalEdgeLoadSettings
 */
	API_AnalyticalEdgeLoad_Settings		analyticalEdgeLoadSettings;

/**
 * @brief The Analytical Member part reference where the Analytical Edge Load is applied.
 * @var loadedMemberPartRef
 */
	API_AnalyticalMemberPartRef			loadedMemberPartRef;

};


/**
 * @brief Describes the Structural Analytical Model Analytical Surface Load settings.
 * @struct API_AnalyticalSurfaceLoad_Settings
 * @ingroup Analytical
 * @since Archicad 25
 */
struct API_AnalyticalSurfaceLoad_Settings {

/**
 * @brief The GUID of the connected Load Case.
 * @var loadCaseId
 */
	API_Guid									loadCaseId;

/**
 * @brief Defines the coordinate system of the member in which the load is applied. For "Local", the coordinate system is defined by the member where the load is applied.
 * @var coordinateSystemType
 */
	API_AnalyticalCoordSysDirection				coordinateSystemType;

/**
 * @brief The force/moment value in the X direction of the Analytical Surface Load.
 * @var xValue
 */
	double										xValue;

/**
 * @brief The force/moment value in the Y direction of the Analytical Surface Load.
 * @var yValue
 */
	double										yValue;

/**
 * @brief The force/moment value in the Z direction of the Analytical Surface Load.
 * @var zValue
 */
	double										zValue;

};


/**
 * @brief Describes a Structural Analytical Model Member Surface Load.
 * @struct API_AnalyticalSurfaceLoadType
 * @ingroup Analytical
 * @since Archicad 25
 * @remarks A Surface Load element can be created using ACAPI_Element_Create and removed using ACAPI_Element_Delete. Currently, the ACAPI_Element_Change function is unavailable for Analytical Surface Loads.
 */
struct API_AnalyticalSurfaceLoadType {
/**
 * @brief Describes the Structural Analytical Model Analytical Surface Load settings.
 * @var analyticalSurfaceLoadSettings
 */
	API_AnalyticalSurfaceLoad_Settings		analyticalSurfaceLoadSettings;

/**
 * @brief The Analytical Member part reference where the Analytical Surface Load is applied.
 * @var loadedMemberPartRef
 */
	API_AnalyticalMemberPartRef				loadedMemberPartRef;

};


/**
 * @brief Describes a Structural Analytical Model Analytical Edge Load %Geometry.
 * @struct API_EdgeLoadCustomData
 * @ingroup Analytical
 * @since Archicad 25
 */
struct API_EdgeLoadCustomData {

/**
 * @brief Position of the Analytical Edge Load.
 * @var curve
 */
	GS::Array<API_AnalyticalCurve>	curve;

};


/**
 * @brief Describes Custom Surface Coordinates for Surface Load.
 * @struct API_SurfaceLoadCustomData
 * @ingroup Element
 * @since Archicad 25
 */
struct API_SurfaceLoadCustomData {

/**
 * @brief The contour as a list of Structural Analytical Model Curves.
 * @var contour
 */
	GS::Array<API_AnalyticalCurve>	contour;

};



} // extern "C"


#endif
