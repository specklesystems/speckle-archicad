// *****************************************************************************
//
//                     Export definitions for RS module
//
// Module:			RS
// Namespace:		RS
// Contact person:	SzaM
//
// SG compatible
//
// *****************************************************************************

#ifndef RSEXPORT_HPP
#define RSEXPORT_HPP

#pragma once

// from GSRoot
#include "PlatformDLLExport.hpp"

#if defined (RS_DLL_COMPILE)
#define RS_DLL_EXPORT		PLATFORM_DLL_EXPORT
#elif defined (RS_STATIC_COMPILE)
#define RS_DLL_EXPORT
#else
#define RS_DLL_EXPORT		PLATFORM_DLL_IMPORT
#endif

#endif
