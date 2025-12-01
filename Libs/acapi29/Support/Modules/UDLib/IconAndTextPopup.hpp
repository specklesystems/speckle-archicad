#ifndef ICONANDTEXTPOPUP_HPP
#define ICONANDTEXTPOPUP_HPP

#include "UDDefinitions.hpp"

namespace UD
{

class UD_DLL_EXPORT IconAndTextPopup :	public DG::ModalDialog,
										public DG::PanelObserver
{
public:
	IconAndTextPopup (const DG::NativeRect& inParentRect, short dialogWidth, short dialogHeight);
	virtual ~IconAndTextPopup ();

	void					PanelOpened (const DG::PanelOpenEvent& ev) override;

	virtual DG::Icon		GetIcon () const = 0;
	virtual GS::UniString	GetText () const = 0;

protected:
	DG::NativeRect	parentRect;
	short			dialogWidth;
	short			dialogHeight;
	DG::IconItem	iconItem;
	DG::LeftText	textItem;
};

}

#endif
