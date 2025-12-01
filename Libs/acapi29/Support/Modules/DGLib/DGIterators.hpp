#ifndef DG_ITERATORS__H
#define DG_ITERATORS__H

#pragma once

#include <functional>

#include "DG.h"
#include "DGItem.hpp"
#include "DGPanel.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace DG {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef const std::function<void (const Item&)>& ConstItemFn;
typedef const std::function<void (Item&)>& ItemFn;

typedef const std::function<void (const Panel&)>& ConstPanelFn;
typedef const std::function<void (Panel&)>& PanelFn;

class ItemIterator
{
public:
	ItemIterator (const DG::Panel* panel);

public:
	void ForEach (ConstItemFn fn) const;
	void ForEachNotConst (ItemFn fn);

protected:
	const DG::Panel*  panel;
};

class SubPanelIterator
{
public:
	SubPanelIterator (const DG::Panel* panel);

public:
	void ForEach (ConstPanelFn fn) const;
	void ForEachNotConst (PanelFn fn);

protected:
	const DG::Panel*  panel;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace DG
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // DG_ITERATORS__H
