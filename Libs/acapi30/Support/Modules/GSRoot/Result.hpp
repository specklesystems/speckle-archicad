// *****************************************************************************
//
// Contact person: GaGa, MB, PR, BIA
//
// *****************************************************************************

#ifndef GS_RESULT_HPP
#define GS_RESULT_HPP


#include "ResultDetails.hpp"


namespace GS::ResultImpl {


// === class Result ====================================================================================================

template <typename T, typename A>
class Result : private ResultBase<T, A, TerminatePolicy> {
private:

	using Base = ResultBase<T, A, TerminatePolicy>;


public:

	// Types
	using MainType = T;
	using AltType = A;


	// Construction from main value

	constexpr Result (const T& main) noexcept (std::is_nothrow_constructible_v<Base, const T&>);

	constexpr Result (T&& main) noexcept (std::is_nothrow_constructible_v<Base, T&&>);

	template <typename... Args>
	constexpr Result (std::in_place_type_t<T>, Args&&... args) noexcept (std::is_nothrow_constructible_v<Base, std::in_place_type_t<T>, Args...>);


	// Construction from alternative value

	constexpr Result (const A& alternative) noexcept (std::is_nothrow_constructible_v<Base, const A&>);

	constexpr Result (A&& alternative) noexcept (std::is_nothrow_constructible_v<Base, A&&>);

	template <typename... Args>
	constexpr Result (std::in_place_type_t<A>, Args&&... args) noexcept (std::is_nothrow_constructible_v<Base, std::in_place_type_t<A>, Args...>);


	// Main queries

	using Base::IsMain;

	using Base::Get;
	using Base::GetPtr;

	using Base::GetOr;


	// Alternative queries

	using Base::IsAlt;

	using Base::GetAlt;
	using Base::GetAltPtr;

	using Base::GetAltOr;


	// Monadic functions

	using Base::OnMain;
	using Base::OnAlt;


private:

	template <typename, typename>
	friend class Result;

	using Base::mValue;
};


template <typename T, typename A>
constexpr Result<T, A>::Result (const T& main) noexcept (std::is_nothrow_constructible_v<Base, const T&>)
	: Base { main }
{}


template <typename T, typename A>
constexpr Result<T, A>::Result (T&& main) noexcept (std::is_nothrow_constructible_v<Base, T&&>)
	: Base { std::move (main) }
{}


template <typename T, typename A>
template <typename... Args>
constexpr Result<T, A>::Result (std::in_place_type_t<T>, Args&&... args)
noexcept (std::is_nothrow_constructible_v<Base, std::in_place_type_t<T>, Args...>)
	: Base { std::in_place_type<T>, std::forward<Args> (args)... }
{}


template <typename T, typename A>
constexpr Result<T, A>::Result (const A& alternative) noexcept (std::is_nothrow_constructible_v<Base, const A&>)
	: Base { alternative }
{}


template <typename T, typename A>
constexpr Result<T, A>::Result (A&& alternative) noexcept (std::is_nothrow_constructible_v<Base, A&&>)
	: Base { std::move (alternative) }
{}


template <typename T, typename A>
template <typename... Args>
constexpr Result<T, A>::Result (std::in_place_type_t<A>, Args&&... args)
noexcept (std::is_nothrow_constructible_v<Base, std::in_place_type_t<A>, Args...>)
	: Base { std::in_place_type<A>, std::forward<Args> (args)... }
{}


// === class Result<void> ==============================================================================================

template <typename A>
class Result<void, A> : private ResultBase<void, A, TerminatePolicy> {
private:

	using Base = ResultBase<void, A, TerminatePolicy>;


public:

	// Types
	using MainType = void;
	using AltType = A;


	// Construction from main value

	Result () = default;


	// Construction from alternative value

	constexpr Result (const A& alternative) noexcept (std::is_nothrow_constructible_v<Base, const A&>);

	constexpr Result (A&& alternative) noexcept (std::is_nothrow_constructible_v<Base, A&&>);

	template <typename... Args>
	constexpr Result (std::in_place_type_t<A>, Args&&... args) noexcept (std::is_nothrow_constructible_v<Base, std::in_place_type_t<A>, Args...>);

	// Construction from non-void Result

	template <typename OtherT, typename = std::enable_if_t<!std::is_void_v<OtherT>>>
	constexpr Result (const Result<OtherT, A>&);

	template <typename OtherT, typename = std::enable_if_t<!std::is_void_v<OtherT>>>
	constexpr Result (Result<OtherT, A>&&);


	// Main queries

	using Base::IsMain;


	// Alternative queries

	using Base::IsAlt;

	using Base::GetAlt;
	using Base::GetAltPtr;

	using Base::GetAltOr;


	// Monadic functions

	template <typename F>
	constexpr void	OnMain (F&&) const;

	using Base::OnAlt;


private:

	template <typename R, std::size_t, typename F, typename VariantT>
	friend constexpr R Invoke (F&&, VariantT&&);

	constexpr Result (std::monostate) noexcept;
};


template <typename A>
constexpr Result<void, A>::Result (const A& alternative) noexcept (std::is_nothrow_constructible_v<Base, const A&>)
	: Base { alternative }
{}


template <typename A>
constexpr Result<void, A>::Result (A&& alternative) noexcept (std::is_nothrow_constructible_v<Base, A&&>)
	: Base { std::move (alternative) }
{}


template <typename A>
template <typename... Args>
constexpr Result<void, A>::Result (std::in_place_type_t<A>, Args&&... args)
noexcept (std::is_nothrow_constructible_v<Base, std::in_place_type_t<A>, Args...>)
	: Base { std::in_place_type<A>, std::forward<Args> (args)... }
{}


template <typename A>
template <typename OtherT, typename /* SFINAE */>
constexpr Result<void, A>::Result (const Result<OtherT, A>& other)
	: Base { ToVoidVariant<A> (other.mValue) }
{}


template <typename A>
template <typename OtherT, typename /* SFINAE */>
constexpr Result<void, A>::Result (Result<OtherT, A>&& other)
	: Base { ToVoidVariant<A> (std::move (other.mValue)) }
{}


template <typename A>
template <typename F>
constexpr void Result<void, A>::OnMain (F&& func) const
{
	static_assert (CheckOnMainFunc<void, F> ());

	if (IsMain ()) {
		std::invoke (std::forward<F> (func));
	}
}


template <typename A>
constexpr Result<void, A>::Result (std::monostate) noexcept
{}


} // namespace GS::ResultImpl


namespace GS {

using ResultImpl::Result;

} // namespace GS


#endif /* GS_RESULT_HPP */
