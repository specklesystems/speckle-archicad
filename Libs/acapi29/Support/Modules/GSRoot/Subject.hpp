// *****************************************************************************
//
// Contact person: MB, BIA, PR
//
// *****************************************************************************

#ifndef GS_SUBJECT_HPP
#define GS_SUBJECT_HPP

#include "Definitions.hpp"
#include "GSRootExport.hpp"

// from Standard Library
#include <ostream>
#include <string_view>
#include <tuple>
#include <typeinfo>
#include <utility>


namespace GS {


GSROOT_DLL_EXPORT
void	PrintSubject (std::ostream&, float);


GSROOT_DLL_EXPORT
void	PrintSubject (std::ostream&, double);


GSROOT_DLL_EXPORT
void	PrintSubject (std::ostream&, const std::type_info&);


template<typename T>
void	PrintSubject (std::ostream& os, const T& subject)
{
	os << subject;
}


template<typename... Ts, std::size_t... Is>
void	PrintSubjects (std::ostream& os, const std::tuple<Ts...>& subjects, std::index_sequence<Is...>)
{
	using namespace std::string_view_literals;

	(((os << "\nSubject "sv << (Is + 1) << ":\n"sv), PrintSubject (os, std::get<Is> (subjects))), ...);
}


} // namespace GS


template<typename... Ts>
auto	Subject (Ts&&... ts)
{
	static_assert (sizeof... (Ts) > 0, "Can't call Subject without parameters.");

	return std::forward_as_tuple (std::forward<Ts> (ts)...);
}


#endif /* GS_SUBJECT_HPP */
