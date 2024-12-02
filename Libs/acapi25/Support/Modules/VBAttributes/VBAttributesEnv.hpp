// *****************************************************************************
// The compiler settings of the VBAttributes
//
// Namespaces:        Contact person:
//
// [SG compatible]
// *****************************************************************************

#if !defined (VBATTRIBUTESENV_HPP)
#define VBATTRIBUTESENV_HPP

#pragma once

#include "PlatformDLLExport.hpp"

#if defined (VBATTRIBUTES_DLL_COMPILE)
	#define VBATTRIBUTES_DLL_EXPORT	PLATFORM_DLL_EXPORT
#else
	#define VBATTRIBUTES_DLL_EXPORT	PLATFORM_DLL_IMPORT
#endif

#endif
