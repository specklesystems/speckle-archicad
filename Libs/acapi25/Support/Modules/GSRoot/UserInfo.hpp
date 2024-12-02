// ****************************************************************************
//
// Module:			GSRoot/BasicEnvironment
// Namespace:		GS
// Contact person:	SzA
//
// ****************************************************************************


#ifndef GSUSERINFO
#define GSUSERINFO


// ------------------------------- Includes -----------------------------------

// from GSRoot
#include "Definitions.hpp"
#include "GSRootExport.hpp"
#include "Owner.hpp"


// --- Predeclarations	-------------------------------------------------------

namespace GS {
	class UniString;
}


// ------------------------------- Namespace -----------------------------------

namespace GS {

// Undefine Windows Macros, we want to use "GetComputerName" and "GetUserName"

#if defined (WINDOWS)
#if defined (GetComputerName)
#undef GetComputerName
#endif
#if defined (GetUserName)
#undef GetUserName
#endif
#endif


GS::UniString			GSROOT_DLL_EXPORT	GetComputerName ();
GS::UniString			GSROOT_DLL_EXPORT	GetUserName		();

// For identifying machines. See the implementation for platform-specific peculiarities and limitations
GS::Owner<GS::NChar[]>	GSROOT_DLL_EXPORT	GetMachineID	();

} // namespace GS

#endif //GSUSERINFO
