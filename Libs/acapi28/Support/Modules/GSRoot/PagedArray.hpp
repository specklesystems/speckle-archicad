
// *****************************************************************************
//
//                               Class PagedArray
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined PAGEDARRAY_HPP
#define PAGEDARRAY_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "BaseAlgorithms.hpp"
#include "BM.hpp"
#include "Channel.hpp"
#include "ClassInfo.hpp"
#include "ConditionalView.hpp"
#include "Enumerator.hpp"
#include "FunctionRef.hpp"
#include "Inserter.hpp"
#include "IOFrame.hpp"
#include "PushInserter.hpp"
#include "RandomContainer.hpp"
#include "RandomContainerIterator.hpp"
#include "RandomContainerReverseIterator.hpp"

#include <new>
#include <utility>
#include <functional>


// ============================= Class PagedArray ==============================

namespace GS {

class GSROOT_DLL_EXPORT PagedArrayPrivate {
public:
	static GS::ClassInfo	classInfo;	// PagedArray's private classInfo
};


template <UInt32 value>
struct Check2;

template <>
struct Check2<0> {
	enum { Check = 0 };
};

template <UInt32 value>
struct Log2 {
	enum { Result = 1 + Log2<value / 2>::Result + Check2<value % 2>::Check };
};

template <>
struct Log2<1> {
	enum { Result = 0 };
};

template <>
struct Log2<8> {
	enum { Result = 3 };
};


constexpr UInt32 DefaultPagedArrayPageSize = 8;


template <class Type, UInt32 PageSize = DefaultPagedArrayPageSize>
class GS_EXPORT_TYPEINFO PagedArray: public RandomContainer<Type> {
private:
	enum { FixPageTableCapacity = 1 };

	Type**	pageTable = nullptr;					// table of pointers to pages of items
	Type*	fixPageTable[FixPageTableCapacity];		// built in page table for small sizes
	USize	capacity = 0;							// capacity of the PagedArray (in items)
	USize	deallocationCapacity = 0;				// lower capacity of the PagedArray below (or equal) which allocation units should be deleted
	USize	size = 0;								// number of items in the PagedArray

	enum {
		Log2PageSize = Log2<PageSize>::Result,	// log2 of the page size
		OffsetMask	 = PageSize - 1				// mask for the indices inside a page
	};

	Type&		Cell (UIndex idx);
	const Type&	Cell (UIndex idx) const;

	USize		GetPageNumber () const;

	USize			GetPageTableCapacity () const;
	static USize	GetNextPageTableCapacity (USize minCapacity);

	void			SetIncreasedSize (USize increasedSize);
	void			SetDecreasedSize (USize decreasedSize);

	void			IncreaseCapacity (USize minCapacity);
	void			AddNewPages		 (USize minCapacity);

	void			DecreaseCapacity  (USize minCapacity);
	void			DeleteUnusedPages (USize minCapacity);

	ULong	GetCurrentAllocationUnit () const;
	ULong	GetNextAllocationUnit (ULong currentAllocationUnit) const;
	ULong	GetPrevAllocationUnit (ULong currentAllocationUnit) const;

	static char*	AllocateBuffer (USize bufferCapacity);
	static void		DeleteBuffer   (char* buffer);

	static ULong	ComputeLog2 (ULong n);

public:
		// Types

	typedef RandomContainerIterator<PagedArray>				Iterator;
	typedef ConstRandomContainerIterator<PagedArray>		ConstIterator;

	typedef GeneralRandomContainerIterator<PagedArray>		GeneralIterator;
	typedef ConstGeneralRandomContainerIterator<PagedArray>	ConstGeneralIterator;

	typedef RandomContainerReverseIterator<PagedArray>		ReverseIterator;
	typedef ConstRandomContainerReverseIterator<PagedArray>	ConstReverseIterator;

	typedef RandomContainerRange<PagedArray>				Range;
	typedef RandomContainerConstRange<PagedArray>			ConstRange;

	typedef RandomContainerReverseRange<PagedArray>			ReverseRange;
	typedef RandomContainerReverseConstRange<PagedArray>	ReverseConstRange;

	class ConversionEnumerator;

		// Constructors

	PagedArray ();
	explicit PagedArray (ConstIterator begin);
	explicit PagedArray (ConstForwardIterator<Type> begin);
	explicit PagedArray (ConstForwardIterator<Type> begin, ConstForwardIterator<Type> end);
	PagedArray (const GS::ConversionEnumerator<Type>& enumerator);
	PagedArray (std::initializer_list<Type> items);
	PagedArray (const PagedArray& source);
	PagedArray (PagedArray&& source);
	PagedArray (const PagedArray&&) = delete;

	template <class SourceType, UInt32 SourcePageSize>
	explicit PagedArray (const PagedArray<SourceType, SourcePageSize>& source);

	PagedArray&	operator= (const PagedArray& source);
	PagedArray&	operator= (PagedArray&& source);
	PagedArray&	operator= (const GS::ConversionEnumerator<Type>& enumerator);

	template <class SourceType, UInt32 SourcePageSize>
	PagedArray&	operator= (const PagedArray<SourceType, SourcePageSize>& source);

   ~PagedArray ();

	void		Move (PagedArray& source);
	void		Move (FunctionRef<void (Type&&)> processor);

		// Item access

	Type&		operator[] (UIndex idx) gs_lifebound;
	const Type&	operator[] (UIndex idx) const gs_lifebound;

	Type&		Get (UIndex idx) gs_lifebound;
	const Type&	Get (UIndex idx) const gs_lifebound;

	Type&		GetFirst () gs_lifebound;
	const Type&	GetFirst () const gs_lifebound;

	Type&		GetLast () gs_lifebound;
	const Type&	GetLast () const gs_lifebound;
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

	void	Append (const PagedArray& items);
	void	Append (PagedArray&& items);

	template <class R, class = EnableIf<IsCompatibleRange<R, Type>>>
	void	Append (R&& range);

	void	Delete		(UIndex idx);
	void	Delete		(UIndex from, USize range);
	void	DeleteLast	();

	UIndex	DeleteFirst	(const Type& item);
	UIndex	DeleteFirst	(FunctionRef<bool (const Type&)> condition);
	UIndex	DeleteLast	(const Type& item);
	UIndex	DeleteLast	(FunctionRef<bool (const Type&)> condition);
	void	DeleteAll	(const Type& item);
	void	DeleteAll	(FunctionRef<bool (const Type&)> condition);

	void	Clear (bool keepCapacity = false);

	void	Swap (PagedArray& rightOp);

	void	Push (const Type& item);
	void	Push (Type&& item);

	template <class... ItemParameters>
	void	PushNew (ItemParameters&&... itemParameters);

	void	Pop	 (Type* item);
	Type	Pop	 ();

	USize	GetSize		 () const;
	bool	IsEmpty		 () const;
	bool	IsLast		 (UIndex idx) const;
	void	SetSize		 (USize newSize);
	void	IncreaseSize (USize sizeIncrement);
	void	EnsureSize	 (USize requiredSize);

		// Content query

	Iterator				Enumerate ();
	ConstIterator			Enumerate () const;

	template <class Function>
	void					Enumerate	   (Function&& processor);
	template <class Function>
	void					Enumerate	   (Function&& processor) const;
	template <class Function>
	void					EnumerateConst (Function&& processor) const;

	Iterator				Begin ();
	ConstIterator			Begin () const;

	Iterator				End	();
	ConstIterator			End	() const;

	GeneralIterator			EnumerateGeneral ();
	ConstGeneralIterator	EnumerateGeneral () const;

	GeneralIterator			BeginGeneral ();
	ConstGeneralIterator	BeginGeneral () const;

	GeneralIterator			EndGeneral	();
	ConstGeneralIterator	EndGeneral	() const;

	ReverseIterator			ReverseEnumerate ();
	ConstReverseIterator	ReverseEnumerate () const;

	template <class Function>
	void					ReverseEnumerate	  (Function&& processor);
	template <class Function>
	void					ReverseEnumerate	  (Function&& processor) const;
	template <class Function>
	void					ReverseEnumerateConst (Function&& processor) const;

	ReverseIterator			ReverseBegin ();
	ConstReverseIterator	ReverseBegin () const;

	ReverseIterator			ReverseEnd	();
	ConstReverseIterator	ReverseEnd	() const;

	Range					operator() (UIndex begin, UIndex end);
	ConstRange				operator() (UIndex begin, UIndex end) const;

	Range					operator() (FromBeginSelector, UIndex end);
	ConstRange				operator() (FromBeginSelector, UIndex end) const;

	Range					operator() (UIndex begin, ToEndSelector);
	ConstRange				operator() (UIndex begin, ToEndSelector) const;

	ReverseRange			Reverse ();
	ReverseConstRange		Reverse () const;

	ConversionEnumerator	Convert () const;

	auto&					AsConst () const gs_lifebound;

	UIndex	FindFirst (const Type& item, UIndex from = 0, USize range = MaxUSize) const;
	UIndex	FindFirst (FunctionRef<bool (const Type&)> condition, UIndex from = 0, USize range = MaxUSize) const;
	UIndex	FindLast  (const Type& item) const;
	UIndex	FindLast  (FunctionRef<bool (const Type&)> condition) const;

	bool	Contains	 (const Type& item) const;
	bool	Contains	 (FunctionRef<bool (const Type&)> condition) const;
	bool	Contains	 (std::initializer_list<Type> items) const;
	bool	ContainsOnly (FunctionRef<bool (const Type&)> condition) const;

	USize	Count	 (const Type& item, UIndex from = 0, USize range = MaxUSize) const;
	USize	Count	 (FunctionRef<bool (const Type&)> condition, UIndex from = 0, USize range = MaxUSize) const;

	PagedArray	Select (FunctionRef<bool (const Type&)> condition) const;

	template <class ResultType>
	PagedArray<ResultType, PageSize>	Transform (FunctionRef<ResultType (const Type&)> transformation) const;

	template <class ResultType>
	PagedArray<ResultType, PageSize>	Transform () const;

	template <class Condition>
	decltype (auto) 					Where (Condition&& condition) const&;

	template <class Condition>
	decltype (auto) 					Where (Condition&& condition) &&;

		// Equality operations

	template <class T = Type, class = EnableIf<HasOperatorEquals<T>>>
	bool	operator== (const PagedArray& rightOp) const;

	bool	operator!= (const PagedArray& rightOp) const;

	bool	IsEqual	   (std::initializer_list<Type> rightOp) const;

		// I/O

	GSErrCode	Read  (IChannel& ic);
	GSErrCode	Read  (IChannel& ic, FunctionRef<GSErrCode (IChannel&, Type&)> reader);
	GSErrCode	Write (OChannel& oc) const;
	GSErrCode	Write (OChannel& oc, FunctionRef<GSErrCode (OChannel&, const Type&)> writer) const;

		// Debug

	bool	CheckState () const;

		// Types

	class ConversionEnumerator: public GS::ConversionEnumerator<Type> {
	private:
		const PagedArray* source;

	public:
		ConversionEnumerator (const PagedArray& source);

		virtual void	Enumerate (const std::function<void (const Type&)>& processor) const override;

		virtual USize	GetSizeHint (void) const override;
	};
};

// === class DefaultPagedArray =========================================================================================

template <class Type>
class DefaultPagedArray: public GS::PagedArray<Type> {};


// === PagedArray methods ==============================================================================================

template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>::PagedArray ()
{
}


template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>::PagedArray (ConstIterator begin)
{
	while (begin != nullptr) {
		Push (*begin);
		++begin;
	}
}


template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>::PagedArray (ConstForwardIterator<Type> begin)
{
	while (begin != nullptr) {
		Push (*begin);
		++begin;
	}
}


template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>::PagedArray (ConstForwardIterator<Type> begin, ConstForwardIterator<Type> end)
{
	while (begin != end) {
		Push (*begin);
		++begin;
	}
}


template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>::PagedArray (const GS::ConversionEnumerator<Type>& enumerator)
{
	enumerator.Enumerate (GetInserter (*this));
}


template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>::PagedArray (const PagedArray& source)
{
	IncreaseCapacity (source.size);

	for (UIndex i = 0; i < source.size; i++)
		::new (&Cell (i)) Type (source[i]);

	size = source.size;
}


template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>::PagedArray (std::initializer_list<Type> items)
{
	IncreaseCapacity (USize (items.size ()));

	UIndex i = 0;
	for (const auto& item : items)
		::new (&Cell (i++)) Type (item);

	size = USize (items.size ());
}


template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>::PagedArray (PagedArray&& source)
{
	Move (source);
}


template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>&		PagedArray<Type, PageSize>::operator= (const PagedArray& source)
{
	PagedArray copy = source;
	Swap (copy);

	return *this;
}


template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>&		PagedArray<Type, PageSize>::operator= (PagedArray&& source)
{
	Move (source);

	return *this;
}


template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>&		PagedArray<Type, PageSize>::operator= (const GS::ConversionEnumerator<Type>& enumerator)
{
	Clear ();

	enumerator.Enumerate (GetInserter (*this));

	return *this;
}


template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>::~PagedArray ()
{
	Clear ();
}


template <class Type, UInt32 PageSize>
template <class SourceType, UInt32 SourcePageSize>
PagedArray<Type, PageSize>::PagedArray (const PagedArray<SourceType, SourcePageSize>& items) :
	pageTable (nullptr),
	capacity (0),
	deallocationCapacity (0),
	size (0)
{
	static_assert (IsConvertible<SourceType, Type>, "'SourceType' is not convertible to 'Type'.");

	IncreaseCapacity (items.GetSize ());

	for (const SourceType& item : items)
		Push (item);

	size = items.GetSize ();
}


template <class Type, UInt32 PageSize>
template <class SourceType, UInt32 SourcePageSize>
PagedArray<Type, PageSize>&		PagedArray<Type, PageSize>::operator= (const PagedArray<SourceType, SourcePageSize>& items)
{
	static_assert (IsConvertible<SourceType, Type>, "'SourceType' is not convertible to 'Type'.");

	PagedArray<Type, PageSize> copy (items);
	Swap (copy);

	return *this;
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Move (PagedArray& source)
{
	if (DBERROR (&source == this))
		return;

	Swap (source);
	source.Clear ();
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Move (const FunctionRef<void (Type&&)> processor)
{
	for (UIndex i = 0; i < size; ++i)
		processor (std::move (Cell (i)));

	Clear ();
}


template <class Type, UInt32 PageSize>
Type&	PagedArray<Type, PageSize>::operator[] (UIndex idx)
{
	REF_CHECK (idx < size);

	return Cell (idx);
}


template <class Type, UInt32 PageSize>
const Type&		PagedArray<Type, PageSize>::operator[] (UIndex idx) const
{
	REF_CHECK (idx < size);

	return Cell (idx);
}


template <class Type, UInt32 PageSize>
Type&	PagedArray<Type, PageSize>::Get (UIndex idx)
{
	REF_CHECK_R (idx < size);

	return Cell (idx);
}


template <class Type, UInt32 PageSize>
const Type&		PagedArray<Type, PageSize>::Get (UIndex idx) const
{
	REF_CHECK_R (idx < size);

	return Cell (idx);
}


template <class Type, UInt32 PageSize>
Type&	PagedArray<Type, PageSize>::GetFirst ()
{
	PRECOND_DEPRECATED (size != 0);

	return pageTable[0][0];
}


template <class Type, UInt32 PageSize>
const Type&		PagedArray<Type, PageSize>::GetFirst () const
{
	PRECOND_DEPRECATED (size != 0);

	return pageTable[0][0];
}


template <class Type, UInt32 PageSize>
Type&	PagedArray<Type, PageSize>::GetLast ()
{
	PRECOND_DEPRECATED (size != 0);

	return Cell (size - 1);
}


template <class Type, UInt32 PageSize>
const Type&		PagedArray<Type, PageSize>::GetLast () const
{
	PRECOND_DEPRECATED (size != 0);

	return Cell (size - 1);
}


template <class Type, UInt32 PageSize>
UIndex		PagedArray<Type, PageSize>::GetLastIndex () const
{
	PRECOND_DEPRECATED (size != 0);

	return size - 1;
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Set (UIndex idx, const Type& item)
{
	REF_CHECK (idx < size);
	NULL_REF_CHECK (item);

	Cell (idx) = item;
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Set (UIndex idx, Type&& item)
{
	REF_CHECK (idx < size);
	NULL_REF_CHECK (item);

	Cell (idx) = std::move (item);
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Fill (const Type& item, UIndex from, USize range)
{
	NULL_REF_CHECK (item);
	REF_CHECK ((range == MaxUSize && from <= size) || (range != MaxUSize && from + range <= size));

	if (range == MaxUSize)
		range = size - from;

	GS::Fill (Begin () + from, Begin () + from + range, item);
}


template <class Type, UInt32 PageSize>
USize	PagedArray<Type, PageSize>::Replace (const Type& oldItem, const Type& newItem, UIndex from, USize range)
{
	NULL_REF_CHECK (oldItem);
	NULL_REF_CHECK (newItem);
	REF_CHECK ((range == MaxUSize && from <= size) || (range != MaxUSize && from + range <= size));

	if (range == MaxUSize)
		range = size - from;

	return GS::Replace (Begin () + from, Begin () + from + range, oldItem, newItem);
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Insert (UIndex to, const Type& item)
{
	REF_CHECK (to <= size);
	NULL_REF_CHECK (item);

	IncreaseCapacity (size + 1);

	::new (&Cell (size)) Type ();
	for (UIndex i = size; i > to; i--)
		Cell (i) = std::move (Cell (i - 1));
	Cell (to) = item;

	size++;
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Insert (UIndex to, Type&& item)
{
	REF_CHECK (to <= size);
	NULL_REF_CHECK (item);

	IncreaseCapacity (size + 1);

	::new (&Cell (size)) Type ();
	for (UIndex i = size; i > to; i--)
		Cell (i) = std::move (Cell (i - 1));
	Cell (to) = std::move (item);

	size++;
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Insert (UIndex to, ConstIterator begin)
{
	REF_CHECK (to <= size);

	while (begin != nullptr) {
		Insert (to, *begin);
		to++;
		++begin;
	}
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Insert (UIndex to, ConstIterator begin, ConstIterator end)
{
	REF_CHECK (to <= size);

	while (begin != end) {
		Insert (to, *begin);
		to++;
		++begin;
	}
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Insert (UIndex to, ConstForwardIterator<Type> begin)
{
	REF_CHECK (to <= size);

	while (begin != nullptr) {
		Insert (to, *begin);
		to++;
		++begin;
	}
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Insert (UIndex to, ConstForwardIterator<Type> begin, ConstForwardIterator<Type> end)
{
	REF_CHECK (to <= size);

	while (begin != end) {
		Insert (to, *begin);
		to++;
		++begin;
	}
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Append (const PagedArray& items)
{
	NULL_REF_CHECK (items);

	if (&items == this) {
		PagedArray temp = items;
		Append (std::move (temp));
		return;
	}

	IncreaseCapacity (size + items.GetSize ());

	for (UIndex i = 0; i < items.GetSize (); i++)
		::new (&Cell (size + i)) Type (items[i]);

	size += items.GetSize ();
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Append (PagedArray&& items)
{
	NULL_REF_CHECK (items);

	IncreaseCapacity (size + items.GetSize ());

	for (UIndex i = 0; i < items.GetSize (); i++)
		::new (&Cell (size + i)) Type (std::move (items[i]));

	size += items.GetSize ();
}


template <class Type, UInt32 PageSize>
template <class R, class /*SFINAE*/>
void	PagedArray<Type, PageSize>::Append (R&& range)
{
	const auto endIt = GS::EndADL (range);

	for (auto it = GS::BeginADL (range); it != endIt; ++it)
		Push (*it);
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Delete (UIndex idx)
{
	REF_CHECK (idx < size);

	for (UIndex i = idx + 1; i < size; i++)
		Cell (i - 1) = std::move (Cell (i));

	Cell (size - 1).~Type ();
	size--;

	DecreaseCapacity (size);
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Delete (UIndex from, USize range)
{
	REF_CHECK (from + range <= size);

	if (range == 0)
		return;

	for (UIndex i = from + range; i < size; i++)
		Cell (i - range) = std::move (Cell (i));

	for (UIndex j = size - range; j < size; j++)
		Cell (j).~Type ();
	size -= range;

	DecreaseCapacity (size);
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::DeleteLast ()
{
	Cell (size - 1).~Type ();
	size--;

	DecreaseCapacity (size);
}


template <class Type, UInt32 PageSize>
UIndex		PagedArray<Type, PageSize>::DeleteFirst (const Type& item)
{
	NULL_REF_CHECK (item);

	UIndex first = FindFirst (item);
	if (first != MaxUIndex)
		Delete (first);

	return first;
}


template <class Type, UInt32 PageSize>
UIndex		PagedArray<Type, PageSize>::DeleteFirst (const FunctionRef<bool (const Type&)> condition)
{
	NULL_REF_CHECK (condition);

	UIndex first = FindFirst (condition);
	if (first != MaxUIndex)
		Delete (first);

	return first;
}


template <class Type, UInt32 PageSize>
UIndex		PagedArray<Type, PageSize>::DeleteLast (const Type& item)
{
	NULL_REF_CHECK (item);

	UIndex last = FindLast (item);
	if (last != MaxUIndex)
		Delete (last);

	return last;
}


template <class Type, UInt32 PageSize>
UIndex		PagedArray<Type, PageSize>::DeleteLast (const FunctionRef<bool (const Type&)> condition)
{
	NULL_REF_CHECK (condition);

	UIndex last = FindLast (condition);
	if (last != MaxUIndex)
		Delete (last);

	return last;
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::DeleteAll (const Type& item)
{
	NULL_REF_CHECK (item);

	UIndex toDelete = FindFirst (item);

	if (toDelete == MaxUIndex)
		return;

	for (UIndex i = toDelete + 1; i < GetSize (); i++) {
		if (!(Cell (i) == item)) {
			Cell (toDelete) = std::move (Cell (i));
			toDelete++;
		}
	}

	SetDecreasedSize (toDelete);
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::DeleteAll (const FunctionRef<bool (const Type&)> condition)
{
	NULL_REF_CHECK (condition);

	UIndex toDelete = FindFirst (condition);

	if (toDelete == MaxUIndex)
		return;

	for (UIndex i = toDelete + 1; i < GetSize (); i++) {
		if (!condition (Cell (i))) {
			Cell (toDelete) = std::move (Cell (i));
			toDelete++;
		}
	}

	SetDecreasedSize (toDelete);
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Clear (bool keepCapacity)
{
	for (UIndex i = 0; i < size; i++)
		Cell (i).~Type ();

	if (!keepCapacity) {
		USize growth = GetCurrentAllocationUnit ();
		UIndex j = GetPageNumber ();
		while (j > 0) {
			j -= growth;	// start index of the allocation unit
			DeleteBuffer (reinterpret_cast<char*> (pageTable[j]));
			growth = GetPrevAllocationUnit (growth);
		}

		if (pageTable != fixPageTable)
			DeleteBuffer (reinterpret_cast<char*> (pageTable));

		pageTable = nullptr;
		capacity = 0;
		deallocationCapacity = 0;
	}

	size = 0;
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Swap (PagedArray& rightOp)
{
	NULL_REF_CHECK (rightOp);

	if (this == &rightOp)
		return;

	GS::Swap (pageTable, rightOp.pageTable);
	if (pageTable == rightOp.fixPageTable)
		pageTable = fixPageTable;
	if (rightOp.pageTable == fixPageTable)
		rightOp.pageTable = rightOp.fixPageTable;

	for (UIndex i = 0; i < FixPageTableCapacity; i++)
		GS::Swap (fixPageTable[i], rightOp.fixPageTable[i]);

	GS::Swap (capacity,				rightOp.capacity);
	GS::Swap (deallocationCapacity,	rightOp.deallocationCapacity);
	GS::Swap (size,					rightOp.size);
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Push (const Type& item)
{
	NULL_REF_CHECK (item);

	IncreaseCapacity (size + 1);

	::new (&Cell (size)) Type (item);
	size++;
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Push (Type&& item)
{
	NULL_REF_CHECK (item);

	IncreaseCapacity (size + 1);

	::new (&Cell (size)) Type (std::move (item));
	size++;
}


template <class Type, UInt32 PageSize>
template <class... ItemParameters>
void	PagedArray<Type, PageSize>::PushNew (ItemParameters&&... itemParameters)
{
	IncreaseCapacity (size + 1);

	::new (&Cell (size)) Type { std::forward<ItemParameters> (itemParameters)... };
	size++;
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Pop (Type* item)
{
	PRECOND_DEPRECATED (size != 0);
	NULL_PTR_CHECK (item);

	*item = std::move (Cell (size - 1));

	Cell (size - 1).~Type ();
	size--;

	DecreaseCapacity (size);
}


template <class Type, UInt32 PageSize>
Type	PagedArray<Type, PageSize>::Pop ()
{
	PRECOND_DEPRECATED (size != 0);

	Type result = std::move (Cell (size - 1));

	Cell (size - 1).~Type ();
	size--;

	DecreaseCapacity (size);

	return result;
}


template <class Type, UInt32 PageSize>
USize	PagedArray<Type, PageSize>::GetSize () const
{
	return size;
}


template <class Type, UInt32 PageSize>
bool	PagedArray<Type, PageSize>::IsEmpty () const
{
	return (size == 0);
}


template <class Type, UInt32 PageSize>
bool	PagedArray<Type, PageSize>::IsLast (UIndex idx) const
{
	return (size > 0 && idx == size - 1);
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::SetSize (USize newSize)
{
	if (newSize < size)
		SetDecreasedSize (newSize);
	else if (newSize > size)
		SetIncreasedSize (newSize);
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::IncreaseSize (USize sizeIncrement)
{
	SetSize (size + sizeIncrement);
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::EnsureSize (USize requiredSize)
{
	if (size < requiredSize)
		SetSize (requiredSize);
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::Iterator	PagedArray<Type, PageSize>::Enumerate ()
{
	return Iterator (*this, 0);
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::ConstIterator	PagedArray<Type, PageSize>::Enumerate () const
{
	return ConstIterator (*this, 0);
}


template <class Type, UInt32 PageSize>
template <class Function>
void	PagedArray<Type, PageSize>::Enumerate (Function&& processor)
{
	for (UIndex i = 0; i < size; i++)
		processor (Cell (i));
}


template <class Type, UInt32 PageSize>
template <class Function>
void	PagedArray<Type, PageSize>::Enumerate (Function&& processor) const
{
	for (UIndex i = 0; i < size; i++)
		processor (Cell (i));
}


template <class Type, UInt32 PageSize>
template <class Function>
void	PagedArray<Type, PageSize>::EnumerateConst (Function&& processor) const
{
	Enumerate (processor);
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::Iterator	PagedArray<Type, PageSize>::Begin ()
{
	return Iterator (*this, 0);
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::ConstIterator	PagedArray<Type, PageSize>::Begin () const
{
	return ConstIterator (*this, 0);
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::Iterator	PagedArray<Type, PageSize>::End ()
{
	return Iterator (*this, size);
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::ConstIterator	PagedArray<Type, PageSize>::End () const
{
	return ConstIterator (*this, size);
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::GeneralIterator		PagedArray<Type, PageSize>::EnumerateGeneral ()
{
	return GeneralIterator (*this, 0);
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::ConstGeneralIterator	PagedArray<Type, PageSize>::EnumerateGeneral () const
{
	return ConstGeneralIterator (*this, 0);
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::GeneralIterator		PagedArray<Type, PageSize>::BeginGeneral ()
{
	return GeneralIterator (*this, 0);
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::ConstGeneralIterator	PagedArray<Type, PageSize>::BeginGeneral () const
{
	return ConstGeneralIterator (*this, 0);
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::GeneralIterator		PagedArray<Type, PageSize>::EndGeneral ()
{
	return GeneralIterator (*this, size);
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::ConstGeneralIterator	PagedArray<Type, PageSize>::EndGeneral () const
{
	return ConstGeneralIterator (*this, size);
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::ReverseIterator		PagedArray<Type, PageSize>::ReverseEnumerate ()
{
	return ReverseIterator (*this, size - 1);
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::ConstReverseIterator	PagedArray<Type, PageSize>::ReverseEnumerate () const
{
	return ConstReverseIterator (*this, size - 1);
}


template <class Type, UInt32 PageSize>
template <class Function>
void	PagedArray<Type, PageSize>::ReverseEnumerate (Function&& processor)
{
	for (UIndex i = size; i > 0; i--)
		processor (Cell (i - 1));
}


template <class Type, UInt32 PageSize>
template <class Function>
void	PagedArray<Type, PageSize>::ReverseEnumerate (Function&& processor) const
{
	for (UIndex i = size; i > 0; i--)
		processor (Cell (i - 1));
}


template <class Type, UInt32 PageSize>
template <class Function>
void	PagedArray<Type, PageSize>::ReverseEnumerateConst (Function&& processor) const
{
	ReverseEnumerate (processor);
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::ReverseIterator	PagedArray<Type, PageSize>::ReverseBegin ()
{
	return ReverseIterator (*this, size - 1);
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::ConstReverseIterator	PagedArray<Type, PageSize>::ReverseBegin () const
{
	return ConstReverseIterator (*this, size - 1);
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::ReverseIterator	PagedArray<Type, PageSize>::ReverseEnd ()
{
	return ReverseIterator (*this, -1);
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::ConstReverseIterator	PagedArray<Type, PageSize>::ReverseEnd () const
{
	return ConstReverseIterator (*this, -1);
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::Range	PagedArray<Type, PageSize>::operator() (UIndex begin, UIndex end)
{
	return { *this, begin, end };
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::ConstRange		PagedArray<Type, PageSize>::operator() (UIndex begin, UIndex end) const
{
	return { *this, begin, end };
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::Range	PagedArray<Type, PageSize>::operator() (FromBeginSelector, UIndex end)
{
	return { *this, 0, end };
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::ConstRange		PagedArray<Type, PageSize>::operator() (FromBeginSelector, UIndex end) const
{
	return { *this, 0, end };
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::Range	PagedArray<Type, PageSize>::operator() (UIndex begin, ToEndSelector)
{
	return { *this, begin, GetSize () };
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::ConstRange		PagedArray<Type, PageSize>::operator() (UIndex begin, ToEndSelector) const
{
	return { *this, begin, GetSize () };
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::ReverseRange	PagedArray<Type, PageSize>::Reverse ()
{
	return { *this };
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::ReverseConstRange	PagedArray<Type, PageSize>::Reverse () const
{
	return { *this };
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::ConversionEnumerator	PagedArray<Type, PageSize>::Convert () const
{
	return ConversionEnumerator (*this);
}


template <class Type, UInt32 PageSize>
auto&	PagedArray<Type, PageSize>::AsConst () const
{
	return reinterpret_cast<const PagedArray<typename Container<Type>::template MakeConstPtr<Type>::ConstType, PageSize>&> (*this);
}


template <class Type, UInt32 PageSize>
UIndex	PagedArray<Type, PageSize>::FindFirst (const Type& item, UIndex from, USize range) const
{
	NULL_REF_CHECK (item);
	REF_CHECK ((range == MaxUSize && from <= size) || (range != MaxUSize && from + range <= size));

	if (range == MaxUSize)
		range = size - from;

	ConstIterator it = GS::Find (Begin () + from, Begin () + from + range, item);

	if (it.GetIndex () == from + range)
		return MaxUIndex;

	return it.GetIndex ();
}


template <class Type, UInt32 PageSize>
UIndex	PagedArray<Type, PageSize>::FindFirst (const FunctionRef<bool (const Type&)> condition, UIndex from, USize range) const
{
	REF_CHECK ((range == MaxUSize && from <= size) || (range != MaxUSize && from + range <= size));

	if (range == MaxUSize)
		range = size - from;

	ConstIterator it = GS::Find (Begin () + from, Begin () + from + range, condition);

	if (it.GetIndex () == from + range)
		return MaxUIndex;

	return it.GetIndex ();
}


template <class Type, UInt32 PageSize>
UIndex	PagedArray<Type, PageSize>::FindLast (const Type& item) const
{
	NULL_REF_CHECK (item);

	for (UIndex i = size; i > 0; i--) {
		if (Cell (i - 1) == item)
			return i - 1;
	}

	return MaxUIndex;
}


template <class Type, UInt32 PageSize>
UIndex	PagedArray<Type, PageSize>::FindLast (const FunctionRef<bool (const Type&)> condition) const
{
	for (UIndex i = size; i > 0; i--) {
		if (condition (Cell (i - 1)))
			return i - 1;
	}

	return MaxUIndex;
}


template <class Type, UInt32 PageSize>
bool	PagedArray<Type, PageSize>::Contains (const Type& item) const
{
	NULL_REF_CHECK (item);

	return (GS::Find (Begin (), End (), item) != nullptr);
}


template <class Type, UInt32 PageSize>
bool	PagedArray<Type, PageSize>::Contains (const FunctionRef<bool (const Type&)> condition) const
{
	return (GS::Find (Begin (), End (), condition) != nullptr);
}


template <class Type, UInt32 PageSize>
bool	PagedArray<Type, PageSize>::Contains (std::initializer_list<Type> items) const
{
	for (const auto& item : items) {
		if (!Contains (item))
			return false;
	}

	return true;
}


template <class Type, UInt32 PageSize>
bool	PagedArray<Type, PageSize>::ContainsOnly (const FunctionRef<bool (const Type&)> condition) const
{
	for (const Type& item : *this) {
		if (!condition (item))
			return false;
	}

	return true;
}


template <class Type, UInt32 PageSize>
USize	PagedArray<Type, PageSize>::Count (const Type& item, UIndex from, USize range) const
{
	NULL_REF_CHECK (item);
	REF_CHECK ((range == MaxUSize && from <= size) || (range != MaxUSize && from + range <= size));

	if (range == MaxUSize)
		range = size - from;

	return GS::Count (Begin () + from, Begin () + from + range, item);
}


template <class Type, UInt32 PageSize>
USize	PagedArray<Type, PageSize>::Count (const FunctionRef<bool (const Type&)> condition, UIndex from, USize range) const
{
	REF_CHECK ((range == MaxUSize && from <= size) || (range != MaxUSize && from + range <= size));

	if (range == MaxUSize)
		range = size - from;

	return GS::Count (Begin () + from, Begin () + from + range, condition);
}


template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>	PagedArray<Type, PageSize>::Select (const FunctionRef<bool (const Type&)> condition) const
{
	PagedArray<Type, PageSize> result;
	for (UIndex i = 0; i < size; i++) {
		const Type& item = Cell (i);
		if (condition (item))
			result.Push (item);
	}

	return result;
}


template <class Type, UInt32 PageSize>
template <class ResultType>
PagedArray<ResultType, PageSize>	PagedArray<Type, PageSize>::Transform (const FunctionRef<ResultType (const Type&)> transformation) const
{
	PagedArray<ResultType, PageSize> result;
	for (UIndex i = 0; i < size; i++)
		result.Push (transformation (Cell (i)));

	return result;
}


template <class Type, UInt32 PageSize>
template <class ResultType>
PagedArray<ResultType, PageSize>	PagedArray<Type, PageSize>::Transform () const
{
	PagedArray<ResultType, PageSize> result;
	for (UIndex i = 0; i < size; i++)
		result.Push (static_cast<ResultType> (Cell (i)));

	return result;
}


template <class Type, UInt32 PageSize>
template <class Condition>
decltype (auto) PagedArray<Type, PageSize>::Where (Condition&& condition) const&
{
	return CreateConditionalView (*this, std::forward<Condition> (condition));
}


template <class Type, UInt32 PageSize>
template <class Condition>
decltype (auto) PagedArray<Type, PageSize>::Where (Condition&& condition) &&
{
	return CreateConditionalView (std::move (*this), std::forward<Condition> (condition));
}


template <class Type, UInt32 PageSize>
template <class T /*= Type*/, class /*= EnableIf<HasOperatorEquals<T>>*/>
bool	PagedArray<Type, PageSize>::operator== (const PagedArray& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	if (size != rightOp.size)
		return false;

	return (GS::IsEqual (Begin (), End (), rightOp.Begin ()));
}


template <class Type, UInt32 PageSize>
bool	PagedArray<Type, PageSize>::operator!= (const PagedArray& rightOp) const
{
	return !operator== (rightOp);
}


template <class Type, UInt32 PageSize>
bool	PagedArray<Type, PageSize>::IsEqual (std::initializer_list<Type> rightOp) const
{
	NULL_REF_CHECK (rightOp);

	if (size != rightOp.size ())
		return false;

	return (GS::IsEqual (Begin (), End (), rightOp.begin ()));
}


template <class Type, UInt32 PageSize>
GSErrCode	PagedArray<Type, PageSize>::Read (IChannel& ic)
{
	NULL_REF_CHECK (ic);

	Clear ();

	GS::InputFrame frame (ic, PagedArrayPrivate::classInfo);
	if (frame.GetStatus () != NoError)
		return frame.GetStatus ();

	USize newSize;
	GSErrCode errorCode = ic.Read (newSize);
	if (errorCode == NoError)
		SetSize (newSize);

	for (UIndex i = 0; i < newSize && errorCode == NoError; i++)
		errorCode = ic.Read (Cell (i));

	return errorCode;
}


template <class Type, UInt32 PageSize>
GSErrCode	PagedArray<Type, PageSize>::Write (OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	GS::OutputFrame frame (oc, PagedArrayPrivate::classInfo);

	GSErrCode errorCode = oc.Write (size);

	for (UIndex i = 0; i < size && errorCode == NoError; i++)
		errorCode = oc.Write (Cell (i));

	return errorCode;
}


template <class Type, UInt32 PageSize>
GSErrCode	PagedArray<Type, PageSize>::Read (IChannel& ic, const FunctionRef<GSErrCode (IChannel&, Type&)> reader)
{
	NULL_REF_CHECK (ic);

	Clear ();

	GS::InputFrame frame (ic, PagedArrayPrivate::classInfo);
	if (frame.GetStatus () != NoError)
		return frame.GetStatus ();

	USize newSize;
	GSErrCode errorCode = ic.Read (newSize);
	if (errorCode == NoError)
		SetSize (newSize);

	for (UIndex i = 0; i < newSize && errorCode == NoError; i++)
		errorCode = reader (ic, Cell (i));

	return errorCode;
}


template <class Type, UInt32 PageSize>
GSErrCode	PagedArray<Type, PageSize>::Write (OChannel& oc, const FunctionRef<GSErrCode (OChannel&, const Type&)> writer) const
{
	NULL_REF_CHECK (oc);

	GS::OutputFrame frame (oc, PagedArrayPrivate::classInfo);

	GSErrCode errorCode = oc.Write (size);

	for (UIndex i = 0; i < size && errorCode == NoError; i++)
		errorCode = writer (oc, Cell (i));

	return errorCode;
}


template <class Type, UInt32 PageSize>
bool	PagedArray<Type, PageSize>::CheckState () const
{
	if ((pageTable == nullptr && (capacity != 0 || deallocationCapacity != 0 || size != 0)) ||
		(pageTable != nullptr && (capacity == 0 || size == 0)) ||
		capacity < size || size < deallocationCapacity)
		return false;

	USize currentAllocationUnit = GetCurrentAllocationUnit ();
	USize prevAllocationUnit = GetPrevAllocationUnit (currentAllocationUnit);
	USize reserve = (currentAllocationUnit + prevAllocationUnit) * PageSize;
	if ((reserve <= capacity && capacity - deallocationCapacity != reserve) ||
		(reserve > capacity && deallocationCapacity != 0))
		return false;

	USize pageNumber = GetPageNumber ();
	for (UIndex i = 0; i < pageNumber; i++) {
		if (pageTable[i] == nullptr)
			return false;
	}

	USize pageTableCapacity = GetPageTableCapacity ();
	for (UIndex j = pageNumber; j < pageTableCapacity; j++) {
		if (pageTable[j] != nullptr)
			return false;
	}

	return true;
}


template <class Type, UInt32 PageSize>
Type&	PagedArray<Type, PageSize>::Cell (UIndex idx)
{
	return *(pageTable[idx >> Log2PageSize] + (idx & OffsetMask));
}


template <class Type, UInt32 PageSize>
const Type&		PagedArray<Type, PageSize>::Cell (UIndex idx) const
{
	return *(pageTable[idx >> Log2PageSize] + (idx & OffsetMask));
}


template <class Type, UInt32 PageSize>
USize	PagedArray<Type, PageSize>::GetPageNumber () const
{
	return (capacity / PageSize);
}


template <class Type, UInt32 PageSize>
USize	PagedArray<Type, PageSize>::GetPageTableCapacity () const
{
	if (capacity == 0)
		return 0;
	else
		return (1u << ComputeLog2 (GetPageNumber ()));
}


template <class Type, UInt32 PageSize>
USize	PagedArray<Type, PageSize>::GetNextPageTableCapacity (USize minCapacity)
{
	if (minCapacity == 0)
		return 0;
	else
		return (1u << ComputeLog2 (minCapacity));
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::SetIncreasedSize (USize increasedSize)
{
	DBASSERT (increasedSize >= size);

	IncreaseCapacity (increasedSize);

	for (UIndex i = size; i < increasedSize; i++)
		::new (&Cell (i)) Type ();

	size = increasedSize;
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::SetDecreasedSize (USize decreasedSize)
{
	DBASSERT (decreasedSize <= size);

	for (UIndex i = decreasedSize; i < size; i++)
		Cell (i).~Type ();

	size = decreasedSize;

	DecreaseCapacity (size);
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::IncreaseCapacity (USize minCapacity)
{
	if (minCapacity > capacity)
		AddNewPages (minCapacity);
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::AddNewPages (USize minCapacity)
{
	if (minCapacity <= capacity)
		return;		// there is no need to add new pages

	USize pageNumber = GetPageNumber ();

	USize minPageNumber = (minCapacity + PageSize - 1) >> Log2PageSize;
	USize growth = GetCurrentAllocationUnit ();
	USize newPageNumber = pageNumber;
	while (newPageNumber < minPageNumber) {
		growth = GetNextAllocationUnit (growth);
		newPageNumber += growth;
	}
	USize lastAU     = growth;
	USize prevLastAU = GetPrevAllocationUnit (lastAU);

	USize newCapacity = newPageNumber * PageSize;

	USize pageTableCapacity = GetPageTableCapacity ();

	if (newPageNumber > pageTableCapacity) {
		USize newPageTableCapacity = GetNextPageTableCapacity (newPageNumber);

		Type** newPageTable;
		if (newPageTableCapacity <= FixPageTableCapacity && pageTable != fixPageTable)
			newPageTable = fixPageTable;
		else
			newPageTable = reinterpret_cast<Type**> (AllocateBuffer (newPageTableCapacity * sizeof (Type*)));

		if (pageNumber > 0)
			::BNCopyMemory (newPageTable, pageTable, static_cast<GSSize>(pageNumber * sizeof (Type*)));
		if (pageTable != fixPageTable)
			DeleteBuffer (reinterpret_cast<char*> (pageTable));
		pageTable = newPageTable;

		for (UIndex k = newPageNumber; k < newPageTableCapacity; k++)
			pageTable[k] = nullptr;
	}

	growth = GetCurrentAllocationUnit ();
	UIndex i = pageNumber;
	while (i < newPageNumber) {
		growth = GetNextAllocationUnit (growth);
		Type* buffer = reinterpret_cast<Type*> (AllocateBuffer (growth * PageSize * sizeof (Type)));
		for (UIndex j = 0; j < growth; j++)
			pageTable[i + j] = buffer + j * PageSize;
		i += growth;
	}

	capacity = newCapacity;

	USize reserve = (lastAU + prevLastAU) * PageSize;
	if (capacity >= reserve)
		deallocationCapacity = capacity - reserve;
	else
		deallocationCapacity = 0;
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::DecreaseCapacity (USize minCapacity)
{
	if (minCapacity <= deallocationCapacity)
		DeleteUnusedPages (minCapacity);
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::DeleteUnusedPages (USize minCapacity)
{
	if (minCapacity > deallocationCapacity)
		return;		// it is not possible or worth to delete unused allocation units

	USize pageNumber = GetPageNumber ();

	USize minPageNumber = (minCapacity + PageSize - 1) >> Log2PageSize;
	USize growth = GetCurrentAllocationUnit ();
	USize newPageNumber = pageNumber;
	while (newPageNumber - growth >= minPageNumber && newPageNumber != 0) {
		newPageNumber -= growth;
		DeleteBuffer (reinterpret_cast<char*> (pageTable[newPageNumber]));
		for (UIndex i = 0; i < growth; i++)
			pageTable[newPageNumber + i] = nullptr;
		growth = GetPrevAllocationUnit (growth);
	}
	USize lastAU     = growth;
	USize prevLastAU = GetPrevAllocationUnit (lastAU);

	USize newCapacity = newPageNumber * PageSize;

	USize pageTableCapacity = GetPageTableCapacity ();

	USize newPageTableCapacity = GetNextPageTableCapacity (newPageNumber);

	if (newPageTableCapacity < pageTableCapacity) {
		Type** newPageTable = nullptr;
		if (newPageTableCapacity != 0) {
			if (newPageTableCapacity <= FixPageTableCapacity && pageTable != fixPageTable)
				newPageTable = fixPageTable;
			else
				newPageTable = reinterpret_cast<Type**> (AllocateBuffer (newPageTableCapacity * sizeof (Type*)));

			::BNCopyMemory (newPageTable, pageTable, newPageNumber * sizeof (Type*));
			for (UIndex j = newPageNumber; j < newPageTableCapacity; j++)
				newPageTable[j] = nullptr;
		}
		if (pageTable != fixPageTable)
			DeleteBuffer (reinterpret_cast<char*> (pageTable));
		pageTable = newPageTable;
	}

	capacity = newCapacity;

	USize reserve = (lastAU + prevLastAU) * PageSize;
	if (capacity >= reserve)
		deallocationCapacity = capacity - reserve;
	else
		deallocationCapacity = 0;
}


template <class Type, UInt32 PageSize>
ULong	PagedArray<Type, PageSize>::GetCurrentAllocationUnit () const
{
	return ((((capacity - deallocationCapacity) >> Log2PageSize) + 1) >> 1);
}


template <class Type, UInt32 PageSize>
ULong	PagedArray<Type, PageSize>::GetNextAllocationUnit (ULong currentAllocationUnit) const
{
	return currentAllocationUnit + 1;
}


template <class Type, UInt32 PageSize>
ULong	PagedArray<Type, PageSize>::GetPrevAllocationUnit (ULong currentAllocationUnit) const
{
	return (currentAllocationUnit == 0 ? 0 : currentAllocationUnit - 1);
}


template <class Type, UInt32 PageSize>
char*	PagedArray<Type, PageSize>::AllocateBuffer (USize bufferCapacity)
{
	return new char[bufferCapacity];
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::DeleteBuffer (char* buffer)
{
	delete [] buffer;
}


template <class Type, UInt32 PageSize>
ULong	PagedArray<Type, PageSize>::ComputeLog2 (ULong n)
{
	PRECOND_DEPRECATED (n > 0);

	n += n - 1;	// to reach the next power of 2 (if it isn't power of 2)

	ULong log2 = 0;
	while (n > 1) {
		n = n >> 1;
		log2++;
	}

	return log2;
}


template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>::ConversionEnumerator::ConversionEnumerator (const PagedArray& source):
	source (&source)
{
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::ConversionEnumerator::Enumerate (const std::function<void (const Type&)>& processor) const
{
	source->Enumerate (processor);
}


template <class Type, UInt32 PageSize>
USize	PagedArray<Type, PageSize>::ConversionEnumerator::GetSizeHint (void) const
{
	return source->GetSize ();
}


// === Global functions ================================================================================================

template <class Type, UInt32 PageSize>
auto		begin (PagedArray<Type, PageSize>& pagedArray)
{
	return pagedArray.Begin ();
}


template <class Type, UInt32 PageSize>
auto		end (PagedArray<Type, PageSize>& pagedArray)
{
	return pagedArray.End ();
}


template <class Type, UInt32 PageSize>
auto		begin (const PagedArray<Type, PageSize>& pagedArray)
{
	return pagedArray.Begin ();
}


template <class Type, UInt32 PageSize>
auto		end (const PagedArray<Type, PageSize>& pagedArray)
{
	return pagedArray.End ();
}


template <class Type, UInt32 PageSize>
auto	GetInserter (PagedArray<Type, PageSize>& pagedArray)
{
	return PushInserter<PagedArray<Type, PageSize>> (&pagedArray);
}


}	// namespace GS
// _____________________________ Class PagedArray ______________________________


#endif
