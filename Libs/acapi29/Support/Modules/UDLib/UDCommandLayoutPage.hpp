// *****************************************************************************
// File:			UDCommandLayoutPage.hpp
//
// Description:		Command Layout
//
// Project:			GRAPHISOFT User Dialog Module (UDLib)
//
// Namespace:		UD
//
// Contact person:	BLA
// *****************************************************************************

#ifndef UDCOMMANDLAYOUTPAGE_HPP
#define UDCOMMANDLAYOUTPAGE_HPP

// --- Includes ----------------------------------------------------------------

#include "UDModule.hpp"
#include "UCModule.hpp"

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
#include "DGUserControl.hpp"

#include "DGMenuBar.hpp"
#include "DGMenu.hpp"
#include "DGToolBar.hpp"

#include "DGCommandLayout.hpp"
#include "UCPopup.hpp"
#include "UDUtility.hpp"
#include "UDImprovedSearchTextEdit.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class MenuItem;
	class ToolBarItem;
}

namespace UD {
	class CommandLayoutCustomizationPage;
	class CommandLayoutCustomizationPageData;
}


// --- Class declarations ------------------------------------------------------

namespace UD {

// --- MenuPath ----------------------------------------------------------------

class MenuPath
{
public:
	enum RootType {
		MenuBar,
		ToolBar,
		Global,
		Context
	};

private:
	DG::MenuBar*			menuBarRoot;
	DG::ContextMenu*		contextMenuRoot;
	DG::ToolBar*			toolBarRoot;
	GS::Array<DG::Menu*>	path;

	RootType				type;

public:
	typedef		GS::Array<DG::Menu*>::ConstIterator		ConstIterator;

	MenuPath ();
   ~MenuPath ();

	void		SetRoot			(DG::MenuBar* menuBar);
	void		SetRoot			(DG::ContextMenu* contextMenu);
	void		SetRoot			(DG::ToolBar* toolBar);
	void		SetRoot			(RootType type);
	void		AddPathItem		(DG::Menu* menu);
	void		SetParentPath	(void);

	DG::MenuBar*		GetMenuBarRoot		(void) const;
	DG::ContextMenu*	GetContextMenuRoot	(void) const;
	DG::ToolBar*		GetToolBarRoot		(void) const;
	RootType			GetRootType			(void) const;
	DG::Menu*			GetLastPathItem		(void) const;
	DG::Menu*			GetFirstPathItem	(void) const;
	bool				HasParentPathItem	(void) const;

	ConstIterator		Begin			(void) const;
	ConstIterator		End				(void) const;

	GS::UniString		ToString		(void) const;

	bool				operator==		(const MenuPath& op) const;
};


// --- EditPanelHandler --------------------------------------------------------

class EditPanelHandler
{
protected:
	CommandLayoutCustomizationPage*	tabPage;

	void		SelectListBoxItem		(int item, bool notify = true);

	DG::Menu*	GetSelectedMenu			(void);
	MenuPath	GetSelectedMenuPath		(void);

	void		FillMenuPopup			(void);

public:
		EditPanelHandler (CommandLayoutCustomizationPage* tabPage);

	virtual			~EditPanelHandler ();

	// popup item commands
	virtual	void	New			(bool duplicate = false) = 0;
	virtual	void	Rename		(void) = 0;
	virtual	void	Delete		(void) = 0;

	// buttons
	virtual	void	DragListItem (const short fromItem, const short toItem) = 0;
	virtual	void	Add			(void) = 0;
	virtual	void	Insert		(Int32 treeItem, short insertPosition) = 0;
	virtual void	Insert		(void* itemPtr, Int32 itemType, short insertPosition) = 0;
	virtual	void	Remove		(void) = 0;
	virtual	void	Back		(void) = 0;

	// other
	virtual void	MainPopupChanged	(void) = 0;
	virtual	void	ListBoxDoubleClick	(void) = 0;
	virtual	void	FillMainPopup		(bool selectTop = false) = 0;
	virtual void	FillListBox			(void) = 0;
};


// --- MenuBarEditPanelHandler -------------------------------------------------

class MenuBarEditPanelHandler	:	public EditPanelHandler
{
private:
	void	IterateToMenuBarItem	(DG::MenuBar::ConstIterator* iterator, int index);

public:
		MenuBarEditPanelHandler (CommandLayoutCustomizationPage* tabPage);

	// implements EditPanelHandler
	virtual	void	New			(bool duplicate = false) override;
	virtual	void	Rename		(void) override;
	virtual	void	Delete		(void) override;

	virtual	void	DragListItem (const short fromItem, const short toItem) override;
	virtual	void	Add			(void) override;
	virtual	void	Insert		(Int32 treeItem, short insertPosition) override;
	virtual void	Insert		(void* itemPtr, Int32 itemType, short insertPosition) override;
	virtual	void	Remove		(void) override;
	virtual	void	Back		(void) override;

	virtual void	MainPopupChanged	(void) override;
	virtual	void	ListBoxDoubleClick	(void) override;
	virtual	void	FillMainPopup		(bool selectTop = false) override;
	virtual void	FillListBox			(void) override;
};


// --- MenuEditPanelHandler ----------------------------------------------------

class MenuEditPanelHandler	:	public EditPanelHandler
{
private:
	void		IterateToMenuItem		(DG::Menu::ConstIterator* iterator, int index);
	void		UpdateMainPopup			(void);

public:
		MenuEditPanelHandler (CommandLayoutCustomizationPage* tabPage);

	DG::MenuItem*	SetMenuItemDynamicFlag (bool dynamic);

	// implements EditPanelHandler
	virtual	void	New			(bool duplicate = false) override;
	virtual	void	Rename		(void) override;
	virtual	void	Delete		(void) override;

	virtual	void	DragListItem (const short fromItem, const short toItem) override;
	virtual	void	Add			(void) override;
	virtual	void	Insert		(Int32 treeItem, short insertPosition) override;
	virtual void	Insert		(void* itemPtr, Int32 itemType, short insertPosition) override;
	virtual	void	Remove		(void) override;
	virtual	void	Back		(void) override;

	virtual void	MainPopupChanged	(void) override;
	virtual	void	ListBoxDoubleClick	(void) override;
	virtual	void	FillMainPopup		(bool selectTop = false) override;
	virtual void	FillListBox			(void) override;

	void			InsertMenuAftertSelected (DG::Menu* newMenu);
};


// --- ToolBarEditPanelHandler -------------------------------------------------

class ToolBarEditPanelHandler	:	public EditPanelHandler
{
private:
	enum InputAction {
		NewToolBar,
		DuplicateToolBar,
		RenameToolBar
	};

	struct MenuPathStruct {
		MenuPath	menuPath;
		UIndex		pathIndex;
	};

	static bool		CompareMenuPathStructs (MenuPathStruct s1, MenuPathStruct s2);

	void		IterateToToolBarItem	(DG::ToolBar::ConstIterator* iterator, int index);
	void		UpdateMainPopup			(void);

	bool		ToolBarNameInput (GS::UniString& name, InputAction action) const;

public:
		ToolBarEditPanelHandler (CommandLayoutCustomizationPage* tabPage);

	DG::ToolBarItem*	SetToolBarItemStickyFlag (bool sticky);

	// implements EditPanelHandler
	virtual	void	New			(bool duplicate = false) override;
	virtual	void	Rename		(void) override;
	virtual	void	Delete		(void) override;

	virtual	void	DragListItem (const short fromItem, const short toItem) override;
	virtual	void	Add			(void) override;
	virtual	void	Insert		(Int32 treeItem, short insertPosition) override;
	virtual void	Insert		(void* itemPtr, Int32 itemType, short insertPosition) override;
	virtual	void	Remove		(void) override;
	virtual	void	Back		(void) override;

	virtual void	MainPopupChanged	(void) override;
	virtual	void	ListBoxDoubleClick	(void) override;
	virtual	void	FillMainPopup		(bool selectTop = false) override;
	virtual void	FillListBox			(void) override;
};


// --- CommandLayoutCustomizationPageDataObserver ------------------------------

class CommandLayoutCustomizationPageDataObserver	:	public GS::EventObserver
{
	friend class CommandLayoutCustomizationPageData;

protected:
	virtual void	CommandSelectionChanged		(const CommandLayoutCustomizationPageData& /*pageData*/) {};
	virtual void	MenuItemSelectionChanged	(const CommandLayoutCustomizationPageData& /*pageData*/) {};
	virtual void	ToolBarItemSelectionChanged	(const CommandLayoutCustomizationPageData& /*pageData*/) {};
	virtual void	ToolBarSelectionChanged		(const CommandLayoutCustomizationPageData& /*pageData*/) {};
	virtual	void	CustomizeTypeChanged		(const CommandLayoutCustomizationPageData& /*pageData*/) {};
	virtual	void	SplitterRatioChanged		(const CommandLayoutCustomizationPageData& /*pageData*/) {};

public:
			 CommandLayoutCustomizationPageDataObserver () {};
	virtual ~CommandLayoutCustomizationPageDataObserver ();

};


// --- CommandLayoutCustomizationPageData --------------------------------------

class UD_DLL_EXPORT CommandLayoutCustomizationPageData	: public GS::EventSource
{
private:
	CommandLayoutCustomizationPage*	commandLayoutPage;

	float	splitterRatio;

	void	ProcessCommandSelectionChanged		(void);
	void	ProcessMenuItemSelectionChanged		(void);
	void	ProcessToolBarItemSelectionChanged	(void);
	void	ProcessToolBarSelectionChanged		(void);
	void	ProcessCustomizeTypeChanged			(void);
	void	ProcessSplitterRatioChanged			(void);

public:
	enum CustomizeType {
		Invalid		= 0,
		MenuBar		= 1,
		Menu		= 2,
		ContextMenu	= 3,
		ToolBar		= 4
	};

	CommandLayoutCustomizationPageData ();
   ~CommandLayoutCustomizationPageData ();

	void	Init (CommandLayoutCustomizationPage* commandLayoutPage);

	void	Attach (CommandLayoutCustomizationPageDataObserver& observer);
	void	Detach (CommandLayoutCustomizationPageDataObserver& observer);

	DG::MenuItem*		GetSelectedMenuItem		(void) const;
	DG::ToolBarItem*	GetSelectedToolBarItem	(void) const;
	DG::ToolBar*		GetSelectedToolBar		(void) const;
	CustomizeType		GetCustomizeType		(void) const;

	DG::CommandDescriptor*	GetSelectedCommand	(void) const;

	float				GetSplitterRatio		(void) const;
	void				SetSplitterRatio		(float ratio);

	DG::MenuItem*		SetMenuItemDynamicFlag		(bool dynamic);
	DG::ToolBarItem*	SetToolBarItemStickyFlag	(bool sticky);

	void	SendCommandSelectionChanged		(void);
	void	SendMenuItemSelectionChanged	(void);
	void	SendToolBarItemSelectionChanged	(void);
	void	SendToolBarSelectionChanged		(void);
	void	SendCustomizeTypeChanged		(void);
	void	SendSplitterRatioChanged		(void);
};


// --- CommandLayoutCustomizationPageState -------------------------------------

class UD_DLL_EXPORT CommandLayoutCustomizationPageState: public GS::StateEventSource
{
private:
	bool showContextMenuData;

public:
	CommandLayoutCustomizationPageState (bool showContextMenuData);
   ~CommandLayoutCustomizationPageState ();

	bool	GetContextMenuDataVisibility (void) const;

	void	SendChange (void);
};


// --- CommandLayoutCustomizationPageObserver ----------------------------------

class CommandLayoutCustomizationPageObserver:	public DG::TreeViewObserver,
												public DG::PanelObserver,
												public DG::ButtonItemObserver,
												public DG::TextEditBaseObserver,
												public DG::ListBoxObserver,
												public DG::ListViewObserver,
												public DG::PopUpObserver,
												public DG::UserControlObserver,
												public DG::SplitterObserver,
												public DG::CompoundItemObserver,
												public UD::ImprovedSearchEditObserver

{
private:
	CommandLayoutCustomizationPage*	tabPage;
	bool firstIdle;

protected:
	virtual void	PanelClosed					(const DG::PanelCloseEvent& ev) override;
	virtual void	PanelOpened					(const DG::PanelOpenEvent& ev) override;
	virtual void	PanelResized				(const DG::PanelResizeEvent& ev) override;
	virtual void	PanelResizeExited			(const DG::PanelResizeEvent& ev) override;
	virtual void	PanelIdle					(const DG::PanelIdleEvent& ev) override;

	virtual void	ButtonClicked				(const DG::ButtonClickEvent& ev) override;

	virtual void	TextEditChanged				(const DG::TextEditChangeEvent& ev) override;
	virtual	void	SearchTextChanged			(const UD::ImprovedSearchEditChangeEvent& ev) override;
	virtual	void	SearchEnded					(const UD::ImprovedSearchEditChangeEvent& ev) override;

	virtual void	PopUpChanged				(const DG::PopUpChangeEvent& ev) override;

	virtual void	UserControlChanged			(const DG::UserControlChangeEvent& ev) override;

	virtual void	TreeViewSelectionChanged	(const DG::TreeViewSelectionEvent& ev) override;
	virtual void	TreeViewDragStarting		(const DG::TreeViewDragSourceEvent& ev, bool* canStart) override;
	virtual void	TreeViewDragStarted			(const DG::TreeViewDragSourceEvent& ev, UShort* effect) override;

	virtual void	ListBoxSelectionChanged		(const DG::ListBoxSelectionEvent& ev) override;
	virtual void	ListBoxDoubleClicked		(const DG::ListBoxDoubleClickEvent& ev) override;
	virtual void	ListBoxClicked				(const DG::ListBoxClickEvent& ev) override;
	virtual void	ListBoxMouseMoved			(const DG::ListBoxMouseMoveEvent& ev, short* inArea) override;
	virtual void	ListBoxDragEntered			(const DG::ListBoxDropTargetEvent& ev, DG::DragDrop::Effect* effect, bool* defBehaviour) override;
	virtual void	ListBoxDragMoved			(const DG::ListBoxDropTargetEvent& ev, DG::DragDrop::Effect* effect,
												 DG::DragDrop::Feedback* denyFeedback) override;
	virtual void	ListBoxDragLeft				(const DG::ListBoxDropTargetEvent& ev, DG::DragDrop::Effect* effect) override;
	virtual void	ListBoxDropped				(const DG::ListBoxDropTargetEvent& ev, DG::DragDrop::Effect* effect) override;
	virtual void	ListBoxDragStarting			(const DG::ListBoxDragSourceEvent& ev, bool* canStart) override;
	virtual void	ListBoxDragStarted			(const DG::ListBoxDragSourceEvent& ev, UShort* effect) override;
	virtual void	ListBoxDragEnded			(const DG::ListBoxDragSourceEvent& ev, DG::DragDrop::Effect effect) override;
	virtual void	ListBoxDragSetDelayedData	(const DG::ListBoxDragSourceEvent& ev) override;

	virtual	void	ListBoxItemDragged			(const DG::ListBoxDragEvent& ev) override;

	virtual void	ListViewSelectionChanged	(const DG::ListViewSelectionEvent& ev) override;

	virtual void	SplitterDragged				(const DG::SplitterDragEvent& ev) override;

public:
	CommandLayoutCustomizationPageObserver (CommandLayoutCustomizationPage* tabPageParam);
   ~CommandLayoutCustomizationPageObserver ();
};

// --- CommandLayoutCustomizationPage -------------------------------------------------

class UD_DLL_EXPORT CommandLayoutCustomizationPage: public DG::TabPage
{
	friend class EditPanelHandler;
	friend class CommandLayoutCustomizationPageObserver;
	friend class CommandLayoutCustomizationPageData;
	friend class MenuBarEditPanelHandler;
	friend class MenuEditPanelHandler;
	friend class ToolBarEditPanelHandler;

private:
	CommandLayoutCustomizationPageObserver*	observer;
	CommandLayoutCustomizationPageData*		pageData;
	CommandLayoutCustomizationPageState*	pageState;

	bool								duringChangeCustomizeType;

	GS::Array<EditPanelHandler*>		editPanelHandlers;

	// ----- common ------
	enum {
		CustomizeStaticTextId		= 1,
		SelectorListViewId			= 2,
		MainListBoxEditId			= 3,
		TopSeparatorId				= 4,
		CommandsMenusStaticTextId	= 5,

		CommandPopUpId				= 6,

		CommandTreeViewId			= 7,
		MenuTreeViewId				= 8,
		AllCommandsTreeViewId		= 9,
		AllMenusTreeViewId			= 10,
		AllNewCommandsTreeViewId	= 11,
		CommandInfoStaticTextId		= 12,
		AddButtonId					= 13,

		SplitterId					= 14,
		// ----- other views ------
		BuildComponentStaticTextId	= 15,

		MainPopupId					= 16,

		OptionsUserControlId		= 17,
		BackIconButtonId			= 18,
		MainListBoxId				= 19,
		RemoveButtonId				= 20,

		WindowTypesGroupBoxId		= 21,
		ContextInfoStaticTextId		= 22,
		ContextNoteStaticTextId		= 23,
		SearchTextEditId			= 24
	};

	enum {
		DragColumn					= 1,
		IconColumn					= 2,
		ItemTextColumn				= 3,
		MenuIndicatorColumn			= 4
	};

	DG::LeftText			customizeStaticText;
	DG::SingleSelListView	selectorListView;
	DG::TextEdit			mainListBoxEdit;
	DG::Separator			topSeparator;

	DG::LeftText			commandsMenusStaticText;

	DG::PopUp				commandPopUp;
	DG::MultiSelTreeView	commandTreeView;
	DG::MultiSelTreeView	menuTreeView;
	DG::MultiSelTreeView	allCommandsTreeView;
	DG::MultiSelTreeView	allMenusTreeView;
	DG::MultiSelTreeView	allNewCommandsTreeView;
	DG::LeftText			commandInfoStaticText;
	DG::Button				addButton;

	DG::Splitter			splitter;

	DG::LeftText			buildComponentStaticText;

	DG::PopUp				mainPopup;
	UC::PopupMenu			optionsUserControl;
	DG::IconButton			backIconButton;
	DG::MultiSelListBox		mainListBox;
	DG::Button				removeButton;

	DG::GroupBox			windowTypesGroup;
	DG::LeftText			contextInfoStaticText;
	DG::LeftText			contextNoteStaticText;

	UD::ImprovedSearchEdit	searchEdit;

//	DG::LeftText			toolBarChooseText;

	GS::Array<DG::Item*>	selectorItems;
	GS::Array<DG::Item*>	otherItems;
	GS::Array<DG::Item*>	menuBarTextItems;
	GS::Array<DG::Item*>	menuTextItems;
	GS::Array<DG::Item*>	contextMenuTextItems;
	GS::Array<DG::Item*>	toolBarTextItems;

	// icons
	DG::Icon		menuBarIcon;
	DG::Icon		menuIcon;
	DG::Icon		contextMenuIcon;
	DG::Icon		toolBarIcon;
	DG::Icon		backIcon;
	DG::Icon		commandGroupIcon;
	DG::Icon		menuDownIcon;

	enum TreeViewType {
		InvalidType		= -1,
		MenuLayout		= 1,
		CommandCatalog	= 2,
		AllCommands		= 3,
		AllMenus		= 4,
		AllNewCommands	= 6
	};

	DG::CommandLayout*	commandLayout;

	CommandLayoutCustomizationPageData::CustomizeType	currentCustomizeType;
	CommandLayoutCustomizationPageData::CustomizeType	rootCustomizeType;

	TreeViewType	currentTreeType;
	TreeViewType	savedTreeType;

	GS::UniString   commandCatalogFilter;
	GS::UniString   menuLayoutFilter;
	GS::UniString   allCommandsFilter;
	GS::UniString   allNewCommandsFilter;
	GS::UniString   allMenusFilter;

	bool			commandCatalogFilled;
	bool			menuLayoutFilled;
	bool			allCommandsFilled;
	bool			allNewCommandsFilled;
	bool			allMenusFilled;

	GS::UniString   selectedCommandName;

	bool			menuLayoutInited;

	bool			commandsEnabled;
	bool			menusEnabled;
	bool			contextMenusEnabled;
	bool			anchorsEnabled;
	bool			separatorsEnabled;

	// the currently selected command or any treeItem's data
	Int32		selectedItemType;
	void*		selectedItemPtr;

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
	Int32		separatorMenuLayoutTreeItem;
	Int32		separatorAllCommandsTreeItem;
	Int32		separatorAllMenusTreeItem;
	Int32		separatorAllNewCommandsTreeItem;

	GS::HashTable<Int32, void*> commandTreeDescTable;

	GS::HashTable<Int32, void*> menuLayoutTreeDescTable;

	// menuPath array (the current menu layout's path collection)
	GS::Array<MenuPath>		menuPathes;

	// last selected menuBar
	short	selectedMenuBar;

#if defined (WINDOWS)
	WinImages	winImages;
#endif

	// current splitter ratio - used to avoid unnecessary dialog item fllickering
	float	currentSplitterRatio;

	CommandLayoutCustomizationPage (const CommandLayoutCustomizationPage&);					// disable copy
	CommandLayoutCustomizationPage&	operator= (const CommandLayoutCustomizationPage&);		// disable assignment

	// layout
	void				LayoutPage					(short pageWidth, float* ratio, short hGrow = 0, short vGrow = 0);
	void				Resize						(short dx, short dy);
	void				SetTabFields				(void);

	// utility functions
	void				Refresh						(bool contextChange);

	void				HandleSearchTextChanged		(void);

	bool				InsertMenuIntoMenuArray		(DG::Menu* menu);
	void				DeleteMenuFromMenuArray		(DG::Menu* menu);
	void				RenameMenuInTreeView		(DG::Menu* menu);

	EditPanelHandler*	GetCurrentEditPanelHandler	(void);

	void				MainPopupChanged			(void);
	void				MainListBoxSelectionChanged	(void);
	void				ChangeTreeViewType			(TreeViewType treeViewType);

	void				CommandSelectionChanged		(Int32 itemType, void* itemPtr);

	// selector listview functions
	bool				SetCustomizeType			(CommandLayoutCustomizationPageData::CustomizeType customizeType);

	CommandLayoutCustomizationPageData::CustomizeType		GetRootCustomizeType		(void) const;

	// treeview functions
	void				DisableAllTreeDraw				(void);
	void				EnableAllTreeDraw				(void);
	void				RedrawTree						(void);

	DG::TreeView&		GetTreeView						(void);
	DG::TreeView&		GetTreeView						(TreeViewType treeViewType);

	Int32				GetSelectedTreeItem				(void);
	Int32				GetSelectedTreeItem				(TreeViewType treeViewType);

	void				GetSelectedTreeItems			(GS::Array<Int32>* itemArray);
	void				GetSelectedTreeItems			(GS::Array<Int32>* itemArray, TreeViewType treeViewType);

	void*				GetSelectedCommand				(Int32* itemType);
	void*				GetSelectedCommand				(Int32 treeItem, Int32* itemType, bool* hiddenItem = nullptr);
	void*				GetSelectedCommand				(TreeViewType treeViewType, Int32 treeItem, Int32* itemType, bool* hiddenItem = nullptr);

	bool				CheckTreeSelection				(const GS::Array<Int32>& items);

	void	TreeViewSelectionChanged	(void);

	void	SetTreeMode				(TreeViewType treeViewType, bool enableCommands, bool enableMenus, bool enableContextMenus, bool enableAnchors, bool enableSeparators);
	void	SetTreeMode				(TreeViewType treeViewType, Int32 parentItem, bool enableCommands, bool enableMenus, bool enableContextMenus, bool enableAnchors, bool enableSeparators);

	void	SetTreeMode				(TreeViewType treeViewType, bool enable, const DG::CommandTable& commands);
	void	SetTreeMode				(TreeViewType treeViewType, bool enable, Int32 parentItem, const DG::CommandTable& commands);

	void	FillCommandTreeView			(void);
	bool	FillMenuTreeView			(Int32 parentItem, DG::Menu* menu, Int32& itemToSelect);
	void	FillFilteredMenuTreeView 	(Int32 parentItem, DG::Menu* menu, GS::Array<GS::UniString>& commandNames);
	void	FillMenuTreeView			(void);
	void	FillAllCommandsTreeView		(void);
	void	FillAllNewCommandsTreeView	(void);
	bool	AddSubMenuToAllMenu			(Int32 parentItem, DG::Menu* menu);
	bool	AddFilteredSubMenuToAllMenu	(Int32 parentItem, DG::Menu* menu);
	void	FillAllMenusTreeView	(void);

	// other item functions
	void	SetVisibilityOfItems	(GS::Array<DG::Item*>& items, bool visible);
	void	SetStatusOfItems		(GS::Array<DG::Item*>& items, bool status);

	void	SetStatusOfEditButtons	(void);
	void	FillOptionsUserControl	(CommandLayoutCustomizationPageData::CustomizeType type);

	// change view (called from CustomizeTypeChanged ())
	void	SetMenuBarView		(void);
	void	SetMenuView			(void);
	void	SetContextMenuView	(void);
	void	SetToolBarView		(void);

	// common functions
	void	SetTreeMode			(TreeViewType treeViewType);
	void	SetTextsVisibility	(void);

	// menubar functions
	void	SetMenuBarTreeView			(void);
	void	SetMenuBarTreeView			(TreeViewType treeViewType);
	void	GetRecursiveMenuList		(DG::MenuBar* menuBar, GS::Array<DG::Menu*>* menus, GS::Array<MenuPath>* paths);
	void	ChooseMenuBar				(DG::MenuBar* menuBar);
	void	ChooseListBoxItemMenuBar	(DG::Menu* menu);

	// menu functions
	void	SetMenuTreeView			(void);
	void	SetMenuTreeView			(TreeViewType treeViewType);
	void	CollectMenus			(GS::Array<DG::Menu*>* menuColl, GS::Array<MenuPath>* paths);
	void	GetRecursiveMenuList	(MenuPath basePath, DG::Menu* baseMenu, GS::Array<DG::Menu*>* menus, GS::Array<MenuPath>* paths);
	void	ChooseMenu				(MenuPath menuPath, bool fillList = true);
	void	ChooseListBoxItemMenu	(DG::Menu* menu);
	DG::Menu*	GetEditedMenu		(void);
	bool	CheckInfiniteRecursion	(DG::Menu* insertedMenu, DG::Menu* intoMenu);

	// context menu functions
	void	SetContextMenuTreeView	(void);
	void	SetContextMenuTreeView	(TreeViewType treeViewType);
	void	SetContextMenuTreeView	(const DG::CommandTable& commands);
	void	SetContextMenuTreeView	(TreeViewType treeViewType, const DG::CommandTable& commands);
	void	FilterContextMenuTreeView	(void);

	// toolbar functions
	void	SetToolBarTreeView			(void);
	void	SetToolBarTreeView			(TreeViewType treeViewType);
	void	GetRecursiveMenuList		(DG::ToolBar* toolBar, GS::Array<DG::Menu*>* menus, GS::Array<MenuPath>* paths);
	void	ChooseToolBar				(DG::ToolBar* toolBar);
	void	ChooseListBoxItemToolBar	(DG::Menu* menu);

	// main listbox handling
	void		InitListBoxOnTabItems	(void);
	void		WriteBackEditText		(void);
	DG::Menu*	GetSelectedMenuFromListBox	(void);

	void	AddItem				(const DG::Menu* menu);
	void	InsertItem			(short item, const DG::Menu* menu);
	void	AddItem				(const DG::MenuItem& menuItem);
	void	InsertItem			(short item, const DG::MenuItem& menuItem);
	void	AddItem				(const DG::ToolBarItem& toolBarItem);
	void	InsertItem			(short item, const DG::ToolBarItem& toolBarItem);

	void	RemoveItem			(short item);

	Int32	AddSeparatorItem	(DG::TreeView& treeView);

	void	GetSortedMenus (GS::Array<DG::Menu*>& sortedMenus);
	void	SetCommandPopUpStatus (bool menuBarMode);

protected:
	void	CustomizeTypeChanged	(void);

public:
	static GS::Array<GS::UniString>					ucButtonTexts;

	CommandLayoutCustomizationPage (const DG::TabControl& tabControl,
									CommandLayoutCustomizationPageData* customizationPageData,
									DG::CommandLayout* commandLayoutParam,
									CommandLayoutCustomizationPageState* customizationPageState,
									UIndex activeMenuBar,
									USize contextCount,
									CommandLayoutCustomizationPageData::CustomizeType customizeType);

   ~CommandLayoutCustomizationPage ();

	static CommandLayoutCustomizationPage*	Create (const DG::TabControl& tabControl,
													CommandLayoutCustomizationPageData* customizationPageData,
													DG::CommandLayout* commandLayoutParam,
													CommandLayoutCustomizationPageState* customizationPageState,
													UIndex activeMenuBar,
													USize contextCount,
													CommandLayoutCustomizationPageData::CustomizeType customizeType = CommandLayoutCustomizationPageData::Invalid);

	static short	GetOriginalWidth	(void);
	static short	GetOriginalHeight	(void);

	void			RefreshPage			(const GS::Guid& menuBarGuid, bool contextChange);
	void			SetRootCustomizeType	(CommandLayoutCustomizationPageData::CustomizeType customizeType);
};


// --- CommandLayoutCustomizationExpertPage -----------------------------------------------

class UD_DLL_EXPORT CommandLayoutCustomizationExpertPage : public DG::TabPage,
														   public DG::PanelObserver,
														   public DG::CheckItemObserver,
														   public DG::PopUpObserver,
														   public CommandLayoutCustomizationPageDataObserver,
														   public DG::CompoundItemObserver
{
private:
	// common items
	enum {
		SeparatorId			= 1
	};
	DG::Separator			separator;

	// shortcut view
	enum {
		AllowMultipleCheckId	= 2
	};
	DG::CheckBox			allowMultipleCheck;
	GS::Array<DG::Item*>	shortcutViewItems;

	// menu view
	enum {
		AlternateTextId		= 3,
		AlternateCheckId	= 4
	};
	DG::LeftText			alternateText;
	DG::CheckBox			alternateCheck;
	GS::Array<DG::Item*>	menuViewItems;

	DG::MenuItem*			currentMenuItem;

	// toolbar view
	enum {
		ItemModeCheckId		= 5,
		StickyCheckId		= 6
	};

	DG::CheckBox			itemModeCheck;
	DG::CheckBox			stickyCheck;
	GS::Array<DG::Item*>	toolBarViewTotalItems;
	GS::Array<DG::Item*>	toolBarViewItems;
	GS::Array<DG::Item*>	toolBarItemViewItems;

	DG::ToolBar*			currentToolBar;
	DG::ToolBarItem*		currentToolBarItem;

	CommandLayoutCustomizationPageData*		customizationPageData;
	CommandLayoutCustomizationPageState*	customizationPageState;

	// item functions
	void	SetVisibilityOfItems	(GS::Array<DG::Item*>& items, bool visible);
	void	SetStatusOfItems		(GS::Array<DG::Item*>& items, bool status);

	// layout functions
	void	LayoutPage				(short pageWidth, float ratio, short hGrow = 0, short vGrow = 0);

	// view change functions
	void	SetShortcutView		(void);
	void	SetMenuView			(void);
	void	SetToolBarView		(void);

	void	MenuItemSelectionChanged	(void);
	void	ToolBarItemSelectionChanged	(void);
	void	ToolBarSelectionChanged		(void);

protected:
	virtual void	PanelClosed		(const DG::PanelCloseEvent& ev) override;
	virtual void	PanelOpened		(const DG::PanelOpenEvent& ev) override;
	virtual void	PanelResized	(const DG::PanelResizeEvent& ev) override;
	virtual void	CheckItemChanged (const DG::CheckItemChangeEvent& ev) override;

public:
		CommandLayoutCustomizationExpertPage (const DG::TabControl& tabControl,
											  CommandLayoutCustomizationPageData* customizationPageData,
											  CommandLayoutCustomizationPageState* customizationPageState);

	   ~CommandLayoutCustomizationExpertPage ();

	static CommandLayoutCustomizationExpertPage*	Create (const DG::TabControl& tabControl,
															CommandLayoutCustomizationPageData* customizationPageData,
															CommandLayoutCustomizationPageState* customizationPageState);

	static short	GetOriginalWidth	(void);
	static short	GetOriginalHeight	(void);

	// from CommandLayoutCustomizationPageDataObserver
	virtual void	MenuItemSelectionChanged	(const CommandLayoutCustomizationPageData& pageData) override;
	virtual void	ToolBarItemSelectionChanged	(const CommandLayoutCustomizationPageData& pageData) override;
	virtual void	ToolBarSelectionChanged		(const CommandLayoutCustomizationPageData& pageData) override;
	virtual	void	CustomizeTypeChanged		(const CommandLayoutCustomizationPageData& pageData) override;
	virtual	void	SplitterRatioChanged		(const CommandLayoutCustomizationPageData& pageData) override;
};

}	// namespace UD

#endif
