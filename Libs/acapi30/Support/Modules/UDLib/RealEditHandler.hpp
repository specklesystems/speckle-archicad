#ifndef REAL_EDIT_HANDLER_HPP
#define REAL_EDIT_HANDLER_HPP

// from GSRoot
#include "Owner.hpp"
#include "OnHeap.hpp"

// from UD
#include "UDDefinitions.hpp"
#include "DisplayerRefresherOwner.hpp"
#include "SimplifiedDataControlTypes.hpp"

namespace DG {
	class RealEdit;
	class Panel;
}

namespace UD {
	class RealEditValueChangeObserver;
	class DoubleDisplayer;
}

namespace UD {

class UD_DLL_EXPORT RealEditHandler
{
public:
	RealEditHandler (GS::Owner<DG::RealEdit> editControlInit,
					 GS::Owner<DisplayerRefresher<DoubleDisplayer>> displayerRefresherInit,
					 GS::Owner<DoubleValueApplier> valueApplierInit,
					 const std::function<void (DoubleDisplayer& realEditDisplayer)> initializer);

	virtual ~RealEditHandler ();

	void MoveAndResize (short horizontalDelta, short verticalDelta, short horizontalGrow, short verticalGrow);
	void Move	(short horizontalDelta, short verticalDelta);
	void Resize (short horizontalGrow, short verticalGrow);

private:
	GS::Owner<DG::RealEdit> editControl;
	GS::OnHeap<RealEditValueChangeObserver>		editValueChangeObserver;
	DisplayerRefresherOwner<DoubleDisplayer>	displayerRefresherOwner;
};

UD_DLL_EXPORT GS::Owner<DG::RealEdit> CreateLengthEdit (const DG::Panel& panel, short item);

}


#endif


