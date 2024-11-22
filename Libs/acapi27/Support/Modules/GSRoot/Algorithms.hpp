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


#include <algorithm>
#include "BaseAlgorithms.hpp"
#include "GSDebug.hpp"
#include "STLIteratorConnection.hpp"
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

template <class In, class UnOp>
UnOp	ForEach (In first, In last, UnOp op)
{
	return std::for_each (first, last, op);
}


template <class In, class Pred>
In	FindIf (In first, In last, Pred condition)
{
	return std::find_if (first, last, condition);
}


template <class For1, class For2>
For1	FindFirstOf (For1 first1, For1 last1, For2 first2, For2 last2)
{
	return std::find_first_of (first1, last1, first2, last2);
}


template <class For1, class For2, class BinPred>
For1	FindFirstOf (For1 first1, For1 last1, For2 first2, For2 last2, BinPred isEqual)
{
	return std::find_first_of (first1, last1, first2, last2, isEqual);
}


template <class For>
For		AdjacentFind (For first, For last)
{
	return std::adjacent_find (first, last);
}


template <class For, class BinPred>
For		AdjacentFind (For first, For last, BinPred isEqual)
{
	return std::adjacent_find (first, last, isEqual);
}


template <class In, class Pred>
USize	CountIf (In first, In last, Pred condition)
{
	return TruncateTo32Bit (std::count_if (first, last, condition));
}


template <class In1, class In2>
Pair<In1, In2>	Mismatch (In1 first1, In1 last1, In2 first2)
{
	return Imp::ToGsPair (std::mismatch (first1, last1, first2));
}


template <class In1, class In2, class BinPred>
Pair<In1, In2>	Mismatch (In1 first1, In1 last1, In2 first2, BinPred isEqual)
{
	return Imp::ToGsPair (std::mismatch (first1, last1, first2, isEqual));
}


template <class In1, class In2, class BinPred>
bool	IsEqual (In1 first1, In1 last1, In2 first2, BinPred isEqual)
{
	return std::equal (first1, last1, first2, isEqual);
}


template <class For1, class For2>
For1	Search (For1 first1, For1 last1, For2 first2, For2 last2)
{
	return std::search (first1, last1, first2, last2);
}


template <class For1, class For2, class BinPred>
For1	Search (For1 first1, For1 last1, For2 first2, For2 last2, BinPred isEqual)
{
	return std::search (first1, last1, first2, last2, isEqual);
}


template <class For1, class For2>
For1	FindEnd (For1 first1, For1 last1, For2 first2, For2 last2)
{
	return std::find_end (first1, last1, first2, last2);
}


template <class For1, class For2, class BinPred>
For1	FindEnd (For1 first1, For1 last1, For2 first2, For2 last2, BinPred isEqual)
{
	return std::find_end (first1, last1, first2, last2, isEqual);
}


template <class For, class T>
For		SearchN (For first, For last, USize range, const T& value)
{
	return std::search_n (first, last, range, value);
}


template <class For, class T, class BinPred>
For		SearchN (For first, For last, USize range, const T& value, BinPred isEqual)
{
	return std::search_n (first, last, range, value, isEqual);
}


template <class In1, class In2, class Out, class BinOp>
Out		Transform (In1 first1, In1 last1, In2 first2, Out result, BinOp op)
{
	return std::transform (first1, last1, first2, result, op);
}


template <class In, class Out, class UnOp>
Out		Transform (In first, In last, Out result, UnOp op)
{
	return std::transform (first, last, result, op);
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


template <class Bi1, class Bi2>
Bi2		CopyBackward (Bi1 first, Bi1 last, Bi2 result)
{
	return std::copy_backward (first, last, result);
}


template <class Bi1, class Bi2, class Pred>
Bi2		CopyIfBackward (Bi1 first, Bi1 last, Bi2 result, Pred condition)
{
	while (first != last) {
		--last;
		if (condition (*last)) {
			--result;
			*result = *last;
		}
	}

	return result;
}


template <class For1, class For2>
void	IterSwap (For1 f1, For2 f2)
{
	std::iter_swap (f1, f2);
}


template <class For1, class For2>
For2	SwapRanges (For1 first1, For1 last1, For2 first2)
{
	return std::swap_ranges (first1, last1, first2);
}


template <class For, class Pred, class T>
void	ReplaceIf (For first, For last, Pred condition, const T& newVal)
{
	std::replace_if (first, last, condition, newVal);
}


template <class In, class Out, class T>
Out		ReplaceCopy (In first, In last, Out res, const T& oldVal, const T& newVal)
{
	return std::replace_copy (first, last, res, oldVal, newVal);
}


template <class In, class Out, class Pred, class T>
Out		ReplaceCopyIf (In first, In last, Out res, Pred condition, const T& newVal)
{
	return std::replace_copy_if (first, last, res, condition, newVal);
}


template <class Out, class T>
void	FillN (Out first, USize range, const T& value)
{
	std::fill_n (first, range, value);
}


template <class For, class Gen>
void	Generate (For first, For last, Gen gen)
{
	std::generate (first, last, gen);
}


template <class Out, class Gen>
Out		GenerateN (Out first, USize range, Gen gen)
{
	return std::generate_n (first, range, gen);
}


template <class For, class T>
For		Remove (For first, For last, const T& value)
{
	return std::remove (first, last, value);
}


template <class For, class Pred>
For		RemoveIf (For first, For last, Pred condition)
{
	return std::remove_if (first, last, condition);
}


template <class In, class Out, class T>
Out		RemoveCopy (In first, In last, Out res, const T& value)
{
	return std::remove_copy (first, last, res, value);
}


template <class In, class Out, class Pred>
Out		RemoveCopyIf (In first, In last, Out res, Pred condition)
{
	return std::remove_copy_if (first, last, res, condition);
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


template <class For, class Out>
Out		UniqueCopy (For first, For last, Out res)
{
	return std::unique_copy (first, last, res);
}


template <class For, class Out, class BinPred>
Out		UniqueCopy (For first, For last, Out res, BinPred isEqual)
{
	return std::unique_copy (first, last, res, isEqual);
}


template <class Bi>
void	Reverse (Bi first, Bi last)
{
	std::reverse (first, last);
}


template <class Bi, class Out>
Out		ReverseCopy (Bi first, Bi last, Out res)
{
	return std::reverse_copy (first, last, res);
}


template <class For>
void	 Rotate (For first, For mid, For last)
{
	std::rotate (first, mid, last);
}


template <class For, class Out>
Out		RotateCopy (For first, For mid, For last, Out res)
{
	return std::rotate_copy (first, mid, last, res);
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
void	PartialSort (Ran first, Ran mid, Ran last)
{
	IS_LESS_CHECK1 (first, last);
	std::partial_sort (first, mid, last);
}


template <class Ran, class BinPred>
void	PartialSort (Ran first, Ran mid, Ran last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	std::partial_sort (first, mid, last, isLess);
}


template <class In, class Ran>
Ran		PartialSortCopy (In first1, In last1, Ran first2, Ran last2)
{
	IS_LESS_CHECK1 (first1, last1);
	return std::partial_sort_copy (first1, last1, first2, last2);
}


template <class In, class Ran, class BinPred>
Ran		PartialSortCopy (In first1, In last1, Ran first2, Ran last2, BinPred isLess)
{
	IS_LESS_CHECK2 (first1, last1, isLess);
	return std::partial_sort_copy (first1, last1, first2, last2, isLess);
}


template <class For>
bool	IsSorted (For first, For last)
{
	IS_LESS_CHECK1 (first, last);
	return std::is_sorted (first, last);
}


template <class For, class BinPred>
bool	IsSorted (For first, For last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	return std::is_sorted (first, last, isLess);
}


template <class For>
For		IsSortedUntil (For first, For last)
{
	IS_LESS_CHECK1 (first, last);
	return std::is_sorted_until (first, last);
}


template <class For, class BinPred>
For		IsSortedUntil (For first, For last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	return std::is_sorted_until (first, last, isLess);
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


template <class For, class T>
bool 	BinarySearch (For first, For last, const T& value)
{
	IS_LESS_CHECK1 (first, last);
	return std::binary_search (first, last, value);
}


template <class For, class T, class BinPred>
bool 	BinarySearch (For first, For last, const T& value, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	return std::binary_search (first, last, value, isLess);
}


template <class In1, class In2, class Out>
Out		Merge (In1 first1, In1 last1, In2 first2, In2 last2, Out res)
{
	IS_LESS_CHECK1 (first1, last1);
	return std::merge (first1, last1, first2, last2, res);
}


template <class In1, class In2, class Out, class BinPred>
Out		Merge (In1 first1, In1 last1, In2 first2, In2 last2, Out res, BinPred isLess)
{
	IS_LESS_CHECK2 (first1, last1, isLess);
	return std::merge (first1, last1, first2, last2, res, isLess);
}


template <class Bi>
void	 InplaceMerge (Bi first, Bi mid, Bi last)
{
	IS_LESS_CHECK1 (first, last);
	std::inplace_merge (first, mid, last);
}


template <class Bi, class BinPred>
void	 InplaceMerge (Bi first, Bi mid, Bi last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	std::inplace_merge (first, mid, last, isLess);
}


template <class Bi, class Pred>
Bi	Partition (Bi first, Bi last, Pred condition)
{
	return std::partition (first, last, condition);
}


template <class Bi, class Pred>
Bi	StablePartition (Bi first, Bi last, Pred condition)
{
	return std::stable_partition (first, last, condition);
}


template <class In>
bool	 Includes (In first1, In last1, In first2, In last2)
{
	IS_LESS_CHECK1 (first1, last1);
	return std::includes (first1, last1, first2, last2);
}


template <class In, class BinPred>
bool	 Includes (In first1, In last1, In first2, In last2, BinPred isLess)
{
	IS_LESS_CHECK2 (first1, last1, isLess);
	return std::includes (first1, last1, first2, last2, isLess);
}


template <class In1, class In2, class Out>
Out		SetUnion (In1 first1, In1 last1, In2 first2, In2 last2, Out res)
{
	IS_LESS_CHECK1 (first1, last1);
	return std::set_union (first1, last1, first2, last2, res);
}


template <class In1, class In2, class Out, class BinPred>
Out		SetUnion (In1 first1, In1 last1, In2 first2, In2 last2, Out res, BinPred isLess)
{
	IS_LESS_CHECK2 (first1, last1, isLess);
	return std::set_union (first1, last1, first2, last2, res, isLess);
}


template <class In, class Out>
Out		SetIntersection (In first1, In last1, In first2, In last2, Out res)
{
	IS_LESS_CHECK1 (first1, last1);
	return std::set_intersection (first1, last1, first2, last2, res);
}


template <class In, class Out, class BinPred>
Out		SetIntersection (In first1, In last1, In first2, In last2, Out res, BinPred isLess)
{
	IS_LESS_CHECK2 (first1, last1, isLess);
	return std::set_intersection (first1, last1, first2, last2, res, isLess);
}


template <class In1, class In2, class Out>
Out		SetDifference (In1 first1, In1 last1, In2 first2, In2 last2, Out res)
{
	IS_LESS_CHECK1 (first1, last1);
	return std::set_difference (first1, last1, first2, last2, res);
}


template <class In1, class In2, class Out, class BinPred>
Out		SetDifference (In1 first1, In1 last1, In2 first2, In2 last2, Out res, BinPred isLess)
{
	IS_LESS_CHECK2 (first1, last1, isLess);
	return std::set_difference (first1, last1, first2, last2, res, isLess);
}


template <class In1, class In2, class Out>
Out		SetSymmetricDifference (In1 first1, In1 last1, In2 first2, In2 last2, Out res)
{
	IS_LESS_CHECK1 (first1, last1);
	return std::set_symmetric_difference (first1, last1, first2, last2, res);
}


template <class In1, class In2, class Out, class BinPred>
Out		SetSymmetricDifference (In1 first1, In1 last1, In2 first2, In2 last2, Out res, BinPred isLess)
{
	IS_LESS_CHECK2 (first1, last1, isLess);
	return std::set_symmetric_difference (first1, last1, first2, last2, res, isLess);
}


template <class Ran>
void	MakeHeap (Ran first, Ran last)
{
	IS_LESS_CHECK1 (first, last);
	std::make_heap (first, last);
}


template <class Ran, class BinPred>
void	MakeHeap (Ran first, Ran last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	std::make_heap (first, last, isLess);
}


template <class Ran>
void	PushHeap (Ran first, Ran last)
{
	IS_LESS_CHECK1 (first, last);
	std::push_heap (first, last);
}


template <class Ran, class BinPred>
void	PushHeap (Ran first, Ran last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	std::push_heap (first, last, isLess);
}


template <class Ran>
void	PopHeap (Ran first, Ran last)
{
	IS_LESS_CHECK1 (first, last);
	std::pop_heap (first, last);
}


template <class Ran, class BinPred>
void	PopHeap (Ran first, Ran last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	std::pop_heap (first, last, isLess);
}


template <class Ran>
void	SortHeap (Ran first, Ran last)
{
	IS_LESS_CHECK1 (first, last);
	std::sort_heap (first, last);
}


template <class Ran, class BinPred>
void	SortHeap (Ran first, Ran last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	std::sort_heap (first, last, isLess);
}


template <class Ran>
bool	IsHeap (Ran first, Ran last)
{
	IS_LESS_CHECK1 (first, last);
	return std::is_heap (first, last);
}


template <class Ran, class BinPred>
bool	IsHeap (Ran first, Ran last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	return std::is_heap (first, last, isLess);
}


template <class Ran>
Ran		IsHeapUntil (Ran first, Ran last)
{
	IS_LESS_CHECK1 (first, last);
	return std::is_heap_until (first, last);
}


template <class Ran, class BinPred>
Ran		IsHeapUntil (Ran first, Ran last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	return std::is_heap_until (first, last, isLess);
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


template <class T>
constexpr Pair<T, T>	MinMax (const T& a, const T& b)
{
	return Imp::ToGsPair (std::minmax (a, b));
}


template <class T, class BinPred>
constexpr Pair<T, T>	MinMax (const T& a, const T& b, BinPred isLess)
{
	return Imp::ToGsPair (std::minmax (a, b, isLess));
}


template <class T, class... Ts>
constexpr Pair<T, T>	MinMax (const T& a, const T& b, const T& c, const Ts&... rest)
{
	return Imp::ToGsPair (std::minmax ({ a, b, c, rest... }));
}


template <class T, class BinPred>
constexpr Pair<T, T>	MinMax (std::initializer_list<T> iList, BinPred isLess)
{
	return Imp::ToGsPair (std::minmax (iList, isLess));
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


template <class In1, class In2>
bool 	LexicographicalCompare (In1 first1, In1 last1, In2 first2, In2 last2)
{
	IS_LESS_CHECK1 (first1, last1);
	return std::lexicographical_compare (first1, last1, first2, last2);
}


template <class In1, class In2, class BinPred>
bool 	LexicographicalCompare (In1 first1, In1 last1, In2 first2, In2 last2, BinPred isLess)
{
	IS_LESS_CHECK2 (first1, last1, isLess);
	return std::lexicographical_compare (first1, last1, first2, last2, isLess);
}


template <class Bi>
bool 	NextPermutation (Bi first, Bi last)
{
	IS_LESS_CHECK1 (first, last);
	return std::next_permutation (first, last);
}


template <class Bi, class BinPred>
bool 	NextPermutation (Bi first, Bi last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	return std::next_permutation (first, last, isLess);
}


template <class Bi>
bool 	PrevPermutation (Bi first, Bi last)
{
	IS_LESS_CHECK1 (first, last);
	return std::prev_permutation (first, last);
}


template <class Bi, class BinPred>
bool 	PrevPermutation (Bi first, Bi last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	return std::prev_permutation (first, last, isLess);
}


}	// namespace GS


#endif
