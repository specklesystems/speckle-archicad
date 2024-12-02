#ifndef THREADLOCALMEMORYPOOL_HPP
#define THREADLOCALMEMORYPOOL_HPP
#pragma once

#include "FastThreadLocal.hpp"
#include "SpinLock.hpp"
#include "Array.hpp"
#include "MemoryManager.hpp"

namespace GS {

class GSROOT_DLL_EXPORT ThreadLocalMemoryPool {
private:
	class ThreadLocalCache {
	public:
		ThreadLocalCache	() : pool (nullptr) {}
		~ThreadLocalCache	();

		void EnsureOwner (ThreadLocalMemoryPool* ownerPool);

		GS::Array<void*> buffers;

	private:
		ThreadLocalMemoryPool* pool;
	};

	class GlobalCache {
	public:
		~GlobalCache ();

		GS::Array<void*> buffers;

	};

	ThreadLocalCache&	GetThreadLocalCache	();
	void*				AllocateGlobal		();
	void				DeallocateGlobal	(void* buffer);

	const USize		bufferSize;
	const USize		threadLocalCacheSize;
	USize			globalCacheSize;
	GS::SpinLock	globalCacheLock;
	GlobalCache		globalCache;	// destroyed after ThreadLocalCache

	GS::FastThreadLocal<ThreadLocalCache> threadLocalCache;

public:
	ThreadLocalMemoryPool	(USize bufferSize, USize threadLocalCacheSize, USize globalCacheSize);
	~ThreadLocalMemoryPool	();

	void*	Allocate	();
	void	Deallocate	(void* buffer);
};

}	// namespace GS

#endif //THREADLOCALMEMORYPOOL_HPP