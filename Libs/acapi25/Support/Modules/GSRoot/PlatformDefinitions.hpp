#ifndef PLATFORM_DEFINITIONS_HPP
#define PLATFORM_DEFINITIONS_HPP

#pragma once


#if defined (_MSC_VER) && !defined (WINDOWS)
#define	WINDOWS
#endif

#if defined (__APPLE__) && !defined(macintosh)
#define macintosh
#endif

#if defined (__linux) && !defined(__linux__)
#define __linux__
#endif

#if defined (linux) && !defined(__linux__)
#define __linux__
#endif


#if defined (macintosh) || defined (__linux__)
	#if defined (__LP64__)
		#define GS_64BIT
	#else
		#define GS_32BIT
	#endif
#endif

#if defined (_MSC_VER)
	#if defined (_WIN64)
		#define GS_64BIT
	#else
		#define GS_32BIT
	#endif
#endif

#if defined (_WIN64) && !defined (WIN64)
	#define	WIN64
#endif


#if defined (_MSC_VER)
	#if defined _M_X64
		#define GS_X86_64
	#elif defined (_M_ARM)
		#define GS_ARM64
	#else 
		#error "Unknown cpu architecture"
	#endif
#elif defined (__clang__)
	#if defined __x86_64__
		#define GS_X86_64
	#elif defined (__arm64__)
		#define GS_ARM64
	#else 
		#error "Unknown cpu architecture"
	#endif
#else
	#error "Unknown compiler"
#endif


#if defined (_MSC_VER)
	#if _MSC_VER < 1920
		#error "VS2019 (v142 toolset) is required"
	#endif
#endif


namespace GS {

enum PlatformSign {
	Unknown_Platform_Sign	= 0,
	Mac_Platform_Sign		= 19789, //'MM',
	Mactel_Platform_Sign	= 28013, //'mm',
	Win_Platform_Sign		= 22359, //'WW',
	Unx_Platform_Sign		= 21845  //'UU'
};

#if defined (macintosh)
	#if defined(__BIG_ENDIAN__)
		const PlatformSign	Act_Platform_Sign	= Mac_Platform_Sign;
	#elif defined(__LITTLE_ENDIAN__)
		const PlatformSign	Act_Platform_Sign	= Mactel_Platform_Sign;
	#else
		#error "Undefined endianness"
	#endif
#elif defined (__linux__)
	const PlatformSign	Act_Platform_Sign	= Unx_Platform_Sign;
#elif defined (WINDOWS)
	const PlatformSign	Act_Platform_Sign	= Win_Platform_Sign;
#else
	#error	"Unknown platform."
#endif

}	// namespace GS

#endif
