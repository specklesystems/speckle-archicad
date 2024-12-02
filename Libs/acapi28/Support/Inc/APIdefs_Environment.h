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
	APIEnv_IsInColumnEditModeID					= 'ICOE',			// par1: bool* (is in edit mode)		par2: [API_Guid*] (edited column)

	APIEnv_GetMainWindowHWNDID					= 'hWND',

	APIEnv_SetPreferencesID						= 'SPRF',
	APIEnv_ChangeSuspendGroupID					= 'CSPG',
	APIEnv_GetLibPartOrigLocationID				= 'GLOL'
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
#define APIPROT_OEM_MASK			0x0400						// OEM product versions

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

/**
 * @brief Contains information about the current project.
 * @struct API_ProjectInfo
 * @ingroup ProjectOperation
 * @sa ACAPI_Environment_GetProject
 * @remarks This structure is used to get information about the current project.
 */
struct API_ProjectInfo {

/**
 * @brief Indicates that the project file has not been saved yet.
 * @var untitled
 */
	bool							untitled;

/**
 * @brief Signed into a team project or not.
 * @var teamwork
 */
	bool							teamwork;

/**
 * @brief team project member ID; if signed into a team project.
 * @var userId
 */
	short							userId;

/**
 * @brief team project member rights; if signed into a team project
 * @var workGroupMode
 */
	Int32							workGroupMode;

/**
 * @brief Location of the non-teamwork project file
 * @var location
 */
	IO::Location*					location;

/**
 * @brief the shared project file; if signed into a team project.
 * @var location_team
 */
	IO::Location*					location_team;

/**
 * @brief Modification stamp of project.
 * @var modiStamp
 */
	UInt64							modiStamp;

/**
 * @brief optional; location of the project as string.
 * @var projectPath
 */
	GS::UniString*					projectPath;

/**
 * @brief optional; name of the project as Unicode string.
 * @var projectName
 */
	GS::UniString*					projectName;

	API_ProjectInfo () :
		untitled (false), teamwork (false), userId (0), workGroupMode (0),
		location (nullptr), location_team (nullptr), modiStamp (0),
		projectPath (nullptr), projectName (nullptr)
	{}

/**
 * @brief Destroys the project info (also cleans up)
 * @var location_team
 */
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
	APISaveAsRVT,
	APIStructuralAnalyticalLoadCombinationCreate,
	APIStructuralAnalyticalLoadCombinationDeleteModify,
	APIDesignOptionsCreate,
	APIDesignOptionsDeleteModify,
	APIMEPToolElements,
	APIMEPPreferences,
	APIKeynotesCreate,
	APIKeynotesDeleteModify
} API_TWAccessRights;

/**
 * @brief Possible Teamwork lockable status.
 * @enum API_LockableStatus
 * @ingroup LibraryPart
 * @remarks This enum is the return type of the @ref ACAPI_Teamwork_GetLockableStatus function.
 */
typedef enum {
	APILockableStatus_NotExist,
	APILockableStatus_Free,								// Free for reservation, not locked
	APILockableStatus_Editable,							// Editable, locked by me
	APILockableStatus_Locked,							// Locked by someone else
	APILockableStatus_NotAvailable						// Server is offline or not available

} API_LockableStatus;

/**
 * @brief Information on a registered Team Member
 * @struct API_UserInfo
 * @ingroup ProjectOperation
 * @remarks Refer to the @ref ACAPI_Teamwork_ProjectSharing function for more details.
 */
struct API_UserInfo {
/**
 * @brief Unique member login name as Unicode string
 * @var loginName
 */
	GS::uchar_t						loginName[API_UniLongNameLen];

/**
 * @brief member full name as Unicode string
 * @var fullName
 */
	GS::uchar_t						fullName[API_UniLongNameLen];

/**
 * @brief member identifier
 * @var guid
 */
	API_Guid						guid;

/**
 * @brief member ID
 * @var userId
 */
	short							userId;

/**
 * @brief actually connected to the teamwork project or not
 * @var connected
 */
	bool							connected;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[7];

};

/**
 * @brief Project sharing parameters.
 * @struct API_SharingInfo
 * @ingroup ProjectOperation
 * @sa ACAPI_Teamwork_ProjectSharing
 * @remarks This data gives the information on which users the active team project is opened for.
 * 			Refer to the @ref API_UserInfo structure for detailed information (what data can be obtained about one team member).
 */
struct API_SharingInfo {

/**
 * @brief Number of registered members of the active project.
 * @var nUsers
 */
	Int32							nUsers;

/**
 * @brief Data of each registered member.
 * @var users
 */
	API_UserInfo**					users;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1[8];

};


// =============================================================================
// Project Notes
//
// =============================================================================

/**
 * @brief Project note information parameters.
 * @struct API_ProjectNoteInfo
 * @ingroup ProjectSetting
 * @remarks The data structure members correspond to the items of the "Project Info..." dialog of Archicad.
 * 			This information can be used for autotext entries in text elements. See @ref ACAPI_AutoText_GetAutoTexts for details. Call
 * 			the @ref ACAPI_ProjectSetting_GetProjectNotes or the @ref ACAPI_ProjectSetting_ChangeProjectNotes functions to
 * 			operate on this data. The same behavior can be achieved with the autotext functions: @ref ACAPI_AutoText_GetAutoTexts,
 * @ref ACAPI_AutoText_SetAnAutoText. The main difference is that the autotext functions work on Unicode strings,
 * 		whereas the project notes functions use UTF-8 encoded strings.
 */
struct API_ProjectNoteInfo {
/**
 * @brief The name of the client.
 * @var client
 */
	char							client [256];

/**
 * @brief The name of the project.
 * @var projectName
 */
	char							projectName [256];

/**
 * @brief The company working on the project.
 * @var company
 */
	char							company [256];

/**
 * @brief Street address.
 * @var street
 */
	char							street [256];

/**
 * @brief City name..
 * @var city
 */
	char							city [256];

/**
 * @brief State or country.
 * @var country
 */
	char							country [256];

/**
 * @brief Postal code.
 * @var code
 */
	char							code [256];

/**
 * @brief Main architect(s).
 * @var architect
 */
	char							architect [256];

/**
 * @brief Drafts person.
 * @var draftsmen
 */
	char							draftsmen [256];

/**
 * @brief Status of the project as text.
 * @var projectStatus
 */
	char							projectStatus [256];

/**
 * @brief Issue date.
 * @var dateOfIssue
 */
	char							dateOfIssue [256];

/**
 * @brief Other keywords related to the project.
 * @var keywords
 */
	char							keywords [256];

/**
 * @brief Notes for the project info.
 * @var notes
 */
	char							notes [1024];
};


// =============================================================================
// Library Manager
//
// =============================================================================

/**
 * @brief Project library types.
 * @enum API_LibraryTypeID
 * @ingroup LibraryManagement
 * @remarks The `libraryType` data member in the @ref API_LibraryInfo structure defines the type of the project library, which can be
 * 			- Local Library
 * 			- Embedded Library
 * 			- Built-In Library
 * 			- Library on a BIMcloud / BIM Server
 * 			- Web Objects (addressed by URL)
 * 			- Other local objects
 */
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

/**
 * @brief Describes the data of an active library of an Archicad project.
 * @struct API_LibraryInfo
 * @ingroup LibraryManagement
 * @remarks This data structure describes one active library from the library list of Archicad. All the libraries that can be seen in
 * 			the "Library Manager" dialog of Archicad are passed to you with @ref ACAPI_LibraryManagement_GetLibraries.
 * 			Call the @ref ACAPI_LibraryManagement_GetLibraries and @ref ACAPI_LibraryManagement_SetLibraries function codes to operate on this data.
 * 			From 6.1 those library locations which refer to built-in libraries (e.g. library parts coming from an add-on) have an `rfs`
 * 			component at the end. This is necessary if you want to convert the location to a folder, but you can safely remove this component
 * 			for display purposes with `IO::Location::DeleteLastLocalName` or `IO::Location::MoveLastLocalName`.
 * @par Example
 * 		@snippet API_Examples.cpp API_LibraryInfo-Example-Snippet
 */
struct API_LibraryInfo {

/**
 * @brief the folder specification of the library
 * @var location
 */
	IO::Location					location;

/**
 * @brief the name of the library
 * @var name
 */
	GS::UniString					name;

/**
 * @brief the type of the library (Built-In, Local, Embedded, BIM Server, Web Object, Other; see `API_LibraryTypeID`)
 * @var libraryType
 */
	API_LibraryTypeID				libraryType;

/**
 * @brief the library is available (e.g. not missing)
 * @var available
 */
	bool							available;

/**
 * @brief the library is not writable
 * @var readOnly
 */
	bool							readOnly;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	bool							filler[2];

/**
 * @brief URL address of the TeamWork server hosting the library (`API_ServerLibrary` only)
 * @var twServerUrl
 */
	GS::UniString					twServerUrl;

/**
 * @brief URL of the downloaded Internet library (`API_UrlLibrary` and `API_UrlOtherObject` only)
 * @var urlWebLibrary
 */
	GS::UniString					urlWebLibrary;

};


// =============================================================================
// Toolbox
//
// =============================================================================

/**
 * @brief Data of the active toolbox mode.
 * @struct API_ToolBoxItem
 * @ingroup Element
 * @since Archicad 26
 * @remarks For the utilization of this structure see the @ref ACAPI_Toolbox_GetToolBoxMode and
 * 			the @ref ACAPI_Toolbox_SetToolBoxMode environment functions.
 * 			From version 26 the `typeID` and `variationID` members were merged into an @ref API_ElemType structure.
 */
struct API_ToolBoxItem {

/**
 * @brief Toolbox item element type
 * @var type
 */
	API_ElemType					type;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1[2];

};


/**
 * @brief Contains information on the current state of the toolbox.
 * @struct API_ToolBoxInfo
 * @ingroup Toolbox
 * @remarks Remember to dispose of the `data` handle.
 */
struct API_ToolBoxInfo {

/**
 * @brief number of tools installed (internal, subtypes)
 * @var nTools
 */
	Int32							nTools;

/**
 * @brief the tools themselves
 * @var data
 */
	API_ToolBoxItem**				data;

/**
 * @brief the tool which is currently active
 * @var activeTool
 */
	API_ToolBoxItem					activeTool;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1[6];

};


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


/**
 * @brief This is the enumeration of the Partial Structure Display.
 * @enum API_StructureDisplay
 * @ingroup Element
 * @remarks You are able to get and change the Partial Structure Display via @ref ACAPI_Navigator_GetStructureDisplay and @ref ACAPI_Navigator_ChangeStructureDisplay functions. This function allows you to display and output composite and complex elements in simplified form.
 */
typedef enum {
	API_EntireStructure,
	API_CoreOnly,
	API_WithoutFinishes,
	API_StructureOnly
} API_StructureDisplay;


/**
 * @brief This structure represents the Partial Structure Display state.
 * @struct API_UIStructureDisplay
 * @ingroup Navigator
 * @remarks You are able to get and change the Partial Structure Display via @ref ACAPI_Navigator_GetStructureDisplay and @ref ACAPI_Navigator_ChangeStructureDisplay functions. This function allows you to display and output composite and complex elements in simplified form.
 * 			All model based databases (Model2D, Model3D, Section, Elevation, InteriorElevation, DocumentFrom3D) contain their own Partial Structure Display state.
 */
struct API_UIStructureDisplay {

/**
 * @brief The Partial Structure Display state.
 * @var structureDisplay
 */
	API_StructureDisplay			structureDisplay;

/**
 * @brief The identifier of the owner database.
 * @var databaseUnId
 */
	API_DatabaseUnId				databaseUnId;

/**
 * @brief The owner is the 3D window.
 * @var is3D
 */
	bool							is3D;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	bool							filler[7];
};


// =============================================================================
// Classifications
//
// =============================================================================

/**
 * @brief Specifies a classification item.
 * @struct API_ClassificationItem
 * @ingroup Classification
 */
struct API_ClassificationItem {

/**
 * @brief The Archicad generated unique identifier of the classification item
 * @var guid
 */
	API_Guid						guid;

/**
 * @brief The user specified unique identifier for the classification item
 * @var id
 */
	GS::UniString					id;

/**
 * @brief The display name of the classification item
 * @var name
 */
	GS::UniString					name;

/**
 * @brief The description of the classification item
 * @var description
 */
	GS::UniString					description;

	API_ClassificationItem () :
		guid (APINULLGuid)
	{ }

};

/**
 * @brief Specifies a classification system.
 * @struct API_ClassificationSystem
 * @ingroup Classification
 */
struct API_ClassificationSystem {

/**
 * @brief The Archicad generated unique identifier of the classification system
 * @var guid
 */
	API_Guid		guid;

/**
 * @brief The display name of the classification system
 * @var name
 */
	GS::UniString	name;

/**
 * @brief The general description of the classification system
 * @var description
 */
	GS::UniString	description;

/**
 * @brief The source of the classification system (i.e. URL to a classification system standard)
 * @var source
 */
	GS::UniString	source;

/**
 * @brief The version string of the classification system
 * @var editionVersion
 */
	GS::UniString	editionVersion;

/**
 * @brief The release date of this version of the classification system
 * @var editionDate
 */
	GSDateRecord	editionDate;

	API_ClassificationSystem () :
		guid (APINULLGuid)
	{ }

};

// =============================================================================
// Overrides
//
// =============================================================================

/**
 * @brief Represents a combination of override rules with a name.
 * @struct API_OverrideCombination
 * @ingroup GraphicalOverride
 */
struct API_OverrideCombination {

/**
 * @brief The unique identifier of the combination
 * @var guid
 */
	API_Guid						guid;

/**
 * @brief The name of the combination, that is unique within its project
 * @var name
 */
	GS::UniString					name;

};


/**
 * @brief Represents a group of override rules with a name.
 * @struct API_OverrideRuleGroup
 * @ingroup GraphicalOverride
 */
struct API_OverrideRuleGroup {

/**
 * @brief The unique identifier of the rule group
 * @var guid
 */
	API_Guid						guid;

/**
 * @brief The name of the rule group, that is unique within its project
 * @var name
 */
	GS::UniString					name;

};


/**
 * @brief Describes the fill types to be overridden.
 * @struct API_OverriddenFillType
 * @ingroup GraphicalOverride
 */
struct API_OverriddenFillType {

/**
 * @brief Specifies if cut fills should be overridden
 * @var overrideCutFill
 */
	bool							overrideCutFill;

/**
 * @brief Specifies if cover fills should be overridden
 * @var overrideCoverFill
 */
	bool							overrideCoverFill;

/**
 * @brief Specifies if drafting fills should be overridden
 * @var overrideDraftingFill
 */
	bool							overrideDraftingFill;

};


/**
 * @brief Describes the surface types to be overridden.
 * @struct API_OverriddenSurfaceType
 * @ingroup GraphicalOverride
 */
struct API_OverriddenSurfaceType {

/**
 * @brief Specifies if cut surfaces should be overridden
 * @var overrideCutSurface
 */
	bool							overrideCutSurface;

/**
 * @brief Specifies if uncut surfaces should be overridden
 * @var overrideUncutSurface
 */
	bool							overrideUncutSurface;

};


/**
 * @brief Specifies what, and how an @ref API_OverrideRule should override.
 * @struct API_OverrideRuleStyle
 * @ingroup GraphicalOverride
 * @since Archicad 25
 * @remarks In version 25, the fillBackgroundPenOverride and surfaceOverride members type are changed to API_OverriddenAttributeOrRGB
 * 			In version 25, hiddenContours and overrideContours are added
 */
struct API_OverrideRuleStyle {

/**
 * @brief Specifies how the line type should be overridden
 * @var lineType
 */
	API_OverriddenAttribute			lineType;

/**
 * @brief Specifies how the line/marker/text pen should be overridden
 * @var lineMarkerTextPen
 */
	API_OverriddenPen				lineMarkerTextPen;


/**
 * @brief Specifies how the fills should be overridden
 * @var fillOverride
 */
	API_OverriddenAttribute			fillOverride;

/**
 * @brief Specifies which fills should be overridden
 * @var fillType
 */
	API_OverriddenFillType			fillType;

/**
 * @brief Specifies how the fill foreground pen should be overridden
 * @var fillForegroundPenOverride
 */
	API_OverriddenPen				fillForegroundPenOverride;

/**
 * @brief Specifies which fill foreground pen should be overridden
 * @var fillTypeForegroundPen
 */
	API_OverriddenFillType			fillTypeForegroundPen;

/**
 * @brief Specifies how the fill background pen should be overridden
 * @var fillBackgroundPenOverride
 */
	API_OverriddenPenOrRGB			fillBackgroundPenOverride;

/**
 * @brief Specifies which fill background pen should be overridden
 * @var fillTypeBackgroundPen
 */
	API_OverriddenFillType			fillTypeBackgroundPen;


/**
 * @brief Specifies how the surface should be overridden
 * @var surfaceOverride
 */
	API_OverriddenAttributeOrRGB	surfaceOverride;

/**
 * @brief Specifies which surface should be overridden
 * @var surfaceType
 */
	API_OverriddenSurfaceType		surfaceType;

/**
 * @brief Specifies if the skin separators should be shown
 * @var showSkinSeparators
 */
	bool							showSkinSeparators;

/**
 * @brief Specifies if the pen color and thickness should be overridden
 * @var overridePenColorAndThickness
 */
	bool							overridePenColorAndThickness;


/**
 * @brief Specifies which contours should be hidden
 * @var hiddenContours
 */
	API_OverriddenSurfaceType		hiddenContours;

/**
 * @brief Specifies if contour hiding should be overridden
 * @var overrideContours
 */
	bool							overrideContours;

};


/**
 * @brief Represents an override rule.
 * @struct API_OverrideRule
 * @ingroup GraphicalOverride
 */
struct API_OverrideRule {

/**
 * @brief The unique identifier for the override rule
 * @var guid
 */
	API_Guid						guid;

/**
 * @brief The name of the rule, that is unique within the project
 * @var name
 */
	GS::UniString					name;

/**
 * @brief Specifies what, and how this rule should override
 * @var style
 */
	API_OverrideRuleStyle			style;

/**
 * @brief Specifies when this rule should be used. To get the proper criterion XML, save the configured override rule as XML in Archicad. See the Override_Test add-on about the format of the XML
 * @var criterionXML
 */
	GS::UniString					criterionXML;

};


/**
 * @brief Specifies what is overridden and how, for an @ref API_Element.
 * @struct API_OverrideStyle
 * @ingroup Element
 * @since Archicad 25
 * @remarks In version 25, the `cutFillBGPen`, `coverFillBGPen`, `draftingFillBGPen`, `cutSurfaceType` and `uncutSurfaceType` members
 * 			types are changed to `@ref API_OverriddenAttributeOrRGB`.
 * 			In version 25, the `hideCutContours` and `hideUncutContours` members were added.
 */
struct API_OverrideStyle {

/**
 * @brief Specifies how the line type should be overridden
 * @var lineType
 */
	API_OverriddenAttribute			lineType;

/**
 * @brief Specifies how the line/marker/text pen should be overridden
 * @var lineMarkerTextPen
 */
	API_OverriddenPen				lineMarkerTextPen;

/**
 * @brief Specifies if line and pen thickness should be overridden
 * @var overrideLinePenThickness
 */
	bool							overrideLinePenThickness;


/**
 * @brief Specifies how the cut fills should be overridden
 * @var cutFillType
 */
	API_OverriddenAttribute			cutFillType;

/**
 * @brief Specifies how the cut fill foregrounds should be overridden
 * @var cutFillFGPen
 */
	API_OverriddenPen				cutFillFGPen;

/**
 * @brief Specifies how the cut fill backgrounds should be overridden
 * @var cutFillBGPen
 */
	API_OverriddenPenOrRGB			cutFillBGPen;

/**
 * @brief Specifies whether the cut fill foreground pen thickness should be overridden
 * @var overrideCutFillFGThickness
 */
	bool							overrideCutFillFGThickness;


/**
 * @brief Specifies how the cover fills should be overridden
 * @var coverFillType
 */
	API_OverriddenAttribute			coverFillType;

/**
 * @brief Specifies how the cover fill foregrounds should be overridden
 * @var coverFillFGPen
 */
	API_OverriddenPen			coverFillFGPen;

/**
 * @brief Specifies how the cover fill backgrounds should be overridden
 * @var coverFillBGPen
 */
	API_OverriddenPenOrRGB	coverFillBGPen;

/**
 * @brief Specifies whether the cover fill foreground pen thickness should be overridden
 * @var overrideCoverFillFGThickness
 */
	bool							overrideCoverFillFGThickness;


/**
 * @brief Specifies how the draft fills should be overridden
 * @var draftFillType
 */
	API_OverriddenAttribute			draftFillType;

/**
 * @brief Specifies how the draft fill foregrounds should be overridden
 * @var draftFillFGPen
 */
	API_OverriddenPen			draftFillFGPen;

/**
 * @brief Specifies how the draft fill backgrounds should be overridden
 * @var draftFillBGPen
 */
	API_OverriddenPenOrRGB	draftFillBGPen;

/**
 * @brief Specifies whether the draft fill foreground pen thickness should be overridden
 * @var overrideDraftFillFGThickness
 */
	bool							overrideDraftFillFGThickness;


/**
 * @brief Specifies how the cut surfaces should be overridden
 * @var cutSurfaceType
 */
	API_OverriddenAttributeOrRGB	cutSurfaceType;

/**
 * @brief Specifies how the uncut surfaces should be overridden
 * @var uncutSurfaceType
 */
	API_OverriddenAttributeOrRGB	uncutSurfaceType;

/**
 * @brief Specifies if the skin separators should be shown
 * @var showSkinSeparators
 */
	bool							showSkinSeparators;


/**
 * @brief Specifies if the contours of the cut surface should be hidden
 * @var hideCutContours
 */
	bool							hideCutContours;

/**
 * @brief Specifies if the contours of the uncut surface should be hidden
 * @var hideUncutContours
 */
	bool							hideUncutContours;

};



/**
 * @brief View type identifier
 * @enum API_ImageViewID
 * @ingroup Element
 * @remarks This structure is used in @ref API_VisualOverriddenImage.
 */
typedef enum {
	APIImage_Model2D	= 0,
	APIImage_Model3D	= 1,
	APIImage_Section	= 2

} API_ImageViewID;

/**
 * @brief Visual overridden image descriptor
 * @struct API_VisualOverriddenImage
 * @ingroup GraphicalOverride
 * @remarks Use this structure with @ref ACAPI_GraphicalOverride_GetVisualOverriddenImage function.
 */
struct API_VisualOverriddenImage {

/**
 * @brief The view type identifier.
 * @var view
 */
	API_ImageViewID					view;

/**
 * @brief The visual override style of the preview image.
 * @var overrideStyle
 */
	API_OverrideStyle				overrideStyle;

/**
 * @brief Handle for the output vector image.
 * @var vectorImageHandle
 */
	GSHandle						vectorImageHandle;

/**
 * @brief Pointer to the output native image.
 * @var nativeImagePtr
 */
	NewDisplay::NativeImage*		nativeImagePtr;

};

/**
 * @brief Structure for retrieving data related to a room.
 * @struct API_RoomImage
 * @ingroup Element
 * @remarks To learn more about the usage of the structure please refer to the @ref ACAPI_Element_GetRoomImage function.
 */
struct API_RoomImage {

/**
 * @brief Element identifier of the zone.
 * @var roomGuid
 */
	API_Guid						roomGuid;

/**
 * @brief Currently not used, only the 2D image (Floor Plan) can be generated.
 * @var viewType
 */
	API_ImageViewID					viewType;

/**
 * @brief Offset of the clip polygon from the edge of the zone.
 * @var offset
 */
	double							offset;

/**
 * @brief Scale of the view (e.g. 0.002 for 1:500).
 * @var scale
 */
	double							scale;

/**
 * @brief Background color of the generated image.
 * @var backgroundColor
 */
	API_RGBColor					backgroundColor;

/**
 * @brief Pointer to the output image (must be initialized before calling @ref ACAPI_Element_GetRoomImage).
 * @var nativeImagePtr
 */
	NewDisplay::NativeImage*		nativeImagePtr;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	Int32							filler[4];

};


// =============================================================================
// Story Settings
//
// =============================================================================

/**
 * @brief Ghost Story settings.
 * @struct API_GhostStoryType
 * @ingroup View
 * @sa ACAPI_View_GetGhostStorySettings
 * @remarks This structure is a member of @ref API_StoryInfo.
 */
struct API_GhostStoryType {

/**
 * @brief Ghost story is visible or hidden
 * @var on
 */
	bool							on;

/**
 * @brief Ghost story is specified in the @c storyInd field (show this story)
 * @var showOne
 */
	bool							showOne;

/**
 * @brief Show on the story above the current as ghost story
 * @var showAbove
 */
	bool							showAbove;

/**
 * @brief Show on the story below the current as ghost story
 * @var showBelow
 */
	bool							showBelow;

/**
 * @brief The index of the story displayed as ghost story (if @c showOne is @c true)
 * @var storyInd
 */
	short							storyInd;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief Ghost story color
 * @var ghostColor
 */
	API_RGBColor					ghostColor;

/**
 * @brief Element type filter to show/hide elements on the ghost story
 * @var filter
 */
	API_ElemFilter					filter;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2;

};

/**
 * @brief Represents the way of the ghost to be shown.
 * @enum API_ShowGhostType
 * @ingroup View
 */
typedef enum {
	APIGhost_NoFloor = 0,
	APIGhost_ShowOneFloor,
	APIGhost_ShowAboveFloor,
	APIGhost_ShowBelowFloor,
	APIGhost_ShowPreviousFloor,
	APIGhost_ShowAllStructure
}  API_ShowGhostType;

/**
 * @brief Describes a tracing (ghost) database.
 * @struct API_GhostRecord
 * @ingroup View
 * @remarks This structure describes the Trace feature related information.
 */
struct API_GhostRecord {

/**
 * @brief Position of the reference database.
 * @var offset
 */
	API_Coord						offset;

/**
 * @brief Rotation angle of the reference database.
 * @var rotation
 */
	double							rotation;

/**
 * @brief Scale factor of the reference database.
 * @var scale
 */
	double							scale;

/**
 * @brief Last modification time of the reference database.
 * @var time
 */
	GSTime							time;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief Identifier of the parent database (i.e. out of which the reference database was created from).
 * @var parentDatabase
 */
	API_DatabaseUnId				parentDatabase;

/**
 * @brief Own identifier.
 * @var ghostDatabase
 */
	API_DatabaseUnId				ghostDatabase;

/**
 * @brief Type of the reference database.
 * @var ghostDBType
 */
	API_DatabaseTypeID				ghostDBType;

/**
 * @brief Reference previous/above current/below current story.
 * @var ghostType
 */
	API_ShowGhostType				ghostType;

/**
 * @brief Tells which element types are visible.
 * @var filter
 */
	API_ElemFilter					filter;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool							filler_2[5];

/**
 * @brief Original floor of the reference database.
 * @var floor
 */
	short							floor;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	short							filler_3;

/**
 * @brief Is it activated?
 * @var activated
 */
	bool							activated;

/**
 * @brief Is it shown?
 * @var show
 */
	bool							show;

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	short							filler_4;

/**
 * @brief Reference database color with transparency.
 * @var ghostColor
 */
	API_RGBAColor					ghostColor;

/**
 * @brief The color of the ghost view.
 * @var ghostOriginalColor
 */
	bool							ghostOriginalColor;

/**
 * @brief The tone of the ghost view.
 * @var ghostOriginalTone
 */
	bool							ghostOriginalTone;

/**
 * @brief The background fill of the ghost view.
 * @var ghostBackgroundFill
 */
	bool							ghostBackgroundFill;

/**
 * @brief Reserved for later use.
 * @var filler_5
 */
	bool							filler_5[5];

/**
 * @brief Parent database color with transparency.
 * @var viewColor
 */
	API_RGBAColor					viewColor;

/**
 * @brief The color of the originating view.
 * @var viewOriginalColor
 */
	bool							viewOriginalColor;

/**
 * @brief The tone of the originating view.
 * @var viewOriginalTone
 */
	bool							viewOriginalTone;

/**
 * @brief The background fill of the originating view.
 * @var viewBackgroundFill
 */
	bool							viewBackgroundFill;

/**
 * @brief Reserved for later use.
 * @var filler_6
 */
	bool							filler_6;

/**
 * @brief Is Ghost on the top?
 * @var ghostOnTop
 */
	bool							ghostOnTop;

/**
 * @brief Reserved for later use.
 * @var filler_7
 */
	bool							filler_7[3];

};

/**
 * @brief Story information of the active project.
 * @struct API_StoryInfo
 * @ingroup View
 * @sa ACAPI_ProjectSetting_GetStorySettings, @ref ACAPI_ProjectSetting_ChangeStorySettings
 * @remarks This structure corresponds to the "Story Settings..." dialog of Archicad. The parameters of each story are contained, as well as the parameters ghost story settings.
 * 			Call the @ref ACAPI_ProjectSetting_GetStorySettings or @ref ACAPI_ProjectSetting_ChangeStorySettings functions to operate on this data.
 * 			Remomber to dispose of the `data` array if you don't need it anymore.
 * 			Note, that a virtual story is also exported, above the top story. This story does not exist, but the level parameter is important to calculate the height of the top story.
 * 			Ghost story settings can also be retrieved by the @ref ACAPI_View_GetGhostStorySettings function.
 */
struct API_StoryInfo {

/**
 * @brief First story index.
 * @var firstStory
 */
	short							firstStory;

/**
 * @brief Last story index.
 * @var lastStory
 */
	short							lastStory;

/**
 * @brief Actual (currently visible in 2D) story index.
 * @var actStory
 */
	short							actStory;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1;

/**
 * @brief Floor indices above ground-floor level start with 1 instead of 0. (US, Japan)
 * @var skipNullFloor
 */
	bool							skipNullFloor;

/**
 * @brief Array of data to hold the parameters of each story. Refer to @c API_StoryType for further details.
 * @var data
 */
	API_StoryType**					data;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2;

/**
 * @brief Ghost story settings. Refer to @c API_GhostStoryType for further details.
 * @var ghostStory
 */
	API_GhostStoryType				ghostStory;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3[4];

};


/**
 * @brief Action codes for the story settings command.
 * @enum API_StoryCmdID
 * @ingroup View
 * @remarks Refer to the @ref API_StoryCmdType structure for further details on modifying the story structure of Archicad.
 */
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

/**
 * @brief Parameters of the change story settings command.
 * @struct API_StoryCmdType
 * @ingroup View
 * @remarks The command is related to an existing story. It must be referred by the index field of the structure. Possible operations are listed in the @ref API_StoryCmdID list.
 * 			Note, that in case story operations are disabled in team projects; except changing the active story.
 * 			Note that story operations —except changing the active story— are disabled in teamwork projects.
 */
struct API_StoryCmdType {

/**
 * @brief Action to be done in the Story Settings dialog.
 * @var action
 */
	API_StoryCmdID					action;

/**
 * @brief An existing story index, which the command is performed upon.
 * @var index
 */
	short							index;

/**
 * @brief The level line of the given story will or will not appear in any model window; in the case of `APIStory_SetDispOnSections`.
 * @var dispOnSections
 */
	bool							dispOnSections;

/**
 * @brief Do not call rebuild or redraw after Go To Story command.
 * @var dontRebuild
 */
	bool							dontRebuild;

/**
 * @brief Story height value; in the case of `APIStory_SetHeight`, `APIStory_InsAbove`, or `APIStory_InsBelow` commands.
 * @var height
 */
	double							height;

/**
 * @brief Story elevation value for `APIStory_SetElevation`.
 * @var elevation
 */
	double							elevation;

/**
 * @brief Story name for `APIStory_InsAbove`, `APIStory_InsBelow`, and `APIStory_Rename`.
 * @var uName
 */
	GS::uchar_t						uName [API_UniLongNameLen];

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[4];

};


// =============================================================================
// Preferences
//
// =============================================================================

/**
 * @brief Possible values for length unit preferences.
 * @enum API_LengthTypeID
 * @ingroup Navigator
 * @since Archicad 26
 */
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

/**
 * @brief Possible values for area unit preferences.
 * @enum API_AreaTypeID
 * @ingroup Navigator
 * @since Archicad 26
 */
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

/**
 * @brief Possible values for volume unit preferences.
 * @enum API_VolumeTypeID
 * @ingroup ProjectSetting
 */
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

/**
 * @brief Possible values for angle unit preferences.
 * @enum API_AngleTypeID
 * @ingroup Navigator
 */
enum class API_AngleTypeID {
	DecimalDegree,
	DegreeMinSec,
	Grad,
	Radian,
	Surveyors

};

/**
 * @brief The representation of the Preferences / Units tab page.
 * @struct API_WorkingUnitPrefs
 * @ingroup ProjectSetting
 * @sa ACAPI_ProjectSetting_GetPreferences, @c ACAPI_ProjectSetting_SetPreferences
 * @remarks This structure is used by the @ref ACAPI_ProjectSetting_GetPreferences function to get the settings of the unit preferences page.
 */
struct API_WorkingUnitPrefs {

/**
 * @brief The type of the length measurement unit.
 * @var lengthUnit
 */
	API_LengthTypeID				lengthUnit;

/**
 * @brief The type of the area measurement unit.
 * @var areaUnit
 */
	API_AreaTypeID					areaUnit;

/**
 * @brief The type of the volume measurement unit.
 * @var volumeUnit
 */
	API_VolumeTypeID				volumeUnit;

/**
 * @brief The type of the angle measurement unit.
 * @var angleUnit
 */
	API_AngleTypeID					angleUnit;

/**
 * @brief 1, 2, 4, 8, 16, 32, 64
 * @var roundInch
 */
	short							roundInch;

/**
 * @brief Number of decimals for length measurement unit. (0..4)
 * @var lenDecimals
 */
	short							lenDecimals;

/**
 * @brief Number of decimals for area measurement unit. (0..4)
 * @var areaDecimals
 */
	short							areaDecimals;

/**
 * @brief Number of decimals for volume measurement unit. (0..4)
 * @var volumeDecimals
 */
	short							volumeDecimals;

/**
 * @brief Number of decimals for angle measurement unit. (0..4)
 * @var angleDecimals
 */
	short							angleDecimals;

/**
 * @brief 0..4
 * @var angleAccuracy
 */
	short							angleAccuracy;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1[12];

};


/**
 * @brief European methods for rounding decimal values.
 * @enum API_ExtraAccuracyID
 * @ingroup Navigator
 */
typedef enum {
	APIExtAc_Off					= 0,
	APIExtAc_Small5					= 1,						// show small 5 after decimals
	APIExtAc_Small25				= 2,						// show small 25/75 after decimals
	APIExtAc_Small1					= 3,						// show small 1 after decimals
	APIExtAc_Small01				= 4,						// show small 01 after decimals
	APIExtAc_Fractions				= 10						// FootInch & Inch case small Fractions
} API_ExtraAccuracyID;

/**
 * @brief The representation of the linear, radial, level, elevation, door/window and parapet dimensioning on the Preferences / Dimensioning tab page.
 * @struct API_LengthDimFormat
 * @ingroup Navigator
 * @remarks This structure is a member of @ref API_DimensionPrefs.
 */
struct API_LengthDimFormat {

/**
 * @brief measurement unit, for the possible values see `API_LengthTypeID`
 * @var unit
 */
	API_LengthTypeID				unit;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	short							filler_0;

/**
 * @brief fractional inches (1, 2, 4, 8, 16, 32, 64)
 * @var roundInch
 */
	short							roundInch;

/**
 * @brief number of decimals (0, 1, 2, 3, 4)
 * @var lenDecimals
 */
	short							lenDecimals;

/**
 * @brief show zeros to the left of the decimal point
 * @var show0Whole
 */
	bool							show0Whole;

/**
 * @brief show zeros to the left of the decimal inches
 * @var show0Inch
 */
	char							show0Inch;

/**
 * @brief European methods for rounding decimal values
 * @var showSmall5
 */
	API_ExtraAccuracyID				showSmall5;

/**
 * @brief hide zeros at the right of the decimal point
 * @var hide0Dec
 */
	bool							hide0Dec;

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

};

/**
 * @brief The representation of the angle dimensioning on the Preferences / Dimensioning tab page.
 * @struct API_AngleDimFormat
 * @ingroup Navigator
 * @remarks This structure is a member of @ref API_DimensionPrefs.
 */
struct API_AngleDimFormat {

/**
 * @brief measurement unit, for the possible values see `API_AngleTypeID`
 * @var unit
 */
	API_AngleTypeID					unit;

/**
 * @brief number of digits when using decimal degrees, grad or radian units (0, 1, 2, 3, 4)
 * @var angleDecimals
 */
	short							angleDecimals;

/**
 * @brief precision of the angle measurement units (°, ', ")
 * @var angleAccuracy
 */
	short							angleAccuracy;

/**
 * @brief hide zeros at the right of the decimal point
 * @var hide0Dec
 */
	bool							hide0Dec;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	char							filler_0[3];

};

/**
 * @brief The representation of the area dimensioning on the Preferences / Dimensioning tab page.
 * @struct API_AreaDimFormat
 * @ingroup Navigator
 * @remarks This structure is a member of @ref API_DimensionPrefs.
 */
struct API_AreaDimFormat {

/**
 * @brief measurement unit, for the possible values see `API_AreaTypeID`
 * @var unit
 */
	API_AreaTypeID					unit;

/**
 * @brief number of decimals (0, 1, 2, 3, 4)
 * @var lenDecimals
 */
	short							lenDecimals;

/**
 * @brief hide zeros at the right of the decimal point
 * @var hide0Dec
 */
	bool							hide0Dec;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	char							filler_0;

};

/**
 * @brief The representation of the Project Preferences / Dimensions tab page.
 * @struct API_DimensionPrefs
 * @ingroup ProjectSetting
 * @sa ACAPI_ProjectSetting_GetPreferences, @c ACAPI_ProjectSetting_SetPreferences
 * @remarks This structure is used by the @ref ACAPI_ProjectSetting_GetPreferences function to get the settings of the Project Preferences / Dimensions page.
 */
struct API_DimensionPrefs {

/**
 * @brief Linear Dimensions preferences
 * @var linear
 */
	API_LengthDimFormat				linear;

/**
 * @brief Angular Dimensions preferences
 * @var angle
 */
	API_AngleDimFormat				angle;

/**
 * @brief Radial Dimensions preferences
 * @var radial
 */
	API_LengthDimFormat				radial;

/**
 * @brief Level Dimensions preferences
 * @var level
 */
	API_LengthDimFormat				level;

/**
 * @brief Elevation Dimensions preferences
 * @var elevation
 */
	API_LengthDimFormat				elevation;

/**
 * @brief Door, Window and Skylight Dimensions preferences
 * @var doorwindow
 */
	API_LengthDimFormat				doorwindow;

/**
 * @brief Sill Height Dimensions preferences
 * @var parapet
 */
	API_LengthDimFormat				parapet;

/**
 * @brief Area Calculations preferences
 * @var area
 */
	API_AreaDimFormat				area;

/**
 * @brief dimension style attribute index if the dimension preferences are stored for views (see @ref API_DimensionStandardsType)
 * @var index
 */
	short							index;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	short							filler_0;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1[3];

};


/**
 * @brief The @ref API_CalcUnitPrefs structure contains this structure.
 * @struct API_CalcLengthFormat
 * @ingroup ProjectSetting
 */
struct API_CalcLengthFormat {

/**
 * @brief The type of the length measurement unit.
 * @var unit
 */
	API_LengthTypeID				unit;

/**
 * @brief European methods for rounding decimal values.
 * @var accuracy
 */
	API_ExtraAccuracyID				accuracy;

/**
 * @brief Number of decimals for length measurement unit [0..4]
 * @var decimals
 */
	short							decimals;

/**
 * @brief fractional inches (1, 2, 4, 8, 16, 32, 64)
 * @var roundInch
 */
	short							roundInch;

};

/**
 * @brief The @ref API_CalcUnitPrefs structure contains this structure.
 * @struct API_CalcAreaFormat
 * @ingroup ProjectSetting
 */
struct API_CalcAreaFormat {

/**
 * @brief The type of the area measurement unit.
 * @var unit
 */
	API_AreaTypeID					unit;

/**
 * @brief European methods for rounding decimal values.
 * @var accuracy
 */
	API_ExtraAccuracyID				accuracy;

/**
 * @brief Number of decimals for area measurement unit [0..4]
 * @var decimals
 */
	short							decimals;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

};

/**
 * @brief The @ref API_CalcUnitPrefs structure contains this structure.
 * @struct API_CalcVolumeFormat
 * @ingroup ProjectSetting
 */
struct API_CalcVolumeFormat {

/**
 * @brief The type of the volume measurement unit.
 * @var unit
 */
	API_VolumeTypeID				unit;

/**
 * @brief European methods for rounding decimal values.
 * @var accuracy
 */
	API_ExtraAccuracyID				accuracy;

/**
 * @brief Number of decimals for volume measurement unit [0..4]
 * @var decimals
 */
	short							decimals;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

};

/**
 * @brief The @ref API_CalcUnitPrefs structure contains this structure.
 * @struct API_CalcAngleFormat
 * @ingroup ProjectSetting
 */
struct API_CalcAngleFormat {

/**
 * @brief The type of the angle measurement unit.
 * @var unit
 */
	API_AngleTypeID					unit;

/**
 * @brief Number of decimals for angle measurement unit [0..4]
 * @var decimals
 */
	short							decimals;

/**
 * @brief European methods for rounding decimal values.
 * @var accuracy
 */
	short							accuracy;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	Int32							filler_0;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

};

/**
 * @brief The representation of the Project Preferences / Calculation Units Rules tab page.
 * @struct API_CalcUnitPrefs
 * @ingroup ProjectSetting
 * @remarks This structure is used by the @ref ACAPI_ProjectSetting_GetPreferences function to get the settings of the Calculation Units Rules preferences page.
 */
struct API_CalcUnitPrefs {

/**
 * @brief Length preferences.
 * @var length
 */
	API_CalcLengthFormat			length;

/**
 * @brief Area preferences.
 * @var area
 */
	API_CalcAreaFormat				area;

/**
 * @brief Volume preferences.
 * @var volume
 */
	API_CalcVolumeFormat			volume;

/**
 * @brief Angle preferences.
 * @var angle
 */
	API_CalcAngleFormat				angle;

/**
 * @brief Represents the "Calculate Totals by" RadioButton. @c true means that Archicad should use the displayed values in calculations.
 * 		  This way the calculations can be verified manually. @c false means that Archicad should use the exact values (in @c double precision) in calculations.
 * @var useDisplayedValues
 */
	bool							useDisplayedValues;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	bool							filler_0[15];

};

/**
 * @brief Property type of an element used in conditional calculation element rules.
 * @enum API_ConditionalElementPropertyTypeID
 * @ingroup ProjectSetting
 * @since Archicad 25
 */
typedef enum {
	APIConditionalElementPropertyType_Volume,
	APIConditionalElementPropertyType_Surface,
	APIConditionalElementPropertyType_Length
} API_ConditionalElementPropertyTypeID;

/**
 * @brief The representation of a conditional element rule on the Preferences / Calculation Rules tab page.
 * @struct API_ConditionalElementRule
 * @ingroup ProjectSetting
 * @since Archicad 26
 * @remarks Valid element types for `APIConditionalElementPropertyType_Volume`:
 * 			- @c API_WallID
 * 			- @c API_SlabID
 * 			- @c API_RoofID
 * 			- @c API_ShellID
 * 			- @c API_BeamID
 * 			Valid element types for `APIConditionalElementPropertyType_Surface`:
 * 			- @c API_WallID
 * 			- @c API_SlabID
 * 			- @c API_RoofID
 * 			- @c API_ShellID
 * 			Valid element type for `APIConditionalElementPropertyType_Length`:
 * 			- @c API_WallID
 * 			From version 26 the type of the elementTypes member was changed into `GS::HashSet<API_ElemType>`.
 */
struct API_ConditionalElementRule {

/**
 * @brief Type of element property to which the rule is applied.
 * @var propertyType
 */
	API_ConditionalElementPropertyTypeID		propertyType;

/**
 * @brief Limit of element hole size. Holes smaller than the limit are ignored in calculations.
 * @var holeLimit
 */
	double										holeLimit;

/**
 * @brief List of element types to which the rule is applied.
 * @var elementTypes
 */
	GS::HashSet<API_ElemType>					elementTypes;

};

/**
 * @brief The representation of the Calculation Rules on the Preferences / Calculation Units Rules tab
 * 		  page.
 * @struct API_CalcRulesPrefs
 * @ingroup ProjectSetting
 * @since Archicad 25
 * @remarks The @ref ACAPI_ProjectSetting_GetPreferences function uses this structure to get the settings of the Calculation
 * 			Rules on the Preferences / Calculation Units Rules preferences page. From API 25 `BNZeroMemory`, `BNClear`, or
 * 			`memset` should not be used to initialize an object of this structure.
 */
struct API_CalcRulesPrefs {

/**
 * @brief Conditional calculation rules for elements.
 * @var elementRules
 */
	GS::Array<API_ConditionalElementRule>	elementRules;


/**
 * @brief Wall insulation fill indices.
 * @var wallInsulationFills
 */
	GS::HashSet<API_AttributeIndex>			wallInsulationFills;

/**
 * @brief Wall air fill indices.
 * @var wallAirFills
 */
	GS::HashSet<API_AttributeIndex>			wallAirFills;

/**
 * @brief Roof insulation fill indices.
 * @var roofInsulationFills
 */
	GS::HashSet<API_AttributeIndex>			roofInsulationFills;

/**
 * @brief Shell insulation fill indexes.
 * @var shellInsulationFills
 */
	GS::HashSet<API_AttributeIndex>			shellInsulationFills;

};

typedef enum {
	APIRoofDisplay_AllVisibleContours		= 1,
	APIRoofDisplay_OnlyTheTopSurfaceOldWay	= 2
} API_RoofContourDisplay;

/**
 * @brief The representation of the Preferences / Legacy tab page.
 * @struct API_LegacyPrefs
 * @ingroup ProjectSetting
 * @remarks This structure is used by the @ref ACAPI_ProjectSetting_GetPreferences function to get the legacy
 * 			preferences page.
 * 			The `aboveLineType` and `belowLineType` parameters are are only effective on Library Parts if
 * 			the "Use Symbol Linetypes" checkbox in their Settings dialog boxes is switched off. They have no effect on
 * 			Ghost Story elements.
 */
struct API_LegacyPrefs {

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief The priority factor for column intersection.
 * @var coluConnPriority
 */
	Int32							coluConnPriority;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	short							filler_2;

/**
 * @brief Line type index to be used for displaying construction elements above their home story.
 * @var aboveLineType
 */
	API_AttributeIndex				aboveLineType;

/**
 * @brief Line type index to be used for displaying construction elements below their home story.
 * @var belowLineType
 */
	API_AttributeIndex				belowLineType;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	short							filler_3;

/**
 * @brief Display the roof with all visible contours (@c APIRoofDisplay_AllVisibleContours), or the old way (@c APIRoofDisplay_OnlyTheTopSurfaceOldWay).
 * 		  Possible values: @c API_RoofContourDisplay @c APIRoofDisplay_AllVisibleContours @c APIRoofDisplay_OnlyTheTopSurfaceOldWay
 * @var roofContourDisplay
 */
	API_RoofContourDisplay			roofContourDisplay;

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	bool							filler_4;

/**
 * @brief Use legacy intersection and Surface methods for model elements.
 * @var useLegacyIntersections
 */
	bool							useLegacyIntersections;

	/**
	 * @brief Hide zones on sections.
	 * @var hideZonesOnSections
	 */
	bool							hideZonesOnSections;

/**
 * @brief Reserved for later use.
 * @var filler_5
 */
	char							filler_5;

/**
 * @brief Reserved for later use.
 * @var filler_6
 */
	Int32							filler_6[12];

};


#define APIRecess_And				1							// add wall recesses: deeper nichDepth and larger nichSize
#define APIRecess_Or				2							// add wall recesses: deeper nichDepth or larger nichSize

/**
 * @brief The representation of the Preferences / Zones tab page.
 * @struct API_ZonePrefs
 * @ingroup ProjectSetting
 * @remarks This structure is used by the @ref ACAPI_ProjectSetting_GetPreferences function to get the settings of the zone preferences page.
 */
struct API_ZonePrefs {

/**
 * @brief The depth of the recesses to Zone.
 * @var nichDepth
 */
	double							nichDepth;

/**
 * @brief The size of the recess to Zones.
 * @var nichSize
 */
	double							nichSize;

/**
 * @brief The relation between depth and size variable. It can be one of the following constants: @c APIRecess_And, @c APIRecess_Or
 * @var nichCombineMode
 */
	unsigned char					nichCombineMode;

/**
 * @brief Whether the recesses created by windows are included in the Zone size, depending on values of the @c nichDepth, @c nichSize, and the relation of those.
 * @var nichWindFlag
 */
	bool							nichWindFlag;

/**
 * @brief Whether the recesses created by windows are included in the Zone size, depending on values of the @c nichDepth, @c nichSize, and the relation of those.
 * @var nichDoorFlag
 */
	bool							nichDoorFlag;

/**
 * @brief Whether the minimal value for the depth of the wall recesses (@c nichDepth) is taken notice of.
 * @var nichDepthFlag
 */
	bool							nichDepthFlag;

/**
 * @brief Whether the minimal value for the size of the wall recesses (@c nichSize) is taken notice of.
 * @var nichSizeFlag
 */
	bool							nichSizeFlag;

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
 * @brief Whether the areas of wall elements are subtracted from the Zone size.
 * @var subtrWallFlag
 */
	bool							subtrWallFlag;

/**
 * @brief Whether the areas of columns elements are subtracted from the Zone size.
 * @var subtrColuFlag
 */
	bool							subtrColuFlag;

/**
 * @brief Percent of subtraction for the wall elements from the Zone sizes.
 * @var subtrWallPercent
 */
	unsigned char					subtrWallPercent;

/**
 * @brief Percent of subtraction for the column elements from the Zone sizes.
 * @var subtrColuPercent
 */
	unsigned char					subtrColuPercent;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3;

/**
 * @brief The minimal square meters for the wall elements placed inside a Zone area to subtract areas of walls from Zone sizes.
 * @var subtrWallSize
 */
	double							subtrWallSize;

/**
 * @brief The minimal square meters for the columns elements placed inside a Zone area to subtract areas of columns from Zone sizes.
 * @var subtrColuSize
 */
	double							subtrColuSize;

/**
 * @brief Number of height limits for ceiling reduction.
 * @var nLowAreas
 */
	unsigned char					nLowAreas;

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	bool							filler_4;

/**
 * @brief Reserved for later use.
 * @var filler_5
 */
	short							filler_5;

/**
 * @brief The ratios for height limits (@ref roomHeightLimits) to take into account for calculating Zone sizes.
 * @var roomRedPercents
 */
	unsigned char					roomRedPercents[4];

/**
 * @brief The height limits to take into account for calculating Zone sizes.
 * @var roomHeightLimits
 */
	double							roomHeightLimits[4];

/**
 * @brief Reserved for later use.
 * @var filler_6
 */
	Int32							filler_6[16];

};

/**
 * @brief The representation of the Preferences / Miscellaneous tab page.
 * @struct API_SafetyPrefs
 * @ingroup ProjectSetting
 * @remarks This structure is used by the @ref ACAPI_ProjectSetting_GetPreferences function to get the settings of the safety preferences page.
 */
struct API_SafetyPrefs {

/**
 * @brief the location of the temporary folder
 * @var tempFolder
 */
	IO::Location*					tempFolder;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1[15];

};

/**
 * @brief The representation of the Reference Levels on the Preferences / Working Units Levels tab page.
 * @struct API_RefLevelsPrefs
 * @ingroup ProjectSetting
 * @remarks This structure is used by the @ref ACAPI_ProjectSetting_GetPreferences function to get the settings of the Working Units Levels preferences page.
 */
struct API_RefLevelsPrefs {

/**
 * @brief The name of the first reference level.
 * @var level1UStr
 */
    GS::UniString					*level1UStr;

/**
 * @brief The name of the second reference level.
 * @var level2UStr
 */
    GS::UniString                   *level2UStr;

/**
 * @brief The value of the first reference level.
 * @var level1val
 */
    double							level1val;

/**
 * @brief The value of the second reference level.
 * @var level2val
 */
    double							level2val;

};


#define APIReportLevel_No			0							// no Report
#define APIReportLevel_Brief		1							// brief Report
#define APIReportLevel_Short		2							// short Report
#define APIReportLevel_Detailed		3							// detailed Report
#define APIReportLevel_Full			4							// full Report

#define APICalcSelElems_ShowAlert	1							// display warning dialog to choose listing method
#define APICalcSelElems_ListAll		2							// calculate all selected elements in the list
#define APICalcSelElems_UseFilters	3							// apply filters defined for the selected elements

/**
 * @brief The representation of the Imaging and Calculation tab page of the Work Environment dialog.
 * @struct API_ImagingAndCalcPrefs
 * @ingroup ProjectSetting
 * @remarks This structure is used by the @ref ACAPI_ProjectSetting_GetPreferences function to get the settings
 * 			of the Imaging and Calculation tab page of the Work Environment dialog.
 */
struct API_ImagingAndCalcPrefs {

/**
 * @brief Rebuild the 3D window whenever it's brought to the front
 * @var autoRebuild3D
 */
	bool							autoRebuild3D;

/**
 * @brief Bring the 3D window to the front whenever the 3D Projection Settings or Rendering modes are changed
 * @var activate3DOnChange
 */
	bool							activate3DOnChange;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1;

/**
 * @brief Display previously magnified detail in the section window whenever the section window is rebuilt
 * @var keepZoomedSection
 */
	bool							keepZoomedSection;

/**
 * @brief Display the 3D progress information window
 * @var showProgressWindow
 */
	bool							showProgressWindow;

/**
 * @brief Allow interruption of any imaging process
 * @var interruptOnError
 */
	bool							interruptOnError;

/**
 * @brief Enable sound indications of 3D processes
 * @var progressSounds
 */
	bool							progressSounds;

/**
 * @brief Create a 3D Report window
 * @var generate3DReport
 */
	bool							generate3DReport;

/**
 * @brief Value of the slider that defines one of four levels of detail for the 3D Report:
 * 		  | Value | Report level |
 * 		  |-------|--------------|
 * 		  | @c APIReportLevel_No | No Report |
 * 		  | @c APIReportLevel_Brief | Brief Report |
 * 		  | @c APIReportLevel_Short | Short Report |
 * 		  | @c APIReportLevel_Detailed | Detailed Report |
 * 		  | @c APIReportLevel_Full | Full Report |
 * @var reportLevel
 */
	short							reportLevel;

/**
 * @brief Switch to define how to handle selected elements while listing:
 * 		  | Value | Meaning |
 * 		  |-------|---------|
 * 		  | @c APICalcSelElems_ShowAlert | Display warning dialog to choose listing method |
 * 		  | @c APICalcSelElems_ListAll | Calculate all selected elements in the list |
 * 		  | @c APICalcSelElems_UseFilters |Apply filters defined for the selected elements |
 * @var selElemsListing
 */
	short							selElemsListing;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2 [5];

};

/**
 * @brief Parameters of the Floor Plan Cut Plane Settings dialog.
 * @ingroup ProjectSetting
 * @struct API_FloorPlanCutDefinition
 * @remarks The Floor Plan Cut Plane Settings define the visibility limitations of floor plan elements on the current view. In their Floor Plan and Section settings the model elements can be set to be displayed on the floor plan according to the relative floor plan range or the absolute display limit (see @ref API_ElemViewDepthLimitationsID).
 * 			In order to access to these global parameters use the @ref ACAPI_ProjectSetting_GetPreferences environment function with the @ref API_FloorPlanCutDefinition structure and @c APIPrefs_FloorPlanCutPlaneDef preferences type ID.
 */
struct API_FloorPlanCutDefinition {

/**
 * @brief The level of the cut plane that determines the appearance of elements on the floor plan of the current view.
 * @var currCutLevel
 */
	double							currCutLevel;

/**
 * @brief Upper limit of the view range relative to the top story specified in `topCutBaseStoryRelInd`.
 * @var topCutLevel
 */
	double							topCutLevel;

/**
 * @brief Lower limit of the view range relative to the bottom story specified in `bottomCutBaseStoryRelInd`.
 * @var bottomCutLevel
 */
	double							bottomCutLevel;

/**
 * @brief Elements of the floor plan will be displayed up to the given number of stories above the cut plane.
 * @var topCutBaseStoryRelInd
 */
	short							topCutBaseStoryRelInd;

/**
 * @brief Elements of the floor plan will be displayed down to the given number of stories below the cut plane.
 * @var bottomCutBaseStoryRelInd
 */
	short							bottomCutBaseStoryRelInd;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	Int32							filler;

/**
 * @brief The absolute lowest display limit relative to the project zero where the elements of the floor plan are visible.
 * @var fixLevel2Absolute0
 */
	double							fixLevel2Absolute0;

};

/**
 * @brief The representation of the Layouts page of the Project Preferences.
 * @struct API_LayoutsPrefs
 * @ingroup ProjectSetting
 * @remarks This structure is used by the @ref ACAPI_ProjectSetting_GetPreferences function to get the settings of the Layouts preferences page.
 */
struct API_LayoutsPrefs {

/**
 * @brief Color of master items on the layout.
 * @var masterColor
 */
	API_RGBColor					masterColor;

/**
 * @brief Use master items' own color.
 * @var useOwnMasterColor
 */
	bool							useOwnMasterColor;

/**
 * @brief When placing model views onto layouts, adjust each drawing frame to show only zoomed area of model view.
 * @var adjustDrawingFrameToViewZoom
 */
	bool							adjustDrawingFrameToViewZoom;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	char							filler[6];

};

/**
 * @brief The enumeration of the available preferences tab page types.
 * @enum API_PrefsTypeID
 * @ingroup ProjectSetting
 * @remarks Use this enum as a selector to the @ref ACAPI_ProjectSetting_GetPreferences function to get data of the different tab pages of the Preferences and the Work Environment dialog.
 */
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

/**
 * @brief Describes the supported Project Preferences to use with @ref ACAPI_Conversion_GetConvertedUnitValue.
 * @enum API_UnitConversionPrefID
 * @ingroup Conversion
 */
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

/**
 * @brief Input and output struct for @ref ACAPI_Conversion_GetConvertedUnitValue.
 * @struct API_UnitConversionData
 * @ingroup Conversion
 * @remarks Angles and imperial measured values can have several units, thus in these cases the unit is left empty, and the unit(s) are concatenated to convertedValue.
 */
struct API_UnitConversionData {

/**
 * @brief [in] Contains the value to convert. It should be in m/m²/m³/radian.
 * @var value
 */
	double							value;

/**
 * @brief [in] Specifies the Project Preference, which has to be used for conversion. For the supported values see @c API_UnitConversionPrefID.
 * @var unitConvPref
 */
	API_UnitConversionPrefID		unitConvPref;

/**
 * @brief [out] Contains the converted value, in the unit and rounding specified by the Project Preference.
 * @var convertedValue
 */
	GS::uchar_t						convertedValue[64];

/**
 * @brief [out] Contains the extra accuracy decimals, if any. It may be "1"&ndash;"99", "5", "25"/"5"/"75" or the empty string.
 * @var extraAccuracy
 */
	GS::uchar_t						extraAccuracy[4];

/**
 * @brief [out] Contains the unit of the converted value.
 * @var unit
 */
	GS::uchar_t						unit[64];

};


// =============================================================================
// Sun Settings
//
// =============================================================================

/**
 * @brief Parameters of the sunlight.
 * @struct API_SunInfo
 * @ingroup ProjectSetting
 * @remarks This structure is used when you get information about the sun. See the @ref ACAPI_GeoLocation_GetSunSets environment function.
 */
struct API_SunInfo {

/**
 * @brief Color of the directional light
 * @var sunRGB
 */
	API_RGBColor					sunRGB;

/**
 * @brief Color of the ambient light
 * @var ambientRGB
 */
	API_RGBColor					ambientRGB;

/**
 * @brief Intensity of the directional light [0..100]
 * @var sunIntensity
 */
	short							sunIntensity;

/**
 * @brief Intensity of the ambient light [0..100]
 * @var ambientIntensity
 */
	short							ambientIntensity;

/**
 * @brief Contribution to ambient [0..100]
 * @var sunToAmbient
 */
	short							sunToAmbient;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

};


// =============================================================================
// Location and Date
//
// =============================================================================

/**
 * @brief typedef enum { APINorthUnit_DecimalDegree, @c APINorthUnit_DegreeMinSec } @ref API_NorthUnitID ;
 * @enum API_NorthUnitID
 * @ingroup GeoLocation
 */
typedef enum {
	APINorthUnit_DecimalDegree,
	APINorthUnit_DegreeMinSec

} API_NorthUnitID;

/**
 * @brief typedef enum { APIAltitudeUnit_Meter, @c APIAltitudeUnit_DecFoot } @ref API_AltitudeUnitID ;
 * @enum API_AltitudeUnitID
 * @ingroup GeoLocation
 */
typedef enum {
	APIAltitudeUnit_Meter,
	APIAltitudeUnit_DecFoot

} API_AltitudeUnitID;

/**
 * @brief enum class API_LongLatUnitID { @c APILongLatUnit_DecimalDegree, @c APILongLatUnit_DegreeMinSec } ;
 * @enum API_LongLatUnitID
 * @ingroup GeoLocation
 * @since Archicad 26
 */
enum class API_LongLatUnitID {
	APILongLatUnit_DecimalDegree,
	APILongLatUnit_DegreeMinSec

};

/**
 * @brief The current location, date and sun parameters.
 * @struct API_PlaceInfo
 * @ingroup GeoLocation
 * @since Archicad 26
 * @remarks This structure is used to hold the consistent location, date and sun parameters.
 * 			It can be used either to retrieve the current parameter set (see the @ref ACAPI_GeoLocation_GetPlaceSets function);
 * 			or to calculate the sun angles in a given place at a given time (see the @ref ACAPI_GeoLocation_CalcSunOnPlace function);
 * 			or to set/change and the current parameter set (see @ref ACAPI_GeoLocation_ChangePlaceSets function).
 */
struct API_PlaceInfo {

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	short							filler_0;

/**
 * @brief true if daylight saving time is in effect
 * @var sumTime
 */
	bool							sumTime;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1;

/**
 * @brief The year at the given place.
 * @var year
 */
	unsigned short					year;

/**
 * @brief The month at the given place.
 * @var month
 */
	unsigned short					month;

/**
 * @brief The day at the given place.
 * @var day
 */
	unsigned short					day;

/**
 * @brief The hour at the given place.
 * @var hour
 */
	unsigned short					hour;

/**
 * @brief The minute at the given place.
 * @var minute
 */
	unsigned short					minute;

/**
 * @brief The second at the given place.
 * @var second
 */
	unsigned short					second;

/**
 * @brief longitude in degrees
 * @var longitude
 */
	double							longitude;

/**
 * @brief latitude in degrees
 * @var latitude
 */
	double							latitude;

/**
 * @brief altitude in meters
 * @var altitude
 */
	double							altitude;

/**
 * @brief North direction in radians.
 * @var north
 */
	double							north;

/**
 * @brief Sun position component in radians.
 * @var sunAngXY
 */
	double							sunAngXY;

/**
 * @brief Sun position component in radians.
 * @var sunAngZ
 */
	double							sunAngZ;

/**
 * @brief angle unit of north direction. See also: @c API_NorthUnitID
 * @var northUnit
 */
	API_NorthUnitID					northUnit;

/**
 * @brief display @c altitude in meters or feet. See also: @c API_AltitudeUnitID
 * @var altitudeUnit
 */
	API_AltitudeUnitID				altitudeUnit;

/**
 * @brief display @c latLongUnit in decimal degrees or degrees, minutes and seconds. See also: @c API_LongLatUnitID
 * @var longLatUnit
 */
	API_LongLatUnitID				longLatUnit;

/**
 * @brief Time zone in minutes from Greenwich.
 * @var timeZoneInMinutes
 */
	short							timeZoneInMinutes;

/**
 * @brief Used when different timezones have the same @c timeZoneInMinutes.
 * @var timeZoneOffset
 */
	short							timeZoneOffset;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3[2];

};

/**
 * @brief Coordinate Reference System and Map Conversion parameters of the Geo Location of the project.
 * @struct API_GeoReferenceData
 * @ingroup GeoLocation
 * @since Archicad 25
 * @remarks This structure is a member of @ref API_GeoLocation.
 * 			These Geo Referencing map parameters correspond to the `IfcCoordinateReferenceSystem` and `IfcMapConversion` entities of the IFC standard.
 */
struct API_GeoReferenceData {

/**
 * @brief Name by which the coordinate reference system is identified.
 * @var name
 */
	GS::UniString					name;

/**
 * @brief Informal description of this coordinate reference system.
 * @var description
 */
	GS::UniString					description;

/**
 * @brief Name by which this datum is identified.
 * @var geodeticDatum
 */
	GS::UniString					geodeticDatum;

/**
 * @brief Name by which the vertical datum is identified.
 * @var verticalDatum
 */
	GS::UniString					verticalDatum;

/**
 * @brief Name by which the map projection is identified.
 * @var mapProjection
 */
	GS::UniString					mapProjection;

/**
 * @brief Name by which the map zone, relating to the MapProjection, is identified.
 * @var mapZone
 */
	GS::UniString					mapZone;

/**
 * @brief Location along the easting of the coordinate system of the target map coordinate reference system.
 * @var eastings
 */
	double							eastings;

/**
 * @brief Location along the northing of the coordinate system of the target map coordinate reference system.
 * @var northings
 */
	double							northings;

/**
 * @brief Orthogonal height relative to the vertical datum specified.
 * @var orthogonalHeight
 */
	double							orthogonalHeight;

/**
 * @brief Value along the easting axis of the end point of a vector indicating the position of the local x axis of the engineering coordinate reference system.
 * @var xAxisAbscissa
 */
	double							xAxisAbscissa;

/**
 * @brief Value along the northing axis of the end point of a vector indicating the position of the local x axis of the engineering coordinate reference system.
 * @var xAxisOrdinate
 */
	double							xAxisOrdinate;

/**
 * @brief Scale to be used, when the units of the CRS are not identical to the units of the engineering coordinate system.
 * @var scale
 */
	double							scale;

};

/**
 * @brief Geo Location data of the project.
 * @struct API_GeoLocation
 * @ingroup GeoLocation
 * @since Archicad 25
 * @remarks This structure holds the parameters of the Geo Location settings of the project, such as geographic location, survey point position, and reference map conversion parameters.
 * 			In Teamwork you can retrieve the guid of this lockable object by using the "GeoLocation" identifier as the parameter of the @ref ACAPI_Teamwork_FindLockableObjectSet function.
 */
struct API_GeoLocation {

/**
 * @brief Project Location settings.
 * @var placeInfo
 */
	API_PlaceInfo					placeInfo;

/**
 * @brief Position of the Survey Point in the project.
 * @var surveyPointPosition
 */
	API_Coord3D						surveyPointPosition;

/**
 * @brief Coordinate Reference System and Map Conversion data.
 * @var geoReferenceData
 */
	API_GeoReferenceData			geoReferenceData;

};


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

/**
 * @brief Curve tracing parameters.
 * @struct API_MagicWandInfo
 * @ingroup UserInput
 * @remarks This structure corresponds to the "Magic Wand Settings..." dialog of Archicad. Follow the actual settings in the case yo need to trace curves with linear segments.
 * 			Refer to the @ref ACAPI_UserInput_GetMagicWandSets function to get the current settings.
 */
struct API_MagicWandInfo {

/**
 * @brief Mode of the approximating curves with linear segments. Possible values are:
 * @var divArcMode
 */
	short							divArcMode;

/**
 * @brief Trace method mode. Possible values are:
 * @var traceMethod
 */
	short							traceMethod;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;


/**
 * @brief The deviation from curves less than
 * @var arcSegNumb
 */
	short							arcSegNumb;

/**
 * @brief Number of the segment along arc/circles
 * @var arcDiff
 */
	double							arcDiff;

/**
 * @brief Segment length
 * @var partLength
 */
	double							partLength;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[8];

};


// =============================================================================
// 3D Projection settings
//
// =============================================================================

/**
 * @brief 3D projection setting parameters.
 * @struct API_3DProjectionInfo
 * @ingroup View
 * @remarks This structure corresponds to the "3D Projection Settings..." dialog of Archicad.
 * 			The isPersp field determines whether perspective or a parallel view is set. Refer to the @ref API_PerspPars or @ref API_AxonoPars structures to get the right projection parameters, respectively.
 * 			Refer to the @ref ACAPI_View_Get3DProjectionSets and @ref ACAPI_View_Change3DProjectionSets functions to get the current settings.
 */
struct API_3DProjectionInfo {

/**
 * @brief Perspective or parallel projection settings
 * @var isPersp
 */
	bool							isPersp;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	char							filler_1[7];

/**
 * @brief Guid of the camera; if specified from a floorplan camera element
 * @var camGuid
 */
	API_Guid						camGuid;

/**
 * @brief Guid of the camera set; if specified from a floorplan camera element
 * @var actCamSet
 */
	API_Guid						actCamSet;

/**
 * @brief Perspective or parallel project settings.
 * @var u
 */
	union {

/**
 * @brief Perspective settings
 * @var persp
 */
		API_PerspPars				persp;

/**
 * @brief Parallel projection settings
 * @var axono
 */
		API_AxonoPars				axono;

	} u;
};


// =============================================================================
// Rendering Settings
//
// =============================================================================

/**
 * @brief The representation of the Rendering Settings / Effects tab page.
 * @struct API_RendEffects
 * @ingroup Rendering
 * @remarks This structure is used by the @ref ACAPI_Rendering_GetRenderingSets and @ref ACAPI_Rendering_ChangeRenderingSets functions to get and modify the Effects "Rendering Settings" tab page.
 * 			See an example of using this structure at the description of @ref ACAPI_Rendering_ChangeRenderingSets.
 */
struct API_RendEffects {

/**
 * @brief The module ID of the rendering engine.
 * @var rendererID
 */
	API_ModulID						rendererID;

/**
 * @brief Use alpha channel for transparency
 * @var useBkgAlpha
 */
	bool							useBkgAlpha;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[7];

};


/**
 * @brief The representation of the Rendering Settings / Size Background tab page.
 * @ingroup Rendering
 * @struct API_RendImage
 * @remarks This structure is used by the @ref ACAPI_Rendering_GetRenderingSets and @ref ACAPI_Rendering_ChangeRenderingSets
 * 			functions to get and modify the Size and Background "Rendering Settings" tab page.
 * 			See an example of using this structure at the description of @ref ACAPI_Rendering_ChangeRenderingSets.
 */
struct API_RendImage {

/**
 * @brief Horizontal pixel size
 * @var hSize
 */
	short							hSize;

/**
 * @brief Vertical pixel size
 * @var vSize
 */
	short							vSize;

/**
 * @brief Dots per inch resolution
 * @var outResolution
 */
	short							outResolution;

/**
 * @brief Proportional change for hSize/vSize.
 * @var proportional
 */
	bool							proportional;


/**
 * @brief Colors or picture background.
 * @var bkgPict
 */
	bool							bkgPict;

/**
 * @brief Sky color
 * @var bkgSkyRGB
 */
	API_RGBColor					bkgSkyRGB;

/**
 * @brief Earth color
 * @var bkgEarthRGB
 */
	API_RGBColor					bkgEarthRGB;

/**
 * @brief Background picture rectangle
 * @var bkgPictRect
 */
	API_Rect						bkgPictRect;

/**
 * @brief Background picture file
 * @var bkgPictFile
 */
	IO::Location*					bkgPictFile;

/**
 * @brief Background resolution
 * @var bkgResolution
 */
	short							bkgResolution;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1;


/**
 * @brief Photorender only a part of the whole image. The rectangular shape is defined by the @c partialRect field
 * @var partialRendering
 */
	bool							partialRendering;

/**
 * @brief Rectangle for partial photorendering; valid only if the @c partialRendering field is @c true. The position of the rectangle is relative to the left-top corner of the whole image
 * @var partialRect
 */
	API_Rect						partialRect;


/**
 * @brief its value can be 0 (ScaleType_ToFill), or 1 (ScaleType_ToFit)
 * @var scaleType
 */
	short							scaleType;

/**
 * @brief its value can be 0 (BKGScaleType_ToFit), 1 (BKGScaleType_ToFill), or 2 (BKGScaleType_Custom)
 * @var bkgScaleType
 * @image html API_RendImage_bkgScaleType.png width=50%
 */
	short							bkgScaleType;


/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[13];

};


/**
 * @brief The enumeration of the available photorendering tab page types.
 * @enum API_RendSetTypeID
 * @ingroup Rendering
 * @remarks Use this enum as a selector to the @ref ACAPI_Rendering_GetRenderingSets and @ref ACAPI_Rendering_ChangeRenderingSets environment functions to get data of the different tab pages of the "Rendering Settings..." dialog.
 */
typedef enum {
	APIRendSet_EffectsID,
	APIRendSet_ImageID

} API_RendSetTypeID;


// =============================================================================
// 3D Image Info
//
// =============================================================================

/**
 * @brief The enumeration of the available 3D filter modes.
 * @enum API_3DFilterModeID
 * @ingroup View
 * @remarks Use this enum in @ref API_3DFilterAndCutSettings structure.
 */
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

/**
 * @brief Defines the filter for 3D filter and cut settings.
 * @struct API_MarqueeFilter
 * @ingroup Selection
 */
struct API_MarqueeFilter {
	/**
	 * @brief ConvertElemsInMarquee: convert what's in the marquee rectangle. \n ConvertElemsOutsideMarquee: convert what's outside the marquee rectangle.
	 * @var elemsInMarquee
	 */
	API_MarqueeConversionFilter		elemsInMarquee;
	/**
	 * @brief Trim to marquee.
	 * @var trimToMarquee
	 */
	bool							trimToMarquee;
	/**
	 * @brief The story for the single-story marquee rectangle.
	 * @var marqueeStory
	 */
	short							marqueeStory;
	/**
	 * @brief It can be a single story (SingleStory) or an all story (MultiStory) marquee rectangle.
	 * @var marqueeType
	 */
	API_MarqueeType					marqueeType;
};


/**
 * @brief Parameters of the 'Filter and Cut Elements in 3D' dialog.
 * @struct API_3DFilterAndCutSettings
 * @ingroup View
 * @since Archicad 26
 * @remarks This structure is used to retrieve and modify the data of the 3D image item settings by the @ref ACAPI_View_Get3DImageSets and @ref ACAPI_View_Change3DImageSets environment functions. Note that the visibility of GDL-based elements can also be modified through GDL parmeters which can overwrite the visibility settings in @ref API_3DFilterAndCutSettings.
 */
struct API_3DFilterAndCutSettings {

/**
 * @brief First story to convert. Valid only if @c allStories is @c false
 * @var firstStory3D
 */
	short							firstStory3D;

/**
 * @brief Last story to convert. Valid only if @c allStories is @c false
 * @var lastStory3D
 */
	short							lastStory3D;

/**
 * @brief Create a 3D projection of all stories rather than a range of stories defined by @c firstStory3D.. @c lastStory3D
 * @var allStories
 */
	bool							allStories;

/**
 * @brief Image only the elements that are within or outside the marquee area defined in the floor plan
 * @var marqueeFilter
 */
	API_MarqueeFilter				marqueeFilter;

/**
 * @brief Trims elements to the story range (see the `Trim Elements to story range` checkbox in the "Filter and Cut Elements in 3D" dialog.
 * @var trimToStoryRange
 */
	bool							trimToStoryRange;

/**
 * @brief The 3D filter mode. For available modes see @c API_3DFilterModeID enumeration. (output only)
 * @var filterMode
 */
	API_3DFilterModeID				filterMode;

/**
 * @brief A map containig @ref API_ElemTypeID pairs. @ref ACAPI_View_Change3DImageSets function will set element types with @c false value invisible on 3D and element types with @c true value visible. @c API_ZombieElemID will change the visibility of all element types regardless of other passed element types.
 * @var elemTypeFilter
 */
	std::map<API_ElemTypeID, bool>	elemTypeFilter;

};


// =============================================================================
// 3D Window Settings
//
// =============================================================================

/**
 * @brief Model image type in the 3D window.
 * @enum API_3DModelTypeID
 * @ingroup View
 * @remarks The @ref API_3DModelTypeID type is used in the @ref API_3DWindowInfo structure.
 */
typedef enum {
	API3DModel_Block = 0,
	API3DModel_WireFrame,
	API3DModel_Hiddenline,
	API3DModel_Shading

} API_3DModelTypeID;

/**
 * @brief Contour visibility options for shaded image mode in the 3D window.
 * @enum API_ShadingContoursID
 * @ingroup View
 * @remarks The @ref API_ShadingContoursID type is used in the @ref API_3DWindowInfo structure.
 */
typedef enum {
	APIShadContours_Draft = 0,
	APIShadContours_Off,
	APIShadContours_Best

} API_ShadingContoursID;

/**
 * @brief Options for vectorial sun shadow generation in the 3D window.
 * @enum API_VectorShadowID
 * @ingroup View
 * @remarks The @ref API_VectorShadowID type is used in the @ref API_3DWindowInfo structure. The elevation of the horizontal plane for shadow generaion on a single level is given in the shadowElevation field of @ref API_3DWindowInfo.
 */
typedef enum {
	APIVectShad_Off = 0,										// no vectorial sun shadows
	APIVectShad_ContOff_AllSurf,								// contours OFF * On all surfaces
	APIVectShad_ContOn_AllSurf,									// contours ON  * On all surfaces
	APIVectShad_ContOff_OneLevel,								// contours OFF * On a single level
	APIVectShad_ContOn_OneLevel									// contours ON  * On a single level

} API_VectorShadowID;

/**
 * @brief 3D Window setting parameters.
 * @struct API_3DWindowInfo
 * @ingroup View
 * @remarks The @ref API_3DWindowInfo structure is used by the @ref ACAPI_View_Get3DWindowSets and the @ref ACAPI_View_Change3DWindowSets environment functions. &nbsp;With API ver. 21, the parameters and functionality regarding 3D drawing options and colors was moved to the @ref API_3DStyle structure and related functions.
 */
struct API_3DWindowInfo {

/**
 * @brief Resize the 3D window according to the @c hSize and @c vSize fields
 * @var setWindowSize
 */
	bool							setWindowSize;

/**
 * @brief Horizontal size of the 3D window in pixels
 * @var hSize
 */
	short							hSize;

/**
 * @brief Vertical size of the 3D window in pixels
 * @var vSize
 */
	short							vSize;


/**
 * @brief Modify the projection zoom data according to the @c zoomScaleX, @c zoomScaleY, @c zoomDispX and @c zoomDispY fields
 * @var setZoom
 */
	bool							setZoom;

/**
 * @brief Horizontal scale factor of the projection (ignored if @c setZoom is @c false)
 * @var zoomScaleX
 */
	double							zoomScaleX;

/**
 * @brief Vertical scale factor of the projection (ignored if @c setZoom is @c false)
 * @var zoomScaleY
 */
	double							zoomScaleY;

/**
 * @brief Horizontal offset of the projection (ignored if @c setZoom is @c false)
 * @var zoomDispX
 */
	double							zoomDispX;

/**
 * @brief Vertical offset of the projection (ignored if @c setZoom is @c false)
 * @var zoomDispY
 */
	double							zoomDispY;

};

/**
 * @brief 3D Style parameters.
 * @struct API_3DStyle
 * @ingroup View
 * @remarks The @ref API_3DStyle structure is used by the @ref ACAPI_View_Get3DStyleList, the @ref ACAPI_View_Get3DStyle and the @ref ACAPI_View_Change3DStyle environment functions. Changing active style can be done using the @ref ACAPI_View_SetCurrent3DStyle function.
 * 			Changing the active style can be done using the @ref ACAPI_View_SetCurrent3DStyle function.
 * 			The range of values for all kinds of line thicknesses is `[1..10]`.
 * 			The following settings are ignored using the OpenGL engine: `vectHatchOn`, `silhouetteThickness`, `vectorialHatchingThickness`, `shadowContourThickness`, `castShadowPercent`, `shadingPercent`.
 */
struct API_3DStyle {
/**
 * @brief The name of 3D Style. Must be unique within the project.
 * @var name
 */
	GS::uchar_t						name[API_UniLongNameLen];

	/*GENERAL*/

/**
 * @brief ID of 3D Rendering Engine
 * @var engineId
 */
	Int32							engineId;

/**
 * @brief Image type of the 3D model (Block, Wireframe, Hidden Line, Shading)
 * @var model3D
 */
	API_3DModelTypeID				model3D;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1[2];

/**
 * @brief Transparency in shading is in effect or not
 * @var transparency
 */
	bool							transparency;

/**
 * @brief Monochrome rendering mode, using one uniform color for all surfaces and another one for all contours.
 * @var monochromeEnabled
 */
	bool							monochromeEnabled;

/**
 * @brief Color of all surfaces (ignored if @c monochromeEnabled is @c false)
 * @var monochromeSurfaceRGB
 */
	API_RGBColor					monochromeSurfaceRGB;

/**
 * @brief Color of all contours (ignored if @c monochromeEnabled is @c false)
 * @var monochromeContourRGB
 */
	API_RGBColor					monochromeContourRGB;

	/*BACKGROUND*/

/**
 * @brief Use the background specified previously in Photorendering Settings
 * @var bkgAsInRendering
 */
	bool							bkgAsInRendering;

/**
 * @brief Link sky and ground colors
 * @var chainBkgColors
 */
	bool							chainBkgColors;

/**
 * @brief Background sky color (ignored if @c bkgAsInRendering is @c true)
 * @var bkgSkyColor
 */
	API_RGBColor					bkgSkyColor;

/**
 * @brief Background ground color (ignored if @c bkgAsInRendering is @c true)
 * @var backGroundRGB
 */
	API_RGBColor					backGroundRGB;

	/*CONTOURS*/

/**
 * @brief Contour visibility options for shaded image mode
 * @var shadCont
 */
	API_ShadingContoursID			shadCont;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[4];

/**
 * @brief Vectorial sun shadow generation options
 * @var vectSunShadow
 */
	API_VectorShadowID				vectSunShadow;

/**
 * @brief Vectorial hatch patterns are used in analytic shaded mode
 * @var vectHatchOn
 */
	bool							vectHatchOn;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	bool							filler_3;

/**
 * @brief Thickness of contour lines in pixels
 * @var contourThickness
 */
	short							contourThickness;

/**
 * @brief Thickness of silhouette lines in pixels
 * @var silhouetteThickness
 */
	short							silhouetteThickness;

/**
 * @brief Thickness of vectorial hatching lines in pixels
 * @var vectorialHatchingThickness
 */
	short							vectorialHatchingThickness;

/**
 * @brief Thickness of shadow contour lines in pixels
 * @var shadowContourThickness
 */
	short							shadowContourThickness;

	/*SHADOWS*/

/**
 * @brief Intensity of cast shadows
 * @var castShadowPercent
 */
	short							castShadowPercent;

/**
 * @brief Intensity of shades
 * @var shadingPercent
 */
	short							shadingPercent;

/**
 * @brief The absolute elevation of the horizontal plane on which the vectorial shadows will be generated. Valid only if @c vectSunShadow is either @c APIVectShad_ContOff_OneLevel or @c APIVectShad_ContOn_OneLevel
 * @var shadowElevation
 */
	double							shadowElevation;

	/*HOTSPOTS*/

/**
 * @brief Display also 2D hotspots in the 3D window
 * @var show3DHotSpotsOnly
 */
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

/**
 * @brief Shape of the 3D cutting plane.
 * @struct API_3DCutShapeType
 * @ingroup View
 * @remarks This structure is a member of @ref API_3DCutPlanesInfo.
 */
struct API_3DCutShapeType {

/**
 * @brief Reserved for internal use
 * @var cutStatus
 */
	short							cutStatus;

/**
 * @brief Pen of the cutplane
 * @var cutPen
 */
	short							cutPen;

/**
 * @brief Material of the cutplane
 * @var cutMater
 */
	API_AttributeIndex				cutMater;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief Horizontal coordinate of the begin of the section line
 * @var pa
 */
	double							pa;

/**
 * @brief Vertical coordinate of the begin of the section line
 * @var pb
 */
	double							pb;

/**
 * @brief Horizontal coordinate of the end of the section line
 * @var pc
 */
	double							pc;

/**
 * @brief Vertical coordinate of the end of the section line
 * @var pd
 */
	double							pd;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	double							filler_2[5];

};


/**
 * @brief Data of the "3D Cutting Planes..." dialog.
 * @struct API_3DCutPlanesInfo
 * @ingroup View
 * @remarks The @ref API_3DCutPlanesInfo structure is used by the @ref ACAPI_View_Get3DCuttingPlanes and the @ref ACAPI_View_Change3DCuttingPlanes environment functions.
 * 			Don't forget to dispose of the `shapes` handle when it is not needed anymore.
 */
struct API_3DCutPlanesInfo {

/**
 * @brief 3D cutaway on
 * @var isCutPlanes
 */
	bool							isCutPlanes;

/**
 * @brief Custom edges and surfaces of elements cut in 3D Sections
 * @var useCustom
 */
	bool							useCustom;

/**
 * @brief Custom pen
 * @var customPen
 */
	short							customPen;

/**
 * @brief Custom material
 * @var customMater
 */
	API_AttributeIndex				customMater;

/**
 * @brief Number of the shapes
 * @var nShapes
 */
	short							nShapes;

/**
 * @brief Shapes of the cutting planes
 * @var shapes
 */
	API_3DCutShapeType**			shapes;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[9];

};


// =============================================================================
// Application/Printer/Plotter Info
//
// =============================================================================

/**
 * @brief Miscellaneous information of the application
 * @struct API_MiscAppInfo
 * @ingroup ProjectOperation
 * @remarks This structure contains version string and main window's caption of application.
 * 			Call the @ref ACAPI_ProjectOperation_GetMiscAppInfo function to get this data.
 */
struct API_MiscAppInfo {

/**
 * @brief Version string of the application.
 * @var version
 */
	char							version [256];

/**
 * @brief Caption of the application's main window.
 * @var caption
 */
	char							caption [256];

};


/**
 * @brief Miscellaneous information of the selected printer
 * @struct API_MiscPrinterInfo
 * @ingroup ProjectOperation
 * @remarks This structure contains name and orientation of selected printer in Archicad.
 * 			Call the @ref ACAPI_ProjectOperation_GetMiscPrinterInfo function to get this data.
 */
struct API_MiscPrinterInfo {

/**
 * @brief Name of the selected printer.
 * @var name
 */
	char							name [256];

/**
 * @brief Currently selected orientation: portrait (true) or landscape (false).
 * @var orientPortrait
 */
	bool							orientPortrait;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	char							filler [7];

};


#define API_DrvNameLen				32							// maximum length of a driver name

/**
 * @brief Miscellaneous information of the selected plotter
 * @struct API_MiscPlotterInfo
 * @ingroup ProjectOperation
 * @remarks This structure contains name and model of selected plotter in Archicad.
 * 			Call the @ref ACAPI_ProjectOperation_GetMiscPlotterInfo function to get this data.
 */
struct API_MiscPlotterInfo {

/**
 * @brief Name of the selected plotter.
 * @var name
 */
	char							name  [API_DrvNameLen];

/**
 * @brief Model of the selected plotter.
 * @var model
 */
	char							model [API_DrvNameLen];

};


// =============================================================================
// Special Folders
//
// =============================================================================

/**
 * @brief The selector of special folders.
 * @enum API_SpecFolderID
 * @ingroup View
 */
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

/**
 * @brief Properties of an Archicad Layout.
 * @struct API_LayoutInfo
 * @ingroup Navigator
 * @remarks You can retrieve and modify the properties of a layout with the @ref ACAPI_Navigator_GetLayoutSets
 * 			and @ref ACAPI_Navigator_ChangeLayoutSets environment functions, respectively.
 * 			Note that the paper size and margins are expressed in **mm**s, not in meters, and these parameters always apply
 * 			to master layouts.
 * @image html layout_id.png "Layout ID assigment tab page" width=50%
 * 		  Do not forget do delete the `customData` pointer after calling @ref ACAPI_Navigator_GetLayoutSets.
 */
struct API_LayoutInfo {

/**
 * @brief The name of the layout as a Unicode string.
 * @var layoutName
 */
	GS::uchar_t								layoutName[API_UniLongNameLen];

/**
 * @brief Horizontal size of the layout in mm.
 * @var sizeX
 */
	double									sizeX;

/**
 * @brief Vertical size of the layout in mm.
 * @var sizeY
 */
	double									sizeY;

/**
 * @brief Layout margin to the left side of the paper.
 * @var leftMargin
 */
	double									leftMargin;

/**
 * @brief Layout margin to the top side of the paper.
 * @var topMargin
 */
	double									topMargin;

/**
 * @brief Layout margin to the right side of the paper.
 * @var rightMargin
 */
	double									rightMargin;

/**
 * @brief Layout margin to the bottom side of the paper.
 * @var bottomMargin
 */
	double									bottomMargin;

/**
 * @brief Corresponds to the Custom ID field on the Layout ID assignment tab page in the Layout Settings dialog (see picture below).
 * @var customLayoutNumber
 */
	char									customLayoutNumber[256];

/**
 * @brief Corresponds to the Use Automatic Book and Subset ID numbering / Custom ID radio buttons on the Layout ID assignment tab page in the Layout Settings dialog (see picture below).
 * @var customLayoutNumbering
 */
	bool									customLayoutNumbering;

/**
 * @brief Corresponds to state of the Do not include this Layout in ID sequence check box on the Layout ID assignment tab page in the Layout Settings dialog (see picture below).
 * @var doNotIncludeInNumbering
 */
	bool									doNotIncludeInNumbering;

/**
 * @brief Display master layout above or below the layout.
 * @var showMasterBelow
 */
	bool									showMasterBelow;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool									filler_1[5];

/**
 * @brief Number of layout (page) when this layout contains any MultiPage Drawing. (Drawing with "Split to more layouts" flag.)
 * @var layoutPageNumber
 */
	UInt32									layoutPageNumber;

/**
 * @brief The actual index of layout (page) inside the Multi Page Layout. (Layout what contains any drawing with "Split to more layouts" flag.)
 * @var actPageIndex
 */
	UInt32									actPageIndex;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	double									filler_2[2];

/**
 * @brief Contains the custom data fields. The custom scheme GUID-value pairs are stored in a GS::HashTable.
 * @var customData
 */
	GS::HashTable<API_Guid, GS::UniString>* customData;

/**
 * @brief ID of the current document revision of the layout.
 * @var currentRevisionId
 */
	GS::uchar_t								currentRevisionId[API_UniLongNameLen];

/**
 * @brief EID with optional suffix (- WIP) of the current document revision of the layout.
 * @var currentFinalRevisionId
 */
	GS::uchar_t								currentFinalRevisionId[API_UniLongNameLen];

/**
 * @brief One or more issued document revisions have already been created for the layout.
 * @var hasIssuedRevision
 */
	bool									hasIssuedRevision;

/**
 * @brief Exists an opened document revision for the layout.
 * @var hasActualRevision
 */
	bool									hasActualRevision;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	bool									filler_3[6];

};


// =============================================================================
// Numbering Grid Lines
// =============================================================================

/**
 * @brief Represents a drawing numbering grid line of the layout.
 * @ingroup Drawing
 * @struct API_NumberingGridLine
 * @remarks This structure holds the data of a line of the grid-based drawing numbering system. The stucture is passed as a parameter of the APINumberingGridLineProc callback function while the drawing numbering grid lines are being enumerated by the @ref ACAPI_Drawing_GetNumberingGridLines environment function.
 */
struct API_NumberingGridLine {

/**
 * @brief Coordinate of the starting point
 * @var begC
 */
	API_Coord						begC;

/**
 * @brief Coordinate of the endpoint
 * @var endC
 */
	API_Coord						endC;

/**
 * @brief Pen attribute index
 * @var penInd
 */
	short							penInd;

/**
 * @brief Line type attribute index
 * @var ltypeInd
 */
	API_AttributeIndex				ltypeInd;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1[7];

};

// =============================================================================
// API_DocumentFrom3DDefaults
//
// =============================================================================


/**
 * @brief How to display the cut surfaces.
 * @enum API_3DCutSurfFills
 * @ingroup View
 */
typedef enum {
	API_3DDocumentVectorFilles		= 1,
	API_3DDocumentUniformMaterial	= 2,
	API_3DDocumentOwnMaterial		= 3,
	API_3DDocumentOwnShadedMaterial	= 4

} API_3DCutSurfFills;


/**
 * @brief How to display the uncut surfaces.
 * @enum API_3DUncutSurfaceFillType
 * @ingroup View
 */
typedef enum {
	API_3DDocumentPenColor				 = 1,
	API_3DDocumentMaterialColorShaded	 = 2,
	API_3DDocumentMaterialColorNonShaded = 3
} API_3DUncutSurfaceFillType;


/**
 * @brief Show or hide hidden edges.
 * @enum API_3DHiddenEdgeVisibility
 * @ingroup View
 */
typedef enum {
	API_3DDocumentHideHiddenEdges,
	API_3DDocumentShowHiddenEdges
} API_3DHiddenEdgeVisibility;


/**
 * @brief Show or hide hidden cut lines.
 * @enum API_3DOnCutPlaneVisibility
 * @ingroup View
 */
typedef enum {
	API_3DDocumentDontShowOnCutPlanes,
	API_3DDocumentShowOnCutPlanes
} API_3DOnCutPlaneVisibility;


/**
 * @brief General representation of a Model Display in 3D Document.
 * @struct API_UniformAttributeOptions
 * @ingroup View
 * @remarks You are able to get and change the default settings of 3D document via @ref ACAPI_View_GetDocumentFrom3DDefaults and @ref ACAPI_View_ChangeDocumentFrom3DDefaults functions. @ref ACAPI_View_GetDocumentFrom3DSettings and @ref ACAPI_View_ChangeDocumentFrom3DSettings function retrieves and modifies the settings of an existing 3D document database.
 */
struct API_UniformAttributeOptions {

/**
 * @brief Use uniform cut attributes.
 * @var shouldUseUniformCutAttributes
 */
	bool							shouldUseUniformCutAttributes;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1;

/**
 * @brief Uniform line type index.
 * @var uniformLineType
 */
	short							uniformLineType;

/**
 * @brief Uniform fill index.
 * @var uniformFillPen
 */
	short							uniformFillPen;

/**
 * @brief Background color of the uniform fill.
 * @var uniformFillBkgPen
 */
	short							uniformFillBkgPen;

/**
 * @brief Use uncut surface fill.
 * @var shouldUseUncutSurfaceFill
 */
	bool							shouldUseUncutSurfaceFill;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool							filler_2[3];

/**
 * @brief How to display the cut surfaces.
 * @var fillCutSurfacesWith
 */
	API_3DCutSurfFills				fillCutSurfacesWith;

/**
 * @brief How to display the uncut surfaces.
 * @var uncutSurfaceFillType
 */
	API_3DUncutSurfaceFillType		uncutSurfaceFillType;

/**
 * @brief Background color of the uncut surface.
 * @var uncutSurfaceBkgPen
 */
	short							uncutSurfaceBkgPen;

/**
 * @brief Use elem pen.
 * @var shouldUseElemPen
 */
	bool							shouldUseElemPen;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	bool							filler_3;

/**
 * @brief Elem pen index.
 * @var elemPen
 */
	short							elemPen;

/**
 * @brief Shadow fill pen.
 * @var shadFillPen
 */
	short							shadFillPen;

/**
 * @brief Shadow fill index.
 * @var shadFill
 */
	API_AttributeIndex				shadFill;

/**
 * @brief Shadow fill background pen.
 * @var shadFillBkgPen
 */
	short							shadFillBkgPen;

/**
 * @brief Shadow contour pen.
 * @var shadContPen
 */
	short							shadContPen;

/**
 * @brief Show or hide hidden edges.
 * @var hiddenEdgeVisibility
 */
	API_3DHiddenEdgeVisibility		hiddenEdgeVisibility;

/**
 * @brief Hidden edge line type.
 * @var hiddenEdgeLineType
 */
	API_AttributeIndex				hiddenEdgeLineType;

/**
 * @brief Hidden edge line pen.
 * @var hiddenEdgeLinePen
 */
	short							hiddenEdgeLinePen;

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	short							filler_4;

/**
 * @brief Show or hide hidden cut lines.
 * @var onCutPlaneVisibility
 */
	API_3DOnCutPlaneVisibility		onCutPlaneVisibility;

/**
 * @brief Reserved for later use.
 * @var filler_5
 */
	short							filler_5[2];

};

/**
 * @brief 3D Document source.
 * @enum API_DocumentSourceID
 * @ingroup View
 */
typedef enum {
	API_DDD			= 1,
	API_FloorPlan	= 2

} API_DocumentSourceID;

/**
 * @brief Skeleton drawing 3D Document view source.
 * @enum API_ViewSourceID
 * @ingroup View
 */
typedef enum {
	API_Top			= 1,
	API_Bottom		= 2

} API_ViewSourceID;

/**
 * @brief Skeleton drawing options.
 * @struct API_SkeletonOptions
 * @ingroup View
 */
struct API_SkeletonOptions {

/**
 * @brief Skeleton view source.
 * @var viewSrc
 */
	API_ViewSourceID		viewSrc;

/**
 * @brief Skeleton source floor index.
 * @var floorIdx
 */
	short					floorIdx;

/**
 * @brief Cut height (on the source floor).
 * @var cutHeight
 */
	double					cutHeight;

/**
 * @brief Floor offset to the other cutplane.
 * @var floorOffset
 */
	short					floorOffset;

/**
 * @brief Cut height (on the " @c floorIdx + @c floorOffset " floor).
 * @var cutOffset
 */
	double					cutOffset;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	short					filler;

};

/**
 * @brief Default settings of 3D document.
 * @struct API_DocumentFrom3DDefaults
 * @ingroup View
 * @remarks You are able to get and change the default settings of 3D document via @c ACAPI_View_GetDocumentFrom3DDefaults and @c ACAPI_View_ChangeDocumentFrom3DDefaults functions.
 */
struct API_DocumentFrom3DDefaults {

/**
 * @brief General representation of a Model Display.
 * @var attributeOptions
 */
	API_UniformAttributeOptions		attributeOptions;

/**
 * @brief The name of the database.
 * @var name
 */
	GS::uchar_t						name[API_UniLongNameLen];

/**
 * @brief Reference string / ID of the database.
 * @var refId
 */
	GS::uchar_t						refId[API_UniLongNameLen];

/**
 * @brief Vectorial 3D hatching option
 * @var vect3DHatching
 */
	bool							vect3DHatching;

/**
 * @brief Vectorial sun shadow generation options.
 * @var vectSunShadow
 */
	bool							vectSunShadow;

/**
 * @brief Transparent effect (see-through Materials e.g. glass).
 * @var mustBeTransparent
 */
	bool							mustBeTransparent;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1;

/**
 * @brief Intended plan connectivity. It could be different from the state of its window.
 * @var intPlanConn
 */
	API_CutPlanePlanConn			intPlanConn;

/**
 * @brief Use Material Defined in 3D Cutting Planes.
 * @var materialFrom3D
 */
	bool							materialFrom3D;

/**
 * @brief Vectorial sun shadow contour on(off).
 * @var contureOff
 */
	bool							contureOff;

/**
 * @brief Cut surface material.
 * @var cMater
 */
	API_AttributeIndex				cMater;

/**
 * @brief Skeleton drawing options.
 * @var skeletonOptions
 */
	API_SkeletonOptions				skeletonOptions;

/**
 * @brief Boundary display options
 * @var boundaryDisplay
 */
	API_BoundaryDisplay				boundaryDisplay;

/**
 * @brief Boundary pen (in case of overridden contours)
 * @var boundaryPen
 */
	short							boundaryPen;

/**
 * @brief Boundary line type (in case of overridden contours)
 * @var boundaryLineType
 */
	API_AttributeIndex				boundaryLineType;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	short							filler_2[3];

};

/**
 * @brief Represents a 3D Document.
 * @struct API_DocumentFrom3DType
 * @ingroup View
 * @since Archicad 26
 * @remarks This structure is used by the @c ACAPI_View_GetDocumentFrom3DSettings and the @c ACAPI_View_ChangeDocumentFrom3DSettings environment functions.
 */
struct API_DocumentFrom3DType {

/**
 * @brief Tells which elements should appear in the 3D document window. Corresponds to the Filter and Cut Settings dialog.
 * @var filterAndCutSettings
 */
	API_3DFilterAndCutSettings		filterAndCutSettings;

/**
 * @brief List of cut planes to apply
 * @var cutSetting
 */
	API_3DCutPlanesInfo				cutSetting;

/**
 * @brief Apply 3D cut away
 * @var cutaway3D
 */
	bool							cutaway3D;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[7];

/**
 * @brief Projection settings (camera position etc.)
 * @var projectionSetting
 */
	API_3DProjectionInfo			projectionSetting;

/**
 * @brief 2D floorplan origo offset (only in skeleton drawing).
 * @var floorPlanRotationOrigo
 */
	API_Coord						floorPlanRotationOrigo;

/**
 * @brief Appearance settings of the 3D window
 * @var window3DInfo
 */
	API_3DWindowInfo				window3DInfo;

/**
 * @brief Linetype index for hidden lines (obsolete).
 * @var hiddenLineType
 */
	API_AttributeIndex				hiddenLineType;

/**
 * @brief Line length for hidden lines (obsolete).
 * @var hiddenLineLen
 */
	short							hiddenLineLen;

/**
 * @brief Effects to apply
 * @var effects3D
 */
	short							effects3D;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	short							filler_2;

/**
 * @brief Rect
 * @var drawRect
 */
	API_Rect						drawRect;

/**
 * @brief List of uniform attributes if @c attributeOptions.shouldUseUniformCutAttributes is set
 * @var attributeOptions
 */
	API_UniformAttributeOptions		attributeOptions;

/**
 * @brief Current Plan connectivity
 * @var currPlanConn
 */
	API_CutPlanePlanConn			currPlanConn;

/**
 * @brief Intended Plan connectivity
 * @var intPlanConn
 */
	API_CutPlanePlanConn			intPlanConn;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	short							filler_3;

/**
 * @brief Use materials from the 3D window
 * @var materialFrom3D
 */
	bool							materialFrom3D;

/**
 * @brief 3D Document source.
 * @var docSrc
 */
	API_DocumentSourceID			docSrc;

/**
 * @brief Skeleton drawing options
 * @var skeletonOptions
 */
	API_SkeletonOptions				skeletonOptions;

/**
 * @brief Boundary display options
 * @var boundaryDisplay
 */
	API_BoundaryDisplay				boundaryDisplay;

/**
 * @brief Boundary pen (in case of overridden contours)
 * @var boundaryPen
 */
	short							boundaryPen;

/**
 * @brief Boundary line type (in case of overridden contours)
 * @var boundaryLineType
 */
	API_AttributeIndex				boundaryLineType;

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	bool							filler_4[4];

/**
 * @brief Enable transparent surfaces in 3D window
 * @var transparency
 */
	bool							transparency;

};


// =============================================================================
// Font
//
// =============================================================================
/**
 * @brief Contains common information related to API_FontType.
 * @struct API_Font_Head
 * @ingroup Font
 * @remarks This structure contains general information about a font.
 * 			As a general rule, before calling any of the applicable functions, clear the whole structure, fill the necessary fields, then call the function. Clearing all fields in the structure is important for future compatibility; in the next API releases the fillers may have meanings.
 * 			You can access long name in C string format (name) or in GS::UniString format (uniStringNamePtr).
 * 			You can use UniString format for font operations to avoid loss of information due to character conversion. To achieve this set the pointer of a GS::UniString variable in the uniStringNamePtr field of the @ref API_ModelViewOptions_Head structure. Otherwise always set this field to nullptr.
 * 			You can identify fonts by name. If you want to refer to a font by name, set the index member to 0. If you set uniStringNamePtr to point to a valid GS::UniString object, the content of the name character buffer is ignored.
 */
struct API_Font_Head {
/**
 * @brief The index is the current index of the given font.
 * References to any font are done through these indices. It goes from 1 to the maximum available font index.
 * @var index
 */
	Int32			index;

/**
 * @brief specifies whether this is a vectorial font.
 * @var flags
 */
	short			flags;
	short			filler_0;

/**
 * @brief The name of the font as UTF-8 encoded C string, which appears in the appropriate dialogs.
 * @var name
 */
	char			name[API_UniLongNameLen];

/**
 * @brief Optional parameter for accessing the name of the font in @c UniString (UTF-16 encoded) format.
 * @var uniStringNamePtr
 */
	GS::UniString*	uniStringNamePtr;
};


/**
 * @brief Contains common information related to a font.
 * @struct API_FontType
 * @ingroup Font
 */
struct API_FontType {
/**
 * @brief Specifies the name and index of the font. The @c flags field in the header specifies whether this is a vectorial font.
 * @var head
 */
	API_Font_Head	head;

/**
 * @brief The character code used in the Unicode-ANSI string conversion routines of the @c GSRoot String Manager.
 * @var charCode
 */
	GSCharCode		charCode;

/**
 * @brief The ascent of the characters (the height above the baseline).
 * @var ascent
 */
	double			ascent;

/**
 * @brief The descent of the characters (the depth below the baseline).
 * @var descent
 */
	double			descent;

/**
 * @brief The maximum width of the characters in this font.
 * @var widMax
 */
	double			widMax;

/**
 * @brief The value of the external leading.
 * @var externalLeading
 */
	double			externalLeading;

/**
 * @brief Attribute ndex of the substitute font.
 * @var substituteInd
 */
	short			substituteInd;
	short			filler_1;
};


/**
 * @brief Pen attribute representation.
 * @struct API_Pen
 * @ingroup Attribute
 * @remarks This structure is used to manipulate pen attributes of the currently active Pen Table. Pens cannot be created or deleted; you can just modify them.
 * 			There is no additional data assigned to pen attributes in the @ref API_AttributeDef structure.
 *
 * 			The index of Pen attributes normally must be between 1 and 255, but there are some special values:
 * 			|Index|Meaning|
 * 			|--- |--- |
 * 			|`APIPen_Transparent` (= 0)|Transparent pen. Fill backgrounds having this pen index are drawn transparently.|
 * 			|`APIPen_WindowBackground` (= -1)|Background pen. Fill backgrounds having this pen index are drawn with the current window background color.|
 * 			|1000|Grid color pen. Pen index for drawing the grid|
 * 			|1001|Zone fill color. This is the foreground color of a zone's fill; coming from the zone category; use the rgb value of the pen|
 * 			|1002|Ghost Story color. Pen index used for drawing ghost story elements|
 * @sa API_Attr_Head,API_RGBColor, API_Attribute, Attribute Management
 */

#define APIPen_Transparent			0		/**< Transparent Pen Index (available only as a Fill background Pen) */
#define APIPen_WindowBackground	   -1		/**< Window Background Pen Index (available only as a Fill background Pen) */

struct API_Pen {
/**
 * @brief index of the pen. 1..255
 * @var index
 */
	short			index;

/**
 * @brief modification time of the pen.
 * @var modiTime
 */
	UInt64			modiTime;

/**
 * @brief Color of the pen.
 * @var rgb
 */
	API_RGBColor	rgb;

/**
 * @brief Thickness of the pen defined in paper millimeters.
 * @var width
 */
	double			width;

/**
 * @brief Textual description of the pen; doesn't have to be unique, and can be empty.
 * @var description
 */
	char			description[128];
};

// ---------------------------------------------------------------------------------------------------------------------

#endif
