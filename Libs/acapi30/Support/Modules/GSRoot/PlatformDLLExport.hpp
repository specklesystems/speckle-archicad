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


#if defined(_MSC_VER)
	#define PLATFORM_DLL_EXPORT __declspec(dllexport)
	#define PLATFORM_DLL_IMPORT __declspec(dllimport)
#else
	#define PLATFORM_DLL_EXPORT __attribute__((visibility("default")))
	#define PLATFORM_DLL_IMPORT __attribute__((visibility("default")))
#endif


// When we are compiling with -fvisibility=hidden, the typeinfo symbols will also be hidden by default.
// This prevents dynamic_cast and typeid from working correctly with e.g. template types and enums.
// Use this macro for types where PLATFORM_DLL_EXPORT is not suitable.
#ifdef __clang__
	#define GS_EXPORT_TYPEINFO [[clang::type_visibility("default")]]
#else
	#define GS_EXPORT_TYPEINFO
#endif


#endif	// PLATFORMDLLEXPORT_HPP
