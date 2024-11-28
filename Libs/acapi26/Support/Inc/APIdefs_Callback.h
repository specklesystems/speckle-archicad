// *********************************************************************************************************************
// API definitions - callback functions of the API services
//
// Module:			API
// Namespace:		-
// Contact person:	archicadapi@graphisoft.com
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef	_APIDEFS_CALLBACK_H_
#define	_APIDEFS_CALLBACK_H_

#if defined (_MSC_VER)
#pragma once
#endif


// --- Includes	--------------------------------------------------------------------------------------------------------

// own
#include "APICalls.h"
#include "APIdefs.h"
#include "API_Guid.hpp"

// GSRoot
#include "SharedPtr.hpp"
#include "HashSet.hpp"
#include "HashTable.hpp"

namespace Modeler {
	class Sight;
	typedef GS::SharedPtr<Sight>		SightPtr;
}

namespace IO { class Location; class Name; }

// --- Compiler settings -----------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------


// =============================================================================
// Menu commands
//
// =============================================================================

typedef struct  {
	API_MenuItemRef					menuItemRef;
} API_MenuParams;


// =============================================================================
// I/O Commands (Load, Save)
//
// =============================================================================

#define IO_OPEN						1
#define IO_MERGE					2
#define IO_OPENLIBPART				3
#define IO_SAVEAS					4
#define IO_SAVEAS3D					5
#define IO_SAVEASFLY3D				6
#define IO_IMPORT					7

typedef struct  {
	short 							refCon;
	short 							method;
	UInt32							fileTypeID;
	IO::Location*					fileLoc;
	IO::Location*					fileLocOnServer;
	IO::Name*						saveFileIOName;				// real name when fileLoc refers to scratch file
	bool							noDialog;					// silent mode
	bool							fromDragDrop;				// IO_MERGE file from drag-and-drop
	bool							filler_1 [6];
	API_Vector						dropOffset;					// merge and drop offset
	GSPtr							additionalData;				// for internal use
	Int32							filler_2;
	API_Guid						drawingGuid;				// drawing element guid during relink
	Int32							filler_3 [6];
} API_IOParams;


// =============================================================================
// ESYM Commands
//
// =============================================================================

#define ESYM_NEW					1
#define ESYM_EDIT					2

typedef struct {
	GSType 							signature;
	short							method;
	short							filler_1;
	Int32							libInd;
	IO::Location*					location;
	API_AddParType**				params;
	Int32							filler_2 [6];
} API_ESYMParams;


// =============================================================================
// Property commands
//
// =============================================================================

typedef enum {
	APIPropObj_None					= 0,
	APIPropObj_AssignProperty		= 1,
	APIPropObj_DisableProperty		= 2
} API_PropertyObjectCmdID;

typedef struct {
	API_PropertyObjectCmdID			cmd;
	GS::uchar_t						propertyName [API_UniLongNameLen];	// UTF16 name of the Library Part
	char							propertyUnID [128];					// unique ID string of the Library Part
} API_PropertyObjectParams;


// =============================================================================
// Notifications on project events
//
// =============================================================================

typedef enum {
	APINotify_New								= 0x00000001,
	APINotify_NewAndReset						= 0x00000002,
	APINotify_Open								= 0x00000004,
	APINotify_PreSave							= 0x00000008,
	APINotify_Save								= 0x00000010,
	APINotify_Close								= 0x00000020,
	APINotify_Quit								= 0x00000040,
	APINotify_TempSave							= 0x00000080,
	APINotify_ConvertUnId						= 0x00000100,
	APINotify_ConvertGuid						= 0x00000200,
	APINotify_ConvertLinkId						= 0x00000400,
	APINotify_ConvertDrwGuid					= 0x00000800,

	APINotify_SendChanges						= 0x00008000,
	APINotify_ReceiveChanges					= 0x00010000,

	APINotify_ChangeProjectDB					= 0x00040000,
	APINotify_ChangeWindow						= 0x00080000,
	APINotify_ChangeFloor						= 0x00100000,
	APINotify_ChangeLibrary						= 0x00200000,

	APINotify_AllInputFinished					= 0x00400000,				// Open, Merge or Drag-and_Drop finished, everything is in PLANDB/currDBRef

	APINotify_UnitChanged						= 0x00800000,				// notifies that the working units or calculation units have changed on Preferences dialogs

	APINotify_SideviewCreated					= 0x01000000,
	APINotify_SideviewRebuilt					= 0x02000000,

	APINotify_PropertyVisibilityChanged			= 0x04000000,
	APINotify_ClassificationVisibilityChanged	= 0x08000000,

	APINotify_ShowIn3DChanged					= 0x10000000
} API_NotifyEventID;

#define	API_AllProjectNotificationMask	0x00000FFF				// APINotify_New..APINotify_ConvertGuid
#define	API_AllTeamWorkNotificationMask	0x00018000				// APINotify_Share..APINotify_ChangeWorkspace
#define	API_AllChangeNotificationMask	0x033C0000				// APINotify_ChangeProjectDB..APINotify_ChangeFloor

#define	API_AllNotificationMask			0xFFFFFFFF


// =============================================================================
// Project Navigator View Events
//
// =============================================================================

typedef enum {
	APINotifyView_Inserted			= 0x00000001,
	APINotifyView_Modified			= 0x00000002,
	APINotifyView_Deleted			= 0x00000004,
	APINotifyView_Opened			= 0x00000008,
	APINotifyView_Begin				= 0x00000010,
	APINotifyView_End				= 0x00000020
} API_NotifyViewEventID;

#define	API_AllViewNotificationMask		0x000000FF

typedef struct {
	API_NotifyViewEventID			notifID;				// type of the notification
	API_NavigatorMapID				mapId;					// which navigator organizer
	API_Guid						itemGuid;				// guid of the item in string format
} API_NotifyViewEventType;


// =============================================================================
// Custom Window Events
//
// =============================================================================

typedef enum {
	APINotifyWindow_Rebuild			= 1,
	APINotifyWindow_Activate		= 2,
	APINotifyWindow_Close			= 3
} API_NotifyWindowEventID;


// =============================================================================
// Element database events
//
// =============================================================================

typedef enum {
	APINotifyElement_BeginEvents			= -1,
	APINotifyElement_EndEvents				= -2,

	APINotifyElement_New					=  1,
	APINotifyElement_Copy					=  2,
	APINotifyElement_Change					=  3,
	APINotifyElement_Edit					=  4,
	APINotifyElement_Delete					=  5,

	APINotifyElement_Undo_Created			=  11,
	APINotifyElement_Undo_Modified			=  12,
	APINotifyElement_Undo_Deleted			=  13,
	APINotifyElement_Redo_Created			=  14,
	APINotifyElement_Redo_Modified			=  15,
	APINotifyElement_Redo_Deleted			=  16,
	APINotifyElement_PropertyValueChange	=  17,
	APINotifyElement_ClassificationChange	=  18
} API_ElementDBEventID;

typedef struct {
	API_ElementDBEventID			notifID;					// type of the notification
	Int32							filler_1;
	API_Elem_Head					elemHead;					// element reference
	API_DatabaseUnId				databaseId;					// element database identifier
	Int32							filler_2[8];
} API_NotifyElementType;


// =============================================================================
// AddOnObject handling
//
// =============================================================================

typedef enum {
	GeneralAddOnObject,
	UniqueAddOnObject,
	ClientOnlyAddOnObject
} API_AddonObjectType;

typedef struct {
	API_Guid						id;
	GS::UniString*					name;
	GSHandle						data;
	API_AddonObjectType				type;
} API_AddonObject;

// --- Function prototypes ---------------------------------------------------------------------------------------------

// =============================================================================
// Main entry points
//
// =============================================================================

typedef GSErrCode	__ACENV_CALL	APIMenuCommandProc (const API_MenuParams* menuParams);
typedef GSErrCode	__ACENV_CALL	APIIOCommandProc (const API_IOParams* ioParams);
typedef GSErrCode	__ACENV_CALL	APIIO3DCommandProc (const API_IOParams* ioParams, Modeler::SightPtr sight);
typedef GSErrCode	__ACENV_CALL	APIPanelCreateProc (Int32 refCon, const void* tabControl, void* data, void** tabPage);
typedef GSErrCode	__ACENV_CALL	APIPanelDestroyProc (Int32 refCon, void* tabPage);
typedef GSErrCode	__ACENV_CALL	APIESYMCommandProc (const API_ESYMParams* esymParams);
typedef GSErrCode	__ACENV_CALL	APIModulCommandProc (GSHandle params, GSPtr resultData, bool silentMode);
typedef GSErrCode	__ACENV_CALL	APIPropertyObjectCommandProc (API_PropertyObjectParams* propertyParams);
typedef GSErrCode	__ACENV_CALL	APISettingsCreateProc (void* uiData);
typedef GSErrCode	__ACENV_CALL	APISettingsDestroyProc (void* uiData);
typedef GSErrCode	__ACENV_CALL	APIPublishFormatCommandProc (void* uiData);


// =============================================================================
// Notification manager
//
// =============================================================================

typedef GSErrCode	__ACENV_CALL	APIProjectEventHandlerProc (API_NotifyEventID notifID, Int32 param);
typedef GSErrCode	__ACENV_CALL	APIViewEventHandlerProc (const API_NotifyViewEventType* viewEvent);
typedef GSErrCode	__ACENV_CALL	APIDefaultsChangeHandlerProc (const API_ToolBoxItem* defElemType);
typedef GSErrCode	__ACENV_CALL	APIToolChangeHandlerProc (const API_ToolBoxItem* newToolMode);
typedef GSErrCode	__ACENV_CALL	APISelectionChangeHandlerProc (const API_Neig* selElemNeig);
typedef GSErrCode	__ACENV_CALL	APIAttributeReplacementHandlerProc (const API_AttributeReplaceIndexTable& table);

typedef GSErrCode	__ACENV_CALL	APIReservationChangeHandlerProc (const GS::HashTable<API_Guid, short>&	reserved,
																	 const GS::HashSet<API_Guid>&			released,
																	 const GS::HashSet<API_Guid>&			deleted);

typedef GSErrCode	__ACENV_CALL	APILockChangeHandlerProc (const API_Guid& objectId, short ownerId);

typedef GSErrCode	__ACENV_CALL	APILicenseBorrowStatusChangeHandlerProc (API_LicenseBorrowStatusTypeID licenseBorrowStatus);

typedef GSErrCode	__ACENV_CALL	APIElementEventHandlerProc (const API_NotifyElementType* elemType);

typedef GSErrCode	__ACENV_CALL	APIModulDataMergeHandlerProc (API_MDSetCmd			mode,
																  const GS::UniString&	modulName,
																  const API_ModulData*	originalInfo,
																  const API_ModulData*	toMergeInfo,
																  API_ModulData*		destInfo);

typedef GSErrCode	__ACENV_CALL	APIModulDataSaveOldFormatHandlerProc (API_FTypeID									planFileType,
																		  GS::HashTable<GS::UniString, API_ModulData*>&	modulesToSave);

typedef GSErrCode	__ACENV_CALL	APIElemSetSaveOldFormatHandlerProc	(API_FTypeID planFileType, const GSPtr dataPtr, GSPtr* oldDataPtr);


typedef GSErrCode	__ACENV_CALL	APIAddonObjectMergeHandlerProc (const GS::Array<API_AddonObject>&	sourceAddOnObjectArray);


typedef GSErrCode	__ACENV_CALL	APIAddonObjectSaveOldFormatHandlerProc (API_FTypeID						planFileType,
																			const GS::Array<API_AddonObject>&		currentFormatAddOnObjectArray,
																			GS::Array<API_AddonObject>&				oldFormatAddOnObjectArray);


typedef GSErrCode	__ACENV_CALL	APIAddonObjectConvertNewFormatHandlerProc (API_FTypeID						planFileType,
																			   const GS::Array<API_AddonObject>&	oldFormatAddOnObjectArray,
																			   GS::Array<API_AddonObject>&			currentFormatAddOnObjectArray);


typedef GSErrCode	__ACENV_CALL	APINavigatorAddOnViewPointDataMergeHandlerProc (const GS::Array<API_NavigatorAddOnViewPointData>&	sourceVPDataArray);


typedef GSErrCode	__ACENV_CALL	APINavigatorAddOnViewPointDataSaveOldFormatHandlerProc (API_FTypeID												planFileType,
																							const GS::Array<API_NavigatorAddOnViewPointData>&		currentFormatVPDataArray,
																							GS::Array<API_NavigatorAddOnViewPointData>&				oldFormatVPDataArray);


typedef GSErrCode	__ACENV_CALL	APINavigatorAddOnViewPointDataConvertNewFormatHandlerProc (API_FTypeID											planFileType,
																							   const GS::Array<API_NavigatorAddOnViewPointData>&	oldFormatVPDataArray,
																							   GS::Array<API_NavigatorAddOnViewPointData>&			currentFormatVPDataArray);

// =============================================================================
// Classification events
//
// =============================================================================

typedef enum {
	APIClassVis_IsEnabled = 0,
	APIClassVis_IsClassificationVisible = 1
} API_ClassificationVisibilityMode;

typedef bool		__ACENV_CALL	APIClassificationVisibilityHandlerProc (API_ClassificationVisibilityMode visibilityMode,
																			const GS::Array<API_Guid>& classificationGuids,
																			const API_Guid& classificationItemGuid);

// =============================================================================
// Property events
//
// =============================================================================

typedef enum {
	APIPropVis_IsEnabled = 0,
	APIPropVis_IsPropertyVisible = 1
} API_PropertyVisibilityMode;

typedef bool		__ACENV_CALL	APIPropertyVisibilityHandlerProc (	API_PropertyVisibilityMode visibilityMode,
																		const GS::Array<API_Guid>& classificationGuids,
																		const API_Guid& propertyDefinitionGuid);

// =============================================================================
// Miscellaneous callbacks
//
// =============================================================================

typedef void		__ACENV_CALL	RubberLineInfoProc (const API_RubberLineInfo* info);

typedef void		__ACENV_CALL	Get3DComponentProc (const API_Get3DComponentType* info);

typedef void		__ACENV_CALL	AddPolyNodeProc (const API_Coord3D* c);
typedef void		__ACENV_CALL	DelPolyNodeProc (void);

typedef GSErrCode	__ACENV_CALL	APIPetPaletteCallBackProc (short actValue);

typedef void		__ACENV_CALL	RoomReductionPolyProc (const API_RoomReductionPolyType* roomRed);

typedef GSErrCode	__ACENV_CALL	APIPaletteControlCallBackProc (Int32 referenceID, API_PaletteMessageID messageID, GS::IntPtr param);

typedef GSErrCode	__ACENV_CALL	APICustomWindowHandlerProc (const API_Guid& userRefId, API_NotifyWindowEventID notifID);

typedef GSErrCode	__ACENV_CALL	ShapePrimsProc (const API_PrimElement* primElem, const void* par1, const void* par2, const void* par3);

typedef GSErrCode	__ACENV_CALL	APIIFCRelationshipDataProc (GS::HashTable<API_Guid, API_IFCRelationshipData>* ifcRelationshipDataTable, const void* par1);

typedef GSErrCode	__ACENV_CALL	APINumberingGridLineProc (const API_NumberingGridLine* gridLine);

typedef GSErrCode	__ACENV_CALL	APIExternalCallBackProc (GSHandle params, GSErrCode returnCode);

typedef void		__ACENV_CALL	APICommandCallBackProc (GSHandle* paramsHandle, GSPtr resultData, GSErrCode returnCode);

typedef void		__ACENV_CALL	APIDllTermHookProc (void);

typedef void		__ACENV_CALL	APIAttributeProc (const API_Attribute& attribute, const API_AttributeDefExt& attributeDefExt, GSPtr par1);

typedef GSErrCode	__ACENV_CALL	ImportAttrProc (const IO::Location& fileName, GS::Array<GS::Pair<API_Attribute, API_AttributeDefExt*>>& result);


// =============================================================================
// Miscellaneous interfaces
//
// =============================================================================

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

class API_ElementDecomposerInterface {
public:
	virtual GSErrCode	GeneratePartElement (const API_Guid& guid, const API_ElemPartId& partId,
											 const API_Element& partElem, const API_ElementMemo& partMemo) = 0;
};

#ifdef __clang__
#pragma clang diagnostic pop
#endif


// =============================================================================
// Event handler interfaces
//
// =============================================================================


#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif


constexpr const char* AttributeEventHandlerName						= "AttributeEventHandler";
constexpr const char* AttributeFolderEventHandlerName				= "AttributeFolderEventHandler";
constexpr const char* ClassificationItemEventHandlerName			= "ClassificationItemEventHandler";
constexpr const char* ClassificationSystemEventHandlerName			= "ClassificationSystemEventHandler";
constexpr const char* PropertyGroupEventHandlerName					= "PropertyGroupEventHandler";
constexpr const char* PropertyDefinitionEventHandlerName			= "PropertyDefinitionEventHandler";
constexpr const char* GraphisoftIDEventHandlerName					= "GraphisoftIDEventHandler";
constexpr const char* EnableAllInfoDialogEventHandlerName			= "EnableAllInfoDialogEventHandler";


class API_IAttributeEventHandler;
class API_IAttributeFolderEventHandler;
class API_IClassificationItemEventHandler;
class API_IClassificationSystemEventHandler;
class API_IPropertyGroupEventHandler;
class API_IPropertyDefinitionEventHandler;
class API_IGraphisoftIDEventHandler;
class API_IEnableAllInfoDialogEventHandler;

class API_IEventNotifier {
public:
	virtual ~API_IEventNotifier () = default;

	virtual void NotifyAttributeChanges (const API_IAttributeEventHandler& eventHandler) const = 0;
	virtual void NotifyAttributeFolderChanges (const API_IAttributeFolderEventHandler& eventHandler) const = 0;
	virtual void NotifyClassificationItemChanges (const API_IClassificationItemEventHandler& eventHandler) const = 0;
	virtual void NotifyClassificationSystemChanges (const API_IClassificationSystemEventHandler& eventHandler) const = 0;
	virtual void NotifyPropertyGroupChanges (const API_IPropertyGroupEventHandler& eventHandler) const = 0;
	virtual void NotifyPropertyDefinitionChanges (const API_IPropertyDefinitionEventHandler& eventHandler) const = 0;
	virtual void NotifyGraphisoftIDChanges (const API_IGraphisoftIDEventHandler& eventHandler) const = 0;
	virtual void NotifyEnableAllDialogInfoEvent (const API_IEnableAllInfoDialogEventHandler& eventHandler) const = 0;
};


class API_IEventHandler {
public:
	virtual ~API_IEventHandler () = default;

	virtual GS::UniString		GetName () const = 0;
	virtual void				Dispatch (const API_IEventNotifier& eventNotfier) const = 0;
};


class API_IObjectEventHandler {
public:
	virtual ~API_IObjectEventHandler () = default;

	virtual void OnCreated (const GS::HashSet<API_Guid>&) const { }
	virtual void OnModified (const GS::HashSet<API_Guid>&) const { }
	virtual void OnDeleted (const GS::HashSet<API_Guid>&) const { }
};


class API_IDialogEventHandler {
public:
	virtual ~API_IDialogEventHandler () = default;

	virtual void EnableAllInfoDialog () const = 0;
};


class API_IAttributeEventHandler : public API_IEventHandler,
								   public API_IObjectEventHandler {
public:
	virtual GS::UniString GetName () const override final
	{
		return AttributeEventHandlerName;
	}

	virtual void Dispatch (const API_IEventNotifier& eventNotfier) const override final
	{
		eventNotfier.NotifyAttributeChanges (*this);
	}
};


class API_IAttributeFolderEventHandler : public API_IEventHandler,
										 public API_IObjectEventHandler {
public:
	virtual GS::UniString GetName () const override final
	{
		return AttributeFolderEventHandlerName;
	}

	virtual void Dispatch (const API_IEventNotifier& eventNotfier) const override final
	{
		eventNotfier.NotifyAttributeFolderChanges (*this);
	}
};


class API_IClassificationSystemEventHandler : public API_IEventHandler,
											  public API_IObjectEventHandler {
public:
	virtual GS::UniString GetName () const override final
	{
		return ClassificationSystemEventHandlerName; 
	}

	virtual void Dispatch (const API_IEventNotifier& eventNotfier) const override final
	{
		eventNotfier.NotifyClassificationSystemChanges (*this);
	}
};


class API_IClassificationItemEventHandler : public API_IEventHandler,
											public API_IObjectEventHandler {
public:
	virtual GS::UniString GetName () const override final
	{ 
		return ClassificationItemEventHandlerName; 
	}

	virtual void Dispatch (const API_IEventNotifier& eventNotfier) const override final
	{
		eventNotfier.NotifyClassificationItemChanges (*this);
	}
};


class API_IPropertyGroupEventHandler : public API_IEventHandler,
									   public API_IObjectEventHandler {
public:
	virtual GS::UniString GetName () const override final
	{
		return PropertyGroupEventHandlerName;
	}

	virtual void Dispatch (const API_IEventNotifier& eventNotfier) const override final
	{
		eventNotfier.NotifyPropertyGroupChanges (*this);
	}
};


class API_IPropertyDefinitionEventHandler : public API_IEventHandler,
											public API_IObjectEventHandler {
public:
	virtual GS::UniString GetName () const override final
	{
		return PropertyDefinitionEventHandlerName;
	}

	virtual void Dispatch (const API_IEventNotifier& eventNotfier) const override final
	{
		eventNotfier.NotifyPropertyDefinitionChanges (*this);
	}
};


class API_IGraphisoftIDEventHandler : public API_IEventHandler {
public:
	virtual GS::UniString GetName () const override final
	{
		return GraphisoftIDEventHandlerName;
	}

	virtual void Dispatch (const API_IEventNotifier& eventNotfier) const override final
	{
		eventNotfier.NotifyGraphisoftIDChanges (*this);
	}

	virtual void OnUserChanged () const = 0;
};


class API_IEnableAllInfoDialogEventHandler : public API_IEventHandler,
											 public API_IDialogEventHandler {
public:
	virtual GS::UniString GetName () const override final
	{
		return EnableAllInfoDialogEventHandlerName;
	}

	virtual void Dispatch (const API_IEventNotifier& eventNotfier) const override final
	{
		eventNotfier.NotifyEnableAllDialogInfoEvent (*this);
	}
};


#ifdef __clang__
#pragma clang diagnostic pop
#endif


// ---------------------------------------------------------------------------------------------------------------------

#endif
