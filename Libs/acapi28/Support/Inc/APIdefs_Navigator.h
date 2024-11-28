// *********************************************************************************************************************
// API definitions - navigator data
//
// Module:			API
// Namespace:		-
// Contact person:	archicadapi@graphisoft.com
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APIDEFS_NAVIGATOR_H)
#define APIDEFS_NAVIGATOR_H

#if defined (_MSC_VER)
#pragma once
#endif

// --- Includes	--------------------------------------------------------------------------------------------------------

// own
#include "APIdefs_Base.h"
#include "APIdefs_Database.h"
#include "APIdefs_Elements.h"
#include "APIdefs_Environment.h"
#include "APIdefs_ViewSettings.hpp"
#include "APIdefs_Registration.h"
#include "API_Guid.hpp"

// GSRoot
#include "UniString.hpp"


// --- Compiler settings -----------------------------------------------------------------------------------------------


// --- Type definitions	------------------------------------------------------------------------------------------------


// =============================================================================
// Function codes and parameter descriptions
//
// =============================================================================

typedef enum {			// Codes for Navigator functions

	APINavigator_GetNavigatorSetNumID				= 'GNSN',			// par1: Int32*								par2: ---
	APINavigator_GetNavigatorSetID					= 'GNSE',			// par1: API_NavigatorSet*					par2: Int32*
	APINavigator_GetNavigatorItemID					= 'GNIT',			// par1: const API_Guid*					par2: API_NavigatorItem*
	APINavigator_GetNavigatorParentItemID			= 'GNPI',			// par1: const API_Guid*					par2: API_NavigatorItem*
	APINavigator_GetNavigatorChildNumID				= 'GNCN',			// par1: API_NavigatorItem*					par2: Int32*
	APINavigator_GetNavigatorChildrenItemsID		= 'GNCI',			// par1: API_NavigatorItem*					par2: GS::Array<API_NavigatorItem>*
	APINavigator_GetNavigatorViewID					= 'GNVI',			// par1: API_NavigatorItem*					par2: API_NavigatorView*
	APINavigator_SearchNavigatorItemID				= 'SNVI',			// par1: API_NavigatorItem*					par2: GS::Array<API_NavigatorItem>*
	APINavigator_ChangeNavigatorViewID				= 'CHNV',			// par1: API_NavigatorItem*					par2: API_NavigatorView*
	APINavigator_NewNavigatorViewID					= 'NHNV',			// par1: API_NavigatorItem*					par2: API_NavigatorView*				par3: [const GS::Guid*] (parent guid)		par4: [const GS::Guid*] (previous sibling guid)
	APINavigator_DeleteNavigatorViewID				= 'DENV',			// par1: const API_Guid*					par2: const bool*
	APINavigator_ChangeNavigatorItemID				= 'CHNI',			// par1: API_NavigatorItem*					par2: ---
	APINavigator_SetNavigatorItemPositionID			= 'SNIP',			// par1: const GS::Guid* (source)			par2: const GS::Guid* (parent)			par3: const GS::Guid* (child)
	APINavigator_CloneProjectMapItemToViewMapID		= 'CPMI',			// par1: const API_Guid* (ItemToClone)		par2: const API_Guid* (parent)			par3: API_Guid* (cloned item)

	APINavigator_CreateNavigatorVPItemID			= 'CVPI',			// par1: API_NavigatorAddOnViewPointData*	par2: ---
	APINavigator_DeleteNavigatorVPItemID			= 'DVPI',			// par1: const API_Guid*					par2: ---
	APINavigator_ChangeNavigatorVPItemID			= 'MVPI',			// par1: API_NavigatorAddOnViewPointData*	par2: ---
	APINavigator_GetNavigatorVPItemID				= 'GVPI',			// par1: API_NavigatorAddOnViewPointData*	par2: ---
	APINavigator_GetNavigatorVPRootGroupsID			= 'GVPR',			// par1: GS::Array<API_Guid>*				par2: ---
	APINavigator_GetNavigatorVPItemChildrenID		= 'GVPC',			// par1: const API_Guid*					par2: GS::Array<API_Guid>*
	APINavigator_RegisterCallbackInterfaceID		= 'RCBI'			// par1: INavigatorCallbackInterface*		par2: ---
} API_NavigatorID;


// =============================================================================
// Navigator Info
//
// =============================================================================

/**
 * @brief Enumeration of Project Navigator maps.
 * @enum API_NavigatorMapID
 * @ingroup Notification
 * @remarks This type identifier can be used as mapId in @ref API_NavigatorSet and @ref API_NavigatorItem structures.
 */
typedef enum {
	API_UndefinedMap				= 0,
	API_ProjectMap					= 1,
	API_PublicViewMap				= 2,
	API_MyViewMap					= 3,
	API_LayoutMap					= 4,
	API_PublisherSets				= 5

} API_NavigatorMapID;

#define API_FirstNavigatorMap		API_UndefinedMap
#define API_LastNavigatorMap		API_PublisherSets

/**
 * @brief Enumeration of Project Navigator items.
 * @enum API_NavigatorItemTypeID
 * @ingroup Navigator
 * @remarks This type identifier can be used as itemType in @ref API_NavigatorItem structure.
 */
typedef enum {
	API_UndefinedNavItem			= 0,
	API_ProjectNavItem				= 1,
	API_StoryNavItem				= 2,
	API_SectionNavItem				= 3,
	API_DetailDrawingNavItem		= 4,
	API_PerspectiveNavItem			= 5,
	API_AxonometryNavItem			= 6,
	API_ListNavItem					= 7,
	API_ScheduleNavItem				= 8,
	API_TocNavItem					= 9,
	API_CameraNavItem				= 10,
	API_CameraSetNavItem			= 11,
	API_InfoNavItem					= 12,
	API_HelpNavItem					= 13,
	API_LayoutNavItem				= 14,
	API_MasterLayoutNavItem			= 15,
	API_BookNavItem					= 16,
	API_MasterFolderNavItem			= 17,
	API_SubSetNavItem				= 18,
	API_TextListNavItem				= 19,
	API_ElevationNavItem			= 20,
	API_InteriorElevationNavItem	= 21,
	API_WorksheetDrawingNavItem		= 22,
	API_DocumentFrom3DNavItem		= 23,
	API_FolderNavItem				= 24,
	API_DrawingNavItem				= 25

} API_NavigatorItemTypeID;

/**
 * @brief Parameters of a project Navigator Set.
 * @struct API_NavigatorSet
 * @ingroup Navigator
 * @remarks This structure contains name, guid and root guid of a navigator set in Archicad. You can optionally obtain the publishing parameters as well, if the navigator set is a publisher set.
 * 			If the path member is not nullptr, it means the set will be published locally. If it is nullptr, then the host / dirName pair contains the Internet publishing parameters. No extra information is available for other publishing types.
 * 			Call the @ref ACAPI_Navigator_GetNavigatorSet function to get this data.
 */
struct API_NavigatorSet {

/**
 * @brief The name of navigator set.
 * @var name
 */
	char							name[128];

/**
 * @brief The own GUID of the navigator set.
 * @var guid
 */
	API_Guid						guid;

/**
 * @brief The GUID of the root.
 * @var rootGuid
 */
	API_Guid						rootGuid;

/**
 * @brief The navigator set belongs to this map.
 * @var mapId
 */
	API_NavigatorMapID				mapId;

/**
 * @brief Indicates that you need the publishing information (@c host/ @c dirname/ @c path) for the set.
 * @var wantsExtraInfo
 */
	bool							wantsExtraInfo;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	char							filler_0[3];

/**
 * @brief Contains the host name for internet publishing.
 * @var host
 */
	GS::UniString					*host;

/**
 * @brief Contains the directory name for internet publishing.
 * @var dirName
 */
	GS::UniString					*dirName;

/**
 * @brief Contains the full output path for local/LAN publishing.
 * @var path
 */
	IO::Location					*path;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	Int32							filler[3];

/**
 * @brief Output path on OpenBIMcloud (only when publishing to OpenBIMcloud, otherwise nullptr).
 * @var twFileServerPath
 */
	IO::Location					*twFileServerPath;

};

/**
 * @brief Represents a Project Navigator item.
 * @struct API_NavigatorItem
 * @ingroup Navigator
 * @remarks This structure holds the data of an item of the Project Navigator.
 * 			The structure is used with the @ref ACAPI_Navigator_GetNavigatorItem, @ref ACAPI_Navigator_GetNavigatorParentItem, @ref ACAPI_Navigator_GetNavigatorChildrenItems, @ref ACAPI_Navigator_SearchNavigatorItem and @ref ACAPI_Navigator_ChangeNavigatorItem functions.
 */
struct API_NavigatorItem {
/**
 * @brief The name of the navigator item.
 * @var uName
 */
	GS::uchar_t						uName[API_UniLongNameLen];

/**
 * @brief The name of the navigator item which contains the autotext tokens.
 * @var uAutoTextedName
 */
	GS::uchar_t						uAutoTextedName[API_UniLongNameLen];

/**
 * @brief The ID of the navigator item.
 * @var uiId
 */
	char							uiId[128];

/**
 * @brief The own GUID of the navigator item
 * @var guid
 */
	API_Guid						guid;

/**
 * @brief The database reference of the the navigator item.
 * @var db
 */
	API_DatabaseInfo				db;

/**
 * @brief Floor index the navigator item refers to. Valid only if the type of the database is floorplan [ @c itemType is @c API_StoryNavItem].
 * @var floorNum
 */
	short							floorNum;

/**
 * @brief For internal use.
 * @var vType
 */
	short							vType;

/**
 * @brief The status of the link between the navigator item and the Floor Plan
 * @var intendedPlanConn
 */
	API_CutPlanePlanConn			intendedPlanConn;

/**
 * @brief GUID of a single camera [ @c itemType is @c API_CameraNavItem] or a camera set [ @c itemType is @c API_CameraNavItem].
 * @var camId
 */
	API_Guid						camId;

/**
 * @brief The Project Navigator map wich contains this item.
 * @var mapId
 */
	API_NavigatorMapID				mapId;

/**
 * @brief Type of the item.
 * @var itemType
 */
	API_NavigatorItemTypeID			itemType;

/**
 * @brief The guid of the source navigator item. For example a View item can be the source of a Drawing or a PublisherSet item.
 * @var sourceGuid
 */
	API_Guid						sourceGuid;

/**
 * @brief The member ID of the item's owner in TeamWork mode (relevant only in View Map).
 * @var owner
 */
	Int32							owner;

/**
 * @brief Custom name of the item (relevant only in the View Map and Layout Map).
 * @var customName
 */
	bool							customName;

/**
 * @brief Custom ID of the item (relevant only in the View Map and Layout Map).
 * @var customUiId
 */
	bool							customUiId;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool							filler_2;

/**
 * @brief True when the navigator item is independent.
 * @var isIndependent
 */
	bool							isIndependent;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3[6];

};

/**
 * @brief Representation of a Navigator view item.
 * @struct API_NavigatorView
 * @ingroup Navigator
 * @remarks You can retrieve information about a view via @ref ACAPI_Navigator_GetNavigatorView and you are able to change it with @ref ACAPI_Navigator_ChangeNavigatorView function.
 */
struct API_NavigatorView {

/**
 * @brief The associated zoom box defined in model coordinates. Valid only if the @c saveZoom field is @c true.
 * @var zoom
 */
	API_Box							zoom;

/**
 * @brief The name of the model view options as UTF-8 string.
 * @var modelViewOptName
 */
	char							modelViewOptName[API_LongNameLen];

/**
 * @brief Model View option stored for this view, if custom. Valid only if the @c saveDispOpt field is @c true. Do not forget to free this pointer if not needed any more.
 * @var modelViewOpt
 */
	API_ModelViewOptions*			modelViewOpt;

/**
 * @brief The Partial Structure Display state of the view. See @c API_StructureDisplay.
 * @var structureDisplay
 */
	API_StructureDisplay			structureDisplay;

/**
 * @brief Layer combination name of the view. Valid only if the `saveLaySet` field is `true`.
 * @var layerCombination
 */
	char							layerCombination[API_AttrNameLen];

/**
 * @brief Handle to a set of layer status stored for the view. Valid only if the @c saveLaySet field is @c true and @c layerCombination is empty, otherwise it should be set to @c nullptr.
 * @var layerStats
 */
	GS::HashTable<API_AttributeIndex, API_LayerStat>*	layerStats;

/**
 * @brief The drawing scale associated with the view. Valid only if the @c saveDScale field is @c true.
 * @var drawingScale
 */
	Int32							drawingScale;

/**
 * @brief Dimension style attribute name. Valid only if the `saveDim` field is `true`.
 * @var dimName
 */	char							dimName[API_LongNameLen];

/**
 * @brief Dimensioning settings stored for this view (only if custom). Valid only if the @c saveDim field is @c true. Do not forget to free this pointer if not needed any more.
 * @var dimPrefs
 */
	API_DimensionPrefs*				dimPrefs;

/**
 * @brief Zoom box is stored in the view. If @c false, the @c zoom field does not contain valid data.
 * @var saveZoom
 */
	bool							saveZoom;

/**
 * @brief Display options are stored in the view. If @c false, the @c displayOpt field does not contain valid data.
 * @var saveDispOpt
 */
	bool							saveDispOpt;

/**
 * @brief Layer settings are stored in the view. If @c false, the @c layerCombinationand the layerStats fields do not contain valid data.
 * @var saveLaySet
 */
	bool							saveLaySet;

/**
 * @brief Drawing scale is stored in the view. If @c false, the @c drawingScalefield does not contain valid data.
 * @var saveDScale
 */
	bool							saveDScale;

/**
 * @brief Dimensioning is stored in this view. If @c false, the @c dimNameand the dimPrefs fields do not contain valid data.
 * @var saveDim
 */
	bool							saveDim;

/**
 * @brief Store the penset.
 * @var savePenSet
 */
	bool							savePenSet;

/**
 * @brief Partial Structure Display setting is stored in the view.
 * @var saveStructureDisplay
 */
	bool							saveStructureDisplay;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool							filler_2[5];

/**
 * @brief Penset name (empty if custom).
 * @var penSetName
 */
	char							penSetName[API_AttrNameLen];

/**
 * @brief Pens of the pen table (only if custom).
 * @var pens
 */
	GS::Array<API_Pen>*				pens;

/**
 * @brief If this value is true, the saved zoomBox for the view is not used when changing between views. (in View Organizer this can be set with the "Do not apply saved zooms when changing views" check)
 * @var ignoreSavedZoom
 */
	bool							ignoreSavedZoom;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	bool							filler_3[7];

/**
 * @brief The view transformation (rotation etc.).
 * @var tr
 */
	API_Tranmat						tr;

/**
 * @brief Renovation filter used by this navigator view.
 * @var renovationFilterGuid
 */
	API_Guid						renovationFilterGuid;

/**
 * @brief The currently active override combination in this navigator view (or empty string if there is no
 * 		  active override combination).
 * @var overrideCombination
 */
	GS::uchar_t						overrideCombination[API_UniLongNameLen];

/**
 * @brief 3D style name (or empty string if this is not a 3D view).
 * @var d3styleName
 */
	GS::uchar_t						d3styleName[API_UniLongNameLen];

/**
 * @brief Rendering scene name (or empty string if this is not a rendered view).
 * @var renderingSceneName
 */
	GS::uchar_t						renderingSceneName[API_UniLongNameLen];

/**
 * @brief Use photorendering in visualization (for rendered views).
 * @var usePhotoRendering
 */
	bool							usePhotoRendering;

};

/**
 * @brief Describes the type of a Navigator AddOn item.
 * @enum API_NavigatorAddOnViewPointTypeID
 * @ingroup Navigator
 */
typedef enum {
	API_NavigatorAddOnViewPointUndefinedID	= 0,
	API_NavigatorAddOnViewPointRootID		= 1,
	API_NavigatorAddOnViewPointGroupID		= 2,
	API_NavigatorAddOnViewPointNodeID		= 3

} API_NavigatorAddOnViewPointTypeID;

/**
 * @brief Determines which view settings to enable in an @ref API_NavigatorAddOnViewPointData.
 * @enum API_NavigatorViewSettingsFlags
 */
typedef enum {
	API_NavigatorViewSettingsNoAttributeID						= 0b000000000,
	API_NavigatorViewSettingsLayerAttributeID					= 0b000000001,
	API_NavigatorViewSettingsScaleAttributeID					= 0b000000010,
	API_NavigatorViewSettingsStructureDisplayAttributeID		= 0b000000100,
	API_NavigatorViewSettingsPenTableAttributeID				= 0b000001000,
	API_NavigatorViewSettingsDisplayOptionAttributeID			= 0b000010000,
	API_NavigatorViewSettingsOverrideCombinationAttributeID		= 0b000100000,
	API_NavigatorViewSettingsPlanTypeAttributeID				= 0b001000000,
	API_NavigatorViewSettingsDimensionAttributeID				= 0b010000000,
	API_NavigatorViewSettingsZoomAttributeID					= 0b100000000

} API_NavigatorViewSettingsFlags;


/**
 * @brief Describes a Navigator AddOn viewpoint root, group or leaf node.
 * @struct API_NavigatorAddOnViewPointData
 * @ingroup Navigator
 * @remarks This is not POD type.
 * 			- Do not use memset, BNZeroMemory or BNClear to initialize an object of this class. The constructors will initialize it.
 * 			- Do not use BMKillHandle or BMHandleToHandle to manage the lifetime of the data member. The constructors, destructors and assignment operators of the class will manage it.
 */
struct API_NavigatorAddOnViewPointData {

/**
 * @brief The display ID of the viewpoint.
 * @var displayId
 */
	GS::UniString						displayId;

/**
 * @brief The display name of the viewpoint.
 * @var displayName
 */
	GS::UniString						displayName;

/**
 * @brief The type of the viewpoint: root, group or leaf node. See @c API_NavigatorAddOnViewPointTypeID.
 * @var itemType
 */
	API_NavigatorAddOnViewPointTypeID	itemType;

/**
 * @brief Identifier of the icon.
 * @var iconId
 */
	Int32								iconId;

/**
 * @brief Unique ID of the viewpoint.
 * @var guid
 */
	API_Guid							guid;

/**
 * @brief Unique ID of the parent root/group of the viewpoint. The parent of a root is @c APINULLGuid.
 * @var parentGuid
 */
	API_Guid							parentGuid;

/**
 * @brief The data stored by the AddOn in this viewpoint.
 * @var data
 */
	GSHandle							data;

/**
 * @brief Specifies which view settings are enabled in this viewpoint leaf node. Not applicable for viewpoint roots or groups. The value of this member can be set by combining the flags in @c API_NavigatorViewSettingsFlags.
 * @var viewSettingsFlags
 */
	UInt32								viewSettingsFlags;

/**
 * @brief Default constructor for API_NavigatorAddOnViewPointData. Construct an undefined viewpoint.
 */
	API_NavigatorAddOnViewPointData () :
		itemType		  (API_NavigatorAddOnViewPointUndefinedID),
		iconId			  (0),
		guid			  (APINULLGuid),
		parentGuid		  (APINULLGuid),
		data			  (nullptr),
		viewSettingsFlags (API_NavigatorViewSettingsNoAttributeID)
	{
	}

/**
 * @brief Copy constructor for API_NavigatorAddOnViewPointData.
 * @param source The other API_NavigatorAddOnViewPointData object.
 */
	API_NavigatorAddOnViewPointData (const API_NavigatorAddOnViewPointData& source) :
		displayId		  (source.displayId),
		displayName		  (source.displayName),
		itemType		  (source.itemType),
		iconId			  (source.iconId),
		guid			  (source.guid),
		parentGuid		  (source.parentGuid),
		viewSettingsFlags (source.viewSettingsFlags)
	{
		data = nullptr;
		BMHandleToHandle (source.data, &data);
	}

/**
 * @brief Move constructor for API_NavigatorAddOnViewPointData.
 * @param source The other API_NavigatorAddOnViewPointData object.
 */
	API_NavigatorAddOnViewPointData (API_NavigatorAddOnViewPointData&& source) :
		displayId		  (std::move (source.displayId)),
		displayName		  (std::move (source.displayName)),
		itemType		  (std::move (source.itemType)),
		iconId			  (std::move (source.iconId)),
		guid			  (std::move (source.guid)),
		parentGuid		  (std::move (source.parentGuid)),
		viewSettingsFlags (std::move (source.viewSettingsFlags))
	{
		data = source.data;
		source.data = nullptr;
	}

/**
 * @brief Copy assignement operator for API_NavigatorAddOnViewPointData.
 * @param source The other API_NavigatorAddOnViewPointData object.
 */
	void	operator= (const API_NavigatorAddOnViewPointData& source)
	{
		displayId		  = source.displayId;
		displayName		  = source.displayName;
		itemType		  = source.itemType;
		iconId			  = source.iconId;
		guid			  = source.guid;
		parentGuid		  = source.parentGuid;
		viewSettingsFlags = source.viewSettingsFlags;

		BMKillHandle (&data);
		BMHandleToHandle (source.data, &data);
	}

/**
 * @brief Move assignement operator for API_NavigatorAddOnViewPointData.
 * @param source The other API_NavigatorAddOnViewPointData object.
 */
	void	operator= (API_NavigatorAddOnViewPointData&& source)
	{
		displayId		  = std::move (source.displayId);
		displayName		  = std::move (source.displayName);
		itemType		  = std::move (source.itemType);
		iconId			  = std::move (source.iconId);
		guid			  = std::move (source.guid);
		parentGuid		  = std::move (source.parentGuid);
		viewSettingsFlags = std::move (source.viewSettingsFlags);

		BMKillHandle (&data);

		data = source.data;
		source.data = nullptr;
	}

	~API_NavigatorAddOnViewPointData ()
	{
		BMKillHandle (&data);
	}

};


// ---------------------------------------------------------------------------------------------------------------------

#endif
