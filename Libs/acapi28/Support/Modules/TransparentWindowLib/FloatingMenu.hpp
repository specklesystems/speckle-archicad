// *********************************************************************************************************************
// Description:		FloatingMenu
//
// Module:			DG
// Namespace:
// Contact person:	NZ, BaP
//
// SG compatible
// *********************************************************************************************************************

#ifndef _FLOATINGMENU_HPP_
#define _FLOATINGMENU_HPP_

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "IDoubleProperty.hpp"

#include "Array.hpp"
#include "Optional.hpp"

#include "Color.hpp"

#include "DGUtility.hpp"

#include "DisposableObject.hpp"

#include "TransparentWindow.hpp"
#include "FloatingMenuItem.hpp"
#include "ItemHighlightInfo.hpp"

#include "FloatingMenuDefinitions.hpp"
#include "FloatingMenuAppearance.hpp"

// --- Predeclarations -------------------------------------------------------------------------------------------------


// --- Class declarations ----------------------------------------------------------------------------------------------

namespace FloatingWindow {

class TRANSPARENTWINDOWLIB_DLL_EXPORT FloatingMenu : public TransparentWindow
{
public:
	class TRANSPARENTWINDOWLIB_DLL_EXPORT MenuRow : public GS::Object {
	private:
		bool							highlightable;
	public:
		MenuRow ();
		virtual ~MenuRow ();

		void SetHighlightable (bool inHighlightable);
		bool IsHighlightable (void) const;

		virtual UInt16 GetNecessaryHeight (bool smallFont, double resolutionFactor) const = 0;

		virtual USize GetItemCount () const = 0;
	};

	class TRANSPARENTWINDOWLIB_DLL_EXPORT MenuItemRow : public MenuRow {
	private:
		GS::Array<FloatingMenuItemPtr>	rowItems;
	public:
		MenuItemRow ();
		MenuItemRow (const GS::Array<FloatingMenuItemPtr>& inRowItems);
		MenuItemRow (FloatingMenuItemPtr floatingMenuItem);

		virtual MenuItemRow* Clone (void) const override;

		UInt16 GetNecessaryHeight (bool smallFont, double resolutionFactor) const override;

		virtual USize GetItemCount () const override;

		const GS::Array <FloatingMenuItemPtr>& GetRowItems () const;
	};

	class TRANSPARENTWINDOWLIB_DLL_EXPORT HorizontalSeparator : public MenuRow {
	public:
		virtual HorizontalSeparator* Clone (void) const override;

		UInt16 GetNecessaryHeight (bool smallFont, double resolutionFactor) const override;

		virtual USize GetItemCount () const override;
	};

	class TRANSPARENTWINDOWLIB_DLL_EXPORT MenuItemWidths {
	public:
		UInt16 fullWidth;
		UInt16 drawOffset;
		UInt16 midOffset;
		UInt16 endOffset;
		UInt16 iconWidth;
		UInt16 textWidth;
	public:
		MenuItemWidths () : fullWidth (0), drawOffset (0), midOffset (0), endOffset (0), iconWidth (0), textWidth (0) {}
	};

	typedef GS::Array<GS::Ref<MenuRow>> MenuItemRowArray;

	struct LayoutData {
		GS::Array<UInt16> rowHeights;
		GS::Array<GS::Array<MenuItemWidths>> columnWidths;
	};

	class TRANSPARENTWINDOWLIB_DLL_EXPORT LayoutStrategy {
	public:
		virtual			~LayoutStrategy ();
	public:
		virtual void	InitLayoutData (const MenuItemRowArray& rows, LayoutData* data) const = 0;
		virtual void	Calculate (const MenuItemRowArray& rows, const bool smallFont, LayoutData* data) const = 0;

		virtual UInt16	GetRowGap (void) const;
		virtual UInt16	GetHFrameGrap (void) const;
		virtual UInt16	GetVFrameGrap (void) const;
		virtual UInt16	GetRowHeightAdjustment (void) const;

	public:
		typedef GS::Ref<LayoutStrategy> Ref;
	};

	class TRANSPARENTWINDOWLIB_DLL_EXPORT DefaultLayout : public LayoutStrategy
	{
	public:
		virtual void	Calculate (const MenuItemRowArray& rows, const bool smallFont, LayoutData* data) const override;
		virtual void	InitLayoutData (const MenuItemRowArray& rows, LayoutData* data) const override;
	private:
		void			CalculateRows (const MenuItemRowArray& rows, const bool smallFont, LayoutData* data) const;
		void			CalculateColumns (const MenuItemRowArray& rows, const bool smallFont, LayoutData* data) const;
	};

	class TRANSPARENTWINDOWLIB_DLL_EXPORT CustomLayout : public LayoutStrategy
	{
	public:
		virtual void	Calculate (const MenuItemRowArray& rows, const bool smallFont, LayoutData* data) const override;
		virtual void	InitLayoutData (const MenuItemRowArray& rows, LayoutData* data) const override;
	private:
		void			CalculateRows (const MenuItemRowArray& rows, const bool smallFont, LayoutData* data) const;
		void			CalculateColumns (const MenuItemRowArray& rows, const bool smallFont, LayoutData* data)const;
	};

private:
	MenuItemRowArray			floatingMenuRows;
	LayoutStrategy::Ref			layoutStrategy;
	LayoutData					layoutData;
	GS::UniString				toolTipString;
	short						calculatedNecessaryWidth;
	short						calculatedNecessaryHeight;
	short						minimalWidth;
	short						fixedWidth;
	short						fixedHeight;
	DG::Rect					wholeMenuRect;
	GS::Optional<ItemHighlightInfo> hoverInfo;
	HighlightRefreshBehaviour	highlightRefreshBehaviour;
	FloatingMenuAppearance		floatingMenuAppearance;
	Int32						mouseEventsDisableCounter;
	bool						shouldCallDrawIfBecomesVisible;

public:
	explicit FloatingMenu (const DG::NativePoint& position = DG::NativePoint (), LayoutStrategy::Ref layoutStrategy = new DefaultLayout ());
	virtual ~FloatingMenu ();

	FloatingMenu (const FloatingMenu&) = delete;
	FloatingMenu& operator= (const FloatingMenu&) = delete;

	UInt16				GetRowHeight (const UInt16 row) const;
	UInt16				GetColumnWidth (const UInt16 row, const UInt16 column) const;
	GS::Pair<short, short> CalculateWindowSize (bool useMinimalWidth = true);

	void				AddRow (GS::Ref<MenuRow> menuItemRow);
	void				InsertRow (GS::Ref<MenuRow> menuItemRow, UInt16 menuItemRowIndex);
	void				DeleteRow (UInt16 menuItemRowIndex);
	void				DeleteAllRows (void);
	UInt16				GetRowNumber (void) const;
	GS::Ref<MenuRow>	GetRow (UInt16 menuItemRowIndex) const;
	DG::Rect			GetMenuItemRect (UInt16 rowIndex, UInt16 columnIndex) const;
	DG::NativeRect		GetNativeRect (void) const;	
	void				SetPosition (const DG::NativePoint& point, bool animated = false, short milliSec = -1, bool placeWindowBehindPalettes = true);
	short				GetWidth (void) const override;
	short				GetHeight (void) const override;
	void				Draw (void);
	void				Hide (void) override;
	virtual void		Show (bool animate = false);
	bool				IsVisible (void) const override;
	bool				HitTest (const DG::NativePoint& point, short frameSize = 0) const;
	void				FixSelectedRowIndex (void);
	short				GetFrameThickness (void) const;
	void				SetMinimalWidth (short minimalWidth);
	void				SetFixedSize (short fixedWidth, short fixedHeight);
	void				SetHighlightRefreshBehaviour (HighlightRefreshBehaviour highlightRefreshBehaviour);
	static void			DrawRoundedRect (NewDisplay::NativeContext& context,
										 float posX, float posY, float right, float bottom,
										 float cornerRadius, short offsetX,
										 unsigned short arrowSize, ArrowStyle arrowStyle, float arrowOffset);

	void				SetForegroundColor (const Gfx::Color& foregroundColor);
	const Gfx::Color&	GetForegroundColor () const;

	void				SetBackgroundColor (const Gfx::Color& backgroundColor);
	const				Gfx::Color& GetBackgroundColor () const;

	void				SetFrameColor (const Gfx::Color& frameColor);
	const				Gfx::Color& GetFrameColor () const;

	void				SetAlpha (unsigned char alpha);
	unsigned char		GetAlpha () const;

	void				SetContourVisibility (bool	contourIsVisible);
	//bool				IsContourVisible () const;

	void				SetOffsetX (short offsetX);
	short				GetOffsetX () const;

	void				SetBoundingRectStyle (BoundingRectStyle boundingRectStyle);
	BoundingRectStyle	GetBoundingRectStyle () const;

	void				SetCornerRadius (float cornerRadius);
	float				GetCornerRadius () const;

	void				SetArrowStyle (ArrowStyle arrowStyle);
	ArrowStyle			GetArrowStyle () const;

	//void				SetArrowSize (unsigned short arrowSize);
	unsigned short		GetArrowSize () const;

	void				SetArrowOffset (float arrowOffset);
	float				GetArrowOffset () const;

	void				SetSmallFont (bool);
	bool				IsSmallFont (void) const;

	virtual void		OnClick ();
	virtual void		OnMouseUp (const DG::Point& clickPosition, const DG::Point& releasePosition);
	virtual void		OnRMouseUp (const DG::Point& clickPosition, const DG::Point& releasePosition);
	virtual void		OnLeave ();

	void				EnableMouseEvents ();
	void				DisableMouseEvents ();
	bool				MouseEventsEnabled () const;

	void				SetCustomLayout ();

protected:
	GS::UniString		ToolTipTextRequested (void) const override;
	virtual void		DrawBackground (NewDisplay::NativeContext& context, float posX, float posY, float right, float bottom);
	virtual void		OnMouseMove (const DG::Point& point);

	virtual void		DrawBackground (NewDisplay::NativeContext& context, const DG::Rect& workRect);

	LayoutStrategy::Ref	GetLayoutStrategy ();
	const LayoutStrategy::Ref& GetLayoutStrategy () const;

private:
	void				MoveAnimated (const DG::NativePoint& moveTo, short milliSec);
	void				DrawBackgroundContour (NewDisplay::NativeContext& context, const DG::Rect& workRect);
	void				DrawAllMark (NewDisplay::NativeContext& context, const DG::Rect& workRect);
	void				DrawVerticalSeparators (NewDisplay::NativeContext&	context, UInt16 currentRowIndex);
	FloatingMenuItemPtr	GetMenuItem (UInt16 rowIndex, UInt16 columnIndex);
	UInt16				GetTotalRowHeight (void) const;
	UInt16				GetTotalRowHeight (const UInt16 rowIndex) const;
	UInt16				GetMaxTotalColumnWidth (void) const;
	UInt16				GetTotalColumnWidth (const UInt16 rowIndex, const UInt16 columnIndex) const;
	DG::NativePoint		MapPointToScreen (const DG::Point& pointToMap) const;
	bool				MouseMove (const short xPos, const short yPos);
	virtual void		MouseMove (const DG::Point& point) override;
	virtual void		MouseClick (const DG::Point& point) override;
	virtual void		MouseUp (GS::Optional<DG::Point> clickPt, const DG::Point& releasePt) override;

	virtual void		MouseRClick (const DG::Point& point) override;
	virtual void		MouseRUp (GS::Optional<DG::Point> clickPt, const DG::Point& releasePt) override;
};


}

#endif	// _FLOATINGMENU_HPP_
