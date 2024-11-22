
// *****************************************************************************
//
//                                  Class Array
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined ARRAY_HPP
#define ARRAY_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "RandomContainer.hpp"

#include "RandomContainerIterator.hpp"
#include "RandomContainerReverseIterator.hpp"
#include "Enumerator.hpp"
#include "BaseAlgorithms.hpp"
#include "PushInserter.hpp"
#include "ClassInfo.hpp"
#include "IOFrame.hpp"
#include "Channel.hpp"
#include "Inserter.hpp"

#include <new>
#include <utility>
#include <functional>

#include "ConditionalView.hpp"

// ================================ Class Array ================================

namespace GS {

class GSROOT_DLL_EXPORT ArrayPrivate {
public:
	static GS::ClassInfo	classInfo;	// Array's private classInfo
};


template <class Type>
class Array: public RandomContainer<Type> {
private:
	Type*	array = nullptr;	// array storing items
	USize	capacity = 0;		// capacity of the array (in items)
	USize	size = 0;			// number of items in the array

	void			IncreaseCapacity (USize minCapacity);
	void			DecreaseCapacity (USize minCapacity);
	void			AdjustCapacity   (USize minCapacity);
	virtual void	Reallocate	     (USize minCapacity);

	void			SetIncreasedSize (USize increasedSize);
	void			SetDecreasedSize (USize decreasedSize);

protected:
					Array (char* initialBuffer, USize initialCapacity);
	void			SetContent (Type* newArray, USize newSize, USize newCapacity);

	virtual USize	GetMinBufferCapacity () const;
	virtual Type*	AllocateNewBuffer	 (USize bufferCapacity, const Type* oldBuffer);
	virtual void	DeleteBuffer		 (Type* buffer);
	virtual bool	IsIndependentBuffer  (const Type* buffer) const;

public:
		// Types

	using Iterator =				RandomContainerIterator<Array>;
	using ConstIterator =			ConstRandomContainerIterator<Array>;

	using GeneralIterator =			GeneralRandomContainerIterator<Array>;
	using ConstGeneralIterator =	ConstGeneralRandomContainerIterator<Array>;

	using ReverseIterator =			RandomContainerReverseIterator<Array>;
	using ConstReverseIterator =	ConstRandomContainerReverseIterator<Array>;

	using Range =					RandomContainerRange<Array>;
	using ConstRange =				RandomContainerConstRange<Array>;

	using ReverseRange =			RandomContainerReverseRange<Array>;
	using ReverseConstRange =		RandomContainerReverseConstRange<Array>;

	using FastIterator = 			Type*;
	using ConstFastIterator =		const Type*;

	class ConversionEnumerator;

		// Constructors

	Array ();
	explicit Array (USize initialCapacity);
	explicit Array (ConstIterator begin);
	explicit Array (ConstForwardIterator<Type> begin);
	explicit Array (ConstForwardIterator<Type> begin, ConstForwardIterator<Type> end); 
	Array (const GS::ConversionEnumerator<Type>& enumerator);
	Array (std::initializer_list<Type> items);
	Array (const Array& source);
	Array (Array&& source);
	Array (const Array&&) = delete;

	template <class SourceType>
	explicit Array (const Array<SourceType>& source);

	template <class SourceType>
	explicit Array (Array<SourceType>&& source);

	Array&	operator= (const Array& source);
	Array&	operator= (Array&& source);
	Array&	operator= (const GS::ConversionEnumerator<Type>& enumerator);

	template <class SourceType>
	Array&	operator= (const Array<SourceType>& source);

	template <class SourceType>
	Array&	operator= (Array<SourceType>&& source);

	virtual ~Array ();


		// Type conversion constructors

	void		Move (Array& source);
	void		Move (const std::function<void (Type&&)>& processor);

		// Item access

	Type&		operator[] (UIndex idx);
	const Type&	operator[] (UIndex idx) const;

	Type&		Get (UIndex idx);
	const Type&	Get (UIndex idx) const;

	Type&		GetFirst ();
	const Type&	GetFirst () const;

	Type&		GetLast ();
	const Type&	GetLast () const;
	UIndex		GetLastIndex () const;

	void		Set (UIndex idx, const Type& item);
	void		Set (UIndex idx, Type&& item);

		// Content management

	void	Fill (const Type& item, UIndex from = 0, USize range = MaxUSize);

	USize	Replace (const Type& oldItem, const Type& newItem, UIndex from = 0, USize range = MaxUSize);

	void	Insert (UIndex to, const Type& item);
	void	Insert (UIndex to, Type&& item);
	void	Insert (UIndex to, ConstIterator begin);
	void	Insert (UIndex to, ConstIterator begin, ConstIterator end);
	void	Insert (UIndex to, ConstForwardIterator<Type> begin);
	void	Insert (UIndex to, ConstForwardIterator<Type> begin, ConstForwardIterator<Type> end);

	void	Append (const Array& items);
	void	Append (Array&& items);

	void	Delete		(UIndex idx);
	void	Delete		(UIndex from, USize range);
	void	DeleteLast	();

	UIndex	DeleteFirst	(const Type& item);
	UIndex	DeleteFirst	(const std::function<bool (const Type&)>& condition);
	UIndex	DeleteLast	(const Type& item);
	UIndex	DeleteLast	(const std::function<bool (const Type&)>& condition);
	void	DeleteAll	(const Type& item);
	void	DeleteAll	(const std::function<bool (const Type&)>& condition);

	void	Clear (bool keepCapacity = false);

	void	Swap (Array& rightOp);

	void	Push (const Type& item);
	void	Push (Type&& item);

	template <class... ItemParameters>
	void	PushNew (ItemParameters&&... itemParameters);
	
	void	Pop	(Type* item);
	Type	Pop	();

	USize	GetSize			() const;
	bool	IsEmpty			() const;
	bool	IsLast			(UIndex idx) const;
	void	SetSize			(USize newSize);
	void	IncreaseSize	(USize sizeIncrement);
	void	EnsureSize		(USize requiredSize);

		// Content query

	Iterator		Enumerate ();
	ConstIterator	Enumerate () const;

	template <class Function>
	void			Enumerate	   (Function&& processor);
	template <class Function>
	void			Enumerate	   (Function&& processor) const;
	template <class Function>
	void			EnumerateConst (Function&& processor) const;

	Iterator		Begin ();
	ConstIterator	Begin () const;

	Iterator		End	();
	ConstIterator	End	() const;

	GeneralIterator			EnumerateGeneral ();
	ConstGeneralIterator	EnumerateGeneral () const;

	GeneralIterator			BeginGeneral ();
	ConstGeneralIterator	BeginGeneral () const;

	GeneralIterator			EndGeneral	();
	ConstGeneralIterator	EndGeneral	() const;

	ReverseIterator			ReverseEnumerate ();
	ConstReverseIterator	ReverseEnumerate () const;

	template <class Function>
	void	ReverseEnumerate	  (Function&& processor);
	template <class Function>
	void	ReverseEnumerate	  (Function&& processor) const;
	template <class Function>
	void	ReverseEnumerateConst (Function&& processor) const;

	ReverseIterator			ReverseBegin ();
	ConstReverseIterator	ReverseBegin () const;

	ReverseIterator			ReverseEnd	();
	ConstReverseIterator	ReverseEnd	() const;

	FastIterator			BeginFast ();
	ConstFastIterator		BeginFast () const;

	FastIterator			EndFast	();
	ConstFastIterator		EndFast	() const;

	Range					operator() (UIndex begin, UIndex end);
	ConstRange				operator() (UIndex begin, UIndex end) const;

	Range					operator() (FromBeginSelector, UIndex end);
	ConstRange				operator() (FromBeginSelector, UIndex end) const;

	Range					operator() (UIndex begin, ToEndSelector);
	ConstRange				operator() (UIndex begin, ToEndSelector) const;

	ReverseRange			Reverse ();
	ReverseConstRange		Reverse () const;

	ConversionEnumerator	Convert () const;

	auto&					AsConst () const;

	UIndex	FindFirst (const Type& item, UIndex from = 0, USize range = MaxUSize) const;
	UIndex	FindFirst (const std::function<bool (const Type&)>& condition, UIndex from = 0, USize range = MaxUSize) const;
	UIndex	FindLast  (const Type& item) const;
	UIndex	FindLast  (const std::function<bool (const Type&)>& condition) const;

	bool	Contains	 (const Type& item) const;
	bool	Contains	 (const std::function<bool (const Type&)>& condition) const;
	bool	Contains	 (std::initializer_list<Type> items) const;
	bool	ContainsOnly (const std::function<bool (const Type&)>& condition) const;

	USize	Count (const Type& item, UIndex from = 0, USize range = MaxUSize) const;
	USize	Count (const std::function<bool (const Type&)>& condition, UIndex from = 0, USize range = MaxUSize) const;

	Array	Select (const std::function<bool (const Type&)>& condition) const;

	template <class ResultType>
	Array<ResultType>	Transform (const std::function<ResultType (const Type&)>& transformation) const;

	template <class ResultType>
	Array<ResultType>	Transform () const;

	template <class Condition>
	decltype (auto)		Where (Condition&& condition) const&;

	template <class Condition>
	decltype (auto)		Where (Condition&& condition) &&;

		// Equality operations

	template <class T = Type, class = EnableIf<HasOperatorEquals<T>>>
	bool	operator== (const Array& rightOp) const;

	bool	operator!= (const Array& rightOp) const;

	bool	IsEqual    (std::initializer_list<Type> rightOp) const;

		// Performance tuning

	USize	GetCapacity	() const;
	void	SetCapacity (USize newCapacity);

	void	EnsureCapacity (USize minCapacity);

		// I/O

	GSErrCode	Read  (IChannel& ic);
	GSErrCode	Read  (IChannel& ic, const std::function<GSErrCode (IChannel&, Type&)>& reader);

	GSErrCode	Write (OChannel& oc) const;
	GSErrCode	Write (OChannel& oc, const std::function<GSErrCode (OChannel&, const Type&)>& writer) const;

		// Low level access

	Type*		GetContent ();
	const Type*	GetContent () const;

		// Debug

	void	Print	   (OChannel& oc) const;
	void	Dump	   (OChannel& oc) const;
	bool	CheckState () const;

		// Types

	class ConversionEnumerator: public GS::ConversionEnumerator<Type> {
	private:
		const Array* source;

	public:
		ConversionEnumerator (const Array& source);

		virtual void	Enumerate (const std::function<void (const Type&)>& processor) const override;

		virtual USize	GetSizeHint (void) const override;
	};
};

// === Array methods ===================================================================================================

template <class Type>
Array<Type>::Array () = default;


template <class Type>
Array<Type>::Array (USize initialCapacity)
{
	IncreaseCapacity (initialCapacity);
}


template <class Type>
Array<Type>::Array (ConstIterator begin)
{
	while (begin != nullptr) {
		Push (*begin);
		++begin;
	}
}


template <class Type>
Array<Type>::Array (ConstForwardIterator<Type> begin)
{
	while (begin != nullptr) {
		Push (*begin);
		++begin;
	}
}


template <class Type>
Array<Type>::Array (ConstForwardIterator<Type> begin, ConstForwardIterator<Type> end)
{
	while (begin != end) {
		Push (*begin);
		++begin;
	}
}


template <class Type>
Array<Type>::Array (const GS::ConversionEnumerator<Type>& enumerator)
{
	SetCapacity (enumerator.GetSizeHint ());

	enumerator.Enumerate (GetInserter (*this));
}


template <class Type>
template <class SourceType>
Array<Type>::Array (const Array<SourceType>& source)
{
	static_assert (IsConvertible<SourceType, Type>, "'SourceType' is not convertible to 'Type'.");

	IncreaseCapacity (source.GetSize ());

	UIndex i = 0;
	for (const SourceType& item : source)
		::new (&array[i++]) Type (item);

	size = source.GetSize ();
}


template <class Type>
template <class SourceType>
Array<Type>::Array (Array<SourceType>&& source)
{
	static_assert (IsConstructible<Type, SourceType&&>, "'Type' is not constructible from 'SourceType&&'.");

	IncreaseCapacity (source.GetSize ());

	UIndex i = 0;
	for (SourceType& item : source)
		::new (&array[i++]) Type (std::move (item));

	size = source.GetSize ();

	source.Clear ();
}


template <class Type>
template <class SourceType>
Array<Type>&	Array<Type>::operator= (const Array<SourceType>& source)
{
	static_assert (IsConvertible<SourceType, Type>, "'SourceType' is not convertible to 'Type'.");

	Clear (true);

	AdjustCapacity (source.GetSize ());

	UIndex i = 0;
	for (const SourceType& item : source)
		::new (&array[i++]) Type (item);
	size = source.GetSize ();

	return *this;
}


template <class Type>
template <class SourceType>
Array<Type>&	Array<Type>::operator= (Array<SourceType>&& source)
{
	static_assert (IsConstructible<Type, SourceType&&>, "'Type' is not constructible from 'SourceType&&'.");

	Clear (true);

	AdjustCapacity (source.GetSize ());

	UIndex i = 0;
	for (SourceType& item : source)
		::new (&array[i++]) Type (std::move (item));
	size = source.GetSize ();

	source.Clear ();

	return *this;
}


template <class Type>
Array<Type>::Array (std::initializer_list<Type> items)
{
	IncreaseCapacity (USize (items.size ()));

	UIndex i = 0;
	for (const Type& item : items)
		::new (&array[i++]) Type (item);
	size = USize (items.size ());
}


template <class Type>
Array<Type>::Array (const Array& source)
{
	IncreaseCapacity (source.size);

	for (UIndex i = 0; i < source.size; i++)
		::new (&array[i]) Type (source.array[i]);
	size = source.size;
}


template <class Type>
Array<Type>::Array (Array&& source)
{
	Move (source);
}


template <class Type>
Array<Type>&	Array<Type>::operator= (const Array& source)
{
	if (&source != this) {
		Clear (true);

		AdjustCapacity (source.size);

		for (UIndex i = 0; i < source.size; i++)
			::new (&array[i]) Type (source.array[i]);
		size = source.size;
	}
	
	return *this;
}


template <class Type>
Array<Type>&	Array<Type>::operator= (Array&& source)
{
	Move (source);

	return *this;
}


template <class Type>
Array<Type>&	Array<Type>::operator= (const GS::ConversionEnumerator<Type>& enumerator)
{
	Clear (true);
	AdjustCapacity (enumerator.GetSizeHint ());

	enumerator.Enumerate ([&] (const Type& item) {
		Push (item);
	});

	return *this;
}


template <class Type>
Array<Type>::~Array ()
{
	Clear ();
}


template <class Type>
void	Array<Type>::Move (Array& source)
{
	if (DBERROR (&source == this))
		return;

	if (IsIndependentBuffer (array) && source.IsIndependentBuffer (source.array)) {
		GS::Swap (array,	source.array);
		GS::Swap (capacity, source.capacity);
		GS::Swap (size,		source.size);
	} else {
		Clear (true);

		AdjustCapacity (source.size);

		for (UIndex i = 0; i < source.size; i++)
			::new (&array[i]) Type (std::move (source.array[i]));
		size = source.size;
	}

	source.Clear ();
}


template <class Type>
void	Array<Type>::Move (const std::function<void (Type&&)>& processor)
{
	for (UIndex i = 0; i < size; ++i) {
		processor (std::move (array[i]));
	}

	Clear ();
}


template <class Type>
Type&	Array<Type>::operator[] (UIndex idx)
{
	REF_CHECK (idx < size);

	return array[idx];
}


template <class Type>
const Type&		Array<Type>::operator[] (UIndex idx) const
{
	REF_CHECK (idx < size);

	return array[idx];
}


template <class Type>
Type&	Array<Type>::Get (UIndex idx)
{
	REF_CHECK_R (idx < size);

	return array[idx];
}


template <class Type>
const Type&		Array<Type>::Get (UIndex idx) const
{
	REF_CHECK_R (idx < size);

	return array[idx];
}


template <class Type>
Type&	Array<Type>::GetFirst ()
{
	PRECOND (size != 0);

	return array[0];
}


template <class Type>
const Type&		Array<Type>::GetFirst () const
{
	PRECOND (size != 0);

	return array[0];
}


template <class Type>
Type&	Array<Type>::GetLast ()
{
	PRECOND (size != 0);

	return array[size - 1];
}


template <class Type>
const Type&		Array<Type>::GetLast () const
{
	PRECOND (size != 0);

	return array[size - 1];
}


template <class Type>
UIndex	Array<Type>::GetLastIndex () const
{
	PRECOND (size != 0);

	return size - 1;
}


template <class Type>
void	Array<Type>::Set (UIndex idx, const Type& item)
{
	REF_CHECK (idx < size);
	NULL_REF_CHECK (item);

	array[idx] = item;
}


template <class Type>
void	Array<Type>::Set (UIndex idx, Type&& item)
{
	REF_CHECK (idx < size);
	NULL_REF_CHECK (item);

	array[idx] = std::move (item);
}


template <class Type>
void	Array<Type>::Fill (const Type& item, UIndex from, USize range)
{
	NULL_REF_CHECK (item);
	REF_CHECK ((range == MaxUSize && from <= size) || (range != MaxUSize && from + range <= size));

	if (range == MaxUSize)
		range = size - from;

	GS::Fill (array + from, array + from + range, item);
}


template <class Type>
USize	Array<Type>::Replace (const Type& oldItem, const Type& newItem, UIndex from, USize range)
{
	NULL_REF_CHECK (oldItem);
	NULL_REF_CHECK (newItem);
	REF_CHECK ((range == MaxUSize && from <= size) || (range != MaxUSize && from + range <= size));

	if (range == MaxUSize)
		range = size - from;

	return GS::Replace (array + from, array + from + range, oldItem, newItem);
}


template <class Type>
void	Array<Type>::Insert (UIndex to, const Type& item)
{
	REF_CHECK (to <= size);
	NULL_REF_CHECK (item);

	if (&item >= array && &item < array + size) {	// is item in the array ?
		Type temp = item;
		Insert (to, std::move (temp));
		return;
	}

	IncreaseCapacity (size + 1);

	if (size == to) {
		::new (&array[size]) Type (item);
	} else { // size > 0 for sure
		::new (&array[size]) Type (std::move (array[size - 1]));
		for (UIndex i = size - 1; i > to; i--)
			array[i] = std::move (array[i - 1]);
		array[to] = item;
	}

	size++;
}


template <class Type>
void	Array<Type>::Insert (UIndex to, Type&& item)
{
	REF_CHECK (to <= size);
	NULL_REF_CHECK (item);
	DBASSERT (&item < array || &item >= array + size);		// item should not be in the array

	IncreaseCapacity (size + 1);

	if (size == to) {
		::new (&array[size]) Type (std::move (item));
	} else { // size > 0 for sure
		::new (&array[size]) Type (std::move (array[size - 1]));
		for (UIndex i = size - 1; i > to; i--)
			array[i] = std::move (array[i - 1]);
		array[to] = std::move (item);
	}

	size++;
}


template <class Type>
void	Array<Type>::Insert (UIndex to, ConstIterator begin)
{
	REF_CHECK (to <= size);

	while (begin != nullptr) {
		Insert (to, *begin);
		to++;
		++begin;
	}
}


template <class Type>
void	Array<Type>::Insert (UIndex to, ConstIterator begin, ConstIterator end)
{
	REF_CHECK (to <= size);

	while (begin != end) {
		Insert (to, *begin);
		to++;
		++begin;
	}
}


template <class Type>
void	Array<Type>::Insert (UIndex to, ConstForwardIterator<Type> begin)
{
	REF_CHECK (to <= size);

	while (begin != nullptr) {
		Insert (to, *begin);
		to++;
		++begin;
	}
}


template <class Type>
void	Array<Type>::Insert (UIndex to, ConstForwardIterator<Type> begin, ConstForwardIterator<Type> end)
{
	REF_CHECK (to <= size);

	while (begin != end) {
		Insert (to, *begin);
		to++;
		++begin;
	}
}


template <class Type>
void	Array<Type>::Append (const Array& items)
{
	NULL_REF_CHECK (items);

	if (&items == this) {
		Array temp = items;
		Append (std::move (temp));
		return;
	}

	IncreaseCapacity (size + items.GetSize ());

	for (UIndex i = 0; i < items.GetSize (); i++)
		::new (&array[size + i]) Type (items[i]);

	size += items.GetSize ();
}


template <class Type>
void	Array<Type>::Append (Array&& items)
{
	NULL_REF_CHECK (items);

	IncreaseCapacity (size + items.GetSize ());

	for (UIndex i = 0; i < items.GetSize (); i++)
		::new (&array[size + i]) Type (std::move (items[i]));

	size += items.GetSize ();
}


template <class Type>
void	Array<Type>::Delete (UIndex idx)
{
	REF_CHECK (idx < size);

	for (UIndex i = idx + 1; i < size; i++)
		array[i - 1] = std::move (array[i]);

	array[size - 1].~Type ();
	size--;

	DecreaseCapacity (size);
}


template <class Type>
void	Array<Type>::Delete (UIndex from, USize range)
{
	REF_CHECK (from + range <= size);

	if (range == 0)
		return;

	for (UIndex i = from + range; i < size; i++)
		array[i - range] = std::move (array[i]);

	for (UIndex j = size - range; j < size; j++)
		array[j].~Type ();
	size -= range;

	DecreaseCapacity (size);
}


template <class Type>
void	Array<Type>::DeleteLast ()
{
	array[size - 1].~Type ();
	size--;

	DecreaseCapacity (size);
}


template <class Type>
UIndex	Array<Type>::DeleteFirst (const Type& item)
{
	NULL_REF_CHECK (item);

	UIndex first = FindFirst (item);
	if (first != MaxUIndex)
		Delete (first);

	return first;
}


template <class Type>
UIndex	Array<Type>::DeleteFirst (const std::function<bool (const Type&)>& condition)
{
	NULL_REF_CHECK (condition);

	UIndex first = FindFirst (condition);
	if (first != MaxUIndex)
		Delete (first);

	return first;
}


template <class Type>
UIndex	Array<Type>::DeleteLast (const Type& item)
{
	NULL_REF_CHECK (item);

	UIndex last = FindLast (item);
	if (last != MaxUIndex)
		Delete (last);

	return last;
}


template <class Type>
UIndex	Array<Type>::DeleteLast (const std::function<bool (const Type&)>& condition)
{
	NULL_REF_CHECK (condition);

	UIndex last = FindLast (condition);
	if (last != MaxUIndex)
		Delete (last);

	return last;
}


template <class Type>
void	Array<Type>::DeleteAll (const Type& item)
{
	NULL_REF_CHECK (item);

	UIndex toDelete = FindFirst (item);

	if (toDelete == MaxUIndex)
		return;

	for (UIndex i = toDelete + 1; i < GetSize (); i++) {
		if (!(array[i] == item)) {
			array[toDelete] = std::move (array[i]);
			toDelete++;
		}
	}

	SetDecreasedSize (toDelete);
}


template <class Type>
void	Array<Type>::DeleteAll (const std::function<bool (const Type&)>& condition)
{
	NULL_REF_CHECK (condition);

	UIndex toDelete = FindFirst (condition);

	if (toDelete == MaxUIndex)
		return;

	for (UIndex i = toDelete + 1; i < GetSize (); i++) {
		if (!condition (array[i])) {
			array[toDelete] = std::move (array[i]);
			toDelete++;
		}
	}

	SetDecreasedSize (toDelete);
}


template <class Type>
void	Array<Type>::Clear (bool keepCapacity)
{
	for (UIndex i = 0; i < size; i++)
		array[i].~Type ();

	if (!keepCapacity) {
		DeleteBuffer (array);
		array = nullptr;
		capacity = 0;
	}

	size = 0;
}


template <class Type>
void	Array<Type>::Swap (Array& rightOp)
{
	NULL_REF_CHECK (rightOp);

	if (IsIndependentBuffer (array) && rightOp.IsIndependentBuffer (rightOp.array)) {
		GS::Swap (array,	rightOp.array);
		GS::Swap (capacity, rightOp.capacity);
		GS::Swap (size,		rightOp.size);
	} else {
		Array* largeArray = this;
		Array* smallArray = &rightOp;
		if (largeArray->GetSize () < smallArray->GetSize ())
			GS::Swap (largeArray, smallArray);

		USize smallArraySize = smallArray->GetSize ();

		for (UIndex i = 0; i < smallArraySize; i++)
			GS::Swap ((*smallArray)[i], (*largeArray)[i]);

		for (UIndex i = smallArraySize; i < largeArray->GetSize (); i++)
			smallArray->Push ((*largeArray)[i]);

		largeArray->SetDecreasedSize (smallArraySize);
	}
}



template <class Type>
void	Array<Type>::Push (const Type& item)
{
	NULL_REF_CHECK (item);

	if (&item >= array && &item < array + size) {	// is item in the array ?
		Type temp = item;
		Push (std::move (temp));
		return;
	}

	IncreaseCapacity (size + 1);

	::new (&array[size]) Type (item);
	size++;
}


template <class Type>
void	Array<Type>::Push (Type&& item)
{
	NULL_REF_CHECK (item);
	DBASSERT (&item < array || &item >= array + size);		// item should not be in the array

	IncreaseCapacity (size + 1);

	::new (&array[size]) Type (std::move (item));
	size++;
}


template <class Type>
template <class... ItemParameters>
void	Array<Type>::PushNew (ItemParameters&&... itemParameters)
{
	IncreaseCapacity (size + 1);

	::new (&array[size]) Type { std::forward<ItemParameters> (itemParameters)... };
	size++;
}


template <class Type>
void	Array<Type>::Pop (Type* item)
{
	PRECOND (size != 0);
	NULL_PTR_CHECK (item);

	*item = std::move (array[size - 1]);

	array[size - 1].~Type ();
	size--;

	DecreaseCapacity (size);
}


template <class Type>
Type	Array<Type>::Pop ()
{
	PRECOND (size != 0);

	Type result = std::move (array[size - 1]);

	array[size - 1].~Type ();
	size--;

	DecreaseCapacity (size);

	return result;
}


template <class Type>
USize	Array<Type>::GetSize () const
{
	return size;
}


template <class Type>
bool		Array<Type>::IsEmpty () const
{
	return (size == 0);
}


template <class Type>
bool		Array<Type>::IsLast (UIndex idx) const
{
	return (size > 0 && idx == size - 1);
}


template <class Type>
void	Array<Type>::SetSize (USize newSize)
{
	if (newSize < size)
		SetDecreasedSize (newSize);
	else if (newSize > size)
		SetIncreasedSize (newSize);
}


template <class Type>
void	Array<Type>::IncreaseSize (USize sizeIncrement)
{
	SetSize (size + sizeIncrement);
}


template <class Type>
void	Array<Type>::EnsureSize (USize requiredSize)
{
	if (size < requiredSize)
		SetSize (requiredSize);
}


template <class Type>
typename Array<Type>::Iterator	Array<Type>::Enumerate ()
{
	return Iterator (*this, 0);
}


template <class Type>
typename Array<Type>::ConstIterator	Array<Type>::Enumerate () const
{
	return ConstIterator (*this, 0);
}


template <class Type>
template <class Function>
void	Array<Type>::Enumerate (Function&& processor)
{
	for (UIndex i = 0; i < size; i++)
		processor (array[i]);
}


template <class Type>
template <class Function>
void	Array<Type>::Enumerate (Function&& processor) const
{
	for (UIndex i = 0; i < size; i++)
		processor (const_cast<const Type&> (array[i]));
}


template <class Type>
template <class Function>
void	Array<Type>::EnumerateConst (Function&& processor) const
{
	Enumerate (processor);
}


template <class Type>
typename Array<Type>::Iterator	Array<Type>::Begin ()
{
	return Iterator (*this, 0);
}


template <class Type>
typename Array<Type>::ConstIterator	Array<Type>::Begin () const
{
	return ConstIterator (*this, 0);
}


template <class Type>
typename Array<Type>::Iterator	Array<Type>::End ()
{
	return Iterator (*this, size);
}


template <class Type>
typename Array<Type>::ConstIterator	Array<Type>::End () const
{
	return ConstIterator (*this, size);
}


template <class Type>
typename Array<Type>::GeneralIterator	Array<Type>::EnumerateGeneral ()
{
	return GeneralIterator (*this, 0);
}


template <class Type>
typename Array<Type>::ConstGeneralIterator	Array<Type>::EnumerateGeneral () const
{
	return ConstGeneralIterator (*this, 0);
}


template <class Type>
typename Array<Type>::GeneralIterator	Array<Type>::BeginGeneral ()
{
	return GeneralIterator (*this, 0);
}


template <class Type>
typename Array<Type>::ConstGeneralIterator	Array<Type>::BeginGeneral () const
{
	return ConstGeneralIterator (*this, 0);
}


template <class Type>
typename Array<Type>::GeneralIterator	Array<Type>::EndGeneral ()
{
	return GeneralIterator (*this, size);
}


template <class Type>
typename Array<Type>::ConstGeneralIterator	Array<Type>::EndGeneral () const
{
	return ConstGeneralIterator (*this, size);
}


template <class Type>
typename Array<Type>::ReverseIterator	Array<Type>::ReverseEnumerate ()
{
	return ReverseIterator (*this, size - 1);
}


template <class Type>
typename Array<Type>::ConstReverseIterator	Array<Type>::ReverseEnumerate () const
{
	return ConstReverseIterator (*this, size - 1);
}


template <class Type>
template <class Function>
void	Array<Type>::ReverseEnumerate (Function&& processor)
{
	for (UIndex i = size; i > 0; i--)
		processor (array[i - 1]);
}


template <class Type>
template <class Function>
void	Array<Type>::ReverseEnumerate (Function&& processor) const
{
	for (UIndex i = size; i > 0; i--)
		processor (const_cast<const Type&> (array[i - 1]));
}


template <class Type>
template <class Function>
void	Array<Type>::ReverseEnumerateConst (Function&& processor) const
{
	ReverseEnumerate (processor);
}


template <class Type>
typename Array<Type>::ReverseIterator	Array<Type>::ReverseBegin ()
{
	return ReverseIterator (*this, size - 1);
}


template <class Type>
typename Array<Type>::ConstReverseIterator	Array<Type>::ReverseBegin () const
{
	return ConstReverseIterator (*this, size - 1);
}


template <class Type>
typename Array<Type>::ReverseIterator	Array<Type>::ReverseEnd ()
{
	return ReverseIterator (*this, -1);
}


template <class Type>
typename Array<Type>::ConstReverseIterator	Array<Type>::ReverseEnd () const
{
	return ConstReverseIterator (*this, -1);
}


template <class Type>
typename Array<Type>::FastIterator	Array<Type>::BeginFast ()
{
	return array;
}


template <class Type>
typename Array<Type>::ConstFastIterator	Array<Type>::BeginFast () const
{
	return array;
}


template <class Type>
typename Array<Type>::FastIterator	Array<Type>::EndFast ()
{
	return array + size;
}


template <class Type>
typename Array<Type>::ConstFastIterator	Array<Type>::EndFast () const
{
	return array + size;
}


template <class Type>
typename Array<Type>::Range		Array<Type>::operator() (UIndex begin, UIndex end)
{
	return { *this, begin, end };
}


template <class Type>
typename Array<Type>::ConstRange	Array<Type>::operator() (UIndex begin, UIndex end) const
{
	return { *this, begin, end };
}


template <class Type>
typename Array<Type>::Range		Array<Type>::operator() (FromBeginSelector, UIndex end)
{
	return { *this, 0, end };
}


template <class Type>
typename Array<Type>::ConstRange	Array<Type>::operator() (FromBeginSelector, UIndex end) const
{
	return { *this, 0, end };
}


template <class Type>
typename Array<Type>::Range		Array<Type>::operator() (UIndex begin, ToEndSelector)
{
	return { *this, begin, GetSize () };
}


template <class Type>
typename Array<Type>::ConstRange	Array<Type>::operator() (UIndex begin, ToEndSelector) const
{
	return { *this, begin, GetSize () };
}


template <class Type>
typename Array<Type>::ReverseRange	Array<Type>::Reverse ()
{
	return { *this };
}


template <class Type>
typename Array<Type>::ReverseConstRange	Array<Type>::Reverse () const
{
	return { *this };
}


template <class Type>
typename Array<Type>::ConversionEnumerator	Array<Type>::Convert () const
{
	return ConversionEnumerator (*this);
}


template <class Type>
auto&	Array<Type>::AsConst () const
{ 
	return reinterpret_cast<const Array<typename Container<Type>::template MakeConstPtr<Type>::ConstType>&> (*this);
}


template <class Type>
UIndex	Array<Type>::FindFirst (const Type& item, UIndex from, USize range) const
{
	NULL_REF_CHECK (item);
	REF_CHECK ((range == MaxUSize && from <= size) || (range != MaxUSize && from + range <= size));

	if (range == MaxUSize)
		range = size - from;

	Type* it = GS::Find (array + from, array + from + range, item);

	if (it == array + from + range)
		return MaxUIndex;
	else
		return TruncateTo32Bit (it - array);
}


template <class Type>
UIndex	Array<Type>::FindFirst (const std::function<bool (const Type&)>& condition, UIndex from, USize range) const
{
	REF_CHECK ((range == MaxUSize && from <= size) || (range != MaxUSize && from + range <= size));

	if (range == MaxUSize)
		range = size - from;

	Type* it = GS::Find (array + from, array + from + range, condition);

	if (it == array + from + range)
		return MaxUIndex;
	else
		return TruncateTo32Bit (it - array);
}


template <class Type>
UIndex	Array<Type>::FindLast (const Type& item) const
{
	NULL_REF_CHECK (item);

	for (UIndex i = size; i > 0; i--) {
		if (array[i - 1] == item)
			return i - 1;
	}

	return MaxUIndex;
}


template <class Type>
UIndex	Array<Type>::FindLast (const std::function<bool (const Type&)>& condition) const
{
	for (UIndex i = size; i > 0; i--) {
		if (condition (array[i - 1]))
			return i - 1;
	}

	return MaxUIndex;
}


template <class Type>
bool	Array<Type>::Contains (const Type& item) const
{
	NULL_REF_CHECK (item);

	return (GS::Find (array, array + size, item) != array + size);
}


template <class Type>
bool	Array<Type>::Contains (const std::function<bool (const Type&)>& condition) const
{
	return (GS::Find (array, array + size, condition) != array + size);
}


template <class Type>
bool	Array<Type>::Contains (std::initializer_list<Type> items) const
{
	for (const auto& item : items) {
		if (!Contains (item))
			return false;
	}

	return true;
}


template <class Type>
bool	Array<Type>::ContainsOnly (const std::function<bool (const Type&)>& condition) const
{
	for (UInt32 i = 0; i < size; i++) {
		if (!condition (array[i]))
			return false;
	}

	return true;
}


template <class Type>
USize	Array<Type>::Count (const Type& item, UIndex from, USize range) const
{
	NULL_REF_CHECK (item);
	REF_CHECK ((range == MaxUSize && from <= size) || (range != MaxUSize && from + range <= size));

	if (range == MaxUSize)
		range = size - from;

	return GS::Count (array + from, array + from + range, item);
}


template <class Type>
USize	Array<Type>::Count (const std::function<bool (const Type&)>& condition, UIndex from, USize range) const
{
	REF_CHECK ((range == MaxUSize && from <= size) || (range != MaxUSize && from + range <= size));

	if (range == MaxUSize)
		range = size - from;

	return GS::Count (array + from, array + from + range, condition);
}


template <class Type>
Array<Type>   Array<Type>::Select (const std::function<bool (const Type&)>& condition) const
{
	Array<Type> result (size);
	for (UIndex i = 0; i < size; i++) {
		const Type& sourceItem = array[i];
		if (condition (sourceItem))
			result.Push (sourceItem);
	}

	return result;
}


template <class Type>
template <class ResultType>
Array<ResultType>	Array<Type>::Transform (const std::function<ResultType (const Type&)>& transformation) const
{
	Array<ResultType> result (size);
	for (UIndex i = 0; i < size; i++)
		result.Push (transformation (array[i]));
	
	return result;
}


template <class Type>
template <class ResultType>
Array<ResultType>	Array<Type>::Transform () const
{
	Array<ResultType> result (size);
	for (UIndex i = 0; i < size; i++)
		result.Push (static_cast<ResultType> (array[i]));
	
	return result;
}


template <class Type>
template <class Condition>
decltype (auto) Array<Type>::Where (Condition&& condition) const&
{
	return CreateConditionalView (*this, std::forward<Condition> (condition));
}


template <class Type>
template <class Condition>
decltype (auto) Array<Type>::Where (Condition&& condition) &&
{
	return CreateConditionalView (std::move (*this), std::forward<Condition> (condition));
}


template <class Type>
template <class T /*= Type*/, class /*= EnableIf<HasOperatorEquals<T>>*/>
bool	Array<Type>::operator== (const Array& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	if (size != rightOp.size)
		return false;

	return (GS::IsEqual (array, array + size, rightOp.array));
}


template <class Type>
bool	Array<Type>::operator!= (const Array& rightOp) const
{
	return !operator== (rightOp);
}


template <class Type>
bool	Array<Type>::IsEqual (std::initializer_list<Type> rightOp) const
{
	NULL_REF_CHECK (rightOp);

	if (size != rightOp.size ())
		return false;

	return (GS::IsEqual (array, array + size, rightOp.begin ()));
}


template <class Type>
USize	Array<Type>::GetCapacity () const
{
	return capacity;
}


template <class Type>
void	Array<Type>::SetCapacity (USize newCapacity)
{
	if (newCapacity < size)
		newCapacity = size;		// can't delete items with this method

	if (newCapacity == capacity)
		return;

	Reallocate (newCapacity);
}


template <class Type>
void	Array<Type>::EnsureCapacity (USize minCapacity)
{
	IncreaseCapacity (minCapacity);
}


template <class Type>
GSErrCode	Array<Type>::Read (IChannel& ic)
{
	NULL_REF_CHECK (ic);

	Clear ();

	GS::InputFrame frame (ic, ArrayPrivate::classInfo);
	if (frame.GetStatus () != NoError)
		return frame.GetStatus ();

	USize newSize;
	GSErrCode errorCode = ic.Read (newSize);
	if (errorCode == NoError)
		SetSize (newSize);

	for (UIndex i = 0; i < newSize && errorCode == NoError; i++)
		errorCode = ic.Read (array[i]);

	return errorCode;
}


template <class Type>
GSErrCode	Array<Type>::Write (OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	GS::OutputFrame frame (oc, ArrayPrivate::classInfo);

	GSErrCode errorCode = oc.Write (size);

	for (UIndex i = 0; i < size && errorCode == NoError; i++)
		errorCode = oc.Write (array[i]);

	return errorCode;
}


template <class Type>
GSErrCode	Array<Type>::Read (IChannel& ic, const std::function<GSErrCode (IChannel&, Type&)>& reader)
{
	NULL_REF_CHECK (ic);

	Clear ();

	GS::InputFrame frame (ic, ArrayPrivate::classInfo);
	if (frame.GetStatus () != NoError)
		return frame.GetStatus ();

	USize newSize;
	GSErrCode errorCode = ic.Read (newSize);
	if (errorCode == NoError)
		SetSize (newSize);

	for (UIndex i = 0; i < newSize && errorCode == NoError; i++)
		errorCode = reader (ic, array[i]);

	return errorCode;
}


template <class Type>
GSErrCode	Array<Type>::Write (OChannel& oc, const std::function<GSErrCode (OChannel&, const Type&)>& writer) const
{
	NULL_REF_CHECK (oc);

	GS::OutputFrame frame (oc, ArrayPrivate::classInfo);

	GSErrCode errorCode = oc.Write (size);

	for (UIndex i = 0; i < size && errorCode == NoError; i++)
		errorCode = writer (oc, array[i]);

	return errorCode;
}


template <class Type>
Type*	Array<Type>::GetContent ()
{
	return array;
}


template <class Type>
const Type*		Array<Type>::GetContent () const
{
	return array;
}


template <class Type>
void	Array<Type>::Print (OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	oc << "Array" << '\n';
}


template <class Type>
void	Array<Type>::Dump (OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	oc << "array:    " << array    << '\n';
	oc << "capacity: " << capacity << '\n';
	oc << "size:     " << size     << '\n';
}


template <class Type>
bool	Array<Type>::CheckState () const
{
	if ((array == nullptr && (capacity != 0 || size != 0)) ||
		(array != nullptr && capacity == 0) ||
		capacity < size)
		return false;

	return true;
}


template <class Type>
USize	Array<Type>::GetMinBufferCapacity () const
{
	return 0;
}


template <class Type>
Type*	Array<Type>::AllocateNewBuffer (USize bufferCapacity, const Type* /*oldBuffer*/)
{
	return reinterpret_cast<Type*> (new char[bufferCapacity * sizeof (Type)]);
}


template <class Type>
void	Array<Type>::DeleteBuffer (Type* buffer)
{
	delete [] reinterpret_cast<char*> (buffer);
}


template <class Type>
bool	Array<Type>::IsIndependentBuffer (const Type* /*buffer*/) const
{
	return true;
}


template <class Type>
void	Array<Type>::IncreaseCapacity (USize minCapacity)
{
	if (minCapacity > capacity)
		AdjustCapacity (minCapacity);
}


template <class Type>
void	Array<Type>::DecreaseCapacity (USize minCapacity)
{
	if (minCapacity <= capacity / 4)
		AdjustCapacity (minCapacity);
}


template <class Type>
void	Array<Type>::AdjustCapacity (USize minCapacity)
{
	if (minCapacity <= capacity && minCapacity > capacity / 4)
		return;		// there is no need to reallocate

	Reallocate (GS::Max (minCapacity, size * 2));
}


template <class Type>
Array<Type>::Array (char* initialBuffer, USize initialCapacity):
	array (reinterpret_cast<Type*> (initialBuffer)),
	capacity (initialCapacity),
	size (0)
{
}


template <class Type>
void	Array<Type>::SetContent (Type* newArray, USize newSize, USize newCapacity)
{
	// This is used by HandleArray to notify Array about the Handle reallocation.
	ARG_CHECK (newCapacity >= newSize);

	array = newArray;
	size = newSize;
	capacity = newCapacity;
}


template <class Type>
void	Array<Type>::Reallocate (USize minCapacity)
{
	ARG_CHECK (minCapacity >= size);	// can't delete items with this method

	USize newCapacity = minCapacity;

	if (newCapacity < GetMinBufferCapacity ())
		newCapacity = GetMinBufferCapacity ();

	if (newCapacity == capacity)
		return;

	Type* newArray = nullptr;
	if (newCapacity != 0) {
		try {
			newArray = AllocateNewBuffer (newCapacity, array);
		}
		catch (const GS::OutOfMemoryException&) {
			if (capacity >= minCapacity)
				return;
			else
				throw;
		}

		for (UIndex i = 0; i < size; i++) {
			::new (&newArray[i]) Type (std::move (array[i]));
			array[i].~Type ();
		}
	}

	DeleteBuffer (array);

	array = newArray;
	capacity = newCapacity;
}


template <class Type>
void	Array<Type>::SetIncreasedSize (USize increasedSize)
{
	DBASSERT (increasedSize >= size);

	IncreaseCapacity (increasedSize);

	for (UIndex i = size; i < increasedSize; i++)
		::new (&array[i]) Type ();

	size = increasedSize;
}


template <class Type>
void	Array<Type>::SetDecreasedSize (USize decreasedSize)
{
	DBASSERT (decreasedSize <= size);

	for (UIndex i = decreasedSize; i < size; i++)
		array[i].~Type ();

	size = decreasedSize;

	DecreaseCapacity (size);
}


template <class Type>
Array<Type>::ConversionEnumerator::ConversionEnumerator (const Array& source):
	source (&source)
{
}


template <class Type>
void	Array<Type>::ConversionEnumerator::Enumerate (const std::function<void (const Type&)>& processor) const
{
	source->Enumerate (processor);
}


template <class Type>
USize	Array<Type>::ConversionEnumerator::GetSizeHint (void) const
{
	return source->GetSize ();
}


// === Global functions ================================================================================================

template <class Type>
auto		begin (Array<Type>& array)
{
	return array.BeginFast ();
}


template <class Type>
auto		end (Array<Type>& array)
{
	return array.EndFast ();
}


template <class Type>
auto		begin (const Array<Type>& array)
{
	return array.BeginFast ();
}


template <class Type>
auto		end (const Array<Type>& array)
{
	return array.EndFast ();
}


template <class Type>
GSErrCode	Print (OChannel& oc, const Array<Type>& obj)
{
	obj.Print (oc);

	return NoError;
}


template <class Type>
auto	GetInserter (Array<Type>& array)
{
	return PushInserter<Array<Type>> (&array);
}


}	// namespace GS
// ________________________________ Class Array ________________________________



// =============================== Class ArrayFB ===============================

namespace GS {

template <class Type, USize BufferCapacity>
class ArrayFB: public Array<Type> {
private:
	alignas (Type) char     fixBuffer[BufferCapacity * sizeof (Type)];      // fix buffer for the Array

protected:
	virtual USize	GetMinBufferCapacity () const override;
	virtual Type*	AllocateNewBuffer	 (USize bufferCapacity, const Type* oldBuffer) override;
	virtual void	DeleteBuffer		 (Type* buffer) override;
	virtual bool	IsIndependentBuffer  (const Type* buffer) const override;

public:
	ArrayFB ();
	explicit ArrayFB (ConstForwardIterator<Type> begin);
	explicit ArrayFB (ConstForwardIterator<Type> begin, ConstForwardIterator<Type> end);
	ArrayFB (const GS::ConversionEnumerator<Type>& enumerator);
	ArrayFB (std::initializer_list<Type> items);
	ArrayFB (const ArrayFB& source);
	ArrayFB (ArrayFB&& source);
	ArrayFB (const Array<Type>& source);
	ArrayFB (Array<Type>&& source);
	ArrayFB (const ArrayFB&&) = delete;
	ArrayFB&	operator= (const ArrayFB& source);
	ArrayFB&	operator= (ArrayFB&& source);
	ArrayFB&	operator= (const Array<Type>& source);
	ArrayFB&	operator= (Array<Type>&& source);
	ArrayFB&	operator= (const GS::ConversionEnumerator<Type>& enumerator);
   ~ArrayFB ();
};


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>::ArrayFB ():
	Array<Type> (fixBuffer, BufferCapacity)
{
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>::ArrayFB (ConstForwardIterator<Type> begin):
	ArrayFB<Type, BufferCapacity> ()
{
	Array<Type>::Insert (0, begin);
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>::ArrayFB (ConstForwardIterator<Type> begin, ConstForwardIterator<Type> end) :
	ArrayFB<Type, BufferCapacity> ()
{
	while (begin != end) {
		Array<Type>::Push (*begin);
		++begin;
	}
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>::ArrayFB (const GS::ConversionEnumerator<Type>& enumerator):
	ArrayFB<Type, BufferCapacity> ()
{
	Array<Type>::operator= (enumerator);
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>::ArrayFB (std::initializer_list<Type> items):
	ArrayFB<Type, BufferCapacity> ()
{
	Array<Type>::EnsureCapacity (USize (items.size ()));

	for (const Type& item : items)
		Array<Type>::Push (item);
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>::ArrayFB (const ArrayFB& source):
	ArrayFB<Type, BufferCapacity> ()
{
	Array<Type>::operator= (source);
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>::ArrayFB (ArrayFB&& source):
	ArrayFB<Type, BufferCapacity> ()
{
	Array<Type>::Move (source);
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>::ArrayFB (const Array<Type>& source):
	ArrayFB<Type, BufferCapacity> ()
{
	Array<Type>::operator= (source);
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>::ArrayFB (Array<Type>&& source):
	ArrayFB<Type, BufferCapacity> ()
{
	Array<Type>::Move (source);
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>&	ArrayFB<Type, BufferCapacity>::operator= (const ArrayFB& source)
{
	Array<Type>::operator= (source);

	return *this;
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>&	ArrayFB<Type, BufferCapacity>::operator= (ArrayFB&& source)
{
	Array<Type>::Move (source);

	return *this;
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>&	ArrayFB<Type, BufferCapacity>::operator= (const Array<Type>& source)
{
	Array<Type>::operator= (source);

	return *this;
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>&	ArrayFB<Type, BufferCapacity>::operator= (Array<Type>&& source)
{
	Array<Type>::Move (source);

	return *this;
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>&	ArrayFB<Type, BufferCapacity>::operator= (const GS::ConversionEnumerator<Type>& enumerator)
{
	Array<Type>::Clear (true);
	Array<Type>::EnsureCapacity (enumerator.GetSizeHint ());

	enumerator.Enumerate ([&] (const Type& item) {
		Array<Type>::Push (item);
	});

	return *this;
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>::~ArrayFB ()
{
	this->Clear ();
}


template <class Type, USize BufferCapacity>
USize	ArrayFB<Type, BufferCapacity>::GetMinBufferCapacity () const
{
	return BufferCapacity;
}


template <class Type, USize BufferCapacity>
Type*	ArrayFB<Type, BufferCapacity>::AllocateNewBuffer (USize bufferCapacity, const Type* oldBuffer)
{
	if (IsIndependentBuffer (oldBuffer) && bufferCapacity <= BufferCapacity)
		return reinterpret_cast<Type*> (fixBuffer);
	else
		return Array<Type>::AllocateNewBuffer (bufferCapacity, oldBuffer);
}


template <class Type, USize BufferCapacity>
void	ArrayFB<Type, BufferCapacity>::DeleteBuffer (Type* buffer)
{
	if (IsIndependentBuffer (buffer))
		Array<Type>::DeleteBuffer (buffer);
}


template <class Type, USize BufferCapacity>
bool	ArrayFB<Type, BufferCapacity>::IsIndependentBuffer (const Type* buffer) const
{
	return (buffer != reinterpret_cast<const Type*> (fixBuffer));
}

// === Global functions ================================================================================================


template<typename Type, USize BufferCapacity>
auto	GetInserter (ArrayFB<Type, BufferCapacity>& array)
{
	return GS::GetInserter (static_cast<Array<Type>&> (array));
}


}	// namespace GS
// _______________________________ Class ArrayFB _______________________________


#endif
