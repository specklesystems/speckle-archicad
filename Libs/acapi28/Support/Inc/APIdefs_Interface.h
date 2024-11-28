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

#define API_MenuItemDisabled		0x00000001
#define API_MenuItemChecked			0x00000002

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
 * @enum API_ProcessControlTypeID
 * @ingroup ProcessWindow
 * @remarks Used in @ref ACAPI_ProcessWindow_InitProcessWindow.
 */
typedef enum {
	API_MenuCommandEnabled,
	API_MenuCommandDisabled

} API_ProcessControlTypeID;


// =============================================================================
// Cursor Forms
//
// =============================================================================

/**
 * @brief Predefined cursor forms for customizing the user input.
 * @enum API_CursorFormID
 * @ingroup UserInput
 * @remarks The @ref API_CursorFormID values are used to specify the cursor set for a user input process invoked from the API tool add-on.
 * 			|Form|Icon|Description|
 * 			|---|---|---|
 * 			|`APICursor_UserDefined`| |Cursor defined by resource ID (NOT USED)|
 * 			|`APICursor_Default`| |Default cursor shape|
 * 			|`APICursor_Spin`|![SpinCursor](@ref cf_SpinCursor.png)|Spin cursor (rotating beach balls)|
 * 			|`APICursor_SystemArrow`| |System arrow cursor|
 * 			|`APICursor_SystemClock`| |System clock cursor|
 * 			|`APICursor_IBeam`|![IBeamCursor](@ref cf_IBeamCursor.png)|I beam cursor for text editing|
 * 			|`APICursor_Drag`|![DragCursor](@ref cf_DragCursor.png)|Cursor for dragging windows|
 * 			|`APICursor_Trident`|![TridentCursor](@ref cf_TridentCursor.png)|Trident cursor for dragging rollrect|
 * 			|`APICursor_ZoomIn`|![ZoomInCursor](@ref cf_ZoomInCursor.png)|Zoom in cursor|
 * 			|`APICursor_ZoomOut`|![ZoomOutCursor](@ref cf_ZoomOutCursor.png)|Zoom out cursor|
 * 			|`APICursor_Hand`|![HandCursor](@ref cf_HandCursor.png)|Hand cursor|
 * 			|`APICursor_MiniHand`|![MiniHandCursor](@ref cf_MiniHandCursor.png)|Small hand cursor|
 * 			|`APICursor_Cross`|![CrossCursor](@ref cf_CrossCursor.png)|Cross cursor|
 * 			|`APICursor_Check`|![CheckCursor](@ref cf_CheckCursor.png)|Check cursor (indicates ...Neig)|
 * 			|`APICursor_CheckRef`|![CheckRefCursor](@ref cf_CheckRefCursor.png)|Check cursor (thick)|
 * 			|`APICursor_Branch`|![BranchCursor](@ref cf_BranchCursor.png)|Branch cursor (indicates ...OnNeig)|
 * 			|`APICursor_BranchRef`|![BranchRefCursor](@ref cf_BranchRefCursor.png)|Branch cursor (thick)|
 * 			|`APICursor_XPoint`|![XPointCursor](@ref cf_XPointCursor.png)|Cross point cursor|
 * 			|`APICursor_Normal`|![NormalCursor](@ref cf_NormalCursor.png)|Normal (perpendicular) cursor|
 * 			|`APICursor_Tangent`|![TangentCursor](@ref cf_TangentCursor.png)|Tangent (osculation) cursor|
 * 			|`APICursor_Arrow`|![ArrowCursor](@ref cf_ArrowCursor.png)|Arrow cursor (selection mode)|
 * 			|`APICursor_ArrowCheck`|![ArrowCheckCursor](@ref cf_ArrowCheckCursor.png)|Check cursor in arrow mode|
 * 			|`APICursor_ArrowCheckRef`|![ArrowCheckRefCursor](@ref cf_ArrowCheckRefCursor.png)|Check cursor in arrow mode (thick)|
 * 			|`APICursor_ArrowBranch`|![ArrowBranchCursor](@ref cf_ArrowBranchCursor.png)|Branch cursor in arrow mode|
 * 			|`APICursor_ArrowBranchRef`|![ArrowBranchRefCursor](@ref cf_ArrowBranchRefCursor.png)|Branch cursor in arrow mode (thick)|
 * 			|`APICursor_ArrowXPoint`|![ArrowXPointCursor](@ref cf_ArrowXPointCursor.png)|Cross point cursor in arrow mode|
 * 			|`APICursor_ArrowNormal`|![ArrowNormalCursor](@ref cf_ArrowNormalCursor.png)|Normal cursor in arrow mode|
 * 			|`APICursor_ArrowTangent`|![ArrowTangentCursor](@ref cf_ArrowTangentCursor.png)|Tangent cursor in arrow mode|
 * 			|`APICursor_Pencil`|![PencilCursor](@ref cf_PencilCursor.png)|Pencil shaped cursor during input|
 * 			|`APICursor_PencilCheck`|![PencilCheckCursor](@ref cf_PencilCheckCursor.png)|Check cursor during input|
 * 			|`APICursor_PencilCheckRef`|![PencilCheckRefCursor](@ref cf_PencilCheckRefCursor.png)|Check cursor during input (thick)|
 * 			|`APICursor_PencilBranch`|![PencilBranchCursor](@ref cf_PencilBranchCursor.png)|Branch cursor during input|
 * 			|`APICursor_PencilBranchRef`|![PencilBranchRefCursor](@ref cf_PencilBranchRefCursor.png)|Branch cursor during input (thick)|
 * 			|`APICursor_PencilXPoint`|![PencilXPointCursor](@ref cf_PencilXPointCursor.png)|Cross point cursor during input|
 * 			|`APICursor_PencilNormal`|![PencilNormalCursor](@ref cf_PencilNormalCursor.png)|Normal cursor during input|
 * 			|`APICursor_PencilTangent`|![PencilTangentCursor](@ref cf_PencilTangentCursor.png)|Tangent cursor during input|
 * 			|`APICursor_Eye`|![EyeCursor](@ref cf_EyeCursor.png)|Eye cursor for window/door opening|
 * 			|`APICursor_DoubleEye`|![DoubleEyeCursor](@ref cf_DoubleEyeCursor.png)|Double eye for window/door position|
 * 			|`APICursor_Hammer`|![HammerCursor](@ref cf_HammerCursor.png)|Hammer cursor for completing input|
 * 			|`APICursor_MagicWand`|![MagicWandCursor](@ref cf_MagicWandCursor.png)|Magic wand cursor|
 * 			|`APICursor_Trimmer`|![TrimmerCursor](@ref cf_TrimmerCursor.png)|Scissors shaped cursor|
 * 			|`APICursor_TrimmerFull`|![TrimmerFullCursor](@ref cf_TrimmerFullCursor.png)|Scissors shaped cursor (thick)|
 * 			|`APICursor_Picker`|![PickerCursor](@ref cf_PickerCursor.png)|Dropper shaped cursor|
 * 			|`APICursor_PickerFull`|![PickerFullCursor](@ref cf_PickerFullCursor.png)|Dropper shaped cursor (thick)|
 * 			|`APICursor_Injection`|![InjectionCursor](@ref cf_InjectionCursor.png)|Injection shaped cursor|
 * 			|`APICursor_InjectionFull`| ![InjectionFullCursor](@ref cf_InjectionFullCursor.png) |Injection shaped cursor (thick)|
 *
 * 			For example of using custom cursor sets see @ref ACAPI_UserInput_GetArc.
 */
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
 * @enum API_InitNeigFilterID
 * @ingroup UserInput
 * @remarks For the utilization of @c API_InitNeigFilterID see the @ref ACAPI_UserInput_InitNeigFilter function.
 */
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
		struct {												// circle or elliptic arc defined by it's origo and two angles - only in 2D

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
 * @brief Beginning point of the circular arc (defined by it's origo and two points - for 3D)
 * @var begC
 */
			API_Coord3D				begC;

/**
 * @brief End point of the circular arc (defined by it's origo and two points - for 3D)
 * @var endC
 */
			API_Coord3D				endC;

/**
 * @brief The angle of the circular arc (defined by it's origo and two points - for 3D).
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

typedef enum {
	APIPolyGetMethod_General,
	APIPolyGetMethod_Rect,
	APIPolyGetMethod_RotRect,
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
 * @brief [out] Handle containing the z coordinates of the correspondong polygon nodes (retrieved only on demand by passing @c true in @c getZCoords)
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
 * @enum API_ConstraintType
 * @ingroup UserInput
 * @remarks For the utilization of @c API_ConstraintType see the @ref ACAPI_UserInput_SetConstraint function.
 * 			When fixing the input angle (`APIConst_A`), `constValue` is defined in radian
 */
typedef enum {
	APIConst_X						= 1,
	APIConst_Y						= 2,
	APIConst_Z						= 3,
	APIConst_A						= 4,
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
 * @enum API_UserControlType
 * @ingroup Dialog
 * @remarks These are the special constants used in @ref ACAPI_Dialog_SetUserControlCallback (...) function. They define the attribute set used in the user control.
 */
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
	APIUserControlType_BuildingMaterial,						// building material control
	APIUserControlType_HandrailProfile,							// handrail profile control
	APIUserControlType_OtherGDLObjectProfile,					// other gdl object profile control
	APIUserControlType_BeamAndColumnProfile,					// column and beam profile control

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
