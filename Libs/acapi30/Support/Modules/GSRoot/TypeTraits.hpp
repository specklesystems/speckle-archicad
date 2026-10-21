// *********************************************************************************************************************
// Description:		Custom type traits.
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// *********************************************************************************************************************

#ifndef TYPETRAITS_HPP
#define TYPETRAITS_HPP

#pragma once


#include "StandardTypeTraits.hpp"


namespace GS {


// === IsDecayed =======================================================================================================

template <class T>
constexpr bool	IsDecayed = IsSame<T, Decay<T>>;


// === IsCompatible ====================================================================================================

template <class From, class To>
constexpr bool	IsCompatible = std::is_base_of<To, From>::value;			// To is base of From, From is a To


// === AreRelated ======================================================================================================

template <class T1, class T2>
constexpr bool	AreRelated = std::is_base_of<T1, T2>::value || std::is_base_of<T2, T1>::value;


// === DontDeduce ======================================================================================================

namespace Imp {

template <class T>
struct DontDeduce {
	using Type = T;
};

}

template <class T>
using DontDeduce = typename Imp::DontDeduce<T>::Type;


// === IsSubstitutable, SubstituteOr, SubstituteOrNoneSuch =============================================================

namespace Imp {

template <class Default, class AlwaysVoid, template <class...> class Op, class... Args>
struct IsSubstitutableDetector {
	static constexpr bool Value	= false;
	using Type					= Default;
};

template <class Default, template <class...> class Op, class... Args>
struct IsSubstitutableDetector<Default, VoidT<Op<Args...>>, Op, Args...> {
	static constexpr bool Value	= true;
	using Type					= Op<Args...>;
};

struct NoneSuch final {
	NoneSuch () = delete;
};

}	// namespace Imp


template <template <class...> class Op, class... Args>
constexpr bool	IsSubstitutable = Imp::IsSubstitutableDetector<void, void, Op, Args...>::Value;


template <class Default, template <class...> class Op, class... Args>
using SubstituteOr = typename Imp::IsSubstitutableDetector<Default, void, Op, Args...>::Type;


template <template <class...> class Op, class... Args>
using SubstituteOrNoneSuch = SubstituteOr<Imp::NoneSuch, Op, Args...>;


// === HasMemberNonConstOperatorEquals =================================================================================


namespace ImpHasNonConstOperatorEqualsMethod {

struct Helper {
	template <class T>
	static void				Accept (bool (T::*) (T));

	template <class T>
	static void				Accept (bool (T::*) (const T&));

	template <class T>
	static constexpr bool	Test (decltype (Accept (&T::operator==))*)		{ return true; }

	template <class T>
	static constexpr bool	Test (...)										{ return false; }
};

}


template <class Type>
constexpr bool	HasNonConstOperatorEqualsMethod = ImpHasNonConstOperatorEqualsMethod::Helper::Test<Type> (nullptr);


// === HasOperatorEquals ===============================================================================================

namespace Imp {
template <class LeftType, class RightType>
using OperatorEqualsRequirement = decltype (bool { std::declval<LeftType> () == std::declval<RightType> () });
}


template <class LeftType, class RightType = LeftType>
constexpr bool	HasOperatorEquals = IsSubstitutable<Imp::OperatorEqualsRequirement, AddConst<LeftType>, AddConst<RightType>>;


// === HasMemberNonConstOperatorLess ===================================================================================


namespace ImpHasNonConstOperatorLessMethod {

struct Helper {
	template <class T>
	static void				Accept (bool (T::*) (T));

	template <class T>
	static void				Accept (bool (T::*) (const T&));

	template <class T>
	static constexpr bool	Test (decltype (Accept (&T::operator<))*)		{ return true; }

	template <class T>
	static constexpr bool	Test (...)										{ return false; }
};

}


template <class Type>
constexpr bool	HasNonConstOperatorLessMethod = ImpHasNonConstOperatorLessMethod::Helper::Test<Type> (nullptr);


// === HasOperatorLess =================================================================================================

namespace Imp {
template <class T>
using OperatorLessRequirement = decltype (bool { std::declval<T> () < std::declval<T> () });
}


template <class T>
constexpr bool	HasOperatorLess = IsSubstitutable<Imp::OperatorLessRequirement, AddConst<T>>;


// === FirstArgumentType ===============================================================================================

namespace Imp {

template <class Ret, class Arg, class... Rest>
Arg		GetFirstArgument (Ret (*) (Arg, Rest...));

template <class Ret, class T, class Arg, class... Rest>
Arg		GetFirstArgument (Ret (T::*) (Arg, Rest...));

template <class Ret, class T, class Arg, class... Rest>
Arg		GetFirstArgument (Ret (T::*) (Arg, Rest...) const);

template <class T>
decltype (GetFirstArgument (&T::operator()))	GetFirstArgument (T);

}


template <class Function>
using FirstArgumentType = decltype (Imp::GetFirstArgument (std::declval<Function> ()));


// === DecayedFirstArgumentType ========================================================================================

namespace Imp {

template <class F>
auto	GetDecayedFirstArgumentType () -> Decay<typename F::DecayedFirstArgumentType>;


template <class F>
auto	GetDecayedFirstArgumentType () -> Decay<FirstArgumentType<F>>;

}


template <class Function>
using DecayedFirstArgumentType = decltype (Imp::GetDecayedFirstArgumentType<Function> ());


// === ResultType ======================================================================================================

namespace Imp {

template <class Ret, class... Rest>
Ret		GetReturnType (Ret (*) (Rest...));

template <class Ret, class T, class... Rest>
Ret		GetReturnType (Ret (T::*) (Rest...));

template <class Ret, class T, class... Rest>
Ret		GetReturnType (Ret (T::*) (Rest...) const);

template <class T>
decltype (GetReturnType (&T::operator()))	GetReturnType (T);

}

template <class Function>
using ResultType = decltype (Imp::GetReturnType (std::declval<Function> ()));


// === EnumType and NotEnumType ========================================================================================

template <class T>
using EnumType = EnableIf<IsEnum<T>, bool>;

template <class T>
using NotEnumType = EnableIf<!IsEnum<T>, bool>;


// === IsSpecializationOf ==============================================================================================

namespace Imp {

template<typename T, template<typename...> class U>
struct IsSpecializationOf {
	static constexpr bool Value = false;
};

template<template<typename...> class T, typename... Ts>
struct IsSpecializationOf<T<Ts...>, T> {
	static constexpr bool Value = true;
};

}

template<typename T, template<typename...> class U>
constexpr bool IsSpecializationOf = Imp::IsSpecializationOf<T, U>::Value;


}	// namespace GS


#endif
