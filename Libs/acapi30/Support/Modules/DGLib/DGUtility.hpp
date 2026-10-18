// *********************************************************************************************************************
// File:			DGUtility.hpp
//
// Description:		Utility classes and functions
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	BM
//
// *********************************************************************************************************************

#ifndef DGUTILITY_HPP
#define DGUTILITY_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "Definitions.hpp"

#if defined (WINDOWS)
#include "Win32UxInterface.hpp"
#include "DGWImageCache.hpp"
#endif

#include "Array.hpp"
#include "DG.h"
#include "DGImage.hpp"
#include "DGPoint.hpp"
#include "DGRect.hpp"
#include "NativeImage.hpp"
#include "Range.hpp"


// --- Predeclarations -------------------------------------------------------------------------------------------------

namespace Gfx {
	class Color;
}

namespace IO {
	class Location;
}

namespace NewDisplay {
	class NativeContext;
}

namespace DG {
	class CommandDescriptor;
	class Dialog;
	class DragDropData;
	class Item;
	class ListBox;
	class ListBoxItemUpdateEvent;
	class ListBoxTabItemUpdateEvent;
	class ListView;
	class Panel;
	class Shortcut;
	class ShortcutScheme;
	class TreeView;
}

namespace DG {

// === RichEdit ========================================================================================================

// --- Definitions -----------------------------------------------------------------------------------------------------

namespace EOL {

	enum Type {
		Default	= DG_EOL_DEFAULT,
		CR		= DG_EOL_CR,
		CRLF	= DG_EOL_CRLF
	};

}	// namespace EOL


namespace Search {

	enum Dir {
		Down		= DG_RFT_DOWN,
		Up			= DG_RFT_UP
	};

	enum Case {
		InSensitive	= 0,
		Sensitive	= DG_RFT_MATCHCASE
	};

	enum Word {
		NoMatchWord	= 0,
		MatchWord	= DG_RFT_WHOLEWORD
	};

}	// namespace Search

namespace UC {

	enum UC257CellSkinType {
		FillSkin,
		EmptySkin,
		SurfaceSkin,
		MissingSkin,		// displaying a ? (on Building Materials)
		DefaultSkin			// displaying a -
	};

}	// namespace UC


typedef GS::Range<Int32> CharRange;


// --- Definitions -----------------------------------------------------------------------------------------------------

enum EventHandlerResultType {
	NotProcessedEvent		= 0,
	ProcessedEvent			= 1,
	ForbidDGToHandleEvent	= 2
};

namespace Unit {

	enum Type {
		Unit_MM				= DG_UNIT_MM,
		Unit_CM				= DG_UNIT_CM,
		Unit_DM				= DG_UNIT_DM,
		Unit_M				= DG_UNIT_M,
		Unit_KM				= DG_UNIT_KM,

		Unit_DecInch		= DG_UNIT_DECINCH,
		Unit_FootInch		= DG_UNIT_FOOT_INCH,
		Unit_Inch			= DG_UNIT_INCH,
		Unit_FootDecInch	= DG_UNIT_FOOT_DECINCH,
		Unit_DecFoot		= DG_UNIT_DECFOOT,

		Unit_DecDegree		= DG_UNIT_DECDEGREE,
		Unit_DegMinSec		= DG_UNIT_DEGMINSEC,
		Unit_Grad			= DG_UNIT_GRAD,
		Unit_Radian			= DG_UNIT_RADIAN,
		Unit_Surveyors		= DG_UNIT_SURVEYORS

	};

}	// namespace Unit


// === Key handling ====================================================================================================

#if defined (macintosh)

enum VirtualCodes {
	CommandKey = 55,	// Command
	PeriodKey1 = 47,	// Period key
	PeriodKey2 = 65,	// Period key on Numpad
	SpaceKey   = 49,	// space
	InvalidVkCode = 255
};

#endif

namespace Key {

	enum Modifier {
		NoModifier	= 0,
		Command		= DG_MOD_COMMAND,
		Option		= DG_MOD_OPTION,
		Shift		= DG_MOD_SHIFT,
		Ctrl		= DG_MOD_CTRL
	};

	enum Special {
		Empty		= DG_KEY_EMPTY,
		Back		= DG_KEY_BACK,
		Tab			= DG_KEY_TAB,
		Enter		= DG_KEY_ENTER,
		Return		= DG_KEY_RETURN,
		Escape		= DG_KEY_ESCAPE,

		Left		= DG_KEY_LEFT,
		Right		= DG_KEY_RIGHT,
		Up			= DG_KEY_UP,
		Down		= DG_KEY_DOWN,

		Insert		= DG_KEY_INSERT,
		Delete		= DG_KEY_DELETE,
		Home		= DG_KEY_HOME,
		End			= DG_KEY_END,
		PageUp		= DG_KEY_PAGEUP,
		PageDown	= DG_KEY_PAGEDOWN,

		F1			= DG_KEY_F1,
		F2			= DG_KEY_F2,
		F3			= DG_KEY_F3,
		F4			= DG_KEY_F4,
		F5			= DG_KEY_F5,
		F6			= DG_KEY_F6,
		F7			= DG_KEY_F7,
		F8			= DG_KEY_F8,
		F9			= DG_KEY_F9,
		F10			= DG_KEY_F10,
		F11			= DG_KEY_F11,
		F12			= DG_KEY_F12,
		F13			= DG_KEY_F13,
		F14			= DG_KEY_F14,
		F15			= DG_KEY_F15,

		Help		= DG_KEY_HELP
	};


	// --- Code class declaration --------------------------------------------------------------------------------------

	class Code
	{
		Special		code;
		GS::UniChar	uniChar;

	public:
		inline				Code ();
		inline				Code (Special code);
		inline				Code (GS::UniChar code);

		inline bool			IsSpecial (void) const;
		inline GS::UniChar	GetUniChar (void) const;
		inline Special		GetSpecialKey (void) const;

		inline bool			operator== (const Code& op) const;
		inline bool			operator!= (const Code& op) const;

		inline GSErrCode	ReadOld (GS::IChannel& ic);
		inline GSErrCode	Read (GS::IChannel& ic);
		inline GSErrCode	Write (GS::OChannel& oc) const;
	};


	// --- Code class inline implementation ----------------------------------------------------------------------------

	inline Code::Code ()
	{
		this->code = Empty;
	}


	inline Code::Code (Special code)
	{
		this->code = code;
	}


	inline Code::Code (GS::UniChar uniChar)
	{
		this->code = Empty;
		this->uniChar = uniChar;
	}


	inline bool		Code::IsSpecial (void) const
	{
		return (code != Empty);
	}


	inline GS::UniChar		Code::GetUniChar (void) const
	{
		return uniChar;
	}


	inline Special	Code::GetSpecialKey (void) const
	{
		return code;
	}


	inline bool		Code::operator== (const Code& op) const
	{
		return (op.code == code && op.uniChar == uniChar);
	}


	inline bool		Code::operator!= (const Code& op) const
	{
		return (op.code != code || op.uniChar != uniChar);
	}


	inline GSErrCode	Code::ReadOld (GS::IChannel& ic)
	{
		short tmpCode;
		GSErrCode errCode = ic.Read (tmpCode);
		if (tmpCode < 0) {
			code = static_cast<Special> (tmpCode);
		} else {
			char chrStr[2];
			chrStr[0] = static_cast<char> (tmpCode);
			chrStr[1] = 0;
			GS::UniString tmp (chrStr, CC_System);
			if (tmp.GetLength () > 0)
				uniChar = tmp.GetChar (0);
		}
		return errCode;
	}


	inline GSErrCode	Code::Read (GS::IChannel& ic)
	{
		short tmpCode;
		GSErrCode errCode = ic.Read (tmpCode);
		if (errCode != NoError)
			return errCode;
		code = static_cast<Special> (tmpCode);
		GS::UniChar::Layout tmpLayout;
		errCode = ic.Read (tmpLayout);
		if (errCode == NoError)
			uniChar = tmpLayout;
		return errCode;
	}


	inline GSErrCode	Code::Write (GS::OChannel& oc) const
	{
		GSErrCode errCode = oc.Write (static_cast<short> (code));
		if (errCode != NoError)
			return errCode;
		return oc.Write (GS::UniChar::Layout (uniChar));
	}
}	// namespace Key

} //namespace DG


namespace DG {

// --- MousePosData class ----------------------------------------------------------------------------------------------

class DG_DLL_EXPORT MousePosData
{
private:
	DGMousePosData	data;
	bool			valid;

public:
	MousePosData ();

	bool		Retrieve (void);
	bool		Retrieve (const Panel& panel);
	bool		Retrieve (const Item& item);

	void		RetrieveFailSafe (void);
	void		RetrieveFailSafe (const Panel& panel);
	void		RetrieveFailSafe (const Item& item);

	Panel*		GetPanel (void) const;
	Item*		GetItem (void) const;

	Rect		GetRect (void) const;
	Point		GetMouseOffsetInLogicalUnits (void) const;
	NativePoint	GetMouseOffsetInNativeUnits (void) const;

	bool		IsCommandPressed (void) const;
	bool		IsOptionPressed (void) const;
	bool		IsShiftPressed (void) const;

	bool		IsLeftButtonPressed (void) const;
	bool		IsRightButtonPressed (void) const;
	bool		IsWheelButtonPressed (void) const;
};


// === Drag & Drop handling ============================================================================================

// --- Definitions -----------------------------------------------------------------------------------------------------

namespace DragDrop
{
	enum class Effect : UInt16 {
		Reject		= DG_DRAG_REJECT,
		Accept		= DG_DRAG_ACCEPT,
		Copy		= DG_DRAG_ACCEPT_COPY,
		Move		= DG_DRAG_ACCEPT_MOVE,
		CopyAndMove	= DG_DRAG_ACCEPT_COPY | DG_DRAG_ACCEPT_MOVE,
		Link		= DG_DRAG_ACCEPT_LINK,
		Delete		= DG_DRAG_DELETE
	};

	Effect operator| (Effect lhv, Effect rhv);
	Effect operator& (Effect lhv, Effect rhv);
	Effect operator|= (Effect& lhv, Effect rhv);
	Effect operator&= (Effect& lhv, Effect rhv);

	enum Feedback {
		AcceptSelAndIns	= 0,
		RejectSelection	= DG_DRAG_REJECT_SEL,
		RejectInsertion	= DG_DRAG_REJECT_INS,
		RejectSelAndIns	= DG_DRAG_REJECT_SEL | DG_DRAG_REJECT_INS
	};

	enum RelativePos {
		InsertOn	= DG_DRAG_INSERT_ON,
		InsertBelow	= DG_DRAG_INSERT_BELOW,
		InsertAbove = DG_DRAG_INSERT_ABOVE
	};

	enum Scope {
		Item		= DG_DRAG_SCOPE_ITEM,
		Dialog		= DG_DRAG_SCOPE_DIALOG,
		Module		= DG_DRAG_SCOPE_MODULE,
		Application	= DG_DRAG_SCOPE_APP,
		System		= DG_DRAG_SCOPE_SYSTEM
	};
}


// --- ItemDragDropData class ------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ItemDragDropData
{
protected:
	mutable DragDropData* dragData;			//Mutable, because this object is updateable
	mutable bool		  isDataUpToDate;
	short				  mainDialId;

	explicit ItemDragDropData (Panel* source);

public:
	~ItemDragDropData ();

	bool	  HasDataFormat (DGDragFormat format) const;
	ULong	  GetDataSize (DGDragFormat format) const;
	bool	  GetData (DGDragFormat format, void* data, ULong size) const;
	bool	  GetFileData (DGDragFormat format, const GS::uchar_t* folderPath, void* data, ULong size) const;

	bool	  GetText (Int8* text, ULong size) const;

	ULong	  GetLocationCount (void) const;
	bool	  GetLocation (ULong index, IO::Location& location) const;	//must change to IO::Location*

	Item*	  GetSourceItem (void) const;
	ListBox*  GetListBoxSource (void) const;
	ListView* GetListViewSource (void) const;
	TreeView* GetTreeViewSource (bool externalEnabled = false) const;

	ULong	  GetItemCount (void) const;
	Int32	  GetTreeViewItem (ULong index) const;
	short	  GetListBoxItem (ULong index) const;
	short	  GetListViewItem (ULong index) const;
};


// --- DragSourceEventProperty class -----------------------------------------------------------------------------------

class DG_DLL_EXPORT DragSourceEventProperty
{
private:
	DragDropData*			dragData;
	DG::DragDropEventArg*	ddMsgData;
	GSPtr					fileData;

public:
	DragSourceEventProperty ();
	virtual ~DragSourceEventProperty ();

	void	Init (DG::DragDropEventArg* msgData);

	bool	SetData (DGDragFormat format, void* data, ULong size, DragDrop::Scope scope);
	bool	SetDelayedData (DGDragFormat format, DragDrop::Scope scope);
	void	SetLocationData (IO::Location *locArray, ULong nrOfLocations);
	bool	ModifyBaseFormat (DGDragFormat format, DragDrop::Scope scope);

	Point	GetSourcePosition (void) const;
	DGDragFormat		GetRequestedDragFormat (void) const;
	const GS::uchar_t*	GetFolderPath () const;
	void	SetSourceFeedback (const void* feedback, const DG::Rect* feedbackRect);
};


// --- DropTargetEventProperty class -----------------------------------------------------------------------------------

class DG_DLL_EXPORT DropTargetEventProperty: public ItemDragDropData
{
private:
	Point	targetPos;

protected:
	DropTargetEventProperty (const DG::EventArg& msgData, Panel* source);

public:
	virtual ~DropTargetEventProperty ();

	Point	GetTargetPosition (void) const;
};


// --- CompoundItemObserver class --------------------------------------------------------------------------------------

class DG_DLL_EXPORT CompoundItemObserver
{
protected:
	CompoundItemObserver ();

public:
	virtual	~CompoundItemObserver ();

	short	AttachToAllItems (const Panel& panel);
	short	DetachFromAllItems (const Panel& panel);
};


// --- SetAndRestoreEditUpdateDelay class ------------------------------------------------------------------------------

class DG_DLL_EXPORT SetAndRestoreEditUpdateDelay {
public:
	SetAndRestoreEditUpdateDelay (ULong newEditUpdateDelay = 0);
	~SetAndRestoreEditUpdateDelay ();

private:
	SetAndRestoreEditUpdateDelay (const SetAndRestoreEditUpdateDelay&);				// disabled
	SetAndRestoreEditUpdateDelay& operator= (const SetAndRestoreEditUpdateDelay&);	// disabled

	const ULong		mSavedEditUpdateDelay;
};


// --- Utils class (General utility functions) -------------------------------------------------------------------------

class DG_DLL_EXPORT ScrollBarMetrics
{
public:
	Int32 hScrollHeight;
	Int32 vScrollWidth;
	Int32 hScrollArrowWidth;
	Int32 vScrollArrowHeight;

	ScrollBarMetrics ():
		hScrollHeight (0),
		vScrollWidth (0),
		hScrollArrowWidth (0),
		vScrollArrowHeight (0)
	{
	}
};

class DG_DLL_EXPORT Utils
{
public:
	enum SystemColorType {
		ShadowColorType,			// COLOR_3DSHADOW,		[NSColor shadowColor]
		FaceColorType,				// COLOR_3DFACE,		[NSColor gridColor]
		StandardGrayTextColor
	};

	enum Alignment {
		RightTopOrLeftTop,				// Place dialog on the right of the control if possible (it has enough place), and if not, then to the left side of it. Top edges aligned.
		RightBottomOrLeftBottom,		// Place dialog on the right of the control if possible (it has enough place), and if not, then to the left side of it. Bottom edges aligned.
		LeftTopOrRightTop,				// Place dialog on the left of the control if possible (it has enough place), and if not, then to the right side of it. Top edges aligned.
		LeftBottomOrRightBottom,		// Place dialog on the left of the control if possible (it has enough place), and if not, then to the right side of it. Bottom edges aligned.
		RightCenter,					// Place dialog on the right of the control, center aligned
		BottomLeftRightOrTopLeftRight,	// Place dialog on the bottom of the control, left edges aligned if possible, and if not, then in order to the right edges are aligned
										// If this is not succeed, than the try top aligning
		BottomRight,					// Place dialog on the bottom of the control, right edges aligned
		OnlyKeepRectInScreen			// Place dialog on the screen fitting in it. No alignment, no passing to some item
	};

public:
	// --- Set parent window of a DG dialog opened from a system dialog ------------------------------------------------

	class DG_DLL_EXPORT SetNextModalParentGuard
	{
	private:
		const void* lastWindow;
		SetNextModalParentGuard () { }	// Disable default consrtuction

	public:
		SetNextModalParentGuard (const void* parentWindow);
		virtual ~SetNextModalParentGuard ();
	};

	// --- Image utilities ---------------------------------------------------------------------------------------------

#if defined (WINDOWS)
 	static void			FillRect (HDC context, double resolutionFactor, const DG::Rect& rect, const Gfx::Color& color, bool drawFrame = false, bool roundEdge = false, bool modifyColorForDisabledControl = false);
#endif

	// --- Drawing utilities -------------------------------------------------------------------------------------------

	static void			FillRect (NewDisplay::NativeContext& context, const DG::Rect& rect, const Gfx::Color& color, bool drawFrame = false, bool roundEdge = false, bool modifyColorForDisabledControl = false);

	// --- Text utilities ----------------------------------------------------------------------------------------------
	static Gfx::Color	GetSystemColor (SystemColorType type);
	static bool 		CanTextFitInArea (const GS::UniString& inText, const DG::Rect& inRect, bool wrappingItem, short inFontType, const double scaleFactor);
	//static GS::UniString WordWrapTextToWidth (const GS::UniString& inText, const short maxWidth, short inFontType, const GS::UniString& separatorStr);
	static void			DrawText (NewDisplay::NativeContext& context, const DG::Rect& rect, const GS::UniString& text, short inFontType, short alignment, bool endEllipsis = false, const Gfx::Color* color = nullptr);
	static void			DrawGrayText (NewDisplay::NativeContext& context, const DG::Rect& rect, const GS::UniString& text, short inFontType, short alignment, bool endEllipsis = false);
	static DG::Rect 	GetTextDimensions (const GS::UniString& inText, short inFontType, short inMaxWidth, short inMaxHeight, const double scaleFactor, bool wrapText);

#if defined (WINDOWS)
	static bool			GetTruncatedText (HTHEME hTheme, HDC hDC, int partId, int stateId, const wchar_t* pTextIn, const RECT* rc, short truncMode, wchar_t* pTextOut);
#endif

	// --- Other utilities ---------------------------------------------------------------------------------------------

	static GS::UniString	GetShortcutText		(const DG::Shortcut& shortcut, bool inBracket);
	static GS::UniString	GetShortcutText		(const CommandDescriptor* cmdDesc, bool inBracket, const DG::ShortcutScheme* shortcutScheme = nullptr);
	static GS::UniString	GetShortcutListText (const CommandDescriptor* cmdDesc, bool inBracket, GS::UniString delimiter, const DG::ShortcutScheme* shortcutScheme = nullptr);

	static bool			GetKeyState (Key::Modifier modifier, bool asyncRead = true);
	static bool			GetKeyState (const Key::Code& key, bool asyncRead = true);

	static bool			IsModifierKeyPressed ();

	static ScrollBarMetrics		GetScrollBarSizes (double scaleFactor);

	static ULong		GetDoubleClickTime (void);

	static Int32		GetRealDisplayDigits ();

#if defined (WINDOWS)
	static GS::UniString	GetGUIResourceUsageInfo (void);
	static bool			IsWindows11OrGreater ();
#endif

	static double		GetInitialToolTipDelay ();
	static double		GetToolTipToToolTipDelay ();

	// --- Dialog utilities --------------------------------------------------------------------------------------------

	static void		CalcDialogMaxClientSize (const DG::Dialog& dialog, short& maxClientWidth, short& maxClientHeight);

	static void		KeepRectInBoundingRect (DG::NativeRect& nativeRect, const DG::NativeRect& boundingRect);

	static void		PlaceDialogNextToNativeRect (DG::Dialog& dialog, const DG::NativeRect& nativeRect, Alignment alignment);
	static void		PlaceDialogNextToItem (DG::Dialog& dialog, const DG::Item& item, Alignment alignment);
	static void		PlaceDialogNextToItem (DG::Dialog& dialog, short dialogId, short itemId, Alignment alignment);
	static void		PlaceDialogNextToItems (DG::Dialog& dialog, const DG::Item& leftItem, const DG::Item& rightItem);

	static void		PlaceDialogToMousePos (DG::Dialog& dialog, const DG::NativeUnit& xOffset = DG::NativeUnit (), const DG::NativeUnit& yOffset = DG::NativeUnit (), Alignment alignment = RightTopOrLeftTop);

	// --- Drawing arrows ----------------------------------------------------------------------------------------------

	enum ArrowOrientation {
		Left,
		Right,
		Down
	};

	enum ArrowType {
		Opened,
		Filled
	};

#if defined (WINDOWS)
	static void		DrawArrow (HDC hDC, RECT  arrowRect,	 ArrowType arrowType, ArrowOrientation arrowOrientation, UInt32 dpi, bool disabled = false);
	static void		DrawArrow (HDC hDC, POINT arrowTipCoord, ArrowType arrowType, ArrowOrientation arrowOrientation, UInt32 dpi, bool disabled = false);

	static bool		GetArrowSize (ArrowType arrowType, ArrowOrientation arrowOrientation, UInt32 dpi, Int32* width, Int32* height = nullptr);
#endif

	static float	DistanceBetweenPoints (const DG::Point& point1, const DG::Point& point2);
	static float	DistanceBetweenPoints (const DG::NativePoint& point1, const DG::NativePoint& point2);

	static UInt32	GetRawDPIForWindow (void* window = nullptr);
};

// --- Utility functions -----------------------------------------------------------------------------------------------

DG_DLL_EXPORT bool CCALL			IsVisibleOnScreen (const DG::NativePoint& point);
DG_DLL_EXPORT DG::NativeRect CCALL	VisibleBoundingRectOfScreens (void);
DG_DLL_EXPORT short CCALL			GetPixelDepthOnScreen (const DG::NativeRect& rect);
DG_DLL_EXPORT double CCALL			GetPrimaryScreenScaleFactor (void);

DG_DLL_EXPORT void CCALL			GetMonitorRects (GS::Array<DG::NativeRect>& monitorRects, bool onlyUsableFrame = false);
DG_DLL_EXPORT void CCALL			LogMonitorInformation (void);
DG_DLL_EXPORT void CCALL			LogPaletteLayoutInformation (void);

DG_DLL_EXPORT DG::Icon CCALL		GetArrowImage (Utils::ArrowType arrowType, Utils::ArrowOrientation orientation);

// === CEF =============================================================================================================

DG_DLL_EXPORT GS::UniString CCALL	GetCefCacheBasePath ();
DG_DLL_EXPORT GS::UniString CCALL	GetCefCachePath (const GS::UniString& cacheBasePath);
DG_DLL_EXPORT GS::UShort CCALL		GetCefDebugPort ();
DG_DLL_EXPORT bool CCALL			GetCefUseBackgroundPriorityMessages ();

} // namespace DG

#endif
