// *********************************************************************************************************************
// Description:		GRAPHISOFT String Utilities
//
// Namespace:		-
// Contact person:	MM
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (CH_HPP)
#define	CH_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------
// from C Runtime Library
#include	<stddef.h>
#include	<string.h>

#if (_MSC_VER >= 1900 && _MSC_VER < 2000)	// MSVC 14
#include	<intrin.h>
#include	<xlocale>
#endif

// from Standard C++ library
#if defined (_MSC_VER)
#include <stdarg.h>
namespace std { using ::va_list; }
#else
#include <cstdarg>
	#if defined (_LIBCPP_VERSION)
		#include <cstring>
	#endif
#endif


// from GRoot
#include	"Definitions.hpp"
#include	"GSDebug.hpp"
#include	"GSRootExport.hpp"

#if defined(macintosh)
// from Carbon/CoreFoundation
typedef const struct __CFString * CFStringRef;
typedef UInt32 CFStringEncoding;
#endif


// =====================================================================================================================
// Manager Identifier
// =====================================================================================================================

#define	IDStringManager		'CH04'				// toASCII added  mm.2004.02.25.
#define	chManager			ch04Manager

// =====================================================================================================================
// Type definitions
// =====================================================================================================================

const char	CharNULL		= 0x00;
const char	CharENTER		= 0x03;
const char	CharBACKSPACE	= 0x08;
const char	CharTAB			= 0x09;
const char	CharCR			= 0x0D;
const char	CharLF			= 0x0A;
const char	CharESC			= 0x1B;

enum GSCharCode {
	CC_Default		= 0,
	CC_System		= 1,
	CC_User			= 2,
	CC_Application	= 3,
	CC_Legacy		= 4,

	CC_WestEuropean	= 11,
	CC_EastEuropean	= 12,
	CC_Baltic		= 13,
	CC_Cyrillic		= 14,
	CC_Greek		= 15,
	CC_Turkish		= 16,

	CC_Hebrew		= 21,
	CC_Arabic		= 22,

	CC_Thai			= 31,
	CC_Japanese		= 32,
	CC_TradChinese	= 33,
	CC_SimpChinese	= 34,
	CC_Korean		= 35,

	CC_Symbol		= 40,

	CC_UTF8			= 99,
	CC_UTF16		= 100,
	CC_UniCode		= 100
};

enum EOLType {
	EOL_CR			=	0,
	EOL_LF			=	1,
	EOL_CRLF		=	2,
	EOL_ANY         =   3
};


enum CaseType {
	CS_CaseInsensitive	= 0,
	CS_CaseSensitive	= 1
};

namespace GS {
	const Int32	CStringLen			=  -1;
	const UChar LastASCIICharacter	= 127;
}

using GS::CStringLen;

namespace GS {
	typedef const struct CHANSI2UnicodeCache* CHANSI2UnicodeCacheRef;
	typedef const struct CHUnicode2ANSICache* CHUnicode2ANSICacheRef;
}

#if defined (macintosh)
	const EOLType			Platform_EOLType	= EOL_CR;
#elif defined (WINDOWS)
	const EOLType			Platform_EOLType	= EOL_CRLF;
#elif defined (__linux__)
	const EOLType			Platform_EOLType	= EOL_LF;
#else
	#error	Unknown platform.
#endif

// =====================================================================================================================
// Predefinitions
// =====================================================================================================================

namespace GS { namespace Unicode { namespace UTF8 {
	GSROOT_DLL_EXPORT bool	IsEqualCStrings (const Utf8Char* p1, const Utf8Char* p2, CaseType cs);
} } }

// =====================================================================================================================
// Interface definition
// =====================================================================================================================

inline bool	CHisASCII (char aChar)
{
	return  0 <= aChar && aChar <= GS::LastASCIICharacter;
}


inline bool CHisAlphaASCII (char aChar)
{
	DBASSERT (CHisASCII (aChar));

	return  ('A' <= aChar && aChar <= 'Z') || ('a' <= aChar && aChar <= 'z');
}


inline bool CHisDigitASCII (char aChar)
{
	DBASSERT (CHisASCII (aChar));

	return  '0' <= aChar && aChar <= '9';
}


inline bool CHisAlnumASCII (char aChar)
{
	DBASSERT (CHisASCII (aChar));

	return  CHisAlphaASCII (aChar) || CHisDigitASCII (aChar);
}


GSROOT_DLL_EXPORT bool	CHisAlpha (const char* pChar, GSCharCode charCode = CC_Default);
GSROOT_DLL_EXPORT bool	CHisDigit (const char* pChar, GSCharCode charCode = CC_Default);

GSROOT_DLL_EXPORT bool	CHisHexaDigit (const char* pChar, GSCharCode charCode = CC_Default);
GSROOT_DLL_EXPORT bool	CHisAlnum (const char* pChar, GSCharCode charCode = CC_Default);

GSROOT_DLL_EXPORT bool 			CHInternalTest (GSCharCode charCode = CC_Default);
GSROOT_DLL_EXPORT GSCharCode	CHGetSystemCharCode (void);
GSROOT_DLL_EXPORT GSCharCode	CHGetUserCharCode (void);
GSROOT_DLL_EXPORT GSCharCode	CHGetDefaultCharCode (void);
GSROOT_DLL_EXPORT void			CHSetDefaultCharCode (GSCharCode newDefault);
GSROOT_DLL_EXPORT GSCharCode	CHGetLegacyCharCode (void);
GSROOT_DLL_EXPORT void			CHSetLegacyCharCode (GSCharCode newLegacy);
GSROOT_DLL_EXPORT void 			CHtoUpper (char* pChars, Int32 nChars = CStringLen, GSCharCode charCode = CC_Default);
GSROOT_DLL_EXPORT void 			CHtoUpperASCII (char* pChars, Int32 nChars = CStringLen);
GSROOT_DLL_EXPORT void 			CHtoASCII (char* pChars, Int32 nChars = CStringLen, GSCharCode charCode = CC_Default, char substChar = '?');
GSROOT_DLL_EXPORT bool 			CHSingleByteCharacters (GSCharCode charCode = CC_Default);
GSROOT_DLL_EXPORT Int32			CHCopyPascal (const unsigned char* p1PascalString, unsigned char* p2PascalString);
GSROOT_DLL_EXPORT Int32			CHCopyC (const char* p1CString, char* p2CString);
GSROOT_DLL_EXPORT Int32			CHTruncate (
									const char*		sourceCString,			// Zero terminated source string
									char*			targetCString,			// pointer to the target, can be equal with sourceCString
									Int32			targetSize,				// the size of target buffer
									GSCharCode		charCode = CC_Default	// the character code of the source string
								);											// RETURNS:	the size of the resulted string (without the 0 byte)


GSROOT_DLL_EXPORT void	CHtoLower (char* pChars, Int32 nChars = CStringLen, GSCharCode charCode = CC_Default);
GSROOT_DLL_EXPORT Int32	CHpascal2c (const unsigned char* pPascalString, char* pCString);
GSROOT_DLL_EXPORT Int32	CHc2pascal (const char* pCString, unsigned char* pPascalString);

GSROOT_DLL_EXPORT void	IVChars (GS::PlatformSign iplatform, char* pChars, Int32 nChars, GSCharCode charCode = CC_Default, GS::PlatformSign targetPlatform = GS::Act_Platform_Sign);
GSROOT_DLL_EXPORT void	IVCString (GS::PlatformSign iplatform, char* pCString, GSCharCode charCode = CC_Default, GS::PlatformSign targetPlatform = GS::Act_Platform_Sign);
GSROOT_DLL_EXPORT void	IVPString (GS::PlatformSign iplatform, unsigned char* pPString, GSCharCode charCode = CC_Default, GS::PlatformSign targetPlatform = GS::Act_Platform_Sign);

GSROOT_DLL_EXPORT Int32	IVEndofLine (const char* pChars, Int32 nChars, char* pNewChars, Int32 maxNewChars, EOLType targetEOL = Platform_EOLType);

GSROOT_DLL_EXPORT Int32	CHANSI2Unicode (const char* pChars, Int32 nChars, GS::uchar_t* pWChars, Int32 maxWChars, GSCharCode charCode = CC_Default, GS::CHANSI2UnicodeCacheRef* cache = nullptr);
GSROOT_DLL_EXPORT Int32	CHUnicode2ANSI (const GS::uchar_t* pWChars, Int32 nWChars, char* pChars, Int32 maxChars, GSCharCode charCode = CC_Default, bool lossyConversion = true, GS::CHUnicode2ANSICacheRef* cache = nullptr);
GSROOT_DLL_EXPORT void	CHFreeUnicode2ANSICache (GS::CHUnicode2ANSICacheRef cache);
GSROOT_DLL_EXPORT void	CHFreeANSI2UnicodeCache (GS::CHANSI2UnicodeCacheRef cache);

GSROOT_DLL_EXPORT Int32	CHANSItoUTF8 (const char* pChars, Int32 nChars, char** pUTF8Chars, GSCharCode charCode);
GSROOT_DLL_EXPORT Int32	CHUTF8toANSI (const char* pUTF8Chars, Int32 nChars, char** pChars, GSCharCode charCode);

#if defined (macintosh)
GSROOT_DLL_EXPORT CFStringRef		CHToCFString (const char* pChars, Int32 nChars, GSCharCode charCode = CC_Default) __attribute__((cf_returns_retained));
GSROOT_DLL_EXPORT CFStringEncoding	CHGSCharCode2CFStringEncoding (GSCharCode charCode);
#endif

GSROOT_DLL_EXPORT Int32	CHCompareASCII (const char* p1, const char* p2, CaseType cs = CS_CaseSensitive);
GSROOT_DLL_EXPORT bool	CHEqualCStringsInsensitive (const char* p1, const char* p2);

inline bool CHEqualCStrings (const char* p1, const char* p2)
{
	for (; *p1 == *p2 ; p1++, p2++) {
		if (*p1 == '\0')
			return  true;
	}

	return  false;
}


inline bool CHEqualASCII (const char* p1, const char* p2, CaseType cs = CS_CaseSensitive)
{
	if (cs == CS_CaseSensitive)
		return  CHEqualCStrings (p1, p2);
	else
		return  CHEqualCStringsInsensitive (p1, p2);
}


GSROOT_DLL_EXPORT Int32	CHCompareFileNames (const char* p1CFileName, const char* p2CFileName, GSCharCode charCode = CC_Default);
GSROOT_DLL_EXPORT bool	CHEqualFileNames (const char* p1CFileName, const char* p2CFileName, GSCharCode charCode = CC_Default);
GSROOT_DLL_EXPORT bool	CHEqualPFileNames (const unsigned char* p1PFileName, const unsigned char* p2PFileName, GSCharCode charCode = CC_Default);
GSROOT_DLL_EXPORT Int32	CHCompareTexts (const char* p1, Int32 n1, const char* p2, Int32 n2, CaseType cs = CS_CaseSensitive, GSCharCode cc = CC_Default);
GSROOT_DLL_EXPORT bool	CHEqualCStrings (const char* p1, const char* p2, CaseType cs, GSCharCode cc = CC_Default);
inline Int32 CHCompareCStrings (const char* p1, const char* p2, CaseType cs = CS_CaseSensitive, GSCharCode cc = CC_Default)
{
	return  CHCompareTexts (p1, CStringLen, p2, CStringLen, cs, cc);
}



GSROOT_DLL_EXPORT Int32 		CHCharBytes (const char* pChars, GSCharCode charCode = CC_Default);
GSROOT_DLL_EXPORT const char* 	CHGetNextCharPtr (const char* pCString, GSCharCode charCode = CC_Default);
GSROOT_DLL_EXPORT char* 		CHGetNextCharPtr (char* pCString, GSCharCode charCode = CC_Default);
GSROOT_DLL_EXPORT const char* 	CHGetLastCharPtr (const char* pCString, GSCharCode charCode = CC_Default);
GSROOT_DLL_EXPORT char* 		CHGetLastCharPtr (char* pCString, GSCharCode charCode = CC_Default);
GSROOT_DLL_EXPORT const char* 	CHSearchCharLeft (const char* pChar, const char* pChars, Int32 nChars = CStringLen, GSCharCode charCode = CC_Default);
GSROOT_DLL_EXPORT char* 		CHSearchCharLeft (const char* pChar, char* pChars, Int32 nChars = CStringLen, GSCharCode charCode = CC_Default);
GSROOT_DLL_EXPORT const char* 	CHSearchCharRight (const char* pChar, const char* pChars, Int32 nChars = CStringLen, GSCharCode charCode = CC_Default);
GSROOT_DLL_EXPORT char* 		CHSearchCharRight (const char* pChar, char* pChars, Int32 nChars = CStringLen, GSCharCode charCode = CC_Default);
GSROOT_DLL_EXPORT const char* 	CHSearchSubstring (const char* pCSubString, const char* pChars, Int32 nChars = CStringLen, CaseType cs = CS_CaseSensitive, GSCharCode cc = CC_Default);
GSROOT_DLL_EXPORT char* 		CHSearchSubstring (const char* pCSubString, char* pChars, Int32 nChars = CStringLen, CaseType cs = CS_CaseSensitive, GSCharCode cc = CC_Default);
GSROOT_DLL_EXPORT const char* 	CHGetNextLine (const char* pChars, Int32* lineEndLength = nullptr, Int32 nChars = CStringLen, EOLType eolType = EOL_ANY, GSCharCode charCode = CC_Default);
GSROOT_DLL_EXPORT char* 		CHGetNextLine (char* pChars, Int32* lineEndLength = nullptr, Int32 nChars = CStringLen, EOLType eolType = EOL_ANY, GSCharCode charCode = CC_Default);

GSROOT_DLL_EXPORT void	 		CHGetXMLString (const char *buffer, char *str, Int32 maxLen);

namespace GS {

inline const char*	GetScanfFormatCStrOf (const char* par)		{ return par == nullptr ? "" : "%c\0%s\0"; }
//inline const char*	GetScanfFormatCStrOf (const unsigned char* par)		{ return par == nullptr ? "" : "%hhu\0%hho\0%hhx\0%hhX\0"; }
inline const char*	GetScanfFormatCStrOf (const Int16* par)		{ return par == nullptr ? "" : "%hd\0%hi\0%hn\0%ho\0%hx\0%hX\0"; }
inline const char*	GetScanfFormatCStrOf (const UInt16* par)	{ return par == nullptr ? "" : "%hu\0%ho\0%hx\0%hX\0"; }
inline const char*	GetScanfFormatCStrOf (const Int32* par)		{ return par == nullptr ? "" : "%d\0%i\0%n\0%o\0%x\0%X\0"; }
inline const char*	GetScanfFormatCStrOf (const UInt32* par)	{ return par == nullptr ? "" : "%u\0%o\0%x\0%X\0"; }
inline const char*	GetScanfFormatCStrOf (const Int64* par)		{ return par == nullptr ? "" : "%lld\0%lli\0%lln\0%llo\0%llx\0%llX\0"; }
inline const char*	GetScanfFormatCStrOf (const UInt64* par)	{ return par == nullptr ? "" : "%llu\0%llo\0%llx\0%llX\0"; }
inline const char*	GetScanfFormatCStrOf (const float* par)		{ return par == nullptr ? "" : "%f\0%F\0%g\0%G\0%e\0%E\0%a\0%A\0"; }
inline const char*	GetScanfFormatCStrOf (const double* par)	{ return par == nullptr ? "" : "%lf\0%lF\0%lg\0%lG\0%le\0%lE\0%la\0%lA\0"; }
#if defined (GS_64BIT)
  template<class Type>
  inline const char*	GetScanfFormatCStrOf (Type** par)		{ return par == nullptr ? "" : "%p\0%llx\0%llX\0"; }
#else
  template<class Type>
  inline const char*	GetScanfFormatCStrOf (Type** par)		{ return par == nullptr ? "" : "%p\0%lx\0%lX\0"; }
#endif

inline const char*	GetPrintfFormatCStrOf (const char* par)		{ return par == nullptr ? "" : "%s\0"; }
inline const char*	GetPrintfFormatCStrOf (const char)			{ return "%c\0%hhd\0%hhi\0%hhn\0"; }
inline const char*	GetPrintfFormatCStrOf (const unsigned char)	{ return "%hho\0%hhu\0%hhx\0%hhX\0"; }
inline const char*	GetPrintfFormatCStrOf (const Int16)			{ return "%hd\0%hi\0%hn\0"; }
inline const char*	GetPrintfFormatCStrOf (const UInt16)		{ return "%hu\0%ho\0%hx\0%hX\0"; }
inline const char*	GetPrintfFormatCStrOf (const Int32)			{ return "%d\0%i\0%n\0"; }
inline const char*	GetPrintfFormatCStrOf (const UInt32)		{ return "%u\0%o\0%x\0%X\0"; }
inline const char*	GetPrintfFormatCStrOf (const Int64)			{ return "%lld\0%lli\0%lln\0"; }
inline const char*	GetPrintfFormatCStrOf (const UInt64)		{ return "%llu\0%llo\0%llx\0"; }
inline const char*	GetPrintfFormatCStrOf (const double)		{ return "%f\0%F\0%g\0%G\0%e\0%E\0%a\0%A\0%lf\0%lF\0%lg\0%lG\0%le\0%lE\0%la\0%lA\0"; }
#if defined (GS_64BIT)
  template<class Type>
  inline const char*	GetPrintfFormatCStrOf (const Type*)		{ return "%p\0%llx\0%llX\0"; }
#else
  template<class Type>
  inline const char*	GetPrintfFormatCStrOf (const Type*)		{ return "%p\0%lx\0%lX\0"; }
#endif



#if defined (GS_64BIT)
 #if defined (__GNUC__)
	inline const char*	GetScanfFormatCStrOf (const long* par)			{ return GetScanfFormatCStrOf ((Int64*)par); }
	inline const char*	GetScanfFormatCStrOf (const unsigned long* par)	{ return GetScanfFormatCStrOf ((UInt64*)par); }

	inline const char*	GetPrintfFormatCStrOf (const long par)			{ return GetPrintfFormatCStrOf ((Int64)par); }
	inline const char*	GetPrintfFormatCStrOf (const unsigned long par)	{ return GetPrintfFormatCStrOf ((UInt64)par); }
 #else //__GNUC__
	inline const char*	GetScanfFormatCStrOf (const long* par)			{ return GetScanfFormatCStrOf ((Int32*)par); }
	inline const char*	GetScanfFormatCStrOf (const unsigned long* par)	{ return GetScanfFormatCStrOf ((UInt32*)par); }

	inline const char*	GetPrintfFormatCStrOf (const long par)			{ return GetPrintfFormatCStrOf ((Int32)par); }
	inline const char*	GetPrintfFormatCStrOf (const unsigned long par)	{ return GetPrintfFormatCStrOf ((UInt32)par); }
 #endif //__GNUC__
#else //GS_64BIT
 inline const char*	GetScanfFormatCStrOf (const int* par)			{ return GetScanfFormatCStrOf ((Int32*)par); }
 inline const char*	GetScanfFormatCStrOf (const unsigned int* par)	{ return GetScanfFormatCStrOf ((UInt32*)par); }

 inline const char*	GetPrintfFormatCStrOf (const int par)			{ return GetPrintfFormatCStrOf ((Int32)par); }
 inline const char*	GetPrintfFormatCStrOf (const unsigned int par)	{ return GetPrintfFormatCStrOf ((UInt32)par); }
#endif //GS_64BIT

 void InitDefaultCharCode (void);

enum FormatCStrCheckFlags
{
	FormatCStrFullCheck = 0x00,
	FormatCStrNoCheckNumOfResult = 0x01
};

GSROOT_DLL_EXPORT int	checkedsscanf (FormatCStrCheckFlags chkFlags, const char* str, const char* format, const char** formatStrs, ...);
GSROOT_DLL_EXPORT int	checkedvsscanf (FormatCStrCheckFlags chkFlags, const char* str, const char* format, const char** formatStrs, std::va_list arg);

template<class Type1>
inline int	csscanf (const char* str, const char* format, Type1* par1)
{
	const char* formatStrs[2] = {GetScanfFormatCStrOf(par1), nullptr};
	return checkedsscanf (FormatCStrFullCheck, str, format, formatStrs, par1);
}

template<class Type1, class Type2>
inline int	csscanf (const char* str, const char* format, Type1* par1, Type2* par2)
{
	const char* formatStrs[3] = {GetScanfFormatCStrOf(par1), GetScanfFormatCStrOf(par2), nullptr};
	return checkedsscanf (FormatCStrFullCheck, str, format, formatStrs, par1, par2);
}

template<class Type1, class Type2, class Type3>
inline int	csscanf (const char* str, const char* format, Type1* par1, Type2* par2, Type3* par3)
{
	const char* formatStrs[4] = {GetScanfFormatCStrOf(par1), GetScanfFormatCStrOf(par2), GetScanfFormatCStrOf(par3), nullptr};
	return checkedsscanf (FormatCStrFullCheck, str, format, formatStrs, par1, par2, par3);
}

template<class Type1, class Type2, class Type3, class Type4>
inline int	csscanf (const char* str, const char* format, Type1* par1, Type2* par2, Type3* par3, Type4* par4)
{
	const char* formatStrs[5] = {GetScanfFormatCStrOf(par1), GetScanfFormatCStrOf(par2), GetScanfFormatCStrOf(par3), GetScanfFormatCStrOf(par4), nullptr};
	return checkedsscanf (FormatCStrFullCheck, str, format, formatStrs, par1, par2, par3, par4);
}

template<class Type1, class Type2, class Type3, class Type4, class Type5>
inline int	csscanf (const char* str, const char* format, Type1* par1, Type2* par2, Type3* par3, Type4* par4, Type5* par5)
{
	const char* formatStrs[6] = {GetScanfFormatCStrOf(par1), GetScanfFormatCStrOf(par2), GetScanfFormatCStrOf(par3), GetScanfFormatCStrOf(par4), GetScanfFormatCStrOf(par5), nullptr};
	return checkedsscanf (FormatCStrFullCheck, str, format, formatStrs, par1, par2, par3, par4, par5);
}

template<class Type1, class Type2, class Type3, class Type4, class Type5, class Type6>
inline int	csscanf (const char* str, const char* format, Type1* par1, Type2* par2, Type3* par3, Type4* par4, Type5* par5, Type6* par6)
{
	const char* formatStrs[7] = {GetScanfFormatCStrOf(par1), GetScanfFormatCStrOf(par2), GetScanfFormatCStrOf(par3), GetScanfFormatCStrOf(par4), GetScanfFormatCStrOf(par5), GetScanfFormatCStrOf(par6), nullptr};
	return checkedsscanf (FormatCStrFullCheck, str, format, formatStrs, par1, par2, par3, par4, par5, par6);
}

template<class Type1, class Type2, class Type3, class Type4, class Type5, class Type6, class Type7>
inline int	csscanf (const char* str, const char* format, Type1* par1, Type2* par2, Type3* par3, Type4* par4, Type5* par5, Type6* par6, Type7* par7)
{
	const char* formatStrs[8] = {GetScanfFormatCStrOf(par1), GetScanfFormatCStrOf(par2), GetScanfFormatCStrOf(par3), GetScanfFormatCStrOf(par4), GetScanfFormatCStrOf(par5), GetScanfFormatCStrOf(par6), GetScanfFormatCStrOf(par7), nullptr};
	return checkedsscanf (FormatCStrFullCheck, str, format, formatStrs, par1, par2, par3, par4, par5, par6, par7);
}

template<class Type1, class Type2, class Type3, class Type4, class Type5, class Type6, class Type7, class Type8>
inline int	csscanf (const char* str, const char* format, Type1* par1, Type2* par2, Type3* par3, Type4* par4, Type5* par5, Type6* par6, Type7* par7, Type8* par8)
{
	const char* formatStrs[9] = {GetScanfFormatCStrOf(par1), GetScanfFormatCStrOf(par2), GetScanfFormatCStrOf(par3), GetScanfFormatCStrOf(par4), GetScanfFormatCStrOf(par5), GetScanfFormatCStrOf(par6), GetScanfFormatCStrOf(par7), GetScanfFormatCStrOf(par8), nullptr};
	return checkedsscanf (FormatCStrFullCheck, str, format, formatStrs, par1, par2, par3, par4, par5, par6, par7, par8);
}

template<class Type1, class Type2, class Type3, class Type4, class Type5, class Type6, class Type7, class Type8, class Type9>
inline int	csscanf (const char* str, const char* format, Type1* par1, Type2* par2, Type3* par3, Type4* par4, Type5* par5, Type6* par6, Type7* par7, Type8* par8, Type9* par9)
{
	const char* formatStrs[10] = {GetScanfFormatCStrOf(par1), GetScanfFormatCStrOf(par2), GetScanfFormatCStrOf(par3), GetScanfFormatCStrOf(par4), GetScanfFormatCStrOf(par5), GetScanfFormatCStrOf(par6), GetScanfFormatCStrOf(par7), GetScanfFormatCStrOf(par8), GetScanfFormatCStrOf(par9), nullptr};
	return checkedsscanf (FormatCStrFullCheck, str, format, formatStrs, par1, par2, par3, par4, par5, par6, par7, par8, par9);
}

template<class Type1, class Type2, class Type3, class Type4, class Type5, class Type6, class Type7, class Type8, class Type9, class Type10>
inline int	csscanf (const char* str, const char* format, Type1* par1, Type2* par2, Type3* par3, Type4* par4, Type5* par5, Type6* par6, Type7* par7, Type8* par8, Type9* par9, Type10* par10)
{
	const char* formatStrs[11] = {GetScanfFormatCStrOf(par1), GetScanfFormatCStrOf(par2), GetScanfFormatCStrOf(par3), GetScanfFormatCStrOf(par4), GetScanfFormatCStrOf(par5), GetScanfFormatCStrOf(par6), GetScanfFormatCStrOf(par7), GetScanfFormatCStrOf(par8), GetScanfFormatCStrOf(par9), GetScanfFormatCStrOf(par10), nullptr};
	return checkedsscanf (FormatCStrFullCheck, str, format, formatStrs, par1, par2, par3, par4, par5, par6, par7, par8, par9, par10);
}

template<class Type1, class Type2, class Type3, class Type4, class Type5, class Type6, class Type7, class Type8, class Type9, class Type10, class Type11>
inline int	csscanf (const char* str, const char* format, Type1* par1, Type2* par2, Type3* par3, Type4* par4, Type5* par5, Type6* par6, Type7* par7, Type8* par8, Type9* par9, Type10* par10, Type11* par11)
{
	const char* formatStrs[12] = {GetScanfFormatCStrOf(par1), GetScanfFormatCStrOf(par2), GetScanfFormatCStrOf(par3), GetScanfFormatCStrOf(par4), GetScanfFormatCStrOf(par5), GetScanfFormatCStrOf(par6), GetScanfFormatCStrOf(par7), GetScanfFormatCStrOf(par8), GetScanfFormatCStrOf(par9), GetScanfFormatCStrOf(par10), GetScanfFormatCStrOf(par11), nullptr};
	return checkedsscanf (FormatCStrFullCheck, str, format, formatStrs, par1, par2, par3, par4, par5, par6, par7, par8, par9, par10, par11);
}

template<class Type1, class Type2, class Type3, class Type4, class Type5, class Type6, class Type7, class Type8, class Type9, class Type10, class Type11, class Type12>
inline int	csscanf (const char* str, const char* format, Type1* par1, Type2* par2, Type3* par3, Type4* par4, Type5* par5, Type6* par6, Type7* par7, Type8* par8, Type9* par9, Type10* par10, Type11* par11, Type12* par12)
{
	const char* formatStrs[13] = {GetScanfFormatCStrOf(par1), GetScanfFormatCStrOf(par2), GetScanfFormatCStrOf(par3), GetScanfFormatCStrOf(par4), GetScanfFormatCStrOf(par5), GetScanfFormatCStrOf(par6), GetScanfFormatCStrOf(par7), GetScanfFormatCStrOf(par8), GetScanfFormatCStrOf(par9), GetScanfFormatCStrOf(par10), GetScanfFormatCStrOf(par11), GetScanfFormatCStrOf(par12), nullptr};
	return checkedsscanf (FormatCStrFullCheck, str, format, formatStrs, par1, par2, par3, par4, par5, par6, par7, par8, par9, par10, par11, par12);
}

GSROOT_DLL_EXPORT int	checkedsnprintf (FormatCStrCheckFlags chkFlags, char* buffer, size_t bufferSize, const char* format, const char** formatStrs, ...);
GSROOT_DLL_EXPORT int	checkedvsnprintf (FormatCStrCheckFlags chkFlags, char* buffer, size_t bufferSize, const char* format, const char** formatStrs, std::va_list arg);

template<class Type1>
inline int	csnprintf (char* buffer, size_t bufferSize, const char* format, Type1 par1)
{
	const char* formatStrs[2] = {GetPrintfFormatCStrOf(par1), nullptr};
	return checkedsnprintf (FormatCStrFullCheck, buffer, bufferSize, format, formatStrs, par1);
}

template<class Type1, class Type2>
inline int	csnprintf (char* buffer, size_t bufferSize, const char* format, Type1 par1, Type2 par2)
{
	const char* formatStrs[3] = {GetPrintfFormatCStrOf(par1), GetPrintfFormatCStrOf(par2), nullptr};
	return checkedsnprintf (FormatCStrFullCheck, buffer, bufferSize, format, formatStrs, par1, par2);
}

template<class Type1, class Type2, class Type3>
inline int	csnprintf (char* buffer, size_t bufferSize, const char* format, Type1 par1, Type2 par2, Type3 par3)
{
	const char* formatStrs[4] = {GetPrintfFormatCStrOf(par1), GetPrintfFormatCStrOf(par2), GetPrintfFormatCStrOf(par3), nullptr};
	return checkedsnprintf (FormatCStrFullCheck, buffer, bufferSize, format, formatStrs, par1, par2, par3);
}

template<class Type1, class Type2, class Type3, class Type4>
inline int	csnprintf (char* buffer, size_t bufferSize, const char* format, Type1 par1, Type2 par2, Type3 par3, Type4 par4)
{
	const char* formatStrs[5] = {GetPrintfFormatCStrOf(par1), GetPrintfFormatCStrOf(par2), GetPrintfFormatCStrOf(par3), GetPrintfFormatCStrOf(par4), nullptr};
	return checkedsnprintf (FormatCStrFullCheck, buffer, bufferSize, format, formatStrs, par1, par2, par3, par4);
}

template<class Type1, class Type2, class Type3, class Type4, class Type5>
inline int	csnprintf (char* buffer, size_t bufferSize, const char* format, Type1 par1, Type2 par2, Type3 par3, Type4 par4, Type5 par5)
{
	const char* formatStrs[6] = {GetPrintfFormatCStrOf(par1), GetPrintfFormatCStrOf(par2), GetPrintfFormatCStrOf(par3), GetPrintfFormatCStrOf(par4), GetPrintfFormatCStrOf(par5), nullptr};
	return checkedsnprintf (FormatCStrFullCheck, buffer, bufferSize, format, formatStrs, par1, par2, par3, par4, par5);
}

template<class Type1, class Type2, class Type3, class Type4, class Type5, class Type6>
inline int	csnprintf (char* buffer, size_t bufferSize, const char* format, Type1 par1, Type2 par2, Type3 par3, Type4 par4, Type5 par5, Type6 par6)
{
	const char* formatStrs[7] = {GetPrintfFormatCStrOf(par1), GetPrintfFormatCStrOf(par2), GetPrintfFormatCStrOf(par3), GetPrintfFormatCStrOf(par4), GetPrintfFormatCStrOf(par5), GetPrintfFormatCStrOf(par6), nullptr};
	return checkedsnprintf (FormatCStrFullCheck, buffer, bufferSize, format, formatStrs, par1, par2, par3, par4, par5, par6);
}

template<class Type1, class Type2, class Type3, class Type4, class Type5, class Type6, class Type7>
inline int	csnprintf (char* buffer, size_t bufferSize, const char* format, Type1 par1, Type2 par2, Type3 par3, Type4 par4, Type5 par5, Type6 par6, Type7 par7)
{
	const char* formatStrs[8] = {GetPrintfFormatCStrOf(par1), GetPrintfFormatCStrOf(par2), GetPrintfFormatCStrOf(par3), GetPrintfFormatCStrOf(par4), GetPrintfFormatCStrOf(par5), GetPrintfFormatCStrOf(par6), GetPrintfFormatCStrOf(par7), nullptr};
	return checkedsnprintf (FormatCStrFullCheck, buffer, bufferSize, format, formatStrs, par1, par2, par3, par4, par5, par6, par7);
}

template<class Type1, class Type2, class Type3, class Type4, class Type5, class Type6, class Type7, class Type8>
inline int	csnprintf (char* buffer, size_t bufferSize, const char* format, Type1 par1, Type2 par2, Type3 par3, Type4 par4, Type5 par5, Type6 par6, Type7 par7, Type8 par8)
{
	const char* formatStrs[9] = {GetPrintfFormatCStrOf(par1), GetPrintfFormatCStrOf(par2), GetPrintfFormatCStrOf(par3), GetPrintfFormatCStrOf(par4), GetPrintfFormatCStrOf(par5), GetPrintfFormatCStrOf(par6), GetPrintfFormatCStrOf(par7), GetPrintfFormatCStrOf(par8), nullptr};
	return checkedsnprintf (FormatCStrFullCheck, buffer, bufferSize, format, formatStrs, par1, par2, par3, par4, par5, par6, par7, par8);
}

template<class Type1, class Type2, class Type3, class Type4, class Type5, class Type6, class Type7, class Type8, class Type9>
inline int	csnprintf (char* buffer, size_t bufferSize, const char* format, Type1 par1, Type2 par2, Type3 par3, Type4 par4, Type5 par5, Type6 par6, Type7 par7, Type8 par8, Type9 par9)
{
	const char* formatStrs[10] = {GetPrintfFormatCStrOf(par1), GetPrintfFormatCStrOf(par2), GetPrintfFormatCStrOf(par3), GetPrintfFormatCStrOf(par4), GetPrintfFormatCStrOf(par5), GetPrintfFormatCStrOf(par6), GetPrintfFormatCStrOf(par7), GetPrintfFormatCStrOf(par8), GetPrintfFormatCStrOf(par9), nullptr};
	return checkedsnprintf (FormatCStrFullCheck, buffer, bufferSize, format, formatStrs, par1, par2, par3, par4, par5, par6, par7, par8, par9);
}

template<class Type1, class Type2, class Type3, class Type4, class Type5, class Type6, class Type7, class Type8, class Type9, class Type10>
inline int	csnprintf (char* buffer, size_t bufferSize, const char* format, Type1 par1, Type2 par2, Type3 par3, Type4 par4, Type5 par5, Type6 par6, Type7 par7, Type8 par8, Type9 par9, Type10 par10)
{
	const char* formatStrs[11] = {GetPrintfFormatCStrOf(par1), GetPrintfFormatCStrOf(par2), GetPrintfFormatCStrOf(par3), GetPrintfFormatCStrOf(par4), GetPrintfFormatCStrOf(par5), GetPrintfFormatCStrOf(par6), GetPrintfFormatCStrOf(par7), GetPrintfFormatCStrOf(par8), GetPrintfFormatCStrOf(par9), GetPrintfFormatCStrOf(par10), nullptr};
	return checkedsnprintf (FormatCStrFullCheck, buffer, bufferSize, format, formatStrs, par1, par2, par3, par4, par5, par6, par7, par8, par9, par10);
}

template<class Type1, class Type2, class Type3, class Type4, class Type5, class Type6, class Type7, class Type8, class Type9, class Type10, class Type11>
inline int	csnprintf (char* buffer, size_t bufferSize, const char* format, Type1 par1, Type2 par2, Type3 par3, Type4 par4, Type5 par5, Type6 par6, Type7 par7, Type8 par8, Type9 par9, Type10 par10, Type11 par11)
{
	const char* formatStrs[12] = {GetPrintfFormatCStrOf(par1), GetPrintfFormatCStrOf(par2), GetPrintfFormatCStrOf(par3), GetPrintfFormatCStrOf(par4), GetPrintfFormatCStrOf(par5), GetPrintfFormatCStrOf(par6), GetPrintfFormatCStrOf(par7), GetPrintfFormatCStrOf(par8), GetPrintfFormatCStrOf(par9), GetPrintfFormatCStrOf(par10), GetPrintfFormatCStrOf(par11), nullptr};
	return checkedsnprintf (FormatCStrFullCheck, buffer, bufferSize, format, formatStrs, par1, par2, par3, par4, par5, par6, par7, par8, par9, par10, par11);
}

template<class Type1, class Type2, class Type3, class Type4, class Type5, class Type6, class Type7, class Type8, class Type9, class Type10, class Type11, class Type12>
inline int	csnprintf (char* buffer, size_t bufferSize, const char* format, Type1 par1, Type2 par2, Type3 par3, Type4 par4, Type5 par5, Type6 par6, Type7 par7, Type8 par8, Type9 par9, Type10 par10, Type11 par11, Type12 par12)
{
	const char* formatStrs[13] = {GetPrintfFormatCStrOf(par1), GetPrintfFormatCStrOf(par2), GetPrintfFormatCStrOf(par3), GetPrintfFormatCStrOf(par4), GetPrintfFormatCStrOf(par5), GetPrintfFormatCStrOf(par6), GetPrintfFormatCStrOf(par7), GetPrintfFormatCStrOf(par8), GetPrintfFormatCStrOf(par9), GetPrintfFormatCStrOf(par10), GetPrintfFormatCStrOf(par11), GetPrintfFormatCStrOf(par12), nullptr};
	return checkedsnprintf (FormatCStrFullCheck, buffer, bufferSize, format, formatStrs, par1, par2, par3, par4, par5, par6, par7, par8, par9, par10, par11, par12);
}

enum ToValueMode { Strict, NotStrict };
enum TrimWSMode { TrimWhiteSpaces, DontTrimWhiteSpaces };

GSROOT_DLL_EXPORT bool	strtovalue(const char* str, Int16& value, GS::ToValueMode strict = GS::NotStrict, GS::TrimWSMode trim = GS::TrimWhiteSpaces);
GSROOT_DLL_EXPORT bool	valuetostr(Int16 value, char* buffer, size_t bufferSize);

GSROOT_DLL_EXPORT bool	strtovalue(const char* str, UInt16& value, GS::ToValueMode strict = GS::NotStrict, GS::TrimWSMode trim = GS::TrimWhiteSpaces);
GSROOT_DLL_EXPORT bool	valuetostr(UInt16 value, char* buffer, size_t bufferSize);

GSROOT_DLL_EXPORT bool	strtovalue(const char* str, Int32& value, GS::ToValueMode strict = GS::NotStrict, GS::TrimWSMode trim = GS::TrimWhiteSpaces);
GSROOT_DLL_EXPORT bool	valuetostr(Int32 value, char* buffer, size_t bufferSize);

GSROOT_DLL_EXPORT bool	strtovalue(const char* str, UInt32& value, GS::ToValueMode strict = GS::NotStrict, GS::TrimWSMode trim = GS::TrimWhiteSpaces);
GSROOT_DLL_EXPORT bool	valuetostr(UInt32 value, char* buffer, size_t bufferSize);

GSROOT_DLL_EXPORT bool	strtovalue(const char* str, Int64& value, GS::ToValueMode strict = GS::NotStrict, GS::TrimWSMode trim = GS::TrimWhiteSpaces);
GSROOT_DLL_EXPORT bool	valuetostr(Int64 value, char* buffer, size_t bufferSize);

GSROOT_DLL_EXPORT bool	strtovalue(const char* str, UInt64& value, GS::ToValueMode strict = GS::NotStrict, GS::TrimWSMode trim = GS::TrimWhiteSpaces);
GSROOT_DLL_EXPORT bool	valuetostr(UInt64 value, char* buffer, size_t bufferSize);

GSROOT_DLL_EXPORT bool	strtovalue(const char* str, float& value, GS::ToValueMode strict = GS::NotStrict, GS::TrimWSMode trim = GS::TrimWhiteSpaces);
GSROOT_DLL_EXPORT bool	valuetostr(float value, char* buffer, size_t bufferSize);

GSROOT_DLL_EXPORT bool	strtovalue(const char* str, double& value, GS::ToValueMode strict = GS::NotStrict, GS::TrimWSMode trim = GS::TrimWhiteSpaces);
GSROOT_DLL_EXPORT bool	valuetostr(double value, char* buffer, size_t bufferSize);

#if defined (GS_64BIT)
 GSROOT_DLL_EXPORT bool	strtovalue(const char* str, long& value, GS::ToValueMode strict = GS::NotStrict, GS::TrimWSMode trim = GS::TrimWhiteSpaces);
 GSROOT_DLL_EXPORT bool	valuetostr(long value, char* buffer, size_t bufferSize);

 GSROOT_DLL_EXPORT bool	strtovalue(const char* str, unsigned long& value, GS::ToValueMode strict = GS::NotStrict, GS::TrimWSMode trim = GS::TrimWhiteSpaces);
 GSROOT_DLL_EXPORT bool	valuetostr(unsigned long value, char* buffer, size_t bufferSize);
#else
 GSROOT_DLL_EXPORT bool	strtovalue(const char* str, int& value, GS::ToValueMode strict = GS::NotStrict, GS::TrimWSMode trim = GS::TrimWhiteSpaces);
 GSROOT_DLL_EXPORT bool	valuetostr(int value, char* buffer, size_t bufferSize);

 GSROOT_DLL_EXPORT bool	strtovalue(const char* str, unsigned int& value, GS::ToValueMode strict = GS::NotStrict, GS::TrimWSMode trim = GS::TrimWhiteSpaces);
 GSROOT_DLL_EXPORT bool	valuetostr(unsigned int value, char* buffer, size_t bufferSize);
#endif

}

#define	CHCOPYARRAY(source, array)		{ BNZeroMemory (array, sizeof (array)) ; CHTruncate (source, array, sizeof (array)); }
#define	IVPCHARARRAY(inplatform, array)                         IVChars (inplatform, array, sizeof (array))
#define	IVP2CHARARRAY(inplatform, toplatform, array)			IVChars (inplatform,  array, sizeof (array), CC_Default, toplatform)


class GSROOT_DLL_EXPORT DefaultCharCodeGuard {
	GSCharCode savedDefaultCharCode;
public:
	DefaultCharCodeGuard (void);
	DefaultCharCodeGuard (GSCharCode toCharcode);
	~DefaultCharCodeGuard ();
};

#endif
