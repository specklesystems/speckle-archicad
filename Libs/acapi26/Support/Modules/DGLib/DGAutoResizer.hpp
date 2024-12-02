// *********************************************************************************************************************
// File:			DGAutoResizer.hpp
//
// Description:		Panel related classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	SzaM
// *********************************************************************************************************************

#ifndef DGAUTORESIZER_HPP
#define DGAUTORESIZER_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "DGPanelEventArgs.hpp"

// --- Predeclarations -------------------------------------------------------------------------------------------------

namespace DG {
	class Panel;
}

namespace DG {

// --- Class declarations ----------------------------------------------------------------------------------------------

// --- AutoResizer -----------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT AutoResizer
{
protected:
	AutoResizer ();
public:
	AutoResizer (const AutoResizer& ar) = delete;
	AutoResizer&	operator= (const AutoResizer& ar) = delete;

	virtual ~AutoResizer ();

	virtual const std::function<void (const Panel&, ResizeEventArg&)>	GetResizeFunction ();
	virtual const std::function<void (const Panel&, ResizeEventArg&)>	GetResizeEnteredFunction ();
	virtual const std::function<void (const Panel&, ResizeEventArg&)>	GetResizeExitedFunction ();
};


// -> keeps padding between the items, and the percentage of them
class DG_DLL_EXPORT ProportionalResizer : public AutoResizer
{
	struct ItemResizeData
	{
		Item*	item		= nullptr;
		double	percentage	= 0.0;
		short	padding		= 0;
		// ---  On Windows item position and size are not available during resize!
		short	position	= 0;
		short	size		= 0;
		// ---
	};

	GS::Array<ItemResizeData>	dataArray;

	short 	allPadding = 0;
	short	panelSize = 0; // --- On Windows panelSize is not available during resize!
	bool	isInitialized = false;

private:
	void	InitSizes ();

protected:
	void	Helper ();
	Item*	GetItem (UIndex index) const;
	void	AddToPanelSize (short panelSizeToAdd);

	template <typename... Args>
	void	Helper (Item& item, Args&... args);

	Rect			GetTabpageRelativeRect (const Item* item) const;

	virtual short	GetStartAnchor (const Item* item) const = 0;
	virtual short	GetEndAnchor (const Item* item) const = 0;
	virtual short	GetItemSize (const Item* item) const = 0;
	virtual short	GetAvailableSize () const = 0;
	virtual void	UpdateAvailableSize (const ResizeEventArg& ev) = 0;

	virtual void	ResizeItem (Item* item, short newAnchor, short newSize) const = 0;

public:
	virtual const std::function<void (const Panel&, ResizeEventArg&)>	GetResizeFunction () override;
	virtual const std::function<void (const Panel&, ResizeEventArg&)>	GetResizeEnteredFunction () override;
};


class DG_DLL_EXPORT HorizontalResizer: public ProportionalResizer
{
private:
	HorizontalResizer () = default;

	virtual short	GetStartAnchor (const Item* item) const override;
	virtual short	GetEndAnchor (const Item* item) const override;
	virtual short	GetItemSize (const Item* item) const override;
	virtual short	GetAvailableSize () const override;
	virtual void	UpdateAvailableSize (const ResizeEventArg& ev) override;

	virtual void	ResizeItem (Item* item, short newAnchor, short newSize) const override;

public:
	template <typename... Args>
	static GS::Ref<HorizontalResizer>	Create (Item& item1, Item& item2, Args&... args);
};


class DG_DLL_EXPORT VerticalResizer: public ProportionalResizer
{
private:
	VerticalResizer () = default;

	virtual short	GetStartAnchor (const Item* item) const override;
	virtual short	GetEndAnchor (const Item* item) const override;
	virtual short	GetItemSize (const Item* item) const override;
	virtual short	GetAvailableSize () const override;
	virtual void	UpdateAvailableSize (const ResizeEventArg& ev) override;
	virtual void	ResizeItem (Item* item, short newAnchor, short newSize) const override;


public:
	template <typename... Args>
	static GS::Ref<VerticalResizer>	Create (Item& item1, Item& item2, Args&... args);
};


// -> keeps the size of the elements first, and then it resizes the elements to the expected size
class DG_DLL_EXPORT TwoItemHorizontalResizer: public AutoResizer
{
	const short eps = 3;

	double	percentOfFirst = 0.5;
	short	paddingBeforeLeftItem = 0;
	short	paddingBetweenItems = 0;
	short	paddingAfterRightItem = 0;

	// --- on windows item rects are not available while resizing
	short	leftItemWidth = 0;
	short	rightItemWidth = 0;
	short	panelWidth = 0;
	// ---

	Item& leftItem;
	Item& rightItem;

private:
	TwoItemHorizontalResizer (Item& leftItem, Item& rightItem, double percentOfFirstItem = 0.5);

	short 	CalculateWidthToDivide () const;
	bool 	IsItemTooSmall (short itemNum) const;
	bool 	IsItemTooBig (short itemNum) const;
	short	GrowOneItem (short hGrow);

public:
	static GS::Ref<TwoItemHorizontalResizer>	Create (Item& leftItem, Item& rightItem, double percentOfFirstItem = 0.5);

	virtual const std::function<void (const Panel&, ResizeEventArg&)>	GetResizeFunction () override;
	virtual const std::function<void (const Panel&, ResizeEventArg&)>	GetResizeEnteredFunction () override;
};


class DG_DLL_EXPORT ItemRelativeResizer: public AutoResizer
{
public:
	enum class LayoutConstraint {
		ConnectHorizontally,
		ConnectVertically
	};

	enum class LayoutType {
		Move,
		Resize
	};

	enum class LayoutDirection {
		Towards,
		Reverse
	};

private:
	LayoutConstraint layoutConstraint;
	LayoutType layoutType;
	LayoutDirection layoutDirection;

	Item& resizedItem;

	ItemRelativeResizer (Item& resizedItem, Item& referenceItem, LayoutConstraint layoutConstraint, LayoutType layoutType, LayoutDirection layoutDirection);

public:
	virtual ~ItemRelativeResizer ();

	static GS::Ref<ItemRelativeResizer>	Create (Item& referenceItem, Item& baseItem, LayoutConstraint layoutConstraint, LayoutType layoutType, LayoutDirection layoutDirection);
};


template <typename... Args>
void ProportionalResizer::Helper (DG::Item& item, Args&... args)
{
	ItemResizeData data;
	data.item = &item;

	dataArray.Push (data);
	Helper (std::forward<Args&>(args)...);
}


template <typename... Args>
GS::Ref<HorizontalResizer>	HorizontalResizer::Create (Item& item1, Item& item2, Args&... args)
{
	GS::Ref<HorizontalResizer> resizer = new HorizontalResizer ();
	resizer->Helper (item1);
	resizer->Helper (item2);
	resizer->Helper (std::forward<Args&>(args)...);
	return resizer;
}


template <typename... Args>
GS::Ref<VerticalResizer> VerticalResizer::Create (Item& item1, Item& item2, Args&... args)
{
	GS::Ref<VerticalResizer> resizer = new VerticalResizer ();
	resizer->Helper (item1);
	resizer->Helper (item2);
	resizer->Helper (std::forward<Args&>(args)...);
	return resizer;
}

}	// namespace DG

#endif // DGAUTORESIZER_HPP
