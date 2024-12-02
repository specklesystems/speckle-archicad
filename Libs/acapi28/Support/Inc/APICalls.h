// *****************************************************************************
// API addons - Calling conventions
//
// Module:			API
// Namespace:		-
// Contact person:	archicadapi@graphisoft.com
//
// [SG compatible]
// *********************************************************************************************************************


#if !defined (APICALLS_H)
#define	APICALLS_H

#include "PlatformDLLExport.hpp"


#if !defined (__APIEXPORT)
	#if defined (USE_API_DLL)
		#define	__APIEXPORT	PLATFORM_DLL_IMPORT
	#else
		#if defined (COMP_API_DLL)
			#define	__APIEXPORT PLATFORM_DLL_EXPORT
		#else
			#define	__APIEXPORT
		#endif
	#endif
#endif


#endif
