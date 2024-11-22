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


#if !defined (__ACENV_CALL)
	#if defined (macintosh)
		#define	__ACENV_CALL
	#endif
	#if defined (WINDOWS)
		#define	__ACENV_CALL	__cdecl
	#endif
#endif

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

#if !defined (__ACDLL_CALL)
	#if defined (WINDOWS) && defined (COMP_API_VBDLL)
		#undef	__ACENV_CALL
		#define	__ACENV_CALL	__stdcall
		#define	__ACDLL_CALL	__cdecl
	#else
		#define	__ACDLL_CALL	__ACENV_CALL
	#endif
#endif


#endif
