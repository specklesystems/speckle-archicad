// *********************************************************************************************************************
// File:			TransparentWindowLibDefinitions.hpp
//
// Description:		Common constants of the GRAPHISOFT Tracker Module
//
// Project:			GRAPHISOFT Tracker Module (TransparentWindowLib)
//
// Namespace:		Tracking
//
// Contact person:	NZ, SD
//
// SG compatible
// *********************************************************************************************************************

#ifndef	TRANSPARENTWINDOWLIBDEFINITIONS_HPP
#define	TRANSPARENTWINDOWLIBDEFINITIONS_HPP
#pragma once

// --- Includes --------------------------------------------------------------------------------------------------------

#include "PlatformDLLExport.hpp"


// --- Module export defines -------------------------------------------------------------------------------------------

#if defined (TRANSPARENTWINDOWLIB_DLL_COMPILE)
	#define TRANSPARENTWINDOWLIB_DLL_EXPORT		PLATFORM_DLL_EXPORT
#else
	#define TRANSPARENTWINDOWLIB_DLL_EXPORT		PLATFORM_DLL_IMPORT
#endif

#endif
