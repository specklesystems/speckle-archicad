// *****************************************************************************
//
// HTTPClient Optional arguments
//
// Contact person: OA
//
// *****************************************************************************

#ifndef GS_HTTPCLIENT_OPTIONAL_ARGUMENTS_HPP
#define GS_HTTPCLIENT_OPTIONAL_ARGUMENTS_HPP

// from std
#include <type_traits>
#include <utility>
#include <memory>

// from HTTPClient
#include "Content.hpp"
#include "Header.hpp"
#include "Options.hpp"
#include "IRequestProgress.hpp"


namespace HTTPClient {

	template<typename Type, typename ... Types>
	struct OptionalArguments : public OptionalArguments<Type>, public OptionalArguments<Types ...> {

		OptionalArguments () = default;
		OptionalArguments (const OptionalArguments&) = delete;
		OptionalArguments (OptionalArguments&&) = default;

		template<typename ... Args>
		OptionalArguments (Args&& ... args)
		{
			(UnsupportedArgument<std::decay_t<Args>>{}, ...);

			(OptionalArguments<std::decay_t<Args>>::Set (std::forward<Args> (args)), ...);
		}


		template<typename T>
		struct UnsupportedArgument {
			static_assert (std::is_base_of_v<OptionalArguments<T>, OptionalArguments>,
				"Unsupported argument type. "
				"Search the compiler's output for T of UnsupportedArgument<> to find out which argument is wrong.");
		};
	};


	template<>
	struct OptionalArguments<GS::Owner<Content>> {

		GS::Owner<Content> content = nullptr;

	protected:
		void Set (GS::Owner<Content> content)
		{
			this->content = content.Pass ();
		}
	};


	template<>
	struct OptionalArguments<Headers> {

		Headers headers = {};

	protected:
		void Set (const Headers& headers)
		{
			this->headers = headers;
		}

		void Set (Headers&& headers)
		{
			this->headers = std::move (headers);
		}
	};


	template<>
	struct OptionalArguments<Options> {

		Options options = {};

	protected:
		void Set (const Options& options)
		{
			this->options = options;
		}

		void Set (Options&& options)
		{
			this->options = std::move (options);
		}
	};

	template<>
	struct OptionalArguments<std::weak_ptr<IRequestProgress>> {

		std::weak_ptr<IRequestProgress> requestProgress = {};

	protected:
		void Set (const std::weak_ptr<IRequestProgress>& requestProgress)
		{
			this->requestProgress = requestProgress;
		}

		void Set (std::weak_ptr<IRequestProgress>&& requestProgress)
		{
			this->requestProgress = std::move (requestProgress);
		}
	};
}

#endif // GS_HTTPCLIENT_OPTIONAL_ARGUMENTS_HPP