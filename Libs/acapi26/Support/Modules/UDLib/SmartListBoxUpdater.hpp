#ifndef GS_UD_LD_MULTI_SEL_LISTBOX_HPP
#define GS_UD_LD_MULTI_SEL_LISTBOX_HPP

#pragma once

#include "UDDefinitions.hpp"
#include "DGListBox.hpp"
#include "UDImprovedListBox.hpp"
#include "LDListDiff.hpp"
#include <memory>
#include "SmartListBoxDecorator.hpp"

namespace UD {


class UD_DLL_EXPORT SeparatorDiffable final : public ListDiff::ListDiffable {
public:
	SeparatorDiffable (const GS::Guid& diffId);
	virtual ~SeparatorDiffable ();

	virtual GS::Guid	GetDiffIdentifier () const override;
	virtual bool		IsEqualToDiffableObject (const ListDiffable& object) const override;

private:
	GS::Guid			diffId;
};


class UD_DLL_EXPORT SmartListBoxUpdater {
public:
	using ItemType = std::shared_ptr<const ListDiff::ListDiffable>;

	enum SelectionKeeperResult {
		AllRestored,
		SomeRestored,
		NoneRestored
	};

	class UD_DLL_EXPORT SelectionKeeper {
		GS::Array<short>			selectedRows;
		GS::Array<GS::Guid>			selectedItemIds;
		DG::ListBox*				listBox;
		const SmartListBoxUpdater*	updater;

		SelectionKeeper (DG::ListBox* listBox, const SmartListBoxUpdater* updater);
		friend class SmartListBoxUpdater;
	public:
		SelectionKeeper (SelectionKeeper&&) = default;
		GS::Array<short>		GetSelectedRows ();
		GS::Array<GS::Guid>		GetSelectedItemIds ();
		SelectionKeeperResult	RestoreByItemIds ();
	};
private:
	struct IndexMap;
	GS::OnHeap<IndexMap>	indexMap;
	GS::Array<ItemType>		items;
	DG::ListBox*			listBox;
	ListBoxDecorator*		decorator;

public:
	SmartListBoxUpdater (DG::ListBox* listBox, ListBoxDecorator* decorator);

	GS::Array<GS::Guid>	GetSelectedItemIds () const;
	GS::Array<ItemType>	GetSelectedItems () const;
	const GS::Array<ItemType>&	GetItems () const;
	bool				HasItem (const GS::Guid& id) const;
	bool				HasItem (short row) const;
	ItemType			GetItem (short row) const;
	ItemType			GetItem (const GS::Guid& id) const;
	short				GetRow (const GS::Guid& id) const;
	short				GetRow (const ItemType& item) const;
	SelectionKeeper		SetItems (GS::Array<ItemType>&& newItems);
	void				UpdateItem (const GS::Guid& id) const;

	~SmartListBoxUpdater ();

private:
	void				InsertNewEmptyRow (short row, const ItemType& item);
	void				UpdateExistingRowType (short row, const ItemType& item);
	void				FillRowContent (short row, const ItemType& item);
};

} // namespace UD

#endif
