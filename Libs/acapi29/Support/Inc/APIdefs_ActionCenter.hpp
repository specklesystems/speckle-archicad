// *********************************************************************************************************************
// API definitions - Managing Action Center
//
// Module:			API
// Namespace:		-
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APIDEFS_ACTIONCENTER_HPP)
#define	APIDEFS_ACTIONCENTER_HPP

// --- Compiler settings -----------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif


// --- Type definitions	------------------------------------------------------------------------------------------------

/**
 * @brief Possible check method of Action Center.
 * @enum API_ActionCenterItemID
 * @since Archicad 25
 * @remarks This enum is used with the @ref ACAPI_Window_Check function.
 */
enum API_ActionCenterItemID {

/**
 * Check whether all hotlinks are up-to-date.
 * @var APIActionCenterItem_Hotlinks
 */
	APIActionCenterItem_Hotlinks = 0,

};

// ---------------------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif
