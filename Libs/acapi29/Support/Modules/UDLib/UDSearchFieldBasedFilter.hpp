#ifndef GS_UD_SEARCHFIELDBASEDFILTER_HPP
#define GS_UD_SEARCHFIELDBASEDFILTER_HPP

#include "UDIFilter.hpp"
#include "UDImprovedSearchTextEdit.hpp"

// from DG
#include "DGLowLevelKeyboardHandling.hpp"

// from GSRoot
#include "GSTime.hpp"
#include "Owner.hpp"
#include "UniString.hpp"

// from STL
#include <functional>
#include <memory>
#include <vector>


namespace UD {


class IFilterableItem;
using IFilterableItemRef = std::reference_wrapper<IFilterableItem>;
using IFilterableItemRefContainer = std::vector<IFilterableItemRef>;

class SearchFieldBasedFilterObserver;
class SearchFieldBasedFilterCache;


class UD_DLL_EXPORT SearchFieldBasedFilter :	public IFilter,
												public ImprovedSearchEditObserver,
												public DG::LowLevelKeyboardHandler,
												public DG::PanelObserver,
												public GS::EventSource,
												public std::enable_shared_from_this<SearchFieldBasedFilter>
{
protected:
	IFilterableItemRefContainer			filterableItemRefContainer;
	Owner<SearchFieldBasedFilterCache>	filterCache;
	UD::ImprovedSearchEdit				searchField;

public:

	SearchFieldBasedFilter (DG::Dialog&			dialog,
							const DG::Panel&	panel,
							IFilterableItem&	filterableItem,
							short				searchEditItem,
							GS::UniString		searchHintText);

	SearchFieldBasedFilter (DG::Dialog&							dialog,
							const DG::Panel&					panel,
							const IFilterableItemRefContainer&	filterableItemRefContainer,
							short								searchEditItem,
							GS::UniString						searchHintText);

	SearchFieldBasedFilter (DG::Dialog&							dialog,
							const DG::Panel&					panel,
							const IFilterableItemRefContainer&	filterableItemRefContainer,
							const DG::Rect&						searchEditRect,
							GS::UniString						searchHintText);

	virtual ~SearchFieldBasedFilter () override;

	void			Init ();

	void			Attach (SearchFieldBasedFilterObserver& observer);
	void			Detach (SearchFieldBasedFilterObserver& observer);

	void			Enable ();
	void			Disable ();

	DG::Rect		GetBoundingRect () const;

	void			SetSearchText (const GS::UniString& searchText);
	GS::UniString	GetSearchText () const;

	void			SetSearchHintText (const GS::UniString& hintText);
	void			SetSearchHelp (short);

	void			Resize (short hGrow, short vGrow);
	void			MoveAndResize (short dhMove, short dvMove, short dhGrow, short dvGrow);

	void			SetToolTipText (GS::UniString);
	void			ResetToolTipText (void);

	void			SetStatus (bool enabled);

// DG::PanelObserver implementation

	void			PanelOpened (const DG::PanelOpenEvent& ev) override;
	void			PanelClosed (const DG::PanelCloseEvent& ev) override;

// DG::LowLevelKeyboardHandler implementation

	DG::EventHandlerResultType	KeyPressed (const DG::Key::Code& code, DG::Item** item) override;

// IFilter implementation

	State			GetState		() const override;
	bool			Allow			(const GS::UniString& name) const override;
	bool			IsNarrowerThan	(const IFilterCheckpoint& checkPoint) const override;

	Owner<IFilterCheckpoint>	ToCheckPoint () override;

// ImprovedSearchEditObserver implementation

	void			SearchTextChanged	(const ImprovedSearchEditChangeEvent&) override;
	void			SearchEnded			(const ImprovedSearchEditChangeEvent&) override;

protected:

	void			ClearSearchField ();

private:

	void			ConstructorFunction (DG::Dialog&);

	void			RefreshFilteringOnAllFilterableItems ();

};


// === SearchFieldBasedFilterObserver ==================================================================================


class UD_DLL_EXPORT SearchFieldBasedFilterObserver : public GS::EventObserver {
public:
	virtual void	RefreshFilteringEnded ();
};


// === TextCheckPoint ==================================================================================================


class UD_DLL_EXPORT TextCheckPoint : public IFilterCheckpoint {
private:
	GS::UniString checkpointText;

public:
	explicit TextCheckPoint (GS::UniString);

	const GS::UniString&	GetText () const;

	virtual IFilter::State	GetState () const override;
};


} // namespace UD


#endif
