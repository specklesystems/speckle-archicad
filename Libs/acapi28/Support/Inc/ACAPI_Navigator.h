#ifndef ACAPINAVIGATOR_H
#define	ACAPINAVIGATOR_H

// GSRoot
#include "GSRoot.hpp"
#include "Array.hpp"

// own
#include "APICalls.h"
#include "APIdefs.h"

class INavigatorCallbackInterface;


/**
 * @brief Retrieves the number of Publisher Sets.
 * @ingroup Navigator
 * @param setNum [out] Number of Publisher Sets.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - setNum is nullptr.
 * 			- APIERR_GENERAL - No open project
 * @remarks This function is used to retrieve the number of Publisher Sets.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Navigator_GetNavigatorSetNum-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Navigator_GetNavigatorSetNum (Int32* setNum);


/**
 * @brief Retrieves information of a Project Navigator Map or Publisher Set.
 * @ingroup Navigator
 * @param navigatorSet [in/out] Data of the Project Navigator's Map. Identified with mapId.
 * @param index [in] Index of the required set. Used only for Publisher Sets.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The navigatorSet or the index parameter is nullptr.
 * 			- APIERR_BADINDEX - The index parameter contains invalid data.
 * 			- APIERR_GENERAL - No open project.
 * @remarks This function is used to retrieve the name and GUID parameters of a given Project Navigator Map.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Navigator_GetNavigatorSet-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Navigator_GetNavigatorSet (API_NavigatorSet* navigatorSet, Int32* index = nullptr);


/**
 * @brief Retrieves a navigator item.
 * @ingroup Navigator
 * @param guid [in] The GUID of the navigator item
 * @param navigatorItem [in/out] Data of the navigator item (you should set mapId for performance).
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The guid or the navigatorItem parameter is nullptr, or contains invalid data.
 * 			- APIERR_GENERAL - No open project.
 * @remarks This function is used to get an item of the Project Navigator.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Navigator_GetNavigatorItem-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Navigator_GetNavigatorItem (const API_Guid* guid, API_NavigatorItem* navigatorItem);


/**
 * @brief Retrieves the parent item of a navigator item.
 * @ingroup Navigator
 * @param guid [in] The GUID of the navigator item
 * @param parent [in/out] The parent item of the navigator item (you should set mapId for performance).
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The guid or the parent parameter is nullptr, or contains invalid data.
 * 			- APIERR_GENERAL - No open project.
 * @remarks This function is used to get the parent node of a given item of the Project Navigator.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Navigator_GetNavigatorParentItem-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Navigator_GetNavigatorParentItem (const API_Guid* guid, API_NavigatorItem* parent);


/**
 * @brief Retrieves the number of children of a navigator item.
 * @ingroup Navigator
 * @param parent [in] The requested navigator item identified with GUID (you should set mapId for performance).
 * @param num [out] The number of children of the navigator item
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The parent or the num parameter is nullptr, or contains invalid data.
 * 			- APIERR_GENERAL - No open project
 * @remarks This function retrieves the number of child items of a given item of the Project Navigator.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Navigator_GetNavigatorChildNum-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Navigator_GetNavigatorChildNum (API_NavigatorItem* parent, Int32* num);


/**
 * @brief Retrieves the child items of a navigator item.
 * @ingroup Navigator
 * @param item [in] The requested navigator item identified with GUID (optional you should set mapId for performance).
 * @param items [out] Data of the child navigator items (optional parameter)
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The item parameter is nullptr or contains invalid data, or both the items and itemsArray parameters are nullptr.
 * 			- APIERR_GENERAL - No open project.
 * @remarks This function is used to get the child items of a given item of the Project Navigator.
 * 			Do not forget to dispose the items handle if not needed any more.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Navigator_GetNavigatorChildrenItems-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Navigator_GetNavigatorChildrenItems (API_NavigatorItem* item, GS::Array<API_NavigatorItem>* items);


/**
 * @brief Retrives a navigator view.
 * @ingroup Navigator
 * @param navigatorItem [in] The requested navigator item identified with GUID (you should set mapId for performance).
 * @param navigatorView [out] Data of the navigator item
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The navigatorItem or the navigatorView parameter is nullptr, or contains invalid data.
 * 			- APIERR_GENERAL - No open project.
 * @remarks This function is used to get the view settings of an item of the Project Navigator.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Navigator_GetNavigatorView-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Navigator_GetNavigatorView (API_NavigatorItem* navigatorItem, API_NavigatorView* navigatorView);


/**
 * @brief Searches the navigator items of the requested database.
 * @ingroup Navigator
 * @param item [in] The identification parameters of the requested Viewpoint/database. The itemType parameter is compulsory.
 * @param items [out] The navigator items matching the specified Viewpoint/database (optional parameter)
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The item parameter is nullptr or contains invalid data, or both the items and itemsArray parameters are nullptr.
 * 			- APIERR_GENERAL - No open project.
 * @remarks This function retrieves the items of the Project Navigator which refer to the specified Viewpoint/database.
 * 			Do not forget to dispose the items handle if it is not needed any more.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Navigator_SearchNavigatorItem-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Navigator_SearchNavigatorItem (API_NavigatorItem* item, GS::Array<API_NavigatorItem>* items);


/**
 * @brief Sets the given Project Navigator item and its view settings.
 * @ingroup Navigator
 * @param navigatorItem [in] The navigator item identified with its guid.
 * @param navigatorView [in] New view settings of the specified item (can be nullptr).
 * @return
 * 			- APIERR_BADPARS - The specified navigator item doesn't exist neither in Public View Map nor in My View Map (TeamWork mode).
 * 			- APIERR_NOTMINE - You have no permission to change the item.
 * 			- NoError - The function has completed with success.
 * @remarks Use this function to change a Project Navigator item's name or ID and optionally its view settings. Only View Map items are modifiable.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Navigator_ChangeNavigatorView-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Navigator_ChangeNavigatorView (API_NavigatorItem* navigatorItem, API_NavigatorView* navigatorView);


/**
 * @brief Creates a new Navigator View.
 * @ingroup Navigator
 * @param navigatorItem [in/out] The item used for creating the view; its guid member will be filled on output.
 * @param navigatorView [out] The created view (unless the navigator item's type is @c API_FolderNavItem).
 * @param parent These parameters are used, when one wants to create a new folder item on the view map, and in this case the first guid is the guid of the node whereunder the new navitem will be placed (the "parent").
 * @param previousSibling These parameters are used, when one wants to create a new folder item on the view map, and in this case the navigatorView parameter can be nullptr. If you create an other type of element, then this parameter can be nullptr.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - You will encounter with this return value, if something was wrong with the parameters, for example the item was nullptr, orin the parentAndChild array, the first guid is not the guid of the second's father.
 * @remarks This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Navigator_NewNavigatorView-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Navigator_NewNavigatorView (API_NavigatorItem* navigatorItem, API_NavigatorView* navigatorView, const GS::Guid* parent = nullptr, const GS::Guid* previousSibling = nullptr);


/**
 * @brief Deletes the given navigator view.
 * @ingroup Navigator
 * @param viewGuid The unique identifier of the view.
 * @param silentMode This parameter is used for turn on/off the warning messages comes from Archicad during deleting a view.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - You will encounter with this return value, if something was wrong with the parameters.
 * @remarks This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Navigator_DeleteNavigatorView-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Navigator_DeleteNavigatorView (const API_Guid* viewGuid, const bool* silentMode);


/**
 * @brief Modifies the given Project Navigator item.
 * @ingroup Navigator
 * @param navigatorItem [in] The navigator item identified with its guid.
 * @return
 * 			- APIERR_BADPARS - The specified navigator item doesn't exist neither in Public View Map nor in My View Map (TeamWork mode).
 * 			- APIERR_NOTMINE - You have no permission to change the item.
 * 			- NoError - The function has completed with success.
 * @remarks Use this function to change a Project Navigator item's name or ID. Only View Map items are modifiable.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Navigator_ChangeNavigatorItem-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Navigator_ChangeNavigatorItem (API_NavigatorItem* navigatorItem);


/**
 * @brief With this function a navigator item can be moved to an other place. It can be used with items on the layout map and on the view maps (in case of teamworking on the public and on the users' own view map as well.
 * @ingroup Navigator
 * @param source The guid of the item, what you want to replace.
 * @param parent The new parent of the replaced item.
 * @param child If it is nullptr, then the item will be inserted to the first place on the actual level, otherwise the it will be inserted after the child.
 * @return
 * 			- NoError - Everything is OK.
 * 			- APIERR_BADPARS - This value can be returned in several cases: the source or the parent parameter is nullptr, or the source or the parent guid was not found in the layout map and neither in the view maps, or the source item cannot be moved to the desired destination.
 * 			- APIERR_NOACCESSRIGHT - In case of teamworking, if the user not owns (locked) the item which (s)he wants to move then the user has no access right...
 * @remarks This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_Navigator_SetNavigatorItemPosition (const GS::Guid* source, const GS::Guid* parent, const GS::Guid* child);


/**
 * @brief Clones a Navigator item from the project map to view map.
 * @ingroup Navigator
 * @param sourceItemId [in] Navigator item to be cloned.
 * @param parentItemId [in] Parent navigator item of the cloned navigator item.
 * @param createdItemId [out] Cloned navigator item.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - sourceItemId or parentItemId is nullptr or invalid.
 * 			- APIERR_GENERAL - General internal error.
 * @remarks This function is used to clone a navigator item from the project map to view map by specifying the navigator item to be cloned and the parent in the view map.
 * 			The properties of the cloned view can be changed with the @ref ACAPI_Navigator_ChangeNavigatorView navigator function.
 */
__APIEXPORT GSErrCode ACAPI_Navigator_CloneProjectMapItemToViewMap (const API_Guid* sourceItemId, const API_Guid* parentItemId, API_Guid* createdItemId);


/**
 * @brief Creates a new Navigator viewpoint root, group or leaf node in the Project Map.
 * @ingroup Navigator
 * @param viewPointData [in/out] Details of the viewpoint root, group or leaf node to be created. The guid member will be filled out on return.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - viewPointData was nullptr.
 * 			viewPointData.itemType was @c API_NavigatorAddOnViewPointUndefinedID.
 * 			- APIERR_BADID - viewPointData.guid is already used, i.e. an object already exists with the same GUID. Note: if viewPointData.guid was set to APINULLGuid, a GUID is generated for the Navigator root group or group to be created, and this error can never come.
 * 			viewPointData.parentGuid does not designate an already existing viewpoint group.
 * 			- APIERR_NOACCESSRIGHT - The function was called in teamwork mode, and a root or group was to be created.
 * @remarks Creating a root group:
 * 			Set viewPointData.itemType to @c API_NavigatorAddOnViewPointRootID. When creating a root group, viewPointData.parentGuid and viewPointData.viewSettingsFlags is ignored. If viewPointData.guid was provided on input, the function creates a root group with the given GUID. If an object with the same GUID already exists, the function returns APIERR_BADID. Creating a group Set viewPointData.itemType to @c API_NavigatorAddOnViewPointGroupID. When creating a group, viewPointData.viewSettingsFlags is ignored. If viewPointData.guid was provided on input, the function creates a group with the given GUID. If an object with the same GUID already exists, the function returns APIERR_BADID. Creating a leaf node Set viewPointData.itemType to @c API_NavigatorAddOnViewPointNodeID. viewPointData.guid is ignored. A leaf node is always created with an internally generated GUID.
 * 			Note: In teamwork mode you cannot create, change or delete viewpoint roots or groups.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Navigator_CreateNavigatorVPItem-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Navigator_CreateNavigatorVPItem (API_NavigatorAddOnViewPointData* viewPointData);


/**
 * @brief Deletes a Navigator viewpoint root, group or leaf node from the Project Map.
 * @ingroup Navigator
 * @param guid [in] GUID of the viewpoint root, group or leaf node to delete.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - guid was nullptr.
 * 			- APIERR_BADID - guid designetes an object which does not exist, or it is not a Navigator viewpoint root, group or leaf node of the current AddOn.
 * 			- APIERR_NOACCESSRIGHT - The function was called in teamwork mode, and a root or group was to be deleted.
 * 			- APIERR_NOTMINE - In teamwork mode, the current user has not reserved the viewpoint root, group or leaf node designated by guid.
 * @remarks If a root or group is deleted, all descendants are also deleted.
 * 			Note: In teamwork mode you cannot create, change or delete viewpoint roots or groups.
 */
__APIEXPORT GSErrCode ACAPI_Navigator_DeleteNavigatorVPItem (const API_Guid* guid);


/**
 * @brief Changes an existing Navigator viewpoint root, group or leaf node in the Project Map.
 * @ingroup Navigator
 * @param viewPointData [in] Details of the viewpoint root, group or leaf node to be modified.
 * 						The guid member designates which item to modify. The other members should hold the new values.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - viewPointData was nullptr.
 * 			- APIERR_BADID - viewPointData.guid designetes an object which does not exist, or it is not a Navigator viewpoint root, group or leaf node of the current AddOn.
 * 			- APIERR_NOACCESSRIGHT - The function was called in teamwork mode, and a root or group was to be modified.
 * 			- APIERR_NOTMINE - In teamwork mode, the current user has not reserved the viewpoint root, group or leaf node designated by viewPointData.guid.
 * @remarks viewPointData.parentGuid is ignored, i.e. the hierarchy cannot be changed with this function.
 * 			viewPointData.itemType is ignored, i.e. the type of the object to change is determined by viewPointData.guid.
 * 			viewPointData.viewSettingsFlags is ignored, if viewPointData.parentGuid designates a root or a group.
 * 			Note: In teamwork mode you cannot create, change or delete viewpoint roots or groups.
 */
__APIEXPORT GSErrCode ACAPI_Navigator_ChangeNavigatorVPItem (API_NavigatorAddOnViewPointData* viewPointData);


/**
 * @brief Gets information about an existing Navigator viewpoint root, group or leaf node in the Project Map.
 * @ingroup Navigator
 * @param viewPointData [in/out] The guid member should be provided before call. The result of the query will be filled in the other members on return.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - viewPointData was nullptr.
 * 			- APIERR_BADID - viewPointData.guid designetes an object which does not exist, or it is not a Navigator viewpoint root, group or leaf node of the current AddOn.
 * @remarks viewPointData.viewSettingsFlags is set to @c API_NavgatorViewSettingsNoAttributeID, if viewPointData.guid designates a root or a group.
 */
__APIEXPORT GSErrCode ACAPI_Navigator_GetNavigatorVPItem (API_NavigatorAddOnViewPointData* viewPointData);


/**
 * @brief Gets the list of Navigator viewpoint roots.
 * @ingroup Navigator
 * @param rootGuids [out] The GUIDs of the current AddOn's Navigator viewpoint roots.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - rootGuids was nullptr.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Navigator_GetNavigatorVPRootGroups-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Navigator_GetNavigatorVPRootGroups (GS::Array<API_Guid>* rootGuids);


/**
 * @brief Gets the list of child viewpoint groups/nodes of a Navigator viewpoint root or group.
 * @ingroup Navigator
 * @param guid [in] The GUID of the root/group of which the children are to be queried.
 * @param childrenGuids [out] The GUIDs of the children.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - guid was nullptr.
 * 			childrenGuids was nullptr.
 * 			- APIERR_BADID - guid does not designate an existing Navigator viewpoint root or group.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Navigator_GetNavigatorVPItemChildren-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Navigator_GetNavigatorVPItemChildren (const API_Guid* guid, GS::Array<API_Guid>* childrenGuids);


/**
 * @brief Registers an object with virtual functions that are implemented by the AddOn. These are called by Archicad when certain events happen relating to the navigator items that are registered by the AddOn.
 * @ingroup Navigator
 * @param callBackInterface [in] Pointer to the callback interface object to register.
 * @return
 * 			- NoError - The function has been completed with success.
 * 			- APIERR_BADPARS - callBackInterface was nullptr.
 * @remarks The object pointed to by callBackInterface must be derived from INavigatorCallbackInterface. Its lifetime must be managed by the AddOn.
 */
__APIEXPORT GSErrCode ACAPI_Navigator_RegisterCallbackInterface (INavigatorCallbackInterface* callBackInterface);


#endif	// ACAPINAVIGATOR_H
