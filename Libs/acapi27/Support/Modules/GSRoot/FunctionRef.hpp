// *****************************************************************************
//
// Contact person: MB, PR
//
// *****************************************************************************

#ifndef GS_FUNCTIONREF_HPP
#define GS_FUNCTIONREF_HPP

#include <cstddef>
#include <type_traits>


namespace GS::FunctionRefImpl {


template<typename>
class FunctionRef;


/* ================================================================================================================== */


template<typename T>
struct IsFunctionRefImpl : std::false_type {};

template<typename R, typename... Args>
struct IsFunctionRefImpl<FunctionRef<R (Args...)>> : std::true_type {};

template<typename R, typename... Args>
struct IsFunctionRefImpl<FunctionRef<R (Args...) const>> : std::true_type {};

template<typename R, typename... Args>
struct IsFunctionRefImpl<FunctionRef<R (Args...) noexcept>> : std::true_type {};

template<typename R, typename... Args>
struct IsFunctionRefImpl<FunctionRef<R (Args...) const noexcept>> : std::true_type {};

template<typename T>
constexpr bool IsFunctionRef = IsFunctionRefImpl<T> ();


/* ================================================================================================================== */


template<typename>
struct SignatureTrait;


template<typename R, typename... Args>
struct SignatureTrait<R (Args...)> final {

	static constexpr bool IsConst    = false;
	static constexpr bool IsNoexcept = false;
};


template<typename R, typename... Args>
struct SignatureTrait<R (Args...) const> final {

	static constexpr bool IsConst    = true;
	static constexpr bool IsNoexcept = false;
};


template<typename R, typename... Args>
struct SignatureTrait<R (Args...) noexcept> final {

	static constexpr bool IsConst    = false;
	static constexpr bool IsNoexcept = true;
};


template<typename R, typename... Args>
struct SignatureTrait<R (Args...) const noexcept> final {

	static constexpr bool IsConst    = true;
	static constexpr bool IsNoexcept = true;
};


/* ================================================================================================================== */


template<bool IsNoexcept, typename R, typename... Args>
using FunctionPtrT = R (*) (Args...) noexcept (IsNoexcept);

template<bool IsNoexcept, typename R, typename... Args>
using CallerPtrT = R (*) (void*, Args...) noexcept (IsNoexcept);


template<bool IsConst, typename T, typename RawT = std::remove_reference_t<T>>
using NonRefT = std::conditional_t<IsConst, std::add_const_t<RawT>, RawT>;


template<bool IsNoexcept, typename R, typename F, typename... Args>
constexpr bool IsCallable = std::conditional_t<
	IsNoexcept,
	typename std::is_nothrow_invocable_r<R, F, Args...>::type,
	typename std::is_invocable_r<R, F, Args...>::type
>::value;


/* === class FunctionRefBase ======================================================================================== */


template<typename Signature, typename RetType, typename... Args>
class FunctionRefBase {

	using Trait       = SignatureTrait<Signature>;
	using FunctionPtr = FunctionPtrT<Trait::IsNoexcept, RetType, Args...>;
	using CallerPtr   = CallerPtrT  <Trait::IsNoexcept, RetType, Args...>;

	void*		mCallable;	// A function pointer, or a pointer to an object which can be called. Type erasure achieved with void*.
	CallerPtr	mCaller;	// Forwards the arguments to 'mCallable' according to its type.

public:

	FunctionRefBase (std::nullptr_t) = delete;

	FunctionRefBase (FunctionPtr) noexcept;

	template<typename F, typename = std::enable_if_t<!IsFunctionRef<std::decay_t<F>> && !std::is_pointer_v<std::decay_t<F>>
													 && IsCallable<Trait::IsNoexcept, RetType, NonRefT<Trait::IsConst, F>&, Args...>>>
	FunctionRefBase (F&&) noexcept;

	RetType		operator() (Args...) const noexcept (Trait::IsNoexcept);
};


/* === class FunctionRefBase implementation ========================================================================= */


template<typename Signature, typename RetType, typename... Args>
FunctionRefBase<Signature, RetType, Args...>::FunctionRefBase (FunctionPtr ptr) noexcept
	: mCallable { reinterpret_cast<void*> (ptr) }
{
	mCaller = [] (void* callable, Args... args) noexcept (Trait::IsNoexcept) -> RetType {
		return reinterpret_cast<FunctionPtr> (callable) (std::forward<Args> (args)...);
	};
}


template<typename Signature, typename RetType, typename... Args>
template<typename F, typename>
FunctionRefBase<Signature, RetType, Args...>::FunctionRefBase (F&& callable) noexcept
	: mCallable { const_cast<void*> (reinterpret_cast<const void*> (&callable)) }
{
	using CallableT = NonRefT<Trait::IsConst, F>;
	static_assert (!std::is_pointer_v<CallableT>);
	static_assert (!std::is_member_function_pointer_v<CallableT>);

	mCaller = [] (void* callable, Args... args) noexcept (Trait::IsNoexcept) -> RetType {
		return reinterpret_cast<CallableT*> (callable)->operator() (std::forward<Args> (args)...);
	};
}


template<typename Signature, typename RetType, typename... Args>
RetType		FunctionRefBase<Signature, RetType, Args...>::operator() (Args... args) const noexcept (Trait::IsNoexcept)
{
	return mCaller (mCallable, std::forward<Args> (args)...);
}


/* === class FunctionRef<RetType (Args...)> ========================================================================= */


template<typename RetType, typename... Args>
class FunctionRef<RetType (Args...)> : private FunctionRefBase<RetType (Args...), RetType, Args...> {

	using Base = FunctionRefBase<RetType (Args...), RetType, Args...>;

public:

	using Base::Base;
	using Base::operator();
};


/* === class FunctionRef<RetType (Args...) const> =================================================================== */


template<typename RetType, typename... Args>
class FunctionRef<RetType (Args...) const> : private FunctionRefBase<RetType (Args...) const, RetType, Args...> {

	using Base = FunctionRefBase<RetType (Args...) const, RetType, Args...>;

public:

	using Base::Base;
	using Base::operator();
};


/* === class FunctionRef<RetType (Args...) noexcept> ================================================================ */


template<typename RetType, typename... Args>
class FunctionRef<RetType (Args...) noexcept> : private FunctionRefBase<RetType (Args...) noexcept, RetType, Args...> {

	using Base = FunctionRefBase<RetType (Args...) noexcept, RetType, Args...>;

public:

	using Base::Base;
	using Base::operator();
};


/* === class FunctionRef<RetType (Args...) const noexcept> ========================================================== */


template<typename RetType, typename... Args>
class FunctionRef<RetType (Args...) const noexcept> : private FunctionRefBase<RetType (Args...) const noexcept, RetType, Args...> {

	using Base = FunctionRefBase<RetType (Args...) const noexcept, RetType, Args...>;

public:

	using Base::Base;
	using Base::operator();
};


} // namespace GS::FunctionRefImpl


namespace GS {
	using FunctionRefImpl::FunctionRef;
}


#endif /* GS_FUNCTIONREF_HPP */
