#ifndef __GS_ACAPI_MIGRATION_HEADER_HPP__
#define __GS_ACAPI_MIGRATION_HEADER_HPP__

#include "ACAPinc.h"
#include "Polygon2D.hpp"

#define APIDo_LoadLibrariesID APIEnv_SetLibrariesID
#define APIDo_ShowSelectionIn3DID APIIo_ShowSelectionIn3DID
#define APIDo_ShowAllIn3DID APIIo_ShowAllIn3DID
#define APIDo_EditHierarchicalElemID APIIo_EditHierarchicalElemID
#define APIDo_CancelHierarchicalElemID APIIo_CancelHierarchicalElemID
#define APIDo_OkHierarchicalElemID APIIo_OkHierarchicalElemID


GSErrCode ACAPI_Database (API_DatabaseID code, void* par1 = nullptr, void* par2 = nullptr, void* par3 = nullptr)
{
	switch (code) {
		case APIDb_GetCurrentDatabaseID:
			return ACAPI_Database_GetCurrentDatabase (reinterpret_cast<API_DatabaseInfo*> (par1));
		case APIDb_RoomReductionsID:
			return ACAPI_Element_RoomReductions (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<RoomReductionPolyProc*> (par2));
		case APIDb_GetRVMDocumentRevisionChangesID:
			return ACAPI_Revision_GetRVMDocumentRevisionChanges (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<GS::Array<API_RVMChange>*> (par2));
		case APIDb_GetRVMDocumentRevisionsID:
			return ACAPI_Revision_GetRVMDocumentRevisions (reinterpret_cast<GS::Array<API_RVMDocumentRevision>*> (par1));
		case APIDb_GetDBUnIdFromGuidID:
			return ACAPI_Database_GetDBUnIdFromGuid (reinterpret_cast<API_Guid*> (par1), reinterpret_cast<short*> (par2), reinterpret_cast<UInt32*> (par3));
		case APIDb_DeleteDatabaseID:
			return ACAPI_Database_DeleteDatabase (reinterpret_cast<API_DatabaseInfo*> (par1));
		case APIDb_GetRVMChangeCustomSchemeID:
			return ACAPI_Revision_GetRVMChangeCustomScheme (reinterpret_cast<GS::HashTable<API_Guid, GS::UniString>*> (par1));
		case APIDb_GetHotlinkNodeID:
			return ACAPI_Hotlink_GetHotlinkNode (reinterpret_cast<API_HotlinkNode*> (par1), reinterpret_cast<bool*> (par2));
		case APIDb_ModifyDatabaseID:
			return ACAPI_Database_ModifyDatabase (reinterpret_cast<API_DatabaseInfo*> (par1));
		case APIDb_GetGuidFromDBUnIdID:
			return ACAPI_Database_GetGuidFromDBUnId (reinterpret_cast<short*> (par1), reinterpret_cast<UInt32*> (par2), reinterpret_cast<API_Guid*> (par3));
		case APIDb_GetWorksheetDatabasesID:
			return ACAPI_Database_GetWorksheetDatabases (reinterpret_cast<API_DatabaseUnId**> (par1), reinterpret_cast<GS::Array<API_DatabaseUnId>*> (par2));
		case APIDb_GetRVMLayoutCurrentRevisionChangesID:
			return ACAPI_Revision_GetRVMLayoutCurrentRevisionChanges (reinterpret_cast<const API_DatabaseUnId*> (par1), reinterpret_cast<GS::Array<API_RVMChange>*> (par2));
		case APIDb_UpdateHotlinkCacheID:
			return ACAPI_Hotlink_UpdateHotlinkCache (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<API_HotlinkCacheGenerator*> (par2));
		case APIDb_CheckWindowValidatorID:
			return ACAPI_Database_CheckWindowValidator (reinterpret_cast<const API_WindowValidatorInfo*> (par1), reinterpret_cast<bool*> (par2));
		case APIDb_GetCurrentWindowID:
			return ACAPI_Window_GetCurrentWindow (reinterpret_cast<API_WindowInfo*> (par1));
		case APIDb_RebuildCurrentDatabaseID:
			return ACAPI_Database_RebuildCurrentDatabase ();
		case APIDb_GetElementFromAnywhereID:
			return ACAPI_Element_GetElementFromAnywhere (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<API_Element*> (par2));
		case APIDb_GetHotlinkInstancesID:
			return ACAPI_Hotlink_GetHotlinkInstances (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<GS::Array<API_Guid>*> (par2));
		case APIDb_ResetCurrentDatabaseID:
			return ACAPI_Window_ResetCurrentDatabase ();
		case APIDb_StoreViewSettingsID:
			return ACAPI_View_StoreViewSettings (static_cast<bool> (reinterpret_cast<GS::IntPtr> (par1)));
		case APIDb_ReSetZoomID:
			return ACAPI_View_ResetZoom (reinterpret_cast<short*> (par1));
		case APIDb_GetRVMElemChangeIdsID:
			return ACAPI_Revision_GetRVMElemChangeIds (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<GS::Array<GS::UniString>*> (par2));
		case APIDb_GetMasterLayoutDatabasesID:
			return ACAPI_Database_GetMasterLayoutDatabases (reinterpret_cast<API_DatabaseUnId**> (par1), reinterpret_cast<GS::Array<API_DatabaseUnId>*> (par2));
		case APIDb_GetHotLinkOwnerID:
			return ACAPI_Hotlink_GetHotLinkOwner (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<API_Guid*> (par2));
		case APIDb_StopDrawingDataID:
			return ACAPI_Drawing_StopDrawingData (reinterpret_cast<GSPtr*> (par1), reinterpret_cast<API_Box*> (par2));
		case APIDb_GetSubSetDefaultID:
			return ACAPI_Navigator_GetSubSetDefault (reinterpret_cast<API_SubSet*> (par1));
		case APIDb_GetDrawingScaleID:
			return ACAPI_Drawing_GetDrawingScale (reinterpret_cast<double*> (par1));
		case APIDb_DrawOrderGetNextID:
			return ACAPI_DrawOrder_DrawOrderGetNext (static_cast<API_ElemFilterFlags> (reinterpret_cast<GS::IntPtr> (par1)), reinterpret_cast<API_Elem_Head*> (par2));
		case APIDb_ModifyHotlinkNodeID:
			return ACAPI_Hotlink_ModifyHotlinkNode (reinterpret_cast<API_HotlinkNode*> (par1));
		case APIDb_BreakHotlinkNodeID:
			return ACAPI_Hotlink_BreakHotlinkNode (reinterpret_cast<const API_Guid*> (par1));
		case APIDb_SetActualRenovationFilterID:
			return ACAPI_Renovation_SetActualRenovationFilter (reinterpret_cast<const API_Guid*> (par1));
		case APIDb_CalcBoundsID:
			return ACAPI_Element_CalcBounds (reinterpret_cast<const API_Elem_Head*> (par1), reinterpret_cast<API_Box3D*> (par2));
		case APIDb_GetRenovationFiltersID:
			return ACAPI_Renovation_GetRenovationFilters (reinterpret_cast<GS::Array<API_Guid>*> (par1));
		case APIDb_GetActualRenovationFilterID:
			return ACAPI_Renovation_GetActualRenovationFilter (reinterpret_cast<API_Guid*> (par1));
		case APIDb_DrawOrderInitID:
			return ACAPI_DrawOrder_DrawOrderInit ();
		case APIDb_GetRVMIssueDocumentRevisionsID:
			return ACAPI_Revision_GetRVMIssueDocumentRevisions (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<GS::Array<API_RVMDocumentRevision>*> (par2));
		case APIDb_GetRVMChangesFromChangeIdsID:
			return ACAPI_Revision_GetRVMChangesFromChangeIds (reinterpret_cast<const GS::Array<GS::UniString>*> (par1), reinterpret_cast<GS::Array<API_RVMChange>*> (par2));
		case APIDb_GetOwnWindowsID:
			return ACAPI_Window_GetOwnWindows (reinterpret_cast<API_WindowTypeID*> (par1), reinterpret_cast<GS::Array<API_Guid>*> (par2));
		case APIDb_RefreshElementID:
			return ACAPI_Element_RefreshElement (reinterpret_cast<API_Elem_Head*> (par1), reinterpret_cast<bool*> (par2));
		case APIDb_GetRVMChangesID:
			return ACAPI_Revision_GetRVMChanges (reinterpret_cast<GS::Array<API_RVMChange>*> (par1));
		case APIDb_GetDrawingLinkID:
			return ACAPI_Drawing_GetDrawingLink (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<API_DrawingLinkInfo*> (par2));
		case APIDb_GetExtent3DID:
			return ACAPI_Element_GetExtent3D (reinterpret_cast<API_Box3D*> (par1));
		case APIDb_IsCWPanelDegenerateID:
			return ACAPI_CurtainWall_IsCWPanelDegenerate (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<bool*> (par2));
		case APIDb_GetRVMIssuesID:
			return ACAPI_Revision_GetRVMIssues (reinterpret_cast<GS::Array<API_RVMIssue>*> (par1));
		case APIDb_GetExtentID:
			return ACAPI_Element_GetExtent (reinterpret_cast<API_Box*> (par1), reinterpret_cast<API_DatabaseUnId*> (par2));
		case APIDb_SetZoomID:
			return ACAPI_View_SetZoom (reinterpret_cast<API_Box*> (par1), reinterpret_cast<API_Tranmat*> (par2));
		case APIDb_GetDocumentFrom3DDatabasesID:
			return ACAPI_Database_GetDocumentFrom3DDatabases (reinterpret_cast<API_DatabaseUnId**> (par1), reinterpret_cast<GS::Array<API_DatabaseUnId>*> (par2));
		case APIDb_ChangeRVMIssueID:
			return ACAPI_Revision_ChangeRVMIssue (reinterpret_cast<API_RVMIssue*> (par1));
		case APIDb_GetHotlinkNodeTreeID:
			return ACAPI_Hotlink_GetHotlinkNodeTree (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<GS::HashTable<API_Guid, GS::Array<API_Guid>>*> (par2));
		case APIDb_GetRVMChangeFirstIssueID:
			return ACAPI_Revision_GetRVMChangeFirstIssue (reinterpret_cast<const GS::UniString*> (par1), reinterpret_cast<API_RVMIssue*> (par2));
		case APIDb_SetWindowIdID:
			return ACAPI_Window_SetWindowId (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<const API_Guid*> (par2));
		case APIDb_GetElementCategoryValuesID:
			return ACAPI_Category_GetElementCategoryValues (reinterpret_cast<const API_ElemCategory*> (par1), reinterpret_cast<GS::Array<API_ElemCategoryValue>*> (par2));
		case APIDb_GetGridSettingsID:
			return ACAPI_Window_GetGridSettings (reinterpret_cast<API_GridType*> (par1));
		case APIDb_RedrawCurrentDatabaseID:
			return ACAPI_Database_RedrawCurrentDatabase ();
		case APIDb_InitCreationOrderTableID:
			return ACAPI_DrawOrder_InitCreationOrderTable (reinterpret_cast<API_ElemFilter*> (par1));
		case APIDb_GetInteriorElevationDatabasesID:
			return ACAPI_Database_GetInteriorElevationDatabases (reinterpret_cast<API_DatabaseUnId**> (par1), reinterpret_cast<GS::Array<API_DatabaseUnId>*> (par2));
		case APIDb_GetHotlinkRootNodeGuidID:
			return ACAPI_Hotlink_GetHotlinkRootNodeGuid (reinterpret_cast<const API_HotlinkTypeID*> (par1), reinterpret_cast<API_Guid*> (par2));
		case APIDb_GetElementCategoriesID:
			return ACAPI_Category_GetElementCategories (reinterpret_cast<GS::Array<API_ElemCategory>*> (par1));
		case APIDb_GetElementURLRefID:
			return ACAPI_Element_GetElementURLRef (reinterpret_cast<API_Elem_Head*> (par1), reinterpret_cast<API_ElemURLRef*> (par2));
		case APIDb_RebuildWindowValidatorID:
			return ACAPI_Database_RebuildWindowValidator (reinterpret_cast<const API_WindowValidatorInfo*> (par1));
		case APIDb_GetSectionDatabasesID:
			return ACAPI_Database_GetSectionDatabases (reinterpret_cast<API_DatabaseUnId**> (par1), reinterpret_cast<GS::Array<API_DatabaseUnId>*> (par2));
		case APIDb_StartClippingSessionID:
			return ACAPI_Database_StartClippingSession ();
		case APIDb_CheckDrawingStatusID:
			return ACAPI_Drawing_CheckDrawingStatus (reinterpret_cast<API_Guid*> (par1), reinterpret_cast<Int32*> (par2));
		case APIDb_GetElevationDatabasesID:
			return ACAPI_Database_GetElevationDatabases (reinterpret_cast<API_DatabaseUnId**> (par1), reinterpret_cast<GS::Array<API_DatabaseUnId>*> (par2));
		case APIDb_DrawStoryControlID:
			return ACAPI_DrawingPrimitive_DrawStoryControl (reinterpret_cast<API_DatabaseUnId*> (par1), reinterpret_cast<ShapePrimsProc*> (par2));
		case APIDb_PointToCoordID:
			return ACAPI_View_PointToCoord (reinterpret_cast<API_Point*> (par1), reinterpret_cast<API_Coord*> (par2));
		case APIDb_DrawElementID:
			return ACAPI_Element_DrawElement (reinterpret_cast<API_Elem_Head*> (par1), static_cast<UInt32> (reinterpret_cast<GS::IntPtr> (par2)));
		case APIDb_NewDatabaseID:
			return ACAPI_Database_NewDatabase (reinterpret_cast<API_DatabaseInfo*> (par1), reinterpret_cast<const API_Guid*> (par2), reinterpret_cast<const API_Guid*> (par3));
		case APIDb_ChangeCurrentDatabaseID:
			return ACAPI_Database_ChangeCurrentDatabase (reinterpret_cast<API_DatabaseInfo*> (par1));
		case APIDb_StartDrawingDataID:
			return ACAPI_Drawing_StartDrawingData (reinterpret_cast<double*> (par1), reinterpret_cast<API_PenType**> (par2));
		case APIDb_SetElementURLRefID:
			return ACAPI_Element_SetElementURLRef (reinterpret_cast<API_Elem_Head*> (par1), reinterpret_cast<API_ElemURLRef*> (par2));
		case APIDb_JsonQueryID:
			return ACAPI_Database_JsonQuery (reinterpret_cast<const GS::UniString*> (par1), reinterpret_cast<GS::UniString*> (par2));
		case APIDb_DoClipID:
			return ACAPI_Database_DoClip (reinterpret_cast<API_Region*> (par1), reinterpret_cast<API_ClipTran*> (par2));
		case APIDb_GetFullDrawingContentBoxID:
			return ACAPI_Drawing_GetFullDrawingContentBox (reinterpret_cast<API_Box*> (par1), reinterpret_cast<const API_Guid*> (par2));
		case APIDb_GetHotlinkProxyElementTableID:
			return ACAPI_Hotlink_GetHotlinkProxyElementTable (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<GS::HashTable<API_Guid, API_Guid>*> (par2));
		case APIDb_GetZoomID:
			return ACAPI_View_GetZoom (reinterpret_cast<API_Box*> (par1), reinterpret_cast<API_Tranmat*> (par2));
		case APIDb_DeleteHotlinkNodeID:
			return ACAPI_Hotlink_DeleteHotlinkNode (reinterpret_cast<const API_Guid*> (par1));
		case APIDb_ChangeGridSettingsID:
			return ACAPI_Window_ChangeGridSettings (reinterpret_cast<API_GridType*> (par1));
		case APIDb_DestroyWindowValidatorID:
			return ACAPI_Window_DestroyWindowValidator (reinterpret_cast<const API_Guid*> (par1));
		case APIDb_GetDatabaseInfoID:
			return ACAPI_Window_GetDatabaseInfo (reinterpret_cast<API_DatabaseInfo*> (par1), reinterpret_cast<API_DatabaseUnId*> (par2));
		case APIDb_CreateSubSetID:
			return ACAPI_Navigator_CreateSubSet (reinterpret_cast<const API_SubSet*> (par1), reinterpret_cast<const API_Guid*> (par2));
		case APIDb_GetElementInfoStringID:
			return ACAPI_Element_GetElementInfoString (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<GS::UniString*> (par2));
		case APIDb_DisposeCreationOrderTableID:
			return ACAPI_DrawOrder_DisposeCreationOrderTable ();
		case APIDb_GetCompoundInfoStringID:
			return ACAPI_Element_GetCompoundInfoString (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<GS::UniString*> (par2));
		case APIDb_GetContainingDatabaseID:
			return ACAPI_Database_GetContainingDatabase (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<API_DatabaseInfo*> (par2));
		case APIDb_DrawOrderTermID:
			return ACAPI_DrawOrder_DrawOrderTerm ();
		case APIDb_GetOffsetID:
			return ACAPI_ProjectSetting_GetOffset (reinterpret_cast<API_Coord*> (par1));
		case APIDb_CloseWindowID:
			return ACAPI_Window_CloseWindow (reinterpret_cast<API_WindowInfo*> (par1));
		case APIDb_ChangeElementInfoStringID:
			return ACAPI_Element_ChangeElementInfoString (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<const GS::UniString*> (par2));
		case APIDb_GetLayoutBookID:
			return ACAPI_Navigator_GetLayoutBook (reinterpret_cast<API_LayoutBook*> (par1));
		case APIDb_GetTWOwnerID:
			return ACAPI_Teamwork_GetTWOwner (reinterpret_cast<API_DatabaseUnId*> (par1), reinterpret_cast<short*> (par2));
		case APIDb_BuildWindowValidatorID:
			return ACAPI_Database_BuildWindowValidator (reinterpret_cast<const API_WindowValidatorInfo*> (par1));
		case APIDb_GetHotlinkNodesID:
			return ACAPI_Hotlink_GetHotlinkNodes (reinterpret_cast<const API_HotlinkTypeID*> (par1), reinterpret_cast<GS::Array<API_Guid>*> (par2), reinterpret_cast<bool*> (par3));
		case APIDb_ResetCurrentWindowID:
			return ACAPI_Window_ResetCurrentWindow ();
		case APIDb_AddTextWindowContentID:
			return ACAPI_Window_AddTextWindowContent (reinterpret_cast<API_WindowInfo*> (par1), reinterpret_cast<const char*> (par2), reinterpret_cast<const GS::UniString*> (par3));
		case APIDb_NewWindowID:
			return ACAPI_Window_NewWindow (reinterpret_cast<API_NewWindowPars*> (par1), reinterpret_cast<APICustomWindowHandlerProc*> (par2));
		case APIDb_CreateHotlinkNodeID:
			return ACAPI_Hotlink_CreateHotlinkNode (reinterpret_cast<API_HotlinkNode*> (par1));
		case APIDb_ChangeDrawingScaleID:
			return ACAPI_Drawing_ChangeDrawingScale (reinterpret_cast<double*> (par1), static_cast<bool> (reinterpret_cast<GS::IntPtr> (par2)));
		case APIDb_GetSubSetID:
			return ACAPI_Navigator_GetSubSet (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<API_SubSet*> (par2));
		case APIDb_GetLocOrigoID:
			return ACAPI_Database_GetLocOrigo (reinterpret_cast<API_Coord3D*> (par1));
		case APIDb_GetRVMIssueCustomSchemeID:
			return ACAPI_Revision_GetRVMIssueCustomScheme (reinterpret_cast<GS::HashTable<API_Guid, GS::UniString>*> (par1));
		case APIDb_GetLayoutDatabasesID:
			return ACAPI_Database_GetLayoutDatabases (reinterpret_cast<API_DatabaseUnId**> (par1), reinterpret_cast<GS::Array<API_DatabaseUnId>*> (par2));
		case APIDb_GetDetailDatabasesID:
			return ACAPI_Database_GetDetailDatabases (reinterpret_cast<API_DatabaseUnId**> (par1), reinterpret_cast<GS::Array<API_DatabaseUnId>*> (par2));
		case APIDb_GetHotlinkSourceStatusID:
			return ACAPI_Hotlink_GetHotlinkSourceStatus (reinterpret_cast<const IO::Location*> (par1), reinterpret_cast<API_HotlinkSourceStatus*> (par2));
		case APIDb_StopClippingSessionID:
			return ACAPI_Database_StopClippingSession ();
		case APIDb_CreationOrderGetNextID:
			return ACAPI_DrawOrder_CreationOrderGetNext (reinterpret_cast<API_Guid*> (par1));
		case APIDb_Switch3DSightID:
			return ACAPI_Sight_Switch3DSight (static_cast<API_3DSightID> (reinterpret_cast<GS::IntPtr> (par1)));
		case APIDb_CoordToPointID:
			return ACAPI_View_CoordToPoint (reinterpret_cast<API_Coord*> (par1), reinterpret_cast<API_Point*> (par2));
		default:
			return APIERR_NOTSUPPORTED;
	}
}


GSErrCode ACAPI_Environment (API_EnvironmentID code, void* par1 = nullptr, void* par2 = nullptr, void* par3 = nullptr)
{
	switch (code) {
		case APIEnv_ProjectSharingID:
			return ACAPI_Teamwork_ProjectSharing (reinterpret_cast<API_SharingInfo*> (par1));
		case APIEnv_GetPreferencesID:
			return ACAPI_ProjectSetting_GetPreferences (reinterpret_cast<void*> (par1), static_cast<API_PrefsTypeID> (reinterpret_cast<GS::IntPtr> (par2)));
		case APIEnv_GetRenderingSetsID:
			return ACAPI_Rendering_GetRenderingSets (reinterpret_cast<void*> (par1), static_cast<API_RendSetTypeID> (reinterpret_cast<GS::IntPtr> (par2)), reinterpret_cast<const GS::UniString*> (par3));
		case APIEnv_SetCurrent3DStyleID:
			return ACAPI_View_SetCurrent3DStyle (reinterpret_cast<const GS::UniString*> (par1));
		case APIEnv_SetSurveyPointLockedID:
			return ACAPI_SurveyPoint_SetSurveyPointLocked (reinterpret_cast<bool*> (par1));
		case APIEnv_CreateFolderInLibraryID:
			return ACAPI_LibraryManagement_CreateFolderInLibrary (reinterpret_cast<const IO::Location*> (par1));
		case APIEnv_ChangeRenderingSetsID:
			return ACAPI_Rendering_ChangeRenderingSets (reinterpret_cast<void*> (par1), static_cast<API_RendSetTypeID> (reinterpret_cast<GS::IntPtr> (par2)));
		case APIEnv_GetPrinterParsID:
			return ACAPI_ProjectOperation_GetPrinterPars (reinterpret_cast<API_PrintPars*> (par1));
		case APIEnv_ApplicationID:
			return ACAPI_AddOnIdentification_Application (reinterpret_cast<API_ServerApplicationInfo*> (par1));
		case APIEnv_CopyFilesIntoLibraryID:
			return ACAPI_LibraryManagement_CopyFilesIntoLibrary (reinterpret_cast<const IO::Location*> (par1), reinterpret_cast<const GS::Array<IO::Location>*> (par2), reinterpret_cast<const bool*> (par3));
		case APIEnv_GetGhostStorySettingsID:
			return ACAPI_View_GetGhostStorySettings (reinterpret_cast<API_GhostStoryType*> (par1));
		case APIEnv_IsSurveyPointLockedID:
			return ACAPI_SurveyPoint_IsSurveyPointLocked (reinterpret_cast<bool*> (par1));
		case APIEnv_GetMainWindowHWNDID:
		{
#if defined (WINDOWS)			// use ACAPI_GetMainWindow instead
			if (par1 != nullptr)
				(*(HWND*) par1) = ACAPI_GetMainWindow ();
			return NoError;
#else
			return APIERR_BADID;
#endif
		}
		case APIEnv_Change3DImageSetsID:
			return ACAPI_View_Change3DImageSets (reinterpret_cast<API_3DFilterAndCutSettings*> (par1), reinterpret_cast<bool*> (par2));
		case APIEnv_Create3DStyleID:
			return ACAPI_View_Create3DStyle (reinterpret_cast<API_3DStyle*> (par1));
		case APIEnv_IsInColumnEditModeID:
			return ACAPI_HierarchicalEditing_IsInColumnEditMode (reinterpret_cast<bool*> (par1), reinterpret_cast<API_Guid*> (par2));
		case APIEnv_IsAutoGroupOnID:
			return ACAPI_View_IsAutoGroupOn (reinterpret_cast<bool*> (par1));
		case APIEnv_GetDocumentFrom3DDefaultsID:
			return ACAPI_View_GetDocumentFrom3DDefaults (reinterpret_cast<API_DocumentFrom3DDefaults*> (par1));
		case APIEnv_GetSpecFolderID:
			return ACAPI_ProjectSettings_GetSpecFolder (reinterpret_cast<API_SpecFolderID*> (par1), reinterpret_cast<IO::Location*> (par2));
		case APIEnv_GetConvertedUnitValueID:
			return ACAPI_Conversion_GetConvertedUnitValue (reinterpret_cast<API_UnitConversionData*> (par1));
		case APIEnv_DeleteGhostRecordID:
			return ACAPI_View_DeleteGhostRecord (reinterpret_cast<const API_GhostRecord*> (par1));
		case APIEnv_SetPreferencesID:
			return ACAPI_ProjectSetting_SetPreferences (reinterpret_cast<void*> (par1), static_cast<API_PrefsTypeID> (reinterpret_cast<GS::IntPtr> (par2)));
		case APIEnv_ChangeCurrLayerCombID:
			return ACAPI_Navigator_ChangeCurrLayerComb (reinterpret_cast<API_AttributeIndex*> (par1));
		case APIEnv_GetStructureDisplayID:
			return ACAPI_Navigator_GetStructureDisplay (reinterpret_cast<API_UIStructureDisplay*> (par1));
		case APIEnv_OverwriteLibPartID:
			return ACAPI_LibraryManagement_OverwriteLibPart (static_cast<bool> (reinterpret_cast<GS::IntPtr> (par1)));
		case APIEnv_ChangeMarkerDrawingEnabledID:
			return ACAPI_Drawing_ChangeMarkerDrawingEnabled (static_cast<bool> (reinterpret_cast<GS::IntPtr> (par1)));
		case APIEnv_CanChangePlaceSetsID:
			return ACAPI_GeoLocation_CanChangePlaceSets (reinterpret_cast<bool*> (par1));
		case APIEnv_Get3DImageSetsID:
			return ACAPI_View_Get3DImageSets (reinterpret_cast<API_3DFilterAndCutSettings*> (par1));
		case APIEnv_GetShowHideStateID:
			return ACAPI_View_GetShowHideState (reinterpret_cast<bool*> (par1));
		case APIEnv_GetStorySettingsID:
			return ACAPI_ProjectSetting_GetStorySettings (reinterpret_cast<API_StoryInfo*> (par1), static_cast<UInt32> (reinterpret_cast<GS::IntPtr> (par2)));
		case APIEnv_IsSuspendGroupOnID:
			return ACAPI_View_IsSuspendGroupOn (reinterpret_cast<bool*> (par1));
		case APIEnv_ChangeProjectNotesID:
			return ACAPI_ProjectSetting_ChangeProjectNotes (reinterpret_cast<API_ProjectNoteInfo*> (par1));
		case APIEnv_SetSurveyPointVisibilityID:
			return ACAPI_SurveyPoint_SetSurveyPointVisibility (reinterpret_cast<bool*> (par1));
		case APIEnv_GetViewOptionsID:
			return ACAPI_Navigator_GetViewOptions (reinterpret_cast<API_ViewOptions*> (par1), reinterpret_cast<short*> (par2));
		case APIEnv_GetLibPartRefGuidID:
			return ACAPI_LibraryPart_GetLibPartRefGuid (reinterpret_cast<const IO::Location*> (par1), reinterpret_cast<API_Guid*> (par2));
		case APIEnv_DestroyCopyOfGdlUserGlobalsHandleID:
			return ACAPI_LibraryManagement_DestroyCopyOfGdlUserGlobalsHandle (reinterpret_cast<GDL::Parameters**> (par1));
		case APIEnv_Get3DStyleID:
			return ACAPI_View_Get3DStyle (reinterpret_cast<API_3DStyle*> (par1));
		case APIEnv_GetGDLDateID:
			return ACAPI_LibraryManagement_GetGDLDate (reinterpret_cast<Int32*> (par1));
		case APIEnv_ChangeGDLDateID:
			return ACAPI_LibraryManagement_ChangeGDLDate (reinterpret_cast<Int32*> (par1));
		case APIEnv_ChangeDocumentFrom3DSettingsID:
			return ACAPI_View_ChangeDocumentFrom3DSettings (reinterpret_cast<API_DatabaseUnId*> (par1), reinterpret_cast<API_DocumentFrom3DType*> (par2));
		case APIEnv_GetLibPartOrigLocationID:
			return ACAPI_LibraryManagement_GetLibPartOrigLocation (reinterpret_cast<const Int32*> (par1), reinterpret_cast<IO::Location*> (par2));
		case APIEnv_GetProjectNotesID:
			return ACAPI_ProjectSetting_GetProjectNotes (reinterpret_cast<API_ProjectNoteInfo*> (par1));
		case APIEnv_GetToolBoxInfoID:
			return ACAPI_Toolbox_GetToolBoxInfo (reinterpret_cast<API_ToolBoxInfo*> (par1), static_cast<bool> (reinterpret_cast<GS::IntPtr> (par2)));
		case APIEnv_GetMiscAppInfoID:
			return ACAPI_ProjectOperation_GetMiscAppInfo (reinterpret_cast<API_MiscAppInfo*> (par1));
		case APIEnv_GetToolBoxModeID:
			return ACAPI_Toolbox_GetToolBoxMode (reinterpret_cast<API_ToolBoxItem*> (par1));
		case APIEnv_GetPlaceSetsID:
			return ACAPI_GeoLocation_GetPlaceSets (reinterpret_cast<API_PlaceInfo*> (par1));
		case APIEnv_NewLibDialID:
			return ACAPI_LibraryManagement_NewLibDial (reinterpret_cast<char*> (par1), reinterpret_cast<IO::Location*> (par2));
		case APIEnv_IsAutoIntersectOnID:
			return ACAPI_View_IsAutoIntersectOn (reinterpret_cast<bool*> (par1));
		case APIEnv_GetCurrPenSetID:
			return ACAPI_Attribute_GetCurrPenSet (reinterpret_cast<API_AttributeIndex*> (par1));
		case APIEnv_ChangeStructureDisplayID:
			return ACAPI_Navigator_ChangeStructureDisplay (reinterpret_cast<API_UIStructureDisplay*> (par1));
		case APIEnv_GetCurrLayerCombID:
			return ACAPI_Navigator_GetCurrLayerComb (reinterpret_cast<API_AttributeIndex*> (par1));
		case APIEnv_CreateLayoutID:
			return ACAPI_Navigator_CreateLayout (reinterpret_cast<API_LayoutInfo*> (par1), reinterpret_cast<API_DatabaseUnId*> (par2), reinterpret_cast<API_Guid*> (par3));
		case APIEnv_ChangeSuspendGroupID:
			return ACAPI_Grouping_ChangeSuspendGroup (static_cast<bool> (reinterpret_cast<GS::IntPtr> (par1)));
		case APIEnv_CreateCopyOfGdlUserGlobalsHandleID:
			return ACAPI_LibraryManagement_CreateCopyOfGdlUserGlobalsHandle (reinterpret_cast<GDL::Parameters**> (par1));
		case APIEnv_IsInBeamEditModeID:
			return ACAPI_HierarchicalEditing_IsInBeamEditMode (reinterpret_cast<bool*> (par1), reinterpret_cast<API_Guid*> (par2));
		case APIEnv_GetLibrariesID:
			return ACAPI_LibraryManagement_GetLibraries (reinterpret_cast<GS::Array<API_LibraryInfo>*> (par1), reinterpret_cast<Int32*> (par2));
		case APIEnv_GetMiscPlotterInfoID:
			return ACAPI_ProjectOperation_GetMiscPlotterInfo (reinterpret_cast<API_MiscPlotterInfo*> (par1));
		case APIEnv_SetToolBoxModeID:
			return ACAPI_Toolbox_SetToolBoxMode (reinterpret_cast<API_ToolBoxItem*> (par1));
		case APIEnv_ChangeDocumentFrom3DDefaultsID:
			return ACAPI_View_ChangeDocumentFrom3DDefaults (reinterpret_cast<API_DocumentFrom3DDefaults*> (par1));
		case APIEnv_ChangeStorySettingsID:
			return ACAPI_ProjectSetting_ChangeStorySettings (reinterpret_cast<API_StoryCmdType*> (par1));
		case APIEnv_CheckLibrariesID:
			return ACAPI_LibraryManagement_CheckLibraries ();
		case APIEnv_IsInStairEditModeID:
			return ACAPI_HierarchicalEditing_IsInStairEditMode (reinterpret_cast<bool*> (par1), reinterpret_cast<API_Guid*> (par2));
		case APIEnv_ChangePlaceSetsID:
			return ACAPI_GeoLocation_ChangePlaceSets (reinterpret_cast<API_PlaceInfo*> (par1));
		case APIEnv_GetSurveyPointTransformationID:
			return ACAPI_SurveyPoint_GetSurveyPointTransformation (reinterpret_cast<API_Tranmat*> (par1));
		case APIEnv_ChangeAutoIntersectID:
			return ACAPI_View_ChangeAutoIntersect (reinterpret_cast<bool*> (par1));
		case APIEnv_ChangeLayoutSetsID:
			return ACAPI_Navigator_ChangeLayoutSets (reinterpret_cast<const API_LayoutInfo*> (par1), reinterpret_cast<API_DatabaseUnId*> (par2));
		case APIEnv_DeleteEmbeddedLibItemsID:
			return ACAPI_LibraryManagement_DeleteEmbeddedLibItems (reinterpret_cast<const GS::Array<IO::Location>*> (par1), static_cast<bool> (reinterpret_cast<GS::IntPtr> (par2)), static_cast<bool> (reinterpret_cast<GS::IntPtr> (par3)));
		case APIEnv_GetMagicWandSetsID:
			return ACAPI_UserInput_GetMagicWandSets (reinterpret_cast<API_MagicWandInfo*> (par1));
		case APIEnv_CreateGhostRecordID:
			return ACAPI_View_CreateGhostRecord (reinterpret_cast<const API_GhostRecord*> (par1));
		case APIEnv_ChangeShowHideStateID:
			return ACAPI_View_ChangeShowHideState (reinterpret_cast<bool*> (par1));
		case APIEnv_IsSurveyPointVisibleID:
			return ACAPI_SurveyPoint_IsSurveyPointVisible (reinterpret_cast<bool*> (par1));
		case APIEnv_IsMarkerDrawingEnabledID:
			return ACAPI_Drawing_IsMarkerDrawingEnabled (reinterpret_cast<bool*> (par1));
		case APIEnv_GetRenderingSceneNamesID:
			return ACAPI_Rendering_GetRenderingSceneNames (reinterpret_cast<GS::Array<GS::UniString>*> (par1));
		case APIEnv_AddLibrariesID:
			return ACAPI_LibraryManagement_AddLibraries (reinterpret_cast<IO::Location*> (par1));
		case APIEnv_GetGhostRecordID:
			return ACAPI_View_GetGhostRecord (reinterpret_cast<const API_DatabaseUnId*> (par1), reinterpret_cast<API_GhostRecord*> (par2));
		case APIEnv_Get3DProjectionSetsID:
			return ACAPI_View_Get3DProjectionSets (reinterpret_cast<API_3DProjectionInfo*> (par1));
		case APIEnv_GetLayoutSetsID:
			return ACAPI_Navigator_GetLayoutSets (reinterpret_cast<API_LayoutInfo*> (par1), reinterpret_cast<API_DatabaseUnId*> (par2), reinterpret_cast<const ULong*> (par3));
		case APIEnv_GetGeoLocationID:
			return ACAPI_GeoLocation_GetGeoLocation (reinterpret_cast<API_GeoLocation*> (par1));
		case APIEnv_SetLibrariesID:
			return ACAPI_LibraryManagement_SetLibraries (reinterpret_cast<const GS::Array<API_LibraryInfo>*> (par1));
		case APIEnv_Get3DWindowSetsID:
			return ACAPI_View_Get3DWindowSets (reinterpret_cast<API_3DWindowInfo*> (par1));
		case APIEnv_ChangeGhostRecordID:
			return ACAPI_View_ChangeGhostRecord (reinterpret_cast<const API_GhostRecord*> (par1));
		case APIEnv_GetDocumentFrom3DSettingsID:
			return ACAPI_View_GetDocumentFrom3DSettings (reinterpret_cast<API_DatabaseUnId*> (par1), reinterpret_cast<API_DocumentFrom3DType*> (par2));
		case APIEnv_GetTWAccessRightID:
			return ACAPI_Teamwork_GetTWAccessRight (static_cast<API_TWAccessRights> (reinterpret_cast<GS::IntPtr> (par1)), reinterpret_cast<bool*> (par2));
		case APIEnv_GetExportToleranceID:
			return ACAPI_ProjectSetting_GetExportTolerance (reinterpret_cast<double*> (par1));
		case APIEnv_Get3DCuttingPlanesID:
			return ACAPI_View_Get3DCuttingPlanes (reinterpret_cast<API_3DCutPlanesInfo*> (par1));
		case APIEnv_Get3DStyleListID:
			return ACAPI_View_Get3DStyleList (reinterpret_cast<GS::Array<GS::UniString>*> (par1), reinterpret_cast<GS::UniString*> (par2));
		case APIEnv_SetCurrentRenderingSceneID:
			return ACAPI_Rendering_SetCurrentRenderingScene (reinterpret_cast<const GS::UniString*> (par1));
		case APIEnv_Change3DWindowSetsID:
			return ACAPI_View_Change3DWindowSets (reinterpret_cast<API_3DWindowInfo*> (par1));
		case APIEnv_SetGeoLocationID:
			return ACAPI_GeoLocation_SetGeoLocation (reinterpret_cast<API_GeoLocation*> (par1));
		case APIEnv_ChangeViewOptionsID:
			return ACAPI_Navigator_ChangeViewOptions (reinterpret_cast<API_ViewOptions*> (par1), reinterpret_cast<short*> (par2));
		case APIEnv_ProjectID:
			return ACAPI_ProjectOperation_Project (reinterpret_cast<API_ProjectInfo*> (par1));
		case APIEnv_GetSunSetsID:
			return ACAPI_GeoLocation_GetSunSets (reinterpret_cast<API_SunInfo*> (par1));
		case APIEnv_GetNumberingGridLinesID:
			return ACAPI_Drawing_GetNumberingGridLines (reinterpret_cast<APINumberingGridLineProc*> (par1));
		case APIEnv_Change3DProjectionSetsID:
			return ACAPI_View_Change3DProjectionSets (reinterpret_cast<API_3DProjectionInfo*> (par1), reinterpret_cast<bool*> (par2));
		case APIEnv_ResetLibrariesID:
			return ACAPI_LibraryManagement_ResetLibraries ();
		case APIEnv_GetLibPartUnIDStrID:
			return ACAPI_LibraryPart_GetLibPartUnIDStr (reinterpret_cast<const IO::Location*> (par1), reinterpret_cast<char*> (par2));
		case APIEnv_Change3DStyleID:
			return ACAPI_View_Change3DStyle (reinterpret_cast<API_3DStyle*> (par1));
		case APIEnv_GetMiscPrinterInfoID:
			return ACAPI_ProjectOperation_GetMiscPrinterInfo (reinterpret_cast<API_MiscPrinterInfo*> (par1));
		case APIEnv_DeleteEmbeddedLibItemID:
			return ACAPI_LibraryManagement_DeleteEmbeddedLibItem (reinterpret_cast<const IO::Location*> (par1), static_cast<bool> (reinterpret_cast<GS::IntPtr> (par2)), static_cast<bool> (reinterpret_cast<GS::IntPtr> (par3)));
		case APIEnv_GetLibPartLockStatusID:
			return ACAPI_LibraryPart_GetLibPartLockStatus (reinterpret_cast<const IO::Location*> (par1), reinterpret_cast<API_LockableStatus*> (par2), reinterpret_cast<IO::Location*> (par3));
		case APIEnv_Change3DCuttingPlanesID:
			return ACAPI_View_Change3DCuttingPlanes (reinterpret_cast<API_3DCutPlanesInfo*> (par1));
		case APIEnv_IsInCurtainWallEditModeID:
			return ACAPI_HierarchicalEditing_IsInCurtainWallEditMode (reinterpret_cast<bool*> (par1), reinterpret_cast<API_Guid*> (par2));
		default:
			return APIERR_NOTSUPPORTED;
	}
}


GSErrCode ACAPI_Interface (API_InterfaceID code, void* par1 = nullptr, void* par2 = nullptr, void* par3 = nullptr, void* par4 = nullptr, void* par5 = nullptr)
{
	switch (code) {
		case APIIo_DrawRubberArcID:
			return ACAPI_UserInput_DrawRubberArc (reinterpret_cast<API_RubberArcType*> (par1));
		case APIIo_IsCuttingPlanesVisibleID:
			return ACAPI_CuttingPlane_IsCuttingPlanesVisible (reinterpret_cast<bool*> (par1));
		case APIIo_OpenOtherObjectDialogID:
			return ACAPI_Dialog_OpenOtherObjectDialog (reinterpret_cast<bool*> (par1), reinterpret_cast<IO::Location*> (par2), reinterpret_cast<bool*> (par3));
		case APIIo_SettingsDialogID:
			return ACAPI_Dialog_SettingsDialog (reinterpret_cast<API_ToolBoxItem*> (par1), reinterpret_cast<const API_Guid*> (par2));
		case APIIo_SetNeigFilterID:
			return ACAPI_UserInput_SetNeigFilter (reinterpret_cast<API_NeigFilter*> (par1), static_cast<API_NeigID> (reinterpret_cast<GS::IntPtr> (par2)));
		case APIIo_ObjectSettingsID:
			return ACAPI_Dialog_ObjectSettings (reinterpret_cast<API_ObjectSettingsPars*> (par1));
		case APIIo_GetProcessOnOffSwitchID:
			return ACAPI_ProcessWindow_GetProcessOnOffSwitch (reinterpret_cast<bool*> (par1));
		case APIIo_SetProcessOnOffSwitchID:
			return ACAPI_ProcessWindow_SetProcessOnOffSwitch (reinterpret_cast<bool*> (par1));
		case APIIo_IncProcessValueID:
			return ACAPI_ProcessWindow_IncProcessValue (reinterpret_cast<Int32*> (par1));
		case APIIo_OpenPictureDialogID:
			return ACAPI_Dialog_OpenPictureDialog (reinterpret_cast<bool*> (par1), reinterpret_cast<IO::Location*> (par2));
		case APIIo_GetPolyID:
			return ACAPI_UserInput_GetPoly (reinterpret_cast<API_GetPolyType*> (par1), reinterpret_cast<API_RubberPolyCallbacks*> (par2));
		case APIIo_Is3DCutawayEnabledID:
			return ACAPI_CuttingPlane_Is3DCutawayEnabled (reinterpret_cast<bool*> (par1));
		case APIIo_SetMenuItemTextID:
			return ACAPI_MenuItem_SetMenuItemText (reinterpret_cast<const API_MenuItemRef*> (par1), reinterpret_cast<char*> (par2), reinterpret_cast<GS::UniString*> (par3));
		case APIIo_SetNextProcessPhaseID:
			return ACAPI_ProcessWindow_SetNextProcessPhase (reinterpret_cast<const GS::UniString*> (par1), reinterpret_cast<Int32*> (par2), reinterpret_cast<bool*> (par3));
		case APIIo_Set3DCutawayStatusID:
			return ACAPI_CuttingPlane_Set3DCutawayStatus (reinterpret_cast<bool*> (par1));
		case APIIo_SetConstraintID:
			return ACAPI_UserInput_SetConstraint (reinterpret_cast<API_ConstraintPars*> (par1));
		case APIIo_SetMenuItemFlagsID:
			return ACAPI_MenuItem_SetMenuItemFlags (reinterpret_cast<const API_MenuItemRef*> (par1), reinterpret_cast<GSFlags*> (par2), reinterpret_cast<GS::UniString*> (par3));
		case APIIo_CloseProcessWindowID:
			return ACAPI_ProcessWindow_CloseProcessWindow ();
		case APIIo_GetArcID:
			return ACAPI_UserInput_GetArc (reinterpret_cast<API_GetArcType*> (par1), reinterpret_cast<RubberLineInfoProc*> (par2));
		case APIIo_CancelUserInputID:
			return ACAPI_UserInput_CancelUserInput ();
		case APIIo_GetLineID:
			return ACAPI_UserInput_GetLine (reinterpret_cast<API_GetLineType*> (par1), reinterpret_cast<RubberLineInfoProc*> (par2));
		case APIIo_DrawRubberLineID:
			return ACAPI_UserInput_DrawRubberLine (reinterpret_cast<API_RubberLineType*> (par1));
		case APIIo_GetMenuItemFlagsID:
			return ACAPI_MenuItem_GetMenuItemFlags (reinterpret_cast<const API_MenuItemRef*> (par1), reinterpret_cast<GSFlags*> (par2), reinterpret_cast<GS::UniString*> (par3));
		case APIIo_CompleteUserInputID:
			return ACAPI_UserInput_CompleteUserInput ();
		case APIIo_ClearNeigFilterID:
			return ACAPI_UserInput_ClearNeigFilter (reinterpret_cast<API_NeigFilter*> (par1), static_cast<API_NeigID> (reinterpret_cast<GS::IntPtr> (par2)));
		case APIIo_GetMenuItemTextID:
			return ACAPI_MenuItem_GetMenuItemText (reinterpret_cast<const API_MenuItemRef*> (par1), reinterpret_cast<char*> (par2), reinterpret_cast<GS::UniString*> (par3));
		case APIIo_PetPaletteID:
			return ACAPI_Dialog_PetPalette (reinterpret_cast<API_PetPaletteType*> (par1), reinterpret_cast<APIPetPaletteCallBackProc*> (par2));
		case APIIo_SetProcessValueID:
			return ACAPI_ProcessWindow_SetProcessValue (reinterpret_cast<Int32*> (par1));
		case APIIo_SetCuttingPlanesVisibilityID:
			return ACAPI_CuttingPlane_SetCuttingPlanesVisibility (reinterpret_cast<bool*> (par1));
		case APIIo_OpenLibPartFileDialogID:
			return ACAPI_Dialog_OpenLibPartFileDialog (reinterpret_cast<bool*> (par1), reinterpret_cast<IO::Location*> (par2), reinterpret_cast<bool*> (par3), reinterpret_cast<bool*> (par4));
		case APIIo_GetProcessControlID:
			return ACAPI_ProcessWindow_GetProcessControl (reinterpret_cast<GS::ProcessControl**> (par1));
		case APIIo_InitNeigFilterID:
			return ACAPI_UserInput_InitNeigFilter (reinterpret_cast<API_NeigFilter*> (par1), static_cast<API_InitNeigFilterID> (reinterpret_cast<GS::IntPtr> (par2)));
		case APIIo_GetLastValidEmbeddedLPNameID:
			return ACAPI_LibraryPart_GetLastValidEmbeddedLPName (reinterpret_cast<GS::UniString*> (par1), reinterpret_cast<IO::Location*> (par2));
		case APIIo_SetUserControlCallbackID:
			return ACAPI_Dialog_SetUserControlCallback (reinterpret_cast<API_UCCallbackType*> (par1));
		case APIIo_InitProcessWindowID:
			return ACAPI_ProcessWindow_InitProcessWindow (reinterpret_cast<const GS::UniString*> (par1), reinterpret_cast<Int32*> (par2), reinterpret_cast<API_ProcessControlTypeID*> (par3));
		case APIIo_IsProcessCanceledID:
			return ACAPI_ProcessWindow_IsProcessCanceled ();
		case APIIo_SaveLibPartFileDialogID:
			return ACAPI_Dialog_SaveLibPartFileDialog (reinterpret_cast<bool*> (par1), reinterpret_cast<IO::Location*> (par2), reinterpret_cast<bool*> (par3), reinterpret_cast<GS::UniString*> (par4), reinterpret_cast<GS::UniString*> (par5));
		case APIIo_AddMenuItemTextID:
			return ACAPI_MenuItem_AddMenuItemText (reinterpret_cast<const API_MenuItemRef*> (par1), reinterpret_cast<char*> (par2), reinterpret_cast<GS::UniString*> (par3));
		case APIIo_ResetConstraintID:
			return ACAPI_UserInput_ResetConstraint ();
		case APIIo_GetPointID:
			return ACAPI_UserInput_GetPoint (reinterpret_cast<API_GetPointType*> (par1), reinterpret_cast<RubberLineInfoProc*> (par2), reinterpret_cast<Get3DComponentProc*> (par3));
		case APIIo_SetInnerProcessControlID:
			return ACAPI_ProcessWindow_SetInnerProcessControl (reinterpret_cast<GS::ProcessControl*> (par1));
		default:
			return APIERR_NOTSUPPORTED;
	}
}


GSErrCode ACAPI_Goodies (API_GoodiesID code, void* par1 = nullptr, void* par2 = nullptr, void* par3 = nullptr, void* par4 = nullptr)
{
	switch (code) {
		case APIAny_GetElemCreatorToolUnIdID:
			return ACAPI_Element_GetElemCreatorToolUnId (reinterpret_cast<API_Elem_Head*> (par1), reinterpret_cast<char*> (par2));
		case APIAny_EnableVisualOverrideID:
			return ACAPI_GraphicalOverride_EnableVisualOverride (reinterpret_cast<bool*> (par1), reinterpret_cast<const bool*> (par2));
		case APIAny_DeletePolyNodeID:
			return ACAPI_Polygon_DeletePolyNode (reinterpret_cast<API_ElementMemo*> (par1), reinterpret_cast<Int32*> (par2));
		case APIAny_GetTextLineLengthID:
			return ACAPI_Element_GetTextLineLength (reinterpret_cast<API_TextLinePars*> (par1), reinterpret_cast<double*> (par2));
		case APIAny_GetLibPartToolVariationID:
			return ACAPI_LibraryPart_GetLibPartToolVariation (reinterpret_cast<API_LibPart*> (par1), reinterpret_cast<API_ToolBoxItem*> (par2));
		case APIAny_ElemHasVisibleSkinID:
			return ACAPI_Element_ElemHasVisibleSkin (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<const API_StructureDisplay*> (par2), reinterpret_cast<bool*> (par3));
		case APIAny_CompareLibPartUnIdsID:
			return ACAPI_LibraryPart_CompareLibPartUnIds (reinterpret_cast<const char*> (par1), reinterpret_cast<const char*> (par2));
		case APIAny_ChangeContentID:
			return ACAPI_Element_ChangeContent (reinterpret_cast<API_ContentPars*> (par1));
		case APIAny_CalcSunOnPlaceID:
			return ACAPI_GeoLocation_CalcSunOnPlace (reinterpret_cast<API_PlaceInfo*> (par1));
		case APIAny_CalcSideOffsetToCoreOffsetID:
			return ACAPI_Element_CalcSideOffsetToCoreOffset (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<const double*> (par2), reinterpret_cast<double*> (par3));
		case APIAny_RunGDLParScriptID:
			return ACAPI_LibraryManagement_RunGDLParScript (reinterpret_cast<const API_Elem_Head*> (par1), static_cast<UInt32> (reinterpret_cast<GS::IntPtr> (par2)));
		case APIAny_TriangulatePolyID:
			return ACAPI_Polygon_TriangulatePoly (reinterpret_cast<API_ElementMemo*> (par1), reinterpret_cast<API_Coord***> (par2));
		case APIAny_InsertSubPolyID:
			return ACAPI_Polygon_InsertSubPoly (reinterpret_cast<API_ElementMemo*> (par1), reinterpret_cast<API_ElementMemo*> (par2));
		case APIAny_FreeMDCLParameterListID:
			return ACAPI_AddOnAddOnCommunication_FreeMDCLParameterList (reinterpret_cast<GSHandle*> (par1));
		case APIAny_SetAnAutoTextID:
			return ACAPI_AutoText_SetAnAutoText (reinterpret_cast<const GS::UniString*> (par1), reinterpret_cast<const GS::UniString*> (par2));
		case APIAny_EnableRenovationOverrideID:
			return ACAPI_GraphicalOverride_EnableRenovationOverride (reinterpret_cast<bool*> (par1), reinterpret_cast<const bool*> (par2));
		case APIAny_SearchElementByCoordID:
			return ACAPI_Element_SearchElementByCoord (reinterpret_cast<const API_ElemSearchPars*> (par1), reinterpret_cast<API_Guid*> (par2));
		case APIAny_GetElemLibPartUnIdID:
			return ACAPI_LibraryPart_GetElemLibPartUnId (reinterpret_cast<API_Elem_Head*> (par1), reinterpret_cast<char*> (par2));
		case APIAny_GetSelectedElementID:
			return ACAPI_Selection_GetSelectedElement (reinterpret_cast<const API_Neig*> (par1), reinterpret_cast<API_Guid*> (par2));
		case APIAny_OpenParametersID:
			return ACAPI_LibraryPart_OpenParameters (reinterpret_cast<API_ParamOwnerType*> (par1));
		case APIAny_DeleteSubPolyID:
			return ACAPI_Polygon_DeleteSubPoly (reinterpret_cast<API_ElementMemo*> (par1), reinterpret_cast<Int32*> (par2));
		case APIAny_GetUnloadedLibpartNameID:
			return ACAPI_LibraryPart_GetUnloadedLibpartName (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<GS::UniString*> (par2));
		case APIAny_ActivateSessionReportID:
			return ACAPI_Dialog_ActivateSessionReport ();
		case APIAny_DisposeRegularizedPolyID:
			return ACAPI_Polygon_DisposeRegularizedPoly (reinterpret_cast<API_RegularizedPoly*> (par1));
		case APIAny_GetActParametersID:
			return ACAPI_LibraryPart_GetActParameters (reinterpret_cast<API_GetParamsType*> (par1));
		case APIAny_GetOpeningTransformationID:
			return ACAPI_Element_GetOpeningTransformation (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<API_Tranmat*> (par2));
		case APIAny_RegularizePolylineID:
			return ACAPI_Polygon_RegularizePolyline (reinterpret_cast<const API_RegularizedPoly*> (par1), reinterpret_cast<API_RegularizedPoly*> (par2));
		case APIAny_GetRenovationStatusNameID:
			return ACAPI_Renovation_GetRenovationStatusName (static_cast<API_RenovationStatusType> (reinterpret_cast<GS::IntPtr> (par1)), reinterpret_cast<GS::UniString*> (par2));
		case APIAny_AddMDCLParameterID:
			return ACAPI_AddOnAddOnCommunication_AddMDCLParameter (reinterpret_cast<GSHandle> (par1), reinterpret_cast<API_MDCLParameter*> (par2));
		case APIAny_ChangeMDCLParameterID:
			return ACAPI_AddOnAddOnCommunication_ChangeMDCLParameter (reinterpret_cast<GSHandle> (par1), reinterpret_cast<API_MDCLParameter*> (par2));
		case APIAny_GetBuiltInLibpartUnIdID:
			return ACAPI_LibraryPart_GetBuiltInLibpartUnId (static_cast<short> (reinterpret_cast<GS::IntPtr> (par1)), reinterpret_cast<char*> (par2));
		case APIAny_GetTextureCoordID:
			return ACAPI_ModelAccess_GetTextureCoord (reinterpret_cast<API_TexCoordPars*> (par1), reinterpret_cast<API_UVCoord*> (par2));
		case APIAny_SetSelectedElementNeigID:
			return ACAPI_Selection_SetSelectedElementNeig (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<API_Neig*> (par2));
		case APIAny_UI2ElemPriorityID:
			return ACAPI_Element_UI2ElemPriority (reinterpret_cast<GS::Int32*> (par1), reinterpret_cast<GS::Int32*> (par2));
		case APIAny_GetAutoTextsID:
			return ACAPI_AutoText_GetAutoTexts (reinterpret_cast<GS::Array<GS::ArrayFB<GS::UniString, 3>>*> (par1), static_cast<API_AutotextType> (reinterpret_cast<GS::IntPtr> (par2)));
		case APIAny_InterpretGDLScript3DID:
			return ACAPI_LibraryManagement_InterpretGDLScript3D (reinterpret_cast<const GS::UniString*> (par1), reinterpret_cast<API_AddParType**> (par2), reinterpret_cast<void*> (par3), reinterpret_cast<void*> (par4));
		case APIAny_GetPropertyAutoTextKeyTableID:
			return ACAPI_AutoText_GetPropertyAutoTextKeyTable (reinterpret_cast<API_Guid*> (par1), reinterpret_cast<GS::HashTable<GS::UniString, GS::UniString>*> (par2));
		case APIAny_ConvertMimePictureID:
			return ACAPI_Conversion_ConvertMimePicture (reinterpret_cast<API_MimePicture*> (par1));
		case APIAny_InsertPolyNodeID:
			return ACAPI_Polygon_InsertPolyNode (reinterpret_cast<API_ElementMemo*> (par1), reinterpret_cast<Int32*> (par2), reinterpret_cast<API_Coord*> (par3));
		case APIAny_CheckLibPartSubtypeOfID:
			return ACAPI_LibraryPart_CheckLibPartSubtypeOf (reinterpret_cast<const char*> (par1), reinterpret_cast<const char*> (par2));
		case APIAny_SolveStairID:
			return ACAPI_HierarchicalEditing_SolveStair (reinterpret_cast<API_StairType*> (par1), reinterpret_cast<API_ElementMemo*> (par2), reinterpret_cast<API_StairSolutionID*> (par3));
		case APIAny_ChangeAutoTextFlagID:
			return ACAPI_AutoText_ChangeAutoTextFlag (reinterpret_cast<bool*> (par1));
		case APIAny_InterpretAutoTextID:
			return ACAPI_AutoText_InterpretAutoText (reinterpret_cast<const GS::UniString*> (par1), reinterpret_cast<const API_Guid*> (par2), reinterpret_cast<GS::UniString*> (par3));
		case APIAny_SetMasterLayoutOnLayoutID:
			return ACAPI_Navigator_SetMasterLayoutOnLayout (reinterpret_cast<const API_DatabaseUnId*> (par1));
		case APIAny_GetSkylightHolePolygonID:
			return ACAPI_Element_GetSkylightHolePolygon (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<Geometry::Polygon2D*> (par2));
		case APIAny_CloseParametersID:
			return ACAPI_LibraryPart_CloseParameters ();
		case APIAny_GetRoomImageID:
			return ACAPI_Element_GetRoomImage (reinterpret_cast<API_RoomImage*> (par1));
		case APIAny_GetAutoTextFlagID:
			return ACAPI_AutoText_GetAutoTextFlag (reinterpret_cast<bool*> (par1));
		case APIAny_Elem2UIPriorityID:
			return ACAPI_Element_Elem2UIPriority (reinterpret_cast<GS::Int32*> (par1), reinterpret_cast<GS::Int32*> (par2));
		case APIAny_GetCWSubElemParamsID:
			return ACAPI_CurtainWall_GetCWSubElemParams (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<API_AddParType***> (par2));
		case APIAny_GetRenovationFilterNameID:
			return ACAPI_Renovation_GetRenovationFilterName (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<GS::UniString*> (par2));
		case APIAny_ChangeAParameterID:
			return ACAPI_LibraryPart_ChangeAParameter (reinterpret_cast<API_ChangeParamType*> (par1));
		case APIAny_GetMDCLParameterNumID:
			return ACAPI_AddOnAddOnCommunication_GetMDCLParameterNum (reinterpret_cast<GSHandle> (par1), reinterpret_cast<Int32*> (par2));
		case APIAny_NeigToCoordID:
			return ACAPI_Element_NeigToCoord (reinterpret_cast<API_Neig*> (par1), reinterpret_cast<API_Coord3D*> (par2), reinterpret_cast<API_Coord3D*> (par3));
		case APIAny_CheckPropertyExpressionStringID:
			return ACAPI_Property_CheckPropertyExpressionString (reinterpret_cast<GS::UniString*> (par1));
		case APIAny_CheckLibPartSubtypeOfbyMainID:
			return ACAPI_LibraryPart_CheckLibPartSubtypeOfbyMain (reinterpret_cast<const char*> (par1), reinterpret_cast<const char*> (par2));
		case APIAny_CreateAnAutoTextID:
			return ACAPI_AutoText_CreateAnAutoText (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<const char*> (par2));
		case APIAny_GetHierarchicalElementOwnerID:
			return ACAPI_HierarchicalEditing_GetHierarchicalElementOwner (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<const API_HierarchicalOwnerType*> (par2), reinterpret_cast<API_HierarchicalElemType*> (par3), reinterpret_cast<API_Guid*> (par4));
		case APIAny_GetCWAbsoluteBottomID:
			return ACAPI_CurtainWall_GetCWAbsoluteBottom (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<double*> (par2));
		case APIAny_GetTextSizeFactorID:
			return ACAPI_Element_GetTextSizeFactor (reinterpret_cast<short*> (par1), reinterpret_cast<double*> (par2));
		case APIAny_DeleteAnAutoTextID:
			return ACAPI_AutoText_DeleteAnAutoText (reinterpret_cast<const char*> (par1));
		case APIAny_PolygonId2SurfaceTypeID:
			return ACAPI_Polygon_PolygonId2SurfaceType (reinterpret_cast<const API_Element*> (par1), reinterpret_cast<const Int32*> (par2), reinterpret_cast<API_SurfaceTypeID*> (par3));
		case APIAny_GetHttpConnectionPortID:
			return ACAPI_Command_GetHttpConnectionPort (reinterpret_cast<UShort*> (par1));
		case APIAny_GetSplineMaxDistID:
			return ACAPI_ProjectSetting_GetSplineMaxDist (reinterpret_cast<API_TestSplineFit*> (par1), reinterpret_cast<double*> (par2));
		case APIAny_UsableGDLStringID:
			return ACAPI_LibraryManagement_UsableGDLString (reinterpret_cast<const char*> (par1));
		case APIAny_GetParamValuesID:
			return ACAPI_LibraryPart_GetParamValues (reinterpret_cast<API_GetParamValuesType*> (par1));
		case APIAny_GetPropertyExprReferenceStringID:
			return ACAPI_Property_GetPropertyExprReferenceString (reinterpret_cast<API_PropertyDefinition*> (par1), reinterpret_cast<GS::UniString*> (par2));
		case APIAny_GetMDCLParameterID:
			return ACAPI_AddOnAddOnCommunication_GetMDCLParameter (reinterpret_cast<GSHandle> (par1), reinterpret_cast<API_MDCLParameter*> (par2));
		case APIAny_CalcCoreOffsetToSideOffsetID:
			return ACAPI_Element_CalcCoreOffsetToSideOffset (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<const double*> (par2), reinterpret_cast<double*> (par3));
		case APIAny_RegularizePolygonID:
			return ACAPI_Polygon_RegularizePolygon (reinterpret_cast<const API_RegularizedPoly*> (par1), reinterpret_cast<Int32*> (par2), reinterpret_cast<API_RegularizedPoly***> (par3));
		case APIAny_GetMainGroupGuidID:
			return ACAPI_Grouping_GetMainGroupGuid (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<API_Guid*> (par2));
		case APIAny_ConvertPictureID:
			return ACAPI_Conversion_ConvertPicture (reinterpret_cast<API_PictureHandle*> (par1), reinterpret_cast<API_PictureHandle*> (par2));
		case APIAny_InitMDCLParameterListID:
			return ACAPI_AddOnAddOnCommunication_InitMDCLParameterList (reinterpret_cast<GSHandle*> (par1));
		case APIAny_GetCWHeightID:
			return ACAPI_CurtainWall_GetCWHeight (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<double*> (par2));
		case APIAny_SetEmptyHoleUnIdID:
			return ACAPI_Element_SetEmptyHoleUnId (reinterpret_cast<GSType*> (par1), reinterpret_cast<const char*> (par2), reinterpret_cast<const char*> (par3));
		case APIAny_GetAutoTextKeysID:
			return ACAPI_AutoText_GetAutoTextKeys (reinterpret_cast<char***> (par1), reinterpret_cast<char***> (par2));
		case APIAny_GetContainingHotlinkGuidID:
			return ACAPI_Hotlink_GetContainingHotlinkGuid (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<API_Guid*> (par2));
		default:
			return APIERR_NOTSUPPORTED;
	}
}


GSErrCode ACAPI_Automate (API_EnvironmentID code, void* par1 = nullptr, [[maybe_unused]] void* par2 = nullptr, [[maybe_unused]] void* par3 = nullptr)
{
	switch (code) {
		case APIEnv_SetLibrariesID:
			return ACAPI_LibraryManagement_SetLibraries (reinterpret_cast<const GS::Array<API_LibraryInfo>*> (par1));
		default:
			return APIERR_NOTSUPPORTED;
	}
}


GSErrCode ACAPI_Automate (API_InterfaceID code, void* par1 = nullptr, [[maybe_unused]] void* par2 = nullptr, [[maybe_unused]] void* par3 = nullptr)
{
	switch (code) {
		case APIIo_OkHierarchicalElemID:
			return ACAPI_HierarchicalEditing_OkHierarchicalElem ();
		case APIIo_EditHierarchicalElemID:
			return ACAPI_HierarchicalEditing_EditHierarchicalElem (reinterpret_cast<const API_Guid*> (par1));
		case APIIo_CancelHierarchicalElemID:
			return ACAPI_HierarchicalEditing_CancelHierarchicalElem ();
		case APIIo_ShowSelectionIn3DID:
			return ACAPI_View_ShowSelectionIn3D ();
		case APIIo_ShowAllIn3DID:
			return ACAPI_View_ShowAllIn3D ();
		default:
			return APIERR_NOTSUPPORTED;
	}
}


GSErrCode ACAPI_Automate (API_AutomateID code, void* par1 = nullptr, void* par2 = nullptr, void* par3 = nullptr)
{
	switch (code) {
		case APIDo_PhotoRenderID:
			return ACAPI_Rendering_PhotoRender (reinterpret_cast<const API_PhotoRenderPars*> (par1), reinterpret_cast<const API_PrintPars*> (par2));
		case APIDo_QuitID:
			return ACAPI_ProjectOperation_Quit ();
		case APIDo_PublishID:
			return ACAPI_ProjectOperation_Publish (reinterpret_cast<const API_PublishPars*> (par1), reinterpret_cast<const GS::Array<API_Guid>*> (par2));
		case APIDo_ZoomID:
			return ACAPI_View_Zoom (reinterpret_cast<API_Box*> (par1), reinterpret_cast<API_Rect*> (par2), reinterpret_cast<API_Tranmat*> (par3));
		case APIDo_ZoomToElementsID:
			return ACAPI_View_ZoomToElements (reinterpret_cast<const GS::Array<API_Guid>*> (par1));
		case APIDo_RebuildID:
			return ACAPI_View_Rebuild (reinterpret_cast<bool*> (par1));
		case APIDo_ReloadLibrariesID:
			return ACAPI_ProjectOperation_ReloadLibraries ();
		case APIDo_ChangeWindowID:
			return ACAPI_Window_ChangeWindow (reinterpret_cast<const API_WindowInfo*> (par1));
		case APIDo_RedrawID:
			return ACAPI_View_Redraw ();
		case APIDo_CloseID:
			return ACAPI_ProjectOperation_Close ();
		case APIDo_PrintID:
			return ACAPI_ProjectOperation_Print (reinterpret_cast<const API_PrintPars*> (par1));
		case APIDo_OpenID:
			return ACAPI_ProjectOperation_Open (reinterpret_cast<const API_FileOpenPars*> (par1));
		case APIDo_SaveAsModuleFileID:
			return ACAPI_ProjectOperation_SaveAsModuleFile (reinterpret_cast<const IO::Location*> (par1), reinterpret_cast<GS::Array<API_Elem_Head>*> (par2));
		case APIDo_SaveID: {
			if (reinterpret_cast<const API_FileSavePars*> (par1) != nullptr && reinterpret_cast<const API_SavePars_Ifc*> (par2) != nullptr && reinterpret_cast<API_IFCRelationshipData*> (par3) != nullptr)
				return ACAPI_ProjectOperation_Save (reinterpret_cast<const API_FileSavePars*> (par1), reinterpret_cast<const API_SavePars_Ifc*> (par2), reinterpret_cast<API_IFCRelationshipData*> (par3));
			else if (reinterpret_cast<const API_FileSavePars*> (par1) != nullptr && reinterpret_cast<const API_SavePars_Archive*> (par2) != nullptr)
				return ACAPI_ProjectOperation_Save (reinterpret_cast<const API_FileSavePars*> (par1), reinterpret_cast<const API_SavePars_Archive*> (par2));
			else if (reinterpret_cast<const API_FileSavePars*> (par1) != nullptr && reinterpret_cast<const API_SavePars_PlanDump*> (par2) != nullptr)
				return ACAPI_ProjectOperation_Save (reinterpret_cast<const API_FileSavePars*> (par1), reinterpret_cast<const API_SavePars_PlanDump*> (par2));
			else if (reinterpret_cast<const API_FileSavePars*> (par1) != nullptr && reinterpret_cast<const API_SavePars_Object*> (par2) != nullptr)
				return ACAPI_ProjectOperation_Save (reinterpret_cast<const API_FileSavePars*> (par1), reinterpret_cast<const API_SavePars_Object*> (par2));
			else if (reinterpret_cast<const API_FileSavePars*> (par1) != nullptr && reinterpret_cast<const API_SavePars_Picture*> (par2) != nullptr)
				return ACAPI_ProjectOperation_Save (reinterpret_cast<const API_FileSavePars*> (par1), reinterpret_cast<const API_SavePars_Picture*> (par2));
			else if (reinterpret_cast<const API_FileSavePars*> (par1) != nullptr && reinterpret_cast<const API_SavePars_Pdf*> (par2) != nullptr)
				return ACAPI_ProjectOperation_Save (reinterpret_cast<const API_FileSavePars*> (par1), reinterpret_cast<const API_SavePars_Pdf*> (par2));
			else if (reinterpret_cast<const API_FileSavePars*> (par1) != nullptr && reinterpret_cast<const API_SavePars_Saf*> (par2) != nullptr)
				return ACAPI_ProjectOperation_Save (reinterpret_cast<const API_FileSavePars*> (par1), reinterpret_cast<const API_SavePars_Saf*> (par2));
			else if (reinterpret_cast<const API_FileSavePars*> (par1) != nullptr)
				return ACAPI_ProjectOperation_Save (reinterpret_cast<const API_FileSavePars*> (par1));
			else
				return ACAPI_ProjectOperation_Save ();
		}
		case APIDo_GoToViewID:
			return ACAPI_View_GoToView (reinterpret_cast<const char*> (par1));
		case APIDo_NewProjectID:
			return ACAPI_ProjectOperation_NewProject (reinterpret_cast<const API_NewProjectPars*> (par1));
		case APIDo_ZoomToSelectedID:
			return ACAPI_View_ZoomToSelected ();
		case APIDo_OpenLibraryPartID:
			return ACAPI_LibraryManagement_OpenLibraryPart (reinterpret_cast<const API_OpenLibPartInfo*> (par1));
		default:
			return APIERR_NOTSUPPORTED;
	}
}


GSErrCode ACAPI_Navigator (API_NavigatorID code, void* par1 = nullptr, void* par2 = nullptr, void* par3 = nullptr, void* par4 = nullptr)
{
	switch (code) {
		case APINavigator_SearchNavigatorItemID:
			return ACAPI_Navigator_SearchNavigatorItem (reinterpret_cast<API_NavigatorItem*> (par1), reinterpret_cast<GS::Array<API_NavigatorItem>*> (par2));
		case APINavigator_GetNavigatorItemID:
			return ACAPI_Navigator_GetNavigatorItem (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<API_NavigatorItem*> (par2));
		case APINavigator_ChangeNavigatorViewID:
			return ACAPI_Navigator_ChangeNavigatorView (reinterpret_cast<API_NavigatorItem*> (par1), reinterpret_cast<API_NavigatorView*> (par2));
		case APINavigator_ChangeNavigatorItemID:
			return ACAPI_Navigator_ChangeNavigatorItem (reinterpret_cast<API_NavigatorItem*> (par1));
		case APINavigator_DeleteNavigatorVPItemID:
			return ACAPI_Navigator_DeleteNavigatorVPItem (reinterpret_cast<const API_Guid*> (par1));
		case APINavigator_GetNavigatorSetID:
			return ACAPI_Navigator_GetNavigatorSet (reinterpret_cast<API_NavigatorSet*> (par1), reinterpret_cast<Int32*> (par2));
		case APINavigator_GetNavigatorParentItemID:
			return ACAPI_Navigator_GetNavigatorParentItem (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<API_NavigatorItem*> (par2));
		case APINavigator_GetNavigatorChildrenItemsID:
			return ACAPI_Navigator_GetNavigatorChildrenItems (reinterpret_cast<API_NavigatorItem*> (par1), reinterpret_cast<GS::Array<API_NavigatorItem>*> (par2));
		case APINavigator_DeleteNavigatorViewID:
			return ACAPI_Navigator_DeleteNavigatorView (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<const bool*> (par2));
		case APINavigator_GetNavigatorViewID:
			return ACAPI_Navigator_GetNavigatorView (reinterpret_cast<API_NavigatorItem*> (par1), reinterpret_cast<API_NavigatorView*> (par2));
		case APINavigator_RegisterCallbackInterfaceID:
			return ACAPI_Navigator_RegisterCallbackInterface (reinterpret_cast<INavigatorCallbackInterface*> (par1));
		case APINavigator_GetNavigatorVPRootGroupsID:
			return ACAPI_Navigator_GetNavigatorVPRootGroups (reinterpret_cast<GS::Array<API_Guid>*> (par1));
		case APINavigator_GetNavigatorSetNumID:
			return ACAPI_Navigator_GetNavigatorSetNum (reinterpret_cast<Int32*> (par1));
		case APINavigator_ChangeNavigatorVPItemID:
			return ACAPI_Navigator_ChangeNavigatorVPItem (reinterpret_cast<API_NavigatorAddOnViewPointData*> (par1));
		case APINavigator_GetNavigatorChildNumID:
			return ACAPI_Navigator_GetNavigatorChildNum (reinterpret_cast<API_NavigatorItem*> (par1), reinterpret_cast<Int32*> (par2));
		case APINavigator_GetNavigatorVPItemChildrenID:
			return ACAPI_Navigator_GetNavigatorVPItemChildren (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<GS::Array<API_Guid>*> (par2));
		case APINavigator_SetNavigatorItemPositionID:
			return ACAPI_Navigator_SetNavigatorItemPosition (reinterpret_cast<const GS::Guid*> (par1), reinterpret_cast<const GS::Guid*> (par2), reinterpret_cast<const GS::Guid*> (par3));
		case APINavigator_CreateNavigatorVPItemID:
			return ACAPI_Navigator_CreateNavigatorVPItem (reinterpret_cast<API_NavigatorAddOnViewPointData*> (par1));
		case APINavigator_GetNavigatorVPItemID:
			return ACAPI_Navigator_GetNavigatorVPItem (reinterpret_cast<API_NavigatorAddOnViewPointData*> (par1));
		case APINavigator_CloneProjectMapItemToViewMapID:
			return ACAPI_Navigator_CloneProjectMapItemToViewMap (reinterpret_cast<const API_Guid*> (par1), reinterpret_cast<const API_Guid*> (par2), reinterpret_cast<API_Guid*> (par3));
		case APINavigator_NewNavigatorViewID:
			return ACAPI_Navigator_NewNavigatorView (reinterpret_cast<API_NavigatorItem*> (par1), reinterpret_cast<API_NavigatorView*> (par2), reinterpret_cast<const GS::Guid*> (par3), reinterpret_cast<const GS::Guid*> (par4));
		default:
			return APIERR_NOTSUPPORTED;
	}
}


GSErrCode ACAPI_Register_SupportedService (GSType cmdID, Int32 cmdVersion)
{
	return ACAPI_AddOnAddOnCommunication_RegisterSupportedService (cmdID, cmdVersion);
}


GSErrCode ACAPI_Register_RequiredService (const API_ModulID* modulID, GSType cmdID, Int32 cmdVersion)
{
	return ACAPI_AddOnIntegration_RegisterRequiredService (modulID, cmdID, cmdVersion);
}


GSErrCode ACAPI_Register_Menu (short menuStrResID, short promptStrResID, APIMenuCodeID menuPosCode, GSFlags menuFlags)
{
	return ACAPI_MenuItem_RegisterMenu (menuStrResID, promptStrResID, menuPosCode, menuFlags);
}


GSErrCode ACAPI_Register_FileType (Int32 refCon, GSType ftype, GSType fcreator, const char* extname, short iconResID, short descStrResID, short descStrResItemID, API_IOMethod methodFlags)
{
	return ACAPI_AddOnIntegration_RegisterFileType (refCon, ftype, fcreator, extname, iconResID, descStrResID, descStrResItemID, methodFlags);
}


GSErrCode ACAPI_Register_Subtype (GSType signature, short templateFileResID, bool transparentNode, short stringResID, short smallIconResID, short largeIconResID, API_TBoxGroup toolGroupId, API_TBoxEnabled enableFlags, short defaultsResID)
{
	return ACAPI_LibraryPart_RegisterSubtype (signature, templateFileResID, transparentNode, stringResID, smallIconResID, largeIconResID, toolGroupId, enableFlags, defaultsResID);
}


GSErrCode ACAPI_Register_SettingsPanel (Int32 refCon, const API_ElemType& tool, short iconId, short stringId, short pageId, short growType = 0, bool visibleByDefault = false)
{
	return ACAPI_AddOnIntegration_RegisterSettingsPanel (refCon, tool, iconId, stringId, pageId, growType, visibleByDefault);
}


GSErrCode ACAPI_Register_AttributePanel (Int32 refCon, API_AttrTypeID attr, short iconId, short stringId, short pageId, short growType = 0)
{
	return ACAPI_AddOnIntegration_RegisterAttributePanel (refCon, attr, iconId, stringId, pageId, growType);
}


GSErrCode ACAPI_Register_InfoBoxPanel (Int32 refCon, const API_ElemType& tool, short stringId, short pageId, bool visibleByDefault = false)
{
	return ACAPI_AddOnIntegration_RegisterInfoBoxPanel (refCon, tool, stringId, pageId, visibleByDefault);
}


GSErrCode ACAPI_Register_ESYM (GSType signature, API_LibTypeID typeID, short stringResID)
{
	return ACAPI_LibraryPart_RegisterESYM (signature, typeID, stringResID);
}


GSErrCode ACAPI_Register_PropertyObjectHandler (short assignStrResID)
{
	return ACAPI_Property_RegisterPropertyObjectHandler (assignStrResID);
}


GSErrCode ACAPI_Register_BuiltInLibrary ()
{
	return ACAPI_AddOnIntegration_RegisterBuiltInLibrary ();
}


GSErrCode ACAPI_Register_ModulDataHandler ()
{
	return ACAPI_AddOnIntegration_RegisterModulDataHandler ();
}


GSErrCode ACAPI_Register_ClassificationVisibilityHandler ()
{
	return ACAPI_AddOnIntegration_RegisterClassificationVisibilityHandler ();
}


GSErrCode ACAPI_Register_PropertyVisibilityHandler ()
{
	return ACAPI_Property_RegisterPropertyVisibilityHandler ();
}


GSErrCode ACAPI_Register_AddOnObjectHandler ()
{
	return ACAPI_AddOnObject_RegisterAddOnObjectHandler ();
}


GSErrCode ACAPI_Register_NavigatorAddOnViewPointDataHandler ()
{
	return ACAPI_AddOnIntegration_RegisterNavigatorAddOnViewPointDataHandler ();
}


GSErrCode ACAPI_Register_SettingsObserver (const API_ElemType& tool)
{
	return ACAPI_AddOnIntegration_RegisterSettingsObserver (tool);
}


GSErrCode ACAPI_Register_AttributeImportFormat (const API_AttributeManagerFormat& formatData)
{
	return ACAPI_AddOnIntegration_RegisterAttributeImportFormat (formatData);
}


GSErrCode ACAPI_Register_PublishFormat (const API_PublishFormatData& formatData)
{
	return ACAPI_AddOnIntegration_RegisterPublishFormat (formatData);
}


GSErrCode ACAPI_Install_ModulCommandHandler (GSType cmdID, Int32 cmdVersion, APIModulCommandProc* handlerProc)
{
	return ACAPI_AddOnIntegration_InstallModulCommandHandler (cmdID, cmdVersion, handlerProc);
}


GSErrCode ACAPI_Install_MenuHandler (short menuStrResID, APIMenuCommandProc* handlerProc)
{
	return ACAPI_MenuItem_InstallMenuHandler (menuStrResID, handlerProc);
}


GSErrCode ACAPI_Install_FileTypeHandler (GSType cmdID, APIIOCommandProc* handlerProc)
{
	return ACAPI_AddOnIntegration_InstallFileTypeHandler (cmdID, handlerProc);
}


GSErrCode ACAPI_Install_FileTypeHandler3D (GSType cmdID, APIIO3DCommandProc* handlerProc)
{
	return ACAPI_AddOnIntegration_InstallFileTypeHandler3D (cmdID, handlerProc);
}


GSErrCode ACAPI_Install_PanelHandler (Int32 refCon, APIPanelCreateProc* handlerCreateProc, APIPanelDestroyProc* handlerDestroyProc)
{
	return ACAPI_AddOnIntegration_InstallPanelHandler (refCon, handlerCreateProc, handlerDestroyProc);
}


GSErrCode ACAPI_Install_AddOnCommandHandler (GS::Owner<API_AddOnCommand> addOnCommand)
{
	return ACAPI_AddOnAddOnCommunication_InstallAddOnCommandHandler (addOnCommand.Pass ());
}


GSErrCode ACAPI_Install_ESYMHandler (GSType signature, APIESYMCommandProc* handlerProc)
{
	return ACAPI_LibraryPart_InstallESYMHandler (signature, handlerProc);
}


GSErrCode ACAPI_Install_PropertyObjectHandler (short strResID, APIPropertyObjectCommandProc* propertyCommandProc)
{
	return ACAPI_Property_InstallPropertyObjectHandler (strResID, propertyCommandProc);
}


GSErrCode ACAPI_Install_ModulDataMergeHandler (APIModulDataMergeHandlerProc* mergeHandlerProc)
{
	return ACAPI_AddOnIntegration_InstallModulDataMergeHandler (mergeHandlerProc);
}


GSErrCode ACAPI_Install_ModulDataSaveOldFormatHandler (APIModulDataSaveOldFormatHandlerProc* modulDataSaveOldFormatProc)
{
	return ACAPI_AddOnIntegration_InstallModulDataSaveOldFormatHandler (modulDataSaveOldFormatProc);
}


GSErrCode ACAPI_Install_ElemSetSaveOldFormatHandler (APIElemSetSaveOldFormatHandlerProc* elemSetSaveOldFormatProc)
{
	return ACAPI_AddOnIntegration_InstallElemSetSaveOldFormatHandler (elemSetSaveOldFormatProc);
}


GSErrCode ACAPI_Install_AddOnObjectMergeHandler (APIAddonObjectMergeHandlerProc* mergeHandlerProc)
{
	return ACAPI_AddOnObject_InstallAddOnObjectMergeHandler (mergeHandlerProc);
}


GSErrCode ACAPI_Install_AddOnObjectSaveOldFormatHandler (APIAddonObjectSaveOldFormatHandlerProc* saveOldFormatProc)
{
	return ACAPI_AddOnObject_InstallAddOnObjectSaveOldFormatHandler (saveOldFormatProc);
}


GSErrCode ACAPI_Install_AddOnObjectConvertNewFormatHandler (APIAddonObjectConvertNewFormatHandlerProc* convertNewFormatProc)
{
	return ACAPI_AddOnObject_InstallAddOnObjectConvertNewFormatHandler (convertNewFormatProc);
}


GSErrCode ACAPI_Install_NavigatorAddOnViewPointDataMergeHandler (APINavigatorAddOnViewPointDataMergeHandlerProc* mergeHandlerProc)
{
	return ACAPI_AddOnIntegration_InstallNavigatorAddOnViewPointDataMergeHandler (mergeHandlerProc);
}


GSErrCode ACAPI_Install_NavigatorAddOnViewPointDataSaveOldFormatHandler (APINavigatorAddOnViewPointDataSaveOldFormatHandlerProc* saveOldFormatProc)
{
	return ACAPI_AddOnIntegration_InstallNavigatorAddOnViewPointDataSaveOldFormatHandler (saveOldFormatProc);
}


GSErrCode ACAPI_Install_NavigatorAddOnViewPointDataConvertNewFormatHandler (APINavigatorAddOnViewPointDataConvertNewFormatHandlerProc* convertNewFormatProc)
{
	return ACAPI_AddOnIntegration_InstallNavigatorAddOnViewPointDataConvertNewFormatHandler (convertNewFormatProc);
}


GSErrCode ACAPI_Install_SettingsHandler (const API_ElemType& tool, APISettingsCreateProc* handlerCreateProc, APISettingsDestroyProc* handlerDestroyProc)
{
	return ACAPI_AddOnIntegration_InstallSettingsHandler (tool, handlerCreateProc, handlerDestroyProc);
}


GSErrCode ACAPI_Install_ClassificationVisibilityHandler (APIClassificationVisibilityHandlerProc* handlerProc)
{
	return ACAPI_AddOnIntegration_InstallClassificationVisibilityHandler (handlerProc);
}


GSErrCode ACAPI_Install_PropertyVisibilityHandler (APIPropertyVisibilityHandlerProc* handlerProc)
{
	return ACAPI_Property_InstallPropertyVisibilityHandler (handlerProc);
}


GSErrCode ACAPI_Install_PublisherSaveMethod (const char* mimeType, SaveProc* saveProc)
{
	return ACAPI_AddOnIntegration_InstallPublisherSaveMethod (mimeType, saveProc);
}


GSErrCode ACAPI_Install_PublisherSaveOption (const char* mimeType, SaveOptionProc* saveOptionProc)
{
	return ACAPI_AddOnIntegration_InstallPublisherSaveOption (mimeType, saveOptionProc);
}


GSErrCode ACAPI_Install_PublisherTranslatorGetter (const char* mimeType, TranslatorGetterProc* translatorGetterProc)
{
	return ACAPI_AddOnIntegration_InstallPublisherTranslatorGetter (mimeType, translatorGetterProc);
}


GSErrCode ACAPI_Install_PublisherDefaultTranslatorGetter (const char* mimeType, DefaultTranslatorGetterProc* defaultTranslatorGetterProc)
{
	return ACAPI_AddOnIntegration_InstallPublisherDefaultTranslatorGetter (mimeType, defaultTranslatorGetterProc);
}


GSErrCode ACAPI_Install_AttrManagerImportMethod (const GS::UniString& fileExtension, ImportAttrProc* importProc)
{
	return ACAPI_AddOnIntegration_InstallAttrManagerImportMethod (fileExtension, importProc);
}


GSErrCode ACAPI_Inform_AdditionalFileWasCreated (const IO::Location& path)
{
	return ACAPI_ProjectOperation_AdditionalFileWasCreated (path);
}


GSErrCode ACAPI_GetPreferences_Platform (Int32* version, GSSize* nByte, void* data, unsigned short* platformSign)
{
	return ACAPI_Preferences_Platform (version, nByte, data, platformSign);
}


GSErrCode ACAPI_Goodies_GetMarkerParent (const API_ElemType& elemType, API_LibPart& libPart)
{
	return ACAPI_LibraryPart_GetMarkerParent (elemType, libPart);
}


GSErrCode ACAPI_Goodies_GetElemTypeName (const API_ElemType& elemType, GS::UniString& name)
{
	return ACAPI_Element_GetElemTypeName (elemType, name);
}


GSErrCode ACAPI_Goodies_NeigIDToElemType (API_NeigID neigID, API_ElemType& elemType)
{
	return ACAPI_Element_NeigIDToElemType (neigID, elemType);
}


GSErrCode ACAPI_Goodies_ElemTypeToNeigID (const API_ElemType& elemType, API_NeigID& neigID)
{
	return ACAPI_Element_ElemTypeToNeigID (elemType, neigID);
}


GSErrCode ACAPI_Database_GetLast3DDefLevels (const GS::Array<API_ElemType>& elemTypes, GS::Array<double>& levels)
{
	return ACAPI_ProjectSetting_GetLast3DDefLevels (elemTypes, levels);
}


GSErrCode ACAPI_Database_SetLast3DDefLevels (const GS::Array<API_ElemType>& elemTypes, const GS::Array<double>& levels)
{
	return ACAPI_ProjectSetting_SetLast3DDefLevels (elemTypes, levels);
}


void ACAPI_Interface_SetElementHighlight (const GS::HashTable<API_Guid, API_RGBAColor>& highlightedElems, const GS::Optional<bool>& wireframe3D = GS::NoValue, const GS::Optional<API_RGBAColor>& nonHighlightedElemsColor = GS::NoValue)
{
	return ACAPI_UserInput_SetElementHighlight (highlightedElems, wireframe3D, nonHighlightedElemsColor);
}


void ACAPI_Interface_ClearElementHighlight ()
{
	return ACAPI_UserInput_ClearElementHighlight ();
}


void ACAPI_Interface_InvokeForwardDialog ()
{
	return ACAPI_Licensing_InvokeForwardDialog ();
}


GSErrCode ACAPI_Override_GetOverrideCombinationList (GS::Array<API_Guid>& combinationList)
{
	return ACAPI_GraphicalOverride_GetOverrideCombinationList (combinationList);
}


GSErrCode ACAPI_Override_GetOverrideRuleList (GS::Array<API_Guid>& ruleList)
{
	return ACAPI_GraphicalOverride_GetOverrideRuleList (ruleList);
}


GSErrCode ACAPI_Override_GetOverrideCombination (API_OverrideCombination& combination, GS::Array<API_Guid>* ruleList = nullptr)
{
	return ACAPI_GraphicalOverride_GetOverrideCombination (combination, ruleList);
}


GSErrCode ACAPI_Override_GetOverrideRule (API_OverrideRule& rule)
{
	return ACAPI_GraphicalOverride_GetOverrideRule (rule);
}


GSErrCode ACAPI_Override_CreateOverrideCombination (API_OverrideCombination& combination, const GS::Array<API_Guid>& ruleList)
{
	return ACAPI_GraphicalOverride_CreateOverrideCombination (combination, ruleList);
}


GSErrCode ACAPI_Override_CreateOverrideRule (API_OverrideRule& rule)
{
	return ACAPI_GraphicalOverride_CreateOverrideRule (rule);
}


GSErrCode ACAPI_Override_ChangeOverrideCombination (const API_OverrideCombination& combination, const GS::Array<API_Guid>* const ruleList = nullptr)
{
	return ACAPI_GraphicalOverride_ChangeOverrideCombination (combination, ruleList);
}


GSErrCode ACAPI_Override_ChangeOverrideRule (const API_OverrideRule& rule)
{
	return ACAPI_GraphicalOverride_ChangeOverrideRule (rule);
}


GSErrCode ACAPI_Override_DeleteOverrideCombination (const API_Guid& combination)
{
	return ACAPI_GraphicalOverride_DeleteOverrideCombination (combination);
}


GSErrCode ACAPI_Override_DeleteOverrideRule (const API_Guid& rule)
{
	return ACAPI_GraphicalOverride_DeleteOverrideRule (rule);
}


GSErrCode ACAPI_Attribute_GetUserData (API_Attr_Head* attrHead, API_AttributeUserData* userData)
{
	return ACAPI_UserData_GetUserData (attrHead, userData);
}


GSErrCode ACAPI_Attribute_SetUserData (API_Attr_Head* attrHead, const API_AttributeUserData* userData)
{
	return ACAPI_UserData_SetUserData (attrHead, userData);
}


GSErrCode ACAPI_Interface_CreateAttributePicker (const API_AttributePickerParams& attributePickerParams, GS::Owner<API_AttributePicker>& attributePicker)
{
	return ACAPI_Dialog_CreateAttributePicker (attributePickerParams, attributePicker);
}


GSErrCode ACAPI_LibPart_GetNum (Int32* count)
{
	return ACAPI_LibraryPart_GetNum (count);
}


GSErrCode ACAPI_LibPart_Search (API_LibPart* ancestor, bool createIfMissing, bool onlyPlaceable = false)
{
	return ACAPI_LibraryPart_Search (ancestor, createIfMissing, onlyPlaceable);
}


GSErrCode ACAPI_LibPart_PatternSearch (const API_LibPart* ancestor, const GS::UniString& pattern, API_LibPart result[50], Int32* numFound)
{
	return ACAPI_LibraryPart_PatternSearch (ancestor, pattern, result, numFound);
}


GSErrCode ACAPI_LibPart_Get (API_LibPart* libPart)
{
	return ACAPI_LibraryPart_Get (libPart);
}


GSErrCode ACAPI_LibPart_GetParams (Int32 libInd, double* a, double* b, Int32* addParNum, API_AddParType*** addPars)
{
	return ACAPI_LibraryPart_GetParams (libInd, a, b, addParNum, addPars);
}


GSErrCode ACAPI_LibPart_GetSection (Int32 libInd, API_LibPartSection* section, GSHandle* sectionHdl, GS::UniString* sectionStr, GS::UniString* password = nullptr)
{
	return ACAPI_LibraryPart_GetSection (libInd, section, sectionHdl, sectionStr, password);
}


GSErrCode ACAPI_LibPart_UpdateSection (Int32 libInd, const API_LibPartSection* section, GSHandle sectionHdl, GS::UniString* sectionStr, GS::UniString* password = nullptr)
{
	return ACAPI_LibraryPart_UpdateSection (libInd, section, sectionHdl, sectionStr, password);
}


GSErrCode ACAPI_LibPart_SetUpSect_2DDrawHdl ()
{
	return ACAPI_LibraryPart_SetUpSect_2DDrawHdl ();
}


GSErrCode ACAPI_LibPart_GetSect_2DDrawHdl (GSHandle* sectionHdl)
{
	return ACAPI_LibraryPart_GetSect_2DDrawHdl (sectionHdl);
}


GSErrCode ACAPI_LibPart_GetSect_ParamDef (const API_LibPart* libPart, API_AddParType** addPars, double* a, double* b, GSHandle sect2DDrawHdl, GSHandle* sectionHdl, GS::UniString* password = nullptr)
{
	return ACAPI_LibraryPart_GetSect_ParamDef (libPart, addPars, a, b, sect2DDrawHdl, sectionHdl, password);
}


GSErrCode ACAPI_LibPart_Create (const API_LibPart* libPart)
{
	return ACAPI_LibraryPart_Create (libPart);
}


GSErrCode ACAPI_LibPart_AddSection (const API_LibPartSection* section, GSHandle sectionHdl, GS::UniString* sectionStr)
{
	return ACAPI_LibraryPart_AddSection (section, sectionHdl, sectionStr);
}


GSErrCode ACAPI_LibPart_NewSection (const API_LibPartSection* section)
{
	return ACAPI_LibraryPart_NewSection (section);
}


GSErrCode ACAPI_LibPart_WriteSection (Int32 nByte, GSConstPtr data)
{
	return ACAPI_LibraryPart_WriteSection (nByte, data);
}


GSErrCode ACAPI_LibPart_EndSection ()
{
	return ACAPI_LibraryPart_EndSection ();
}


GSErrCode ACAPI_LibPart_Save (API_LibPart* libPart)
{
	return ACAPI_LibraryPart_Save (libPart);
}


GSErrCode ACAPI_LibPart_ShapePrims (Int32 libInd, const API_Guid& instanceElemGuid, short gdlContext, ShapePrimsProc* shapePrimsProc)
{
	return ACAPI_LibraryPart_ShapePrims (libInd, instanceElemGuid, gdlContext, shapePrimsProc);
}


GSErrCode ACAPI_LibPart_GetHotspots (Int32 libInd, const API_Guid& instanceElemGuid, Int32* nHotspots, API_PrimHotspot*** hotspots)
{
	return ACAPI_LibraryPart_GetHotspots (libInd, instanceElemGuid, nHotspots, hotspots);
}


GSErrCode ACAPI_LibPart_Register (API_LibPart* libPart)
{
	return ACAPI_LibraryPart_Register (libPart);
}


GSErrCode ACAPI_LibPart_RegisterAll (GS::Array<API_LibPart>* libParts)
{
	return ACAPI_LibraryPart_RegisterAll (libParts);
}


GSErrCode ACAPI_LibPart_GetSectionList (Int32 libInd, Int32* nSection, API_LibPartSection*** sections)
{
	return ACAPI_LibraryPart_GetSectionList (libInd, nSection, sections);
}


GSErrCode ACAPI_LibPart_GetDetails (Int32 libInd, API_LibPartDetails* details)
{
	return ACAPI_LibraryPart_GetDetails (libInd, details);
}


GSErrCode ACAPI_LibPart_SetDetails_ParamDef (const API_LibPart* libPart, GSHandle paramHdl, const API_LibPartDetails* details)
{
	return ACAPI_LibraryPart_SetDetails_ParamDef (libPart, paramHdl, details);
}


GSErrCode ACAPI_Element_GetConnectedElements (const API_Guid& guid, const API_ElemType& connectedElemType, GS::Array<API_Guid>* connectedElements, API_ElemFilterFlags filterBits = APIFilt_None, const API_Guid& renovationFilterGuid = APINULLGuid)
{
	return ACAPI_Grouping_GetConnectedElements (guid, connectedElemType, connectedElements, filterBits, renovationFilterGuid);
}


GSErrCode ACAPI_Element_Tool (const GS::Array<API_Guid>& elemGuids, API_ToolCmdID typeID, void* pars)
{
	return ACAPI_Grouping_Tool (elemGuids, typeID, pars);
}


GSErrCode ACAPI_Element_Select (const GS::Array<API_Neig>& selNeigs, bool add)
{
	return ACAPI_Selection_Select (selNeigs, add);
}


GSErrCode ACAPI_Element_DeselectAll ()
{
	return ACAPI_Selection_DeselectAll ();
}


GSErrCode ACAPI_Element_DeleteUserData (API_Elem_Head* elemHead)
{
	return ACAPI_UserData_DeleteUserData (elemHead);
}


GSErrCode ACAPI_Element_Link (const API_Guid& guid_linkFrom, const API_Guid& guid_linkTo, GSFlags linkFlags)
{
	return ACAPI_ElementLink_Link (guid_linkFrom, guid_linkTo, linkFlags);
}


GSErrCode ACAPI_Element_Unlink (const API_Guid& guid_linkFrom, const API_Guid& guid_linkTo)
{
	return ACAPI_ElementLink_Unlink (guid_linkFrom, guid_linkTo);
}


GSErrCode ACAPI_Element_GetLinks (const API_Guid& guid_linkFrom, GS::Array<API_Guid>* guids_linkTo)
{
	return ACAPI_ElementLink_GetLinks (guid_linkFrom, guids_linkTo);
}


GSErrCode ACAPI_Element_GetLinkFlags (const API_Guid& guid_linkFrom, const API_Guid& guid_linkTo, GSFlags* linkFlags)
{
	return ACAPI_ElementLink_GetLinkFlags (guid_linkFrom, guid_linkTo, linkFlags);
}


GSErrCode ACAPI_Element_GetObservedElements (GS::Array<API_Elem_Head>* elemHeads)
{
	return ACAPI_Notification_GetObservedElements (elemHeads);
}


GSErrCode ACAPI_Element_Get3DInfo (const API_Elem_Head& elemHead, API_ElemInfo3D* info3D)
{
	return ACAPI_ModelAccess_Get3DInfo (elemHead, info3D);
}


GSErrCode ACAPI_Element_ShapePrims (const API_Elem_Head& elemHead, ShapePrimsProc* shapePrimsProc)
{
	return ACAPI_DrawingPrimitive_ShapePrims (elemHead, shapePrimsProc);
}


GSErrCode ACAPI_Element_ShapePrimsExt (const API_Elem_Head& elemHead, ShapePrimsProc* shapePrimsProc, API_ShapePrimsParams* shapePrimsParams)
{
	return ACAPI_DrawingPrimitive_ShapePrimsExt (elemHead, shapePrimsProc, shapePrimsParams);
}


GSErrCode ACAPI_Element_GetLinkedPropertyObjects (const API_Elem_Head* head, bool* criteria, Int32* inviduallyLibInd, Int32** critLibInds, Int32* nCrits)
{
	return ACAPI_ElementLink_GetLinkedPropertyObjects (head, criteria, inviduallyLibInd, critLibInds, nCrits);
}


GSErrCode ACAPI_Element_SetLinkedPropertyObjects (API_Elem_Head* head, bool criteria, Int32 inviduallyLibInd)
{
	return ACAPI_ElementLink_SetLinkedPropertyObjects (head, criteria, inviduallyLibInd);
}


GSErrCode ACAPI_Element_GetCategoryValue (const API_Guid& elemGuid, const API_ElemCategory& elemCategory, API_ElemCategoryValue* elemCategoryValue)
{
	return ACAPI_Category_GetCategoryValue (elemGuid, elemCategory, elemCategoryValue);
}


GSErrCode ACAPI_Element_GetCategoryValueDefault (const API_ElemType& type, const API_ElemCategory& elemCategory, API_ElemCategoryValue* elemCategoryValue)
{
	return ACAPI_Category_GetCategoryValueDefault (type, elemCategory, elemCategoryValue);
}


GSErrCode ACAPI_Element_SetCategoryValue (const API_Guid& elemGuid, const API_ElemCategory& elemCategory, const API_ElemCategoryValue& elemCategoryValue)
{
	return ACAPI_Category_SetCategoryValue (elemGuid, elemCategory, elemCategoryValue);
}


GSErrCode ACAPI_Element_SetCategoryValueDefault (const API_ElemType& type, const API_ElemCategory& elemCategory, const API_ElemCategoryValue& elemCategoryValue)
{
	return ACAPI_Category_SetCategoryValueDefault (type, elemCategory, elemCategoryValue);
}


GSErrCode ACAPI_ElementList_AddProperty (API_PropertyDefinition& definition, const GS::Array<API_Guid>& elemGuids)
{
	return ACAPI_Property_AddProperty (definition, elemGuids);
}


GSErrCode ACAPI_ElementList_ModifyPropertyValue (const API_Property& property, const GS::Array<API_Guid>& elemGuids)
{
	return ACAPI_Property_ModifyPropertyValue (property, elemGuids);
}


GSErrCode ACAPI_ElementList_DeleteProperty (const API_Guid& definitionGuid, const GS::Array<API_Guid>& elemGuids)
{
	return ACAPI_Property_DeleteProperty (definitionGuid, elemGuids);
}


GSErrCode ACAPI_AttributeList_AddProperty (API_PropertyDefinition& definition, const GS::Array<API_Attr_Head>& attrHeaders)
{
	return ACAPI_Attribute_AddProperty (definition, attrHeaders);
}


GSErrCode ACAPI_AttributeList_ModifyPropertyValue (const API_Property& property, const GS::Array<API_Attr_Head>& attrHeaders)
{
	return ACAPI_Attribute_ModifyPropertyValue (property, attrHeaders);
}


GSErrCode ACAPI_AttributeList_DeleteProperty (const API_Guid& definitionGuid, const GS::Array<API_Attr_Head>& attrHeaders)
{
	return ACAPI_Attribute_DeleteProperty (definitionGuid, attrHeaders);
}


GSErrCode ACAPI_Element_GrantElements (const GS::Array<API_Guid>& elemGuids, short toUserId)
{
	return ACAPI_Teamwork_GrantElements (elemGuids, toUserId);
}


GSErrCode ACAPI_ElemComponent_GetPropertyDefinitions (const API_ElemComponentID& elemComponent, API_PropertyDefinitionFilter filter, GS::Array<API_PropertyDefinition>& propertyDefinitions)
{
	return ACAPI_Element_GetPropertyDefinitions (elemComponent, filter, propertyDefinitions);
}


GSErrCode ACAPI_ElemComponent_GetPropertyValue (const API_ElemComponentID& elemComponent, const API_Guid& propertyDefinitionGuid, API_Property& property)
{
	return ACAPI_Element_GetPropertyValue (elemComponent, propertyDefinitionGuid, property);
}


GSErrCode ACAPI_ElemComponent_GetPropertyValues (const API_ElemComponentID& elemComponent, const GS::Array<API_PropertyDefinition>& propertyDefinitions, GS::Array<API_Property>& properties)
{
	return ACAPI_Element_GetPropertyValues (elemComponent, propertyDefinitions, properties);
}


GSErrCode ACAPI_ElemComponent_GetPropertyValuesByGuid (const API_ElemComponentID& elemComponent, const GS::Array<API_Guid>& propertyDefinitions, GS::Array<API_Property>& properties)
{
	return ACAPI_Element_GetPropertyValuesByGuid (elemComponent, propertyDefinitions, properties);
}


GSErrCode ACAPI_ElemDifferenceGenerator_GetState (API_ElemDifferenceGeneratorTypeID type, API_ElemDifferenceGeneratorState* diffGeneratorState)
{
	return ACAPI_DifferenceGenerator_GetState (type, diffGeneratorState);
}


GSErrCode ACAPI_ElemDifferenceGenerator_GenerateDifference (API_ElemDifferenceGeneratorTypeID type, API_ElemDifferenceGeneratorState* diffState1, API_ElemDifferenceGeneratorState* diffState2, API_ElemDifference& difference)
{
	return ACAPI_DifferenceGenerator_GenerateDifference (type, diffState1, diffState2, difference);
}


GSErrCode ACAPI_Element_GetVisualOverriddenImage (const API_Guid& elemGuid, API_VisualOverriddenImage* image)
{
	return ACAPI_GraphicalOverride_GetVisualOverriddenImage (elemGuid, image);
}


GSErrCode ACAPI_Element_GetNoteAutotexts (const API_ElemType& noteOwnerType, std::unordered_map<API_NoteAutotextID, std::unordered_set<API_ElemType>>& elemTypesForAutotextIDs, const GS::Optional<API_AppearID>& dimAppear = GS::NoValue)
{
	return ACAPI_AutoText_GetNoteAutotexts (noteOwnerType, elemTypesForAutotextIDs, dimAppear);
}


GSErrCode ACAPI_Element_GetNoteKeywordForAutotextID (API_NoteAutotextID autotextID, GS::UniString& keyword)
{
	return ACAPI_AutoText_GetNoteKeywordForAutotextID (autotextID, keyword);
}


GSErrCode ACAPI_MarkUp_Create (API_MarkUpType& markUp)
{
	return ACAPI_Markup_Create (markUp);
}


GSErrCode ACAPI_MarkUp_GetList (const API_Guid& elemGuid, GS::Array<API_MarkUpType>* markUpList, bool* asCorrected = nullptr)
{
	return ACAPI_Markup_GetList (elemGuid, markUpList, asCorrected);
}


GSErrCode ACAPI_MarkUp_Delete (const API_Guid& markUpGuid, bool acceptAllElements = false)
{
	return ACAPI_Markup_Delete (markUpGuid, acceptAllElements);
}


GSErrCode ACAPI_MarkUp_AttachElements (const API_Guid& markUpGuid, const GS::Array<API_Guid>& elemList, API_MarkUpComponentTypeID type, GS::HashTable<API_Guid, API_Guid>* modificationElemTable = nullptr)
{
	return ACAPI_Markup_AttachElements (markUpGuid, elemList, type, modificationElemTable);
}


GSErrCode ACAPI_MarkUp_DetachElements (const API_Guid& markUpGuid, const GS::Array<API_Guid>& elemList)
{
	return ACAPI_Markup_DetachElements (markUpGuid, elemList);
}


GSErrCode ACAPI_MarkUp_GetAttachedElements (const API_Guid& markUpGuid, API_MarkUpComponentTypeID type, GS::Array<API_Guid>& attachedElements)
{
	return ACAPI_Markup_GetAttachedElements (markUpGuid, type, attachedElements);
}


GSErrCode ACAPI_MarkUp_AddComment (const API_Guid& markUpGuid, API_MarkUpCommentType& comment)
{
	return ACAPI_Markup_AddComment (markUpGuid, comment);
}


GSErrCode ACAPI_MarkUp_GetComments (const API_Guid& markUpGuid, GS::Array<API_MarkUpCommentType>* commentList)
{
	return ACAPI_Markup_GetComments (markUpGuid, commentList);
}


GSErrCode ACAPI_MarkUp_ExportToBCF (const IO::Location& fileLoc, const GS::Array<API_Guid>& markupEntryIds, const bool useExternalId = false, const bool alignBySurveyPoint = true)
{
	return ACAPI_Markup_ExportToBCF (fileLoc, markupEntryIds, useExternalId, alignBySurveyPoint);
}


GSErrCode ACAPI_MarkUp_ImportFromBCF (const IO::Location& fileLoc, const bool silentMode, APIIFCRelationshipDataProc* ifcRelationshipDataProc, const void* par1, const bool openMarkUpPalette = false, const bool alignBySurveyPoint = true)
{
	return ACAPI_Markup_ImportFromBCF (fileLoc, silentMode, ifcRelationshipDataProc, par1, openMarkUpPalette, alignBySurveyPoint);
}


GSErrCode ACAPI_Element_Update_Drawings (const GS::Array<API_Guid>& drawingsToUpdate)
{
	return ACAPI_Drawing_Update_Drawings (drawingsToUpdate);
}


GSErrCode ACAPI_ElementGroup_Create (const GS::Array<API_Guid>& elemGuids, API_Guid* groupGuid = nullptr, const API_Guid* parentGroupGuid = nullptr)
{
	return ACAPI_ElementSet_Create (elemGuids, groupGuid, parentGroupGuid);
}


GSErrCode ACAPI_ElementGroup_GetGroup (const API_Guid& elemGuid, API_Guid* groupGuid)
{
	return ACAPI_Grouping_GetGroup (elemGuid, groupGuid);
}


GSErrCode ACAPI_ElementGroup_GetRootGroup (const API_Guid& elemGuid, API_Guid* rootGroupGuid)
{
	return ACAPI_Grouping_GetRootGroup (elemGuid, rootGroupGuid);
}


GSErrCode ACAPI_ElementGroup_GetGroupedElems (const API_Guid& groupGuid, GS::Array<API_Guid>* elemGuids)
{
	return ACAPI_Grouping_GetGroupedElems (groupGuid, elemGuids);
}


GSErrCode ACAPI_ElementGroup_GetAllGroupedElems (const API_Guid& groupGuid, GS::Array<API_Guid>* elemGuids)
{
	return ACAPI_Grouping_GetAllGroupedElems (groupGuid, elemGuids);
}


GSErrCode ACAPI_ElementGroup_GetUserData (const API_Guid& groupGuid, API_UserData* userData)
{
	return ACAPI_Grouping_GetUserData (groupGuid, userData);
}


GSErrCode ACAPI_ElementGroup_SetUserData (const API_Guid& groupGuid, const API_UserData* userData)
{
	return ACAPI_Grouping_SetUserData (groupGuid, userData);
}


GSErrCode ACAPI_3D_GetNum (API_3DTypeID typeID, Int32* count)
{
	return ACAPI_ModelAccess_GetNum (typeID, count);
}


GSErrCode ACAPI_3D_GetComponent (API_Component3D* component)
{
	return ACAPI_ModelAccess_GetComponent (component);
}


GSErrCode ACAPI_3D_DecomposePgon (Int32 ipgon, Int32*** cpoly)
{
	return ACAPI_ModelAccess_DecomposePgon (ipgon, cpoly);
}


GSErrCode ACAPI_3D_CreateSight (void** newSightPtr)
{
	return ACAPI_Sight_CreateSight (newSightPtr);
}


GSErrCode ACAPI_3D_SelectSight (void* sight, void** oldSightPtr)
{
	return ACAPI_Sight_SelectSight (sight, oldSightPtr);
}


GSErrCode ACAPI_3D_DeleteSight (void* sight)
{
	return ACAPI_Sight_DeleteSight (sight);
}


GSErrCode ACAPI_3D_GetCurrentWindowSight (void** sightPtr)
{
	return ACAPI_Sight_GetCurrentWindowSight (sightPtr);
}


GSErrCode ACAPI_3D_GetCutPolygonInfo (Int32 bodyIndex, const API_Plane3D& cutPlane, GS::Array<Geometry::MultiPolygon2D>* resPolygons = nullptr, double* area = nullptr)
{
	return ACAPI_CuttingPlane_GetCutPolygonInfo (bodyIndex, cutPlane, resPolygons, area);
}


Int32 ACAPI_ListData_GetSetNum ()
{
	return ACAPI_OldListing_GetSetNum ();
}


GSErrCode ACAPI_ListData_GetSet (API_ListDataSetType* listdataSet)
{
	return ACAPI_OldListing_GetSet (listdataSet);
}


GSErrCode ACAPI_ListData_GetNum (Int32 setIndex, API_ListDataID typeID, Int32* count)
{
	return ACAPI_OldListing_GetNum (setIndex, typeID, count);
}


GSErrCode ACAPI_ListData_Get (API_ListData* listdata)
{
	return ACAPI_OldListing_Get (listdata);
}


GSErrCode ACAPI_ListData_Search (API_ListData* listdata)
{
	return ACAPI_OldListing_Search (listdata);
}


GSErrCode ACAPI_ListData_GetLocal (Int32 libIndex, const API_Elem_Head* elemHead, API_ListData* listdata)
{
	return ACAPI_OldListing_GetLocal (libIndex, elemHead, listdata);
}


GSErrCode ACAPI_Command_Test (const API_ModulID* mdid, GSType cmdID, Int32 cmdVersion)
{
	return ACAPI_AddOnAddOnCommunication_Test (mdid, cmdID, cmdVersion);
}


GSErrCode ACAPI_Command_Call (const API_ModulID* mdid, GSType cmdID, Int32 cmdVersion, GSHandle params, GSPtr resultData, bool silentMode)
{
	return ACAPI_AddOnAddOnCommunication_Call (mdid, cmdID, cmdVersion, params, resultData, silentMode);
}


GSErrCode ACAPI_Command_ExternalCall (const IO::Location* projectFileLoc, const API_ModulID* mdid, GSType cmdID, Int32 cmdVersion, GSHandle params, bool silentMode, APIExternalCallBackProc* externalCallbackProc)
{
	return ACAPI_AddOnAddOnCommunication_ExternalCall (projectFileLoc, mdid, cmdID, cmdVersion, params, silentMode, externalCallbackProc);
}


GSErrCode ACAPI_Command_CallFromEventLoop (const API_ModulID* mdid, GSType cmdID, Int32 cmdVersion, GSHandle paramsHandle, bool silentMode, APICommandCallBackProc* callbackProc)
{
	return ACAPI_AddOnAddOnCommunication_CallFromEventLoop (mdid, cmdID, cmdVersion, paramsHandle, silentMode, callbackProc);
}


GSErrCode ACAPI_Notify_CatchProjectEvent (GSFlags eventTypes, APIProjectEventHandlerProc* handlerProc)
{
	return ACAPI_ProjectOperation_CatchProjectEvent (eventTypes, handlerProc);
}


GSErrCode ACAPI_Notify_CatchViewEvent (GSFlags eventTypes, API_NavigatorMapID mapId, APIViewEventHandlerProc* handlerProc)
{
	return ACAPI_Notification_CatchViewEvent (eventTypes, mapId, handlerProc);
}


GSErrCode ACAPI_Notify_CatchToolChange (APIToolChangeHandlerProc* handlerProc)
{
	return ACAPI_Notification_CatchToolChange (handlerProc);
}


GSErrCode ACAPI_Notify_CatchSelectionChange (APISelectionChangeHandlerProc* handlerProc)
{
	return ACAPI_Notification_CatchSelectionChange (handlerProc);
}


GSErrCode ACAPI_Notify_CatchChangeDefaults (const API_ToolBoxItem* elemType, APIDefaultsChangeHandlerProc* handlerProc)
{
	return ACAPI_Element_CatchChangeDefaults (elemType, handlerProc);
}


GSErrCode ACAPI_Notify_CatchNewElement (const API_ToolBoxItem* elemType, APIElementEventHandlerProc* handlerProc)
{
	return ACAPI_Element_CatchNewElement (elemType, handlerProc);
}


GSErrCode ACAPI_Notify_CatchAttributeReplacement (APIAttributeReplacementHandlerProc* handlerProc)
{
	return ACAPI_Notification_CatchAttributeReplacement (handlerProc);
}


GSErrCode ACAPI_Notify_InstallElementObserver (APIElementEventHandlerProc* handlerProc)
{
	return ACAPI_Element_InstallElementObserver (handlerProc);
}


GSErrCode ACAPI_Notify_GetTranParams (API_ActTranPars* actTranPars)
{
	return ACAPI_Notification_GetTranParams (actTranPars);
}


GSErrCode ACAPI_Notify_GetParentElement (API_Element* element, API_ElementMemo* memo, UInt64 mask, API_ElementUserData* userData)
{
	return ACAPI_Notification_GetParentElement (element, memo, mask, userData);
}


GSErrCode ACAPI_Notify_CatchElementReservationChange (APIReservationChangeHandlerProc* handlerProc, const GS::HashSet<API_Guid>* filterElementsInterestedOnly = nullptr)
{
	return ACAPI_Notification_CatchElementReservationChange (handlerProc, filterElementsInterestedOnly);
}


GSErrCode ACAPI_Notify_CatchLockableReservationChange (APILockChangeHandlerProc* handlerProc, const GS::HashSet<API_Guid>* filterLockablesInterestedOnly = nullptr)
{
	return ACAPI_Notification_CatchLockableReservationChange (handlerProc, filterLockablesInterestedOnly);
}


GSErrCode ACAPI_Notify_CatchLicenseBorrowStatusChange (APILicenseBorrowStatusChangeHandlerProc* handlerProc)
{
	return ACAPI_Licensing_CatchLicenseBorrowStatusChange (handlerProc);
}


GSErrCode ACAPI_Notify_ClassificationVisibilityChanged ()
{
	return ACAPI_Notification_ClassificationVisibilityChanged ();
}


GSErrCode ACAPI_Notify_PropertyVisibilityChanged ()
{
	return ACAPI_Notification_PropertyVisibilityChanged ();
}


GSErrCode ACAPI_Notify_RegisterEventHandler (GS::Owner<API_IEventHandler> eventHandler, API_Guid& id)
{
	return ACAPI_Notification_RegisterEventHandler (eventHandler.Pass (), id);
}


GSErrCode ACAPI_Notify_UnregisterEventHandler (const API_Guid& id)
{
	return ACAPI_Notification_UnregisterEventHandler (id);
}


bool ACAPI_TeamworkControl_HasConnection ()
{
	return ACAPI_Teamwork_HasConnection ();
}


bool ACAPI_TeamworkControl_IsOnline ()
{
	return ACAPI_Teamwork_IsOnline ();
}


bool ACAPI_TeamworkControl_IsServerLibPart (const IO::Location& location)
{
	return ACAPI_Teamwork_IsServerLibPart (location);
}


GSErrCode ACAPI_TeamworkControl_GetTeamworkProjectDetails (const IO::Location& twProjectLocation, GS::UniString* serverUrl = nullptr, GS::UniString* projectName = nullptr, GS::UniString* userName = nullptr)
{
	return ACAPI_Teamwork_GetTeamworkProjectDetails (twProjectLocation, serverUrl, projectName, userName);
}


bool ACAPI_TeamworkControl_HasCreateRight (const API_Guid& objectId)
{
	return ACAPI_Teamwork_HasCreateRight (objectId);
}


bool ACAPI_TeamworkControl_HasDeleteModifyRight (const API_Guid& objectId)
{
	return ACAPI_Teamwork_HasDeleteModifyRight (objectId);
}


API_LockableStatus ACAPI_TeamworkControl_GetLockableStatus (const API_Guid& objectId, GS::PagedArray<short>* conflicts = nullptr)
{
	return ACAPI_Teamwork_GetLockableStatus (objectId, conflicts);
}


API_Guid ACAPI_TeamworkControl_FindLockableObjectSet (const GS::UniString& objectSetName)
{
	return ACAPI_Teamwork_FindLockableObjectSet (objectSetName);
}


GSErrCode ACAPI_TeamworkControl_ReserveLockable (const API_Guid& objectId, GS::PagedArray<short>* conflicts = nullptr, bool enableDialogs = true)
{
	return ACAPI_Teamwork_ReserveLockable (objectId, conflicts, enableDialogs);
}


GSErrCode ACAPI_TeamworkControl_ReleaseLockable (const API_Guid& objectId, bool enableDialogs = true)
{
	return ACAPI_Teamwork_ReleaseLockable (objectId, enableDialogs);
}


GSErrCode ACAPI_TeamworkControl_ReserveElements (const GS::Array<API_Guid>& elements, GS::HashTable<API_Guid, short>* conflicts = nullptr, bool enableDialogs = true)
{
	return ACAPI_Teamwork_ReserveElements (elements, conflicts, enableDialogs);
}


GSErrCode ACAPI_TeamworkControl_ReleaseElements (const GS::Array<API_Guid>& elements, bool enableDialogs = true)
{
	return ACAPI_Teamwork_ReleaseElements (elements, enableDialogs);
}


GSErrCode ACAPI_TeamworkControl_ReserveHotlinkCacheManagement (short* conflict = nullptr)
{
	return ACAPI_Teamwork_ReserveHotlinkCacheManagement (conflict);
}


GSErrCode ACAPI_TeamworkControl_ReleaseHotlinkCacheManagement ()
{
	return ACAPI_Teamwork_ReleaseHotlinkCacheManagement ();
}


GSErrCode ACAPI_TeamworkControl_GetHotlinkCacheManagementOwner (short* owner)
{
	return ACAPI_Teamwork_GetHotlinkCacheManagementOwner (owner);
}


GSErrCode ACAPI_TeamworkControl_GetUsernameFromId (short userId, GS::UniString* username)
{
	return ACAPI_Teamwork_GetUsernameFromId (userId, username);
}


GSErrCode ACAPI_TeamworkControl_SendChanges (const GS::UniString& comment = "")
{
	return ACAPI_Teamwork_SendChanges (comment);
}


GSErrCode ACAPI_TeamworkControl_ReceiveChanges ()
{
	return ACAPI_Teamwork_ReceiveChanges ();
}


GSErrCode ACAPI_ActionCenter_Check (API_ActionCenterItemID item)
{
	return ACAPI_Window_Check (item);
}


UInt32 ACAPI_Protection_GetProtectionMode ()
{
	return ACAPI_Licensing_GetProtectionMode ();
}


UInt32 ACAPI_Protection_GetSerialNumber ()
{
	return ACAPI_Licensing_GetSerialNumber ();
}


UInt16 ACAPI_Protection_GetBoxMask ()
{
	return ACAPI_Licensing_GetBoxMask ();
}


GS::UniString ACAPI_Protection_GetConfigurationNumber ()
{
	return ACAPI_Licensing_GetConfigurationNumber ();
}


UInt32 ACAPI_Protection_GetNumberOfLicenses ()
{
	return ACAPI_Licensing_GetNumberOfLicenses ();
}


GSTime ACAPI_Protection_GetExpirationTime ()
{
	return ACAPI_Licensing_GetExpirationTime ();
}


GS::UniString ACAPI_Protection_GetPartnerId ()
{
	return ACAPI_Licensing_GetPartnerId ();
}


bool ACAPI_Protection_IsSSALevelAtLeast (API_SSALevel requiredLevel)
{
	return ACAPI_Licensing_IsSSALevelAtLeast (requiredLevel);
}


GSErrCode ACAPI_SetPreferences_OldVersion (Int32 version, GSSize nByte, const void* data, unsigned short platformSign, API_FTypeID oldPlanFileID)
{
	return ACAPI_Preferences_SetOldVersion (version, nByte, data, platformSign, oldPlanFileID);
}

#endif // __GS_ACAPI_MIGRATION_HEADER_HPP__
