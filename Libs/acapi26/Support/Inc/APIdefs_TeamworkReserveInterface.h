// *********************************************************************************************************************
// API definitions for Teamwork Control ReserveInterface functionality
//
// Module:			API
// Namespace:		-
// Contact person:
//
// [SG compatible]
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

typedef GSErrCode	__ACENV_CALL	APIReservationTeamWorkPanelParentUIRefreshNeededProc (short dialId, API_ReservationInterfaceStatus reservationStatus);
typedef GSErrCode	__ACENV_CALL	APIReservationTeamWorkPanelParentDataSaveNeededProc  (short dialId, API_ReservationInterfaceStatus reservationStatus);

#if defined (ACExtension) && !defined (COMP_API_DLL)

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_RegisterTeamworkReserveInterface (
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

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_UnregisterTeamworkReserveInterface (const API_Guid& objectId, short dialogId = 0);
__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_RefreshTeamworkReserveInterface (const API_Guid& objectId, short dialogId, bool isTeamWorkPanelParentUIRefreshNeeded = false);
__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_TeamworkReserveInterface_SendReleaseCommentMail (const API_Guid& objectId, short dialogId);

#endif


// ---------------------------------------------------------------------------------------------------------------------

#endif
