/*==========================================================================**
**								GSModelerPrivExp.h							**
**																			**
**			DEFINITIONS FOR EXPORTATION FROM THE GSMODELER MODULE			**
**==========================================================================*/

#ifndef	GSMODELERPRIVEXPORT_H
#define	GSMODELERPRIVEXPORT_H

#pragma once

#include "PlatformDLLExport.hpp"

#if	defined	(GSMODELER_NOT_DLL)
	#define GSMODELER_PRIVATE_EXPORT
#else
	#if defined (GSMODELER_DLL_COMPILE)
		#define GSMODELER_PRIVATE_EXPORT	PLATFORM_DLL_EXPORT
	#else
		#define GSMODELER_PRIVATE_EXPORT	PLATFORM_DLL_IMPORT
	#endif
#endif

#endif
