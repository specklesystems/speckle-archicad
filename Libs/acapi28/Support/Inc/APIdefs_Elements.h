// *********************************************************************************************************************
// API definitions - managing Elements
//
// Module:			API
// Namespace:		-
// Contact person:	archicadapi@graphisoft.com
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APIDEFS_ELEMENTS_H)
#define	APIDEFS_ELEMENTS_H

#if defined (_MSC_VER)
#pragma once
#endif


// --- Includes	--------------------------------------------------------------------------------------------------------

//from GSRoot
#include "Array.hpp"
#include "Pair.hpp"
#include "UniString.hpp"
#include "HashCommon.hpp"
#include "Any.hpp"

//from ARCHICADAPI
#include "APIdefs_AttributeIndex.hpp"
#include "APIdefs_Base.h"
#include "APIdefs_LibraryParts.h"
#include "APIdefs_Database.h"
#include "API_Guid.hpp"
#include "API_ValueWrappers.hpp"

//! @cond Doxygen_Suppress
namespace Geometry {
	class PolyId;

	template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData> class CustomPolygon2D;
	typedef CustomPolygon2D<PolyId, PolyId, PolyId, PolyId> Polygon2D;
}
//! @endcond


namespace Modeler {
	class MeshBody;
}

class ProfileVectorImage;


// --- Compiler settings -----------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

// =============================================================================
// Element types and common header
//
// =============================================================================

/**
 * @brief The type of an element.
 * @enum API_ElemTypeID
 * @ref API_ElemType
 * 		variationID
 * @c APIVarId_Generic
 * @ingroup Element
 * @since Archicad 26
 * @remarks This is general constant which describes the different element types, and is used in most element-related operations.
 * 			Use the @c API_FirstElemType and @c API_LastElemType defines in loops that enumerate all element types.
 * 			With the @ref ACAPI_Element_GetElemTypeName goody function you can retrieve the localized name of the element types.
 */
typedef enum {
	API_ZombieElemID				= 0,

	API_WallID						= 1,
	API_ColumnID					= 2,
	API_BeamID						= 3,
	API_WindowID					= 4,
	API_DoorID						= 5,
	API_ObjectID					= 6,
	API_LampID						= 7,
	API_SlabID						= 8,
	API_RoofID						= 9,
	API_MeshID						= 10,

	API_DimensionID					= 11,
	API_RadialDimensionID			= 12,
	API_LevelDimensionID			= 13,
	API_AngleDimensionID			= 14,

	API_TextID						= 15,
	API_LabelID						= 16,
	API_ZoneID						= 17,

	API_HatchID						= 18,
	API_LineID						= 19,
	API_PolyLineID					= 20,
	API_ArcID						= 21,
	API_CircleID					= 22,
	API_SplineID					= 23,
	API_HotspotID					= 24,

	API_CutPlaneID					= 25,
	API_CameraID					= 26,
	API_CamSetID					= 27,

	API_GroupID						= 28,
	API_SectElemID					= 29,

	API_DrawingID					= 30,
	API_PictureID					= 31,
	API_DetailID					= 32,
	API_ElevationID					= 33,
	API_InteriorElevationID			= 34,
	API_WorksheetID					= 35,

	API_HotlinkID					= 36,

	API_CurtainWallID				= 37,
	API_CurtainWallSegmentID		= 38,
	API_CurtainWallFrameID			= 39,
	API_CurtainWallPanelID			= 40,
	API_CurtainWallJunctionID		= 41,
	API_CurtainWallAccessoryID		= 42,
	API_ShellID						= 43,
	API_SkylightID					= 44,
	API_MorphID						= 45,
	API_ChangeMarkerID				= 46,
	API_StairID						= 47,
	API_RiserID						= 48,
	API_TreadID						= 49,
	API_StairStructureID			= 50,
	API_RailingID					= 51,
	API_RailingToprailID			= 52,
	API_RailingHandrailID			= 53,
	API_RailingRailID				= 54,
	API_RailingPostID				= 55,
	API_RailingInnerPostID			= 56,
	API_RailingBalusterID			= 57,
	API_RailingPanelID				= 58,
	API_RailingSegmentID			= 59,
	API_RailingNodeID				= 60,
	API_RailingBalusterSetID		= 61,
	API_RailingPatternID			= 62,
	API_RailingToprailEndID			= 63,
	API_RailingHandrailEndID		= 64,
	API_RailingRailEndID			= 65,
	API_RailingToprailConnectionID	= 66,
	API_RailingHandrailConnectionID	= 67,
	API_RailingRailConnectionID		= 68,
	API_RailingEndFinishID			= 69,
	API_BeamSegmentID				= 70,
	API_ColumnSegmentID				= 71,
	API_OpeningID					= 72,

	API_ExternalElemID				= 150

} API_ElemTypeID;

#define API_FirstElemType			API_WallID
#define API_LastElemType			API_OpeningID


/**
 * @brief Array for filtering elements.
 * @typedef API_ElemFilter
 * @ingroup Element
 * @remarks This type is used in the @ref API_GhostStoryType structure. The indices of this array correspond to the @ref API_ElemTypeID enum values.
 */
typedef bool API_ElemFilter [API_LastElemType + 1];

/**
 * @brief Describes the subcategory of an element.
 * @enum API_ElemVariationID
 * @ingroup Element
 * @since Archicad 25
 * @remarks API_ElemVariationID is an extension of typeID (see @ref API_Elem_Head). These are built in subcategories. But if you register an own subtype with @ref ACAPI_LibraryPart_RegisterSubtype function you have to pass at first a four-character identifier the variationID (your signature). This is an arbitrary long value wherewith you can identify your own subtype. It is used only in case of library elems (object, lamp, window, door).
 */
typedef enum {
	APIVarId_Generic				= 0,

	APIVarId_WallEnd				= 'WAEN',
	APIVarId_Door					= 'DOOR',
	APIVarId_Skylight				= 'SKYL',
	APIVarId_Object					= 'SYMB',
	APIVarId_GridElement			= 'GREL',
	APIVarId_Light					= 'LIGH',
	APIVarId_CornerWindow			= 'CRWD',

} API_ElemVariationID;


#define APIDrwIndex_Default			0
#define APIDrwIndex_Min				1
#define APIDrwIndex_Max				14

/**
 * @brief The type of an element.
 * @struct API_ElemType
 * @ingroup Element
 * @since Archicad 26
 */
struct API_ElemType {

/**
 * @brief The typeID of the element (see @ref API_ElemTypeID).
 * @var typeID
 */
	API_ElemTypeID			typeID;

/**
 * @brief Subcategory of the element (see @ref API_ElemVariationID).
 * @var variationID
 */
	API_ElemVariationID		variationID;

/**
 * @brief The classID of the element. It is used when the typeID is @ref API_ExternalElemType.
 * @var classID
 */
	API_Guid				classID;

/**
 * @brief Default constructor.
 */
	API_ElemType () = default;

/**
 * @brief Constructor with generic type.
 * @param typeID The typeID of the element.
 */
	API_ElemType (API_ElemTypeID typeID)
		: typeID (typeID), variationID (APIVarId_Generic), classID (APINULLGuid)
	{}

/**
 * @brief Constructor.
 * @param typeID The typeID of the element.
 * @param variationID Subcategory of the element.
 */
	API_ElemType (API_ElemTypeID typeID, API_ElemVariationID variationID)
		: typeID (typeID), variationID (variationID), classID (APINULLGuid)
	{}

/**
 * @brief Constructor with external element.
 * @param classID The classID of the element.
 */
	API_ElemType (const API_Guid& classID)
		: typeID (API_ExternalElemID), variationID (APIVarId_Generic), classID (classID)
	{}

/**
 * @brief Assignment operator (by element type).
 * @param newTypeID The new element type.
 * @return Returns with reference to this.
 */
	API_ElemType&	operator= (API_ElemTypeID newTypeID)
	{
		typeID = newTypeID;
		variationID = APIVarId_Generic;
		classID = APINULLGuid;
		return *this;
	}

/**
 * @brief Assignment operator (by element class identifier).
 * @param newClassID The new element type (for external elements).
 * @return Returns with reference to this.
 */
	API_ElemType&	operator= (const API_Guid& newClassID)
	{
		typeID = API_ExternalElemID;
		variationID = APIVarId_Generic;
		classID = newClassID;
		return *this;
	}

/**
 * @brief Comparison operator (by element type).
 * @param other The element type to compare to.
 * @return True if it is equal to the other.
 */
	bool	operator== (const API_ElemType& other) const
	{
		return typeID == other.typeID && variationID == other.variationID && classID == other.classID;
	}

/**
 * @brief Comparison operator (by element type).
 * @param other The element type to compare to.
 * @return True if it is not equal to the other.
 */
	bool	operator!= (const API_ElemType& other) const
	{
		return !operator== (other);
	}

/**
 * @brief Comparison operator (by element type ID).
 * @param otherTypeID The type of the element to compare to.
 * @return True if it is equal to the otherTypeID.
 */
	bool	operator== (API_ElemTypeID otherTypeID) const
	{
		return typeID == otherTypeID;
	}

/**
 * @brief Comparison operator (by element type ID).
 * @param otherTypeID The type of the element to compare to.
 * @return True if it is not equal to otherTypeID.
 */
	bool	operator!= (API_ElemTypeID otherTypeID) const
	{
		return !operator== (otherTypeID);
	}

/**
 * @brief Comparison operator (by class ID; for external elements).
 * @param otherClassID The identifier of the element type to compare to.
 * @return True if it is equal to otherClassID.
 */
	bool operator== (const API_Guid &otherClassID) const
	{
		return classID == otherClassID;
	}

/**
 * @brief Comparison operator (by class ID; for external elements).
 * @param otherClassID the identifier of the element type to compare to
 * @return True if it is not equal to otherClassID
 */
	bool	operator!= (const API_Guid& otherClassID) const
	{
		return !operator== (otherClassID);
	}

/**
 * @brief Generates unique identifier
 * @return the unique value
 */
	ULong GenerateHashValue (void) const
	{
		return GS::CalculateHashValue (typeID, variationID, classID);
	}

};

/**
 * @brief std::hash specialization for @ref API_ElemType.
 * @struct std::hash<API_ElemType>
 * @ingroup Element
 */
template<>
struct std::hash<API_ElemType> {
//! @cond Doxygen_Suppress
	std::size_t operator() (const API_ElemType& elemType) const
	{
		return elemType.GenerateHashValue ();
	}
//! @endcond
};

//! \{

inline bool operator== (API_ElemTypeID typeID, const API_ElemType& elemType)
{
	return elemType == typeID;
}

inline bool operator != (API_ElemTypeID typeID, const API_ElemType& elemType)
{
	return elemType != typeID;
}

inline bool operator== (const API_Guid& classID, const API_ElemType& elemType)
{
	return elemType == classID;
}

inline bool operator != (const API_Guid& classID, const API_ElemType& elemType)
{
	return elemType != classID;
}

//! \}


/**
 * @brief General element header for element types.
 * @struct API_Elem_Head
 * @ingroup Element
 * @since Archicad 26
 * @remarks  From version 12 the element refers to the containing group by the Guid of the group element. The m_groupId field has been eliminated, the top level group can be obtained with the @ref ACAPI_Grouping_GetMainGroupGuid goody function.
 * 			 From version 18 the index -based identification is not available any more; please use GUIDs.
 * 			 From version 26 the typeID and variationID members were merged into an @ref API_ElemType structure.
 */
struct API_Elem_Head {

/**
 * @brief The type of the element.
 * @var type
 */
	API_ElemType					type;


/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	UInt32							filler_0;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief The globally unique identifier of the element. It is type-independent, and guaranteed to be globally unique in all projects. (The only possible guid clash is between projects which have evolved from the same base project.) Also, it doesn't change under any circumstances.
 * @var guid
 */
	API_Guid						guid;

/**
 * @brief The modification stamp of the element.
 * @var modiStamp
 */
	UInt64							modiStamp;


/**
 * @brief The identifier of the group the element belongs to. APINULLGuid means the element is not grouped. Doesn't apply to certain (non-groupable) element types.
 * @var groupGuid
 */
	API_Guid						groupGuid;

/**
 * @brief The identifier of the hotlink instance the element belongs to (see @ref API_HotlinkType). APINULLGuid means the element is not part of any hotlinks.
 * @var hotlinkGuid
 */
	API_Guid						hotlinkGuid;

/**
 * @brief The element belongs to this floor.
 * @var floorInd
 */
	short							floorInd;

/**
 * @brief The layer attribute index of the element.
 * @var layer
 */
	API_AttributeIndex				layer;


/**
 * @brief Tells whether an element has extended information (memo) attached.
 * @var hasMemo
 */
	bool							hasMemo;

/**
 * @brief The index of the element in drawing order. It is important for bring to front/send to back type operations. Elements with higher drwIndex are drawn last.
 * @var drwIndex
 */
	char							drwIndex;

/**
 * @brief The member ID of the owner in TeamWork mode.
 * @var userId
 */
	short							userId;

/**
 * @brief The member ID of the locker in TeamWork mode, bool in normal mode.
 * @var lockId
 */
	short							lockId;

/**
 * @brief Reference group layer (-1: special/locked group).
 * @var rgr_layer
 */
	API_AttributeIndex				rgr_layer;


/**
 * @brief Renovation status of the element.
 * @var renovationStatus
 */
	API_RenovationStatusType		renovationStatus;

/**
 * @brief Renovation filter GUID for the element. If set, the element's visibility is determined by the given renovation filter. No special filter set when its value APIUndefinedGuid ; APINULLGuid means that the renovation filter cannot be determined at the time of the query.
 * @var renovationFilterGuid
 */
	API_Guid						renovationFilterGuid;

};


#define APIFilt_None						0x00000000
#define APIFilt_IsEditable					0x00000001
#define APIFilt_OnVisLayer					0x00000002
#define APIFilt_OnActFloor					0x00000004
#define APIFilt_In3D						0x00000008
#define APIFilt_InMyWorkspace				0x00000010
#define APIFilt_IsIndependent				0x00000020
#define APIFilt_OnActLayout					0x00000040
#define APIFilt_InCroppedView				0x00000080
#define APIFilt_IsOfVariation				0x00000100
#define APIFilt_HasAccessRight				0x00000200
#define APIFilt_IsVisibleByRenovation		0x00000400
#define APIFilt_IsOverridden			 	0x00000800
#define APIFilt_IsInStructureDisplay	 	0x00001000
#define APIFilt_FromFloorplan				0x10000000

typedef GSFlags	API_ElemFilterFlags;

#define APISect_Normal				0x0000						// simple cross section element
#define	APISect_Poly				0x0001						// profiled cross section element
#define	APISect_Slanted				0x0003						// slanted cross section element
#define	APISect_Trapez				0x0005						// trapezoid cross section element

#define APIElemMask_FromFloorplan	0x10000000



/**
 * @brief Identify a part of an element. It's valid for PolyRoof and Morph only.
 * @struct API_ElemPartId
 * @ingroup Element
 */
class API_ElemPartId {
public:
/**
 * @brief VertexId of the pivot polygon (relevant only for PolyRoof).
 * @var main
 */
	UInt32							main;

/**
 * @brief Level of part (relevant only for PolyRoof).
 * @var sub
 */
	UInt32							sub;

/**
 * @brief Floor number (relevant only for Mesh).
 * @var floor
 */
	Int32							floor;

/**
 * @brief Constructor which resets the data members.
 */
	API_ElemPartId () : main (0), sub (0), floor (0) {}

/**
 * @brief Comparison operator.
 * @param right Other elempart to compare to.
 * @return True if it is equal to right.
 */
	bool	operator==	(const API_ElemPartId& right) const		{ return (main == right.main && sub == right.sub && floor == right.floor); }

/**
 * @brief Comparison operator.
 * @param right Other elempart to compare to.
 * @return True if it is not equal to right.
 */
	bool	operator!=	(const API_ElemPartId& right) const		{ return !operator== (right); }

/**
 * @brief Generates unique identifier
 * @return the unique value
 */
	ULong	GenerateHashValue () const							{ return (main ^ sub) + floor * 65599; }
};


// =============================================================================
// Common Structures and Definitions
//
// =============================================================================

typedef enum {
	API_HatchGlobal				= 0,
	API_HatchRotated			= 1,
	API_HatchDistorted			= 2,
	API_HatchCentered			= 3
} API_HatchOrientationTypeID;


#define	APIHatchOrinFlag_XAxisGlobal			0x0001					    // the fill origin's X coordinate is the global origin's X coordinate
#define	APIHatchOrinFlag_YAxisGlobal			0x0002					    // the fill origin's Y coordinate is the global origin's Y coordinate
#define	APIHatchOrinFlag_GlobalOrigo			0x0003
#define	APIHatchOrinFlag_UseInnerRadius			0x0004						// create circular distortion using the innerRadius parameter (API_HatchCentered)
#define	APIHatchOrinFlag_GlobalOrientation		0x0008					    // use local orientation, use the distortion matrix, when doesn't set it

#define	APIHatchOrinFlag_FitX					0x0010						// (effective for symbol fills only) reset the pattern's X size to the defined X vector's length
#define	APIHatchOrinFlag_FitY					0x0020						// (effective for symbol fills only) reset the pattern's Y size to the defined Y vector's length
#define	APIHatchOrinFlag_KeepProportion			0x0040						// (effective for symbol fills only) keep proportion of symbol fill pattern


/**
 * @brief Fill orientation and distortion parameters.
 * @struct API_HatchOrientation
 * @ingroup Element
 * @remarks This structure holds the orientation and distortion parameters of the cover fills of @ref API_ShellBaseType, @ref API_SlabType and @ref API_HatchType elements.
 */
struct API_HatchOrientation {

/**
 * @brief Type of the cover fill orientation
 * 		  |API_HatchOrientationTypeID|Meaning|
 * 		  |--- |--- |
 * 		  |API_HatchGlobal|The fill is linked to Project Origin, the orientation of the hatching is always orthogonal independently of transformations made on the filled element|
 * 		  |API_HatchRotated|The fill is linked to Fill Origin, a single handle shows the orientation of the fill, and the fill pattern starts at the origin of the filled element|
 * 		  |API_HatchDistorted|The pattern of the fill is distorted in x and/or y directions|
 * 		  |API_HatchCentered|The pattern is circular fill distorted.|
 * @var type
 */
	API_HatchOrientationTypeID		type;

/**
 * @brief Version of the HatchOrientation
 * @var version
 */
	unsigned short					version;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

	/**
	 * @brief Flags for HatchOrientation
	 * 		  |Flag|Meaning|
	 * 		  |--- |--- |
	 * 		  |APIHatchOrinFlag_XAxisGlobal|The fill origin's X coordinate is the global origin's X coordinate|
	 * 		  |APIHatchOrinFlag_YAxisGlobal|The fill origin's Y coordinate is the global origin's Y coordinate|
	 * 		  |APIHatchOrinFlag_UseInnerRadius|Radius for circular fill distortion; the origin of the base circle will be
	 * 		  placed on the Y fill axis in the (0, -innerRadius) position| |APIHatchOrinFlag_GlobalOrientation|Use local
	 * 		  orientation, or use the distortion matrix, when it is not set.| |APIHatchOrinFlag_FitX|Reset the pattern's
	 * 		  X size to the defined X vector's length (effective for symbol fills only)|
	 * 		  |APIHatchOrinFlag_FitY|Reset the pattern's Y size to the defined Y vector's length (effective for symbol fills only)|
	 * 		  |APIHatchOrinFlag_KeepProportion|Keep proportion of symbol fill pattern (effective for symbol fills only)|
	 * @var flags
	 */
	Int32							flags;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2;

/**
 * @brief The origo of the fill relative to the project origin
 * @var origo
 */
	API_Coord						origo;

/**
 * @brief The x component of the primary distortion (direction) vector (the cosine of the fill angle, if not distorted)
 * @var matrix00
 */
	double							matrix00;

/**
 * @brief The y component of the primary distortion (direction) vector (the sine of the fill angle, if not distorted)
 * @var matrix10
 */
	double							matrix10;

/**
 * @brief The x component of the secondary distortion vector (the cosine of the angle of the normal vector, if not distorted)
 * @var matrix01
 */
	double							matrix01;

/**
 * @brief The y component of the secondary distortion vector (the sine of the angle of the normal vector, if not distorted)
 * @var matrix11
 */
	double							matrix11;

/**
 * @brief Radius for circular fill distortion.
 * @var innerRadius
 */
	double							innerRadius;

};

/**
 * @brief Type of cover fill transformation.
 * @enum API_CoverFillTransformationTypeID
 * @ingroup Element
 * @remarks This structure holds the @ref API_CoverFillTransformation type of the cover fills of @ref API_BeamType and @ref API_ColumnType elements.
 */
typedef enum {
	API_CoverFillTransformationType_Global 		= 0,
	API_CoverFillTransformationType_Rotated 	= 1,
	API_CoverFillTransformationType_Distorted 	= 2

} API_CoverFillTransformationTypeID;

/**
 * @brief Fill orientation and distortion parameters.
 * @struct API_CoverFillTransformation
 * @ingroup Element
 * @remarks This structure holds the orientation and distortion parameters of the cover fills of @ref API_BeamType and @ref API_ColumnType elements.
 */
struct API_CoverFillTransformation {

/**
 * @brief The origo of the fill relative to the center of the element.
 * @var origo
 */
	API_Coord		origo;

/**
 * @brief Primary distortion (direction) vector.
 * @var xAxis
 */
	API_Vector		xAxis;

/**
 * @brief Secondary distortion (direction) vector.
 * @var yAxis
 */
	API_Vector		yAxis;

};

/**
 * @brief Symbol transformation parameters.
 * @ingroup Element
 * @struct API_SyTran
 * @remarks This data structure gives information on the transformation parameters of a plaved Library Part.
 * 			The transformation chain is: placement, rotation, scaling; respectively. Scaling is done in the rotated coordinate system. Refer to the @c ACAPI_LibraryPart_GetSyTran function for more details.
 */
struct API_SyTran {

/**
 * @brief The location of the referenced library part.
 * @var loc
 */
	API_Coord						loc;

/**
 * @brief The rotation angle.
 * @var angle
 */
	double							angle;

/**
 * @brief 'x' scaling.
 * @var xRatio
 */
	double							xRatio;

/**
 * @brief 'y' scaling.
 * @var yRatio
 */
	double							yRatio;

};

/**
 * @brief Determines the appearance of model elements on different stories.
 * @struct API_StoryVisibility
 * @ingroup Element
 * @remarks For @ref API_SlabType, @ref API_RoofType and @ref API_MeshType elements you can set
 * 			a desired number of stories above and below their own story on which to display their contour
 * 			line and cover fill. @ref API_BeamType and @ref API_ObjectType contain this structure but this new feature was not extended for these elements.
 */
struct API_StoryVisibility {

/**
 * @brief Show the element on its own story only.
 * @var showOnHome
 */
	bool							showOnHome;

/**
 * @brief Show the element on all stories above its own story.
 * @var showAllAbove
 */
	bool							showAllAbove;

/**
 * @brief Show the element on all stories below its own story.
 * @var showAllBelow
 */
	bool							showAllBelow;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1;

/**
 * @brief Show the element on showRelAbove stories above its own story.
 * @var showRelAbove
 */
	short							showRelAbove;

/**
 * @brief Show the element on showRelBelow stories below its own story.
 * @var showRelBelow
 */
	short							showRelBelow;

};

/**
 * @brief Option for linking model elements to their home stories.
 * @struct API_LinkToSettings
 * @ingroup Element
 * @remarks Automatic link type can set only for @ref API_BeamType, @ref API_ColumnType, @ref API_ShellBaseType, @ref API_MorphType and @ref API_WallType elements. @ref API_MeshType, @ref API_LampType, @ref API_ObjectType and @ref API_SlabType contain the same structure but this feature was not extended for these elements.
 */
struct API_LinkToSettings {

/**
 * @brief Difference of home story from current story.
 * @var homeStoryDifference
 */
	short							homeStoryDifference;

/**
 * @brief Use this structure during element creation. If it is true, then head.floorInd will not be taken into account, otherwise homeStoryDifference will be filled.
 * @var newCreationMode
 */
	bool							newCreationMode;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1;

};

/**
 * @brief Floor plan display options of construction elements.
 * @enum API_ElemDisplayOptionsID
 * @ingroup Element
 * @remarks Element display option defines how a construction element appears on the floor plan.
 */
typedef enum  {
	API_Standard					= 0,						// show element with cut and below part
	API_StandardWithAbstract		= 1,						// show element with cut, above and below part
	API_CutOnly						= 2,						// show cut part only
	API_OutLinesOnly				= 3,						// show view with below attributes
	API_AbstractAll					= 4,						// show view with above attributes
	API_CutAll						= 5							// always show walls and columns cut part

} API_ElemDisplayOptionsID;

/**
 * @brief Floor plan projection modes of construction elements.
 * @enum API_ElemProjectionModesID
 * @ingroup Element
 * @remarks Element projection mode defines how a construction element appears on the floor plan.
 */
typedef enum {
	API_Symbolic					= 0,						// symbolic
	API_Projected					= 1,						// projected
	API_Hybrid						= 2 						// hybrid

} API_ElemProjectionModesID;

/**
 * @brief Depth limitation for the appearance of complex elements on the floor plan.
 * @enum API_ElemViewDepthLimitationsID
 * @ingroup Element
 * @remarks For a display option, view depth limitation defines how much of an element appears on the floor plan.
 * 			You can retrieve the current floor plan cut plane settings using the @ref ACAPI_ProjectSetting_GetPreferences function with the @ref API_FloorPlanCutDefinition structure.
 */
typedef enum  {
	API_ToFloorPlanRange			= 0,						// show projection to floor plan range
	API_ToAbsoluteLimit				= 1,						// show projection to absolute limit
	API_EntireElement				= 2							// show entire element

} API_ElemViewDepthLimitationsID;

/**
 * @brief Determines the type of the roof or slab edge trim. In previous API versions this enum type used to
 * 		  be called `@ref API_RsideID`.
 * @enum API_EdgeTrimID
 * @ingroup Element
 * @image html vert_roofside.png "Vertical roof side" width=50%
 * @image html perp_roofside.png "Perpendicular roof side" width=50%
 * @image html cust_roofside.png "Custom roof side" width=50%
 */
typedef enum {
	APIEdgeTrim_Vertical,
	APIEdgeTrim_Perpendicular,
	APIEdgeTrim_Horizontal,
	APIEdgeTrim_CustomAngle,
	APIEdgeTrim_AlignWithCut

} API_EdgeTrimID;

/**
 * @brief Describes the parameters of a roof or slab edge. In previous API versions this structure used to be called @c API_RoofSide.
 * @struct API_EdgeTrim
 * @ingroup Element
 */
struct API_EdgeTrim {

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	Int32							filler_0;

/**
 * @brief The trim type of the edge (see @ref API_EdgeTrimID).
 * @var sideType
 */
	API_EdgeTrimID					sideType;

/**
 * @brief The angle of the edge trim in radians in case of custom trim types.
 * @var sideAngle
 */
	double							sideAngle;

};


// =============================================================================
// Arrow
//
// =============================================================================

/**
 * @brief Describes the different arrow types.
 * @enum API_ArrowID
 * @ingroup Element
 */
typedef enum {
	APIArr_EmptyCirc,											// Empty Circle
	APIArr_CrossCircIs,											// Crossline + EmptyCirc (inside circle)
	APIArr_FullCirc,											// Full Circle
	APIArr_SlashLine15,											// 15deg Slash Line					NOT USED
	APIArr_OpenArrow15,											// 15deg opened arrow
	APIArr_ClosArrow15,											// 15deg closed arrow (triangle)
	APIArr_FullArrow15,											// 15deg Full arrow
	APIArr_SlashLine30,											// 30deg Slash Line					NOT USED
	APIArr_OpenArrow30,											// 30deg opened arrow
	APIArr_ClosArrow30,											// 30deg closed arrow (triangle)
	APIArr_FullArrow30,											// 30deg Full arrow
	APIArr_SlashLine45,											// 45deg Slash Line
	APIArr_OpenArrow45,											// 45deg opened arrow
	APIArr_ClosArrow45,											// 45deg closed arrow (triangle)
	APIArr_FullArrow45,											// 45deg Full arrow
	APIArr_SlashLine60,											// 60deg Slash Line
	APIArr_OpenArrow60,											// 60deg opened arrow				NOT USED
	APIArr_ClosArrow60,											// 60deg closed arrow (triangle)	NOT USED
	APIArr_FullArrow60,											// 60deg Full arrow					NOT USED
	APIArr_SlashLine90,											// 90deg Slash Line
	APIArr_PepitaCirc,											// Pepita Circle
	APIArr_BandArrow,											// Lane arrow (double line)
	APIArr_HalfArrowCcw15,										// 15deg rightwards harpoon with barb upwards
	APIArr_HalfArrowCw15,										// 15deg rightwards harpoon with barb downwards
	APIArr_HalfArrowCcw30,										// 30deg rightwards harpoon with barb upwards
	APIArr_HalfArrowCw30,										// 30deg rightwards harpoon with barb downwards
	APIArr_HalfArrowCcw45,										// 45deg rightwards harpoon with barb upwards
	APIArr_HalfArrowCw45,										// 45deg rightwards harpoon with barb downwards
	APIArr_HalfArrowCcw60,										// 60deg rightwards harpoon with barb upwards		NOT USED
	APIArr_HalfArrowCw60,										// 60deg rightwards harpoon with barb downwards		NOT USED
	APIArr_SlashLine75											// 75deg Slash Line

} API_ArrowID;

/**
 * @brief Describes the arrows at line ends.
 * @struct API_ArrowData
 * @ingroup Element
 */
struct API_ArrowData {

/**
 * @brief Type of the arrow.
 * @var arrowType
 */
	API_ArrowID						arrowType;

/**
 * @brief Put arrow to the beginning?
 * @var begArrow
 */
	bool							begArrow;

/**
 * @brief Put arrow to the end?
 * @var endArrow
 */
	bool							endArrow;

/**
 * @brief Pen attribute index for the arrows.
 * @var arrowPen
 */
	short							arrowPen;

/**
 * @brief Arrow size in mm.
 * @var arrowSize
 */
	double							arrowSize;

};


// =============================================================================
// Note
//
// =============================================================================


/**
 * @brief Identifies the autotexts of the note.
 * @enum API_NoteAutotextID
 * @ingroup AutoText
 * @since Archicad 26
 * @remarks API_NoteAutotextID helps to identify the note autotexts. The evaluable autotexts depends on the note owner's type.
 */
enum class API_NoteAutotextID {
	MeasuredValue,
	MeasuredValueToPZ,
	MeasuredValueToFirstRL,
	MeasuredValueToSecondRL,
	MeasuredValueToAltitude,
	MeasuredValueToSO,
	StoredOriginToPZ,
	TopElevToPZ,
	TopElevToFirstRL,
	TopElevToSecondRL,
	TopElevToAltitude,
	CoreTopElevToPZ,
	CoreTopElevToFirstRL,
	CoreTopElevToSecondRL,
	CoreTopElevToAltitude,
	CoreBottomElevToPZ,
	CoreBottomElevToFirstRL,
	CoreBottomElevToSecondRL,
	CoreBottomElevToAltitude,
	BottomElevToPZ,
	BottomElevToFirstRL,
	BottomElevToSecondRL,
	BottomElevToAltitude,
	ProjectZeroName,
	FirstReferenceLevelName,
	SecondReferenceLevelName,
	AltitudeName,
	StoredOriginName

};

/**
 * @brief Describes the type of the content.
 * @enum API_NoteContentType
 * @ingroup Element
 * @remarks API_NoteContent_Auto has been removed in API 14.
 */
typedef enum {
	API_NoteContent_Measured,
	API_NoteContent_Custom

} API_NoteContentType;

/**
 * @brief Describes how the pointer line is connected to the Label text (in case of Text Labels).
 * @enum API_LblAnchorID
 * @ingroup Element
 */
typedef enum {
	APILbl_MiddleAnchor				= 0,
	APILbl_TopAnchor				= 1,
	APILbl_BottomAnchor				= 2,
	APILbl_Underlined				= 3

} API_LblAnchorID;

/**
 * @brief Describes the shape of the pointer line of Note text or Label.
 * @enum API_LeaderLineShapeID
 * @ingroup Element
 * @remarks API_SquareRoot type applies to Labels only.
 */
typedef enum {
	API_Segmented					= 0,
	API_Splinear					= 1,
	API_SquareRoot					= 2							// used only for labels

} API_LeaderLineShapeID;

/**
 * @brief Describes the various justification options.
 * @enum API_JustID
 * @ingroup Element
 */
typedef enum {
	APIJust_Left					= 0,
	APIJust_Center,
	APIJust_Right,
	APIJust_Full

} API_JustID;

/**
 * @brief Describes a general note, used in dimensioning and hatch text.
 * @struct API_NoteType
 * @ingroup Element
 * @remarks This type is used in many as text blocks of any kind of dimensions.
 * 			You can only create notes with leader line on angle dimensions, floor plan dimensions and hatches. If you want to create a note with leaderline you will have to set fixpos to true, but you do not have to calculate pos and noteAngle because leaderline will determine these automatically.
 * 			subContent is removed in API 14.
 */
struct API_NoteType {

/**
 * @brief Pen attribute index.
 * @var notePen
 */
	short							notePen;

/**
 * @brief Font attribute index.
 * @var noteFont
 */
	short							noteFont;

/**
 * @brief Layer attribute index.
 * @var noteLayer
 */
	API_AttributeIndex				noteLayer;

/**
 * @brief The character height in mm.
 * @var noteSize
 */
	double							noteSize;

/**
 * @brief Rotation angle in radian.
 * @var noteAngle
 */
	double							noteAngle;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[8];

/**
 * @brief Coordinates of left bottom.
 * @var pos
 */
	API_Coord						pos;

/**
 * @brief The text or the autotext of the note.
 * @var content
 */
	char							content[64];

/**
 * @brief Optional parameter for accessing the text or the autotext of the note in UniString format.
 * @var contentUStr
 */
	GS::UniString*					contentUStr;

/**
 * @brief 0: measured value 1: custom text
 * @var contentType
 */
	API_NoteContentType				contentType;

/**
 * @brief Is the position of the note manually fixed?
 * @var fixPos
 */
	bool							fixPos;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	bool							filler_3;

/**
 * @brief The style of the note:
 * 		  |Bit|Style|
 * 		  |--- |--- |
 * 		  |APIFace_Plain|Plain text|
 * 		  |APIFace_Bold|Bold|
 * 		  |APIFace_Italic|Italic|
 * 		  |APIFace_Underline|Underline|
 *
 * @var faceBits
 */
	unsigned short					faceBits;

/**
 * @brief The note has background.
 * @var opaque
 */
	bool							opaque;

/**
 * @brief The note has frame.
 * @var frame
 */
	bool							frame;

/**
 * @brief The background color index if opaque.
 * @var backgroundPen
 */
	short							backgroundPen;

/**
 * @brief Frame color index if framed.
 * @var framePen
 */
	short							framePen;

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	short							filler_4;

/**
 * @brief Reserved for later use.
 * @var filler_5
 */
	Int32							filler_5[4];

/**
 * @brief Whether the note has leader line.
 * @var useLeaderLine
 */
	bool							useLeaderLine;

/**
 * @brief Whether the leader line attached to the end of the note text.
 * @var anchorAtTextEnd
 */
	bool							anchorAtTextEnd;

/**
 * @brief Reserved for later use.
 * @var filler_6
 */
	short							filler_6[3];

/**
 * @brief Beginning coordinate of the leader line.
 * @var begC
 */
	API_Coord						begC;

/**
 * @brief Middle coordinate of the leader line.
 * @var midC
 */
	API_Coord						midC;

/**
 * @brief End coordinate of the leader line.
 * @var endC
 */
	API_Coord						endC;

/**
 * @brief Reserved for later use.
 * @var filler_7
 */
	Int32							filler_7;

/**
 * @brief Reserved for later use.
 * @var filler_8
 */
	short							filler_8;

/**
 * @brief Leader line pen attribute index.
 * @var leaderPen
 */
	short							leaderPen;

/**
 * @brief Line type attribute index of the leader line.
 * @var leaderLineType
 */
	API_AttributeIndex				leaderLineType;

/**
 * @brief Shape of the leader line.
 * @var leaderShape
 */
	API_LeaderLineShapeID			leaderShape;

/**
 * @brief The arrow type. See @ref API_ArrowData
 * @var arrowData
 */
	API_ArrowData					arrowData;

/**
 * @brief Anchor point the pointer line is connected to. See @ref API_LblAnchorID.
 * @var anchorPoint
 */
	API_LblAnchorID					anchorPoint;

/**
 * @brief Multiline Text alignment (Left, Center, Right).
 * @var just
 */
	API_JustID						just;

/**
 * @brief Width scale of the note's text.
 * @var widthFactor
 */
	double							widthFactor;

/**
 * @brief Spacing scale of the note's text.
 * @var spacingFactor
 */
	double							spacingFactor;

/**
 * @brief Text anchor row (First = 0, or Last Row = 1).
 * @var rowAnchor
 */
	short							rowAnchor;

/**
 * @brief Special text effects:
 * 		  |Effect|Style|
 * 		  |--- |--- |
 * 		  |APIEffect_StrikeOut|Strikethrough text|
 * 		  |APIEffect_SuperScript|Superscript|
 * 		  |APIEffect_SubScript|Subscript|
 * 		  |APIEffect_Protected|Protected text (autotext reference)|
 *
 * @var effectBits
 */
	unsigned short					effectBits;

};


// =============================================================================
// ModelElemStructure
//
// =============================================================================

/**
 * @brief Determines the structure type of the element.
 * @enum API_ModelElemStructureType
 * @ingroup Element
 * @remarks Valid structure types of an element type are shown in the table below:
 * 			|Element Type|Basic Structure|Composite Structure|Profile Structure|
 * 			|--- |--- |--- |--- |
 * 			|API_WallID|x|x|x|
 * 			|API_ColumnID, API_BeamID|x||x|
 * 			|API_SlabID, API_RoofID, API_ShellID|x|x||
 *
 * @ref API_MeshType, @ref API_MorphType and @ref API_CurtainWallType always contain Building Materials, so
 * 		they don't have this structure.
 */
typedef enum {
	API_BasicStructure,
	API_CompositeStructure,
	API_ProfileStructure

} API_ModelElemStructureType;


using API_PenIndex = short;
constexpr API_PenIndex APIInvalidPenIndex = 0;
using API_OverriddenPen = APIOptional<API_PenIndex>;
using API_OverriddenPenOrRGB = APIOptional<APIVariant<API_PenIndex, API_RGBColor>>;
using API_OverriddenAttribute = APIOptional<API_AttributeIndex>;
using API_OverriddenAttributeOrRGB = APIOptional<APIVariant<API_AttributeIndex, API_RGBColor>>;


// =============================================================================
// Wall
//
// =============================================================================

/**
 * @brief Distinguishes among the different wall reference line locations.
 * @enum API_WallReferenceLineLocationID
 * @ingroup Element
 * @remarks These constants determine the location of the reference line in the wall.
 * 			This - along with the new flipped member in @ref API_WallType - replace the old `API_WallDirID`,
 * 			and allow you to exactly position the reference line, instead of coding both this position
 * 			and the 'flippedness' of the wall into one member.
 * 			Imagine a horizontal unflipped composite wall drawn from left to right (as shown in the Composite Settings
 * 			dialog): outside is the top, inside is the bottom.
 * @image html WallReferenceLineLocationID.png "Wall reference line location" width=50%
 * 		  Only composite walls may have a core-related reference line
 * 		  location; polygonal and complex walls always use `@ref APIWallRefLine_Outside`. Profiled walls don't use this
 * 		  member; their reference line always goes through their origin. When its value is `APIWallRefLine_Center` or
 * 		  `@ref APIWallRefLine_CoreCenter`, you cannot specify an offset in the @ref API_WallType structure. The new
 * 		  `offsetFromOutside` output only member in @ref API_WallType tells you the distance between the 'top' of the
 * 		  wall (as shown in the Composite Settings dialog) and the reference line's position.
 */
typedef enum {
	APIWallRefLine_Outside = 0,
	APIWallRefLine_Center,
	APIWallRefLine_Inside,
	APIWallRefLine_CoreOutside,
	APIWallRefLine_CoreCenter,
	APIWallRefLine_CoreInside

} API_WallReferenceLineLocationID;

/**
 * @brief Represents the different wall types.
 * @enum API_WallTypeID
 * @ingroup Element
 */
typedef enum {
	APIWtyp_Normal,												// normal parallel wall
	APIWtyp_Trapez,												// normal trapezoid wall (vertical)
	APIWtyp_Poly												// general polygon

} API_WallTypeID;

#define	APICutElem_Beam				1							// gable is coming from a beam
#define	APICutElem_Ceil				2							// gable is coming from a ceil
#define	APICutElem_Roof				3							// gable is coming from a roof
#define	APICutElem_Shell			4							// gable is coming from a shell

/**
 * @brief Defines a cutting plane applied to spatial elements.
 * @struct API_Gable
 * @ingroup Element
 * @remarks The **a**, **b**, **c**, **d** plane coefficients are the parameters of the plane equation:
 * 			*a** x + **b** y + **c** z = **d**
 * 			Where `x`, `y` and `z` are points in 3D space, `a`, `b` and `c` are the `x`, `y` and `z` components of the surface normal,
 * 			and `d` is the distance value. A point whose components are put into `x`, `y` and `z` is on the plane if the above equality is satisfied.
 * 			All gable data is defined in the local coordinate system of the element.
 * 			The picture below shows how gable parameters should be interpreted for curved walls:
 * @image html WallGable.png "Wall gable" width=50%
 * 		  Note that the coordinates of the limit polygon are transformed (shifted and rotated) into
 * 		  a position relative to the first edge of the zone polygon. To get the real gable polygon
 * 		  coordinates you should transform them back.
 * 		  Check the Dump Zone function in the Element_Manager example project.
 */
struct API_Gable {

/**
 * @brief Plane coefficients relative to the parent element.
 * @var a
 */
	double							a;

/**
 * @brief Plane coefficients relative to the parent element.
 * @var b
 */
	double							b;

/**
 * @brief Plane coefficients relative to the parent element.
 * @var c
 */
	double							c;

/**
 * @brief Plane coefficients relative to the parent element.
 * @var d
 */
	double							d;

/**
 * @brief Beginning distance of vertical cut planes from local origin.
 * @var xb
 */
	double							xb;

/**
 * @brief End distance of vertical cut planes from local origin.
 * @var xe
 */
	double							xe;

/**
 * @brief X component of the normal vector of vertical cut planes (nz always 0.0).
 * @var nx
 */
	double							nx;

/**
 * @brief Y component of the normal vector of vertical cut planes (nz always 0.0).
 * @var ny
 */
	double							ny;

/**
 * @brief Element the gable is generated from (output only).
 * @var cutElem
 */
	short							cutElem;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief Material for the cut surface (output only).
 * @var material
 */
	API_AttributeIndex				material;

/**
 * @brief Coordinate array, only if cut is limited to a polygon.
 * @var coords
 */
	API_Coord						**coords;

/**
 * @brief Polygon endpoints; see @ref API_Polygon for more information.
 * @var pends
 */
	Int32							**pends;

/**
 * @brief Polygon arcs; see @ref API_PolyArc and @ref API_Polygon for more information.
 * @var parcs
 */
	API_PolyArc						**parcs;

};

#define	APIWBeam_RefMater			1							// apply Reference side material on horizontal edges
#define	APIWBeam_OppMater			2							// apply Opposite side material on horizontal edges
#define	APIWBeam_HalfLog			4							// start with half log
#define	APIWBeam_QuadricLog			8							// start with quadric log
#define	APIWBeam_Stretched			64							// ???
#define	APIWBeam_RightLog			128							// logs on the right side of the wall
#define	APIWBeam_LeftLog			256							// logs on the left side of the wall

/**
 * @brief Describes the relation of an element to a zone.
 * @enum API_ZoneRelID
 * @ingroup Element
 */
typedef enum {
	APIZRel_Boundary,
	APIZRel_ReduceArea,
	APIZRel_None,
	APIZRel_SubtractFromZone
} API_ZoneRelID;

/**
 * @brief Represents a wall element.
 * @struct API_WallType
 * @ingroup Element
 * @remarks  The type of the elements' structure is defined with the new modelElemStructureType member. The related attribute indices are separated into buildingMaterial, composite and profileAttr. The composite index is a non-negative index.
 * 			 The elements' cut fill foreground and background pens inherit from the element structure, and can be overridden on the element level.
 * 			 The elements' surface materials inherit from the element structure, and can be overridden on the element level.
 * 			 For wall related memo data see the @ref ACAPI_Element_GetMemo function.
 */
struct API_WallType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;


/**
 * @brief Pen attribute index of wall's contour.
 * @var contPen
 */
	short							contPen;

/**
 * @brief The pen index of wall's contour in 3D.
 * @var contPen3D
 */
	short							contPen3D;

/**
 * @brief The linetype index of wall's contour.
 * @var contLtype
 */
	API_AttributeIndex				contLtype;

/**
 * @brief Line type used when "OutLines Only" is selected from the "Floor Plan Display" popup. Corresponds to the "Uncut Lines" value in the Wall Settings dialog.
 * @var belowViewLineType
 */
	API_AttributeIndex				belowViewLineType;

/**
 * @brief The structure type of the wall.
 * @var modelElemStructureType
 */
	API_ModelElemStructureType		modelElemStructureType;

/**
 * @brief Building Material index of wall's hatch. Used only, if structure type is @c API_BasicStrucure.
 * @var buildingMaterial
 */
	API_AttributeIndex				buildingMaterial;

/**
 * @brief Composite index of wall. Used only, if structure type is @c API_CompositeStructure.
 * @var composite
 */
	API_AttributeIndex				composite;

/**
 * @brief Sequence is required when two walls meet with the same priority or when 3 or more walls meet in a junction. It's actual values can be between 0 and 999.
 * @var sequence
 */
	Int32							sequence;
/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	Int32							filler_0;

/**
 * @brief Cut fill pens set in the used structure (building material, composite, complex profile) can be overridden on the element level.
 * @var cutFillPen
 */
	API_OverriddenPen				cutFillPen;

/**
 * @brief Cut fill pens set in the used structure (building material, composite, complex profile) can be overridden on the element level.
 * @var cutFillBackgroundPen
 */
	API_OverriddenPen				cutFillBackgroundPen;

/**
 * @brief Material override structure of the surface on the reference line side.
 * @var refMat
 */
	API_OverriddenAttribute			refMat;

/**
 * @brief Material override structure of the opposite surface.
 * @var oppMat
 */
	API_OverriddenAttribute			oppMat;

/**
 * @brief Material override structure of the side surfaces.
 * @var sidMat
 */
	API_OverriddenAttribute			sidMat;

/**
 * @brief Attribute index of the extruded profile (APIInvalidAttributeIndex if not profiled). See @ref API_ProfileAttrType.
 * @var profileAttr
 */
	API_AttributeIndex				profileAttr;

/**
 * @brief The type of the cross section of the wall:
 * 		  |Profile type|Meaning|
 * 		  |--- |--- |
 * 		  |APISect_Normal|Simple cross section element|
 * 		  |APISect_Poly|Profiled cross section element|
 * 		  |APISect_Slanted|Slanted cross section element|
 * 		  |APISect_Trapez|Trapezoid cross section element|
 *
 * @var profileType
 */
	short							profileType;

/**
 * @brief The polygon wall's corners can be changed in case of L and T connections.
 * @var polyCanChange
 */
	bool							polyCanChange;

/**
 * @brief Are surface materials chained?
 * @var materialsChained
 */
	bool							materialsChained;

/**
 * @brief If true then the wall is mirrored to the reference line. (true == @c APIWdir_Left or @c APIWdir_LCenter ; false == @c APIWdir_Right or @c APIWdir_Center in the old @c API_WallDirID enum).
 * @var flipped
 */
	bool							flipped;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[7];

/**
 * @brief The type of the geometry of the wall (see @ref API_WallTypeID).
 * @var type
 */
	API_WallTypeID					type;

/**
 * @brief The location of the reference line (see @ref API_WallReferenceLineLocationID).
 * @var referenceLineLocation
 */
	API_WallReferenceLineLocationID	referenceLineLocation;

/**
 * @brief The height of the wall relative to its bottom.
 * @var height
 */
	double							height;

/**
 * @brief Base height of the wall relative to the floor level.
 * @var bottomOffset
 */
	double							bottomOffset;

/**
 * @brief The offset from top floor if wall is top linked.
 * @var topOffset
 */
	double							topOffset;

/**
 * @brief The thickness of the wall at the beginning point.
 * @var thickness
 */
	double							thickness;

/**
 * @brief The thickness of the wall at the end point.
 * @var thickness1
 */
	double							thickness1;

/**
 * @brief The offset of the wall's base line from reference line at the beginning point (invalid for center wall directions).
 * @var offset
 */
	double							offset;

/**
 * @brief Distance between reference line and outside face of the wall (output only).
 * @var offsetFromOutside
 */
	double							offsetFromOutside;

/**
 * @brief The height of the log for log walls (0 means normal wall).
 * @var logHeight
 */
	double							logHeight;

/**
 * @brief Log wall relation flags.
 * 		  |Flag|Meaning|
 * 		  |--- |--- |
 * 		  |APIWBeam_RefMater|Apply Reference side material on horizontal edges.|
 * 		  |APIWBeam_OppMater|Apply Opposite side material on horizontal edges.|
 * 		  |APIWBeam_HalfLog|Start with half log.|
 * 		  |APIWBeam_QuadricLog|Use square (quadric) logs.|
 * 		  |APIWBeam_Stretched|The log radius is measured from the opposite side.|
 * 		  |APIWBeam_RightLog|The logs are curved on the right side of the wall.|
 * 		  |APIWBeam_LeftLog|The logs are curved on the left side of the wall.|
 *
 * @var beamFlags
 */
	Int32							beamFlags;

/**
 * @brief Defines the wall's relation to zones (see @ref API_ZoneRelID).
 * @var zoneRel
 */
	API_ZoneRelID					zoneRel;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	char							filler_2[16];

/**
 * @brief Recalculate the story visibility automatically according to the actual vertical extent of the wall.
 * @var isAutoOnStoryVisibility
 */
	bool							isAutoOnStoryVisibility;

/**
 * @brief The end surface of the wall is inherited from the adjoining wall.
 * @var inheritEndSurface
 */
	bool							inheritEndSurface;

/**
 * @brief Align texture mapping to wall edges.
 * @var alignTexture
 */
	bool							alignTexture;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	bool							filler_3;

/**
 * @brief The option to define which stories display the wall.
 * @var visibility
 */
	API_StoryVisibility				visibility;

/**
 * @brief Mode of linking to home story.
 * @var linkToSettings
 */
	API_LinkToSettings				linkToSettings;

/**
 * @brief The top linked story (relative to home story). Negative values are invalid. 0 = not top linked.
 * @var relativeTopStory
 */
	short							relativeTopStory;

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	short							filler_4[3];


/**
 * @brief The start (beginning) coordinate of the wall.
 * @var begC
 */
	API_Coord						begC;

/**
 * @brief The end coordinate of the wall.
 * @var endC
 */
	API_Coord						endC;

/**
 * @brief The original outline of the wall.
 * @var poly
 */
	API_Polygon						poly;

/**
 * @brief The index of the reference line beginning edge (starting from 1). Note that the direction can be reversed if the polygonal wall is mirrored.
 * @var rLinInd
 */
	Int32							rLinInd;

/**
 * @brief The index of the reference line end edge.
 * @var rLinEndInd
 */
	Int32							rLinEndInd;

/**
 * @brief The index of the reference material start edge index.
 * @var refInd
 */
	Int32							refInd;

/**
 * @brief The index of the reference material end edge index.
 * @var refEndInd
 */
	Int32							refEndInd;

/**
 * @brief The index of the opposite side material edge start.
 * @var oppInd
 */
	Int32							oppInd;

/**
 * @brief The index of the opposite side material end edge index.
 * @var oppEndInd
 */
	Int32							oppEndInd;


/**
 * @brief The rotation angle of the wall in radians.
 * @var angle
 */
	double							angle;

/**
 * @brief Output only: true, if the Wall has at least one Window.
 * @var hasWindow
 */
	bool							hasWindow;

/**
 * @brief Output only: true, if the Wall has at least one Door.
 * @var hasDoor
 */
	bool							hasDoor;

/**
 * @brief Reserved for later use.
 * @var filler_5
 */
	bool							filler_5[2];


/**
 * @brief Set the priority of the wall in the junction with other elements.
 * @var wallConnPriority
 */
	Int32							wallConnPriority;

/**
 * @brief Set the priority of the composits in the junction with other elements.
 * @var useCompositePriority
 */
	bool							useCompositePriority;

/**
 * @brief Reserved for later use.
 * @var filler_6
 */
	bool							filler_6;

/**
 * @brief Pen used when "Overhead All" is selected from the "Floor Plan Display" popup. Corresponds to the "Overhead Line Pens" value in the Wall Settings dialog.
 * @var aboveViewLinePen
 */
	short							aboveViewLinePen;

/**
 * @brief Line type used when "Overhead All" is selected from the "Floor Plan Display" popup. Corresponds to the "Overhead Lines" value in the Wall Settings dialog.
 * @var aboveViewLineType
 */
	API_AttributeIndex				aboveViewLineType;


/**
 * @brief Determines how the wall appears on the floor plan.
 * @var displayOption
 */
	API_ElemDisplayOptionsID		displayOption;

/**
 * @brief Determines which part of the wall is visible for multi-story walls.
 * @var viewDepthLimitation
 */
	API_ElemViewDepthLimitationsID	viewDepthLimitation;


/**
 * @brief Defines the angle for slanted and double slanted walls.
 * @var slantAlpha
 */
	double							slantAlpha;

/**
 * @brief Defines the angle for double slanted walls.
 * @var slantBeta
 */
	double							slantBeta;


/**
 * @brief Reserved for later use.
 * @var filler_8
 */
	Int32							filler_8[4];

};


// =============================================================================
// Curtain Wall
//
// =============================================================================

// Curtain Wall Segment

/**
 * @brief Represents a curtain wall contour type element.
 * @struct API_CWContourData
 * @ingroup CurtainWall
 * @remarks .
 */
struct API_CWContourData {

/**
 * @brief The curtain wall contour polygon.
 * @var polygon
 */
	API_Polygon						polygon;

/**
 * @brief The coordinates of the curtain wall contour polygon.
 * @var coords
 */
	API_Coord						**coords;

/**
 * @brief Polygon end vertex indices.
 * @var pends
 */
	Int32							**pends;

/**
 * @brief Arc indices in the polygon.
 * @var parcs
 */
	API_PolyArc						**parcs;

/**
 * @brief Vertex indices.
 * @var vertexIDs
 */
	UInt32							**vertexIDs;

};

/**
 * @brief Curtain wall segment type.
 * @enum API_CWSegmentTypeID
 * @ingroup Element
 * @remarks The @ref API_CWSegmentTypeID type is used in the @ref API_CWSegmentType structure.
 */
typedef enum {
	APICWSeT_Invalid = 0,
	APICWSeT_Line,
	APICWSeT_Arc

} API_CWSegmentTypeID;

typedef enum {
	APICWCFT_NoCrossingFrame,
	APICWCFT_FromBottomLeftToTopRight,
	APICWCFT_FromTopLeftToBottomRight
} API_CWCellCrossingFrameTypeID;

/**
 * @brief Curtain wall segment type.
 * @enum API_CWSegmentCategoryID
 * @ingroup Element
 * @remarks The @ref API_CWSegmentCategoryID type is used in the @ref API_CWSegmentType structure.
 */
typedef enum {
	APICWSeC_System = 0,
	APICWSeC_Custom

} API_CWSegmentCategoryID;

/**
 * @brief Curtain wall segment grid origin pos type.
 * @enum API_CWSegmentGridOrigPosTypeID
 * @ingroup Element
 * @remarks The @ref API_CWSegmentGridOrigPosTypeID type is used in the @ref API_CWSegmentPatternData structure.
 */
typedef enum {
	APICWSeGridOrigin_StartWithPattern,
	APICWSeGridOrigin_StartFromCenter,
	APICWSeGridOrigin_AlignToCenter,
	APICWSeGridOrigin_EndWithPattern

} API_CWSegmentGridOrigPosTypeID;

typedef enum {
	APICWSePL_FixedSizes,
	APICWSePL_BestDivision,
	APICWSePL_NumberOfDivisions
} API_CWSegmentPatternLogicID;

#define APICWFrameClass_Merged					0
#define APICWFrameClass_Division				1
#define APICWFrameClass_Corner					2
#define APICWFrameClass_Boundary				3
#define APICWFrameClass_FirstCustomClass		4
#define APICWFrameClass_Customized				MaxUIndex

#define APICWPanelClass_Deleted					0
#define APICWPanelClass_FirstCustomClass		1
#define APICWPanelClass_Customized				MaxUIndex

/**
 * @brief Represents a curtain wall segment cell.
 * @struct API_CWSegmentPatternCellData
 * @ingroup Element
 */
struct API_CWSegmentPatternCellData {

/**
 * @brief Describes the type of the crossing frame in the cell.
 * 		  |Type|Meaning|
 * 		  |--- |--- |
 * 		  |APICWCFT_NoCrossingFrame|The cell does not have a crossing frame.|
 * 		  |APICWCFT_FromBottomLeftToTopRight|The cell has a crossing frame from its bottom left to its top right.|
 * 		  |APICWCFT_FromTopLeftToBottomRight|The cell has a crossing frame from its top left to its bottom right.|
 * @var crossingFrameType
 */
	API_CWCellCrossingFrameTypeID	crossingFrameType;

/**
 * @brief Class index of the panel left of the cell.
 * @var leftPanelID
 */
	UInt32 							leftPanelID;

/**
 * @brief Class index of the panel right of the cell.
 * @var rightPanelID
 */
	UInt32 							rightPanelID;

/**
 * @brief Class index of the frame left of the cell.
 * @var leftFrameID
 */
	UInt32 							leftFrameID;

/**
 * @brief Class index of the frame under the cell.
 * @var bottomFrameID
 */
	UInt32 							bottomFrameID;

/**
 * @brief Class index of the frame crossing the cell.
 * @var crossingFrameID
 */
	UInt32 							crossingFrameID;

};

/**
 * @brief Represents the horizontal (primary) or vertical (secondary) pattern of a Curtain Wall segment.
 * @struct API_CWSegmentPatternData
 * @ingroup Element
 */
struct API_CWSegmentPatternData {
	/**
	 * @brief Describes how the pattern is stretched in segments.
	 * 		  |Type|Meaning|
	 * 		  |--- |--- |
	 * 		  |APICWSePL_FixedSizes|The length of the pattern is given explicitly. This may result in incomplete patterns.|
	 * 		  |APICWSePL_BestDivision|The length of the pattern is stretched, so that the least amount of stretching is done.|
	 * 		  |APICWSePL_NumberOfDivisions|The length of the pattern is stretched, so that exactly nDivisions amount of patterns are placed.|
	 * @var logic
	 */
	API_CWSegmentPatternLogicID		logic;

/**
 * @brief Describes how the pattern is aligned in segments. See available value in the documentation of @ref API_CWSegmentGridOrigPosTypeID enum.
 * @var gridOriginType
 */
	API_CWSegmentGridOrigPosTypeID	gridOriginType;

/**
 * @brief Amount of columns/rows in the pattern.
 * @var nPattern
 */
	UInt32 							nPattern;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	UInt32							filler_1;

/**
 * @brief The distances of each columns/rows.
 * @var pattern
 */
	double 							*pattern;

/**
 * @brief The indices of columns/rows that can be stretched. Only used in case of @c APICWSePL_BestDivision or @c APICWSePL_NumberOfDivisions logic.
 * @var flexibleIDs
 */
	UInt32 							*flexibleIDs;

/**
 * @brief Amount of stretchable columns/rows. Only used in case of @c APICWSePL_BestDivision or @c APICWSePL_NumberOfDivisions logic.
 * @var nFlexibleIDs
 */
	UInt32							nFlexibleIDs;

/**
 * @brief Amount of divisions. Only used in case of @c APICWSePL_NumberOfDivisions logic.
 * @var nDivisions
 */
	UInt32 							nDivisions;

/**
 * @brief Class index of the panel, that fills the end of an incomplete pattern. Use APICWInfillWithPartial to fill with partial pattern. Only used in case of @c APICWSePL_FixedSizes logic.
 * @var infillPanelID
 */
	UInt32 							infillPanelID;

/**
 * @brief The index of the ending panel.
 * @var endWithID
 */
	UInt32 							endWithID;

};

/**
 * @brief Represents a curtain wall segment element.
 * @struct API_CWSegmentType
 * @ingroup Element
 */
struct API_CWSegmentType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;

/**
 * @brief The pen index.
 * @var pen
 */
	short							pen;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief See @ref API_CWSegmentCategoryID.
 * @var category
 */
	API_CWSegmentCategoryID			category;

/**
 * @brief The angle of rows in relation to columns.
 * @var gridAngle
 */
	double							gridAngle;

/**
 * @brief The begining coordinate of the segment.
 * @var begC
 */
	API_Coord3D						begC;

/**
 * @brief The end coordinate of the segment.
 * @var endC
 */
	API_Coord3D						endC;

/**
 * @brief The origin coordinate of the grid.
 * @var gridOrigin
 */
	API_Coord3D						gridOrigin;

/**
 * @brief The origin coordinate of the arc.
 * @var arcOrigin
 */
	API_Coord3D						arcOrigin;

/**
 * @brief The arc of the segment is a negative (clockwise) arc.
 * @var negArc
 */
	bool							negArc;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool							filler_2[3];

/**
 * @brief See @ref API_CWSegmentTypeID.
 * @var segmentType
 */
	API_CWSegmentTypeID				segmentType;

/**
 * @brief Owner Curtain Wall.
 * @var owner
 */
	API_Guid						owner;

/**
 * @brief The extrusion of the segment.
 * @var extrusion
 */
	API_Vector3D					extrusion;

/**
 * @brief The size of the segment contour.
 * @var contourNum
 */
	UInt32							contourNum;

/**
 * @brief The amount of cells in the Segment pattern.
 * @var patternCellNum
 */
	UInt32							patternCellNum;

};

/**
 * @brief Curtain wall frame object type.
 * @enum API_CWFrameObjectTypeID
 * @ingroup Element
 * @remarks The @ref API_CWFrameObjectTypeID type is used in the @ref API_CWFrameType structure.
 * 			The @c APICWFrObjectType_Generic and @c APICWFrObjectType_ButtGlazed types have been removed in Archicad 22.
 */
typedef enum {
	APICWFrObjectType_Invisible = 0,
	APICWFrObjectType_GDL,
	APICWFrObjectType_InvisibleConnectedTurning,
	APICWFrObjectType_InvisibleConnectedStill
} API_CWFrameObjectTypeID;

/**
 * @brief Represents a Curtain Wall Frame element.
 * @struct API_CWFrameType
 * @ingroup Element
 * @remarks The Curtain Wall is a hierarchical (system) element consisting of Frame, Panel, Accessory and
 * 			Junction components: these are the Members of the Curtain Wall, arranged on a Base Surface according to a
 * 			pre-defined scheme.
 */
struct API_CWFrameType {
	/**
	 * @brief General element header.
	 * @var head
	 */
	API_Elem_Head					head;

	/**
	 * @brief For internal use.
	 * @var pen
	 */
	short							pen;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	short							filler_0;

	/**
	 * @brief Material index of the frame's surface.
	 * @var material
	 */
	API_AttributeIndex				material;

	/**
	 * @brief  The frame uses its own materials or materials defined in the library part (in case of GDL based frame).
	 * @var useOwnMaterial
	 */
	bool							useOwnMaterial;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[3];

	/**
	 * @brief Building Material of the frame.
	 * @var buildingMaterial
	 */
	API_AttributeIndex				buildingMaterial;

	/**
	 * @brief Line index of the cut part of the frame on the floorplan.
	 * @var cutLineType
	 */
	API_AttributeIndex				cutLineType;

	/**
	 * @brief Pen index of the cut part of the frame on the floorplan.
	 * @var cutLinePen
	 */
	short							cutLinePen;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	short							filler_2;

	/**
	 * @brief Panel connection hole depth.
	 * @var d
	 */
	double							d;

	/**
	 * @brief Panel connection hole width.
	 * @var w
	 */
	double							w;

	/**
	 * @brief Frame contour width inside. @c a1 and @c a2 are always equal and `a1 + a2 = a` on the Frame Type and
	 * 		  %Geometry tabpage of the Frame Settings Dialog.
	 * @var a1
	 */
	double							a1;

	/**
	 * @brief Frame contour width outside. @c a1 and @c a2 are always equal and `a1 + a2 = a` on the
	 * 		  Frame Type and %Geometry tabpage of the Frame Settings Dialog.
	 * @var a2
	 */
	double							a2;

	/**
	 * @brief Frame contour length inside. `b1 = b - h` on the Frame Type and %Geometry tabpage of the Frame Settings
	 * 		  Dialog.
	 * @var b1
	 */
	double							b1;

	/**
	 * @brief Frame contour length outside. `b2 = h` on the Frame Type and %Geometry tabpage of the Frame
	 * 		  Settings Dialog.
	 * @var b2
	 */
	double							b2;

	/**
	 * @brief Angle of the frame.
	 * @var angle
	 */
	double							angle;

	/**
	 * @brief Type of the frame.
	 * @var objectType
	 */
	API_CWFrameObjectTypeID			objectType;

	/**
	 * @brief The priority of the frame in 3D intersections on a 1 to 19 scale.
	 * @var connPriority
	 */
	unsigned short					connPriority;

	/**
	 * @brief The class identifier of the frame (previously known as category).
	 * @var classID
	 */
	UInt32 							classID;

	/**
	 * @brief The owner curtain wall.
	 * @var owner
	 */
	API_Guid						owner;

	/**
	 * @brief The related library part's object identifier.
	 * @var symbolID
	 */
	API_Guid						symbolID;

	/**
	 * @brief True if the panel is a GDL object.
	 * @var hasSymbol
	 */
	bool							hasSymbol;

	/**
	 * @brief Flags a panel class for deletion. In this case, the panel's className should be the name of the
	 * 		  class to substitute it with.
	 * @var deleteFlag
	 */
	bool							deleteFlag;

	/**
	 * @brief Tells if this is the default panel for the curtain wall.
	 * @var defaultSubElem
	 */
	bool							defaultSubElem;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	bool							filler_3;

	/**
	 * @brief Identifier of containing segment.
	 * @var segmentID
	 */
	UInt32							segmentID;

	/**
	 * @brief The identifier of containing cell.
	 * @var cellID
	 */
	API_GridElemID 					cellID;

	/**
	 * @brief Relative first point in cell.
	 * @var begRel
	 */
	API_Coord 						begRel;

	/**
	 * @brief Relative second point in cell.
	 * @var endRel
	 */
	API_Coord 						endRel;

	/**
	 * @brief First point of the frame's reference line.
	 * @var begC
	 */
	API_Coord3D						begC;

	/**
	 * @brief Second point of the frame's reference line.
	 * @var endC
	 */
	API_Coord3D						endC;

	/**
	 * @brief Orientation of the frame. This vector is always perpendicular to the vector defined by @c begC and @c endC coordinates.
	 * @var orientation
	 */
	API_Coord3D						orientation;

	/**
	 * @brief Number of frames joined at @c begC.
	 * @var joinedCWFramesBegCNum
	 */
	UInt32							joinedCWFramesBegCNum;

	/**
	 * @brief Number of frames joined at @c endC.
	 * @var joinedCWFramesEndCNum
	 */
	UInt32							joinedCWFramesEndCNum;

	/**
	 * @brief Number of associated panels - one frame border two panels.
	 * @var assocCWPanelsNum
	 */
	UInt32							assocCWPanelsNum;

	/**
	 * @brief Object Library Part index if the frame is GDL based.
	 * @var libInd
	 */
	Int32							libInd;

	/**
	 * @brief Number of additional panel clamping vectors.
	 * @var auxPanelDirsNum
	 */
	UInt32							auxPanelDirsNum;

	/**
	 * @brief Contour ID for contour frames; other has invalid value.
	 * @var contourID
	 */
	Int32							contourID;

	/**
	 * @brief Name of the frame's class.
	 * @var className
	 */
	GS::uchar_t 					className[256];
};

/**
 * @brief Curtain wall panel object type.
 * @enum API_CWPanelObjectTypeID
 * @ingroup Element
 * @remarks The @ref API_CWPanelObjectTypeID type is used in the @ref API_CWPanelType structure.
 */
typedef enum {
	APICWPaObjectType_Generic = 0,
	APICWPaObjectType_GDL
} API_CWPanelObjectTypeID;

/**
 * @brief Represents a Curtain Wall Panel element.
 * @struct API_CWPanelType
 * @ingroup Element
 * @remarks The Curtain Wall is a hierarchical (system) element consisting of Frame, Panel, Accessory and
 * 			Junction components: these are the Members of the Curtain Wall, arranged on a Base Surface according to a
 * 			pre-defined scheme.
 */
struct API_CWPanelType {
	/**
	 * @brief General element header.
	 * @var head
	 */
	API_Elem_Head head;

	/**
	 * @brief For internal use only.
	 * @var pen
	 */
	short							pen;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1[3];

	/**
	 * @brief Material override structure of the exterior surface of the panel.
	 * @var outerSurfaceMaterial
	 */
	API_OverriddenAttribute			outerSurfaceMaterial;

	/**
	 * @brief Material override structure of the interior surface of the panel.
	 * @var innerSurfaceMaterial
	 */
	API_OverriddenAttribute			innerSurfaceMaterial;

	/**
	 * @brief Material override structure of the edge surface of the panel.
	 * @var cutSurfaceMaterial
	 */
	API_OverriddenAttribute			cutSurfaceMaterial;

	/**
	 * @brief Building Material of the panel.
	 * @var buildingMaterial
	 */
	API_AttributeIndex				buildingMaterial;

	/**
	 * @brief Line index of the cut part of the panel on the floorplan.
	 * @var cutLineType
	 */
	API_AttributeIndex				cutLineType;

	/**
	 * @brief Pen index of the cut part of the panel on the floorplan.
	 * @var cutLinePen
	 */
	short							cutLinePen;

	/**
	 * @brief Flags a panel class for deletion. In this case, the panel's className should be the name of the
	 * 		  class to substitute it with.
	 * @var deleteFlag
	 */
	bool							deleteFlag;

	/**
	 * @brief Tells if this is the default panel for the curtain wall.
	 * @var defaultSubElem
	 */
	bool							defaultSubElem;

	/**
	 * @brief Identifier of containing segment.
	 * @var segmentID
	 */
	UInt32							segmentID;

	/**
	 * @brief Type of the panel.
	 * @var objectType
	 */
	API_CWPanelObjectTypeID			objectType;

	/**
	 * @brief Thickness of the panel.
	 * @var thickness
	 */
	double							thickness;

	/**
	 * @brief The owner curtain wall of this panel.
	 * @var owner
	 */
	API_Guid						owner;

	/**
	 * @brief The related library part's object identifier.
	 * @var symbolID
	 */
	API_Guid						symbolID;

	/**
	 * @brief True if the panel is a GDL object.
	 * @var hasSymbol
	 */
	bool							hasSymbol;

	/**
	 * @brief Deleted panels remain in the database.
	 * @var hidden
	 */
	bool							hidden;

	/**
	 * @brief Library object index if the panel is a GDL object.
	 * @var libInd
	 */
	Int32							libInd;

	/**
	 * @brief Panel class identifier (previously known as category).
	 * @var classID
	 */
	UInt32							classID;

	/**
	 * @brief The number of neighbour frames.
	 * @var edgesNum
	 */
	UInt32							edgesNum;

	/**
	 * @brief Reserved for internal use.
	 * @var gridPolyIDsNum
	 */
	UInt32							gridPolyIDsNum;

	/**
	 * @brief The 3D coordinates of the panel's centroid.
	 * @var centroid
	 */
	API_Coord3D						centroid;

	/**
	 * @brief Name of the panel's class.
	 * @var className
	 */
	GS::uchar_t						className[256];
};

/**
 * @brief This table contains the grid mesh identifiers for each Curtain Wall panel instance (these grid
 * 		  mesh cells are partly or fully covered by the panel).
 * @typedef API_CWPanelGridIDTable
 * @ingroup Element
 */
typedef GS::HashTable<API_Guid, GS::Array<API_GridElemID>> API_CWPanelGridIDTable;

// Curtain Wall Junction

/**
 * @brief Curtain wall junction clamp frame orientation type.
 * @enum API_CWJunctionClampFrameOrientationID
 * @remarks The @ref API_CWJunctionClampFrameOrientationID type is used in the @ref API_CWJunctionType structure.
 */
typedef enum {
	APICWJunClampFrameOrient_NoClamp = 0,
	APICWJunClampFrameOrient_ClampAtBeg,
	APICWJunClampFrameOrient_ClampAtEnd,
	APICWJunClampFrameOrient_ClampAtBothEnds

} API_CWJunctionClampFrameOrientationID;

/**
 * @brief Curtain wall junction category type.
 * @enum API_CWJunctionCategoryID
 * @ingroup Element
 * @remarks The @ref API_CWJunctionCategoryID type is used in the @ref API_CWJunctionType structure.
 */
typedef enum {
	APICWJunC_System = 0,
	APICWJunC_Custom

} API_CWJunctionCategoryID;

/**
 * @brief Represents a curtain wall junction element.
 * @struct API_CWJunctionType
 * @ingroup Element
 * @remarks The Curtain Wall is a hierarchical (system) element consisting of Frame, Panel, Accessory and Junction components: these are the Members of the Curtain Wall, arranged on a Base Surface according to a pre-defined scheme.
 * @c API_GridElemID is a typedef for UInt64.
 */
struct API_CWJunctionType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;

/**
 * @brief For internal use.
 * @var pen
 */
	short							pen;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief Category of the junction. See @ref API_CWJunctionCategoryID.
 * @var category
 */
	API_CWJunctionCategoryID		category;

/**
 * @brief Owner Curtain Wall.
 * @var owner
 */
	API_Guid						owner;

/**
 * @brief Object identifier. (junctions are always GDL based)
 * @var symbolID
 */
	API_Guid						symbolID;

/**
 * @brief In normal case it is always true.
 * @var hasSymbol
 */
	bool							hasSymbol;

/**
 * @brief True, if the frame is flipped.
 * @var flipped
 */
	bool							flipped;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool							filler_2[6];

/**
 * @brief Number of clamping frames.
 * @var clampFramesNum
 */
	UInt32							clampFramesNum;

/**
 * @brief In normal case it is equal to clampFramesNum
 * @var clampFrameOrientsNum
 */
	UInt32							clampFrameOrientsNum;

/**
 * @brief Number of clamping panels.
 * @var clampPanelsNum
 */
	UInt32							clampPanelsNum;

/**
 * @brief Library Part index if the junction is GDL-based.
 * @var libInd
 */
	Int32							libInd;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	UInt32 							filler_3;

};

// Curtain Wall Accessory

/**
 * @brief Curtain wall accessory category type.
 * @enum API_CWAccessoryCategoryID
 * @ingroup Element
 * @remarks The @ref API_CWAccessoryCategoryID type is used in the @ref API_CWAccessoryType structure.
 */
typedef enum {
	APICWAccC_System = 0,
	APICWAccC_Custom
} API_CWAccessoryCategoryID;

/**
 * @brief Represents a curtain wall accessory element.
 * @struct API_CWAccessoryType
 * @ingroup Element
 * @remarks The Curtain Wall is a hierarchical (system) element consisting of Frame, Panel, Accessory
 * 			and Junction components: these are the Members of the Curtain Wall, arranged on a Base Surface
 * 			according to a pre-defined scheme.
 */
struct API_CWAccessoryType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;

/**
 * @brief For internal use.
 * @var pen
 */
	short							pen;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief Category of the accessory. See @ref API_CWAccessoryCategoryID.
 * @var category
 */
	API_CWAccessoryCategoryID		category;

/**
 * @brief Owner Curtain Wall.
 * @var owner
 */
	API_Guid						owner;

/**
 * @brief Object identifier.
 * @var symbolID
 */
	API_Guid						symbolID;

/**
 * @brief In normal case it is always true.
 * @var hasSymbol
 */
	bool							hasSymbol;

/**
 * @brief Curtain Wall Accessory is flipped?
 * @var flipped
 */
	bool							flipped;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool							filler_2[2];

/**
 * @brief Library Part index.
 * @var libInd
 */
	Int32 							libInd;

/**
 * @brief Accessory is always joins to a frame. This is the reference frame.
 * @var refFrame
 */
	API_Guid						refFrame;

};

// Curtain Wall (Main Element)

/**
 * @brief Define curtain wall boundary frame position.
 * @enum API_CWBoundaryFramePosID
 * @ingroup Element
 * @remarks The @ref API_CWBoundaryFramePosID type is used in the @ref API_CWSegmentType structure.
 */
typedef enum {
	APICW_Boundary_Unknown = 0,
	APICW_Boundary_OutSide,
	APICW_Boundary_Center,
	APICW_Boundary_Inside

} API_CWBoundaryFramePosID;

/**
 * @brief Curtain wall junction placement type.
 * @enum API_CWPlacementID
 * @ingroup Element
 * @remarks The @ref API_CWPlacementID type is used in the @ref API_CWSegmentType structure.
 */
typedef enum {
	APICW_Placement_AllGridPoints = 0,
	APICW_Placement_Manual

} API_CWPlacementID;

/**
 * @brief Represents a Curtain Wall element.
 * @struct API_CurtainWallType
 * @ingroup Element
 * @remarks The Curtain Wall is a hierarchical (system) element consisting of Frame, Panel, Accessory and Junction components: these are the Members of the Curtain Wall, arranged on a Base Surface according to a pre-defined scheme. By default all CW component is generic and has built from the owner elem.
 * 			The elements' cut fill foreground and background pens inherit from the building material, and can be overridden on the element level.
 * 			In Archicad 22, the Frames and Panels of a Curtain Wall element are no longer forced into primary/secondary or glass/glazed categories, with the exception of Boundary Frames, which are still a separate category. As so, the other default Frame and Panel elements are found in the corresponding @ref API_ElementMemo structure. Also, Curtain Wall subelements now contain their own library part identifiers instead of the Curtain Wall structure itself.
 */
struct API_CurtainWallType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;

/**
 * @brief Relation to zones. See @ref API_ZoneRelID.
 * @var zoneRel
 */
	API_ZoneRelID					zoneRel;

/**
 * @brief The pen index.
 * @var pen
 */
	short							pen;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief Nominal width of the Curtain Wall.
 * @var nominalWidth
 */
	double							nominalWidth;

/**
 * @brief The curtain wall is flipped.
 * @var flipped
 */
	bool							flipped;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool							filler_2[7];

/**
 * @brief Panel offset to the reference plane.
 * @var offset
 */
	double							offset;

/**
 * @brief Theoretical border of the curtain wall.
 * @var distanceInside
 */
	double							distanceInside;

/**
 * @brief Theoretical border of the curtain wall.
 * @var distanceOutside
 */
	double							distanceOutside;

/**
 * @brief Boundary Frame position.
 * @var boundaryFramePosition
 */
	API_CWBoundaryFramePosID		boundaryFramePosition;

/**
 * @brief Link to story settings. See @ref API_LinkToSettings.
 * @var linkToSettings
 */
	API_LinkToSettings				linkToSettings;

/**
 * @brief Story visibility. See @ref API_StoryVisibility.
 * @var visibility
 */
	API_StoryVisibility				visibility;

/**
 * @brief Story visibility will be automatically recalculated when needed.
 * @var isAutoOnStoryVisibility
 */
	bool							isAutoOnStoryVisibility;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	bool							filler_3[3];

/**
 * @brief Base level (relative to home story).
 * @var storyRelLevel
 */
	double							storyRelLevel;

/**
 * @brief Floor plan display option. See @ref API_ElemDisplayOptionsID.
 * @var displayOption
 */
	API_ElemDisplayOptionsID		displayOption;

/**
 * @brief Cut projection mode. See @ref API_ElemProjectionModesID.
 * @var cutProjectionMode
 */
	API_ElemProjectionModesID		cutProjectionMode;

/**
 * @brief Uncut projection mode. See @ref API_ElemProjectionModesID.
 * @var uncutProjectionMode
 */
	API_ElemProjectionModesID		uncutProjectionMode;

/**
 * @brief Overhead projection mode. See @ref API_ElemProjectionModesID.
 * @var overheadProjectionMode
 */
	API_ElemProjectionModesID		overheadProjectionMode;

/**
 * @brief Floor plan view depth limitation. See @ref API_ElemViewDepthLimitationsID.
 * @var viewDepthLimitation
 */
	API_ElemViewDepthLimitationsID	viewDepthLimitation;

/**
 * @brief Linetype of view above cutplane on the floorplan.
 * @var overheadLineType
 */
	API_AttributeIndex				overheadLineType;

/**
 * @brief Pen index of view above cutplane on the floorplan.
 * @var overheadLinePen
 */
	short							overheadLinePen;

/**
 * @brief Pen index of view below cutplane on the floorplan.
 * @var uncutLinePen
 */
	short							uncutLinePen;

/**
 * @brief Linetype of view below cutplane on the floorplan.
 * @var uncutLineType
 */
	API_AttributeIndex				uncutLineType;

/**
 * @brief Line index of the cut part of frames on the floorplan.
 * @var frameCutLineType
 */
	API_AttributeIndex				frameCutLineType;

/**
 * @brief Pen index of the cut part of frames on the floorplan.
 * @var frameCutLinePen
 */
	short							frameCutLinePen;

/**
 * @brief Pen index of the cut part of panels on the floorplan.
 * @var panelCutLinePen
 */
	short							panelCutLinePen;

/**
 * @brief Line index of the cut part of panels on the floorplan.
 * @var panelCutLineType
 */
	API_AttributeIndex				panelCutLineType;

/**
 * @brief Use Frame type's attributes.
 * @var useFrameTypesAttributes
 */
	bool							useFrameTypesAttributes;

/**
 * @brief Use Panel type's attributes.
 * @var usePanelTypesAttributes
 */
	bool							usePanelTypesAttributes;
	bool							filler_4[2];

/**
 * @brief Cut fill pens set in the building material can be overridden on the element level.
 * @var cutFillPen
 */
	API_OverriddenPen				cutFillPen;

/**
 * @brief Cut fill pens set in the building material can be overridden on the element level.
 * @var cutFillBackgroundPen
 */
	API_OverriddenPen				cutFillBackgroundPen;

/**
 * @brief Placement method.
 * @var placementMethod
 */
	API_CWPlacementID				placementMethod;

/**
 * @brief Reserved for later use.
 * @var filler_5
 */
	Int32							filler_5;

/**
 * @brief Curtain Wall Segment related data.
 * @var segmentData
 */
	API_CWSegmentType				segmentData;

/**
 * @brief Parameters of corner frames.
 * @var cornerFrameData
 */
	API_CWFrameType					cornerFrameData;

/**
 * @brief Parameters of boundary frames.
 * @var boundaryFrameData
 */
	API_CWFrameType					boundaryFrameData;

/**
 * @brief Parameters of junctions.
 * @var junctionData
 */
	API_CWJunctionType				junctionData;

/**
 * @brief Parameters of glass accessories.
 * @var accessoryData
 */
	API_CWAccessoryType				accessoryData;

/**
 * @brief Angle of the curtain wall (input only).
 * @var angle
 */
	double							angle;

/**
 * @brief Height of the curtain wall (input only).
 * @var height
 */
	double							height;

/**
 * @brief Base polygon of the curtain wall.
 * @var polygon
 */
	API_Polygon						polygon;

/**
 * @brief Plane matrix of the curtain wall.
 * @var planeMatrix
 */
	API_Tranmat						planeMatrix;

/**
 * @brief Plane offset of the curtain wall.
 * @var planeOffset
 */
	double							planeOffset;

/**
 * @brief Number of segments.
 * @var nSegments
 */
	UInt32							nSegments;

/**
 * @brief Number of frames.
 * @var nFrames
 */
	UInt32							nFrames;

/**
 * @brief Number of custom frame classes (Corner Frame and Boundary Frame Classes are not included).
 * @var nFrameDefaults
 */
	UInt32 							nFrameDefaults;

/**
 * @brief Number of panels.
 * @var nPanels
 */
	UInt32							nPanels;

/**
 * @brief Number of panel classes.
 * @var nPanelDefaults
 */
	UInt32							nPanelDefaults;

/**
 * @brief Number of junctions.
 * @var nJunctions
 */
	UInt32							nJunctions;

/**
 * @brief Number of accessories.
 * @var nAccessories
 */
	UInt32							nAccessories;

/**
 * @brief Reserved for later use.
 * @var filler_6
 */
	UInt32							filler_6;

};

// =============================================================================
// AssemblySegment
//
// =============================================================================
/**
 * @brief The type of segment length.
 * @enum API_AssemblySegmentLengthTypeID
 * @ingroup Element
 */
typedef enum {
	APIAssemblySegment_Fixed		= 0,
	APIAssemblySegment_Proportional	= 1,

} API_AssemblySegmentLengthTypeID;

/**
 * @brief Represents an general segment.
 * @struct API_AssemblySegmentData
 * @ingroup Element
 */
struct API_AssemblySegmentData {

/**
 * @brief The structure type of the column's segment.
 * @var modelElemStructureType
 */
	API_ModelElemStructureType		modelElemStructureType;

/**
 * @brief Building Material index of column's hatch. Used only, if structure type is @c API_BasicStrucure.
 * @var buildingMaterial
 */
	API_AttributeIndex				buildingMaterial;

/**
 * @brief Defines whether the column is circular (true) or rectangular/profiled (false).
 * @var circleBased
 */
	bool							circleBased;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	char							filler_0[3];

/**
 * @brief Attribute index of the extruded profile.
 * @var profileAttr
 */
	API_AttributeIndex				profileAttr;

/**
 * @brief The type of the profile:
 * @var profileType
 */
	short							profileType;

/**
 * @brief Whether it is homogeneous which means the size of the segment's profiles are the same at the beginning and end of it.
 * @var isHomogeneous
 */
	bool							isHomogeneous;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	char							filler_1[5];

/**
 * @brief Nominal width of segment.
 * @var nominalWidth
 */
	double							nominalWidth;

/**
 * @brief Nominal height of segment.
 * @var nominalHeight
 */
	double							nominalHeight;

/**
 * @brief State of linking between width and height.
 * @var isWidthAndHeightLinked
 */
	bool							isWidthAndHeightLinked;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	char							filler_2[7];

/**
 * @brief Width of end in case of not homogeneous uniformity.
 * @var endWidth
 */
	double							endWidth;

/**
 * @brief Height of end in case of not homogeneous uniformity.
 * @var endHeight
 */
	double							endHeight;

/**
 * @brief State of linking between end width and end height in case of not homogeneous uniformity.
 * @var isEndWidthAndHeightLinked
 */
	bool							isEndWidthAndHeightLinked;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	char							filler_3[7];

/**
 * @brief Relative Home Story Level of the segment, should not be interpreted on default, only on instance. Output only parameter.
 * @var relativeHomeStoryLevel
 */
	double							relativeHomeStoryLevel;

};

/**
 * @brief Represents a segment scheme.
 * @struct API_AssemblySegmentSchemeData
 * @ingroup Element
 */
struct API_AssemblySegmentSchemeData {

/**
 * @brief Segment length type.
 * @var lengthType
 */
	API_AssemblySegmentLengthTypeID	lengthType;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	char							filler_0[4];

/**
 * @brief Use this if lengthType is @c APIAssemblySegment_Fixed.
 * @var fixedLength
 */
	double							fixedLength;

/**
 * @brief Use this if lengthType is @c APIAssemblySegment_Proportional.
 * @var lengthProportion
 */
	double							lengthProportion;

};

/**
 * @brief Represents an segment of the beam element.
 * @struct API_AssemblySegmentProfileData
 * @ingroup Element
 */
struct API_AssemblySegmentProfileData {

/**
 * @brief Index of the segment.
 * @var segmentIndex
 */
	UInt32							segmentIndex;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	char							filler_0[4];

/**
 * @brief Original custom profile.
 * @var customOrigProfile
 */
	ProfileVectorImage				*customOrigProfile;

/**
 * @brief Stretched profile.
 * @var stretchedProfile
 */
	ProfileVectorImage				*stretchedProfile;

};

/**
 * @brief The type of cut.
 * @enum API_AssemblySegmentCutTypeID
 * @ingroup Element
 */
typedef enum {
	APIAssemblySegmentCut_Horizontal	= 0,
	APIAssemblySegmentCut_Vertical		= 1,
	APIAssemblySegmentCut_Custom		= 2
} API_AssemblySegmentCutTypeID;

/**
 * @brief Represents a cut on segment.
 * @struct API_AssemblySegmentCutData
 * @ingroup Element
 */
struct API_AssemblySegmentCutData {

/**
 * @brief Type of cut. See @ref API_AssemblySegmentCutTypeID.
 * @var cutType
 */
	API_AssemblySegmentCutTypeID	cutType;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	char							filler_0[4];

/**
 * @brief The angle of cut if cutType is @c APIAssemblySegmentCut_Custom.
 * @var customAngle
 */
	double							customAngle;

};

// =============================================================================
// Column
//
// =============================================================================

#define APICSect_Normal				0x0000						// normal upright column
#define	APICSect_Poly				0x0001						// extruded column from polygon

/**
 * @brief Describes the veneer type of a column.
 * @enum API_VeneerTypeID
 * @ingroup Element
 */
typedef enum {
	APIVeneer_Core		= 0,
	APIVeneer_Finish	= 1,
	APIVeneer_Other		= 2

} API_VeneerTypeID;

/**
 * @brief Represents an segment of the column element.
 * @struct API_ColumnSegmentType
 * @ingroup Element
 */
struct API_ColumnSegmentType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head						head;

/**
 * @brief Guid of the owner column.
 * @var owner
 */
	API_Guid							owner;

/**
 * @brief General informations about segment.
 * @var assemblySegmentData
 */
	API_AssemblySegmentData				assemblySegmentData;

/**
 * @brief The column's segment material override structure.
 * @var extrusionSurfaceMaterial
 */
	API_OverriddenAttribute				extrusionSurfaceMaterial;

/**
 * @brief The material override structure of the beginning and end side of the column's segment.
 * @var endsMaterial
 */
	API_OverriddenAttribute				endsMaterial;

/**
 * @brief Are surface materials chained?
 * @var materialsChained
 */
	bool								materialsChained;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	char								filler_0[3];

/**
 * @brief Building Material index of column's segment veneer's hatch. Used only, if structure type is @c API_BasicStrucure.
 * @var venBuildingMaterial
 */
	API_AttributeIndex					venBuildingMaterial;

/**
 * @brief The type of the column's segment veneer.
 * @var venType
 */
	API_VeneerTypeID					venType;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	char								filler_1[4];

/**
 * @brief The thickness of the column's segment veneer.
 * @var venThick
 */
	double								venThick;

};

/**
 * @brief Represents a column element.
 * @struct API_ColumnType
 * @ingroup Element
 * @remarks In Archicad 17, the elements' structure type is defined with the new `modelElemStructureType`
 * 			member. The related attribute indices are separated into `buildingMaterial` and `profileAttr`.
 * 			In Archicad 17, the elements' cut fill foreground and background pens inherit from the element structure
 * 			and can be overridden onthe element level.
 * 			In Archicad 17, the elements' surface materials inherit from the element structure and can
 * 			be overridden on the element level. For column-related memo data, see the @ref ACAPI_Element_GetMemo function.
 */
struct API_ColumnType {
	/**
	 * @brief General element header
	 * @var head
	 */
	API_Elem_Head						head;

	/**
	 * @brief The pen color index of the core
	 * @var corePen
	 */
	short								corePen;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	char								filler_0[6];

	/**
	 * @brief Cut fill pens set in the used structure (building material, complex profile) can be overridden on the element level.
	 * @var cutFillPen
	 */
	API_OverriddenPen					cutFillPen;

	/**
	 * @brief Cut fill pens set in the used structure (building material, complex profile) can be overridden on the element level.
	 * @var cutFillBackgroundPen
	 */
	API_OverriddenPen					cutFillBackgroundPen;

	/**
	 * @brief Pen index of the uncut lines.
	 * @var belowViewLinePen
	 */
	short								belowViewLinePen;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	char								filler_1[2];

	/**
	 * @brief The line type of the uncut lines.
	 * @var belowViewLineType
	 */
	API_AttributeIndex					belowViewLineType;

	/**
	 * @brief The line type of the core.
	 * @var contLtype
	 */
	API_AttributeIndex					contLtype;

	/**
	 * @brief Defines the wall wrapping. If `true`, the wall wraps around the column.
	 * @var wrapping
	 */
	bool								wrapping;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	char								filler_2[3];

	/**
	 * @brief Defines the column's relation to zones (see @ref API_ZoneRelID).
	 * @var zoneRel
	 */
	API_ZoneRelID						zoneRel;

	/**
	 * @brief Determines the display of the column on the floor plan:
	 * 		  |Value|Meaning|
	 * 		  |--- |--- |
	 * 		  |1|Plain|
	 * 		  |2|Slash|
	 * 		  |3|X|
	 * 		  |4|CrossHair|
	 * @var coreSymbolType
	 */
	short								coreSymbolType;

	/**
	 * @brief Anchor point of the core.
	 * 		  |0|1|2|
	 * 		  |3|4|5|
	 * 		  |6|7|8|
	 * @var coreAnchor
	 */
	short								coreAnchor;

	/**
	 * @brief The height of the column
	 * @var height
	 */
	double								height;

	/**
	 * @brief The column base level relative to the floor level
	 * @var bottomOffset
	 */
	double								bottomOffset;

	/**
	 * @brief The offset from top floor if column is top linked
	 * @var topOffset
	 */
	double								topOffset;

	/**
	 * @brief The line type index of veneer line
	 * @var venLineType
	 */
	API_AttributeIndex					venLineType;

    /**
     * @brief The color index of veneer line
     * @var venLinePen
     */
	short								venLinePen;

    /**
     * @brief The color index of column cross line
     * @var coreSymbolPen
     */
	short								coreSymbolPen;

    /**
     * @brief The length of the crosshair outside the column's contour line
     * @var coreSymbolPar1
     */
	double								coreSymbolPar1;

    /**
     * @brief The distance of the crosshair from the column's center
     * @var coreSymbolPar2
     */
	double								coreSymbolPar2;

    /**
     * @brief Defines on which floor the given element is visible (see @ref API_StoryVisibility)
     * @var visibility
     */
	API_StoryVisibility					visibility;

    /**
     * @brief Mode of linking to home story.
     * @var linkToSettings
     */
	API_LinkToSettings					linkToSettings;

	/**
	 * @brief The top linked story (relative to home story). Negative values are invalid. 0 = not top linked.
	 * @var relativeTopStory
	 */
	short relativeTopStory;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	char								filler_3[2];

    /**
     * @brief Hidden line type.
     * @var hiddenLineType
     */
	API_AttributeIndex					hiddenLineType;

    /**
     * @brief Hidden line pen.
     * @var hiddenLinePen
     */
	short								hiddenLinePen;

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	char								filler_4[2];

    /**
     * @brief The position of the column
     * @var origoPos
     */
	API_Coord							origoPos;

    /**
     * @brief The angle of rotation around the axis of the column (in radian)
     * @var axisRotationAngle
     */
	double								axisRotationAngle;

    /**
     * @brief Linetype of the overhead lines
     * @var aboveViewLineType
     */
	API_AttributeIndex					aboveViewLineType;

    /**
     * @brief Pen index of the overhead lines
     * @var aboveViewLinePen
     */
	short								aboveViewLinePen;


    /**
     * @brief If set to `true`, the application will automatically provide the story dependent visibility
     * 		  of the element (if the element is physically on a story, it will be shown on that story)
     * @var isAutoOnStoryVisibility
     */
	bool								isAutoOnStoryVisibility;


	/**
	 * @brief Defines whether the column is slanted or vertical
	 * @var isSlanted
	 */
	bool								isSlanted;

    /**
     * @brief Flipped column.
     * @var isFlipped
     */
	bool								isFlipped;

/**
 * @brief Reserved for later use.
 * @var filler_5
 */
	char								filler_5[7];

    /**
     * @brief Slant angle (in radian)
     * @var slantAngle
     */
	double								slantAngle;

    /**
     * @brief The rotation angle of the slanted column on the horizontal plane (in radians)
     * @var slantDirectionAngle
     */
	double								slantDirectionAngle;


    /**
     * @brief Display options of the element on the floor plan.
     * @var displayOption
     */
	API_ElemDisplayOptionsID			displayOption;

    /**
     * @brief Defines the range within the element is shown on the floor plan .
     * @var viewDepthLimitation
     */
	API_ElemViewDepthLimitationsID		viewDepthLimitation;

    /**
     * @brief Number of cuts.
     * @var nCuts
     */
	UInt32								nCuts;

	/**
	 * @brief Number of segments.
	 * @var nSegments
	 */
	UInt32								nSegments;

	/**
	 * @brief Number of schemes.
	 * @var nSchemes
	 */
	UInt32								nSchemes;

    /**
     * @brief Number of profiles.
     * @var nProfiles
     */
	UInt32								nProfiles;


	/**
	 * @brief Use Floor plan fill.
	 * @var useCoverFill
	 */
	bool								useCoverFill;

	/**
	 * @brief Use the fill attribute assigned to the surface material of the element.
	 * @var useCoverFillFromSurface
	 */
	bool								useCoverFillFromSurface;

	/**
	 * @brief Use cover fill orientation from 3D element view.
	 * @var coverFillOrientationComesFrom3D
	 */
	bool								coverFillOrientationComesFrom3D;

/**
 * @brief Reserved for later use.
 * @var filler_6
 */
	char								filler_6;

	/**
	 * @brief Fill type of the cover fill.
	 * @var coverFillType
	 */
	API_AttributeIndex					coverFillType;

    /**
     * @brief Foreground pen of the cover fill.
     * @var coverFillForegroundPen
     */
	short 								coverFillForegroundPen;

    /**
     * @brief Background pen of the cover fill.
     * @var coverFillBackgroundPen
     */
	short 								coverFillBackgroundPen;

/**
 * @brief Reserved for later use.
 * @var filler_7
 */
	char								filler_7[4];

    /**
     * @brief TransformationType of the fill
     * @var coverFillTransformationType
     */
	API_CoverFillTransformationTypeID 	coverFillTransformationType;

/**
 * @brief Reserved for later use.
 * @var filler_8
 */
	char								filler_8[4];

    /**
     * @brief Orientation and distortion parameters of the cover fill.
     * @var coverFillTransformation
     */	API_CoverFillTransformation 		coverFillTransformation;
};


// =============================================================================
// Beam
//
// =============================================================================

#define APIBSect_Normal				0x0000						// normal upright parallel sided wall
#define	APIBSect_Poly				0x0001						// extruded wall from polygon

/**
 * @brief Represents an segment of the beam element.
 * @struct API_BeamSegmentType
 * @ingroup Element
 */
struct API_BeamSegmentType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;

/**
 * @brief The guid of the owner beam.
 * @var owner
 */
	API_Guid						owner;

/**
 * @brief General informations about segment.
 * @var assemblySegmentData
 */
	API_AssemblySegmentData			assemblySegmentData;

/**
 * @brief The material override structure of the left side of the beam.
 * @var leftMaterial
 */
	API_OverriddenAttribute			leftMaterial;

/**
 * @brief Material override structure of the top of the beam.
 * @var topMaterial
 */
	API_OverriddenAttribute			topMaterial;

/**
 * @brief Material override structure of the right side of the beam.
 * @var rightMaterial
 */
	API_OverriddenAttribute			rightMaterial;

/**
 * @brief Material override structure of the bottom of the beam.
 * @var bottomMaterial
 */
	API_OverriddenAttribute			bottomMaterial;

/**
 * @brief The material override structure of the beginning and end side of the beam.
 * @var endsMaterial
 */
	API_OverriddenAttribute			endsMaterial;

/**
 * @brief The material override structure of the extrusion surface.
 * @var extrusionMaterial
 */
	API_OverriddenAttribute			extrusionMaterial;

/**
 * @brief Are surface materials chained?
 * @var materialsChained
 */
	bool							materialsChained;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	char							filler_0[7];

};

/**
 * @brief Determines the shape of the holes in the beam.
 * @enum API_BHoleTypeID
 * @ingroup Element
 */
typedef enum {
	APIBHole_Rectangular,
	APIBHole_Circular

} API_BHoleTypeID;

/**
 * @brief Describes a beam hole.
 * @struct API_Beam_Hole
 * @ingroup Element
 */
struct API_Beam_Hole {

/**
 * @brief Type of the hole (rectangular / circular).
 * @var holeType
 */
	API_BHoleTypeID					holeType;

/**
 * @brief Show the hole's contour in 2D?
 * @var holeContureOn
 */
	bool							holeContureOn;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	short							filler_2;

/**
 * @brief ID of the hole, unique in the beam.
 * @var holeID
 */
	Int32							holeID;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3;

/**
 * @brief The 'x' location of the hole's center relative to the beginning coordinate of the beam.
 * @var centerx
 */
	double							centerx;

/**
 * @brief The 'z' location of the hole's center relative to the top of the beam.
 * @var centerz
 */
	double							centerz;

/**
 * @brief The width of the hole.
 * @var width
 */
	double							width;

/**
 * @brief The height of the hole (effective only for the rectangular type).
 * @var height
 */
	double							height;

};


typedef enum {
	APIBeamLineShowAlways	= 0,
	APIBeamLineHideAlways	= 1,
	APIBeamLineByMVO = 2
} API_BeamVisibleLinesID;

/**
 * @brief The type of segment length.
 * @enum API_BeamShapeTypeID
 * @ingroup Element
 */
typedef enum {
	API_StraightBeam			= 0,
	API_HorizontallyCurvedBeam	= 1,
	API_VerticallyCurvedBeam	= 2
} API_BeamShapeTypeID;

/**
 * @brief Represents a beam element.
 * @struct API_BeamType
 * @ingroup Element
 * @remark The elements' structure type is defined with the new `modelElemStructureType` member. The related attribute indices are separated into `buildingMaterial` and `profileAttr`.
 * 		   The elements' cut fill foreground and background pens inherit from the element structure and can be overridden on the element level.
 * 		   The elements' surface materials inherit from the element structure and can be overridden on the element level.
 * 		   For beam-related memo data see the @ref ACAPI_Element_GetMemo function.
 */
struct API_BeamType {
	/**
	 * @brief General element header
	 * @var head
	 */
	API_Elem_Head						head;

    /**
     * @brief Pen index of the overhead lines.
     * @var aboveViewLinePen
     */
	short								aboveViewLinePen;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	char								filler_0[2];

    /**
     * @brief Linetype of the overhead lines.
     * @var aboveViewLineType
     */
	API_AttributeIndex					aboveViewLineType;

    /**
     * @brief The linetype index of the reference line.
     * @var refLtype
     */
	API_AttributeIndex					refLtype;

    /**
     * @brief The pen index of the reference line.
     * @var refPen
     */
	short								refPen;

    /**
     * @brief The pen index of the cut lines of the beam.
     * @var cutContourLinePen
     */
	short								cutContourLinePen;

    /**
     * @brief The line type index of the beam section contour line.
     * @var cutContourLineType
     */
	API_AttributeIndex					cutContourLineType;

    /**
     * @brief Sequence is required when two beams meet with the same priority or when 3 or more beams meet in a junction.
     * 		  Its values can be between 0 and 999.
     * @var sequence
     */
	Int32								sequence;

	/**
	 * @brief Cut fill pens set in the used structure (building material, complex profile) can be overridden on the element level.
	 * @var cutFillPen
	 */
	API_OverriddenPen					cutFillPen;

	/**
	 * @brief Cut fill pens set in the used structure (building material, complex profile) can be overridden on the element level.
	 * @var cutFillBackgroundPen
	 */
	API_OverriddenPen					cutFillBackgroundPen;

	/**
	 * @brief The option to define on which stories display the beam.
	 * @var visibility
	 */
	API_StoryVisibility					visibility;	

	/**
	 * @brief Mode of linking to home story.
	 * @var linkToSettings
	 */
	API_LinkToSettings					linkToSettings;

	/**
	 * @brief The shape of the beam hole (see @ref API_BHoleTypeID).
	 * @var holeType
	 */
	API_BHoleTypeID						holeType;

	/**
	 * @brief Show the hole's contour on the plan.
	 * @var holeContureOn
	 */
	bool								holeContureOn;

	/**
	 * @brief Recalculate the story visibility automatically according to the actual elevation of the beam.
	 * @var isAutoOnStoryVisibility
	 */
	bool								isAutoOnStoryVisibility;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	char								filler_1[6];

    /**
     * @brief The default width of the holes.
     * @var holeWidth
     */
	double								holeWidth;

    /**
     * @brief The default height of the holes (effective only for the rectangle type - `holeType` is `APIBHole_Rectangular`).
     * @var holeHeight
     */
	double								holeHeight;

    /**
     * @brief The default level of the holes: the distance between the center of the hole and the top of the beam.
     * @var holeLevel
     */
	double								holeLevel;

    /**
     * @brief The offset of beam's reference line from the center.
     * @var offset
     */
	double								offset;

    /**
     * @brief The top height of the beam relative to the floor level.
     * @var level
     */
	double								level;

    /**
     * @brief Show the contour lines of the beam.
     * @var showContourLines
     */
	API_BeamVisibleLinesID				showContourLines;

    /**
     * @brief Show the reference axis of the beam.
     * @var showReferenceAxis
     */
	API_BeamVisibleLinesID				showReferenceAxis;

    /**
     * @brief The beginning (start) coordinate of the beam.
     * @var begC
     */
	API_Coord							begC;

    /**
     * @brief The end coordinate of the beam.
     * @var endC
     */
	API_Coord							endC;

    /**
     * @brief The arc angle of the curved beam between `begC` and `endC` (negative value results an arc
     * 		  on the opposite side). This value is always zero for straight beams.
     * @var curveAngle
     */
	double								curveAngle;

    /**
     * @brief The height of the vertical curvature of the beam.
     * @var verticalCurveHeight
     */
	double								verticalCurveHeight;

    /**
     * @brief Hidden line type.
     * @var hiddenLineType
     */
	API_AttributeIndex					hiddenLineType;

	/**
	 * @brief Hidden line pen.
	 * @var hiddenLinePen
	 */
	short								hiddenLinePen;

	/**
	 * @brief Anchor point of the beam.
	 * 		  |0|1|2|
	 * 		  |3|4|5|
	 * 		  |6|7|8|
	 * @var anchorPoint
	 */
	short								anchorPoint;

    /**
     * @brief Linetype of the uncut lines.
     * @var belowViewLineType
     */
	API_AttributeIndex					belowViewLineType;

    /**
     * @brief Pen index of the uncut lines.
     * @var belowViewLinePen
     */
	short								belowViewLinePen;

    /**
     * @brief Defines whether the beam is mirrored. Applies to profiled beams only.
     * @var isFlipped
     */
	bool								isFlipped;

    /**
     * @brief Defines whether the beam is slanted.
     * @var isSlanted
     */
	bool								isSlanted;

    /**
     * @brief Slant angle.
     * @var slantAngle
     */
	double								slantAngle;

    /**
     * @brief Profile rotating angle around it's center line.
     * @var profileAngle
     */
	double								profileAngle;

    /**
     * @brief Type to define if beam is straight, horizontally or vertically curved.
     * @var beamShape
     */
	API_BeamShapeTypeID					beamShape;

    /**
     * @brief Display options of the element on the floor plan.
     * @var displayOption
     */
	API_ElemDisplayOptionsID			displayOption;

    /**
     * @brief Defines the range within the element is shown on the floor plan.
     * @var viewDepthLimitation
     */
	API_ElemViewDepthLimitationsID		viewDepthLimitation;

    /**
     * @brief Uncut projection mode.
     * @var uncutProjectionMode
     */
	API_ElemProjectionModesID			uncutProjectionMode;

    /**
     * @brief Overhead projection mode.
     * @var overheadProjectionMode
     */
	API_ElemProjectionModesID			overheadProjectionMode;

    /**
     * @brief Number of segments.
     * @var nSegments
     */
	UInt32								nSegments;

    /**
     * @brief Number of cuts.
     * @var nCuts
     */
	UInt32								nCuts;

    /**
     * @brief Number of schemes.
     * @var nSchemes
     */
	UInt32								nSchemes;

    /**
     * @brief Number of profiles.
     * @var nProfiles
     */
	UInt32								nProfiles;

    /**
     * @brief Use Floor plan fill.
     * @var useCoverFill
     */
	bool 								useCoverFill;

    /**
     * @brief Use the fill attribute assigned to the surface material of the element.
     * @var useCoverFillFromSurface
     */
	bool 								useCoverFillFromSurface;

    /**
     * @brief Use cover fill orientation from 3D element view.
     * @var coverFillOrientationComesFrom3D
     */
	bool 								coverFillOrientationComesFrom3D;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	char								filler_2;

    /**
     * @brief Type of the cover fill.
     * @var coverFillType
     */
	API_AttributeIndex					coverFillType;

	/**
	 * @brief Foreground pen of the cover fill.
	 * @var coverFillForegroundPen
	 */
	short coverFillForegroundPen;

    /**
     * @brief Background pen of the cover fill.
     * @var coverFillBackgroundPen
     */
	short 								coverFillBackgroundPen;

	/**
	 * @brief TransformationType of the fill.
	 * @var coverFillTransformationType
	 */
	API_CoverFillTransformationTypeID	coverFillTransformationType;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	char								filler_3[4];

	/**
	 * @brief Orientation and distortion parameters of the cover fill.
	 * @var coverFillTransformation
	 */
	API_CoverFillTransformation coverFillTransformation;
};


// =============================================================================
// Window/Door/Skylight
//
// =============================================================================

typedef enum {
	API_NoLink						= -1,
	API_LinkSillToWallBottom		= 0,
	API_LinkSillToStory				= 1,
	API_LinkHeaderToWallBottom		= 2,
	API_LinkHeaderToStory			= 3,
	API_LinkSkylightToRoofPivot		= 4,
	API_LinkSkylightToStory			= 5,
	API_LinkSkylightToShellBase		= 6,
	API_LinkSillToWallTop			= 7,
	API_LinkHeaderToWallTop			= 8
} API_VerticalLinkID;

/**
 * @brief Option for anchoring the vertical position of an opening within the wall or the roof.
 * @struct API_VerticalLink
 * @ingroup Element
 * @remarks This structure defines the vertical anchor
 * 			- of a window/door element (see @ref API_WindowType), to wall or story, by sill height or header,
 * 			- of a skylight element (see @ref API_SkylightType), to roof or story, by the selected anchor point.
 */
struct API_VerticalLink {

/**
 * @brief Type of the vertical anchor
 * 		  |API_VerticalLinkID|Meaning|
 * 		  |--- |--- |
 * 		  |API_NoLink|Undefined vertical link type, not applicable for windows/doors and skylights|
 * 		  |API_LinkSillToWallBottom|Position the sill of the opening relative to the bottom of the containing wall|
 * 		  |API_LinkSillToStory|Position the sill of the opening relative to a given story|
 * 		  |API_LinkHeaderToWallBottom|Position the header of the opening relative to the bottom of the containing wall|
 * 		  |API_LinkHeaderToStory|Position the header of the opening relative to a given story|
 * 		  |API_LinkSkylightToRoofPivot|Position the skylight anchor vertically relative to the roof pivot lines|
 * 		  |API_LinkSkylightToStory|Position the skylight anchor vertically relative to a given story|
 * 		  |API_LinkSkylightToShellBase|Position the skylight anchor relative to ShellBase|
 * 		  |API_LinkSillToWallTop|Position the sill of the opening relative to the top of the containing wall|
 * 		  |API_LinkHeaderToWallTop|Position the header of the opening relative to the top of the containing wall|
 *
 * @var linkType
 */
	API_VerticalLinkID				linkType;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief The index of the anchor story if linked to story, 0 otherwise.
 * @var linkValue
 */
	short							linkValue;

};

/**
 * @brief Represents the common part of window, door and skylight elements.
 * @struct API_OpeningBaseType
 * @ingroup Element
 * @remarks  This structure is created from @ref API_WindowType to hold the common parameters of @ref API_WindowType and @ref API_SkylightType.
 * 			 For window/door/skylight related memo data see the @ref ACAPI_Element_GetMemo function.
 */
struct API_OpeningBaseType {									// common part of windows, doors and skylights

/**
 * @brief Pen index.
 * @var pen
 */
	short							pen;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	short							filler_0;

/**
 * @brief Line type index.
 * @var ltypeInd
 */
	API_AttributeIndex				ltypeInd;

/**
 * @brief Material index.
 * @var mat
 */
	API_AttributeIndex				mat;

/**
 * @brief Fill index of section of the opening.
 * @var sectFill
 */
	API_AttributeIndex				sectFill;

/**
 * @brief Pen index of the fill of the section of the opening.
 * @var sectFillPen
 */
	short							sectFillPen;

/**
 * @brief Background pen index of the fill of the section of the opening.
 * @var sectBGPen
 */
	short							sectBGPen;

/**
 * @brief Contour pen index of the fill of the section of the opening.
 * @var sectContPen
 */
	short							sectContPen;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief Line type index for cut lines of the opening.
 * @var cutLineType
 */
	API_AttributeIndex				cutLineType;

/**
 * @brief Line type used when "Overhead All" is selected from the "Floor Plan Display" popup. Corresponds to the "Overhead Lines" value in the Door/Window Settings dialog.
 * @var aboveViewLineType
 */
	API_AttributeIndex				aboveViewLineType;

/**
 * @brief Pen used when "Overhead All" is selected from the "Floor Plan Display" popup. Corresponds to the "Overhead Line Pens" value in the Door/Window Settings dialog.
 * @var aboveViewLinePen
 */
	short							aboveViewLinePen;

/**
 * @brief Pen index of the uncut lines of the opening.
 * @var belowViewLinePen
 */
	short							belowViewLinePen;

/**
 * @brief Line type used when "OutLines Only" is selected from the "Floor Plan Display" popup. Corresponds to the "Uncut Lines" value in the Door/Window Settings dialog.
 * @var belowViewLineType
 */
	API_AttributeIndex				belowViewLineType;

/**
 * @brief Use the pens defined in the library part.
 * @var useObjPens
 */
	bool							useObjPens;

/**
 * @brief Use the line types defined in the library part.
 * @var useObjLtypes
 */
	bool							useObjLtypes;

/**
 * @brief Use the materials defined in the library part.
 * @var useObjMaterials
 */
	bool							useObjMaterials;

/**
 * @brief Use the section attributes defined in the library part.
 * @var useObjSectAttrs
 */
	bool							useObjSectAttrs;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool							filler_2[4];


/**
 * @brief Width of the opening.
 * @var width
 */
	double							width;

/**
 * @brief Vertical size of the opening.
 * @var height
 */
	double							height;

/**
 * @brief Sub-floor thickness (used to be Parapet correction ppCorr).
 * @var subFloorThickness
 */
	double							subFloorThickness;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	char							filler_3[16];


/**
 * @brief Index to the symbol in the library. If 0, an empty window/door/skylight hole is created.
 * @var libInd
 */
	Int32							libInd;

/**
 * @brief The anchor position defining how the window/door element to be kept fixed during elevation changes.
 * @var verticalLink
 */
	API_VerticalLink				verticalLink;

/**
 * @brief True if mirrored to Y axis.
 * @var reflected
 */
	bool						    reflected;

/**
 * @brief True if mirrored to X axis.
 * @var oSide
 */
	bool							oSide;

/**
 * @brief True if mirrored to X axis (same as oSide).
 * @var refSide
 */
	bool							refSide;

/**
 * @brief True if the window inherits the gables of the owner wall.
 * @var wallCutUsing
 */
	bool							wallCutUsing;

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	bool							filler_4[4];

/**
 * @brief Same number for similar-looking windows/doors/skylights 2D draw.
 * @var lookId
 */
	GS::Int64						lookId;

/**
 * @brief Guid of the dimension marker symbol.
 * @var markGuid
 */
	API_Guid						markGuid;


/**
 * @brief Display options of the element on the floor plan (see @ref API_ElemDisplayOptionsID).
 * @var displayOption
 */
	API_ElemDisplayOptionsID		displayOption;

/**
 * @brief Reserved for later use.
 * @var filler_5
 */
	Int32							filler_5;

};


// -----------------------------------------------------------------------------
// Window/Door
// -----------------------------------------------------------------------------

#define	APIHoleAnchor_BegFix		-1
#define	APIHoleAnchor_CenterFix		0
#define	APIHoleAnchor_EndFix		1

/**
 * @brief Window Door Direction type.
 * @enum API_WindowDoorDirectionTypes
 * @ingroup Elment
 */
typedef enum {
	API_WDAssociativeToWall			= 0,
	API_WDVertical					= 1
} API_WindowDoorDirectionTypes;

/**
 * @brief Window Door Reveal Depth Location type.
 * @enum API_WindowDoorRevealDepthLocationID
 * @ingroup Elment
 */
typedef enum {
	APIWDRevealDepth_Side				= 0,
	APIWDRevealDepth_Core				= 1
} API_WindowDoorRevealDepthLocationID;


/**
 * @brief Represents a window element.
 * @struct API_WindowType
 * @ingroup Element
 * @remarks For window related memo data see the @ref ACAPI_Element_GetMemo function. See also @ref API_DoorType.
 */
struct API_WindowType {
/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head						head;

/**
 * @brief Common part of windows, doors and skylights (see @ref API_OpeningBaseType).
 * @var openingBase
 */
	API_OpeningBaseType					openingBase;

/**
 * @brief The location of the reveal depth reference line.
 * 		  | APIWDRevealDepth_Side | The reference line location is on the clicked side of the wall. |
 * 		  | APIWDRevealDepth_Core | The reference line location is on the core (clicked side) skin of the composite structure. |
 * @var revealDepthLocation
 */
	API_WindowDoorRevealDepthLocationID	revealDepthLocation;

/**
 * @brief Inset from the clicked side of wall or core (according to @c revealDepthLocation).
 * @var revealDepthOffset
 */
	double								revealDepthOffset;

/**
 * @brief Calculated inset from the clicked side of wall.
 * @var revealDepthFromSide
 */
	double								revealDepthFromSide;

/**
 * @brief Inset on top.
 * @var jambDepthHead
 */
	double								jambDepthHead;

/**
 * @brief Inset on bottom.
 * @var jambDepthSill
 */
	double								jambDepthSill;

/**
 * @brief Inset on left.
 * @var jambDepth
 */
	double								jambDepth;

/**
 * @brief Inset on right.
 * @var jambDepth2
 */
	double								jambDepth2;

/**
 * @brief True if the opening has reveal.
 * @var reveal
 */
	bool								reveal;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool								filler_1[7];

/**
 * @brief Reference to the container wall (see @ref API_Guid).
 * @var owner
 */
	API_Guid							owner;

/**
 * @brief Location of the center of the window. If the container wall is polygonal, this value is not used.
 * @var objLoc
 */
	double								objLoc;

/**
 * @brief Parapet height.
 * @var lower
 */
	double								lower;

/**
 * @brief The location of the center point of the opening. It is measured from the beginning corner of the wall roof etc., rotated into the direction of the wall reference edge starting from the first corner. Note that this location can be outside of the wall polygon.
 * @var startPoint
 */
	API_Coord							startPoint;

/**
 * @brief The direction vector of the opening in a polygonal wall, relative to the wall reference edge starting from the first corner.
 * @var dirVector
 */
	API_Coord							dirVector;

/**
 * @brief Type of the plane orientation of the window placed into slanted wall.
 * 		  |Direction type|Meaning|
 * 		  |--- |--- |
 * 		  |API_WDAssociativeToWall|The plane of the window follows the plane of the wall|
 * 		  |API_WDVertical|The window is placed vertically regardless of the plane of the wall it is placed into|
 *
 * @var directionType
 */
	API_WindowDoorDirectionTypes		directionType;

/**
 * @brief The fixed (placement) point of the window (relative to the owning wall's reference line):
 * 		  | APIHoleAnchor_BegFix | Beginning point is fixed. |
 * 		  | APIHoleAnchor_CenterFixCenter | Center point is fixed. |
 * 		  | APIHoleAnchor_EndFixEnd | End point is fixed. |
 * @var fixPoint
 */
	short								fixPoint;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	short								filler_2;
};


/**
 * @brief Represents a door element.
 * @ingroup Element
 * @remarks For door related memo data see the @ref ACAPI_Element_GetMemo function.
 * @sa @ref API_WindowType
 */
using API_DoorType = API_WindowType;


// -----------------------------------------------------------------------------
// Skylight
// -----------------------------------------------------------------------------

/**
 * @brief Skylight constrain in the Roof element.
 * @enum API_SkylightFixModeID
 * @ingroup Element
 */
typedef enum {
	APISkylightFixMode_Horizontal,
	APISkylightFixMode_Vertical

} API_SkylightFixModeID;

/**
 * @brief Anchor point of the Skylight object.
 * @enum API_SkylightAnchorID
 * @ingroup Element
 */
typedef enum {
	APISkylightAnchor_BC			= 0,						// bottom center anchor
	APISkylightAnchor_BL			= 1,						// bottom left anchor
	APISkylightAnchor_BR			= 2,						// bottom right anchor
	APISkylightAnchor_TC			= 3,						// top center anchor
	APISkylightAnchor_TL			= 4,						// top left anchor
	APISkylightAnchor_TR			= 5							// top right anchor

} API_SkylightAnchorID;

/**
 * @brief Represents a skylight element.
 * @struct API_SkylightType
 * @ingroup Element
 * @remarks For skylight related memo data see the @ref ACAPI_Element_GetMemo function.
 */
struct API_SkylightType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;


/**
 * @brief Common part of windows, doors and skylights (see @ref API_OpeningBaseType).
 * @var openingBase
 */
	API_OpeningBaseType				openingBase;


/**
 * @brief Reference to the container roof or shell.
 * @var owner
 */
	API_Guid						owner;

/**
 * @brief For polyroofs it is the ID of the vertex of the pivot polygon. For plane roofs it is always 0.
 * @var vertexID
 */
	UInt32							vertexID;

/**
 * @brief Defines how the skylight is constrained in case the angle or the vertical position of the owner roof or shell changes (see @ref API_SkylightFixModeID).
 * @var fixMode
 */
	API_SkylightFixModeID			fixMode;

/**
 * @brief Anchor point of the skylight.
 * @var anchorPoint
 */
	API_SkylightAnchorID			anchorPoint;

/**
 * @brief The global XY cooordinate of the anchor point (see fixPoint)
 * @var anchorPosition
 */
	API_Coord						anchorPosition;

/**
 * @brief The global Z coordinate of the anchor point.
 * @var anchorLevel
 */
	double							anchorLevel;

/**
 * @brief The rotation angle measured clockwise in the horizontal plane.
 * @var azimuthAngle
 */
	double							azimuthAngle;

/**
 * @brief The elevation angle of the roof at the insert position.
 * @var elevationAngle
 */
	double							elevationAngle;

};


// =============================================================================
// Object/Lamp
//
// =============================================================================

/**
 * @brief Represents an object or a lamp, or a symbol label.
 * @struct API_ObjectType
 * @ingroup Element
 * @since Archicad 26
 * @remarks For beam related memo data see the @ref ACAPI_Element_GetMemo function.
 * 			From version 26 the type of the `ownerID` member was changed to @ref API_ElemType.
 * @sa API_LampType
 */
struct API_ObjectType {
/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;

/**
 * @brief Pen attribute index.
 * @var pen
 */
	short							pen;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	short							filler_0;

/**
 * @brief Line type attribute index.
 * @var ltypeInd
 */
	API_AttributeIndex				ltypeInd;

/**
 * @brief Material attribute index.
 * @var mat
 */
	API_AttributeIndex				mat;

/**
 * @brief Section fill attribute index.
 * @var sectFill
 */
	API_AttributeIndex				sectFill;

/**
 * @brief Section fill pen attribute index.
 * @var sectFillPen
 */
	short							sectFillPen;

/**
 * @brief Section fill background pen attribute index.
 * @var sectBGPen
 */
	short							sectBGPen;

/**
 * @brief Section fill contour pen attribute index.
 * @var sectContPen
 */
	short							sectContPen;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief Use the pens defined in the library part?
 * @var useObjPens
 */
	bool							useObjPens;

/**
 * @brief Use the line types defined in the library part.
 * @var useObjLtypes
 */
	bool							useObjLtypes;

/**
 * @brief Use the materials defined in the library part.
 * @var useObjMaterials
 */
	bool							useObjMaterials;

/**
 * @brief Is the symbol reflected?
 * @var reflected
 */
	bool							reflected;

/**
 * @brief Use the A and B values as fixed sizes?
 * @var useXYFixSize
 */
	bool							useXYFixSize;

/**
 * @brief Use the section attributes defined in the library part?
 * @var useObjSectAttrs
 */
	bool							useObjSectAttrs;

/**
 * @brief The index-1 of hotspot to keep fixed.
 * @var fixPoint
 */
	short							fixPoint;

/**
 * @brief The rotation angle (radian).
 * @var angle
 */
	double							angle;

/**
 * @brief The base height from the floor level.
 * @var level
 */
	double							level;

/**
 * @brief The ratio of the size of the placed object/lamp in the X direction and the A value defined in the library part (multiplication factor in X direction).
 * @var xRatio
 */
	double							xRatio;

/**
 * @brief The ratio of the size of the placed object/lamp in the Y direction and the B value defined in the library part (multiplication factor in Y direction).
 * @var yRatio
 */
	double							yRatio;

/**
 * @brief Offset of the symbol's origin from insertion point.
 * @var offset
 */
	API_Coord						offset;

/**
 * @brief Use fix angle.
 * @var fixedAngle
 */
	Int32							fixedAngle;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	char							filler_2[12];

/**
 * @brief Color of the light (for lamps only).
 * @var lightColor
 */
	API_RGBColor					lightColor;

/**
 * @brief Visibility information of the object/lamp.
 * @var visibility
 */
	API_StoryVisibility				visibility;

/**
 * @brief Mode of linking to home story.
 * @var linkToSettings
 */
	API_LinkToSettings				linkToSettings;

/**
 * @brief The light is on/off.
 * @var lightIsOn
 */
	bool							lightIsOn;

/**
 * @brief Recalculate the story visibility automatically according to the actual vertical extent of the object ("All Relevant Stories").
 * @var isAutoOnStoryVisibility
 */
	bool							isAutoOnStoryVisibility;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	bool							filler_3[6];

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	Int32							filler_4;

/**
 * @brief Type of the owner (external object).
 * @var ownerType
 */
	API_ElemType					ownerType;

/**
 * @brief Index of the owner element of the object.
 * @var owner
 */
	API_Guid						owner;

/**
 * @brief Index to the symbol in the library.
 * @var libInd
 */
	Int32							libInd;

/**
 * @brief Reserved for later use.
 * @var filler_5
 */
	Int32							filler_5;

/**
 * @brief Position of the origin of the object.
 * @var pos
 */
	API_Coord						pos;

/**
 * @brief Reserved for later use.
 * @var filler_6
 */
	bool							filler_6[4];

/**
 * @brief Same number for similar-looking objects/lamps 2D draw.
 * @var lookId
 */
	GS::Int64						lookId;

/**
 * @brief Reserved for later use.
 * @var filler_7
 */
	Int32							filler_7[3];
};

/**
 * @brief Represents an object or a lamp, or a symbol label.
 * @ingroup Element
 * @since Archicad 26
 * @remarks For beam related memo data see the @ref ACAPI_Element_GetMemo function. See also @ref API_ObjectType.
 */
using API_LampType = API_ObjectType;


// =============================================================================
// Slab
//
// =============================================================================

/**
 * @brief Location of slab's reference plane.
 * @enum API_SlabReferencePlaneLocationID
 * @ingroup Element
 * @remarks The @ref API_SlabReferencePlaneLocationID enum is used in the @ref API_SlabType structure.
 * 			The following picture illustrates the different values:
 * @image html Slab_Reference_Line_logic.png "Slab reference line" width=50%
 * 		  For a basic (homogenous) slab the possible values are `APISlabRefPlane_Top` or `APISlabRefPlane_Bottom`.
 * 		  For composite slabs all values are valid. It determines the reference position: so during input the level member
 * 		  in @ref API_SlabType will refer to this position.
 * 		  The new `offsetFromTop` [output only] member tells you the distance of the reference position (level) from the top of the slab.
 */
typedef enum {
	APISlabRefPlane_Top = 0,
	APISlabRefPlane_CoreTop,
	APISlabRefPlane_CoreBottom,
	APISlabRefPlane_Bottom

} API_SlabReferencePlaneLocationID;

/**
 * @brief Represents a slab element.
 * @struct API_SlabType
 * @ingroup Element
 * @remarks For slab related memo data see the @ref ACAPI_Element_GetMemo function.
 * 			In Archicad 10 the useLocalOrigo, locOrigo and fillAngle fields are placed into a separate structure (API_HatchOrientation).
 * 			The type of the elements' structure is defined with the new modelElemStructureType member. The related attribute indices are separated into buildingMaterial and composite. The composite index is a non-negative index.
 * 			The elements' cut fill foreground and background pens inherit from the element structure, and can be overridden on the element level.
 * 			The elements' surface materials inherit from the element structure, and can be overridden on the element level.
 */
struct API_SlabType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head						head;


/**
 * @brief Pen attribute index of the slab's contour.
 * @var pen
 */
	short								pen;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	short								filler_0;

/**
 * @brief Line type attribute index of the slab's contour.
 * @var ltypeInd
 */
	API_AttributeIndex					ltypeInd;

/**
 * @brief The structure type of the slab.
 * @var modelElemStructureType
 */
	API_ModelElemStructureType			modelElemStructureType;

/**
 * @brief Building Material index of slabs's hatch. Used only, if structure type is @c API_BasicStrucure.
 * @var buildingMaterial
 */
	API_AttributeIndex					buildingMaterial;

/**
 * @brief Composite index of slab. Used only, if structure type is @c API_CompositeStructure.
 * @var composite
 */
	API_AttributeIndex					composite;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short								filler_1;

/**
 * @brief Contour pen attribute index of the slab's fill in sections.
 * @var sectContPen
 */
	short								sectContPen;

/**
 * @brief Cut fill pens set in the used structure (building material, composite) can be overridden on the element level.
 * @var cutFillPen
 */
	API_OverriddenPen					cutFillPen;

/**
 * @brief Cut fill pens set in the used structure (building material, composite) can be overridden on the element level.
 * @var cutFillBackgroundPen
 */
	API_OverriddenPen					cutFillBackgroundPen;

/**
 * @brief Top material attribute override structure.
 * @var topMat
 */
	API_OverriddenAttribute				topMat;

/**
 * @brief Side material attribute override structure.
 * @var sideMat
 */
	API_OverriddenAttribute				sideMat;

/**
 * @brief Bottom material attribute override structure.
 * @var botMat
 */
	API_OverriddenAttribute				botMat;

/**
 * @brief Are surface materials chained?.
 * @var materialsChained
 */
	bool								materialsChained;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool								filler_2[7];

/**
 * @brief Thickness of the slab.
 * @var thickness
 */
	double								thickness;

/**
 * @brief Distance of the reference level of the slab from the floor level.
 * @var level
 */
	double								level;

/**
 * @brief Line type of the slab's Hidden Contour.
 * @var hiddenContourLineType
 */
	API_AttributeIndex					hiddenContourLineType;

/**
 * @brief Pen of the slab's Hidden Contour line.
 * @var hiddenContourLinePen
 */
	short								hiddenContourLinePen;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	short								filler_3;

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	char								filler_4[16];

/**
 * @brief Line type attribute index of the slab's section contour.
 * @var sectContLtype
 */
	API_AttributeIndex					sectContLtype;

/**
 * @brief Location of the reference plane.
 * @var referencePlaneLocation
 */
	API_SlabReferencePlaneLocationID	referencePlaneLocation;

/**
 * @brief Use cover fill?
 * @var useFloorFill
 */
	bool								useFloorFill;

/**
 * @brief Reserved for later use.
 * @var filler_5
 */
	bool								filler_5[7];


/**
 * @brief Visibility of slab's contour line. On the element's own story the contour should allways be visible.
 * @var visibilityCont
 */
	API_StoryVisibility					visibilityCont;

/**
 * @brief Visibility of slab's cover fill.
 * @var visibilityFill
 */
	API_StoryVisibility					visibilityFill;

/**
 * @brief Mode of linking to home story.
 * @var linkToSettings
 */
	API_LinkToSettings					linkToSettings;

/**
 * @brief Pen attribute index of slab's cover fill.
 * @var floorFillPen
 */
	short								floorFillPen;

/**
 * @brief Background pen attribute index of the slab's cover fill.
 * @var floorFillBGPen
 */
	short								floorFillBGPen;

/**
 * @brief Fill attribute index of the slab's cover fill.
 * @var floorFillInd
 */
	API_AttributeIndex					floorFillInd;

/**
 * @brief Use Vectorial 3D Hatch patterns in Floor Plan view? This will apply the Vectorial 3D Hatch set for the element's top side material.
 * @var use3DHatching
 */
	bool								use3DHatching;

/**
 * @brief Reserved for later use.
 * @var filler_6
 */
	bool								filler_6[3];

/**
 * @brief Vertical distance between the reference level and the top of the slab (output only), see @ref API_SlabReferencePlaneLocationID.
 * @var offsetFromTop
 */
	double								offsetFromTop;


/**
 * @brief Polygon of the slab.
 * @var poly
 */
	API_Polygon							poly;

/**
 * @brief Reserved for later use.
 * @var filler_7
 */
	Int32								filler_7[4];

/**
 * @brief Orientation and distortion parameters of the cover fill.
 * @var hatchOrientation
 */
	API_HatchOrientation				hatchOrientation;

/**
 * @brief Reserved for later use.
 * @var filler_8
 */
	short								filler_8[4];


/**
 * @brief Reserved for later use.
 * @var filler_9
 */
	bool								filler_9[8];

};


// =============================================================================
// Roof/Shell
//
// =============================================================================

/**
 * @brief These values affect the connection type of Roof and Shell elements (see on the Model tab page of the Roof/Shell Settings dialog).
 * @enum API_ShellBaseCutBodyTypeID
 * @ingroup Element
 * @remarks This enumeration type is used in the @ref API_ShellBaseType structure.
 */
typedef enum {
	APIShellBaseCutBody_Editable,
	APIShellBaseCutBody_ContoursDown,
	APIShellBaseCutBody_PivotLinesDown,
	APIShellBaseCutBody_UpwardsExtrusion,
	APIShellBaseCutBody_DownwardsExtrusion

} API_ShellBaseCutBodyTypeID;

/**
 * @brief Arc decomposition method for polyroof pivot edges or revolved shells. An N integral number tells how many segments to generate and this enum determines how to use the number N.
 * @enum API_ShellBaseSegmentTypeID
 * @ingroup Element
 */
typedef enum {
	APIShellBase_SegmentsByCircle,
	APIShellBase_SegmentsByArc

} API_ShellBaseSegmentTypeID;

/**
 * @brief The common parameters of roof (API_RoofType) and shell (API_ShellType) elements.
 * @struct API_ShellBaseType
 * @ingroup Element
 * @remarks  This structure is created from @ref API_RoofType to hold the common parameters of @ref API_RoofType and @ref API_ShellType.
 * 			 The type of the elements' structure is defined with the new modelElemStructureType member. The related attribute indices are separated into buildingMaterial and composite. The composite index is a non-negative index.
 * 			 The elements' cut fill foreground and background pens inherit from the element structure, and can be overridden on the element level.
 * 			 The elements' surface materials inherit from the element structure, and can be overridden on the element level.
 * 			 For shell related memo data see the @ref ACAPI_Element_GetMemo function.
 */
struct API_ShellBaseType {

/**
 * @brief Pen attribute index of the contour.
 * @var pen
 */
	short							pen;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	short							filler_0;

/**
 * @brief Line type attribute index of the contour.
 * @var ltypeInd
 */
	API_AttributeIndex				ltypeInd;

/**
 * @brief The structure type of the shellBase.
 * @var modelElemStructureType
 */
	API_ModelElemStructureType		modelElemStructureType;

/**
 * @brief Building Material index of shellBase's hatch. Used only, if structure type is @c API_BasicStrucure.
 * @var buildingMaterial
 */
	API_AttributeIndex				buildingMaterial;

/**
 * @brief Composite index of shellBase. Used only, if structure type is @c API_CompositeStructure.
 * @var composite
 */
	API_AttributeIndex				composite;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1[2];

/**
 * @brief Cut fill pens set in the used structure (building material, composite) can be overridden on the element level.
 * @var cutFillPen
 */
	API_OverriddenPen				cutFillPen;

/**
 * @brief Cut fill pens set in the used structure (building material, composite) can be overridden on the element level.
 * @var cutFillBackgroundPen
 */
	API_OverriddenPen				cutFillBackgroundPen;

/**
 * @brief Line type attribute index of the element's section contour.
 * @var sectContLtype
 */
	API_AttributeIndex				sectContLtype;

/**
 * @brief Contour pen attribute index of the fill in sections.
 * @var sectContPen
 */
	short							sectContPen;

/**
 * @brief Pen attribute index of element's cover fill.
 * @var floorFillPen
 */
	short							floorFillPen;

/**
 * @brief Fill attribute index of the element's cover fill.
 * @var floorFillInd
 */
	API_AttributeIndex				floorFillInd;

/**
 * @brief Background pen attribute index of the element's cover fill.
 * @var floorFillBGPen
 */
	short							floorFillBGPen;

/**
 * @brief Pen used when "Overhead All" is selected from the "Floor Plan Display" popup. Corresponds to the "Overhead Line Pens" value in the element's Settings dialog.
 * @var aboveViewLinePen
 */
	short							aboveViewLinePen;

/**
 * @brief Line type used when "Overhead All" is selected from the "Floor Plan Display" popup. Corresponds to the "Overhead Lines" value in the element's Settings dialog.
 * @var aboveViewLineType
 */
	API_AttributeIndex				aboveViewLineType;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	short							filler_2[2];


/**
 * @brief Use cover fill.
 * @var useFloorFill
 */
	bool							useFloorFill;

/**
 * @brief Use the fill attribute assigned to the surface material (vectorial 3D hatch) of the element.
 * @var use3DHatching
 */
	bool							use3DHatching;

/**
 * @brief Align the cover fill pattern with the pivot line of the roof instead of using the fill handle.
 * @var useFillLocBaseLine
 */
	bool							useFillLocBaseLine;

/**
 * @brief Distort the cover fill to have the effect of a sloped roof as seen from above.
 * @var useSlantedFill
 */
	bool							useSlantedFill;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3[8];


/**
 * @brief Orientation and distortion parameters of the cover fill.
 * @var hatchOrientation
 */
	API_HatchOrientation			hatchOrientation;


/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	char							filler_4[16];


/**
 * @brief Top material attribute override structure.
 * @var topMat
 */
	API_OverriddenAttribute			topMat;

/**
 * @brief Side material attribute override structure.
 * @var sidMat
 */
	API_OverriddenAttribute			sidMat;

/**
 * @brief Bottom material attribute override structure.
 * @var botMat
 */
	API_OverriddenAttribute			botMat;


/**
 * @brief Are surface materials chained?
 * @var materialsChained
 */
	bool							materialsChained;

/**
 * @brief Recalculate the story visibility automatically according to the actual vertical extent of the element.
 * @var isAutoOnStoryVisibility
 */
	bool							isAutoOnStoryVisibility;

/**
 * @brief Visibility of the element's contour line. On the element's own story the contour should always be visible.
 * @var visibilityCont
 */
	API_StoryVisibility				visibilityCont;

/**
 * @brief Visibility of the element's cover fill.
 * @var visibilityFill
 */
	API_StoryVisibility				visibilityFill;

/**
 * @brief Mode of linking to home story.
 * @var linkToSettings
 */
	API_LinkToSettings				linkToSettings;


/**
 * @brief Reserved for later use.
 * @var filler_5
 */
	bool							filler_5[12];

/**
 * @brief Reserved for later use.
 * @var filler_6
 */
	Int32							filler_6;


/**
 * @brief Base level of the element (reference line height in case of Roof elements) from the floor level.
 * @var level
 */
	double							level;

/**
 * @brief Thickness of the element.
 * @var thickness
 */
	double							thickness;

/**
 * @brief Type of the trim of the element's edges. (In former API versions this parameter used to be called sideType.)
 * @var edgeTrim
 */
	API_EdgeTrim					edgeTrim;


/**
 * @brief Type of the element's body extension for connections (see @ref API_ShellBaseCutBodyTypeID).
 * @var cutBodyType
 */
	API_ShellBaseCutBodyTypeID		cutBodyType;


/**
 * @brief Display options of the element on the floor plan (see @ref API_ElemDisplayOptionsID).
 * @var displayOption
 */
	API_ElemDisplayOptionsID		displayOption;

/**
 * @brief Defines the range within the element is shown on the floor plan (see @ref API_ElemViewDepthLimitationsID).
 * @var viewDepthLimitation
 */
	API_ElemViewDepthLimitationsID	viewDepthLimitation;


/**
 * @brief Corresponds to the value of "Junction Order" in the settings dialogs, visible only when "Use legacy intersection and Surface methods for model elements" is set in Project Preferences / Legacy.
 * @var compositionPriority
 */
	Int32							compositionPriority;

};


// -----------------------------------------------------------------------------
// Roof
// -----------------------------------------------------------------------------

typedef enum {
	API_PlaneRoofID,
	API_PolyRoofID
} API_RoofClassID;

/**
 * @brief Determines the type of the roof edges. This type is used just for listing purposes. It can be set individualy for each edge of the roof, the default value is Undefined.
 * @enum API_RoofEdgeTypeID
 * @ingroup Element
 */
typedef enum {
	APIRoofEdgeType_Undefined = 0,
	APIRoofEdgeType_Ridge,
	APIRoofEdgeType_Valley,
	APIRoofEdgeType_Gable,
	APIRoofEdgeType_Hip,
	APIRoofEdgeType_Eaves,
	APIRoofEdgeType_Peak,
	APIRoofEdgeType_SideWall,
	APIRoofEdgeType_EndWall,
	APIRoofEdgeType_RTDome,
	APIRoofEdgeType_RTHollow

} API_RoofEdgeTypeID;

/**
 * @brief Defines a level of a polyroof plane. This structure is used in @ref API_PolyRoofData.
 * @struct API_RoofLevelData
 * @ingroup Element
 */
struct API_RoofLevelData {

/**
 * @brief Height of the level.
 * @var levelHeight
 */
	double							levelHeight;

/**
 * @brief Angle of planes measured from horizontal on this level.
 * @var levelAngle
 */
	double							levelAngle;

};

/**
 * @brief Type of the eaves overhang of Multi-plane Roofs.
 * @enum API_RoofOverHangTypeID
 * @ingroup Element
 */
typedef enum {
	API_OffsetOverhang	= 1,
	API_ManualOverhang	= 2

} API_RoofOverHangTypeID;

/**
 * @brief Type of the segment of Multi-plane Roofs.
 * @enum API_PolyRoofSegmentAngleTypeID
 * @ingroup Element
 */
typedef enum {
	APIPolyRoof_SegmentAngleTypeSloped,
	APIPolyRoof_SegmentAngleTypeGable

} API_PolyRoofSegmentAngleTypeID;

/**
 * @brief Texture wrapping parameters. This structure is used in @ref API_LocalCoordsType.
 * @struct API_Wrapping
 * @ingroup Element
 * @remarks For internal use.
 */
struct API_Wrapping {

/**
 * @brief Wrapping method.
 * @var method
 */
	Int32	method;

/**
 * @brief Wrapping flags.
 * @var flags
 */
	UInt32	flags;

};

/**
 * @brief Texture applying parameters. This structure is used in @ref API_LocalCoordsData.
 * @struct API_LocalCoordsType
 * @ingroup Element
 * @remarks See @ref ACAPI_Element_GetMemo to find out which element type needs/provides which information in the memo.
 */
struct API_LocalCoordsType {

/**
 * @brief Texturing method.
 * @var wrapping
 */
	API_Wrapping					wrapping;

/**
 * @brief The interpretation is dependent on the wrapping member.
 * @var c0
 */
	API_Coord3D						c0;

/**
 * @brief The interpretation is dependent on the wrapping member.
 * @var c1
 */
	API_Coord3D						c1;

/**
 * @brief The interpretation is dependent on the wrapping member.
 * @var c2
 */
	API_Coord3D						c2;

/**
 * @brief The interpretation is dependent on the wrapping member.
 * @var c3
 */
	API_Coord3D						c3;

};

/**
 * @brief Dynamic array of @ref API_LocalCoordsType items. This structure is used in @ref API_RoofSegmentData.
 * @struct API_LocalCoordsData
 * @ingroup Element
 */
struct API_LocalCoordsData {

/**
 * @brief Array of @ref API_LocalCoordsType items.
 * @var data
 */
	API_LocalCoordsType				*data;

/**
 * @brief Number of the records in the array.
 * @var nItems
 */
	Int32							nItems;

};

/**
 * @brief Describes various properties/parameters of a roof segment that can be separately adjusted. This structure is used in @ref API_PivotPolyEdgeData.
 * @struct API_RoofSegmentData
 * @ingroup Element
 */
struct API_RoofSegmentData {

/**
 * @brief Angle of the plane of the segment to the XY plane.
 * @var angle
 */
	double							angle;

/**
 * @brief Texture local coordinates data (see @ref API_LocalCoordsData).
 * @var lcoo
 */
	API_LocalCoordsData				lcoo;

/**
 * @brief Top material of the roof segment.
 * @var topMaterial
 */
	API_AttributeIndex				topMaterial;

/**
 * @brief Bottom material of the roof segment.
 * @var bottomMaterial
 */
	API_AttributeIndex				bottomMaterial;

/**
 * @brief Fill of the top surface.
 * @var coverFillType
 */
	API_AttributeIndex				coverFillType;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief Eaves' extension outside the pivot polygon.
 * @var eavesOverhang
 */
	double							eavesOverhang;

/**
 * @brief The type of Segment. (see @ref API_PolyRoofSegmentAngleTypeID)
 * @var angleType
 */
	API_PolyRoofSegmentAngleTypeID	angleType;

};

/**
 * @brief Complete polygon descriptor for polyroofs and shells. This structure is used in @ref API_ElementMemo.
 * @struct API_PivotPolyEdgeData
 * @ingroup Element
 */
struct API_PivotPolyEdgeData {

/**
 * @brief Unique identifier of the pivot polygon edge.
 * @var pivotEdgeUnId
 */
	UInt32							pivotEdgeUnId;

/**
 * @brief Reserved for later use.
 * @var filler1
 */
	Int32							filler1;

/**
 * @brief Array of @ref API_RoofSegmentData items.
 * @var levelEdgeData
 */
	API_RoofSegmentData				*levelEdgeData;

/**
 * @brief Number of items in the levelEdgeData array (indexed from 0).
 * @var nLevelEdgeData
 */
	Int32							nLevelEdgeData;

/**
 * @brief Arc decomposition method for polyroof pivot edges or revolved shells. (see @ref API_ShellBaseSegmentTypeID).
 * @var segmentType
 */
	API_ShellBaseSegmentTypeID		segmentType;

/**
 * @brief Cut the arc itself into segmentsByArc straight segments.
 * @var segmentsByArc
 */
	Int32							segmentsByArc;

/**
 * @brief Cut a whole circle to segmentsByCircle segments and use as many as necessary to cover the arc.
 * @var segmentsByCircle
 */
	Int32							segmentsByCircle;

};

/**
 * @brief This structure holds the Single-plane Roof specific data of @ref API_RoofType.
 * @struct API_PlaneRoofData
 * @ingroup Element
 * @remarks For roof related memo data see the @ref ACAPI_Element_GetMemo function.
 * 			In order to enumerate the planes of the Multi-plane Roof, use the @ref ACAPI_Element_Decompose function.
 */
struct API_PlaneRoofData {

/**
 * @brief Angle of the roof plane.
 * @var angle
 */
	double							angle;

/**
 * @brief The polygon of the roof slab, projected onto the horizontal plane.
 * @var poly
 */
	API_Polygon						poly;

/**
 * @brief Base (pivot) line of the roof.
 * @var baseLine
 */
	API_Sector						baseLine;

/**
 * @brief The sign of the vectorial product of the pivot line vector and the elevation indicator point (its value is 1 if the roof plane raises on the left side of the pivot line vector, otherwise 0).
 * @var posSign
 */
	bool							posSign;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[7];

};

/**
 * @brief This structure holds the Multi-plane Roof specific data of @ref API_RoofType.
 * @struct API_PolyRoofData
 * @ingroup Element
 * @remarks For roof related memo data see the @ref ACAPI_Element_GetMemo function.
 * 			In order to enumerate the planes of the Multi-plane Roof, use the @ref ACAPI_Element_Decompose function.
 */
struct API_PolyRoofData {

/**
 * @brief Fixed-size array of @ref API_RoofLevelData items.
 * @var levelData
 */
	API_RoofLevelData				levelData[16];

/**
 * @brief The actual number of levelData items (the maximum value is 16).
 * @var levelNum
 */
	short							levelNum;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;


/**
 * @brief Overhang value is calculated or manually set for each roof segment.
 * @var overHangType
 */
	API_RoofOverHangTypeID			overHangType;

/**
 * @brief Eaves' extension outside the pivot polygon.
 * @var eavesOverHang
 */
	double							eavesOverHang;


/**
 * @brief Curve resolution method: by circle or by arc.
 * @var segmentType
 */
	API_ShellBaseSegmentTypeID		segmentType;

/**
 * @brief Curve resolution value by arc.
 * @var segmentsByArc
 */
	Int32							segmentsByArc;

/**
 * @brief Curve resolution value by circle.
 * @var segmentsByCircle
 */
	Int32							segmentsByCircle;

/**
 * @brief Place Skylights tangentially to curved surfaces rather than parallel to the individual segments.
 * @var fitSkylightToCurve
 */
	bool							fitSkylightToCurve;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool							filler_2[3];


/**
 * @brief The polygon constructed from the pivot edges of the roof planes. The actual data of the pivot polygon is held in the pivotPolyCoords, pivotPolyPends, pivotPolyParcs, and pivotPolyVertexIDs members of the @ref API_ElementMemo structure.
 * @var pivotPolygon
 */
	API_Polygon						pivotPolygon;

/**
 * @brief The contour polygon that cuts the roof on the horizontal plane. The actual data is held in the coords, pends, parcs, and vertexIDs members of the @ref API_ElementMemo structure.
 * @var contourPolygon
 */
	API_Polygon						contourPolygon;

};

/**
 * @brief Represents a roof element.
 * @struct API_RoofType
 * @ingroup Element
 * @remarks For roof related memo data see the @ref ACAPI_Element_GetMemo function.
 * 			In order to enumerate the planes of the Multi-plane Roof, use the @ref ACAPI_Element_Decompose function.
 */
struct API_RoofType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;

/**
 * @brief Roof class:
 * 		  |API_RoofClassID value|Meaning|
 * 		  |--- |--- |
 * 		  |API_PlaneRoofID|Single-plane roof, use the API_PlaneRoofData member of the union|
 * 		  |API_PolyRoofID|Multi-plane roof, use the API_PolyRoofData member of the union|
 *
 * @var roofClass
 */
	API_RoofClassID					roofClass;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief Parameters common with all shell-based element types.
 * @var shellBase
 */
	API_ShellBaseType				shellBase;

/**
 * @brief Single-plane or Multi-plane roof specific data.
 * @var u
 */
	union {
		/**
		 * @brief Single-plane roof specific data.
		 * @var planeRoof
		 */
		API_PlaneRoofData			planeRoof;

		/**
		 * @brief Multi-plane roof specific data.
		 * @var polyRoof
		 */
		API_PolyRoofData			polyRoof;

	} u;
};


// -----------------------------------------------------------------------------
// Shell
// -----------------------------------------------------------------------------

/**
 * @brief Determines the type of the shell contour edge.
 * @enum API_ShellBaseContourEdgeTypeID
 * @ingroup Element
 */
typedef enum {
	APIShellBaseContour_Undefined = 0,
	APIShellBaseContour_Ridge,
	APIShellBaseContour_Valley,
	APIShellBaseContour_Gable,
	APIShellBaseContour_Hip,
	APIShellBaseContour_Eaves,
	APIShellBaseContour_Peak,
	APIShellBaseContour_SideWall,
	APIShellBaseContour_EndWall,
	APIShellBaseContour_RTDome,
	APIShellBaseContour_RTHollow

} API_ShellBaseContourEdgeTypeID;

/**
 * @brief Type of the morphing rule applied by the Ruled Shell.
 * @enum API_MorphingRuleID
 * @ingroup Element
 */
typedef enum {
	APIMorphingRule_Paired,
	APIMorphingRule_Smooth

} API_MorphingRuleID;

typedef enum {
	API_ExtrudedShellID,
	API_RevolvedShellID,
	API_RuledShellID
} API_ShellClassID;

/**
 * @brief Parameters of a shell contour edge.
 * @struct API_ContourEdgeData
 * @ingroup Element
 */
struct API_ContourEdgeData {

/**
 * @brief The edge trim data (see @ref API_EdgeTrim).
 * @var edgeTrim
 */
	API_EdgeTrim					edgeTrim;

/**
 * @brief Material override structure of the contour edge.
 * @var sideMaterial
 */
	API_OverriddenAttribute			sideMaterial;

/**
 * @brief Type of the contour edge (see @ref API_ShellBaseContourEdgeTypeID).
 * @var edgeType
 */
	API_ShellBaseContourEdgeTypeID	edgeType;

};

/**
 * @brief Contains the profile data of the Shell element. This structure is used in @ref API_ElementMemo.
 * @struct API_ShellShapeData
 * @ingroup Element
 * @remarks Shell shapes are actually polylines with some additional information.
 * 			For shell related memo data see the @ref ACAPI_Element_GetMemo function.
 */
struct API_ShellShapeData {

/**
 * @brief Coordinate array of the shape polyline.
 * @var coords
 */
	API_Coord						**coords;

/**
 * @brief Polyline endpoints; see @ref API_Polygon for more information.
 * @var pends
 */
	Int32							**pends;

/**
 * @brief Polyline arcs; see @ref API_PolyArc and @ref API_Polygon for more information.
 * @var parcs
 */
	API_PolyArc						**parcs;

/**
 * @brief Unique identifiers the polyline vertices (unique inside the polyline).
 * @var vertexIDs
 */
	UInt32							**vertexIDs;

/**
 * @brief Unique identifiers the polyline edges (unique inside the polyline).
 * @var edgeIDs
 */
	UInt32							**edgeIDs;

/**
 * @brief Flags for each edge. If the edge generates a surface (body when applying thickness) it is true. If the edge serves only to close the polyline, it is false. Normally for open polyline profiles all edge flags should be set to true, for closed polyline profiles only the last edge flag should be set to false.
 * @var bodyFlags
 */
	bool							**bodyFlags;

};

/**
 * @brief Shell contour or shell hole contour definition. This structure is used in @ref API_ElementMemo.
 * @struct API_ShellContourData
 * @ingroup Element
 * @remarks This structure describes the data for the clipping polygon contour (in this case the height and id members are irrelevant), and the hole contours of a shell element.
 */
struct API_ShellContourData {

/**
 * @brief The dimensions of the variable size polygon data (see @ref API_Polygon).
 * @var poly
 */
	API_Polygon						poly;

/**
 * @brief Coordinate array.
 * @var coords
 */
	API_Coord						**coords;

/**
 * @brief Polygon endpoints; see @ref API_Polygon for more information.
 * @var pends
 */
	Int32							**pends;

/**
 * @brief Polygon arcs; see @ref API_PolyArc and @ref API_Polygon for more information.
 * @var parcs
 */
	API_PolyArc						**parcs;

/**
 * @brief Unique identifiers the polygon vertices (unique inside the polygon).
 * @var vertexIDs
 */
	UInt32							**vertexIDs;

/**
 * @brief Unique identifiers the polygon edges (unique inside the polygon).
 * @var edgeIDs
 */
	UInt32							**edgeIDs;

/**
 * @brief Unique identifiers the polygon contours (unique inside the polygon).
 * @var contourIDs
 */
	UInt32							**contourIDs;

/**
 * @brief Data associated to the edges of the contour polygon (see @ref API_ContourEdgeData).
 * @var edgeData
 */
	API_ContourEdgeData				*edgeData;

/**
 * @brief The contour polygon lies on this plane. The coordinates are given in its 2D coordinate system.
 * @var plane
 */
	API_Tranmat						plane;

/**
 * @brief Height (depth) of the cutting body extruded from the hole polygon. Always 0 for the outside contour.
 * @var height
 */
	double							height;

/**
 * @brief Id of the hole polygon. Always 0 for the outside contour.
 * @var id
 */
	UInt32							id;

};

/**
 * @brief This structure holds the Extruded Shell specific data of @ref API_ShellType.
 * @struct API_ExtrudedShellData
 * @ingroup Element
 * @remarks For shell related memo data see the @ref ACAPI_Element_GetMemo function.
 */
struct API_ExtrudedShellData {

/**
 * @brief Angle of the extrusion vector from the horizontal plane.
 * @var slantAngle
 */
	double							slantAngle;

/**
 * @brief Parameter of the plane of the extruded profile.
 * @var shapePlaneTilt
 */
	double							shapePlaneTilt;

/**
 * @brief Parameter of the starting plane of the extrusion.
 * @var begPlaneTilt
 */
	double							begPlaneTilt;

/**
 * @brief Parameter of the end plane of the extrusion.
 * @var endPlaneTilt
 */
	double							endPlaneTilt;


/**
 * @brief Profile polygon specification to extrude. The shape data arrays are held in the first @ref API_ShellShapeData record of shellShapes in @ref API_ElementMemo.
 * @var shellShape
 */
	API_Polygon						shellShape;

/**
 * @brief Start the extrusion from here (3D point).
 * @var begC
 */
	API_Coord3D						begC;

/**
 * @brief Extrude the profile in this direction (3D vector).
 * @var extrusionVector
 */
	API_Vector3D					extrusionVector;

/**
 * @brief Direction of the profile (2D vector).
 * @var shapeDirection
 */
	API_Vector						shapeDirection;

/**
 * @brief Edge information for the starting plane of the shell
 * @var begShapeEdgeData
 */
	API_ContourEdgeData				begShapeEdgeData;

/**
 * @brief Edge information for the end plane of the shell
 * @var endShapeEdgeData
 */
	API_ContourEdgeData				endShapeEdgeData;

/**
 * @brief Edge information for the edges connecting points of the starting and end plane.
 * @var extrudedEdgeDatas
 */
	API_ContourEdgeData				extrudedEdgeDatas[2];

};

/**
 * @brief This structure holds the Revolved Shell specific data of @ref API_ShellType.
 * @struct API_RevolvedShellData
 * @ingroup Element
 * @remarks For shell related memo data see the @ref ACAPI_Element_GetMemo function.
 */
struct API_RevolvedShellData {

/**
 * @brief Relative to the plane (radians).
 * @var slantAngle
 */
	double							slantAngle;

/**
 * @brief Angle of view (in radians).
 * @var revolutionAngle
 */
	double							revolutionAngle;

/**
 * @brief Angle of shear (radians).
 * @var distortionAngle
 */
	double							distortionAngle;

/**
 * @brief The surface generated by revolving the profile is broken into planes along the revolution arc.
 * @var segmentedSurfaces
 */
	bool							segmentedSurfaces;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[3];

/**
 * @brief Curve resolution method: by circle or by arc.
 * @var segmentType
 */
	API_ShellBaseSegmentTypeID		segmentType;

/**
 * @brief Number of actual segments if segmentType is @c APIShellBase_SegmentsByArc.
 * @var segmentsByArc
 */
	Int32							segmentsByArc;

/**
 * @brief Number of actual segments if segmentType is @c APIShellBase_SegmentsByCircle.
 * @var segmentsByCircle
 */
	Int32							segmentsByCircle;


/**
 * @brief Profile polygon specification to revolve. The shape data arrays are held in the first @ref API_ShellShapeData record of shellShapes in @ref API_ElementMemo.
 * @var shellShape
 */
	API_Polygon						shellShape;

/**
 * @brief Coord System of axis.
 * @var axisBase
 */
	API_Tranmat						axisBase;

/**
 * @brief Direction of shear (in axisBase x-y plane)..
 * @var distortionVector
 */
	API_Vector						distortionVector;

/**
 * @brief edge information for the starting plane of the shell
 * @var begShapeEdgeData
 */
	API_ContourEdgeData				begShapeEdgeData;

/**
 * @brief edge information for the end plane of the shell
 * @var endShapeEdgeData
 */
	API_ContourEdgeData				endShapeEdgeData;

/**
 * @brief edge information for the edges connecting points of the starting and end plane.
 * @var revolvedEdgeDatas
 */
	API_ContourEdgeData				revolvedEdgeDatas[2];

/**
 * @brief Begin angle.
 * @var begAngle
 */
	double							begAngle;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool							filler_2[8];

};

/**
 * @brief This structure holds the Ruled Shell specific data of @ref API_ShellType.
 * @struct API_RuledShellData
 * @ingroup Element
 * @remarks For shell related memo data see the @ref ACAPI_Element_GetMemo function.
 */
struct API_RuledShellData {

/**
 * @brief Specification of the first profile polygon. The shape data arrays are held in the first @ref API_ShellShapeData record of shellShapes in @ref API_ElementMemo.
 * @var shellShape1
 */
	API_Polygon						shellShape1;

/**
 * @brief Plane of the first profile.
 * @var plane1
 */
	API_Tranmat						plane1;

/**
 * @brief Specification of the second profile polygon. The shape data arrays are held in the second @ref API_ShellShapeData record of shellShapes in @ref API_ElementMemo..
 * @var shellShape2
 */
	API_Polygon						shellShape2;

/**
 * @brief Plane of the second profile.
 * @var plane2
 */
	API_Tranmat						plane2;

/**
 * @brief Edge information for the starting plane of the shell.
 * @var begShapeEdgeData
 */
	API_ContourEdgeData				begShapeEdgeData;

/**
 * @brief Edge information for the end plane of the shell.
 * @var endShapeEdgeData
 */
	API_ContourEdgeData				endShapeEdgeData;

/**
 * @brief Edge information for the edges connecting points of the starting and end plane.
 * @var ruledEdgeDatas
 */
	API_ContourEdgeData				ruledEdgeDatas[2];

/**
 * @brief Morphing method for shape generation: paired segments or smooth.
 * @var morphingRule
 */
	API_MorphingRuleID				morphingRule;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[4];

};

/**
 * @brief Represents a shell element.
 * @struct API_ShellType
 * @ingroup Element
 * @remarks For shell related memo data see the @ref ACAPI_Element_GetMemo function.
 */
struct API_ShellType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;


/**
 * @brief Shell class:
 * 		  |API_ShellClassID value|Meaning|
 * 		  |--- |--- |
 * 		  |API_ExtrudedShellID|Extruded shell type, use the `API_ExtrudedShellData` member of the union|
 * 		  |API_RevolvedShellID|Revolved shell type, use the `API_RevolvedShellData` member of the union|
 * 		  |API_RuledShellID|Ruled shell type, use the API_RuledShellData member of the union|
 *
 * @var shellClass
 */
	API_ShellClassID				shellClass;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;


/**
 * @brief Parameters common with all shell-based element types.
 * @var shellBase
 */
	API_ShellBaseType				shellBase;


/**
 * @brief Base plane of the shell element.
 * @var basePlane
 */
	API_Tranmat						basePlane;

/**
 * @brief It tells what way (inside or out) the thickness must be applied from the shell's surfaces.
 * @var isFlipped
 */
	bool							isFlipped;

/**
 * @brief The shell has body contour data. If the shell is cut with a body contour polygon, the data of the contour is stored in the first (0-indexed) record of the shellContours array of @ref API_ElementMemo.
 * @var hasContour
 */
	bool							hasContour;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	short							filler_2;

/**
 * @brief Number of the shell hole contours. The data of the hole contours are stored in the shellContours array of @ref API_ElementMemo, starting after the body contour if there is one, or from the first record if no body contour is given.
 * @var numHoles
 */
	UInt32							numHoles;

/**
 * @brief Default edge type for the shell element (see @ref API_ShellBaseContourEdgeTypeID).
 * @var defEdgeType
 */
	API_ShellBaseContourEdgeTypeID	defEdgeType;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3;

/**
 * @brief Extruded, Revolved or Ruled Shell-specific data.
 * @var u
 */
	union {
		/**
		 * @brief Extruded Shell-specific data.
		 * @var extrudedShell
		 */
		API_ExtrudedShellData		extrudedShell;

		/**
		 * @brief Revolved Shell-specific data.
		 * @var revolvedShell
		 */
		API_RevolvedShellData		revolvedShell;

		/**
		 * @brief Ruled Shell-specific data.
		 * @var ruledShell
		 */
		API_RuledShellData			ruledShell;

	} u;
};


// -----------------------------------------------------------------------------
// Morph
// -----------------------------------------------------------------------------


/**
 * @brief Determines the type of the texture projection.
 * @enum API_TextureProjectionTypeID
 * @ingroup Element
 */
typedef enum {
	APITextureProjectionType_Invalid		= 0,
	APITextureProjectionType_Planar			= 1,
	APITextureProjectionType_Default		= 2,
	APITextureProjectionType_Cylindric		= 3,
	APITextureProjectionType_Spheric		= 4,
	APITextureProjectionType_Box			= 5

} API_TextureProjectionTypeID;

/**
 * @brief Determines the type of the morph body.
 * @enum API_MorphBodyTypeID
 * @ingroup Element
 */
typedef enum {
	APIMorphBodyType_SurfaceBody,
	APIMorphBodyType_SolidBody

} API_MorphBodyTypeID;

/**
 * @brief Determines the type of the morph edge.
 * @enum API_MorphEdgeTypeID
 * @ingroup Element
 */
typedef enum {
	APIMorphEdgeType_SoftHiddenEdge,
	APIMorphEdgeType_HardHiddenEdge,
	APIMorphEdgeType_HardVisibleEdge

} API_MorphEdgeTypeID;

/**
 * @brief Represents a morph element.
 * @struct API_MorphType
 * @ingroup Element
 * @remarks  The elements' cut fill foreground and background pens inherit from the building material, and can be overridden on the element level.
 * 			 The elements' surface materials inherit from the building material, and can be overridden on the element level.
 * 			 For morph related memo data see the @ref ACAPI_Element_GetMemo function.
 * 			 For mesh related memo data see the @ref ACAPI_Element_GetMemo function.
 * 			 The elements' surface materials inherit from the building material, and can be overridden on the element level.
 * 			 For morph related memo data see the @ref ACAPI_Element_GetMemo function.
 */
struct API_MorphType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head						head;


/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	char								filler_1[16];

/**
 * @brief Is Auto On Story Visibility.
 * @var isAutoOnStoryVisibility
 */
	bool								isAutoOnStoryVisibility;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool								filler_2[7];

/**
 * @brief The option to define which stories display the contour of the morph.
 * @var showContour
 */
	API_StoryVisibility					showContour;

/**
 * @brief The option to define which stories display the fill of the morph.
 * @var showFill
 */
	API_StoryVisibility					showFill;


/**
 * @brief Mode of linking to home story.
 * @var linkToSettings
 */
	API_LinkToSettings					linkToSettings;

/**
 * @brief Display options of the element on the floor plan (see @ref API_ElemDisplayOptionsID).
 * @var displayOption
 */
	API_ElemDisplayOptionsID			displayOption;

/**
 * @brief Defines the range within the element is shown on the floor plan (see @ref API_ElemViewDepthLimitationsID).
 * @var viewDepthLimitation
 */
	API_ElemViewDepthLimitationsID		viewDepthLimitation;

/**
 * @brief Building Material index of morph's hatch.
 * @var buildingMaterial
 */
	API_AttributeIndex					buildingMaterial;

/**
 * @brief Cut fill pens set in the building material can be overridden on the element level.
 * @var cutFillPen
 */
	API_OverriddenPen					cutFillPen;

/**
 * @brief Cut fill pens set in the building material can be overridden on the element level.
 * @var cutFillBackgroundPen
 */
	API_OverriddenPen					cutFillBackgroundPen;

/**
 * @brief Line Type of the cut contour.
 * @var cutLineType
 */
	API_AttributeIndex					cutLineType;

/**
 * @brief Pen of the cut contour.
 * @var cutLinePen
 */
	short								cutLinePen;

/**
 * @brief Pen of the contour.
 * @var uncutLinePen
 */
	short								uncutLinePen;

/**
 * @brief Line Type of the contour.
 * @var uncutLineType
 */
	API_AttributeIndex					uncutLineType;

/**
 * @brief Line Type of view above (Floor plan only).
 * @var overheadLineType
 */
	API_AttributeIndex					overheadLineType;

/**
 * @brief Pen of view above (Floor plan only).
 * @var overheadLinePen
 */
	short								overheadLinePen;

/**
 * @brief Use Floor plan fill.
 * @var useCoverFillType
 */
	bool								useCoverFillType;

/**
 * @brief Outline Contour Display.
 * @var outlineContourDisplay
 */
	bool								outlineContourDisplay;

/**
 * @brief Floor plan fill type.
 * @var coverFillType
 */
	API_AttributeIndex					coverFillType;

/**
 * @brief Floor plan fill pen.
 * @var coverFillPen
 */
	short								coverFillPen;

/**
 * @brief Floor plan fill background pen.
 * @var coverFillBGPen
 */
	short								coverFillBGPen;

/**
 * @brief Floor plan fill from material.
 * @var use3DHatching
 */
	bool								use3DHatching;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	bool								filler_3[3];

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	Int32								filler_4[8];

/**
 * @brief Floor plan local origo type of fill.
 * @var coverFillOrientation
 */
	API_HatchOrientation				coverFillOrientation;

/**
 * @brief Show hatching as projected onto a plane.
 * @var useDistortedCoverFill
 */
	bool								useDistortedCoverFill;

/**
 * @brief Reserved for later use.
 * @var filler_5
 */
	bool								filler_5[5];

/**
 * @brief Material override structure of non customized surfaces.
 * @var material
 */
	API_OverriddenAttribute				material;

/**
 * @brief Projection type of texture.
 * @var textureProjectionType
 */
	API_TextureProjectionTypeID			textureProjectionType;

/**
 * @brief Reserved for later use.
 * @var filler_6
 */
	Int32								filler_6[21];

/**
 * @brief Texture projection coordinate system.
 * @var textureProjectionCoords
 */
	API_Coord3D							textureProjectionCoords[4];


/**
 * @brief Z position of the free shape.
 * @var level
 */
	double								level;

/**
 * @brief Type of the body (Solid, Surface).
 * @var bodyType
 */
	API_MorphBodyTypeID					bodyType;

/**
 * @brief Type of the edge (Soft, Sharp).
 * @var edgeType
 */
	API_MorphEdgeTypeID					edgeType;

/**
 * @brief Body casts shadow.
 * @var castShadow
 */
	bool								castShadow;

/**
 * @brief Body receives shadow.
 * @var receiveShadow
 */
	bool								receiveShadow;

/**
 * @brief Reserved for later use.
 * @var filler_7
 */
	bool								filler_7[6];

/**
 * @brief Reserved for later use.
 * @var filler_8
 */
	Int32								filler_8[18];

/**
 * @brief Tranmat of the morph element.
 * @var tranmat
 */
	API_Tranmat							tranmat;

/**
 * @brief Reserved for later use.
 * @var filler_9
 */
	bool								filler_9[8];

};


// =============================================================================
// Mesh
//
// =============================================================================

#define APIRidge_AllSharp			0
#define APIRidge_AllSmooth			1
#define APIRidge_UserSharp			2

/**
 * @brief Describes one coordinate of a mesh level line.
 * @struct API_MeshLevelCoord
 * @ingroup Element
 */
struct API_MeshLevelCoord {

/**
 * @brief The 3D coordinate of the vertex.
 * @var c
 */
	API_Coord3D						c;

/**
 * @brief Vertex ID unique in the given mesh; can be used to track the vertices.
 * @var vertexID
 */
	Int32							vertexID;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	Int32							filler_0;

};

/**
 * @brief Defines the level lines of a mesh.
 * @struct API_MeshLevel
 * @ingroup Element
 * @remarks This structure should be used in conjunction with the meshLevelCoords and meshLevelEnds fields of @ref API_ElementMemo. The meshLevelCoords field defines the coordinates of the level line points; while meshLevelEnds field contains the indices of the end points of each level line in the meshLevelCoords array.
 */
struct API_MeshLevel {

/**
 * @brief Number of vertices in the level lines.
 * @var nCoords
 */
	Int32							nCoords;

/**
 * @brief Number of sublines including the first one.
 * @var nSubLines
 */
	Int32							nSubLines;

};

/**
 * @brief Represents a mesh.
 * @struct API_MeshType
 * @ingroup Element
 * @remarks  The elements' cut fill foreground and background pens inherit from the building material, and can be overridden on the element level.
 * 			 The elements' surface materials inherit from the building material, and can be overridden on the element level.
 * 			 For morph and mesh related memo data see the @ref ACAPI_Element_GetMemo function.
 * 			 The elements' surface materials inherit from the building material, and can be overridden on the element level.
 * 			 For morph related memo data see the @ref ACAPI_Element_GetMemo function.
 */
struct API_MeshType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;


/**
 * @brief Pen attribute index of the mesh's contour.
 * @var contPen
 */
	short							contPen;

/**
 * @brief Pen attribute index of the mesh's level lines.
 * @var levelPen
 */
	short							levelPen;

/**
 * @brief Line type attribute index of mesh's contour.
 * @var ltypeInd
 */
	API_AttributeIndex				ltypeInd;

/**
 * @brief Building Material index of mesh's hatch.
 * @var buildingMaterial
 */
	API_AttributeIndex				buildingMaterial;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1[2];

/**
 * @brief Cut fill pens set in the building material can be overridden on the element level.
 * @var cutFillPen
 */
	API_OverriddenPen				cutFillPen;

/**
 * @brief Cut fill pens set in the building material can be overridden on the element level.
 * @var cutFillBackgroundPen
 */
	API_OverriddenPen				cutFillBackgroundPen;

/**
 * @brief Contour pen attribute index of the mesh 's fill in sections.
 * @var sectContPen
 */
	short							sectContPen;

/**
 * @brief Top material attribute override structure.
 * @var topMat
 */
	API_OverriddenAttribute			topMat;

/**
 * @brief Side material attribute override structure.
 * @var sideMat
 */
	API_OverriddenAttribute			sideMat;

/**
 * @brief Bottom material attribute override structure.
 * @var botMat
 */
	API_OverriddenAttribute			botMat;

/**
 * @brief Are surface materials chained?
 * @var materialsChained
 */
	bool							materialsChained;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool							filler_2;

/**
 * @brief Use cover fill?
 * @var useFloorFill
 */
	bool							useFloorFill;

/**
 * @brief How the connecting surfaces to be shown in the PhotoRendering window:
 * 		  |APIRidge_AllSharp|All ridges sharp|
 * 		  |APIRidge_AllSmooth|All ridges smooth|
 * 		  |APIRidge_UserSharp|Only the user defined ridges are sharp|
 * @var smoothRidges
 */
	char							smoothRidges;

/**
 * @brief False : hide secondary lines; true : show everything.
 * @var showLines
 */
	short							showLines;

/**
 * @brief Skirt: 1 = yes; 2 = no bottom; 3 = no.
 * @var skirt
 */
	short							skirt;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	short							filler_3[2];

/**
 * @brief Height of base plane of the mesh from the floor level.
 * @var level
 */
	double							level;

/**
 * @brief Distance of the mesh's bottom from the base plane of the mesh.
 * @var skirtLevel
 */
	double							skirtLevel;

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	char							filler_4[16];

/**
 * @brief Visibility of mesh's contour line. On the element's own story the contour should allways be visible.
 * @var visibilityCont
 */
	API_StoryVisibility				visibilityCont;

/**
 * @brief Visibility of mesh's cover fill.
 * @var visibilityFill
 */
	API_StoryVisibility				visibilityFill;

/**
 * @brief Mode of linking to home story.
 * @var linkToSettings
 */
	API_LinkToSettings				linkToSettings;

/**
 * @brief Pen attribute index of mesh's cover fill.
 * @var floorFillPen
 */
	short							floorFillPen;

/**
 * @brief Background pen attribute index of the mesh's cover fill.
 * @var floorFillBGPen
 */
	short							floorFillBGPen;

/**
 * @brief Fill attribute index of the mesh's cover fill.
 * @var floorFillInd
 */
	API_AttributeIndex				floorFillInd;

/**
 * @brief Use local origo for cover fill drawing?
 * @var useLocalOrigo
 */
	bool							useLocalOrigo;

/**
 * @brief Reserved for internal use.
 * @var use3DHatching
 */
	bool							use3DHatching;

/**
 * @brief Reserved for later use.
 * @var filler_5
 */
	short							filler_5;


/**
 * @brief The polygon of the mesh.
 * @var poly
 */
	API_Polygon						poly;

/**
 * @brief Reserved for later use.
 * @var filler_6
 */
	Int32							filler_6;

/**
 * @brief The level lines of the mesh.
 * @var levelLines
 */
	API_MeshLevel					levelLines;

/**
 * @brief Base coordinate of mesh's cover fill reference vector if it's linked to the element.
 * @var locOrigo
 */
	API_Coord						locOrigo;

/**
 * @brief Angle of mesh's cover fill reference vector if it's linked to the element.
 * @var fillAngle
 */
	double							fillAngle;

/**
 * @brief Reserved for later use.
 * @var filler_7
 */
	Int32							filler_7[2];

/**
 * @brief Reserved for later use.
 * @var filler_8
 */
	bool							filler_8[8];

};


// =============================================================================
// Dimension
//
// =============================================================================

/**
 * @brief Describes the various appearance options for witness lines.
 * @enum API_WitnessID
 * @ingroup Element
 */
typedef enum {
	APIWtn_None,
	APIWtn_Small,
	APIWtn_Large,
	APIWtn_Fix

} API_WitnessID;

/**
 * @brief Describes the various options for the appearance of the dimensions.
 * @enum API_AppearID
 * @ingroup AutoText
 */
typedef enum {
	APIApp_Normal,
	APIApp_Cumu,
	APIApp_CumuSv,
	APIApp_Elev

} API_AppearID;

/**
 * @brief Describes the various options for dimension text positioning.
 * @enum API_TextPosID
 * @ingroup Element
 */
typedef enum {
	APIPos_Above,
	APIPos_In,
	APIPos_Below

} API_TextPosID;

/**
 * @brief Defines various orientations for dimension and label texts.
 * @enum API_DirID
 * @ingroup Element
 */
typedef enum {
	APIDir_Parallel,
	APIDir_Horizontal,
	APIDir_Vertical,
	APIDir_General,
	APIDir_Radial,
	APIDir_ArcDim,
	APIDir_Perpendicular

} API_DirID;

/**
 * @brief Describes the various types of dimension markers.
 * @enum API_MarkerID
 * @ingroup Element
 */
typedef enum {
	APIMark_CrossLine,											// Small vertical line (smallWitness)
	APIMark_EmptyCirc,											// Empty Circle
	APIMark_SlashLine,											// 60deg Slash Line
	APIMark_OpenArrow30,										// 30deg opened arrow
	APIMark_ClosArrow30,										// 30deg closed arrow (triangle)
	APIMark_FullArrow30,										// 30deg filled arrow
	APIMark_SlashLine45,										// 45deg Slash Line
	APIMark_CrossCirc,											// Crossline + EmptyCirc
	APIMark_OpenArrow90,										// 90deg opened arrow
	APIMark_ClosArrow90,										// 90deg closed arrow (triangle)
	APIMark_FullArrow90,										// 90deg filled arrow
	APIMark_FullCirc,											// Filled Circle
	APIMark_PepitaCirc,											// Pepita Circle, like a LevDim
	APIMark_BandArrow,											// Lane arrow (double line)
	APIMark_OpenArrow60,										// 60deg opened arrow
	APIMark_ClosArrow60,										// 60deg closed arrow (triangle)
	APIMark_FullArrow60,										// 60deg filled arrow
	APIMark_SlashLine75											// 75deg Slash Line

} API_MarkerID;

/**
 * @brief Describes the elevation dimension origin.
 * @enum API_DimOriginID
 * @ingroup Element
 */
typedef enum {
	APIDimOrigin_ProjectZero,
	APIDimOrigin_RefLevel1,
	APIDimOrigin_RefLevel2,
	APIDimOrigin_StoredOrigin,
	APIDimOrigin_Altitude

} API_DimOriginID;

/**
 * @brief Describes the various parameters of dimension markers.
 * @struct API_MarkerData
 * @ingroup Element
 */
struct API_MarkerData {

/**
 * @brief Marker type.
 * @var markerType
 */
	API_MarkerID					markerType;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief Pen attribute index for the marker.
 * @var markerPen
 */
	short							markerPen;

/**
 * @brief In scaled drawing size (in mm).
 * @var markerSize
 */
	double							markerSize;

};

/**
 * @brief The base of a non-static linear, angle or radial dimension element.
 * @struct API_Base
 * @ingroup Element
 * @since Archicad 26
 * @remarks From version 26 the type of the typeID member was changed into @ref API_ElemType.
 */
struct API_Base {

/**
 * @brief The type of the base element.
 * @var type
 */
	API_ElemType					type;

/**
 * @brief True in case of @c APINeig_WallOn, @c APINeig_WallPlOn, @c APINeig_BeamOn, @c APINeig_CeilOn, @c APINeig_RoofOn, @c APINeig_MeshOn, @c APINeig_HatchOn, @c APINeig_LineOn, @c APINeig_ArcOn, @c APINeig_SplineOn
 * @var line
 */
	bool							line;

/**
 * @brief True in case of @c APINeig_WallPl, @c APINeig_WallPlOn, @c APINeig_BeamHole, @c APINeig_WindHole, @c APINeig_DoorHole, @c APINeig_MeshRidge, @c APINeig_MeshRidgeOn
 * @var special
 */
	char							special;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2;

/**
 * @brief InIndex of the base element's node (see @ref API_Neig).
 * @var inIndex
 */
	Int32							inIndex;

/**
 * @brief The unique identifier of the base element.
 * @var guid
 */
	API_Guid						guid;

// Section-specific data

/**
 * @brief Polygon vertex id (from the @ref API_ElementMemo of the elements which have a polygon).
 * @var node_id
 */
	UInt32							node_id;

/**
 * @brief For internal use (reserved for section dim).
 * @var node_status
 */
	short							node_status;

/**
 * @brief For internal use (reserved for section dim).
 * @var node_typ
 */
	short							node_typ;

};

/**
 * @brief Describes the base element for dimensioning.
 * @struct API_DimBase
 * @ingroup Element
 */
struct API_DimBase {

/**
 * @brief The base element.
 * @var base
 */
	API_Base						base;

/**
 * @brief Location of the dimension line.
 * @var loc
 */
	API_Coord						loc;

/**
 * @brief Coordinate of the base point in 3D (see @ref API_Coord3D).
 * @var loc3D
 */
	API_Coord3D						loc3D;

};

/**
 * @brief Describes a dimension element.
 * @struct API_DimElem
 * @ingroup Element
 */
struct API_DimElem {

/**
 * @brief The dimensioned point.
 * @var base
 */
	API_DimBase						base;

/**
 * @brief Parameters of the dimension text.
 * @var note
 */
	API_NoteType					note;

/**
 * @brief Gap (APIWtn_Fix) or length (APIWtn_Large) of witness line according to witnessForm.
 * @var witnessVal
 */
	double							witnessVal;

/**
 * @brief Witness line format (see @ref API_WitnessID).
 * @var witnessForm
 */
	API_WitnessID					witnessForm;

/**
 * @brief Fixed position (pos needed for calculation in this case only)
 * @var fixedPos
 */
	bool							fixedPos;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	short							filler_2;

/**
 * @brief Position of Dimension.
 * @var pos
 */
	API_Coord						pos;

/**
 * @brief Distance from previous DimElem (output only).
 * @var dimVal
 */
	double							dimVal;

/**
 * @brief Corresponding coordinate on the dimension line in 3D.
 * @var pos3D
 */
	API_Coord3D						pos3D;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3[6];

};


/**
 * @brief Describes the layouting algorithm of the dimension.
 * @enum API_DimLayoutID
 * @ingroup Element
 */
typedef enum {
	API_Legacy						= 0,
	API_Flexible,
	API_Centered,
	API_LayoutOff

} API_DimLayoutID;

/**
 * @brief Describe the circle style marker fill type of elevation dimension.
 * @enum API_CircleLevelDimensionFillID
 * @ingroup Element
 */
typedef enum {
	API_EmptyFill,
	API_NorthwestBlack,
	API_NortheastBlack

} API_CircleLevelDimensionFillID;

/**
 * @brief Describes the drawing order of the text's fill and contour relative to the dimension line.
 * @enum API_DimTextFillOrderID
 * @ingroup Element
 * @since Archicad 26
 */
enum class API_DimTextFillOrderID {
	FillAndContourUnderDimLine,
	FillAndContourAboveDimLine

};

/**
 * @brief Describes a (linear) dimension.
 * @struct API_DimensionType
 * @ingroup Element
 * @since Archicad 26
 * @remarks For dimension related memo data see the @ref ACAPI_Element_GetMemo function.
 */
struct API_DimensionType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;


/**
 * @brief Pen attribute index of dimension and witness lines.
 * @var linPen
 */
	short							linPen;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief Dimension text position (see `API_TextPosID`).
 * @var textPos
 */
	API_TextPosID					textPos;

/**
 * @brief The position of the text relative to the dimension line (see `API_DirID`). The possible values are:
 * 		  `@ref APIDir_Parallel`, `APIDir_Horizontal`, `APIDir_Vertical`, `APIDir_ArcDim`.
 * @var textWay
 */
	API_DirID						textWay;

/**
 * @brief Appearance of the dimension (see `API_AppearID`).
 * @var dimAppear
 */
	API_AppearID					dimAppear;

/**
 * @brief Detailed door/window dimension.
 * @var detailedHoleDim
 */
	bool							detailedHoleDim;

/**
 * @brief Nominal height for door/window dimension.
 * @var nominalHoleDim
 */
	char							nominalHoleDim;

/**
 * @brief Dimension type bits of composite walls (totalBit = 1; coreBit = 2; refLineBit = 4; manualBit	= 16;).
 * @var compAutoThick
 * @image html CompAutoThick.png width=25%
 */
	char							compAutoThick;

/**
 * @brief Static dimension (default)?
 * @var defStaticDim
 */
	bool							defStaticDim;

/**
 * @brief Default witness line format (see `API_WitnessID`).
 * @var defWitnessForm
 */
	API_WitnessID					defWitnessForm;

/**
 * @brief Default gap (`APIWtn_Fix`) or length (`APIWtn_Large`) of witness line according to`defWitnessForm`.
 * @var defWitnessVal
 */
	double							defWitnessVal;

/**
 * @brief Default note parameters (see @ref API_NoteType).
 * @var defNote
 */
	API_NoteType					defNote;

/**
 * @brief Marker specification (see @ref API_MarkerData).
 * @var markerData
 */
	API_MarkerData					markerData;

/**
 * @brief Elevation dimension marker type.
 * @var ed_dimForm
 */
	char							ed_dimForm;

/**
 * @brief Elevation dimension half-arrow angle:
 * 		  | Value | Degree |
 * 		  |-------|--------|
 * 		  | 0 | 30 degrees |
 * 		  | 1 | 45 degrees |
 * 		  | 2 | 60 degrees |
 * @var ed_arrowAng
 */
	char							ed_arrowAng;

/**
 * @brief Elevation dimension arrow is filled or not.
 * @var ed_arrowFill
 */
	bool							ed_arrowFill;

/**
 * @brief Elevation dimension arrow is up/down.
 * @var ed_arrowUp
 */
	bool							ed_arrowUp;

/**
 * @brief Elevation dimension plus sign needed for positive numbers.
 * @var ed_needPlus
 */
	bool							ed_needPlus;

/**
 * @brief Used for dimensioning 3D points.
 * @var usedIn3D
 */
	bool							usedIn3D;

/**
 * @brief Dimension texts are horizontal.
 * @var horizontalText
 */
	bool							horizontalText;

/**
 * @brief Only dimension texts (notes) are visible &mdash; no leader line.
 * @var onlyDimensionText
 */
	bool							onlyDimensionText;

/**
 * @brief Elevation dimension origin
 * @var ed_origin
 */
	API_DimOriginID					ed_origin;

/**
 * @brief Elevation dimension: the circle style marker fill.
 * @var ed_circleLevelDimensionFill
 */
	API_CircleLevelDimensionFillID	ed_circleLevelDimensionFill;

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	Int32							filler_4[4];

/**
 * @brief Dimension line location.
 * @var refC
 */
	API_Coord						refC;

/**
 * @brief Direction of the dimension line if parallel.
 * @var direction
 */
	API_Vector						direction;

/**
 * @brief Neig unique ID of the base element for an arc dimension chain.
 * @var arcBase
 */
	API_DimBase						arcBase;

/**
 * @brief Number of segments in dimension elements' chain (see @ref API_ElementMemo)
 * @var nDimElem
 */
	Int32							nDimElem;

/**
 * @brief Reserved for later use.
 * @var filler_5
 */
	Int32							filler_5;

/**
 * @brief Position of the dimension chain (used only in 3D).
 * @var refC3D
 */
	API_Coord3D						refC3D;

/**
 * @brief Direction of the dimension line (used only in 3D).
 * @var direction3D
 */
	API_Vector3D					direction3D;

/**
 * @brief Dimension plane's normal vector (used only in 3D).
 * @var normVect3D
 */
	API_Vector3D					normVect3D;

/**
 * @brief Layouting algorithm used by the dimension.
 * @var dimLayout
 */
	API_DimLayoutID					dimLayout;

/**
 * @brief Enable a note to push its neighbours (In case of `API_Flexible` layouting algorithm).
 * @var pushNeighborEnabled
 */
	bool							pushNeighborEnabled;

/**
 * @brief Try to place a note under the dimension line (In case of `API_Flexible` layouting algorithm).
 * @var placeUnderEnabled
 */
	bool							placeUnderEnabled;

/**
 * @brief Use advanced logic (In case of `API_Centered` layouting algorithm).
 * @var advanced
 */
	bool							advanced;

/**
 * @brief No witness line part on the other side (opposite to basepoint).
 * @var clipOtherSide
 */
	bool							clipOtherSide;

/**
 * @brief Drawing order of the text's fill and contour relative to the dimension line.
 * @var textFillOrder
 */
	API_DimTextFillOrderID			textFillOrder;

};


// =============================================================================
// Radial Dimension
//
// =============================================================================

/**
 * @brief Represents a radial dimension.
 * @struct API_RadialDimensionType
 * @ingroup Element
 */
struct API_RadialDimensionType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;


/**
 * @brief Pen attribute index of dimension and witness lines.
 * @var linPen
 */
	short							linPen;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief Dimension text position (see @ref API_TextPosID).
 * @var textPos
 */
	API_TextPosID					textPos;

/**
 * @brief The position of the text relative to the dimension line (see @ref API_DirID). The possible values are: @c APIDir_Horizontal, @c APIDir_Vertical, @c APIDir_Radial.
 * @var textWay
 */
	API_DirID						textWay;

/**
 * @brief Show arc's origin.
 * @var showOrigo
 */
	bool							showOrigo;

/**
 * @brief Only dimension texts (notes) are visible &mdash; no leader line.
 * @var onlyDimensionText
 */
	bool							onlyDimensionText;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool							filler_2[2];

/**
 * @brief Place this prefix before the number; example: 'R 7.55'
 * @var prefix
 */
	char							prefix[8];

/**
 * @brief Optional parameter for accessing the prefix in UniString format.
 * @var prefixUStr
 */
	GS::UniString*					prefixUStr;

/**
 * @brief Marker specification (see @ref API_MarkerData).
 * @var markerData
 */
	API_MarkerData					markerData;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3[6];


/**
 * @brief Note parameters (see @ref API_NoteType).
 * @var note
 */
	API_NoteType					note;


/**
 * @brief Base element for the radial dimension.
 * @var base
 */
	API_DimBase						base;

/**
 * @brief End of [radial] dimension line.
 * @var endC
 */
	API_Coord						endC;

/**
 * @brief Radius of dimensioned item.
 * @var dimVal
 */
	double							dimVal;

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	Int32							filler_4[8];

};


// =============================================================================
// Level Dimension
//
// =============================================================================

/**
 * @brief Represents a level dimension.
 * @struct API_LevelDimensionType
 * @ingroup Element
 * @since Archicad 26
 * @remarks The `needFrame` member has been removed in v13; framing is now handled by the dimension note.
 * 			The `parentIndex` member has been removed in v18; use the `parentGuid` field instead.
 * 			From version 26 the type of the `parentType` member was changed to @ref API_ElemType.
 */
struct API_LevelDimensionType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;


/**
 * @brief Pen attribute index of the dimension.
 * @var pen
 */
	short							pen;

/**
 * @brief Format [0..9]:
 * @var dimForm
 * @image html levdim.png "Level dimension format" width=50%
 */
	short							dimForm;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	bool							filler_0;

/**
 * @brief Show plus sign for positive numbers.
 * @var needPlus
 */
	bool							needPlus;

/**
 * @brief Static level dimension.
 * @var staticLevel
 */
	bool							staticLevel;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1;

/**
 * @brief marker size in mms
 * @var markerSize
 */
	double							markerSize;

/**
 * @brief Angle of the level dimension marker, in radians.
 * @var angle
 */
	double							angle;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[8];

/**
 * @brief Parameters of the dimension text (see `API_NoteType`).
 * @var note1
 */
	API_NoteType					note1;

/**
 * @brief Parameters of the secondary dimension text (see `API_NoteType`); for `dimForm` = 8, 9.
 * @var note2
 */
	API_NoteType					note2;

	/**
	 * @brief Location of the marker.
	 * @var loc
	 */
	API_Coord						loc;

/**
 * @brief Level of the parent/floor, or static.
 * @var level
 */
	double							level;

/**
 * @brief Refers to this element (see @ref API_ElemType); refers to floor if `API_ZombieElemID`.
 * @var parentType
 */
	API_ElemType					parentType;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3;

/**
 * @brief Unique ID of referred element if parentType is not `API_ZombieElemID`.
 * @var parentGuid
 */
	API_Guid						parentGuid;

/**
 * @brief Origin of dimensioning (see `API_DimOriginID`).
 * @var origin
 */
	API_DimOriginID					origin;

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	Int32							filler_4[7];

};


// =============================================================================
// Angle Dimension
//
// =============================================================================

/**
 * @brief Represents an angle dimension.
 * @struct API_AngleDimensionType
 * @ingroup Element
 */
struct API_AngleDimensionType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;


/**
 * @brief Pen attribute index of dimension and witness lines.
 * @var linPen
 */
	short							linPen;

/**
 * @brief Show the smaller arc of a-b (inner or outer dimension).
 * @var smallArc
 */
	bool							smallArc;

/**
 * @brief Only dimension texts (notes) are visible &mdash; no leader line.
 * @var onlyDimensionText
 */
	bool							onlyDimensionText;

/**
 * @brief up/in/below
 * @var textPos
 */
	API_TextPosID					textPos;

/**
 * @brief The position of the text relative to the dimension line (see @ref API_DirID). The possible values are: @c APIDir_Parallel, @c APIDir_Horizontal, @c APIDir_Perpendicular.
 * @var textWay
 */
	API_DirID						textWay;

/**
 * @brief Witness line format (see @ref API_WitnessID).
 * @var witnessForm
 */
	API_WitnessID					witnessForm;

/**
 * @brief Gap (APIWtn_Fix) or length (APIWtn_Large) of witness line according to witnessForm.
 * @var witnessVal
 */
	double							witnessVal;

/**
 * @brief Marker specification (see @ref API_MarkerData).
 * @var markerData
 */
	API_MarkerData					markerData;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1[8];


/**
 * @brief Parameters of the dimension text.
 * @var note
 */
	API_NoteType					note;

/**
 * @brief Reference points.
 * @var base
 */
	API_DimBase						base[4];

/**
 * @brief Point to fit dimension arc.
 * @var pos
 */
	API_Coord						pos;

/**
 * @brief Of dimension arc.
 * @var origo
 */
	API_Coord						origo;

/**
 * @brief Angle of dimensioned items [radian].
 * @var dimVal
 */
	double							dimVal;

/**
 * @brief Of dimension arc.
 * @var radius
 */
	double							radius;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[8];

};


// =============================================================================
// Text
//
// =============================================================================

#define	APIFace_Plain				0x0000
#define	APIFace_Bold				0x0001
#define	APIFace_Italic				0x0002
#define	APIFace_Underline			0x0004

#define	APIEffect_StrikeOut			0x0020
#define	APIEffect_SuperScript		0x0040
#define	APIEffect_SubScript			0x0080
#define	APIEffect_Fractional		0x0100
#define	APIEffect_Protected			0x0200

/**
 * @brief Various options for anchor points.
 * @enum API_AnchorID
 * @ingroup Element
 */
typedef enum {
	APIAnc_LT,
	APIAnc_MT,
	APIAnc_RT,
	APIAnc_LM,
	APIAnc_MM,
	APIAnc_RM,
	APIAnc_LB,
	APIAnc_MB,
	APIAnc_RB

} API_AnchorID;

/**
 * @brief Types of the tab.
 * @enum API_TabID
 * @ingroup Element
 * @remarks This enum is used in @ref API_TabType structure. The only available value is @c APITab_Left because the other options are not implemented yet.
 */
typedef enum {
	APITab_Left,
	APITab_Center,
	APITab_Right,
	APITab_Decimalpoint
} API_TabID;

/**
 * @brief Describes a tabulator of a paragraph.
 * @struct API_TabType
 * @ingroup Element
 */
struct API_TabType {

/**
 * @brief The type of the tab. It should be always @c APITab_Left. The other options are not implemented yet.
 * @var type
 */
	API_TabID						type;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief Position of tab in model unit.
 * @var pos
 */
	double							pos;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	double							filler_2[3];

};

/**
 * @brief Describes a continous monostyle piece - called run - of a paragraph.
 * @struct API_RunType
 * @ingroup Element
 * @remarks From Archicad 9 you are able to create multistyle text or textual label. The textContent field of @ref API_ElementMemo structure contains the content. By text or textual label element creating you can pass the content as a UniCode string. In this case all offsets (from, range...) are character offset instead of byte offset. A run can not contain line end character. For more details examine Element Manager example project.
 */
struct API_RunType {

/**
 * @brief The beginning character offset of the run in the content.
 * @var from
 */
	Int32							from;

/**
 * @brief The range of the run in character offset.
 * @var range
 */
	Int32							range;

/**
 * @brief Pen attribute index.
 * @var pen
 */
	short							pen;

/**
 * @brief Style (face) of the run:
 * 		  |Face bit|Style|
 * 		  |--- |--- |
 * 		  |APIFace_Plain|Plain text|
 * 		  |APIFace_Bold|Bold|
 * 		  |APIFace_Italic|Italic|
 * 		  |APIFace_Underline|Underline|
 * @var faceBits
 */
	unsigned short					faceBits;

/**
 * @brief Font attribute index.
 * @var font
 */
	short							font;

/**
 * @brief Effect on the run:
 * 		  |Effect|Style|
 * 		  |--- |--- |
 * 		  |APIEffect_StrikeOut|Strikethrough text|
 * 		  |APIEffect_SuperScript|Superscript|
 * 		  |APIEffect_SubScript|Subscript|
 * 		  |APIEffect_Fractional|Fractional text (not used)|
 * 		  |APIEffect_Protected|Protected text (autotext reference)|
 * @var effectBits
 */
	unsigned short					effectBits;

/**
 * @brief Character height in mms.
 * @var size
 */
	double							size;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	double							filler_1[3];

};

/**
 * @brief Describes a paragraph of a text.
 * @struct API_ParagraphType
 * @ingroup Element
 * @remarks From Archicad 9 you are able to create multistyle text or textual label. @ref API_ParagraphType structure contains all related informations for a paragraph. By text or textual label element creating you can pass the content as a UniCode string. In this case all offsets (from, range...) are character offset instead of byte offset. For more details examine Element Manager example project.
 */
struct API_ParagraphType {

/**
 * @brief The beginning byte offset of the paragraph in the content.
 * @var from
 */
	Int32							from;

/**
 * @brief The range of the paragraph in byte offset.
 * @var range
 */
	Int32							range;

/**
 * @brief Justification of the paragraph (see @ref API_JustID).
 * @var just
 */
	API_JustID						just;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief First indent in mm.
 * @var firstIndent
 */
	double							firstIndent;

/**
 * @brief Indent in mm.
 * @var indent
 */
	double							indent;

/**
 * @brief Right indent in mm.
 * @var rightIndent
 */
	double							rightIndent;

/**
 * @brief Spacing factor between text lines (it should be between -10.0 and -1.0).
 * @var spacing
 */
	double							spacing;

/**
 * @brief Tabulator(s) of a paragraph (see @ref API_TabType).
 * @var tab
 */
	API_TabType						*tab;

/**
 * @brief Run(s) of a paragraph (see @ref API_RunType).
 * @var run
 */
	API_RunType						*run;

/**
 * @brief Line end positions in byte offset.
 * @var eolPos
 */
	Int32							*eolPos;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2;

/**
 * @brief Width of the paragraph in mm (output only).
 * @var width
 */
	double							width;

/**
 * @brief Height of the paragraph in mm (output only).
 * @var height
 */
	double							height;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	double							filler_3[2];

};


/**
 * @brief Text frame shape identifiers.
 * @enum API_TextFrameShapeTypeID
 * @ingroup Element
 */
typedef enum {
	API_TextFrameShapeType_Rectangle			= 0,
	API_TextFrameShapeType_Circle				= 1,
	API_TextFrameShapeType_RoundedRectangle		= 2,
	API_TextFrameShapeType_Pill					= 3
} API_TextFrameShapeTypeID;


/**
 * @brief Parameters of the Text frame shape.
 * @struct API_TextFrameType
 * @ingroup Element
 */
struct API_TextFrameType {
/**
 * @brief Shape type identifier.
 * @var shapeType
 */
	API_TextFrameShapeTypeID		shapeType;

/**
* @brief Use fixed width and height values for the size of the shape polygon, otherwise the frame shape fits to the current text box.
* @var isSizeFixed
*/
	bool							isSizeFixed;

/**
 * @brief Width of the frame shape in mm, when @c isSizeFixed is true. Its value should be between 1 and 1000.
 * @var fixedWidth
 */
	double							fixedWidth;

/**
 * @brief Height of the frame shape in mm, when @c isSizeFixed is true. Its value should be between 1 and 1000.\n
 * 	This parameter is ignored in case of @c API_TextFrameShapeType_Circle shape type, where the value of @c fixedWidth is used as the diameter of the circle.
 * @var fixedHeight
 */
	double							fixedHeight;
};


/**
 * @brief Represents a text, or a textual label.
 * @struct API_TextType
 * @ingroup Element
 * @remarks From Archicad 9 you are able to create multistyle text or textual label. In this case the pen, faceBits, font, just, size, spacing, effectBits members are not used. These members are used only by default element setting and monostyle textual element creating. The paragraphs handle of @ref API_ElementMemo structure contains these informations for each paragraphs of the text. For text related memo data (e.g. content, paragraphs) see the @ref ACAPI_Element_GetMemo function. For more details examine Element Manager example project.
 */
struct API_TextType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;


/**
 * @brief Pen attribute index.
 * @var pen
 */
	short							pen;

/**
 * @brief Style (face) of text:
 * 		  |Face bit|Style|
 * 		  |--- |--- |
 * 		  |APIFace_Plain|Plain text|
 * 		  |APIFace_Bold|Bold|
 * 		  |APIFace_Italic|Italic|
 * 		  |APIFace_Underline|Underline|
 *
 * @var faceBits
 */
	unsigned short					faceBits;

/**
 * @brief Font attribute index.
 * @var font
 */
	short							font;

/**
 * @brief The rotation angle will not change when the element is rotated and this flag is true.
 * @var fixedAngle
 */
	bool							fixedAngle;

/**
 * @brief Anchor point of the text (see @ref API_AnchorID).
 * @var anchor
 */
	API_AnchorID					anchor;

/**
 * @brief Justification of the text (see @ref API_JustID).
 * @var just
 */
	API_JustID						just;

/**
 * @brief Character height in mm.
 * @var size
 */
	double							size;

/**
 * @brief Spacing factor between text lines (it should be between -10.0 and -1.0).
 * @var spacing
 */
	double							spacing;

/**
 * @brief Rotation angle [radian].
 * @var angle
 */
	double							angle;



/**
 * @brief Special text effects:
 * 		  |Effect|Style|
 * 		  |--- |--- |
 * 		  |APIEffect_StrikeOut|Strikethrough text|
 * 		  |APIEffect_SuperScript|Superscript|
 * 		  |APIEffect_SubScript|Subscript|
 * 		  |APIEffect_Protected|Protected text (autotext reference)|
 *
 * @var effectsBits
 */
	Int32							effectsBits;

/**
 * @brief Width scale of the text (it should be between 0.75 and 10.0).
 * @var widthFactor
 */
	double							widthFactor;

/**
 * @brief Spacing scale of the text (it should be between 0.75 and 10.0).
 * @var charSpaceFactor
 */
	double							charSpaceFactor;

/**
 * @brief Size not depends on output scale if this flag is true.
 * @var fixedSize
 */
	bool							fixedSize;

/**
 * @brief Draw the frame of the textblock.
 * @var usedContour
 */
	bool							usedContour;

/**
 * @brief Draw a solid fill to the background of the textblock.
 * @var usedFill
 */
	bool							usedFill;

/**
 * @brief Pen index of the frame of the textblock.
 * @var contourPen
 */
	short							contourPen;

/**
 * @brief Pen index of the background of the textblock.
 * @var fillPen
 */
	short							fillPen;


/**
 * @brief Coordinates of text anchor point.
 * @var loc
 */
	API_Coord						loc;

/**
 * @brief Horizontal size of text box in mm.
 * @var width
 */
	double							width;

/**
 * @brief Vertical size of text box in mm.
 * @var height
 */
	double							height;

/**
 * @brief If false then wrap around at the boundary of the destination rectangle.
 * @var nonBreaking
 */
	bool							nonBreaking;

/**
 * @brief Multistyle text (input only).
 * @var multiStyle
 */
	bool							multiStyle;

/**
 * @brief Use the array of line end positions by creating the element (input only).
 * 		  Only available for multistyle text. (see @ref API_ParagraphType)
 * @var useEolPos
 */
	bool							useEolPos;


/**
 * @brief Number of text lines.
 * @var nLine
 */
	Int32							nLine;

/**
 * @brief Belongs to something else e.g. a label.
 * @var owner
 */
	API_Guid						owner;


/**
 * @brief The offset value of the frame or opaque background to the bounding box of the text block.
 * @var contourOffset
 */
	double							contourOffset;


/**
 * @brief The text should always be readable.
 * @var flipEnabled
 */
	bool							flipEnabled;

/**
* @brief The text frame info. @ref API_TextFrameType
* The text frame shapes are available only for label elements. Standalone Text elements may have rectangle shaped frame only.
* @var textFrame
*/
	API_TextFrameType				textFrame;
};


// =============================================================================
// Label
//
// =============================================================================

/**
 * @brief Describes the various types for a label.
 * @enum API_LblClassID
 * @ingroup Element
 */
typedef enum {
	APILblClass_Text				= 'TEXT',
	APILblClass_Symbol				= 'SYMB'

} API_LblClassID;

/**
 * @brief Represents a textual or a symbol label.
 * @struct API_LabelType
 * @ingroup Element
 * @remarks For label related memo data (e.g. content, additional parameters) see the @ref ACAPI_Element_GetMemo function. The interpretation of the `textWay` field is:
 * @image html labelway.png "Label direction" width=50%
 * 		  The `squareRootAngle` is marked with &beta; on the following picture:
 * @image html squareRootAngle.png "Square root angle" width=50%
 * 		  The `titleTyp` field has been removed in API 21.
 * 		  From version 26 the type of the parentType member was changed to @ref API_ElemType.
 */
struct API_LabelType {
	/**
	 * @brief General element header and text or symbol information of label.
	 * @var u
	 */
	union {
		/**
		 * @brief General element header.
		 * @var head
		 */
		API_Elem_Head				head;

		/**
		 * @brief Contains the details of the textual label. The `typeID` field of the
		 * 		  `head` should be set to `API_LabelID` (!).
		 * @var text
		 */
		API_TextType				text;

		/**
		 * @brief Contains the details of the symbol label. The `typeID` field of the
		 * 		  `head` should be set to `API_LabelID` (!).
		 * @var symbol
		 */
		API_ObjectType				symbol;

	} u;

	/**
	 * @brief Type (class) of the label.
	 * @var labelClass
	 */
	API_LblClassID					labelClass;

// Text labels
	/**
	 * @brief Direction of text for textual labels (see @ref API_DirID and the
	 * 		  picture under Remarks). For labels only `APIDir_Parallel`,
	 * 		  `APIDir_Horizontal`, `APIDir_Vertical`, and `APIDir_General` can be
	 * 		  used.
	 * @var textWay
	 */
	API_DirID						textWay;

	/**
	 * @brief Font attribute index (for symbol labels only).
	 * @var font
	 */
	short							font;

	/**
	 * @brief Style (face) of text (for symbol labels only):
	 * 		  |Face bit|Meaning|
	 * 		  |--- |--- |
	 * 		  |APIFace_Plain|Plain text|
	 * 		  |APIFace_Bold|Bold|
	 * 		  |APIFace_Italic|Italic|
	 * 		  |APIFace_Underline|Underline|
	 * 		  |APIFace_Outline|Outlined (Macintosh only)|
	 * 		  |APIFace_Shadow|Shadow (Macintosh only)|
	 *
	 * @var faceBits
	 */
	unsigned short					faceBits;

	/**
	 * @brief True if the Label is set to be "Always Readable".
	 * @var flipEnabled
	 */
	bool							flipEnabled;

	/**
	 * @brief True if "Wrap Text" is turned off for this Label.
	 * @var nonBreaking
	 */
	bool							nonBreaking;

	/**
	 * @brief Size of the text in mm (for symbol labels only).
	 * @var textSize
	 */
	double							textSize;

	/**
	 * @brief Switches opaque background for symbol labels.
	 * @var useBgFill
	 */
	bool							useBgFill;

	/**
	 * @brief Defines the background pen for symbol labels; effective only if `useBgFill` is `true`.
	 * @var fillBgPen
	 */
	short							fillBgPen;

	/**
	 * @brief Text effects to be applied for symbol labels:
	 * 		  |Effect bit|Effect|
	 * 		  |--- |--- |
	 * 		  |APIEffect_StrikeOut|Strikethrough text|
	 * 		  |APIEffect_SuperScript|Superscript|
	 * 		  |APIEffect_SubScript|Subscript|
	 * 		  |APIEffect_Fractional|Fractional text (not used)|
	 * 		  |APIEffect_Protected|Protected text (autotext reference)|
	 * @var effectsBits
	 */
	Int32							effectsBits;

// Label leader line
	/**
	 * @brief Pen attribute index of the leader line.
	 * @var pen
	 */
	short							pen;

	/**
	 * @brief Line type attribute index of the leader line.
	 * @var ltypeInd
	 */
	API_AttributeIndex				ltypeInd;

	/**
	 * @brief The padding of the Label's frame (i.e. the distance between the frame and the text).
	 * @var contourOffset
	 */
	double							contourOffset;

	/**
	 * @brief Put a frame around the content? (For both Symbol and Text Labels).
	 * @var framed
	 */
	bool							framed;

	/**
	 * @brief Add a Leader Line (i.e. pointer line) to the Label? (For both Symbol and Text Labels.)
	 * @var hasLeaderLine
	 */
	bool							hasLeaderLine;

	/**
	 * @brief The arrow type.
	 * @var arrowData
	 */
	API_ArrowData					arrowData;

	/**
	 * @brief Anchor point the label pointer line is connected to.
	 * @var anchorPoint
	 */
	API_LblAnchorID					anchorPoint;

	/**
	 * @brief Leader line shape. For the list of available shapes see
	 * @ref API_LeaderLineShapeID.
	 * @var leaderShape
	 */
	API_LeaderLineShapeID			leaderShape;

	/**
	 * @brief Used only if `leaderShape == API_SquareRoot`. Valid range: 1&deg; <=
	 * 		  `squareRootAngle` <= 179&deg;, in radians. See picture under Remarks.
	 * @var squareRootAngle
	 */
	double							squareRootAngle;

	/**
	 * @brief Font attribute index (for symbol labels only).
	 * @var parentType
	 */
	API_ElemType					parentType;

	/**
	 * @brief Contains the type of the parent element, or `API_ZombieElemID` if the Label
	 * 		  is independent.
	 * 		  When getting the Label defaults the labelable element type can be passed here.
	 * @ref ACAPI_Element_GetDefaults will return the Label default for the given element type.
	 * 		When creating new Labels,
	 * 		- set this to `APINULLGuid` to create an independent Label; or
	 * 		- set this to the GUID of the owner element (a labelable element) to create an associative Label.
	 * 		When getting or changing a Label, this member will be filled with the GUID of the owner element, or
	 * 		`APINULLGuid`, if the Label is independent. You cannot change an existing associative
	 * 		Label to independent, or an existing independent Label to associative.
	 * @var parent
	 */
	API_Guid						parent;

	/**
	 * @brief Beginning coordinate of the leader line.
	 * @var begC
	 */
	API_Coord						begC;

	/**
	 * @brief Middle coordinate of the leader line.
	 * @var midC
	 */
	API_Coord						midC;

	/**
	 * @brief End coordinate of the leader line.
	 * @var endC
	 */
	API_Coord						endC;

	/**
	 * @brief When creating associative Labels:
	 * 		  - if set to `true`, the Label will be created at its default position
	 * 		  (`begC`, `midC`, and `endC` are ignored);
	 * 		  - if set to `false`, the Label will be created using `begC`, `midC`, and `endC`.
	 * @var createAtDefaultPosition
	 */
	bool							createAtDefaultPosition;

	/**
	 * @brief Hide the label with its base element?
	 * @var hideWithBaseElem
	 */
	bool							hideWithBaseElem;
};


// =============================================================================
// Zone
//
// =============================================================================

/**
 * @brief Represents a zone stamp.
 * @struct API_ZoneType
 * @ingroup Element
 * @remarks The additional parameters of the zone category can be found in the params field of @ref API_ElementMemo.
 * 			With the help of @ref ACAPI_Element_GetRelations you can find out what and how many construction elements and objects are in the zone.
 */
struct API_ZoneType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;


/**
 * @brief Pen attribute index for the zone stamp. Used only if useStampPens is false.
 * @var pen
 */
	short							pen;

/**
 * @brief Index of the actual zone category.
 * @var catInd
 */
	API_AttributeIndex				catInd;

/**
 * @brief Draw with a single pen (false) or use the pens defined in the zone category library part (true)?
 * @var useStampPens
 */
	bool							useStampPens;

/**
 * @brief Manually created zone; all edges static, no reference point (refPos).
 * @var manual
 */
	bool							manual;

/**
 * @brief Surrounded by walls' reference lines, not side lines.
 * @var refLineFlag
 */
	bool							refLineFlag;

/**
 * @brief If true, then Archicad uses the reference line of the walls surrounding the zone for calculations; otherwise it uses the inner edges of the walls. (Can be used only if refLineFlag is true.)
 * @var show_found_poly
 */
	bool							show_found_poly;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	char							filler_1[16];

/**
 * @brief Name of the room as a Unicode string.
 * @var roomName
 */
	GS::uchar_t						roomName [API_UniLongNameLen];

/**
 * @brief Room number as a Unicode string.
 * @var roomNoStr
 */
	GS::uchar_t						roomNoStr [32];

/**
 * @brief Base level of the room, measured from the floor level.
 * @var roomBaseLev
 */
	double							roomBaseLev;

/**
 * @brief Height of the room.
 * @var roomHeight
 */
	double							roomHeight;

/**
 * @brief The offset from top floor if zone is top linked.
 * @var roomTopOffset
 */
	double							roomTopOffset;

/**
 * @brief Sub-floor thickness of the room.
 * @var roomFlThick
 */
	double							roomFlThick;

/**
 * @brief Room letter size in mm.
 * @var roomLSize
 */
	double							roomLSize;

/**
 * @brief Reduce the zone area with this value [%].
 * @var reducePercent
 */
	double							reducePercent;

/**
 * @brief Material attribute index of the 3D zone's (free or all) surfaces.
 * @var material
 */
	API_AttributeIndex				material;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[2];

/**
 * @brief Rotation angle of the room stamp [radian].
 * @var stampAngle
 */
	double							stampAngle;

/**
 * @brief The stampAngle will not change when the element is rotated and this flag is true.
 * @var fixedAngle
 */
	bool							fixedAngle;

/**
 * @brief Use material for all surfaces if true; otherwise inherit boundary walls' and trimming elements' materials.
 * @var oneMat
 */
	bool							oneMat;

/**
 * @brief Pen attribute index of zone's cover fill.
 * @var floorFillPen
 */
	short							floorFillPen;

/**
 * @brief Fill attribute index of the zone's cover fill.
 * @var floorFillInd
 */
	API_AttributeIndex				floorFillInd;

/**
 * @brief Background pen attribute index of the zone's cover fill.
 * @var floorFillBGPen
 */
	short							floorFillBGPen;

/**
 * @brief Pen attribute index of zone's contour.
 * @var floorContLPen
 */
	short							floorContLPen;

/**
 * @brief Line type attribute index of zone's contour.
 * @var floorContLType
 */
	API_AttributeIndex				floorContLType;

/**
 * @brief Draw contour line?
 * @var useContourLine
 */
	bool							useContourLine;

/**
 * @brief Use local origo for cover fill drawing?
 * @var useLocalOrigo
 */
	bool							useLocalOrigo;

/**
 * @brief Use Vectorial 3D Hatch patterns in Floor Plan view? This will apply the Vectorial 3D Hatch set for the element's top side material.
 * @var use3DHatching
 */
	bool							use3DHatching;

/**
 * @brief Use cover fill?
 * @var useFloorFill
 */
	bool							useFloorFill;

/**
 * @brief Index to the zone category library part in the library.
 * @var libInd
 */
	Int32							libInd;

/**
 * @brief Mode of linking to home story.
 * @var linkToSettings
 */
	API_LinkToSettings				linkToSettings;

/**
 * @brief The top linked story (relative to home story). Negative values are invalid. 0 = not top linked.
 * @var relativeTopStory
 */
	short							relativeTopStory;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	short							filler_3[3];


/**
 * @brief Polygon of the zone.
 * @var poly
 */
	API_Polygon						poly;

/**
 * @brief Position of the origin of the zone stamp.
 * @var pos
 */
	API_Coord						pos;

/**
 * @brief Reference point to find zone if it was not created manually.
 * @var refPos
 */
	API_Coord						refPos;

/**
 * @brief Base coordinate of zone's cover fill reference vector if it's linked to the element.
 * @var locOrigo
 */
	API_Coord						locOrigo;

/**
 * @brief Angle of zone's cover fill reference vector if it's linked to the element.
 * @var fillAngle
 */
	double							fillAngle;

/**
 * @brief The found polygon of the zone. You can access the geometry through the @ref API_ElementMemo of the zone.
 * @var refPoly
 */
	API_Polygon						refPoly;

/**
 * @brief GUID of the zone stamp object.
 * @var stampGuid
 */
	API_Guid						stampGuid;

};


// =============================================================================
// Hatch
//
// =============================================================================

#define	APIHatch_DraftingFills		0x0000						// drafting fill
#define	APIHatch_CutFills 			0x0001						// cut fill
#define	APIHatch_CoverFills			0x0002						// cover fill

/**
 * @brief Determines the subtype type of the hatch.
 * @enum API_HatchSubType
 * @ingroup Element
 */
typedef enum {
	API_FillHatch,
	API_BuildingMaterialHatch

} API_HatchSubType;

/**
 * @brief Determines the behaviour of the hatch.
 * @enum API_HatchFlags
 */
typedef enum {
	APIHatch_HasBkgRGBColor					= 0x01,
	APIHatch_HasFgRGBColor					= 0x02,
	APIHatch_OverrideFgPen					= 0x04,
	APIHatch_OverrideBkgPen					= 0x08,
	APIHatch_OverrideFillInd				= 0x10

} API_HatchFlags;

/**
 * @brief Describes the optionally overridden pen used for hatches.
 * @struct API_ExtendedPenType
 * @ingroup Element
 */
struct API_ExtendedPenType {

/**
 * @brief The pen color index if not overridden; the original pen index.
 * @var penIndex
 */
	short	penIndex;

/**
 * @brief The pen color index if overridden.
 * @var colorOverridePenIndex
 */
	short	colorOverridePenIndex;

/**
 * @brief Sets both the normal and the overridden pen color index.
 * @param pen1 Pen index.
 * @param pen2 Color override pen index.
 */
	void	Set (short pen1, short pen2)		{ penIndex = pen1; colorOverridePenIndex = pen2; }

/**
 * @brief Tells whether the pen index is overridden.
 * @return True if it is overridden.
 */
	bool	IsOverriden () const				{ return colorOverridePenIndex > 0; }

/**
 * @brief Returns the effective pen color index.
 * @return Pen color index.
 */
	short	GetEffectiveColorIndex () const		{ return IsOverriden () ? colorOverridePenIndex : penIndex; }
};

/**
 * @brief Represents a hatch element.
 * @struct API_HatchType
 * @ingroup Element
 * @remarks In Archicad 10 the `polyFill` field is removed from the structure, and the `global`, `refPos`, and
 * 			`refAngle` parameters are placed into a separate structure (@ref API_HatchOrientation). Along this line, in Archicad
 * 			13 the gradient fill parameters were also moved to the same structure. The `hasForegroundRGB` and
 * 			`hasBackgroundRGB` parameters are placed into a separate structure (`API_HatchFlags`). In Archicad 20 the `contPen`
 * 			and `fillPen` parameters are placed into a separate structure (@ref API_ExtendedPenType).
 */
struct API_HatchType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;


/**
 * @brief Pen attribute index of the hatch contour (0 if contour is switched off).
 * @var contPen
 */
	API_ExtendedPenType				contPen;

/**
 * @brief Subtype of the hatch.
 * @var hatchType
 */
	API_HatchSubType				hatchType;

/**
 * @brief Flags to modify hatch display. See `API_HatchFlags` for possible values.
 * @var hatchFlags
 */
	UInt32							hatchFlags;

/**
 * @brief Pen attribute index of the hatch fill.
 * @var fillPen
 */
	API_ExtendedPenType				fillPen;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	short							filler_0;

/**
 * @brief Pen attribute index of hatch fill background.
 * @var fillBGPen
 */
	short							fillBGPen;

/**
 * @brief Fill attribute index of the hatch. Used only is case of `API_FillHatch`.
 * @var fillInd
 */
	API_AttributeIndex				fillInd;

/**
 * @brief Building Material attribute index of the hatch. Used only is case of `API_BuildingMaterialHatch`..
 * @var buildingMaterial
 */
	API_AttributeIndex				buildingMaterial;

/**
 * @brief Line type attribute index.
 * @var ltypeInd
 */
	API_AttributeIndex				ltypeInd;

/**
 * @brief Special area percent in a room (negative means OFF).
 * @var roomSpecial
 */
	char							roomSpecial;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	char							filler_1[4];

/**
 * @brief True if area text is shown (parameters in note).
 * @var showArea
 */
	bool							showArea;

/**
 * @brief How to determine the type of this fill (cover, cut, drafting)
 * 		  |Determination|Meaning|
 * 		  |--- |--- |
 * 		  |APIHatch_DraftingFills|Default fill category. Drafting fills adopt the Drafting Fill settings chosen in<br>Display Options.|
 * 		  |APIHatch_CoverFills|The Cover Fill category is assigned to the fills of Slabs, Roofs,<br>Meshes and Zones on the floor plan. Cover fills adopt the Element Cover Fill settings chosen in Display
 * 		  Options.| |APIHatch_CutFills|The Cut Fill category is assigned to the fills of Cut Elements. Cut fills
 * 		  adopt the Cut Fill settings chosen in Display Options.|<br>@var determination
 */
	short							determination;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[2];

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	char							filler_3[16];

/**
 * @brief Pen weight of the contour (overrides the weight defined in `contPen`).
 * @var penWeight
 */
	double							penWeight;

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	Int32							filler_4[2];


/**
 * @brief Parameters of the area text.
 * @var note
 */
	API_NoteType					note;


/**
 * @brief Polygon of the hatch element.
 * @var poly
 */
	API_Polygon						poly;

/**
 * @brief Reserved for later use.
 * @var filler_5
 */
	bool							filler_5[8];

/**
 * @brief Reserved for later use.
 * @var filler_6
 */
	Int32							filler_6[10];


/**
 * @brief Orientation and distortion parameters of the cover fill.
 * @var hatchOrientation
 */
	API_HatchOrientation			hatchOrientation;


/**
 * @brief Reserved for later use.
 * @var filler_7
 */
	bool							filler_7;

/**
 * @brief Reserved for later use.
 * @var filler_8
 */
	char							filler_8[3];

/**
 * @brief Reserved for later use.
 * @var filler_9
 */
	Int32							filler_9[5];

/**
 * @brief RGB color for background painting.
 * @var backgroundRGB
 */
	API_RGBColor					backgroundRGB;

/**
 * @brief Reserved for later use.
 * @var filler_10
 */
	bool							filler_10;

/**
 * @brief Reserved for later use.
 * @var filler_11
 */
	char							filler_11[3];

/**
 * @brief Reserved for later use.
 * @var filler_12
 */
	Int32							filler_12[5];

/**
 * @brief RGB color for foreground painting.
 * @var foregroundRGB
 */
	API_RGBColor					foregroundRGB;

};


// =============================================================================
// Line
//
// =============================================================================

#define	APILine_DetOrigin			0x0000
#define	APILine_DetInnerLine		0x0001
#define	APILine_DetContourLine		0x0002

/**
 * @brief Represents a 2D line.
 * @struct API_LineType
 * @ingroup Element
 */
struct API_LineType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;


/**
 * @brief (Overridden) pen attribute index.
 * @var linePen
 */
	API_ExtendedPenType				linePen;

/**
 * @brief Line type attribute index.
 * @var ltypeInd
 */
	API_AttributeIndex				ltypeInd;

/**
 * @brief Is this line a zone boundary?
 * @var roomSeparator
 */
	bool							roomSeparator;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[5];

/**
 * @brief Line category:
 * 		  |Determination|Meaning|
 * 		  |--- |--- |
 * 		  |APILine_DetOrigin|Default line category. Lines in the Drafting line category are not affected by the Line<br>Weight and Section Fill settings chosen in Display Options.|
 * 		  |APILine_DetInnerLine|A skin separator line separates skins of composite structures. Lines in the Skin<br>Separator category will be either hidden or shown depending on the Cut Fill type chosen in Display Options.<br>Also, lines in the Skin Separator category can be optionally placed onto their own layer during DXF/DWG conversion functions.|
 * 		  |APILine_DetContourLine|Lines in the Cut line category will be affected if you have chosen the 'Bold Cut<br>Line' setting in the Line Weight menu of Display Options.|
 * @var determination
 */
	short							determination;

/**
 * @brief Arrow data for the line ends.
 * @var arrowData
 */
	API_ArrowData					arrowData;

/**
 * @brief Pen weight for the line (can override the weight in linePen, otherwise set it to `API_DefPenWeigth`: use default weight of the pen).
 * @var penWeight
 */
	double							penWeight;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[8];


/**
 * @brief Coordinate of the first point.
 * @var begC
 */
	API_Coord						begC;

/**
 * @brief Coordinate of the second point.
 * @var endC
 */
	API_Coord						endC;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3[8];

};


// =============================================================================
// Polyline
//
// =============================================================================

/**
 * @brief Represents a 2D polyline.
 * @struct API_PolyLineType
 * @ingroup Element
 */
struct API_PolyLineType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;


/**
 * @brief (Overridden) pen color attribute index.
 * @var linePen
 */
	API_ExtendedPenType				linePen;

/**
 * @brief Line type index.
 * @var ltypeInd
 */
	API_AttributeIndex				ltypeInd;

/**
 * @brief Room separator line.
 * @var roomSeparator
 */
	bool							roomSeparator;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[5];
/**
 * @brief Line category:
 * 		  |Category|Meaning|
 * 		  |--- |--- |
 * 		  |APILine_DetOrigin|Default line category. Lines in the Drafting line category are not affected by the Line<br>Weight and Section Fill settings chosen in Display Options.|
 * 		  |APILine_DetInnerLine|A skin separator line<br>separates skins of composite structures. Lines in the Skin Separator category will be either hidden or shown<br>depending on the Cut Fill type chosen in Display Options. Also, lines in the Skin Separator category can be<br>optionally placed onto their own layer during DXF/DWG conversion functions.|
 * 		  |APILine_DetContourLine|Lines in<br>the Cut line category will be affected if you have chosen the 'Bold Cut Line' setting in the Line Weight menu<br>of Display Options.|
 * @var determination
 */
	short							determination;

/**
 * @brief Arrow data for the line ends.
 * @var arrowData
 */
	API_ArrowData					arrowData;

/**
 * @brief Pen weight for the line (can override the weight in linePen, otherwise set it to @c API_DefPenWeigth : use default weight of the pen).
 * @var penWeight
 */
	double							penWeight;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	char							filler_2[16];

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3[8];


/**
 * @brief The polygon of the polyline.
 * @var poly
 */
	API_Polygon						poly;

/**
 * @brief Determine the draw segment mode of the polyline. 0 means draw segments one-by-one, 1 means draw segments continuously.
 * @var drawSegmentMode
 */
	short							drawSegmentMode;

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	short							filler_4;

/**
 * @brief Reserved for later use.
 * @var filler_5
 */
	Int32							filler_5[7];

};


// =============================================================================
// Arc or Circle
//
// =============================================================================

/**
 * @brief Represents an elliptical or circular arc.
 * @struct API_ArcType
 * @ingroup Element
 */
struct API_ArcType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;


/**
 * @brief (Overridden) pen attribute index.
 * @var linePen
 */
	API_ExtendedPenType				linePen;

/**
 * @brief Line type attribute index.
 * @var ltypeInd
 */
	API_AttributeIndex				ltypeInd;

/**
 * @brief Is this arc a zone boundary?
 * @var roomSeparator
 */
	bool							roomSeparator;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[5];

/**
 * @brief Determines the type of this line.
 * @var determination
 * 		Line category:
 * 		|Type|Meaning|
 * 		|--- |--- |
 * 		|APILine_DetOrigin|Default line category. Lines in the Drafting line category are not affected by the Line Weight and Section Fill settings chosen in Display Options.|
 * 		|APILine_DetInnerLine|A skin separator line separates skins of composite structures. Lines in the Skin Separator category will be either hidden or shown depending on the Cut Fill type chosen in Display Options. Also, lines in the Skin Separator category can be optionally placed onto their own layer during DXF/DWG conversion functions.|
 * 		|APILine_DetContourLine|Lines in the Cut line category will be affected if you have chosen the 'Bold Cut Line' setting in the Line Weight menu of Display Options.|
 */
	short							determination;

/**
 * @brief Arrow data for the arc ends.
 * @var arrowData
 */
	API_ArrowData					arrowData;

/**
 * @brief Pen weight for the arc (can override the weight in linePen, otherwise set it to @c API_DefPenWeigth : use default weight of the pen).
 * @var penWeight
 */
	double							penWeight;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	char							filler_2[16];

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3[8];


/**
 * @brief Coordinate of the center point.
 * @var origC
 */
	API_Coord						origC;

/**
 * @brief Radius.
 * @var r
 */
	double							r;

/**
 * @brief 0.0, or the angle of the 'a' axis.
 * @var angle
 */
	double							angle;

/**
 * @brief 1.0, or 'a/b' of the ellipse.
 * @var ratio
 */
	double							ratio;

/**
 * @brief Beginning angle of the arc.
 * @var begAng
 */
	double							begAng;

/**
 * @brief End angle of the arc.
 * @var endAng
 */
	double							endAng;

/**
 * @brief Is the ellipse reflected onto the smaller axis?
 * @var reflected
 */
	bool							reflected;

/**
 * @brief Is this a whole arc? (output only)
 * @var whole
 */
	bool							whole;

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	short							filler_4;

/**
 * @brief Reserved for later use.
 * @var filler_5
 */
	Int32							filler_5[7];

};

/**
 * @brief Represents a circle (derived from the circular arc).
 * @typedef API_CircleType
 * @ingroup Element
 */
using API_CircleType = API_ArcType;


// =============================================================================
// Spline
//
// =============================================================================

/**
 * @brief Describes the control handles for Bezier-splines.
 * @struct API_SplineDir
 * @ingroup Element
 * @remarks The picture below illustrates the meaning of these fields.
 * @image html SplineDir.png "Spline direction" width=50%
 */
struct API_SplineDir {

/**
 * @brief Bezier direction length previous.
 * @var lenPrev
 */
	double							lenPrev;

/**
 * @brief Bezier direction length next.
 * @var lenNext
 */
	double							lenNext;

/**
 * @brief Bezier direction angle.
 * @var dirAng
 */
	double							dirAng;

};

/**
 * @brief Represents a cubic or Bezier-spline.
 * @struct API_SplineType
 * @ingroup Element
 * @remarks The coordinates of the spline points are given in the coords field of @ref API_ElementMemo.
 * 			The last and the first coordinate in coords should be different; and the coordinate with index 0 is also used.
 * 			If `autoSmooth` is false, then the handle positions for every spline point are given in the `bezierDirs` field in @ref API_ElementMemo.
 */
struct API_SplineType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;


/**
 * @brief (Overridden) pen attribute index.
 * @var linePen
 */
	API_ExtendedPenType				linePen;

/**
 * @brief Line type attribute index.
 * @var ltypeInd
 */
	API_AttributeIndex				ltypeInd;

/**
 * @brief Is this arc a zone boundary?
 * @var roomSeparator
 */
	bool							roomSeparator;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[5];

/**
 * @brief Line category:
 * 		  |Category|Meaning|
 * 		  |--- |--- |
 * 		  |APILine_DetOrigin|Default line category. Lines in the Drafting line category are not affected by the Line Weight and Section Fill settings chosen in Display Options.|
 * 		  |APILine_DetInnerLine|A skin separator line separates skins of composite structures. Lines in the Skin Separator category will be either hidden or shown depending on the Cut Fill type chosen in Display Options. Also, lines in the Skin Separator category can be optionally placed onto their own layer during DXF/DWG conversion functions.|
 * 		  |APILine_DetContourLine|Lines in the Cut line category will be affected if you have chosen the 'Bold Cut Line' setting in the Line Weight menu of Display Options.|
 *
 * @var determination
 */
	short							determination;

/**
 * @brief Arrow data for the arc ends.
 * @var arrowData
 */
	API_ArrowData					arrowData;

/**
 * @brief Pen weight for the arc (can override the weight in linePen, otherwise set it to @c API_DefPenWeigth : use default weight of the pen).
 * @var penWeight
 */
	double							penWeight;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	char							filler_2[16];

/**
 * @brief Smooth spline automatically, or use the bezierDirs field (of type @ref API_SplineDir) in @ref API_ElementMemo?
 * @var autoSmooth
 */
	bool							autoSmooth;

/**
 * @brief Is this a closed curve?
 * @var closed
 */
	bool							closed;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	short							filler_3;

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	Int32							filler_4[7];

};


// =============================================================================
// Hotspot
//
// =============================================================================

/**
 * @brief Represents a hotspot.
 * @struct API_HotspotType
 * @ingroup Element
 */
struct API_HotspotType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;


/**
 * @brief Pen attribute index.
 * @var pen
 */
	short							pen;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1[3];


/**
 * @brief 2D position of the hotspot.
 * @var pos
 */
	API_Coord						pos;

/**
 * @brief Z coordinate of the hotpsot (this can come from a GDL script).
 * @var height
 */
	double							height;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[2];

};


// =============================================================================
// Picture
//
// =============================================================================

/**
 * @brief Storage format of a picture.
 * @enum API_PictureFormat
 * @ingroup Element
 * @remarks This enum is used when you convert a picture from a given format to another with the @ref ACAPI_Conversion_ConvertPicture goody function. @ref API_PictureFormat is also a part of the @ref API_PictureType structure.
 * 			You might also use MIME types for identifying the standard image formats instead of @ref API_PictureFormat. See the @ref ACAPI_Conversion_ConvertMimePicture goody function.
 */
typedef enum {
	APIPictForm_Default,
	APIPictForm_Bitmap,
	APIPictForm_GIF,
	APIPictForm_TIFF,
	APIPictForm_JPEG,
	APIPictForm_PNG

} API_PictureFormat;

/**
 * Various options for color depth.
 * @enum API_ColorDepthID
 * @ingroup Dialog
 */
typedef enum {
	APIColorDepth_FromSourceImage = -1,							// Use color depth from source image
	APIColorDepth_BW = 0,										// Black && White
	APIColorDepth_16C,											// 16 Colors
	APIColorDepth_256C,											// 256 Colors
	APIColorDepth_16G,											// 16 Grays
	APIColorDepth_256G,											// 256 Grays
#ifdef macintosh
	APIColorDepth_4C,											// 4 Colors
	APIColorDepth_4G,											// 4 Grays
	APIColorDepth_ThC,											// Thousands of Colors
	APIColorDepth_MiC,											// Millions of Colors
	APIColorDepth_MiCP											// Millions of Colors+
#endif
#ifdef WINDOWS
	APIColorDepth_64KC,											// 64K Colors
	APIColorDepth_TC24,											// True Color - 24 bit
	APIColorDepth_TC32											// True Color - 32 bit
#endif

} API_ColorDepthID;


/**
 * @brief Represents a figure (picture) element.
 * @struct API_PictureType
 * @ingroup Element
 * @remarks Possible values:
 * 			|   |creating (usePixelSize is true)|creating (usePixelSize is false)|
 * 			|---|-------------------------------|--------------------------------|
 * 			|mirrored|required|   |
 * 			|pixelSizeX|required|ignored|
 * 			|pixelSizeY|required|ignored|
 * 			|rotAngle|required| |
 * 			|destBox: xMin, yMin|required (insert position)| |
 * 			|destBox: xMax, yMax|ignored|required|
 * 			|origBox|ignored| |
 * 			|colorDepth|ignored| |
 * 			|anchorPoint|required| |
 * 			|storageFormat|required| |
 * 			|pictName|optional| |
 * 			Creating
 * @image html PictDestBox.png "Picture destination box" width=50%
 * 		  Not creating
 * @image html PictUsePixelSize.png "Picture with pixel size" width=50%
 * 		  Use the `directCreate` option if you do not want the parameters you passed to be checked and re-calculated.
 */
struct API_PictureType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;


/**
 * @brief True if mirrored to local vertical axis.
 * @var mirrored
 */
	bool							mirrored;

/**
 * @brief Has meaning only when creating the picture, see the table below.
 * @var usePixelSize
 */
	bool							usePixelSize;

/**
 * @brief Physical x size in pixels (When creating the picture and usePixelSize is true, then the logical x size in pixels of the current zoom. See the table below.)
 * @var pixelSizeX
 */
	short							pixelSizeX;

/**
 * @brief Physical y size in pixels (When creating the picture and usePixelSize is true, then the logical y size in pixels of the current zoom. See the table below.)
 * @var pixelSizeY
 */
	short							pixelSizeY;

/**
 * @brief White pixels of the picture are drawn transparently.
 * @var transparent
 */
	bool							transparent;

/**
 * @brief Create the picture element without parameter checking and re-calculating (input only).
 * @var directCreate
 */
	bool							directCreate;

/**
 * @brief Rotation angle.
 * @var rotAngle
 */
	double							rotAngle;

/**
 * @brief Current box of the picture (when creating the picture, see the table below).
 * @var destBox
 */
	API_Box							destBox;

/**
 * @brief Original box of the picture.
 * @var origBox
 */
	API_Box							origBox;

/**
 * @brief Color depth of the image, see @ref API_ColorDepthID.
 * @var colorDepth
 */
	API_ColorDepthID				colorDepth;

/**
 * @brief Anchor point of core, see @ref API_AnchorID.
 * @var anchorPoint
 */
	API_AnchorID					anchorPoint;

/**
 * @brief Storage format of the picture.
 * @var storageFormat
 */
	API_PictureFormat 				storageFormat;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief Name of the picture as a Unicode string.
 * @var pictName
 */
	GS::uchar_t						pictName[API_UniLongNameLen];

/**
 * @brief MIME string identifying the image format (output only).
 * @var mime
 */
	char							mime[128];

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[6];

};


// =============================================================================
// CutPlane
//
// =============================================================================

#define	APICutPl_VectorHatch		1
#define	APICutPl_VectorShadow		4
#define	APICutPl_SunFrom3D			32

typedef enum {
	APIHorRange_Infinite = 0,
	APIHorRange_Limited,
	APIHorRange_ZeroDepth
} API_SegmentHorizontalRange;

typedef enum {
	APIVerRange_Infinite = 0,
	APIVerRange_Limited,
	APIVerRange_FitToZoneRange									// only for interior elevations
} API_SegmentVerticalRange;

typedef enum {
	APICutPl_ShowAll,											// show on all stories
	APICutPl_ShowOnOneStory,									// show only on one story
	APICutPl_ShowInRange,										// show on stories which are in the range
	APICutPl_ShowPartRange										// show on stories which are in or cut by the range
} API_CutPlaneShowType;

typedef enum {
	APICutPl_PenColor				= 1,
	APICutPl_MaterialColorShaded	= 2,
	APICutPl_MaterialColorNonShaded	= 3
} API_CutPlaneUncutSurfaceFillID;

/**
 * @brief Boundary display options.
 * @enum API_BoundaryDisplay
 * @ingroup Dialog
 */
typedef enum {
	APIBound_UncutContours			= 1,
	APIBound_NoContours				= 2,
	APIBound_OverrideContours		= 3

} API_BoundaryDisplay;

/**
 * @brief Define the status of the link between the Section/Elevation and the Floor Plan.
 * @enum API_CutPlanePlanConn
 * @ingroup Dialog
 * @remarks From Archicad 9 it's possible to set the status of the link between the Section/Elevation and the Floor Plan (see @ref API_CutPlaneType).
 */
typedef enum {
	APICutPl_Online					= 0,
	APICutPl_Offline				= 1,
	APICutPl_Drawing				= 2

} API_CutPlanePlanConn;

typedef enum {
	APICutPl_SHANone				= 0,
	APICutPl_SHADisplayOnly			= 1,
	APICutPl_SHAAll					= 2
} API_StoryHandleAppearance;

/**
 * @brief The enumeration of the available Section/Elevation markers appearing.
 * @enum API_CutPlaneMarkerShowType
 * @remarks The @ref API_CutPlaneMarkerShowType enum is used in the @ref API_CutPlaneType structure.
 */
typedef enum {
	APICutPl_ShowMiddleMarker		= 0,
	APICutPl_ShowWingMarkers		= 1

} API_CutPlaneMarkerShowType;


/**
 * @brief Represents one segment of a section/elevation/interior elevation.
 * @struct API_SectionSegment
 * @ingroup Element
 * @remarks Refer to the @ref ACAPI_Database_ChangeCurrentDatabase function to access and operate on the corresponding Section/Elevation/Interior Elevation database.
 * 			For cut plane element related memo data see the @ref ACAPI_Element_GetMemo function.
 * 			You can retrieve the Section Marker and the Story Handle Marker objects with the @ref ACAPI_Element_Get and @ref ACAPI_Element_GetMemo functions applying the corresponding marker indices stored in @ref API_CutPlaneType, but you cannot create or modify them directly. You can define and change marker objects only together with the cut plane element using @ref ACAPI_Element_CreateExt and @ref ACAPI_Element_ChangeExt respectively. You can access to the default settings of the markers with the @ref ACAPI_Element_GetDefaultsExt and @ref ACAPI_Element_ChangeDefaultsExt functions.
 * 			You can enumerate the drawing primitives of the Story Level lines of a given Section/Elevation database with the @ref ACAPI_DrawingPrimitive_DrawStoryControl database function.
 * 			From API 21 all 3 (main, depth, and marked distant) lines of a section segment can be "broken". The coordinates can be found in the element memo.
 */
struct API_SectionSegment {

/**
 * @brief Pen attribute index of the line.
 * @var linePen
 */
	short							linePen;

/**
 * @brief Pen attribute index of the text.
 * @var textPen
 */
	short							textPen;

/**
 * @brief Line type attribute index.
 * @var ltypeInd
 */
	API_AttributeIndex				ltypeInd;

/**
 * @brief Pen attribute index to be used in sections for contours (when not overridden by useElemPens).
 * @var sectPen
 */
	short							sectPen;

/**
 * @brief Pen attribute index to be used in sections for fills (when not overridden by useElemPens)
 * @var sectFillPen
 */
	short							sectFillPen;

/**
 * @brief Pen attribute index of the background fill of the cut elements (when not overridden by useElemPens)
 * @var sectFillBGPen
 */
	short							sectFillBGPen;

/**
 * @brief The story number to which vertMin and vertMax is relative to, when relativeToStory is true.
 * @var verticalRangeStoryBaseNumber
 */
	short							verticalRangeStoryBaseNumber;

/**
 * @brief Horizontal range of the segment:
 * 		  |API_SegmentHorizontalRange|Meaning|
 * 		  |--- |--- |
 * 		  |APIHorRange_Infinite|No limit on horizontal range.|
 * 		  |APIHorRange_Limited|Limit the horizontal range.|
 * 		  |APIHorRange_ZeroDepth|The depth of the section or elevation is 0.|
 *
 * @var horizRange
 */
	API_SegmentHorizontalRange		horizRange;

/**
 * @brief Vertical range of the segment:
 * 		  |API_SegmentVerticalRange|Meaning|
 * 		  |--- |--- |
 * 		  |APIVerRange_Infinite|No limit on vertical range.|
 * 		  |APIVerRange_Limited|Limit the vertical range; the limits are in vertMin and vertMax|
 * 		  |APIVerRange_FitToZoneRange|If a zone is present, then use the top and bottom level of the zone as a limit (for interior elevations only).|
 *
 * @var vertRange
 */
	API_SegmentVerticalRange		vertRange;

/**
 * @brief Marker size.
 * @var markerSize
 */
	double							markerSize;

/**
 * @brief Put marker on the beginning point.
 * @var begMark
 */
	bool							begMark;

/**
 * @brief Put marker on the end point.
 * @var endMark
 */
	bool							endMark;

/**
 * @brief Vertical limited range is relative to the home story or absolute to project zero.
 * @var relativeToStory
 */
	bool							relativeToStory;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool							filler_2;

/**
 * @brief Use the pens defined in the elements.
 * @var useElemPens
 */
	bool							useElemPens;

/**
 * @brief Show line at beginning point.
 * @var begLine
 */
	bool							begLine;

/**
 * @brief Show line at midlle point.
 * @var middleLine
 */
	bool							middleLine;

/**
 * @brief Show line at end point.
 * @var endLine
 */
	bool							endLine;

/**
 * @brief Length of the line.
 * @var lineLength
 */
	double							lineLength;

/**
 * @brief Vertical limitation - minimum height.
 * @var vertMin
 */
	double							vertMin;

/**
 * @brief Vertical limitation - maximum height.
 * @var vertMax
 */
	double							vertMax;

/**
 * @brief Name of the section as a Unicode string.
 * @var cutPlName
 */
	GS::uchar_t						cutPlName [API_UniLongNameLen];

/**
 * @brief The reference ID of the section in Unicode. If the text contains a '/' character, then the text is split
 * 		  between the beginning and end marks.
 * @var cutPlIdStr
 */
	GS::uchar_t						cutPlIdStr [API_UniLongNameLen];

/**
 * @brief Text size [mm] of marker text.
 * @var textSize
 */
	double							textSize;

/**
 * @brief Font attribute index for the marker text.
 * @var font
 */
	short							font;

/**
 * @brief The settings of the 3D view. It can take the following values:
 * 		  |Effect|Meaning|
 * 		  |--- |--- |
 * 		  |APICutPl_VectorHatch|Create vectorial 3D hatching|
 * 		  |APICutPl_VectorShadow|Create vectorial Sun shadows|
 * 		  |APICutPl_SunFrom3D|The parameters of the Sun are the same as in the 3D window|
 *
 * @var effectBits
 */
	short							effectBits;

/**
 * @brief Fill attribute index of the shadow's fill.
 * @var shadFill
 */
	API_AttributeIndex				shadFill;

/**
 * @brief Pen attribute index of the shadow's fill.
 * @var shadFillPen
 */
	short							shadFillPen;

/**
 * @brief Background pen attribute index of the shadow's fill.
 * @var shadFillBGPen
 */
	short							shadFillBGPen;

/**
 * @brief Line type of the horizontal limit line.
 * @var limitLtypeInd
 */
	API_AttributeIndex				limitLtypeInd;

/**
 * @brief Line pen of the horizontal limit line.
 * @var limitLinePen
 */
	short							limitLinePen;

/**
 * @brief Continuous if true, otherwise is segmented.
 * @var continuous
 */
	bool							continuous;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	bool							filler_3[5];

/**
 * @brief Custom sun azimuth relative to the cut plane.
 * @var sunAngXY
 */
	double							sunAngXY;

/**
 * @brief Custom sun altitude relative to the cut plane.
 * @var sunAngZ
 */
	double							sunAngZ;


/**
 * @brief Guid of the Section Marker object at the starting point of the section line.
 * @var begMarkerId
 */
	API_Guid						begMarkerId;

/**
 * @brief Guid of the Section Marker object at the center point of the section line.
 * @var midMarkerId
 */
	API_Guid						midMarkerId;

/**
 * @brief Guid of the Section Marker object at the end point of the section line.
 * @var endMarkerId
 */
	API_Guid						endMarkerId;


/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	short							filler_4;

/**
 * @brief Use one pen for all elements in the Section/Elevation view.
 * @var modelUseElemPen
 */
	bool							modelUseElemPen;

/**
 * @brief Use one pen for all elements in distant area of the Section/Elevation view.
 * @var distAreaUseElemPen
 */
	bool							distAreaUseElemPen;

/**
 * @brief Foreground pen of model uncut surface fill.
 * @var modelElemPen
 */
	short							modelElemPen;

/**
 * @brief Pen attribute index of elements in distant area of the Section/Elevation view.
 * @var distAreaElemPen
 */
	short							distAreaElemPen;

/**
 * @brief Fill attribute index for Shadow Polygons used in the Section/Elevation view.
 * @var distAreaShadFill
 */
	API_AttributeIndex				distAreaShadFill;

/**
 * @brief Fill pen index for Shadow Polygons used in the Section/Elevation view.
 * @var distAreaShadFillPen
 */
	short							distAreaShadFillPen;

/**
 * @brief Fill background pen index for Shadow Polygons used in the Section/Elevation view.
 * @var distAreaShadFillBGPen
 */
	short							distAreaShadFillBGPen;

/**
 * @brief The method for displaying fills of uncut surfaces in the distant area of the Section/Elevation
 * 		  (effective if `distAreaUseUncutSurfFill` is true)
 * 		  |API_CutPlaneUncutSurfaceFillID|Meaning|
 * 		  |--- |--- |
 * 		  |APICutPl_PenColor|Apply uniform pencolor to the fills of all uncut surfaces|
 * 		  |APICutPl_MaterialColorShaded|Display uncut fills using own material colors of the elements with shading|
 * 		  |APICutPl_MaterialColorNonShaded|Display uncut fills using own material colors of the elements without shading|
 *
 * @var distAreaUncutSurfFillType
 */
	API_CutPlaneUncutSurfaceFillID	distAreaUncutSurfFillType;

/**
 * @brief Pencolor to apply to the fills of all uncut surfaces in the distant area of the Section/Elevation (if uniform pencolor is selected in the Distant Area Options).
 * @var distAreaUncutSurfBGPen
 */
	short							distAreaUncutSurfBGPen;

/**
 * @brief Apply fills to uncut surfaces displayed in the distant area of the Section/Elevation.
 * @var distAreaUseUncutSurfFill
 */
	bool							distAreaUseUncutSurfFill;

/**
 * @brief Mark distant area.
 * @var markedDistArea
 */
	bool							markedDistArea;


/**
 * @brief The method for displaying fills of uncut surfaces (Model Effects) of the Section/Elevation (effective if `modelUseUncutSurfFill` is true). See the @c API_CutPlaneUncutSurfaceFillID values at the distAreaUncutSurfFillType parameter.
 * @var modelUncutSurfFillType
 */
	API_CutPlaneUncutSurfaceFillID	modelUncutSurfFillType;

/**
 * @brief Pencolor to apply to the fills of all uncut surfaces in the Section/Elevation (if uniform pencolor is selected in the Model Effects panel).
 * @var modelUncutSurfBGPen
 */
	short							modelUncutSurfBGPen;

/**
 * @brief Apply fills to uncut surfaces displayed in the Section/Elevation.
 * @var modelUseUncutSurfFill
 */
	bool							modelUseUncutSurfFill;

/**
 * @brief Set transparency of the Section/Elevation.
 * @var transparency
 */
	bool							transparency;


/**
 * @brief Number of main line coordinates in memo.
 * @var nMainCoord
 */
	UInt32							nMainCoord;

/**
 * @brief Number of marked distant area line coordinates in memo.
 * @var nDistCoord
 */
	UInt32							nDistCoord;

/**
 * @brief Number of depth line coordinates in memo.
 * @var nDepthCoord
 */
	UInt32							nDepthCoord;

/**
 * @brief Section is in drawing mode.
 * @var drawingModeON
 */
	bool							drawingModeON;


/**
 * @brief The section/elevation/interior elevation window is opened.
 * @var windOpened
 */
	bool							windOpened;

/**
 * @brief Turned off or active.
 * @var active
 */
	bool							active;

/**
 * @brief Is this segment a source marker? (output only/no default)
 * @var sourceMarker
 */
	bool							sourceMarker;

/**
 * @brief Reserved for later use.
 * @var filler_5
 */
	bool							filler_5[4];

/**
 * @brief Database ID to switch to (see @ref API_DatabaseUnId).
 * @var databaseID
 */
	API_DatabaseUnId				databaseID;


/**
 * @brief Current plan connectivity (read only). Show the state of the Section/Elevation window. This member will pick up the value of `intPlanConn` when the Section/Elevation window was activated. The Section/Elevation will be regenerated from the model if it's necessary.
 * @var currPlanConn
 */
	API_CutPlanePlanConn			currPlanConn;

/**
 * @brief Intended plan connectivity. Show the state of the element on the plan. It could be different from the state of its Section/Elevation window (currPlanConn).
 * @var intPlanConn
 */
	API_CutPlanePlanConn			intPlanConn;


/**
 * @brief Use the solid operations on zones (for interior elevations only).
 * @var solidOperationsOnZones
 */
	bool							solidOperationsOnZones;

/**
 * @brief Exclude view blocking walls (for interior elevations only).
 * @var exclBlockWalls
 */
	bool							exclBlockWalls;

/**
 * @brief Show cut elements (for interior elevations only).
 * @var showCutElements
 */
	bool							showCutElements;

/**
 * @brief Relevant elems are detected only by limit lines (used only for Interior Elevation segments).
 * @var byLimitLines
 */
	bool							byLimitLines;

/**
 * @brief Reserved for later use.
 * @var filler_6
 */
	bool							filler_6[4];


/**
 * @brief Options for displaying story lines on the Section/Elevation
 * 		  |API_StoryHandleAppearance|Meaning|
 * 		  |--- |--- |
 * 		  |APICutPl_SHANone|Story lines are not displayed on the Section/Elevation|
 * 		  |APICutPl_SHADisplayOnly|Story lines appear only on-screen, but are not displayed on the printed output|
 * 		  |APICutPl_SHAAll|Story lines appear both on screen and on the printed output|
 *
 * @var shAppearance
 */
	API_StoryHandleAppearance		shAppearance;

/**
 * @brief Line type index of the Story Level lines.
 * @var shLineType
 */
	API_AttributeIndex				shLineType;

/**
 * @brief Pencolor index of the Story Level lines.
 * @var shLinePen
 */
	short							shLinePen;

/**
 * @brief Pencolor index of the Story Handle Markers (effective when not overridden by shUseSymbolPens).
 * @var shMarkerPen
 */
	short							shMarkerPen;

/**
 * @brief Use own colors of the Story Handle Marker object.
 * @var shUseSymbolPens
 */
	bool							shUseSymbolPens;

/**
 * @brief Display the Story Handle Markers on the left side.
 * @var shLeftMarkerOn
 */
	bool							shLeftMarkerOn;

/**
 * @brief Display the Story Handle Markers on the right side.
 * @var shRightMarkerOn
 */
	bool							shRightMarkerOn;

/**
 * @brief Story handle line is on or off.
 * @var shLineOn
 */
	bool							shLineOn;

/**
 * @brief The offset of the Story Level line beyond the limits of the Section/Elevation on the left side.
 * @var shLeftMarkerOffset
 */
	double							shLeftMarkerOffset;

/**
 * @brief The offset of the Story Level line beyond the limits of the Section/Elevation on the right side.
 * @var shRightMarkerOffset
 */
	double							shRightMarkerOffset;

/**
 * @brief The guid of the Story Handle Marker object element instance (API_ObjectType).
 * @var shSymbolId
 */
	API_Guid						shSymbolId;

/**
 * @brief The font index of the Story Handle Marker.
 * @var shMarkerFont
 */
	short							shMarkerFont;

/**
 * @brief The text style of the Story Handle Marker.
 * @var shMarkerFaceBits
 */
	unsigned short					shMarkerFaceBits;

/**
 * @brief The text size of the Story Handle Marker in mm.
 * @var shMarkerTextSize
 */
	double							shMarkerTextSize;

/**
 * @brief The size of the Story Handle Marker in mm.
 * @var shMarkerSize
 */
	double							shMarkerSize;

/**
 * @brief Boundary contour display mode. The possible values are: @c APIBound_UncutContours, @c APIBound_NoContours, and @c APIBound_OverrideContours.
 * @var boundaryDisplay
 */
	API_BoundaryDisplay				boundaryDisplay;

/**
 * @brief Boundary contour pen.
 * @var boundaryPen
 */
	short							boundaryPen;

/**
 * @brief Reserved for later use.
 * @var filler_7
 */
	short							filler_7[3];

/**
 * @brief Boundary contour line type.
 * @var boundaryLineType
 */
	API_AttributeIndex				boundaryLineType;

/**
 * @brief Used for link the segment to an edge of the Interior Elevation.
 * @var iePolygonEdge
 */
	API_Sector						iePolygonEdge;


/**
 * @brief Used only for Interior Elevation creation.
 * @var ieCreationSegmentHorizontalOffset
 */
	double							ieCreationSegmentHorizontalOffset;

/**
 * @brief Used only for Interior Elevation creation.
 * @var ieCreationSegmentDepth
 */
	double							ieCreationSegmentDepth;

};

// =============================================================================
// MarkerLinkData
//
// =============================================================================
typedef enum {
	NotReferred			= 0,
	ReferredToViewPoint	= 1,
	ReferredToView		= 2,
	ReferredToDrawing	= 3
} API_ReferringLevel;

/**
 * @brief This type manifestates as a "linkedMarker" named variable in the detail/worksheet, section and elevation API types, and used to set the referring properties of the marker.
 * @ingroup Element
 * @struct API_MarkerLinkDataType
 */
struct API_MarkerLinkDataType {

/**
 * @brief Guid of the referred view. (Only if the marker refers to a view, otherwise this variable does not carry any useful information.)
 * @var referredView
 */
	API_Guid			referredView;

/**
 * @brief Guid of the referred drawing. (Only if the marker refers to a drawing, otherwise this variable does not carry any useful information.) You should use the drawingGuid member of one instance of @ref API_DrawingType if you want to create a new element with markerLinkData...
 * @var referredDrawing
 */
	API_Guid			referredDrawing;

/**
 * @brief Guid of the referred view point. (Only if the marker refers to a view point, otherwise this variable does not carry any useful information.)
 * @var referredPMViewPoint
 */
	API_Guid			referredPMViewPoint;

/**
 * @brief If it's true, the marker is a source marker.
 * @var sourceMarker
 */
	bool				sourceMarker;

/**
 * @brief If it's true, the marker is an unlinked one. The other variables don't represent any meaningful information in this case. If sourceMarker and customMarker are both false, then the marker is a linked one.
 * @var customMarker
 */
	bool				customMarker;

/**
 * @brief This boolean variable has meaning if the marker is a source or linked marker.
 * @var referToDrawing
 */
	bool				referToDrawing;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool				filler_1;

/**
 * @brief This variable carries information if the marker is a source or a linked marker, namely it determindes the referred type. Based on this info it can be decided, that which guid should be used of the three above. The type and the values of this variable are the following: typedef enum { NotReferred = 0, ReferredToViewPoint = 1, ReferredToView = 2, ReferredToDrawing = 3 } @c API_ReferringLevel
 * @var referringLevel
 */
	API_ReferringLevel	referringLevel;


/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32				filler_2[8];

};

/**
 * @brief Represents a section element.
 * @struct API_CutPlaneType
 * @ingroup Element
 * @remarks Most of the original structure members are now in @ref API_SectionSegment. See also @ref API_ElevationType.
 */
struct API_CutPlaneType {
/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;

/**
 * @brief Stories to show cutplane on:
 * 		  |API_CutPlaneShowType|Meaning|
 * 		  |--- |--- |
 * 		  |APICutPl_ShowAll|Show on All stories|
 * 		  |APICutPl_ShowOnOneStory|Show only on one story, setting in storyToShowOn|
 * 		  |APICutPl_ShowInRange|Show on stories which are in the range|
 * 		  |APICutPl_ShowPartRange|Show on stories which are in or cut by the range|
 * @var cutPlShow
 */
	API_CutPlaneShowType			cutPlShow;

/**
 * @brief Story to show cutplane on, if cutPlShow is @c APICutPl_ShowOnOneStory.
 * @var storyToShowOn
 */
	short							storyToShowOn;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief Section segment.
 * @var segment
 */
	API_SectionSegment				segment;

/**
 * @brief Show side markers or middle marker.
 * @var markerShow
 */
	API_CutPlaneMarkerShowType		markerShow;

/**
 * @brief Link information for segments, elevations, details and worksheets.
 * @var linkData
 */
	API_MarkerLinkDataType			linkData;


/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2;
};

/**
 * @brief Represents a elevation element.
 * @ingroup Element
 * @remarks Most of the original structure members are now in @ref API_SectionSegment. See also @ref API_CutPlaneType.
 */
using API_ElevationType = API_CutPlaneType;

/**
 * @brief An iterior elevation element.
 * @ingroup Element
 * @remarks This structure represents an interior elevation element. The section segment information is stored in the element memo.
 */
struct API_InteriorElevationType {

/**
 * @brief The element header.
 * @var head
 */
	API_Elem_Head					head;


/**
 * @brief Stories to show cutplane on.
 * @var cutPlShow
 */
	API_CutPlaneShowType			cutPlShow;

/**
 * @brief Story to show cutplane on, if cutPlShow is @c APICutPl_ShowOnOneStory.
 * @var storyToShowOn
 */
	short							storyToShowOn;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;


/**
 * @brief Used to get and set the defaults; real segments are in the memo.
 * @var segment
 */
	API_SectionSegment				segment;


/**
 * @brief Show the common marker.
 * @var useCommonMarker
 */
	bool							useCommonMarker;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool							filler_2[7];

/**
 * @brief Guid of the common marker object.
 * @var markerGuid
 */
	API_Guid						markerGuid;

/**
 * @brief Pen of the common marker.
 * @var markerPen
 */
	short							markerPen;

/**
 * @brief Font of the common marker.
 * @var markerFont
 */
	short							markerFont;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3;

/**
 * @brief Size of the common marker.
 * @var markerSize
 */
	double							markerSize;

/**
 * @brief Size of the common marker's text.
 * @var markerTextSize
 */
	double							markerTextSize;


/**
 * @brief Number of segments in the memo.
 * @var nSegments
 */
	UInt32							nSegments;

/**
 * @brief Total number of segment line coordinates.
 * @var nLineCoords
 */
	Int32							nLineCoords;


/**
 * @brief Polyline of the connected segments.
 * @var poly
 */
	API_Polygon						poly;


/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	Int32							filler_4[6];

};

// =============================================================================
// Camera
//
// =============================================================================

#define API_Projection_YZ			1							// projMod
#define API_Projection_XZ			2
#define API_Projection_XY			3
#define API_Projection_Frontal		4
#define API_Projection_Monometric	5
#define API_Projection_Isometric	6
#define API_Projection_Dimetric		7
#define API_Projection_Perspective	8
#define API_Projection_Bottom		9
#define API_Projection_FrontalB		10
#define API_Projection_MonometricB	11
#define API_Projection_IzometricB	12
#define API_Projection_DimetricB	13
#define API_Projection_Parallel		14
#define API_Projection_FreeAx		15

/**
 * @brief Sun position options for calculating Sun's angles.
 * @enum API_SunAngleSettings_SunPositionOption
 * @ingroup Dialog
 * @remarks The options correspond to the different Sun position setting choices in the "3D Projection Settings..." dialog of Archicad.
 */
typedef enum {
	API_SunPosition_GivenByAngles	= 0,
	API_SunPosition_GivenByDate		= 1

} API_SunAngleSettings_SunPositionOption;


/**
 * @brief Sun angle settings.
 * @struct API_SunAngleSettings
 * @ingroup Dialog
 * @remarks This structure corresponds to Sun parameters set in the "3D Projection Settings..." dialog of Archicad.
 */
struct API_SunAngleSettings {

/**
 * @brief rotation angle of the Sun around the target
 * @var sunAzimuth
 */
	double									sunAzimuth;

/**
 * @brief Sun's altitude
 * @var sunAltitude
 */
	double									sunAltitude;

/**
 * @brief this enumeration tells if the azimuth and altitude values have to be considered or the Sun position is given with a date (project location-dependent!)
 * @var sunPosOpt
 */
	API_SunAngleSettings_SunPositionOption	sunPosOpt;

/**
 * @brief date's year.
 * @var year
 */
	unsigned short							year;

/**
 * @brief date's month
 * @var month
 */
	unsigned short							month;

/**
 * @brief date's day
 * @var day
 */
	unsigned short							day;

/**
 * @brief date's hour
 * @var hour
 */
	unsigned short							hour;

/**
 * @brief date's minute
 * @var minute
 */
	unsigned short							minute;

/**
 * @brief date's second
 * @var second
 */
	unsigned short							second;

/**
 * @brief this option controls daylight saving
 * @var summerTime
 */
	bool									summerTime;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	bool									filler;
};

/**
 * @brief Parallel projection parameters.
 * @struct API_AxonoPars
 * @ingroup View
 * @remarks This structure corresponds to parameters set in the "3D Projection Settings..." dialog of Archicad, when a parallel view is selected.
 * 			Refer to the @ref ACAPI_View_Get3DProjectionSets function to get the actual projection parameters.
 */
struct API_AxonoPars {

/**
 * @brief rotation angle of the camera around the target
 * @var azimuth
 */
	double							azimuth;

/**
 * @brief Sun's angle settings
 * @var sunAngSets
 */
	API_SunAngleSettings			sunAngSets;

/**
 * @brief projection type selected
 * @var projMod
 */
	short							projMod;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2;


/**
 * @brief the transformation matrix to calculate projected coordinates
 * @var tranmat
 */
	API_Tranmat						tranmat;

/**
 * @brief the inverse transformation matrix to calculate model coordinates from projected ones
 * @var invtranmat
 */
	API_Tranmat						invtranmat;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	double							filler_3[8];

};

/**
 * @brief Perspective projection parameters.
 * @struct API_PerspPars
 * @ingroup Dialog
 * @remarks This structure corresponds to parameters set in the "3D Projection Settings..." dialog of Archicad, when a perspective view is selected.
 * 			Refer to the @ref ACAPI_View_Get3DProjectionSets function to get the actual projection parameters.
 */
struct API_PerspPars {

/**
 * @brief rotation angle of the camera around the target
 * @var azimuth
 */
	double							azimuth;

/**
 * @brief Sun's angle settings
 * @var sunAngSets
 */
	API_SunAngleSettings			sunAngSets;

/**
 * @brief angle of the camera view cone
 * @var viewCone
 */
	double							viewCone;

/**
 * @brief roll angle of the camera
 * @var rollAngle
 */
	double							rollAngle;

/**
 * @brief distance of the camera and the target
 * @var distance
 */
	double							distance;

/**
 * @brief Z coordinate of camera position
 * @var cameraZ
 */
	double							cameraZ;

/**
 * @brief Z coordinate of target position
 * @var targetZ
 */
	double							targetZ;

/**
 * @brief Two-point perspective mode
 * @var isTwoPointPersp
 */
	bool							isTwoPointPersp;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	bool							filler_0[7];

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	double							filler_1[7];


/**
 * @brief X and Y coordinate of camera position
 * @var pos
 */
	API_Coord						pos;

/**
 * @brief X and Y coordinate of target position
 * @var target
 */
	API_Coord						target;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	double							filler_2[8];

};

/**
 * @brief Parameters of a perspective camera.
 * @struct API_PerspCamPars
 * @ingroup Element
 */
struct API_PerspCamPars {

/**
 * @brief Perspective projection settings of the camera.
 * @var persp
 */
	API_PerspPars					persp;

/**
 * @brief Number of the frames to wait here.
 * @var waitFrames
 */
	short							waitFrames;

/**
 * @brief Pen attribute index for the camera.
 * @var pen
 */
	short							pen;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;


/**
 * @brief Guid of the previous camera in the same camera set (APINULLGuid if no previous camera).
 * @var prevCam
 */
	API_Guid						prevCam;

/**
 * @brief Guid of the following camera in the same camera set (APINULLGuid if no following camera).
 * @var nextCam
 */
	API_Guid						nextCam;

/**
 * @brief Bezier direction length previous.
 * @var lenPrev
 */
	double							lenPrev;

/**
 * @brief Bezier direction length next.
 * @var lenNext
 */
	double							lenNext;

/**
 * @brief Bezier direction angle (radian).
 * @var dirAng
 */
	double							dirAng;

/**
 * @brief Active in the path?
 * @var active
 */
	bool							active;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool							filler_2[7];

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3[6];

};

/**
 * @brief Describes a link for cameras.
 * @struct API_LinkType
 * @ingroup Element
 */
struct API_LinkType {

/**
 * @brief Index of the target camera.
 * @var camInd
 */
	Int32							camInd;

/**
 * @brief Status of the target camera. (Active?)
 * @var status
 */
	short							status;

/**
 * @brief Pen attribute index.
 * @var pen
 */
	short							pen;

/**
 * @brief Connection point coordinates between the current camera and the one defined by camInd.
 * @var connPoint
 */
	API_Coord						connPoint;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	double							filler_2[4];

};

/**
 * @brief Represents a single camera.
 * @struct API_CameraType
 * @ingroup Element
 */
struct API_CameraType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;

/**
 * @brief This camera belongs to this camera set.
 * @var camSetGuid
 */
	API_Guid						camSetGuid;

/**
 * @brief Perspective camera parameters.
 * @var perspCam
 */
	API_PerspCamPars				perspCam;

};


// =============================================================================
// CamSet
//
// =============================================================================

/**
 * @brief Represents a perspective camera set.
 * @struct API_PersCamSetPars
 * @ingroup Element
 * @remarks These fields correspond to the fields of the Path Options dialog.
 */
struct API_PersCamSetPars {

/**
 * @brief Open or closed animation path?
 * @var openedPath
 */
	bool							openedPath;

/**
 * @brief Generate the in-between frames along polygonal or Bezier animation path?
 * @var bezierPath
 */
	bool							bezierPath;

/**
 * @brief Generate the in-between frames along a straight line or a smooth curve?
 * @var smoothTarget
 */
	bool							smoothTarget;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	short							filler_2;

/**
 * @brief Pen attribute index of the camera and the path.
 * @var pen
 */
	short							pen;

/**
 * @brief Number of the in-between frames.
 * @var inFrames
 */
	Int32							inFrames;

/**
 * @brief First camera index in slide.
 * @var showFrom
 */
	Int32							showFrom;

/**
 * @brief Last camera index in slide.
 * @var showTo
 */
	Int32							showTo;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3;

};

/**
 * @brief Represents a camera set.
 * @struct API_CamSetType
 * @ingroup Element
 */
struct API_CamSetType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;

/**
 * @brief Name of the camera set as a Unicode string.
 * @var name
 */
	GS::uchar_t						name [API_UniLongNameLen];

/**
 * @brief Parameters of the perspective camera.
 * @var perspPars
 */
	API_PersCamSetPars				perspPars;


/**
 * @brief Is this the active camera set?
 * @var active
 */
	bool							active;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool							filler_2[7];

/**
 * @brief First camera in the camera set.
 * @var firstCam
 */
	API_Guid						firstCam;

/**
 * @brief Actual camera in the camera set.
 * @var actCam
 */
	API_Guid						actCam;

};


// =============================================================================
// Drawing
//
// =============================================================================

/**
 * @brief Specifies how the name of the drawing is assembled.
 * @enum API_NameTypeValues
 * @ingroup Element
 * @remarks The options correspond to the different values in the Drawing Name popup on the Identification tabpage of the Drawing Settings dialog.
 */
typedef enum {
	APIName_ViewOrSrcFileName		= 0,
	APIName_ViewIdAndName			= 1,
	APIName_CustomName				= 2

} API_NameTypeValues;

/**
 * @brief Numbering method options of a drawing element.
 * @enum API_NumberingTypeValues
 * @ingroup Element
 * @remarks The options correspond to the different values in the Drawing ID popup on the Identification tabpage of the Drawing Settings dialog.
 */
typedef enum {
	APINumbering_ByLayout			= 0,
	APINumbering_ByViewId			= 1,
	APINumbering_CustomNum			= 2

} API_NumberingTypeValues;

/**
 * @brief Specifies output color transformation for drawing elements.
 * @enum API_ColorModeValues
 * @ingroup Element
 */
typedef enum {
	APIColorMode_OriginalColors		= 0,
	APIColorMode_BlackAndWhite		= 1,
	APIColorMode_GrayScale			= 2

} API_ColorModeValues;

/**
 * @brief Specifies which pen table a drawing element uses.
 * @enum API_PenTableUsageModeValues
 * @ingroup Element
 */
typedef enum {
	APIPenTableUsageMode_UseOwnPenTable		= 0,
	APIPenTableUsageMode_UseModelPenTable	= 1,
	APIPenTableUsageMode_UsePenTableIndex	= 2

} API_PenTableUsageModeValues;

/**
 * @brief Determines what is shown on the preview the drawing title.
 * @enum API_TitlePreviewModes
 * @ingroup Element
 * @remarks The values correspond to the different settings on the Title tabpage of the Drawing Settings dialog.
 * 			Can be @c APITitlePreviewMode_DrawingWithTitle or @c APITitlePreviewMode_TitleOnly
 */
typedef enum {
	APITitlePreviewMode_DrawingWithTitle	= 0,
	APITitlePreviewMode_TitleOnly			= 1

} API_TitlePreviewModes;

/**
 * @brief Specifies the drawing's title object.
 * @struct API_DrawingTitle
 * @ingroup Element
 * @remarks Drawing titles are now object based elements from Archicad 10.
 */
struct API_DrawingTitle {

/**
 * @brief Library part index of the title.
 * @var libInd
 */
	Int32							libInd;

/**
 * @brief Show the title preview with or without the drawing itself (see @ref API_TitlePreviewModes).
 * @var previewMode
 */
	API_TitlePreviewModes			previewMode;

/**
 * @brief Use the fonts and style set on the title tabpage.
 * @var useUniformTextFormat
 */
	bool							useUniformTextFormat;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	bool							filler_0;

/**
 * @brief Title common text font ID.
 * @var font
 */
	short							font;

/**
 * @brief Plain, bold, italic, underline.
 * @var faceBits
 */
	unsigned short					faceBits;

/**
 * @brief Title common text pen.
 * @var textPen
 */
	short							textPen;

/**
 * @brief Title text size.
 * @var textSize
 */
	double							textSize;

/**
 * @brief The title object is flipped.
 * @var flipped
 */
	bool							flipped;

/**
 * @brief Use the pens set on the title tabpage.
 * @var useUniformSymbolPens
 */
	bool							useUniformSymbolPens;

/**
 * @brief Title common pen.
 * @var pen
 */
	short							pen;

/**
 * @brief Guid of title element (the placed object).
 * @var guid
 */
	API_Guid						guid;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1[2];

};

/**
 * @brief Represents a drawing element.
 * @struct API_DrawingType
 * @ingroup Element
 * @remarks Drawing elements can be placed both in the model space (except which come from an internal view) and onto layouts.
 * 			The 2D elements which appear in the drawing are stored in the drawingData field in the @ref API_ElementMemo.
 * 			This data structure has been rewritten from scratch; it has very little resemblance to the original data structure in PlotMaker.
 */
struct API_DrawingType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;


/**
 * @brief Custom drawing name if nameType is set to @c APIName_CustomName.
 * @var name
 */
	char							name[256];

/**
 * @brief Type of the drawing name (see @ref API_NameTypeValues).
 * @var nameType
 */
	API_NameTypeValues				nameType;

/**
 * @brief Numbering options (see @ref API_NumberingTypeValues).
 * @var numberingType
 */
	API_NumberingTypeValues			numberingType;

/**
 * @brief Custom drawing number if numberingType is set to @c APINumbering_CustomNum.
 * @var customNumber
 */
	char							customNumber[256];

/**
 * @brief The drawing is included in the numbering sequence.
 * @var isInNumbering
 */
	bool							isInNumbering;

/**
 * @brief Updating method: manual or automatic.
 * @var manualUpdate
 */
	bool							manualUpdate;

/**
 * @brief Drawing is stored in the project file - output only.
 * @var storedInProject
 */
	bool							storedInProject;

/**
 * @brief Internal parameter used by the Interactive Element Schedule add-on - output only.
 * @var isScheduleAdjusted
 */
	bool							isScheduleAdjusted;

/**
 * @brief Drawing is splitted to more layout (page). It can be true when the source is an Interactive Shedule view.
 * @var isMultiPageDrawing
 */
	bool							isMultiPageDrawing;

/**
 * @brief When true, the Scale of this Drawing will be included in "Drawing Scale" and "Original Scale" AutoTexts, in "Drawing Scales" field of Layout type Project Indexes, in "Drawing Scale" field of Drawing type Project Indexes. Include this Drawing in "Drawing Scale", "Magnification" and "Original Scale" AutoTexts.
 * @var includeInAutoTextsAndIES
 */
	bool							includeInAutoTextsAndIES;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[2];


/**
 * @brief Angle of the placed drawing in radian.
 * @var angle
 */
	double							angle;

/**
 * @brief Ratio of drawing size and original size.
 * @var ratio
 */
	double							ratio;

/**
 * @brief Rasterize PDF at this dpi.
 * @var rasterizeDPI
 */
	double							rasterizeDPI;

/**
 * @brief Scale of the view (e.g. 0.002 for 1:500) - output only.
 * @var drawingScale
 */
	double							drawingScale;

/**
 * @brief Parent scale while drawing creation (used in updating image and pdf type drawings) - output only.
 * @var parentOriginalScale
 */
	double							parentOriginalScale;

/**
 * @brief Placement reference by bounding box node (relevant only if not useOwnOrigoAsAnchor).
 * @var anchorPoint
 */
	API_AnchorID					anchorPoint;

/**
 * @brief Produce B W or grayscale output (see @ref API_ColorModeValues).
 * @var colorMode
 */
	API_ColorModeValues				colorMode;

/**
 * @brief Determines which pen table will be used by the drawing (see @ref API_PenTableUsageModeValues)
 * @var penTableUsageMode
 */
	API_PenTableUsageModeValues		penTableUsageMode;

/**
 * @brief Index of the pen table to use (if penTableUsageMode is set to @c APIPenTableUsageMode_UsePenTableIndex.
 * @var penTableIndex
 */
	API_AttributeIndex				penTableIndex;

/**
 * @brief Use drawing's own origo as placement reference point.
 * @var useOwnOrigoAsAnchor
 */
	bool							useOwnOrigoAsAnchor;

/**
 * @brief The background of the drawing should be transparent.
 * @var isTransparentBk
 */
	bool							isTransparentBk;

/**
 * @brief Drawing is clipped with frame polygon.
 * @var isCutWithFrame
 */
	bool							isCutWithFrame;

/**
 * @brief Show drawing border?
 * @var hasBorderLine
 */
	bool							hasBorderLine;

/**
 * @brief Line type of the border.
 * @var borderLineType
 */
	API_AttributeIndex				borderLineType;

/**
 * @brief Pen attribute index of the border.
 * @var borderPen
 */
	short							borderPen;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool							filler_2[2];

/**
 * @brief Thickness of the border in 'm'.
 * @var borderSize
 */
	double							borderSize;


/**
 * @brief Drawing title.
 * @var title
 */
	API_DrawingTitle				title;


/**
 * @brief Boundary box.
 * @var bounds
 */
	API_Box							bounds;

/**
 * @brief Coordinate of the placed drawing's origin on the layout.
 * @var pos
 */
	API_Coord						pos;

/**
 * @brief Polygon on the layout: the clip polygon if isCutWithFrame is true else the bounding box in polygon format
 * @var poly
 */
	API_Polygon						poly;


/**
 * @brief Sort index.
 * @var sortIndex
 */
	UInt32							sortIndex;

/**
 * @brief Not used yet.
 * @var linkUId
 */
	Int32							linkUId;

/**
 * @brief GUID of the drawing for identification by autotext.
 * @var drawingGuid
 */
	API_Guid						drawingGuid;

/**
 * @brief If isCutWithFrame is true than it is the offset of the model. It will modify also the pos of the drawing.
 * @var modelOffset
 */
	API_Coord						modelOffset;

/**
 * @brief If the drawing is clipped with frame polygon offset is equal to pos else the subvector of pos and the coordinate of anchor. Output only parameter.
 * @var offset
 */
	API_Vector						offset;


/**
 * @brief Offset of the next page's position, when isMultiPageDrawing set.
 * @var pageOffset
 */
	API_Coord						pageOffset;

/**
 * @brief Number of pages in x direction, when isMultiPageDrawing set.
 * @var pageNumberX
 */
	UInt32							pageNumberX;

/**
 * @brief Number of pages in y direction, when isMultiPageDrawing set.
 * @var pageNumberY
 */
	UInt32							pageNumberY;


};


// =============================================================================
// Section Elem
// (virtual symbol created from the plan's construction elements)
// =============================================================================

/**
 * @brief Describes an element in the section window.
 * @struct API_SectElemType
 * @ingroup Element
 * @since Archicad 26
 * @remarks This structure represents elements in the section window, which originally were created in the 2D or 3D window, and are visible in the current section window.
 * 			From version 26 the type of the parentID member was changed into @ref API_ElemType.
 */
struct API_SectElemType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;


/**
 * @brief Parent elem type.
 * @var parentType
 */
	API_ElemType					parentType;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief Parent elem GUID.
 * @var parentGuid
 */
	API_Guid						parentGuid;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[6];

/**
 * @brief GUID of owner curtain wall it the parent is a curtain wall subelem (frame, panel, junction or accessory). APINULLGuid in all other cases.
 * @var ownerGuid
 */
	API_Guid						ownerGuid;

};


// =============================================================================
// Detail
//
// =============================================================================

/**
 * @brief Represents a detail/worksheet (detail/worksheet mark).
 * @struct API_DetailType
 * @ingroup Element
 * @remarks Refer to the @ref ACAPI_Database_ChangeCurrentDatabase function to access and operate on the
 * 			corresponding Detail/Worksheet database. For detail related memo data see the @ref ACAPI_Element_GetMemo
 * 			function, and @ref API_WorksheetType. Note that the origin of the coordinate system of a
 * 			detail/worksheet database corresponds to the reference point location of the detail/worksheet element on the
 * 			floor plan; thus elements on the detail/worksheet databases are offset by `pos` from their original location
 * 			on the floor plan. Suppose the referencing detail/worksheet element was placed on a section/elevation
 * 			window. In that case, the `y` coordinate on the detail/worksheet database equals to the `y` value of the section
 * 			database to help working with the vertical (elevation) level. In this case, the `pos.y` data is ignored.
 */
struct API_DetailType {
/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;

/**
 * @brief Pen color attribute index of the detail's contour.
 * @var pen
 */
	short							pen;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief Line type attribute index of the detail's contour.
 * @var ltypeInd
 */
	API_AttributeIndex				ltypeInd;

/**
 * @brief Coordinate of the base point. (See remarks)
 * @var pos
 */
	API_Coord						pos;

/**
 * @brief The rotation angle (radian) of the marker symbol.
 * @var angle
 */
	double							angle;

/**
 * @brief Guid of the marker symbol.
 * @var markId
 */
	API_Guid						markId;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2;

/**
 * @brief Name of the detail/worksheet (Unicode string, UTF-8 encoding).
 * @var detailName
 */
	GS::uchar_t						detailName[API_UniLongNameLen];

/**
 * @brief Reference ID of the detail/worksheet (Unicode string, UTF-8 encoding). If the text contains a '/' character,
 * 		  then the text is split between the beginning and end marks.
 * @var detailIdStr
 */
	GS::uchar_t						detailIdStr[API_UniLongNameLen];

/**
 * @brief Marker symbol is always horizontal?
 * @var horizontalMarker
 */
	bool							horizontalMarker;

/**
 * @brief Side (detail/worksheet) window is opened?
 * @var windOpened
 */
	bool							windOpened;

/**
 * @brief Copy construction elements only
 * @var constructionElementsOnly
 */
	bool							constructionElementsOnly;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	bool							filler_3[5];

/**
 * @brief Database ID to switch to (see @ref API_DatabaseUnId).
 * @var databaseID
 */
	API_DatabaseUnId				databaseID;

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	Int32							filler_4[8];

/**
 * @brief The clip polygon of the detail/worksheet.
 * @var poly
 */
	API_Polygon						poly;

/**
 * @brief The marker link data.
 * @var linkData
 */
	API_MarkerLinkDataType			linkData;


/**
 * @brief Reserved for later use.
 * @var filler_5
 */
	Int32							filler_5[8];
};

/**
 * @brief Represents a worksheet (worksheet mark).
 * @ingroup Element
 * @remarks Refer to the @ref ACAPI_Database_ChangeCurrentDatabase function to access and operate on
 * 			the corresponding Detail/Worksheet database. For detail related memo data see the @ref ACAPI_Element_GetMemo function.
 * @sa API_DetailType
 */
using API_WorksheetType = API_DetailType;


// =============================================================================
// Hotlink instance
//
// =============================================================================

/**
 * @brief Represents a Hotlink Module type or XRef type hotlink instance element.
 * @struct API_HotlinkType
 * @ingroup Element
 */
struct API_HotlinkType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;


/**
 * @brief Type of the hotlink.
 * @var type
 */
	API_HotlinkTypeID				type;

/**
 * @brief Reserved for further use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief Reference to the associated hotlink node (see @ref API_HotlinkNode).
 * @var hotlinkNodeGuid
 */
	API_Guid						hotlinkNodeGuid;

/**
 * @brief Reference to the associated element group.
 * @var hotlinkGroupGuid
 */
	API_Guid						hotlinkGroupGuid;

/**
 * @brief Placement transformation of the hotlink instance.
 * @var transformation
 */
	API_Tranmat						transformation;

/**
 * @brief Floor difference in case of hotlink module.
 * @var floorDifference
 */
	short							floorDifference;

/**
 * @brief Adjust angle of fixed-angle elements to reflect module rotation.
 * @var suspendFixAngle
 */
	bool							suspendFixAngle;

/**
 * @brief Skip nested hotlinks.
 * @var skipNested
 */
	bool							skipNested;

/**
 * @brief Top linked building elements will not keep their top floor links (homeFloorLinksOnly before 19).
 * @var ignoreTopFloorLinks
 */
	bool							ignoreTopFloorLinks;

/**
 * @brief Wall openings linked to stories will be relinked to walls to follow their elevation if the story structures differ.
 * @var relinkWallOpenings
 */
	bool							relinkWallOpenings;

/**
 * @brief If this parameter is true, then all Hotlink elements will retain their original vertical position relative to the Hotlink insertion point. Otherwise elevation of elements will follow the shift in Story Levels in the Host Project. Therefore, Hotlink element may shift vertically.
 * @var adjustLevelDiffs
 */
	bool							adjustLevelDiffs;

/**
 * @brief Reserved for further use.
 * @var filler_2
 */
	char							filler_2[2];

/**
 * @brief Reserved for further use.
 * @var filler_3
 */
	char							filler_3[16];

/**
 * @brief Reserved for further use.
 * @var filler_4
 */
	Int32							filler_4[2];
};


// =============================================================================
// Change Marker
//
// =============================================================================

/**
 * @brief Specifies the linkage type of a ChangeMarker, or the ChangeMarker Default.
 * @enum API_ChangeMarkerLinkType
 * @ingroup Element
 */
typedef enum {
	APICMLT_CreateNewChange,
	APICMLT_Linked,
	APICMLT_Unlinked

} API_ChangeMarkerLinkType;

/**
 * @brief Specifies which parts of the Change Marker are visible.
 * @enum API_ChangeMarkerComponentType
 * @ingroup Element
 */
typedef enum {
	APICMCT_HeadOnly,
	APICMCT_CloudOnly,
	APICMCT_HeadAndCloud

} API_ChangeMarkerComponentType;


/**
 * @brief Represents a ChangeMarker (a placeable element, not to be confused with the Change from the Change Manager palette).
 * @struct API_ChangeMarkerType
 * @ingroup Element
 * @remarks For ChangeMarker related memo data see the @ref ACAPI_Element_GetMemo function.
 */
struct API_ChangeMarkerType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;


/**
 * @brief When creating/changing a ChangeMarker or changing the ChangeMarker Default, this field is used to make the ChangeMarker/ChangeMarker Default linked or unlinked. When linkType is @c APICMLT_CreateNewChange, first a new Change will be created, then the ChangeMarker will be made linked to this Change. When creating/changing a ChangeMarker or changing the ChangeMarker Default if linkType is @c APICMLT_CreateNewChange, changeId and changeName also has to be supplied, if linkType is @c APICMLT_Linked, changeId also has to be supplied (changeName won't be used). When querying a placed ChangeMarker, in this field it is returned, whether the ChangeMarker is linked or unlinked. If linked, changeId and changeName shows the linked Change. When querying the ChangeMarker Default, in this field it is returned, whether the Default is linked, unlinked or a new Change will be created when placing a ChangeMarker (APICMLT_CreateNewChange). If linked, changeId and changeName shows the linked Change. If @c APICMLT_CreateNewChange, changeId and changeName shows what Change will be created when placing a ChangeMarker.
 * @var linkType
 */
	API_ChangeMarkerLinkType		linkType;

/**
 * @brief This field specifies whether the ChangeMarker has a Marker Head and/or Marker Cloud.
 * @var markerComponent
 */
	API_ChangeMarkerComponentType	markerComponent;

/**
 * @brief Specifies the Id of the linked Change.
 * @var changeId
 */
	GS::uchar_t						changeId[API_UniLongNameLen];

/**
 * @brief Specifies the name of the linked Change.
 * @var changeName
 */
	GS::uchar_t						changeName[API_UniLongNameLen];

/**
 * @brief If the ChangeMarker has no polygon, this coordinate means the reference position, where the ChangeMarker points to.
 * @var pos
 */
	API_Coord						pos;

/**
 * @brief If the ChangeMarker has polygon, this field contains some data of the polygon (see @ref API_Polygon). The polygon itself can be set/queried through memo.
 * @var poly
 */
	API_Polygon						poly;

/**
 * @brief After querying, changing, or creating a ChangeMarker, when the ChangeMarker has a Marker, this field contains the GUID of the associated Marker symbol.
 * @var markerGuid
 */
	API_Guid						markerGuid;

/**
 * @brief Marker rotation angle (radian).
 * @var angle
 */
	double							angle;

/**
 * @brief Marker is always horizontal.
 * @var horizontalMarker
 */
	bool							horizontalMarker;

/**
 * @brief Reserved for further use.
 * @var filler_1
 */
	char							filler_1[3];

/**
 * @brief Reserved for further use.
 * @var filler_2
 */
	Int32							filler_2;
};

// =============================================================================
// Stair
//
// =============================================================================

typedef enum {
	APILP_Left,
	APILP_Right,
	APILP_Center,
	APILP_Auto
} API_LinePositionID;

typedef enum {
	APIStairDisplay_Custom,
	APIStairDisplay_ByModelViewOptions
} API_StairDisplayTypeID;

typedef enum {
	APIStairGrid_NotRelevant,
	APIStairGrid_WithSingleBreaklineFull,
	APIStairGrid_NoBreaklineFull,
	APIStairGrid_BelowBreakline,
	APIStairGrid_AboveBreakline,
	APIStairGrid_MiddleBreakline,
	APIStairGrid_MiddleBreaklineFull,

	APIStairGrid_NoBreakMarkHidden,
	APIStairGrid_AboveBreakMarkHidden,
	APIStairGrid_BelowBreakMarkHidden,
	APIStairGrid_Multistory2DAllVisible,
	APIStairGrid_Multistory2DHiddenVisible,
	APIStairGrid_Multistory2DNoneVisibleHidden,
	APIStairGrid_WithBreakMarkAllVisible,
	APIStairGrid_WithBreakMarkHiddenVisible
} API_StairGridTypeID;

typedef enum {
	APIBreakLineAngle_AngleToVertical,
	APIBreakLineAngle_AngleToHorizontal,
	APIBreakLineAngle_NumberOfGoings
} API_BreakLineAngleTypeID;

typedef enum {
	APIBreakLinePosition_FloorPlanCutPlaneHeight,
	APIBreakLinePosition_CustomHeight,
	APIBreakLinePosition_AtNthRiser
} API_BreakLinePositionTypeID;

typedef enum {
	APIRP_OnTread,
	APIRP_BehindTread
} API_RiserPositionID;

typedef enum {
	APIRCS_Simple,
	APIRCS_Slanted
} API_RiserCrossSectID;

typedef enum {
	APISB_Stepped,
	APISB_Flat,
	APISB_Smooth
} API_StairStructBottomTypeID;

/**
 * @brief Determines the type of a Stair boundary edge or vertex.
 * @enum API_StairPolyTypeID
 * @ingroup Element
 */
typedef enum {
	APISP_Undefined,
	APISP_BaseLine,
	APISP_LeftBoundary,
	APISP_RightBoundary,
	APISP_Tread,
	APISP_Riser,
	APISP_WalkingLine,
	APISP_FloorPlanSymb,
	APISP_BreakMark,
	APISP_DummyTreadLeading,
	APISP_DummyTreadTrailing

} API_StairPolyTypeID;

/**
 * @brief Determines the type of a Stair boundary edge or vertex.
 * @enum API_StairPolyGeometryTypeID
 * @ingroup Element
 */
typedef enum {
	APISG_Vertex,
	APISG_Edge,
	APISG_Surface

} API_StairPolyGeometryTypeID;

typedef enum {
	APISN_Treads,
	APISN_Risers
} API_StairNumberingID;

typedef enum {
	APISD_Upward,
	APISD_Inverse
} API_StairDirectionID;

typedef enum {
	APIST_StepsSegment,
	APIST_LandingSegment,
	APIST_DividedLandingSegment
} API_StairSegmentTypeID;

/**
 * @brief Describes the mode for deciding the amount of winders in a divided landing.
 * @enum API_StairDLWinderNumTypeID
 * @ingroup Element
 */
typedef enum {
	APIDWN_Max,
	APIDWN_Optimal,
	APIDWN_Fix,
	APIDWN_Uniform

} API_StairDLWinderNumTypeID;

typedef enum {
	APIST_NoTurn,
	APIST_LandingTurn,
	APIST_WinderTurn,
	APIST_DividedLandingTurn
} API_StairTurnTypeID;

typedef enum {
	APIIWO_Min,
	APIIWO_Fix
} API_StairInnerWidthOffsetTypeID;

typedef enum {
	APIWN_Min,
	APIWN_Fix
} API_StairWinderNumTypeID;

/**
 * @brief Represents the role of a stair subelement.
 * @enum API_StairPartRoleID
 * @ingroup Element
 */
typedef enum {
	APISR_Run                   = 0,
	APISR_Landing               = 1

} API_StairPartRoleID;
#define API_StairPartRoleNum 	  2

typedef enum {
	APIST_Side,
	APIST_Monolith,
	APIST_BeamSupport,
	APIST_CantileveredSupport
} API_StairStructureTypeID;

typedef enum {
	APISS_LeftSide						= 0,
	APISS_RightSide 					= 1,
	APISS_UnderSide 					= 2,
} API_StairStructureSideID;
#define API_StairStructureSideNum 		  3

typedef enum {
	APISP_Auto,
	APISP_Center,
	APISP_Custom
} API_StairWalkLineSymbPosID;

typedef enum {
	APIST_Stepped,
	APIST_Smooth
} API_StairDrainSurfaceTypeID;

typedef enum {
	APIDS_Left		= 0,
	APIDS_Right		= 1
} API_StairDrainSideID;
#define API_StairDrainSideNum	2

typedef enum {
	APIWT_DINTurn,
	APIWT_NZETurn,
	APIWT_SIPTurn,
	APIWT_AGNTurn
} API_StairWinderID;

typedef enum {
	APISSV_HomeStoryOnly,
	APISSV_HomeAndOneStoryUp,
	APISSV_HomeAndOneStoryDown,
	APISSV_HomeAndOneStoryUpAndDown,
	APISSV_OneStoryUp,
	APISSV_OneStoryDown,
	APISSV_AllStories,
	APISSV_AllRelevantStories,
	APISSV_AllRelevantAndOneStoryUp,
	APISSV_AllRelevantAndOneStoryDown
} API_StairStoryVisibilityID;

typedef enum {
	APIST_UnderStructure				= 0,
	APIST_Stringer 						= 1,
} API_StairStructSymbTypeID;
#define API_StairStructSymbTypeNum 		  2

typedef enum {
	APISV_FloorPlan 					= 0,
	APISV_CeilingPlan 					= 1
} API_StairStructSymbViewID;
#define API_StairStructSymbViewNum 		  2

typedef enum {
	APISV_Beam 							= 0,
	APISV_Cantilevered 					= 1,
	APISV_Stringer						= 2,
	APISV_Monolith						= 3
} API_StairStructSymbVisibilityID;
#define API_StairStructSymbVisibilityNum  4

typedef enum {
	APISP_Visible 						= 0,
	APISP_Hidden 						= 1
} API_StairStructSymbPartID;
#define API_StairStructSymbPartNum 		  2


typedef enum {
	APISCV_ALL_STORIES = 0,
	APISCV_BELOW_RELEVANT = 1,
	APISCV_BOTTOM_RELEVANT = 2,
	APISCV_MID_RELEVANT = 3,
	APISCV_TOP_RELEVANT = 4,
	APISCV_ABOVE_RELEVANT = 5,
} API_StairStructSymbRelevantStoriesID;
#define API_StairStructSymbRelevantStoriesNum  6

typedef enum {
	APITN_ByValue,
	APITN_BySlanting
} API_StairTreadNosingTypeID;

typedef enum {
	APIHM_Perpendicular,
	APIHM_Vertical
} API_StairStructHeightMeasureID;

typedef enum {
	APIHM_RightAngleToSlope,
	APIHM_VerticallyToSlope
} API_HeadroomGenerationModeID;

/**
 * @brief Stores data of a stair polyline edge.
 * @struct API_StairPolylineEdgeData
 * @ingroup Element
 */
struct API_StairPolylineEdgeData {

/**
 * @brief The type of the boundary polyline section.
 * @var type
 */
	API_StairPolyTypeID 			type;

/**
 * @brief The geometry type of the boundary polyline section.
 * @var geometryType
 */
	API_StairPolyGeometryTypeID 	geometryType;

/**
 * @brief The subelement identifier of the boundary polyline section.
 * @var subElemId
 */
	UInt32 							subElemId;

/**
 * @brief The section describes the top of the subelement.
 * @var isTop
 */
	bool	 						isTop;

/**
 * @brief The section describes the bottom of the subelement.
 * @var isBottom
 */
	bool	 						isBottom;

/**
 * @brief The section describes the front of the subelement.
 * @var isFront
 */
	bool	 						isFront;

/**
 * @brief The section describes the back of the subelement.
 * @var isBack
 */
	bool	 						isBack;

/**
 * @brief Internal identifier.
 * @var customId
 */
	UInt32 							customId;

/**
 * @brief Type of the segment described by this edge:
 * 		  |APIST_StepsSegment|Step segment.|
 * 		  |APIST_LandingSegment|Landing segment.|
 * 		  |APIST_DividedLandingSegment|Divided landing segment.|
 *
 * @var segmentType
 */
	API_StairSegmentTypeID			segmentType;

/**
 * @brief If true, edge is locked.
 * @var isLocked
 */
	bool	 						isLocked;

/**
 * @brief Reserved for further use.
 * @var filler_1
 */
	bool	 						filler_1[3];

/**
 * @brief Reserved for further use.
 * @var filler_2
 */
	Int32 							filler_2;
};

/**
 * @brief Stores data of a stair polyline vertex.
 * @struct API_StairPolylineVertexData
 * @ingroup Element
 */
struct API_StairPolylineVertexData {

/**
 * @brief The type of the boundary polyline section.
 * @var type
 */
	API_StairPolyTypeID 				type;

/**
 * @brief The geometry type of the boundary polyline section.
 * @var geometryType
 */
	API_StairPolyGeometryTypeID 		geometryType;

/**
 * @brief The subelement identifier of the boundary polyline section.
 * @var subElemId
 */
	UInt32 								subElemId;

/**
 * @brief The section describes the top of the subelement.
 * @var isTop
 */
	bool	 							isTop;

/**
 * @brief The section describes the bottom of the subelement.
 * @var isBottom
 */
	bool	 							isBottom;

/**
 * @brief The section describes the front of the subelement.
 * @var isFront
 */
	bool	 							isFront;

/**
 * @brief The section describes the back of the subelement.
 * @var isBack
 */
	bool	 							isBack;

/**
 * @brief Internal identifier.
 * @var customId
 */
	UInt32 								customId;

/**
 * @brief The type of the turn.
 * 		  |APIST_NoTurn|No turn.|
 * 		  |APIST_LandingTurn|Type is landing turn.|
 * 		  |APIST_WinderTurn|Type is winder turn.|
 * 		  |APIST_DividedLandingTurn|Type is divided landing turn.|
 *
 * @var turnType
 */
	API_StairTurnTypeID 				turnType;

/**
 * @brief Number of Winder Steps backward.
 * @var winderStepNumBackward
 */
	Int32								winderStepNumBackward;

/**
 * @brief Number of Winder Steps forward.
 * @var winderStepNumForward
 */
	Int32								winderStepNumForward;

/**
 * @brief Lead Edge Offset and Trail Edge Offset are linked.
 * @var symmetricalLandingOffset
 */
	bool								symmetricalLandingOffset;

/**
 * @brief Reserved for further use.
 * @var filler_1
 */
	bool	 							filler_1[7];

/**
 * @brief Minimal Lead Edge Offset.
 * @var minLandingStartEdgeOffset
 */
	double								minLandingStartEdgeOffset;

/**
 * @brief Minimal Trail Edge Offset.
 * @var minLandingEndEdgeOffset
 */
	double								minLandingEndEdgeOffset;

/**
 * @brief Calculated Lead Edge Offset.
 * @var currLandingStartEdgeOffset
 */
	double								currLandingStartEdgeOffset;

/**
 * @brief Calculated Trail Edge Offset.
 * @var currLandingEndEdgeOffset
 */
	double								currLandingEndEdgeOffset;

/**
 * @brief Reserved for further use.
 * @var filler_2
 */
	double								filler_2;

/**
 * @brief The type of the Riser Offsets from Corner:
 * 		  |APIIWO_Min|Minimum Riser Offset.|
 * 		  |APIIWO_Fix|Fixed Riser Offset.|
 *
 * @var innerWidthOffsetType
 */
	API_StairInnerWidthOffsetTypeID		innerWidthOffsetType;

/**
 * @brief The type of the Number of Winders:
 * 		  |APIWN_Min|Minimum Number of Winders.|
 * 		  |APIWN_Fix|Fixed Number of Winders.|
 *
 * @var numOfWindersType
 */
	API_StairWinderNumTypeID			numOfWindersType;

/**
 * @brief Winders division method type.
 * @var dividedLandingNumOfWindersType
 */
	API_StairDLWinderNumTypeID			dividedLandingNumOfWindersType;

/**
 * @brief Number of steps on Divided Landing if the division method is Fixed Number of Goings.
 * @var dividedLandingFixedNumOfSteps
 */
	Int32								dividedLandingFixedNumOfSteps;

/**
 * @brief The type of the Winder:
 * 		  |APIWT_DINTurn|Auxiliary Walking Line|
 * 		  |APIWT_NZETurn|Two Points|
 * 		  |APIWT_SIPTurn|Single Point|
 * 		  |APIWT_AGNTurn|Principal Lines|
 *
 * @var winderType
 */
	API_StairWinderID					winderType;

};

/**
 * @brief Represents a Stair polyline (baseline or walking line).
 * @struct API_StairPolylineData
 * @ingroup Element
 * @remarks There are two Stair polylines in the @ref API_StairType structure, the baseline and the walking line.
 */
struct API_StairPolylineData {

/**
 * @brief The API polygon element describing the amounts of vertices in the boundary line.
 * @var polygon
 */
	API_Polygon 					polygon;

/**
 * @brief The coordinates of the vertices of the boundary line.
 * @var coords
 */
	API_Coord 						**coords;

/**
 * @brief The polygon endings of the boundary line.
 * @var pends
 */
	Int32 							**pends;

/**
 * @brief The arcs of the boundary line.
 * @var parcs
 */
	API_PolyArc 					**parcs;

/**
 * @brief The edge data of each edge.
 * @var edgeData
 */
	API_StairPolylineEdgeData		*edgeData;

/**
 * @brief The vertex data of each vertex.
 * @var vertexData
 */
	API_StairPolylineVertexData 	*vertexData;

};

/**
 * @brief Stores data of a stair boundary vertex.
 * @struct API_StairBoundaryVertexData
 * @ingroup Element
 */
struct API_StairBoundaryVertexData {

/**
 * @brief The type of the boundary polyline section.
 * @var type
 */
	API_StairPolyTypeID 			type;

/**
 * @brief The geometry type of the boundary polyline section.
 * @var geometryType
 */
	API_StairPolyGeometryTypeID 	geometryType;

/**
 * @brief The subelement identifier of the boundary polyline section.
 * @var subElemId
 */
	UInt32 							subElemId;

/**
 * @brief The section describes the top of the subelement.
 * @var isTop
 */
	bool	 						isTop;

/**
 * @brief The section describes the bottom of the subelement.
 * @var isBottom
 */
	bool	 						isBottom;

/**
 * @brief The section describes the front of the subelement.
 * @var isFront
 */
	bool	 						isFront;

/**
 * @brief The section describes the back of the subelement.
 * @var isBack
 */
	bool	 						isBack;

/**
 * @brief Internal identifier.
 * @var customId
 */
	UInt32 							customId;

/**
 * @brief Reserved for further use.
 * @var filler_1
 */
	UInt32 							filler_1;

/**
 * @brief Value in the z axis.
 * @var zValue
 */
	double 							zValue;

};

/**
 * @brief Stores data of a stair boundary edge.
 * @struct API_StairBoundaryEdgeData
 * @ingroup Element
 */
struct API_StairBoundaryEdgeData {

/**
 * @brief The type of the boundary polyline section.
 * @var type
 */
	API_StairPolyTypeID 			type;

/**
 * @brief The geometry type of the boundary polyline section.
 * @var geometryType
 */
	API_StairPolyGeometryTypeID 	geometryType;

/**
 * @brief The subelement identifier of the boundary polyline section.
 * @var subElemId
 */
	UInt32 							subElemId;

/**
 * @brief The section describes the top of the subelement.
 * @var isTop
 */
	bool	 						isTop;

/**
 * @brief The section describes the bottom of the subelement.
 * @var isBottom
 */
	bool	 						isBottom;

/**
 * @brief The section describes the front of the subelement.
 * @var isFront
 */
	bool	 						isFront;

/**
 * @brief The section describes the back of the subelement.
 * @var isBack
 */
	bool	 						isBack;

/**
 * @brief Internal identifier.
 * @var customId
 */
	UInt32 							customId;

/**
 * @brief The described subelement is visible.
 * @var visible
 */
	bool	 						visible;

/**
 * @brief Reserved for further use.
 * @var filler_1
 */
	bool	 						filler_1[3];
};

/**
 * @brief Represents a Stair boundary.
 * @struct API_StairBoundaryData
 * @ingroup Element
 * @remarks There are two Stair boundaries in the @ref API_ElementMemo structure, the one with the index of 0 describes the left, and the one with the index of 1 describes the right side boundary line of the Stair element.
 */
struct API_StairBoundaryData {

/**
 * @brief The API polygon element describing the amounts of vertices in the boundary line.
 * @var polygon
 */
	API_Polygon 					polygon;

/**
 * @brief The coordinates of the vertices of the boundary line.
 * @var coords
 */
	API_Coord       				**coords;

/**
 * @brief The polygon endings of the boundary line.
 * @var pends
 */
	Int32           				**pends;

/**
 * @brief The arcs of the boundary line.
 * @var parcs
 */
	API_PolyArc     				**parcs;

/**
 * @brief The edge data of each edge.
 * @var edgeData
 */
	API_StairBoundaryEdgeData 		*edgeData;

/**
 * @brief The vertex data of each vertex.
 * @var vertexData
 */
	API_StairBoundaryVertexData 	*vertexData;

/**
 * @brief True, if the stair boundary is customized.
 * @var isCustom
 */
	bool	 						isCustom;

/**
 * @brief Reserved for further use.
 * @var filler_1
 */
	bool	 						filler_1[7];
};

/**
 * @brief Represents the layout of a Stair element.
 * @struct API_StairLayoutData
 * @ingroup Element
 * @remarks The Stair is a hierarchical (system) element consisting of Tread, Riser, and Structure components: these are the members of the Stair, arranged on a base surface according to a pre-defined scheme.
 * 			To create a Stair, one must provide its base line and position.
 */
struct API_StairLayoutData {

/**
 * @brief The option to define on which stories are the stairs displayed.
 * @var visibility
 */
	API_StoryVisibility             visibility;

/**
 * @brief It will be true, if showOnHome in visibility is false.
 * @var isAutoOnStoryVisibility
 */
	bool	                        isAutoOnStoryVisibility;

/**
 * @brief Reserved for further use.
 * @var filler_1
 */
	bool	                        filler_1[3];

/**
 * @brief Layout above relevant stories:
 * 		  |Type|Meaning|
 * 		  |--- |--- |
 * 		  |APIStairGrid_NotRelevant|Not Relevant.|
 * 		  |APIStairGrid_WithSingleBreaklineFull|With Break Mark: Visible - Hidden|
 * 		  |APIStairGrid_NoBreaklineFull|No Break Mark: Visible|
 * 		  |APIStairGrid_BelowBreakline|Below Break Mark: Visible|
 * 		  |APIStairGrid_AboveBreakline|Above Break Mark: Visible|
 * 		  |APIStairGrid_MiddleBreakline|Multistory 2D: Visible Inbetween Break Marks|
 * 		  |APIStairGrid_MiddleBreaklineFull|Multistory 2D: Hidden - Visible - Hidden|
 * 		  |APIStairGrid_NoBreakMarkHidden|No Break Mark: Hidden|
 * 		  |APIStairGrid_AboveBreakMarkHidden|Above Break Mark: Hidden|
 * 		  |APIStairGrid_BelowBreakMarkHidden|Below Break Mark: Hidden|
 * 		  |APIStairGrid_Multistory2DAllVisible|Multistory 2D: All Visible|
 * 		  |APIStairGrid_Multistory2DHiddenVisible|Multistory 2D: Hidden - Visible - None|
 * 		  |APIStairGrid_Multistory2DNoneVisibleHidden|Multistory 2D: None - Visible - Hidden|
 * 		  |APIStairGrid_WithBreakMarkAllVisible|With Break Mark: All Visible|
 * 		  |APIStairGrid_WithBreakMarkHiddenVisible|With Break Mark: Hidden - Visible|
 *
 * @var gridTypeAbove
 */
	API_StairGridTypeID             gridTypeAbove;

/**
 * @brief Layout on top relevant stories.
 * @var gridTypeTop
 */
	API_StairGridTypeID             gridTypeTop;

/**
 * @brief Layout on middle stories.
 * @var gridTypeMiddle
 */
	API_StairGridTypeID             gridTypeMiddle;

/**
 * @brief Layout on bottom story.
 * @var gridTypeBottom
 */
	API_StairGridTypeID             gridTypeBottom;

/**
 * @brief Layout below relevant stories.
 * @var gridTypeBelow
 */
	API_StairGridTypeID             gridTypeBelow;

/**
 * @brief Visibility type in the story.
 * @var storyVisibility
 */
	API_StairStoryVisibilityID      storyVisibility;

/**
 * @brief If true, the walking line is shown.
 * @var showWalkingLine
 */
	bool	                        showWalkingLine;

/**
 * @brief If true, the stair numbering is shown.
 * @var showNumbering
 */
	bool	                        showNumbering;

/**
 * @brief If true, the stair direction label is shown.
 * @var showUpDownText
 */
	bool	                        showUpDownText;

/**
 * @brief If true, the stair description is shown.
 * @var showDescription
 */
	bool	                        showDescription;

/**
 * @brief Reserved for further use.
 * @var filler_2
 */
	bool	                        filler_2[2];

/**
 * @brief If true, the stair structures are shown.
 * @var showStructure
 */
	bool	                        showStructure;

/**
 * @brief Reserved for further use.
 * @var filler_3
 */
	bool		                    filler_3[5];

/**
 * @brief The angle of the break line.
 * @var breakLineAngle
 */
	double                          breakLineAngle;

/**
 * @brief The amount of goings of the break line.
 * @var breakLineAngleNumberOfGoings
 */
	Int32                           breakLineAngleNumberOfGoings;

/**
 * @brief The angle type of the break line:
 * 		  |APIBreakLineAngle_AngleToVertical|Angel to vertical.|
 * 		  |APIBreakLineAngle_AngleToHorizontal|Angle to horizontal.|
 * 		  |APIBreakLineAngle_NumberOfGoings|Angle will be calculated based on the given Number of Goings.|
 *
 * @var breakLineAngleType
 */
	API_BreakLineAngleTypeID        breakLineAngleType;

/**
 * @brief The gap of the break line.
 * @var breakLineDistance
 */
	double                          breakLineDistance;

/**
 * @brief The line position type of the break line:
 * 		  |APIBreakLinePosition_FloorPlanCutPlaneHeight|Break line height is determined from the Floor Plan Cut Plane Height.|
 * 		  |APIBreakLinePosition_CustomHeight|Break line is on Custom Height.|
 * 		  |APIBreakLinePosition_AtNthRiser|Break line is on a given Riser.|
 *
 * @var breakLinePositionType
 */
	API_BreakLinePositionTypeID     breakLinePositionType;

/**
 * @brief Reserved for further use.
 * @var filler_4
 */
	Int32                           filler_4;

/**
 * @brief Custom position of the upper break line.
 * @var upperBreakLineCustomPosition
 */
	double                          upperBreakLineCustomPosition;

/**
 * @brief Custom position of the lower break line.
 * @var lowerBreakLineCustomPosition
 */
	double                          lowerBreakLineCustomPosition;

/**
 * @brief Riser position of the upper break line.
 * @var upperBreakLineNthRiserPosition
 */
	UInt32                          upperBreakLineNthRiserPosition;

/**
 * @brief Riser position of the lower break line.
 * @var lowerBreakLineNthRiserPosition
 */
	UInt32                          lowerBreakLineNthRiserPosition;

/**
 * @brief If true, the line type will be overridden.
 * @var overrideLineType
 */
	bool	                        overrideLineType;

/**
 * @brief If true, the line pen will be overridden.
 * @var overridePen
 */
	bool	                        overridePen;

/**
 * @brief The line pen index for the Stair.
 * @var pen
 */
	short                           pen;

/**
 * @brief The line type index for the Stair.
 * @var lineType
 */
	API_AttributeIndex              lineType;

/**
 * @brief If true, the fill will be overridden.
 * @var overrideSymbolFill
 */
	bool	                        overrideSymbolFill;

/**
 * @brief Reserved for further use.
 * @var filler_5
 */
	bool	                        filler_5[3];

/**
 * @brief The symbol fill type index for the Stair.
 * @var symbolFill
 */
	API_AttributeIndex              symbolFill;

/**
 * @brief The sybol fill pen index for the Stair.
 * @var symbolFillPen
 */
	short                           symbolFillPen;

/**
 * @brief The symbol fill background pen index for the Stair.
 * @var symbolFillBkgPen
 */
	short                           symbolFillBkgPen;

/**
 * @brief Reserved for further use.
 * @var filler_6
 */
	short                           filler_6[2];

};

/**
 * @brief Represents a the Rules and Standards of a Stair element.
 * @struct API_StairRulesData
 * @ingroup Element
 */
struct API_StairRulesData {

/**
 * @brief Minimum riser height.
 * @var riserHeightMinValue
 */
	double 							riserHeightMinValue;

/**
 * @brief Maximum riser height.
 * @var riserHeightMaxValue
 */
	double 							riserHeightMaxValue;

/**
 * @brief Minimum going length.
 * @var treadDepthMinValue
 */
	double 							treadDepthMinValue;

/**
 * @brief Maximum going length.
 * @var treadDepthMaxValue
 */
	double 							treadDepthMaxValue;

/**
 * @brief Minimum 2R+G.
 * @var ruleMinValue
 */
	double 							ruleMinValue;

/**
 * @brief Maixmum 2R+G.
 * @var ruleMaxValue
 */
	double 							ruleMaxValue;

/**
 * @brief Minimum automatic landing length.
 * @var landingLengthMinValue
 */
	double 							landingLengthMinValue;

/**
 * @brief Minimum automatic landing offset.
 * @var walkingLineOffsetMinValue
 */
	double 							walkingLineOffsetMinValue;

/**
 * @brief Minimum winder width.
 * @var winderTurnOffsetMinValue
 */
	double 							winderTurnOffsetMinValue;

/**
 * @brief Minimum riser height/tread length ratio.
 * @var riserGoingRatioMinValue
 */
	double  						riserGoingRatioMinValue;

/**
 * @brief Maximum riser height/tread length ratio.
 * @var riserGoingRatioMaxValue
 */
	double  						riserGoingRatioMaxValue;

/**
 * @brief Minimum riser height + tread length value.
 * @var riserPlusGoingMinValue
 */
   	double  						riserPlusGoingMinValue;

/**
 * @brief Maximum riser height + tread length value.
 * @var riserPlusGoingMaxValue
 */
   	double  						riserPlusGoingMaxValue;

/**
 * @brief Minimum stair pitch.
 * @var stairPitchMinValue
 */
   	double  						stairPitchMinValue;

/**
 * @brief Maximum stair pitch.
 * @var stairPitchMaxValue
 */
   	double  						stairPitchMaxValue;

/**
 * @brief Minimum riser height set.
 * @var riserHeightMinApplied
 */
	bool	 						riserHeightMinApplied;

/**
 * @brief Maximum riser height set.
 * @var riserHeightMaxApplied
 */
	bool	 						riserHeightMaxApplied;

/**
 * @brief Minimum going length set.
 * @var treadDepthMinApplied
 */
	bool	 						treadDepthMinApplied;

/**
 * @brief Maximum going length set.
 * @var treadDepthMaxApplied
 */
	bool	 						treadDepthMaxApplied;

/**
 * @brief Minimum 2R+G set.
 * @var ruleMinApplied
 */
	bool	 						ruleMinApplied;

/**
 * @brief Maixmum 2R+G set.
 * @var ruleMaxApplied
 */
	bool	 						ruleMaxApplied;

/**
 * @brief Minimum automatic landing length set.
 * @var landingLengthMinApplied
 */
	bool	 						landingLengthMinApplied;

/**
 * @brief Minimum automatic landing offset set.
 * @var walkingLineOffsetMinApplied
 */
	bool	 						walkingLineOffsetMinApplied;

/**
 * @brief Minimum winder width set.
 * @var winderTurnOffsetMinApplied
 */
	bool	 						winderTurnOffsetMinApplied;


	bool							filler_1[2];

/**
 * @brief Minimum riser height/tread length ratio set.
 * @var riserGoingRatioMinApplied
 */
	bool							riserGoingRatioMinApplied;

/**
 * @brief Maximum riser height/tread length ratio set.
 * @var riserGoingRatioMaxApplied
 */
   	bool							riserGoingRatioMaxApplied;

/**
 * @brief Minimum riser height + tread length value set.
 * @var riserPlusGoingMinApplied
 */
   	bool							riserPlusGoingMinApplied;

/**
 * @brief Maximum riser height + tread length value set.
 * @var riserPlusGoingMaxApplied
 */
   	bool							riserPlusGoingMaxApplied;

/**
 * @brief Minimum stair pitch set.
 * @var stairPitchMinApplied
 */
   	bool							stairPitchMinApplied;

/**
 * @brief Maximum stair pitch set.
 * @var stairPitchMaxApplied
 */
   	bool							stairPitchMaxApplied;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool	 						filler_2[3];

};

/**
 * @brief Description of the Stair Headroom.
 * @struct API_StairHeadroomData
 * @ingroup Element
 */
struct API_StairHeadroomData {

/**
 * @brief The type of room generation mode: @c APIHM_RightAngleToSlope or @c APIHM_VerticallyToSlope
 * @var headroomMethod
 */
	API_HeadroomGenerationModeID	headroomMethod;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	UInt32 							filler_1;

/**
 * @brief The height of the headroom.
 * @var headroomHeight
 */
	double 							headroomHeight;

/**
 * @brief The offset of the headroom from the left side.
 * @var headroomLeftOffset
 */
	double 							headroomLeftOffset;

/**
 * @brief The offset of the headroom from the right side.
 * @var headroomRightOffset
 */
	double 							headroomRightOffset;

};

/**
 * @brief Represents the draining of a monolithic Stair Structure element.
 * @struct API_StairStructureDrainingData
 * @ingroup Element
 */
struct API_StairStructureDrainingData {

/**
 * @brief True, if structure draining is enabled.
 * @var enabled
 */
	bool	 						enabled;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool	 						filler_1[7];

/**
 * @brief Width of the draining.
 * @var width
 */
	double 							width;

/**
 * @brief Offset from boundary.
 * @var offset
 */
	double 							offset;

/**
 * @brief Draining vertical depth.
 * @var horizontalDepth
 */
	double 							horizontalDepth;

/**
 * @brief Draning horizontal depth.
 * @var verticalDepth
 */
	double 							verticalDepth;

/**
 * @brief Material of the draining.
 * @var material
 */
	API_OverriddenAttribute			material;

/**
 * @brief Surface type of the draining:
 * 		  |APIST_Stepped|Stepped structure draining.|
 * 		  |APIST_Smooth|Smooth structure draining.|
 *
 * @var surfaceType
 */
	API_StairDrainSurfaceTypeID		surfaceType;

};

/**
 * @brief Represents the data of a side supported Stair Structure element.
 * @struct API_SideStairStructData
 * @ingroup Element
 */
struct API_SideStairStructData {

/**
 * @brief The width of the Stair Structure element.
 * @var width
 */
	double                          width;

/**
 * @brief The height of the Stair Structure above its related Tread.
 * @var heightAboveTread
 */
	double 							heightAboveTread;

/**
 * @brief The way of measuring of height above treads:
 * 		  |APIHM_Perpendicular|Perpendicular calculation.|
 * 		  |APIHM_Vertical|Straight vertical calculation.|
 *
 * @var heightMeasure
 */
	API_StairStructHeightMeasureID	heightMeasure;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	UInt32 							filler_1;

};

/**
 * @brief Represents the data of a monolithic Stair Structure element.
 * @struct API_MonolithStairStructData
 * @ingroup Element
 */
struct API_MonolithStairStructData {

/**
 * @brief True, if the structure is thinned.
 * @var thinning
 */
	bool	 						thinning;

/**
 * @brief True, if the structure's materials are chained.
 * @var materialsChained
 */
	bool	 						materialsChained;

/**
 * @brief UNUSED PARAMETER
 * @var filler_1
 */
	short 							filler_1;

/**
 * @brief The fill of the building material.
 * @var sideFill
 */
	API_AttributeIndex 				sideFill;

/**
 * @brief The index of the structure's building material.
 * @var buildingMaterial
 */
	API_AttributeIndex 				buildingMaterial;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	short 							filler_2[2];

/**
 * @brief The thickness of the monolith.
 * @var monolithThickness
 */
	double 							monolithThickness;

/**
 * @brief The size of the horizontal bottom.
 * @var bottomOversize
 */
	double 							bottomOversize;

/**
 * @brief The top material of the structure.
 * @var topMaterial
 */
	API_OverriddenAttribute 	 	topMaterial;

/**
 * @brief The left side material of the structure.
 * @var leftMaterial
 */
	API_OverriddenAttribute 	 	leftMaterial;

/**
 * @brief The right side material of the structure.
 * @var rightMaterial
 */
	API_OverriddenAttribute 	 	rightMaterial;

/**
 * @brief The bottom material of the structure.
 * @var bottomMaterial
 */
	API_OverriddenAttribute 	 	bottomMaterial;

/**
 * @brief The index of the cut parts' 2D representation's line type.
 * @var cutLineType
 */
	API_AttributeIndex				cutLineType;

/**
 * @brief The index of the cut parts' 2D representation's pen.
 * @var cutLinePen
 */
	short							cutLinePen;

/**
 * @brief The index of the 2D representation's pen.
 * @var pen
 */
	short							pen;

/**
 * @brief The index of the 2D representation's line type.
 * @var lineType
 */
	API_AttributeIndex				lineType;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	short 							filler_3[2];

/**
 * @brief The cut fill pen of the Stair Structure.
 * @var cutFillPen
 */
	API_OverriddenPen				cutFillPen;

/**
 * @brief The cut fill background pen of the Stair Structure.
 * @var cutFillBackgroundPen
 */
	API_OverriddenPen				cutFillBackgroundPen;

/**
 * @brief The Stair Structure's surface material.
 * @var surfaceMaterial
 */
	API_AttributeIndex 				surfaceMaterial;

/**
 * @brief Uniform Drainings on left and right side.
 * @var uniformDrainings
 */
	bool							uniformDrainings;

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	bool 							filler_4[3];

/**
 * @brief Data about the Stair Structure's drainings.
 * 		  |APIDS_Left|Draining on the left side.|
 * 		  |APIDS_Right|Draining on the right side.|
 *
 * @var draining
 */
	API_StairStructureDrainingData	draining[API_StairDrainSideNum];

};

/**
 * @brief Represents the data of a 2D symbol a Stair's Structure elements.
 * @struct API_StairStructureSymbolData
 * @ingroup Element
 */
struct API_StairStructureSymbolData {

/**
 * @brief Type of the visible lines.
 * @var visibleLineType
 */
	API_AttributeIndex				visibleLineType;

/**
 * @brief Pen of the visible lines.
 * @var visibleLinePen
 */
	short							visibleLinePen;

/**
 * @brief Pen of the hidden lines.
 * @var hiddenLinePen
 */
	short							hiddenLinePen;

/**
 * @brief Type of the hidden lines.
 * @var hiddenLineType
 */
	API_AttributeIndex				hiddenLineType;

/**
 * @brief Type of the visible fills.
 * @var visibleFillType
 */
	API_AttributeIndex				visibleFillType;

/**
 * @brief Pen of the visible fills.
 * @var visibleFillPen
 */
	short							visibleFillPen;

/**
 * @brief Pen of the visible background fills.
 * @var visibleFillBackgroundPen
 */
	short							visibleFillBackgroundPen;

/**
 * @brief Type of the hidden fills.
 * @var hiddenFillType
 */
	API_AttributeIndex				hiddenFillType;

/**
 * @brief Pen of the hidden fills.
 * @var hiddenFillPen
 */
	short							hiddenFillPen;

/**
 * @brief Pen of the hidden background fills.
 * @var hiddenFillBackgroundPen
 */
	short							hiddenFillBackgroundPen;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[4];

};

/**
 * @brief Represents the data of a monolith Stair's Structure elements.
 * @struct API_StairMonolithStructureSymbolData
 * @ingroup Element
 */
struct API_StairMonolithStructureSymbolData {
/**
 * @brief Line type of Stair's Going line.
 * @var goingLineType
 */
	API_AttributeIndex				goingLineType;

/**
 * @brief Pen of Stair's Going line.
 * @var goingLinePen
 */
	short							goingLinePen;

/**
 * @brief Pen of Stair's Nosing line.
 * @var goingNosingLinePen
 */
	short							goingNosingLinePen;

/**
 * @brief Line type of Stair's Nosing line.
 * @var goingNosingLineType
 */
	API_AttributeIndex				goingNosingLineType;

/**
 * @brief Line type of Stair's Connection line.
 * @var connectionLineType
 */
	API_AttributeIndex				connectionLineType;

/**
 * @brief Pen of Stair's Connection line.
 * @var connectionLinePen
 */
	short							connectionLinePen;

/**
 * @brief Pen of Stair's Connection line on Detail view.
 * @var connectionDetailLinePen
 */
	short							connectionDetailLinePen;

/**
 * @brief Line type of Stair's Connection line on Detail view.
 * @var connectionDetailLineType
 */
	API_AttributeIndex				connectionDetailLineType;

/**
 * @brief Fill type of Stair's Draining.
 * @var drainingFillType
 */
	API_AttributeIndex				drainingFillType;

/**
 * @brief Pen of Stair's Draining fill.
 * @var drainingFillPen
 */
	short							drainingFillPen;

/**
 * @brief Background pen of Stair's Draining fill.
 * @var drainingFillBackGroundPen
 */
	short							drainingFillBackGroundPen;

/**
 * @brief Line type of Stair's Contour line.
 * @var contourLineType
 */
	API_AttributeIndex				contourLineType;

/**
 * @brief Pen of Stair's Contour line.
 * @var contourLinePen
 */
	short							contourLinePen;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[2];
};

/**
 * @brief Describes which types of monolith parts are visible.
 * @struct API_MonolithPartsVisibilityData
 * @ingroup Element
 */
struct API_MonolithPartsVisibilityData {

/**
 * @brief Connection visibility settings.
 * @var connectionVisible
 */
	bool							connectionVisible;

/**
 * @brief Draining visibility settings.
 * @var drainingVisible
 */
	bool							drainingVisible;

/**
 * @brief Landing line visibility settings.
 * @var landingLineVisible
 */
	bool							landingLineVisible;

/**
 * @brief Structure going visibility settings.
 * @var structureGoingVisible
 */
	bool							structureGoingVisible;

/**
 * @brief Structure going nosing visibility settings.
 * @var structureGoingNosingVisible
 */
	bool							structureGoingNosingVisible;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[3];

};

/**
 * @brief Describes story's stair structure component visibility settings.
 * @struct API_StairStructureComponentSettingsVisibilityOnStory
 * @ingroup Element
 */
struct API_StairStructureComponentSettingsVisibilityOnStory {

/**
 * @brief Visibility settings of structure.
 * @var structureVisibility
 */
	bool							structureVisibility[API_StairStructSymbPartNum][API_StairStructSymbVisibilityNum];

/**
 * @brief Visibility settings of fill.
 * @var fillVisibility
 */
	bool							fillVisibility[API_StairStructSymbPartNum][API_StairStructSymbTypeNum];

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[4];

/**
 * @brief Visibility settings of monolith parts.
 * @var monolithPartsVisibility
 */
	API_MonolithPartsVisibilityData	monolithPartsVisibility[API_StairStructSymbPartNum];

};

/**
 * @brief Settings for visibility of the stair component strucutre.
 * @struct API_StairStructureComponentSettingsVisibility
 * @ingroup Element
 */
struct API_StairStructureComponentSettingsVisibility {

/**
 * @brief Settings of uniform symbol representation.
 * @var uniformSymbolRepresentationEnabled
 */
	bool													uniformSymbolRepresentationEnabled;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool													filler_1[7];

/**
 * @brief Stair structure component visibility settings on relevant stories.
 * @var structureVisibilityOnStories
 */
	API_StairStructureComponentSettingsVisibilityOnStory	structureVisibilityOnStories[API_StairStructSymbRelevantStoriesNum];

};

/**
 * @brief Represents a Riser element.
 * @struct API_StairRiserType
 * @ingroup Element
 */
struct API_StairRiserType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head 					head;

/**
 * @brief Riser position:
 * 		  |APIRP_OnTread|Risers are placed on top of the treads.|
 * 		  |APIRP_BehindTread|Risers are behind the treads.|
 *
 * @var riserPosition
 */
	API_RiserPositionID 			riserPosition;

/**
 * @brief Riser cross section type:
 * 		  |APIRCS_Simple|Simple, straight risers|
 * 		  |APIRCS_Slanted|Slanted risers.|
 *
 * @var crossSect
 */
	API_RiserCrossSectID 			crossSect;

/**
 * @brief Slanting angle of risers, if they are slanted.
 * @var angle
 */
	double 							angle;

/**
 * @brief Riser gap.
 * @var offset
 */
	double 							offset;

/**
 * @brief Riser thickness.
 * @var thickness
 */
	double 							thickness;

/**
 * @brief GUID of the owning stair.
 * @var owner
 */
	API_Guid 						owner;

/**
 * @brief Library part GUID.
 * @var libId
 */
	API_Guid 						libId;

/**
 * @brief The number of the step that the riser belongs to.
 * @var sequenceNumber
 */
	UInt32 							sequenceNumber;

/**
 * @brief The subelement identifier of the riser.
 * @var subElemId
 */
	UInt32 							subElemId;

/**
 * @brief True, if the object is visible.
 * @var visible
 */
	bool	 						visible;

/**
 * @brief Role of the Stair subelement.
 * @var role
 */
	API_StairPartRoleID				role;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool	 						filler_1[3];

};

/**
 * @brief Represents a Tread element.
 * @struct API_StairTreadType
 * @ingroup Element
 */
struct API_StairTreadType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head 					head;

/**
 * @brief Tread is custom.
 * @var isCustom
 */
	bool	 						isCustom;

/**
 * @brief The object is visible.
 * @var visible
 */
	bool	 						visible;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool	 						filler_1[2];

/**
 * @brief Type of the Tread nosing:
 * 		  |APITN_ByValue|The Tread nosing is given a length value.|
 * 		  |APITN_BySlanting|The Tread nosing is given a slanting value.|
 *
 * @var nosingType
 */
	API_StairTreadNosingTypeID 		nosingType;

/**
 * @brief Length of the nosing if the nosing type is by value.
 * @var nosingValue
 */
	double 							nosingValue;

/**
 * @brief Slanting of the nosing if the nosing type is by slanting.
 * @var nosingSlant
 */
	double 							nosingSlant;

/**
 * @brief Tread gap.
 * @var offset
 */
	double 							offset;

/**
 * @brief Tread thickness.
 * @var thickness
 */
	double 							thickness;

/**
 * @brief GUID of the owning stair.
 * @var owner
 */
	API_Guid 						owner;

/**
 * @brief Library part GUID.
 * @var libId
 */
	API_Guid 						libId;

/**
 * @brief The number of the step that the tread belongs to.
 * @var sequenceNumber
 */
	UInt32 							sequenceNumber;

/**
 * @brief The subelement identifier of the tread.
 * @var subElemId
 */
	UInt32 							subElemId;

/**
 * @brief The custom offset of the tread.
 * @var zOffset
 */
	double 							zOffset;

/**
 * @brief Role of the Stair subelement.
 * @var role
 */
	API_StairPartRoleID				role;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool	 						filler_2[4];

};

/**
 * @brief Represents a Stair Structure element.
 * @struct API_StairStructureType
 * @ingroup Element
 */
struct API_StairStructureType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;

/**
 * @brief GUID of the owning stair.
 * @var owner
 */
	API_Guid						owner;

/**
 * @brief Library part GUID.
 * @var libId
 */
	API_Guid						libId;

/**
 * @brief The number of the step that the structure element belongs to.
 * @var sequenceNumber
 */
	UInt32							sequenceNumber;

/**
 * @brief The subelement identifier of the structure element.
 * @var subElemId
 */
	UInt32							subElemId;

/**
 * @brief True, if the object is visible.
 * @var visible
 */
	bool							visible;

/**
 * @brief True, if the structure is a landing.
 * @var isLanding
 */
	bool							isLanding;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1[3];

/**
 * @brief The type of the stair structure:
 * 		  |APIST_Side|The Stair is supported at its sides.|
 * 		  |APIST_Monolith|The Stair has a solid block under it.|
 * 		  |APIST_BeamSupport|The Stair is supported by beams.|
 * 		  |APIST_CantileveredSupport|The Stair is supported at only one side.|
 *
 * @var structType
 */
	API_StairStructureTypeID		structType;

/**
 * @brief The type of the stair structure bottom:
 * 		  |APISB_Stepped|The stair structure is stepped along with the steps.|
 * 		  |APISB_Flat|The stair structure is flattened under the steps.|
 * 		  |APISB_Smooth|The stair structure is monolithic.|
 *
 * @var bottomType
 */
	API_StairStructBottomTypeID		bottomType;

/**
 * @brief The horizontal thickness of the stair structure.
 * @var horizontalThickness
 */
	double							horizontalThickness;

/**
 * @brief The thickness of the stair structure.
 * @var thickness
 */
	double							thickness;

/**
 * @brief Data of the monolithic or side supported structure.
 * @var data
 */
	union {

/**
 * @brief Data of the side supported structures.
 * @var sideStair
 */
		API_SideStairStructData			sideStair;

/**
 * @brief Data of the monolithic structures.
 * @var monolith
 */
		API_MonolithStairStructData		monolith;
		/* Beam supported and cantilevered structures don't have any extra members. */

	} data;

/**
 * @brief Role of the Stair subelement.
 * @var role
 */
	API_StairPartRoleID				role;

/**
 * @brief Supported side of the Stair:
 * 		  |APISS_LeftSide|The stair structure supports the step from the left side.|
 * 		  |APISS_RightSide|The stair structure supports the step from the right side.|
 * 		  |APISS_UnderSide|The stair structure supports the step from under.|
 *
 * @var side
 */
	API_StairStructureSideID		side;
};

/**
 * @brief Represents a Stair element.
 * @struct API_StairType
 * @ingroup Dialog
 * @remarks The Stair is a hierarchical element consisting of Tread, Riser, and Structure components:
 * 			these are the members of the Stair, arranged on a base surface according to a pre-defined scheme.
 * 			To create a Stair, one must provide its base line and position.
 */
struct API_StairType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head 					head;

/**
 * @brief The height of the stairs relative to their bottom.
 * @var totalHeight
 */
	double 							totalHeight;

/**
 * @brief The offset from top floor if the stairs are top linked.
 * @var topOffset
 */
	double 							topOffset;

/**
 * @brief Mode of linking to home story.
 * @var linkToSettings
 */
	API_LinkToSettings 				linkToSettings;

/**
 * @brief The top linked story (relative to home story).
 * @var relativeTopStory
 */
	short 							relativeTopStory;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short 							filler_1;

/**
 * @brief The width of the stairs.
 * @var flightWidth
 */
	double							flightWidth;

/**
 * @brief The number of steps (risers).
 * @var stepNum
 */
	UInt32 							stepNum;

/**
 * @brief The amount of markers associated to the Stair element on the Floor Plan display.
 * @var nFPDMarkers
 */
	UInt32 							nFPDMarkers;

/**
 * @brief The amount of markers associated to the Stair element on the Reflected Ceilind Plan display.
 * @var nRCPDMarkers
 */
	UInt32 							nRCPDMarkers;

/**
 * @brief The number of treads in this stair.
 * @var treadNum
 */
	UInt32							treadNum;

/**
 * @brief The height of each riser.
 * @var riserHeight
 */
	double 							riserHeight;

/**
 * @brief The length of each going.
 * @var treadDepth
 */
	double							treadDepth;

/**
 * @brief Going lengths are locked.
 * @var treadDepthLocked
 */
	bool	 						treadDepthLocked;

/**
 * @brief The total height of the Stair is locked.
 * @var totalHeightLocked
 */
	bool	 						totalHeightLocked;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	short 							filler_2;

/**
 * @brief Offset of the walking line, if not centered.
 * @var walkingLineOffset
 */
	double 							walkingLineOffset;

/**
 * @brief Position of the walking line:
 * 		  |APILP_Left|Offset from the left side.|
 * 		  |APILP_Right|Offset from the right side.|
 * 		  |APILP_Center|Centered.|
 * 		  |APILP_Auto|Automatic (walking lines only).|
 *
 * @var walkingLinePosition
 */
	API_LinePositionID 				walkingLinePosition;

/**
 * @brief Extra Top Tread is used to display the top tread.
 * @var extraTopTread
 */
	bool 	 						extraTopTread;

/**
 * @brief Extra Bottom Tread is used to display the top tread.
 * @var extraBottomTread
 */
	bool 	 						extraBottomTread;

/**
 * @brief Is visibile the Finishing.
 * @var finishVisible
 */
	bool 	 						finishVisible;

/**
 * @brief Position of the baseline.
 * @var baselinePosition
 */
	API_LinePositionID 				baselinePosition;

/**
 * @brief Offset of the baseline, if not centered.
 * @var baselineOffset
 */
	double 							baselineOffset;

/**
 * @brief The rules and standards of the stairs.
 * @var rules
 */
	API_StairRulesData 				rules;

/**
 * @brief Default parameters of treads.
 * @var tread
 */
	API_StairTreadType 				tread[API_StairPartRoleNum];

/**
 * @brief Default parameters of risers.
 * @var riser
 */
	API_StairRiserType 				riser[API_StairPartRoleNum];

/**
 * @brief Default parameters of stair structures.
 * @var structure
 */
	API_StairStructureType 			structure[API_StairPartRoleNum][API_StairStructureSideNum];

/**
 * @brief Display type of the Stair:
 * 		  |APIStairDisplay_Custom|Custom display.|
 * 		  |APIStairDisplay_ByModelViewOptions|Display by Model View Options.|
 *
 * @var stairDisplayType
 */
	API_StairDisplayTypeID			stairDisplayType;

/**
 * @brief The layout of the Stair element in Floor Plan Display.
 * @var fpdLayout
 */
	API_StairLayoutData				fpdLayout;

/**
 * @brief The layout of the Stair element in Reflected Ceiling Plan Display.
 * @var rcpdLayout
 */
	API_StairLayoutData				rcpdLayout;

/**
 * @brief Type of numbering for each step of the Stair element:
 * 		  |APISN_Treads|Numbering on treads.|
 * 		  |APISN_Risers|Numbering on risers.|
 *
 * @var numberingType
 */
	API_StairNumberingID 			numberingType;

/**
 * @brief The walking direction of the Stair element:
 * 		  |APISD_Upward|Default walking direction (upwards).|
 * 		  |APISD_Inverse|Inverse walking direction (downwards).|
 *
 * @var inputDirection
 */
	API_StairDirectionID 			inputDirection;

/**
 * @brief The base plane of the Stair subelements.
 * @var basePlane
 */
	API_Plane3D						basePlane;

/**
 * @brief Uniform Finish on Flight and Landing.
 * @var uniformFinish
 */
	bool  							uniformFinish;

/**
 * @brief Uniform Monolithic on Flight and Landing.
 * @var uniformMonolithAttributes
 */
	bool  							uniformMonolithAttributes;

	/**
	 * @brief Uniform Stringers on Left and Right.
	 * @var uniformLeftRightSideSupports
	 */
	bool  							uniformLeftRightSideSupports[API_StairPartRoleNum];

/**
 * @brief Uniform Drainings on Flight and Landing
 * @var uniformDrainings
 */
	bool							uniformDrainings;

/**
 * @brief The Structure is visible.
 * @var structureVisibility
 */
	bool  							structureVisibility;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	bool  							filler_3[6];

/**
 * @brief Stair Structure symbol data for 2D representations.
 * @var structSymbData
 */
	API_StairStructureSymbolData					structSymbData[API_StairStructSymbTypeNum][API_StairStructSymbViewNum];

/**
 * @brief Monolith stair structure symbol data for 2D representations.
 * @var monolithStructureSymbolData
 */
	API_StairMonolithStructureSymbolData			monolithStructureSymbolData[API_StairStructSymbViewNum][API_StairStructSymbPartNum];

/**
 * @brief Stair Structure symbol visibility for 2D representations.
 * @var structureVisibilityOnStories
 */
	API_StairStructureComponentSettingsVisibility	structureVisibilityOnStories[API_StairStructSymbViewNum];

/**
 * @brief Position of the walking line symbol:
 * 		  |APISP_Auto|Automatic positioning.|
 * 		  |APISP_Center|Centered positioning.|
 * 		  |APISP_Custom|Custom positioning.|
 *
 * @var walkLineSymbPos
 */
	API_StairWalkLineSymbPosID		walkLineSymbPos;

/**
 * @brief Data of the headroom.
 * @var stairHeadroomData
 */
	API_StairHeadroomData			stairHeadroomData;

};


// =============================================================================
// Railing
//
// =============================================================================

typedef enum {
	APIDT_Divisions,
	APIDT_PatternLength,
	APIDT_BestDivisionByLength
} API_DistribTypeID;

typedef enum {
	APIPA_StartWithPattern,
	APIPA_StartFromCenter,
	APIPA_CenterAligned,
	APIPA_EndWithPattern
} API_PatternAlignID;

typedef enum {
	APIRE_Extension,
	APIRE_Curve,
	APIRE_FullReturn,
	APIRE_ConnectWithDuplicate
} API_RailEndTypeID;

typedef enum {
	APIBC_Horizontal,
	APIBC_Tangential
} API_RailEndBaseConnectionID;

typedef enum {
	APIBB_Horizontal,
	APIBB_Tangential
} API_RailBaseBaseConnectionID;

typedef enum {
	APIRC_SegmentPlane,
	APIRC_HorizontalRight,
	APIRC_HorizontalLeft
} API_RailEndFixtureConnectionID;

typedef enum {
	APIAM_SetToVertical,
	APIAM_CustomAngle
} API_RailEndArcAngleModeID;

typedef enum {
	APIEM_CustomLength,
	APIEM_ToReferenceLine,
	APIEM_ToHandrailSibling
} API_RailEndExtrusionModeID;

typedef enum {
	APICT_NoRailConnection,
	APICT_GooseneckRailConnection,
	APICT_DirectRailConnection
} API_RailConnectionTypeID;

typedef enum {
	APIRLL_Left,
	APIRLL_Center,
	APIRLL_Right
} API_RailingRefLineLocationID;

/**
 * @brief Represents the horizontal alignment of a Railing subelement.
 * @struct API_RailingHorizontalPosData
 * @ingroup Element
 */
struct API_RailingHorizontalPosData {

/**
 * @brief The horizontal position of the element.
 * @var position
 */
	double							position;

/**
 * @brief True, if the element can be stretched.
 * @var isStretchable
 */
	bool							isStretchable;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool	 						filler_1[7];

};

/**
 * @brief Represents the vertical position of a Railing subelement.
 * @struct API_RailingVerticalPosData
 * @ingroup Element
 * @remarks The vertical position of a railing subelement calculates the bottom offset and height of a subelement by 	giving it boundaries between two rails.
 */
struct API_RailingVerticalPosData {

/**
 * @brief The index of the bottom rail.
 * @var bottomRailIndex
 */
	UInt32							bottomRailIndex;

/**
 * @brief The index of the top rail.
 * @var topRailIndex
 */
	UInt32							topRailIndex;

};

/**
 * @brief Represents the boundaries of a Railing subelement.
 * @struct API_RailingFrameData
 * @ingroup Element
 */
struct API_RailingFrameData {

/**
 * @brief Horizontal offset from Segment, perpendicularly to the plane of the segment.
 * @var yOffset
 */
	double 							yOffset;

/**
 * @brief Offset from top Rail or the top of the Segment.
 * @var zTopOffset
 */
	double 							zTopOffset;

/**
 * @brief Offset from bottom Rail or the bottom of the Segment.
 * @var zBottomOffset
 */
	double 							zBottomOffset;

/**
 * @brief Offset from left Inner Post.
 * @var xBeginOffset
 */
	double 							xBeginOffset;

/**
 * @brief Offset from right Inner Post.
 * @var xEndOffset
 */
	double 							xEndOffset;

/**
 * @brief Index of the left Inner Post.
 * @var placeIndex
 */
	UInt32 							placeIndex;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	UInt32 							filler_1;

/**
 * @brief This structure describes the vertical position of the subelement.
 * @var verticalPosition
 */
	API_RailingVerticalPosData 		verticalPosition;

};

/**
 * @brief Represents the distribution of some Railing subelements.
 * @struct API_RailingDistributionData
 * @ingroup Element
 */
struct API_RailingDistributionData {

/**
 * @brief Distribution of the given pattern:
 * 		  |APIDT_Divisions|Divide segment into patternAmount divisions.|
 * 		  |APIDT_PatternLength|Fixed pattern length.|
 * 		  |APIDT_BestDivisionByLength|Equally distributed pattern. Maximal length is given by length.|
 *
 * @var type
 */
	API_DistribTypeID 				type;

/**
 * @brief Pattern origin position:
 * 		  |APIPA_StartWithPattern|Start with pattern.|
 * 		  |APIPA_StartFromCenter|Start from center.|
 * 		  |APIPA_CenterAligned|Aligned to center.|
 * 		  |APIPA_EndWithPattern|End with pattern.|
 *
 * @var alignment
 */
	API_PatternAlignID 				alignment;

/**
 * @brief Length between divisions.
 * @var length
 */
	double 							length;

/**
 * @brief Amount of the given pattern's repetitions.
 * @var patternAmount
 */
	UInt32							patternAmount;

/**
 * @brief UNUSED PARAMETER
 * @var filler_1
 */
	UInt32 							filler_1;

};

/**
 * @brief Represents a Railing Post element.
 * @struct API_RailingPostType
 * @ingroup Element
 */
struct API_RailingPostType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head 					head;

/**
 * @brief GUID of the Railing Node element owning this Railing Post.
 * @var owner
 */
	API_Guid 						owner;

/**
 * @brief The identifier of the symbol of this element.
 * @var symbID
 */
	API_Guid 						symbID;

/**
 * @brief Vertical alignment of the Railing Post.
 * @var verticalPosition
 */
	API_RailingVerticalPosData 		verticalPosition;

};

/**
 * @brief Represents a Baluster element.
 * @struct API_RailingBalusterType
 * @ingroup Element
 */
struct API_RailingBalusterType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head 					head;

/**
 * @brief GUID of the Baluster Set owning this element.
 * @var owner
 */
	API_Guid 						owner;

/**
 * @brief The identifier of the symbol of this element.
 * @var symbID
 */
	API_Guid 						symbID;

/**
 * @brief Horizontal alignment of this element.
 * @var horizontalPosition
 */
	API_RailingHorizontalPosData	horizontalPosition;

};

/**
 * @brief Represents a Baluster Set element.
 * @struct API_RailingBalusterSetType
 * @ingroup Element
 */
struct API_RailingBalusterSetType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head 					head;

/**
 * @brief GUID of the Railing Pattern element owning this Baluster Set.
 * @var owner
 */
	API_Guid 						owner;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	API_Guid 						filler_1;

/**
 * @brief Describes the boundaries of the Baluster Set.
 * @var frame
 */
	API_RailingFrameData 			frame;

/**
 * @brief Describes the distribution of Balusters in the Baluster Set.
 * @var distribution
 */
	API_RailingDistributionData		distribution;

/**
 * @brief The default Baluster element, from which the Baluster instances will be generated.
 * @var defBaluster
 */
	API_RailingBalusterType 		defBaluster;

/**
 * @brief The amount of Balusters in the Baluster Set.
 * @var nBalusters
 */
	UInt32 							nBalusters;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	UInt32							filler_2;

};

/**
 * @brief Represents the finish of a Rail End element.
 * @struct API_RailingFinishType
 * @ingroup Element
 */
struct API_RailingFinishType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head 					head;

/**
 * @brief GUID of the Rail End element owning this Finish.
 * @var owner
 */
	API_Guid 						owner;

/**
 * @brief The identifier of the symbol of this element.
 * @var symbID
 */
	API_Guid 						symbID;

};

/**
 * @brief Represents a Rail/Handrail/Toprail End element.
 * @struct API_RailingRailEndType
 * @ingroup Element
 */
struct API_RailingRailEndType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;

/**
 * @brief GUID of the Railing Node element owning this Rail End.
 * @var owner
 */
	API_Guid 						owner;

/**
 * @brief The identifier of the symbol of this element.
 * @var symbID
 */
	API_Guid 						symbID;

/**
 * @brief The type of the Rail End:
 * 		  |APIRE_Extension|The type is extension.|
 * 		  |APIRE_Curve|The type is curved.|
 * 		  |APIRE_FullReturn|The type is full return.|
 * 		  |APIRE_ConnectWithDuplicate|The type is connection between duplicated handrails.|
 *
 * @var type
 */
	API_RailEndTypeID				type;

/**
 * @brief Connection type between the Rail End and a base:
 * 		  |APIBC_Horizontal|Connection type is horizontal.|
 * 		  |APIBC_Tangential|Connection type is tangential.|
 *
 * @var baseConnection
 */
	API_RailEndBaseConnectionID		baseConnection;

/**
 * @brief Offset of the first extrusion.
 * @var firstExtrusionOffset
 */
	double 							firstExtrusionOffset;

/**
 * @brief Length of the first extrusion.
 * @var firstExtrusionLength
 */
	double 							firstExtrusionLength;

/**
 * @brief Radius of the filleting of the Rail End.
 * @var filletRadius
 */
	double 							filletRadius;

/**
 * @brief The type of the curving in case of Curved type:
 * 		  |APIRC_SegmentPlane|The curving is in the plane of the segment.|
 * 		  |APIRC_HorizontalRight|The curving is horizontal to the right.|
 * 		  |APIRC_HorizontalLeft|The curving is horizontal to the left.|
 *
 * @var fixtureConnection
 */
	API_RailEndFixtureConnectionID	fixtureConnection;

/**
 * @brief Angle mode of the Rail End's arc:
 * 		  |APIAM_SetToVertical|The angle is absolute vertical.|
 * 		  |APIAM_CustomAngle|The angle is relative to the first extrusion.|
 *
 * @var arcAngleMode
 */
	API_RailEndArcAngleModeID		arcAngleMode;

/**
 * @brief Angle of the Rail End's arc.
 * @var arcAngle
 */
	double 							arcAngle;

/**
 * @brief Radius of the Rail End's arc.
 * @var arcRadius
 */
	double 							arcRadius;

/**
 * @brief Length of the second extrusion.
 * @var secondExtrusionLength
 */
	double 							secondExtrusionLength;

/**
 * @brief Length of the third extrusion.
 * @var thirdExtrusionLength
 */
	double 							thirdExtrusionLength;

/**
 * @brief Mode of the second extrusion:
 * 		  |APIEM_CustomLength|The length is custom.|
 * 		  |APIEM_ToReferenceLine|The length of the extrusion will be set so that it will reach the reference line.|
 * 		  |APIEM_ToHandrailSibling|In case of a handrail the length will be set so that it will reach the other handrail.<br>If this is set for one of the handrails, then the other handrail's `secondExtrusionMode` will be automatically set<br>to `APIEM_ToHandrailSibling`, too.|
 *
 * @var secondExtrusionMode
 */
	API_RailEndExtrusionModeID		secondExtrusionMode;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	UInt32 							filler_1;

/**
 * @brief Default finish for the Rail End.
 * @var finishDef
 */
	API_RailingFinishType 			finishDef;

};

/**
 * @brief Represents a connection between two Rail/Handrail/Toprail elements.
 * @struct API_RailingRailConnectionType
 * @ingroup Element
 */
struct API_RailingRailConnectionType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head					head;

/**
 * @brief GUID of the Railing Node element owning this Rail Connection.
 * @var owner
 */
	API_Guid 						owner;

/**
 * @brief The identifier of the symbol of this element.
 * @var symbID
 */
	API_Guid 						symbID;

/**
 * @brief Connection type between two Rail bases:
 * 		  |APIBB_Horizontal|Connection type is horizontal.|
 * 		  |APIBB_Tangential|Connection type is tangential.|
 *
 * @var baseConnection
 */
	API_RailBaseBaseConnectionID	baseConnection;

/**
 * @brief Connection type:
 * 		  |APICT_NoRailConnection|Disconnected.|
 * 		  |APICT_GooseneckRailConnection|Gooseneck connection.|
 * 		  |APICT_DirectRailConnection|Direct connection.|
 *
 * @var type
 */
	API_RailConnectionTypeID		type;

/**
 * @brief Offset from the end of the rail.
 * @var railEndOffset
 */
	double 							railEndOffset;

/**
 * @brief Fillet at the end of the rail.
 * @var railEndFillet
 */
	double 							railEndFillet;

/**
 * @brief Length of the first extrusion.
 * @var firstExtrusionLength
 */
	double							firstExtrusionLength;

/**
 * @brief Length of the second extrusion.
 * @var secondExtrusionLength
 */
	double							secondExtrusionLength;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	double							filler_1;

/**
 * @brief Horizontal filleting.
 * @var horizontalFillet
 */
	double							horizontalFillet;

/**
 * @brief Gooseneck filleting.
 * @var gooseneckFillet
 */
	double							gooseneckFillet;

/**
 * @brief Gooseneck offset.
 * @var gooseneckOffset
 */
	double							gooseneckOffset;

/**
 * @brief Vertical bottom filleting.
 * @var verticalBottomFillet
 */
	double							verticalBottomFillet;

/**
 * @brief Direct filleting.
 * @var directFillet
 */
	double							directFillet;

};

/**
 * @brief Represents a Railing Node element.
 * @struct API_RailingNodeType
 * @ingroup Element
 * @remarks Railing Node elements contain Railing Posts, and Rail connections and endings. 	Each Node represents a vertex in the reference line of the railing.
 */
struct API_RailingNodeType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head 					head;

/**
 * @brief GUID of the Railing element owning this Railing Node.
 * @var owner
 */
	API_Guid 						owner;

/**
 * @brief True, if the Railing Node is visible.
 * @var visible
 */
	bool	 						visible;

/**
 * @brief If unifyPatterns is false, than crop segment at Node, otherwise continue the pattern.
 * @var unifyPatterns
 */
	bool	 						unifyPatterns;

/**
 * @brief True, if the Railing Node is static.
 * @var isStatic
 */
	bool	 						isStatic;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool	 						filler_1[5];

/**
 * @brief The default Railing Post element, from which the Railing Post instances will be generated.
 * @var defPost
 */
	API_RailingPostType 			defPost;

/**
 * @brief The default Rail End element, from which the default Rail End instances will be generated.
 * @var defRailEnd
 */
	API_RailingRailEndType 			defRailEnd;

/**
 * @brief The default Handrail End elements, from which the Handrail End instances will be generated.
 * @var defHandrailEnd
 */
	API_RailingRailEndType 			defHandrailEnd[2];

/**
 * @brief The default Toprail End element, from which the Toprail End instances will be generated.
 * @var defToprailEnd
 */
	API_RailingRailEndType 			defToprailEnd;

/**
 * @brief The default Rail Connection element, from which the default Rail Connection instances will be generated.
 * @var defRailConnection
 */
	API_RailingRailConnectionType 	defRailConnection;

/**
 * @brief The default Handrail Connection elements, from which the Handrail Connection instances will be generated.
 * @var defHandrailConnection
 */
	API_RailingRailConnectionType	defHandrailConnection[2];

/**
 * @brief The default Toprail Connection element, from which the Toprail Connection instances will be generated.
 * @var defToprailConnection
 */
	API_RailingRailConnectionType	defToprailConnection;

/**
 * @brief Amount of visible posts.
 * @var visiblePostNum
 */
	short 							visiblePostNum;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	short 							filler_2[3];

/**
 * @brief Vertical offset.
 * @var elevation
 */
	double 							elevation;

/**
 * @brief Post offset from Node.
 * @var postOffset
 */
	double 							postOffset;

/**
 * @brief The number of Rail Connections.
 * @var nRailConnections
 */
	UInt32 							nRailConnections;

/**
 * @brief The number of Rail Ends.
 * @var nRailEnds
 */
	UInt32 							nRailEnds;

/**
 * @brief Offset connections automatically?
 * @var autoConnectionOffset
 */
	bool 							autoConnectionOffset;

/**
 * @brief The post is tilted.
 * @var tiltedPost
 */
	bool 							tiltedPost;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	bool 							filler_3[6];

/**
 * @brief The connection offset if not automatic.
 * @var connectionOffset
 */
	double 							connectionOffset;

/**
 * @brief The ending offset.
 * @var endingOffset
 */
	double 							endingOffset;

};

/**
 * @brief Represents a Toprail element.
 * @struct API_RailingToprailType
 * @ingroup Element
 */
struct API_RailingToprailType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head 					head;

/**
 * @brief GUID of the Railing Segment element owning this Toprail.
 * @var owner
 */
	API_Guid 						owner;

/**
 * @brief The identifier of the symbol of this element.
 * @var symbID
 */
	API_Guid 						symbID;

/**
 * @brief True, if the Rail is visible.
 * @var visible
 */
	bool	 						visible;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[7];

};

/**
 * @brief Represents a Handrail element.
 * @struct API_RailingHandrailType
 * @ingroup Element
 */
struct API_RailingHandrailType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head 					head;

/**
 * @brief GUID of the Railing Segment element owning this Handrail.
 * @var owner
 */
	API_Guid 						owner;

/**
 * @brief The identifier of the symbol of this element.
 * @var symbID
 */
	API_Guid 						symbID;

/**
 * @brief True, if the Handrail is visible.
 * @var visible
 */
	bool	 						visible;

/**
 * @brief True, if the Handrail is relative.
 * @var doubleHandrail
 */
	bool	 						doubleHandrail;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[6];

/**
 * @brief The horizontal offset of the Handrail from the Segment.
 * @var horizontalOffset
 */
	double 							horizontalOffset;

/**
 * @brief The height of the Handrail element.
 * @var height
 */
	double 							height;

};

/**
 * @brief Represents a Rail element.
 * @struct API_RailingRailType
 * @ingroup Element
 */
struct API_RailingRailType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head 					head;

/**
 * @brief GUID of the Railing Segment element owning this Rail.
 * @var owner
 */
	API_Guid 						owner;

/**
 * @brief The identifier of the symbol of this element.
 * @var symbID
 */
	API_Guid 						symbID;

/**
 * @brief True, if the Rail is visible.
 * @var visible
 */
	bool	 						visible;

/**
 * @brief True, if the Rail is relative.
 * @var relative
 */
	bool	 						relative;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[6];

/**
 * @brief The horizontal offset of the Rail from the Segment.
 * @var horizontalOffset
 */
	double 							horizontalOffset;

/**
 * @brief The height of the Rail element.
 * @var height
 */
	double 							height;

};

/**
 * @brief Represents an Inner Post element.
 * @struct API_RailingInnerPostType
 * @ingroup Element
 */
struct API_RailingInnerPostType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head 					head;

/**
 * @brief GUID of the Railing Pattern element owning this Inner Post.
 * @var owner
 */
	API_Guid 						owner;

/**
 * @brief The identifier of the symbol of this element.
 * @var symbID
 */
	API_Guid 						symbID;

/**
 * @brief Offset of the Inner Posts from the pattern.
 * @var doublePostOffset
 */
	double 							doublePostOffset;

/**
 * @brief Vertical alignment of this element.
 * @var verticalPosition
 */
	API_RailingVerticalPosData 		verticalPosition;

/**
 * @brief Horizontal alignment of this element.
 * @var horizontalPosition
 */
	API_RailingHorizontalPosData	horizontalPosition;

/**
 * @brief The amount of posts within this element (maximum of 2).
 * @var postNum
 */
	short 							postNum;				/* maximum of 2 */

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short 							filler_1[3];

};

/**
 * @brief Represents a Railing Panel element.
 * @struct API_RailingPanelType
 * @ingroup Element
 */
struct API_RailingPanelType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head 					head;

/**
 * @brief GUID of the Railing Segment element owning this Railing Panel.
 * @var owner
 */
	API_Guid 						owner;

/**
 * @brief The identifier of the symbol of this element.
 * @var symbID
 */
	API_Guid 						symbID;

/**
 * @brief True, if the Railing Panel is visible.
 * @var visible
 */
	bool	 						visible;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[7];

/**
 * @brief Describes the boundaries of the Railing Panel.
 * @var frame
 */
	API_RailingFrameData 			frame;

};

/**
 * @brief Represents a Railing Pattern element.
 * @struct API_RailingPatternType
 * @ingroup Element
 */
struct API_RailingPatternType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head 					head;

/**
 * @brief The owner railing this pattern belongs to.
 * @var owner
 */
	API_Guid 						owner;

/**
 * @brief Describes the distribution of the Pattern's subelements.
 * @var distribution
 */
	API_RailingDistributionData		distribution;

/**
 * @brief The default Railing Panel element, from which the Railing Panel instances will be generated.
 * @var defPanel
 */
	API_RailingPanelType			defPanel;

/**
 * @brief The default Baluster Set element, from which the Baluster Set instances will be generated.
 * @var defBalusterSet
 */
	API_RailingBalusterSetType 		defBalusterSet;

/**
 * @brief The default Inner Post element, from which the Inner Post instances will be generated.
 * @var defInnerPost
 */
	API_RailingInnerPostType		defInnerPost;

/**
 * @brief Amount of Railing Panels in the Railing Pattern.
 * @var nPanels
 */
	UInt32 							nPanels;

/**
 * @brief Amount of Baluster Sets in the Railing Pattern.
 * @var nBalusterSets
 */
	UInt32 							nBalusterSets;

/**
 * @brief Amount of Inner Posts in the Railing Pattern.
 * @var nInnerPosts
 */
	UInt32 							nInnerPosts;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	UInt32 							filler_1;

};

/**
 * @brief Represents a Railing Segment element.
 * @struct API_RailingSegmentType
 * @ingroup Element
 */
struct API_RailingSegmentType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head 					head;

/**
 * @brief GUID of the Railing element owning this Railing Node.
 * @var owner
 */
	API_Guid 						owner;

/**
 * @brief True, if the Railing Segment is visible.
 * @var visible
 */
	bool	 						visible;

/**
 * @brief True, if the skew angle of the Railing Segment is relative.
 * @var relativeSkewingAngle
 */
	bool							relativeSkewingAngle;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[2];

/**
 * @brief The location of the segment's reference line
 * 		  |APIRLL_Left|Reference line is on the left|
 * 		  |APIRLL_Center|Reference line is at the centre|
 * 		  |APIRLL_Right|Reference line is on the right|
 *
 * @var refLineLocation
 */
	API_RailingRefLineLocationID	refLineLocation;

/**
 * @brief The height of the Railing Segment.
 * @var height
 */
	double 							height;

/**
 * @brief Reference line offset.
 * @var yOffset
 */
	double 							yOffset;

/**
 * @brief Railing vertical offset.
 * @var zOffset
 */
	double 							zOffset;

/**
 * @brief The slanting angle of the Railing Segment.
 * @var slantAngle
 */
	double 							slantAngle;

/**
 * @brief The skewing angle of the Railing Segment.
 * @var skewAngle
 */
	double 							skewAngle;

/**
 * @brief The default Railing Pattern element, from which the Railing Pattern instances will be generated.
 * @var defPattern
 */
	API_RailingPatternType 			defPattern;

/**
 * @brief The default Handrail element, from which the upper Handrail instances will be generated.
 * @var defDefaultHandrail
 */
	API_RailingHandrailType 		defDefaultHandrail;

/**
 * @brief The default Handrail element, from which the lower Handrail instances will be generated.
 * @var defHandrails
 */
	API_RailingHandrailType 		defHandrails;

/**
 * @brief The default Toprail element, from which the Toprail instances will be generated.
 * @var defToprail
 */
	API_RailingToprailType 			defToprail;

/**
 * @brief The default Rail element, from which the default Rail instances will be generated.
 * @var defDefaultRail
 */
	API_RailingRailType 			defDefaultRail;				/* default rail data for the default rail */

/**
 * @brief The default Rail element, from which the added Rail instances will be generated.
 * @var defRails
 */
	API_RailingRailType 			defRails;					/* default rail data for additional rails */

};

/**
 * @brief Represents a Railing element.
 * @struct API_RailingType
 * @ingroup Element
 * @remarks The Railing element is a complex structure of elements, requiring each subelement to be filled correctly.
 * @image html railing_transparent.png "Raling structure" width=50%
 */
struct API_RailingType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head 					head;

/**
 * @brief The mode of linking to home story.
 * @var linkToSettings
 */
	API_LinkToSettings 				linkToSettings;

/**
 * @brief The default Railing Node element, from which the Railing Node instances will be generated.
 * @var defNode
 */
	API_RailingNodeType 			defNode;

/**
 * @brief The default Railing Segment element, from which the Railing Segment instances will be generated.
 * @var defSegment
 */
	API_RailingSegmentType			defSegment;

/**
 * @brief The story visibility of the element. See @ref API_StoryVisibility for details.
 * @var visibility
 */
	API_StoryVisibility 			visibility;

/**
 * @brief Recalculate the story visibility automatically according to the actual elevation of the railing.
 * @var isAutoOnStoryVisibility
 */
	bool	 						isAutoOnStoryVisibility;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool	 						filler_1[3];

/**
 * @brief The amount of vertices in the Railing's reference line.
 * @var nVertices
 */
	UInt32							nVertices;

/**
 * @brief The pen index of the Railing's reference line.
 * @var referenceLinePen
 */
	short  							referenceLinePen;

/**
 * @brief The pen index of the Railing's contour line.
 * @var contourPen
 */
	short  							contourPen;

/**
 * @brief The amount of Nodes in the Railing.
 * @var nNodes
 */
	UInt32 							nNodes;

/**
 * @brief The amount of Segments in the Railing.
 * @var nSegments
 */
	UInt32 							nSegments;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	UInt32 							filler_2;

/**
 * @brief TBase height of the Railing relative to the floor level.
 * @var bottomOffset
 */
	double 							bottomOffset;

};

// =============================================================================
// Opening
//
// =============================================================================

/**
 * @brief Floor plan display mode type of openings.
 * @enum API_OpeningFloorPlanDisplayModeTypeID
 * @ingroup Element
 */
typedef enum {
	API_OpeningSymbolic,
	API_OpeningSymbolicCut,
	API_OpeningSymbolicOverhead,
	API_OpeningProjected

} API_OpeningFloorPlanDisplayModeTypeID;

/**
 * @brief Representation type of openings divided by air space.
 * @enum API_OpeningFloorPlanConnectionModeTypeID
 * @ingroup Element
 */
typedef enum {
	API_OpeningDisconnected,
	API_OpeningConnected

} API_OpeningFloorPlanConnectionModeTypeID;

/**
 * @brief Cut surface parameters.
 * @struct API_OpeningCutSurfacesParameters
 * @ingroup Element
 */
struct API_OpeningCutSurfacesParameters {

/**
 * @brief Use lines of cut elements.
 * @var useLineOfCutElements
 */
	bool					useLineOfCutElements;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool					filler_1;

/**
 * @brief Cut line pen.
 * @var linePenIndex
 */
	short					linePenIndex;

/**
 * @brief Cut line index.
 * @var lineIndex
 */
	API_AttributeIndex		lineIndex;

};

/**
 * @brief Type of contours on open edges of outlines.
 * @enum API_OpeningFloorPlanOutlinesStyleTypeID
 * @ingroup Element
 */
typedef enum {
	API_OpeningHideBorder,
	API_OpeningShowUncutBorder,
	API_OpeningShowOverheadBorder

} API_OpeningFloorPlanOutlinesStyleTypeID;

/**
 * @brief Opening outlines parameters.
 * @struct API_OpeningOutlinesParameters
 * @ingroup Element
 */
struct API_OpeningOutlinesParameters {

/**
 * @brief Type of contours on open edges.
 * @var outlinesStyle
 */
	API_OpeningFloorPlanOutlinesStyleTypeID	outlinesStyle;

/**
 * @brief Use contours of cut elements.
 * @var useLineOfCutElements
 */
	bool						useLineOfCutElements;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool						filler_1;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	short						filler_2;

/**
 * @brief Uncut line.
 * @var uncutLineIndex
 */
	API_AttributeIndex			uncutLineIndex;

/**
 * @brief Overhead line.
 * @var overheadLineIndex
 */
	API_AttributeIndex			overheadLineIndex;

/**
 * @brief Uncut line pen.
 * @var uncutLinePenIndex
 */
	short						uncutLinePenIndex;

/**
 * @brief Overhead line pen.
 * @var overheadLinePenIndex
 */
	short						overheadLinePenIndex;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	short						filler_3[2];

};

/**
 * @brief Opening cover fills parameters.
 * @struct API_OpeningCoverFillsParameters
 * @ingroup Element
 */
struct API_OpeningCoverFillsParameters {

/**
 * @brief Use cover fills.
 * @var useCoverFills
 */
	bool							useCoverFills;

/**
 * @brief Use fills of cut elements.
 * @var useFillsOfCutElements
 */
	bool							useFillsOfCutElements;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief Cover fill index.
 * @var coverFillIndex
 */
	API_AttributeIndex				coverFillIndex;

/**
 * @brief Cover fill pen index.
 * @var coverFillPenIndex
 */
	short							coverFillPenIndex;

/**
 * @brief Cover fill background pen index.
 * @var coverFillBackgroundPenIndex
 */
	short							coverFillBackgroundPenIndex;

/**
 * @brief Cover fill orientation (API_HatchGlobal, @c API_HatchRotated, @c API_HatchDistorted).
 * @var coverFillOrientation
 */
	API_HatchOrientationTypeID		coverFillOrientation;

};

/**
 * @brief Opening floor plan and section reference axis parameters.
 * @struct API_OpeningReferenceAxisParameters
 * @ingroup Element
 */
struct API_OpeningReferenceAxisParameters {

/**
 * @brief Show reference axis.
 * @var showReferenceAxis
 */
	bool				showReferenceAxis;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool				filler_1;

/**
 * @brief Reference axis pen index.
 * @var referenceAxisPenIndex
 */
	short				referenceAxisPenIndex;

/**
 * @brief Reference axis line type.
 * @var referenceAxisLineTypeIndex
 */
	API_AttributeIndex	referenceAxisLineTypeIndex;

/**
 * @brief Reference axis overhang.
 * @var referenceAxisOverhang
 */
	double				referenceAxisOverhang;

};

/**
 * @brief Parameters of floor plan and section representation.
 * @struct API_OpeningFloorPlanParameters
 * @ingroup Element
 */
struct API_OpeningFloorPlanParameters {

/**
 * @brief Floor plan display type.
 * @var floorPlanDisplayMode
 */
	API_OpeningFloorPlanDisplayModeTypeID		floorPlanDisplayMode;

/**
 * @brief Floor plan connection mode.
 * @var connectionMode
 */
	API_OpeningFloorPlanConnectionModeTypeID	connectionMode;

/**
 * @brief Cut surfaces parameters.
 * @var cutSurfacesParameters
 */
	API_OpeningCutSurfacesParameters			cutSurfacesParameters;

/**
 * @brief Outlines parameters.
 * @var outlinesParameters
 */
	API_OpeningOutlinesParameters				outlinesParameters;

/**
 * @brief Cover fills parameters.
 * @var coverFillsParameters
 */
	API_OpeningCoverFillsParameters				coverFillsParameters;

/**
 * @brief Cover fill transformation.
 * @var coverFillTransformation
 */
	API_CoverFillTransformation					coverFillTransformation;

/**
 * @brief Reference axis parameters.
 * @var referenceAxisParameters
 */
	API_OpeningReferenceAxisParameters			referenceAxisParameters;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	double										filler_1;

};

/**
 * @brief Opening base polygon type.
 * @enum API_OpeningBasePolygonTypeTypeID
 * @ingroup Element
 */
typedef enum {
	API_OpeningBasePolygonRectangular,
	API_OpeningBasePolygonCircular,
	API_OpeningBasePolygonCustom

} API_OpeningBasePolygonTypeTypeID;

/**
 * @brief Opening constraint.
 * @enum API_OpeningConstraintTypeID
 * @ingroup Element
 */
typedef enum {
	API_OpeningForcedVertical,
	API_OpeningForcedHorizontal,
	API_OpeningAligned,
	API_OpeningFree

} API_OpeningConstraintTypeID;

/**
 * @brief Opening limit type.
 * @enum API_OpeningLimitTypeTypeID
 * @ingroup Element
 */
typedef enum {
	API_OpeningLimitInfinite,
	API_OpeningLimitFinite,
	API_OpeningLimitHalfInfinite

} API_OpeningLimitTypeTypeID;

/**
 * @brief Linked dimensions type for rectangular and circular openings.
 * @enum API_OpeningLinkedStatusTypeID
 * @ingroup Element
 */
typedef enum {
	API_OpeningLinked,
	API_OpeningNotLinked

} API_OpeningLinkedStatusTypeID;

/**
 * @brief Opening extrusion parameters.
 * @struct API_OpeningExtrusionParameters
 * @ingroup Element
 */
struct API_OpeningExtrusionParameters {

/**
 * @brief Type of base polygon.
 * @var basePolygonType
 */
	API_OpeningBasePolygonTypeTypeID		basePolygonType;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short									filler_1[2];

/**
 * @brief Width of base polygon. Valid only if base polygon is rectangular or circular.
 * @var width
 */
	double									width;

/**
 * @brief Height of base polygon. Valid only if base polygon is rectangular or circular.
 * @var height
 */
	double									height;

/**
 * @brief Extrusion limit type.
 * @var constraint
 */
	API_OpeningConstraintTypeID				constraint;

/**
 * @brief The anchor point of the opening.
 * @var anchor
 */
	API_AnchorID							anchor;

/**
 * @brief Altitude of opening anchor. Valid only if constraint is forced horizontal or aligned.
 * @var anchorAltitude
 */
	double									anchorAltitude;

/**
 * @brief Extrusion limit type.
 * @var limitType
 */
	API_OpeningLimitTypeTypeID				limitType;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	short									filler_2[2];

/**
 * @brief Offset from reference plane of the opening. Valid only if limitType is not infinite.
 * @var extrusionStartOffset
 */
	double									extrusionStartOffset;

/**
 * @brief Extrusion body length. Valid only if limitType is finite.
 * @var finiteBodyLength
 */
	double									finiteBodyLength;

/**
 * @brief Linked dimensions type. Valid only if base polygon is rectangular or circular.
 * @var linkedStatus
 */
	API_OpeningLinkedStatusTypeID			linkedStatus;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	short									filler_3[2];

};

/**
 * @brief Extrusion geometry parameters.
 * @struct API_OpeningExtrusionGeometryData
 * @ingroup Element
 */
struct API_OpeningExtrusionGeometryData {

/**
 * @brief Opening base plane.
 * @var frame
 */
	API_Plane3D							frame;

/**
 * @brief Extrusion parameters.
 * @var parameters
 */
	API_OpeningExtrusionParameters		parameters;

/**
 * @brief Reserved for future use.
 * @var customBasePolygon
 */
	API_Polygon							customBasePolygon;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	double								filler_1;

};

/**
 * @brief Represents an opening element
 * @struct API_OpeningType
 * @ingroup Element
 * @remarks Opening symbols can not be accessed in this version.
 */
struct API_OpeningType {

/**
 * @brief General element header.
 * @var head
 */
	API_Elem_Head 						head;

/**
 * @brief Reference to the element the opening is associated to. (see @ref API_Guid).
 * @var owner
 */
	API_Guid							owner;

/**
 * @brief Floor plan parameters of the opening.
 * @var floorPlanParameters
 */
	API_OpeningFloorPlanParameters		floorPlanParameters;

/**
 * @brief %Geometry data of the opening extrusion.
 * @var extrusionGeometryData
 */
	API_OpeningExtrusionGeometryData	extrusionGeometryData;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	double								filler_1;

};

// =============================================================================
// ExternalElem
//
// =============================================================================

constexpr USize API_ExternalElemDataSize = 1024;


/**
 * @brief A struct containing the header and data of an external element type (see @ref API_AnalyticalLinkType).
 * @struct API_ExternalElemType
 * @ingroup Element
 * @since Archicad 26
 * @remarks In version 26 the Analytical element types were replaced by the externalElem member. The former structures (e.g. @ref API_AnalyticalLinkType) can be obtained by the appropriate functions (e.g. @c ACAPI_Analytical_GetLinkFromElement).
 */
struct API_ExternalElemType {

/**
 * @brief General element header. The `typeID` should be `API_ExternalElemType`.
 * @var head
 */
	API_Elem_Head	head;

/**
 * @brief Serialized data identifying the element.
 * @var externalElemData
 */
	char			externalElemData[API_ExternalElemDataSize];
};


// =============================================================================
// General element
//
// =============================================================================

/**
 * @brief A union collecting all known element types.
 * @union API_Element
 * @ingroup Element
 * @since Archicad 26
 * @remarks Database items named elements are global collections of constuction and drawing elements which are placed onto the floorplan, Section/Elevation etc. windows.
 * 			API functions operating on the element databases begin with the @c ACAPI_Element_ prefix, refer to the Element Manager for more details.
 * 			Many element related functions use the @ref API_Element structure on the parameter list. As a general rule, you have to fill the required fields in the union, then the server application parses the request based on the values and passes the return parameters in the same parameter. This is why most of the functions do not have the const directive in the prototypes.
 * 			Refer to the Save data into the Element records document to get information how to save/assign custom data to the element records and save it into the project file for later use.
 * 			In version 26 the Analytical element types were replaced by the externalElem member. The former structures (e.g. @ref API_AnalyticalLinkType) can be obtained by the appropriate functions (e.g. @c ACAPI_Analytical_GetLinkFromElement).
 */
union API_Element {

/**
 * @brief General element header.
 * @var header
 */
	API_Elem_Head						header;


/**
 * @brief Represents a wall.
 * @var wall
 */
	API_WallType						wall;

/**
 * @brief Represents a column.
 * @var column
 */
	API_ColumnType						column;

/**
 * @brief Represents a beam.
 * @var beam
 */
	API_BeamType						beam;

/**
 * @brief Represents a window.
 * @var window
 */
	API_WindowType						window;

/**
 * @brief Represents a door.
 * @var door
 */
	API_DoorType						door;

/**
 * @brief Represents an object.
 * @var object
 */
	API_ObjectType						object;

/**
 * @brief Represents a lamp.
 * @var lamp
 */
	API_LampType						lamp;

/**
 * @brief Represents a slab.
 * @var slab
 */
	API_SlabType						slab;

/**
 * @brief Represents a roof.
 * @var roof
 */
	API_RoofType						roof;

/**
 * @brief Represents a mesh.
 * @var mesh
 */
	API_MeshType						mesh;


/**
 * @brief Represents a dimension.
 * @var dimension
 */
	API_DimensionType					dimension;

/**
 * @brief Represents a radial dimension.
 * @var radialDimension
 */
	API_RadialDimensionType				radialDimension;

/**
 * @brief Represents a level dimension.
 * @var levelDimension
 */
	API_LevelDimensionType				levelDimension;

/**
 * @brief Represents an angle dimension.
 * @var angleDimension
 */
	API_AngleDimensionType				angleDimension;


/**
 * @brief Represents a text.
 * @var text
 */
	API_TextType						text;

/**
 * @brief Represents a label.
 * @var label
 */
	API_LabelType						label;

/**
 * @brief Represents a zone.
 * @var zone
 */
	API_ZoneType						zone;


/**
 * @brief Represents a hatch.
 * @var hatch
 */
	API_HatchType						hatch;

/**
 * @brief Represents a 2D line.
 * @var line
 */
	API_LineType						line;

/**
 * @brief Represents a 2D polyline.
 * @var polyLine
 */
	API_PolyLineType					polyLine;

/**
 * @brief Represents a 2D arc.
 * @var arc
 */
	API_ArcType							arc;

/**
 * @brief Represents a 2D circle.
 * @var circle
 */
	API_CircleType						circle;

/**
 * @brief Represents a 2D spline.
 * @var spline
 */
	API_SplineType						spline;

/**
 * @brief Represents a hotspot.
 * @var hotspot
 */
	API_HotspotType						hotspot;

/**
 * @brief Represents a picture.
 * @var picture
 */
	API_PictureType						picture;


/**
 * @brief Represents a section.
 * @var cutPlane
 */
	API_CutPlaneType					cutPlane;

/**
 * @brief Represents an elevation.
 * @var elevation
 */
	API_ElevationType					elevation;

/**
 * @brief Represents an interior elevation.
 * @var interiorElevation
 */
	API_InteriorElevationType			interiorElevation;

/**
 * @brief Represents a camera.
 * @var camera
 */
	API_CameraType						camera;

/**
 * @brief Represents a camera set.
 * @var camset
 */
	API_CamSetType						camset;


/**
 * @brief Represents a drawing element.
 * @var drawing
 */
	API_DrawingType						drawing;

/**
 * @brief Represents an element in the section window.
 * @var sectElem
 */
	API_SectElemType					sectElem;

/**
 * @brief Represents a detail drawing.
 * @var detail
 */
	API_DetailType						detail;

/**
 * @brief Represents a worksheet.
 * @var worksheet
 */
	API_WorksheetType					worksheet;

/**
 * @brief Represents a hotlink.
 * @var hotlink
 */
	API_HotlinkType						hotlink;


/**
 * @brief Represents a curtain wall.
 * @var curtainWall
 */
	API_CurtainWallType					curtainWall;

/**
 * @brief Represents a curtain wall segment.
 * @var cwSegment
 */
	API_CWSegmentType					cwSegment;

/**
 * @brief Represents a curtain wall frame.
 * @var cwFrame
 */
	API_CWFrameType						cwFrame;

/**
 * @brief Represents a curtain wall panel.
 * @var cwPanel
 */
	API_CWPanelType						cwPanel;

/**
 * @brief Represents a curtain wall junction.
 * @var cwJunction
 */
	API_CWJunctionType					cwJunction;

/**
 * @brief Represents a curtain wall accessory.
 * @var cwAccessory
 */
	API_CWAccessoryType					cwAccessory;

/**
 * @brief Represents a shell (kind of a roof with special geometry).
 * @var shell
 */
	API_ShellType						shell;

/**
 * @brief Represents a morph.
 * @var morph
 */
	API_MorphType						morph;

/**
 * @brief Represents a skylight (a window put into roofs and shells).
 * @var skylight
 */
	API_SkylightType					skylight;

/**
 * @brief Represents a ChangeMarker.
 * @var changeMarker
 */
	API_ChangeMarkerType				changeMarker;


/**
 * @brief Represents a Stair.
 * @var stair
 */
	API_StairType 						stair;

/**
 * @brief Represents a Riser.
 * @var stairRiser
 */
	API_StairRiserType 					stairRiser;

/**
 * @brief Represents a Tread.
 * @var stairTread
 */
	API_StairTreadType 					stairTread;

/**
 * @brief Represents a Stair structure.
 * @var stairStructure
 */
	API_StairStructureType				stairStructure;


/**
 * @brief Represents a Railing structure.
 * @var railing
 */
	API_RailingType						railing;

/**
 * @brief Represents a Toprail structure.
 * @var railingToprail
 */
	API_RailingToprailType				railingToprail;

/**
 * @brief Represents a Handrail structure.
 * @var railingHandrail
 */
	API_RailingHandrailType				railingHandrail;

/**
 * @brief Represents a Rail structure.
 * @var railingRail
 */
	API_RailingRailType					railingRail;

/**
 * @brief Represents a Toprail End structure.
 * @var railingToprailEnd
 */
	API_RailingRailEndType				railingToprailEnd;

/**
 * @brief Represents a Handrail End structure.
 * @var railingHandrailEnd
 */
	API_RailingRailEndType				railingHandrailEnd;

/**
 * @brief Represents a Rail End structure.
 * @var railingRailEnd
 */
	API_RailingRailEndType				railingRailEnd;

/**
 * @brief Represents the finish of a Rail End element.
 * @var railingEndFinish
 */
	API_RailingFinishType 				railingEndFinish;

/**
 * @brief Represents a Toprail Connection structure.
 * @var railingToprailConnection
 */
	API_RailingRailConnectionType		railingToprailConnection;

/**
 * @brief Represents a Handrail Connection structure.
 * @var railingHandrailConnection
 */
	API_RailingRailConnectionType		railingHandrailConnection;

/**
 * @brief Represents a Rail Connection structure.
 * @var railingRailConnection
 */
	API_RailingRailConnectionType		railingRailConnection;

/**
 * @brief Represents a Railing Post structure.
 * @var railingPost
 */
	API_RailingPostType					railingPost;

/**
 * @brief Represents an Inner Post structure.
 * @var railingInnerPost
 */
	API_RailingInnerPostType			railingInnerPost;

/**
 * @brief Represents a Baluster Set structure.
 * @var railingBalusterSet
 */
	API_RailingBalusterSetType			railingBalusterSet;

/**
 * @brief Represents a Baluster structure.
 * @var railingBaluster
 */
	API_RailingBalusterType				railingBaluster;

/**
 * @brief Represents a Railing Panel structure.
 * @var railingPanel
 */
	API_RailingPanelType				railingPanel;

/**
 * @brief Represents a Railing Node structure.
 * @var railingNode
 */
	API_RailingNodeType					railingNode;

/**
 * @brief Represents a Railing Segment structure.
 * @var railingSegment
 */
	API_RailingSegmentType				railingSegment;

/**
 * @brief Represents a Railing Pattern structure.
 * @var railingPattern
 */
	API_RailingPatternType				railingPattern;


/**
 * @brief Represents a Column segment structure.
 * @var columnSegment
 */
	API_ColumnSegmentType				columnSegment;

/**
 * @brief Represents a Beam segment structure.
 * @var beamSegment
 */
	API_BeamSegmentType					beamSegment;

/**
 * @brief Represents an Opening.
 * @var opening
 */
	API_OpeningType						opening;

/**
 * @brief Represents an external element. See remarks for more information.
 * @var externalElem
 */
	API_ExternalElemType				externalElem;

};


#define	ACAPI_ELEMENT_MASK_CLEAR(rec)				memset (&rec, 0, sizeof (API_Element))
#define	ACAPI_ELEMENT_MASK_SETFULL(rec)				memset (&rec, 0xFF, sizeof (API_Element))
#define	ACAPI_ELEMENT_MASK_SET(rec,typ,varnam)		*((char *) &((typ *) &rec)->varnam) = -1
#define	ACAPI_ELEMENT_MASK_CHECK(rec,typ,varnam)	(*((char *) &((typ *) &rec)->varnam) != 0)
#define	ACAPI_ELEMENT_MASK_CLEAR1(rec,typ,varnam)	*((char *) &((typ *) &rec)->varnam) = 0

#define	ACAPI_ELEMENT_CHANGEEXT_ALLSEGMENTS			-1L

// =============================================================================
// Additional (dynamic) data of elements
//
// =============================================================================

#define APIMemoMask_Polygon						0x0000000000000001
#define APIMemoMask_Gables						0x0000000000000002
#define APIMemoMask_AddPars						0x0000000000000004
#define APIMemoMask_EdgeTrims					0x0000000000000008
#define APIMemoMask_MeshPolyZ					0x0000000000000010
#define APIMemoMask_MeshLevel					0x0000000000000020
#define APIMemoMask_BeamHole					0x0000000000000040
#define APIMemoMask_TextContent					0x0000000000000080
#define APIMemoMask_Paragraph					0x0000000000000100
#define APIMemoMask_TextContentUni				0x0000000000000200
#define APIMemoMask_ParagraphUni				0x0000000000000400
#define APIMemoMask_DrawingData					0x0000000000000800
#define APIMemoMask_CustomOrigProfile			0x0000000000001000
#define APIMemoMask_StretchedProfile			0x0000000000002000
#define APIMemoMask_SectionSegments				0x0000000000004000
#define APIMemoMask_SectionMainCoords			0x0000000000008000
#define APIMemoMask_SectionDistCoords			0x0000000000010000
#define APIMemoMask_SectionDepthCoords			0x0000000000020000
#define APIMemoMask_WallWindows					0x0000000000040000
#define APIMemoMask_WallDoors					0x0000000000080000
#define APIMemoMask_CWSegGridMesh				0x0000000000100000
#define APIMemoMask_CWSegPrimaryPattern			0x0000000000200000
#define APIMemoMask_CWSegSecPattern				0x0000000000400000
#define APIMemoMask_CWSegPanelPattern			0x0000000000800000
#define APIMemoMask_CWSegContour				0x0000000001000000
#define APIMemoMask_CWallSegments				0x0000000002000000
#define APIMemoMask_CWallFrames					0x0000000004000000
#define APIMemoMask_CWallPanels					0x0000000008000000
#define APIMemoMask_CWallJunctions				0x0000000010000000
#define APIMemoMask_CWallAccessories			0x0000000020000000
#define APIMemoMask_FromFloorplan				0x0000000040000000
#define APIMemoMask_RoofEdgeTypes				0x0000000080000000
#define APIMemoMask_SideMaterials				0x0000000100000000
#define APIMemoMask_AdditionalPolygon			0x0000000200000000
#define APIMemoMask_ElemInfoString				0x0000000400000000
#define APIMemoMask_StairRiser					0x0000000800000000
#define APIMemoMask_StairTread					0x0000001000000000
#define APIMemoMask_StairStructure				0x0000002000000000
#define APIMemoMask_RailingNode					0x0000004000000000
#define APIMemoMask_RailingSegment				0x0000008000000000
#define APIMemoMask_RailingPost					0x0000010000000000
#define APIMemoMask_RailingInnerPost			0x0000020000000000
#define APIMemoMask_RailingRail					0x0000040000000000
#define APIMemoMask_RailingHandrail				0x0000080000000000
#define APIMemoMask_RailingToprail				0x0000100000000000
#define APIMemoMask_RailingPanel				0x0000200000000000
#define APIMemoMask_RailingBaluster				0x0000400000000000
#define APIMemoMask_RailingPattern				0x0000800000000000
#define APIMemoMask_RailingBalusterSet			0x0001000000000000
#define APIMemoMask_RailingRailEnd				0x0002000000000000
#define APIMemoMask_RailingHandrailEnd			0x0004000000000000
#define APIMemoMask_RailingToprailEnd			0x0008000000000000
#define APIMemoMask_RailingRailConnection		0x0010000000000000
#define APIMemoMask_RailingHandrailConnection	0x0020000000000000
#define APIMemoMask_RailingToprailConnection	0x0040000000000000
#define APIMemoMask_CWallFrameClasses			0x0080000000000000
#define APIMemoMask_CWallPanelClasses			0x0100000000000000
#define APIMemoMask_BeamSegment					0x0200000000000000
#define APIMemoMask_ColumnSegment				0x0400000000000000
#define APIMemoMask_AssemblySegmentCut			0x0800000000000000
#define APIMemoMask_AssemblySegmentScheme		0x1000000000000000
#define APIMemoMask_AssemblySegmentProfile		0x2000000000000000
#define APIMemoMask_SurfaceLoadCustomData		0x4000000000000000
#define APIMemoMask_EdgeLoadCustomData			0x8000000000000000

#define APIMemoMask_All				   		   (0x3FFFFFFFFFFFFFFF &~ APIMemoMask_FromFloorplan)

/**
 * @brief Describes the variable length additional data of elements.
 * @struct API_ElementMemo
 * @ingroup Element
 * @remarks See @ref ACAPI_Element_GetMemo to find out which element type needs/provides which information in the memo.
 * 			If you retrieve an array of vertices, edges or contours with @ref ACAPI_Element_GetMemo, do not change the IDs in these arrays. New vertices, edges and contours should be inserted with ID = 0.
 */
struct API_ElementMemo {

/**
 * @brief Coordinate array (used for polygons, spline coordinates, etc.).
 * @var coords
 */
	API_Coord						**coords;

/**
 * @brief Polygon endpoints; see @ref API_Polygon for more information.
 * @var pends
 */
	Int32							**pends;

/**
 * @brief Polygon arcs; see @ref API_PolyArc and @ref API_Polygon for more information.
 * @var parcs
 */
	API_PolyArc						**parcs;

/**
 * @brief Unique identifiers the polygon vertices (unique inside the polygon).
 * @var vertexIDs
 */
	UInt32							**vertexIDs;

/**
 * @brief Unique identifiers the polygon edges (unique inside the polygon).
 * @var edgeIDs
 */
	UInt32							**edgeIDs;

/**
 * @brief Unique identifiers the polygon contours (unique inside the polygon).
 * @var contourIDs
 */
	UInt32							**contourIDs;

/**
 * @brief Additional parameters for library part-based elements.
 * @var params
 */
	API_AddParType					**params;

/**
 * @brief Parameters of the cutting planes the element has been cut with.
 * @var gables
 */
	API_Gable						**gables;

/**
 * @brief Trim data of slab/roof/shell edges. (Formerly roofSides.)
 * @var edgeTrims
 */
	API_EdgeTrim					**edgeTrims;

/**
 * @brief Z coordinates of mesh polygon points.
 * @var meshPolyZ
 */
	double							**meshPolyZ;

/**
 * @brief Mesh level line coordinates.
 * @var meshLevelCoords
 */
	API_MeshLevelCoord				**meshLevelCoords;

/**
 * @brief Mesh level line endpoints.
 * @var meshLevelEnds
 */
	Int32							**meshLevelEnds;

/**
 * @brief Dimension elements.
 * @var dimElems
 */
	API_DimElem						**dimElems;

/**
 * @brief Bezier-spline directions.
 * @var bezierDirs
 */
	API_SplineDir					**bezierDirs;

/**
 * @brief Text content for textual elements.
 * @var textContent
 */
	GS::UniString					*textContent;

/**
 * @brief Text line starts array (indices into the text content).
 * @var textLineStarts
 */
	short							**textLineStarts;

/**
 * @brief Beam hole information.
 * @var beamHoles
 */
	API_Beam_Hole					**beamHoles;

/**
 * @brief Camera link list.
 * @var linkList
 */
	API_LinkType					**linkList;

/**
 * @brief Picture content.
 * @var pictHdl
 */
	char							**pictHdl;

/**
 * @brief Paragraph informations for text and label element.
 * @var paragraphs
 */
	API_ParagraphType				**paragraphs;


/**
 * @brief Internal format drawing data of an @ref API_DrawingType element.
 * @var drawingData
 */
	GSPtr							drawingData;

/**
 * @brief The original custom profile data applied to the wall, beam, or column element, in @c HGX::VectorImage format (see @ref API_ProfileAttrType).
 * @var customOrigProfile
 */
	ProfileVectorImage				*customOrigProfile;

/**
 * @brief The stretched profile actually used by the wall, beam, or column element, in @c HGX::VectorImage format (see @ref API_ProfileAttrType).
 * @var stretchedProfile
 */
	ProfileVectorImage				*stretchedProfile;


/**
 * @brief Reserved for internal use.
 * @var customParams
 */
	GSPtr							customParams;


/**
 * @brief Segments of an interior elevation.
 * @var intElevSegments
 */
	API_SectionSegment				*intElevSegments;

/**
 * @brief Coordinates of the section/elevation/interior elevation main line.
 * @var sectionSegmentMainCoords
 */
	API_Coord						*sectionSegmentMainCoords;

/**
 * @brief Coordinates of the section/elevation/interior elevation marked distant area line.
 * @var sectionSegmentDistCoords
 */
	API_Coord						*sectionSegmentDistCoords;

/**
 * @brief Coordinates of the section/elevation/interior elevation depth line.
 * @var sectionSegmentDepthCoords
 */
	API_Coord						*sectionSegmentDepthCoords;


/**
 * @brief Guid list of Window elements in the specified Wall (output only).
 * @var wallWindows
 */
	API_Guid						*wallWindows;

/**
 * @brief Guid list of Door elements in the specified Wall (output only).
 * @var wallDoors
 */
	API_Guid						*wallDoors;


/**
 * @brief Curtain wall segment grid mesh.
 * @var cWSegGridMesh
 */
	API_GridMesh					*cWSegGridMesh;

/**
 * @brief The contour of Curtain Wall segments.
 * @var cWSegContour
 */
	API_CWContourData				*cWSegContour;

/**
 * @brief Curtain Wall primary segment pattern.
 * @var cWSegPrimaryPattern
 */
	API_CWSegmentPatternData		cWSegPrimaryPattern;

/**
 * @brief Curtain Wall secondary segment pattern.
 * @var cWSegSecondaryPattern
 */
	API_CWSegmentPatternData		cWSegSecondaryPattern;

/**
 * @brief Curtain Wall segment pattern cells.
 * @var cWSegPatternCells
 */
	API_CWSegmentPatternCellData 	*cWSegPatternCells;

/**
 * @brief Curtain Wall segments.
 * @var cWallSegments
 */
	API_CWSegmentType				*cWallSegments;

/**
 * @brief Curtain Wall frame instances.
 * @var cWallFrames
 */
	API_CWFrameType					*cWallFrames;

/**
 * @brief Curtain Wall custom frame defaults (categories/classes).
 * @var cWallFrameDefaults
 */
	API_CWFrameType					*cWallFrameDefaults;

/**
 * @brief Curtain Wall panel instances.
 * @var cWallPanels
 */
	API_CWPanelType					*cWallPanels;

/**
 * @brief This table contains the grid mesh identifiers for each Curtain Wall panel instance (these grid mesh cells are partly or fully covered by the panel).
 * @var cWallPanelGridIDTable
 */
	API_CWPanelGridIDTable			*cWallPanelGridIDTable;

/**
 * @brief Curtain Wall panel defaults (categories/classes).
 * @var cWallPanelDefaults
 */
	API_CWPanelType					*cWallPanelDefaults;

/**
 * @brief Curtain Wall junction instances.
 * @var cWallJunctions
 */
	API_CWJunctionType				*cWallJunctions;

/**
 * @brief Curtain Wall accessory instances.
 * @var cWallAccessories
 */
	API_CWAccessoryType				*cWallAccessories;


/**
 * @brief Stair Riser subelements.
 * @var stairRisers
 */
	API_StairRiserType				*stairRisers;

/**
 * @brief Stair Tread subelements.
 * @var stairTreads
 */
	API_StairTreadType				*stairTreads;

/**
 * @brief Stair Structure subelements.
 * @var stairStructures
 */
	API_StairStructureType			*stairStructures;


/**
 * @brief Stair boundaries (index 0 is the left, and 1 is the right).
 * @var stairBoundary
 */
	API_StairBoundaryData			stairBoundary[2];

/**
 * @brief The base line of a Stair element.
 * @var stairBaseLine
 */
	API_StairPolylineData 			stairBaseLine;

/**
 * @brief The walking line of a Stair element.
 * @var stairWalkingLine
 */
	API_StairPolylineData 			stairWalkingLine;

/**
 * @brief The customized walking line of a Stair element.
 * @var stairCustomWalkLine
 */
	API_StairPolylineData 			stairCustomWalkLine;

/**
 * @brief The default, centered walking line of a Stair element.
 * @var stairCenterWalkLine
 */
	API_StairPolylineData 			stairCenterWalkLine;


/**
 * @brief Railing Node subelements.
 * @var railingNodes
 */
	API_RailingNodeType 			*railingNodes;

/**
 * @brief Railing Segment subelements.
 * @var railingSegments
 */
	API_RailingSegmentType 			*railingSegments;

/**
 * @brief Railing Post subelements.
 * @var railingPosts
 */
	API_RailingPostType 			*railingPosts;

/**
 * @brief Rail End subelements.
 * @var railingRailEnds
 */
	API_RailingRailEndType 			*railingRailEnds;

/**
 * @brief Rail Connection subelements.
 * @var railingRailConnections
 */
	API_RailingRailConnectionType 	*railingRailConnections;

/**
 * @brief Handrail End subelements. Only filled for Railing elements. If a Railing Node element is queried, these can be found inside the Element's structure.
 * @var railingHandrailEnds
 */
	API_RailingRailEndType 			*railingHandrailEnds;

/**
 * @brief Handrail Connection subelements. Only filled for Railing elements. If a Railing Node element is queried, these can be found inside the Element's structure.
 * @var railingHandrailConnections
 */
	API_RailingRailConnectionType 	*railingHandrailConnections;

/**
 * @brief Toprail End subelements. Only filled for Railing elements. If a Railing Node element is queried, these can be found inside the Element's structure.
 * @var railingToprailEnds
 */
	API_RailingRailEndType 			*railingToprailEnds;

/**
 * @brief Toprail Connection subelements. Only filled for Railing elements. If a Railing Node element is queried, these can be found inside the Element's structure.
 * @var railingToprailConnections
 */
	API_RailingRailConnectionType 	*railingToprailConnections;

/**
 * @brief Rail subelements.
 * @var railingRails
 */
	API_RailingRailType 			*railingRails;

/**
 * @brief Toprail subelements.
 * @var railingToprails
 */
	API_RailingToprailType 			*railingToprails;

/**
 * @brief Handrail subelements.
 * @var railingHandrails
 */
	API_RailingHandrailType 		*railingHandrails;

/**
 * @brief Railing Pattern subelements.
 * @var railingPatterns
 */
	API_RailingPatternType 			*railingPatterns;

/**
 * @brief Inner Post subelements.
 * @var railingInnerPosts
 */
	API_RailingInnerPostType		*railingInnerPosts;

/**
 * @brief Railing panel subelements.
 * @var railingPanels
 */
	API_RailingPanelType			*railingPanels;

/**
 * @brief Baluster Set subelements.
 * @var railingBalusterSets
 */
	API_RailingBalusterSetType 		*railingBalusterSets;

/**
 * @brief Baluster subelements.
 * @var railingBalusters
 */
	API_RailingBalusterType 		*railingBalusters;


/**
 * @brief Array for the Z coordinates of a coordinate array.
 * @var polyZCoords
 */
	double 							**polyZCoords;


/**
 * @brief Roof edge types.
 * @var roofEdgeTypes
 */
	API_RoofEdgeTypeID				*roofEdgeTypes;

/**
 * @brief Roof / Slab side materials.
 * @var sideMaterials
 */
	API_OverriddenAttribute			*sideMaterials;


/**
 * @brief Coordinate array of the pivot polygon of a Multi-plane Roof element (see @ref API_PolyRoofData) or the found polygon of the zone element. In case of zones, it can be nullptr if zone does not have found polygon. Also this is output only parameter for zones. Can be accessed with the @c APIMemoMask_AdditionalPolygon memo mask.
 * @var additionalPolyCoords
 */
	API_Coord						**additionalPolyCoords;

/**
 * @brief Polygon endpoints of the pivot polygon of a Multi-plane Roof element (see @ref API_PolyRoofData) or the found polygon of the zone element. Can be accessed with the @c APIMemoMask_AdditionalPolygon memo mask. See also @ref API_Polygon for more information.
 * @var additionalPolyPends
 */
	Int32							**additionalPolyPends;

/**
 * @brief Polygon arcs of the pivot polygon of a Multi-plane Roof element (see @ref API_PolyRoofData) or the found polygon of the zone element. Can be accessed with the @c APIMemoMask_AdditionalPolygon memo mask. See also @ref API_PolyArc and @ref API_Polygon for more information.
 * @var additionalPolyParcs
 */
	API_PolyArc						**additionalPolyParcs;

/**
 * @brief Unique identifiers the polygon vertices of the pivot polygon of a Multi-plane Roof element (see @ref API_PolyRoofData). Not used for zones. Can be accessed with the @c APIMemoMask_AdditionalPolygon memo mask.
 * @var additionalPolyVertexIDs
 */
	UInt32							**additionalPolyVertexIDs;

/**
 * @brief Unique identifiers the polygon edges of the pivot polygon of a Multi-plane Roof element (see @ref API_PolyRoofData). Not used for zones. Can be accessed with the @c APIMemoMask_AdditionalPolygon memo mask.
 * @var additionalPolyEdgeIDs
 */
	UInt32							**additionalPolyEdgeIDs;

/**
 * @brief Unique identifiers the polygon contours of the pivot polygon of a Multi-plane Roof element (see @ref API_PolyRoofData). Not used for zones. Can be accessed with the @c APIMemoMask_AdditionalPolygon memo mask.
 * @var additionalPolyContourIDs
 */
	UInt32							**additionalPolyContourIDs;


/**
 * @brief Multi-plane roof specific data associated to the edges of the pivot polygon. They contain geometry (angle, eavesOverHang) and attribute (material etc.) data for each segment (see @ref API_PivotPolyEdgeData). Can be accessed with the @c APIMemoMask_PivotPolygon memo mask.
 * @var pivotPolyEdges
 */
	API_PivotPolyEdgeData			*pivotPolyEdges;


/**
 * @brief Shell specific data to describe the profiles that form the shell shape. Extruded and revolved shells use the first (0-indexed) record only, ruled shells use both. This is a required parameter to pass when creating a new shell element.
 * @var shellShapes
 */
	API_ShellShapeData				shellShapes[2];

/**
 * @brief Shell specific data to define body contour and hole contours to the shell element. If hasContour is true, the first record contains the body contour data. If the shell has holes (numHoles > 0), the following items of the array describe the hole contours (the first hole contour is located in the second (1-indexed) record if there is a body contour given, otherwise it is in the first (0-indexed) record).
 * @var shellContours
 */
	API_ShellContourData			*shellContours;


/**
 * @brief Morph element.
 * @var morphBody
 */
	Modeler::MeshBody				*morphBody;

/**
 * @brief Morph element.
 * @var morphMaterialMapTable
 */
	API_OverriddenAttribute			*morphMaterialMapTable;


/**
 * @brief Info string of the element.
 * @var elemInfoString
 */
	GS::UniString					*elemInfoString;


/**
 * @brief Beam segments.
 * @var beamSegments
 */
	API_BeamSegmentType				*beamSegments;

/**
 * @brief Column segments.
 * @var columnSegments
 */
	API_ColumnSegmentType			*columnSegments;

/**
 * @brief Cuts of segments.
 * @var assemblySegmentCuts
 */
	API_AssemblySegmentCutData		*assemblySegmentCuts;

/**
 * @brief Segment schemes.
 * @var assemblySegmentSchemes
 */
	API_AssemblySegmentSchemeData	*assemblySegmentSchemes;

/**
 * @brief Segment profiles.
 * @var assemblySegmentProfiles
 */
	API_AssemblySegmentProfileData	*assemblySegmentProfiles;

/**
 * @brief External element data.
 * @var externalElemData
 */
	GS::Any							*externalElemData;

};


// ====================================================================================
/**
 * @brief Describes the filter for the different subtypes of elements.
 * @enum API_SubElementType
 * @ingroup Element
 * @since Archicad 26
 * @remarks This enumeration was renamed in Archicad 25, the previous name was @c API_SubElemMemoMaskType.
 */
enum API_SubElementType : UInt64 {
	APISubElement_MainMarker					= 0x0000000000000001,
	APISubElement_SHMarker						= 0x0000000000000002,
	APISubElement_CommonMarker					= 0x0000000000000004,
	APISubElement_CWFrameClass					= 0x0000000000000008,
	APISubElement_CWPanelClass					= 0x0000000000000010,
	APISubElement_CWJunction					= 0x0000000000000020,
	APISubElement_CWAccessory					= 0x0000000000000040,
	APISubElement_StairRiser					= 0x0000000000000080,
	APISubElement_StairTread					= 0x0000000000000100,
	APISubElement_StairStructure				= 0x0000000000000200,
	APISubElement_StairFPDMarker				= 0x0000000000000400,
	APISubElement_StairRCPDMarker				= 0x0000000000000800,
	APISubElement_RailingNode					= 0x0000000000001000,
	APISubElement_RailingSegment				= 0x0000000000002000,
	APISubElement_RailingPost					= 0x0000000000004000,
	APISubElement_RailingInnerPost				= 0x0000000000008000,
	APISubElement_RailingRail					= 0x0000000000010000,
	APISubElement_RailingHandrail				= 0x0000000000020000,
	APISubElement_RailingToprail				= 0x0000000000040000,
	APISubElement_RailingPanel					= 0x0000000000080000,
	APISubElement_RailingBaluster				= 0x0000000000100000,
	APISubElement_RailingPattern				= 0x0000000000200000,
	APISubElement_RailingBalusterSet			= 0x0000000000400000,
	APISubElement_RailingRailEnd				= 0x0000000000800000,
	APISubElement_RailingHandrailEnd			= 0x0000000001000000,
	APISubElement_RailingToprailEnd				= 0x0000000002000000,
	APISubElement_RailingRailConnection			= 0x0000000004000000,
	APISubElement_RailingHandrailConnection		= 0x0000000008000000,
	APISubElement_RailingToprailConnection		= 0x0000000010000000,
	APISubElement_RailingFinish					= 0x0000000020000000,
	APISubElement_CWTag							= 0x1000000000000000,
	APISubElement_NoElem						= 0x2000000000000000,
	APISubElement_NoParams						= 0x4000000000000000
//													    5432109876543210
};

enum API_SubElemFlagType : UInt32 {
	APISubElemFlag_Run								= 0x00000001,	// stair subelement role: run
	APISubElemFlag_Landing							= 0x00000002,	// stair subelement role: landing
	APISubElemFlag_LeftSide 						= 0x00000004,	// stair structure side: right
	APISubElemFlag_RightSide 						= 0x00000008,	// stair structure side: left
	APISubElemFlag_UnderSide 						= 0x00000010,	// stair structure side: under
	APISubElemFlag_GridMarker						= 0x00000020,	// stair marker type: grid
	APISubElemFlag_BreakMarkMarker					= 0x00000040,	// stair marker type: breakmark
	APISubElemFlag_WalkingLineMarker				= 0x00000080,	// stair marker type: walking line
	APISubElemFlag_NumberingMarker					= 0x00000100,	// stair marker type: numbering
	APISubElemFlag_UpDownTextMarker					= 0x00000200,	// stair marker type: up/down text
	APISubElemFlag_DescriptionMarker				= 0x00000400,	// stair marker type: description
	APISubElemFlag_DefaultDefault 					= 0x00000800	// railing subelement: default default
};

/**
 * @brief Helper structure to create / modify / get markers for window, door, section, elevation, interior elevation, detail, worksheet elements and curtain wall parts.
 * @struct API_SubElement
 * @ingroup Element
 * @since Archicad 25
 * @remarks This structure reduces the number of parameters passed to @ref ACAPI_Element_GetDefaultsExt, @ref ACAPI_Element_ChangeDefaultsExt, @ref ACAPI_Element_CreateExt, and @ref ACAPI_Element_ChangeExt.
 * 			This enumeration was renamed in Archicad 25, the previous name was @c API_SubElemMemoMask.
 */
struct API_SubElement {

/**
 * @brief The sub element.
 * @var subElem
 */
	API_Element						subElem;

/**
 * @brief The sub element mask.
 * @var mask
 */
	API_Element						mask;

/**
 * @brief The memo of the sub element.
 * @var memo
 */
	API_ElementMemo					memo;


/**
 * @brief The type of this sub element.
 * @var subType
 */
	API_SubElementType				subType;

/**
 * @brief Used only for identify Interior Elevation, Curtain Wall, and Railing sub-segment by modification.
 * @var subIndex
 */
	Int32							subIndex;

/**
 * @brief Second-Level Subelement Index (Railing).
 * @var subSubIndex
 */
	UInt32 							subSubIndex;

/**
 * @brief Subelement Flags (Stair).
 * @var subElemFlags
 */
	UInt32 							subElemFlags;


/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

};

// =============================================================================
// Custom data stored into elements
//
// =============================================================================

#define APIUserDataFlag_FillWith	0x00000004					// inject userdata into element from default
#define APIUserDataFlag_Pickup		0x00000008					// copy userdata into default at element parameter transfer

/**
 * @brief Custom data record attached to element sets.
 * @struct API_UserData
 * @ingroup Grouping
 * @remarks The possible values of flags are:
 * 			|Value|Meaning|
 * 			|-----|-------|
 * 			|@c APIUserDataFlag_Copy| Copy the user data into the copied element also|
 * 			|@c APIUserDataFlag_Merge| Merge user data with the element|
 * 			|@c APIUserDataFlag_FillWith| Inject user data into the element instance from the element default|
 * 			|@c APIUserDataFlag_Pickup| Copy user data into the element default at parameter transfer|
 * 			|@c APIUserDataFlag_SkipRecalcAndDraw| @ref ACAPI_Element_SetUserData skips recalculation and redraw (input only<br>control flag).|
 * 			From Archicad 20 all user data operations should be undoable.
 */
struct API_UserData {

/**
 * @brief the version of the user data
 * @var dataVersion
 */
	short							dataVersion;

/**
 * @brief the platform the data was created on; defines the byte ordering (can be         GS::Win_Platform_Sign, GS::Mac_Platform_Sign or GS::Mactel_Platform_Sign
 * @var platformSign
 */
	unsigned short					platformSign;

/**
 * @brief Special flags
 * 		  | @c APIUserDataFlag_Pickup | copy userdata into default at element parameter transfer |
 * 		  | @c APIUserDataFlag_SkipRecalcAndDraw | @ref ACAPI_Element_SetUserData skips recalc and redraw (input only control flag) |
 * 		  | @c APIUserDataFlag_FillWith | inject userdata into element from default |
 * @var flags
 */
	GSFlags							flags;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief handle containing the user data (arbitrary size)
 * @var dataHdl
 */
	GSHandle						dataHdl;

};

/**
 * @brief A UserData attached to an Element
 * @ingroup Element
 */
using API_ElementUserData = API_UserData;
/**
 * @brief A UserData attached to an Attribute
 * @ingroup Attribute
 */
using API_AttributeUserData = API_UserData;


// =============================================================================
// Element relations
//
// =============================================================================

/**
 * @brief Section of a wall segment that neighbours a border line of the room.
 * @struct API_WallPart
 * @ingroup Element
 * @sa API_CWSegmentPart
 * @remarks The `API_WallPart` structure is a member of @ref API_RoomRelation.
 * 			The following example shows how to interpret this data.
 * @image html RoomWallPart.png "Room wall part" width=50%
 */
struct API_WallPart {
/**
 * @brief Guid of the wall.
 * @var guid
 */
	API_Guid						guid;

/**
 * @brief Index of the room polygon edge adjacent to the wall.
 * @var roomEdge
 */
	Int32							roomEdge;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	Int32							filler;

/**
 * @brief Beginning distance of the section from the beginning point of the wall.
 * @var tBeg
 */
	double							tBeg;

/**
 * @brief End distance of the section from the beginning point of the wall.
 * @var tEnd
 */
	double							tEnd;
};

/**
 * @brief Section of a curtain wall segment that neighbours a border line of the room.
 * @ingroup Element
 * @remarks The @ref API_WallPart structure is a member of @ref API_RoomRelation. The following example shows how to interpret this data.
 * @sa API_WallPart
 */
using API_CWSegmentPart = API_WallPart;

/**
 * @brief Structure describing a niche in a room.
 * @struct API_Niche
 * @ingroup Element
 * @remarks The `API_Niche` structure is a member of @ref API_RoomRelation.
 * 			If you need to add niches to area or volume calculation of a room, get the room relations with the @ref ACAPI_Element_GetRelations function.
 */
struct API_Niche {

/**
 * @brief Coordinate array.
 * @var coords
 */
	API_Coord						**coords;

/**
 * @brief Polygon endpoints; see @ref API_Polygon for more information.
 * @var pends
 */
	Int32							**pends;

/**
 * @brief Polygon arcs; see @ref API_PolyArc and @ref API_Polygon for more information.
 * @var parcs
 */
	API_PolyArc						**parcs;

/**
 * @brief Height of the niche
 * @var height
 */
	double							height;

};

/**
 * @brief Section of a beam that crosses the room.
 * @struct API_BeamPart
 * @ingroup Element
 * @remarks The @ref API_BeamPart structure is a member of @ref API_RoomRelation. The following example shows how to interpret this data.
 * @image html RoomBeamPart.png "Room beam part" width=50%
 * 		  `@ref API_RoomRelation`ß\n
 * 		  | nBeamPart | | 2 |
 * 		  | beamPart[0] | | |
 * 		  |   | tBeg | 0.00 |
 * 		  |   | tEnd | 2.05 |
 * 		  | beamPart[1] | |
 * 		  |   | tBeg | 0.30 |
 * 		  |   | tEnd | 4.00 |
 */
struct API_BeamPart {

/**
 * @brief GUID of the beam
 * @var guid
 */
	API_Guid						guid;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	Int32							filler[2];

/**
 * @brief Beginning distance of the section from the beginning point of the beam
 * @var tBeg
 */
	double							tBeg;

/**
 * @brief End distance of the section from the beginning point of the beam
 * @var tEnd
 */
	double							tEnd;

};

/**
 * @brief Structure for retrieving data related to a room.
 * @struct API_RoomRelation
 * @ingroup Element
 * @since Archicad 26
 * @remarks Get the array's size with it's GetSize() function.
 * 			To learn more about the usage of the room relation structure please refer to the @ref ACAPI_Element_GetRelations function.
 * 			From version 26 the type of the elementsGroupedByType member was changed into GS::HashTable< @ref API_ElemType, GS::Array<API_Guid>>.
 */
struct API_RoomRelation {

/**
 * @brief Related elements of the room grouped by type. The keys in this table are the types and the values are the GUIDs of the elements with the given type.
 * @var elementsGroupedByType
 */
	GS::HashTable<API_ElemType, GS::Array<API_Guid>>	elementsGroupedByType;

/**
 * @brief Wall parts that borders the room polygon
 * @var wallPart
 */
	GS::Array<API_WallPart>								wallPart;

/**
 * @brief Beam parts that related to the room.
 * @var beamPart
 */
	GS::Array<API_BeamPart>								beamPart;

/**
 * @brief Curtain Wall Segment parts that related to the room.
 * @var cwSegmentPart
 */
	GS::Array<API_CWSegmentPart>						cwSegmentPart;

/**
 * @brief Niches inside the room.
 * @var niches
 */
	GS::Array<API_Niche>								niches;

};


/**
 * @brief Represents a wall or beam connection.
 * @struct API_ConnectionGuidItem
 * @ingroup Element
 * @remarks For more details see @ref API_WallRelation, @ref API_BeamRelation, and @ref API_BeamSegmentRelation structures.
 */
struct API_ConnectionGuidItem {

/**
 * @brief guid          of the wall, beam, or beam segment connected with its reference line to the given element.
 * @var guid
 */
	API_Guid	guid;

/**
 * @brief The wall, beam, or beam segment is connected with its beginning or the end point.
 * @var conWithBeg
 */
	bool		conWithBeg;

/**
 * @brief Reserve4d for further use.
 * @var filler_1
 */
	bool		filler_1[7];

};


/**
 * @brief Structure for retrieving connection data of a wall.
 * @struct API_WallRelation
 * @ingroup Element
 * @remarks To learn more about the usage of the wall relation structure please refer to the @ref ACAPI_Element_GetRelations function. Explanatory figure for wall relation cases:
 * @image html WallRelation.png "Wall relation" width=50%
 */
struct API_WallRelation {

/**
 * @brief Coordinates of the modified outline polygon
 * @var coords
 */
	API_Coord						**coords;

/**
 * @brief Indices of the end coordinates of the subpolygons
 * @var pends
 */
	Int32							**pends;

/**
 * @brief Arc segments of the modified outline polygon
 * @var parcs
 */
	API_PolyArc						**parcs;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief Modified outline polygon due to the connections
 * @var connPoly
 */
	API_Polygon						connPoly;


/**
 * @brief List of walls connected to the beginning point of the wall with their beginning or end point.
 * @var conBeg
 */
	API_ConnectionGuidItem			**conBeg;

/**
 * @brief List of walls connected to the end point of the wall with their beginning or end point.
 * @var conEnd
 */
	API_ConnectionGuidItem			**conEnd;

/**
 * @brief List of walls connected with their reference line to the beginning or the end point of the wall.
 * @var conRef
 */
	API_ConnectionGuidItem			**conRef;

/**
 * @brief List of walls connected to the reference line of the wall not at the endpoints.
 * 		  +/- values: connection with their beg/end point
 * @var con
 */
	API_ConnectionGuidItem			**con;

/**
 * @brief List of walls having intersections with the reference line of the wall
 * @var conX
 */
	API_ConnectionGuidItem			**conX;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[5];


/**
 * @brief Number of `conBeg` indices
 * @var nConBeg
 */
	Int32							nConBeg;

/**
 * @brief Number of `conEnd` indices
 * @var nConEnd
 */
	Int32							nConEnd;

/**
 * @brief Number of `conRef` indices
 * @var nConRef
 */
	Int32							nConRef;

/**
 * @brief Number of `con` indices
 * @var nCon
 */
	Int32							nCon;

/**
 * @brief Number of `conX` indices
 * @var nConX
 */
	Int32							nConX;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3[5];

};


/**
 * @brief Structure for retrieving connection data of a beam segment.
 * @struct API_BeamSegmentRelation
 * @ingroup Element
 * @remarks To learn more about the usage of the beam segment relation structure please refer to the @ref ACAPI_Element_GetRelations function.
 */
struct API_BeamSegmentRelation {

/**
 * @brief Coordinates of the modified outline polygon
 * @var coords
 */
	API_Coord							**coords;

/**
 * @brief Indices of the end coordinates of the subpolygons
 * @var pends
 */
	Int32								**pends;

/**
 * @brief Arc segments of the modified outline polygon (used with curved beams
 * @var parcs
 */
	API_PolyArc							**parcs;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32								filler_1;

/**
 * @brief Modified outline polygon due to the connections
 * @var connPoly
 */
	API_Polygon							connPoly;


/**
 * @brief List of beam segments connected to the beginning point of the beam segment with their beginning or end point.
 * @var conBeg
 */
	GS::Array<API_ConnectionGuidItem>	*conBeg;

/**
 * @brief List of beam segments connected to the end point of the beam segment with their beginning or end point.
 * @var conEnd
 */
	GS::Array<API_ConnectionGuidItem>	*conEnd;

/**
 * @brief List of beam segments connected with their reference line to the beginning or the end point of the beam segment.
 * @var conRef
 */
	GS::Array<API_ConnectionGuidItem>	*conRef;

/**
 * @brief List of beam segments connected to the reference line of the beam segment not at the endpoints.
 * 		  +/- values: connection with beginning/end point
 * @var con
 */
	GS::Array<API_ConnectionGuidItem>	*con;


/**
 * @brief List of beam segments having intersection with the reference line of the beam segment.
 * @var conX
 */
	GS::Array<API_ConnectionGuidItem>	*conX;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	double								filler_2[8];

};


/**
 * @brief Structure for retrieving connection data of a beam.
 * @struct API_BeamRelation
 * @ingroup Element
 * @remarks To learn more about the usage of the beam relation structure please refer to the @ref ACAPI_Element_GetRelations function.
 * 			Explanatory figure for beam relation cases:
 * @image html BeamRelation.png "Beam relation" width=50%
 */
struct API_BeamRelation {

/**
 * @brief Coordinates of the modified outline polygon
 * @var coords
 */
	API_Coord							**coords;

/**
 * @brief Indices of the end coordinates of the subpolygons
 * @var pends
 */
	Int32								**pends;

/**
 * @brief Arc segments of the modified outline polygon (used with curved beams
 * @var parcs
 */
	API_PolyArc							**parcs;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32								filler_1;

/**
 * @brief Modified outline polygon due to the connections
 * @var connPoly
 */
	API_Polygon							connPoly;


/**
 * @brief List of beams connected to the beginning point of the beam with their beginning or end point (see figure).
 * @var conBeg
 */
	GS::Array<API_ConnectionGuidItem>	*conBeg;

/**
 * @brief List of beams connected to the end point of the beam with their beginning or end point (see figure).
 * @var conEnd
 */
	GS::Array<API_ConnectionGuidItem>	*conEnd;

/**
 * @brief List of beams connected with their reference line to the beginning or the end point of the beam (see figure).
 * @var conRef
 */
	GS::Array<API_ConnectionGuidItem>	*conRef;

/**
 * @brief List of beams connected to the reference line of the beam not at the endpoints (see figure).
 * 		  +/- values: connection with beginning/end point
 * @var con
 */
	GS::Array<API_ConnectionGuidItem>	*con;

/**
 * @brief List of beams having intersection with the reference line of the beam (see figure).
 * @var conX
 */
	GS::Array<API_ConnectionGuidItem>	*conX;


/**
 * @brief List of relations of the beam's segments.
 * @var segmentRelations
 */
	GS::Array<API_BeamSegmentRelation>	*segmentRelations;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32								filler_2[5];

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32								filler_3[5];

};

/**
 * @brief Structure for retrieving connection data of a curtain wall panel, skylight, window or a door element.
 * @struct API_CWPanelRelation
 * @ingroup Element
 * @remarks To learn more about the usage of this relation structure please refer to the @ref ACAPI_Element_GetRelations function. See also @ref API_SkylightRelation.
 */
struct API_CWPanelRelation {
/**
 * @brief Guid of the room connected to the requested element.
 * @var fromRoom
 */
	API_Guid						fromRoom;
/**
 * @brief Guid of the room connected to the requested element.
 * @var toRoom
 */
	API_Guid						toRoom;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	double							filler[8];
};

/**
 * @brief Structure for retrieving connection data of a curtain wall panel, skylight, window or a door element.
 * @ingroup Element
 * @remarks To learn more about the usage of this relation structure please refer to the @ref ACAPI_Element_GetRelations function. See also @ref API_CWPanelRelation.
 */
using API_SkylightRelation = API_CWPanelRelation;

/**
 * @brief Structure for retrieving connection data of a curtain wall panel, skylight, window or a door element.
 * @ingroup Element
 * @remarks To learn more about the usage of this relation structure please refer to the @ref ACAPI_Element_GetRelations function. See also @ref API_CWPanelRelation.
 */
using API_WindowRelation = API_CWPanelRelation;

/**
 * @brief Structure for retrieving connection data of a curtain wall panel, skylight, window or a door element.
 * @ingroup Element
 * @remarks To learn more about the usage of this relation structure please refer to the @ref ACAPI_Element_GetRelations function. See also @ref API_CWPanelRelation.
 */
using API_DoorRelation = API_CWPanelRelation;

/**
 * @brief Structure for retrieving connection data of a roof or a shell element.
 * @ingroup Element
 * @struct API_RoofRelation
 * @remarks To learn more about the usage of this relation structure please refer to the @ref ACAPI_Element_GetRelations function. See also @ref API_ShellRelation.
 */
struct API_RoofRelation {
/**
 * @brief Array of guid of the rooms connected to the roof or shell.
 * @var rooms
 */
	GS::Array<API_Guid>*			rooms;
};

/**
 * @brief Structure for retrieving connection data of a roof or a shell element.
 * @ingroup Element
 * @remarks To learn more about the usage of this relation structure please refer to the @ref ACAPI_Element_GetRelations function. See also @ref API_RoofRelation.
 */
using API_ShellRelation = API_RoofRelation;


// =============================================================================
// 3D information
//
// =============================================================================

/**
 * @brief 3D data of an element.
 * @struct API_ElemInfo3D
 * @ingroup  ModelAccess
 * @remarks Use the @ref ACAPI_ModelAccess_Get3DInfo function to get the 3D representation of a construction element.
 * 			Once an element is converted to 3D, it will have the following components:
 * 			- model information based on BODYs,
 * 			- lighting model based on LIGHTs; if lights are defined from the 3D GDL script,
 * 			- materials; either from the global attribute pool, or defined from the 3D GDL script.
 * 			All of the data can be accessed through the @ref API_Component3D structure.
 */
struct API_ElemInfo3D {

/**
 * @brief It is equal to the incoming element index.
 * @var fElemIdx
 */
	UInt32							fElemIdx;

/**
 * @brief It is always zero.
 * @var fBodyIdx
 */
	UInt32							fBodyIdx;

/**
 * @brief It is equal to the incoming element index.
 * @var lElemIdx
 */
	UInt32							lElemIdx;

/**
 * @brief Index of the last body which belongs to the element. (not flat list)
 * @var lBodyIdx
 */
	UInt32							lBodyIdx;

/**
 * @brief Index of the first body which belongs to the element.
 * @var fbody
 */
	Int32							fbody;

/**
 * @brief Index of the last body which belongs to the element.
 * @var lbody
 */
	Int32							lbody;

/**
 * @brief Index of the first light source which belongs to the element.
 * @var flight
 */
	Int32							flight;

/**
 * @brief Index of the last light source which belongs to the element.
 * @var llight
 */
	Int32							llight;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1[2];

/**
 * @brief The 3D bounding box of the element.
 * @var bounds
 */
	API_Box3D						bounds;

};


// =============================================================================
// ShapePrims parameters
//
// =============================================================================

/**
 * @brief Shape primitive parameters.
 * @struct API_ShapePrimsParams
 * @ingroup DrawingPrimitive
 * @remarks Use the @ref ACAPI_DrawingPrimitive_ShapePrimsExt function to virtually draw the shape of an element.
 */
struct API_ShapePrimsParams {

/**
 * @brief Pass false to turn off clippings when exploding a drawing.
 * @var dontClip
 */
	bool							dontClip;

/**
 * @brief Pass false to use the drawing only on the current story
 * @var allStories
 */
	bool							allStories;

/**
 * @brief Set a pointer to Geometry::Polygon2D to set that as a clipping polygon for the drawing.
 * @var polygon
 */
	Geometry::Polygon2D*			polygon;

};


// =============================================================================
// Quantities
//
// =============================================================================

/**
 * @brief Describes the different calculated values for walls.
 * @struct API_WallQuantity
 * @ingroup Element
 * @remarks See also the wall parameters for listing in Appendix A of the GDL Reference manual.
 * 			The columnsVolume member was never calculated, so we removed it in API 21.
 */
struct API_WallQuantity {

/**
 * @brief volume of the wall
 * @var volume
 */
	double							volume;

/**
 * @brief conditional volume of the wall
 * @var volume_cond
 */
	double							volume_cond;

/**
 * @brief wall skin volume on the reference line side
 * @var volumeASkin
 */
	double							volumeASkin;

/**
 * @brief wall skin volume on the side opposite to the reference line
 * @var volumeBSkin
 */
	double							volumeBSkin;

/**
 * @brief conditional wall skin volume on the reference line side
 * @var volumeASkin_cond
 */
	double							volumeASkin_cond;

/**
 * @brief conditional wall skin volume on the side opposite to the reference line
 * @var volumeBSkin_cond
 */
	double							volumeBSkin_cond;

/**
 * @brief surface of the wall on the reference line side
 * @var surface1
 */
	double							surface1;

/**
 * @brief surface of the wall on the side opposite to the reference line
 * @var surface2
 */
	double							surface2;

/**
 * @brief surface of the edge of the wall
 * @var surface3
 */
	double							surface3;

/**
 * @brief conditional surface of the wall on the reference line side
 * @var surface1_cond
 */
	double							surface1_cond;

/**
 * @brief conditional surface of the wall on the side opposite to the reference line
 * @var surface2_cond
 */
	double							surface2_cond;

/**
 * @brief length of the wall (average of the length on the reference line side and on the side opposite to the reference line)
 * @var length
 */
	double							length;

/**
 * @brief surface of windows in the wall
 * @var windowsSurf
 */
	double							windowsSurf;

/**
 * @brief surface of doors in the wall
 * @var doorsSurf
 */
	double							doorsSurf;

/**
 * @brief surface of empty openings in the wall
 * @var emptyholesSurf
 */
	double							emptyholesSurf;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	double							filler_0;

/**
 * @brief number of columns in the wall
 * @var columnsNumber
 */
	Int32							columnsNumber;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief combined width of windows in the wall
 * @var windowsWidth
 */
	double							windowsWidth;

/**
 * @brief combined width of doors in the wall
 * @var doorsWidth
 */
	double							doorsWidth;

/**
 * @brief Minimum height of the wall
 * @var minHeight
 */
	double							minHeight;

/**
 * @brief Maximum height of the wall
 * @var maxHeight
 */
	double							maxHeight;

/**
 * @brief Minimum height of the wall skin on the reference line side
 * @var minHeightASkin
 */
	double							minHeightASkin;

/**
 * @brief Maximum height of the wall skin on the reference line
 * @var maxHeightASkin
 */
	double							maxHeightASkin;

/**
 * @brief Minimum height of the wall skin on the side opposite to the reference line
 * @var minHeightBSkin
 */
	double							minHeightBSkin;

/**
 * @brief Maximum height of the wall skin on the side opposite to the reference line
 * @var maxHeightBSkin
 */
	double							maxHeightBSkin;

/**
 * @brief Length of the wall at the center
 * @var centerLength
 */
	double							centerLength;

/**
 * @brief Area of the wall
 * @var area
 */
	double							area;

/**
 * @brief Perimeter of the wall
 * @var perimeter
 */
	double							perimeter;

/**
 * @brief Gross volume of the wall
 * @var grossVolume
 */
	double							grossVolume;

/**
 * @brief Gross surface of the wall on the reference line side
 * @var grossSurf1
 */
	double							grossSurf1;

/**
 * @brief Gross surface of the wall on the side opposite to the reference line
 * @var grossSurf2
 */
	double							grossSurf2;

/**
 * @brief Analytic volume of openings in the wall
 * @var emptyHolesVolume
 */
	double							emptyHolesVolume;

/**
 * @brief Analytic surface of openings on the reference line side
 * @var emptyHolesSurf1
 */
	double							emptyHolesSurf1;

/**
 * @brief Analytic surface of openings on the side opposite to the reference line
 * @var emptyHolesSurf2
 */
	double							emptyHolesSurf2;


/**
 * @brief Length of the wall on the reference line side
 * @var length12
 */
	double							length12;

/**
 * @brief Length of the wall on the side opposite to the reference line
 * @var length34
 */
	double							length34;

/**
 * @brief Conditional length of the wall on the reference line side
 * @var length12_cond
 */
	double							length12_cond;

/**
 * @brief Conditional length of the wall on the side opposite to the reference line
 * @var length34_cond
 */
	double							length34_cond;

/**
 * @brief Wall insulation skin thickness
 * @var insuThickness
 */
	double							insuThickness;

/**
 * @brief Wall air skin thickness
 * @var airThickness
 */
	double							airThickness;

/**
 * @brief Wall skin thickness on the reference line side
 * @var skinAThickness
 */
	double							skinAThickness;

/**
 * @brief Wall skin thickness on the side opposite to the reference line
 * @var skinBThickness
 */
	double							skinBThickness;

/**
 * @brief Length of the reference line
 * @var refLineLength
 */
	double							refLineLength;

};

/**
 * @brief Describes the different calculated values for columns.
 * @struct API_ColumnQuantity
 * @ingroup Element
 * @remarks See also the column description in Appendix A of the GDL Reference manual.
 */
struct API_ColumnQuantity {

/**
 * @brief surface of the column core
 * @var coreSurface
 */
	double							coreSurface;

/**
 * @brief surface of the column veneer
 * @var veneSurface
 */
	double							veneSurface;

/**
 * @brief volume of the column core
 * @var coreVolume
 */
	double							coreVolume;

/**
 * @brief volume of the column veneer
 * @var veneVolume
 */
	double							veneVolume;

/**
 * @brief minimum height of the column
 * @var minHeight
 */
	double							minHeight;

/**
 * @brief maximum height of the column
 * @var maxHeight
 */
	double							maxHeight;

/**
 * @brief perimeter of the column
 * @var perimeter
 */
	double							perimeter;

/**
 * @brief area of the column
 * @var area
 */
	double							area;

/**
 * @brief gross surface of the core
 * @var coreGrossSurf
 */
	double							coreGrossSurf;

/**
 * @brief gross surface of the veneer
 * @var veneGrossSurf
 */
	double							veneGrossSurf;

/**
 * @brief area of the columns begin cross section
 * @var crossSectionAreaCutBegin
 */
	double							crossSectionAreaCutBegin;

/**
 * @brief area of the columns end cross section
 * @var crossSectionAreaCutEnd
 */
	double							crossSectionAreaCutEnd;

/**
 * @brief gross volume of the core
 * @var coreGrossVolume
 */
	double							coreGrossVolume;

/**
 * @brief gross volume of the veneer
 * @var veneGrossVolume
 */
	double							veneGrossVolume;

/**
 * @brief surface of the core top
 * @var coreTopSurf
 */
	double							coreTopSurf;

/**
 * @brief surface of the core bottom
 * @var coreBotSurf
 */
	double							coreBotSurf;

/**
 * @brief surface of the veneer top
 * @var veneTopSurf
 */
	double							veneTopSurf;

/**
 * @brief surface of the veneer bottom
 * @var veneBotSurf
 */
	double							veneBotSurf;

/**
 * @brief gross surface of the core top and bottom
 * @var coreGrossTopBotSurf
 */
	double							coreGrossTopBotSurf;

/**
 * @brief gross surface of the veneer top and bottom
 * @var veneGrossTopBotSurf
 */
	double							veneGrossTopBotSurf;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	double							filler_1[2];

};

/**
 * @brief Describes the different calculated values for column segments.
 * @struct API_ColumnSegmentQuantity
 * @ingroup Element
 */
struct API_ColumnSegmentQuantity {

/**
 * @brief surface of the column segments side veneer
 * @var veneerSideSurface
 */
	double							veneerSideSurface;

/**
 * @brief surface of the column segments bottom veneer
 * @var veneerBottomSurface
 */
	double							veneerBottomSurface;

/**
 * @brief surface of the column segments top veneer
 * @var veneerTopSurface
 */
	double							veneerTopSurface;

/**
 * @brief gross surface of the column segments veneer
 * @var veneerGrossSurface
 */
	double							veneerGrossSurface;

/**
 * @brief gross surface of the column segments top veneer
 * @var veneerGrossTopSurface
 */
	double							veneerGrossTopSurface;

/**
 * @brief gross surface of the column segments bottom veneer
 * @var veneerGrossBottomSurface
 */
	double							veneerGrossBottomSurface;


/**
 * @brief gross surface of the column segments core
 * @var coreGrossSurface
 */
	double							coreGrossSurface;

/**
 * @brief gross surface of the column segments top core
 * @var coreGrossTopSurface
 */
	double							coreGrossTopSurface;

/**
 * @brief gross surface of the column segments bottom core
 * @var coreGrossBottomSurface
 */
	double							coreGrossBottomSurface;


/**
 * @brief gross volume of the column segment
 * @var grossVolume
 */
	double							grossVolume;

/**
 * @brief gross volume of the column segments core
 * @var coreGrossVolume
 */
	double							coreGrossVolume;

/**
 * @brief gross volume of the column segments veneer
 * @var veneerGrossVolume
 */
	double							veneerGrossVolume;


/**
 * @brief net surface of the column segments bottom core
 * @var coreNetBottomSurface
 */
	double							coreNetBottomSurface;

/**
 * @brief net surface of the column segments core
 * @var coreNetSurface
 */
	double							coreNetSurface;

/**
 * @brief net surface of the column segments top core
 * @var coreNetTopSurface
 */
	double							coreNetTopSurface;


/**
 * @brief volume of the column segments core
 * @var coreVolume
 */
	double							coreVolume;

/**
 * @brief net volume of the column segments veneer
 * @var veneerNetVolume
 */
	double							veneerNetVolume;


/**
 * @brief length of the column segment
 * @var length
 */
	double							length;

/**
 * @brief area of the column segment
 * @var area
 */
	double							area;

/**
 * @brief volume of the column segment
 * @var volume
 */
	double							volume;


/**
 * @brief area of the column segments begin cross section
 * @var crossSectionAreaCutBegin
 */
	double							crossSectionAreaCutBegin;

/**
 * @brief area of the column segments end cross section
 * @var crossSectionAreaCutEnd
 */
	double							crossSectionAreaCutEnd;


/**
 * @brief minimum height of the column segment
 * @var minHeight
 */
	double							minHeight;

/**
 * @brief maximum height of the column segment
 * @var maxHeight
 */
	double							maxHeight;

/**
 * @brief height of the column segment
 * @var height
 */
	double							height;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	double							filler_1[8];

};

/**
 * @brief Describes the different calculated values for beams.
 * @struct API_BeamQuantity
 * @ingroup Element
 * @remarks See also the beam parameters for listing in Appendix A of the GDL Reference manual.
 */
struct API_BeamQuantity {

/**
 * @brief area of the beam
 * @var area
 */
	double							area;

/**
 * @brief length of the beam on the right side of the reference line
 * @var rightLength
 */
	double							rightLength;

/**
 * @brief length of the beam on the left side of the reference line
 * @var leftLength
 */
	double							leftLength;

/**
 * @brief surface of the bottom of the beam
 * @var bottomSurface
 */
	double							bottomSurface;

/**
 * @brief surface of the top of the beam
 * @var topSurface
 */
	double							topSurface;

/**
 * @brief surface of the beam on the left side of the reference line
 * @var edgeSurfaceLeft
 */
	double							edgeSurfaceLeft;

/**
 * @brief surface of the beam on the right side of the reference line
 * @var edgeSurfaceRight
 */
	double							edgeSurfaceRight;

/**
 * @brief surface of both ends of the beam
 * @var edgeSurface
 */
	double							edgeSurface;

/**
 * @brief total surface of holes in the beam
 * @var holesSurface
 */
	double							holesSurface;

/**
 * @brief total surface of hole edges in the beam
 * @var holesEdgeSurface
 */
	double							holesEdgeSurface;

/**
 * @brief number of holes in the beam
 * @var holesNumber
 */
	Int32							holesNumber;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief area of the beams begin cross section
 * @var crossSectionAreaCutBegin
 */
	double							crossSectionAreaCutBegin;

/**
 * @brief area of the beams end cross section
 * @var crossSectionAreaCutEnd
 */
	double							crossSectionAreaCutEnd;

/**
 * @brief volume of the beam
 * @var volume
 */
	double							volume;

/**
 * @brief conditional volume of the beam
 * @var volume_cond
 */
	double							volume_cond;

/**
 * @brief total volume of holes in the beam
 * @var holesVolume
 */
	double							holesVolume;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	double							filler_2[6];

};

/**
 * @brief Describes the different calculated values for beam segments.
 * @struct API_BeamSegmentQuantity
 * @ingroup Element
 */
struct API_BeamSegmentQuantity {

/**
 * @brief surface of the ends of the beam segment
 * @var endSurface
 */
	double							endSurface;

/**
 * @brief surface of the left side of the beam segment
 * @var leftSurface
 */
	double							leftSurface;

/**
 * @brief surface of the right side of the beam segment
 * @var rightSurface
 */
	double							rightSurface;

/**
 * @brief surface of the bottom of the beam segment
 * @var bottomSurface
 */
	double							bottomSurface;

/**
 * @brief surface of the top of the beam segment
 * @var topSurface
 */
	double							topSurface;


/**
 * @brief length of the beam segment
 * @var length
 */
	double							length;

/**
 * @brief length of the beam segment on the left side
 * @var leftLength
 */
	double							leftLength;

/**
 * @brief length of the beam segment on the right side
 * @var rightLength
 */
	double							rightLength;


/**
 * @brief area of the beam segment cut section at the beginning of the segment
 * @var crossSectionAreaCutBegin
 */
	double							crossSectionAreaCutBegin;

/**
 * @brief area of the beam segment cut section at the end of the segment
 * @var crossSectionAreaCutEnd
 */
	double							crossSectionAreaCutEnd;


/**
 * @brief volume of the beam segment
 * @var volume
 */
	double							volume;


/**
 * @brief total number of holes in the beam segment
 * @var holesNumber
 */
	Int32							holesNumber;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;


/**
 * @brief total surface of holes in the beam segment
 * @var holesSurface
 */
	double							holesSurface;

/**
 * @brief total surface of hole edges in the beam segment
 * @var holesEdgeSurface
 */
	double							holesEdgeSurface;

/**
 * @brief total volume of holes in the beam segment
 * @var holesVolume
 */
	double							holesVolume;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	double							filler_2[8];

};

/**
 * @brief Describes the different calculated values for windows.
 * @ingroup Element
 * @struct API_WindowQuantity
 * @remarks See also the window parameters in Appendix A of the GDL Reference manual. See also @ref API_DoorQuantity.
 */
struct API_WindowQuantity {
/**
 * @brief Window/door opening width on the reveal side
 * @var width1
 */
	double							width1;

/**
 * @brief Window/door opening width on the side opposite to the reveal side
 * @var width2
 */
	double							width2;

/**
 * @brief Window/door opening height on the reveal side
 * @var height1
 */
	double							height1;

/**
 * @brief Window/door opening height on the side opposite to the reveal side
 * @var height2
 */
	double							height2;

/**
 * @brief Window/door opening surface on the reveal side
 * @var surface1
 */
	double							surface1;

/**
 * @brief Window/door opening surface on the side opposite to the reveal side
 * @var surface2
 */
	double							surface2;

/**
 * @brief Nominal window/door opening width on the reveal side
 * @var nWidth1
 */
	double							nWidth1;

/**
 * @brief Nominal window/door opening width on the side opposite to the reveal side
 * @var nWidth2
 */
	double							nWidth2;

/**
 * @brief Nominal window/door opening height on the reveal side
 * @var nHeight1
 */
	double							nHeight1;

/**
 * @brief Nominal window/door opening height on the side opposite to the reveal side
 * @var nHeight2
 */
	double							nHeight2;

/**
 * @brief Nominal window/door opening surface on the side opposite to the reveal side
 * @var nSurface1
 */
	double							nSurface1;

/**
 * @brief Nominal window/door opening surface on the side opposite to the reveal side
 * @var nSurface2
 */
	double							nSurface2;

/**
 * @brief Window/door opening volume
 * @var volume
 */
	double							volume;

/**
 * @brief Window/door opening nominal surface
 * @var grossSurf
 */
	double							grossSurf;

/**
 * @brief Window/door opening nominal volume
 * @var grossVolume
 */
	double							grossVolume;

/**
 * @brief surface of the window/door
 * @var surface
 */
	double							surface;

/**
 * @brief Window/door nominal sill height
 * @var sillHeight
 */
	double							sillHeight;

/**
 * @brief Window/door sill height on the reveal side
 * @var sillHeight1
 */
	double							sillHeight1;

/**
 * @brief Window/door sill height on the side opposite to the reveal side
 * @var sillHeight2
 */
	double							sillHeight2;

/**
 * @brief Window/door nominal head height
 * @var headHeight
 */
	double							headHeight;

/**
 * @brief Window/door head height on the reveal side
 * @var headHeight1
 */
	double							headHeight1;

/**
 * @brief Window/door head height on the side opposite to the reveal side
 * @var headHeight2
 */
	double							headHeight2;

/**
 * @brief Window/door sill height according to the vertical anchor.
 * @var sillHeight3
 */
	double							sillHeight3;

/**
 * @brief Window/door head height according to the vertical anchor.
 * @var headHeight3
 */
	double							headHeight3;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	double							filler_1[7];
};

/**
 * @brief Describes the different calculated values for doors.
 * @ingroup Element
 * @remarks See also the window parameters in Appendix A of the GDL Reference manual. See also @ref API_WindowQuantity.
 */
using API_DoorQuantity = API_WindowQuantity;

/**
 * @brief Describes the different calculated values for skylight.
 * @struct API_SkylightQuantity
 * @ingroup Element
 * @remarks See also the window parameters in Appendix A of the GDL Reference manual.
 */
struct API_SkylightQuantity {

/**
 * @brief Skylight opening width.
 * @var openingWidth
 */
	double							openingWidth;

/**
 * @brief Skylight opening height.
 * @var openingHeight
 */
	double							openingHeight;

/**
 * @brief Skylight opening surface.
 * @var openingSurface
 */
	double							openingSurface;

/**
 * @brief Skylight opening volume
 * @var openingVolume
 */
	double							openingVolume;

/**
 * @brief Skylight sill height
 * @var sillHeight
 */
	double							sillHeight;

/**
 * @brief Skylight head height
 * @var headerHeight
 */
	double							headerHeight;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	double							filler_1[2];

};

/**
 * @brief Describes the different calculated values for objects.
 * @struct API_ObjectQuantity
 * @ingroup Element
 * @remarks These parameters are calculated from the 3D model of the object. See also @ref API_LightQuantity.
 */
struct API_ObjectQuantity {
/**
 * @brief surface of the object
 * @var surface
 */
	double							surface;

/**
 * @brief volume of the object
 * @var volume
 */
	double							volume;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	double							filler_1[8];
};

/**
 * @brief Describes the different calculated values for lights.
 * @ingroup Element
 * @remarks These parameters are calculated from the 3D model of the light. See also @ref API_ObjectQuantity.
 */
using API_LightQuantity = API_ObjectQuantity;

/**
 * @brief Returns the morph quantity values.
 * @struct API_MorphQuantity
 * @ingroup Element
 */
struct API_MorphQuantity {

/**
 * @brief Net area of the body surface.
 * @var surface
 */
	double							surface;

/**
 * @brief Net volume of the body.
 * @var volume
 */
	double							volume;

/**
 * @brief Net area of the floor plan projection.
 * @var floorPlanArea
 */
	double							floorPlanArea;

/**
 * @brief Perimeter of the floor plan projection.
 * @var floorPlanPerimeter
 */
	double							floorPlanPerimeter;

/**
 * @brief Elevation.
 * @var baseLevel
 */
	double							baseLevel;

/**
 * @brief The height range from the lowest point of inward-sloping faces to the highest point within the story height, relative to the story.
 * @var baseHeight
 */
	double							baseHeight;

/**
 * @brief Height of the morph.
 * @var wholeHeight
 */
	double							wholeHeight;

/**
 * @brief Number of the nodes of the body.
 * @var nodesNr
 */
	UInt32							nodesNr;

/**
 * @brief Number of the edges of the body.
 * @var edgesNr
 */
	UInt32							edgesNr;

/**
 * @brief Number of the hidden edges of the body.
 * @var hiddenEdgesNr
 */
	UInt32							hiddenEdgesNr;

/**
 * @brief Number of the soft edges of the body.
 * @var softEdgesNr
 */
	UInt32							softEdgesNr;

/**
 * @brief Number of the visible edges of the body.
 * @var visibleEdgesNr
 */
	UInt32							visibleEdgesNr;

/**
 * @brief Number of the faces of the body.
 * @var facesNr
 */
	UInt32							facesNr;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	double							filler_1[8];

};

/**
 * @brief Describes the different calculated values for slabs.
 * @struct API_SlabQuantity
 * @ingroup Element
 * @remarks See also the slab parameters for listing in Appendix A of the GDL Reference manual.
 */
struct API_SlabQuantity {

/**
 * @brief bottom surface of the slab
 * @var bottomSurface
 */
	double							bottomSurface;

/**
 * @brief top surface of the slab
 * @var topSurface
 */
	double							topSurface;

/**
 * @brief surface of the edges of the slab
 * @var edgeSurface
 */
	double							edgeSurface;

/**
 * @brief conditional bottom surface of the slab
 * @var bottomSurface_cond
 */
	double							bottomSurface_cond;

/**
 * @brief conditional top surface of the slab
 * @var topSurface_cond
 */
	double							topSurface_cond;

/**
 * @brief volume of the slab
 * @var volume
 */
	double							volume;

/**
 * @brief conditional volume of the slab
 * @var volume_cond
 */
	double							volume_cond;

/**
 * @brief perimeter of the slab
 * @var perimeter
 */
	double							perimeter;

/**
 * @brief total area of holes in the slab
 * @var holesSurf
 */
	double							holesSurf;

/**
 * @brief total perimeter of holes in the slab
 * @var holesPrm
 */
	double							holesPrm;

/**
 * @brief Gross surface of the slab bottom
 * @var grossBotSurf
 */
	double							grossBotSurf;

/**
 * @brief Gross surface of the slab top
 * @var grossTopSurf
 */
	double							grossTopSurf;

/**
 * @brief Gross surface of the slab edges
 * @var grossEdgeSurf
 */
	double							grossEdgeSurf;

/**
 * @brief Gross volume of the slab
 * @var grossVolume
 */
	double							grossVolume;

/**
 * @brief Gross surface of the slab bottom with holes
 * @var grossBotSurfWithHoles
 */
	double							grossBotSurfWithHoles;

/**
 * @brief Gross surface of the slab top with holes
 * @var grossTopSurfWithHoles
 */
	double							grossTopSurfWithHoles;

/**
 * @brief Gross surface of the slab edges with holes
 * @var grossEdgeSurfWithHoles
 */
	double							grossEdgeSurfWithHoles;

/**
 * @brief Gross volume of the slab with holes
 * @var grossVolumeWithHoles
 */
	double							grossVolumeWithHoles;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	double							filler_1[1];

};

/**
 * @brief Describes the different calculated values for meshes.
 * @struct API_MeshQuantity
 * @ingroup Element
 * @remarks See also the mesh parameters for listing in Appendix A of the GDL Reference manual.
 */
struct API_MeshQuantity {

/**
 * @brief bottom surface of the mesh
 * @var bottomSurface
 */
	double							bottomSurface;

/**
 * @brief top surface of the mesh
 * @var topSurface
 */
	double							topSurface;

/**
 * @brief surface of the edge of the mesh
 * @var edgeSurface
 */
	double							edgeSurface;

/**
 * @brief volume of the mesh
 * @var volume
 */
	double							volume;

/**
 * @brief perimeter of the mesh
 * @var perimeter
 */
	double							perimeter;

/**
 * @brief total area of holes in the mesh
 * @var holesSurf
 */
	double							holesSurf;

/**
 * @brief total perimeter of holes in the mesh
 * @var holesPrm
 */
	double							holesPrm;

/**
 * @brief projected area of the mesh
 * @var projectedArea
 */
	double							projectedArea;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	double							filler_1[8];

};

/**
 * @brief Gives the different calculated values for roofs.
 * @struct API_RoofQuantity
 * @ingroup Element
 * @remarks See also the roof parameters for listing in Appendix A of the GDL Reference manual.
 */
struct API_RoofQuantity {

/**
 * @brief bottom surface of the roof
 * @var bottomSurface
 */
	double							bottomSurface;

/**
 * @brief top surface of the roof
 * @var topSurface
 */
	double							topSurface;

/**
 * @brief edge surface of the roof
 * @var edgeSurface
 */
	double							edgeSurface;

/**
 * @brief conditional bottom surface of the roof
 * @var bottomSurface_cond
 */
	double							bottomSurface_cond;

/**
 * @brief conditional top surface of the roof
 * @var topSurface_cond
 */
	double							topSurface_cond;

/**
 * @brief volume of the roof
 * @var volume
 */
	double							volume;

/**
 * @brief conditional volume of the roof
 * @var volume_cond
 */
	double							volume_cond;

/**
 * @brief perimeter of the roof
 * @var perimeter
 */
	double							perimeter;

/**
 * @brief total area of holes in the roof
 * @var holesSurf
 */
	double							holesSurf;

/**
 * @brief total perimeter of holes in the roof
 * @var holesPrm
 */
	double							holesPrm;

/**
 * @brief Gross surface of the roof bottom
 * @var grossBotSurf
 */
	double							grossBotSurf;

/**
 * @brief Gross surface of the roof top
 * @var grossTopSurf
 */
	double							grossTopSurf;

/**
 * @brief Gross surface of the roof edges
 * @var grossEdgeSurf
 */
	double							grossEdgeSurf;

/**
 * @brief The area of the roof contour polygon.
 * @var contourArea
 */
	double							contourArea;

/**
 * @brief Gross volume of the roof
 * @var grossVolume
 */
	double							grossVolume;

/**
 * @brief roof insulation skin thickness
 * @var insuThickness
 */
	double							insuThickness;

/**
 * @brief length of Ridge type edges divided by 2
 * @var ridgesLength
 */
	double							ridgesLength;

/**
 * @brief length of Valley type edges divided by 2
 * @var valleysLength
 */
	double							valleysLength;

/**
 * @brief length of Gable type edges
 * @var gablesLength
 */
	double							gablesLength;

/**
 * @brief length of Hip type edges divided by 2
 * @var hipsLength
 */
	double							hipsLength;

/**
 * @brief length of Eave type edges
 * @var eavesLength
 */
	double							eavesLength;

/**
 * @brief length of Peak type edges
 * @var peaksLength
 */
	double							peaksLength;

/**
 * @brief length of SideWall type edges
 * @var sideWallConLength
 */
	double							sideWallConLength;

/**
 * @brief length of EndWall type edges
 * @var endWallConLength
 */
	double							endWallConLength;

/**
 * @brief length of RTDome type edges divided by 2
 * @var domeConLength
 */
	double							domeConLength;

/**
 * @brief length of RTHollow type edges divided by 2
 * @var hollowConLength
 */
	double							hollowConLength;

/**
 * @brief Sum of the surfaces of the roof openings.
 * @var openingSurf
 */
	double							openingSurf;

/**
 * @brief Number of holes in contour polygon.
 * @var numOfHoles
 */
	Int32							numOfHoles;

/**
 * @brief Number of skylight.
 * @var numOfSkylight
 */
	Int32							numOfSkylight;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2;

};

/**
 * @brief Returns the shell quantity values.
 * @struct API_ShellQuantity
 * @ingroup Element
 */
struct API_ShellQuantity {

/**
 * @brief Net area of the reference surface (without holes).
 * @var referenceSurface
 */
	double							referenceSurface;

/**
 * @brief Net area of the surface opposite to the reference (without holes).
 * @var oppositeSurface
 */
	double							oppositeSurface;

/**
 * @brief Total are of the edges.
 * @var edgeSurface
 */
	double							edgeSurface;

/**
 * @brief Conditional area of the reference surface.
 * @var referenceSurface_cond
 */
	double							referenceSurface_cond;

/**
 * @brief Conditional area of the opposite surface.
 * @var oppositeSurface_cond
 */
	double							oppositeSurface_cond;

/**
 * @brief Volume of the shell.
 * @var volume
 */
	double							volume;

/**
 * @brief Conditional volume of the shell.
 * @var volume_cond
 */
	double							volume_cond;

/**
 * @brief Perimeter of the contour polygon.
 * @var perimeter
 */
	double							perimeter;

/**
 * @brief Total area of the holes.
 * @var holesSurf
 */
	double							holesSurf;

/**
 * @brief Total perimeter of the holes.
 * @var holesPrm
 */
	double							holesPrm;

/**
 * @brief Gross reference surface area (holes included).
 * @var grossReferenceSurf
 */
	double							grossReferenceSurf;

/**
 * @brief Gross area of the opposite surface (holes included).
 * @var grossOppositeSurf
 */
	double							grossOppositeSurf;

/**
 * @brief Gross area of the edge surface.
 * @var grossEdgeSurf
 */
	double							grossEdgeSurf;

/**
 * @brief Gross volume of the shell (holes included).
 * @var grossVolume
 */
	double							grossVolume;

/**
 * @brief Insulation thickness of the shell.
 * @var insuThickness
 */
	double							insuThickness;

/**
 * @brief Total length of the ridges.
 * @var ridgesLength
 */
	double							ridgesLength;

/**
 * @brief Total length of the valleys.
 * @var valleysLength
 */
	double							valleysLength;

/**
 * @brief Total length of the gables.
 * @var gablesLength
 */
	double							gablesLength;

/**
 * @brief Total length of the hips.
 * @var hipsLength
 */
	double							hipsLength;

/**
 * @brief Total length of the eaves.
 * @var eavesLength
 */
	double							eavesLength;

/**
 * @brief Total length of the peaks.
 * @var peaksLength
 */
	double							peaksLength;

/**
 * @brief Total length of the connecting line with side walls.
 * @var sideWallConLength
 */
	double							sideWallConLength;

/**
 * @brief Total length of the connecting line with wall ends.
 * @var endWallConLength
 */
	double							endWallConLength;

/**
 * @brief Total length of the connecting line with domes.
 * @var domeConLength
 */
	double							domeConLength;

/**
 * @brief Total length of the connecting line with hollows.
 * @var hollowConLength
 */
	double							hollowConLength;

/**
 * @brief Total area of the openings.
 * @var openingSurf
 */
	double							openingSurf;

/**
 * @brief Projected floor plan area of the contour polygon.
 * @var floorplanArea
 */
	double							floorplanArea;

/**
 * @brief Number of holes in contour polygon.
 * @var numOfHoles
 */
	Int32							numOfHoles;

/**
 * @brief Number of skylight.
 * @var numOfSkylight
 */
	Int32							numOfSkylight;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2;

};

/**
 * @brief Describes the different calculated values for fills.
 * @struct API_HatchQuantity
 * @ingroup Element
 * @remarks See also the fill parameters for listing in Appendix A of the GDL Reference manual.
 */
struct API_HatchQuantity {

/**
 * @brief area of the fill
 * @var surface
 */
	double							surface;

/**
 * @brief perimeter of the fill
 * @var perimeter
 */
	double							perimeter;

/**
 * @brief perimeter of holes in the fill
 * @var holesPrm
 */
	double							holesPrm;

/**
 * @brief area of holes in the fill
 * @var holesSurf
 */
	double							holesSurf;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	double							filler_1[8];

};

/**
 * @brief Describes the different calculated values for zones.
 * @struct API_ZoneAllQuantity
 * @ingroup Element
 * @remarks See also the parameters of a zone stamp library part.
 * 			This structure replaces the previous @c API_ZoneQuantity and @c API_ZoneExtraQuantity structures.
 */
struct API_ZoneAllQuantity {

/**
 * @brief measured area of the zone in square meters
 * @var area
 */
	double							area;

/**
 * @brief perimeter of the zone
 * @var perimeter
 */
	double							perimeter;

/**
 * @brief perimeter of holes in the zone
 * @var holesPrm
 */
	double							holesPrm;

/**
 * @brief length of perimeter walls
 * @var wallsPrm
 */
	double							wallsPrm;

/**
 * @brief number of the corners of the zone
 * @var allCorners
 */
	Int32							allCorners;

/**
 * @brief number of concave corners of the zone
 * @var concaveCorners
 */
	Int32							concaveCorners;

/**
 * @brief surface area of perimeter walls
 * @var wallsSurf
 */
	double							wallsSurf;

/**
 * @brief combined width of all doors in the zone
 * @var doorsWidth
 */
	double							doorsWidth;

/**
 * @brief surface area of doors in the zone
 * @var doorsSurf
 */
	double							doorsSurf;

/**
 * @brief combined width of all windows in the zone
 * @var windowsWidth
 */
	double							windowsWidth;

/**
 * @brief surface area of windows in the zone
 * @var windowsSurf
 */
	double							windowsSurf;

/**
 * @brief floor level of the zone
 * @var baseLevel
 */
	double							baseLevel;

/**
 * @brief subfloor thickness of the zone
 * @var floorThick
 */
	double							floorThick;

/**
 * @brief height of the zone
 * @var height
 */
	double							height;

/**
 * @brief net area of the zone
 * @var netarea
 */
	double							netarea;

/**
 * @brief net perimeter of the zone
 * @var netperimeter
 */
	double							netperimeter;

/**
 * @brief the volume of the zone
 * @var volume
 */
	double							volume;

/**
 * @brief zone area reducement
 * @var reducementArea
 */
	double							reducementArea;

/**
 * @brief calculated area of the zone
 * @var calcArea
 */
	double							calcArea;

/**
 * @brief total extracted area of the zone
 * @var totalExtrArea
 */
	double							totalExtrArea;

/**
 * @brief reduced area of the zone
 * @var reducedExtrArea
 */
	double							reducedExtrArea;

/**
 * @brief extracted low area of the zone
 * @var lowExtrArea
 */
	double							lowExtrArea;

/**
 * @brief extracted wall area of the zone
 * @var wallExtrArea
 */
	double							wallExtrArea;

/**
 * @brief extracted curtain wall area of the zone
 * @var curtainWallExtrArea
 */
	double							curtainWallExtrArea;

/**
 * @brief extracted column area of the zone
 * @var coluExtrArea
 */
	double							coluExtrArea;

/**
 * @brief extracted fill area of the zone
 * @var fillExtrArea
 */
	double							fillExtrArea;

/**
 * @brief wall inset top surface
 * @var insetTopSurf
 */
	double							insetTopSurf;

/**
 * @brief wall inset back side surface
 * @var insetBackSurf
 */
	double							insetBackSurf;

/**
 * @brief wall inset side surface
 * @var insetSideSurf
 */
	double							insetSideSurf;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	double							filler[8];
};

/**
 * @brief Describes the different calculated values for curtain walls.
 * @struct API_CurtainWallQuantity
 * @ingroup Element
 * @remarks See also the curtain wall parameters for listing in Appendix A of the GDL Reference manual.
 */
struct API_CurtainWallQuantity {

/**
 * @brief Sum of all contained frame's length.
 * @var framesLength
 */
	double							framesLength;

/**
 * @brief Sum of the lengths of contour frames.
 * @var contourFramesLength
 */
	double							contourFramesLength;

/**
 * @brief Sum of the lengths of the frames belong to the main axis (vertical)
 * @var mainaxisFramesLength
 */
	double							mainaxisFramesLength;

/**
 * @brief Sum of the lengths of the frames belong to the secondary axis (horizontal)
 * @var secaxisFramesLength
 */
	double							secaxisFramesLength;

/**
 * @brief Sum of the lengths of the custom frames. (custom means in this case: diagonal frame inside the cell)
 * @var customFramesLength
 */
	double							customFramesLength;

/**
 * @brief Sum of all contained panel's surface. Equal to the sum of panelsSurfaceN, panelsSurfaceS... and equal to the sum of surface values in the @ref API_CWPanelQuantity structure.
 * @var panelsSurface
 */
	double							panelsSurface;

/**
 * @brief Sum of those panel's surface wich normal vector points to north.
 * @var panelsSurfaceN
 */
	double							panelsSurfaceN;

/**
 * @brief Sum of those panel's surface wich normal vector points to south.
 * @var panelsSurfaceS
 */
	double							panelsSurfaceS;

/**
 * @brief Sum of those panel's surface wich normal vector points to east.
 * @var panelsSurfaceE
 */
	double							panelsSurfaceE;

/**
 * @brief Sum of those panel's surface wich normal vector points to west.
 * @var panelsSurfaceW
 */
	double							panelsSurfaceW;

/**
 * @brief Sum of those panel's surface wich normal vector points to north-east.
 * @var panelsSurfaceNE
 */
	double							panelsSurfaceNE;

/**
 * @brief Sum of those panel's surface wich normal vector points to north-west.
 * @var panelsSurfaceNW
 */
	double							panelsSurfaceNW;

/**
 * @brief Sum of those panel's surface wich normal vector points to south-east.
 * @var panelsSurfaceSE
 */
	double							panelsSurfaceSE;

/**
 * @brief Sum of those panel's surface wich normal vector points to south-west.
 * @var panelsSurfaceSW
 */
	double							panelsSurfaceSW;

/**
 * @brief Surface bordered by contour.
 * @var contourSurface
 */
	double							contourSurface;

/**
 * @brief Surface bordered by boundary frames.
 * @var boundarySurface
 */
	double							boundarySurface;

/**
 * @brief Length of the curtain wall.
 * @var length
 */
	double							length;

/**
 * @brief Height of the curtain wall.
 * @var height
 */
	double							height;

/**
 * @brief Slant angle of curtain wall.
 * @var slantAngle
 */
	double							slantAngle;

/**
 * @brief The number of panels belong to the Curtain Wall.
 * @var numOfPanels
 */
	UInt32							numOfPanels;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	UInt32							filler_1;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	double							filler_2[6];

};

/**
 * @brief Describes the different calculated values for curtain wall frames.
 * @struct API_CWFrameQuantity
 * @ingroup Element
 * @remarks See also the curtain wall frame parameters for listing in Appendix A of the GDL Reference manual.
 */
struct API_CWFrameQuantity {

/**
 * @brief Name of the GDL object.
 * @var typeText
 */
	GS::uchar_t						typeText[API_UniLongNameLen];

/**
 * @brief Category of the frame in textual form. See @c API_CWFrameCategory for possible values.
 * @var categoryText
 */
	GS::uchar_t						categoryText[API_UniLongNameLen];

/**
 * @brief Direction of the frame.
 * @var direction
 */
	double							direction;

/**
 * @brief Width of the frame.
 * @var width
 */
	double							width;

/**
 * @brief Depth of the frame
 * @var depth
 */
	double							depth;

/**
 * @brief Length of the frame.
 * @var length
 */
	double							length;

/**
 * @brief Material index of the frame.
 * @var material
 */
	API_AttributeIndex				material;

/**
 * @brief Physical position of the frame. See @c API_CWFrameCategory for possible values.
 * @var position
 */
	short							position;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1[13];

};

/**
 * @brief Describes the different calculated values for curtain wall panels.
 * @struct API_CWPanelQuantity
 * @ingroup Element
 * @remarks See also the curtain wall panel parameters for listing in Appendix A of the GDL Reference manual.
 */
struct API_CWPanelQuantity {

/**
 * @brief Name of the GDL object.
 * @var typeText
 */
	GS::uchar_t						typeText[API_UniLongNameLen];

/**
 * @brief Vertical direction.
 * @var vertDirection
 */
	double							vertDirection;

/**
 * @brief Horizontal direction.
 * @var horDirection
 */
	double							horDirection;

/**
 * @brief Thickness of the panel.
 * @var thickness
 */
	double							thickness;

/**
 * @brief Net surface of the panel. Equal to grossSurface minus the surface covered by neighbouring frames.
 * @var surface
 */
	double							surface;

/**
 * @brief Gross Surface of the panel. Equal to surface plus the surface covered by neighbouring frames.
 * @var grossSurface
 */
	double							grossSurface;

/**
 * @brief Net perimeter of the frame.
 * @var perimeter
 */
	double							perimeter;

/**
 * @brief Gross perimeter of the frame.
 * @var grossPerimeter
 */
	double							grossPerimeter;

/**
 * @brief Material index of the exterior surface of the panel.
 * @var material_outer
 */
	API_AttributeIndex				material_outer;

/**
 * @brief Material index of the edge of the panel.
 * @var material_inner
 */
	API_AttributeIndex				material_inner;

/**
 * @brief Material index of the interior surface of the panel.
 * @var material_cut
 */
	API_AttributeIndex				material_cut;

/**
 * @brief Type of the panel. Possible values: 0 - fixed, 1 - door, 2 - window (value of AC_Panel_Type GDL parameter)
 * @var function
 */
	short							function;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief Width of the panel. (The visible part of the panel. It doesn't includes the part covered by neighbouring frames.)
 * @var width
 */
	double							width;

/**
 * @brief Nominal panel width (it is equal to width if the panel is generic [non GDL based].)
 * @var nominalWidth
 */
	double							nominalWidth;

/**
 * @brief Reserved for later use. (The visible part of the panel. It doesn't includes the part covered by neighbouring frames.)
 * @var height
 */
	double							height;

/**
 * @brief Nominal panel height (it is equal to height if the panel is generic [non GDL based].)
 * @var nominalHeight
 */
	double							nominalHeight;

/**
 * @brief Orientation text in Unicode.
 * @var orientationText
 */
	GS::uchar_t						orientationText[API_UniLongNameLen];

/**
 * @brief Reserved for later use.
 * @var filler
 */
	double							filler[4];

};

/**
 * @brief Describes the different calculated values for curtain wall junctions.
 * @struct API_CWJunctionQuantity
 * @ingroup Element
 * @remarks See also the curtain wall junction parameters for listing in Appendix A of the GDL Reference manual.
 * 			API 21 removed those quantities (width, height, length) that were never calculated.
 */
struct API_CWJunctionQuantity {
/**
 * @brief Name of the GDL object.
 * @var typeText
 */
	GS::uchar_t						typeText[API_UniLongNameLen];

/**
 * @brief Reserved for later use.
 * @var filler
 */
	double							filler[8];

};

/**
 * @brief Describes the different calculated values for curtain wall accessories.
 * @struct API_CWAccessoryQuantity
 * @ingroup Element
 * @remarks See also the curtain wall accessory description in Appendix A of the GDL Reference manual.
 */
struct API_CWAccessoryQuantity {
/**
 * @brief Name of the GDL object.
 * @var typeText
 */
	GS::uchar_t						typeText[API_UniLongNameLen];

/**
 * @brief Width of the accessory.
 * @var width
 */
	double							width;

/**
 * @brief Height of the acccessory.
 * @var height
 */
	double							height;

/**
 * @brief Length of the accessory. (It's equal to the frame length belongs to plus offset value stored in GDL)
 * @var length
 */
	double							length;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	double							filler[4];

};

/**
 * @brief Calculates values for stairs.
 * @struct API_StairQuantity
 * @ingroup Element
 */
typedef struct
{

/**
 * @brief The front surface area of the stair.
 * @var area
 */
	double							area;

/**
 * @brief Volume of the stair.
 * @var volume
 */
	double							volume;

/**
 * @brief Height of the stair.
 * @var height
 */
	double							height;

/**
 * @brief Length of the stair's walking line.
 * @var walklineLength
 */
	double							walklineLength;

/**
 * @brief Inclination angle of the stair.
 * @var gradient
 */
	double							gradient;

/**
 * @brief Number of risers in this stair.
 * @var numOfRisers
 */
	Int32							numOfRisers;

/**
 * @brief Number of treads in this stair.
 * @var numOfTreads
 */
	Int32							numOfTreads;

} API_StairQuantity;

/**
 * @brief Calculated values for a stair tread.
 * @struct API_StairTreadQuantity
 * @ingroup Element
 */
typedef struct
{

/**
 * @brief Top surface area of the given tread.
 * @var area
 */
	double							area;

/**
 * @brief Volume of the given tread.
 * @var volume
 */
	double							volume;

/**
 * @brief Thickness of the given tread.
 * @var thickness
 */
	double							thickness;

/**
 * @brief Elevation to project zero.
 * @var elevation
 */
	double							elevation;

/**
 * @brief Step index of the given tread.
 * @var stepIndex
 */
	Int32							stepIndex;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	Int32							filler;
} API_StairTreadQuantity;

/**
 * @brief Calculated values for the stair riser.
 * @struct API_StairRiserQuantity
 * @ingroup Element
 */
struct API_StairRiserQuantity {

/**
 * @brief Volume of the riser.
 * @var volume
 */
	double							volume;

/**
 * @brief Slant angle of the given riser.
 * @var slantAngle
 */
	double							slantAngle;

/**
 * @brief The width of the given riser.
 * @var width
 */
	double							width;

/**
 * @brief Front surface area of the riser.
 * @var frontArea
 */
	double							frontArea;

/**
 * @brief Step index of the given riser.
 * @var stepIndex
 */
	Int32							stepIndex;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	Int32							filler;
};

/**
 * @brief Calculated values for the stair structure.
 * @struct API_StairStructureQuantity
 * @ingroup Element
 */
struct API_StairStructureQuantity {

/**
 * @brief Volume of the stair structure.
 * @var volume
 */
	double							volume;

/**
 * @brief Height of the stair structure.
 * @var height
 */
	double							height;

/**
 * @brief Thickness of the stair structure.
 * @var thickness
 */
	double							thickness;

/**
 * @brief Length of the stair structure in 3D.
 * @var length3D
 */
	double							length3D;

};

/**
 * @brief Calculated values for a railing.
 * @struct API_RailingQuantity
 * @ingroup Element
 */
struct API_RailingQuantity {

/**
 * @brief The area of the railing.
 * @var area
 */
	double							area;

/**
 * @brief The volume of the given railing.
 * @var volume
 */
	double							volume;

/**
 * @brief The length of the 3D reference line of the railing.
 * @var length3D
 */
	double							length3D;

};

/**
 * @brief Calculated values for a top rail.
 * @struct API_RailingToprailQuantity
 * @ingroup Element
 */
typedef struct
{

/**
 * @brief The volume of the top rail.
 * @var volume
 */
	double							volume;

/**
 * @brief The 3D length of the top rail.
 * @var length3D
 */
	double							length3D;

} API_RailingToprailQuantity;

/**
 * @brief Calculated values for a handrail.
 * @struct API_RailingHandrailQuantity
 * @ingroup Element
 */
typedef struct
{

/**
 * @brief The volume of the handrail.
 * @var volume
 */
	double							volume;

/**
 * @brief The 3D length of the handrail's reference line.
 * @var length3D
 */
	double							length3D;

} API_RailingHandrailQuantity;

/**
 * @brief Calculated values for the rails of the railing.
 * @struct API_RailingRailQuantity
 * @ingroup Element
 */
typedef struct
{

/**
 * @brief Volume of the given rail.
 * @var volume
 */
	double							volume;

/**
 * @brief Length of the 3D reference line of the given rail.
 * @var length3D
 */
	double							length3D;

} API_RailingRailQuantity;

/**
 * @brief Calculated values for the top rail end of the railing.
 * @struct API_RailingToprailEndQuantity
 * @ingroup Element
 */
typedef struct
{

/**
 * @brief Volume of the top rail end of the given railing.
 * @var volume
 */
	double							volume;

/**
 * @brief Length of the 3D reference line of the top rail end of the given railing.
 * @var length3D
 */
	double							length3D;

} API_RailingToprailEndQuantity;

/**
 * @brief Calculated values for the handrail end of the railing.
 * @struct API_RailingHandrailEndQuantity
 * @ingroup Element
 */
typedef struct
{

/**
 * @brief Volume of the handrail end of the given railing.
 * @var volume
 */
	double							volume;

/**
 * @brief Length of the 3D reference line of the handrail end of the given railing.
 * @var length3D
 */
	double							length3D;

} API_RailingHandrailEndQuantity;

/**
 * @brief Calculated values for the rail end of the railing.
 * @struct API_RailingRailEndQuantity
 * @ingroup Element
 */
typedef struct
{

/**
 * @brief Volume of the given rail end.
 * @var volume
 */
	double							volume;

/**
 * @brief Length of the 3D reference line of the given rail end.
 * @var length3D
 */
	double							length3D;

} API_RailingRailEndQuantity;

/**
 * @brief Calculated values for the top rail connection.
 * @struct API_RailingToprailConnectionQuantity
 * @ingroup Element
 */
typedef struct
{

/**
 * @brief Volume of the top rail connection.
 * @var volume
 */
	double							volume;

/**
 * @brief Length of the 3D reference line of the top rail connection.
 * @var length3D
 */
	double							length3D;

} API_RailingToprailConnectionQuantity;

/**
 * @brief Calculated values for the handrail connection.
 * @struct API_RailingHandrailConnectionQuantity
 * @ingroup Element
 */
typedef struct
{

/**
 * @brief Volume of the handrail connection.
 * @var volume
 */
	double							volume;

/**
 * @brief Length of the 3D reference line of the handrail connection.
 * @var length3D
 */
	double							length3D;

} API_RailingHandrailConnectionQuantity;

/**
 * @brief Calculated values for the rail connection.
 * @struct API_RailingRailConnectionQuantity
 * @ingroup Element
 */
typedef struct
{

/**
 * @brief Volume of the rail connection.
 * @var volume
 */
	double							volume;

/**
 * @brief Length of the 3D reference line of the rail connection.
 * @var length3D
 */
	double							length3D;

} API_RailingRailConnectionQuantity;

/**
 * @brief Calculated values for the railing posts.
 * @struct API_RailingPostQuantity
 * @ingroup Element
 */
typedef struct
{

/**
 * @brief Volume of the railing post.
 * @var volume
 */
	double							volume;

/**
 * @brief Length of the 3D reference line of the railing post.
 * @var length3D
 */
	double							length3D;

} API_RailingPostQuantity;

/**
 * @brief Calculated values for the railing inner posts.
 * @struct API_RailingInnerPostQuantity
 * @ingroup Element
 */
typedef struct
{

/**
 * @brief Volume of the railing inner post.
 * @var volume
 */
	double							volume;

/**
 * @brief Length of the 3D reference line of the railing inner post.
 * @var length3D
 */
	double							length3D;

} API_RailingInnerPostQuantity;

/**
 * @brief Calculated values for the balusters.
 * @struct API_RailingBalusterQuantity
 * @ingroup Element
 */
typedef struct
{

/**
 * @brief Volume of the baluster.
 * @var volume
 */
	double							volume;

/**
 * @brief Length of the 3D reference line of the baluster.
 * @var length3D
 */
	double							length3D;

} API_RailingBalusterQuantity;

/**
 * @brief Calculated values for railing panels.
 * @struct API_RailingPanelQuantity
 * @ingroup Element
 */
typedef struct
{

/**
 * @brief Volume of the railing panel.
 * @var volume
 */
	double							volume;

} API_RailingPanelQuantity;

/**
 * @brief Calculated values for the railing segments.
 * @struct API_RailingSegmentQuantity
 * @ingroup Element
 */
typedef struct
{

/**
 * @brief Volume of the railing segment.
 * @var volume
 */
	double							volume;

/**
 * @brief Length of the 3D reference line of the railing segment.
 * @var length3D
 */
	double							length3D;

} API_RailingSegmentQuantity;

/**
 * @brief Describes the different calculated values.
 * @union API_ElementQuantity
 * @ingroup Element
 */
union API_ElementQuantity {

/**
 * @brief Describes the different calculated values for wall. @ref API_WallQuantity
 * @var wall
 */
	API_WallQuantity						wall;

/**
 * @brief Describes the different calculated values for column. @ref API_ColumnQuantity
 * @var column
 */
	API_ColumnQuantity						column;

/**
 * @brief Describes the different calculated values for beam. @ref API_BeamQuantity
 * @var beam
 */
	API_BeamQuantity						beam;

/**
 * @brief Describes the different calculated values for door. @ref API_DoorQuantity
 * @var door
 */
	API_DoorQuantity						door;

/**
 * @brief Describes the different calculated values for window. @ref API_WindowQuantity
 * @var window
 */
	API_WindowQuantity						window;

/**
 * @brief Describes the different calculated values for skylight. @ref API_SkylightQuantity
 * @var skylight
 */
	API_SkylightQuantity					skylight;

/**
 * @brief Describes the different calculated values for symb. @ref API_ObjectQuantity
 * @var symb
 */
	API_ObjectQuantity						symb;

/**
 * @brief Describes the different calculated values for light. @ref API_LightQuantity
 * @var light
 */
	API_LightQuantity						light;

/**
 * @brief Describes the different calculated values for slab. @ref API_SlabQuantity
 * @var slab
 */
	API_SlabQuantity						slab;

/**
 * @brief Describes the different calculated values for mesh. @ref API_MeshQuantity
 * @var mesh
 */
	API_MeshQuantity						mesh;

/**
 * @brief Describes the different calculated values for roof. @ref API_RoofQuantity
 * @var roof
 */
	API_RoofQuantity						roof;

/**
 * @brief Describes the different calculated values for shell. @ref API_ShellQuantity
 * @var shell
 */
	API_ShellQuantity						shell;

/**
 * @brief Describes the different calculated values for morph. @ref API_MorphQuantity
 * @var morph
 */
	API_MorphQuantity						morph;

/**
 * @brief Describes the different calculated values for hatch. @ref API_HatchQuantity
 * @var hatch
 */
	API_HatchQuantity						hatch;

/**
 * @brief Describes the different calculated values for zone. @ref API_ZoneAllQuantity
 * @var zone
 */
	API_ZoneAllQuantity						zone;

/**
 * @brief Describes the different calculated values for curtain wall. @ref API_CurtainWallQuantity
 * @var cw
 */
	API_CurtainWallQuantity					cw;

/**
 * @brief Describes the different calculated values for frame of curtain wall. @ref API_CWFrameQuantity
 * @var cwFrame
 */
	API_CWFrameQuantity						cwFrame;

/**
 * @brief Describes the different calculated values for panel of curtain wall. @ref API_CWPanelQuantity
 * @var cwPanel
 */
	API_CWPanelQuantity						cwPanel;

/**
 * @brief Describes the different calculated values for junction of curtain wall. @ref API_CWJunctionQuantity
 * @var cwJunction
 */
	API_CWJunctionQuantity					cwJunction;

/**
 * @brief Describes the different calculated values for accessory of curtain wall. @ref API_CWAccessoryQuantity
 * @var cwAccessory
 */
	API_CWAccessoryQuantity					cwAccessory;

/**
 * @brief Describes the different calculated values for stair s.
 * @var stair
 */
	API_StairQuantity						stair;

/**
 * @brief Describes the different calculated values for stair risers.
 * @var stairRiser
 */
	API_StairRiserQuantity					stairRiser;

/**
 * @brief Describes the different calculated values for stair treads.
 * @var stairTread
 */
	API_StairTreadQuantity					stairTread;

/**
 * @brief Describes the different calculated values for stair structures.
 * @var stairStructure
 */
	API_StairStructureQuantity				stairStructure;

/**
 * @brief Describes the different calculated values for railings.
 * @var railing
 */
	API_RailingQuantity						railing;

/**
 * @brief Describes the different calculated values for railing toprails.
 * @var railingToprail
 */
	API_RailingToprailQuantity				railingToprail;

/**
 * @brief Describes the different calculated values for railing handrails.
 * @var railingHandrail
 */
	API_RailingHandrailQuantity				railingHandrail;

/**
 * @brief Describes the different calculated values for railing rails.
 * @var railingRail
 */
	API_RailingRailQuantity					railingRail;

/**
 * @brief Describes the different calculated values for railing toprail ends.
 * @var railingToprailEnd
 */
	API_RailingToprailEndQuantity			railingToprailEnd;

/**
 * @brief Describes the different calculated values for railing handrail ends.
 * @var railingHandrailEnd
 */
	API_RailingHandrailEndQuantity			railingHandrailEnd;

/**
 * @brief Describes the different calculated values for railing rail ends.
 * @var railingRailEnd
 */
	API_RailingRailEndQuantity				railingRailEnd;

/**
 * @brief Describes the different calculated values for railing toprail connections.
 * @var railingToprailConnection
 */
	API_RailingToprailConnectionQuantity	railingToprailConnection;

/**
 * @brief Describes the different calculated values for railing handrail connections.
 * @var railingHandrailConnection
 */
	API_RailingHandrailConnectionQuantity	railingHandrailConnection;

/**
 * @brief Describes the different calculated values for railing rail connections.
 * @var railingRailConnection
 */
	API_RailingRailConnectionQuantity		railingRailConnection;

/**
 * @brief Describes the different calculated values for railing posts.
 * @var railingPost
 */
	API_RailingPostQuantity					railingPost;

/**
 * @brief Describes the different calculated values for railing inner posts.
 * @var railingInnerPost
 */
	API_RailingInnerPostQuantity			railingInnerPost;

/**
 * @brief Describes the different calculated values for railing balusters.
 * @var railingBaluster
 */
	API_RailingBalusterQuantity				railingBaluster;

/**
 * @brief Describes the different calculated values for railing panels.
 * @var railingPanel
 */
	API_RailingPanelQuantity				railingPanel;

/**
 * @brief Describes the different calculated values for railing segments.
 * @var railingSegment
 */
	API_RailingSegmentQuantity				railingSegment;

/**
 * @brief Describes the different calculated values for column segments.
 * @var columnSegment
 */
	API_ColumnSegmentQuantity				columnSegment;

/**
 * @brief Describes the different calculated values for beam segments.
 * @var beamSegment
 */
	API_BeamSegmentQuantity					beamSegment;

};

/**
 * @brief Supplies extra information for some element quantity calculations.
 * @struct API_QuantityPar
 * @ingroup Element
 * @remarks At wall calculations: Openings which are smaller than the supplied minimum area minOpeningSize are not subtracted from the surface of the wall.
 */
struct API_QuantityPar {

/**
 * @brief minimum opening size to reduce wall [in square meters] (ignored at non-wall calculations)
 * @var minOpeningSize
 */
	double							minOpeningSize;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[4];

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	double							filler_3[6];

};

/**
 * @brief Identifies the composite skin and sub-element.
 * @struct API_CompositeId
 * @ingroup Element
 */
struct API_CompositeId {

/**
 * @brief GUID of the sub-element, or APINULLGuid if no sub-element is attached to the component.
 * @var subElementGuid
 */
	API_Guid						subElementGuid;

};

/**
 * @brief Describes the different calculated values for skins of composite or complex elements.
 * @struct API_CompositeQuantity
 * @ingroup Element
 */
struct API_CompositeQuantity {

/**
 * @brief Identifies the composite skin and sub-element.
 * @var compositeId
 */
	API_CompositeId					compositeId;

/**
 * @brief Volumes of consecutive skins of composite or complex elements (in the order defined by the fill indexes).
 * @var volumes
 */
	double							volumes;

/**
 * @brief The projected area of consecutive skins of composite or complex elements (in the order defined by the fill indexes). Its value is 0 if the Use Legacy intersection and Surface methods for model elements is turned on in the Project Preferences, because the special 3D model used to calculate this information cannot be created in legacz mode.
 * @var projectedArea
 */
	double							projectedArea;

/**
 * @brief Building materials of consecutive skins of composite or complex elements.
 * @var buildMatIndices
 */
	API_AttributeIndex				buildMatIndices;

/**
 * @brief The flags of consecutive skins of composite or complex elements (in the order defined by the fill indexes). See the flagBits in @ref API_CWallComponent.
 * @var flags
 */
	short							flags;

};

/**
 * @brief Describes the different calculated values for parts of an element.
 * @struct API_ElemPartQuantity
 * @ingroup Element
 */
struct API_ElemPartQuantity {

/**
 * @brief Identifier of the part of the elem.
 * @var partId
 */
	API_ElemPartId					partId;

/**
 * @brief Quantity values for the specified part of the elem.
 * @var quantity
 */
	API_ElementQuantity				quantity;

};

/**
 * @brief Describes the different calculated values for skins of composite or complex elements.
 * @struct API_ElemPartCompositeQuantity
 * @ingroup Element
 * @remarks You should never memset this structure because of the contained GS::Array member. Both of the contained types have a default constructor.
 */
struct API_ElemPartCompositeQuantity {

/**
 * @brief Identifier of the part of the elem.
 * @var partId
 */
	API_ElemPartId						partId;

/**
 * @brief Calculated values for skins of composite or complex elements
 * @var composites
 */
	GS::Array<API_CompositeQuantity>	composites;

};

/**
 * @brief Describes the different calculated values for surfaces of elements.
 * @struct API_ElemPartSurfaceQuantity
 * @ingroup Element
 */
struct API_ElemPartSurfaceQuantity {

/**
 * @brief GUID of the element.
 * @var elemGUID
 */
	API_Guid						elemGUID;

/**
 * @brief Index of the material, that the surface belongs to.
 * @var materialIndex
 */
	API_AttributeIndex				materialIndex;

/**
 * @brief Building material index of the element, that the surface belongs to.
 * @var buildMatIdx
 */
	API_AttributeIndex				buildMatIdx;

/**
 * @brief Area of exposed surface
 * @var exposedSurface
 */
	double							exposedSurface;

};

/**
 * @brief Describes the different calculated values for skins of composite or complex elements.
 * @class API_Quantities
 * @ingroup Element
 */
class API_Quantities {
public:
/**
 * @brief Describes the different calculated values.
 * @var elements
 */
	API_ElementQuantity							*elements;

/**
 * @brief Describes the different calculated values for skins of composite or complex elements.
 * @var composites
 */
	GS::Array <API_CompositeQuantity>			*composites;

/**
 * @brief Describes the different calculated values for parts of an element.
 * @var elemPartQuantities
 */
	GS::Array <API_ElemPartQuantity>			*elemPartQuantities;

/**
 * @brief Describes the different calculated values for skins of composite or complex elements.
 * @var elemPartComposites
 */
	GS::Array <API_ElemPartCompositeQuantity>	*elemPartComposites;

	API_Quantities () : elements (nullptr), composites (nullptr), elemPartQuantities (nullptr), elemPartComposites (nullptr) {}

};

/**
 * @brief Describes the filter for the different calculated values for elements.
 * @struct API_ElementQuantityMask
 * @ingroup Element
 */
struct API_ElementQuantityMask {

/**
 * @brief Describes the mask of different calculated values for wall. @ref API_WallQuantity
 * @var wall
 */
	API_WallQuantity						wall;

/**
 * @brief Describes the mask of different calculated values for column. @ref API_ColumnQuantity
 * @var column
 */
	API_ColumnQuantity						column;

/**
 * @brief Describes the mask of different calculated values for beam. @ref API_BeamQuantity
 * @var beam
 */
	API_BeamQuantity						beam;

/**
 * @brief Describes the mask of different calculated values for door. @ref API_DoorQuantity
 * @var door
 */
	API_DoorQuantity						door;

/**
 * @brief Describes the mask of different calculated values for window. @ref API_WindowQuantity
 * @var window
 */
	API_WindowQuantity						window;

/**
 * @brief Describes the mask of different calculated values for skylight. @ref API_SkylightQuantity
 * @var skylight
 */
	API_SkylightQuantity					skylight;

/**
 * @brief Describes the mask of different calculated values for symb. @ref API_ObjectQuantity
 * @var symb
 */
	API_ObjectQuantity						symb;

/**
 * @brief Describes the mask of different calculated values for light. @ref API_LightQuantity
 * @var light
 */
	API_LightQuantity						light;

/**
 * @brief Describes the mask of different calculated values for slab. @ref API_SlabQuantity
 * @var slab
 */
	API_SlabQuantity						slab;

/**
 * @brief Describes the mask of different calculated values for mesh. @ref API_MeshQuantity
 * @var mesh
 */
	API_MeshQuantity						mesh;

/**
 * @brief Describes the mask of different calculated values for roof. @ref API_RoofQuantity
 * @var roof
 */
	API_RoofQuantity						roof;

/**
 * @brief Describes the mask of different calculated values for shell. @ref API_ShellQuantity
 * @var shell
 */
	API_ShellQuantity						shell;

/**
 * @brief Describes the mask of different calculated values for morph. @ref API_MorphQuantity
 * @var morph
 */
	API_MorphQuantity						morph;

/**
 * @brief Describes the mask of different calculated values for hatch. @ref API_HatchQuantity
 * @var hatch
 */
	API_HatchQuantity						hatch;

/**
 * @brief Describes the mask of different calculated values for zone. @ref API_ZoneAllQuantity
 * @var zone
 */
	API_ZoneAllQuantity						zone;

/**
 * @brief Describes the mask of different calculated values for curtain wall. @ref API_CurtainWallQuantity
 * @var cw
 */
	API_CurtainWallQuantity					cw;

/**
 * @brief Describes the mask of different calculated values for frame of curtain wall. @ref API_CWFrameQuantity
 * @var cwFrame
 */
	API_CWFrameQuantity						cwFrame;

/**
 * @brief Describes the mask of different calculated values for panel of curtain wall. @ref API_CWPanelQuantity
 * @var cwPanel
 */
	API_CWPanelQuantity						cwPanel;

/**
 * @brief Describes the mask of different calculated values for junction of curtain wall. @ref API_CWJunctionQuantity
 * @var cwJunction
 */
	API_CWJunctionQuantity					cwJunction;

/**
 * @brief Describes the mask of different calculated values for accessory of curtain wall. @ref API_CWAccessoryQuantity
 * @var cwAccessory
 */
	API_CWAccessoryQuantity					cwAccessory;

/**
 * @brief Describes the different calculated values for stair s.
 * @var stair
 */
	API_StairQuantity						stair;

/**
 * @brief Describes the different calculated values for stair risers.
 * @var stairRiser
 */
	API_StairRiserQuantity					stairRiser;

/**
 * @brief Describes the different calculated values for stair treads.
 * @var stairTread
 */
	API_StairTreadQuantity					stairTread;

/**
 * @brief Describes the different calculated values for stair structures.
 * @var stairStructure
 */
	API_StairStructureQuantity				stairStructure;

/**
 * @brief Describes the different calculated values for railings.
 * @var railing
 */
	API_RailingQuantity						railing;

/**
 * @brief Describes the different calculated values for railing toprails.
 * @var railingToprail
 */
	API_RailingToprailQuantity				railingToprail;

/**
 * @brief Describes the different calculated values for railing handrails.
 * @var railingHandrail
 */
	API_RailingHandrailQuantity				railingHandrail;

/**
 * @brief Describes the different calculated values for railing rails.
 * @var railingRail
 */
	API_RailingRailQuantity					railingRail;

/**
 * @brief Describes the different calculated values for railing toprail ends.
 * @var railingToprailEnd
 */
	API_RailingToprailEndQuantity			railingToprailEnd;

/**
 * @brief Describes the different calculated values for railing handrail ends.
 * @var railingHandrailEnd
 */
	API_RailingHandrailEndQuantity			railingHandrailEnd;

/**
 * @brief Describes the different calculated values for railing rail ends.
 * @var railingRailEnd
 */
	API_RailingRailEndQuantity				railingRailEnd;

/**
 * @brief Describes the different calculated values for railing toprail connections.
 * @var railingToprailConnection
 */
	API_RailingToprailConnectionQuantity	railingToprailConnection;

/**
 * @brief Describes the different calculated values for railing handrail connections.
 * @var railingHandrailConnection
 */
	API_RailingHandrailConnectionQuantity	railingHandrailConnection;

/**
 * @brief Describes the different calculated values for railing rail connections.
 * @var railingRailConnection
 */
	API_RailingRailConnectionQuantity		railingRailConnection;

/**
 * @brief Describes the different calculated values for railing posts.
 * @var railingPost
 */
	API_RailingPostQuantity					railingPost;

/**
 * @brief Describes the different calculated values for railing inner posts.
 * @var railingInnerPost
 */
	API_RailingInnerPostQuantity			railingInnerPost;

/**
 * @brief Describes the different calculated values for railing balusters.
 * @var railingBaluster
 */
	API_RailingBalusterQuantity				railingBaluster;

/**
 * @brief Describes the different calculated values for railing panels.
 * @var railingPanel
 */
	API_RailingPanelQuantity				railingPanel;

/**
 * @brief Describes the different calculated values for railing segments.
 * @var railingSegment
 */
	API_RailingSegmentQuantity				railingSegment;

/**
 * @brief Describes the different calculated values for column segments. @ref API_ColumnSegmentQuantity
 * @var columnSegment
 */
	API_ColumnSegmentQuantity				columnSegment;

/**
 * @brief Describes the different calculated values for beam segments. @ref API_BeamSegmentQuantity
 * @var beamSegment
 */
	API_BeamSegmentQuantity					beamSegment;
};

/**
 * @brief Describes the filter for the different calculated values for skins.
 * @typedef API_CompositeQuantityMask
 * @ingroup Element
 */
typedef API_CompositeQuantity API_CompositeQuantityMask;

/**
 * @brief Describes the filter for the different calculated values for skins and elements.
 * @class API_QuantitiesMask
 * @ingroup Element
 */
class API_QuantitiesMask {
public:
/**
 * @brief Describes the filter for the different calculated values for elements.
 * @var elements
 */
	API_ElementQuantityMask			elements;

/**
 * @brief Describes the filter for the different calculated values for skins.
 * @var composites
 */
	API_CompositeQuantityMask		composites;

	API_QuantitiesMask ()
	{
		memset (&elements, 0, sizeof (elements));
		memset (&composites, 0, sizeof (composites));
	}

};

/**
 * @brief Clears the mask for querying quantities.
 * @ingroup Element
 * @param mask the quantity mask to clear
 */
inline void ACAPI_ELEMENT_QUANTITIES_MASK_CLEAR (API_QuantitiesMask &mask)
{
	memset (&mask, 0, sizeof (mask));
}
/**
 * @brief Set the mask to full (return all quantities) for querying quantities.
 * @ingroup Element
 * @param mask the quantity mask to fill fully
 */
inline void ACAPI_ELEMENT_QUANTITIES_MASK_SETFULL (API_QuantitiesMask &mask)
{
	memset (&mask, 0xFF, sizeof (mask));
}

/**
 * @brief Clears the element part of the mask for querying element quantities.
 * @ingroup Element
 * @param mask the quantity mask to clear
 */
inline void ACAPI_ELEMENT_QUANTITY_MASK_CLEAR (API_QuantitiesMask &mask)
{
	memset (&mask.elements, 0, sizeof (mask.elements));
}
/**
 * @brief Set the element part of the mask to full (return all quantities) for querying element quantities.
 * @ingroup Element
 * @param mask the quantity mask to fill the element part fully
 */
inline void ACAPI_ELEMENT_QUANTITY_MASK_SETFULL (API_QuantitiesMask &mask)
{
	memset (&mask.elements, 0xFF, sizeof (mask.elements));
}

#define	ACAPI_ELEMENT_QUANTITY_MASK_SET(rec,typ,varnam)		*((char *) &((rec).elements.typ.varnam)) = -1
#define	ACAPI_ELEMENT_QUANTITY_MASK_CHECK(rec,typ,varnam)	(*((char *) &((rec).elements.typ.varnam)) != 0)

/**
 * @brief Clears the composites part of the mask for querying composite quantities.
 * @ingroup Element
 * @param mask the quantity mask to clear
 */
inline void ACAPI_ELEMENT_COMPOSITES_QUANTITY_MASK_CLEAR (API_QuantitiesMask &mask)
{
	memset (&mask.composites, 0, sizeof (mask.composites));
}

/**
 * @brief Set the composites part of the mask to full (return all quantities) for querying composite quantities.
 * @ingroup Element
 * @param mask the quantity mask to fill the composite part fully
 */
inline void ACAPI_ELEMENT_COMPOSITES_QUANTITY_MASK_SETFULL (API_QuantitiesMask &mask)
{
	memset (&mask.composites, 0xFF, sizeof (mask.composites));
}
#define	ACAPI_ELEMENT_COMPOSITES_QUANTITY_MASK_SET(rec,varnam)		*((char *) &((rec).composites.varnam)) = -1
#define	ACAPI_ELEMENT_COMPOSITES_QUANTITY_MASK_CHECK(rec,varnam)	(*((char *) &((rec).composites.varnam)) != 0)


// =============================================================================
// Properties
//
// =============================================================================

#define APIDBRef_Normal				0							// exists in database
#define APIDBRef_Deleted			1							// referenced, but deleted from the database
#define APIDBRef_Local				2							// defined in the Library Part

/**
 * @brief The property object reference record.
 * @struct API_PropertyObjectRefType
 * @ingroup Element
 * @remarks This structure is used when you want to get the property objectlist of an element. See the @ref ACAPI_Element_GetPropertyObjects function.
 */
struct API_PropertyObjectRefType {

/**
 * @brief Index of the library part, this is a property object
 * @var libIndex
 */
	Int32							libIndex;

/**
 * @brief This member is true, if the property object is invidually assignment.
 * @var assign
 */
	bool							assign;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	char							filler_1;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	short							filler_2;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3[2];

};

/**
 * @brief The component reference record.
 * @struct API_Obsolete_ComponentRefType
 * @ingroup Element
 * @remarks This structure is obsolete. Use the new component API instead.
 * 			This structure is used when you want to get the components of an element. These components are in the property objects of the element. See the @ref ACAPI_Element_GetComponents_Obsolete function.
 * 			This stucture is used when you get or search a component in the listing database. See the @ref ACAPI_OldListing_Get, @ref ACAPI_OldListing_GetLocal and @ref ACAPI_OldListing_Search functions.
 */
struct API_Obsolete_ComponentRefType {

/**
 * @brief Index of the library part where the component was declared
 * @var libIndex
 */
	Int32							libIndex;

/**
 * @brief Index of the listing database set, if status is equal to @c APIDBRef_Normal.
 * @var setIndex
 */
	Int32							setIndex;

/**
 * @brief This member depends on the status field. If status equals APIDBRef _Normal, then index is index of the component in the set, if status equals @c APIDBRef_Local, then index is index of the component in the library part.
 * @var index
 */
	Int32							index;

/**
 * @brief This member is status of component(APIDBRef__Normal, @c APIDBRef__Local, @c APIDBRef_Deleted).
 * @var status
 */
	Int32							status;

/**
 * @brief Calculated quantity of component.
 * @var quantity
 */
	double							quantity;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3[8];

};

/**
 * @brief The descriptor reference record.
 * @struct API_DescriptorRefType
 * @ingroup Element
 * @remarks This structure is used when you want to get the descriptors of an element. These descriptors are in the property objects of the element. See the @ref ACAPI_Element_GetDescriptors function.
 */
struct API_DescriptorRefType {

/**
 * @brief Index of the library part, place of the descriptor declaring
 * @var libIndex
 */
	Int32							libIndex;

/**
 * @brief Index of the listing database set, if status equals @c APIDBRef_Normal.
 * @var setIndex
 */
	Int32							setIndex;

/**
 * @brief This member depends on the status field. If status equals APIDBRef _Normal, then index is index of the descriptor in the set, if status equals APIDBRef _Local, then index is index of the descriptor in the library part.
 * @var index
 */
	Int32							index;

/**
 * @brief This member is status of descriptor(APIDBRef__Normal, @c APIDBRef__Local, @c APIDBRef_Deleted).
 * @var status
 */
	Int32							status;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3[8];

};


// =============================================================================
// Markup Management
//
// =============================================================================

/**
 * @brief Represents a Mark-Up entry.
 * @struct API_MarkUpType
 * @ingroup Markup
 * @remarks Use @ref ACAPI_Markup_Create function to create and @ref ACAPI_Markup_Delete function to delete Mark-Up entry. Mark-Ups can be listed with @ref ACAPI_Markup_GetList function. Elements can be attached to the Mark-Up using @ref ACAPI_Markup_AttachElements and comment can be added with @ref ACAPI_Markup_AddComment function.
 */
struct API_MarkUpType {

/**
 * @brief Identifier of the Mark-Up
 * @var guid
 */
	API_Guid						guid;

/**
 * @brief Name
 * @var name
 */
	GS::UniString					name;

/**
 * @brief The identifier of the parent Mark-Up
 * @var parentGuid
 */
	API_Guid						parentGuid;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	Int32							filler_0;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	short							filler_2;

/**
 * @brief Creation time
 * @var creaTime
 */
	GSTime							creaTime;

/**
 * @brief Modification time
 * @var modiTime
 */
	GSTime							modiTime;

/**
 * @brief Tag text
 * @var tagText
 */
	GS::UniString					tagText;

/**
 * @brief The identifier of the attached tag text element
 * @var tagTextElemGuid
 */
	API_Guid						tagTextElemGuid;

/**
 * @brief The visibility of the attached tag text element
 * @var isTagTextElemVisible
 */
	bool							isTagTextElemVisible;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	bool							filler_3[7];

/**
 * @brief Constructor.
 * @param name Name of the Mark-Up.
 * @param parentGuid The identifier of the parent Mark-Up.
 */
	API_MarkUpType (GS::UniString	name = GS::UniString (),
					API_Guid		parentGuid = APINULLGuid) :
		guid (APINULLGuid),
		name (name),
		parentGuid (parentGuid),
		filler_0 (0),
		filler_1 (0),
		filler_2 (0),
		creaTime (0),
		modiTime (0),
		tagText (),
		tagTextElemGuid (APINULLGuid),
		isTagTextElemVisible (true),
		filler_3 ()
	{
	}

};

/**
 * @brief Describes the various options for Mark-Up comment status.
 * @enum API_MarkUpCommentStatusID
 * @ingroup Markup
 * @remarks API_MarkUpCommentType structure uses this enum.
 */
typedef enum {
	APIComment_Error				= 0,
	APIComment_Warning,
	APIComment_Info,
	APIComment_Unknown

} API_MarkUpCommentStatusID;

/**
 * @brief Represents a comment attached to a Mark-Up entry.
 * @struct API_MarkUpCommentType
 * @ingroup Markup
 * @remarks Comment can be added with @ref ACAPI_Markup_AddComment function to an existing Mark-Up entry and the list of the comments can be retrieved using @ref ACAPI_Markup_GetComments.
 */
struct API_MarkUpCommentType {

/**
 * @brief Identifier of the comment
 * @var guid
 */
	API_Guid						guid;

/**
 * @brief The author of the comment
 * @var author
 */
	GS::UniString					author;

/**
 * @brief Text of the comment
 * @var text
 */
	GS::UniString					text;

/**
 * @brief Status. See @ref API_MarkUpCommentStatusID for further info.
 * @var status
 */
	API_MarkUpCommentStatusID		status;

/**
 * @brief Creation time
 * @var creaTime
 */
	GSTime							creaTime;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1[2];

/**
 * @brief Constructor which fills author, text and status of the comment.
 * @param author The author of the comment.
 * @param text Text of the comment.
 * @param status Status of the comment.
 */
	API_MarkUpCommentType (GS::UniString				author = GS::UniString (),
						   GS::UniString				text = GS::UniString (),
						   API_MarkUpCommentStatusID	status = APIComment_Unknown) :
		guid (APINULLGuid),
		author (author),
		text (text),
		status (status),
		creaTime (0),
		filler_1 ()
	{
	}

};

/**
 * @brief Describes the type of a component attached to a Mark-Up entry.
 * @enum API_MarkUpComponentTypeID
 * @ingroup Markup
 * @since Archicad 25
 * @remarks ACAPI_Markup_AttachElements and @ref ACAPI_Markup_GetAttachedElements functions use this enum.
 */
typedef enum {
	APIMarkUpComponent_Creation		= 0,
	APIMarkUpComponent_Highlight,
	APIMarkUpComponent_Deletion,
	APIMarkUpComponent_Modification

} API_MarkUpComponentTypeID;


// =============================================================================
// Edit operations
//
// =============================================================================

/**
 * @brief Possible element transformations.
 * @enum API_EditCmdID
 * @ingroup Element
 * @remarks Refer to the @ref API_EditPars structure for parametrization; or to the @ref ACAPI_Element_Edit function to transform database elements.
 */
typedef enum {
	APIEdit_Drag					= 'DRAG',
	APIEdit_Rotate					= 'ROTZ',
	APIEdit_Mirror					= 'MIRR',
	APIEdit_Elevate					= 'ELEV',
	APIEdit_Stretch					= 'STRE',
	APIEdit_VertStretch				= 'VSTR',
	APIEdit_Resize					= 'RSIZ',
	APIEdit_General					= 'GENE',
	APIEdit_PHeightStretch			= 'PHST',					// preserved height stretch (for slanted beam / column)
	APIEdit_PDirStretch				= 'PDST'					// preserved direction stretch (for slanted beam / column)

} API_EditCmdID;

/**
 * @brief Structure for retrieving the transformation data of the actual editing operation.
 * @struct API_ActTranPars
 * @ingroup Notification
 * @remarks For the utilization of this structure see the @ref ACAPI_Notification_GetTranParams function.
 */
struct API_ActTranPars {												// transformation parameters of the actual operation

/**
 * @brief Type of the editing operation
 * @var typeID
 */
	API_EditCmdID					typeID;

/**
 * @brief For vertical stretch editing, identifies the base the vertical displacement to be added to
 * @var topNodeStretched
 */
	bool							topNodeStretched;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[3];


/**
 * @brief Displacement vector on the x-y plane
 * @var theDisp
 */
	API_Vector						theDisp;

/**
 * @brief Unit vector for mirroring (the base point of the mirror axis is stored in theOrigo)
 * @var theAxeVect
 */
	API_Vector						theAxeVect;

/**
 * @brief Base coordinate for Rotate, Mirror, Stretch and Resize operations
 * @var theOrigo
 */
	API_Coord						theOrigo;

/**
 * @brief Cosine of the rotation angle
 * @var theCosA
 */
	double							theCosA;

/**
 * @brief Sine of the rotation angle
 * @var theSinA
 */
	double							theSinA;

/**
 * @brief Vertical displacement for Elevate and VertStretch operations
 * @var theDispZ
 */
	double							theDispZ;

/**
 * @brief Ratio for the Resize operation
 * @var theRatio
 */
	double							theRatio;


/**
 * @brief Cutplane line direction unit vector
 * @var sectionLineDir
 */
	API_Vector						sectionLineDir;


/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	double							filler_2[6];

};

/**
 * @brief Transformation parameters for elements.
 * @struct API_EditPars
 * @ingroup Element
 * @remarks Generally you have to think about the coordinates in the same way you should click in Archicad to perform the same operation. For example in case of rotation you have to set the origC field to the origo, the begC and endC fields to the start and end points of the rotation angle.
 * 			The origo does not have vertical information, it just specifies the center of rotation. Other coordinates have a z component; its difference will specify the elevation factor; additive to the original operation.
 * 			This structure is used by the @ref ACAPI_Element_Edit function.
 */
struct API_EditPars {												// global parameters for transforming elements

/**
 * @brief the operation code
 * @var typeID
 */
	API_EditCmdID					typeID;

/**
 * @brief delete the target element after the operation (drag or drag a copy)
 * @var withDelete
 */
	bool							withDelete;

/**
 * @brief the upper node must be edited in case of vertical stretching
 * @var topNodeStretched
 */
	bool							topNodeStretched;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[2];


/**
 * @brief the origo; used for mirror and rotate
 * @var origC
 */
	API_Coord						origC;

/**
 * @brief the start point of the edit vector; this is the reference point
 * @var begC
 */
	API_Coord3D 					begC;

/**
 * @brief the end point of the edit vector; generally this is the second click in Archicad
 * @var endC
 */
	API_Coord3D						endC;

/**
 * @brief additional vector end point; used for mirror
 * @var endC2
 */
	API_Coord3D						endC2;


/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	double							filler_2[8];

};


// =============================================================================
// Tool operations
//
// =============================================================================

/**
 * @brief It is used at the @ref ACAPI_Grouping_Tool function.
 * @enum API_ToolCmdID
 * @ingroup Grouping
 */
typedef enum {
	APITool_Group					= 'GRUP',
	APITool_Ungroup					= 'UGRP',
	APITool_SuspendGroups			= 'SUSP',
	APITool_Lock					= 'LOCK',
	APITool_Unlock					= 'ULCK',

	APITool_BringToFront			= 'OFR0',
	APITool_BringForward			= 'OFR1',
	APITool_SendBackward			= 'OBA1',
	APITool_SendToBack				= 'OBA0',
	APITool_ResetOrder				= 'ORST'

} API_ToolCmdID;


// =============================================================================
// Solid operations
//
// =============================================================================

/**
 * @brief The type of the solid operation link between two construction elements.
 * @enum API_SolidOperationID
 * @ingroup Element
 * @remarks These enumerators are used with the @ref ACAPI_Element_SolidLink_Create, @ref ACAPI_Element_SolidLink_GetOperation and @ref ACAPI_Element_SolidOperation_Create functions.
 */
typedef enum {
	APISolid_Substract				= 'SSUB',					// subtraction
	APISolid_SubstUp				= 'SSUU',					// subtraction with upwards extrusion
	APISolid_SubstDown				= 'SSUD',					// subtraction with downwards extrusion
	APISolid_Intersect				= 'SINT',					// intersection
	APISolid_Add					= 'SADD'					// addition

} API_SolidOperationID;

// linkFlags values
#define APISolidFlag_OperatorAttrib	0x00000001					// inherit attributes of operator
#define APISolidFlag_SkipPolygonHoles 0x00000004				// skip holes of operator (roof/slab)


// =============================================================================
// Trim types
//
// =============================================================================

/**
 * @brief The type of the trim connection link between two construction elements.
 * @enum API_TrimTypeID
 * @ingroup Element
 * @remarks These enumerators are used with the @ref ACAPI_Element_Trim_ElementsWith and @ref ACAPI_Element_Trim_GetTrimType functions.
 */
typedef enum {
	APITrim_No						= 'TRNO',					// No trim
	APITrim_KeepInside				= 'TRIN',					// Keep Inside
	APITrim_KeepOutside				= 'TROU',					// Keep Outside
	APITrim_KeepAll					= 'TRAL'					// Keep All

} API_TrimTypeID;

// =============================================================================
// Selection
//
// =============================================================================

/**
 * @brief Types of the selection.
 * @enum API_SelTypeID
 * @ingroup Selection
 * @remarks This enum is used when you get information about the current selection. See the @ref ACAPI_Selection_Get function.
 * 			There are two basic type of selection methods in Archicad:
 * 			- The selection may be controlled by individually selected elements.
 * 			- The other possibility is to rely on the marquee area.
 * 			The @c API_SelEmpty identifier means that no selection is actually used in Archicad. The @c API_SelElems identifier corresponds to the first method when elements are individually selected. Other values identify that the selection is done by some kind of marquee shape.
 */
typedef enum {													// selection types
	API_SelEmpty					= 0,

	API_SelElems,

	API_MarqueePoly,
	API_MarqueeHorBox,
	API_MarqueeRotBox
} API_SelTypeID;

/**
 * @brief Types of the relative position to marquee criteria.
 * @enum API_SelRelativePosID
 * @ingroup Selection
 * @remarks This enum is used when you get information about the current marquee based selection. See the @ref ACAPI_Selection_Get function.
 */
typedef enum {
	API_InsidePartially				= 0,
	API_InsideEntirely,
	API_OutsidePartially,
	API_OutsideEntirely
} API_SelRelativePosID;

/**
 * @brief Information about the current selection.
 * @struct API_SelectionInfo
 * @ingroup Selection
 * @remarks This structure is used to determine the type and the parameters of the current selection. You can retrieve this information with the @ref ACAPI_Selection_Get function. To change the current marquee with @ref ACAPI_Selection_SetMarquee, you should set the typeID, multiStory and marquee fields in the @ref API_SelectionInfo parameter. In case of marquee-type selection don't forget to dispose the coords handle in the marquee region when you don't need it any more.
 */
struct API_SelectionInfo {

/**
 * @brief The type of the selection. It can be one of the marquee type or element type selection.
 * @var typeID
 */
	API_SelTypeID					typeID;


/**
 * @brief Number of selected elements.
 * @var sel_nElem
 */
	Int32							sel_nElem;

/**
 * @brief Number of the currently selected elements, which are editable.
 * @var sel_nElemEdit
 */
	Int32							sel_nElemEdit;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1[3];

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool							filler_2[3];


/**
 * @brief The marquee selection is extended to all stories.
 * @var multiStory
 */
	bool							multiStory;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3;

/**
 * @brief The parameters of the marquee selection region.
 *
 * @var marquee
 */
	API_Region						marquee;

};


// =============================================================================
// Reference points
//
// =============================================================================

/**
 * @brief Describes the various special points of elements.
 * @enum API_NeigID
 * @ingroup Element
 * @remarks Here are the neigIDs with their inIndex in brackets for walls :
 * 			Here are the neigIDs with their inIndex in brackets for columns :
 * 			Here are the neigIDs with their inIndex in brackets for windows (and very similar for doors):
 * 			Here are the neigIDs with their inIndex in brackets for objects (and very similar for lamps):
 * 			Here are the neigIDs with their inIndex in brackets for slabs :
 * 			Here are the neigIDs with their inIndex in brackets for roofs :
 * 			Here are the neigIDs with their inIndex in brackets for meshes :
 * 			Here are the neigIDs with their inIndex in brackets for dimensions :
 * 			Here are the neigIDs with their inIndex in brackets for radial dimensions :
 * 			Here are the neigIDs with their inIndex in brackets for level dimensions :
 * 			Here are the neigIDs with their inIndex in brackets for angle dimensions :
 * 			Here are the neigIDs with their inIndex in brackets for texts :
 * 			Here are the neigIDs with their inIndex in brackets for labels :
 * 			Here are the neigIDs with their inIndex in brackets for zones :
 * 			Here are the neigIDs with their inIndex in brackets for hatches :
 * 			Here are the neigIDs with their inIndex in brackets for lines :
 * 			Here are the neigIDs with their inIndex in brackets for arcs :
 * 			Here are the neigIDs with their inIndex in brackets for circles :
 * 			Here are the neigIDs with their inIndex in brackets for splines :
 * 			Here are the neigIDs with their inIndex in brackets for hotspots :
 * 			Here are the neigIDs with their inIndex in brackets for cutplanes :
 * 			Here are the neigIDs with their inIndex in brackets for cameras :
 * 			Here are the neigIDs with their inIndex in brackets for virtual symbols :
 * 			Here are the neigIDs with their inIndex in brackets for pictures :
 * 			Here are the neigIDs with their inIndex in brackets for camera sets :
 * 			Here are the neigIDs with their inIndex in brackets for beams :
 * 			Here are the neigIDs with their inIndex in brackets for drawings :
 */
typedef enum {
	APINeig_None						= 0,

	APINeig_Wall						= 1,	// wall end points
	APINeig_WallPl						= 2,	// wall corrected connection point
	APINeig_WallOn						= 3,	// wall reference line
	APINeig_WallPlOn					= 4,	// wall non-reference line

	APINeig_Colu						= 5,	// column origo & corners

	APINeig_Beam						= 6,	// beam points
	APINeig_BeamOn						= 7,	// beam segments
	APINeig_BeamHole					= 8,	// beam's hole points

	APINeig_Wind						= 9,	// hotspots in the window object
	APINeig_WindHole					= 10,	// corners of window hole

	APINeig_Door						= 11,	// hotspots in the door object
	APINeig_DoorHole					= 12,	// corners of door hole

	APINeig_Symb						= 13,	// hotspots in the general object

	APINeig_Light						= 14,	// hotspots in the light object

	APINeig_Ceil						= 15,	// vertexes of the ceiling
	APINeig_CeilOn						= 16,	// edges of the ceiling

	APINeig_Roof						= 17,	// vertexes of the roof polygon
	APINeig_RoofOn						= 18,	// edges of the roof polygon
	APINeig_RBL							= 19,	// roof reference line endpoints
	APINeig_RBLOn						= 20,	// polyroof pivot polygon

	APINeig_Mesh						= 21,	// vertexes of the mesh
	APINeig_MeshOn						= 22,	// edges of the mesh
	APINeig_MeshRidge					= 23,	// vertexes of the mesh ridges
	APINeig_MeshRidgeOn					= 24,	// edges of the mesh ridges

	APINeig_DimInt						= 25,	// dimension segment (interval) as in old dim
	APINeig_DimPt						= 26,	// a dimensioning point in the dimension chain
	APINeig_DimOn						= 27,	// dimension line

	APINeig_RadDim						= 28,	// radial dimension's location

	APINeig_LevDim						= 29,	// level dimension marker's center point

	APINeig_AngDim						= 30,	// angle dimension point
	APINeig_AngDimOn					= 31,	// angle dimension arc

	APINeig_Word						= 32,	// multiline text corners

	APINeig_Label						= 33,	// label points

	APINeig_Room						= 34,	// room corner
	APINeig_RoomStamp					= 35,	// room stamp hotspot
	APINeig_RoomOn						= 36,	// room side line
	APINeig_RoomRefPt					= 37,	// room reference point

	APINeig_Hatch						= 38,	// vertexes of the hatch
	APINeig_HatchOn						= 39,	// edges of the hatch

	APINeig_Line						= 40,	// line end / middle points
	APINeig_LineOn						= 41,	// the line itself

	APINeig_PolyLine					= 42,	// vertexes of the polyLine
	APINeig_PolyLineOn					= 43,	// edges of the polyLine

	APINeig_Arc							= 44,	// arc endpoints and center
	APINeig_ArcOn						= 45,	// the arc itself

	APINeig_Circ						= 46,	// diagonals and center of circle
	APINeig_CircOn						= 47,	// the circle itself

	APINeig_Spline						= 48,	// spline corners
	APINeig_SplineOn					= 49,	// spline segments

	APINeig_Hot							= 50,	// hotspot element point

	APINeig_CutPlane					= 51,	// cutPlane points
	APINeig_CutPlOn						= 52,	// cutPlane segments

	APINeig_Camera						= 53,	// camera points

	APINeig_CamSet						= 54,	// camSet points

	APINeig_VirtSy						= 55,	// virtual symbol hotspots
	APINeig_VirtSyOn					= 56,	// virtual symbol lines

	APINeig_PictObj						= 57,	// 4 corners of pasted pictures

	APINeig_Detail						= 58,	// detail element
	APINeig_DetailPoly					= 59,	// detail element polygon vertex
	APINeig_DetailPolyOn				= 60,	// detail element polygon edge
	APINeig_DetailMarker				= 61,	// detail marker reference

	APINeig_Symb3D						= 62,	// 3d hotspots in the general object
	APINeig_Light3D						= 63,	// 3d hotspots in the light object
	APINeig_Wind3D						= 64,	// 3d hotspots in the window object
	APINeig_Door3D						= 65,	// 3d hotspots in the window object

	APINeig_WindMark					= 66,	// window marker
	APINeig_DoorMark					= 67,	// door marker

	APINeig_CutPlMarker					= 68,	// section marker

	APINeig_WallPlClOff					= 69,	// wall corner point (Clean inters. off)
	APINeig_WallPlOnClOff				= 70,	// wall non-reference line (Clean inters. off)

	APINeig_SymbOn						= 71,	// line status in the general object
	APINeig_WindOn						= 72,	// line status in the window object
	APINeig_DoorOn						= 73,	// line status in the door object
	APINeig_LightOn						= 74,	// line status in the light object

	APINeig_Note						= 75,	// note hotspot

	APINeig_SplineDir					= 76,	// spline direction handle

	APINeig_DrawingCenter				= 77,	// center of drawing
	APINeig_DrawingFrame				= 78,	// frame of drawing
	APINeig_DrawingFrameOn				= 79,	// frame of drawing
	APINeig_DrawingIDF					= 80,	// internal point of drawing
	APINeig_DrawingIDFOn				= 81,	// internal line of drawing
	APINeig_DrawingTitle				= 82,	// drawing title point
	APINeig_DrawingTitleOn				= 83,	// drawing title line

	APINeig_Worksheet					= 84,	// worksheet element
	APINeig_WorksheetPoly				= 85,	// worksheet element polygon vertex
	APINeig_WorksheetPolyOn				= 86,	// worksheet element polygon edge
	APINeig_WorksheetMarker				= 87,	// worksheet marker reference

	APINeig_Elevation					= 88,	// elevation points
	APINeig_ElevationOn					= 89,	// elevation segment lines
	APINeig_ElevationMarker				= 90,	// elevation marker

	APINeig_InteriorElevation			= 91,	// interior elevation points
	APINeig_InteriorElevationOn			= 92,	// interior elevation segment lines
	APINeig_InteriorElevationMarker		= 93,	// interior elevation marker

	APINeig_SectionSegment				= 94,	// section/elevation/interior elevation segment points
	APINeig_SectionSegmentOn			= 95,	// section/elevation/interior elevation segment lines
	APINeig_SectionSegmentMarker		= 96,	// section/elevation/interior elevation segment marker

	APINeig_CurtainWall					= 97,	// curtain wall end points
	APINeig_CurtainWallOn				= 98,	// curtain wall reference line
	APINeig_CurtainWallCut				= 99,	// curtain wall's cutaway frames and panels points
	APINeig_CurtainWallCutOn			= 100,	// curtain wall's cutaway frames and panels lines
	APINeig_CWSegment					= 101,	// curtain wall segment end points
	APINeig_CWSegmentOn					= 102,	// curtain wall segment reference line
	APINeig_CWSegmentBaseLine			= 103,	// curtain wall segment base line end points
	APINeig_CWSegmentBaseLineOn			= 104,	// curtain wall segment base line
	APINeig_CWFrame						= 105,	// vertexes of curtain wall frame
	APINeig_CWFrameOn					= 106,	// edges of curtain wall frame
	APINeig_CWFrame3D					= 107,	//
	APINeig_CWPanel						= 108,	// vertexes of curtain wall panel
	APINeig_CWPanel3D					= 109,	// 3d hotspots in the curtain wall panel
	APINeig_CWJunction					= 110,	// vertexes of curtain wall junction
	APINeig_CWJunction3D				= 111,	//
	APINeig_CWAccessory					= 112,	// vertexes of curtain wall accessory
	APINeig_CWAccessory3D				= 113,	//

	APINeig_Shell						= 114,
	APINeig_ShellOn						= 115,

	APINeig_Skylight					= 116,
	APINeig_SkylightHole				= 117,
	APINeig_Skylight3D					= 118,
	APINeig_SkylightOn3D				= 119,
	APINeig_SkylightOn					= 120,
	APINeig_SkylightMark				= 121,

	APINeig_Morph						= 122,
	APINeig_MorphOn						= 123,

	APINeig_ChangeMarker				= 124,
	APINeig_ChangeMarkerPoly			= 125,
	APINeig_ChangeMarkerPolyOn			= 126,
	APINeig_ChangeMarkerMarker			= 127,

	APINeig_ColuOn						= 128,	// Column: Area on Floor Plan (except Hotspots), or Reference Axis in 3D (except the endpoints).
	APINeig_WordOn						= 129,	// Text: Area of Text (except Hotspots)
	APINeig_CurtainWallBaseLine			= 130,	// Curtain Wall: Hotspots of the Reference Line
	APINeig_CurtainWallBaseLineOn		= 131,	// Curtain Wall: Reference Line (except Hotspots)

	APINeig_StairOn						= 132,
	APINeig_Tread						= 133,
	APINeig_TreadOn						= 134,
	APINeig_Riser						= 135,
	APINeig_RiserOn						= 136,
	APINeig_Stair						= 137,
	APINeig_StairStructure				= 138,
	APINeig_StairStructureOn			= 139,

	APINeig_Railing						= 140,
	APINeig_RailingOn					= 141,
	APINeig_RailingToprail				= 142,
	APINeig_RailingToprailOn			= 143,
	APINeig_RailingHandrail				= 144,
	APINeig_RailingHandrailOn			= 145,
	APINeig_RailingRail					= 146,
	APINeig_RailingRailOn				= 147,
	APINeig_RailingPost					= 148,
	APINeig_RailingPostOn				= 149,
	APINeig_RailingInnerPost			= 150,
	APINeig_RailingInnerPostOn			= 151,
	APINeig_RailingBaluster				= 152,
	APINeig_RailingBalusterOn			= 153,
	APINeig_RailingPanel				= 154,
	APINeig_RailingPanelOn				= 155,
	APINeig_RailingToprailEnd			= 156,
	APINeig_RailingToprailEndOn			= 157,
	APINeig_RailingHandrailEnd			= 158,
	APINeig_RailingHandrailEndOn		= 159,
	APINeig_RailingRailEnd				= 160,
	APINeig_RailingRailEndOn			= 161,
	APINeig_RailingToprailConnection	= 162,
	APINeig_RailingToprailConnectionOn	= 163,
	APINeig_RailingHandrailConnection	= 164,
	APINeig_RailingHandrailConnectionOn = 165,
	APINeig_RailingRailConnection		= 166,
	APINeig_RailingRailConnectionOn		= 167,
	APINeig_RailingEndFinish			= 168,
	APINeig_RailingEndFinishOn			= 169,
	APINeig_BeamSegment					= 170,
	APINeig_BeamSegmentOn				= 171,
	APINeig_ColumnSegment				= 172,
	APINeig_ColumnSegmentOn				= 173

} API_NeigID;

typedef enum {													// subtypes for partial element selection
	APINeigElemPart_None			= 0,
	APINeigElemPart_Edge,										// body edge
	APINeigElemPart_Vertex,										// body vertex
	APINeigElemPart_Face,										// body face
	APINeigElemPart_Subelem										// subelem
} API_NeigElemPartID;

#define	API_NeigFlg_Normal			0x0000
#define	API_NeigFlg_HoleSel			0x0001
#define API_NeigFlg_Extra3D			0x0002
#define API_NeigFlg_Ghost			0x0004
#define API_NeigFlg_Surface			0x0008

/**
 * @brief Describes a neig point of an element.
 * @struct API_Neig
 * @ingroup UserInput
 * @remarks This structure is used in requiring the current element selection ( @ref ACAPI_Selection_Get),
 * 			selecting elements or element parts (@ref ACAPI_Selection_Select), and getting user input ( @ref ACAPI_UserInput_GetPoint, etc.).
 */
struct API_Neig {

/**
 * @brief Type of the element neig. It also defines the type of the element; you can convert the @c neigID to @c API_ElemTypeID with the @ref ACAPI_Element_NeigIDToElemType function.
 * @var neigID
 */
	API_NeigID						neigID;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief Guid of the element.
 * @var guid
 */
	API_Guid						guid;

/**
 * @brief Subindex inside the element.
 * @var inIndex
 */
	Int32							inIndex;

	/**
	 * @brief Flags of the neig:
	 * 		  |Value               | Description |
	 * 		  |--------------------|------------|
	 * 		  |API_NeigFlg_Normal  | Normal neig.|
	 * 		  |API_NeigFlg_HoleSel | The neig is part of a hole.|
	 * 		  |API_NeigFlg_Extra3D | The neig appears only in 3D.|
	 * 		  |API_NeigFlg_Ghost   | The neig is for an element coming from the ghost story.|
	 * 		  |API_NeigFlg_Surface | The neig refers to a surface of an element (e.g. Morph face).|
	 * @var flags
	 */
	Int32							flags;

/**
 * @brief Type of the element part in case of partial selection (currently available with Morph only):
 * 		  |Value | Description |
 * 		  |------------------------|-------------------------------------|
 * 		  |@c APINeigElemPart_Edge | An edge of the element is selected.|
 * 		  |@c APINeigElemPart_None | The whole element is selected.|
 * 		  |@c APINeigElemPart_Vertex | A vertex of the element is selected.|
 * 		  |@c APINeigElemPart_Face | A face of the element is selected.|
 * 		  |@c APINeigElemPart_Subelem | A subelement is selected.|
 * @var elemPartType
 */
	API_NeigElemPartID				elemPartType;

/**
 * @brief Index of the element part (edge, vertex, face) partially selected.
 * @var elemPartIndex
 */
	UInt32							elemPartIndex;

/**
 * @brief Subtype of the element.
 * @var subType
 */
	short							subType;

/**
 * @brief Node type of the element.
 * @var nodeType
 */
	short							nodeType;

/**
 * @brief Supplemental unique identifier used for certain neig types.
 * @var supplUnId
 */
	UInt32							supplUnId;

/**
 * @brief Constructor with null guid.
 */
	API_Neig () : API_Neig (APINULLGuid)
	{
	}

/**
 * @brief Constructor.
 * @param elemGuid Guid of the element.
 */
	explicit API_Neig (const API_Guid& elemGuid) :
		neigID (),
		filler_1 (),
		guid (elemGuid),
		inIndex (),
		flags (),
		elemPartType (),
		elemPartIndex (),
		subType (),
		nodeType (),
		supplUnId ()
	{
	}

};

typedef GS::Pair<API_Neig, API_Coord3D> API_ElementHotspot;


// =============================================================================
// Drawing primitives (when drawn or exploded)
//
// =============================================================================

#define	APINOTIFY_NODATA				100
#define	APINOTIFY_OWN_MEMORY_HANDLER	200

#define	APIGdl_Default					-1
#define	APIGdl_FromFloor				2
#define	APIGdl_From3DWin				3
#define	APIGdl_FromSide					4
#define	APIGdl_FromDial					5
#define	APIGdl_FromList					6
#define	APIGdl_FromDetail				7
#define	APIGdl_FromLayout				8

/**
 * @brief Various primitive element types and control codes.
 * @enum API_PrimTypeID
 * @ingroup LibraryPart
 */
typedef enum {
	API_ZombiePrimID				  = 0,

	API_PrimPointID,
	API_PrimLineID,
	API_PrimArcID,
	API_PrimTextID,
	API_PrimPLineID,
	API_PrimTriID,
	API_PrimPolyID,
	API_PrimPictID,												// picture on placed drawing

	API_PrimCtrl_BegID,											// begin drawing the element				(no pars)
	API_PrimCtrl_HatchBorderBegID,								// begin exporting hatch border				(API_PrimHatchBorder)
	API_PrimCtrl_HatchBorderEndID,								// end exporting hatch border				(no pars)
	API_PrimCtrl_HatchLinesBegID,								// begin exporting hatch lines				(API_PrimHatchBorder)
	API_PrimCtrl_HatchLinesEndID,								// end exporting hatch lines				(no pars)
	API_PrimCtrl_HoledimLinesBegID,								// begin exporting window/door dim.lines	(no pars)
	API_PrimCtrl_HoledimLinesEndID,								// end exporting window/door dim.lines		(no pars)
	API_PrimCtrl_ArrowBegID,									// begin exporting arrow primitives			(no pars)
	API_PrimCtrl_ArrowEndID,									// end exporting arrow primitives			(no pars)
	API_PrimCtrl_ElementRefID,									// reference to another element				(API_PrimElemRef)
	API_PrimCtrl_EndID,											// end element drawing						(no pars)
	API_PrimCtrl_PlacedBorderBegID,								// begin exporting placed drawing border 	(no pars)
	API_PrimCtrl_PlacedBorderEndID,								// end exporting placed drawing border 		(no pars)
	API_PrimCtrl_TextBegID,										// begin exporting text block				(API_PrimText)
	API_PrimCtrl_TextEndID,										// end exporting text block					(API_PrimText)

	API_PrimCtrl_CWallPanelBegID,								// begin exporting a curtainwall panel		(API_PrimCWallPanel)
	API_PrimCtrl_CWallPanelEndID,								// end exporting a curtainwall panel		(no pars)

	API_PrimCtrl_BackgroundFillBegID,							///< Begin exporting drawing background fill	(no pars)
	API_PrimCtrl_BackgroundFillEndID,							///< End exporting drawing background fill		(no pars)

	API_PrimCtrl_FrameBegID,									// begin exporting text frame primitives	(no pars)
	API_PrimCtrl_FrameEndID										// end exporting text frame primitives		(no pars)
} API_PrimTypeID;



/**
 * @brief Hatch border for primitive elements.
 * @ingroup Geometry
 * @struct API_PrimHatchBorder
 * @remarks This structure is used to pass parameters of the hatch to be drawn in the ShapePrimsProc callback function.
 */
struct API_PrimHatchBorder {

/**
 * @brief The frame of the hatch is visible.
 * @var doFrame
 */
	bool							doFrame;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[3];

/**
 * @brief Fill attribute index.
 * @var fillInd
 */
	API_AttributeIndex				fillInd;

/**
 * @brief (Overridden) pen attribute index for the fill lines. If this value is 1008 (RGB Pen), then the foreground color of the fill is defined in the fillRgb parameter.
 * @var fillPen
 */
	API_ExtendedPenType				fillPen;

/**
 * @brief Pen attribute index for the fill background. If this value is 1008 (RGB Pen), then the background color of the fill is defined in the fillbkgRgb parameter.
 * @var fillbkgPen
 */
	short							fillbkgPen;

/**
 * @brief Fill transparency.
 * @var transparency
 */
	short							transparency;

/**
 * @brief Fill category:
 * 		  |||
 * 		  |--- |--- |
 * 		  |APIHatch_DraftingFills|Default fill category. Drafting fills adopt the Drafting Fill settings chosen in Display Options.|
 * 		  |APIHatch_CoverFills|The Cover Fill category is assigned to the fills of Slabs, Roofs, Meshes and Zones on the floor plan. Cover fills adopt the Element Cover Fill settings chosen in Display Options.|
 * 		  |APIHatch_CutFills|The Cut Fill category is assigned to the fills of Cut Elements. Cut fills adopt the Cut Fill settings chosen in Display Options.|
 *
 * @var determination
 */
	short							determination;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	short							filler_2[3];

/**
 * @brief Foreground color of the fill; valid only if fillPen is RGB Pen (value 1008).
 * @var fillRgb
 */
	API_RGBColor					fillRgb;

/**
 * @brief Background color of the fill; valid only if fillbkgPen is RGB Pen (value 1008).
 * @var fillbkgRgb
 */
	API_RGBColor					fillbkgRgb;

/**
 * @brief The hatch has gradient fill (from foreground to background color).
 * @var isGradient
 */
	bool							isGradient;

/**
 * @brief The fill gradient is linear, otherwise it is radial.
 * @var isLinear
 */
	bool							isLinear;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	bool							filler_3[6];

/**
 * @brief Orientation and distortion parameters of the cover fill.
 * @var hatchOrientation
 */
	API_HatchOrientation			hatchOrientation;

};

/**
 * @brief Primitive element reference.
 * @ingroup Geometry
 * @struct API_PrimElemRef
 * @since Archicad 26
 * @remarks Primitive element references can be passed e.g. for windows and doors, where they refer to the owning wall.
 * 			From version 26 the type of the typeID member was changed into @ref API_ElemType.
 */
struct API_PrimElemRef {

/**
 * @brief Guid of the referenced element.
 * @var guid
 */
	API_Guid						guid;

/**
 * @brief Type of the referenced element.
 * @var type
 */
	API_ElemType					type;

/**
 * @brief Drawing order index of the referenced element.
 * @var drwIndex
 */
	short							drwIndex;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	short							filler_0;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1[2];

};

/**
 * @brief Header information for primitive elements.
 * @ingroup Geometry
 * @struct API_Prim_Head
 * @ingroup LibraryPart
 */
struct API_Prim_Head {

/**
 * @brief Type of the primitive element (see @ref API_PrimTypeID).
 * @var typeID
 */
	API_PrimTypeID					typeID;

/**
 * @brief Layer attribute index of the parent element.
 * @var layer
 */
	API_AttributeIndex				layer;

/**
 * @brief (Overridden) pen attribute index of the primitive element.
 * @var pen
 */
	API_ExtendedPenType				pen;

/**
 * @brief Drawing order index of the original element if the primitive element is a part of the content of a drawing element generated from a view.
 * @var drwIndex
 */
	short							drwIndex;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1[3];

/**
 * @brief Renovation Status of the original element.
 * @var renovationStatus
 */
	API_RenovationStatusType		renovationStatus;

};

/**
 * @brief A primitive hotspot.
 * @ingroup Geometry
 * @struct API_PrimHotspot
 * @ingroup LibraryPart
 */
struct API_PrimHotspot {

/**
 * @brief General primitive element header (not used with @ref ACAPI_LibraryPart_GetHotspots).
 * @var head
 */
	API_Prim_Head					head;

/**
 * @brief Coordinate of the hotspot.
 * @var loc
 */
	API_Coord						loc;

/**
 * @brief Neig index and unique ID of the hotspot.
 * @var neig
 */
	API_Neig						neig;

};

/**
 * @brief A primitive point.
 * @ingroup Geometry
 * @struct API_PrimPoint
 */
struct API_PrimPoint {

/**
 * @brief General primitive element header.
 * @var head
 */
	API_Prim_Head					head;

/**
 * @brief The location of the point.
 * @var loc
 */
	API_Coord						loc;

};

/**
 * @brief A primitive line.
 * @ingroup Geometry
 * @struct API_PrimLine
 */
struct API_PrimLine {

/**
 * @brief General primitive element header.
 * @var head
 */
	API_Prim_Head					head;

/**
 * @brief Line type attribute index.
 * @var ltypeInd
 */
	API_AttributeIndex				ltypeInd;

/**
 * @brief Line category:
 * 		  |Category|Meaning|
 * 		  |--- |--- |
 * 		  |APILine_DetOrigin|Default line category. Lines in the Drafting line category are not affected by the Line Weight and Section Fill settings chosen in Display Options.|
 * 		  |APILine_DetInnerLine|A skin separator line separates skins of composite structures. Lines in the Skin Separator category will be either hidden or shown depending on the Cut Fill type chosen in Display Options.|
 * 		  |APILine_DetContourLine|Lines in the Cut line category will be affected if you have chosen the 'Bold Cut Line' setting in the Line Weight menu of Display Options.|
 *
 * @var determination
 */
	short							determination;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief Thickness of the line; overrides the pen attribute's penWeight in the header in [mm].
 * @var penWeight
 */
	double							penWeight;

/**
 * @brief One endpoint of the line.
 * @var c1
 */
	API_Coord						c1;

/**
 * @brief The other endpoint of the line.
 * @var c2
 */
	API_Coord						c2;

};

/**
 * @brief A primitive arc.
 * @ingroup Geometry
 * @struct API_PrimArc
 * @ingroup DrawingPrimitive
 */
struct API_PrimArc {

/**
 * @brief General primitive element header.
 * @var head
 */
	API_Prim_Head					head;

/**
 * @brief Line type attribute index.
 * @var ltypeInd
 */
	API_AttributeIndex				ltypeInd;

/**
 * @brief Filled with solid color?
 * @var solid
 */
	bool							solid;

/**
 * @brief Whole arc?
 * @var whole
 */
	bool							whole;

/**
 * @brief Line category:
 * 		  |Category|Meaning|
 * 		  |--- |--- |
 * 		  |APILine_DetOrigin|Default line category. Lines in the Drafting line category are not affected by the Line Weight and Section Fill settings chosen in Display Options.|
 * 		  |APILine_DetInnerLine|A skin separator line separates skins of composite structures. Lines in the Skin Separator category will be either hidden or shown depending on the Cut Fill type chosen in Display Options.|
 * 		  |APILine_DetContourLine|Lines in the Cut line category will be affected if you have chosen the 'Bold Cut Line' setting in the Line Weight menu of Display Options.|
 *
 * @var determination
 */
	short							determination;

/**
 * @brief If true then the direction of the arc is negative (clockwise).
 * @var reflected
 */
	bool							reflected;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	char							filler_1[7];

/**
 * @brief Thickness of the arc [mm].
 * @var penWeight
 */
	double							penWeight;

/**
 * @brief Origin of the arc.
 * @var orig
 */
	API_Coord						orig;

/**
 * @brief Radius of the arc.
 * @var r
 */
	double							r;

/**
 * @brief Beginning angle of the arc (CCW, from the horizontal axis).
 * @var begAng
 */
	double							begAng;

/**
 * @brief End angle of the arc (CCW, from the horizontal axis).
 * @var endAng
 */
	double							endAng;

/**
 * @brief 0.0, or the angle of the 'a' axis.
 * @var angle
 */
	double							angle;

/**
 * @brief 1.0, or 'a/b' of the ellipse.
 * @var ratio
 */
	double							ratio;

};

/**
 * @brief A primitive text.
 * @struct API_PrimText
 * @ingroup DrawingPrimitive
 */
struct API_PrimText {

/**
 * @brief General primitive element header.
 * @var head
 */
	API_Prim_Head					head;

/**
 * @brief ind1 in array type parameter
 * @var ind1
 */
	short							ind1;

/**
 * @brief ind2 in array type parameter
 * @var ind2
 */
	short							ind2;

/**
 * @brief additive parameter index. Non zero if the text generated by a TEXT2 GDL command with an argument referencing to a text type variable
 * @var paramInd
 */
	short							paramInd;

/**
 * @brief Font attribute index.
 * @var font
 */
	short							font;

/**
 * @brief Style of text:
 * 		  |Face bit|Style|
 * 		  |--- |--- |
 * 		  |APIFace_Plain|Plain text|
 * 		  |APIFace_Bold|Bold|
 * 		  |APIFace_Italic|Italic|
 * 		  |APIFace_Underline|Underline|
 *
 * @var faceBits
 */
	unsigned short					faceBits;

/**
 * @brief Special text effects:
 * 		  | APIEffect_StrikeOut |	Strikethrough text |
 * 		  | APIEffect_SuperScript |	Superscript |
 * 		  | APIEffect_SubScript |	Subscript |
 * 		  | APIEffect_Fractional |	Fractional text (not used) |
 * 		  | APIEffect_Protected |	Protected text (autotext reference) |
 * @var effectBits
 */
	short							effectBits;

/**
 * @brief Anchor point of the text
 * @var anchor
 */
	API_AnchorID					anchor;

/**
 * @brief Justification of the text
 * @var just
 */
	API_JustID						just;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief Left-baseline position, including the angle.
 * @var loc
 */
	API_Coord						loc;

/**
 * @brief Vertical size of text box in mm.
 * @var heightMM
 */
	double							heightMM;

/**
 * @brief Horizontal size of text box in mm.
 * @var widthMM
 */
	double							widthMM;

/**
 * @brief Angle of the text [radian].
 * @var angle
 */
	double							angle;

/**
 * @brief Text width factor; 1.0 is 100%.
 * @var widthFactor
 */
	double							widthFactor;

/**
 * @brief Character spacing factor; 1.0 is 100%.
 * @var charSpaceFactor
 */
	double							charSpaceFactor;

};
																// callback parameters for API_PrimText:
																//    (char **) par1				content
																//    (unsigned short **) par2		UniCode content

/**
 * @brief A primitive polyline.
 * @ingroup Geometry
 * @struct API_PrimPLine
 * @remarks The actual coordinates of the polyline vertices are passed in the par1 parameter of the ShapePrimsProc function.
 * 			The par3 parameter contains the polyline arcs.
 */
struct API_PrimPLine {

/**
 * @brief General primitive element header.
 * @var head
 */
	API_Prim_Head					head;

/**
 * @brief Line type attribute index.
 * @var ltypeInd
 */
	API_AttributeIndex				ltypeInd;

/**
 * @brief Line category:
 * 		  |Category|Meaning|
 * 		  |--- |--- |
 * 		  |APILine_DetOrigin|Default line category. Lines in the Drafting line category are not affected by the Line Weight and Section Fill settings chosen in Display Options.|
 * 		  |APILine_DetInnerLine|A skin separator line separates skins of composite structures. Lines in the Skin Separator category will be either hidden or shown depending on the Cut Fill type chosen in Display Options.|
 * 		  |APILine_DetContourLine|Lines in the Cut line category will be affected if you have chosen the 'Bold Cut Line' setting in the Line Weight menu of Display Options.|
 *
 * @var determination
 */
	short							determination;

/**
 * @brief Determine the draw segment mode of the polyline. 0 means draw segments one-by-one, 1 means draw segments continuously
 * @var drawSegmentMode
 */
	short							drawSegmentMode;

/**
 * @brief Number of vertices.
 * @var nCoords
 */
	Int32							nCoords;

/**
 * @brief Number of arcs.
 * @var nArcs
 */
	Int32							nArcs;

/**
 * @brief Thickness of the polyline segments in mm.
 * @var penWeight
 */
	double							penWeight;

};
																// callback parameters for API_PrimPLine:
																//    (API_Coord *) par1		coordinates
																//	  (API_PolyArc *) par3		arc parameters

/**
 * @brief A primitive triangle.
 * @ingroup Geometry
 * @struct API_PrimTri
 */
struct API_PrimTri {

/**
 * @brief General primitive element header.
 * @var head
 */
	API_Prim_Head					head;

/**
 * @brief Line type attribute index.
 * @var ltypeInd
 */
	API_AttributeIndex				ltypeInd;

/**
 * @brief Filled with solid color?
 * @var solid
 */
	bool							solid;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1;

/**
 * @brief Line category:
 * 		  |Category|Meaning|
 * 		  |--- |--- |
 * 		  |APILine_DetOrigin|Default line category. Lines in the Drafting line category are not affected by the Line Weight and Section Fill settings chosen in Display Options.|
 * 		  |APILine_DetInnerLine|A skin separator line separates skins of composite structures. Lines in the Skin Separator category will be either hidden or shown depending on the Cut Fill type chosen in Display Options.|
 * 		  |APILine_DetContourLine|Lines in the Cut line category will be affected if you have chosen the 'Bold Cut Line' setting in the Line Weight menu of Display Options.|
 *
 * @var determination
 */
	short							determination;

/**
 * @brief Thickness of the triangle segments in mm.
 * @var penWeight
 */
	double							penWeight;

/**
 * @brief Triangle's vertices.
 * @var c
 */
	API_Coord						c[3];

};

/**
 * @brief A primitive polygon.
 * @ingroup Geometry
 * @struct API_PrimPoly
 * @ingroup DrawingPrimitive
 * @remarks The actual coordinates of the polyline vertices are passed in the par1 parameter of the ShapePrimsProc function. The par2 and par3 parameters contain the polygon endpoints and the polygon arcs, as in @ref API_Polygon.
 */
struct API_PrimPoly {

/**
 * @brief General primitive element header.
 * @var head
 */
	API_Prim_Head					head;

/**
 * @brief Line type attribute index.
 * @var ltypeInd
 */
	API_AttributeIndex				ltypeInd;

/**
 * @brief Filled with solid color?
 * @var solid
 */
	bool							solid;

/**
 * @brief Have to use rgbColor when it set.
 * @var useRgb
 */
	bool							useRgb;

/**
 * @brief Line category:
 * 		  |Category|Meaning|
 * 		  |--- |--- |
 * 		  |APILine_DetOrigin|Default line category. Lines in the Drafting line category are not affected by the Line Weight and Section Fill settings chosen in Display Options.|
 * 		  |APILine_DetInnerLine|A skin separator line separates skins of composite structures. Lines in the Skin Separator category will be either hidden or shown depending on the Cut Fill type chosen in Display Options.|
 * 		  |APILine_DetContourLine|Lines in the Cut line category will be affected if you have chosen the 'Bold Cut Line' setting in the Line Weight menu of Display Options.|
 *
 * @var determination
 */
	short							determination;

/**
 * @brief Thickness of the polygon segments in mm.
 * @var penWeight
 */
	double							penWeight;

/**
 * @brief Number of vertices.
 * @var nCoords
 */
	Int32							nCoords;

/**
 * @brief Number of closed subpolygons including the first one.
 * @var nSubPolys
 */
	Int32							nSubPolys;

/**
 * @brief Number of curves in the polygon.
 * @var nArcs
 */
	Int32							nArcs;

/**
 * @brief (Overridden) pen attribute of the fill.
 * @var fillPen
 */
	API_ExtendedPenType				fillPen;

/**
 * @brief The color of fill if useRgb is set.
 * @var rgbColor
 */
	API_RGBColor					rgbColor;

};
																// callback parameters for API_PrimPoly:
																//    (API_Coord *) par1		coordinates
																//    (long *) par2				polyends
																//    (API_PolyArc *) par3		arc parameters

/**
 * @brief A picture inside a placed drawing.
 * @ingroup Geometry
 * @struct API_PrimPict
 * @ingroup DrawingPrimitive
 * @remarks  This structure formerly described a picture on a placed drawing on a PlotMaker layout. Since layouting was integrated into Archicad, it is the part of the drawing content of a @ref API_DrawingType element.
 * 			 Many of the data members have similar meanings to those of @ref API_PictureType.
 * 			 The picture data is passed in the par1 parameter of the ShapePrimsProc function. The par2 parameter contains the standard MIME type of the picture.
 * 			 The picture is not clipped by the border of the drawing on the layout. (Note: this is different from the behavior in PlotMaker.)
 * 			 The picture here was imported as drawing, rotated, then placed on the layout, and rotated back. Its bounding polygon was also adjusted.
 * 			 If you need the original picture data, switch to the drawing database, and fetch the information from there with @ref ACAPI_Element_Get and @ref ACAPI_Element_GetMemo.
 */
struct API_PrimPict {

/**
 * @brief General primitive element header.
 * @var head
 */
	API_Prim_Head					head;

/**
 * @brief Physical x size in pixels of the original picture.
 * @var pixelSizeX
 */
	short							pixelSizeX;

/**
 * @brief Physical y size in pixels of the original picture.
 * @var pixelSizeY
 */
	short							pixelSizeY;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief The rotation angle.
 * @var rotAngle
 */
	double							rotAngle;

/**
 * @brief Bounding box of the picture on the layout (without rotation and mirroring).
 * @var destBox
 */
	API_Box							destBox;

/**
 * @brief Color depth of the image.
 * @var colorDepth
 */
	API_ColorDepthID				colorDepth;

/**
 * @brief Storage format of the picture.
 * @var storageFormat
 */
	API_PictureFormat 				storageFormat;

/**
 * @brief Name of the picture as a Unicode string.
 * @var pictName
 */
	GS::uchar_t						pictName[API_UniLongNameLen];

/**
 * @brief MIME string identifying the image format.
 * @var mime
 */
	char							mime[128];

/**
 * @brief The anchor point of the picture.
 * @var anchor
 */
	API_AnchorID					anchor;

/**
 * @brief Tells if the picture is transparent.
 * @var transparent
 */
	bool							transparent;

/**
 * @brief Tells if the picture is mirrored.
 * @var mirrored
 */
	bool							mirrored;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	short							filler_2;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3[4];

};
																// callback parameter for API_PrimPict:
																//    (char **) par1			picture data

/**
 * @brief A primitive triangle.
 * @ingroup Element
 * @struct API_CWallPanel
 */
struct API_CWallPanel {

/**
 * @brief TODO
 * @var isWindow
 */
	bool							isWindow;

/**
 * @brief TODO
 * @var isDoor
 */
	bool							isDoor;

};

/**
 * @brief A union containing all drawing primitives used with @ref ACAPI_DrawingPrimitive_ShapePrims and @ref ACAPI_LibraryPart_ShapePrims.
 * @ingroup DrawingPrimitive
 * @union API_PrimElement
 */
union API_PrimElement {

/**
 * @brief General primitive element header.
 * @var header
 */
	API_Prim_Head					header;


/**
 * @brief A primitive point.
 * @var point
 */
	API_PrimPoint					point;

/**
 * @brief A primitive line.
 * @var line
 */
	API_PrimLine					line;

/**
 * @brief A primitive arc.
 * @var arc
 */
	API_PrimArc						arc;

/**
 * @brief A primitive text.
 * @var text
 */
	API_PrimText					text;

/**
 * @brief A primitive polyline.
 * @var pline
 */
	API_PrimPLine					pline;

/**
 * @brief A primitive triangle.
 * @var tri
 */
	API_PrimTri						tri;

/**
 * @brief A primitive polygon.
 * @var poly
 */
	API_PrimPoly					poly;

/**
 * @brief A picture inside a placed drawing element.
 * @var pict
 */
	API_PrimPict					pict;

/**
 * @brief The curtain wall panel is window or door type.
 * @var panelKind
 */
	API_CWallPanel					panelKind;

};

// Categories

/**
 * @brief Type identifiers of element category types.
 * @enum API_ElemCategoryID
 * @ingroup Category
 * @remarks API_ElemCategoryID is used in element category (API_ElemCategory structure) as identifier.
 */
typedef enum {
	API_ElemCategory_Undefined			= 0,
	API_ElemCategory_StructuralFunction,
	API_ElemCategory_Position,
	API_ElemCategory_RenovationStatus,
	API_ElemCategory_RenovationFilter,
	API_ElemCategory_BRI

} API_ElemCategoryID;

/**
 * @brief Element category structure.
 * @struct API_ElemCategory
 * @ingroup Category
 * @remarks This structure contains the data of an element category. For available category identifiers check @ref API_ElemCategoryID.
 */
struct API_ElemCategory {

/**
 * @brief GUID of the category.
 * @var guid
 */
	API_Guid					guid;

/**
 * @brief Identifier of the category.
 * @var categoryID
 */
	API_ElemCategoryID			categoryID;

/**
 * @brief Localized name of the category.
 * @var name
 */
	GS::uchar_t					name[API_UniLongNameLen];

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool						filler_1[2];

};

/**
 * @brief Element category value structure.
 * @struct API_ElemCategoryValue
 * @ingroup Category
 * @remarks This structure contains the data of an element category value. For available categories check @ref API_ElemCategoryID.
 */
struct API_ElemCategoryValue {

/**
 * @brief GUID of the category value
 * @var guid
 */
	API_Guid					guid;

/**
 * @brief the category of the category value
 * @var category
 */
	API_ElemCategory			category;

/**
 * @brief Localized name of the category value.
 * @var name
 */
	GS::uchar_t					name[API_UniLongNameLen];

/**
 * @brief specifies if it is visible on the UI
 * @var isVisibleOnUI
 */
	bool						isVisibleOnUI;

/**
 * @brief specifies if it is usable as a criteria
 * @var usableAsCriteria
 */
	bool						usableAsCriteria;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool						filler_1[3];

};

// ---------------------------------------------------------------------------------------------------------------------

#endif
