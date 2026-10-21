/*==========================================================================**
**						Model3DPrivExp.h									**
**																			**
**		DEFINITIONS FOR EXPORTATION FROM THE MODEL3D	MODULE				**
**==========================================================================*/

#ifndef	MODEL3DPRIVEXPORT_H
#define	MODEL3DPRIVEXPORT_H

#pragma once

#include "PlatformDLLExport.hpp"

#if	defined	(MODEL3D_NOT_DLL)
	#define MODEL3D_PRIVATE_EXPORT
	#define MOD3D_PRIV
#else
	#if defined (MODEL3D_DLL_COMPILE)
		#define MODEL3D_PRIVATE_EXPORT	PLATFORM_DLL_EXPORT
	#else
		#define MODEL3D_PRIVATE_EXPORT	PLATFORM_DLL_IMPORT
	#endif

	#define MOD3D_PRIV
#endif

#endif
