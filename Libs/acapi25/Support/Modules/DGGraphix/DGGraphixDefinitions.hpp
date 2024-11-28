// *********************************************************************************************************************
// File:			DGGraphixDefinitions.hpp
//
// Description:		Common constants of the GRAPHISOFT Tracker Module
//
// Project:			GRAPHISOFT DG Graphix Module (DGGraphix)
//
// Namespace:		NewDisplay
//
// Contact person:	NZ, DG
//
// SG compatible
// *********************************************************************************************************************

#ifndef	DGGRAPHIXDEFINITIONS_HPP
#define	DGGRAPHIXDEFINITIONS_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "PlatformDLLExport.hpp"
#include "Array.hpp"

// --- Module export defines -------------------------------------------------------------------------------------------

#if defined (DGGRAPHIX_DLL_COMPILE)
	#define DGGRAPHIX_DLL_EXPORT		PLATFORM_DLL_EXPORT
#else
	#define DGGRAPHIX_DLL_EXPORT		PLATFORM_DLL_IMPORT
#endif

#endif
