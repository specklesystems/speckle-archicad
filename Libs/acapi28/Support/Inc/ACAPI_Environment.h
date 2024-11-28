#ifndef ACAPI_ENVIRONMENT_H
#define	ACAPI_ENVIRONMENT_H

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

namespace GDL {
	class Parameters;
}


/**
 * @brief Returns information about the current application.
 * @ingroup AddOnIdentification
 * @param serverApplicationInfo [out] Information about the server application. Contains the main and maintenance release number of the server application.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - the serverInfo is nullptr.
 * @remarks This function is used to get that the add-on is currently running in Archicad or the 3D Engine.
 * 			The returned serverInfo->serverApplication value can be:
 * 			- @c APIAppl_ArchiCADID : add-on is currently running in Archicad.
 */
__APIEXPORT GSErrCode ACAPI_AddOnIdentification_Application (API_ServerApplicationInfo* serverApplicationInfo);


/**
 * @brief Returns information on the current project file.
 * @ingroup ProjectOperation
 * @param projectInfo [out] Project file and teamwork project specific data.
 * @return
 * 			- NoError - No error occurred.
 * 			- APIERR_BADPARS - projectInfo is nullptr.
 * 			- APIERR_NOPLAN - No open project.
 * 			- APIERR_MEMFULL - Low memory condition.
 * @remarks This function is used to get information on the project file. In teamwork mode, the teamwork related data are also available. See the definitions of the returned parameters at @ref API_ProjectInfo.
 * 			The file specification is available only if the project file has been saved before. For 'untitled' project no data is returned.
 * 			The dynamic memory allocated by this function will be deleted in the destructor of the @ref API_ProjectInfo structure.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ProjectOperation_Project-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ProjectOperation_Project (API_ProjectInfo* projectInfo);


/**
 * @brief Returns the project sharing data in the case of a TeamWork project.
 * @ingroup Teamwork
 * @ingroup ProjectOperation
 * @param sharingInfo data of the registered members of the team project
 * @return
 * 			- NoError - The function completed with success.
 * 			- APIERR_BADPARS - sharingInfo is nullptr.
 * 			- APIERR_NOPLAN - sharingInfo is nullptr.
 * 			- APIERR_MEMFULL - Low memory condition.
 * @remarks This function is used to get the registered members of the opened team project. Member data are returned through an array of @ref API_UserInfo records.
 * 			Do not forget to dispose the member data handle if it is not needed any more.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Teamwork_ProjectSharing-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Teamwork_ProjectSharing (API_SharingInfo* sharingInfo);


/**
 * @brief Returns information about the 'Project Info' dialog.
 * @ingroup ProjectSetting
 * @param projectNoteInfo [out] project note data
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - projectNoteInfo is nullptr
 * 			- APIERR_NOPLAN - There are no project loaded.
 * @remarks This function is used to get the project info parameters. It can be set in the 'Project Info...' dialog box in the File/Info menu.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ProjectSetting_GetProjectNotes-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ProjectSetting_GetProjectNotes (API_ProjectNoteInfo* projectNoteInfo);


/**
 * @brief Changes the data of the 'Project Info' dialog.
 * @ingroup ProjectSetting
 * @param projectNoteInfo [in] project note data
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - noteInfo is nullptr
 * 			- APIERR_NOPLAN - There are no project loaded.
 * @remarks This function is used to change the project info parameters. It can be set in the 'Project Info...' dialog box in the File/Info menu.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ProjectSetting_ChangeProjectNotes-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ProjectSetting_ChangeProjectNotes (API_ProjectNoteInfo* projectNoteInfo);


/**
 * @brief Returns the list of loaded libraries.
 * @ingroup LibraryManagement
 * @param activeLibs the active library list
 * @param embeddedLibraryIndex [out] optional; the 0-based index of the embedded library in this list
 * @return
 * 			- NoError - The function completed with success.
 * 			- APIERR_BADPARS - activeLibs is nullptr.
 * 			- APIERR_MEMFULL - Low memory condition.
 * @remarks This function is used to get the list of active libraries of Archicad. Refer to the @ref API_LibraryInfo for further details.
 * 			For linked BIMcloud or BIM Server Libraries the location of local library cache will be returned.
 * 			To change the active libraries use the @ref ACAPI_LibraryManagement_SetLibraries function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryManagement_GetLibraries-Example-Snippet
 * @warning *Legacy function - to be deleted in future versions, use ACAPI::Library::LibraryManager::FindLibraries instead*
 */
__APIEXPORT GSErrCode ACAPI_LibraryManagement_GetLibraries (GS::Array<API_LibraryInfo>* activeLibs, Int32* embeddedLibraryIndex = nullptr);


/**
 * @brief Changes the list of loaded libraries.
 * @ingroup LibraryManagement
 * @param activeLibs the active library list to set
 * @return
 * 			- NoError - The function completed with success.
 * 			- APIERR_BADPARS - activeLibs is nullptr or size of the internal locations handle is not match to nLib
 * 			- APIERR_NOTMINE - The project library list is not editable in Teamwork. You need to reserve it first.
 * @remarks This function is used to reset the list of active libraries of Archicad. The passed library folders will be enumerated. Refer to the @ref API_LibraryInfo for further details.
 * 			To get the active libraries use the @ref ACAPI_LibraryManagement_GetLibraries function.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryManagement_SetLibraries-Example-Snippet
 * @warning *Legacy function - to be deleted in future versions, use ACAPI::Library::LibraryManager::AddLibrary instead*
 */
__APIEXPORT GSErrCode ACAPI_LibraryManagement_SetLibraries (const GS::Array<API_LibraryInfo>* activeLibs);


/**
 * @brief Resets the loaded libraries.
 * @ingroup Dialog
 * @return
 * 			- NoError - The function completed with success.
 * 			- APIERR_NOTMINE - The project library list is not editable in Teamwork. You need to reserve it first.
 * @remarks All the currently selected libraries will go away. You can use this command to prepare for defining your own set of libraries.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @warning *Legacy function - to be deleted in future versions, use ACAPI::Library::LibraryManager::RemoveLibrary instead*
 */
__APIEXPORT GSErrCode ACAPI_LibraryManagement_ResetLibraries ();


/**
 * @brief Instructs the user to select a new library folder in a dialog.
 * @ingroup LibraryManagement
 * @param defName [in] A pointer to the default name of the new library.
 * @param newLib [out] The file system location of the selected folder.
 * @return
 * 			- NoError - The function completed with success.
 * 			- APIERR_BADPARS - any of the parameters are nullptr.
 * 			- APIERR_CANCEL - The user canceled the operation by the cancel button in the dialog.
 * @remarks If a library is created or selected, the file specification is returned in the second parameter.
 * 			To add a new folder to the active libraries use either the @ref ACAPI_LibraryManagement_AddLibraries or the @ref ACAPI_LibraryManagement_SetLibraries functions.
 * 			You may also use directly the base class `DG::FolderDialog` of the Dialog Manager instead of calling @ref ACAPI_LibraryManagement_NewLibDial.
 */
__APIEXPORT GSErrCode ACAPI_LibraryManagement_NewLibDial (char* defName, IO::Location* newLib);


/**
 * @brief Registers a new folder into the list of active libraries.
 * @ingroup LibraryManagement
 * @param newLib [in] The file system location of the folder to add.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - newLib is nullptr.
 * 			- APIERR_NOTMINE - The project library list is not editable in Teamwork. You need to reserve it first.
 * @remarks The registered folder will be the default one, which means that Library Parts created by the subsequent @ref ACAPI_LibraryPart_Create functions automatically will go into this library, unless an other folder is specified.
 * 			The modified list of active libraries will be enumerated.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * 			Note that BIM Server libraries cannot be added to the project with this function.
 * @warning *Legacy function - to be deleted in future versions, use ACAPI::Library::LibraryManager::AddLibrary instead*
 */
__APIEXPORT GSErrCode ACAPI_LibraryManagement_AddLibraries (IO::Location* newLib);


/**
 * @brief Checks the currently loaded libraries.
 * @ingroup LibraryManagement
 * @return
 * 			- NoError - Always returns NoError.
 * @remarks Check the active library folders for the required Library Parts. If any of them are missing, an alert is highlighted to inform the user.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_LibraryManagement_CheckLibraries ();


/**
 * @brief Sets the overwrite mode for the library part create function.
 * @ingroup LibraryManagement
 * @param overwriteOn [in] Switch ON or OFF the overwrite mode.
 * @return
 * 			- NoError - The function always returns NoError.
 * @remarks This function is used to configure the @ref ACAPI_LibraryPart_Create function to overwrite an existing library part instead of creating a new one with unique name.
 * 			The parameter should be pass as a value, instead of a pointer. See the example.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryManagement_OverwriteLibPart-Example-Snippet
 * @warning *Legacy function - to be deleted in future versions, use ACAPI::Library::GSMObject::CopyTo instead*
 */
__APIEXPORT GSErrCode ACAPI_LibraryManagement_OverwriteLibPart (bool overwriteOn);


/**
 * @brief This function is used to obtain the reference guid of a library part.
 * @ingroup LibraryPart
 * @param location [in] The location of the library part.
 * @param guid [out] The reference guid of the library part.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks The function is used to obtain the reference guid of a library part using the library part's location.
 * @warning *Legacy function - to be deleted in future versions, use ACAPI::Library::GSMObject::GetUnID instead*
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_GetLibPartRefGuid (const IO::Location* location, API_Guid* guid);


/**
 * @brief This function is used to obtain the given library part's own unique ID.
 * @ingroup LibraryPart
 * @param location [in] The location of the library part.
 * @param libPartUnId [out] The unique ID of the library part.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks The function is used to obtain the library part's own unique ID using the library part's
 * 			location.
 * @warning *Legacy function - to be deleted in future versions, use ACAPI::Library::GSMObject::GetUnID instead*
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_GetLibPartUnIDStr (const IO::Location *location, char *libPartUnId);


/**
 * @brief Returns the current lock status of the given library part.
 * @ingroup LibraryPart
 * @param location [in] The location of the library part.
 * @param status [out] The Teamwork lock status of the library part.
 * @param userCacheLibPartLocation [out] Location of the server library part file in the user cache (optional parameter).
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks The possible return values are the same as in @ref ACAPI_Teamwork_GetLockableStatus.
 * 			From Archicad 20 library parts from BIM server libraries can be locked and edited. 	When a server library part becomes editable, it is copied into a separate cache on the local machine, which is called user cache. This location can be retrieved with this function 	in the optional userCacheLibPartLocation parameter.
 * @warning *Legacy function - to be deleted in future versions, use ACAPI::Library::LibraryManager::GetTWID instead*
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_GetLibPartLockStatus (const IO::Location* location, API_LockableStatus* status, IO::Location* userCacheLibPartLocation = nullptr);


/**
 * @brief Deletes the given embedded library item (folder or library part).
 * @ingroup LibraryManagement
 * @ingroup LibraryPart
 * @param location [in] The location of the embedded library item.
 * @param keepGSMFile [in] If this parameter is true, then the operation deletes libpart only from the embedded library, but keeps the.gsm file in the filesystem. (optional parameter, by default it's false)
 * @param silentMode [in] If this parameter is true, then the missing libpart window won't open in case of any warning. (optional parameter, by default it's false)
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The given loc parameter is nullptr.
 * 			- APIERR_NOTMINE - The operation attempted to delete a library part that belongs to another user. Likely to occur in teamwork mode.
 * @remarks This operation is not undoable.
 */
__APIEXPORT GSErrCode ACAPI_LibraryManagement_DeleteEmbeddedLibItem (const IO::Location* location, bool keepGSMFile = false, bool silentMode = false);


/**
 * @brief Delete embeded lib items.
 * @ingroup LibraryManagement
 * @ingroup LibraryPart
 * @param location [in] Array of locations of the library items.
 * @param keepGSMFile [in] Keep the GSM file.
 * @param silentMode [in] Missing library parts dialog window should pop up.
 * @return
 * 			- NoError - The function has completed with success.
 */
__APIEXPORT GSErrCode ACAPI_LibraryManagement_DeleteEmbeddedLibItems (const GS::Array<IO::Location>* location, bool keepGSMFile = false, bool silentMode = false);


/**
 * @brief Creates a new folder inside a loaded library.
 * @ingroup LibraryManagement
 * @param newFolderLocationInLibrary [in] The location of the folder to be created in an existing active library.
 * @return
 * 			- APIERR_BADPARS - The passed location parameter is invalid or nullptr.
 * @remarks The function creates a new folder in an existing library loaded in the current project. The given location must be writable and, in Teamwork, must be reserved. If the folder already exists, the function returns NoError.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryManagement_CreateFolderInLibrary-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_LibraryManagement_CreateFolderInLibrary (const IO::Location* newFolderLocationInLibrary);


/**
 * @brief Copies files into a folder inside a loaded library.
 * @ingroup LibraryManagement
 * @param targetFolderLocationInLibrary [in] The target folder location.
 * @param filesToCopy [in] The list of files to be copied.
 * @param overwriteIfExists [in] Overwrite existing files found on the target location (optional parameter; if omitted, the value is considered false, resulting existing files to be skipped).
 * @return
 * 			- APIERR_BADPARS - The target folder location parameter is invalid or nullptr.
 * @remarks The function copies file from the passed locations into a folder in an existing library loaded in the current project. The target folder must be writable and, in Teamwork, must be reserved.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryManagement_CopyFilesIntoLibrary-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_LibraryManagement_CopyFilesIntoLibrary (const IO::Location* targetFolderLocationInLibrary, const GS::Array<IO::Location>* filesToCopy, const bool* overwriteIfExists);


/**
 * @brief Returns the actual toolbox mode.
 * @ingroup Toolbox
 * @param toolBoxItem [out] Current toolbox mode data.
 * @return
 * 			- NoError - The function completed with success.
 * 			- APIERR_BADPARS - toolBoxItem is nullptr
 * @remarks This function is used to get the current toolbox mode. The mode is returned in the type field. For those types which can have more toolbox modes (ID_Wind, ID_Door, ID_Symb, ID_Light), the owner ID of the tool is returned, too. If the current toolbox mode has no element type associated with (e.g. arrow mode and marquee mode), the typeID will be @c API_ZombieElemID.
 * 			To change the active toolbox item use the @ref ACAPI_Toolbox_SetToolBoxMode function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Toolbox_GetToolBoxMode-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Toolbox_GetToolBoxMode (API_ToolBoxItem* toolBoxItem);


/**
 * @brief Sets the actual toolbox mode.
 * @ingroup Toolbox
 * @param toolBoxItem [in] Toolbox mode to be set.
 * @return
 * 			- NoError - The function completed with success.
 * 			- APIERR_BADPARS - The variationID of the library part type does not match to the toolbox mode type
 * 			- APIERR_BADID - toolBoxItem->type contains invalid data
 * @remarks This function is used to change the current toolbox mode. The mode is specified by the element type ID. For those types which can have more toolbox modes (ID_Wind, ID_Door, ID_Symb, ID_Light), the variationID of the tool should also be supplied. For @c API_ZombieElemID or an invalid element type ID specification the arrow mode will be set.
 * 			Note that the function does not switch the toolbox immediately, but posts an event into the application queue. The command will be executed only when the application events are processed.
 * 			To get the active toolbox mode use the @ref ACAPI_Toolbox_GetToolBoxMode function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Toolbox_SetToolBoxMode-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Toolbox_SetToolBoxMode (API_ToolBoxItem* toolBoxItem);


/**
 * @brief Returns information on the current state of the toolbox.
 * @ingroup Toolbox
 * @param toolBoxInfo [out] Miscellaneous information on the toolbox.
 * @param enableHidden [in] Include hidden tools from the toolbox as well. This parameter is optional; if you pass nullptr in the second parameter, it defaults to false.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - tboxInfo is nullptr.
 * 			- APIERR_MEMFULL - Low memory condition.
 * @remarks You can query the current state of the toolbox with this function. It returns information on the different installed items (external tools, too), and the active toolbox item (the active tool).
 * 			The enableHidden flag tells Archicad to include hidden toolbox items as well. These are the tools which don't have any icon in the toolbox, though using them puts Archicad into a state which works as if you chose one of the 'real' tools. A good example of this is the Slab Accessory.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Toolbox_GetToolBoxInfo-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Toolbox_GetToolBoxInfo (API_ToolBoxInfo* toolBoxInfo, bool enableHidden = false);


/**
 * @brief Returns the current state of the autogroup mode.
 * @ingroup View
 * @param autoGrp [out] Autogroup mode is ON or OFF.
 * @return
 * 			- NoError - The function completed with success.
 * 			- APIERR_NOPLAN - There is no plan window currently opened
 * 			- APIERR_BADPARS - autoGrp is nullptr
 * @remarks This function is used to get the current autogroup mode.
 */
__APIEXPORT GSErrCode ACAPI_View_IsAutoGroupOn (bool* autoGrp);


/**
 * @brief Returns the current state of the Suspend Groups mode.
 * @ingroup View
 * @param suspGrp [out] Suspend Groups mode is ON or OFF.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOPLAN - There is no plan window currently opened
 * 			- APIERR_BADPARS - suspGrp is nullptr
 * @remarks This function is used to get the current suspendgroup mode. For changing the suspension state of groups use the @ref ACAPI_Grouping_Tool function.
 */
__APIEXPORT GSErrCode ACAPI_View_IsSuspendGroupOn (bool* suspGrp);


/**
 * @brief Returns the actual view display options.
 * @ingroup Navigator
 * @param viewOptions [out] actual settings of the 'Model View Options' dialog, and the View/On-Screen View Options menu.
 * @param attrIndex [out] Optional parameter; the index of the current model view options combination.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - viewOptions is nullptr
 * 			- APIERR_NOPLAN - There is no plan window currently opened
 * @remarks This function is used to retrieve the actual model and on-screen view options. The returned structure corresponds to the parameters can be set in the 'Model View Options' dialog, and in the View/On-Screen View Options submenu. For more information see the @ref API_ViewOptions structure.
 * 			The settings can be changed with the @ref ACAPI_Navigator_ChangeViewOptions environment function.
 */
__APIEXPORT GSErrCode ACAPI_Navigator_GetViewOptions (API_ViewOptions* viewOptions, short* attrIndex = nullptr);


/**
 * @brief Changes the actual model view options.
 * @ingroup Navigator
 * @param viewOptions [in] the settings of the 'Model View Options' dialog, and the View/On-Screen View Options menu.
 * @param modelViewOptionAttributeIndex [in] Optional parameter; if not nullptr, then switch to the model view options attribute identified by this index.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - viewOptions is nullptr.
 * 			- APIERR_NOPLAN - There is no plan window currently opened.
 * 			- APIERR_BADINDEX - attrIndex is invalid.
 * @remarks This function is used to change the on-screen and model view options. The first part of the passed structure corresponds to the parameters in the 'Model View Options' dialog; the other fields to the elements of the View/On-Screen View Options submenu. For more information see the @ref API_ViewOptions structure.
 * 			The actual settings can be retrieved with the @ref ACAPI_Navigator_GetViewOptions environment function.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_Navigator_ChangeViewOptions (API_ViewOptions* viewOptions, short* modelViewOptionAttributeIndex = nullptr);


/**
 * @brief Returns the data of the installed stories.
 * @ingroup ProjectSetting
 * @param storyInfo [out] parameters of the actual stories.
 * @param mask Can be @c APIElemMask_FromFloorplan or nullptr.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - storyInfo is nullptr.
 * 			- APIERR_NOPLAN - No open project.
 * 			- APIERR_MEMFULL - Low memory condition.
 * @remarks The @ref API_StoryInfo structure contains an array of information to each story (index, level, and name); and also the active one.
 * 			Do not forget to dispose the data handle if it is not needed any more.
 */
__APIEXPORT GSErrCode ACAPI_ProjectSetting_GetStorySettings (API_StoryInfo* storyInfo, UInt32 mask = 0);


/**
 * @brief Modifies the story structure.
 * @ingroup ProjectSetting
 * @param storyCmd [in] Action parameters to change the story settings.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - storyCommand is nullptr or contains invalid value:
 * 			- the index  is out of the range of existing stories,
 * 			- the action  field is invalid.
 * 			- APIERR_NOPLAN - No open project.
 * 			- APIERR_MEMFULL - Low memory condition.
 * @remarks This function is used to perform story settings related commands. The command is specified by the action field of the storyCommand parameter. Possible values and the required parametrization are described at the @ref API_StoryCmdID structure.
 * 			If this function is called with @c APIStory_Delete parameter, it performs complete operations. Otherwise this function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_ProjectSetting_ChangeStorySettings (API_StoryCmdType* storyCmd);


/**
 * @brief Create a new Trace (ghost) database.
 * @ingroup View
 * @param ghostRecord Information describing the new Trace database.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function creates a new Trace record (ghost database).
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_View_CreateGhostRecord-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_View_CreateGhostRecord (const API_GhostRecord* ghostRecord);


/**
 * @brief Retrieve a Trace record from the database.
 * @ingroup View
 * @param databaseUnId [in] Retrieve the trace record for this database (the parent database unid is given here).
 * @param ghostRecord [out] The ghost record for that database.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks Use this function to retrieve an existing trace (ghost) record. You should pass the parent database unid here (the same database the trace record was created for).
 */
__APIEXPORT GSErrCode ACAPI_View_GetGhostRecord (const API_DatabaseUnId* databaseUnId, API_GhostRecord* ghostRecord);


/**
 * @brief Deletes a Virtual Trace (ghost) record.
 * @ingroup View
 * @param ghostRecord The Trace database to delete (the parentDatabase and ghostDatabase should be set).
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks Deletes the trace record associated with the parent database.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_View_DeleteGhostRecord (const API_GhostRecord* ghostRecord);


/**
 * @brief Change the settings of a Virtual Trace (ghost) record.
 * @ingroup View
 * @param ghostRecord The Trace database to change.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_WINDNOTEXIST - The parent database does not exist.
 * @remarks Change the settings of the trace record associated with the parent database.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_View_ChangeGhostRecord (const API_GhostRecord* ghostRecord);


/**
 * @brief Retrieves the current ghost story settings.
 * @ingroup View
 * @param ghostStoryType The ghost story settings
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - ghostStory is nullptr
 * 			- APIERR_NOPLAN - There is no floor plan window opened
 * @remarks Use this function to retrieve the ghost story settings. The same data can also be required with the @ref ACAPI_ProjectSetting_GetStorySettings environment function.
 */
__APIEXPORT GSErrCode ACAPI_View_GetGhostStorySettings (API_GhostStoryType* ghostStoryType);


/**
 * @brief Returns the preferences data.
 * @ingroup ProjectSetting
 * @param prefs [out] Data of a preferences tab page. The content depends on the prefsType parameter.
 * @param prefsTypeID [in] The type of the preferences you want to get.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - prefs is nullptr
 * 			- APIERR_BADID - prefsTypeID is invalid.
 * 			- APIERR_NOPLAN - No open project.
 * 			- APIERR_MEMFULL - Low memory condition.
 * @remarks Many switches and values are returned which appear on the different tab pages of the Project
 * 			Preferences dialog and the Work Environment settings. Usable structures of preference types (for `prefs`)
 * 			are: @ref API_WorkingUnitPrefs @ref API_RefLevelsPrefs @ref API_DimensionPrefs @ref API_CalcUnitPrefs @ref
 * 			API_CalcRulesPrefs @ref API_LegacyPrefs @ref API_ZonePrefs @ref API_SafetyPrefs @ref API_ImagingAndCalcPrefs
 * @ref API_FloorPlanCutDefinition @ref API_LayoutsPrefs Note: `prefsTypeID` should be passed as a value
 * 		instead of a pointer. See the example codes for details.
 */
__APIEXPORT GSErrCode ACAPI_ProjectSetting_GetPreferences (void* prefs, API_PrefsTypeID prefsTypeID);

/**
 * @brief Adjusts the preferences.
 * @ingroup ProjectSetting
 * @param prefs [in] Data of a preferences tab page. The content depends on the prefsType parameter.
 * @param prefsTypeID [in] The type of the preferences you want to set.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - `prefs` is `nullptr`, or calculation rules are invalid, or the given dimensioning standard index is invalid.
 * 			- APIERR_BADID - `prefsTypeID` is invalid (for example, you cannot set Data Safety preferences)
 * 			- APIERR_NOPLAN - No open project.
 * 			- APIERR_GENERAL - No dimensioning standards in the project.
 * @remarks Many switches and values (except Data Safety) can be set that appear on the different tab pages of the Project
 * 			Preferences dialog and the Work Environment settings. Usable structures of preference types (for `prefs`) are:
 * @ref API_WorkingUnitPrefs @ref API_RefLevelsPrefs @ref API_DimensionPrefs @ref API_CalcUnitPrefs @ref
 * 		API_CalcRulesPrefs @ref API_LegacyPrefs @ref API_ZonePrefs @ref API_SafetyPrefs @ref API_ImagingAndCalcPrefs
 * @ref API_FloorPlanCutDefinition @ref API_LayoutsPrefs Note: `prefsType` should be passed as a value
 * 		instead of a pointer. See the example.
 * 		This is an undoable operation, so be careful!
 */
__APIEXPORT GSErrCode ACAPI_ProjectSetting_SetPreferences (void* prefs, API_PrefsTypeID prefsTypeID);


/**
 * @brief Returns the value of a physical property (length/area/volume/angle) in the unit of the given Project Preference.
 * @ingroup Conversion
 * @param api_unitConvData [in/out] You can specify in it the value to convert, and the Project Preference with which to convert. The environment function returns the converted value, extra accuracy and unit string in the same struct.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - api_unitConvData is nullptr, or api_unitConvData->unitConvPref is invalid.
 * @remarks api_unitConvData->value has to be given in m/m²/m³/radian. The converted value will be returned in string format, as it would appear in Archicad.
 */
__APIEXPORT GSErrCode ACAPI_Conversion_GetConvertedUnitValue (API_UnitConversionData* api_unitConvData);


/**
 * @brief Returns information on sun parameters.
 * @ingroup GeoLocation
 * @param sunInfo [out] Parameters of the sun.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - sunInfo is nullptr.
 * 			- APIERR_NOPLAN - No open project.
 * @remarks This function is used to get information on sunlight parameters. These parameters are sophisticated sunlight for photorendering.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_GeoLocation_GetSunSets-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GeoLocation_GetSunSets (API_SunInfo* sunInfo);


/**
 * @brief Returns information on location parameters.
 * @ingroup GeoLocation
 * @since Archicad 26
 * @param placeInfo [out] Parameters of the place.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - placeInfo is nullptr.
 * 			- APIERR_NOPLAN - No open project.
 * @remarks This function is used to get the current place, date, time, and sun information. These data can be set in the Sun Settings dialog.
 * 			Refer to the @ref ACAPI_GeoLocation_CalcSunOnPlace function to calculate the sun parameters on a custom place and date; Refer to the @ref ACAPI_GeoLocation_ChangePlaceSets function to set the current settings.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_GeoLocation_GetPlaceSets-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GeoLocation_GetPlaceSets (API_PlaceInfo* placeInfo);


/**
 * @brief May the current user change the place settings now?
 * @ingroup GeoLocation
 * @param withDialog [in] If the user don't have permisson to change the place settings now, then the Location Dialog will open if this parameter is true, otherwise it will just return whether the user can or can not change the place settings now. This parameter is optional; if you pass nullptr, it defaults to true.
 * @return
 * 			- NoError - The user is allowed to change the place settings.
 * 			- APIERR_NOTEDITABLE - The user is not allowed to change the place settings.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_GeoLocation_CanChangePlaceSets-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GeoLocation_CanChangePlaceSets (bool* withDialog);


/**
 * @brief Changes the place settings.
 * @ingroup GeoLocation
 * @since Archicad 26
 * @param placeInfo [in] This structure holds the parameters of the place.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - placeInfo is nullptr or contains invalid data.
 * 			- APIERR_NOPLAN - No open project.
 * @remarks This function is used to set/change the current place, date, time and north direction parameters of the plan. The sun angles are calculated in the given place and on the given day and time. The calculated angles are returned in the sunAngXY and sunAngZ fields of the @ref API_PlaceInfo structure.
 * 			Please refer to the @ref ACAPI_GeoLocation_GetPlaceSets function for calculating the sun parameters at a custom place on a certain date.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_GeoLocation_ChangePlaceSets-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GeoLocation_ChangePlaceSets (API_PlaceInfo* placeInfo);


/**
 * @brief Returns the Location settings of the project.
 * @ingroup GeoLocation
 * @since Archicad 25
 * @param apiGeoLocation [out] Location data associated with the project
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - apiGeoLocation is nullptr
 * @remarks This function returns the Location settings of the project.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_GeoLocation_GetGeoLocation-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GeoLocation_GetGeoLocation (API_GeoLocation* apiGeoLocation);


/**
 * @brief Modifies the Location settings of the project.
 * @ingroup GeoLocation
 * @since Archicad 25
 * @param apiGeoLocation [in] the Location settings associated with the project
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - apiGeoLocation is nullptr
 * 			- APIERR_NOTEDITABLE - The Location settings cannot be modified in Teamwork unless it is reserved by the current user.
 * @remarks This function sets the Location settings of the project.
 * 			The @c ACAPI_GeoLocation_SetGeoLocation function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_GeoLocation_SetGeoLocation-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GeoLocation_SetGeoLocation (API_GeoLocation* apiGeoLocation);


/**
 * @brief Returns the transformation matrix that transforms points given in the Project Origin's coordinate system into the Survey Point's coordinate system.
 * @ingroup SurveyPoint
 * @since Archicad 25
 * @param apiSPTransformation [out] the calculated transformation matrix
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - apiSPTransformation is nullptr
 * @remarks This function computes a transformation matrix that transforms the coordinates of a given point in the Project Origin's coordinate system into the Survey Point's coordinate system.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_SurveyPoint_GetSurveyPointTransformation-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_SurveyPoint_GetSurveyPointTransformation (API_Tranmat* apiSPTransformation);


/**
 * @brief Checks if the survey point is visible.
 * @ingroup SurveyPoint
 * @since Archicad 25
 * @param spVisibility [out] Survey point visibility
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - spVisibility is nullptr
 * @remarks This function checks the visibility of the survey point.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_SurveyPoint_IsSurveyPointVisible-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_SurveyPoint_IsSurveyPointVisible (bool* spVisibility);


/**
 * @brief Sets the visibility of the survey point.
 * @ingroup SurveyPoint
 * @since Archicad 25
 * @param spVisibility [in] New survey point visibility
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - spVisibility is nullptr
 * @remarks This function sets the visibility of the survey point.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_SurveyPoint_SetSurveyPointVisibility-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_SurveyPoint_SetSurveyPointVisibility (bool* spVisibility);


/**
 * @brief Returns the lock state of the Survey Point.
 * @ingroup SurveyPoint
 * @since Archicad 25
 * @param isSurveyPointLocked [out] Lock state of the Survey Point
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter is nullptr
 * @remarks The Survey Point can be locked in order to prevent its floor plan position coordinates and the project north angle from being changed.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_SurveyPoint_IsSurveyPointLocked-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_SurveyPoint_IsSurveyPointLocked (bool* isSurveyPointLocked);


/**
 * @brief Locks or Unlocks the Survey Point.
 * @ingroup SurveyPoint
 * @since Archicad 25
 * @param lockedState [in] Lock state of the Survey Point
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameter is nullptr
 * @remarks This function locks or unlocks the Survey Point. Note that this lock affects only the North Angle and the floor plan position of the Survey Point. All the other parameters of the @ref API_GeoLocation data can be changed even if the Survey Point is locked.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_SurveyPoint_SetSurveyPointLocked-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_SurveyPoint_SetSurveyPointLocked (bool* lockedState);


/**
 * @brief Returns GDL environment date information (GDL_PROJECT_DATE).
 * @ingroup LibraryManagement
 * @param date [out] GDL environment date. It must be an Int32 array with 6 size.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks The returned array contains the date in the following format:
 * 			|Date component|Meaning|
 * 			|--- |--- |
 * 			|date[0]|Year|
 * 			|date[1]|Month|
 * 			|date[2]|Day|
 * 			|date[3]|Hour|
 * 			|date[4]|Minute|
 * 			|date[5]|Second|
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryManagement_GetGDLDate-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_LibraryManagement_GetGDLDate (Int32* date);


/**
 * @brief Changes GDL environment date (GDL_PROJECT_DATE).
 * @ingroup LibraryManagement
 * @param date [in] The new GDL environment date. It must be an Int32 array with 6 size.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks The input date array must contain the new date in the following format:
 * 			|Date component|Meaning|
 * 			|--- |--- |
 * 			|date[0]|Year|
 * 			|date[1]|Month|
 * 			|date[2]|Day|
 * 			|date[3]|Hour|
 * 			|date[4]|Minute|
 * 			|date[5]|Second|
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryManagement_ChangeGDLDate-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_LibraryManagement_ChangeGDLDate (Int32* date);


/**
 * @brief Returns information on curve tracing parameters.
 * @ingroup UserInput
 * @param magicWandInfo [out] Parameters of the 'Magic Wand Settings...' dialog.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - magicWandInfo is nullptr.
 * 			- APIERR_NOPLAN - No open project.
 * @remarks This function is used to get the parameters can be set in the 'Magic Wand Settings...' dialog.
 * 			Refer to the @ref API_MagicWandInfo structure to get further details.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_UserInput_GetMagicWandSets-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_UserInput_GetMagicWandSets (API_MagicWandInfo* magicWandInfo);


/**
 * @brief Returns information on curve tracing parameters.
 * @ingroup ProjectSetting
 * @param arcDiff [out] Distance between arc and line when segmenting the arc.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - arcDiff is nullptr.
 * 			- APIERR_NOTSUPPORTED - Not at export.
 * @remarks Return the arc differecnes at export.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ProjectSetting_GetExportTolerance-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ProjectSetting_GetExportTolerance (double* arcDiff);


/**
 * @brief Returns information on the 3D projection settings.
 * @ingroup View
 * @param proj3DInfo [out] Parameters of the '3D Projection Settings...' dialog
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - proj3DInfo is nullptr
 * 			- APIERR_NOPLAN - No open project
 * @remarks This function is used to get the parameters can be set in the '3D Projection Settings...' dialog of Archicad.
 * 			Refer to the @ref API_3DProjectionInfo structure to get further details.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_View_Get3DProjectionSets-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_View_Get3DProjectionSets (API_3DProjectionInfo* proj3DInfo);


/**
 * @brief Changes the parameters of the 3D projection.
 * @ingroup View
 * @param proj3DInfo [in] Parameters of the '3D Projection Settings...' dialog
 * @param switchOnlyAxonoOrPersp [in] Optional parameter. If it is not nullptr and the value is true, only the isPersp field of proj3DInfo is considered
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - proj3DInfo is nullptr
 * 			- APIERR_NOPLAN - No open project
 * @remarks This function is used to change the 3D projection.
 * 			If you pass true in the switchOnlyAxoOrPersp parameter, the kind of the projection (parallel or perspective) will be changed only, all the other parameters will be ignored. If the value of camGuid or actCamSet field of @ref API_3DProjectionInfo is non-zero, the perspective projection will be defined according to the camera identified by camGuid. If camGuid is invalid, the first camera of the camera set defined by the actCamSet field will be used. Otherwise the perspective settings will not be related to any floorplan camera element, and will be defined by the @ref API_PerspPars data. These fields are irrelevant when changing the axonometric projection parameters.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_View_Change3DProjectionSets-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_View_Change3DProjectionSets (API_3DProjectionInfo* proj3DInfo, bool* switchOnlyAxonoOrPersp = nullptr);


/**
 * @brief Returns information on the photorendering settings.
 * @ingroup Rendering
 * @param rendInfo [out] Data of a "PhotoRendering Settings..." tab page. The type depends on the prefsType parameter
 * @param rendSetType [in] Type of the PhotoRendering Settings you want to get
 * @param sceneName [in] The name of the Rendering Scene of which the settings you want to get. If nullptr, the settings of the current Scene will be returned.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - rendInfo is nullptr or rendSetType is invalid
 * 			- APIERR_BADNAME - The sceneName parameter was not nullptr, and no named Rendering Scene exists with this name.
 * @remarks Many switches and values are returned which can be set in the different tab pages of the "PhotoRendering Settings..." dialog.
 * 			Usable structures of photorendering types (for rendInfo) are:
 * 			- @ref API_RendEffects,
 * 			- @ref API_RendImage,
 * 			Note: the rendSetType should be passed as a value instead of a pointer.
 * 			Note: when you get an @ref API_RendImage with this function, don't forget to free the allocated memory: delete rendInfo.bkgPictFile;.
 * 			See an example of getting and modifying photorendering settings at the description of @ref ACAPI_Rendering_ChangeRenderingSets.
 */
__APIEXPORT GSErrCode ACAPI_Rendering_GetRenderingSets (void* rendInfo, API_RendSetTypeID rendSetType, const GS::UniString* sceneName = nullptr);


/**
 * @brief Changes the photorendering settings.
 * @ingroup Rendering
 * @param rendEffects [in] Data of a "PhotoRendering Settings..." tab page. The type depends on the prefsType parameter
 * @param rendSetType [in] Type of the PhotoRendering Settings you want to modify
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - rendInfo is nullptr or rendSetType is invalid
 * @remarks This function is used to modify the settings of the different tab pages of the "PhotoRendering Settings..." dialog.
 * 			Usable structures of photorendering types (for rendInfo) are:
 * 			- @ref API_RendEffects,
 * 			- @ref API_RendImage,
 * 			Note: the rendSetType should be passed as a value instead of a pointer; see the example below.
 * 			If you pass a valid location in the bkgPictFile pointer of the @ref API_RendImage parameter, and the referenced file does not belong to any currently loaded library, then the image file will be copied into the embedded library of the project. This also means that any subsequent modifications to the original image file will not affect the rendering backround picture until you remove it, and add it again to the library.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Rendering_ChangeRenderingSets-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Rendering_ChangeRenderingSets (void* rendEffects, API_RendSetTypeID rendSetType);


/**
 * @brief Returns the names of all the named Rendering Scenes.
 * @ingroup Rendering
 * @param sceneNames [out] Array of the names of all the named Rendering Scenes.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - sceneNames is nullptr.
 * @remarks The names are returned in the order of recent usage, putting the most recent rendering scene first.
 */
__APIEXPORT GSErrCode ACAPI_Rendering_GetRenderingSceneNames (GS::Array<GS::UniString>* sceneNames);


/**
 * @brief Sets the current Rendering Scene to the given named Rendering Scene.
 * @ingroup Rendering
 * @param newCurrentSceneName [in] The name of the Rendering Scene, which you want to set as the current Scene.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - newCurrentSceneName is nullptr.
 * 			- APIERR_BADNAME - No named Rendering Scene exists with this name (newCurrentSceneName).
 * 			- APIERR_GENERAL - Could not set newCurrentSceneName as the current Scene.
 * @remarks This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_Rendering_SetCurrentRenderingScene (const GS::UniString* newCurrentSceneName);


/**
 * @brief Returns the 3D image item settings.
 * @ingroup View
 * @since Archicad 26
 * @param filterAndCutSettings [out] Parameters of the 'Filter and Cut Elements in 3D' dialog box
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - filterAndCutSettings is nullptr
 * 			- APIERR_NOPLAN - No open project
 * @remarks This function is used to retrieve the 3D image item settings which can be accessed via the 'Filter and Cut Elements in 3D' dialog box. See an example at the description of @ref ACAPI_View_Change3DImageSets.
 */
__APIEXPORT GSErrCode ACAPI_View_Get3DImageSets (API_3DFilterAndCutSettings* filterAndCutSettings);


/**
 * @brief Changes the 3D image item settings.
 * @ingroup View
 * @since Archicad 26
 * @param filterAndCutSettings [in] Parameters of the 'Filter and Cut Elements in 3D' dialog box
 * @param mustConvert [in] Optional parameter; if it is not nullptr and its value is true then the function drops the partial conversion data, so that a full rebuild will be performed upon the next Rebuild operation
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOPLAN - No open project
 * @remarks This function is used to change the 3D image item settings which can be accessed via the 'Filter and Cut Elements in 3D' dialog box.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_View_Change3DImageSets-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_View_Change3DImageSets (API_3DFilterAndCutSettings* filterAndCutSettings, bool* mustConvert = nullptr);


/**
 * @brief Retrieves the 3D Window settings.
 * @ingroup View
 * @param windowInfo [out] Parameters of the 3D Window
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - windowInfo is nullptr
 * 			- APIERR_NOPLAN - No open project
 * @remarks This function is used to get the data of the '3D Window Settings' dialog box, and the size and zoom parameters of the 3D window.
 */
__APIEXPORT GSErrCode ACAPI_View_Get3DWindowSets (API_3DWindowInfo* windowInfo);


/**
 * @brief Changes the 3D window settings.
 * @ingroup View
 * @param windowInfo [in] Parameters of the 3D Window.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - windowInfo is nullptr
 * 			- APIERR_NOPLAN - No open project
 * @remarks This function is used to modify the data of the '3D Window Settings' dialog box, and the size and zoom parameters of the 3D window.
 * 			In order the changes to take effect you might need to call the @ref ACAPI_Database_RebuildCurrentDatabase database function.
 * 			You can also change the zoom of the 3D model window with the @ref ACAPI_View_Zoom automation function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_View_Change3DWindowSets-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_View_Change3DWindowSets (API_3DWindowInfo* windowInfo);


/**
 * @brief Retrieves all parameters of a 3D style
 * @ingroup View
 * @param style [in/out] Parameters of the 3D Style
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - style is nullptr, or style->name is invalid.
 * 			- APIERR_NOPLAN - No open project.
 * @remarks Set the style->name field to the name of a valid style in the project, and call @c ACAPI_View_Get3DStyle to get the details of that style. Leaving the style->name field empty is equivalent to setting it to the name of the current style.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_View_Get3DStyleList-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_View_Get3DStyle (API_3DStyle* style);


/**
 * @brief Modifies the parameters of an existing 3D style
 * @ingroup View
 * @param style [in] New parameters of the existing 3D style
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - style is nullptr, or a some parameter of the style is invalid.
 * 			- APIERR_NOPLAN - No open project.
 * 			- APIERR_NOACCESSRIGHT - The user does not have Teamwork privilege to modify 3D styles.
 * @remarks Renaming styles is not supported, do not edit the style->name field as it is used for the identification of the existing style.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_View_Get3DStyleList-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_View_Change3DStyle (API_3DStyle* style);


/**
 * @brief Creates a new 3D style.
 * @ingroup View
 * @param style [in] Parameters of a new 3D style
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - style is nullptr, or a some parameter of the style is invalid, or a style with the same name already exists.
 * 			- APIERR_NOPLAN - No open project.
 * 			- APIERR_NOACCESSRIGHT - The user does not have Teamwork privilege to create a 3D style.
 * @remarks The newly created style is not applied upon creation. To set the new style as active use @ref ACAPI_View_SetCurrent3DStyle.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_View_Get3DStyleList-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_View_Create3DStyle (API_3DStyle* style);


/**
 * @brief Retrieves the names of all styles in the project and/or the name of the current style.
 * @ingroup View
 * @param styles [out] List of the names of all styles in the project.
 * @param current [out] The name of the currently active style.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Both parameter pointers are nullptr.
 * @remarks This function is used to retrieve the list of 3D styles which can be accessed via the '3D Styles' dialog box. Any of the parameters can be set to @c nullptr if that information is to be ignored, but doing so with both at the same time returns no information.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_View_Get3DStyleList-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_View_Get3DStyleList (GS::Array<GS::UniString>* styles, GS::UniString* current = nullptr);


/**
 * @brief Sets an existing style as active.
 * @ingroup View
 * @param name [in] Name of an existing style
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - name is nullptr, or the specified style does not exist.
 * 			- APIERR_NOPLAN - No open project.
 * @remarks See an example at the description of @ref ACAPI_View_Get3DStyleList.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_View_Get3DStyleList-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_View_SetCurrent3DStyle (const GS::UniString* name);


/**
 * @brief Retrieves the 3D cutting plane settings.
 * @ingroup View
 * @param cutInfo [out] Data of the "3D Cutting Planes..." dialog
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - cutInfo is nullptr
 * 			- APIERR_NOPLAN - No open project
 * 			- APIERR_MEMFULL - Low memory condition
 * @remarks This function is used to get information on 3D cutting planes.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_View_Get3DCuttingPlanes-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_View_Get3DCuttingPlanes (API_3DCutPlanesInfo* cutInfo);


/**
 * @brief Changes the 3D cutting planes.
 * @ingroup View
 * @param cutInfo Data of the "3D Cutting Planes..." dialog
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - cutInfo is nullptr or contains invalid data
 * 			- APIERR_NOPLAN - No open project
 * @remarks This function is used to change the 3D cutting plane parameters.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_View_Change3DCuttingPlanes-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_View_Change3DCuttingPlanes (API_3DCutPlanesInfo* cutInfo);


/**
 * @brief Returns the visibility of application.
 * @ingroup View
 * @param isShown [out] Application is visible.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function is used to used to get visibility of application.
 * 			The actual visibility can be changed with the @ref ACAPI_View_ChangeShowHideState function.
 * 			Supported on Windows only.
 */
__APIEXPORT GSErrCode ACAPI_View_GetShowHideState (bool* isShown);


/**
 * @brief Changes the visibility of application.
 * @ingroup View
 * @param toShow [in] Application is visible.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function is used to change visibility of application.
 * 			The actual visibility can be retrieved with the @ref ACAPI_View_GetShowHideState function.
 * 			Supported on Windows only.
 */
__APIEXPORT GSErrCode ACAPI_View_ChangeShowHideState (bool* toShow);


/**
 * @brief Gets miscellaneous information about application.
 * @ingroup ProjectOperation
 * @param miscAppInfo [out] Miscellaneous information of the application
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - miscAppInfo is nullptr.
 * @remarks This function is used to get version string of application and caption of application's main window.
 */
__APIEXPORT GSErrCode ACAPI_ProjectOperation_GetMiscAppInfo (API_MiscAppInfo* miscAppInfo);


/**
 * @brief Gets miscellaneous information about current printer.
 * @ingroup ProjectOperation
 * @param miscPrinterInfo [out] Miscellaneous information of the selected printer
 * @return
 * 			- NoError - The function completed with success.
 * 			- APIERR_BADPARS - miscPrinterInfo is nullptr.
 * @remarks This function is used to get name and orientation of selected printer in Archicad.
 * 			Supported on Windows only.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ProjectOperation_GetMiscPrinterInfo-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ProjectOperation_GetMiscPrinterInfo (API_MiscPrinterInfo* miscPrinterInfo);


/**
 * @brief Gets miscellaneous information about plotter.
 * @ingroup ProjectOperation
 * @param miscPlotterInfo [out] Miscellaneous information of the selected plotter
 * @return
 * 			- NoError - The function completed with success.
 * 			- APIERR_BADPARS - miscPlotterInfo is nullptr.
 * @remarks This function is used to get name and model of selected plotter in Archicad.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ProjectOperation_GetMiscPlotterInfo-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ProjectOperation_GetMiscPlotterInfo (API_MiscPlotterInfo* miscPlotterInfo);


/**
 * @brief Retrieves the current printer settings.
 * @ingroup ProjectOperation
 * @param printPars [out] the printing parameters
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The printPars parameter is nullptr
 * @remarks This function retrieves the printing settings currently used.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_ProjectOperation_GetPrinterPars-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_ProjectOperation_GetPrinterPars (API_PrintPars* printPars);


/**
 * @brief Returns the location of special folders.
 * @ingroup ProjectSetting
 * @param specFolderID [in] A pointer to the type of the folder you are interested in.
 * @param location [out] The file system location of the required folder.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - specFolderID contains invalid data, or the location parameter is nullptr
 * 			- APIERR_REFUSEDPAR - The requested special folder is not initialized or missing
 */
__APIEXPORT GSErrCode ACAPI_ProjectSettings_GetSpecFolder (API_SpecFolderID* specFolderID, IO::Location* location);


/**
 * @brief Creates a new layout.
 * @ingroup Navigator
 * @param layoutInfo [in] properties of the layout
 * @param databaseUnId [in] Database of the master layout
 * @param parent [in] Optional parameter; Parent navigator item to insert below.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - layoutInfo or databaseUnId is nullptr or invalid
 * 			- APIERR_NOPLAN - Current windows is not plan type
 * 			- APIERR_REFUSEDCMD - This function cannot be called from an opened undo session
 * 			- APIERR_GENERAL - General internal error
 * @remarks This function is used to create a new layout by specifying the master layout and the parent in the layout tree.
 * 			The properties of the layout can be changed with the @ref ACAPI_Navigator_ChangeLayoutSets environment function.
 */
__APIEXPORT GSErrCode ACAPI_Navigator_CreateLayout (API_LayoutInfo* layoutInfo, API_DatabaseUnId* databaseUnId, API_Guid* parent = nullptr);


/**
 * @brief Returns the settings of a layout.
 * @ingroup Navigator
 * @param layoutInfo [out] properties of the layout
 * @param databaseUnId [in] Optional parameter; return the layout information for this database. If nullptr, then the current layout is used.
 * @param actualPageIndex [in] Optional parameter; return the layout information for this page.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - layoutInfo is nullptr
 * 			- APIERR_BADDATABASE - The current database is not layout type
 * @remarks This function is used to retrieve the current or the given layout's parameters such as name, size and margin values.
 * 			The properties of the layout can be changed with the @ref ACAPI_Navigator_ChangeLayoutSets environment function.
 */
__APIEXPORT GSErrCode ACAPI_Navigator_GetLayoutSets (API_LayoutInfo* layoutInfo, API_DatabaseUnId* databaseUnId = nullptr, const ULong* actualPageIndex = nullptr);


/**
 * @brief Changes the settings of the current layout in Archicad.
 * @ingroup Navigator
 * @param layoutInfo [in] Properties of the layout.
 * @param databaseUnId [in] apply changes to this database (can be nullptr). The changes are applied to the current layout or master layout database if this parameter is omitted, otherwise to the given database.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - layoutInfo is nullptr
 * 			- APIERR_GENERAL - No master layout, or the function failed
 * @remarks This function is used to modify the current (master) layout parameters such as size and margin values. The size and margins are always applied to the master layout.
 * 			This function does not modify the name of the layout. This can be done with @ref ACAPI_Database_ModifyDatabase database function.
 * 			The actual settings can be retrieved with the @ref ACAPI_Navigator_GetLayoutSets environment function.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_Navigator_ChangeLayoutSets (const API_LayoutInfo* layoutInfo, API_DatabaseUnId* databaseUnId);


/**
 * @brief Retrieves the index of the current layer combination.
 * @ingroup Navigator
 * @param layerCombIndex [out] index of the layer combination currently in effect
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - layerCombInd is nullptr
 * @remarks Use this function to retrieve the index of the layer combination currently set. If the current state of the layers does not match any layer combinations, the function returns 0 in the layerCombInd parameter.
 * 			You can set layers according to a given layer combination with the @ref ACAPI_Navigator_ChangeCurrLayerComb environment function.
 */
__APIEXPORT GSErrCode ACAPI_Navigator_GetCurrLayerComb (API_AttributeIndex* layerCombIndex);


/**
 * @brief Activates a layer combination.
 * @ingroup Navigator
 * @param layerCombIndex [in] index of the layer combination to be activated
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - layerCombInd is nullptr
 * 			- APIERR_BADINDEX - layerCombInd is out of range
 * @remarks This function puts the given layer combination into effect. The currently active layer combination can be retrieved with the @ref ACAPI_Navigator_GetCurrLayerComb environment function.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_Navigator_ChangeCurrLayerComb (API_AttributeIndex* layerCombIndex);


/**
 * @brief Get current pen set index.
 * @ingroup Attribute
 * @param penSetIndex [out] Current pen set index.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Incorrect penSetIndex was specified.
 */
__APIEXPORT GSErrCode ACAPI_Attribute_GetCurrPenSet (API_AttributeIndex* penSetIndex);


/**
 * @brief Retrieves the lines of the grid-based drawing numbering system.
 * @ingroup Drawing
 * @param gridLineProc The callback function to be called to process the lines of the drawing numbering grid.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - gridLineProc is nullptr
 * 			- APIERR_BADDATABASE - The current database is not layout type
 * @remarks Use this function to enumerate the lines of the grid if the current layout uses grid-based drawing numbering. The user-defined callback function gridLineProc is called for each line of the grid.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Drawing_GetNumberingGridLines-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Drawing_GetNumberingGridLines (APINumberingGridLineProc* gridLineProc);


/**
 * @brief Returns the state of the automatic wall intersection flag.
 * @ingroup View
 * @param isOn Tells whether the automatic intersection of walls is turned on.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOPLAN - No open project.
 * 			- APIERR_BADPARS - The isOn parameter is nullptr.
 * @remarks This flag was part of the Display Options in previous (pre-10) API versions. With the separation of the Display Options from Display and Output Options, automatic intersection has started its own 'life'.
 * 			Its value can be modified with @ref ACAPI_View_ChangeAutoIntersect.
 */
__APIEXPORT GSErrCode ACAPI_View_IsAutoIntersectOn (bool* isOn);


/**
 * @brief Modifies the automatic wall intersection flag.
 * @ingroup View
 * @param isOn Turns on/off the automatic wall intersection.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOPLAN - No open project.
 * 			- APIERR_BADPARS - The isOn parameter is nullptr.
 * @remarks This flag was part of the Display Options in previous (pre-10) API versions. From API 10, it has started its own 'life'.
 * 			The current state of the flag can be queried with @ref ACAPI_View_IsAutoIntersectOn.
 */
__APIEXPORT GSErrCode ACAPI_View_ChangeAutoIntersect (bool* isOn);


/**
 * @brief Checks whether attached objects (window/door markers, drawing titles, etc.) are processed and returned during primitive decomposition.
 * @ingroup Drawing
 * @param enabled [out] True if attached objects are processed.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks Use this function to query the flag set by @ref ACAPI_Drawing_ChangeMarkerDrawingEnabled. In most cases you should query the value first, then change it for your code, then change it back to it's original value, as the example shows.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Drawing_IsMarkerDrawingEnabled-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Drawing_IsMarkerDrawingEnabled (bool* enabled);


/**
 * @brief Sets whether attached objects (window/door markers, drawing titles, etc.) should be processed and returned during primitive decomposition.
 * @ingroup Drawing
 * @param enabled [in] True if attached objects should be processed.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks In most cases you should query the value first with @ref ACAPI_Drawing_IsMarkerDrawingEnabled, then change it for your code, then change it back to it's original value, as the example shows.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Drawing_ChangeMarkerDrawingEnabled-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Drawing_ChangeMarkerDrawingEnabled (bool enabled);


/**
 * @brief Returns a copy of the current GDL globals.
 * @ingroup LibraryManagement
 * @param userGlobals [out] The object containing the GDL globals required by the GDL interpreter.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The userGlobals parameter is nullptr.
 * @remarks You can use this function to obtain the current GDL globals. Do not forget to destroy the returned pointer using @ref ACAPI_LibraryManagement_DestroyCopyOfGdlUserGlobalsHandle.
 */
__APIEXPORT GSErrCode ACAPI_LibraryManagement_CreateCopyOfGdlUserGlobalsHandle (GDL::Parameters** userGlobals);


/**
 * @brief Destroys the previously copied GDL globals handle.
 * @ingroup LibraryManagement
 * @param userGlobals [in] The object containing the GDL globals required by the GDL interpreter.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The userGlobals parameter is nullptr.
 * @remarks This function destroys the object pointer returned from @ref ACAPI_LibraryManagement_CreateCopyOfGdlUserGlobalsHandle.
 */
__APIEXPORT GSErrCode ACAPI_LibraryManagement_DestroyCopyOfGdlUserGlobalsHandle (GDL::Parameters** userGlobals);


/**
 * @brief Returns the 3D document setting default values.
 * @ingroup View
 * @param documentFrom3DDefaults [out] The default settings of 3D document database.
 * @return
 * 			- NoError - The function completed with success.
 * 			- APIERR_BADPARS - The documentFrom3DDefaults parameter is nullptr.
 * @remarks You can use this function to obtain the 3D document setting defaults.
 */
__APIEXPORT GSErrCode ACAPI_View_GetDocumentFrom3DDefaults (API_DocumentFrom3DDefaults* documentFrom3DDefaults);


/**
 * @brief Changes the 3D document setting default values.
 * @ingroup View
 * @param documentFrom3DDefaults [in] The new default values of the 3D document database.
 * @return
 * 			- NoError - The function completed with success.
 * 			- APIERR_BADPARS - The documentFrom3DDefaults parameter is nullptr.
 * @remarks You can use this function to change the 3D document setting default values.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_View_ChangeDocumentFrom3DDefaults (API_DocumentFrom3DDefaults* documentFrom3DDefaults);


/**
 * @brief Returns the 3D document settings of the specified database.
 * @ingroup View
 * @param databaseUnId [in] The database unique ID of the 3D document database to get the parameters for.
 * @param documentFrom3DType [out] The parameters.
 * @return
 * 			- NoError - The function completed with success.
 * 			- APIERR_BADDATABASE - The referred database is not a 3D document.
 * 			- APIERR_BADPARS - The dbPars or documentFrom3DType parameter is nullptr, or the settings couldn't be obtained.
 * @remarks You can use this function to obtain the 3D document settings of the specified database.
 */
__APIEXPORT GSErrCode ACAPI_View_GetDocumentFrom3DSettings (API_DatabaseUnId* databaseUnId, API_DocumentFrom3DType* documentFrom3DType);


/**
 * @brief Changes the 3D document settings of the specified database.
 * @ingroup View
 * @param databaseUnId [in] The database unique ID of the 3D document database to change parameters for.
 * @param documentFrom3DType [in] The new parameters.
 * @return
 * 			- NoError - The function completed with success.
 * 			- APIERR_BADDATABASE - The referred database is not a 3D document.
 * 			- APIERR_BADPARS - The dbPars or documentFrom3DType parameter is nullptr, or the settings couldn't be obtained.
 * @remarks You can use this function to change the 3D document settings of the specified database.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_View_ChangeDocumentFrom3DSettings (API_DatabaseUnId* databaseUnId, API_DocumentFrom3DType* documentFrom3DType);


/**
 * @brief Changes the partial structure display options for the current database.
 * @ingroup Navigator
 * @param uiStructureDisplay [out] The settings of the structure display in the current database.
 * @return
 * 			- NoError - The function completed with success.
 * 			- APIERR_NOPLAN - No plan window.
 * 			- APIERR_BADDATABASE - The current database doesn't have structure display settings.
 * 			- APIERR_BADPARS - The uiStructureDisplay parameter is nullptr
 * @remarks You can use this function to get the partial structure display settings for the current database.
 */
__APIEXPORT GSErrCode ACAPI_Navigator_GetStructureDisplay (API_UIStructureDisplay* uiStructureDisplay);


/**
 * @brief Changes the partial structure display options for the current database.
 * @ingroup Navigator
 * @param uiStructureDisplay [in] The new parameters of the structure display.
 * @return
 * 			- NoError - The function completed with success.
 * 			- APIERR_NOPLAN - No plan window.
 * 			- APIERR_BADPARS - The uiStructureDisplay parameter is nullptr
 * @remarks You can use this function to change the partial structure display settings.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_Navigator_ChangeStructureDisplay (API_UIStructureDisplay* uiStructureDisplay);


/**
 * @brief Returns if applicaton is in curtain wall editing mode.
 * @ingroup HierarchicalEditing
 * @param isInEditMode [out] Is the application in curtain wall editing mode?
 * @param editedCurtainWall [out] (optional) The GUID of the currently edited curtain wall.
 * @return
 * 			- NoError - The function completed with success.
 * 			- APIERR_BADPARS - isInEditMode is nullptr
 * @remarks You can use this function to check the state of the applicaton; many things work differently in curtain wall editing mode.
 */
__APIEXPORT GSErrCode ACAPI_HierarchicalEditing_IsInCurtainWallEditMode (bool* isInEditMode, API_Guid* editedCurtainWall = nullptr);


/**
 * @brief Returns if the current user has the specifed access right.
 * @ingroup Teamwork
 * @param accessRight [in] The access right to check.
 * @param hasRight [out] The status of the access right in question.
 * @return
 * 			- NoError - The function completed with success.
 * 			- APIERR_BADPARS - hasRight is nullptr
 * @remarks In non-teamwork mode hasRight is always true.
 * 			You can use this function to check the user's permissions.
 */
__APIEXPORT GSErrCode ACAPI_Teamwork_GetTWAccessRight (API_TWAccessRights accessRight, bool* hasRight);


/**
 * @brief Tells if Archicad is in Stair Editing mode.
 * @ingroup HierarchicalEditing
 * @param isInEditMode [out] true if Archicad is in Stair Edit mode, false otherwise.
 * @param editedStair The GUID of the stair being edited.
 * @return
 * 			- NoError - The function has completed with success.
 */
__APIEXPORT GSErrCode ACAPI_HierarchicalEditing_IsInStairEditMode (bool* isInEditMode, API_Guid* editedStair = nullptr);


/**
 * @brief Returns if applicaton is in beam editing mode.
 * @ingroup HierarchicalEditing
 * @param isInEditMode [out] Is the application in beam editing mode?
 * @param editedBeam [out] (optional) The GUID of the currently edited beam.
 * @return
 * 			- NoError - The function completed with success.
 * 			- APIERR_BADPARS - isInEditMode is nullptr
 * @remarks You can use this function to check the state of the applicaton; many things work differently in beam editing mode.
 */
__APIEXPORT GSErrCode ACAPI_HierarchicalEditing_IsInBeamEditMode (bool* isInEditMode, API_Guid* editedBeam = nullptr);


/**
 * @brief Returns if applicaton is in column editing mode.
 * @ingroup HierarchicalEditing
 * @param isInEditMode [out] Is the application in column editing mode?
 * @param editedColumn [out] (optional) The GUID of the currently edited column.
 * @return
 * 			- NoError - The function completed with success.
 * 			- APIERR_BADPARS - isInEditMode is nullptr
 * @remarks You can use this function to check the state of the applicaton; many things work differently in column editing mode.
 */
__APIEXPORT GSErrCode ACAPI_HierarchicalEditing_IsInColumnEditMode (bool* isInEditMode, API_Guid* editedColumn);


/**
 * @brief Set 'Suspend Groups' in Archicad.
 * @ingroup Grouping
 * @param suspendGroups [in] Suspend or unsuspend grouping in Archicad.
 * @return
 * 			- NoError - The function completed with success.
 * 			- APIERR_NOPLAN - No user project is open.
 * @remarks Suspend groups if you want to perform an operation on an element which is part of a group. Remember to set it
 * 			back to its previous state when you finished your operation.
 */
__APIEXPORT GSErrCode ACAPI_Grouping_ChangeSuspendGroup (bool suspendGroups);


/**
 * @brief Returns the original location of a library part.
 * @ingroup LibraryManagement
 * @param libItemIndex [in] The index of the library part.
 * @param origLocation [out] The location of the given library part.
 * @return
 * 			- NoError - The function completed with success.
 * 			- APIERR_BADPARS - `libItemIndex` or `origLocation` is nullptr
 */
__APIEXPORT GSErrCode ACAPI_LibraryManagement_GetLibPartOrigLocation (const Int32*  libItemIndex,
																			 IO::Location* origLocation);


#endif // ACAPI_ENVIRONMENT_H
