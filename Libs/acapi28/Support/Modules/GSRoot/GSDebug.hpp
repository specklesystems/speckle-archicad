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

#include "Definitions.hpp"
#include "TypeTraits.hpp"

// from Standard Library
#include <stdarg.h>
#include <iosfwd>

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
	DBMemory	= 1
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

// --- Constants -------------------------------------------------------------------------------------------------------

// Most functions operating on strings are using an internal buffer in GSDebug (because of technical reasons). This is
//   the limit. If you need to pass strings bigger than this, split the string, if you can.
constexpr USize DBMaxStringLength = 8192;

// --- DebugManager interface ------------------------------------------------------------------------------------------

typedef	void STDCALL	DBMessageProc (const char* cString);

extern GSROOT_DLL_EXPORT GS::OChannel&		dbChannel;
extern GSROOT_DLL_EXPORT GS::XMLOChannel&	dbXMLChannel;

namespace GS {

extern GSROOT_DLL_EXPORT std::ostream&		dbStream;

} // namespace GS

// --- Debug functions -------------------------------------------------------------------------------------------------


GSROOT_DLL_EXPORT bool				DBInit ();
GSROOT_DLL_EXPORT bool				DBTerminate ();

GSROOT_DLL_EXPORT void				DBSetMessageProc (DBMessageProc* pMessageProc);
GSROOT_DLL_EXPORT void CCALL		DBPrint (const char* string);	// DBMaxStringLength limitation does not apply here
GSROOT_DLL_EXPORT void CCALL		DBPrintf (const char* format, ...);
GSROOT_DLL_EXPORT void CCALL		DBVPrintf (const char* format, va_list argList);
GSROOT_DLL_EXPORT void CCALL		DBPrintf (const Utf16Char* format, ...);
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

GSROOT_DLL_EXPORT void			DBBreak (const char *fileName, UInt32 lineCount, const char* pMessage = nullptr, const char* reason = nullptr, const char* function = nullptr, const char* assertGuidString = nullptr);
#ifdef WINDOWS
GSROOT_DLL_EXPORT void			DBBreak (const char *fileName, UInt32 lineCount, const wchar_t* pMessage, const wchar_t* reason = nullptr, const char* function = nullptr, const char* assertGuidString = nullptr);
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

class GSROOT_DLL_EXPORT [[nodiscard]] DBStackMaxDepthBlock {
#if defined (WINDOWS) && defined (DEBUVERS) && defined (HEAP_DEBUG)
	UInt16 oldStackMaxDepth;
#endif

public:
	explicit DBStackMaxDepthBlock (UInt16 newStackMaxDepth);
	~DBStackMaxDepthBlock ();
};

// --- DEBUVERS / TEST_VERSION dependent macros ------------------------------------------------------------------------


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
	#define	DBERROR(b)					( (b) ?		(DBBreak (__FILE__, __LINE__, nullptr,	#b,					__FUNCTION__, nullptr), true)	: false)
	#define	DBVERIFY(b)					(!(b) ?		(DBBreak (__FILE__, __LINE__, nullptr,	#b " is false",		__FUNCTION__, nullptr), false)	: true)

	#define	DBASSERT_STR(b, s)			if (!(b))	DBBreak (__FILE__, __LINE__, s,			#b " is false",		__FUNCTION__, nullptr)
	#define	DBERROR_STR(b, s)			( (b) ?		(DBBreak (__FILE__, __LINE__, s,		#b,					__FUNCTION__, nullptr), true)	: false)
	#define	DBVERIFY_STR(b, s)			(!(b) ?		(DBBreak (__FILE__, __LINE__, s,		#b " is false",		__FUNCTION__, nullptr), false)	: true)

	#define DBASSERT_GUID(b, g)			if (!(b))	DBBreak (__FILE__, __LINE__, nullptr,	#b " is false",		__FUNCTION__, g)
	#define	DBERROR_GUID(b, g)			( (b) ?		(DBBreak (__FILE__, __LINE__, nullptr,	#b,					__FUNCTION__, g), true)		: false)
	#define	DBVERIFY_GUID(b, g)			(!(b) ?		(DBBreak (__FILE__, __LINE__, nullptr,	#b " is false",		__FUNCTION__, g), false)	: true)

	#define DBASSERT_STR_GUID(b, s, g)	if (!(b))	DBBreak (__FILE__, __LINE__, s,			#b " is false",		__FUNCTION__, g)
	#define	DBERROR_STR_GUID(b, s, g)	( (b) ?		(DBBreak (__FILE__, __LINE__, s,		#b,					__FUNCTION__, g), true)		: false)
	#define	DBVERIFY_STR_GUID(b, s, g)	(!(b) ?		(DBBreak (__FILE__, __LINE__, s,		#b " is false",		__FUNCTION__, g), false)	: true)

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
Type*	DBASSERTPTR (Type* ptr)
{
	DBASSERT (ptr != nullptr);
	return ptr;
}


GSROOT_DLL_EXPORT void DBNewFailedGUIDAssertCounter		(const char* assertGUIDString, Int32 nAsserts);
GSROOT_DLL_EXPORT void DBNewFailedGUIDAssertCounter		(const char* assertGUIDString, Int32 nMinAsserts, Int32 nMaxAsserts);
GSROOT_DLL_EXPORT void DBDeleteFailedGUIDAssertCounter	(const char* assertGUIDString);

class GSROOT_DLL_EXPORT [[nodiscard]] DBFailedGUIDAssertCounterGuard {
private:
	char* idStr;
public:
	DBFailedGUIDAssertCounterGuard (const char* assertGUIDString, Int32 nAsserts);
	DBFailedGUIDAssertCounterGuard (const char* assertGUIDString, Int32 nMinAsserts, Int32 nMaxAsserts);
	~DBFailedGUIDAssertCounterGuard ();
private:
	DBFailedGUIDAssertCounterGuard (const DBFailedGUIDAssertCounterGuard&)				= delete;
	DBFailedGUIDAssertCounterGuard& operator= (const DBFailedGUIDAssertCounterGuard&)	= delete;
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

class GSROOT_DLL_EXPORT [[nodiscard]] NothrowGuard {
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


// === Unreachable =====================================================================================================


GSROOT_DLL_EXPORT
void	Unreachable [[noreturn]] (void);


}	// namespace GS


#define ERRCHK(f)			{ const GSErrCode errCode = (f); if (DBERROR (errCode != NoError)) { return errCode; } }
#define ERRCHK_GUID(f, g)	{ const GSErrCode errCode = (f); if (DBERROR_GUID (errCode != NoError, (g))) { return errCode; } }
#define ERRCHK_NO_ASSERT(f)	{ const GSErrCode errCode = (f); if (errCode != NoError) { return errCode; } }


#endif
