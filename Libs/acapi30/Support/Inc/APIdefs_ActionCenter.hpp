// *********************************************************************************************************************
// API definitions - Managing Action Center
//
// Module:			API
// Namespace:		-
// *********************************************************************************************************************

#if !defined (APIDEFS_ACTIONCENTER_HPP)
#define	APIDEFS_ACTIONCENTER_HPP

#pragma once


// --- Compiler settings -----------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif


// --- Type definitions	------------------------------------------------------------------------------------------------

/**
 * @brief Possible check method of the Action Center.
 * @ingroup Window
 * @remarks This enum is used with the @ref ACAPI_Window_Check function.
 */
enum API_ActionCenterItemID {

/**
 * Checks whether all hotlinks are up-to-date.
 */
	APIActionCenterItem_Hotlinks = 0

};

// ---------------------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif
