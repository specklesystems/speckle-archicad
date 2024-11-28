// *********************************************************************************************************************
// Description:		GRAPHISOFT Debug Manager
//
// Module:			GSRoot
// Namespace:		-
// Contact person:	MM
//
// SG compatible
// *********************************************************************************************************************

#ifndef	GSDEBUG_HPP
#define	GSDEBUG_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

#include	"Definitions.hpp"
#include	"TypeTraits.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace GS {

	class OProtocol;
	class OChannel;
	class XMLOChannel;

	class String;
	class UniString;
}

// --- DEBUG flag categories -------------------------------------------------------------------------------------------

enum DebugFlagCategories {
	DBGeneral	= 0,
	DBMemory	= 1,
	DBEncoding	= 2
};

enum GeneralFlags {
	DBEnableLogFile				= 0x00000004,
	DBEnableTrace				= 0x00000008,
	DBEnableLoadTrace			= 0x00000010,
	DBDisableAssertMessage		= 0x00000020,
	DBDisableAssertLog			= 0x00000040,
	DBEnableDiagnosticLogFiles	= 0x00000080,
	DBEnableWriteCallstack		= 0x00000100
};

enum MemoryFlags {
	DBEnableHeapCheck			= 0x00000001,
	DBEnableBMTrace				= 0x00000002,
	DBEnableAllocTrace			= 0x00000004
};

enum EncodingFlags {
	DBUtf8Encoding				= 0x00000001
};

// --- Constants -------------------------------------------------------------------------------------------------------

// Most functions operating on strings are using an internal buffer in GSDebug (because of technical reasons). This is
//   the limit. If you need to pass strings bigger than this, split the string, if you can.
constexpr USize DBMaxStringLength = 8192;

// --- DebugManager interface ------------------------------------------------------------------------------------------

typedef	void STDCALL	DBMessageProc (const char* cString);

EXTERNC GSROOT_DLL_EXPORT GS::OChannel&		dbChannel;
EXTERNC GSROOT_DLL_EXPORT GS::XMLOChannel&	dbXMLChannel;


// --- Debug functions -------------------------------------------------------------------------------------------------


#ifndef CLANG_ANALYZER_NORETURN
#if defined(__clang_analyzer__)
#if __has_feature(attribute_analyzer_noreturn)
#define CLANG_ANALYZER_NORETURN __attribute__((analyzer_noreturn))
#else
#define CLANG_ANALYZER_NORETURN
#endif
#else
#define CLANG_ANALYZER_NORETURN
#endif
#endif


GSROOT_DLL_EXPORT bool				DBInit ();
GSROOT_DLL_EXPORT bool				DBTerminate ();

GSROOT_DLL_EXPORT void				DBSetMessageProc (DBMessageProc* pMessageProc);
GSROOT_DLL_EXPORT void CCALL		DBPrint (const char* string);	// DBMaxStringLength limitation does not apply here
GSROOT_DLL_EXPORT void CCALL		DBPrintf (const char* format, ...);
GSROOT_DLL_EXPORT void CCALL		DBVPrintf (const char* format, va_list argList);
GSROOT_DLL_EXPORT void CCALL		DBPrintf (const GS::Utf16Char* format, ...);
GSROOT_DLL_EXPORT void CCALL		DBPrintWithThreadId (const char* pString);
GSROOT_DLL_EXPORT void				DBPrintStack (GS::OChannel& oChannel = dbChannel);
GSROOT_DLL_EXPORT void				DBTrace (const char *fileName, UInt32 lineCount, const char* pMessage = nullptr);
GSROOT_DLL_EXPORT void				DBPrintMemBlockInfo (void* pMemBlock);

GSROOT_DLL_EXPORT bool				DBGetDiagnosticLogFilesLocation (GS::Utf8Char* pPathOut, USize pathNChar);

GSROOT_DLL_EXPORT bool				WasUnexpectedAssertFailure (void);
GSROOT_DLL_EXPORT void				ClearUnexpectedAssertFailure (void);

GSROOT_DLL_EXPORT UInt32		GetFirstUnexpectedAssertLineCount    ();
GSROOT_DLL_EXPORT GS::String	GetFirstUnexpectedAssertFilename     ();
GSROOT_DLL_EXPORT GS::String	GetFirstUnexpectedAssertFunctionName ();
GSROOT_DLL_EXPORT GS::String	GetFirstUnexpectedAssertReason	     ();
GSROOT_DLL_EXPORT GS::String	GetFirstUnexpectedAssertMessage	     ();
GSROOT_DLL_EXPORT GS::UniString GetFirstUnexpectedAssertCallStack    ();

GSROOT_DLL_EXPORT bool			DBBreak (const char *fileName, UInt32 lineCount, const char* pMessage = nullptr, const char* reason = nullptr, const char* function = nullptr, const char* assertGuidString = nullptr) CLANG_ANALYZER_NORETURN;
#ifdef WINDOWS
GSROOT_DLL_EXPORT bool			DBBreak (const char *fileName, UInt32 lineCount, const wchar_t* pMessage, const wchar_t* reason = nullptr, const char* function = nullptr, const char* assertGuidString = nullptr);
#endif // WINDOWS

GSROOT_DLL_EXPORT GSFlags		DBGetFlags (DebugFlagCategories flagCategory);
GSROOT_DLL_EXPORT void			DBSetFlags (DebugFlagCategories flagCategory, GSFlags flags);

GSROOT_DLL_EXPORT bool			DBIsFlagSet (DebugFlagCategories flagCategory, GSFlags flag);
GSROOT_DLL_EXPORT bool			DBIsFlagClear (DebugFlagCategories flagCategory, GSFlags flag);
GSROOT_DLL_EXPORT void			DBSetFlag (DebugFlagCategories flagCategory, GSFlags flag);
GSROOT_DLL_EXPORT void			DBClearFlag (DebugFlagCategories flagCategory, GSFlags flag);

GSROOT_DLL_EXPORT bool			DBGetBool (const char* keyPath, const char* valueName, bool defaultValue = false);
GSROOT_DLL_EXPORT Int32			DBGetLong (const char* keyPath, const char* valueName, Int32 defaultValue = 0);
GSROOT_DLL_EXPORT void			DBGetString (const char* keyPath, const char* valueName, char* pPuffer, UInt32 pufferSize, const char* defaultValue = nullptr);
GSROOT_DLL_EXPORT void			DBSetBool (const char* keyPath, const char* valueName, bool newValue);
GSROOT_DLL_EXPORT void			DBSetLong (const char* keyPath, const char* valueName, Int32 newValue);
GSROOT_DLL_EXPORT void			DBSetString (const char* keyPath, const char* valueName, const char* newValue);


// --- Utility classes for debugging memory problems  ------------------------------------------------------------------

class DBMemTester {
	GSFlags memFlags;
public:
	explicit DBMemTester (bool on = true) : memFlags (DBGetFlags (DBMemory)) {
		DBSetFlags (DBMemory, on ? memFlags | DBEnableHeapCheck : memFlags & ~DBEnableHeapCheck);
	}
	~DBMemTester () {
		DBSetFlags (DBMemory, memFlags);
	}
};

class DBAllocTracer {
	GSFlags memFlags;
public:
	explicit DBAllocTracer (bool on = true) : memFlags (DBGetFlags (DBMemory)) {
		DBSetFlags (DBMemory, on ? memFlags | DBEnableAllocTrace : memFlags & ~DBEnableAllocTrace);
	}
	~DBAllocTracer () {
		DBSetFlags (DBMemory, memFlags);
	}
};

class GSROOT_DLL_EXPORT DBStackMaxDepthBlock {
#if defined (WINDOWS) && defined (DEBUVERS) && defined (HEAP_DEBUG)
	UInt16 oldStackMaxDepth;
#endif

public:
	explicit DBStackMaxDepthBlock (UInt16 newStackMaxDepth);
	~DBStackMaxDepthBlock ();
};

// --- DEBUVERS / TEST_VERSION dependent macros ------------------------------------------------------------------------

#ifdef CHECKED_VERSION
#define	ASSERT_SIZE(typeName, typeSize)	static char typeName##SizeCheck[(sizeof (typeName) == typeSize) ? 1 : -1] GCC_UNUSED;
#if defined (WINDOWS)
#define	PRINT_SIZE(TypeName)\
	struct	TypeName##Print {\
		TypeName##Print () { char puffer [256] ; sprintf (puffer, "sizeof (" #TypeName ") = %d\n", sizeof (TypeName)); OutputDebugStringA (puffer);}\
	};\
	static	TypeName##Print a##TypeName##Print;
#else
	// should be __GNUC__ ...
#define	PRINT_SIZE(TypeName)\
	struct	TypeName##Print {\
		TypeName##Print () { fprintf (stderr, "sizeof (" #TypeName ") = %d\n", sizeof (TypeName)); }\
	};\
	static	TypeName##Print a##TypeName##Print __attribute__((unused));
#endif
#else
#define	ASSERT_SIZE(typeName, typeSize)
#define	PRINT_SIZE(TypeName)
#endif



#ifdef CHECKED_VERSION

	#define	DBPRINTF					DBPrintf
	#define	DBTRACE(pStr)				DBTrace (__FILE__, __LINE__, pStr)
	#define	DBGETFLAGS(c)				DBGetFlags (c)
	#define	DBSETFLAGS(c, b)			DBSetFlags (c, b)

	#define	DBBREAK()					DBBreak (__FILE__, __LINE__, (const char*)nullptr,	nullptr, __FUNCTION__, nullptr)
	#define	DBBREAK_STR(s)				DBBreak (__FILE__, __LINE__, s,			nullptr, __FUNCTION__, nullptr)

	#define	DBBREAK_GUID(g)				DBBreak (__FILE__, __LINE__, (const char*)nullptr,	nullptr, __FUNCTION__, g)
	#define	DBBREAK_STR_GUID(s, g)		DBBreak (__FILE__, __LINE__, s,			nullptr, __FUNCTION__, g)

	#define	DBASSERT(b)					if (!(b))	DBBreak (__FILE__, __LINE__, nullptr,	#b " is false",		__FUNCTION__, nullptr)
	#define	DBERROR(b)					( (b) ?		DBBreak (__FILE__, __LINE__, nullptr,	#b,					__FUNCTION__, nullptr)		: false)
	#define	DBVERIFY(b)					(!(b) ? !	DBBreak (__FILE__, __LINE__, nullptr,	#b " is false",		__FUNCTION__, nullptr)		: true)

	#define	DBASSERT_STR(b, s)			if (!(b))	DBBreak (__FILE__, __LINE__, s,		#b " is false",		__FUNCTION__, nullptr)
	#define	DBERROR_STR(b, s)			( (b) ?		DBBreak (__FILE__, __LINE__, s,		#b,					__FUNCTION__, nullptr)		: false)
	#define	DBVERIFY_STR(b, s)			(!(b) ? !	DBBreak (__FILE__, __LINE__, s,		#b " is false",		__FUNCTION__, nullptr)		: true)

	#define DBASSERT_GUID(b, g)			if (!(b))	DBBreak (__FILE__, __LINE__, nullptr,	#b " is false",		__FUNCTION__, g)
	#define	DBERROR_GUID(b, g)			( (b) ?		DBBreak (__FILE__, __LINE__, nullptr,	#b,					__FUNCTION__, g)		: false)
	#define	DBVERIFY_GUID(b, g)			(!(b) ? !	DBBreak (__FILE__, __LINE__, nullptr,	#b " is false",		__FUNCTION__, g)		: true)

	#define DBASSERT_STR_GUID(b, s, g)	if (!(b))	DBBreak (__FILE__, __LINE__, s,		#b " is false",		__FUNCTION__, g)
	#define	DBERROR_STR_GUID(b, s, g)	( (b) ?		DBBreak (__FILE__, __LINE__, s,		#b,					__FUNCTION__, g)		: false)
	#define	DBVERIFY_STR_GUID(b, s, g)	(!(b) ? !	DBBreak (__FILE__, __LINE__, s,		#b " is false",		__FUNCTION__, g)		: true)

	#define GCC_UNUSED_FINAL

#else	/* NOT DEBUVERS AND NOT TEST_VERSION*/

	#define	DBPRINTF(fmt,...)
	#define	DBTRACE(pStr)
	#define	DBGETFLAGS(c)				(0)
	#define	DBSETFLAGS(c, b)

	#define	DBBREAK()
	#define	DBASSERT(b)
	#define	DBERROR(b)					(b)
	#define	DBVERIFY(b)					(b)

	#define	DBBREAK_STR(s)
	#define	DBASSERT_STR(b, s)
	#define	DBERROR_STR(b, s)			(b)
	#define	DBVERIFY_STR(b, s)			(b)

	#define DBBREAK_GUID(g)
	#define DBASSERT_GUID(b, g)
	#define DBERROR_GUID(b, g)			(b)
	#define DBVERIFY_GUID(b, g)			(b)

	#define DBBREAK_STR_GUID(s, g)
	#define DBASSERT_STR_GUID(b, s, g)
	#define DBERROR_STR_GUID(b, s, g)	(b)
	#define DBVERIFY_STR_GUID(b, s, g)	(b)

	#define GCC_UNUSED_FINAL	GCC_UNUSED

#endif

template<class Type>
inline Type* DBASSERTPTR (Type* ptr) {
	DBASSERT (ptr != nullptr);
	return ptr;
}
template<class Type>
inline const Type* DBASSERTPTR (const Type* ptr) {
	DBASSERT (ptr != nullptr);
	return ptr;
}


GSROOT_DLL_EXPORT void DBNewFailedGUIDAssertCounter		(const char* assertGUIDString, Int32 nAsserts);
GSROOT_DLL_EXPORT void DBNewFailedGUIDAssertCounter		(const char* assertGUIDString, Int32 nMinAsserts, Int32 nMaxAsserts);
GSROOT_DLL_EXPORT void DBDeleteFailedGUIDAssertCounter	(const char* assertGUIDString);

class GSROOT_DLL_EXPORT DBFailedGUIDAssertCounterGuard {
private:
	char* idStr;
public:
	DBFailedGUIDAssertCounterGuard (const char* assertGUIDString, Int32 nAsserts);
	DBFailedGUIDAssertCounterGuard (const char* assertGUIDString, Int32 nMinAsserts, Int32 nMaxAsserts);
	~DBFailedGUIDAssertCounterGuard ();
private:
	DBFailedGUIDAssertCounterGuard (const DBFailedGUIDAssertCounterGuard& source);				// disable
	DBFailedGUIDAssertCounterGuard& operator= (const DBFailedGUIDAssertCounterGuard& source);	// disable
};

#define _LINENAME_CAT(name, line) name##line
#define _LINENAME(name, line) _LINENAME_CAT(name, line)
#define LINENAME(name) _LINENAME(name, __LINE__)

#ifdef CHECKED_VERSION

	#define DB_NEW_FAILED_GUID_ASSERT_COUNTER(g, ...)				DBNewFailedGUIDAssertCounter (g, __VA_ARGS__)
	#define DB_DELETE_FAILED_GUID_ASSERT_COUNTER(g)					DBDeleteFailedGUIDAssertCounter (g)

	#define DB_FAILED_GUID_ASSERT_COUNTER_GUARD(g, ...)				DBFailedGUIDAssertCounterGuard LINENAME(guidAssertGuard)(g, __VA_ARGS__)
#else	/* NOT DEBUVERS AND NOT TEST_VERSION*/

	#define DB_NEW_FAILED_GUID_ASSERT_COUNTER(g, ...)
	#define DB_DELETE_FAILED_GUID_ASSERT_COUNTER(g)

	#define DB_FAILED_GUID_ASSERT_COUNTER_GUARD(g, ...)
#endif

#define ASSERT_NOTHROW					GS::NothrowGuard NA__guard (__FUNCTION__);
#define ASSERT_NOTHROW_N(location)		GS::NothrowGuard NA__guard (location);


namespace GS {


// === class NothrowGuard ==============================================================================================

class GSROOT_DLL_EXPORT NothrowGuard {
public:
	NothrowGuard (const char* location);
	~NothrowGuard ();

private:
	const char*	location;
	bool		in_exception;
};


// === AssertIsSame ====================================================================================================

namespace Imp {

template <class T1, class T2>
struct TestIsSame {
	static_assert (GS::IsSame<T1, T2>, "GS::AssertIsSame<T1, T2> failed.");

	static constexpr void*	Value = nullptr;
};

}


template <class T1, class T2>
constexpr void*  AssertIsSame = Imp::TestIsSame<T1, T2>::Value;


}	// namespace GS


#endif
