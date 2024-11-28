
// *****************************************************************************
//
//	            Base declarations and definitions for the IO module
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined IOBASE_HPP
#define IOBASE_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "PlatformDLLExport.hpp"
#include "GSRoot.hpp"



// -------------------------------- Definitions --------------------------------

#if defined (INPUTOUTPUT_DLL_COMPILE)
	#define IO_DLL_EXPORT		PLATFORM_DLL_EXPORT
#elif defined (INPUTOUTPUT_STATIC_COMPILE)
	#define IO_DLL_EXPORT
#else
	#define IO_DLL_EXPORT	PLATFORM_DLL_IMPORT
#endif


#define	IOASSERT(assertion,errorCode)	if (!(assertion)) { DBBREAK(); return errorCode; }
#define	IOASSERT0(assertion)			if (!(assertion)) { DBBREAK(); return; }


namespace IO {

const Int32 ModuleId = 257;

const Int32 ErrorStart = GS::ErrorFlagMask | (ModuleId << 16);

	// Error code ranges for IO system - defined here to make the range allocation easier

const Int32 LocationErrors		  = ErrorStart + 0x0000;
const Int32 FileErrors			  = ErrorStart + 0x0100;
const Int32 FolderErrors		  = ErrorStart + 0x0200;
const Int32 FileSystemErrors	  = ErrorStart + 0x0300;
const Int32 TreeEnumeratorErrors  = ErrorStart + 0x0400;
const Int32 RelativeLocationErrors = ErrorStart + 0x0500;
const Int32 TypeErrors			  = ErrorStart + 0x0600;
const Int32 URLErrors			  = ErrorStart + 0x0700;
const Int32 ZipErrors			  = ErrorStart + 0x0800;
const Int32 CodeChannelErrors	  = ErrorStart + 0x0900;

	// Base types

enum AccessDeniedTreatment {
	AccessDeniedIsAllowed,					// do not retry
	AccessDeniedIsError,					// retry some times
	AccessDeniedIsErrorInPrivateLocations	// default; retry, if the file is in a previously declared folder
};

	// Base functions

inline GS::PlatformSign		GetCurrentPlatform (void)
{
	return GS::Act_Platform_Sign;
}


DECLARE_EXCEPTION_CLASS  (IOException, GS::RootException, Error, IO_DLL_EXPORT)


}	// namespace IO



#endif
