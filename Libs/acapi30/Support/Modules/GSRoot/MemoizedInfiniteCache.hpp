
// *****************************************************************************
//
//                             class MemoizedInfiniteCache
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SzoBe
//
//
//
// *****************************************************************************


#if !defined MEMOIZEDINFINITECACHE_HPP
#define MEMOIZEDINFINITECACHE_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "HashTable.hpp"

namespace GS {

template <class Key, class Value>
struct MemoizedInfiniteCache {
	GS::HashTable<Key, Value> cache;

	const Value*	Get (const Key& key) const;
	const Value*	Add (const Key& key, const Value& value);
	const Value*	Add (const Key& key, Value&& value);
};


template <class Key, class Value>
const Value*	MemoizedInfiniteCache<Key, Value>::Get (const Key& key) const
{
	return cache.GetPtr (key);
}


template <class Key, class Value>
const Value*	MemoizedInfiniteCache<Key, Value>::Add (const Key& key, const Value& value)
{
	Value *innerValuePtr;
	cache.Add (key, value, &innerValuePtr);
	return innerValuePtr;
}


template <class Key, class Value>
const Value*	MemoizedInfiniteCache<Key, Value>::Add (const Key& key, Value&& value)
{
	Value *innerValuePtr;
	cache.Add (key, std::move (value), &innerValuePtr);
	return innerValuePtr;
}


} // namespace GS


#endif
