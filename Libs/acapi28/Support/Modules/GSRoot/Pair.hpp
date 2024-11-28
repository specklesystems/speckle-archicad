// *********************************************************************************************************************
//
// Description:		Class Pair
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// *********************************************************************************************************************


#ifndef PAIR_HPP
#define PAIR_HPP

#pragma once


#include "HashCommon.hpp"
#include "Channel.hpp"


namespace GS {


// === class Pair ======================================================================================================

template <class Type1, class Type2>
class GS_EXPORT_TYPEINFO Pair {
public:
		// Types

	using FirstType  = Type1;
	using SecondType = Type2;

		// Data members

	Type1	first;
	Type2	second;

		// Methods

	constexpr Pair ();
	constexpr Pair (const Type1& first, const Type2& second);
	template <class T1, class T2>	constexpr Pair (const Pair<T1, T2>& source);
	template <class T1, class T2>	constexpr Pair (Pair<T1, T2>&& source);

	template <class T1, class T2>	constexpr Pair&		operator= (const Pair<T1, T2>& source);
	template <class T1, class T2>	constexpr Pair&		operator= (Pair<T1, T2>&& source);

	constexpr void	Get (Type1& outFirst, Type2& outSecond) const;
	constexpr void	Set (const Type1& newFirst, const Type2& newSecond);

	template <class T1 = Type1, class T2 = Type2, class = EnableIf<HasOperatorEquals<T1> && HasOperatorEquals<T2>>>
	constexpr bool	operator== (const Pair& rightOp) const;
	constexpr bool	operator!= (const Pair& rightOp) const;

	template <class T1 = Type1, class T2 = Type2, class = EnableIf<HasOperatorLess<T1> && HasOperatorLess<T2>>>
	constexpr bool	operator<  (const Pair& rightOp) const;
	constexpr bool	operator>  (const Pair& rightOp) const;
	constexpr bool	operator<= (const Pair& rightOp) const;
	constexpr bool	operator>= (const Pair& rightOp) const;

	template <class T1 = Type1, class T2 = Type2, class = EnableIf<HasGenerateHashValue<T1> && HasGenerateHashValue<T2>>>
	ULong			GenerateHashValue () const;

	GSErrCode		Read (IChannel& ic);
	GSErrCode		Write (OChannel& oc) const;
};


// === Pair inline methods =============================================================================================

template <class Type1, class Type2>
constexpr Pair<Type1, Type2>::Pair () :
	first  (),
	second ()
{
}


template <class Type1, class Type2>
constexpr Pair<Type1, Type2>::Pair (const Type1& first, const Type2& second) :
	first  (first),
	second (second)
{
}


template <class Type1, class Type2>
template <class T1, class T2>
constexpr Pair<Type1, Type2>::Pair (const Pair<T1, T2>& source) :
	first  (source.first),
	second (source.second)
{
}


template <class Type1, class Type2>
template <class T1, class T2>
constexpr Pair<Type1, Type2>::Pair (Pair<T1, T2>&& source) :
	first  (std::move (source.first)),
	second (std::move (source.second))
{
	static_assert (!IsReference<Type1> || IsReference<T1>, "If 'Type1' is a reference, and 'T1' is not, you get a dangling reference.");
	static_assert (!IsReference<Type2> || IsReference<T2>, "If 'Type2' is a reference, and 'T2' is not, you get a dangling reference.");
}


template <class Type1, class Type2>
template <class T1, class T2>
constexpr Pair<Type1, Type2>&	Pair<Type1, Type2>::operator= (const Pair<T1, T2>& source)
{
	first  = source.first;
	second = source.second;

	return *this;
}


template <class Type1, class Type2>
template <class T1, class T2>
constexpr Pair<Type1, Type2>&	Pair<Type1, Type2>::operator= (Pair<T1, T2>&& source)
{
	first  = std::move (source.first);
	second = std::move (source.second);

	return *this;
}


template <class Type1, class Type2>
constexpr void	Pair<Type1, Type2>::Get (Type1& outFirst, Type2& outSecond) const
{
	outFirst  = first;
	outSecond = second;
}


template <class Type1, class Type2>
constexpr void	Pair<Type1, Type2>::Set (const Type1& newFirst, const Type2& newSecond)
{
	first  = newFirst;
	second = newSecond;
}


template <class Type1, class Type2>
template <class T1 /*= Type1*/, class T2 /*= Type2*/, class /*= EnableIf<HasOperatorEquals<T1> && HasOperatorEquals<T2>>*/>
constexpr bool		Pair<Type1, Type2>::operator== (const Pair& rightOp) const
{
	return first  == rightOp.first &&
		   second == rightOp.second;
}


template <class Type1, class Type2>
constexpr bool		Pair<Type1, Type2>::operator!= (const Pair& rightOp) const
{
	return !operator== (rightOp);
}


template <class Type1, class Type2>
template <class T1 /*= Type1*/, class T2 /*= Type2*/, class /*= EnableIf<HasOperatorLess<T1> && HasOperatorLess<T2>>*/>
constexpr bool		Pair<Type1, Type2>::operator< (const Pair& rightOp) const
{
	if (!(first == rightOp.first))
		return first < rightOp.first;

	return second < rightOp.second;
}


template <class Type1, class Type2>
constexpr bool		Pair<Type1, Type2>::operator> (const Pair& rightOp) const
{
	return rightOp < *this;
}


template <class Type1, class Type2>
constexpr bool		Pair<Type1, Type2>::operator<= (const Pair& rightOp) const
{
	return !(rightOp < *this);
}


template <class Type1, class Type2>
constexpr bool		Pair<Type1, Type2>::operator>= (const Pair& rightOp) const
{
	return !(*this < rightOp);
}


template <class Type1, class Type2>
template <class T1 /*= Type1*/, class T2 /*= Type2*/, class /*= EnableIf<HasGenerateHashValue<T1> && HasGenerateHashValue<T2>>*/>
ULong	Pair<Type1, Type2>::GenerateHashValue () const
{
	return GS::CalculateHashValue (first, second);
}


template <class Type1, class Type2>
GSErrCode	Pair<Type1, Type2>::Read (IChannel& ic)
{
	return ic.Read (first, second);
}


template <class Type1, class Type2>
GSErrCode	Pair<Type1, Type2>::Write (OChannel& oc) const
{
	return oc.Write (first, second);
}


// === Type aliases ====================================================================================================

template <class Type>
using PairOf = Pair<Type, Type>;


// === Global functions ================================================================================================

template <class Type1, class Type2>
constexpr Pair<Type1, Type2>	NewPair (const Type1& first, const Type2& second)
{
	return Pair<Type1, Type2> (first, second);
}


template <class Type1, class Type2>
Pair<Type1&, Type2&>	Tie (Type1& f, Type2& s)
{
	return Pair<Type1&, Type2&> (f, s);
}


}	// namespace GS


#endif
