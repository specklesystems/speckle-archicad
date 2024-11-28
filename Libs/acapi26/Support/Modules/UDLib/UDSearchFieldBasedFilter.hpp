#ifndef GS_UD_SEARCHFIELDBASEDFILTER_HPP
#define GS_UD_SEARCHFIELDBASEDFILTER_HPP
#pragma once

#include <vector>

#include "UDDefinitions.hpp"
#include "UDIFilter.hpp"
#include "DGEditControl.hpp"
#include "DGButton.hpp"
#include "UniString.hpp"
#include "UDTextEditWithHintText.hpp"


namespace UD {

class IFilterableItem;
using IFilterableItemRef = std::reference_wrapper<IFilterableItem>;
using IFilterableItemRefContainer = std::vector<IFilterableItemRef>;

class SearchFieldBasedFilterObserver;
class SearchFieldBasedFilterCache;


class UD_DLL_EXPORT SearchFieldBasedFilter :	public GS::EventSource,
												public IFilter,
												public DG::PanelObserver,
												public DG::CompoundItemObserver,
												public DG::TextEditBaseObserver,
												public DG::ButtonItemObserver
{
protected:
	DG::Dialog&										dialog;
	IFilterableItemRefContainer						filterableItemRefContainer;
	UD::TextEditWithHintText						searchField;
	DG::IconButton									endSearchButton;
	std::shared_ptr<SearchFieldBasedFilterCache>	filterCache;

	GSTimer				timerForRefreshFiltering;
	Int32				delayForRefreshFiltering;

public:
	SearchFieldBasedFilter (DG::Dialog&							dialog,
							const DG::Panel&					panel,
							const IFilterableItemRefContainer&	filterableItemRefContainer,
							const short							textEditResID,
							const short							iconButtonResID,
							const GS::UniString&				defaultText,
							GS::Optional<Int32>					forcedDelayForRefreshFiltering = GS::NoValue);

	SearchFieldBasedFilter (DG::Dialog&							dialog,
							const DG::Panel&					panel,
							const IFilterableItemRefContainer&	filterableItemRefContainer,
							const DG::Rect&						textEditRect,
							const DG::Rect&						iconRect,
							const GS::UniString&				defaultText,
							GS::Optional<Int32>					forcedDelayForRefreshFiltering = GS::NoValue);
	
	void	Attach (SearchFieldBasedFilterObserver& observer);
	void	Detach (SearchFieldBasedFilterObserver& observer);

	virtual State	GetState () const override;

	virtual bool	Allow (const GS::UniString& name) const override;

	virtual bool IsNarrowerThan (const std::shared_ptr<IFilterCheckpoint>& checkPoint) const override;

	virtual std::shared_ptr<IFilterCheckpoint> ToCheckPoint () override;

	virtual void	PanelIdle (const DG::PanelIdleEvent& ev) override;

	virtual void	TextEditChanged (const DG::TextEditChangeEvent& ev) override;
	virtual void	ButtonClicked (const DG::ButtonClickEvent& ev) override;
	virtual void	ItemToolTipRequested (const DG::ItemHelpEvent& ev, GS::UniString* toolTipText) override;

	DG::Rect		GetBoundingRect () const;

	virtual void	RefreshLayout () = 0;
	 
	void			SetSearchText (const GS::UniString& searchText);
	GS::UniString	GetSearchText () const;

	void			SetVariousText (const GS::UniString& variousText);

protected:
	void	HandleTextEditChanged ();
	void	HandleButtonClicked ();

	enum class RefreshFilteringDelayment {
		Enabled,
		Disabled
	};
	void	HandleRefreshFilteringRequest (RefreshFilteringDelayment refreshFilteringDelayment);

private:

	void	ConstructorFunction (const DG::Panel&		panel,
								 GS::Optional<Int32>	forcedDelayForRefreshFiltering);

	void	RefreshFilteringOnAllFilterableItems ();

};


class UD_DLL_EXPORT SearchFieldBasedFilterObserver : public GS::EventObserver {
public:
	virtual void RefreshFilteringEnded ();
};


class UD_DLL_EXPORT TextCheckPoint : public IFilterCheckpoint {
private:
	GS::UniString checkpointText;

public:
	explicit TextCheckPoint (const GS::UniString& newText);

	const GS::UniString& GetText () const;

	virtual IFilter::State GetState () const override;
};


}

#endif
