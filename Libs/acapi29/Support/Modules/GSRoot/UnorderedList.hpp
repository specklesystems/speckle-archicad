// *********************************************************************************************************************
//
//                                  Class UnorderedList
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SzoBe
//
//
//
// *********************************************************************************************************************


#ifndef UNORDEREDLIST_HPP
#define UNORDEREDLIST_HPP

#pragma once


#include "Array.hpp"
#include "ParameterPackTraits.hpp"


// === class UnorderedList =============================================================================================

namespace GS {

template <class Type>
class UnorderedList;


template <class Type>
bool operator== (const Array<Type>& array, const UnorderedList<Type>& unorderedList);

template <class Type>
bool operator!= (const Array<Type>& array, const UnorderedList<Type>& unorderedList);

template <class Type>
bool operator== (const UnorderedList<Type>& unorderedList, const Array<Type>& array);

template <class Type>
bool operator!= (const UnorderedList<Type>& unorderedList, const Array<Type>& array);


template <class Type>
class UnorderedListBase {
public:
	UnorderedListBase ()
	{
		static_assert (HasOperatorEquals<Type>, "'Type' has no operator== ().");
	}
};


template <class Type>
class UnorderedList : public UnorderedListBase<Type> {
private:
	Array<Type> array;

	static bool		IsEqual (const Array<Type>& array1, const Array<Type>& array2);

	template <class FirstArg, class... OtherArgs>
	static void		Push (Array<Type>& target, const FirstArg& firstArg, const OtherArgs&... otherArgs);
	static void		Push (Array<Type>&);

public:
		// Constructors

	UnorderedList () = default;
	UnorderedList (const Array<Type>& items);
	UnorderedList (Array<Type>&& items);
	UnorderedList (std::initializer_list<Type> items);

		// Friend functions
	
	friend bool operator==<Type> (const Array<Type>& array, const UnorderedList& unorderedList);
	friend bool operator!=<Type> (const Array<Type>& array, const UnorderedList& unorderedList);
	friend bool operator==<Type> (const UnorderedList& unorderedList, const Array<Type>& array);
	friend bool operator!=<Type> (const UnorderedList& unorderedList, const Array<Type>& array);

	template <class Type2>
	friend UnorderedList<Type2> Unordered ();

	template <class FirstArg, class... OtherArgs>
	friend UnorderedList<FirstArg> Unordered (const FirstArg& firstArg, const OtherArgs&... otherArgs);
};


template <class Type>
UnorderedList<Type>::UnorderedList (const Array<Type>& items) :
	array (items)
{
}


template <class Type>
UnorderedList<Type>::UnorderedList (Array<Type>&& items) :
	array (std::move (items))
{
}


template <class Type>
UnorderedList<Type>::UnorderedList (std::initializer_list<Type> items) :
	array (items)
{
}


template <class Type>
bool	UnorderedList<Type>::IsEqual (const Array<Type>& array1, const Array<Type>& array2)
{
	if (array1.GetSize () != array2.GetSize ())
		return false;

	for (const Type& item : array1) {
		if (array1.Count (item) != array2.Count (item))
			return false;
	}

	return true;
}


template <class Type>
bool	operator== (const Array<Type>& array, const UnorderedList<Type>& unorderedList)
{
	return UnorderedList<Type>::IsEqual (array, unorderedList.array);
}


template <class Type>
bool	operator!= (const Array<Type>& array, const UnorderedList<Type>& unorderedList)
{
	return !UnorderedList<Type>::IsEqual (array, unorderedList.array);
}


template <class Type>
bool	operator== (const UnorderedList<Type>& unorderedList, const Array<Type>& array)
{
	return UnorderedList<Type>::IsEqual (array, unorderedList.array);
}


template <class Type>
bool	operator!= (const UnorderedList<Type>& unorderedList, const Array<Type>& array)
{
	return !UnorderedList<Type>::IsEqual (array, unorderedList.array);
}


template <class Type>
void	UnorderedList<Type>::Push (Array<Type>&)
{
}


template <class Type>
template <class FirstArg, class... OtherArgs>
void	UnorderedList<Type>::Push (Array<Type>& target, const FirstArg& firstArg, const OtherArgs&... otherArgs)
{
	target.Push (firstArg);
	Push (target, otherArgs...);
}


template <class Type>
UnorderedList<Type>		Unordered ()
{
	return UnorderedList<Type> ();
}


template <class FirstArg, class... OtherArgs>
UnorderedList<FirstArg>		Unordered (const FirstArg& firstArg, const OtherArgs&... otherArgs)
{
	constexpr USize Capacity = ParameterPackSize<OtherArgs...> + 1;
	
	Array<FirstArg> items (Capacity);

	UnorderedList<FirstArg>::Push (items, firstArg, otherArgs...);
	
	return UnorderedList<FirstArg> (std::move (items));
}


}	// namespace GS


#endif
