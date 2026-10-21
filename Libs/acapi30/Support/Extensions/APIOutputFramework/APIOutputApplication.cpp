// includes and defines needed by API functions
#ifdef _WIN32
	#include <Win32Interface.hpp>
	#ifndef WINDOWS
		#define WINDOWS
	#endif
#endif

#ifdef macintosh
	#include <CoreServices/CoreServices.h>
#endif

#ifndef ACExtension
	#define ACExtension
#endif

#include "ACAPinc.h"

#include "APIOutputApplication.hpp"


GSAPI::APIOutputApplication::~APIOutputApplication ()
{
}
