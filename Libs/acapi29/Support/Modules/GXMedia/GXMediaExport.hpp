// *********************************************************************************************************************
// File:			GXMediaExport.hpp
//
// Description:		Common constants of the GRAPHISOFT GXMedia Module
//
// Project:			GRAPHISOFT GX Media Module
//
// Namespace:		GX
//
// Contact person:	DG
//
// SG compatible
// *********************************************************************************************************************

#ifndef	GXMEDIAEXPORT_HPP
#define	GXMEDIAEXPORT_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "PlatformDLLExport.hpp"

// --- Module export defines -------------------------------------------------------------------------------------------

#if defined (GXMEDIA_DLL_COMPILE)
	#define GXMEDIA_DLL_EXPORT		PLATFORM_DLL_EXPORT
#else
	#define GXMEDIA_DLL_EXPORT		PLATFORM_DLL_IMPORT
#endif

#endif
