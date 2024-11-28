#ifndef ACAPI_DATABASE_H
#define	ACAPI_DATABASE_H

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
 * @brief Returns the identifier of the current (active) window.
 * @ingroup Window
 * @ingroup Database
 * @param windowInfo [out] The identification parameters of the front window
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - windowInfo is nullptr.
 * 			- APIERR_BADWINDOW - the type of the current front window is not known by the API
 * @remarks This function is used to return the parameters of the front window of the server application. It can be used to identify which window your command was called on.
 * 			Generally the current window and the window of the current database are the same. However you must be careful; the database dependent functions work on the current database not on the database of the current window. The interface functions work on the current window always.
 * 			Note that this function fills out only the fields which are needed to identify the window type and the database behind the window. In order to retrieve the additional parameters of the database (title, name, ref, masterLayoutUnId) call the @ref ACAPI_Window_GetDatabaseInfo function with the databaseUnId of the current window.
 * 			Use the @ref ACAPI_Window_ChangeWindow function to change the current window.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Window_GetCurrentWindow-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Window_GetCurrentWindow (API_WindowInfo* windowInfo);


/**
 * @brief Deletes the database elements of the current window and sets up a new, empty environment.
 * @ingroup Window
 * @ingroup Database
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADWINDOW - The current database is not a custom drawing or owned by an other addon.
 * @remarks This function is used to delete all elements from the current window. It returns an error if the active window is not a custom window owned by the caller addon.
 * 			You can use the @ref ACAPI_Window_ResetCurrentDatabase function to reset the content of any window being in the background.
 */
__APIEXPORT GSErrCode ACAPI_Window_ResetCurrentWindow ();


/**
 * @brief Opens a new window.
 * @ingroup Window
 * @ingroup Database
 * @param newWindowPars [in] parameters of the window to be created (type and reference index)
 * @param handlerProc [in] Callback function to handle special (e.g. activate) events. Specify nullptr if you are not interested in these events.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - windowPars is nullptr.
 * 			- APIERR_REFUSEDCMD - the function is called from notification level.
 * 			- APIERR_REFUSEDPAR - not @c APIWind_MyTextID or @c APIWind_MyDrawID is requested.
 * 			- APIERR_WINDEXIST - a window with the same type and reference index already opened.
 * 			- APIERR_NOPLAN - no open project
 * @remarks This function is used to open a new window.
 * 			It is limited to opening simple text or drawing windows. The drawing window will have limited functionality and database beyond, compared to a normal 2D model window. It can have real 2D elements only (lines, arcs, etc.), construction elements like walls or beams cannot appear in this database. The database cannot be modified by the user, the input and edit functionality on these windows are disabled for the user.
 * 			These type of windows are excellent to visualize the output of your algorithms, for example in case of listings. An add-on can open any number of drawing and text windows at the same time.
 * 			Once an add-on opens such a window, it will be responsible for rebuilding its content when it is necessary. Archicad will post notifications for such an event. Upon receiving a notification Archicad will pass the windowPars->userRefCon parameter to the add-on to identify which window it should work on. Refer to the Notification Manager to get further details.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Window_NewWindow-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Window_NewWindow (API_NewWindowPars* newWindowPars, APICustomWindowHandlerProc* handlerProc = nullptr);


/**
 * @brief Closes a window.
 * @ingroup Window
 * @ingroup Database
 * @param windowInfo parameters of the window to be closed (type and reference index)
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - windowPars is nullptr.
 * 			- APIERR_REFUSEDCMD - the function is called from notification level.
 * 			- APIERR_REFUSEDPAR - not @c APIWind_MyTextID or @c APIWind_MyDrawID is requested.
 * 			- APIERR_WINDNOTEXIST - a window with the same type and reference index is not opened.
 * 			- APIERR_NOPLAN - no open project
 * @remarks This function is used to close a previously opened custom window.
 * 			It is the inverse function of @ref ACAPI_Window_NewWindow, so it is limited to close simple text or drawing windows. Such a window can be closed from the same addon, which it was opened from.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Window_CloseWindow-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Window_CloseWindow (API_WindowInfo* windowInfo);


/**
 * @brief Returns the ids of the opened windows in an array.
 * @ingroup Window
 * @ingroup Database
 * @param windowTypeID [in] TypeID of the opened windows.
 * @param guid [out] An array of guids of the opened windows.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOPLAN - There is no open project. The operation cannot be executed without an open project.
 * 			- APIERR_BADPARS - Incorrect windowTypeID or guid was specified.
 */
__APIEXPORT GSErrCode ACAPI_Window_GetOwnWindows (API_WindowTypeID* windowTypeID, GS::Array<API_Guid>* guid = nullptr);


/**
 * @brief Returns the identifier of the current (active) database.
 * @ingroup Database
 * @param databaseInfo [out] The identification parameters of the current database
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - databaseInfo is nullptr
 * 			- APIERR_BADWINDOW - the type of the current database is not known by the API
 * @remarks This function is used to return the parameters of the current database of the server application. It can be used to identify which database the subsequent API calls will work on.
 * 			Generally the current window and the window of the current database are the same. However you must be careful; the database dependent functions work on the current database not on the database of the current window. You can change the current database by calling the @ref ACAPI_Database_ChangeCurrentDatabase function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Database_GetCurrentDatabase-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Database_GetCurrentDatabase (API_DatabaseInfo* databaseInfo);


/**
 * @brief Deletes the database elements of the current window and sets up a new, empty environment.
 * @ingroup Database
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE - The current database is not a custom drawing or owned by an other addon,
 * @remarks This function is used to delete all elements from the current database. It returns an error if the active database is not a custom window owned by the caller addon.
 * 			To reset the content of the current (front) window use the @ref ACAPI_Window_ResetCurrentWindow function.
 */
__APIEXPORT GSErrCode ACAPI_Window_ResetCurrentDatabase ();


/**
 * @brief Changes the current (active) database.
 * @ingroup Database
 * @since Archicad 25
 * @param databaseInfo [in] parameters of the database to be created (type, reference index)
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - databasePars is nullptr
 * 			- APIERR_NOPLAN - no open project
 * 			- APIERR_BADDATABASE - the requested database does not exist
 * @remarks This function is used to change the current database in the background. All the subsequent API calls to any database dependent function will work on the specified database.
 * 			This function can be very expensive in case of low memory condition. The server application tries to keep as many database object in the memory as possibly, however it can happen, that some of them must be swapped out. Switching to an other database means, that the server application loads it into the memory, which may cause others to be unloaded. It can be a relatively long time.
 * 			Refer to the @ref ACAPI_Window_ChangeWindow function in the case you want to change not only the database in the background, but the current front window also.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Database_ChangeCurrentDatabase-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Database_ChangeCurrentDatabase (API_DatabaseInfo* databaseInfo);


/**
 * @brief Redraws the current database, even it's associated window is in the background.
 * @ingroup Database
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOPLAN - No open project.
 * @remarks This function is used to redraw the current database in the background. Only the visible region of the associated window will be updated from the update picture.
 */
__APIEXPORT GSErrCode ACAPI_Database_RedrawCurrentDatabase ();


/**
 * @brief Rebuilds the current database, even it's associated window is in the background.
 * @ingroup Database
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOPLAN - No open project.
 * @remarks This function is used to rebuild the current database in the background. Only the visible region of the associated window will be updated.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_Database_RebuildCurrentDatabase ();


/**
 * @brief Creates a new independent detail, worksheet, layout or master layout database.
 * @ingroup Database
 * @param databaseInfo [in/out] parameters of the database to be created
 * @param parent The parent of the new item.
 * @param child If it is nullptr, then the new item will be inserted to the first place on the actual level, otherwise the it will be inserted after the child.
 * @return
 * 			- NoError - the function has completed with success.
 * 			- APIERR_REFUSEDCMD - the function was refused to execute, because it was called inside an undo scope.
 * 			- APIERR_NOPLAN - no floor plan window opened
 * 			- APIERR_BADPARS - databaseInfo is nullptr
 * 			- APIERR_REFUSEDPAR - the passed typeID is not @c APIWind_DetailID, @c APIWind_WorksheetID, @c APIWind_LayoutID or @c APIWind_MasterLayoutID
 * 			- APIERR_GENERAL - could not create new database
 * @remarks This function is used to create a new database with the given name and ref parameters. No associated window will be opened.
 * 			In case of Layout databases you must specify an existing Master Layout in masterLayoutUnId.
 * 			If the database is created successfully, the unique ID of the database returns in the databaseUnId field.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Database_NewDatabase-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Database_NewDatabase (API_DatabaseInfo* databaseInfo, const API_Guid* parent = nullptr, const API_Guid* child = nullptr);


/**
 * @brief Modifies the parameters of an independent detail, worksheet, layout or master layout database.
 * @ingroup Database
 * @param databaseInfo [in/out] parameters of the database to be created
 * @return
 * 			- NoError - the function has completed with success.
 * 			- APIERR_NOPLAN - no floor plan window opened
 * 			- APIERR_BADPARS - databaseInfo is nullptr
 * 			- APIERR_REFUSEDPAR - the passed typeID is not @c APIWind_DetailID, @c APIWind_WorksheetID, @c APIWind_LayoutID or @c APIWind_MasterLayoutID
 * 			- APIERR_REFUSEDCMD - attempted to modify database parameters during signing in a Teamwork file
 * 			- APIERR_NOTMINE - unsufficient privileges to modify database parameters in Teamwork mode
 * 			- APIERR_GENERAL - failed to modify the database parameters
 * @remarks With this function you can rename an independent detail, worksheet, layout or master layout database, and change their reference ID. Note that you cannot change the title parameter of the database.
 * 			You can also change the Master of a Layout database by passing a valid masterLayoutUnId.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Database_ModifyDatabase-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Database_ModifyDatabase (API_DatabaseInfo* databaseInfo);


/**
 * @brief Deletes an independent detail, worksheet, layout, or master layout database.
 * @ingroup Database
 * @param databaseInfo [in] parameters of the database to be deleted
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOPLAN - no floor plan window opened
 * 			- APIERR_BADPARS - api_dbInfo is nullptr, or contains invalid database reference
 * 			- APIERR_REFUSEDPAR - the passed typeID is not @c APIWind_DetailID, @c APIWind_WorksheetID, @c APIWind_LayoutID or @c APIWind_MasterLayoutID
 * 			- APIERR_REFUSEDCMD - attempted to delete database during signing in a Teamwork file
 * 			- APIERR_NOTMINE - unsufficient privileges to delete database in Teamwork mode
 * 			- APIERR_GENERAL - failed to delete the database
 * @remarks This function is used to delete an independent detail drawing, worksheet layout or master layout database. This operation is not undoable.
 * 			This function performs complete operations, so it cannot be called neither during undoable operations nor during non-undoable commands. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Database_DeleteDatabase-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Database_DeleteDatabase (API_DatabaseInfo* databaseInfo);


/**
 * @brief Retrieves information of the given database.
 * @ingroup Database
 * @param databaseInfo [in/out] parameters of the database
 * @param databaseId [out] Second old identifier.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - databaseInfo is nullptr
 * 			- APIERR_BADDATABASE - the passed database reference is not valid
 * @remarks This function is used to retrieve information about a database specified with databaseUnId.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Window_GetDatabaseInfo-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Window_GetDatabaseInfo (API_DatabaseInfo* databaseInfo, API_DatabaseUnId* databaseId = nullptr);


/**
 * @brief Returns the old database identifiers from the database GUID.
 * @ingroup Database
 * @param elemSetId [in] Unique identifier of the database.
 * @param userId [out] First old identifier.
 * @param databaseId [out] Second old identifier.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - One of the parameters is nullptr.
 * @remarks This function is used to convert the old database identifiers to the new guid.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Database_GetDBUnIdFromGuid-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Database_GetDBUnIdFromGuid (API_Guid* elemSetId, short* userId, UInt32* databaseId);


/**
 * @brief Returns the GUID from old database identifiers.
 * @ingroup Database
 * @param userId [in] First old identifier.
 * @param databaseId [in] Second old identifier.
 * @param elemSetId [out] Unique identifier of the database.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - One of the parameters is nullptr. Or databaseId is 0.
 * @remarks This function is used to convert new database identifier guid to the old identifiers.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Database_GetGuidFromDBUnId-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Database_GetGuidFromDBUnId (short* userId, UInt32* databaseId, API_Guid* elemSetId);


/**
 * @brief Returns the list of unique IDs of all detail databases.
 * @ingroup Database
 * @param databaseUnIds [out] The list of detail database unique IDs. Note this is not handle; it's the address of a pointer. See the example below.
 * @param databaseUnIdArray [out] the array of detail databases, in a more recent form. Pass the address of an appropriate GS::Array<> to get the result. This parameter has precedence over the other databaseUnIds parameter.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - dbUnIDs is nullptr
 * 			- APIERR_NOPLAN - the plan database does not exist
 * @remarks This function is used to return the database unique IDs of all detail databases, including independent details as well. Currently this is the only way you can access independent details.
 * 			Independent details don't have a corresponding detail marker on the floor plan or in any of the sections/elevations.
 * 			One detail database may belong to many detail markers (i.e. if you place the same marker several times, they will all refer to the same detail database).
 * 			You can switch to any of the detail databases by calling the @ref ACAPI_Database_ChangeCurrentDatabase function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Database_GetDetailDatabases-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Database_GetDetailDatabases (API_DatabaseUnId** databaseUnIds, GS::Array<API_DatabaseUnId>* databaseUnIdArray = nullptr);


/**
 * @brief Returns the list of unique IDs of all layout databases.
 * @ingroup Database
 * @param databaseUnIds [out] The list of layout database unique IDs. Note: this is not handle; it's the address of a pointer. You'll have to dispose it with BMpFree when you don't need it any more.
 * @param databaseUnIdArray [out] the array of layout databases, in a more recent form. Pass the address of an appropriate GS::Array<> to get the result. This parameter has precedence over the other databaseUnIds parameter.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - dbUnIDs is nullptr
 * 			- APIERR_NOPLAN - the plan database does not exist
 * @remarks You can get the list of all layout databases with this function, then you can use @ref ACAPI_Database_ChangeCurrentDatabase to switch to that database.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Database_GetLayoutDatabases-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Database_GetLayoutDatabases (API_DatabaseUnId** databaseUnIds, GS::Array<API_DatabaseUnId>* databaseUnIdArray = nullptr);


/**
 * @brief Returns the list of unique IDs of all master layout databases.
 * @ingroup Database
 * @param databaseUnIds [out] The list of master layout database unique IDs. Note this is not handle; it's the address of a pointer.
 * @param databaseUnIdArray [out] the array of master layout databases, in a more recent form. Pass the address of an appropriate GS::Array<> to get the result. This parameter has precedence over the other databaseUnIds parameter.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - dbUnIDs is nullptr
 * 			- APIERR_NOPLAN - the plan database does not exist
 * @remarks You can use this function to enumerate all master layout databases.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Database_GetMasterLayoutDatabases-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Database_GetMasterLayoutDatabases (API_DatabaseUnId** databaseUnIds, GS::Array<API_DatabaseUnId>* databaseUnIdArray = nullptr);


/**
 * @brief Adds new lines to the content of a text window.
 * @ingroup Database
 * @param windowInfo [in] window identification
 * @param content [in] the text to append
 * @param uniContent [in] the Unicode text to append
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - windowPars is nullptr,
 * 			- APIERR_REFUSEDPAR - not @c APIWind_MyTextID is referenced,
 * 			- APIERR_WINDNOTEXIST - the referenced window does not exist
 * @remarks This function is used to append new lines to a text window.
 * 			It is limited to use for custom text windows only, which is opened by @ref ACAPI_Window_NewWindow in the same addon. The Report Window, Missing Library Parts Window etc cannot be addressed with this function.
 * 			The string must be '\0' terminated. Line feeds should be passed with '\n' characters.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Window_AddTextWindowContent-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Window_AddTextWindowContent (API_WindowInfo* windowInfo, const char* content, const GS::UniString* uniContent = nullptr);


/**
 * @brief Convert a model coordinate to screen in the current database.
 * @ingroup View
 * @param coord the coordinate to convert
 * @param point the associated screen coordinate
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - any of the parameters are nullptr.
 * @remarks This function is used to determine the pixel of a real coordinate.
 * 			It is the inverse function of @ref ACAPI_View_PointToCoord function. Note that different coordinates may be assigned to the same pixel. The conversion mainly depends on the window size, on the actual drawing scale and zoom settings (@ref ACAPI_Drawing_GetDrawingScale, @ref ACAPI_View_GetZoom) which means the projection is database dependent.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_View_CoordToPoint-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_View_CoordToPoint (API_Coord* coord, API_Point* point);


/**
 * @brief Convert a screen coordinate into model coordinate in the current database.
 * @ingroup View
 * @param point [in] the pixel screen coordinate to convert
 * @param coord [out] the associated model space coordinate
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - any of the parameters are nullptr
 * @remarks This function is used to determine the real (model space) coordinate of a screen pixel coordinate.
 * 			It is the inverse function of @ref ACAPI_View_CoordToPoint function. Note that different coordinates may be assigned to the same pixel. The conversion mainly depends on the window size, on the actual drawing scale and zoom settings (@ref ACAPI_Drawing_GetDrawingScale, @ref ACAPI_View_GetZoom) which means the projection is database dependent.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_View_PointToCoord-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_View_PointToCoord (API_Point* point, API_Coord* coord);


/**
 * @brief Returns the drawing scale of the current database.
 * @ingroup Drawing
 * @param scale [out] the drawing scale
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - dScale is nullptr
 * @remarks This function returns the drawing scale of the current database, as each database may have different scale.
 * 			Note: for 1:100 drawings 100.0 is returned, for 1:20 drawings 20.0 is returned etc.
 * 			For layouts, the return value is always 1.0.
 */
__APIEXPORT GSErrCode ACAPI_Drawing_GetDrawingScale (double* scale);


/**
 * @brief Changes the drawing scale.
 * @ingroup Drawing
 * @param scale [in] The new scale for the drawing.
 * @param zoom [in] Perform a rebuild command after changing the scale.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - dScale is nullptr or contains wrong value.
 * @remarks This function is used to change the drawing scale of the plan. The scale has to be greater than 1 and smaller than 30000.
 */
__APIEXPORT GSErrCode ACAPI_Drawing_ChangeDrawingScale (double* scale, bool zoom = false);


/**
 * @brief Returns the grid setting parameters of the current database.
 * @ingroup Window
 * @param gridPars [out] the grid parameters
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - `gridPars` is `nullptr`
 * @remarks This function is used to get the parameters of the actual grid setting. It is database dependent, each database may have different grid parameters set. The setting parameters can be changed with the @ref ACAPI_Window_ChangeGridSettings function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Window_GetGridSettings-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Window_GetGridSettings (API_GridType* gridPars);


/**
 * @brief Changes the grid setting parameters of the current database.
 * @ingroup Window
 * @param gridPars [out] the grid parameters
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - gridPars is nullptr
 * @remarks This function is used to change the parameters of the actual grid setting. It is database dependent, each database may have different grid parameters set. The actual setting parameters can be got with the @ref ACAPI_Window_GetGridSettings function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Window_ChangeGridSettings-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Window_ChangeGridSettings (API_GridType* gridPars);


/**
 * @brief Sets the zoom box of the current database.
 * @ingroup View
 * @param zoomBox [in] The zoom parameters to set; pass nullptr to set the zoom factor according to the drawing extent.
 * @param tranmat [in] Transformation matrix (optional parameter).
 * @return
 * 			- NoError - The function has completed with success
 * 			- APIERR_NOPLAN - There is no any project opened
 * 			- APIERR_BADDATABASE - The current database is not 2D drawing type
 * 			- APIERR_BADPARS - The passed zoomBox is incorrect (empty box)
 * @remarks This function is used to set the zoom box of the current 2D drawing type database. The database will not be rebuilt unless the transformation matrix is set.
 * 			To get the actual zoom box refer to the @ref ACAPI_View_GetZoom function. To restore one of the previous zooms use the @ref ACAPI_View_ResetZoom function.
 * 			You can modify the zoom of the 3D model window with the @ref ACAPI_View_Change3DWindowSets environment function.
 * 			In order to set the zoom of the top window, use the @ref ACAPI_View_Zoom automation function instead.
 */
__APIEXPORT GSErrCode ACAPI_View_SetZoom (API_Box* zoomBox = nullptr, API_Tranmat* tranmat = nullptr);


/**
 * @brief Returns the actual zoom parameters of the current database.
 * @ingroup View
 * @param zoomBox [out] The actual zoom parameters
 * @param tranmat [out] Contains the floor plan grid rotation.
 * @return
 * 			- NoError - The function has completed with success
 * 			- APIERR_BADDATABASE - The current database is not 2D drawing type
 * 			- APIERR_BADPARS - zoomBox is nullptr
 * @remarks This function is used to retrieve the zoom box of the window of the current database if it is 2D drawing type window.
 * 			To change the actual zoom box refer to the @ref ACAPI_View_SetZoom function.
 * 			To restore one of the previous zooms use the @ref ACAPI_View_ResetZoom function.
 */
__APIEXPORT GSErrCode ACAPI_View_GetZoom (API_Box* zoomBox = nullptr, API_Tranmat* tranmat = nullptr);


/**
 * @brief Restores the zoom parameters of the current database by a given number of steps.
 * @ingroup View
 * @param numOfStepsBack [in] Number of steps to go back among the previous zoom boxes
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOPLAN - No open project.
 * 			- APIERR_BADDATABASE - The current database does not match to the current window. (This function works only in this case.)
 * 			- APIERR_BADPARS - The step number is less than 1 or greater than the number of currently stored zooms.
 * @remarks This function is used to restore one of the previous zooms. The database will not be rebuilt.
 * 			If the numOfStepsBack parameter is nullptr, the initial zoom is restored, and all the other stored zooms will be erased.
 * 			To get the actual zoom box refer to the @ref ACAPI_View_GetZoom function. To change the actual zoom box refer to the @ref ACAPI_View_SetZoom and the @ref ACAPI_View_Zoom functions.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_View_ResetZoom-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_View_ResetZoom (short* numOfStepsBack);


/**
 * @brief Returns the drawing extent of the current database.
 * @ingroup Element
 * @param extent the extent box
 * @param databaseUnId optional parameter; if nullptr then the extent box is returned for the current database taking into consideration only the visible elements. If a valid database unique ID is given, then the bounding box of that database is returned, including hidden elements.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - extent is nullptr
 * 			- APIERR_NOPLAN - no open project
 * @remarks This function is used to get the drawing extent of the actual database. The extent depends on different settings (hidden layers, actual story etc.), always returns the region would be shown in case of a "Fit in Window" command.
 */
__APIEXPORT GSErrCode ACAPI_Element_GetExtent (API_Box* extent, API_DatabaseUnId* databaseUnId = nullptr);


/**
 * @brief Returns the model extent of the current database.
 * @ingroup Element
 * @param extent3D the extent box
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - extent3D is nullptr
 * 			- APIERR_NOPLAN - no open project
 * @remarks This function is used to get the drawing extent of the actual database, as well as in vertical range. The extent depends on different settings (hidden layers, actual story etc.), always returns the region would be shown in case of a "Fit in Window" command.
 */
__APIEXPORT GSErrCode ACAPI_Element_GetExtent3D (API_Box3D* extent3D);


/**
 * @brief Sets up clipping session for newly created elements to be clipped.
 * @ingroup Database
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NESTING - the clip session is opened for the database
 * @remarks This function creates a temporary database and redirects the subsequent @ref ACAPI_Element_Create calls into it. The elements created during this session then can be copied into the actual element database with the @ref ACAPI_Database_DoClip command applying the given clipping region and transformation. You must close the clipping session with the @ref ACAPI_Database_StopClippingSession database function to restore the target database.
 * 			Note that only the 2D drawing elements will be clipped. Construction elements, like walls, columns will NOT take part in the clipping algorithm.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Database_StartClippingSession-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Database_StartClippingSession ();


/**
 * @brief Clips the elements created during a clipping session.
 * @ingroup Database
 * @param clipRegion the region to clip elements to
 * @param clipTran clipping transformation
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - clipRegion is nullptr
 * 			- APIERR_NESTING - the clip session is opened for the database
 * @remarks You can create elements to be clipped into the current database with a clipping region and transformation. Use the @ref ACAPI_Database_StartClippingSession database function to open a temporary database, create the elements with @ref ACAPI_Element_Create into it, then call @ref ACAPI_Database_DoClip to merge them into the actual database applying the given clipping parameters. Don't forget to close the clipping session with the @ref ACAPI_Database_StopClippingSession database function to restore the target database.
 * 			Note that only the 2D drawing elements will be clipped. Construction elements, like walls, columns will NOT take part in the clipping algorithm.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Database_DoClip-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Database_DoClip (API_Region* clipRegion, API_ClipTran* clipTran = nullptr);


/**
 * @brief Stops clipping elements.
 * @ingroup Database
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_GENERAL - no opened clipping session for the database
 * @remarks This function is used to close the automatic clip service of the server application. Use when a clipping session has been opened by the @ref ACAPI_Database_StartClippingSession database function, if clipping newly created elements is not necessary any more.
 */
__APIEXPORT GSErrCode ACAPI_Database_StopClippingSession ();


/**
 * @brief Redirects element creation into a temporary database for creating drawing data.
 * @ingroup Drawing
 * @param dScale [in] optional parameter (the default value is 1.0); defines the scaling from paper to model. For example, for 1:100 scaling, pass 100.
 * @param api_pens [in] optional parameter (the default pen table is coming from the current workspace (layout or model)); defines the pen table to use for this drawing data.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NESTING - Calls to this function cannot be nested; you have to finish the previous drawing data with @ref ACAPI_Drawing_StopDrawingData.
 * @remarks This function opens an internal store for the drawing data (the internal data of a drawing element). Further element creation functions will put the created elements into this store. Only 2D elements (including figures/pictures) are allowed. This drawing data can be passed later in the drawingData member of the @ref API_ElementMemo to @ref ACAPI_Element_Create.
 * 			The pens have to be passed upfront in the api_pens parameter, and you cannot modify them later. This restriction is coming from the internal setup of the data store.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Drawing_StartDrawingData-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Drawing_StartDrawingData (double* dScale = nullptr, const GS::Array<API_Pen>* api_pens = nullptr);


/**
 * @brief Finalizes the direct creation of drawing elements.
 * @ingroup Drawing
 * @param idfMem [out] an opaque data stream containing the drawing database in a serialized form
 * @param api_boundBox [out] optional parameter; if not nullptr then on return contains the bounding box of the created elements
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function finalizes the database started with @ref ACAPI_Drawing_StartDrawingData. The returned database can be used to create a drawing element on the layout or in the model; pass the idfMem pointer in the drawingData member of @ref API_ElementMemo.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Drawing_StopDrawingData-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Drawing_StopDrawingData (GSPtr* idfMem = nullptr, API_Box* api_boundBox = nullptr);


/**
 * @brief Initializes a loop on the current database to get the elements in the order specified by the BTF/STB system.
 * @ingroup DrawOrder
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function is used to set up a loop to get element in the order the server application would draw them onto the display. Once the loop is initialized the @ref ACAPI_DrawOrder_DrawOrderGetNext function can be called repeatedly to get the element references in order.
 * 			The function can be called any time to reset the loop, it is not necessary to scan all the elements to restart the loop.
 * 			The order of elements depends on the BTF / STB commands invoked by the user. Also the default ordering can be imported while opening an external file, which format give information on this issue.
 * 			Don't forget to call @ref ACAPI_DrawOrder_DrawOrderTerm to allow the server application to free its cached data.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_DrawOrder_DrawOrderInit-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_DrawOrder_DrawOrderInit ();


/**
 * @brief Returns a reference to the next element of the current database in the order specified by the BTF/STB system.
 * @ingroup DrawOrder
 * @param filterBits [in] element filter attributes (pass as VALUE)
 * @param elemHead [out] element reference
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - elemHead is nullptr
 * 			- APIERR_NOMORE - no more element in the list
 * @remarks This function is used to get the database elements in the order the server application would draw them onto the display. The loop should be initialized by the @ref ACAPI_DrawOrder_DrawOrderInit function.
 * 			Pass filter bits (AS A VALUE) to skip elements with specific properties; as shown in the example. See more details on this topic at @ref ACAPI_Element_Filter.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_DrawOrder_DrawOrderGetNext-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_DrawOrder_DrawOrderGetNext (API_ElemFilterFlags filterBits, API_Elem_Head* elemHead);


/**
 * @brief Signals the end of a draw order loop.
 * @ingroup DrawOrder
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function is used to terminate a loop to get element in the order the server application would draw them onto the display. Once the loop is initialized with @ref ACAPI_DrawOrder_DrawOrderInit, then the @ref ACAPI_DrawOrder_DrawOrderGetNext function can be called repeatedly to get the element references in order.
 * 			You have to call this function at the end of each loop, so that the server application can free its cached data.
 */
__APIEXPORT GSErrCode ACAPI_DrawOrder_DrawOrderTerm ();


/**
 * @brief Draws the primitives of the Story Level Control elements on the given Section/Elevation database.
 * @ingroup DrawingPrimitive
 * @param databaseUnId [in] The unique ID of the database
 * @param shapePrimsProc [in] The function to be called to process the element primitives
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed dbUnID or the shapePrimsProc parameter nullptr,
 * @remarks Use this function to export the primitives of the Story Level Control of a Section/Elevation database.
 * 			Similarly to @ref ACAPI_DrawingPrimitive_ShapePrims and @ref ACAPI_LibraryPart_ShapePrims it calls back the passed handler function with each drawing primitive part of the Story Level Handler. Since the Story Level Handler is not a separate element type in API, it is referenced by the database unique ID of the Section/Elevation the Story Levels are displayed on.
 * 			The settings of the Story Level lines and Markers can be accessed via the @ref API_CutPlaneType structure. Note that the primitives are sent only when the value of @c API_StoryHandleAppearance is @c APICutPl_SHAAll in the settings of the Cut Plane element.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_DrawingPrimitive_DrawStoryControl-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_DrawingPrimitive_DrawStoryControl (API_DatabaseUnId* databaseUnId, ShapePrimsProc* shapePrimsProc);


/**
 * @brief Returns the model extent of an element of the current database.
 * @ingroup Element
 * @param elemHead [in] the element reference
 * @param extent3D [out] the 3D enclose box of the element
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Any of the parameters are nullptr.
 * 			- APIERR_BADID - elemHead->guid is invalid.
 * 			- APIERR_DELETED - The element is deleted.
 * @remarks This function is used to determine the model extent of an element. It can be used either to construction or 2D element. In the second case the vertical information will be not filled.
 */
__APIEXPORT GSErrCode ACAPI_Element_CalcBounds (const API_Elem_Head* elemHead, API_Box3D* extent3D);


/**
 * @brief Returns reduction data assigned to a room of the current database.
 * @ingroup Element
 * @param guid The referenced zone GUID identifier
 * @param roomReductionPolyProc Callback function to export reduction information
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Any of the parameters are nullptr.
 * 			- APIERR_NESTING - The function is called from the body of a RoomReductionPolyProc.
 * 			- APIERR_BADID - The zone reference is invalid.
 * 			- APIERR_DELETED - The zone is deleted.
 * @remarks Zones have very complex relationships to other elements.
 * 			This function is used to make easy to find what elements may reduce the zone area and how.
 * 			These elements may be walls, colums, hatches, gables and rest. The overlapping places return only by either of them (see image below).
 * @image html RoomRedPoly.png "Room reduction polygon" width=50%
 * 		  The reduction polygons can be obtained by the `RoomReductionPolyProc` callback function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_RoomReductions-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_RoomReductions (const API_Guid* guid, RoomReductionPolyProc* roomReductionPolyProc);


/**
 * @brief Retrieves the URL reference assigned to an element.
 * @ingroup Element
 * @param elem_Head [in] The element the URL was assigned to.
 * @param elemURLRef [out] The URL reference of the element.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Any of the parameters are nullptr.
 * 			- APIERR_BADINDEX - The element is not present in the Archicad database.
 * 			- APIERR_BADID - The element cannot hold a URL reference.
 * 			- APIERR_DELETED - The element is deleted.
 * 			- APIERR_NOUSERDATA - The element didn't hold a URL reference.
 * @remarks This function is used to retrieve the URL reference assigned to an element. The same group of elements can hold a URL reference as userdata.
 */
__APIEXPORT GSErrCode ACAPI_Element_GetElementURLRef (API_Elem_Head* elem_Head, API_ElemURLRef* elemURLRef);


/**
 * @brief Assigns a URL reference to an element.
 * @ingroup Element
 * @param elemHead [in] The element the URL has to be assigned to.
 * @param elemURLRef [in] The URL reference of the element.
 * @return
 * 			- NoError - The function was completed successfully.
 * 			- APIERR_BADPARS - Any of the parameters are nullptr.
 * 			- APIERR_BADINDEX - The element is not present in the Archicad database.
 * 			- APIERR_BADID - The element cannot hold a URL reference.
 * 			- APIERR_DELETED e - The element is deleted.
 * 			- APIERR_MOREUSER - The element already holds a URL reference.
 * @remarks This function is used for assigning a URL reference to an Archicad database element. The same group of elements can hold a URL reference as userdata.
 */
__APIEXPORT GSErrCode ACAPI_Element_SetElementURLRef (API_Elem_Head* elemHead, API_ElemURLRef* elemURLRef);


/**
 * @brief Rebuilds (refreshes) a library part instance.
 * @ingroup Element
 * @param elemHead identifies the element to refresh
 * @param force force rebuild for GDL based elements (run parameter script).
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - elemHead is nullptr
 * 			- APIERR_BADINDEX - The element is not present in the Archicad database.
 * 			- APIERR_DELETED - The element is deleted.
 * @remarks This function is used to refresh (rebuild) a library part instance identified by its element header on the floor plan or in the section or detail window.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_Element_RefreshElement (API_Elem_Head* elemHead, bool* force);


/**
 * @brief Shows/draws an existing element.
 * @ingroup Element
 * @param elem_Head identifies the element to draw/show
 * @param mask [in] Element mask (from floor plan).
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - elemHead is nullptr
 * 			- APIERR_BADID - The element is not present in the Archicad database.
 * 			- APIERR_DELETED - The element is deleted.
 * @remarks This function is used to draw/show an element identified by its element header on the floor plan or in the section or detail window. You should fill the guid field.
 */
__APIEXPORT GSErrCode ACAPI_Element_DrawElement (API_Elem_Head* elem_Head, UInt32 mask);


/**
 * @brief Initializes an internal table for fast access of the next element in creation order.
 * @ingroup DrawOrder
 * @param elemFilter [in] Optional parameter, can be nullptr. Use this filter to leave out element types from the access table.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_MEMFULL - The internal creation order table cannot be allocated.
 * 			- APIERR_NESTING - Internal access table initializations cannot be nested, i.e. you should dispose the previously allocated table before initializing a new one.
 * @remarks This function is used to set up an internal table which allows fast access to the next element in creation order (an ordering more or less equal to the unique ID ordering in previous versions).
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_DrawOrder_InitCreationOrderTable-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_DrawOrder_InitCreationOrderTable (API_ElemFilter* elemFilter);


/**
 * @brief Returns the next element's guid from the previously initialized creation order table.
 * @ingroup DrawOrder
 * @param guid [in/out] On input this is the guid of the element for which the following in creation order is sought. On output this is the guid of the following element.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The guid parameter is nullptr.
 * 			- APIERR_GENERAL - The creation order table was not allocated beforehand.
 * 			- APIERR_NOMORE - The guid parameter is not in the table or it was the last elem.
 * @remarks This function is used to get the next element's guid in element creation order. Input a value of APINULLGuid to get the first element; an output value of APINULLGuid means the last elem. The creation order table must be initialized beforehand with @ref ACAPI_DrawOrder_InitCreationOrderTable.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_DrawOrder_CreationOrderGetNext-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_DrawOrder_CreationOrderGetNext (API_Guid* guid);


/**
 * @brief Disposes the previously allocated creation order table.
 * @ingroup DrawOrder
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_GENERAL - The creation order table was not allocated beforehand.
 * @remarks This function is used to dispose the creation order table allocated by @ref ACAPI_DrawOrder_InitCreationOrderTable.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_DrawOrder_DisposeCreationOrderTable-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_DrawOrder_DisposeCreationOrderTable ();


/**
 * @brief Switches between different 3D databases.
 * @ingroup Sight
 * @param newSight The ID of the sight (as value!)
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Incorrect sight ID was passed.
 * @remarks This function is used to switch between the 3D database behind the real 3D window and 3D database behind the API (the 3D information for an element is coming from the floor plan). The switch usually takes no time unless the database doesn't exist or was deleted; in these cases the database is rebuilt.
 */
__APIEXPORT GSErrCode ACAPI_Sight_Switch3DSight (API_3DSightID newSight);


/**
 * @brief Returns the offset of origin of the virtual coordinate system.
 * @ingroup ProjectSetting
 * @param offset the offset of the origin of the virtual coordinate system
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - offset is nullptr
 * 			- APIERR_BADDATABASE - the command was called for a non-2D window
 * @remarks This function is used to get the offset of the origin of the virtual coordinate system from the origin of the world coordinate system.
 * 			This origin was introduced in Archicad 9 to reduce the inaccuracies, which could happen if the model was far away from the origin of the world coordinate system. This offset is set after a file is opened, if the so called 'weight point' of the model is far enough from the origin of the world coordinate system.
 * 			After that all coordinates coming from the API are measured from this origin.
 */
__APIEXPORT GSErrCode ACAPI_ProjectSetting_GetOffset (API_Coord* offset);


/**
 * @brief Returns the local origin of the current database.
 * @ingroup Database
 * @param locOrigin the local origin
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - locOrigin is nullptr
 * 			- APIERR_BADDATABASE - the query is valid only for the plan, section, detail and 3D window.
 * @remarks This function is used to get the local origin of the current database. This can be modified by the user by clicking on the User Origin button on the coordinate box. The value is measured relative to the origin of the virtual coordinate system.
 */
__APIEXPORT GSErrCode ACAPI_Database_GetLocOrigo (API_Coord3D* locOrigin);


/**
 * @brief Returns various information on a drawing link.
 * @ingroup Drawing
 * @param guid [in] get information for drawing link identified with drawing's guid
 * @param drawingLinkInfo [out] the drawing link's type, guid, etc.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The drawing link is not valid.
 * @remarks This function is used to get basic information about a drawing link identified by the linkUID parameter.
 * 			Remember to release the linkPath location and the viewPath pointer dynamically allocated by the function, as it is shown in the example below.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Drawing_GetDrawingLink-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Drawing_GetDrawingLink (const API_Guid* guid, API_DrawingLinkInfo* drawingLinkInfo);


/**
 * @brief Checks whether the given drawing is up-to-date.
 * @ingroup Drawing
 * @param guid [in] The GUID of the drawing element
 * @param status [out] 1  if the drawing is up-to-date, 0  if modified, -1  otherwise
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The status parameter is nullptr, or the drawing contains invalid link ID.
 * 			- APIERR_BADINDEX - The guid is not valid, or the drawing comes from a master layout.
 * @remarks Call this function to check the status of a drawing quickly (as seen on the Drawing Link Manager palette).
 */
__APIEXPORT GSErrCode ACAPI_Drawing_CheckDrawingStatus (API_Guid* guid, Int32* status);


/**
 * @brief Stores/restores the actual view settings.
 * @ingroup View
 * @param store [in] stores the settings if not 0  , restore if 0
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The function cannot be stacked.
 * @remarks Stores general view settings for a view before longer operations (e.g. saving the contents of a drawing elment), and restores them afterwards.
 * 			This function has to be called in pairs, and cannot be stacked.
 * 			Use this sparingly; may cause a rebuild.
 */
__APIEXPORT GSErrCode ACAPI_View_StoreViewSettings (bool store);


/**
 * @brief Retrieves the TeamWork owner of a given database.
 * @ingroup Teamwork
 * @param databaseUnId [in] The unique ID of the database
 * @param userId [out] The TeamWork user ID of the owner of the specified database
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The dbUnID or the userId parameter is nullptr, or dbUnID is not valid
 * @remarks This function is used to get the user ID of the owner of a database.
 * 			You can get the user ID of the current TeamWork client with @ref ACAPI_ProjectOperation_Project.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Teamwork_GetTWOwner-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Teamwork_GetTWOwner (API_DatabaseUnId* databaseUnId, short* userId);


/**
 * @brief Returns all the section databases in the project.
 * @ingroup Database
 * @param databaseUnIds the array of section databases (address of a pointer! not a handle).
 * @param databaseUnIdArray [out] the array of section databases, in a more recent form. Pass the address of an appropriate GS::Array<> to get the result. This parameter has precedence over the other databaseUnIds parameter.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks Don't forget to dispose the allocated pointer with BMpFree.
 */
__APIEXPORT GSErrCode ACAPI_Database_GetSectionDatabases (API_DatabaseUnId** databaseUnIds, GS::Array<API_DatabaseUnId>* databaseUnIdArray = nullptr);


/**
 * @brief Returns all the elevation databases in the project.
 * @ingroup Database
 * @param databaseUnIds the array of elevation databases (address of a pointer! not a handle).
 * @param databaseUnIdArray [out] the array of elevation databases, in a more recent form. Pass the address of an appropriate GS::Array<> to get the result. This parameter has precedence over the other databaseUnIds parameter.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks Don't forget to dispose the allocated pointer with BMpFree.
 */
__APIEXPORT GSErrCode ACAPI_Database_GetElevationDatabases (API_DatabaseUnId** databaseUnIds, GS::Array<API_DatabaseUnId>* databaseUnIdArray = nullptr);


/**
 * @brief Returns all the interior elevation databases in the project.
 * @ingroup Database
 * @param databaseUnIds the array of interior elevation databases (address of a pointer! not a handle).
 * @param databaseUnIdArray [out] the array of interior elevation databases, in a more recent form. Pass the address of an appropriate GS::Array<> to get the result. This parameter has precedence over the other databaseUnIds parameter.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks Don't forget to dispose the allocated pointer with BMpFree.
 */
__APIEXPORT GSErrCode ACAPI_Database_GetInteriorElevationDatabases (API_DatabaseUnId** databaseUnIds, GS::Array<API_DatabaseUnId>* databaseUnIdArray = nullptr);


/**
 * @brief Returns the list of unique IDs of all detail databases.
 * @ingroup Database
 * @param databaseUnIds [out] The list of worksheet database unique IDs. Note this is not handle; it's the address of a pointer. See the example below.
 * @param databaseUnIdArray [out] the array of worksheet databases, in a more recent form. Pass the address of an appropriate GS::Array<> to get the result. This parameter has precedence over the other databaseUnIds parameter.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - dbUnIDs is nullptr
 * 			- APIERR_NOPLAN - the plan database does not exist
 * @remarks This function is used to return the database unique IDs of all worksheets databases, including independent details as well. Currently this is the only way you can access independent details.
 * 			[Independent worksheets don't have a corresponding detail marker on the floor plan or in any of the sections/elevations.???]
 * 			[One worksheet database may belong to many worksheet markers (i.e. if you place the same marker several times, they will all refer to the same worksheet database).???]
 * 			You can switch to any of the worksheet databases by calling the @ref ACAPI_Database_ChangeCurrentDatabase function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Database_GetWorksheetDatabases-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Database_GetWorksheetDatabases (API_DatabaseUnId** databaseUnIds, GS::Array<API_DatabaseUnId>* databaseUnIdArray = nullptr);


/**
 * @brief Returns the list of unique IDs of all document 3D databases.
 * @ingroup Database
 * @param databaseUnIds [out] The list of document 3D database unique IDs. Note this is not handle; it's the address of a pointer. See the example below.
 * @param databaseUnIdArray [out] the array of 3D document databases, in a more recent form. Pass the address of an appropriate GS::Array<> to get the result. This parameter has precedence over the other databaseUnIds parameter.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - dbUnIDs is nullptr
 * 			- APIERR_NOPLAN - the plan database does not exist
 * @remarks This function is used to return the database unique IDs of all document 3D databases. Currently this is the only way you can access these kind of databases because they don't have markers.
 * 			You can switch to any of the other databases by calling the @ref ACAPI_Database_ChangeCurrentDatabase function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Database_GetDocumentFrom3DDatabases-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Database_GetDocumentFrom3DDatabases (API_DatabaseUnId** databaseUnIds, GS::Array<API_DatabaseUnId>* databaseUnIdArray = nullptr);


/**
 * @brief Returns the full boundary box of an IDF database.
 * @ingroup Drawing
 * @param api_box [out] The bounding box of the drawing's IDF.
 * @param drawingGuid [in] The guid of the drawing contains the IDF.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADINDEX - The drawingGuid parameter is invalid.
 * @remarks This function is used to get the bounding box of drawing's IDF.
 */
__APIEXPORT GSErrCode ACAPI_Drawing_GetFullDrawingContentBox (API_Box* api_box, const API_Guid* drawingGuid);


/**
 * @brief Retrieves the default Subset settings of the Layout Book.
 * @ingroup Navigator
 * @param subSet The default Subset.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - subSet is nullptr
 * @remarks This function retrieves the default subset settings of the Layout Book. You can create subsets via @ref ACAPI_Navigator_CreateSubSet function.
 */
__APIEXPORT GSErrCode ACAPI_Navigator_GetSubSetDefault (API_SubSet* subSet);


/**
 * @brief Creates the Subset in the Layout Book.
 * @ingroup Navigator
 * @param subSet The Subset.
 * @param parentGuid The guid of parent node in the Navigator's Layout Map
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - parentGuid is nullptr
 * 			- APIERR_MEMFULL - Not enough memory to complete the operation.
 * @remarks You can create subsets in the Layout Book with this function. You are able to get the default SubSet Settings via @ref ACAPI_Navigator_GetSubSetDefault database function. This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_Navigator_CreateSubSet (const API_SubSet* subSet, const API_Guid* parentGuid = nullptr);


/**
 * @brief Retrieves the Subset settings of the given Layout Subset.
 * @ingroup Navigator
 * @param guid The guid of the Layout Subset.
 * @param subSet The Subset.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - subSet is nullptr
 * @remarks This function retrieves the subset settings of a Layout Subset given by @ref API_Guid. You can create subsets via @ref ACAPI_Navigator_CreateSubSet function.
 */
__APIEXPORT GSErrCode ACAPI_Navigator_GetSubSet (const API_Guid* guid, API_SubSet* subSet);


/**
 * @brief Retrieves the Book Settings.
 * @ingroup Navigator
 * @param book The Book settings.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - book is nullptr
 * @remarks This function retrieves the Book settings.
 */
__APIEXPORT GSErrCode ACAPI_Navigator_GetLayoutBook (API_LayoutBook* book);


/**
 * @brief Returns a hotlink node identified by its guid.
 * @ingroup Hotlink
 * @since Archicad 26
 * @param hotlinkNode [in/out] Hotlink node.
 * @param enableUnplaced [in] True if the search is performed in all hotlink nodes (including cached ones) and false if only in placed ones.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - hotlinkNode parameter is nullptr
 * @remarks This function is used to get the data of the specified hotlink node.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Hotlink_GetHotlinkNode-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Hotlink_GetHotlinkNode (API_HotlinkNode* hotlinkNode, bool* enableUnplaced = nullptr);


/** 
 * @brief Creates a hotlink node without updating its cache content.
 * @ingroup Hotlink
 * @param hotlinkNode [in/out] the hotlink node to be created
 * @return
 *	- NoError - The function has completed with success.
 *	- APIERR_BADPARS - hotlinkNode parameter is nullptr, or sourceLocation is nullptr or invalid.
 * @remarks This function is used to add a new hotlink node to the project.
 *  The hotlink can be either @c APIHotlink_Module or @c APIHotlink_XRef type A valid sourceLocation must be specified. On success the Guid of the new hotlink node returns in the guid field of the hotlinkNode parameter.
 *  Creating a hotlink node does not make the hotlinked content appear in the project. This simply creates a reference to the source module file, and prepares a cache which contains the elements and attributes as an image of the original source. In order to place a hotlink instance on the plan, you need to create an @ref API_HotlinkType element referring to this hotlink node with the appropriate hotlinkNodeGuid identifier.
 *  Note that XRefs are handled by the DXF/DWG add-on, and the format of their userdata is not published.
 *  This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_Hotlink_GetHotlinkStoryInfo (API_HotlinkNode* hotlinkNode);


/**
 * @brief Gets the story info from a hotlink source file.
 * @ingroup Hotlink
 * @param hotlinkNode [in/out] the hotlink node which contains the location of the file
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - hotlinkNode parameter is nullptr, or sourceLocation is nullptr or invalid.
 * @remarks This function is used to get the story info from a hotlink source file, usually called before creating a hotlink node with the right story settings (storyRangeType, refFloorInd).
 * 			The hotlink can be @c APIHotlink_Module A valid sourceLocation must be specified. On success the ... of the new hotlink node returns in the guid field of the hotlinkNode parameter.
 * 			Ths function does not create a hotlink node and does not changes the database.
 */
__APIEXPORT GSErrCode ACAPI_Hotlink_CreateHotlinkNode (API_HotlinkNode* hotlinkNode);


/**
 * @brief Modifies the parameters of a hotlink node.
 * @ingroup Hotlink
 * @param hotlinkNode [in] hotlink node data to be changed
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - hotlinkNode parameter is nullptr.
 * 			- APIERR_BADID - guid of hotlinkNode is invalid.
 * @remarks This function is used to modify the data of a hotlink node. The node is identified by the guid member of the hotlinkNode parameter.
 * 			Only the sourceLocation, ownerId and userData parameters can be modified.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_Hotlink_ModifyHotlinkNode (API_HotlinkNode* hotlinkNode);


/**
 * @brief Deletes the given hotlink node.
 * @ingroup Hotlink
 * @param hotlinkNodeGuid [in] guid of the hotlink node to be deleted
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - hotlinkNodeGuid parameter is nullptr.
 * 			- APIERR_BADID - hotlinkNodeGuid is invalid.
 * 			- APIERR_NEEDSUNDOSCOPE - The function must be undoable, it wasn't called from an undoable command scope.
 * @remarks This function deletes the hotlink node identified by the hotlinkNodeGuid parameter. Unlike @ref ACAPI_Hotlink_BreakHotlinkNode all the instance elements created from this node are removed from the project.
 */
__APIEXPORT GSErrCode ACAPI_Hotlink_DeleteHotlinkNode (const API_Guid* hotlinkNodeGuid);


/**
 * @brief Breaks the link of the given hotlink node.
 * @ingroup Hotlink
 * @param hotlinkNodeGuid [in] guid of the hotlink node to be broken
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - hotlinkNodeGuid parameter is nullptr.
 * 			- APIERR_BADID - hotlinkNodeGuid is invalid.
 * 			- APIERR_NEEDSUNDOSCOPE - The function must be undoable, it wasn't called from an undoable command scope.
 * @remarks This function deletes the hotlink node identified by the hotlinkNodeGuid parameter. Unlike @ref ACAPI_Hotlink_DeleteHotlinkNode the instance elements are not deleted from the project, but converted into normal elements grouped together.
 */
__APIEXPORT GSErrCode ACAPI_Hotlink_BreakHotlinkNode (const API_Guid* hotlinkNodeGuid);


/**
 * @brief Updates the cache of the given hotlink node.
 * @ingroup Hotlink
 * @param hotlinkNodeGuid [in] guid of the hotlink node
 * @param hotlinkCacheGenerator [in] optional cache content generator object
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - hotlinkNodeGuid parameter is nullptr
 * 			- APIERR_BADID - hotlinkNodeGuid is invalid
 * @remarks This function is used to update the cache of a hotlink node.
 * 			If the hotlink content is supposed to be generated by the add-on, you need to pass a generator object. The GenerateCacheContentForHotlinkNode method of @ref API_HotlinkCacheGenerator must be implemented to create the new (updated) content of the specified hotlink cache. When this method is called back from the @ref ACAPI_Hotlink_UpdateHotlinkCache function, the standard element and attribute creator functions (like @ref ACAPI_Element_Create and @ref ACAPI_Attribute_Create) are redirected to create elements and attributes into the hotlink cache database, rather than the project database.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Hotlink_UpdateHotlinkCache-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Hotlink_UpdateHotlinkCache (const API_Guid* hotlinkNodeGuid, API_HotlinkCacheGenerator* hotlinkCacheGenerator = nullptr);


/**
 * @brief Returns the list of hotlink nodes.
 * @ingroup Hotlink
 * @since Archicad 26
 * @param type [in] optional type selector ( APIHotlink_Module or @c APIHotlink_XRef), if this variable is nullptr, all nodes are collected
 * @param nodeRefList [out] the list of hotlink nodes found in the project
 * @param enableUnplaced [in] True if the search is performed in all hotlink nodes (including cached ones) and false if only in placed ones.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - the nodeRefList parameter is nullptr
 * @remarks This function returns the hotlink nodes as a list of Guids. The data of a hotlink node can be retrieved with the @ref ACAPI_Hotlink_GetHotlinkNode function. To explore a nested node hierarchy, use @ref ACAPI_Hotlink_GetHotlinkNodeTree. In order to get the hotlink instances placed in the project, use the @ref ACAPI_Hotlink_GetHotlinkInstances function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Hotlink_GetHotlinkNodes-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Hotlink_GetHotlinkNodes (const API_HotlinkTypeID* type, GS::Array<API_Guid>* nodeRefList, bool* enableUnplaced = nullptr);


/**
 * @brief Retrieves the Guid of the Hotlink Module type or XRef type hotlink root node.
 * @ingroup Hotlink
 * @param type [in] hotlink type selector ( APIHotlink_Module or @c APIHotlink_XRef)
 * @param rootNodeGuid [out] the Guid of the selected root node
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - any of the parameters is nullptr
 * 			- APIERR_BADID - the type parameter is neither @c APIHotlink_Module nor @c APIHotlink_XRef
 * @remarks This function retrieves the Guid identifier of the root hotlink node of the selected type. This root node is not a real hotlink node, it actually represents the project itself, and can be used as the parent of the main-level hotlinks when the whole structure is requested with the @ref ACAPI_Hotlink_GetHotlinkNodeTree function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Hotlink_GetHotlinkRootNodeGuid-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Hotlink_GetHotlinkRootNodeGuid (const API_HotlinkTypeID* type, API_Guid* rootNodeGuid);


/**
 * @brief Retrieves the tree structure under a given hotlink node.
 * @ingroup Hotlink
 * @param hotlinkNodeGuid [in] Guid of the parent node
 * @param hotlinkNodeTree [out] the tree structure under the given parent node
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - any of the parameters is nullptr
 * @remarks This function helps to explore the nested node hierarchy of hotlinks used in the project. The structure is presented in a hashtable of parent node and array of children nodes pairs.
 * 			The top node of the tree is defined by the hotlinkNodeGuid parameter, which is usually either the Hotlink Module type or the XRef type hotlink root node (these can be retrieved with the @ref ACAPI_Hotlink_GetHotlinkRootNodeGuid function), however it can be any of the nodes when only a sub-tree is requested.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Hotlink_GetHotlinkNodeTree-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Hotlink_GetHotlinkNodeTree (const API_Guid* hotlinkNodeGuid, GS::HashTable<API_Guid, GS::Array<API_Guid>>* hotlinkNodeTree);


/**
 * @brief Returns a list of hotlink instance elements placed from the given hotlink node.
 * @ingroup Hotlink
 * @param hotlinkNodeGuid [in] the Guid of the hotlink node
 * @param elementRefList [out] Guid list of the hotlink instances
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - any of the parameters is nullptr
 * 			- APIERR_BADID - no hotlink element found by the specified Guid
 * @remarks This function retrieves the @ref API_HotlinkType hotlink instance elements of the specified hotlink node.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Hotlink_GetHotlinkInstances-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Hotlink_GetHotlinkInstances (const API_Guid* hotlinkNodeGuid, GS::Array<API_Guid>* elementRefList);


/**
 * @brief Returns the identifier of the hotlink instance the element belongs to (see @ref API_HotlinkType).
 * @ingroup Hotlink
 * @param elemGuid [in] The Guid of the element.
 * @param hotlinkGuid [out] The hotlink instance the element belongs to. @ref APINULLGuid means the element is not part of any hotlinks.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Any of the parameters is nullptr
 * 			- APIERR_BADID - The elemGuid is invalid or the element is deleted.
 * @remarks This function retrieves the identifier of the hotlink (API_HotlinkType) instance the incoming element belongs to.
 */
__APIEXPORT GSErrCode ACAPI_Hotlink_GetHotLinkOwner (const API_Guid* elemGuid, API_Guid* hotlinkGuid);


/**
 * @brief Returns the mapping table of the proxy elements and the source elements of the given hotlink instance.
 * @ingroup Hotlink
 * @since Archicad 25
 * @param hotlinkGuid [in] The guid of the hotlink instance.
 * @param proxyElementTable [out] A hashtable in which the keys are the proxy elements in the current project and the values are the source elements from the hotlinked project.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOPLAN - There is no opened project.
 * 			- APIERR_BADID - The hotlinkGuid is invalid, it does not refer to an element.
 * 			- APIERR_BADELEMENTTYPE - The hotlinkGuid does not belong to a hotlink instance.
 */
__APIEXPORT GSErrCode ACAPI_Hotlink_GetHotlinkProxyElementTable (const API_Guid* hotlinkGuid, GS::HashTable<API_Guid, API_Guid>* proxyElementTable);


/**
 * @brief Returns the status of the given hotlink source file.
 * @ingroup Hotlink
 * @param hotlinkLocation [in] The location of the hotlink file.
 * @param hotlinkSourceStatus [out] The status (availability) of the hotlink.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOPLAN - There is no opened project.
 * 			- APIERR_REFUSEDPAR - The hotlink location is invalid, or the location does not point to a hotlink.
 * 			- APIERR_BADELEMENTTYPE - The hotlinkGuid does not belong to a hotlink instance.
 */
__APIEXPORT GSErrCode ACAPI_Hotlink_GetHotlinkSourceStatus (const IO::Location* hotlinkLocation, API_HotlinkSourceStatus* hotlinkSourceStatus);


/**
 * @brief Returns the compound info string of the given element.
 * @ingroup Element
 * @param elementGuid [in] the Guid of the element
 * @param infoString [out] the composite info string of the element
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - any of the parameters is nullptr
 * 			- APIERR_BADID - no element found by the specified Guid
 * 			- APIERR_BADELEMENTTYPE - element has no info string
 * @remarks For hotlinked elements the info string is composed of the element's own info string and the hotlink element's info strings it placed via.
 */
__APIEXPORT GSErrCode ACAPI_Element_GetCompoundInfoString (const API_Guid* elementGuid, GS::UniString* infoString);


/**
 * @brief Obtains the unique ID of database contains the given element.
 * @ingroup Database
 * @param element [in] The referred element.
 * @param dbInfo [out] The owner database ID.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The guid or dbInfo parameter is nullptr.
 * 			- APIERR_NOPLAN - There is no open project.
 * @remarks This function is used to get the ID of owner database of the referred element.
 */
__APIEXPORT GSErrCode ACAPI_Database_GetContainingDatabase (const API_Guid* element, API_DatabaseInfo* dbInfo);


/**
 * @brief Returns the element referred by guid irrespectively of the current database.
 * @ingroup Element
 * @param guid [in] The referred element.
 * @param element [out] The element.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The guid or element parameter is nullptr.
 * 			- APIERR_NOPLAN - There is no open project.
 * @remarks This function is used to get an element irrespectively of the current database. This is a useful function because you don't have to enumerate all database to find the element, switch to it and get the element.
 */
__APIEXPORT GSErrCode ACAPI_Element_GetElementFromAnywhere (const API_Guid* guid, API_Element* element);


/**
 * @brief Checks whether the curtain wall panel is degenerate.
 * @ingroup CurtainWall
 * @param guid [in] Curtain wall panel reference.
 * @param isDegenerate [out] Is the panel degenerate?
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - guid or height parameter is nullptr.
 * 			- APIERR_BADID - guid is invalid or is not a curtain wall panel reference.
 * @remarks Curtain Wall element may contain degenerate panel elements (eg. its length is Eps). These elements are not selectable but for technical reasons database must contains them. This function is used to filter these CW panels.
 */
__APIEXPORT GSErrCode ACAPI_CurtainWall_IsCWPanelDegenerate (const API_Guid* guid, bool* isDegenerate);


/**
 * @brief Returns the current renovation filter.
 * @ingroup Renovation
 * @param renovationFilterGuid [out] The GUID of the current renovation filter.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function returns the Guid of the current renovation filter.
 * 			The list of the renovation filters can be retrieved with the @ref ACAPI_Renovation_GetRenovationFilters function.
 */
__APIEXPORT GSErrCode ACAPI_Renovation_GetActualRenovationFilter (API_Guid* renovationFilterGuid);


/**
 * @brief Changes the current renovation filter.
 * @ingroup Renovation
 * @since Archicad 25
 * @param renovationFilterGuid [in] The GUID of the new renovation filter.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function is changing the current renovation filter.
 * 			The list of the renovation filters can be retrieved with the @ref ACAPI_Renovation_GetRenovationFilters function.
 */
__APIEXPORT GSErrCode ACAPI_Renovation_SetActualRenovationFilter (const API_Guid* renovationFilterGuid);


/**
 * @brief Returns the array of renovation filters.
 * @ingroup Renovation
 * @param renovationFilterList [out] The array of renovation filters.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The renovationFilterList parameter is nullptr.
 * @remarks This function returns the renovation filters as an array of Guids. To get the current renovation filter use the @ref ACAPI_Renovation_GetActualRenovationFilter function.
 * 			The name of the renovation filter can be retrieved with the @ref ACAPI_Renovation_GetRenovationFilterName function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Renovation_GetRenovationFilters-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Renovation_GetRenovationFilters (GS::Array<API_Guid>* renovationFilterList);


/**
 * @brief Retrieves all changes.
 * @ingroup Revision
 * @param api_changes The array of the changes.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - api_changes is nullptr.
 * 			- APIERR_GENERAL - Couldn't get the changes.
 * @remarks This function retrieves all changes.
 */
__APIEXPORT GSErrCode ACAPI_Revision_GetRVMChanges (GS::Array<API_RVMChange>* api_changes);


/**
 * @brief Retrieves change custom scheme.
 * @ingroup Revision
 * @param customScheme Contains @ref API_Guid (unique identifier of a custom field), GS::UniString (name of a custom field) pairs.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - customScheme is nullptr.
 * 			- APIERR_GENERAL - Couldn't get the customScheme.
 * @remarks This function retrieves custom fields of the @ref API_RVMChange s.
 */
__APIEXPORT GSErrCode ACAPI_Revision_GetRVMChangeCustomScheme (GS::HashTable<API_Guid, GS::UniString>* customScheme);


/**
 * @brief Retrieves all issues.
 * @ingroup Revision
 * @param api_issues The array of the issues.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - api_issues is nullptr.
 * 			- APIERR_GENERAL - Couldn't get the issues.
 * @remarks This function retrieves all issues.
 */
__APIEXPORT GSErrCode ACAPI_Revision_GetRVMIssues (GS::Array<API_RVMIssue>* api_issues);


/**
 * @brief Modify an RVM issue.
 * @ingroup Revision
 * @param api_issue [in] The RVM issue to change.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - api_issue is nullptr.
 * 			- APIERR_BADNAME - the ID in api_issue is not valid.
 * 			- APIERR_NOACCESSRIGHT - api_issue has already been issued.
 * 			- APIERR_GENERAL - Couldn't get the issues.
 * @remarks This function modifies the short description, the ID, or the custom data of the given issue.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_Revision_ChangeRVMIssue (API_RVMIssue* api_issue);


/**
 * @brief Retrieves issue custom scheme.
 * @ingroup Revision
 * @param customScheme Contains @ref API_Guid (unique identifier of a custom field), GS::UniString (name of a custom field) pairs.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - customScheme is nullptr.
 * 			- APIERR_GENERAL - Couldn't get the customScheme.
 * @remarks This function retrieves custom fields of the @ref API_RVMIssue s.
 */
__APIEXPORT GSErrCode ACAPI_Revision_GetRVMIssueCustomScheme (GS::HashTable<API_Guid, GS::UniString>* customScheme);


/**
 * @brief Retrieves all document revisions.
 * @ingroup Revision
 * @param api_revisions The array of the document revisions.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - api_revisions is nullptr.
 * 			- APIERR_GENERAL - Couldn't get the document revisions.
 * @remarks This function retrieves all document revisions.
 */
__APIEXPORT GSErrCode ACAPI_Revision_GetRVMDocumentRevisions (GS::Array<API_RVMDocumentRevision>* api_revisions);


/**
 * @brief Retrieves all changes those given by unique change IDs.
 * @ingroup Revision
 * @param changeIds The array of the change IDs.
 * @param api_changes The array of the changes.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - changeIds or api_changes is nullptr.
 * 			- APIERR_GENERAL - Couldn't get the changes.
 * @remarks If only unique change IDs are owned, @ref API_RVMChange s can be retrieved by this function.
 */
__APIEXPORT GSErrCode ACAPI_Revision_GetRVMChangesFromChangeIds (const GS::Array<GS::UniString>* changeIds, GS::Array<API_RVMChange>* api_changes);


/**
 * @brief Retrieves all changes belong to the last revision of the given layout.
 * @ingroup Revision
 * @param inUnId The unique ID of the layout database.
 * @param api_changes The array of the changes.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - inUnId or api_changes is nullptr.
 * 			- APIERR_GENERAL - Couldn't get the layout database.
 * @remarks You are able to get changes contained by the last revision of the given layout.
 */
__APIEXPORT GSErrCode ACAPI_Revision_GetRVMLayoutCurrentRevisionChanges (const API_DatabaseUnId* inUnId, GS::Array<API_RVMChange>* api_changes);


/**
 * @brief Retrieves all document revisions belong to the given issue.
 * @ingroup Revision
 * @param issueGuid GUID of the issue.
 * @param api_revisions The array of the document revisions.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - issueGuid or api_revisions is nullptr.
 * 			- APIERR_BADID - issueGuid does not identify a valid issue.
 * 			- APIERR_GENERAL - Couldn't get the document revisions.
 * @remarks You are able to get document revisions contained by the given issue.
 */
__APIEXPORT GSErrCode ACAPI_Revision_GetRVMIssueDocumentRevisions (const API_Guid* issueGuid, GS::Array<API_RVMDocumentRevision>* api_revisions);


/**
 * @brief Retrieves all changes belong to the given document revision.
 * @ingroup Revision
 * @param revisionGuid GUID of the document revision.
 * @param api_changes The array of the changes.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - revisionGuid or api_changes is nullptr.
 * 			- APIERR_BADID - revisionGuid does not identify a valid document revision.
 * 			- APIERR_GENERAL - Couldn't get the changes.
 * @remarks You are able to get changes contained by the given document revision.
 */
__APIEXPORT GSErrCode ACAPI_Revision_GetRVMDocumentRevisionChanges (const API_Guid* revisionGuid, GS::Array<API_RVMChange>* api_changes);


/**
 * @brief Retrieves the change IDs of the given elem identified by GUID.
 * @ingroup Revision
 * @param elemGuid GUID of the element.
 * @param api_changeIds The array of the change IDs.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - elemGuid or api_changeIds is nullptr.
 * 			- APIERR_BADID - elemGuid does not identify a valid element.
 * 			- APIERR_GENERAL - Couldn't get the change IDs.
 * @remarks You are able to get change IDs of the given element.
 */
__APIEXPORT GSErrCode ACAPI_Revision_GetRVMElemChangeIds (const API_Guid* elemGuid, GS::Array<GS::UniString>* api_changeIds);


/**
 * @brief Retrieves the issue in which the given change is issued at first.
 * @ingroup Revision
 * @param api_changeId ID of the change.
 * @param api_firstIssue The first issue in which the given change is issued.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - api_changeId or api_firstIssue is nullptr.
 * 			- APIERR_BADID - api_changeId does not identify a valid change.
 * 			- APIERR_GENERAL - Couldn't get the first issue.
 * @remarks You are able to get the first issue that the given GS::UniString identified change is issued in.
 */
__APIEXPORT GSErrCode ACAPI_Revision_GetRVMChangeFirstIssue (const GS::UniString* api_changeId, API_RVMIssue* api_firstIssue);


/**
 * @brief Returns the compound info string of the given element.
 * @ingroup Element
 * @param elementGuid [in] the Guid of the element
 * @param infoString [out] the info string of the element
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - any of the parameters is nullptr
 * 			- APIERR_BADID - no element found by the specified Guid
 * 			- APIERR_BADELEMENTTYPE - element has no info string
 */
__APIEXPORT GSErrCode ACAPI_Element_GetElementInfoString (const API_Guid* elementGuid, GS::UniString* infoString);


/**
 * @brief Changes the compound info string of the given element.
 * @ingroup Element
 * @param elementGuid [in] the Guid of the element
 * @param infoString [in] the info string of the element
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - any of the parameters is nullptr
 * 			- APIERR_BADID - no element found by the specified Guid
 * 			- APIERR_BADELEMENTTYPE - element has no info string
 */
__APIEXPORT GSErrCode ACAPI_Element_ChangeElementInfoString (const API_Guid* elementGuid, const GS::UniString* infoString);


/**
 * @brief Returns the array of categories.
 * @ingroup Category
 * @param categoryList [out] The array of categories.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - categoryList is nullptr.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Category_GetElementCategories-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Category_GetElementCategories (GS::Array<API_ElemCategory>* categoryList);


/**
 * @brief Returns the array of category values in the given category.
 * @ingroup Category
 * @param category [in] The category identified by guid or categoryID.
 * @param categoryValueList [out] The array of category values.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - categoryList is nullptr.
 * 			- APIERR_BADID - Incorrect category was specified (bad guid and categoryID).
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Category_GetElementCategoryValues-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Category_GetElementCategoryValues (const API_ElemCategory* category, GS::Array<API_ElemCategoryValue>* categoryValueList);


/**
 * @brief Registers a new window validator for the given guid.
 * @ingroup Database
 * @param pValidatorInfo Contains the guid of a window which will be the owner of the new validator and an element and checksum list to track their changes.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - pValidatorInfo is nullptr
 * 			- APIERR_MEMFULL - Not enough memory to complete the operation.
 * 			- APIERR_GENERAL - There is already a validator registered for this guid.
 */
__APIEXPORT GSErrCode ACAPI_Database_BuildWindowValidator (const API_WindowValidatorInfo* pValidatorInfo);


/**
 * @brief Destroys an already registered validator for the given guid.
 * @ingroup Database
 * @param pGuid The guid of the owner window of the validator.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - pValidatorInfo is nullptr
 * 			- APIERR_MEMFULL - Not enough memory to complete the operation.
 * 			- APIERR_GENERAL - There is no validator registered for this guid.
 */
__APIEXPORT GSErrCode ACAPI_Window_DestroyWindowValidator (const API_Guid* pGuid);


/**
 * @brief Cheks the already added list of elements and checksums form the validator (identified by the guid) against the lists from the parameter if there was any changes.
 * @ingroup Database
 * @param pValidatorInfo Contains the guid of a window which is the owner of the validator and the current, and the element and checksum list to check against.
 * @param pContentChanged Out paramter for the result. true if there was a change false otherwise.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - pValidatorInfo or pContentChanged is nullptr
 * 			- APIERR_MEMFULL - Not enough memory to complete the operation.
 * 			- APIERR_GENERAL - There is no validator registered for this guid.
 * @remarks This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_Database_CheckWindowValidator (const API_WindowValidatorInfo* pValidatorInfo, bool* pContentChanged);


/**
 * @brief Sets the element and checksum list for an already added validator with given guid.
 * @ingroup Database
 * @param pValidatorInfo Contains the guid of a window which is the owner of the validator and the new element and checksum list.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - pValidatorInfo is nullptr
 * 			- APIERR_MEMFULL - Not enough memory to complete the operation.
 * 			- APIERR_GENERAL - There is no validator registered for this guid.
 * @remarks This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_Database_RebuildWindowValidator (const API_WindowValidatorInfo* pValidatorInfo);


/**
 * @brief Changes the guid of a previously registered window. Useful when replacing already opened windows by reusing their window object.
 * @ingroup Window
 * @param pOldGuid Guid of an existing window to be replaced with the new one.
 * @param pNewGuid Guid of a non-existing window to replace the old one.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - pOldGuid or pNewGuid is nullptr
 * 			- APIERR_WINDNOTEXIST - No window found with the given guid.
 * 			- APIERR_WINDEXIST - There is a window already registered with the new guid.
 * 			- APIERR_GENERAL - Any other unexpected error
 * @remarks If there is a content validator associated with the old guid, this function will delete it.
 * 			This function only works if the window's type is either @c APIWind_MyDrawID or @c APIWind_MyTextID.
 */
__APIEXPORT GSErrCode ACAPI_Window_SetWindowId (const API_Guid* pOldGuid, const API_Guid* pNewGuid);


/**
 * @brief Helper function to call various functions inside Archicad.
 * @ingroup Database
 * @param query The request towards Archicad
 * @param result The answer from Archicad
 * @return
 * 			- NoError - The function has completed with success.
 * 			- Other error code - `query` is invalid.
 * @remark The following queries/commands are available:
 * 		   | Query | Result |
 * 		   |-------|--------|
 * 		   | "getTopWindow" | The title of the top window. |
 * 		   | "lineConsolidation" | Calls the Line Consolidation menu command. |
 * 		   | "fillNormalization" | Calls the Fill Consolidation menu command. |
 * 		   | "usedAttributes" | Returns the list of used attributes. |
 * 		   | "numberOfTraceReferences" | Returns the number of trace references. |
 */
__APIEXPORT GSErrCode ACAPI_Database_JsonQuery (const GS::UniString *query, GS::UniString *result);


/**
 * @brief Helper function to collect all Archicad databases of the given type.
 * @ingroup Database
 * @param id The database type to collect.
 * @return A list of database idetifiers for the given type, or any empty list if no such databases exist in the current project.
 */
__APIEXPORT GS::Array<API_DatabaseUnId> ACAPI_Database_GetDatabasesForType (const API_DatabaseTypeID& id);


/**
 * @brief Helper function to collect all Archicad databases of the given types.
 * @ingroup Database
 * @param ids List of database types to collect.
 * @return A list of database idetifiers for the given types, or any empty list if no such databases exist in the current project.
 */
__APIEXPORT GS::Array<API_DatabaseUnId> ACAPI_Database_GetDatabasesForTypes (const GS::Array<API_DatabaseTypeID>& ids);


/**
 * @brief Retrieves the 3D default levels for the construction elems.
 * @ingroup ProjectSetting
 * @since Archicad 26
 * @param elemTypes [in] The elem types for which you want to obtain the 3D default levels.
 * @param levels [out] The 3D default levels for the elem types given in the elemIDs array.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks Retrieves the 3D default levels for the types passed in the elemIDs array. Possible elem types:
 * 			Wall, Column, Beam, Symbol, Light, Slab, Roof, Mesh.
 */
__APIEXPORT GSErrCode ACAPI_ProjectSetting_GetLast3DDefLevels (const GS::Array<API_ElemType> &elemTypes,
															   GS::Array<double>			 &levels);


/**
 * @brief Sets the 3D default levels for the passed construction element types.
 * @ingroup ProjectSetting
 * @since Archicad 26
 * @param elemTypes [in] Elem types for which you want to set the 3D default levels.
 * @param levels [in] The default 3D level values.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The size of elemTypes differes from the size of levels.
 * @remarks Sets the 3D default levels for the given elemtypes. Possible elemtypes: Wall, Column, Beam,
 * 			Symbol, Light, Slab, Roof, Mesh.
 */
__APIEXPORT GSErrCode ACAPI_ProjectSetting_SetLast3DDefLevels (const GS::Array<API_ElemType> &elemTypes,
															   const GS::Array<double>		&levels);


#endif // ACAPI_DATABASE_H