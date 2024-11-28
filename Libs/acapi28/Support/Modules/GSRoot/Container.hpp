
// *****************************************************************************
//
//                              Interface Container
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined CONTAINER_HPP
#define CONTAINER_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"
#include "TypeTraits.hpp"
#include "EnumerationTraits.hpp"

// from Standard Library
#include <iterator>


// ============================ Interface Container ============================

namespace GS {

template <class Type>
class Container {
public:
	using ValueType = Type;		// type of the value the container stores

protected:
	template <class T>
	struct MakeConstPtr {
		typedef T ConstType;
	};

	template <class T>
	struct MakeConstPtr<T*> {
		typedef const T* ConstType;
	};
};


enum FromBeginSelector {
	FromBegin
};


enum ToEndSelector {
	ToEnd
};


template <class Container>
void	SelectSmallerAndLargerContainer (Container& cont1, Container& cont2, Container*& smallerCont, Container*& largerCont)
{
	if (cont1.GetSize () <= cont2.GetSize ()) {
		smallerCont = &cont1;
		largerCont  = &cont2;
	} else {
		smallerCont = &cont2;
		largerCont  = &cont1;
	}
}


// TODO C++20: Replace this with std::ranges::begin/end.
template<typename Range>
auto	BeginADL (Range& range)
{
	using std::begin;

	return begin (range);
}


template<typename Range>
auto	EndADL (Range& range)
{
	using std::end;

	return end (range);
}


namespace Impl {

template<typename T>
using HasBeginRequirement = decltype (begin (std::declval<T> ()));

template<typename T>
using HasStdBeginRequirement = decltype (std::begin (std::declval<T> ()));

template<typename Range>
using RangeReferenceRequirement = decltype (*std::declval<SubstituteOr<SubstituteOrNoneSuch<Impl::HasStdBeginRequirement, Range>, Impl::HasBeginRequirement, Range>> ());

// TODO C++20: Replace this with std::ranges::range_reference_t.
template<typename Range>
using RangeReferenceType = SubstituteOrNoneSuch<RangeReferenceRequirement, AddLValueReference<RemoveReference<Range>>>;

} // namespace Impl


template <class Range, class ValueType>
constexpr bool IsCompatibleRange
	= !std::is_same_v<Impl::RangeReferenceType<Range>, Imp::NoneSuch>
	&& std::is_convertible_v<Impl::RangeReferenceType<Range>, ValueType>;


}	// namespace GS
// ____________________________ Interface Container ____________________________


#endif
