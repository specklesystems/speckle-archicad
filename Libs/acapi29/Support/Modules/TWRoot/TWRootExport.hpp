// *****************************************************************************
//
//                     Export definitions for TWRoot
//
// Module:			TWRoot
// Namespace:		TW
// Contact person:	MI
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_TWROOTEXPORT_HPP
#define GS_TWROOTEXPORT_HPP

#if defined (_MSC_VER) && !defined (WINDOWS)
#define	WINDOWS
#endif

// from GSRoot
#include "PlatformDLLExport.hpp"

#if defined (TWROOT_DLL_COMPILE)
#define TWROOT_DLL_EXPORT		PLATFORM_DLL_EXPORT
#else
#define TWROOT_DLL_EXPORT		PLATFORM_DLL_IMPORT
#endif

#endif
