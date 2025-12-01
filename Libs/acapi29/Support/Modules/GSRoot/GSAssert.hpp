// *****************************************************************************
//
// Contact person: MB, BIA, PR
//
// *****************************************************************************

#ifndef GSASSERT_HPP
#define GSASSERT_HPP

#include "Definitions.hpp"
#include "FunctionRef.hpp"
#include "GSAssertCore.hpp"
#include "GSAssertDeprecated.hpp"
#include "SourceLocation.hpp"
#include "Subject.hpp"
#include "Warning.hpp"

// from Standard Library
#include <functional>


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


/* ================================================================================================================== */


namespace GS::AssertImpl {


GSROOT_DLL_EXPORT
void	DoInspect (const SourceLocation&, const char* expr, const char* owner);

GSROOT_DLL_EXPORT
void	DoInspect (const SourceLocation&, const char* expr, const char* owner, FunctionRef<void (std::ostream&)>);

template<typename... Ts>
void	DoInspect (const SourceLocation& loc, const char* expr, const char* owner, const std::tuple<Ts...>& subjects)
{
	::GS::AssertImpl::DoInspect (loc, expr, owner, [&] (std::ostream& os) {
		::GS::PrintSubjects (os, subjects, std::make_index_sequence<sizeof... (Ts)> {});
	});
}


class AssertDescription {
private:
	const char* id			= "";
	const char* description	= "";

public:
	constexpr AssertDescription (const char* id, const char* description)	: id { id }, description { description } {};
	constexpr AssertDescription (const char* description)					: description { description } {};

	constexpr const char* GetId			 () const noexcept { return id == nullptr ? "" : id; }
	constexpr const char* GetDescription () const noexcept { return description == nullptr ? "" : description; };
};


/* === AssertFailed ================================================================================================= */


GSROOT_DLL_EXPORT void AssertFailed (const SourceLocation&, const AssertData&, const char* expr, const AssertDescription*, FunctionRef<void (std::ostream&)>) GS_CLANG_ANALYZER_NORETURN;

GSROOT_DLL_EXPORT void AssertFailed (const SourceLocation&, const AssertData&, const char* expr, const AssertDescription&) GS_CLANG_ANALYZER_NORETURN;


template<typename... Ts>
void	AssertFailed (const SourceLocation& location, const AssertData& data, const char* expr, const std::tuple<Ts...>& subjects) GS_CLANG_ANALYZER_NORETURN
{
	::GS::AssertImpl::AssertFailed (location, data, expr, nullptr, [&] (std::ostream& os) {
		::GS::PrintSubjects (os, subjects, std::make_index_sequence<sizeof... (Ts)> {});
	});
}


template<typename... Ts>
void	AssertFailed (const SourceLocation& location, const AssertData& data, const char* expr, const AssertDescription& description, const std::tuple<Ts...>& subjects) GS_CLANG_ANALYZER_NORETURN
{
	::GS::AssertImpl::AssertFailed (location, data, expr, &description, [&] (std::ostream& os) {
		::GS::PrintSubjects (os, subjects, std::make_index_sequence<sizeof... (Ts)> {});
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


#endif /* GSASSERT_HPP */
