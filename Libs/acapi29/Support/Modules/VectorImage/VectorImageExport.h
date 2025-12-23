/*==========================================================================**
**							VectorImageExport.h								**
**																			**
**		DEFINITIONS FOR EXPORTATION FROM THE VECTORIMAGE MODULE				**
**==========================================================================*/

#ifndef	VECTORIMAGEEXPORT_H
#define	VECTORIMAGEEXPORT_H


#pragma once

#include "PlatformDLLExport.hpp"

enum GradientFillType {
	Other_Fill		= 0,
	Linear_Fill		= 1,
	Radial_Fill		= 2
};


#if	defined	(VI_NOT_DLL)
	#define VI_DLL_EXPORT
	#define	VI_CALL
#else
	#if defined (VI_DLL_COMPILE)
		#define VI_DLL_EXPORT				PLATFORM_DLL_EXPORT
		#define VI_DLL_CLASS_EXPORT			PLATFORM_DLL_EXPORT
	#else
		#define VI_DLL_EXPORT				PLATFORM_DLL_IMPORT
		#define VI_DLL_CLASS_EXPORT			PLATFORM_DLL_IMPORT
	#endif
	#if defined (_MSC_VER)
		#define	VI_CALL				__stdcall
	#else
		#define	VI_CALL
	#endif
#endif

#endif
