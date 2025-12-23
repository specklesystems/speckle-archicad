// *********************************************************************************************************************
// File:			DGCommonEventArgs.hpp
//
// Description:		Dialog manager event handling.
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Contact person:	SZM
// *********************************************************************************************************************

#ifndef DG_ITEM_EVENT_NOTIFIERS_HPP
#define DG_ITEM_EVENT_NOTIFIERS_HPP

#include "DGCommonEventArgs.hpp"
#include "DGEventNotifier.hpp"

namespace DG {

class Item;


// --- ItemDragDropNotifierBase ----------------------------------------------------------------------------------------

class ItemDragDropNotifierBase
{
public:
	virtual ~ItemDragDropNotifierBase ();

	virtual short	NotifyDragDrop (DragDropEventArg& eventArg, Item* item) = 0;
};


// --- ItemDragDropNotifier --------------------------------------------------------------------------------------------

template <typename ItemType>
class ItemDragDropNotifier: public ItemDragDropNotifierBase
{
public:
	virtual ~ItemDragDropNotifier () {}

	EventNotifier<ItemType, const DragDropEventArg, short> onDragStarting;
	EventNotifier<ItemType, const DragDropEventArg, short> onDragStarted;
	EventNotifier<ItemType, const DragDropEventArg, short> onDragEnded;
	EventNotifier<ItemType, const DragDropEventArg, short> onDragDelayedDataSetted;
	EventNotifier<ItemType, const DragDropEventArg, short> onDragEntered;
	EventNotifier<ItemType, const DragDropEventArg, short> onDragMoved;
	EventNotifier<ItemType, const DragDropEventArg, short> onDragLeft;
	EventNotifier<ItemType, const DragDropEventArg, short> onDragDropped;

	virtual short	NotifyDragDrop (DragDropEventArg& eventArg, Item* item) override
	{
		ItemType* specItem = dynamic_cast<ItemType*> (item);
		if (specItem == nullptr)
			return 0;

		switch (eventArg.subMessage) {
			case DG_DRAG_STARTING:
				return onDragStarting.NotifyAll (*specItem, eventArg);

			case DG_DRAG_START:
				return onDragStarted.NotifyAll (*specItem, eventArg);

			case DG_DRAG_END:
				return onDragEnded.NotifyAll (*specItem, eventArg);

			case DG_DRAG_SETDELAYEDDATA:
				return onDragDelayedDataSetted.NotifyAll (*specItem, eventArg);

			case DG_DRAG_ENTER:
				return onDragEntered.NotifyAll (*specItem, eventArg);

			case DG_DRAG_OVER:
				return onDragMoved.NotifyAll (*specItem, eventArg);

			case DG_DRAG_LEAVE:
				return onDragLeft.NotifyAll (*specItem, eventArg);

			case DG_DRAG_DROP:
				return onDragDropped.NotifyAll (*specItem, eventArg);

			default:
				break;
		}
		return 0;
	}
};


// --- ItemWheelNotifierBase -------------------------------------------------------------------------------------------

class ItemWheelNotifierBase
{
public:
	virtual ~ItemWheelNotifierBase ();

	virtual short	NotifyWheel (const WheelEventArg& eventArg, Item* item) = 0;
};


// --- ItemWheelNotifierBase -------------------------------------------------------------------------------------------

template <typename ItemType>
class ItemWheelNotifier : public ItemWheelNotifierBase
{
public:
	virtual ~ItemWheelNotifier () {}

	EventNotifier<ItemType, const WheelEventArg, short> onWheelEntered;
	EventNotifier<ItemType, const WheelEventArg, short> onWheelTracked;
	EventNotifier<ItemType, const WheelEventArg, short> onWheelExited;

	virtual short	NotifyWheel (const WheelEventArg& eventArg, Item* item) override
	{
		ItemType* specItem = dynamic_cast<ItemType*> (item);
		if (specItem == nullptr)
			return 0;

		switch (eventArg.subMessage) {
			case DG_TSM_TRACKENTER:
				return onWheelEntered.NotifyAll (*specItem, eventArg);

			case DG_TSM_TRACKING:
				return onWheelTracked.NotifyAll (*specItem, eventArg);

			case DG_TSM_TRACKEXIT:
				return onWheelExited.NotifyAll (*specItem, eventArg);

			default:
				break;
		}
		return 0;
	}
};

// --- ItemTrackNotifierBase -------------------------------------------------------------------------------------------

class ItemTrackNotifierBase
{
public:
	virtual ~ItemTrackNotifierBase ();

	virtual short	NotifyTrack (const ItemTrackEventArg& eventArg, Item* item) = 0;
};


// --- ItemTrackNotifier -----------------------------------------------------------------------------------------------

template <typename ItemType>
class ItemTrackNotifier : public ItemTrackNotifierBase
{
public:
	virtual ~ItemTrackNotifier () {}

	EventNotifier<ItemType, const ItemTrackEventArg, short> onItemTrackEntered;
	EventNotifier<ItemType, const ItemTrackEventArg, short> onItemTracked;
	EventNotifier<ItemType, const ItemTrackEventArg, short> onItemTrackExited;

	virtual short	NotifyTrack (const ItemTrackEventArg& eventArg, Item* item) override
	{
		ItemType* specItem = dynamic_cast<ItemType*> (item);
		if (specItem == nullptr)
			return 0;

		switch ((Int32) (eventArg)) {
			case DG_TSM_TRACKENTER:
				return onItemTrackEntered.NotifyAll (*specItem, eventArg);

			case DG_TSM_TRACKEXIT:
				return onItemTrackExited.NotifyAll (*specItem, eventArg);

			default:
				return onItemTracked.NotifyAll (*specItem, eventArg);
		}
	}
};


// --- ItemFocusNotifierBase -------------------------------------------------------------------------------------------

class ItemFocusNotifierBase
{
public:
	virtual ~ItemFocusNotifierBase ();

	virtual short	NotifyFocus (const ItemFocusChangeEventArg& eventArg, Item* item) = 0;
};


// --- ItemFocusNotifier -----------------------------------------------------------------------------------------------

template <typename ItemType>
class ItemFocusNotifier : public ItemFocusNotifierBase
{
public:
	virtual ~ItemFocusNotifier () {}

	EventNotifier<ItemType, const ItemFocusChangeEventArg, short> onItemFocusGained;
	EventNotifier<ItemType, const ItemFocusChangeEventArg, short> onItemFocusLost;

	virtual short	NotifyFocus (const ItemFocusChangeEventArg& eventArg, Item* item) override
	{
		ItemType* specItem = dynamic_cast<ItemType*> (item);
		if (specItem == nullptr)
			return 0;

		switch ((Int32) (eventArg)) {
			case 0:
				return onItemFocusLost.NotifyAll (*specItem, eventArg);

			case 1:
				return onItemFocusGained.NotifyAll (*specItem, eventArg);

			default:
				break;
		}
		return 0;
	}
};


// --- FilterCharNotifierBase ------------------------------------------------------------------------------------------

class FilterCharNotifierBase
{
public:
	virtual ~FilterCharNotifierBase ();

	virtual short	NotifyFilterChar (const FilterCharEventArg& eventArg, Item* item) = 0;
};


// --- FilterCharNotifier ----------------------------------------------------------------------------------------------

template <typename ItemType>
class FilterCharNotifier : public FilterCharNotifierBase
{
public:
	virtual ~FilterCharNotifier () {}

	EventNotifier<ItemType, const FilterCharEventArg, short> onFilterChar;

	virtual short	NotifyFilterChar (const FilterCharEventArg& eventArg, Item* item) override
	{
		ItemType* specItem = dynamic_cast<ItemType*> (item);
		if (specItem == nullptr)
			return 0;

		return onFilterChar.NotifyAll (*specItem, eventArg);
	}
};

}

#endif // DG_ITEM_EVENT_NOTIFIERS_HPP
