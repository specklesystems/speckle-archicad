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

/**
 * @brief Describes the menu item that was chosen.
 * @ingroup AddOnIntegration
 * @struct API_MenuParams
 * @remarks This is the parameter of the APIMenuCommandProc callback function, identifying the menu item your add-on was called for.
 */
struct API_MenuParams {

/**
 * @brief The menu item chosen by the user. The menuItemRef.menuResID is the same what you called @ref ACAPI_MenuItem_InstallMenuHandler with, and also the same what you used in the @ref ACAPI_MenuItem_RegisterMenu as a menu number in the RegisterInterface function.
 * @var menuItemRef
 */
	API_MenuItemRef					menuItemRef;

};


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

/**
 * @brief Describes the file to work on in your callback procedure.
 * @ingroup AddOnIntegration
 * @struct API_IOParams
 * @remarks This structure is used as the parameter of the APIIOCommandProc callback function for identifying the file you should work on.
 */
struct API_IOParams {

/**
 * @brief The identifier of your file type. It's is the same what you called @ref ACAPI_AddOnIntegration_InstallFileTypeHandler with, and also the same what you used in the @ref ACAPI_AddOnIntegration_RegisterFileType as a reference number in the RegisterInterface function.
 * @var refCon
 */
	short 							refCon;

	/**
	 * @brief Tells the type of operation your add-on was called to perform; basically identifies the dialog.
	 * 		  Its value can be one of the followings: `IO_OPEN`, `IO_MERGE`, `IO_OPENLIBPART`, `IO_SAVEAS`,
	 * 		  `IO_SAVEAS3D`, `IO_SAVEASFLY3D`, `IO_IMPORT`.
	 * @var method
	 */
	short 							method;

/**
 * @brief The file type registered with the internal File Type Manager.
 * @var fileTypeID
 */
	UInt32							fileTypeID;

/**
 * @brief The location of the file in the file system.
 * @var fileLoc
 */
	IO::Location*					fileLoc;

/**
 * @brief Contains the BIMcloud location of the file without authentication info if the file was originally downloaded from BIMcloud. Only set for Save and Merge operations. nullptr otherwise.
 * @var fileLocOnServer
 */
	IO::Location*					fileLocOnServer;

/**
 * @brief Contains the Unicode name of the file entered into the Save dialog (in this case fileLoc refers to a scratch file).
 * @var saveFileIOName
 */
	IO::Name*						saveFileIOName;

/**
 * @brief Work in silent mode (for normal drag drop operations its default value is true
 * @var noDialog
 */
	bool							noDialog;

/**
 * @brief Indicates whether a merge operation (IO_MERGE method) was initiated via drag drop. In this case the dropOffset field contains the dropping coordinates.
 * @var fromDragDrop
 */
	bool							fromDragDrop;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1 [6];

/**
 * @brief At a drag and drop merge this field contains the drop position relative to project origin; in all the other cases it is null vector.
 * @var dropOffset
 */
	API_Vector						dropOffset;

/**
 * @brief Reserved for internal use.
 * @var additionalData
 */
	GSPtr							additionalData;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2;

/**
 * @brief GUID of the drawing element during relink.
 * @var drawingGuid
 */
	API_Guid						drawingGuid;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3 [6];

};


// =============================================================================
// ESYM Commands
//
// =============================================================================

#define ESYM_NEW					1
#define ESYM_EDIT					2

/**
 * @brief Describes the current external symbol your add-on can work on.
 * @ingroup LibraryPart
 * @struct API_ESYMParams
 * @remarks The is the parameter of the APIESYMCommandProc callback function, identifying the external symbol you should work on.
 */
struct API_ESYMParams {

/**
 * @brief A four-character identifier of your external symbol type. It's is the same what you called @ref ACAPI_LibraryPart_InstallESYMHandler with.
 * @var signature
 */
	GSType 							signature;

/**
 * @brief The type of the requested operation:
 * 		  |Tyype|Operation|
 * 		  |--- |--- |
 * 		  |ESYM_NEW|Archicad opened a new external symbol for your add-on; the user chose your external symbol type from the New Library Part menu.|
 * 		  |ESYM_EDIT|The user has begun editing one of your external symbols.|
 * @var method
 */
	short							method;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief The library index of the symbol your add-on was called for.
 * @var libInd
 */
	Int32							libInd;

/**
 * @brief The location of the external symbol your add-on was called for.
 * @var location
 */
	IO::Location*					location;

/**
 * @brief Additional parameters of the external symbol.
 * @var params
 */
	API_AddParType**				params;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2 [6];

};


// =============================================================================
// Property commands
//
// =============================================================================

typedef enum {
	APIPropObj_None					= 0,
	APIPropObj_AssignProperty		= 1,
	APIPropObj_DisableProperty		= 2
} API_PropertyObjectCmdID;

/**
 * @brief Defines parameters for the property handler function.
 * @ingroup AddOnIntegration
 * @struct API_PropertyObjectParams
 * @remarks See the example for APIPropertyObjectCommandProc.
 */
struct API_PropertyObjectParams {

/**
 * @brief The identifier of the command the handler was called for. Its value can be `APIPropObj_None`, `APIPropObj_AssignProperty`, or `APIPropObj_DisableProperty`.
 * @var cmd
 */
	API_PropertyObjectCmdID			cmd;

/**
 * @brief The Unicode name of the property library part.
 * @var propertyName
 */
	GS::uchar_t						propertyName [API_UniLongNameLen];

/**
 * @brief The property library part's unique ID.
 * @var propertyUnID
 */
	char							propertyUnID [128];

};


// =============================================================================
// Notifications on project events
//
// =============================================================================

/**
 * @brief Possible values for notifications on project events.
 * @ingroup ProjectOperation
 * @ingroup Notification
 * @enum API_NotifyEventID
 * @since Archicad 26
 * @remarks Refer to @ref ACAPI_ProjectOperation_CatchProjectEvent function for further details.
 */
typedef enum {
	APINotify_New								= 0x00000001,
	APINotify_NewAndReset						= 0x00000002,
	APINotify_Open								= 0x00000004,
	APINotify_PreSave							= 0x00000008,
	APINotify_Save								= 0x00000010,
	APINotify_Close								= 0x00000020,
	APINotify_Quit								= 0x00000040,
	APINotify_TempSave							= 0x00000080,

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

#define	API_AllProjectNotificationMask	0x00000FFF				// APINotify_New..APINotify_TempSave
#define	API_AllTeamWorkNotificationMask	0x00018000				// APINotify_Share..APINotify_ChangeWorkspace
#define	API_AllChangeNotificationMask	0x033C0000				// APINotify_ChangeProjectDB..APINotify_ChangeFloor

#define	API_AllNotificationMask			0xFFFFFFFF


// =============================================================================
// Project Navigator View Events
//
// =============================================================================

/**
 * @brief Possible values for notifications on Project Navigator events.
 * @ingroup ProjectOperation
 * @ingroup Notification
 * @enum API_NotifyViewEventID
 * @remarks Refer to @ref ACAPI_Notification_CatchViewEvent function for further details.
 */
typedef enum {
	APINotifyView_Inserted			= 0x00000001,
	APINotifyView_Modified			= 0x00000002,
	APINotifyView_Deleted			= 0x00000004,
	APINotifyView_Opened			= 0x00000008,
	APINotifyView_Begin				= 0x00000010,
	APINotifyView_End				= 0x00000020

} API_NotifyViewEventID;

#define	API_AllViewNotificationMask		0x000000FF

/**
 * @brief Describes the Project Navigator item the notification is coming for, and the type of the notification.
 * @ingroup Notification
 * @struct API_NotifyViewEventType
 * @remarks This is the parameter of the APIViewEventHandlerProc callback function, identifying the navigator item and the type of notification your add-on was called for. In order to receive the notifications of inserted, deleted, changed or opened items you should install an APIViewEventHandlerProc with the @ref ACAPI_Notification_CatchViewEvent function.
 */
struct API_NotifyViewEventType {

/**
 * @brief The type of the notification.
 * @var notifID
 */
	API_NotifyViewEventID			notifID;

/**
 * @brief This Project Navigator map contains the item the nofication is coming for.
 * @var mapId
 */
	API_NavigatorMapID				mapId;

/**
 * @brief The own GUID of the navigator item.
 * @var itemGuid
 */
	API_Guid						itemGuid;

};


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

/**
 * @brief Describes the cause of the element notification.
 * @ingroup Element
 * @ingroup Notification
 * @enum API_ElementDBEventID
 * @remarks This enumeration type is used in the @ref API_NotifyElementType structure.
 */
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

/**
 * @brief Describes the element the notification is coming for, and the type of the notification.
 * @ingroup Element
 * @ingroup Notification
 * @struct API_NotifyElementType
 * @remarks This is the parameter of the @ref APIElementEventHandlerProc callback function,
 * 			identifying the element and the type of notification your add-on was called for.
 * 			In order to receive the notifications of created elements you should install an
 * @ref APIElementEventHandlerProc with the @ref ACAPI_Element_CatchNewElement function. To be notified on
 * 		deleting or modifying a specified element, attach an observer to the element you are interested in with
 * @ref ACAPI_Element_AttachObserver with the appropriate flags. You should definitely not modify the
 * 		project database during `@ref APINotifyElement_Undo` and `APINotifyElement_Redo` notifications. The Notification Manager
 * 		section explains how the element related notifications are sent to the add-ons. Since each add-on can be
 * 		notified twice during the same operation, the first call is marked with a -1 index value in the
 * 		`@ref APINotifyElement_BeginEvents` notification. This helps you to distinguish the first and the second
 * 		`@ref APINotifyElement_BeginEvents` (for example if you have to keep the data synchronized with an external database).
 */
struct API_NotifyElementType {

/**
 * @brief The type of the notification.
 * @var notifID
 */
	API_ElementDBEventID			notifID;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief Element reference.
 * @var elemHead
 */
	API_Elem_Head					elemHead;

/**
 * @brief Element database identifier.
 * @var databaseId
 */
	API_DatabaseUnId				databaseId;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[8];

};


// =============================================================================
// AddOnObject handling
//
// =============================================================================

/**
 * @brief Represents the two types of an AddOnObject: general (non-unique) and unique.
 * @ingroup AddOnObject
 * @enum API_AddonObjectType
 */
typedef enum {
	GeneralAddOnObject,
	UniqueAddOnObject,
	ClientOnlyAddOnObject

} API_AddonObjectType;

/**
 * @brief Control information of a custom data stored into the project database.
 * @ingroup AddOnObject
 * @struct API_AddonObject
 * @remarks This structure is used by the AddOnObject Manager functions, for further details refer to these sections.
 */
struct API_AddonObject {

/**
 * @brief The GUID of the AddOnObject
 * @var id
 */
	API_Guid						id;

/**
 * @brief The name of the AddOnObject
 * @var name
 */
	GS::UniString*					name;

/**
 * @brief User specified data (cannot be nullptr).
 * @var data
 */
	GSHandle						data;

/**
 * @brief Whether the AddOnObject is general (non-unique) or unique.
 * @var type
 */
	API_AddonObjectType				type;

};

// --- Function prototypes ---------------------------------------------------------------------------------------------

// =============================================================================
// Main entry points
//
// =============================================================================

/**
 * @brief User supplied callback procedure for handling menu commands.
 * @ingroup AddOnIntegration
 * @param menuParams [in] This structure contains the various parameters identifying the menu command.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This is the function which will be called when your add-on installed it with @ref ACAPI_MenuItem_InstallMenuHandler. For tool type add-ons, this is the replacement for the original DoCommand function.
 */
typedef GSErrCode APIMenuCommandProc (const API_MenuParams* menuParams);

/**
 * @brief User supplied callback procedure for handling I/O operations.
 * @ingroup AddOnIntegration
 * @param ioParams [in] This structure contains the various parameters identifying the file to be opened or saved.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This is the function which will be called when your add-on installed it with @ref ACAPI_AddOnIntegration_InstallFileTypeHandler.
 * 			From Archicad 19 you have to enclose the element creation creating in an undoable command scope during a merge file operation. In case you pass empty string parameter to @ref ACAPI_CallUndoableCommand, Archicad replaces it with the default "Paste" undo string.
 * 			From Archicad 9 merge and open operations can be initiated also with drag drop:
 * 			- dropping a file of a registered type onto the frame window (on Windows) results an IO_OPEN method call
 * 			- dropping a file of a registered type onto the visible client area of a drawing (floorplan, section, detail) window generates an IO_MERGE operation. In this case the fromDragDrop flag of @ref API_IOParams is set, and the dropOffset field contains the vector that points to the dropping position from the origin. The false value in the noDialog parameter means that the drag drop operation was performed with the right mouse button or with pressing a modifier key (Ctrl on Windows, Alt on the Macintosh).
 */
typedef GSErrCode APIIOCommandProc (const API_IOParams* ioParams);

/**
 * @brief User supplied callback procedure for handling I/O operations.
 * @ingroup AddOnIntegration
 * @param ioParams [in] This structure contains the various parameters identifying the file to be opened or saved.
 * @param sight [in] The 3D sight pointer.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This is the function which will be called when your add-on installed it with @ref ACAPI_AddOnIntegration_InstallFileTypeHandler3D.
 */
typedef GSErrCode APIIO3DCommandProc (const API_IOParams* ioParams, Modeler::SightPtr sight);

/**
 * @brief Callback procedure for creating custom tabpages.
 * @ingroup AddOnIntegration
 * @param refCon [in] reference number passed by the panel registration function
 * @param tabControl [in] pointer to the constructed DG::TabControl dialog item
 * @param data [in] pointer to an interface which provides access to the user data
 * @param tabPage [out] pointer to the tabpage object instance created in the callback function
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks When the additional panel is being created, a callback function is called which lets the add-on initialize the tabpage item with the associated user data and an attached observer to it.
 * 			Install this handler function with @ref ACAPI_AddOnIntegration_InstallPanelHandler in order to be called to create your tabpage identified with refCon and attach the observer to it when the settings dialog is being constructed.
 */
typedef GSErrCode APIPanelCreateProc (Int32 refCon, const void* tabControl, void* data, void** tabPage);

/**
 * @brief Callback procedure for destroying custom tabpages.
 * @ingroup AddOnIntegration
 * @param refCon [in] reference number passed by the panel registration function
 * @param tabPage [in] pointer to the tabpage object instance
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks When the additional panel is being destroyed, a callback function is called in order to detach the tabpage observer, destruct the tabpage item, and free the associated user data.
 * 			Install this handler function with @ref ACAPI_AddOnIntegration_InstallPanelHandler in order to be called to detach the observer and destroy your tabpage identified with refCon when the settings dialog closes.
 */
typedef GSErrCode APIPanelDestroyProc (Int32 refCon, void* tabPage);

/**
 * @brief User supplied callback function for handling external symbols.
 * @ingroup LibraryPart
 * @ingroup AddOnIntegration
 * @param esymParams [in] This structure contains the various parameters identifying the external symbol (type, index) and the type of operation (new/edit).
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This is the function which will be called when your add-on installed it with @ref ACAPI_LibraryPart_InstallESYMHandler.
 */
typedef GSErrCode APIESYMCommandProc (const API_ESYMParams* esymParams);

/**
 * @brief User supplied callback procedure for handling calls from other add-ons.
 * @ingroup AddOnIntegration
 * @param params [in/out] This structure contains the parameters of the command passed onto your add-on.
 * @param resultData [out] This structure contains parameters passed back to the caller add-on.
 * @param silentMode [in] This flag tells the add-on to work "silently", i.e. skip all dialogs and warning messages.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks Your add-on can provide services to other add-ons by calling @ref ACAPI_AddOnAddOnCommunication_RegisterSupportedService in its @ref RegisterInterface function. After that any add-on can call your add-on which knows the command's interface; and this function will be the entry point of your add-on in this case.
 */
typedef GSErrCode APIModulCommandProc (GSHandle params, GSPtr resultData, bool silentMode);

/**
 * @brief Callback function to handle the different property assignments.
 * @ingroup AddOnIntegration
 * @ingroup Property
 * @param propertyParams [in] the parameters of the property assignment.
 * @return
 * 			- NoError - The function has completed with success.
 */
typedef GSErrCode APIPropertyObjectCommandProc (API_PropertyObjectParams* propertyParams);

/**
 * @brief Callback procedure for handle settings dialog create event.
 * @ingroup AddOnIntegration
 * @param uiData [in/out] pointer to the tool UI data. This UI data can be used to get the current settings and to attach an observer which monitors changes of the settings dialog.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks When the settings dialog is being created, the callback function is called which lets the add-on get the current settings and attach an observer to the tool UI data.
 * 			Install this handler function with @ref ACAPI_AddOnIntegration_InstallSettingsHandler.
 */
typedef GSErrCode APISettingsCreateProc (void* uiData);

/**
 * @brief Callback procedure for handle settings dialog destroy event.
 * @ingroup AddOnIntegration
 * @param uiData [in/out] pointer to the tool UI data.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks When the settings dialog is being destroyed, a callback function is called in order to detach tool UI data observer.
 * 			Install this handler function with @ref ACAPI_AddOnIntegration_InstallSettingsHandler.
 */
typedef GSErrCode APISettingsDestroyProc (void* uiData);

/**
 * @brief Callback procedure for handle publish format command.
 * @ingroup AddOnIntegration
 * @param uiData [in/out] pointer to the tool UI data.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks When the publish called from a type, then this function will be called.
 */
typedef GSErrCode APIPublishFormatCommandProc (void* uiData);


// =============================================================================
// Notification manager
//
// =============================================================================

/**
 * @brief Callback function to receive notifications on changes of the project.
 * @ingroup ProjectOperation
 * @ingroup Notification
 * @param notifID [in] The type of the project event the notification is for.
 * @param param [in] This parameter is valid only if the notifID is @c APINotify_ChangeLibrary. If an
 * 				individual library part has changed in the library (e.g. it was added to the library), then this
 * 				parameter contains the index of that library part. This parameter is also valid if `notifID` is
 * 				`APINotify_ChangeProjectDB`, and contains a code for the cause of the event.
 *
 * 				|param|Event cause|
 * 				|--- |--- |
 * 				|0|Other|
 * 				|1|Floor(s) edited|
 * 				|2|Merge|
 *
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This is the function which will be called when your add-on requested notifications on project
 * 			events with @ref ACAPI_ProjectOperation_CatchProjectEvent.
 */
typedef GSErrCode APIProjectEventHandlerProc (API_NotifyEventID notifID, Int32 param);

/**
 * @brief User supplied callback function for handling changes of Project Navigator items.
 * @ingroup Notification
 * @param viewEvent [in] This structure identifies the Project Navigator item and the event the add-on is called for.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This is the function which will be called when your add-on requested notifications on Project Navigator item changes with @ref ACAPI_Notification_CatchViewEvent.
 */
typedef GSErrCode APIViewEventHandlerProc (const API_NotifyViewEventType* viewEvent);

/**
 * @brief Callback procedure to receive notifications on changes in element defaults.
 * @ingroup Element
 * @ingroup Notification
 * @param defElemType [in] The element type the notification is coming for.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This is the function which will be called when your add-on requested notifications on element default chnages with @ref ACAPI_Element_CatchChangeDefaults.
 */
typedef GSErrCode APIDefaultsChangeHandlerProc (const API_ToolBoxItem* defElemType);

/**
 * @brief Callback function to handle changes in the toolbox.
 * @ingroup Notification
 * @param newToolMode [in] The toolbox mode the user switched to.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This is the function which will be called when your add-on requested notifications on toolbox item changes with @ref ACAPI_Notification_CatchToolChange.
 */
typedef GSErrCode APIToolChangeHandlerProc (const API_ToolBoxItem* newToolMode);

/**
 * @brief User supplied callback procedure for handling selection changes.
 * @ingroup Notification
 * @ingroup Selection
 * @param selElemNeig [in] This structure identifies the last selected element.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This is the function which will be called when your add-on installed it with @ref ACAPI_Notification_CatchSelectionChange.
 */
typedef GSErrCode APISelectionChangeHandlerProc (const API_Neig* selElemNeig);

/**
 * @brief User supplied callback procedure for handling attribute replacements.
 * @ingroup Notification
 * @ingroup Attribute
 * @since Archicad 25
 * @param table [in] List of attributes replaced. The hash key in the hash table is the type of attribute (material, profile etc.), the paired value is another hash table, which holds the old (deleted) attribute indices as keys, and the replacement attribute indices as values.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This callback function should be implemented and set with @ref ACAPI_Notification_CatchAttributeReplacement in order to receive notifications of attribute replacements.
 */
typedef GSErrCode APIAttributeReplacementHandlerProc (const API_AttributeReplaceIndexTable& table);

/**
 * @brief User supplied callback procedure for handling element reservation changes.
 * @ingroup Notification
 * @param reserved [in] List of elements recently reserved. The hash key in the hash table is the element guid, the paired value is the Teamwork owner identifier of the member who reserved the element.
 * @param released [in] List of elements recently released.
 * @param deleted [in] List of elements deleted during the recent Teamwork operations. Element deletions are reported when the member who deleted the elements sends the changes to the BIM Server.
 * @return
 * 			- NoError - The function has completed with success.
 */
typedef GSErrCode APIReservationChangeHandlerProc (const GS::HashTable<API_Guid, short>&	reserved,
																	 const GS::HashSet<API_Guid>&			released,
																	 const GS::HashSet<API_Guid>&			deleted);

/**
 * @brief User supplied callback procedure for handling reservation changes of lockable objects.
 * @ingroup Notification
 * @param objectId [in] Identifies the lockable object set that has been reserved or released. The available identifiers are listed at the description of lockable object sets.
 * @param ownerId [in] The identifier of the locker team member who obtained the reservation, or 0 if the lockable object got released.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This callback function should be implemented and set with @ref ACAPI_Notification_CatchLockableReservationChange in order to receive notifications of reservation changes of lockable objects.
 * 			You can retrieve information of the members with the @ref ACAPI_Teamwork_ProjectSharing environment function. Note that the handler receives reservation changes effected by the current team member as well.
 * 			In the reservation change handler try to avoid calling functions that would modify the database.
 */
typedef GSErrCode APILockChangeHandlerProc (const API_Guid& objectId, short ownerId);

/**
 * @brief User supplied callback procedure for handling license borrowing status changes.
 * @ingroup LicenseInfo
 * @ingroup Notification
 * @param licenseBorrowStatus [out] The status of license borrowing, can be @c API_LicenseBorrowed or @c API_LicenseReturned.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This notification comes when the user borrows or returns a license, and allows you to act accordingly.
 */
typedef GSErrCode APILicenseBorrowStatusChangeHandlerProc (API_LicenseBorrowStatusTypeID licenseBorrowStatus);

/**
 * @brief User supplied callback function for handling changes in elements.
 * @ingroup Element
 * @ingroup Notification
 * @param elemType [in] This structure contains the various parameters identifying the element the notification is for.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This is the function which will be called when your add-on attached an observer to an element with @ref ACAPI_Element_AttachObserver, i.e. you are interested in changes to an element. This is a common entry point to your add-on for all observed elements; the element in question is passed in the elemType parameter.
 * 			The meaning of the notification parameters are desrcribed at the @ref API_NotifyElementType structure.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_CatchNewElement-Example-Snippet
 */
typedef GSErrCode APIElementEventHandlerProc (const API_NotifyElementType* elemType);

/**
 * @brief User supplied callback procedure for handling module data merge operations.
 * @ingroup AddOnIntegration
 * @param mode [in] The operation the add-on is called for.
 * @param modulName [in] Identifier name of the modul data (for modules stored in previous versions this parameter is always empty string).
 * @param originalInfo [in] The original module data in the to which data has to be merged into.
 * @param toMergeInfo [in] The incoming module data.
 * @param destInfo [out] The result module data. Your add-on should put the result of the merge in here.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This is the function to be called when two conflicting modules need to be merged by your add-on. The handler function pointer must be passed with @ref ACAPI_AddOnIntegration_InstallModulDataMergeHandler.
 * 			It is also necessary to register this functionality of the add-on with calling @ref ACAPI_AddOnIntegration_RegisterModulDataHandler.
 * 			The details of the notification process are described in the ModulData Manager section.
 */
typedef GSErrCode APIModulDataMergeHandlerProc (API_MDSetCmd			mode,
																  const GS::UniString&	modulName,
																  const API_ModulData*	originalInfo,
																  const API_ModulData*	toMergeInfo,
																  API_ModulData*		destInfo);

/**
 * @brief User supplied callback procedure for converting modules into previous format.
 * @ingroup AddOnIntegration
 * @param planFileType [in] The old format plan version the project is being saved. In Archicad 13 this can be only @c APIFType_PlanFile1200.
 * @param modulesToSave [out] A hash table to retrieve the converted module data.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks In order to save the add-on's moduldata in the proper format into a previous version project file, you need to implement this callback function, and pass it to Archicad with @ref ACAPI_AddOnIntegration_InstallModulDataSaveOldFormatHandler during the Initialize phase. It is also necessary to notify Archicad about this capability of the add-on by calling @ref ACAPI_AddOnIntegration_RegisterModulDataHandler from the @ref RegisterInterface function.
 * 			This handler function is called whenever the user saves the project into an older format, and tha add-on has any moduldata stored currently into the project. The data should be constructed according to the required version into a dynamically allocated @ref API_ModulData structure, and the pointer of this structure should be pushed into the modulesToSave table. Notice that more modules can be added, should be identified with different names. In Archicad versions prior to 13 were able to store only one moduldata per add-on, this moduldata should be stored with empty string identifier ("").
 * 			The memory allocated for the converted moduldata by the add-on's handler function will be released by the caller application.
 * 			For further details of the notification process refer to the ModulData Manager section.
 */
typedef GSErrCode APIModulDataSaveOldFormatHandlerProc (API_FTypeID									planFileType,
																		  GS::HashTable<GS::UniString, API_ModulData*>&	modulesToSave);

/**
 * @brief User supplied callback function for handling backward conversion on user data attached to elements
 * @ingroup AddOnIntegration
 * @param planFileType [in] File type's ID of the save process
 * @param dataPtr [in] Pointer to the attached user data
 * @param oldDataPtr [out] Pointer to the backward converted user data
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks @c oldDataPtr is nullptr on call, and should be allocated in the function. If it is nullptr on return, the used data will be deleted from the saved plan.
 */
typedef GSErrCode APIElemSetSaveOldFormatHandlerProc	(API_FTypeID planFileType, GSConstPtr dataPtr, GSPtr* oldDataPtr);

/**
 * @brief User supplied callback procedure for handling AddOnObject merge operations.
 * @ingroup AddOnObject
 * @typedef APIAddonObjectMergeHandlerProc
 * @param sourceAddOnObjectArray [in] The list of the source AddOnObjects.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This is the function to be called when a file merge operation is performed.
 * 			The handler function should merge the source objects into the project database by calling AddOnObject-related API functions (e.g. @ref ACAPI_AddOnObject_ModifyObject).
 */
typedef GSErrCode APIAddonObjectMergeHandlerProc (const GS::Array<API_AddonObject>&	sourceAddOnObjectArray);

/**
 * @brief User supplied callback procedure for converting AddOnObjects into previous format.
 * @ingroup AddOnObject
 * @param planFileType [in] The old format plan version the project is being saved.
 * @param currentFormatAddOnObjectArray [in] AddOnObject data in current format.
 * @param oldFormatAddOnObjectArray [out] Array for the converted AddOnObject data in old format.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks In order to save the add-on's AddOnObject data in the proper format into a previous version project file, you need to implement this callback function, and pass it to Archicad with @ref ACAPI_AddOnObject_InstallAddOnObjectSaveOldFormatHandler during the Initialize phase. It is also necessary to notify Archicad about this capability of the add-on by calling @ref ACAPI_AddOnObject_RegisterAddOnObjectHandler from the RegisterInterface function.
 */
typedef GSErrCode APIAddonObjectSaveOldFormatHandlerProc (API_FTypeID						planFileType,
																			const GS::Array<API_AddonObject>&		currentFormatAddOnObjectArray,
																			GS::Array<API_AddonObject>&				oldFormatAddOnObjectArray);

/**
 * @brief User supplied callback procedure for converting AddOnObjects into current format.
 * @ingroup AddOnObject
 * @param planFileType [in] The original version of the plan of the project is being opened.
 * @param oldFormatAddOnObjectArray [in] AddOnObject data in original format.
 * @param currentFormatAddOnObjectArray [out] Array for the converted AddOnObject data in current format.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks In order to convert the add-on's AddOnObject data into current format, you need to implement this callback function, and pass it to Archicad with @ref ACAPI_AddOnObject_InstallAddOnObjectConvertNewFormatHandler during the @ref Initialize phase. It is also necessary to notify Archicad about this capability of the add-on by calling @ref ACAPI_AddOnObject_RegisterAddOnObjectHandler from the @ref RegisterInterface function.
 */
typedef GSErrCode APIAddonObjectConvertNewFormatHandlerProc (API_FTypeID						planFileType,
																			   const GS::Array<API_AddonObject>&	oldFormatAddOnObjectArray,
																			   GS::Array<API_AddonObject>&			currentFormatAddOnObjectArray);

/**
 * @brief User supplied callback procedure for handling Navigator AddOn viewpoint merge operations.
 * @ingroup AddOnIntegration
 * @param sourceVPDataArray [in] The list of the Navigator AddOn viewpoints to be merged. These viewpoint roots, groups or leaf nodes come from the merged plan file.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function is called by Archicad when a file merge operation is performed.
 * 			The handler function should merge the source objects into the project database by calling Navigator AddOn viewpoint related API functions, e.g. @ref ACAPI_Navigator_CreateNavigatorVPItem, @ref ACAPI_Navigator_ChangeNavigatorVPItem.
 */
typedef GSErrCode APINavigatorAddOnViewPointDataMergeHandlerProc (const GS::Array<API_NavigatorAddOnViewPointData>&	sourceVPDataArray);

/**
 * @brief User supplied callback procedure for converting Navigator AddOn viewpoints into older format.
 * @ingroup AddOnIntegration
 * @param planFileType [in] The old format plan version, the project is being saved into.
 * @param currentFormatVPDataArray [in] Navigator AddOn viewpoints in current format.
 * @param oldFormatVPDataArray [out] Navigator AddOn viewpoints in old format. This will be saved into the old format plan.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks In order to save the Navigator AddOn viewpoints into a previous version project file, you need to implement this callback function, and install it with @ref ACAPI_AddOnIntegration_InstallNavigatorAddOnViewPointDataSaveOldFormatHandler in the Initialize function. It is also necessary to call @ref ACAPI_AddOnIntegration_RegisterNavigatorAddOnViewPointDataHandler from the @ref RegisterInterface function.
 * 			This handler function is called by Archicad whenever the user saves the project into an older format.
 * 			Inside the function the converted viewpoints should be constructed in @ref API_NavigatorAddOnViewPointData structures in the format required by the previous version of this AddOn, and these structures should be pushed into @c oldFormatVPDataArray. When Archicad calls this function, it passes an empty @c oldFormatVPDataArray.
 * 			If you need to delete a Navigator AddOn viewpoint (e.g. it cannot be converted to previous version) then simply do not push it into @c oldFormatVPDataArray. Note, that if you do not push a root or group, all its descendants will be deleted, even if some descendants were pushed into @c oldFormatVPDataArray. If you push a viewpoint data with an invalid guid (i.e. one that does not designate an existing root, group or leaf node), it will be skipped, and not created. Order of the items in @c oldFormatVPDataArray is irrelevant.
 * 			The hierarchy cannot be changed during conversion. The parentGuid of the pushed structures will be ignored.
 * 			The item type of the Navigator viewpoints cannot be changed during conversion. The itemType of the pushed structures will be ignored.
 */
typedef GSErrCode APINavigatorAddOnViewPointDataSaveOldFormatHandlerProc (API_FTypeID												planFileType,
																							const GS::Array<API_NavigatorAddOnViewPointData>&		currentFormatVPDataArray,
																							GS::Array<API_NavigatorAddOnViewPointData>&				oldFormatVPDataArray);

/**
 * @brief User supplied callback procedure for converting Navigator AddOn viewpoints into current format.
 * @ingroup AddOnIntegration
 * @param planFileType [in] The old format plan version being opened.
 * @param oldFormatVPDataArray [in] Navigator AddOn viewpoints in old format.
 * @param currentFormatVPDataArray [out] Navigator AddOn viewpoints in current format. These will be visible after the plan finished opening.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks In order to convert older version Navigator AddOn viewpoints into current version during plan file opening, you need to implement this callback function, and install it with @ref ACAPI_AddOnIntegration_InstallNavigatorAddOnViewPointDataConvertNewFormatHandler in the @ref Initialize function. It is also necessary to call @ref ACAPI_AddOnIntegration_RegisterNavigatorAddOnViewPointDataHandler from the @ref RegisterInterface function.
 * 			This handler function is called by Archicad whenever the user opens a plan file, that is in older format.
 * 			Inside the function the converted viewpoints should be constructed in @ref API_NavigatorAddOnViewPointData structures in the format required by current version of this AddOn, and these structures should be pushed into @c currentFormatVPDataArray. When Archicad calls this function, it passes an empty @c currentFormatVPDataArray.
 * 			If you need to delete a Navigator AddOn viewpoint (e.g. it cannot be converted to current version) then simply do not push it into @c currentFormatVPDataArray. Note, that if you do not push a root or group, all its descendants will be deleted, even if some descendants were pushed into currentFormatVPDataArray. If you push a viewpoint data with an invalid guid (i.e. one that does not designate an existing root, group or leaf node), it will be skipped, and not created. Order of the items in @c currentFormatVPDataArray is irrelevant.
 * 			The hierarchy cannot be changed during conversion. The parentGuid of the pushed structures will be ignored.
 * 			The item type of the Navigator viewpoints cannot be changed during conversion. The itemType of the pushed structures will be ignored.
 */
typedef GSErrCode APINavigatorAddOnViewPointDataConvertNewFormatHandlerProc (API_FTypeID											planFileType,
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

/**
 * @brief Callback function to handle the visibility of a classification.
 * @ingroup AddOnIntegration
 * @param visibilityMode [in] specifies what should the callback function return. Has one of the following values:
 * 						 |API_ClassificationVisibilityMode|Meaning|
 * 						 |--- |--- |
 * 						 |APIClassVis_IsEnabled|The callback function should return true if the visibility handling is enabled.|
 * 						 |APIClassVis_IsClassificationVisible|The callback function should return true if the given classification is visible.|
 * @param classificationGuids [in] the classification guids of the current element.
 * @param classificationItemGuid [in] the guid of the current classification.
 * @return
 * 			- true - The result if it was successfull.
 */
typedef bool APIClassificationVisibilityHandlerProc (API_ClassificationVisibilityMode visibilityMode,
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

/**
 * @brief Callback function to handle the visibility of a property.
 * @ingroup Property
 * @ingroup AddOnIntegration
 * @param visibilityMode [in] specifies what should the callback function return. Has one of the following values:
 * 						 |API_PropertyVisibilityMode|Meaning|
 * 						 |--- |--- |
 * 						 |APIPropVis_IsEnabled|The callback function should return true if the visibility handling is enabled.|
 * 						 |APIPropVis_IsPropertyVisible|The callback function should return true if the given property is visible.|
 * @param classificationGuids [in] the classification guids of the current element.
 * @param propertyDefinitionGuid [in] the guid of the current property.
 * @return
 * 			- bool - The result.
 */
typedef bool APIPropertyVisibilityHandlerProc (	API_PropertyVisibilityMode visibilityMode,
																		const GS::Array<API_Guid>& classificationGuids,
																		const API_Guid& propertyDefinitionGuid);

// =============================================================================
// Miscellaneous callbacks
//
// =============================================================================


/**
 * @brief Callback function for custom feedback drawing.
 * @ingroup UserInput
 * @param info Information on the actual input state.
 * @remarks You should implement this function if you have to give graphical feedback for the input operation invoked from your API tool add-on. This callback routine should be passed as a parameter when calling the @ref ACAPI_UserInput_GetPoint, @ref ACAPI_UserInput_GetLine and @ref ACAPI_UserInput_GetArc interface functions. During the input process your procedure is called repeatedly as the mouse moves. In the info parameter you get the actual mouse coordinate and the current drawing phase. Call the @ref ACAPI_UserInput_DrawRubberLine interface function to draw your rubber lines. The lines are drawn in XOR mode, therefore you can use the same code for both the drawing and erasing phases when calling back.
 * 			From Archicad 9 the z coordinates are retrieved even when the input plane has not been defined. The height value can be non-zero if the cursor is on one of the neigs of a three-dimensional element, or gravity method is switched on for the element type the cursor is currently cruising above.
 */
typedef void RubberLineInfoProc (const API_RubberLineInfo* info);

/**
 * @brief Callback function for getting elem informations online (realtime).
 * @ingroup UserInput
 * @param info Information on the actual input state.
 * @remarks None.
 */
typedef void Get3DComponentProc (const API_Get3DComponentType* info);

/**
 * @brief Callback function for custom feedback while editing polygons.
 * @param c [out] Actual mouse coordinate.
 * @remarks You should implement this function if you have to give graphical feedback for the input operation invoked from your API tool add-on. This callback routine should be passed as a parameter when calling the @ref ACAPI_UserInput_GetPoly interface function. During the input process your procedure is called when the user adds a new node to the polygon. In the c parameter you get the coordinate of the node.
 */
typedef void AddPolyNodeProc (const API_Coord3D* c);

/**
 * @brief Callback function for custom feedback while editing polygons.
 * @remarks You should implement this function if you have to give graphical feedback for the input operation invoked from your API tool add-on. This callback routine should be passed as a parameter when calling the @ref ACAPI_UserInput_GetPoly interface function. During the input process your procedure is called when the user deletes a node from the polygon.
 */
typedef void DelPolyNodeProc (void);

/**
 * @brief User supplied callback procedure during pet palette input.
 * @ingroup Dialog
 * @param actValue [in] The current value of the pet palette control.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks When you open a pet palette with the @ref ACAPI_Dialog_PetPalette @c ACAPI_Interface function, this callback procedure will be called whenever the user chooses a new item on the pet palette.
 */
typedef GSErrCode APIPetPaletteCallBackProc (short actValue);

/**
 * @brief Callback function to get reduction polygons of a room.
 * @ingroup Element
 * @param roomRed [out] Data of a room reduction polygon.
 * @remarks You should implement this function and pass its address to the @ref ACAPI_Element_RoomReductions function as a callback function if you want Archicad to send the polygons which reduce a room area.
 * 			Archicad will send you all the area (polygon) which reduce the room area. Many information is provided, the polygon itself, the area, the reduction percent, and the type of the parent element.
 * 			See @ref API_RoomReductionPolyType for more details. Since Archicad 18, the first dummy element has been removed.
 */
typedef void RoomReductionPolyProc (const API_RoomReductionPolyType* roomRed);

/**
 * @brief User supplied callback function for handling special messages for modeless palettes.
 * @ingroup AddOnIntegration
 * @param referenceID [in] The unique ID that identifies the modeless palette.
 * @param messageID [in] Event to be handled in the palette control callback procedure.
 * @param param [out] Return parameter, used for @c APIPalMsg_IsPaletteVisible.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks You can register this function with @ref ACAPI_RegisterModelessWindow. From now on, it will be your responsibility to adjust the behavior of your palette to the other palettes.
 * 			The following types of events will come for your custom window:
 * 			|Message type|Description|
 * 			|--- |--- |
 * 			|APIPalMsg_ClosePalette|The API asks the add-on to close its palette.|
 * 			|APIPalMsg_HidePalette_Begin|Your palette should be hidden for some reason, e.g. the user chose Hide All Palettes from the menu.|
 * 			|APIPalMsg_HidePalette_End|The palette can be shown again if needed.|
 * 			|APIPalMsg_DisableItems_Begin|Certain palette items should be disabled, because the user is performing an input. This is necessary because you shouldn't make any modifications to the database during input.|
 * 			|APIPalMsg_DisableItems_End|The reason behind APIPalMsg_DisableItems_Begin is gone; you can enable the items on the palette.|
 * 			|APIPalMsg_OpenPalette|Sent when the palette should be opened automatically as set in the Work Environment. Your palette should pass a GUID when created: DG::Palette (resourceId, paletteGuid) to make this work.|
 * 			|APIPalMsg_IsPaletteVisible|The Work Environment queries the palette for its visibility status on closing the current document/quitting the application. If you return true in param (really a bool*), then Archicad will send a APIPalMsg_OpenPalette to your add-on on next launch, so that you can re-open your add-on's palette.|
 */
typedef GSErrCode APIPaletteControlCallBackProc (Int32 referenceID, API_PaletteMessageID messageID, GS::IntPtr param);

/**
 * @brief User supplied callback function for handling events in windows opened by the add-on.
 * @ingroup Window
 * @ingroup Database
 * @param userRefId [in] The reference GUID of the custom window, as supplied to @ref ACAPI_Window_NewWindow.
 * @param notifID [in] The type of the event for the custom window.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function will be called when installed with @ref ACAPI_Window_NewWindow.
 * 			The following types of events will come for your custom window:
 * 			|Event type|Description|
 * 			|--- |--- |
 * 			|APINotifyWindow_Rebuild|The user chose Rebuild from the menu.|
 * 			|APINotifyWindow_Activate|Your window was activated.|
 * 			|APINotifyWindow_Close|The user closed your window.|
 */
typedef GSErrCode APICustomWindowHandlerProc (const API_Guid& userRefId, API_NotifyWindowEventID notifID);

/**
 * @brief Primitive drawing function for elements and library parts.
 * @ingroup DrawingPrimitive
 * @param primElem The primitive element to draw; can also contain control codes.
 * @param par1 First parameter for drawing the element (can be nullptr).
 * @param par2 Second parameter for drawing the element (can be nullptr).
 * @param par3 Third parameter for drawing the element (can be nullptr).
 * @return
 * 			- NoError - The element was drawn successfully.
 * 			- APINOTIFY_NODATA - Supress hierarchical decomposition.
 * 			- APINOTIFY_OWN_MEMORY_HANDLER - Tells the API that your add-on took over the ownership of the passed coords, pends and parcs array. For lines, polylines and polygons only.
 * 			- APIERR_GENERAL - Any user-defined error can be returned.
 * @remarks This function is used to draw the primitive elements. As such, it plugs into the server application's drawing routines. It can also be used to save the contents of a plan into an external file.
 * 			|API_PrimTypeID|par1|par2|par3|
 * 			|--- |--- |--- |--- |
 * 			|API_PrimPointID|nullptr|nullptr|nullptr|
 * 			|API_PrimLineID|nullptr|nullptr|nullptr|
 * 			|API_PrimArcID|nullptr|nullptr|nullptr|
 * 			|API_PrimTextID|nullptr|(unsigned short*) pointer to the text (UniCode string) or nullptr|nullptr|
 * 			|API_PrimPLineID|(API_Coord*) coordinates|nullptr|(API_PolyArc*) arcs|
 * 			|API_PrimTriID|nullptr|nullptr|nullptr|
 * 			|API_PrimPolyID|(API_Coord*) coordinates|(Int32*) subpolygon endpoints|(API_PolyArc*) arcs|
 * 			|API_PrimCtrl_BegID|nullptr|nullptr|nullptr|
 * 			|API_PrimCtrl_HatchBorderBegID|(API_PrimHatchBorder*) border|nullptr|nullptr|
 * 			|API_PrimCtrl_HatchBorderEndID|nullptr|nullptr|nullptr|
 * 			|API_PrimCtrl_HatchLinesBegID|nullptr|nullptr|nullptr|
 * 			|API_PrimCtrl_HatchLinesEndID|nullptr|nullptr|nullptr|
 * 			|API_PrimCtrl_HoledimLinesBegID|nullptr|nullptr|nullptr|
 * 			|API_PrimCtrl_HoledimLinesEndID|nullptr|nullptr|nullptr|
 * 			|API_PrimCtrl_ArrowBegID|nullptr|nullptr|nullptr|
 * 			|API_PrimCtrl_ArrowEndID|nullptr|nullptr|nullptr|
 * 			|API_PrimCtrl_ElementRefID|(API_PrimElemRef*) reference|nullptr|nullptr|
 * 			|API_PrimCtrl_EndID|nullptr|nullptr|nullptr|
 * 			|API_PrimCtrl_PlacedBorderBegID|nullptr|nullptr|nullptr|
 * 			|API_PrimCtrl_PlacedBorderEndID|nullptr|nullptr|nullptr|
 * 			|API_PrimCtrl_TextBegID|nullptr|nullptr|nullptr|
 * 			|API_PrimCtrl_TextEndID|nullptr|nullptr|nullptr|
 * 			|API_PrimCtrl_BackgroundFillBegID|nullptr|nullptr|nullptr|
 * 			|API_PrimCtrl_BackgroundFillEndID|nullptr|nullptr|nullptr|
 * 			|API_PrimCtrl_FrameBegID|nullptr|nullptr|nullptr|
 * 			|API_PrimCtrl_FrameEndID|nullptr|nullptr|nullptr|
 */
typedef GSErrCode ShapePrimsProc (const API_PrimElement* primElem, const void* par1, const void* par2, const void* par3);

/**
 * @brief User supplied callback procedure for helping BCF Import.
 * @ingroup IFC
 * @since Archicad 26
 * @param ifcRelationshipDataTable [out] Gives back a Hashtable where the keys are the IFCProject's GlobalIds and the values are their @ref API_IFCRelationshipData.
 * @param par1 [in] Optional parameter.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_GENERAL - Any user-defined error can be returned.
 * @remarks @ref API_IFCRelationshipData may be needed by BCF topics when they refer to such components which are represented by their parent elements in Archicad.
 * 			A typical example is when an Archicad Wall is exported in IFC as an IFCWall instance having several IFCBuildingElementPart components and the imported BCF topic refers to a certain IFCBuildingElementPart.
 * 			In this case the BCF importer should convert the IFCBuildingElementPart reference to its parent (IFCWall) and connect its corresponding Archicad Wall element to the created MarkUp Entry.
 * 			In code it looks like the following:
 * @ref API_IFCRelationshipData ifcRelationshipData; ifcRelationshipData.containmentTable.Add (ifcBuildingElementPartGuid1, ifcWallGuid); ifcRelationshipData.containmentTable.Add (ifcBuildingElementPartGuid2, ifcWallGuid); ifcRelationshipData.containmentTable.Add (ifcBuildingElementPartGuid3, ifcWallGuid); ifcRelationshipDataTable->Add (ifcProjectGuid, ifcRelationshipData);
 * 		If the origin of the model is the current Archicad project, then we can get the @ref API_IFCRelationshipData which can be generated with @ref ACAPI_IFC_GetIFCRelationshipData. 	The ifcRelationshipDataTable can have several @ref API_IFCRelationshipData of several IFCProjects. This is because the components of a BCF topic can refer several components which may be located under different IFCProjects.
 * 		For use see @ref ACAPI_Markup_ImportFromBCF.
 */
typedef GSErrCode APIIFCRelationshipDataProc (GS::HashTable<GS::UniString, API_IFCRelationshipData>* ifcRelationshipDataTable, const void* par1);

/**
 * @brief User supplied callback function for processing the drawing numbering grid lines.
 * @ingroup Drawing
 * @param gridLine [in] This structure contains parameters (coordinates, pen color, line type) of the current drawing numbering grid lines
 * @return
 * 			- NoError - The callback function is expected to return NoError.
 * @remarks This callback function is used with the @ref ACAPI_Drawing_GetNumberingGridLines function to get the lines of the drawing numbering grid of the current Archicad layout database.
 */
typedef GSErrCode APINumberingGridLineProc (const API_NumberingGridLine* gridLine);

/**
 * @brief Callback function for handling the responses of asynchronous external module command calls.
 * @ingroup AddOnAddOnCommunication
 * @param params [in/out] the passed parameters for the module command
 * @param returnCode [in] the return value of the APIModulCommandProc function of the server side add-on
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This is the handler function to be used for collecting the results of external module command calls in asynchronous case.
 * 			For more details refer to the description of the @ref ACAPI_AddOnAddOnCommunication_ExternalCall function.
 */
typedef GSErrCode APIExternalCallBackProc (GSHandle params, GSErrCode returnCode);

/**
 * @brief Callback function for handling the responses of asynchronous module command calls from main event loop.
 * @ingroup AddOnAddOnCommunication
 * @param paramsHandle [in/out] pointer to the passed parameters for the module command
 * @param resultData [in] optional result data from the @ref APIModulCommandProc function of the server side add-on
 * @param returnCode [in] the return value of the @ref APIModulCommandProc function of the server side add-on
 * @remarks This is the handler function to be used for collecting the results of module command calls in asynchronous case.
 * 			For more details refer to the description of the @ref ACAPI_AddOnAddOnCommunication_CallFromEventLoop function.
 */
typedef void APICommandCallBackProc (GSHandle* paramsHandle, GSPtr resultData, GSErrCode returnCode);

/**
 * @brief Handler procedure for abnormal termination.
 * @ingroup AddOnLifetime
 * @remarks Set this hook procedure with the @ref ACAPI_SetDllTermHookProc function in order to be called when the application does not terminate in the normal way. Generally this function should do the same as @ref FreeData does.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_SetDllTermHookProc-Example-Snippet
 */
typedef void APIDllTermHookProc (void);

/**
 * @brief Callback function to handle Attribute
 */
typedef void APIAttributeProc (const API_Attribute& attribute, const API_AttributeDefExt& attributeDefExt, GSPtr par1);

/**
 * Callback function to import attributes from the new registered import format.
 * @since Archicad 26
 * @param fileName [in] The path from where to read the attributes.
 * @param result [out] The read attributes. These will appear in the Attribute Manager.
 * @return
 * 			- NoError - The function has completed with success.
 */
typedef GSErrCode ImportAttrProc (const IO::Location& fileName, GS::Array<GS::Pair<API_Attribute, API_AttributeDefExt*>>& result);


// =============================================================================
// Miscellaneous interfaces
//
// =============================================================================

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

/**
 * @brief Interface class for the element decomposition process.
 * @ingroup Element
 * @remarks Interface class for enumerating the planes of a Multi-plane Roof element with the @ref ACAPI_Element_Decompose function. An instance of a derived class of this type should be passed to the decomposer function, which then calls the GeneratePartElement virtual method of the object for each planes of the PolyRoof one by one.
 * @par Example
 * 		@snippet API_Examples.cpp API_ElementDecomposerInterface-Example-Snippet
 */
class API_ElementDecomposerInterface {
public:

	/**
	 * This methor is called from the @ref ACAPI_Element_Decompose function for all decomposed element part.
	 * @param guid [in] The guid of the original PolyRoof element.
	 * @param partId [in] Identifies the part element within the whole structure. In the context of Multi-plane Roofs the main member refers to the vertexId of the pivot polygon, and sub identifies the roof level.
	 * @param partElem [in] Data describing the element part. Currently this variable always returns @ref API_RoofType parameters with API_PlaneRoofID class.
	 * @param partMemo [in] Memo data of the part element. Only the relevant members are initialized, in case of plane roofs the following ones: coords, pends, parcs, vertexIDs, edgeTrims, roofEdgeTypes, sideMaterials. These memo arrays will be disposed by @ref ACAPI_Element_Decompose at the end of the call.
	 * @return Error code.
	 */
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
constexpr const char* MarqueeEventHandlerName						= "MarqueeEventHandler";
constexpr const char* WindowEventHandlerName						= "WindowEventHandler";


class API_IAttributeEventHandler;
class API_IAttributeFolderEventHandler;
class API_IClassificationItemEventHandler;
class API_IClassificationSystemEventHandler;
class API_IPropertyGroupEventHandler;
class API_IPropertyDefinitionEventHandler;
class API_IGraphisoftIDEventHandler;
class API_IEnableAllInfoDialogEventHandler;
class API_IMarqueeEventHandler;
class API_IWindowEventHandler;


/**
 * @brief Defining an interface for a class that will be used to notify all event handlers.
 * @ingroup Notification
 * @class API_IEventNotifier
 * @since Archicad 26
 */
class API_IEventNotifier {
public:
	virtual ~API_IEventNotifier () = default;
};


/**
 * @brief Defining an interface for a class that will be used to notify event handlers.
 * @ingroup Notification
 * @class API_IACEventNotifier
 * @since Archicad 28
 */
class API_IACEventNotifier : public API_IEventNotifier {
public:
	virtual ~API_IACEventNotifier () = default;

/**
 * @brief Notifies the event handler about the attribute changes.
 * @param eventHandler An instance that handles the event.
 */
	virtual void NotifyAttributeChanges (const API_IAttributeEventHandler& eventHandler) const = 0;

/**
 * @brief Notifies the event handler about the attribute folder changes.
 * @param eventHandler An instance that handles the event.
 */
	virtual void NotifyAttributeFolderChanges (const API_IAttributeFolderEventHandler& eventHandler) const = 0;

/**
 * @brief Notifies the event handler about the classification item changes.
 * @param eventHandler An instance that handles the event.
 */
	virtual void NotifyClassificationItemChanges (const API_IClassificationItemEventHandler& eventHandler) const = 0;

/**
 * @brief Notifies the event handler about the classification system changes.
 * @param eventHandler An instance that handles the event.
 */
	virtual void NotifyClassificationSystemChanges (const API_IClassificationSystemEventHandler& eventHandler) const = 0;

/**
 * @brief Notifies the event handler about property group changes.
 * @param eventHandler An instance that handles the event.
 */
	virtual void NotifyPropertyGroupChanges (const API_IPropertyGroupEventHandler& eventHandler) const = 0;

/**
 * @brief Notifies the event handler about property definition changes.
 * @param eventHandler An instance that handles the event.
 */
	virtual void NotifyPropertyDefinitionChanges (const API_IPropertyDefinitionEventHandler& eventHandler) const = 0;

/**
 * @brief Notifies the event handler when Graphisoft ID is changed.
 * @param eventHandler An instance that handles the event.
 */
	virtual void NotifyGraphisoftIDChanges (const API_IGraphisoftIDEventHandler& eventHandler) const = 0;

/**
 * @brief Notifies the event handler when the user enables all informational dialogs.
 * @param eventHandler An instance that handles the event.
 */
	virtual void NotifyEnableAllDialogInfoEvent (const API_IEnableAllInfoDialogEventHandler& eventHandler) const = 0;

/**
 * @brief Notifies the event handler about the marquee event.
 * @param eventHandler An instance that handles the event.
 */
	virtual void NotifyMarqueeEvent (const API_IMarqueeEventHandler& eventHandler) const = 0;

/**
 * @brief Notifies the event handler about window changes.
 * @param eventHandler An instance that handles the event.
 */
	virtual void NotifyWindowChanges (const API_IWindowEventHandler& eventHandler) const = 0;
};

/**
 * @brief Defining an interface for all event handlers.
 * @ingroup Notification
 * @class API_IEventHandler
 * @since Archicad 26
 */
class API_IEventHandler {
public:
	virtual ~API_IEventHandler () = default;

/**
 * @return Human readable name of the event handler.
 */
	virtual GS::UniString		GetName () const = 0;

/**
 * @brief It dispatches the event.
 * @param eventNotifier The occurrence of an event can be notified via this parameter.
 */
	virtual void				Dispatch (const API_IEventNotifier& eventNotifier) const = 0;
};

/**
 * @brief Defining an interface for Object event handlers.
 * @ingroup Notification
 * @class API_IObjectEventHandler
 * @since Archicad 26
 */
class API_IObjectEventHandler {
public:
	virtual ~API_IObjectEventHandler () = default;

/**
 * @brief Event handler for object creation events.
 */
	virtual void OnCreated (const GS::HashSet<API_Guid>&) const { }

/**
 * @brief Event handler for object modification events.
 */
	virtual void OnModified (const GS::HashSet<API_Guid>&) const { }

/**
 * @brief Event handler for object deletion events.
 */
	virtual void OnDeleted (const GS::HashSet<API_Guid>&) const { }
};

/**
 * @brief Defining an interface for Dialog event handlers.
 * @ingroup Notification
 * @class API_IDialogEventHandler
 * @since Archicad 26
 */
class API_IDialogEventHandler {
public:
	virtual ~API_IDialogEventHandler () = default;

/**
 * @brief Event handler in case of enabling all informational messages in the Work Environment.
 */
	virtual void EnableAllInfoDialog () const = 0;
};

/**
 * @brief Defining an interface for Attribute event handlers.
 * @ingroup Notification
 * @class API_IAttributeEventHandler
 * @since Archicad 26
 */
class API_IAttributeEventHandler : public API_IEventHandler,
								   public API_IObjectEventHandler {
public:
/**
 * @return Human readable name of the event handler.
 */
	virtual GS::UniString GetName () const override final
	{
		return AttributeEventHandlerName;
	}

/**
 * @brief It dispatches the event.
 * @param eventNotifier The occurrence of an event can be notified via this parameter.
 */
	virtual void Dispatch (const API_IEventNotifier& eventNotifier) const override final
	{
		const API_IACEventNotifier* acEventNotifier = dynamic_cast<const API_IACEventNotifier*> (&eventNotifier);
		if (acEventNotifier != nullptr)
			acEventNotifier->NotifyAttributeChanges (*this);
	}
};

/**
 * @brief Defining an interface for Attribute Folder event handlers.
 * @ingroup Notification
 * @class API_IAttributeFolderEventHandler
 * @since Archicad 26
 */
class API_IAttributeFolderEventHandler : public API_IEventHandler,
										 public API_IObjectEventHandler {
public:
/**
 * @return Human readable name of the event handler.
 */
	virtual GS::UniString GetName () const override final
	{
		return AttributeFolderEventHandlerName;
	}

/**
 * @brief It dispatches the event.
 * @param eventNotifier The occurrence of an event can be notified via this parameter.
 */
	virtual void Dispatch (const API_IEventNotifier& eventNotifier) const override final
	{
		const API_IACEventNotifier* acEventNotifier = dynamic_cast<const API_IACEventNotifier*> (&eventNotifier);
		if (acEventNotifier != nullptr)
			acEventNotifier->NotifyAttributeFolderChanges (*this);
	}
};


/**
 * @brief The base class you need to inherit from in case you want to handle @ref API_ClassificationSystem events.
 * @ingroup Notification
 * @class API_IClassificationSystemEventHandler
 * @since Archicad 26
 */
class API_IClassificationSystemEventHandler : public API_IEventHandler,
											  public API_IObjectEventHandler {
public:
/**
 * @return Human readable name of the event handler.
 */
	virtual GS::UniString GetName () const override final
	{
		return ClassificationSystemEventHandlerName;
	}

/**
 * @brief It dispatches the event.
 * @param eventNotifier The occurrence of an event can be notified via this parameter.
 */
	virtual void Dispatch (const API_IEventNotifier& eventNotifier) const override final
	{
		const API_IACEventNotifier* acEventNotifier = dynamic_cast<const API_IACEventNotifier*> (&eventNotifier);
		if (acEventNotifier != nullptr)
			acEventNotifier->NotifyClassificationSystemChanges (*this);
	}

};


/**
 * @brief The base class you need to inherit from in case you want to handle @ref API_ClassificationItem events.
 * @ingroup Notification
 * @class API_IClassificationItemEventHandler
 * @since Archicad 26
 */
class API_IClassificationItemEventHandler : public API_IEventHandler,
											public API_IObjectEventHandler {
public:
/**
 * @return Human readable name of the event handler.
 */
	virtual GS::UniString GetName () const override final
	{
		return ClassificationItemEventHandlerName;
	}

/**
 * @brief It dispatches the event.
 * @param eventNotifier The occurrence of an event can be notified via this parameter.
 */
	virtual void Dispatch (const API_IEventNotifier& eventNotifier) const override final
	{
		const API_IACEventNotifier* acEventNotifier = dynamic_cast<const API_IACEventNotifier*> (&eventNotifier);
		if (acEventNotifier != nullptr)
			acEventNotifier->NotifyClassificationItemChanges (*this);
	}

};


/**
 * @brief The base class you need to inherit from in case you want to handle @ref API_PropertyGroup events.
 * @ingroup Notification
 * @class API_IPropertyGroupEventHandler
 * @since Archicad 26
 */
class API_IPropertyGroupEventHandler : public API_IEventHandler,
									   public API_IObjectEventHandler {
public:
/**
 * @return Human readable name of the event handler.
 */
	virtual GS::UniString GetName () const override final
	{
		return PropertyGroupEventHandlerName;
	}

/**
 * @brief It dispatches the event.
 * @param eventNotifier The occurrence of an event can be notified via this parameter.
 */
	virtual void Dispatch (const API_IEventNotifier& eventNotifier) const override final
	{
		const API_IACEventNotifier* acEventNotifier = dynamic_cast<const API_IACEventNotifier*> (&eventNotifier);
		if (acEventNotifier != nullptr)
			acEventNotifier->NotifyPropertyGroupChanges (*this);
	}

};


/**
 * @brief The base class you need to inherit from in case you want to handle @ref API_PropertyDefinition events.
 * @ingroup Notification
 * @class API_IPropertyDefinitionEventHandler
 * @since Archicad 26
 */
class API_IPropertyDefinitionEventHandler : public API_IEventHandler,
											public API_IObjectEventHandler {
public:
/**
 * @return Human readable name of the event handler.
 */
	virtual GS::UniString GetName () const override final
	{
		return PropertyDefinitionEventHandlerName;
	}

/**
 * @brief It dispatches the event.
 * @param eventNotifier The occurrence of an event can be notified via this parameter.
 */
	virtual void Dispatch (const API_IEventNotifier& eventNotifier) const override final
	{
		const API_IACEventNotifier* acEventNotifier = dynamic_cast<const API_IACEventNotifier*> (&eventNotifier);
		if (acEventNotifier != nullptr)
			acEventNotifier->NotifyPropertyDefinitionChanges (*this);
	}

};


/**
 * The base class you need to inherit from in case you want to handle Graphisoft ID change event.
 * @ingroup Notification
 * @class API_IGraphisoftIDEventHandler
 * @since Archicad 26
 */
class API_IGraphisoftIDEventHandler : public API_IEventHandler {
public:
/**
 * @return Human readable name of the event handler.
 */
	virtual GS::UniString GetName () const override final
	{
		return GraphisoftIDEventHandlerName;
	}

/**
 * @brief It dispatches the event.
 * @param eventNotifier The occurrence of an event can be notified via this parameter.
 */
	virtual void Dispatch (const API_IEventNotifier& eventNotifier) const override final
	{
		const API_IACEventNotifier* acEventNotifier = dynamic_cast<const API_IACEventNotifier*> (&eventNotifier);
		if (acEventNotifier != nullptr)
			acEventNotifier->NotifyGraphisoftIDChanges (*this);
	}

/**
 * @brief Event handler for Graphisoft ID changes.
 */
	virtual void OnUserChanged () const = 0;

};

/**
 * The base class you need to inherit from in case you want to handle Info Dialog change event.
 * @ingroup Notification
 * @class API_IEnableAllInfoDialogEventHandler
 * @since Archicad 26
 */
class API_IEnableAllInfoDialogEventHandler : public API_IEventHandler,
											 public API_IDialogEventHandler {
public:
/**
 * @return Human readable name of the event handler.
 */
	virtual GS::UniString GetName () const override final
	{
		return EnableAllInfoDialogEventHandlerName;
	}

/**
 * @brief It dispatches the event.
 * @param eventNotifier The occurrence of an event can be notified via this parameter.
 */
	virtual void Dispatch (const API_IEventNotifier& eventNotifier) const override final
	{
		const API_IACEventNotifier* acEventNotifier = dynamic_cast<const API_IACEventNotifier*> (&eventNotifier);
		if (acEventNotifier != nullptr)
			acEventNotifier->NotifyEnableAllDialogInfoEvent (*this);
	}
};

/**
 * The base class you need to inherit from in case you want to handle Marquee change event.
 * @ingroup Notification
 * @class API_IMarqueeEventHandler
 * @since Archicad 26
 */
class API_IMarqueeEventHandler : public API_IEventHandler {
public:
/**
 * @return Human readable name of the event handler.
 */
	virtual GS::UniString GetName () const override final
	{
		return MarqueeEventHandlerName;
	}

/**
 * @brief It dispatches the event.
 * @param eventNotifier The occurrence of an event can be notified via this parameter.
 */
	virtual void Dispatch (const API_IEventNotifier& eventNotifier) const override final
	{
		const API_IACEventNotifier* acEventNotifier = dynamic_cast<const API_IACEventNotifier*> (&eventNotifier);
		if (acEventNotifier != nullptr)
			acEventNotifier->NotifyMarqueeEvent (*this);
	}

/**
 * @brief Event handler for marquee changes.
 * @param selectionInfo Information about the current selection.
 */
	virtual void OnMarqueeChanged (const API_SelectionInfo& selectionInfo) const = 0;
};

/** 
 * @brief The base class you need to inherit from in case you want to handle window change events.
 * @ingroup Notification
 * @class API_IWindowEventHandler
 * @since Archicad 28
 */
class API_IWindowEventHandler : public API_IEventHandler {
public:
/**
 * @return Human readable name of the event handler.
 */
	virtual GS::UniString GetName () const override final
	{
		return WindowEventHandlerName;
	}

/**
 * @brief It dispatches the event.
 * @param eventNotifier The occurrence of an event can be notified via this parameter.
 */
	virtual void Dispatch (const API_IEventNotifier& eventNotifier) const override final
	{
		const API_IACEventNotifier* acEventNotifier = dynamic_cast<const API_IACEventNotifier*> (&eventNotifier);
		if (acEventNotifier != nullptr)
			acEventNotifier->NotifyWindowChanges (*this);
	}

/**
 * @brief Event handler for window brought forward event
 *
 * @warning Avoid complex operations in this function. It could cause significant slowdowns
 *
 * @param[in] window The window brought forward
 * @details The function called on windows gaining top status. This event is only triggered by windows (Floorplan, 3D, Section, etc.) and does not consider palettes or dialogs.
 * 			OnWindowBroughtForward is usually received after an @ref OnWindowSentBackward event, except when all windows are closed. Closing all windows will not result in a OnWindowBroughtForward event.
 * @remarks	Note that in case of the parameter only the fields which are necessary to identify the window type and the database behind the windows are filled out (similarly to @ref ACAPI_Window_GetCurrentWindow).
 * 			In order to retrieve the additional parameters of the database (title, name, ref, masterLayoutUnId) call the @ref ACAPI_Window_GetDatabaseInfo function with the databaseUnId of the window.
 */
	virtual void OnWindowBroughtForward (const API_WindowInfo& window) const = 0;

/**
 * @brief Event handler for window sent backward event
 *
 * @warning Avoid complex operations in this function. It could cause significant slowdowns
 *
 * @param[in] window The window sent backward
 * @details The function called on windows losing top status. This event is only triggered by windows (Floorplan, 3D, Section, etc.) and does not consider palettes or dialogs.
 * 			OnWindowSentBackward is usually received before an @ref OnWindowBroughtForward event, except opening the first window. Opening the first window will not result in a OnWindowSentBackward event.
 * @remarks	Note that in case of the parameter only the fields which are necessary to identify the window type and the database behind the windows are filled out (similarly to @ref ACAPI_Window_GetCurrentWindow).
 * 			In order to retrieve the additional parameters of the database (title, name, ref, masterLayoutUnId) call the @ref ACAPI_Window_GetDatabaseInfo function with the databaseUnId of the window.
 */
	virtual void OnWindowSentBackward (const API_WindowInfo& window) const = 0;
};


#ifdef __clang__
#pragma clang diagnostic pop
#endif


// ---------------------------------------------------------------------------------------------------------------------

#endif
