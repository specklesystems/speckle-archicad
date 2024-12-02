#ifndef UDSETTINGSCOMBLISTTABPAGE_HPP
#define UDSETTINGSCOMBLISTTABPAGE_HPP

#pragma once

#include	<memory>
#include	"UDDefinitions.hpp"
#include	"DGUtility.hpp"
#include	"DGListBox.hpp"
#include	"Ref.hpp"
#include	"Array.hpp"

#include	"UDFilterableListBox.hpp"
#include	"UDSearchFieldBasedFilter.hpp"

namespace NewDisplay {
	class ListBoxUpdateEventContext;
}

namespace UD {

class SettingsCombControl;

class UD_DLL_EXPORT SettingsCombListTabPage :	public DG::TabPage,
												public DG::PanelObserver,
												public DG::CompoundItemObserver,
												public DG::ButtonItemObserver,
												public DG::ListBoxObserver,
												public UD::SearchFieldBasedFilterObserver
{
public:
	enum SortOrder {
		Ascending,
		Descending
	};

	class UD_DLL_EXPORT GroupSeparatorObject : public GS::Object {
	public:
		GroupSeparatorObject ();
		~GroupSeparatorObject ();
	private:
		GroupSeparatorObject (const GroupSeparatorObject&) = delete;
		GroupSeparatorObject& operator= (const GroupSeparatorObject&) = delete;
	};

private:


	class ObjectWithHoverInfo : public GS::Object {
	public:
		enum HoverState {
			NOHOVER,
			HOVER
		};

		ObjectWithHoverInfo (GS::Ref<GS::Object> object, HoverState hoverState = NOHOVER);

		virtual	GS::Object*	Clone (void) const override;

		GS::Ref<GS::Object> GetObject () const;

		HoverState GetHoverState () const;
		void SetHoverState (HoverState hoverState);

	private:
		ObjectWithHoverInfo (const ObjectWithHoverInfo&);
		ObjectWithHoverInfo& operator= (const ObjectWithHoverInfo&);

		GS::Ref<GS::Object> object;
		HoverState hoverState;
	};

	GS::Array<GS::Ref<GS::Object>>&		setsCombRefArr;
	std::weak_ptr<SettingsCombControl>	settingsCombControl;

	DG::Button											newButton;
	DG::Button											deleteButton;
	DG::IconButton										importButton;
	DG::IconButton										exportButton;
	GS::Owner<UD::FilterableListBoxHandler>				listBox;

	std::shared_ptr<UD::SearchFieldBasedFilter>			mSearchFieldBasedFilter;

	SortOrder							sortOrder;
	
	short								textColumnId;
	short								iconColumnId;

	bool								hasHeader;

public:
	SettingsCombListTabPage (const DG::TabControl&					tabControl,
							 GS::Array<GS::Ref<GS::Object>>&		setsCombRefArr,
							 std::shared_ptr<SettingsCombControl>	settingsCombControl,
							 const DG::Rect&						rect,
							 DG::ListBox::ScrollType				scroll,
							 DG::ListBox::PartialItemType			part,
							 DG::ListBox::HeaderFlag				headerFlag,
							 short									headerSize,
							 DG::ListBox::FrameType					frameType,
							 DG::Font::Style						fontStyle,
							 DG::Font::Size							fontSize,
							 short									itemSize,
							 const GS::Array<short>&				searchTabIndex,
							 bool									typeIsMultiSel);

	void			Initialize ();

	void			DisableInteractivity ();
	void			AdjustTabPageWidth (const DG::Rect& rect);

	//DG::PanelObserver
	virtual void	PanelClosed (const DG::PanelCloseEvent& ev) override;
	virtual void	PanelResized		(const DG::PanelResizeEvent& ev) override;
	virtual void	PanelResizeExited	(const DG::PanelResizeEvent& ev) override;
	virtual void	PanelContextHelpRequested	(const DG::PanelHelpEvent& ev, GS::UniString* contextHelpAnchor) override;

	//DG::ButtonItemObserver
	virtual void	ButtonClicked (const DG::ButtonClickEvent& ev) override;

	//DG::ListBoxObserver
	virtual void	ListBoxClicked (const DG::ListBoxClickEvent& ev) override;
	virtual void	ListBoxDoubleClicked (const DG::ListBoxDoubleClickEvent& ev) override;
	virtual void	ListBoxSelectionChanged (const DG::ListBoxSelectionEvent& ev) override;
	virtual void	ListBoxHeaderItemClicked (const DG::ListBoxHeaderItemClickEvent& ev) override;
	virtual void	ListBoxTabFieldUpdate (const DG::ListBoxTabItemUpdateEvent& ev) override;
	virtual void	ListBoxHoverStarted (const  DG::ListBoxHoverEvent& ev) override;
	virtual void	ListBoxHoverEnded (const  DG::ListBoxHoverEvent& ev) override;
	virtual void	ListBoxOverlayUpdate (const  DG::ListBoxItemUpdateEvent& ev, DG::Rect* imageRect) override;

	void			Refresh (bool selectFirstElemInListBoxIfNothingSelected = false, bool wasNewElemAdded = false);
	void			RefreshControls ();

	void			EnumerateAllItems (const std::function<void (const GS::Ref<GS::Object>&)>& fn) const;
	void			EnumerateSelectedItems (const std::function<void (const GS::Ref<GS::Object>&)>& fn) const;

	UIndex			GetItemIndex (const GS::Ref<GS::Object>& obj) const;

	static bool		IsSeparatorObject (const GS::Ref<GS::Object>& obj);

	virtual void	RefreshFilteringEnded () override;

private:
	void			DrawIconToContext (NewDisplay::ListBoxUpdateEventContext& context, const DG::Icon& icon, short begPosX, float alpha = 1.0f);

	void			HandleDoubleClick (short listItem);

	USize			GetNotSeparatorListBoxItemsCount ();
};

} //namespace UD

#endif
