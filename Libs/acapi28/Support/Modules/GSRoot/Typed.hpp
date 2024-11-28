// *****************************************************************************
//
// Contact person: MB, PR
//
// *****************************************************************************

#ifndef GS_TYPED_HPP
#define GS_TYPED_HPP

#include "GSAssert.hpp"
#include "HashCommon.hpp"
#include "TypedOperators.hpp"


namespace GS {
	class IChannel;
	class OChannel;
}


namespace GS::TypedImpl {


template<typename ValueType, auto... Conditions>
class Constraint {
public:
	static_assert (((std::is_invocable_v<decltype (Conditions), const ValueType&>) && ...));

	static constexpr bool IsValid (const ValueType& value) // TODO C++20: std::invoke
	{
		return (((*Conditions) (value)) && ...);
	}

	static constexpr void EnsureConstraint (const ValueType& value)
	{
		PRECOND_T (IsValid (value));
	}

	static constexpr bool IsEmpty ()
	{
		return sizeof... (Conditions) == 0;
	}
};


template<typename ValueType, typename TagType, typename ConstraintType = Constraint<ValueType>>
class Typed final {
public:

	template<typename U = ValueType, EnableIf<IsDefaultConstructible<U>>* = nullptr>
	constexpr Typed () noexcept (IsNothrowDefaultConstructible<ValueType>);

	template<typename U = ValueType, EnableIf<IsMoveConstructible<U>>* = nullptr>
	explicit constexpr Typed (ValueType&&) noexcept (IsNothrowMoveConstructible<ValueType>);

	template<typename U = ValueType, EnableIf<IsCopyConstructible<U>>* = nullptr>
	explicit constexpr Typed (const ValueType&) noexcept (IsNothrowCopyConstructible<ValueType>);

	template<typename... Args, EnableIf<IsConstructible<ValueType, Args...>>* = nullptr>
	explicit constexpr Typed (std::in_place_t, Args&&...) noexcept (IsNothrowConstructible<ValueType, Args...>);

	template<bool E = ConstraintType::IsEmpty (), EnableIf<!E>* = nullptr>
	static bool					IsValid (const ValueType& value);

	template<bool E = ConstraintType::IsEmpty (), EnableIf<E>* = nullptr>
	constexpr ValueType&		Get (void) & noexcept gs_lifebound;
	constexpr ValueType&&		Get (void) && noexcept gs_lifebound;
	constexpr const ValueType&	Get (void) const& noexcept gs_lifebound;

	template<bool E = ConstraintType::IsEmpty (), EnableIf<E>* = nullptr>
	constexpr ValueType&		operator* (void) & noexcept gs_lifebound;
	constexpr ValueType&&		operator* (void) && noexcept gs_lifebound;
	constexpr const ValueType&	operator* (void) const& noexcept gs_lifebound;

	template<bool E = ConstraintType::IsEmpty (), EnableIf<E>* = nullptr>
	constexpr ValueType*		operator-> (void) noexcept gs_lifebound;
	constexpr const ValueType*	operator-> (void) const noexcept gs_lifebound;

private:
	
	template<typename V, typename T, typename C, typename>
	friend GSErrCode			Read (IChannel& ic, Typed<V, T, C>& value);

	static_assert (IsDecayed<ValueType>);

	ValueType mValue {};
};


/* ================================================================================================================== */


template<typename ValueType, typename TagType, typename ConstraintType>
template<typename U, EnableIf<IsDefaultConstructible<U>>*>
constexpr Typed<ValueType, TagType, ConstraintType>::Typed ()
	noexcept (IsNothrowDefaultConstructible<ValueType>)
{
	ConstraintType::EnsureConstraint (mValue);
}


template<typename ValueType, typename TagType, typename ConstraintType>
template<typename U, EnableIf<IsMoveConstructible<U>>*>
constexpr Typed<ValueType, TagType, ConstraintType>::Typed (ValueType&& value)
	noexcept (IsNothrowMoveConstructible<ValueType>)
	: mValue { static_cast<ValueType&&> (value) }
{
	ConstraintType::EnsureConstraint (mValue);
}


template<typename ValueType, typename TagType, typename ConstraintType>
template<typename U, EnableIf<IsCopyConstructible<U>>*>
constexpr Typed<ValueType, TagType, ConstraintType>::Typed (const ValueType& value)
	noexcept (IsNothrowCopyConstructible<ValueType>)
	: mValue { value }
{
	ConstraintType::EnsureConstraint (mValue);
}


template<typename ValueType, typename TagType, typename ConstraintType>
template<typename... Args, EnableIf<IsConstructible<ValueType, Args...>>*>
constexpr Typed<ValueType, TagType, ConstraintType>::Typed (std::in_place_t, Args&&... args)
	noexcept (IsNothrowConstructible<ValueType, Args...>)
	: mValue { std::forward<Args> (args)... }
{
	ConstraintType::EnsureConstraint (mValue);
}


template<typename ValueType, typename TagType, typename ConstraintType>

template<bool E, EnableIf<!E>*>
bool Typed<ValueType, TagType, ConstraintType>::IsValid (const ValueType& value)
{
	return ConstraintType::IsValid (value);
}


template<typename ValueType, typename TagType, typename ConstraintType>
template<bool E, EnableIf<E>*>
constexpr ValueType&		Typed<ValueType, TagType, ConstraintType>::Get (void) & noexcept
{
	return mValue;
}


template<typename ValueType, typename TagType, typename ConstraintType>
constexpr ValueType&&		Typed<ValueType, TagType, ConstraintType>::Get (void) && noexcept
{
	return static_cast<ValueType&&> (mValue);
}


template<typename ValueType, typename TagType, typename ConstraintType>
constexpr const ValueType&	Typed<ValueType, TagType, ConstraintType>::Get (void) const& noexcept
{
	return mValue;
}


template<typename ValueType, typename TagType, typename ConstraintType>
template<bool E, EnableIf<E>*>
constexpr ValueType&		Typed<ValueType, TagType, ConstraintType>::operator* (void) &noexcept
{
	return mValue;
}


template<typename ValueType, typename TagType, typename ConstraintType>
constexpr ValueType&&		Typed<ValueType, TagType, ConstraintType>::operator* (void) && noexcept
{
	return static_cast<ValueType&&> (mValue);
}


template<typename ValueType, typename TagType, typename ConstraintType>
constexpr const ValueType&	Typed<ValueType, TagType, ConstraintType>::operator* (void) const& noexcept
{
	return mValue;
}


template<typename ValueType, typename TagType, typename ConstraintType>
template<bool E, EnableIf<E>*>
constexpr ValueType*		Typed<ValueType, TagType, ConstraintType>::operator-> (void) noexcept
{
	return &mValue;
}


template<typename ValueType, typename TagType, typename ConstraintType>
constexpr const ValueType*	Typed<ValueType, TagType, ConstraintType>::operator-> (void) const noexcept
{
	return &mValue;
}


/* ================================================================================================================== */


template<typename V, typename T, typename C, typename = decltype (EnableGenerateHashValue (std::declval<Typed<V, T, C>> ()))>
ULong	GenerateHashValue (const Typed<V, T, C>& value)
{
	return ::GS::CalculateHashValue (value.Get ());
}


template<typename V, typename T, typename C, typename = decltype (EnableReadWrite (std::declval<Typed<V, T, C>> ()))>
GSErrCode	Read (IChannel& ic, Typed<V, T, C>& value)
{
	return ic.Read (value.mValue);
}


template<typename V, typename T, typename C, typename = decltype (EnableReadWrite (std::declval<Typed<V, T, C>> ()))>
GSErrCode	Write (OChannel& oc, const Typed<V, T, C>& value)
{
	return oc.Write (value.Get ());
}


} // namespace GS::TypedImpl


namespace GS {
	template<typename ValueType, typename TagType>
	using Typed = TypedImpl::Typed<ValueType, TagType>;
}


#endif /* GS_TYPED_HPP */
