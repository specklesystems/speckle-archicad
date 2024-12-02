// *********************************************************************************************************************
// API definitions - managing own data section in the project file
//
// Module:			API
// Namespace:		-
// Contact person:	archicadapi@graphisoft.com
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APIDEFS_MODULDATA_H)
#define	APIDEFS_MODULDATA_H

#if defined (_MSC_VER)
#pragma once
#endif


// --- Includes	--------------------------------------------------------------------------------------------------------

// own
#include "APIdefs_Base.h"


// --- Compiler settings -----------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------


// =============================================================================
// Command codes
//
// =============================================================================

/**
 * @brief ModulData operation code.
 * @enum API_MDSetCmd
 * @ingroup ModulData
 * @remarks This value is passed as a parameter to the APIModulDataMergeHandlerProc callback function.
 * 			When the ModulData Manager notifies your add-on, this code tells you the type of operation your add-on is called for.
 * 			The @c APIMDSetMerge_Merge code means that the notification is posted because of the database must be updated; invoked by the Merge or Copy commands.
 * 			The APIMDSetMerge_HLM and APIMDSetMerge_TW means the notification is posted because of the databases must be merged; invoked by Teamwork (Send Changes, Receive Changes), or Place Hotlink Module commands, respectively.
 */
enum API_MDSetCmd {
	APIMDSetMerge_TW				= 11,
	APIMDSetMerge_HLM				= 12,
	APIMDSetMerge_Merge				= 13
};


// =============================================================================
// Data info
//
// =============================================================================

/**
 * @brief Control information of a custom data section saved into the project file.
 * @struct API_ModulData
 * @ingroup ModulData
 * @remarks This structure is used by the ModulData Manager functions, for further details refer to these sections.
 */
struct API_ModulData {

/**
 * @brief Data version; use this for backward compatibility.
 * @var dataVersion
 */
	Int32							dataVersion;

/**
 * @brief Byte ordering in data storage (can be either GS::Win_Platform_Sign, GS::Mac_Platform_Sign or GS::Mactel_Platform_Sign
 * @var platformSign
 */
	unsigned short					platformSign;
	short							filler_1;

/**
 * @brief User specified data (cannot be nullptr).
 * @var dataHdl
 */
	GSHandle						dataHdl;
	Int32							filler_2 [11];

};


// ---------------------------------------------------------------------------------------------------------------------

#endif
