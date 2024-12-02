// *********************************************************************************************************************
// Description:		GRAPHISOFT Resource Manager
//
// Namespaces:		-
// Contact persons:	MM
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (RS_HPP)
#define	RS_HPP

#pragma once

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace GS
{
	template <class Type> class Array;
	class String;
	class UniString;
}


// --- Includes	--------------------------------------------------------------------------------------------------------

// from GRoot
#include	"Definitions.hpp"
#include	"RSExport.hpp"

#if defined (WINDOWS)
#include	"Win32Interface.hpp"
#endif

#include	"RSTypes.hpp"

#if defined (WINDOWS)
typedef bool	(CCALL *EnumResTypesCallbackWin) (const WCHAR* resType, GSResModule resModule, void* userData);
typedef bool	(CCALL *EnumResIDsCallbackWin) (GSResID resID, const WCHAR* resType, GSResModule resModule, void* userData);
#endif

// =====================================================================================================================
// Manager identifier
// =====================================================================================================================

#define	IDRSManager		'RS01'

//------------------------- Special Windows Resources --------------------------

#if defined (WINDOWS)
// See definitions in WINUSER.H
extern const WCHAR*	RS_Accelerator;		// Accelerator table
extern const WCHAR*	RS_Anicursor;		// Animated cursor
extern const WCHAR*	RS_Aniicon;			// Animated icon
extern const WCHAR*	RS_Bitmap;			// Bitmap resource
extern const WCHAR*	RS_Cursor;			// Hardware-dependent cursor resource
extern const WCHAR*	RS_Dialog;			// Dialog box
extern const WCHAR*	RS_Font;			// Font resource
extern const WCHAR*	RS_Fontdir;			// Font directory resource
extern const WCHAR*	RS_Group_Cursor;	// Hardware-independent cursor resource
extern const WCHAR*	RS_Group_Icon;		// Hardware-independent icon resource
extern const WCHAR*	RS_HTML;			// HTML document
extern const WCHAR*	RS_Icon;			// Hardware-dependent icon resource
extern const WCHAR*	RS_Menu;			// Menu resource
extern const WCHAR*	RS_Messagetable;	// Message-table entry
extern const WCHAR*	RS_RCData;			// Application-defined resource (raw data)
extern const WCHAR*	RS_String;			// String-table entry
extern const WCHAR*	RS_Version;			// Version resource
#endif


// =====================================================================================================================
// Interface definition
// =====================================================================================================================

// checking and logging of resources and resource modules (D-076)

RS_DLL_EXPORT GSHandle	RSLoadResource_ParamAdapter (const char* fileName, UInt32 lineCount, GSResType resType, GSResModule resModule, GSResID resID);

#if defined (WINDOWS)
RS_DLL_EXPORT GSHandle	RSLoadResource_ParamAdapter (const char* fileName, UInt32 lineCount, const WCHAR* resType, GSResModule resModule, GSResID resID);
#endif

#define RSLoadResource(...)		  RSLoadResource_ParamAdapter (__FILE__, __LINE__, __VA_ARGS__)

#if defined (WINDOWS)
#define RSLoadResourceLengthPrefix(resType, resID, resModule)	RSLoadResourceLengthPrefixFunc (__FILE__, __LINE__, resType, resID, resModule)
#endif


RS_DLL_EXPORT bool				RSGetIndString_ParamAdapter (const char* fileName, UInt32 lineCount, char*          result, GSResID resID, Int32 index, GSResModule resModule, ResStringType rsType = RST_Localised);
RS_DLL_EXPORT bool				RSGetIndString_ParamAdapter (const char* fileName, UInt32 lineCount, GS::String*    result, GSResID resID, Int32 index, GSResModule resModule, ResStringType rsType = RST_Localised);
RS_DLL_EXPORT bool				RSGetIndString_ParamAdapter (const char* fileName, UInt32 lineCount, GS::UniString* result, GSResID resID, Int32 index, GSResModule resModule, ResStringType rsType = RST_Localised);
RS_DLL_EXPORT bool				RSGetIndString_ParamAdapter (const char* fileName, UInt32 lineCount, GS::Utf16Char* result, GSResID resID, Int32 index, GSResModule resModule, ResStringType rsType = RST_Localised);
RS_DLL_EXPORT GS::UniString		RSGetIndString_ParamAdapter (const char* fileName, UInt32 lineCount,                        GSResID resID, Int32 index, GSResModule resModule, ResStringType rsType = RST_Localised);

RS_DLL_EXPORT bool				RSGetStringList_ParamAdapter	(const char* fileName, UInt32 lineCount, GS::Array<GS::UniString>* results, GSResID resID, GSResModule resModule, ResStringType rsType = RST_Localised);

RS_DLL_EXPORT bool				RSGetText_ParamAdapter      (const char* fileName, UInt32 lineCount, GS::UniString* result, GSResID resID, GSResModule resModule);

#define RSGetIndString(...)			   RSGetIndString_ParamAdapter (__FILE__, __LINE__, __VA_ARGS__)
#define RSGetStringList(...)		   RSGetStringList_ParamAdapter (__FILE__, __LINE__, __VA_ARGS__)
#define RSGetText(...)				   RSGetText_ParamAdapter (__FILE__, __LINE__, __VA_ARGS__)


RS_DLL_EXPORT bool				RSInternalTest (void);
RS_DLL_EXPORT void				RSSetFlags (GSFlags flags);
RS_DLL_EXPORT GSFlags			RSGetFlags (void);

inline bool	RSMissingResourceAlert (bool enable)
{
	const GSFlags flags = RSGetFlags ();
	const bool wasSet = (flags & RSF_MissingResourceAlert) != 0;

	if (enable)	RSSetFlags (flags | RSF_MissingResourceAlert);
	else		RSSetFlags (flags & ~RSF_MissingResourceAlert);

	return wasSet;
}

inline void	RSSkipImageLoadingOnOpen (bool skip)
{
	if (skip)	RSSetFlags (RSGetFlags () | RSF_DontLoadImages);
	else		RSSetFlags (RSGetFlags () & ~RSF_DontLoadImages);
}

RS_DLL_EXPORT GSResModule		RSGetApplicationResModule (void);

RS_DLL_EXPORT GSResModule		RSInitModuleImageCache (GSResModule resModule);
RS_DLL_EXPORT void				RSRemoveModuleImageCache (GSResModule resModule);

RS_DLL_EXPORT bool				RSEqualResModules (GSResModule resModule1, GSResModule resModule2);
#if defined (WINDOWS)
RS_DLL_EXPORT GSResModule		RSOpenResourceFile (const WCHAR* pathName);
RS_DLL_EXPORT GSHandle			RSLoadResourceFunc (const char* fileName, UInt32 lineCount, GSResType resType, GSResID resID, GSResModule resModule);
RS_DLL_EXPORT GSHandle			RSLoadResourceFunc (const char* fileName, UInt32 lineCount, const WCHAR* resType, GSResID resID, GSResModule resModule);
RS_DLL_EXPORT GSHandle			RSLoadResourceLengthPrefixFunc (const char* fileName, UInt32 lineCount, const WCHAR* resType, GSResID resID, GSResModule resModule);
#endif
#if defined (macintosh)
RS_DLL_EXPORT GSHandle			RSLoadResourceFunc (const char* fileName, UInt32 lineCount, GSResType resType, GSResID resID, GSResModule resModule);
RS_DLL_EXPORT GSResModule		RSOpenResourceFile (const char* pathName);
#endif
#if defined (__linux__)
RS_DLL_EXPORT GSHandle			RSLoadResourceFunc (const char* fileName, UInt32 lineCount, GSResType resType, GSResID resID, GSResModule resModule);
#endif
RS_DLL_EXPORT void				RSCloseResourceFile (GSResModule resModule);

RS_DLL_EXPORT bool				RSGetIndStringFunc (const char* fileName, UInt32 lineCount, char* result, GSResID resID, Int32 index, GSResModule resModule, ResStringType rsType = RST_Localised);
RS_DLL_EXPORT bool				RSGetIndStringFunc (const char* fileName, UInt32 lineCount, GS::String* result, GSResID resID, Int32 index, GSResModule resModule, ResStringType rsType = RST_Localised);
RS_DLL_EXPORT bool				RSGetIndStringFunc (const char* fileName, UInt32 lineCount, GS::UniString* result, GSResID resID, Int32 index, GSResModule resModule, ResStringType rsType = RST_Localised);
RS_DLL_EXPORT bool				RSGetIndStringFunc (const char* fileName, UInt32 lineCount, GS::Utf16Char* result, GSResID resID, Int32 index, GSResModule resModule, ResStringType rsType = RST_Localised);

RS_DLL_EXPORT bool				RSGetStringListFunc (const char* fileName, UInt32 lineCount, GS::Array<GS::UniString>* results, GSResID resID, GSResModule resModule, ResStringType rsType = RST_Localised);

RS_DLL_EXPORT bool				RSGetTextFunc (const char* fileName, UInt32 lineCount, GS::UniString* result, GSResID resID, GSResModule resModule);

RS_DLL_EXPORT bool				RSEnumResourceTypes (EnumResTypesCallback callBack, void* userData, GSResModule resModule);
RS_DLL_EXPORT bool				RSEnumResourceIDs (EnumResIDsCallback callBack, void* userData, GSResType resType, GSResModule resModule);

#if defined (WINDOWS)
RS_DLL_EXPORT bool				RSEnumResourceTypes (EnumResTypesCallbackWin callBack, void* userData, GSResModule resModule);
RS_DLL_EXPORT bool				RSEnumResourceIDs (EnumResIDsCallbackWin callBack, void* userData, const WCHAR* resType, GSResModule resModule);
#endif
#if defined (macintosh)
RS_DLL_EXPORT CFStringRef		RSGetResModulePath (GSResModule resModule) __attribute__((cf_returns_retained));
RS_DLL_EXPORT CFURLRef			RSGetResModuleURL  (GSResModule resModule) __attribute__((cf_returns_retained));

RS_DLL_EXPORT USize				RSGetResourceSize  (GSResModule resModule, GSResType resType, GSResID resID);
#endif

// Mactel todo [

#if defined (macintosh)
const GS::PlatformSign RSResourceDataPlatfromSign = GS::Mac_Platform_Sign;
#else
const GS::PlatformSign RSResourceDataPlatfromSign = GS::Act_Platform_Sign;
#endif

Int32 			RS_DLL_EXPORT	RSSwapInt32ToHost (Int32 		   	value);
UInt32 			RS_DLL_EXPORT	RSSwapInt32ToHost (UInt32 			value);
short 			RS_DLL_EXPORT	RSSwapInt16ToHost (short 			value);
unsigned short 	RS_DLL_EXPORT	RSSwapInt16ToHost (unsigned short 	value);
// ] Mactel todo

#endif	// RS_HPP
