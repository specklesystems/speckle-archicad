#ifndef ACAPI_INTERFACE_H
#define	ACAPI_INTERFACE_H

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


/**
 * @brief Returns the flag values of the specified menu item mounted by API tool add-on.
 * @ingroup MenuItem
 * @param menuItemRef [in] Identifies the menu item.
 * @param itemFlags [out] Menu item flags.
 * 					|Flag Value|Meaning|
 * 					|--- |--- |
 * 					|API_MenuItemDisabled|The menu item is currently disabled|
 * 					|API_MenuItemChecked|The menu item is currently checked|
 * @param menuItemText [out] Optional Unicode menu item text to get.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - any of the parameters are nullptr
 * 			- APIERR_BADINDEX - the specified menu item does not belong to the caller add-on
 * @remarks This function is used to get the current status of a menu item which belongs to the caller API
 * 			tool add-on. The menu item is referenced with the resource ID and the string number. To change the status of a
 * 			menu item use the @ref ACAPI_MenuItem_SetMenuItemFlags function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_MenuItem_GetMenuItemFlags-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_MenuItem_GetMenuItemFlags (const API_MenuItemRef* menuItemRef, GSFlags* itemFlags, GS::UniString* menuItemText = nullptr);


/**
 * @brief Sets the flag values of the specified menu item.
 * @ingroup MenuItem
 * @param menuItemRef [in] Identifies the menu item.
 * @param itemFlags [in] Menu item flags.
 * 					|Flag Value|Meaning|
 * 					|--- |--- |
 * 					|API_MenuItemDisabled|Disable the menu item|
 * 					|API_MenuItemChecked|Check the menu item|
 * @param menuItemText [in] Optional Unicode menu item text to set.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - any of the parameters are nullptr
 * 			- APIERR_BADINDEX - the specified menu item does not belong to the caller add-on
 * @remarks This function is used to set the current status of a menu item which belongs to the caller API
 * 			tool add-on. The menu item is referenced with the resource ID and the string number. To get the current status
 * 			of a menu item use the @ref ACAPI_MenuItem_GetMenuItemFlags function. Note that the initial status of a menu
 * 			item can also be set in the menu item string resources of the add-on. Refer to the STR# specification explained
 * 			in the Required Resources paper in details.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_MenuItem_SetMenuItemFlags-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_MenuItem_SetMenuItemFlags (const API_MenuItemRef* menuItemRef, GSFlags* itemFlags, GS::UniString* menuItemText = nullptr); // Int32?


/**
 * @brief Returns the text of the specified menu item.
 * @ingroup MenuItem
 * @param menuItemRef [in] Identifies the menu item.
 * @param itemText [out] Menu item text (if you don't pass itemUniText).
 * @param itemUniText [out] Optional Unicode menu item text to set.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - menuItemRef or both itemText and itemUniText are nullptr
 * 			- APIERR_BADINDEX - the specified menu item does not belong to the caller add-on
 * @remarks This function is used to get the text of a menu item which belongs to the caller API tool add-on. The menu item is referenced with the resource ID and the string number.
 * 			To change the text of a menu item use the @ref ACAPI_MenuItem_SetMenuItemText function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_MenuItem_GetMenuItemText-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_MenuItem_GetMenuItemText (const API_MenuItemRef* menuItemRef, char* itemText, GS::UniString* itemUniText = nullptr);


/**
 * @brief Sets the text of the specified menu item.
 * @ingroup MenuItem
 * @param menuItemRef [in] Identifies the menu item.
 * @param itemText [in] Menu item text to set (if you don't pass itemUniText).
 * @param itemUniText [in] Optional Unicode menu item text to set.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - menuItemRef or both itemText and itemUniText are nullptr
 * 			- APIERR_BADINDEX - the specified menu item does not belong to the caller add-on
 * @remarks This function is used to set the text of a menu item which belongs to the caller API tool add-on. The menu item is referenced with the resource ID and the string number.
 * 			To get the current text of a menu item use the @ref ACAPI_MenuItem_GetMenuItemText function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_MenuItem_SetMenuItemText-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_MenuItem_SetMenuItemText (const API_MenuItemRef* menuItemRef, char* itemText, GS::UniString* itemUniText = nullptr);


/**
 * @brief Sets the text of a specified menu item that will appear in the Work Environment dialog.
 * @ingroup MenuItem
 * @param menuItemRef [in] The referenced menu item.
 * @param weText [in] The text (if you don't pass weUniText) that will appear as the name of the menu item in the menu customization part of the work environment dialog.
 * @param weUniText [in] The Unicode text that will appear as the name of the menu item in the menu customization part of the work environment dialog.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - menuItemRef or both itemText and itemUniText are nullptr
 * @remarks We use this function mainly for palettes. In the Palettes menu the item is usually the title of the palette (e.g. "Element Information"), whereas in the Work Environment dialog it reads "Show/Hide Element Information".
 */
__APIEXPORT GSErrCode ACAPI_MenuItem_AddMenuItemText (const API_MenuItemRef* menuItemRef, char* weText, GS::UniString* weUniText = nullptr);


/**
 * @brief Returns the actual process control from Archicad.
 * @ingroup ProcessWindow
 * @param processControl [out]
 * @return
 * 			- NoError - The function has completed with success.
 */
__APIEXPORT GSErrCode ACAPI_ProcessWindow_GetProcessControl (GS::ProcessControl** processControl);


/**
 * @brief Sets the given process control to Archicad.
 * @ingroup ProcessWindow
 * @param processControl [in] Can be nullptr.
 * @return
 * 			- NoError - The function has completed with success.
 */
__APIEXPORT GSErrCode ACAPI_ProcessWindow_SetInnerProcessControl (GS::ProcessControl* processControl = nullptr);


/**
 * @brief Opens the process window.
 * @ingroup ProcessWindow
 * @param title [in] Process string.
 * @param nPhase [in] Number of phases.
 * @param processCntrolType [in]
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - nPhase is nullptr
 * @remarks This function is used to prepare the process window for a long operation. You can specify the name of the whole operation and the number of the phases of the process.
 * 			Other process window related functions are:
 * 			- @ref ACAPI_ProcessWindow_SetNextProcessPhase
 * 			- @ref ACAPI_ProcessWindow_SetProcessValue
 * 			- @ref ACAPI_ProcessWindow_IncProcessValue
 * 			- @ref ACAPI_ProcessWindow_IsProcessCanceled
 * 			- @ref ACAPI_ProcessWindow_CloseProcessWindow
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ProcessWindow_InitProcessWindow-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ProcessWindow_InitProcessWindow (const GS::UniString* title = nullptr, Int32* nPhase = nullptr, API_ProcessControlTypeID* processCntrolType = nullptr);


/**
 * @brief Closes the process window.
 * @ingroup ProcessWindow
 * @return
 * 			- NoError - The function always returns NoError.
 * @remarks This function is used to close the process window opened with @ref ACAPI_ProcessWindow_InitProcessWindow.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ProcessWindow_CloseProcessWindow-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ProcessWindow_CloseProcessWindow ();


/**
 * @brief Starts the next process phase in the process window.
 * @ingroup ProcessWindow
 * @param subtitle [in] Description of the process phase.
 * @param maxval [in] Maximum value of the progress bar.
 * @param showPercent [in] Show phase percentage. (optional)
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - maxval is nullptr
 * @remarks This function is used to reinitialize the process window for the next process phase during a long operation. Set some description about the process phase in the subtitle parameter. The progress bar will be divided up according to the value of the maxval parameter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ProcessWindow_SetNextProcessPhase-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ProcessWindow_SetNextProcessPhase (const GS::UniString* subtitle, Int32* maxval, bool* showPercent = nullptr);


/**
 * @brief Sets the value of the progress bar.
 * @ingroup ProcessWindow
 * @param newval [in] The new value of the progress bar in the current process phase.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - newval is nullptr
 * @remarks This function is used to set the progress bar value of the current phase in the process window.
 * 			Use the @ref ACAPI_ProcessWindow_IncProcessValue function to increment the process value, instead of setting it to a given value.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ProcessWindow_SetProcessValue-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ProcessWindow_SetProcessValue (Int32* newval);


/**
 * @brief Increases the value of the progress bar.
 * @ingroup ProcessWindow
 * @param incval [in] The value to add to the progress bar in the current process phase.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - incval is nullptr
 * @remarks This function is used to increase the progress bar value of the current phase in the process window. The increment should be passed in the incval parameter.
 * 			Use the @ref ACAPI_ProcessWindow_SetProcessValue function to set the process value to a given value, instead of increasing the current one.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ProcessWindow_IncProcessValue-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ProcessWindow_IncProcessValue (Int32* incval = nullptr);


/**
 * @brief Checks for user breaks during long processes.
 * @ingroup ProcessWindow
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_CANCEL - The current process was canceled
 * @remarks This function is used to check whether the user has canceled a long process (by clicking on the Cancel button of the process window, or by pressing the appropriate keys on the keyboard).
 * 			It also give visual feedback on processing by changing the cursor shape.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ProcessWindow_IsProcessCanceled-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ProcessWindow_IsProcessCanceled ();


/**
 * @brief Initializes the neig filter for an input.
 * @ingroup UserInput
 * @param neigFilter [in] The neig filter.
 * @param initNeigFilterID [in] Type of the filter initialization. The possible values:
 * 						   |Filter value|Meaning|
 * 						   |--- |--- |
 * 						   |APIInitNeigFilter_Full|Filter all neig types|
 * 						   |APIInitNeigFilter_Empty|Filter nothing|
 * 						   |APIInitNeigFilter_On|Filter line type neigs only|
 * 						   |APIInitNeigFilter_Node|Filter node type neigs only|
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - neigFilter is nullptr or `initNeigFilterID` is not a valid @ref API_InitNeigFilterID value
 * @remarks This function is used to initialize the neig filter for an input process. Use neig filtering if you want to control the default behavior of the cursor sensitivity above a certain set of neig types. During a filtered input the cursor gravity works only for those neig types that are set in the neig filter, all the other neigs will be ignored.
 * 			To change certain filters in the @ref API_NeigFilter structure use the the @ref ACAPI_UserInput_SetNeigFilter and @ref ACAPI_UserInput_ClearNeigFilter functions.
 * 			Note that the changeFilter field of the @ref API_NeigFilter structure must be set to true, in order to have the neig filter effect.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_UserInput_InitNeigFilter-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_UserInput_InitNeigFilter (API_NeigFilter* neigFilter, API_InitNeigFilterID initNeigFilterID);


/**
 * @brief Sets one of the neig types in the neig filter to be filtered.
 * @ingroup UserInput
 * @param neigFilter [in] The neig filter.
 * @param neigID [in] Neig type to set for filtering.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - neigFilter is nullptr
 * @remarks This function is used to set one of the neig types to be filtered during a user input. More information about neig filtering can be found at the remarks section of the @ref ACAPI_UserInput_InitNeigFilter function.
 * 			To clear an installed filter use the @ref ACAPI_UserInput_ClearNeigFilter function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_UserInput_SetNeigFilter-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_UserInput_SetNeigFilter (API_NeigFilter* neigFilter, API_NeigID neigID);


/**
 * @brief Sets one of the neig types in the neig filter not to be filtered.
 * @ingroup UserInput
 * @param neigFilter [in] The neig filter.
 * @param neigID [in] Neig type to clear out from filtering.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - neigFilter is nullptr
 * @remarks This function is used to set one of the neig types not to be filtered during a user input. More information about neig filtering can be found at the remarks section of the @ref ACAPI_UserInput_InitNeigFilter function.
 * 			To set a new filter use the @ref ACAPI_UserInput_SetNeigFilter function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_UserInput_ClearNeigFilter-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_UserInput_ClearNeigFilter (API_NeigFilter* neigFilter, API_NeigID neigID);


/**
 * @brief Performs a point input.
 * @ingroup UserInput
 * @param pointInfo [in/out] Parameters of the point input operation.
 * @param rubberLineInfoProc [in] Callback function for custom feedback drawing.
 * @param get3DComponentProc [in] Callback function for getting elem informations online (realtime).
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - pointInfo is nullptr
 * 			- APIERR_BADPLANE - invalid plane definition in pointInfo
 * 			- APIERR_BADWINDOW - the operation cannot be performed in the current front window of the application
 * 			- APIERR_CANCEL - the input was canceled by the user
 * @remarks This function is used to let the user input a point graphically.
 * 			If the input process has failed, the function returns APIERR_CANCEL. Otherwise the result is returned in the pos and neig fields of pointInfo.
 * 			The prompt string displayed in the control box which can contain instructions about the action. You can control the cursor gravity above neigs and the cursor shapes, and set the input plane. There is a possibility of drawing own graphical feedback during the input with passing a pointer to your rubber line callback function. For more details on the utilization refer to the documentation of the @ref API_GetPointType structure.
 * 			Do not invoke any input operation while there are modal dialogs open.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_UserInput_GetPoint-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_UserInput_GetPoint (API_GetPointType* pointInfo, RubberLineInfoProc* rubberLineInfoProc = nullptr, Get3DComponentProc* get3DComponentProc = nullptr);


/**
 * @brief Performs a line input.
 * @ingroup UserInput
 * @param lineInfo [in/out] Parameters of the line input operation.
 * @param rubberLineInfoProc [in] Callback function for custom feedback drawing.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - lineInfo is nullptr
 * 			- APIERR_BADPLANE - invalid plane definition in lineInfo
 * 			- APIERR_BADWINDOW - the operation cannot be performed in the current front window of the application
 * 			- APIERR_CANCEL - the input was canceled by the user
 * @remarks This function is used to let the user input a line graphically.
 * 			If the input process has failed, the function returns APIERR_CANCEL. Otherwise the result is returned in the pos and neig fields of lineInfo.
 * 			The start point of the line can be defined directly, or entered graphically with the @ref ACAPI_UserInput_GetPoint interface function.
 * 			The prompt string displayed in the control box which can contain instructions about the action. You can control the cursor gravity above neigs and the cursor shapes, and set the input plane. There is a possibility of drawing own graphical feedback during the input with passing a pointer to your rubber line callback function. For more details on the utilization refer to the documentation of the @ref API_GetLineType structure.
 * 			Do not invoke any input operation while there are modal dialogs open.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_UserInput_GetLine-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_UserInput_GetLine (API_GetLineType* lineInfo, RubberLineInfoProc* rubberLineInfoProc = nullptr);


/**
 * @brief Performs an arc input.
 * @ingroup UserInput
 * @param arcInfo [in/out] Parameters of the arc input operation.
 * @param rubberLineInfoProc [in] Callback function for custom feedback drawing.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - arcInfo is nullptr
 * 			- APIERR_BADPLANE - invalid plane definition in arcInfo
 * 			- APIERR_BADWINDOW - the operation cannot be performed in the current front window of the application
 * 			- APIERR_CANCEL - the input was canceled by the user
 * @remarks This function is used to let the user input an arc graphically.
 * 			If the input process has failed, the function returns APIERR_CANCEL. Otherwise the result is returned in the startCoord (if the start coordinate has not been given before the arc input), negArc, pos and neig fields of arcInfo.
 * 			The center point and the start point of the arc can be defined directly, or entered graphically with the @ref ACAPI_UserInput_GetPoint and @ref ACAPI_UserInput_GetLine interface functions.
 * 			The prompt string displayed in the control box which can contain instructions about the action. You can control the cursor gravity above neigs and the cursor shapes, and set the input plane. There is a possibility of drawing own graphical feedback during the input with passing a pointer to your rubber line callback function. For more details on the utilization refer to the documentation of the @ref API_GetArcType structure.
 * 			Do not invoke any input operation while there are modal dialogs open.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_UserInput_GetArc-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_UserInput_GetArc (API_GetArcType* arcInfo, RubberLineInfoProc* rubberLineInfoProc = nullptr);


/**
 * @brief Performs polygon input.
 * @ingroup UserInput
 * @param polyInfo [in/out] Parameters of the polygon input operation.
 * @param rubberPolyCallbacks [in] Callback functions for custom feedback drawing. Optional, can be nullptr.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - polyInfo is nullptr or one of the rubber callback function pointers in rubberProcs is nullptr
 * 			- APIERR_BADPLANE - Invalid plane definition in polyInfo
 * 			- APIERR_BADWINDOW - The operation cannot be performed in the current front window of the application
 * 			- APIERR_CANCEL - The input was canceled by the user
 * @remarks This function is used to let the user input a polygon graphically.
 * 			If the input process has failed, the function returns APIERR_CANCEL. Otherwise the result is returned in the coords, parcs, nCoords, nArcs and polylineWas fields of polyInfo. The returned polygon consists of at least 2 points. The polygon's coordinates start from index 1, and the polygon is closed if polyInfo->polylineWas is false, meaning that the last point is equal to the first. Do not forget to dispose the coords and parcs handle with BMKillHandle.
 * 			If changePlane has not been set for the input, the z coordinates of the polygon nodes can be also retrieved in the zCoords handle by passing true in the getZCoords member of @ref API_GetPolyType. In this case the add-on should dispose this handle when it is not needed any more.
 * 			The start point of the polyline can be defined directly, or entered graphically with the @ref ACAPI_UserInput_GetPoint interface function.
 * 			The prompt string displayed in the control box can contain instructions about the action. You can control the cursor shapes, set the input plane and the specify the polygon input method. From API v3.1 it is possible to draw your own graphical feedback during the input, as it is provided in the @ref ACAPI_UserInput_GetPoint, @ref ACAPI_UserInput_GetLine, @ref ACAPI_UserInput_GetArc functions. For more details on the utilization refer to the documentation of the @ref API_GetPolyType structure.
 * 			Do not invoke any input operation while there are modal dialogs open.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_UserInput_GetPoly-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_UserInput_GetPoly (API_GetPolyType* polyInfo, API_RubberPolyCallbacks* rubberPolyCallbacks = nullptr);


/**
 * @brief Draws graphical feedback during an input process.
 * @ingroup UserInput
 * @param rubberLine [in] Definition of the line to be drawn.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_GENERAL - no rubber line callback function has been defined
 * @remarks This function is used to draw rubber lines while a user input. The function can be called only from the RubberLineInfoProc passed to the given input function; @ref ACAPI_UserInput_GetPoint or @ref ACAPI_UserInput_GetLine or @ref ACAPI_UserInput_GetArc or @ref ACAPI_UserInput_GetPoly.
 * 			The line is defined with the two endpoint coordinates.
 * 			Note that during an input in the 3D model window the z coordinate can also be used to draw the feedback.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_UserInput_DrawRubberLine-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_UserInput_DrawRubberLine (API_RubberLineType* rubberLine);


/**
 * @brief Draws graphical feedback during an input process.
 * @ingroup UserInput
 * @param rubberArc [in] Definition of the arc (circle or elliptic) to be drawn.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_GENERAL - no rubber line callback function has been defined
 * 			- APIERR_BADPARS - rubberArc->arcType is neither @c APIRubberArc_OrigoAngles nor @c APIRubberArc_ThreePoint
 * @remarks This function is used to draw rubber arcs while a user input. The function can be called only from the RubberLineInfoProc passed to the given input function; @ref ACAPI_UserInput_GetPoint or @ref ACAPI_UserInput_GetLine or @ref ACAPI_UserInput_GetArc or @ref ACAPI_UserInput_GetPoly.
 * 			The arc is defined with the coordinate of the center point, the radius (or 'a' if ellipse), the beginning angle of the arc and the ending angle of the arc or with the coordinate of the center point, the beginning point of the arc, the ending point of the arc and the sign of the arc's angle (see @ref API_RubberArcType).
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_UserInput_DrawRubberArc-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_UserInput_DrawRubberArc (API_RubberArcType* rubberArc);


/**
 * @brief Opens a pet palette for performing user input from the add-on.
 * @ingroup Dialog
 * @param petPaletteInfo [in] identifies the pet palette.
 * @param petPaletteProc [in] callback procedure for the palette.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - One or both of the parameters are nullptr.
 * 			- APIERR_NESTING - Pet palettes cannot be opened when the input has already begun.
 * 			- APIERR_BADWINDOW - Pet palettes can be opened only above drawing windows.
 * 			- APIERR_BADID - One of the following errors occured: The petIconIDsHdl is nullptr. The petIconIDsHdl contain more or less IDs, thanindicated by nCols * nRows. The supplied petPaletteID collides with abuilt-in Archicad petpalette identifier. Choosing the old pictID for identifier is a good idea. The supplied petPaletteIDcollides withanother petpalette, which differs from the actual one: it hasmore or less items, or it has the same number of items, butat least one of them has different icon resource identifier. The Add-On is using the old @ref API_PetPaletteType structure. For other common API errors see the API Errors document.
 * @remarks The pet palette consists of individual 'GICN' icon resources (pet items). Each pet item in the palette assumed to be 22 pixels wide and 22 pixels high. Larger icons will appear truncated. The iconIDs should be passed to the Archicad in a GSHandle consisting of short numbers. The Archicad builds up the palette from these icons. Besides this, each different pet palette should have a unique identifier. Choosing the old pictID for identifier is a good idea.
 * 			The pet palette can have tooltip (yellow bar) strings and help anchors (the help mechanism is loaded with it). The strings should be placed as pairs into a 'DHLP' resource. In the 'DHLP' resource, every tooltip and help anchor pair belongs to the corresponding pet item on the palette. This resource should be compiled into the API resource module, and their identifier can be passed to the @ref API_PetPaletteType structure.
 * 			The API will search for only this resource, and will index this with the pet palette item's relative index to get the help object and take an action: it will display the tooltip string, or will pass the anchor as a parameter to the help engine configured by the add-on. If the add-on wants to take these opportunities, then it should set the Location of its own help engine by the DGRegisterAdditionalHelpLocation function of the Dialog Manager module. This can be done during the Initialize phase, and you should unregister the help location by calling DGUnregisterAdditionalHelpLocation during the FreeData phase. The developerId and localId is the MDID stored in your 32500 'MDID' resource.
 * 			The palette callback procedure is called with the actual value of the pet palette (see APIPetPaletteCallBackProc).
 */
__APIEXPORT GSErrCode ACAPI_Dialog_PetPalette (API_PetPaletteType* petPaletteInfo, APIPetPaletteCallBackProc* petPaletteProc);


/**
 * @brief Finishes the user input.
 * @ingroup UserInput
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks It works as if the user clicked the OK button on the control box during input.
 */
__APIEXPORT GSErrCode ACAPI_UserInput_CompleteUserInput ();


/**
 * @brief Cancels the user input.
 * @ingroup UserInput
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks It works as if the user clicked the Cancel button on the control box during input.
 */
__APIEXPORT GSErrCode ACAPI_UserInput_CancelUserInput ();


/**
 * @brief Helper function to set the proper attribute callback for a user control.
 * @ingroup Dialog
 * @param callbackType [in] identifies the control to set the callback for.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - callbackType is nullptr, or the supplied dialogID is invalid.
 * 			- APIERR_BADID - the given dialog is closed, or the supplied callback type is invalid.
 * @remarks This function provides an easy way for your user control items to use the default attribute set in the server application. By settings this callback, you don't have to write your own.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Dialog_SetUserControlCallback-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Dialog_SetUserControlCallback (API_UCCallbackType* callbackType);


/**
 * @brief Opens the Object/Lamp(/Window/Door) Settings dialog.
 * @ingroup Dialog
 * @param objectSettingsPars [in/out] The parameters to open the dialog with. Also contains the selected object on return.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - objectSettingsPars is nullptr.
 * 			- APIERR_BADID - objectSettingsPars contains invalid data.
 * @remarks The Settings dialog may show only library parts with a given subtype. The default library part's library index can also be passed onto this function.
 * 			It returns the parameters set in the Settings dialog, and also the additional parameters of the selected library part.
 * 			If subtypeID is an empty string, then the passed typeID and variationID will be used to identify the tool whose subtype will serve as a filter.
 * 			If libIndex is 0 (i.e. you haven't used @ref ACAPI_LibraryPart_Search to find an appropriate library item), then the function tried to find the first item in the loaded libraries, whose subtype matches the passed subTypeID (or typeID and variationID).
 * 			The linked properties information specified on the Listing and Labeling page returns in the propIndivLibInd and propCriteria fields. These properties should be linked to the element you would create after calling the Object Settings dialog (see @ref ACAPI_ElementLink_SetLinkedPropertyObjects).
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Dialog_ObjectSettings-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Dialog_ObjectSettings (API_ObjectSettingsPars* objectSettingsPars);


/**
 * @brief Opens a tool settings dialog.
 * @ingroup Dialog
 * @param toolBoxItem [in] The parameters to open the dialog with.
 * @param guid [in] Special unique identifier of the dialog, used in automated testing.
 * @param indexOfSubTool [in] Index of sub tool to open the dialog at. If the dialog belongs to a hierarchical tool, this parameter can help to open the dialog with the desired sub tool in
 * 						 focus. Indexing starts from 0, which belongs to the first sub tool on the UI. If you do not want to customize this behavior, leave it empty.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - toolBoxItem->type is invalid.
 * 			- APIERR_CANCEL - CANCEL was hit.
 * @remarks The Settings dialog is identified with toolBoxItem->type.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Dialog_SettingsDialog-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Dialog_SettingsDialog (API_ToolBoxItem* toolBoxItem, const API_Guid* guid = nullptr, const UShort* indexOfSubTool = nullptr);


/**
 * @brief Opens the settings dialog of the current tool or current selection.
 * @ingroup Dialog
 * @param dialogTestID [in] Special unique identifier of the dialog, used in automated testing.
 * @param indexOfSubTool [in] Index of sub tool to open the dialog at. If the dialog belongs to a hierarchical tool, this parameter can help to open the dialog with the desired sub tool in
 * 						 focus. Indexing starts from 0, which belongs to the first sub tool on the UI. If you do not want to customize this behavior, leave it empty.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_CANCEL - CANCEL was hit.
 * @remarks Opens the Settings Dialog for the last selected element. If no element is selected, the Settings Dialog of the current tool will be opened.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Dialog_SettingsDialog-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Dialog_SettingsDialog (const API_Guid* dialogTestID = nullptr, const UShort* indexOfSubTool = nullptr);


/**
 * @brief Set the drawing constraint for graphical user input.
 * @ingroup UserInput
 * @param constraintPars [in] Parameters of the drawing constraint.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - constraintPars is nullptr
 * 			- APIERR_BADID - Invalid type of drawing constraint in constraintPars
 * @remarks This function is used to set drawing constraint before the user input.
 * 			It could be called just before @ref ACAPI_UserInput_GetPoint, @ref ACAPI_UserInput_GetLine, @ref ACAPI_UserInput_GetArc, @ref ACAPI_UserInput_GetPoly or in the addPolyNodeProc, delPolyNodeProc callback functions. After finishing the input do not forget to call @ref ACAPI_UserInput_ResetConstraint function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_UserInput_SetConstraint-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_UserInput_SetConstraint (API_ConstraintPars* constraintPars);


/**
 * @brief Dissolve the drawing constraint.
 * @ingroup UserInput
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function is used to dissolve drawing constraint. Do not forget to call it after @ref ACAPI_UserInput_SetConstraint.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_UserInput_ResetConstraint-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_UserInput_ResetConstraint ();


/**
 * @brief Opens the Save Library Part dialog and returns the selected location.
 * @ingroup Dialog
 * @param retCode [out] returns whether the dialog was closed with confirmation (OK, Save, etc.)
 * @param location [in/out] sets the default library and filename to open the dialog with, and returns the location of the chosen file
 * @param browseForFolder [in] enables the dialog to save Library Parts outside the Embedded Library (optional; the default value is false)
 * @param dialogTitle [in] defines the title of the dialog (optional)
 * @param dialogTypeStr [in] defines the library part type of the dialog (optional); applicable identifiers are: "ExportObjectDialog" (default), "ExportDoorDialog", "ExportWindowDialog"
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - retCode or location is nullptr.
 * @remarks Use this function to let the user choose a file location for saving a library part in the loaded libraries.
 * 			The function needs a valid location to open the dialog from.
 * 			The location is set only if the dialog was closed with confirmation button (OK, Save, etc.).
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Dialog_SaveLibPartFileDialog-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Dialog_SaveLibPartFileDialog (bool* retCode, IO::Location* location, bool* browseForFolder = nullptr, GS::UniString* dialogTitle = nullptr, GS::UniString* dialogTypeStr = nullptr);


/**
 * @brief Invokes the "Open Library Part" dialog.
 * @ingroup Dialog
 * @since Archicad 26
 * @param retCode Return code is true when a valid gsm file is successfully opened in the "Open Library Part" dialog.
 * @param location Location of the selected library part.
 * @param isGSM [in] Optional parameter. If it is set to true, the file filter in the open dialog is set to "General GDL Objects".
 * @param wasExternalEditorInvoked [out] Optional parameter. If it is set to true, the file was opened using an external editor.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function invokes the "Open Library Part" dialog, and returns the chosen library part's location.
 */
__APIEXPORT GSErrCode ACAPI_Dialog_OpenLibPartFileDialog (bool* retCode, IO::Location* location, bool* isGSM, bool* wasExternalEditorInvoked);


/**
 * @brief Opens an "Open Picture" dialog (same dialog as on Material Settings, Texture tabpage).
 * @ingroup Dialog
 * @since Archicad 26
 * @param retCode [out] True if a valid picture format file is selected in the "Open Picture" dialog.
 * @param location [out] The location of the selected Picture format file.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks Invokes the Open Picture (Load Image from Library) dialog, and returns the chosen picture's location. Also adds the chosen picture to the Embedded Library if it was not part of that previously.
 */
__APIEXPORT GSErrCode ACAPI_Dialog_OpenPictureDialog (bool* retCode, IO::Location* location);


/**
 * @brief Invokes the "Open Library" dialog.
 * @ingroup Dialog
 * @since Archicad 26
 * @param retCode [out] Return code. True if the zone stamp or label object file selected in the file open dialog was opened successfully.
 * @param location The location of the library part.
 * @param isRoom [in] Optional parameter. Defines the type of the file in the file open dialog (true - the file type is Zone, nullptr or false - the file type is Label)
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function is used to let the user open a file of type Zone Stamp or Label, using the Open File Dialog. The location is set only if a valid Zone Stamp or Label file was selected in the "Open File" dialog.
 */
__APIEXPORT GSErrCode ACAPI_Dialog_OpenOtherObjectDialog (bool* retCode, IO::Location* location, bool* isRoom);


/**
 * @brief Turns the process window on/off.
 * @ingroup ProcessWindow
 * @param switchOff [in] sets the current state.
 * @return
 * 			- NoError - The function has completed with success.
 */
__APIEXPORT GSErrCode ACAPI_ProcessWindow_SetProcessOnOffSwitch (bool* switchOff);


/**
 * @brief Returns whether the process window will appear.
 * @ingroup ProcessWindow
 * @param param [out] returns the current state.
 * @return
 * 			- NoError - The function has completed with success.
 */
__APIEXPORT GSErrCode ACAPI_ProcessWindow_GetProcessOnOffSwitch (bool* param);


/**
 * @brief Retrieves the last valid embedded library location.
 * @ingroup LibraryPart
 * @param name [in] Library part name.
 * @param location [out] The location of the last valid embedded libpart for the given libpart name.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This fuction is used to retrieve the last valid embedded library part location identified by its name.
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_GetLastValidEmbeddedLPName (GS::UniString* name, IO::Location* location);

/**
 * @brief Activates the 3D window and shows the selected elements.
 * @ingroup View
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADWINDOW - The command cannot be executed on the topmost window.
 * @remarks Activates the 3D window and shows the selected elements.
 * 			To switch to the 3D window showing the all the elements, use the @ref ACAPI_View_ShowAllIn3D function.
 */
__APIEXPORT GSErrCode ACAPI_View_ShowSelectionIn3D ();

/**
 * @brief Activates the 3D window and shows the whole model.
 * @ingroup View
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADWINDOW - The command cannot be executed on the topmost window.
 * @remarks Activates the 3D window and shows the whole model.
 * 			To switch to the 3D window showing the selected elements only, use the @ref ACAPI_View_ShowSelectionIn3D function.
 */
__APIEXPORT GSErrCode ACAPI_View_ShowAllIn3D ();

/**
 * Change to Hierarchical Elem (Curtain Wall, Stair, Railing, Beam, Column) editing mode.
 * @ingroup HierarchicalEditing
 * @param guid [in] guid of the hierarchical elem (curtain wall, stair, railing, beam, column) to be open for editing in 3D.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_REFUSEDCMD - It is already in hierarchical editing mode.
 * 			- APIERR_BADPARS - guid is not a valid curtain wall, stair, railing, beam or column guid.
 * @remarks Switch to 3D editing mode of a hierarchical elem (curtain wall, stair, railing, beam, column).
 * 			This function performs complete operations, so it cannot be called neither during undoable operations nor during non-undoable commands. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_HierarchicalEditing_EditHierarchicalElem (const API_Guid* guid);

/**
 * @brief Cancel changes in Hierarchical Elem (Curtain Wall, Stair, Railing, Beam, Column) editing mode.
 * @ingroup HierarchicalEditing
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_REFUSEDCMD - Archicad is not in Curtain Wall, Stair, Railing, Beam or Column editing mode.
 * @remarks ou are able to cancel changes made in Curtain Walls, Stairs, Railings, Beams and Columns 3D editing mode via this function.
 * 			This function performs complete operations, so it cannot be called neither during undoable operations nor during non-undoable commands. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_HierarchicalEditing_CancelHierarchicalElem ();

/**
 * @brief Accept changes in Hierarchical Elem (Curtain Wall, Stair, Railing, Beam, Column) editing mode.
 * @ingroup HierarchicalEditing
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_REFUSEDCMD - Archicad is not in Curtain Wall, Stair, Railing, Beam or Column editing mode.
 * @remarks You are able to accept changes made in Curtain Walls, Stairs, Railings, Beams or Columns 3D editing mode via this function.
 * 			This function performs complete operations, so it cannot be called neither during undoable operations nor during non-undoable commands. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_HierarchicalEditing_OkHierarchicalElem ();


/**
 * @brief Highlight elements in the 2D (floor plan and section) and 3D window.
 * @ingroup UserInput
 * @since Archicad 26
 * @param highlightedElems Hash table containing the elements (identified by their GUIDs) and the colors to highlight the element with.
 * @param wireframe3D Switch other elements in the 3D window to wireframe (does not have effect in case of using Vectorial Engine). Optional, it can be GS::NoValue.
 * @param nonHighlightedElemsColor It contains the color and the transparency of the non highlighted elements. Optional, it can be GS::NoValue.
 * @remarks You can remove element highlight by calling @ref ACAPI_UserInput_ClearElementHighlight.
 * 			After changing element highlights the model needs to be redrawn by calling @c ACAPI_Automate (@ref ACAPI_View_Redraw).
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_UserInput_SetElementHighlight-Example-Snippet
 */
__APIEXPORT void ACAPI_UserInput_SetElementHighlight (const GS::HashTable<API_Guid, API_RGBAColor>& highlightedElems, const GS::Optional<bool>& wireframe3D = GS::NoValue, const GS::Optional<API_RGBAColor>& nonHighlightedElemsColor = GS::NoValue);


/**
 * @brief Removes element highlights from 2D (floor plan and section) and 3D window.
 * @ingroup View
 * @since Archicad 26
 * @remarks This function removes element highlights set by @ref ACAPI_UserInput_SetElementHighlight.
 * 			After changing element highlights the model needs to be redrawn by calling @c ACAPI_Automate (@ref ACAPI_View_Redraw).
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_UserInput_ClearElementHighlight-Example-Snippet
 */
__APIEXPORT void ACAPI_UserInput_ClearElementHighlight ();


/**
 * @brief Invoke generic SSA Forward dialog that warn that the user don't have SSA license.
 * @ingroup LicenseInfo
 * @since Archicad 26
 */
__APIEXPORT void ACAPI_Licensing_InvokeForwardDialog	();

#endif // ACAPI_INTERFACE_H
