// *****************************************************************************
//
// Contact person: MB, PR
//
// *****************************************************************************

#ifndef GS_EXPECTEDDETAILS_HPP
#define GS_EXPECTEDDETAILS_HPP

#include "Definitions.hpp"
#include "GSAssertCore.hpp"
#include "RuntimeError.hpp"
#include "TypeTraits.hpp"
#include "GSDebug.hpp"

#ifndef GS_BUILD_MODULE
// from Standard Library
#include <concepts>
#include <utility>
#include <variant>
#endif


namespace GS::ExpectedImpl {


template<typename T>
concept IsRuntimeError = std::derived_from<T, GS::RuntimeError>;

template<typename T>
concept IsStandardException = std::derived_from<T, std::exception>;

template<typename T>
concept IsExceptionType = IsRuntimeError<T> || IsStandardException<T>;


template<typename T>
using EnableIfExceptionType = EnableIf<IsExceptionType<T>>;

template<typename T>
using EnableIfNotExceptionType = EnableIf<!IsExceptionType<T>>;


template<typename T>
concept IsErrorType = std::same_as<T, GS::ErrorType>;


template<typename V, typename E>
concept BothAreEqualityComparable = std::equality_comparable<V> && std::equality_comparable<E>;


template<typename, typename, typename>
class ExpectedBase;

template<typename, typename = GS::ErrorType, typename = void /*SFINAE*/>
class Expected;


template<typename R, std::size_t I, typename F, typename VariantT>
constexpr auto	Invoke (F&& callable, VariantT&& variant) -> R
{
	if (variant.index () == I)
		return std::invoke (std::forward<F> (callable), std::get<I> (std::forward<VariantT> (variant)));

	return std::get<1 - I> (std::forward<VariantT> (variant));
}


template<typename V, typename E, typename F>
constexpr bool	CheckAndThenFunc (void) // TODO: Should be consteval when we have that.
{
	static_assert (std::invocable<F, V>);
	using R = InvokeResult<F, V>;

	static_assert (IsSpecializationOf<R, Expected>, "The callable must return an rvalue Expected.");
	static_assert (std::same_as<typename R::ErrorType, E>, "You cannot change the error type, only the value type.");

	return true;
}


template<typename V, typename F>
constexpr bool	CheckTransformFunc (void) // TODO: Should be consteval when we have that.
{
	static_assert (std::invocable<F, V>);
	using R = InvokeResult<F, V>;

	static_assert (!IsSpecializationOf<Decay<R>, Expected>, "The callable must not return an Expected.");

	return true;
}


template<typename V, typename E, typename F>
constexpr bool	CheckOrElseFunc (void) // TODO: Should be consteval when we have that.
{
	static_assert (std::invocable<F, E>);
	using R = InvokeResult<F, E>;

	static_assert (IsSpecializationOf<R, Expected>, "The callable must return an rvalue Expected.");
	static_assert (std::same_as<typename R::ValueType, V>, "You cannot change the value type, only the error type.");

	return true;
}


template<typename E, typename F>
constexpr bool	CheckTransformErrorFunc (void) // TODO: Should be consteval when we have that.
{
	static_assert (std::invocable<F, E>);
	using R = InvokeResult<F, E>;

	static_assert (!IsSpecializationOf<Decay<R>, Expected>, "The callable must not return an Expected.");

	return true;
}


/* ================================================================================================================== */


template<typename ExT, typename... Args>
auto	MakeExceptionPtr (Args&&... args) noexcept (IsNothrowConstructible<ExT, Args...>) -> std::exception_ptr
{
	static_assert (IsExceptionType<ExT>);

	try {
		throw ExT (std::forward<Args> (args)...);
	}
	catch (const ExT&) {
		return std::current_exception ();
	}
}


template<typename V, typename ExpectedT>
auto	ToErrVariant (ExpectedT&& expected) -> std::variant<V, GS::ErrorType>
{
	static_assert (IsRuntimeError<typename Decay<ExpectedT>::ErrorType>);

	try {
		if constexpr (std::same_as<V, std::monostate>) {
			std::as_const (expected).GetValue ();
			return std::monostate {};
		} else {
			return std::forward<ExpectedT> (expected).GetValue ();
		}
	}
	catch (const GS::RuntimeError& ex) {
		return static_cast<GS::ErrorType> (ex.GetErrCode ());
	}
	catch (...) {
		GS::Unreachable ();
	}
}


template<typename V, typename ExT, typename ExpectedT>
auto	ToExVariant (ExpectedT&& expected) -> std::variant<V, std::exception_ptr>
{
	static_assert (std::same_as<typename Decay<ExpectedT>::ErrorType, GS::ErrorType>);
	static_assert (std::derived_from<ExT, GS::RuntimeError>);

	if (expected.IsValue ()) {
		if constexpr (std::same_as<V, std::monostate>) {
			return std::monostate {};
		} else {
			return std::forward<ExpectedT> (expected).GetValue ();
		}
	}

	try {
		throw ExT { "GS::Expected", expected.GetError (), __FILE__, __LINE__ };
	}
	catch (const ExT&) {
		return std::current_exception ();
	}
}


template<typename E, typename VariantT>
auto	ToVoidVariant (VariantT&& variant) -> std::variant<std::monostate, E>
{
	if (std::holds_alternative<E> (variant))
		return std::get<E> (std::forward<VariantT> (variant));

	return std::monostate {};
}


/* ================================================================================================================== */


template<typename T, typename TagT = T>
class ErrorData {
private:

	constexpr ErrorData (T&& error)
		noexcept (IsNothrowMoveConstructible<T>)
		: error { std::move (error) }
	{}

	constexpr ErrorData (const T& error)
		noexcept (IsNothrowCopyConstructible<T>)
		: error { error }
	{}

private:

	template<typename, typename, typename>
	friend class ExpectedBase;

	template<typename, typename, typename>
	friend class Expected;

	T error;
};


/* ================================================================================================================== */


struct TerminatePolicy {

	template<typename V, typename E>
	static void		OnBadValueAccess [[noreturn]] (const std::variant<V, E>&)
	{
		GS::AssertImpl::AssertFailedT ({ __FILE__, __FUNCTION__, __LINE__ }, AssertImpl::GetPrecondDataT (), "TerminatePolicy::OnBadValueAccess");
	}

	template<typename V, typename E>
	static void		OnBadErrorAccess [[noreturn]] (const std::variant<V, E>&)
	{
		GS::AssertImpl::AssertFailedT ({ __FILE__, __FUNCTION__, __LINE__ }, AssertImpl::GetPrecondDataT (), "TerminatePolicy::OnBadErrorAccess");
	}
};


struct ExceptionPolicy {

	template<typename V>
	static void		OnBadValueAccess [[noreturn]] (const std::variant<V, std::exception_ptr>& variant)
	{
		std::rethrow_exception (std::get<1> (variant));
	}

	template<typename V>
	static void		OnBadErrorAccess [[noreturn]] (const std::variant<V, std::exception_ptr>&)
	{
		GS::AssertImpl::AssertFailedT ({ __FILE__, __FUNCTION__, __LINE__ }, AssertImpl::GetPrecondDataT (), "ExceptionPolicy::OnBadErrorAccess");
	}
};


/* === class ExpectedBase =========================================================================================== */


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
class ExpectedBase {

	using VT = Conditional<std::same_as<ValueT, void>, std::monostate, ValueT>;
	using ET = Conditional<IsExceptionType<ErrorT>, std::exception_ptr, ErrorT>;

	static_assert (IsDecayed<VT>);
	static_assert (IsDecayed<ET>);
	static_assert (!std::same_as<VT, ET>);
	static_assert (!std::same_as<ValueT, GS::NoErrorType>);
	static_assert (!std::same_as<ErrorT, GS::NoErrorType>);

protected:

	std::variant<VT, ET> mState;

protected:

	ExpectedBase () = default;

	template<typename T>
	constexpr ExpectedBase (T&&)
		noexcept (IsNothrowConstructible<std::variant<VT, ET>, T>);

	template<typename T, typename... Args>
	constexpr ExpectedBase (std::in_place_type_t<T>, Args&&...);

// Comparisons

	constexpr bool			operator== (GS::NoErrorType) const noexcept;

	constexpr bool			operator== (const VT&) const requires (std::equality_comparable<ValueT>);
	constexpr bool			operator== (const ET&) const requires (!IsExceptionType<ErrorT> && std::equality_comparable<ErrorT>);

// Value queries

	constexpr bool			IsValue (void) const noexcept;

	constexpr VT*			GetValuePtr (void) noexcept gs_lifebound;
	constexpr const VT*		GetValuePtr (void) const noexcept gs_lifebound;

	constexpr VT&			GetValue (void) & gs_lifebound;
	constexpr VT&&			GetValue (void) && gs_lifebound;
	constexpr const VT&		GetValue (void) const& gs_lifebound;

	constexpr VT&			operator* (void) & gs_lifebound;
	constexpr VT&&			operator* (void) && gs_lifebound;
	constexpr const VT&		operator* (void) const& gs_lifebound;

	constexpr VT*			operator-> (void) & gs_lifebound;
	constexpr const VT*		operator-> (void) const& gs_lifebound;

// Error queries

	constexpr bool			IsError (void) const noexcept;

	constexpr ET*			GetErrorPtr (void) & noexcept gs_lifebound;
	constexpr const ET*		GetErrorPtr (void) const& noexcept gs_lifebound;

	constexpr ET&			GetError (void) & gs_lifebound;
	constexpr ET&&			GetError (void) && gs_lifebound;
	constexpr const ET&		GetError (void) const& gs_lifebound;

	constexpr ErrorData<ET, ErrorT>	AsError (void) &;
	constexpr ErrorData<ET, ErrorT>	AsError (void) &&;
	constexpr ErrorData<ET, ErrorT>	AsError (void) const&;

// Monadic operations

	template<typename F>
	constexpr auto		AndThen (F&&) &;

	template<typename F>
	constexpr auto		AndThen (F&&) &&;

	template<typename F>
	constexpr auto		AndThen (F&&) const&;

	template<typename F>
	constexpr auto		Transform (F&&) &;

	template<typename F>
	constexpr auto		Transform (F&&) &&;

	template<typename F>
	constexpr auto		Transform (F&&) const&;

	template<typename F>
	constexpr auto		OrElse (F&&) &;

	template<typename F>
	constexpr auto		OrElse (F&&) &&;

	template<typename F>
	constexpr auto		OrElse (F&&) const&;

	template<typename F>
	constexpr auto		TransformError (F&&) &;

	template<typename F>
	constexpr auto		TransformError (F&&) &&;

	template<typename F>
	constexpr auto		TransformError (F&&) const&;
};


/* === class ExpectedBase implementation ============================================================================ */


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
template<typename T>
constexpr ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::ExpectedBase (T&& object)
	noexcept (IsNothrowConstructible<std::variant<VT, ET>, T>)
	: mState { std::forward<T> (object) }
{}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
template<typename T, typename... Args>
constexpr ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::ExpectedBase (std::in_place_type_t<T>, Args&&... args)
	: mState { std::in_place_type<T>, std::forward<Args> (args)... }
{}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
constexpr bool		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::operator== (GS::NoErrorType) const noexcept
{
	return IsValue ();
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
constexpr bool		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::operator== (const VT& other) const requires (std::equality_comparable<ValueT>)
{
	if (auto* value = GetValuePtr (); value != nullptr)
		return *value == other;

	return false;
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
constexpr bool		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::operator== (const ET& other) const requires (!IsExceptionType<ErrorT> && std::equality_comparable<ErrorT>)
{
	if (auto* error = GetErrorPtr (); error != nullptr)
		return *error == other;

	return false;
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
constexpr bool		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::IsValue (void) const noexcept
{
	return std::holds_alternative<VT> (mState);
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::GetValuePtr (void) noexcept -> VT*
{
	return std::get_if<VT> (&mState);
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::GetValuePtr (void) const noexcept -> const VT*
{
	return std::get_if<VT> (&mState);
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::GetValue (void) & -> VT&
{
	if (VT* value = std::get_if<VT> (&mState); value != nullptr)
		return *value;

	BadAccessPolicy::OnBadValueAccess (mState);
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::GetValue (void) && -> VT&&
{
	if (VT* value = std::get_if<VT> (&mState); value != nullptr)
		return std::move (*value);

	BadAccessPolicy::OnBadValueAccess (mState);
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::GetValue (void) const& -> const VT&
{
	if (const VT* value = std::get_if<VT> (&mState); value != nullptr)
		return *value;

	BadAccessPolicy::OnBadValueAccess (mState);
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::operator* (void) & -> VT&
{
	return GetValue ();
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::operator* (void) && -> VT&&
{
	return std::move (*this).GetValue ();
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::operator* (void) const& -> const VT&
{
	return GetValue ();
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::operator-> (void) & -> VT*
{
	return &GetValue ();
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::operator-> (void) const& -> const VT*
{
	return &GetValue ();
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
constexpr bool		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::IsError (void) const noexcept
{
	return std::holds_alternative<ET> (mState);
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::GetErrorPtr (void) & noexcept -> ET*
{
	return std::get_if<ET> (&mState);
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::GetErrorPtr (void) const& noexcept -> const ET*
{
	return std::get_if<ET> (&mState);
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::GetError (void) & -> ET&
{
	if (ET* error = std::get_if<ET> (&mState); error != nullptr)
		return *error;

	BadAccessPolicy::OnBadErrorAccess (mState);
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::GetError (void) && -> ET&&
{
	if (ET* error = std::get_if<ET> (&mState); error != nullptr)
		return std::move (*error);

	BadAccessPolicy::OnBadErrorAccess (mState);
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::GetError (void) const& -> const ET&
{
	if (const ET* error = std::get_if<ET> (&mState); error != nullptr)
		return *error;

	BadAccessPolicy::OnBadErrorAccess (mState);
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::AsError (void) & -> ErrorData<ET, ErrorT>
{
	return GetError ();
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::AsError (void) && -> ErrorData<ET, ErrorT>
{
	return std::move (*this).GetError ();
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::AsError (void) const& -> ErrorData<ET, ErrorT>
{
	return GetError ();
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
template<typename F>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::AndThen (F&& func) &
{
	static_assert (CheckAndThenFunc<VT&, ErrorT, F> ());
	using R = InvokeResult<F, VT&>;

	return Invoke<R, 0> (std::forward<F> (func), mState);
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
template<typename F>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::AndThen (F&& func) &&
{
	static_assert (CheckAndThenFunc<VT&&, ErrorT, F> ());
	using R = InvokeResult<F, VT&&>;

	return Invoke<R, 0> (std::forward<F> (func), std::move (mState));
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
template<typename F>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::AndThen (F&& func) const&
{
	static_assert (CheckAndThenFunc<const VT&, ErrorT, F> ());
	using R = InvokeResult<F, const VT&>;

	return Invoke<R, 0> (std::forward<F> (func), mState);
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
template<typename F>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::Transform (F&& func) &
{
	static_assert (CheckTransformFunc<VT&, F> ());
	using R = Decay<InvokeResult<F, VT&>>;

	return Invoke<Expected<R, ErrorT>, 0> (std::forward<F> (func), mState);
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
template<typename F>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::Transform (F&& func) &&
{
	static_assert (CheckTransformFunc<VT&&, F> ());
	using R = Decay<InvokeResult<F, VT&&>>;

	return Invoke<Expected<R, ErrorT>, 0> (std::forward<F> (func), std::move (mState));
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
template<typename F>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::Transform (F&& func) const&
{
	static_assert (CheckTransformFunc<const VT&, F> ());
	using R = Decay<InvokeResult<F, const VT&>>;

	return Invoke<Expected<R, ErrorT>, 0> (std::forward<F> (func), mState);
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
template<typename F>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::OrElse (F&& func) &
{
	static_assert (CheckOrElseFunc<ValueT, ET&, F> ());
	using R = InvokeResult<F, ET&>;

	return Invoke<R, 1> (std::forward<F> (func), mState);
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
template<typename F>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::OrElse (F&& func) &&
{
	static_assert (CheckOrElseFunc<ValueT, ET&&, F> ());
	using R = InvokeResult<F, ET&&>;

	return Invoke<R, 1> (std::forward<F> (func), std::move (mState));
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
template<typename F>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::OrElse (F&& func) const&
{
	static_assert (CheckOrElseFunc<ValueT, const ET&, F> ());
	using R = InvokeResult<F, const ET&>;

	return Invoke<R, 1> (std::forward<F> (func), mState);
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
template<typename F>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::TransformError (F&& func) &
{
	static_assert (CheckTransformErrorFunc<ET&, F> ());
	using R = Decay<InvokeResult<F, ET&>>;

	return Invoke<Expected<ValueT, R>, 1> (std::forward<F> (func), mState);
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
template<typename F>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::TransformError (F&& func) &&
{
	static_assert (CheckTransformErrorFunc<ET&&, F> ());
	using R = Decay<InvokeResult<F, ET&&>>;

	return Invoke<Expected<ValueT, R>, 1> (std::forward<F> (func), std::move (mState));
}


template<typename ValueT, typename ErrorT, typename BadAccessPolicy>
template<typename F>
constexpr auto		ExpectedBase<ValueT, ErrorT, BadAccessPolicy>::TransformError (F&& func) const&
{
	static_assert (CheckTransformErrorFunc<const ET&, F> ());
	using R = Decay<InvokeResult<F, const ET&>>;

	return Invoke<Expected<ValueT, R>, 1> (std::forward<F> (func), mState);
}


} // namespace GS::ExpectedImpl


#endif /* GS_EXPECTEDDETAILS_HPP */
