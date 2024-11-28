
// *****************************************************************************
//
//                                Class HashTable
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined HASHTABLE_HPP
#define HASHTABLE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "AddInserter.hpp"
#include "Array.hpp"
#include "AssociativeContainer.hpp"
#include "BaseAlgorithms.hpp"
#include "ForwardContainerIterator.hpp"
#include "FunctionRef.hpp"
#include "HashCommon.hpp"
#include "Inserter.hpp"
#include "Optional.hpp"
#include "PagedArray.hpp"
#include "Pair.hpp"

#include <functional>


// ------------------------------ Predeclarations ------------------------------

namespace GS {

class ObjectState;

template <class Type1, class Type2>
GSErrCode	StorePair (ObjectState& os, const Type1& first, const Type2& second);

}


// ============================== Class HashTable ==============================

namespace GS {

class GSROOT_DLL_EXPORT HashTablePrivate {
public:
	static GS::ClassInfo	classInfo;	// HashTable's private classInfo

	static USize	GetNextCapacity		(USize oldCapacity);
	static USize	GetPreviousCapacity	(USize oldCapacity);
};


template <class Key, class Value>
class HashTableBase : public AssociativeContainer<Key, Value> {
public:
	HashTableBase ()
	{
		static_assert (GS::HasGenerateHashValue<Key>, "'Key' has no GenerateHashValue ().");
		static_assert (GS::HasOperatorEquals<Key>,    "'Key' has no operator== ().");
	}
};


template <class Key, class Value>
class GS_EXPORT_TYPEINFO HashTable : public HashTableBase<Key, Value> {
private:
	struct HashEntry {
		Key			key;	// stores the key
		Value		value;	// stores the value
		HashEntry*	next;	// pointer to the next entry (or nullptr)

		HashEntry (const Key& key, const Value& value, HashEntry* nextEntry):
			key   (key),
			value (value),
			next  (nextEntry) {}

		HashEntry (const Key& key, Value&& value, HashEntry* nextEntry):
			key   (key),
			value (std::move (value)),
			next  (nextEntry) {}

		void	Move (HashEntry& source)
		{
			key	  = std::move (source.key);
			value = std::move (source.value);
			next  = source.next;
		}
	};

	ArrayFB<HashEntry*, 1>	hashListTable;				// stores pointers to lists of hash entries
	PagedArray<HashEntry>	hashEntryTable;				// stores hash entries (lists of hash entries)
	float					averageSeekFactorLimit;		// specifies limit for the average seek factor above which the hash table should be rehashed (if the minimum fill factor is also reached)
	float					minFillFactor;				// specifies the minimum fill factor above which the rehashing should be considered (depending on the average seek factor)
	ULong					seekWeightSum;				// sum of seek weights (it is very unlikely to exceed MaxULong because in 4GB can fit at most 256 millions key-value pairs which can have average seek factor 16, but if it yet does exceed then hash table will be not rehashed any more)

	HashEntry*	AccessEntry (const Key& key) const;

	void		EnsureAverageSeekFactor	  ();
	void		DecreaseAverageSeekFactor ();
	void		IncreaseAverageSeekFactor ();
	USize		GetHashListTableSize (USize hashEntryCount) const;
	void		Rehash (USize newHashListTableSize);

	void		SwapPrimitiveMembers (HashTable& rightOp);

		// CurrentPair, ConstCurrentPair

	struct CurrentPair {
		const Key&		key;
		Value&			value;
	};

	struct ConstCurrentPair {
		const Key&		key;
		const Value&	value;
	};

		// IteratorState

	struct IteratorState {
		UIndex	current;	// current entry

		explicit IteratorState (UIndex initialIndex = 0): current (initialIndex) {}
	};
	void			Increment (IteratorState& state) const;
	bool			IsEqual (const IteratorState& state1, const IteratorState& state2) const;
	bool			IsEnd (const IteratorState& state) const;

		// KeyIteratorState

	struct KeyIteratorState: public IteratorState {
		explicit KeyIteratorState (UIndex initialIndex = 0): IteratorState (initialIndex) {}
	};
	Key&			GetCurrent (const KeyIteratorState& state);
	const Key&		GetCurrent (const KeyIteratorState& state) const;

		// ValueIteratorState

	struct ValueIteratorState: public IteratorState {
		explicit ValueIteratorState (UIndex initialIndex = 0): IteratorState (initialIndex) {}
	};
	Value&			GetCurrent (const ValueIteratorState& state);
	const Value&	GetCurrent (const ValueIteratorState& state) const;

		// PairIteratorState

	struct PairIteratorState: public IteratorState {
		mutable std::byte currentPair[sizeof (CurrentPair)];	// stores the current key-value pair

		explicit PairIteratorState (UIndex initialIndex = 0): IteratorState (initialIndex) {}
	};
	CurrentPair&			GetCurrent (const PairIteratorState& state);
	const CurrentPair&		GetCurrent (const PairIteratorState& state) const;

		// ConstPairIteratorState

	struct ConstPairIteratorState: public IteratorState {
		mutable std::byte currentPair[sizeof (ConstCurrentPair)];	// stores the current key-value pair

		explicit ConstPairIteratorState (UIndex initialIndex = 0):	IteratorState (initialIndex) {}
		ConstPairIteratorState (const PairIteratorState& source):	IteratorState (source) {}
		void operator= (const PairIteratorState& source)			{ IteratorState::operator= (source); }
	};
	ConstCurrentPair&		GetCurrent (const ConstPairIteratorState& state);
	const ConstCurrentPair&	GetCurrent (const ConstPairIteratorState& state) const;

		// Friend classes

	friend class ConstForwardContainerIterator<HashTable, KeyIteratorState, Key>;
	friend class ForwardContainerIterator<HashTable, ValueIteratorState, Value>;
	friend class ConstForwardContainerIterator<HashTable, ValueIteratorState, Value>;
	friend class ConstForwardContainerIterator<HashTable, PairIteratorState, CurrentPair>;
	friend class ConstForwardContainerIterator<HashTable, ConstPairIteratorState, ConstCurrentPair>;
	friend class ConstGeneralForwardContainerIterator<HashTable, KeyIteratorState, Key>;
	friend class GeneralForwardContainerIterator<HashTable, ValueIteratorState, Value>;
	friend class ConstGeneralForwardContainerIterator<HashTable, ValueIteratorState, Value>;
	friend class ConstGeneralForwardContainerIterator<HashTable, PairIteratorState, CurrentPair>;
	friend class ConstGeneralForwardContainerIterator<HashTable, ConstPairIteratorState, ConstCurrentPair>;

public:
		// Types

	typedef ConstForwardContainerIterator<HashTable, KeyIteratorState, Key> 							ConstKeyIterator;
	typedef ForwardContainerIterator<HashTable, ValueIteratorState, Value> 								ValueIterator;
	typedef ConstForwardContainerIterator<HashTable, ValueIteratorState, Value> 						ConstValueIterator;
	typedef ConstForwardContainerIterator<HashTable, PairIteratorState, CurrentPair>					Iterator;
	typedef ConstForwardContainerIterator<HashTable, ConstPairIteratorState, ConstCurrentPair>			ConstIterator;

	typedef ConstGeneralForwardContainerIterator<HashTable, KeyIteratorState, Key> 						ConstGeneralKeyIterator;
	typedef GeneralForwardContainerIterator<HashTable, ValueIteratorState, Value> 						GeneralValueIterator;
	typedef ConstGeneralForwardContainerIterator<HashTable, ValueIteratorState, Value> 					ConstGeneralValueIterator;
	typedef ConstGeneralForwardContainerIterator<HashTable, PairIteratorState, CurrentPair> 			GeneralIterator;
	typedef ConstGeneralForwardContainerIterator<HashTable, ConstPairIteratorState, ConstCurrentPair>	ConstGeneralIterator;

	typedef Iterator														 							PairIterator;
	typedef ConstIterator																				ConstPairIterator;

	class KeyConversionEnumerator;
	class ValueConversionEnumerator;

private:
		// Ranges

	class KeyRange {
	public:
		ConstKeyIterator	begin () const		{ return reinterpret_cast<const HashTable*> (this)->BeginKeys (); }
		ConstKeyIterator	end   () const		{ return reinterpret_cast<const HashTable*> (this)->EndKeys (); }
	};

	class ValueRange {
	public:
		ValueIterator		begin ()			{ return reinterpret_cast<HashTable*> (this)->BeginValues (); }
		ValueIterator		end   ()			{ return reinterpret_cast<HashTable*> (this)->EndValues (); }
		ConstValueIterator	begin () const		{ return reinterpret_cast<const HashTable*> (this)->BeginValues (); }
		ConstValueIterator	end   () const		{ return reinterpret_cast<const HashTable*> (this)->EndValues (); }
	};

public:
		// Constructors

	HashTable ();
	explicit HashTable (float averageSeekFactorLimit, float minFillFactor = 0.0);
	HashTable (std::initializer_list<Pair<Key, Value>> source);
	HashTable (const HashTable& source);
	HashTable (HashTable&& source);
	HashTable (const HashTable&&) = delete;
   ~HashTable ();
	HashTable&	operator= (const HashTable& source);
	HashTable&	operator= (HashTable&& source);

	void			Move (HashTable& source);
	void			Move (FunctionRef<void (Value&&)> processor);

		// Key access

	GS_FORCE_INLINE const Key&		GetKey (const Key& key) const gs_lifebound;
	GS_FORCE_INLINE bool			GetKey (const Key& key, Key* keyInContainer) const;
	GS_FORCE_INLINE bool			GetKey (const Key& key, const Key** keyInContainer) const;

	GS_FORCE_INLINE const Key*		GetKeyPtr (const Key& key) const gs_lifebound;

	void							SetEquivalentKey (const Key& oldKey, const Key& newKey);

		// Item access

	GS_FORCE_INLINE Value&			operator[] (const Key& key) gs_lifebound;
	GS_FORCE_INLINE const Value&	operator[] (const Key& key) const gs_lifebound;

	GS_FORCE_INLINE Value&			Get (const Key& key) gs_lifebound;
	GS_FORCE_INLINE const Value&	Get (const Key& key) const gs_lifebound;
	GS_FORCE_INLINE Value			Get (const Key& key, const Value& defaultValue) const;
	GS_FORCE_INLINE bool			Get (const Key& key, Value* value) const;
	GS_FORCE_INLINE bool			Get (const Key& key, Value** value);
	GS_FORCE_INLINE bool			Get (const Key& key, const Value** value) const;

	GS_FORCE_INLINE Value*			GetPtr (const Key& key) gs_lifebound;
	GS_FORCE_INLINE const Value*	GetPtr (const Key& key) const gs_lifebound;

	Value&							Retrieve (const Key& key) gs_lifebound;
	Value&							Retrieve (const Key& key, const Value& defaultValue) gs_lifebound;

	void							Set (const Key& key, const Value& value);

		// Content management

	bool			Add	   (const Key& key, const Value& value);
	bool			Add	   (const Key& key, Value&& value);

	bool			Add    (const Pair<Key, Value>& pair);
	bool			Add    (Pair<Key, Value>&& pair);

	bool			Add	   (const Key& key, const Value& value, Value** valueInContainer);
	bool			Add	   (const Key& key, Value&& value, Value** valueInContainer);

	void			Put	   (const Key& key, const Value& value);
	void			Put	   (const Key& key, Value&& value);

	bool			Delete    (const Key& key);
	void			DeleteAll (FunctionRef<bool (const Key&, const Value&)> condition);

	void			Clear  ();

	void			Swap   (HashTable& rightOp);

	USize			GetSize () const;
	bool			IsEmpty () const;

		// Iteration

	ConstKeyIterator			EnumerateKeys () const;
	ConstKeyIterator			BeginKeys () const;
	ConstKeyIterator			EndKeys () const;

	ValueIterator				EnumerateValues ();
	ConstValueIterator			EnumerateValues () const;
	ValueIterator				BeginValues ();
	ConstValueIterator			BeginValues () const;
	ValueIterator				EndValues ();
	ConstValueIterator			EndValues () const;

	Iterator					Enumerate ();
	ConstIterator				Enumerate () const;
	Iterator					Begin ();
	ConstIterator				Begin () const;
	Iterator					End ();
	ConstIterator				End () const;

		// General iteration

	ConstGeneralKeyIterator		EnumerateKeysGeneral () const;
	ConstGeneralKeyIterator		BeginKeysGeneral () const;
	ConstGeneralKeyIterator		EndKeysGeneral () const;

	GeneralValueIterator		EnumerateValuesGeneral ();
	ConstGeneralValueIterator	EnumerateValuesGeneral () const;
	GeneralValueIterator		BeginValuesGeneral ();
	ConstGeneralValueIterator	BeginValuesGeneral () const;
	GeneralValueIterator		EndValuesGeneral ();
	ConstGeneralValueIterator	EndValuesGeneral () const;

	GeneralIterator				EnumerateGeneral ();
	ConstGeneralIterator		EnumerateGeneral () const;
	GeneralIterator				BeginGeneral ();
	ConstGeneralIterator		BeginGeneral () const;
	GeneralIterator				EndGeneral ();
	ConstGeneralIterator		EndGeneral () const;

		// Deprecated iteration

	PairIterator				EnumeratePairs ();
	ConstPairIterator			EnumeratePairs () const;
	PairIterator				BeginPairs ();
	ConstPairIterator			BeginPairs () const;
	PairIterator				EndPairs ();
	ConstPairIterator			EndPairs () const;

		// Enumeration

	template <class Function>
	void							EnumerateKeys (Function&& processor) const;

	template <class Function>
	void							EnumerateValues		 (Function&& processor);
	template <class Function>
	void							EnumerateValues		 (Function&& processor) const;
	template <class Function>
	void							EnumerateValuesConst (Function&& processor) const;

	template <class Function>
	void							Enumerate		(Function&& processor);
	template <class Function>
	void							Enumerate		(Function&& processor) const;
	template <class Function>
	void							EnumerateConst	(Function&& processor) const;

		// Range-based for loop support

	const KeyRange&				Keys () const gs_lifebound;
	ValueRange&					Values () gs_lifebound;
	const ValueRange&			Values () const gs_lifebound;
	auto&						ConstValues () const gs_lifebound;

	auto&						AsConst () const gs_lifebound;

		// Conversion

	KeyConversionEnumerator		ConvertKeys  () const;
	ValueConversionEnumerator	ConvertValues () const;

		// Content query

	bool			ContainsKey   (const Key& key) const;

	bool			ContainsValue (const Value& value) const;
	bool			ContainsValue (FunctionRef<bool (const Value&)> condition) const;

	bool			IfContainsHasValue (const Key& key, const Value& value) const;

	Optional<Key>	FindValue (const Value& value) const;
	Optional<Key>	FindValue (FunctionRef<bool (const Value&)> condition) const;

	USize			Count (const Value& value) const;
	USize			Count (FunctionRef<bool (const Value&)> condition) const;

	template <class K = Key, class V = Value, class = EnableIf<HasOperatorEquals<K> && HasOperatorEquals<V>>>
	bool			operator== (const HashTable& rightOp) const;

	template <class K = Key, class V = Value, class = EnableIf<HasOperatorEquals<K>&& HasOperatorEquals<V>>>
	bool			operator!= (const HashTable& rightOp) const;

		// Performance tuning

	void			EnsureCapacity		 (USize minCapacity);

	double			GetAverageSeekFactor () const;
	ULong			FindMaxSeekFactor	 () const;
	double			GetFillFactor		 () const;
	ULong			CountEmptyLists		 () const;

		// I/O

	GSErrCode		Read  (IChannel& ic);
	GSErrCode		Read  (IChannel& ic, FunctionRef<GSErrCode (IChannel&, Key&, Value&)> reader);

	GSErrCode		Write (OChannel& oc) const;
	GSErrCode		Write (OChannel& oc, FunctionRef<GSErrCode (OChannel&, const Key&, const Value&)> writer) const;

		// Debug

	bool			CheckState () const;

	const Key&		GetAKey (ULong rnd) const gs_lifebound;

		// Types

	class KeyConversionEnumerator: public GS::ConversionEnumerator<Key> {
	private:
		const HashTable* source;

	public:
		KeyConversionEnumerator (const HashTable& source);

		virtual void	Enumerate (const std::function<void (const Key&)>& processor) const override;

		virtual USize	GetSizeHint (void) const override;
	};

	class ValueConversionEnumerator: public GS::ConversionEnumerator<Value> {
	private:
		const HashTable* source;

	public:
		ValueConversionEnumerator (const HashTable& source);

		virtual void	Enumerate (const std::function<void (const Value&)>& processor) const override;

		virtual USize	GetSizeHint (void) const override;
	};

		// Friend declarations

	friend GSErrCode 	Store (ObjectState& os, const typename HashTable<Key, Value>::ConstCurrentPair& pair)
	{
		return StorePair (os, pair.key, pair.value);
	}

	friend GSErrCode 	Restore (const ObjectState& os, typename HashTable<Key, Value>::ConstCurrentPair& pair);    // Not used - needed for ObjectStateTraits
};


// === HashTable methods ===============================================================================================

template <class Key, class Value>
HashTable<Key, Value>::HashTable ():
	HashTable (0.0, 0.0)
{
}


template <class Key, class Value>
HashTable<Key, Value>::HashTable (float averageSeekFactorLimit, float minFillFactor /*= 0.0*/)
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


template <class Key, class Value>
HashTable<Key, Value>::HashTable (const HashTable& source)
{
	NULL_REF_CHECK (source);

	averageSeekFactorLimit = source.averageSeekFactorLimit;
	minFillFactor		   = source.minFillFactor;
	seekWeightSum		   = 0;

	USize sourceHashEntryCount = source.hashEntryTable.GetSize ();
	for (UIndex i = 0; i < sourceHashEntryCount; i++) {
		const HashEntry& hashEntry = source.hashEntryTable[i];
		hashEntryTable.PushNew (hashEntry.key, hashEntry.value, nullptr);
	}

	Rehash (GetHashListTableSize (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
HashTable<Key, Value>::HashTable (std::initializer_list<Pair<Key, Value>> source):
	HashTable ()
{
	EnsureCapacity (USize (source.size ()));

	for (const auto& pair : source)
		Add (pair.first, pair.second);
}


template <class Key, class Value>
HashTable<Key, Value>::HashTable (HashTable&& source):
	averageSeekFactorLimit (2.0),
	minFillFactor (0.75),
	seekWeightSum (0)
{
	Move (source);
}


template <class Key, class Value>
HashTable<Key, Value>::~HashTable () = default;


template <class Key, class Value>
HashTable<Key, Value>&		HashTable<Key, Value>::operator= (const HashTable& source)
{
	NULL_REF_CHECK (source);

	HashTable copy = source;
	hashListTable.Move (copy.hashListTable);
	hashEntryTable.Move (copy.hashEntryTable);
	SwapPrimitiveMembers (copy);

	return *this;
}


template <class Key, class Value>
HashTable<Key, Value>&		HashTable<Key, Value>::operator= (HashTable&& source)
{
	NULL_REF_CHECK (source);

	Move (source);

	return *this;
}


template <class Key, class Value>
void	HashTable<Key, Value>::Move (HashTable& source)
{
	if (DBERROR (&source == this))
		return;

	hashListTable.Move (source.hashListTable);
	hashEntryTable.Move (source.hashEntryTable);
	SwapPrimitiveMembers (source);

	source.Clear ();
}


template <class Key, class Value>
void	HashTable<Key, Value>::Move (const FunctionRef<void (Value&&)> processor)
{
	for (UIndex i = 0; i < hashEntryTable.GetSize (); ++i)
		processor (std::move (hashEntryTable[i].value));

	Clear ();
}


template <class Key, class Value>
GS_FORCE_INLINE const Key&	HashTable<Key, Value>::GetKey (const Key& key) const
{
	NULL_REF_CHECK (key);

	const HashEntry* hashEntry = AccessEntry (key);
	REF_CHECK_R (hashEntry != nullptr);

	return hashEntry->key;
}


template <class Key, class Value>
GS_FORCE_INLINE bool	HashTable<Key, Value>::GetKey (const Key& key, Key* keyInContainer) const
{
	NULL_REF_CHECK (key);
	NULL_PTR_CHECK (keyInContainer);

	const HashEntry* hashEntry = AccessEntry (key);
	if (hashEntry == nullptr)
		return false;

	*keyInContainer = hashEntry->key;
	return true;
}


template <class Key, class Value>
GS_FORCE_INLINE bool	HashTable<Key, Value>::GetKey (const Key& key, const Key** keyInContainer) const
{
	NULL_REF_CHECK (key);
	NULL_PTR_CHECK (keyInContainer);

	const HashEntry* hashEntry = AccessEntry (key);
	if (hashEntry == nullptr)
		return false;

	*keyInContainer = &hashEntry->key;
	return true;
}


template <class Key, class Value>
GS_FORCE_INLINE const Key*	HashTable<Key, Value>::GetKeyPtr (const Key& key) const
{
	NULL_REF_CHECK (key);

	const HashEntry* hashEntry = AccessEntry (key);
	if (hashEntry != nullptr)
		return &hashEntry->key;
	else
		return nullptr;
}


template <class Key, class Value>
void	HashTable<Key, Value>::SetEquivalentKey (const Key& oldKey, const Key& newKey)
{
	NULL_REF_CHECK (oldKey);
	NULL_REF_CHECK (newKey);

	DBASSERT (oldKey == newKey);

	HashEntry* hashEntry = AccessEntry (oldKey);
	REF_CHECK (hashEntry != nullptr);

	hashEntry->key = newKey;
}


template <class Key, class Value>
GS_FORCE_INLINE Value&	HashTable<Key, Value>::operator[] (const Key& key)
{
	NULL_REF_CHECK (key);

	HashEntry* hashEntry = AccessEntry (key);
	REF_CHECK (hashEntry != nullptr);

	return hashEntry->value;
}


template <class Key, class Value>
GS_FORCE_INLINE const Value&	HashTable<Key, Value>::operator[] (const Key& key) const
{
	NULL_REF_CHECK (key);

	const HashEntry* hashEntry = AccessEntry (key);
	REF_CHECK (hashEntry != nullptr);

	return hashEntry->value;
}


template <class Key, class Value>
GS_FORCE_INLINE Value&	HashTable<Key, Value>::Get (const Key& key)
{
	NULL_REF_CHECK (key);

	HashEntry* hashEntry = AccessEntry (key);
	REF_CHECK_R (hashEntry != nullptr);

	return hashEntry->value;
}


template <class Key, class Value>
GS_FORCE_INLINE const Value&	HashTable<Key, Value>::Get (const Key& key) const
{
	NULL_REF_CHECK (key);

	const HashEntry* hashEntry = AccessEntry (key);
	REF_CHECK_R (hashEntry != nullptr);

	return hashEntry->value;
}


template <class Key, class Value>
GS_FORCE_INLINE Value	HashTable<Key, Value>::Get (const Key& key, const Value& defaultValue) const
{
	NULL_REF_CHECK (key);

	const HashEntry* hashEntry = AccessEntry (key);

	if (hashEntry != nullptr)
		return hashEntry->value;
	else
		return defaultValue;
}


template <class Key, class Value>
GS_FORCE_INLINE bool	HashTable<Key, Value>::Get (const Key& key, Value* value) const
{
	NULL_REF_CHECK (key);
	NULL_PTR_CHECK (value);

	const HashEntry* hashEntry = AccessEntry (key);
	if (hashEntry == nullptr)
		return false;

	*value = hashEntry->value;
	return true;
}


template <class Key, class Value>
GS_FORCE_INLINE bool	HashTable<Key, Value>::Get (const Key& key, Value** value)
{
	NULL_REF_CHECK (key);
	NULL_PTR_CHECK (value);

	HashEntry* hashEntry = AccessEntry (key);
	if (hashEntry == nullptr)
		return false;

	*value = &hashEntry->value;
	return true;
}


template <class Key, class Value>
GS_FORCE_INLINE bool	HashTable<Key, Value>::Get (const Key& key, const Value** value) const
{
	NULL_REF_CHECK (key);
	NULL_PTR_CHECK (value);

	const HashEntry* hashEntry = AccessEntry (key);
	if (hashEntry == nullptr)
		return false;

	*value = &hashEntry->value;
	return true;
}


template <class Key, class Value>
GS_FORCE_INLINE Value*	HashTable<Key, Value>::GetPtr (const Key& key)
{
	NULL_REF_CHECK (key);

	HashEntry* hashEntry = AccessEntry (key);
	if (hashEntry != nullptr)
		return &hashEntry->value;
	else
		return nullptr;
}


template <class Key, class Value>
GS_FORCE_INLINE const Value*	HashTable<Key, Value>::GetPtr (const Key& key) const
{
	NULL_REF_CHECK (key);

	const HashEntry* hashEntry = AccessEntry (key);
	if (hashEntry != nullptr)
		return &hashEntry->value;
	else
		return nullptr;
}


template <class Key, class Value>
Value&	HashTable<Key, Value>::Retrieve (const Key& key)
{
	NULL_REF_CHECK (key);

	Value* valueInContainer;
	Add (key, Value (), &valueInContainer);

	REF_CHECK (valueInContainer != nullptr);

	return *valueInContainer;
}


template <class Key, class Value>
Value&	HashTable<Key, Value>::Retrieve (const Key& key, const Value& defaultValue)
{
	NULL_REF_CHECK (key);
	NULL_REF_CHECK (defaultValue);

	Value* valueInContainer;
	Add (key, defaultValue, &valueInContainer);

	REF_CHECK (valueInContainer != nullptr);

	return *valueInContainer;
}


template <class Key, class Value>
void	HashTable<Key, Value>::Set (const Key& key, const Value& value)
{
	NULL_REF_CHECK (key);
	NULL_REF_CHECK (value);

	HashEntry* hashEntry = AccessEntry (key);
	REF_CHECK (hashEntry != nullptr);

	hashEntry->value = value;
}


template <class Key, class Value>
bool	HashTable<Key, Value>::Add (const Key& key, const Value& value, Value** valueInContainer)
{
	NULL_REF_CHECK (key);
	NULL_REF_CHECK (value);

	if (hashListTable.IsEmpty ()) {
		USize firstHashListTableSize = GetNextHashCapacity (0);
		hashListTable.SetCapacity (firstHashListTableSize);	// in this way SetSize will not waste capacity
		hashListTable.SetSize (firstHashListTableSize);
		hashListTable.Fill (nullptr);
	}

	UIndex hashListIndex = GS::CalculateHashValue (key) % hashListTable.GetSize ();
	HashEntry* hashEntry = hashListTable[hashListIndex];
	UIndex hashListLength = 0;
	while (hashEntry != nullptr) {
		if (hashEntry->key == key) {
			if (valueInContainer != nullptr)
				*valueInContainer = &hashEntry->value;
			return false;
		}
		hashListLength++;
		hashEntry = hashEntry->next;
	}
	seekWeightSum += hashListLength + 1;

	hashEntryTable.PushNew (key, value, hashListTable[hashListIndex]);
	hashEntry = &hashEntryTable.GetLast ();
	hashListTable[hashListIndex] = hashEntry;

	EnsureAverageSeekFactor ();

	if (valueInContainer != nullptr)
		*valueInContainer = &hashEntry->value;

	return true;
}


template <class Key, class Value>
bool	HashTable<Key, Value>::Add (const Key& key, Value&& value, Value** valueInContainer)
{
	NULL_REF_CHECK (key);
	NULL_REF_CHECK (value);

	if (hashListTable.IsEmpty ()) {
		USize firstHashListTableSize = GetNextHashCapacity (0);
		hashListTable.SetCapacity (firstHashListTableSize);	// in this way SetSize will not waste capacity
		hashListTable.SetSize (firstHashListTableSize);
		hashListTable.Fill (nullptr);
	}

	UIndex hashListIndex = GS::CalculateHashValue (key) % hashListTable.GetSize ();
	HashEntry* hashEntry = hashListTable[hashListIndex];
	UIndex hashListLength = 0;
	while (hashEntry != nullptr) {
		if (hashEntry->key == key) {
			if (valueInContainer != nullptr)
				*valueInContainer = &hashEntry->value;
			return false;
		}
		hashListLength++;
		hashEntry = hashEntry->next;
	}
	seekWeightSum += hashListLength + 1;

	hashEntryTable.PushNew (key, std::move (value), hashListTable[hashListIndex]);
	hashEntry = &hashEntryTable.GetLast ();
	hashListTable[hashListIndex] = hashEntry;

	EnsureAverageSeekFactor ();

	if (valueInContainer != nullptr)
		*valueInContainer = &hashEntry->value;

	return true;
}


template <class Key, class Value>
bool	HashTable<Key, Value>::Add (const Key& key, const Value& value)
{
	return Add (key, value, nullptr);
}


template <class Key, class Value>
bool	HashTable<Key, Value>::Add (const Key& key, Value&& value)
{
	return Add (key, std::move (value), nullptr);
}


template <class Key, class Value>
bool GS::HashTable<Key, Value>::Add (const Pair<Key, Value>& pair)
{
	return Add (pair.first, pair.second);
}


template <class Key, class Value>
bool GS::HashTable<Key, Value>::Add (Pair<Key, Value>&& pair)
{
	return Add (pair.first, std::move (pair.second));
}


template <class Key, class Value>
void	HashTable<Key, Value>::Put (const Key& key, const Value& value)
{
	NULL_REF_CHECK (key);
	NULL_REF_CHECK (value);

	Value* valueInContainer = nullptr;
	if (!Add (key, value, &valueInContainer))
		*valueInContainer = value;
}


template <class Key, class Value>
void	HashTable<Key, Value>::Put (const Key& key, Value&& value)
{
	NULL_REF_CHECK (key);
	NULL_REF_CHECK (value);

	Value* valueInContainer = nullptr;
	if (!Add (key, std::move (value), &valueInContainer))
		*valueInContainer = std::move (value);
}


template <class Key, class Value>
bool	HashTable<Key, Value>::Delete (const Key& key)
{
	NULL_REF_CHECK (key);

		// deleting the entry

	if (hashEntryTable.IsEmpty ())
		return false;

	UIndex hashListIndex = GS::CalculateHashValue (key) % hashListTable.GetSize ();
	HashEntry* hashEntry = hashListTable[hashListIndex];
	HashEntry* prevHashEntry = nullptr;
	while (hashEntry != nullptr) {
		if (hashEntry->key == key)
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

		UIndex lpeListIndex = GS::CalculateHashValue (hashEntry->key) % hashListTable.GetSize ();
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


template <class Key, class Value>
void	HashTable<Key, Value>::DeleteAll (const FunctionRef<bool (const Key&, const Value&)> condition)
{
	ArrayFB<Key, 8> keysToDelete;

	for (const auto& [key, value] : *this) {
		if (condition (key, value))
			keysToDelete.Push (key);
	}

	for (const Key& key : keysToDelete)
		Delete (key);
}


template <class Key, class Value>
void	HashTable<Key, Value>::Clear ()
{
	hashListTable.Clear ();
	hashEntryTable.Clear ();

	seekWeightSum = 0;
}


template <class Key, class Value>
void	HashTable<Key, Value>::Swap (HashTable& rightOp)
{
	NULL_REF_CHECK (rightOp);

	if (this == &rightOp)
		return;

	hashListTable.Swap (rightOp.hashListTable);
	hashEntryTable.Swap (rightOp.hashEntryTable);
	SwapPrimitiveMembers (rightOp);
}


template <class Key, class Value>
void	HashTable<Key, Value>::SwapPrimitiveMembers (HashTable& rightOp)
{
	NULL_REF_CHECK (rightOp);

	GS::Swap (averageSeekFactorLimit, rightOp.averageSeekFactorLimit);
	GS::Swap (minFillFactor,		  rightOp.minFillFactor);
	GS::Swap (seekWeightSum,		  rightOp.seekWeightSum);
}


template <class Key, class Value>
USize	HashTable<Key, Value>::GetSize () const
{
	return hashEntryTable.GetSize ();
}


template <class Key, class Value>
bool	HashTable<Key, Value>::IsEmpty () const
{
	return (hashEntryTable.IsEmpty ());
}


template <class Key, class Value>
typename HashTable<Key, Value>::ConstKeyIterator	HashTable<Key, Value>::EnumerateKeys () const
{
	return ConstKeyIterator (*this, KeyIteratorState (0));
}


template <class Key, class Value>
typename HashTable<Key, Value>::ConstKeyIterator	HashTable<Key, Value>::BeginKeys () const
{
	return ConstKeyIterator (*this, KeyIteratorState (0));
}


template <class Key, class Value>
typename HashTable<Key, Value>::ConstKeyIterator	HashTable<Key, Value>::EndKeys () const
{
	return ConstKeyIterator (*this, KeyIteratorState (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
typename HashTable<Key, Value>::ValueIterator		HashTable<Key, Value>::EnumerateValues ()
{
	return ValueIterator (*this, ValueIteratorState (0));
}


template <class Key, class Value>
typename HashTable<Key, Value>::ConstValueIterator	HashTable<Key, Value>::EnumerateValues () const
{
	return ConstValueIterator (*this, ValueIteratorState (0));
}


template <class Key, class Value>
typename HashTable<Key, Value>::ValueIterator		HashTable<Key, Value>::BeginValues ()
{
	return ValueIterator (*this, ValueIteratorState (0));
}


template <class Key, class Value>
typename HashTable<Key, Value>::ConstValueIterator	HashTable<Key, Value>::BeginValues () const
{
	return ConstValueIterator (*this, ValueIteratorState (0));
}


template <class Key, class Value>
typename HashTable<Key, Value>::ValueIterator		HashTable<Key, Value>::EndValues ()
{
	return ValueIterator (*this, ValueIteratorState (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
typename HashTable<Key, Value>::ConstValueIterator	HashTable<Key, Value>::EndValues () const
{
	return ConstValueIterator (*this, ValueIteratorState (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
typename HashTable<Key, Value>::Iterator			HashTable<Key, Value>::Enumerate ()
{
	return Iterator (*this, PairIteratorState (0));
}


template <class Key, class Value>
typename HashTable<Key, Value>::ConstIterator		HashTable<Key, Value>::Enumerate () const
{
	return ConstIterator (*this, ConstPairIteratorState (0));
}


template <class Key, class Value>
typename HashTable<Key, Value>::Iterator			HashTable<Key, Value>::Begin ()
{
	return Iterator (*this, PairIteratorState (0));
}


template <class Key, class Value>
typename HashTable<Key, Value>::ConstIterator		HashTable<Key, Value>::Begin () const
{
	return ConstIterator (*this, ConstPairIteratorState (0));
}


template <class Key, class Value>
typename HashTable<Key, Value>::Iterator			HashTable<Key, Value>::End ()
{
	return Iterator (*this, PairIteratorState (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
typename HashTable<Key, Value>::ConstIterator		HashTable<Key, Value>::End () const
{
	return ConstIterator (*this, ConstPairIteratorState (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
typename HashTable<Key, Value>::ConstGeneralKeyIterator		HashTable<Key, Value>::EnumerateKeysGeneral () const
{
	return ConstGeneralKeyIterator (*this, KeyIteratorState (0));
}


template <class Key, class Value>
typename HashTable<Key, Value>::ConstGeneralKeyIterator		HashTable<Key, Value>::BeginKeysGeneral () const
{
	return ConstGeneralKeyIterator (*this, KeyIteratorState (0));
}


template <class Key, class Value>
typename HashTable<Key, Value>::ConstGeneralKeyIterator		HashTable<Key, Value>::EndKeysGeneral () const
{
	return ConstGeneralKeyIterator (*this, KeyIteratorState (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
typename HashTable<Key, Value>::GeneralValueIterator		HashTable<Key, Value>::EnumerateValuesGeneral ()
{
	return GeneralValueIterator (*this, ValueIteratorState (0));
}


template <class Key, class Value>
typename HashTable<Key, Value>::ConstGeneralValueIterator	HashTable<Key, Value>::EnumerateValuesGeneral () const
{
	return ConstGeneralValueIterator (*this, ValueIteratorState (0));
}


template <class Key, class Value>
typename HashTable<Key, Value>::GeneralValueIterator		HashTable<Key, Value>::BeginValuesGeneral ()
{
	return GeneralValueIterator (*this, ValueIteratorState (0));
}


template <class Key, class Value>
typename HashTable<Key, Value>::ConstGeneralValueIterator	HashTable<Key, Value>::BeginValuesGeneral () const
{
	return ConstGeneralValueIterator (*this, ValueIteratorState (0));
}


template <class Key, class Value>
typename HashTable<Key, Value>::GeneralValueIterator		HashTable<Key, Value>::EndValuesGeneral ()
{
	return GeneralValueIterator (*this, ValueIteratorState (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
typename HashTable<Key, Value>::ConstGeneralValueIterator	HashTable<Key, Value>::EndValuesGeneral () const
{
	return ConstGeneralValueIterator (*this, ValueIteratorState (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
typename HashTable<Key, Value>::GeneralIterator				HashTable<Key, Value>::EnumerateGeneral ()
{
	return GeneralIterator (*this, PairIteratorState (0));
}


template <class Key, class Value>
typename HashTable<Key, Value>::ConstGeneralIterator		HashTable<Key, Value>::EnumerateGeneral () const
{
	return ConstGeneralIterator (*this, ConstPairIteratorState (0));
}


template <class Key, class Value>
typename HashTable<Key, Value>::GeneralIterator				HashTable<Key, Value>::BeginGeneral ()
{
	return GeneralIterator (*this, PairIteratorState (0));
}


template <class Key, class Value>
typename HashTable<Key, Value>::ConstGeneralIterator		HashTable<Key, Value>::BeginGeneral () const
{
	return ConstGeneralIterator (*this, ConstPairIteratorState (0));
}


template <class Key, class Value>
typename HashTable<Key, Value>::GeneralIterator				HashTable<Key, Value>::EndGeneral ()
{
	return GeneralIterator (*this, PairIteratorState (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
typename HashTable<Key, Value>::ConstGeneralIterator		HashTable<Key, Value>::EndGeneral () const
{
	return ConstGeneralIterator (*this, ConstPairIteratorState (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
typename HashTable<Key, Value>::PairIterator				HashTable<Key, Value>::EnumeratePairs ()
{
	return PairIterator (*this, PairIteratorState (0));
}


template <class Key, class Value>
typename HashTable<Key, Value>::ConstPairIterator			HashTable<Key, Value>::EnumeratePairs () const
{
	return ConstPairIterator (*this, ConstPairIteratorState (0));
}


template <class Key, class Value>
typename HashTable<Key, Value>::PairIterator				HashTable<Key, Value>::BeginPairs ()
{
	return PairIterator (*this, PairIteratorState (0));
}


template <class Key, class Value>
typename HashTable<Key, Value>::ConstPairIterator			HashTable<Key, Value>::BeginPairs () const
{
	return ConstPairIterator (*this, ConstPairIteratorState (0));
}


template <class Key, class Value>
typename HashTable<Key, Value>::PairIterator				HashTable<Key, Value>::EndPairs ()
{
	return PairIterator (*this, PairIteratorState (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
typename HashTable<Key, Value>::ConstPairIterator			HashTable<Key, Value>::EndPairs () const
{
	return ConstPairIterator (*this, ConstPairIteratorState (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
template <class Function>
void		HashTable<Key, Value>::EnumerateKeys (Function&& processor) const
{
	for (UIndex i = 0; i < hashEntryTable.GetSize (); i++)
		processor (const_cast<const Key&> (hashEntryTable[i].key));
}


template <class Key, class Value>
template <class Function>
void		HashTable<Key, Value>::EnumerateValues (Function&& processor)
{
	for (UIndex i = 0; i < hashEntryTable.GetSize (); i++)
		processor (hashEntryTable[i].value);
}


template <class Key, class Value>
template <class Function>
void		HashTable<Key, Value>::EnumerateValues (Function&& processor) const
{
	for (UIndex i = 0; i < hashEntryTable.GetSize (); i++)
		processor (const_cast<const Value&> (hashEntryTable[i].value));
}


template <class Key, class Value>
template <class Function>
void		HashTable<Key, Value>::EnumerateValuesConst (Function&& processor) const
{
	EnumerateValues (processor);
}


template <class Key, class Value>
template <class Function>
void		HashTable<Key, Value>::Enumerate (Function&& processor)
{
	for (UIndex i = 0; i < hashEntryTable.GetSize (); i++)
		processor (const_cast<const Key&> (hashEntryTable[i].key), hashEntryTable[i].value);
}


template <class Key, class Value>
template <class Function>
void		HashTable<Key, Value>::Enumerate (Function&& processor) const
{
	for (UIndex i = 0; i < hashEntryTable.GetSize (); i++)
		processor (const_cast<const Key&> (hashEntryTable[i].key), const_cast<const Value&> (hashEntryTable[i].value));
}


template <class Key, class Value>
template <class Function>
void		HashTable<Key, Value>::EnumerateConst (Function&& processor) const
{
	Enumerate (processor);
}


template <class Key, class Value>
const typename HashTable<Key, Value>::KeyRange&		HashTable<Key, Value>::Keys () const
{
	return reinterpret_cast<const KeyRange&> (*this);
}


template <class Key, class Value>
typename HashTable<Key, Value>::ValueRange&		HashTable<Key, Value>::Values ()
{
	return reinterpret_cast<ValueRange&> (*this);
}


template <class Key, class Value>
const typename HashTable<Key, Value>::ValueRange&	HashTable<Key, Value>::Values () const
{
	return reinterpret_cast<const ValueRange&> (*this);
}


template <class Key, class Value>
auto&	HashTable<Key, Value>::ConstValues () const
{
	return AsConst ().Values ();
}


template <class Key, class Value>
auto&	HashTable<Key, Value>::AsConst () const
{
	using ConstValueType = typename HashTable<Key, Value>::template MakeConstPtr<Value>::ConstType;

	return reinterpret_cast<const HashTable<Key, ConstValueType>&> (*this);
}


template <class Key, class Value>
typename HashTable<Key, Value>::KeyConversionEnumerator		HashTable<Key, Value>::ConvertKeys () const
{
	return KeyConversionEnumerator (*this);
}


template <class Key, class Value>
typename HashTable<Key, Value>::ValueConversionEnumerator	HashTable<Key, Value>::ConvertValues () const
{
	return ValueConversionEnumerator (*this);
}


template <class Key, class Value>
bool	HashTable<Key, Value>::ContainsKey (const Key& key) const
{
	NULL_REF_CHECK (key);

	return AccessEntry (key) != nullptr;
}


template <class Key, class Value>
bool	HashTable<Key, Value>::ContainsValue (const Value& value) const
{
	NULL_REF_CHECK (value);

	USize hashEntryCount = hashEntryTable.GetSize ();
	for (UIndex i = 0; i < hashEntryCount; i++) {
		if (hashEntryTable[i].value == value)
			return true;
	}

	return false;
}


template <class Key, class Value>
bool	HashTable<Key, Value>::ContainsValue (const FunctionRef<bool (const Value&)> condition) const
{
	USize hashEntryCount = hashEntryTable.GetSize ();
	for (UIndex i = 0; i < hashEntryCount; i++) {
		if (condition (hashEntryTable[i].value))
			return true;
	}

	return false;
}


template <class Key, class Value>
bool	HashTable<Key, Value>::IfContainsHasValue (const Key& key, const Value& value) const
{
	NULL_REF_CHECK (key);
	NULL_REF_CHECK (value);

	const Value* valueInContainer;
	return !Get (key, &valueInContainer) || *valueInContainer == value;
}


template <class Key, class Value>
Optional<Key>	HashTable<Key, Value>::FindValue (const Value& value) const
{
	NULL_REF_CHECK (value);

	USize hashEntryCount = hashEntryTable.GetSize ();
	for (UIndex i = 0; i < hashEntryCount; i++) {
		if (hashEntryTable[i].value == value)
			return hashEntryTable[i].key;
	}

	return NoValue;

}


template <class Key, class Value>
Optional<Key>	HashTable<Key, Value>::FindValue (const FunctionRef<bool (const Value&)> condition) const
{
	USize hashEntryCount = hashEntryTable.GetSize ();
	for (UIndex i = 0; i < hashEntryCount; i++) {
		if (condition (hashEntryTable[i].value))
			return hashEntryTable[i].key;
	}

	return NoValue;
}


template <class Key, class Value>
USize	HashTable<Key, Value>::Count (const Value& value) const
{
	NULL_REF_CHECK (value);

	USize count = 0;

	USize hashEntryCount = hashEntryTable.GetSize ();
	for (UIndex i = 0; i < hashEntryCount; i++) {
		if (hashEntryTable[i].value == value)
			count++;
	}

	return count;
}


template <class Key, class Value>
USize	HashTable<Key, Value>::Count (const FunctionRef<bool (const Value&)> condition) const
{
	USize count = 0;

	for (UIndex i = 0; i < hashEntryTable.GetSize (); i++) {
		if (condition (hashEntryTable[i].value))
			count++;
	}

	return count;
}


template <class Key, class Value>
template <class K, class V, class /*= EnableIf<HasOperatorEquals<K>&& HasOperatorEquals<V>>*/>
bool	HashTable<Key, Value>::operator== (const HashTable& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	USize hashEntryCount = hashEntryTable.GetSize ();

	if (hashEntryCount != rightOp.hashEntryTable.GetSize ())
		return false;

	for (UIndex i = 0; i < hashEntryCount; i++) {
		const HashEntry& hashEntry = hashEntryTable[i];
		const HashEntry* rightHashEntry = rightOp.AccessEntry (hashEntry.key);
		if (rightHashEntry == nullptr || !(rightHashEntry->value == hashEntry.value))
			return false;
	}

	return true;
}


template <class Key, class Value>
template <class K, class V, class /*= EnableIf<HasOperatorEquals<K>&& HasOperatorEquals<V>>*/>
bool	HashTable<Key, Value>::operator!= (const HashTable& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	return !operator== (rightOp);
}


template <class Key, class Value>
void	HashTable<Key, Value>::EnsureCapacity (USize minCapacity)
{
	if (minCapacity <= hashEntryTable.GetSize ())
		return;

	USize newHashListTableSize = GetHashListTableSize (minCapacity);
	if (newHashListTableSize <= hashListTable.GetSize ())
		return;

	Rehash (newHashListTableSize);
}


template <class Key, class Value>
double	HashTable<Key, Value>::GetAverageSeekFactor () const
{
	if (hashEntryTable.IsEmpty ())
		return 0.0;
	else
		return (static_cast<double> (seekWeightSum) / static_cast<double> (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
ULong	HashTable<Key, Value>::FindMaxSeekFactor () const
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


template <class Key, class Value>
double	HashTable<Key, Value>::GetFillFactor () const
{
	if (hashListTable.GetSize () == 0)
		return 0.0;
	else
		return (static_cast<double> (hashEntryTable.GetSize ()) / static_cast<double> (hashListTable.GetSize ()));
}


template <class Key, class Value>
ULong	HashTable<Key, Value>::CountEmptyLists () const
{
	ULong emptyListCount = 0;
	USize hashListCount = hashListTable.GetSize ();
	for (UIndex i = 0; i < hashListCount; i++) {
		if (hashListTable[i] == nullptr)
			emptyListCount++;
	}

	return emptyListCount;
}


template <class Key, class Value>
GSErrCode	HashTable<Key, Value>::Read (IChannel& ic)
{
	Clear ();

	GS::InputFrame frame (ic, HashTablePrivate::classInfo);
	if (frame.GetStatus () != NoError)
		return frame.GetStatus ();

	USize newSize;
	GSErrCode errorCode = ic.Read (newSize);

	Key key {};
	for (UIndex i = 0; i < newSize && errorCode == NoError; i++) {
		Value value {};
		errorCode = ic.Read (key, value);
		if (errorCode == NoError)
			hashEntryTable.PushNew (key, std::move (value), nullptr);
	}

	if (errorCode == NoError)
		Rehash (GetHashListTableSize (hashEntryTable.GetSize ()));

	return errorCode;
}


template <class Key, class Value>
GSErrCode	HashTable<Key, Value>::Read (IChannel& ic, const FunctionRef<GSErrCode (IChannel&, Key&, Value&)> reader)
{
	Clear ();

	GS::InputFrame frame (ic, HashTablePrivate::classInfo);
	if (frame.GetStatus () != NoError)
		return frame.GetStatus ();

	USize newSize;
	GSErrCode errorCode = ic.Read (newSize);

	if (errorCode == NoError)
		EnsureCapacity (newSize);

	Key key {};
	for (UIndex i = 0; i < newSize && errorCode == NoError; i++) {
		Value value {};
		errorCode = reader (ic, key, value);
		if (errorCode == NoError)
			Add (key, std::move (value));
	}

	return errorCode;
}


template <class Key, class Value>
GSErrCode	HashTable<Key, Value>::Write (OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	GS::OutputFrame frame (oc, HashTablePrivate::classInfo);

	USize hashEntryCount = hashEntryTable.GetSize ();

	GSErrCode errorCode = oc.Write (hashEntryCount);

	for (UIndex i = 0; i < hashEntryCount && errorCode == NoError; i++) {
		const HashEntry& hashEntry = hashEntryTable[i];
		errorCode = oc.Write (hashEntry.key, hashEntry.value);
	}

	return errorCode;
}


template <class Key, class Value>
GSErrCode	HashTable<Key, Value>::Write (OChannel& oc, const FunctionRef<GSErrCode (OChannel&, const Key&, const Value&)> writer) const
{
	NULL_REF_CHECK (oc);

	GS::OutputFrame frame (oc, HashTablePrivate::classInfo);

	USize hashEntryCount = hashEntryTable.GetSize ();

	GSErrCode errorCode = oc.Write (hashEntryCount);

	for (UIndex i = 0; i < hashEntryCount && errorCode == NoError; i++) {
		const HashEntry& hashEntry = hashEntryTable[i];
		errorCode = writer (oc, hashEntry.key, hashEntry.value);
	}

	return errorCode;
}


template <class Key, class Value>
bool	HashTable<Key, Value>::CheckState () const
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


template <class Key, class Value>
const Key&		HashTable<Key, Value>::GetAKey (ULong rnd) const
{
	PRECOND_DEPRECATED (!hashEntryTable.IsEmpty ());

	return hashEntryTable[rnd % hashEntryTable.GetSize ()].key;
}


template <class Key, class Value>
typename HashTable<Key, Value>::HashEntry*		HashTable<Key, Value>::AccessEntry (const Key& key) const
{
	USize hasListCount = hashListTable.GetSize ();
	if (hasListCount == 0)
		return nullptr;

	HashEntry* hashEntry = hashListTable[GS::CalculateHashValue (key) % hasListCount];

	while (hashEntry != nullptr) {
		if (hashEntry->key == key)
			return hashEntry;
		hashEntry = hashEntry->next;
	}

	return nullptr;
}


template <class Key, class Value>
void		HashTable<Key, Value>::EnsureAverageSeekFactor	()
{
	if (GetFillFactor () < minFillFactor)
		return;

	if (GetAverageSeekFactor () <= averageSeekFactorLimit)
		return;

	DecreaseAverageSeekFactor ();
}


template <class Key, class Value>
void		HashTable<Key, Value>::DecreaseAverageSeekFactor ()
{
	Rehash (GetNextHashCapacity (hashListTable.GetSize ()));
}


template <class Key, class Value>
void		HashTable<Key, Value>::IncreaseAverageSeekFactor ()
{
	if (hashEntryTable.GetSize () == 0)
		Clear ();
	else
		Rehash (GetPreviousHashCapacity (hashListTable.GetSize ()));
}


template <class Key, class Value>
USize		HashTable<Key, Value>::GetHashListTableSize (USize hashEntryCount) const
{
	USize optimalListTableSize = static_cast<USize> (static_cast<double> (hashEntryCount) / (2.0 * averageSeekFactorLimit  - 1.0));
	return GetNextHashCapacity (GetNextHashCapacity (optimalListTableSize));
}


template <class Key, class Value>
void		HashTable<Key, Value>::Rehash (USize newHashListTableSize)
{
	hashListTable.SetCapacity (newHashListTableSize);	// if the new capacity is less than old size then this call has no effect
	hashListTable.SetSize (newHashListTableSize);		// SetSize will not waste capacity because of SetCapacity calls
	hashListTable.SetCapacity (newHashListTableSize);	// if the new capacity is greater than old size then this call has no effect
	hashListTable.Fill (nullptr);

	USize newHashListCount = newHashListTableSize;

	USize hashEntryCount = hashEntryTable.GetSize ();
	for (UIndex i = 0; i < hashEntryCount; i++) {
		HashEntry& hashEntry = hashEntryTable[i];
		UIndex newHashListIndex = GS::CalculateHashValue (hashEntry.key) % newHashListCount;
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


template <class Key, class Value>
void		HashTable<Key, Value>::Increment (IteratorState& state) const
{
	state.current++;
}


template <class Key, class Value>
bool		HashTable<Key, Value>::IsEqual (const IteratorState& state1, const IteratorState& state2) const
{
	if (state1.current >= hashEntryTable.GetSize () && state2.current >= hashEntryTable.GetSize ())
		return true;

	return (state1.current == state2.current);
}


template <class Key, class Value>
bool		HashTable<Key, Value>::IsEnd (const IteratorState& state) const
{
	return (state.current >= hashEntryTable.GetSize ());
}


template <class Key, class Value>
Key&		HashTable<Key, Value>::GetCurrent (const KeyIteratorState& state)
{
	return hashEntryTable[state.current].key;
}


template <class Key, class Value>
const Key&		HashTable<Key, Value>::GetCurrent (const KeyIteratorState& state) const
{
	return hashEntryTable[state.current].key;
}


template <class Key, class Value>
Value&		HashTable<Key, Value>::GetCurrent (const ValueIteratorState& state)
{
	return hashEntryTable[state.current].value;
}


template <class Key, class Value>
const Value&	HashTable<Key, Value>::GetCurrent (const ValueIteratorState& state) const
{
	return hashEntryTable[state.current].value;
}


template <class Key, class Value>
typename HashTable<Key, Value>::CurrentPair&		HashTable<Key, Value>::GetCurrent (const PairIteratorState& state)
{
	HashEntry& entry = hashEntryTable[state.current];

	return *::new (state.currentPair) CurrentPair { entry.key, entry.value }; // Constructing a new object in place of the existing state.currentPair is safe, because it is trivially destructible so we can omit the call to its destructor.
}


template <class Key, class Value>
const typename HashTable<Key, Value>::CurrentPair&		HashTable<Key, Value>::GetCurrent (const PairIteratorState& state) const
{
	const HashEntry& entry = hashEntryTable[state.current];

	return *::new (state.currentPair) CurrentPair { entry.key, const_cast<Value&> (entry.value) };  // Constructing a new object in place of the existing state.currentPair is safe, because it is trivially destructible so we can omit the call to its destructor.
}


template <class Key, class Value>
typename HashTable<Key, Value>::ConstCurrentPair&		HashTable<Key, Value>::GetCurrent (const ConstPairIteratorState& state)
{
	HashEntry& entry = hashEntryTable[state.current];

	return *::new (state.currentPair) ConstCurrentPair { entry.key, entry.value };  // Constructing a new object in place of the existing state.currentPair is safe, because it is trivially destructible so we can omit the call to its destructor.
}


template <class Key, class Value>
const typename HashTable<Key, Value>::ConstCurrentPair&		HashTable<Key, Value>::GetCurrent (const ConstPairIteratorState& state) const
{
	const HashEntry& entry = hashEntryTable[state.current];

	return *::new (state.currentPair) ConstCurrentPair { entry.key, entry.value };  // Constructing a new object in place of the existing state.currentPair is safe, because it is trivially destructible so we can omit the call to its destructor.
}


template <class Key, class Value>
HashTable<Key, Value>::KeyConversionEnumerator::KeyConversionEnumerator (const HashTable& source):
	source (&source)
{
}


template <class Key, class Value>
void	HashTable<Key, Value>::KeyConversionEnumerator::Enumerate (const std::function<void (const Key&)>& processor) const
{
	source->EnumerateKeys (processor);
}


template <class Key, class Value>
USize	HashTable<Key, Value>::KeyConversionEnumerator::GetSizeHint (void) const
{
	return source->GetSize ();
}


template <class Key, class Value>
HashTable<Key, Value>::ValueConversionEnumerator::ValueConversionEnumerator (const HashTable& source):
	source (&source)
{
}


template <class Key, class Value>
void	HashTable<Key, Value>::ValueConversionEnumerator::Enumerate (const std::function<void (const Value&)>& processor) const
{
	source->EnumerateValues (processor);
}


template <class Key, class Value>
USize	HashTable<Key, Value>::ValueConversionEnumerator::GetSizeHint (void) const
{
	return source->GetSize ();
}


// === Global functions ================================================================================================

template <class Key, class Value>
auto	begin (HashTable<Key, Value>& hashTable)
{
	return hashTable.Begin ();
}


template <class Key, class Value>
auto	end (HashTable<Key, Value>& hashTable)
{
	return hashTable.End ();
}


template <class Key, class Value>
auto	begin (const HashTable<Key, Value>& hashTable)
{
	return hashTable.Begin ();
}


template <class Key, class Value>
auto	end (const HashTable<Key, Value>& hashTable)
{
	return hashTable.End ();
}


template <class Key, class Value>
auto	GetInserter (HashTable<Key, Value>& hashTable)
{
	return AddInserter<HashTable<Key, Value>> (&hashTable);
}


}	// namespace GS


#endif
