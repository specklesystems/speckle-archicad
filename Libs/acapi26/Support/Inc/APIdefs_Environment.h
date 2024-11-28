// *********************************************************************************************************************
// API definitions - environmental data
//
// Module:			API
// Namespace:		-
// Contact person:	archicadapi@graphisoft.com
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APIDEFS_ENVIRONMENT_H)
#define APIDEFS_ENVIRONMENT_H

#if defined (_MSC_VER)
#pragma once
#endif

// --- Includes	--------------------------------------------------------------------------------------------------------

// own
#include "APIdefs_Base.h"
#include "APIdefs_Elements.h"
#include "APIdefs_Registration.h"
#include "Location.hpp"
#include "Array.hpp"
#include "HashSet.hpp"
#include <map>

struct API_PenType;

namespace NewDisplay {
	class NativeImage;
}


// --- Compiler settings -----------------------------------------------------------------------------------------------


// --- Type definitions	------------------------------------------------------------------------------------------------


struct API_LayerStat;

// =============================================================================
// Function codes and parameter descriptions
//
// =============================================================================

typedef enum {			// Codes for Environment functions
	APIEnv_ApplicationID						= 'APPL',			// par1: API_ServerApplicationInfo*		par2: ---

	APIEnv_ProjectID							= 'PROJ',			// par1: API_ProjectInfo*				par2: ---
	APIEnv_ProjectSharingID						= 'SHAR',			// par1: API_SharingInfo*				par2: ---

	APIEnv_GetProjectNotesID					= 'GPRN',			// par1: API_ProjectNoteInfo*			par2: ---
	APIEnv_ChangeProjectNotesID					= 'CPRN',			// par1: API_ProjectNoteInfo*			par2: ---

	APIEnv_GetLibrariesID						= 'GLIB',			// par1: GS::Array<API_LibraryInfo>*	par2: Int32* (embeddedLibraryIndex)
	APIEnv_SetLibrariesID						= 'SLIB',			// par1: const GS::Array<API_LibraryInfo>*	par2: ---
	APIEnv_ResetLibrariesID						= 'RLIB',			// par1: ---							par2: ---
	APIEnv_NewLibDialID							= 'NLIB',			// par1: char* (def name)				par2: IO::Location*
	APIEnv_AddLibrariesID						= 'ALIB',			// par1: IO::Location*					par2: ---
	APIEnv_CheckLibrariesID						= 'CLIB',			// par1: ---							par2: ---
	APIEnv_OverwriteLibPartID					= 'OWLP',			// par1: bool							par2: ---
	APIEnv_GetLibPartRefGuidID					= 'GLRG',			// par1: const IO::Location*			par2: API_Guid*
	APIEnv_GetLibPartUnIDStrID					= 'GLGS',			// par1: const IO::Location*			par2: char*
	APIEnv_GetLibPartLockStatusID				= 'GLLS',			// par1: const IO::Location*			par2: API_LockableStatus*					par3: [IO::Location* userCacheLibPartLocation]
	APIEnv_DeleteEmbeddedLibItemID				= 'DELI',			// par1: const IO::Location*			par2: bool (keep GSM file)					par3: bool (silent mode)
	APIEnv_DeleteEmbeddedLibItemsID				= 'DELS',			// par1: const GS::Array<IO::Location>*	par2: bool (keep GSM file)					par3: bool (silent mode)
	APIEnv_CreateFolderInLibraryID				= 'CFOL',			// par1: const IO::Location*			par2: ---
	APIEnv_CopyFilesIntoLibraryID				= 'CFIL',			// par1: const IO::Location*			par2: const GS::Array<IO::Location>*		par3: [const bool* (overwriteIfExists)]

	APIEnv_GetToolBoxModeID						= 'GTBX',			// par1: API_ToolBoxItem*				par2: ---
	APIEnv_SetToolBoxModeID						= 'STBX',			// par1: API_ToolBoxItem*				par2: ---
	APIEnv_GetToolBoxInfoID						= 'GTBI',			// par1: API_ToolBoxInfo*				par2: bool (enable hidden)

	APIEnv_IsAutoGroupOnID						= 'ISAG',			// par1: bool*							par2: ---
	APIEnv_IsSuspendGroupOnID					= 'ISSG',			// par1: bool*							par2: ---

	APIEnv_GetViewOptionsID						= 'GDOP',			// par1: API_ViewOptions*				par2: short* (model view option attribute index)
	APIEnv_ChangeViewOptionsID					= 'CDOP',			// par1: API_ViewOptions*				par2: short* (model view option attribute index)

	APIEnv_GetStorySettingsID					= 'GSTO',			// par1: API_StoryInfo*					par2: UInt32 (mask)
	APIEnv_ChangeStorySettingsID				= 'CSTO',			// par1: API_StoryCmdType*				par2: ---

	APIEnv_CreateGhostRecordID					= 'CGRE',			// par1: const API_GhostRecord*			par2: ---
	APIEnv_GetGhostRecordID						= 'GGRE',			// par1: const API_DatabaseUnId*		par2: API_GhostRecord*
	APIEnv_DeleteGhostRecordID					= 'DGRE',			// par1: const API_GhostRecord*			par2: ---
	APIEnv_ChangeGhostRecordID					= 'CHRE',			// par1: const API_GhostRecord*			par2: ---

	APIEnv_GetGhostStorySettingsID				= 'GGST',			// par1: API_GhostStoryType*			par2: ---

	APIEnv_GetPreferencesID						= 'GPRF',			// par1: API_WorkingUnitPrefs...*		par2: API_PrefsTypeID
	APIEnv_GetConvertedUnitValueID				= 'GCUV',			// par1: API_UnitConversionData*		par2: ---

	APIEnv_GetSunSetsID							= 'GSUN',			// par1: API_SunInfo*					par2: ---
	APIEnv_GetPlaceSetsID						= 'GPLA',			// par1: API_PlaceInfo*					par2: ---
	APIEnv_CanChangePlaceSetsID					= 'CCPL',			// par1: [bool*] (with dialog)			par2: ---
	APIEnv_ChangePlaceSetsID					= 'CPLA',			// par1: API_PlaceInfo*					par2: ---

	APIEnv_GetGeoLocationID						= 'GGEO',			// par1: API_GeoLocation*				par2: ---
	APIEnv_SetGeoLocationID						= 'SGEO',			// par1: API_GeoLocation*				par2: ---
	APIEnv_GetSurveyPointTransformationID		= 'SPTR',			// par1: API_Tranmat*					par2: ---
	APIEnv_IsSurveyPointVisibleID				= 'ISPV',			// par1: bool*							par2: ---
	APIEnv_SetSurveyPointVisibilityID			= 'SSPV',			// par1: bool*							par2: ---
	APIEnv_IsSurveyPointLockedID				= 'ISPL',			// par1: bool*							par2: ---
	APIEnv_SetSurveyPointLockedID				= 'SSPL',			// par1: bool*							par2: ---

	APIEnv_GetGDLDateID							= 'GGDT',			// par1: Int32*							par2: ---
	APIEnv_ChangeGDLDateID						= 'CGDT',			// par1: Int32*							par2: ---

	APIEnv_GetMagicWandSetsID					= 'GMWA',			// par1: API_MagicWandInfo*				par2: ---
	APIEnv_GetExportToleranceID					= 'GEXT',			// par1: double*						par2: ---
	APIEnv_Get3DProjectionSetsID				= 'GP3D',			// par1: API_3DProjectionInfo*			par2: ---
	APIEnv_Change3DProjectionSetsID				= 'CP3D',			// par1: API_3DProjectionInfo*			par2: [bool*] (switch only axono or persp)
	APIEnv_GetRenderingSetsID					= 'GREN',			// par1: API_RendEffects...*			par2: API_RendSetTypeID					par3: const GS::UniString*
	APIEnv_ChangeRenderingSetsID				= 'CREN',			// par1: API_RendEffects...*			par2: API_RendSetTypeID
	APIEnv_GetRenderingSceneNamesID				= 'GRNA',			// par1: GS::Array<GS::UniString>*
	APIEnv_SetCurrentRenderingSceneID			= 'SREN',			// par1: const GS::UniString*

	APIEnv_Get3DImageSetsID						= 'GI3D',			// par1: API_3DFilterAndCutSettings*				par2: ---
	APIEnv_Change3DImageSetsID					= 'CI3D',			// par1: API_3DFilterAndCutSettings*				par2: [bool*] (must convert)

	APIEnv_Get3DWindowSetsID					= 'GW3D',			// par1: API_3DWindowInfo*				par2: ---
	APIEnv_Change3DWindowSetsID					= 'CW3D',			// par1: API_3DWindowInfo*				par2: ---

	APIEnv_Get3DStyleID							= 'GD3S',			// par1: API_3DStyle*					par2: ---
	APIEnv_Change3DStyleID						= 'CD3S',			// par1: API_3DStyle*					par2: ---
	APIEnv_Create3DStyleID						= 'CRD3',			// par1: API_3DStyle*					par2: ---
	APIEnv_Get3DStyleListID						= 'G3SL',			// par1: GS::Array<GS::UniString>*		par2: GS::UniString*
	APIEnv_SetCurrent3DStyleID					= 'SCD3',			// par1: GS::UniString*					par2: ---

	APIEnv_Get3DCuttingPlanesID					= 'GC3D',			// par1: API_3DCutPlanesInfo*			par2: ---
	APIEnv_Change3DCuttingPlanesID				= 'CC3D',			// par1: API_3DCutPlanesInfo*			par2: ---

	APIEnv_GetShowHideStateID					= 'GSHW',			// par1: bool*							par2: ---
	APIEnv_ChangeShowHideStateID				= 'CSHW',			// par1: bool*							par2: ---

	APIEnv_GetMiscAppInfoID						= 'GMAP',			// par1: API_MiscAppInfo*				par2: ---
	APIEnv_GetMiscPrinterInfoID					= 'GMPR',			// par1: API_MiscPrinterInfo*			par2: ---
	APIEnv_GetMiscPlotterInfoID					= 'GMPL',			// par1: API_MiscPlotterInfo*			par2: ---
	APIEnv_GetPrinterParsID						= 'GPRP',			// par1: API_PrintPars*					par2: ---

	APIEnv_GetSpecFolderID						= 'GSPF',			// par1: API_SpecFolderID* 				par2: IO::Location*

	APIEnv_CreateLayoutID						= 'CRLY',			// par1: API_LayoutInfo*)				par2: API_DatabaseUnId*					par3: API_Guid*
	APIEnv_GetLayoutSetsID						= 'GLAY',			// par1: API_LayoutInfo*				par2: [API_DatabaseUnId*]				par3: [ULong*] (actual page index)
	APIEnv_ChangeLayoutSetsID					= 'CLAY',			// par1: API_LayoutInfo*				par2: [API_DatabaseUnId*]

	APIEnv_GetCurrLayerCombID					= 'GCLC',			// par1: API_AttributeIndex*			par2: ---
	APIEnv_ChangeCurrLayerCombID				= 'CCLC',			// par1: API_AttributeIndex*			par2: ---

	APIEnv_GetCurrPenSetID						= 'GCPS',			// par1: API_AttributeIndex* (Pen set index)			par2: ---

	APIEnv_GetNumberingGridLinesID				= 'GNGL',			// par1: APINumberingGridLineProc*		par2: ---

	APIEnv_IsAutoIntersectOnID					= 'ISAI',			// par1: bool*							par2: ---
	APIEnv_ChangeAutoIntersectID				= 'CHAI',			// par1: bool*							par2: ---

	APIEnv_IsMarkerDrawingEnabledID				= 'IMDR',			// par1: bool*							par2: ---
	APIEnv_ChangeMarkerDrawingEnabledID			= 'CMDR',			// par1: bool (enabled)					par2: ---

	APIEnv_CreateCopyOfGdlUserGlobalsHandleID	= 'CGUG',			// par1: GDL::Parameters**				par2: ---
	APIEnv_DestroyCopyOfGdlUserGlobalsHandleID	= 'DGUG',			// par1: GDL::Parameters**				par2: ---

	APIEnv_GetDocumentFrom3DDefaultsID			= 'G3DD',			// par1: API_DocumentFrom3DDefaults*	par2: ---
	APIEnv_ChangeDocumentFrom3DDefaultsID		= 'C3DD',			// par1: API_DocumentFrom3DDefaults*	par2: ---
	APIEnv_GetDocumentFrom3DSettingsID			= 'G3DS',			// par1: API_DatabaseUnId*				par2: API_DocumentFrom3DType*
	APIEnv_ChangeDocumentFrom3DSettingsID		= 'C3DS',			// par1: API_DatabaseUnId*				par2: API_DocumentFrom3DType*

	APIEnv_GetStructureDisplayID				= 'GSTD',			// par1: API_UIStructureDisplay*		par2: ---
	APIEnv_ChangeStructureDisplayID				= 'CSTD',			// par1: API_UIStructureDisplay*		par2: ---

	APIEnv_IsInCurtainWallEditModeID			= 'ICWE',			// par1: bool* (is in edit mode)		par2: [API_Guid*] (edited curtain wall)
	APIEnv_GetTWAccessRightID					= 'GTAR',			// par1: API_TWAccessRights (perm)		par2: bool* (has right)
	APIEnv_IsInStairEditModeID					= 'ISTE',			// par1: bool* (is in edit mode)		par2: [API_Guid*] (edited stair)
	APIEnv_IsInBeamEditModeID					= 'IBEE',			// par1: bool* (is in edit mode)		par2: [API_Guid*] (edited beam)
	APIEnv_IsInColumnEditModeID					= 'ICOE'			// par1: bool* (is in edit mode)		par2: [API_Guid*] (edited column)
} API_EnvironmentID;



// =============================================================================
// Protection
//
// =============================================================================

// protected by hardware key
#define APIPROT_SITE_MASK			0x0001						// More license (full version)
#define APIPROT_NFR_MASK			0x0002						// Not For Resale version (full version)
#define APIPROT_SCHOOL_MASK			0x0004						// School version (full version)
#define APIPROT_PPU_MASK			0x0008						// PPU version (full version)
#define APIPROT_NET_MASK			0x0010						// Network licensing (full version)
#define APIPROT_TW_MASK				0x0020						// TeamWork functionality is on
#define APIPROT_PROTEDU_MASK		0x0040						// Student version
#define APIPROT_START_MASK			0x0080						// Start version
#define APIPROT_SOLO_MASK			0x0100						// SOLO edition (JPN, UK)
#define APIPROT_LIVE_MASK			0x0200						// Live Subscription license type

// no hardware key
#define APIPROT_EDU_MASK			0x00010000					// Student version
#define APIPROT_DEMO_MASK			0x00020000					// Demo version
#define APIPROT_TRIAL_MASK			0x00040000					// Trial version
#define APIPROT_BTC_MASK			0x00080000					// BIMcloud Team Client version


typedef enum {
	API_LicenseBorrowed,
	API_LicenseReturned
} API_LicenseBorrowStatusTypeID;


// =============================================================================
// Project information
//
// =============================================================================

struct API_ProjectInfo {
	bool							untitled;					// project file not saved yet
	bool							teamwork;					// signed into a team project
	short							userId;						// TeamWork member ID
	Int32							workGroupMode;				// Teamwork rights
	IO::Location*					location;					// project file
	IO::Location*					location_team;				// shared project
	UInt64							modiStamp;					// modification stamp of project
	GS::UniString*					projectPath;
	GS::UniString*					projectName;

	API_ProjectInfo () :
		untitled (false), teamwork (false), userId (0), workGroupMode (0),
		location (nullptr), location_team (nullptr), modiStamp (0),
		projectPath (nullptr), projectName (nullptr)
	{}

	~API_ProjectInfo ()
	{
		if (location != nullptr) { delete location; location = nullptr; }
		if (location_team != nullptr) { delete location_team; location_team = nullptr; }
		if (projectPath != nullptr) { delete projectPath; projectPath = nullptr; }
		if (projectName != nullptr) { delete projectName; projectName = nullptr; }
	}
};


// =============================================================================
// Teamwork - sharing and workspace information
//
// =============================================================================

typedef enum {
	APINoPermission	= 0,
	APILineTypesCreate,
	APILineTypesDeleteModify,
	APIFillTypesCreate,
	APIFillTypesDeleteModify,
	APICompositesCreate,
	APICompositesDeleteModify,
	APIPenSetsCreate,
	APIPenSetsDeleteModify,
	APIProfilesCreate,
	APIProfilesDeleteModify,
	APICitiesCreate,
	APICitiesDeleteModify,
	APIMarkupStylesCreate,
	APIMarkupStylesDeleteModify,
	APIZoneCategoriesCreate,
	APIZoneCategoriesDeleteModify,
	APILayersCreate,
	APILayersDeleteModify,
	APIMaterialsCreate,
	APIMaterialsDeleteModify,
	APIFavoritesCreate,
	APIFavoritesDeleteModify,
	APIPublicFindSelectCriteriaCreate,
	APIPublicFindSelectCriteriaDeleteModify,
	APIMasterLayoutsCreate,
	APIMasterLayoutsDeleteModify,
	APIModelViewOptionsCreate,
	APIModelViewOptionsDeleteModify,
	APIProjectLocation,
	APIProjectPreferences,
	APIProjectInfo,
	APIStoreyCreate,
	APIStoreyDeleteModify,
	APIViewsAndFoldersCreate,
	APIViewsAndFoldersDeleteModify,
	APILayoutsAndSubsetsCreate,
	APILayoutsAndSubsetsDeleteModify,
	APIProjectNotesManage,
	APIDesignToolElements,
	APIGridToolElements,
	APIDocumentToolElements,
	APIExternalDrawingsManage,
	APIIFCExternalPropertiesManage,
	APISchedulesAndIndexesCreate,
	APISchedulesAndIndexesDeleteModify,
	APISetUpListSchemesManage,
	APIPublisherSetsCreate,
	APIPublisherSetsDeleteModify,
	APIPublisherSetsPublish,
	APIViewpointManage,
	APIMarkupEntryCreate,
	APIMarkupEntryDeleteModify,
	APIXrefInstances,
	APIHotlinkInstances,
	APIHotlinkAndXrefManage,
	APILibraryAddRemove,
	APILibraryPartCreate,
	APILibraryPartDeleteModify,
	APIAddOnsSetupManage,
	APIMEPSystemCreate,
	APIMEPSystemDeleteModify,
	APIProjectPreviewManage,
	APIRenovationFilterCreate,
	APIRenovationFilterDeleteModify,
	APIRenovationOverrideStyleManage,
	APIBuildingMaterialsCreate,
	APIBuildingMaterialsDeleteModify,
	APIRenderingSceneCreate,
	APIRenderingSceneDeleteModify,
	APISaveAsPLNPLAMOD,
	APISaveAsDXFDWG,
	APISaveAsIFC,
	APIViewTimeSheet,
	APIUpgradeToLaterArchiCADBuild,
	APIChangeCreate,
	APIChangeDeleteModify,
	APIIssueManage,
	APIIssueModifyHistory,
	APIPropertyAndClassificationCreate,
	APIPropertyAndClassificationDeleteModify,
	APIGraphicOverridesCreate,
	APIGraphicOverridesDeleteModify,
	APIElementTransferSettingsCreate,
	APIElementTransferSettingsDeleteModify,
	API3DStyleCreate,
	API3DStyleDeleteModify,
	APIIFCPreferencesManage,
	APIIssueCreateModify,
	APIIssueDelete,
	APIIssueTagManage,
	APIStructuralAnalyticalToolElements,
	APIStructuralAnalyticalModelGenerationRulesManage,
	APISAFTranslatorsManage,
	APISaveAsSAF,
	APISaveAsRVT
} API_TWAccessRights;

typedef enum {
	APILockableStatus_NotExist,
	APILockableStatus_Free,								// Free for reservation, not locked
	APILockableStatus_Editable,							// Editable, locked by me
	APILockableStatus_Locked,							// Locked by someone else
	APILockableStatus_NotAvailable						// Server is offline or not available
} API_LockableStatus;

typedef struct {
	GS::uchar_t						loginName[API_UniLongNameLen];	// member login name (unique)
	GS::uchar_t						fullName[API_UniLongNameLen];	// member full name
	API_Guid						guid;							// member guid
	short							userId;							// member ID
	bool							connected;						// actually connected or not
	bool							filler_1;
	Int32							filler_2[7];
} API_UserInfo;

typedef struct {
	Int32							nUsers;						// registered members of the Team Project
	API_UserInfo**					users;
	Int32							filler_1[8];
} API_SharingInfo;


// =============================================================================
// Project Notes
//
// =============================================================================

typedef struct {
	char							client [256];
	char							projectName [256];
	char							company [256];
	char							street [256];
	char							city [256];
	char							country [256];
	char							code [256];
	char							architect [256];
	char							draftsmen [256];
	char							projectStatus [256];
	char							dateOfIssue [256];
	char							keywords [256];
	char							notes [1024];
} API_ProjectNoteInfo;


// =============================================================================
// Library Manager
//
// =============================================================================

typedef enum {
	API_Undefined,
	API_LocalLibrary,
	API_UrlLibrary,
	API_BuiltInLibrary,
	API_EmbeddedLibrary,
	API_OtherObject,
	API_UrlOtherObject,
	API_ServerLibrary
} API_LibraryTypeID;

typedef struct {
	IO::Location					location;
	GS::UniString					name;
	API_LibraryTypeID				libraryType;
	bool							available;
	bool							readOnly;
	bool							filler[2];
	GS::UniString					twServerUrl;				// URL address of the TeamWork server hosting the library (API_ServerLibrary only)
	GS::UniString					urlWebLibrary;				// URL of the downloaded Internet library (API_UrlLibrary and API_UrlOtherObject only)
} API_LibraryInfo;


// =============================================================================
// Toolbox
//
// =============================================================================

typedef struct {
	API_ElemType					type;						// element type
	Int32							filler_1[2];
} API_ToolBoxItem;


typedef struct {
	Int32							nTools;						// number of tools installed (internal, subtypes)
	API_ToolBoxItem**				data;
	API_ToolBoxItem					activeTool;
	Int32							filler_1[6];
} API_ToolBoxInfo;


// =============================================================================
// Display Options
//
// =============================================================================

#define API_LWeight_On						1					// Line Weight popup
#define API_LWeight_Hairline				2

#define API_Hole_ShowWithDim				1					// Door, Windows, Skylights
#define API_Hole_ShowOnPlan					2
#define API_Hole_HideOnPlan					3
#define API_Hole_ReflCeiling				4
#define API_Hole_HideHole					5

#define API_Drawing_Clean					1					// Wall & Beam Intersections popup
#define API_Drawing_Constr					2

#define API_Beam_Drawing_Full				1					// Beams popup
#define API_Beam_Drawing_RefLine			2
#define API_Beam_Drawing_Contour			3

#define API_Slab_ShowCommonEdges			0					// Slabs popup
#define API_Slab_EliminateCommonEdges		1
#define API_Slab_HiddenCommonEdges			2

#define API_Wall_Drawing_Contour			1					// Walls popup
#define API_Wall_Drawing_RefLine			2

#define API_TextSet_Normal					1					// Text popup
#define API_TextSet_Handles					2

#define API_Figure_WithHandles				1					// Figures popup
#define API_Figure_WithoutHandles			2

#define API_CamPath_None					1					// Path Option dialog - Display Options popup
#define API_CamPath_CamerasOnly				2
#define API_CamPath_CamerasAndPath			3
#define API_CamPath_Everything				4

#define API_Section_Marker_Normal			0					// Section Marker popup
#define API_Section_Marker_KeyPlan			1
#define API_Section_Marker_AsInSettings		2

#define API_Column_Symbol_Hide				0					// Show/Hide Column Symbols options
#define API_Column_Symbol_Show				1

#define API_RoofShellShow_AllDetails		0					// Controls the way roofs/shells are displayed
#define API_RoofShellShow_TopSurface		1
#define API_RoofShellShow_ContourDrawing	2

#define API_CurtainWallCompShow_None		0					// Detail levels of Curtain Wall components in model view options
#define API_CurtainWallCompShow_Linear		1					// only for CWFrame
#define API_CurtainWallCompShow_Schematic	2
#define API_CurtainWallCompShow_Simplified	3
#define API_CurtainWallCompShow_Full		4

#define API_Stair3DDetail_Full				1
#define API_Stair3DDetail_Schematic			2

#define API_StairFloorPlanVisual_FloorPlan	1
#define API_StairFloorPlanVisual_Reflected	2

#define API_Railing3DDetail_Full			1
#define API_Railing3DDetail_Simplified		2
#define API_Railing3DDetail_Schematic		3

#define API_Fill_Bitmap						1
#define API_Fill_Vector						2

#define API_Zone_NoFillZone					1
#define API_Zone_HideBackgroundZone			2
#define API_Zone_SolidForegroundZone		3
#define API_Zone_SolidBackgroundZone		4
#define API_Zone_HidePatternZone			5
#define API_Zone_CategoryBackgroundZone		6
#define API_Zone_SolidCategoryZone			7


typedef enum {
	API_EntireStructure,
	API_CoreOnly,
	API_WithoutFinishes,
	API_StructureOnly
} API_StructureDisplay;


typedef struct {
	API_StructureDisplay			structureDisplay;
	API_DatabaseUnId				databaseUnId;
	bool							is3D;
	bool							filler[7];
} API_UIStructureDisplay;


// =============================================================================
// Classifications
//
// =============================================================================

struct API_ClassificationItem {
	API_Guid						guid;
	GS::UniString					id;
	GS::UniString					name;
	GS::UniString					description;

	API_ClassificationItem () :
		guid (APINULLGuid)
	{ }
};

struct API_ClassificationSystem {
	API_Guid		guid;
	GS::UniString	name;
	GS::UniString	description;
	GS::UniString	source;
	GS::UniString	editionVersion;
	GSDateRecord	editionDate;

	API_ClassificationSystem () :
		guid (APINULLGuid)
	{ }
};

// =============================================================================
// Overrides
//
// =============================================================================

typedef struct {
	API_Guid						guid;
	GS::UniString					name;
} API_OverrideCombination;


typedef struct {
	bool							overrideCutFill;
	bool							overrideCoverFill;
	bool							overrideDraftingFill;
} API_OverriddenFillType;


typedef struct {
	bool							overrideCutSurface;
	bool							overrideUncutSurface;
} API_OverriddenSurfaceType;


struct API_OverrideRuleStyle {
	API_OverriddenAttribute			lineType;
	API_OverriddenAttribute			lineMarkerTextPen;

	API_OverriddenAttribute			fillOverride;
	API_OverriddenFillType			fillType;

	API_OverriddenAttribute			fillForegroundPenOverride;
	API_OverriddenFillType			fillTypeForegroundPen;

	API_OverriddenAttributeOrRGB	fillBackgroundPenOverride;
	API_OverriddenFillType			fillTypeBackgroundPen;

	API_OverriddenAttributeOrRGB	surfaceOverride;
	API_OverriddenSurfaceType		surfaceType;
	bool							showSkinSeparators;
	bool							overridePenColorAndThickness;

	API_OverriddenSurfaceType		hiddenContours;
	bool							overrideContours;
};


typedef struct {
	API_Guid						guid;
	GS::UniString					name;
	API_OverrideRuleStyle			style;
	GS::UniString					criterionXML;
} API_OverrideRule;


struct API_OverrideStyle {
	API_OverriddenAttribute			lineType;
	API_OverriddenAttribute			lineMarkerTextPen;
	bool							overrideLinePenThickness;

	API_OverriddenAttribute			cutFillType;
	API_OverriddenAttribute			cutFillFGPen;
	API_OverriddenAttributeOrRGB	cutFillBGPen;
	bool							overrideCutFillFGThickness;

	API_OverriddenAttribute			coverFillType;
	API_OverriddenAttribute			coverFillFGPen;
	API_OverriddenAttributeOrRGB	coverFillBGPen;
	bool							overrideCoverFillFGThickness;

	API_OverriddenAttribute			draftFillType;
	API_OverriddenAttribute			draftFillFGPen;
	API_OverriddenAttributeOrRGB	draftFillBGPen;
	bool							overrideDraftFillFGThickness;

	API_OverriddenAttributeOrRGB	cutSurfaceType;
	API_OverriddenAttributeOrRGB	uncutSurfaceType;
	bool							showSkinSeparators;

	bool							hideCutContours;
	bool							hideUncutContours;
};



typedef enum {
	APIImage_Model2D	= 0,
	APIImage_Model3D	= 1,
	APIImage_Section	= 2
} API_ImageViewID;

typedef struct {
	API_ImageViewID					view;
	API_OverrideStyle				overrideStyle;
	GSHandle						vectorImageHandle;
	NewDisplay::NativeImage*		nativeImagePtr;
} API_VisualOverriddenImage;

typedef struct {
	API_Guid						roomGuid;
	API_ImageViewID					viewType;
	double							offset;
	double							scale;
	API_RGBColor					backgroundColor;
	NewDisplay::NativeImage*		nativeImagePtr;
	Int32							filler[4];
} API_RoomImage;


typedef struct {
	GS::uchar_t						name[API_UniLongNameLen];
	API_Guid						guid;
	API_AddParType					**params;
	char							checkSum[64];
	API_Guid						supersetGuid;
	Int32							filler[4];
} API_GDLModelViewOptions;


typedef struct {
	char							cwFrameDetailLevel;				// API_CurtainWallCompShow...
	char							cwPanelDetailLevel;				// API_CurtainWallCompShow_None, ...Schematic, ...Simplified, ...Full
	char							cwJunctionDetailLevel;			// API_CurtainWallCompShow_None, ...Schematic, ...Simplified, ...Full
	char							cwAccessoryDetailLevel;			// API_CurtainWallCompShow_None, ...Schematic, ...Simplified, ...Full
} API_CurtainWallModelViewOptions;


typedef struct {
	char							stair3DDetailLevel;				// API_Stair3DDetail...
	char							stairFloorPlanVisualization;	// API_StairFloorPlanVisual...
	bool							showStairHeadroom;
	char							filler_1[5];
	bool							stairFloorPlanCompWalkingLine;
	bool							stairFloorPlanCompNumbering;
	bool							stairFloorPlanCompUPDOWNText;
	bool							stairFloorPlanCompDescription;
	bool							stairFloorPlanCompTreadAccessories;
	bool							stairFloorPlanCompStructureBeamSupport;
	bool							stairFloorPlanCompStructureStringers;
	bool							stairFloorPlanCompStructureCantilevered;
	bool							stairReflectedCompWalkingLine;
	bool							stairReflectedCompDescription;
	bool							stairReflectedCompStructureBeamSupport;
	bool							stairReflectedCompStructureStringers;
	bool							stairReflectedCompStructureCantilevered;
	bool							filler_2[3];
	API_AttributeIndex				stairSchemeSurfaceIndex;
	API_AttributeIndex				stairSchemeCutLineIndex;
	short							stairSchemeCutLinePenIndex;
	API_AttributeIndex				stairSchemeUncutLineIndex;
	short							stairSchemeUncutLinePenIndex;
	short							filler_3[3];
} API_StairModelViewOptions;


typedef struct {
	char							railing3DDetailLevel;
	char							filler_1[7];
	bool							railing2DDisplayCompPosts;
	bool							railing2DDisplayCompTopRail;
	bool							railing2DDisplayCompHandrails;
	bool							railing2DDisplayCompRails;
	bool							railing2DDisplayCompInnerPosts;
	bool							railing2DDisplayCompBalusters;
	bool							railing2DDisplayCompPanels;
	bool							filler_2;
	API_AttributeIndex				railingSchemeSurfaceIndex;
	API_AttributeIndex				railingSchemeCutLineIndex;
	short							railingSchemeCutLinePenIndex;
	API_AttributeIndex				railingSchemeUncutLineIndex;
	short							railingSchemeUncutLinePenIndex;
	short							filler_3[3];
} API_RailingModelViewOptions;


typedef struct {
	char							filler_0[2];				// Model View Options (filler_0 was: constFill, polyFill)
	char							doorMode;					// API_Hole_ShowWithDim...API_Hole_HideHole
	char							windowMode;					// API_Hole_ShowWithDim...API_Hole_HideHole
	char							skylightMode;				// API_Hole_ShowWithDim...API_Hole_HideHole
	char							filler_1;
	char							sectionMarker;
	char							beamMethod;					// API_Beam_Drawing_Full, API_Beam_Drawing_RefLine, API_Beam_Drawing_Contour
	char							roofShellMode;				// API_RoofShellShow_AllDetails, API_RoofShellShow_TopSurface, API_RoofShellShow_ContourDrawing
	char							showColumnSymbol;			// API_Column_Symbol_Show, API_Column_Symbol_Hide
	char							slabMethod;					// API_Slab_ShowCommonEdges, API_Slab_EliminateCommonEdges, API_Slab_HiddenCommonEdges
	char							filler_2;
	bool							coluHiddenlineUnderSlabs;
	bool							beamHiddenlineUnderSlabs;
	bool							zoneHideZoneStamp;
	API_CurtainWallModelViewOptions	curtainWallModelViewOptions;
	API_StairModelViewOptions		stairModelViewOptions;
	API_RailingModelViewOptions		railingModelViewOptions;

	API_GDLModelViewOptions*		gdlOptions;
} API_ModelViewOptions;


typedef struct {
	char							wallMode;					// On-Screen View Options
	bool							showRoofPivLine;
	bool							showFillHandles;
	char							lineWeight;
	char							textMode;
	char							figureMode;
	bool							showExtrudedBodies;			// 3D only (was: showSectDepth)
	char							camPathViewMode;
	char							wallMethod;
	bool							showMarkerRange;
	char							filldrawingMode;
	bool							splineMode;
	bool							showDrawingFrames;
	bool							showMasterItems;
	bool							boldCutLines;
	bool							showSourceMarkerBound;
	bool							showDimensionAllLines;
	bool							showOpeningCuttingBodies;
	bool							showOpeningReferences;
	char							filler_1[7];
} API_OnScreenViewOptions;


typedef struct {
	API_ModelViewOptions			modelViewOpt;
	API_OnScreenViewOptions			onScreenViewOpt;

	Int32							filler[4];
} API_ViewOptions;


// =============================================================================
// Story Settings
//
// =============================================================================

typedef struct {
	short							index;						// the story index
	short							floorId;					// unique ID of the story
	bool							notMine;					// belongs to other client
	bool							dispOnSections;
	short							filler_1;
	double							level;
	GS::uchar_t						uName [API_UniLongNameLen];
	Int32							filler_2[4];
} API_StoryType;

typedef struct {
	bool							on;							// show ghost story
	bool							showOne;					// show this story
	bool							showAbove;					// show on the story above the current
	bool							showBelow;					// show on the story below the current
	short							storyInd; 					// index of the ghost story displayed
	short							filler_1;
	API_RGBColor					ghostColor;
	API_ElemFilter					filter;
	Int32							filler_2;
} API_GhostStoryType;

typedef enum {
	APIGhost_NoFloor = 0,
	APIGhost_ShowOneFloor,
	APIGhost_ShowAboveFloor,
	APIGhost_ShowBelowFloor,
	APIGhost_ShowPreviousFloor,
	APIGhost_ShowAllStructure
}  API_ShowGhostType;

typedef struct {
	API_Coord						offset;
	double							rotation;
	double							scale;
	GSTime							time;
	Int32							filler_1;
	API_DatabaseUnId				parentDatabase;
	API_DatabaseUnId				ghostDatabase;
	API_DatabaseTypeID				ghostDBType;
	API_ShowGhostType				ghostType;
	API_ElemFilter					filter;
	bool							filler_2[5];
	short							floor;
	short							filler_3;
	bool							activated;
	bool							show;
	short							filler_4;
	API_RGBAColor					ghostColor;
	bool							ghostOriginalColor;
	bool							ghostOriginalTone;
	bool							ghostBackgroundFill;
	bool							filler_5[5];
	API_RGBAColor					viewColor;
	bool							viewOriginalColor;
	bool							viewOriginalTone;
	bool							viewBackgroundFill;
	bool							filler_6;
	bool							ghostOnTop;
	bool							filler_7[3];
} API_GhostRecord;

typedef struct {
	short							firstStory;					// first story index
	short							lastStory;					// last story index
	short							actStory;					// actual story index
	bool							filler_1;
	bool							skipNullFloor;				// skip the	zero floor
	API_StoryType**					data;
	Int32							filler_2;
	API_GhostStoryType				ghostStory;					// ghost story data
	Int32							filler_3[4];
} API_StoryInfo;


typedef enum {
	APIStory_GoTo,
	APIStory_Delete,
	APIStory_InsAbove,											// <- name
	APIStory_InsBelow,											// <- name
	APIStory_SetHeight,											// <- height
	APIStory_Rename,											// <- name
	APIStory_SetElevation,										// <- elevation
	APIStory_SetDispOnSections
} API_StoryCmdID;

typedef struct {
	API_StoryCmdID					action;						// action done in Story Settings dialog
	short							index;						// an existing story index
	bool							dispOnSections;
	bool							dontRebuild;				// don't call rebuild or redraw after Go To Story
	double							height;
	double							elevation;
	GS::uchar_t						uName [API_UniLongNameLen];
	Int32							filler_2[4];
} API_StoryCmdType;


// =============================================================================
// Preferences
//
// =============================================================================

enum class API_LengthTypeID {
	Meter,
	Decimeter,
	Centimeter,
	Millimeter,
	FootFracInch,
	FootDecInch,
	DecFoot,
	FracInch,
	DecInch,
	KiloMeter,
	Yard
};

enum class API_AreaTypeID {
	SquareMeter,
	SquareKiloMeter,
	SquareDeciMeter,
	SquareCentimeter,
	SquareMillimeter,
	SquareFoot,
	SquareInch,
	SquareYard
};

enum class API_VolumeTypeID {
	CubicMeter,
	CubicKiloMeter,
	Liter,
	CubicCentimeter,
	CubicMillimeter,
	CubicFoot,
	CubicInch,
	CubicYard,
	Gallon
};

enum class API_AngleTypeID {
	DecimalDegree,
	DegreeMinSec,
	Grad,
	Radian,
	Surveyors
};

typedef struct {
	API_LengthTypeID				lengthUnit;
	API_AreaTypeID					areaUnit;
	API_VolumeTypeID				volumeUnit;
	API_AngleTypeID					angleUnit;
	short							roundInch;					// 1, 2, 4, 8, 16, 32, 64
	short							lenDecimals;				// 0..4
	short							areaDecimals;				// 0..4
	short							volumeDecimals;				// 0..4
	short							angleDecimals;				// 0..4
	short							angleAccuracy;				// 0..4
	Int32							filler_1[12];
} API_WorkingUnitPrefs;


typedef enum {
	APIExtAc_Off					= 0,
	APIExtAc_Small5					= 1,						// show small 5 after decimals
	APIExtAc_Small25				= 2,						// show small 25/75 after decimals
	APIExtAc_Small1					= 3,						// show small 1 after decimals
	APIExtAc_Small01				= 4,						// show small 01 after decimals
	APIExtAc_Fractions				= 10						// FootInch & Inch case small Fractions
} API_ExtraAccuracyID;

typedef struct {
	API_LengthTypeID				unit;
	short							filler_0;
	short							roundInch;					// fractional inches
	short							lenDecimals;				// number of digits
	bool							show0Whole;					// show/hide Zero Wholes
	char							show0Inch;					// show zero inch
	API_ExtraAccuracyID				showSmall5;					// extra accuracy
	bool							hide0Dec;					// show/hide Zero Decimals
	char							filler_1;
	short							filler_2;
} API_LengthDimFormat;

typedef struct {
	API_AngleTypeID					unit;
	short							angleDecimals;				// number of digits
	short							angleAccuracy;
	bool							hide0Dec;					// show/hide Zero Decimals
	char							filler_0[3];
} API_AngleDimFormat;

typedef struct {
	API_AreaTypeID					unit;
	short							lenDecimals;				// number of digits
	bool							hide0Dec;					// show/hide Zero Decimals
	char							filler_0;
} API_AreaDimFormat;

typedef struct {
	API_LengthDimFormat				linear;
	API_AngleDimFormat				angle;
	API_LengthDimFormat				radial;
	API_LengthDimFormat				level;
	API_LengthDimFormat				elevation;
	API_LengthDimFormat				doorwindow;
	API_LengthDimFormat				parapet;
	API_AreaDimFormat				area;
	short							index;						// attribute index (used only in non custom case)
	short							filler_0;
	Int32							filler_1[3];
} API_DimensionPrefs;


typedef struct {
	API_LengthTypeID				unit;
	API_ExtraAccuracyID				accuracy;					// extra accuracy
	short							decimals;					// number of digits [0..4]
	short							roundInch;					// 1, 2, 4, 8, 16, 32, 64
} API_CalcLengthFormat;

typedef struct {
	API_AreaTypeID					unit;
	API_ExtraAccuracyID				accuracy;					// extra accuracy
	short							decimals;					// number of digits [0..4]
	short							filler_1;
} API_CalcAreaFormat;

typedef struct {
	API_VolumeTypeID				unit;
	API_ExtraAccuracyID				accuracy;					// extra accuracy
	short							decimals;					// number of digits [0..4]
	short							filler_1;
} API_CalcVolumeFormat;

typedef struct {
	API_AngleTypeID					unit;
	short							decimals;					// number of digits [0..4]
	short							accuracy;					// accuracy
	Int32							filler_0;
	Int32							filler_1;
} API_CalcAngleFormat;

typedef struct {
	API_CalcLengthFormat			length;
	API_CalcAreaFormat				area;
	API_CalcVolumeFormat			volume;
	API_CalcAngleFormat				angle;
	bool							useDisplayedValues;
	bool							filler_0[15];
} API_CalcUnitPrefs;

typedef enum {
	APIConditionalElementPropertyType_Volume,
	APIConditionalElementPropertyType_Surface,
	APIConditionalElementPropertyType_Length
} API_ConditionalElementPropertyTypeID;

typedef struct {
	API_ConditionalElementPropertyTypeID		propertyType;
	double										holeLimit;
	GS::HashSet<API_ElemType>					elementTypes;
} API_ConditionalElementRule;

typedef struct {
	GS::Array<API_ConditionalElementRule>	elementRules;

	GS::HashSet<API_AttributeIndex>			wallInsulationFills;
	GS::HashSet<API_AttributeIndex>			wallAirFills;
	GS::HashSet<API_AttributeIndex>			roofInsulationFills;
	GS::HashSet<API_AttributeIndex>			shellInsulationFills;
} API_CalcRulesPrefs;

typedef enum {
	APIRoofDisplay_AllVisibleContours		= 1,
	APIRoofDisplay_OnlyTheTopSurfaceOldWay	= 2
} API_RoofContourDisplay;

typedef struct {
	Int32							filler_1;
	Int32							coluConnPriority;
	short							filler_2;
	API_AttributeIndex				aboveLineType;
	API_AttributeIndex				belowLineType;
	short							filler_3;
	API_RoofContourDisplay			roofContourDisplay;
	bool							filler_4;
	bool							useLegacyIntersections;
	bool							hideZonesOnSections;
	char							filler_5;
	Int32							filler_6[12];
} API_LegacyPrefs;


#define APIRecess_And				1							// add wall recesses: deeper nichDepth and larger nichSize
#define APIRecess_Or				2							// add wall recesses: deeper nichDepth or larger nichSize

typedef struct {
	double							nichDepth;
	double							nichSize;
	unsigned char					nichCombineMode;
	bool							nichWindFlag;
	bool							nichDoorFlag;
	bool							nichDepthFlag;
	bool							nichSizeFlag;
	bool							filler_1;
	short							filler_2;

	bool							subtrWallFlag;
	bool							subtrColuFlag;
	unsigned char					subtrWallPercent;
	unsigned char					subtrColuPercent;
	Int32							filler_3;
	double							subtrWallSize;
	double							subtrColuSize;

	unsigned char					nLowAreas;
	bool							filler_4;
	short							filler_5;
	unsigned char					roomRedPercents[4];
	double							roomHeightLimits[4];

	Int32							filler_6[16];
} API_ZonePrefs;

typedef struct {
	IO::Location*					tempFolder;
	Int32							filler_1[15];
} API_SafetyPrefs;

typedef struct {
    GS::UniString					*level1UStr;
    GS::UniString                   *level2UStr;
    double							level1val;
    double							level2val;
} API_RefLevelsPrefs;


#define APIReportLevel_No			0							// no Report
#define APIReportLevel_Brief		1							// brief Report
#define APIReportLevel_Short		2							// short Report
#define APIReportLevel_Detailed		3							// detailed Report
#define APIReportLevel_Full			4							// full Report

#define APICalcSelElems_ShowAlert	1							// display warning dialog to choose listing method
#define APICalcSelElems_ListAll		2							// calculate all selected elements in the list
#define APICalcSelElems_UseFilters	3							// apply filters defined for the selected elements

typedef struct {
	bool							autoRebuild3D;				// auto-rebuild 3D Window when activated
	bool							activate3DOnChange;			// 3D Settings changes bring 3D Window to front
	bool							filler_1;
	bool							keepZoomedSection;			// keep zoomed detail on Rebuild from Model in Section Window
	bool							showProgressWindow;			// show Progress Window
	bool							interruptOnError;			// interrupt with error messages
	bool							progressSounds;				// 3D progress sounds
	bool							generate3DReport;			// write Report
	short							reportLevel;				// levels of detail for the 3D report [APIReportLevel_...]
	short							selElemsListing;			// selected elements to be calculated [APICalcSelElems_...]
	Int32							filler_2 [5];
} API_ImagingAndCalcPrefs;

typedef struct {
	double							currCutLevel;				// current cut level relative to the given story
	double							topCutLevel;				// top level relative to the top story (see topCutBaseStoryRelInd)
	double							bottomCutLevel;				// bottom level relative to the bottom story (see bottomCutBaseStoryRelInd)
	short							topCutBaseStoryRelInd;		// top story index relative to the given story index
	short							bottomCutBaseStoryRelInd;	// bottom story index relative to the given story index
	Int32							filler;
	double							fixLevel2Absolute0;
} API_FloorPlanCutDefinition;

typedef struct {
	API_RGBColor					masterColor;					// color of master items
	bool							useOwnMasterColor;				// use master items' own color
	bool							adjustDrawingFrameToViewZoom;	// display master layout above/below the layout
	char							filler[6];
} API_LayoutsPrefs;

typedef enum {
	APIPrefs_WorkingUnitsID,
	APIPrefs_ReferenceLevelsID,
	APIPrefs_DimensionsID,
	APIPrefs_CalcUnitsID,
	APIPrefs_CalcRulesID,
	APIPrefs_LegacyID,
	APIPrefs_ZonesID,
	APIPrefs_DataSafetyID,
	APIPrefs_ImagingAndCalcID,
	APIPrefs_FloorPlanCutPlaneDef,
	APIPrefs_LayoutsID
} API_PrefsTypeID;

typedef enum {
	APIUnitConv_WorkModel,										// Project Preferences / Working Units / Model Unit
	APIUnitConv_WorkLayout,										// Project Preferences / Working Units / Layout Unit
	APIUnitConv_WorkAngle,										// Project Preferences / Working Units / Angle Unit
	APIUnitConv_DimLinear,										// Project Preferences / Dimensions / Linear Dimensions
	APIUnitConv_DimAngle,										// Project Preferences / Dimensions / Angular Dimensions
	APIUnitConv_DimRadial,										// Project Preferences / Dimensions / Radial Dimensions
	APIUnitConv_DimLevel,										// Project Preferences / Dimensions / Level Dimensions
	APIUnitConv_DimElevation,									// Project Preferences / Dimensions / Elevation Dimensions
	APIUnitConv_DimDoorWindow,									// Project Preferences / Dimensions / Door, Window and Skylight Dimensions
	APIUnitConv_DimParapet,										// Project Preferences / Dimensions / Sill Height Dimensions
	APIUnitConv_DimArea,										// Project Preferences / Dimensions / Area Calculations
	APIUnitConv_CalcLength,										// Project Preferences / Calculation Units & Rules / Length Unit
	APIUnitConv_CalcArea,										// Project Preferences / Calculation Units & Rules / Area Unit
	APIUnitConv_CalcVolume,										// Project Preferences / Calculation Units & Rules / Volume Unit
	APIUnitConv_CalcAngle										// Project Preferences / Calculation Units & Rules / Angle Unit
} API_UnitConversionPrefID;

typedef struct {
	double							value;						// value to convert (m/m2/m3/radian)
	API_UnitConversionPrefID		unitConvPref;				// conversion and rounding setting to apply
	GS::uchar_t						convertedValue[64];			// converted value (in the target unit, without extra accuracy decimals); may contain the unit(s)
	GS::uchar_t						extraAccuracy[4];			// extra accuracy, if any (at most two decimals)
	GS::uchar_t						unit[64];					// the target unit; may be empty string
} API_UnitConversionData;


// =============================================================================
// Sun Settings
//
// =============================================================================

typedef struct {
	API_RGBColor					sunRGB;
	API_RGBColor					ambientRGB;
	short							sunIntensity;
	short							ambientIntensity;
	short							sunToAmbient;
	short							filler_1;
} API_SunInfo;


// =============================================================================
// Location and Date
//
// =============================================================================

typedef enum {
	APINorthUnit_DecimalDegree,
	APINorthUnit_DegreeMinSec
} API_NorthUnitID;

typedef enum {
	APIAltitudeUnit_Meter,
	APIAltitudeUnit_DecFoot
} API_AltitudeUnitID;

enum class API_LongLatUnitID {
	APILongLatUnit_DecimalDegree,
	APILongLatUnit_DegreeMinSec
};

typedef struct {
	short							filler_0; // cityInd; has been made redundant
	bool							sumTime;					// true if +1h (summer time)
	bool							filler_1;
	unsigned short					year;						// year
	unsigned short					month;						// month, 1..12
	unsigned short					day;						// day, 1..31
	unsigned short					hour;						// hour, 0..23
	unsigned short					minute;						// minute, 0..59
	unsigned short					second;						// second, 0..59
	double							longitude;					// Longitude in degrees
	double							latitude;					// Latitude in degrees
	double							altitude;					// Altitude in metres
	double							north;						// North direction in radians
	double							sunAngXY;					// Sun position component in radians
	double							sunAngZ;					// Sun position component in radians
	API_NorthUnitID					northUnit;					// angle unit of North direction
	API_AltitudeUnitID				altitudeUnit;				// Altitude displayed in meters or feet
	API_LongLatUnitID				longLatUnit;				// Longitude, Latitude display mode
	short							timeZoneInMinutes;			// Time zone in minutes from Greenwich
	short							timeZoneOffset;				// used when different timezones have the same timeZoneInMinutes
	Int32							filler_3[2];
} API_PlaceInfo;

typedef struct {
	GS::UniString					name;						// Name by which the coordinate reference system is identified
	GS::UniString					description;				// Informal description of this coordinate reference system
	GS::UniString					geodeticDatum;				// Name by which this datum is identified
	GS::UniString					verticalDatum;				// Name by which the vertical datum is identified
	GS::UniString					mapProjection;				// Name by which the map projection is identified
	GS::UniString					mapZone;					// Name by which the map zone, relating to the MapProjection, is identified
	double							eastings;					// Location along the easting of the coordinate system of the target map coordinate reference system
	double							northings;					// Location along the northing of the coordinate system of the target map coordinate reference system
	double							orthogonalHeight;			// Orthogonal height relative to the vertical datum specified
	double							xAxisAbscissa;				// Value along the easting axis of the end point of a vector indicating the position of the local x axis of the engineering coordinate reference system
	double							xAxisOrdinate;				// Value along the northing axis of the end point of a vector indicating the position of the local x axis of the engineering coordinate reference system
	double							scale;						// Scale to be used, when the units of the CRS are not identical to the units of the engineering coordinate system
} API_GeoReferenceData;

typedef struct {
	API_PlaceInfo					placeInfo;					// Project Location settings
	API_Coord3D						surveyPointPosition;		// Position of the Survey Point in the project
	API_GeoReferenceData			geoReferenceData;			// Coordinate Reference System and Map Conversion data (as defined in IFC)
} API_GeoLocation;


// =============================================================================
// Magic wand settings
//
// =============================================================================

#define API_ArcDiv_DivArc			1							// segments Along Arcs
#define API_ArcDiv_DivCircle		2							// segments Along Circles
#define API_ArcDiv_DiffArc			3							// deviation from Curves
#define API_ArcDiv_PartLength		4							// segment Length

#define API_ArcTrace_Linear			1
#define API_ArcTrace_BestMatch		2

typedef struct {
	short							divArcMode;
	short							traceMethod;
	short							filler_1;

	short							arcSegNumb;
	double							arcDiff;
	double							partLength;
	Int32							filler_2[8];
} API_MagicWandInfo;


// =============================================================================
// 3D Projection settings
//
// =============================================================================

typedef struct {
	bool							isPersp;
	char							filler_1[7];
	API_Guid						camGuid;
	API_Guid						actCamSet;
	union {
		API_PerspPars				persp;						// perspective settings
		API_AxonoPars				axono;						// axonometric (Parallel projection) settings
	} u;
} API_3DProjectionInfo;


// =============================================================================
// Rendering Settings
//
// =============================================================================

typedef struct {
	API_ModulID						rendererID;
	bool							useBkgAlpha;
	bool							filler_1[7];
} API_RendEffects;


typedef struct {
	short							hSize;
	short							vSize;
	short							outResolution;
	bool							proportional;

	bool							bkgPict;
	API_RGBColor					bkgSkyRGB;
	API_RGBColor					bkgEarthRGB;
	API_Rect						bkgPictRect;
	IO::Location*					bkgPictFile;
	short							bkgResolution;
	bool							filler_1;

	bool							partialRendering;
	API_Rect						partialRect;

	short							scaleType;
	short							bkgScaleType;

	Int32							filler_2[13];
} API_RendImage;


typedef enum {
	APIRendSet_EffectsID,
	APIRendSet_ImageID
} API_RendSetTypeID;


// =============================================================================
// 3D Image Info
//
// =============================================================================

typedef enum {
	API_FilterByRules,				// Show All (by the given rules)
	API_FilterBySelection,			// Show Selection
	API_FilterByMarqueeAndRules		// Show Marquee (by the given rules)
} API_3DFilterModeID;



enum class API_MarqueeType {
	SingleStory,
	MultiStory
};


enum class API_MarqueeConversionFilter {
	ConvertElemsInMarquee,
	ConvertElemsOutsideMarquee
};


typedef struct {
	API_MarqueeConversionFilter		elemsInMarquee;				// true: convert what's IN markRect
	bool							trimToMarquee;				// trim to marquee
	short							marqueeStory;				// the story for the single-story markRect
	API_MarqueeType					marqueeType;				// whether it is a single story or an all story markRect
} API_MarqueeFilter;


typedef struct {
	short							firstStory3D;				// first floor to convert
	short							lastStory3D;				// last floor to convert
	bool							allStories;					// if false, in 3Dconv firstStory3D..lastStory3D is valid
	API_MarqueeFilter				marqueeFilter;
	bool							trimToStoryRange;
	API_3DFilterModeID				filterMode;
	std::map<API_ElemTypeID, bool>	elemTypeFilter;
} API_3DFilterAndCutSettings;


// =============================================================================
// 3D Window Settings
//
// =============================================================================

typedef enum {
	API3DModel_Block = 0,
	API3DModel_WireFrame,
	API3DModel_Hiddenline,
	API3DModel_Shading
} API_3DModelTypeID;

typedef enum {
	APIShadContours_Draft = 0,
	APIShadContours_Off,
	APIShadContours_Best
} API_ShadingContoursID;										// API3DModel_Shading only

typedef enum {
	APIVectShad_Off = 0,										// no vectorial sun shadows
	APIVectShad_ContOff_AllSurf,								// contours OFF * On all surfaces
	APIVectShad_ContOn_AllSurf,									// contours ON  * On all surfaces
	APIVectShad_ContOff_OneLevel,								// contours OFF * On a single level
	APIVectShad_ContOn_OneLevel									// contours ON  * On a single level
} API_VectorShadowID;

typedef struct {
	bool							setWindowSize;
	short							hSize;	// Logical units
	short							vSize;	// Logical units

	bool							setZoom;
	double							zoomScaleX;
	double							zoomScaleY;
	double							zoomDispX;
	double							zoomDispY;
} API_3DWindowInfo;

struct API_3DStyle {
	GS::uchar_t						name[API_UniLongNameLen];

	/*GENERAL*/
	Int32							engineId;
	API_3DModelTypeID				model3D;
	Int32							filler_1[2];
	bool							transparency;				// transparency in Shading
	bool							monochromeEnabled;
	API_RGBColor					monochromeSurfaceRGB;
	API_RGBColor					monochromeContourRGB;

	/*BACKGROUND*/
	bool							bkgAsInRendering;
	bool							chainBkgColors;
	API_RGBColor					bkgSkyColor;
	API_RGBColor					backGroundRGB;

	/*CONTOURS*/
	API_ShadingContoursID			shadCont;
	Int32							filler_2[4];
	API_VectorShadowID				vectSunShadow;				// vectorial Sun Shadows
	bool							vectHatchOn;				// vectorial 3D Hatching
	bool							filler_3;
	short							contourThickness;
	short							silhouetteThickness;
	short							vectorialHatchingThickness;
	short							shadowContourThickness;

	/*SHADOWS*/
	short							castShadowPercent;
	short							shadingPercent;
	double							shadowElevation;

	/*HOTSPOTS*/
	bool							show3DHotSpotsOnly;

	API_3DStyle () :
		name (),
		engineId (0),
		model3D (API3DModel_Block),
		filler_1 (),
		transparency (false),
		monochromeEnabled (false),

		bkgAsInRendering (false),
		chainBkgColors (false),
		bkgSkyColor (),
		backGroundRGB (),

		shadCont (APIShadContours_Draft),
		filler_2 (),
		vectSunShadow (APIVectShad_Off),
		vectHatchOn (false),
		filler_3 (false),
		contourThickness (0),
		silhouetteThickness (0),
		vectorialHatchingThickness (0),
		shadowContourThickness (0),

		castShadowPercent (0),
		shadingPercent (0),
		shadowElevation (0.0),

		show3DHotSpotsOnly (false)

	{
		monochromeSurfaceRGB = { 0.0, 0.0, 0.0 };
		monochromeContourRGB = { 0.0, 0.0, 0.0 };
		bkgSkyColor = { 0.0, 0.0, 0.0 };
		backGroundRGB = { 0.0, 0.0, 0.0 };
	}
};


// =============================================================================
// 3D Cutting Planes
//
// =============================================================================

typedef struct {
	short							cutStatus;
	short							cutPen;
	API_AttributeIndex				cutMater;
	short							filler_1;
	double							pa;
	double							pb;
	double							pc;
	double							pd;
	double							filler_2[5];
} API_3DCutShapeType;


typedef struct {
	bool							isCutPlanes;
	bool							useCustom;
	short							customPen;
	API_AttributeIndex				customMater;
	short							nShapes;
	API_3DCutShapeType**			shapes;
	Int32							filler_2[9];
} API_3DCutPlanesInfo;


// =============================================================================
// Application/Printer/Plotter Info
//
// =============================================================================

typedef struct {
	char							version [256];				// version string of application
	char							caption [256];				// caption of application's main window
} API_MiscAppInfo;


typedef struct {
	char							name [256];					// name of selected printer
	bool							orientPortrait;				// currently selected orientation: portrait (true) or landscape (false)
	char							filler [7];
} API_MiscPrinterInfo;


#define API_DrvNameLen				32							// maximum length of a driver name

typedef struct {
	char							name  [API_DrvNameLen];		// name of selected plotter in AC
	char							model [API_DrvNameLen];		// model of selected plotter in AC
} API_MiscPlotterInfo;


// =============================================================================
// Special Folders
//
// =============================================================================

typedef enum {
	API_ApplicationPrefsFolderID	= 1,
	API_GraphisoftPrefsFolderID,
	API_GraphisoftHomeFolderID,
	API_CacheFolderID,
	API_DataFolderID,
	API_UserDocumentsFolderID,
	API_TemporaryFolderID,
	API_ApplicationFolderID,									// read-only
	API_DefaultsFolderID,										// read-only
	API_WebObjectsFolderID,
	API_TemplatesFolderID,
	API_HelpFolderID,
	API_EmbeddedProjectLibraryFolderID,
	API_EmbeddedProjectLibraryHotlinkFolderID
} API_SpecFolderID;


// =============================================================================
// Layout Info
//
// =============================================================================

typedef struct {
	GS::uchar_t								layoutName[API_UniLongNameLen];
	double									sizeX;
	double									sizeY;
	double									leftMargin;
	double									topMargin;
	double									rightMargin;
	double									bottomMargin;
	char									customLayoutNumber[256];
	bool									customLayoutNumbering;
	bool									doNotIncludeInNumbering;
	bool									showMasterBelow;
	bool									filler_1[5];
	UInt32									layoutPageNumber;
	UInt32									actPageIndex;
	double									filler_2[2];
	GS::HashTable<API_Guid, GS::UniString>* customData;
	GS::uchar_t								currentRevisionId[API_UniLongNameLen];
	GS::uchar_t								currentFinalRevisionId[API_UniLongNameLen];
	bool									hasIssuedRevision;
	bool									hasActualRevision;
	bool									filler_3[6];
} API_LayoutInfo;


// =============================================================================
// Numbering Grid Lines
// =============================================================================

typedef struct {
	API_Coord						begC;
	API_Coord						endC;
	short							penInd;
	API_AttributeIndex				ltypeInd;
	Int32							filler_1[7];
} API_NumberingGridLine;

// =============================================================================
// API_DocumentFrom3DDefaults
//
// =============================================================================


typedef enum {
	API_3DDocumentVectorFilles		= 1,
	API_3DDocumentUniformMaterial	= 2,
	API_3DDocumentOwnMaterial		= 3,
	API_3DDocumentOwnShadedMaterial	= 4
} API_3DCutSurfFills;


typedef enum {
	API_3DDocumentPenColor				 = 1,
	API_3DDocumentMaterialColorShaded	 = 2,
	API_3DDocumentMaterialColorNonShaded = 3
} API_3DUncutSurfaceFillType;


typedef enum {
	API_3DDocumentHideHiddenEdges,
	API_3DDocumentShowHiddenEdges
} API_3DHiddenEdgeVisibility;


typedef enum {
	API_3DDocumentDontShowOnCutPlanes,
	API_3DDocumentShowOnCutPlanes
} API_3DOnCutPlaneVisibility;


typedef struct {
	bool							shouldUseUniformCutAttributes;
	bool							filler_1;
	short							uniformLineType;
	short							uniformFillPen;
	short							uniformFillBkgPen;
	bool							shouldUseUncutSurfaceFill;
	bool							filler_2[3];
	API_3DCutSurfFills				fillCutSurfacesWith;
	API_3DUncutSurfaceFillType		uncutSurfaceFillType;
	short							uncutSurfaceBkgPen;
	bool							shouldUseElemPen;
	bool							filler_3;
	short							elemPen;
	short							shadFillPen;
	API_AttributeIndex				shadFill;
	short							shadFillBkgPen;
	short							shadContPen;
	API_3DHiddenEdgeVisibility		hiddenEdgeVisibility;
	API_AttributeIndex				hiddenEdgeLineType;
	short							hiddenEdgeLinePen;
	short							filler_4;
	API_3DOnCutPlaneVisibility		onCutPlaneVisibility;
	short							filler_5[2];
} API_UniformAttributeOptions;

typedef enum {
	API_DDD			= 1,
	API_FloorPlan	= 2
} API_DocumentSourceID;

typedef enum {
	API_Top			= 1,
	API_Bottom		= 2
} API_ViewSourceID;

typedef struct {
	API_ViewSourceID		viewSrc;
	short					floorIdx;
	double					cutHeight;
	short					floorOffset;
	double					cutOffset;
	short					filler;
} API_SkeletonOptions;

typedef struct {
	API_UniformAttributeOptions		attributeOptions;
	GS::uchar_t						name[API_UniLongNameLen];			// name of the database
	GS::uchar_t						refId[API_UniLongNameLen];			// reference string/id of the database
	bool							vect3DHatching;
	bool							vectSunShadow;
	bool							mustBeTransparent;
	bool							filler_1;
	API_CutPlanePlanConn			intPlanConn;
	bool							materialFrom3D;
	bool							contureOff;
	API_AttributeIndex				cMater;
	API_SkeletonOptions				skeletonOptions;
	API_BoundaryDisplay				boundaryDisplay;
	short							boundaryPen;
	API_AttributeIndex				boundaryLineType;
	short							filler_2[3];
} API_DocumentFrom3DDefaults;

typedef struct {
	API_3DFilterAndCutSettings		filterAndCutSettings;
	API_3DCutPlanesInfo				cutSetting;
	bool							cutaway3D;
	bool							filler_1[7];
	API_3DProjectionInfo			projectionSetting;
	API_Coord						floorPlanRotationOrigo;
	API_3DWindowInfo				window3DInfo;
	API_AttributeIndex				hiddenLineType;
	short							hiddenLineLen;
	short							effects3D;
	short							filler_2;
	API_Rect						drawRect;
	API_UniformAttributeOptions		attributeOptions;
	API_CutPlanePlanConn			currPlanConn;
	API_CutPlanePlanConn			intPlanConn;
	short							filler_3;
	bool							materialFrom3D;
	API_DocumentSourceID			docSrc;
	API_SkeletonOptions				skeletonOptions;
	API_BoundaryDisplay				boundaryDisplay;
	short							boundaryPen;
	API_AttributeIndex				boundaryLineType;
	bool							filler_4[4];
	bool							transparency;
} API_DocumentFrom3DType;

// ---------------------------------------------------------------------------------------------------------------------

#endif
