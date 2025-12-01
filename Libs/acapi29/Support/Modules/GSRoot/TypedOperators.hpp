// *****************************************************************************
//
// Contact person: MB, PR
//
// *****************************************************************************

#ifndef GS_TYPEDOPERATORS_HPP
#define GS_TYPEDOPERATORS_HPP

#include "TypeTraits.hpp"


namespace GS::TypedImpl {


template<typename V, typename T, typename C>
class Typed;


template<typename T>
constexpr bool IsTyped = IsSpecializationOf<Decay<T>, Typed>;


template<typename T>
struct EffectiveTypeImpl {
	using Type = T;
};

template<typename V, typename T, typename C>
struct EffectiveTypeImpl<Typed<V, T, C>> {
	using Type = V;
};

template<typename T>
using EffectiveType = typename EffectiveTypeImpl<Decay<T>>::Type;


template<typename T, template<typename> typename... Rs>
using IsAnySubstitutable = EnableIf<(IsSubstitutable<Rs, T> || ...), bool>;


// === Assignment ======================================================================================================


template<typename T>
using AssignmentReq = decltype (EnableAssignment (std::declval<T> ()));


#define GS_TYPEDIMPL_DEFINE_ASSIGNMENT(OpName, Op)														\
																										\
template<typename LhsT, typename RhsT>																	\
using OpName##Req = decltype (OpName (std::declval<LhsT> (), std::declval<RhsT> ()));					\
																										\
																										\
template<typename V, typename T, typename C, typename RhsT, typename ResultT = OpName##Req <Typed<V, T, C>&, RhsT>>	\
constexpr Typed<V, T, C>&																							\
operator Op (Typed<V, T, C>& lhs, RhsT&& rhs)																		\
	noexcept (IsArithmetic<V> && IsArithmetic<EffectiveType<RhsT>>)										\
{																										\
	static_assert (IsSame<ResultT, Typed<V, T, C>&>, "Result of " #OpName " is not configurable.");					\
	static_assert (C::IsEmpty (),  #OpName " is not supported for types with constraints.");						\
																										\
	if constexpr (IsTyped<RhsT>) {																		\
		lhs.Get () Op static_cast<RhsT&&> (rhs).Get ();													\
	} else {																							\
		lhs.Get () Op static_cast<RhsT&&> (rhs);														\
	}																									\
																										\
	return lhs;																							\
}																										\
																										\
template<typename V, typename T, typename C, IsAnySubstitutable<Typed<V, T, C>, AssignmentReq> = true>				\
constexpr Typed<V, T, C>&																							\
operator Op (Typed<V, T, C>& lhs, Typed<V, T, C>&& rhs)																\
	noexcept (IsArithmetic<V>)																			\
{																										\
	static_assert (C::IsEmpty (),  #OpName " is not supported for types with constraints.");						\
	lhs.Get () Op static_cast<Typed<V, T, C>&&> (rhs).Get ();														\
																										\
	return lhs;																							\
}																										\
																										\
template<typename V, typename T, typename C, IsAnySubstitutable<Typed<V, T, C>, AssignmentReq> = true>				\
constexpr Typed<V, T, C>&																							\
operator Op (Typed<V, T, C>& lhs, const Typed<V, T, C>& rhs)														\
	noexcept (IsArithmetic<V>)																			\
{																										\
	static_assert (C::IsEmpty (),  #OpName " is not supported for types with constraints.");						\
	lhs.Get () Op rhs.Get ();																			\
																										\
	return lhs;																							\
}

GS_TYPEDIMPL_DEFINE_ASSIGNMENT (AdditionAssignment, +=)
GS_TYPEDIMPL_DEFINE_ASSIGNMENT (SubtractionAssignment, -=)
GS_TYPEDIMPL_DEFINE_ASSIGNMENT (MultiplicationAssignment, *=)
GS_TYPEDIMPL_DEFINE_ASSIGNMENT (DivisionAssignment, /=)
GS_TYPEDIMPL_DEFINE_ASSIGNMENT (RemainderAssignment, %=)
GS_TYPEDIMPL_DEFINE_ASSIGNMENT (BitwiseAndAssignment, &=)
GS_TYPEDIMPL_DEFINE_ASSIGNMENT (BitwiseOrAssignment, |=)
GS_TYPEDIMPL_DEFINE_ASSIGNMENT (BitwiseXorAssignment, ^=)
GS_TYPEDIMPL_DEFINE_ASSIGNMENT (BitwiseLeftShiftAssignment, <<=)
GS_TYPEDIMPL_DEFINE_ASSIGNMENT (BitwiseRightShiftAssignment, >>=)

#undef GS_TYPEDIMPL_DEFINE_ASSIGNMENT


// === Increment / Decrement ===========================================================================================


template<typename T>
using IncrementDecrementReq = decltype (EnableIncrementDecrement (std::declval<T> ()));

template<typename T>
using PreIncrementReq = decltype (AddLValueReference<T> { PreIncrement (std::declval<T> ()) });

template<typename T>
using PreDecrementReq = decltype (AddLValueReference<T> { PreDecrement (std::declval<T> ()) });

template<typename T>
using PostIncrementReq = decltype (T { PostIncrement (std::declval<T> ()) });

template<typename T>
using PostDecrementReq = decltype (T { PostDecrement (std::declval<T> ()) });

template<typename V, typename T, typename C, IsAnySubstitutable<Typed<V, T, C>, IncrementDecrementReq, PreIncrementReq> = true>
constexpr Typed<V, T, C>&
operator++ (Typed<V, T, C>& value)
	noexcept (IsArithmetic<V>)
{
	static_assert (C::IsEmpty (),  "PreIncrement is not supported for types with constraints.");
	++value.Get ();

	return value;
}

template<typename V, typename T, typename C, IsAnySubstitutable<Typed<V, T, C>, IncrementDecrementReq, PreDecrementReq> = true>
constexpr Typed<V, T, C>&
operator-- (Typed<V, T, C>& value)
	noexcept (IsArithmetic<V>)
{
	static_assert (C::IsEmpty (),  "PreDecrement is not supported for types with constraints.");
	--value.Get ();

	return value;
}


template<typename V, typename T, typename C, IsAnySubstitutable<Typed<V, T, C>, IncrementDecrementReq, PostIncrementReq> = true>
constexpr Typed<V, T, C>
operator++ (Typed<V, T, C>& value, int)
	noexcept (IsArithmetic<V>)
{
	static_assert (C::IsEmpty (),  "PostIncrement is not supported for types with constraints.");
	return Typed<V, T, C> {value.Get ()++};
}


template<typename V, typename T, typename C, IsAnySubstitutable<Typed<V, T, C>, IncrementDecrementReq, PostDecrementReq> = true>
constexpr Typed<V, T, C>
operator-- (Typed<V, T, C>& value, int)
	noexcept (IsArithmetic<V>)
{
	static_assert (C::IsEmpty (),  "PostDecrement is not supported for types with constraints.");
	return Typed<V, T, C> {value.Get ()--};
}


// === Arithmetic ======================================================================================================


template<typename T>
using ArithmeticReq = decltype (EnableArithmetic (std::declval<T> ()));


#define GS_TYPEDIMPL_DEFINE_ARITHMETIC(OpName, Op)																							\
																																			\
template<typename LhsT, typename RhsT>																										\
using OpName##Req = decltype (OpName (std::declval<LhsT> (), std::declval<RhsT> ()));														\
																																			\
																																			\
template<typename LhsT, typename RhsT, typename ResultT = OpName##Req <LhsT, RhsT>>															\
constexpr ResultT																															\
operator Op (LhsT&& lhs, RhsT&& rhs)																										\
	noexcept (IsArithmetic<EffectiveType<LhsT>> && IsArithmetic<EffectiveType<RhsT>>)														\
{																																			\
	if constexpr (IsTyped<LhsT>) {																											\
		if constexpr (IsTyped<RhsT>) {																										\
			return ResultT { static_cast<LhsT&&> (lhs).Get () Op static_cast<RhsT&&> (rhs).Get () };										\
		} else {																															\
			return ResultT { static_cast<LhsT&&> (lhs).Get () Op static_cast<RhsT&&> (rhs) };												\
		}																																	\
	} else {																																\
		if constexpr (IsTyped<RhsT>) {																										\
			return ResultT { static_cast<LhsT&&> (lhs) Op static_cast<RhsT&&> (rhs).Get () };												\
		} else {																															\
			static_assert (AlwaysFalse<ResultT>);																							\
		}																																	\
	}																																		\
}																																			\
																																			\
template<typename LhsT, typename RhsT, EnableIf<!IsSame<Decay<LhsT>, Decay<RhsT>>, int> = 0, typename ResultT = OpName##Req <RhsT, LhsT>>	\
constexpr ResultT																															\
operator Op (LhsT&& lhs, RhsT&& rhs)																										\
	noexcept (IsArithmetic<EffectiveType<LhsT>> && IsArithmetic<EffectiveType<RhsT>>)														\
{																																			\
	return ::GS::TypedImpl::operator Op <LhsT, RhsT, ResultT> (static_cast<LhsT&&> (lhs), static_cast<RhsT&&> (rhs));						\
}																																			\
																																			\
template<typename V, typename T, typename C, IsAnySubstitutable<Typed<V, T, C>, ArithmeticReq> = true>										\
constexpr Typed<V, T, C>																													\
operator Op (Typed<V, T, C>&& lhs, Typed<V, T, C>&& rhs)																					\
	noexcept (IsArithmetic<V>)																												\
{																																			\
	return Typed<V, T, C> { static_cast<Typed<V, T, C>&&> (lhs).Get () Op static_cast<Typed<V, T, C>&&> (rhs).Get () };						\
}																																			\
																																			\
template<typename V, typename T, typename C, IsAnySubstitutable<Typed<V, T, C>, ArithmeticReq> = true>										\
constexpr Typed<V, T, C>																													\
operator Op (Typed<V, T, C>&& lhs, const Typed<V, T, C>& rhs)																				\
	noexcept (IsArithmetic<V>)																												\
{																																			\
	return Typed<V, T, C> { static_cast<Typed<V, T, C>&&> (lhs).Get () Op rhs.Get () };														\
}																																			\
																																			\
template<typename V, typename T, typename C, IsAnySubstitutable<Typed<V, T, C>, ArithmeticReq> = true>										\
constexpr Typed<V, T, C>																													\
operator Op (const Typed<V, T, C>& lhs, Typed<V, T, C>&& rhs)																				\
	noexcept (IsArithmetic<V>)																												\
{																																			\
	return Typed<V, T, C> { lhs.Get () Op static_cast<Typed<V, T, C>&&> (rhs).Get () };														\
}																																			\
																																			\
template<typename V, typename T, typename C, IsAnySubstitutable<Typed<V, T, C>, ArithmeticReq> = true>										\
constexpr Typed<V, T, C>																													\
operator Op (const Typed<V, T, C>& lhs, const Typed<V, T, C>& rhs)																			\
	noexcept (IsArithmetic<V>)																												\
{																																			\
	return Typed<V, T, C> { lhs.Get () Op rhs.Get () };																						\
}

GS_TYPEDIMPL_DEFINE_ARITHMETIC (Addition, +)
GS_TYPEDIMPL_DEFINE_ARITHMETIC (Subtraction, -)
GS_TYPEDIMPL_DEFINE_ARITHMETIC (Multiplication, *)
GS_TYPEDIMPL_DEFINE_ARITHMETIC (Division, /)
GS_TYPEDIMPL_DEFINE_ARITHMETIC (Remainder, %)
GS_TYPEDIMPL_DEFINE_ARITHMETIC (BitwiseAnd, &)
GS_TYPEDIMPL_DEFINE_ARITHMETIC (BitwiseOr, |)
GS_TYPEDIMPL_DEFINE_ARITHMETIC (BitwiseXor, ^)
GS_TYPEDIMPL_DEFINE_ARITHMETIC (BitwiseLeftShift, <<)
GS_TYPEDIMPL_DEFINE_ARITHMETIC (BitwiseRightShift, >>)

#undef GS_TYPEDIMPL_DEFINE_ARITHMETIC 


template<typename T>
using UnaryMinusReq = decltype (T { UnaryMinus (std::declval<T> ()) });

template<typename T>
using BitwiseNotReq = decltype (T { BitwiseNot (std::declval<T> ()) });


template<typename V, typename T, typename C, IsAnySubstitutable<Typed<V, T, C>, ArithmeticReq, UnaryMinusReq> = true>
constexpr Typed<V, T, C>
operator- (const Typed<V, T, C>& value)
	noexcept (IsArithmetic<V>)
{
	return Typed<V, T, C> { -value.Get () };
}


template<typename V, typename T, typename C, IsAnySubstitutable<Typed<V, T, C>, ArithmeticReq, BitwiseNotReq> = true>
constexpr Typed<V, T, C>
operator- (const Typed<V, T, C>& value)
	noexcept (IsArithmetic<V>)
{
	return Typed<V, T, C> { ~value.Get () };
}


// === Logical =========================================================================================================


template<typename T>
using LogicalReq = decltype (EnableLogical (std::declval<T> ()));


#define GS_TYPEDIMPL_DEFINE_LOGICAL(OpName, Op)																								\
																																			\
template<typename LhsT, typename RhsT>																										\
using OpName##Req = decltype (OpName (std::declval<LhsT> (), std::declval<RhsT> ()));														\
																																			\
																																			\
template<typename LhsT, typename RhsT, typename ResultT = OpName##Req <LhsT, RhsT>>															\
constexpr bool																																\
operator Op (LhsT&& lhs, RhsT&& rhs)																										\
	noexcept (IsArithmetic<EffectiveType<LhsT>> && IsArithmetic<EffectiveType<RhsT>>)														\
{																																			\
	static_assert (IsSame<ResultT, bool>, "Result of " #OpName " is not configurable.");													\
																																			\
	if constexpr (IsTyped<LhsT>) {																											\
		if constexpr (IsTyped<RhsT>) {																										\
			return static_cast<LhsT&&> (lhs).Get () Op static_cast<RhsT&&> (rhs).Get ();													\
		} else {																															\
			return static_cast<LhsT&&> (lhs).Get () Op static_cast<RhsT&&> (rhs);															\
		}																																	\
	} else {																																\
		if constexpr (IsTyped<RhsT>) {																										\
			return static_cast<LhsT&&> (lhs) Op static_cast<RhsT&&> (rhs).Get ();															\
		} else {																															\
			static_assert (AlwaysFalse<ResultT>);																							\
		}																																	\
	}																																		\
}																																			\
																																			\
template<typename LhsT, typename RhsT, EnableIf<!IsSame<Decay<LhsT>, Decay<RhsT>>, int> = 0, typename ResultT = OpName##Req <RhsT, LhsT>>	\
constexpr bool																																\
operator Op (LhsT&& lhs, RhsT&& rhs)																										\
	noexcept (IsArithmetic<EffectiveType<LhsT>> && IsArithmetic<EffectiveType<RhsT>>)														\
{																																			\
	return ::GS::TypedImpl::operator Op <LhsT, RhsT, ResultT> (static_cast<LhsT&&> (lhs), static_cast<RhsT&&> (rhs));						\
}																																			\
																																			\
template<typename V, typename T, typename C, IsAnySubstitutable<Typed<V, T, C>, LogicalReq> = true>											\
constexpr bool																																\
operator Op (const Typed<V, T, C>& lhs, const Typed<V, T, C>& rhs)																			\
	noexcept (IsArithmetic<V>)																												\
{																																			\
	return lhs.Get () Op rhs.Get ();																										\
}

GS_TYPEDIMPL_DEFINE_LOGICAL (And, &&)
GS_TYPEDIMPL_DEFINE_LOGICAL (Or, ||)

#undef GS_TYPEDIMPL_DEFINE_LOGICAL


template<typename T>
using NegationReq = decltype (bool { Negation (std::declval<T> ()) });


template<typename V, typename T, typename C, IsAnySubstitutable<Typed<V, T, C>, LogicalReq, NegationReq> = true>
constexpr bool
operator! (const Typed<V, T, C>& value)
	noexcept (IsArithmetic<V>)
{
	return !value.Get ();
}


// === Comparison ======================================================================================================


template<typename T>
using ComparisonReq = decltype (EnableComparison (std::declval<T> ()));


#define GS_TYPEDIMPL_DEFINE_COMPARISON(OpName, Op)																			\
																															\
template<typename LhsT, typename RhsT>																						\
using OpName##Req = decltype (bool { OpName (std::declval<LhsT> (), std::declval<RhsT> ()) });								\
																															\
																															\
template<typename LhsT, typename RhsT, typename ResultT = OpName##Req <LhsT, RhsT>>											\
constexpr bool																												\
operator Op (const LhsT& lhs, const RhsT& rhs)																				\
	noexcept (IsArithmetic<EffectiveType<LhsT>> && IsArithmetic<EffectiveType<RhsT>>)										\
{																															\
	static_assert (IsSame<ResultT, bool>, "Result of " #OpName " is not configurable.");									\
																															\
	if constexpr (IsTyped<LhsT>) {																							\
		if constexpr (IsTyped<RhsT>) {																						\
			return lhs.Get () Op rhs.Get ();																				\
		} else {																											\
			return lhs.Get () Op rhs;																						\
		}																													\
	} else {																												\
		if constexpr (IsTyped<RhsT>) {																						\
			return lhs Op rhs.Get ();																						\
		} else {																											\
			static_assert (AlwaysFalse<ResultT>);																			\
		}																													\
	}																														\
}																															\
																															\
template<typename LhsT, typename RhsT, EnableIf<!IsSame<LhsT, RhsT>, int> = 0, typename ResultT = OpName##Req <RhsT, LhsT>>	\
constexpr bool																												\
operator Op (const LhsT& lhs, const RhsT& rhs)																				\
	noexcept (IsArithmetic<EffectiveType<LhsT>> && IsArithmetic<EffectiveType<RhsT>>)										\
{																															\
	return ::GS::TypedImpl::operator Op <LhsT, RhsT, ResultT> (lhs, rhs);													\
}																															\
																															\
template<typename V, typename T, typename C, IsAnySubstitutable<Typed<V, T, C>, ComparisonReq> = true>						\
constexpr bool																												\
operator Op (const Typed<V, T, C>& lhs, const Typed<V, T, C>& rhs)															\
	noexcept (IsArithmetic<V>)																								\
{																															\
	return lhs.Get () Op rhs.Get ();																						\
}

GS_TYPEDIMPL_DEFINE_COMPARISON (EqualTo, ==)
GS_TYPEDIMPL_DEFINE_COMPARISON (NotEqualTo, !=)
GS_TYPEDIMPL_DEFINE_COMPARISON (LessThan, <)
GS_TYPEDIMPL_DEFINE_COMPARISON (GreaterThan, >)
GS_TYPEDIMPL_DEFINE_COMPARISON (LessThanOrEqualTo, <=)
GS_TYPEDIMPL_DEFINE_COMPARISON (GreaterThanOrEqualTo, >=)

#undef GS_TYPEDIMPL_DEFINE_COMPARISON


} // namespace GS::TypedImpl


#endif /* GS_TYPEDOPERATORS_HPP */
