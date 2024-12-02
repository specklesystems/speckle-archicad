// *********************************************************************************************************************
// API definitions - environmental data
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

typedef enum {			// Codes for Environment functions

	APINavigator_GetNavigatorSetNumID				= 'GNSN',			// par1: Int32*								par2: ---
	APINavigator_GetNavigatorSetID					= 'GNSE',			// par1: API_NavigatorSet*					par2: Int32*
	APINavigator_GetNavigatorItemID					= 'GNIT',			// par1: const API_Guid*					par2: API_NavigatorItem*
	APINavigator_GetNavigatorParentItemID			= 'GNPI',			// par1: const API_Guid*					par2: API_NavigatorItem*
	APINavigator_GetNavigatorChildNumID				= 'GNCN',			// par1: API_NavigatorItem*					par2: Int32*
	APINavigator_GetNavigatorChildrenItemsID		= 'GNCI',			// par1: API_NavigatorItem*					par2: API_NavigatorItem***				par3: GS::Array<API_NavigatorItem>*
	APINavigator_GetNavigatorViewID					= 'GNVI',			// par1: API_NavigatorItem*					par2: API_NavigatorView*
	APINavigator_SearchNavigatorItemID				= 'SNVI',			// par1: API_NavigatorItem*					par2: API_NavigatorItem***				par3: GS::Array<API_NavigatorItem>*
	APINavigator_ChangeNavigatorViewID				= 'CHNV',			// par1: API_NavigatorItem*					par2: API_NavigatorView*
	APINavigator_NewNavigatorViewID					= 'NHNV',			// par1: API_NavigatorItem*					par2: API_NavigatorView*				par3: [const GS::Guid*] (parent and child guids)
	APINavigator_DeleteNavigatorViewID				= 'DENV',			// par1: const API_Guid*					par2: const bool*
	APINavigator_ChangeNavigatorItemID				= 'CHNI',			// par1: API_NavigatorItem*					par2: ---
	APINavigator_SetNavigatorItemPositionID			= 'SNIP',			// par1: const GS::Guid* (source)			par2: const GS::Guid* (parent)			par3: const GS::Guid* (child)
	APINavigator_CloneProjectMapItemToViewMapID		= 'CPMI',			// par1: const API_Guid* (ItemToClone)		par2: const API_Guid* (parent)			par3: API_Guid* (cloned item)

	APINavigator_CreateNavigatorVPItemID			= 'CVPI',			// par1: API_NavigatorAddOnViewPointData*	par2: ---
	APINavigator_DeleteNavigatorVPItemID			= 'DVPI',			// par1: const API_Guid*					par2: ---
	APINavigator_ChangeNavigatorVPItemID			= 'MVPI',			// par1: API_NavigatorAddOnViewPointData*	par2: ---
	APINavigator_GetNavigatorVPItemID				= 'GVPI',			// par1: API_NavigatorAddOnViewPointData*	par2: ---
	APINavigator_GetNavigatorVPRootGroupsID			= 'GVPR',			// par1: const API_Guid*					par2: GS::Array<API_Guid>*
	APINavigator_GetNavigatorVPItemChildrenID		= 'GVPC',			// par1: GS::Array<API_Guid>*				par2: ---
	APINavigator_RegisterCallbackInterfaceID		= 'RCBI'			// par1: IAPINavigator*						par2: ---
} API_NavigatorID;


// =============================================================================
// Navigator Info
//
// =============================================================================

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

typedef struct {
	char							name[128];
	API_Guid						guid;
	API_Guid						rootGuid;
	API_NavigatorMapID				mapId;
	bool							wantsExtraInfo;				// wants host/dirName or path
	char							filler_0[3];
	GS::UniString					*host;						// host name for Internet publishing
	GS::UniString					*dirName;					// directory name for Internet publishing
	IO::Location					*path;						// local output path for SaveFiles publishing (temporary if later uploaded to TW File Server)
	Int32							filler[3];
	IO::Location					*twFileServerPath;			// output path on TW File Server (when a SaveFiles publishing is set to publish onto a file server, otherwise nullptr)
} API_NavigatorSet;

typedef struct {
	GS::uchar_t						uName[API_UniLongNameLen];
	GS::uchar_t						uAutoTextedName[API_UniLongNameLen];
	char							uiId[128];
	API_Guid						guid;
	API_DatabaseInfo				db;
	short							floorNum;
	short							vType;
	API_CutPlanePlanConn			intendedPlanConn;
	API_Guid						camId;
	API_NavigatorMapID				mapId;
	API_NavigatorItemTypeID			itemType;
	API_Guid						sourceGuid;
	Int32							owner;
	bool							customName;
	bool							customUiId;
	bool							filler_2;
	bool							isIndependent;
	Int32							filler_3[6];
} API_NavigatorItem;

typedef struct {
	API_Box							zoom;								// zoom box
	char							modelViewOptName[API_LongNameLen];	// model view options
	API_ModelViewOptions*			modelViewOpt;						// model view options (only if custom)
	API_StructureDisplay			structureDisplay;
	char							layerCombination[API_AttrNameLen];
	API_LayerStat**					layerStats;							// layer settings (only if custom)
	Int32							drawingScale;						// drawing scale
	char							dimName[API_LongNameLen];			// dimStand name
	API_DimensionPrefs*				dimPrefs;							// dimensioning settings (only if custom)
	bool							saveZoom;							// store the zoom box
	bool							saveDispOpt;						// store the display options
	bool							saveLaySet;							// store the layer settings
	bool							saveDScale;							// store the drawing scale
	bool							saveDim;							// store the dimensioning
	bool							savePenSet;							// store the penset
	bool							saveStructureDisplay;
	bool							filler_2[5];
	char							penSetName[API_AttrNameLen];		// penset name (empty if custom)
	API_PenType*					pens;								// pentable (only if custom)
	bool							ignoreSavedZoom;
	bool							filler_3[7];
	API_Tranmat						tr;									// view transformation (rotation etc.)
	API_Guid						renovationFilterGuid;				// renovation filter
	GS::uchar_t						overrideCombination[API_UniLongNameLen];
	GS::uchar_t						d3styleName[API_UniLongNameLen];	// 3D style
	GS::uchar_t						renderingSceneName[API_UniLongNameLen];
	bool							usePhotoRendering;
} API_NavigatorView;

typedef enum {
	API_NavigatorAddOnViewPointUndefinedID	= 0,
	API_NavigatorAddOnViewPointRootID		= 1,
	API_NavigatorAddOnViewPointGroupID		= 2,
	API_NavigatorAddOnViewPointNodeID		= 3
} API_NavigatorAddOnViewPointTypeID;

typedef enum {
	API_NavgatorViewSettingsNoAttributeID						= 0b000000000,
	API_NavgatorViewSettingsLayerAttributeID					= 0b000000001,
	API_NavgatorViewSettingsScaleAttributeID					= 0b000000010,
	API_NavgatorViewSettingsStructureDisplayAttributeID			= 0b000000100,
	API_NavgatorViewSettingsPenTableAttributeID					= 0b000001000,
	API_NavgatorViewSettingsDisplayOptionAttributeID			= 0b000010000,
	API_NavgatorViewSettingsOverrideCombinationAttributeID		= 0b000100000,
	API_NavgatorViewSettingsPlanTypeAttributeID					= 0b001000000,
	API_NavgatorViewSettingsDimensionAttributeID				= 0b010000000,
	API_NavgatorViewSettingsZoomAttributeID						= 0b100000000
} API_NavigatorViewSettingsFlags;


struct API_NavigatorAddOnViewPointData {
	GS::UniString						displayId;
	GS::UniString						displayName;
	API_NavigatorAddOnViewPointTypeID	itemType;
	Int32								iconId;
	API_Guid							guid;
	API_Guid							parentGuid;
	GSHandle							data;
	UInt32								viewSettingsFlags;

	API_NavigatorAddOnViewPointData () :
		itemType		  (API_NavigatorAddOnViewPointUndefinedID),
		iconId			  (0),
		guid			  (APINULLGuid),
		parentGuid		  (APINULLGuid),
		data			  (nullptr),
		viewSettingsFlags (API_NavgatorViewSettingsNoAttributeID)
	{
	}

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
