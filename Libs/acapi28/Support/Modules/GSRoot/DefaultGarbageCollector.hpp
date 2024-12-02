
// *****************************************************************************
//
//                    Default GarbageCollector implementation
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB, AZS
//
// SG compatible
//
// *****************************************************************************


#if !defined DEFAULTGARBAGECOLLECTOR_HPP
#define DEFAULTGARBAGECOLLECTOR_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "GSRootExport.hpp"
#include "GarbageCollector.hpp"



// =============================================================================

namespace GS {

GSROOT_DLL_EXPORT extern GarbageCollector&	defaultGarbageCollector;	// refers to the default garbage collector instance

}	// namespace GS

// _____________________________________________________________________________


#endif
