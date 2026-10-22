#ifndef GS_UD_IFILTERABLEITEM_HPP
#define GS_UD_IFILTERABLEITEM_HPP
#pragma once

#include "UDIFilterable.hpp"
#include "DGItemProperty.hpp"

namespace UD {

class UD_DLL_EXPORT IFilterableItem : public IFilterable {
public:
	virtual ~IFilterableItem ();

	virtual DG::Panel* GetPanel (void) const = 0;

	virtual void	Show (void) = 0;
	virtual void	Hide (void) = 0;
	virtual void	SetVisibility (bool show) = 0;
	virtual bool	IsVisible (void) const = 0;

	virtual void	Enable (void) = 0;
	virtual void	Disable (void) = 0;
	virtual void	SetStatus (bool enable) = 0;
	virtual bool	IsEnabled (void) const = 0;

	virtual void	Move (short hDisp, short vDisp) = 0;
	virtual void	Resize (short hGrow, short vGrow) = 0;
	virtual void	MoveAndResize (short hDisp, short vDisp, short hGrow, short vGrow) = 0;

	virtual void	SetPosition (const DG::Point& pt) = 0;
	virtual void	SetPosition (short hPos, short vPos) = 0;
	virtual void	SetRect (const DG::Rect& rect) = 0;
	virtual void	SetSize (short width, short height) = 0;
	virtual void	SetWidth (short width) = 0;
	virtual void	SetHeight (short height) = 0;

	virtual DG::Point	GetPosition (void) const = 0;
	virtual DG::Rect	GetRect (void) const = 0;
	virtual short	GetWidth (void) const = 0;
	virtual short	GetHeight (void) const = 0;

	virtual DG::NativeRect	GetNativeRectInScreenSpace (void) const = 0;

	virtual void	Invalidate (void) const = 0;
	virtual void	Redraw (void) const = 0;

	virtual DG::EventNotifier<DG::Item, const DG::VisibilityChangeEventArg>& AccessOnVisibilityChangedEventNotifier () = 0;

	virtual void		 SetFontSize (DG::Font::Size size) = 0;
	virtual DG::Font::Size	 GetFontSize (void) const = 0;

	virtual void		 SetFontStyle (DG::Font::Style style) = 0;
	virtual DG::Font::Style	 GetFontStyle (void) const = 0;

	virtual void	SetFocus (void) = 0;
	virtual bool	IsFocused (void) const = 0;

};

}

#endif  //GS_UD_IFILTERABLEITEM_HPP
