#ifndef UCMONACOCONNECTION_HPP
#define UCMONACOCONNECTION_HPP

#include "UC.h"
#include "JSValues.hpp"
#include "Result.hpp"
#include "JavascriptEngine.hpp"
#include "DGUtility.hpp"

#include <deque>
#include <memory>
#include <optional>
#include <vector>

namespace GS {
	class UniString;
}

namespace UC {
	class MonacoEditorDelegate;
}


namespace UC {

class UC_DLL_EXPORT MonacoConnection : public JS::Object {
public:
	struct KeyBinding {
		DG::Key::Code code;
		DG::Key::Modifier modifier;
		bool operator== (const KeyBinding& op) const;
	};

	struct Action {
		GS::UniString id;
		GS::UniString label;
	};

private:
	enum class MonacoState {
		Uninitialized,
		Created,
		Ready,
	};

	using PostponedJSCodeExecution = GS::UniString;
	std::deque<PostponedJSCodeExecution> queue;

	JavascriptEngine& engine;
	MonacoState monacoState;
	GS::UniString text;
	UInt32 tabSize = 4;
	std::vector<DG::CharRange> selection;
	AppearanceType appearance;
	std::vector<KeyBinding> keyBindings;
	std::vector<Action> actions;
	bool isLoading;

	std::unique_ptr<MonacoEditorDelegate> delegate;

	virtual void FlushQueue ();

	virtual GS::Ref<JS::Base> OnCreated (GS::Ref<JS::Base> param);
	virtual GS::Ref<JS::Base> OnReady (GS::Ref<JS::Base> param);
	virtual GS::Ref<JS::Base> TextChanged (GS::Ref<JS::Base> param);
	virtual GS::Ref<JS::Base> OnSelectionChanged (GS::Ref<JS::Base> param);
	virtual GS::Ref<JS::Base> OnKeyBindingsChanged (GS::Ref<JS::Base> param);
	virtual GS::Ref<JS::Base> OnActionListReceived (GS::Ref<JS::Base> param);
	virtual GS::Ref<JS::Base> GetLocale (GS::Ref<JS::Base> param);
	virtual GS::Ref<JS::Base> SetLoadingState (GS::Ref<JS::Base> param);

	virtual GS::Result<GS::UniString> GetPathForLanguageFileLocation (const IO::Location& loc) const;
	virtual std::optional<KeyBinding> GetKeyBinding (const GS::Ref<JS::Object>& param) const;
	virtual std::optional<Action> GetAction (const GS::Ref<JS::Object>& param) const;

protected:
	virtual void ExecuteCommand (const GS::UniString& jsCode);
	virtual const GS::UniString& GetStringFromJavaScriptVariable (GS::Ref<JS::Base> jsVariable) const;
	virtual GS::UniString ConvertLineEndingsToLF (const GS::UniString& text) const;

public:
	explicit MonacoConnection (JavascriptEngine& engine);
	virtual ~MonacoConnection ();

	virtual void SendText (const GS::UniString& text, bool undoable);
	virtual void RegisterLanguage (const GS::UniString& languageName, const std::vector<IO::Location>& languageFiles);
	virtual void SetLanguage (const GS::UniString& language);
	virtual void SetEditorZoomLevel (int editorZoomLevel);
	virtual void SetReadMode (bool isReadOnly);
	virtual void SetTheme (AppearanceType appearance);
	virtual void SelectAll ();
	virtual void Undo ();
	virtual void Redo ();
	virtual void Find ();
	virtual void Replace ();
	virtual void GoToLine ();
	virtual void AddCommentLine ();
	virtual void RemoveCommentLine ();
	virtual void ShowCommandPalette ();
	virtual void ToggleDarkMode ();
	virtual bool IsLoading () const;
	virtual void RegisterShortcuts (const GS::UniString& shortcuts);

	virtual void TriggerMonacoAction (const GS::UniString& actionID);

	virtual void SetDelegate (std::unique_ptr<MonacoEditorDelegate> delegate);
	virtual void SetFocus ();
	virtual void ForceTextAreaFocus ();
	virtual void CloseCommandPalette ();

	virtual std::vector<DG::CharRange> GetSelection () const;
	virtual void SetSelection (const std::vector<DG::CharRange>& sel);

	virtual UInt32 GetTabSize () const;
	virtual void SetTabSize (UInt32 tabSize);

	virtual const GS::UniString& GetText () const;

	virtual const std::vector<KeyBinding>& GetKeyBindings () const;
	virtual const std::vector<Action>& GetActions () const;
};

}

#endif