#ifndef TEXT_EDIT_HANDLER
#define TEXT_EDIT_HANDLER

// from GSRoot
#include "Owner.hpp"
#include "OnHeap.hpp"

// from UD
#include "UDDefinitions.hpp"
#include "DisplayerRefresherOwner.hpp"
#include "SimplifiedDataControlTypes.hpp"

namespace DG {
	class TextEdit;
	class Panel;
}

namespace UD {
	class StringDisplayer;
	class TextEditValueChangeObserver;
}

namespace UD {

class UD_DLL_EXPORT TextEditHandler
{
public:
	TextEditHandler (GS::Owner<DG::TextEdit> editControlInit,
					 GS::Owner<DisplayerRefresher<StringDisplayer>> displayerRefresherInit,
					 GS::Owner<StringValueApplier> valueApplierInit,
					 const std::function<void (StringDisplayer& textEditDisplayer)> initializer);

	virtual ~TextEditHandler ();

	void Move (short horizontalDelta, short verticalDelta);
	void Resize (short horizontalGrow, short verticalGrow);

private:
	GS::Owner<DG::TextEdit> editControl;
	GS::OnHeap<TextEditValueChangeObserver>		editValueChangeObserver;
	DisplayerRefresherOwner<StringDisplayer>	displayerRefresherOwner;
};

UD_DLL_EXPORT GS::Owner<DG::TextEdit> CreateTextEdit (const DG::Panel& panel, short item);

}


#endif


