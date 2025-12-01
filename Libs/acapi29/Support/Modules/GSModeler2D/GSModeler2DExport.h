/*==========================================================================**
**							GSModeler2DExport.h								**
**																			**
**		DEFINITIONS FOR EXPORTATION FROM THE GSMODELER2D MODULE				**
**==========================================================================*/

#ifndef	GSMODELER2DEXPORT_H
#define	GSMODELER2DEXPORT_H

#pragma once

#include "PlatformDLLExport.hpp"

#if	defined	(GSMODELER2D_NOT_DLL)
	#define GSMODELER2D_PRIVATE_EXPORT
	#define GSMODELER2D_DLL_EXPORT
	#define	GSM2D_CALL
#else
	#if defined (GSMODELER2D_DLL_COMPILE)
		#define GSMODELER2D_PRIVATE_EXPORT		extern "C" PLATFORM_DLL_EXPORT
		#define GSMODELER2D_DLL_EXPORT			PLATFORM_DLL_EXPORT
		#define GSMODELER2D_DLL_CLASS_EXPORT	PLATFORM_DLL_EXPORT
	#else
		#define GSMODELER2D_PRIVATE_EXPORT		extern "C" PLATFORM_DLL_IMPORT
		#define GSMODELER2D_DLL_EXPORT			PLATFORM_DLL_IMPORT
		#define GSMODELER2D_DLL_CLASS_EXPORT	PLATFORM_DLL_IMPORT
	#endif
	#if defined (_MSC_VER)
		#define	GSM2D_CALL						__stdcall
	#else
		#define	GSM2D_CALL
	#endif
#endif

#endif
