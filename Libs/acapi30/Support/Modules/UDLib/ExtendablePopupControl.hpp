#ifndef GS_COMMONUI_EXTENDABLEPOPUPCONTROL_HPP
#define GS_COMMONUI_EXTENDABLEPOPUPCONTROL_HPP


#include "UDDefinitions.hpp"

#include "UCPopup.hpp"


namespace UD {
	class ExtendablePopupControlObserver;
}


namespace UD {


class UD_DLL_EXPORT ExtendablePopupControlItemData {
private:
	GS::UniString	text;
	bool			isPrimaryItem;
	bool			isVisible;

public:
	ExtendablePopupControlItemData ();

	const GS::UniString&	GetText (void) const;
	void					SetText (const GS::UniString& inText);

	bool					IsPrimaryItem (void) const;
	void					SetPrimaryItem (bool inIsPrimaryItem);

	bool					IsVisible () const;
	void					SetVisibility (bool inIsVisible);
};


class UD_DLL_EXPORT ExtendablePopupControl:	public GS::EventSource,
																public DG::UserControlObserver
{
private:
	class PopupItemUserData
	{
	private:
		UIndex	itemIndex;
		bool	isMoreOptionsItem;
	public:
		PopupItemUserData ();

		UIndex	GetItemIndex (void) const;
		void	SetItemIndex (UIndex inItemIndex);

		bool	IsMoreOptionsItem (void) const;
		void	SetMoreOptionsItem (bool inIsMoreOptionsItem);
	};

	UC::PopupControl ucPopupControl;

	GS::Array<ExtendablePopupControlItemData>	items;
	UIndex										selectedItem;

	bool areSecondaryItemsVisible;

	void	ClearUCPopupControl (void);
	void	FillUCPopupControl (void);
	void	RefreshUCPopupControlStatus (void);

	virtual void	UserControlChanged (const DG::UserControlChangeEvent& ev) override;

public:
	ExtendablePopupControl (const DG::Panel& panel, short item);
	ExtendablePopupControl (const DG::Panel& panel, const DG::Rect& rect);
	~ExtendablePopupControl ();

	void	Attach (ExtendablePopupControlObserver& observer);
	void	Detach (ExtendablePopupControlObserver& observer);

	void	SetVisibility (bool visibility);

	void	Move (short hDisp, short vDisp);
	void	Resize (short hGrow, short vGrow);

	void	SetItems (const GS::Array<ExtendablePopupControlItemData>& inItems);

	UIndex	GetSelectedItem (void) const;
	void	SelectItem (UIndex inSelectedItem);
};


class UD_DLL_EXPORT ExtendablePopupControlObserver: public GS::EventObserver
{
friend class ExtendablePopupControl;

protected:
	virtual void	SelectionChanged (const ExtendablePopupControl& source);
};


} // namespace UD


#endif