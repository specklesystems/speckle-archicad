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
#include "Variant.hpp"
#include "Any.hpp"

//from ACPM
#include "APIdefs_Base.h"
#include "APIdefs_LibraryParts.h"
#include "APIdefs_Database.h"
#include "API_Guid.hpp"


namespace Geometry {
	class PolyId;

	template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData> class CustomPolygon2D;
	typedef CustomPolygon2D<PolyId, PolyId, PolyId, PolyId> Polygon2D;
}


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

typedef bool API_ElemFilter [API_LastElemType + 1];


typedef enum {
	APIVarId_Generic				= 0,

	APIVarId_SymbStair				= 'SYST',
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

struct API_ElemType {
	API_ElemTypeID			typeID;			// type of the element
	API_ElemVariationID		variationID;	// type subcategory
	API_Guid				classID;		// unique id of the element type

	API_ElemType () = default;

	API_ElemType (API_ElemTypeID typeID)
		: typeID (typeID), variationID (APIVarId_Generic), classID (APINULLGuid)
	{}

	API_ElemType (API_ElemTypeID typeID, API_ElemVariationID variationID)
		: typeID (typeID), variationID (variationID), classID (APINULLGuid)
	{}

	API_ElemType (const API_Guid& classID)
		: typeID (API_ExternalElemID), variationID (APIVarId_Generic), classID (classID)
	{}

	API_ElemType&	operator= (const API_ElemType&) = default;

	API_ElemType&	operator= (API_ElemTypeID newTypeID)
	{
		typeID = newTypeID;
		variationID = APIVarId_Generic;
		classID = APINULLGuid;
		return *this;
	}

	API_ElemType&	operator= (const API_Guid& newClassID)
	{
		typeID = API_ExternalElemID;
		variationID = APIVarId_Generic;
		classID = newClassID;
		return *this;
	}

	bool	operator== (const API_ElemType& other) const
	{
		return typeID == other.typeID && variationID == other.variationID && classID == other.classID;
	}

	bool	operator!= (const API_ElemType& other) const
	{
		return !operator== (other);
	}

	bool	operator== (API_ElemTypeID otherTypeID) const
	{
		return typeID == otherTypeID;
	}

	bool	operator!= (API_ElemTypeID otherTypeID) const
	{
		return !operator== (otherTypeID);
	}

	bool	operator== (const API_Guid& otherClassID) const
	{
		return classID == otherClassID;
	}

	bool	operator!= (const API_Guid& otherClassID) const
	{
		return !operator== (otherClassID);
	}

	ULong	GenerateHashValue (void) const
	{
		return GS::CalculateHashValue (typeID, variationID, classID);
	}
};


extern "C++" {

template<>
struct std::hash<API_ElemType> {
	std::size_t operator() (const API_ElemType& elemType) const
	{
		return elemType.GenerateHashValue ();
	}
};


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

} // extern "C++"


typedef struct {
	API_ElemType					type;						// type of the element

	UInt32							filler_0;
	Int32							filler_1;
	API_Guid						guid;						// globally unique Id
	UInt64							modiStamp;					// modification stamp

	API_Guid						groupGuid;					// reference to the containing group element (APINULLGuid if not grouped)
	API_Guid						hotlinkGuid;				// reference to the containing hotlink element (APINULLGuid if not part of hotlink)
	short							floorInd;					// belongs to this floor
	API_AttributeIndex				layer;						// layer index

	bool							hasMemo;					// has memo data
	char							drwIndex;					// index in drawing order
	short							userId;						// member ID of the owner in TeamWork mode
	short							lockId;						// member ID of the locker in TeamWork mode, bool in normal mode
	API_AttributeIndex				rgr_layer;					// reference group layer (-1: special/locked group)

	API_RenovationStatusType		renovationStatus;			// renovation status
	API_Guid						renovationFilterGuid;		// appears only in this renovation filter
} API_Elem_Head;


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


// =============================================================================
// Element part identifier
//
// =============================================================================

class API_ElemPartId {
public:
	UInt32							main;
	UInt32							sub;
	Int32							floor;

	API_ElemPartId () : main (0), sub (0), floor (0) {}

	bool	operator==	(const API_ElemPartId& right) const		{ return (main == right.main && sub == right.sub && floor == right.floor); }
	bool	operator!=	(const API_ElemPartId& right) const		{ return !operator== (right); }
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


typedef struct {
	API_HatchOrientationTypeID		type;
	unsigned short					version;
	short							filler_1;
	Int32							flags;
	Int32							filler_2;
	API_Coord						origo;
	double							matrix00;
	double							matrix10;
	double							matrix01;
	double							matrix11;
	double							innerRadius;
} API_HatchOrientation;

typedef enum {
	API_CoverFillTransformationType_Global 		= 0,
	API_CoverFillTransformationType_Rotated 	= 1,
	API_CoverFillTransformationType_Distorted 	= 2
} API_CoverFillTransformationTypeID;

typedef struct {
	API_Coord		origo;
	API_Vector		xAxis;
	API_Vector		yAxis;
} API_CoverFillTransformation;

typedef struct {
	API_Coord						loc;
	double							angle;
	double							xRatio;
	double							yRatio;
} API_SyTran;

typedef struct {
	bool							showOnHome;					// show on home floor
	bool							showAllAbove;				// show all stories above this one
	bool							showAllBelow;				// show all stories below this one
	bool							filler_1;
	short							showRelAbove;				// show showRelAbove stories above this one
	short							showRelBelow;				// show showRelBelow stories below this one
} API_StoryVisibility;

typedef struct {
	short							homeStoryDifference;		// difference of home story from current story
	bool							newCreationMode;			// true: relative to current story, false: use head.floorInd
	bool							filler_1;
} API_LinkToSettings;

typedef enum  {
	API_Standard					= 0,						// show element with cut and below part
	API_StandardWithAbstract		= 1,						// show element with cut, above and below part
	API_CutOnly						= 2,						// show cut part only
	API_OutLinesOnly				= 3,						// show view with below attributes
	API_AbstractAll					= 4,						// show view with above attributes
	API_CutAll						= 5							// always show walls and columns cut part
} API_ElemDisplayOptionsID;

typedef enum {
	API_Symbolic					= 0,						// symbolic
	API_Projected					= 1,						// projected
	API_Hybrid						= 2 						// hybrid
} API_ElemProjectionModesID;

typedef enum  {
	API_ToFloorPlanRange			= 0,						// show projection to floor plan range
	API_ToAbsoluteLimit				= 1,						// show projection to absolute limit
	API_EntireElement				= 2							// show entire element
} API_ElemViewDepthLimitationsID;

typedef enum {
	APIEdgeTrim_Vertical,
	APIEdgeTrim_Perpendicular,
	APIEdgeTrim_Horizontal,
	APIEdgeTrim_CustomAngle,
	APIEdgeTrim_AlignWithCut
} API_EdgeTrimID;

typedef struct {
	Int32							filler_0;
	API_EdgeTrimID					sideType;
	double							sideAngle;
} API_EdgeTrim;


// =============================================================================
// Arrow
//
// =============================================================================

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

typedef struct {
	API_ArrowID						arrowType;					// arrow type
	bool							begArrow;
	bool							endArrow;
	short							arrowPen;
	double							arrowSize;					// arrow size in mm
} API_ArrowData;


// =============================================================================
// Note
//
// =============================================================================


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

typedef enum {
	API_NoteContent_Measured,
	API_NoteContent_Custom
} API_NoteContentType;

typedef enum {
	APILbl_MiddleAnchor				= 0,
	APILbl_TopAnchor				= 1,
	APILbl_BottomAnchor				= 2,
	APILbl_Underlined				= 3
} API_LblAnchorID;

typedef enum {
	API_Segmented					= 0,
	API_Splinear					= 1,
	API_SquareRoot					= 2							// used only for labels
} API_LeaderLineShapeID;

typedef enum {
	APIJust_Left					= 0,
	APIJust_Center,
	APIJust_Right,
	APIJust_Full
} API_JustID;

typedef struct {
	short							notePen;					// color index
	short							noteFont;					// font index
	API_AttributeIndex				noteLayer; 					// layer index
	double							noteSize;					// float size char height in mm
	double							noteAngle;					// rotation angle (radian)
	Int32							filler_2[8];

	API_Coord						pos;						// real coordinates of left bottom
	char							content[64];				// the text or the autotext
	GS::UniString*					contentUStr;
	API_NoteContentType				contentType;				// 0: measured value 1: custom text
	bool							fixPos;						// manually fixed position
	bool							filler_3;
	unsigned short					faceBits;					// style of text
	bool							opaque;						// has background
	bool							frame;						// has frame
	short							backgroundPen;				// background color index
	short							framePen;					// frame color index
	short							filler_4;
	Int32							filler_5[4];
	bool							useLeaderLine;				// true if note has leader line. In this case, pos and noteangle are ignored
	bool							anchorAtTextEnd;
	short							filler_6[3];
	API_Coord						begC;						// beg Coord of leader line
	API_Coord						midC;						// mid Coord of leader line
	API_Coord						endC;						// end Coord of leader line
	Int32							filler_7;
	short							filler_8;
	short							leaderPen;					// color index of the leader
	API_AttributeIndex				leaderLineType;				// line type index of the leader
	API_LeaderLineShapeID			leaderShape;				// plain/ splinear leader line
	API_ArrowData					arrowData;
	API_LblAnchorID					anchorPoint;				// the anchor point the label's leader is connected to
	API_JustID						just;						// left, center, right
	double							widthFactor;
	double							spacingFactor;
	short							rowAnchor;					// text anchor at first (0) or last row (1) (multiline text)
	unsigned short					effectBits;					// effects of CharStyle
} API_NoteType;


// =============================================================================
// ModelElemStructure
//
// =============================================================================

typedef enum {
	API_BasicStructure,
	API_CompositeStructure,
	API_ProfileStructure
} API_ModelElemStructureType;

typedef struct {
	short							cutFillPen;
	short							cutFillBackgroundPen;
	bool							overrideCutFillPen;
	bool							overrideCutFillBackgroundPen;
	bool							filler_1[2];
} API_PenOverrideType;

typedef struct {
	API_AttributeIndex				attributeIndex;
	bool							overridden;
	bool							filler_1[3];
} API_OverriddenAttribute;

struct API_OverriddenAttributeOrRGB {
	GS::Variant<API_AttributeIndex, API_RGBColor>	attributeStyle;
	bool											overridden;
	bool											filler_1[3];

	API_OverriddenAttributeOrRGB () : 
		attributeStyle (API_AttributeIndex (0)),
		overridden (false)
	{ 
	}
};


// =============================================================================
// Wall
//
// =============================================================================

typedef enum {
	APIWallRefLine_Outside = 0,
	APIWallRefLine_Center,
	APIWallRefLine_Inside,
	APIWallRefLine_CoreOutside,
	APIWallRefLine_CoreCenter,
	APIWallRefLine_CoreInside
} API_WallReferenceLineLocationID;

typedef enum {
	APIWtyp_Normal,												// normal parallel wall
	APIWtyp_Trapez,												// normal trapezoid wall (vertical)
	APIWtyp_Poly												// general polygon
} API_WallTypeID;

#define	APICutElem_Beam				1							// gable is coming from a beam
#define	APICutElem_Ceil				2							// gable is coming from a ceil
#define	APICutElem_Roof				3							// gable is coming from a roof
#define	APICutElem_Shell			4							// gable is coming from a shell

typedef struct {
	double							a;							// plane coefficients relative to the parent element
	double							b;
	double							c;
	double							d;
	double							xb;							// distance of vertical cut planes from local origin
	double							xe;
	double							nx;							// normal vector of vertical cut planes (nz always 0.0)
	double							ny;
	short							cutElem;					// element the gable is generated from  (output only)
	short							filler_1;
	API_AttributeIndex				material;					// material for the cut surface (output only)
	API_Coord						**coords;					// if cut is limited to polygon (output only)
	Int32							**pends;
	API_PolyArc						**parcs;
} API_Gable;

#define	APIWBeam_RefMater			1							// apply Reference side material on horizontal edges
#define	APIWBeam_OppMater			2							// apply Opposite side material on horizontal edges
#define	APIWBeam_HalfLog			4							// start with half log
#define	APIWBeam_QuadricLog			8							// start with quadric log
#define	APIWBeam_Stretched			64							// ???
#define	APIWBeam_RightLog			128							// logs on the right side of the wall
#define	APIWBeam_LeftLog			256							// logs on the left side of the wall

typedef enum {
	APIZRel_Boundary,
	APIZRel_ReduceArea,
	APIZRel_None
} API_ZoneRelID;

typedef struct {
	API_Elem_Head					head;

	short							contPen;					// color index of wall's contour
	short							contPen3D;					// color index of wall's contour in 3D
	API_AttributeIndex				contLtype;					// linetype index of wall's contour
	API_AttributeIndex				belowViewLineType;			// floor plan: linetype of view below
	API_ModelElemStructureType		modelElemStructureType;		//
	API_AttributeIndex				buildingMaterial;			// building material
	API_AttributeIndex				composite;					// composite index
	Int32							sequence;					// sequence
	Int32							filler_0;
	API_PenOverrideType				penOverride;				// pen override
	API_OverriddenAttribute			refMat;						// material of the surface on the ref. line
	API_OverriddenAttribute			oppMat;						// material of the opposite surface
	API_OverriddenAttribute			sidMat;						// material of the side surfaces
	API_AttributeIndex				profileAttr;				// attribute index of the extruded profile
	short							profileType;				// conventional, slanted, trapezoid, polygonal in cross section
	bool							polyCanChange;				// can change polywall corners in case of L and T connections
	bool							materialsChained;			// are surface materials chained?
	bool							flipped;					// the wall is mirrored to the reference line
	bool							filler_1[7];
	API_WallTypeID					type;						// conventional, trapezoid, polygonal
	API_WallReferenceLineLocationID	referenceLineLocation;		// location of the reference line
	double							height;						// height relative to bottom
	double							bottomOffset;				// base height of the wall relative to the floor level
	double							topOffset;					// offset from top floor if top linked
	double							thickness;					// thickness
	double							thickness1;					// thickness of the other end
	double							offset;						// wall's base line's offset from ref. line
	double							offsetFromOutside;			// distance between the reference line and outside face of the wall
	double							logHeight;					// modified beam height
	Int32							beamFlags;					// APIWBeam_TreeTrunk ...
	API_ZoneRelID					zoneRel;					// relation to zones
	char							filler_2[16];
	bool							isAutoOnStoryVisibility;	// story visibility will be automatically recalculated when needed
	bool							inheritEndSurface;			// inherit surface of wall end from adjointing walls
	bool							alignTexture;				// align texture to wall edge lengthwise
	bool							filler_3;
	API_StoryVisibility				visibility;					// story visibility
	API_LinkToSettings				linkToSettings;				// link to story settings
	short							relativeTopStory;			// top linked story (relative to home story), 0 = not top linked
	short							filler_4[3];

	API_Coord						begC;						// start coordinate
	API_Coord						endC;						// end coordinate
	API_Polygon						poly;						// original outline
	Int32							rLinInd;					// index of the refLine beg corner (<0 beg edge)
	Int32							rLinEndInd;					// index of the refLine end
	Int32							refInd;						// index of the refMaterial edge
	Int32							refEndInd;					// index of the refMaterial edge end
	Int32							oppInd;						// index of the oppMaterial edge
	Int32							oppEndInd;					// index of the oppMaterial edge end

	double							angle;
	bool							hasWindow;
	bool							hasDoor;
	bool							filler_5[2];

	Int32							wallConnPriority;			// wall connection priority
	bool							useCompositePriority;		// use the priority of the composite when connecting walls
	bool							filler_6;
	short							aboveViewLinePen;			// floor plan: pen of view above
	API_AttributeIndex				aboveViewLineType;			// floor plan: linetype of view above

	API_ElemDisplayOptionsID		displayOption;				// floor plan display option
	API_ElemViewDepthLimitationsID	viewDepthLimitation;		// floor plan view depth limitation

	double							slantAlpha;					// the (first) angle of the slant - if slanted (trapezoid)
	double							slantBeta;					// the second angle of the slant - if trapezoid

	Int32							filler_8[4];
} API_WallType;


// =============================================================================
// Curtain Wall
//
// =============================================================================

// Curtain Wall Segment

typedef struct {
	API_Polygon						polygon;
	API_Coord						**coords;
	Int32							**pends;
	API_PolyArc						**parcs;
	UInt32							**vertexIDs;
} API_CWContourData;

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

typedef enum {
	APICWSeC_System = 0,
	APICWSeC_Custom
} API_CWSegmentCategoryID;

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

typedef struct {
	API_CWCellCrossingFrameTypeID	crossingFrameType;
	UInt32 							leftPanelID;
	UInt32 							rightPanelID;
	UInt32 							leftFrameID;
	UInt32 							bottomFrameID;
	UInt32 							crossingFrameID;
} API_CWSegmentPatternCellData;

typedef struct {
	API_CWSegmentPatternLogicID		logic;
	API_CWSegmentGridOrigPosTypeID	gridOriginType;
	UInt32 							nPattern;
	UInt32							filler_1;
	double 							*pattern;
	UInt32 							*flexibleIDs;
	UInt32							nFlexibleIDs;
	UInt32 							nDivisions;
	UInt32 							infillPanelID;
	UInt32 							endWithID;
} API_CWSegmentPatternData;

typedef struct {
	API_Elem_Head					head;
	short							pen;
	short							filler_1;
	API_CWSegmentCategoryID			category;
	double							gridAngle;
	API_Coord3D						begC;
	API_Coord3D						endC;
	API_Coord3D						gridOrigin;
	API_Coord3D						arcOrigin;
	bool							negArc;
	bool							filler_2[3];
	API_CWSegmentTypeID				segmentType;
	API_Guid						owner;
	API_Vector3D					extrusion;
	UInt32							contourNum;
	UInt32							patternCellNum;
} API_CWSegmentType;

// Curtain Wall Frame

typedef enum {
	APICWFrObjectType_Invisible = 0,
	APICWFrObjectType_GDL,
	APICWFrObjectType_InvisibleConnectedTurning,
	APICWFrObjectType_InvisibleConnectedStill
} API_CWFrameObjectTypeID;

typedef struct {
	API_Elem_Head					head;
	short							pen;
	short							filler_0;
	API_AttributeIndex				material;
	bool							useOwnMaterial;
	bool							filler_1[3];
	API_AttributeIndex				buildingMaterial;
	API_AttributeIndex				cutLineType;
	short							cutLinePen;
	short							filler_2;
	double							d;							// panel connection hole depth
	double							w;							// panel connection hole width
	double							a1;							// frame contour width 1
	double							a2;							// frame contour width 2
	double							b1;							// frame contour length 1
	double							b2;							// frame contour length 2
	double							angle;
	API_CWFrameObjectTypeID			objectType;					// frame object type
	unsigned short					connPriority;				// connection priority
	UInt32 							classID;					// previously known as category
	API_Guid						owner;						// owner Curtain Wall
	API_Guid						symbolID;					// object identifier
	bool							hasSymbol;
	bool 							deleteFlag;					// category will be deleted on modify event
	bool 							defaultSubElem;				// set as default sub-element
	bool							filler_3;
	UInt32 							segmentID; 					// identifier of containing segment
	API_GridElemID 					cellID;						// identifier of containing cell
	API_Coord 						begRel;						// relative first point in cell
	API_Coord 						endRel;						// relative second point in cell
	API_Coord3D						begC;						// First point of frame
	API_Coord3D						endC;						// Second point of frame
	API_Coord3D						orientation;				// Orientation of frame
	UInt32							joinedCWFramesBegCNum;		// number of frames joined at begC
	UInt32							joinedCWFramesEndCNum;		// number of frames joined at endC
	UInt32							assocCWPanelsNum;			// number of associated panels - one frame border two panels
	Int32							libInd;
	UInt32							auxPanelDirsNum;			// number of additional panel clamping vectors
	Int32							contourID;					// contour ID for contour frames other has invalid value
	GS::uchar_t 					className[256];				// class name
} API_CWFrameType;

// Curtain Wall Panel

typedef enum {
	APICWPaObjectType_Generic = 0,
	APICWPaObjectType_GDL
} API_CWPanelObjectTypeID;

typedef struct {
	API_Elem_Head					head;

	short							pen;
	short							filler_1[3];
	API_OverriddenAttribute			outerSurfaceMaterial;
	API_OverriddenAttribute			innerSurfaceMaterial;
	API_OverriddenAttribute			cutSurfaceMaterial;
	API_AttributeIndex				buildingMaterial;
	API_AttributeIndex				cutLineType;
	short							cutLinePen;
	bool 							deleteFlag;
	bool 							defaultSubElem;				// set as default sub-element
	UInt32							segmentID;					// identifier of containing segment
	API_CWPanelObjectTypeID			objectType;
	double							thickness;
	API_Guid						owner;						// owner Curtain Wall
	API_Guid						symbolID;					// object identifier
	bool							hasSymbol;
	bool							hidden;						// deleted panels remain in the database
	Int32 							libInd;
	UInt32 							classID;					// previously known as category
	UInt32							edgesNum;
	UInt32							gridPolyIDsNum;
	API_Coord3D						centroid;
	GS::uchar_t 					className[256];				// class name
} API_CWPanelType;

typedef GS::HashTable<API_Guid, GS::Array<API_GridElemID>> API_CWPanelGridIDTable;

// Curtain Wall Junction

typedef enum {
	APICWJunClampFrameOrient_NoClamp = 0,
	APICWJunClampFrameOrient_ClampAtBeg,
	APICWJunClampFrameOrient_ClampAtEnd,
	APICWJunClampFrameOrient_ClampAtBothEnds
} API_CWJunctionClampFrameOrientationID;

typedef enum {
	APICWJunC_System = 0,
	APICWJunC_Custom
} API_CWJunctionCategoryID;

typedef struct {
	API_Elem_Head					head;
	short							pen;
	short							filler_1;
	API_CWJunctionCategoryID		category;
	API_Guid						owner;						// owner Curtain Wall
	API_Guid						symbolID;					// object identifier
	bool							hasSymbol;
	bool							flipped;
	bool							filler_2[6];
	UInt32							clampFramesNum;
	UInt32							clampFrameOrientsNum;
	UInt32							clampPanelsNum;
	Int32 							libInd;
	UInt32 							filler_3;
} API_CWJunctionType;

// Curtain Wall Accessory

typedef enum {
	APICWAccC_System = 0,
	APICWAccC_Custom
} API_CWAccessoryCategoryID;

typedef struct {
	API_Elem_Head					head;
	short							pen;
	short							filler_1;
	API_CWAccessoryCategoryID		category;
	API_Guid						owner;						// owner Curtain Wall
	API_Guid						symbolID;					// object identifier
	bool							hasSymbol;
	bool							flipped;
	bool							filler_2[2];
	Int32 							libInd;
	API_Guid						refFrame;					// reference frame
} API_CWAccessoryType;

// Curtain Wall (Main Element)

typedef enum {
	APICW_Boundary_Unknown = 0,
	APICW_Boundary_OutSide,
	APICW_Boundary_Center,
	APICW_Boundary_Inside
} API_CWBoundaryFramePosID;

typedef enum {
	APICW_Placement_AllGridPoints = 0,
	APICW_Placement_Manual
} API_CWPlacementID;

typedef struct {
	API_Elem_Head					head;
	API_ZoneRelID					zoneRel;					// relation to zones
	short							pen;
	short							filler_1;
	double							nominalWidth;
	bool							flipped;
	bool							filler_2[7];
	double							offset;
	double							distanceInside;				// theory border of the curtain wall
	double							distanceOutside;			// theory border of the curtain wall
	API_CWBoundaryFramePosID		boundaryFramePosition;
	API_LinkToSettings				linkToSettings;				// link to story settings
	API_StoryVisibility				visibility;					// story visibility
	bool							isAutoOnStoryVisibility;	// story visibility will be automatically recalculated when needed
	bool							filler_3[3];
	double							storyRelLevel;				// default only member!
	API_ElemDisplayOptionsID		displayOption;				// floor plan display option
	API_ElemProjectionModesID		cutProjectionMode;			// cut projection mode
	API_ElemProjectionModesID		uncutProjectionMode;		// uncut projection mode
	API_ElemProjectionModesID		overheadProjectionMode;		// overhead projection mode
	API_ElemViewDepthLimitationsID	viewDepthLimitation;		// floor plan view depth limitation
	API_AttributeIndex				overheadLineType;
	short							overheadLinePen;
	short							uncutLinePen;
	API_AttributeIndex				uncutLineType;
	API_AttributeIndex				frameCutLineType;
	short							frameCutLinePen;
	short							panelCutLinePen;
	API_AttributeIndex				panelCutLineType;
	bool							useFrameTypesAttributes;
	bool							usePanelTypesAttributes;
	bool							filler_4[2];
	API_PenOverrideType				penOverride;				// pen override
	API_CWPlacementID				placementMethod;			// default only member!
	Int32							filler_5;
	API_CWSegmentType				segmentData;				// default segment data
	API_CWFrameType					cornerFrameData;			// default corner frame data
	API_CWFrameType					boundaryFrameData;			// default boundary frame data
	API_CWJunctionType				junctionData;				// default junction data
	API_CWAccessoryType				accessoryData; 				// default accessory data
	double							angle;
	double							height;
	API_Polygon						polygon;					// corners of the CW
	API_Tranmat						planeMatrix;				// describes the baseplane of the CW
	double							planeOffset;				// offset of the real basepoly from the baseplane
	UInt32							nSegments;					// number of segments
	UInt32							nFrames;					// number of frames
	UInt32 							nFrameDefaults;				// number of custom frame classes
	UInt32							nPanels;					// number of panels
	UInt32							nPanelDefaults; 			// number of panel classes
	UInt32							nJunctions;					// number of junctions
	UInt32							nAccessories;				// number of accessories
	UInt32							filler_6;
} API_CurtainWallType;

// =============================================================================
// AssemblySegment
//
// =============================================================================
typedef enum {
	APIAssemblySegment_Fixed		= 0,
	APIAssemblySegment_Proportional	= 1,
} API_AssemblySegmentLengthTypeID;

typedef struct {
	API_ModelElemStructureType		modelElemStructureType;
	API_AttributeIndex				buildingMaterial;
	bool							circleBased;
	char							filler_0[3];
	API_AttributeIndex				profileAttr;
	short							profileType;
	bool							isHomogeneous;
	char							filler_1[5];
	double							nominalWidth;
	double							nominalHeight;
	bool							isWidthAndHeightLinked;
	char							filler_2[7];
	double							endWidth;
	double							endHeight;
	bool							isEndWidthAndHeightLinked;
	char							filler_3[7];
	double							relativeHomeStoryLevel;
} API_AssemblySegmentData;

typedef struct {
	API_AssemblySegmentLengthTypeID	lengthType;
	char							filler_0[4];
	double							fixedLength;
	double							lengthProportion;
} API_AssemblySegmentSchemeData;

typedef struct {
	UInt32							segmentIndex;
	char							filler_0[4];
	ProfileVectorImage				*customOrigProfile;
	ProfileVectorImage				*stretchedProfile;
} API_AssemblySegmentProfileData;

typedef enum {
	APIAssemblySegmentCut_Horizontal	= 0,
	APIAssemblySegmentCut_Vertical		= 1,
	APIAssemblySegmentCut_Custom		= 2
} API_AssemblySegmentCutTypeID;

typedef struct {
	API_AssemblySegmentCutTypeID	cutType;
	char							filler_0[4];
	double							customAngle;
} API_AssemblySegmentCutData;

// =============================================================================
// Column
//
// =============================================================================

#define APICSect_Normal				0x0000						// normal upright column
#define	APICSect_Poly				0x0001						// extruded column from polygon

typedef enum {
	APIVeneer_Core		= 0,
	APIVeneer_Finish	= 1,
	APIVeneer_Other		= 2
} API_VeneerTypeID;

typedef struct {
	API_Elem_Head						head;
	API_Guid							owner;
	API_AssemblySegmentData				assemblySegmentData;
	API_OverriddenAttribute				extrusionSurfaceMaterial;
	API_OverriddenAttribute				endsMaterial;
	bool								materialsChained;
	char								filler_0[3];
	API_AttributeIndex					venBuildingMaterial;
	API_VeneerTypeID					venType;
	char								filler_1[4];
	double								venThick;
} API_ColumnSegmentType;

typedef struct {
	API_Elem_Head						head;

	short								corePen;					// color index of core
	char								filler_0[6];
	API_PenOverrideType					penOverride;				// pen override
	short								belowViewLinePen;
	char								filler_1[2];
	API_AttributeIndex					belowViewLineType;			// floor plan: linetype of view below
	API_AttributeIndex					contLtype;					// line type index of core
	bool								wrapping;					// wall wrapping
	char								filler_2[3];
	API_ZoneRelID						zoneRel;					// relation to zones
	short								coreSymbolType;				// floor plan Symbol Type [1:Plain, 2:Slash, 3:X, 4:Crosshair]
	short								coreAnchor;					// anchor point of core
	double								height;						// column height
	double								bottomOffset;				// column base level relative to the floor
	double								topOffset;					// offset from top floor if top linked
	API_AttributeIndex					venLineType;				// veneer line type index
	short								venLinePen;					// color index of column veneer line
	short								coreSymbolPen;
	double								coreSymbolPar1;				// first param of CrossCore type
	double								coreSymbolPar2;				// second param of CrossCore type
	API_StoryVisibility					visibility;					// story visibility
	API_LinkToSettings					linkToSettings;				// link to story settings
	short								relativeTopStory;			// top linked story (relative to home story), 0 = not top linked
	char								filler_3[2];
	API_AttributeIndex					hiddenLineType;				// Hidden Lines
	short								hiddenLinePen;				// Hidden Line Pen
	char								filler_4[2];

	API_Coord							origoPos;
	double								axisRotationAngle;

	API_AttributeIndex					aboveViewLineType;			// linetype of view above
	short								aboveViewLinePen;			// pen of view above

	bool								isAutoOnStoryVisibility;	// story visibility will be automatically recalculated when needed

	bool								isSlanted;					// slanted column
	bool								isFlipped;					// flipped column
	char								filler_5[7];
	double								slantAngle;					// slant angle
	double								slantDirectionAngle;		// angle of slant direction

	API_ElemDisplayOptionsID			displayOption;				// floor plan display option
	API_ElemViewDepthLimitationsID		viewDepthLimitation;		// floor plan view depth limitation

	UInt32								nCuts;
	UInt32								nSegments;
	UInt32								nSchemes;
	UInt32								nProfiles;

	bool 								useCoverFill;
	bool 								useCoverFillFromSurface;
	bool 								coverFillOrientationComesFrom3D;
	char								filler_6;
	API_AttributeIndex					coverFillType;
	short 								coverFillForegroundPen;
	short 								coverFillBackgroundPen;
	char								filler_7[4];
	API_CoverFillTransformationTypeID 	coverFillTransformationType;
	char								filler_8[4];
	API_CoverFillTransformation 		coverFillTransformation;
} API_ColumnType;


// =============================================================================
// Beam
//
// =============================================================================

#define APIBSect_Normal				0x0000						// normal upright parallel sided wall
#define	APIBSect_Poly				0x0001						// extruded wall from polygon

typedef struct {
	API_Elem_Head					head;
	API_Guid						owner;
	API_AssemblySegmentData			assemblySegmentData;
	API_OverriddenAttribute			leftMaterial;
	API_OverriddenAttribute			topMaterial;
	API_OverriddenAttribute			rightMaterial;
	API_OverriddenAttribute			bottomMaterial;
	API_OverriddenAttribute			endsMaterial;
	bool							materialsChained;
	char							filler_0[7];
} API_BeamSegmentType;

typedef enum {
	APIBHole_Rectangular,
	APIBHole_Circular
} API_BHoleTypeID;

typedef struct {
	API_BHoleTypeID					holeType;					// type of the hole (rectangle / circle)
	bool							holeContureOn;
	bool							filler_1;
	short							filler_2;
	Int32							holeID;						// ID of the hole, unique in the beam
	Int32							filler_3;
	double							centerx;					// 'x' location of the hole's center relative to the beam
	double							centerz;					// 'z' location of the hole's center relative to the beam
	double							width;						// width of the hole
	double							height;						// height of the hole (effective only for the rectangle type)
} API_Beam_Hole;


typedef enum {
	APIBeamLineShowAlways	= 0,
	APIBeamLineHideAlways	= 1,
	APIBeamLineByMVO = 2
} API_BeamVisibleLinesID;

typedef enum {
	API_StraightBeam			= 0,
	API_HorizontallyCurvedBeam	= 1,
	API_VerticallyCurvedBeam	= 2
} API_BeamShapeTypeID;

typedef struct {
	API_Elem_Head						head;

	short								aboveViewLinePen;			// floor plan: pen of view above
	char								filler_0[2];
	API_AttributeIndex					aboveViewLineType;			// floor plan: line type of view below
	API_AttributeIndex					refLtype;					// linetype index of the reference line
	short								refPen;						// color index of the reference line
	short								cutContourLinePen;			// beam cut contour line color
	API_AttributeIndex					cutContourLineType;			// beam cut contour line type
	Int32								sequence;					// sequence
	API_PenOverrideType					penOverride;				// pen override
	API_StoryVisibility					visibility;					// story visibility
	API_LinkToSettings					linkToSettings;				// link to story settings
	API_BHoleTypeID						holeType;					// default hole shape
	bool								holeContureOn;				// default hole contour on plan
	bool								isAutoOnStoryVisibility;	// story visibility will be automatically recalculated when needed
	char								filler_1[6];
	double								holeWidth;					// default width of the holes
	double								holeHeight;					// default height of the holes (effective only for the rectangle type)
	double								holeLevel;					// default level of the holes
	double								offset;						// beam ref.line offset from the center
	double								level;						// base height of the beam relative to the floor level
	API_BeamVisibleLinesID				showContourLines;			// Show Contour Lines
	API_BeamVisibleLinesID				showReferenceAxis;			// Show Reference Axis
	API_Coord							begC;						// begin point of the beam reference line
	API_Coord							endC;						// end point of the beam reference line
	double								curveAngle;					// angle parameter of the curved beam
	double								verticalCurveHeight;		// curve height of the vertical curved beam
	API_AttributeIndex					hiddenLineType;				// Hidden Lines
	short								hiddenLinePen;				// Hidden Line Pen
	short								anchorPoint;
	API_AttributeIndex					belowViewLineType;			// floor plan: line type of view below
	short								belowViewLinePen;			// floor plan: pen of view below
	bool								isFlipped;					// Is the Beam mirrored? Applies to profiled Beams only.
	bool								isSlanted;					// slanted beam
	double								slantAngle;					// slant angle
	double								profileAngle;				// twisted profile
	API_BeamShapeTypeID					beamShape;
	API_ElemDisplayOptionsID			displayOption;				// floor plan display option
	API_ElemViewDepthLimitationsID		viewDepthLimitation;		// floor plan view depth limitation
	API_ElemProjectionModesID			uncutProjectionMode;
	API_ElemProjectionModesID			overheadProjectionMode;
	UInt32								nSegments;
	UInt32								nCuts;
	UInt32								nSchemes;
	UInt32								nProfiles;

	bool 								useCoverFill;
	bool 								useCoverFillFromSurface;
	bool 								coverFillOrientationComesFrom3D;
	char								filler_2;
	API_AttributeIndex					coverFillType;
	short 								coverFillForegroundPen;
	short 								coverFillBackgroundPen;
	API_CoverFillTransformationTypeID 	coverFillTransformationType;
	char								filler_3[4];
	API_CoverFillTransformation 		coverFillTransformation;
} API_BeamType;


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

typedef struct {
	API_VerticalLinkID				linkType;
	short							filler_1;
	short							linkValue;
} API_VerticalLink;

typedef struct {												// common part of windows, doors and skylights
	short							pen;						// color index
	short							filler_0;
	API_AttributeIndex				ltypeInd;					// line type index
	API_AttributeIndex				mat;						// material index
	API_AttributeIndex				sectFill;
	short							sectFillPen;
	short							sectBGPen;
	short							sectContPen;
	short							filler_1;
	API_AttributeIndex				cutLineType;				// linetype of cut lines
	API_AttributeIndex				aboveViewLineType;			// linetype of view above
	short							aboveViewLinePen;			// pen of view above
	short							belowViewLinePen;			// pen of view below
	API_AttributeIndex				belowViewLineType;			// linetype of view below
	bool							useObjPens;
	bool							useObjLtypes;
	bool							useObjMaterials;
	bool							useObjSectAttrs;
	bool							filler_2[4];

	double							width;						// width of the opening
	double							height;						// vertical size of the opening
	double							subFloorThickness;			// subfloor thickness (parapet correction)
	char							filler_3[16];

	Int32							libInd;						// index to the symbol in the library
	API_VerticalLink				verticalLink;
	bool						    reflected;					// true if mirrored to y axis
	bool							oSide;						// true if mirrored to x axis
	bool							refSide;					// true if mirrored to x axis same as oSide
	bool							wallCutUsing;				// true if the window inherits the gables of the owning wall
	bool							filler_4[4];
	GS::Int64						lookId;
	API_Guid						markGuid;					// guid of the dimension marker symbol

	API_ElemDisplayOptionsID		displayOption;				// floor plan display option
	Int32							filler_5;
} API_OpeningBaseType;


// -----------------------------------------------------------------------------
// Window/Door
// -----------------------------------------------------------------------------

#define	APIHoleAnchor_BegFix		-1
#define	APIHoleAnchor_CenterFix		0
#define	APIHoleAnchor_EndFix		1

typedef enum {
	API_WDAssociativeToWall			= 0,
	API_WDVertical					= 1
} API_WindowDoorDirectionTypes;

typedef enum {
	APIWDRevealDepth_Side				= 0,
	APIWDRevealDepth_Core				= 1
} API_WindowDoorRevealDepthLocationID;

typedef struct {
	API_Elem_Head						head;

	API_OpeningBaseType					openingBase;				// common with API_SkyLightType

	API_WindowDoorRevealDepthLocationID	revealDepthLocation;		// reveal depth location (side or core)
	double								revealDepthOffset;			// user defined inset from clicked side of wall or core
	double								revealDepthFromSide;		// calculated inset from the clicked side of the wall
	double								jambDepthHead;				// inset on top
	double								jambDepthSill;				// inset on bottom
	double								jambDepth;					// inset on left
	double								jambDepth2;					// inset on right
	bool								reveal;						// true if window has reveal
	bool								filler_1[7];

	API_Guid							owner;						// reference to the container wall element
	double								objLoc;						// location of the center of the window from the starting point of the 'owner' wall
	double								lower;						// parapet height
	API_Coord							startPoint;					// start point if the wall is polygonal
	API_Coord							dirVector;					// direction vector if the wall is polygonal
	API_WindowDoorDirectionTypes		directionType;				// direction type in 3D/Section
	short								fixPoint;					// APIHoleAnchor_BegFix, APIHoleAnchor_CenterFix, APIHoleAnchor_EndFix
	short								filler_2;
} API_WindowType, API_DoorType;


// -----------------------------------------------------------------------------
// Skylight
// -----------------------------------------------------------------------------

typedef enum {
	APISkylightFixMode_Horizontal,
	APISkylightFixMode_Vertical
} API_SkylightFixModeID;

typedef enum {
	APISkylightAnchor_BC			= 0,						// bottom center anchor
	APISkylightAnchor_BL			= 1,						// bottom left anchor
	APISkylightAnchor_BR			= 2,						// bottom right anchor
	APISkylightAnchor_TC			= 3,						// top center anchor
	APISkylightAnchor_TL			= 4,						// top left anchor
	APISkylightAnchor_TR			= 5							// top right anchor
} API_SkylightAnchorID;

typedef struct {
	API_Elem_Head					head;

	API_OpeningBaseType				openingBase;				// common with API_WindowType, API_DoorType

	API_Guid						owner;						// reference to the container roof/shell element
	UInt32							vertexID;					// for polyroofs the ID of the vertex of the pivot polygon
	API_SkylightFixModeID			fixMode;					// vertical or horizontal constraint to keep during roof changes
	API_SkylightAnchorID			anchorPoint;				// object anchor point identifier
	API_Coord						anchorPosition;				// the global XY coordinate of the anchor point
	double							anchorLevel;				// the global Z coordinate of the anchor point
	double							azimuthAngle;				// rotation angle measured clockwise in the horizontal plane
	double							elevationAngle;				// elevation angle of the roof at the insert position
} API_SkylightType;


// =============================================================================
// Object/Lamp
//
// =============================================================================

typedef struct {
	API_Elem_Head					head;

	short							pen;						// color index
	short							filler_0;
	API_AttributeIndex				ltypeInd;					// line type index
	API_AttributeIndex				mat;						// material index
	API_AttributeIndex				sectFill;
	short							sectFillPen;
	short							sectBGPen;
	short							sectContPen;
	short							filler_1;
	bool							useObjPens;
	bool							useObjLtypes;
	bool							useObjMaterials;
	bool							reflected;					// default symbol is reflected
	bool							useXYFixSize;
	bool							useObjSectAttrs;
	short							fixPoint;					// index-1 of hotspot to keep fixed
	double							angle;						// rotation angle /radian/
	double							level;						// base height from FloorLevel
	double							xRatio;
	double							yRatio;						// multiplication factor in x,y directions
	API_Coord						offset;						// offset of the symbol's origin from insertion point
	Int32							fixedAngle;					// use fix angle
	char							filler_2[12];
	API_RGBColor					lightColor;
	API_StoryVisibility				visibility;					// story visibility
	API_LinkToSettings				linkToSettings;				// link to story settings
	bool							lightIsOn;					// light is on/off
	bool							isAutoOnStoryVisibility;	// "All Relevant Stories"
	bool							filler_3[6];
	Int32							filler_4;

	API_ElemType					ownerType;					// type of the owner element of the object
	API_Guid						owner;						// guid of the owner element of the object
	Int32							libInd;						// index to the symbol in the library
	Int32							filler_5;

	API_Coord						pos;						// position of the origin of the object
	bool							filler_6[4];
	GS::Int64						lookId;
	Int32							filler_7[3];
} API_ObjectType, API_LampType;


// =============================================================================
// Slab
//
// =============================================================================

typedef enum {
	APISlabRefPlane_Top = 0,
	APISlabRefPlane_CoreTop,
	APISlabRefPlane_CoreBottom,
	APISlabRefPlane_Bottom
} API_SlabReferencePlaneLocationID;

typedef struct {
	API_Elem_Head						head;

	short								pen;						// color index of slab's contour
	short								filler_0;
	API_AttributeIndex					ltypeInd;					// line type index of slab's contour
	API_ModelElemStructureType			modelElemStructureType;		// model elem structure
	API_AttributeIndex					buildingMaterial;			// slab building material
	API_AttributeIndex					composite;					// slab composite index
	short								filler_1;
	short								sectContPen;
	API_PenOverrideType					penOverride;				// pen override
	API_OverriddenAttribute				topMat;
	API_OverriddenAttribute				sideMat;
	API_OverriddenAttribute				botMat; 					// material
	bool								materialsChained;			// are surface materials chained?
	bool								filler_2[7];
	double								thickness;					// thickness
	double								level;						// reference plane level of ceiling relative to FloorLevel
	API_AttributeIndex					hiddenContourLineType;		// Hidden Contour Lines
	short								hiddenContourLinePen;		// Hidden Contour Line Pen
	short								filler_3;
	char								filler_4[16];
	API_AttributeIndex					sectContLtype;				// line type of slab's cut contour
	API_SlabReferencePlaneLocationID	referencePlaneLocation;		// reference plane location (Top, Core Top, Core Bottom, Bottom)
	bool								useFloorFill;				// use cover fill
	bool								filler_5[7];

	API_StoryVisibility					visibilityCont;				// story visibility (Contour)
	API_StoryVisibility					visibilityFill;				// story visibility (Fill)
	API_LinkToSettings					linkToSettings;				// link to story settings
	short								floorFillPen;				// color index of floorplan fill
	short								floorFillBGPen;				// color index of floorplan fill background
	API_AttributeIndex					floorFillInd;				// floorplan fill index
	bool								use3DHatching;				// floorplan fill from material
	bool								filler_6[3];
	double								offsetFromTop;				// offset between reference plane's level and top plane's level

	API_Polygon							poly;						// polygon of the slab
	Int32								filler_7[4];
	API_HatchOrientation				hatchOrientation;
	short								filler_8[4];

	bool								filler_9[8];
} API_SlabType;


// =============================================================================
// Roof/Shell
//
// =============================================================================

typedef enum {
	APIShellBaseCutBody_Editable,
	APIShellBaseCutBody_ContoursDown,
	APIShellBaseCutBody_PivotLinesDown,
	APIShellBaseCutBody_UpwardsExtrusion,
	APIShellBaseCutBody_DownwardsExtrusion
} API_ShellBaseCutBodyTypeID;

typedef enum {
	APIShellBase_SegmentsByCircle,
	APIShellBase_SegmentsByArc
} API_ShellBaseSegmentTypeID;

typedef struct {
	short							pen;						// contour pen
	short							filler_0;
	API_AttributeIndex				ltypeInd;					// contour line type
	API_ModelElemStructureType		modelElemStructureType;		// model elem structure type
	API_AttributeIndex				buildingMaterial;			// building material
	API_AttributeIndex				composite;					// composite
	short							filler_1[2];
	API_PenOverrideType				penOverride;				// pen override
	API_AttributeIndex				sectContLtype;				// cut contour line type
	short							sectContPen;				// cut contour line pen
	short							floorFillPen;				// floorplan fill pen
	API_AttributeIndex				floorFillInd;				// floorplan fill index
	short							floorFillBGPen;				// floorplan fill background pen
	short							aboveViewLinePen;			// pen of view above
	API_AttributeIndex				aboveViewLineType;			// line type of view above
	short							filler_2[2];

	bool							useFloorFill;				// use cover fill
	bool							use3DHatching;				// cover fill use fill of surface material
	bool							useFillLocBaseLine;			// align cover fill with pitch
	bool							useSlantedFill;				// distort cover fill with pitch
	Int32							filler_3[8];

	API_HatchOrientation			hatchOrientation;			// orientation and distortion of cover fill

	char							filler_4[16];

	API_OverriddenAttribute			topMat;						// top surface material
	API_OverriddenAttribute			sidMat;						// default edge material
	API_OverriddenAttribute			botMat;						// bottom surface material

	bool							materialsChained;			// are surface materials chained?
	bool							isAutoOnStoryVisibility;	// story visibility will be automatically recalculated when needed
	API_StoryVisibility				visibilityCont;				// story visibility (Contour)
	API_StoryVisibility				visibilityFill;				// story visibility (Fill)
	API_LinkToSettings				linkToSettings;				// link to story settings

	bool							filler_5[12];
	Int32							filler_6;

	double							level;						// base height
	double							thickness;					// roof/shell thickness
	API_EdgeTrim					edgeTrim;					// default edge trim

	API_ShellBaseCutBodyTypeID		cutBodyType;				// extend roof/shell body for connections

	API_ElemDisplayOptionsID		displayOption;				// floor plan display option
	API_ElemViewDepthLimitationsID	viewDepthLimitation;		// floor plan view depth limitation

	Int32							compositionPriority;
} API_ShellBaseType;


// -----------------------------------------------------------------------------
// Roof
// -----------------------------------------------------------------------------

typedef enum {
	API_PlaneRoofID,
	API_PolyRoofID
} API_RoofClassID;

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

typedef struct {
	double							levelHeight;
	double							levelAngle;					// angle in radians
} API_RoofLevelData;

typedef enum {
	API_OffsetOverhang	= 1,
	API_ManualOverhang	= 2
} API_RoofOverHangTypeID;

typedef enum {
	APIPolyRoof_SegmentAngleTypeSloped,
	APIPolyRoof_SegmentAngleTypeGable
} API_PolyRoofSegmentAngleTypeID;

typedef struct {
	Int32	method;
	UInt32	flags;
} API_Wrapping;

typedef struct {
	API_Wrapping					wrapping;					// texturing method
	API_Coord3D						c0;
	API_Coord3D						c1;
	API_Coord3D						c2;
	API_Coord3D						c3;
} API_LocalCoordsType;											// texturing method and its parameters

typedef struct {
	API_LocalCoordsType				*data;
	Int32							nItems;
} API_LocalCoordsData;

typedef struct {
	double							angle;						// angle in radians
	API_LocalCoordsData				lcoo;
	API_AttributeIndex				topMaterial;
	API_AttributeIndex				bottomMaterial;
	API_AttributeIndex				coverFillType;
	Int32							filler_1;
	double							eavesOverhang;
	API_PolyRoofSegmentAngleTypeID	angleType;
} API_RoofSegmentData;

typedef struct {
	UInt32							pivotEdgeUnId;				// unique identifier of the edge in the pivot polygon (output parameter only)
	Int32							filler1;
	API_RoofSegmentData				*levelEdgeData;
	Int32							nLevelEdgeData;
	API_ShellBaseSegmentTypeID		segmentType;
	Int32							segmentsByArc;
	Int32							segmentsByCircle;
} API_PivotPolyEdgeData;

typedef struct {
	double							angle;						// angle of the Roof Plane
	API_Polygon						poly;
	API_Sector						baseLine;
	bool							posSign;					// sign of the Vectorial product of baseline and elevation indicator Point
	bool							filler_1[7];
} API_PlaneRoofData;

typedef struct {
	API_RoofLevelData				levelData[16];				// angle and base height of the roof levels
	short							levelNum;					// number of roof levels [1..16]
	short							filler_1;

	API_RoofOverHangTypeID			overHangType;				// eaves overhang method
	double							eavesOverHang;				// eaves overhang offset value

	API_ShellBaseSegmentTypeID		segmentType;				// curve resolution method
	Int32							segmentsByArc;				// curve resolution value by arc
	Int32							segmentsByCircle;			// curve resolution value by circle
	bool							fitSkylightToCurve;			// fit skylights to curve
	bool							filler_2[3];

	API_Polygon						pivotPolygon;				// pivot polygon
	API_Polygon						contourPolygon;				// contour polygon
} API_PolyRoofData;

typedef struct {
	API_Elem_Head					head;

	API_RoofClassID					roofClass;					// single-plane or multi-plane roof
	Int32							filler_1;

	API_ShellBaseType				shellBase;					// common roof parameters

	union {
		API_PlaneRoofData			planeRoof;					// single-plane geometry data (used with API_PlaneRoofID)
		API_PolyRoofData			polyRoof;					// multi-plane geometry data (used with API_PolyRoofID)
	} u;
} API_RoofType;


// -----------------------------------------------------------------------------
// Shell
// -----------------------------------------------------------------------------

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

typedef enum {
	APIMorphingRule_Paired,
	APIMorphingRule_Smooth
} API_MorphingRuleID;

typedef enum {
	API_ExtrudedShellID,
	API_RevolvedShellID,
	API_RuledShellID
} API_ShellClassID;

typedef struct {
	API_EdgeTrim					edgeTrim;
	API_OverriddenAttribute			sideMaterial;
	API_ShellBaseContourEdgeTypeID	edgeType;
} API_ContourEdgeData;

typedef struct {
	API_Coord						**coords;
	Int32							**pends;
	API_PolyArc						**parcs;
	UInt32							**vertexIDs;
	UInt32							**edgeIDs;
	bool							**bodyFlags;
} API_ShellShapeData;

typedef struct {
	API_Polygon						poly;
	API_Coord						**coords;
	Int32							**pends;
	API_PolyArc						**parcs;
	UInt32							**vertexIDs;
	UInt32							**edgeIDs;
	UInt32							**contourIDs;
	API_ContourEdgeData				*edgeData;
	API_Tranmat						plane;
	double							height;
	UInt32							id;
} API_ShellContourData;

typedef struct {
	double							slantAngle;					// relative to the plane (radian)
	double							shapePlaneTilt;				// relative to extrusion vector
	double							begPlaneTilt;				// relative to extrusion vector
	double							endPlaneTilt;				// relative to extrusion vector

	API_Polygon						shellShape;					// polyline with edge flags to be extruded
	API_Coord3D						begC;
	API_Vector3D					extrusionVector;
	API_Vector						shapeDirection;
	API_ContourEdgeData				begShapeEdgeData;			// one edge data for all edges of the "beg" shape polygon
	API_ContourEdgeData				endShapeEdgeData;			// one edge data for all edges of the "end" shape polygon
	API_ContourEdgeData				extrudedEdgeDatas[2];		// for edges of the extruded first & last shape points
} API_ExtrudedShellData;

typedef struct {
	double							slantAngle;					// relative to the plane (radian)
	double							revolutionAngle;			// Angle of view
	double							distortionAngle;			// Angle of shear
	bool							segmentedSurfaces;
	bool							filler_1[3];
	API_ShellBaseSegmentTypeID		segmentType;
	Int32							segmentsByArc;
	Int32							segmentsByCircle;

	API_Polygon						shellShape;					// polyline with edge flags to be revolved
	API_Tranmat						axisBase;					// CoordSystem of axis
	API_Vector						distortionVector;			// Direction of shear (in axisBase x-y plane). Aux. member for SetSlantAngle ???
	API_ContourEdgeData				begShapeEdgeData;			// one edge data for all edges of the "beg" shape polygon
	API_ContourEdgeData				endShapeEdgeData;			// one edge data for all edges of the "end" shape polygon
	API_ContourEdgeData				revolvedEdgeDatas[2];		// for edges of the revolved first & last shape points
	double							begAngle;					// Begin angle
	bool							filler_2[8];
} API_RevolvedShellData;

typedef struct {
	API_Polygon						shellShape1;				// polyline with edge flags to be revolved
	API_Tranmat						plane1;						// plane, where shape1 is defined
	API_Polygon						shellShape2;				// polyline with edge flags to be revolved
	API_Tranmat						plane2;						// plane, where shape2 is defined
	API_ContourEdgeData				begShapeEdgeData;			// one edge data for all edges of the "beg" shape polygon
	API_ContourEdgeData				endShapeEdgeData;			// one edge data for all edges of the "end" shape polygon
	API_ContourEdgeData				ruledEdgeDatas[2];			// for edges of the connected first & last shape points
	API_MorphingRuleID				morphingRule;				// morphing method for shape generation: paired segments, smooth
	bool							filler_1[4];
} API_RuledShellData;

typedef struct {
	API_Elem_Head					head;

	API_ShellClassID				shellClass;
	Int32							filler_1;

	API_ShellBaseType				shellBase;

	API_Tranmat						basePlane;
	bool							isFlipped;
	bool							hasContour;
	short							filler_2;
	UInt32							numHoles;
	API_ShellBaseContourEdgeTypeID	defEdgeType;
	Int32							filler_3;

	union {
		API_ExtrudedShellData		extrudedShell;
		API_RevolvedShellData		revolvedShell;
		API_RuledShellData			ruledShell;
	} u;
} API_ShellType;


// -----------------------------------------------------------------------------
// Morph
// -----------------------------------------------------------------------------


typedef enum {
	APITextureProjectionType_Invalid		= 0,
	APITextureProjectionType_Planar			= 1,
	APITextureProjectionType_Default		= 2,
	APITextureProjectionType_Cylindric		= 3,
	APITextureProjectionType_Spheric		= 4,
	APITextureProjectionType_Box			= 5
} API_TextureProjectionTypeID;

typedef enum {
	APIMorphBodyType_SurfaceBody,
	APIMorphBodyType_SolidBody
} API_MorphBodyTypeID;

typedef enum {
	APIMorphEdgeType_SoftHiddenEdge,
	APIMorphEdgeType_HardHiddenEdge,
	APIMorphEdgeType_HardVisibleEdge
} API_MorphEdgeTypeID;

typedef struct {
	API_Elem_Head						head;

	char								filler_1[16];					// user information
	bool								isAutoOnStoryVisibility;		// calculate the per story visibility from vertical data
	bool								filler_2[7];
	API_StoryVisibility					showContour;					// show on given floors
	API_StoryVisibility					showFill;						// show on given floors

	API_LinkToSettings					linkToSettings;					// link to settings

	API_ElemDisplayOptionsID			displayOption;					// floor plan display options
	API_ElemViewDepthLimitationsID		viewDepthLimitation;			// floor plan view depth limitation
	API_AttributeIndex					buildingMaterial;				// building material
	API_PenOverrideType					penOverride;					// pen override
	API_AttributeIndex					cutLineType;					// line type of cut contour
	short								cutLinePen;						// pen of contour
	short								uncutLinePen;					// line pen of contour
	API_AttributeIndex					uncutLineType;					// line type of contour
	API_AttributeIndex					overheadLineType;				// floor plan only, line type of view above
	short								overheadLinePen;				// floor plan only, pen of view above
	bool								useCoverFillType;				// use floorplan fill
	bool								outlineContourDisplay;			// Outline Contour Display
	API_AttributeIndex					coverFillType;					// floor plan fill type
	short								coverFillPen;					// floor plan fill pen
	short								coverFillBGPen;					// floor plan fill background pen
	bool								use3DHatching;					// floor plan fill from material
	bool								filler_3[3];
	Int32								filler_4[8];
	API_HatchOrientation				coverFillOrientation;			// floor plan local origin type of fill
	bool								useDistortedCoverFill;			// show hatching as projected onto a plane
	bool								filler_5[5];
	API_OverriddenAttribute				material;						// material of non-customized surfaces
	API_TextureProjectionTypeID			textureProjectionType;			// projection type of texture
	Int32								filler_6[21];
	API_Coord3D							textureProjectionCoords[4];		// texture projection coordinate system

	double								level;							// base height of the shape relative to the floor level
	API_MorphBodyTypeID					bodyType;						// type of body (Solid, Surface)
	API_MorphEdgeTypeID					edgeType;						// type of edge (Soft, Sharp)
	bool								castShadow;						// body casts shadow
	bool								receiveShadow;					// body receives shadow
	bool								filler_7[6];
	Int32								filler_8[18];
	API_Tranmat							tranmat;						// transformation of the body (the origin is at (0,0))
	bool								filler_9[8];
} API_MorphType;


// =============================================================================
// Mesh
//
// =============================================================================

#define APIRidge_AllSharp			0
#define APIRidge_AllSmooth			1
#define APIRidge_UserSharp			2

typedef struct {
	API_Coord3D						c;
	Int32							vertexID;					// vertex ID unique in the given mesh
	Int32							filler_0;
} API_MeshLevelCoord;

typedef struct {
	Int32							nCoords; 					// number of vertexes
	Int32							nSubLines;					// number of sublines including the first one
} API_MeshLevel;

typedef struct {
	API_Elem_Head					head;

	short							contPen;					// color index of mesh's contour
	short							levelPen;					// color index of mesh's contour
	API_AttributeIndex				ltypeInd;					// line type index of mesh's contour
	API_AttributeIndex				buildingMaterial;			// building material
	short							filler_1[2];
	API_PenOverrideType				penOverride;				// pen override
	short							sectContPen;
	API_OverriddenAttribute			topMat;
	API_OverriddenAttribute			sideMat;
	API_OverriddenAttribute			botMat;
	bool							materialsChained;			// are surface materials chained?
	bool							filler_2;
	bool							useFloorFill;				// use cover fill
	char							smoothRidges;				// smooth ridges?
	short							showLines;					// hide sec. lines/show everything
	short							skirt;						// skirt yes/no bottom/no
	short							filler_3[2];
	double							level;						// height of mesh relative to FloorLevel
	double							skirtLevel;					// level of the bottom/top of the skirt
	char							filler_4[16];
	API_StoryVisibility				visibilityCont;				// story visibility (Contour)
	API_StoryVisibility				visibilityFill;				// story visibility (Fill)
	API_LinkToSettings				linkToSettings;				// link to story settings
	short							floorFillPen;				// color index of floorplan fill
	short							floorFillBGPen;				// color index of floorplan fill background
	API_AttributeIndex				floorFillInd;				// floorplan fill index
	bool							useLocalOrigo;				// floorplan fill (used local origo)
	bool							use3DHatching;				// floorplan fill from material
	short							filler_5;

	API_Polygon						poly;						// the polygon of the mesh
	Int32							filler_6;
	API_MeshLevel					levelLines;
	API_Coord						locOrigo;					// base coordinate of floorplan fill reference vector if linked to the element
	double							fillAngle;					// angle of floorplan fill reference vector if linked to the element
	Int32							filler_7[2];
	bool							filler_8[8];
} API_MeshType;


// =============================================================================
// Dimension
//
// =============================================================================

typedef enum {
	APIWtn_None,
	APIWtn_Small,
	APIWtn_Large,
	APIWtn_Fix
} API_WitnessID;

typedef enum {
	APIApp_Normal,
	APIApp_Cumu,
	APIApp_CumuSv,
	APIApp_Elev
} API_AppearID;

typedef enum {
	APIPos_Above,
	APIPos_In,
	APIPos_Below
} API_TextPosID;

typedef enum {
	APIDir_Parallel,
	APIDir_Horizontal,
	APIDir_Vertical,
	APIDir_General,
	APIDir_Radial,
	APIDir_ArcDim,
	APIDir_Perpendicular
} API_DirID;

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

typedef enum {
	APIDimOrigin_ProjectZero,
	APIDimOrigin_RefLevel1,
	APIDimOrigin_RefLevel2,
	APIDimOrigin_StoredOrigin,
	APIDimOrigin_Altitude
} API_DimOriginID;

typedef struct {
	API_MarkerID					markerType;					// marker type
	short							filler_1;
	short							markerPen;
	double							markerSize;					// in scaled drawing size (in mm)
} API_MarkerData;

typedef struct {
	API_ElemType					type;						// type of base element
	bool							line;						// OnNeigs
	char							special;					// e.g. WallPl...
	short							filler_1;
	Int32							filler_2;
	Int32							inIndex;					// of base element's node
	API_Guid						guid;						// of base element

																// section-specific data
	UInt32							node_id;					// internal id of this node [alternative of inIndex]
	short							node_status;				// for section dim.
	short							node_typ;					// for section dim
} API_Base;

typedef struct {
	API_Base						base;
	API_Coord						loc;
	API_Coord3D						loc3D;						// coordinate of the base point in 3D
} API_DimBase;

typedef struct {
	API_DimBase						base;						// the dimensioned point
	API_NoteType					note;
	double							witnessVal;					// gap or length of witness line according to WitnessForm
	API_WitnessID					witnessForm;				// witness Format
	bool							fixedPos;					// fixed position ('pos' has to be calculated in this case only)
	bool							filler_1;
	short							filler_2;
	API_Coord						pos;						// corresponding coordinate on the dimension line
	double							dimVal; 					// distance from previous DimElem (output only)
	API_Coord3D						pos3D;						// corresponding coordinate on the dimension line in 3D
	Int32							filler_3[6];
} API_DimElem;


typedef enum {
	API_Legacy						= 0,
	API_Flexible,
	API_Centered,
	API_LayoutOff
} API_DimLayoutID;

typedef enum {
	API_EmptyFill,
	API_NorthwestBlack,
	API_NortheastBlack
} API_CircleLevelDimensionFillID;

typedef struct {
	API_Elem_Head					head;

	short							linPen;						// color index of lines
	short							filler_1;
	API_TextPosID					textPos;					// text position
	API_DirID						textWay;					// parallel, horizontal, vertical
	API_AppearID					dimAppear;
	bool							detailedHoleDim;			// detailed door/wind dimension
	char							nominalHoleDim;				// nominal height for door/wind dimension
	char							compAutoThick;				// dimension of composite walls -> totalBit = 1; coreBit = 2; refLineBit = 4; manualBit	= 16;
	bool							defStaticDim;				// default static switch
	API_WitnessID					defWitnessForm;				// default witness format
	double							defWitnessVal;				// default gap or length of witness line according to defWitnessForm
	API_NoteType					defNote;					// default note parameters
	API_MarkerData					markerData;
	char							ed_dimForm;					// elevation dimension:  Marker type
	char							ed_arrowAng;				// elevation dimension: half-arrow angle  0,1,2 -> 30,45,60
	bool							ed_arrowFill;				// elevation dimension: arrow is filled or not
	bool							ed_arrowUp;					// elevation dimension: arrow is up/down
	bool							ed_needPlus;				// elevation dimension: plus sign needed for positive numbers
	bool							usedIn3D;					// used for dimensioning 3D points
	bool							horizontalText;				// dimension texts are horizontal
	bool							onlyDimensionText;			// Only DimensionNotes visible
	API_DimOriginID					ed_origin;					// elevation dimension: origin
	API_CircleLevelDimensionFillID	ed_circleLevelDimensionFill;	// elevation dimension: the circle style marker fill
	Int32							filler_4[4];
	API_Coord						refC;						// dimension line location
	API_Vector						direction;					// direction of the dim line if parallel
	API_DimBase						arcBase;
	Int32							nDimElem;					// number of segments in dimension elements in chain (memo)
	Int32							filler_5;
	API_Coord3D						refC3D;						// Position of the dimension chain (used only in 3D)
	API_Vector3D					direction3D;				// direction of the dimension line (used only in 3D)
	API_Vector3D					normVect3D;					// dimension plane's normal vector (used only in 3D)
	API_DimLayoutID					dimLayout;
	bool							pushNeighborEnabled;		// API_Flexible layout only
	bool							placeUnderEnabled;			// API_Flexible layout only
	bool							advanced;					// API_Centered layout only
	bool							clipOtherSide;				// No witness line part on the other side (opposite to basepoint)
	Int32							filler_6[6];
} API_DimensionType;


// =============================================================================
// Radial Dimension
//
// =============================================================================

typedef struct {
	API_Elem_Head					head;

	short							linPen;						// color index of lines
	short							filler_1;
	API_TextPosID					textPos;	  				// up/in/below
	API_DirID						textWay;					// Horizontal, Vertical, Radial
	bool							showOrigo;					// show arc's origo
	bool							onlyDimensionText;			// Only DimensionNotes visible
	bool							filler_2[2];
	char							prefix[8];					// before number; example: R 7.55
	GS::UniString*					prefixUStr;
	API_MarkerData					markerData;
	Int32							filler_3[6];

	API_NoteType					note;

	API_DimBase						base;
	API_Coord						endC;						// end of [radial] dimension line
	double							dimVal; 					// radius of dimensioned item
	Int32							filler_4[8];
} API_RadialDimensionType;


// =============================================================================
// Level Dimension
//
// =============================================================================

typedef struct {
	API_Elem_Head					head;

	short							pen;  						// color index/exist
	short							dimForm;  					// format [0..9]
	bool							filler_0;					// framed dimension number
	bool							needPlus;					// plus sign needed for positive numbers
	bool							staticLevel;
	bool							filler_1;
	double							markerSize;					// marker size in mm
	double							angle;    					// angle of LevDim mark, radian
	Int32							filler_2[8];

	API_NoteType					note1;
	API_NoteType					note2;						// for type: dimForm = 8,9

	API_Coord						loc;						// of the marker
	double							level;						// of the parent/floor or static
	API_ElemType					parentType;					// refer to this element; refer to floor if Zombie
	Int32							filler_3;
	API_Guid						parentGuid;					// guid of referred element
	API_DimOriginID					origin;
	Int32							filler_4[7];
} API_LevelDimensionType;


// =============================================================================
// Angle Dimension
//
// =============================================================================

typedef struct {
	API_Elem_Head					head;

	short							linPen;						// color index of lines
	bool							smallArc;					// show the smaller arc of a-b
	bool							onlyDimensionText;			// Only DimensionNotes visible
	API_TextPosID					textPos;	  				// up/in/below
	API_DirID						textWay;					// parallel, horizontal, perpendicular
	API_WitnessID					witnessForm;				// witness format, see in Types
	double							witnessVal;					// gap or length of witness line according to WitnessForm
	API_MarkerData					markerData;
	Int32							filler_1[8];

	API_NoteType					note;

	API_DimBase						base[4];					// reference points
	API_Coord						pos;						// point to fit dimension arc
	API_Coord						origo;						// of dimension arc
	double							dimVal; 					// angle of dimensioned items [Rad]
	double							radius;						// of dimension arc
	Int32							filler_2[8];
} API_AngleDimensionType;


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

typedef enum {
	APITab_Left,
	APITab_Center,
	APITab_Right,
	APITab_Decimalpoint
} API_TabID;

typedef struct {
	API_TabID						type;
	Int32							filler_1;
	double							pos;						// position in model unit
	double							filler_2[3];
} API_TabType;

typedef struct {
	Int32							from;						// byte offset
	Int32							range;
	short							pen;						// pen index
	unsigned short					faceBits;					// bold, italic...
	short							font;						// font index
	unsigned short					effectBits;					// strikeout, superscript...
	double							size;
	double							filler_1[3];
} API_RunType;

typedef struct {
	Int32							from;
	Int32							range;
	API_JustID						just;						// justification of Paragraph
	Int32							filler_1;
	double							firstIndent;
	double							indent;
	double							rightIndent;				// not used yet
	double							spacing;					// spacing scale between text lines
	API_TabType						*tab;						// array of tabulators (GSPtr)
	API_RunType						*run;						// array of runs (GSPtr)
	Int32							*eolPos;					// array of End Of Line positions (GSPtr)
	Int32							filler_2;
	double							width;						// width of the paragraph (output only)
	double							height;						// height of the paragraph (output only)
	double							filler_3[2];
} API_ParagraphType;

typedef struct {
	API_Elem_Head					head;

	short							pen;						// color index
	unsigned short					faceBits;					// style of text
	short							font;						// font index
	bool							fixedAngle;					// use fix angle
	bool							filler_1;
	API_AnchorID					anchor;						// kind of text center
	API_JustID						just;						// justification of text
	double							size;						// char height in mm
	double							spacing;					// spacing scale between text lines
	double							angle;						// rotation angle (radian)
	double							filler_2;					// slant not used yet
	Int32							charCode;					// (GSCharCode)  do not use for string encoding. only for font handling!!

	Int32							effectsBits;				// superscript, subscript, strike-through
	double							widthFactor;
	double							charSpaceFactor;			// spacing scale
	bool							fixedSize;					// size not depends on output scale
	bool							usedContour;
	bool							usedFill;
	bool							filler_3;
	short							contourPen;
	short							fillPen;

	API_Coord						loc;						// real coordinates of text anchor point
	double							width;						// horizontal size of text box in mm
	double							height;						// vertical size of text box in mm
	bool							nonBreaking;				// false: wrap around destination rect
	bool							multiStyle;
	bool							useEolPos;					// input only
	bool							filler_4;
	Int32							nLine;						// number of text lines
	API_Guid						owner;						// belongs to something else e.g. a label

	double							contourOffset;

	bool							flipEnabled;

	char							filler_5[3];
	Int32							filler_6[5];
} API_TextType;


// =============================================================================
// Label
//
// =============================================================================

typedef enum {
	APILblClass_Text				= 'TEXT',
	APILblClass_Symbol				= 'SYMB'
} API_LblClassID;

typedef struct {
	union {
		API_Elem_Head				head;
		API_TextType				text;						// with API_LabelID
		API_ObjectType				symbol;
	} u;
	API_LblClassID					labelClass;					// type (class) of the label
	Int32							filler_1;

																// text
	API_DirID						textWay;					// parallel, horizontal, vertical, general
	Int32							filler_2[5];

																// symbol
	bool							filler_3[2];
	short							font;						// font index for symbol labels only
	unsigned short					faceBits;					// style of text for symbol labels only
	bool							flipEnabled;				// true, if text is "Always Readable"
	bool							nonBreaking;				// true, if "Wrap Text" is disabled
	double							textSize;					// size of text in mm, for symbol labels only
	bool							filler_4;
	bool							useBgFill;					// use opaque background (for symbol labels)
	short							fillBgPen;					// background pen (for symbol labels)
	Int32							effectsBits;				// superscript, subscript, strike-through text effects (for symbol labels)

																// leader
	short							pen;						// color index of the leader
	short							filler_5;
	API_AttributeIndex				ltypeInd;					// line type index of the leader
	double							contourOffset;				// offset between the text and the frame
	bool							framed;						// framed content
	bool							hasLeaderLine;				// Leader Line is turned on or off?
	char							filler_6[6];
	API_ArrowData					arrowData;
	API_LblAnchorID					anchorPoint;				// the anchor point the label's leader is connected to
	API_LeaderLineShapeID			leaderShape;				// segmented, spline or square root
	double							squareRootAngle;			// used only if leaderShape == API_SquareRoot, see API documentation for a picture
	Int32							filler_7[4];

	API_ElemType					parentType;					// associative Label: type of the owner element; independent Label: API_ZombieElemID
	bool							filler_8[4];
	API_Guid						parent;						// associative Label: GUID of the owner element; independent Label: APINULLGuid
	API_Coord						begC;						// beg Coord of leader line
	API_Coord						midC;						// mid Coord of leader line
	API_Coord						endC;						// end Coord of leader line
	bool							createAtDefaultPosition;	// if set to true, the associative Label will be created at its default position (input only field)
	bool 							hideWithBaseElem; 			// output only
	char							filler_9[22];
} API_LabelType;


// =============================================================================
// Zone
//
// =============================================================================

typedef struct {
	API_Elem_Head					head;

	short							pen;						// color index for stamp
	API_AttributeIndex				catInd; 					// index of the actual room category
	bool							useStampPens;				// draw with a single pen or multicolor
	bool							manual;						// manually created; all edges static, no refPt
	bool							refLineFlag;				// surrounded by walls' ref.line, not side lines
	bool							show_found_poly;			// show found_poly/poly switch, used if refLineFlag
	char							filler_1[16];
	GS::uchar_t						roomName [API_UniLongNameLen];
	GS::uchar_t						roomNoStr [32];
	double							roomBaseLev;
	double							roomHeight;
	double							roomTopOffset;				// offset from top floor if top linked
	double							roomFlThick;
	double							roomLSize;
	double							reducePercent;
	API_AttributeIndex				material;					// of the 3D room's [free or all] surfaces
	Int32							filler_2[2];
	double							stampAngle;					// rotation angle of the room stamp (radian)
	bool							fixedAngle;					// zone stamp angle is fixed
	bool							oneMat;						// use "material" for all surfaces
	short							floorFillPen;				// color index of floorplan fill
	API_AttributeIndex				floorFillInd;				// floorplan fill index
	short							floorFillBGPen;				// color index of floorplan fill background
	short							floorContLPen;				// color index of floorplan contour
	API_AttributeIndex				floorContLType;				// line type index of floorplan contour
	bool							useContourLine;				// use floorplan contour line
	bool							useLocalOrigo;				// floorplan fill (used local origo)
	bool							use3DHatching;				// floorplan fill from material
	bool							useFloorFill;				// use cover fill
	Int32							libInd;						// index to the room in the library
	API_LinkToSettings				linkToSettings;				// link to story settings
	short							relativeTopStory;			// top linked story (relative to home story), 0 = not top linked
	short							filler_3[3];

	API_Polygon						poly;
	API_Coord						pos;						// position of the origin of the object
	API_Coord						refPos;						// reference point to find room if not manual
	API_Coord						locOrigo;					// base coordinate of floorplan fill reference vector if linked to the element
	double							fillAngle;					// angle of floorplan fill reference vector if linked to the element
	API_Polygon						refPoly;					// the found poly
	API_Guid						stampGuid;
} API_ZoneType;


// =============================================================================
// Hatch
//
// =============================================================================

#define	APIHatch_DraftingFills		0x0000						// drafting fill
#define	APIHatch_CutFills 			0x0001						// cut fill
#define	APIHatch_CoverFills			0x0002						// cover fill

typedef enum {
	API_FillHatch,
	API_BuildingMaterialHatch
} API_HatchSubType;

typedef enum {
	APIHatch_HasBkgRGBColor					= 0x01,
	APIHatch_HasFgRGBColor					= 0x02,
	APIHatch_OverrideFgPen					= 0x04,
	APIHatch_OverrideBkgPen					= 0x08,
	APIHatch_OverrideFillInd				= 0x10
} API_HatchFlags;

struct API_ExtendedPenType {
	short	penIndex;
	short	colorOverridePenIndex;

	void	Set (short pen1, short pen2)		{ penIndex = pen1; colorOverridePenIndex = pen2; }
	bool	IsOverriden () const				{ return colorOverridePenIndex > 0; }
	short	GetEffectiveColorIndex () const		{ return IsOverriden () ? colorOverridePenIndex : penIndex; }
};

typedef struct {
	API_Elem_Head					head;

	API_ExtendedPenType				contPen;					// color index of hatch contour
	API_HatchSubType				hatchType;					// type of the hatch
	UInt32							hatchFlags;
	API_ExtendedPenType				fillPen;					// color index of hatch fill
	short							filler_0;
	short							fillBGPen;					// color index of hatch background
	API_AttributeIndex				fillInd;					// fill index
	API_AttributeIndex				buildingMaterial;			// building material
	API_AttributeIndex				ltypeInd;					// line type index
	char							roomSpecial;				// special area percent in a room (negative means OFF)
	char							filler_1[4];
	bool							showArea;					// true if area text shown (parameters in note)
	short							determination;				// how to determine the type of this fill (cover, cut, drafting)
	Int32							filler_2[2];
	char							filler_3[16];
	double							penWeight;
	Int32							filler_4[2];

	API_NoteType					note;

	API_Polygon						poly;
	bool							filler_5[8];
	Int32							filler_6[10];

	API_HatchOrientation			hatchOrientation;

	bool							filler_7;
	char							filler_8[3];
	Int32							filler_9[5];
	API_RGBColor					backgroundRGB;				// RGB color for background painting
	bool							filler_10;
	char							filler_11[3];
	Int32							filler_12[5];
	API_RGBColor					foregroundRGB;				// RGB color for foreground painting
} API_HatchType;


// =============================================================================
// Line
//
// =============================================================================

#define	APILine_DetOrigin			0x0000
#define	APILine_DetInnerLine		0x0001
#define	APILine_DetContourLine		0x0002

typedef struct {
	API_Elem_Head					head;

	API_ExtendedPenType				linePen;					// color index
	API_AttributeIndex				ltypeInd;					// line type index
	bool							roomSeparator;				// room separator line
	bool							filler_1[5];
	short							determination;				// how to determine the type of this line
	API_ArrowData					arrowData;
	double							penWeight;
	Int32							filler_2[8];

	API_Coord						begC; 						// coordinate of the first point
	API_Coord						endC;						// coordinate of the second point
	Int32							filler_3[8];
} API_LineType;


// =============================================================================
// Polyline
//
// =============================================================================

typedef struct {
	API_Elem_Head					head;

	API_ExtendedPenType				linePen;					// color index
	API_AttributeIndex				ltypeInd;					// line type index
	bool							roomSeparator;				// room separator line
	bool							filler_1[5];
	short							determination;				// how to determine the type of this line
	API_ArrowData					arrowData;
	double							penWeight;
	char							filler_2[16];
	Int32							filler_3[8];

	API_Polygon						poly;
	short							drawSegmentMode;			// 0 - draw segments one-by-one, 1 - draw all continuously
	short							filler_4;
	Int32							filler_5[7];
} API_PolyLineType;


// =============================================================================
// Arc or Circle
//
// =============================================================================

typedef struct {
	API_Elem_Head					head;

	API_ExtendedPenType				linePen;					// color index
	API_AttributeIndex				ltypeInd;					// line type index
	bool							roomSeparator;				// room separator line
	bool							filler_1[5];
	short							determination;				// how to determine the type of this line
	API_ArrowData					arrowData;
	double							penWeight;					// API_DefPenWeigth: use default weight of the pen
	char							filler_2[16];
	Int32							filler_3[8];

	API_Coord						origC;						// coordinate of the center point
	double							r;							// radius
	double							angle;						// 0.0,	or the angle of the 'a' axis
	double							ratio;						// 1.0,	or 'a/b' of the ellipse
	double							begAng;						// beginning angle of the arc
	double							endAng;						// ending angle of the arc
	bool							reflected;					// on the smaller axis (???)
	bool							whole;						// is this a whole arc -- output only
	short							filler_4;
	Int32							filler_5[7];
} API_ArcType, API_CircleType;


// =============================================================================
// Spline
//
// =============================================================================

typedef struct {
	double							lenPrev;					// Bezier direction length prev/next
	double							lenNext;
	double							dirAng;						// Bezier direction angle
} API_SplineDir;

typedef struct {
	API_Elem_Head					head;

	API_ExtendedPenType				linePen;					// color index
	API_AttributeIndex				ltypeInd;					// line type index
	bool							roomSeparator;				// room separator line
	bool							filler_1[5];
	short							determination;				// how to determine the type of this line
	API_ArrowData					arrowData;
	double							penWeight;
	char							filler_2[16];
	bool							autoSmooth;					// auto-smooth
	bool							closed;						// closed curve
	short							filler_3;
	Int32							filler_4[7];
} API_SplineType;


// =============================================================================
// Hotspot
//
// =============================================================================

typedef struct {
	API_Elem_Head					head;

	short							pen;						// color index
	short							filler_1[3];

	API_Coord						pos; 						// coordinate of the hotspot
	double							height;
	Int32							filler_2[2];
} API_HotspotType;


// =============================================================================
// Picture
//
// =============================================================================

typedef enum {
	APIPictForm_Default,
	APIPictForm_Bitmap,
	APIPictForm_GIF,
	APIPictForm_TIFF,
	APIPictForm_JPEG,
	APIPictForm_PNG
} API_PictureFormat;

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


typedef struct {
	API_Elem_Head					head;

	bool							mirrored;					// true if mirrored to local vertical axis
	bool							usePixelSize;
	short							pixelSizeX;
	short							pixelSizeY;
	bool							transparent;
	bool							directCreate;
	double							rotAngle;
	API_Box							destBox;
	API_Box							origBox;
	API_ColorDepthID				colorDepth;
	API_AnchorID					anchorPoint;				// anchor point of core (0 = center)
	API_PictureFormat 				storageFormat;				// id to pict data block in "picts" handle
	Int32							filler_1;

	GS::uchar_t						pictName[API_UniLongNameLen];
	char							mime[128];					// MIME type (only output)
	Int32							filler_2[6];
} API_PictureType;


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

typedef enum {
	APIBound_UncutContours			= 1,
	APIBound_NoContours				= 2,
	APIBound_OverrideContours		= 3
} API_BoundaryDisplay;

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

typedef enum {
	APICutPl_ShowMiddleMarker		= 0,
	APICutPl_ShowWingMarkers		= 1
} API_CutPlaneMarkerShowType;


typedef struct {
	short							linePen; 					// color index
	short							textPen;					// text color
	API_AttributeIndex				ltypeInd;					// line type index
	short							sectPen;
	short							sectFillPen;
	short							sectFillBGPen;				// background pen on section drawing
	short							verticalRangeStoryBaseNumber;
	API_SegmentHorizontalRange		horizRange;					// horizontal range
	API_SegmentVerticalRange		vertRange;					// vertical range
	double							markerSize;					// marker size
	bool							begMark;					// 1: marker on beg Point
	bool							endMark;
	bool							relativeToStory;			// vertical limited range is relative to story or absolute to project zero
	bool							filler_2;
	bool							useElemPens;				// use elements' own pens
	bool							begLine;					// line at beginning point
	bool							middleLine;					// line at middle point
	bool							endLine;					// line at end point
	double							lineLength;					// length of the line
	double							vertMin;					// vertical limited min range
	double							vertMax;					// vertical limited max range
	GS::uchar_t						cutPlName [API_UniLongNameLen];
	GS::uchar_t						cutPlIdStr [API_UniLongNameLen];
	double							textSize;					// text size [mm] of marker text
	short							font;						// font index
	short							effectBits;					// settings of the 3D view
	API_AttributeIndex				shadFill;					// fill index of the shadow's fill
	short							shadFillPen;				// pen of the fill
	short							shadFillBGPen;				// background pen of the fill
	API_AttributeIndex				limitLtypeInd;				// line type of the horizontal limit line
	short							limitLinePen;				// pen of the horizontal limit line
	bool							continuous;					// continuous if true, otherwise is segmented
	bool							filler_3[5];
	double							sunAngXY;					// custom sun azimuth relative to the cutplane
	double							sunAngZ;					// custom sun altitude relative to the cutplane

	API_Guid						begMarkerId;				// marker element guid for cutting line
	API_Guid						midMarkerId;				// marker element guid for cutting line
	API_Guid						endMarkerId;				// marker element guid for cutting line

	short							filler_4;
	bool							modelUseElemPen;			// use elements' model colors
	bool							distAreaUseElemPen;			// use elements' model colors in distant area
	short							modelElemPen;				// elements' model color
	short							distAreaElemPen;			// elements' model colors
	API_AttributeIndex				distAreaShadFill;			// fill index of the shadow's fill
	short							distAreaShadFillPen;		// pen of the fill
	short							distAreaShadFillBGPen;		// background pen of the fill
	API_CutPlaneUncutSurfaceFillID	distAreaUncutSurfFillType;	// type of distant area uncut surface fill
	short							distAreaUncutSurfBGPen;		// background pen of distant area uncut surface fill
	bool							distAreaUseUncutSurfFill;	// use distant area uncut surface fill
	bool							markedDistArea;				// marked distant area

	API_CutPlaneUncutSurfaceFillID	modelUncutSurfFillType;		// type of model uncut surface fill
	short							modelUncutSurfBGPen;		// background pen of model uncut surface fill
	bool							modelUseUncutSurfFill;		// use model uncut surface fill

	bool							transparency;				// instead of Transparency in Shading (3D Window settings)

	UInt32							nMainCoord;					// coordinates in memo
	UInt32							nDistCoord;					// coordinates in memo
	UInt32							nDepthCoord;				// coordinates in memo
	bool							drawingModeON;				// section is in drawing mode

	bool							windOpened;					// side window is opened
	bool							active;						// turned off or active
	bool							sourceMarker;				// is a source marker (output only/no default)
	bool							filler_5[4];
	API_DatabaseUnId				databaseID;					// database ID to switch to (API_DatabaseInfo)

	API_CutPlanePlanConn			currPlanConn;				// current plan connectivity
	API_CutPlanePlanConn			intPlanConn;				// intended plan connectivity

	bool							solidOperationsOnZones;		// use the solid operations on zones
	bool							exclBlockWalls;				// exclude view blocking walls
	bool							showCutElements;			// show cut elements
	bool							byLimitLines;				// relevant elems are detected only by limit lines
	bool							filler_6[4];

	API_StoryHandleAppearance		shAppearance;				// where do stories appear (nowhere/only on display/also printouts)
	API_AttributeIndex				shLineType;					// story handle line type
	short							shLinePen;					// story handle line pen
	short							shMarkerPen;				// story handle marker pen
	bool							shUseSymbolPens;			// use own colors of the story handle marker object
	bool							shLeftMarkerOn;				// story handle left marker is needed
	bool							shRightMarkerOn;			// story handle right marker is needed
	bool							shLineOn;					// story handle line is on or off
	double							shLeftMarkerOffset;			// story handle left marker offset
	double							shRightMarkerOffset;		// story handle right marker offset
	API_Guid						shSymbolId;					// story handle marker symbol element guid
	short							shMarkerFont;				// story handle marker font index
	unsigned short					shMarkerFaceBits;			// story handle marker text style
	double							shMarkerTextSize;			// story handle marker text size
	double							shMarkerSize;				// story handle marker size
	API_BoundaryDisplay				boundaryDisplay;			// boundary contour display mode
	short							boundaryPen;				// boundary contour pen
	short							filler_7[3];
	API_AttributeIndex				boundaryLineType;			// boundary contour line type
	API_Sector						iePolygonEdge;				// used for link the segment to an edge of the Interior Elevation.

	double							ieCreationSegmentHorizontalOffset;	// used only for Interior Elevation creation.
	double							ieCreationSegmentDepth;				// used only for Interior Elevation creation.
} API_SectionSegment;

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

typedef struct {
	API_Guid			referredView;
	API_Guid			referredDrawing;
	API_Guid			referredPMViewPoint;
	bool				sourceMarker;
	bool				customMarker;
	bool				referToDrawing;
	bool				filler_1;
	API_ReferringLevel	referringLevel;

	Int32				filler_2[8];
} API_MarkerLinkDataType;

typedef struct {
	API_Elem_Head					head;

	API_CutPlaneShowType			cutPlShow;					// stories to show cutplane on
	short							storyToShowOn;
	short							filler_1;

	API_SectionSegment				segment;
	API_CutPlaneMarkerShowType		markerShow;

	API_MarkerLinkDataType			linkData;

	Int32							filler_2;
} API_CutPlaneType, API_ElevationType;

typedef struct {
	API_Elem_Head					head;

	API_CutPlaneShowType			cutPlShow;					// stories to show cutplane on
	short							storyToShowOn;
	short							filler_1;

	API_SectionSegment				segment;					// used to get and set the defaults; real segments are in the memo

	bool							useCommonMarker;			// show the common marker
	bool							filler_2[7];
	API_Guid						markerGuid;					// guid of the common marker library part
	short							markerPen;					// pen of the common marker
	short							markerFont;					// font of the common marker
	Int32							filler_3;
	double							markerSize;					// size of the common marker
	double							markerTextSize;				// size of the common marker's text

	UInt32							nSegments;					// number of segments in the memo
	Int32							nLineCoords;				// total number of segment line coordinates

	API_Polygon						poly;						// polyline of the connected segments

	Int32							filler_4[6];
} API_InteriorElevationType;

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

typedef enum {
	API_SunPosition_GivenByAngles	= 0,
	API_SunPosition_GivenByDate		= 1
} API_SunAngleSettings_SunPositionOption;


typedef struct {
	double									sunAzimuth;
	double									sunAltitude;
	API_SunAngleSettings_SunPositionOption	sunPosOpt;
	unsigned short							year;
	unsigned short							month;
	unsigned short							day;
	unsigned short							hour;
	unsigned short							minute;
	unsigned short							second;
	bool									summerTime;

	bool									filler;
} API_SunAngleSettings;

typedef struct {
	double							azimuth;					// rotation angle of the camera around the target
	API_SunAngleSettings			sunAngSets;					// Sun position
	short							projMod;					// projection type selected
	short							filler_1;
	Int32							filler_2;

	API_Tranmat						tranmat;
	API_Tranmat						invtranmat;
	double							filler_3[8];
} API_AxonoPars;

typedef struct {
	double							azimuth;					// rotation angle of the camera around the target
	API_SunAngleSettings			sunAngSets;					// Sun position
	double							viewCone;					// angle of the camera view cone
	double							rollAngle;					// roll angle of the camera
	double							distance;					// distance of the camera and the target
	double							cameraZ;					// Z coordinate of camera position
	double							targetZ;					// Z coordinate of target position
	bool							isTwoPointPersp;			// Two-point perspective
	bool							filler_0[7];
	double							filler_1[7];

	API_Coord						pos;						// X and Y coordinate of camera position
	API_Coord						target;						// X and Y coordinate of target position
	double							filler_2[8];
} API_PerspPars;

typedef struct {
	API_PerspPars					persp;						// perspective settings of the camera
	short							waitFrames;					// number of the frames for waiting here
	short							pen;
	Int32							filler_1;

	API_Guid						prevCam;					// previous camera guid
	API_Guid						nextCam;					// next camera guid
	double							lenPrev;					// Bezier direction length previous
	double							lenNext;					// Bezier direction length next
	double							dirAng;						// Bezier direction angle
	bool							active;						// active in the path
	bool							filler_2[7];
	Int32							filler_3[6];
} API_PerspCamPars;

typedef struct {
	Int32							camInd;						// index of the target camera
	short							status;
	short							pen;
	API_Coord						connPoint;
	double							filler_2[4];
} API_LinkType;

typedef struct {
	API_Elem_Head					head;
	API_Guid						camSetGuid;				// belongs to this camera set
	API_PerspCamPars				perspCam;
} API_CameraType;


// =============================================================================
// CamSet
//
// =============================================================================

typedef struct {
	bool							openedPath;					// open or closed animation path
	bool							bezierPath;					// in-between frames along polygonal or Bezier animation path
	bool							smoothTarget;				// in-between frames along a straight line or smooth curve
	bool							filler_1;
	short							filler_2;
	short							pen;
	Int32							inFrames;					// number of the in-between frames
	Int32							showFrom;					// first camera index in slide
	Int32							showTo;						// last camera index in slide
	Int32							filler_3;
} API_PersCamSetPars;

typedef struct {
	API_Elem_Head					head;

	GS::uchar_t						name [API_UniLongNameLen];	// name of the camera-set
	API_PersCamSetPars				perspPars;

	bool							active;						// is it the active camera-set or not?
	bool							filler_2[7];
	API_Guid						firstCam;					// first camera in the camera-set
	API_Guid						actCam;						// actual camera in the camera-set
} API_CamSetType;


// =============================================================================
// Drawing
//
// =============================================================================

typedef enum {
	APIName_ViewOrSrcFileName		= 0,
	APIName_ViewIdAndName			= 1,
	APIName_CustomName				= 2
} API_NameTypeValues;

typedef enum {
	APINumbering_ByLayout			= 0,
	APINumbering_ByViewId			= 1,
	APINumbering_CustomNum			= 2
} API_NumberingTypeValues;

typedef enum {
	APIColorMode_OriginalColors		= 0,
	APIColorMode_BlackAndWhite		= 1,
	APIColorMode_GrayScale			= 2
} API_ColorModeValues;

typedef enum {
	APIPenTableUsageMode_UseOwnPenTable		= 0,
	APIPenTableUsageMode_UseModelPenTable	= 1,
	APIPenTableUsageMode_UsePenTableIndex	= 2
} API_PenTableUsageModeValues;

typedef enum {
	APITitlePreviewMode_DrawingWithTitle	= 0,
	APITitlePreviewMode_TitleOnly			= 1
} API_TitlePreviewModes;

typedef struct {
	Int32							libInd;						// library part index of the title
	API_TitlePreviewModes			previewMode;				// title preview mode: a TitlePreviewModes value
	bool							useUniformTextFormat;		// use the fonts and style set on the title tabpage
	bool							filler_0;
	short							font;						// title common text font ID
	unsigned short					faceBits;					// plain, bold, italic, underline
	short							textPen;					// title common text pen
	double							textSize;					// title text size
	bool							flipped;					// the title object is flipped
	bool							useUniformSymbolPens;		// use the pens set on the title tabpage
	short							pen;						// title common pen
	API_Guid						guid;						// guid of title element
	Int32							filler_1[2];
} API_DrawingTitle;

typedef struct {
	API_Elem_Head					head;

	char							name[256];					// custom drawing name
	API_NameTypeValues				nameType;					// type of the drawing name
	API_NumberingTypeValues			numberingType;				// type of numbering
	char							customNumber[256];			// custom drawing number
	bool							isInNumbering;				// include in numbering sequence
	bool							manualUpdate;				// update type: manual or auto
	bool							storedInProject;			// drawing is stored in the project file - output only
	bool							isScheduleAdjusted;			// internal parameter used by the Element Schedule - output only
	bool							isMultiPageDrawing;			// drawing is split to more page
	bool							includeInAutoTextsAndIES;	// include this Drawing in Drawing Scale/Original Scale AutoTexts, and in Scale columns of Drawing/Layout type Project Indexes
	bool							filler_1[2];

	double							angle;						// angle of the placed drawing in radian (clockwise)
	double							ratio;						// drawing size / original size
	double							rasterizeDPI;				// rasterize PDF at this dpi
	double							drawingScale;				// scale of the view (e.g. 0.002 for 1:500) - output only
	double							parentOriginalScale;		// parent scale while drawing creation (used in updating image and pdf type drawings) - output only
	API_AnchorID					anchorPoint;				// placement reference by bounding box node (relevant only if not useOwnOrigoAsAnchor)
	API_ColorModeValues				colorMode;					// mode of using pens
	API_PenTableUsageModeValues		penTableUsageMode;
	API_AttributeIndex				penTableIndex;				// index of the pen table
	bool							useOwnOrigoAsAnchor;		// use drawing's own origo as placement reference point
	bool							isTransparentBk;			// transparent background
	bool							isCutWithFrame;				// clip with frame polygon
	bool							hasBorderLine;				// show border
	API_AttributeIndex				borderLineType;				// line type of drawing border
	short							borderPen;					// pen of drawing border
	bool							filler_2[2];
	double							borderSize;					// thickness of border in m

	API_DrawingTitle				title;						// drawing title

	API_Box							bounds;						// boundary box
	API_Coord						pos;						// coordinate of the placed drawing's origin on the layout
	API_Polygon						poly;						// polygon on the layout: the clip polygon if isCutWithFrame else the bounding box in polygon format

	UInt32							sortIndex;					// sort index
	Int32							linkUId;					// unique ID of link associated with drawing (not used yet)
	API_Guid						drawingGuid;				// GUID of the drawing.
	API_Coord						modelOffset;				// Output-only - for DXF save
	API_Vector						offset;						// Output-only

	API_Coord						pageOffset;					// Offset of the next page's position
	UInt32							pageNumberX;				// Number of pages in x direction
	UInt32							pageNumberY;				// Number of pages in y direction

} API_DrawingType;


// =============================================================================
// Section Elem
// (virtual symbol created from the plan's construction elements)
// =============================================================================

typedef struct {
	API_Elem_Head					head;

	API_ElemType					parentType;					// parent elem type
	Int32							filler_1;
	API_Guid						parentGuid;					// parent elem guid
	Int32							filler_2[6];
	API_Guid						ownerGuid;					// to quicken the search for CurtainWall subelems in section
} API_SectElemType;


// =============================================================================
// Detail
//
// =============================================================================

typedef struct {
	API_Elem_Head					head;

	short							pen;						// color index of detail's contour
	short							filler_1;
	API_AttributeIndex				ltypeInd;					// line type index of detail's contour
	API_Coord						pos;						// coordinate of the base Point
	double							angle;						// marker rotation angle (radian)
	API_Guid						markId;						// guid of the marker symbol
	Int32							filler_2;
	GS::uchar_t						detailName [API_UniLongNameLen];// name of the detail
	GS::uchar_t						detailIdStr [API_UniLongNameLen];// ref Id of the detail
	bool							horizontalMarker;			// marker always horizontal
	bool							windOpened;
	bool							constructionElementsOnly;
	bool							filler_3[5];
	API_DatabaseUnId				databaseID;
	Int32							filler_4[8];

	API_Polygon						poly;						// the clip polygon of the detail

	API_MarkerLinkDataType			linkData;

	Int32							filler_5[8];
} API_DetailType, API_WorksheetType;


// =============================================================================
// Hotlink instance
//
// =============================================================================

typedef struct {
	API_Elem_Head					head;

	API_HotlinkTypeID				type;						// hotlink reference type
	Int32							filler_1;
	API_Guid						hotlinkNodeGuid;			// reference to the associated hotlink node (API_HotlinkNode)
	API_Guid						hotlinkGroupGuid;			// reference to the associated group of elements
	API_Tranmat						transformation;				// hotlink transformation
	short							floorDifference;			// floor difference in case of hotlink module
	bool							suspendFixAngle;			// adjust angle of fixed-angle elements to reflect module rotation
	bool							skipNested;
	bool							ignoreTopFloorLinks;
	bool							relinkWallOpenings;
	bool							adjustLevelDiffs;
	char							filler_2[2];
	char							filler_3[16];			// master ID
	Int32							filler_4[2];
} API_HotlinkType;


// =============================================================================
// Change Marker
//
// =============================================================================

typedef enum {
	APICMLT_CreateNewChange,
	APICMLT_Linked,
	APICMLT_Unlinked
} API_ChangeMarkerLinkType;

typedef enum {
	APICMCT_HeadOnly,
	APICMCT_CloudOnly,
	APICMCT_HeadAndCloud
} API_ChangeMarkerComponentType;


typedef struct {
	API_Elem_Head					head;

	API_ChangeMarkerLinkType		linkType;						// unlinked, linked, or linked to a newly created Change
	API_ChangeMarkerComponentType	markerComponent;				// has Marker Head and/or Cloud
	GS::uchar_t						changeId[API_UniLongNameLen];	// unique ID of the linked Change
	GS::uchar_t						changeName[API_UniLongNameLen];	// name (short description) of the linked Change
	API_Coord						pos; 							// coordiate, where the ChangeMarker points (if it does not have a polygon)
	API_Polygon						poly;							// some data of the polygon of the ChangeMarker (if it has a polygon)
	API_Guid						markerGuid;						// GUID of the associated Marker LibPart
	double							angle;							// marker rotation angle (radian)
	bool							horizontalMarker;				// marker always horizontal
	char							filler_1[3];
	Int32							filler_2;
} API_ChangeMarkerType;

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

typedef struct {
	API_StairPolyTypeID 			type;
	API_StairPolyGeometryTypeID 	geometryType;
	UInt32 							subElemId;
	bool	 						isTop;
	bool	 						isBottom;
	bool	 						isFront;
	bool	 						isBack;
	UInt32 							customId;
	API_StairSegmentTypeID			segmentType;
	bool	 						isLocked;
	bool	 						filler_1[3];
	Int32 							filler_2;
} API_StairPolylineEdgeData;

typedef struct {
	API_StairPolyTypeID 				type;
	API_StairPolyGeometryTypeID 		geometryType;
	UInt32 								subElemId;
	bool	 							isTop;
	bool	 							isBottom;
	bool	 							isFront;
	bool	 							isBack;
	UInt32 								customId;
	API_StairTurnTypeID 				turnType;
	Int32								winderStepNumBackward;
	Int32								winderStepNumForward;
	bool								symmetricalLandingOffset;
	bool	 							filler_1[7];
	double								minLandingStartEdgeOffset;
	double								minLandingEndEdgeOffset;
	double								currLandingStartEdgeOffset;
	double								currLandingEndEdgeOffset;
	double								filler_2;
	API_StairInnerWidthOffsetTypeID		innerWidthOffsetType;
	API_StairWinderNumTypeID			numOfWindersType;
	API_StairDLWinderNumTypeID			dividedLandingNumOfWindersType;
	Int32								dividedLandingFixedNumOfSteps;
	API_StairWinderID					winderType;
} API_StairPolylineVertexData;

typedef struct {
	API_Polygon 					polygon;
	API_Coord 						**coords;
	Int32 							**pends;
	API_PolyArc 					**parcs;
	API_StairPolylineEdgeData		*edgeData;
	API_StairPolylineVertexData 	*vertexData;
} API_StairPolylineData;

typedef struct {
	API_StairPolyTypeID 			type;
	API_StairPolyGeometryTypeID 	geometryType;
	UInt32 							subElemId;
	bool	 						isTop;
	bool	 						isBottom;
	bool	 						isFront;
	bool	 						isBack;
	UInt32 							customId;
	UInt32 							filler_1;
	double 							zValue;
} API_StairBoundaryVertexData;

typedef struct {
	API_StairPolyTypeID 			type;
	API_StairPolyGeometryTypeID 	geometryType;
	UInt32 							subElemId;
	bool	 						isTop;
	bool	 						isBottom;
	bool	 						isFront;
	bool	 						isBack;
	UInt32 							customId;
	bool	 						visible;
	bool	 						filler_1[3];
} API_StairBoundaryEdgeData;

typedef struct {
	API_Polygon 					polygon;
	API_Coord       				**coords;
	Int32           				**pends;
	API_PolyArc     				**parcs;
	API_StairBoundaryEdgeData 		*edgeData;
	API_StairBoundaryVertexData 	*vertexData;
	bool	 						isCustom;
	bool	 						filler_1[7];
} API_StairBoundaryData;

typedef struct {
	API_StoryVisibility             visibility;
	bool	                        isAutoOnStoryVisibility;
	bool	                        filler_1[3];
	API_StairGridTypeID             gridTypeAbove;
	API_StairGridTypeID             gridTypeTop;
	API_StairGridTypeID             gridTypeMiddle;
	API_StairGridTypeID             gridTypeBottom;
	API_StairGridTypeID             gridTypeBelow;
	API_StairStoryVisibilityID      storyVisibility;
	bool	                        showWalkingLine;
	bool	                        showNumbering;
	bool	                        showUpDownText;
	bool	                        showDescription;
	bool	                        filler_2[2];
	bool	                        showStructure;
	bool		                    filler_3[5];
	double                          breakLineAngle;
	Int32                           breakLineAngleNumberOfGoings;
	API_BreakLineAngleTypeID        breakLineAngleType;
	double                          breakLineDistance;
	API_BreakLinePositionTypeID     breakLinePositionType;
	Int32                           filler_4;
	double                          upperBreakLineCustomPosition;
	double                          lowerBreakLineCustomPosition;
	UInt32                          upperBreakLineNthRiserPosition;
	UInt32                          lowerBreakLineNthRiserPosition;
	bool	                        overrideLineType;
	bool	                        overridePen;
	short                           pen;
	API_AttributeIndex              lineType;
	bool	                        overrideSymbolFill;
	bool	                        filler_5[3];
	API_AttributeIndex              symbolFill;
	short                           symbolFillPen;
	short                           symbolFillBkgPen;
	short                           filler_6[2];
} API_StairLayoutData;

typedef struct {
	double 							riserHeightMinValue;
	double 							riserHeightMaxValue;
	double 							treadDepthMinValue;
	double 							treadDepthMaxValue;
	double 							ruleMinValue;
	double 							ruleMaxValue;
	double 							landingLengthMinValue;
	double 							walkingLineOffsetMinValue;
	double 							winderTurnOffsetMinValue;
	double  						riserGoingRatioMinValue;
	double  						riserGoingRatioMaxValue;
   	double  						riserPlusGoingMinValue;
   	double  						riserPlusGoingMaxValue;
   	double  						stairPitchMinValue;
   	double  						stairPitchMaxValue;
	bool	 						riserHeightMinApplied;
	bool	 						riserHeightMaxApplied;
	bool	 						treadDepthMinApplied;
	bool	 						treadDepthMaxApplied;
	bool	 						ruleMinApplied;
	bool	 						ruleMaxApplied;
	bool	 						landingLengthMinApplied;
	bool	 						walkingLineOffsetMinApplied;
	bool	 						winderTurnOffsetMinApplied;
	bool							filler_1[2];
	bool							riserGoingRatioMinApplied;
   	bool							riserGoingRatioMaxApplied;
   	bool							riserPlusGoingMinApplied;
   	bool							riserPlusGoingMaxApplied;
   	bool							stairPitchMinApplied;
   	bool							stairPitchMaxApplied;
	bool	 						filler_2[3];
} API_StairRulesData;

typedef struct {
	API_HeadroomGenerationModeID	headroomMethod;
	UInt32 							filler_1;
	double 							headroomHeight;
	double 							headroomLeftOffset;
	double 							headroomRightOffset;
} API_StairHeadroomData;

typedef struct {
	bool	 						enabled;
	bool	 						filler_1[7];
	double 							width;
	double 							offset;
	double 							horizontalDepth;
	double 							verticalDepth;
	API_OverriddenAttribute			material;
	API_StairDrainSurfaceTypeID		surfaceType;
} API_StairStructureDrainingData;

typedef struct {
	double                          width;
	double 							heightAboveTread;
	API_StairStructHeightMeasureID	heightMeasure;
	UInt32 							filler_1;
} API_SideStairStructData;

typedef struct {
	bool	 						thinning;
	bool	 						materialsChained;
	short 							filler_1;
	API_AttributeIndex 				sideFill;
	API_AttributeIndex 				buildingMaterial;
	short 							filler_2[2];
	double 							monolithThickness;
	double 							bottomOversize;
	API_OverriddenAttribute 	 	topMaterial;
	API_OverriddenAttribute 	 	leftMaterial;
	API_OverriddenAttribute 	 	rightMaterial;
	API_OverriddenAttribute 	 	bottomMaterial;
	API_AttributeIndex				cutLineType;
	short							cutLinePen;
	short							pen;
	API_AttributeIndex				lineType;
	short 							filler_3[2];
	API_OverriddenAttribute 		cutFillPen;
	API_OverriddenAttribute			cutFillBackPen;
	API_AttributeIndex 				surfaceMaterial;
	bool							uniformDrainings;
	bool 							filler_4[3];
	API_StairStructureDrainingData	draining[API_StairDrainSideNum];
} API_MonolithStairStructData;

typedef struct {
	API_AttributeIndex				visibleLineType;
	short							visibleLinePen;
	short							hiddenLinePen;
	API_AttributeIndex				hiddenLineType;
	API_AttributeIndex				visibleFillType;
	short							visibleFillPen;
	short							visibleFillBackgroundPen;
	API_AttributeIndex				hiddenFillType;
	short							hiddenFillPen;
	short							hiddenFillBackgroundPen;
	bool							filler_1[4];
} API_StairStructureSymbolData;

typedef struct {
	API_AttributeIndex				goingLineType;
	short							goingLinePen;
	short							goingNosingLinePen;
	API_AttributeIndex				goingNosingLineType;
	API_AttributeIndex				connectionLineType;
	short							connectionLinePen;
	short							connectionDetailLinePen;
	API_AttributeIndex				connectionDetailLineType;
	API_AttributeIndex				drainingFillType;
	short							drainingFillPen;
	short							drainingFillBackGroundPen;
	API_AttributeIndex				contourLineType;
	short							contourLinePen;
	bool							filler_1[2];
} API_StairMonolithStructureSymbolData;

typedef struct {
	bool							connectionVisible;
	bool							drainingVisible;
	bool							landingLineVisible;
	bool							structureGoingVisible;
	bool							structureGoingNosingVisible;
	bool							filler_1[3];
} API_MonolithPartsVisibilityData;

typedef struct {
	bool							structureVisibility[API_StairStructSymbPartNum][API_StairStructSymbVisibilityNum];
	bool							fillVisibility[API_StairStructSymbPartNum][API_StairStructSymbTypeNum];
	bool							filler_1[4];
	API_MonolithPartsVisibilityData	monolithPartsVisibility[API_StairStructSymbPartNum];
} API_StairStructureComponentSettingsVisibilityOnStory;

typedef struct {
	bool													uniformSymbolRepresentationEnabled;
	bool													filler_1[7];
	API_StairStructureComponentSettingsVisibilityOnStory	structureVisibilityOnStories[API_StairStructSymbRelevantStoriesNum];
} API_StairStructureComponentSettingsVisibility;

typedef struct {
	API_Elem_Head 					head;
	API_RiserPositionID 			riserPosition;
	API_RiserCrossSectID 			crossSect;
	double 							angle;
	double 							offset;
	double 							thickness;
	API_Guid 						owner;
	API_Guid 						libId;
	UInt32 							sequenceNumber;
	UInt32 							subElemId;
	bool	 						visible;
	API_StairPartRoleID				role;
	bool	 						filler_1[3];
} API_StairRiserType;

typedef struct {
	API_Elem_Head 					head;
	bool	 						isCustom;
	bool	 						visible;
	bool	 						filler_1[2];
	API_StairTreadNosingTypeID 		nosingType;
	double 							nosingValue;
	double 							nosingSlant;
	double 							offset;
	double 							thickness;
	API_Guid 						owner;
	API_Guid 						libId;
	UInt32 							sequenceNumber;
	UInt32 							subElemId;
	double 							zOffset;
	API_StairPartRoleID				role;
	bool	 						filler_2[4];
} API_StairTreadType;

typedef struct {
	API_Elem_Head 					head;
	API_Guid 						owner;
	API_Guid 						libId;
	UInt32 							sequenceNumber;
	UInt32 							subElemId;
	bool	 						visible;
	bool	                        isLanding;
	short                           filler_1[3];
	API_StairStructureTypeID		structType;
	API_StairStructBottomTypeID     bottomType;
	double 							horizontalThickness;
	double  						thickness;
	union {
	    API_SideStairStructData			sideStair;
	    API_MonolithStairStructData		monolith;
	    /* Beam supported and cantilevered structures don't have any extra members. */
	} data;
	API_StairPartRoleID				role;
	API_StairStructureSideID		side;
} API_StairStructureType;

typedef struct {
	API_Elem_Head 					head;
	double 							totalHeight;
	double 							topOffset;
	API_LinkToSettings 				linkToSettings;
	short 							relativeTopStory;
	short 							filler_1;
	double							flightWidth;
	UInt32 							stepNum;
	UInt32 							nFPDMarkers;
	UInt32 							nRCPDMarkers;
	UInt32							treadNum;
	double 							riserHeight;
	double							treadDepth;
	bool	 						treadDepthLocked;
	bool	 						totalHeightLocked;
	short 							filler_2;
	double 							walkingLineOffset;
	API_LinePositionID 				walkingLinePosition;
	bool 	 						extraTopTread;
	bool 	 						extraBottomTread;
	bool 	 						finishVisible;
	API_LinePositionID 				baselinePosition;
	double 							baselineOffset;
	API_StairRulesData 				rules;
	API_StairTreadType 				tread[API_StairPartRoleNum];
	API_StairRiserType 				riser[API_StairPartRoleNum];
	API_StairStructureType 			structure[API_StairPartRoleNum][API_StairStructureSideNum];
	API_StairDisplayTypeID			stairDisplayType;
	API_StairLayoutData				fpdLayout;
	API_StairLayoutData				rcpdLayout;
	API_StairNumberingID 			numberingType;
	API_StairDirectionID 			inputDirection;
	API_Plane3D						basePlane;
	bool  							uniformFinish;
	bool  							uniformMonolithAttributes;
	bool  							uniformLeftRightSideSupports[API_StairPartRoleNum];
	bool							uniformDrainings;
	bool  							structureVisibility;
	bool  							filler_3[6];
	API_StairStructureSymbolData					structSymbData[API_StairStructSymbTypeNum][API_StairStructSymbViewNum];
	API_StairMonolithStructureSymbolData			monolithStructureSymbolData[API_StairStructSymbViewNum][API_StairStructSymbPartNum];
	API_StairStructureComponentSettingsVisibility	structureVisibilityOnStories[API_StairStructSymbViewNum];
	API_StairWalkLineSymbPosID		walkLineSymbPos;
	API_StairHeadroomData			stairHeadroomData;
} API_StairType;


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

typedef struct {
	double							position;
	bool							isStretchable;
	bool	 						filler_1[7];
} API_RailingHorizontalPosData;

typedef struct {
	UInt32							bottomRailIndex;
	UInt32							topRailIndex;
} API_RailingVerticalPosData;

typedef struct {
	double 							yOffset;
	double 							zTopOffset;
	double 							zBottomOffset;
	double 							xBeginOffset;
	double 							xEndOffset;
	UInt32 							placeIndex;
	UInt32 							filler_1;
	API_RailingVerticalPosData 		verticalPosition;
} API_RailingFrameData;

typedef struct {
	API_DistribTypeID 				type;
	API_PatternAlignID 				alignment;
	double 							length;
	UInt32							patternAmount;
	UInt32 							filler_1;
} API_RailingDistributionData;

typedef struct {
	API_Elem_Head 					head;
	API_Guid 						owner;
	API_Guid 						symbID;
	API_RailingVerticalPosData 		verticalPosition;
} API_RailingPostType;

typedef struct {
	API_Elem_Head 					head;
	API_Guid 						owner;
	API_Guid 						symbID;
	API_RailingHorizontalPosData	horizontalPosition;
} API_RailingBalusterType;

typedef struct {
	API_Elem_Head 					head;
	API_Guid 						owner;
	API_Guid 						filler_1;
	API_RailingFrameData 			frame;
	API_RailingDistributionData		distribution;
	API_RailingBalusterType 		defBaluster;
	UInt32 							nBalusters;
	UInt32							filler_2;
} API_RailingBalusterSetType;

typedef struct {
	API_Elem_Head 					head;
	API_Guid 						owner;
	API_Guid 						symbID;
} API_RailingFinishType;

typedef struct {
	API_Elem_Head					head;
	API_Guid 						owner;
	API_Guid 						symbID;
	API_RailEndTypeID				type;
	API_RailEndBaseConnectionID		baseConnection;
	double 							firstExtrusionOffset;
	double 							firstExtrusionLength;
	double 							filletRadius;
	API_RailEndFixtureConnectionID	fixtureConnection;
	API_RailEndArcAngleModeID		arcAngleMode;
	double 							arcAngle;
	double 							arcRadius;
	double 							secondExtrusionLength;
	double 							thirdExtrusionLength;
	API_RailEndExtrusionModeID		secondExtrusionMode;
	UInt32 							filler_1;
	API_RailingFinishType 			finishDef;
} API_RailingRailEndType;

typedef struct {
	API_Elem_Head					head;
	API_Guid 						owner;
	API_Guid 						symbID;
	API_RailBaseBaseConnectionID	baseConnection;
	API_RailConnectionTypeID		type;
	double 							railEndOffset;
	double 							railEndFillet;
	double							firstExtrusionLength;
	double							secondExtrusionLength;
	double							filler_1;
	double							horizontalFillet;
	double							gooseneckFillet;
	double							gooseneckOffset;
	double							verticalBottomFillet;
	double							directFillet;
} API_RailingRailConnectionType;

typedef struct {
	API_Elem_Head 					head;
	API_Guid 						owner;
	bool	 						visible;
	bool	 						unifyPatterns;
	bool	 						isStatic;
	bool	 						filler_1[5];
	API_RailingPostType 			defPost;
	API_RailingRailEndType 			defRailEnd;
	API_RailingRailEndType 			defHandrailEnd[2];
	API_RailingRailEndType 			defToprailEnd;
	API_RailingRailConnectionType 	defRailConnection;
	API_RailingRailConnectionType	defHandrailConnection[2];
	API_RailingRailConnectionType	defToprailConnection;
	short 							visiblePostNum;
	short 							filler_2[3];
	double 							elevation;
	double 							postOffset;
	UInt32 							nRailConnections;
	UInt32 							nRailEnds;
	bool 							autoConnectionOffset;
	bool 							tiltedPost;
	bool 							filler_3[6];
	double 							connectionOffset;
	double 							endingOffset;
} API_RailingNodeType;

typedef struct {
	API_Elem_Head 					head;
	API_Guid 						owner;
	API_Guid 						symbID;
	bool	 						visible;
	bool							filler_1[7];
} API_RailingToprailType;

typedef struct {
	API_Elem_Head 					head;
	API_Guid 						owner;
	API_Guid 						symbID;
	bool	 						visible;
	bool	 						doubleHandrail;
	bool							filler_1[6];
	double 							horizontalOffset;
	double 							height;
} API_RailingHandrailType;

typedef struct {
	API_Elem_Head 					head;
	API_Guid 						owner;
	API_Guid 						symbID;
	bool	 						visible;
	bool	 						relative;
	bool							filler_1[6];
	double 							horizontalOffset;
	double 							height;
} API_RailingRailType;

typedef struct {
	API_Elem_Head 					head;
	API_Guid 						owner;
	API_Guid 						symbID;
	double 							doublePostOffset;
	API_RailingVerticalPosData 		verticalPosition;
	API_RailingHorizontalPosData	horizontalPosition;
	short 							postNum;				/* maximum of 2 */
	short 							filler_1[3];
} API_RailingInnerPostType;

typedef struct {
	API_Elem_Head 					head;
	API_Guid 						owner;
	API_Guid 						symbID;
	bool	 						visible;
	bool							filler_1[7];
	API_RailingFrameData 			frame;
} API_RailingPanelType;

typedef struct {
	API_Elem_Head 					head;
	API_Guid 						owner;
	API_RailingDistributionData		distribution;
	API_RailingPanelType			defPanel;
	API_RailingBalusterSetType 		defBalusterSet;
	API_RailingInnerPostType		defInnerPost;
	UInt32 							nPanels;
	UInt32 							nBalusterSets;
	UInt32 							nInnerPosts;
	UInt32 							filler_1;
} API_RailingPatternType;

typedef struct {
	API_Elem_Head 					head;
	API_Guid 						owner;
	bool	 						visible;
	bool							relativeSkewingAngle;
	bool							filler_1[2];
	API_RailingRefLineLocationID	refLineLocation;
	double 							height;
	double 							yOffset;
	double 							zOffset;
	double 							slantAngle;
	double 							skewAngle;
	API_RailingPatternType 			defPattern;
	API_RailingHandrailType 		defDefaultHandrail;
	API_RailingHandrailType 		defHandrails;
	API_RailingToprailType 			defToprail;
	API_RailingRailType 			defDefaultRail;				/* default rail data for the default rail */
	API_RailingRailType 			defRails;					/* default rail data for additional rails */
} API_RailingSegmentType;

typedef struct {
	API_Elem_Head 					head;
	API_LinkToSettings 				linkToSettings;
	API_RailingNodeType 			defNode;
	API_RailingSegmentType			defSegment;
	API_StoryVisibility 			visibility;
	bool	 						isAutoOnStoryVisibility;
	bool	 						filler_1[3];
	UInt32							nVertices;
	short  							referenceLinePen;
	short  							contourPen;
	UInt32 							nNodes;
	UInt32 							nSegments;
	UInt32 							filler_2;
	double 							bottomOffset;
} API_RailingType;

// =============================================================================
// Opening
//
// =============================================================================

typedef enum {
	API_OpeningSymbolic,
	API_OpeningSymbolicCut,
	API_OpeningSymbolicOverhead
} API_OpeningFloorPlanDisplayModeTypeID;

typedef enum {
	API_OpeningDisconnected,
	API_OpeningConnected
} API_OpeningFloorPlanConnectionModeTypeID;

typedef struct {
	bool					useLineOfCutElements;
	bool					filler_1;
	short					linePenIndex;
	API_AttributeIndex		lineIndex;
} API_OpeningCutSurfacesParameters;

typedef enum {
	API_OpeningHideBorder,
	API_OpeningShowUncutBorder,
	API_OpeningShowOverheadBorder
} API_OpeningFloorPlanOutlinesStyleTypeID;

typedef struct {
	API_OpeningFloorPlanOutlinesStyleTypeID	outlinesStyle;
	bool						useLineOfCutElements;
	bool						filler_1;
	short						filler_2;
	API_AttributeIndex			uncutLineIndex;
	API_AttributeIndex			overheadLineIndex;
	short						uncutLinePenIndex;
	short						overheadLinePenIndex;
	short						filler_3[2];
} API_OpeningOutlinesParameters;

typedef struct {
	bool							useCoverFills;
	bool							useFillsOfCutElements;
	short							filler_1;
	API_AttributeIndex				coverFillIndex;
	short							coverFillPenIndex;
	short							coverFillBackgroundPenIndex;
	API_HatchOrientationTypeID		coverFillOrientation;
} API_OpeningCoverFillsParameters;

typedef struct {
	bool				showReferenceAxis;
	bool				filler_1;
	short				referenceAxisPenIndex;
	API_AttributeIndex	referenceAxisLineTypeIndex;
	double				referenceAxisOverhang;
} API_OpeningReferenceAxisParameters;

typedef struct {
	API_OpeningFloorPlanDisplayModeTypeID		floorPlanDisplayMode;
	API_OpeningFloorPlanConnectionModeTypeID	connectionMode;
	API_OpeningCutSurfacesParameters			cutSurfacesParameters;
	API_OpeningOutlinesParameters				outlinesParameters;
	API_OpeningCoverFillsParameters				coverFillsParameters;
	API_CoverFillTransformation					coverFillTransformation;
	API_OpeningReferenceAxisParameters			referenceAxisParameters;
	double										filler_1;
} API_OpeningFloorPlanParameters;

typedef enum {
	API_OpeningBasePolygonRectangular,
	API_OpeningBasePolygonCircular,
	API_OpeningBasePolygonCustom
} API_OpeningBasePolygonTypeTypeID;

typedef enum {
	API_OpeningForcedVertical,
	API_OpeningForcedHorizontal,
	API_OpeningAligned,
	API_OpeningFree
} API_OpeningConstraintTypeID;

typedef enum {
	API_OpeningLimitInfinite,
	API_OpeningLimitFinite,
	API_OpeningLimitHalfInfinite
} API_OpeningLimitTypeTypeID;

typedef enum {
	API_OpeningLinked,
	API_OpeningNotLinked
} API_OpeningLinkedStatusTypeID;

typedef struct {
	API_OpeningBasePolygonTypeTypeID		basePolygonType;
	short									filler_1[2];
	double									width;					// valid only if basePolygonType != API_OpeningBasePolygonCustom
	double									height;					// valid only if basePolygonType != API_OpeningBasePolygonCustom
	API_OpeningConstraintTypeID				constraint;
	API_AnchorID							anchor;
	double									anchorAltitude;			// valid only if constraint == API_OpeningForcedHorizontal || constraint == API_OpeningAligned
	API_OpeningLimitTypeTypeID				limitType;
	short									filler_2[2];
	double									extrusionStartOffset;	// valid only if limitType != API_OpeningLimitInfinite
	double									finiteBodyLength;		// valid only if limitType == API_OpeningLimitFinite
	API_OpeningLinkedStatusTypeID			linkedStatus;			// valid only if basePolygonType != API_OpeningBasePolygonCustom
	short									filler_3[2];
} API_OpeningExtrusionParameters;

typedef struct {
	API_Plane3D							frame;
	API_OpeningExtrusionParameters		parameters;
	API_Polygon							customBasePolygon;		// reserved
	double								filler_1;
} API_OpeningExtrusionGeometryData;

typedef struct {
	API_Elem_Head 						head;
	API_Guid							owner;					// relativeCoordinateSystemSource
	API_OpeningFloorPlanParameters		floorPlanParameters;
	API_OpeningExtrusionGeometryData	extrusionGeometryData;
	double								filler_1;
} API_OpeningType;

// =============================================================================
// ExternalElem
//
// =============================================================================

constexpr USize API_ExternalElemDataSize = 1024;

struct API_ExternalElemType {
	API_Elem_Head	head;
	char			externalElemData[API_ExternalElemDataSize];
};


// =============================================================================
// General element
//
// =============================================================================

typedef union {
	API_Elem_Head						header;

	API_WallType						wall;
	API_ColumnType						column;
	API_BeamType						beam;
	API_WindowType						window;
	API_DoorType						door;
	API_ObjectType						object;
	API_LampType						lamp;
	API_SlabType						slab;
	API_RoofType						roof;
	API_MeshType						mesh;

	API_DimensionType					dimension;
	API_RadialDimensionType				radialDimension;
	API_LevelDimensionType				levelDimension;
	API_AngleDimensionType				angleDimension;

	API_TextType						text;
	API_LabelType						label;
	API_ZoneType						zone;

	API_HatchType						hatch;
	API_LineType						line;
	API_PolyLineType					polyLine;
	API_ArcType							arc;
	API_CircleType						circle;
	API_SplineType						spline;
	API_HotspotType						hotspot;
	API_PictureType						picture;

	API_CutPlaneType					cutPlane;
	API_ElevationType					elevation;
	API_InteriorElevationType			interiorElevation;
	API_CameraType						camera;
	API_CamSetType						camset;

	API_DrawingType						drawing;
	API_SectElemType					sectElem;
	API_DetailType						detail;
	API_WorksheetType					worksheet;
	API_HotlinkType						hotlink;

	API_CurtainWallType					curtainWall;
	API_CWSegmentType					cwSegment;
	API_CWFrameType						cwFrame;
	API_CWPanelType						cwPanel;
	API_CWJunctionType					cwJunction;
	API_CWAccessoryType					cwAccessory;
	API_ShellType						shell;
	API_MorphType						morph;
	API_SkylightType					skylight;
	API_ChangeMarkerType				changeMarker;

	API_StairType 						stair;
	API_StairRiserType 					stairRiser;
	API_StairTreadType 					stairTread;
	API_StairStructureType				stairStructure;

	API_RailingType						railing;
	API_RailingToprailType				railingToprail;
	API_RailingHandrailType				railingHandrail;
	API_RailingRailType					railingRail;
	API_RailingRailEndType				railingToprailEnd;
	API_RailingRailEndType				railingHandrailEnd;
	API_RailingRailEndType				railingRailEnd;
	API_RailingFinishType 				railingEndFinish;
	API_RailingRailConnectionType		railingToprailConnection;
	API_RailingRailConnectionType		railingHandrailConnection;
	API_RailingRailConnectionType		railingRailConnection;
	API_RailingPostType					railingPost;
	API_RailingInnerPostType			railingInnerPost;
	API_RailingBalusterSetType			railingBalusterSet;
	API_RailingBalusterType				railingBaluster;
	API_RailingPanelType				railingPanel;
	API_RailingNodeType					railingNode;
	API_RailingSegmentType				railingSegment;
	API_RailingPatternType				railingPattern;

	API_ColumnSegmentType				columnSegment;
	API_BeamSegmentType					beamSegment;
	API_OpeningType						opening;
	API_ExternalElemType				externalElem;
} API_Element;


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
#define APIMemoMask_TextContent					0x0000000000000080	// UTF8
#define APIMemoMask_Paragraph					0x0000000000000100
#define APIMemoMask_TextContentUni				0x0000000000000200	// UTF16
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

typedef struct {
	API_Coord						**coords;
	Int32							**pends;
	API_PolyArc						**parcs;
	UInt32							**vertexIDs;
	UInt32							**edgeIDs;
	UInt32							**contourIDs;
	API_AddParType					**params;
	API_Gable						**gables;
	API_EdgeTrim					**edgeTrims;
	double							**meshPolyZ;
	API_MeshLevelCoord				**meshLevelCoords;
	Int32							**meshLevelEnds;
	API_DimElem						**dimElems;
	API_SplineDir					**bezierDirs;
	char							**textContent;
	short							**textLineStarts;			// output only
	API_Beam_Hole					**beamHoles;
	API_LinkType					**linkList;
	char							**pictHdl;
	API_ParagraphType				**paragraphs;

	GSPtr							drawingData;
	ProfileVectorImage				*customOrigProfile;
	ProfileVectorImage				*stretchedProfile;

	GSPtr							customParams;

	API_SectionSegment				*intElevSegments;
	API_Coord						*sectionSegmentMainCoords;
	API_Coord						*sectionSegmentDistCoords;
	API_Coord						*sectionSegmentDepthCoords;

	API_Guid						*wallWindows;				// output only (obsolete, use ACAPI_Element_GetConnectedElements instead)
	API_Guid						*wallDoors;					// output only (obsolete, use ACAPI_Element_GetConnectedElements instead)

	API_GridMesh					*cWSegGridMesh;
	API_CWContourData				*cWSegContour;
	API_CWSegmentPatternData		cWSegPrimaryPattern;
	API_CWSegmentPatternData		cWSegSecondaryPattern;
	API_CWSegmentPatternCellData 	*cWSegPatternCells;
	API_CWSegmentType				*cWallSegments;
	API_CWFrameType					*cWallFrames;
	API_CWFrameType					*cWallFrameDefaults;
	API_CWPanelType					*cWallPanels;
	API_CWPanelGridIDTable			*cWallPanelGridIDTable;
	API_CWPanelType					*cWallPanelDefaults;
	API_CWJunctionType				*cWallJunctions;
	API_CWAccessoryType				*cWallAccessories;

	API_StairRiserType				*stairRisers;
	API_StairTreadType				*stairTreads;
	API_StairStructureType			*stairStructures;

	API_StairBoundaryData			stairBoundary[2]; 				// stair boundaries (0 - left, 1 - right)
	API_StairPolylineData 			stairBaseLine;
	API_StairPolylineData 			stairWalkingLine;
	API_StairPolylineData 			stairCustomWalkLine;
	API_StairPolylineData 			stairCenterWalkLine;

	API_RailingNodeType 			*railingNodes;
	API_RailingSegmentType 			*railingSegments;
	API_RailingPostType 			*railingPosts;
	API_RailingRailEndType 			*railingRailEnds;
	API_RailingRailConnectionType 	*railingRailConnections;
	API_RailingRailEndType 			*railingHandrailEnds;
	API_RailingRailConnectionType 	*railingHandrailConnections;
	API_RailingRailEndType 			*railingToprailEnds;
	API_RailingRailConnectionType 	*railingToprailConnections;
	API_RailingRailType 			*railingRails;
	API_RailingToprailType 			*railingToprails;
	API_RailingHandrailType 		*railingHandrails;
	API_RailingPatternType 			*railingPatterns;
	API_RailingInnerPostType		*railingInnerPosts;
	API_RailingPanelType			*railingPanels;
	API_RailingBalusterSetType 		*railingBalusterSets;
	API_RailingBalusterType 		*railingBalusters;

	double 							**polyZCoords;

	API_RoofEdgeTypeID				*roofEdgeTypes;
	API_OverriddenAttribute			*sideMaterials;

	API_Coord						**additionalPolyCoords;			// polyroof pivot polygon data or zone reference polygon
	Int32							**additionalPolyPends;
	API_PolyArc						**additionalPolyParcs;
	UInt32							**additionalPolyVertexIDs;		// not used for zone reference polygon
	UInt32							**additionalPolyEdgeIDs;		// not used for zone reference polygon
	UInt32							**additionalPolyContourIDs;		// not used for zone reference polygon

	API_PivotPolyEdgeData			*pivotPolyEdges;

	API_ShellShapeData				shellShapes[2];				// shell profile data
	API_ShellContourData			*shellContours;				// shell body and hole contours

	Modeler::MeshBody				*morphBody;
	API_OverriddenAttribute			*morphMaterialMapTable;

	GS::UniString					*elemInfoString;			// it is available for elems and default elem

	API_BeamSegmentType				*beamSegments;
	API_ColumnSegmentType			*columnSegments;
	API_AssemblySegmentCutData		*assemblySegmentCuts;
	API_AssemblySegmentSchemeData	*assemblySegmentSchemes;
	API_AssemblySegmentProfileData	*assemblySegmentProfiles;

	GS::Any							*externalElemData;
} API_ElementMemo;


// ====================================================================================
// Helper struct for easier sub element handling (e.g. markers [section, detail etc.])
//
// ====================================================================================


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

typedef struct {
	API_Element						subElem;					// Subelement
	API_Element						mask;						// Subelement Mask
	API_ElementMemo					memo;						// Subelement Memo

	API_SubElementType				subType;					// Subelement Type
	Int32							subIndex;					// Subelement Index (Interior Elevation, Curtain Wall, and Railing)
	UInt32 							subSubIndex;				// Second-Level Subelement Index (Railing)
	UInt32 							subElemFlags;				// Subelement Flags (Stair)

	Int32							filler_1;
} API_SubElement;

// =============================================================================
// Custom data stored into elements
//
// =============================================================================

#define APIUserDataFlag_FillWith	0x00000004					// inject userdata into element from default
#define APIUserDataFlag_Pickup		0x00000008					// copy userdata into default at element parameter transfer

typedef struct {
	short							dataVersion;				// data version
	unsigned short					platformSign;				// byte ordering in data storage
	GSFlags							flags;						// APIUserDataFlag_...
	Int32							filler_1;
	GSHandle						dataHdl;					// user specified data
} API_UserData, API_ElementUserData, API_AttributeUserData;


// =============================================================================
// Element relations
//
// =============================================================================

typedef struct {
	API_Guid						guid;
	Int32							roomEdge;					// index of the room polygon edge adjacent to the wall
	Int32							filler;
	double							tBeg;
	double							tEnd;
} API_WallPart, API_CWSegmentPart;

typedef struct {
	API_Coord						**coords;					// polygon of niche
	Int32							**pends;
	API_PolyArc						**parcs;
	double							height;						// niche height
} API_Niche;

typedef struct {
	API_Guid						guid;
	Int32							filler[2];
	double							tBeg;
	double							tEnd;
} API_BeamPart;

typedef struct {
	GS::HashTable<API_ElemType, GS::Array<API_Guid>>	elementsGroupedByType;
	GS::Array<API_WallPart>								wallPart;
	GS::Array<API_BeamPart>								beamPart;
	GS::Array<API_CWSegmentPart>						cwSegmentPart;
	GS::Array<API_Niche>								niches;
} API_RoomRelation;


typedef struct {
	API_Guid	guid;
	bool		conWithBeg;
	bool		filler_1[7];
} API_ConnectionGuidItem;


typedef struct {
	API_Coord						**coords;
	Int32							**pends;
	API_PolyArc						**parcs;
	Int32							filler_1;
	API_Polygon						connPoly;					// modified outline

	API_ConnectionGuidItem			**conBeg;					// list of walls connected to the beg point
	API_ConnectionGuidItem			**conEnd;					// list of walls connected to the end point
	API_ConnectionGuidItem			**conRef;					// list of walls connected to the reference line
	API_ConnectionGuidItem			**con;						// list of walls connected by reference line on the end points
																// +/- values: connection with beg/end point
	API_ConnectionGuidItem			**conX;
	Int32							filler_2[5];

	Int32							nConBeg;
	Int32							nConEnd;
	Int32							nConRef;
	Int32							nCon;
	Int32							nConX;
	Int32							filler_3[5];
} API_WallRelation;


typedef struct {
	API_Coord							**coords;
	Int32								**pends;
	API_PolyArc							**parcs;
	Int32								filler_1;
	API_Polygon							connPoly;				// modified outline

	GS::Array<API_ConnectionGuidItem>	*conBeg;				// list of beam segments connected to the beg point
	GS::Array<API_ConnectionGuidItem>	*conEnd;				// list of beam segments connected to the end point
	GS::Array<API_ConnectionGuidItem>	*conRef;				// list of beam segments connected to the reference line
	GS::Array<API_ConnectionGuidItem>	*con;					// list of beam segments connected by reference line on the end points
																// +/- values: connection with beg/end point
	GS::Array<API_ConnectionGuidItem>	*conX;

	double								filler_2[8];
} API_BeamSegmentRelation;


typedef struct {
	API_Coord							**coords;
	Int32								**pends;
	API_PolyArc							**parcs;
	Int32								filler_1;
	API_Polygon							connPoly;				// modified outline

	GS::Array<API_ConnectionGuidItem>	*conBeg;				// list of beams connected to the beg point
	GS::Array<API_ConnectionGuidItem>	*conEnd;				// list of beams connected to the end point
	GS::Array<API_ConnectionGuidItem>	*conRef;				// list of beams connected to the reference line
	GS::Array<API_ConnectionGuidItem>	*con;					// list of beams connected by reference line on the end points
																// +/- values: connection with beg/end point
	GS::Array<API_ConnectionGuidItem>	*conX;

	GS::Array<API_BeamSegmentRelation>	*segmentRelations;

	Int32								filler_2[5];
	Int32								filler_3[5];
} API_BeamRelation;


typedef struct {
	API_Guid						fromRoom;
	API_Guid						toRoom;
	double							filler[8];
} API_CWPanelRelation, API_SkylightRelation, API_WindowRelation, API_DoorRelation;

typedef struct {
	GS::Array<API_Guid>*			rooms;
} API_RoofRelation, API_ShellRelation;


// =============================================================================
// 3D information
//
// =============================================================================

typedef struct {
	UInt32							fElemIdx;
	UInt32							fBodyIdx;
	UInt32							lElemIdx;
	UInt32							lBodyIdx;
	Int32							fbody;
	Int32							lbody;
	Int32							flight;
	Int32							llight;
	Int32							filler_1[2];
	API_Box3D						bounds;
} API_ElemInfo3D;


// =============================================================================
// ShapePrims parameters
//
// =============================================================================

typedef struct {
	bool							dontClip;
	bool							allStories;
	Geometry::Polygon2D*			polygon;
} API_ShapePrimsParams;


// =============================================================================
// Quantities
//
// =============================================================================

typedef struct {
	double							volume;
	double							volume_cond;
	double							volumeASkin;
	double							volumeBSkin;
	double							volumeASkin_cond;
	double							volumeBSkin_cond;
	double							surface1;
	double							surface2;
	double							surface3;
	double							surface1_cond;
	double							surface2_cond;
	double							length;
	double							windowsSurf;
	double							doorsSurf;
	double							emptyholesSurf;
	double							filler_0;			// columnsVolume never calculated
	Int32							columnsNumber;
	Int32							filler_1;
	double							windowsWidth;
	double							doorsWidth;
	double							minHeight;
	double							maxHeight;
	double							minHeightASkin;
	double							maxHeightASkin;
	double							minHeightBSkin;
	double							maxHeightBSkin;
	double							centerLength;
	double							area;
	double							perimeter;
	double							grossVolume;
	double							grossSurf1;
	double							grossSurf2;
	double							emptyHolesVolume;
	double							emptyHolesSurf1;
	double							emptyHolesSurf2;

	double							length12;
	double							length34;
	double							length12_cond;
	double							length34_cond;
	double							insuThickness;
	double							airThickness;
	double							skinAThickness;
	double							skinBThickness;
	double							refLineLength;
} API_WallQuantity;

typedef struct {
	double							coreSurface;
	double							veneSurface;
	double							coreVolume;
	double							veneVolume;
	double							minHeight;
	double							maxHeight;
	double							perimeter;
	double							area;
	double							coreGrossSurf;
	double							veneGrossSurf;
	double							crossSectionAreaCutBegin;
	double							crossSectionAreaCutEnd;
	double							coreGrossVolume;
	double							veneGrossVolume;
	double							coreTopSurf;
	double							coreBotSurf;
	double							veneTopSurf;
	double							veneBotSurf;
	double							coreGrossTopBotSurf;
	double							veneGrossTopBotSurf;
	double							filler_1[2];
} API_ColumnQuantity;

typedef struct {
	double							veneerSideSurface;
	double							veneerBottomSurface;
	double							veneerTopSurface;
	double							veneerGrossSurface;
	double							veneerGrossTopSurface;
	double							veneerGrossBottomSurface;

	double							coreGrossSurface;
	double							coreGrossTopSurface;
	double							coreGrossBottomSurface;

	double							grossVolume;
	double							coreGrossVolume;
	double							veneerGrossVolume;

	double							coreNetBottomSurface;
	double							coreNetSurface;
	double							coreNetTopSurface;

	double							coreVolume;
	double							veneerNetVolume;

	double							length;
	double							area;
	double							volume;

	double							crossSectionAreaCutBegin;
	double							crossSectionAreaCutEnd;

	double							minHeight;
	double							maxHeight;
	double							height;
	double							filler_1[8];
} API_ColumnSegmentQuantity;

typedef struct {
	double							area;
	double							rightLength;
	double							leftLength;
	double							bottomSurface;
	double							topSurface;
	double							edgeSurfaceLeft;
	double							edgeSurfaceRight;
	double							edgeSurface;
	double							holesSurface;
	double							holesEdgeSurface;
	Int32							holesNumber;
	Int32							filler_1;
	double							crossSectionAreaCutBegin;
	double							crossSectionAreaCutEnd;
	double							volume;
	double							volume_cond;
	double							holesVolume;
	double							filler_2[6];
} API_BeamQuantity;

typedef struct {
	double							endSurface;
	double							leftSurface;
	double							rightSurface;
	double							bottomSurface;
	double							topSurface;

	double							length;
	double							leftLength;
	double							rightLength;

	double							crossSectionAreaCutBegin;
	double							crossSectionAreaCutEnd;

	double							volume;

	Int32							holesNumber;
	Int32							filler_1;

	double							holesSurface;
	double							holesEdgeSurface;
	double							holesVolume;
	double							filler_2[8];
} API_BeamSegmentQuantity;

typedef struct {
	double							width1;						// Reveal Side Width
	double							width2;						// Opposite Side Width
	double							height1;					// Reveal Side Height
	double							height2;					// Opposite Side Height
	double							surface1;					// Reveal Side Surface
	double							surface2;					// Opposite Side Surface
	double							nWidth1;					// Reveal Side Nominal Width
	double							nWidth2;					// Opposite Side Nominal Width
	double							nHeight1;					// Reveal Side Nominal Height
	double							nHeight2;					// Opposite Side Nominal Height
	double							nSurface1;					// Reveal Side Nominal Surface
	double							nSurface2;					// Opposite Side Nominal Surface
	double							volume;						// Volume
	double							grossSurf;					// Gross Surface
	double							grossVolume;				// Gross Volume

	double							surface;					// Surface
	double							sillHeight;					// Sill Height
	double							sillHeight1;				// Reveal Side Sill height
	double							sillHeight2;				// Opposite Side Sill height
	double							headHeight;					// Head Height
	double							headHeight1;				// Reveal Side Head Height
	double							headHeight2;				// Opposite Side Head Height
	double							sillHeight3;				// Sill Height
	double							headHeight3;				// Head Height
	double							filler_1[7];
} API_WindowQuantity, API_DoorQuantity;

typedef struct {
	double							openingWidth;
	double							openingHeight;
	double							openingSurface;
	double							openingVolume;
	double							sillHeight;
	double							headerHeight;
	double							filler_1[2];
} API_SkylightQuantity;

typedef struct {
	double							surface;
	double							volume;
	double							filler_1[8];
} API_ObjectQuantity, API_LightQuantity;

typedef struct {
	double							surface;
	double							volume;
	double							floorPlanArea;
	double							floorPlanPerimeter;
	double							baseLevel;
	double							baseHeight;
	double							wholeHeight;
	UInt32							nodesNr;
	UInt32							edgesNr;
	UInt32							hiddenEdgesNr;
	UInt32							softEdgesNr;
	UInt32							visibleEdgesNr;
	UInt32							facesNr;
	double							filler_1[8];
} API_MorphQuantity;

typedef struct {
	double							bottomSurface;
	double							topSurface;
	double							edgeSurface;
	double							bottomSurface_cond;
	double							topSurface_cond;
	double							volume;
	double							volume_cond;
	double							perimeter;
	double							holesSurf;
	double							holesPrm;
	double							grossBotSurf;
	double							grossTopSurf;
	double							grossEdgeSurf;
	double							grossVolume;
	double							grossBotSurfWithHoles;
	double							grossTopSurfWithHoles;
	double							grossEdgeSurfWithHoles;
	double							grossVolumeWithHoles;
	double							filler_1[1];
} API_SlabQuantity;

typedef struct {
	double							bottomSurface;
	double							topSurface;
	double							edgeSurface;
	double							volume;
	double							perimeter;
	double							holesSurf;
	double							holesPrm;
	double							projectedArea;
	double							filler_1[8];
} API_MeshQuantity;

typedef struct {
	double							bottomSurface;
	double							topSurface;
	double							edgeSurface;
	double							bottomSurface_cond;
	double							topSurface_cond;
	double							volume;
	double							volume_cond;
	double							perimeter;
	double							holesSurf;
	double							holesPrm;
	double							grossBotSurf;
	double							grossTopSurf;
	double							grossEdgeSurf;
	double							contourArea;
	double							grossVolume;
	double							insuThickness;
	double							ridgesLength;
	double							valleysLength;
	double							gablesLength;
	double							hipsLength;
	double							eavesLength;
	double							peaksLength;
	double							sideWallConLength;
	double							endWallConLength;
	double							domeConLength;
	double							hollowConLength;
	double							openingSurf;
	Int32							numOfHoles;
	Int32							numOfSkylight;
	Int32							filler_1;
	Int32							filler_2;
} API_RoofQuantity;

typedef struct {
	double							referenceSurface;
	double							oppositeSurface;
	double							edgeSurface;
	double							referenceSurface_cond;
	double							oppositeSurface_cond;
	double							volume;
	double							volume_cond;
	double							perimeter;
	double							holesSurf;
	double							holesPrm;
	double							grossReferenceSurf;
	double							grossOppositeSurf;
	double							grossEdgeSurf;
	double							grossVolume;
	double							insuThickness;
	double							ridgesLength;
	double							valleysLength;
	double							gablesLength;
	double							hipsLength;
	double							eavesLength;
	double							peaksLength;
	double							sideWallConLength;
	double							endWallConLength;
	double							domeConLength;
	double							hollowConLength;
	double							openingSurf;
	double							floorplanArea;
	Int32							numOfHoles;
	Int32							numOfSkylight;
	Int32							filler_1;
	Int32							filler_2;
} API_ShellQuantity;

typedef struct {
	double							surface;
	double							perimeter;
	double							holesPrm;
	double							holesSurf;
	double							filler_1[8];
} API_HatchQuantity;

typedef struct {
	double							area;
	double							perimeter;
	double							holesPrm;
	double							wallsPrm;
	Int32							allCorners;
	Int32							concaveCorners;
	double							wallsSurf;
	double							doorsWidth;
	double							doorsSurf;
	double							windowsWidth;
	double							windowsSurf;
	double							baseLevel;
	double							floorThick;
	double							height;
	double							netarea;
	double							netperimeter;
	double							volume;
	double							reducementArea;
	double							calcArea;
	double							totalExtrArea;
	double							reducedExtrArea;
	double							lowExtrArea;
	double							wallExtrArea;
	double							curtainWallExtrArea;
	double							coluExtrArea;
	double							fillExtrArea;
	double							insetTopSurf;
	double							insetBackSurf;
	double							insetSideSurf;
	double							filler[8];
} API_ZoneAllQuantity;

typedef struct {
	double							framesLength;
	double							contourFramesLength;
	double							mainaxisFramesLength;
	double							secaxisFramesLength;
	double							customFramesLength;
	double							panelsSurface;
	double							panelsSurfaceN;
	double							panelsSurfaceS;
	double							panelsSurfaceE;
	double							panelsSurfaceW;
	double							panelsSurfaceNE;
	double							panelsSurfaceNW;
	double							panelsSurfaceSE;
	double							panelsSurfaceSW;
	double							contourSurface;
	double							boundarySurface;
	double							length;
	double							height;
	double							slantAngle;
	UInt32							numOfPanels;
	UInt32							filler_1;
	double							filler_2[6];
} API_CurtainWallQuantity;

typedef struct {
	GS::uchar_t						typeText[API_UniLongNameLen];
	GS::uchar_t						categoryText[API_UniLongNameLen];
	double							direction;
	double							width;
	double							depth;
	double							length;
	API_AttributeIndex				material;
	short							position;
	short							filler_1[13];
} API_CWFrameQuantity;

typedef struct {
	GS::uchar_t						typeText[API_UniLongNameLen];
	double							vertDirection;
	double							horDirection;
	double							thickness;
	double							surface;
	double							grossSurface;
	double							perimeter;
	double							grossPerimeter;
	API_AttributeIndex				material_outer;
	API_AttributeIndex				material_inner;
	API_AttributeIndex				material_cut;
	short							function;
	short							filler_1;
	double							width;
	double							nominalWidth;
	double							height;
	double							nominalHeight;
	GS::uchar_t						orientationText[API_UniLongNameLen];
	double							filler[4];
} API_CWPanelQuantity;

typedef struct {
	GS::uchar_t						typeText[API_UniLongNameLen];
	double							filler[8];
} API_CWJunctionQuantity;

typedef struct {
	GS::uchar_t						typeText[API_UniLongNameLen];
	double							width;
	double							height;
	double							length;
	double							filler[4];
} API_CWAccessoryQuantity;

typedef struct
{
	double							area;
	double							volume;
	double							height;
	double							walklineLength;
	double							gradient;
	Int32							numOfRisers;
	Int32							numOfTreads;
} API_StairQuantity;

typedef struct
{
	double							area;
	double							volume;
	double							thickness;
	double							elevation;
	Int32							stepIndex;
	Int32							filler;
} API_StairTreadQuantity;

typedef struct {
	double							volume;
	double							slantAngle;
	double							width;
	double							frontArea;
	Int32							stepIndex;
	Int32							filler;
} API_StairRiserQuantity;

typedef struct {
	double							volume;
	double							height;
	double							thickness;
	double							length3D;
} API_StairStructureQuantity;

typedef struct {
	double							area;
	double							volume;
	double							length3D;
} API_RailingQuantity;

typedef struct
{
	double							volume;
	double							length3D;
} API_RailingToprailQuantity;

typedef struct
{
	double							volume;
	double							length3D;
} API_RailingHandrailQuantity;

typedef struct
{
	double							volume;
	double							length3D;
} API_RailingRailQuantity;

typedef struct
{
	double							volume;
	double							length3D;
} API_RailingToprailEndQuantity;

typedef struct
{
	double							volume;
	double							length3D;
} API_RailingHandrailEndQuantity;

typedef struct
{
	double							volume;
	double							length3D;
} API_RailingRailEndQuantity;

typedef struct
{
	double							volume;
	double							length3D;
} API_RailingToprailConnectionQuantity;

typedef struct
{
	double							volume;
	double							length3D;
} API_RailingHandrailConnectionQuantity;

typedef struct
{
	double							volume;
	double							length3D;
} API_RailingRailConnectionQuantity;

typedef struct
{
	double							volume;
	double							length3D;
} API_RailingPostQuantity;

typedef struct
{
	double							volume;
	double							length3D;
} API_RailingInnerPostQuantity;

typedef struct
{
	double							volume;
	double							length3D;
} API_RailingBalusterQuantity;

typedef struct
{
	double							volume;
} API_RailingPanelQuantity;

typedef struct
{
	double							volume;
	double							length3D;
} API_RailingSegmentQuantity;

typedef union {
	API_WallQuantity						wall;
	API_ColumnQuantity						column;
	API_BeamQuantity						beam;
	API_DoorQuantity						door;
	API_WindowQuantity						window;
	API_SkylightQuantity					skylight;
	API_ObjectQuantity						symb;
	API_LightQuantity						light;
	API_SlabQuantity						slab;
	API_MeshQuantity						mesh;
	API_RoofQuantity						roof;
	API_ShellQuantity						shell;
	API_MorphQuantity						morph;
	API_HatchQuantity						hatch;
	API_ZoneAllQuantity						zone;
	API_CurtainWallQuantity					cw;
	API_CWFrameQuantity						cwFrame;
	API_CWPanelQuantity						cwPanel;
	API_CWJunctionQuantity					cwJunction;
	API_CWAccessoryQuantity					cwAccessory;
	API_StairQuantity						stair;
	API_StairRiserQuantity					stairRiser;
	API_StairTreadQuantity					stairTread;
	API_StairStructureQuantity				stairStructure;
	API_RailingQuantity						railing;
	API_RailingToprailQuantity				railingToprail;
	API_RailingHandrailQuantity				railingHandrail;
	API_RailingRailQuantity					railingRail;
	API_RailingToprailEndQuantity			railingToprailEnd;
	API_RailingHandrailEndQuantity			railingHandrailEnd;
	API_RailingRailEndQuantity				railingRailEnd;
	API_RailingToprailConnectionQuantity	railingToprailConnection;
	API_RailingHandrailConnectionQuantity	railingHandrailConnection;
	API_RailingRailConnectionQuantity		railingRailConnection;
	API_RailingPostQuantity					railingPost;
	API_RailingInnerPostQuantity			railingInnerPost;
	API_RailingBalusterQuantity				railingBaluster;
	API_RailingPanelQuantity				railingPanel;
	API_RailingSegmentQuantity				railingSegment;
	API_ColumnSegmentQuantity				columnSegment;
	API_BeamSegmentQuantity					beamSegment;
} API_ElementQuantity;

typedef struct {
	double							minOpeningSize;				// minimum opening size to reduce Wall
	bool							filler_1[4];
	Int32							filler_2;
	double							filler_3[6];
} API_QuantityPar;

typedef struct {
	API_Guid						subElementGuid;
} API_CompositeId;

typedef struct {
	API_CompositeId					compositeId;
	double							volumes;
	double							projectedArea;
	API_AttributeIndex				buildMatIndices;
	short							flags;
} API_CompositeQuantity;

typedef struct {
	API_ElemPartId					partId;
	API_ElementQuantity				quantity;
} API_ElemPartQuantity;

typedef struct {
	API_ElemPartId						partId;
	GS::Array<API_CompositeQuantity>	composites;
} API_ElemPartCompositeQuantity;

typedef struct {
	API_Guid						elemGUID;
	API_AttributeIndex				materialIndex;
	API_AttributeIndex				buildMatIdx;
	double							exposedSurface;
} API_ElemPartSurfaceQuantity;

class API_Quantities {
public:
	API_ElementQuantity							*elements;
	GS::Array <API_CompositeQuantity>			*composites;
	GS::Array <API_ElemPartQuantity>			*elemPartQuantities;
	GS::Array <API_ElemPartCompositeQuantity>	*elemPartComposites;

	API_Quantities () : elements (nullptr), composites (nullptr), elemPartQuantities (nullptr), elemPartComposites (nullptr) {}
};

typedef struct {
	API_WallQuantity						wall;
	API_ColumnQuantity						column;
	API_BeamQuantity						beam;
	API_DoorQuantity						door;
	API_WindowQuantity						window;
	API_SkylightQuantity					skylight;
	API_ObjectQuantity						symb;
	API_LightQuantity						light;
	API_SlabQuantity						slab;
	API_MeshQuantity						mesh;
	API_RoofQuantity						roof;
	API_ShellQuantity						shell;
	API_MorphQuantity						morph;
	API_HatchQuantity						hatch;
	API_ZoneAllQuantity						zone;
	API_CurtainWallQuantity					cw;
	API_CWFrameQuantity						cwFrame;
	API_CWPanelQuantity						cwPanel;
	API_CWJunctionQuantity					cwJunction;
	API_CWAccessoryQuantity					cwAccessory;
	API_StairQuantity						stair;
	API_StairRiserQuantity					stairRiser;
	API_StairTreadQuantity					stairTread;
	API_StairStructureQuantity				stairStructure;
	API_RailingQuantity						railing;
	API_RailingToprailQuantity				railingToprail;
	API_RailingHandrailQuantity				railingHandrail;
	API_RailingRailQuantity					railingRail;
	API_RailingToprailEndQuantity			railingToprailEnd;
	API_RailingHandrailEndQuantity			railingHandrailEnd;
	API_RailingRailEndQuantity				railingRailEnd;
	API_RailingToprailConnectionQuantity	railingToprailConnection;
	API_RailingHandrailConnectionQuantity	railingHandrailConnection;
	API_RailingRailConnectionQuantity		railingRailConnection;
	API_RailingPostQuantity					railingPost;
	API_RailingInnerPostQuantity			railingInnerPost;
	API_RailingBalusterQuantity				railingBaluster;
	API_RailingPanelQuantity				railingPanel;
	API_RailingSegmentQuantity				railingSegment;
	API_ColumnSegmentQuantity				columnSegment;
	API_BeamSegmentQuantity					beamSegment;
} API_ElementQuantityMask;

typedef API_CompositeQuantity API_CompositeQuantityMask;

class API_QuantitiesMask {
public:
	API_ElementQuantityMask			elements;
	API_CompositeQuantityMask		composites;

	API_QuantitiesMask ()
	{
		memset (&elements, 0, sizeof (elements));
		memset (&composites, 0, sizeof (composites));
	}
};

inline void ACAPI_ELEMENT_QUANTITIES_MASK_CLEAR (API_QuantitiesMask& mask)
{
	memset (&mask, 0, sizeof (mask));
}
inline void ACAPI_ELEMENT_QUANTITIES_MASK_SETFULL (API_QuantitiesMask& mask)
{
	memset (&mask, 0xFF, sizeof (mask));
}

inline void ACAPI_ELEMENT_QUANTITY_MASK_CLEAR (API_QuantitiesMask& mask)
{
	memset (&mask.elements, 0, sizeof (mask.elements));
}
inline void ACAPI_ELEMENT_QUANTITY_MASK_SETFULL (API_QuantitiesMask& mask)
{
	memset (&mask.elements, 0xFF, sizeof (mask.elements));
}
#define	ACAPI_ELEMENT_QUANTITY_MASK_SET(rec,typ,varnam)		*((char *) &((rec).elements.typ.varnam)) = -1
#define	ACAPI_ELEMENT_QUANTITY_MASK_CHECK(rec,typ,varnam)	(*((char *) &((rec).elements.typ.varnam)) != 0)

inline void ACAPI_ELEMENT_COMPOSITES_QUANTITY_MASK_CLEAR (API_QuantitiesMask& mask)
{
	memset (&mask.composites, 0, sizeof (mask.composites));
}

inline void ACAPI_ELEMENT_COMPOSITES_QUANTITY_MASK_SETFULL (API_QuantitiesMask& mask)
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

typedef struct {
	Int32							libIndex;					// index of the Library Part
	bool							assign;						// assignment/criteria
	char							filler_1;
	short							filler_2;
	Int32							filler_3[2];
} API_PropertyObjectRefType;

typedef struct {
	Int32							libIndex;					// index of the Library Part
	Int32							setIndex;
	Int32							index;
	Int32							status;						// APIDBRef_...
	double							quantity;					// calculated quantity
	Int32							filler_3[8];
} API_Obsolete_ComponentRefType;

typedef struct {
	Int32							libIndex;					// index of the Library Part
	Int32							setIndex;
	Int32							index;
	Int32							status;						// APIDBRef_...
	Int32							filler_3[8];
} API_DescriptorRefType;


// =============================================================================
// Markup Management
//
// =============================================================================

struct API_MarkUpType {
	API_Guid						guid;
	GS::UniString					name;
	API_Guid						parentGuid;
	Int32							filler_0;
	short							filler_1;
	short							filler_2;
	GSTime							creaTime;
	GSTime							modiTime;
	GS::UniString					tagText;
	API_Guid						tagTextElemGuid;
	bool							isTagTextElemVisible;
	bool							filler_3[7];

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

typedef enum {
	APIComment_Error				= 0,
	APIComment_Warning,
	APIComment_Info,
	APIComment_Unknown
} API_MarkUpCommentStatusID;

struct API_MarkUpCommentType {
	API_Guid						guid;
	GS::UniString					author;
	GS::UniString					text;
	API_MarkUpCommentStatusID		status;
	GSTime							creaTime;
	Int32							filler_1[2];

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

typedef struct {												// transformation parameters of the actual operation
	API_EditCmdID					typeID;
	bool							topNodeStretched;
	bool							filler_1[3];

	API_Vector						theDisp;
	API_Vector						theAxeVect;
	API_Coord						theOrigo;
	double							theCosA;
	double							theSinA;
	double							theDispZ;
	double							theRatio;

	API_Vector						sectionLineDir;				// cutplane line direction unit vector

	double							filler_2[6];
} API_ActTranPars;

typedef struct {												// global parameters for transforming elements
	API_EditCmdID					typeID;
	bool							withDelete;
	bool							topNodeStretched;
	bool							filler_1[2];

	API_Coord						origC;
	API_Coord3D 					begC;
	API_Coord3D						endC;
	API_Coord3D						endC2;

	double							filler_2[8];
} API_EditPars;


// =============================================================================
// Tool operations
//
// =============================================================================

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

typedef enum {													// selection types
	API_SelEmpty					= 0,

	API_SelElems,

	API_MarqueePoly,
	API_MarqueeHorBox,
	API_MarqueeRotBox
} API_SelTypeID;

typedef enum {
	API_InsidePartially				= 0,
	API_InsideEntirely,
	API_OutsidePartially,
	API_OutsideEntirely
} API_SelRelativePosID;

typedef struct {
	API_SelTypeID					typeID;

	Int32							sel_nElem;
	Int32							sel_nElemEdit;
	Int32							filler_1[3];
	bool							filler_2[3];

	bool							multiStory;
	Int32							filler_3;
	API_Region						marquee;
} API_SelectionInfo;


// =============================================================================
// Reference points
//
// =============================================================================

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

struct API_Neig {
	API_NeigID						neigID;						// type of the element
	Int32							filler_1;
	API_Guid						guid;						// guid of the element
	Int32							inIndex;					// neig index inside the element
	Int32							flags;						// API_NeigFlg_... flags
	API_NeigElemPartID				elemPartType;				// type of the element part in case of partial selection
	UInt32							elemPartIndex;				// index of the element part (edge, vertex, face) partially selected
	short							subType;
	short							nodeType;
	UInt32							supplUnId;

	API_Neig () : API_Neig (APINULLGuid)
	{
	}

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
	API_PrimCtrl_CWallPanelEndID								// end exporting a curtainwall panel		(no pars)
} API_PrimTypeID;



typedef struct {
	bool							doFrame;
	bool							filler_1[3];
	API_AttributeIndex				fillInd;
	API_ExtendedPenType				fillPen;
	short							fillbkgPen;
	short							transparency;				// 1-100
	short							determination;				// how to determine the type of this fill (is it a construction, drawing fill, or it is determined by the origin)
	short							filler_2[3];
	API_RGBColor					fillRgb;
	API_RGBColor					fillbkgRgb;
	bool							isGradient;					// gradient fill parameters
	bool							isLinear;
	bool							filler_3[6];
	API_HatchOrientation			hatchOrientation;
} API_PrimHatchBorder;

typedef struct {
	API_Guid						guid;
	API_ElemType					type;
	short							drwIndex;					// draw order index of the element
	short							filler_0;
	Int32							filler_1[2];
} API_PrimElemRef;

typedef struct {
	API_PrimTypeID					typeID;						// type of the primitive element
	API_AttributeIndex				layer;						// layer of the parent element
	API_ExtendedPenType				pen;						// pen of the primitive element
	short							drwIndex;
	short							filler_1[3];
	API_RenovationStatusType		renovationStatus;
} API_Prim_Head;

typedef struct {
	API_Prim_Head					head;
	API_Coord						loc;						// hotspot coordinate
	API_Neig						neig;						// the neig
} API_PrimHotspot;

typedef struct {
	API_Prim_Head					head;
	API_Coord						loc;
} API_PrimPoint;

typedef struct {
	API_Prim_Head					head;
	API_AttributeIndex				ltypeInd;
	short							determination;				// how to determine the type of this line (origin, innerline, contourline)
	short							filler_1;
	double							penWeight;					// thickness of the line
	API_Coord						c1;
	API_Coord						c2;
} API_PrimLine;

typedef struct {
	API_Prim_Head					head;
	API_AttributeIndex				ltypeInd;
	bool							solid;						// filled with solid color
	bool							whole;						// whole arc
	short							determination;				// how to determine the type of this arc (origin, innerline, contourline)
	bool							reflected;					// means negative direction (clockwise)
	char							filler_1[7];
	double							penWeight;					// thickness of the arc
	API_Coord						orig;
	double							r;
	double							begAng;
	double							endAng;
	double							angle;						// 0.0,	or the angle of the 'a' axis
	double							ratio;						// 1.0,	or 'a/b' of the ellipse
} API_PrimArc;

typedef struct {
	API_Prim_Head					head;
	short							ind1;						// ind1 in array type parameter
	short							ind2;						// ind2 in array type parameter
	short							paramInd;
	short							font;						// font index
	unsigned short					faceBits;					// style of text
	short							effectBits;
	API_AnchorID					anchor;						// kind of text center
	API_JustID						just;						// justification of text
	Int32							filler_1;
	API_Coord						loc;						// left-baseline position, including the 'angle'
	double							heightMM;
	double							widthMM;
	double							angle;
	double							widthFactor;				// 1.0 == no scaling
	double							charSpaceFactor;			// 1.0 == normal
} API_PrimText;
																// callback parameters for API_PrimText:
																//    (char **) par1				content
																//    (unsigned short **) par2		UniCode content

typedef struct {
	API_Prim_Head					head;
	API_AttributeIndex				ltypeInd;
	short							determination;				// how to determine the type of this pLine (origin, innerline, contourline)
	short							drawSegmentMode;			// 0 - draw segments one-by-one, 1 - draw all continuously
	Int32							nCoords;
	Int32							nArcs;
	double							penWeight;					// thickness of the polyline segments
} API_PrimPLine;
																// callback parameters for API_PrimPLine:
																//    (API_Coord *) par1		coordinates
																//	  (API_PolyArc *) par3		arc parameters

typedef struct {
	API_Prim_Head					head;
	API_AttributeIndex				ltypeInd;
	bool							solid;						// filled with solid color
	bool							filler_1;
	short							determination;
	double							penWeight;					// thickness of the triangle segments
	API_Coord						c[3];
} API_PrimTri;

typedef struct {
	API_Prim_Head					head;
	API_AttributeIndex				ltypeInd;
	bool							solid;						// filled with solid color
	bool							useRgb;						// Have to use rgbColor when it set
	short							determination;
	double							penWeight;					// thickness of the poly segments
	Int32							nCoords; 					// number of vertexes
	Int32							nSubPolys;					// number of closed sub polygons including the first one
	Int32							nArcs;						// number of curves in the polygon
	API_ExtendedPenType				fillPen;					// pen of the fill
	API_RGBColor					rgbColor;					// the color of fill
} API_PrimPoly;
																// callback parameters for API_PrimPoly:
																//    (API_Coord *) par1		coordinates
																//    (long *) par2				polyends
																//    (API_PolyArc *) par3		arc parameters

typedef struct {
	API_Prim_Head					head;
	short							pixelSizeX;
	short							pixelSizeY;
	Int32							filler_1;
	double							rotAngle;
	API_Box							destBox;
	API_ColorDepthID				colorDepth;
	API_PictureFormat 				storageFormat;				// id to pict data block in "picts" handle
	GS::uchar_t						pictName[API_UniLongNameLen];
	char							mime[128];					// MIME type
	API_AnchorID					anchor;						// picture placement anchor point
	bool							transparent;
	bool							mirrored;
	short							filler_2;
	Int32							filler_3[4];
} API_PrimPict;
																// callback parameter for API_PrimPict:
																//    (char **) par1			picture data

typedef struct {
	bool							isWindow;
	bool							isDoor;
} API_CWallPanel;

typedef union {
	API_Prim_Head					header;

	API_PrimPoint					point;
	API_PrimLine					line;
	API_PrimArc						arc;
	API_PrimText					text;
	API_PrimPLine					pline;
	API_PrimTri						tri;
	API_PrimPoly					poly;
	API_PrimPict					pict;
	API_CWallPanel					panelKind;
} API_PrimElement;

// Categories

typedef enum {
	API_ElemCategory_Undefined			= 0,
	API_ElemCategory_StructuralFunction,
	API_ElemCategory_Position,
	API_ElemCategory_RenovationStatus,
	API_ElemCategory_RenovationFilter,
	API_ElemCategory_BRI
} API_ElemCategoryID;

typedef struct {
	API_Guid					guid;							// globally unique Id

	API_ElemCategoryID			categoryID;						// identifier of the category
	GS::uchar_t					name [API_UniLongNameLen];		// localized name of the category
	bool						filler_1[2];
} API_ElemCategory;

typedef struct {
	API_Guid					guid;							// globally unique Id

	API_ElemCategory			category;						// category of the category value
	GS::uchar_t					name [API_UniLongNameLen];		// localized name of the category value
	bool						isVisibleOnUI;
	bool						usableAsCriteria;
	bool						filler_1[3];
} API_ElemCategoryValue;

// ---------------------------------------------------------------------------------------------------------------------

#endif
