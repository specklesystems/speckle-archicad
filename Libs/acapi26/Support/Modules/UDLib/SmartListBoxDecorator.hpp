#ifndef GS_UD_LD_MULTI_SEL_LISTBOX_DECORATOR_HPP
#define GS_UD_LD_MULTI_SEL_LISTBOX_DECORATOR_HPP

#pragma once

#include "UDDefinitions.hpp"

namespace UD { class ListBox; }
namespace UD { namespace ListDiff { class ListDiffable; } }

namespace UD {

class UD_DLL_EXPORT ListBoxDecorator {
public:
	virtual	void	Decorate (DG::ListBox& listBox, short row, const UD::ListDiff::ListDiffable& item) = 0;
	virtual ~ListBoxDecorator ();
};

} // namespace UD

#endif
