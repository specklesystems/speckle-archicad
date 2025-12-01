#ifndef GS_UD_SIMPLECONTEXTMENU_HPP
#define GS_UD_SIMPLECONTEXTMENU_HPP

#pragma once

#include "DGCommandDescriptor.hpp"
#include "UDDefinitions.hpp"
#include "Optional.hpp"

namespace DG { class MenuObserver; }
namespace DG { class MenuItem; }
namespace DG { class Menu; }
namespace DG { class TreeViewContextMenuEvent; }

namespace UD {

class UD_DLL_EXPORT SimpleContextMenu {
public:
	typedef std::function<void ()> Function;

	struct UD_DLL_EXPORT Shortcut {
		const DG::Key::Code		code;
		const DG::Key::Modifier	modifier;
		Shortcut (DG::Key::Code code, DG::Key::Modifier	modifier = DG::Key::NoModifier);
	};

	explicit SimpleContextMenu (DG::MenuObserver* observer);

	void AddItem (const GS::UniString&			text,
				  const Function&				fn,
				  bool							isEnabled = true,
				  bool							isChecked = false,
				  const DG::Icon				icon = DG::Icon (),
				  GS::Optional<Shortcut>		shortcut = GS::NoValue);

	void AddItem (const DG::CommandDescriptor*	command,
				  const	Function&				fn,
				  bool							isEnabled = true,
				  GS::Optional<Shortcut>		shortcut = GS::NoValue);

	void AddSeparator ();

	void StartPopupMenu (const GS::UniString& menuName);

	void EndPopupMenu ();

	bool IsEmpty () const;

	void Invoke (const DG::NativePoint& position);

private:
	struct UD_DLL_EXPORT ItemBase {
		Function	fn;

		ItemBase ();
		ItemBase (const Function& fn);

		virtual ~ItemBase ();
		virtual GS::Ref<DG::MenuItem>	RegisterAndBuildUI (DG::CommandTable& enabledCommands) = 0;

	};

	struct UD_DLL_EXPORT SimpleItem : public ItemBase {
	public:
		SimpleItem (UIndex					index,
					const GS::UniString&	text,
					const DG::Icon&			icon,
					const GS::UniString&	description,
					const Function&			fn,
					bool					status,
					bool					isChecked,
					const GS::Optional<Shortcut>& shortcut
		);

		virtual ~SimpleItem ();
		virtual GS::Ref<DG::MenuItem>	RegisterAndBuildUI (DG::CommandTable& enabledCommands) override;

		const UIndex		index;
		const GS::UniString	text;
		const DG::Icon		icon;
		const GS::UniString	description;
		const bool			status;
		const bool			isChecked;
		const GS::Optional<Shortcut>	shortcut;
	};


	struct UD_DLL_EXPORT SeparatorItem : public ItemBase {
	public:
		SeparatorItem ();

		virtual ~SeparatorItem ();
		virtual GS::Ref<DG::MenuItem>	RegisterAndBuildUI (DG::CommandTable& enabledCommands) override;
	};


	struct UD_DLL_EXPORT PopupMenuStartItem : public ItemBase {
	public:
		PopupMenuStartItem (const GS::UniString& menuName);

		virtual ~PopupMenuStartItem ();
		virtual GS::Ref<DG::MenuItem>	RegisterAndBuildUI (DG::CommandTable& enabledCommands) override;

		GS::Ref<DG::Menu> GetPopupMenu ();

	private:
		const GS::UniString menuName;
	};


	struct UD_DLL_EXPORT PopupMenuEndItem : public ItemBase {
	public:
		PopupMenuEndItem ();
		virtual GS::Ref<DG::MenuItem>	RegisterAndBuildUI (DG::CommandTable& enabledCommands) override;

		virtual ~PopupMenuEndItem ();
	};

	GS::Array<GS::Ref<ItemBase>>	items;
	DG::MenuObserver*				observer;
};


class UD_DLL_EXPORT SimpleTreeViewContextMenu : public SimpleContextMenu {
public:
	using SimpleContextMenu::SimpleContextMenu;

	static GS::UniString	GetExpandAllText ();
	static GS::UniString	GetCollapseAllText ();

	bool	Invoke (const DG::TreeViewContextMenuEvent& ev);

	static bool		InvokeStatic (const DG::TreeViewContextMenuEvent& ev);


	virtual ~SimpleTreeViewContextMenu ();
};

} // namespace UD

#endif
