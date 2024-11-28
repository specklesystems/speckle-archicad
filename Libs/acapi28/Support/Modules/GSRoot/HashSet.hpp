
// *****************************************************************************
//
//                                 Class HashSet
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined HASHSET_HPP
#define HASHSET_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "AddInserter.hpp"
#include "Array.hpp"
#include "BaseAlgorithms.hpp"
#include "ConditionalView.hpp"
#include "Container.hpp"
#include "Enumerator.hpp"
#include "ForwardContainerIterator.hpp"
#include "ForwardIterator.hpp"
#include "FunctionRef.hpp"
#include "HashCommon.hpp"
#include "Inserter.hpp"
#include "PagedArray.hpp"

#include <functional>


// =============================== Class HashSet ===============================

namespace GS {

class GSROOT_DLL_EXPORT HashSetPrivate {
public:
	static ClassInfo	classInfo;	// HashSet's private classInfo
};


template <class Type>
class HashSetBase : public Container<Type> {
public:
	HashSetBase ()
	{
		static_assert (GS::HasGenerateHashValue<Type>, "'Type' has no GenerateHashValue ().");
		static_assert (GS::HasOperatorEquals<Type>,    "'Type' has no operator== ().");
	}
};


template <class Type>
class GS_EXPORT_TYPEINFO HashSet : public HashSetBase<Type> {
private:
	struct HashEntry {
		Type		item;	// stores the item
		HashEntry*	next;	// pointer to the next entry (or nullptr)

		HashEntry (const Type& item, HashEntry* next):
			item (item),
			next (next) {}

		HashEntry (Type&& item, HashEntry* next):
			item (std::move (item)),
			next (next) {}

		void	Move (HashEntry& source)
		{
			item = std::move (source.item);
			next = source.next;
		}
	};

	ArrayFB<HashEntry*, 1>	hashListTable;				// stores pointers to lists of hash entries
	PagedArray<HashEntry>	hashEntryTable;				// stores hash entries (lists of hash entries)
	float					averageSeekFactorLimit;		// specifies limit for the average seek factor above which the hash set should be rehashed (if the minimum fill factor is also reached)
	float					minFillFactor;				// specifies the minimum fill factor above which the rehashing should be considered (depending on the average seek factor)
	ULong					seekWeightSum;				// sum of seek weights (it is very unlikely to exceed MaxULong because in 4GB can fit at most 512 millions items which can have average seek factor 16, but if it yet does exceed then hash set will be not rehashed any more)

	HashEntry*	AccessEntry (const Type& item) const;

	void		EnsureAverageSeekFactor	  (void);
	void		DecreaseAverageSeekFactor (void);
	void		IncreaseAverageSeekFactor (void);
	USize		GetHashListTableSize (USize hashEntryCount) const;
	void		Rehash (USize newHashListTableSize);

	void		SwapPrimitiveMembers (HashSet& rightOp);

		// Iterator support

	struct IteratorState {
		UIndex	current;	// current entry

		explicit IteratorState (UIndex initIndex = 0): current (initIndex) {}
	};
	const Type&	GetCurrent (const IteratorState& state) const;
	void		Increment  (IteratorState& state) const;
	bool		IsEqual    (const IteratorState& state1, const IteratorState& state2) const;
	bool		IsEnd      (const IteratorState& state) const;

	friend class ConstForwardContainerIterator<HashSet, IteratorState, Type>;
	friend class ConstGeneralForwardContainerIterator<HashSet, IteratorState, Type>;

public:
		// Types

	typedef ConstForwardContainerIterator<HashSet, IteratorState, Type>			ConstIterator;
	typedef ConstGeneralForwardContainerIterator<HashSet, IteratorState, Type>	ConstGeneralIterator;

	class ConversionEnumerator;

		// Constructors

	HashSet ();
	explicit HashSet (float averageSeekFactorLimit, float minFillFactor = 0.0);
	explicit HashSet (ConstForwardIterator<Type> begin);
	explicit HashSet (ConstForwardIterator<Type> begin, ConstForwardIterator<Type> end);
	HashSet (const GS::ConversionEnumerator<Type>& enumerator);
	HashSet (std::initializer_list<Type> items);
	HashSet (const HashSet& source);
	HashSet (HashSet&& source);
	HashSet (const HashSet&&) = delete;

	template <class SourceType>
	explicit HashSet (const HashSet<SourceType>& source);

	HashSet&	operator= (const HashSet& source);
	HashSet&	operator= (HashSet&& source);
	HashSet&	operator= (const GS::ConversionEnumerator<Type>& enumerator);

	template <class SourceType>
	HashSet&	operator= (const HashSet<SourceType>& source);

   ~HashSet ();

	void					Move (HashSet& source);
	void					Move (FunctionRef<void (Type&&)> processor);

		// Content management

	bool					Add (const Type& item);
	bool					Add (Type&& item);

	template <class R, class = EnableIf<IsCompatibleRange<R, Type>>>
	void					Add (R&& range);

	bool					Delete    (const Type& item);
	void					DeleteAll (FunctionRef<bool (const Type&)> condition);

	void					Clear (void);

	void					Swap (HashSet& rightOp);

	USize					GetSize (void) const;
	bool					IsEmpty (void) const;

		// Content query

	ConstIterator			Enumerate (void) const;

	template <class Function>
	void					Enumerate (Function&& processor) const;

	ConstIterator			Begin (void) const;

	ConstIterator			End	(void) const;

	ConstGeneralIterator	EnumerateGeneral (void) const;
	ConstGeneralIterator	BeginGeneral (void) const;
	ConstGeneralIterator	EndGeneral	(void) const;

	const Type&				GetTheOnlyItem () const gs_lifebound;

	ConversionEnumerator	Convert (void) const;

	auto&					AsConst (void) const gs_lifebound;

	bool					Contains (const Type& item) const;
	bool					Contains (std::initializer_list<Type> items) const;
	bool					Contains (FunctionRef<bool (const Type&)> condition) const;

	const Type&				Get (const Type& item) const gs_lifebound;
	bool					Get (const Type& item, Type* result) const;
	bool					Get (const Type& item, const Type** result) const;

	void					SetEquivalent (const Type& oldItem, const Type& newItem);
	Type&					ModifyValue	  (const Type& item) gs_lifebound;

	HashSet					Select (FunctionRef<bool (const Type&)> condition) const;

	template <class ResultType>
	HashSet<ResultType>		Transform (FunctionRef<ResultType (const Type&)> transformation) const;

	template <class ResultType>
	HashSet<ResultType>		Transform () const;

	template <class Condition>
	decltype (auto)			Where (Condition&& condition) const&;

	template <class Condition>
	decltype (auto)			Where (Condition&& condition) &&;

		// Equality operations

	bool					operator== (const HashSet& rightOp) const;
	bool					operator!= (const HashSet& rightOp) const;

		// Set operations

	bool					IsSubsetOf		   (const HashSet& rightOp) const;
	bool					IsSupersetOf	   (const HashSet& rightOp) const;
	bool					IsStrictSubsetOf   (const HashSet& rightOp) const;
	bool					IsStrictSupersetOf (const HashSet& rightOp) const;

	void					Unify			   (const HashSet& rightOp);
	void					Unify			   (HashSet&&      rightOp);
	void					Intersect		   (const HashSet& rightOp);
	void					Subtract		   (const HashSet& rightOp);

		// Performance tuning

	void					EnsureCapacity		 (USize minCapacity);

	double					GetAverageSeekFactor (void) const;
	ULong					FindMaxSeekFactor	 (void) const;
	double					GetFillFactor		 (void) const;
	ULong					CountEmptyLists		 (void) const;

		// I/O

	GSErrCode				Read  (IChannel& ic);
	GSErrCode				Read  (IChannel& ic, FunctionRef<GSErrCode (IChannel&, Type&)> reader);

	GSErrCode				Write (OChannel& oc) const;
	GSErrCode				Write (OChannel& oc, FunctionRef<GSErrCode (OChannel&, const Type&)> writer) const;

		// Debug

	bool					CheckState (void) const;

	const Type&				GetAnItem (ULong rnd) const gs_lifebound;

		// Types

	class ConversionEnumerator: public GS::ConversionEnumerator<Type> {
	private:
		const HashSet* source;

	public:
		ConversionEnumerator (const HashSet& source);

		virtual void	Enumerate (const std::function<void (const Type&)>& processor) const override;

		virtual USize	GetSizeHint (void) const override;
	};
};


// === HashSet methods =================================================================================================

template <class Type>
HashSet<Type>::HashSet ():
	HashSet (0.0, 0.0)
{
}


template <class Type>
HashSet<Type>::HashSet (float averageSeekFactorLimit, float minFillFactor /*= 0.0*/)
{
	ARG_CHECK (averageSeekFactorLimit >= 0.0);
	ARG_CHECK (minFillFactor >= 0.0);

	if (averageSeekFactorLimit < 1.0)	// 0.0 indicates the default value, whereas values below 1.0 have no sense
		averageSeekFactorLimit = 2.0;

	if (minFillFactor < 0.01)	// 0.0 indicates the default value, whereas "small" values are unsafe because may cause continuous reallocation in some very unlikely circumstances
		minFillFactor = 0.75;

	this->averageSeekFactorLimit = averageSeekFactorLimit;
	this->minFillFactor			 = minFillFactor;
	this->seekWeightSum			 = 0;
}


template <class Type>
HashSet<Type>::HashSet (std::initializer_list<Type> items):
	HashSet ()
{
	EnsureCapacity (USize (items.size ()));

	for (const auto& item : items)
		Add (item);
}


template <class Type>
HashSet<Type>::HashSet (ConstForwardIterator<Type> begin):
	HashSet ()
{
	while (begin != nullptr) {
		Add (*begin);
		++begin;
	}
}


template <class Type>
HashSet<Type>::HashSet (ConstForwardIterator<Type> begin, ConstForwardIterator<Type> end):
	HashSet ()
{
	while (begin != end) {
		Add (*begin);
		++begin;
	}
}


template <class Type>
HashSet<Type>::HashSet (const GS::ConversionEnumerator<Type>& enumerator):
	averageSeekFactorLimit (2.0),
	minFillFactor (0.75),
	seekWeightSum (0)
{
	EnsureCapacity (enumerator.GetSizeHint ());

	enumerator.Enumerate (GetInserter (*this));
}


template <class Type>
HashSet<Type>::HashSet (const HashSet& source)
{
	averageSeekFactorLimit = source.averageSeekFactorLimit;
	minFillFactor		   = source.minFillFactor;
	seekWeightSum		   = 0;

	for (const Type& item : source)
		hashEntryTable.PushNew (item, nullptr);

	Rehash (GetHashListTableSize (hashEntryTable.GetSize ()));
}


template <class Type>
HashSet<Type>::HashSet (HashSet&& source):
	averageSeekFactorLimit (2.0),
	minFillFactor (0.75),
	seekWeightSum (0)
{
	Move (source);
}


template <class Type>
HashSet<Type>&	HashSet<Type>::operator= (const HashSet& source)
{
	HashSet copy = source;

	hashListTable.Move (copy.hashListTable);
	hashEntryTable.Move (copy.hashEntryTable);
	SwapPrimitiveMembers (copy);

	return *this;
}


template <class Type>
HashSet<Type>&	HashSet<Type>::operator= (HashSet&& source)
{
	Move (source);

	return *this;
}


template <class Type>
HashSet<Type>&	HashSet<Type>::operator= (const GS::ConversionEnumerator<Type>& enumerator)
{
	Clear ();
	EnsureCapacity (enumerator.GetSizeHint ());

	enumerator.Enumerate ([&] (const Type& item) {
		Add (item);
	});

	return *this;
}


template <class Type>
HashSet<Type>::~HashSet () = default;


template <class Type>
template <class SourceType>
HashSet<Type>::HashSet (const HashSet<SourceType>& source):
	HashSet ()
{
	static_assert (IsConvertible<SourceType, Type>, "'SourceType' is not convertible to 'Type'.");

	for (const SourceType& item : source)
		hashEntryTable.PushNew (item, nullptr);

	Rehash (GetHashListTableSize (hashEntryTable.GetSize ()));
}


template <class Type>
template <class SourceType>
HashSet<Type>&	HashSet<Type>::operator= (const HashSet<SourceType>& source)
{
	HashSet<Type> copy (source);

	hashListTable.Move (copy.hashListTable);
	hashEntryTable.Move (copy.hashEntryTable);
	SwapPrimitiveMembers (copy);

	return *this;
}


template <class Type>
void	HashSet<Type>::Move (HashSet& source)
{
	if (DBERROR (&source == this))
		return;

	hashListTable.Move (source.hashListTable);
	hashEntryTable.Move (source.hashEntryTable);
	SwapPrimitiveMembers (source);

	source.Clear ();
}


template <class Type>
void			HashSet<Type>::Move (const FunctionRef<void (Type&&)> processor)
{
	for (UIndex i = 0; i < hashEntryTable.GetSize (); ++i)
		processor (std::move (hashEntryTable[i].item));

	Clear ();
}


template <class Type>
bool	HashSet<Type>::Add (const Type& item)
{
	if (hashListTable.IsEmpty ()) {
		USize firstHashListTableSize = GetNextHashCapacity (0);
		hashListTable.SetCapacity (firstHashListTableSize);	// in this way SetSize will not waste capacity
		hashListTable.SetSize (firstHashListTableSize);
		hashListTable.Fill (nullptr);
	}

	UIndex hashListIndex = GS::CalculateHashValue (item) % hashListTable.GetSize ();
	HashEntry* hashEntry = hashListTable[hashListIndex];
	UIndex hashListLength = 0;
	while (hashEntry != nullptr) {
		if (hashEntry->item == item)
			return false;
		hashListLength++;
		hashEntry = hashEntry->next;
	}
	seekWeightSum += hashListLength + 1;

	hashEntryTable.PushNew (item, hashListTable[hashListIndex]);
	hashListTable[hashListIndex] = &hashEntryTable.GetLast ();

	EnsureAverageSeekFactor ();

	return true;
}


template <class Type>
bool	HashSet<Type>::Add (Type&& item)
{
	if (hashListTable.IsEmpty ()) {
		USize firstHashListTableSize = GetNextHashCapacity (0);
		hashListTable.SetCapacity (firstHashListTableSize);	// in this way SetSize will not waste capacity
		hashListTable.SetSize (firstHashListTableSize);
		hashListTable.Fill (nullptr);
	}

	UIndex hashListIndex = GS::CalculateHashValue (item) % hashListTable.GetSize ();
	HashEntry* hashEntry = hashListTable[hashListIndex];
	UIndex hashListLength = 0;
	while (hashEntry != nullptr) {
		if (hashEntry->item == item)
			return false;
		hashListLength++;
		hashEntry = hashEntry->next;
	}
	seekWeightSum += hashListLength + 1;

	hashEntryTable.PushNew (std::move (item), hashListTable[hashListIndex]);
	hashListTable[hashListIndex] = &hashEntryTable.GetLast ();

	EnsureAverageSeekFactor ();

	return true;
}


template <class Type>
template <class R, class /*SFINAE*/>
void	HashSet<Type>::Add (R&& range)
{
	const auto endIt = GS::EndADL (range);

	for (auto it = GS::BeginADL (range); it != endIt; ++it)
		Add (*it);
}


template <class Type>
bool	HashSet<Type>::Delete (const Type& item)
{
		// deleting the entry

	if (hashEntryTable.IsEmpty ())
		return false;

	UIndex hashListIndex = GS::CalculateHashValue (item) % hashListTable.GetSize ();
	HashEntry* hashEntry = hashListTable[hashListIndex];
	HashEntry* prevHashEntry = nullptr;
	while (hashEntry != nullptr) {
		if (hashEntry->item == item)
			break;
		prevHashEntry = hashEntry;
		hashEntry = hashEntry->next;
	}
	if (hashEntry == nullptr)
		return false;

	if (prevHashEntry == nullptr)
		hashListTable[hashListIndex] = hashEntry->next;
	else
		prevHashEntry->next = hashEntry->next;

		// updating sum of seek weights

	UIndex hashListLength = 0;
	HashEntry* listEntry = hashListTable[hashListIndex];
	while (listEntry != nullptr) {
		hashListLength++;
		listEntry = listEntry->next;
	}
	seekWeightSum -= hashListLength + 1;

		// eliminating the hole from the hash entry table

	HashEntry* lastPhysicalEntry = &hashEntryTable.GetLast ();
	if (hashEntry != lastPhysicalEntry) {
		hashEntry->Move (*lastPhysicalEntry);

		UIndex lpeListIndex = GS::CalculateHashValue (hashEntry->item) % hashListTable.GetSize ();
		HashEntry* he = hashListTable[lpeListIndex];
		HashEntry* prevLPE = nullptr;
		while (he != lastPhysicalEntry) {
			prevLPE = he;
			he = he->next;
		}

		if (prevLPE == nullptr)
			hashListTable[lpeListIndex] = hashEntry;
		else
			prevLPE->next = hashEntry;
	}

	hashEntryTable.DeleteLast ();

	if (GetFillFactor () <= minFillFactor / 4)
		IncreaseAverageSeekFactor ();	// decreases capacity of the hashListTable and increases fill factor

	return true;
}


template <class Type>
void	HashSet<Type>::DeleteAll (const FunctionRef<bool (const Type&)> condition)
{
	ArrayFB<Type, 8> itemsToDelete;

	for (const Type& item : *this) {
		if (condition (item))
			itemsToDelete.Push (item);
	}

	for (const Type& item : itemsToDelete)
		Delete (item);
}


template <class Type>
void	HashSet<Type>::Clear (void)
{
	hashListTable.Clear ();
	hashEntryTable.Clear ();

	seekWeightSum = 0;
}


template <class Type>
void	HashSet<Type>::Swap (HashSet& rightOp)
{
	if (this == &rightOp)
		return;

	hashListTable.Swap (rightOp.hashListTable);
	hashEntryTable.Swap (rightOp.hashEntryTable);
	SwapPrimitiveMembers (rightOp);
}


template <class Type>
void	HashSet<Type>::SwapPrimitiveMembers (HashSet& rightOp)
{
	GS::Swap (averageSeekFactorLimit, rightOp.averageSeekFactorLimit);
	GS::Swap (minFillFactor,		  rightOp.minFillFactor);
	GS::Swap (seekWeightSum,		  rightOp.seekWeightSum);
}


template <class Type>
USize	HashSet<Type>::GetSize (void) const
{
	return hashEntryTable.GetSize ();
}


template <class Type>
bool	HashSet<Type>::IsEmpty (void) const
{
	return (hashEntryTable.IsEmpty ());
}


template <class Type>
typename HashSet<Type>::ConstIterator	HashSet<Type>::Enumerate (void) const
{
	return ConstIterator (*this, IteratorState (0));
}


template <class Type>
template <class Function>
void	HashSet<Type>::Enumerate (Function&& processor) const
{
	for (UIndex i = 0; i < hashEntryTable.GetSize (); i++)
		processor (const_cast<const Type&> (hashEntryTable[i].item));
}


template <class Type>
typename HashSet<Type>::ConstIterator	HashSet<Type>::Begin (void) const
{
	return ConstIterator (*this, IteratorState (0));
}


template <class Type>
typename HashSet<Type>::ConstIterator	HashSet<Type>::End (void) const
{
	return ConstIterator (*this, IteratorState (hashEntryTable.GetSize ()));
}


template <class Type>
typename HashSet<Type>::ConstGeneralIterator		HashSet<Type>::EnumerateGeneral (void) const
{
	return ConstGeneralIterator (*this, IteratorState (0));
}


template <class Type>
typename HashSet<Type>::ConstGeneralIterator		HashSet<Type>::BeginGeneral (void) const
{
	return ConstGeneralIterator (*this, IteratorState (0));
}


template <class Type>
typename HashSet<Type>::ConstGeneralIterator		HashSet<Type>::EndGeneral (void) const
{
	return ConstGeneralIterator (*this, IteratorState (hashEntryTable.GetSize ()));
}


template <class Type>
const Type&		HashSet<Type>::GetTheOnlyItem (void) const
{
	DBASSERT (hashEntryTable.GetSize () == 1);

	return hashEntryTable[0].item;
}


template <class Type>
typename HashSet<Type>::ConversionEnumerator	HashSet<Type>::Convert (void) const
{
	return ConversionEnumerator (*this);
}


template <class Type>
auto&	HashSet<Type>::AsConst (void) const
{
	return reinterpret_cast<const HashSet<typename Container<Type>::template MakeConstPtr<Type>::ConstType>&> (*this);
}


template <class Type>
bool	HashSet<Type>::Contains (const Type& item) const
{
	return (AccessEntry (item) != nullptr);
}


template <class Type>
bool	HashSet<Type>::Contains (std::initializer_list<Type> items) const
{
	for (const auto& item : items) {
		if (!Contains (item))
			return false;
	}

	return true;
}


template <class Type>
bool	HashSet<Type>::Contains (const FunctionRef<bool (const Type&)> condition) const
{
	for (const Type& item : *this) {
		if (condition (item)) {
			return true;
		}
	}
	return false;
}


template <class Type>
const Type&		HashSet<Type>::Get (const Type& item) const
{
	HashEntry* hashEntry = AccessEntry (item);
	REF_CHECK (hashEntry != nullptr);

	return hashEntry->item;
}


template <class Type>
bool	HashSet<Type>::Get (const Type& item, Type* result) const
{
	NULL_PTR_CHECK (result);

	HashEntry* hashEntry = AccessEntry (item);
	if (hashEntry == nullptr)
		return false;

	*result = hashEntry->item;
	return true;
}


template <class Type>
bool	HashSet<Type>::Get (const Type& item, const Type** result) const
{
	NULL_PTR_CHECK (result);

	const HashEntry* hashEntry = AccessEntry (item);
	if (hashEntry == nullptr)
		return false;

	*result = &hashEntry->item;
	return true;
}


template <class Type>
void	HashSet<Type>::SetEquivalent (const Type& oldItem, const Type& newItem)
{
	DBASSERT (oldItem == newItem);

	HashEntry* hashEntry = AccessEntry (oldItem);
	REF_CHECK (hashEntry != nullptr);

	hashEntry->item = newItem;
}


template <class Type>
Type&	HashSet<Type>::ModifyValue (const Type& item)
{
	HashEntry* hashEntry = AccessEntry (item);
	REF_CHECK (hashEntry != nullptr);

	return hashEntry->item;
}


template <class Type>
HashSet<Type>	HashSet<Type>::Select (const FunctionRef<bool (const Type&)> condition) const
{
	HashSet<Type> result;
	for (const Type& item : *this)
		if (condition (item))
			result.Add (item);

	return result;
}


template <class Type>
template <class ResultType>
HashSet<ResultType>	HashSet<Type>::Transform (const FunctionRef<ResultType (const Type&)> transformation) const
{
	HashSet<ResultType> result;
	for (const Type& item : *this)
		result.Add (transformation (item));

	return result;
}


template <class Type>
template <class ResultType>
HashSet<ResultType>	HashSet<Type>::Transform () const
{
	HashSet<ResultType> result;
	for (const Type& item : *this)
		result.Add (static_cast<ResultType> (item));

	return result;
}


template <class Type>
template <class Condition>
decltype (auto)	HashSet<Type>::Where (Condition&& condition) const&
{
	return CreateConditionalView (*this, std::forward<Condition> (condition));
}


template <class Type>
template <class Condition>
decltype (auto)	HashSet<Type>::Where (Condition&& condition) &&
{
	return CreateConditionalView (std::move (*this), std::forward<Condition> (condition));
}


template <class Type>
bool	HashSet<Type>::operator== (const HashSet& rightOp) const
{
	if (hashEntryTable.GetSize () != rightOp.hashEntryTable.GetSize ())
		return false;

	for (UIndex i = 0; i < hashEntryTable.GetSize (); ++i) {
		if (!rightOp.Contains (hashEntryTable[i].item))
			return false;
	}

	return true;
}


template <class Type>
bool	HashSet<Type>::operator!= (const HashSet& rightOp) const
{
	return !operator== (rightOp);
}


template <class Type>
bool	HashSet<Type>::IsSubsetOf (const HashSet& rightOp) const
{
	if (GetSize () > rightOp.GetSize ())
		return false;

	for (const Type& item : *this) {
		if (!rightOp.Contains (item))
			return false;
	}

	return true;
}


template <class Type>
bool	HashSet<Type>::IsSupersetOf (const HashSet& rightOp) const
{
	return rightOp.IsSubsetOf (*this);
}


template <class Type>
bool	HashSet<Type>::IsStrictSubsetOf (const HashSet& rightOp) const
{
	return GetSize () < rightOp.GetSize () && IsSubsetOf (rightOp);
}


template <class Type>
bool	HashSet<Type>::IsStrictSupersetOf (const HashSet& rightOp) const
{
	return rightOp.IsStrictSubsetOf (*this);
}


template <class Type>
void	HashSet<Type>::Unify (const HashSet& rightOp)
{
	for (const Type& item : rightOp)
		Add (item);
}


template <class Type>
void	HashSet<Type>::Unify (HashSet&& rightOp)
{
	for (const Type& item : rightOp)
		Add (const_cast<Type&&> (item));
}


template <class Type>
void	HashSet<Type>::Intersect (const HashSet& rightOp)
{
	Array<Type> uncommonItems;
	uncommonItems.EnsureCapacity (GetSize ());

	for (const Type& item : *this) {
		if (!rightOp.Contains (item))
			uncommonItems.Push (item);
	}

	for (const Type& item : uncommonItems)
		Delete (item);
}


template <class Type>
void	HashSet<Type>::Subtract (const HashSet& rightOp)
{
	for (const Type& item : rightOp)
		Delete (item);
}


template <class Type>
void	HashSet<Type>::EnsureCapacity (USize minCapacity)
{
	if (minCapacity <= hashEntryTable.GetSize ())
		return;

	USize newHashListTableSize = GetHashListTableSize (minCapacity);
	if (newHashListTableSize <= hashListTable.GetSize ())
		return;

	Rehash (newHashListTableSize);
}


template <class Type>
double	HashSet<Type>::GetAverageSeekFactor (void) const
{
	if (hashEntryTable.IsEmpty ())
		return 0.0;
	else
		return (static_cast<double> (seekWeightSum) / static_cast<double> (hashEntryTable.GetSize ()));
}


template <class Type>
ULong	HashSet<Type>::FindMaxSeekFactor (void) const
{
	ULong maxSeekFactor = 0;
	USize hashListCount = hashListTable.GetSize ();
	for (UIndex i = 0; i < hashListCount; i++) {
		HashEntry* hashEntry = hashListTable[i];
		ULong seekfactor = 0;
		while (hashEntry != nullptr) {
			seekfactor++;
			hashEntry = hashEntry->next;
		}
		if (seekfactor > maxSeekFactor)
			maxSeekFactor = seekfactor;
	}

	return maxSeekFactor;
}


template <class Type>
double	HashSet<Type>::GetFillFactor (void) const
{
	if (hashListTable.GetSize () == 0)
		return 0.0;
	else
		return (static_cast<double> (hashEntryTable.GetSize ()) / static_cast<double> (hashListTable.GetSize ()));
}


template <class Type>
ULong	HashSet<Type>::CountEmptyLists (void) const
{
	ULong emptyListCount = 0;
	USize hashListCount = hashListTable.GetSize ();
	for (UIndex i = 0; i < hashListCount; i++) {
		if (hashListTable[i] == nullptr)
			emptyListCount++;
	}

	return emptyListCount;
}


template <class Type>
GSErrCode	HashSet<Type>::Read (IChannel& ic)
{
	Clear ();

	InputFrame frame (ic, HashSetPrivate::classInfo);
	if (frame.GetStatus () != NoError)
		return frame.GetStatus ();

	USize newSize;
	GSErrCode errorCode = ic.Read (newSize);

	Type item = Type ();
	for (UIndex i = 0; i < newSize && errorCode == NoError; i++) {
		errorCode = ic.Read (item);
		if (errorCode == NoError)
			hashEntryTable.PushNew (item, nullptr);
	}

	if (errorCode == NoError)
		Rehash (GetHashListTableSize (newSize));

	return errorCode;
}


template <class Type>
GSErrCode	HashSet<Type>::Read (IChannel& ic, const FunctionRef<GSErrCode (IChannel&, Type&)> reader)
{
	Clear ();

	InputFrame frame (ic, HashSetPrivate::classInfo);
	if (frame.GetStatus () != NoError)
		return frame.GetStatus ();

	USize newSize;
	GSErrCode errorCode = ic.Read (newSize);

	for (UIndex i = 0; i < newSize && errorCode == NoError; i++) {
		Type item {};
		errorCode = reader (ic, item);
		if (errorCode == NoError)
			hashEntryTable.PushNew (std::move (item), nullptr);
	}

	if (errorCode == NoError)
		Rehash (GetHashListTableSize (newSize));

	return errorCode;
}



template <class Type>
GSErrCode	HashSet<Type>::Write (OChannel& oc) const
{
	OutputFrame frame (oc, HashSetPrivate::classInfo);

	USize hashEntryCount = hashEntryTable.GetSize ();

	GSErrCode errorCode = oc.Write (hashEntryCount);

	for (UIndex i = 0; i < hashEntryCount && errorCode == NoError; i++) {
		errorCode = oc.Write (hashEntryTable[i].item);
	}

	return errorCode;
}


template <class Type>
GSErrCode	HashSet<Type>::Write (OChannel& oc, const FunctionRef<GSErrCode (OChannel&, const Type&)> writer) const
{
	OutputFrame frame (oc, HashSetPrivate::classInfo);

	USize hashEntryCount = hashEntryTable.GetSize ();

	GSErrCode errorCode = oc.Write (hashEntryCount);

	for (UIndex i = 0; i < hashEntryCount && errorCode == NoError; i++) {
		errorCode = writer (oc, hashEntryTable[i].item);
	}

	return errorCode;
}


template <class Type>
bool	HashSet<Type>::CheckState (void) const
{
	if (!hashListTable.CheckState ()  ||
		!hashEntryTable.CheckState ())
		return false;

	if (hashEntryTable.GetSize () > seekWeightSum)
		return false;

	USize computedSize = 0;
	ULong computedSeekWeightSum = 0;
	USize hashListCount = hashListTable.GetSize ();
	for (UIndex i = 0; i < hashListCount; i++) {
		HashEntry* hashEntry = hashListTable[i];
		ULong weight = 1;
		while (hashEntry != nullptr) {
			computedSize++;
			computedSeekWeightSum += weight;
			weight++;
			hashEntry = hashEntry->next;
		}
	}

	if (hashEntryTable.GetSize () != computedSize || seekWeightSum != computedSeekWeightSum)
		return false;

	return true;
}


template <class Type>
const Type&		HashSet<Type>::GetAnItem (ULong rnd) const
{
	PRECOND_DEPRECATED (!hashEntryTable.IsEmpty ());

	return hashEntryTable[rnd % hashEntryTable.GetSize ()].item;
}


template <class Type>
typename HashSet<Type>::HashEntry*	HashSet<Type>::AccessEntry (const Type& item) const
{
	USize hasListCount = hashListTable.GetSize ();
	if (hasListCount == 0)
		return nullptr;

	HashEntry* hashEntry = hashListTable[GS::CalculateHashValue (item) % hasListCount];

	while (hashEntry != nullptr) {
		if (hashEntry->item == item)
			return hashEntry;
		hashEntry = hashEntry->next;
	}

	return nullptr;
}


template <class Type>
void	HashSet<Type>::EnsureAverageSeekFactor	(void)
{
	if (GetFillFactor () < minFillFactor)
		return;

	if (GetAverageSeekFactor () <= averageSeekFactorLimit)
		return;

	DecreaseAverageSeekFactor ();
}


template <class Type>
void	HashSet<Type>::DecreaseAverageSeekFactor (void)
{
	Rehash (GetNextHashCapacity (hashListTable.GetSize ()));
}


template <class Type>
void	HashSet<Type>::IncreaseAverageSeekFactor (void)
{
	if (hashEntryTable.GetSize () == 0)
		Rehash (0);
	else
		Rehash (GetPreviousHashCapacity (hashListTable.GetSize ()));
}


template <class Type>
USize	HashSet<Type>::GetHashListTableSize (USize hashEntryCount) const
{
	USize optimalListTableSize = static_cast<USize> (static_cast<double> (hashEntryCount) / (2.0 * averageSeekFactorLimit  - 1.0));
	return GetNextHashCapacity (GetNextHashCapacity (optimalListTableSize));
}


template <class Type>
void	HashSet<Type>::Rehash (USize newHashListTableSize)
{
	hashListTable.SetCapacity (newHashListTableSize);	// if the new capacity is less than old size then this call has no effect
	hashListTable.SetSize (newHashListTableSize);		// SetSize will not waste capacity because of SetCapacity calls
	hashListTable.SetCapacity (newHashListTableSize);	// if the new capacity is greater than old size then this call has no effect
	hashListTable.Fill (nullptr);

	USize newHashListCount = newHashListTableSize;

	USize hashEntryCount = hashEntryTable.GetSize ();
	for (UIndex i = 0; i < hashEntryCount; i++) {
		HashEntry& hashEntry = hashEntryTable[i];
		UIndex newHashListIndex = GS::CalculateHashValue (hashEntry.item) % newHashListCount;
		hashEntry.next = hashListTable[newHashListIndex];
		hashListTable[newHashListIndex] = &hashEntry;
	}

		// recalculating sum of seek weights

	seekWeightSum = 0;
	for (UIndex j = 0; j < newHashListCount; j++) {
		HashEntry* hashEntry = hashListTable[j];
		ULong weight = 1;
		while (hashEntry != nullptr) {
			seekWeightSum += weight;
			weight++;
			hashEntry = hashEntry->next;
		}
	}
}


template <class Type>
const Type&  HashSet<Type>::GetCurrent (const IteratorState& state) const
{
	return hashEntryTable[state.current].item;
}


template <class Type>
void	HashSet<Type>::Increment (IteratorState& state) const
{
	state.current++;
}


template <class Type>
bool	HashSet<Type>::IsEqual (const IteratorState& state1, const IteratorState& state2) const
{
	if (state1.current >= hashEntryTable.GetSize () && state2.current >= hashEntryTable.GetSize ())
		return true;

	return (state1.current == state2.current);
}


template <class Type>
bool	HashSet<Type>::IsEnd (const IteratorState& state) const
{
	return (state.current >= hashEntryTable.GetSize ());
}


template <class Type>
HashSet<Type>::ConversionEnumerator::ConversionEnumerator (const HashSet& source):
	source (&source)
{
}


template <class Type>
void	HashSet<Type>::ConversionEnumerator::Enumerate (const std::function<void (const Type&)>& processor) const
{
	source->Enumerate (processor);
}


template <class Type>
USize	HashSet<Type>::ConversionEnumerator::GetSizeHint (void) const
{
	return source->GetSize ();
}


// === Global functions ================================================================================================

template <class Type>
auto	begin (HashSet<Type>& hashSet)
{
	return hashSet.Begin ();
}


template <class Type>
auto	end (HashSet<Type>& hashSet)
{
	return hashSet.End ();
}


template <class Type>
auto	begin (const HashSet<Type>& hashSet)
{
	return hashSet.Begin ();
}


template <class Type>
auto	end (const HashSet<Type>& hashSet)
{
	return hashSet.End ();
}


template <class Type>
bool	AreIntersecting (const HashSet<Type>& leftOp, const HashSet<Type>& rightOp)
{
	const HashSet<Type>* smallerSet;
	const HashSet<Type>* largerSet;
	SelectSmallerAndLargerContainer (leftOp, rightOp, smallerSet, largerSet);

	for (const Type& item : *smallerSet) {
		if (largerSet->Contains (item))
			return true;
	}

	return false;
}


template <class Type>
bool	AreDisjoint (const HashSet<Type>& leftOp, const HashSet<Type>& rightOp)
{
	return !AreIntersecting (leftOp, rightOp);
}


template <class Type>
HashSet<Type>	Union (const HashSet<Type>& leftOp, const HashSet<Type>& rightOp)
{
	HashSet<Type> result (leftOp);
	result.Unify (rightOp);
	return result;
}


template <class Type>
HashSet<Type>	Intersection (const HashSet<Type>& leftOp, const HashSet<Type>& rightOp)
{
	const HashSet<Type>* smallerSet;
	const HashSet<Type>* largerSet;
	SelectSmallerAndLargerContainer (leftOp, rightOp, smallerSet, largerSet);

	HashSet<Type> result;

	for (const Type& item : *smallerSet) {
		if (largerSet->Contains (item))
			result.Add (item);
	}

	return result;
}


template <class Type>
HashSet<Type>	Subtraction (const HashSet<Type>& leftOp, const HashSet<Type>& rightOp)
{
	HashSet<Type> result;

	for (const Type& item : leftOp) {
		if (!rightOp.Contains (item))
			result.Add (item);
	}

	return result;
}


template <class Type>
auto	GetInserter (HashSet<Type>& hashSet)
{
	return AddInserter<HashSet<Type>> (&hashSet);
}

}	// namespace GS


#endif
