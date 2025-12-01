/*==========================================================================**
**							Model3DExport.h									**
**																			**
**		DEFINITIONS FOR EXPORTATION FROM THE MODEL3D MODULE					**
**==========================================================================*/

#ifndef	MODEL3DEXPORT_H
#define	MODEL3DEXPORT_H

#pragma once

#include "PlatformDLLExport.hpp"

#if	defined	(MODEL3D_NOT_DLL)
	#define MODEL3D_DLL_EXPORT
	#define	MODEL3D_CALL
#else
	#if defined (MODEL3D_DLL_COMPILE)
		#define MODEL3D_DLL_EXPORT						PLATFORM_DLL_EXPORT
		#define MODEL3D_CPP_DLL_EXPORT					PLATFORM_DLL_EXPORT
	#else
		#define MODEL3D_DLL_EXPORT						PLATFORM_DLL_IMPORT
		#define MODEL3D_CPP_DLL_EXPORT					PLATFORM_DLL_IMPORT
	#endif
	#if defined (_MSC_VER)
		#define	MODEL3D_CALL				__stdcall
	#else
		#define	MODEL3D_CALL
	#endif
#endif

#endif
