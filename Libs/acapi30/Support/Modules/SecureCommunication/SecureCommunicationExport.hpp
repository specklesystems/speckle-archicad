
// *****************************************************************************
//
// Import/export macro declarations for Secure Communication module
//
// Module:			SecureCommunication
// Namespace:		SecureCommunication
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef SECURECOMMUNICATION_EXPORT_HPP
#define SECURECOMMUNICATION_EXPORT_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "PlatformDLLExport.hpp"


#if defined (SECURECOMMUNICATION_EXPORTS)
#define	SECURECOMMUNICATION_API		PLATFORM_DLL_EXPORT
#else
#define SECURECOMMUNICATION_API		PLATFORM_DLL_IMPORT
#endif


#endif
