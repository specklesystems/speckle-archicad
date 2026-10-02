#pragma once

#include "APIEnvir.h"
#include "ACAPinc.h"

// ENG-10361: keep the Archicad 27 API vocabulary at the connector boundary;
// Archicad 26 dispatches these operations through its legacy API entry points.
#define ACAPI_MenuItem_RegisterMenu ACAPI_Register_Menu
#define ACAPI_MenuItem_InstallMenuHandler ACAPI_Install_MenuHandler
#define ACAPI_ProjectOperation_CatchProjectEvent ACAPI_Notify_CatchProjectEvent
#define ACAPI_Notification_CatchSelectionChange ACAPI_Notify_CatchSelectionChange
#define ACAPI_Selection_DeselectAll ACAPI_Element_DeselectAll
#define ACAPI_Selection_Select ACAPI_Element_Select
#define ACAPI_Sight_GetCurrentWindowSight ACAPI_3D_GetCurrentWindowSight
#define ACAPI_LibraryPart_RegisterAll ACAPI_LibPart_RegisterAll
#define ACAPI_Grouping_GetRootGroup ACAPI_ElementGroup_GetRootGroup

inline API_AttributeIndex ACAPI_CreateAttributeIndex(Int32 index) { return static_cast<API_AttributeIndex>(index); }

inline GSErrCode ACAPI_Attribute_GetNum(API_AttrTypeID type, GS::UInt32& count)
{
    API_AttributeIndex legacyCount = 0;
    const GSErrCode result = ACAPI_Attribute_GetNum(type, &legacyCount);
    count = static_cast<GS::UInt32>(legacyCount);
    return result;
}

inline GSErrCode ACAPI_MenuItem_GetMenuItemFlags(const API_MenuItemRef* item, GSFlags* flags)
{ return ACAPI_Interface(APIIo_GetMenuItemFlagsID, const_cast<API_MenuItemRef*>(item), flags); }
inline GSErrCode ACAPI_MenuItem_SetMenuItemFlags(const API_MenuItemRef* item, GSFlags* flags)
{ return ACAPI_Interface(APIIo_SetMenuItemFlagsID, const_cast<API_MenuItemRef*>(item), flags); }
inline GSErrCode ACAPI_Database_GetCurrentDatabase(API_DatabaseInfo* database)
{ return ACAPI_Database(APIDb_GetCurrentDatabaseID, database); }
inline GSErrCode ACAPI_Database_ChangeCurrentDatabase(API_DatabaseInfo* database)
{ return ACAPI_Database(APIDb_ChangeCurrentDatabaseID, database); }
inline GSErrCode ACAPI_Window_GetCurrentWindow(API_WindowInfo* window)
{ return ACAPI_Database(APIDb_GetCurrentWindowID, window); }
inline GSErrCode ACAPI_Window_ChangeWindow(const API_WindowInfo* window)
{ return ACAPI_Automate(APIDo_ChangeWindowID, const_cast<API_WindowInfo*>(window)); }
inline GSErrCode ACAPI_View_ShowAllIn3D()
{ return ACAPI_Automate(APIDo_ShowAllIn3DID); }
inline GSErrCode ACAPI_View_GoToView(const char* view)
{ return ACAPI_Automate(APIDo_GoToViewID, const_cast<char*>(view)); }
inline GSErrCode ACAPI_ProjectOperation_Project(API_ProjectInfo* project)
{ return ACAPI_Environment(APIEnv_ProjectID, project); }
inline GSErrCode ACAPI_ProjectSetting_GetPreferences(void* preferences, API_PrefsTypeID type)
{ return ACAPI_Environment(APIEnv_GetPreferencesID, preferences, reinterpret_cast<void*>(static_cast<GS::IntPtr>(type))); }
inline GSErrCode ACAPI_ProjectSetting_GetStorySettings(API_StoryInfo* stories)
{ return ACAPI_Environment(APIEnv_GetStorySettingsID, stories); }
inline GSErrCode ACAPI_ProjectSettings_GetSpecFolder(API_SpecFolderID* folder, IO::Location* location)
{ return ACAPI_Environment(APIEnv_GetSpecFolderID, folder, location); }
inline GSErrCode ACAPI_LibraryManagement_GetLibraries(GS::Array<API_LibraryInfo>* libraries, Int32* embeddedIndex)
{ return ACAPI_Environment(APIEnv_GetLibrariesID, libraries, embeddedIndex); }
inline GSErrCode ACAPI_LibraryManagement_DeleteEmbeddedLibItem(const IO::Location* location, bool keepFile, bool silent)
{
    return ACAPI_Environment(APIEnv_DeleteEmbeddedLibItemID, const_cast<IO::Location*>(location),
        reinterpret_cast<void*>(static_cast<GS::IntPtr>(keepFile)), reinterpret_cast<void*>(static_cast<GS::IntPtr>(silent)));
}
inline GSErrCode ACAPI_Element_GetElementInfoString(const API_Guid* element, GS::UniString* info)
{ return ACAPI_Database(APIDb_GetElementInfoStringID, const_cast<API_Guid*>(element), info); }
inline GSErrCode ACAPI_HierarchicalEditing_GetHierarchicalElementOwner(const API_Guid* element,
    const API_HierarchicalOwnerType* ownerType, API_HierarchicalElemType* elementType, API_Guid* owner)
{
    return ACAPI_Goodies(APIAny_GetHierarchicalElementOwnerID, const_cast<API_Guid*>(element),
        const_cast<API_HierarchicalOwnerType*>(ownerType), elementType, owner);
}
inline GSErrCode ACAPI_Navigator_SearchNavigatorItem(API_NavigatorItem* item, GS::Array<API_NavigatorItem>* results)
{ return ACAPI_Navigator(APINavigator_SearchNavigatorItemID, item, results); }
inline GSErrCode ACAPI_ProcessWindow_InitProcessWindow(const GS::UniString* title, Int32* phases, API_ProcessControlTypeID* control)
{
    short legacyPhases = static_cast<short>(*phases);
    return ACAPI_Interface(APIIo_InitProcessWindowID, const_cast<GS::UniString*>(title), &legacyPhases, control);
}
inline GSErrCode ACAPI_ProcessWindow_SetNextProcessPhase(const GS::UniString* title, Int32* steps, bool* showPercent)
{ return ACAPI_Interface(APIIo_SetNextProcessPhaseID, const_cast<GS::UniString*>(title), steps, showPercent); }
inline GSErrCode ACAPI_ProcessWindow_SetProcessValue(Int32* value)
{ return ACAPI_Interface(APIIo_SetProcessValueID, value); }
inline GSErrCode ACAPI_ProcessWindow_IsProcessCanceled()
{ return ACAPI_Interface(APIIo_IsProcessCanceledID); }
inline GSErrCode ACAPI_ProcessWindow_CloseProcessWindow()
{ return ACAPI_Interface(APIIo_CloseProcessWindowID); }
