#ifndef VERTICALSEPARATORMENUITEM_HPP
#define VERTICALSEPARATORMENUITEM_HPP
#pragma once

#include "FloatingMenuItem.hpp"

class FloatingMenu;

namespace FloatingWindow {

class TRANSPARENTWINDOWLIB_DLL_EXPORT VerticalSeparatorMenuItem : public FloatingMenuItem {
public:
	VerticalSeparatorMenuItem ();
	virtual ~VerticalSeparatorMenuItem ();

	virtual void	DrawHoverAtTheBeginning (NewDisplay::NativeContext&, const ItemHighlightInfo&, const FloatingMenuAppearance&, const DG::Rect&) const override;
	virtual void	DrawHoverAtTheEnd (NewDisplay::NativeContext&, const ItemHighlightInfo&, const FloatingMenuAppearance&, const DG::Rect&) const override;
	virtual void	DrawSelection (NewDisplay::NativeContext&, const ItemHighlightInfo&, const FloatingMenuAppearance&, const DG::Rect&) const override;
	virtual void	DrawMark (NewDisplay::NativeContext&, const ItemHighlightInfo&, const FloatingMenuAppearance&, const DG::Rect&) const override;

	virtual UInt16			GetTextWidth (bool smallFont) const override;
	virtual UInt16			GetImageHeight (double resolutionFactor) const override;
	virtual UInt16			GetImageWidth (double resolutionFactor) const override;
};

} //FloatingWindow

#endif
