// *****************************************************************************
//
//                     Platform DLL export/import directive
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MM
//
// SG compatible
//
// *****************************************************************************

#ifndef PLATFORMDLLEXPORT_HPP
#define PLATFORMDLLEXPORT_HPP

#pragma once


#if defined(_MSC_VER)
	#define PLATFORM_DLL_EXPORT	__declspec(dllexport)
	#define PLATFORM_DLL_IMPORT	__declspec(dllimport)
#else
	#define PLATFORM_DLL_EXPORT __attribute__((visibility("default")))
	#define PLATFORM_DLL_IMPORT
#endif


#endif	// PLATFORMDLLEXPORT_HPP
