#ifndef ITEMSTATUSCHANGERDIALOG_HPP
#define ITEMSTATUSCHANGERDIALOG_HPP

#include "DGModule.hpp"
#include "UDDefinitions.hpp"
#include "ItemSelectionDialog.hpp"
#include "DGRadioItem.hpp"


namespace UD {

enum class ItemCheckStatus {
	Checked,
	Unchecked,
	Mixed
};

enum class ItemSelectionFilterMode {
	All = 1,
	Checked = 2
};

class UD_DLL_EXPORT TreeViewMultiItemSelectionDialogData : public BaseItemSelectionData
{
public:
	enum ColumnIndex
	{
		GroupColumnIndex   = 1,
		ItemColumnIndex    = 2,
		ListBoxColumnCount = 2
	};

	enum class NodeType {
		SelectableSeparately,
		NotSelectableSeparately
	};

	class UD_DLL_EXPORT ItemStatus {
	public:
		UD::ItemCheckStatus	GetOriginalStatus () const;
		void				SetOriginalStatus (UD::ItemCheckStatus originalStatus);
		UD::ItemCheckStatus	GetCurrentStatus () const;
		void				SetCurrentStatus (UD::ItemCheckStatus currentStatus);
		bool				IsExpanded () const;
		void				SetIsExpanded (bool isExpanded);

		UD::TreeViewMultiItemSelectionDialogData::NodeType	GetNodeType () const;
		void												SetNodeType (UD::TreeViewMultiItemSelectionDialogData::NodeType nodeType);

		ItemStatus (ItemCheckStatus currentStatus, NodeType nodeType, bool isExpanded);
	private:
		ItemCheckStatus			originalStatus;
		ItemCheckStatus			currentStatus;
		bool					isExpanded;
		NodeType			nodeType;
	};

	TreeViewMultiItemSelectionDialogData ();
	virtual ~TreeViewMultiItemSelectionDialogData ();

	UIndex AddItem (const AvailableItemData& itemData, NodeType nodeType, ItemCheckStatus currentStatus);
	UIndex AddGroup (const AvailableItemData& itemData, NodeType nodeType, ItemCheckStatus currentStatus);

	void					SetFilterMode (ItemSelectionFilterMode inMode);
	ItemSelectionFilterMode GetFilterMode () const;

	ItemCheckStatus		ToggleItemStatus (UIndex itemIndex);
	void				SetItemExpansionStatus (UIndex itemIndex, bool status);
	void				SetStatusToItemChildren (UIndex itemIndex, UD::ItemCheckStatus status);
	ItemCheckStatus		GetItemStatus (UIndex itemIndex) const;
	void				SetItemStatus (UIndex itemIndex, UD::ItemCheckStatus status);
	ItemCheckStatus		GetAggregatedChildrenStatus (UIndex itemIndex) const;

	static short		GetIconColumnMinWidth ();
	bool				IsItemSelectable (UIndex itemIndex) const;
	bool				IsItemExpanded (UIndex itemIndex) const;
	bool				AllChildrenHaveEqualStatus (UIndex itemIndex) const;

	const GS::Array<ItemStatus>& GetItemStatuses () const;
	void				  		 SetItemStatuses (const GS::Array<ItemStatus> itemStatuses);

	GS::Array<UIndex>	GetChangedItemIndices () const;

	DG::Icon			GetStatusIconForListDisplay (UIndex itemIndex) const;

private:
	ItemSelectionFilterMode filterMode;
	GS::Array<ItemStatus> itemStatuses;
};


class UD_DLL_EXPORT	DialogClickStateMachine
{
	UIndex currentFunctionIndex = 0;
	GS::Array<std::function<void ()>> stepFunctions;
	TreeViewMultiItemSelectionDialogData& dialogData;
	GS::Array<TreeViewMultiItemSelectionDialogData::ItemStatus> originalState;
	UIndex itemIndex;

public:
	DialogClickStateMachine (TreeViewMultiItemSelectionDialogData& dialogData, UIndex itemIndex);

	virtual void DoNextStep ();

	void AddToggleStep ();
	void AddToggleChildrenStep ();
	void AddApplyItemStatusToChildrenStep ();
	void AddRestoreStateStep ();
	UIndex GetItemIndex () const;
};




class UD_DLL_EXPORT TreeViewMultiItemSelectionDialog : public DG::ModalDialog,
													   public SearchableTreeViewAndListBoxDialogBase,
													   public DG::ButtonItemObserver,
													   public DG::RadioItemObserver
{
public:
	TreeViewMultiItemSelectionDialog (TreeViewMultiItemSelectionDialogData& dialogData);
	~TreeViewMultiItemSelectionDialog ();

	virtual void PanelOpened (const DG::PanelOpenEvent& ev) override;
	virtual void PanelResized (const DG::PanelResizeEvent& ev) override;
	virtual void PanelResizeExited (const DG::PanelResizeEvent& ev) override;
	virtual void PanelIdle (const DG::PanelIdleEvent& ev) override;

	virtual void ButtonClicked (const DG::ButtonClickEvent& ev) override;
	virtual void RadioItemChanged (const DG::RadioItemChangeEvent& ev) override;
	
	virtual void TreeViewItemClicked (const DG::TreeViewItemClickEvent& ev, bool* denySelectionChange) override;
	virtual void TreeViewItemDoubleClicked (const DG::TreeViewDoubleClickEvent& ev, bool* processed) override;

	virtual void ListBoxClicked (const DG::ListBoxClickEvent& ev) override;
	virtual void TreeViewContextMenuRequested (const DG::TreeViewContextMenuEvent& ev, bool* processed) override;

private:

	enum {
		DialogResourceId = 2111,

		OkButtonResId = 1,
		CancelButtonResId = 2,
		TreeViewButtonResId = 3,
		FilterToCheckedButtonResId = 4,
		ListViewButtonResId = 5,
		SearchInputResId = 6,
		TreeViewResId = 7,
		SearchResultResId = 8,
		ListBoxResId = 9
	};

	DG::Button				okButton;
	DG::Button				cancelButton;
	DG::IconPushRadio		treeViewButton;
	DG::IconPushRadio		filterToCheckedButton;
	DG::IconPushRadio		listViewButton;

	DG::TextEdit			searchInputTextEdit;
	DG::SingleSelTreeView	itemsTreeView;
	DG::LeftText			searchResultText;
	DG::SingleSelListBox	itemsListBox;

	bool refreshOnIdle;
	TreeViewMultiItemSelectionDialogData& dialogData;

	GS::Ref<DialogClickStateMachine> clickStateMachine;

	void UpdateStatusIconsInTreeView (UIndex itemIndex);
	void UpdateAllStatusIcons ();

	virtual	SearchableTreeViewAndListBoxDialogBase::ItemsDisplayMode GetItemsDisplayMode (void) const override;

	virtual	void	TextEditChanged (const DG::TextEditChangeEvent& ev) override;
	DG::Icon		GetStatusIconForTreeDisplay (UIndex itemIndex) const;

	void	ApplyTreeItemClick (Int32 treeItemId);
	void	SetItemExpansionStatus (UIndex dataIndex, bool status);
	void	SelectTreeItemsRecursively (UIndex itemInd);
	void	DeselectTreeItemsRecursively (UIndex itemInd);

	void ResetClickStateMachine ();

protected:
	virtual void TreeViewItemCollapsed (const DG::TreeViewExpandEvent& ev) override;


	virtual void TreeViewItemExpanded (const DG::TreeViewExpandEvent& ev) override;

};


} // namespace UD


#endif // ITEMSTATUSCHANGERDIALOG_HPP
