// *********************************************************************************************************************
// Description:		Custom type traits.
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB, BIM
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


// === IsFunctor =======================================================================================================

namespace Imp {
template <class T>
using FunctorRequirement = decltype (&T::operator());
}


template <class T>
constexpr bool	IsFunctor = IsSubstitutable<Imp::FunctorRequirement, T>;


// === HasOperatorEquals ===============================================================================================

namespace Imp {
template <class LeftType, class RightType>
using OperatorEqualsRequirement = decltype (bool { std::declval<LeftType> () == std::declval<RightType> () });
}


template <class LeftType, class RightType = LeftType>
constexpr bool	HasOperatorEquals = IsSubstitutable<Imp::OperatorEqualsRequirement, LeftType, RightType>;


// === HasOperatorLess =================================================================================================

namespace Imp {
template <class T>
using OperatorLessRequirement = decltype (bool { std::declval<T> () < std::declval<T> () });
}


template <class T>
constexpr bool	HasOperatorLess = IsSubstitutable<Imp::OperatorLessRequirement, T>;


// === HasNonConstFunctionCallOperator =================================================================================

namespace ImpNonConstFunctionCallOperator {

template <class Type, class Result, class... Args>
using MethodPointer = Result (Type::*) (Args...);

template <class Type, class Result, class... Args>
using Requirement = decltype (MethodPointer<Type, Result, Args...> { &Type::operator() });

}


template <class Type, class Result, class... Args>
constexpr bool HasNonConstFunctionCallOperator = IsSubstitutable<ImpNonConstFunctionCallOperator::Requirement, Type, Result, Args...>;


// === HasConstFunctionCallOperator ====================================================================================

namespace ImpConstFunctionCallOperator {

template <class Type, class Result, class... Args>
using MethodPointer = Result (Type::*) (Args...) const;

template <class Type, class Result, class... Args>
using Requirement = decltype (MethodPointer<Type, Result, Args...> { &Type::operator() });

}


template <class Type, class Result, class... Args>
constexpr bool HasConstFunctionCallOperator = IsSubstitutable<ImpConstFunctionCallOperator::Requirement, Type, Result, Args...>;


// === HasFunctionCallOperator =========================================================================================

template <class Type, class Result, class... Args>
constexpr bool HasFunctionCallOperator = HasNonConstFunctionCallOperator<Type, Result, Args...> ||
										 HasConstFunctionCallOperator<Type, Result, Args...>;


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


}	// namespace GS


#endif
