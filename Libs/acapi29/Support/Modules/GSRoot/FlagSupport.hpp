// *********************************************************************************************************************
// Description:		By calling the macro ENABLE_FLAG_SUPPORT () for an enum type, one can use that type as flags.
//
// Module:			GSRoot
// Namespace:		Fl
// Contact person:	MB
//
// *********************************************************************************************************************


#ifndef FLAGSUPPORT_HPP
#define FLAGSUPPORT_HPP

#pragma once


#include "TypeTraits.hpp"


// === Macro to activate flag support functions for an enum ============================================================

#define ENABLE_FLAG_SUPPORT(E)																																	\
																																								\
static_assert (GS::IsEnum<E>, "ENABLE_FLAG_SUPPORT () can be used only with enum types.");																		\
																																								\
UNUSED_FUNCTION constexpr E				operator| (E leftOp, E rightOp)		{ return E (GS::UnderlyingType<E> (leftOp) | GS::UnderlyingType<E> (rightOp)); }	\
UNUSED_FUNCTION constexpr E				operator& (E leftOp, E rightOp)		{ return E (GS::UnderlyingType<E> (leftOp) & GS::UnderlyingType<E> (rightOp)); }	\
UNUSED_FUNCTION constexpr E				operator~ (E value)					{ return E (~GS::UnderlyingType<E> (value)); }										\
UNUSED_FUNCTION constexpr void			operator|= (E& target, E source)	{ target = target | source; }														\
UNUSED_FUNCTION constexpr void			operator&= (E& target, E source)	{ target = target & source; }														\


#define ENABLE_FLAG_SUPPORT_IN_CLASS(E)																															\
																																								\
static_assert (GS::IsEnum<E>, "ENABLE_FLAG_SUPPORT_IN_CLASS () can be used only with enum types.");																\
																																								\
UNUSED_FUNCTION friend constexpr E		operator| (E leftOp, E rightOp)		{ return E (GS::UnderlyingType<E> (leftOp) | GS::UnderlyingType<E> (rightOp)); }	\
UNUSED_FUNCTION friend constexpr E		operator& (E leftOp, E rightOp)		{ return E (GS::UnderlyingType<E> (leftOp) & GS::UnderlyingType<E> (rightOp)); }	\
UNUSED_FUNCTION friend constexpr E		operator~ (E value)					{ return E (~GS::UnderlyingType<E> (value)); }										\
UNUSED_FUNCTION friend constexpr void	operator|= (E& target, E source)	{ target = target | source; }														\
UNUSED_FUNCTION friend constexpr void	operator&= (E& target, E source)	{ target = target & source; }														\


// === Flag functions ==================================================================================================

namespace Fl {


template <class E>
constexpr void	TurnOn (E& target, E flagsToTurnOn)
{
	static_assert (GS::IsEnum<E>,                   "This function can be used only with enum types.");
	static_assert (GS::IsSame<decltype (~E {}), E>, "To use this function, enable flag support for 'E'.");

	target |= flagsToTurnOn;
}


template <class E>
constexpr void	TurnOff (E& target, E flagsToTurnOff)
{
	static_assert (GS::IsEnum<E>,                   "This function can be used only with enum types.");
	static_assert (GS::IsSame<decltype (~E {}), E>, "To use this function, enable flag support for 'E'.");

	target &= ~flagsToTurnOff;
}


template <class E>
constexpr void	Flip (E& target, E flagsToFlip)
{
	static_assert (GS::IsEnum<E>,                   "This function can be used only with enum types.");
	static_assert (GS::IsSame<decltype (~E {}), E>, "To use this function, enable flag support for 'E'.");

	target = E (GS::UnderlyingType<E> (target) ^ GS::UnderlyingType<E> (flagsToFlip));
}


template <class E>
constexpr bool	IsAllOn (E target, E flags)
{
	static_assert (GS::IsEnum<E>,                   "This function can be used only with enum types.");
	static_assert (GS::IsSame<decltype (~E {}), E>, "To use this function, enable flag support for 'E'.");

	return (target & flags) == flags;
}


template <class E>
constexpr bool	IsAnyOn (E target, E flags)
{
	static_assert (GS::IsEnum<E>,                   "This function can be used only with enum types.");
	static_assert (GS::IsSame<decltype (~E {}), E>, "To use this function, enable flag support for 'E'.");

	return (target & flags) != E {};
}


template <class E>
constexpr bool	IsNoneOn (E target, E flags)
{
	static_assert (GS::IsEnum<E>,                   "This function can be used only with enum types.");
	static_assert (GS::IsSame<decltype (~E {}), E>, "To use this function, enable flag support for 'E'.");

	return (target & flags) == E {};
}


template <class E>
constexpr bool	IsAllOff (E target, E flags)
{
	static_assert (GS::IsEnum<E>,                   "This function can be used only with enum types.");
	static_assert (GS::IsSame<decltype (~E {}), E>, "To use this function, enable flag support for 'E'.");

	return IsNoneOn (target, flags);
}


template <class E>
constexpr bool	IsAnyOff (E target, E flags)
{
	static_assert (GS::IsEnum<E>,                   "This function can be used only with enum types.");
	static_assert (GS::IsSame<decltype (~E {}), E>, "To use this function, enable flag support for 'E'.");

	return !IsAllOn (target, flags);
}


template <class E>
constexpr bool	IsNoneOff (E target, E flags)
{
	static_assert (GS::IsEnum<E>,                   "This function can be used only with enum types.");
	static_assert (GS::IsSame<decltype (~E {}), E>, "To use this function, enable flag support for 'E'.");

	return IsAllOn (target, flags);
}


template <class E>
constexpr bool	IsOneFlagOn (E flags)
{
	static_assert (GS::IsEnum<E>,                   "This function can be used only with enum types.");
	static_assert (GS::IsSame<decltype (~E {}), E>, "To use this function, enable flag support for 'E'.");

	const auto underlyingValue = GS::MakeUnsigned<GS::UnderlyingType<E>> (flags);
	return underlyingValue != 0 && (underlyingValue & (underlyingValue - 1)) == 0;
}


template <class E>
constexpr bool	IsOn (E target, E flag)
{
	static_assert (GS::IsEnum<E>,                   "This function can be used only with enum types.");
	static_assert (GS::IsSame<decltype (~E {}), E>, "To use this function, enable flag support for 'E'.");

	DBASSERT (IsOneFlagOn (flag));

	return IsAllOn (target, flag);
}


template <class E>
constexpr bool	IsOff (E target, E flag)
{
	static_assert (GS::IsEnum<E>,                   "This function can be used only with enum types.");
	static_assert (GS::IsSame<decltype (~E {}), E>, "To use this function, enable flag support for 'E'.");

	DBASSERT (IsOneFlagOn (flag));

	return IsAllOff (target, flag);
}


}	// namespace Fl


#endif
