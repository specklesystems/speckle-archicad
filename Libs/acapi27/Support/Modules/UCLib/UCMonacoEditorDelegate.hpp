#ifndef UCMONACOEDITORDELEGATE_HPP
#define UCMONACOEDITORDELEGATE_HPP

#include "UC.h"
#include <vector>

namespace UC {

class UC_DLL_EXPORT MonacoEditorDelegate
{
public:
	virtual ~MonacoEditorDelegate ();

	virtual void TextChanged (const GS::UniString& oldText, const GS::UniString& newText) = 0;
	virtual void SelectionChanged (const std::vector<DG::CharRange>& oldSelection, const std::vector<DG::CharRange>& newSelection) = 0;
};

}

#endif
