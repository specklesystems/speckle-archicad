// *****************************************************************************
//
//                      Base definitions, types and constants
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB, MM
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_DEFINITIONS_HPP
#define GS_DEFINITIONS_HPP

#include <cstring>
#include <initializer_list>
#include <utility>				// std::move, std::forward
#include <new>					// placement new, std::nothrow
#include "GSRootExport.hpp"



// === Platform-dependent definitions ==================================================================================


#if defined _WIN64

	#ifndef GS_WIN
		#define GS_WIN
	#endif

#elif defined __APPLE__

	#ifndef GS_MAC
		#define GS_MAC
	#endif

	#ifndef GS_POSIX
		#define GS_POSIX
	#endif

#elif defined __linux__

	#ifndef GS_LINUX
		#define GS_LINUX
	#endif

	#ifndef GS_POSIX
		#define GS_POSIX
	#endif

#else

	#error "The platform is unknown."

#endif


namespace GS {

// ------------------------------ GSRoot #defines ------------------------------

#if defined (_MSC_VER)
	#define GS_FORCE_INLINE		__forceinline
#else
	#define GS_FORCE_INLINE		__attribute__ ((always_inline)) inline
#endif


#if defined (_MSC_VER)
	#define GS_NO_INLINE	__declspec(noinline)
#else
	#define GS_NO_INLINE	__attribute__ ((noinline))
#endif


#if defined (__GNUC__)
	#define GCC_UNUSED		__attribute__ ((unused))
#else
	#define GCC_UNUSED
#endif


#ifdef _MSC_VER
#define UNUSED_FUNCTION    __pragma (warning (suppress: 4505))
#else
#define UNUSED_FUNCTION    __attribute__ ((unused))
#endif


#ifdef FINAL_VERSION
	#define UNUSED_FUNCTION_FINAL    UNUSED_FUNCTION
#else
	#define UNUSED_FUNCTION_FINAL
#endif


namespace Imp {

template <class... Ts>
GS_FORCE_INLINE constexpr void SinkUnusedVariables (const Ts&...)
{
}

}   // namespace Imp

#if defined _MSC_VER
	#define UNUSED_VARIABLE(...)	(__VA_ARGS__)
	#define UNUSED_PARAMETER(...)	(__VA_ARGS__)
#else
	#define UNUSED_VARIABLE(...)	GS::Imp::SinkUnusedVariables (__VA_ARGS__)
	#define UNUSED_PARAMETER(...)	GS::Imp::SinkUnusedVariables (__VA_ARGS__)
#endif


#ifdef CHECKED_VERSION
	#define GS_DEBUG_ONLY(text) text
	#define GS_DEBUG_HIDE(text)
#else
	#define GS_DEBUG_ONLY(text)
	#define GS_DEBUG_HIDE(text) text
#endif


#if defined (__clang__)
#define CLANG_WEAK_VTABLE_OFF	_Pragma ("clang diagnostic push") \
								_Pragma ("clang diagnostic ignored \"-Wweak-vtables\"")
#define CLANG_WEAK_VTABLE_ON	_Pragma ("clang diagnostic pop")
#else
#define CLANG_WEAK_VTABLE_OFF
#define CLANG_WEAK_VTABLE_ON
#endif


#ifdef _MSC_VER
	#define GS_UNHANDLED_ENUM_VALUE_CHECK_ON	__pragma (warning (error: 4061 4062))
	#define GS_UNHANDLED_ENUM_VALUE_CHECK_OFF	__pragma (warning (disable: 4061 4062))
#else
	#define GS_UNHANDLED_ENUM_VALUE_CHECK_ON	_Pragma ("clang diagnostic error \"-Wswitch-enum\"")
	#define GS_UNHANDLED_ENUM_VALUE_CHECK_OFF	_Pragma ("clang diagnostic ignored \"-Wswitch-enum\"")
#endif


#ifdef _MSC_VER
	/* TODO cl.exe 19.36 /analyze => C26815, C26816 */
	#define gs_lifebound /*[[msvc::lifetimebound]]*/
#else
	#define gs_lifebound [[clang::lifetimebound]]
#endif


#define mtaccess volatile
#define sync_cast const_cast

template <class T>
GS_FORCE_INLINE T*	Sync (volatile T* ptr)
{
	return sync_cast<T*> (ptr);
}

template <class T>
GS_FORCE_INLINE const T*	Sync (const volatile T* ptr)
{
	return sync_cast<T*> (ptr);
}

template <class T>
GS_FORCE_INLINE T&	Sync (volatile T& ptr)
{
	return sync_cast<T&> (ptr);
}

template <class T>
GS_FORCE_INLINE const T&	Sync (const volatile T& ptr)
{
	return sync_cast<T&> (ptr);
}


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


#if !defined (__INTELLISENSE__) && defined (_MSC_VER)
	#if _MSC_VER < 1920 || _MSC_VER >= 1930
		#error "VC++ 2019 v142 toolset is required. You can install it from a Visual Studio 2019 or later installer, or from a Build Tools for Visual Studio 2019 or later installer."
	#endif
#endif

// ---------------------------- Calling conventions ----------------------------

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

#ifndef	STDCALL
	#if defined (macintosh) || defined (__linux__)
		#define	STDCALL
	#else
		#define	STDCALL	__stdcall
	#endif
#endif

#ifndef	CCALL
	#if defined (macintosh) || defined (__linux__)
		#define	CCALL
	#else
		#define	CCALL	__cdecl
	#endif
#endif


#ifndef	CmpResult
	#define	CmpResult	int CCALL
	typedef	CmpResult	CmpFunction (const void*, const void*);
#endif


// ----------------------------- Compiler warnings -----------------------------

#if defined (_MSC_VER)
#pragma warning (disable: 4251)		// non dll-interface class used as member
#pragma warning (disable: 4275)		// non dll-interface class used as base
#pragma warning (disable: 4355)		// 'this' used in base member initializer list
#pragma warning (disable: 4250)		// class inherits method via dominance
#pragma warning (disable: 4458)		// declaration of XY hides class member
#pragma warning (disable: 4456)		// declaration of XY hides previous local declaration
#pragma warning (disable: 4838)		// conversion from X to Y requires a narrowing conversion
#pragma warning (disable: 4459)		// declaration of XY hides global declaration
#pragma warning (disable: 4302)		// 'type cast': truncation from X to Y
#pragma warning (disable: 4595)		// 'operator X': non-member operator new or delete functions may not be declared inline, SEE TT 210105

#endif

// ------------------------------- Macro helpers -------------------------------

#define GS_EXPAND_MACRO_AND_CONCATENATE_IMPL(param1, param2) param1 ## param2
#define GS_EXPAND_MACRO_AND_CONCATENATE(param1, param2) GS_EXPAND_MACRO_AND_CONCATENATE_IMPL (param1, param2)
#define GS_EXPAND_AND_STRINGIFY_IMPL(param) #param
#define GS_EXPAND_AND_STRINGIFY(param) GS_EXPAND_AND_STRINGIFY_IMPL(param)

// -------------------------------- GS Bad Pointer Value -----------------------

static void* const BadPointer = reinterpret_cast<void*> (0xFFFFBADC0DEFFFFF);

// -------------------------- Fixed sized Integral types -----------------------

typedef	char						Int8;
typedef unsigned char				UInt8;

typedef	short						Int16;
typedef unsigned short				UInt16;

typedef int							Int32;
typedef unsigned int				UInt32;

typedef long long					Int64;
typedef unsigned long long			UInt64;

typedef	Int32						NumChars;

static constexpr Int8               MaxInt8     = 127;
static constexpr UInt8              MaxUInt8    = 255;
static constexpr Int16              MaxInt16    = 32767;
static constexpr UInt16             MaxUInt16   = 65535;
static constexpr Int32              MaxInt32    = 2147483647;
static constexpr UInt32             MaxUInt32   = 4294967295;
static constexpr Int64              MaxInt64    = 9223372036854775807ULL;
static constexpr UInt64             MaxUInt64   = 18446744073709551615ULL;
static constexpr float				MaxFloat	= 3.402823466e+38F;
static constexpr double				MaxDouble	= 1.7976931348623158e+308;

static constexpr Int8               MinInt8		= -128;
static constexpr Int16              MinInt16	= -32768;
static constexpr Int32              MinInt32	= -2147483648LL;
static constexpr Int64              MinInt64	= -9223372036854775807LL - 1; // 9223372036854775808LL does not fit in Int64 so negation fails
static constexpr float				MinFloat	= -MaxFloat;
static constexpr double				MinDouble	= -MaxDouble;

static constexpr UInt16 KByte = 1024;
static constexpr UInt32 MByte = 1024 * 1024;
static constexpr UInt64 GByte = 1024ull * 1024ull * 1024ull;

inline constexpr UInt64 operator"" _KByte (UInt64 value) { return value * KByte; }
inline constexpr UInt64 operator"" _MByte (UInt64 value) { return value * MByte; }
inline constexpr UInt64 operator"" _GByte (UInt64 value) { return value * GByte; }

// -------------------------- Platform independent stdio types -----------------

typedef	int                         IntForStdio;           // format: d,x,X
typedef	unsigned int                UIntForStdio;          // format: u,x,X
typedef	long                        LongForStdio;          // format: ld,lx,lX
typedef	unsigned long               ULongForStdio;         // format: lu,lx,lX
typedef	long long                   LongLongForStdio;      // format: lld,llx,llX
typedef	unsigned long long          ULongLongForStdio;     // format: llu,llx,llX

// -------------------------- Platform dependent Integral types ----------------

typedef Int64						IntPtr;		// Integer as large as a pointer
typedef UInt64						UIntPtr;	// unsigned Integer as large as a pointer

typedef	IntPtr						PtrDiff;

typedef	size_t						MemSize;	// unsigned number of raw bytes
typedef	IntPtr						MemOffset;

typedef	IntPtr						NumBytes;	// signed number of raw bytes

// -------------------------- Inline conversion functions ----------------------

inline Int32	TruncateTo32Bit (Int64 int64)
{
	return  (Int32) int64;
}

inline UInt32	TruncateTo32Bit (UInt64 uint64)
{
	return  (UInt32) uint64;
}

#if defined (macintosh) || defined (__linux__)
inline Int32	TruncateTo32Bit (long int64)		// 64bit macen a long is 64 bites, megis kulon tipusnak erzi a long-ot es a longlong-ot, ezert ambigous volt. FG0710
{
	return (Int32) int64;
}

inline UInt32	TruncateTo32Bit (unsigned long uint64)
{
	return (UInt32) uint64;
}
#endif

inline UInt32	Strlen32 (const char* pStr)
{
	return  GS::TruncateTo32Bit (std::strlen (pStr));
}


#define	Sizeof32(par)		GS::TruncateTo32Bit (sizeof (par))
#define SizeofArray(par)	GS::TruncateTo32Bit (sizeof (par) / sizeof (par[0]))

template<typename IntegerType>
GS_FORCE_INLINE IntegerType RoundUp8 (IntegerType value)
{
	return (value + 7) & ~(IntegerType (7));
}

template<typename IntegerType>
GS_FORCE_INLINE IntegerType RoundUp4 (IntegerType value)
{
	return (value + 3) & ~(IntegerType (3));
}

// -------------------------------- Basic types --------------------------------

typedef	UInt32						GSType;			// == OSType on Mac
typedef	UInt32						GSFlags;
typedef Int32						GSSize;			// not unsigned for compatibility with Mac
typedef Int32						GSIndex;		// not unsigned for compatibility
typedef	char*						GSPtr;			// == Ptr on Mac
typedef	const char *				GSConstPtr;		// == const Ptr on Mac
typedef	GSPtr*						GSHandle;		// == Handle on Mac
typedef const char *const *			GSConstHandle;	// == const Handle on Mac
typedef	short						GSErr;			// == OSErr  on Mac
typedef	Int32						GSErrCode;		// bit coded error code

typedef GSErrCode					ErrCode;		// GS::ErrCode

typedef UInt32						USize;			// logical size (measured in context dependent unit)
typedef UInt32						UIndex;			// logical index
typedef Int32						Offset;			// logical offset (signed!)
typedef Int64						IteratorOffset;

static constexpr UIndex				MaxUIndex = 4294967295;
static constexpr USize				MaxUSize  = 4294967295;

typedef UInt8						UChar;
typedef UInt16						UShort;
typedef UInt32						ULong;

static constexpr UChar				MaxUChar  = 255;
static constexpr UShort				MaxUShort = 65535;
static constexpr ULong				MaxULong  = 4294967295;

typedef	char						Utf8Char;
typedef UInt16						Utf16Char;

#ifdef WINDOWS
typedef Utf16Char					NChar;
#else
typedef Utf8Char					NChar;
#endif

enum PlatformSign {
	Unknown_Platform_Sign	= 0,
	Mac_Platform_Sign		= 19789, //'MM',
	Mactel_Platform_Sign	= 28013, //'mm',
	Win_Platform_Sign		= 22359, //'WW',
	Unx_Platform_Sign		= 21845  //'UU'
};

#if defined GS_WIN
	constexpr PlatformSign Act_Platform_Sign = Win_Platform_Sign;
#elif defined GS_MAC
	constexpr PlatformSign Act_Platform_Sign = Mactel_Platform_Sign;
#elif defined GS_LINUX
	constexpr PlatformSign Act_Platform_Sign = Unx_Platform_Sign;
#else
	#error "Unknown Operating System."
#endif

// --------------------------------- Constants ---------------------------------

extern GSROOT_DLL_EXPORT const char* EOL;	// WINDOWS = "\r\n" - macintosh = "\n" - linux = "\n"

// -------------------------------- Error codes --------------------------------

enum ErrorType : GSErrCode {
	ErrRead			=	-19,	// == readErr		on Mac		/*I/O System Errors*/
	ErrDskFul		=	-34,	// == dskFulErr		on Mac		/*disk full*/
	ErrIO			=	-36,	// == ioErr			on Mac
	ErrEof			=	-39,	// == eofErr		on Mac		/*End of file*/
	ErrFnf			=	-43,	// == fnfErr		on Mac		/*File not found*/
	ErrParam		=	-50,	// == paramErr		on Mac
	ErrPerm			=	-54,	// == permErr		on Mac		/*permissions error (on file open)*/
	ErrWrPerm		=	-61,	// == wrPermErr		on Mac		/*write permissions error*/
	ErrMemoryFull	=  -108,	// == memFullErr	on Mac
	ErrNilHandle	=  -109,	// == nilHandleErr	on Mac
	ErrUserCanceled	=  -128,	// == userCanceledErr on Mac
	ErrTime			= -2015,	// == invalidTime	on Mac
	ErrNilPtr		= -7001,
	ErrEmptyHandle	= -7002,
	Error			= -7003,
	Cancel			= -7004,
	ExceptionError	= -7005
};


enum NoErrorType : GSErrCode {
	NoError = 0
};


inline GSErr	GSErrCode2GSErr (GSErrCode errCode)
	{
		return  static_cast<GSErr> (errCode == NoError ? NoError : Error);
	}

static constexpr Int32 ErrorFlagMask = (Int32) 0x80000000;
static constexpr Int32 ModuleMask	 = 0x7fff0000;
static constexpr Int32 ErrorCodeMask = 0x0000ffff;


// ----------------- Error code definitions for GSRoot module ------------------

constexpr Int32 GSRootModuleId = 256;
constexpr Int32 GSRootErrorStart = ErrorFlagMask | (GSRootModuleId << 16);

	// Error code ranges for GSRoot module are defined here to make the range allocation easier

constexpr Int32 IntegrityError = GSRootErrorStart + 0;		// state of the entity is invalid

constexpr Int32 IChannelErrors		= GSRootErrorStart + 0x0100;
constexpr Int32 OChannelErrors		= GSRootErrorStart + 0x0200;
constexpr Int32 ClassManagerErrors	= GSRootErrorStart + 0x0300;
constexpr Int32 GuidErrors			= GSRootErrorStart + 0x0400;

constexpr Int32 GSPrefErrors		= GSRootErrorStart + 0x0500;


	// Range-based for iteration support

// TODO C++20: Replace this with std::views::iota.
template <class T>
struct RangeDescriptor {
	T rangeBegin;
	T rangeEnd;

	struct Iterator {
		T index;

		T    operator* () const { return index; }
		bool operator!= (const Iterator& rhs) const { return index != rhs.index; }
		void operator++ () { ++index; }
	};

	Iterator    begin () const { return { rangeBegin }; }
	Iterator    end () const { return { rangeEnd }; }
};


template <class T>
RangeDescriptor<T>    InRange (const T& begin, const T& end) { return { begin, end }; }


template <typename T, std::size_t N>
constexpr USize  ArraySize (T const (&)[N]) noexcept
{
	return static_cast<USize> (N);
}


// In clang static_assert (false, "") will always yield a compilation error, even if the containing template function is not instantiated at all.
// As a workaround, you can use
//   - AlwaysFalse<Ts...>, if you have type template parameters, and
//   - ReturnFalse (ts...), if you have value template parameters.

template <class...>
constexpr bool	AlwaysFalse = false;


template <class... Ts>
constexpr bool	ReturnFalse (const Ts&...)
{
	return false;
}


}	// namespace GS


// ----------------- Bringing the most frequently used names into the global namespace

using GS::GSType;
using GS::GSFlags;
using GS::GSSize;
using GS::GSIndex;
using GS::GSPtr;
using GS::GSConstPtr;
using GS::GSHandle;
using GS::GSConstHandle;
using GS::GSErr;
using GS::GSErrCode;

using GS::NoError;
using GS::ErrIO;
using GS::ErrParam;
using GS::ErrMemoryFull;
using GS::ErrNilHandle;
using GS::ErrTime;
using GS::ErrNilPtr;
using GS::ErrEmptyHandle;
using GS::Error;
using GS::Cancel;
using GS::ExceptionError;

using GS::USize;
using GS::UIndex;
using GS::UChar;
using GS::UShort;
using GS::ULong;
using GS::Int8;
using GS::UInt8;
using GS::Int16;
using GS::UInt16;
using GS::Int32;
using GS::UInt32;
using GS::Int64;
using GS::UInt64;

using GS::NumBytes;
using GS::NumChars;

using GS::MemSize;
using GS::MemOffset;

using GS::MaxUIndex;
using GS::MaxUSize;

using GS::MaxUChar;
using GS::MaxUShort;
using GS::MaxULong;

using GS::Utf8Char;
using GS::Utf16Char;

using GS::MaxInt8;
using GS::MaxUInt8;
using GS::MaxInt16;
using GS::MaxUInt16;
using GS::MaxInt32;
using GS::MaxUInt32;
using GS::MaxInt64;
using GS::MaxUInt64;
using GS::MaxFloat;
using GS::MaxDouble;

using GS::MinInt8;
using GS::MinInt16;
using GS::MinInt32;
using GS::MinInt64;
using GS::MinFloat;
using GS::MinDouble;

using GS::TruncateTo32Bit;
using GS::Strlen32;

using GS::operator"" _KByte;
using GS::operator"" _MByte;
using GS::operator"" _GByte;

using GS::InRange;

#endif
