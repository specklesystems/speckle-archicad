// *********************************************************************************************************************
// Description:		A traits class, that can be specialized to tell whether a class is enumerable (i.e. a container)
//					or not. Enables different function overloads for enumerable and not enumerable types.
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB, KKr
//
// *********************************************************************************************************************

// TODO C++20: This file can be deleted. IsEnumerable can be replaced with the std::ranges::range concept.

#ifndef ENUMERATIONTRAITS_HPP
#define ENUMERATIONTRAITS_HPP

#pragma once


#include "TypeTraits.hpp"


namespace GS {

namespace Imp {

void begin ();		// disabling ordinary lookup
void end ();		// disabling ordinary lookup

template <class T>
constexpr bool	IsEnumerableExternal (decltype (bool { begin (std::declval<T> ()) != end (std::declval<T> ()) })*) { return true; }

template <class T>
constexpr bool	IsEnumerableExternal (...) { return false; }

template <class T>
constexpr bool	IsEnumerableInternal (decltype (bool { std::declval<T> ().begin () != std::declval<T> ().end () })*) { return true; }

template <class T>
constexpr bool	IsEnumerableInternal (...) { return false; }

template <class T>
constexpr bool	IsEnumerable = IsEnumerableExternal<T> (nullptr) || IsEnumerableInternal<T> (nullptr);		// this intermediate definition is needed due to a Developer Studio internal compiler error

template <class T, size_t N>
constexpr bool IsEnumerable<T[N]> = true;

} // namespace Imp

template <class T>
constexpr bool	IsEnumerable = Imp::IsEnumerable<T>;

template <class T>
using Enumerable = EnableIf<IsEnumerable<T>, bool>;			// for convenient compile time function selection (like enable_if)

template <class T>
using NotEnumerable = EnableIf<!IsEnumerable<T>, bool>;		// for convenient compile time function selection (like enable_if)

} // namespace GS


#endif
