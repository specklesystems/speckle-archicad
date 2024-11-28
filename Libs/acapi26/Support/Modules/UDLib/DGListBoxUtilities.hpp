#ifndef GS_COMMONUI_DGLISTBOXUTILITIES_HPP
#define GS_COMMONUI_DGLISTBOXUTILITIES_HPP


#include "UDDefinitions.hpp"
#include "HashTable.hpp"

namespace DG {
	class ListBox;
}

namespace Gfx {
	class Color;
}


namespace UD {
	UD_DLL_EXPORT short	GetListBoxDesiredOnTabItemWidth (const DG::ListBox& listBox, short tabItemIndex);
	UD_DLL_EXPORT short GetListBoxRequiredHeight (const DG::ListBox& listBox);
	UD_DLL_EXPORT Gfx::Color GetListBoxDefaultSectionHeaderBackgroundColor (const DG::ListBox&	listBox, short itemIndex);

	template <class ListBoxType, class ListboxItemType>
	class ListBoxSelectionHandler {
	private:
		GS::HashSet<const ListboxItemType*> selectedItems;
		ListBoxType& listBox;

	public:
		ListBoxSelectionHandler (ListBoxType& listBox);
		~ListBoxSelectionHandler ();
	};

	template <class ListBoxType, class ListboxItemType>
	ListBoxSelectionHandler<ListBoxType, ListboxItemType>::ListBoxSelectionHandler (ListBoxType& listBox) :
		listBox (listBox)
	{
		auto selectedItemsIndices = listBox.GetSelectedItems ();
		for (const auto& selectedItemIndex : selectedItemsIndices) {
			const GS::Object& itemObjectData = listBox.GetItemObjectData (selectedItemIndex);
			const ListboxItemType* selectedMember = static_cast<const ListboxItemType*> (&itemObjectData);
			selectedItems.Add (selectedMember->Clone ());
		}
	}


	template <class ListBoxType, class ListboxItemType>
	ListBoxSelectionHandler<ListBoxType, ListboxItemType>::~ListBoxSelectionHandler ()
	{
		for (short index = 1; index <= listBox.GetItemCount (); ++index) {
			const GS::Object& itemObjectData = listBox.GetItemObjectData (index);
			const ListboxItemType* participant = static_cast<const ListboxItemType*> (&itemObjectData);
			bool selectActualParticipant = !selectedItems.Select ([&] (const ListboxItemType* item) {
				return *item == *participant;
			}).IsEmpty ();

			if (selectActualParticipant)
				listBox.SelectItem (index);
		}

		selectedItems.Enumerate ([&] (const ListboxItemType* item) {
			delete item;
		});
	}


	class UD_DLL_EXPORT ListBoxColumnResizer : public DG::ListBoxObserver {
	public:
		explicit ListBoxColumnResizer (DG::ListBox& listBox);
		virtual ~ListBoxColumnResizer ();

		void SetColumnFixWidth (short column, short fixWidth);
		void SetColumnResizableWeight (short column, short weight);

		void Resize ();

	private:
		DG::ListBox& listBox;
		GS::HashTable<short, short> fixColumnWidths;
		GS::HashTable<short, short> resizableColumnWeights;

		virtual short	ListBoxHeaderItemResizeExited (const DG::ListBoxHeaderItemResizeEvent& ev) override;
		void			UpdateResizableColumnWeights ();
		void			FillWithDefaultValues ();
	};
}


#endif
