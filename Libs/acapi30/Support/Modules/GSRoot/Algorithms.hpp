// *********************************************************************************************************************
// Description:		Algorithms
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// *********************************************************************************************************************


#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#pragma once


#ifndef GS_BUILD_MODULE
#include <algorithm>
#endif

#include "BaseAlgorithms.hpp"
#include "GSDebug.hpp"
#include "Pair.hpp"


// === Comparator preconditions ========================================================================================

#define IS_LESS_CHECK1(first, last)				DBASSERT_STR (first == last || !(*first < *first),       "Invalid 'operator<' was used in an STL algorithm. Did you implement it with '<=' instead of '<'?");
#define IS_LESS_CHECK2(first, last, isLess)		DBASSERT_STR (first == last || !isLess (*first, *first), "Invalid 'isLess' comparator was passed to an STL algorithm. Did you implement it with '<=' instead of '<'?");



namespace GS {


namespace Imp {


// === Implementation details ==========================================================================================

template <class Type1, class Type2>
constexpr Pair<Type1, Type2>	ToGsPair (std::pair<Type1, Type2>&& stdPair)
{
	return { std::move (stdPair.first), std::move (stdPair.second) };
}


}	// namespace Imp


// === Algorithms ======================================================================================================

template <class In, class Pred>
In	FindIf (In first, In last, Pred condition)
{
	return std::find_if (first, last, condition);
}


template <class In, class Pred>
USize	CountIf (In first, In last, Pred condition)
{
	return TruncateTo32Bit (std::count_if (first, last, condition));
}


template <class In1, class In2, class BinPred>
bool	IsEqual (In1 first1, In1 last1, In2 first2, BinPred isEqual)
{
	return std::equal (first1, last1, first2, isEqual);
}


template <class In, class Out>
Out		Copy (In first, In last, Out result)
{
	return std::copy (first, last, result);
}


template <class In, class Out, class Pred>
Out		CopyIf (In first, In last, Out result, Pred condition)
{
	while (first != last) {
		if (condition (*first)) {
			*result = *first;
			++result;
		}
		++first;
	}

	return result;
}


template <class For, class Pred>
For		RemoveIf (For first, For last, Pred condition)
{
	return std::remove_if (first, last, condition);
}


template <class For>
For		Unique (For first, For last)
{
	return std::unique (first, last);
}


template <class For, class BinPred>
For		Unique (For first, For last, BinPred isEqual)
{
	return std::unique (first, last, isEqual);
}


template <class Bi>
void	Reverse (Bi first, Bi last)
{
	std::reverse (first, last);
}


template <class For>
void	 Rotate (For first, For mid, For last)
{
	std::rotate (first, mid, last);
}


template <class Ran>
void	Sort (Ran first, Ran last)
{
	IS_LESS_CHECK1 (first, last);
	std::sort (first, last);
}


template <class Ran, class BinPred>
void	Sort (Ran first, Ran last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	std::sort (first, last, isLess);
}


template <class Bi>
void	StableSort (Bi first, Bi last)
{
	IS_LESS_CHECK1 (first, last);
	std::stable_sort (first, last);
}


template <class Bi, class BinPred>
void	StableSort (Bi first, Bi last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	std::stable_sort (first, last, isLess);
}


template <class Ran>
void	NthElement (Ran first, Ran nth, Ran last)
{
	IS_LESS_CHECK1 (first, last);
	std::nth_element (first, nth, last);
}


template <class Ran, class BinPred>
void	NthElement (Ran first, Ran nth, Ran last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	std::nth_element (first, nth, last, isLess);
}


template <class For, class T>
For		LowerBound (For first, For last, const T& value)
{
	IS_LESS_CHECK1 (first, last);
	return std::lower_bound (first, last, value);
}


template <class For, class T, class BinPred>
For		LowerBound (For first, For last, const T& value, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	return std::lower_bound (first, last, value, isLess);
}


template <class For, class T>
For		UpperBound (For first, For last, const T& value)
{
	IS_LESS_CHECK1 (first, last);
	return std::upper_bound (first, last, value);
}


template <class For, class T, class BinPred>
For		UpperBound (For first, For last, const T& value, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	return std::upper_bound (first, last, value, isLess);
}


template <class For, class T>
Pair<For, For>	EqualRange (For first, For last, const T& value)
{
	IS_LESS_CHECK1 (first, last);
	return Imp::ToGsPair (std::equal_range (first, last, value));
}


template <class For, class T, class BinPred>
Pair<For, For>	EqualRange (For first, For last, const T& value, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	return Imp::ToGsPair (std::equal_range (first, last, value, isLess));
}


template <class Bi>
void	InplaceMerge (Bi first, Bi mid, Bi last)
{
	IS_LESS_CHECK1 (first, last);
	std::inplace_merge (first, mid, last);
}


template <class Bi, class BinPred>
void	InplaceMerge (Bi first, Bi mid, Bi last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	std::inplace_merge (first, mid, last, isLess);
}


template <class Bi, class Pred>
Bi	Partition (Bi first, Bi last, Pred condition)
{
	return std::partition (first, last, condition);
}


template <class T, class BinPred>
constexpr T		Min (const T& a, const T& b, BinPred isLess)
{
	return (std::min) (a, b, isLess);
}


template <class T, class BinPred>
constexpr T		Min (std::initializer_list<T> iList, BinPred isLess)
{
	return (std::min) (iList, isLess);
}


template <class T, class BinPred>
constexpr T		Max (const T& a, const T& b, BinPred isLess)
{
	return (std::max) (a, b, isLess);
}


template <class T, class BinPred>
constexpr T		Max (std::initializer_list<T> iList, BinPred isLess)
{
	return (std::max) (iList, isLess);
}


template <class For>
constexpr For		MinElement (For first, For last)
{
	IS_LESS_CHECK1 (first, last);
	return std::min_element (first, last);
}


template <class For, class BinPred>
constexpr For		MinElement (For first, For last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	return std::min_element (first, last, isLess);
}


template <class For>
constexpr For		MaxElement (For first, For last)
{
	IS_LESS_CHECK1 (first, last);
	return std::max_element (first, last);
}


template <class For, class BinPred>
constexpr For		MaxElement (For first, For last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	return std::max_element (first, last, isLess);
}


template <class For>
constexpr Pair<For, For>	MinMaxElement (For first, For last)
{
	IS_LESS_CHECK1 (first, last);
	return Imp::ToGsPair (std::minmax_element (first, last));
}


template <class For, class BinPred>
constexpr Pair<For, For>	MinMaxElement (For first, For last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	return Imp::ToGsPair (std::minmax_element (first, last, isLess));
}


}	// namespace GS


#endif
