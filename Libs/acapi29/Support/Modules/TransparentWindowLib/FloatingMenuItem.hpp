// *****************************************************************************
// File:			FloatingMenuItem.hpp
//
// Description:
//
// Project:			ARCHICAD
//
// Namespace:
//
// Contact person:	NZ, RA, BL
//
// SG compatible
// *****************************************************************************

#ifndef FLOATINGMENUITEM_HPP
#define FLOATINGMENUITEM_HPP

#pragma once

// --- Includes ----------------------------------------------------------------

#include "SharedObject.hpp"
#include "Any.hpp"
#include "TransparentWindowLibDefinitions.hpp"
#include "UniString.hpp"
#include "DGItemProperty.hpp"

#include "ItemHighlightDisplayer.hpp"

// --- Predeclarations ---------------------------------------------------------

namespace FloatingWindow {

class FloatingMenu;
class FloatingMenuItem;

typedef GS::SharedPtr<FloatingMenuItem>		FloatingMenuItemPtr;

// --- Class declarations ------------------------------------------------------

class TRANSPARENTWINDOWLIB_DLL_EXPORT FloatingMenuItem : public GS::SharedObject, public Highlightable {
friend class FloatingMenu;
friend class CustomFloatingMenu;

public:
	enum VisibilityType {
		Visible				= 1,
		Invisible			= 2,
		VisibleOnHighlight	= 3
	};

protected:
	GS::UniString			text;
	GS::Any					image;
	DG::Font::Style			textStyle;
	short					drawOffset;
	short					midOffset;
	short					endOffset;
	short					yOffset;
	bool					selectable;
	bool					selected;
	VisibilityType			visibilityType;
	bool					colorIcon;
	GS::Ref<Gfx::Color>		textColorRef;
	bool					isMarked;
	bool					isTooltipEnabledOnNonSelectable;

protected:
	virtual void			OnClick (const DG::Rect& menuItemRect, const DG::Point& position);
	virtual void			OnMouseUp (const DG::Rect& menuItemRect, const DG::Point& clickPosition, const DG::Point& releasePosition, bool& processed);
	virtual void			OnRClick (const DG::Rect& menuItemRect, const DG::Point& position);
	virtual void			OnRMouseUp (const DG::Rect& menuItemRect, const DG::Point& clickPosition, const DG::Point& releasePosition, bool& processed);
	virtual void			OnEnter ();
	virtual void			OnLeave ();
	virtual void			OnMouseMove (const ItemHighlightInfo& itemHighlightInfo);
	virtual void			OnSelectionChanged ();

public:
	FloatingMenuItem ();
	virtual ~FloatingMenuItem ();

	void					SetText (const GS::UniString& text);
	void					SetIcon (const DG::Icon& icon);
	void					SetImage (const NewDisplay::NativeImage& image);
	void					SetTextStyle (const DG::Font::Style style);
	void					SetDrawOffset (const short offset);
	void					SetMidOffset (const short offset);
	void					SetEndOffset (const short offset);
	void					SetYOffset (const short offset);
	void					SetSelectable (bool inSelectable);
	void					SetSelected (bool inSelected);
	void					SetVisibilityType (VisibilityType inVisibilityType);
	void					SetColorIcon (bool color);
	void					SetTextColor (GS::Ref<Gfx::Color> textColor);
	void					SetMarked (bool marked);
	void					SetTooltipStatusOnNonSelectable (bool enable);

	const GS::UniString&	GetText () const;
	virtual bool			HasImage () const;
	virtual NewDisplay::NativeImage GetImage (double resolutionFactor) const;

	DG::Font::Style			GetTextStyle () const;
	short					GetDrawOffset () const;
	short					GetMidOffset () const;
	short					GetEndOffset () const;
	short					GetYOffset () const;
	bool					IsSelectable () const;
	bool					IsSelected () const;
	VisibilityType			GetVisibilityType () const;
	virtual bool			IsColorImage () const;
	bool					HasTextColor () const;
	const GS::Ref<Gfx::Color> GetTextColor () const;
	bool					IsMarked () const;
	bool					IsTooltipEnabledOnNonSelectable () const;

	virtual GS::UniString	GetToolTipString (const ItemHighlightInfo& /*itemHighlightInfo*/) const { return GS::UniString (); }

	virtual UInt16			GetTextHeight (bool smallFont) const;
	virtual UInt16			GetTextWidth (bool smallFont) const;
	virtual UInt16			GetImageHeight (double resolutionFactor) const;
	virtual UInt16			GetImageWidth (double resolutionFactor) const;

	UInt16			GetFullWidth (bool smallFont, UInt32 iconWidth) const;
};

}

#endif
