#if !defined(POLYGONBOOLEAN_ALLOCATOR_HPP)
#define POLYGONBOOLEAN_ALLOCATOR_HPP
#pragma once

#include "ThreadLocalMemoryPool.hpp"

namespace PolygonBoolean {

template <typename T, USize ThreadLocalPoolSize = 1, USize GlobalPoolSize = 1>
class AllocatedFromThreadLocalMemoryPool {
public:
	void* operator new (size_t size) {
		DBASSERT (size == sizeof (T));
		UNUSED_PARAMETER (size);

		return pool.Allocate ();
	}

	void operator delete (void* ptr) {
		pool.Deallocate (ptr);
	}

private:
	static GS::ThreadLocalMemoryPool pool;
};

template <typename T, USize ThreadLocalPoolSize, USize GlobalPoolSize>
GS::ThreadLocalMemoryPool AllocatedFromThreadLocalMemoryPool<T, ThreadLocalPoolSize, GlobalPoolSize>::pool (
	sizeof (T),
	ThreadLocalPoolSize,
	GlobalPoolSize);

}	// namespace PolygonBoolean

#endif	// POLYGONBOOLEAN_ALLOCATOR_HPP