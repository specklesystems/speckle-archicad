// *********************************************************************************************************************
// Description:		Base algorithms
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// *********************************************************************************************************************


#ifndef BASEALGORITHMS_HPP
#define BASEALGORITHMS_HPP

#include "Definitions.hpp"
#include "FunctionRef.hpp"

#include <utility>


namespace GS {


// === Base algorithms =================================================================================================

template <class In, class T>
In	Find (In first, In last, const T& value)
{
	while (first != last && !(*first == value))
		++first;

	return first;
}


template <class In, class T>
In	Find (In first, In last, const FunctionRef<bool (const T&)> condition)
{
	while (first != last && !condition (*first))
		++first;

	return first;
}


template <class In, class T>
USize	Count (In first, In last, const T& value)
{
	USize result = 0;

	while (first != last) {
		if (*first == value)
			result++;
		++first;
	}

	return result;
}


template <class In, class T>
USize	Count (In first, In last, const FunctionRef<bool (const T&)> condition)
{
	USize result = 0;

	while (first != last) {
		if (condition (*first))
			++result;
		++first;
	}

	return result;
}


template <class For, class T>
void	Fill (For first, For last, const T& value)
{
	while (first != last) {
		*first = value;
		++first;
	}
}


template <class For, class T>
USize	Replace (For first, For last, const T& oldVal, const T& newVal)
{
	USize result = 0;

	while (first != last) {
		if (*first == oldVal) {
			*first = newVal;
			result++;
		}
		++first;
	}

	return result;
}


template <class In1, class In2>
bool	IsEqual (In1 first1, In1 last1, In2 first2)
{
	while (first1 != last1) {
		if (!(*first1 == *first2))
			return false;
		++first1;
		++first2;
	}

	return true;
}


template <class T>
constexpr T		Min (const T& a, const T& b)
{
	return b < a ? b : a;
}


template <class T, class... Ts>
constexpr T		Min (const T& a, const T& b, const T& c, const Ts&... rest)
{
	T minB = GS::Min (b, c, rest...);
	return minB < a ? minB : a;
}


template <class T>
constexpr T		Max (const T& a, const T& b)
{
	return a < b ? b : a;
}


template <class T, class... Ts>
constexpr T		Max (const T& a, const T& b, const T& c, const Ts&... rest)
{
	T maxB = GS::Max (b, c, rest...);
	return a < maxB ? maxB : a;
}


template <class T>
constexpr bool	IsBetween (const T& value, const T& minVal, const T& maxVal)
{
	return minVal <= value && value <= maxVal;
}


template <class T>
constexpr void	CutToMin (T& value, const T& lowerLimit)
{
	if (value < lowerLimit)
		value = lowerLimit;
}


template <class T>
constexpr void	CutToMax (T& value, const T& upperLimit)
{
	if (upperLimit < value)
		value = upperLimit;
}


template <class T>
constexpr void	CutToRange (T& value, const T& lowerLimit, const T& upperLimit)
{
	if (value < lowerLimit)
		value = lowerLimit;
	else if	(upperLimit < value)
		value = upperLimit;
}


template <class T>
constexpr T		Abs (const T& value)
{
	return value < 0 ? -value : value;
}


template <class T>
constexpr void	Swap (T& a, T& b)
{
	T tmp = std::move (a);
	a = std::move (b);
	b = std::move (tmp);
}


}	// namespace GS


#endif
