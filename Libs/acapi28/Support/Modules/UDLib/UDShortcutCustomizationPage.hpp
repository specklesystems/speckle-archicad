// *****************************************************************************
// File:			UDShortcutCustomizationPage.hpp
//
// Description:		Shortcut Customization dialog
//
// Project:			GRAPHISOFT User Dialog Module (UDLib)
//
// Namespace:		UD
//
// Contact person:	BLA
//
// SG compatible
// *****************************************************************************

#ifndef UDSHORTCUTCUSTOMIZATIONPAGE_HPP
#define UDSHORTCUTCUSTOMIZATIONPAGE_HPP

// --- Includes ----------------------------------------------------------------

#include "EventSource.hpp"
#include "StateEventSource.hpp"
#include "EventObserver.hpp"

#include "UniString.hpp"
#include "DGButton.hpp"
#include "DGPopUp.hpp"
#include "DGPanel.hpp"
#include "DGRadioItem.hpp"
#include "DGEditControl.hpp"
#include "DGListBox.hpp"
#include "DGTreeView.hpp"
#include "DGTabPage.hpp"
#include "DGStaticItem.hpp"

#include "DGCommandDescriptor.hpp"

#include "UDModule.hpp"
#include "UDUtility.hpp"

#include "UDImprovedSearchTextEdit.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class Menu;
	class MenuBar;
	class ShortcutScheme;
}

namespace UD {
	class ShortcutCustomizationPage;
}


// --- Class declarations ------------------------------------------------------

namespace UD {


// --- ShortcutCustomizationPageState ------------------------------------------

class UD_DLL_EXPORT ShortcutCustomizationPageState	:	public GS::StateEventSource
{
private:

public:
	ShortcutCustomizationPageState ();
   ~ShortcutCustomizationPageState ();

	void		SendChange (void);
};


// --- ShortcutCustomizationPageObserver ---------------------------------------

class ShortcutCustomizationPageObserver	:	public DG::TreeViewObserver,
											public DG::PanelObserver,
											public DG::ButtonItemObserver,
											public DG::ListBoxObserver,
											public DG::RadioItemObserver,
											public DG::ShortcutEditObserver,
											public DG::SplitterObserver,
											public DG::CompoundItemObserver,
											public DG::PopUpObserver,
											public UD::ImprovedSearchEditObserver

{
private:
	ShortcutCustomizationPage*		tabPage;

protected:

	virtual void	PanelClosed					(const DG::PanelCloseEvent& ev) override;
	virtual void	PanelOpened					(const DG::PanelOpenEvent& ev) override;
	virtual void	PanelResized				(const DG::PanelResizeEvent& ev) override;
	virtual void	PanelIdle					(const DG::PanelIdleEvent& ev) override;

	virtual void	ButtonClicked				(const DG::ButtonClickEvent& ev) override;
	virtual void	ShortcutHit					(const DG::ShortcutHitEvent& ev) override;
	virtual void	TreeViewSelectionChanged	(const DG::TreeViewSelectionEvent& ev) override;
	virtual void	ListBoxSelectionChanged		(const DG::ListBoxSelectionEvent& ev) override;
	virtual void	RadioItemChanged			(const DG::RadioItemChangeEvent& ev) override;
	virtual void	PopUpChanged				(const DG::PopUpChangeEvent& ev) override;
	virtual void	SplitterDragged				(const DG::SplitterDragEvent& ev) override;
	virtual	void	SearchTextChanged			(const UD::ImprovedSearchEditChangeEvent& ev) override;
	virtual	void	SearchEnded					(const UD::ImprovedSearchEditChangeEvent& ev) override;


public:
	ShortcutCustomizationPageObserver (ShortcutCustomizationPage* shortcutCustomizationPage);
   ~ShortcutCustomizationPageObserver ();
};


// --- ShortcutCustomizationPage -----------------------------------------------

class UD_DLL_EXPORT ShortcutCustomizationPage: public DG::TabPage
{
friend class ShortcutCustomizationPageObserver;

private:
	ShortcutCustomizationPageObserver*	observer;
	ShortcutCustomizationPageState*		pageState;

	// ----- common ------
	enum {
		ApplCmdStaticTextId			= 1,

		CommandPopUpId				= 2,

		CommandTreeViewId			= 3,
		MenuTreeViewId				= 4,
		AllCommandsTreeViewId		= 5,
		AllNewCommandsTreeViewId	= 6,
		CommandInfoStaticTextId		= 7,
		SplitterId					= 8,
		SearchEditId				= 25,
	};

	DG::LeftText			applCmdStaticText;
	UD::ImprovedSearchEdit	searchEdit;

	DG::PopUp				commandPopUp;

	DG::MultiSelTreeView	commandTreeView;
	DG::MultiSelTreeView	menuTreeView;
	DG::MultiSelTreeView	allCommandsTreeView;
	DG::MultiSelTreeView	allNewCommandsTreeView;
	DG::LeftText			commandInfoStaticText;
	DG::Splitter			splitter;

	// ----- shortcut view ------
	enum {
		CreateNewStaticTextId	= 9,

		ShortcutTextId			= 10,
		ShortcutEditId			= 11,

		AssignedTextId			= 12,
		AssignedNothingTextId	= 13,
		AssignedListBoxId		= 14,

		AssignButtonId			= 15,
		AssignAnyWayButtonId	= 16,

		ShortcutsTextId			= 17,
		ShortcutsListBoxId		= 18,
		RemoveShortcutButtonId	= 19,

		WindowTypesGroupId		= 20,
		InfoStaticTextId		= 21,
		AssignToContextRadio	= 22,
		AssignToAllRadio		= 23,
		AssignNoteStaticTextId	= 24
	};

	DG::LeftText			createNewStaticText;

	DG::LeftText			shortcutText;
	DG::ShortcutEdit		shortcutEdit;

	DG::LeftText			assignedText;
	DG::LeftText			assignedNothingText;
	DG::SingleSelListBox	assignedListBox;

	DG::Button				assignButton;
	DG::Button				assignAnyWayButton;

	DG::LeftText			shortcutsText;
	DG::SingleSelListBox	shortcutsListBox;
	DG::Button				removeShortcutButton;

	DG::GroupBox			windowTypesGroup;
	DG::LeftText			infoStaticText;
	DG::RadioButton			assignToContextRadio;
	DG::RadioButton			assignToAllRadio;
	DG::LeftText			assignNoteStaticText;

	GS::Array<DG::Item*>	allShortcutItems;
	GS::Array<DG::Item*>	shortcutItems;

	enum TreeViewType {
		InvalidType		 = -1,
		MenuLayout		 = 1,
		CommandCatalog	 = 2,
		AllCommands		 = 3,
		AllNewCommands	 = 5
	};

	TreeViewType	currentTreeType;

	GS::UniString	commandCatalogFilter;
	GS::UniString	menuLayoutFilter;
	GS::UniString	allCommandsFilter;
	GS::UniString	allNewCommandsFilter;

	bool			commandCatalogFilled;
	bool			menuLayoutFilled;
	bool			allCommandsFilled;
	bool			allNewCommandsFilled;

	GS::UniString	selectedCommandName;

	bool			menuLayoutInited;

	bool			commandsEnabled;
	bool			anchorsEnabled;
	bool			separatorsEnabled;

	// current context guid
	GS::Guid		currentContextGuid;
	GS::Guid		contextGuid;

	// context names
	GS::HashTable<GS::Guid, GS::UniString>	contextNames;

	// the last shortcut's hit data
	DG::Key::Code			hitKey;
	ULong					hitModifiers;

	// the currently selected command or any treeItem's data
	Int32					selectedItemType;
	void*					selectedItemPtr;

	// tree group ids
	const Int32	invalidItemTypeId;
	const Int32	menuItemTypeId;
	const Int32	contextMenuItemTypeId;
	const Int32	anchorItemTypeId;
	const Int32	separatorItemTypeId;
	const Int32	commandItemTypeId;

	Int32		menuGroupTreeItem;
	Int32		contextMenuGroupTreeItem;
	Int32		separatorTreeItem;
	Int32		separatorAllNewCommandsTreeItem;

	GS::HashTable<Int32, void*> commandTreeDescTable;

#if defined (WINDOWS)
	WinImages	winImages;
#endif

	DG::Icon	commandGroupIcon;

	DG::ShortcutScheme*		shortcutScheme;
	const DG::MenuBar*		menuBar;

	static float			splitterRatio;

	ShortcutCustomizationPage (const ShortcutCustomizationPage&);					// disable copy
	ShortcutCustomizationPage&	operator= (const ShortcutCustomizationPage&);		// disable assignment

	// utility functions
	void				ChangeTreeViewType			(TreeViewType treeViewType);
	void				CommandSelectionChanged		(Int32 itemType, void* itemPtr);
	void				AfterShortcutHit			(void);

	GS::UniString		GetContextName				(const GS::Guid& guid) const;

	// treeview functions
	void					DisableAllTreeDraw				(void);
	void					EnableAllTreeDraw				(void);
	void					RedrawTree						(void);

	DG::TreeView&			GetTreeView						(void);
	DG::TreeView&			GetTreeView						(TreeViewType treeViewType);

	Int32					GetSelectedTreeItem				(void);
	Int32					GetSelectedTreeItem				(TreeViewType treeViewType);

	void					GetSelectedTreeItems			(GS::Array<Int32>* itemArray);
	void					GetSelectedTreeItems			(GS::Array<Int32>* itemArray, TreeViewType treeViewType);

	void*					GetSelectedCommand				(Int32* itemType);
	void*					GetSelectedCommand				(Int32 treeItem, Int32* itemType);
	void*					GetSelectedCommand				(TreeViewType treeViewType, Int32 treeItem, Int32* itemType);

	bool					CheckTreeSelection				(const GS::Array<Int32>& items);

	void					TreeViewSelectionChanged		(void);

	void	SetTreeMode				(TreeViewType treeViewType, bool enableCommands, bool enableMenus, bool enableContextMenus, bool enableAnchors, bool enableSeparators);
	void	SetTreeMode				(TreeViewType treeViewType, Int32 parentItem, bool enableCommands, bool enableMenus, bool enableContextMenus, bool enableAnchors, bool enableSeparators);

	void	SetTreeMode				(TreeViewType treeViewType, bool enable, const DG::CommandTable& commands);
	void	SetTreeMode				(TreeViewType treeViewType, bool enable, Int32 parentItem, const DG::CommandTable& commands);

	void	FillCommandTreeView			(void);
	bool	FillMenuTreeView			(Int32 parentItem, DG::Menu* menu, Int32& itemToSelect);
	void	FillFilteredMenuTreeView	(Int32 parentItem, DG::Menu* menu, GS::Array<GS::UniString>& commandNames);
	void	FillMenuTreeView			(void);
	void	FillAllCommandsTreeView		(void);
	void	FillAllNewCommandsTreeView	(void);

	// other item functions
	void	SetStatusOfItems		(GS::Array<DG::Item*>& items, bool status);

	void	SetStatusOfShortcutItems	(bool status);

	// common functions
	void	SetTreeMode			(TreeViewType treeViewType);

	// shortcut functions
	void	SetShortcutTreeView	(void);
	void	SetShortcutTreeView	(TreeViewType treeViewType);
	void	FillShortcutsListBox	(DG::CommandDescriptor* selectedCommandDescriptor);
	void	SetStatusOfShortcutButtons (void);

	// layouting functions
	void	LayoutPage (short pageWidth, float* ratio, short hGrow = 0, short vGrow = 0);

public:
	ShortcutCustomizationPage (const DG::TabControl& tabControl,
							   DG::ShortcutScheme* shortcutScheme,
							   ShortcutCustomizationPageState* pageState,
							   const DG::MenuBar* menuBarParam,
							   const GS::Guid& contextGuid,
							   const GS::HashTable<GS::Guid, GS::UniString>* contextNamesIni);

   ~ShortcutCustomizationPage ();

	static ShortcutCustomizationPage*	Create (const DG::TabControl& tabControl,
												DG::ShortcutScheme* shortcutScheme,
												ShortcutCustomizationPageState* pageState,
												const DG::MenuBar* menuBarParam,
												const GS::Guid& contextGuid,
												const GS::HashTable<GS::Guid, GS::UniString>* contextNames);

	static short	GetOriginalWidth	(void);
	static short	GetOriginalHeight	(void);

	void			RefreshPage			(const GS::Guid& contextGuid, bool contextChange);
};

}	// namespace UD

#endif
