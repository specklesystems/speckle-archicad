// *****************************************************************************
//
// 							   AssertTestSupport
//
// Module:		   GSRoot
// NameSpace:      GS
// Contact person: SzoBe
//
// *****************************************************************************


#ifndef GS_ASSERTTESTSUPPORT_HPP
#define	GS_ASSERTTESTSUPPORT_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "GSAssert.hpp"

namespace GS {

// ============================ Support functions ==============================

template <class Function>
void	SkipAssert (Function&& function, const char* module = nullptr);

template <class Function>
bool	WasAssert (Function&& function, const char* module = nullptr);


template <class Function>
void	SkipModuleAssert (Function&& function);

template <class Function>
bool	WasModuleAssert (Function&& function);

// ------------------------------ Implementation -------------------------------

template <class Function>
void	SkipAssert (Function&& function, const char* module)
{
	const bool wasAssertEnabled = IsAssertEnabled (module);
	if (wasAssertEnabled)
		DisableAssert (module);

	function ();

	if (wasAssertEnabled)
		EnableAssert (module);
}


template <class Function>
bool	WasAssert (Function&& function, const char* module)
{
	const UInt32 before = GetAssertFailureCount (module);

	SkipAssert (function, module);

	const UInt32 after = GetAssertFailureCount (module);

	return before < after;
}


template <class Function>
void	SkipModuleAssert (Function&& function)
{
	SkipAssert (function, ModuleName);
}


template <class Function>
bool	WasModuleAssert (Function&& function)
{
	return WasAssert (function, ModuleName);
}

} // namespace GS

#endif // ASSERTTESTSUPPORT_HPP
