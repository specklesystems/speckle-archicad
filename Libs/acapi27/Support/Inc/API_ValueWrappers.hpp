#if !defined API_VALUEWRAPPERS_HPP
#define API_VALUEWRAPPERS_HPP

// from GSRoot
#include "ParameterPackTraits.hpp"

/** @brief Represents NullValueType in the API layer.
	@ingroup APIInfrastructure
	@struct NullValueType
	@since Archicad 27
*/
constexpr struct NullValueType {} APINullValue;

/** @brief compares NullValueTyp in the API layer.
	@ingroup APIInfrastructure
	@since Archicad 27
*/
constexpr bool operator== (NullValueType, NullValueType) { return true; }

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#endif

/** @brief Represents a variant in the API layer.
	@ingroup APIInfrastructure
	@struct APIVariant
	@since Archicad 27
*/
template<typename... Types>
struct APIVariant {
	static_assert ((std::is_trivially_default_constructible_v<Types> && ...));
	static_assert (!(std::is_pointer_v<Types> && ...));
	static_assert ((std::is_trivially_copyable_v<Types> && ...));
	static_assert (GS::ParameterPack<Types...>::IsUnique);

	alignas (GS::Max (alignof (Types)...)) std::byte buffer[GS::Max (sizeof (Types)...)];
	UInt8 typeIndex;

	template <class T>
	static constexpr bool	Contains	= GS::ParameterPack<Types...>::template Contains<T>;

	template <class T>
	static constexpr UInt8	TypeToIndex	= GS::ParameterPack<Types...>::template FindFirst<T>;

	template<typename T>
	void Put (T p) {
		static_assert (Contains<T>);
		DBASSERT (TypeToIndex<T> == typeIndex);
		std::memcpy (reinterpret_cast<void*> (buffer), &p, sizeof (T));
		typeIndex = TypeToIndex<T>;
	}

	template<typename T>
	T Get () const {
		static_assert (Contains<T>);
		DBASSERT (TypeToIndex<T> == typeIndex);
		T value;
		std::memcpy (&value, &buffer, sizeof (T));
		return value;
	}

	template<typename T>
	bool IsType () const {
		static_assert (Contains<T>);
		return TypeToIndex<T> == typeIndex;
	}

	template<typename T>
	APIVariant& operator= (T p) {
		static_assert (Contains<T>);
		static_assert(std::disjunction_v<std::is_same<T, Types>...>);
		std::memcpy (reinterpret_cast<void*> (buffer), &p, sizeof (T));
		typeIndex = TypeToIndex<T>;

		return *this;
	}
};

/** @brief Represents an optional in the API layer.
	@ingroup APIInfrastructure
	@struct APIOptional
	@since Archicad 27
*/
template<typename T>
struct APIOptional {
	static_assert (std::is_trivially_default_constructible_v<T>);
	static_assert (!std::is_pointer_v<T>);
	static_assert (std::is_trivially_copyable_v<T>);

	bool hasValue;
	T value;

	template<typename K>
	void operator = (K v) {
		hasValue = true;
		value = v;
	}

	void operator = (NullValueType nullOpt) {
		static_assert (nullOpt == APINullValue, "Unsafe assignment! Use APINullValue to indicate the loss of valid stored value.");
		hasValue = false;
	}
};


#ifdef __clang__
#pragma clang diagnostic pop
#endif


#endif //  API_VALUEWRAPPERS_HPP
