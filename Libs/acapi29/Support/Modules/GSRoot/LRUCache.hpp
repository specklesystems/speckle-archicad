
// *****************************************************************************
//
//                                Class LRUCache
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined LRUCACHE_HPP
#define LRUCACHE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "PagedArray.hpp"
#include "HashTable.hpp"


// ============================== Class LRUCache ===============================

namespace GS {

class GSROOT_DLL_EXPORT LRUCachePrivate {
public:
	static GS::ClassInfo	classInfo;	// LRUCache's private classInfo
};


template <class IndexType, class ItemType>
class LRUCache {
public:
	class Control {
	public:
		virtual ~Control () {};
		virtual bool	CacheMissed (const LRUCache& /*source*/, const IndexType& /*idx*/, ItemType* /*item*/) { return false; }

		virtual void	AboutToDiscard (const LRUCache& /*source*/, const IndexType& /*idx*/, const ItemType& /*item*/) {}
		virtual void	AboutToSet     (const LRUCache& /*source*/, const IndexType& /*idx*/, const ItemType& /*oldItem*/, const ItemType& /*newItem*/) {}
	};

private:
	struct CacheEntry {
		IndexType	key;		// stores the index (key)
		ItemType	value;		// stores the item (value)
		ULong		refCounter;	// number of references to the entry (MaxUIndex indicates deleted entry)
		CacheEntry*	younger;	// previous (younger in time) entry (or nullptr)
		CacheEntry*	older;		// next (older in time) entry (or nullptr)

		CacheEntry ():
			refCounter (0),
			younger (nullptr),
			older   (nullptr) {}

		inline void		Set (const IndexType& newKey,
							 const ItemType&  newValue,
							 ULong            newRefCounter,
							 CacheEntry*      newYounger,
							 CacheEntry*      newOlder)
		{
			key        = newKey;
			value      = newValue;
			refCounter = newRefCounter;
			younger    = newYounger;
			older      = newOlder;
		}
	};

	struct KeyRef {
		const IndexType* key;

		KeyRef (const IndexType* idx = nullptr): key (idx) {}

		inline bool		operator== (const KeyRef& rightOp) const { return (*key == *rightOp.key); }
		ULong			GenerateHashValue () const				 { return GS::CalculateHashValue (*key); }
	};

	enum { DefaultCacheCapacity = 128 };

	PagedArray<CacheEntry>			cacheEntryTable;	// stores cache entries
	HashTable<KeyRef, CacheEntry*>	indexTable;			// provides fast access to cache entries based on their keys
	USize			capacity;			// desired capacity of the cache (real capacity can be larger when all items are acquired and new items are added)
	USize			acquiredItemCount;	// number of acquired items
	CacheEntry*		youngest;			// first (youngest in time) entry (or nullptr)
	CacheEntry*		oldest;				// last (oldest in time) entry (or nullptr)
	CacheEntry*		free;				// list of free cache entries (or nullptr)
	USize			hitCount;			// number of cache hits
	USize			missCount;			// number of cache misses
	Control*		userControl;		// control implementation supplied by the user (or nullptr)

	CacheEntry*		Add (const IndexType& idx, const ItemType& item);

	CacheEntry*		ObtainEntry (const IndexType& idx);
	CacheEntry*		AccessEntry (const IndexType& idx);

	void			EnsureCapacity (void);
	inline void		Unlink (CacheEntry* cacheEntry);

public:
		// Definitions

	typedef IndexType KeyType;		// type of the index the LRUCache is searchable by
	typedef ItemType  ValueType;	// type of the value the LRUCache stores

		// Constructors

	explicit LRUCache (USize cacheCapacity = 0, Control* control = nullptr);
	LRUCache (const LRUCache& source);
   ~LRUCache ();
	LRUCache&	operator= (const LRUCache& source);

		// Item access

	inline ItemType&	operator[] (const IndexType& idx) gs_lifebound;

	inline ItemType&	Get (const IndexType& idx) gs_lifebound;
	inline bool			Get (const IndexType& idx, ItemType* item);
	inline bool			Get (const IndexType& idx, ItemType** item);

	inline ItemType&	Acquire (const IndexType& idx) gs_lifebound;
	inline bool			Acquire (const IndexType& idx, ItemType** item);
	inline void			Release (const IndexType& idx);

	inline bool			IsAcquired (const IndexType& idx);

	void				ReleaseAll (void);

		// Content management

	void	Set     (const IndexType& idx, const ItemType& item);
	void	Discard (const IndexType& idx);
	bool	DiscardOldest (void);
	void	Clear   (void);

	inline USize	GetSize (void) const;
	inline bool		IsEmpty (void) const;

	inline USize	GetAcquiredCount (void) const;

		// Content query

	inline bool		ContainsKey (const IndexType& idx) const;

		// Performance tuning

	USize	GetCapacity (void) const;
	void	SetCapacity (USize newCapacity);

	USize	GetHitCount  (void) const;
	USize	GetMissCount (void) const;
	double	GetHitRatio  (void) const;
	double	GetMissRatio (void) const;
	void	ResetHitCounting (void);

		// Debug

	bool	CheckState (void) const;

	const IndexType&	GetAnAcquiredItem   (ULong rnd) const gs_lifebound;
	const IndexType&	GetAnUnacquiredItem (ULong rnd) const gs_lifebound;
};


template <class IndexType, class ItemType>
LRUCache<IndexType, ItemType>::LRUCache (USize cacheCapacity, Control* control)
{
	if (cacheCapacity == 0)
		cacheCapacity = DefaultCacheCapacity;
	capacity = cacheCapacity;

	acquiredItemCount = 0;

	youngest = nullptr;
	oldest   = nullptr;
	free     = nullptr;

	hitCount  = 0;
	missCount = 0;

	userControl = control;
}


template <class IndexType, class ItemType>
LRUCache<IndexType, ItemType>::LRUCache (const LRUCache& source)
{
	NULL_REF_CHECK (source);

	// cache doesn't need to copy the content

	capacity = source.capacity;

	acquiredItemCount = 0;

	youngest = nullptr;
	oldest   = nullptr;
	free     = nullptr;

	hitCount  = 0;
	missCount = 0;

	userControl = source.userControl;
}


template <class IndexType, class ItemType>
LRUCache<IndexType, ItemType>::~LRUCache ()
{
	Clear ();
}


template <class IndexType, class ItemType>
LRUCache<IndexType, ItemType>&		LRUCache<IndexType, ItemType>::operator= (const LRUCache& source)
{
	NULL_REF_CHECK (source);

	if (&source != this) {
		Clear ();

		// cache doesn't need to copy the content
	}

	return *this;
}


template <class IndexType, class ItemType>
inline ItemType&	LRUCache<IndexType, ItemType>::operator[] (const IndexType& idx)
{
	NULL_REF_CHECK (idx);

	CacheEntry* cacheEntry = ObtainEntry (idx);
	REF_CHECK (cacheEntry != nullptr);

	return cacheEntry->value;
}


template <class IndexType, class ItemType>
inline ItemType&	LRUCache<IndexType, ItemType>::Get (const IndexType& idx)
{
	NULL_REF_CHECK (idx);

	CacheEntry* cacheEntry = ObtainEntry (idx);
	REF_CHECK_R (cacheEntry != nullptr);

	return cacheEntry->value;
}


template <class IndexType, class ItemType>
inline bool		LRUCache<IndexType, ItemType>::Get (const IndexType& idx, ItemType* item)
{
	NULL_REF_CHECK (idx);
	NULL_PTR_CHECK (item);

	const CacheEntry* cacheEntry = ObtainEntry (idx);
	if (cacheEntry == nullptr)
		return false;

	*item = cacheEntry->value;

	return true;
}


template <class IndexType, class ItemType>
inline bool		LRUCache<IndexType, ItemType>::Get (const IndexType& idx, ItemType** item)
{
	NULL_REF_CHECK (idx);
	NULL_PTR_CHECK (item);

	CacheEntry* cacheEntry = ObtainEntry (idx);
	if (cacheEntry == nullptr)
		return false;

	*item = &(cacheEntry->value);

	return true;
}


template <class IndexType, class ItemType>
inline ItemType&	LRUCache<IndexType, ItemType>::Acquire (const IndexType& idx)
{
	NULL_REF_CHECK (idx);

	CacheEntry* cacheEntry = ObtainEntry (idx);
	REF_CHECK_R (cacheEntry != nullptr);

	if (cacheEntry->refCounter == 0)
		acquiredItemCount++;
	cacheEntry->refCounter++;

	return cacheEntry->value;
}


template <class IndexType, class ItemType>
inline bool		LRUCache<IndexType, ItemType>::Acquire (const IndexType& idx, ItemType** item)
{
	NULL_REF_CHECK (idx);
	NULL_PTR_CHECK (item);

	CacheEntry* cacheEntry = ObtainEntry (idx);
	if (cacheEntry == nullptr)
		return false;

	if (cacheEntry->refCounter == 0)
		acquiredItemCount++;
	cacheEntry->refCounter++;
	*item = &(cacheEntry->value);

	return true;
}


template <class IndexType, class ItemType>
inline void		LRUCache<IndexType, ItemType>::Release (const IndexType& idx)
{
	NULL_REF_CHECK (idx);

	CacheEntry* cacheEntry;
	if (indexTable.Get (&idx, &cacheEntry)) {
		DBASSERT (cacheEntry->refCounter > 0);
		if (cacheEntry->refCounter > 0) {
			cacheEntry->refCounter--;
			if (cacheEntry->refCounter == 0)
				acquiredItemCount--;
			EnsureCapacity ();
		}
	}
}


template <class IndexType, class ItemType>
inline bool	LRUCache<IndexType, ItemType>::IsAcquired (const IndexType& idx)
{
	NULL_REF_CHECK (idx);

	CacheEntry* cacheEntry = ObtainEntry (idx);
	if (cacheEntry == nullptr)
		return false;

	if (cacheEntry->refCounter == 0)
		return false;

	return true;
}


template <class IndexType, class ItemType>
void	LRUCache<IndexType, ItemType>::ReleaseAll (void)
{
	CacheEntry* cacheEntry = youngest;
	while (cacheEntry != nullptr) {
		cacheEntry->refCounter = 0;
		cacheEntry = cacheEntry->older;
	}

	acquiredItemCount = 0;

	EnsureCapacity ();
}


template <class IndexType, class ItemType>
void	LRUCache<IndexType, ItemType>::Set (const IndexType& idx, const ItemType& item)
{
	NULL_REF_CHECK (idx);
	NULL_REF_CHECK (item);

		// if the item is in the cache then its value can be set

	CacheEntry* cacheEntry = AccessEntry (idx);
	if (cacheEntry != nullptr) {
		if (userControl != nullptr)
			userControl->AboutToSet (*this, cacheEntry->key, cacheEntry->value, item);
		cacheEntry->value = item;
		return;
	}

		// if the item is not in the cache then it should be added

	Add (idx, item);
}


template <class IndexType, class ItemType>
void	LRUCache<IndexType, ItemType>::Discard (const IndexType& idx)
{
	NULL_REF_CHECK (idx);

	CacheEntry* cacheEntry;
	if (!indexTable.Get (&idx, &cacheEntry))
		return;

	DBASSERT (cacheEntry->refCounter != MaxUIndex);	// can't be deleted

	if (cacheEntry->refCounter > 0) {	// discarded item can't be acquired
		DBBREAK ();
		acquiredItemCount--;
	}

	if (userControl != nullptr)
		userControl->AboutToDiscard (*this, cacheEntry->key, cacheEntry->value);

	indexTable.Delete (&cacheEntry->key);
	Unlink (cacheEntry);
	cacheEntry->Set (IndexType (), ItemType (), MaxUIndex, nullptr, free);
	free = cacheEntry;

	EnsureCapacity ();
}


template <class IndexType, class ItemType>
bool	LRUCache<IndexType, ItemType>::DiscardOldest (void)
{
	CacheEntry* cacheEntry = oldest;
	while (cacheEntry != nullptr) {
		if (cacheEntry->refCounter == 0) {
			Discard (cacheEntry->key);
			return true;
		}
		cacheEntry = cacheEntry->younger;
	}
	return false;
}


template <class IndexType, class ItemType>
void	LRUCache<IndexType, ItemType>::Clear (void)
{
	if (userControl != nullptr) {
		for (UIndex i = 0; i < cacheEntryTable.GetSize (); i++) {
			CacheEntry* cacheEntry = &cacheEntryTable[i];
			DBASSERT (cacheEntry->refCounter == 0 || cacheEntry->refCounter == MaxUIndex);
			if (cacheEntry->refCounter != MaxUIndex)
				userControl->AboutToDiscard (*this, cacheEntry->key, cacheEntry->value);
		}
	}

	cacheEntryTable.Clear ();
	indexTable.Clear ();

	acquiredItemCount = 0;

	youngest = nullptr;
	oldest   = nullptr;
	free     = nullptr;
}


template <class IndexType, class ItemType>
inline USize	LRUCache<IndexType, ItemType>::GetSize (void) const
{
	return indexTable.GetSize ();
}


template <class IndexType, class ItemType>
inline bool		LRUCache<IndexType, ItemType>::IsEmpty (void) const
{
	return (indexTable.GetSize () == 0);
}


template <class IndexType, class ItemType>
inline USize	LRUCache<IndexType, ItemType>::GetAcquiredCount (void) const
{
	return acquiredItemCount;
}


template <class IndexType, class ItemType>
bool	LRUCache<IndexType, ItemType>::ContainsKey (const IndexType& idx) const
{
	NULL_REF_CHECK (idx);

	return (indexTable.ContainsKey (&idx));
}


template <class IndexType, class ItemType>
USize	LRUCache<IndexType, ItemType>::GetCapacity (void) const
{
	return capacity;
}


template <class IndexType, class ItemType>
void	LRUCache<IndexType, ItemType>::SetCapacity (USize newCapacity)
{
	if (newCapacity == 0)
		newCapacity = DefaultCacheCapacity;
	capacity = newCapacity;

	EnsureCapacity ();
}


template <class IndexType, class ItemType>
USize	LRUCache<IndexType, ItemType>::GetHitCount (void) const
{
	return hitCount;
}


template <class IndexType, class ItemType>
USize	LRUCache<IndexType, ItemType>::GetMissCount (void) const
{
	return missCount;
}


template <class IndexType, class ItemType>
double	LRUCache<IndexType, ItemType>::GetHitRatio (void) const
{
	if (hitCount + missCount == 0)
		return 1.0;
	else
		return (static_cast<double> (hitCount) / static_cast<double> (hitCount + missCount));
}


template <class IndexType, class ItemType>
double	LRUCache<IndexType, ItemType>::GetMissRatio (void) const
{
	if (hitCount + missCount == 0)
		return 1.0;
	else
		return (static_cast<double> (missCount) / static_cast<double> (hitCount + missCount));
}


template <class IndexType, class ItemType>
void	LRUCache<IndexType, ItemType>::ResetHitCounting (void)
{
	hitCount  = 0;
	missCount = 0;
}


template <class IndexType, class ItemType>
bool	LRUCache<IndexType, ItemType>::CheckState (void) const
{
	if (!cacheEntryTable.CheckState ()  ||
		!indexTable.CheckState ())
		return false;

	if (acquiredItemCount > indexTable.GetSize ())
		return false;

	USize computedAcquiredItemCount = 0;
	for (UIndex i = 0; i < cacheEntryTable.GetSize (); i++) {
		if (cacheEntryTable[i].refCounter > 0 && cacheEntryTable[i].refCounter != MaxUSize)
			computedAcquiredItemCount++;
	}
	if (acquiredItemCount != computedAcquiredItemCount)
		return false;

	USize computedFreeCount1 = 0;
	CacheEntry* cacheEntry = free;
	while (cacheEntry != nullptr) {
		computedFreeCount1++;
		cacheEntry = cacheEntry->older;
	}
	USize computedFreeCount2 = 0;
	for (UIndex i = 0; i < cacheEntryTable.GetSize (); i++) {
		if (cacheEntryTable[i].refCounter == MaxUSize)
			computedFreeCount2++;
	}
	if (computedFreeCount1 != computedFreeCount2)
		return false;

	if (indexTable.GetSize () + computedFreeCount1 != cacheEntryTable.GetSize ())
		return false;

	USize youngestListLength = 0;
	cacheEntry = youngest;
	while (cacheEntry != nullptr) {
		if (!indexTable.ContainsKey (&(cacheEntry->key)))
			return false;
		youngestListLength++;
		cacheEntry = cacheEntry->older;
	}
	USize oldestListLength = 0;
	cacheEntry = oldest;
	while (cacheEntry != nullptr) {
		if (!indexTable.ContainsKey (&(cacheEntry->key)))
			return false;
		oldestListLength++;
		cacheEntry = cacheEntry->younger;
	}
	if (youngestListLength != oldestListLength)
		return false;

	if (youngestListLength != indexTable.GetSize ())
		return false;

	return true;
}


template <class IndexType, class ItemType>
const IndexType&	LRUCache<IndexType, ItemType>::GetAnAcquiredItem (ULong rnd) const
{
	PRECOND_R_DEPRECATED (acquiredItemCount > 0);

	UIndex i = rnd % cacheEntryTable.GetSize ();
	while (cacheEntryTable[i].refCounter == 0 || cacheEntryTable[i].refCounter == MaxUSize)
		i = (i + 1) % cacheEntryTable.GetSize ();

	return cacheEntryTable[i].key;
}


template <class IndexType, class ItemType>
const IndexType&	LRUCache<IndexType, ItemType>::GetAnUnacquiredItem (ULong rnd) const
{
	PRECOND_R_DEPRECATED (acquiredItemCount < GetSize ());

	UIndex i = rnd % cacheEntryTable.GetSize ();
	while (cacheEntryTable[i].refCounter != 0)
		i = (i + 1) % cacheEntryTable.GetSize ();

	return cacheEntryTable[i].key;
}


template <class IndexType, class ItemType>
typename GS::LRUCache<IndexType, ItemType>::CacheEntry*		LRUCache<IndexType, ItemType>::Add (const IndexType& idx, const ItemType& item)
{
	CacheEntry* newEntry = nullptr;
	if (free != nullptr) {
			// using first entry from the free list

		newEntry = free;
		free = newEntry->older;
	} else {
		USize size = GetSize ();
		if (size >= capacity && acquiredItemCount < size) {
				// if the capacity is full then oldest unacquired entry should be used

			newEntry = oldest;
			while (newEntry->refCounter > 0)
				newEntry = newEntry->younger;
			if (userControl != nullptr)
				userControl->AboutToDiscard (*this, newEntry->key, newEntry->value);
			indexTable.Delete (&newEntry->key);
			Unlink (newEntry);
		} else {
				// if the capacity is not full or every item is acquired then adding a new entry

			cacheEntryTable.Push (CacheEntry ());
			newEntry = &cacheEntryTable.GetLast ();
		}
	}

	newEntry->Set (idx, item, 0, nullptr, youngest);
	if (youngest != nullptr)
		youngest->younger = newEntry;
	youngest = newEntry;
	if (oldest == nullptr)
		oldest = newEntry;

	indexTable.Add (&(newEntry->key), newEntry);

	return newEntry;
}


template <class IndexType, class ItemType>
typename LRUCache<IndexType, ItemType>::CacheEntry*		LRUCache<IndexType, ItemType>::ObtainEntry (const IndexType& idx)
{
	CacheEntry* cacheEntry = AccessEntry (idx);
	if (cacheEntry == nullptr) {
		missCount++;

		if (userControl != nullptr) {
			ItemType item;
			if (userControl->CacheMissed (*this, idx, &item))
				cacheEntry = Add (idx, item);
		}
	} else {
		hitCount++;
	}

	return cacheEntry;
}


template <class IndexType, class ItemType>
typename LRUCache<IndexType, ItemType>::CacheEntry*		LRUCache<IndexType, ItemType>::AccessEntry (const IndexType& idx)
{
	CacheEntry* cacheEntry;
	if (!indexTable.Get (&idx, &cacheEntry))
		return nullptr;

	if (cacheEntry != youngest) {
		Unlink (cacheEntry);

		youngest->younger   = cacheEntry;
		cacheEntry->younger = nullptr;
		cacheEntry->older   = youngest;
		youngest            = cacheEntry;
	}

	return cacheEntry;
}


template <class IndexType, class ItemType>
void	LRUCache<IndexType, ItemType>::EnsureCapacity (void)
{
	if (cacheEntryTable.GetSize () <= capacity)
		return;	// capacity is OK

	if (cacheEntryTable.GetSize () == acquiredItemCount)
		return;	// nothing can be done, every item is acquired

	while (cacheEntryTable.GetSize () > capacity) {
		CacheEntry* lastEntry = &cacheEntryTable.GetLast ();
		if (lastEntry->refCounter == 0) {
				// if the entry is not acquired then it can be deleted

			if (userControl != nullptr)
				userControl->AboutToDiscard (*this, lastEntry->key, lastEntry->value);
			indexTable.Delete (&lastEntry->key);
			Unlink (lastEntry);
			cacheEntryTable.Delete (cacheEntryTable.GetSize () - 1);
		} else if (lastEntry->refCounter == MaxUIndex) {
				// if the entry is deleted then it should be unlinked from the free list and can be deleted

			CacheEntry* cacheEntry = free;
			while (cacheEntry != lastEntry && cacheEntry->older != lastEntry)
				cacheEntry = cacheEntry->older;
			if (cacheEntry == lastEntry)
				free = lastEntry->older;
			else
				cacheEntry->older = lastEntry->older;
			cacheEntryTable.Delete (cacheEntryTable.GetSize () - 1);
		} else {
			break;	// the last entry can not be eliminated because it is acquired
		}
	}
}


template <class IndexType, class ItemType>
inline void		LRUCache<IndexType, ItemType>::Unlink (CacheEntry* cacheEntry)
{
	if (cacheEntry->younger != nullptr)
		cacheEntry->younger->older = cacheEntry->older;
	else
		youngest = cacheEntry->older;

	if (cacheEntry->older != nullptr)
		cacheEntry->older->younger = cacheEntry->younger;
	else
		oldest = cacheEntry->younger;
}


}	// namespace GS
// ______________________________ Class LRUCache _______________________________


#endif
