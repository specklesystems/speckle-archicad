// *********************************************************************************************************************
// File:			GraphixDefinitions.hpp
//
// Description:		Common defintions of the GRAPHISOFT Graphix Module
//
// Project:			GRAPHISOFT Graphix Module (DGGraphix)
//
// Namespace:		NewDisplay
//
// Contact person:	NZ, DG
//
// SG compatible
// *********************************************************************************************************************

#ifndef	GRAPHIXDEFINITIONS_HPP
#define	GRAPHIXDEFINITIONS_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "PlatformDLLExport.hpp"
#include "Array.hpp"

// --- Module export defines -------------------------------------------------------------------------------------------

#undef GRAPHIX_DLL_EXPORT

#if defined (GRAPHIX_DLL_COMPILE)
	#define GRAPHIX_DLL_EXPORT		PLATFORM_DLL_EXPORT
#else
	#define GRAPHIX_DLL_EXPORT		PLATFORM_DLL_IMPORT
#endif

#endif
