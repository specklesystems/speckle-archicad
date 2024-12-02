// *********************************************************************************************************************
// File:			SeparatedListBoxUtils.hpp
//
// Description:		-
//
// Project:			A-183
//
// Namespace:		DG
//
// Contact person:	KKr
//
// *********************************************************************************************************************

#ifndef UDSEPARATEDLISTBOXUTILS_HPP
#define UDSEPARATEDLISTBOXUTILS_HPP

#pragma once

// from DG
#include "DGListBox.hpp"
#include "UDDefinitions.hpp"

// from GSRoot
#include "RSTypes.hpp"
#include "SkipSet.hpp"
#include "Array.hpp"
#include "GSFriend.hpp"


namespace UD {
class SeparatedListBoxObserver;
class SeparatedListBoxEventBase;
class SeparatedListBoxItemHelpEvent;
class SeparatedListBoxClickEvent;
class SeparatedListBoxDoubleClickEvent;

class UD_DLL_EXPORT SeparatedListBox : public DG::ListBoxObserver, 
									   public GS::EventSource
{
	template <class ListBoxType, class ListboxItemType>
	friend class ListBoxSelectionHandler;

public:
	class UD_DLL_EXPORT ItemIndex
	{
	private:
		short indexWithoutSeparator;
	public:
		ItemIndex ();
		explicit ItemIndex (short itemIndex);
		
		short ToShort () const;

		bool		operator>	(const ItemIndex& otherIndex) const;
		bool		operator<	(const ItemIndex& otherIndex) const;
		bool		operator<=	(const ItemIndex& otherIndex) const;
		bool		operator>=	(const ItemIndex& otherIndex) const;
		bool		operator==	(const ItemIndex& otherIndex) const;
		bool		operator!=	(const ItemIndex& otherIndex) const;
		void		operator++	();
		void		operator--	();
	};

	static const ItemIndex AllItems;
	static const ItemIndex BottomItem;
	static const ItemIndex InvalidItem;


	enum ListBoxSelectionType {
		SingleSelection,
		MultiSelection
	};

private:
	struct SeparatedListBoxData
	{
		GS::Array<DG::Icon>				tabItemIcons;
		GS::Array<GS::UniString>		tabItemTexts;
		GS::Ref<GS::Object>				itemObjectData;

		virtual ~SeparatedListBoxData ();
	};

	short				lastSelectedItem;
	GS::SkipSet<short>	separators;
	Owner<DG::ListBox>	listBox;

	bool				isCheckBoxEnabled;
	short				checkBoxTab;

	bool				isDragEnabled;
	short				dragIconTab;

	virtual void 		ListBoxClicked (const DG::ListBoxClickEvent& ev) override;
	virtual void		ListBoxItemDragged (const DG::ListBoxDragEvent& ev) override;
	virtual void		ListBoxMouseMoved (const DG::ListBoxMouseMoveEvent& ev, short* inArea) override;
	virtual void		ListBoxHeaderItemClicked (const DG::ListBoxHeaderItemClickEvent& ev) override;
	virtual void		ListBoxDoubleClicked (const DG::ListBoxDoubleClickEvent& ev) override;
	virtual void		ListBoxSelectionChanged (const DG::ListBoxSelectionEvent& ev) override;
	virtual void		ListBoxContextMenuRequested (const DG::ListBoxContextMenuEvent& ev, bool* processed) override;
	virtual void		ListBoxTabFieldUpdate (const DG::ListBoxTabItemUpdateEvent& ev) override;
	virtual void		ItemToolTipRequested (const DG::ItemHelpEvent& ev, GS::UniString* toolTipText) override;


	GS::Array<SeparatedListBoxData> 	CreateDataTable () const;
	void								RebuildListBoxFromDataTable (const GS::Array<SeparatedListBoxData> &dataArray);

	short								AddSeparatorsToIndex (ItemIndex listItem) const;
	ItemIndex							DeleteSeparatorsFromIndex (short selected) const;
	
	void								RefreshListBox ();
	
	GS::Array<short>					GetSelectedEnabledItems () const;
	bool								WasCheckBoxTabClicked (const DG::ListBoxClickEvent& ev) const;

	//for ListBoxSelectionHandler
	void								SelectItem (short index);
	GS::Object&							GetItemObjectData (short itemIndex) const;
public:
	SeparatedListBox (const DG::Panel& panel, short item, ListBoxSelectionType selectionType);
	virtual	~SeparatedListBox ();

	void						Attach (SeparatedListBoxObserver& observer);
	void						Detach (SeparatedListBoxObserver& observer);
	
	ItemIndex					DeleteSeparatorsFromIndex (GS::Friend<SeparatedListBoxEventBase>, short selected) const;

	ItemIndex					GetSelectedItem (bool ignoreLastSelected = false) const;
	GS::Array<ItemIndex>		GetSelectedItems () const;

	short						GetItemCount () const;
	ItemIndex					GetLastItemIndex () const;
	USize						GetSelectedItemsCount () const;

	bool						AppendItem ();
	bool						InsertItem (short insertIdx);
	void						InsertSeparator (short listItem);
	bool						IsSeparator (GS::Friend<SeparatedListBoxEventBase>, short listItem) const;

	void						SetTabItemText (ItemIndex itemIndex, short tabIndex, const GS::UniString& text);
	GS::UniString				GetTabItemText (ItemIndex itemIndex, short tabIndex) const;

	void						SetTabItemIcon (ItemIndex itemIndex, short tabIndex, const DG::Icon& icon);
	DG::Icon					GetTabItemIcon (ItemIndex itemIndex, short tabIndex) const;

	void						SelectItem (ItemIndex itemIndex);
	void						DeselectItem (ItemIndex itemIndex);

	void						DeleteItem (ItemIndex itemIndex);
	void						DeleteItems (GS::Array<ItemIndex> items);

	bool						WasCheckBoxTabClicked (const SeparatedListBoxClickEvent& ev) const;
	bool						WasCheckBoxTabDoubleClicked (const SeparatedListBoxDoubleClickEvent& ev) const;

	void						EnableCheckBox (short column);
	bool						IsCheckBoxEnabled () const;
	bool						GetCheckBoxState (ItemIndex itemIndex) const;
	void						SetCheckBoxState (ItemIndex itemIndex, bool state);

	void						EnableDrag (short iconColumn);
	bool						IsDragEnabled () const;

	void						SetItemStatus (ItemIndex itemIndex, DG::ListBox::ItemStatus status);
	DG::ListBox::ItemStatus		GetItemStatus (ItemIndex itemIndex) const;

	void						RedrawItem (ItemIndex itemIndex);
	void						RedrawTabItem (ItemIndex itemIndex, short tabIndex);

	void						OrderListBox (short column, bool isIncreasing, bool iconOrder = false);
	void						Clear ();

	void						SetItemObjectData (ItemIndex itemIndex, GS::Ref<GS::Object> object);
	GS::Object&					GetItemObjectData (ItemIndex itemIndex) const;

	void						Show (void);
	void						Hide (void);

	void						Enable (void);
	void						Disable (void);

	void						Move (short hDisp, short vDisp);
	void						Resize (short hGrow, short vGrow);

	void						EnableDraw (void);
	void						DisableDraw (void);
	void						Redraw (void) const;

	void						SetItemHeight (short itemHeight);
	short						GetItemHeight (void) const;
	short						GetItemWidth (void) const;
	short						GetHeight (void) const;
	
	bool						IsFocused (void) const;
	void						SetFocus (void);

	void						SetHeaderItemSizeableFlag (short headerItem, bool isSizeable);

	void						SetTabFieldOwnerDrawFlag (short tabIndex, bool ownerDraw);
	bool						GetTabFieldOwnerDrawFlag (short tabIndex) const;

	void						SetTabFieldBeginEndPosition (short tabIndex, short begPos, short endPos);
	void						SetTabFieldJustification (short tabIndex, DG::ListBox::Justification just);
	void						SetTabFieldTruncation (short tabIndex, DG::ListBox::Truncation trunc);

	void						SetTabFieldProperties (short tabIndex, short begPos, short endPos, DG::ListBox::Justification just, DG::ListBox::Truncation trunc,
													   bool hasSeparator = false, bool status = true);
	bool						SetTabFieldCount (short nTabFields);

	void						SetHeaderItemArrowType (short headerItem, DG::ListBox::ArrowType arrowType);
	DG::ListBox::ArrowType		GetHeaderItemArrowType (short headerItem) const;

	void						SetHeaderSynchronState (bool isSynchron);
	bool						IsHeaderInSynchronState (void) const;

	void						SetHeaderItemText (short headerItem, const GS::UniString& text);
	GS::UniString				GetHeaderItemText (short headerItem) const;

	void						SetHeaderPushableButtons (bool hasPushableButtons);
	bool						HasHeaderPushableButtons (void) const;
	void						EnableHeaderButton (void);

	void						SetHeaderDragableButtons (bool hasDragableButtons);
	bool						HasHeaderDragableButtons (void) const;

	void						SetHeaderItemCount (short itemCount);
	short						GetHeaderItemCount (void) const;

	void						SetOnTabItem (short tabIndex, const DG::Item& item);
	DG::Item*					GetOnTabItem (short tabIndex) const;
	void						RemoveOnTabItem (short tabIndex);

	short						GetTabFieldCount (void) const;
	short						GetTabFieldBeginPosition (short tabIndex) const;
	short						GetTabFieldEndPosition (short tabIndex) const;
};						


class UD_DLL_EXPORT SeparatedListBoxEventBase {
protected:
	const SeparatedListBox* separatedListBox;
	SeparatedListBoxEventBase (const SeparatedListBox* listBox);

	SeparatedListBox::ItemIndex	DeleteSeparatorsFromIndex (short listItem) const;
	bool						IsSeparator (short listItem) const;
public:
	virtual ~SeparatedListBoxEventBase ();
	const SeparatedListBox* GetSource (void) const;
};


class UD_DLL_EXPORT SeparatedListBoxItemHelpEvent : public SeparatedListBoxEventBase
{
private:
	const DG::ItemHelpEvent& itemHelpEvent;
public:
	SeparatedListBoxItemHelpEvent (const DG::ItemHelpEvent& ev, const SeparatedListBox* listBox);
	virtual ~SeparatedListBoxItemHelpEvent ();

	SeparatedListBox::ItemIndex	GetSubItem (void) const;
	bool						CurrentSubItemIsSeparator (void) const;
};


class UD_DLL_EXPORT SeparatedListBoxTabItemUpdateEvent : public SeparatedListBoxEventBase
{
private:
	const DG::ListBoxTabItemUpdateEvent& listBoxTabItemUpdateEvent;
public:
	SeparatedListBoxTabItemUpdateEvent (const DG::ListBoxTabItemUpdateEvent& ev, const SeparatedListBox* listBox);
	virtual ~SeparatedListBoxTabItemUpdateEvent ();

	operator const DG::ListBoxTabItemUpdateEvent& () const;

	short							GetTabFieldIndex (void) const;
	SeparatedListBox::ItemIndex		GetListItem (void) const;
	GS::UniString					GetTabItemText (void) const;
};


class UD_DLL_EXPORT SeparatedListBoxContextMenuEvent : public SeparatedListBoxEventBase
{
private:
	const DG::ListBoxContextMenuEvent& listBoxContextMenuEvent;
public:
	SeparatedListBoxContextMenuEvent (const DG::ListBoxContextMenuEvent& ev, const SeparatedListBox* listBox);
	virtual ~SeparatedListBoxContextMenuEvent ();

	SeparatedListBox::ItemIndex			GetItem (void) const;
	DG::NativePoint						GetPosition (void) const;
};


class UD_DLL_EXPORT SeparatedListBoxDoubleClickEvent : public SeparatedListBoxEventBase
{
private:
	const DG::ListBoxDoubleClickEvent& listBoxDoubleClickEvent;
public:
	SeparatedListBoxDoubleClickEvent (const DG::ListBoxDoubleClickEvent& ev, const SeparatedListBox* listBox);
	virtual ~SeparatedListBoxDoubleClickEvent ();

	SeparatedListBox::ItemIndex	GetListItem (void) const;
	DG::Point					GetMouseOffset (void) const;
};


class UD_DLL_EXPORT SeparatedListBoxHeaderItemClickEvent : public SeparatedListBoxEventBase
{
private:
	const DG::ListBoxHeaderItemClickEvent& listBoxHeaderItemClickEvent;
public:
	SeparatedListBoxHeaderItemClickEvent (const DG::ListBoxHeaderItemClickEvent& ev, const SeparatedListBox* listBox);
	virtual ~SeparatedListBoxHeaderItemClickEvent ();

	short		GetHeaderItem (void) const;
};


class UD_DLL_EXPORT SeparatedListBoxDragEvent : public SeparatedListBoxEventBase
{
private:
	const DG::ListBoxDragEvent& listBoxDragEvent;
public:
	SeparatedListBoxDragEvent (const DG::ListBoxDragEvent& ev, const SeparatedListBox* listBox);
	virtual ~SeparatedListBoxDragEvent ();

	SeparatedListBox::ItemIndex	GetPreviousIndex (void) const;
	SeparatedListBox::ItemIndex	GetNewIndex (void) const;
	bool						IsDraggedItemSeparator (void) const;
};


class UD_DLL_EXPORT SeparatedListBoxSelectionEvent : public SeparatedListBoxEventBase
{
public:
	SeparatedListBoxSelectionEvent (const DG::ListBoxSelectionEvent& ev, const SeparatedListBox* listBox);
	virtual ~SeparatedListBoxSelectionEvent ();
};


class UD_DLL_EXPORT SeparatedListBoxClickEvent : public SeparatedListBoxEventBase
{
private:
	const DG::ListBoxClickEvent& listBoxClickEvent;
public:
	SeparatedListBoxClickEvent (const DG::ListBoxClickEvent& ev, const SeparatedListBox* listBox);
	virtual ~SeparatedListBoxClickEvent ();

	DG::Point	GetMouseOffset (void) const;
};


class UD_DLL_EXPORT SeparatedListBoxObserver : public GS::EventObserver
{
public:
	virtual void	ListBoxClicked (const SeparatedListBoxClickEvent& ev);
	virtual void	ListBoxSelectionChanged (const SeparatedListBoxSelectionEvent& ev);
	virtual void	ListBoxItemDragged (const SeparatedListBoxDragEvent& ev);
	virtual void	ListBoxHeaderItemClicked (const SeparatedListBoxHeaderItemClickEvent& ev);
	virtual void	ListBoxDoubleClicked (const SeparatedListBoxDoubleClickEvent& ev);
	virtual void	ListBoxContextMenuRequested (const SeparatedListBoxContextMenuEvent& ev, bool* processed);
	virtual void	ListBoxTabFieldUpdate (const SeparatedListBoxTabItemUpdateEvent& ev);
	virtual void	ItemToolTipRequested (const SeparatedListBoxItemHelpEvent& ev, GS::UniString* toolTipText);

	virtual			~SeparatedListBoxObserver ();
};



}		//namespace UD


#endif
