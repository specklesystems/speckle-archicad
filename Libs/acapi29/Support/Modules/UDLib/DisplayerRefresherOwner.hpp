#ifndef DISPLAYER_REFRESHER_OWNER
#define DISPLAYER_REFRESHER_OWNER

// from GSRoot
#include "Owner.hpp"

// from UD
#include "DisplayerRefresher.hpp"

namespace UD {

template<typename DisplayerType>
class DisplayerRefresherOwner
{
public:
	DisplayerRefresherOwner (GS::Owner<DisplayerRefresher<DisplayerType>> refresherInit,
							 GS::Owner<DisplayerType> displayerInit,
							 const std::function<void (DisplayerType& displayerToInitialize)> initializeDisplayer) :
		refresher (refresherInit.Pass ()),
		displayer (displayerInit.Pass ())
	{
		initializeDisplayer (*displayer);
		refresher->AttachDisplayer (*displayer);
	}

private:
	GS::Owner<DisplayerRefresher<DisplayerType>> refresher;
	GS::Owner<DisplayerType> displayer;
};

}

#endif