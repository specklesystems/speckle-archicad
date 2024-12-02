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

	APIDb_StartDrawingDataID				= 'BIDF',				// par1: [double*]						par2: [API_PenType**]
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


typedef	struct API_DatabaseUnId {
	API_Guid						elemSetId;
} API_DatabaseUnId;


extern "C++" {

inline bool		operator== (const API_DatabaseUnId& leftOp, const API_DatabaseUnId& rightOp)	{ return leftOp.elemSetId == rightOp.elemSetId; }
inline bool		operator!= (const API_DatabaseUnId& leftOp, const API_DatabaseUnId& rightOp)	{ return leftOp.elemSetId != rightOp.elemSetId; }

}


typedef struct {
	API_WindowTypeID				typeID;
	Int32							index;						// database/window index
	API_DatabaseUnId				databaseUnId;				// database unique ID
	API_DatabaseUnId				masterLayoutUnId;			// for Layouts only; database unique ID of the master layout
	GS::uchar_t						title[API_UniLongNameLen];	// title of the database (generally "ref"+" "+"name") - output only
	GS::uchar_t						name[API_UniLongNameLen];	// name of the database
	GS::uchar_t						ref[API_UniLongNameLen];	// reference string/id of the database
	API_Guid						linkedElement;				// element linked to the database or drawing guid if (typeID == APIWind_DrawingID) (e.g. section to a section database); the element, never the section segment!
	API_DatabaseUnId				linkedDatabaseUnId;			// for databases linked to elements (section, detail, etc.): the database containing the element
	Int32							linkedSegmentMemoIndex;		// for interior elevations
	Int32							filler_1[3];
} API_WindowInfo, API_DatabaseInfo;


typedef struct {
	API_WindowTypeID				typeID;						// only APIWind_MyTextID and APIWind_MyDrawID allowed
	API_Guid						userRefId;					// free to use identifier of the window, returned in notifications
	GS::Int8						filler_1;
	bool							useOriginalPenWeight;
	GS::uchar_t						wTitle[API_UniLongNameLen];
	GS::uchar_t						wFile[API_UniLongNameLen];
	Int32							filler_2[8];
} API_NewWindowPars;


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

typedef struct {
	double							spaceMainX;					// main grid horizontal spacing in meter
	double							spaceMainY;					// main grid vertical spacing in meter
	short							nLineMainX;					// number of main horizontal grid lines
	short							nLineMainY;					// number of main vertical grid lines
	short							filler_0;
	bool							filler_1;
	bool							gridSwitch;					// true if grid is visible

	double							spaceAuxX;					// auxiliary grid horizontal spacing in meter
	double							spaceAuxY;					// auxiliary grid vertical spacing in meter
	short							nLineAuxX;					// number of horizontal auxiliary grid lines
	short							nLineAuxY;					// number of auxiliary grid lines vertical
	short							filler_2;
	bool							filler_3;

	unsigned char					gridMode;					// 0:none, 1:grid, 2:snap

	double							snapOffsX;					// snap grid horizontal offset in meter
	double							snapOffsY;					// snap grid vertical offset in meter
	double							snapStepX;					// snap grid horizontal spacing in meter
	double							snapStepY;					// snap grid vertical spacing in meter

	short							status;						// status of the grid
	short							filler_4;
	Int32							filler_5;

	double							gridAngle;					// rotation angle of the grid
	double							gridOffsX;					// X offset of the grid
	double							gridOffsY;					// Y offset of the grid
	double							gridOffsZ;					// Z offset of the grid

	API_RGBAColor					backColor;					// color of background with transparency
	API_RGBAColor					gridColor;					// color of main grid lines with transparency
} API_GridType;


// =============================================================================
// Room Reductions
//
// =============================================================================

#define	APIRoomReduction_Rest		1							// room reduction type
#define	APIRoomReduction_Wall		2
#define	APIRoomReduction_Column		3
#define	APIRoomReduction_Hatch		4
#define	APIRoomReduction_Gable		5

typedef struct {
	short							type;
	short							percent;
	Int32							nCoords;
	Int32							nSubPolys;
	Int32							nArcs;
	API_Coord**						coords;
	Int32**							subPolys;
	API_PolyArc**					arcs;
	double							area;
	Int32							filler_1[8];
} API_RoomReductionPolyType;


// =============================================================================
// Element URL Reference
//
// =============================================================================

typedef struct {
	char							urlLink [512];				// "http://www.graphisoft.com"
	char							description [256];			// "GRAPHISOFT Home Page"
	char							filler [256];
} API_ElemURLRef;


// =============================================================================
// 3D Database Reference
//
// =============================================================================

typedef enum {
	APISight_3DModel,											// actual 3D sight
	APISight_Floorplan											// element related 3D sight
} API_3DSightID;


// =============================================================================
// Clipping
//
// =============================================================================

typedef struct {
	double							x0;
	double							y0;
	double							scale;
	double							angle;
	short							floor;
	short							filler_0[3];
} API_ClipTran;


// =============================================================================
// Drawing link
//
// =============================================================================

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

typedef struct {
	API_DrawingLinkTypeID			linkTypeID;					// type of the link
	API_IDFTypeID					idfTypeID;					// type of the IDF
	API_Guid						linkGuid;					// guid for internal views
	IO::Location*					linkPath;					// path for internal and external views, images, add-on related, and PDF files
	Int32							filler_2;
	char							name[256];					// drawing name
	char							number[256];				// drawing number
	API_ViewNodeTypeID				viewType;					// the type of the model behind the view (API_DrawingLink_InternalViewID or API_DrawingLink_ExternalViewID)
	bool							viewDeleted;				// the destination view is not available
	char							filler_3[3];
	GSPtr							viewPath;					// the source view navigator path
	API_DrawingLinkTypeID			infoTypeID;					// info type of the link (for broken links) - in case of linkTypeID is API_DrawingLink_InfoID
	Int32							filler_4[2];
} API_DrawingLinkInfo;


// =============================================================================
// Hotlink reference
//
// =============================================================================

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

typedef enum {
	APIHotlink_SingleStory			= 0,
	APIHotlink_AllStories			= 1
} API_HotlinkStoryRangeID;

typedef struct {
	short							dataVersion;						// data version
	unsigned short					platformSign;						// byte ordering in data storage
	GSFlags							flags;								// user specified flags
	Int32							filler_1;
	GSPtr							data;								// user specified data
	GS::UniString*					translatorContent;					// for xref node creation only, it can be nullptr otherwise
} API_HotlinkUserData;

struct API_HotlinkNode {
	API_Guid						guid;								// globally unique Id
	API_HotlinkTypeID				type;								// hotlink reference type
	API_HotlinkStoryRangeID			storyRangeType;						// single or multistory
	GSTime							updateTime;							// last updated time
	IO::Location*					sourceLocation;						// location of the source file
	GS::uchar_t						name [API_UniLongNameLen];			// name of the hotlink node
	GS::uchar_t						refFloorName [API_UniLongNameLen];	// name of the hotlinked story
	short							refFloorInd;						// index of the hotlinked story (in case of single story hotlink)
	bool							filler_3;
	bool							filler_1;
	GSType							ownerId;							// owner of the hotlink (0 - ARCHICAD)
	API_HotlinkUserData				userData;							// optional custom data handled by the owner
	Int32							filler_2[4];
	IO::Location*					serverSourceLocation;				// location of the source file on the server
	API_HotlinkSourceTypeID			sourceType;							// source reference type
	UInt64							fileSize;							// size of the source file
	Int64							versionNumber;						// TWFS revision number

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

class API_HotlinkCacheGenerator {
public:
	virtual ~API_HotlinkCacheGenerator () {}
	virtual GSErrCode	GenerateCacheContentForHotlinkNode (const API_Guid& hotlinkNodeGuid) = 0;
};

#ifdef __clang__
#pragma clang diagnostic pop
#endif


// =============================================================================
// Revision Management
//
// =============================================================================

typedef struct {
	GS::UniString							id;
	GS::UniString							description;
	GSTime									lastModifiedTime;
	GS::UniString							modifiedByUser;
	bool									issued;
	bool									archived;
	GS::HashTable<API_Guid, GS::UniString>	customData;
} API_RVMChange;

typedef struct {
	API_Guid								guid;
	GS::UniString							id;
	GS::UniString							description;
	GSTime									issueTime;
	GS::UniString							issuedByUser;
	short									userId;
	bool									isOverrideRevisionId;
	bool									isCreateNewRevision;
	short									visibleMarkersInIssues;
	bool									issued;
	bool									filler[5];
	GS::HashTable<API_Guid, GS::UniString>	customData;
} API_RVMIssue;

typedef enum {
	API_RVMDocumentRevisionStatusActual		= 0,
	API_RVMDocumentRevisionStatusIssued		= 1
} API_RVMDocumentRevisionStatusID;

typedef struct {
	GS::UniString							id;
	API_DatabaseUnId						dbId;
	GS::UniString							name;
	GS::UniString							masterLayoutName;
	double									width;
	double									height;
	GS::Array<GS::UniString>				drawingScales;
	GS::UniString							subsetId;
	GS::UniString							subsetName;
	GS::HashTable<API_Guid, GS::UniString>	customData;
	short									teamworkOwner;
	short									filler[3];
} API_RVMLayoutInfo;

typedef struct {
	API_Guid								guid;
	GS::UniString							id;
	GS::UniString							finalId;
	short									userId;
	API_RVMDocumentRevisionStatusID			status;
	Int32									filler;
	API_RVMLayoutInfo						layoutInfo;
} API_RVMDocumentRevision;

// =============================================================================
// SubSet
// =============================================================================

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

typedef struct {
	GS::uchar_t			name[API_LongNameLen];
	bool				doNotInclude;
	bool				customNumbering;
	bool				continueNumbering;
	bool				useUpperPrefix;
	bool				addOwnPrefix;
	bool				filler[3];
	GS::uchar_t			customNumber[API_LongNameLen];
	GS::uchar_t			autoNumber[API_LongNameLen];
	API_NumberingStyle	numberingStyle;
	Int32				startAt;
	GS::uchar_t			ownPrefix[API_LongNameLen];
} API_SubSet;

// =============================================================================
// Layout Book
// =============================================================================

typedef struct {
	bool									flatNumbering;
	GS::UniString							prefix;
	API_NumberingStyle						numberingStyle;
	Int32									startAt;
	bool									useChangeOwnID;
	GS::UniString							changePrefix;
	API_NumberingStyle						changeNumberingStyle;
	GS::HashTable<API_Guid, GS::UniString>	customScheme;
	Int32									filler_1[2];
} API_LayoutBook;


// ---------------------------------------------------------------------------------------------------------------------

struct API_WindowValidatorInfo {
	API_Guid						guid;
	GS::Array<API_Guid>				elemList;
	GS::Array<MD5::FingerPrint>		checkSumList;
};

#endif
