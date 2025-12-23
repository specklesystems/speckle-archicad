// *****************************************************************************
//
//	    Export-import declarations and definitions for the QGDrawing module
//
// Module: QGDrawing
// Namespace: TE
// Contact person: DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined QGBASE_HPP
#define QGBASE_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "PlatformDLLExport.hpp"

// -------------------------------- Definitions --------------------------------

#if defined (QGDRAWING_DLL_COMPILE)
	#define QG_DLL_EXPORT	PLATFORM_DLL_EXPORT
#else
	#define QG_DLL_EXPORT	PLATFORM_DLL_IMPORT
#endif

#endif // QGBASE_HPP
