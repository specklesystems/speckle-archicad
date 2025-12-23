// *****************************************************************************
//
// Contact person: GaGa, MB, PR, BIA
//
// *****************************************************************************

#ifndef GS_RESULT_DETAILS_HPP
#define GS_RESULT_DETAILS_HPP


#include <functional>
#include <utility>
#include <variant>

#include "GSAssertCore.hpp"
#include "TypeTraits.hpp"


namespace GS::ResultImpl {


template <typename, typename>
class Result;


template <typename R, std::size_t I, typename F, typename VariantT>
constexpr R Invoke (F&& func, VariantT&& variant)
{
	if (variant.index () == I)
		return std::invoke (std::forward<F> (func), std::get<I> (std::forward<VariantT> (variant)));

	return std::get<1 - I> (std::forward<VariantT> (variant));
}


template <typename MainT, typename A, typename F>
constexpr bool CheckAndThenFunc ()
{
	static_assert (std::is_invocable_v<F, MainT>);
	using R = std::invoke_result_t<F, MainT>;

	static_assert (IsSpecializationOf<R, Result>, "The callable must return a prvalue Result.");
	static_assert (std::is_same_v<typename R::AltType, A>, "You cannot change the alternative type, only the main type.");

	return true;
}


template <typename MainT, typename F>
constexpr bool CheckTransformFunc ()
{
	static_assert (std::is_invocable_v<F, MainT>);

	return true;
}


template <typename MainT, typename F>
constexpr bool CheckOnMainFunc ()
{
	if constexpr (std::is_void_v<MainT>) {
		static_assert (std::is_invocable_v<F>);
	} else {
		static_assert (std::is_invocable_v<F, MainT>);
	}

	return true;
}


template <typename T, typename AltT, typename F>
constexpr bool	CheckOrElseFunc ()
{
	static_assert (std::is_invocable_v<F, AltT>);
	using R = std::invoke_result_t<F, AltT>;

	static_assert (IsSpecializationOf<R, Result>, "The callable must return a prvalue Result.");
	static_assert (std::is_same_v<typename R::MainType, T>, "You cannot change the main type, only the alternative type.");

	return true;
}


template <typename AltT, typename F>
constexpr bool	CheckTransformAltFunc ()
{
	static_assert (std::is_invocable_v<F, AltT>);

	return true;
}


template <typename AltT, typename F>
constexpr bool CheckOnAltFunc ()
{
	static_assert (std::is_invocable_v<F, AltT>);

	return true;
}


// ================================================================================================================== */


template <typename A, typename VariantT>
constexpr auto ToVoidVariant (VariantT&& variant) -> std::variant<std::monostate, A>
{
	if (std::holds_alternative<A> (variant))
		return std::get<A> (std::forward<VariantT> (variant));

	return std::monostate {};
}


// ================================================================================================================== */


struct TerminatePolicy {

	template <typename T, typename A>
	static void		OnBadMainAccess [[noreturn]] (const std::variant<T, A>&)
	{
		GS::AssertImpl::AssertFailedT ({__FILE__, __FUNCTION__, __LINE__}, AssertImpl::GetPrecondDataT (), "TerminatePolicy::OnBadMainAccess");
	}

	template <typename T, typename A>
	static void		OnBadAltAccess [[noreturn]] (const std::variant<T, A>&)
	{
		GS::AssertImpl::AssertFailedT ({__FILE__, __FUNCTION__, __LINE__}, AssertImpl::GetPrecondDataT (), "TerminatePolicy::OnBadAltAccess");
	}
};



// === class ResultBase ================================================================================================

template <typename T, typename A, typename BadAccessPolicy>
class ResultBase {
private:

	using MainT = std::conditional_t<std::is_same_v<T, void>, std::monostate, T>;
	using AltT = A;

	static_assert (IsDecayed<T>);
	static_assert (IsDecayed<A>);
	static_assert (!std::is_same_v<T, A>);


protected:

	ResultBase () = default;

	template <typename U>
	constexpr ResultBase (U&&) noexcept (std::is_nothrow_constructible_v<std::variant<MainT, AltT>, U>);

	template <typename U, typename... Args>
	constexpr ResultBase (std::in_place_type_t<U>, Args&&...)
		noexcept (std::is_nothrow_constructible_v<std::variant<MainT, AltT>, std::in_place_type_t<U>, Args...>);


	// Main queries

	constexpr bool				IsMain () const noexcept;

	constexpr MainT&			Get () & gs_lifebound;
	constexpr const MainT&		Get () const& gs_lifebound;
	constexpr MainT&&			Get () && gs_lifebound;

	constexpr MainT*			GetPtr () gs_lifebound;
	constexpr const MainT*		GetPtr () const gs_lifebound;

	template <typename U>
	constexpr MainT				GetOr (U&& fallbackValue) const&;
	template <typename U>
	constexpr MainT				GetOr (U&& fallbackValue) &&;


	// Alternative queries

	constexpr bool				IsAlt () const noexcept;

	constexpr AltT&				GetAlt () & gs_lifebound;
	constexpr const AltT&		GetAlt () const& gs_lifebound;
	constexpr AltT&&			GetAlt () && gs_lifebound;

	constexpr AltT*				GetAltPtr () gs_lifebound;
	constexpr const AltT*		GetAltPtr () const gs_lifebound;

	template <typename U>
	constexpr AltT				GetAltOr (U&& fallbackValue) const&;
	template <typename U>
	constexpr AltT				GetAltOr (U&& fallbackValue) &&;


	// Main monadic operations

	template <typename F>
	constexpr auto		AndThen (F&&) &;
	template <typename F>
	constexpr auto		AndThen (F&&) const&;
	template <typename F>
	constexpr auto		AndThen (F&&) &&;

	template <typename F>
	constexpr auto		Transform (F&&) &;
	template <typename F>
	constexpr auto		Transform (F&&) const&;
	template <typename F>
	constexpr auto		Transform (F&&) &&;

	template <typename F>
	constexpr void		OnMain (F&&) &;
	template <typename F>
	constexpr void		OnMain (F&&) const&;
	template <typename F>
	constexpr void		OnMain (F&&) &&;


	// Alternative monadic operations

	template <typename F>
	constexpr auto		OrElse (F&&) &;
	template <typename F>
	constexpr auto		OrElse (F&&) const&;
	template <typename F>
	constexpr auto		OrElse (F&&) &&;

	template <typename F>
	constexpr auto		TransformAlt (F&&) &;
	template <typename F>
	constexpr auto		TransformAlt (F&&) const&;
	template <typename F>
	constexpr auto		TransformAlt (F&&) &&;

	template <typename F>
	constexpr void		OnAlt (F&&) &;
	template <typename F>
	constexpr void		OnAlt (F&&) const&;
	template <typename F>
	constexpr void		OnAlt (F&&) &&;


protected:

	std::variant<MainT, AltT> mValue;
};


// === class ResultBase implementation =================================================================================

template <typename T, typename A, typename BadAccessPolicy>
template <typename U>
constexpr ResultBase<T, A, BadAccessPolicy>::ResultBase (U&& object)
	noexcept (std::is_nothrow_constructible_v<std::variant<MainT, AltT>, U>)
	: mValue { std::forward<U> (object) }
{
}


template <typename T, typename A, typename BadAccessPolicy>
template <typename U, typename... Args>
constexpr ResultBase<T, A, BadAccessPolicy>::ResultBase (std::in_place_type_t<U>, Args&&... args)
noexcept (std::is_nothrow_constructible_v<std::variant<MainT, AltT>, std::in_place_type_t<U>, Args...>)
	: mValue { std::in_place_type<U>, std::forward<Args> (args)... }
{
}


template <typename T, typename A, typename BadAccessPolicy>
constexpr bool ResultBase<T, A, BadAccessPolicy>::IsMain () const noexcept
{
	return std::holds_alternative<MainT> (mValue);
}


template <typename T, typename A, typename BadAccessPolicy>
constexpr auto ResultBase<T, A, BadAccessPolicy>::Get () & -> MainT&
{
	if (MainT* main = std::get_if<MainT> (&mValue); main != nullptr)
		return *main;

	BadAccessPolicy::OnBadMainAccess (mValue);
}


template <typename T, typename A, typename BadAccessPolicy>
constexpr auto ResultBase<T, A, BadAccessPolicy>::Get () const& -> const MainT&
{
	if (const MainT* main = std::get_if<MainT> (&mValue); main != nullptr)
		return *main;

	BadAccessPolicy::OnBadMainAccess (mValue);
}


template <typename T, typename A, typename BadAccessPolicy>
constexpr auto ResultBase<T, A, BadAccessPolicy>::Get () && -> MainT&&
{
	if (MainT* main = std::get_if<MainT> (&mValue); main != nullptr)
		return std::move (*main);

	BadAccessPolicy::OnBadMainAccess (mValue);
}


template <typename T, typename A, typename BadAccessPolicy>
constexpr auto ResultBase<T, A, BadAccessPolicy>::GetPtr () -> MainT*
{
	return std::get_if<MainT> (&mValue);
}


template <typename T, typename A, typename BadAccessPolicy>
constexpr auto ResultBase<T, A, BadAccessPolicy>::GetPtr () const -> const MainT*
{
	return std::get_if<MainT> (&mValue);
}


template <typename T, typename A, typename BadAccessPolicy>
template <typename U>
constexpr auto ResultBase<T, A, BadAccessPolicy>::GetOr (U&& fallbackValue) const& -> MainT
{
	if (const MainT* main = std::get_if<MainT> (&mValue); main != nullptr) {
		return *main;
	}

	return std::forward<U> (fallbackValue);
}


template <typename T, typename A, typename BadAccessPolicy>
template <typename U>
constexpr auto ResultBase<T, A, BadAccessPolicy>::GetOr (U&& fallbackValue) && -> MainT
{
	if (MainT* main = std::get_if<MainT> (&mValue); main != nullptr) {
		return std::move (*main);
	}

	return std::forward<U> (fallbackValue);
}


template <typename T, typename A, typename BadAccessPolicy>
constexpr bool ResultBase<T, A, BadAccessPolicy>::IsAlt () const noexcept
{
	return std::holds_alternative<AltT> (mValue);
}


template <typename T, typename A, typename BadAccessPolicy>
constexpr auto ResultBase<T, A, BadAccessPolicy>::GetAlt () & -> AltT&
{
	if (AltT* alt = std::get_if<AltT> (&mValue); alt != nullptr)
		return *alt;

	BadAccessPolicy::OnBadAltAccess (mValue);
}


template <typename T, typename A, typename BadAccessPolicy>
constexpr auto ResultBase<T, A, BadAccessPolicy>::GetAlt () const& -> const AltT&
{
	if (const AltT* alt = std::get_if<AltT> (&mValue); alt != nullptr)
		return *alt;

	BadAccessPolicy::OnBadAltAccess (mValue);
}


template <typename T, typename A, typename BadAccessPolicy>
constexpr auto ResultBase<T, A, BadAccessPolicy>::GetAlt () && -> AltT&&
{
	if (AltT* alt = std::get_if<AltT> (&mValue); alt != nullptr)
		return std::move (*alt);

	BadAccessPolicy::OnBadAltAccess (mValue);
}


template <typename T, typename A, typename BadAccessPolicy>
constexpr auto ResultBase<T, A, BadAccessPolicy>::GetAltPtr () -> AltT*
{
	return std::get_if<AltT> (&mValue);
}


template <typename T, typename A, typename BadAccessPolicy>
constexpr auto ResultBase<T, A, BadAccessPolicy>::GetAltPtr () const -> const AltT*
{
	return std::get_if<AltT> (&mValue);
}


template <typename T, typename A, typename BadAccessPolicy>
template <typename U>
constexpr auto ResultBase<T, A, BadAccessPolicy>::GetAltOr (U&& fallbackValue) const& -> AltT
{
	if (const AltT* alt = std::get_if<AltT> (&mValue); alt != nullptr) {
		return *alt;
	}

	return std::forward<U> (fallbackValue);
}


template <typename T, typename A, typename BadAccessPolicy>
template <typename U>
constexpr auto ResultBase<T, A, BadAccessPolicy>::GetAltOr (U&& fallbackValue) && -> AltT
{
	if (AltT* alt = std::get_if<AltT> (&mValue); alt != nullptr) {
		return std::move (*alt);
	}

	return std::forward<U> (fallbackValue);
}


template <typename T, typename A, typename BadAccessPolicy>
template <typename F>
constexpr auto ResultBase<T, A, BadAccessPolicy>::AndThen (F&& func) &
{
	static_assert (CheckAndThenFunc<MainT&, A, F> ());

	using R = std::invoke_result_t<F, MainT&>;
	return Invoke<R, 0> (std::forward<F> (func), mValue);
}


template <typename T, typename A, typename BadAccessPolicy>
template <typename F>
constexpr auto ResultBase<T, A, BadAccessPolicy>::AndThen (F&& func) const&
{
	static_assert (CheckAndThenFunc<const MainT&, A, F> ());

	using R = std::invoke_result_t<F, const MainT&>;
	return Invoke<R, 0> (std::forward<F> (func), mValue);
}


template <typename T, typename A, typename BadAccessPolicy>
template <typename F>
constexpr auto ResultBase<T, A, BadAccessPolicy>::AndThen (F&& func) &&
{
	static_assert (CheckAndThenFunc<MainT&&, A, F> ());

	using R = std::invoke_result_t<F, MainT&&>;
	return Invoke<R, 0> (std::forward<F> (func), std::move (mValue));
}


template <typename T, typename A, typename BadAccessPolicy>
template <typename F>
constexpr auto ResultBase<T, A, BadAccessPolicy>::Transform (F&& func) &
{
	static_assert (CheckTransformFunc<MainT&, F> ());
	using R = std::decay_t<std::invoke_result_t<F, MainT&>>;

	return Invoke<Result<R, A>, 0> (std::forward<F> (func), mValue);
}


template <typename T, typename A, typename BadAccessPolicy>
template <typename F>
constexpr auto ResultBase<T, A, BadAccessPolicy>::Transform (F&& func) const&
{
	static_assert (CheckTransformFunc<const MainT&, F> ());
	using R = std::decay_t<std::invoke_result_t<F, const MainT&>>;

	return Invoke<Result<R, A>, 0> (std::forward<F> (func), mValue);
}


template <typename T, typename A, typename BadAccessPolicy>
template <typename F>
constexpr auto ResultBase<T, A, BadAccessPolicy>::Transform (F&& func) &&
{
	static_assert (CheckTransformFunc<MainT&&, F> ());
	using R = std::decay_t<std::invoke_result_t<F, MainT&&>>;

	return Invoke<Result<R, A>, 0> (std::forward<F> (func), std::move (mValue));
}


template <typename T, typename A, typename BadAccessPolicy>
template <typename F>
constexpr void ResultBase<T, A, BadAccessPolicy>::OnMain (F&& func) &
{
	static_assert (CheckOnMainFunc<MainT&, F> ());

	if (IsMain ()) {
		std::invoke (std::forward<F> (func), Get ());
	}
}


template <typename T, typename A, typename BadAccessPolicy>
template <typename F>
constexpr void ResultBase<T, A, BadAccessPolicy>::OnMain (F&& func) const&
{
	static_assert (CheckOnMainFunc<const MainT&, F> ());

	if (IsMain ()) {
		std::invoke (std::forward<F> (func), Get ());
	}
}


template <typename T, typename A, typename BadAccessPolicy>
template <typename F>
constexpr void ResultBase<T, A, BadAccessPolicy>::OnMain (F&& func) &&
{
	static_assert (CheckOnMainFunc<MainT&&, F> ());

	if (IsMain ()) {
		std::invoke (std::forward<F> (func), std::move (*this).Get ());
	}
}


template <typename T, typename A, typename BadAccessPolicy>
template <typename F>
constexpr auto ResultBase<T, A, BadAccessPolicy>::OrElse (F&& func) &
{
	static_assert (CheckOrElseFunc<T, AltT&, F> ());
	using R = std::invoke_result_t<F, AltT&>;

	return Invoke<R, 1> (std::forward<F> (func), mValue);
}


template <typename T, typename A, typename BadAccessPolicy>
template <typename F>
constexpr auto ResultBase<T, A, BadAccessPolicy>::OrElse (F&& func) const&
{
	static_assert (CheckOrElseFunc<T, const AltT&, F> ());
	using R = std::invoke_result_t<F, const AltT&>;

	return Invoke<R, 1> (std::forward<F> (func), mValue);
}


template <typename T, typename A, typename BadAccessPolicy>
template <typename F>
constexpr auto ResultBase<T, A, BadAccessPolicy>::OrElse (F&& func) &&
{
	static_assert (CheckOrElseFunc<T, AltT&&, F> ());
	using R = std::invoke_result_t<F, AltT&&>;

	return Invoke<R, 1> (std::forward<F> (func), std::move (mValue));
}


template <typename T, typename A, typename BadAccessPolicy>
template <typename F>
constexpr auto ResultBase<T, A, BadAccessPolicy>::TransformAlt (F&& func) &
{
	static_assert (CheckTransformAltFunc<AltT&, F> ());
	using R = std::decay_t<std::invoke_result_t<F, AltT&>>;

	return Invoke<Result<T, R>, 1> (std::forward<F> (func), mValue);
}


template <typename T, typename A, typename BadAccessPolicy>
template <typename F>
constexpr auto ResultBase<T, A, BadAccessPolicy>::TransformAlt (F&& func) const&
{
	static_assert (CheckTransformAltFunc<const AltT&, F> ());
	using R = std::decay_t<std::invoke_result_t<F, const AltT&>>;

	return Invoke<Result<T, R>, 1> (std::forward<F> (func), mValue);
}


template <typename T, typename A, typename BadAccessPolicy>
template <typename F>
constexpr auto ResultBase<T, A, BadAccessPolicy>::TransformAlt (F&& func) &&
{
	static_assert (CheckTransformAltFunc<AltT&&, F> ());
	using R = std::decay_t<std::invoke_result_t<F, AltT&&>>;

	return Invoke<Result<T, R>, 1> (std::forward<F> (func), std::move (mValue));
}


template <typename T, typename A, typename BadAccessPolicy>
template <typename F>
constexpr void ResultBase<T, A, BadAccessPolicy>::OnAlt (F&& func) &
{
	static_assert (CheckOnAltFunc<AltT&, F> ());

	if (IsAlt ()) {
		std::invoke (std::forward<F> (func), GetAlt ());
	}
}


template <typename T, typename A, typename BadAccessPolicy>
template <typename F>
constexpr void ResultBase<T, A, BadAccessPolicy>::OnAlt (F&& func) const&
{
	static_assert (CheckOnAltFunc<const AltT&, F> ());

	if (IsAlt ()) {
		std::invoke (std::forward<F> (func), GetAlt ());
	}
}


template <typename T, typename A, typename BadAccessPolicy>
template <typename F>
constexpr void ResultBase<T, A, BadAccessPolicy>::OnAlt (F&& func) &&
{
	static_assert (CheckOnAltFunc<AltT&&, F> ());

	if (IsAlt ()) {
		std::invoke (std::forward<F> (func), std::move (*this).GetAlt ());
	}
}


} // namespace GS::ResultImpl


#endif /* GS_RESULT_HPP */
