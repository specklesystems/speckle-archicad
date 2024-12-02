#ifndef GS_FLOATINGWINDOW_ITEMHIGHLIGHTDISPLAYER_HPP
#define GS_FLOATINGWINDOW_ITEMHIGHLIGHTDISPLAYER_HPP
#pragma once

#include "TransparentWindowLibDefinitions.hpp"
#include "FloatingMenuDefinitions.hpp"

namespace FloatingWindow {

class ItemHighlightInfo;
class FloatingMenuAppearance;

class TRANSPARENTWINDOWLIB_DLL_EXPORT Highlightable {
public:
	virtual ~Highlightable ();
	virtual void	DrawIfNoHoverAtTheBeginning (NewDisplay::NativeContext& context, const DG::Rect& itemRect, const FloatingMenuAppearance& menuAppearance, const DG::Rect& workRect) const;
	virtual void	DrawIfNoHoverAtTheEnd (NewDisplay::NativeContext& context, const DG::Rect& itemRect, const FloatingMenuAppearance& menuAppearance, const DG::Rect& workRect) const;
	virtual void	DrawHoverAtTheBeginning (NewDisplay::NativeContext& context, const ItemHighlightInfo& itemHighlightInfo, const FloatingMenuAppearance& menuAppearance, const DG::Rect& workRect) const;
	virtual void	DrawHoverAtTheEnd (NewDisplay::NativeContext& context, const ItemHighlightInfo& itemHighlightInfo, const FloatingMenuAppearance& menuAppearance, const DG::Rect& workRect) const;
	virtual void	DrawSelection (NewDisplay::NativeContext& context, const ItemHighlightInfo& itemHighlightInfo, const FloatingMenuAppearance& menuAppearance, const DG::Rect& workRect) const;
	virtual void	DrawMark (NewDisplay::NativeContext& context, const ItemHighlightInfo& itemHighlightInfo, const FloatingMenuAppearance& menuAppearance, const DG::Rect& workRect) const;

private:
	void	DrawHighlight (NewDisplay::NativeContext& context, const ItemHighlightInfo& itemHighlightInfo, const FloatingMenuAppearance& menuAppearance, const DG::Rect& workRect) const;
	void	DrawItemRectWithColor (NewDisplay::NativeContext& context, const ItemHighlightInfo& itemHighlightInfo, const FloatingMenuAppearance& menuAppearance, const DG::Rect& workRect, const Gfx::Color& color) const;
	void	DrawRectWithColor (NewDisplay::NativeContext& context, const FloatingMenuAppearance& menuAppearance, const DG::Rect& rect, const Gfx::Color& color) const;
};

}

#endif //GS_FLOATINGWINDOW_ITEMHIGHLIGHTDISPLAYER_HPP
