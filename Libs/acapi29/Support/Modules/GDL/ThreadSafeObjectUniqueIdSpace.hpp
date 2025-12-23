#if !defined GDL_RUNTIMESTRINGIDSPACE_HPP
#define GDL_RUNTIMESTRINGIDSPACE_HPP

#include "GDLExport.h"
#include "SpinLock.hpp"
#include "Owner.hpp"
#include "String.hpp"
#include "Array.hpp"
#include "Optional.hpp"
#include "HashTable.hpp"
#include "Guard.hpp"
#include "ThreadLocal.hpp"
#include "GDLObjectUniqueId.hpp"

namespace GDL
{


template <typename T>
class HashableFlyweightReference
{
public:
	HashableFlyweightReference (const T* objIn) :
		hashValue (GS::CalculateHashValue (*objIn)),
		obj (objIn)
	{
	}

	bool operator== (const HashableFlyweightReference& other) const
	{
		return hashValue == other.hashValue && *obj == *other.obj;
	}

	ULong GenerateHashValue () const
	{
		return hashValue;
	}

	const T&	GetReferredObject () const
	{
		return *obj;
	}
	
private:
	ULong				hashValue;
	const T*			obj;
};


template <typename T>
class SingleThreadObjectUniqueIdCache
{
public:
	class SharedContainer
	{
	public:
		void SynchronizedAccess (const std::function<void (GS::Array<GS::Owner<T>>&)>& fn)
		{
			synchronized (lock) {
				fn (prototypes);
			}
		}

	private:
		GS::SpinLock				lock;
		GS::Array<GS::Owner<T>>		prototypes;
	};

	void SetAssociatedContainer (SharedContainer& container)
	{
		if (DBVERIFY (associatedContainer == nullptr || associatedContainer == &container)) {
			associatedContainer = &container;
		}
	}

	GS::Optional<RuntimeUniqueId<T>> TryGetUniqueIdOfValueWithoutCacheSynchronization (const T& obj)
	{
		HashableFlyweightReference<T> objectWrapper (&obj);

		RuntimeUniqueId<T> index;
		if (objectToUniqueId.Get (objectWrapper, &index)) {
			return index;
		} else {
			return GS::NoValue;
		}
	}

	RuntimeUniqueId<T>	ValueToUniqueId (const T& obj)
	{
		HashableFlyweightReference<T> objectWrapper (&obj);
		GS::Optional<RuntimeUniqueId<T>> index;
		
		index = TryGetUniqueIdOfValueWithoutCacheSynchronization (obj);
		if (index.HasValue ()) {
			return *index;
		}
		
		Synchronize (&obj);
		
		index = TryGetUniqueIdOfValueWithoutCacheSynchronization (obj);
		if (index.HasValue ()) {
			return *index;
		}

		DBBREAK_STR ("The string should have been added during synchronization");
		return RuntimeUniqueId<T> ();
	}

	const T&	UniqueIdToValue (RuntimeUniqueId<T> index)
	{
		if (index.index >= uniqueIdToObject.GetSize ()) {
			Synchronize (nullptr);
		}

		DBASSERT (index.index < uniqueIdToObject.GetSize ());
		DBASSERT (&uniqueIdToObject[index.index].GetReferredObject () == index.referredObjectForDebug);
		return uniqueIdToObject[index.index].GetReferredObject ();
	}


private:
	void Synchronize (const T* newValue)
	{
		if (DBERROR (associatedContainer == nullptr)) {
			return;
		}

		associatedContainer->SynchronizedAccess ([&] (GS::Array<GS::Owner<T>>& containerEntries) {
			AppendValuesFromContainerIncrementally (containerEntries);

			if (newValue != nullptr) {
				EnsureValueExistsInContainer (containerEntries, *newValue);
			}
		});
	}

	void AppendValuesFromContainerIncrementally (GS::Array<GS::Owner<T>>& containerEntries)
	{
		UInt32 i = uniqueIdToObject.GetSize ();
		while (i < containerEntries.GetSize ()) {
			HashableFlyweightReference<T> stringWrapper (containerEntries[i].Get ());
			uniqueIdToObject.Push (stringWrapper);
			objectToUniqueId.Add (stringWrapper, CreateUniqueId (uniqueIdToObject.GetLastIndex ()));
			i++;
		}
	}

	void EnsureValueExistsInContainer (GS::Array<GS::Owner<T>>& containerEntries, const T& newValue)
	{
		DBASSERT_STR (uniqueIdToObject.GetSize () == containerEntries.GetSize (), "The cache must already be synchronized");

		HashableFlyweightReference<T> toFindWrapper (&newValue);
		if (!objectToUniqueId.ContainsKey (toFindWrapper)) {
			containerEntries.Push (GS::Pass (new T (newValue)));

			AppendValuesFromContainerIncrementally (containerEntries);
		}
	}

	RuntimeUniqueId<T> CreateUniqueId (UInt32 index) 
	{
#ifdef CHECKED_VERSION
		return { index, &uniqueIdToObject[index].GetReferredObject () };
#else
		return { index };
#endif
	}

	GS::Array<HashableFlyweightReference<T>>							uniqueIdToObject;
	GS::HashTable<HashableFlyweightReference<T>,RuntimeUniqueId<T>>		objectToUniqueId;

	SharedContainer*		associatedContainer = nullptr;
};



template <typename T>
class ThreadSafeObjectUniqueIdSpace
{
public:
	SingleThreadObjectUniqueIdCache<T>& GetCache ()
	{
		SingleThreadObjectUniqueIdCache<T>& cacheOfThread = threadLocalCache.Get ();
		cacheOfThread.SetAssociatedContainer (centralContainer);
		return cacheOfThread;
	}

private:
	using ContainerType = typename SingleThreadObjectUniqueIdCache<T>::SharedContainer;
	ContainerType											centralContainer;
	GS::ThreadLocal<SingleThreadObjectUniqueIdCache<T>>		threadLocalCache;
};

}


#endif