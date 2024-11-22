#ifndef __APIFUNCTIONSENVIRONMENT_HPP__
#define __APIFUNCTIONSENVIRONMENT_HPP__

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
	#define	ACExtension
#endif

#include <ACAPinc.h>

#endif //__APIFUNCTIONSENVIRONMENT_HPP__
