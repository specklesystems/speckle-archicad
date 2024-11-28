// license found in the LICENSE file in the same directory as this header.

#pragma once

#include <iostream>
#include <functional>
#include <type_traits>
#include <string>
#include <string_view>

#include "ACAPI/ArchicadAPIExport.hpp"

#include "Definitions.hpp"
#include "APIdefs_Registration.h"


namespace ACAPI {

//! @cond Doxygen_Suppress
namespace types {
	template<typename T>
	struct Ok {
		explicit Ok(const T& val) : val(val) { }
		explicit Ok(T&& val) : val(std::move(val)) { }

		T val;
	};

/// @private
	template<>
	struct Ok<void> { };

/// @private
	template<typename E>
	struct Err {
		Err(const E& val) : val(val) { }
		Err(E&& val) : val(std::move(val)) { }

		E val;
	};
}
//! @endcond


/// @brief Error type for @ref ACAPI::Result containing an error message and an error code
/// @ingroup APIInfrastructure
struct Error {
	/**
	 * @brief Construct a new Error instance.
	 * @param kind Error code.
	 * @param text Detailed description of the error.
	 */
	Error (GSErrCode kind, const std::string& text) : kind (kind), text (text) {}

	/**
	 * @brief Construct a new Error instance.
	 * @param kind Error code.
	 * @param text Detailed description of the error.
	 */
	Error (GSErrCode kind, const std::string_view text) : kind (kind), text (text)	{}

	/**
	 * @brief Construct a new Error instance.
	 * @param kind Error code.
	 * @param text Detailed description of the error.
	 */
	Error (GSErrCode kind, std::string&& text) : kind (kind), text (std::move (text)) {}

	/**
	 * @brief Construct a new Error instance.
	 * @param kind Error code.
	 * @param text Detailed description of the error.
	 */
	Error (GSErrCode kind, const char* text) : kind (kind), text (text) {}

	/**
	 * @brief Comparison operator.
	 * @param rhs The other instance to compare.
	 * @return True if the two instances are equal, otherwise false.
	 */
	bool operator== (const Error& rhs) const {
		return kind == rhs.kind && text == rhs.text;
	}

	/// @private
	GSErrCode kind;
	/// @private
	std::string text;
};

//! @cond Doxygen_Suppress
/// @private
template<typename T, typename CleanT = typename std::decay<T>::type>
types::Ok<CleanT> Ok(T&& val) {
	return types::Ok<CleanT>(std::forward<T>(val));
}

/// @private
inline types::Ok<void> Ok() {
	return types::Ok<void>();
}

/// @private
template<typename E, typename CleanE = typename std::decay<E>::type>
types::Err<CleanE> Err(E&& val) {
	return types::Err<CleanE>(std::forward<E>(val));
}

/// @private
template<typename T, typename E> class Result;

/// @private
namespace details {

/// @private
template<typename ...> struct void_t { typedef void type; };

/// @private
template<typename R>
struct ResultOkType { typedef typename std::decay<R>::type type; };

/// @private
template<typename T, typename E>
struct ResultOkType<Result<T, E>> {
	typedef T type;
};

/// @private
template<typename R>
struct ResultErrType { typedef R type; };

/// @private
template<typename T, typename E>
struct ResultErrType<Result<T, E>> {
	typedef typename std::remove_reference<E>::type type;
};

/// @private
template<typename R> struct IsResult : public std::false_type { };
template<typename T, typename E>
struct IsResult<Result<T, E>> : public std::true_type { };

/// @private
namespace ok {

/// @private
namespace impl {

/// @private
template<typename T> struct Map;

/// @private
template<typename Ret, typename Cls, typename Arg>
struct Map<Ret (Cls::*)(Arg) const> : public Map<Ret (Arg)> { };

/// @private
template<typename Ret, typename Cls, typename Arg>
struct Map<Ret (Cls::*)(Arg)> : public Map<Ret (Arg)> { };

// General implementation
/// @private
template<typename Ret, typename Arg>
struct Map<Ret (Arg)> {

	static_assert(!IsResult<Ret>::value,
			"Can not map a callback returning a Result, use andThen instead");

	template<typename T, typename E, typename Func>
	static Result<Ret, E> map(const Result<T, E>& result, Func func) {

		static_assert(
				std::is_same<T, Arg>::value ||
				std::is_convertible<T, Arg>::value,
				"Incompatible types detected");

		if (result.IsOk()) {
			auto res = func(result.Storage().template get<T>());
			return {types::Ok<Ret>(std::move(res))};
		}

		return {types::Err<E>(result.Storage().template get<E>()), result.Token ()};
	}
};

// Specialization for callback returning void
/// @private
template<typename Arg>
struct Map<void (Arg)> {

	template<typename T, typename E, typename Func>
	static Result<void, E> map(const Result<T, E>& result, Func func) {

		if (result.IsOk()) {
			func(result.Storage().template get<T>());
			return {types::Ok<void>()};
		}

		return {types::Err<E>(result.Storage().template get<E>()), result.Token ()};
	}
};

// Specialization for a void Result
/// @private
template<typename Ret>
struct Map<Ret (void)> {

	template<typename T, typename E, typename Func>
	static Result<Ret, E> map(const Result<T, E>& result, Func func) {
		static_assert(std::is_same<T, void>::value,
				"Can not map a void callback on a non-void Result");

		if (result.IsOk()) {
			auto ret = func();
			return types::Ok<Ret>(std::move(ret));
		}

		return {types::Err<E>(result.Storage().template get<E>()), result.Token ()};
	}
};

// Specialization for callback returning void on a void Result
/// @private
template<>
struct Map<void (void)> {

	template<typename T, typename E, typename Func>
	static Result<void, E> map(const Result<T, E>& result, Func func) {
		static_assert(std::is_same<T, void>::value,
				"Can not map a void callback on a non-void Result");

		if (result.IsOk()) {
			func();
			return {types::Ok<void>()};
		}

		return {types::Err<E>(result.Storage().template get<E>()), result.Token ()};
	}
};

// General specialization for a callback returning a Result
/// @private
template<typename U, typename E, typename Arg>
struct Map<Result<U, E> (Arg)> {

	template<typename T, typename Func>
	static Result<U, E> map(const Result<T, E>& result, Func func) {
		static_assert(
				std::is_same<T, Arg>::value ||
				std::is_convertible<T, Arg>::value,
				"Incompatible types detected");

		if (result.IsOk()) {
			auto res = func(result.Storage().template get<T>());
			return res;
		}

		return {types::Err<E>(result.Storage().template get<E>()), result.Token ()};
	}
};

// Specialization for a void callback returning a Result
/// @private
template<typename U, typename E>
struct Map<Result<U, E> (void)> {

	template<typename T, typename Func>
	static Result<U, E> map(const Result<T, E>& result, Func func) {
		static_assert(std::is_same<T, void>::value, "Can not call a void-callback on a non-void Result");

		if (result.IsOk()) {
			auto res = func();
			return res;
		}

		return {types::Err<E>(result.Storage().template get<E>()), result.Token ()};
	}

};

} // namespace impl

/// @private
template<typename Func> struct Map : public impl::Map<decltype(&Func::operator())> { };

/// @private
template<typename Ret, typename... Args>
struct Map<Ret (*) (Args...)> : public impl::Map<Ret (Args...)> { };

/// @private
template<typename Ret, typename Cls, typename... Args>
struct Map<Ret (Cls::*) (Args...)> : public impl::Map<Ret (Args...)> { };

/// @private
template<typename Ret, typename Cls, typename... Args>
struct Map<Ret (Cls::*) (Args...) const> : public impl::Map<Ret (Args...)> { };

/// @private
template<typename Ret, typename... Args>
struct Map<std::function<Ret (Args...)>> : public impl::Map<Ret (Args...)> { };

} // namespace ok


/// @private
namespace err {

/// @private
namespace impl {

/// @private
template<typename T> struct Map;

/// @private
template<typename Ret, typename Cls, typename Arg>
struct Map<Ret (Cls::*)(Arg) const> {

	static_assert(!IsResult<Ret>::value,
			"Can not map a callback returning a Result, use orElse instead");

/// @private
	template<typename T, typename E, typename Func>
	static Result<T, Ret> map(const Result<T, E>& result, Func func) {
		if (result.IsErr()) {
			auto res = func(result.Storage().template get<E>());
			return types::Err<Ret>(res);
		}

		return types::Ok<T>(result.Storage().template get<T>());
	}

/// @private
	template<typename E, typename Func>
	static Result<void, Ret> map(const Result<void, E>& result, Func func) {
		if (result.IsErr()) {
			auto res = func(result.Storage().template get<E>());
			return types::Err<Ret>(res);
		}

		return {types::Ok<void>(), result.Token ()};
	}


};

} // namespace impl

/// @private
template<typename Func> struct Map : public impl::Map<decltype(&Func::operator())> { };

} // namespace err;

/// @private
namespace And {

/// @private
namespace impl {

/// @private
	template<typename Func> struct Then;

/// @private
	template<typename Ret, typename... Args>
	struct Then<Ret (*)(Args...)> : public Then<Ret (Args...)> { };

/// @private
	template<typename Ret, typename Cls, typename... Args>
	struct Then<Ret (Cls::*)(Args...)> : public Then<Ret (Args...)> { };

/// @private
	template<typename Ret, typename Cls, typename... Args>
	struct Then<Ret (Cls::*)(Args...) const> : public Then<Ret (Args...)> { };

/// @private
	template<typename Ret, typename Arg>
	struct Then<Ret (Arg)> {
		static_assert(std::is_same<Ret, void>::value,
				"then() should not return anything, use map() instead");

/// @private
		template<typename T, typename E, typename Func>
		static Result<T, E> then(const Result<T, E>& result, Func func) {
			if (result.IsOk()) {
				func(result.Storage().template get<T>());
			}
			return result;
		}
	};

/// @private
	template<typename Ret>
	struct Then<Ret (void)> {
		static_assert(std::is_same<Ret, void>::value,
				"then() should not return anything, use map() instead");

/// @private
		template<typename T, typename E, typename Func>
		static Result<T, E> then(const Result<T, E>& result, Func func) {
			static_assert(std::is_same<T, void>::value, "Can not call a void-callback on a non-void Result");

			if (result.IsOk()) {
				func();
			}

			return result;
		}
	};


} // namespace impl

/// @private
template<typename Func>
struct Then : public impl::Then<decltype(&Func::operator())> { };

/// @private
template<typename Ret, typename... Args>
struct Then<Ret (*) (Args...)> : public impl::Then<Ret (Args...)> { };

/// @private
template<typename Ret, typename Cls, typename... Args>
struct Then<Ret (Cls::*)(Args...)> : public impl::Then<Ret (Args...)> { };

/// @private
template<typename Ret, typename Cls, typename... Args>
struct Then<Ret (Cls::*)(Args...) const> : public impl::Then<Ret (Args...)> { };

} // namespace And

/// @private
namespace Or {

/// @private
namespace impl {

/// @private
	template<typename Func> struct Else;

/// @private
	template<typename Ret, typename... Args>
	struct Else<Ret (*)(Args...)> : public Else<Ret (Args...)> { };

/// @private
	template<typename Ret, typename Cls, typename... Args>
	struct Else<Ret (Cls::*)(Args...)> : public Else<Ret (Args...)> { };

/// @private
	template<typename Ret, typename Cls, typename... Args>
	struct Else<Ret (Cls::*)(Args...) const> : public Else<Ret (Args...)> { };

/// @private
	template<typename T, typename F, typename Arg>
	struct Else<Result<T, F> (Arg)> {

/// @private
		template<typename E, typename Func>
		static Result<T, F> orElse(const Result<T, E>& result, Func func) {
			static_assert(
					std::is_same<E, Arg>::value ||
					std::is_convertible<E, Arg>::value,
					"Incompatible types detected");

			if (result.IsErr()) {
				auto res = func(result.Storage().template get<E>());
				return res;
			}

			return {types::Ok<T>(result.Storage().template get<T>())};
		}

/// @private
		template<typename E, typename Func>
		static Result<void, F> orElse(const Result<void, E>& result, Func func) {
			if (result.IsErr()) {
				auto res = func(result.Storage().template get<E>());
				return res;
			}

			return {types::Ok<void>(), result.Token ()};
		}

	};

/// @private
	template<typename T, typename F>
	struct Else<Result<T, F> (void)> {

/// @private
		template<typename E, typename Func>
		static Result<T, F> orElse(const Result<T, E>& result, Func func) {
			static_assert(std::is_same<T, void>::value,
					"Can not call a void-callback on a non-void Result");

			if (result.IsErr()) {
				auto res = func();
				return res;
			}

			return types::Ok<T>(result.Storage().template get<T>());
		}

/// @private
		template<typename E, typename Func>
		static Result<void, F> orElse(const Result<void, E>& result, Func func) {
			if (result.IsErr()) {
				auto res = func();
				return res;
			}

			return {types::Ok<void>(), result.Token ()};
		}

	};

} // namespace impl

/// @private
template<typename Func>
struct Else : public impl::Else<decltype(&Func::operator())> { };

/// @private
template<typename Ret, typename... Args>
struct Else<Ret (*) (Args...)> : public impl::Else<Ret (Args...)> { };

/// @private
template<typename Ret, typename Cls, typename... Args>
struct Else<Ret (Cls::*)(Args...)> : public impl::Else<Ret (Args...)> { };

/// @private
template<typename Ret, typename Cls, typename... Args>
struct Else<Ret (Cls::*)(Args...) const> : public impl::Else<Ret (Args...)> { };

} // namespace Or

/// @private
namespace Other {

/// @private
namespace impl {

/// @private
	template<typename Func> struct Wise;

/// @private
	template<typename Ret, typename... Args>
	struct Wise<Ret (*)(Args...)> : public Wise<Ret (Args...)> { };

/// @private
	template<typename Ret, typename Cls, typename... Args>
	struct Wise<Ret (Cls::*)(Args...)> : public Wise<Ret (Args...)> { };

/// @private
	template<typename Ret, typename Cls, typename... Args>
	struct Wise<Ret (Cls::*)(Args...) const> : public Wise<Ret (Args...)> { };

/// @private
	template<typename Ret, typename Arg>
	struct Wise<Ret (Arg)> {

		template<typename T, typename E, typename Func>
		static Result<T, E> otherwise(const Result<T, E>& result, Func func) {
			static_assert(
					std::is_same<E, Arg>::value ||
					std::is_convertible<E, Arg>::value,
					"Incompatible types detected");

			static_assert(std::is_same<Ret, void>::value,
					"callback should not return anything, use mapError() for that");

			if (result.IsErr()) {
				func(result.Storage().template get<E>());
			}
			return result;
		}

	};

} // namespace impl

/// @private
template<typename Func>
struct Wise : public impl::Wise<decltype(&Func::operator())> { };

/// @private
template<typename Ret, typename... Args>
struct Wise<Ret (*) (Args...)> : public impl::Wise<Ret (Args...)> { };

/// @private
template<typename Ret, typename Cls, typename... Args>
struct Wise<Ret (Cls::*)(Args...)> : public impl::Wise<Ret (Args...)> { };

/// @private
template<typename Ret, typename Cls, typename... Args>
struct Wise<Ret (Cls::*)(Args...) const> : public impl::Wise<Ret (Args...)> { };

} // namespace Other

/// @private
template<typename T, typename E, typename Func,
		 typename Ret =
			Result<
				typename details::ResultOkType<
					std::invoke_result_t<Func, T>
				>::type,
			E>
		>
Ret map(const Result<T, E>& result, Func func) {
	return ok::Map<Func>::map(result, func);
}

/// @private
template<typename T, typename E, typename Func,
		 typename Ret =
			Result<T,
				typename details::ResultErrType<
					std::invoke_result_t<Func, E>
				>::type
			>
		>
Ret mapError(const Result<T, E>& result, Func func) {
	return err::Map<Func>::map(result, func);
}

/// @private
template<typename T, typename E, typename Func>
Result<T, E> then(const Result<T, E>& result, Func func) {
	return And::Then<Func>::then(result, func);
}

/// @private
template<typename T, typename E, typename Func>
Result<T, E> otherwise(const Result<T, E>& result, Func func) {
	return Other::Wise<Func>::otherwise(result, func);
}

/// @private
template<typename T, typename E, typename Func,
	typename Ret =
		Result<T,
			typename details::ResultErrType<
				std::invoke_result_t<Func, E>
			>::type
	   >
>
Ret orElse(const Result<T, E>& result, Func func) {
	return Or::Else<Func>::orElse(result, func);
}

/// @private
struct ok_tag { };
/// @private
struct err_tag { };

/// @private
template<typename T, typename E>
struct Storage {
	static constexpr size_t Size = sizeof(T) > sizeof(E) ? sizeof(T) : sizeof(E);
	static constexpr size_t Align = sizeof(T) > sizeof(E) ? alignof(T) : alignof(E);

	typedef typename std::aligned_storage<Size, Align>::type type;

	Storage()
		: initialized_(false)
	{ }

	void construct(types::Ok<T> ok)
	{
		new (&storage_) T(ok.val);
		initialized_ = true;
	}
	void construct(types::Err<E> err)
	{
		new (&storage_) E(err.val);
		initialized_ = true;
	}

	template<typename U>
	void rawConstruct(U&& val) {
		typedef typename std::decay<U>::type CleanU;

		new (&storage_) CleanU(std::forward<U>(val));
		initialized_ = true;
	}

	template<typename U>
	const U& get() const {
		return *reinterpret_cast<const U *>(&storage_);
	}

	template<typename U>
	U& get() {
		return *reinterpret_cast<U *>(&storage_);
	}

	template<typename U>
	const U* getPtr() const {
		return reinterpret_cast<const U *>(&storage_);
	}

	template<typename U>
	U* getPtr() {
		return reinterpret_cast<U *>(&storage_);
	}

	void destroy(ok_tag) {
		if (initialized_) {
			get<T>().~T();
			initialized_ = false;
		}
	}

	void destroy(err_tag) {
		if (initialized_) {
			get<E>().~E();
			initialized_ = false;
		}
	}

	type storage_;
	bool initialized_;
};

/// @private
template<typename E>
struct Storage<void, E> {
	typedef typename std::aligned_storage<sizeof(E), alignof(E)>::type type;

	void construct(types::Ok<void>)
	{
		initialized_ = true;
	}

	void construct(types::Err<E> err)
	{
		new (&storage_) E(err.val);
		initialized_ = true;
	}

	template<typename U>
	void rawConstruct(U&& val) {
		typedef typename std::decay<U>::type CleanU;

		new (&storage_) CleanU(std::forward<U>(val));
		initialized_ = true;
	}

	void destroy(ok_tag) { initialized_ = false; }
	void destroy(err_tag) {
		if (initialized_) {
			get<E>().~E(); initialized_ = false;
		}
	}

	template<typename U>
	const U& get() const {
		return *reinterpret_cast<const U *>(&storage_);
	}

	template<typename U>
	U& get() {
		return *reinterpret_cast<U *>(&storage_);
	}

	type storage_;
	bool initialized_;
};

/// @private
template<typename T, typename E>
struct Constructor {
	static void move(Storage<T, E>&& src, Storage<T, E>& dst, ok_tag) {
		dst.rawConstruct(std::move(src.template get<T>()));
		src.destroy(ok_tag());
	}

	static void copy(const Storage<T, E>& src, Storage<T, E>& dst, ok_tag) {
		dst.rawConstruct(src.template get<T>());
	}

	static void move(Storage<T, E>&& src, Storage<T, E>& dst, err_tag) {
		dst.rawConstruct(std::move(src.template get<E>()));
		src.destroy(err_tag());
	}

	static void copy(const Storage<T, E>& src, Storage<T, E>& dst, err_tag) {
		dst.rawConstruct(src.template get<E>());
	}
};

/// @private
template<typename E>
struct Constructor<void, E> {
	static void move(Storage<void, E>&&, Storage<void, E>&, ok_tag) {
	}

	static void copy(const Storage<void, E>&, Storage<void, E>&, ok_tag) {
	}

	template <typename U>
	static void move(Storage<U, E>&& src, Storage<void, E>& dst, err_tag) {
		dst.rawConstruct(std::move(src.template get<E>()));
		src.destroy(err_tag());
	}

	template <typename U>
	static void copy(const Storage<U, E>& src, Storage<void, E>& dst, err_tag) {
		dst.rawConstruct(src.template get<E>());
	}
};

} // namespace details

/// @private
namespace concepts {

/// @private
template<typename T, typename = void> struct EqualityComparable : std::false_type { };

/// @private
template<typename T>
struct EqualityComparable<T,
typename std::enable_if<
	true,
	typename details::void_t<decltype(std::declval<T>() == std::declval<T>())>::type
	>::type
> : std::true_type
{
};


} // namespace concepts

/// @private
class ARCHICADAPI_EXPORT ResultBase {
protected:
	void HandleUnwrapFailure (std::string_view errorMessage, const API_Token& token) const;
};
//! @endcond

/// @brief Result is the standard return type of API functions.
/// @ingroup APIInfrastructure
/// @details Result is a value wrapper that can contain an error message and error code if the function failed, or a return value if the function
/// succeeded. It supports advanced functional operations such as Map or Otherwise or can be used as a simple Optional by dereferencing the contained value.
/// Trying to dereference the value while it contains an error will result in crash and should be avoided.
template<typename T, typename E = Error>
class Result : public ResultBase {
public:
	static_assert(!std::is_same<E, void>::value, "void error type is not allowed");

	template <typename T2, typename E2>
	friend class Result;

	/// @private
	typedef details::Storage<T, E> storage_type;

	/**
	 * @brief Construct a new Result instance that contains OK.
	 * @param ok The value which Result will contain.
	 */
	Result(types::Ok<T> ok)
		: ok_(true), token_(APINULLGuid)
	{
		storage_.construct(std::move(ok));
	}

	/**
	 * @brief Construct a new Result instance that contains the specified error.
	 * @param err The specified error.
	 * @param token Token of the add-on.
	 */
	Result(types::Err<E> err, const API_Token& token)
		: ok_(false), token_(token)
	{
		storage_.construct(std::move(err));
	}

	/**
	 * @brief Move constructor of Result.
	 * @param other Other Result instance.
	 */
	Result(Result&& other) {
		if (other.IsOk()) {
			details::Constructor<T, E>::move(std::move(other.storage_), storage_, details::ok_tag());
			ok_ = true;
		} else {
			details::Constructor<T, E>::move(std::move(other.storage_), storage_, details::err_tag());
			ok_ = false;
		}
	}

	/**
	 * @brief Copy constructor of Result.
	 * @param other Other Result instance.
	 */
	Result(const Result& other) {
		if (other.IsOk()) {
			details::Constructor<T, E>::copy(other.storage_, storage_, details::ok_tag());
			ok_ = true;
		} else {
			details::Constructor<T, E>::copy(other.storage_, storage_, details::err_tag());
			ok_ = false;
		}
	}

	/**
	 * @brief Move constructor specialization.
	 * @param other Other Result instance.
	 */
	template <typename U, typename P = T, typename = std::enable_if_t<std::is_void_v<P>>>
	explicit Result(Result<U, E>&& other) {
		if (other.IsOk()) {
			ok_ = true;
		} else {
			details::Constructor<T, E>::move(std::move(other.storage_), storage_, details::err_tag());
			ok_ = false;
		}
	}

	/**
	 * @brief Copy constructor specialization.
	 * @param other Other Result instance.
	 */
	template <typename U, typename P = T, typename = std::enable_if_t<std::is_void_v<P>>>
	explicit Result(const Result<U, E>& other) {
		if (other.IsOk()) {
			ok_ = true;
		} else {
			details::Constructor<T, E>::copy(other.storage_, storage_, details::err_tag());
			ok_ = false;
		}
	}

	~Result() {
		if (ok_)
			storage_.destroy(details::ok_tag());
		else
			storage_.destroy(details::err_tag());
	}

	/// @return True if the result contains a value. False if it contains an error.
	bool IsOk() const {
		return ok_;
	}

	/// @return False if the result contains a value. True if it contains an error.
	bool IsErr() const {
		return !ok_;
	}

	/**
	 * @brief This function will yield the value of an Ok(T).
	 * @details This function will yield the value of an Ok(T) or terminate the program with an error message passed
	 * 			as a parameter. Crashing Archicad may result in disabling the AddOn during the next Archicad startup.
	 * @tparam std::string_view Standard string_view
	 * @param message the error message handed over to the error handler.
	 * @return the value of the Ok(T)
	 * 		   @snippet APIResultTest.cpp Expect example
	 * 		   @snippet APIResultTest.cpp Expect terminate
	 */
	T Expect(std::string_view message) const {
		if (!IsOk()) {
			HandleUnwrapFailure (message, token_);
		}
		return expect_impl(std::is_same<T, void>());
	}

	/**
	 * @brief This function will apply a function to a contained value and will return the result of the transformation. In case the Result
	 * 		  contains an Error, Map does nothing. Note that the passed function should return a simple value and not a Result. If you want to transform
	 * 		  the error result of a function, use MapError.
	 * @tparam Func the type of the function to be applied to the value contained in the Result.
	 * @param func the function to be applied to the value contained in the Result.
	 * @return the result of the transformation applied to the value by the passed function.
	 * 		   @snippet APIResultTest.cpp Map example
	 */
	template<typename Func,
			 typename Ret =
				Result<
					typename details::ResultOkType<
						std::invoke_result_t<Func, T>
					>::type,
				E>
			>
	Ret Map(Func func) const {
		return details::map(*this, func);
	}

	/**
	 * @brief This function will apply a function to a contained error value and will return the result of the transformation.
	 * @details In case the Result contains an Ok value, MapError does nothing. Note that the passed function should return a simple value and not a Result.
	 * @tparam Func the type of the function to be applied to the error value contained in the Result.
	 * @param func the function to be applied to the error value contained in the Result.
	 * @return the result of the transformation applied to the error value by the passed function.
	 * 		   @snippet APIResultTest.cpp MapError example function
	 * 		   @snippet APIResultTest.cpp MapError example
	 */
	template<typename Func,
		 typename Ret =
			 Result<T,
				typename details::ResultErrType<
					std::invoke_result_t<Func, E>
				>::type
			>
	>
	Ret MapError(Func func) const {
		return details::mapError(*this, func);
	}

	/**
	 * @brief This function executes the passed function if the Result contains an Ok value. In case the Result contains an Error value, Then does nothing.
	 * @tparam Func a function with void return type. It gets the value of the Result as a parameter.
	 * @param func The function that is executed if the Result contains an Ok value.
	 * @return The original Result.
	 * 		   @snippet APIResultTest.cpp Then example
	 */
	template<typename Func>
	Result<T, E> Then(Func func) const {
		return details::then(*this, func);
	}

	/**
	 * @brief This function will execute a function if the Result contains an Error value.
	 * @tparam Func a function with void return type. It gets the ACAPI::Error value of the Result as a parameter.
	 * @param func The function that is executed if the Result contains an Error value.
	 * @return The original Result.
	 * 		   @snippet APIResultTest.cpp Otherwise example
	 */
	template<typename Func>
	Result<T, E> Otherwise(Func func) const {
		return details::otherwise(*this, func);
	}

	/**
	 * @brief This function will return the result of a transformation executed on the Error value of the Result, only if the Result contains an Error value.
	 * @tparam Func A function with a Result<T,E> return type. It gets the ACAPI::Result value of the Result as a parameter.
	 * @param func The function that is executed if the Result contains an Error value.
	 * @return The result of the transformation.
	 * 		   @snippet APIResultTest.cpp OrElse example
	 */
	template<typename Func,
		typename Ret =
			Result<T,
				typename details::ResultErrType<
					std::invoke_result_t<Func, E>
				>::type
		   >
	>
	Ret OrElse(Func func) const {
		return details::orElse(*this, func);
	}

	/**
	 * @brief A simple getter for the Token of the AddOn which called the function that returned the Result. Mainly for internal use.
	 * @return The AddOn token.
	 */
	const API_Token& Token() const {
		return token_;
	}

	/**
	 * @brief Unwraps the value contained in the Result. In case the Result contains an Error value, it returns a default value passed in as a parameter.
	 * @tparam U the type of the value of the Result.
	 * @param defaultValue the default value which gets returned if the Result contains an Error.
	 * 					   @snippet APIResultTest.cpp UnwrapOr example
	 * @return The contained value if the Result contains one, or the defaultValue.
	 */
	template<typename U = T>
	const typename std::enable_if_t<!std::is_same_v<U, void>, U>&
	UnwrapOr(const U& defaultValue) const&
	{
		if (IsOk()) {
			return Storage().template get<U>();
		}
		return defaultValue;
	}


	/**
	 * @brief Unwraps the value contained in the Result. Trying to Unwrap the value while it contains an error will
	 * 		  result in crash and should be avoided. Crashing Archicad may result in disabling the AddOn during the next
	 * 		  Archicad startup.
	 * @return The value contained in the Result.
	 * 		   @snippet APIResultTest.cpp Unwrap bad example
	 * 		   @snippet APIResultTest.cpp Unwrap example
	 */
	template <typename U = T>
	typename std::enable_if_t<!std::is_same_v<U, void>, U>&&
	Unwrap () &&
	{
		if (!IsOk ()) {
			using namespace std::literals;
			HandleUnwrapFailure ("Attempting to Unwrap an error Result"sv, token_);
		}
		return std::move(Storage ().template get<U> ());
	}

	/**
	 * @brief Unwraps the value contained in the Result. Trying to Unwrap the value while it contains an error will
	 * 		  result in crash and should be avoided. Crashing Archicad may result in disabling the AddOn during the next
	 * 		  Archicad startup.
	 * @return The value contained in the Result.
	 * 		   @snippet APIResultTest.cpp Unwrap bad example
	 * 		   @snippet APIResultTest.cpp Unwrap example
	 */
	template <typename U = T>
	const typename std::enable_if_t<!std::is_same_v<U, void>, U>&
	Unwrap () const&
	{
		if (!IsOk ()) {
			using namespace std::literals;
			HandleUnwrapFailure ("Attempting to Unwrap an error Result"sv, token_);
		}
		return Storage ().template get<U> ();
	}

	/**
	 * @brief Unwraps the value contained in the Result. Trying to Unwrap the value while it contains an error will
	 * 		  result in crash and should be avoided. Crashing Archicad may result in disabling the AddOn during the next
	 * 		  Archicad startup.
	 * @return The value contained in the Result.
	 * 		   @snippet APIResultTest.cpp Unwrap bad example
	 * 		   @snippet APIResultTest.cpp Unwrap example
	 */
	template <typename U = T>
	typename std::enable_if_t<!std::is_same_v<U, void>, U>&
	Unwrap () &
	{
		if (!IsOk ()) {
			using namespace std::literals;
			HandleUnwrapFailure ("Attempting to Unwrap an error Result"sv, token_);
		}
		return Storage ().template get<U> ();
	}

	/**
	 * @brief Unwraps the error value contained in the Result. Trying to UnwrapErr the value while it contains an Ok value will result in crash and should be avoided.
	 * 		  Crashing Archicad may result in disabling the AddOn during the next Archicad startup.
	 * @return The value contained in the Result.
	 * 		   @snippet APIResultTest.cpp UnwrapErr example
	 */
	E UnwrapErr() const {
		if (!IsErr()) {
			return E (NoError, "NoError");
		}
		return Storage().template get<E>();
	}

	/**
	 * @brief Unwraps the value contained in the Result. Trying to Unwrap the value while it contains an error will result in crash and should be avoided.
	 * 		  Crashing Archicad may result in disabling the AddOn during the next Archicad startup.
	 * @return The value contained in the Result.
	 * 		   @snippet APIResultTest.cpp Dereference example
	 */
	template <typename U = T>
	typename std::enable_if_t<!std::is_same_v<U, void>, U>&
	operator* () &
	{
		return Unwrap ();
	}

	/**
	 * @brief Unwraps the value contained in the Result. Trying to Unwrap the value while it contains an error will
	 * 		  result in crash and should be avoided. Crashing Archicad may result in disabling the AddOn during the next
	 * 		  Archicad startup.
	 * @return The value contained in the Result.
	 * 		   @snippet APIResultTest.cpp Dereference example
	 */
	template <typename U = T>
	typename std::enable_if_t<!std::is_same_v<U, void>, U>&&
	operator* () &&
	{
		return std::move (*this).Unwrap ();
	}

	/**
	 * @brief Unwraps the value contained in the Result. Trying to Unwrap the value while it contains an error will
	 * 		  result in crash and should be avoided. Crashing Archicad may result in disabling the AddOn during the next
	 * 		  Archicad startup.
	 * @return The value contained in the Result.
	 * 		   @snippet APIResultTest.cpp Dereference example
	 */
	template <typename U = T>
	const typename std::enable_if_t<!std::is_same_v<U, void>, U>&
	operator* () const&
	{
		return Unwrap ();
	}

	/**
	 * @brief Unwraps the value contained in the Result and return with a pointer to it.
	 * 		  Trying to Unwrap the value while it contains an error will result in crash and should be avoided.
	 * 		  Crashing Archicad may result in disabling the AddOn during the next Archicad startup.
	 * @return The pointer contained in the Result.
	 */
	template<typename U = T>
	typename std::enable_if<
		!std::is_same<U, void>::value,
		U
	>::type*
	operator-> ()						{
		return Storage().template getPtr<U>();
	}

	/**
	 * @brief Unwraps the value contained in the Result and return with a pointer to it.
	 * 		  Trying to Unwrap the value while it contains an error will result in crash and should be avoided.
	 * 		  Crashing Archicad may result in disabling the AddOn during the next Archicad startup.
	 * @return The pointer contained in the Result.
	 */
	template<typename U = T>
	const typename std::enable_if<
		!std::is_same<U, void>::value,
		U
	>::type*
	operator-> () const					{
		return Storage().template getPtr<U>();
	}

	/**
	 * @brief For internal use only.
	 * @return
	 */
	const storage_type& Storage() const {
		return storage_;
	}

	/**
	 * @brief For internal use only.
	 * @return
	 */
	storage_type& Storage() {
		return storage_;
	}
private:
	T expect_impl(std::true_type) const { }
	T expect_impl(std::false_type) const { return storage_.template get<T>(); }

	bool ok_;
	storage_type storage_;
	API_Token token_;
};

//! \{

template <typename T, typename E>
bool operator== (const Result<T, E> &lhs, const Result<T, E> &rhs)
{
	static_assert(concepts::EqualityComparable<T>::value, "T must be EqualityComparable for Result to be comparable");
	static_assert(concepts::EqualityComparable<E>::value, "E must be EqualityComparable for Result to be comparable");

	if (lhs.IsOk() && rhs.IsOk()) {
		return lhs.Storage().template get<T>() == rhs.Storage().template get<T>();
	}
	if (lhs.IsErr() && rhs.IsErr()) {
		return lhs.Storage().template get<E>() == rhs.Storage().template get<E>();
	}
}

template<typename T, typename E>
bool operator==(const Result<T, E>& lhs, types::Ok<T> ok) {
	static_assert(concepts::EqualityComparable<T>::value, "T must be EqualityComparable for Result to be comparable");

	if (!lhs.IsOk()) return false;

	return lhs.Storage().template get<T>() == ok.val;
}

template<typename E>
bool operator==(const Result<void, E>& lhs, types::Ok<void>) {
	return lhs.IsOk();
}

template<typename T, typename E>
bool operator==(const Result<T, E>& lhs, types::Err<E> err) {
	static_assert(concepts::EqualityComparable<E>::value, "E must be EqualityComparable for Result to be comparable");
	if (!lhs.IsErr()) return false;

	return lhs.Storage().template get<E>() == err.val;
}

//! \}

}