#ifndef SMALLOBJ_HPP
#define SMALLOBJ_HPP

#include "GSRootExport.hpp"
#include "ThreadingDebug.hpp"

class FixedAllocator;

enum class AllocatorPurgePolicy : GS::UInt8 { Manual, Auto };


class GSROOT_DLL_EXPORT SmallObjAllocator: private NonThreadSafeClass
{
	friend class FixedAllocator;

private:
	FixedAllocator**	 data;
	size_t				 maxObjectSize;
	AllocatorPurgePolicy purgePolicy;

private:
	AllocatorPurgePolicy GetPurgePolicy () const;
	void				 SetPurgePolicy (const AllocatorPurgePolicy newPolicy);

public:
	class GSROOT_DLL_EXPORT [[nodiscard]] ManualPurgeScope {
	public:
		explicit ManualPurgeScope (SmallObjAllocator& allocator);
		~ManualPurgeScope ();

	private:
		SmallObjAllocator&   allocator;
		AllocatorPurgePolicy originalPurgePolicy;
	};
	
	SmallObjAllocator (size_t				maxObjectSize,
					   AllocatorPurgePolicy purgePolicy = AllocatorPurgePolicy::Auto,
					   bool					threadSafe  = false);
	~SmallObjAllocator ();

	SmallObjAllocator (const SmallObjAllocator&)			= delete;
	SmallObjAllocator (SmallObjAllocator&&)					= delete;
	SmallObjAllocator& operator= (const SmallObjAllocator&) = delete;
	SmallObjAllocator& operator= (SmallObjAllocator&&)		= delete;

	void*		Allocate (size_t numBytes);
	static void	Deallocate (void* p);

	void*		AllocateAligned (size_t numBytes, size_t alignment);
	static void	DeallocateAligned (void* p);

	void		Purge ();

	void		LeaveThread ();

	size_t		GetSize () const;
};


class GSROOT_DLL_EXPORT FixedAllocator: public NonThreadSafeClass
{
public:
	class Page;

	enum AllocationPolicy {
		FixedSize,
		Quadratic,
		Exponential
	};

private:
	friend class SmallObjAllocator;
	friend class ThreadSafeFixedAllocator;

	const size_t		 recordSize;
	size_t				 allocatedSize;
	Page*				 firstPageWithSpaceLeft;
	Page*				 firstEmptyPage;
	AllocatorPurgePolicy purgePolicy;
	bool				 threadSafe;
	SmallObjAllocator*   parent;
	UInt32				 pageCount;
	AllocationPolicy	 allocationPolicy;


private:
	void   DeletePage (Page* page);
	void   Deallocate (Page* page, void* p);
	void   IncreaseSize ();
	void   DecreaseSize ();
	size_t GetSize () const;

	virtual void*	AllocateFromSmallObjAllocator ();
	virtual void	DeallocateFromSmallObjAllocator (Page* page, void* p);

	AllocatorPurgePolicy GetPurgePolicy () const;
	virtual void		 SetPurgePolicy (const AllocatorPurgePolicy newPolicy);

	FixedAllocator (size_t				 recordSize,
					AllocatorPurgePolicy purgePolicy,
					bool				 threadSafe,
					SmallObjAllocator*   parent);

public:
	FixedAllocator (size_t				 recordSize,
					AllocatorPurgePolicy purgePolicy	  = AllocatorPurgePolicy::Auto,
					AllocationPolicy	 allocationPolicy = FixedSize);
	virtual ~FixedAllocator ();

	FixedAllocator (const FixedAllocator&)				= delete;
	FixedAllocator (FixedAllocator&&)					= delete;
	FixedAllocator& operator= (const FixedAllocator&)	= delete;
	FixedAllocator& operator= (FixedAllocator&&)		= delete;

	void*			Allocate ();

	static void		Deallocate (void* p);

	virtual void	Purge ();

	class GSROOT_DLL_EXPORT ManualPurgeScope {
	public:
		explicit ManualPurgeScope (FixedAllocator& allocator);
		~ManualPurgeScope ();

	private:
		FixedAllocator&			allocator;
		AllocatorPurgePolicy	originalPurgePolicy;
	};
};


template <typename Type>
struct SubAllocatedData: public Type {
public:
	void*	operator new (size_t /*size*/, FixedAllocator& allocator)	{ return allocator.Allocate (); }
	void	operator delete (void* p)									{ return FixedAllocator::Deallocate (p); }
	void	operator delete (void* p, FixedAllocator& /*allocator*/)	{ return FixedAllocator::Deallocate (p); }

	template <typename... Args>
	SubAllocatedData (Args&&... args):
		Type (std::forward<Args> (args)...)
	{
	}
};


extern GSROOT_DLL_EXPORT SmallObjAllocator	threadSafeGlobalObjPool;

#endif // SMALLOBJ_HPP
