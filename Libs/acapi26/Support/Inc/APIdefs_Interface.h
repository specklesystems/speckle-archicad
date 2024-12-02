// *********************************************************************************************************************
// API definitions - managing interface components
//
// Module:			API
// Namespace:		-
// Contact person:	archicadapi@graphisoft.com
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APIDEFS_INTERFACE_H)
#define	APIDEFS_INTERFACE_H

#if defined (_MSC_VER)
#pragma once
#endif


// --- Includes	--------------------------------------------------------------------------------------------------------

// own
#include "APIdefs_Base.h"
#include "APIdefs_Elements.h"

// GSRoot
#include "RS.hpp"

namespace DG {
	class PushCheck;
};

struct API_AttributeFolder;

// --- Compiler settings -----------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------


// =============================================================================
// Function codes and parameter descriptions
//
// =============================================================================

typedef enum {
	APIIo_GetMenuItemFlagsID			= 'GMIF',		// par1: const API_MenuItemRef*					par2: GSFlags (itemFlags)
	APIIo_SetMenuItemFlagsID			= 'SMIF',		// par1: const API_MenuItemRef*					par2: GSFlags (itemFlags)
	APIIo_GetMenuItemTextID				= 'GMIT',		// par1: const API_MenuItemRef*					par2: char* (itemText) 			par3: [GS::UniString*] (itemUniText)
	APIIo_SetMenuItemTextID				= 'SMIT',		// par1: const API_MenuItemRef*					par2: char* (itemText) 			par3: [GS::UniString*] (itemUniText)
	APIIo_AddMenuItemTextID				= 'AMIT',		// par1: const API_MenuItemRef*					par2: char* (itemText) 			par3: [GS::UniString*] (itemUniText)

	APIIo_GetProcessControlID			= 'PCTR',		// par1: GS::ProcessControl*					par2: ---
	APIIo_SetInnerProcessControlID  	= 'SIPC',		// par1: GS::ProcessControl*					par2: ---

	APIIo_InitProcessWindowID			= 'IPWD',		// par1: const GS::UniString* (title)			par2: short* (nPhase)			par3: API_ProcessControlTypeID* (processControlType)
	APIIo_CloseProcessWindowID			= 'CPWD',		// par1: ---									par2: ---
	APIIo_SetNextProcessPhaseID			= 'SPRP',		// par1: const GS::UniString* (subtitle)		par2: Int32* (maxval)			par3: [bool*] (show percent)
	APIIo_SetProcessValueID				= 'SPRV',		// par1: Int32* (newval)						par2: ---
	APIIo_IncProcessValueID				= 'IPRV',		// par1: Int32* (incval)						par2: ---
	APIIo_IsProcessCanceledID			= 'CANC',		// par1: ---									par2: ---

	APIIo_InitNeigFilterID				= 'INFI',		// par1: API_NeigFilter*						par2: API_InitNeigFilterID
	APIIo_SetNeigFilterID				= 'SNFI',		// par1: API_NeigFilter*						par2: API_NeigID
	APIIo_ClearNeigFilterID				= 'CNFI',		// par1: API_NeigFilter*						par2: API_NeigID

	APIIo_GetPointID					= 'IPOI',		// par1: API_GetPointType*						par2: [RubberLineInfoProc*] 	par3: [Get3DComponentProc*]
	APIIo_GetLineID						= 'ILIN',		// par1: API_GetLineType*						par2: [RubberLineInfoProc*]
	APIIo_GetArcID						= 'IARC',		// par1: API_GetArcType*						par2: [RubberLineInfoProc*]
	APIIo_GetPolyID						= 'IPOL',		// par1: API_GetPolyType*						par2: [API_RubberPolyCallbacks*]
	APIIo_DrawRubberLineID				= 'DRLI',		// par1: API_RubberLineType*					par2: ---
	APIIo_DrawRubberArcID				= 'DRAR',		// par1: API_RubberArcType*						par2: ---

	APIIo_PetPaletteID					= 'PETP',		// par1: API_PetPaletteType*					par2: APIPetPaletteCallBackProc*

	APIIo_CompleteUserInputID			= 'INOK',		// par1: ---									par2: ---
	APIIo_CancelUserInputID				= 'INCA',		// par1: ---									par2: ---

	APIIo_SetUserControlCallbackID		= 'SUCC',		// par1: API_UCCallbackType*					par2: ---

	APIIo_ObjectSettingsID				= 'OBJS',		// par1: API_ObjectSettingsPars*				par2: ---
	APIIo_SettingsDialogID				= 'SETD',		// par1: API_ToolBoxItem*						par2: API_Guid*

	APIIo_SetConstraintID				= 'SCON',		// par1: API_ConstraintPars*					par2: ---
	APIIo_ResetConstraintID				= 'RESC',		// par1: ---									par2: ---

	APIIo_SaveLibPartFileDialogID		= 'SLPD',		// par1: bool*									par2: IO::Location*				par3: [bool*] (browse for folder)		par4: [GS::UniString*] (dialog title)	par5: [GS::UniString*] (dialog type)
	APIIo_OpenLibPartFileDialogID		= 'OLPD',		// par1: bool*									par2: IO::Location*				par3: [bool*] (is GSM)					par4: [bool*] (external editor was invoked)
	APIIo_OpenPictureDialogID			= 'OPID',		// par1: bool*									par2: IO::Location*
	APIIo_OpenOtherObjectDialogID		= 'OOOD',		// par1: bool*									par2: IO::Location*				par3: [bool*] (is room)

	APIIo_SetProcessOnOffSwitchID		= 'SPOS',		// par1: bool*									par2: ---
	APIIo_GetProcessOnOffSwitchID		= 'GPOS',		// par1: bool*									par2: ---

	APIIo_GetLastValidEmbeddedLPNameID	= 'LVEI',		// par1: GS::UniString*							par2: IO::Location*

	APIIo_Is3DCutawayEnabledID			= 'I3CE',		// par1: bool*									par2: ---
	APIIo_Set3DCutawayStatusID			= 'S3CS',		// par1: bool*									par2: ---
	APIIo_IsCuttingPlanesVisibleID		= 'ICPV',		// par1: bool*									par2: ---
	APIIo_SetCuttingPlanesVisibilityID	= 'SCPV'		// par1: bool*									par2: ---
} API_InterfaceID;



// =============================================================================
// Menu Item reference
//
// =============================================================================

#define API_MenuItemDisabled		0x00000001
#define API_MenuItemChecked			0x00000002

typedef struct {
	short							menuResID;
	short							filler_1;
	Int32							itemIndex;
	Int32							filler_2[2];
} API_MenuItemRef;


// =============================================================================
// ProcessControl types
//
// =============================================================================

typedef enum {
	API_MenuCommandEnabled,
	API_MenuCommandDisabled
} API_ProcessControlTypeID;


// =============================================================================
// Cursor Forms
//
// =============================================================================

typedef enum {
	APICursor_UserDefined,										// Cursor defined by Resource ID - UNUSED
	APICursor_Default,											// Default cursor shape

	APICursor_Spin,												// SpinCursor (beach balls)
	APICursor_SystemArrow,										// System arrow cursor
	APICursor_SystemClock,										// System clock cursor

	APICursor_IBeam,											// I beam cursor for text editing
	APICursor_Drag,												// Cursor for dragging windows
	APICursor_Trident,											// Trident cursor for dragging rollrect

	APICursor_ZoomIn,											// Zoom in cursor
	APICursor_ZoomOut,											// Zoom out cursor
	APICursor_Hand,												// Hand cursor
	APICursor_MiniHand,											// Small hand cursor

	APICursor_Cross,											// Cross cursor
	APICursor_Check,											// Check cursor (indicates ...Neig)
	APICursor_CheckRef,											// Check cursor (thick)
	APICursor_Branch,											// Branch cursor (indicates ...OnNeig)
	APICursor_BranchRef,										// Branch cursor (thick)
	APICursor_XPoint,											// Cross point cursor
	APICursor_Normal,											// Normal (perpendicular) cursor
	APICursor_Tangent,											// Tangent (osculation) cursor

	APICursor_Arrow,											// Arrow cursor (selection mode)
	APICursor_ArrowCheck,										// Check cursor in arrow mode
	APICursor_ArrowCheckRef,									// Check cursor in arrow mode (thick)
	APICursor_ArrowBranch,										// Branch cursor in arrow mode
	APICursor_ArrowBranchRef,									// Branch cursor in arrow mode (thick)
	APICursor_ArrowXPoint,										// Cross point cursor in arrow mode
	APICursor_ArrowNormal,										// Normal cursor in arrow mode
	APICursor_ArrowTangent,										// Tangent cursor in arrow mode

	APICursor_Pencil,											// Pencil shaped cursor during input
	APICursor_PencilCheck,										// Check cursor during input
	APICursor_PencilCheckRef,									// Check cursor during input thick
	APICursor_PencilBranch,										// Branch cursor during input
	APICursor_PencilBranchRef,									// Branch cursor during input thick
	APICursor_PencilXPoint,										// Cross point cursor during input
	APICursor_PencilNormal,										// Normal cursor during input
	APICursor_PencilTangent,									// Tangent cursor during input

	APICursor_Eye,												// Eye cursor for window/door opening
	APICursor_DoubleEye,										// Double eye for window/door position
	APICursor_Hammer,											// Hammer cursor for completing input
	APICursor_MagicWand,										// Magic wand cursor

	APICursor_Trimmer,											// Scissors shaped cursor
	APICursor_TrimmerFull,										// Scissors shaped cursor (thick)
	APICursor_Picker,											// Dropper shaped cursor
	APICursor_PickerFull,										// Dropper shaped cursor (thick)
	APICursor_Injection,										// Injection shaped cursor
	APICursor_InjectionFull										// Injection shaped cursor (thick)
} API_CursorFormID;


typedef struct {
	API_CursorFormID				nothingOnCursor;			// cursor is not above any remarkable point
	API_CursorFormID				pointOnCursor;				// point neig (wall case: not on refLine)
	API_CursorFormID				lineOnCursor;				// on line neig (wall case: not refLine)
	API_CursorFormID				refPointOnCursor;			// point neig on wall reference line
	API_CursorFormID				refLineOnCursor;			// on line neig of wall reference line
	API_CursorFormID				crossOnCursor;				// cursor is over cross point of elements
	API_CursorFormID				normalOnCursor;				// perpendicular point during input
	API_CursorFormID				tangentOnCursor;			// point of osculation during input
	API_CursorFormID				invalpointCursor;			//
	API_CursorFormID				areaOnCursor;				// over area
	API_CursorFormID				lineSurfCrossOnCursor;		// line and surface cross point
	API_CursorFormID				lineSurfNormOnCursor;		// normal line points of surface
	API_CursorFormID				surfSurfCrossCursor;		// cross line of two surfaces
	API_CursorFormID				surfSurfNormOnCursor;		// two surfaces are normal
} API_CursorSet;


// =============================================================================
// Input Filtering
//
// =============================================================================

typedef char	API_NeigFilter[16];

typedef enum {
	APIInitNeigFilter_Full,
	APIInitNeigFilter_Empty,
	APIInitNeigFilter_On,
	APIInitNeigFilter_Node
} API_InitNeigFilterID;


// =============================================================================
// Rubberline feedback
//
// =============================================================================

typedef enum {
	APIRubberLine_Simple			= 1,
	APIRubberLine_Double			= 2
} API_RubberLineThickness;

typedef enum {
	APIRubberArc_OrigoAngles		= 0,
	APIRubberArc_ThreePoint			= 1
} API_RubberArcTypeID;

typedef struct {
	API_Coord3D						c1;
	API_Coord3D						c2;
	API_RubberLineThickness			lineThick;
	Int32							filler[3];
} API_RubberLineType;

typedef struct {
	API_Coord3D						origC;						// coordinate of the center point
	bool							radii;						// draw radii as well
	char							filler[7];
	API_RubberLineThickness			lineThick;
	API_RubberArcTypeID				arcType;
	union {
		struct {												// circle or elliptic arc defined by it's origo and two angles - only in 2D
			double					r;							// radius (or 'a' if ellipse)
			double					angle;						// 0.0,	or the angle of the 'a' axis
			double					ratio;						// 1.0,	or 'a/b' of the ellipse
			double					begAng;						// beginning angle of the arc
			double					endAng;						// ending angle of the arc
		} arc2D;
		struct {												// circle arc defined by it's origo and two points - for 3D
			API_Coord3D				begC;						// beginning point of the arc
			API_Coord3D				endC;						// ending point of the arc
			bool					sign;						// the arc's angle is + (true) or - (false)
			char					filler[7];
		} arc3D;
	};
	Int32							filler_2[8];
} API_RubberArcType;

typedef struct {
	API_Coord3D						actCoord;					// actual mouse coordinate
	bool							drawFlag;					// draw or delete
	char							filler_1;
	short							filler_2;
	Int32							filler_3[3];
} API_RubberLineInfo;


// =============================================================================
// Point input
//
// =============================================================================

typedef struct {
	char							prompt[256];				// prompt string in the info box
	bool							changeFilter;				// filter is initialized for change
	bool							changeCursorSet;			// cursorSet initialized for change
	bool							changePlane;				// plane is initialized for change
	bool							enableQuickSelection;		// magnetic cursor
	Int32							filler_1;
	API_NeigFilter					filter;						// neig filter for cursor snapping
	API_CursorSet					cursorSet;					// cursor set for visual feedback
	API_Coord3D						planeCoord;					// a point of the input plane
	API_Vector3D					planeNormal;				// normal vector of the input plane
	API_Coord3D						pos;						// <-- the coordinate
	API_Neig						neig;						// <-- the neig

	API_Guid						guid;						// guid of the pointed element
	Int32							dbElemIdx;					// database elem index
	Int32							bodyIdx;					// body index of the element
	ULong							ipgon;						// polygon index of the body
} API_GetPointType;

// =============================================================================
// Get 3D component
//
// =============================================================================

typedef struct {
	API_Guid		guid;
	Int32			dbElemIdx;
	Int32			bodyIdx;
	ULong			ipgon;
	API_Coord3D		c3;
	API_Coord3D		normal;
} API_Get3DComponentType;


// =============================================================================
// Line input
//
// =============================================================================

typedef struct {
	char							prompt[256];				// prompt string in the info box
	bool							changeFilter;				// filter is initialized for change
	bool							changeCursorSet;			// cursorSet initialized for change
	bool							changePlane;				// normal is initialized for change
	bool							disableDefaultFeedback;		// do not draw default rubber line
	Int32							filler_1;
	API_NeigFilter					filter;						// neig filter for cursor snapping
	API_CursorSet					cursorSet;					// cursor set for visual feedback
	API_Vector3D					planeNormal;				// normal vector of the input plane
	API_Coord3D						startCoord;					// the start coordinate
	API_Coord3D						pos;						// <-- the coordinate
	API_Neig						neig;						// <-- the neig
} API_GetLineType;


// =============================================================================
// Arc input
//
// =============================================================================

typedef struct {
	char							prompt[256];				// prompt string in the info box
	bool							startCoordGiven;			// start coordinate specified
	bool							negArc;						// <-- negative arc entered
	bool							changeCursorSet;			// cursorSet initialized for change
	bool							disableDefaultFeedback;		// do not draw default rubber line
	Int32							filler_1;
	API_CursorSet					cursorSet;					// cursor set for visual feedback
	API_Coord3D						origo;						// the origo
	API_Coord3D						startCoord;					// <--> the start coordinate
	API_Coord3D						pos;						// <-- the coordinate
	API_Neig						neig;						// <-- the neig
} API_GetArcType;


// =============================================================================
// Polygon input
//
// =============================================================================

typedef struct {
	GSPtr 							*rubberLineInfoProc;		// RubberLineInfoProc
	GSPtr							*get3DComponentProc;		// Get3DComponentProc
	GSPtr							*addPolyNodeProc;			// AddPolyNodeProc
	GSPtr							*delPolyNodeProc;			// DelPolyNodeProc
} API_RubberPolyCallbacks;

typedef enum {
	APIPolyGetMethod_General,
	APIPolyGetMethod_Rect,
	APIPolyGetMethod_RotRect,
	APIPolyGetMethod_Polyline
} API_PolyGetMethod;

typedef struct {
	char							prompt[256];				// prompt string in the info box
	bool							changeCursorSet;			// cursorSet initialized for change
	bool							changePlane;				// normal is initialized for change
	bool							disableDefaultFeedback;		// do not draw default rubber line
	bool							getZCoords;					// retrieve z coordinates in case of 3D input
	API_PolyGetMethod				method;						// polygon input method
	API_CursorSet					cursorSet;					// cursor set for visual feedback
	API_Vector3D					planeNormal;				// normal vector of the input plane
	API_Coord3D						startCoord;					// the start coordinate
	API_Coord						**coords;					// <-- the coordinates (project vertically to the plane)
	API_PolyArc						**parcs;					// <-- arcs segments
	Int32							nCoords;					// <-- number of coordinates
	Int32							nArcs;						// <-- number of curves in the polygon
	API_Neig						neig;						// <-- the closing neig
	double							**zCoords;					// <-- z coordinates (if getZCoords is true)
	Int32							filler_1;
	bool							polylineWas;				// <-- polyline contour entered
	bool							useStandardPetPalette;		// <-- input with standard petpalette
	bool							filler_2[2];
	Int32							filler_3;
} API_GetPolyType;


// =============================================================================
// Drawing constraints for input
//
// =============================================================================

typedef enum {
	APIConst_X						= 1,
	APIConst_Y						= 2,
	APIConst_Z						= 3,
	APIConst_A						= 4,
	APIConst_R						= 5
} API_ConstraintType;

typedef struct {
	API_ConstraintType				constType;
	Int32							filler_1;
	double							constValue;
	double							filler_2[2];
	bool							useLocOrigo;
	bool							filler_3;
	short							filler_4[3];
} API_ConstraintPars;


// =============================================================================
// Modeless Palette control flags and notification messages
//
// =============================================================================

#define API_PalEnabled_FloorPlan			0x00000001
#define API_PalEnabled_Section				0x00000002
#define API_PalEnabled_3D					0x00000004
#define API_PalEnabled_SelOnly				0x00000008
#define API_PalEnabled_Detail				0x00000010
#define API_PalEnabled_Layout				0x00000020
#define API_PalEnabled_Worksheet			0x00000040
#define API_PalEnabled_Elevation			0x00000080
#define API_PalEnabled_InteriorElevation	0x00000100
#define API_PalEnabled_DocumentFrom3D		0x00000200
#define API_PalEnabled_ModelCompare			0x00000400

typedef enum {
	APIPalMsg_ClosePalette			= 1,						// must close the palette
	APIPalMsg_HidePalette_Begin		= 2,						// must hide the palette
	APIPalMsg_HidePalette_End		= 3,						// hidden palette can be shown again
	APIPalMsg_DisableItems_Begin	= 4,						// disable palette items during user input
	APIPalMsg_DisableItems_End		= 5,						// disabled items can be enabled
	APIPalMsg_OpenPalette			= 6,						// open the palette; called from Work Environment
	APIPalMsg_IsPaletteVisible		= 7							// return true if palette is visible; called from Work Environment
} API_PaletteMessageID;


// =============================================================================
// Pet Palette control
//
// =============================================================================

typedef struct {
	short							petPaletteID;				// unique pet palette identifier
	short							nCols;						// number of columns
	short							nRows;						// number of rows
	short							value;						// actual control value
	UInt32							grayBits;					// disabled items
	short**							petIconIDsHdl;				// array of pet icons' 'GICN' resource IDs
	short							dhlpResourceID;				// ID of the DHLP help resource
	short							obsolete;					// obsolete now
	GSResModule						petIconResModule;			// resource module to load the icon resource from
	Int32							filler_1[5];
} API_PetPaletteType;



// =============================================================================
// User Control callbacks
//
// =============================================================================

typedef enum {
	APIUserControlType_Pen,										// pen control
	APIUserControlType_PenWithNull,								// pen control with background pen
	APIUserControlType_PolyFill,								// polygon fill control
	APIUserControlType_WallFill,								// wall fill control
	APIUserControlType_WallCompFill,							// wall fill control without composites
	APIUserControlType_AllFill,									// all fill types control
	APIUserControlType_AllFillGradNoComp,						// all fill types without composites
	APIUserControlType_WallSetsFill,							// wall fill control as in the settings dialog
	APIUserControlType_WallComposites,							// wall composites control as in the settings dialog
	APIUserControlType_SlabSetsFill,							// slab fill control as in the settings dialog
	APIUserControlType_SlabComposites,							// slab composites control as in the settings dialog
	APIUserControlType_RoofSetsFill,							// roof fill control as in the settings dialog
	APIUserControlType_RoofComposites,							// roof composites control as in the settings dialog
	APIUserControlType_ShellSetsFill,							// shell fill control as in the settings dialog
	APIUserControlType_ShellComposites,							// shell composites control as in the settings dialog
	APIUserControlType_OnlyCompFill,							// composite fills only control
	APIUserControlType_Material,								// material control
	APIUserControlType_MaterialWithGeneral,						// material control with general material
	APIUserControlType_Layer,									// layer control
	APIUserControlType_ZoneCategory,							// zone category control
	APIUserControlType_DashedLine,								// dashed line control
	APIUserControlType_SymbolLine,								// symbol line control, all line types
	APIUserControlType_CoverFill,								// cover fill control
	APIUserControlType_WallProfile,								// wall profile control
	APIUserControlType_BeamProfile,								// beam profile control
	APIUserControlType_ColumnProfile,							// column profile control
	APIUserControlType_AllProfile,								// all profile control
	APIUserControlType_PolyFillWithGradient,					// polygon fill control with gradient ones
	APIUserControlType_BuildingMaterial,							// building material control
	APIUserControlType_HandrailProfile,							// handrail profile control
	APIUserControlType_OtherGDLObjectProfile,					// other gdl object profile control
	APIUserControlType_BeamAndColumnProfile,					// column and beam profile control
} API_UserControlType;

typedef struct {
	API_UserControlType				type;						// requested type of the user control
	short							dialogID;					// ID of the dialog
	short							itemID;						// ID of the user control
} API_UCCallbackType;


// =============================================================================
// Object Settings Dialog
//
// =============================================================================

typedef struct {
	API_Element						elemDef;					// symbol data [in|out]
	API_Element						elemMask;					// relevant fields in elemDef [in]
	API_AddParType					**addPars;					// additional symbol parameters [out]
	char							subtypeID [128];			// GUID string of the object subtype
	Int32							propIndivLibInd;			// index of individually assigned property [out]
	bool							propCriteria;				// properties assigned by criteria [out]
	char							filler_1[3];
	Int32							filler_2[31];
} API_ObjectSettingsPars;



// ---------------------------------------------------------------------------------------------------------------------


struct API_AttributePickerParams {
	enum class PushCheckAppearance {
		ArrowIconAndText,
		ArrowOnly
	};

	enum class EmptySelectionBehaviour {
		SelectFirst,
		SelectNothing
	};

	enum class LockedLayersStatus {
		Disabled,
		Enabled
	};

	API_UserControlType				type;						// requested type of the user control
	short							dialogID = 0;				// ID of the dialog
	short							itemID = 0;					// ID of the user control
	PushCheckAppearance				pushCheckAppearance;		// what to draw on the pushcheck button, only the arrow, or arrow+icon+text?
	EmptySelectionBehaviour			emptySelectionBehaviour;	// when opening the popup, and the attributeIndex is invalid or not in the given attribute set, select the first attribute?
	LockedLayersStatus				lockedLayersStatus;			// appearance of locked layers in the Layer Picker

	API_AttributePickerParams () :
		pushCheckAppearance (PushCheckAppearance::ArrowOnly),
		emptySelectionBehaviour (EmptySelectionBehaviour::SelectFirst)
	{
		lockedLayersStatus = LockedLayersStatus::Enabled;
	}
};


class API_AttributePicker {
public:
	virtual ~API_AttributePicker ();

	virtual API_AttributeIndex	GetSelectedAttributeIndex () const = 0;
	virtual void				SetSelectedAttributeIndex (const API_AttributeIndex& index) = 0;

	virtual bool				Invoke () = 0;
	virtual void				Refresh () = 0;

	virtual API_UserControlType GetUserControlType () = 0;
};


struct API_AttributeFolderPickerParams {
	enum class PushCheckAppearance {
		ArrowIconAndText,
		ArrowOnly
	};

	API_UserControlType				type;							// requested type of the user control
	short							dialogID = 0;					// ID of the dialog
	short							itemID = 0;						// ID of the user control
	PushCheckAppearance				pushCheckAppearance;			// what to draw on the pushcheck button, only the arrow, or arrow+icon+text?
};


class API_AttributeFolderPicker {
public:
	virtual ~API_AttributeFolderPicker ();

	virtual API_AttributeFolder	GetSelectedAttributeFolder () const = 0;
	virtual void				SetSelectedAttributeFolder (const API_AttributeFolder& folder) = 0;

	virtual bool				Invoke () = 0;
};


#endif
