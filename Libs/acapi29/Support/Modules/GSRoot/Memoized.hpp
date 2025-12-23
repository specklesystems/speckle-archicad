
// *****************************************************************************
//
//                             class Memoized
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SzoBe
//
//
//
// *****************************************************************************


#if !defined MEMOIZED_HPP
#define MEMOIZED_HPP

#pragma once

#include "MemoizedInfiniteCache.hpp"
#include <tuple>

namespace GS {

namespace ImpMemoized { template <class... Types> struct Key; }

// === class Memoized ==================================================================================================

template <class CalculateFunction, template <class, class> class Cache = MemoizedInfiniteCache>
class Memoized {
private:
	using FunctionType = DecomposeFunction<CalculateFunction>;
	using Key		   = typename FunctionType::Arguments::template Convert<Decay>::template Substitute<ImpMemoized::Key>;
	using Value		   = typename FunctionType::Result;

	static constexpr USize ArgumentCount = FunctionType::Arguments::Size;
	static_assert (ArgumentCount > 0, "Argument count must be greater than zero!");

	mutable Cache<Key, Value>			cache;
	std::function<CalculateFunction>	function;

public:
	explicit Memoized (const std::function<CalculateFunction>& function);
	explicit Memoized (std::function<CalculateFunction>&& function);

	template <class... Args>
	const Value& Get (const Args&... args) const;

	template <class... Args>
	const Value& operator() (const Args&... args) const;

	Cache<Key, Value>& GetCache ();
	const Cache<Key, Value>& GetCache () const;
};


// === class MemoizedEmptyCache ========================================================================================

template <class Key, class Value>
class MemoizedEmptyCache;


// === class Memoized specialized for EmptyCache =======================================================================

template <class CalculateFunction>
class Memoized<CalculateFunction, MemoizedEmptyCache> {
private:
	std::function<CalculateFunction> function;

	using Value = typename DecomposeFunction<CalculateFunction>::Result;
public:
	explicit Memoized (const std::function<CalculateFunction>& function);
	explicit Memoized (std::function<CalculateFunction>&& function);

	template <class... Args>
	Value Get (const Args&... args) const;

	template <class... Args>
	Value operator() (const Args&... args) const;
};


// === class ImpMemoized::Key ==========================================================================================

namespace ImpMemoized {

template <class... Types>
struct Key {
	static_assert (ParameterPack<Types...>::IsDecayed, "Types... must be decayed");

	std::tuple<Types...> values;

	Key () = default;
	Key (const Key&) = default;
	Key (Key&&) = default;
	Key (const Types&... values);

	Key& operator= (const Key&) = default;
	Key& operator= (Key&&) = default;

	template <std::size_t... I>
	ULong	GenerateHashValue (const std::index_sequence<I...>&) const;
	ULong	GenerateHashValue () const;

	bool operator== (const Key& rightOp) const;
	bool operator!= (const Key& rightOp) const;
	bool operator< (const Key& rightOp) const;
};

} // namespace ImpMemoized


// === Implementation of Memoized ======================================================================================

template <class CalculateFunction, template <class, class> class Cache>
Memoized<CalculateFunction, Cache>::Memoized (const std::function<CalculateFunction>& function) :
	function (function)
{
}


template <class CalculateFunction, template <class, class> class Cache>
Memoized<CalculateFunction, Cache>::Memoized (std::function<CalculateFunction>&& function) :
	function (std::move (function))
{
}


template <class CalculateFunction, template <class, class> class Cache>
template <class... Args>
const typename DecomposeFunction<CalculateFunction>::Result&	Memoized<CalculateFunction, Cache>::Get (const Args&... args) const
{
	constexpr USize IncomingArgumentCount = ParameterPackSize<Args...>;
	static_assert (ArgumentCount == IncomingArgumentCount, "Argument count must be equal to argument count of the Memoized function!");

	Key key (args...);
	const Value* value = cache.Get (key);
	if (value != nullptr)
		return *value;

	return *cache.Add (key, function (args...));
}


template <class CalculateFunction, template <class, class> class Cache>
template <class... Args>
const typename DecomposeFunction<CalculateFunction>::Result&	Memoized<CalculateFunction, Cache>::operator() (const Args&... args) const
{
	constexpr USize IncomingArgumentCount = ParameterPackSize<Args...>;
	static_assert (ArgumentCount == IncomingArgumentCount, "Argument count must be equal to argument count of the Memoized function!");

	return Get<Args...> (args...);
}


template <class CalculateFunction, template <class, class> class Cache>
Cache<typename Memoized<CalculateFunction, Cache>::Key, typename DecomposeFunction<CalculateFunction>::Result>&		Memoized<CalculateFunction, Cache>::GetCache ()
{
	return cache;
}


template <class CalculateFunction, template <class, class> class Cache>
const Cache<typename Memoized<CalculateFunction, Cache>::Key, typename DecomposeFunction<CalculateFunction>::Result>&	Memoized<CalculateFunction, Cache>::GetCache () const
{
	return cache;
}


// === Implementation of Memoized specialized for EmptyCache ===========================================================

template <class CalculateFunction>
Memoized<CalculateFunction, MemoizedEmptyCache>::Memoized (const std::function<CalculateFunction>& function) :
	function (function)
{
}


template <class CalculateFunction>
Memoized<CalculateFunction, MemoizedEmptyCache>::Memoized (std::function<CalculateFunction>&& function) :
	function (std::move (function))
{
}


template <class CalculateFunction>
template <class... Args>
typename Memoized<CalculateFunction, MemoizedEmptyCache>::Value		Memoized<CalculateFunction, MemoizedEmptyCache>::Get (const Args&... args) const
{
	return function (args...);
}


template <class CalculateFunction>
template <class... Args>
typename Memoized<CalculateFunction, MemoizedEmptyCache>::Value		Memoized<CalculateFunction, MemoizedEmptyCache>::operator()(const Args&... args) const
{
	return function (args...);
}


// === Implementation of ImpMemoized::Key ==============================================================================

namespace ImpMemoized {

template <class... Types>
Key<Types...>::Key (const Types&... values) :
	values (values...)
{
}


template <class... Types>
template <std::size_t... I>
ULong	Key<Types...>::GenerateHashValue (const std::index_sequence<I...>&) const
{
	return GS::CalculateHashValue (std::get<I> (values)...);
}


template <class... Types>
ULong	Key<Types...>::GenerateHashValue () const
{
	return GenerateHashValue (std::index_sequence_for<Types...> {});
}


template <class... Types>
bool	Key<Types...>::operator==(const Key& rightOp) const
{
	return values == rightOp.values;
}


template <class... Types>
bool	Key<Types...>::operator!= (const Key& rightOp) const
{
	return values != rightOp.values;
}


template <class... Types>
bool	Key<Types...>::operator< (const Key& rightOp) const
{
	return values < rightOp.values;
}

} // namespace ImpMemoized

} // namespace GS


#endif
