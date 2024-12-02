
// *****************************************************************************
//
//	            Base declarations and definitions for the Network module
//
// Module: Network
// Namespace: Network
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined NETWORKBASE_HPP
#define NETWORKBASE_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "PlatformDLLExport.hpp"
#include "GSRoot.hpp"



// -------------------------------- Definitions --------------------------------

#if defined (NETWORK_DLL_COMPILE)
	#define NETWORK_DLL_EXPORT		PLATFORM_DLL_EXPORT
	#define NETWORK_DLL_EXPORT_RTTI	PLATFORM_DLL_EXPORT_RTTI
#elif defined (NETWORK_STATIC_COMPILE)
	#define NETWORK_DLL_EXPORT
	#define NETWORK_DLL_EXPORT_RTTI
#else
	#define NETWORK_DLL_EXPORT	PLATFORM_DLL_IMPORT
	#define NETWORK_DLL_EXPORT_RTTI	PLATFORM_DLL_EXPORT_RTTI
#endif


#define	NETWORKASSERT(assertion,errorCode)	if (!(assertion)) { DBBREAK(); return errorCode; }
#define	NETWORKASSERT0(assertion)			if (!(assertion)) { DBBREAK(); return; }


namespace Network {

DECLARE_EXCEPTION_CLASS  (NetworkException, GS::RootException, Error, NETWORK_DLL_EXPORT)

}	// namespace Network




#endif
