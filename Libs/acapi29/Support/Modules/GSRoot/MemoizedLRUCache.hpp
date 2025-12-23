
// *****************************************************************************
//
//                             class Cache<LeastRecentlyUsed>
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SzoBe
//
//
//
// *****************************************************************************


#if !defined MEMOIZEDLRUCACHE_HPP
#define MEMOIZEDLRUCACHE_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "LRUCache.hpp"


namespace GS {


template <class Key, class Value>
struct MemoizedLRUCache {
	mutable LRUCache<Key, Value> cache;

	const Value*	Get (const Key& key) const;
	const Value*	Add (const Key& key, const Value& value);
	const Value*	Add (const Key& key, Value&& value);
};


template <class Key, class Value>
const Value*	GS::MemoizedLRUCache<Key, Value>::Get (const Key& key) const
{
	Value* value = nullptr;
	cache.Get (key, &value);

	return value;
}


template <class Key, class Value>
const Value*	GS::MemoizedLRUCache<Key, Value>::Add (const Key& key, const Value& value)
{
	cache.Set (key, value);

	return Get (key);
}


template <class Key, class Value>
const Value*	GS::MemoizedLRUCache<Key, Value>::Add (const Key& key, Value&& value)
{
	cache.Set (key, std::move (value));

	return Get (key);
}


} // namespace GS


#endif
