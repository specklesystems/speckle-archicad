// *********************************************************************************************************************
// File:			DGItemEventArgs.hpp
//
// Description:		Dialog manager event handling.
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Contact person:	SZM
// *********************************************************************************************************************

#ifndef DG_ITEM_EVENTARGS_HPP
#define DG_ITEM_EVENTARGS_HPP

#include "Color.hpp"
#include "DGCommonEventArgs.hpp"
#include "UniString.hpp"

struct DGTabulatorItem;

namespace TE {
	class FontFamily;
}

namespace DG {

typedef IntBasedEventArg	ItemClickEventArg;
typedef IntBasedEventArg	ItemDoubleClickEventArg;
typedef IntBasedEventArg	ItemChangeEventArg;
typedef IntBasedEventArg	ItemSelectionChangeEventArg;
typedef IntBasedEventArg	ListViewItemMouseMoveEventArg;
typedef IntBasedEventArg	ListViewItemDoubleClickEventArg;
typedef IntBasedEventArg	ListViewItemPressEventArg;
typedef IntBasedEventArg	TreeViewClickEventArg;
typedef IntBasedEventArg	TreeViewDoubleClickEventArg;
typedef IntBasedEventArg	ItemTrackEventArg;
typedef IntBasedEventArg	FilterCharEventArg;


// --- DoubleBasedEventArg ---------------------------------------------------------------------------------------------

class DG_DLL_EXPORT DoubleBasedEventArg: public EventArg
{
	double doubleData = 0.0;

public:
	DoubleBasedEventArg () = default;
	DoubleBasedEventArg (double data);
	virtual ~DoubleBasedEventArg ();

	virtual operator double() const override;
};


// --- MoveEventArg -------------------------------------------------------------------------------------------

class DG_DLL_EXPORT MoveEventArg: public EventArg
{
public:
	short	dx = 0;
	short	dy = 0;

	virtual ~MoveEventArg ();
};


// --- ItemFocusChangeEventArg -----------------------------------------------------------------------------------------

class DG_DLL_EXPORT ItemFocusChangeEventArg: public IntBasedEventArg
{
public:
	static ItemFocusChangeEventArg FocusLost;
	static ItemFocusChangeEventArg FocusGained;

	ItemFocusChangeEventArg (Int32 changeType);
	virtual ~ItemFocusChangeEventArg ();
};


// --- VisibilityChangeEventArg ----------------------------------------------------------------------------------------
class DG_DLL_EXPORT VisibilityChangeEventArg: public IntBasedEventArg
{
public:
	static VisibilityChangeEventArg BecameHidden;
	static VisibilityChangeEventArg BecameVisible;

private:
	VisibilityChangeEventArg (Int32 visibilityType);

public:
	virtual ~VisibilityChangeEventArg ();
};


// --- Listbox ---------------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ListBoxItemMouseEventArg: public EventArg
{
public:
	short			pressedItem = 0;		// One-base index of item
	bool			isHovered = 0;
	short			tabIndex = 0;			// One-base index of the tabulator field
	short			xPos = 0;				// Horizontal mouse position relative to the list item rect
	short			yPos = 0;				// Vertical mouse position relative to the list item rect
	short			keyFlag = 0;			// DG_MOD_COMMAND, DG_MOD_OPTION, DG_MOD_SHIFT

	ListBoxItemMouseEventArg ();
	virtual ~ListBoxItemMouseEventArg ();
};


class DG_DLL_EXPORT ListBoxHeaderEventArg: public EventArg
{
public:
	short			subMessage = 0;				// 0, DG_LHM_RESIZEENTER, DG_LHM_RESIZING, DG_LHM_RESIZEEXIT
	short			itemIndex = 0;				// 1-based index of the clicked, dragged or resized header item
	short			newIndex = 0;				// 1-based new index of the dragged header item
	short			growSize = 0;				// Size change of the resized header item

	ListBoxHeaderEventArg ();
	ListBoxHeaderEventArg (short subMessage, short itemIndex, short newIndex, short	growSize);
	virtual ~ListBoxHeaderEventArg ();
};


class DG_DLL_EXPORT ListBoxItemHoverEventArg: public IntBasedEventArg
{
public:
	Int32			listItem = 0;			// One-base index of the list item

	ListBoxItemHoverEventArg (Int32 listItem);
	virtual ~ListBoxItemHoverEventArg ();
};


class ListBoxUpdateEventArg;

class ListBoxNotifyHandler
{
public:
	virtual ~ListBoxNotifyHandler ();

	virtual void	NotifyItemClickEvent (const ListBoxItemMouseEventArg& /*eventArg*/) = 0;
	virtual void	NotifyItemDoubleClickEvent (const ListBoxItemMouseEventArg& /*eventArg*/) = 0;
	virtual short	NotifyItemMouseMoveEvent (const ListBoxItemMouseEventArg& /*eventArg*/) = 0;
	virtual bool	NotifyItemMouseDownEvent (const ListBoxItemMouseEventArg& /*eventArg*/) = 0;

	virtual void	NotifyHeaderItemClickEvent (const ListBoxHeaderEventArg& /*eventArg*/) = 0;
	virtual void	NotifyHeaderItemDragEvent (const ListBoxHeaderEventArg& /*eventArg*/) = 0;
	virtual short	NotifyHeaderItemResizeEnterEvent (const ListBoxHeaderEventArg& /*eventArg*/) = 0;
	virtual short	NotifyHeaderItemResizeEvent (const ListBoxHeaderEventArg& /*eventArg*/) = 0;
	virtual short	NotifyHeaderItemResizeExitEvent (const ListBoxHeaderEventArg& /*eventArg*/) = 0;
	virtual void	NotifyHeaderButtonClickEvent (const ListBoxHeaderEventArg& /*eventArg*/) = 0;

	virtual short	NotifyItemHoverStartEvent (const ListBoxItemHoverEventArg& /*eventArg*/) = 0;
	virtual short	NotifyItemHoverEndEvent (const ListBoxItemHoverEventArg& /*eventArg*/) = 0;

	virtual bool	NotifySelectionChangeRequestEvent (const ListBoxItemMouseEventArg& /*eventArg*/) = 0;
	virtual void	NotifySelectionChangeEvent (const ItemSelectionChangeEventArg& /*eventArg*/) = 0;

	virtual void	NotifyItemUpdateEvent (ListBoxUpdateEventArg& /*eventArg*/) = 0;
	virtual void	NotifyItemOverlayUpdateEvent (const ListBoxUpdateEventArg& /*eventArg*/) = 0;
};


// --- ListView --------------------------------------------------------------------------------------------------------

class ListViewUpdateEventArg;

class DG_DLL_EXPORT ListViewItemMouseEventArg : public EventArg
{
public:
	short			pressedItem = 0;		// One-base index of item
	bool			isHovered = 0;


	ListViewItemMouseEventArg ();
	virtual ~ListViewItemMouseEventArg ();
};


class DG_DLL_EXPORT ListViewItemHoverEventArg: public IntBasedEventArg
{
public:
	Int32			listItem = 0;			// One-base index of the list item

	ListViewItemHoverEventArg (Int32 listItem);
	virtual ~ListViewItemHoverEventArg ();
};


class ListViewNotifyHandler
{
public:
	virtual ~ListViewNotifyHandler ();

	virtual bool	NotifyItemMouseDownEvent (const ListViewItemMouseEventArg& /*eventArg*/) = 0;
	virtual bool	NotifySelectionChangeRequestEvent (const ListViewItemMouseEventArg& /*eventArg*/) = 0;

	virtual void	NotifyItemUpdateEvent (ListViewUpdateEventArg& /*eventArg*/) = 0;
	virtual void	NotifyItemOverlayUpdateEvent (const ListViewUpdateEventArg& /*eventArg*/) = 0;

	virtual short	NotifyItemMouseMoveEvent (const ListViewItemMouseMoveEventArg& /*eventArg*/) = 0;
	virtual short	NotifyItemDoubleClickEvent (const ListViewItemDoubleClickEventArg& /*eventArg*/) = 0;

	virtual short	NotifyItemHoverStartEvent (const ListViewItemHoverEventArg& /*eventArg*/) = 0;
	virtual short	NotifyItemHoverEndEvent (const ListViewItemHoverEventArg& /*eventArg*/) = 0;

	virtual short	NotifyItemPressEvent (const ListViewItemPressEventArg& /*eventArg*/) = 0;
};


// --- UserItem --------------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT UserItemMouseEventArg: public EventArg
{
public:
	short			left;					// Client rect left position in dialog coordinates
	short			top;					// Client rect top position in dialog coordinates
	short			right;					// Client rect right position in dialog coordinates
	short			bottom;					// Client rect bottom position in dialog coordinates
	short			xPos;					// Horizontal mouse position relative to the user item client rect
	short			yPos;					// Vertical mouse position relative to the user item client rect
	short			keyFlag;				// DG_MOD_COMMAND, DG_MOD_OPTION, DG_MOD_SHIFT
	short			buttonFlag;				// DG_BUTTON_LEFT, DG_BUTTON_RIGHT, DG_BUTTON_WHEEL

	UserItemMouseEventArg ();
	virtual ~UserItemMouseEventArg ();
};


class DG_DLL_EXPORT UserItemResolutionChangeEventArg: public EventArg
{
public:
	double			oldResolutionFactor;
	UserItemResolutionChangeEventArg ();
	UserItemResolutionChangeEventArg (double oldResolutionFactor);
	~UserItemResolutionChangeEventArg ();
};


class UserItemUpdateEventArg;

class UserItemNotifyHandler
{
public:
	virtual ~UserItemNotifyHandler ();

	virtual short	NotifyMouseDownEvent (const UserItemMouseEventArg& /*eventArg*/) = 0;
	virtual void	NotifyDoubleClickEvent (const UserItemMouseEventArg& /*eventArg*/) = 0;
	virtual short	NotifyMouseUpEvent (const UserItemMouseEventArg& /*eventArg*/) = 0;
	virtual short	NotifyMouseMoveEvent (const UserItemMouseEventArg& /*eventArg*/) = 0;
	virtual short	NotifyMouseEnterEvent (const UserItemMouseEventArg& /*eventArg*/) = 0;
	virtual short	NotifyMouseLeaveEvent (const UserItemMouseEventArg& /*eventArg*/) = 0;

	virtual void	NotifyResolutionFactorChangeEvent (const UserItemResolutionChangeEventArg& /*eventArg*/) = 0;
	virtual void	NotifyUpdateEvent (UserItemUpdateEventArg& /*eventArg*/) = 0;
};


// --- ItemUpdates -----------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ItemUpdateEventArg: public EventArg
{
public:
	void*			drawContext = nullptr;		// CGContextRef (MAC) / HDC (Windows)
	double			resolutionFactor = 1.;		// on MAC it's always 1.0
	short			left = 0;					// Client rect left position in dialog coordinates
	short			top = 0;					// Client rect top position in dialog coordinates

	virtual ~ItemUpdateEventArg ();
};


class DG_DLL_EXPORT ListBoxUpdateEventArg: public ItemUpdateEventArg
{
public:
	short			listItem;				// One-base index of the list item
	bool			isHighlighted;			// true if the item is highlighted
	short			tabIndex;				// One-base index of the tabulator field, zero for owner drawn list items
	short			width;					// Width in pixels of the tabulator field
	short			height;					// Height in pixels of the tabulator field
	short			justFlag;				// DG_IS_LEFT, DG_IS_CENTER, DG_IS_RIGHT
	short			truncFlag;				// DG_IS_NOTRUNC, DG_IS_TRUNCEND, DG_IS_TRUNCMIDDLE
	GS::UniString	tabText;				// Text of the tabulator field
	Gfx::Color		fgColor;				// Foreground color of the updated list item
	Gfx::Color		bkColor;				// Backround color of the updated list item

	void Init ();
	ListBoxUpdateEventArg ();
	virtual ~ListBoxUpdateEventArg ();
};


class DG_DLL_EXPORT ListViewUpdateEventArg: public ItemUpdateEventArg
{
public:
	short			listItem;				// One-base index of the listview item
	short			width;					// Input/output: width in pixels of the image field
	short			height;					// Input/output: height in pixels of the image field
	short			filler;					//

	void Init ();
	ListViewUpdateEventArg ();
	virtual ~ListViewUpdateEventArg ();
};


class DG_DLL_EXPORT UserItemUpdateEventArg: public ItemUpdateEventArg
{
public:
	void*			updateRgn;				// Region to update: RgnHandle (MAC) / HRGN (Windows)
	short			updateType;				// DG_UUT_NORMAL, DG_UUT_PARTIAL, DG_UUT_INUPDATE
	short			right;					// Client rect right position in dialog coordinates
	short			bottom;					// Client rect bottom position in dialog coordinates
	short			filler;					//

	void Init ();
	UserItemUpdateEventArg ();
	virtual ~UserItemUpdateEventArg ();
};


// --- StaticItem ------------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT StaticItemMouseEventArg: public EventArg
{
public:
	short			left;					// Dialog or item client rect left position
	short			top;					// Dialog or item client rect top position
	short			right;					// Dialog or item client rect right position
	short			bottom;					// Dialog or item client rect bottom position
	short			xPos;					// Horizontal mouse position relative to the client rect
	short			yPos;					// Vertical mouse position relative to the client rect
	short			keyFlag;				// DG_MOD_COMMAND, DG_MOD_OPTION, DG_MOD_SHIFT
	short			buttonFlag;				// DG_BUTTON_LEFT, DG_BUTTON_RIGHT, DG_BUTTON_WHEEL

	StaticItemMouseEventArg ();
	virtual ~StaticItemMouseEventArg ();
};


class StaticItemNotifyHandler
{
public:
	virtual ~StaticItemNotifyHandler ();

	virtual short	NotifyMouseMoveEvent (const StaticItemMouseEventArg& /*eventArg*/) = 0;
};


// --- ShortcutEdit ----------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ShortcutEditChangeEventArg: public EventArg
{
public:
	short			itemId;					// Id of the item
	short			modifiers;				// modifier flags of the hit key
	short			code;					// special key code of the key
	GS::uchar_t		uniChar;				// char code of the key

	ShortcutEditChangeEventArg ();
	virtual ~ShortcutEditChangeEventArg ();
};


class ShortcutEditNotifyHandler
{
public:
	virtual ~ShortcutEditNotifyHandler ();

	virtual void	NotifyChangeEvent (const ShortcutEditChangeEventArg& /*eventArg*/) = 0;
};


// --- IntEdit ---------------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT IntEditChangeEventArg: public EventArg
{
public:
	Int32	oldItemVal = 0;
	Int32	hint = -1;	// UT_Invalid

	virtual ~IntEditChangeEventArg ();
};


class IntEditNotifyHandler
{
public:
	virtual ~IntEditNotifyHandler ();

	virtual void	NotifyChangeEvent (const IntEditChangeEventArg& /*eventArg*/) = 0;
};


// --- RealEdit --------------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT RealEditChangeEventArg: public EventArg
{
public:
	double	oldItemVal = 0.0;
	Int32	hint = -1;	// UT_Invalid

	virtual ~RealEditChangeEventArg ();
};


class RealEditNotifyHandler
{
public:
	virtual ~RealEditNotifyHandler ();

	virtual void	NotifyChangeEvent (const RealEditChangeEventArg& /*eventArg*/) = 0;
};


// --- SearchEdit ------------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT SearchEditNotifyHandler
{
public:

	virtual ~SearchEditNotifyHandler ();

	virtual void	NotifySearchStartEvent			(const ItemChangeEventArg&) = 0;
	virtual void	NotifySearchTextChangedEvent	(const ItemChangeEventArg&) = 0;
	virtual void	NotifySearchEndEvent			(const ItemChangeEventArg&) = 0;
};

// --- TreeView --------------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT TreeViewChangeEventArg: public EventArg
{
public:
	short			actionFlag;				// DG_TVCF_SELECTION,DG_TVCF_EDITBEGIN,DG_TVCF_EDITEND,
											// DG_TVCF_TRACK, DG_TVCF_DROPMOVE, DG_TVCF_DROPCOPY
											// DG_TVCF_EXPAND, DG_TVCF_COLLAPSE
	short			filler;					//
	Int32			treeItem;				// ID of the treeview item
	GS::UniString	oldText;				// Old text of the edited treeview item
	GS::UniString	newText;				// New text of the edited treeview item

	void Init ();

	TreeViewChangeEventArg ();
	virtual ~TreeViewChangeEventArg ();
};


class DG_DLL_EXPORT TreeViewItemClickEventArg: public EventArg
{			// Message data for the DG_MSG_TREEITEMCLICK message
public:
	Int32			treeItem;				// Clicked TreeView item id
	short			partId;					// DG_TVPI_STATEICON, DG_TVPI_NORMALICON

	TreeViewItemClickEventArg ();
	virtual ~TreeViewItemClickEventArg ();
};


class TreeViewNotifyHandler
{
public:
	virtual ~TreeViewNotifyHandler ();

	virtual bool	NotifyChangeEvent (const TreeViewChangeEventArg& /*eventArg*/) = 0;
	virtual short	NotifyClickEvent (const TreeViewClickEventArg& /*eventArg*/) = 0;
	virtual short	NotifyDoubleClickEvent (const TreeViewDoubleClickEventArg& /*eventArg*/) = 0;
	virtual bool	NotifyItemClickEvent (const TreeViewItemClickEventArg& /*eventArg*/) = 0;
};


// --- TabBar ----------------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT TabBarMouseEventArg: public EventArg
{
public:
	short			pressedItem = 0;		// One-base index of item
	Int32			tabBarItemId;			// The TabBar item identifier above the help is requested
	short			itemLeft;				// TabBar control relative logical coordinate
	short			itemTop;				// TabBar control relative logical coordinate
	short			itemRight;				// TabBar control relative logical coordinate
	short			itemBottom;				// TabBar control relative logical coordinate
	short			clickPosX;				// TabBar control relative logical coordinate
	short			clickPosY;				// TabBar control relative logical coordinate
	short			keyFlag;
	bool			isCloseClicked;

	TabBarMouseEventArg ();
	virtual ~TabBarMouseEventArg ();
};


class DG_DLL_EXPORT TabBarItemDragEventArg: public EventArg
{
public:
	Int32			tabBarItemId;			// The TabBar item identifier above the help is requested
	Int32			previousIndex;
	Int32			newIndex;

	TabBarItemDragEventArg ();
	virtual ~TabBarItemDragEventArg ();
};


class DG_DLL_EXPORT TabBarItemHoverEventArg: public IntBasedEventArg
{
public:
	Int32			tabBarItem = 0;			// One-base index of the tab item

	TabBarItemHoverEventArg (Int32 tabBarItem);
	virtual ~TabBarItemHoverEventArg ();
};


class TabBarNotifyHandler
{
public:
	virtual ~TabBarNotifyHandler ();

	virtual short	NotifyClickEvent (const TabBarMouseEventArg& /*eventArg*/) = 0;
	virtual short	NotifyDoubleClickEvent (const TabBarMouseEventArg& /*eventArg*/) = 0;
	virtual void	NotifyItemDragEvent (const TabBarItemDragEventArg& /*eventArg*/) = 0;

	virtual short	NotifyItemHoverStartEvent (const TabBarItemHoverEventArg& /*eventArg*/) = 0;
	virtual short	NotifyItemHoverEndEvent (const TabBarItemHoverEventArg& /*eventArg*/) = 0;

	virtual short	NotifyItemMouseDownEvent (const TabBarMouseEventArg& /*eventArg*/) = 0;
};


// --- Splitter --------------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT SplitterDragEventArg: public EventArg
{
public:
	short	subMessage;						// DG_SPL_DRAGSTART, DG_SPL_DRAG, DG_SPL_DRAGEND
	short	position;						// A new dialog-relative postition according the mouse pointer

	SplitterDragEventArg ();
	virtual ~SplitterDragEventArg ();
};


class SplitterNotifyHandler
{
public:
	virtual ~SplitterNotifyHandler ();

	virtual void	NotifyDragStartEvent (const SplitterDragEventArg& /*eventArg*/) = 0;
	virtual void	NotifyDragEvent (const SplitterDragEventArg& /*eventArg*/) = 0;
	virtual void	NotifyDragExitEvent (const SplitterDragEventArg& /*eventArg*/) = 0;
};

// --- Ruler -----------------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT RulerClickEventArg: public EventArg
{
public:
	short				clickedPart;		// DG_RUPT_FIRSTLINEINDENT, DG_RUPT_LEFTINDENT, DG_RUPT_RIGHTINDENT, DG_RUPT_TAB, DG_RUPT_NONSPECIFICPART
	short				tabulatorIndex;		// if clickedPart == DG_RUPT_TAB
	double				position;			// in logical unit

	RulerClickEventArg ();
	virtual ~RulerClickEventArg ();
};


class DG_DLL_EXPORT RulerChangeEventArg: public EventArg
{
public:
	short				changedPart;		// DG_RUPT_FIRSTLINEINDENT, DG_RUPT_LEFTINDENT, DG_RUPT_RIGHTINDENT, DG_RUPT_TAB
	double				newPos;				// in logical unit
	short				tabulatorCount;
	DGTabulatorItem*	tabulators;			// in logical unit

	RulerChangeEventArg ();
	virtual ~RulerChangeEventArg ();
};


class RulerNotifyHandler
{
public:
	virtual ~RulerNotifyHandler ();

	virtual short	NotifyDoubleClickEvent (const RulerClickEventArg& /*eventArg*/) = 0;
	virtual short	NotifyChangeEvent (const RulerChangeEventArg& /*eventArg*/) = 0;
};


// --- PopUp -----------------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT FontPopUpChangeEventArg: public IntBasedEventArg
{
public:
	const TE::FontFamily*	fontFamily = nullptr;

	FontPopUpChangeEventArg (const TE::FontFamily* fontFamily);
	virtual ~FontPopUpChangeEventArg ();
};


class PopUpNotifyHandler
{
public:
	virtual ~PopUpNotifyHandler ();

	virtual short	NotifyChangeEvent (const FontPopUpChangeEventArg& /*eventArg*/) = 0;
};


// --- RichEdit --------------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT RichEditChangeEventArg: public EventArg
{
public:
	short			changeFlag = 0;				// DG_RECF_SELECTION, DG_RECF_CONTENT, (all)
												// DG_RECF_RESIZEREQUEST, DG_RECF_SCROLLBARPOS (only UniRichEdit)
	short			filler = 0;					//
	Int32			oldLength = 0;				// Length of text in unicode characters before change
	Int32			newLength = 0;				// Length of text in unicode characters after change
	Int32			oldMinPos = 0;				// Selection begin position before change
	Int32			oldMaxPos = 0;				// Selection end position before change
	Int32			newMinPos = 0;				// New selection begin position after selection changed
	Int32			newMaxPos = 0;				// New selection end position after selection changed
	RichEditChangeEventArg ();
	virtual ~RichEditChangeEventArg ();
};


class RichEditNotifyHandler
{
public:
	virtual ~RichEditNotifyHandler ();

	virtual void	NotifyChangeEvent  (const RichEditChangeEventArg& /*eventArg*/) = 0;
};


// --- UniRichEdit -----------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT UniRichEditChangeEventArg: public RichEditChangeEventArg
{
public:
	struct {									// Only for UniRichEdit:
		short			reqWidth = 0;			// Requested/recommended edit control width. Logical value.
		short			reqHeight = 0;			// Requested/recommended edit control height. Logical value.
		Int32			oldHScrollPos = 0;		// Previous horizontal scrollbar position. Logical value.
		Int32			oldVScrollPos = 0;		// Previous vertical scrollbar position. Logical value.
		Int32			hScrollPos = 0;			// Current horizontal scrollbar position. Logical value.
		Int32			vScrollPos = 0;			// Current vertical scrollbar position. Logical value.
		DG::NativeUnit	reqWidthNatUnit;		// Requested/recommended edit control width. Pixel value.
		DG::NativeUnit	reqHeightNatUnit;		// Requested/recommended edit control height. Pixel value.
	}	uniRich;								// Only for UniRichEdit
	UniRichEditChangeEventArg ();
	virtual ~UniRichEditChangeEventArg ();
};


class UniRichEditNotifyHandler
{
public:
	virtual ~UniRichEditNotifyHandler ();

	virtual void	NotifyChangeEvent  (const UniRichEditChangeEventArg& /*eventArg*/) = 0;
};


// --- Other -----------------------------------------------------------------------------------------------------------

class ItemNotifyHandler
{
public:
	virtual ~ItemNotifyHandler ();

	virtual short	NotifyDragDropEvent (DragDropEventArg& /*eventArg*/) = 0;
	virtual bool	NotifyContextMenuRequestEvent (ContextMenuEventArg& /*eventArg*/) = 0;
	virtual short	NotifyWheelEvent (const WheelEventArg& /*eventArg*/) = 0;
	virtual short	NotifyHelpRequestEvent (HelpEventArg& /*eventArg*/) = 0;
	virtual short	NotifyToolTipRequestEvent (HelpEventArg& /*eventArg*/) = 0;
	virtual short	NotifyClickEvent (const ItemClickEventArg& /*eventArg*/) = 0;
	virtual short	NotifyDoubleClickEvent (const ItemDoubleClickEventArg& /*eventArg*/) = 0;
	virtual short	NotifyChangeEvent (const ItemChangeEventArg& /*eventArg*/) = 0;
	virtual short	NotifyTrackEvent (const ItemTrackEventArg& /*eventArg*/) = 0;
	virtual short	NotifyFocusChangeEvent (const ItemFocusChangeEventArg& /*eventArg*/) = 0;
	virtual short	NotifyFilterCharEvent (const FilterCharEventArg& /*eventArg*/) = 0;
	virtual short	NotifyUserDefinedEvent (const UserDefinedEventArg& /*eventArg*/) = 0;
};

}

#endif // DG_ITEM_EVENTARGS_HPP
