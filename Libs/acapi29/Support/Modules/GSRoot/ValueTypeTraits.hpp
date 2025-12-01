#pragma once

#include <type_traits>

namespace GS {

// === TypeAvailability class macro ====================================================================================

#define GS_DEFINE_TYPE_AVAILABILITY_CLASS(ClassName, TypeName)						\
	template <class T_>																\
	class ClassName {																\
	private:																		\
		typedef char Yes[1];														\
		typedef char No[2];															\
																					\
		template <class U_>															\
		static Yes&			Test (typename U_::TypeName*);							\
		template <class>															\
		static No&			Test (...);												\
																					\
	public:																			\
		static const bool Value = (sizeof (Test<T_> (nullptr)) == sizeof (Yes));	\
	};


// === ValueTypeTrait class ============================================================================================

template <class T>
class ValueTypeTrait {
private:
	GS_DEFINE_TYPE_AVAILABILITY_CLASS (CamelCaseValueTypeAvailability, ValueType)
	GS_DEFINE_TYPE_AVAILABILITY_CLASS (SnakeCaseValueTypeAvailability, value_type)

	template <class U, bool HasCamelCase, bool HasSnakeCase>
	struct ConditionalValueType;
	template <class U, bool HasSnakeCase>
	struct ConditionalValueType<U, true, HasSnakeCase> { typedef typename U::ValueType Type; };
	template <class U>
	struct ConditionalValueType<U, false, true> { typedef typename U::value_type Type; };
	template <class U>
	struct ConditionalValueType<U, false, false> { typedef void Type; };

public:
	typedef typename ConditionalValueType<T, CamelCaseValueTypeAvailability<T>::Value, SnakeCaseValueTypeAvailability<T>::Value>::Type Type;
};


// --- Specialization for pointers -------------------------------------------------------------------------------------

template <class T>
class ValueTypeTrait<T*> {
public:
	typedef T Type;
};

template <class T>
class ValueTypeTrait<const T*> {
public:
	typedef T Type;
};

}	// namespace OA
