#ifndef UDITEMINFOTAG_HPP
#define UDITEMINFOTAG_HPP

#pragma once

#include <memory>

#include "HashTable.hpp"

#include "FloatingMenu.hpp"

#include "UDDefinitions.hpp"

#include "DGApplicationObserver.hpp"

#include "UDItemInfoTagSettings.hpp"
#include "UDItemInfoTagContentCreator.hpp"


// predeclaration
namespace UD {
	class InfoTagProperty;
}

namespace UD {
namespace ItemInfoTag {

/************************************************************************/
/* ItemInterface                                                        */
/************************************************************************/

class UD_DLL_EXPORT ItemInterface {
protected:
	DG::Item* itemPtr;
public:
	ItemInterface ();
	virtual ~ItemInterface ();

	void Connect (DG::Item& item);

	virtual short		GetItemFromPosition (const DG::Point& position) const = 0;
	virtual DG::Rect	GetSubItemRect (short subItem) const = 0;
	virtual ItemInfoTag::InfoTagContentCreator::MenuItemRowArray CreateMenuItemRowArray (short listItem) const = 0;

protected:
	bool		IsItemEqual (const DG::Item& item) const;
	short		GetItemId () const;
	short		GetPanelId () const;
	DG::Rect	GetItemRect () const;
};


/************************************************************************/
/* DisablerGuardInterface                                                */
/************************************************************************/
class UD_DLL_EXPORT DisablerGuardInterface {
private:
	Int32 _infoTagDisablerGuard;
public:
	explicit DisablerGuardInterface ();

	bool IsDisablingActive () const;
	void Disable ();
	void Enable ();
};


/************************************************************************/
/* ItemDecorator                                                        */
/************************************************************************/

class UD_DLL_EXPORT ItemDecorator :	public ItemInterface,
									public DisablerGuardInterface,
									public DG::PanelObserver,
									public DG::ItemObserver
{
protected:
	GS::Ref<SettingsProvider>	settingsProvider;
	SettingsOptions				settingsOptions;

	bool						_inWheelTrack;
	bool						_isConsistent;

public:
	explicit ItemDecorator (GS::Ref<SettingsProvider> settingsProvider = new SettingsProvider (RegistryBasedSettingsOptions ()));
	virtual ~ItemDecorator ();

	virtual void Connect (DG::Item& item);
	void SetConsistency (bool newValue);
	static void CleanUp ();
	void SetSettingsProvider (GS::Ref<SettingsProvider> settingsProvider);

private:
	virtual void	PanelIdle (const DG::PanelIdleEvent& ev) override;
	virtual	void	PanelClosed (const DG::PanelCloseEvent& ev) override;
	virtual void	PanelResizeEntered (const DG::PanelResizeEvent& ev) override;
	virtual void	PanelResizeExited (const DG::PanelResizeEvent& ev) override;
	virtual void	PanelMoveEntered (const DG::PanelMoveEvent& ev) override;
	virtual void	PanelMoveExited (const DG::PanelMoveEvent& ev) override;
	virtual	void	PanelActivated (const DG::PanelActivateEvent& ev) override;
	virtual void	ItemWheelTrackEntered (const DG::ItemWheelEvent& ev, bool* processed) override;
	virtual void	ItemWheelTrackExited (const DG::ItemWheelEvent& ev, bool* processed) override;

	virtual void	EnsureConsistency ();

private:
	void RebuildAndRefreshInfoTag ();

	void RefreshInfoTag ();

	void ApplySettings ();

	DG::Dialog* GetDialog () const;
};


/************************************************************************/
/* DisablerGuardInterfaceConnector									    */
/************************************************************************/

class UD_DLL_EXPORT DisablerGuardInterfaceConnector {
public:
	DisablerGuardInterfaceConnector ();
	virtual ~DisablerGuardInterfaceConnector ();

	void Connect (std::shared_ptr<DisablerGuardInterface> disablerGuardInterface);
	void DisableInfoTag ();
	void EnableInfoTag ();

private:
	std::weak_ptr<DisablerGuardInterface> disablerGuardInterface;
};


}
}

#endif //UDITEMINFOTAG_HPP
