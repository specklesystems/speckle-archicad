// *****************************************************************************
//
// Contact person: MB, BIA, PR
//
// *****************************************************************************

#ifndef GSASSERT_CORE_HPP
#define GSASSERT_CORE_HPP

#include "Definitions.hpp"
#include "GSRootExport.hpp"


#ifndef GS_CLANG_ANALYZER_NORETURN
	#ifdef __clang__
		#if __has_feature (attribute_analyzer_noreturn)
			#define GS_CLANG_ANALYZER_NORETURN __attribute__((analyzer_noreturn))
		#else
			#define GS_CLANG_ANALYZER_NORETURN
		#endif
	#else
		#define GS_CLANG_ANALYZER_NORETURN
	#endif
#endif


// === PRECOND/GSASSERT ================================================================================================

// For details when GSASSERT and PRECOND terminates the program see the docs in Confluence.
// For an average developer: DEV => no termination, TST and FIN => termination.
// Example usages:
// GSASSERT (value == 5);					=> Asserts if value not equals 5.
// PRECOND (value == 5, Subject (value));	=> Asserts if value not equals 5 and write details about value.
// 
// You can test PRECOND failure with GS::TestSupport::ThrowOnPrecondViolationScope.
// GSASSERT cannot be tested as it is an internal detail of a function.
//
// Get the info from the log:
// ConvertLog -meta GSASSERT Path/To/Log/File.log
// ConvertLog -meta PRECOND Path/To/Log/File.log


#define GSASSERT(expr, ...)			if ((expr) == false) { ::GS::AssertImpl::AssertFailed ({ __FILE__, __FUNCTION__, __LINE__ }, ::GS::AssertImpl::GetAssertData (), #expr, ##__VA_ARGS__); }
#define GSASSERT_DB(expr, ...)		if ((expr) == false) { ::GS::AssertImpl::AssertFailed ({ __FILE__, __FUNCTION__, __LINE__ }, ::GS::AssertImpl::GetAssertData (), #expr, ##__VA_ARGS__); }
#define GSASSERT_FAILED(msg, ...)	::GS::AssertImpl::AssertFailed ({ __FILE__, __FUNCTION__, __LINE__ }, ::GS::AssertImpl::GetAssertData (), msg, ##__VA_ARGS__);

#define GSASSERT_T(expr, ...)		if ((expr) == false) { ::GS::AssertImpl::AssertFailedT ({ __FILE__, __FUNCTION__, __LINE__ }, ::GS::AssertImpl::GetAssertDataT (), #expr, ##__VA_ARGS__); }
#define GSASSERT_FAILED_T(msg, ...)	::GS::AssertImpl::AssertFailedT ({ __FILE__, __FUNCTION__, __LINE__ }, ::GS::AssertImpl::GetAssertDataT (), msg, ##__VA_ARGS__);

#define PRECOND(expr, ...)		if ((expr) == false) { ::GS::AssertImpl::AssertFailed ({ __FILE__, __FUNCTION__, __LINE__ }, ::GS::AssertImpl::GetPrecondData (), #expr, ##__VA_ARGS__); }
#define PRECOND_DB(expr, ...)	if ((expr) == false) { ::GS::AssertImpl::AssertFailed ({ __FILE__, __FUNCTION__, __LINE__ }, ::GS::AssertImpl::GetPrecondData (), #expr, ##__VA_ARGS__); }

#define PRECOND_T(expr, ...)	if ((expr) == false) { ::GS::AssertImpl::AssertFailedT ({ __FILE__, __FUNCTION__, __LINE__ }, ::GS::AssertImpl::GetPrecondDataT (), #expr, ##__VA_ARGS__); }


#ifndef CHECKED_VERSION
	#undef GSASSERT_DB
	#define GSASSERT_DB(expr, ...)
	#undef PRECOND_DB
	#define PRECOND_DB(expr, ...)
#endif


/* ================================================================================================================== */


namespace GS {


// TODO C++20: Replace this with std::source_location.
struct SourceLocation {
	const char* file;
	const char* function;
	UInt32		line;
};


} // namespace GS


namespace GS::AssertImpl {


struct AssertData;


GSROOT_DLL_EXPORT const AssertData& GetAssertData () noexcept;
GSROOT_DLL_EXPORT const AssertData& GetAssertDataT () noexcept;
GSROOT_DLL_EXPORT const AssertData& GetPrecondData () noexcept;
GSROOT_DLL_EXPORT const AssertData& GetPrecondDataT () noexcept;


GSROOT_DLL_EXPORT void AssertFailed (const SourceLocation&, const AssertData&, const char* expr) GS_CLANG_ANALYZER_NORETURN;

GSROOT_DLL_EXPORT void AssertFailedT [[noreturn]] (const SourceLocation&, const AssertData&, const char* expr);


} // namespace GS::AssertImpl


#endif /* GSASSERT_CORE_HPP */
