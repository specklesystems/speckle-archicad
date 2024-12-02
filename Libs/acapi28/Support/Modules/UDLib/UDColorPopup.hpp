#ifndef GS_UDCOLORPOPUP_HPP
#define GS_UDCOLORPOPUP_HPP

#include <optional>

#include "Array.hpp"
#include "ColorRecord.hpp"
#include "UCPopup.hpp"
#include "UDDefinitions.hpp"

namespace UD {

// TODO: Replace with either Boost.CircularBuffer or something from GSRoot
class UD_DLL_EXPORT ColorRingBufferAdapter
{
public:
	ColorRingBufferAdapter (GS::Array<ColorRecord>& storage, USize capacity);

	void PushFront (const ColorRecord&);

	ColorRecord&	   Get (UIndex);
	const ColorRecord& Get (UIndex) const;

	USize GetSize () const;
	bool  IsEmpty () const;

	auto begin () { return GetStorage ().BeginFast (); }

	auto end () { return GetStorage ().EndFast (); }

private:
	GS::Array<ColorRecord>&		  GetStorage ();
	const GS::Array<ColorRecord>& GetStorage () const;

	GS::Array<ColorRecord>* mStorage;
	USize					mCapacity;
};

class ColorPopupObserver;

class UD_DLL_EXPORT ColorPopup : public UC::PopupControl,
								 private DG::UserControlObserver
{
public:
	enum ItemType : UIndex {
		OriginalColor = 1, // Indexes are 1-based according to the UC::Popup
		CustomColor	  = 2,
		ChooseCustom  = 3,
		FirstRecent	  = 5
	};

	enum class ReloadIfSet : bool {
		No	= false,
		Yes = true,
	};

	ColorPopup (const DG::Panel& panel, short item, ColorRingBufferAdapter& recentColors, bool hasOrigColorItem = true);
	ColorPopup (const DG::Panel&		   panel,
				const DG::Rect&			   rect,
				DG::UserControl::FrameType frameType,
				ColorRingBufferAdapter&	   recentColors,
				bool					   hasOrigColorItem = true);
	virtual ~ColorPopup () override;

	void Attach (ColorPopupObserver& observer);
	void Detach (ColorPopupObserver& observer);

	void UpdateWith (Gfx::Color customColor, bool isOriginalColorSelected = false);
	void ReloadItems ();

	bool SelectOriginalColor (ReloadIfSet = ReloadIfSet::Yes);
	bool IsOriginalColorSelected () const;

	bool					  SelectColor (Gfx::Color color, ReloadIfSet = ReloadIfSet::Yes);
	std::optional<Gfx::Color> GetSelectedColor () const;

private:
	ColorPopup (ColorPopup&&) = delete;

	void SelectItem (UIndex) = delete;

	UIndex GetItemIndex (ItemType itemType) const;

	virtual void UserControlChanged (const DG::UserControlChangeEvent& ev) override;

	void Init ();
	void NotifyObservers () const;

	ColorRecord				mCustomColor;
	ColorRingBufferAdapter* mRecentColors;
	UIndex					mSelectedIndex;
	bool					mHasOrigColorItem;
	bool					mIsUpdating = false;
};

class UD_DLL_EXPORT ColorPopupObserver : public GS::EventObserver
{
	friend ColorPopup;

protected:
	virtual void ColorChanged (const ColorPopup& source);
};

} // namespace UD

#endif // GS_UDCOLORPOPUP_HPP
