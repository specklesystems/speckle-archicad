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

enum API_ActionCenterItemID {
	APIActionCenterItem_All,
	APIActionCenterItem_Hotlinks,
	APIActionCenterItem_Libraries,
	APIActionCenterItem_Drawings,
	APIActionCenterItem_Licenses
};

// ---------------------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif
