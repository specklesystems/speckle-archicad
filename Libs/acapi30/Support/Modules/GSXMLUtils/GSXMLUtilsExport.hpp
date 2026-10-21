// *********************************************************************************************************************
// File:			GSXMLExport.hpp
//
// Description:		XML DOM I/O related utility functions
//
// Project:			ARCHICAD, Plotmaker
//
// Namespace:		GSXMLUtils
//
// Contact person:	PA, CSF
//
// SG compatible
// *********************************************************************************************************************

#ifndef GSXMLUTILSEXPORT_HPP
#define GSXMLUTILSEXPORT_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "PlatformDLLExport.hpp"

// --- GSXMLUTILS_EXPORT -----------------------------------------------------------------------------------------------

#if defined (GSXMLUTILS_DLL_COMPILE)
	#define GSXMLUTILS_EXPORT	PLATFORM_DLL_EXPORT
#else
	#define GSXMLUTILS_EXPORT	PLATFORM_DLL_IMPORT
#endif

#endif
