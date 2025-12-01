#if !defined GS_COMMONUI_SINGLESELECTIONTREEVIEWPOPUPDIALOG_HPP
#define	GS_COMMONUI_SINGLESELECTIONTREEVIEWPOPUPDIALOG_HPP

#include "UDDefinitions.hpp"
#include "DGModule.hpp"
#include "HashSet.hpp"
#include "HashTable.hpp"


namespace UD {
	class SingleSelectionTreeViewPopupDialogDataObserver;
	class TreeData;
	class SingleSelectionTreeViewPopupDialog;
}


namespace UD {


class UD_DLL_EXPORT SingleSelectionTreeViewPopupDialogData: public GS::EventSource
{
private:
	const TreeData& treeData;
	UIndex			selectedItemIndex;

public:
	static const UIndex NoSelectedItemIndex;

	SingleSelectionTreeViewPopupDialogData (const TreeData& treeData);
	virtual ~SingleSelectionTreeViewPopupDialogData ();

	void Attach (SingleSelectionTreeViewPopupDialogDataObserver& observer);
	void Detach (SingleSelectionTreeViewPopupDialogDataObserver& observer);

	const TreeData& GetTreeData (void) const;

	UIndex	GetSelectedItemIndex (void) const;
	void	SetSelectedItemIndex (UIndex inSelectedItemIndex);
};


class UD_DLL_EXPORT SingleSelectionTreeViewPopupDialogDataObserver: public GS::EventObserver
{
public:
	virtual void SelectionChanged (const SingleSelectionTreeViewPopupDialogData& data) = 0;

	virtual ~SingleSelectionTreeViewPopupDialogDataObserver ();
};


class UD_DLL_EXPORT SingleSelectionTreeViewPopupDialogDisplayParameters
{
private:
	const DG::Item&		parentItem;
	const DG::Item*		leftParentItem;

	short		maxDialogWidth;
	short		maxDialogHeight;

	bool		hasNormalIcon;

public:
	SingleSelectionTreeViewPopupDialogDisplayParameters (const DG::Item& parentItem, const DG::Item* leftParentItem = nullptr);
	virtual ~SingleSelectionTreeViewPopupDialogDisplayParameters ();

	const DG::Item&		GetParentItem (void) const;
	const DG::Item*		GetLeftParentItem (void) const;

	short	GetMaxDialogWidth (void) const;
	void	SetMaxDialogWidth (short inMaxDialogWidth);
	short	GetMaxDialogHeight (void) const;
	void	SetMaxDialogHeight (short inMaxDialogHeight);

	bool	HasNormalIcon (void) const;
	void	SetHasNormalIcon (bool inHasNormalIcon);
};


class UD_DLL_EXPORT SingleSelectionTreeViewPopupDialog:	public DG::ModalDialog,
																			public DG::PanelObserver,
																			public DG::TreeViewObserver
{
private:
	static const short DialogResourceIdWithNormalIcon;
	static const short DialogResourceIdWithoutNormalIcon;

	enum {
		SingleSetTreeViewId = 1
	};

	SingleSelectionTreeViewPopupDialogData&						dialogData;
	const SingleSelectionTreeViewPopupDialogDisplayParameters&	displayParameters;

	short minDialogWidth;
	short minDialogHeight;

	bool isUpdatingDialogSizeNeededInPanelIdle;
	bool isExpandedTreeViewItemsNeededInPanelIdle;

	bool closeWhenDoubleClick;
	bool closeWhenLeafSelected;

	DG::SingleSelTreeView treeView;

	GS::HashTable<UIndex, Int32> treeViewItemIds;

	GS::HashSet<UIndex> expandedTreeItemIndices;

	void FillTreeView (void);
	void UpdateSelection (void);
	void UpdateDialogSize (void);
	void ExpandTreeViewItems (void);

	virtual void PanelOpened (const DG::PanelOpenEvent& ev) override;
	virtual void PanelResized (const DG::PanelResizeEvent& ev) override;
	virtual void PanelIdle (const DG::PanelIdleEvent& ev) override;

	virtual void TreeViewSelectionChanged (const DG::TreeViewSelectionEvent& ev) override;
	virtual void TreeViewItemExpanded (const DG::TreeViewExpandEvent& ev) override;
	virtual void TreeViewItemDoubleClicked (const DG::TreeViewDoubleClickEvent& ev, bool* processed) override;

public:
	SingleSelectionTreeViewPopupDialog (SingleSelectionTreeViewPopupDialogData&						dialogData,
										const SingleSelectionTreeViewPopupDialogDisplayParameters&	displayParameters);

	~SingleSelectionTreeViewPopupDialog ();

	void SetExpandedTreeViewItems (const GS::HashSet<UIndex>& inExpandedTreeItemIndices);
	void GetExpandedTreeViewItems (GS::HashSet<UIndex>& outExpandedTreeItemIndices) const;

	void SetCloseWhenDoubleClick (bool inCloseWhenDoubleClick);
	void SetCloseWhenLeafSelected (bool inCloseWhenLeafSelected);
};


} // namespace UD


#endif