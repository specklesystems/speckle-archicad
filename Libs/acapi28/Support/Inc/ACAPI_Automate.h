#ifndef ACAPIAUTOMATE_H
#define	ACAPIAUTOMATE_H

// GSRoot
#include "GSRoot.hpp"
#include "Array.hpp"
#include "Location.hpp"

// own
#include "APICalls.h"
#include "APIdefs.h"


/**
 * @brief Opens a new plan.
 * @ingroup ProjectOperation
 * @param newProjectPars [in] Parameters for opening a new project.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - newplanPars is nullptr
 * 			- APIERR_REFUSEDCMD - the function is called from notification level
 * @remarks This function is used to perform a New or a New and reset command in the server application.
 * 			It cannot be called from notification level; the command is refused if other addons are running. Calling this function may notify other addons on the event. The caller addon does not get any notification. See the Notification Manager for further details.
 * 			This function performs complete operations, so it cannot be called neither during undoable operations nor during non-undoable commands. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ProjectOperation_NewProject-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ProjectOperation_NewProject (const API_NewProjectPars* newProjectPars);


/**
 * @brief Opens a new project file.
 * @ingroup ProjectOperation
 * @param fileOpenPars [in] Parameters for opening a project file.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - openPars or openPars->file is nullptr, or openPars->file is not a valid location, or openPars->archiveLib is nullptr if openPars->libGiven is true
 * 			- APIERR_BADID - openPars->fileTypeID is unknown file type
 * @remarks This function is used to open an existing project file.
 * 			It cannot be called from notification level; the command is refused if other addons are running. Calling this function may notify other addons on the event. The caller addon does not get any notification. See the Notification Manager for further details.
 * 			This function performs complete operations, so it cannot be called neither during undoable operations nor during non-undoable commands. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ProjectOperation_Open-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ProjectOperation_Open (const API_FileOpenPars* fileOpenPars);


/**
 * @brief Closes the current project window.
 * @ingroup ProjectOperation
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_REFUSEDCMD - The command is not allowed to call.
 * 			- APIERR_NOPLAN - No open project.
 * @remarks This function is used to perform a Close command in the server application.
 * 			It cannot be called from notification level; the command is refused if other addons are running. Calling this function may notify other addons on the event. The caller addon does not get any notification. See the Notification Manager for further details.
 * 			This function performs complete operations, so it cannot be called neither during undoable operations nor during non-undoable commands. See more details on this topic at Command Overview.
 * 			Not for public usage.
 */
__APIEXPORT GSErrCode ACAPI_ProjectOperation_Close ();


/**
 * @brief Saves the content of the current window in different file formats.
 * @ingroup ProjectOperation
 * @since Archicad 25
 * @return
 * 			- NoError - The function has completed with success
 * 			- APIERR_REFUSEDCMD - The function is called from notification level, or you are running a demo version of Archicad
 * 			- APIERR_READONLY - The plan could not be saved either because it's open in read-only mode, or has never been saved to a file and the fileSavePars is nullptr.
 * @remarks This function is used to save the content of the current window in different file formats. This may change in case of @ref API_SavePars_Pdf>.
 * 			It cannot be called from notification level; the command is refused if other addons are running. Calling this function may notify other addons on the event. The caller addon does not get any notification. See the Notification Manager for further details.
 * 			It cannot be called in the demo version of Archicad either, because the API tries to mimic the behavior of the host system.
 * 			This function performs complete operations, so it cannot be called neither during undoable operations nor during non-undoable commands. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_ProjectOperation_Save ();


/**
 * @brief Saves the content of the current window in different file formats.
 * @ingroup ProjectOperation
 * @since Archicad 25
 * @param fileSavePars [in] Parameters of the saved file; optional, if not passed default settings will be used
 * @return
 * 			- NoError - The function has completed with success
 * 			- APIERR_REFUSEDCMD - The function is called from notification level, or you are running a demo version of Archicad
 * 			- APIERR_READONLY - The plan could not be saved either because it's open in read-only mode, or has never been saved to a file and the fileSavePars is nullptr.
 * @remarks This function is used to save the content of the current window in different file formats. This may change in case of @ref API_SavePars_Pdf>.
 * 			It cannot be called from notification level; the command is refused if other addons are running. Calling this function may notify other addons on the event. The caller addon does not get any notification. See the Notification Manager for further details.
 * 			It cannot be called in the demo version of Archicad either, because the API tries to mimic the behavior of the host system.
 * 			This function performs complete operations, so it cannot be called neither during undoable operations nor during non-undoable commands. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_ProjectOperation_Save (const API_FileSavePars* fileSavePars);


/**
 * @brief Saves the content of the current window in different file formats.
 * @ingroup ProjectOperation
 * @since Archicad 25
 * @param fileSavePars [in] Parameters of the saved file; optional, if not passed default settings will be used
 * @param formatPars [in] Parameters of the requested format. It can be either @ref API_SavePars_Archive, @ref API_SavePars_Ifc, @c API_SavePars_Plandump, @ref API_SavePars_Object, @ref API_SavePars_Picture, @ref API_SavePars_Pdf or an @ref API_SavePars_Saf record.
 * @return
 * 			- NoError - The function has completed with success
 * 			- APIERR_REFUSEDCMD - The function is called from notification level, or you are running a demo version of Archicad
 * 			- APIERR_READONLY - The plan could not be saved either because it's open in read-only mode, or has never been saved to a file and the fileSavePars is nullptr.
 * @remarks This function is used to save the content of the current window in different file formats. This may change in case of @ref API_SavePars_Pdf>.
 * 			It cannot be called from notification level; the command is refused if other addons are running. Calling this function may notify other addons on the event. The caller addon does not get any notification. See the Notification Manager for further details.
 * 			It cannot be called in the demo version of Archicad either, because the API tries to mimic the behavior of the host system.
 * 			This function performs complete operations, so it cannot be called neither during undoable operations nor during non-undoable commands. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_ProjectOperation_Save (const API_FileSavePars* fileSavePars, const API_SavePars_Archive* formatPars);


/**
 * @brief Saves the content of the current window in different file formats.
 * @ingroup ProjectOperation
 * @since Archicad 25
 * @param fileSavePars [in] Parameters of the saved file; optional, if not passed default settings will be used
 * @param formatPars [in] Parameters of the requested format. It can be either @ref API_SavePars_Archive, @ref API_SavePars_Ifc, @c API_SavePars_Plandump, @ref API_SavePars_Object, @ref API_SavePars_Picture, @ref API_SavePars_Pdf or an @ref API_SavePars_Saf record.
 * @return
 * 			- NoError - The function has completed with success
 * 			- APIERR_REFUSEDCMD - The function is called from notification level, or you are running a demo version of Archicad
 * 			- APIERR_READONLY - The plan could not be saved either because it's open in read-only mode, or has never been saved to a file and the fileSavePars is nullptr.
 * @remarks This function is used to save the content of the current window in different file formats. This may change in case of @ref API_SavePars_Pdf>.
 * 			It cannot be called from notification level; the command is refused if other addons are running. Calling this function may notify other addons on the event. The caller addon does not get any notification. See the Notification Manager for further details.
 * 			It cannot be called in the demo version of Archicad either, because the API tries to mimic the behavior of the host system.
 * 			This function performs complete operations, so it cannot be called neither during undoable operations nor during non-undoable commands. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_ProjectOperation_Save (const API_FileSavePars* fileSavePars, const API_SavePars_PlanDump* formatPars);


/**
 * @brief Saves the content of the current window in different file formats.
 * @ingroup ProjectOperation
 * @since Archicad 25
 * @param fileSavePars [in] Parameters of the saved file; optional, if not passed default settings will be used
 * @param formatPars [in] Parameters of the requested format. It can be either @ref API_SavePars_Archive, @ref API_SavePars_Ifc, @c API_SavePars_Plandump, @ref API_SavePars_Object, @ref API_SavePars_Picture, @ref API_SavePars_Pdf or an @ref API_SavePars_Saf record.
 * @return
 * 			- NoError - The function has completed with success
 * 			- APIERR_REFUSEDCMD - The function is called from notification level, or you are running a demo version of Archicad
 * 			- APIERR_READONLY - The plan could not be saved either because it's open in read-only mode, or has never been saved to a file and the fileSavePars is nullptr.
 * @remarks This function is used to save the content of the current window in different file formats. This may change in case of @ref API_SavePars_Pdf>.
 * 			It cannot be called from notification level; the command is refused if other addons are running. Calling this function may notify other addons on the event. The caller addon does not get any notification. See the Notification Manager for further details.
 * 			It cannot be called in the demo version of Archicad either, because the API tries to mimic the behavior of the host system.
 * 			This function performs complete operations, so it cannot be called neither during undoable operations nor during non-undoable commands. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_ProjectOperation_Save (const API_FileSavePars* fileSavePars, const API_SavePars_Object* formatPars);


/**
 * @brief Saves the content of the current window in different file formats.
 * @ingroup ProjectOperation
 * @since Archicad 25
 * @param fileSavePars [in] Parameters of the saved file; optional, if not passed default settings will be used
 * @param formatPars [in] Parameters of the requested format. It can be either @ref API_SavePars_Archive, @ref API_SavePars_Ifc, @c API_SavePars_Plandump, @ref API_SavePars_Object, @ref API_SavePars_Picture, @ref API_SavePars_Pdf or an @ref API_SavePars_Saf record.
 * @return
 * 			- NoError - The function has completed with success
 * 			- APIERR_REFUSEDCMD - The function is called from notification level, or you are running a demo version of Archicad
 * 			- APIERR_READONLY - The plan could not be saved either because it's open in read-only mode, or has never been saved to a file and the fileSavePars is nullptr.
 * @remarks This function is used to save the content of the current window in different file formats. This may change in case of @ref API_SavePars_Pdf>.
 * 			It cannot be called from notification level; the command is refused if other addons are running. Calling this function may notify other addons on the event. The caller addon does not get any notification. See the Notification Manager for further details.
 * 			It cannot be called in the demo version of Archicad either, because the API tries to mimic the behavior of the host system.
 * 			This function performs complete operations, so it cannot be called neither during undoable operations nor during non-undoable commands. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ProjectOperation_Save_Pic-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ProjectOperation_Save (const API_FileSavePars* fileSavePars, const API_SavePars_Picture* formatPars);


/**
 * @brief Saves the content of the current window in different file formats.
 * @ingroup ProjectOperation
 * @since Archicad 25
 * @param fileSavePars [in] Parameters of the saved file; optional, if not passed default settings will be used
 * @param formatPars [in] Parameters of the requested format. It can be either @ref API_SavePars_Archive, @ref API_SavePars_Ifc, @c API_SavePars_Plandump, @ref API_SavePars_Object, @ref API_SavePars_Picture, @ref API_SavePars_Pdf or an @ref API_SavePars_Saf record.
 * @param resultData [out] Parameter for output data. Optionally it can be an @ref API_IFCRelationshipData pointer while saving IFC.
 * @return
 * 			- NoError - The function has completed with success
 * 			- APIERR_REFUSEDCMD - The function is called from notification level, or you are running a demo version of Archicad
 * 			- APIERR_READONLY - The plan could not be saved either because it's open in read-only mode, or has never been saved to a file and the fileSavePars is nullptr.
 * @remarks This function is used to save the content of the current window in different file formats. This may change in case of @ref API_SavePars_Pdf>.
 * 			It cannot be called from notification level; the command is refused if other addons are running. Calling this function may notify other addons on the event. The caller addon does not get any notification. See the Notification Manager for further details.
 * 			It cannot be called in the demo version of Archicad either, because the API tries to mimic the behavior of the host system.
 * 			This function performs complete operations, so it cannot be called neither during undoable operations nor during non-undoable commands. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_ProjectOperation_Save (const API_FileSavePars* fileSavePars, const API_SavePars_Ifc* formatPars, API_IFCRelationshipData* resultData = nullptr);


/**
 * @brief Saves the content of the current window in different file formats.
 * @ingroup ProjectOperation
 * @since Archicad 25
 * @param fileSavePars [in] Parameters of the saved file; optional, if not passed default settings will be used
 * @param formatPars [in] Parameters of the requested format. It can be either @ref API_SavePars_Archive, @ref API_SavePars_Ifc, @c API_SavePars_Plandump, @ref API_SavePars_Object, @ref API_SavePars_Picture, @ref API_SavePars_Pdf or an @ref API_SavePars_Saf record.
 * @return
 * 			- NoError - The function has completed with success
 * 			- APIERR_REFUSEDCMD - The function is called from notification level, or you are running a demo version of Archicad
 * 			- APIERR_READONLY - The plan could not be saved either because it's open in read-only mode, or has never been saved to a file and the fileSavePars is nullptr.
 * @remarks This function is used to save the content of the current window in different file formats. This may change in case of @ref API_SavePars_Pdf>.
 * 			It cannot be called from notification level; the command is refused if other addons are running. Calling this function may notify other addons on the event. The caller addon does not get any notification. See the Notification Manager for further details.
 * 			It cannot be called in the demo version of Archicad either, because the API tries to mimic the behavior of the host system.
 * 			This function performs complete operations, so it cannot be called neither during undoable operations nor during non-undoable commands. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_ProjectOperation_Save (const API_FileSavePars* fileSavePars, const API_SavePars_Pdf* formatPars);


/**
 * @brief Saves the content of the current window in different file formats.
 * @ingroup ProjectOperation
 * @since Archicad 25
 * @param fileSavePars [in] Parameters of the saved file; optional, if not passed default settings will be used
 * @param formatPars [in] Parameters of the requested format. It can be either @ref API_SavePars_Archive, @ref API_SavePars_Ifc, @c API_SavePars_Plandump, @ref API_SavePars_Object, @ref API_SavePars_Picture, @ref API_SavePars_Pdf or an @ref API_SavePars_Saf record.
 * @return
 * 			- NoError - The function has completed with success
 * 			- APIERR_REFUSEDCMD - The function is called from notification level, or you are running a demo version of Archicad
 * 			- APIERR_READONLY - The plan could not be saved either because it's open in read-only mode, or has never been saved to a file and the fileSavePars is nullptr.
 * @remarks This function is used to save the content of the current window in different file formats. This may change in case of @ref API_SavePars_Pdf>.
 * 			It cannot be called from notification level; the command is refused if other addons are running. Calling this function may notify other addons on the event. The caller addon does not get any notification. See the Notification Manager for further details.
 * 			It cannot be called in the demo version of Archicad either, because the API tries to mimic the behavior of the host system.
 * 			This function performs complete operations, so it cannot be called neither during undoable operations nor during non-undoable commands. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_ProjectOperation_Save (const API_FileSavePars* fileSavePars, const API_SavePars_Saf* formatPars);


/**
 * @brief Resets and loads the active libraries.
 * @ingroup ProjectOperation
 * @ingroup LibraryManagement
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function is used to perform a Reload Libraries command in the server application.
 * 			All the active libraries (included the BIMcloud and BIM Server Libraries too) will be reloaded.
 */
__APIEXPORT GSErrCode ACAPI_ProjectOperation_ReloadLibraries ();


/**
 * @brief Prints the content of the current window.
 * @ingroup ProjectOperation
 * @param printPars [in] Control parameters; optional, if missing, the current defaults will be used
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_REFUSEDCMD - The function is called from notification level
 * 			- APIERR_NOPLAN - No open project
 * 			- APIERR_BADPARS - printPars contains invalid data
 * @remarks This function is used to print the content of the current window. This function performs a Print command in the server application.
 * 			To get more details on the parametrization refer to the @ref API_PrintPars structure.
 * 			It cannot be called from notification level; the command is refused if other addons are running. Calling this function may notify other addons about the event. The caller addon does not get any notification. See the Notification Manager for further details.
 * 			This function performs complete operations, so it cannot be called neither during undoable operations nor during non-undoable commands. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ProjectOperation_Print-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ProjectOperation_Print (const API_PrintPars* printPars = nullptr);


/**
 * @brief Terminates the server application.
 * @ingroup ProjectOperation
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_REFUSEDCMD - the function is called from notification level
 * @remarks This function is used to terminate the server application.
 * 			It cannot be called from notification level; the command is refused if other addons are running. Calling this function may notify other addons on the event. The caller addon does not get any notification. See the Notification Manager for further details.
 * 			This function performs complete operations, so it cannot be called neither during undoable operations nor during non-undoable commands. See more details on this topic at Command Overview.
 * 			Not for public usage.
 */
__APIEXPORT GSErrCode ACAPI_ProjectOperation_Quit ();


/**
 * @brief Redraws the content of the current window.
 * @ingroup View
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOPLAN - no open project
 * 			- APIERR_BADDATABASE - the current window and the active database are not in synchrony
 * @remarks This function is used to redraw the content of the current (front) window.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_View_Redraw-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_View_Redraw ();


/**
 * @brief Rebuilds the content of the current window.
 * @ingroup View
 * @param doRebuildAndRegenerate [in] Performs a rebuild and regenerate operation instead of a simple rebuild. Optional; considered false (i.e. rebuild only) if omitted.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOPLAN - no open project
 * 			- APIERR_BADDATABASE - the current window and the active database don't match
 * @remarks This function is used to rebuild the content of the current (front) window. The effect is the same as if the user chose the Rebuild menu command with or without holding the Option (Alt) key.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_View_Rebuild-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_View_Rebuild (bool* doRebuildAndRegenerate = nullptr);


/**
 * @brief Performs a zoom operation.
 * @ingroup View
 * @param zoomBox [in] The box to zoom in (optional parameter, can be nullptr)
 * @param zoomRect [in] Zoom rectangle (optional parameter, alternative of zoomBox, can be nullptr)
 * @param tranmat [in] Transformation matrix (optional parameter)
 * @return
 * 			- NoError - The function has completed with success
 * 			- APIERR_NOPLAN - There is no open project
 * 			- APIERR_BADDATABASE - The active database is not the top window
 * 			- APIERR_BADPARS - The passed zoomBox is incorrect (empty box) or zoomRect is too small
 * @remarks This function performs a zoom or a fit in window operation on the front window, and rebuilds it.
 * 			If the zoomBox parameter is passed, the given zoom factor will be set up. Alternatively you can pass a rectangle to define the zoom in pixel coordinates. If both parameters are nullptr, a Fit In Window command will be executed.
 * 			To set the zoom box of a 2D drawing type window without rebuilding the database, use the @ref ACAPI_View_SetZoom database function. You can retrieve the current zoom box of a 2D drawing type window with @ref ACAPI_View_GetZoom.
 * 			If the top window is the 3D model window, only the zoomRect parameter is considered. You can retrieve the current window size with the @ref ACAPI_View_Get3DWindowSets environment function.
 * 			You can also modify the zoom of the 3D model window with the @ref ACAPI_View_Change3DWindowSets environment function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_View_Zoom-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_View_Zoom (API_Box* zoomBox = nullptr, API_Rect* zoomRect = nullptr, API_Tranmat* tranmat = nullptr);


/**
 * @brief Zooming to the actual selection. (Even in 3D.)
 * @ingroup View
 * @return
 * 			- NoError - The function has completed with success.
 */
__APIEXPORT GSErrCode ACAPI_View_ZoomToSelected ();


/**
 * @brief Zoom to the given elements.
 * @ingroup View
 * @param elemsToZoom [in] Zoom to these elements (cannot be nullptr.
 * @return
 * 			- APIERR_BADPARS - The elementsToZoom parameter is nullptr.
 * 			- NoError - The function has completed with success, or you passed an empty element array.
 * @remarks The function works both in the 2D and 3D window.
 */
__APIEXPORT GSErrCode ACAPI_View_ZoomToElements (const GS::Array<API_Guid>* elemsToZoom);


/**
 * @brief Changes the current (active) window.
 * @ingroup Window
 * @param windowInfo [in] The identification parameters of the requested front window
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - windowInfo is nullptr.
 * 			- APIERR_NOPLAN - There is no any project opened.
 * 			- APIERR_BADWINDOW - the requested front window is invalid
 * @remarks This function is used to change the front window of the server application. It performs the same operation as you click the appropriate menu item in the Window menu.
 * 			Generally the current window and the window of the current database are the same. However you must be careful; the database dependent functions work on the current database instead of the database of the current window. The interface functions work on the current window always.
 * 			Note, that this function changes the current database also.
 * 			This function is very useful to access the database of a section/elevation and detail window if the @ref ACAPI_Database_ChangeCurrentDatabase function has been failed. It occurs when the section or detail window was not opened any time since the actual project has been opened; the database is not available since it is not regenerated. Once the user switch to the section or detail window, the database becomes available.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Window_ChangeWindow-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Window_ChangeWindow (const API_WindowInfo* windowInfo);


/**
 * @brief Switches to the given navigator view.
 * @ingroup View
 * @param viewGuidStr [in] string representation of the GUID of the navigator view to be generated
 * @return
 * 			- NoError - the function has completed with success
 * 			- APIERR_BADPARS - viewGuidStr is nullptr, or not a valid GUID
 * 			- APIERR_BADID - no view found with the specified GUID
 * 			- APIERR_GENERAL - failed to generate the view
 * @remarks This function simulates the action when you open a view from the Project Navigator.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_View_GoToView-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_View_GoToView (const char* viewGuidStr);


/**
 * @brief Creates a photorealistic image of the 3D window.
 * @ingroup Rendering
 * @param photoRenderPars [in] Parameters for saving the photorendered picture into image file
 *
 * @param printPars [in] Printing options for producing printed output of the photorendered picture. Optional parameter, can be nullptr
 *
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE - The current database does not match the current window
 * 			- APIERR_BADPARS - Either the rendPars parameter is nullptr
 * @remarks This function is used to generate the photorendered image of the current 3D window, and save the picture into an image file
 * 			defined in `rendPars`. The picture window will be closed automatically before the function returns. You can also print the rendered
 * 			picture to the default printer if the `printPars` parameter is not `nullptr`. If you need printed output only, set the `fileTypeID`
 * 			field of rendPars to @c APIFType_None.
 * 			The photorendering settings can be accessed with the @ref ACAPI_Rendering_GetRenderingSets and @ref ACAPI_Rendering_ChangeRenderingSets
 * 			functions.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Rendering_PhotoRender-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Rendering_PhotoRender (const API_PhotoRenderPars* photoRenderPars, const API_PrintPars* printPars = nullptr);


/**
 * @brief Saves the selected elements into a module file.
 * @ingroup ProjectOperation
 * @param location [in] Specifies the module file to be saved
 * @param elemHead [in] Elements to save into the module. Optional parameter, can be nullptr - in this case the current selection is saved
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADDATABASE - The current database must be floor plan, section/elevation or detail type
 * 			- APIERR_BADPARS - The fileSpec parameter is nullptr or the file specified by fileSpec cannot be registered
 * 			- APIERR_BADINDEX - There were no valid elements passed in the elemHead parameter
 * 			- APIERR_GENERAL - Cannot create or write the module file
 * 			- APIERR_MEMFULL - Low memory condition
 * @remarks This function is used to create a module file from a selection of elements. The elements that the module should contain can be passed in the elemHead handle. If this parameter is nullptr, the function uses the current selection, similarly to the 'Save Selection as Module' menu command. The module file will not be created if there are no valid elements to save. Do not forget to release the elemHead handle when not needed any more.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ProjectOperation_SaveAsModuleFile-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ProjectOperation_SaveAsModuleFile (const IO::Location* location, GS::Array<API_Elem_Head>* elemHead = nullptr);


/**
 * @brief Publishes a publisher set.
 * @ingroup ProjectOperation
 * @param publishPars [in] Control parameters; the guid member identifies the set to be published.
 * @param selectedLinks [in] Optional parameter; publish only these items.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_REFUSEDCMD - The function is called from notification level.
 * 			- APIERR_BADINDEX - The guid in publishPars is invalid.
 * 			- APIERR_BADPARS - publishPars is nullptr, or no open project.
 * @remarks This function publishes the given publisher set.
 * 			To get more details on the parametrization refer to the @ref API_PublishPars structure.
 * 			This function performs complete operations, so it cannot be called neither during undoable operations nor during non-undoable commands. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ProjectOperation_Publish-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ProjectOperation_Publish (const API_PublishPars* publishPars, const GS::Array<API_Guid>* selectedLinks = nullptr);


/**
 * @brief Opens the given library part in the Library Part Editor window.
 * @ingroup LibraryManagement
 * @ingroup Dialog
 * @param libPartToOpen [in] Identifies the library part to open.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed library part information is incorrect.
 * @remarks First it tries to open by the document name, then the file name (which may come from the location).
 */
__APIEXPORT GSErrCode ACAPI_LibraryManagement_OpenLibraryPart (const API_OpenLibPartInfo *libPartToOpen);


#endif