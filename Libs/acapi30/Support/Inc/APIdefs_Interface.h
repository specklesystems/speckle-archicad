// *********************************************************************************************************************
// API definitions - managing interface components
//
// Module:			API
// Namespace:		-
// *********************************************************************************************************************

#if !defined (APIDEFS_INTERFACE_H)
#define	APIDEFS_INTERFACE_H

#pragma once


// --- Includes	--------------------------------------------------------------------------------------------------------

// own
#include "APIdefs_Base.h"
#include "APIdefs_Attributes.h"
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
	APIIo_SettingsDialogID				= 'SETD',		// par1: API_ToolBoxItem*						par2: API_Guid*					par3: [UShort*] (index of sub tool)
	APIIo_NewSettingsDialogID           = 'NSET',       // par1: API_Guid*                              par2: [UShort*] (index of sub tool)

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
	APIIo_AreCuttingPlanesVisibleID		= 'ICPV',		// par1: bool*									par2: ---
	APIIo_SetCuttingPlanesVisibilityID	= 'SCPV',		// par1: bool*									par2: ---

	APIIo_ShowSelectionIn3DID			= 'SS3D',		// par1: ---									par2: ---
	APIIo_ShowAllIn3DID					= 'SA3D',		// par1: ---									par2: ---

	APIIo_EditHierarchicalElemID		= 'EDHE',		// par1: API_Guid*								par2: ---
	APIIo_CancelHierarchicalElemID		= 'CAHE',		// par1: ---									par2: ---
	APIIo_OkHierarchicalElemID			= 'OKHE'		// par1: ---									par2: ---

} API_InterfaceID;



// =============================================================================
// Menu Item reference
//
// =============================================================================

#define API_MenuItemDisabled							0x00000001
#define API_MenuItemChecked								0x00000002
#define API_MenuItemDisabledByHostApplication			0x00000004

/**
 * @brief Reference to a menu item mounted by the API tool add-on.
 * @struct API_MenuItemRef
 * @ingroup MenuItem
 * @remarks For the utilization of the @c API_MenuItemRef structure and examples see the @c ACAPI_Interface function.
 */
struct API_MenuItemRef {

/**
 * @brief The resource ID which the tool command belongs to.
 * @var menuResID
 */
	short							menuResID;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief The index of the command within the specified menu.
 * @var itemIndex
 */
	Int32							itemIndex;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[2];

};


// =============================================================================
// ProcessControl types
//
// =============================================================================

/**
 * @brief Process control types.
 * @ingroup ProcessWindow
 * @remarks Used in @ref ACAPI_ProcessWindow_InitProcessWindow.
 */
typedef enum {
	/** Enabled */
	API_MenuCommandEnabled,

	/** Disabled */
	API_MenuCommandDisabled

} API_ProcessControlTypeID;


// =============================================================================
// Cursor Forms
//
// =============================================================================

/**
 * @brief Predefined cursor forms for customizing the user input.
 * @ingroup UserInput
 * @remarks The @ref API_CursorFormID values are used to specify the cursor set for a user input process invoked from the API tool add-on.
 *          For example of using custom cursor sets see @ref ACAPI_UserInput_GetArc.
 */
typedef enum {
	/** Cursor defined by resource ID (NOT USED) */
	APICursor_UserDefined,

	/** Default cursor shape */
	APICursor_Default,

	/** Spin cursor (rotating beach balls) - ![SpinCursor](@ref cf_SpinCursor.png) */
	APICursor_Spin,

	/** System arrow cursor */
	APICursor_SystemArrow,

	/** System clock cursor */
	APICursor_SystemClock,

	/** I beam cursor for text editing - ![IBeamCursor](@ref cf_IBeamCursor.png) */
	APICursor_IBeam,

	/** Cursor for dragging windows - ![DragCursor](@ref cf_DragCursor.png) */
	APICursor_Drag,

	/** Trident cursor for dragging rollrect - ![TridentCursor](@ref cf_TridentCursor.png) */
	APICursor_Trident,

	/** Zoom in cursor - ![ZoomInCursor](@ref cf_ZoomInCursor.png) */
	APICursor_ZoomIn,

	/** Zoom out cursor - ![ZoomOutCursor](@ref cf_ZoomOutCursor.png) */
	APICursor_ZoomOut,

	/** Hand cursor - ![HandCursor](@ref cf_HandCursor.png)*/
	APICursor_Hand,

	/** Small hand cursor- ![MiniHandCursor](@ref cf_MiniHandCursor.png) */
	APICursor_MiniHand,

	/** Cross cursor - ![CrossCursor](@ref cf_CrossCursor.png)*/
	APICursor_Cross,

	/** Check cursor (indicates ...Neig) - ![CheckCursor](@ref cf_CheckCursor.png)*/
	APICursor_Check,

	/** Check cursor (thick) - ![CheckRefCursor](@ref cf_CheckRefCursor.png)*/
	APICursor_CheckRef,

	/** Branch cursor (indicates ...OnNeig) - ![BranchCursor](@ref cf_BranchCursor.png)*/
	APICursor_Branch,

	/** Branch cursor (thick) - ![BranchRefCursor](@ref cf_BranchRefCursor.png)*/
	APICursor_BranchRef,

	/** Cross point cursor - ![XPointCursor](@ref cf_XPointCursor.png)*/
	APICursor_XPoint,

	/** Normal (perpendicular) cursor - ![NormalCursor](@ref cf_NormalCursor.png)*/
	APICursor_Normal,

	/** Tangent (osculation) cursor - ![TangentCursor](@ref cf_TangentCursor.png)*/
	APICursor_Tangent,

	/** Arrow cursor (selection mode) - |![ArrowCursor](@ref cf_ArrowCursor.png)*/
	APICursor_Arrow,

	/** Check cursor in arrow mode - ![ArrowCheckCursor](@ref cf_ArrowCheckCursor.png)*/
	APICursor_ArrowCheck,

	/** Check cursor in arrow mode (thick) - ![ArrowCheckRefCursor](@ref cf_ArrowCheckRefCursor.png)*/
	APICursor_ArrowCheckRef,

	/** Branch cursor in arrow mode - ![ArrowBranchCursor](@ref cf_ArrowBranchCursor.png)*/
	APICursor_ArrowBranch,

	/** Branch cursor in arrow mode (thick) - ![ArrowBranchRefCursor](@ref cf_ArrowBranchRefCursor.png)*/
	APICursor_ArrowBranchRef,

	/** Cross point cursor in arrow mode - ![ArrowXPointCursor](@ref cf_ArrowXPointCursor.png)*/
	APICursor_ArrowXPoint,

	/** |Normal cursor in arrow mode - ![ArrowNormalCursor](@ref cf_ArrowNormalCursor.png)*/
	APICursor_ArrowNormal,

	/** Tangent cursor in arrow mode - ![ArrowTangentCursor](@ref cf_ArrowTangentCursor.png)*/
	APICursor_ArrowTangent,

	/** Pencil shaped cursor during input - ![PencilCursor](@ref cf_PencilCursor.png)*/
	APICursor_Pencil,

	/** Check cursor during input - ![PencilCheckCursor](@ref cf_PencilCheckCursor.png)*/
	APICursor_PencilCheck,

	/** Check cursor during input (thick) - ![PencilCheckRefCursor](@ref cf_PencilCheckRefCursor.png)*/
	APICursor_PencilCheckRef,

	/** Branch cursor during input - ![PencilBranchCursor](@ref cf_PencilBranchCursor.png)*/
	APICursor_PencilBranch,

	/** Branch cursor during input (thick) - ![PencilBranchRefCursor](@ref cf_PencilBranchRefCursor.png)*/
	APICursor_PencilBranchRef,

	/** Cross point cursor during input - ![PencilXPointCursor](@ref cf_PencilXPointCursor.png)*/
	APICursor_PencilXPoint,

	/** Normal cursor during input - ![PencilNormalCursor](@ref cf_PencilNormalCursor.png)*/
	APICursor_PencilNormal,

	/** Tangent cursor during input - ![PencilTangentCursor](@ref cf_PencilTangentCursor.png)*/
	APICursor_PencilTangent,

	/** Eye cursor for window/door opening - ![EyeCursor](@ref cf_EyeCursor.png)*/
	APICursor_Eye,

	/** Double eye for window/door position - ![DoubleEyeCursor](@ref cf_DoubleEyeCursor.png)*/
	APICursor_DoubleEye,

	/** Hammer cursor for completing input - ![HammerCursor](@ref cf_HammerCursor.png)*/
	APICursor_Hammer,

	/** Magic wand cursor - ![MagicWandCursor](@ref cf_MagicWandCursor.png)*/
	APICursor_MagicWand,

	/** Scissors shaped cursor - ![TrimmerCursor](@ref cf_TrimmerCursor.png)*/
	APICursor_Trimmer,

	/** Scissors shaped cursor (thick) - ![TrimmerFullCursor](@ref cf_TrimmerFullCursor.png)*/
	APICursor_TrimmerFull,

	/** Dropper shaped cursor - ![PickerCursor](@ref cf_PickerCursor.png)*/
	APICursor_Picker,

	/** Dropper shaped cursor (thick) - ![PickerFullCursor](@ref cf_PickerFullCursor.png)*/
	APICursor_PickerFull,

	/** Injection shaped cursor - ![InjectionCursor](@ref cf_InjectionCursor.png)*/
	APICursor_Injection,

	/** Injection shaped cursor (thick) - ![InjectionFullCursor](@ref cf_InjectionFullCursor.png)*/
	APICursor_InjectionFull

} API_CursorFormID;


/**
 * @brief Cursor set definition for a user input.
 * @struct API_CursorSet
 * @ingroup UserInput
 * @remarks For example of using custom cursor sets see @ref ACAPI_UserInput_GetArc.
 */
struct API_CursorSet {

/**
 * @brief The cursor form when the cursor is not above any remarkable point
 * @var nothingOnCursor
 */
	API_CursorFormID				nothingOnCursor;

/**
 * @brief The cursor form when the cursor is above a point neig (except wall neigs on the reference line)
 * @var pointOnCursor
 */
	API_CursorFormID				pointOnCursor;

/**
 * @brief The cursor form when the cursor is above a line neig (except wall reference line)
 * @var lineOnCursor
 */
	API_CursorFormID				lineOnCursor;

/**
 * @brief The cursor form when the cursor is above a point neig on wall reference line
 * @var refPointOnCursor
 */
	API_CursorFormID				refPointOnCursor;

/**
 * @brief The cursor form when the cursor is above the reference line of a wall
 * @var refLineOnCursor
 */
	API_CursorFormID				refLineOnCursor;

/**
 * @brief The cursor form when the cursor is above cross point of elements
 * @var crossOnCursor
 */
	API_CursorFormID				crossOnCursor;

/**
 * @brief The cursor form when the cursor is above a line which is perpendicular to the input line
 * @var normalOnCursor
 */
	API_CursorFormID				normalOnCursor;

/**
 * @brief The cursor form when the cursor is above a point of osculation with an arc
 * @var tangentOnCursor
 */
	API_CursorFormID				tangentOnCursor;

/**
 * @brief MISSING
 * @var invalpointCursor
 */
	API_CursorFormID				invalpointCursor;

/**
 * @brief Over area.
 * @var areaOnCursor
 */
	API_CursorFormID				areaOnCursor;

/**
 * @brief Line and surface cross point.
 * @var lineSurfCrossOnCursor
 */
	API_CursorFormID				lineSurfCrossOnCursor;

/**
 * @brief Normal line points of surface.
 * @var lineSurfNormOnCursor
 */
	API_CursorFormID				lineSurfNormOnCursor;

/**
 * @brief Cross line of two surfaces.
 * @var surfSurfCrossCursor
 */
	API_CursorFormID				surfSurfCrossCursor;

/**
 * @brief Two surfaces are normal.
 * @var surfSurfNormOnCursor
 */
	API_CursorFormID				surfSurfNormOnCursor;

};


// =============================================================================
// Input Filtering
//
// =============================================================================

/**
 * @brief The size of @ref API_NeigFilter
 */
constexpr std::size_t API_NeigFilterSize = 16;

/**
 * @brief Structure for filtering neigs during user input.
 * @ingroup UserInput
 * @typedef API_NeigFilter
 * @sa ACAPI_UserInput_InitNeigFilter, @ref ACAPI_UserInput_ClearNeigFilter, @ref ACAPI_UserInput_SetNeigFilter
 */
typedef char	API_NeigFilter[API_NeigFilterSize];

/**
 * @brief Type of the neig filter initialization.
 * @ingroup UserInput
 * @remarks For the utilization of @c API_InitNeigFilterID see the @ref ACAPI_UserInput_InitNeigFilter function.
 */
typedef enum {
	/** Filter all neig types */
	APIInitNeigFilter_Full,

	/** Filter nothing */
	APIInitNeigFilter_Empty,

	/** Filter line type neigs only */
	APIInitNeigFilter_On,

	/** Filter node type neigs only */
	APIInitNeigFilter_Node

} API_InitNeigFilterID;


// =============================================================================
// Rubberline feedback
//
// =============================================================================

/**
 * @brief Rubber line thickness
 * @ingroup UserInput
 */
typedef enum {
	/** Simple rubber line */
	APIRubberLine_Simple			= 1,

	/** Double rubber line */
	APIRubberLine_Double			= 2

} API_RubberLineThickness;

/**
 * @brief Defines the modes for placing an arc
 * @ingroup UserInput
 */
typedef enum {
	/** Define arc by origo point and radius */
	APIRubberArc_OrigoAngles		= 0,

	/** Define arc by three points */
	APIRubberArc_ThreePoint			= 1

} API_RubberArcTypeID;

/**
 * @brief Rubber line definition.
 * @struct API_RubberLineType
 * @ingroup UserInput
 * @remarks See @ref ACAPI_UserInput_DrawRubberLine for utilization and example of @c API_RubberLineType.
 */
struct API_RubberLineType {

/**
 * @brief The start coordinate of the rubber line to draw.
 * @var c1
 */
	API_Coord3D						c1;

/**
 * @brief The end coordinate of the rubber line to draw.
 * @var c2
 */
	API_Coord3D						c2;

/**
 * @brief The thickness of the line, can be @c APIRubberLine_Simple or @c APIRubberLine_Double.
 * @var lineThick
 */
	API_RubberLineThickness			lineThick;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	Int32							filler[3];

};

/**
 * @brief Rubber line definition.
 * @struct API_RubberArcType
 * @ingroup UserInput
 * @remarks See @ref ACAPI_UserInput_DrawRubberArc for utilization and example of @c API_RubberArcType.
 */
struct API_RubberArcType {

/**
 * @brief Coordinate of the center point
 * @var origC
 */
	API_Coord3D						origC;

/**
 * @brief Draw radii as well
 * @var radii
 */
	bool							radii;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	char							filler[7];

/**
 * @brief The thickness of the line, can be @c APIRubberLine_Simple or @c APIRubberLine_Double.
 * @var lineThick
 */
	API_RubberLineThickness			lineThick;

/**
 * @brief The arc is defined with @c arc2D (used only in 2D) or @c arc3D structure (@c APIRubberArc_OrigoAngles or @c APIRubberArc_ThreePoint).
 * @var arcType
 */
	API_RubberArcTypeID				arcType;
	union {
		struct {												// circle or elliptic arc defined by its origo and two angles - only in 2D

/**
 * @brief Radius (or 'a' if ellipse)
 * @var r
 */
			double					r;

/**
 * @brief This value should be 0.0 in circle case or the angle of the 'a' axis of the ellipse
 * @var angle
 */
			double					angle;

/**
 * @brief This value should be 1.0 in circle case or 'a/b' of the ellipse
 * @var ratio
 */
			double					ratio;

/**
 * @brief Beginning angle of the arc
 * @var begAng
 */
			double					begAng;

/**
 * @brief Ending angle of the arc
 * @var endAng
 */
			double					endAng;

		} arc2D;

		struct {
/**
 * @brief Beginning point of the circular arc (defined by its origo and two points - for 3D)
 * @var begC
 */
			API_Coord3D				begC;

/**
 * @brief End point of the circular arc (defined by its origo and two points - for 3D)
 * @var endC
 */
			API_Coord3D				endC;

/**
 * @brief The angle of the circular arc (defined by its origo and two points - for 3D).
 * 		  + (true) or - (false)
 * @var sign
 */
			bool					sign;

/**
 * @brief Reserved for later use.
 * @var filler
 */
			char					filler[7];
		} arc3D;
	};

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[8];
};

/**
 * @brief Parameters of the rubber line callback function.
 * @ingroup UserInput
 * @struct API_RubberLineInfo
 * @remarks See @ref RubberLineInfoProc for more information and the @ref ACAPI_UserInput_DrawRubberLine function for example
 * 			of using the rubber line drawing callback function.
 */
struct API_RubberLineInfo {

/**
 * @brief The actual mouse coordinate
 * @var actCoord
 */
	API_Coord3D						actCoord;

/**
 * @brief The callback function is called from drawing or deleting phase
 * @var drawFlag
 */
	bool							drawFlag;

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
	Int32							filler_3[3];

};


// =============================================================================
// Point input
//
// =============================================================================

/**
 * @brief Parameters of the point input operation.
 * @struct API_GetPointType
 * @ingroup UserInput
 * @remarks For the utilization of @c API_GetPointType see the @ref ACAPI_UserInput_GetPoint function.
 */
struct API_GetPointType {

/**
 * @brief [in] Prompt string to be displayed in the control box during input
 * @var prompt
 */
	char							prompt[256];

/**
 * @brief [in] Use the @c filter field for filtering neigs during input
 * @var changeFilter
 */
	bool							changeFilter;

/**
 * @brief [in] Use the @c cursorSet field for changing cursor forms
 * @var changeCursorSet
 */
	bool							changeCursorSet;

/**
 * @brief [in] Use the @c planeCoord and @c planeNormal fields for defining input plane
 * @var changePlane
 */
	bool							changePlane;

/**
 * @brief [in] Enabling Quick Selection (magnetic cursor)
 * @var enableQuickSelection
 */
	bool							enableQuickSelection;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief [in] Neig filter for cursor snapping. See @ref ACAPI_UserInput_InitNeigFilter
 * @var filter
 */
	API_NeigFilter					filter;

/**
 * @brief [in] Cursor set for customized visual feedback
 * @var cursorSet
 */
	API_CursorSet					cursorSet;

/**
 * @brief [in] A point of the input plane
 * @var planeCoord
 */
	API_Coord3D						planeCoord;

/**
 * @brief [in] The normal vector of the input plane
 * @var planeNormal
 */
	API_Vector3D					planeNormal;

/**
 * @brief [out] The coordinate of the clicked point
 * @var pos
 */
	API_Coord3D						pos;

/**
 * @brief [out] The neig found at the clicked point
 * @var neig
 */
	API_Neig						neig;


/**
 * @brief [out] Guid of the clicked element.
 * @var guid
 */
	API_Guid						guid;

/**
 * @brief [out] Database elem index of the clicked element.
 * @var dbElemIdx
 */
	Int32							dbElemIdx;

/**
 * @brief [out] Index of the clicked body in the clicked element.
 * @var bodyIdx
 */
	Int32							bodyIdx;

/**
 * @brief [out] Index of the clicked polygon in the clicked body.
 * @var ipgon
 */
	ULong							ipgon;

};

// =============================================================================
// Get 3D component
//
// =============================================================================

/**
 * @brief Parameters of the get component type in 3D operation.
 * @ingroup UserInput
 * @struct API_Get3DComponentType
 * @remarks For the utilization of @c API_Get3DComponentType see the @ref ACAPI_UserInput_GetPoint function.
 */
struct API_Get3DComponentType {

/**
 * @brief Guid of the pointed element, or @c APINULLGuid, if no element is pointed.
 * @var guid
 */
	API_Guid		guid;

/**
 * @brief Index of the pointed element.
 * @var dbElemIdx
 */
	Int32			dbElemIdx;

/**
 * @brief Index of the pointed body in the pointed element.
 * @var bodyIdx
 */
	Int32			bodyIdx;

/**
 * @brief Index of the pointed polygon in the pointed element.
 * @var ipgon
 */
	ULong			ipgon;

/**
 * @brief Model coordinate of the point.
 * @var c3
 */
	API_Coord3D		c3;

/**
 * @brief Normal vector of the pointed polygon.
 * @var normal
 */
	API_Coord3D		normal;

};


// =============================================================================
// Line input
//
// =============================================================================

/**
 * @brief Parameters of the line input operation.
 * @struct API_GetLineType
 * @ingroup UserInput
 * @remarks For the utilization of @c API_GetLineType see the @ref ACAPI_UserInput_GetLine function.
 */
struct API_GetLineType {

/**
 * @brief [in] Prompt string to be displayed in the control box during input
 * @var prompt
 */
	char							prompt[256];

/**
 * @brief [in] Use the @c filter field for filtering neigs during input
 * @var changeFilter
 */
	bool							changeFilter;

/**
 * @brief [in] Use the @c cursorSet field for changing cursor forms
 * @var changeCursorSet
 */
	bool							changeCursorSet;

/**
 * @brief [in] Use the @c startCoord and @c planeNormal fields to define the input plane
 * @var changePlane
 */
	bool							changePlane;

/**
 * @brief Disable the default line drawing feedback.
 * @var disableDefaultFeedback
 */
	bool							disableDefaultFeedback;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief [in] Neig filter for cursor snapping. See @ref ACAPI_UserInput_InitNeigFilter
 * @var filter
 */
	API_NeigFilter					filter;

/**
 * @brief [in] Cursor set for customized visual feedback
 * @var cursorSet
 */
	API_CursorSet					cursorSet;

/**
 * @brief [in] The normal vector of the input plane
 * @var planeNormal
 */
	API_Vector3D					planeNormal;

/**
 * @brief [in] The start coordinate of the line
 * @var startCoord
 */
	API_Coord3D						startCoord;

/**
 * @brief [out] The end coordinate of the line
 * @var pos
 */
	API_Coord3D						pos;

/**
 * @brief [out] The neig found at the end point
 * @var neig
 */
	API_Neig						neig;

};


// =============================================================================
// Arc input
//
// =============================================================================

/**
 * @brief Parameters of the arc input operation.
 * @struct API_GetArcType
 * @ingroup UserInput
 * @remarks For the utilization of @c API_GetArcType see the @ref ACAPI_UserInput_GetArc function.
 */
struct API_GetArcType {

/**
 * @brief [in] Prompt string to be displayed in the control box during input
 * @var prompt
 */
	char							prompt[256];

/**
 * @brief [in] Use the start coordinate specified in the @c startCoord field
 * @var startCoordGiven
 */
	bool							startCoordGiven;

/**
 * @brief [out] Negative (clockwise) arc has been entered
 * @var negArc
 */
	bool							negArc;

/**
 * @brief [in] Use the @c cursorSet field for changing cursor forms
 * @var changeCursorSet
 */
	bool							changeCursorSet;

/**
 * @brief Disable the default feedback drawing.
 * @var disableDefaultFeedback
 */
	bool							disableDefaultFeedback;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief [in] Cursor set for customized visual feedback
 * @var cursorSet
 */
	API_CursorSet					cursorSet;

/**
 * @brief [in] The center coordinate of the arc
 * @var origo
 */
	API_Coord3D						origo;

/**
 * @brief [in/out] The start coordinate of the arc
 * @var startCoord
 */
	API_Coord3D						startCoord;

/**
 * @brief [out] The end coordinate of the arc
 * @var pos
 */
	API_Coord3D						pos;

/**
 * @brief [out] The neig found at the end point
 * @var neig
 */
	API_Neig						neig;

};


// =============================================================================
// Polygon input
//
// =============================================================================

/**
 * @brief Parameters of the polygon input operation.
 * @struct API_RubberPolyCallbacks
 * @ingroup UserInput
 * @remarks For the utilization of @ref API_RubberPolyCallbacks see the @ref ACAPI_UserInput_GetPoly.
 */
struct API_RubberPolyCallbacks {

/**
 * @brief [in] Callback function for custom feedback drawing. See the @c RubberLineInfoProc.
 * @var rubberLineInfoProc
 */
	GSPtr 							*rubberLineInfoProc;

/**
 * @brief [in] Callback function to query the 3D component. See the @c Get3DComponentProc.
 * @var get3DComponentProc
 */
	GSPtr							*get3DComponentProc;

/**
 * @brief [in] Callback function for custom feedback editing polygons. See the @c AddPolyNodeProc.
 * @var addPolyNodeProc
 */
	GSPtr							*addPolyNodeProc;

/**
 * @brief [in] Callback function for custom feedback editing polygons. See the @c DelPolyNodeProc.
 * @var delPolyNodeProc
 */
	GSPtr							*delPolyNodeProc;

};

/**
 * @brief The polygon input method.
 * @ingroup UserInput
 */
typedef enum {
	/** Gets an arbitrary closed polygon */
	APIPolyGetMethod_General,

	/** Gets a rectangle */
	APIPolyGetMethod_Rect,

	/** Gets a base vector then a rectangle perpendicular to it */
	APIPolyGetMethod_RotRect,

	/** Gets a polyline (can be open) */
	APIPolyGetMethod_Polyline

} API_PolyGetMethod;

/**
 * @brief Parameters of the polygon input operation.
 * @struct API_GetPolyType
 * @ingroup UserInput
 * @remarks For the utilization of @c API_GetPolyType see the @ref ACAPI_UserInput_GetPoly function.
 */
struct API_GetPolyType {

/**
 * @brief [in] Prompt string to be displayed in the control box during input
 * @var prompt
 */
	char							prompt[256];

/**
 * @brief [in] Use the @c cursorSet field for changing cursor forms
 * @var changeCursorSet
 */
	bool							changeCursorSet;

/**
 * @brief [in] Use the @c startCoord and @c planeNormal fields for defining the input plane
 * @var changePlane
 */
	bool							changePlane;

/**
 * @brief [in] Disable the default polygon drawing feedback
 * @var disableDefaultFeedback
 */
	bool							disableDefaultFeedback;

/**
 * @brief [in] Retrieve z coordinates in case of 3D input
 * @var getZCoords
 */
	bool							getZCoords;

/**
 * @brief [in] The polygon input method
 * 		  | Value | Meaning |
 * 		  |-------|---------|
 * 		  | @c APIPolyGetMethod_General | Gets an arbitrary closed polygon |
 * 		  | @c APIPolyGetMethod_Rect | Gets a rectangle |
 * 		  | @c APIPolyGetMethod_RotRect | Gets a base vector then a rectangle perpendicular to it |
 * 		  | @c APIPolyGetMethod_Polyline | Gets a polyline (can be open) |
 * @var method
 */
	API_PolyGetMethod				method;

/**
 * @brief [in] Cursor set for customized visual feedback
 * @var cursorSet
 */
	API_CursorSet					cursorSet;

/**
 * @brief [in] The normal vector of the input plane
 * @var planeNormal
 */
	API_Vector3D					planeNormal;

/**
 * @brief [in] The start coordinate of the polygon
 * @var startCoord
 */
	API_Coord3D						startCoord;

/**
 * @brief [out] The polygon coordinates (projected vertically to the input plane), indexed from 1 to @c nCoords. The first coordinate is the same as the last one
 * @var coords
 */
	API_Coord						**coords;

/**
 * @brief [out] The polygon arcs segments, indexed from 1 to @c nArcs
 * @var parcs
 */
	API_PolyArc						**parcs;

/**
 * @brief [out] The number of the polygon coordinates
 * @var nCoords
 */
	Int32							nCoords;

/**
 * @brief [out] The number of curves in the polygon
 * @var nArcs
 */
	Int32							nArcs;

/**
 * @brief [out] The closing neig of the polygon
 * @var neig
 */
	API_Neig						neig;

/**
 * @brief [out] Handle containing the z coordinates of the corresponding polygon nodes (retrieved only on demand by passing @c true in @c getZCoords)
 * @var zCoords
 */
	double							**zCoords;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief [out] Polyline contour has been entered
 * @var polylineWas
 */
	bool							polylineWas;

/**
 * @brief [out] Use standard polygon input palette
 * @var useStandardPetPalette
 */
	bool							useStandardPetPalette;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool							filler_2[2];

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3;

};


// =============================================================================
// Drawing constraints for input
//
// =============================================================================

/**
 * @brief Type of the drawing constraint.
 * @ingroup UserInput
 * @remarks For the utilization of @c API_ConstraintType see the @ref ACAPI_UserInput_SetConstraint function.
 * 			When fixing the input angle (`APIConst_A`), `constValue` is defined in radian
 */
typedef enum {
	/** Constraint by X */
	APIConst_X						= 1,

	/** Constraint by Y */
	APIConst_Y						= 2,

	/** Constraint by Z */
	APIConst_Z						= 3,

	/** Constraint by angle */
	APIConst_A						= 4,

	/** Constraint by radian */
	APIConst_R						= 5

} API_ConstraintType;

/**
 * @brief Parameters of the drawing constraint.
 * @struct API_ConstraintPars
 * @ingroup UserInput
 * @remarks For the utilization of @c API_ConstraintPars see the @ref ACAPI_UserInput_SetConstraint interface function.
 */
struct API_ConstraintPars {

/**
 * @brief Type of the drawing constraint.
 * @var constType
 */
	API_ConstraintType				constType;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief The value of the constraint.
 * @var constValue
 */
	double							constValue;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	double							filler_2[2];

/**
 * @brief Use the project origin or the last clicked point (locOrigo) as the reference point.
 * @var useLocOrigo
 */
	bool							useLocOrigo;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	bool							filler_3;

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	short							filler_4[3];

};


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

/**
 * @brief Messages sent to the add-on's palette.
 * @ingroup Dialog
 */
typedef enum {
	/** The API asks the add-on to close its palette. */
	APIPalMsg_ClosePalette			= 1,

	/** Your palette should be hidden for some reason, e.g. the user chose @b Hide @b All @b Palettes from the menu. */
	APIPalMsg_HidePalette_Begin		= 2,

	/** The palette can be shown again if needed. */
	APIPalMsg_HidePalette_End		= 3,

	/** Certain palette items should be disabled, because the user is performing an input. This is necessary because you shouldn't make any modifications to the database during input. */
	APIPalMsg_DisableItems_Begin	= 4,

	/** The reason behind @c APIPalMsg_DisableItems_Begin is gone; you can enable the items on the palette. */
	APIPalMsg_DisableItems_End		= 5,

	/** Sent when the palette should be opened automatically as set in the Work Environment. Your palette should pass a GUID when created: @c DG::Palette (resourceId, paletteGuid) to make this work. */
	APIPalMsg_OpenPalette			= 6,

	/**
	 * The Work Environment queries the palette for its visibility status on closing the current document/quitting the application. If you return @c true in @c param (really a @c bool*),
	 * then Archicad will send a @c APIPalMsg_OpenPalette to your add-on on next launch, so that you can re-open your add-on's palette.
	 */
	APIPalMsg_IsPaletteVisible		= 7,

	/** returns the API_PaletteDeactivationMethod */
	APIPalMsg_GetPaletteDeactivationMethod		= 8

} API_PaletteMessageID;

/**
 * @brief Deactivation method of the palette.
 * @ingroup Dialog
 */
typedef enum {
	/** disable palette items if it is docked before deactivation, hide palette if it is undocked before deactivation */
	APIPaletteDeactivationMethod_Default		= 1,

	/** hide palette when it is deactivated */
	APIPaletteDeactivationMethod_Hide			= 2,

	/** disable palette items when it is deactivated */
	APIPaletteDeactivationMethod_DisableItems	= 3

} API_PaletteDeactivationMethod;


// =============================================================================
// Pet Palette control
//
// =============================================================================

/**
 * @brief Parameters for performing user input with pet palette.
 * @struct API_PetPaletteType
 * @ingroup Dialog
 * @remarks This structure holds the input parameters for the @ref ACAPI_Dialog_PetPalette interface
 * 			function. The help handling is changed because of the new help system. There are help anchor strings instead of
 * 			the context help texts now, and tooltip strings. You should use the 'DHLP' resource, you can store the tooltip
 * 			string and context help anchor pairs in one resource. For more details see @ref ACAPI_Dialog_PetPalette.
 */
struct API_PetPaletteType {

/**
 * @brief Unique identifier of the pet palette.
 * @var petPaletteID
 */
	short							petPaletteID;

/**
 * @brief Number of columns in the picture.
 * @var nCols
 */
	short							nCols;

/**
 * @brief Number of columns in the picture.
 * @var nRows
 */
	short							nRows;

/**
 * @brief The actual value of the control (starts from 1).
 * @var value
 */
	short							value;

/**
 * @brief The disabled items of the control.
 * @var grayBits
 */
	UInt32							grayBits;

/**
 * @brief Handle of the array of the 'GICN' resource IDs of the pet items; each item should be 22x22 pixels.
 * @var petIconIDsHdl
 */
	short**							petIconIDsHdl;

/**
 * @brief 'DHLP' resource ID (the tooltip and help anchor pairs).
 * @var dhlpResourceID
 */
	short							dhlpResourceID;

/**
 * @brief Previously used to be @c toolTipStrListID, now obsolete, not used.
 * @var obsolete
 */
	short							obsolete;

/**
 * @brief Resource module to load the icon resource from.
 * @var petIconResModule
 */
	GSResModule						petIconResModule;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1[5];

};



// =============================================================================
// User Control callbacks
//
// =============================================================================

/**
 * @brief Describes the different types of user controls.
 * @ingroup Dialog
 * @remarks These are the special constants used in @ref ACAPI_Dialog_SetUserControlCallback (...) function. They define the attribute set used in the user control.
 */
typedef enum {
	/** pen control */
	APIUserControlType_Pen,

	/** pen control with background pen */
	APIUserControlType_PenWithNull,

	/** polygon fill control (drafting fills) */
	APIUserControlType_PolyFill,

	/** wall fill control (cut fills) */
	APIUserControlType_WallFill,

	/** wall fill control without composites */
	APIUserControlType_WallCompFill,

	/** all fill types control */
	APIUserControlType_AllFill,

	/** all fill types without composites */
	APIUserControlType_AllFillGradNoComp,

	/** fill control like in the Wall Settings dialog */
	APIUserControlType_WallSetsFill,

	/** composite control like in the Wall Settings dialog */
	APIUserControlType_WallComposites,

	/** fill control like in the Slab Settings dialog */
	APIUserControlType_SlabSetsFill,

	/** composite control like in the Slab Settings dialog */
	APIUserControlType_SlabComposites,

	/** fill control like in the Roof Settings dialog */
	APIUserControlType_RoofSetsFill,

	/** composite control like in the Roof Settings dialog */
	APIUserControlType_RoofComposites,

	/** fill control like in the Shell Settings dialog */
	APIUserControlType_ShellSetsFill,

	/** composite control like in the Shell Settings dialog */
	APIUserControlType_ShellComposites,

	/** fill control containing composite fills only */
	APIUserControlType_OnlyCompFill,

	/** material control */
	APIUserControlType_Material,

	/** material control with general material */
	APIUserControlType_MaterialWithGeneral,

	/** layer control */
	APIUserControlType_Layer,

	/** zone category control */
	APIUserControlType_ZoneCategory,

	/** dashed line control */
	APIUserControlType_DashedLine,

	/** all line types */
	APIUserControlType_SymbolLine,

	/** cover fill type control */
	APIUserControlType_CoverFill,

	/** wall profiles control */
	APIUserControlType_WallProfile,

	/** beam profiles control */
	APIUserControlType_BeamProfile,

	/** column profiles control */
	APIUserControlType_ColumnProfile,

	/** all profiles control */
	APIUserControlType_AllProfile,

	/** polygon fill control with gradient fills */
	APIUserControlType_PolyFillWithGradient,

	/** building material control */
	APIUserControlType_BuildingMaterial,

	/** handrail profiles control */
	APIUserControlType_HandrailProfile,

	/** other GDL object profiles control */
	APIUserControlType_OtherGDLObjectProfile,

	/** column and beam profile control */
	APIUserControlType_BeamAndColumnProfile,

} API_UserControlType;

/**
 * @brief Describes the attribute set to be used in a user control dialog item.
 * @struct API_UCCallbackType
 * @ingroup Dialog
 * @remarks This structure is used in the @ref ACAPI_Dialog_SetUserControlCallback (...) function.
 */
struct API_UCCallbackType {

/**
 * @brief The attribute set to be used.
 * @var type
 */
	API_UserControlType				type;

/**
 * @brief The identifier of the dialog or tab page.
 * @var dialogID
 */
	short							dialogID;

/**
 * @brief The dialog item identifier.
 * @var itemID
 */
	short							itemID;

};


// =============================================================================
// Object Settings Dialog
//
// =============================================================================

/**
 * @brief Defines the parameters of the Object Settings dialog.
 * @struct API_ObjectSettingsPars
 * @ingroup Dialog
 * @remarks See the remarks and the example for @ref ACAPI_Dialog_ObjectSettings().
 */
struct API_ObjectSettingsPars {

/**
 * @brief [in/out] the default symbol on input; the selected symbol on output
 * @var elemDef
 */
	API_Element						elemDef;

/**
 * @brief [in] defines which fields of @c elemDef should be used only
 * @var elemMask
 */
	API_Element						elemMask;

/**
 * @brief [out] additional symbol parameters
 * @var addPars
 */
	API_AddParType					**addPars;

/**
 * @brief [out] The GUID of the object's subtype.
 * @var subtypeID
 */
	char							subtypeID [128];

/**
 * @brief [out] library index of individually assigned property object to be linked to the element ( @c 0 value means no property assigned individually)
 * @var propIndivLibInd
 */
	Int32							propIndivLibInd;

/**
 * @brief [out] matching properties by criteria need to be linked to the element
 * @var propCriteria
 */
	bool							propCriteria;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	char							filler_1[3];

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[31];

};



// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief Describes the type and the push check for creating an attribute picker in @ref ACAPI_Dialog_CreateAttributePicker.
 * @class API_AttributePickerParams
 * @ingroup Attribute
 * @ingroup Dialog
 * @since Archicad 26
 */
struct API_AttributePickerParams {
/**
 * @brief Type of the push check item appearance in the button.
 */
	enum class PushCheckAppearance {
		ArrowIconAndText,
		ArrowOnly
	};

/**
 * @brief Tells what should happen with the selection during opening the popup, when the selected attribute index is not in the usable attribute set.
 */
	enum class EmptySelectionBehaviour {
		SelectFirst,
		SelectNothing
	};

/**
 * @brief The appearance of locked layers in the Layer Picker.
 */
	enum class LockedLayersStatus {
		Disabled,
		Enabled
	};

/**
 * @brief Requested type of the user control.
 * @var type
 * @remarks Supported types in version 26 and later:
 * @li @c APIUserControlType_Layer
 * @li @c APIUserControlType_BuildingMaterial
 * @li @c APIUserControlType_WallComposites
 * @li @c APIUserControlType_SlabComposites
 * @li @c APIUserControlType_RoofComposites
 * @li @c APIUserControlType_ShellComposites
 * @li @c APIUserControlType_OnlyCompFill
 * @li @c APIUserControlType_AllProfile
 * @li @c APIUserControlType_WallProfile
 * @li @c APIUserControlType_BeamProfile
 * @li @c APIUserControlType_ColumnProfile
 * @li @c APIUserControlType_HandrailProfile
 * @li @c APIUserControlType_OtherGDLObjectProfile
 * @li @c APIUserControlType_Material
 * @li @c APIUserControlType_MaterialWithGeneral
 * @remarks Supported types in version 27 and later:
 * @li @c APIUserControlType_PolyFill
 * @li @c APIUserControlType_WallFill
 * @li @c APIUserControlType_WallCompFill
 * @li @c APIUserControlType_AllFillGradNoComp
 * @li @c APIUserControlType_CoverFill
 * @li @c APIUserControlType_PolyFillWithGradient
 * @li @c APIUserControlType_DashedLine
 * @li @c APIUserControlType_SymbolLine
 */
	API_UserControlType				type;

/**
 * @brief Id of the dialog of picker.
 * @var dialogID
 */
	short							dialogID = 0;
/**
 * @brief Id of the push check of picker.
 * @var itemID
 */
	short							itemID = 0;

/**
 * @brief Defines whether the push check item should contain only an arrow icon pointing to right (@c PushCheckAppearance::ArrowOnly),
 * 		  or an icon and a text part also ( @c PushCheckAppearance::ArrowIconAndText).
 * @var pushCheckAppearance
 */
	PushCheckAppearance				pushCheckAppearance;

/**
 * @brief Tells what should happen with the selection during opening the popup, when the selected attribute index is not in the usable attribute set.
 * 		  Either the first attribute should be selected (@c EmptySelectionBehaviour::SelectFirst) or nothing should be selected in the appearing popup
 * 		  ( @c EmptySelectionBehaviour::SelectNothing).
 * @var emptySelectionBehaviour
 */
	EmptySelectionBehaviour			emptySelectionBehaviour;

/**
 * @brief Layer specific data that controls the appearance of locked layers in the Layer Picker.
 * 		  The value @c LockedLayersStatus::Disabled tells that locked layers are gray and unselectable. The default value of this field is @c LockedLayersStatus::Enabled.
 * @var lockedLayersStatus
 */
	LockedLayersStatus				lockedLayersStatus;

	API_AttributePickerParams () :
		pushCheckAppearance (PushCheckAppearance::ArrowOnly),
		emptySelectionBehaviour (EmptySelectionBehaviour::SelectFirst)
	{
		lockedLayersStatus = LockedLayersStatus::Enabled;
	}
};


/**
 * @brief Describes an attribute picker created in @ref ACAPI_Dialog_CreateAttributePicker, with getter and setter for the selected attribute and the hanlder of push check click event.
 * @class API_AttributePicker
 * @ingroup Dialog
 * @ingroup Attribute
 * @since Archicad 26
 */
class API_AttributePicker {
public:
	virtual ~API_AttributePicker ();


/**
 * @brief Returns the index of the selected attribute.
 * @return the selected attribute's index
 */
	virtual API_AttributeIndex	GetSelectedAttributeIndex () const = 0;

/**
 * @brief Sets the index of the attribute to select.
 * @param index the index of the attribute to select.
 */
	virtual void				SetSelectedAttributeIndex (const API_AttributeIndex& index) = 0;


/**
 * @brief Handles click event to the push check: shows the picker popup dialog.
 * @return True if OK was clicked in the popup dialog, false otherwise.
 */
	virtual bool				Invoke () = 0;

/**
 * @brief Refreshes the dialogicon and the caption in the pushcheck.
 */
	virtual void				Refresh () = 0;


/**
 * @return Returns the @ref API_UserControlType param which was used to create itself.
 */
	virtual API_UserControlType GetUserControlType () = 0;

};

/**
 * @brief Describes the type and the push check for creating an attribute folder picker in @ref ACAPI_Attribute_CreateAttributeFolderPicker.
 * @struct API_AttributeFolderPickerParams
 * @ingroup Attribute
 * @ingroup Dialog
 * @since Archicad 26
 */
struct API_AttributeFolderPickerParams {
/**
 * @brief Type of the push check item appearance in the button.
 */
	enum class PushCheckAppearance {
		ArrowIconAndText,
		ArrowOnly
	};

/**
 * @brief Requested type of the user control.
 * @var type
 */
	API_UserControlType				type;

/**
 * @brief Id of the dialog of picker.
 * @var dialogID
 */
	short							dialogID = 0;

/**
 * @brief Id of the attribute picker control.
 * @var itemID
 */
	short							itemID = 0;

/**
 * @brief Defines whether the push check item should contain only an arrow icon pointing to right (@c PushCheckAppearance::ArrowOnly),
 * 		  or an icon and a text part also ( @c PushCheckAppearance::ArrowIconAndText).
 * @var pushCheckAppearance
 */
	PushCheckAppearance				pushCheckAppearance;
};


/**
 * @brief Describes an attribute folder picker created in @ref ACAPI_Attribute_CreateAttributeFolderPicker, with getter and setter for the selected attribute folder and the hanlder of push check click event.
 * @class API_AttributeFolderPicker
 * @ingroup Attribute
 * @since Archicad 26
 */
class API_AttributeFolderPicker {
public:
	virtual ~API_AttributeFolderPicker ();


/**
 * @brief Returns the selected attribute folder.
 * @return API_AttributeFolder type.
 */
	virtual API_AttributeFolder	GetSelectedAttributeFolder () const = 0;

/**
 * @brief Selects an attribute folder in the picker.
 * @param folder [in], the attribute folder to select.
 */
	virtual void				SetSelectedAttributeFolder (const API_AttributeFolder& folder) = 0;


/**
 * @brief Handles click event to the push check: shows the picker popup dialog.
 * @return True if OK was clicked in the popup dialog, false otherwise.
 */
	virtual bool				Invoke () = 0;

};


#endif
