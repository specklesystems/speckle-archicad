// *****************************************************************************
//
// Contact person: MB, BIA, PR
//
// *****************************************************************************

#ifndef GS_WARNING_HPP
#define GS_WARNING_HPP

#include "Definitions.hpp"
#include "SourceLocation.hpp"
#include "Subject.hpp"


namespace GS { class Guid; }


// === GSWARNING =======================================================================================================

// Example usages:
// GSWARNING (err == NoError);						=> Warn if err not equals NoError.
// GSWARNING (err == NoError, Subject (value));		=> Warn if err not equals NoError and write details about value.
//
// Get the info from the log:
// ConvertLog -meta GSWARNING Path/To/Log/File.log


#define GSWARNING(expr, ...)		(((expr) == false) ? (::GS::WarningImpl::DoWarning ({ __FILE__, __FUNCTION__, __LINE__ }, #expr,  ##__VA_ARGS__), false) : true)


// === GSWARNING_RET ===================================================================================================

// Example usages:
// GSWARNING_RET (err == NoError, -1);						=> Warn if err not equals NoError and return from the function with -1.
// GSWARNING_RET (err == NoError, Subject (value), -1);		=> Warn if err not equals NoError, write details about value and return from the function with -1.
//
// Get the info from the log:
// ConvertLog -meta GSWARNING Path/To/Log/File.log


#define GSWARNINGIMPL_EXPAND(x) x
#define GSWARNINGIMPL_GETMACRO(_1, _2, _3, NAME, ...) NAME

#define GSWARNING_RET(...) \
	GSWARNINGIMPL_EXPAND (GSWARNINGIMPL_GETMACRO (__VA_ARGS__, GSWARNING_RETIMPL2, GSWARNING_RETIMPL1) (__VA_ARGS__))

#define GSWARNING_RETIMPL1(expr, ret)				if ((expr) == false) [[unlikely]] { ::GS::WarningImpl::DoWarning ({ __FILE__, __FUNCTION__, __LINE__ }, #expr); return ret; }
#define GSWARNING_RETIMPL2(expr, subjects, ret)		if ((expr) == false) [[unlikely]] { ::GS::WarningImpl::DoWarning ({ __FILE__, __FUNCTION__, __LINE__ }, #expr, subjects); return ret; }


// === GSWARNING_GUID ==================================================================================================

// For testing use GS::TestSupport::ExpectedWarningScope with the guid. Example usages:
// GSWARNING_GUID (err == NoError, "AB-CD-EF-GH");												=> Warn if err not equals NoError.
// GSWARNING_GUID (err == NoError, "AB-CD-EF-GH", Subject (value));								=> Warn if err not equals NoError, write details about value.
//
// Get the info from the log:
// ConvertLog -meta GSWARNING Path/To/Log/File.log


#define GSWARNING_GUID(expr, guid, ...)		(((expr) == false) ? (::GS::WarningImpl::DoWarning ({ __FILE__, __FUNCTION__, __LINE__ }, #expr, guid, ##__VA_ARGS__), false) : true)


// === GSWARNING_GUID_RET ==============================================================================================

// For testing use GS::TestSupport::ExpectedWarningScope with the guid. Example usages:
// GSWARNING_GUID_RET (err == NoError, "AB-CD-EF-GH", -1);						=> Warn if err not equals NoError and return from the function with -1.
// GSWARNING_GUID_RET (err == NoError, "AB-CD-EF-GH", Subject (value), -1);		=> Warn if err not equals NoError, write details about value and return from the function with -1.
//
// Get the info from the log:
// ConvertLog -meta GSWARNING Path/To/Log/File.log


#define GSWARNINGGUIDIMPL_GETMACRO(_1, _2, _3, _4, NAME, ...) NAME

#define GSWARNINGGUID_RET(...) \
	GSWARNINGIMPL_EXPAND (GSWARNINGGUIDIMPL_GETMACRO (__VA_ARGS__, GSWARNINGGUID_RETIMPL2, GSWARNINGGUID_RETIMPL1) (__VA_ARGS__))

#define GSWARNINGGUID_RETIMPL1(expr, guid, ret)				if ((expr) == false) [[unlikely]] { ::GS::WarningImpl::DoWarning ({ __FILE__, __FUNCTION__, __LINE__ }, #expr, guid); return ret; }
#define GSWARNINGGUID_RETIMPL2(expr, guid, subjects, ret)	if ((expr) == false) [[unlikely]] { ::GS::WarningImpl::DoWarning ({ __FILE__, __FUNCTION__, __LINE__ }, #expr, guid, subjects); return ret; }


// === GSWARNING_ONERR =================================================================================================

// For testing use GS::TestSupport::ExpectedWarningScope with the guid. Example usages:
// GSWARNING_ONERR (ic.Read (value));					=> Warn if the return value of 'ic.Read (value)' not equals NoError, and if not, return from the function with that value.
// GSWARNING_ONERR (ic.Read (value), "AB-CD-EF-GH");	=> Does the same as above.
//
// Get the info from the log:
// ConvertLog -meta GSWARNING Path/To/Log/File.log

#define GSWARNINGONERRIMPL_GETMACRO(_1, _2, NAME, ...) NAME

#define GSWARNING_ONERR(...) \
	GSWARNINGIMPL_EXPAND (GSWARNINGONERRIMPL_GETMACRO (__VA_ARGS__, GSWARNINGONERRIMPL2, GSWARNINGONERRIMPL1) (__VA_ARGS__))


#define GSWARNINGONERRIMPL1(expr)													\
	if (auto result = expr; result != ::GS::NoError) [[unlikely]] {					\
		::GS::WarningImpl::DoWarning ({ __FILE__, __FUNCTION__, __LINE__ }, #expr);	\
		return result;																\
	}

#define GSWARNINGONERRIMPL2(expr, guid)														\
	if (auto result = expr; result != ::GS::NoError) [[unlikely]] {							\
		::GS::WarningImpl::DoWarning ({ __FILE__, __FUNCTION__, __LINE__ }, #expr, guid);	\
		return result;																		\
	}


// === GSWARNING_FAILED ================================================================================================

// Example usage:
// GSWARNING_FAILED ("Something happened.");
//
// Get the info from the log:
// ConvertLog -meta GSWARNING Path/To/Log/File.log


#define GSWARNING_FAILED(msg) ::GS::WarningImpl::DoWarning ({ __FILE__, __FUNCTION__, __LINE__ }, msg);


/* ================================================================================================================== */


namespace GS::WarningImpl {


GSROOT_DLL_EXPORT
void	DoWarning (const SourceLocation&, const char* expr);

GSROOT_DLL_EXPORT
void	DoWarning (const SourceLocation&, const char* expr, FunctionRef<void(std::ostream&)>);

template<typename... Ts>
void	DoWarning (const SourceLocation& loc, const char* expr, const std::tuple<Ts...>& subjects)
{
	DoWarning (loc, expr, [&] (std::ostream& os) {
		::GS::PrintSubjects (os, subjects, std::make_index_sequence<sizeof... (Ts)> {});
	});
}

GSROOT_DLL_EXPORT
void	DoWarning (const SourceLocation&, const char* expr, const char* guid);

GSROOT_DLL_EXPORT
void	DoWarning (const SourceLocation&, const char* expr, const char* guid, FunctionRef<void(std::ostream&)>);

template<typename... Ts>
void	DoWarning (const SourceLocation& loc, const char* expr, const char* guid, const std::tuple<Ts...>& subjects)
{
	DoWarning (loc, expr, guid, [&] (std::ostream& os) {
		::GS::PrintSubjects (os, subjects, std::make_index_sequence<sizeof... (Ts)> {});
	});
}

GSROOT_DLL_EXPORT
void	DoWarning (const SourceLocation&, const char* expr, Guid guid);


GSROOT_DLL_EXPORT
void	DoWarning (const SourceLocation&, const char* expr, Guid guid, FunctionRef<void(std::ostream&)>);

template<typename... Ts>
void	DoWarning (const SourceLocation& loc, const char* expr, Guid guid, const std::tuple<Ts...>& subjects)
{
	DoWarning (loc, expr, guid, [&] (std::ostream& os) {
		::GS::PrintSubjects (os, subjects, std::make_index_sequence<sizeof... (Ts)> {});
	});
}


} // namespace GS::WarningImpl


#endif /* GS_WARNING_HPP */
