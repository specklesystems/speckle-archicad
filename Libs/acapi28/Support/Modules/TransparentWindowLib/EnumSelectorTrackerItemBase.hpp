#ifndef GS_TRACKING_ENUMSELECTORTRACKERITEMBASE_HPP
#define GS_TRACKING_ENUMSELECTORTRACKERITEMBASE_HPP

#include "TrackerItemBase.hpp"
#include "UCPopup.hpp"

namespace GS
{
template<typename T>
class Friend;
}

namespace DG
{
class LowLevelKeyboardHandler;
}

namespace NewDisplay
{
class DrawingItem;
}

namespace Tracking
{

class EnumSelectorKeyboardHandler;

class TRANSPARENTWINDOWLIB_DLL_EXPORT EnumSelectorTrackerItemBase : public Tracking::TrackerItemBase,
	public DG::UserControlObserver
{
public:
	~EnumSelectorTrackerItemBase ();

	enum class DisplayType
	{
		IconOnly,
		TextOnly,
		IconText
	};

	EnumSelectorTrackerItemBase ();
	void SetDisplayType (const DisplayType&);
	void RightArrowKeyPressed (GS::Friend<EnumSelectorKeyboardHandler>);

protected:
	struct ItemConfigBase
	{
		DG::Icon icon;
		GS::UniString text;
	};

	virtual void Draw (NewDisplay::NativeContext& context, const DG::Rect& itemRect, bool selected, short itemWidth[4]) override;
	virtual void FocusDefaultItem () override;
	virtual short GetHeight () const override;
	virtual bool IsInInput () const override;
	virtual short GetColumnWidth (short (&itemWidth)[4]) const override;

	virtual const ItemConfigBase* GetItemConfigForCurrentValue () const = 0;
	virtual bool ConfigMatchesCurrentValue (const ItemConfigBase&) const = 0;
	virtual UIndex GetItemConfigCount () const = 0;
	virtual const ItemConfigBase& GetItemConfig (UIndex index) const = 0;

	DisplayType displayType = DisplayType::TextOnly;
	mutable GS::Owner<UC::PopupControl> popupControlOwner;
	GS::Owner<NewDisplay::DrawingItem> drawingItemOwner;
	GS::Owner<DG::TextEdit> textEditOwner;

	void UpdateControlsWithItemConfig (const ItemConfigBase& itemConfig);
	virtual DG::Item* ActivateEditMode (DG::Palette& palette, short itemWidth[4]) override;

private:
	virtual void DeactivateEditMode () override;

	GS::Owner<UC::PopupControl> CreateUCPopupControl (DG::Palette& palette, const DG::Rect& itemRect);
	short CalculateMaxTextWidth (const TE::Font& teFont) const;

	GS::Owner<DG::LowLevelKeyboardHandler> keyboardHandler;
};

}

#endif // GS_TRACKING_ENUMSELECTORTRACKERITEMBASE_HPP
