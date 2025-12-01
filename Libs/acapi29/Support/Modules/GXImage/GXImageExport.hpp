// *********************************************************************************************************************
// File:			GXImageExport.hpp
//
// Description:		Common constants of the GRAPHISOFT Tracker Module
//
// Project:			GRAPHISOFT GX Image Module
//
// Namespace:		NewDisplay (?)
//
// Contact person:	EA
//
// SG compatible
// *********************************************************************************************************************

#ifndef	GXIMAGEEXPORT_HPP
#define	GXIMAGEEXPORT_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "PlatformDLLExport.hpp"

// --- Module export defines -------------------------------------------------------------------------------------------

#if defined (GXIMAGE_DLL_COMPILE)
	#define GXIMAGE_DLL_EXPORT		PLATFORM_DLL_EXPORT
#else
	#define GXIMAGE_DLL_EXPORT		PLATFORM_DLL_IMPORT
#endif

#endif
