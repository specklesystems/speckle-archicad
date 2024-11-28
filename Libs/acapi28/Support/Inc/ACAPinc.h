// *********************************************************************************************************************
//
//
// Module:			API
// Namespace:		-
// Contact person:
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (ACAPINC_H)
#define	ACAPINC_H

#if defined (_MSC_VER)
#pragma once
#endif


// --- Includes	--------------------------------------------------------------------------------------------------------

#if defined (WINDOWS)
#include "Win32Interface.hpp"
#endif

// STL
#include <unordered_set>
#include <unordered_map>

// GSRoot
#include "GSRoot.hpp"
#include "Array.hpp"
#include "PagedArray.hpp"
#include "UniString.hpp"
#include "Owner.hpp"

// own
#include "APICalls.h"
#include "APIdefs.h"
#include "ACAPI_Automate.h"
#include "ACAPI_Database.h"
#include "ACAPI_Environment.h"
#include "ACAPI_Goodies.h"
#include "ACAPI_Interface.h"
#include "ACAPI_Navigator.h"

// --- Predeclarations -------------------------------------------------------------------------------------------

//! @cond Doxygen_Suppress
namespace Geometry {
	class PolyId;

	template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData> class CustomMultiPolygon2D;
	typedef CustomMultiPolygon2D<PolyId, PolyId, PolyId, PolyId> MultiPolygon2D;
}
//! @endcond


// --- Compiler settings -----------------------------------------------------------------------------------------------

#if defined (_MSC_VER)
	#pragma pack(push, 8)
#endif


// --- Predeclarations -------------------------------------------------------------------------------------------

namespace Modeler {
	class MeshBody;
	class IAttributeReader;
}

namespace ModelerAPI {
	class Model;
}

// --- Function declarations -------------------------------------------------------------------------------------------

// =============================================================================
// Functions must be supported by the addon
//
// Following functions must be implemented in each extension.
// They are called from ARCHICAD.
// For detailed description refer to the enclosed documentation.
//
// =============================================================================

extern "C" {

/**
 * @brief Defines the behavior of the add-on based on the current running environment.
 * @param envirParams [in/out] Contains information on the environment. The add-on should also return a textual description of its purpose.
 * @ingroup AddOnLifetime
 * @return
 * 			- type of add-on.
 * @remarks This is one of the main entry points of add-ons; each add-on should implement this function. It is called when the Add-On Manager is enumerating the add-ons during application startup. After collecting the all the information from the different add-ons, the Add-On Manager performs a dependency check, then calls the @ref RegisterInterface function of the "good" add-ons.
 * 			The add-on can check the running environment (server application, main and sub-version), and return whether it can run under the given conditions. For example, you can disable your add-on in the demo version of Archicad; or enable/disable certain commands.
 * 			This function is also the place to inform other add-ons about the availability of certain services of your add-on (see @ref ACAPI_AddOnAddOnCommunication_RegisterSupportedService), and also to tell the server application that your add-on requires services of other add-ons (see @ref ACAPI_AddOnIntegration_RegisterRequiredService).
 * @par Example
 * 		@snippet API_Examples.cpp CheckEnvironment-Example-Snippet
 */
API_AddonType CheckEnvironment (API_EnvirParams* envirParams);


/**
 * @brief In this function the add-on can register its services, and menu commands.
 * @ingroup AddOnLifetime
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function registers the different services of your add-on: menu commands, file types, commands other add-on can call, toolbox items, or library part subtypes. Here you can obtain information on the server application, on the protection, and the availability of the services of other add-ons as well; and adjust the registration depending on this information.
 * 			The actual callback functions which handle the events and notifications coming from the server application are installed in the Initialize function of your add-on.
 * 			The actual callback functions which handle the events and notifications coming from the server application are installed in the @ref Initialize function of your add-on.
 * @par Example
 * 		@snippet API_Examples.cpp RegisterInterface-Example-Snippet
 */
GSErrCode RegisterInterface (void);


/**
 * @brief The main entry point of the add-on.
 * @ingroup AddOnLifetime
 * @return
 * 			- NoError - The initialization procedure has completed with success.
 * @remarks You can use this function as the main entry point of your code. It is called by the library right after the DLL/code fragment has been loaded into the memory, and the communication channels are set up correctly. This is the place where you can initialize your global variables, dynamic memory blocks etc.
 * 			In this function you will also have to install the callback functions for the different services you registered in the @ref CheckEnvironment and @ref RegisterInterface routines. Also you can install the notification handlers here.
 * 			If your add-on has user interface, and you want to use a context sensitive help engine (you want to use not just tooltips, but help anchors too), then this is the place where you can register your own help engine's path with your add-on's MDID (see DG::RegisterAdditionalHelpLocation in the example code).
 * @par Example
 * 		@snippet API_Examples.cpp Initialize-Example-Snippet
 */
GSErrCode Initialize (void);


/**
 * The termination point of the addon.
 * @ingroup AddOnLifetime
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks You can use this function as the termination point of your code. It is called right before the DLL/code fragment is to be unloaded from the memory. This is the place where you can free your dynamic memory blocks, and unload the loaded modules.
 * 			This function will be called in conjunction with the @ref Initialize function. You can be sure that the FreeData function will be called only if this function was called before, even if any error code returned in the @ref Initialize or the different callback functions.
 * 			If your add-on has user interface, and you want to use a context sensitive help engine (you want to use not just tooltips, but help anchors too), and you registered your own help engine's path with your add-on's MDID in the Initialize function, then you should uninitialize this data here.
 * 			In some exceptional cases the application terminates without calling the FreeData function of the add-ons. In these situations the system unloads the add-on modules. If you need to be called to handle these abnormal termination cases, set an @ref APIDllTermHookProc with the @ref ACAPI_SetDllTermHookProc function.
 * @par Example
 * 		@snippet API_Examples.cpp FreeData-Example-Snippet
 */
GSErrCode FreeData (void);

}



#if defined (ACExtension)
/* [ --> */
// =============================================================================
// Function supported by the API
//
// Following functions are supported by the ACAP library.
// For detailed description refer to the enclosed documentation.
//
// =============================================================================

/* -- Server ------------------------------ */
#define	ServerMainVers_600			0x0001			// Package 6.00:  (ARCHICAD 6.0, PlotMaker 2.1)
#define	ServerMainVers_650			0x0002			// Package 6.50:  (ARCHICAD 6.5, PlotMaker 2.2)
#define	ServerMainVers_700			0x0003			// Package 7.00:  (ARCHICAD 7.0, PlotMaker 2.3)
#define	ServerMainVers_800			0x0004			// Package 8.00:  (ARCHICAD 8,   PlotMaker 3)
#define	ServerMainVers_810			0x0005			// Package 8.10:  (ARCHICAD 8.1, PlotMaker 3.1)
#define	ServerMainVers_900			0x0006			// Package 9.00:  (ARCHICAD 9,   PlotMaker 9)
#define	ServerMainVers_1000			0x000A			// ARCHICAD 10
#define	ServerMainVers_1100			0x000B			// ARCHICAD 11
#define	ServerMainVers_1200			0x000C			// ARCHICAD 12
#define	ServerMainVers_1300			0x000D			// ARCHICAD 13
#define	ServerMainVers_1400			0x000E			// ARCHICAD 14
#define	ServerMainVers_1500			0x000F			// ARCHICAD 15
#define	ServerMainVers_1600			0x0010			// ARCHICAD 16
#define	ServerMainVers_1700			0x0011			// ARCHICAD 17
#define	ServerMainVers_1800			0x0012			// ARCHICAD 18
#define	ServerMainVers_1900			0x0013			// ARCHICAD 19
#define	ServerMainVers_2000			0x0014			// ARCHICAD 20
#define	ServerMainVers_2100			0x0015			// ARCHICAD 21
#define	ServerMainVers_2200		    0x0016			// ARCHICAD 22
#define	ServerMainVers_2300		    0x0017			// ARCHICAD 23
#define	ServerMainVers_2400		    0x0018			// ARCHICAD 24
#define	ServerMainVers_2500		    0x0019			// ARCHICAD 25
#define	ServerMainVers_2600		    0x001A			// ARCHICAD 26
#define	ServerMainVers_2700		    0x001B			// ARCHICAD 27
#define	ServerMainVers_2800		    0x001C			// ARCHICAD 28

#define	ServerReleaseVers_R1		1




/**
 * Returns information on the server application.
 * @ingroup HierarchicalEditing
 * @since Archicad 26
 * @param serverApplicationInfo [out] Contains the main and maintenance release number of the server application. The main version for the current release is equal to the ServerMainVers_2700 constant in ACAPinc.h.
 * @remarks If you have features or workarounds in your add-on that work only with special releases of the server application, you can obtain that version information during runtime with this function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_GetReleaseNumber-Example-Snippet
 */
__APIEXPORT void ACAPI_GetReleaseNumber (API_ServerApplicationInfo	*serverApplicationInfo);

/* -- System ------------------------------ */

#if defined (WINDOWS)
/**
 * @brief Returns the HINSTANCE of the add-on's DLL.
 * @ingroup Deprecated
 * @return
 * 			- HINSTANCE - The HINSTANCE of the add-on.
 * @remarks This function is applicable for Windows only.
 */
__APIEXPORT HINSTANCE ACAPI_GetExtensionInstance (void);


/**
 * @brief Returns the main window of the application the add-on is working in.
 * @ingroup Dialog
 * @return
 * 			- HWND - The handle of the main window.
 * @remarks This function is applicable for Windows only.
 */
__APIEXPORT HWND ACAPI_GetMainWindow (void);
#endif


/**
 * @brief Returns the add-on's own resource module identifier for loading resources.
 * @ingroup Resource
 * @return
 * 			- NoError - The identifier of the add-on's resource file.
 * @remarks You can use the return values of this function wherever a reference to the add-on's own resource module is needed.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_GetOwnResModule-Example-Snippet
 */
__APIEXPORT GSResModule ACAPI_GetOwnResModule (void);


/**
 * @brief Returns the location of the add-on in the file system.
 * @ingroup AddOnIdentification
 * @param ownFileLoc [out] On return contains the location of the add-on in the file system.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOTINIT - The internal variable holding the location of the add-on hasn't been initalized yet.
 */
__APIEXPORT GSErrCode ACAPI_GetOwnLocation (IO::Location *ownFileLoc);


/**
 * @brief Sets a handler procedure for the case of abnormal termination.
 * @ingroup AddOnLifetime
 * @param dllTermHookProc [in] Handler function pointer
 * @remarks Normally the FreeData function of the add-on is called before the add-on module is unloaded from the memory. However in some exceptional cases the application terminates without properly unloading the add-ons. For handling these situations you can set a hook procedure with the @ref ACAPI_SetDllTermHookProc function. This might be useful if, for example, you have loaded additional modules (DLLs) from your add-on, and you want to unload them even in the case of abnormal termination.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_SetDllTermHookProc-Example-Snippet
 */
__APIEXPORT void ACAPI_SetDllTermHookProc (APIDllTermHookProc* dllTermHookProc);


/* -- Registration ------------------ */



/**
 * @brief Registers a command which can be used by other add-ons.
 * @ingroup AddOnAddOnCommunication
 * @ingroup AddOnIntegration
 * @param cmdID [in] The command identifier of the supported service.
 * @param cmdVersion [in] The command version of the supported service.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks The function registers one of your add-on's command, and makes it avaliable for other add-ons. This should be called from the RegisterInterface function of the add-on.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AddOnAddOnCommunication_RegisterSupportedService-Example-Snippet
 */	// CheckEnvironment
__APIEXPORT GSErrCode ACAPI_AddOnAddOnCommunication_RegisterSupportedService (GSType cmdID, Int32 cmdVersion);


/**
 * @brief Check the availability of an other add-on's command.
 * @ingroup AddOnIntegration
 * @param modulID [in] The modul ID of the add-on containing the required service.
 * @param cmdID [in] The command identifier of the required service.
 * @param cmdVersion [in] The command version of the required service.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_GENERAL - The command isn't supported service.
 * @remarks This function checks for the availability of an other add-on's command, without which it cannot run. The other add-on should provide all the necessary information. The function should be called from the RegisterInterface function of the add-on.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AddOnIntegration_RegisterRequiredService-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_RegisterRequiredService (const API_ModulID	*modulID,
																	  GSType			cmdID,
																	  Int32				cmdVersion);



/**
 * @brief Registers the menu items of the add-on.
 * @ingroup MenuItem
 * @ingroup AddOnIntegration
 * @param menuStrResID [in] The resource ID of the menu resource, which should be in the resource fork of the add-on.
 * @param promptStrResID [in] The resource ID of the propmt string resource, which should be in the resource fork of the add-on. These strings appear in the status bar.
 * @param menuPosCode [in] Defines the server application's menu to insert the command into.
 * @param menuFlags [in] Flags describing whether you would like to see any separator item in the menu before or after the registered menu item. Its possible values are: MenuFlag_Default, MenuFlag_SeparatorBefore, and MenuFlag_SeparatorAfter
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function should be called from the RegisterInterface routine in your add-on. You can register more than one menu from the same add-on, even appearing in different menus of the server application.
 * 			The supplied menuStrResID parameter should be the same in the @ref ACAPI_MenuItem_InstallMenuHandler function, which you have to call from your Initialize routine.
 * 			The following scenarios are possible:
 * 			- the add-on inserts one menu item at the position defined by menuPosCode 'STR#' 32500 "Menu Description" { / [ 1] / "My add-on's solo menuitem" }
 * 			- the add-on inserts a submenu at the position defined by menuPosCode 'STR#' 32501 "Menu Description" { / [ 1] / "My add-on's submenu" / [ 2] / "My add-on's menuitem #1" / [ 3] / "My add-on's menuitem #2" }
 * 			- the add-on inserts its own main menu; menuPosCode should be MenuCode_UserDef 'STR#' 32502 "Menu Description" { / [ 1] / "My add-on's main menu" / [ 2] / "My add-on's solo menuitem" }
 * 			- the add-on inserts its own main menu with a submenu; menuPosCode should be MenuCode_UserDef 'STR#' 32503 "Menu Description" { / [ 1] / "My add-on's main menu" / [ 2] / "My add-on's submenu" / [ 3] / "My add-on's menuitem #1" / [ 4] / "My add-on's menuitem #2" }
 * 			As you see, the add-on may define its own main menu, if it uses MenuCode_UserDef and the menu position. In this case the first item in the STR# resource will be the title of the main menu, and the other items correspond to the menu items in the non-main menu case.
 * 			If this first item is the same as one of the server application's main menu titles, then the API won't open a new main menu, rather it inserts the add-on's menu into the original main menu, as defined by the rules for that menu. This also means if you use an already existing menu title (e.g. Window) which doesn't have an insertion place for add-ons, your add-on's menu won't appear.
 * 			This implies that the location of the add-on within the Add-Ons folder doesn't have any impact on the menu position of your add-on's commands.
 * 			The appearance of menu items can be controlled by control codes appended to the menu item string resource as described in the Required Resources section.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_MenuItem_RegisterMenu-Example-Snippet
 */	// RegisterInterface
__APIEXPORT GSErrCode ACAPI_MenuItem_RegisterMenu	(short			menuStrResID,
													 short			promptStrResID,
													 APIMenuCodeID	menuPosCode,
													 GSFlags		menuFlags);


/**
 * @brief Registers a file type for I/O type add-ons.
 * @ingroup AddOnIntegration
 * @param refCon [in] An arbitrary number which identifies this file type within the add-on.
 * @param ftype [in] Macintosh file type (e.g. 'TEXT').
 * @param fcreator [in] Creator on Macintosh (e.g. 'GSAC' for Archicad).
 * @param extname [in] The extension used on Windows (e.g. "txt").
 * @param iconResID [in] An optional icon resource ID. This icon appears in the Open/Save dialogs on the Macintosh.
 * @param descStrResID [in] The resource ID of the resource containing the description of the file type.
 * @param descStrResItemID [in] The item ID within the resource of the item containing the description of the file type, or 0 when specifying MIME type as well (see Remarks).
 * @param methodFlags [in] Flags describing the Open/Save dialogs to add this file type to (see Remarks).
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function should be called from the RegisterInterface routine in your add-on. You can register more than one file type from the same add-on, appearing in different menus of the server application.
 * 			The supplied refCon parameter should be the same in the @ref ACAPI_AddOnIntegration_InstallFileTypeHandler function, which you have to call from your Initialize routine.
 * 			The methodFlags parameter defines which dialogs' file type popup should contain the registered file type:
 * 			|Flag|File Dialog|
 * 			|--- |--- |
 * 			|Open2DSupported|Open as 2D|
 * 			|Merge2DSupported|Merge|
 * 			|OpenLibPartSupported|Open Library Item|
 * 			|SaveAs2DSupported|Save as 2D|
 * 			|SaveAs3DSupported|Save as 3D|
 * 			|SaveAsFlySupported|Create Fly-Through/Sun Study|
 * 			|Import2DDrawingSupported|Import as Drawing|
 *
 * 			From API v4.2 you have the possibility to register the MIME type for the file as well. MIME (Multipurpose Internet Mail Extension) types are commonly accepted identifiers for certain media types. Specifying the MIME type makes the file format identification more accurate in the File Type Manager. If you decide to use this feature, you can do this in the following way:
 * 			- in the GRC file the string resource that describes the file format must contain two items: the descriptive name of the file format (e.g. "DWF File") the assigned MIME type (e.g. "model/vnd.dwf")
 * 			- the descriptive name of the file format (e.g. "DWF File")
 * 			- the assigned MIME type (e.g. "model/vnd.dwf")
 * 			- in the descStrResItemID parameter of the @ref ACAPI_AddOnIntegration_RegisterFileType function you must pass 0
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AddOnIntegration_RegisterFileType-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_RegisterFileType (Int32		refCon,
															   GSType		ftype,
															   GSType		fcreator,
															   const char*	extname,
															   short		iconResID,
															   short		descStrResID,
															   short		descStrResItemID,
															   API_IOMethod methodFlags);


/**
 * @brief Registers a new library part subtype.
 * @ingroup Toolbox
 * @ingroup LibraryManagement
 * @ingroup AddOnIntegration
 * @param signature [in] A four-character identifier of this library part subtype
 * @param templateFileResID [in] 'FILE' resource ID of the subtype template library part compiled into the add-on
 * @param transparentNode [in] Objects of this subtype can be shown on higher ancestry levels as well
 * @param stringResID [in] Resource ID of the library part subtype description string
 * @param smallIconResID [in] Resource ID of the small-sized toolbox (toolbar) item icon
 * @param largeIconResID [in] Resource ID of the large-sized toolbox item icon
 * @param toolGroupId [in] Toolbox item position
 * @param enableFlags [in] Enable or disable the subtype tool depending on the active window
 * @param defaultsResID [in] ID of the 'ACP0' resource that contains the element default values for this subtype
 * @return
 * 			- APIERR_BADPARS - templateFileResID refers to an invalid 'FILE' resource or the built-in library part cannot be accepted as subtype template.
 * 			- NoError - The function has completed with success.
 * @remarks This function registers a new library part subtype.
 * 			In order to have an own element subtype the add-on must contain a built-in library part in its reource module. This library part will be loaded into the active libraries, and become a new node in the ancestry tree.
 * 			The new element type will be identified with the signature identifier chosen by the add-on's writer. The signature should be unique in order to avoid collisions. You may pass 0 in the signature parameter if you do not need a new element type but a single subtype node.
 * 			The subtype can appear in the toolbox as an external tool, and also on the Windows toolbar. In this case you must pass two valid icon resource IDs in the smallIconResID and the largeIconResID parameters. The size of the icons should be 16x16 and 30x21 pixels respectively.
 * 			You can specify the position of the subtype item inserted into the toolbox with the toolGroupId parameter as follows:
 * 			|API_TBoxGroup|Meaning|
 * 			|--- |--- |
 * 			|TBoxGroup_Root|The subtype tool item will be appended to the group of model element tools|
 * 			|TBoxGroup_Objects|The subtype tool item will be added to the object tools|
 * 			|TBoxGroup_Openings|The subtype tool item will be added to the window/door tools|
 *
 * 			You can control the availability of the subtype tool in the toolbox by setting the `enableFlags` bits:
 * 			|API_TBoxEnabled|The subtype tool is enabled|
 * 			|--- |--- |
 * 			|API_TBoxEnabled_FloorPlan|on floor plan window|
 * 			|API_TBoxEnabled_ModelSection|on model type section and elevation windows|
 * 			|API_TBoxEnabled_DrawingSection|on drawing type section and elevation windows|
 * 			|API_TBoxEnabled_3D|on 3D model window|
 * 			|API_TBoxEnabled_Detail|on detail window|
 * 			|API_TBoxEnabled_Layout|on layout and master layout windows|
 * 			|API_TBoxEnabled_Worksheet|on worksheet window|
 * 			|API_TBoxEnabled_ModelInteriorElevation|on model type interior elevation windows|
 * 			|API_TBoxEnabled_DrawingInteriorElevation|on drawing type interior elevation windows|
 *
 * 			If you want to register your subtype tool without appearing in the toolbox, pass 0 for both the `smallIconResID` and the `largeIconResID` parameters.
 * 			If you register a subtype tool you should define the factory default values for this element type in an 'ACP0' resource. The element default will be
 * 			initialized with these parameters when no preferences data is stored. The structure of this resource is shown at the example below. The resource ID
 * 			should be passed in the defaultsResID parameter.
 * 			Learn more about this topic at the general description of Library Part Subtypes.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_RegisterSubtype-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_RegisterSubtype	(GSType				signature,				// identifier
																			 short				templateFileResID,		// subtype template (FILE resource ID)
																			 bool				transparentNode,		// allow ancestor tools to place object instances
																			 short				stringResID,			// tool descriptions (STR# resource ID)
																			 short				smallIconResID,			// toolbar icon
																			 short				largeIconResID,			// toolbox icon
																			 API_TBoxGroup		toolGroupId,			// toolbar group
																			 API_TBoxEnabled	enableFlags,			// toolbar enable flags
																			 short				defaultsResID);			// factory defaults (ACP0 resource ID)


/**
 * @brief Appends a custom panel to an element settings dialog.
 * @ingroup AddOnIntegration
 * @since Archicad 26
 * @param refCon [in] Unique reference number chosen for this panel
 * @param tool [in] The element type that identifies the settings dialog
 * @param iconId [in] Panel icon resource ID
 * @param stringId [in] Title text to appear in the handler area of the panel
 * @param pageId [in] Dialog resource ID of the tabpage
 * @param growType [in] Grow type of the tab page: can be DG_DLG_NOGROW, DG_DLG_HGROW, DG_DLG_VGROW, or DG_DLG_HGROW | DG_DLG_VGROW. This parameter is optional, the default is DG_DLG_NOGROW.
 * @param visibleByDefault [in] Show or hide the panel by default (optional parameter, false if omitted)
 * @return
 * 			- APIERR_BADPARS - The passed element type is invalid.
 * 			- APIERR_BADID - The passed tool / variation parameter pair does not identify a valid toolbox item (including invisible tools).
 * 			- NoError - The function has completed with success.
 * @remarks This function appends a new panel into an element settings dialog specified by tool and variation. In order to get panel create/destroy events you must install the panel handler callback functions with @ref ACAPI_AddOnIntegration_InstallPanelHandler.
 * 			For more details refer to the general description of Custom Panels in Settings Dialogs.
 * 			From version 26 the tool and variation parameters were merged into a single @c API_ElemType parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AddOnIntegration_RegisterSettingsPanel-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_RegisterSettingsPanel	(Int32					refCon,
																						 const API_ElemType&	tool,
																						 short					iconId,
																						 short					stringId,
																						 short					pageId,
																						 short					growType = 0,	// means NoGrow
																						 bool					visibleByDefault = false);


/**
 * @brief Appends a custom panel to an attribute settings dialog.
 * @ingroup AddOnIntegration
 * @param refCon [in] Unique reference number chosen for this panel
 * @param attr [in] The attribute type that identifies the settings dialog
 * @param iconId [in] Panel icon resource ID
 * @param stringId [in] Title text to appear in the handler area of the panel
 * @param pageId [in] Dialog resource ID of the tabpage
 * @param growType [in] Grow type of the tab page: can be DG_DLG_NOGROW, DG_DLG_HGROW, DG_DLG_VGROW, or DG_DLG_HGROW | DG_DLG_VGROW. This parameter is optional, the default is DG_DLG_NOGROW.
 * @return
 * 			- APIERR_BADPARS - The attr parameter is invalid.
 * 			- APIERR_NOTSUPPORTED - The attribute type does not support custom panels.
 * 			- NoError - The function has completed with success.
 * @remarks This function appends a new panel into an attribute settings dialog.
 * 			For more details refer to the general description of Custom Panels in Settings Dialogs.
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_RegisterAttributePanel	(Int32					refCon,
																						 API_AttrTypeID			attr,
																						 short					iconId,
																						 short					stringId,
																						 short					pageId,
																						 short					growType = 0);	// means NoGrow


/**
 * @brief Appends a custom panel to the info box.
 * @ingroup AddOnIntegration
 * @since Archicad 26
 * @param refCon [in] Unique reference number chosen for this panel
 * @param tool [in] The element type that identifies the settings dialog
 * @param stringId [in] Title text to appear in the handler area of the panel
 * @param pageId [in] Dialog resource ID of the tabpage
 * @param visibleByDefault [in] Show or hide the panel by default (optional parameter, false if omitted)
 * @return
 * 			- APIERR_BADPARS - The passed element type is invalid.
 * 			- APIERR_BADID - The passed tool / variation parameter pair does not identify a valid toolbox item (including invisible tools).
 * 			- NoError - The function has completed with success.
 * @remarks This function appends a new panel into an element settings dialog specified by tool. In order to get panel create/destroy events you must install the panel handler callback functions with @ref ACAPI_AddOnIntegration_InstallPanelHandler.
 * 			Compared to the @ref ACAPI_AddOnIntegration_RegisterSettingsPanel function there is no need to specify icon resource ID.
 * 			For more details refer to the general description of Custom Panels in Settings Dialogs.
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_RegisterInfoBoxPanel	(Int32					refCon,
																					 const API_ElemType&	tool,
																					 short					stringId,
																					 short					pageId,
																					 bool					visibleByDefault = false);


/**
 * @brief Registers an external symbol type with Archicad.
 * @ingroup LibraryPart
 * @ingroup AddOnIntegration
 * @param signature [in] Unique identifier of the new symbol type (a four-character ID).
 * @param typeID [in] Type of the new symbol (can be @c API_ObjectID, @c API_LampID, @c API_WindowID, or @c API_DoorID).
 * @param stringResID [in] Resource containing the description of the new symbol type.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Invalid symbol type.
 * @remarks This function should be called from your add-on's RegisterInterface routine. More than one external symbol can be registered from one add-on. After registration you should also install a callback function with @ref ACAPI_LibraryPart_InstallESYMHandler in your Initialize function, which will handle the events coming from Archicad.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_RegisterESYM-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_RegisterESYM	(GSType			signature,				// LibPart owner ID
																		 API_LibTypeID	typeID,					// LibPart base type (Window, Door, Object, Lamp)
																		 short			stringResID);			// description


/**
 * @brief Registers a property handler.
 * @ingroup Property
 * @ingroup AddOnIntegration
 * @param assignStrResID [in] The string resource ID, which will be used in Archicad's dialogs.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function should be called from the RegisterInterface routine in your add-on.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Property_RegisterPropertyObjectHandler-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Property_RegisterPropertyObjectHandler (short assignStrResID);


/**
 * @brief Registers built-in library parts to be loaded.
 * @ingroup AddOnIntegration
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function notifies the host application that your add-on has library parts compiled into the add-on as 'FILE' resources. The application will add the add-on module to the active libraries and the library parts will be available as read only objects.
 * 			You can retrieve the unique ID of a built-in library part with the @ref ACAPI_LibraryPart_GetBuiltInLibpartUnId goodie function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AddOnIntegration_RegisterBuiltInLibrary-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_RegisterBuiltInLibrary (void);


/**
 * @brief Registers the add-on to be called for merging and converting its moduldata.
 * @ingroup AddOnIntegration
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks Call this function from RegisterInterface to let Archicad know that the add-on has @ref APIModulDataMergeHandlerProc and/or @ref APIModulDataSaveOldFormatHandlerProc callback function implemented for merging and converting its modules. In order this functions to be called on the adequate event, the add-on needs to pass the function pointers to Archicad from Initialize with @ref ACAPI_AddOnIntegration_InstallModulDataMergeHandler and @ref ACAPI_AddOnIntegration_InstallModulDataSaveOldFormatHandler, respectively.
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_RegisterModulDataHandler (void);


/**
 * @brief Tells Archicad that your add-on wants to modify classification visibility.
 * @ingroup AddOnIntegration
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function should be called from the RegisterInterface routine in your add-on.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AddOnIntegration_RegisterClassificationVisibilityHandler-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_RegisterClassificationVisibilityHandler (void);


/**
 * @brief Tells Archicad that your add-on wants to modify property visibility.
 * @ingroup Property
 * @ingroup AddOnIntegration
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function should be called from the RegisterInterface routine in your add-on.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Property_RegisterPropertyVisibilityHandler-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Property_RegisterPropertyVisibilityHandler (void);


/**
 * @brief Registers the add-on to be called for merging and converting its custom data stored in AddOnObjects.
 * @ingroup AddOnObject
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks Call this function from RegisterInterface to let Archicad know that the add-on has APIAddOnObjectMergeHandlerProc and/or APIAddOnObjectSaveOldFormatHandlerProc and/or APIAddOnObjectConvertNewFormatHandlerProc callback function implemented for merging and converting its custom data. In order this functions to be called on the adequate event, the add-on needs to pass the function pointers to Archicad from Initialize with @ref ACAPI_AddOnObject_InstallAddOnObjectMergeHandler, @ref ACAPI_AddOnObject_InstallAddOnObjectSaveOldFormatHandler and @ref ACAPI_AddOnObject_InstallAddOnObjectConvertNewFormatHandler, respectively.
 */
__APIEXPORT GSErrCode ACAPI_AddOnObject_RegisterAddOnObjectHandler (void);


/**
 * @brief Registers the add-on to be called when Navigator AddOn viewpoints are merged, saved to older format, or converted from older format to current format.
 * @ingroup AddOnIntegration
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks Call this function from RegisterInterface to let Archicad know that the AddOn has @ref APINavigatorAddOnViewPointDataMergeHandlerProc, @ref APINavigatorAddOnViewPointDataSaveOldFormatHandlerProc or @ref APINavigatorAddOnViewPointDataConvertNewFormatHandlerProc callback function implemented for merging and converting its Navigator AddOn viewpoint data.
 * 			In order these functions to be called on the adequate event, the AddOn needs to pass the function pointers to @ref ACAPI_AddOnIntegration_InstallNavigatorAddOnViewPointDataMergeHandler, @ref ACAPI_AddOnIntegration_InstallNavigatorAddOnViewPointDataSaveOldFormatHandler and @ref ACAPI_AddOnIntegration_InstallNavigatorAddOnViewPointDataConvertNewFormatHandler respectively. Call these install functions in the AddOn's Initialize function.
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_RegisterNavigatorAddOnViewPointDataHandler (void);


/**
 * @brief Create an observer to an element settings dialog.
 * @ingroup AddOnIntegration
 * @since Archicad 26
 * @param tool [in] The element type that identifies the settings dialog
 * @return
 * 			- APIERR_BADPARS - The passed element type is invalid.
 * 			- APIERR_BADID - The passed tool does not identify a valid toolbox item (including invisible tools).
 * 			- NoError - The function has completed with success.
 * @remarks This function creates an observer for an element settings dialog specified by tool. In order to get settings dialog create or destroy events you must install the settings handler callback functions with @ref ACAPI_AddOnIntegration_InstallSettingsHandler.
 * 			This function should be called from your add-on's @ref RegisterInterface routine. You can register more than one observers from the same add-on for different settings dialogs.
 * 			From version 26 the tool and variation parameters were merged into a single @c API_ElemType parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AddOnIntegration_RegisterSettingsObserver-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_RegisterSettingsObserver (const API_ElemType& tool);


/**
 * @brief Registers an attribute manager format which can be used in attribute manager import.
 * @ingroup AddOnIntegration
 * @since Archicad 26
 * @param formatData [in] Stores parameters of the new attribute manager import format.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks For further informations read the documentation of @ref API_AttributeManagerFormat structure.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AddOnIntegration_RegisterAttributeImportFormat-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_RegisterAttributeImportFormat (const API_AttributeManagerFormat& formatData);


/**
 * @brief Registers a publish format which can be used in publisher tree.
 * @ingroup AddOnIntegration
 * @param formatData [in] Stores parameters of the new publish format
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks For further informations read the documentation of @ref API_PublishFormatData structure.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AddOnIntegration_RegisterPublishFormat-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_RegisterPublishFormat (const API_PublishFormatData& formatData);



/**
 * @brief Installs a callback for handling command calls from other add-ons.
 * @ingroup AddOnIntegration
 * @param cmdID [in] An identifier of the command to install the callback procedure for. This should be the same what you used in the @ref ACAPI_AddOnAddOnCommunication_RegisterSupportedService as the command identifier in the RegisterInterface function.
 * @param cmdVersion [in] An identifier of the command to install the callback procedure for. This should be the same what you used in the @ref ACAPI_AddOnAddOnCommunication_RegisterSupportedService as the command version number in the RegisterInterface function.
 * @param handlerProc [in] The callback function to handle the command calls.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function should be called in the Initialize function of your add-on. It installs the callback function which is called when the other add-ons would like to use the supported services of your add-on.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AddOnIntegration_InstallModulCommandHandler-Example-Snippet
 */	// Initialize
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_InstallModulCommandHandler  (GSType					cmdID,
																							Int32					cmdVersion,
																							APIModulCommandProc*	handlerProc);


/**
 * @brief Installs a callback procedure for handling the add-on's menu commands.
 * @ingroup MenuItem
 * @ingroup AddOnIntegration
 * @param menuStrResID [in] An identifier of the menu to install the callback procedure for. This should be the same what you used in the @ref ACAPI_MenuItem_RegisterMenu as a menu string resource number in the RegisterInterface function.
 * @param handlerProc [in] The callback function to handle the menu commands.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function should be called in the Initialize function of your add-on. It installs the callback function which is called when the user chooses one of your menu commands.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_MenuItem_InstallMenuHandler-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_MenuItem_InstallMenuHandler  (short					menuStrResID,
																			APIMenuCommandProc*		handlerProc);


/**
 * @brief Installs a callback procedure for handling file operations.
 * @ingroup AddOnIntegration
 * @param cmdID [in] An identifier of the file type to install the callback procedure for. This should be the same what you used in the @ref ACAPI_AddOnIntegration_RegisterFileType as a reference number in the RegisterInterface function.
 * @param handlerProc [in] The callback function to handle the different file operations.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function should be called in the Initialize function of your add-on. It installs the callback function which is called when the user chooses your registered file format in one of the Open/Save/Merge dialogs.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AddOnIntegration_InstallFileTypeHandler-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_InstallFileTypeHandler  (GSType					cmdID,
																						APIIOCommandProc*		handlerProc);


/**
 * @brief Installs a callback procedure for handling file operations.
 * @ingroup AddOnIntegration
 * @param cmdID [in] An identifier of the file type to install the callback procedure for. This should be the same what you used in the @ref ACAPI_AddOnIntegration_RegisterFileType as a reference number in the RegisterInterface function.
 * @param handlerProc [in] The callback function to handle the different file operations.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function should be called in the Initialize function of your add-on. It installs the callback function which is called when the user chooses your registered file format in one of the Open/Save dialogs.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AddOnIntegration_InstallFileTypeHandler3D-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_InstallFileTypeHandler3D	   (GSType					cmdID,
																							APIIO3DCommandProc*		handlerProc);


/**
 * @brief Installs the creation and destroy handlers for the registered custom settings panel.
 * @ingroup AddOnIntegration
 * @param refCon [in] Panel reference number
 * @param handlerCreateProc [in] Callback function, called when the panel is created.
 * @param handlerDestroyProc [in] Callback function, called when the panel is destroyed.
 * @return
 * 			- APIERR_REFUSEDPAR - There is no panel registered with refcon by the add-on.
 * 			- NoError - The function has completed with success.
 * @remarks This function installs the callback functions for handling create/delete events of the dialog panel registered by @ref ACAPI_AddOnIntegration_RegisterSettingsPanel, @ref ACAPI_AddOnIntegration_RegisterInfoBoxPanel or @ref ACAPI_AddOnIntegration_RegisterAttributePanel.
 * 			The @ref ACAPI_AddOnIntegration_InstallPanelHandler function should be called from Initialize.
 * 			The 'create' handler is called when the panel is created. The handler must create the tabpage and the observer. The 'destroy' handler is called when the panel is destroyed. The handler must destroy the tabpage and the observer.
 * 			For more details refer to the general description of Custom Panels in Settings Dialogs.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AddOnIntegration_InstallPanelHandler-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_InstallPanelHandler (Int32					refCon,
																					APIPanelCreateProc*		handlerCreateProc,
																					APIPanelDestroyProc*	handlerDestroyProc);


/**
 * @brief Installs the Add-On command handler object.
 * @ingroup AddOnAddOnCommunication
 * @param addOnCommand [in] The Add-On command handler object. After the @c ACAPI_AddOnAddOnCommunication_InstallAddOnCommandHandler is called, the ownership is passed and the object can not be used.
 * @return
 * 			- APIERR_REFUSEDPAR - The addOnCommand parameter is nullptr.
 * 			- APIERR_BADNAME - There is already an @ref API_AddOnCommand installed with the same name for this Add-On.
 * 			- APIERR_BADPARS - The input, output or schema definitions is not in a valid JSON format.
 * 			- NoError - The function has completed with success.
 * @remarks This function installs a handler object for the corresponding HTTP requests. The handler object is identified by the Add-On MDID and its name.
 * 			The @c ACAPI_AddOnAddOnCommunication_InstallAddOnCommandHandler function should be called from Initialize.
 * 			After a successful @c ACAPI_AddOnAddOnCommunication_InstallAddOnCommandHandler function call, the Add-On stays in the memory.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AddOnAddOnCommunication_InstallAddOnCommandHandler-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AddOnAddOnCommunication_InstallAddOnCommandHandler (GS::Owner<API_AddOnCommand> addOnCommand);


/**
 * @brief Installs a callback for handling external symbols.
 * @ingroup LibraryPart
 * @ingroup AddOnIntegration
 * @param signature [in] A four-character identifier of the external symbol.
 * @param handlerProc [in] The callback function to handle the creation and the editing of the external symbol.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function should be called in the Initialize function of your add-on.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_InstallESYMHandler-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_InstallESYMHandler (GSType					signature,
																			  APIESYMCommandProc*		handlerProc);


/**
 * @brief Installs the property handler function for the given menu item.
 * @ingroup Property
 * @ingroup AddOnIntegration
 * @param strResID [in] The string resource ID you install the property handler for.
 * @param propertyCommandProc [in] The property command handler function.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks The string resource will appear in Archicad's dialogs. This function should be called from the Initialize function of the add-on, after registering the property handler with @ref ACAPI_Property_RegisterPropertyObjectHandler.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Property_InstallPropertyObjectHandler-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Property_InstallPropertyObjectHandler	(short					 		strResID,
																					 APIPropertyObjectCommandProc*  propertyCommandProc);


/**
 * @brief Installs a callback procedure for handling the module data merge operations.
 * @ingroup AddOnIntegration
 * @param mergeHandlerProc [in] The callback procedure which will handle the module data merge. Can be nullptr ; this removes the installed callback.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function should be called in the Initialize function of your add-on to pass the pointer of the APIModulDataMergeHandlerProc callback routine implemented for resolving conflicts between two instances of the same custom data section of the add-on during a merge operation.
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_InstallModulDataMergeHandler	(APIModulDataMergeHandlerProc* mergeHandlerProc);


/**
 * @brief Installs a callback procedure for converting module data into older format.
 * @ingroup AddOnIntegration
 * @param modulDataSaveOldFormatProc [in] The callback procedure to convert module data. Passing nullptr in this parameter uninstalls the previously installed handler function.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function should be called in the Initialize function of your add-on to pass the pointer of the APIModulDataSaveOldFormatHandlerProc callback routine implemented for converting modules of the add-on into previous format.
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_InstallModulDataSaveOldFormatHandler (APIModulDataSaveOldFormatHandlerProc* modulDataSaveOldFormatProc);


/**
 * @brief Installs a callback procedure for handling the converison of the user data, the addOn attached to an elemeset
 * @ingroup AddOnIntegration
 * @param elemSetSaveOldFormatProc [in] The callback function to handle the backward conversion
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks The installed callback is called when the plan is saved back to an earlier version of Archicad. You can handle any change in the user data's here, to make it readable for previous version.
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_InstallElemSetSaveOldFormatHandler (APIElemSetSaveOldFormatHandlerProc* elemSetSaveOldFormatProc);



/**
 * @brief Installs a callback procedure for handling the AddOnObject merge operations.
 * @ingroup AddOnObject
 * @param mergeHandlerProc [in] The callback procedure which will handle the AddOnObject data merge. Can be nullptr ; this removes the installed callback.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function should be called in the Initialize function of your add-on to pass the pointer of the APIAddOnObjectMergeHandlerProc callback routine implemented for resolving conflicts between two lists of the AddOnObjects of the add-on during a merge operation.
 */
__APIEXPORT GSErrCode ACAPI_AddOnObject_InstallAddOnObjectMergeHandler			(APIAddonObjectMergeHandlerProc*				mergeHandlerProc);


/**
 * @brief Installs a callback procedure for converting AddOnObject data into older format.
 * @ingroup AddOnObject
 * @param saveOldFormatProc [in] The callback procedure to convert AddOnObject data. Passing nullptr in this parameter uninstalls the previously installed handler function.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks In order to save the add-on's AddOnObject data in the proper format into a previous version project file, you need to implement this callback function, and pass it to Archicad with @ref ACAPI_AddOnObject_InstallAddOnObjectSaveOldFormatHandler during the Initialize phase. It is also necessary to notify Archicad about this capability of the add-on by calling @ref ACAPI_AddOnObject_RegisterAddOnObjectHandler from the @ref RegisterInterface function.
 * 			This handler function is called whenever the user saves the project into an older format, and the add-on has any AddOnObject stored currently into the project. The data should be constructed according to the required version into @ref API_AddonObject structures, and these structures should be pushed into the @c oldFormatAddOnObjectArray array.
 * 			The memory allocated for the converted AddOnObjects by the add-on's handler function will be released by the caller application.
 * 			If you need to delete an AddOnObject (e.g. it cannot be read by a previous version) then simply don't push it into the array. Order of the converted @ref API_AddonObject s is irrelevant.
 * 			You must pay attention to not create more than one @ref API_AddonObject s with the same name if the AddOnObject is Unique.
 * 			Because Unique AddOnObjects is an API 21 () feature, please pay special attention to converting AddOnObjects with UniqueAddOnObject @ref API_AddonObjectType by either setting their type to GeneralAddOnObject or leaving them from @c oldFormatAddOnObjectArray.
 */
__APIEXPORT GSErrCode ACAPI_AddOnObject_InstallAddOnObjectSaveOldFormatHandler	(APIAddonObjectSaveOldFormatHandlerProc*		saveOldFormatProc);


/**
 * @brief Installs a callback procedure for converting old format AddOnObject data into current format.
 * @ingroup AddOnObject
 * @param convertNewFormatProc [in] The callback procedure to convert AddOnObject data. Passing nullptr in this parameter uninstalls the previously installed handler function.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks In order to convert the add-on's AddOnObject data into current format, you need to implement this callback function, and pass it to Archicad with @ref ACAPI_AddOnObject_InstallAddOnObjectConvertNewFormatHandler during the Initialize phase. It is also necessary to notify Archicad about this capability of the add-on by calling @ref ACAPI_AddOnObject_RegisterAddOnObjectHandler from the RegisterInterface function.
 * 			This handler function is called whenever the user opens an old version project, and the add-on has any AddOnObject stored in the original project. The data should be constructed according to the current version into @c API_AddonObject structures, and these structures should be pushed into the currentFormatAddOnObjectArray array.
 * 			The memory allocated for the converted AddOnObject by the add-on's handler function will be released by the caller application.
 * 			You must pay attention to not create more than one @ref API_AddonObject s with the same name if the AddOnObject is Unique.
 */
__APIEXPORT GSErrCode ACAPI_AddOnObject_InstallAddOnObjectConvertNewFormatHandler (APIAddonObjectConvertNewFormatHandlerProc*	convertNewFormatProc);


/**
 * @brief Installs a callback procedure for handling the Navigator AddOn viewpoint merge operations.
 * @ingroup AddOnIntegration
 * @param mergeHandlerProc [in] The callback procedure which will handle the Navigator AddOn viewpoint data merge. If nullptr is passed, an installed callback function is removed.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function should be called in the Initialize function of your AddOn.
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_InstallNavigatorAddOnViewPointDataMergeHandler			 (APINavigatorAddOnViewPointDataMergeHandlerProc*				mergeHandlerProc);


/**
 * @brief Installs a callback procedure for converting Navigator AddOn viewpoints into older format.
 * @ingroup AddOnIntegration
 * @param saveOldFormatProc [in] The callback procedure which will handle the Navigator AddOn viewpoints' conversion into older format. If nullptr is passed, an installed callback function is removed.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function should be called in the Initialize function of your AddOn.
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_InstallNavigatorAddOnViewPointDataSaveOldFormatHandler	 (APINavigatorAddOnViewPointDataSaveOldFormatHandlerProc*		saveOldFormatProc);


/**
 * @brief Installs a callback procedure for converting Navigator AddOn viewpoints into current format.
 * @ingroup AddOnIntegration
 * @param convertNewFormatProc [in] The callback procedure which will handle the Navigator AddOn viewpoints' conversion into current format. If nullptr is passed, an installed callback function is removed.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function should be called in the Initialize function of your AddOn.
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_InstallNavigatorAddOnViewPointDataConvertNewFormatHandler (APINavigatorAddOnViewPointDataConvertNewFormatHandlerProc*	convertNewFormatProc);


/**
 * @brief Installs the create and destroy handlers for the registered settings observer.
 * @ingroup AddOnIntegration
 * @since Archicad 26
 * @param tool [in] The element type that identifies the settings dialog
 * @param handlerCreateProc [in] Callback function, called when the settings dialog is created.
 * @param handlerDestroyProc [in] Callback function, called when the settings dialog is destroyed.
 * @return
 * 			- APIERR_BADPARS - No settings observer was registered for the settings dialog specified by tool and variaton.
 * 			- NoError - The function has completed with success.
 * @remarks This function installs the callback functions for handling create/destroy events of the settings dialog observer registered by @ref ACAPI_AddOnIntegration_RegisterSettingsObserver.
 * 			The @c ACAPI_AddOnIntegration_InstallSettingsHandler function should be called from Initialize.
 * 			The 'create' handler is called when the settings dialog is created. The 'destroy' handler is called when the settings dialog is destroyed.
 * 			From version 26 the tool and variation parameters were merged into a single @ref API_ElemType parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AddOnIntegration_InstallSettingsHandler-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_InstallSettingsHandler (const API_ElemType&			tool,
																					   APISettingsCreateProc*		handlerCreateProc,
																					   APISettingsDestroyProc*		handlerDestroyProc);


/**
 * @brief Installs the classification visibility handler function.
 * @ingroup AddOnIntegration
 * @param handlerProc [in] The classification visibility handler function.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function should be called from the Initialize function of the add-on, after registering the classification handler with @ref ACAPI_AddOnIntegration_RegisterClassificationVisibilityHandler.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AddOnIntegration_InstallClassificationVisibilityHandler-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_InstallClassificationVisibilityHandler (APIClassificationVisibilityHandlerProc* handlerProc);


/**
 * @brief Installs the property visibility handler function.
 * @ingroup Property
 * @ingroup AddOnIntegration
 * @param handlerProc [in] The property visibility handler function.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function should be called from the Initialize function of the add-on, after registering the property handler with @ref ACAPI_Property_RegisterPropertyVisibilityHandler.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Property_InstallPropertyVisibilityHandler-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Property_InstallPropertyVisibilityHandler (APIPropertyVisibilityHandlerProc* handlerProc);


/**
 * @brief Installs the save methods for the Publisher
 * @ingroup AddOnIntegration
 * @param mimeType The unique mimeType which identifies the new publish format
 * @param saveProc Callback function, called in case of publishing
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function installs the callback functions for the new publish formats. The publisher will call the registered function, during the publishing command.
 * 			Example Refer to the Format Register Test example project of the API Development Kit.
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_InstallPublisherSaveMethod (const char* mimeType, SaveProc* saveProc);


/**
 * @brief Installs the option methods for the Publisher
 * @ingroup AddOnIntegration
 * @param mimeType The unique mimeType which identifies the new publish format
 * @param saveOptionProc Callback function, called in case of publishing
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function installs the callback functions for the new publish formats. The Add-on can create his own option dialog, the settings are stored in @c API_Userdata structures.
 * 			Example Refer to the Format Register Test example project of the API Development Kit.
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_InstallPublisherSaveOption (const char* mimeType, SaveOptionProc* saveOptionProc);


/**
 * @brief Installs the translator getter function for the Publisher
 * @ingroup AddOnIntegration
 * @since Archicad 26
 * @param mimeType The unique mimeType which identifies the new publish format
 * @param translatorGetterProc Callback function, called from the Organizer
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function installs the callback functions for the new publish formats. The publisher will call the registered function, during the setup of the formats in the Organizer.
 * 			Example Refer to the Format Register Test example project of the API Development Kit.
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_InstallPublisherTranslatorGetter (const char* mimeType, TranslatorGetterProc* translatorGetterProc);


/**
 * @brief Installs the default translator getter function for the Publisher
 * @ingroup AddOnIntegration
 * @since Archicad 26
 * @param mimeType The unique mimeType which identifies the new publish format
 * @param defaultTranslatorGetterProc Callback function, called from the Organizer
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function installs the callback functions for the new publish formats. The publisher will call the registered function, during the setup of the formats in the Organizer.
 * 			Example Refer to the Format Register Test example project of the API Development Kit.
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_InstallPublisherDefaultTranslatorGetter (const char* mimeType, DefaultTranslatorGetterProc* defaultTranslatorGetterProc);


/**
 * @brief Installs the format info getter function for the Publisher
 * @ingroup AddOnIntegration
 * @since Archicad 27
 * @param mimeType The unique mimeType which identifies the new publish format
 * @param infoGetterProc Callback function, called from the Organizer
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function installs the callback functions for the new publish formats. The publisher will call the registered function, during the setup of the formats in the Organizer.
 * 			Example Refer to the Format Register Test example project of the API Development Kit.
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_InstallPublisherFormatInfoGetter (const char* mimeType, InfoGetterProc* infoGetterProc);


/**
 * @brief Installs the import method for the Attribute Manager
 * @ingroup AddOnIntegration
 * @ingroup Attribute
 * @since Archicad 26
 * @param fileExtension The unique file extension which identifies the new import format.
 * @param importProc Callback function, called when import a file with the registered extension.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function installs the callback function for the new attribute import format. The Attribute Manager will call the registered function, during the import command.
 * 			Example Refer to the Attribute Test example project of the API Development Kit.
 */
__APIEXPORT GSErrCode ACAPI_AddOnIntegration_InstallAttrManagerImportMethod (const GS::UniString& fileExtension, ImportAttrProc* importProc);




/**
 * @brief Informs Archicad about the additionally created file during exporting or publishing. Required for handling them with the target file. (E.g. uploading to BIMcloud together.)
 * @ingroup ProjectOperation
 * @param path [in] The path to the created file.
 * @return
 * 			- NoError - The function has completed with success.
 */
__APIEXPORT GSErrCode ACAPI_ProjectOperation_AdditionalFileWasCreated (const IO::Location& path);


/**
 * @brief Frees the memory occupied by a handle to an array of @ref API_AddParType.
 * @ingroup LibraryPart
 * @param addPars [in] A handle to an array of @ref API_AddParType.
 * @return
 * @remarks This is the recommended way of disposing the parameter description handles for compatibility reasons, as in a later version of the API the @ref API_AddParType structure might change. Also, you might have array-type parameters among the additional parameters; this function also takes care of those.
 */
__APIEXPORT GSErrCode ACAPI_DisposeAddParHdl (API_AddParType ***addPars);


/**
 * @brief Frees the memory occupied by a handle to an array of @ref API_ParagraphType.
 * @ingroup Element
 * @param paragraphs [in] A handle to an array of @ref API_ParagraphType.
 * @return
 * @remarks This is the recommended way of disposing the paragraph handles for compatibility reasons, as in a later version of the API the @ref API_ParagraphType structure might change.
 */
__APIEXPORT GSErrCode ACAPI_DisposeParagraphsHdl (API_ParagraphType ***paragraphs);


/**
 * @brief Frees the memory occupied by all of the allocated memo handles.
 * @ingroup Element
 * @param memo [in] Points to an @ref API_ElementMemo structure which contains handles used for previous operations and not needed any more.
 * @return
 * @remarks This is the recommended way of disposing the memo handles for compatibility reasons, as in a later version of the API the @ref API_ElementMemo structure might change.
 */
__APIEXPORT GSErrCode ACAPI_DisposeElemMemoHdls (API_ElementMemo *memo);


/**
 * @brief Frees the memory occupied by all of the attribute definition handles.
 * @ingroup Attribute
 * @param defs [in] Points to an @ref API_AttributeDef structure which contains handles used for previous operations and not needed any more.
 * @return
 * @remarks This is the recommended way of disposing the attribute definition handles for compatibility reasons, as in a later version of the API the @ref API_AttributeDef structure might change.
 */
__APIEXPORT GSErrCode ACAPI_DisposeAttrDefsHdls (API_AttributeDef *defs);


/**
 * @brief Frees the memory occupied by all of the attribute definition handles.
 * @ingroup Attribute
 * @param defs [in] Points to an @ref API_AttributeDefExt structure which contains handles used for previous operations and not needed any more.
 * @return
 * @remarks This is the recommended way of disposing the attribute definition handles for compatibility reasons, as in a later version of the API the @ref API_AttributeDefExt structure might change.
 */
__APIEXPORT GSErrCode ACAPI_DisposeAttrDefsHdlsExt (API_AttributeDefExt *defs);


/**
 * @brief Frees the memory occupied by all of the allocated room relation handles.
 * @ingroup Element
 * @since Archicad 26
 * @param roomInfo [in] Points to an @ref API_RoomRelation structure which contains handles used for previous operations and not needed any more.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This is the recommended way of disposing the room relation handles for compatibility reasons, as in a later version of the API the @ref API_RoomRelation structure might change.
 */
__APIEXPORT GSErrCode ACAPI_DisposeRoomRelationHdls (API_RoomRelation *roomInfo);


/**
 * @brief Frees the memory occupied by all of the allocated wall relation handles.
 * @ingroup Element
 * @param wallInfo [in] Points to an @ref API_WallRelation structure which contains handles used for previous operations and not needed any more.
 * @remarks This is the recommended way of disposing the wall relation handles for compatibility reasons, as in a later version of the API the @ref API_WallRelation structure might change.
 */
__APIEXPORT void ACAPI_DisposeWallRelationHdls (API_WallRelation *wallInfo);


/**
 * @brief Frees the memory occupied by all of the allocated beam segment relation handles.
 * @ingroup Element
 * @param segmentInfo [in] Points to an @ref API_BeamSegmentRelation structure which contains handles used for previous operations and not needed any more.
 * @remarks This is the recommended way of disposing the beam segment relation handles for compatibility reasons, as in a later version of the API the @ref API_BeamSegmentRelation structure might change.
 */
__APIEXPORT void ACAPI_DisposeBeamSegmentRelationHdls (API_BeamSegmentRelation *segmentInfo);


/**
 * @brief Frees the memory occupied by all of the allocated beam relation handles.
 * @ingroup Element
 * @param beamInfo [in] Points to an @ref API_BeamRelation structure which contains handles used for previous operations and not needed any more.
 * @remarks This is the recommended way of disposing the beam relation handles for compatibility reasons, as in a later version of the API the @ref API_BeamRelation structure might change.
 */
__APIEXPORT void ACAPI_DisposeBeamRelationHdls (API_BeamRelation *beamInfo);


/**
 * @brief Frees the curtain wall contour pointer.
 * @ingroup CurtainWall
 * @param contours [in] A pointer to an array of @ref API_CWContourData.
 * @return
 * @remarks This is the recommended way of disposing the curtain wall contour for compatibility reasons.
 */
__APIEXPORT GSErrCode ACAPI_FreeCWContourPtr (API_CWContourData **contours);


/**
 * @brief Frees the GDL model view options pointer.
 * @ingroup Navigator
 * @param gdlModelViewOptions [in] A pointer to an array of @ref API_GDLModelViewOptions.
 * @remarks This is the recommended way of disposing the gdlOptions member of @ref API_ModelViewOptions structure.
 */
__APIEXPORT void ACAPI_FreeGDLModelViewOptionsPtr (API_GDLModelViewOptions **gdlModelViewOptions);


/**
 * @brief Reads a string from an 'STR# ' string list resource.
 * @ingroup Resource
 * @param str [out] The pointer of the string.
 * @param resID [in] The resource ID of the ' STR# ' resource in the GRC file.
 * @param index [in] The index of the string in the resource.
 * @param resModule [in] The resource module to load the resource from. The default value is the add-on's own resource module.
 * @return
 * 			- true - The string was retrieved successfully.
 * 			- false - The string wasn't retrieved.
 * @remarks This function is used to load a string from a string list resource, which requires localization.
 * 			The GRC compiler uses the ' STR# ' resource type for this purpose. The different lines in the resource will be the indices referenced by index parameter. For more information about the structure of the GRC file please refer to the GRC documentation.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Resource_GetLocStr-Example-Snippet
 */
__APIEXPORT bool ACAPI_Resource_GetLocStr (char *str, short resID, short index, GSResModule resModule = ACAPI_GetOwnResModule ());


/**
 * @brief Reads a unicode string from an 'STR# ' string list resource.
 * @ingroup Resource
 * @param str [out] The pointer of the string.
 * @param resID [in] The resource ID of the ' STR# ' resource in the GRC file.
 * @param index [in] The index of the string in the resource.
 * @param resModule [in] The resource module to load the resource from. The default value is the add-on's own resource module.
 * @return
 * 			- true - The string was retrieved successfully.
 * 			- false - The string wasn't retrieved.
 * @remarks This function is used to load a Unicode string from a string list resource, which requires localization.
 * 			The GRC compiler uses the ' STR# ' resource type for this purpose. The different lines in the resource will be the indices referenced by index parameter. For more information about the structure of the GRC file please refer to the GRC documentation.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Resource_GetLocUStr-Example-Snippet
 */
__APIEXPORT bool ACAPI_Resource_GetLocUStr (GS::uchar_t *str, short resID, short index, GSResModule resModule = ACAPI_GetOwnResModule ());


/**
 * @brief Reads a string from an 'STRf ' string list resource.
 * @ingroup Resource
 * @param str The pointer of the string.
 * @param resID The resource ID of the ' STRf ' resource in the GRC file.
 * @param index The index of the string in the resource.
 * @param resModule [in] The resource module to load the resource from. The default value is the add-on's own resource module.
 * @return
 * 			- true - The string was retrieved successfully.
 * 			- false - The string wasn't retrieved.
 * @remarks This function is used to load a string from a string list resource, which is not required to localize.
 * 			The GRC compiler uses the ' STRf ' resource type for this purpose. The different lines in the resource will be the indices referenced by index parameter. For more information about the structure of the GRC file please refer to the GRC documentation.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Resource_GetFixStr-Example-Snippet
 */
__APIEXPORT bool ACAPI_Resource_GetFixStr (char *str, short resID, short index, GSResModule resModule = ACAPI_GetOwnResModule ());


/**
 * @brief Instructs the host application to keep the add-on in the memory after execution.
 * @ingroup AddOnLifetime
 * @ingroup AddOnIntegration
 * @param keepIn [in] If true the add-on will stay in the memory.
 * @remarks This function is used to keep the add-on in the memory.
 * 			You should call this function with true each time your add-on is called to stay in memory. The values of all your global variables stay the same between the calls to your add-on. Also, when in memory, the Initialize and the FreeData functions of your add-on are not called. See more about this topic at the Control the Load/Unload Mechanism part of the Tips and Tricks.
 */
/* -- Client Manager ---------------------- */
__APIEXPORT void ACAPI_KeepInMemory (bool keepIn);


/**
 * @brief Saves custom preferences data into the preferences file.
 * @ingroup Preferences
 * @param version [in] The version of the data to be stored.
 * @param nByte [in] The size of the data to be stored.
 * @param data [in] The preferences data you would like to store.
 * @return
 * @remarks This function is used to save your own options or preferences into the preferences file of the server application, and can be later retrieved with @ref ACAPI_GetPreferences.
 * 			If you store incompatible versions of preferences data in different Archicad releases, use the @ref ACAPI_Preferences_SetOldVersion function to define preferences to be saved into the older project file formats.
 */
__APIEXPORT GSErrCode ACAPI_SetPreferences (Int32 version, GSSize nByte, const void *data);


/**
 * @brief Returns the stored preferences of the add-on.
 * @ingroup Preferences
 * @param version [out] On return contains the version of the stored preferences, or 0 if no preferences were found.
 * @param nByte [out] On return contains the size of the stored preferences in bytes, or 0 if no preferences were found.
 * @param data [in/out] On return contains the stored preferences. This parameter can be nullptr.
 * @return
 * 			- NoError - For common API errors see the API Errors document.
 * @remarks
 * 			-# You can retrieve the stored preferences of your add-on. This information was previously passed onto the add-on as a parameter of the DoCommand function.
 * 			-# Setting the last parameter to nullptr means the API will return only the version number and the size of the preferences data. If the size or the version number is 0, then no preferences were stored.
 * 			-# Version information can be used to convert older preferences to the current format.
 * 			In Archicad use @ref ACAPI_Preferences_Platform instead of @ref ACAPI_GetPreferences in order to get the platform identifier of the preferences data.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_GetPreferences-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GetPreferences (Int32 *version, GSSize *nByte, void *data);


/**
 * @brief Returns the stored preferences of the add-on.
 * @ingroup Preferences
 * @param version [out] On return contains the version of the stored preferences, or 0 if no preferences were found.
 * @param nByte [out] On return contains the size of the stored preferences in bytes, or 0 if no preferences were found.
 * @param data [in/out] On return contains the stored preferences.
 * @param platformSign [out] On return contains the platform identifier of the stored preferences.
 * @return
 * 			- NoError - For common API errors see the API Errors document.
 * @remarks Use this function to retrieve the preferences data stored into the preferences or the plan file currently opened. The preferences could have been saved into the plan on the other platform; in this case it is your responsibility to convert data structures stored in opposite byte order.
 * 			All the parameters can be nullptr.
 * 			The data pointer should be allocated and disposed by the add-on, thus first you should call this function to retrieve only the version number and the size of the preferences data.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Preferences_Platform-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Preferences_Platform (Int32			*version,
																	   GSSize			*nByte,
																	   void				*data,
																	   unsigned short	*platformSign);


/**
 * @brief Defines custom preferences data to be saved into older project file versions.
 * @ingroup Preferences
 * @param version [in] The version of the data to be stored.
 * @param nByte [in] The size of the data to be stored.
 * @param data [in] The preferences data you would like to store for the specified plan version.
 * @param platformSign [in] The platform identifier of the data (GS::Win_Platform_Sign, GS::Mac_Platform_Sign, GS::Mactel_Platform_Sign
 * @param oldPlanFileID [in] The plan file format associated with the preferences data when saving the project into this plan version. The value of this parameter can be:
 * @return
 * 			- NoError - For common API errors see the API Errors document.
 * @remarks This function is used to save your own options or preferences into the preferences file of the server application or into the project file to be saved. This information can be later retrieved with @ref ACAPI_GetPreferences and @ref ACAPI_Preferences_Platform.
 * 			You can define different preferences to be saved into different plan file formats. Use this function if your add-on had incompatible preferences format in the previous versions of Archicad. Store the data in that format too indicating which plan version should use it. When the user chooses to save the plan into an older plan format, the appropriate preferences data will be stored.
 * 			For more details see the Saving Add-On data into the Preferences and the Project File section.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Preferences_SetOldVersion-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Preferences_SetOldVersion (Int32				version,
																		 GSSize				nByte,
																		 const void*		data,
																		 unsigned short		platformSign,
																		 API_FTypeID		oldPlanFileID);


/**
 * @brief Registers a modeless palette in the API.
 * @ingroup AddOnIntegration
 * @param referenceID [in] Arbitrary number to uniquely identify your modeless palette. (You can use the resource ID if you wish.)
 * @param callBackProc [in] Callback procedure for handling special API messages. It is called by the API, independently of DG.
 * @param controlFlags [in] Define the behavior of the palette above different Archicad windows (plan, 3D, section, layout), and in case of selection.
 * @param paletteGuid [in] A unique identifier for recording the state of the palette in the Work Environment. Optional parameter, can be omitted.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The passed referenceID has already been used.
 * 			- APIERR_MEMFULL - No free memory was available for the new entry.
 * @remarks Modeless palettes now can be opened with the normal DG functions (either DGModelessInit, or DG::Palette). However, the API should know about the existence of an add-on's palette, so that it could send special messages to the palette (see APIPaletteControlCallBackProc). This function registers the add-on's modeless window with the API; call it from the Initialize function.
 * 			API 11 introduced new values for the controlFlags parameter: @c API_PalEnabled_Worksheet, @c API_PalEnabled_Elevation, and @c API_PalEnabled_InteriorElevation.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_RegisterModelessWindow-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_RegisterModelessWindow (Int32							referenceID,
																	  APIPaletteControlCallBackProc	*callBackProc,
																	  GSFlags						controlFlags,
																	  const API_Guid&				paletteGuid = APINULLGuid);


/**
 * @brief Ends the registration of an add-on's modeless palette with the API.
 * @ingroup Dialog
 * @param referenceID [in] The number to uniquely identify your modeless palette. Use the same ID that was supplied to @ref ACAPI_RegisterModelessWindow.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks When you close the modeless palette the registration should be ended with this function; call it in the FreeData function.
 */
__APIEXPORT GSErrCode ACAPI_UnregisterModelessWindow (Int32 referenceID);


/**
 * @brief Performs an undoable operation.
 * @ingroup Command
 * @param undoString [in] This string will appear after "Undo " in the Edit menu. Should be localizable. When left empty: "Paste" appears for merging and drag'n'drop operations the name of the command will be shown after "Undo " when the user chooses normal menu driven commands
 * @param command [in] The lambda function (C++11 function wrapper) that encapsulates the command to be called during the undoable operation.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_UNDOEMPTY - The current action is not undoable.
 * 			- APIERR_REFUSEDCMD - The current action is not undoable.
 * 			- APIERR_COMMANDFAILED - The current command threw an exception.
 * 			- APIERR_NOTMINE - Another add-on has already opened an undoable operation.
 * @remarks This function encapsulates a (series of) undoable steps (e.g. element creation). All the database modification operations check whether they are performed within an undoable command scope (a database transaction).
 * 			For some add-on types (e.g. I/O type add-ons) this function doesn't have to be called, as it doesn't make any sense to 'undo' opening a file.
 * 			Add-ons may not call this function from their element database event handler callback, because those notifications are sent from within an existing database transaction.
 * 			An add-on can perform more than one undoable command during one call. Just be aware that if the user completes an action in one step, it wouldn't be too convenient for her/him to restore the previous state (perform an "undo") in more than one step.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_CallUndoableCommand-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_CallUndoableCommand (const GS::UniString& undoString, const std::function<GSErrCode ()>& command);


/**
 * @brief Performs an operation without opening an undoable session.
 * @ingroup Command
 * @param commandName [in] Reserved for further use, this string won't appear anywhere.
 * @param command [in] The lambda function (C++11 function wrapper) that encapsulates all the operations.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_REFUSEDCMD - An operation has already opened, or the current command is undoable.
 * 			- APIERR_COMMANDFAILED - The current command threw an exception.
 * @remarks This function is used to execute more not-undoable data structure modifier functions in a single command.
 */
__APIEXPORT GSErrCode ACAPI_CallCommand (const GS::UniString& commandName, const std::function<GSErrCode ()>& command);


/**
 * @brief Returns the token associated with the AddOn.
 * @ingroup AddOnIdentification
 * @since Archicad 25
 * @return The token associated with the add-on.
 * @remarks It is not guaranteed that this function will always return the same value. Always obtain your token by calling this function on demand.
 */
__APIEXPORT API_Token ACAPI_GetToken (void);


/**
 * @brief Writes a report string into the Report Windowot into a custom alert window.
 * @ingroup Dialog
 * @param format A pointer to the message/format string.
 * @param withDial If `true` an alert window displaying the report string comes up, otherwise it writes to the Report window.
 * @param ... This a variadic argument which supplies the parameters to the `format` string
 */
__APIEXPORT void ACAPI_WriteReport (const GS::UniString& format, bool withDial, ...);


/**
 * @brief Returns a font either by index or name
 * @ingroup Font
 * @since Archicad 27
 * @param font [out] Reference of an API_FontType.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADINDEX - font with the given index does not exist.
 * 			- APIERR_BADNAME - font with the given name does not exist.
 */
__APIEXPORT GSErrCode	ACAPI_Font_GetFont		(API_FontType& font);


/**
 * @brief Search for a font by name
 * @ingroup Font
 * @since Archicad 27
 * @param font [in] The reference of the API_FontType on which the search is based.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADNAME - font with the given name does not exist.
 */
__APIEXPORT GSErrCode	ACAPI_Font_SearchFont	(API_FontType& font);


/**
 * @brief Get the number of fonts. You could use it to iterate over the fonts
 * @ingroup Font
 * @since Archicad 27
 * @return
 * 			- the number of fonts
 */
__APIEXPORT Int32		ACAPI_Font_GetFontNum	();


/**
 * @brief Modify a pen by index in the active pentable
 * @ingroup Attribute
 * @since Archicad 27
 * @param pen [in] Reference of the API_Pen on which the modification is based.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOACCESSRIGHT - no access right in teamwork
 * 			- APIERR_NOTMINE - pen tables not reserved in teamwork
 * 			- APIERR_General - general error
 * 			- APIERR_BADINDEX - bad pen index
 * 			- APIERR_NOCURRATTRSET - no current attributeset
 */
__APIEXPORT GSErrCode	ACAPI_Attribute_ModifyPen		(const API_Pen& pen);


/**
 * @brief Returns a pen by index from the active pentable
 * @ingroup Attribute
 * @since Archicad 27
 * @param pen [out] Reference of an API_Pen.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADINDEX - bad pen index
 * 			- APIERR_NOCURRATTRSET - no current attributeset
 */
__APIEXPORT GSErrCode	ACAPI_Attribute_GetPen		(API_Pen& pen);


/**
 * @brief Get the number of pens in the active pentable
 * @ingroup Attribute
 * @since Archicad 27
 * @param count [out] Reference of a UInt32.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOCURRATTRSET - no current attributeSet exists
 */
__APIEXPORT GSErrCode	ACAPI_Attribute_GetPenNum		(UInt32& count);


/**
 * @brief Retrieves a list of all override combinations in the current plan.
 * @ingroup GraphicalOverride
 * @param combinationList [out] The list of all override combinations in the current plan.
 * @return
 * 			- NoError - The function has completed with success.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_GraphicalOverride_GetOverrideCombinationList-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GraphicalOverride_GetOverrideCombinationList (GS::Array<API_Guid>& combinationList);


/**
 * @brief Retrieves a list of all override rule groups in the current plan.
 * @ingroup GraphicalOverride
 * @since Archicad 27
 * @param ruleGroupList [out] The list of all override rule groups in the current plan.
 * @return
 * 			- NoError - The function has completed with success.
 * @par Example from Override_Test / TestNormalUsage
 * 		@snippet Override_Test.cpp ACAPI_GraphicalOverride_GetOverrideRuleGroupList-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GraphicalOverride_GetOverrideRuleGroupList	(GS::Array<API_Guid>& ruleGroupList);


/**
 * @brief Retrieves a list of all override rules in the current plan.
 * @ingroup GraphicalOverride
 * @param ruleList [out] The list of all override rules in the current plan.
 * @return
 * 			- NoError - The function has completed with success.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_GraphicalOverride_GetOverrideRuleList-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GraphicalOverride_GetOverrideRuleList		  (GS::Array<API_Guid>& ruleList);


/**
 * @brief Retrieves an override combination identified by its guid or name.
 * @ingroup GraphicalOverride
 * @param combination [in/out] The guid field specifies the combination to retrieve. If the guid field is APINULLGuid, then the name field is used to find the combination. Once the operation is successfully completed, this will hold the retrieved combination.
 * @param ruleList [out] If not a nullptr, then the list of guids of the rules that the combination "contains".
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The guid or name did not refer to a valid override combination.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_GraphicalOverride_GetOverrideCombination-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GraphicalOverride_GetOverrideCombination	(API_OverrideCombination& combination,
																		 GS::Array<API_Guid>* ruleList = nullptr);


/**
 * @brief Retrieves an override rule group identified by its guid or name.
 * @ingroup GraphicalOverride
 * @since Archicad 27
 * @param ruleGroup [in/out] The guid field specifies the rule group to retrieve. If the guid field is APINULLGuid, then the name field is used to find the rule group. Once the operation is successfully completed, this will hold the retrieved rule group.
 * @param ruleList [out] If not a nullptr, then the list of guids of the rules that belong to the rule group.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The guid or name did not refer to a valid override rule group.
 * @par Example from Override_Test / TestNormalUsage
 * 		@snippet Override_Test.cpp ACAPI_GraphicalOverride_GetOverrideRuleGroup-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GraphicalOverride_GetOverrideRuleGroup	(API_OverrideRuleGroup& ruleGroup,
																	 GS::Array<API_Guid>* ruleList = nullptr);


/**
 * @brief Retrieves an override rule identified by its guid.
 * @ingroup GraphicalOverride
 * @since Archicad 27
 * @param rule [in/out] The guid field specifies the rule to retrieve. Once the operation is successfully completed, this will hold the retrieved rule.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The guid did not refer to a valid override rule.
 * @par Example from Override_Test / TestNormalUsage
 * 		@snippet Override_Test.cpp ACAPI_GraphicalOverride_GetOverrideRuleById-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GraphicalOverride_GetOverrideRuleById	(API_OverrideRule& rule);


/**
 * @brief Retrieves an override rule identified by its name.
 * @ingroup GraphicalOverride
 * @since Archicad 27
 * @param rule [in/out] The name field is used to find the rule within the group. Once the operation is successfully completed, this will hold the retrieved rule.
 * @param ruleGroup The guid of the override rule group that contains the rule.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The name did not refer to a valid override rule in that rule group.
 * @par Example from Override_Test / TestNormalUsage
 * 		@snippet Override_Test.cpp ACAPI_GraphicalOverride_GetOverrideRuleByName-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GraphicalOverride_GetOverrideRuleByName	  (API_OverrideRule& rule, const API_Guid& ruleGroup);



/**
 * @brief Creates an override combination.
 * @ingroup GraphicalOverride
 * @param combination [in/out] The combination to create. Once the operation is successfully completed, this will hold the valid guid of the created combination.
 * @param ruleList [in] The ids of the rules that the combination should "contain".
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The guid of a rule did not refer to a valid override rule.
 * 			- APIERR_BADNAME - The specified name for the combination is invalid (empty, or whitespace only, or contains more than 255 characters)
 * 			- APIERR_NAMEALREADYUSED - The specified name for the combination is already taken in the current project.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_GraphicalOverride_CreateOverrideCombination-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GraphicalOverride_CreateOverrideCombination		(API_OverrideCombination& combination,
																			 const GS::Array<API_Guid>& ruleList);


/**
 * @brief Creates an override rule group.
 * @ingroup GraphicalOverride
 * @since Archicad 27
 * @param ruleGroup [in/out] The rule group to create. Once the operation is successfully completed, this will hold the valid guid of the created rule group.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADNAME - The specified name for the rule group is invalid (empty, or whitespace only, or contains more than 255 characters)
 * 			- APIERR_NAMEALREADYUSED - The specified name for the rule group is already taken in the current project.
 * @par Example from Override_Test / TestNormalUsage
 * 		@snippet Override_Test.cpp ACAPI_GraphicalOverride_CreateOverrideRuleGroup-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GraphicalOverride_CreateOverrideRuleGroup		(API_OverrideRuleGroup& ruleGroup);


/**
 * @brief Creates an override rule.
 * @ingroup GraphicalOverride
 * @param rule [in/out] The rule to create. Once the operation is successfully completed, this will hold the valid guid of the created rule.
 * @param ruleGroup [in] The rule group the rule should belong to.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The guid or name did not refer to a valid override rule group.
 * 			- APIERR_BADNAME - The specified name for the rule is invalid (empty, or whitespace only, or contains more than 255 characters)
 * 			- APIERR_NAMEALREADYUSED - The specified name for the rule is already taken in the current project.
 * @par Example from Override_Test / TestNormalUsage
 * 		@snippet Override_Test.cpp ACAPI_GraphicalOverride_CreateOverrideRule-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GraphicalOverride_CreateOverrideRule		(API_OverrideRule& rule, const API_Guid& ruleGroup);



/**
 * @brief Changes an override combination identified by its guid.
 * @ingroup GraphicalOverride
 * @param combination [in] The combination to change.
 * @param ruleList [in] The ids of the rules that the combination should "contain", or nullptr if they shouldn't be changed.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The guid did not refer to a valid override combination or an element of the ruleList array did not refer to a valid override rule.
 * 			- APIERR_BADNAME - The specified new name for the combination is invalid (empty, or whitespace only, or contains more than 255 characters)
 * 			- APIERR_NAMEALREADYUSED - The specified new name for the combination is already taken in the current project.
 * 			- APIERR_NOACCESSRIGHT - Tried to change a built-in combination.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_GraphicalOverride_ChangeOverrideCombination-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GraphicalOverride_ChangeOverrideCombination		(const API_OverrideCombination& combination,
																			 const GS::Array<API_Guid>* const ruleList = nullptr);



/**
 * @brief Changes an override rule group identified by its guid.
 * @ingroup GraphicalOverride
 * @since Archicad 27
 * @param ruleGroup [in] The rule group to change.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The guid did not refer to a valid override rule group or an element of the ruleList array did not refer to a valid override rule.
 * 			- APIERR_BADNAME - The specified new name for the rule group is invalid (empty, or whitespace only, or contains more than 255 characters)
 * 			- APIERR_NAMEALREADYUSED - The specified new name for the rule group is already taken in the current project.
 * 			- APIERR_NOACCESSRIGHT - Tried to change a built-in rule group.
 * @par Example from Override_Test / TestNormalUsage
 * 		@snippet Override_Test.cpp ACAPI_GraphicalOverride_ChangeOverrideRuleGroup-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GraphicalOverride_ChangeOverrideRuleGroup	(const API_OverrideRuleGroup& ruleGroup);


/**
 * @brief Changes an override rule identified by its guid.
 * @ingroup GraphicalOverride
 * @param rule [in] The rule to change.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The guid did not refer to a valid override rule.
 * 			- APIERR_BADNAME - The specified new name for the rule is invalid (empty, or whitespace only, or contains more than 255 characters)
 * 			- APIERR_NAMEALREADYUSED - The specified new name for the rule is already taken in the current project.
 * 			- APIERR_NOACCESSRIGHT - Tried to change a built-in rule.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_GraphicalOverride_ChangeOverrideRule-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GraphicalOverride_ChangeOverrideRule		(const API_OverrideRule& rule);


/**
 * @brief Moves an override rule between override rule groups.
 * @ingroup GraphicalOverride
 * @param rule [in] The id of the rule to move.
 * @param targetRuleGroup [in] The id of the rule group the rule should belong to after the move.
 * @param nextRule [in] The id of the rule this rule should be right before in the target group. If this is nullptr then the rule will be the last in the target group.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - A guid did not refer to a valid override rule or override rule group, or the referred next rule was not in the target group.
 * 			- APIERR_NAMEALREADYUSED - The specified new name for the rule is already taken in the target group in the current project.
 * 			- APIERR_NOACCESSRIGHT - Insufficient teamwork permission or tried to move a built-in rule
 * @par Example from Override_Test / TestNormalUsage
 * 		@snippet Override_Test.cpp ACAPI_GraphicalOverride_MoveOverrideRule-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GraphicalOverride_MoveOverrideRule	(const API_Guid& rule, const API_Guid& targetRuleGroup, const API_Guid* nextRule);


/**
 * @brief Deletes an override combination identified by its guid.
 * @ingroup GraphicalOverride
 * @param combination [in] The guid of the combination to delete.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The guid did not refer to a valid override combination.
 * 			- APIERR_NOACCESSRIGHT - Tried to delete a built-in combination.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_GraphicalOverride_DeleteOverrideCombination-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GraphicalOverride_DeleteOverrideCombination  (const API_Guid& combination);


/**
 * @brief Deletes an override rule group identified by its guid and deletes all the override rules it contains.
 * @ingroup GraphicalOverride
 * @since Archicad 27
 * @param ruleGroup [in] The guid of the rule group to delete.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The guid did not refer to a valid override rule group.
 * 			- APIERR_NOACCESSRIGHT - Tried to delete a built-in rule group.
 * @par Example from Override_Test / TestNormalUsage
 * 		@snippet Override_Test.cpp ACAPI_GraphicalOverride_DeleteOverrideRuleGroup-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GraphicalOverride_DeleteOverrideRuleGroup  (const API_Guid& ruleGroup);


/**
 * @brief Deletes an override rule identified by its guid.
 * @ingroup GraphicalOverride
 * @param rule [in] The guid of the rule to delete.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The guid did not refer to a valid override rule.
 * 			- APIERR_NOACCESSRIGHT - Tried to delete a built-in rule.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_GraphicalOverride_DeleteOverrideRule-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GraphicalOverride_DeleteOverrideRule	(const API_Guid& rule);


/**
 * @brief Sets the order of rule groups in the current project.
 * @ingroup GraphicalOverride
 * @since Archicad 27
 * @param orderedRuleGroupIds [in] The ids of all the user-defined rule groups in the expected order.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - A guid did not refer to a valid override rule group, or the array didn't contain all the user-defined rule groups.
 * 			- APIERR_NOACCESSRIGHT - Insufficient teamwork permission or tried to move a built-in rule
 * @par Example from Override_Test / TestNormalUsage
 * 		@snippet Override_Test.cpp ACAPI_GraphicalOverride_SetOverrideRuleGroupOrder-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GraphicalOverride_SetOverrideRuleGroupOrder	(const GS::Array<API_Guid>& orderedRuleGroupIds);


/**
 * @brief Sets the order of rules in the specified override rule group.
 * @ingroup GraphicalOverride
 * @since Archicad 27
 * @param ruleGroup [in] The guid of the rule group all the rules belong to.
 * @param orderedRuleIds [in] The ids of all the rules in the expected order.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - A guid did not refer to a valid override rule, or the array didn't contain all the rules in the override rule group.
 * 			- APIERR_NOACCESSRIGHT - Insufficient teamwork permission or tried to reorder rules in a built-in group.
 * @par Example from Override_Test / TestNormalUsage
 * 		@snippet Override_Test.cpp ACAPI_GraphicalOverride_SetOverrideRuleOrder-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GraphicalOverride_SetOverrideRuleOrder	(const API_Guid& ruleGroup, const GS::Array<API_Guid>& orderedRuleIds);


/**
 * @brief Returns the number of instances of a given type of attribute.
 * @ingroup Attribute
 * @param typeID [in] Type of the attribute.
 * @param count [out] The number of attributes in the database for the given attribute type.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter is nullptr; count
 * 			- APIERR_BADID - The attribute type is invalid
 * @remarks This function returns the actual number of the given attribute type. You should use @c ACAPI_Attribute_GetAttributesByType or @c ACAPI_Attribute_EnumerateAttributesByType to iterate on attributes!.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Attribute_GetNum-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Attribute_GetNum (API_AttrTypeID typeID, UInt32& count);


/**
 * @brief Retrieves an attribute from the database.
 * @ingroup Attribute
 * @since Archicad 27
 * @param attribute [in/out] Parameters of the attribute. The type and the index or the name of the attribute must be passed in the typeID and index, or in the typeID and name fields in the attribute header. The data of the attribute is returned in the appropriate fields of the @ref API_Attribute structure.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter (attribute) is nullptr
 * 			- APIERR_BADID - The attribute type is invalid
 * 			- APIERR_BADINDEX - The attribute index is invalid; if referenced by index
 * 			- APIERR_BADNAME - The attribute with the given name doesn't exist; if referenced by name
 * @remarks This function is used to retrieve one attribute's data from the database. Beside the typeID, you should specify either the index or the name field of the header. In the latter case, the index field should be set to zero, and the attribute database is searched by name.
 * 			You may optionally call @ref ACAPI_Attribute_GetDef to get extended information for certain attribute types.
 * 			The index range is not always continuous; deleted attributes are not purged immediately from the database.
 * 			Note: The received attributes can have dynamically allocated members depending on the typeID. They should be disposed when they are no more needed.
 * 			- @c API_MaterialID : attribute.material.texture.fileLoc
 * 			- @c API_ModelViewOptionsID : attribute.modelViewOpt.modelViewOpt.gdlOptions
 * 			Note: Special pen IDs can be used:
 * 			- 1000 : returns the color of the grid line
 * 			- 1001 : returns the color of the zone stamp
 * 			- 1002 : returns the color of the ghost story
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Attribute_Get-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Attribute_Get (API_Attribute *attribute);


/**
 * @brief Returns the instances of a given attribute type in the database.
 * @ingroup Attribute
 * @since Archicad 27
 * @param typeID [in] Type of the attribute.
 * @param attributes [out] The attributes in the database for the given attribute type.
 * @return
 */
__APIEXPORT GSErrCode ACAPI_Attribute_GetAttributesByType (API_AttrTypeID typeID, GS::Array<API_Attribute>& attributes);


/**
 * @brief Iterates the instances of a given attribute type in the database.
 * @ingroup Attribute
 * @since October 18, 2022
 * @param typeID [in] Type of the attribute.
 * @param processor [in] The enumerator process on the API_Attribute  as a lambda function.
 * @return
 */
__APIEXPORT GSErrCode ACAPI_Attribute_EnumerateAttributesByType (API_AttrTypeID typeID, const std::function<void (API_Attribute&)>& processor);


/**
 * @brief Retrieves extended information for an attribute.
 * @ingroup Attribute
 * @since Archicad 27
 * @param typeID [in] Type of the attribute.
 * @param index [in] Index of the attribute.
 * @param defs [out] The extended information for an attribute.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter (defs) is nullptr
 * 			- APIERR_BADID - The attribute type is invalid; see Remarks
 * 			- APIERR_BADINDEX - The attribute index is invalid
 * @remarks This function is used to return detailed information on the specified attribute.
 * 			This function is available only for lines, fills, composites, layers, and zone categories. Other type of attributes do not have extended information; all of the their data can be passed through the @ref API_Attribute structure. See the @ref ACAPI_Attribute_Get function to get the base parameters of an attribute.
 * 			Do not forget to dispose the returned data handles if they are not needed any more. Use the @ref ACAPI_DisposeAttrDefsHdls function for this purpose.
 * 			This function is available only for lines, fills, composites, layers, and zone categories. Other type of attributes do not have extended information; all of the their data can be passed through the @ref API_Attribute structure. See the @ref ACAPI_Attribute_Get function to get the base parameters of an attribute.
 * 			Do not forget to dispose the returned data handles if they are not needed any more. Use the @ref ACAPI_DisposeAttrDefsHdlsExt function for this purpose.
 * 			Use this function instead of @ref ACAPI_Attribute_GetDef function because @ref API_AttributeDefExt structure contains more fields - detailed information for composite wall attribute - than @ref API_AttributeDef.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Attribute_GetDef-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Attribute_GetDef (API_AttrTypeID typeID, API_AttributeIndex index, API_AttributeDef *defs);


/**
 * @brief Retrieves extended information for an attribute.
 * @ingroup Attribute
 * @since Archicad 27
 * @param typeID [in] Type of the attribute.
 * @param index [in] Index of the attribute.
 * @param defs [out] The extended information for an attribute.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter (defs) is nullptr
 * 			- APIERR_BADID - The attribute type is invalid; see Remarks
 * 			- APIERR_BADINDEX - The attribute index is invalid
 * @remarks This function is used to return detailed information on the specified attribute.
 * 			This function is available only for lines, fills, composites, layers, and zone categories. Other type of attributes do not have extended information; all of the their data can be passed through the @ref API_Attribute structure. See the @ref ACAPI_Attribute_Get function to get the base parameters of an attribute.
 * 			Do not forget to dispose the returned data handles if they are not needed any more. Use the @ref ACAPI_DisposeAttrDefsHdls function for this purpose.
 * 			This function is available only for lines, fills, composites, layers, and zone categories. Other type of attributes do not have extended information; all of the their data can be passed through the @ref API_Attribute structure. See the @ref ACAPI_Attribute_Get function to get the base parameters of an attribute.
 * 			Do not forget to dispose the returned data handles if they are not needed any more. Use the @ref ACAPI_DisposeAttrDefsHdlsExt function for this purpose.
 * 			Use this function instead of @ref ACAPI_Attribute_GetDef function because @ref API_AttributeDefExt structure contains more fields - detailed information for composite wall attribute - than @ref API_AttributeDef.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Attribute_GetDefExt-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Attribute_GetDefExt (API_AttrTypeID		typeID,
																   API_AttributeIndex	index,
																   API_AttributeDefExt	*defs);


/**
 * @brief Creates an attribute.
 * @ingroup Attribute
 * @since Archicad 26
 * @param attribute [in/out] Parameters of the attribute. The type of the attribute must be passed in the typeID field in the attribute header. The index field of the attribute header is used as an output parameter to return the reference index to the newly created attribute.
 * @param defs [in] Additional parameters of the attribute. It is required or optional to pass depending on the type of the attribute.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_ATTREXIST - An attribute with the same name already exists.
 * 			- APIERR_BADID - Invalid attribute type was passed, or a pen or font attribute type was given.
 * 			- APIERR_BADPARS - A nullptr attribute pointer was passed.
 * 			- APIERR_NOTMINE - You are in view-only mode for a teamwork project.
 * @remarks This function is used to create an attribute, defined by the typeID field of the attribute header. The reference index of the newly created attribute is returned in the index field of the attribute header.
 * 			You cannot create pen and font attributes.
 * 			The function also checks the data for possible inconsistency. If a problem is encountered it may be corrected automatically, or an error code is generated.
 * 			If an attribute with the same name exists in the database, the existing index will be returned. The matching procedure ignores the differences of the attribute definition. Multiple attributes with the same name are not allowed.
 * 			When creating the attribute, the applicable fields should be filled.
 * @ref API_Attr_Head typeID required index ignored flags required where applicable name required @c API_AttributeTypeID defs @c API_LayerID - @c API_LinetypeID ltype_dashItems (for dashed line type) ltype_lineItems(for symbol line type) @c API_FilltypeID fill_lineItems (for vector fill type) fill_lineLength (for vector fill type) sfill_Items (for symbol fill type) @c API_CompWallID cwall_compItems @c API_MaterialID - @c API_LayerCombID layer_statItems @c API_ZoneCatID zone_addParItems @c API_MEPSystemID -
 * 		It is important that Archicad does not free any dynamic data structure you have allocated and passed to Archicad. It is your responsibility to dispose the handles passed in the defs parameter, when they are no longer needed. It is advised to use the @ref ACAPI_DisposeAttrDefsHdls function for compatibility reasons.
 * 		This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * 		You cannot create pen and font attributes.
 * 		The function also checks the data for possible inconsistency. If a problem is encountered it may be corrected automatically, or an error code is generated.
 * 		If an attribute with the same name exists in the database, the existing index will be returned. The matching procedure ignores the differences of the attribute definition. Multiple attributes with the same name are not allowed.
 * 		When creating the attribute, the applicable fields should be filled.
 * 		Use this function instead of @ref ACAPI_Attribute_Create function because @ref API_AttributeDefExt structure contains more fields - detailed information for composite wall attribute - than @ref API_AttributeDef.
 * 		|@ref API_Attr_Head||
 * 		|--- |--- |
 * 		|typeID|required|
 * 		|index|ignored|
 * 		|flags|required where applicable|
 * 		|name|required|
 *
 * 		|`API_AttributeTypeID`|defs|
 * 		|--- |--- |
 * 		|`API_LayerID`|-|
 * 		|`API_LinetypeID`|ltype_dashItems (for dashed line type)<br>ltype_lineItems(for symbol line type)|
 * 		|`API_FilltypeID`|fill_lineItems (for vector fill type)<br>fill_lineLength (for vector fill type)<br>sfill_Items (for symbol fill type)|
 * 		|`API_CompWallID`|cwall_compItems|
 * 		|`API_MaterialID`|-|
 * 		|`API_LayerCombID`|layer_statItems|
 * 		|`API_ZoneCatID`|zone_addParItems|
 * 		|`API_MEPSystemID`|-|
 *
 * 		It is important that Archicad does not free any dynamic data structure you have allocated and passed to Archicad. It is your responsibility to dispose of the handles passed in the defs parameter, when they are no longer needed. It is advised to use the @ref ACAPI_DisposeAttrDefsHdlsExt function for compatibility reasons.
 * 		This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Attribute_Create-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Attribute_Create (API_Attribute *attribute, API_AttributeDef *defs);


/**
 * @brief Creates an attribute.
 * @ingroup Attribute
 * @since Archicad 26
 * @param attribute [in/out] Parameters of the attribute. The type of the attribute must be passed in the typeID field in the attribute header. The index field of the attribute header is used as an output parameter to return the reference index to the newly created attribute.
 * @param defs [in] Additional parameters of the attribute. It is required or optional to pass depending on the type of the attribute.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_ATTREXIST - An attribute with the same name already exists.
 * 			- APIERR_BADID - Invalid attribute type was passed, or a pen or font attribute type was given.
 * 			- APIERR_BADPARS - A nullptr attribute pointer was passed.
 * 			- APIERR_NOTMINE - You are in view-only mode for a teamwork project.
 * @remarks This function is used to create an attribute, defined by the typeID field of the attribute header. The reference index of the newly created attribute is returned in the index field of the attribute header.
 * 			You cannot create pen and font attributes.
 * 			The function also checks the data for possible inconsistency. If a problem is encountered it may be corrected automatically, or an error code is generated.
 * 			If an attribute with the same name exists in the database, the existing index will be returned. The matching procedure ignores the differences of the attribute definition. Multiple attributes with the same name are not allowed.
 * 			When creating the attribute, the applicable fields should be filled.
 * @ref API_Attr_Head typeID required index ignored flags required where applicable name required @c API_AttributeTypeID defs @c API_LayerID - @c API_LinetypeID ltype_dashItems (for dashed line type) ltype_lineItems(for symbol line type) @c API_FilltypeID fill_lineItems (for vector fill type) fill_lineLength (for vector fill type) sfill_Items (for symbol fill type) @c API_CompWallID cwall_compItems @c API_MaterialID - @c API_LayerCombID layer_statItems @c API_ZoneCatID zone_addParItems @c API_MEPSystemID -
 * 		It is important that Archicad does not free any dynamic data structure you have allocated and passed to Archicad. It is your responsibility to dispose the handles passed in the defs parameter, when they are no longer needed. It is advised to use the @ref ACAPI_DisposeAttrDefsHdls function for compatibility reasons.
 * 		This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * 		You cannot create pen and font attributes.
 * 		The function also checks the data for possible inconsistency. If a problem is encountered it may be corrected automatically, or an error code is generated.
 * 		If an attribute with the same name exists in the database, the existing index will be returned. The matching procedure ignores the differences of the attribute definition. Multiple attributes with the same name are not allowed.
 * 		When creating the attribute, the applicable fields should be filled.
 * 		Use this function instead of @ref ACAPI_Attribute_Create function because @ref API_AttributeDefExt structure contains more fields - detailed information for composite wall attribute - than @ref API_AttributeDef.<br>
 * 		|`API_Attr_Head`||
 * 		|--- |--- |
 * 		|typeID|required|
 * 		|index|ignored|
 * 		|flags|required where applicable|
 * 		|name|required|
 *
 * 		|API_AttributeTypeID|defs|
 * 		|--- |--- |
 * 		|API_LayerID|-|
 * 		|API_LinetypeID|ltype_dashItems (for dashed line type)<br>ltype_lineItems(for symbol line type)|
 * 		|API_FilltypeID|fill_lineItems (for vector fill type)<br>fill_lineLength (for vector fill type)<br>sfill_Items (for symbol fill type)|
 * 		|API_CompWallID|cwall_compItems<br>cwall_compLItems|
 * 		|API_MaterialID|-|
 * 		|API_LayerCombID|layer_statItems|
 * 		|API_ZoneCatID|zone_addParItems|
 * 		|API_MEPSystemID|-|
 *
 * 		It is important that Archicad does not free any dynamic data structure you have allocated and passed to Archicad. It is your responsibility to dispose the handles passed in the defs parameter, when they are no longer needed. It is advised to use the @ref ACAPI_DisposeAttrDefsHdlsExt function for compatibility reasons.
 * 		This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Attribute_CreateExt-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Attribute_CreateExt (API_Attribute *attribute, API_AttributeDefExt *defs);


/**
 * @brief Modifies an attribute.
 * @ingroup Attribute
 * @since Archicad 27
 * @param attribute [in] The attribute to be modified is defined by the typeID and index fields of the header.
 * @param defs [in] The extended information for the attribute where needed.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter is nullptr; attribute, [defs]
 * 			- APIERR_BADID - The attribute type is invalid
 * 			- APIERR_BADINDEX - The attribute index is invalid
 * 			- APIERR_REFUSEDPAR - For layers, fills and line types you cannot modify the attribute with index 1. Solid and empty fills are also unalterable.
 * @remarks This function is used to modify an attribute. The attribute to be modified is identified by the typeID and the index fields in the attribute header.
 * 			You can either modify the parameters passed through the @ref API_Attribute structure or the extended information given in @ref API_AttributeDef.
 * 			The attribute will be named according to @c uniStringNamePtr in @ref API_Attribute, or @c name if the first was nullptr.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * 			You can either modify the parameters passed through the @ref API_Attribute structure or the extended information given in @ref API_AttributeDefExt.
 * 			Use this function instead of @ref ACAPI_Attribute_Modify function because @ref API_AttributeDefExt structure contains more fields - detailed information for composite wall attribute - than @ref API_AttributeDef.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Attribute_Modify-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Attribute_Modify (API_Attribute *attribute, API_AttributeDef *defs);


/**
 * @brief Modifies an attribute.
 * @ingroup Attribute
 * @since Archicad 27
 * @param attribute [in] The attribute to be modified is defined by the typeID and index fields of the header.
 * @param defs [in] The extended information for the attribute where needed.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter is nullptr; attribute, [defs]
 * 			- APIERR_BADID - The attribute type is invalid
 * 			- APIERR_BADINDEX - The attribute index is invalid
 * 			- APIERR_REFUSEDPAR - For layers, fills and line types you cannot modify the attribute with index 1. Solid and empty fills are also unalterable.
 * @remarks This function is used to modify an attribute. The attribute to be modified is identified by the typeID and the index fields in the attribute header.
 * 			You can either modify the parameters passed through the @ref API_Attribute structure or the extended information given in @ref API_AttributeDef.
 * 			The attribute will be named according to @c uniStringNamePtr in @ref API_Attribute, or @c name if the first was nullptr.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * 			You can either modify the parameters passed through the @ref API_Attribute structure or the extended information given in @ref API_AttributeDefExt.
 * 			Use this function instead of @ref ACAPI_Attribute_Modify function because @ref API_AttributeDefExt structure contains more fields - detailed information for composite wall attribute - than @ref API_AttributeDef.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Attribute_ModifyExt-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Attribute_ModifyExt (API_Attribute *attribute, API_AttributeDefExt *defs);


/**
 * @brief Searches for an attribute by name.
 * @ingroup Attribute
 * @param attrHead [in/out] The attribute to search for, identified by the typeID and name or the guid fields of the header.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter is nullptr; attrHead
 * 			- APIERR_BADID - The attribute type is invalid
 * 			- APIERR_BADGUID - The attribute with the given guid doesn't exist
 * 			- APIERR_BADNAME - The attribute with the given name doesn't exist
 * @remarks This function is used to search for an attribute by name or by GUID. Upon return, the index and other applicable fields of the header are set.
 * 			The primary search criteria is the GUID, then the Unicode name (if present), then the name field of the header.
 * 			This function cannot be used to search for pens; they don't have any name or GUID.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Attribute_Search-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Attribute_Search (API_Attr_Head *attrHead);


/**
 * @brief Deletes an attribute.
 * @ingroup Attribute
 * @since Archicad 26
 * @param attrHead [in] The typeID and index fields in the header identifies the attribute to delete.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter (attrHead) is invalid.
 * 			- APIERR_REFUSEDPAR - You tried to delete pens, fonts, a solid or an empty fill, or an attribute with index 1.
 * 			- APIERR_NOTMINE - The attribute is out of the users workspace.
 * @remarks This function is used to delete an attribute, defined by the typeID and index field of the attribute header. Certain attributes in the database can not be deleted; see the return values.
 * 			Note, that deleting an attribute do not effect any changes in the element database; they will refer to an attribute which is missing. That is not a problem, the server applications work in the same way when an attribute is deleted from the menus. The only exception is the layer attribute. Once a layer is deleted all the elements will be deleted; no matter in which database they are. The floor plan and all the section/elevations will be scanned to delete the elements which are on the given layer.
 * 			You can delete more than one attribute of the same type with the @ref ACAPI_Attribute_DeleteMore function.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Attribute_Delete-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Attribute_Delete (const API_Attr_Head& attrHead);


/**
 * @brief Deletes more attributes of the same type.
 * @ingroup Attribute
 * @since Archicad 26
 * @param attrTypeID [in] Identifies the type of the attributes to delete.
 * @param attrIndexList [in] List of attribute indices to be deleted.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter attrTypeID is invalid or the given attrIndexList is empty.
 * 			- APIERR_REFUSEDPAR - You tried to delete pens, fonts, a solid or an empty fill, or an attribute with index 1.
 * 			- APIERR_NOTMINE - The attribute is out of the users workspace.
 * @remarks This function is the extension of @ref ACAPI_Attribute_Delete. You can specify a list of attribute indices to be deleted. If you pass only one index in the attrIndexList parameter, this function works like @ref ACAPI_Attribute_Delete.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Attribute_DeleteMore-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Attribute_DeleteMore (API_AttrTypeID attrTypeID, const GS::Array<API_AttributeIndex>& attrIndexList);


/**
 * @brief Obtains the user data attached to an attribute.
 * @ingroup UserData
 * @ingroup Attribute
 * @since Archicad 27
 * @param attrHead [in] Header of the attribute (only fields typeID and index are used).
 * @param userData [in/out] Pointer to the user data.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Any of the passed parameters is nullptr
 * 			- APIERR_BADPLATFORMSIGN - The user data contained platform sign is invalid (out of range)
 * 			- APIERR_MEMFULL - Out of memory
 * 			- APIERR_NOUSERDATA - No user data attached by the caller module
 * @remarks This function is used to get the user attached data from an atribute. The typeID and index fields of the DDD record has to be filled to get the data attached to the attribute.
 * 			The caller should not allocate the userData->dataHdl field. It's allocated by the function itself but should be destroyed after use by the caller!
 * 			Use the @ref ACAPI_UserData_SetUserData functions to push data into the attribute record.
 */
__APIEXPORT GSErrCode ACAPI_UserData_GetUserData (API_Attr_Head			*attrHead,
																	 API_AttributeUserData	*userData);


/**
 * @brief Attaches user data to an attribute, or deletes the attached data.
 * @ingroup UserData
 * @ingroup Attribute
 * @param attrHead [in] The attribute to attach the user data to is defined by the typeID and index fields of the header.
 * @param userData [in] The user data to store. If dataHdl is nullptr, then the function deletes the user data.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - A nullptr attrHead or userData pointer was passed.
 * 			- APIERR_BADPLATFORMSIGN - The platform sign in the user data is invalid (out of range).
 * @remarks This function is used to attach user data to an an atribute, or to delete the attached information (if userData->dataHdl is nullptr. The caller is responsible for allocating and deleting the userData->dataHdl. You can safely destroy the passed handle after use, as it is copied into the internal database.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_UserData_SetUserData (API_Attr_Head					*attrHead,
																	 const API_AttributeUserData	*userData);

/**
 * @brief Loads the given attributes from a project file.
 * @ingroup Attribute
 * @param location [in] The location of the project to load the attributes from.
 * @param typeID [in] The attribute type to load from the project.
 * @param resultArray [out] The list of attributes that has been loaded successfully.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks Be aware that certain attribute types (e.g., composite walls) refer to other attribute types as well.
 */
__APIEXPORT GSErrCode ACAPI_Attribute_GetAttributesFromProject (const IO::Location&										location,
																				  API_AttrTypeID											typeID,
																				  GS::Array<GS::Pair<API_Attribute, API_AttributeDefExt>>*	resultArray);


/**
 * @brief Returns an attribute reader for the currently used attribute set.
 * @ingroup Attribute
 * @since Archicad 25
 * @return
 * @remarks Use this function when an attribute reader is required as a parameter of other functions. For example when retrieving the 3D model by using the EXPGetModel function.
 * 			The returned attribute reader is allocated on the heap. Don't forget to delete it when it's not needed anymore!
 */
__APIEXPORT Modeler::IAttributeReader* ACAPI_Attribute_GetCurrentAttributeSetReader ();


/**
 * @brief Retrieves an existing attribute folder by it's path or guid.
 * @ingroup Attribute
 * @since Archicad 26
 * @param folder [in out] Set the typeID and the path or guid of the attribute folder to retrieve.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - Incorrect folder.typeID was specified, or folder.path is illegal, see remarks.
 * 			- APIERR_NOPLAN - There is no open project.
 * @remarks folder.path has to be legal, i.e. all names in the array must not be empty, and must not begin or end with whitespace.
 * 			Besides folder.typeID, either folder.guid or folder.path is to be passed. If none of the latter is provided, the root folder is accessed.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Attribute_GetFolder-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Attribute_GetFolder	(API_AttributeFolder& folder);


/**
 * @brief Creates attribute folders. To create a folder, its full path has to be provided. The command will create all folders along the path, if they do not exist.
 * @ingroup Attribute
 * @since Archicad 26
 * @param folder [in out] Type and path of the attribute folder to create.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - Incorrect folder.typeID was specified, or folder.path is illegal, see remarks.
 * 			- APIERR_NOPLAN - There is no open project.
 * 			- APIERR_NOACCESSRIGHT - User has no permission to create folders under typeID.
 * 			- APIERR_BADPARS - Folder creation is not available for folder.typeID.
 * @remarks older.path has to be legal, i.e. all names in the array must not be empty, and must not begin or end with whitespace.
 * 			If a folder in folder.path already exists, it is not renamed or recreated. Name collision of folders is case insensitive. Examples:
 * 			- If the folders A/B exist, and folder.path = a/b/c/d, two new folders, c/d under A/B are created. A and B are not renamed to a and b.
 * 			- If the folders A/B/C exist, and folder.path = a/b/c, this has no effect. NoError will be returned.
 * 			If a folder at folder.path was successfully created, it's unique identifier is set to folder.guid. It can be used later, even if the folder was moved or renamed since it's creation.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Attribute_CreateFolder-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Attribute_CreateFolder (API_AttributeFolder& folder);


/**
 * @brief Moves attributes and attribute folders.
 * @ingroup Attribute
 * @since Archicad 26
 * @param foldersToMove [in] List of folders to move.
 * @param attributesToMove [in] List of attributes to move.
 * @param targetFolder [in] Target folder, i.e. the new parent of the folders and attributes to move.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - Incorrect typeID was specified.
 * @remarks All folders (items of foldersToMove and targetFolder) have to be existing folders.
 * 			Handling name collisions:
 * 			- If there are name collisions, the moved folders will be merged with the colliding folders in targetFolder, like in a filesystem.
 * 			- Name collision of folders is case insensitive. An existing folder in targetFolder will not be renamed. E.g. merging 'foo' into an existing 'Foo' keeps the 'Foo' name.
 * 			- Name collision between two moved folders will be handled in order of appearance in foldersToMove. E.g. moving 'A/foo' and 'B/Foo' (in this order) to 'Bar' will result in 'Bar/foo', because 'foo' is first created in 'Bar', and then it is not renamed to 'Foo'.
 * 			foldersToMove and attributesToMove can contain repeated items. Repeated items will be handled as if only the first occurrence would be present in the list.
 * 			foldersToMove and attributesToMove can contain items which are already under targetFolder. Such items will be left in place.
 * 			foldersToMove and attributesToMove can contain items which are under a folder to move. Such items will be ignored, as if they would not be on the list, and only the outermost folder will be moved.
 * 			A folder or attribute cannot be moved out of its attribute type.
 */
__APIEXPORT GSErrCode ACAPI_Attribute_Move (const GS::Array<API_AttributeFolder>&	foldersToMove,
															  const GS::Array<GS::Guid>&			attributesToMove,
															  const API_AttributeFolder&			targetFolder);


/**
 * @brief Returns all folders and attributes of an attribute type.
 * @ingroup Attribute
 * @since Archicad 26
 * @param folder [in] Identifier of the folder to query.
 * @param result [out] Content of te queried folder.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - Incorrect folder was specified.
 * 			- APIERR_NOPLAN - There is no open project.
 */
__APIEXPORT GSErrCode ACAPI_Attribute_GetFolderContent	(const API_AttributeFolder& folder,
																			API_AttributeFolderContent& result);


/**
 * @brief Deletes an attribute folder and all the folders and attributes it contains.
 * @ingroup Attribute
 * @since Archicad 26
 * @param folder [in] The folder to delete.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Incorrect folder was specified.
 * 			- APIERR_NOPLAN - There is no open project.
 * 			- APIERR_NOACCESSRIGHT - User has no permission to delete folders under folder.typeID.
 * 			- APIERR_NOTMINE - Attribute type folder.typeID is not reserved.
 * @remarks Folder has to be an existing folder identified by it's typeID, and path or guid..
 * 			Deletes all deletable attributes and folders the given folder contains. If an attribute is not deletable, the folders containing the attribute are not deleted.
 * 			newName has to be legal, must not be empty, and must not begin or end with whitespace.
 * 			Renames the specified folder (while preserving it's guid). The root folder can't be renamed, two folders in the same parent folder can't have the same name.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Attribute_DeleteFolder-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Attribute_DeleteFolder (const API_AttributeFolder& folder);


/**
 * @brief Deletes an attribute folder and all the folders and attributes it contains.
 * @ingroup Attribute
 * @since Archicad 26
 * @param folder [in] The folder to rename.
 * @param newName [in] The new name for the folder.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Incorrect folder was specified.
 * 			- APIERR_NOPLAN - There is no open project.
 * 			- APIERR_NOACCESSRIGHT - User has no permission to rename folders under folder.typeID.
 * 			- APIERR_NOTMINE - Attribute type folder.typeID is not reserved.
 * @remarks Folder has to be an existing folder identified by it's typeID, and path or guid..
 * 			Deletes all deletable attributes and folders the given folder contains. If an attribute is not deletable, the folders containing the attribute are not deleted.
 * 			newName has to be legal, must not be empty, and must not begin or end with whitespace.
 * 			Renames the specified folder (while preserving it's guid). The root folder can't be renamed, two folders in the same parent folder can't have the same name.
 */
__APIEXPORT GSErrCode ACAPI_Attribute_RenameFolder (const API_AttributeFolder& folder, const GS::UniString& newName);


/**
 * @brief Enables the attribute picker functionality for a push check, if the user clicks the push check, the picker will open. Attributes pickers can be used to choose an attribute. On these new pickers, the folder structure and searching functionality is enabled.
 * @ingroup Dialog
 * @since Archicad 26
 * @param attributePickerParams [in] Parameters of attribute picker (type of the attribute, the parameters of push check).
 * @param attributePicker [out] The constructed picker.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Incorrect attributePickerParams was specified.
 */
__APIEXPORT GSErrCode ACAPI_Dialog_CreateAttributePicker (const API_AttributePickerParams& attributePickerParams,
																			   GS::Owner<API_AttributePicker>& attributePicker);


/**
 * @brief Enables the attribute folder picker functionality for a push check, if the user clicks the push check, the picker will open. Attributes folder pickers can be used to choose an attribute folder.
 * @ingroup Attribute
 * @since Archicad 26
 * @param attributeFolderPickerParams [in] Parameters of attribute folder picker (type of the attribute, the parameters of push check).
 * @param attributeFolderPicker [out] The constructed picker.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Incorrect attributeFolderPickerParams was specified.
 */
__APIEXPORT GSErrCode ACAPI_Attribute_CreateAttributeFolderPicker	(const API_AttributeFolderPickerParams& attributeFolderPickerParams,
																	 GS::Owner<API_AttributeFolderPicker>& attributeFolderPicker);

/**
 * @brief Returns the first valid attribute index
 * @ingroup Attribute
 * @param typeID type of Attribute
 * @since Archicad 27
 * @return
 * 			- API_AttributeIndex - the index of the first valid attribute of type or APIInvalidAttributeIndex
 */
__APIEXPORT API_AttributeIndex ACAPI_Attribute_GetFirstValidAttribute (API_AttrTypeID typeID);


/**
 * @brief Returns the number of registered library parts.
 * @ingroup LibraryPart
 * @param count [out] number of Library Parts.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - count is nullptr
 * @remarks This function is used to get the number of currently available library parts. The number of the different type of library parts can not be obtained with this function; you have to walk through all the library parts to get e.g. the number of windows in the library.
 * 			Library Parts are referenced by indices. This function returns the maximal value such a reference; valid indices are in the [1? count ] range. The special value zero used some time to reference to an empty Library Part, as in case of an empty opening.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_GetNum-Example-Snippet
 * @warning *Legacy function - to be deleted in future versions, use ACAPI::LM::LibraryManager::FindLibParts instead*
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_GetNum (Int32 *count);


/**
 * @brief Searches for a registered Library Part in the loaded libraries.
 * @ingroup LibraryPart
 * @param ancestor [in/out] The library part to search for
 * @param createIfMissing [in] Set to true to create a reference if it is missing.
 * @param onlyPlaceable [in] The search is limited to placeable library parts only. Optional parameter, can be omitted.
 * @return
 * 			- NoError - The function has completed with success, the Library Part has been found (or reference created successfully if createIfMissing is true)
 * 			- APIERR_MISSINGDEF - The originating library part file is missing. The document name is still filled.
 * 			- APIERR_BADPARS - ancestor is nullptr
 * 			- APIERR_BADID - no library part is found according to the given ownUnID, parentUnID or typeID parameters
 * 			- APIERR_BADNAME - no library part is found with the given document or file name
 * 			- APIERR_MEMFULL - the reference cannot be created; only when createIfMissing is true
 * @remarks This function is used to search a Library Part in the loaded libraries.
 * 			The Library Part can be referenced by the following criteria:
 * 			- the most exact identification of a library part is the global unique ID. You can copy the unique ID string of the requested library part into the ownUnID field of the @ref API_LibPart structure. Since the revision part of the unique ID can be changed by minor modifications (see Library Part Subtypes for more details), only main GUID match can meet the condition. If you search by ownUnID, set the docu_Name and file_Name fields to empty string
 * 			- if you leave the ownUnID and docu_Name fields blank, but file_Name is given, the function will search by the name of the library part file
 * 			- if ownUnID and file_Name are not specified, or docu_Name is not an empty string if docu_Name is given, @ref ACAPI_LibraryPart_Search tries to find a library part with that document name. Note that document names are not unique. You may reduce the chance of mismatch if you also specify the subtype parentUnID if parentUnID is given, but docu_UName is empty, the function retrieves the first library part in the enumerated libraries which is a descendant of the specified parent subtype
 * 			- if docu_Name is given, @ref ACAPI_LibraryPart_Search tries to find a library part with that document name. Note that document names are not unique. You may reduce the chance of mismatch if you also specify the subtype parentUnID
 * 			- if parentUnID is given, but docu_UName is empty, the function retrieves the first library part in the enumerated libraries which is a descendant of the specified parent subtype
 * 			Library Part Subtypes
 * 			typeID
 * 			parentUnID
 * @c APILib_ObjectID
 * @c API_ZombieLibID
 * @ref ACAPI_LibraryPart_Search can also create a virtual reference to a none existing library part (i.e. an index which can be referred to) if the library part has not found in the active libraries and createIfMissing was set true). Same effect appears when an opened plan refers to a library part which is not in the active libraries. In this case Archicad places a filled circle on the plan where a missing library part is referenced.
 * 		On success @ref ACAPI_LibraryPart_Search fills out all the fields of the @ref API_LibPart structure, therefore remember to free the location pointer allocated by the function if you do not not need it any more.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_Search-Example-Snippet
 * @warning *Legacy function - to be deleted in future versions, use ACAPI::LM::LibraryManager::FindLibParts instead*
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_Search (API_LibPart *ancestor, bool createIfMissing, bool onlyPlaceable = false);


/**
 * @brief Searches for registered Library Parts in the loaded libraries.
 * @ingroup LibraryPart
 * @param ancestor [in] The library part type to search for
 * @param pattern [in] Pattern to search for in the loaded librairies.
 * @param result [out] Array to store the first 50 found library parts.
 * @param numFound [out] Number of found library parts.
 * @return
 * 			- NoError - The function has completed with success, the Library Part has been found (or reference created successfully if createIfMissing is true)
 * 			- APIERR_BADPARS - ancestor is nullptr, numFound is nullptr or pattern is empty
 * 			- APIERR_BADID - no library part is found according to the given typeID or ownUnID as ancestor
 * @remarks This function is used to search a Library Parts in the loaded libraries.
 * 			The search pattern can be one or more words or expression(s) in quotes.
 * 			Please remember that library parts are classified according to the subtype hierarchy as it is explained in the Library Part Subtypes chapter of this documentation. The expandable subtype system made the typeID based distinction of library parts obsolete, though you may use this field for searching by subtype instead of parentUnID for internal ancestor nodes (note that in this case @c APILib_ObjectID corresponds to Model Elements, and @c API_ZombieLibID marks the General Object subtype).
 * @warning *Legacy function - to be deleted in future versions, use ACAPI::LM::LibraryManager::FindLibParts instead*
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_PatternSearch (const API_LibPart *ancestor, const GS::UniString& pattern, API_LibPart result[50], Int32* numFound);


/**
 * @brief Returns the data of a registered Library Part.
 * @ingroup LibraryPart
 * @param libPart [in/out] Definition of the library part.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_MISSINGDEF - The originating library part file is missing. The document name is still filled.
 * 			- APIERR_BADPARS - libPart is nullptr or the index is invalid.
 * 			- APIERR_BADINDEX - libPart.index is not correct for the given typeID.
 * @remarks This function is used to get the data of the requested Library Part defined by the index field. The other fields of the structure are returned by Archicad. You cannot use names here; first you have to find the library part with @ref ACAPI_LibraryPart_Search function.
 * 			After calling @ref ACAPI_LibraryPart_Get please remember to free the location pointer allocated by the function if you do not need it any more.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_Get-Example-Snippet
 * @warning *Legacy function - to be deleted in future versions, use ACAPI::LM::LibraryManager::FindLibParts instead*
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_Get (API_LibPart *libPart);


/**
 * @brief Returns the default parameters of a registered Library Part.
 * @ingroup LibraryPart
 * @param libInd Index of the library part.
 * @param a The A parameter of the the Library Part
 * @param b The B parameter of the the Library Part
 * @param addParNum The number of additive parameters; others than A and B
 * @param addPars The additive parameters
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Invalid libInd, or any of the parameters are nullptr, or the addressed Library Part is a macro, picture file etc.
 * 			- APIERR_MEMFULL - not enough memory to complete the operation
 * @remarks This function is used to get the default parameters of the requested Library Part defined by libInd.
 * 			In the a and b parameters, the values of the A and B variables are returned; in the addParNum and addPars parameters the additive parameter list is returned, the number of the parameters and the actual values, respectively.
 * 			Refer to the @ref API_AddParType to get more information on a Library Part parameter.
 * 			It is absolutely important that the function returns a formalized data handle to describe the parameter list. The content is not equal to the section handle returned by the @ref ACAPI_LibraryPart_GetSection function called with the @c API_SectParamDef argument.
 * 			The function works only on real Library Parts. In the case the type of the target Library Part is not listed below, the function returns an error code. This is since other type of Library Parts are just simple picture or text files which are enumerated and registered from the active library folders; such a picture or macro.
 * 			Applicable type of Library Parts which have parameter list are:
 * 			- @c APILib_WindowID,
 * 			- @c APILib_DoorID,
 * 			- @c APILib_ObjectID,
 * 			- @c APILib_LampID,
 * 			- @c APILib_RoomID,
 * 			- @c APILib_LabelID,
 * 			- @c APILib_MacroObjID,
 * 			- @c APILib_PropertyID
 * 			Do not forget to dispose the additive parameter handle if it is not needed any more. Use the @ref ACAPI_DisposeAddParHdl function for this purpose.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_GetParams-Example-Snippet
 * @warning *Legacy function - to be deleted in future versions, use ACAPI::LM::GSMObject::GetParameters instead*
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_GetParams (Int32			libInd,
																 double			*a,
																 double			*b,
																 Int32			*addParNum,
																 API_AddParType	***addPars);


/**
 * @brief Returns an existing section of a registered Library Part.
 * @ingroup LibraryPart
 * @param libInd [in] Index of the library part
 * @param section [in/out] Definition of the section. The section is defined by the sectType an the subIdent fields of the @ref API_LibPartSection structure.
 * @param sectionHdl [out] Section data.
 * @param sectionStr [out] The content of textual sections as a Unicode string. Pass the address of an existing Unicode string if you need this data.
 * @param password [in] The (optional) password that encrypted the section.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Invalid libInd, or any of the parameters are nullptr, or the addressed Library Part is a macro, picture file etc.
 * 			- APIERR_NOLIBSECT - no such a section in the Library Part
 * @remarks This function is used to get the data of the requested section from the Library Part.
 * 			It returns the requested section of the Library Part defined by libInd in the sectionHdl. The section is defined by the sectType field of the @ref API_LibPartSection structure. If it (a four-character case-sensitive identifier) is not any of the standard types, it is interpreted as a custom type. In this case you are responsible for the content and the management of this section. The description of the standard sections can be found in the Archicad Reference Manual.
 * 			The function works only on real Library Parts. In the case the type of the target Library Part is not listed below, the function returns an error code. This is since other type of Library Parts are just simple picture or text files which are enumerated and registered from the active library folders; such a picture or macro.
 * 			Applicable type of Library Parts are:
 * 			- @c APILib_WindowID,
 * 			- @c APILib_DoorID,
 * 			- @c APILib_ObjectID,
 * 			- @c APILib_LampID,
 * 			- @c APILib_RoomID,
 * 			- @c APILib_LabelID,
 * 			- @c APILib_MacroObjID,
 * 			- @c APILib_PropertyID
 * 			Do not forget to dispose the data if it is not needed any more.
 * 			From API 11, the textual section data is now stored as a GS::UniString in the library parts. You can also obtain the text in this format in the sectionStr parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_GetSection-Example-Snippet
 * @warning *Legacy function - to be deleted in future versions, use ACAPI::LM::GSMObject::GetCustomSection instead*
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_GetSection (Int32					libInd,
																  API_LibPartSection	*section,
																  GSHandle				*sectionHdl,
																  GS::UniString			*sectionStr,
																  GS::UniString			*password = nullptr);


/**
 * @brief Updates a section of a registered Library Part.
 * @ingroup LibraryPart
 * @param libInd [in] Index of the Library Part
 * @param section [in] Identifier of the section.
 * @param sectionHdl [in] Section data.
 * @param sectionStr [in] Optional Unicode content of any textual section.
 * @param password [in] The (optional) password that encrypted the section.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Invalid libInd, or any of the parameters are nullptr, or the addressed Library Part is a macro, picture file etc.
 * @remarks This function is used to update the requested section of the library part defined by libInd with the data in the supplied handle.
 * 			In the case the identified section exists in the Library Part it will be updated; if the section is not found it will be created.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @warning *Legacy function - to be deleted in future versions, use ACAPI::LM::GSMObject::SetCustomSection instead*
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_UpdateSection (Int32						libInd,
																	 const API_LibPartSection	*section,
																	 GSHandle					sectionHdl,
																	 GS::UniString				*sectionStr,
																	 GS::UniString				*password = nullptr);


/**
 * @brief Sets up an empty 2D binary (drawing) section to fill up from API elements.
 * @ingroup LibraryPart
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NESTING - recursive call, @ref ACAPI_LibraryPart_GetSect_2DDrawHdl was not called after the previous call
 * 			- APIERR_MEMFULL - not enough memory
 * @remarks This function is used to initialize the 2D binary (drawing) section of the library part.
 * 			The subsequent calls to the element creation function @ref ACAPI_Element_Create will be redirected. Instead of putting the created elements into the current database it will put them into the opened 2D symbol drawing, until the @ref ACAPI_LibraryPart_GetSect_2DDrawHdl function is called.
 * 			This is the only way to add a 2D binary drawing section to a Library Part. However the internal format of the section handle is public, it is a quite hard job to provide a full solution without this functionality.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_SetUpSect_2DDrawHdl-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_SetUpSect_2DDrawHdl (void);


/**
 * @brief Returns the 2D binary (drawing) section data created from API elements.
 * @ingroup LibraryPart
 * @param sectionHdl [out] 2D binary section data
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - sectionHdl is nullptr
 * 			- APIERR_GENERAL - No 2D drawing section has been opened with the @ref ACAPI_LibraryPart_SetUpSect_2DDrawHdl function.
 * @remarks This function is used to close and return the 2D binary (drawing) section of the library part, prepared to be used with @ref ACAPI_LibraryPart_AddSection function.
 * 			This function must be called to close the 2D binary section if the @ref ACAPI_LibraryPart_SetUpSect_2DDrawHdl function has succeeded; even if any of the in-between function calls to @ref ACAPI_Element_Create has failed.
 * 			Refer to the @ref ACAPI_LibraryPart_SetUpSect_2DDrawHdl function to get more details on this topics.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_GetSect_2DDrawHdl-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_GetSect_2DDrawHdl (GSHandle *sectionHdl);


/**
 * @brief Prepares the parameter section data to save into a Library Part.
 * @ingroup LibraryPart
 * @param libPart [in] The library part to work on
 * @param addPars [in] Additive parameters of the Library Part
 * @param a [in] the value of the A parameter
 * @param b [in] the value of the B parameter
 * @param sect2DDrawHdl [in] 2D binary section data
 * @param sectionHdl [out] the prepared parameter section data
 * @param password [in] The (optional) password that encrypted the section.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The libPart or the sectionHdl parameter is nullptr
 * 			- APIERR_BADID - The function cannot work with library parts of type specified by libPart->typeID
 * @remarks This function is used to prepare the parameter section of the Library Part, and return the prepared section handle in sectionHdl.
 * 			The returned handle than can be supplied to the @ref ACAPI_LibraryPart_AddSection or the @ref ACAPI_LibraryPart_UpdateSection functions to put it into the Library Part. The a/b and sect2DDrawHdl parameters are exclusive, they are both used to calculate the bounding box of the symbol of the Library Part. Specifically, a and b should be defined only if sect2DDrawHdl is nullptr, otherwise their value will be calculated and returned.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_GetSect_ParamDef-Example-Snippet
 * @warning *Legacy function - to be deleted in future versions, use ACAPI::LM::GSMObject setters instead*
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_GetSect_ParamDef (const API_LibPart	*libPart,
																		API_AddParType		**addPars,
																		double				*a,
																		double				*b,
																		GSHandle			sect2DDrawHdl,
																		GSHandle			*sectionHdl,
																		GS::UniString		*password = nullptr);


/**
 * @brief Starts to create a new Library Part from scratch.
 * @ingroup LibraryPart
 * @param libPart [in] Parameters of the Library Part to create
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NESTING - Recursive call, @ref ACAPI_LibraryPart_Save was not called after the previous call
 * 			- APIERR_BADPARS - The libPart parameter is nullptr, or holds invalid data
 * 			- APIERR_BADID - No match found with the passed parentUnID
 * 			- APIERR_NOLIB - No valid location was passed, and there is no active library also
 * 			- APIERR_READONLY - The specified location is read-only
 * @remarks This function is used to create a new empty Library Part from scratch.
 * 			You have to specify the subtype of the Library Part in order to place it under the proper node in the ancestry hierarchy. For more information about subtypes see the Library Part Subtypes passage.
 * 			By default, all new Library Parts are created into the active library folder, however you can specify any directory you want. If the location field describes a valid folder in the file system, the Library Part will be created there. Note that the name of the Library Part is determined by the docu_UName, so the file name itself is ignored both in the file_Name and location fields.
 * 			This function creates an empty Library Part. The sections should be defined with subsequent function calls; basically there are two ways to create a section:
 * 			- Write the section as a stream with the functions @ref ACAPI_LibraryPart_NewSection, @ref ACAPI_LibraryPart_WriteSection, and @ref ACAPI_LibraryPart_EndSection
 * 			- Create the section in one step by calling the @ref ACAPI_LibraryPart_AddSection function.
 * 			The Library Part itself will be created and registered upon the @ref ACAPI_LibraryPart_Save function call. Do not forget to call this function in order to close the scratch file; even in case of any error encountered in the other function calls.
 * 			Macros and pictures cannot be created in this way. Refer to the function @ref ACAPI_LibraryPart_Register for more details.
 * 			If the function has completed with success the index of the newly created library part is given by the index field of the @ref API_LibPart structure.
 * 			Do not forget to dispose of the used section handles.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_Create-Example-Snippet
 * @warning *Legacy function - to be deleted in future versions, use ACAPI::LM::GSMObject setters instead*
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_Create (const API_LibPart *libPart);


/**
 * @brief Adds a new section to the Library Part under creation.
 * @ingroup LibraryPart
 * @param section [in] Parameters of the new section.
 * @param sectionHdl [in] Section data.
 * @param sectionStr [in] Content of any textual section as a Unicode string.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_GENERAL - No scratch file has been opened by the @ref ACAPI_LibraryPart_Create function.
 * @remarks This function is used to add a whole section to the Library Part opened to create.
 * 			This function is allowed to call between the @ref ACAPI_LibraryPart_Create and @ref ACAPI_LibraryPart_Save functions only, while creating a Library Part from scratch. The identifier of the section must be defined in the @ref API_LibPartSection parameter. The section data is passed through the sectionHdl parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_AddSection-Example-Snippet
 * @warning *Legacy function - to be deleted in future versions, use ACAPI::LM::GSMObject setters instead*
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_AddSection (const API_LibPartSection	*section,
																  GSHandle					sectionHdl,
																  GS::UniString				*sectionStr);


/**
 * @brief Opens a new section to write into the Library Part under creation.
 * @ingroup LibraryPart
 * @param section [in] Parameters of the new section.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_GENERAL - No scratch file has been opened by the @ref ACAPI_LibraryPart_Create function.
 * @remarks This function is used to open a new section to write into the Library Part opened to create.
 * 			This function is allowed to call between the @ref ACAPI_LibraryPart_Create and @ref ACAPI_LibraryPart_Save functions only, while creating a Library Part from scratch. The identifier of the section must be defined in the @ref API_LibPartSection parameter. The section data is passed through the sectionHandle parameter.
 * 			This is the other way to add sections to the library part, where the section is opened, then data is added with repetitive calls to the @ref ACAPI_LibraryPart_WriteSection function, and finally it is closed with the @ref ACAPI_LibraryPart_EndSection function call.
 * 			Refer to the @ref ACAPI_LibraryPart_AddSection to add a section in one step.
 * 			Do not nest these function calls. Always close the opened section with @ref ACAPI_LibraryPart_EndSection before you open an other.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_NewSection-Example-Snippet
 * @warning *Legacy function - to be deleted in future versions, use ACAPI::LM::GSMObject setters instead*
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_NewSection (const API_LibPartSection *section);


/**
 * @brief Writes data into an opened section of the Library Part under creation.
 * @ingroup LibraryPart
 * @param nByte [in] Number of bytes.
 * @param data [in] Data to be written.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_GENERAL - No section has been opened with the @ref ACAPI_LibraryPart_NewSection function.
 * @remarks This function is used to write data into the section recently opened with @ref ACAPI_LibraryPart_NewSection function.
 * 			It writes the given data (nByte number of bytes addressed by data) to the section recently opened with @ref ACAPI_LibraryPart_NewSection function. If you write the data to a textual section, don't forget to include the newline (+linefeed for Windows) character(s) in data.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_WriteSection-Example-Snippet
 * @warning *Legacy function - to be deleted in future versions, use ACAPI::LM::GSMObject setters instead*
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_WriteSection (Int32 nByte, GSConstPtr data);


/**
 * @brief Closes the last opened section of the Library Part under creation.
 * @ingroup LibraryPart
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_GENERAL - No scratch file has been opened by the @ref ACAPI_LibraryPart_Create function.
 * @remarks This function is used to close the section recently opened with the @ref ACAPI_LibraryPart_NewSection function.
 * 			Data of the section should be filled by calling the @ref ACAPI_LibraryPart_WriteSection function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_EndSection-Example-Snippet
 * @warning *Legacy function - to be deleted in future versions, use ACAPI::LM::GSMObject setters instead*
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_EndSection (void);


/**
 * @brief Saves the Library Part has been created and registers it.
 * @ingroup LibraryPart
 * @param libPart [in/out] Parameters of the library part to create
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The libPart parameter is nullptr
 * 			- APIERR_GENERAL - No scratch file has been opened with the @ref ACAPI_LibraryPart_Create function.
 * @remarks This function is used to save the recently created library part by the @ref ACAPI_LibraryPart_Create function.
 * 			The same parameters should be passed in the @ref API_LibPart structure as it was pass to the @ref ACAPI_LibraryPart_Create function. In the index field, the library index of the currently created library part is returned, which you can use in subsequent operations.
 * 			This function must be called to close the scratch if the @ref ACAPI_LibraryPart_Create function has succeed; even if any of the in-between function calls have failed.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_Save-Example-Snippet
 * @warning *Legacy function - to be deleted in future versions, use ACAPI::LM::GSMObject setters instead*
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_Save (API_LibPart *libPart);

/**
 * @brief Virtually draws the shape of a registered Library Part.
 * @ingroup LibraryPart
 * @param libInd [in] Index of the library part
 * @param instanceElemGuid [in] Instance element GUID; if APINULLGuid, then the drawing parameters will be the default parameters of the library part (with no transformation, etc.), otherwise they are taken from the instance of the library part defined by this GUID.
 * @param gdlContext [in] The environment of the GDL object (sets GLOB_CONTEXT GDL Global parameter).
 * 					 | Context | Value |
 * 					 |---------|-------|
 * 					 | Default (depends on the current database) | @c APIGdl_Default |
 * 					 | Library Part Editing Dialog (all windows within it) | @c APIGdl_FromEdit |
 * 					 | Floor Plan Window | @c APIGdl_FromFloor |
 * 					 | 3D Window | @c APIGdl_From3DWin |
 * 					 | Section/Elevation Windows | @c APIGdl_FromSide |
 * 					 | Library Part Settings Dialog | @c APIGdl_FromDial |
 * 					 | List generated about Library Part | @c APIGdl_FromList |
 * 					 | Detail Windows | @c APIGdl_FromDetail |
 * 					 | Layout Windows | @c APIGdl_FromLayout |
 * @param shapePrimsProc [in] Callback function for catching the drawing primitives of the Libpart Part shape.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - shapePrimsProc is nullptr, or invalid libInd parameter has been passed.
 * 			- APIERR_BADINDEX - Invalid instanceElemGuid for the element type that libInd implies.
 * 			- APIERR_NESTING - The function was called from a ShapePrimsProc; recursion is not allowed.
 * @remarks This function is used to draw the shape of the Libpart Part; as it would appear on the floor plan.
 * 			The key point is the parameter values to use, since it absolutely determines how a Library Part looks like when it is placed. That's why the instanceElemGuid parameter should be passed; if it is zero the default parameter set, otherwise the parameter set of an already placed instance will be used.
 * 			The shape will be passed to the callback function with the same drawing primitives would be drawn onto the display. Refer to he ShapePrimsProc to get further details.
 * 			These drawing procedures cannot be nested. From the callback function it is not allowed to call the @c ACAPI_LibraryPart_ShapePrims function again.
 * 			The function works only on Library Parts can be placed onto the floor plan. Applicable type of Library Parts are: @c APILib_WindowID, @c APILib_DoorID, @c APILib_ObjectID, @c APILib_LampID, @c APILib_RoomID (zone stamp), @c APILib_LabelID (symbol label).
 * 			In order to get the hotspots of a library part or an object instance use the @ref ACAPI_LibraryPart_GetHotspots function.
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_ShapePrims (Int32				libInd,
																  const API_Guid&	instanceElemGuid,
																  short				gdlContext,
																  ShapePrimsProc	*shapePrimsProc);


/**
 * @brief Retrieves the hotspots of a registered Library Part.
 * @ingroup LibraryPart
 * @param libInd [in] Index of the library part
 * @param instanceElemGuid [in] Instance element GUID; if APINULLGuid, then the drawing parameters will be the default parameters of the library part (with no transformation, etc.), otherwise they are taken from the instance of the library part defined by this GUID.
 * @param nHotspots [out] Numbers of hotspots.
 * @param hotspots [out] Handle that contains the hotspot data on return.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - nHotspots or hotspots parameter is nullptr, or invalid libInd has been passed
 * 			- APIERR_BADINDEX - Invalid instanceElemGuid for the element type that libInd implies
 * @remarks This function is used to retrieve the hotspots of the Libpart Part. The library part is identified the same way as @ref ACAPI_LibraryPart_ShapePrims does.
 * 			The hotspots return in an array of @ref API_PrimHotspot structures. The coordinate values in the loc field are interpreted in the local coordinate system of the library part, however if the referred element instance has been resized, the coordinates follow the scale. If you would like to get the actual position of a hotspot of the specified element instance, use the neig field to convert the coordinates.
 * 			Do not forget to dispose the hotspots handle after the operation.
 * 			The function works only on Library Parts that can be placed onto the floor plan. Applicable type of Library Parts are:
 * 			- @c APILib_WindowID
 * 			- @c APILib_DoorID
 * 			- @c APILib_ObjectID
 * 			- @c APILib_LampID
 * 			- @c APILib_RoomID (zone stamp)
 * 			- @c APILib_LabelID (symbol label)
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_GetHotspots-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_GetHotspots (Int32				libInd,
																   const API_Guid&		instanceElemGuid,
																   Int32*				nHotspots,
																   API_PrimHotspot***	hotspots);


/**
 * @brief Registers a Library Part.
 * @ingroup LibraryPart
 * @param libPart [in/out] Parameters of the library part;
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - libPart is nullptr, or refers to invalid data
 * @remarks This function is used to register a new Library Part.
 * 			You can register any kind of Library Part, however this function basically implemented for handling macros and pictures. These type of Library Parts are simple text and picture files which can be created without any help of the API. If you want to create a new macro, you just have to create a simple text file somewhere in the file system, and register it as a macro.
 * 			If the function has completed with success, the reference index is returned by Archicad in the libPart->index parameter. Use this value to reference to the registered Library Part in any subsequent operation.
 * 			Creating real Archicad library parts are much more complicated. Although the file format is public, it is strongly recommended to use the API functions while creating an object, lamp, door etc. kind library part. In this case you do not have to register it, because the @ref ACAPI_LibraryPart_Save function does it.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_Register-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_Register (API_LibPart *libPart);


/**
 * @brief Registers an array of Library Parts.
 * @ingroup LibraryPart
 * @param libParts [in/out] Parameters of the library parts; the type, the owner signature and the location of the library parts must be initialized, by setting the typeID, ownerID and the location fields respectively. Other values will be filled and returned by Archicad.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - libParts is nullptr, or any of its members refer to invalid data.
 * @remarks This function is used to register an array of new library parts. During the time of the batch registration internal library part caching is disabled, providing better performance.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_RegisterAll-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_RegisterAll (GS::Array<API_LibPart>* libParts);


/**
 * @brief Returns the list of sections contained by a registered Library
 * @ingroup LibraryPart
 * @param libInd [in] Index of the library part
 * @param nSection [out] Number of the sections found
 * @param sections [out] section data returned
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Invalid libInd, or any of the parameters are nullptr, or the addressed Library Part is a macro, picture file etc.
 * @remarks This function is used to get the headers of the sections the library part is built from.
 * 			The function works only on real Library Parts. In the case the type of the target Library Part is not listed below, the function returns an error code. This is since other type of Library Parts are just simple picture or text files which are enumerated and registered from the active library folders; such a picture or macro.
 * 			Applicable type of Library Parts are: @c APILib_WindowID, @c APILib_DoorID, @c APILib_ObjectID, @c APILib_LampID, @c APILib_RoomID, @c APILib_LabelID, @c APILib_MacroObjID, @c APILib_PropertyID
 * 			Do not forget to dispose the returned handle if it is not needed any more.
 * 			Note, that it cannot be used between @ref ACAPI_LibraryPart_Create and @ref ACAPI_LibraryPart_Save functions.
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_GetSectionList (Int32					libInd,
																	  Int32					*nSection,
																	  API_LibPartSection	***sections);


/**
 * @brief Returns the detail parameters of a registered Library Part.
 * @ingroup LibraryPart
 * @param libInd [in] Index of the Library Part
 * @param details [out] Detail parameter of the Library Part
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - any of the parameters are nullptr, or
 * 			the addressed Library Part is a macro, picture file etc.
 * @remarks This function is used to get the detail parameters of a Library Part. These parameters can be edited in Archicad by clicking the Details button on the parameter list editor dialog box.
 * 			The function works only on real Library Parts. In the case the type of the target Library Part is not listed below, the function returns an error code. This is since other type of Library Parts are just simple picture or text files which are enumerated and registered from the active library folders; such a picture or macro.
 * 			Applicable type of Library Parts are:
 * 			- @c APILib_WindowID
 * 			- @c APILib_DoorID
 * 			- @c APILib_ObjectID
 * 			- @c APILib_LampID
 * 			- @c APILib_RoomID
 * 			- @c APILib_LabelID
 * 			To change the parameters refer to the @ref ACAPI_LibraryPart_SetDetails_ParamDef function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_GetDetails-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_GetDetails (Int32					libInd,
																  API_LibPartDetails	*details);


/**
 * @brief Sets the detail parameters of a Library Part parameter section handle.
 * @ingroup LibraryPart
 * @param libPart [in] The library part to work on.
 * @param paramHdl [in/out] Parameter section data
 * @param details [in] Detail parameters
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - any of the parameters are nullptr
 * @remarks This function is used to store detail parameters in the parameter section handle. These parameters can be edited in Archicad by clicking the Details button on the parameter list editor dialog box.
 * 			Applicable type of Library Parts are:
 * 			- @c APILib_WindowID
 * 			- @c APILib_DoorID
 * 			- @c APILib_ObjectID
 * 			- @c APILib_LampID
 * 			- @c APILib_RoomID
 * 			- @c APILib_LabelID
 * 			To get the detail parameters of a registered Library Part refer to the @ref ACAPI_LibraryPart_GetDetails function.
 * 			Note, that the @ref ACAPI_LibraryPart_GetDetails and @ref ACAPI_LibraryPart_SetDetails_ParamDef functions are not symmetrical; it is shown in the function names too. Since the detail parameters are stored in the parameter section of the Library Part, this implementation interface is the most effective.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_SetDetails_ParamDef-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_SetDetails_ParamDef (const API_LibPart		*libPart,
																		   GSHandle					paramHdl,
																		   const API_LibPartDetails	*details);


/* -- Element Manager --------------------- */


/**
 * @brief Retrieves the actual default settings for the element of type.
 * @ingroup Element
 * @param element [in/out] The desired element for which the defaults are needed.
 * @param memo [out] This is needed only in case of library part-based elements (including zone stamps).
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter is nullptr ; element
 * 			- APIERR_BADID - The element type is invalid, or the element type is not supported by the server application
 * 			- APIERR_REFUSEDCMD - The element type is not a valid target for the operation; @c API_SectElemID
 * @remarks This function is used to obtain the actual default settings for an element.
 * 			The requested type is identified by the type field of the header. The function fills the central part of the @ref API_Element structure with values from the Settings dialog. You have to fill in the geometric information yourself; if you need it.
 * 			The memo parameter is used only for library part based elements (including zone stamps), where the params field is filled with the actual parameter values of the referenced Library Part. Do not forget to call the @ref ACAPI_DisposeElemMemoHdls function to dispose of the obtained handles.
 * 			To change the default settings use the @ref ACAPI_Element_ChangeDefaults function.
 * 			You can use the returned values to initialize the element attributes and parameters to create a new instance. Refer to the @ref ACAPI_Element_Create function for more details.
 * 			In order to get the default settings of markered element types (API_WindowType, @ref API_DoorType, @ref API_CutPlaneType, @ref API_ChangeMarkerType, @ref API_DetailType and @ref API_WorksheetType) use the @ref ACAPI_Element_GetDefaultsExt function instead.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetDefaults-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetDefaults (API_Element *element, API_ElementMemo *memo);


/**
 * @brief Retrieves the actual default settings for the Window, Door, Section, Elevation, Interior Elevation, ChangeMarker, Detail, Worksheet, or Stair element with its marker(s). You are able to obtain Curtain Wall and its subelem default settings also via this function.
 * @ingroup Element
 * @since Archicad 25
 * @param element [in/out] The desired element for which the defaults are needed. The element->header.type can be @c API_WindowID, @c API_DoorID, @c API_CutPlaneID, @c API_ElevationID, @c API_InteriorElevationID, @c API_ChangeMarkerID, @c API_DetailID, @c API_WorksheetID, @c API_CurtainWallID, @c API_CurtainWallPanelID, @c API_CurtainWallFrameID, @c API_CurtainWallJunctionID, @c API_CurtainWallAccessoryID, @c API_StairID or @c API_ExternalElemID.
 * @param memo [out] This is needed only in case of library part-based elements (including zone stamps).
 * @param nSubElems [out] The subelem of the desired element for which the defaults are needed.
 * @param subElems [out] The subelem(s) (normal, story handle, interior elevation common marker) of the desired element.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed element parameter is nullptr.
 * 			- APIERR_BADID - The element type should be @c API_WindowID, @c API_DoorID, @c API_CutPlaneID, @c API_ElevationID, @c API_InteriorElevationID, @c API_ChangeMarkerID, @c API_DetailID, @c API_WorksheetID, @c API_CurtainWallID, @c API_CurtainWallFrameID, @c API_CurtainWallPanelID, @c API_CurtainWallJunctionID, @c API_CurtainWallAccessoryID, @c API_StairID or @c API_ExternalElemID.
 * 			- APIERR_BADID can be returned in case of API_ExternalElemID, when the function is unsupported for the specified classID.
 * @remarks This function is used to obtain the actual default settings for a Window, Door, Section, Elevation, Interior Elevation, ChangeMarker, Detail or Worksheet element, as an alternative of @ref ACAPI_Element_GetDefaults.
 * 			The requested type is identified by the type field of the header. The function fills the central part of the @ref API_Element structure with values from the Settings dialog. You have to fill in the geometric information yourself, if you need it.
 * 			The memo parameter is used only for library part based elements (including zone stamps), where the params field is filled with the actual parameter values of the referenced Library Part. Do not forget to call the @ref ACAPI_DisposeElemMemoHdls function to dispose of the obtained handles.
 * 			To change the default settings use the @ref ACAPI_Element_ChangeDefaultsExt function.
 * 			You can use the returned values to initialize the element attributes and parameters to create a new instance. Refer to the @ref ACAPI_Element_CreateExt function for more details.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetDefaultsExt-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetDefaultsExt (API_Element			*element,
																	  API_ElementMemo		*memo,
																	  UInt32				nSubElems,
																	  API_SubElement		*subElems);


/**
 * @brief Changes the default parameters of an element.
 * @ingroup Element
 * @param element [in] Contains the general parameters to which you would like to change the defaults.
 * @param memo [in][ Contains the special parameters to which you would like to change the defaults.
 * @param mask [in] Contains a mask that specifies which parameters you would like to change. The memo fields are always used when they contain valid data.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter is nullptr ; element
 * 			- APIERR_BADID - The element type is invalid, or the element type is not supported by the server application
 * 			- APIERR_REFUSEDCMD - The element type is not a valid target for the operation; @c API_SectElemID
 * 			- APIERR_MEMFULL - Not enough memory to complete the operation
 * @remarks This function is used to change the actual default settings for an element type. Only those parameters are changed where the corresponding field in the mask is not 0. The requested type is identified by the type field of the header.
 * 			The memo parameter is used only in the case of @c API_WindowID, @c API_DoorID, @c API_ObjectID, @c API_LampID, @c API_RoomID, @c API_LabelID, @c API_PictureID and @c API_ExternalElemID. For library part-based elements, if memo is set to nullptr, the default parameters of the originating library part are used, otherwise the values are taken from the params field of memo.
 * 			To retrieve the actual settings defaults use the @ref ACAPI_Element_GetDefaults function.
 * 			Only those parameters are required to fill in the element argument, which are marked to be changed. There are macros to set up the mask values correctly. They are:
 * 			- ACAPI_ELEMENT_MASK_CLEAR - Clear all the flags in the mask
 * 			- ACAPI_ELEMENT_MASK_SETFULL - Set all the flags in the mask
 * 			- ACAPI_ELEMENT_MASK_SET - Set only one flag in the mask according to one element parameter
 * 			- ACAPI_ELEMENT_MASK_CHECK - Check the mask for one element parameter
 * 			Don't forget to call @ref ACAPI_DisposeElemMemoHdls to dispose of the passed handles.
 * 			Note, that the @c ACAPI_SetDefaults function became obsolete; it was the solution in API 1.3.
 * 			In order to change the default settings of markered element types (API_WindowType, @ref API_DoorType, @ref API_CutPlaneType, @ref API_ChangeMarkerType, @ref API_DetailType, @ref API_WorksheetType and @ref API_ExternalElemType) use the @ref ACAPI_Element_ChangeDefaultsExt function instead.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_ChangeDefaults-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_ChangeDefaults (API_Element		*element,
																	  API_ElementMemo	*memo,
																	  const API_Element	*mask);


/**
 * @brief Changes the default parameters of the Window, Door, Section, Elevation, Interior Elevation, ChangeMarker, Detail, Worksheet, or Stair default element and its marker(s). You are able to change Curtain Wall and its subelem default settings also via this function.
 * @ingroup Element
 * @since Archicad 25
 * @param element [in] Contains the general parameters to which you would like to change the defaults. The element->header.type can be @c API_WindowID, @c API_DoorID, @c API_CutPlaneID, @c API_ElevationID, @c API_InteriorElevationID, @c API_ChangeMarkerID, @c API_DetailID, @c API_WorksheetID, @c API_CurtainWallID, @c API_CurtainWallPanelID, @c API_CurtainWallFrameID, @c API_CurtainWallJunctionID, @c API_CurtainWallAccessoryID, @c API_StairID or @c API_ExternalElemID.
 * @param memo [in][ Contains the special parameters to which you would like to change the defaults.
 * @param mask [in] Contains a mask that specifies which parameters you would like to change. The memo fields are always used when they contain valid data.
 * @param nSubElems [in] The number of subelems passed (0-3)
 * @param subElems [in] Usually the first marker contains the general marker parameters to which you would like to change the defaults. If this parameter is not nullptr then the header.type must be @c API_ObjectID. The mask specifies which parameters of the marker you would like to change. These fields are always used when they contain valid data. The second marker element is the Story Handle Marker where applicable. The third marker element is the common marker of the interior elevation element.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed element parameter is nullptr.
 * 			- APIERR_BADID - The element type should be @c API_WindowID, @c API_DoorID, @c API_CutPlaneID, @c API_ElevationID, @c API_InteriorElevationID, @c API_ChangeMarkerID, @c API_DetailID, @c API_WorksheetID, @c API_CurtainWallID, @c API_CurtainWallPanelID, @c API_CurtainWallFrameID, @c API_CurtainWallJunctionID, @c API_CurtainWallAccessoryID, @c API_StairID or @c API_ExternalElemID.
 * 			- APIERR_MEMFULL - Not enough memory to complete the operation.
 * @remarks This function is used to change the actual default settings for a Window, Door, Section, Elevation, Interior elevation, ChangeMarker, Detail or Worksheet element type, as an alternative of @ref ACAPI_Element_ChangeDefaults.
 * 			The marker parameters are optional, pass nullptr to keep them unchanged. For the detailed interpretation of the parameters refer to the @ref ACAPI_Element_ChangeExt function.
 * 			Only those parameters are changed where the corresponding field in the mask is not 0. The requested type is identified by the type field of the header.
 * 			The memo parameter is used only in the case of @c API_WindowID and @c API_DoorID. For library part-based elements, if memo is set to nullptr, the default parameters of the originating library part are used, otherwise the values are taken from the params field of memo.
 * 			To retrieve the actual settings defaults use the @ref ACAPI_Element_GetDefaultsExt function.
 * 			Only those parameters are required to fill in the element argument, which are marked to be changed. There are macros to set up the mask values correctly. They are:
 * 			|Mask function|Behavior|
 * 			|--- |--- |
 * 			|ACAPI_ELEMENT_MASK_CLEAR|Clear all the flags in the mask|
 * 			|ACAPI_ELEMENT_MASK_SETFULL|Set all the flags in the mask|
 * 			|ACAPI_ELEMENT_MASK_SET|Set only one flag in the mask according to one element parameter|
 * 			|ACAPI_ELEMENT_MASK_CHECK|Check the mask for one element parameter|
 * 			Remember to call @ref ACAPI_DisposeElemMemoHdls to dispose of the passed handles.
 */
__APIEXPORT GSErrCode ACAPI_Element_ChangeDefaultsExt (API_Element			*element,
																		 API_ElementMemo		*memo,
																		 const API_Element		*mask,
																		 UInt32					nSubElems,
																		 API_SubElement			*subElems);


/**
 * @brief Returns an array of guids of the elements of the given type.
 * @ingroup Element
 * @since Archicad 26
 * @param type [in] Element type identifier
 * @param elemList [out] List of element Guids collected by the function
 * @param filterBits [in] The flags used for filtering (see @ref ACAPI_Element_Filter). The default value is @c APIFilt_None.
 * @param renovationFilterGuid [in] Optional global unique identifier of the renovation filter. Used in combination with @c APIFilt_IsVisibleByRenovation. The default value is APINULLGuid.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The elemList pointer is nullptr.
 * @remarks This function can be used to iterate through elements of the given type and variation, that match the criteria defined by filterbits (see the filterbits flag values described in the table of @ref ACAPI_Element_Filter).
 * 			You may pass @c API_ZombieElemID as type in order to retrieve all the elements regardless of type.
 * 			The variationID member in type is used in combination with @c APIFilt_IsOfVariation
 * 			From version 26 the typeID and variationID parameters were merged into a single @ref API_ElemType parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetElemList-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetElemList (const API_ElemType&	type,
																   GS::Array<API_Guid>*	elemList,
																   API_ElemFilterFlags	filterBits = APIFilt_None,
																   const API_Guid&		renovationFilterGuid = APINULLGuid);


/**
 * @brief Returns a list of elements connected to the given element.
 * @ingroup Grouping
 * @since Archicad 26
 * @param guid [in] Identifier of the element having other elements connected to it.
 * @param connectedElemType [in] The type of the connected elements to be retrieved. Currently applicable types: @c API_WindowID, @c API_DoorID (with Wall elements), @c API_SkylightID (with Roof and Shell elements), @c API_LabelID (with all labelable elements, i.e. modeling elements, Curtain Wall subelements, and Fill elements), @c API_OpeningID
 * @param connectedElements [out] Guid list of the connected elements retrieved.
 * @param filterBits [in] The flags used for filtering (see @ref ACAPI_Element_Filter). The default value is @c APIFilt_None.
 * @param renovationFilterGuid [in] Optional global unique identifier of the renovation filter. This parameter is currently ignored.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The connectedElements pointer is nullptr.
 * 			- APIERR_BADID - The guid parameter does not identify a valid element. Or the given element type cannot be in connection with elements of the requested type.
 * @remarks This function can be used to get the elements of the given type and variation, that are connected in an ownership relation with a given element, and match the criteria defined by filterbits (see the filterbits flag values described in the table of @ref ACAPI_Element_Filter).
 * 			Available connections:
 * 			| Type of the owner element (specified with guid) | Connected element type (connectedElemTypeID) |
 * 			|----|----|
 * 			| @c API_WallID | @c API_WindowID, @c API_DoorID |
 * 			| @c API_RoofID, @c API_ShellID | @c API_SkylightID |
 * 			| All labelable elements | @c API_LabelID |
 * 			| @c API_OpeningID | @c API_WallID, @c API_SlabID, @c API_MeshID, @c API_BeamID |
 * 			The windows and doors of a given wall element can also be retrieved with the @ref ACAPI_Element_GetMemo function (wallWindows, wallDoors members of @ref API_ElementMemo).
 * 			When querying the Labels of an element, if the returned GUID array is not empty, the first GUID will be the GUID of the "Listing Label". It is the Label, which can be listed in Interactive Schedule.
 * 			From version 26 the connectedElemTypeID and variationID parameters were merged into a single @ref API_ElemType parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Grouping_GetConnectedElements-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Grouping_GetConnectedElements (const API_Guid&			guid,
																			const API_ElemType&		connectedElemType,
																			GS::Array<API_Guid>*	connectedElements,
																			API_ElemFilterFlags		filterBits = APIFilt_None,
																			const API_Guid&			renovationFilterGuid = APINULLGuid);


/**
 * @brief Tests an element by some given criteria.
 * @ingroup Element
 * @param guid [in] Global unique identifier of the element to be tested
 * @param filterBits [in] The flags used for filtering (see the table below)
 * @param variationID [in] Optional variation ID for objects. Used in combination with @c APIFilt_IsOfVariation. The default value is @c APIVarId_Generic.
 * @param renovationFilterGuid [in] Optional global unique identifier of the renovation filter. Used in combination with @c APIFilt_IsVisibleByRenovation. The default value is APINULLGuid.
 * @return
 * 			- true - The given element (defined by guid) matches the criteria defined by filterbits
 * 			- false - The referenced element does not pass the criteria
 * @remarks Note that the 3D visibility of GDL-based elements can also be modified through GDL parameters which work independently from the element settings. Due to this there may be cases where the @ref ACAPI_Element_Filter function shows that an elem is visible on 3D, but its GDL script hides it on 3D-based views.
 * 			Returns true, if the given element matches the criteria defined by filterbits :
 * 			|filterbits value | Checks whether the element | Concerned elements|
 * 			|-------------|---------------------|------------------------------|
 * 			|@c APIFilt_None | not filtered | |
 * 			|@c APIFilt_IsEditable | is not on a locked/deleted/invisible layer | all (for windows, doors and skylights this tests the layer of the owner element)|
 * 			|@c APIFilt_OnVisLayer | is on a visible layer | all (for windows, doors and skylights this tests the layer of the owner element)|
 * 			|@c APIFilt_OnActFloor | is on the active floor | all (always true for cut planes and groups)|
 * 			|@c APIFilt_In3D | has 3D representation | @c API_WallID, @c API_ColumnID, @c API_BeamID, @c API_WindowID, @c API_DoorID, @c API_SkylightID, @c API_ObjectID, @c API_LampID, @c API_SlabID, @c API_RoofID, @c API_MeshID, @c API_ShellID, @c API_CurtainWallID, @c API_MorphID|
 * 			|@c APIFilt_InMyWorkspace | is in my workspace (in Teamwork mode) | all element types|
 * 			|@c APIFilt_IsIndependent | is independent (not a sub elem) | @c API_ObjectID, @c API_TextID|
 * 			|@c APIFilt_OnActLayout | is on the active layout | drawing type elements|
 * 			|@c APIFilt_InCroppedView | is visible inside the cropped part of a drawing database | drawing type elements|
 * 			|@c APIFilt_IsOfVariation | tells if the given element has the variation ID passed in the variationID parameter. | object type elements|
 * 			|@c APIFilt_FromFloorplan | additional flag; instructs the function to take the element from the floor plan database | all element types|
 * 			|@c APIFilt_HasAccessRight | additional flag; checks if the element is accessible for the current user | all element types|
 * 			|@c APIFilt_IsVisibleByRenovation | additional flag; checks if the element is visible by the renovation filter passed in the renovationFilterGuid parameter, default by the current renovation filter. | all element types|
 * 			|@c APIFilt_IsOverriddenByRenovation | additional flag; checks if the attributes of the element are overridden by current renovation filter | all element types|
 * 			|@c APIFilt_IsInStructureDisplay | additional flag; checks if the element is visible taking into account the current structure display setting | all element types|
 * 			If the value of filterBits is 0, only the existence of the element is checked.
 * 			This routine helps you quickly test different attributes without converting the whole model, for example when you walk through all the elements, and test for the existence of the 3D representation of an element.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_Filter-Example-Snippet
 */
__APIEXPORT bool ACAPI_Element_Filter (const API_Guid&		guid,
															  API_ElemFilterFlags	filterBits,
															  API_ElemVariationID	variationID = APIVarId_Generic,
															  const API_Guid&		renovationFilterGuid = APINULLGuid);


/**
 * @brief Returns information on the main parameters of a given element.
 * @ingroup Element
 * @param element [in/out] The element participating in the operation.
 * @param mask [in] Optional mask. Currently valid values are 0 and @c APIElemMask_FloorPlan. In the latter case, the elements in the floor plan database are counted directly, without changing the database first.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter is nullptr; element
 * 			- APIERR_BADID - The element reference is invalid (guid). The element type is invalid, or the element type is not supported by the server application
 * 			- APIERR_DELETED - The element does not exist in the database
 * @remarks This function returns information on the main parameters of a given element in the @ref API_Element structure, which is a union of the different element structures.
 * 			There is only one way (from API 18 or later) to identify the element:
 * 			- pass the guid of the element in the element header.
 * 			The information returned is the main data of the element; further information can be obtained with the @ref ACAPI_Element_GetMemo function, where applicable; the hasMemo field of the header indicates the existence of the extra information.
 * 			Please use filtering with the @ref ACAPI_Element_Filter function before calling this function; in this case you can spare the conversion time in certain cases.
 * 			Please note that the attributes referenced by the element may be invalid. The layer attribute is the only one, which must exist. Other type of attributes my be deleted without editing the element database, it results that elements may refer missing attributes. In this case the @ref ACAPI_Attribute_Get function returns an error code.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_Get-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_Get (API_Element *element,
														   UInt32		mask = 0);


/**
 * @brief Returns general information on the given element.
 * @ingroup Element
 * @param elementHead [in/out] On input, it identifies the element based on its GUID. On return, the other fields are filled.
 * @param mask [in] Optional mask. Currently valid values are 0 and @c APIElemMask_FloorPlan. In the latter case, the elements in the floor plan database are counted directly, without changing the database first.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This is a fast version of @ref ACAPI_Element_Get, where only the fields of the header are returned. There are many cases when you only need information (e.g. layer, story) contained in the element header, but in the past the server application had to convert the whole element.
 */
__APIEXPORT GSErrCode ACAPI_Element_GetHeader (API_Elem_Head *elementHead,
																 UInt32			mask = 0);


/**
 * @brief Retrieves all additional information attached to elements.
 * @ingroup Element
 * @since Archicad 25
 * @param guid [in] Guid of the element.
 * @param memo [out] Pointer to the memo to be filled.
 * @param mask [in] Specifies which part of the memo you are interested in.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed memo parameter is nullptr
 * 			- APIERR_BADID - The element type is invalid, or the element type is not supported by the server application
 * 			- APIERR_BADID - The element guid is invalid.
 * 			- APIERR_DELETED - The element does not exist in the database
 * 			- APIERR_MEMFULL - not enough memory to complete the operation
 * @remarks This function returns additional information attached to elements. This doesn't apply to all the drawing elements; you can check the hasMemo field of the element header.
 * 			The following table shows which elements may have additional data attached; it also explains what information is returned in @ref API_ElementMemo.
 * 			| Value | Parameters | Function |
 * 			|-------|------------|--------------|
 * 			| @c API_WallID | (API_Gable **) gables <br>(API_Coord **) coords <br>(Int32 **) pends <br>(API_PolyArc **) parcs <br>(UInt32 **) vertexIDs <br>(ProfileVectorImage*) customOrigProfile <br>(ProfileVectorImage*) stretchedProfile <br>(API_Guid **) wallWindows <br>(API_Guid **) wallDoors | Returns the gable <sup>@ref acapielementmemofnt1 "1"</sup> and the polygon data <sup>@ref acapielementmemofnt2 "2"</sup> and the vector image data of the complex cross-section profile <sup>@ref acapielementmemofnt5 "5"</sup>. May also return the windows and doors in this wall. |
 * 			| @c API_ColumnID | (API_Gable **) gables <br>(ProfileVectorImage*) customOrigProfile <br>(ProfileVectorImage*) stretchedProfile <br>(API_ColumnSegmentType*) columnSegments <br>(API_AssemblySegmentCutData*)		assemblySegmentCuts <br>(API_AssemblySegmentSchemeData*)	assemblySegmentSchemes <br>(API_AssemblySegmentProfileData*) assemblySegmentProfiles | Returns the gable data <sup>@ref acapielementmemofnt1 "1"</sup>, the vector image data of the complex cross-section profile <sup>@ref acapielementmemofnt5 "5"</sup> and segment related information. |
 * 			| @c API_BeamID | (API_Gable **) gables <br>(API_Beam_Hole **) beamHoles <br>(ProfileVectorImage*) customOrigProfile <br>(ProfileVectorImage*) stretchedProfile <br>(API_BeamSegmentType*) beamSegments <br>(API_AssemblySegmentCutData*)		assemblySegmentCuts <br>(API_AssemblySegmentSchemeData*)	assemblySegmentSchemes <br>(API_AssemblySegmentProfileData*) assemblySegmentProfiles | Returns the gable data <sup>@ref acapielementmemofnt1 "1"</sup>, the vector image data of the complex cross-section profile <sup>@ref acapielementmemofnt5 "5"</sup>, the holes of the beam, and segment related information. |
 * 			| @c API_WindowID @c API_DoorID | (API_Gable **) gables <br>(char **) textContent <br>(API_AddParType **) params | Returns the gable data <sup>@ref acapielementmemofnt1 "1"</sup> and the parameters of the instance of a library part <sup>@ref acapielementmemofnt4 "4"</sup>, also the window / door orientation text in textContent. |
 * 			| @c API_ObjectID @c API_LampID | (API_Gable **) gables <br>(API_AddParType **) params | Returns the gable data <sup>@ref acapielementmemofnt1 "1"</sup> and the parameters of the instance of a library part <sup>@ref acapielementmemofnt4 "4"</sup> |
 * 			| @c API_SkylightID | (API_AddParType **) params | Returns the parameters of the instance of a library part <sup>@ref acapielementmemofnt4 "4"</sup> |
 * 			| @c API_SlabID | (API_Coord **) coords <br>(Int32 **) pends <br>(API_PolyArc **) parcs <br>(UInt32 **) vertexIDs <br>(UInt32 **) edgeIDs <br>(UInt32 **) contourIDs <br>(API_EdgeTrim **) edgeTrims <br>(API_OverriddenAttribute *) sideMaterials | Returns the polygon <sup>@ref acapielementmemofnt2 "2"</sup>, the edge trim data <sup>@ref acapielementmemofnt3 "3"</sup> and the side materials <sup>@ref acapielementmemofnt6 "6"</sup> of the slab. |
 * 			| @c API_RoofID | (API_Coord **) coords <br>(Int32 **) pends <br>(API_PolyArc **) parcs <br>(UInt32 **) vertexIDs <br>(API_EdgeTrim **) edgeTrims <br>(API_RoofEdgeTypeID *) roofEdgeTypes <br>(API_OverriddenAttribute *) sideMaterials <br>(API_Coord **) pivotPolyCoords <br>(Int32 **) pivotPolyPends <br>(API_PolyArc **) pivotPolyParcs <br>(UInt32 ** *) pivotPolyVertexIDs <br>(API_PivotPolyEdgeData *) pivotPolyEdges | - @c API_PlaneRoofID: Returns the polygon <sup>@ref acapielementmemofnt2 "2"</sup>, the edge trim data <sup>@ref acapielementmemofnt3 "3"</sup> and the side materials <sup>@ref acapielementmemofnt6 "6"</sup> of the roof.<br> - @c API_PolyRoofID: Returns the contour and pivot polygons <sup>@ref acapielementmemofnt2 "2"</sup>, the edge trim data <sup>@ref acapielementmemofnt3 "3"</sup>, the side materials <sup>@ref acapielementmemofnt6 "6"</sup> and the data of the pivot polygon edges <sup>@ref acapielementmemofnt9 "9"</sup> of the roof.
 * 			| @c API_MeshID | (API_Coord **) coords <br>(Int32 **) pends <br>(API_PolyArc **) parcs <br>(UInt32 **) vertexIDs <br>(double **) meshPolyZ <br>(API_MeshLevelCoord **) meshLevelCoords <br>(Int32 **) meshLevelEnds | Returns the polygon <sup>@ref acapielementmemofnt2 "2"</sup> of the mesh, and the level lines |
 * 			| @c API_ShellID | @ref API_ShellShapeData shellShapes[2] <br>(API_ShellContourData*) shellContours | Returns the profile shape polygon(s) <sup>@ref acapielementmemofnt7 "7"</sup> and the clipping and hole contour data <sup>@ref acapielementmemofnt8 "8"</sup> of the shell |
 * 			| @c API_MorphID | (Modeler::Body*) morphBody <br>(API_OverriddenAttribute*) morphMaterialMapTable | Returns the body and the material override map table of the morph |
 * 			| @c API_DimensionID | (API_DimElem **) dimElems | Returns the coordinates, the neig information, the text, and the witness line information of the dimension |
 * 			| @c API_LabelID | (char **) textContent <br>(short **) textLineStarts <br>(API_ParagraphType **) paragraphs <br>(API_AddParType **) params | Returns the text and its style for text-type labels, or the parameters of the originating library part for symbol labels. |
 * 			| @c API_SplineID | (API_Coord **) coords <br>(API_SplineDir **) bezierDirs | Returns the Bezier curve parameters |
 * 			| @c API_TextID | (char **) textContent <br>(short **) textLineStarts <br>(API_ParagraphType **) paragraphs | Returns the content the line starts <br>(offsets into textContent) and the style informations of the text. The content can be either in UTF-8 or UTF-16 encoding, depending on the text element's charCode member and the memo mask. |
 * 			| @c API_HatchID | (API_Coord **) coords <br>(Int32 **) pends <br>(API_PolyArc **) parcs <br>(UInt32 **) vertexIDs | Returns the polygon of the hatch |
 * 			| @c API_ZoneID | (API_Gable **) gables <br>(API_Coord **) coords <br>(Int32 **) pends <br>(API_PolyArc **) parcs <br>(API_AddParType **) params | Returns the polygon of the room <sup>@ref acapielementmemofnt2 "2"</sup> |
 * 			| @c API_CameraID | (API_LinkType **) linkList | Returns the data of the camera |
 * 			| @c API_CutPlaneID | (API_Coord **) sectionSegmentMainCoords <br>(API_Coord **) sectionSegmentDistCoords <br>(API_Coord **) sectionSegmentDepthCoords | Returns the coordinates of the main, amrked distant area, and depth line of the section segment. |
 * 			| @c API_ElevationID | (API_Coord **) sectionSegmentMainCoords <br>(API_Coord **) sectionSegmentDistCoords <br>(API_Coord **) sectionSegmentDepthCoords | Returns the coordinates of the main, amrked distant area, and depth line of the section segment. |
 * 			| @c API_InteriorElevationID | (API_SectionSegment **) intElevSegments <br>(API_Coord **) sectionSegmentMainCoords <br>(API_Coord **) sectionSegmentDistCoords <br>(API_Coord **) sectionSegmentDepthCoord <br>(API_AddParType **) params | Returns the coordinates of the main, amrked distant area, and depth line of the section segment, and also the parameters of the common marker. |
 * 			| @c API_ChangeMarkerID | (API_Coord **) coords <br>(Int32 **) pends <br>(API_PolyArc **) parcs | Returns the polygon of the ChangeMarker <sup>@ref acapielementmemofnt2 "2"</sup>, if it has a polygon. |
 * 			| @c API_DetailID @c API_WorksheetID | (API_Coord **) coords <br>(Int32 **) pends <br>(API_PolyArc **) parcs | Returns the polygon of the detail or worksheet <sup>@ref acapielementmemofnt2 "2"</sup> |
 * 			| @c API_PolyLineID | (API_Coord **) coords <br>(Int32 **) pends <br>(API_PolyArc **) parcs | Returns the polygon of the polyline <sup>@ref acapielementmemofnt2 "2"</sup> |
 * 			| @c API_PictureID | (char **) pictHdl | Returns the picture |
 * 			| @c API_DrawingID | (API_Coord **) coords <br>(Int32 **) pends <br>(API_PolyArc **) parcs <br>(GSPtr) drawingData | Returns the polygon and drawing data of a drawing element |
 * 			| @c API_CurtainWallID | (API_Coord **) coords <br>(Int32 **) pends <br>(API_PolyArc **) parcs <br>(UInt32 **) vertexIDs <br>(API_CWSegmentPatternData) cWSegPrimaryPattern <br>(API_CWSegmentPatternData) cWSegSecondaryPattern <br>(API_CWSegmentPatternCellData*) cWSegPatternCells <br>(API_CWSegmentType*) cWallSegments <br>(API_CWFrameType*) cWallFrames <br>(API_CWFrameType*) cWallFrameDefaults <br>(API_CWPanelType*) cWallPanels <br>(API_CWPanelGridIDTable*) cWallPanelGridIDTable <br>(API_CWPanelType*) cWallPanelDefaults <br>(API_CWPanelType*) cWallPanelDefaultSymbs <br>(API_CWJunctionType*) cWallJunctions <br>(API_CWAccessoryType*) cWallAccessories | Returns the polygon and all CW related data. @c cWSegPrimaryPattern, @c cWSegSecondaryPattern and @c cWSegPatternCells members will contain the default segment scheme of the curtain wall. |
 * 			| @c API_CurtainWallSegmentID | (API_GridMesh*) cWSegGridMesh <br>(API_CWContourData*) cWSegContour <br>(API_CWSegmentPatternData) cWSegPrimaryPattern <br>(API_CWSegmentPatternData) cWSegSecondaryPattern <br>(API_CWSegmentPatternCellData*) cWSegPatternCells | Returns the CW segment related data. |
 * 			| @c API_CurtainWallPanelID | (API_Coord **) coords | Returns the coordinates of the panel's polygon. Please note that a curtain wall panel cannot contain holes. |
 * 			| @c API_StairID | (API_StairRiserType*) stairRisers <br>(API_StairTreadType*) stairTreads <br>(API_StairStructureType*) stairStructures <br>(API_StairBoundaryData[2]) stairBoundary | Returns the Stair related data. |
 * 			| @c API_RailingID | (API_Coord **) coords <br>(Int32 **) pends <br>(API_PolyArc **) parcs <br>(API_RailingNodeType*) railingNodes <br>(API_RailingSegmentType*) railingSegments <br>(API_RailingPostType*) railingPosts <br>(API_RailingRailEndType*) railingRailEnds <br>(API_RailingRailEndType*) railingHandrailEnds <br>(API_RailingRailEndType*) railingToprailEnds <br>(API_RailingRailConnectionType*) railingRailConnections <br>(API_RailingRailConnectionType*) railingHandrailConnections <br>(API_RailingRailConnectionType*) railingToprailConnections <br>(API_RailingRailType*) railingRails <br>(API_RailingToprailType*) railingToprails <br>(API_RailingHandrailType*) railingHandrails <br>(API_RailingPatternType*) railingPatterns <br>(API_RailingInnerPostType*) railingInnerPosts <br>(API_RailingPanelType*) railingPanels <br>(API_RailingBalusterSetType*) railingBalusterSets <br>(API_RailingBalusterType*) railingBalusters <br>(double**) polyZCoords; | Returns the Railing related data. |
 * 			| @c API_ExternalElemID | (API_AddParType **) params | Returns the parameters of the instance of a library part <sup>@ref acapielementmemofnt4 "4"</sup> |
 * 			<br> @anchor acapielementmemofnt1 <sup>1</sup> Any number of gables can be present.
 * 			<br> @anchor acapielementmemofnt2 <sup>2</sup> See the description of @ref API_Polygon.
 * 			<br> @anchor acapielementmemofnt3 <sup>3</sup> The length of the @ref API_EdgeTrim memo handle is (poly.nCoords+1)*sizeof(API_EdgeTrim) ; the first and the last record are not used, filled with zero.
 * 			<br> @anchor acapielementmemofnt4 <sup>4</sup> The parameters of an element are the parameters of its originating library part, their values are taken from the actual instance.
 * 			<br> @anchor acapielementmemofnt5 <sup>5</sup> The drawing primitives of the complex profile are stored in a serialized @c HGX::VectorImage.
 * 			<br> @anchor acapielementmemofnt6 <sup>6</sup> The length of the sideMaterials memo array is (poly.nCoords+1)*sizeof(API_OverriddenAttribute) ; the first and the last record are not used, filled with zero.
 * 			<br> @anchor acapielementmemofnt7 <sup>7</sup> Fixed size array of two @ref API_ShellShapeData records. The members of @ref API_ShellShapeData are handled similarly to the members of @ref API_Polygon.
 * 			<br> @anchor acapielementmemofnt8 <sup>8</sup> The number of @ref API_ShellContourData records in the shellContours memo array can be calculated from the @ref API_ShellType parameters: numHoles+(hasContour?1:0).
 * 			<br> @anchor acapielementmemofnt9 <sup>9</sup> The length of the pivotPolyEdges memo array is (pivotPolygon.nCoords+1)*sizeof(API_PivotPolyEdgeData); the first and the last record are not used, filled with zero.
 * 			For improving performance you can select which data is needed with the mask parameter. This feature provides filtered access to the attached data; instead of converting all the attached data, the function returns only those which are in interest.
 * 			The possible values of the mask are:
 * 			| Mask | Meaning |
 * 			|------|---------|
 * 			| @c APIMemoMask_Polygon	| Returns the polygon for polygonal elements. For more information see @ref API_Polygon. |
 * 			| @c APIMemoMask_Gables	| Returns the gable information. |
 * 			| @c APIMemoMask_AddPars	| Returns the additional parameters of a library part-based element (object, lamp, door, window, zone stamp, label). |
 * 			| @c APIMemoMask_EdgeTrims |Returns the edge trim information for roofs and slabs. (Renamed from @c APIMemoMask_RoofSide.) |
 * 			| @c APIMemoMask_MeshPolyZ	| Returns Z coordinates of the mesh points for meshes. |
 * 			| @c APIMemoMask_MeshLevel	| Returns the mesh level information for meshes. |
 * 			| @c APIMemoMask_BeamHole	| Returns the hole information for beams. |
 * 			| @c APIMemoMask_TextContent	|Returns the content as ANSI string for textual elements (Text, Label). (This is the default.) |
 * 			| @c APIMemoMask_Paragraph	|Returns paragraph informations for textual elements (Text, Label). The paragraphs handle contains byte offsets. Use with @c APIMemoMask_TextContent mask. (This is the default.) |
 * 			| @c APIMemoMask_TextContentUni	| Returns the content as UniCode string for textual elements (Text, Label). You should cast the textContent handle to unsigned short ** |
 * 			| @c APIMemoMask_ParagraphUni	|Returns paragraph informations for textual elements (Text, Label). The paragraphs handle contains character offsets. Use with @c APIMemoMask_TextContentUni mask. |
 * 			| @c APIMemoMask_DrawingData |Returns the drawing data of a drawing element (API_DrawingType) in internal format. See also @ref ACAPI_Drawing_StopDrawingData. |
 * 			| @c APIMemoMask_CustomOrigProfile |Returns the original custom profile data applied to the wall, beam, or column element. |
 * 			| @c APIMemoMask_StretchedProfile |Returns the stretched profile actually used by the wall, beam, or column element. |
 * 			| @c APIMemoMask_SectionSegments |Returns the section segments of a section, elevation, or interior elevation element. |
 * 			| @c APIMemoMask_SectionMainCoords |Returns the section view line coordinates of a section, elevation, or interior elevation element. |
 * 			| @c APIMemoMask_SectionDistCoords |Returns the section marked distant area line coordinates of a section, elevation, or interior elevation element. |
 * 			| @c APIMemoMask_SectionDepthCoords |Returns the section depth line coordinates of a section, elevation, or interior elevation element. |
 * 			| @c APIMemoMask_WallWindows |Returns the Guid list of the windows placed in a given wall element. |
 * 			| @c APIMemoMask_WallDoors |Returns the Guid list of the doors placed in a given wall element. |
 * 			| @c APIMemoMask_CWSegGridMesh |Returns the GridMesh of a curtain wall segment. |
 * 			| @c APIMemoMask_CWSegPrimaryPattern |Returns the primary pattern of a curtain wall segment. |
 * 			| @c APIMemoMask_CWSegSecPattern |Returns the secondary pattern of a curtain wall segment. |
 * 			| @c APIMemoMask_CWSegPanelPattern |Returns the panel pattern of curtain wall segment. |
 * 			| @c APIMemoMask_CWSegContour |Returns the contour of curtain wall segment. |
 * 			| @c APIMemoMask_CWallSegments |Returns the segments of curtain wall element. |
 * 			| @c APIMemoMask_CWallFrames |Returns the frames of curtain wall element. |
 * 			| @c APIMemoMask_CWallPanels |Returns the panels of curtain wall element. |
 * 			| @c APIMemoMask_CWallJunctions |Returns the junctions of curtain wall element. |
 * 			| @c APIMemoMask_CWallAccessories |Returns the accessories of curtain wall element. |
 * 			| @c APIMemoMask_FromFloorPlan |Additional flag; take the element information from the floor plan database. This flag is excluded from @c APIMemoMask_All! |
 * 			| @c APIMemoMask_RoofEdgeTypes |Returns the edge types of the contour polygon of a roof element. |
 * 			| @c APIMemoMask_SideMaterials |Returns the side material indices of a Slab or Roof element. |
 * 			| @c APIMemoMask_PivotPolygon |Returns the pivot polygon and the pivot edges of a Multi-plane Roof element (see @ref API_PolyRoofData). |
 * 			| @c APIMemoMask_StairRiser |Returns the Riser subelements of a Stair element. |
 * 			| @c APIMemoMask_StairTread |Returns the Tread subelements of a Stair element. |
 * 			| @c APIMemoMask_StairStructure |Returns the Stair Structure subelements of a Stair element. |
 * 			| @c APIMemoMask_RailingNode |Returns the Nodes of a Railing element. |
 * 			| @c APIMemoMask_RailingSegment |Returns the Segments of a Railing element. |
 * 			| @c APIMemoMask_RailingPost |Returns the Railing Posts of a Railing element. |
 * 			| @c APIMemoMask_RailingInnerPost |Returns the Inner Posts of a Railing element. |
 * 			| @c APIMemoMask_RailingRail |Returns the Rails of a Railing element. |
 * 			| @c APIMemoMask_RailingHandrail |Returns the Handrails of a Railing element. |
 * 			| @c APIMemoMask_RailingToprail |Returns the Toprails of a Railing element. |
 * 			| @c APIMemoMask_RailingPanel |Returns the Railing Panels of a Railing element. |
 * 			| @c APIMemoMask_RailingBaluster |Returns the Balusters of a Railing element. |
 * 			| @c APIMemoMask_RailingPattern |Returns the Railing Patterns of a Railing element. |
 * 			| @c APIMemoMask_RailingBalusterSet |Returns the Baluster Sets of a Railing element. |
 * 			| @c APIMemoMask_RailingRailEnd |Returns the Rail Ends of a Railing Node element. |
 * 			| @c APIMemoMask_RailingRailConnection |Returns the Rail Connections of a Railing Node element. |
 * 			| @c APIMemoMask_BeamSegment |Returns the Beam segments of a Beam element. |
 * 			| @c APIMemoMask_ColumnSegment |Returns the Column segments of a Column element. |
 * 			| @c APIMemoMask_AssemblySegmentCut |Returns cuts of a Column or a Beam element. |
 * 			| @c APIMemoMask_AssemblySegmentScheme |Returns schemes of ColumnSegments or BeamSegments. |
 * 			| @c APIMemoMask_AssemblySegmentProfile |Returns profiles of ColumnSegments or BeamSegments. |
 * 			| @c APIMemoMask_SurfaceLoadCustomData |Returns the contour of the Custom Surface Load |
 * 			| @c APIMemoMask_All |Returns all the applicable fields for the element. |
 *
 * 			Do not forget to call @ref ACAPI_DisposeElemMemoHdls to dispose of the handles when you're finished.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetMemo-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetMemo	(const API_Guid&			guid,
																 API_ElementMemo*			memo,
																 UInt64						mask = APIMemoMask_All);


/**
 * @brief @brief Retrieves all additional information of the sub elements of an external hierarchical element.
 * @ingroup Element
 * @since Archicad 27
 * @param guid [in] Guid of the external hierarchical element.
 * @param subElems [out] The subelem(s) of the desired element.
 * @param mask [in] Specifies which part of the memo you are interested in.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The element type is invalid, or the element type is not supported by the server application
 * 			- APIERR_BADID - The element guid is invalid.
 * 			- APIERR_DELETED - The element does not exist in the database
 * 			- APIERR_MEMFULL - not enough memory to complete the operation
 */
__APIEXPORT GSErrCode					ACAPI_Element_GetMemo_ExternalHierarchical (const API_Guid&					guid,
																					std::vector<API_SubElement>&	subElems,
																					UInt64							mask = APIMemoMask_All);

/**
 * @brief Changes the memo part of certain element types.
 * @ingroup Element
 * @param guid [in] Guid of the element.
 * @param mask [in] Specifies which part of a memo should be changed. Currently only @c APIMemoMask_Polygon is supported.
 * @param memo [in] The replacement memo. Don't forget to dispose of it with @ref ACAPI_DisposeElemMemoHdls when you are done.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - You called the function for element types other then slabs or roofs.
 * 			- APIERR_BADPARS - You called the function with a mask value other than @c APIMemoMask_Polygon, or you specified wrong parameters.
 * @remarks This function is used to change the memo part of certain element types. Currently you can change only the polygon data of polygonal elements. It is recommended to use the @ref ACAPI_Element_Change function instead.
 */
__APIEXPORT GSErrCode ACAPI_Element_ChangeMemo (API_Guid&				guid,
																  UInt64				mask,
											   					  const API_ElementMemo	*memo);


/**
 * @brief Returns information on objects connected to walls, beams, beam segments, rooms, shells, roofs, curtain wall panels, skylights, windows and doors.
 * @ingroup Element
 * @since Archicad 26
 * @param guid [in] Guid of the element.
 * @param otherType [in] Type of the requested element.
 * @param relData [out] The relation data returned by the function. This pointer must refer to an @ref API_WallRelation, @ref API_BeamRelation, @ref API_BeamSegmentRelation, @ref API_RoomRelation, @ref API_RoofRelation, @ref API_ShellRelation, @ref API_SkylightRelation, @ref API_WindowRelation, or an @ref API_DoorRelation structure according to the type of the requested element given be the guid parameter.
 * @param mask [in] Optional mask. Currently valid values are 0 and @c APIElemMask_FromFloorplan. In the latter case, the element referred by guid is searched in the floor plan database.
 * @return
 * 			- NoError - The operation was successful.
 * 			- APIERR_BADPARS - The relData parameter was nullptr or otherID parameter is incorrect.
 * 			- APIERR_BADID - Incorrect guid was specified.
 * 			- APIERR_DELETED - The element does not exist in the database
 * @remarks This function returns information on elements connected to the element identified by the given guid. The requested object type is given in otherType.
 * 			|Type of the given element | otherID | Comment|
 * 			|--------------------------|---------|--------|
 * 			| walls | @c API_ZombieElemID, @c API_WallID | For walls the connected elements and the modified polygon is put into relData. Positive indices mean that the begin point of the other object is connected to the wall; while negative indices mean the end point. Five types of connections are returned: walls which are connected to the begin point, to the end point and to the reference line of the wall, walls to the reference line of whose the wall you requested information on is connected, and cross connections.|
 * 			| rooms | @c API_ZombieElemID, @c API_WallID, @c API_ColumnID, @c API_ObjectID, @c API_LampID, @c API_WindowID @c API_DoorID, @c API_BeamID, @c API_CurtainWallID, @c API_CurtainWallFrameID, @c API_CurtainWallPanelID, @c API_CurtainWallJunctionID, @c API_CurtainWallAccessoryID, @c API_CurtainWallSegmentID, @c API_SkylightID, @c API_RoofID, @c API_ShellID, @c API_MorphID, @c API_StairID, @c API_RiserID, @c API_TreadID, @c API_StairStructureID, @c API_RailingID, @c API_RailingToprailID, @c API_RailingHandrailID, @c API_RailingRailID, @c API_RailingPostID, @c API_RailingInnerPostID, @c API_RailingBalusterID, @c API_RailingPanelID, @c API_RailingSegmentID, @c API_RailingToprailEndID, @c API_RailingHandrailEndID, @c API_RailingRailEndID, @c API_RailingToprailConnectionID, @c API_RailingHandrailConnectionID, @c API_RailingRailConnectionID, @c API_RailingNodeID or @c API_SlabID | For rooms, the walls, columns, objects, lamps, windows, doors, beams, curtain walls, skylights, roofs, shells, morphs, stairs, risers, treads, railings and slabs are returned. For walls, beams and curtain wall segments the returned information contains that segment of the wall which is inside the room (see @ref API_WallPart / @ref API_CWSegmentPart and @ref API_BeamPart).|
 * 			| beams | @c API_ZombieElemID or @c API_BeamID | For beams the connected elements and the modified polygon is put into relData. Positive indices mean that the begin point of the other object is connected to the beam; while negative indices mean the end point. Five types of connections are returned: beams which are connected to the begin point, to the end point and to the reference line of the beam, beams to the reference line of whose the beam you requested information on is connected, and cross connections.|
 * 			| beam segments | @c API_ZombieElemID or @c API_BeamSegmentID | For beam segments the connected elements and the modified polygon is put into relData. Positive indices mean that the begin point of the other object is connected to the beam segment; while negative indices mean the end point. Five types of connections are returned: beam segments which are connected to the begin point, to the end point and to the reference line of the beam segment, beam segments to the reference line of whose the beam segment you requested information on is connected, and cross connections.|
 * 			| curtain wall panels and skylights | @c API_ZombieElemID or @c API_ZoneID | For curtain wall panels and skylights the connected rooms are put into relData.|
 * 			| windows and doors | @c API_ZombieElemID or @c API_ZoneID | For windows and doors the connected rooms are put into relData.|
 * 			| roof and shell | @c API_ZombieElemID or @c API_ZoneID | For roof and shell the connected rooms are put into rooms.|
 * 			Don't forget to call the appropriate @ref ACAPI_DisposeRoomRelationHdls, @ref ACAPI_DisposeWallRelationHdls, @ref ACAPI_DisposeBeamRelationHdls, or @ref ACAPI_DisposeBeamSegmentRelationHdls function to dispose the handles.
 * 			From version 26 the otherTypeID parameter was changed into an @ref API_ElemType parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetRelations-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetRelations (const API_Guid&		guid,
																	const API_ElemType&	otherType,
																	void*				relData,
																	UInt32				mask = 0);


/**
 * @brief Obtains the transformation parameters of an actual instance of a library part.
 * @ingroup Element
 * @param elemHead [in] Identifies the element. Its type should be @c API_WindowID, @c API_DoorID, @c API_ObjectID, @c API_LampID, or @c API_ZoneID.
 * @param syTran [out] The function returns the transformation parameters here.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The syTran parameter was nullptr.
 * 			- APIERR_BADID - The element reference is invalid; elemHead->guid.
 * 			- APIERR_DELETED - The element does not exist in the database
 * 			- APIERR_GENERAL - The element reference is invalid; elemHead->guid.
 * @remarks You can get the transformation parameters of an actual instance of a library part (type should be @c API_WindowID, @c API_DoorID, @c API_ObjectID, @c API_LampID, or @c API_ZoneID) with this function. The transformation parameters are not easy to calculate and keep up-to-date, this function helps you to obtain this information.
 */
__APIEXPORT GSErrCode ACAPI_Element_GetSyTran (const API_Elem_Head *elemHead, API_SyTran *syTran);


/**
 * @brief Retrieves the hotspots of the given element.
 * @ingroup Element
 * @param guid [in] Identifier of the element.
 * @param hotspotArray [out] Array that contains hotspots (neig and coordinate pairs).
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - hotspotArray parameter is nullptr.
 * 			- APIERR_BADID - Invalid guid.
 * @remarks This function is used to retrieve the hotspots of the given element.
 * 			The hotspots return in an array of @c API_ElementHotspot objects which contain neig and coordinate pairs (GS::Pair < @ref API_Neig, @ref API_Coord3D >).
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetHotspots-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetHotspots (const API_Guid&					guid,
																   GS::Array<API_ElementHotspot>*	hotspotArray);


/**
 * @brief Places a new element into current database.
 * @ingroup Element
 * @param element [in/out] The desired element will be created in the pointed structure. The element->header.type must specify the type of the element to be created.
 * @param memo [in] The memo field of the desired element will be created from the pointed structure (if the memo field is needed).
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE - The current database is not proper for the operation.
 * 			- APIERR_BADPARS - The passed parameter is nullptr; element
 * 			- APIERR_BADID - The element type is invalid, or the element type is not supported by the server application
 * 			- APIERR_REFUSEDPAR - The element->header.type parameter was incorrect. It might happen if you want to create something in a window not capable to display it, for example a wall in a section window.
 * 			- APIERR_INVALFLOOR - The element->header.floorInd parameter is out of range.
 * 			- APIERR_IRREGULARPOLY - Input polygon or polyline is irregular.
 * @remarks The type of the element to be created is defined by type in the element header. On return, the guid field of the header is filled in. Don't forget to call @ref ACAPI_DisposeElemMemoHdls to dispose the handles when you're done.
 * 			The meaning of the different parameters is explained in the table below:
 * 			|element->header.type | memo fields | Notes |
 * 			|---------------------|-------------|-------|
 * 			| @c API_WallID | optional/required | The gables are optional, the coords, pends, and parcs are required only for walls of type @c APIWtyp_Poly (polygon-based walls)|
 * 			| @c API_ColumnID | optional (gables, assemblySegmentProfiles) required (columnSegments, assemblySegmentCuts, assemblySegmentSchemes) | |
 * 			| @c API_BeamID | optional (gables, beam holes, assemblySegmentProfiles) required (beamSegments, assemblySegmentCuts, assemblySegmentSchemes) | |
 * 			| @c API_WindowID @c API_DoorID | required (params) | See also @ref ACAPI_Element_CreateExt.|
 * 			| @c API_SkylightID | required (params) | See also @ref ACAPI_Element_CreateExt.|
 * 			| @c API_ObjectID @c API_LampID | required | |
 * 			| @c API_SlabID | required/optional | The slab polygon is required; the edgeTrims and sideMaterials are optional.|
 * 			| @c API_RoofID | required/optional | The roof polygon is required; the edgeTrims, roofEdgeTypes and sideMaterials are optional. Besides these parameters for Multi-plane roofs the pivotPolyCoords, pivotPolyPends and pivotPolyParcs are also required; the pivotPolyEdges are optional.|
 * 			| @c API_MeshID | required/optional | The mesh polygon is required, the meshPolyZ (mesh points' Z coordinates), the meshLevelCoords (level line coordinates), and the meshLevelEnds (level lines' endpoints) fields are optional.|
 * 			| @c API_ShellID | required/optional | Shell shape data is required (first record of shellShapes for extruded and revolved shells, both records for ruled shells ; shellContours are optional.|
 * 			| @c API_MorphID | required/optional | The morphBody field is required and the morphMaterialMapTable field is optional.|
 * 			| @c API_DimensionID | required (dimension data) | |
 * 			| @c API_RadialDimensionID <br> @c API_AngleDimensionID | | |
 * 			| @c API_LevelDimensionID | | If the ceilNum is set to 0, the level dimension's reference is the floor, otherwise the given ceiling.|
 * 			| @c API_TextID | required (content) <br> optional (paragraphs) | for multistyle content |
 * 			| @c API_LabelID | optional (content) for textual labels <br> optional (paragraphs) for multistyle content | required (parameters) for symbol labels|
 * 			| @c API_ZoneID | required (polygon and parameters) | |
 * 			| @c API_HatchID | required (fill polygon) | If the hatchGlobal field is set to false (the fill is linked to an element), the refPos and refAngle fields are used to calculate the orientation, otherwise the global origin is used for this. If the showArea field is set to true, the note and the noteC fields are used for the appearance of the area, otherwise these fields are ignored.|
 * 			| @c API_LineID <br> @c API_ArcID <br> @c API_CircleID | | |
 * 			| @c API_PolyLineID | required (polygon) | |
 * 			| @c API_SplineID | required/optional | The curve point coordinates are required. If the bezierDirs field is nullptr (autoSmooth is true), the direction parameters are automatically calculated from the first two points' relative position (the autoSmooth field must be set to true in this case).|
 * 			| @c API_HotspotID | | |
 * 			| @c API_PictureID | required (picture content) | |
 * 			| @c API_DrawingID | optional (polygon, drawing data) | |
 * 			| @c API_CutPlaneID | required | The cutplane coordinates are required. See also @ref ACAPI_Element_CreateExt.|
 * 			| @c API_ChangeMarkerID | optional (polygon) | See also @ref ACAPI_Element_CreateExt.|
 * 			| @c API_DetailID @c API_WorksheetID | optional (polygon) | See also @ref ACAPI_Element_CreateExt.|
 * 			| @c API_CameraID | optional (linklist) | Optional for panoramic cameras only.|
 * 			| @c API_CamSetID | | |
 * 			| @c API_SectElemID | | This type of element cannot be created.|
 * 			| @c API_StairID | required (polyline) | |
 * 			| @c API_RailingID | required (polyline) | |
 * 			| @c API_OpeningID | | Extrusion base plane (extrusionGeometryData.frame) and owner element required.|
 * 			The creation process for elements follows the same process as the one you use for creating elements graphically in Archicad. This means for example, that you have to create a wall for windows and doors, etc. The API always checks for the presence of the necessary information, and returns with an error code if something is missing.
 * 			The created element may be redirected into the 2D binary section of a Library Part. Refer to the @ref ACAPI_LibraryPart_SetUpSect_2DDrawHdl function for details. In these case no information is returned, what indices, guids were generated. In this environment only 2D drawing elements can be generated.
 * 			The element also can be clipped by a clipping region. Refer to the @ref ACAPI_Database_StartClippingSession function for details. In these case no information is returned, what indices, guids were generated, since more parts may be generated.
 */
__APIEXPORT GSErrCode ACAPI_Element_Create (API_Element *element, API_ElementMemo *memo);


/**
 * @brief Places a new Window, Door, Skylight, Section, Elevation, Interior Elevation, ChangeMarker, Detail, or Worksheet element with the specified marker into the current database.
 * @ingroup Element
 * @since Archicad 25
 * @param element [in/out] The desired element will be created in the pointed structure. The element->header.type must specify the type of the element to be created. It can be @c API_WindowID, @c API_DoorID, @c API_CutPlaneID, @c API_ElevationID, @c API_InteriorElevationID, @c API_ChangeMarkerID, @c API_DetailID, @c API_WorksheetID, @c API_CurtainWallID or @c API_StairID.
 * @param memo [in] The memo field of the desired element will be created from the pointed structure (if the memo field is needed).
 * @param nSubElems [in] The number of subelems passed.
 * @param subElems [in] Subelem / marker related information.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE - The current database is not proper for the operation.
 * 			- APIERR_BADPARS - The element parameter is nullptr, or the element type is invalid, or the element type is not supported by the server application. The elementMarker->header.type is not @c API_ObjectID.
 * 			- APIERR_REFUSEDPAR - The element->header.type parameter was incorrect. It might happen if you want to create something in a window not capable to display it, for example a cut plane in a section window.
 * 			- APIERR_INVALFLOOR - The element->header.floorInd parameter is out of range.
 * @remarks The type of the element to be created is defined by type in the element header. On return, the guid field of the header is filled in. Don't forget to call @ref ACAPI_DisposeElemMemoHdls to dispose the handles when you don't need them any more.
 * 			The meaning of the different parameters is explained in the table below:
 * 			|element | memo | elementMarker | memoMarker | elementMarker2 | memoMarker2|
 * 			|--------|-------|--------------|------------|----------------|------------|
 * 			|@ref API_WindowType<br> @ref API_DoorType	|addpar	|window/door marker object | marker object parameters | - | - |
 * 			|@ref API_SkylightType | addpar | window/door marker object | marker object parameters | - | - |
 * 			|@ref API_CutPlaneType | cutplane coordinates | section marker object on floorplan | section marker object parameters | story handle marker object on section | story handle marker object parameters |
 * 			|@ref API_ChangeMarkerType | polygon data (optional) | ChangeMarker marker object | marker object parameters | - | - |
 * 			|@ref API_DetailType<br> @ref API_WorksheetType | polygon data (optional) | detail drawing/worksheet marker object | marker object parameters | - | - |
 * 			For more details and instructions see the description of @ref ACAPI_Element_Create.
 */
__APIEXPORT GSErrCode ACAPI_Element_CreateExt (API_Element			*element,
																 API_ElementMemo		*memo,
																 UInt32					nSubElems,
																 API_SubElement			*subElems);


/**
 * @brief Changes the parameters of a number of elements.
 * @ingroup Element
 * @param elemGuids [in] Identifies the element(s).
 * @param defPars [in] The parameters of the new element.
 * @param defMemo [in] The memo of the new element. (Only if needed.)
 * @param mask [in] The mask of the new element.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - defPars is nullptr
 * 			- APIERR_BADDATABASE - The current database is not proper for the operation
 * 			- APIERR_MEMFULL - Not enough memory to complete the operation
 * @remarks You can use this function to change the settings parameters of a number of elements, identified by elemGuids. If elemGuids is empty, then this function works on the selection. Only those elements are affected whose type is the same that passed in the defPars argument.
 * 			Elements which are not allowed for edit for some reason, are ignored. Such cases can be:
 * 			- it is locked,
 * 			- it is on a locked layer,
 * 			- it is part of a group, and suspend group is OFF
 * 			- it is not in the users workspace, etc.
 * 			This function can only be used to change the settings-type parameters of elements, but not their geometric parameters. Only those parameters are affected which are marked in the mask argument. Such elements which refer to Library Parts, the params handle from the memo is interpreted. If it is nullptr, nothing will happen. If it is passed, the actual parameter list will be changed.
 * 			Refer to the @ref ACAPI_Element_Change and the @ref ACAPI_Element_ChangeDefaults functions, which work similarly.
 * 			The following notes are absolutely important:
 * 			- the list of target elements will be automatically extended by the other group members; if there are a group member in the set, and suspend group is OFF
 * 			- all the edited elements keep their unique ID
 * 			- all the inter-element links will be adjusted; including dimensioning also,
 * 			Do not forget to call @ref ACAPI_DisposeElemMemoHdls to dispose of the handles when you're finished.
 */
__APIEXPORT GSErrCode ACAPI_Element_ChangeParameters (const GS::Array<API_Guid>&	elemGuids,
							   											const API_Element			*defPars,
																		const API_ElementMemo		*defMemo,
												   						const API_Element			*mask);


/**
 * @brief Modifies an element in the current database.
 * @ingroup Element
 * @param element [in/out] Reference to the element to be modified, filled with the appropriate new parameters
 * @param mask [in] Optional parameter for masking the relevant fields of element
 * @param memo [in] The memo data to be changed. Optional parameter, can be nullptr
 * @param memoMask [in] Specifies the relevant parts of the memo parameter
 * @param withdel [in] Delete the original instance of the element, or keep it and create a new one
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE - The current database should be the floor plan, a section/elevation, a detail or a worksheet
 * 			- APIERR_BADPARS - The passed element parameter is nullptr,
 * @remarks With this function not only the setting type parameters of an element can be modified, but geometry data too. Unlike @ref ACAPI_Element_ChangeParameters and @ref ACAPI_Element_Edit, it works only on one element at a time. On return the guid field of the element header is filled in. Element connections and dimension chains are updated automatically.
 * 			To change elements having associated markers use the @ref ACAPI_Element_ChangeExt function instead.
 * @ref ACAPI_DisposeElemMemoHdls
 * 		The following element types are supported:
 * 		| Element type | Notes|
 * 		|---------------|------|
 * 		| @c API_WallID | cannot switch between polygon-based and non-polygon-based wall types; type, begC, endC and angle fields can be modified for non-polygonal walls only; the gables of the wall can be changed|
 * 		| @c API_ColumnID | beside the setting parameters the origoPos, axisRotationAngle fields can be accessed directly; the gables, columnSegments, assemblySegmentCuts, assemblySegmentSchemes and assemblySegmentProfiles memos can be modified|
 * 		| @c API_BeamID | beside the setting parameters the begC, endC fields can be accessed directly; the beamHoles, gables, beamSegments, assemblySegmentCuts, assemblySegmentSchemes and assemblySegmentProfiles memos can be modified |
 * 		| @c API_WindowID <br> @c API_DoorID | beside the setting parameters the following fields can be edited: objLoc, reflected, oSide, refSide, wallCutUsing, libInd; the gables and params memos can also be modified|
 * 		| @c API_ObjectID <br> @c API_LampID | beside the setting parameters the following fields can be edited: pos, libInd; the gables and params memos can also be modified|
 * 		| @c API_SlabID | beside the setting parameters the polygon of the slab can be modified directly (coords, pends, parcs and vertexIDs memo handles)|
 * 		| @c API_RoofID | beside the setting parameters the baseLine field, the polygon of the roof and the roof sides can be modified directly (coords, pends, parcs, vertexIDs and roofSides memo handles)|
 * 		| @c API_MeshID | beside the setting parameters the polygon and ridge levels of the mesh can be modified directly (coords, pends, parcs vertexIDs, meshPolyZ, meshLevelCoords and meshLevelEndsmemo handles)|
 * 		| @c API_DimensionID | beside the setting parameters the dimElems memo handle can be modified|
 * 		| @c API_RadialDimensionID | beside the setting parameters the following fields can be edited: base, note|
 * 		| @c API_LevelDimensionID | beside the setting parameters the following fields can be edited: loc, note1, note2, parentType, parentGuid|
 * 		| @c API_AngleDimensionID | beside the setting parameters the note and base fields can be modified|
 * 		| @c API_TextID | beside the setting parameters the following fields can be edited: loc, width, nonBreaking; the content and the style of the text can also be modified (textContent, paragraphs memo)|
 * 		| @c API_LabelID | beside the setting parameters the following fields can be edited: begC, midC, endC, u.text (the same as @c API_TextID), u.symbol (the same as @c API_ObjectID); for textual label the content and the style of the text can also be modified (textContent, paragraphs memo); an associative Label cannot be made independent, and an independent Label cannot be made associative.|
 * 		| @c API_ZoneID | beside the setting parameters the following fields can be edited: libInd, pos and the polygon of the zone (coords, pends, parcs, vertexIDs memo handles)|
 * 		| @c API_HatchID | beside the setting parameters the following fields can be edited: note and the polygon of the hatch (coords, pends, parcs, vertexIDs memo handles)|
 * 		| @c API_LineID | beside the setting parameters the begC, endC fields can be accessed directly|
 * 		| @c API_ArcID <br> @c API_CircleID | both the setting and geometry parameters can be modified with @ref ACAPI_Element_Change|
 * 		| @c API_PolyLineID | beside the setting parameters the the polygon data (coords, pends, parcs, vertexIDs memo handles) can be accessed directly|
 * 		| @c API_SplineID | only the setting parameters can be modified with @ref ACAPI_Element_Change in this version; geometry data, autoSmooth and closed fields cannot be accessed|
 * 		| @c API_HotspotID | beside the setting parameters the following fields can be edited: pos, height|
 * 		| @c API_CutPlaneID | beside the setting parameters the following fields can be edited: depth, leftDir|
 * 		| @c API_ChangeMarkerID | beside the setting parameters the following fields can be edited: pos. It has effect only when the changed ChangeMarker has no polygon, i.e. it points to a single coordinate marked by pos.|
 * 		| @c API_DetailID <br> @c API_WorksheetID | beside the setting parameters the pos field and the polygon of the detail or worksheet (coords, pends, parcs, vertexIDs memo handles) can be accessed directly|
 * 		| @c API_SectElemID | after modifying the parent element on the floor plan database, calling @ref ACAPI_Element_Change for the section symbol element on the section database rebuilds the image of the modified element in the section window (use this to avoid unnecessary @ref ACAPI_View_Rebuild and @ref ACAPI_Database_RebuildCurrentDatabase calls). The function returns APIERR_DELETED if the parent element has been deleted or got out of the scope of the section; otherwise it gives back the new index of the refreshed section element.|
 * 		| @c API_MorphID | in some cases changing the tranmat field effects the body points themselves and vice versa; the resulting body will be correct, but getting the tranmat field after setting might result different values inside|
 * 		| @c API_HotlinkID | the type, and hotlinkGroupGuid fields can not be changed.|
 * 		| @c API_OpeningID | Connected elements can not be removed or added.|
 * 		| @c API_ExternalElemID | beside the setting parameters in case of non-hierarchical external elements params memos can also be modified |
 * 		You can modify more elements at once with a single call of the @ref ACAPI_Element_ChangeMore function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_Change-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_Change (API_Element			*element,
															  const API_Element		*mask,
															  const API_ElementMemo	*memo,
															  UInt64				memoMask,
															  bool					withdel);


/**
 * @brief Modifies a number of elements in the current database.
 * @ingroup Element
 * @param elemGuids [in/out] This parameter identifies the elements to be modified.
 * @param defPars [in] The parameters of the new element.
 * @param defMemo [in] The memo of the new element. (Only if needed.)
 * @param mask [in] The mask of the new element.
 * @param memoMask [in] The memo mask of the new element. (Only if needed.)
 * @param withdel [in] Delete the original instances of elements, or keep them and create new ones
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE - The current database should be the floor plan a section/elevation a detail a layout or a master layout.
 * 			- APIERR_BADPARS - The passed defParams parameter is nullptr,
 * @remarks This function is an extension of @ref ACAPI_Element_Change to modify more elements at the same time.
 */
__APIEXPORT GSErrCode ACAPI_Element_ChangeMore (GS::Array<API_Guid>&	elemGuids,
							   									  const API_Element		*defPars,
																  const API_ElementMemo	*defMemo,
												   				  const API_Element		*mask,
																  UInt64				memoMask,
																  bool					withdel);


/**
 * @brief Modifies a Window, Door, Section, Elevation, Interior Elevation, ChangeMarker, Detail, Worksheet, Stair or External element in the current database.
 * @ingroup Element
 * @since Archicad 25
 * @param element [in/out] Reference to the element to be modified, filled with the appropriate new parameters
 * @param mask [in] Optional parameter for masking the relevant fields of element
 * @param memo [in] The memo data to be changed. Optional parameter, can be nullptr
 * @param memoMask [in] Specifies the relevant parts of the memo parameter. You can use a special mask value (ACAPI_ELEMENT_CHANGEEXT_ALLSEGMENTS) to change all segment of an interior elevation element.
 * @param nSubElems [in] The number of subelems (markers) passed (0-3).
 * @param subElems [in] Contains the markers (default marker, story handle marker, interior elevation common marker) to be modified.
 * @param withdel [in] Delete the original instance of the element, or keep it and create a new one
 * @param subIndex [in] The index of the section segment to be modified (for interior elevations only). The value is between 0 and the (number of segments - 1).
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE - The current database should be floor plan, section/elevation, detail or worksheet.
 * 			- APIERR_BADPARS - The passed element parameter is nullptr,
 * @remarks This function is an extension of @ref ACAPI_Element_Change to modify elements with their linked sub-elements.
 * 			With this function not only the setting type parameters of an element can be modified, but geometry data too. Unlike @ref ACAPI_Element_ChangeParameters and @ref ACAPI_Element_Edit, it works only on one element at a time. On return the guid field of the element and elementMarker header is filled in. Element connections and dimension chains are updated automatically. Do not forget to call @ref ACAPI_DisposeElemMemoHdls to dispose the memo handles when they are not needed any more.
 * 			The following element types are supported:
 * 			|element | memo | elementMarker | memoMarker | elementMarker2 | memoMarker2|
 * 			|--------|------|---------------|------------|----------------|--------------------|
 * 			|@ref API_WindowType <br> @ref API_DoorType | addpar | window/door marker object | marker object parameters | - | - |
 * 			|@ref API_CutPlaneType | cutplane coordinates | section marker object on floorplan | section marker object parameters | story handle marker object on section | story handle marker object parameters |
 * 			| @ref API_ElevationType | elevation coordinates | elevation marker object on floorplan | elevation marker object parameters | story handle marker object on section | story handle marker object parameters |
 * 			|@ref API_ChangeMarkerType | polygon data (optional) | ChangeMarker marker object | marker object parameters | - | - |
 * 			|@ref API_WindowType <br> @ref API_DoorType | addpar | window/door marker object | marker object parameters | - | - |
 * 			|@ref API_ExternalElemType | - | hierarchical subelement 1 | addpar | hierarchical subelement 2 | addpar | etc.
 */
__APIEXPORT GSErrCode ACAPI_Element_ChangeExt (API_Element			*element,
																 const API_Element		*mask,
																 API_ElementMemo		*memo,
																 UInt64					memoMask,
																 UInt32					nSubElems,
																 API_SubElement			*subElems,
																 bool					withdel,
																 Int32					subIndex);


/**
 * @brief Deletes a number of elements.
 * @ingroup Element
 * @param elemGuids [in] This parameter identifies the elements to be deleted.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE - The current database is not proper for the operation.
 * 			- APIERR_MEMFULL - not enough memory to complete the operation
 * 			- APIERR_NOTMINE - The operation attempted to delete an element that belongs to another user. Likely to occur in teamwork mode.
 * @remarks You can use this function to delete elements identified by elemGuids. To delete the selected elements use @ref ACAPI_Element_DeleteSelected function.
 * 			In the case there is at least one element which are not allowed to delete for some reason, the whole command is terminated. Such cases can be:
 * 			- it is locked,
 * 			- it is on a locked layer,
 * 			- it is part of a group, and suspend group is OFF
 * 			- it is a subelement of a composite element (Curtain Wall, Stair, or Railing)
 * 			- it is not in the users workspace, etc.
 * 			The following notes are absolutely important:
 * 			- the list of target elements will be automatically extended by the other group members; if there are a group member in the set, and suspend group is OFF
 * 			- all the linked elements will be deleted; associative labels, dimensions etc.
 * 			Note that this function is working on the Section/Elevation databases also, which may have references to the plan database; they called virtual symbols identified by the @c API_SectElemID element type. From Archicad 6.50 R2/V2 these elements can be deleted directly from the section database, with the limitation that the section window must be the front window.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_Delete-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_Delete (const GS::Array<API_Guid>& elemGuids);


/**
 * @brief Deletes the selected elements.
 * @ingroup Element
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE - The current database is not proper for the operation.
 * 			- APIERR_MEMFULL - not enough memory to complete the operation
 * 			- APIERR_NOTMINE - The operation attempted to delete an element that belongs to another user. Likely to occur in teamwork mode.
 * @remarks You can use this function to delete selected elements. To delete specific elements use @ref ACAPI_Element_Delete function.
 * 			In the case there is at least one element which are not allowed to delete for some reason, the whole command is terminated. Such cases can be:
 * 			- it is locked,
 * 			- it is on a locked layer,
 * 			- it is part of a group, and suspend group is OFF
 * 			- it is a subelement of a composite element (Curtain Wall, Stair, or Railing)
 * 			- it is not in the users workspace, etc.
 * 			The following notes are absolutely important:
 * 			- the list of target elements will be automatically extended by the other group members; if there are a group member in the set, and suspend group is OFF
 * 			- all the linked elements will be deleted; associative labels, dimensions etc.
 * 			Note that this function is working on the Section/Elevation databases also, which may have references to the plan database; they called virtual symbols identified by the @c API_SectElemID element type. From Archicad 6.50 R2/V2 these elements can be deleted directly from the section database, with the limitation that the section window must be the front window.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_DeleteSelected-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_DeleteSelected ();


/**
 * @brief Transforms a set of elements.
 * @ingroup Element
 * @param elemNeigs [in-out] An Array of @ref API_Neig objects which enables you to work not only on an element as a whole, but on its internal parts too.
 * @param pars [in] The details of the editing operation.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE - The current database is not proper for the operation.
 * 			- APIERR_BADID - The element guid is invalid.
 * 			- APIERR_DELETED - The element does not exist in the database
 * 			- APIERR_MEMFULL - Not enough memory to complete the operation
 * 			- APIERR_REFUSEDPAR - The edit parameters are incorrect.
 * 			- APIERR_BADPARS - The edit parameters are incorrect.
 * @remarks This function transforms a set of elements with the parameters passed in the @ref API_EditPars structure. These parameters identify both the operation code (drag, rotate, mirror...) and the transformation parameters.
 * 			If elemNeigs is nullptr or empty, then this function works on the selection; otherwise the set of elements passed will be the target.
 * 			What elements are transformed in the last case? The elemNeigs array is an @ref API_Neig list which enables you to work on not just a whole element, but on its internal parts as well. If you pass for example a neig to a slab hole, only the given hole will be transformed, without touching the base contour of the element.
 * 			Elements which cannot be edited for some reason are ignored. Such causes can be:
 * 			- it is locked,
 * 			- it is on a locked layer,
 * 			- it is part of a group, and suspend groups is OFF
 * 			- it is not in the users workspace, etc.
 * 			The following notes are absolutely important:
 * 			- the list of target elements will be automatically extended with the other group members; if there is a group member in the set and suspend groups is OFF
 * 			- all the edited elements keep their unique ID
 * 			- all the inter-element links will be adjusted; including dimensioning also
 * 			The new element's GUID will be returned for each edited element in the guid field.
 * 			Note that this function is working on Section/Elevation databases also, which may have references to the plan database; they called virtual symbols identified by the @c API_SectElemID element type. From Archicad 6.50 R2/V2 these elements can be edited directly in the section database, with the limitation that the section window must be the front window.
 * 			You can also change the geometry data of an element with the @ref ACAPI_Element_Change function.
 */
__APIEXPORT GSErrCode ACAPI_Element_Edit (GS::Array<API_Neig>* elemNeigs, const API_EditPars& pars);


/**
 * @brief Executes tool commands on elements.
 * @ingroup Grouping
 * @param elemGuids [in] Array containing the GUIDs of the elements to work on.
 * @param typeID [in] Type of the tool command. The possible values are listed below.
 * @param pars Reserved for further use.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE - The current database is not proper for the operation
 * 			- APIERR_BADPARS - The passed parameter is incorrect; typeID
 * 			- APIERR_MEMFULL - not enough memory to complete the operation
 * @remarks This function is used to execute tool commands on a set of elements. The elements are specified in the elemGuids array or if this parameter is an empty array, the function operates on the current selection. The functionality of each tool is equivalent to the corresponding commands of the Tools menu.
 * 			The following tool commands are available:
 * 			| @ref API_ToolCmdID | Meaning |
 * 			|---------------|---------|
 * 			| @c APITool_Group | Creates a new group with the passed elements. |
 * 			| @c APITool_Ungroup | Ungroups the passed elements. |
 * 			| @c APITool_SuspendGroups | Switches the Suspend Groups mode On/Off. |
 * 			| @c APITool_Lock | Locks the passed elements. |
 * 			| @c APITool_Unlock | Unlocks the passed elements. |
 * 			| @c APITool_BringToFront | Brings the passed elements above all the other. |
 * 			| @c APITool_BringForward | Moves forward the passed elements. |
 * 			| @c APITool_SendBackward | Moves backward the passed elements. |
 * 			| @c APITool_SendToBack | Sends behind the elements to be overlapped by all the other. |
 * 			| @c APITool_ResetOrder | Resets the default drawing order of the passed elements. |
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Grouping_Tool-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Grouping_Tool (const GS::Array<API_Guid>&	elemGuids,
															API_ToolCmdID				typeID,
															void						*pars);


/**
 * @brief Adds/removes a number of elements to/from the current selection.
 * @ingroup Selection
 * @param selNeigs [in] The elements to be added/removed (array of @ref API_Neig objects);
 * @param add [in] If true, adds the elements to the current selection, otherwise removes them from the selection.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE - The current database is not proper for the operation.
 * 			- APIERR_BADID - The element unique ID is invalid. The element type is invalid, or the element type is not supported by the server application.
 * 			- APIERR_BADPARS - The passed parameter contains invalid data; selNeigs.
 * @remarks You can use this function to add/remove (add flag) a number of (nItem) elements to/from the current selection. The elements are defined by the selNeigs array of type @ref API_Neig. Use @ref ACAPI_Selection_DeselectAll function to remove all elements from the selection.
 * 			The neigID and the guid fields are required (inIndex and/or holeSel only where applicable).
 * 			The @ref API_NeigID is differs from the @ref API_ElemTypeID, because it refers to the selectable parts of the elements, not the elements themselves.
 * 			You can select not only whole elements but element parts, such as vertices, edges and faces, specified in the @c elemPartType and @c elemPartIndex fields of @ref API_Neig.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Selection_Select-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Selection_Select (const GS::Array<API_Neig>& selNeigs, bool add);


/**
 * @brief Adds/removes a number of elements to/from the current selection.
 * @ingroup Selection
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE - The current database is not proper for the operation.
 * @remarks This function acts as "Deselect All". Use @ref ACAPI_Selection_Select function to add/remove elements to/from the current selection.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Selection_DeselectAll-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Selection_DeselectAll ();



/**
 * @brief Obtains the user data attached to an element or an element default.
 * @ingroup Element
 * @ingroup UserData
 * @param elemHead [in] Identifies the element or element default (only fields type and guid are used).
 * @param userData [in/out] Pointer to the user data.
 * @param mask [in] Optional mask. Currently valid values are 0 and @c APIElemMask_FloorPlan. In the latter case, the elements in the floor plan database are counted directly, without changing the database first.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter is nullptr; userData
 * 			- APIERR_BADID - The elemHead is incorrect.
 * 			- APIERR_NOUSERDATA - No user data attached with the gived signature
 * @remarks This function is used to get the user attached data from an element or from an element default. To obtain data from element default only elemHead->type is necessary and elemHead->guid should be APINULLGuid.
 * 			To obtain data from an element only elemHead->guid is necessary and it should be set to element's guid. Use the @ref ACAPI_Element_SetUserData functions to push data into the element record.
 * 			You can read more about this topic at the Save data into Element records paper.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetUserData-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetUserData	(API_Elem_Head				*elemHead,
																	 API_ElementUserData		*userData,
																	 UInt32						mask = 0);


/**
 * @brief Attaches the user data to an element or an element default.
 * @ingroup Element
 * @ingroup UserData
 * @param elemHead [in] Header of the element (only fields type and guid are used).
 * @param userData [in] Pointer to the new user data.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Any of the passed parameters is nullptr
 * 			- APIERR_BADPLATFORMSIGN - The given platform sign is invalid (out of range)
 * 			- APIERR_MEMFULL - Out of memory
 * @remarks This function is used to push the user attached data into an element default or into an element. To set data to element default only @c elemHead->type is necessary and @c elemHead->guid should be @c APINULLGuid. To set data to an element only elemHead->guid is necessary and it should be set to element's guid. Use the @ref ACAPI_Element_GetUserData function to get data from the element record.
 * 			Note that this function is not undoable in case of element default setting.
 * 			The caller should allocate and deallocate the userData->dataHdl handle.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_SetUserData-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_SetUserData	(API_Elem_Head				*elemHead,
																	 const API_ElementUserData	*userData);


/**
 * @brief Removes the user data attached to the specified element.
 * @ingroup UserData
 * @param elemHead [in] Identifies the element the user data is attached to.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The element does not contain any user data assigned by this add-on.
 * 			- APIERR_BADPLATFORMSIGN - The platformsign field in the user data is invalid.
 * 			- APIERR_BADID - The passed type is not correct.
 * @remarks You can remove the user data that is no longer needed and is attached to an element with this function.
 */
__APIEXPORT GSErrCode ACAPI_UserData_DeleteUserData (API_Elem_Head *elemHead);


/**
 * @brief Links one element to another.
 * @ingroup ElementLink
 * @param guid_linkFrom [in] Identifies the element to which the other element will be linked.
 * @param guid_linkTo [in] Identifies the element to link to the first element.
 * @param linkFlags [in] Custom flags to store with the link.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NEEDSUNDOSCOPE - The function must be undoable, it wasn't called from an undoable command scope.
 * 			- APIERR_BADDATABASE, APIERR_NOTMINE - The function cannot operate on the current database.
 * 			- APIERR_BADID - One or both of the passed unique IDs are invalid, or the two IDs are equal.
 * 			- APIERR_LINKEXIST - The elements has already been linked together.
 * @remarks The add-on creating the link is also registered with the link; so the link "belongs" to the add-on.
 * 			The advantage of using element linking is that the server application automatically tracks changes in the GUIDs, and updates them accordingly.
 * 			After establishing a link, you can also install an element observer with a callback function, that will be called when any of the observed elements change. In this callback you can find out which other elements are linked to the observed element with @ref ACAPI_ElementLink_GetLinks, and retrieve the supplied linkFlags with @ref ACAPI_ElementLink_GetLinkFlags. You can remove the link when you are done with @ref ACAPI_ElementLink_Unlink.
 */
__APIEXPORT GSErrCode ACAPI_ElementLink_Link (const API_Guid&	guid_linkFrom,
															const API_Guid&	guid_linkTo,
															GSFlags			linkFlags);


/**
 * @brief Removes the link from the second element to the first.
 * @ingroup ElementLink
 * @param guid_linkFrom [in] Identifies the element to which the other element is linked.
 * @param guid_linkTo [in] Identifies the element which is linked to the first element.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE, APIERR_NOTMINE - The function cannot operate on the current database.
 * 			- APIERR_NEEDSUNDOSCOPE - The function must be undoable, it wasn't called from an undoable command scope.
 * 			- APIERR_LINKNOTEXIST - There isn't any link from the second element to the first.
 * @remarks This element removes the link to the second element (identified by guid_linkTo) from the element identified by guid_linkFrom. See @ref ACAPI_ElementLink_Link for more details.
 */
__APIEXPORT GSErrCode ACAPI_ElementLink_Unlink (const API_Guid&	guid_linkFrom,
															  const API_Guid&	guid_linkTo);


/**
 * @brief Returns a list of elements linked to the given element.
 * @ingroup ElementLink
 * @param guid_linkFrom [in] Identifies the element to which the other elements were linked.
 * @param guid_linkTo [out] Returns the GUIDs of the elements which were linked to the first element.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed guid_linkTo pointer is nullptr.
 * 			- APIERR_BADDATABASE, APIERR_NOTMINE - The function cannot operate on the current database.
 * @remarks The element links are not bidirectional, you always link one element to another. This function returns the list of elements linked to the element having the guid_linkFrom GUID.
 * 			Note that if this function is called in an unclosed undoable session, then it returns not only the existing links, but also the links which have been deleted in the current undoable session.
 */
__APIEXPORT GSErrCode ACAPI_ElementLink_GetLinks (const API_Guid&			guid_linkFrom,
																GS::Array<API_Guid>*	guid_linkTo);


/**
 * @brief Retrieves the link flags associated to the link between the two elements.
 * @ingroup ElementLink
 * @param guid_linkFrom [in] Identifies the element to which the other element was linked.
 * @param guid_linkTo [in] Identifies the element which was linked to the first element.
 * @param linkFlags [out] Returns the custom flags assigned to the link with @ref ACAPI_ElementLink_Link.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed linkFlags pointer is nullptr.
 * 			- APIERR_BADDATABASE, APIERR_NOTMINE - The function cannot operate on the current database.
 * @remarks When you link an element to an other, you can also pass custom flags which are stored with the link in the database. With this function you can retrieve these flags.
 */
__APIEXPORT GSErrCode ACAPI_ElementLink_GetLinkFlags (const API_Guid&	guid_linkFrom,
																	const API_Guid&	guid_linkTo,
																	GSFlags			*linkFlags);


/**
 * @brief Attaches an observer to the given element.
 * @ingroup Element
 * @ingroup Notification
 * @param elemGuid [in] Identifies the element to attach the observer to.
 * @param notifyFlags [in] Defines the behavior of the attached observer in certain database operations.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The referenced element cannot be found in the database.
 * @remarks This function can be used to track changes in an element. After attaching the observer, the installed APIElementEventHandlerProc will be called with the appropriate notifications.
 */
__APIEXPORT GSErrCode ACAPI_Element_AttachObserver (const API_Guid& elemGuid, GSFlags notifyFlags = 0);


/**
 * @brief Detaches the observer from the given element.
 * @ingroup Element
 * @ingroup Notification
 * @param elemGuid [in] Identifies the element to detach the observer from.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The referenced element cannot be found in the database.
 */
__APIEXPORT GSErrCode ACAPI_Element_DetachObserver (const API_Guid& elemGuid);


/**
 * @brief Returns the elements observed by the add-on.
 * @ingroup Notification
 * @param elemHeads [out] The headers of the observed elements.
 * @return
 * 			- NoError - The function has completed with success.
 */
__APIEXPORT GSErrCode ACAPI_Notification_GetObservedElements (GS::Array<API_Elem_Head> *elemHeads);



/**
 * @brief Creates a new Solid Operation.
 * @ingroup Element
 * @param guid_Target [in] Identifies the target element.
 * @param guid_Operator [in] Identifies the operator element.
 * @param operation [in] The operation type
 * @param guid_Results [out] The result elements after the operation (in case of successfull operation, the target and operator elements will be deleted).
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NEEDSUNDOSCOPE - The function must be undoable, it wasn't called from an undoable command scope.
 * 			- APIERR_BADDATABASE, APIERR_NOTMINE - The function cannot operate on the current database.
 * 			- APIERR_BADINDEX - One or both of the passed IDs are invalid, or the two IDs are equal.
 * 			- APIERR_BADPARS - Invalid value passed in the operation parameter.
 * 			- APIERR_NO3D - Solid operation targets and operators can be freeshape elements only.
 * @remarks This function defines a new Solid Operation between two morph elements.
 * 			In case of successfull operation, the target and operator elements will be deleted. The result elements will be returned in the guid_Results parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_SolidOperation_Create-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_SolidOperation_Create (API_Guid				guid_Target,
																			 API_Guid				guid_Operator,
																			 API_SolidOperationID	operation,
																			 GS::Array<API_Guid>*	guid_Results = nullptr);


/**
 * @brief Defines a new Solid Operation Link.
 * @ingroup Element
 * @param guid_Target [in] Identifies the target element.
 * @param guid_Operator [in] Identifies the operator element.
 * @param operation [in] The operation type
 * @param linkFlags [in] Linking options (see @ref ACAPI_Element_SolidLink_GetFlags)
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NEEDSUNDOSCOPE - The function must be undoable, it wasn't called from an undoable command scope.
 * 			- APIERR_BADDATABASE, APIERR_NOTMINE - The function cannot operate on the current database.
 * 			- APIERR_BADINDEX - One or both of the passed IDs are invalid, or the two IDs are equal.
 * 			- APIERR_BADPARS - Invalid value passed in the operation parameter.
 * 			- APIERR_REFUSEDPAR - Linking together of hotlinked elements is not allowed.
 * 			- APIERR_LINKEXIST - The elements has already been linked together.
 * @remarks This function defines a new Solid Operation Link between two construction elements.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_SolidLink_Create-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_SolidLink_Create (API_Guid				guid_Target,
																		API_Guid				guid_Operator,
																		API_SolidOperationID	operation,
																		GSFlags					linkFlags);


/**
 * @brief Discontinues a Solid Operation Link.
 * @ingroup Element
 * @param guid_Target [in] Identifies the target element.
 * @param guid_Operator [in] Identifies the operator element.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NEEDSUNDOSCOPE - The function must be undoable, it wasn't called from an undoable command scope.
 * 			- APIERR_BADDATABASE, APIERR_NOTMINE - The function cannot operate on the current database.
 * 			- APIERR_BADINDEX - One or both of the passed IDs are invalid, or the two IDs are equal.
 * 			- APIERR_LINKNOTEXIST - There is no Solid Link in the database between elements specified by guid_Target and guid_Operator.
 * 			- APIERR_REFUSEDPAR - Hotlinked Solid Links cannot be removed.
 * @remarks This function removes the Solid Operation Link defined between two construction elements.
 */
__APIEXPORT GSErrCode ACAPI_Element_SolidLink_Remove (API_Guid	guid_Target,
																		API_Guid	guid_Operator);


/**
 * @brief Retrieves the creation time of a Solid Operation Link.
 * @ingroup Element
 * @param guid_Target [in] Identifies the target element.
 * @param guid_Operator [in] Identifies the operator element.
 * @param linkTime [out] Time of the link creation.
 * @param linkSubTime [out] Auxiliary time parameter of the link creation.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE, APIERR_NOTMINE - The function cannot operate on the current database.
 * 			- APIERR_BADPARS - The linkTime or the linkSubTime parameter is nullptr.
 * 			- APIERR_LINKNOTEXIST - There is no Solid Link in the database between elements specified by guid_Target and guid_Operator.
 * @remarks This function retrieves the creation time of a Solid Operation Link defined between two construction elements.
 * 			Since GSTime is a second-precise date-time format, the linkTime parameter of that type is not enough to order the Solid Operation Links by their creation time. However it is important to know which operation is to be performed prior to another, if there is more than one Solid Operations defined to a given element. That is the auxiliary linkSubTime for, which distinguishes the link creation time values within one second.
 */
__APIEXPORT GSErrCode ACAPI_Element_SolidLink_GetTime (API_Guid		guid_Target,
																		 API_Guid		guid_Operator,
																		 GSTime			*linkTime,
																		 UInt32			*linkSubTime);


/**
 * @brief Retrieves the operation code of a Solid Operation Link.
 * @ingroup Element
 * @param guid_Target [in] Identifies the target element.
 * @param guid_Operator [in] Identifies the operator element.
 * @param operation [out] The type of the Solid Operation.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE, APIERR_NOTMINE - The function cannot operate on the current database.
 * 			- APIERR_BADPARS - The operation parameter is nullptr.
 * 			- APIERR_LINKNOTEXIST - There is no Solid Link in the database between elements specified by guid_Target and guid_Operator.
 * @remarks This function retrieves the operation code of a Solid Operation Link defined between two construction elements.
 */
__APIEXPORT GSErrCode ACAPI_Element_SolidLink_GetOperation (API_Guid				guid_Target,
																			  API_Guid				guid_Operator,
																			  API_SolidOperationID	*operation);


/**
 * @brief Retrieves the flag of a Solid Operation Link.
 * @ingroup Element
 * @param guid_Target [in] Identifies the target element.
 * @param guid_Operator [in] Identifies the operator element.
 * @param linkFlags [out] Linking options (see Remarks).
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE, APIERR_NOTMINE - The function cannot operate on the current database.
 * 			- APIERR_BADPARS - The linkFlags parameter is nullptr.
 * 			- APIERR_LINKNOTEXIST - There is no Solid Link in the database between elements specified by guid_Target and guid_Operator.
 * @remarks This function retrieves the attribute flag of a Solid Operation Link identified by the Target and the Operator element.
 * 			The meaning of the flag bits:
 * 			|Flag|Meaning|
 * 			|--- |--- |
 * 			|APISolidFlag_OperatorAttrib|The new surfaces inherit the attributes of the operator|
 * 			|APISolidFlag_SkipPolygonHoles|Use operator (roof or slab) without holes|
 */
__APIEXPORT GSErrCode ACAPI_Element_SolidLink_GetFlags (API_Guid	guid_Target,
																		  API_Guid	guid_Operator,
																		  GSFlags	*linkFlags);


/**
 * @brief Retrieves the target elements linked to an operator element.
 * @ingroup Element
 * @param guid_Operator [in] The GUID of the operator element.
 * @param guid_Targets [out] GUID list of the target elements linked to the operator element.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE, APIERR_NOTMINE - The function cannot operate on the current database.
 * 			- APIERR_BADPARS - The guid_Targets parameter is nullptr.
 * @remarks This function retrieves a list of target elements associated with a given operator element with Solid Operation Link.
 */
__APIEXPORT GSErrCode ACAPI_Element_SolidLink_GetTargets (API_Guid			guid_Operator,
																			GS::Array<API_Guid>	*guid_Targets);


/**
 * @brief Retrieves the operator elements linked to a target element.
 * @ingroup Element
 * @param guid_Target [in] The GUID of the target element.
 * @param guid_Operators [out] GUID list of the operator elements linked to the target element.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE, APIERR_NOTMINE - The function cannot operate on the current database.
 * 			- APIERR_BADPARS - The guid_Operators parameter is nullptr.
 * @remarks This function retrieves a list of operator elements associated with a given target element with Solid Operation Link.
 */
__APIEXPORT GSErrCode ACAPI_Element_SolidLink_GetOperators (API_Guid				guid_Target,
																			  GS::Array<API_Guid>	*guid_Operators);



/**
 * @brief Retrieves information on the 3D data of an element.
 * @ingroup  ModelAccess
 * @param elemHead [in] The element to get the 3D information for.
 * @param info3D [out] The 3D information to be retrieved.
 * @return
 * 			- NoError - The operation was successful.
 * 			- APIERR_BADID - Incorrect elemHead.guid was specified. Incorrect type was specified, for example 0 or an element without 3D representation. such as @c API_LineID.
 * 			- APIERR_BADPARS - The info3D parameter was nullptr.
 * 			- APIERR_NOTMINE - The element was attempted to be accessed on a layer owned by someone else. Most likely to occur when working on documents in teamwork mode.
 * 			- APIERR_LOCKEDLAY - The element was attempted to be accessed on a locked layer.
 * 			- APIERR_HIDDENLAY - The element was attempted to be accessed on a hidden layer.
 * 			- APIERR_GENERAL - The element wasn't found in the 3D database.
 * @remarks This function returns information on the 3D data of the element defined by elemHead. This function is defined only for those elements which have 3D representation: @c API_WallID, @c API_ColumnID, @c API_BeamID, @c API_WindowID, @c API_DoorID, @c API_ObjectID, @c API_LampID, @c API_SlabID, @c API_RoofID, and @c API_RoomID. The returned structure contains the first and last body (or, in case of @c API_LampID, the first and last light also) indices of the element's 3D data. This index is an index to the whole 3D data structure, where all the 3D data is stored in a continuous way.
 * 			The 3D data of the element doesn't need to exist; Archicad will convert the element to 3D independently of any existing 3D window data. This also means that the 3D representation doesn't contain perspective cuts and 3D cut planes!
 * 			Currently, this is the only way to obtain information on holes in walls. Look for polygons which have a horizontal normal vector perpendicular to the reference line of the wall. Similarly, you can get information on the intersection of walls by looking for polygons with a vertical normal vector.
 * 			You can find more information on the 3D data in the 3D Manager and at the @ref API_ElemInfo3D page of this help. You have to be familiar with the primitive element section of the GDL Reference Manual.
 */
__APIEXPORT GSErrCode ACAPI_ModelAccess_Get3DInfo			(const API_Elem_Head&	elemHead,
															 API_ElemInfo3D			*info3D);


/**
 * @brief Returns a table of connected elements and the connecting polygons.
 * @ingroup ModelAccess
 * @param elementList [in] List of API_Guids, referencing elements from the active sight. Archicad will search connections among these elements.
 * @param connectionTable [out] The returned table which consists of pairs of element ids as keys, and an array of polygons representing the connecting surface between the respective pair of elements.
 * @return
 *			- NoError - The operation was successful.
 *			- APIERR_REFUSEDCMD - The 3D model is not available in the current context.
 *			- APIERR_GENERAL - Error regarding the active sight.
 */
__APIEXPORT GSErrCode ACAPI_ModelAccess_GetConnectionTable (const GS::HashSet<API_Guid>&	elementList,
															API_ElementConnectionTable*	connectionTable);



/**
 * @brief Returns the attribute index of the material of a specific body of an element.
 * @ingroup ModelAccess
 * @param elemIdx [in] The index of the element.
 * @param bodyIdx [in] The index of the body in the element.
 * @param materialIdx [out] API_AttributeIndex of the material.
 * @return
 *			- NoError - The operation was successful.
 *			- APIERR_BADDATABASE - Not the appropriate database was open for the operation. Only 2D and 3D are supported.
 *			- APIERR_REFUSEDCMD - The 3D model is not available in the current context.
 *			- APIERR_GENERAL - Data for the given element can not be found.
 * @remarks This function can not work properly unless the model of the active sight was generated for separate components with the ACAPI_ModelAccess_GenerateModelWithSeparateComponents function.
 */
__APIEXPORT GSErrCode ACAPI_ModelAccess_GetBuildingMaterial (const UInt32 elemIdx, const UInt32 bodyIdx, API_AttributeIndex* materialIdx);


/**
 * @brief Returns information on the quantities parameters of an element.
 * @ingroup Element
 * @param elemGuid [in] Guid of the element.
 * @param params [in] Input parameters.
 * @param quantities [Out] Optional quantity parameters.
 * @param mask [In] Optional parameter for masking the relevant fields of quantities (by default it is nullptr).
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - quantities is nullptr, or mask is nullptr and either elements or composites field is nullptr in quantities.
 * 			- APIERR_BADID - Incorrect elemGuid was specified.
 * @remarks This function is used to get the quantity parameters of an element. The quantitites are: surface, volume, perimeter, length and several other parameters. This applies to all construction elements.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetQuantities-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetQuantities		(API_Guid							elemGuid,
								  										 const API_QuantityPar				*params,
																		 API_Quantities						*quantities,
																		 const API_QuantitiesMask			*mask = nullptr);


/**
 * @brief Returns information on the quantities parameters of multiple elements of the same type.
 * @ingroup Element
 * @param elemGuids [in] Guids of the elements.
 * @param params [in] Input parameters.
 * @param quantities [Out] Optional quantity parameters, one in the array for each Guid.
 * @param mask [In] Optional parameter for masking the relevant fields of quantities (by default it is nullptr).
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Either elemGuids or quantities is nullptr, quantities does not have the same size as elemGuids, or mask is nullptr and either elements or composites field is nullptr in quantities.
 * 			- APIERR_BADID - Incorrect elemGuids was specified.
 * @remarks This function is used to get the quantity parameters of multiple elements of the same type. The quantitites are: surface, volume, perimeter, length and several other parameters. This applies to all construction elements. The elemGuids and the quantities arrays need to have the same size.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetMoreQuantities-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetMoreQuantities	(const GS::Array<API_Guid>			*elemGuids,
								  										 const API_QuantityPar				*params,
																		 GS::Array<API_Quantities>			*quantities,
																		 const API_QuantitiesMask			*mask = nullptr);


/**
 * @brief Returns information of the given elements surfaces.
 * @ingroup Element
 * @param elemGuids [in] Array of elem guids, to calculate surface informations.
 * @param coverElemGuids [in] Array of elem guids to consider as cover elems, when calculating visible surfaces areas.
 * @param quantities [out] Calculated surface information will be pushed into this array, in the same order as in elemGuids.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Either elemGuids or coverElemGuids or quantities is nullptr
 * @remarks This function is used to get one or more elements surface informations, mainly surface area. When calculating the surface area you can specify which elements are considered as cover elems. The area where a cover elem overlaps the given element will be reduced from the whole surface of the elem.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetSurfaceQuantities-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetSurfaceQuantities	(const GS::Array<API_Guid>				*elemGuids,
								  											 const GS::Array<API_Guid>				*coverElemGuids,
																			 GS::Array<API_ElemPartSurfaceQuantity>	*quantities);


/**
 * @brief Returns property objects of the element.
 * @ingroup Element
 * @ingroup Property
 * @param elemHead [in] The element to get the properties for.
 * @param propRefs [out] List of property objects.
 * @param nProp [out] Number of the property objects.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - propRefs or nProp is nullptr
 * 			- APIERR_BADID - Incorrect elemHead was specified
 * 			- APIERR_MEMFULL - Not enough memory to get the properties
 * @remarks This function is used to get the list of property objects for a linked element. The properties can be associated with construction elements by criteria or by individual direct assignment. This applies to all construction elements.
 * 			From Archicad 9 the linked properties of both an element instance and the element defaults can be accessed with two new functions: @ref ACAPI_ElementLink_GetLinkedPropertyObjects and @ref ACAPI_ElementLink_SetLinkedPropertyObjects.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetPropertyObjects-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetPropertyObjects	(const API_Elem_Head		*elemHead,
																			 API_PropertyObjectRefType	***propRefs,
																			 Int32						*nProp);


/**
 * @brief Returns the components of the element.
 * @ingroup Element
 * @param elemHead [in] The element whose components you want to obtain.
 * @param compRefs [out] List of the components.
 * @param nComp [out] Number of the components.
 * @return
 * 			- APIERR_BADPARS - compRefs is nullptr or nComp is nullptr.
 * 			- APIERR_BADID - Incorrect elemHead was specified.
 * 			- APIERR_MEMFULL - Not enough memory to get the components.
 * @remarks This function is obsolete. Use the new component API instead.
 * 			This function is used to get information for every component of an element. These components are in the property objects of the element. This applies to all the construction elements.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetComponents_Obsolete-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetComponents_Obsolete	(const API_Elem_Head			*elemHead,
																				 API_Obsolete_ComponentRefType	***compRefs,
																				 Int32							*nComp);


/**
 * @brief Returns the descriptors of an element.
 * @ingroup Element
 * @ingroup LibraryManagement
 * @param elemHead [in] The element you want to get the descriptors for.
 * @param descRef [out] List of the descriptors.
 * @param nDesc [out] Number of the descriptors in the list.
 * @return
 * 			- APIERR_BADPARS - descRef is nullptr or nDesc is nullptr.
 * 			- APIERR_BADID - Incorrect elemHead was specified.
 * 			- APIERR_MEMFULL - Not enough memory to get the descriptors.
 * @remarks This function is used to get information for every descriptor of an element. These descriptors are in the property objects of the element. This applies to all the construction elements.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetDescriptors-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetDescriptors			(const API_Elem_Head		*elemHead,
																				 API_DescriptorRefType		***descRef,
																				 Int32						*nDesc);


/**
 * @brief Virtually draws the shape of an element
 * @ingroup DrawingPrimitive
 * @param elemHead [in] Identifies the element to be processed.
 * @param shapePrimsProc [in] The function to be called to process the element primitives.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter is nullptr; element
 * 			- APIERR_BADDATABASE - Not the appropriate database was open for the operation. For example you tried to access a 2D element while the 3D window - and also the 3D database - was active.
 * 			- APIERR_BADID - The element type is invalid,
 * @remarks This function draws the element from drawing primitives (see @ref API_PrimElement), using the shapePrimsProc function.
 * 			The @ref API_PrimElement (the first parameter of ShapePrimsProc) can also contain a control code; these codes mark the beginning and the end of the drawing of sub-parts. It can also contain information on connected elements (e.g. for walls, you get the indices of windows and doors in that wall).
 * 			These drawing procedures can not be nested.
 * 			To enable Renovation Overrides or Graphical Overrides see @ref ACAPI_GraphicalOverride_EnableRenovationOverride and @ref ACAPI_GraphicalOverride_EnableVisualOverride.
 * 			The @ref API_PrimElement (the first parameter of ShapePrimsProc) can also contain a control code; these codes mark the beginning and the end of the drawing of sub-parts. It can also contain information on connected elements (e.g. for walls, you get the indices of windows and doors in that wall).
 * 			These drawing procedures can not be nested.
 * 			To enable Renovation Overrides or Graphical Overrides see @ref ACAPI_GraphicalOverride_EnableRenovationOverride and @ref ACAPI_GraphicalOverride_EnableVisualOverride.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_DrawingPrimitive_ShapePrims-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_DrawingPrimitive_ShapePrims				(const API_Elem_Head&	elemHead,
																				 ShapePrimsProc			*shapePrimsProc);


/**
 * @brief Virtually draws the shape of an element
 * @ingroup DrawingPrimitive
 * @param elemHead [in] Identifies the element to be processed.
 * @param shapePrimsProc [in] The function to be called to process the element primitives.
 * @param shapePrimsParams [in] Shape primitives parameters structure to process the shape primitives by.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE - Not the appropriate database was open for the operation. For example you tried to access a 2D element while the 3D window - and also the 3D database - was active.
 * 			- APIERR_BADID - The element type is invalid, or the element guid is invalid, or the element type is not supported by the server application
 * 			- APIERR_REFUSEDCMD - This error code is returned when the element specified by the guid parameter is not on the current floor.
 * 			- APIERR_REFUSEDPAR - Elements that cannot be drawn from primitives were specified in the type parameter, for example @c API_CamSetID in Archicad.
 * @remarks This function draws the element from drawing primitives (see @ref API_PrimElement), using the shapePrimsProc function.
 * 			The @ref API_PrimElement (the first parameter of ShapePrimsProc) can also contain a control code; these codes mark the beginning and the end of the drawing of sub-parts. It can also contain information on connected elements (e.g. for walls, you get the indices of windows and doors in that wall).
 * 			These drawing procedures can not be nested.
 * 			To enable Renovation Overrides or Graphical Overrides see @ref ACAPI_GraphicalOverride_EnableRenovationOverride and @ref ACAPI_GraphicalOverride_EnableVisualOverride.
 * 			The @ref API_PrimElement (the first parameter of ShapePrimsProc) can also contain a control code; these codes mark the beginning and the end of the drawing of sub-parts. It can also contain information on connected elements (e.g. for walls, you get the indices of windows and doors in that wall).
 * 			These drawing procedures can not be nested.
 * 			To enable Renovation Overrides or Graphical Overrides see @ref ACAPI_GraphicalOverride_EnableRenovationOverride and @ref ACAPI_GraphicalOverride_EnableVisualOverride.
 */
__APIEXPORT GSErrCode ACAPI_DrawingPrimitive_ShapePrimsExt (const API_Elem_Head&	elemHead,
																	 ShapePrimsProc			*shapePrimsProc,
																	 API_ShapePrimsParams*	shapePrimsParams);


/**
 * @brief Retrieves property objects linked to an element or the element default.
 * @ingroup ElementLink
 * @param head [in] Header of the element (only field guid is used). Properties linked to the default element are retrieved when guid is APINULLGuid
 * @param criteria [out] Determines whether the matching properties by criteria are linked to the element
 * @param inviduallyLibInd [out] Library index of individually assigned property (value zero means no individual property assigned)
 * @param critLibInds [out] Aray of the library indices of linked properties matching the criteria
 * @param nCrits [out] Number of linked properties matching the criteria
 * @return
 * @remarks This function is used to get the list of property objects for a linked element. Properties can be associated with construction elements by criteria and/or by individual direct assignment (at most one individual assignment can be applied to an element). This applies to all types of construction elements. If no element is specified (ie. guid is APINULLGuid), the default settings of the given element type are retrieved.
 * 			Any of the arguments except head can be nullptr, in this case the function retrieves only the rest of the parameters.
 * 			Remember to free the critLibInds array when not needed any more.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ElementLink_GetLinkedPropertyObjects-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ElementLink_GetLinkedPropertyObjects (const API_Elem_Head		*head,
																				bool					*criteria,
																				Int32					*inviduallyLibInd,
																				Int32					**critLibInds,
																				Int32					*nCrits);


/**
 * @brief Link property objects to an element or the element default.
 * @ingroup ElementLink
 * @param head [in] Header of the element (only fields type and guid are used). The setting is applied to element defaults if guid is APINULLGuid.
 * @param criteria [in] Determines whether the matching properties by criteria need to be linked to the element
 * @param inviduallyLibInd [in] Library index of individually selected property to be linked to the element (value zero means no individual property is to be assigned)
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - head is nullptr
 * 			- APIERR_BADID - Incorrect type was specified, or an element with the specified guid was not found.
 * 			- APIERR_MEMFULL - Not enough memory to set the properties
 * @remarks This function is used to link property objects to an element. Properties can be associated with construction elements by criteria and/or by individual direct assignment (at most one individual assignment can be applied to an element). This applies to all types of construction elements. If no element is specified (ie. guid is APINULLGuid), the setting is applied to the defaults of the given element type.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ElementLink_SetLinkedPropertyObjects-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ElementLink_SetLinkedPropertyObjects (API_Elem_Head		*head,
																				bool				criteria,
																				Int32				inviduallyLibInd);


/**
 * @brief Returns the given category of the element.
 * @ingroup Category
 * @param elemGuid [in] Guid of the element whose category you want to obtain.
 * @param elemCategory [in] The category identified by guid or categoryID.
 * @param elemCategoryValue [out] The category value information to be retrieved.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - elemCategoryValue is nullptr or elemCategory is incorrect.
 * 			- APIERR_BADID - Incorrect elemGuid was specified.
 * @remarks This function is used to get category information for an element. For available category types check @ref API_ElemCategoryID.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Category_GetCategoryValue-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Category_GetCategoryValue (const API_Guid&					elemGuid,
																		const API_ElemCategory&			elemCategory,
																		API_ElemCategoryValue*			elemCategoryValue);


/**
 * @brief Returns the given category of the element.
 * @ingroup Category
 * @since Archicad 26
 * @param type [in] Type of the default element whose category you want to obtain.
 * @param elemCategory [in] The category identified by guid or categoryID.
 * @param elemCategoryValue [out] The category value informations to be retrieved.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - elemCategoryValue is nullptr or elemCategory is incorrect.
 * 			- APIERR_BADID - Incorrect type was specified.
 * @remarks This function is used to get category information for a default element. For available category types check @ref API_ElemCategoryID.
 * 			typeID
 * 			variationID
 * @ref API_ElemType
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Category_GetCategoryValueDefault-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Category_GetCategoryValueDefault (const API_ElemType&			type,
																			   const API_ElemCategory&		elemCategory,
																			   API_ElemCategoryValue*		elemCategoryValue);


/**
 * @brief Set the given category of an element.
 * @ingroup Category
 * @param elemGuid [in] GUID of the element.
 * @param elemCategory [in] The category identified by guid or categoryID.
 * @param elemCategoryValue [in] The category value informations to be set.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - elemCategoryValue or elemCategory is incorrect.
 * 			- APIERR_BADID - Incorrect elemGuid was specified.
 * @remarks This function is used to set category information for an element. For available category types see @ref API_ElemCategoryID.
 * 			To get the list of category values in a given category use @ref ACAPI_Category_GetElementCategoryValues.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Category_SetCategoryValue-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Category_SetCategoryValue (const API_Guid&					elemGuid,
																		const API_ElemCategory&			elemCategory,
																		const API_ElemCategoryValue&	elemCategoryValue);


/**
 * @brief Set the given category of a default element.
 * @ingroup Category
 * @since Archicad 26
 * @param type [in] Type of the default element.
 * @param elemCategory [in] The category identified by guid or categoryID.
 * @param elemCategoryValue [in] The category value informations to be set.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - elemCategoryValue or elemCategory is incorrect.
 * 			- APIERR_BADID - Incorrect type was specified.
 * @remarks This function is used to set category information for a default element. For available category types see `API_ElemCategoryID`.
 * 			To get the list of category values in a given category use @ref ACAPI_Category_GetElementCategoryValues.
 * 			From version 26 the typeID and variationID parameters were merged into a single @ref API_ElemType parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Category_SetCategoryValueDefault-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Category_SetCategoryValueDefault (const API_ElemType&				type,
																			   const API_ElemCategory&			elemCategory,
																			   const API_ElemCategoryValue&		elemCategoryValue);

/* -- Element Composition ----------------- */


/**
 * @brief Trim elements given in the array with Roof(s) and/or Shell(s) are contained in the array.
 * @ingroup Element
 * @param guid_ElementsToTrim [in] Array of GUIDs of the elements to trim with shells and roofs are contained in this array.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NEEDSUNDOSCOPE - The function must be undoable, it wasn't called from an undoable command scope.
 * 			- APIERR_BADDATABASE, APIERR_NOTMINE - The function cannot operate on the current database.
 * 			- APIERR_BADINDEX - One or more of the passed IDs are invalid.
 * 			- APIERR_BADPARS - Invalid value passed in the guid_ElementsToTrim parameter.
 * 			- APIERR_BADELEMENTTYPE - There is element in the array, which is not construction element type, or there is no Roof or Shell element in the array to trim with.
 * @remarks This function trims elements given in the array with Roof(s) and/or Shell(s) are contained in the array.
 */
__APIEXPORT GSErrCode ACAPI_Element_Trim_Elements			(const GS::Array<API_Guid>&	guid_ElementsToTrim);


/**
 * @brief Trim elements given in the array with the given Roof or Shell with the type of trim.
 * @ingroup Element
 * @param guid_ElementsToTrim [in] Array of GUIDs of the elements to trim with the given Shell or Roof.
 * @param guid_Element [in] The trimming element GUID.
 * @param trimType [in] The type of the trimming.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NEEDSUNDOSCOPE - The function must be undoable, it wasn't called from an undoable command scope.
 * 			- APIERR_BADDATABASE, APIERR_NOTMINE - The function cannot operate on the current database.
 * 			- APIERR_BADINDEX - One or more of the passed IDs are invalid.
 * 			- APIERR_BADPARS - Invalid value passed in the guid_ElementsToTrim parameter or invalid value passed in the trimType parameter.
 * 			- APIERR_BADELEMENTTYPE - There is element in the array, which is not construction element type or the trimming element is not Roof or Shell.
 * @remarks This function trims elements given in the array with the given Roof or Shell.
 */
__APIEXPORT GSErrCode ACAPI_Element_Trim_ElementsWith		(const GS::Array<API_Guid>&	guid_ElementsToTrim,
																			 const API_Guid&			guid_Element,
																			 API_TrimTypeID				trimType);


/**
 * @brief Remove the trimming connection from the given elements.
 * @ingroup Element
 * @param guid_Element1 [in] The first element GUID.
 * @param guid_Element2 [in] The second element GUID.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NEEDSUNDOSCOPE - The function must be undoable, it wasn't called from an undoable command scope.
 * 			- APIERR_BADDATABASE, APIERR_NOTMINE - The function cannot operate on the current database.
 * 			- APIERR_BADINDEX - One or more of the passed IDs are invalid.
 * 			- APIERR_BADELEMENTTYPE - One of the elements is not construction element type or there is no given Roof or Shell.
 * @remarks This function removes trimming connection between the elements.
 */
__APIEXPORT GSErrCode ACAPI_Element_Trim_Remove			(const API_Guid&			guid_Element1,
																			 const API_Guid&			guid_Element2);


/**
 * @brief Get the type of trimming connection between the given elements.
 * @ingroup Element
 * @param guid_Element1 [in] The first element GUID.
 * @param guid_Element2 [in] The second element GUID.
 * @param trimType [out] The type of the trimming.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE, APIERR_NOTMINE - The function cannot operate on the current database.
 * 			- APIERR_BADINDEX - One or more of the passed IDs are invalid.
 * 			- APIERR_BADELEMENTTYPE - One of the elements is not construction element type or there is no given Roof or Shell.
 * @remarks This function gets the type of trimming connection between the elements.
 */
__APIEXPORT GSErrCode ACAPI_Element_Trim_GetTrimType		(const API_Guid&			guid_Element1,
																			 const API_Guid&			guid_Element2,
																			 API_TrimTypeID*			trimType);


/**
 * @brief Get the trimmed elements with the given Roof or Shell in the array.
 * @ingroup Element
 * @param guid_Element [in] The element GUID.
 * @param guid_TrimmedElements [out] Array of GUIDs of the elements are trimmed with the given Shell or Roof.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE, APIERR_NOTMINE - The function cannot operate on the current database.
 * 			- APIERR_BADINDEX - One or more of the passed IDs are invalid.
 * 			- APIERR_BADPARS - Invalid value passed in the guid_Element parameter.
 * 			- APIERR_BADELEMENTTYPE - The given element is not Roof or Shell element.
 * @remarks This function gets elements are trimmed with the given Roof or Shell.
 */
__APIEXPORT GSErrCode ACAPI_Element_Trim_GetTrimmedElements	(const API_Guid&		guid_Element,
																				 GS::Array<API_Guid>*	guid_TrimmedElements);


/**
 * @brief Get the trimming elements of the given element in the array.
 * @ingroup Element
 * @param guid_Element [in] The element GUID.
 * @param guid_TrimmingElements [out] Array of GUIDs of the elements are trimming the given element.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE, APIERR_NOTMINE - The function cannot operate on the current database.
 * 			- APIERR_BADINDEX - One or more of the passed IDs are invalid.
 * 			- APIERR_BADPARS - Invalid value passed in the guid_Element parameter.
 * 			- APIERR_BADELEMENTTYPE - The given element is not construction element.
 * @remarks This function gets elements are trimming the given element.
 */
__APIEXPORT GSErrCode ACAPI_Element_Trim_GetTrimmingElements	(const API_Guid&		guid_Element,
																				 GS::Array<API_Guid>*	guid_TrimmingElements);


/**
 * @brief Merge elements given in the array.
 * @ingroup Element
 * @param guid_ElementsToMerge [in] Array of GUIDs of the elements to merge.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NEEDSUNDOSCOPE - The function must be undoable, it wasn't called from an undoable command scope.
 * 			- APIERR_BADDATABASE, APIERR_NOTMINE - The function cannot operate on the current database.
 * 			- APIERR_BADINDEX - One or more of the passed IDs are invalid.
 * 			- APIERR_BADPARS - Invalid value passed in the guid_ElementsToMerge parameter.
 * 			- APIERR_BADELEMENTTYPE - There is element in the array, which is not construction element type.
 * @remarks This function merges elements given in the array.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_Merge_Elements-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_Merge_Elements			(const GS::Array<API_Guid>&	guid_ElementsToMerge);


/**
 * @brief Get the merged elements of the given element in the array.
 * @ingroup Element
 * @param guid_Element [in] The element GUID.
 * @param guid_MergedElements [out] Array of GUIDs of the elements are merged with the given element.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE, APIERR_NOTMINE - The function cannot operate on the current database.
 * 			- APIERR_BADINDEX - One or more of the passed IDs are invalid.
 * 			- APIERR_BADPARS - Invalid value passed in the guid_Element parameter.
 * 			- APIERR_BADELEMENTTYPE - The given element is not construction element.
 * @remarks This function gets elements are merged with the given element.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_Merge_GetMergedElements-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_Merge_GetMergedElements	(const API_Guid&		guid_Element,
																				 GS::Array<API_Guid>*	guid_MergedElements);


/**
 * @brief Remove the merge connection from the given elements.
 * @ingroup Element
 * @param guid_Element1 [in] The first element GUID.
 * @param guid_Element2 [in] The second element GUID.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NEEDSUNDOSCOPE - The function must be undoable, it wasn't called from an undoable command scope.
 * 			- APIERR_BADDATABASE, APIERR_NOTMINE - The function cannot operate on the current database.
 * 			- APIERR_BADINDEX - One or more of the passed IDs are invalid.
 * 			- APIERR_BADELEMENTTYPE - One of the elements is not construction element type.
 * @remarks This function removes merge connection between the elements.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_Merge_Remove-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_Merge_Remove				(const API_Guid&	guid_Element1,
																				 const API_Guid&	guid_Element2);

/* -- IFC --------------------------------- */


/**
 * @brief Get IFC Identifier of an element
 * @warning Deprecated function, will be deleted in the upcoming version!
 * @ingroup Element
 * @ingroup IFC
 * @since Archicad 26
 * @param elementID [in] GUID of the element
 * @param archicadIFCID [out] Archicad IFC ID of the element
 * @param externalIFCID [out] External IFC ID of the element
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - Invalid value passed in the elementID parameter.
 * 			- APIERR_MODULNOTINSTALLED - IFC add-on is not present.
 * @remarks This function returns the IFC Identifier of an element. There are two type of identifiers:
 * 			- Archicad IFC ID - during an IFC export this value will be written to GlobalId attribute and can be seen in IFC Manager.
 * 			- External IFC ID - if the element is originally from IFC then it contains the GlobalId. If it isn't then it is APINULLGuid. It can be seen in IFC Manager also.
 */
[[deprecated("Use IFCAPI::v1::GetGlobalId and IFCAPI::v1::GetExternalGlobalId instead.")]]
__APIEXPORT GSErrCode ACAPI_Element_GetIFCIdentifier	(const API_Guid&				elementID,
														 API_Guid&						archicadIFCID,
														 API_Guid&						externalIFCID);


/**
 * @brief Get elements having a certain IFC identifier
 * @warning Deprecated function, will be deleted in the upcoming version!
 * @ingroup Element
 * @ingroup IFC
 * @since Archicad 26
 * @param archicadIFCID [in] Archicad IFC ID - it can be nullptr
 * @param externalIFCID [in] External IFC ID - it can be nullptr
 * @param elements [out] GUID of the elements
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Both archicadIFCID and externalIFCID are nullptr or elements parameter is nullptr.
 * 			- APIERR_MODULNOTINSTALLED - IFC add-on is not present.
 * @remarks This function searches for elements having the indicated IFC Guid.
 * 			- only archicadIFCID contains value - it searches for an element having the indicated Archicad IFC ID. The elements can have maximum 1 element. only externalIFCID contains value - it searches for elements having the indicated External IFC ID. The elements can have more then one element. both archicadIFCID and externalIFCID contains value - it searches for an element having the indicated Archicad IFC ID and External IFC ID. The elements can have maximum 1 element. both input parameters are nullptr - it returns APIERR_BADPARS.
 * 			- only externalIFCID contains value - it searches for elements having the indicated External IFC ID. The elements can have more then one element. both archicadIFCID and externalIFCID contains value - it searches for an element having the indicated Archicad IFC ID and External IFC ID. The elements can have maximum 1 element. both input parameters are nullptr - it returns APIERR_BADPARS.
 * 			- both archicadIFCID and externalIFCID contains value - it searches for an element having the indicated Archicad IFC ID and External IFC ID. The elements can have maximum 1 element. both input parameters are nullptr - it returns APIERR_BADPARS.
 * 			- both input parameters are nullptr - it returns APIERR_BADPARS.
 */
[[deprecated("Use IFCAPI::v1::FindElementsByGlobalId instead.")]]
__APIEXPORT GSErrCode ACAPI_Element_GetElemListByIFCIdentifier	(const API_Guid*				archicadIFCID,
																 const API_Guid*				externalIFCID,
																 GS::Array<API_Guid>&			elements);


/**
 * @brief Get IFC properties of an element
 * @warning Deprecated function, will be deleted in the upcoming version!
 * @ingroup Element
 * @ingroup IFC
 * @param guid_Element [in] GUID of the element
 * @param storedOnly [in] Get only the core data without the derived content, must be false is most cases
 * @param properties [out] IFC properties of the element
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Invalid value passed in the guid_Element parameter or properties is nullptr.
 * 			- APIERR_MODULNOTINSTALLED - IFC add-on is not present.
 * @remarks This function returns the IFC properties of an element.
 */
[[deprecated("Use IFCAPI::v1::GetLocalProperties or IFCAPI::v1::GetPreviewProperties instead.")]]
__APIEXPORT GSErrCode ACAPI_Element_GetIFCProperties	(const API_Guid&				guid_Element,
														 bool							storedOnly,
														 GS::Array<API_IFCProperty>*	properties);


/**
 * @brief Set IFC property of an element
 * @warning Deprecated function, will be deleted in the upcoming version!
 * @ingroup Element
 * @ingroup IFC
 * @param guid_Element [in] GUID of the element
 * @param property [in] IFC property to add or modify.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Invalid value passed in the guid_Element parameter or property is not correct.
 * 			- APIERR_MODULNOTINSTALLED - IFC add-on is not present.
 * @remarks This function sets the IFC property of an element. If a property with the given property name and propertyset name already exists for the element, this command will change it. If a property is not editable on the user interface, must not be changed. For a successful setting, the property must be set correctly explained in the @ref API_IFCProperty structure. The model may contain GDL objects with APPLICATION_QUERYs which display IFC data. It is the developer's responsability to refresh the views after modifying IFC data through API functions. See: @c ACAPI_Automation - @ref ACAPI_View_Rebuild function.
 */
[[deprecated("See IFCAPI::v1::RegisterPropertyHook for dynamic property manipulation with hooks.")]]
__APIEXPORT GSErrCode ACAPI_Element_SetIFCProperty		(const API_Guid&				guid_Element,
														 const API_IFCProperty&			property);


/**
 * @brief Remove IFC property of an element
 * @warning Deprecated function, will be deleted in the upcoming version!
 * @ingroup Element
 * @ingroup IFC
 * @param guid_Element [in] GUID of the element
 * @param property [in] IFC property to remove.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Invalid value passed in the guid_Element parameter or property is not correct.
 * 			- APIERR_MODULNOTINSTALLED - IFC add-on is not present.
 * @remarks If a property with the given property name and propertyset name exists for the element, this function will remove it. If a property is not editable on the user interface, cannot be removed. For a successful removal, the property.head must be set correctly explained in the @ref API_IFCPropertyHead structure. The model may contain GDL objects with APPLICATION_QUERYs which display IFC data. It is the developer's responsability to refresh the views after modifying IFC data through API functions. See: @c ACAPI_Automation - @ref ACAPI_View_Rebuild function.
 */
[[deprecated]]
__APIEXPORT GSErrCode ACAPI_Element_RemoveIFCProperty	(const API_Guid&				guid_Element,
														 const API_IFCProperty&			property);


/**
 * @brief Get IFC attributes of an element
 * @warning Deprecated function, will be deleted in the upcoming version!
 * @ingroup Element
 * @ingroup IFC
 * @param guid_Element [in] GUID of the element
 * @param storedOnly [in] Get only the core data without the derived content, must be false is most cases
 * @param attributes [out] IFC attributes of the element
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Invalid value passed in the guid_Element parameter or attributes is nullptr.
 * 			- APIERR_MODULNOTINSTALLED - IFC add-on is not present.
 * @remarks This function returns the IFC attributes of an element.
 */
[[deprecated("Use IFCAPI::v1::GetAttributes instead.")]]
__APIEXPORT GSErrCode ACAPI_Element_GetIFCAttributes	(const API_Guid&				guid_Element,
														 bool							storedOnly,
														 GS::Array<API_IFCAttribute>*	attributes);


/**
 * @brief Set IFC attribute of an element
 * @warning Deprecated function, will be deleted in the upcoming version!
 * @ingroup Element
 * @ingroup IFC
 * @param guid_Element [in] GUID of the element
 * @param attribute [in] IFC attribute to modify.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Invalid value passed in the guid_Element parameter or attribute is not correct.
 * 			- APIERR_MODULNOTINSTALLED - IFC add-on is not present.
 * @remarks This function sets the IFC attribute of an element. If an attribute with the given name and type exists for the element, this command will change it. If an attribute is not editable on the user interface, must not be changed. For a successful change, the attribute must be set correctly explained in the @ref API_IFCAttribute structure. The model may contain GDL objects with APPLICATION_QUERYs which display IFC data. It is the developer's responsability to refresh the views after modifying IFC data through API functions. See: @c ACAPI_Automation - @ref ACAPI_View_Rebuild function.
 */
[[deprecated("See IFCAPI::v1::RegisterAttributeHook for dynamic attribute manipulation with hooks.")]]
__APIEXPORT GSErrCode ACAPI_Element_SetIFCAttribute	(const API_Guid&				guid_Element,
													 const API_IFCAttribute&		attribute);


/**
 * @brief Get IFC classificationreferences of an element
 * @warning Deprecated function, will be deleted in the upcoming version!
 * @ingroup Element
 * @ingroup IFC
 * @param guid_Element [in] GUID of the element
 * @param storedOnly [in] Get only the core data without the derived content, must be false is most cases
 * @param classificationReferences [out] IFC classificationreferences of the element
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Invalid value passed in the guid_Element parameter or classificationReferences is nullptr.
 * 			- APIERR_MODULNOTINSTALLED - IFC add-on is not present.
 * @remarks This function returns the IFC classificationreferences of an element.
 */
[[deprecated("Use IFCAPI::v1::GetLocalClassificationReferences or IFCAPI::v1::GetPreviewClassificationReferences instead.")]]
__APIEXPORT GSErrCode ACAPI_Element_GetIFCClassificationReferences	(const API_Guid&							guid_Element,
																	 bool										storedOnly,
																	 GS::Array<API_IFCClassificationReference>*	classificationReferences);


/**
 * @brief Set IFC classificationreference of an element
 * @warning Deprecated function, will be deleted in the upcoming version!
 * @ingroup Element
 * @ingroup IFC
 * @param guid_Element [in] GUID of the element
 * @param classificationReference [in] IFC classificationreference to add or modify.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Invalid value passed in the guid_Element parameter or classificationReference is not correct.
 * 			- APIERR_MODULNOTINSTALLED - IFC add-on is not present.
 * @remarks This function sets the IFC classificationreference of an element. If a classificationreference with the given referencename already exists for the element, this command will change it. For a successful setting, the classificationreference must be set correctly explained in the @ref API_IFCClassificationReference structure. The model may contain GDL objects with APPLICATION_QUERYs which display IFC data. It is the developer's responsability to refresh the views after modifying IFC data through API functions. See: @c ACAPI_Automation - @ref ACAPI_View_Rebuild function.
 */
[[deprecated("See IFCAPI::v1::RegisterClassificationReferenceHook for dynamic classification reference manipulation with hooks.")]]
__APIEXPORT GSErrCode ACAPI_Element_SetIFCClassificationReference	(const API_Guid&						guid_Element,
																	 const API_IFCClassificationReference&	classificationReference);


/**
 * @brief Remove IFC classificationreference of an element
 * @warning Deprecated function, will be deleted in the upcoming version!
 * @ingroup Element
 * @ingroup IFC
 * @param guid_Element [in] GUID of the element
 * @param classificationReference [in] IFC classificationreference to remove.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Invalid value passed in the guid_Element parameter or classificationReference is not correct.
 * 			- APIERR_MODULNOTINSTALLED - IFC add-on is not present.
 * @remarks If a classificationreference with the given referencename exists for the element, this function will remove it. For a successful removal, the classificationReference.referenceName must be set correctly explained in the @ref API_IFCClassificationReference structure. The model may contain GDL objects with APPLICATION_QUERYs which display IFC data. It is the developer's responsability to refresh the views after modifying IFC data through API functions. See: @c ACAPI_Automation - @ref ACAPI_View_Rebuild function.
 */
[[deprecated]]
__APIEXPORT GSErrCode ACAPI_Element_RemoveIFCClassificationReference	(const API_Guid&						guid_Element,
																		 const API_IFCClassificationReference&	classificationReference);


/* -- Classification related functions ----------------- */


/**
 * @brief Retrieves all of the classifications of an element.
 * @ingroup Element
 * @ingroup Classification
 * @param elemGuid [in] The guid of the element.
 * @param systemItemPairs [out] A list of classification system and classification item guid pairs, that represent the element's classifications.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The elemGuid did not refer to a valid element.
 */
__APIEXPORT GSErrCode ACAPI_Element_GetClassificationItems	(const API_Guid& elemGuid, GS::Array<GS::Pair<API_Guid, API_Guid>>& systemItemPairs);


/**
 * @brief Retrieves all of the classifications of a default elem.
 * @ingroup Element
 * @ingroup Classification
 * @since Archicad 26
 * @param type [in] Type of the default element.
 * @param systemItemPairs [out] A list of classification system and classification item guid pairs, that represent the element's classifications.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The type did not refer to a valid default element.
 * @remarks From version 26 the typeID and variationID parameters were merged into a single @ref API_ElemType parameter.
 */
__APIEXPORT GSErrCode ACAPI_Element_GetClassificationItemsDefault		(const API_ElemType&						type,
																						 GS::Array<GS::Pair<API_Guid, API_Guid>>&	systemItemPairs);


/**
 * @brief Retrieves all of the classifications of an attribute.
 * @ingroup Attribute
 * @param attrHead [in] Header of the attribute. The attribute is identified by typeID and index
 * @param systemItemPairs [out] A list of classification system and classification item guid pairs, that represent the attribute's classifications.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADINDEX - The attrHead did not refer to a valid attribute.
 * 			- APIERR_GENERAL - Internal error.
 */
__APIEXPORT GSErrCode ACAPI_Attribute_GetClassificationItems (const API_Attr_Head& attrHead, GS::Array<GS::Pair<API_Guid, API_Guid>>& systemItemPairs);



/**
 * @brief Retrieves a classification of an elem in a given classification system.
 * @ingroup Element
 * @ingroup Classification
 * @param elemGuid [in] The guid of the element.
 * @param systemGuid [in] The guid of the classification system in which the classification item should be retrieved.
 * @param item [out] The retrieved classification item (empty with null guid if the elem doesn't have a classification in the given system).
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The elemGuid did not refer to a valid element or systemGuid did not refer to a valid classification system.
 */
__APIEXPORT GSErrCode ACAPI_Element_GetClassificationInSystem (const API_Guid& elemGuid, const API_Guid& systemGuid, API_ClassificationItem& item);


/**
 * @brief Retrieves a classification of a default elem in a given classification system.
 * @ingroup Element
 * @ingroup Classification
 * @since Archicad 26
 * @param type [in] Type of the default element.
 * @param systemGuid [in] The guid of the classification system in which the classification item should be retrieved.
 * @param item [out] The retrieved classification item (empty with null guid if the elem doesn't have a classification in the given system).
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The type did not refer to a valid default element or systemGuid did not refer to a valid classification system.
 * @remarks From version 26 the typeID and variationID parameters were merged into a single @ref API_ElemType parameter.
 */
__APIEXPORT GSErrCode ACAPI_Element_GetClassificationInSystemDefault	(const API_ElemType&		type,
																						 const API_Guid&			systemGuid,
																						 API_ClassificationItem&	item);


/**
 * @brief Retrieves a classification of an attribute in a given classification system.
 * @ingroup Attribute
 * @param attrHead [in] Header of the attribute. The attribute is identified by typeID and index
 * @param systemGuid [in] The guid of the classification system in which the classification item should be retrieved.
 * @param item [out] The retrieved classification item (empty with null guid if the elem doesn't have a classification in the given system).
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADINDEX - The attrHead did not refer to a valid attribute.
 * 			- APIERR_BADID - Inexistent classification system.
 */
__APIEXPORT GSErrCode ACAPI_Attribute_GetClassificationInSystem (const API_Attr_Head& attrHead, const API_Guid& systemGuid, API_ClassificationItem& item);


/**
 * @brief Classifies an element.
 * @ingroup Element
 * @param elemGuid [in] The identifier of the element which should receive the new classification.
 * @param itemGuid [in] The guid of the classification item, that should be added to the element.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The elemGuid did not refer to a valid element or itemGuid did not refer to a valid classification item.
 * 			- APIERR_READONLY - The element can not be modified (i.e. from a hotlink) or you do not have the right to classify elements in the current teamwork plan.
 * 			- APIERR_BADCLASSIFICATION - The classification item is not available for the given element.
 */
__APIEXPORT GSErrCode ACAPI_Element_AddClassificationItem		(const API_Guid& elemGuid, const API_Guid& itemGuid);


/**
 * @brief Classifies an element.
 * @ingroup Element
 * @since Archicad 26
 * @param type [in] Type of the default element.
 * @param itemGuid [in] The guid of the classification item, that should be added to the element.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The type did not refer to a valid default element or itemGuid did not refer to a valid classification item.
 * 			- APIERR_READONLY - The element can not be modified (i.e. from a hotlink) or you do not have the right to classify elements in the current teamwork plan.
 * 			- APIERR_BADCLASSIFICATION - The classification item is not available for the given element.
 * @remarks From version 26 the typeID and variationID parameters were merged into a single @ref API_ElemType parameter.
 */
__APIEXPORT GSErrCode ACAPI_Element_AddClassificationItemDefault	  (const API_ElemType& type, const API_Guid& itemGuid);


/**
 * @brief Classifies an attribute.
 * @ingroup Attribute
 * @param attrHead [in] Header of the attribute. The attribute is identified by typeID and index
 * @param itemGuid [in] The guid of the classification item, that should be added to the element.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADINDEX - The attrHead did not refer to a valid attribute.
 * 			- APIERR_READONLY - The attribute can not be modified (i.e. from a hotlink) or you do not have the right to classify attributes in the current teamwork plan.
 * 			- APIERR_BADID - Inexistent classification item.
 * 			- APIERR_BADCLASSIFICATION - The classification item is not available for the given attribute.
 */
__APIEXPORT GSErrCode ACAPI_Attribute_AddClassificationItem (const API_Attr_Head& attrHead, const API_Guid& itemGuid);


/**
 * @brief Removes a classification from an element.
 * @ingroup Element
 * @ingroup Classification
 * @param elemGuid [in] The identifier of the element whose classification should be removed.
 * @param itemGuid [in] The guid of the classification item, that should be removed from the element.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The elemGuid did not refer to a valid element or itemGuid did not refer to a valid classification item.
 * 			- APIERR_BADPARS - The element did not have the specified classification.
 * 			- APIERR_READONLY - The element can not be modified (i.e. from a hotlink) or you do not have the right to remove classifications from elements in the current teamwork plan.
 */
__APIEXPORT GSErrCode ACAPI_Element_RemoveClassificationItem	(const API_Guid& elemGuid, const API_Guid& itemGuid);


/**
 * @brief Removes a classification from an element.
 * @ingroup Element
 * @ingroup Classification
 * @since Archicad 26
 * @param type [in] Type of the default element.
 * @param itemGuid [in] The guid of the classification item, that should be removed from the element.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The type did not refer to a valid default element or itemGuid did not refer to a valid classification item.
 * 			- APIERR_BADPARS - The element did not have the specified classification.
 * 			- APIERR_READONLY - The element can not be modified (i.e. from a hotlink) or you do not have the right to remove classifications from elements in the current teamwork plan.
 * @remarks From version 26 the typeID and variationID parameters were merged into a single @ref API_ElemType parameter.
 */
__APIEXPORT GSErrCode ACAPI_Element_RemoveClassificationItemDefault (const API_ElemType& type, const API_Guid& itemGuid);


/**
 * @brief Removes a classification from an attribute.
 * @ingroup Attribute
 * @param attrHead [in] Header of the attribute. The attribute is identified by typeID and index
 * @param itemGuid [in] The guid of the classification item, that should be removed from the attribute.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADINDEX - The attrHead did not refer to a valid attribute.
 * 			- APIERR_READONLY - The attribute can not be modified (i.e. from a hotlink) or you do not have the right to remove classifications from attributes in the current teamwork plan.
 * 			- APIERR_BADID - Inexistent classification item.
 * 			- APIERR_BADPARS - The attribute did not have the specified classification.
 */
__APIEXPORT GSErrCode ACAPI_Attribute_RemoveClassificationItem (const API_Attr_Head& attrHead, const API_Guid& itemGuid);


/**
 * @brief Tells whether a classification item is visible for an element.
 * @ingroup Element
 * @ingroup Classification
 * @param elemGuid [in] The element GUID to search for.
 * @param classificationGuid [in] The classification item GUID to search for.
 * @return
 * 			- true - The given classification item is visible for the element. It can return true even if the parent of the classification item is hidden.
 * 			- false - The given classification item is not visible for the element or invalid parameters.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_IsClassificationItemVisible-Example-Snippet
 */
__APIEXPORT bool ACAPI_Element_IsClassificationItemVisible	(const API_Guid&						elemGuid,
																					 const API_Guid&						classificationGuid);


/**
 * @brief Tells whether a classification item is visible for an element default.
 * @ingroup Element
 * @ingroup Classification
 * @since Archicad 26
 * @param type [in] Type of the default element.
 * @param classificationGuid [in] The classification item GUID to search for.
 * @return
 * 			- true - The given classification item is visible for the element default. It can return true even if the parent of the classification item is hidden.
 * 			- false - The given classification item is not visible for the element default or invalid parameters.
 * @remarks From version 26 the typeID and variationID parameters were merged into a single @ref API_ElemType parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_IsClassificationItemVisibleDefault-Example-Snippet
 */
__APIEXPORT bool ACAPI_Element_IsClassificationItemVisibleDefault   (const API_ElemType&				type,
																							const API_Guid&					classificationGuid);


/**
 * @brief Tells whether a classification item is visible for an attribute.
 * @ingroup Attribute
 * @param attrHead [in] Header of the attribute. The attribute is identified by typeID and index
 * @param classificationGuid [in] The classification item GUID to search for.
 * @return
 * 			- true - The given classification item is visible for the attribute. It can return true even if the parent of the classification item is hidden.
 * 			- false - The given classification item is not visible for the attribute or invalid parameters.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Attribute_IsClassificationItemVisible-Example-Snippet
 */
__APIEXPORT bool ACAPI_Attribute_IsClassificationItemVisible (const API_Attr_Head& attrHead, const API_Guid& classificationGuid);


/**
 * @brief Query elements with the given classification.
 * @ingroup Element
 * @param classificationItemGuid [in] The identifier of the classification item.
 * @param elemGuids [out] The identifiers of the elements with the given classification.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The classificationItemGuid did not refer to a valid classification item.
 */
__APIEXPORT GSErrCode ACAPI_Element_GetElementsWithClassification (const API_Guid&		classificationItemGuid,
																					 GS::Array<API_Guid>&	elemGuids);

/* -- Property related functions ----------------- */


/**
 * @brief Retrieves all of the property definitions that are available for an element.
 * @ingroup Element
 * @ingroup Property
 * @param elemGuid [in] The element's identifier to search for.
 * @param filter [in] Filter the list of property definitions (API_PropertyDefinitionFilter_UserDefined, @c API_PropertyDefinitionFilter_BuiltIn, @c API_PropertyDefinitionFilter_All).
 * @param propertyDefinitions [out] Array of property definitions that are available for a classification of the given element.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The elemGuid did not refer to a valid element.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetPropertyDefinitions-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetPropertyDefinitions		(const API_Guid&							elemGuid,
																					 API_PropertyDefinitionFilter				filter,
																					 GS::Array<API_PropertyDefinition>&			propertyDefinitions);


/**
 * @brief Retrieves all of the built-in property definitions that are available for an attribute.
 * @ingroup Attribute
 * @param attrHead [in] Header of the attribute. The attribute is identified by typeID and index
 * @param filter [in] Get the definition for user defined, fundamental or user-level built-in attributes.
 * @param definitions [out] Array of property definitions that are available for a classification of the given
 * 					  attribute.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADINDEX - The attrHead did not refer to a valid attribute.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Attribute_GetPropertyDefinitions-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Attribute_GetPropertyDefinitions		(const API_Attr_Head&						attrHead,
																					 API_PropertyDefinitionFilter				filter,
																					 GS::Array<API_PropertyDefinition>&			definitions);


/**
 * @brief Retrieves the specified property definition's value from the element.
 * @ingroup Element
 * @ingroup Property
 * @param elemGuid [in] The element GUID to search for.
 * @param propertyDefinitionGuid [in] The property definition to get the values for.
 * @param property [out] The value of the requested property.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The elemGuid did not refer to a valid element.
 * 			- APIERR_GENERAL - The propertyDefinitionGuid did not refer to a valid property definition.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetPropertyValue-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetPropertyValue				(const API_Guid&							elemGuid,
																					 const API_Guid&							propertyDefinitionGuid,
																					 API_Property&								property);


/**
 * @brief Retrieves the property value of the property definition.
 * @ingroup Attribute
 * @param attrHead [in] Header of the attribute. The attribute is identified by typeID and index
 * @param propertyDefinitionGuid [in] Property definition.
 * @param property [out] Property value.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADINDEX - The attrHead did not refer to a valid attribute.
 * 			- APIERR_GENERAL - Every other case.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Attribute_GetPropertyValue-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Attribute_GetPropertyValue			(const API_Attr_Head&						attrHead,
																					 const API_Guid&							propertyDefinitionGuid,
																					 API_Property&								property);


/**
 * @brief Retrieves the specified property definitions with values.
 * @ingroup Element
 * @ingroup Property
 * @param elemGuid [in] The element GUID to search for.
 * @param propertyDefinitions [in] The property definitions to get the values for. They are identified through definition.guid.
 * @param properties [out] The definitions and values of the requested properties.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The elemGuid did not refer to a valid element.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetPropertyValues-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetPropertyValues				(const API_Guid&							elemGuid,
																					 const GS::Array<API_PropertyDefinition>&	propertyDefinitions,
																					 GS::Array<API_Property>&					properties);


/**
 * @brief Retrieves the property values of the property definitions.
 * @ingroup Attribute
 * @param attrHead [in] Header of the attribute. The attribute is identified by typeID and index
 * @param propertyDefinitions [in] List of property definitions.
 * @param properties [out] List of property values.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADINDEX - The attrHead did not refer to a valid attribute.
 * 			- APIERR_GENERAL - Every other case.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Attribute_GetPropertyValues-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Attribute_GetPropertyValues			(const API_Attr_Head&						attrHead,
																					 const GS::Array<API_PropertyDefinition>&	propertyDefinitions,
																					 GS::Array<API_Property>&					properties);


/**
 * @brief Retrieves the specified property definitions (defined by their GUIDs) with values.
 * @ingroup Element
 * @ingroup Property
 * @param elemGuid [in] The element GUID to search for.
 * @param propertyDefinitions [in] The property definition GUIDs to get the values for.
 * @param properties [out] The definitions and values of the requested properties.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The elemGuid did not refer to a valid element.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetPropertyValuesByGuid-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetPropertyValuesByGuid		(const API_Guid&							elemGuid,
																					 const GS::Array<API_Guid>&					propertyDefinitions,
																					 GS::Array<API_Property>&					properties);


/**
 * @brief Retrieves the property values of the property definitions.
 * @ingroup Attribute
 * @param attrHead [in] Header of the attribute. The attribute is identified by typeID and index
 * @param propertyDefinitions [in] List of property definitions identified by guid.
 * @param properties [out] List of property values.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADINDEX - The attrHead did not refer to a valid attribute.
 * 			- APIERR_GENERAL - Every other case.
 */
__APIEXPORT GSErrCode ACAPI_Attribute_GetPropertyValuesByGuid		(const API_Attr_Head&						attrHead,
																					 const GS::Array<API_Guid>&					propertyDefinitions,
																					 GS::Array<API_Property>&					properties);


/**
 * @brief Sets the specified property for the given values on an element.
 * @ingroup Element
 * @ingroup Property
 * @param elemGuid [in] The element GUID to search for.
 * @param property [in] Specifies the property to be set.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The elemGuid did not refer to a valid element.
 * 			- APIERR_NOACCESSRIGHT - The current user does not have the right to modify the properties of the specified element on a teamwork server.
 * 			- APIERR_READONLY - Tried to modify a read-only property (for example a property coming from a hotlink).
 * 			- APIERR_BADPROPERTY - The property definition is not available for the given element.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_SetProperty-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_SetProperty					(const API_Guid&							elemGuid,
																					 const API_Property&						property);


/**
 * @brief Sets the property value of the property definition.
 * @ingroup Attribute
 * @param attrHead [in] Header of the attribute. The attribute is identified by typeID and index
 * @param property [in] Property.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADINDEX - The attrHead did not refer to a valid attribute.
 * 			- APIERR_NOACCESSRIGHT - The property can not be modified because you do not have the right to classify attributes in the current teamwork plan.
 * 			- APIERR_READONLY - The proeprty can not be modified because it is readonly.
 * 			- APIERR_BADID - Inexistent propert item.
 * 			- APIERR_GENERAL - Every other case.
 */
__APIEXPORT GSErrCode ACAPI_Attribute_SetProperty					(const API_Attr_Head&						attrHead,
																					 const API_Property&						property);


/**
 * @brief Sets the specified properties for the given values on an element.
 * @ingroup Element
 * @ingroup Property
 * @param elemGuid [in] The element GUID to search for.
 * @param properties [in] Specifies the properties to be set.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The elemGuid did not refer to a valid element.
 * 			- APIERR_NOACCESSRIGHT - The current user does not have the right to modify the properties of the specified element on a teamwork server.
 * 			- APIERR_READONLY - Tried to modify a read-only property (for example a property coming from a hotlink).
 * 			- APIERR_BADPROPERTY - The property definition is not available for the given element.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_SetProperties-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_SetProperties					(const API_Guid&							elemGuid,
																					 const GS::Array<API_Property>&				properties);


/**
 * @brief Sets the specified built-in properties for the given values on an attribute.
 * @ingroup Attribute
 * @param attrHead [in] Header of the attribute. The attribute is identified by typeID and index
 * @param properties [in] Specifies the properties to be set.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - Incorrect attributeTypeID or attributeIndex was specified or one of the property definitions' guid did not refer to a valid object.
 * 			- APIERR_NOACCESSRIGHT - The current user does not have the right to modify the properties of the specified attribute on a teamwork server.
 * 			- APIERR_READONLY - Tried to modify a read-only property (for example a property coming from a hotlink).
 * 			- APIERR_BADPROPERTY - The property definition is not available for the given attribute.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Attribute_SetProperties-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Attribute_SetProperties				(const API_Attr_Head&						attrHead,
																					 const GS::Array<API_Property>&				properties);


/**
 * @brief Retrieves all of the property definitions that are available for an element default.
 * @ingroup Element
 * @ingroup Property
 * @since Archicad 26
 * @param type [in] Type of the default element.
 * @param filter [in] The property definition type to filter for.
 * @param definitions [out] Array of property definitions that are available for a classification of the given element default.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - Incorrect type was specified.
 * @remarks From version 26 the typeID and variationID parameters were merged into a single @ref API_ElemType parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetPropertyDefinitionsOfDefaultElem-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetPropertyDefinitionsOfDefaultElem	(const API_ElemType&				type,
																							 API_PropertyDefinitionFilter		filter,
																							 GS::Array<API_PropertyDefinition>&	definitions);


/**
 * @brief Retrieves the value of the specified property definition.
 * @ingroup Element
 * @ingroup Property
 * @since Archicad 26
 * @param type [in] Type of the default element.
 * @param propertyDefinitionGuid [in] The property definition's GUID to get the value for.
 * @param property [out] The value of the requested property.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - Incorrect type was specified.
 * @remarks From version 26 the typeID and variationID parameters were merged into a single @ref API_ElemType parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetPropertyValueOfDefaultElem-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetPropertyValueOfDefaultElem			(const API_ElemType&				type,
																							 const API_Guid&					propertyDefinitionGuid,
																							 API_Property&						property);


/**
 * @brief Retrieves the values of the specified property definitions.
 * @ingroup Element
 * @ingroup Property
 * @since Archicad 26
 * @param type [in] Type of the default element.
 * @param propertyDefinitions [in] The property definitions (identified by definition.guid) to get the values for.
 * @param properties [out] The definitions and values of the requested properties.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - Incorrect type was specified.
 * @remarks From version 26 the typeID and variationID parameters were merged into a single @ref API_ElemType parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetPropertyValuesOfDefaultElem-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetPropertyValuesOfDefaultElem		(const API_ElemType&						type,
																							 const GS::Array<API_PropertyDefinition>&	propertyDefinitions,
																							 GS::Array<API_Property>&					properties);


/**
 * @brief Retrieves the values of the specified property definitions.
 * @ingroup Element
 * @ingroup Property
 * @since Archicad 26
 * @param type [in] Type of the default element.
 * @param propertyDefinitionGuids [in] The property definition GUIDs to get the values for.
 * @param properties [out] The definitions and values of the requested properties.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - Incorrect type was specified.
 * @remarks From version 26 the typeID and variationID parameters were merged into a single @ref API_ElemType parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetPropertyValuesOfDefaultElemByGuid-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetPropertyValuesOfDefaultElemByGuid	(const API_ElemType&				type,
																							 const GS::Array<API_Guid>&			propertyDefinitionGuids,
																							 GS::Array<API_Property>&			properties);


/**
 * @brief Sets the specified property to the given value on an element default.
 * @ingroup Element
 * @ingroup Property
 * @since Archicad 26
 * @param type [in] Type of the default element.
 * @param property [in] Specifies the property to be set.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - Incorrect type was specified or one of the property definitions' guid did not refer to a valid object.
 * 			- APIERR_NOACCESSRIGHT - The current user does not have the right to modify the properties of the specified element on a teamwork server.
 * 			- APIERR_READONLY - Tried to modify a read-only property (for example a property coming from a hotlink).
 * 			- APIERR_BADPROPERTY - The property definition is not available for the given element.
 * @remarks From version 26 the typeID and variationID parameters were merged into a single @ref API_ElemType parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_SetPropertyOfDefaultElem-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_SetPropertyOfDefaultElem				(const API_ElemType&				type,
																							 const API_Property&				property);


/**
 * @brief Sets the specified properties for the given values on an element default.
 * @ingroup Element
 * @ingroup Property
 * @since Archicad 26
 * @param type [in] Type of the default element.
 * @param properties [in] Specifies the properties to be set.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - Incorrect type was specified or one of the property definitions' guid did not refer to a valid object.
 * 			- APIERR_NOACCESSRIGHT - The current user does not have the right to modify the properties of the specified element on a teamwork server.
 * 			- APIERR_READONLY - Tried to modify a read-only property (for example a property coming from a hotlink).
 * 			- APIERR_BADPROPERTY - The property definition is not available for the given element.
 * @remarks From version 26 the typeID and variationID parameters were merged into a single @ref API_ElemType parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_SetPropertiesOfDefaultElem-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_SetPropertiesOfDefaultElem			(const API_ElemType&				type,
																							 const GS::Array<API_Property>&		properties);


/**
 * @brief Tells whether the value of the property can be modified for the specified element. If the elemGuid argument is APINULLGuid, it tells whether the property definition's default value is editable.
 * @ingroup Element
 * @ingroup Property
 * @param elemGuid [in] The element GUID to search for. It can be APINULLGuid, in this case the property definition's default value is checked.
 * @param propertyGuid [in] The property definition GUID to search for.
 * @return
 * 			- true - The value of the property, or the property definition's default value can be modified.
 * 			- false - The value of the property, or the property definition's default value can not be modified. For example, it is a read-only property, or a User Defined property with expression, which has cyclic property references.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_IsPropertyDefinitionValueEditable-Example-Snippet
 */
__APIEXPORT bool ACAPI_Element_IsPropertyDefinitionValueEditable		(const API_Guid&					elemGuid,
																							 const API_Guid&					propertyGuid);


/**
 * @brief Tells whether the value of the property can be modified for the specified tool default.
 * @ingroup Element
 * @ingroup Property
 * @since Archicad 26
 * @param type [in] Type of the default element.
 * @param propertyGuid [in] The property definition GUID to search for.
 * @return
 * 			- true - The value of the property can be modified.
 * 			- false - The value of the property can not be modified. For example, it is a read-only property, or a User Defined property with expression, which has cyclic property references.
 * @remarks From version 26 the typeID and variationID parameters were merged into a single @ref API_ElemType parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_IsPropertyDefinitionValueEditableDefault-Example-Snippet
 */
__APIEXPORT bool ACAPI_Element_IsPropertyDefinitionValueEditableDefault (const API_ElemType&				type,
																							 	const API_Guid&					propertyGuid);


/**
 * @brief Tells whether a property definition is editable for an attribute.
 * @ingroup Attribute
 * @param attrHead [in] Header of the attribute. The attribute is identified by typeID and index
 * @param propertyGuid [in] The property definition GUID to search for.
 * @return
 * 			- true - The given property definition is editable for the attribute.
 * 			- false - The given property definition is not editable for the attribute or invalid parameters.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Attribute_IsPropertyDefinitionValueEditable-Example-Snippet
 */
__APIEXPORT bool ACAPI_Attribute_IsPropertyDefinitionValueEditable	(const API_Attr_Head&				attrHead,
																							 const API_Guid&					propertyGuid);


/**
 * @brief Tells whether a property definition is available for an element.
 * @ingroup Element
 * @ingroup Property
 * @param elemGuid [in] The element GUID to search for.
 * @param propertyGuid [in] The property definition GUID to search for.
 * @return
 * 			- true - The given property definition is available for the element.
 * 			- false - The given property definition is not available for the element.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_IsPropertyDefinitionAvailable-Example-Snippet
 */
__APIEXPORT bool ACAPI_Element_IsPropertyDefinitionAvailable			(const API_Guid&					elemGuid,
																							 const API_Guid&					propertyGuid);


/**
 * @brief Tells whether a property definition is available for an element default.
 * @ingroup Element
 * @ingroup Property
 * @since Archicad 26
 * @param type [in] Type of the default element.
 * @param propertyGuid [in] The property definition GUID to search for.
 * @return
 * 			- true - The given property definition is available for the element default.
 * 			- false - The given property definition is not available for the element default.
 * @remarks From version 26 the typeID and variationID parameters were merged into a single @ref API_ElemType parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_IsPropertyDefinitionAvailableDefault-Example-Snippet
 */
__APIEXPORT bool ACAPI_Element_IsPropertyDefinitionAvailableDefault (const API_ElemType&					type,
																							const API_Guid&						propertyGuid);


/**
 * @brief Tells whether a property definition is available for an attribute.
 * @ingroup Attribute
 * @param attrHead [in] Header of the attribute. The attribute is identified by typeID and index
 * @param propertyGuid [in] The property definition GUID to search for.
 * @return
 * 			- true - The given property definition is available for the attribute.
 * 			- false - The given property definition is not available for the attribute or invalid parameters.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Attribute_IsPropertyDefinitionAvailable-Example-Snippet
 */
__APIEXPORT bool ACAPI_Attribute_IsPropertyDefinitionAvailable		(const API_Attr_Head&				attrHead,
																							 const API_Guid&					propertyGuid);


/**
 * @brief Tells whether a property definition is visible for an element.
 * @ingroup Element
 * @ingroup Property
 * @param elemGuid [in] The element GUID to search for.
 * @param propertyGuid [in] The property definition GUID to search for.
 * @return
 * 			- true - The given property definition is visible for the element.
 * 			- false - The given property definition is not visible for the element.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_IsPropertyDefinitionVisible-Example-Snippet
 */
__APIEXPORT bool ACAPI_Element_IsPropertyDefinitionVisible			(const API_Guid&					elemGuid,
																							 const API_Guid&					propertyGuid);


/**
 * @brief Tells whether a property definition is visible for an element default.
 * @ingroup Element
 * @ingroup Property
 * @since Archicad 26
 * @param type [in] Type of the default element.
 * @param propertyGuid [in] The property definition GUID to search for.
 * @return
 * 			- true - The given property definition is visible for the element default.
 * 			- false - The given property definition is not visible for the element default.
 * @remarks From version 26 the typeID and variationID parameters were merged into a single @ref API_ElemType parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_IsPropertyDefinitionVisibleDefault-Example-Snippet
 */
__APIEXPORT bool ACAPI_Element_IsPropertyDefinitionVisibleDefault	(const API_ElemType&				type,
																							 const API_Guid&					propertyGuid);


/**
 * @brief Tells whether a property definition is visible for an attribute.
 * @ingroup Attribute
 * @param attrHead [in] Header of the attribute. The attribute is identified by typeID and index
 * @param propertyGuid [in] The property definition GUID to search for.
 * @return
 * 			- true - The given property definition is visible for the attribute.
 * 			- false - The given property definition is not visible for the attribute or invalid parameters.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Attribute_IsPropertyDefinitionVisible-Example-Snippet
 */
__APIEXPORT bool ACAPI_Attribute_IsPropertyDefinitionVisible			(const API_Attr_Head&				attrHead,
																							 const API_Guid&					propertyGuid);


/**
 * @brief Returns the collisions between two groups.
 * @ingroup Element
 * @param guidSet1 [in] The first group of the comparison.
 * @param guidSet2 [in] The second group of the comparison.
 * @param resultArray [out] The result array of the detected collisions.
 * @param apiColDetSettings [in] Collisions detection settings.
 * @return
 * 			- APIERR_GENERAL - Couldn't get the collisions.
 * @remarks This function is used to detect collisions between two groups. You can find an example for this function in the Element_Test addon.
 */
__APIEXPORT GSErrCode ACAPI_Element_GetCollisions (const GS::Array<API_Guid>&					guidSet1,
																	 const GS::Array<API_Guid>&					guidSet2,
																	 GS::Array<GS::Pair<API_CollisionElem, API_CollisionElem>>&	resultArray,
																	 const API_CollisionDetectionSettings&		apiColDetSettings);


/**
 * @brief Sets the value of a property for multiple elements. If the property is not available for at least one of the given element then returns with an error without changing any property value.
 * @ingroup Property
 * @param property [in] The new value of the property.
 * @param elemGuids [in] The array of elements, whose property should be changed.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - One of the elemGuids did not refer to a valid element.
 * 			- APIERR_NOACCESSRIGHT - The current user does not have the right to modify the properties of a specified element on a teamwork server.
 * 			- APIERR_READONLY - Tried to modify a read-only property (for example a property coming from a hotlink).
 * 			- APIERR_BADPROPERTY - The property definition is not available for one of the given elements.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Property_ModifyPropertyValue-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Property_ModifyPropertyValue (const API_Property& property, const GS::Array<API_Guid>& elemGuids);



/**
 * @brief Sets the value of a property for multiple attributes. If the property is not available for at least one of the given attribute then returns with an error without changing any property value.
 * @ingroup Attribute
 * @param property [in] The new value of the property.
 * @param attrHeaders [in] The array of attributes, that the property should be available for.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - Inexistent property item.
 * 			- APIERR_NOACCESSRIGHT - The current user does not have the right to modify the properties of a specified attribute on a teamwork server.
 * 			- APIERR_READONLY - Tried to modify a read-only property (for example a property coming from a hotlink).
 * 			- APIERR_BADPROPERTY - The property definition is not available for one of the given attributes.
 */
__APIEXPORT GSErrCode ACAPI_Attribute_ModifyPropertyValue (const API_Property& property, const GS::Array<API_Attr_Head>& attrHeaders);



/**
 * @brief In teamwork mode this function grants the specified elements to the given user.
 * @ingroup Teamwork
 * @param elemGuids [in] The list of the elements which must be granted.
 * @param toUserId [in] The teamwork owner, to which the objects must be granted.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter elemGuids is empty, contains APINULLGuid, or not all the elements are on the same floor.
 * 			- APIERR_BADID - If any of the elemGuids is not an AddOnObject GUID.
 * @remarks If the function has completed with success then the specified elements will be granted to the given user. The process runs in silent mode, no dialogs or messages will interrupt.
 */
__APIEXPORT GSErrCode ACAPI_Teamwork_GrantElements (const GS::Array<API_Guid>& elemGuids, short toUserId);



/**
 * @brief Retrieves the components of an element.
 * @ingroup Element
 * @param elemGuid [in] Guid of the element whose components have to be retrieved.
 * @param elemComponents [out] The components of the specified element.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The elemGuid did not refer to a valid element.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetComponents-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetComponents (const API_Guid&					elemGuid,
																	 GS::Array<API_ElemComponentID>&	elemComponents);



/**
 * @brief Retrieves all of the property definitions that are available for a component of an element.
 * @ingroup Element
 * @ingroup Property
 * @param elemComponent [in] The identifier of the element's component to search for.
 * @param filter [in] Filter the list of property definitions (API_PropertyDefinitionFilter_UserDefined, @c API_PropertyDefinitionFilter_BuiltIn, @c API_PropertyDefinitionFilter_All).
 * @param propertyDefinitions [out] Array of property definitions that are available for the given component.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The value of elemComponent did not refer to a valid component.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetPropertyDefinitionsComponent-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetPropertyDefinitions	(const API_ElemComponentID&			elemComponent,
																					 API_PropertyDefinitionFilter		filter,
																					 GS::Array<API_PropertyDefinition>&	propertyDefinitions);


/**
 * @brief Retrieves the specified property definition's value from the component.
 * @ingroup Element
 * @ingroup Property
 * @param elemComponent [in] The identifier of the element's component to search for.
 * @param propertyDefinitionGuid [in] The property definition to get the values for.
 * @param property [out] The value of the requested property.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The elemComponent did not refer to a valid component.
 * 			- APIERR_GENERAL - The propertyDefinitionGuid did not refer to a valid property definition.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetPropertyValueComponent-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetPropertyValue		(const API_ElemComponentID& elemComponent,
																					 const API_Guid&			propertyDefinitionGuid,
																					 API_Property&				property);


/**
 * @brief Retrieves the values of the specified property definitions from the component.
 * @ingroup Element
 * @ingroup Property
 * @param elemComponent [in] The identifier of the element's component to search for.
 * @param propertyDefinitions [in] The property definitions to get the values for.
 * @param properties [out] The definitions and values of the requested properties.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The elemComponent did not refer to a valid element.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetPropertyValuesComponent-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetPropertyValues		(const API_ElemComponentID&					elemComponent,
																					 const GS::Array<API_PropertyDefinition>&	propertyDefinitions,
																					 GS::Array<API_Property>&					properties);


/**
 * @brief Retrieves the specified property definitions (defined by their GUIDs) with values from the component.
 * @ingroup Element
 * @ingroup Property
 * @param elemComponent [in] The identifier of the element's component to search for.
 * @param propertyDefinitions [in] The property definition GUIDs to get the values for.
 * @param properties [out] The definitions and values of the requested properties.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The elemComponent did not refer to a valid element.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetPropertyValuesByGuidComponent-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetPropertyValuesByGuid	(const API_ElemComponentID&	elemComponent,
																					 const GS::Array<API_Guid>&	propertyDefinitions,
																					 GS::Array<API_Property>&	properties);

/* -- Element Difference Generator -------- */


/**
 * @brief Classifies an element.
 * @ingroup DifferenceGenerator
 * @param type [in] The element difference generator methode type.
 * @param diffGeneratorState [in/out] The difference generator state.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The diffGeneratorState is nullptr, or has wrong input parameters.
 * 			- APIERR_GENERAL - There is no current plan open.
 */
__APIEXPORT GSErrCode ACAPI_DifferenceGenerator_GetState (API_ElemDifferenceGeneratorTypeID	type,
																				API_ElemDifferenceGeneratorState*	diffGeneratorState);


/**
 * @brief It gives back the differencies between two states.
 * @ingroup DifferenceGenerator
 * @since Archicad 26
 * @param type [in] The element difference generator method type.
 * @param diffState1 [in] The first difference generator state.
 * @param diffState2 [in] The second difference generator state.
 * @param difference [out] The result of the difference generator.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The diffState1 or diffState2 is nullptr, or has wrong input parameters.
 * 			- APIERR_GENERAL - There is no current plan open.
 */
__APIEXPORT GSErrCode ACAPI_DifferenceGenerator_GenerateDifference (API_ElemDifferenceGeneratorTypeID		type,
																						  API_ElemDifferenceGeneratorState*		diffState1,
																						  API_ElemDifferenceGeneratorState*		diffState2,
																						  API_ElemDifference&					difference);



/**
 * @brief Get actual (merged) visual override style for an element
 * @ingroup Element
 * @param guid_Element [in] GUID of the element
 * @param elemOverrideStyle [out] Returned actual (merged) visual override style
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The element reference is invalid (guid).
 */
__APIEXPORT GSErrCode ACAPI_Element_GetActualOverrideStyle				(const API_Guid&					guid_Element,
																							 API_OverrideStyle&					elemOverrideStyle);


/**
 * @brief Returns visual overridden preview image for and element
 * @ingroup GraphicalOverride
 * @param elemGuid [in] Element reference.
 * @param image [in/out] Visual overridden image descriptor.
 * @return
 * 			- APIERR_BADID - The element reference is invalid (guid).
 * 			- APIERR_BADPARS - The passed image parameter was nullptr.
 * 			- NoError - The function has completed with success.
 * @remarks The output preview image shows an element without concrete geometry and connected elements. Outputs are a vector image and a native image. Do not forget to dispose the handle of the output vector image if it is not needed any more. See @ref API_VisualOverriddenImage structure for further details.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_GraphicalOverride_GetVisualOverriddenImage-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GraphicalOverride_GetVisualOverriddenImage (const API_Guid&				elemGuid,
																				API_VisualOverriddenImage	*image);


/**
 * @brief Returns a map that contains an element type set for every available autotext regards to the note owner's type.
 * @ingroup AutoText
 * @since Archicad 26
 * @param noteOwnerType [in] The note owner's type.
 * @param elemTypesForAutotextIDs [out] The result map for the note owner's type. The autotext is evaluable for the note if the parent element type is contained by the set. The empty set means the autotext is generally evaluable.
 * @param dimAppear [in] The dimAppear is an optional parameter. It is only needed when the note owner's type is @c API_DimensionID.
 * @return
 * 			- APIERR_BADID - The given element type is not a note owner type or if it is @c API_DimensionID then the given dimAppear is nullptr.
 * @remarks This function is used to get a map for the note owner that contains every available autotexts and on which elements are they evaluable. The empty element type set means the autotext is generally evaluable.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AutoText_GetNoteAutotexts-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AutoText_GetNoteAutotexts (const API_ElemType& noteOwnerType,
																		std::unordered_map<API_NoteAutotextID, std::unordered_set<API_ElemType>>& elemTypesForAutotextIDs,
																		const GS::Optional<API_AppearID>& dimAppear = GS::NoValue);


/**
 * @brief Returns the unistring keyword for note autotext id.
 * @ingroup AutoText
 * @since Archicad 26
 * @param autotextID [in] The note autotext identifier.
 * @param keyword [out] The result keyword for the note autotext.
 * @return
 * 			- NoError - This function always return NoError.
 * @remarks This function is used to get the keyword for the note autotext.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AutoText_GetNoteKeywordForAutotextID-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AutoText_GetNoteKeywordForAutotextID (API_NoteAutotextID autotextID,
																				   GS::UniString& keyword);


/* -- Markup Management ------------------ */


/**
 * @brief Creates new Mark-Up entry.
 * @ingroup Markup
 * @param markUp [in/out] The parameters of the new Mark-Up. The GUID and time stamp typed fields will be filled by this function.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NEEDSUNDOSCOPE - The function must be undoable, it wasn't called from an undoable command scope.
 * @remarks Using this function a new Mark-Up entry can be created. Use @c ACAPI_Markup_Change function to change and @ref ACAPI_Markup_Delete function to delete an existing Mark-Up entry. Elements can be attached to the Mark-Up using @ref ACAPI_Markup_AttachElements and comment can be added with @ref ACAPI_Markup_AddComment function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Markup_Create-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Markup_Create					(API_MarkUpType&			markUp);


/**
 * @brief Returns the existing Mark-Up entries which the given element is attached to.
 * @ingroup Markup
 * @param elemGuid [in] The GUID of the element or APINULLGuid to list all Mark-Ups.
 * @param markUpList [out] The list of Mark-Up(s).
 * @param asCorrected [out] Returns whether the given element is a corrected or highlighted element in the listed Mark-Up(s).
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed elemGuid parameter was invalid or the passed markUpList is nullptr.
 * @remarks Use this function to list which Mark-Ups is the given element attached to. To list all the existing Mark-Ups pass APINULLGuid to the elemGuid parameter. Use @ref ACAPI_Markup_Create function to create and @ref ACAPI_Markup_Delete function to delete Mark-Up entries. Note that an element can be attached to only one Mark-Up as corrected, but it can be attached to more Mark-Ups as highlighted and cannot be corrected and highlighted simultaneously. So if true was returned in asCorrected output parameter, then the size of the retuned markUpList array must be 1.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Markup_GetList-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Markup_GetList				(const API_Guid&			elemGuid,
																			 GS::Array<API_MarkUpType>*	markUpList,
																			 bool*						asCorrected = nullptr);


/**
 * @brief Deletes an existing Issue.
 * @ingroup Markup
 * @since Archicad 25
 * @param markUpGuid [in] GUID of an existing Issue.
 * @param acceptAllElements [in] Accept all entry suggestions before the delete operation.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOPLAN - There is no opened project.
 * 			- APIERR_NEEDSUNDOSCOPE - The function must be undoable, it wasn't called from an undoable command scope.
 * 			- APIERR_BADID - Issue not found with the given guid.
 * 			- APIERR_NOACCESSRIGHT - The current user doesn't have the right to delete the Issue in the teamwork project.
 * 			- APIERR_BADPARS - Failed to accept all entry suggestions.
 * @remarks Use this function to delete an existing Issue. If the Issue has any attached suggestion element, then depending on the value of the acceptAllElements parameter, the suggestion elements will be deleted or kept after the deletion of the owner Issue. Use @ref ACAPI_Markup_Create function to create and @ref ACAPI_Markup_Delete function to delete an Issue. Use @ref ACAPI_Markup_GetAttachedElements function to return the attached elements of the Issue.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Markup_Delete-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Markup_Delete					(const API_Guid&			markUpGuid,
																			 bool						acceptAllElements = false);


/**
 * @brief Attach elements to an existing Mark-Up as corrected or highlighted elements.
 * @ingroup Markup
 * @since Archicad 25
 * @param markUpGuid [in] GUID of the existing Mark-Up.
 * @param elemList [in] The list of elements to attach.
 * @param type [in] Attach the elements with the given Component type.
 * @param modificationElemTable [in/out] Optional parameter, used only when @c APIMarkUpComponent_Modification is passed in type parameter. The table of the original and the modified element pairs.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NEEDSUNDOSCOPE - The function must be undoable, it wasn't called from an undoable command scope.
 * 			- APIERR_BADPARS - The passed markUpGuid parameter or at least one of the given element GUIDs was incorrect.
 * @remarks Using this function an existing element can be attached to an existing Mark-Up entry. Note that an element can be attached to only one Mark-Up as creation or deletion, but it can be attached to more Mark-Ups as highlighted and cannot be attached as highlighted and creation/deletion simultaneously. If the requested attachment would violate these rules than APIERR_BADPARS error code will be returned. Use @ref ACAPI_Markup_GetAttachedElements function to return the already attached elements of the Mark-Up entry and @ref ACAPI_Markup_DetachElements function to detach previously added elements.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Markup_AttachElements-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Markup_AttachElements			(const API_Guid&					markUpGuid,
																			 const GS::Array<API_Guid>&			elemList,
																			 API_MarkUpComponentTypeID			type,
																			 GS::HashTable<API_Guid, API_Guid>*	modificationElemTable = nullptr);


/**
 * @brief Detach elements from an existing Mark-Up.
 * @ingroup Markup
 * @param markUpGuid [in] GUID of the existing Mark-Up.
 * @param elemList [in] The list of elements to detach.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NEEDSUNDOSCOPE - The function must be undoable, it wasn't called from an undoable command scope.
 * 			- APIERR_BADPARS - The passed markUpGuid parameter or at least one of the given element GUIDs was incorrect.
 * @remarks Using this function (corrected or highlighted) elements can be detached from an existing Mark-Up entry. Use @ref ACAPI_Markup_GetAttachedElements function to return the already attached elements of the Mark-Up entry and @ref ACAPI_Markup_AttachElements function to attach elements.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Markup_DetachElements-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Markup_DetachElements			(const API_Guid&			markUpGuid,
																			 const GS::Array<API_Guid>&	elemList);


/**
 * @brief Returns the corrected and highlighted elements of the given Mark-Up.
 * @ingroup Markup
 * @since Archicad 26
 * @param markUpGuid [in] GUID of the existing Mark-Up.
 * @param type [in] Return the attached elements with the given Component type.
 * @param attachedElements [out] The list of the attachedElements elements of the Mark-Up.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed markUpGuid parameter was incorrect.
 * @remarks Using this function the corrected and highlighted elements of an existing Mark-Up entry can be listed. @ref ACAPI_Markup_GetList returns the list of the existing Mark-Ups. Use @ref ACAPI_Markup_AttachElements function to attach and @ref ACAPI_Markup_AttachElements function to detach elements.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Markup_GetAttachedElements-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Markup_GetAttachedElements	(const API_Guid&			markUpGuid,
																			 API_MarkUpComponentTypeID	type,
																			 GS::Array<API_Guid>&		attachedElements);


/**
 * @brief Adds a new comment to the given Mark-Up.
 * @ingroup Markup
 * @param markUpGuid [in] GUID of the existing Mark-Up.
 * @param comment [in/out] The parameters of the new comment. The guid and creaTime will be filled by this function.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NEEDSUNDOSCOPE - The function must be undoable, it wasn't called from an undoable command scope.
 * 			- APIERR_BADPARS - The passed markUpGuid parameter was incorrect.
 * @remarks A new comment can be added to an existing Mark-Up entry using this function. Use @ref ACAPI_Markup_GetList function to return the list of all Mark-Up entries and @ref ACAPI_Markup_GetComments function to get the previously added comments.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Markup_AddComment-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Markup_AddComment				(const API_Guid&			markUpGuid,
																			 API_MarkUpCommentType&		comment);


/**
 * @brief Returns the comments attached to the given Mark-Up entry.
 * @ingroup Markup
 * @param markUpGuid [in] GUID of the existing Mark-Up.
 * @param commentList [out] The list of the comments.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed markUpGuid parameter was incorrect or the passed commentList is nullptr.
 * @remarks Using this function the comments attached to an existing Mark-Up entry can be listed. Use @ref ACAPI_Markup_GetList function to return the list of all Mark-Up entries and @ref ACAPI_Markup_AddComment function to add new comment to the Mark-Up.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Markup_GetComments-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Markup_GetComments			(const API_Guid&					markUpGuid,
																			 GS::Array<API_MarkUpCommentType>*	commentList);


/**
 * @brief Exports a BCF file to specified location.
 * @ingroup Markup
 * @since Archicad 25
 * @param fileLoc [in] The location of the BCF file.
 * @param markupEntryIds [in] An Array containing the MarkUp Entry identifiers to export.
 * @param useExternalId [in] Use external IFC ID or Archicad IFC ID as referenced in BCF topics.
 * @param alignBySurveyPoint [in] Align BCF views by Archicad Survey Point or Archicad Project Origin.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks Use this function to export BCF files.
 * 			To learn more about the usage of the External IFC ID please refer to @ref IFCAPI::v1::ObjectAccessor::GetGlobalId and @ref IFCAPI::v1::ObjectAccessor::GetExternalGlobalId.
 * 			@snippet API_Examples.cpp ACAPI_Markup_ExportToBCF-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Markup_ExportToBCF			(const IO::Location&				fileLoc,
																			 const GS::Array<API_Guid>&			markupEntryIds,
																			 const bool							useExternalId = false,
																			 const bool							alignBySurveyPoint = true);


/**
 * @brief Imports a BCF file.
 * @ingroup Markup
 * @since Archicad 25
 * @param fileLoc [in] The location of the BCF file.
 * @param silentMode [in] Execute the import in silent mode, if its value is true then there will be no error or warning dialogs.
 * @param ifcRelationshipDataProc [in] Optional user defined callback function which will supply @ref API_IFCRelationshipData needed by BCF import when topics refers to element components like IFCBuildingElementParts. For more details see APIIFCRelationshipDataProc.
 * @param par1 [in] Optional parameter what will be passed for ifcRelationshipDataProc callback function.
 * @param openMarkUpPalette [in] Open MarkUp Palette after import or not.
 * @param alignBySurveyPoint [in] Align BCF views by Archicad Survey Point or Archicad Project Origin.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed fileLoc is not a valid BCF file.
 * @remarks Use this function to import a BCF file.
 * 			This api command is already part of an Undoable session and should not be called inside of @ref ACAPI_CallUndoableCommand. Example
 * 			For detailed examples, please see the MarkUp_Manager add-on.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Markup_ImportFromBCF-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Markup_ImportFromBCF			(const IO::Location&				fileLoc,
																			 const bool							silentMode,
																			 APIIFCRelationshipDataProc*		ifcRelationshipDataProc,
																			 const void*						par1,
																			 const bool							openMarkUpPalette = false,
																			 const bool							alignBySurveyPoint = true);

/* -- Body Editing ------------------------ */


/**
 * @brief Initializes a new body data object for editing.
 * @ingroup Body
 * @param body [in] The body object to start the editing with. nullptr can be passed to create a new body.
 * @param bodyMaterialMapTable [in] The initial material override structure list of the polygons of the body. nullptr can be passed in case of a new body.
 * @param bodyData [out] The body data object, that shall be passed to further editing functions.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed bodyData parameter is nullptr.
 * @remarks This function is used to create a body data object for further editing.
 * 			Input parameters can be nullptr, but can be passed from the @ref API_ElementMemo of a morph element.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Body_Create-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Body_Create			(const Modeler::MeshBody*		body,
																	 const API_OverriddenAttribute*	bodyMaterialMapTable,
																	 void**							bodyData);


/**
 * @brief Converts the body data object to a format, that can be passed to an @ref API_ElementMemo structure.
 * @ingroup Body
 * @param bodyData [in] The body data object to convert.
 * @param body [out] The body object to put the resulting body to.
 * @param bodyMaterialMapTable [out] The material override structure list of the polygons of the body.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed bodyData parameter is nullptr.
 * @remarks This function is used to convert a body data object to data, that can be passed to an @ref API_ElementMemo structure and create a morph element.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Body_AddPolygon-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Body_Finish			(void*							bodyData,
																	 Modeler::MeshBody**			body,
																	 API_OverriddenAttribute**		bodyMaterialMapTable);


/**
 * @brief Disposes the body data object.
 * @ingroup Body
 * @param bodyData [in] The body data object to dispose.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter in bodyData is nullptr.
 * @remarks This function is used to dispose a body data object.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Body_AddPolygon-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Body_Dispose			(void**					bodyData);


/**
 * @brief Adds a vertex to the body data object.
 * @ingroup Body
 * @param bodyData [in] The body data object to add the vertex to.
 * @param coord [in] Position of the vertex to add.
 * @param index [out] The index of the created vertex, can be used later to define edges.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed bodyData parameter is nullptr.
 * @remarks This function is used to add a vertex to a body data object.
 * 			The returned index can be used to create edges with the @ref ACAPI_Body_AddEdge function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Body_AddPolygon-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Body_AddVertex		(void*					bodyData,
																	 const API_Coord3D&		coord,
																	 UInt32&				index);


/**
 * @brief Adds a vertex to the body data object.
 * @ingroup Body
 * @param bodyData [in] The body data object to add the edge to.
 * @param vertex1 [in] Index of the first vertex of the edge.
 * @param vertex2 [in] Index of the second vertex of the edge.
 * @param index [out] The index of the created edge, can be used later to create polygons.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter is nullptr for bodyData. The index is out of range for vertex1, vertex2.
 * @remarks This function is used to add an edge to a body data object.
 * 			The vertex1 and vertex2 parameters shall be valid vertex indices provided by the @ref ACAPI_Body_AddVertex function.
 * 			The edge can be used with at most 2 polygons, and in that case it has to be passed with opposite directions.
 * 			The returned index can be used to create polygons with the @ref ACAPI_Body_AddPolygon function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Body_AddPolygon-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Body_AddEdge			(void*					bodyData,
																	 const UInt32			vertex1,
																	 const UInt32			vertex2,
																	 Int32&					index);


/**
 * @brief Adds a polygon normal vector to the body data object.
 * @ingroup Body
 * @param bodyData [in] The body data object to add the normal vector to.
 * @param normal [in] The normal vector to add.
 * @param index [out] The index of the created normal vector, can be used later to create polygons.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed bodyData parameter is nullptr. The normal vector length is 0;
 * @remarks This function is used to add a normal vector to a body data object.
 * 			A normal vector can be used for multiple polygons and can be passed with positive and negative direction too.
 * 			The normal vector is perpendicular to the polygon plane and points the direction you want to see the polygon from. (In case of a complete body, the normal vectors point ot of the body)
 * 			The returned index can be used to create polygons with the @ref ACAPI_Body_AddPolygon function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Body_AddPolygon-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Body_AddPolyNormal	(void*					bodyData,
																	 const API_Vector3D&	normal,
																	 Int32&					index);


/**
 * @brief Adds a polygon to the body data object.
 * @ingroup Body
 * @param bodyData [in] The body data object to add the polygon to.
 * @param edges [in] List of the edges of the polygon.
 * @param polyNormal [in] Signed index of the normal vector.
 * @param material [in] Material override structure of the polygon.
 * @param index [out] The index of the created polygon.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed bodyData parameter is nullptr. There are less than 3 edges passed.
 * @remarks This function is used to add a polygon to a body data object.
 * 			The edges list contains edge indices returned by the @ref ACAPI_Body_AddEdge function. The list shall look like the following:
 * 			- First pass the indices of contour edges as they sorruond the polygon counterclockwise. (An edge can be used backwards with a negative index)
 * 			- For each hole pass a 0, then the indices of hole contour edges clockwise.
 * 			polyNormal is the index of a normal vector returned by the @ref ACAPI_Body_AddPolyNormal function.
 * 			- A negative value indicates, that the vector is used in the opposite direction. (So a cube can be created making 3 normal vectors instead of 6)
 * 			- If you pass 0, the normal vector is calculated automatically, but doing so, the same vector may be created multiple times, as duplicates are not detected. (A plane containing many polygons generates the same normal for each polygon)
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Body_AddPolygon-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Body_AddPolygon		(void*							bodyData,
																	 const GS::Array<Int32>&		edges,
																	 const Int32					polyNormal,
																	 const API_OverriddenAttribute&	material,
																	 UInt32&						index);


/**
 * @brief Triggers a manual update of the specified drawings.
 * @ingroup Drawing
 * @since Archicad 27
 * @param drawingsToUpdate [in] List of the drawings to be updated.
 * @return
 * 			- NoError - The function has been completed with success.
 */
/* -- Drawing update */
__APIEXPORT GSErrCode ACAPI_Drawing_Update_Drawings	(const GS::Array<API_Guid>&	drawingsToUpdate);


/* -- PolyRoof Decomposer ----------------- */


/**
 * @brief Enumerates the planes of a Multi-plane Roof.
 * @ingroup Element
 * @param elemGuid [in] Identifier of the element to be decomposed. Currently this must be a PolyRoof element.
 * @param elementDecomposer [in] Interface pointer to an object implemented by the caller to be used during the decomposition.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The elementDecomposer pointer is nullptr or the element specified with elemGuid is not PolyRoof type.
 * 			- APIERR_BADID - The elemGuid parameter does not identify a valid element.
 * @remarks Use this function to enumerate the planes of a Multi-plane Roof as a set of Single-plane @ref API_RoofType elements.
 * 			First you need to implement a derived class of @ref API_ElementDecomposerInterface. An object instance of this class should be passed to @ref ACAPI_Element_Decompose to be called back by its GeneratePartElement method.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_Decompose-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_Decompose	(const API_Guid&					elemGuid,
																 API_ElementDecomposerInterface*	elementDecomposer);

/* -- ElementSet Manager ------------------ */


/**
 * @brief Groups elements into an element set.
 * @ingroup ElementSet
 * @param guids [in] Handle to the array of element GUIDs.
 * @param userData [in] User data assigned to the set (optional, can be nullptr).
 * @param setGuid [out] The unique ID of the newly created element set.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - guids or setGuid parameter is nullptr.
 * 			- APIERR_BADDATABASE, APIERR_NOTMINE - The function cannot operate on the current database.
 * 			- APIERR_NEEDSUNDOSCOPE - The function must be undoable, it wasn't called from an undoable command scope.
 * 			- APIERR_BADPLATFORMSIGN - The given platform sign is invalid.
 * 			- APIERR_MEMFULL - There is not enough memory to complete the operation.
 * @remarks You can use this function to create an element set for any kind of purpose. Similarly to @ref ACAPI_ElementLink_Link it creates a logical record which contains a list of element GUIDs you are interested in. You may also add custom information to the element set, as you can store user data to separate elements with @ref ACAPI_Element_SetUserData.
 * 			The reference GUID of the newly created element set is returned in the setGuid parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ElementSet_Create-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ElementSet_Create (GS::Array<API_Guid>	*guids,
																 const API_UserData		*userData,
																 API_Guid				*setGuid);


/**
 * @brief Deletes an existing element set.
 * @ingroup ElementSet
 * @param setGuid [in] The GUID of the element set to be deleted.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE - The function cannot operate on the current database.
 * 			- APIERR_NEEDSUNDOSCOPE - The function must be undoable, it wasn't called from an undoable command scope.
 * 			- APIERR_BADID - The setGuid parameter is invalid.
 * 			- APIERR_NOTMINE - The element set referenced by setGuid is owned by another user.
 * 			- APIERR_DELETED - The element set is already deleted.
 * @remarks This function deletes an element set identified by the setGuid parameter.
 * 			Note that you cannot delete element sets created by another add-ons.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ElementSet_Delete-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ElementSet_Delete (API_Guid setGuid);


/**
 * @brief Retrieves the data of an existing element set.
 * @ingroup ElementSet
 * @param setGuid [in] The GUID that identifies the element set.
 * @param elemGuids [out] Pointer to the array of element GUIDs.
 * @param data [out] User data assigned to the set.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE - The function cannot operate on the current database.
 * 			- APIERR_BADID - The setGuid parameter is invalid.
 * 			- APIERR_NOTMINE - The element set referenced by setGuid is owned by another user.
 * 			- APIERR_DELETED - The element set is already deleted.
 * @remarks This function retrieves the element GUID list and the attached user data of an element set created by @ref ACAPI_ElementSet_Create. Both of the output parameters are optional, can be nullptr.
 * 			Remember to release the userdata.dataHdl handles when you don't need it any more.
 */
__APIEXPORT GSErrCode ACAPI_ElementSet_GetData (API_Guid				setGuid,
																  GS::Array<API_Guid>	*elemGuids,
																  API_UserData			*data);


/**
 * @brief Retrieves the element sets that contain a given element.
 * @ingroup ElementSet
 * @param elemGuid [in] The element GUID to search for, or GS::NULLGuid to get all element sets.
 * @param setGuids [out] Array of GUIDs of the element sets that contain the element.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The setGuids parameter is nullptr.
 * 			- APIERR_BADDATABASE - The function cannot operate on the current database.
 * @remarks You can use this function to identify the element sets that refer to the passed element.
 * 			Note that element sets created by other add-ons will not be examined. You can get all element sets created by your add-on if you pass GS::NULLGuid in the guid parameter.
 */
__APIEXPORT GSErrCode ACAPI_ElementSet_Identify (API_Guid elemGuid, GS::Array<API_Guid> *setGuids);


/* -- Group Manager ------------------ */


/**
 * @brief Create an element group.
 * @ingroup Grouping
 * @param elemGuids [in] Array of unique IDs of the elements to group.
 * @param groupGuid [out] Unique ID of the newly created group.
 * @param parentGroupGuid [in] Optional parameter for setting unique ID of the parent group of the newly created group (making a group tree with it).
 * @return
 * 			- NoError - The function has completed with success, a new element group has created.
 * 			- APIERR_NEEDSUNDOSCOPE - The function must be undoable, it wasn't called from an undoable command scope.
 * 			- APIERR_BADID - One or more of the passed IDs are invalid.
 * 			- APIERR_BADPARS - Invalid value passed in the parameters (nullptr pointer, empty ID list, etc.).
 * @remarks This function create a simple element group, it becomes only a container of some elements. Passed elements have to be on the same floor.
 */
__APIEXPORT GSErrCode ACAPI_Grouping_CreateGroup (const GS::Array<API_Guid>&	elemGuids,
												  API_Guid*						groupGuid = nullptr,
												  const API_Guid*				parentGroupGuid = nullptr);


/**
 * @brief Returns the group unique ID of the given element.
 * @ingroup Grouping
 * @param elemGuid [in] Unique ID of the element.
 * @param groupGuid [out] Unique ID of the group which contains the element.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - Passed element ID is invalid.
 * 			- APIERR_BADPARS - Invalid value passed in the parameters.
 * @remarks This function is used to get unique ID of a group for a grouped element.
 */
__APIEXPORT GSErrCode ACAPI_Grouping_GetGroup (const API_Guid&		elemGuid,
																 API_Guid*				groupGuid);


/**
 * @brief Returns the top level group unique ID of a nested group element.
 * @ingroup Grouping
 * @param elemGuid [in] Unique ID of the element.
 * @param rootGroupGuid [out] Unique ID of the root group.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - Passed element ID is invalid.
 * 			- APIERR_BADPARS - Invalid value passed in the parameters.
 * @remarks This function is used to obtain the top level group of a nested group element. If the passed group is not part of another group, the function returns the passed group guid as main group guid.
 */
__APIEXPORT GSErrCode ACAPI_Grouping_GetRootGroup (const API_Guid&		elemGuid,
																		 API_Guid*				rootGroupGuid);


/**
 * @brief Returns the immediate elements of the given group.
 * @ingroup Grouping
 * @param groupGuid [in] Unique ID of the passed group.
 * @param elemGuids [out] List of element unique IDs which directly belong to the given group.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - Passed group ID is invalid.
 * 			- APIERR_BADPARS - Invalid value passed in the parameters.
 * @remarks This function is used to get elements of a given group. The retrieved array contains only elements that are directly connected to the given group.
 */
__APIEXPORT GSErrCode ACAPI_Grouping_GetGroupedElems (const API_Guid&		 groupGuid,
																		    GS::Array<API_Guid>* elemGuids);


/**
 * @brief Returns all elements of the given group.
 * @ingroup Grouping
 * @param groupGuid [in] Unique ID of the passed group.
 * @param elemGuids [out] Array of all element unique IDs which below the passed group.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - Passed group ID is invalid.
 * 			- APIERR_BADPARS - Invalid value passed in the parameters.
 * @remarks This function is used to get all elements of a given group. The retrieved array contains all elements which are below the group subtree (root of subtree identified the passed groupGuid).
 */
__APIEXPORT GSErrCode ACAPI_Grouping_GetAllGroupedElems (const API_Guid&		groupGuid,
																		   GS::Array<API_Guid>*	elemGuids);


/**
 * @brief Obtains the user data attached to an element group.
 * @ingroup Grouping
 * @ingroup UserData
 * @param groupGuid [in] Unique ID of the element group.
 * @param userData [in/out] Pointer to the new user data.
 * @return
 * 			- NoError - The function has completed with success, a new user data has attached to the element group.
 * 			- APIERR_NEEDSUNDOSCOPE - The function must be undoable, it wasn't called from an undoable command scope.
 * 			- APIERR_BADID - Passed groupGuid ID is invalid.
 * 			- APIERR_BADPARS - One or more passed parameters are nullptr.
 * 			- APIERR_NOUSERDATA - No user data attached with the gived signature.
 * 			- APIERR_MEMFULL - Out of memory.
 * @remarks This function is used to get the user attached data from an element group. Use the @ref ACAPI_Grouping_SetUserData functions to push data into the element group.
 */
__APIEXPORT GSErrCode ACAPI_Grouping_GetUserData (const API_Guid&		groupGuid,
																		API_UserData*		userData);


/**
 * @brief Attaches the user data to the element group.
 * @ingroup Grouping
 * @ingroup UserData
 * @param groupGuid [in] Unique ID of the element group.
 * @param userData [in] Pointer to the new user data.
 * @return
 * 			- NoError - The function has completed with success, a new user data has attached to the element group.
 * 			- APIERR_NEEDSUNDOSCOPE - The function must be undoable, it wasn't called from an undoable command scope.
 * 			- APIERR_BADID - Passed groupGuid ID is invalid.
 * 			- APIERR_BADPARS - Passed groupGuid parameter is nullptr.
 * 			- APIERR_BADPLATFORMSIGN - The given platform sign is invalid (out of range).
 * 			- APIERR_MEMFULL - Out of memory.
 * @remarks This function is used to attach user data to an element group. Use the @ref ACAPI_Grouping_GetUserData function to get data from the element group. Existing user data can be deleted by setting userData input parameter to nullptr.
 * 			Note that this function is not undoable.
 * 			The caller should allocate and deallocate the userData->dataHdl handle.
 */
__APIEXPORT GSErrCode ACAPI_Grouping_SetUserData (const API_Guid&		groupGuid,
																		const API_UserData*	userData);

/* -- Selection Manager ------------------- */


/**
 * @brief Returns information on the selection, and the selected elements.
 * @ingroup Selection
 * @param selectionInfo [out] The parameters of the current selection. The typeID field of the selectionInfo gives the selection type.
 * @param selNeigs [out] An array containing the GUIDs of the selected elements. Can be nullptr if you are interested in the selection information only.
 * @param onlyEditable [in] Tells whether you are interested in editable elements only.
 * @param ignorePartialSelection [in] Retrieves also partial element selection information or the element itself only selected as whole (for legacy compatibility reasons, the default value of this parameter is true, meaning partial selection is ignored). This parameter is ignored in case of marquee based selection.
 * @param relativePosToMarquee [in] Retrieves elements relative to marquee (for legacy compatibility reasons, the default value of this parameter is @c API_InsidePartially, meaning only those elements will be returned which have an intersection with the marquee area). This parameter is ignored in case of individually selected elements.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOPLAN - There is no open project.
 * 			- APIERR_NOSEL - There is no selection. Note that this is not a real error!
 * @remarks This function is used to get information about the current selection and to retrieve the selected elements. The information is returned in the selectionInfo parameter.
 * 			If individual elements are selected the @c API_SelElems identifier is returned. The number of the selected and selected and editable elements are also returned. In case of marquee based selection, the function gives back the actual polygon of the current selection in the @ref API_SelectionInfo structure; don't forget to dispose this handle.
 * 			The @c API_SelEmpty identifier in the typeID field of the selectionInfo parameter means that no selection is actually used in Archicad.
 * 			In case of individually selected elements, Archicad returns all the elements which are selected. In the case of marquee based selection, only those will be returned which match the position criteria defined by relativePosToMarquee.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Selection_Get-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Selection_Get (API_SelectionInfo*		selectionInfo,
															 GS::Array<API_Neig>*	selNeigs,
															 bool					onlyEditable,
															 bool					ignorePartialSelection = true,
															 API_SelRelativePosID	relativePosToMarquee = API_InsidePartially);


/**
 * @brief Changes the current marquee selection.
 * @ingroup Selection
 * @param selectionInfo [in] The parameters of the marquee to be set.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The selectionInfo parameter is nullptr
 * 			- APIERR_BADDATABASE - The active database is neither the floorplan, nor a section database
 * @remarks This function is used to change the marquee on a floorplan or section window. The typeID field of the selectionInfo must be @c API_MarqueePoly, @c API_MarqueeHorBox or @c API_MarqueeRotBox in order to set a new marquee outline, otherwise the actual marquee will be removed.
 * 			The function has no effect on the individual selection of elements.
 * 			In case of @c API_MarqueePoly type marquee do not forget to release the coordinate handle passed in the selectionInfo parameter.
 */
__APIEXPORT GSErrCode ACAPI_Selection_SetMarquee (API_SelectionInfo *selectionInfo);


/* -- 3D Manager -------------------------- */


/**
 * @brief Returns the number of existing 3D components.
 * @ingroup  ModelAccess
 * @param typeID [in] Type of the 3D component.
 * @param count [out] Number of component with the given type.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter is nullptr ; count
 * 			- APIERR_REFUSEDCMD - The 3D model is not available in the current context
 * 			- APIERR_BADID - The component type is invalid
 * 			- APIERR_REFUSEDPAR - The component type cannot be queried directly
 * @remarks This function is used to get the number of 3D components with a given type. Refer to the @ref API_3DTypeID structure for the possible values.
 * 			Only the @c API_BodyID, @c API_LghtID and @c API_UmatID type components can be addressed with this function.
 * 			Model dependent components (API_PgonID, @c API_PedgID, @c API_EdgeID, @c API_VertID, @c API_VectID) are body dependent; direct access is prohibited. The number of these components can be determined from the @ref API_BodyType type.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ModelAccess_GetNum-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ModelAccess_GetNum (API_3DTypeID typeID, Int32 *count);


/**
 * @brief Retrieves a component from the 3D model of Archicad.
 * @ingroup  ModelAccess
 * @param component [in/out] The typeID and the index field of the component header must be passed. You get the desired component data in the appropriate part of the union.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter is nullptr; component
 * 			- APIERR_REFUSEDCMD - The 3D model is not available in the current context, or
 * 			The component type cannot be queried directly; no active body
 * 			- APIERR_BADID - The component type is invalid
 * 			- APIERR_BADINDEX - The component index is out of range
 * 			- APIERR_DELETED - In case of typeID is @c API_BodyID, you can get this error code, meaning the body has been removed from the 3D model because it was deleted, it is shadow body instead of a model one or it was eliminated during the model creation.
 * @remarks This function is used to retrieve one component from the 3D data structure.
 * 			The component is defined by the typeID and index fields in the header of the component parameter. If the typeID is @c API_BodyID you may get the error code APIERR_DELETED, meaning the body has been removed from the 3D model.
 * 			It is very important to organize your algorithm on a loop based on the component @c API_BodyID (see example below) for the following reasons:
 * 			- Body indices are continuos in all cases, others are not.
 * 			- The 3D model also can have data from deleted floor plan elements. They can be identified only through the deleted bodies.
 * 			- Floor plan elements which have the same geometry may share the primitives of the 3D representation data, but not the bodies. All the bodies contain a transformation matrix which transforms the referenced shared vertices and normal vectors to the right places and directions.
 * 			Once you have the definition of a body, you can set up sub loops to go through the primitives you are interested for. In the @ref API_BodyType record you get the number of all internal components. Indices should start from 1.
 * 			The light and material components can be obtained in their own loops, because they are global (not body relative) components of the 3D model.
 * 			It is very important, that you get the data of the 3D model of Archicad that actually exists. This data is often not consistent with the floor plan elements. The update mechanism of the 3D window depends on many things, such as the switches in the preferences dialogs. As a general rule, you get the model which can be seen in the 3D window, if you use the above template.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ModelAccess_GetComponent-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ModelAccess_GetComponent (API_Component3D *component);


/**
 * @brief Decomposes a polygon of the 3D model into convex polygons.
 * @ingroup  ModelAccess
 * @param ipgon [in] Index of a polygon in the 3D model.
 * @param cpoly [out] Points to an array which contains the vertices of subpolygons.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter is nullptr ; cpoly
 * 			- APIERR_REFUSEDCMD - The 3D model is not available in the current context, or
 * 			The polygon type cannot be queried directly; no active body
 * 			- APIERR_BADINDEX - The polygon index is out of range
 * 			- APIERR_MEMFULL - Not enough memory
 * @remarks This function is used to decompose a polygon into convex polygons. The polygon is defined by ipgon index.
 * 			The decomposed polygon is returned in the cpoly Int32 array, which contains the following values:
 * 			[-n], [-m1 ], i1, i2, ... i(m1 ), [-m2 ], j1, j2, ... j(m2 )...
 * 			where:
 * 			- negative values mean some kind of measurement
 * 			- positive values mean vertex indices
 * 			| Parameter | Descriptions|
 * 			|-----------|-------------|
 * 			|n | The number of subpolygons. Can be 0 on error, or if the polygon is degenerate. |
 * 			|m i | The number of vertices of the following subpolygon|
 * 			|i1 .. i(m 1 ) j1 .. j(m 2 ) | The actual VERT indices of the subpolygons. The function doesn't generate new points, so these indices refer to the original VERT indices.|
 * 			Do not forget to dispose the returned handle if it is not needed any more.
 */
__APIEXPORT GSErrCode ACAPI_ModelAccess_DecomposePgon (Int32 ipgon, Int32 ***cpoly);


/**
 * @brief Creates a new sight for 3D operations.
 * @ingroup Sight
 * @param newSightPtr [out] A pointer to the new sight.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_GENERAL - The sight could not be created.
 * @remarks You can switch to this newly created sight with @ref ACAPI_Sight_SelectSight. Don't forget to delete the sight with @ref ACAPI_Sight_DeleteSight when you are done.
 */
__APIEXPORT GSErrCode ACAPI_Sight_CreateSight (void** newSightPtr);


/**
 * @brief Switches to the supplied 3D sight for subsequent operations.
 * @ingroup Sight
 * @param sightPtr [in] The sight to switch to. If sightPtr parameter is nullptr, then the 3D Window's sight will be selected.
 * @param oldSightPtr [out] A pointer to the previous sight.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_GENERAL - The passed sightPtr was invalid.
 * @remarks Subsequent 3D operations (like @ref ACAPI_ModelAccess_GetNum will use the selected sight.
 * 			You can also pass two special sight IDs:
 * 			| Sight ID | Meaning |
 * 			|----------|---------|
 * 			| `API_PlanSight` | The sight of the 3D window (i.e., the 3D information returned for @ref ACAPI_ModelAccess_GetNum) will use the element as it is on the floor plan. |
 * 			|  `API_SymbSight` | The sight of an object (in its 3D window). |
 */
__APIEXPORT GSErrCode ACAPI_Sight_SelectSight (void* sightPtr, void** oldSightPtr);


/**
 * @brief Deletes the supplied sight.
 * @ingroup Sight
 * @param sightPtr [in] A pointer to the sight to delete.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_GENERAL - The passed sightId was invalid.
 * @remarks Only pass sight pointers created with @ref ACAPI_Sight_CreateSight to this function.
 */
__APIEXPORT GSErrCode ACAPI_Sight_DeleteSight (void* sightPtr);


/**
 * @brief Returns the current window sight.
 * @ingroup Sight
 * @param sightPtr [out] A pointer to the current window sight.
 * @return
 * 			- NoError - The function has completed with success.
 * @
 */
__APIEXPORT GSErrCode ACAPI_Sight_GetCurrentWindowSight (void** sightPtr);


/**
 * @brief Returns the model of the selected sight.
 * @ingroup Sight
 * @param model [out] The model of the selected sight.
 * @return
 *			- NoError - The function has completed with success.
 *			- APIERR_REFUSEDCMD - The model is not available in the current context.
 *			- APIERR_GENERAL - Could not construct ModelerAPI::Model.
 * @
 */
__APIEXPORT GSErrCode ACAPI_Sight_GetSelectedSightModel (ModelerAPI::Model& model);


/**
 * @brief Cuts a body with a plane and returns the cutting surface and area.
 * @ingroup CuttingPlane
 * @param bodyIndex [in] The index of the body to cut.
 * @param cutPlane [in] Cutting plane.
 * @param resPolygons [out] Polygons of the cutting surface. (optional parameter)
 * @param area [out] Area of the cutting surface. (optional parameter)
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed output parameter are both nullptr (resPolygons and area)
 * 			- APIERR_REFUSEDCMD - The 3D model is not available in the current context, or
 * 			The body cannot be queried directly; not active body
 * 			- APIERR_BADINDEX - The bodyIndex is out of range
 * @remarks This function is used to cut a given body with a cutting plane and get the cutting surface.
 * 			To get the polygons of the cutting surface, pass the resPolygons parameter. To get only the area of the cutting surface, set the area parameter.
 * 			One of the output parameters (resPolygons and area) must be not nullptr.
 * @par Example
 */
__APIEXPORT GSErrCode ACAPI_CuttingPlane_GetCutPolygonInfo (Int32 									bodyIndex,
															const API_Plane3D& 						cutPlane,
															GS::Array<Geometry::MultiPolygon2D>* 	resPolygons = nullptr,
															double* 								area		= nullptr);


/**
 * @brief Cuts a body with a plane and returns the cutting surface and area.
 * @ingroup CuttingPlane
 * @param elemIdx [in] The index of the element to cut.
 * @param bodyIdx [in] The index of the body to cut.
 * @param cutPlane [in] Cutting plane.
 * @param resPolygons [out] Polygons of the cutting surface. (optional parameter)
 * @param area [out] Area of the cutting surface. (optional parameter)
 * @return
 *			- NoError - The function has completed with success.
 *			- APIERR_BADPARS - The passed output parameter are both nullptr (resPolygons and area)
 *			- APIERR_REFUSEDCMD - The 3D model is not available in the current context, or
 *								  The body cannot be queried directly; not active body
 * 			- APIERR_BADINDEX - The bodyIndex is out of range
 * @remarks This function is used to cut a given body with a cutting plane and get the cutting surface.
 * 			To get the polygons of the cutting surface, pass the resPolygons parameter. To get only the area of the cutting surface, set the area parameter.
 * 			One of the output parameters (resPolygons and area) must be not nullptr.
 * @par Example
 */
__APIEXPORT GSErrCode ACAPI_CuttingPlane_GetCutPolygonInfo_New (Int32 									elemIdx,
																Int32 									bodyIdx,
																const API_Plane3D& 						cutPlane,
																GS::Array<Geometry::MultiPolygon2D>* 	resPolygons = nullptr,
																double* 								area		= nullptr);


/**
 * @brief Generates a model with separate components of the given elements, and switches to that model for subsequent operations. The operation will not be executed if the active sight is the sight of 3D window.
 * @ingroup ModelAccess
 * @param elementGuids [in] The guids of the elements which will be part of the model.
 * @return
 *			- NoError - The function has completed with success.
 *			- APIERR_REFUSEDCMD - The 3D model is not available in the current context.
 *			- APIERR_BADID - One of the elements represented by a guid can not be found in the project.
 *			- APIERR_GENERAL - The active sight is the sight of 3D Window.
 * @remarks Before calling this function, you should create a new sight (ACAPI_Sight_CreateSight) and select it as active sight (ACAPI_Sight_SelectSight). Don't forget to delete the sight in the end (ACAPI_Sight_DeleteSight).
 */
__APIEXPORT GSErrCode ACAPI_ModelAccess_GenerateModelWithSeparateComponents (const GS::Array<API_Guid>& elementGuids);


/* -- ListData Manager -------------------- */


/**
 * @brief Returns the number of listdata sets.
 * @ingroup OldListing
 * @return
 * 			- NoError - The number of listdata sets of the listing database.
 * @remarks This function is used to get number of sets of the listing database.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_OldListing_GetSetNum-Example-Snippet
 */
__APIEXPORT Int32 ACAPI_OldListing_GetSetNum (void);


/**
 * @brief Retrieves the data of a listdata set.
 * @ingroup OldListing
 * @param listdataSet [in/out] Parameters of the set. The index of the set must be passed in the setIndex field in the listdataSet; it must be greater than 0. The other fields of the structure are filled in automatically.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADINDEX - Invalid listdataSet setindex was passed.
 * @remarks This function is used to get a listdata set, defined by the setIndex field of the listdataSet. The information of a given listdata set is returned in the fields of the listdataSet.
 * 			When getting the listdata set, the applicable fields should be filled: the @ref API_ListDataSetType `setIndex` is required.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_OldListing_GetSet-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_OldListing_GetSet (API_ListDataSetType *listdataSet);


/**
 * @brief Returns the number of listdata in given set.
 * @ingroup OldListing
 * @param setIndex [in] Index of the sets of the listing database.
 * @param typeID [in] Type of the listdata.
 * @param count [out] Number of listdata type in the set.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - Invalid listdata type or setIndex was passed.
 * @remarks This function is used to get the highest available listdata index of the given listdata type in the set.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_OldListing_GetNum-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_OldListing_GetNum (Int32 setIndex, API_ListDataID typeID, Int32 *count);


/**
 * @brief Retrieves the data of a listdata.
 * @ingroup OldListing
 * @param listdata [in/out] Parameters of the listdata. The type of the listdata, the index of the set and the index of the listdata must be passed in the typeID, the setIndex and the index fields in the listdata header. Other fields of the structure are filled in automatically.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADINDEX - Invalid listdata index was passed.
 * 			- APIERR_BADID - Invalid listdata type was passed.
 * 			- APIERR_DELETED - Invalid listdata was deleted.
 * @remarks This function is used to get a listdata, defined by the typeID, the setIndex and the index fields of the listdata header. The information of a given listdata is returned in the fields of the listdata.
 * 			This function is faster than @ref ACAPI_OldListing_GetLocal.
 * 			When getting the listdata, the applicable fields should be filled in.
 * 			|API_ListData_Head||
 * 			|--- |--- |
 * 			|setIndex|required; must be >= 1|
 * 			|typeID|required|
 * 			|index|required|
 * 			If you are retrieving a descriptor, don't forget to dispose of the name handle when you're finished.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_OldListing_Get-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_OldListing_Get (API_ListData *listdata);


/**
 * @brief Searches for a listdata.
 * @ingroup OldListing
 * @param listdata [in/out] Parameters of the listdata. The type and setIndex of the listdata must be passed in the typeID and the setIndex fields in the listdata header. The code and/or the keycode of the listdata must be passed in the code and the keycode fields in the listdata. The setIndex and the index fields of the listdata header are used as the output parameters to return the setIndex/index to the searched listdata.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADKEYCODE - Invalid code or keycode was passed.
 * @remarks This function is used to search for a listdata, identified by the setIndex, the typeID and the code/keycode fields in the listdata header. Units and keys are searchable by code, components and descriptors are searchable by code and/or keycode. The All sets of listing database are sorted by keycode.
 * 			|API_ListData_Head||
 * 			|--- |--- |
 * 			|setIndex|required (if it's 0 - search in all sets)|
 * 			|typeID|required|
 *
 * 			|API_ListDataID|keycode|code|
 * 			|--- |--- |--- |
 * 			|API_KeyID or API_UnitID|not exist|required|
 * 			|API_Obsolete_ComponentID or API_DescriptorID|required|optional|
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_OldListing_Search-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_OldListing_Search (API_ListData *listdata);


/**
 * @brief Retrieves the data of a local listing component.
 * @ingroup OldListing
 * @param libIndex [in] Index of the library part.
 * @param elemHead [in] Element of the placed object instance (see remarks).
 * @param listdata [in/out] Parameters of the listdata. The type of the listdata must be passed in the typeID field in the listdata header. The index in the library part must be passed in the index field in the listdata header. The other fields of the structure are filled in automatically.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Invalid libIndex was passed.
 * 			- APIERR_BADID - Invalid listdata type was passed.
 * @remarks This function is used to get a local component or descriptor in the library part defined by libIndex and typeID, the index field of the listdata header. The information of a given listdata is returned in the fields of the listdata. If the given listdata is in the listing database, use the @ref ACAPI_OldListing_Get function instead.
 * 			When getting the local listdata, the applicable fields should be filled.
 * 			|API_ListData_Head||
 * 			|--- |--- |
 * 			|index|required|
 * 			|typeID (only for `API_Obsolete_ComponentID` and `API_DescriptorID`)|required|
 * 			|libIndex|required|
 * 			If you are retrieving a descriptor, do not forget to dispose of the name handle when you're finished.
 * 			If the listing result depends on the current settings of the library part parameters (which is possible when the component or descriptor definitions in the property script of the object refer to GDL parameters of the object), you might need to get the correct data to be listed for a placed element. In this case you need to pass the appropriate elemTypeID and elemIndex parameters. Otherwise these values should be @c API_ZombieElemID and 0 respectively.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_OldListing_GetLocal-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_OldListing_GetLocal (Int32 libIndex, const API_Elem_Head *elemHead, API_ListData *listdata);


/* -- Communication Manager ------- */


/**
 * @brief Test the availability of a command.
 * @ingroup AddOnAddOnCommunication
 * @param mdid [in] the identifier of the target add-on. It is defined by the 'MDID' resource.
 * @param cmdID [in] the identifier of the command to be tested.
 * @param cmdVersion [in] the required command version
 * @return
 * 			- NoError - the command is installed, it may be called
 * 			- APIERR_BADPARS - the mdid parameter is nullptr
 * 			- APIERR_MODULNOTINSTALLED - the referenced add-on is not installed
 * 			- APIERR_MODULCMDNOTSUPPORTED - the referenced command is not supported by the target add-on
 * 			- APIERR_MODULCMDVERSNOTSUPPORTED - the requested command version is too new; not supported by the target add-on
 * @remarks This function is used to check the availability of an add-on's command.
 * 			Call this function to check whether the requested command of another add-on is available. Depending on the result, for example you can modify your add-on's interface. The following cases may happen:
 * 			- the command is installed,
 * 			- the target add-on is not installed
 * 			- the target add-on is installed, but the command is not supported,
 * 			- the target add-on is installed, the command is supported, but the command version is incorrect.
 * 			Refer to the @ref ACAPI_AddOnAddOnCommunication_Call function to see the details of calling another add-on.
 * 			Refer to the paper of the Communication Manager for more details.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AddOnAddOnCommunication_Test-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AddOnAddOnCommunication_Test	(const API_ModulID*	mdid,
															 GSType				cmdID,
															 Int32				cmdVersion);


/**
 * @brief Call a command of an other add-on.
 * @ingroup AddOnAddOnCommunication
 * @param mdid [in] the identifier of the target add-on. It is defined by the 'MDID' resource.
 * @param cmdID [in] the identifier of the command to be executed.
 * @param cmdVersion [in] the required command version
 * @param params [in/out] passed parameters (optional). See the Inter-add-on communication section of the @c ACAPI_Goodies functions
 * @param resultData [out] results returned by the command (optional)
 * @param silentMode [in] instruct the target add-on to work in silent mode. No option dialogs, error alerts...etc.
 * @return
 * 			- NoError - the function completed successfully
 * 			- APIERR_BADPARS - the mdid parameter is nullptr
 * 			- APIERR_MODULNOTINSTALLED - the referenced add-on is not installed
 * 			- APIERR_MODULCMDNOTSUPPORTED - the referenced command is not supported by the target add-on
 * 			- APIERR_MODULCMDVERSNOTSUPPORTED - the requested command version is too new; not supported by the target add-on
 * @remarks This function is used to call a command implemented in an other add-on.
 * 			Refer to the @ref ACAPI_AddOnAddOnCommunication_Test function to test the command availability.
 * 			Refer to the Communication Manager for more detailed description on
 * 			- how to pass parameters,
 * 			- how to get return values,
 * 			- how the heaps and API environments are managed by the API.
 * 			From Archicad 10 you can execute add-on command with @ref ACAPI_AddOnAddOnCommunication_ExternalCall on a different plan loaded into another instance of Archicad.
 * 			From Archicad 19 you can execute add-on command forced from main event loop with @ref ACAPI_AddOnAddOnCommunication_CallFromEventLoop function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AddOnAddOnCommunication_Call-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AddOnAddOnCommunication_Call	(const API_ModulID*	mdid,
															 GSType				cmdID,
															 Int32				cmdVersion,
															 GSHandle			params,
															 GSPtr				resultData,
															 bool				silentMode);


/**
 * @brief Call a command of an other add-on in another Archicad instance.
 * @ingroup AddOnAddOnCommunication
 * @param projectFileLoc [in] the location of the project file to be opened during the remote call
 * @param mdid [in] the identifier of the target add-on. It is defined by the 'MDID' resource
 * @param cmdID [in] the identifier of the command to be executed
 * @param cmdVersion [in] the required command version
 * @param params [in/out] passed parameters (optional). See the Inter-add-on communication section of the @c ACAPI_Goodies functions
 * @param silentMode [in] instruct the target add-on to work in silent mode. No option dialogs, error alerts...etc.
 * @param externalCallbackProc [in] optional callback procedure for handling the responses asynchronously
 * @return
 * 			- NoError - the function completed successfully
 * 			- APIERR_BADPARS - the mdid or the projectFileLoc parameter is nullptr
 * 			- APIERR_REFUSEDPAR - the location defined by projectFileLoc is empty or invalid
 * 			- APIERR_MODULNOTINSTALLED - the referenced add-on is not installed
 * 			- APIERR_MODULCMDNOTSUPPORTED - the referenced command is not supported by the target add-on
 * 			- APIERR_MODULCMDVERSNOTSUPPORTED - the requested command version is too new; not supported by the target add-on
 * 			- APIERR_CANCEL - the external operation has been canceled (either by the user or due to communication problem)
 * @remarks This function is used to call an add-on implemented command on a different plan loaded into another instance of Archicad.
 * 			The system provides that the requested project would be available for performing the command in the following way:
 * 			- if there is already an Archicad application running with the specified plan, it attempts to reserve it for the external call (it waits for the application to be available if currently busy with some other operation)
 * 			- if there is an Archicad running with currently no plan opened in it (empty), it reserves that application and makes it load the project file
 * 			- if there is no available Archicad running, it launches a new application instance with loading the requested project file
 * 			After the external Archicad instance is reserved for serving the add-on command call, the operation works similarly to the @ref ACAPI_AddOnAddOnCommunication_Call function. On the server side the callee add-on does not even realize that the command request comes from another application instance. The only difference is that the resultData parameter is always nullptr when calling its APIModulCommandProc handler, because this pointer cannot be passed between ARCHICADs. However you can change the content of the params handle modifying any parameters to communicate the result to the caller.
 * 			The caller can decide the function to return immediately after sending the command request (asynchronous operation) or to wait for the external call to be finished (synchronous operation). You need to pass an APIExternalCallBackProc handler function to collect the responses asynchronously; if this parameter is nullptr, the function does not return until the external operation is finished. The advantage of the asynchronous way is that you can initiate more calls even with different project files at the same time, and the internal task scheduler will optimize the sequence of execution.
 * 			Please note that if you use a loop for waiting for the asynchronous responses, do not reserve the processor time superfluously, let other threads run by calling the TIWait function of the GSRoot module.
 * 			Refer to the Communication Manager for more detailed description on
 * 			- how to pass parameters
 * 			- how to get return values
 * 			- how the heaps and API environments are managed by the API
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AddOnAddOnCommunication_ExternalCall-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AddOnAddOnCommunication_ExternalCall	(const IO::Location*		projectFileLoc,
																	 const API_ModulID*			mdid,
																	 GSType						cmdID,
																	 Int32						cmdVersion,
																	 GSHandle					params,
																	 bool						silentMode,
																	 APIExternalCallBackProc*	externalCallbackProc);


/**
 * @brief Calls a command of an add-on from Archicad's main event loop.
 * @ingroup AddOnAddOnCommunication
 * @param mdid [in] the identifier of the target add-on. It is defined by the 'MDID' resource
 * @param cmdID [in] the identifier of the command to be executed
 * @param cmdVersion [in] the required command version
 * @param paramsHandle [in/out] passed parameters (optional). See the Inter-add-on communication section of the @c ACAPI_Goodies functions
 * @param silentMode [in] instruct the target add-on to work in silent mode. No option dialogs, error alerts...etc.
 * @param callbackProc [in] optional callback procedure for handling the responses asynchronously
 * @return
 * 			- NoError - the function completed successfully
 * 			- APIERR_BADPARS - the mdid parameter is nullptr
 * 			- APIERR_MODULNOTINSTALLED - the referenced add-on is not installed
 * 			- APIERR_MODULCMDNOTSUPPORTED - the referenced command is not supported by the target add-on
 * 			- APIERR_MODULCMDVERSNOTSUPPORTED - the requested command version is too new; not supported by the target add-on
 * @remarks This function is used to call a command implemented in an add-on from Archicad's main event loop.
 * 			Refer to the @ref ACAPI_AddOnAddOnCommunication_Test function to test the command availability.
 * 			Refer to the Communication Manager for more detailed description on
 * 			- how to pass parameters,
 * 			- how to get return values,
 * 			- how the heaps and API environments are managed by the API.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AddOnAddOnCommunication_CallFromEventLoop-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AddOnAddOnCommunication_CallFromEventLoop	(const API_ModulID*			mdid,
																		 GSType						cmdID,
																		 Int32						cmdVersion,
																		 GSHandle					paramsHandle,
																		 bool						silentMode,
																		 APICommandCallBackProc*	callbackProc);

/* -- ModulData Manager ---------------- */


/**
 * @brief Saves a custom data section into the project database.
 * @ingroup ModulData
 * @param info [in] The module data to store. It also includes platform and version information.
 * @param modulName [in] Identifier name of the modul data (optional).
 * @return
 * 			- NoError - the function completed successfully
 * 			- APIERR_BADPARS - the passed dataHdl parameter is nullptr
 * 			- APIERR_BADPLATFORMSIGN - the platformSign passed in info is not valid
 * 			- APIERR_NOMODULEDATA - no custom data section is saved into the project file to be deleted
 * 			- APIERR_MEMFULL - failed memory allocation
 * 			- APIERR_GENERAL - a general error
 * @remarks This function is used to embed a custom data section into the project database.
 * 			The data section in the project is identified uniquely using the 'MDID' of the caller add-on and the passed modulName identifier.
 * 			The dataHdl handle has to be allocated and released using the c%20Memory%20Manager"> BM memory manager functions of the GSRoot module. The data content can be copied into the handle directly, or you can use the allocated memory block as a memory channel (see IO::MemoryOChannel).
 * 			In order to remove the saved module data from the project, you can simply pass nullptr pointer in the info parameter. The same effect can be achieved with the @ref ACAPI_ModulData_Delete function.
 * 			To retrieve the stored section use the @ref ACAPI_ModulData_GetInfo and @ref ACAPI_ModulData_Get functions.
 * 			You can also get a list of names of all modules stored by the add-on with the @ref ACAPI_ModulData_GetList function.
 * 			If you need to save different format moduldata back into previous version project file, you should implement an APIModulDataSaveOldFormatHandlerProc callback function, which prepares the necessary data in the format corresponding to the project version.
 * 			You might also need to merge data of the modules conflicting due to a merge or Teamwork receive operation. In order to properly resolve the conflicts you can implement an APIModulDataMergeHandlerProc callback function. For further details refer to the ModulData Manager overview.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ModulData_Store-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ModulData_Store (const API_ModulData* info, const GS::UniString& modulName = GS::EmptyUniString);


/**
 * @brief Returns information on the custom data section stored in the project database.
 * @ingroup ModulData
 * @param info [out] The version and platform information of the stored moduldata.
 * @param modulName [in] Identifier name of the modul data (optional).
 * @return
 * 			- NoError - The information was returned successfully.
 * 			- APIERR_BADPARS - The info parameter is nullptr.
 * 			- APIERR_NOMODULEDATA - No custom data section is saved into the project file identified by the add-on's unique modul ID and the modulName parameter.
 * @remarks This function is used to retrieve version and platform information on the custom data section embedded in the project database, identified with the given modulName.
 * 			In order to get the stored data itself, use the @ref ACAPI_ModulData_Get function.
 */
__APIEXPORT GSErrCode ACAPI_ModulData_GetInfo (API_ModulData* info, const GS::UniString& modulName = GS::EmptyUniString);


/**
 * @brief Returns the data section stored in the project database.
 * @ingroup ModulData
 * @param info [out] Contains the the custom data stored in the project file on return.
 * @param modulName [in] Identifier name of the modul data (optional).
 * @return
 * 			- NoError - The function has completed successfully.
 * 			- APIERR_BADPARS - The info parameter is nullptr.
 * 			- APIERR_NOMODULEDATA - No custom data section is saved into the project file identified by the add-on's unique modul ID and the modulName parameter.
 * @remarks This function is used to retrieve the data bytes of the custom data section embedded into the project database, identified with the given modulName.
 * 			- Always check the platformSign returned in the @ref API_ModulData structure. Call the necessary byte swapping methods to ensure correct data format. Refer to the GSRoot documentation to have further details on the byte swapping methods.
 * 			- Always check the dataVersion returned in the @ref API_ModulData structure. Old data formats should be handled to keep backward compatibility (see also APIModulDataSaveOldFormatHandlerProc).
 * 			Archicad allocates the target buffer in the dataHdl field of info ; the caller add-on is responsible to dispose it with BMKillHandle.
 * 			In order to check whether there is moduldata with the specified identifier stored into the current project, it is recommended to use the @ref ACAPI_ModulData_GetInfo function, which does not retrieves the data itself but the version and platform information.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ModulData_Get-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ModulData_Get (API_ModulData* info, const GS::UniString& modulName = GS::EmptyUniString);


/**
 * @brief Returns a list of names of the custom data sections stored in the project database.
 * @ingroup ModulData
 * @param modulNameList [out] List of moduldata names stored by the add-on into the current project.
 * @return
 * 			- NoError - The information was returned successfully.
 * 			- APIERR_BADPARS - The modulNameList parameter is nullptr.
 * @remarks This function is used to retrieve a list of names of the custom data sections embedded by the add-on in the project database.
 * 			In order to get the stored data itself, use the @ref ACAPI_ModulData_Get function using the names retrieved in the list. Empty list means no custom data section is stored in the project. If the project was saved in earlier format than Archicad 13, the modul name of the stored custom data is empty string ("").
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ModulData_GetList-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ModulData_GetList (GS::Array<GS::UniString>* modulNameList);


/**
 * @brief Removes the custom data section stored in the project database.
 * @ingroup ModulData
 * @param modulName [in] Identifier name of the modul data (optional).
 * @return
 * 			- NoError - The information was returned successfully.
 * 			- APIERR_NOMODULEDATA - No custom data section is saved into the project file identified by the add-on's unique modul ID and the modulName parameter.
 * @remarks This function is used to delete the custom data section embedded in the project database.
 * 			Calling @ref ACAPI_ModulData_Delete is equivalent to @ref ACAPI_ModulData_Store (nullptr).
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_ModulData_Delete (const GS::UniString& modulName = GS::EmptyUniString);

/* -- AddOnObject Manager ---------------- */


/**
 * @brief Creates an AddOnObject.
 * @ingroup AddOnObject
 * @param objectName [in] The name of the AddOnObject.
 * @param content [in] The content of the AddOnObject.
 * @param objectGuid [out] The GUID of the created object.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function is used to store custom data into project database. The custom data is represented by AddOnObject.
 * 			This data is avaible in teamwork only in clinet side, it won't be send to the teamwork server. If you need to ensure that the AddOnObject send between users use @ref ACAPI_AddOnObject_CreateObject.
 * 			The content handle will be copied inside the function so it has to be deleted after the function call.
 * 			The stored data can be accessed using objectGuid parameter. The objectName parameter can also be used for identifying the custom data. It can be also emtpy. Archicad does not check if the name is unique.
 * 			If you need to ensure that only one AddOnObject exists with the same name, then use Unique AddOnObjects. See more: @ref ACAPI_AddOnObject_CreateUniqueObject.
 * 			The content handle will be copied inside the function so it has to be deleted after the function call.
 * 			The stored data can be accessed using objectGuid parameter. The objectName parameter can also be used for identifying the custom data. It can be also emtpy. Archicad does not check if the name is unique.
 * 			If you need to ensure that only one AddOnObject exists with the same name, then use Unique AddOnObjects. See more: @ref ACAPI_AddOnObject_CreateUniqueObject.
 */
__APIEXPORT GSErrCode ACAPI_AddOnObject_CreateObject (const GS::UniString& objectName, const GSHandle& content, API_Guid* objectGuid);


/**
 * @brief Creates a Unique AddOnObject.
 * @ingroup AddOnObject
 * @param objectName [in] The name of the Unique AddOnObject.
 * @param objectGuid [out] The GUID of the created object. Value is undefined if an error happened.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_CANCEL - If the user refused to Send Receive all changes.
 * 			- APIERR_NAMEALREADYUSED - If there is already a Unique AddOnObject with the given objectName.
 * 			- APIERR_NOTEAMWORKPROJECT - Indicates that the project is an Offline TeamWork project. Due to possible conflicts, it is not allowed to create Unique AddOnObjects in an Offline Teamwork Project.
 * 			- APIERR_SERVICEFAILED - The created Unique AddOnObject could not be sent to the TeamWork server.
 * @remarks Unique AddOnObjects were introduced to support more restricted but safer TeamWork behaviour. Because multiple general (non-unique) AddOnObjects can exist with the same name, in TeamWork it could happen that two users created "the same" AddOnObject simultaneously, but at the end they ended up with two different AddOnObjects. This led to a lot of confusion.
 * 			With Unique AddOnObjects - like general AddOnObjects - you can store custom data in the project database. However - unlike general AddOnObjects - their names must be and will be unique among each other. Please note that names of a Unique AddOnObject and general AddOnObjects may be equal.
 * 			In a TeamWork project creating Unique AddOnObjects will result in a Full Receive and a Full Send to ensure project consistency. Due to this inconvenience, it is possible to create more Unique AddOnObjects at once with the @ref ACAPI_AddOnObject_CreateUniqueObjectMore function.
 * 			Unlike general AddOnObjects - to ensure no data conflict occurs - it is not possible to give default content to a Unique AddOnObject. To do so, you must call @ref ACAPI_AddOnObject_ModifyObject function.
 * 			The stored data can be accessed using the returned objectGuid. All functions that work for general AddOnObjects work for Unique AddOnObjects, too, except @ref ACAPI_AddOnObject_GetObjectGuidFromName : to get the GUID of a Unique AddOnObject from its name use @ref ACAPI_AddOnObject_GetUniqueObjectGuidFromName instead.
 */
__APIEXPORT GSErrCode ACAPI_AddOnObject_CreateUniqueObject (const GS::UniString& objectName, API_Guid* objectGuid);


/**
 * @brief Creates more Unique AddOnObjects.
 * @ingroup AddOnObject
 * @param objectNames [in] The names of the Unique AddOnObjects. The names must be unique.
 * @param objectGuids [out] The GUIDs of the created objects. One guid is returned to each given name. Empty array is returned if an error happened.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - If the objectNames array is empty or the names in it are not unique among each other.
 * 			- APIERR_NAMEALREADYUSED - If there is already a Unique AddOnObject with one of the given objectNames.
 * 			- APIERR_NOTEAMWORKPROJECT - Indicates that the project is an Offline TeamWork project. Due to possible conflicts, it is not allowed to create Unique AddOnObjects in an Offline Teamwork Project.
 * 			- APIERR_SERVICEFAILED - The created Unique AddOnObjects could not be sent to the TeamWork server.
 * @remarks In a TeamWork project creating Unique AddOnObjects will result in a Full Receive and a Full Send to ensure project consistency. Due to this inconvenience, it is possible to create more Unique AddOnObjects at once with this function.
 * 			For more info, see @ref ACAPI_AddOnObject_CreateUniqueObject.
 */
__APIEXPORT GSErrCode ACAPI_AddOnObject_CreateUniqueObjectMore (const GS::Array<GS::UniString>& objectNames, GS::Array<API_Guid>& objectGuids);


/**
 * @brief Creates an AddOnObject.
 * @ingroup AddOnObject
 * @param objectName [in] The name of the AddOnObject.
 * @param content [in] The content of the AddOnObject.
 * @param objectGuid [out] The GUID of the created object.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function is used to store custom data into project database. The custom data is represented by AddOnObject.
 * 			This data is avaible in teamwork only in clinet side, it won't be send to the teamwork server. If you need to ensure that the AddOnObject send between users use @ref ACAPI_AddOnObject_CreateObject.
 * 			The content handle will be copied inside the function so it has to be deleted after the function call.
 * 			The stored data can be accessed using objectGuid parameter. The objectName parameter can also be used for identifying the custom data. It can be also emtpy. Archicad does not check if the name is unique.
 * 			If you need to ensure that only one AddOnObject exists with the same name, then use Unique AddOnObjects. See more: @ref ACAPI_AddOnObject_CreateUniqueObject.
 * 			The content handle will be copied inside the function so it has to be deleted after the function call.
 * 			The stored data can be accessed using objectGuid parameter. The objectName parameter can also be used for identifying the custom data. It can be also emtpy. Archicad does not check if the name is unique.
 * 			If you need to ensure that only one AddOnObject exists with the same name, then use Unique AddOnObjects. See more: @ref ACAPI_AddOnObject_CreateUniqueObject.
 */
__APIEXPORT GSErrCode ACAPI_AddOnObject_CreateClientOnlyObject (const GS::UniString& objectName, const GSHandle& content, API_Guid* objectGuid);


/**
 * @brief Returns the list of the AddOnObjects.
 * @ingroup AddOnObject
 * @param objects [out] This array will be filled with the GUIDs of the AddOnObjects.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter objects is nullptr
 * @remarks The function returns both general and Unique AddOnObjects.
 */
__APIEXPORT GSErrCode ACAPI_AddOnObject_GetObjectList (GS::Array<API_Guid>* objects);


/**
 * @brief Retrieves the content and the name of the specified AddOnObject from the project database.
 * @ingroup AddOnObject
 * @param objectGuid [in] The GUID of the object.
 * @param objectName [out] The name of the specified object.
 * @param objectContent [out] The content of the specified object.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter objectGuid is APINULLGuid or either objectName or objectContent is nullptr.
 * 			- APIERR_BADID - No object with the specified GUID exists.
 * @remarks Archicad allocates the target buffer in content parameter; the caller add-on is responsible to dispose it with BMKillHandle.
 */
__APIEXPORT GSErrCode ACAPI_AddOnObject_GetObjectContent (const API_Guid& objectGuid, GS::UniString* objectName, GSHandle* objectContent);


/**
 * @brief Modifies the content and/or the name of the specified AddOnObject.
 * @ingroup AddOnObject
 * @param objectGuid [in] The GUID of the object.
 * @param newObjectName [in] The new name of the specified object. If nullptr, the name of the object remains the original name. Must be nullptr if modifying a Unique AddOnObject.
 * @param newObjectContent [in] The new content of the specified object. If nullptr, the content of the object remains the original content. Must not be nullptr if modifying a Unique AddOnObject.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - If the passed objectGuid parameter is NULLGuid, or if neither newObjectName nor newObjectContent is filled, or if modifying a Unique AddOnObject and either newObjectName is not nullptr (it must be) or newObjectContent is nullptr (it must not be).
 * 			- APIERR_BADID - The specified object does not exist.
 * 			- APIERR_NOTMINE - The object is not owned by the current user in teamwork mode.
 * @remarks This function is used for modifying the content or the name of the specified AddOnObject.
 * 			The newObjectContent handle will be copied inside the function so it has to be deleted after the function call.
 */
__APIEXPORT GSErrCode ACAPI_AddOnObject_ModifyObject (const API_Guid& objectGuid, const GS::UniString* newObjectName, const GSHandle* newObjectContent);


/**
 * @brief Retrieves an attribute from the database.
 * @ingroup AddOnObject
 * @param objectGuid [in] The GUID of the object.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The object does not exist.
 * 			- APIERR_NOTMINE - The object is not owned by the current user in teamwork mode.
 * @remarks This function is used to delete an AddOnObject from the project database.
 */
__APIEXPORT GSErrCode ACAPI_AddOnObject_DeleteObject (const API_Guid& objectGuid);


/**
 * @brief Returns the GUID of the specified object.
 * @ingroup AddOnObject
 * @param name [in] The name of the specified object.
 * @param objectGuid [out] The GUID of the object, if the project database contains AddOnObject with the specified name, otherwise APINULLGuid.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter objectGuid is nullptr.
 * @remarks If more AddOnObjects exist with the same name, it is not specified which GUID will be returned.
 * 			Please note that this is a linear time function.
 * 			This function cannot be used to get the GUID of a Unique AddOnObject or AddOnObject or the get GUID-s from other teamwork users.
 * 			You can use Unique AddOnObjects if it is important to have only one AddOnObject with the same name. See AddOnObject Manager for more information.
 * 			Please note that this is a linear time function.
 * 			This function cannot be used to get the GUID of a Unique AddOnObject.
 * 			You can use Unique AddOnObjects if it is important to have only one AddOnObject with the same name. See AddOnObject Manager for more information.
 */
__APIEXPORT GSErrCode ACAPI_AddOnObject_GetObjectGuidFromName (const GS::UniString& name, API_Guid* objectGuid);


/**
 * @brief Returns the GUID of the specified Unique AddOnObject.
 * @ingroup AddOnObject
 * @param name [in] The name of the specified object.
 * @param objectGuid [out] The GUID of the object, if the project database contains Unique AddOnObject with the specified name, otherwise APINULLGuid.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter objectGuid is NULL.
 * @remarks This function cannot be used to get the GUID of a general (non-unique) AddOnObject.
 * 			Please note that this is a linear time function.
 * 			This function cannot be used to get the GUID of a general (non-unique) AddOnObject.
 */
__APIEXPORT GSErrCode ACAPI_AddOnObject_GetUniqueObjectGuidFromName (const GS::UniString& name, API_Guid* objectGuid);


/**
 * @brief Returns the GUID of the specified object.
 * @ingroup AddOnObject
 * @param name [in] The name of the specified object.
 * @param objectGuid [out] The GUID of the object, if the project database contains AddOnObject with the specified name, otherwise APINULLGuid.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter objectGuid is nullptr.
 * @remarks If more AddOnObjects exist with the same name, it is not specified which GUID will be returned.
 * 			Please note that this is a linear time function.
 * 			This function cannot be used to get the GUID of a Unique AddOnObject or AddOnObject or the get GUID-s from other teamwork users.
 * 			You can use Unique AddOnObjects if it is important to have only one AddOnObject with the same name. See AddOnObject Manager for more information.
 * 			Please note that this is a linear time function.
 * 			This function cannot be used to get the GUID of a Unique AddOnObject.
 * 			You can use Unique AddOnObjects if it is important to have only one AddOnObject with the same name. See AddOnObject Manager for more information.
 */
__APIEXPORT GSErrCode ACAPI_AddOnObject_GetClientOnlyObjectGuidFromName (const GS::UniString& name, API_Guid* objectGuid);


/**
 * @brief In teamwork mode this function reserves the specified objects.
 * @ingroup AddOnObject
 * @param objectGuids [in] The list of the objects which must be released.
 * @param conflicts [out] Can be nullptr. If some of the specified objects cannot be reserved because of reservations of other users, this table will be filled with the conflicts.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter objectGuids is empty or contains APINULLGuid.
 * 			- APIERR_BADID - If any of the objectGuids is not an AddOnObject GUID.
 * @remarks If any of the specified objects were modified by another user, Receive Changes operation will be performed in order to get the latest version of the objects from the server.
 */
__APIEXPORT GSErrCode ACAPI_AddOnObject_ReserveObjects (const GS::Array<API_Guid>& objectGuids, GS::HashTable<API_Guid, short>* conflicts);


/**
 * @brief In teamwork mode this function releases the specified objects.
 * @ingroup AddOnObject
 * @param objectGuids [in] The list of the objects which must be released.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter objectGuids is empty or contains APINULLGuid.
 * 			- APIERR_BADID - If any of the objectGuids is not an AddOnObject GUID.
 * @remarks If any of the specified objects were modified, Send Changes operation will be performed in order to send the modified objects to server.
 */
__APIEXPORT GSErrCode ACAPI_AddOnObject_ReleaseObjects (const GS::Array<API_Guid>& objectGuids);


/**
 * @brief In teamwork mode this function sends a request mail in order to request the specified objects from the owners.
 * @ingroup AddOnObject
 * @param objectGuids [in] The list of the objects which must be requested.
 * @param mailText [in] The text of the request mail.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter objectGuids is empty or contains APINULLGuid.
 * 			- APIERR_BADID - If any of the objectGuids is not an AddOnObject GUID.
 */
__APIEXPORT GSErrCode ACAPI_AddOnObject_RequestObjects (const GS::Array<API_Guid>& objectGuids, const GS::UniString& mailText);


/**
 * @brief In teamwork mode this function grants the specified objects to the given user.
 * @ingroup AddOnObject
 * @param objectGuids [in] The list of the objects which must be granted.
 * @param toUserId [in] The teamwork owner, to which the objects must be granted.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter objectGuids is empty or contains APINULLGuid.
 * 			- APIERR_BADID - If any of the objectGuids is not an AddOnObject GUID.
 * @remarks If the function has completed with success then the specified objects will be granted to the given user. The process runs in silent mode, no dialogs or messages will interrupt.
 */
__APIEXPORT GSErrCode ACAPI_AddOnObject_GrantObjects (const GS::Array<API_Guid>& objectGuids, short toUserId);


/**
 * @brief Returns the ownerId of the specified object in teamwork mode.
 * @ingroup AddOnObject
 * @param objectGuid [in] The GUID of the specified object.
 * @param ownerId [out] The teamwork owner user of the specified object.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter objectGuid is APINULLGuid or ownerId is nullptr
 * 			- APIERR_BADID - AddOnObject does not exist.
 */
__APIEXPORT GSErrCode ACAPI_AddOnObject_GetTeamworkOwnerId (const API_Guid& objectGuid, short* ownerId);


/**
 * @brief Determines if the project database contains the specified AddOnObject or not.
 * @ingroup AddOnObject
 * @param objectGuid [in] The GUID of the specified object..
 * @param objectExists [out] true if the object exists, otherwise false.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter objectGuid is APINULLGuid or objectExists is nullptr
 * 			- APIERR_BADID - The object specified by GUID exists, but its type is not AddOnObject.
 */
__APIEXPORT GSErrCode ACAPI_AddOnObject_ExistsObject (const API_Guid& objectGuid, bool* objectExists);


/**
 * @brief Sets various UI properties of an AddOnObject.
 * @ingroup AddOnObject
 * @param objectGuid [in] GUID of the specified object. Can be NULL if name-based identification is intended.
 * @param name [in] The name of the specified object. Can be NULL if only GUID-based identification is intended.
 * @param localisedName [in] The localised name of the specified object (or objects if objectGuid is NULL and there are more AddOnObjects with the same name).
 * @param dialogMenuStringId [in] The id of the menu which must be called if Show button is pressed on Teamwork User interface.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Both objectGuid and name are NULL, or localisedName is empty string.
 * @remarks This function is used to register UI properties for AddOnObject. UI properties are localised name and the menu command id. The registered properties will be used for all AddOnObjects which have the specified GUID or name.
 * 			If Archicad looks for a UI property, first tries to find it by GUID. If the property is not found, Archicad also tries to find it by name. So the registration can be done even if no instance of AddOnObject exists: in this case objectGuid should be NULL. Please note that if only the name is given for a UI property, then all AddOnObjects (both general and unique) with this name will have the same UI property.
 */
__APIEXPORT GSErrCode ACAPI_AddOnObject_SetUIProperties (const API_Guid* objectGuid, const GS::UniString* name, const GS::UniString& localisedName, short dialogMenuStringId);

/* -- Notification Manager ---------------- */


/**
 * @brief Register or unregister your add-on to be notified of application and project events.
 * @ingroup ProjectOperation
 * @ingroup Notification
 * @param eventTypes [in] A combination of different @ref API_NotifyEventID values, specifying the types of project events you are interested in.
 * @param handlerProc [in] The callback procedure to call when notifications are sent out on different project events. Specifying nullptr here means you don't need the notifications any more.
 * @return
 * 			- NoError - The requested operation finished successfully.
 * @remarks This function enables the API tool add-on catch events happening to the project. Each time when such an event occurs the server application calls the supplied handlerProc of your those add-ons which have been registered for this event previously.
 * 			If you do not need to catch the project events any longer, please remember to unregister by calling @ref ACAPI_ProjectOperation_CatchProjectEvent for the required element type with nullptr in the handlerProc parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ProjectOperation_CatchProjectEvent-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ProjectOperation_CatchProjectEvent		(GSFlags						eventTypes,
																			 APIProjectEventHandlerProc		*handlerProc);


/**
 * @brief Register or unregister your add-on to be notified of Project Navigator changes.
 * @ingroup Notification
 * @param eventTypes [in] A combination of different @ref API_NotifyViewEventID values, specifying the types of project navigator events you are interested in.
 * @param mapId [in] Specifies the project navigator map you are interested in.
 * @param handlerProc [in] The callback procedure to call when notifications are sent out... Specifying nullptr here means you don't need the notifications any more.
 * @return
 * 			- NoError - The requested operation finished successfully.
 * 			- APIERR_BADPARS - The eventTypes parameter is invalid.
 * @remarks This function enables the API tool add-on catch the changes of Project Navigator items in the specified map. Each time when a navigator item is inserted, modified, deleted or opened the server application calls the supplied handlerProc of your those add-ons which have been registered for this event previously.
 * 			If you do not need to catch any project navigator event of the specified map any longer, please remember to unregister by calling @ref ACAPI_Notification_CatchViewEvent for the required map with nullptr in the handlerProc parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Notification_CatchViewEvent-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Notification_CatchViewEvent			(GSFlags						eventTypes,
																			 API_NavigatorMapID				mapId,
																			 APIViewEventHandlerProc		*handlerProc);


/**
 * @brief Turns the monitoring of toolbox item changes on/off.
 * @ingroup Notification
 * @param handlerProc [in] The callback procedure to call when notifications are sent out on changes in the selection. Specifying nullptr here means you don't need the notifications any more.
 * @return
 * 			- NoError - The function completed successfully.
 * @remarks This function is used to register/unregister an addon which wants to monitor the changes in the toolbox, i.e. when the user switches to an other toolbox item. You do not have to call @ref ACAPI_KeepInMemory afterwards, as the API ensures that add-ons with installed notification handlers won't be unloaded. After registration your add-on's handlerProc you will be called when the selected toolbox item changes.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Notification_CatchToolChange-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Notification_CatchToolChange		(APIToolChangeHandlerProc		*handlerProc);


/**
 * @brief Turns the monitoring of selection changes on/off.
 * @ingroup Notification
 * @ingroup Selection
 * @param handlerProc [in] The callback procedure to call when notifications are sent out on changes in the selection. Specifying nullptr here means you don't need the notifications any more.
 * @return
 * 			- NoError - The function completed successfully.
 * @remarks This function is used to register/unregister an add-on which wants to monitor the changes in selection. You do not have to call @ref ACAPI_KeepInMemory afterwards, as the API ensures that add-ons with installed notification handlers won't be unloaded. After registration your add-on's handlerProc you will be called when the selection changes.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Notification_CatchSelectionChange-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Notification_CatchSelectionChange	(APISelectionChangeHandlerProc	*handlerProc);


/**
 * @brief Register or unregister your add-on to be notified if the default settings of a given element type is modified.
 * @ingroup Element
 * @ingroup Notification
 * @param elemType [in] Specifies the type of element for which your add-on should be notified. In order to receive notification on changing the default settings of any type of element, you simply pass nullptr as this parameter.
 * @param handlerProc [in] The callback procedure to call when notifications are sent out on changing the default settings of this element type. Specifying nullptr here means you don't need the notifications any more.
 * @return
 * 			- NoError - The required operation finished successfully.
 * 			- APIERR_BADID - The elemType parameter contains an invalid type.
 * @remarks This function enables the API tool add-on catch the modification of the default settings of a certain element type. Each time when one of the default parameters of the element type is modified the server application calls the supplied callback procedure of the add-on provided that it has been registered for this event previously.
 * 			If you do not need to catch the changes of default settings any longer, please remember to unregister by calling @ref ACAPI_Element_CatchChangeDefaults for the required element type with nullptr in the handlerProc parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_CatchChangeDefaults-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_CatchChangeDefaults	(const API_ToolBoxItem			*elemType,
																			 APIDefaultsChangeHandlerProc	*handlerProc);


/**
 * @brief Register or unregister your add-on to be notified if the given type of element is created.
 * @ingroup Element
 * @ingroup Notification
 * @param elemType [in] Specifies the type of element for which your add-on should be notified. In order to receive notification on the creation of any type of elements, you simply pass nullptr as this parameter.
 * @param handlerProc [in] The callback procedure to call when notifications are sent out on creating this type of element. Specifying nullptr here means you don't need the notifications any more.
 * @return
 * 			- NoError - The requested operation finished successfully.
 * 			- APIERR_BADID - The elemType parameter contains an invalid type.
 * @remarks This function enables the API tool add-on catch the event of creating a certain type of element. Each time when an element of this type is created the server application calls the supplied handlerProc of your those add-ons which have been registered for this event previously.
 * 			If you do not need to catch the creation of new elements any longer, please remember to unregister by calling @ref ACAPI_Element_CatchNewElement for the required element type with nullptr in the handlerProc parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_CatchNewElement-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_CatchNewElement		(const API_ToolBoxItem			*elemType,
																			 APIElementEventHandlerProc		*handlerProc);


/**
 * @brief Register or unregister your add-on to be notified if some attributes are deleted and replaced by other attributes.
 * @ingroup Notification
 * @ingroup Attribute
 * @since Archicad 25
 * @param handlerProc [in] The callback procedure to call when notifications are sent out on replacement of attributes. Specifying nullptr here means you don't need the notifications any more.
 * @return
 * 			- NoError - The required operation finished successfully.
 * @remarks This function enables the API tool add-on to catch the deletion and replacement of the attributes in the project. This operation can be done with the Delete and Replace option in the Attribute Manager dialog.
 * 			If you do not need to catch the changes of default settings any longer, please remember to unregister by calling @ref ACAPI_Notification_CatchAttributeReplacement for the required element type with nullptr in the handlerProc parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Notification_CatchAttributeReplacement-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Notification_CatchAttributeReplacement	(APIAttributeReplacementHandlerProc  *handlerProc);


/**
 * @brief Installs an element observer function which receives notifications on elements' changes.
 * @ingroup Element
 * @ingroup Notification
 * @param handlerProc [in] The callback procedure to call when notifications are sent out on changes of elements. Specifying nullptr here means you don't need the notifications any more.
 * @return
 * 			- NoError - The function completed successfully.
 * @remarks This function is used to register/unregister an add-on which wants to monitor the changes in elements. This is a common callback for all the different element observers which can be attached to an element with @ref ACAPI_Element_AttachObserver. After registration your add-on's handlerProc you will be called when any of the monitored elements change. For more details see also the Element related notifications paragraph of the Notification Manager.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_InstallElementObserver-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_InstallElementObserver	(APIElementEventHandlerProc		*handlerProc);


/**
 * @brief Returns the transformation parameters of the actual edit operation.
 * @ingroup Notification
 * @param actTranPars [out] The transformation parameters to be returned.
 * @return
 * 			- NoError - The function has been executed without error.
 * 			- APIERR_BADPARS - The actTranPars parameter is nullptr.
 * @remarks This function is used to get the parameters of the actual editing operation. The transformation data is valid only between a @c APINotifyElement_BeginEvents and the following @c APINotifyElement_EndEvents notification.
 * 			By using this function your add-on is able to update some elements according to the user's edit action.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Notification_GetTranParams-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Notification_GetTranParams			(API_ActTranPars *actTranPars);


/**
 * @brief Returns the parent of the actual element your addon received notification for.
 * @ingroup Notification
 * @ingroup Notification
 * @param element [out] The parent element to be retrieved.
 * @param memo [out] Additional data of the parent element.
 * @param mask [in] Mask for specifying the relevant memo handles to be retrieved.
 * @param userData [out] Userdata of the parent element.
 * @return
 * 			- NoError - The function was executed without error.
 * 			- APIERR_REFUSEDCMD - There was no parent element during the action.
 * @remarks This function is used to retrieve the original element data from which the notified element has been derived. If you pass nullptr values in the memo and userData parameters, the function performs an @ref ACAPI_Element_Get operation, otherwise it behaves like the @ref ACAPI_Element_GetMemo or the @ref ACAPI_Element_GetUserData function.
 * 			You can use this function to find out what changes have been made to the original element during the operation.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Notification_GetParentElement-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Notification_GetParentElement		(API_Element*			element,
																			 API_ElementMemo*		memo,
																			 UInt64					mask,
																			 API_ElementUserData*	userData);


/**
 * @brief Sets notification handler for element reservation changes.
 * @ingroup Notification
 * @param handlerProc [in] Notification handler function to be called on the specified event. Pass nullptr to unsubscribe from this notification.
 * @param filterElementsInterestedOnly [in] List of element guids; optional parameter for controlling the range of elements of interest. If passed, the reservation change notifications will be sent for only these elements, otherwise every element reservation changes will be reported.
 * @return
 * 			- NoError - The function completed successfully.
 * @remarks This function is used to subscribe an add-on to be notified when element reservations have been changed in Teamwork. Once a APIReservationChangeHandlerProc function pointer is passed, the add-on remains loaded in the memory, and receives the notifications. When the add-on does not need these notifications any more, you can stop receiving them by calling this function with nullptr in the first argument.
 * 			In case the add-on is interested only in specified elements, you can set the focus on those elements by passing the list of the element guids in the filterElementsInterestedOnly parameter. Note that there can be only one handler function set for this notification at the same time, that is you cannot set multiple handlers for different lists of elements.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Notification_CatchElementReservationChange-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Notification_CatchElementReservationChange	(APIReservationChangeHandlerProc*	handlerProc,
																					 const GS::HashSet<API_Guid>*		filterElementsInterestedOnly = nullptr);


/**
 * @brief Sets notification handler for reservation changes of lockable objects.
 * @ingroup Notification
 * @param handlerProc [in] Notification handler function to be called on the specified event. Pass nullptr to unsubscribe from this notification.
 * @param filterLockablesInterestedOnly [in] List of guids of lockable objects; optional parameter for controlling the range of objects of interest. If passed, the lock change notifications will be sent for only these objects, otherwise every lock changes will be reported.
 * @return
 * 			- NoError - The function completed successfully.
 * @remarks This function is used to subscribe an add-on to be notified when reservations of lockable objects (e.g. attributes, favorites, model view options) have been changed in Teamwork. Once a APILockChangeHandlerProc function pointer is passed, the add-on remains loaded in the memory, and receives the notifications. When the add-on does not need these notifications any more, you can stop receiving them by calling this function with nullptr in the first argument.
 * 			In case the add-on is interested only in specified objects, you can set the focus on those objects by passing the list of the guids in the filterLockablesInterestedOnly parameter (see the list of currently available lockable object sets). Note that there can be only one handler function set for this notification at the same time, that is you cannot set multiple handlers for different lists of lockable objects.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Notification_CatchLockableReservationChange-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Notification_CatchLockableReservationChange	(APILockChangeHandlerProc*			handlerProc,
																					 const GS::HashSet<API_Guid>*		filterLockablesInterestedOnly = nullptr);


/**
 * @brief Catches notifications on license borrowing status changes.
 * @ingroup LicenseInfo
 * @ingroup Notification
 * @param handlerProc [in] The callback function which receives the notifications.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function allows you to act on license borrowing and returning.
 */
__APIEXPORT GSErrCode ACAPI_Licensing_CatchLicenseBorrowStatusChange	(APILicenseBorrowStatusChangeHandlerProc*	handlerProc);


/**
 * @brief Sends out an @c APINotify_ClassificationVisibilityChanged project event notification to the other add-ons to state that at least one classification's visibility has changed.
 * @ingroup Notification
 * @ingroup Classification
 * @return
 * 			- NoError - The function completed successfully.
 */
__APIEXPORT GSErrCode ACAPI_Notification_ClassificationVisibilityChanged ();


/**
 * @brief Sends out an @c APINotify_PropertyVisibilityChanged project event notification to the other add-ons to state that at least one property's visibility has changed.
 * @ingroup Notification
 * @ingroup Property
 * @return
 * 			- NoError - The function completed successfully.
 */
__APIEXPORT GSErrCode ACAPI_Notification_PropertyVisibilityChanged ();


/**
 * @brief Register an event handler in your add-on.
 * @ingroup Notification
 * @since Archicad 26
 * @param eventHandler [in] The event handler to be registered.
 * @param id [out] The identifier of the successfully registered event handler.
 * @return
 * 			- NoError - The requested operation finished successfully.
 * 			- APIERR_BADPARS - The requested operation failed due to a nullptr in-parameter.
 * @remarks In case you register an event handler your add-on will automatically be kept loaded in memory.
 * 			The id out-parameter can be used to manually unregister the event handler by calling @ref ACAPI_Notification_UnregisterEventHandler.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Notification_RegisterEventHandler-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Notification_RegisterEventHandler (GS::Owner<API_IEventHandler> eventHandler, API_Guid& id);


/**
 * @brief Unregister an event handler from your add-on.
 * @ingroup Notification
 * @since Archicad 26
 * @param id [in] The identifier of a previously registered event handler.
 * @return
 * 			- NoError - The requested operation finished successfully.
 * 			- APIERR_BADPARS - The requested operation failed due to an invalid id in-parameter.
 * @remarks If not specified otherwise by @ref ACAPI_KeepInMemory the add-on will automatically unload if you unregister all event handlers.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Notification_UnregisterEventHandler-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Notification_UnregisterEventHandler (const API_Guid& id);


/* -- Miscellaneous ----------------------- */


/**
 * @brief Activates or deactivates an add-on's property handler.
 * @ingroup Property
 * @ingroup AddOnIntegration
 * @param strResID [in] tells for which property handler is this command issued
 * @param active [in] turns the property handler on/off
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks Only one property handler can be active in Archicad at a time. The return value of this functions depends on the user, as a dialog pops up when you issue this command. When the function returns, you should adjust your menu items accordingly.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ActivatePropertyObjectHandler-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ActivatePropertyObjectHandler (short strResID, bool active);


/* --- Favorite Functions	--------------- */


/**
 * @brief Loads the parameters of the given favorite.
 * @ingroup Favorite
 * @param favorite [in/out] The Favorite entry settings. On input, it identifies the Favorite based on its name. On return, the other fields are filled.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_GENERAL - The Favorites list could not be retrieved.
 * 			- APIERR_BADPARS - The favorite parameter is nullptr.
 * 			- APIERR_BADNAME - Invalid name given (there is no Favorite with the given favorite.name).
 * @remarks This function does not create a new element into the database, you must use the @ref ACAPI_Element_Create function to do so.
 */
__APIEXPORT GSErrCode ACAPI_Favorite_Get (API_Favorite* favorite);


/**
 * @brief Creates a new Favorites entry based on the given element.
 * @ingroup Favorite
 * @param favorite [in] The Favorite entry settings.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADNAME - Invalid name given.
 * 			- APIERR_GENERAL - The new Favorites list entry could not be created.
 * 			- APIERR_BADPARS - Invalid element given (invalid library part ID), or a marker was given with an element that is not an object.
 * 			- APIERR_BADCLASSIFICATION - One of the specified classification items is not available for the given element.
 */
__APIEXPORT GSErrCode ACAPI_Favorite_Create (const API_Favorite& favorite);


/**
 * @brief Changes an existing Favorite (identifed by name).
 * @ingroup Favorite
 * @param favorite [in] The Favorite entry settings.
 * @param elementMask [in] Optional parameter for masking the relevant fields of favorite.element.
 * @param memoMask [in] Optional parameter for specifying the relevant parts of the favorite.memo parameter.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADNAME - Invalid name given (there is no Favorite with the given favorite.name).
 * 			- APIERR_GENERAL - The Favorites list entry could not be changed.
 * 			- APIERR_BADPARS - Invalid element given (invalid library part ID), or a marker was given with an element that is not an object.
 * 			- APIERR_BADCLASSIFICATION - One of the specified classification items is not available for the given element.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Favorite_Change-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Favorite_Change (const API_Favorite& favorite,
															   const API_Element*  elementMask = nullptr,
															   const UInt64		   memoMask = 0);


/**
 * @brief Renames an existing Favorite (identifed by name).
 * @ingroup Favorite
 * @param oldName [in] The name of the existing Favorite entry.
 * @param newName [in] The new name.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADNAME - Invalid name given (empty name is invalid, or there is no Favorite with the given oldName).
 * 			- APIERR_GENERAL - The Favorites list entry could not be changed.
 * 			- APIERR_NAMEALREADYUSED - newName is already used as a Favorite name.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Favorite_Rename-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Favorite_Rename (const GS::UniString& oldName, const GS::UniString& newName);


/**
 * @brief Deletes a Favorites entry.
 * @ingroup Favorite
 * @param name [in] The name of the Favorites entry to delete.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADNAME - Invalid name given.
 * 			- APIERR_NOTMINE - In Teamwork mode, the given Favorites entry is owned by someone else.
 */
__APIEXPORT GSErrCode ACAPI_Favorite_Delete (const GS::UniString& name);


/**
 * @brief Returns the names and indexes of the contents of the Favorites list, along with the amount of entries, for a given type and variation.
 * @ingroup Favorite
 * @since Archicad 26
 * @param type [in] The given type of elements.
 * @param count [out] The amount of entries for that type and variation combination in the Favorites list.
 * @param folders [out] The folders of the entries for that type and variation combination in the Favorites list.
 * @param names [out] The names of the entries for that type and variation combination in the Favorites list.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_GENERAL - The Favorites list could not be retrieved.
 * @remarks The @c API_FavoriteFolderHierarchy type is a typedef of GS::Array<GS::UniString>.
 * 			From version 26 the typeID and variationID parameters were merged into a single @ref API_ElemType parameter.
 */
__APIEXPORT GSErrCode ACAPI_Favorite_GetNum (const API_ElemType&						type,
															   short									*count,
															   GS::Array<API_FavoriteFolderHierarchy>	*folders,
															   GS::Array<GS::UniString>					*names);

/**
 * @brief Returns the favorite preview image.
 * @ingroup Favorite
 * @param name [in] The name of the given favorite.
 * @param viewType [in] The type of the view.
 * @param nativeImagePtr [out] A pointer to the preview image.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - If the given nativeImagePtr is nullptr.
 * 			- APIERR_BADNAME - If there is no favorite with the given name.
 */
__APIEXPORT GSErrCode ACAPI_Favorite_GetPreviewImage (const GS::UniString&	 name,
																		API_ImageViewID			 viewType,
																		NewDisplay::NativeImage* nativeImagePtr);


/**
 * @brief Imports the contents of a Favorites file or folder into the plan.
 * @ingroup Favorite
 * @param location [in] The path to the Favorite file or folder to import.
 * @param targetFolder [in] The folder to import the Favorites to.
 * @param importFolders [in] Specifies if the imported folders should be kept (all Favorites will be imported into the targetFolder otherwise).
 * @param conflictPolicy [in] Specifies what to do when an imported Favorite already exists in the plan.
 * 						 |API_FavoriteNameConflictResolutionPolicy|Meaning|
 * 						 |--- |--- |
 * 						 |API_FavoriteError|If one of the imported Favorites already exists in the plan, return with APIERR_NAMEALREADYUSED and set the firstConflictName parameter to the conflicting name|
 * 						 |API_FavoriteSkip|If an imported Favorite already exists in the plan, keep the old one in the plan, and ignore the imported one.|
 * 						 |API_FavoriteOverwrite|If an imported Favorite already exists in the plan, keep the imported one and delete the old one in the plan.|
 * 						 |API_FavoriteAppend|If an imported Favorite already exists in the plan, generate a new name for the imported one and keep both Favorites.|
 * @param firstConflictName [out] The name of the first Favorite that was imported and already existed in the plan. Only filled if the conflictPolicy parameter is @c API_FavoriteError.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOACCESSRIGHT - The Favorites list is not editable in a teamwork project.
 * 			- APIERR_BADPARS - The location isn't a valid Favorite file or folder path.
 * 			- APIERR_NAMEALREADYUSED - The conflictPolicy parameter is @c API_FavoriteError, and there was a name conflict.
 * @remarks The @c API_FavoriteFolderHierarchy type is a typedef of `GS::Array<GS::UniString>`.
 */
__APIEXPORT GSErrCode ACAPI_Favorite_Import (const IO::Location&							location,
															   const API_FavoriteFolderHierarchy&			targetFolder,
															   bool											importFolders,
															   API_FavoriteNameConflictResolutionPolicy		conflictPolicy,
															   GS::UniString								*firstConflictName = nullptr);

/**
 * @brief Reads the contents of a Favorites file or folder.
 * @ingroup Favorite
 * @param location [in] The path to the Favorite file or folder to read.
 * @param favorites [out] The parameters of the favorites that have been read successfully.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The location isn't a valid Favorite file or folder path.
 * @remarks Reads the contents of a Favorite file or folder and returns them without modifying the plan. `ACAPI_Favorite_Read` combined
 * 			with @ref ACAPI_Favorite_Create works much like @ref ACAPI_Favorite_Import, however it gives more control, but it is less efficient.
 */
__APIEXPORT GSErrCode ACAPI_Favorite_Read	  (const IO::Location&		location,
															   GS::Array<API_Favorite>*	favorites);


/**
 * @brief Exports the Favorites in the plan into a Favorites file or folder.
 * @ingroup Favorite
 * @param location [in] The path to the file (if the location has the Favorite binary's extension) or folder (otherwise) to export to.
 * @param names [in] The list of the Favorites to export.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOACCESSRIGHT - The location file or folder couldn't be opened for write.
 */
__APIEXPORT GSErrCode ACAPI_Favorite_Export (const IO::Location&				location,
															   const GS::Array<GS::UniString>	*names = nullptr);


/* -- Teamwork Control -------------------- */


/**
 * @brief Tells whether the currently opened project is a Teamwork project.
 * @ingroup Teamwork
 * @return
 * 			- true - The current project is a shared Teamwork project.
 * 			- false - The current project is a solo project, or there is no open project at all.
 * @remarks This function tells if the currently project was opened in Teamwork mode, that is the user is joined to a shared Teamwork project on a BIM Server.
 * 			Note that being connected to a Teamwork project does not mean necessarily online connection to the server. In order to check the online-offline status, use @ref ACAPI_Teamwork_IsOnline.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Teamwork_HasConnection-Example-Snippet
 */
__APIEXPORT bool ACAPI_Teamwork_HasConnection (void);


/**
 * @brief Tells whether the client is online connected to the BIM server.
 * @ingroup Teamwork
 * @return
 * 			- true - The Teamwork user is working in online mode.
 * 			- false - The Teamwork user is working in offline mode.
 * @remarks Use this function to check if the connection status between the client application and the BIM server is online.
 * 			Note that a Teamwork user joined to a shared project is still in Teamwork mode even if the connection staus is offline. To check whether the project the user is working with is a Teamwork project, use @ref ACAPI_Teamwork_HasConnection.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Teamwork_IsOnline-Example-Snippet
 */
__APIEXPORT bool ACAPI_Teamwork_IsOnline (void);


/**
 * @brief Tells whether the given location refers to a BIM Server Library Part.
 * @ingroup Teamwork
 * @param location [in] Location of a library part.
 * @return
 * 			- true - The given location is a BIM Server Library Part.
 * 			- false - The given location is not a BIM Server Library Part.
 */
__APIEXPORT bool ACAPI_Teamwork_IsServerLibPart (const IO::Location& location);


/**
 * @brief Extracts details from the given location about the teamwork project.
 * @ingroup Teamwork
 * @since Archicad 25
 * @param twProjectLocation [in] The location URI of the teamwork project.
 * @param serverUrl [out] The URL of the teamwork (BIMcloud) server.
 * @param projectName [out] The name of the project on the server.
 * @param userName [out] The username of the logged in user.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOTEAMWORKPROJECT - The given project is not Teamwork project.
 * @remarks This function extracts information only from the given location. It does not try to reach the server and does not retrieve any data from it.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Teamwork_GetTeamworkProjectDetails-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Teamwork_GetTeamworkProjectDetails (const IO::Location&	twProjectLocation,
																								 GS::UniString*			serverUrl = nullptr,
																								 GS::UniString*			projectName = nullptr,
																								 GS::UniString*			userName = nullptr);


/**
 * @brief Checks whether the current Teamwork user has access right to create a certain type of object.
 * @ingroup Teamwork
 * @param objectId [in] Unique identifier of the object
 * @return
 * 			- true - The current user has sufficient privileges to create the given type of objects.
 * 			- false - The current user is not allowed to create the given type of objects.
 * @remarks Use this function to decide whether the current Teamwork user has right to create a given type of objects. The access rights are pre-set by the Project Administrator.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Teamwork_HasCreateRight-Example-Snippet
 */
__APIEXPORT bool ACAPI_Teamwork_HasCreateRight (const API_Guid& objectId);


/**
 * @brief Checks whether the current Teamwork user has access right to delete or modify a certain type of object.
 * @ingroup Teamwork
 * @param objectId [in] Unique identifier of the object
 * @return
 * 			- true - The current user has sufficient privileges to delete or modify the given type of objects.
 * 			- false - The current user is not allowed to delete or modify the given type of objects.
 * @remarks Use this function to decide whether the current Teamwork user has right to delete or modify a given type of objects. The access rights are pre-set by the Project Administrator.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Teamwork_HasDeleteModifyRight-Example-Snippet
 */
__APIEXPORT bool ACAPI_Teamwork_HasDeleteModifyRight (const API_Guid& objectId);


/**
 * @brief Retrieves the reservation status of a lockable object set.
 * @ingroup Teamwork
 * @since Archicad 25
 * @param objectId [in] Unique identifier of the lockable object set
 * @param conflicts [out] List of conflicting users (optional, can be nullptr or omitted)
 * @return
 * 			- @c APILockableStatus_NotExist - No Teamwork connection, or the passed objectId parameter does not identifies a valid lockable object set
 * 			- @c APILockableStatus_Free - The given lockable object set is available for reservation, not locked
 * 			- @c APILockableStatus_Editable - The given lockable object set is editable, already reserved by the current user
 * 			- @c APILockableStatus_Locked - The given lockable object set is reserved by someone else
 * 			- @c APILockableStatus_NotAvailable - Server is offline or not available
 * @remarks This function is used to retrieve the current reservation status of a lockable object set.
 * 			In a Teamwork project object sets (like attributes, favorites, project info, etc.) can be locked by any project members having sufficient access rights, using the reservation panel on the settings dialogs. Once the user gains the lock, the object set is syncronized from the server project, that is the user practically works with exactly the same data the server has. When releasing it, the modifications to the object set are sent back to the server.
 * 			Note that a reserved lockable object set is still editable in offline mode, though you cannot release the object set until the connection status becomes online.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Teamwork_GetLockableStatus-Example-Snippet
 */
__APIEXPORT API_LockableStatus ACAPI_Teamwork_GetLockableStatus (const API_Guid&				objectId,
																						 GS::PagedArray<short>*			conflicts = nullptr);


/**
 * @brief Retrieves the unique identifier of a lockable object set with a string identifier.
 * @ingroup Teamwork
 * @since Archicad 25
 * @param objectSetName [in] String identifier of the lockable object set (see below)
 * @return
 * 			- NoError - The function returns the Guid of the named lockable object set if found by the given objectSetName string, otherwise it returns APINULLGuid.
 * @remarks This function is used to retrieve the identifier of a named lockable object set, such as attribute types, favorites, model view options.
 * 			In certain cases lockable object sets need to be reserved simultaneously. For this purpose compound lockable object sets were introduced, to hold the lockable object sets, and to make these sets be reserved together. Reserving individually a lockable object set which belongs to a compound one may result insecure functionality in the Teamwork project, should be avoided.
 * 			Compound lockable object sets are indentified with a string. Currently the following compound lockable object sets are used:
 * 			- Layers, Layer Combinations (compound identifier name: "LayerSettingsDialog")
 * 			- Project Preferences Data, Dimension Standards (compound identifier name: "PreferencesDialog")
 * 			Note that before API version 20, this function handled compound lockable object sets only. From API 20 you need to use this function to retrieve the guid of all lockable object sets.
 * 			The list of the currently available lockable object set identifiers:
 * 			|Object set | Identifier string|
 * 			|-----------|------------------|
 * 			|Building Materials | "BuildingMaterials"|
 * 			|Cities | "Cities"|
 * 			|Composites | "Composites"|
 * 			|Favorites | "Favorites"|
 * 			|Fill Types | "FillTypes"|
 * 			|Layers, Layer Combinations | "LayerSettingsDialog"|
 * 			|Line Types | "LineTypes"|
 * 			|Markup Styles | "MarkupStyles"|
 * 			|MEP Systems | "MEPSystems"|
 * 			|Model View Options | "ModelViewOptions"|
 * 			|Operation Profiles | "OperationProfiles"|
 * 			|Pen Tables | "PenTables"|
 * 			|Profiles | "Profiles"|
 * 			|Project Info | "ProjectInfo"|
 * 			|Project Location | "GeoLocation"|
 * 			|Project Preferences, Dimension Standards | "PreferencesDialog"|
 * 			|Graphic Overrides | "GraphicOverrides"|
 * 			|Surface Materials | "Surfaces"|
 * 			|Zone Categories | "ZoneCategories"|
 * 			For more information on lockable object sets see the Teamwork Control page.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Teamwork_FindLockableObjectSet-Example-Snippet
 */
__APIEXPORT API_Guid ACAPI_Teamwork_FindLockableObjectSet (const GS::UniString&		objectSetName);


/**
 * @brief Reserves a lockable object set in Teamwork mode.
 * @ingroup Teamwork
 * @since Archicad 25
 * @param objectId [in] Unique identifier of the lockable object set
 * @param conflicts [out] List of conflicting users (optional, can be nullptr or omitted)
 * @param enableDialogs [in] Show dialogs during the process? (optional, by default the dialogs are enabled)
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOPLAN - There is no open project.
 * 			- APIERR_NOTEAMWORKPROJECT - The current project is not Teamwork project.
 * 			- APIERR_BADID - The given objectId is not a valid lockable object set identifier.
 * 			- APIERR_SERVICEFAILED - The lock cannot be obtained, or the operation has failed due to communication or server error.
 * @remarks This function is used to reserve a lockable object set in Teamwork mode.
 * 			Before reserving a lockable object set, make sure that the current user has sufficient privileges to edit the object set (ACAPI_Teamwork_HasDeleteModifyRight). It is recommended to check the locking status also before reservation (ACAPI_Teamwork_GetLockableStatus).
 * 			Do not forget to release the lockable object set when reservation is not needed any more.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Teamwork_ReserveLockable-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Teamwork_ReserveLockable (const API_Guid&					objectId,
																					   GS::PagedArray<short>*			conflicts = nullptr,
																					   bool								enableDialogs = true);


/**
 * @brief Releases a lockable object set in Teamwork mode.
 * @ingroup Teamwork
 * @since Archicad 25
 * @param objectId [in] Unique identifier of the lockable object set
 * @param enableDialogs [in] Show dialogs during the process?
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOPLAN - There is no open project.
 * 			- APIERR_NOTEAMWORKPROJECT - The current project is not Teamwork project.
 * 			- APIERR_BADID - The given objectId is not a valid lockable object set identifier.
 * 			- APIERR_SERVICEFAILED - The object set cannot be unlocked, or the operation has failed due to communication or server error.
 * @remarks This function is used to release a lockable object set previously reserved by the current user.
 * 			The modifications to the object set are sent to the server project right before the server actually unlocks the objects.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Teamwork_ReleaseLockable-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Teamwork_ReleaseLockable (const API_Guid&					objectId,
																					   bool								enableDialogs = true);


/**
 * @brief Reserves elements in Teamwork mode.
 * @ingroup Teamwork
 * @since Archicad 25
 * @param elements [in] List of elements to be reserved.
 * @param conflicts [out] List of elements which cannot be reserved (optional, can be nullptr).
 * @param enableDialogs [in] Show dialogs during the process? (optional, by default the dialogs are enabled)
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOPLAN - There is no open project.
 * 			- APIERR_NOTEAMWORKPROJECT - The current project is not Teamwork project.
 * @remarks This function attempts to reserve the elements specified with the guid list.
 * 			If the conflicts parameter is given, the function returns the list of unsuccessful reservations with the userId of the conflicting team members.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Teamwork_ReserveElements-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Teamwork_ReserveElements (const GS::Array<API_Guid>&		elements,
																					   GS::HashTable<API_Guid, short>*	conflicts = nullptr,
																					   bool								enableDialogs = true);


/**
 * @brief Releases elements in Teamwork mode.
 * @ingroup Teamwork
 * @since Archicad 25
 * @param elements [in] List of elements to be released.
 * @param enableDialogs [in] Show dialogs during the process? (optional, by default the dialogs are enabled)
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOPLAN - There is no open project.
 * 			- APIERR_NOTEAMWORKPROJECT - The current project is not Teamwork project.
 * @remarks This function is used to release the elements specified with the guid list.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Teamwork_ReleaseElements-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Teamwork_ReleaseElements (const GS::Array<API_Guid>&		elements,
																					   bool								enableDialogs = true);


/**
 * @brief Reserves the Hotlink/XRef Management in Teamwork mode.
 * @ingroup Teamwork
 * @param conflict [out] userId of the current owner if there is any (optional, can be nullptr).
 * @return
 * 			- NoError - The function has completed with success.
 * 			- Error - The Hotlink/XRef Management is reserved by another team member.
 * 			- APIERR_NOPLAN - There is no open project.
 * 			- APIERR_NOTEAMWORKPROJECT - The current project is not a Teamwork project.
 * @remarks This function is used to reserve the Hotlink/XRef Management.
 * 			If the conflict parameter is given, it will contain the userId of the conflicting team member if there is any.
 * 			You can find out more about the owner from the @ref API_SharingInfo structure which can be obtained by calling the @c ACAPI_Environment function with the @ref ACAPI_Teamwork_ProjectSharing function code.
 * 			The userId of the current Teamwork Client can be retrieved from the @ref API_ProjectInfo structure which can be obtained by calling the @c ACAPI_Environment function with the @ref ACAPI_ProjectOperation_Project function code.
 * 			This function performs complete operations, so it cannot be called neither during undoable operations nor during non-undoable commands. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Teamwork_ReserveHotlinkCacheManagement-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Teamwork_ReserveHotlinkCacheManagement (short* conflict = nullptr);


/**
 * @brief Releases the Hotlink/XRef Management in Teamwork mode.
 * @ingroup Teamwork
 * @return
 * 			- NoError - The function has completed with success.
 * 			- Error - The Hotlink/XRef Management is reserved by another team member.
 * 			- APIERR_NOPLAN - There is no open project.
 * 			- APIERR_NOTEAMWORKPROJECT - The current project is not a Teamwork project.
 * @remarks This function is used to release the Hotlink/XRef Management.
 * 			This function performs complete operations, so it cannot be called neither during undoable operations nor during non-undoable commands. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Teamwork_ReleaseHotlinkCacheManagement-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Teamwork_ReleaseHotlinkCacheManagement (void);


/**
 * @brief Provides the current owner of the Hotlink/XRef Management in Teamwork mode.
 * @ingroup Teamwork
 * @param owner [out] userId of the current owner if there is any (must not be nullptr).
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The given parameter is nullptr.
 * 			- APIERR_NOPLAN - There is no open project.
 * 			- APIERR_NOTEAMWORKPROJECT - The current project is not a Teamwork project.
 * @remarks Use this function to get the current owner of the Hotlink/XRef Management.
 * 			You can find out more about the owner from the @ref API_SharingInfo structure which can be obtained by calling the @c ACAPI_Environment function with the @ref ACAPI_Teamwork_ProjectSharing function code.
 * 			The userId of the current Teamwork Client can be retrieved from the @ref API_ProjectInfo structure which can be obtained by calling the @c ACAPI_Environment function with the @ref ACAPI_ProjectOperation_Project function code.
 * 			If the Hotlink/XRef Management is not reserved by anybody the result will be 0.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Teamwork_GetHotlinkCacheManagementOwner-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Teamwork_GetHotlinkCacheManagementOwner (short* owner);


/**
 * @brief Retrieves the username of a user identified by a short id in a Teamwork project.
 * @ingroup Teamwork
 * @since Archicad 25
 * @param userId [in] Unique identifier of the user
 * @param username [out] The name of the user
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOPLAN - There is no open project.
 * 			- APIERR_NOTEAMWORKPROJECT - The current project is not Teamwork project.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Teamwork_GetUsernameFromId-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Teamwork_GetUsernameFromId (short userId, GS::UniString* username);


/**
 * @brief Sends changes to the BIMcloud server.
 * @ingroup Teamwork
 * @since Archicad 25
 * @param comment [in] Comment attached to the Send operation.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOPLAN - There is no open project.
 * 			- APIERR_NOTEAMWORKPROJECT - The current project is not a Teamwork project.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Teamwork_SendChanges-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Teamwork_SendChanges (const GS::UniString&	comment = GS::EmptyUniString);


/**
 * @brief Receives changes from the BIMcloud server.
 * @ingroup Teamwork
 * @since Archicad 25
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOPLAN - There is no open project.
 * 			- APIERR_NOTEAMWORKPROJECT - The current project is not a Teamwork project.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Teamwork_ReceiveChanges-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Teamwork_ReceiveChanges ();

/* -- Properties -------------------- */


/**
 * @brief Retrieves all the property groups.
 * @ingroup Property
 * @param groups [out] The retrieved property groups.
 * @return
 * 			- NoError - The function has completed with success.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Property_GetPropertyGroups-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Property_GetPropertyGroups			(GS::Array<API_PropertyGroup>& groups);


/**
 * @brief Retrieves all the property definitions from a given group.
 * @ingroup Property
 * @param groupGuid [out] The identifier of the group to search for or APINULLGuid if all property definitions should be retrieved.
 * @param definitions [out] The retrieved property definitions.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The groupGuid parameter wasn't APINULLGuid and it did not refer to a valid property group.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Property_GetPropertyDefinitions-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Property_GetPropertyDefinitions		(const API_Guid& groupGuid, GS::Array<API_PropertyDefinition>&	definitions);


/**
 * @brief Retrieves one property group identified by its guid.
 * @ingroup Property
 * @param group [in/out] The guid field specifies the property group to retrieve. Once the operation completed successfully this will hold the retrieved property group.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The guid of the parameter did not refer to a valid property group.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Property_GetPropertyGroup-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Property_GetPropertyGroup			(API_PropertyGroup& group);


/**
 * @brief Retrieves one property definition identified by its guid.
 * @ingroup Property
 * @param definition [in/out] The guid field specifies the property definition to retrieve. Once the operation completed successfully this will hold the retrieved property definition.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The guid of the parameter did not refer to a valid property definition.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Property_GetPropertyDefinition-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Property_GetPropertyDefinition		(API_PropertyDefinition& definition);


/**
 * @brief Creates a property group in the current plan.
 * @ingroup Property
 * @param group [in/out] The property group to create. Once the operation completed successfully the guid field is overwritten with the id of the newly created property group.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The groupType of the parameter is not supported by the function.
 * 			- APIERR_NOACCESSRIGHT - Do not have the right to create a property group on a teamwork server.
 * 			- APIERR_NAMEALREADYUSED - The name of the group is already used.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Property_CreatePropertyGroup-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Property_CreatePropertyGroup			(API_PropertyGroup& group);


/**
 * @brief Creates a property definition in the current plan.
 * @ingroup Property
 * @param definition [in/out] The property definition to create. Once the operation completed successfully the guid field is overwritten with the id of the newly created property definition.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The groupGuid of the parameter did not refer to a valid property group or one of the availabilities' guid did not refer to a valid structural type category value.
 * 			- APIERR_NOACCESSRIGHT - Do not have the right to create a property definition on a teamwork server.
 * 			- APIERR_NAMEALREADYUSED - The name of the definition is already used in the given property group.
 * 			- APIERR_BADPARS - Either the value of the definition is inconsistent, for example the default value has a different value type than the definition itself, or the definitionType of the parameter is not supported by the function.
 * 			- APIERR_BADVALUE - One of enumerations did not have their value out of the allowed ones. This includes c++ enums (i.e. they were uninitialized or memsetted), and enumeration property values (the possibleEnumValues doesn't contain the default value)
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Property_CreatePropertyDefinition-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Property_CreatePropertyDefinition		(API_PropertyDefinition& definition);


/**
 * @brief Changes an already existing property group in the current plan (identified by its guid).
 * @ingroup Property
 * @param group [in] The property group to change.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The guid of the parameter did not refer to a valid property group.
 * 			- APIERR_BADPARS - The groupType of the parameter is not supported by the function.
 * 			- APIERR_NOACCESSRIGHT - Do not have the right to modify a property group on a teamwork server.
 * 			- APIERR_NAMEALREADYUSED - The new name of the group is already used.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Property_ChangePropertyGroup-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Property_ChangePropertyGroup			(const API_PropertyGroup& group);


/**
 * @brief Changes an already existing property definition in the current plan (identified by its guid).
 * @ingroup Property
 * @param definition [in] The property definition to change.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The guid of the parameter did not refer to a valid property definition or the groupGuid of the parameter did not refer to a valid property group or one of the availabilities' guid did not refer to a valid structural type category value.
 * 			- APIERR_NOACCESSRIGHT - Do not have the right to modify a property definition on a teamwork server.
 * 			- APIERR_NAMEALREADYUSED - The new name of the definition is already used in the target property group.
 * 			- APIERR_BADPARS - Either the new value of the definition is inconsistent, for example the default value has a different value type than the definition itself, or the definitionType of the definition is not supported by the function.
 * 			- APIERR_BADVALUE - One of enumerations did not have their value out of the allowed ones. This includes c++ enums (i.e. they were uninitialized or memsetted), and enumeration property values (the possibleEnumValues doesn't contain the default value)
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Property_ChangePropertyDefinition-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Property_ChangePropertyDefinition		(const API_PropertyDefinition& definition);


/**
 * @brief Returns true if the value is acceptable for the given property definition.
 * @ingroup Property
 * @since Archicad 25
 * @param value [in] The value to check.
 * @param definition [in] The valueType, collectionType and possibleEnumValues of the definition will be used to check the validity of the value.
 * @return
 * 			- true - The given value's variantStatus is @c API_VariantStatusNormal or @c API_VariantStatusUserUndefined and value's variant.type is the same as definition's valueType.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Property_IsValidValue-Example-Snippet
 */
__APIEXPORT bool ACAPI_Property_IsValidValue					(const API_PropertyValue& value, const API_PropertyDefinition& definition);


/**
 * @brief Deletes a property group and all of the property definitions inside in the current plan.
 * @ingroup Property
 * @param groupGuid [in] The identifier of the property group to delete.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The groupGuid parameter did not refer to a valid property group.
 * 			- APIERR_NOACCESSRIGHT - Do not have the right to delete a property group on a teamwork server.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Property_DeletePropertyGroup-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Property_DeletePropertyGroup			(const API_Guid& groupGuid);


/**
 * @brief Deletes a property definition in the current plan.
 * @ingroup Property
 * @param propertyGuid [in] The identifier of the property definition to delete.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The propertyGuid parameter did not refer to a valid property definition.
 * 			- APIERR_NOACCESSRIGHT - Do not have the right to delete a property definition on a teamwork server.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Property_DeletePropertyDefinition-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Property_DeletePropertyDefinition		(const API_Guid& propertyGuid);


/**
 * @brief Imports a property xml.
 * @ingroup Property
 * @param propertyXml [in] The property xml to import.
 * @param conflictPolicy [in] Specifies how to resolve name conflicts.
 * 						 |API_PropertyDefinitionNameConflictResolutionPolicy|Meaning|
 * 						 |--- |--- |
 * 						 |API_AppendConflictingProperties|Generate a new, unused name for the imported property|
 * 						 |API_ReplaceConflictingProperties|Replace the definition in the plan with the imported one|
 * 						 |API_SkipConflictingProperties|Keep the definition in the plan intact, and discard the imported one|
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Invalid property XML.
 */
__APIEXPORT GSErrCode ACAPI_Property_Import						(const GS::UniString&									propertyXml,
																							 API_PropertyDefinitionNameConflictResolutionPolicy		conflictPolicy);


/**
 * @brief Convert an API property value to display string.
 * @ingroup Property
 * @since Archicad 25
 * @param apiProperty [in] An evaluated property with its value.
 * @param resultString [out] The string representation of the given property value. The function can resolve enumeration values (which are stored by the keyVariant in the apiProperty), as well as convert measured numeric values based on the current Project Preferences.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Incorrect variant or param was specified.
 */
__APIEXPORT GSErrCode ACAPI_Property_GetPropertyValueString		(const API_Property&	apiProperty,
																							 GS::UniString*			resultString);


/**
 * @brief Sets the value of a property value from a passed string.
 * @ingroup Property
 * @since Archicad 25
 * @param propertyValueString [in] The string from which the new value will be generated.
 * @param conversionUtils [in] The implementation of @ref API_PropertyConversionUtilsInterface.
 * @param property [in/out] The property whose value we want to set.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The @ref API_Property is nullptr, the property definition does not exist or the value creation from the string failed.
 * 			- APIERR_BADVALUE - The property definition is invalid.
 * @remarks This function doesn't modify the database, only fills the @ref API_Property structure with the appropriate values. In order to introduce the new values to the database the add-on has to call @ref ACAPI_Element_SetProperty or @ref ACAPI_Element_SetProperties.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Property_SetPropertyValueFromString-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Property_SetPropertyValueFromString	(const GS::UniString&							propertyValueString,
																							 const API_PropertyConversionUtilsInterface&	conversionUtils,
																							 API_Property*									property);

/* -- Classifications -------------------- */


/**
 * @brief Retrieves all of the classification systems in the plan.
 * @ingroup Classification
 * @param systems [out] The retrieved classification systems.
 * @return
 * 			- NoError - The function has completed with success.
 */
__APIEXPORT GSErrCode ACAPI_Classification_GetClassificationSystems			(GS::Array<API_ClassificationSystem>& systems);


/**
 * @brief Retrieves a classification item identified by its guid.
 * @ingroup Classification
 * @param item [in/out] The item.guid is the identifier of the classification item to retrieve. Once the operation is completed successfully this will hold the retrieved classification item.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The item.guid did not refer to a valid classification item.
 */
__APIEXPORT GSErrCode	ACAPI_Classification_GetClassificationItem				(API_ClassificationItem& item);


/**
 * @brief Retrieves the parent of a classification item.
 * @ingroup Classification
 * @param itemGuid [in] The guid of the item whose parent should be retrieved.
 * @param parent [out] The retrieved parent classification item. Will be an empty classification item, with null guid, if the specified item doesn't have a parent.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The itemGuid did not refer to a valid classification item.
 */
__APIEXPORT GSErrCode ACAPI_Classification_GetClassificationItemParent		(const API_Guid& itemGuid, API_ClassificationItem& parent);


/**
 * @brief Retrieves the children of a classification item.
 * @ingroup Classification
 * @param itemGuid [in] The guid of the item whose children should be retrieved.
 * @param children [out] The retrieved children classification items.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The itemGuid did not refer to a valid classification item.
 */
__APIEXPORT GSErrCode ACAPI_Classification_GetClassificationItemChildren		(const API_Guid& itemGuid, GS::Array<API_ClassificationItem>& children);


/**
 * @brief Retrieves the system of a classification item.
 * @ingroup Classification
 * @param itemGuid [in] The guid of the item whose system should be retrieved.
 * @param system [out] The retrieved classification system.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The itemGuid did not refer to a valid classification item.
 */
__APIEXPORT GSErrCode ACAPI_Classification_GetClassificationItemSystem		(const API_Guid& itemGuid, API_ClassificationSystem& system);


/**
 * @brief Retrieves a classification system identified by its guid or by its name and edition version.
 * @ingroup Classification
 * @param system [in] The system.guid or the system.name and system.editionVersion together that identify the classification system to retrieve.
 * 				 [out] The retrieved classification system.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The system.guid is not null and did not refer to a valid classification system or the system.name and system.editionVersion together did not refer to a valid classification system.
 */
__APIEXPORT GSErrCode ACAPI_Classification_GetClassificationSystem			(API_ClassificationSystem& system);


/**
 * @brief Retrieves the root items of a classification system.
 * @ingroup Classification
 * @param systemGuid [in] The guid of the classification system whose root items should be retrieved.
 * @param items [out] The retrieved root classification items of the referenced system.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The systemGuid did not refer to a valid classification system.
 */
__APIEXPORT GSErrCode ACAPI_Classification_GetClassificationSystemRootItems	(const API_Guid& systemGuid, GS::Array<API_ClassificationItem>& items);


/**
 * @brief Creates a classification item.
 * @ingroup Classification
 * @param item [in/out] The details of the classification item to create. Once the operation is completed successfully this will hold the guid of the created classification item.
 * @param systemGuid [in] The guid of the classification system in which the item should be created.
 * @param parentItemGuid [in] The guid of the item that should be the parent of the newly created item (or null guid, if it should be a root item).
 * @param nextItemGuid [in] The guid of the item that should next in order to the created item (or null guid, if it created item should be the last).
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOACCESSRIGHT - Don't have the right to create a classification item in this plan.
 * 			- APIERR_BADID - One of the parameter guids did not refer to a valid object.
 * 			- APIERR_BADPARS - The given parent item is in a different system or the given next item is not on the same level as the item to be created.
 * 			- APIERR_BADNAME - The id field of the item is not a valid identifier for a classification item (i.e. empty string).
 * 			- APIERR_NAMEALREADYUSED - The id field of the item is already used as a classification item id within the given system.
 */
__APIEXPORT GSErrCode ACAPI_Classification_CreateClassificationItem			(API_ClassificationItem&	item,
																			 const API_Guid&			systemGuid,
																			 const API_Guid&			parentItemGuid,
																			 const API_Guid&			nextItemGuid);


/**
 * @brief Creates a classification system.
 * @ingroup Classification
 * @param system [in/out] The details of the classification system to create. Once the operation is completed successfully this will hold the guid of the created classification system.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOACCESSRIGHT - Don't have the right to create a classification system in this plan.
 * 			- APIERR_BADNAME - The name field of the system is not a valid name for a classification system (i.e. empty string).
 * 			- APIERR_NAMEALREADYUSED - The name field of the system is already used as a classification system name in the current plan with the same edition version.
 * 			- APIERR_BADPARS - The editionDate field of the system is not a valid date.
 */
__APIEXPORT GSErrCode ACAPI_Classification_CreateClassificationSystem			(API_ClassificationSystem& system);



/**
 * @brief Modifies a classification item.
 * @ingroup Classification
 * @param item [in] The details of the classification item.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOACCESSRIGHT - Don't have the right to modify a classification item in this plan.
 * 			- APIERR_BADID - The item.guid does not refer to a valid classification item.
 * 			- APIERR_READONLY - The referenced classification item can not be modified (i.e. comes from a hotlink).
 * 			- APIERR_BADNAME - The item.id is not a valid identifier for a classification item (i.e. empty string).
 * 			- APIERR_NAMEALREADYUSED - The item.id is different than the current id of the referenced item and the new id is already used as a classification item id in the item's system.
 */
__APIEXPORT GSErrCode ACAPI_Classification_ChangeClassificationItem			(const API_ClassificationItem& item);


/**
 * @brief Modifies a classification system.
 * @ingroup Classification
 * @param system [in] The details of the classification system.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOACCESSRIGHT - Don't have the right to modify a classification system in this plan.
 * 			- APIERR_BADID - The guid of the system parameter does not refer to a valid classification system.
 * 			- APIERR_READONLY - The referenced classification system can not be modified (i.e. comes from a hotlink).
 * 			- APIERR_BADNAME - The name field of the system is not a valid name for a classification system (i.e. empty string).
 * 			- APIERR_NAMEALREADYUSED - The name field of the system is different than the current name of the referenced classification system, but the new name is already used as a classification name in the current plan.
 * 			- APIERR_BADPARS - The editionDate field of the system is not a valid date.
 */
__APIEXPORT GSErrCode ACAPI_Classification_ChangeClassificationSystem			(const API_ClassificationSystem& system);


/**
 * @brief Deletes a classification item.
 * @ingroup Classification
 * @param itemGuid [in] The identifier of classification item to delete.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOACCESSRIGHT - Don't have the right to delete a classification item in this plan.
 * 			- APIERR_BADID - The guid of the item parameter does not refer to a valid classification.
 * 			- APIERR_READONLY - The referenced classification item can not be deleted (i.e. comes from a hotlink).
 */
__APIEXPORT GSErrCode ACAPI_Classification_DeleteClassificationItem			(const API_Guid& itemGuid);


/**
 * @brief Deletes a classification system.
 * @ingroup Classification
 * @param systemGuid [in] The identifier of classification system to delete.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOACCESSRIGHT - Don't have the right to delete a classification system in this plan.
 * 			- APIERR_BADID - The systemGuid parameter does not refer to a valid classification system.
 * 			- APIERR_READONLY - The referenced classification system can not be deleted (i.e. comes from a hotlink).
 */
__APIEXPORT GSErrCode ACAPI_Classification_DeleteClassificationSystem			(const API_Guid& systemGuid);


/**
 * @brief Imports a classification xml.
 * @ingroup Classification
 * @param classificationXml [in] The classification xml to import.
 * @param systemConflictPolicy [in] Specifies how to resolve classification system conflicts.
 * 							   |API_ClassificationSystemNameConflictResolutionPolicy|Meaning|
 * 							   |--- |--- |
 * 							   |API_MergeConflictingSystems|Merge the conflicting systems|
 * 							   |API_ReplaceConflictingSystems|Replace the system in the plan with the imported one|
 * 							   |API_SkipConflictingSystems|Keep the system in the plan intact, and discard the imported one|
 * @param itemConflictPolicy [in] Specifies how to resolve classification item conflicts.
 * 							 |API_ClassificationItemNameConflictResolutionPolicy|Meaning|
 * 							 |--- |--- |
 * 							 |API_ReplaceConflictingItems|Replace the item in the plan with the imported one|
 * 							 |API_SkipConflicitingItems|Keep the item in the plan intact, and discard the imported one|
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Invalid classification XML.
 */
__APIEXPORT GSErrCode ACAPI_Classification_Import								(const GS::UniString&									classificationXml,
																										 API_ClassificationSystemNameConflictResolutionPolicy	systemConflictPolicy,
																										 API_ClassificationItemNameConflictResolutionPolicy		itemConflictPolicy);


/* -- Action Center -------------------- */


/**
 * @brief Runs the selected checks of the Action Center.
 * @ingroup Window
 * @since Archicad 25
 * @param item [in] The checks that Action Center will preform.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOPLAN - There is no open project.
 * 			- APIERR_REFUSEDCMD - Refused to run check method because of opened modal dialog.
 * @remarks This function runs the checks of the Action Center. The Action Center tab will appear if an issue was found.
 */
__APIEXPORT GSErrCode ACAPI_Window_Check (API_ActionCenterItemID item);


/* -- IFC ------------------------------ */


/**
 * @brief It generates an IFC Relationship Data based on the input IFC Translator parameter.
 * @ingroup IFC
 * @since Archicad 26
 * @param ifcTranslatorIdentifier [in] Neccessery parameter for generate IFC Relationship Data.
 * @param ifcRelationshipData [out] The resulting IFC Relationship Data.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - If any error occured during the Relationship Data generation.
 * @remarks It generates an IFC Relationship Data based on the input parameters.
 */
__APIEXPORT GSErrCode ACAPI_IFC_GetIFCRelationshipData (const API_IFCTranslatorIdentifier& ifcTranslatorIdentifier, API_IFCRelationshipData& ifcRelationshipData);


/**
 * @brief Returns the valid IFC Export Translators.
 * @ingroup IFC
 * @since Archicad 26
 * @param ifcExportTranslators [out] The resulting IFC Export Translators.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - If any error occured during the conversion.
 * @remarks Returns the valid IFC Export Translators. The first item of the ifcExportTranslators is the preview translator.
 */
__APIEXPORT GSErrCode ACAPI_IFC_GetIFCExportTranslatorsList (GS::Array<API_IFCTranslatorIdentifier>& ifcExportTranslators);




/**
 * @brief It opens a dialog where a View and an IFC Export Translator can be selected.
 * @ingroup IFC
 * @since Archicad 26
 * @param viewGuid [in/out] A view Guid. Returns the selected view guid.
 * @param ifcTranslatorIdentifier [in/out] An IFC Export Translator. Returns the selected IFC Export Translator identifier.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- Cancel - The user cancelled the export settings dialog.
 * @remarks A dialog where the user can select a View and an IFC Export Translator.
 */
__APIEXPORT GSErrCode ACAPI_IFC_InvokeIFCExportSettingsDlg (API_Guid& viewGuid, API_IFCTranslatorIdentifier& ifcTranslatorIdentifier);


/* -- Protection ----------------------- */


/**
 * @brief Retrieves information about the protection mode.
 * @ingroup LicenseInfo
 * @since Archicad 26
 * @return
 * @remarks You can use the following predefined masks to retrieve information about the protection type.
 * 			- APIPROT_SITE_MASK: More license (full version)
 * 			- APIPROT_NFR_MASK: Not For Resale version (full version)
 * 			- APIPROT_SCHOOL_MASK: School version (full version)
 * 			- APIPROT_PPU_MASK:?PPU version (full version)
 * 			- APIPROT_NET_MASK: Network licensing
 * 			- APIPROT_TW_MASK: TeamWork functionality is on
 * 			- APIPROT_PROTEDU_MASK: Education version
 * 			- APIPROT_START_MASK : Start edition
 * 			Usable masks in case of no hardware or software key:
 * 			- APIPROT_EDU_MASK: Education version
 * 			- APIPROT_DEMO_MASK: Demo version
 * 			- APIPROT_TRIAL_MASK: Trial version
 * 			- APIPROT_BTC_MASK : BIM Cloud Team Client version
 * 			This information can be used to restrict the functionality of your Add-On for certain Archicad editions and license types (use the bitwise-AND operator to find out your license parameters).
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Licensing_GetProtectionMode-Example-Snippet
 */
__APIEXPORT UInt32 ACAPI_Licensing_GetProtectionMode ();


/**
 * @brief Retrieves the unique serial number of the current license.
 * @ingroup LicenseInfo
 * @since Archicad 26
 * @return
 * @remarks The serial number of hardware and software licenses can be queried with this function.
 */
__APIEXPORT UInt32 ACAPI_Licensing_GetSerialNumber ();


/**
 * @brief Retrieves the box mask of the current license.
 * @ingroup LicenseInfo
 * @since Archicad 26
 * @return
 * @remarks The box mask is applicable only in the case of hardware and software licenses.
 */
__APIEXPORT UInt16 ACAPI_Licensing_GetBoxMask ();


/**
 * @brief Retrieves the configuration number of the current license.
 * @remarks The configuration number is applicable only in the case of hardware and software licenses.
 * @ingroup LicenseInfo
 * @since Archicad 26
 * @return The current license's configuration number (also known as the container code).
 */
__APIEXPORT GS::UniString ACAPI_Licensing_GetConfigurationNumber ();


/**
 * @brief Retrieves the number of current licenses.
 * @ingroup LicenseInfo
 * @since Archicad 26
 * @return The number of licenses.
 */
__APIEXPORT UInt32 ACAPI_Licensing_GetNumberOfLicenses ();


/**
 * @brief Retrieves the expiration time of the current license (if any).
 * @ingroup LicenseInfo
 * @since Archicad 26
 * @return
 * 			- GSTime - The expiration time of the current license.
 */
__APIEXPORT GSTime ACAPI_Licensing_GetExpirationTime ();


/**
 * @brief When Archicad runs on an SSA license, this string contains the internal identifier of the reseller.
 * @ingroup LicenseInfo
 * @since Archicad 26
 * @return
 */
__APIEXPORT GS::UniString ACAPI_Licensing_GetPartnerId ();


/**
 * @brief Returns whether the SSA subscription passed in the parameter is available.
 * @ingroup LicenseInfo
 * @since Archicad 26
 * @param requiredLevel [in] The level to check the current level against.
 * @return
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Licensing_IsSSALevelAtLeast-Example-Snippet
 */
__APIEXPORT bool ACAPI_Licensing_IsSSALevelAtLeast (API_SSALevel requiredLevel);


/* -- ViewSettings ---------------------- */
/**
 * @brief Search a dimension preference by name or index
 * @ingroup Navigator
 * @since Archicad 27
 * @param dimStandHead [in/out] the dimension preferences to look up
 * @return
 * 			- NoError
 * 			- APIERR_BADINDEX
 * 			- APIERR_BADNAME
 */
__APIEXPORT GSErrCode	ACAPI_Navigator_DimStand_Search (API_DimensionStandards_Head* dimStandHead);


/**
 * @brief Get the number of dimension preferences
 * @ingroup Navigator
 * @since Archicad 27
 * @param count [out] the number of dimension preferences
 * @return
 * 			- NoError
 */
__APIEXPORT GSErrCode	ACAPI_Navigator_DimStand_GetNum (UInt32& count);


/**
 * @brief Get a dimension preference by index or name
 * @ingroup Navigator
 * @since Archicad 27
 * @param dimStand [out]
 * @return
 * 			- NoError
 * 			- APIERR_BADINDEX
 * 			- APIERR_BADNAME
 */
__APIEXPORT GSErrCode	ACAPI_Navigator_DimStand_Get (API_DimensionStandardsType&	dimStand);


/**
 * @brief Search an API_ModelViewOptions_Head by name or index
 * @ingroup Navigator
 * @since Archicad 27
 * @param mvoHead [in/out] the API_ModelViewOptions_Head to look up
 * @return
 * 			- NoError
 * 			- APIERR_BADINDEX
 * 			- APIERR_BADNAME
 */
__APIEXPORT GSErrCode	ACAPI_Navigator_ModelViewOptions_Search (API_ModelViewOptions_Head* mvoHead);


/**
 * @brief Get the number of API_ModelViewOptions
 * @ingroup Navigator
 * @since Archicad 27
 * @param count [out] the number of MVO-s
 * 				- NoError
 */
__APIEXPORT void		ACAPI_Navigator_ModelViewOptions_GetNum (UInt32& count);


/**
 * @brief Get an API_ModelViewOptionsType by index
 * @ingroup Navigator
 * @since Archicad 27
 * @param modelViewOpt [out]
 * @return
 * 			- NoError
 * 			- APIERR_BADINDEX
 */
__APIEXPORT GSErrCode	ACAPI_Navigator_ModelViewOptions_Get (API_ModelViewOptionsType* modelViewOpt);


/* --> ] */
#endif


// ---------------------------------------------------------------------------------------------------------------------

#if defined (_MSC_VER)
	#pragma pack(pop)
#endif

#endif
