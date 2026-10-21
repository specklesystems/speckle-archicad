// *****************************************************************************
//
// Contact person: MB, PR
//
// *****************************************************************************

#ifndef GS_EXPECTED_HPP
#define GS_EXPECTED_HPP

#include "ExpectedDetails.hpp"


namespace GS::ExpectedImpl {


// === class Expected (ErrCode) ========================================================================================


template<typename V, typename E>
class [[nodiscard]] Expected<V, E, EnableIfNotExceptionType<E>> : private ExpectedBase<V, E, TerminatePolicy> {

	using Base = ExpectedBase<V, E, TerminatePolicy>;

public:

// Construction from value

	constexpr Expected (V&& value);

	constexpr Expected (const V& value);

	template<typename... Args>
	constexpr Expected (std::in_place_type_t<V>, Args&&... valueArgs);

// Construction from error

	constexpr Expected (E&& error);

	constexpr Expected (const E& error);

	template<typename... Args>
	constexpr Expected (std::in_place_type_t<E>, Args&&... errorArgs);

// Construction from throwing Expected

	template<typename OtherE>
	Expected (Expected<V, OtherE>&&) requires (IsErrorType<E> && IsRuntimeError<OtherE>);

	template<typename OtherE>
	Expected (const Expected<V, OtherE>&) requires (IsErrorType<E> && IsRuntimeError<OtherE>);

// Construction by calling AsError on another Expected

	constexpr Expected (ErrorData<E>&&);

// Comparisons

	using		Base::operator==;

	bool		operator== (const Expected&) const requires BothAreEqualityComparable<V, E>;

// Value queries

	using		Base::IsValue;
	using		Base::GetValue;
	using		Base::GetValuePtr;

	using		Base::operator*;
	using		Base::operator->;

	template<typename ExceptionType, typename... Args>
	V&			GetValue (Args&&... exceptionArgs) & gs_lifebound;

	template<typename ExceptionType, typename... Args>
	V&&			GetValue (Args&&... exceptionArgs) && gs_lifebound;

	template<typename ExceptionType, typename... Args>
	const V&	GetValue (Args&&... exceptionArgs) const& gs_lifebound;

// Error queries

	using		Base::IsError;
	using		Base::GetError;
	using		Base::GetErrorPtr;

	using		Base::AsError;

// Monadic operations

	using		Base::AndThen;
	using		Base::Transform;
	using		Base::OrElse;
	using		Base::TransformError;

public:

	using ValueType = V;
	using ErrorType = E;

private:

	template<typename, typename, typename>
	friend class Expected;

	using Base::mState;
};


// === class Expected (ErrCode) implementation =========================================================================


template<typename V, typename E>
constexpr Expected<V, E, EnableIfNotExceptionType<E>>::Expected (V&& value)
	: Base { std::move (value) }
{}


template<typename V, typename E>
constexpr Expected<V, E, EnableIfNotExceptionType<E>>::Expected (const V& value)
	: Base { value }
{}


template<typename V, typename E>
template<typename... Args>
constexpr Expected<V, E, EnableIfNotExceptionType<E>>::Expected (std::in_place_type_t<V>, Args&&... valueArgs)
	: Base { std::in_place_type<V>, std::forward<Args> (valueArgs)... }
{}


template<typename V, typename E>
constexpr Expected<V, E, EnableIfNotExceptionType<E>>::Expected (E&& error)
	: Base { std::move (error) }
{}


template<typename V, typename E>
constexpr Expected<V, E, EnableIfNotExceptionType<E>>::Expected (const E& error)
	: Base { error }
{}


template<typename V, typename E>
template<typename... Args>
constexpr Expected<V, E, EnableIfNotExceptionType<E>>::Expected (std::in_place_type_t<E>, Args&&... errorArgs)
	: Base { std::in_place_type<E>, std::forward<Args> (errorArgs)... }
{}


template<typename V, typename E>
template<typename OtherE>
Expected<V, E, EnableIfNotExceptionType<E>>::Expected (Expected<V, OtherE>&& other) requires (IsErrorType<E> && IsRuntimeError<OtherE>)
	: Base { ToErrVariant<V> (std::move (other)) }
{}


template<typename V, typename E>
template<typename OtherE>
Expected<V, E, EnableIfNotExceptionType<E>>::Expected (const Expected<V, OtherE>& other) requires (IsErrorType<E> && IsRuntimeError<OtherE>)
	: Base { ToErrVariant<V> (other) }
{}


template<typename V, typename E>
constexpr Expected<V, E, EnableIfNotExceptionType<E>>::Expected (ErrorData<E>&& errorData)
	: Base { std::move (errorData.error) }
{}


template<typename V, typename E>
bool	Expected<V, E, EnableIfNotExceptionType<E>>::operator== (const Expected& other) const requires BothAreEqualityComparable<V, E>
{
	if (const V* v1 = GetValuePtr (); v1 != nullptr) {
		const V* v2 = other.GetValuePtr ();
		return (v2 != nullptr) ? *v1 == *v2 : false;
	} else {
		const E* e1 = GetErrorPtr ();
		const E* e2 = other.GetErrorPtr ();
		return (e2 != nullptr) ? *e1 == *e2 : false;
	}
}


template<typename V, typename E>
template<typename ExceptionType, typename... Args>
V&		Expected<V, E, EnableIfNotExceptionType<E>>::GetValue (Args&&... exceptionArgs) &
{
	if (V* value = std::get_if<V> (&mState); value != nullptr)
		return *value;

	throw ExceptionType (std::forward<Args> (exceptionArgs)...);
}


template<typename V, typename E>
template<typename ExceptionType, typename... Args>
V&&		Expected<V, E, EnableIfNotExceptionType<E>>::GetValue (Args&&... exceptionArgs) &&
{
	if (V* value = std::get_if<V> (&mState); value != nullptr)
		return std::move (*value);

	throw ExceptionType (std::forward<Args> (exceptionArgs)...);
}


template<typename V, typename E>
template<typename ExceptionType, typename... Args>
const V&	Expected<V, E, EnableIfNotExceptionType<E>>::GetValue (Args&&... exceptionArgs) const&
{
	if (const V* value = std::get_if<V> (&mState); value != nullptr)
		return *value;

	throw ExceptionType (std::forward<Args> (exceptionArgs)...);
}


// === class Expected<void> (ErrCode) ==================================================================================


template<typename E>
class [[nodiscard]] Expected<void, E, EnableIfNotExceptionType<E>> : private ExpectedBase<void, E, TerminatePolicy> {

	using Base = ExpectedBase<void, E, TerminatePolicy>;

public:

// Construction from value

	Expected () = default;

	constexpr Expected (GS::NoErrorType) noexcept;

// Construction from error

	constexpr Expected (E&& error);

	constexpr Expected (const E& error);

	template<typename... Args>
	constexpr Expected (std::in_place_type_t<E>, Args&&... errorArgs);

// Construction from non-void Expected

	template<typename OtherV>
	constexpr Expected (Expected<OtherV, E>&&) requires (!std::same_as<OtherV, void>);

	template<typename OtherV>
	constexpr Expected (const Expected<OtherV, E>&) requires (!std::same_as<OtherV, void>);

// Construction from throwing Expected

	template<typename OtherV, typename OtherE>
	Expected (Expected<OtherV, OtherE>&&) requires (IsErrorType<E> && IsRuntimeError<OtherE>);

	template<typename OtherV, typename OtherE>
	Expected (const Expected<OtherV, OtherE>&) requires (IsErrorType<E> && IsRuntimeError<OtherE>);

// Construction by calling AsError on another Expected

	constexpr Expected (ErrorData<E>&&);

// Comparisons

	using		Base::operator==;

	bool		operator== (const Expected&) const requires std::equality_comparable<E>;

// Value queries

	using		Base::IsValue;

	void		GetValue (void) const;

	template<typename ExceptionType, typename... Args>
	void		GetValue (Args&&... exceptionArgs) const;

// Error queries

	using		Base::IsError;
	using		Base::GetError;
	using		Base::GetErrorPtr;

	using		Base::AsError;

// Monadic operations

	using		Base::OrElse;
	using		Base::TransformError;

public:

	using ValueType = void;
	using ErrorType = E;

private:

	template<typename, typename, typename>
	friend class Expected;

	template<typename IR, std::size_t, typename IF, typename IV>
	friend constexpr IR ExpectedImpl::Invoke (IF&&, IV&&);

	constexpr Expected (std::monostate) noexcept;

	using Base::mState;
};


// === class Expected<void> (ErrCode) implementation ===================================================================


template<typename E>
constexpr Expected<void, E, EnableIfNotExceptionType<E>>::Expected (GS::NoErrorType) noexcept
{}


template<typename E>
constexpr Expected<void, E, EnableIfNotExceptionType<E>>::Expected (std::monostate) noexcept
{}


template<typename E>
constexpr Expected<void, E, EnableIfNotExceptionType<E>>::Expected (E&& error)
	: Base { std::move (error) }
{}


template<typename E>
constexpr Expected<void, E, EnableIfNotExceptionType<E>>::Expected (const E& error)
	: Base { error }
{}


template<typename E>
template<typename... Args>
constexpr Expected<void, E, EnableIfNotExceptionType<E>>::Expected (std::in_place_type_t<E>, Args&&... errorArgs)
	: Base { std::in_place_type<E>, std::forward<Args> (errorArgs)... }
{}


template<typename E>
template<typename OtherV>
constexpr Expected<void, E, EnableIfNotExceptionType<E>>::Expected (Expected<OtherV, E>&& other) requires (!std::same_as<OtherV, void>)
	: Base { ToVoidVariant<E> (std::move (other.mState)) }
{}


template<typename E>
template<typename OtherV>
constexpr Expected<void, E, EnableIfNotExceptionType<E>>::Expected (const Expected<OtherV, E>& other) requires (!std::same_as<OtherV, void>)
	: Base { ToVoidVariant<E> (other.mState) }
{}


template<typename E>
template<typename OtherV, typename OtherE>
Expected<void, E, EnableIfNotExceptionType<E>>::Expected (Expected<OtherV, OtherE>&& other) requires (IsErrorType<E> && IsRuntimeError<OtherE>)
	: Base { ToErrVariant<std::monostate> (std::move (other)) }
{}


template<typename E>
template<typename OtherV, typename OtherE>
Expected<void, E, EnableIfNotExceptionType<E>>::Expected (const Expected<OtherV, OtherE>& other) requires (IsErrorType<E> && IsRuntimeError<OtherE>)
	: Base { ToErrVariant<std::monostate> (other) }
{}


template<typename E>
constexpr Expected<void, E, EnableIfNotExceptionType<E>>::Expected (ErrorData<E>&& errorData)
	: Base { std::move (errorData.error) }
{}


template<typename E>
bool	Expected<void, E, EnableIfNotExceptionType<E>>::operator== (const Expected& other) const requires std::equality_comparable<E>
{
	if (const E* e1 = GetErrorPtr (); e1 != nullptr) {
		const E* e2 = other.GetErrorPtr ();
		return (e2 != nullptr) ? *e1 == *e2 : false;
	} else {
		return other.IsValue ();
	}
}


template<typename E>
void	Expected<void, E, EnableIfNotExceptionType<E>>::GetValue (void) const
{
	if (IsError ())
		TerminatePolicy::OnBadValueAccess (mState);
}


template<typename E>
template<typename ExceptionType, typename... Args>
void	Expected<void, E, EnableIfNotExceptionType<E>>::GetValue (Args&&... exceptionArgs) const
{
	if (IsError ())
		throw ExceptionType (std::forward<Args> (exceptionArgs)...);
}


// === class Expected (Exception) ======================================================================================


template<typename V, typename E>
class [[nodiscard]] Expected<V, E, EnableIfExceptionType<E>> : private ExpectedBase<V, E, ExceptionPolicy> {

	using Base = ExpectedBase<V, E, ExceptionPolicy>;

public:

// Construction from value

	Expected (V&& value);

	Expected (const V& value);

	template<typename... Args>
	Expected (std::in_place_type_t<V>, Args&&... valueArgs);

// Construction from exception

	Expected (E&&) = delete;

	Expected (const E& exception) noexcept;

	template<std::derived_from<E> ExceptionType, typename... Args>
	Expected (std::in_place_type_t<ExceptionType>, Args&&... exceptionArgs);

// Construction from throwing Expected

	template<typename OtherE>
	Expected (Expected<V, OtherE>&&) requires (!std::same_as<OtherE, E> && std::derived_from<OtherE, E>);

	template<typename OtherE>
	Expected (const Expected<V, OtherE>&) requires (!std::same_as<OtherE, E> && std::derived_from<OtherE, E>);

// Construction from terminating Expected

	Expected (Expected<V, GS::ErrorType>&&) requires std::derived_from<E, GS::RuntimeError>;

	Expected (const Expected<V, GS::ErrorType>&) requires std::derived_from<E, GS::RuntimeError>;

// Construction by calling AsError on another Expected

	template<std::derived_from<E> OtherE>
	Expected (ErrorData<std::exception_ptr, OtherE>&&);

// Comparisons

	using		Base::operator==;

// Value queries

	using		Base::IsValue;
	using		Base::GetValue;
	using		Base::GetValuePtr;

	using		Base::operator*;
	using		Base::operator->;

// Error queries

	using		Base::IsError;

	using		Base::AsError;

	GSErrCode	AsErrCode (void) const noexcept;

// Monadic operations

	using		Base::AndThen;
	using		Base::Transform;

public:

	using ValueType = V;
	using ErrorType = E;

private:

	template<typename, typename, typename>
	friend class Expected;

	template<typename IR, std::size_t, typename IF, typename IV>
	friend constexpr IR ExpectedImpl::Invoke (IF&&, IV&&);

	Expected (std::exception_ptr) noexcept;

	using Base::mState;
};


// === class Expected (Exception) implementation =======================================================================


template<typename V, typename E>
Expected<V, E, EnableIfExceptionType<E>>::Expected (V&& value)
	: Base { std::move (value) }
{}


template<typename V, typename E>
Expected<V, E, EnableIfExceptionType<E>>::Expected (const V& value)
	: Base { value }
{}


template<typename V, typename E>
template<typename... Args>
Expected<V, E, EnableIfExceptionType<E>>::Expected (std::in_place_type_t<V>, Args&&... valueArgs)
	: Base { std::in_place_type<V>, std::forward<Args> (valueArgs)... }
{}


template<typename V, typename E>
Expected<V, E, EnableIfExceptionType<E>>::Expected (const E&) noexcept
	: Base { std::current_exception () }
{
	PRECOND (std::get<1> (mState) != nullptr);
}


template<typename V, typename E>
template<std::derived_from<E> ExceptionType, typename... Args>
Expected<V, E, EnableIfExceptionType<E>>::Expected (std::in_place_type_t<ExceptionType>, Args&&... exceptionArgs)
	: Base { MakeExceptionPtr<ExceptionType> (std::forward<Args> (exceptionArgs)...) }
{}


template<typename V, typename E>
template<typename OtherE>
Expected<V, E, EnableIfExceptionType<E>>::Expected (Expected<V, OtherE>&& other) requires (!std::same_as<OtherE, E> && std::derived_from<OtherE, E>)
	: Base { std::move (other.mState) }
{}


template<typename V, typename E>
template<typename OtherE>
Expected<V, E, EnableIfExceptionType<E>>::Expected (const Expected<V, OtherE>& other) requires (!std::same_as<OtherE, E> && std::derived_from<OtherE, E>)
	: Base { other.mState }
{}


template<typename V, typename E>
Expected<V, E, EnableIfExceptionType<E>>::Expected (Expected<V, GS::ErrorType>&& other) requires std::derived_from<E, GS::RuntimeError>
	: Base { ToExVariant<V, E> (std::move (other)) }
{}


template<typename V, typename E>
Expected<V, E, EnableIfExceptionType<E>>::Expected (const Expected<V, GS::ErrorType>& other) requires std::derived_from<E, GS::RuntimeError>
	: Base { ToExVariant<V, E> (other) }
{}


template<typename V, typename E>
template<std::derived_from<E> OtherE>
Expected<V, E, EnableIfExceptionType<E>>::Expected (ErrorData<std::exception_ptr, OtherE>&& errorData)
	: Base { std::move (errorData.error) }
{}


template<typename V, typename E>
Expected<V, E, EnableIfExceptionType<E>>::Expected (std::exception_ptr ptr) noexcept
	: Base { std::move (ptr) }
{}


template<typename V, typename E>
GSErrCode	Expected<V, E, EnableIfExceptionType<E>>::AsErrCode (void) const noexcept
{
	try {
		GetValue ();
	}
	catch (const GS::RuntimeError& ex) {
		return ex.GetErrCode ();
	}
	catch (...) {
		return GS::Error;
	}

	return GS::NoError;
}


// === class Expected<void> (Exception) ================================================================================


template<typename E>
class [[nodiscard]] Expected<void, E, EnableIfExceptionType<E>> : private ExpectedBase<void, E, ExceptionPolicy> {

	using Base = ExpectedBase<void, E, ExceptionPolicy>;

public:

// Construction from value

	Expected () = default;

	Expected (NoErrorType) noexcept;

// Construction from exception

	Expected (E&&) = delete;

	Expected (const E& exception) noexcept;

	template<std::derived_from<E> ExceptionType, typename... Args>
	Expected (std::in_place_type_t<ExceptionType>, Args&&... exceptionArgs);

// Construction from non-void Expected

	template<typename OtherV, typename OtherE>
	Expected (Expected<OtherV, OtherE>&&) requires (!std::same_as<OtherV, void> && std::derived_from<OtherE, E>);

	template<typename OtherV, typename OtherE>
	Expected (const Expected<OtherV, OtherE>&) requires (!std::same_as<OtherV, void> && std::derived_from<OtherE, E>);

// Construction from terminating Expected

	template<typename OtherV>
	Expected (Expected<OtherV, GS::ErrorType>&&) requires IsRuntimeError<E>;

	template<typename OtherV>
	Expected (const Expected<OtherV, GS::ErrorType>&) requires IsRuntimeError<E>;

// Construction by calling AsError on another Expected

	template<std::derived_from<E> OtherE>
	Expected (ErrorData<std::exception_ptr, OtherE>&&);

// Comparisons

	using		Base::operator==;

// Value queries

	using		Base::IsValue;

	void		GetValue (void) const;

// Error queries

	using		Base::IsError;

	using		Base::AsError;

	GSErrCode	AsErrCode (void) const noexcept;

public:

	using ValueType = void;
	using ErrorType = E;

private:

	template<typename, typename, typename>
	friend class Expected;

	using Base::mState;
};


// === class Expected<void> (Exception) implementation =================================================================


template<typename E>
Expected<void, E, EnableIfExceptionType<E>>::Expected (NoErrorType) noexcept
{}


template<typename E>
Expected<void, E, EnableIfExceptionType<E>>::Expected (const E&) noexcept
	: Base { std::current_exception () }
{
	PRECOND (std::get<1> (mState) != nullptr);
}


template<typename E>
template<std::derived_from<E> ExceptionType, typename... Args>
Expected<void, E, EnableIfExceptionType<E>>::Expected (std::in_place_type_t<ExceptionType>, Args&&... exceptionArgs)
	: Base { MakeExceptionPtr<ExceptionType> (std::forward<Args> (exceptionArgs)...) }
{}


template<typename E>
template<typename OtherV, typename OtherE>
Expected<void, E, EnableIfExceptionType<E>>::Expected (Expected<OtherV, OtherE>&& other) requires (!std::same_as<OtherV, void> && std::derived_from<OtherE, E>)
	: Base { ToVoidVariant (std::move (other.mState)) }
{}


template<typename E>
template<typename OtherV, typename OtherE>
Expected<void, E, EnableIfExceptionType<E>>::Expected (const Expected<OtherV, OtherE>& other) requires (!std::same_as<OtherV, void> && std::derived_from<OtherE, E>)
	: Base { ToVoidVariant (other.mState) }
{}


template<typename E>
template<typename OtherV>
Expected<void, E, EnableIfExceptionType<E>>::Expected (Expected<OtherV, GS::ErrorType>&& other) requires IsRuntimeError<E>
	: Base { ToExVariant<std::monostate, E> (std::move (other)) }
{}


template<typename E>
template<typename OtherV>
Expected<void, E, EnableIfExceptionType<E>>::Expected (const Expected<OtherV, GS::ErrorType>& other) requires IsRuntimeError<E>
	: Base { ToExVariant<std::monostate, E> (other) }
{}


template<typename E>
template<std::derived_from<E> OtherE>
Expected<void, E, EnableIfExceptionType<E>>::Expected (ErrorData<std::exception_ptr, OtherE>&& errorData)
	: Base { std::move (errorData.error) }
{}


template<typename E>
void	Expected<void, E, EnableIfExceptionType<E>>::GetValue (void) const
{
	if (IsError ())
		ExceptionPolicy::OnBadValueAccess (mState);
}


template<typename E>
GSErrCode	Expected<void, E, EnableIfExceptionType<E>>::AsErrCode (void) const noexcept
{
	try {
		GetValue ();
	}
	catch (const GS::RuntimeError& ex) {
		return ex.GetErrCode ();
	}
	catch (...) {
		return GS::Error;
	}

	return GS::NoError;
}


} // namespace GS::ExpectedImpl


namespace GS {
	using ExpectedImpl::Expected;
}


#endif /* GS_EXPECTED_HPP */
