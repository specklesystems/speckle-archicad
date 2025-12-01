#if !defined(FASTTHREADLOCAL_HPP)
#define FASTTHREADLOCAL_HPP
#pragma once

#include "ThreadLocal.hpp"
#include "ThreadSpecificStorage.hpp"

namespace GS {

template <typename T, typename Initializator = typename GS::ThreadLocal<T>::DefaultInitializator>
class FastThreadLocal {
public:
	FastThreadLocal ();
	virtual ~FastThreadLocal ();

	T&		 Get ();
	const T& Get () const;
	void	 Set (const T& value);

private:
	GS::ThreadLocal<T, Initializator>	threadLocalValue;
	GS::ThreadSpecificStorage<T*>		ptrToThreadLocal;
};


template <typename T, typename Initializator>
FastThreadLocal<T, Initializator>::FastThreadLocal () : threadLocalValue (), ptrToThreadLocal ()
{
	// do nothing
}


template <typename T, typename Initializator>
FastThreadLocal<T, Initializator>::~FastThreadLocal ()
{
	ptrToThreadLocal.Set (nullptr);
}


template <typename T, typename Initializator>
T& FastThreadLocal<T, Initializator>::Get ()
{
	T* ptr = ptrToThreadLocal.Get ();
	if (ptr != nullptr) {
		return *ptr;
	}

	ptr = &threadLocalValue.Get ();
	ptrToThreadLocal.Set (ptr);
	return *ptr;
}

template <typename T, typename Initializator>
const T& FastThreadLocal<T, Initializator>::Get () const
{
	return const_cast<FastThreadLocal<T, Initializator>*> (this)->Get ();
}


template <typename T, typename Initializator>
void FastThreadLocal<T, Initializator>::Set (const T& value)
{
	threadLocalValue.Set (value);
	// `value` is assigned with operator= and its address remains the same
	// so there is no need to update `ptrToThreadLocal`
	DBASSERT (ptrToThreadLocal.Get () == &threadLocalValue.Get ());
}

}	// namespace GS

#endif	// FASTTHREADLOCAL_HPP
