
// *****************************************************************************
//
//	            Base declarations and definitions for the TextEngine module
//
// Module: TextEngine
// Namespace: TE
// Contact person: DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined TEBASE_HPP
#define TEBASE_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "PlatformDLLExport.hpp"

// -------------------------------- Definitions --------------------------------

#if defined (TEXTENGINE_DLL_COMPILE)
	#define TE_DLL_EXPORT	PLATFORM_DLL_EXPORT
#else
	#define TE_DLL_EXPORT	PLATFORM_DLL_IMPORT
#endif



#endif
