// *********************************************************************************************************************
//
// Module:			GSRoot
// Contact person:	MM
//
// *********************************************************************************************************************

#ifndef INTELSTACKWALKWIN_HPP
#define INTELSTACKWALKWIN_HPP

#pragma once

#include "Definitions.hpp"
#include "GSRootExport.hpp"

namespace GS {

enum WalkTypeSelector {
	Absolute,
	Relative
};

GSROOT_DLL_EXPORT	UInt16	 IntelStackWalk (void* pStartContext, Int32 ignoreDepth, UInt16 depth, void* pData, WalkTypeSelector selector = Absolute);

}	// namespace GS


#endif // INTELSTACKWALKWIN_HPP
