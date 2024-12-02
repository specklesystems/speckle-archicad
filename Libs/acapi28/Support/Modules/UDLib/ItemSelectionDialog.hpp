#ifndef ITEMSELECTIONDIALOG_HPP
#define ITEMSELECTIONDIALOG_HPP

#include "DGListBox.hpp"
#include "SearchableTreeViewAndListBoxDialogBase.hpp"
#include "UDDefinitions.hpp"
#include "UDImprovedListBox.hpp"
#include "UDImprovedTreeView.hpp"
#include "UDTextEditWithHintText.hpp"

namespace UD {


class UD_DLL_EXPORT	OneColumnItemSelectionData : public UD::BaseItemSelectionData
{
public:
	static const UIndex SelectionColumnIndex = 1;
	static const UIndex SelectionListBoxColumnCount = 1;
	static const UIndex DialogStringResourceId = 1351;

private:
	GS::HashTable<UIndex, GS::UniString> itemsHashTable;
	GS::UniString						 listBoxHeaderText;
	GS::UniString						 searchFieldFormatString;

public:
	OneColumnItemSelectionData (const GS::UniString& listBoxHeaderText, const GS::UniString& searchFieldFormatString);

	virtual GS::UniString							GetItemListBoxTextByColumn (short columnIndex, UIndex itemIndex) const override;
	virtual GS::UniString							GetItemTreeViewText (UIndex itemIndex) const override;
	virtual bool									IsItemSelectable (UIndex itemIndex) const override;
	virtual bool									IsItemVisibleInListBox (UIndex itemIndex) const override;

	virtual std::function<bool(UIndex, UIndex)>		GetSortFunctionForItems (UD::ItemSortOrder sortOrder) const override;

	virtual void									CollectItemStringsForSearchComparison (UIndex					 itemIndex,
																						   GS::Array<GS::UniString>& stringsToCompare) const override;

	virtual GS::Ref<UD::ListBoxBehaviourBase>		CreateListBoxBehaviour (DG::ListBox& inListBox) const override;

	UIndex AddItem (const UD::AvailableItemData& itemData, const GS::UniString& name);

	UIndex AddGroup (const GS::UniString& name,
					 const DG::Icon&	  icon,
					 UIndex				  parentIndex = UD::AvailableItemData::NoParentGroupIndex);
};


class UD_DLL_EXPORT TwoColumnItemSelectionData : public BaseItemSelectionData
{
protected:
	enum ColumnIndex
	{
		GroupColumnIndex = 1,
		ItemColumnIndex = 2,
		ListBoxColumnCount = 2
	};

	class UD_DLL_EXPORT TwoColumnListBoxBehaviour : public ListBoxBehaviourBase
	{
	protected:
		static const short	groupColumnMinWidth = 25;
		static const short	itemColumnMinWidth = 25;

	public:
		TwoColumnListBoxBehaviour (DG::ListBox& inListBox);

		virtual ItemSortOrder	GetNewSortOrderAfterHeaderClicked (ItemSortOrder oldOrder, short clickedColumn) const override;
		virtual ItemSortOrder	GetInitialListBoxSortOrder () const override;
		virtual GS::UniString	GetListBoxSearchFieldFormatString () const override;
		virtual void			SetListBoxLayout () override;
		virtual void			CustomizeListBoxColumnWidths ();
		virtual void			RefreshListBoxHeaderItems (ItemSortOrder sortOrder) override;
		virtual void			RefreshListBoxColumns () override;
		virtual void			SetupListBoxItem (UIndex					   itemInd,
												  short						   listBoxIndex,
												  const BaseItemSelectionData& dialogData) override;
	};

	GS::Array<GS::UniString> names;
	GS::Array<UIndex> groupIndices;
	GS::Array<UIndex> itemIndices;

public:

	enum ItemType {
		Item = 0,
		Group = 1
	};


	typedef std::function<GS::UniString (UIndex)> ColumnUniStringGetter;

	static std::function<bool(UIndex, UIndex)> TwoColumnListBoxComparison (ItemSortOrder				 sortOrder,
																	const ColumnUniStringGetter& groupStringGetter,
																	const ColumnUniStringGetter& itemStringGetter);


	virtual GS::UniString				GetItemListBoxTextByColumn (short columnIndex, UIndex itemIndex) const override;
	virtual GS::UniString				GetItemTreeViewText (UIndex itemIndex) const override;
	virtual bool						IsItemSelectable (UIndex itemIndex) const override;
	virtual bool						IsItemVisibleInListBox (UIndex itemIndex) const override;

	virtual std::function<bool(UIndex, UIndex)> GetSortFunctionForItems (UD::ItemSortOrder sortOrder) const override;

	virtual void						CollectItemStringsForSearchComparison (UIndex itemIndex, GS::Array<GS::UniString>& stringsToCompare) const override;

	virtual GS::Ref<ListBoxBehaviourBase>	CreateListBoxBehaviour (DG::ListBox& inListBox) const override;

	UIndex					AddItem (const UD::AvailableItemData& itemData, const GS::UniString& name);
	UIndex					AddGroup (const UD::AvailableItemData& itemData, const GS::UniString& name);
	virtual void			Clear () override;

	UIndex					GetGroupIndexFromAbsoluteIndex (UIndex absoluteIndex) const;
	UIndex					GetAbsoluteIndexFromGroupIndex (UIndex groupIndex) const;

	UIndex					GetItemIndexFromAbsoluteIndex (UIndex absoluteIndex) const;
	UIndex					GetAbsoluteIndexFromItemIndex (UIndex absoluteIndex) const;
};


class UD_DLL_EXPORT ItemSelectionDialogBase :	public DG::ButtonItemObserver,
												public DG::ModalDialog,
												public SearchableTreeViewAndListBoxDialogBase,
												public UD::ImprovedTreeViewObserver,
												public UD::ImprovedListBoxObserver,
												public UD::ImprovedSearchEditObserver 
{
protected:
	enum ResourceIds : short {
		AddButtonId						= 1,
		InstantSearchInputTextEditId	= 2,
		DelayedSearchInputTextEditId	= 3,
		ItemsTreeViewId					= 4,
		SearchResultTextId				= 5,
		ItemsListBoxId					= 6,
		InformationIconId				= 7,
		InformationTextId				= 8
	};

	DG::Button						addButton;
	UD::ImprovedSearchEdit			searchField;
	UD::ImprovedSearchEdit			hiddenSearchField;
	DG::LeftText					searchResultText;

	UD::ImprovedSingleOrMultiSelTreeView	treeView;
	UD::ImprovedSingleOrMultiSelListBox		listBox;

	DG::IconItem					infoIconItem;
	DG::LeftText					infoTextItem;

	DG::NativeRect					parentRect;
	GS::Optional<short>				requestedWidth;
	GS::Optional<short>				maxHeight;
	DG::Utils::Alignment			placeDirection;

protected:
	ItemSelectionDialogBase (const DG::Item& 		parentItem,
							 BaseItemSelectionData&	itemSelectionDialogData,
							 short					resourceId);

	ItemSelectionDialogBase (const DG::NativeRect& 	parentRect,
							 BaseItemSelectionData&	itemSelectionDialogData,
							 short					resourceId);

	void			RefreshAddButtonStatus (void);
	void			UpdateDialogFrameHeight (void);

	virtual void	AddSelectedItems (void) override;
	virtual void	RefreshControls (void) override;
	void			RefreshInformation (void);

	virtual void	ListBoxSelectionChanged (const DG::ListBoxSelectionEvent& ev) override;
	virtual void	ListBoxDoubleClicked (const DG::ListBoxDoubleClickEvent& ev) override;
	virtual void	TreeViewSelectionChanged (const DG::TreeViewSelectionEvent& ev) override;
	virtual void	TreeViewItemExpanded (const DG::TreeViewExpandEvent& ev) override;
	virtual void	TreeViewItemDoubleClicked (const DG::TreeViewDoubleClickEvent& ev, bool* processed) override;

	virtual void	PanelOpened (const DG::PanelOpenEvent& ev) override;
	virtual void	PanelIdle (const DG::PanelIdleEvent& ev) override;
	virtual void	PanelClosed (const DG::PanelCloseEvent& ev) override;
	virtual void	PanelResized (const DG::PanelResizeEvent& ev) override;
	virtual void	PanelResizeExited (const DG::PanelResizeEvent& ev) override;
	virtual void	ButtonClicked (const DG::ButtonClickEvent& ev) override;

	virtual void	SearchTextChanged (const UD::ImprovedSearchEditChangeEvent& ev) override;
	virtual void	SearchEnded (const ImprovedSearchEditChangeEvent& ev) override;

	virtual void	AttachToDialogItems (void) override;
	virtual void	DetachFromDialogItems (void) override;

	virtual void	CreateMenuItemRowArray (short tvItem, const DG::TreeView& source, UD::ItemInfoTag::InfoTagContentCreator::MenuItemRowArray& out) const override;
	virtual void	CreateMenuItemRowArray (short listItem, const DG::ListBox& source, UD::ItemInfoTag::InfoTagContentCreator::MenuItemRowArray& out) const override;


public:
	virtual ~ItemSelectionDialogBase ();

	void	SetWidth (short width);
	void	SetMaxHeight (short inMaxHeight);
	void	SetPlaceDirection (DG::Utils::Alignment direction);
	void	SetAddButtonText (const GS::UniString& newText);
	void	SetInformationText (const GS::UniString& newText);
	void	SetInformationIcon (const DG::Icon& newIcon);
};


class UD_DLL_EXPORT ExternalTabPageBasedItemSelectionDialogBase : public DG::ModalDialog,
																  public DG::PanelObserver
{
protected:
	const DG::Item&		mParentItem;
	DG::Button			mAddButton;
	DG::SimpleTab		mTabControl;

public:
	ExternalTabPageBasedItemSelectionDialogBase	(const DG::Item& parentItem);

	virtual ~ExternalTabPageBasedItemSelectionDialogBase () override;

protected:
	virtual void			PanelResized				(const DG::PanelResizeEvent& ev) override;

	virtual void			PanelOpened					(const DG::PanelOpenEvent&) override;

	virtual void			PanelCloseRequested			(const DG::PanelCloseRequestEvent&, bool* accepted) override;

	virtual void			ResizeToFit					();
	
	virtual DG::TabPage&	GetTabPage					() const = 0;
	virtual short			GetTabPageRequiredHeight	() const = 0;
};


} // namespace UD


#endif // ITEMSELECTIONDIALOG_HPP
