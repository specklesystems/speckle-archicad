// *********************************************************************************************************************
// Description:		Parameter pack traits
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB, SzoBe
//
// *********************************************************************************************************************

#ifndef PARAMETERPACKTRAITS_HPP
#define PARAMETERPACKTRAITS_HPP

#pragma once


#include "TypeTraits.hpp"


namespace GS {

// === TypeInPack ===============================================================================================

// Folding over empty parameter pack results false:
// https://eel.is/c++draft/temp.variadic#9

template<typename T, typename ... Ts>
constexpr bool TypeInPack = (std::is_same_v<T, Ts> || ...);


// === ParameterPackSize ===============================================================================================

template <class... Ts>
constexpr USize	ParameterPackSize = sizeof... (Ts);


// === SelectNthType ===================================================================================================

namespace Imp {

template <UIndex Index, class... Ts>
struct NthTypeHelper;

template <UIndex Index, class T, class... Ts>
struct NthTypeHelper<Index, T, Ts...> {
	static_assert (Index < ParameterPackSize<Ts...> + 1, "'Index' should be less than the number of types.");

	using Type = typename NthTypeHelper<Index - 1, Ts...>::Type;
};

template <class T, class... Ts>
struct NthTypeHelper<0, T, Ts...> {
	using Type = T;
};

template <UIndex Index>
struct NthTypeHelper<Index> {
	static_assert (ReturnFalse (Index), "Cannot select Nth type from an empty parameter pack.");
};

}	// namespace Imp


template <UIndex Index, class... Ts>
using SelectNthType = typename Imp::NthTypeHelper<Index, Ts...>::Type;


// === SelectFirstType =================================================================================================

template <class... Ts>
using SelectFirstType = SelectNthType<0, Ts...>;


// === SelectLastType ==================================================================================================

template <class... Ts>
using SelectLastType = SelectNthType<ParameterPackSize<Ts...> - 1, Ts...>;


// === Conjunction =====================================================================================================

template <bool... Bs>
constexpr bool	Conjunction = (Bs && ...);


// === Disjunction =====================================================================================================

template <bool... Bs>
constexpr bool	Disjunction = (Bs || ...);


// === ParameterPack ===================================================================================================

namespace Imp {

constexpr UIndex	IncrementIfFound (UIndex index)
{
	return index == MaxUIndex ? MaxUIndex : index + 1;
}

}	// namespace Imp


template <class... Ts>
struct ParameterPack;


template <class T, class... Ts>
struct ParameterPack<T, Ts...> {
	static constexpr USize	Size        = ParameterPackSize<T, Ts...>;

	template <UIndex Index>
	using					Type        = SelectNthType<Index, T, Ts...>;
	using					First       = T;
	using					Last        = SelectLastType<T, Ts...>;

	static constexpr bool	IsDecayed   = IsSame<ParameterPack<T, Ts...>, ParameterPack<Decay<T>, Decay<Ts>...>>;

	template <class Type>
	static constexpr bool	Contains    = TypeInPack<Type, T, Ts...>;

	template <class Type>
	static constexpr UIndex	FindFirst   = IsSame<Type, T> ? 0 : Imp::IncrementIfFound (ParameterPack<Ts...>::template FindFirst<Type>);			// on not found returns MaxUIndex

	static constexpr bool	IsUnique    = !ParameterPack<Ts...>::template Contains<T> && ParameterPack<Ts...>::IsUnique;

	template <template <class...> class Target>
	using					Substitute  = Target<T, Ts...>;

	template <template <class> class Converter>
	using					Convert     = ParameterPack<Converter<T>, Converter<Ts>...>;
};


template <>
struct ParameterPack<> {
	static constexpr USize	Size        = 0;

	//						Type<Index> = compilation error
	//						First       = compilation error
	//						Last        = compilation error

	static constexpr bool	IsDecayed   = true;

	template <class Type>
	static constexpr bool	Contains    = false;

	template <class Type>
	static constexpr UIndex	FindFirst   = MaxUIndex;

	static constexpr bool	IsUnique    = true;

	template <template <class...> class Target>
	using					Substitute  = Target<>;

	template <template <class> class Converter>
	using					Convert     = ParameterPack<>;
};


// === SelectNthParameter ==============================================================================================

namespace Imp {

template <UIndex Index>
struct NthParameterHelper {
	template <class T, class... Ts>
	static constexpr decltype (auto)		Get (T&&, Ts&&... ts)
	{
		static_assert (Index < ParameterPackSize<Ts...> + 1, "'Index' should be less than the number of types.");

		return NthParameterHelper<Index - 1>::Get (std::forward<Ts> (ts)...);
	}
};


template <>
struct NthParameterHelper<0> {
	template <class T, class... Ts>
	static constexpr decltype (auto)		Get (T&& t, Ts&&...)
	{
		return std::forward<T> (t);
	}
};

}	// namespace Imp


template <UIndex Index, class... Ts>
constexpr decltype (auto)		SelectNthParameter (Ts&&... ts)
{
	static_assert (ParameterPackSize<Ts...> != 0, "Cannot select Nth parameter from an empty parameter list.");

	return Imp::NthParameterHelper<Index>::Get (std::forward<Ts> (ts)...);
}


// === SelectFirstParameter ============================================================================================

template <class... Ts>
constexpr decltype (auto)		SelectFirstParameter (Ts&&... ts)
{
	return SelectNthParameter<0> (std::forward<Ts> (ts)...);
}


// === SelectLastParameter =============================================================================================

template <class... Ts>
constexpr decltype (auto)		SelectLastParameter (Ts&&... ts)
{
	return SelectNthParameter<ParameterPackSize<Ts...> - 1> (std::forward<Ts> (ts)...);
}


// === DecomposeFunction ===============================================================================================

namespace Imp {

template <class Function>
struct DecomposeFunction {
	static_assert (AlwaysFalse<Function>, "'Function' is not a function or function pointer type.");
};


template <class R, class... P>
struct DecomposeFunction<R (*) (P...)> {
	using Arguments = ParameterPack<P...>;
	using Result    = R;
};

}	// namespace Imp


template <class Function>
using DecomposeFunction = Imp::DecomposeFunction<Decay<Function>>;


// === DecomposeMethod =================================================================================================

template <class Method>
struct DecomposeMethod {
	static_assert (AlwaysFalse<Method>, "'Method' is not a method pointer type.");
};


template <class R, class C, class... P>
struct DecomposeMethod<R (C::*) (P...)> {
	using Class     = C;
	using Arguments = ParameterPack<P...>;
	using Result    = R;
	static constexpr bool IsConst = false;
};


template <class R, class C, class... P>
struct DecomposeMethod<R (C::*) (P...) const> {
	using Class     = C;
	using Arguments = ParameterPack<P...>;
	using Result    = R;
	static constexpr bool IsConst = true;
};


}	// namespace GS


#endif
