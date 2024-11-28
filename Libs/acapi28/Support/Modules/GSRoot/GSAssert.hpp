// *****************************************************************************
//
// Contact person: MB, BIA, PR
//
// *****************************************************************************

#ifndef GSASSERT_HPP
#define GSASSERT_HPP

#include "Definitions.hpp"
#include "FastLogger.hpp"
#include "FunctionRef.hpp"
#include "GSAssertCore.hpp"
#include "GSAssertDeprecated.hpp"
#include "String.hpp"

// from Standard Library
#include <functional>
#include <tuple>


namespace GS {
	class ErrorStatus;
	class EventReceiver;
	class Guid;
}


// === GSINSPECT =======================================================================================================

// Example usages:
// GSINSPECT (value == 5, "MySquad");					=> Inspect if value not equals 5.
// GSINSPECT (value == 5, "MySquad", Subject (value));	=> Inspect if value not equals 5 and write details about value.
//
// Get the info from the log:
// ConvertLog -owner MySquad Path/To/Log/File.log
// ConvertLog -meta GSINSPECT Path/To/Log/File.log


#define GSINSPECT(expr, owner, ...) \
	(((expr) == false) ? (::GS::AssertImpl::DoInspect ({ __FILE__, __FUNCTION__, __LINE__ }, #expr, owner, ##__VA_ARGS__), false) : true)


#ifdef GS_DEV
	#define GSINSPECT_DB(expr, owner, ...) GSINSPECT (expr, owner, ##__VA_ARGS__)
#else
	#define GSINSPECT_DB(expr, owner, ...)
#endif


// === GSWARNING =======================================================================================================

// Example usages:
// GSWARNING (err == NoError);		=> Warn if err not equals NoError.
// GSWARNING (err == NoError, -1);	=> Warn if err not equals NoError and return from the function with -1.
//
// Get the info from the log:
// ConvertLog -meta GSWARNING Path/To/Log/File.log


#define GSWARNINGIMPL_EXPAND(x) x
#define GSWARNINGIMPL_GETMACRO(_1, _2, NAME, ...) NAME

#define GSWARNING(...) \
	GSWARNINGIMPL_EXPAND (GSWARNINGIMPL_GETMACRO (__VA_ARGS__, GSWARNINGIMPL2, GSWARNINGIMPL1) (__VA_ARGS__))

#define GSWARNINGIMPL1(expr)		(((expr) == false) ? (::GS::AssertImpl::DoWarning ({ __FILE__, __FUNCTION__, __LINE__ }, #expr), false) : true)
#define GSWARNINGIMPL2(expr, ret)	if ((expr) == false) { ::GS::AssertImpl::DoWarning ({ __FILE__, __FUNCTION__, __LINE__ }, #expr); return ret; }


// === GSWARNING_GUID ==================================================================================================

// For testing use GS::TestSupport::ExpectedWarningScope with the guid. Example usages:
// GSWARNING_GUID (err == NoError, "AB-CD-EF-GH");		=> Warn if err not equals NoError.
// GSWARNING_GUID (err == NoError, "AB-CD-EF-GH", -1);	=> Warn if err not equals NoError and return from the function with -1.
//
// Get the info from the log:
// ConvertLog -meta GSWARNING Path/To/Log/File.log


#define GSWARNINGGUIDIMPL_GETMACRO(_1, _2, _3, NAME, ...) NAME

#define GSWARNING_GUID(...) \
	GSWARNINGIMPL_EXPAND (GSWARNINGGUIDIMPL_GETMACRO (__VA_ARGS__, GSWARNINGGUIDIMPL2, GSWARNINGGUIDIMPL1) (__VA_ARGS__))

#define GSWARNINGGUIDIMPL1(expr, guid)		(((expr) == false) ? (::GS::AssertImpl::DoWarning ({ __FILE__, __FUNCTION__, __LINE__ }, #expr, guid), false) : true)
#define GSWARNINGGUIDIMPL2(expr, guid, ret)	if ((expr) == false) { ::GS::AssertImpl::DoWarning ({ __FILE__, __FUNCTION__, __LINE__ }, #expr, guid); return ret; }


// === GSWARNING_ONERR =================================================================================================

// For testing use GS::TestSupport::ExpectedWarningScope with the guid. Example usages:
// GSWARNING_ONERR (ic.Read (value));					=> Warn if the return value of 'ic.Read (value)' not equals NoError, and if not, return from the function with that value.
// GSWARNING_ONERR (ic.Read (value), "AB-CD-EF-GH");	=> Does the same as above.
//
// Get the info from the log:
// ConvertLog -meta GSWARNING Path/To/Log/File.log


#define GSWARNING_ONERR(...) \
	GSWARNINGIMPL_EXPAND (GSWARNINGIMPL_GETMACRO (__VA_ARGS__, GSWARNINGONERRIMPL2, GSWARNINGONERRIMPL1) (__VA_ARGS__))


#define GSWARNINGONERRIMPL1(expr)													\
{																					\
	auto result = expr;																\
	if (result != ::GS::NoError) {													\
		::GS::AssertImpl::DoWarning ({ __FILE__, __FUNCTION__, __LINE__ }, #expr);	\
		return result;																\
	}																				\
}

#define GSWARNINGONERRIMPL2(expr, guid)														\
{																							\
	auto result = expr;																		\
	if (result != ::GS::NoError) {															\
		::GS::AssertImpl::DoWarning ({ __FILE__, __FUNCTION__, __LINE__ }, #expr, guid);	\
		return result;																		\
	}																						\
}


// === GSWARNING_FAILED ================================================================================================

// Example usage:
// GSWARNING_FAILED ("Something happened.");
//
// Get the info from the log:
// ConvertLog -meta GSWARNING Path/To/Log/File.log


#define GSWARNING_FAILED(msg) ::GS::AssertImpl::DoWarning ({ __FILE__, __FUNCTION__, __LINE__ }, msg);


/* ================================================================================================================== */


namespace GS::AssertImpl {


GSROOT_DLL_EXPORT
void	DoWarning (const SourceLocation&, const char* expr);

GSROOT_DLL_EXPORT
void	DoWarning (const SourceLocation&, const char* expr, const char* guid);

GSROOT_DLL_EXPORT
void	DoWarning (const SourceLocation&, const char* expr, Guid guid);


GSROOT_DLL_EXPORT
void	DoInspect (const SourceLocation&, const char* expr, const char* owner);

GSROOT_DLL_EXPORT
void	DoInspect (const SourceLocation&, const char* expr, const char* owner, FunctionRef<void (FastLogger::LogComposer&)>);

template<typename... Ts>
void	DoInspect (const SourceLocation& loc, const char* expr, const char* owner, const std::tuple<Ts...>& subject)
{
	::GS::AssertImpl::DoInspect (loc, expr, owner, [&] (FastLogger::LogComposer& composer) {
		std::apply ([&composer] (const auto&... args) {
			(LogAssertSubject (composer, args), ...);
		}, subject);
	});
}


class GSROOT_DLL_EXPORT AssertDescription {
private:
	const char* id			= "";
	const char* description	= "";

public:
	AssertDescription (const char* id, const char* description) noexcept;
	AssertDescription (const char* description) noexcept;

	const char* GetId			() const noexcept;
	const char* GetDescription	() const noexcept;
};


GSROOT_DLL_EXPORT String	AppendDescription (FastLogger::LogComposer& logComposer, const AssertDescription& description);


/* === AssertFailed ================================================================================================= */


GSROOT_DLL_EXPORT void AssertFailed (const SourceLocation&, const AssertData&, const char* expr, FunctionRef<void (FastLogger::LogComposer&, String&)>);

GSROOT_DLL_EXPORT void AssertFailed (const SourceLocation&, const AssertData&, const char* expr, const AssertDescription&);


template<typename... Ts>
void	AssertFailed (const SourceLocation& location, const AssertData& data, const char* expr, const std::tuple<Ts...>& subject)
{
	::GS::AssertImpl::AssertFailed (location, data, expr, [&] (FastLogger::LogComposer& composer, String& bugRep) {
		std::apply ([&composer, &bugRep] (const auto&... args) {
			(((bugRep += LogAssertSubject (composer, args)) += ::GS::EOL), ...);
		}, subject);
	});
}


template<typename... Ts>
void	AssertFailed (const SourceLocation& location, const AssertData& data, const char* expr, const AssertDescription& description, const std::tuple<Ts...>& subject)
{
	::GS::AssertImpl::AssertFailed (location, data, expr, [&] (FastLogger::LogComposer& composer, String& bugRep) {
		(bugRep += ::GS::AssertImpl::AppendDescription (composer, description)) += ::GS::EOL;
		std::apply ([&composer, &bugRep] (const auto&... args) {
			(((bugRep += LogAssertSubject (composer, args)) += ::GS::EOL), ...);
		}, subject);
	});
}


/* === AssertFailedT ================================================================================================ */


GSROOT_DLL_EXPORT void AssertFailedT [[noreturn]] (const SourceLocation&, const AssertData&, const char* expr, const AssertDescription&);


template<typename... Ts>
void	AssertFailedT [[noreturn]] (const SourceLocation& location, const AssertData& data, const char* expr, const std::tuple<Ts...>& subject)
{
	::GS::AssertImpl::AssertFailed<Ts...> (location, data, expr, subject);
	::GS::Unreachable ();
}


template<typename... Ts>
void	AssertFailedT [[noreturn]] (const SourceLocation& location, const AssertData& data, const char* expr, const AssertDescription& description, const std::tuple<Ts...>& subject)
{
	::GS::AssertImpl::AssertFailed<Ts...> (location, data, expr, description, subject);
	::GS::Unreachable ();
}


} // namespace GS::AssertImpl


namespace GS {


GSROOT_DLL_EXPORT
void	RegisterInspectEventReciever (EventReceiver&, std::function<void (const SourceLocation&, const char* owner, const char* expr)>);


GSROOT_DLL_EXPORT String	LogAssertSubject (FastLogger::LogComposer&, Int32);
GSROOT_DLL_EXPORT String	LogAssertSubject (FastLogger::LogComposer&, UInt32);
GSROOT_DLL_EXPORT String	LogAssertSubject (FastLogger::LogComposer&, Int64);
GSROOT_DLL_EXPORT String	LogAssertSubject (FastLogger::LogComposer&, UInt64);
GSROOT_DLL_EXPORT String	LogAssertSubject (FastLogger::LogComposer&, const ErrorStatus&);
GSROOT_DLL_EXPORT String	LogAssertSubject (FastLogger::LogComposer&, const String&);
GSROOT_DLL_EXPORT String	LogAssertSubject (FastLogger::LogComposer&, Guid);
GSROOT_DLL_EXPORT String	LogAssertSubject (FastLogger::LogComposer&, double);
GSROOT_DLL_EXPORT String	LogAssertSubject (FastLogger::LogComposer&, const char*);

GSROOT_DLL_EXPORT void		EnableAssertDialog ();
GSROOT_DLL_EXPORT void		DisableAssertDialog ();
GSROOT_DLL_EXPORT bool		IsAssertDialogEnabled ();

GSROOT_DLL_EXPORT void		ClearIgnoredAsserts ();


class GSROOT_DLL_EXPORT [[nodiscard]] DisableAssertDialogScope {

	const GSFlags savedFlags;

public:

	DisableAssertDialogScope ();
	~DisableAssertDialogScope ();
};


using AssertImpl::AssertDescription;


} // namespace GS


template<typename... Ts>
auto	Subject (Ts&&... ts)
{
	static_assert (sizeof... (Ts) > 0, "Can't call Subject without parameters");

	return std::forward_as_tuple (std::forward<Ts> (ts)...);
}


#endif /* GSASSERT_HPP */
