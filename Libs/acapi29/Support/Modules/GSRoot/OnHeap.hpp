// *********************************************************************************************************************
// Description:		The class template GS::OnHeap contains a value, which is stored on heap.
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// *********************************************************************************************************************


#ifndef ONHEAP_HPP
#define ONHEAP_HPP

#pragma once


#include "GSDebug.hpp"
#include "ParameterPackTraits.hpp"


namespace GS {


// === class OnHeap ====================================================================================================

template <class Type>
class OnHeap final {
private:
	Type*			valuePtr;

	static_assert (IsDecayed<Type>, "'Type' should be decayed.");

	template <class Arg, class... Args>
	using IsEnabledArgs = EnableIf<ParameterPackSize<Args...> != 0 || !IsSame<Decay<Arg>, OnHeap>>;

	template <class SourceType>
	using IsEnabledSourceType = EnableIf<!IsSame<Decay<SourceType>, OnHeap>>;

public:
	OnHeap ();

	template <class Arg, class... Args, class = IsEnabledArgs<Arg, Args...>>
	OnHeap (Arg&& arg, Args&&... args);

	OnHeap (const OnHeap& source);
	OnHeap (OnHeap&& source);

	~OnHeap ();

	template <class SourceType, class = IsEnabledSourceType<SourceType>>
	OnHeap&			operator= (SourceType&& value);

	OnHeap&			operator= (const OnHeap& source);
	OnHeap&			operator= (OnHeap&& source);

	Type&			operator* () & gs_lifebound;
	Type&&			operator* () && gs_lifebound;
	const Type&		operator* () const& gs_lifebound;

	Type*			operator-> () gs_lifebound;
	const Type*		operator-> () const gs_lifebound;
};


// === OnHeap inline methods ===========================================================================================

template <class Type>
OnHeap<Type>::OnHeap ()
{
	valuePtr = new Type ();
}


template <class Type>
template <class Arg, class... Args, class /*= IsEnabledArgs<Arg, Args...>*/>
OnHeap<Type>::OnHeap (Arg&& arg, Args&&... args)
{
	valuePtr = new Type { std::forward<Arg> (arg), std::forward<Args> (args)... };
}


template <class Type>
OnHeap<Type>::OnHeap (const OnHeap& source)
{
	DBASSERT (source.valuePtr != nullptr);

	valuePtr = new Type (*source.valuePtr);
}


template <class Type>
OnHeap<Type>::OnHeap (OnHeap&& source)
{
	DBASSERT (source.valuePtr != nullptr);

	valuePtr = source.valuePtr;
	source.valuePtr = nullptr;
}


template <class Type>
OnHeap<Type>::~OnHeap ()
{
	delete valuePtr;
}


template <class Type>
template <class SourceType, class /*= IsEnabledSourceType<SourceType>*/>
OnHeap<Type>&		OnHeap<Type>::operator= (SourceType&& value)
{
	DBASSERT (valuePtr != nullptr);

	*valuePtr = std::forward<SourceType> (value);

	return *this;
}


template <class Type>
OnHeap<Type>&		OnHeap<Type>::operator= (const OnHeap& source)
{
	DBASSERT (valuePtr != nullptr && source.valuePtr != nullptr);

	*valuePtr = *source.valuePtr;

	return *this;
}


template <class Type>
OnHeap<Type>&		OnHeap<Type>::operator= (OnHeap&& source)
{
	DBASSERT (valuePtr != nullptr && source.valuePtr != nullptr);

	delete valuePtr;
	valuePtr = source.valuePtr;
	source.valuePtr = nullptr;

	return *this;
}


template <class Type>
Type&	OnHeap<Type>::operator* () &
{
	DBASSERT (valuePtr != nullptr);

	return *valuePtr;
}


template <class Type>
const Type&		OnHeap<Type>::operator* () const&
{
	DBASSERT (valuePtr != nullptr);

	return *valuePtr;
}


template <class Type>
Type&&	OnHeap<Type>::operator* () &&
{
	DBASSERT (valuePtr != nullptr);

	return std::move (*valuePtr);
}


template <class Type>
Type*	OnHeap<Type>::operator-> ()
{
	DBASSERT (valuePtr != nullptr);

	return valuePtr;
}


template <class Type>
const Type*		OnHeap<Type>::operator-> () const
{
	DBASSERT (valuePtr != nullptr);

	return valuePtr;
}


}	// namespace GS


#endif
