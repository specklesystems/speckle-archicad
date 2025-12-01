#if !defined(VARIADICALLOCATOR_HPP)
#define VARIADICALLOCATOR_HPP
#pragma once

#include <type_traits>

#include "SmallObj.hpp"

// `VariadicAllocator` is able to allocate any one of the `Types` given in its parameter pack.
// It is type-safe so one can not allocate memory through it for types other than those in `Types`.
template <typename... Types>
class VariadicAllocator {
private:
	// `IndexOf` tells where is a given type inside a parameter pack.
	// It fails to compile if the given type is not in the parameter pack.
	// See also: https://stackoverflow.com/questions/17844867/find-a-type-in-a-parameter-pack
	template <typename A, typename B, typename... C>
	struct IndexOf : std::integral_constant<std::size_t, 1 + IndexOf<A, C...>::value> {
	};

	template <typename A, typename... C>
	struct IndexOf<A, A, C...> : std::integral_constant<std::size_t, 0> {
	};

	template <typename T>
	FixedAllocator& SelectAllocator ()
	{
		return allocators[IndexOf<T, Types...>::value];
	}

	template <typename T>
	void* Allocate ()
	{
		return SelectAllocator<T> ().Allocate ();
	}

	template <typename T>
	void Deallocate (void* ptr)
	{
		SelectAllocator<T> ().Deallocate (ptr);
	}

public:
	explicit VariadicAllocator (
		const AllocatorPurgePolicy			   purgePolicy		= AllocatorPurgePolicy::Auto,
		const FixedAllocator::AllocationPolicy allocationPolicy = FixedAllocator::FixedSize) :
			allocators{{sizeof (Types), purgePolicy, allocationPolicy}...}
	{
		// do nothing
	}

	template <typename T, typename... Args>
	T* Construct (Args&&... args)
	{
		void* ptr = Allocate<T> ();
		return ::new (ptr) T (std::forward<Args> (args)...);
	}

	template <typename T>
	void Destroy (T* ptr)
	{
		ptr->~T ();
		Deallocate<T> (static_cast<void*> (ptr));
	}

private:
	FixedAllocator allocators[sizeof...(Types)];
};


#endif	// VARIADICALLOCATOR_HPP
