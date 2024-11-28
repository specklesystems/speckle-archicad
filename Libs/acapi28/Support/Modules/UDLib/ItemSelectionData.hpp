#ifndef ITEMSELECTIONDATA_HPP
#define ITEMSELECTIONDATA_HPP

#include <optional>

#include "UDDefinitions.hpp"
#include "DGLowLevelKeyboardHandling.hpp"
#include "DGModule.hpp"
#include "HashSet.hpp"
#include "Owner.hpp"
#include "Any.hpp"
#include "DGListBoxUtilities.hpp"


namespace UD {

class BaseItemSelectionDataObserver;
class BaseItemSelectionData;


class UD_DLL_EXPORT AvailableItemData
{
	enum class Flags {
		Group,
		SortsChildren,
		CannotInheritIcon,
	};

	GS::HashSet<Flags>			   flags;
	UIndex						   ownIndex;
	const UIndex				   parentIndex;
	Gfx::Color					   color;
	std::optional<DG::Font::Style> fontStyle;
	std::optional<DG::Icon>		   icon;
	std::optional<DG::Icon>		   statusIcon;
	GS::UniString				   tooltip;
	GS::Any						   additionalData;

public:
	static const UIndex NoParentGroupIndex = MaxUIndex;

	explicit AvailableItemData (UIndex inParentIndex);

	UIndex				 GetParentIndex () const;
	UIndex				 GetOwnIndex () const;
	DG::Icon			 GetIcon () const;
	DG::Icon			 GetStatusIcon () const;
	const Gfx::Color&	 GetColor () const;
	DG::Font::Style		 GetFontStyle () const;
	const GS::UniString& GetTooltip () const;
	bool				 IsGroup () const;
	bool				 HasParent () const;
	bool				 HasIcon () const;
	bool				 CanInheritIconFromParent () const;
	bool				 HasStatusIcon () const;
	bool				 ShouldChildrenBeSorted () const;
	bool				 HasFontStyle () const;

	void SetIcon (const DG::Icon& icon);
	void SetStatusIcon (const DG::Icon& statusIcon);
	void SetColor (const Gfx::Color& inColor);
	void SetFontStyle (DG::Font::Style inFontStyle);
	void SetTooltip (const GS::UniString& inTooltip);
	void SetOwnIndex (UIndex ownIndex);
	void DisableIconInheritanceFromParent ();
	void SetToGroupType ();
	void SetChildrenToBeSorted ();
	
	template <typename Type> bool			HasAdditionalData () const;
	template <typename Type> const Type&	GetAdditionalData () const;
	template <typename Type> void			SetAdditionalData (const Type& value);
	void ClearAdditionalData ();
};

template <typename Type>
bool AvailableItemData::HasAdditionalData () const
{
	return additionalData.HasValue () && additionalData.Is<Type> ();
}

template <typename Type>
const Type& AvailableItemData::GetAdditionalData () const
{
	return additionalData.Get<Type> ();
}

template <typename Type>
void AvailableItemData::SetAdditionalData (const Type& value)
{
	additionalData = value;
}



enum class UD_DLL_EXPORT ItemSortOrder 
{
	SortByItemNameAsc,
	SortByItemNameDesc,
	SortByGroupNameAsc,
	SortByGroupNameDesc
};


enum class UD_DLL_EXPORT ViewType 
{
	TreeView,
	ListBoxView
};


class UD_DLL_EXPORT ListBoxBehaviourBase 
{
protected:
	DG::ListBox& listBox;
	bool isListBoxInited;
	GS::Owner<UD::ListBoxColumnResizer> listBoxResizer;
public:
	ListBoxBehaviourBase (DG::ListBox& inListBox);
	virtual ~ListBoxBehaviourBase ();

	virtual ItemSortOrder	GetNewSortOrderAfterHeaderClicked (ItemSortOrder oldOrder, short clickedColumn) const = 0;
	virtual GS::UniString	GetListBoxSearchFieldFormatString () const = 0;
	virtual void			SetListBoxLayout () = 0;
	virtual void			RefreshListBoxHeaderItems (ItemSortOrder sortOrder) = 0;
	virtual void			RefreshListBoxColumns () = 0;
	virtual void			SetupListBoxItem (UIndex itemInd, short listBoxIndex, const BaseItemSelectionData& dialogData) = 0;
	virtual ItemSortOrder	GetInitialListBoxSortOrder () const = 0;

	void					InitializeListBox ();
	void					AttachToListBox ();
	void					DetachFromListBox ();
};


class UD_DLL_EXPORT BaseItemSelectionData : public GS::EventSource
{
	GS::Array<AvailableItemData>		itemsData;
	GS::HashSet<UIndex>					disabledItemIndices;
	GS::Array<UIndex>					selectedItemIndices;

public:
	virtual ~BaseItemSelectionData ();

	UIndex	AddItem (const AvailableItemData& itemData);
	UIndex  AddGroup (const AvailableItemData& itemData);

	virtual void	SetDisabledItemIndices (const GS::HashSet<UIndex>& inDisabledItemIndices);
	virtual void	SetSelectedItemIndices (const GS::Array<UIndex>& inSelectedItemIndices);

	virtual const GS::Array<AvailableItemData>&	GetItemsData (void) const;
	virtual const GS::HashSet<UIndex>&			GetDisabledItemIndices (void) const;
	bool										IsItemDisabled (UIndex itemIndex) const;
	virtual const GS::Array<UIndex>&			GetSelectedItemIndices (void) const;

	virtual GS::UniString				GetItemListBoxTextByColumn (short columnIndex, UIndex itemIndex) const = 0;
	virtual GS::UniString				GetItemTreeViewText (UIndex itemIndex) const = 0;
	virtual bool						IsItemSelectable (UIndex itemIndex) const = 0;
	virtual bool						IsItemVisibleInListBox (UIndex itemIndex) const = 0;

	virtual std::function<bool(UIndex first, UIndex second)> GetSortFunctionForItems (UD::ItemSortOrder) const = 0;

	virtual void						CollectItemStringsForSearchComparison (UIndex itemIndex, 
																		GS::Array<GS::UniString>& stringsToCompare) const = 0;
	virtual GS::Ref<ListBoxBehaviourBase>	CreateListBoxBehaviour (DG::ListBox& inListBox) const = 0;

	GS::UniString						GetItemName (UIndex ind) const;
	UIndex								GetRootParentInd (UIndex ind) const;
	void								TraverseSubTreeIndices (UIndex rootInd, const std::function<bool (UIndex ind)>& processor) const;
	bool								IsLeafItem (UIndex itemIndex) const;
	bool								ItemHasEnabledChild (UIndex itemIndex) const;
	virtual void						Clear ();

	virtual GS::UniString				GetSearchHintText (void) const;

	void	Attach (BaseItemSelectionDataObserver& observer);
	void	Detach (BaseItemSelectionDataObserver& observer);
};


class UD_DLL_EXPORT BaseItemSelectionDataObserver : public GS::EventObserver
{
protected:
	friend class BaseItemSelectionData;

	virtual void DisabledItemsChanged (const BaseItemSelectionData& source);
	
public:
	virtual void SelectedItemsChanged (const BaseItemSelectionData& source);
	virtual ~BaseItemSelectionDataObserver ();
};


} // namespace UD


#endif // ITEMSELECTIONDIALOG_HPP