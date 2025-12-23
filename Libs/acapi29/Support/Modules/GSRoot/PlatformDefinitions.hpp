// *****************************************************************************
//
// Contact person: MB, PR
//
// *****************************************************************************

#ifndef GS_PLATFORMDEFINITIONS_HPP
#define GS_PLATFORMDEFINITIONS_HPP


namespace GS {


// === PlatformSign ====================================================================================================


enum PlatformSign {
	Unknown_Platform_Sign	= 0,
	Mac_Platform_Sign		= 19789, // 'MM'
	Mactel_Platform_Sign	= 28013, // 'mm'
	Win_Platform_Sign		= 22359, // 'WW'
	Unx_Platform_Sign		= 21845  // 'UU'
};


// === Platform macros =================================================================================================


#if defined _WIN64

	#ifndef GS_WIN
		#define GS_WIN
	#endif

	#ifndef WINDOWS
		#define WINDOWS
	#endif

	constexpr PlatformSign Act_Platform_Sign = Win_Platform_Sign;

#elif defined __APPLE__

	#ifndef GS_MAC
		#define GS_MAC
	#endif

	#ifndef GS_POSIX
		#define GS_POSIX
	#endif

	#ifndef macintosh
		#define macintosh
	#endif

	constexpr PlatformSign Act_Platform_Sign = Mactel_Platform_Sign;

#elif defined __linux__

	#ifndef GS_LINUX
		#define GS_LINUX
	#endif

	#ifndef GS_POSIX
		#define GS_POSIX
	#endif

	constexpr PlatformSign Act_Platform_Sign = Unx_Platform_Sign;

#else

	#error "The platform is unknown."

#endif


// === Architecture macros =============================================================================================


#if defined _M_X64 || defined __x86_64__

	#define GS_X86_64

#elif defined _M_ARM64 || defined __arm64__

	#define GS_ARM64

#else

	#error "The architecture is unknown."

#endif


} // namespace GS


#endif /* GS_PLATFORMDEFINITIONS_HPP */
