// *****************************************************************************
//
//                     Export definitions for GSRoot module
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MM
//
// SG compatible
//
// *****************************************************************************

#ifndef GSROOTEXPORT_HPP
#define GSROOTEXPORT_HPP

#pragma once

#if defined (_MSC_VER) && !defined (WINDOWS)
#define	WINDOWS
#endif

// from GSRoot
#include "PlatformDLLExport.hpp"

#if defined (GSROOT_DLL_COMPILE)
#define GSROOT_DLL_EXPORT		PLATFORM_DLL_EXPORT
#elif defined (GSROOT_STATIC_COMPILE)
#define GSROOT_DLL_EXPORT
#else
#define GSROOT_DLL_EXPORT		PLATFORM_DLL_IMPORT
#endif

#endif
