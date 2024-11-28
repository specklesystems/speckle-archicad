// *********************************************************************************************************************
// API definitions - managing databases
//
// Module:			API
// Namespace:		-
// Contact person:	archicadapi@graphisoft.com
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APIDEFS_DATABASE_H)
#define	APIDEFS_DATABASE_H

#if defined (_MSC_VER)
#pragma once
#endif


// --- Includes	--------------------------------------------------------------------------------------------------------

// own
#include "API_Guid.hpp"
#include "APIdefs_Base.h"
#include "HashTable.hpp"
#include "Md5.hpp"
#include "Location.hpp"


// --- Compiler settings -----------------------------------------------------------------------------------------------


// --- Type definitions	------------------------------------------------------------------------------------------------


// =============================================================================
// Function codes and parameter descriptions
//
// =============================================================================

typedef enum {			// Codes for Database functions
	APIDb_GetCurrentWindowID				= 'GWIN',				// par1: API_WindowInfo*				par2: ---
	APIDb_ResetCurrentWindowID				= 'RWIN',				// par1: ---							par2: ---
	APIDb_NewWindowID						= 'NWIN',				// par1: API_NewWindowPars*				par2: APICustomWindowHandlerProc*
	APIDb_CloseWindowID						= 'CWIN',				// par1: API_WindowInfo*				par2: ---
	APIDb_GetOwnWindowsID					= 'GWID',				// par1: API_WindowTypeID*				par2: GS::Array<API_Guid>*

	APIDb_GetCurrentDatabaseID				= 'GDAT',				// par1: API_DatabaseInfo*				par2: ---
	APIDb_ResetCurrentDatabaseID			= 'RDAT',				// par1: ---							par2: ---
	APIDb_ChangeCurrentDatabaseID 			= 'CDAT',				// par1: API_DatabaseInfo*				par2: ---
	APIDb_RedrawCurrentDatabaseID 			= 'DRDB',				// par1: ---							par2: ---
	APIDb_RebuildCurrentDatabaseID 			= 'RBDB',				// par1: ---							par2: ---

	APIDb_NewDatabaseID						= 'NDAT',				// par1: API_DatabaseInfo*				par2: const GS::Guid*	(parent)			par3: const GS::Guid* (child)
	APIDb_ModifyDatabaseID					= 'MDAT',				// par1: API_DatabaseInfo*				par2: ---
	APIDb_DeleteDatabaseID					= 'DDAT',				// par1: API_DatabaseInfo*				par2: ---
	APIDb_GetDatabaseInfoID					= 'GDBI',				// par1: API_DatabaseInfo*				par2: ---

	APIDb_GetDBUnIdFromGuidID				= 'GODU',				// par1: API_Guid*						par2: short*					par3: UInt32*
	APIDb_GetGuidFromDBUnIdID				= 'GGOD',				// par1: short*							par2: UInt32*					par3: API_Guid*

	APIDb_GetDetailDatabasesID		 		= 'GDDI',				// par1: [API_DatabaseUnId**]			par2: [GS::Array<API_DatabaseUnId>*]
	APIDb_GetLayoutDatabasesID		 		= 'GLDI',				// par1: [API_DatabaseUnId**]			par2: [GS::Array<API_DatabaseUnId>*]
	APIDb_GetMasterLayoutDatabasesID		= 'GMDI',				// par1: [API_DatabaseUnId**]			par2: [GS::Array<API_DatabaseUnId>*]

	APIDb_AddTextWindowContentID			= 'ATEX',				// par1: API_WindowInfo*				par2: [const char*] (content)	par3: [const GS::UniString*] (uniContent)

	APIDb_CoordToPointID					= 'CTOP',				// par1: API_Coord*  					par2: API_Point*
	APIDb_PointToCoordID					= 'PTOC',				// par1: API_Point*  					par2: API_Coord*

	APIDb_GetDrawingScaleID					= 'GSCL',				// par1: double* (scale)				par2: ---
	APIDb_ChangeDrawingScaleID				= 'CDRS',				// par1: double* (scale)				par2: [bool*] (zoom)

	APIDb_GetGridSettingsID					= 'GGRI',				// par1: API_GridType*					par2: ---
	APIDb_ChangeGridSettingsID				= 'CGRI',				// par1: API_GridType*					par2: ---

	APIDb_SetZoomID							= 'SZOM',				// par1: [API_Box*]						par2: [API_Tranmat*]
	APIDb_GetZoomID							= 'GZOM',				// par1: [API_Box*]						par2: [API_Tranmat*]
	APIDb_ReSetZoomID						= 'RZOM',				// par1: short*	(numOfStepsBack)		par2: ---

	APIDb_GetExtentID						= 'GEX2',				// par1: API_Box*						par2: [const API_DatabaseUnId*]
	APIDb_GetExtent3DID						= 'GEX3',				// par1: API_Box3D*						par2: ---

	APIDb_StartClippingSessionID			= 'BCLP',				// par1: ---							par2: ---
	APIDb_DoClipID							= 'DCLP',				// par1: API_Region*					par2: API_ClipTran*
	APIDb_StopClippingSessionID				= 'ECLP',				// par1: --- 							par2: ---

	APIDb_StartDrawingDataID				= 'BIDF',				// par1: [double*]						par2: [GS::Array<API_Pen>*]
	APIDb_StopDrawingDataID					= 'EIDF',				// par1: GSPtr*							par2: [API_Box*]

	APIDb_DrawOrderInitID					= 'DORI',				// par1: ---							par2: ---
	APIDb_DrawOrderGetNextID				= 'DOGN',				// par1: API_ElemFilterFlags			par2: API_Elem_Head*
	APIDb_DrawOrderTermID					= 'DORT',				// par1: ---							par2: ---

	APIDb_DrawStoryControlID				= 'DSCT',				// par1: API_DatabaseUnId*				par2: ShapePrimsProc*

	APIDb_CalcBoundsID						= 'CABO',				// par1: const API_Elem_Head*			par2: API_Box3D*

	APIDb_RoomReductionsID					= 'RORE',				// par1: const API_Guid*				par2: RoomReductionPolyProc*

	APIDb_GetElementURLRefID				= 'GURL',				// par1: API_Elem_Head*					par2: API_ElemURLRef*
	APIDb_SetElementURLRefID				= 'SURL',				// par1: API_Elem_Head*					par2: API_ElemURLRef*

	APIDb_RefreshElementID					= 'RFSH',				// par1: API_Elem_Head*					par2: bool*
	APIDb_DrawElementID						= 'DRWE',				// par1: API_Elem_Head*					par2: [UInt32] (mask)

	APIDb_InitCreationOrderTableID			= 'ICOT',				// par1: [API_ElemFilter*]		  		par2: ---
	APIDb_CreationOrderGetNextID			= 'COGN',				// par1: API_Guid*						par2: ---
	APIDb_DisposeCreationOrderTableID		= 'DCOT',				// par1: ---							par2: ---

	APIDb_Switch3DSightID					= 'S3DS',				// par1: API_3DSightID					par2: ---

	APIDb_GetOffsetID						= 'GOFS',				// par1: API_Coord*						par2: ---
	APIDb_GetLocOrigoID						= 'GLCO',				// par1: API_Coord3D*					par2: ---

	APIDb_GetDrawingLinkID					= 'GDLN',				// par1: const API_Guid*				par2: API_DrawingLinkInfo*
	APIDb_CheckDrawingStatusID				= 'CKDS',				// par1: const API_Guid*				par2: Int32*

	APIDb_StoreViewSettingsID				= 'STVS',				// par1: bool (store)					par2: ---
	APIDb_GetTWOwnerID						= 'GTWO',				// par1: const API_DatabaseUnId*		par2: short*

	APIDb_GetSectionDatabasesID				= 'GSDI',				// par1: [API_DatabaseUnId**]			par2: [GS::Array<API_DatabaseUnId>*]
	APIDb_GetElevationDatabasesID			= 'GEDI',				// par1: [API_DatabaseUnId**]			par2: [GS::Array<API_DatabaseUnId>*]
	APIDb_GetInteriorElevationDatabasesID	= 'GIED',				// par1: [API_DatabaseUnId**]			par2: [GS::Array<API_DatabaseUnId>*]
	APIDb_GetWorksheetDatabasesID 			= 'GWDI',				// par1: [API_DatabaseUnId**]			par2: [GS::Array<API_DatabaseUnId>*]
	APIDb_GetDocumentFrom3DDatabasesID		= 'GD3D',				// par1: [API_DatabaseUnId**]			par2: [GS::Array<API_DatabaseUnId>*]

	APIDb_GetFullDrawingContentBoxID		= 'FDCB',				// par1: API_Box* (result)				par2: const API_Guid* (drawing element)
	APIDb_GetSubSetDefaultID				= 'GSSD',				// par1: API_SubSet*					par2: ---
	APIDb_CreateSubSetID					= 'CRSS',				// par1: const API_SubSet*				par2: const API_Guid*
	APIDb_GetSubSetID						= 'GSSI',				// par1: const API_Guid*				par2: API_SubSet*
	APIDb_GetLayoutBookID					= 'GLAB',				// par1: API_LayoutBook*				par2: ---

	APIDb_GetHotlinkNodeID					= 'GHLN',				// par1: API_HotlinkNode*				par2: bool* (enableUnplaced)
	APIDb_GetHotlinkStoryInfoID				= 'GHSI',				// par1: API_HotlinkNode*				par2: ---
	APIDb_CreateHotlinkNodeID				= 'CHLN',				// par1: API_HotlinkNode*				par2: ---
	APIDb_ModifyHotlinkNodeID				= 'MHLN',				// par1: API_HotlinkNode*				par2: ---
	APIDb_DeleteHotlinkNodeID				= 'DHLN',				// par1: const API_Guid*				par2: ---
	APIDb_BreakHotlinkNodeID				= 'BHLN',				// par1: const API_Guid*				par2: ---
	APIDb_UpdateHotlinkCacheID				= 'UHLC',				// par1: const API_Guid*				par2: [API_HotlinkCacheGenerator*]

	APIDb_GetHotlinkNodesID					= 'GHNL',				// par1: [const API_HotlinkTypeID*]		par2: GS::Array<API_Guid>* (nodes)								par3: bool* (enableUnplaced)
	APIDb_GetHotlinkRootNodeGuidID			= 'GHRN',				// par1: const API_HotlinkTypeID*		par2: API_Guid* (root node)
	APIDb_GetHotlinkNodeTreeID				= 'GHNT',				// par1: const API_Guid* (root)			par2: GS::HashTable<API_Guid, GS::Array<API_Guid> >*
	APIDb_GetHotlinkInstancesID				= 'GHIL',				// par1: const API_Guid* (node)			par2: GS::Array<API_Guid>* (hotlink elements)
	APIDb_GetHotLinkOwnerID					= 'GHOW',				// par1: const API_Guid* (element)		par2: API_Guid* (hotlink)
	APIDb_GetHotlinkProxyElementTableID		= 'GHPT',				// par1: const API_Guid* (hotlink)		par2: GS::HashTable<API_Guid, API_Guid>* (proxyElementTable)
	APIDb_GetHotlinkSourceStatusID			= 'GHSS',				// par1: const IO::Location* (source)	par2: API_HotlinkSourceStatus* (status)

	APIDb_GetCompoundInfoStringID			= 'GCIS',				// par1: const API_Guid* (element)		par2: GS::UniString* (info string)

	APIDb_GetContainingDatabaseID			= 'GCDB',				// par1: const API_Guid* (element)		par2: API_DatabaseInfo* (-- database containing the element)
	APIDb_GetElementFromAnywhereID			= 'GEFA',				// par1: const API_Guid* (element)		par2: API_Element*
	APIDb_IsCWPanelDegenerateID				= 'IPDE',				// par1: const API_Guid* (element)		par2: bool*

	APIDb_GetActualRenovationFilterID			= 'GARF',			// par1: API_Guid*						par2: ---
	APIDb_SetActualRenovationFilterID			= 'SARF',			// par1: const API_Guid*				par2: ---
	APIDb_GetRenovationFiltersID				= 'GRFL',			// par1: GS::Array<API_Guid>*			par2: ---

	APIDb_GetRVMChangesID						= 'GCHS',			// par1: GS::Array<API_RVMChange>*					par2: ---
	APIDb_GetRVMChangeCustomSchemeID			= 'GCCS',			// par1: GS::HashTable<API_Guid, GS::UniString>*	par2: ---
	APIDb_GetRVMIssuesID						= 'GISU',			// par1: GS::Array<API_RVMIssue>*					par2: ---
	APIDb_ChangeRVMIssueID						= 'CISU',			// par1: API_RVMIssue*								par2: ---
	APIDb_GetRVMIssueCustomSchemeID				= 'GICS',			// par1: GS::HashTable<API_Guid, GS::UniString>*	par2: ---
	APIDb_GetRVMDocumentRevisionsID				= 'GDRE',			// par1: GS::Array<API_RVMDocumentRevision>*		par2: ---
	APIDb_GetRVMChangesFromChangeIdsID			= 'GCFC',			// par1: const GS::Array<GS::UniString>*			par2: GS::Array<API_RVMChange>*
	APIDb_GetRVMLayoutCurrentRevisionChangesID	= 'GLCR',			// par1: const API_DatabaseUnId*					par2: GS::Array<API_RVMChange>*
	APIDb_GetRVMIssueDocumentRevisionsID		= 'GIDR',			// par1: const API_Guid*							par2: GS::Array<API_RVMDocumentRevision>*
	APIDb_GetRVMDocumentRevisionChangesID		= 'GDRC',			// par1: const API_Guid*							par2: GS::Array<API_RVMChange>*
	APIDb_GetRVMElemChangeIdsID					= 'GELC',			// par1: const API_Guid*							par2: GS::Array<GS::UniString>*
	APIDb_GetRVMChangeFirstIssueID				= 'GCFI',			// par1: const GS::UniString*						par2: API_RVMIssue*

	APIDb_GetElementInfoStringID				= 'GEIS',			// par1: const API_Guid* (element)					par2: GS::UniString* (info string)
	APIDb_ChangeElementInfoStringID				= 'CEIS',			// par1: const API_Guid* (element)					par2: const GS::UniString* (info string)

	APIDb_GetElementCategoriesID				= 'GCAS',			// par1: GS::Array<API_ElemCategory>*				par2: ---
	APIDb_GetElementCategoryValuesID			= 'GCVS',			// par1: const API_ElemCategory*					par2: GS::Array<API_ElemCategoryValue>*
	APIDb_BuildWindowValidatorID				= 'BWVR',			// par1: const API_WindowValidatorInfo*				par2: ---
	APIDb_DestroyWindowValidatorID				= 'DWVR',			// par1: const API_Guid*							par2: ---
	APIDb_CheckWindowValidatorID				= 'CWVR',			// par1: const API_WindowValidatorInfo*				par2: bool*
	APIDb_RebuildWindowValidatorID				= 'RWVR',			// par1: const API_WindowValidatorInfo*				par2: ---
	APIDb_SetWindowIdID							= 'SWID',			// par1: const API_Guid*							par2: const API_Guid*

	APIDb_JsonQueryID							= 'JSNQ'			// par1: const API_Guid* (json command)				par2: const API_Guid* (reply message)
} API_DatabaseID;


// =============================================================================
// Window / Database
//
// =============================================================================

/**
 * @brief Possible values of a window/database identifier
 * @enum API_WindowTypeID, @c API_DatabaseTypeID
 * @ingroup Window
 * @remarks This structure holds the parameters of a window or database reference. It must be passed in the case of changing the current window/database (@ref ACAPI_Database_ChangeCurrentDatabase), or just getting the identification of the active one.(@ref ACAPI_Window_GetCurrentWindow /@ref ACAPI_Database_GetCurrentDatabase) In @ref API_PublishFormatData structure it defines the windows in which the publish format is available.
 */
typedef enum {
	API_ZombieWindowID,
	APIWind_FloorPlanID,										// floor plan window type
	APIWind_SectionID,											// section window type
	APIWind_DetailID,											// detail window type
	APIWind_3DModelID,											// 3D model window type
	APIWind_LayoutID,											// layout window type
	APIWind_DrawingID,											// drawing's database type
	APIWind_MyTextID,											// custom text window type
	APIWind_MyDrawID,											// custom draw window type
	APIWind_MasterLayoutID,										// master layout window type
	APIWind_ElevationID,										// elevation window type
	APIWind_InteriorElevationID,								// interior elevation window type
	APIWind_WorksheetID,										// worksheet window type
	APIWind_ReportID,											// report window type
	APIWind_DocumentFrom3DID,									// 3D Document window type
	APIWind_External3DID,										// External 3D window type
	APIWind_Movie3DID,											// movie 3D window type
	APIWind_MovieRenderingID,									// movie rendering window type
	APIWind_RenderingID,										// rendering window type
	APIWind_ModelCompareID,										// model compare window type
	APIWind_IESCommonDrawingID = 0x00001000,					// Interactive Schedule window type

	APIWind_AllModel2DID,
	APIWind_AllModelID,
	APIWind_AllIFCID,
	APIWind_AllWithoutMovieRenderingID,
	APIWind_AllID

} API_WindowTypeID, API_DatabaseTypeID;


/**
 * @brief Identification parameters of a Section, Detail, Interior Elevation, Worksheet, Master Layout,
 * 		  Layout, and 3D Document window or window related database.
 * @struct API_DatabaseUnId
 * @ingroup Database
 * @remarks Use @ref ACAPI_Database_GetGuidFromDBUnId function to convert the old database identifiers to this
 * 			new one. Use @ref ACAPI_Database_GetDBUnIdFromGuid to get old identifiers from this.
 */
typedef	struct API_DatabaseUnId {

/**
 * @brief Unique identifier.
 * @var elemSetId
 */
	API_Guid						elemSetId;

} API_DatabaseUnId;


//! \{

inline bool		operator== (const API_DatabaseUnId& leftOp, const API_DatabaseUnId& rightOp)	{ return leftOp.elemSetId == rightOp.elemSetId; }
inline bool		operator!= (const API_DatabaseUnId& leftOp, const API_DatabaseUnId& rightOp)	{ return leftOp.elemSetId != rightOp.elemSetId; }

//! \}

/**
 * @brief Identification parameters of a project window.
 * @struct API_WindowInfo
 * @ingroup Window
 * @remarks Database/Window reference is used for several purposes:
 * 			- Returned while asking for the active window or database
 * 			- Must be setup when changing the current window or database
 * 			- Defines the database when creating/modifying/deleting an independent detail, worksheet, layout or master layout database
 * 			The databases are referenced with their unique ID, except Floor Plan, 3D Model, and custom window databases.
 * 			The unique IDs can be found in the connecting elements (@ref API_CutPlaneType, @ref API_DetailType, @ref API_WorksheetType),
 * 			or can be listed for independent detail, worksheet, layout and master layout databases (@ref ACAPI_Database_GetDetailDatabases,
 * @ref ACAPI_Database_GetWorksheetDatabases, @ref ACAPI_Database_GetLayoutDatabases, @ref ACAPI_Database_GetMasterLayoutDatabases respectively).
 * 		In the case of Floor Plan and 3D Model databases, the `typeID` field is enough to identify them.
 * 		Custom API windows (`APIWind_MyDrawID`, `APIWind_MyTextID`) are identified with `typeID` and `index`.
 * 		Featuring API 10 With this structure, you can retrieve the name, the title, and the reference ID of a given window/database
 * 		(see @ref ACAPI_Window_GetDatabaseInfo). You can also rename independent detail, worksheet, layout and master layout databases
 * 		using the `name` and `ref` fields in @ref ACAPI_Database_ModifyDatabase.
 */
struct API_WindowInfo {
/**
 * @brief the window/database type identifier
 * @var typeID
 */
	API_WindowTypeID				typeID;

/**
 * @brief usually the database/window index (the refCon value in case of custom windows, not used for Section/Elevation Detail and Worksheet database/window).
 * @var index
 */
	Int32							index;

/**
 * @brief Section/Elevation/Interior Elevation, Detail and Worksheet database/window unique identifier
 * @var databaseUnId
 */
	API_DatabaseUnId				databaseUnId;

/**
 * @brief for Layouts only; database unique ID of the master layout
 * @var masterLayoutUnId
 */
	API_DatabaseUnId				masterLayoutUnId;

/**
 * @brief the title of the database (Unicode string), as it is displayed on the window title bar (generally "ref"+" "+"name")
 * @var title
 */
	GS::uchar_t						title[API_UniLongNameLen];

/**
 * @brief the name of the database (Unicode string)
 * @var name
 */
	GS::uchar_t						name[API_UniLongNameLen];

/**
 * @brief reference string/id of the database
 * @var ref
 */
	GS::uchar_t						ref[API_UniLongNameLen];

/**
 * @brief Element linked to the database (e.g., section to a section database) except for drawing databases where it is the drawing element's @c guid
 * @var linkedElement
 */
	API_Guid						linkedElement;

/**
 * @brief For databases linked to elements (section, detail, etc.): the database containing the element.
 * @var linkedDatabaseUnId
 */
	API_DatabaseUnId				linkedDatabaseUnId;

/**
 * @brief For interior elevations only; the section segment index in the element memo.
 * @var linkedSegmentMemoIndex
 */
	Int32							linkedSegmentMemoIndex;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1[3];
};


/**
 * @brief Identification parameters of a project database.
 * @ingroup Database
 * @remarks Database reference is used for several purposes:
 * 			- Returned while asking for the active database
 * 			- Must be setup when changing the current database
 * 			- Defines the database when creating/modifying/deleting an independent detail, worksheet, layout, or master layout database
 * 			The databases are referenced with their unique ID, except Floor Plan, 3D Model, and custom window databases. The unique IDs can be found in the connecting elements (@ref API_CutPlaneType, @ref API_DetailType, @ref API_WorksheetType) or listed for independent detail, worksheet, layout, and master layout databases (@ref ACAPI_Database_GetDetailDatabases, @ref ACAPI_Database_GetWorksheetDatabases, @ref ACAPI_Database_GetLayoutDatabases, @ref ACAPI_Database_GetMasterLayoutDatabases respectively).
 * 			In Floor Plan and 3D Model databases, the typeID field is enough to identify them. Custom API windows (@c APIWind_MyDrawID, @c APIWind_MyTextID) are identified with typeID and index.
 * 			Featuring API 10 With this structure, you can retrieve the name, the title, and the reference ID of a given window/database (see @ref ACAPI_Window_GetDatabaseInfo). You can also rename independent detail, worksheet, layout, and master layout databases using the name and ref fields in @ref ACAPI_Database_ModifyDatabase.
 * 			See also @ref API_WindowInfo.
 */
using API_DatabaseInfo = API_WindowInfo;


//! \{

#ifdef _MSC_VER
#pragma warning (push)
#else
#pragma clang diagnostic push
#endif
GS_UNHANDLED_ENUM_VALUE_CHECK_OFF

inline bool operator== (const API_DatabaseInfo& leftInfo, const API_DatabaseInfo& rightInfo)
{
	bool result = (leftInfo.typeID == rightInfo.typeID);

	if (result) {
			switch (leftInfo.typeID) {
				case APIWind_FloorPlanID:
				case APIWind_3DModelID:
					break;
				case APIWind_DrawingID:
					result = (leftInfo.databaseUnId == rightInfo.databaseUnId) ? (leftInfo.linkedElement == rightInfo.linkedElement) : false;
					break;
				default:
					result = (leftInfo.databaseUnId == rightInfo.databaseUnId);
					break;
			}
	}

	return result;
}

#ifdef _MSC_VER
#pragma warning (pop)
#else
#pragma clang diagnostic pop
#endif


inline bool operator!= (const API_DatabaseInfo& leftInfo, const API_DatabaseInfo& rightInfo)
{
	return (!(leftInfo == rightInfo));
}


//! \}

/**
 * @brief Parameters to open a new window.
 * @struct API_NewWindowPars
 * @ingroup Window
 * @remarks Refer to the @ref ACAPI_Window_NewWindow function for more details.
 */
struct API_NewWindowPars {

/**
 * @brief type of the database; only @c APIWind_MyTextID and @c APIWind_MyDrawID are allowed.
 * @var typeID
 */
	API_WindowTypeID				typeID;

/**
 * @brief free to use identifier of the window. Returned in notifications.
 * @var userRefId
 */
	API_Guid						userRefId;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	GS::Int8						filler_1;

/**
 * @brief The window uses original weight of pen attributes at line drawing instead of hairline.
 * @var useOriginalPenWeight
 */
	bool							useOriginalPenWeight;

/**
 * @brief The window title (Unicode string).
 * @var wTitle
 */
	GS::uchar_t						wTitle[API_UniLongNameLen];

/**
 * @brief The file name of the window.
 * @var wFile
 */
	GS::uchar_t						wFile[API_UniLongNameLen];

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[8];

};


// =============================================================================
// Grid Settings
//
// =============================================================================

#define	API_GridNone				0
#define	API_GridGrid				1
#define	API_GridSnap				2

#define	API_GridRotDraw				1
#define	API_GridRotCalc				2
#define	API_GridRotView				4

/**
 * @brief The grid parameters.
 * @struct API_GridType
 * @ingroup ProjectSetting
 * @remarks Each database window may have different grid setting parameters.
 * 			To get the actual settings associated to a database use the @ref ACAPI_Window_GetGridSettings function; to change the parameters refer to the @ref ACAPI_Window_ChangeGridSettings function.
 */
struct API_GridType {
/**
 * @brief The main grid's horizontal spacing in meters.
 * @var spaceMainX
 */
	double							spaceMainX;

/**
 * @brief The main grid's vertical spacing in meters.
 * @var spaceMainY
 */
	double							spaceMainY;

/**
 * @brief The number of horizontal lines in the main grid.
 * @var nLineMainX
 */
	short							nLineMainX;

/**
 * @brief The number of vertical lines in the main grid.
 * @var nLineMainY
 */
	short							nLineMainY;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	short							filler_0;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1;

/**
 * @brief true if grid is visible
 * @var gridSwitch
 */
	bool							gridSwitch;

/**
 * @brief The horizontal spacing of the auxiliary grid in meters.
 * @var spaceAuxX
 */
	double							spaceAuxX;

/**
 * @brief The vertical spacing of the auxiliary grid in meters.
 * @var spaceAuxY
 */
	double							spaceAuxY;

/**
 * @brief The number of horizontal auxiliary grid lines.
 * @var nLineAuxX
 */
	short							nLineAuxX;

/**
 * @brief The number of vertical auxiliary grid lines.
 * @var nLineAuxY
 */
	short							nLineAuxY;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	short							filler_2;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	bool							filler_3;


/**
 * @brief Gravity to the grid; @c 0 : none, @c 1 : grid, @c 2 : snap
 * @var gridMode
 */
	unsigned char					gridMode;

/**
 * @brief The snap grid's horizontal offset in meters.
 * @var snapOffsX
 */
	double							snapOffsX;

/**
 * @brief The snap grid's vertical offset in meters.
 * @var snapOffsY
 */
	double							snapOffsY;

/**
 * @brief The snap grid's horizontal spacing in meters.
 * @var snapStepX
 */
	double							snapStepX;

/**
 * @brief The snap grid's vertical offset in meters.
 * @var snapStepY
 */
	double							snapStepY;


/**
 * @brief status of the grid
 * @var status
 */
	short							status;

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	short							filler_4;

/**
 * @brief Reserved for later use.
 * @var filler_5
 */
	Int32							filler_5;


/**
 * @brief rotation angle of the grid, relative to horizontal
 * @var gridAngle
 */
	double							gridAngle;

/**
 * @brief X offset of the grid.
 * @var gridOffsX
 */
	double							gridOffsX;

/**
 * @brief Y offset of the grid.
 * @var gridOffsY
 */
	double							gridOffsY;

/**
 * @brief Z offset of the grid.
 * @var gridOffsZ
 */
	double							gridOffsZ;


/**
 * @brief background color. Transparency is effective only in the Model window.
 * @var backColor
 */
	API_RGBAColor					backColor;

/**
 * @brief color of main grid lines. Transparency is effective only in the Model window.
 * @var gridColor
 */
	API_RGBAColor					gridColor;

};


// =============================================================================
// Room Reductions
//
// =============================================================================

#define	APIRoomReduction_Rest		1							// room reduction type
#define	APIRoomReduction_Wall		2
#define	APIRoomReduction_Column		3
#define	APIRoomReduction_Hatch		4
#define	APIRoomReduction_Gable		5

/**
 * @brief Parameters to get room reduction data.
 * @ingroup Element
 * @struct API_RoomReductionPolyType
 * @remarks Refer to the @ref API_Polygon structure to get more details on the polygon structure. See the @ref RoomReductionPolyProc
 * 			and @ref ACAPI_Element_RoomReductions functions to get more information on how the room reduction data can be obtained.
 * 			Remember to dispose of the `coords`, `subPolys`, and `arcs` handles if they are not needed anymore.
 */
struct API_RoomReductionPolyType {

/**
 * @brief Type of the polygon.
 * 		  | type | polygon |
 * 		  |------|---------|
 * 		  | @c APIRoomReduction_Wall | wall |
 * 		  | @c APIRoomReduction_Column | column |
 * 		  | @c APIRoomReduction_Hatch | hatch |
 * 		  | @c APIRoomReduction_Gable | low ceiling |
 * 		  | @c APIRoomReduction_Rest | other |
 * @var type
 */
	short							type;

/**
 * @brief Percentage of the polygon area
 * @var percent
 */
	short							percent;

/**
 * @brief Number of coordinates
 * @var nCoords
 */
	Int32							nCoords;

/**
 * @brief Number of the subpolygons
 * @var nSubPolys
 */
	Int32							nSubPolys;

/**
 * @brief Number of the arcs
 * @var nArcs
 */
	Int32							nArcs;

/**
 * @brief The coordinate array
 * @var coords
 */
	API_Coord**						coords;

/**
 * @brief The subpolygon endpoints
 * @var subPolys
 */
	Int32**							subPolys;

/**
 * @brief The polygon arcs
 * @var arcs
 */
	API_PolyArc**					arcs;

/**
 * @brief Area of the polygon
 * @var area
 */
	double							area;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1[8];

};


// =============================================================================
// Element URL Reference
//
// =============================================================================

/**
 * @brief URL reference to be stored into elements.
 * @struct API_ElemURLRef
 * @ingroup Element
 * @remarks This structure is used for storing URL references into Archicad database elements.
 * 			The element URL data can be accessed with the @ref ACAPI_Element_GetElementURLRef and @ref ACAPI_Element_SetElementURLRef database functions.
 */
struct API_ElemURLRef {
	/**
	 * @brief The URL link (e.g., "http://www.graphisoft.com")
	 * @var urlLink
	 */
	char							urlLink [512];

/**
 * @brief Description for the URL above (e.g., "GRAPHISOFT Home Page").
 * @var description
 */
	char							description [256];

/**
 * @brief Reserved for later use.
 * @var filler
 */
	char							filler [256];

};


// =============================================================================
// 3D Database Reference
//
// =============================================================================

/**
 * @brief This is the enumeration of the applicable types of 3D sights.
 * @enum API_3DSightID
 * @ingroup Sight
 * @remarks These sight types are used with the @ref ACAPI_Sight_Switch3DSight function; they
 * 			represent the different 3D databases. Currently you can switch between the database behind the 3D window and
 * 			the database coming from the floor plan representation of an element.
 */
typedef enum {
	APISight_3DModel,											// actual 3D sight
	APISight_Floorplan											// element related 3D sight
} API_3DSightID;


// =============================================================================
// Clipping
//
// =============================================================================

/**
 * @brief Defines a transformation for the clipping.
 * @struct API_ClipTran
 * @ingroup Database
 * @remarks This is the second parameter of the @ref ACAPI_Database_DoClip function; defines a
 * 			transformation for the clipping region.
 */
struct API_ClipTran {

/**
 * @brief offset in @c x direction
 * @var x0
 */
	double							x0;

/**
 * @brief offset in @c y direction
 * @var y0
 */
	double							y0;

/**
 * @brief scale factor
 * @var scale
 */
	double							scale;

/**
 * @brief rotation angle
 * @var angle
 */
	double							angle;

/**
 * @brief floor index
 * @var floor
 */
	short							floor;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	short							filler_0[3];

};


// =============================================================================
// Drawing link
//
// =============================================================================

/**
 * @brief Type of the drawing link.
 * @enum API_DrawingLinkTypeID
 * @ingroup Drawing
 * @remarks These drawing link type values are used in the @ref API_DrawingLinkInfo structure.
 */
typedef enum {
	API_DrawingLink_UnknownID = 0,

	API_DrawingLink_InternalViewID,								// internal view
	API_DrawingLink_ExternalViewID,								// external view
	API_DrawingLink_DrawingID,									// drawing
	API_DrawingLink_DXF_DWGID,									// DXF or DWF file
	API_DrawingLink_PDFID,										// PDF file
	API_DrawingLink_ImageID,									// image
	API_DrawingLink_PMKID,										// PlotMaker file
	API_DrawingLink_APIID,										// API Add-On file
	API_DrawingLink_InfoID,										// Info

	API_DrawingLink_OtherID

} API_DrawingLinkTypeID;

/**
 * @brief Type of the view nodes.
 * @enum API_ViewNodeTypeID
 * @ingroup Drawing
 * @remarks These view type values are used in the @ref API_DrawingLinkInfo structure.
 */
typedef enum {
	API_ViewNodeUndefined			= 0,
	API_ViewNodeStory				= 1,
	API_ViewNodeSection				= 2,
	API_ViewNodeDetailDrawing		= 3,
	API_ViewNodePerspective			= 4,
	API_ViewNodeAxonometry			= 5,
	API_ViewNodeList				= 6,
	API_ViewNodeSchedule			= 7,
	API_ViewNodeToc					= 8,
	API_ViewNodeCamera				= 9,
	API_ViewNodeCameraSet			= 10,
	API_ViewNodeElevation			= 11,
	API_ViewNodeInteriorElevation	= 12,
	API_ViewNodeWorksheetDrawing	= 13,
	API_ViewNodeDocumentFrom3D		= 14,
	API_ViewNodeAPIList				= 15

} API_ViewNodeTypeID;

typedef enum {
	API_IDFTypeUndefined			= 0,
	API_IDFTypeDrawing				= 1,
	API_IDFTypeImage				= 2,
	API_IDFTypePdf					= 3
} API_IDFTypeID;

/**
 * @brief Parameters of a drawing link.
 * @struct API_DrawingLinkInfo
 * @ingroup Drawing
 * @remarks You can get information about a given drawing link using this structure with the
 * @ref ACAPI_Drawing_GetDrawingLink function. The `linkPath` location is used only for links having associated source file
 * 		location; otherwise, this pointer is `nullptr`. The `viewPath` is filled out only for internal and external view
 * 		type links, otherwise it is `nullptr`. If the link has been broken, then the `linkTypeID` parameter is
 * 		`@ref API_DrawingLink_InfoID`. In this case the `infoTypeID` field shows the original type of the link.
 */
struct API_DrawingLinkInfo {

/**
 * @brief Type of the link
 * @var linkTypeID
 */
	API_DrawingLinkTypeID			linkTypeID;

/**
 * @brief Type of the content; can be Drawing, Image, PDF, or undefined
 * @var idfTypeID
 */
	API_IDFTypeID					idfTypeID;

/**
 * @brief GUID for internal or external views
 * @var linkGuid
 */
	API_Guid						linkGuid;

/**
 * @brief The location of the file associated with the link in case of internal and external views, images, PDF type or API add-on file types
 * @var linkPath
 */
	IO::Location*					linkPath;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2;

/**
 * @brief The name of the drawing
 * @var name
 */
	char							name[256];

/**
 * @brief The number of the drawing
 * @var number
 */
	char							number[256];

	/**
	 * @brief The type of the model behind the view (in case of view type links only)
	 * 		  ( @c API_DrawingLink_InternalViewID or @c API_DrawingLink_ExternalViewID )
	 * @var viewType
	 */
	API_ViewNodeTypeID				viewType;

/**
 * @brief The destination view is not available (in case of view type links only)
 * @var viewDeleted
 */
	bool							viewDeleted;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	char							filler_3[3];

/**
 * @brief Pointer to a dynamically allocated C string containing the path to the source view in the Project Navigator
 * 		  in case of view type links (e.g. "\Untitled\0. Ground Floor")
 * @var viewPath
 */
	GSPtr							viewPath;

/**
 * @brief The original type of the link if it is broken (used only when @c linkTypeID is `API_DrawingLink_InfoID`)
 * @var infoTypeID
 */
	API_DrawingLinkTypeID			infoTypeID;

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	Int32							filler_4[2];

};


// =============================================================================
// Story Settings
//
// =============================================================================

/**
 * @brief Parameters of one story.
 * @struct API_StoryType
 * @ingroup View
 * @sa API_StoryInfo
 * @remarks Each parameter can be set in the "Story Settings..." dialog of Archicad are represented in the structure. The story height should be calculated based on neighboring stories.
 * 			Refer to @ref API_StoryInfo structure for further details.
 */
struct API_StoryType {

/**
 * @brief The story index. Should be between `firstStory` and `lastStory` in @ref API_StoryInfo
 * @var index
 */
	short							index;

/**
 * @brief Unique ID of the story.
 * @var floorId
 */
	short							floorId;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	char							filler_0;

/**
 * @brief Story level lines should appear on sections and elevations.
 * @var dispOnSections
 */
	bool							dispOnSections;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief The story level.
 * @var level
 */
	double							level;

/**
 * @brief The name of the story as a Unicode string (UTF-16).
 * @var uName
 */
	GS::uchar_t						uName[API_UniLongNameLen];

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[4];

};


// =============================================================================
// Hotlink reference
//
// =============================================================================

/**
 * @brief Enumerates the available hotlink module types.
 * @enum API_HotlinkTypeID
 * @ingroup Hotlink
 */
typedef enum {
	APIHotlink_Unknown				= 0,
	APIHotlink_Module				= 1,
	APIHotlink_XRef					= 2

} API_HotlinkTypeID;

typedef enum {
	APIHotlink_LocalFile			= 0,
	APIHotlink_TWFS					= 1,
	APIHotlink_TWProject			= 2
} API_HotlinkSourceTypeID;

typedef enum {
	API_HotlinkSource_AuthCanceld		  = -1,
	API_HotlinkSource_SourceMissing		  = 0,
	API_HotlinkSource_SourceAvailable	  = 1,
	API_HotlinkSource_SourceNotAccessible = 2,
	API_HotlinkSource_SourceIncompatible  = 3,
	API_HotlinkSource_SourceOffline		  = 4
} API_HotlinkSourceStatus;

/**
 * @brief Type of the hotlink by the number of linked stories.
 * @enum API_HotlinkStoryRangeID
 * @ingroup Hotlink
 * @remarks This type specifies in @ref API_HotlinkNode whether the hotlinked
 */
typedef enum {
	APIHotlink_SingleStory			= 0,
	APIHotlink_AllStories			= 1

} API_HotlinkStoryRangeID;

/**
 * @brief Hotlink user data.
 * @struct API_HotlinkUserData
 * @ingroup Hotlink
 */
struct API_HotlinkUserData {

/**
 * @brief Data version.
 * @var dataVersion
 */
	short							dataVersion;

/**
 * @brief Byte ordering in data storage.
 * @var platformSign
 */
	unsigned short					platformSign;

/**
 * @brief User specified flags.
 * @var flags
 */
	GSFlags							flags;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief User specified data.
 * @var data
 */
	GSPtr							data;

/**
 * @brief For XREF node creation only, @c nullptr otherwise.
 * @var translatorContent
 */
	GS::UniString*					translatorContent;

};

/**
 * @brief Describes a hotlink node.
 * @struct API_HotlinkNode
 * @ingroup Hotlink
 * @since Archicad 26
 * @remarks The destructor of this structure will automatically deallocate the memory pointed by the @c sourceLocation, @c serverSourceLocation and @c userData fields. Make sure those point to memory on heap.
 */
struct API_HotlinkNode {

/**
 * @brief Globally unique Id of the node
 * @var guid
 */
	API_Guid						guid;

/**
 * @brief Hotlink source reference type (Hotlinked Module or XRef)
 * @var type
 */
	API_HotlinkTypeID				type;

/**
 * @brief Single or multistory hotlink
 * @var storyRangeType
 */
	API_HotlinkStoryRangeID			storyRangeType;

/**
 * @brief Time of the hotlink was updated last.
 * @var updateTime
 */
	GSTime							updateTime;

/**
 * @brief Location of the source file
 * @var sourceLocation
 */
	IO::Location*					sourceLocation;

/**
 * @brief Story info of the source file. Refer to @c API_StoryType for further details.
 * @var storyInfo
 */
	API_StoryType**					storyInfo;
	Int32							filler_4;

/**
 * @brief Name of the hotlink node
 * @var name
 */
	GS::uchar_t						name[API_UniLongNameLen];

/**
 * @brief Name of the hotlinked story
 * @var refFloorName
 */
	GS::uchar_t						refFloorName[API_UniLongNameLen];

/**
 * @brief Index of the hotlinked story in case of single-story hotlinked module
 * @var refFloorInd
 */
	short							refFloorInd;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	bool							filler_3;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1;

/**
 * @brief Owner identifier of the hotlink node (0 means the Hotlink Manager of Archicad)
 * @var ownerId
 */
	GSType							ownerId;

/**
 * @brief Optional custom data handled by the owner
 * @var userData
 */
	API_HotlinkUserData				userData;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[4];

/**
 * @brief Location of the source file on the server
 * @var serverSourceLocation
 */
	IO::Location*					serverSourceLocation;

/**
 * @brief Source reference type, could be @c APIHotlink_LocalFile, @c APIHotlink_TWFS (TeamWork File
 * 		  System), or @c APIHotlink_TWProject (TeamWork project)
 * @var sourceType
 */
	API_HotlinkSourceTypeID			sourceType;

/**
 * @brief Size of the source file.
 * @var fileSize
 */
	UInt64							fileSize;

/**
 * @brief File revision number (only for revisions), Teamwork file system only.
 * @var versionNumber
 */
	Int64							versionNumber;

/**
 * Destroys the hotlink node and cleans up properly.
 */
	~API_HotlinkNode ()
	{
		delete sourceLocation; sourceLocation = nullptr;
		delete serverSourceLocation; serverSourceLocation = nullptr;
		BMKillPtr (&userData.data);
	}

};

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif
/**
 * @brief Base class for generating the updated content of a hotlink cache.
 * @class API_HotlinkCacheGenerator
 * @ingroup Hotlink
 * @remarks When a hotlink node is created by the add-on, the content of the hotlink
 * 			cache must be generated also. In order to create the appropriate elements and attributes
 * 			into the cache database, you need to pass an @ref API_HotlinkCacheGenerator object to the
 * @ref ACAPI_Hotlink_UpdateHotlinkCache function. When the GenerateCacheContentForHotlinkNode method
 * 		of the object is called back from the hotlink update function, the standard element and
 * 		attribute creator functions (like @ref ACAPI_Element_Create and ACAPI_Attribute_Create) are
 * 		redirected to create elements and attributes into the hotlink cache database, rather than
 * 		the project database.\n If the GenerateCacheContentForHotlinkNode function return an error,
 * 		the update process is canceled.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Hotlink_UpdateHotlinkCache-Example-Snippet
 */
class API_HotlinkCacheGenerator {
public:
	virtual ~API_HotlinkCacheGenerator () {}

/**
 * @brief A callback function to generate the cache content for hotlink nodes.
 * @param hotlinkNodeGuid Guid of the hotlink node.
 * @return Returns error code.
 */
	virtual GSErrCode	GenerateCacheContentForHotlinkNode (const API_Guid& hotlinkNodeGuid) = 0;
};

#ifdef __clang__
#pragma clang diagnostic pop
#endif


// =============================================================================
// Revision Management
//
// =============================================================================

/**
 * @brief Represents a revision change.
 * @struct API_RVMChange
 * @ingroup Revision
 * @remarks You are able to get all changes via @ref ACAPI_Revision_GetRVMChanges function,
 * 			and get the custom scheme of changes via @ref ACAPI_Revision_GetRVMChangeCustomScheme function.
 */
struct API_RVMChange {

/**
 * @brief Unique ID of the Change.
 * @var id
 */
	GS::UniString							id;

/**
 * @brief Short description of the Change.
 * @var description
 */
	GS::UniString							description;

/**
 * @brief Last modified time of the Change.
 * @var lastModifiedTime
 */
	GSTime									lastModifiedTime;

/**
 * @brief Teamwork user identifier (full name) who last modified the Change.
 * @var modifiedByUser
 */
	GS::UniString							modifiedByUser;

/**
 * @brief Change in a document revision is in an issue or not.
 * @var issued
 */
	bool									issued;

/**
 * @brief Change is archived or active.
 * @var archived
 */
	bool									archived;

/**
 * @brief Contains the custom data fields. The custom scheme GUID-value pairs are stored in a @c GS::HashTable.
 * @var customData
 */
	GS::HashTable<API_Guid, GS::UniString>	customData;

};

/**
 * @brief Represents an Issue.
 * @struct API_RVMIssue
 * @ingroup Revision
 * @remarks You can get all issues via @ref ACAPI_Revision_GetRVMIssues function
 * 			and get the custom scheme of issues via @ref ACAPI_Revision_GetRVMIssueCustomScheme function.
 * @image html issue_details.png "Issue details" width=25%
 */
struct API_RVMIssue {

/**
 * @brief GUID of the Issue.
 * @var guid
 */
	API_Guid								guid;

/**
 * @brief ID of the Issue.
 * @var id
 */
	GS::UniString							id;

/**
 * @brief Short description of the Issue.
 * @var description
 */
	GS::UniString							description;

/**
 * @brief Issued time of the Issue.
 * @var issueTime
 */
	GSTime									issueTime;

/**
 * @brief TW user identifier (full name) who issued the Issue.
 * @var issuedByUser
 */
	GS::UniString							issuedByUser;

/**
 * @brief The member ID of the owner in TeamWork mode.
 * @var userId
 */
	short									userId;

/**
 * @brief Corresponds to the "Override Revision ID of all included Layouts" checkbox on the "Issue Details" dialog (see picture below).
 * @var isOverrideRevisionId
 */
	bool									isOverrideRevisionId;

/**
 * @brief Corresponds to the "Create New Revision in all included Layouts" checkbox on the "Issue Details" dialog (see picture below).
 * @var isCreateNewRevision
 */
	bool									isCreateNewRevision;

/**
 * @brief Corresponds to the "Markers visible since" dropdown list on the "Issue Details" dialog (see picture below).
 * @var visibleMarkersInIssues
 */
	short									visibleMarkersInIssues;

/**
 * @brief Status of the issue (issued or opened).
 * @var issued
 */
	bool									issued;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	bool									filler[5];

/**
 * @brief Contains the custom data fields. The custom scheme GUID-value pairs are stored in a @c GS::HashTable.
 * @var customData
 */
	GS::HashTable<API_Guid, GS::UniString>	customData;

};

/**
 * @brief Status of the document revision.
 * @enum API_RVMDocumentRevisionStatusID
 * @ingroup Revision
 * @remarks This type specifies in @c API_RVMDocumentRevision whether document revision is issued or opened.
 */
typedef enum {
	API_RVMDocumentRevisionStatusActual		= 0,
	API_RVMDocumentRevisionStatusIssued		= 1

} API_RVMDocumentRevisionStatusID;

/**
 * @brief Represents layout meta data in @ref API_RVMDocumentRevision.
 * @struct API_RVMLayoutInfo
 * @ingroup Revision
 * @remarks This structure contains layout meta data for @c API_RVMDocumentRevision.
 */
struct API_RVMLayoutInfo {

/**
 * @brief ID of the layout.
 * @var id
 */
	GS::UniString							id;

/**
 * @brief Database unique identifier. Valid only for opened issue.
 * @var dbId
 */
	API_DatabaseUnId						dbId;

/**
 * @brief Name of the layout.
 * @var name
 */
	GS::UniString							name;

/**
 * @brief Name of the master layout.
 * @var masterLayoutName
 */
	GS::UniString							masterLayoutName;

/**
 * @brief Width of the layout.
 * @var width
 */
	double									width;

/**
 * @brief Height of the layout.
 * @var height
 */
	double									height;

/**
 * @brief Array of the drawing scales.
 * @var drawingScales
 */
	GS::Array<GS::UniString>				drawingScales;

/**
 * @brief ID of the subset.
 * @var subsetId
 */
	GS::UniString							subsetId;

/**
 * @brief Name of the subset.
 * @var subsetName
 */
	GS::UniString							subsetName;

/**
 * @brief Contains the custom data fields. The custom scheme GUID-value pairs are stored in a GS::HashTable.
 * @var customData
 */
	GS::HashTable<API_Guid, GS::UniString>	customData;

/**
 * @brief Teamwork owner of the layout.
 * @var teamworkOwner
 */
	short									teamworkOwner;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	short									filler[3];

};

/**
 * @brief Represents a Document Revision.
 * @struct API_RVMDocumentRevision
 * @ingroup Revision
 * @remarks You can get all document revisions via @ref ACAPI_Revision_GetRVMDocumentRevisions function.
 */
struct API_RVMDocumentRevision {

/**
 * @brief GUID of the Document Revision.
 * @var guid
 */
	API_Guid								guid;

/**
 * @brief ID of the Document Revision.
 * @var id
 */
	GS::UniString							id;

/**
 * @brief ID with optional suffix (- WIP) of the Document Revision.
 * @var finalId
 */
	GS::UniString							finalId;

/**
 * @brief The member ID of the owner in TeamWork mode.
 * @var userId
 */
	short									userId;

/**
 * @brief Status of the document revision (issued or opened).
 * @var status
 */
	API_RVMDocumentRevisionStatusID			status;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	Int32									filler;

/**
 * @brief Layout meta data.
 * @var layoutInfo
 */
	API_RVMLayoutInfo						layoutInfo;

};

// =============================================================================
// SubSet
// =============================================================================

/**
 * @brief Describes the Layout ID styles.
 * @enum API_NumberingStyle
 * @ingroup Navigator
 * @remarks API_SubSet contains this structure. @ref ACAPI_Navigator_CreateSubSet function creates a Subset in the Layout Book.
 */
typedef enum {
	API_NS_Undefined	= 0,
	API_NS_abc			= 1,
	API_NS_ABC			= 2,
	API_NS_1			= 3,
	API_NS_01			= 4,
	API_NS_001			= 5,
	API_NS_0001			= 6,
	API_NS_noID			= 8

} API_NumberingStyle;

/**
 * @brief Represents a Subset in the Layout Book.
 * @struct API_SubSet
 * @ingroup Navigator
 * @remarks You can get the default Subset settings via @ref ACAPI_Navigator_GetSubSetDefault function. @ref ACAPI_Navigator_CreateSubSet creates a Subset in the Layout Book.
 */
struct API_SubSet {

/**
 * @brief Name of the subset.
 * @var name
 */
	GS::uchar_t			name[API_LongNameLen];

/**
 * @brief Do not include this Subset in ID sequence.
 * @var doNotInclude
 */
	bool				doNotInclude;

/**
 * @brief Custom ID or automatically generated.
 * @var customNumbering
 */
	bool				customNumbering;

/**
 * @brief Continue using ID assignment of upper levels.
 * @var continueNumbering
 */
	bool				continueNumbering;

/**
 * @brief Use prefix and IDs of upper levels.
 * @var useUpperPrefix
 */
	bool				useUpperPrefix;

/**
 * @brief Add own prefix for this Subset.
 * @var addOwnPrefix
 */
	bool				addOwnPrefix;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	bool				filler[3];

/**
 * @brief Custom number for the subset.
 * @var customNumber
 */
	GS::uchar_t			customNumber[API_LongNameLen];

/**
 * @brief Automatic numbering format for the subset.
 * @var autoNumber
 */
	GS::uchar_t			autoNumber[API_LongNameLen];

/**
 * @brief ID appearance style.
 * @var numberingStyle
 */
	API_NumberingStyle	numberingStyle;

/**
 * @brief Start numbering at.
 * @var startAt
 */
	Int32				startAt;

/**
 * @brief Prefix for the subset.
 * @var ownPrefix
 */
	GS::uchar_t			ownPrefix[API_LongNameLen];

};

// =============================================================================
// Layout Book
// =============================================================================

/**
 * @brief Represents the Book settings.
 * @struct API_LayoutBook
 * @ingroup Navigator
 * @remarks You can get Book Settings via @ref ACAPI_Navigator_GetLayoutBook function.
 */
struct API_LayoutBook {

/**
 * @brief Use flat Layout order or hierarchy (Tree view by Subset).
 * @var flatNumbering
 */
	bool									flatNumbering;

/**
 * @brief ID Prefix.
 * @var prefix
 */
	GS::UniString							prefix;

/**
 * @brief ID appearance style.
 * @var numberingStyle
 */
	API_NumberingStyle						numberingStyle;

/**
 * @brief Start numbering at.
 * @var startAt
 */
	Int32									startAt;

/**
 * @brief Use change ID or Number by Revisions.
 * @var useChangeOwnID
 */
	bool									useChangeOwnID;

/**
 * @brief ID prefix in Revisions.
 * @var changePrefix
 */
	GS::UniString							changePrefix;

/**
 * @brief ID appearance style in Revisions.
 * @var changeNumberingStyle
 */
	API_NumberingStyle						changeNumberingStyle;

/**
 * @brief Contains the custom data fields. The custom scheme GUID-value pairs are stored in a @c GS::HashTable.
 * @var customScheme
 */
	GS::HashTable<API_Guid, GS::UniString>	customScheme;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32									filler_1[2];

};


// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief Holds information on elements and custom checksums that should be validated for the window
 * @struct API_WindowValidatorInfo
 * @ingroup Database
 * @remarks This structure is used by the *WindowValidator functions; for further details, refer to these sections.
 */
struct API_WindowValidatorInfo {

/**
 * @brief The GUID of the window.
 * @var guid
 */
	API_Guid						guid;

/**
 * @brief List of elements important for the addon.
 * @var elemList
 */
	GS::Array<API_Guid>				elemList;

/**
 * @brief Custom list of checksum to validate along the given elements.
 * @var checkSumList
 */
	GS::Array<MD5::FingerPrint>		checkSumList;

};

#endif
