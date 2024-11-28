#ifndef MODIFIYSCOPE_HPP
#define MODIFIYSCOPE_HPP

#include "ACAPI/ArchicadAPIExport.hpp"
#include <functional>
#include <string_view>

#include "Object.hpp"
#include "ACAPI/Result.hpp"

using API_Token 	= API_Guid;

namespace ACAPI {


/**
 * @brief Base class of every Modifier classes used in ExecuteUndoableScope/ExecuteNotUndoableScope/CallDefaultModifier function
 * @ingroup Command
 */
class ARCHICADAPI_EXPORT ModifierBase {
public:
	virtual ~ModifierBase ();

protected:
	//! @cond Doxygen_Suppress
	virtual void FinalizeModification ();

	template<typename Modifier, typename UnaryInvocable>
	friend ACAPI::Result<void> ExecuteUndoableScope (const UnaryInvocable&, Modifier&, const ACAPI::Object&, const GS::UniString&);

	template<typename Modifier, typename UnaryInvocable>
	friend ACAPI::Result<void> ExecuteNotUndoableScope (const UnaryInvocable&, Modifier&, const ACAPI::Object&);
	
	template<typename Modifier, typename UnaryInvocable>
	friend ACAPI::Result<void> CallDefaultModifier (UnaryInvocable&&, Modifier&);

	//! @endcond
};


/**
 * @brief It executes the given callback function in an Undoable scope
 * @ingroup Command
 * @param callback The function that will be executed inside the Undoable scope.
 * @param token The token of the add-on that is calling the command.
 * @param undoString The string that will be displayed in the Undo/Redo menu.
 *
 * @return The return type is ACAPI::Result<void>.
 */
ACAPI::Result<void> ARCHICADAPI_EXPORT CallUndoableCommand (const std::function<GSErrCode ()>& callback, const API_Token& token, const GS::UniString& undoString);

//! @cond Doxygen_Suppress
ACAPI::Result<void> ARCHICADAPI_EXPORT CallUndoableModifier (const std::function<GSErrCode ()>& callback, const ACAPI::Object& object, const GS::UniString& undoString);

ACAPI::Result<void> ARCHICADAPI_EXPORT CallNotUndoableModifier (const std::function<GSErrCode ()>& callback, const ACAPI::Object& object);

// template<typename Modifier, typename Ret, typename Impl>
template<typename Modifier, typename UnaryInvocable>
ACAPI::Result<void> ExecuteUndoableScope (const UnaryInvocable& function, Modifier& modifier, const ACAPI::Object& object, const GS::UniString& undoString) {
	using Ret = decltype(std::declval<UnaryInvocable> ().operator () (std::declval<Modifier&>()));
	static_assert (std::is_same_v<Ret, GSErrCode> || std::is_same_v<Ret, void>,
					"This function should return a GSErrCode or void");
	static_assert (std::is_base_of<ModifierBase, Modifier>::value, "Modifier should be a derived class of the ACAPI::ModifierBase");

	auto callback = [&]() -> GSErrCode {
		if constexpr (std::is_same_v<Ret, GSErrCode>) {
			GSErrCode err = function (modifier);
			if (err == NoError)
				static_cast<ModifierBase&> (modifier).FinalizeModification ();

			return err;
		}
		if constexpr (std::is_same_v<Ret, void>) {
			function (modifier);
			static_cast<ModifierBase&> (modifier).FinalizeModification ();
			return NoError;
		}
	};
	return CallUndoableModifier (callback, object, undoString);
}

template<typename Modifier, typename UnaryInvocable>
ACAPI::Result<void> ExecuteNotUndoableScope (const UnaryInvocable& function, Modifier& modifier, const ACAPI::Object& object) {
	using Ret = decltype(std::declval<UnaryInvocable> ().operator () (std::declval<Modifier&>()));
	static_assert (std::is_same_v<Ret, GSErrCode> || std::is_same_v<Ret, void>,
					"This function should return a GSErrCode or void");
	static_assert (std::is_base_of<ModifierBase, Modifier>::value, "Modifier should be a derived class of the ACAPI::ModifierBase");

	auto callback = [&]() -> GSErrCode {
		if constexpr (std::is_same_v<Ret, GSErrCode>) {
			GSErrCode err = function (modifier);
			if (err == NoError)
				static_cast<ModifierBase&> (modifier).FinalizeModification ();

			return err;
		}
		if constexpr (std::is_same_v<Ret, void>) {
			function (modifier);
			static_cast<ModifierBase&> (modifier).FinalizeModification ();
			return NoError;
		}
	};
	return CallNotUndoableModifier (callback, object);
}


template<typename Modifier, typename UnaryInvocable>
ACAPI::Result<void> CallDefaultModifier (UnaryInvocable&& function, Modifier& modifier) {
	using Ret = decltype(std::declval<UnaryInvocable> ().operator () (std::declval<Modifier&>()));
	static_assert (std::is_same_v<Ret, ACAPI::Result<void>> || std::is_same_v<Ret, void>,
				   "This function should return a Result or void");
	static_assert (std::is_base_of<ModifierBase, Modifier>::value, "Modifier should be a derived class of the ACAPI::ModifierBase");

	if constexpr (std::is_same_v<Ret, ACAPI::Result<void>>) {
		ACAPI::Result<void> result = std::forward <UnaryInvocable> (function) (modifier);
		if (result.IsOk ())
			static_cast<ModifierBase&> (modifier).FinalizeModification ();
		return result;
	}

	if constexpr (std::is_same_v<Ret, void>) {
		std::forward <UnaryInvocable> (function) (modifier);
		static_cast<ModifierBase&> (modifier).FinalizeModification ();
		return ACAPI::Ok ();
	}
}

//! @endcond

} // end ACAPI namespace

#endif // MODIFIYSCOPE_HPP
