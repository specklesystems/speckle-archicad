// *****************************************************************************
// Definitions for exportation from the Brep module
//
// Source Unit:		Brep
// Module:			Brep
// Namespace:		
// Contact person:	BeA
// *****************************************************************************

#ifndef	BREPEXPORT_HPP
#define	BREPEXPORT_HPP

#pragma once

#include "PlatformDLLExport.hpp"

#ifdef BREP_DLL_COMPILE
#define	BREP_DLL_EXPORT		PLATFORM_DLL_EXPORT
#else
#define BREP_DLL_EXPORT		PLATFORM_DLL_IMPORT
#endif

#endif // BREPEXPORT_HPP
