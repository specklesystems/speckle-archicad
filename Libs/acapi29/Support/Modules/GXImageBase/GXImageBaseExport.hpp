// *********************************************************************************************************************
// File:			GXImageBaseExport.hpp
//
// Description:		Common constants of the GRAPHISOFT Tracker Module
//
// Project:			GRAPHISOFT GX ImageBase Module
//
// Namespace:		NewDisplay (?)
//
// Contact person:	EA
//
// SG compatible
// *********************************************************************************************************************

#ifndef	GXIMAGEBASEEXPORT_HPP
#define	GXIMAGEBASEEXPORT_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "PlatformDLLExport.hpp"

// --- Module export defines -------------------------------------------------------------------------------------------

#if defined (GXIMAGEBASE_DLL_COMPILE)
	#define GXIMAGEBASE_DLL_EXPORT		PLATFORM_DLL_EXPORT
#else
	#define GXIMAGEBASE_DLL_EXPORT		PLATFORM_DLL_IMPORT
#endif

#endif
