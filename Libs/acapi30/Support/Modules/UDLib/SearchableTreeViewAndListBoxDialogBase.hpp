#ifndef ITEMSELECTIONBEHAVIOUR_HPP
#define ITEMSELECTIONBEHAVIOUR_HPP

#include "UDDefinitions.hpp"
#include "ItemSelectionData.hpp"
#include "Owner.hpp"
#include "UDImprovedSearchTextEdit.hpp"

namespace UD {

class BaseItemSelectionDataObserver;
class BaseItemSelectionData;

class UD_DLL_EXPORT SearchableTreeViewAndListBoxDialogBase :
	public DG::PanelObserver,
	public DG::ListBoxObserver,
	public DG::TreeViewObserver,
	public DG::LowLevelKeyboardHandler,
	public UD::BaseItemSelectionDataObserver
{
protected:
	enum class ItemsDisplayMode {
		ItemsInTreeView,
		ItemsInListBoxView
	};

private:
	struct SortedItemSelectionDialogDataIndicies {
		GS::Array<UIndex>	itemIndicies;
		UD::ItemSortOrder	sortOrder;
		USize				lastSize;
	};

	SortedItemSelectionDialogDataIndicies	sortedItemsIndicies;

	UD::ImprovedSearchEdit&					searchField;

protected:
	DG::TreeView&					itemsTreeView;
	DG::LeftText&					searchResultText;
	DG::ListBox&					itemsListBox;

	BaseItemSelectionData&			itemSelectionDialogData;
	GS::Array<Int32>				treeViewItemIds;
	GS::HashSet<UIndex>				expandedGroupIndices;
	bool							isExpandingGroupsNeeded;
	bool							isUpdatingDialogFrameRectNeeded;
	GS::Ref<ListBoxBehaviourBase>	listBoxBehaviour;
	ItemSortOrder					currentItemSortOrderInListBox;

	GS::HashSet<UIndex>				selectedItemIndices;
	bool							isSelectingItemsNeeded;

private:
	void	SetSelectedItems (void);

	void	GetSelectedItemsIndicesFromTreeView (GS::Array<UIndex>& selectedIndices) const;
	void	GetSelectedItemsIndicesFromListBox (GS::Array<UIndex>& selectedIndices) const;

	bool	IsKeyHandledBySearchField (const DG::Key::Code& code) const;
	bool	IsKeyHandledByTreeView (const DG::Key::Code& code) const;
	bool	IsKeyHandledByListBox (const DG::Key::Code& code) const;

	void	UpdateSortedItemsIndicies ();
	bool	IsItemSelectionDialogDataUpdated () const;
	void	AppendMatchedItem (UIndex itemIndex);

protected:

	SearchableTreeViewAndListBoxDialogBase (UD::ImprovedSearchEdit&	inSearchField,
											DG::TreeView&			inTreeView,
											DG::LeftText&			inLeftText,
											DG::ListBox&			inListBox,
											BaseItemSelectionData&	itemSelectionDialogData);

	void	FillItemsTreeView (void);
	void	FillItemListBox (void);
	void	RefreshSearchResultText (void);

	void	UpdateListBoxItemsStatus (void);
	void	UpdateTreeViewItemsStatus (void);
	void	GetSelectedItemsIndices (GS::Array<UIndex>& selectedIndices) const;
	bool	IsSearchMatch (const AvailableItemData& itemData) const;

	virtual	ItemsDisplayMode	GetItemsDisplayMode (void) const;
	virtual void				AddSelectedItems (void);

	virtual void RefreshControls (void);

	void	ExpandGroups (void);
	void	SelectItems (void);

	virtual void						PanelOpened (const DG::PanelOpenEvent& ev) override;
	virtual void						ListBoxDoubleClicked (const DG::ListBoxDoubleClickEvent& ev) override;
	virtual void						ListBoxHeaderItemClicked (const DG::ListBoxHeaderItemClickEvent& ev) override;
	virtual DG::EventHandlerResultType	KeyPressed (const DG::Key::Code& code, DG::Item** item) override;
	virtual void						ItemToolTipRequested (const DG::ItemHelpEvent& ev, GS::UniString* toolTipText) override;

	virtual void						DisabledItemsChanged (const BaseItemSelectionData& source) override;

	virtual void						AttachToDialogItems ();
	virtual void						DetachFromDialogItems ();

public:
	virtual	void		SetExpandedGroupIndices (const GS::HashSet<UIndex>& inExpandedGroupIndices);
	GS::HashSet<UIndex>	GetExpandedGroupIndices () const;

	void SetSelectedItemIndices (const GS::HashSet<UIndex>& inSelectedItemIndices);

	static void	SelectFirstEnabledListBoxItem (DG::ListBox& listBox);
};

UD_DLL_EXPORT GS::Array<UIndex> CreateTreeViewIndexArray (const BaseItemSelectionData& selectionData);
UD_DLL_EXPORT GS::Array<UIndex> CreateListBoxIndexArray (const BaseItemSelectionData& selectionData, UD::ItemSortOrder sortOrder);

UD_DLL_EXPORT bool IsInstantSearchInDialogsWithLotOfItemsAllowed ();

} // namespace UD


#endif // ITEMSELECTIONDIALOG_HPP
