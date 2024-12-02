
// *****************************************************************************
//
//                              Class FixArray
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined FIXARRAY_HPP
#define FIXARRAY_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "BaseAlgorithms.hpp"
#include "Channel.hpp"
#include "Enumerator.hpp"
#include "FunctionRef.hpp"
#include "Inserter.hpp"
#include "RandomContainer.hpp"
#include "RandomContainerIterator.hpp"
#include "RandomContainerReverseIterator.hpp"

#include <new>
#include <utility>
#include <functional>


// ============================== Class FixArray  ==============================

namespace GS {

template <class Type, USize Size>
class GS_EXPORT_TYPEINFO FixArray final: public RandomContainer<Type> {
private:
	Type array[Size];	// array storing items

	static_assert (Size > 0, "Size can't be 0");

public:
		// Types

	typedef RandomContainerIterator<FixArray>				Iterator;
	typedef ConstRandomContainerIterator<FixArray>			ConstIterator;

	typedef GeneralRandomContainerIterator<FixArray>		GeneralIterator;
	typedef ConstGeneralRandomContainerIterator<FixArray>	ConstGeneralIterator;

	typedef RandomContainerReverseIterator<FixArray>		ReverseIterator;
	typedef ConstRandomContainerReverseIterator<FixArray>	ConstReverseIterator;

	typedef RandomContainerRange<FixArray>					Range;
	typedef RandomContainerConstRange<FixArray>				ConstRange;

	typedef RandomContainerReverseRange<FixArray>			ReverseRange;
	typedef RandomContainerReverseConstRange<FixArray>		ReverseConstRange;

	typedef Type*		 FastIterator;
	typedef const Type*	 ConstFastIterator;

	class ConversionEnumerator;

		// Constructors

	FixArray ();
	explicit FixArray (const Type& initialValue);
	template<class SourceType>
	explicit FixArray (SourceType (&a)[Size]);
	template<class SourceType>
	explicit FixArray (SourceType (&&a)[Size]);
	constexpr FixArray (std::initializer_list<Type> items);
	FixArray (const FixArray& source);
	FixArray (FixArray&& source);
	FixArray (const FixArray&&) = delete;

	template <class SourceType>
	explicit FixArray (const FixArray<SourceType, Size>& source);

	FixArray&	operator= (const FixArray& source);
	FixArray&	operator= (FixArray&& source);

	template <class SourceType>
	FixArray&	operator= (const FixArray<SourceType, Size>& source);

	void					Move (FixArray& source);

		// Item access

	Type&					operator[] (UIndex idx) gs_lifebound;
	constexpr const Type&	operator[] (UIndex idx) const gs_lifebound;

	Type&					Get (UIndex idx) gs_lifebound;
	constexpr const Type&	Get (UIndex idx) const gs_lifebound;

	Type&					GetFirst (void) gs_lifebound;
	constexpr const Type&	GetFirst (void) const gs_lifebound;

	Type&					GetLast (void) gs_lifebound;
	constexpr const Type&	GetLast (void) const gs_lifebound;
	constexpr UIndex		GetLastIndex (void) const;

	void					Set (UIndex idx, const Type& item);
	void					Set (UIndex idx, Type&& item);

		// Content management

	void					Fill (const Type& item, UIndex from = 0, USize range = MaxUSize);

	USize					Replace (const Type& oldItem, const Type& newItem, UIndex from = 0, USize range = MaxUSize);

	void					Swap (FixArray& rightOp);

	constexpr USize			GetSize (void) const;
	constexpr bool			IsEmpty (void) const;
	constexpr bool			IsLast  (UIndex idx) const;

		// Content query

	Iterator						Enumerate (void);
	constexpr ConstIterator			Enumerate (void) const;

	template <class Function>
	void							Enumerate	   (Function&& processor);
	template <class Function>
	void							Enumerate	   (Function&& processor) const;
	template <class Function>
	constexpr void					EnumerateConst (Function&& processor) const;

	Iterator						Begin (void);
	constexpr ConstIterator			Begin (void) const;

	Iterator						End	(void);
	constexpr ConstIterator			End	(void) const;

	GeneralIterator					EnumerateGeneral (void);
	constexpr ConstGeneralIterator	EnumerateGeneral (void) const;

	GeneralIterator					BeginGeneral (void);
	constexpr ConstGeneralIterator	BeginGeneral (void) const;

	GeneralIterator					EndGeneral	(void);
	constexpr ConstGeneralIterator	EndGeneral	(void) const;

	ReverseIterator					ReverseEnumerate (void);
	constexpr ConstReverseIterator	ReverseEnumerate (void) const;

	template <class Function>
	void							ReverseEnumerate	  (Function&& processor);
	template <class Function>
	void							ReverseEnumerate	  (Function&& processor) const;
	template <class Function>
	constexpr void					ReverseEnumerateConst (Function&& processor) const;

	ReverseIterator					ReverseBegin (void);
	constexpr ConstReverseIterator	ReverseBegin (void) const;

	ReverseIterator					ReverseEnd	(void);
	constexpr ConstReverseIterator	ReverseEnd	(void) const;

	FastIterator					BeginFast (void);
	constexpr ConstFastIterator		BeginFast (void) const;

	FastIterator					EndFast	(void);
	constexpr ConstFastIterator		EndFast	(void) const;

	Range							operator() (UIndex begin, UIndex end);
	ConstRange						operator() (UIndex begin, UIndex end) const;

	Range							operator() (FromBeginSelector, UIndex end);
	ConstRange						operator() (FromBeginSelector, UIndex end) const;

	Range							operator() (UIndex begin, ToEndSelector);
	ConstRange						operator() (UIndex begin, ToEndSelector) const;

	ReverseRange					Reverse (void);
	ReverseConstRange				Reverse (void) const;

	constexpr ConversionEnumerator	Convert (void) const;

	constexpr auto&					AsConst (void) const gs_lifebound;

	UIndex			FindFirst (const Type& item, UIndex from = 0, USize range = MaxUSize) const;
	UIndex			FindFirst (FunctionRef<bool (const Type&)> condition, UIndex from = 0, USize range = MaxUSize) const;
	UIndex			FindLast  (const Type& item) const;
	UIndex			FindLast  (FunctionRef<bool (const Type&)> condition) const;

	constexpr bool	Contains (const Type& item) const;
	constexpr bool	Contains (FunctionRef<bool (const Type&)> condition) const;
	bool			Contains (std::initializer_list<Type> items) const;
	bool			ContainsOnly (FunctionRef<bool (const Type&)> condition) const;

	USize			Count (const Type& item, UIndex from = 0, USize range = MaxUSize) const;
	USize			Count (FunctionRef<bool (const Type&)> condition, UIndex from = 0, USize range = MaxUSize) const;

	template <class T = Type, class = EnableIf<HasOperatorEquals<T>>>
	constexpr bool	operator== (const FixArray& rightOp) const;

	constexpr bool	operator!= (const FixArray& rightOp) const;

		// I/O

	GSErrCode		Read  (IChannel& ic);
	GSErrCode		Read  (IChannel& ic, FunctionRef<GSErrCode (IChannel&, Type&)> reader);

	GSErrCode		Write (OChannel& oc) const;
	GSErrCode		Write (OChannel& oc, FunctionRef<GSErrCode (OChannel&, const Type&)> writer) const;

		// Low level access

	Type*					GetContent (void) gs_lifebound;
	constexpr const Type*	GetContent (void) const gs_lifebound;

		// Types

	class ConversionEnumerator: public GS::ConversionEnumerator<Type> {
	private:
		const FixArray* source;

	public:
		ConversionEnumerator (const FixArray& source);

		virtual void	Enumerate (const std::function<void (const Type&)>& processor) const override;

		virtual USize	GetSizeHint (void) const override;
	};

private:
	template<class SourceType, USize SourceSize>
	friend class FixArray;

	template<std::size_t... I>
	explicit FixArray (const Type& initialValue, std::index_sequence<I...>);

	template<class SourceType, std::size_t... I>
	explicit FixArray (SourceType (&a)[Size], std::index_sequence<I...>);

	template<class SourceType, std::size_t... I>
	explicit FixArray (SourceType (&&a)[Size], std::index_sequence<I...>);
};


// === FixArray methods ================================================================================================

template <class Type, USize Size>
FixArray<Type, Size>::FixArray ()
{
}


template <class Type, USize Size>
FixArray<Type, Size>::FixArray (const Type& initialValue) : FixArray (initialValue, std::make_index_sequence<Size>{})
{
}


template <class Type, USize Size>
template <class SourceType>
FixArray<Type, Size>::FixArray (SourceType (&a)[Size]) : FixArray (a, std::make_index_sequence<Size>{})
{
}


template <class Type, USize Size>
template <class SourceType>
FixArray<Type, Size>::FixArray (SourceType (&&a)[Size]) : FixArray (std::move(a), std::make_index_sequence<Size>{})
{
}


template <class Type, USize Size>
constexpr FixArray<Type, Size>::FixArray (std::initializer_list<Type> items) : array {}
{
	REF_CHECK (Size >= items.size ());

	UIndex i = 0;
	for (const Type& item : items)
		array[i++] = item;
}


template <class Type, USize Size>
FixArray<Type, Size>::FixArray (const FixArray& source) : FixArray (source.array)
{
}


template <class Type, USize Size>
FixArray<Type, Size>::FixArray (FixArray&& source) : FixArray (std::move (source.array))
{
}


template <class Type, USize Size>
FixArray<Type, Size>&	FixArray<Type, Size>::operator= (const FixArray& source)
{
	for (UIndex i = 0; i < Size; i++)
		array[i] = source.array[i];

	return *this;
}


template <class Type, USize Size>
FixArray<Type, Size>&	FixArray<Type, Size>::operator= (FixArray&& source)
{
	Move (source);

	return *this;
}


template <class Type, USize Size>
template <class SourceType>
FixArray<Type, Size>::FixArray (const FixArray<SourceType, Size>& source) : FixArray (source.array)
{
}


template <class Type, USize Size>
template <class SourceType>
FixArray<Type, Size>&	FixArray<Type, Size>::operator= (const FixArray<SourceType, Size>& source)
{
	static_assert (IsConvertible<SourceType, Type>, "'SourceType' is not convertible to 'Type'.");

	USize i = 0;
	for (const SourceType& item : source)
		array[i++] = item;

	return *this;
}



template <class Type, USize Size>
void	FixArray<Type, Size>::Move (FixArray& source)
{
	if (DBERROR (&source == this))
		return;

	for (UIndex i = 0; i < source.GetSize (); i++)
		array[i] = std::move (source.array[i]);
}


template <class Type, USize Size>
Type&	FixArray<Type, Size>::operator[] (UIndex idx)
{
	REF_CHECK (idx < Size);

	return array[idx];
}


template <class Type, USize Size>
constexpr const Type&	FixArray<Type, Size>::operator[] (UIndex idx) const
{
	REF_CHECK (idx < Size);

	return array[idx];
}


template <class Type, USize Size>
Type&	FixArray<Type, Size>::Get (UIndex idx)
{
	REF_CHECK_R (idx < Size);

	return array[idx];
}


template <class Type, USize Size>
constexpr const Type&	FixArray<Type, Size>::Get (UIndex idx) const
{
	REF_CHECK_R (idx < Size);

	return array[idx];
}


template <class Type, USize Size>
Type&	FixArray<Type, Size>::GetFirst (void)
{
	return array[0];
}


template <class Type, USize Size>
constexpr const Type&	FixArray<Type, Size>::GetFirst (void) const
{
	return array[0];
}


template <class Type, USize Size>
Type&	FixArray<Type, Size>::GetLast (void)
{
	return array[Size - 1];
}


template <class Type, USize Size>
constexpr const Type&	FixArray<Type, Size>::GetLast (void) const
{
	return array[Size - 1];
}


template <class Type, USize Size>
constexpr UIndex	FixArray<Type, Size>::GetLastIndex (void) const
{
	return Size - 1;
}


template <class Type, USize Size>
void		FixArray<Type, Size>::Set (UIndex idx, const Type& item)
{
	REF_CHECK (idx < Size);
	NULL_REF_CHECK (item);

	array[idx] = item;
}


template <class Type, USize Size>
void		FixArray<Type, Size>::Set (UIndex idx, Type&& item)
{
	REF_CHECK (idx < Size);
	NULL_REF_CHECK (item);

	array[idx] = std::move (item);
}


template <class Type, USize Size>
void	FixArray<Type, Size>::Fill (const Type& item, UIndex from, USize range)
{
	NULL_REF_CHECK (item);
	REF_CHECK ((range == MaxUSize && from <= Size) || (range != MaxUSize && from + range <= Size));

	if (range == MaxUSize)
		range = Size - from;

	GS::Fill (array + from, array + from + range, item);
}


template <class Type, USize Size>
USize	FixArray<Type, Size>::Replace (const Type& oldItem, const Type& newItem, UIndex from, USize range)
{
	NULL_REF_CHECK (oldItem);
	NULL_REF_CHECK (newItem);
	REF_CHECK ((range == Size && from <= Size) || (range != Size && from + range <= Size));

	if (range == Size)
		range = Size - from;

	return GS::Replace (array + from, array + from + range, oldItem, newItem);
}


template <class Type, USize Size>
void	FixArray<Type, Size>::Swap (FixArray& rightOp)
{
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (Size == rightOp.GetSize ());

	for (UIndex i = 0; i < Size; i++)
		GS::Swap (array[i], rightOp[i]);
}


template <class Type, USize Size>
constexpr USize	FixArray<Type, Size>::GetSize (void) const
{
	return Size;
}


template <class Type, USize Size>
constexpr bool		FixArray<Type, Size>::IsEmpty (void) const
{
	return false;
}


template <class Type, USize Size>
constexpr bool		FixArray<Type, Size>::IsLast (UIndex idx) const
{
	return (idx == Size - 1);
}


template <class Type, USize Size>
typename FixArray<Type, Size>::Iterator	FixArray<Type, Size>::Enumerate (void)
{
	return Iterator (*this, 0);
}


template <class Type, USize Size>
constexpr typename FixArray<Type, Size>::ConstIterator	FixArray<Type, Size>::Enumerate (void) const
{
	return ConstIterator (*this, 0);
}


template <class Type, USize Size>
template <class Function>
void	FixArray<Type, Size>::Enumerate (Function&& processor)
{
	for (UIndex i = 0; i < Size; i++)
		processor (array[i]);
}


template <class Type, USize Size>
template <class Function>
void	FixArray<Type, Size>::Enumerate (Function&& processor) const
{
	for (UIndex i = 0; i < Size; i++)
		processor (const_cast<const Type&> (array[i]));
}


template <class Type, USize Size>
template <class Function>
constexpr void	FixArray<Type, Size>::EnumerateConst (Function&& processor) const
{
	Enumerate (processor);
}


template <class Type, USize Size>
typename FixArray<Type, Size>::Iterator	FixArray<Type, Size>::Begin (void)
{
	return Iterator (*this, 0);
}


template <class Type, USize Size>
constexpr typename FixArray<Type, Size>::ConstIterator	FixArray<Type, Size>::Begin (void) const
{
	return ConstIterator (*this, 0);
}


template <class Type, USize Size>
typename FixArray<Type, Size>::Iterator	FixArray<Type, Size>::End (void)
{
	return Iterator (*this, Size);
}


template <class Type, USize Size>
constexpr typename FixArray<Type, Size>::ConstIterator	FixArray<Type, Size>::End (void) const
{
	return ConstIterator (*this, Size);
}


template <class Type, USize Size>
typename FixArray<Type, Size>::GeneralIterator	FixArray<Type, Size>::EnumerateGeneral (void)
{
	return GeneralIterator (*this, 0);
}


template <class Type, USize Size>
constexpr typename FixArray<Type, Size>::ConstGeneralIterator	FixArray<Type, Size>::EnumerateGeneral (void) const
{
	return ConstGeneralIterator (*this, 0);
}


template <class Type, USize Size>
typename FixArray<Type, Size>::GeneralIterator	FixArray<Type, Size>::BeginGeneral (void)
{
	return GeneralIterator (*this, 0);
}


template <class Type, USize Size>
constexpr typename FixArray<Type, Size>::ConstGeneralIterator	FixArray<Type, Size>::BeginGeneral (void) const
{
	return ConstGeneralIterator (*this, 0);
}


template <class Type, USize Size>
typename FixArray<Type, Size>::GeneralIterator	FixArray<Type, Size>::EndGeneral (void)
{
	return GeneralIterator (*this, Size);
}


template <class Type, USize Size>
constexpr typename FixArray<Type, Size>::ConstGeneralIterator	FixArray<Type, Size>::EndGeneral (void) const
{
	return ConstGeneralIterator (*this, Size);
}


template <class Type, USize Size>
typename FixArray<Type, Size>::ReverseIterator	FixArray<Type, Size>::ReverseEnumerate (void)
{
	return ReverseIterator (*this, Size - 1);
}


template <class Type, USize Size>
constexpr typename FixArray<Type, Size>::ConstReverseIterator	FixArray<Type, Size>::ReverseEnumerate (void) const
{
	return ConstReverseIterator (*this, Size - 1);
}


template <class Type, USize Size>
template <class Function>
void	FixArray<Type, Size>::ReverseEnumerate (Function&& processor)
{
	for (UIndex i = Size; i > 0; i--)
		processor (array[i - 1]);
}


template <class Type, USize Size>
template <class Function>
void	FixArray<Type, Size>::ReverseEnumerate (Function&& processor) const
{
	for (UIndex i = Size; i > 0; i--)
		processor (const_cast<const Type&> (array[i - 1]));
}


template <class Type, USize Size>
template <class Function>
constexpr void	FixArray<Type, Size>::ReverseEnumerateConst (Function&& processor) const
{
	ReverseEnumerate (processor);
}


template <class Type, USize Size>
typename FixArray<Type, Size>::ReverseIterator	FixArray<Type, Size>::ReverseBegin (void)
{
	return ReverseIterator (*this, Size - 1);
}


template <class Type, USize Size>
constexpr typename FixArray<Type, Size>::ConstReverseIterator	FixArray<Type, Size>::ReverseBegin (void) const
{
	return ConstReverseIterator (*this, Size - 1);
}


template <class Type, USize Size>
typename FixArray<Type, Size>::ReverseIterator	FixArray<Type, Size>::ReverseEnd (void)
{
	return ReverseIterator (*this, -1);
}


template <class Type, USize Size>
constexpr typename FixArray<Type, Size>::ConstReverseIterator	FixArray<Type, Size>::ReverseEnd (void) const
{
	return ConstReverseIterator (*this, -1);
}


template <class Type, USize Size>
typename FixArray<Type, Size>::FastIterator	FixArray<Type, Size>::BeginFast (void)
{
	return array;
}


template <class Type, USize Size>
constexpr typename FixArray<Type, Size>::ConstFastIterator	FixArray<Type, Size>::BeginFast (void) const
{
	return array;
}


template <class Type, USize Size>
typename FixArray<Type, Size>::FastIterator	FixArray<Type, Size>::EndFast (void)
{
	return array + Size;
}


template <class Type, USize Size>
constexpr typename FixArray<Type, Size>::ConstFastIterator	FixArray<Type, Size>::EndFast (void) const
{
	return array + Size;
}


template <class Type, USize Size>
typename FixArray<Type, Size>::Range	FixArray<Type, Size>::operator() (UIndex begin, UIndex end)
{
	return { *this, begin, end };
}


template <class Type, USize Size>
typename FixArray<Type, Size>::ConstRange	FixArray<Type, Size>::operator() (UIndex begin, UIndex end) const
{
	return { *this, begin, end };
}


template <class Type, USize Size>
typename FixArray<Type, Size>::Range	FixArray<Type, Size>::operator() (FromBeginSelector, UIndex end)
{
	return { *this, 0, end };
}


template <class Type, USize Size>
typename FixArray<Type, Size>::ConstRange	FixArray<Type, Size>::operator() (FromBeginSelector, UIndex end) const
{
	return { *this, 0, end };
}


template <class Type, USize Size>
typename FixArray<Type, Size>::Range	FixArray<Type, Size>::operator() (UIndex begin, ToEndSelector)
{
	return { *this, begin, GetSize () };
}


template <class Type, USize Size>
typename FixArray<Type, Size>::ConstRange	FixArray<Type, Size>::operator() (UIndex begin, ToEndSelector) const
{
	return { *this, begin, GetSize () };
}


template <class Type, USize Size>
typename FixArray<Type, Size>::ReverseRange	FixArray<Type, Size>::Reverse (void)
{
	return { *this };
}


template <class Type, USize Size>
typename FixArray<Type, Size>::ReverseConstRange		FixArray<Type, Size>::Reverse (void) const
{
	return { *this };
}


template <class Type, USize Size>
constexpr typename FixArray<Type, Size>::ConversionEnumerator	FixArray<Type, Size>::Convert (void) const
{
	return ConversionEnumerator (*this);
}


template <class Type, USize Size>
constexpr auto&	FixArray<Type, Size>::AsConst (void) const
{
	return reinterpret_cast<const FixArray<typename Container<Type>::template MakeConstPtr<Type>::ConstType, Size>&> (*this);
}

template <class Type, USize Size>
UIndex	FixArray<Type, Size>::FindFirst (const Type& item, UIndex from, USize range) const
{
	NULL_REF_CHECK (item);
	REF_CHECK ((range == MaxUSize && from <= Size) || (range != MaxUSize && from + range <= Size));

	if (range == MaxUSize)
		range = Size - from;

	const Type* it = GS::Find (array + from, array + from + range, item);

	if (it == array + from + range)
		return MaxUIndex;
	else
		return TruncateTo32Bit (it - array);
}


template <class Type, USize Size>
UIndex	FixArray<Type, Size>::FindFirst (const FunctionRef<bool (const Type&)> condition, UIndex from, USize range) const
{
	REF_CHECK ((range == MaxUSize && from <= Size) || (range != MaxUSize && from + range <= Size));

	if (range == MaxUSize)
		range = Size - from;

	const Type* it = GS::Find (array + from, array + from + range, condition);

	if (it == array + from + range)
		return MaxUIndex;
	else
		return TruncateTo32Bit (it - array);
}


template <class Type, USize Size>
UIndex	FixArray<Type, Size>::FindLast (const Type& item) const
{
	NULL_REF_CHECK (item);

	for (UIndex i = Size; i > 0; i--) {
		if (array[i - 1] == item)
			return i - 1;
	}

	return MaxUIndex;
}


template <class Type, USize Size>
UIndex	FixArray<Type, Size>::FindLast (const FunctionRef<bool (const Type&)> condition) const
{
	for (UIndex i = Size; i > 0; i--) {
		if (condition (array[i - 1]))
			return i - 1;
	}

	return MaxUIndex;
}


template <class Type, USize Size>
constexpr bool	FixArray<Type, Size>::Contains (const Type& item) const
{
	NULL_REF_CHECK (item);

	return (GS::Find (array, array + Size, item) != array + Size);
}


template <class Type, USize Size>
constexpr bool	FixArray<Type, Size>::Contains (const FunctionRef<bool (const Type&)> condition) const
{
	return (GS::Find (array, array + Size, condition) != array + Size);
}


template <class Type, USize Size>
bool	FixArray<Type, Size>::Contains (std::initializer_list<Type> items) const
{
	for (const auto& item : items) {
		if (!Contains (item))
			return false;
	}

	return true;
}


template <class Type, USize Size>
bool	FixArray<Type, Size>::ContainsOnly (const FunctionRef<bool (const Type&)> condition) const
{
	for (const Type& item : *this) {
		if (!condition (item))
			return false;
	}

	return true;
}


template <class Type, USize Size>
USize	FixArray<Type, Size>::Count (const Type& item, UIndex from, USize range) const
{
	NULL_REF_CHECK (item);
	REF_CHECK ((range == MaxUSize && from <= Size) || (range != MaxUSize && from + range <= Size));

	if (range == MaxUSize)
		range = Size - from;

	return GS::Count (array + from, array + from + range, item);
}


template <class Type, USize Size>
USize	FixArray<Type, Size>::Count (const FunctionRef<bool (const Type&)> condition, UIndex from, USize range) const
{
	REF_CHECK ((range == MaxUSize && from <= Size) || (range != MaxUSize && from + range <= Size));

	if (range == MaxUSize)
		range = Size - from;

	return GS::Count (array + from, array + from + range, condition);
}


template <class Type, USize Size>
template <class T /*= Type*/, class /*= EnableIf<HasOperatorEquals<T>>*/>
constexpr bool	FixArray<Type, Size>::operator== (const FixArray& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	return (GS::IsEqual (array, array + Size, rightOp.array));
}


template <class Type, USize Size>
constexpr bool	FixArray<Type, Size>::operator!= (const FixArray& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	return !operator== (rightOp);
}


template <class Type, USize Size>
GSErrCode	FixArray<Type, Size>::Read (IChannel& ic)
{
	NULL_REF_CHECK (ic);

	USize sizeOnChannel = 0;

	GSErrCode errorCode = ic.Read (sizeOnChannel);

	if (errorCode != NoError)
		return errorCode;

	if (DBERROR (sizeOnChannel != Size))
		return ErrRead;

	for (UIndex i = 0; i < Size && errorCode == NoError; i++)
		errorCode = ic.Read (array[i]);

	return errorCode;
}


template <class Type, USize Size>
GSErrCode	FixArray<Type, Size>::Read (IChannel& ic, const FunctionRef<GSErrCode (IChannel&, Type&)> reader)
{
	NULL_REF_CHECK (ic);

	USize sizeOnChannel = 0;

	GSErrCode errorCode = ic.Read (sizeOnChannel);

	if (errorCode != NoError)
		return errorCode;

	if (DBERROR (sizeOnChannel != Size))
		return ErrRead;

	for (UIndex i = 0; i < Size && errorCode == NoError; i++)
		errorCode = reader (ic, array[i]);

	return errorCode;
}


template <class Type, USize Size>
GSErrCode	FixArray<Type, Size>::Write (OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	GSErrCode errorCode = oc.Write (Size);

	if (errorCode != NoError)
		return errorCode;

	for (UIndex i = 0; i < Size && errorCode == NoError; i++)
		errorCode = oc.Write (array[i]);

	return errorCode;
}


template <class Type, USize Size>
GSErrCode	FixArray<Type, Size>::Write (OChannel& oc, const FunctionRef<GSErrCode (OChannel&, const Type&)> writer) const
{
	NULL_REF_CHECK (oc);

	GSErrCode errorCode = oc.Write (Size);

	if (errorCode != NoError)
		return errorCode;

	for (UIndex i = 0; i < Size && errorCode == NoError; i++)
		errorCode = writer (oc, array[i]);

	return errorCode;
}


template <class Type, USize Size>
Type*	FixArray<Type, Size>::GetContent (void)
{
	return array;
}


template <class Type, USize Size>
constexpr const Type*	FixArray<Type, Size>::GetContent (void) const
{
	return array;
}


template <class Type, USize Size>
FixArray<Type, Size>::ConversionEnumerator::ConversionEnumerator (const FixArray& source):
	source (&source)
{
}


template <class Type, USize Size>
void	FixArray<Type, Size>::ConversionEnumerator::Enumerate (const std::function<void (const Type&)>& processor) const
{
	source->Enumerate (processor);
}


template <class Type, USize Size>
USize	FixArray<Type, Size>::ConversionEnumerator::GetSizeHint (void) const
{
	return source->GetSize ();
}


template <class Type, USize Size>
template<std::size_t... I>
FixArray<Type, Size>::FixArray (const Type& initialValue, std::index_sequence<I...>) : array {(I, initialValue)...}
{
}


template <class Type, USize Size>
template<class SourceType, std::size_t... I>
FixArray<Type, Size>::FixArray (SourceType (&a)[Size], std::index_sequence<I...>) : array {a[I]...}
{
}


template <class Type, USize Size>
template<class SourceType, std::size_t... I>
FixArray<Type, Size>::FixArray (SourceType (&&a)[Size], std::index_sequence<I...>) : array {std::move(a[I])...}
{
}


template <class SourceType, USize Size>
explicit FixArray (SourceType (&a)[Size])->FixArray<GS::RemoveCV<SourceType>, Size>;


template <class SourceType, USize Size>
explicit FixArray (SourceType (&&a)[Size])->FixArray<GS::RemoveCV<SourceType>, Size>;


// === class FixArrayInserter ==========================================================================================



// === Global functions ================================================================================================

template <class Type, USize Size>
auto		begin (FixArray<Type, Size>& array)
{
	return array.BeginFast ();
}


template <class Type, USize Size>
auto		end (FixArray<Type, Size>& array)
{
	return array.EndFast ();
}


template <class Type, USize Size>
auto		begin (const FixArray<Type, Size>& array)
{
	return array.BeginFast ();
}


template <class Type, USize Size>
auto		end (const FixArray<Type, Size>& array)
{
	return array.EndFast ();
}


// === class Inserter ==================================================================================================

template <class Type, USize Size>
class FixArrayInserter {
private:
	FixArray<Type, Size>*	fixArray;
	mutable UInt32			i = 0;

public:
	using DecayedFirstArgumentType = Type;

	explicit FixArrayInserter (FixArray<Type, Size>* fixArray) :
		fixArray (fixArray)
	{
	}

	void	operator() (const Type& value) const
	{
		DBASSERT (i < Size);
		fixArray->Set (i, value);
		++i;
	}

	void	operator() (Type&& value) const
	{
		DBASSERT (i < Size);
		fixArray->Set (i, std::move (value));
		++i;
	}
};


template <class Type, USize Size>
auto	GetInserter (FixArray<Type, Size>& fixArray)
{
	return FixArrayInserter<Type, Size> (&fixArray);
}


}	// namespace GS


#endif
