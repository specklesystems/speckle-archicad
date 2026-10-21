// *********************************************************************************************************************
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	NZ
//
// SG compatible
//
// *********************************************************************************************************************

#if !defined STABLEHASHTABLE_HPP
#define STABLEHASHTABLE_HPP

#pragma once

// ----------------------------------------------------- Includes ------------------------------------------------------

#include "HashTable.hpp"
#include "SmallObj.hpp"


// =============================================== Class StableHashTable ===============================================

namespace GS
{

template <class IndexType, class ItemType>
class StableHashTable {
private:
	FixedAllocator						allocator;
	GS::HashTable<IndexType, ItemType*>	index;

public:
	class ConstValueIterator {
	public:
		explicit ConstValueIterator (const typename GS::HashTable<IndexType, ItemType*>::ConstValueIterator& iter);

		const ItemType& operator* () const;
		const ItemType* operator-> () const;

		ConstValueIterator& operator++ ();
		ConstValueIterator operator++ (int);

		bool operator== (const ConstValueIterator& rightOp) const;
		bool operator!= (const ConstValueIterator& rightOp) const;

	private:
		typename GS::HashTable<IndexType, ItemType*>::ConstValueIterator iter;
	};

	class ConstValueRange {
	public:
		explicit ConstValueRange (const StableHashTable* hashTablePtr);

		ConstValueIterator begin () const;
		ConstValueIterator end () const;

	private:
		const StableHashTable* hashTablePtr;
	};

		// Constructors

	StableHashTable ();
	~StableHashTable ();

		// Item access

	ItemType&		operator[] (const IndexType& key);
	const ItemType&	operator[] (const IndexType& key) const;

	ItemType*		GetPtr (const IndexType& idx);
	const ItemType*	GetPtr (const IndexType& idx) const;

	ConstValueIterator BeginValues () const;
	ConstValueIterator EndValues () const;
	ConstValueRange ConstValues () const;

		// Content management

	void Add (const IndexType& idx, const ItemType& item);

	void Put (const IndexType& idx, const ItemType& item);

	void Delete (const IndexType& key);

	void Clear ();

	USize GetSize () const;
	bool IsEmpty () const;

		// Content query

	bool ContainsKey (const IndexType& key) const;
};


template <class IndexType, class ItemType>
StableHashTable<IndexType, ItemType>::ConstValueIterator::ConstValueIterator (const typename GS::HashTable<IndexType, ItemType*>::ConstValueIterator& iter)
	: iter (iter)
{
}


template <class IndexType, class ItemType>
const ItemType& StableHashTable<IndexType, ItemType>::ConstValueIterator::operator* () const
{
	return **iter;
}


template <class IndexType, class ItemType>
const ItemType* StableHashTable<IndexType, ItemType>::ConstValueIterator::operator-> () const
{
	return *iter;
}


template <class IndexType, class ItemType>
typename StableHashTable<IndexType, ItemType>::ConstValueIterator& StableHashTable<IndexType, ItemType>::ConstValueIterator::operator++ ()
{
	++iter;
	return *this;
}


template <class IndexType, class ItemType>
typename StableHashTable<IndexType, ItemType>::ConstValueIterator StableHashTable<IndexType, ItemType>::ConstValueIterator::operator++ (int)
{
	return ConstValueIterator (iter++);
}


template <class IndexType, class ItemType>
bool StableHashTable<IndexType, ItemType>::ConstValueIterator::operator== (const ConstValueIterator& rightOp) const
{
	return iter == rightOp.iter;
}


template <class IndexType, class ItemType>
bool StableHashTable<IndexType, ItemType>::ConstValueIterator::operator!= (const ConstValueIterator& rightOp) const
{
	return !(*this == rightOp);
}


template <class IndexType, class ItemType>
typename StableHashTable<IndexType, ItemType>::ConstValueIterator StableHashTable<IndexType, ItemType>::BeginValues () const
{
	return ConstValueIterator (index.BeginValues ());
}


template <class IndexType, class ItemType>
typename StableHashTable<IndexType, ItemType>::ConstValueIterator StableHashTable<IndexType, ItemType>::EndValues () const
{
	return ConstValueIterator (index.EndValues ());
}


template <class IndexType, class ItemType>
StableHashTable<IndexType, ItemType>::ConstValueRange::ConstValueRange (const StableHashTable* hashTablePtr)
	: hashTablePtr (hashTablePtr)
{
}


template <class IndexType, class ItemType>
typename StableHashTable<IndexType, ItemType>::ConstValueIterator StableHashTable<IndexType, ItemType>::ConstValueRange::begin () const
{
	return hashTablePtr->BeginValues ();
}


template <class IndexType, class ItemType>
typename StableHashTable<IndexType, ItemType>::ConstValueIterator StableHashTable<IndexType, ItemType>::ConstValueRange::end () const
{
	return hashTablePtr->EndValues ();
}


template <class IndexType, class ItemType>
typename StableHashTable<IndexType, ItemType>::ConstValueRange StableHashTable<IndexType, ItemType>::ConstValues () const
{
	return StableHashTable<IndexType, ItemType>::ConstValueRange (this);
}


template <class IndexType, class ItemType>
inline StableHashTable<IndexType, ItemType>::StableHashTable ():
	allocator (sizeof (ItemType))
{
}


template <class IndexType, class ItemType>
inline StableHashTable<IndexType, ItemType>::~StableHashTable ()
{
	Clear ();
}


template <class IndexType, class ItemType>
inline ItemType& StableHashTable<IndexType, ItemType>::operator[] (const IndexType& key)
{
	return *index[key];
}


template <class IndexType, class ItemType>
const ItemType& StableHashTable<IndexType, ItemType>::operator[] (const IndexType& key) const
{
	return *index[key];
}


template <class IndexType, class ItemType>
inline ItemType*	StableHashTable<IndexType, ItemType>::GetPtr (const IndexType& idx)
{
	ItemType** indexPtr = index.GetPtr (idx);
	return indexPtr != nullptr ? *indexPtr : nullptr;
}


template <class IndexType, class ItemType>
inline const ItemType*	StableHashTable<IndexType, ItemType>::GetPtr (const IndexType& idx) const
{
	const ItemType* const* indexPtr = index.GetPtr (idx);
	return indexPtr != nullptr ? *indexPtr : nullptr;
}


template <class IndexType, class ItemType>
inline void StableHashTable<IndexType, ItemType>::Add (const IndexType& idx, const ItemType& item)
{
	index.Add (idx, ::new (allocator.Allocate ()) ItemType (item));
}


template <class IndexType, class ItemType>
inline void StableHashTable<IndexType, ItemType>::Put (const IndexType& idx, const ItemType& item)
{
	ItemType* ptr = index.GetPtr (idx);
	if (ptr != nullptr) {
		*index[idx] = item;
	} else {
		Add (idx, item);
	}
}


template <class IndexType, class ItemType>
inline void StableHashTable<IndexType, ItemType>::Delete (const IndexType& key)
{
	index[key]->~ItemType ();
	allocator.Deallocate (index[key]);
	index.Delete (key);
}


template <class IndexType, class ItemType>
inline void StableHashTable<IndexType, ItemType>::Clear ()
{
	for (auto it = index.EnumerateValues (); it != nullptr; ++it) {
		(*it)->~ItemType ();
		allocator.Deallocate (*it);
	}
	index.Clear ();
}


template <class IndexType, class ItemType>
inline USize StableHashTable<IndexType, ItemType>::GetSize () const
{
	return index.GetSize ();
}


template <class IndexType, class ItemType>
inline bool StableHashTable<IndexType, ItemType>::IsEmpty () const
{
	return index.IsEmpty ();
}


template <class IndexType, class ItemType>
inline bool StableHashTable<IndexType, ItemType>::ContainsKey (const IndexType& key) const
{
	return index.ContainsKey (key);
}

}

#endif
