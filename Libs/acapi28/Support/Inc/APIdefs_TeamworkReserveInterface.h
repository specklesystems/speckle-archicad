// *********************************************************************************************************************
// API definitions for Teamwork Control ReserveInterface functionality
//
// Module:			API
// Namespace:		-
// Contact person:
// *********************************************************************************************************************

#if !defined (APIDEFS_TEAMWORKRESERVEINTERFACE_H)
#define APIDEFS_TEAMWORKRESERVEINTERFACE_H

#if defined (_MSC_VER)
#pragma once
#endif


// --- Includes --------------------------------------------------------------------------------------------------------

#if defined (WINDOWS)
#include "Win32Interface.hpp"
#endif

// GSRoot
#include "GSRoot.hpp"

// own
#include "APICalls.h"
#include "API_Guid.hpp"
#include "APIdefs_Environment.h"


// --- Compiler settings -----------------------------------------------------------------------------------------------

typedef enum {
	APIReservationInterfaceStatus_Undefined,
	APIReservationInterfaceStatus_Free,
	APIReservationInterfaceStatus_Editable,
	APIReservationInterfaceStatus_Reserved,
	APIReservationInterfaceStatus_NotAvailable,
	APIReservationInterfaceStatus_EditableAfterReceive
} API_ReservationInterfaceStatus;

typedef GSErrCode APIReservationTeamWorkPanelParentUIRefreshNeededProc (short dialId, API_ReservationInterfaceStatus reservationStatus);
typedef GSErrCode APIReservationTeamWorkPanelParentDataSaveNeededProc  (short dialId, API_ReservationInterfaceStatus reservationStatus);

#if defined (ACExtension)

/**
 * @brief Registers an interface supporting reserve/release in teamwork operations.
 * @ingroup Teamwork
 * @ingroup Dialog
 * @param objectId [in] The unique identifier of this interface.
 * @param dialogId [in] The dialog ID you register the interface for.
 * @param tabId [in] The tab page ID you register the interface for.
 * @param tabResId [in] The resource describing the tab page interface elements.
 * @param resModule [in] The resource module identifier that identifies the module containing the tab page
 * 					interface elements.
 * @param dialogIconResModule [in] The resource module identifier that identifies the module containing the
 * 							  tab page icons.
 * @param teamworkPanelParentUIRefreshNeeded [in] The callback function which is called when you have to
 * 											 refresh the items on the registered interface.
 * @param teamworkPanelParentDataSaveNeeded [in] The callback function which is called before your panel
 * 											is closed. You can use this function to set an internal state in your add-on which you can use later to
 * 											perform teamwork-related operations (e.g., reserve or release AddOnObjects).
 * @param requestMessage [in] The request message.
 * @param createRight [in] The teamwork create right you assign to this interface.
 * @param deleteModifyRight [in] The teamwork delete and modify right you assign to this interface.
 * @return
 * 			- NoError - The function completed with success.
 * 			- APIERR_BADPARS - `objectId` is `APINULLGuid` or `dialogId` is 0 or `tabId` is 0.
 * 			- APIERR_NOPLAN - No project is open.
 * 			- APIERR_NOTEAMWORKPROJECT - The open project is not a teamwork project.
 * 			- APIERR_BADID - `objectId` is `APINULLGuid`.
 */
__APIEXPORT GSErrCode ACAPI_RegisterTeamworkReserveInterface (
												const API_Guid&											objectId,
												short													dialogId,
												short													tabId,
												short													tabResId,
												GSResModule												resModule,
												GSResModule												dialogIconResModule,
												APIReservationTeamWorkPanelParentUIRefreshNeededProc*	teamworkPanelParentUIRefreshNeeded,
												APIReservationTeamWorkPanelParentDataSaveNeededProc*	teamworkPanelParentDataSaveNeeded,
												const GS::UniString&									requestMessage,
												API_TWAccessRights										createRight = APINoPermission,
												API_TWAccessRights										deleteModifyRight = APINoPermission);


/**
 * @brief Unregisters a previously registered interface.
 * @ingroup Teamwork
 * @ingroup Dialog
 * @param objectId [in] The unique identifier of this interface (that you passed during registration).
 * @param dialogId [out] The dialog ID you registered the interface for.
 * @return
 * 			- NoError - The function completed with success.
 * 			- APIERR_BADID - `objectId` is not registered.
 */
__APIEXPORT GSErrCode ACAPI_UnregisterTeamworkReserveInterface (const API_Guid& objectId,
																			 short			 dialogId = 0);


/**
 * @brief Refreshes the registered teamwork interface.
 * @ingroup Teamwork
 * @ingroup Dialog
 * @param objectId [in] The unique identifier of this interface (that you passed during registration).
 * @param dialogId [in] The dialog ID you registered the interface for.
 * @param isTeamWorkPanelParentUIRefreshNeeded [in] Update the parent UI as well?
 * @return
 * 			- NoError - The function completed with success.
 */
__APIEXPORT GSErrCode ACAPI_RefreshTeamworkReserveInterface (const API_Guid&	objectId,
																			   short			dialogId,
																			   bool				isTeamWorkPanelParentUIRefreshNeeded = false);


/**
 * @brief Sends the release comment mail.
 * @ingroup Teamwork
 * @ingroup Dialog
 * @param objectId [in] The unique identifier of this interface (that you passed during registration).
 * @param dialogId [in] The dialog ID you registered the interface for.
 * @return
 * 			- NoError - The function completed with success.
 */
__APIEXPORT GSErrCode ACAPI_Teamwork_SendReleaseCommentMail (const API_Guid& objectId, short dialogId);

#endif


// ---------------------------------------------------------------------------------------------------------------------

#endif
