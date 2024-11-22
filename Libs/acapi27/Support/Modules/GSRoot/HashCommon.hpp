// *********************************************************************************************************************
//
// Description:		Utilities for the hash based containers and algorithms
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// *********************************************************************************************************************


#ifndef HASHCOMMON_HPP
#define HASHCOMMON_HPP

#include "TypeTraits.hpp"

// from STL
#include <cstddef>


namespace GS {


namespace Imp {


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// Predefined hash value generation functions //////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Predefined {


template <class Type, EnableIf<IsIntegral<Type> && sizeof (Type) <= 4>* = nullptr>
inline ULong	GenerateHashValue (Type value)
{
	return value;
}


template <class Type, EnableIf<IsIntegral<Type> && sizeof (Type) >= 5>* = nullptr>
inline ULong	GenerateHashValue (Type value)
{
	static_assert (sizeof (Type) == 8, "No predefined hash value generation is implemented for an integral type of this size.");

	return static_cast<ULong> (((UInt64 (value) >> 32) & 0xFFFFFFFFUL) + (UInt64 (value) & 0xFFFFFFFFUL));
}


inline ULong	GenerateHashValue (float value)
{
	static_assert (sizeof (float) == sizeof (UInt32), "Wrong cast.");

	if (value == 0)    // 0 has two different forms: -0 and +0
		value = 0;
	return Predefined::GenerateHashValue (reinterpret_cast<UInt32&> (value));
}


inline ULong	GenerateHashValue (double value)
{
	static_assert (sizeof (double) == sizeof (UInt64), "Wrong cast.");

	if (value == 0)    // 0 has two different forms: -0 and +0
		value = 0;
	return Predefined::GenerateHashValue (reinterpret_cast<UInt64&> (value));
}


inline ULong	GenerateHashValue (long double value)
{
	return Predefined::GenerateHashValue (static_cast<double> (value));
}


template <class Type>
inline ULong	GenerateHashValue (const Type* ptr)
{
	return Predefined::GenerateHashValue (reinterpret_cast<UIntPtr> (ptr));
}


template <class Enum, EnableIf<IsEnum<Enum>>* = nullptr>
inline ULong	GenerateHashValue (Enum value)
{
	return Predefined::GenerateHashValue (static_cast<UnderlyingType<Enum>> (value));
}


}	// namespace Predefined


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// Type traits /////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// === HasPredefinedGenerateHashValue ==================================================================================

template <class Type>
constexpr bool  HasPredefinedGenerateHashValue = IsArithmetic<Type> || IsPointer<Type> || IsEnum<Type>;


// === HasGenerateHashValueMethod ======================================================================================

template <class Type>
constexpr bool  DetectGenerateHashValueMethod (decltype (ULong { std::declval<const Type> ().GenerateHashValue () })*)		{ return true; }

template <class Type>
constexpr bool  DetectGenerateHashValueMethod (...)																			{ return false; }

template <class Type>
constexpr bool  HasGenerateHashValueMethod = DetectGenerateHashValueMethod<Type> (nullptr);


// === HasGenerateHashValueFunction ====================================================================================

void	GenerateHashValue ();

// This type trait uses ADL. Ordinary lookup finds only the above 'void Imp::GenerateHashValue ()', which hides the name in outer namespaces.

template <class Type>
constexpr bool  DetectGenerateHashValueFunction (decltype (ULong { GenerateHashValue (std::declval<const Type> ()) })*)		{ return true; }

template <class Type>
constexpr bool  DetectGenerateHashValueFunction (...)																		{ return false; }

template <class Type>
constexpr bool  HasGenerateHashValueFunction = DetectGenerateHashValueFunction<Type> (nullptr);


// === struct GenerateHashValueDetector ================================================================================

template <class Type>
struct GenerateHashValueDetector {
	static_assert (IsDecayed<Type>, "'Type' should be decayed.");
	static_assert (!IsMemberPointer<Type>, "'Type' should not be a member pointer.");

	static_assert (!HasGenerateHashValueMethod<Type> || !HasGenerateHashValueFunction<Type>,
				   "'Type' has ambiguous GenerateHashValue (). Could be Type::GenerateHashValue () method or GenerateHashValue (const Type&) function.");

	static constexpr bool Value = HasPredefinedGenerateHashValue<Type> ||
								  HasGenerateHashValueMethod<Type>     ||
								  HasGenerateHashValueFunction<Type>;
};


}   // namespace Imp


// === HasGenerateHashValue ============================================================================================

template <class Type>
constexpr bool  HasGenerateHashValue = Imp::GenerateHashValueDetector<Type>::Value;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// Generic hash value generation functions /////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// These functions call Type::GenerateHashValue () method or GenerateHashValue (const Type&) function, whichever exists,
// and will detect ambiguity if both exist.


namespace Imp {


template <class Type, EnableIf<HasPredefinedGenerateHashValue<Type>>* = nullptr>
inline ULong	CalculateHashValue (const Type& value)
{
	return Predefined::GenerateHashValue (value);		// Qualified lookup in namespace 'Predefined'.
}


template <class Type, EnableIf<!HasPredefinedGenerateHashValue<Type> && HasGenerateHashValueMethod<Type> && !HasGenerateHashValueFunction<Type>>* = nullptr>
inline ULong	CalculateHashValue (const Type& value)
{
	return value.GenerateHashValue ();
}


template <class Type, EnableIf<!HasPredefinedGenerateHashValue<Type> && !HasGenerateHashValueMethod<Type> && HasGenerateHashValueFunction<Type>>* = nullptr>
inline ULong	CalculateHashValue (const Type& value)
{
	return GenerateHashValue (value);					// ADL. Ordinary lookup finds only the above 'void Imp::GenerateHashValue ()', which hides the name in outer namespaces.
}


template <class Type, EnableIf<!HasPredefinedGenerateHashValue<Type> && !HasGenerateHashValueMethod<Type> && !HasGenerateHashValueFunction<Type>>* = nullptr>
inline ULong	CalculateHashValue (const Type& /*value*/)
{
	static_assert (AlwaysFalse<Type>, "'Type' has no GenerateHashValue ().");
}


template <class Type, EnableIf<!HasPredefinedGenerateHashValue<Type> && HasGenerateHashValueMethod<Type> && HasGenerateHashValueFunction<Type>>* = nullptr>
inline ULong	CalculateHashValue (const Type& /*value*/)
{
	static_assert (AlwaysFalse<Type>, "'Type' has ambiguous GenerateHashValue (). Could be Type::GenerateHashValue () method or GenerateHashValue (const Type&) function.");
}


}   // namespace Imp


// === CalculateHashValue () ===========================================================================================

template <class Type>
inline ULong	CalculateHashValue (const Type& value)
{
	return Imp::CalculateHashValue (value);
}


template <class Type, class... Types>
inline ULong	CalculateHashValue (const Type& value, const Types&... values)
{
	return GS::CalculateHashValue (value) + 65599 * GS::CalculateHashValue (values...);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// Common functions for hash containers ////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GSROOT_DLL_EXPORT USize		GetNextHashCapacity     (USize oldCapacity);
GSROOT_DLL_EXPORT USize		GetPreviousHashCapacity (USize oldCapacity);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// Helper functions for hash value generation //////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GSROOT_DLL_EXPORT ULong		GenerateCStringHashValue (const char* cStr);
GSROOT_DLL_EXPORT ULong		GenerateBinaryHashValue (const std::byte* data, USize dataSize);


template <class Type>
inline ULong	GenerateBinaryHashValue (const Type& value)
{
	static_assert (IsTriviallyCopyable<Type>);

	return GenerateBinaryHashValue (reinterpret_cast<const std::byte*> (&value), sizeof (value));
}


template <class RandomIt>
inline ULong	GenerateHashValueFromRange (const RandomIt& begin, const RandomIt& end)
{
	DBASSERT (begin <= end);

	const UInt64 length    = end - begin;
	const UInt64 increment = (length < 16) ? 1 : length / 16;

	ULong hashValue = 0;
	for (UInt64 i = 0; i < length; i += increment)
		hashValue = hashValue * 65599 + GS::CalculateHashValue (begin[i]);

	return hashValue;
}


}	// namespace GS


#endif
