#ifndef UDIMPROVEDUSERITEM_HPP
#define UDIMPROVEDUSERITEM_HPP

#pragma once

#include "Ref.hpp"

#include "DGDialog.hpp"
#include "UDDefinitions.hpp"
#include "UDUserItemInfoTag.hpp"
#include "DrawingItem.hpp"


namespace DG {
	class TabPage;
}


namespace UD {


class ImprovedUserItemObserver;


// --- ImprovedUserItem ---------------------------------------------------------------------------------------

class UD_DLL_EXPORT ImprovedUserItem :	public NewDisplay::DrawingItem,
										public DG::UserItemObserver,
										public DG::PanelObserver,
										public UserItemInfoTagProperty
{
	friend class ImprovedUserItemObserver;
public:
	ImprovedUserItem (DG::TabPage& tabPage, const DG::Panel& panel, short item);

	~ImprovedUserItem ();

	void	Attach (ImprovedUserItemObserver& observer);
	void	Detach (ImprovedUserItemObserver& observer);

	virtual void	DisableInfoTag ()	override;
	virtual void	EnableInfoTag ()	override;
	virtual void	PanelIdle (const DG::PanelIdleEvent& ev) override;

	UInt64			GetSelectedItemPosition (DG::Rect* elemRect, bool* isMultipleElements, bool* fixPosition) const;

private:
	virtual void	PanelOpened (const DG::PanelOpenEvent& ev) override;
	virtual	void	PanelClosed (const DG::PanelCloseEvent& ev) override;

	virtual UserItemInfoTag::MenuItemRowArray	CreateMenuItemRowArray () const override;

	DG::Dialog* dialog;
	Int32		infoTagDisablerGuard;
};



class UD_DLL_EXPORT ImprovedUserItemObserver : public DG::UserItemObserver
{
public:
	ImprovedUserItemObserver ();
	virtual ~ImprovedUserItemObserver ();

	virtual void			CreateMenuItemRowArray	(UD::UserItemInfoTag::MenuItemRowArray& out) const = 0;
	virtual UInt64			GetSelectedItemPosition (DG::Rect* elemRect, bool* isMultipleElements, bool* fixPosition) const = 0;
};

}

#endif //UDIMPROVEDUSERITEM_HPP
