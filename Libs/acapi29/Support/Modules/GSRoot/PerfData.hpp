// *********************************************************************************************************************
// Description:		Get memory and process specific data from the operating system
//
// Module:			GSRoot
// Namespace:		PerfData
// Contact person:	MM
//
// SG compatible
// *********************************************************************************************************************

#if !defined (PERFDATA_HPP)
#define PERFDATA_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include 	"GSRootExport.hpp"
#include 	"Definitions.hpp"


// --- Function declarations -------------------------------------------------------------------------------------------

namespace PerfData {
	GSROOT_DLL_EXPORT GS::UInt64	MaxVirtualBytes (void);
	GSROOT_DLL_EXPORT GS::UInt64	RAMBytes (void);

	GSROOT_DLL_EXPORT GS::UIntPtr	PrivateBytes (void);
	GSROOT_DLL_EXPORT bool			GetPeakBytes (GS::UIntPtr*	pPeakPageFileBytes,
												  GS::UIntPtr*	pPeakWorkingSet);

	GSROOT_DLL_EXPORT double		FragmentationIndex (size_t* allocated, size_t* maxFree);
}

#endif
