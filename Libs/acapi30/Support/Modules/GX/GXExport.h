/*==========================================================================**
**							GXExport.h							**
**																			**
**		DEFINITIONS FOR EXPORTATION FROM THE GX MODULE			**
**==========================================================================*/

#ifndef	GXEXPORT_H
#define	GXEXPORT_H

#pragma once

#include "PlatformDLLExport.hpp"

#if	defined	(GX_STATIC_COMPILE)
	#define GX_DLL_EXPORT
	#define	GX_CALL
#else
	#if defined (GX_DLL_COMPILE)
		#define GX_DLL_EXPORT	extern "C" PLATFORM_DLL_EXPORT
		#define GX_DLL_EXPORT_NOT_C	PLATFORM_DLL_EXPORT
	#else
		#define GX_DLL_EXPORT	extern "C" PLATFORM_DLL_IMPORT
		#define GX_DLL_EXPORT_NOT_C	PLATFORM_DLL_IMPORT
	#endif
	#if defined (WINDOWS)
		#define	GX_CALL				__stdcall
	#else
		#define	GX_CALL
	#endif
#endif

#endif
