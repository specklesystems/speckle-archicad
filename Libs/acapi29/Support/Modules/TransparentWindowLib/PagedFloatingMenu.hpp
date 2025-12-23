// *****************************************************************************
// File:			PagedFloatingMenu.hpp
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

#ifndef PAGEDFLOATINGMENU_HPP
#define PAGEDFLOATINGMENU_HPP

#pragma once

#define ID_PAGEDFLOATINGMENUSTRLIST	2002

enum {
	TitleTextID		=	1,
	PreviousTextID	=	2,
	NextTextID		=	3
};

// --- Includes ----------------------------------------------------------------

#include "IDoubleProperty.hpp"

#include "Array.hpp"
#include "Color.hpp"

#include "DGUtility.hpp"

#include "DisposableObject.hpp"

#include "TransparentWindow.hpp"
#include "FloatingMenuItem.hpp"
#include "FloatingMenu.hpp"

#pragma warning (disable: 4512)


// --- Predeclarations ---------------------------------------------------------


// --- Class declarations ------------------------------------------------------

namespace FloatingWindow {

class TRANSPARENTWINDOWLIB_DLL_EXPORT PagedFloatingMenu
{
private:
	class PreviousPageMenuItem : public FloatingMenuItem
	{
	private:
		PagedFloatingMenu* pagedFloatingMenu;
	protected:
		virtual void OnClick (const DG::Rect& /*menuItemRect*/, const DG::Point& /*position*/)  override { if (pagedFloatingMenu != nullptr) pagedFloatingMenu->PreviousPage (); }
	public:
		PreviousPageMenuItem (PagedFloatingMenu* inPagedFloatingMenu) : pagedFloatingMenu (inPagedFloatingMenu) {}
		virtual ~PreviousPageMenuItem ();
	};

	class NextPageMenuItem : public FloatingMenuItem
	{
	private:
		PagedFloatingMenu* pagedFloatingMenu;
	protected:
		virtual void OnClick (const DG::Rect& /*menuItemRect*/, const DG::Point& /*position*/)  override { if (pagedFloatingMenu != nullptr) pagedFloatingMenu->NextPage (); }
	public:
		NextPageMenuItem (PagedFloatingMenu* inPagedFloatingMenu) : pagedFloatingMenu (inPagedFloatingMenu) {}
		virtual ~NextPageMenuItem ();
	};

private:
	FloatingMenu			floatingMenu;
	GS::Array<FloatingMenu::MenuItemRow>	pagedFloatingMenuRows;
	FloatingMenu::MenuItemRow				titleMenuItemRow;
	FloatingMenu::MenuItemRow				previousPageMenuItemRow;
	FloatingMenu::MenuItemRow				nextPageMenuItemRow;
	FloatingMenuItemPtr		previousPageMenuItem;
	FloatingMenuItemPtr		nextPageMenuItem;
	UInt16					pageSize;
	UInt16					firstVisibleItemIndex;

private:
	FloatingMenuItemPtr		CreatePreviousPageMenuItem ();
	FloatingMenuItemPtr		CreateNextPageMenuItem ();
	void					FillFloatingMenu ();

	// Disable
	PagedFloatingMenu (const PagedFloatingMenu&);
	PagedFloatingMenu& operator= (const PagedFloatingMenu&);

public:
	PagedFloatingMenu ();
	virtual ~PagedFloatingMenu ();

	void				AddPagedRow (FloatingMenu::MenuItemRow& menuItemRow);
	void				InsertPagedRow (FloatingMenu::MenuItemRow& menuItemRow, UInt16 menuItemRowIndex);
	void				DeletePagedRow (UInt16 menuItemRowIndex);
	void				DeleteAllPagedRows ();
	void				PreviousPage ();
	void				NextPage ();
	void				SetPageSize (UInt16 inPageSize);

	void				SetTitleRow (FloatingMenu::MenuItemRow& menuItemRow);

	void				SetPreviousPageText (const GS::UniString& text);
	void				SetPreviousPageIcon (const DG::Icon& icon);
	void				SetPreviousPageOffset (const short offset);
	void				SetPreviousPageEndOffset (const short offset);
	void				SetPreviousPageStyle (const DG::Font::Style style);

	void				SetNextPageText (const GS::UniString& text);
	void				SetNextPageIcon (const DG::Icon& icon);
	void				SetNextPageOffset (const short offset);
	void				SetNextPageEndOffset (const short offset);
	void				SetNextPageStyle (const DG::Font::Style style);

	void				MoveAnimated (const DG::NativePoint& moveTo, short milliSec);
	//DG::NativeRect		GetRect (void) const { return floatingMenu.GetRect (); }
	void				SetPosition (const DG::NativePoint& point, bool animated = false, short milliSec = -1);
	DG::NativePoint		GetPosition (void) const;
	short 				GetWidth (void) const;
	short 				GetHeight (void) const;

	void				Fade (const float endAlpha, short milliSec);
	void				Draw ();
	void				Hide ();
	void				Show ();
	bool				IsVisible () const;

	void				SetForegroundColor (const Gfx::Color&);
	void				SetBackgroundColor (const Gfx::Color&);
	void				SetSmallFont (bool);

	Gfx::Color			GetForegroundColor () const;
	Gfx::Color			GetBackgroundColor () const;
	bool				IsSmallFont () const ;
};

}

#endif
