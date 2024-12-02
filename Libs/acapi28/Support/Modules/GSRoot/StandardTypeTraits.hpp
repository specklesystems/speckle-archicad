// *********************************************************************************************************************
// Description:		GS versions of standard type traits (not all of them).
//					See https://en.cppreference.com/w/cpp/header/type_traits
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// *********************************************************************************************************************

#ifndef STANDARDTYPETRAITS_HPP
#define STANDARDTYPETRAITS_HPP

#pragma once


#include <type_traits>
#include <utility>
#include "Definitions.hpp"


namespace GS {


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Primary type categories ////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// === IsVoid ==========================================================================================================

template <class T>
constexpr bool	IsVoid = std::is_void<T>::value;


// === IsNullPointer ===================================================================================================

template <class T>
constexpr bool	IsNullPointer = std::is_null_pointer<T>::value;


// === IsIntegral ======================================================================================================

template <class T>
constexpr bool	IsIntegral = std::is_integral<T>::value;


// === IsFloatingPoint =================================================================================================

template <class T>
constexpr bool	IsFloatingPoint = std::is_floating_point<T>::value;


// === IsArray =========================================================================================================

template <class T>
constexpr bool	IsArray = std::is_array<T>::value;


// === IsEnum ==========================================================================================================

template <class T>
constexpr bool	IsEnum = std::is_enum<T>::value;


// === IsUnion =========================================================================================================

template <class T>
constexpr bool	IsUnion = std::is_union<T>::value;


// === IsClass =========================================================================================================

template <class T>
constexpr bool	IsClass = std::is_class<T>::value;


// === IsFunction ======================================================================================================

template <class T>
constexpr bool	IsFunction = std::is_function<T>::value;


// === IsPointer =======================================================================================================

template <class T>
constexpr bool	IsPointer = std::is_pointer<T>::value;


// === IsLValueReference ===============================================================================================

template <class T>
constexpr bool	IsLValueReference = std::is_lvalue_reference<T>::value;


// === IsRValueReference ===============================================================================================

template <class T>
constexpr bool	IsRValueReference = std::is_rvalue_reference<T>::value;


// === IsMemberObjectPointer ===========================================================================================

template <class T>
constexpr bool	IsMemberObjectPointer = std::is_member_object_pointer<T>::value;


// === IsMemberFunctionPointer =========================================================================================

template <class T>
constexpr bool	IsMemberFunctionPointer = std::is_member_function_pointer<T>::value;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Composite type categories //////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// === IsArithmetic ====================================================================================================

template <class T>
constexpr bool	IsArithmetic = std::is_arithmetic<T>::value;


// === IsReference =====================================================================================================

template <class T>
constexpr bool	IsReference = std::is_reference<T>::value;


// === IsMemberPointer =================================================================================================

template <class T>
constexpr bool	IsMemberPointer = std::is_member_pointer<T>::value;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Type properties ////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// === IsConst =========================================================================================================

template <class T>
constexpr bool	IsConst = std::is_const<T>::value;


// === IsVolatile ======================================================================================================

template <class T>
constexpr bool	IsVolatile = std::is_volatile<T>::value;


// === IsTrivial =======================================================================================================

template <class T>
constexpr bool	IsTrivial = std::is_trivial<T>::value;


// === IsTriviallyCopyable =============================================================================================

template <class T>
constexpr bool	IsTriviallyCopyable = std::is_trivially_copyable<T>::value;


// === IsStandardLayout ================================================================================================

template <class T>
constexpr bool	IsStandardLayout = std::is_standard_layout<T>::value;


// === IsPod ===========================================================================================================

template <class T>
constexpr bool	IsPod = std::is_pod<T>::value;


// === IsPolymorphic ===================================================================================================

template <class T>
constexpr bool	IsPolymorphic = std::is_polymorphic<T>::value;


// === IsAbstract ======================================================================================================

template <class T>
constexpr bool	IsAbstract = std::is_abstract<T>::value;


// === IsFinal =========================================================================================================

template <class T>
constexpr bool	IsFinal = std::is_final<T>::value;


// === IsSigned ========================================================================================================

template <class T>
constexpr bool	IsSigned = std::is_signed<T>::value;


// === IsUnsigned ======================================================================================================

template <class T>
constexpr bool	IsUnsigned = std::is_unsigned<T>::value;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Supported operations ///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// === IsConstructible =================================================================================================

template <class T, class... Args>
constexpr bool	IsConstructible = std::is_constructible<T, Args...>::value;


// === IsTriviallyConstructible ========================================================================================

template <class T, class... Args>
constexpr bool	IsTriviallyConstructible = std::is_trivially_constructible<T, Args...>::value;


// === IsNothrowConstructible ==========================================================================================

template <class T, class... Args>
constexpr bool	IsNothrowConstructible = std::is_nothrow_constructible_v<T, Args...>;


// === IsDefaultConstructible ==========================================================================================

template <class T>
constexpr bool	IsDefaultConstructible = std::is_default_constructible<T>::value;


// === IsTriviallyDefaultConstructible =================================================================================

template <class T>
constexpr bool	IsTriviallyDefaultConstructible = std::is_trivially_default_constructible<T>::value;


// === IsNothrowDefaultConstructible ===================================================================================

template <class T>
constexpr bool	IsNothrowDefaultConstructible = std::is_nothrow_default_constructible_v<T>;


// === IsCopyConstructible =============================================================================================

template <class T>
constexpr bool	IsCopyConstructible = std::is_copy_constructible<T>::value;


// === IsTriviallyCopyConstructible ====================================================================================

template <class T>
constexpr bool	IsTriviallyCopyConstructible = std::is_trivially_copy_constructible<T>::value;


// === IsNothrowCopyConstructible ======================================================================================

template <class T>
constexpr bool	IsNothrowCopyConstructible = std::is_nothrow_copy_constructible_v<T>;


// === IsMoveConstructible =============================================================================================

template <class T>
constexpr bool	IsMoveConstructible = std::is_move_constructible<T>::value;


// === IsTriviallyMoveConstructible ====================================================================================

template <class T>
constexpr bool	IsTriviallyMoveConstructible = std::is_trivially_move_constructible<T>::value;


// === IsNothrowMoveConstructible ====================================================================================

template <class T>
constexpr bool	IsNothrowMoveConstructible = std::is_nothrow_move_constructible_v<T>;


// === IsAssignable ====================================================================================================

template <class T, class SourceType>
constexpr bool	IsAssignable = std::is_assignable<T, SourceType>::value;


// === IsTriviallyAssignable ===========================================================================================

template <class T, class SourceType>
constexpr bool	IsTriviallyAssignable = std::is_trivially_assignable<T, SourceType>::value;


// === IsCopyAssignable ================================================================================================

template <class T>
constexpr bool	IsCopyAssignable = std::is_copy_assignable<T>::value;


// === IsTriviallyCopyAssignable =======================================================================================

template <class T>
constexpr bool	IsTriviallyCopyAssignable = std::is_trivially_copy_assignable<T>::value;


// === IsMoveAssignable ================================================================================================

template <class T>
constexpr bool	IsMoveAssignable = std::is_move_assignable<T>::value;


// === IsTriviallyMoveAssignable =======================================================================================

template <class T>
constexpr bool	IsTriviallyMoveAssignable = std::is_trivially_move_assignable<T>::value;


// === IsDestructible ==================================================================================================

template <class T>
constexpr bool	IsDestructible = std::is_destructible<T>::value;


// === IsTriviallyDestructible =========================================================================================

template <class T>
constexpr bool	IsTriviallyDestructible = std::is_trivially_destructible<T>::value;


// === HasVirtualDestructor ============================================================================================

template <class T>
constexpr bool	HasVirtualDestructor = std::has_virtual_destructor<T>::value;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Property queries ///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// === Rank ============================================================================================================

template <class Array>
constexpr UInt8		Rank = std::rank<Array>::value;


// === Extent ==========================================================================================================

template <class Array, UInt8 Dim>
constexpr UInt64	Extent = std::extent<Array, Dim>::value;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Type relationships /////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// === IsSame ==========================================================================================================

template <class T1, class T2>
constexpr bool	IsSame = std::is_same<T1, T2>::value;


// === IsBaseOf ========================================================================================================
// see TypeTraits.hpp / IsCompatible


// === IsConvertible ===================================================================================================

namespace Imp {

struct TestConvertible {
	template <class T>
	static void Accept (T);

	template <class From, class To>
	static constexpr bool	Test (decltype (Accept<To> (std::declval<From> ()))*)		{ return true; }

	template <class From, class To>
	static constexpr bool	Test (...)													{ return false; }
};

template <class From, class To>
constexpr bool	ArithmeticIsConvertible (decltype (To { std::declval<From> () })*)		{ return true; }

template <class From, class To>
constexpr bool	ArithmeticIsConvertible (...)											{ return false; }

template <class From, class To> struct EnableConversion { static constexpr bool Value = false; };
template <> struct EnableConversion<Int8,   float>  { static constexpr bool Value = true; };
template <> struct EnableConversion<UInt8,  float>  { static constexpr bool Value = true; };
template <> struct EnableConversion<Int16,  float>  { static constexpr bool Value = true; };
template <> struct EnableConversion<UInt16, float>  { static constexpr bool Value = true; };
template <> struct EnableConversion<Int8,   double> { static constexpr bool Value = true; };
template <> struct EnableConversion<UInt8,  double> { static constexpr bool Value = true; };
template <> struct EnableConversion<Int16,  double> { static constexpr bool Value = true; };
template <> struct EnableConversion<UInt16, double> { static constexpr bool Value = true; };
template <> struct EnableConversion<Int32,  double> { static constexpr bool Value = true; };
template <> struct EnableConversion<UInt32, double> { static constexpr bool Value = true; };

}


template <class From, class To>
constexpr bool IsConvertible = std::is_arithmetic<From>::value && std::is_arithmetic<To>::value ?
							   Imp::ArithmeticIsConvertible<From, To> (nullptr) || Imp::EnableConversion<std::remove_cv_t<From>, std::remove_cv_t<To>>::Value :
							   Imp::TestConvertible::Test<From, To> (nullptr);


// === IsInvocable =====================================================================================================

template <class F, class... Args>
constexpr bool IsInvocable = std::is_invocable_v<F, Args...>;


// === IsInvocableR ====================================================================================================

template <class Ret, class F, class... Args>
constexpr bool IsInvocableR = std::is_invocable_r_v<Ret, F, Args...>;


// === IsNothrowInvocable ==============================================================================================

template <class F, class... Args>
constexpr bool IsNothrowInvocable = std::is_nothrow_invocable_v<F, Args...>;


// === IsNothrowInvocableR =============================================================================================

template <class Ret, class F, class... Args>
constexpr bool IsNothrowInvocableR = std::is_nothrow_invocable_r_v<Ret, F, Args...>;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Const-volatility specifiers, References, Pointers, Sign modifiers, Arrays //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// === RemoveCV ========================================================================================================

template <class T>
using RemoveCV = typename std::remove_cv<T>::type;


// === RemoveConst =====================================================================================================

template <class T>
using RemoveConst = typename std::remove_const<T>::type;


// === RemoveVolatile ==================================================================================================

template <class T>
using RemoveVolatile = typename std::remove_volatile<T>::type;


// === AddCV ===========================================================================================================

template <class T>
using AddCV = typename std::add_cv<T>::type;


// === AddConst ========================================================================================================

template <class T>
using AddConst = typename std::add_const<T>::type;


// === AddVolatile =====================================================================================================

template <class T>
using AddVolatile = typename std::add_volatile<T>::type;


// === RemoveReference =================================================================================================

template <class T>
using RemoveReference = typename std::remove_reference<T>::type;


// === AddLValueReference ==============================================================================================

template <class T>
using AddLValueReference = typename std::add_lvalue_reference<T>::type;


// === AddRValueReference ==============================================================================================

template <class T>
using AddRValueReference = typename std::add_rvalue_reference<T>::type;


// === RemovePointer ===================================================================================================

template <class T>
using RemovePointer = typename std::remove_pointer<T>::type;


// === AddPointer ======================================================================================================

template <class T>
using AddPointer = typename std::add_pointer<T>::type;


// === MakeSigned ======================================================================================================

template <class T>
using MakeSigned = typename std::make_signed<T>::type;


// === MakeUnsigned ====================================================================================================

template <class T>
using MakeUnsigned = typename std::make_unsigned<T>::type;


// === RemoveExtent ====================================================================================================

template <class Array>
using RemoveExtent = typename std::remove_extent<Array>::type;


// === RemoveAllExtents ================================================================================================

template <class Array>
using RemoveAllExtents = typename std::remove_all_extents<Array>::type;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Miscellaneous transformations //////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// === Decay ===========================================================================================================

template <class T>
using Decay = typename std::decay<T>::type;


// === EnableIf ========================================================================================================

template <bool B, class T = void>
using EnableIf = typename std::enable_if<B, T>::type;


// === Conditional =====================================================================================================

template <bool Condition, class TrueType, class FalseType>
using Conditional = typename std::conditional<Condition, TrueType, FalseType>::type;


// === CommonType ======================================================================================================

template <class... Ts>
using CommonType = typename std::common_type<Ts...>::type;


// === UnderlyingType ==================================================================================================

template <class Enum>
using UnderlyingType = typename std::underlying_type<Enum>::type;


// === InvokeResult ====================================================================================================

template <class F, class... Args>
using InvokeResult = std::invoke_result_t<F, Args...>;


// === VoidT ===========================================================================================================

template <class... Ts>
using VoidT = std::void_t<Ts...>;


}	// namespace GS


using GS::EnableIf;


#endif
