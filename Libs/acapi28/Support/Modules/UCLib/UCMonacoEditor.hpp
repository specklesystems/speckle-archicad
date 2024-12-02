#ifndef UC_MONACO_EDITOR_HPP
#define UC_MONACO_EDITOR_HPP

#pragma once

#include "UC.h"
#include "DGBrowser.hpp"
#include "Location.hpp"

#include <vector>
#include <memory>
#include <string>

namespace UC {
	class MonacoConnection;
	class MonacoInstaller;
	class MonacoEditorDelegate;
}


namespace UC {


class UC_DLL_EXPORT MonacoEditor : private DG::Browser, public DG::EventTarget
{
public:
	static const GS::UniString PlainText;

	enum class ReadMode {
		Editable,
		ReadOnly
	};

	enum class TextUpdateMode {
		Undoable,
		NotUndoable
	};

	class ContextMenuAction final {
	public:
		static const GS::UniString SeparatorId;
	private:
		GS::UniString actionId;
		std::function<void ()> actionExecutor;

	public:
		explicit	ContextMenuAction (const GS::UniString& actionId);
		ContextMenuAction (const GS::UniString& actionId,
						   const std::function<void ()>& actionExecutor);

		GS::UniString GetActionId () const;

		bool Execute () const;
	};

private:
	GSErrCode InitBrowser ();
	void InitJavaScriptConnection ();
	std::vector<ContextMenuAction> InitDefaultContextMenuActions ();

	void LoadPredefinedLanguages ();
	DG::Browser::KeyEventResult ProcessJavascriptHotkeys (const DG::BrowserBase& browser, const DG::BrowserKeyboardEventArg& arg);
	bool OnContextMenu (const DG::BrowserBase&, const DG::BrowserContextMenuEventArg& arg);
	virtual bool IsLoading () const override;

	const GS::Guid browserId;
	GS::Ref<MonacoConnection> connection;
	std::unique_ptr<const UC::MonacoInstaller> installer;

	ReadMode		readMode	= ReadMode::Editable;
	GS::UniString	language	= GS::EmptyUniString;

	AppearanceType	appearance	= LightAppearance;

	std::vector<ContextMenuAction> contextMenuActions;

public:
	MonacoEditor	(const DG::Panel& panel, short item, ReadMode readMode = ReadMode::Editable);
	MonacoEditor	(const DG::Panel& panel, const DG::Rect& rect, ReadMode readMode = ReadMode::Editable);
	virtual ~MonacoEditor ();

	void SetContextMenuActions (const std::vector<ContextMenuAction>& contextMenuActions);

	const GS::UniString&	GetText () const;
	void	SetText (const GS::UniString& text, const TextUpdateMode& editMode);

			void	Undo ();
			void	Redo ();
	virtual void	Copy () override;
	virtual void	Cut () override;
	virtual void	Paste () override;
			void	SelectAll ();
			void	Find ();
			void	Replace ();

	void	SetReadMode (ReadMode readMode);
	void	SetColorTheme (AppearanceType appearance);
	AppearanceType	GetColorTheme () const;

	GS::Ref<JS::Base> OnCopy (GS::Ref<JS::Base> param);
	GS::Ref<JS::Base> OnPaste (GS::Ref<JS::Base> param);
	GS::Ref<JS::Base> OnCut (GS::Ref<JS::Base> param);
	GS::Ref<JS::Base> OnBrowserZoomLevelChanged (GS::Ref<JS::Base> param);
	GS::Ref<JS::Base> OnEditorZoomLevelChanged (GS::Ref<JS::Base> param);

	void	RegisterLanguage (const GS::UniString& languageName, const std::vector<IO::Location>& languageFiles);

	void	SetLanguage (const GS::UniString& language);
	GS::UniString	GetLanguage () const;

	std::vector<DG::CharRange> GetSelection () const;
	void SetSelection (const std::vector<DG::CharRange>& sel);

	UInt32 GetTabSize () const;
	void SetTabSize (UInt32 tabSize);

	void GoToLine ();

	void AddCommentLine ();
	void RemoveCommentLine ();

	void ShowCommandPalette ();
	void ToggleDarkMode ();
	
			void SetDelegate (std::unique_ptr<MonacoEditorDelegate> delegate);
	virtual void SetFocus () override;
			void ForceTextAreaFocus ();

	void RegisterShortcuts (const GS::UniString& shortcuts);

	void SetEditorZoomLevel (int editorZoomLevel);
	void SetBrowserZoomLevel (double browserZoomLevel);

	const GS::Guid& GetBrowserId () const;

	virtual GSErrCode	Store (GS::ObjectState& os) const override;

	DG::EventNotifier<MonacoEditor, const double> onBrowserZoomLevelChanged;
	DG::EventNotifier<MonacoEditor, const int> onEditorZoomLevelChanged;

	// from DG::ItemBase
	using DG::ItemBase::IsValid;
	using DG::ItemBase::GetPanel;
	using DG::ItemBase::GetPanelId;
	using DG::ItemBase::GetId;

	// from DG::Item
	using DG::Item::HVGrow;
	using DG::Item::HGrow;
	using DG::Item::VGrow;
	using DG::Item::HVMove;
	using DG::Item::VMove;
	using DG::Item::HMove;
	using DG::Item::HGrow_VMove;
	using DG::Item::VGrow_HMove;

	using DG::Item::onContextMenuRequested;
	using DG::Item::onHelpRequested;
	using DG::Item::onToolTipRequested;
	using DG::Item::onClicked;
	using DG::Item::onDoubleClicked;
	using DG::Item::onChanged;
	using DG::Item::onUserDefinedEvent;

	using DG::Item::onResized;
	using DG::Item::onMoved;
	using DG::Item::onVisibilityChanged;

	using DG::Item::Attach;
	using DG::Item::Detach;

	using DG::Item::Show;
	using DG::Item::Hide;
	using DG::Item::SetVisibility;
	using DG::Item::IsVisible;

	using DG::Item::Enable;
	using DG::Item::Disable;
	using DG::Item::SetStatus;
	using DG::Item::IsEnabled;

	using DG::Item::Move;
	using DG::Item::Resize;
	using DG::Item::MoveAndResize;

	using DG::Item::SetPosition;
	using DG::Item::SetRect;
	using DG::Item::SetSize;
	using DG::Item::SetWidth;
	using DG::Item::SetHeight;

	using DG::Item::GetPosition;
	using DG::Item::GetRect;
	using DG::Item::GetWidth;
	using DG::Item::GetHeight;

	using DG::Item::GetContentSize;

	using DG::Item::GetNativeRectInScreenSpace;

	using DG::Item::Invalidate;
	using DG::Item::Redraw;

	using DG::Item::ResetModified;
	using DG::Item::IsModified;

	using DG::Item::SetHelp;
	using DG::Item::GetTooltipString;
	using DG::Item::GetAnchorString;

	using DG::FocusableProperty::SetFocus;
	using DG::FocusableProperty::IsFocused;
};


}

#endif //UC_MONACO_EDITOR_HPP
