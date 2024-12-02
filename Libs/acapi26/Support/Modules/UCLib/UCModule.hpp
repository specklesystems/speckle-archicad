// *****************************************************************************
// File:			UCModule.hpp
//
// Description:		Main include file of the UC C++ interface
//					Also contains module global definitions and functions
//
// Project:			GRAPHISOFT User Control Library (UCLib)
//
// Namespace:		UC
//
// Contact person:	VM
//
// SG compatible
// *****************************************************************************

#ifndef UCMODULE_HPP
#define UCMODULE_HPP


// --- Inlcudes ----------------------------------------------------------------

#include "DGModule.hpp"
#include "UC.h"

#include "UCRollDown.hpp"
#include "UCFontPopUp.hpp"
#include "UCCodePagePopUp.hpp"


// --- UC module management functions ------------------------------------------

namespace UC {

UC_DLL_EXPORT void	InitModule (const UCInitData* initData);

UC_DLL_EXPORT void	ExitModule (void);


// --- Class declarations ------------------------------------------------------

// --- UC257 Control -----------------------------------------------------------

class UC_DLL_EXPORT UC257: public DG::UserControl
{
public:
	enum ControlType {
		Pen			= T257_PEN,
		Fill		= T257_FILL,
		CFill		= T257_CFILL,
		Material	= T257_MATERIAL,
		Text		= T257_TEXT,
		IconText	= T257_ICONTEXT,
		Menu		= T257_MENU,
		ZoneCat		= T257_ZONECAT,
		Layer		= T257_LAYER,
		Profile		= T257_PROFILE,
		BuildingMat	= T257_BUILDINGMAT
	};

	enum HeaderType {
		NoHeader = 0,
		HasHeader
	};

	enum ButtonType {
		LargeButton = 0,
		SmallButton,
		TextPenButton
	};

	enum PaletteType {
		ScrollablePalette = 0,
		PlainPalette
	};

	enum FontType {
		LargeFont = 0,
		SmallFont
	};

			 UC257 (const DG::Panel& panel, short item);
			 UC257 (const DG::Panel& panel, const DG::Rect& rect);
	virtual ~UC257 ();

	void			SetCallBack (const UC257CallBack callBack);
	UC257CallBack	GetCallBack (void) const;

	void			SetControlType (ControlType controlType);
	ControlType		GetControlType (void) const;

	void			SetHeaderType (HeaderType headerType);
	HeaderType		GetHeaderType (void) const;

	void			SetButtonType (ButtonType buttonType);
	ButtonType		GetButtonType (void) const;

	void			SetPaletteType (PaletteType paletteType);
	PaletteType		GetPaletteType (void) const;

	void			SetFontType (FontType fontType);
	FontType		GetFontType (void) const;

	void			SetUserFlags (UChar userFlags);
	UChar			GetUserFlags (void) const;

	void			SetMenuId (UShort menuId, GSResModule resModule = InvalidResModule);
	UShort			GetMenuId (void) const;
	GSResModule		GetMenuResModuleId (void) const;

	void			SetUserData (const void* userData);
	void*			GetUserData (void) const;

	void			SetData (const void* data, Int32 offset, Int32 dataSize);
	Int32			GetData (void* data, Int32 offset, Int32 dataSize) const;

	void			SetForeColor (const Gfx::Color& color);
	Gfx::Color		GetForeColor (void) const;
	void			UseCellForeColor (void);

	void			SetBackColor (const Gfx::Color& color);
	Gfx::Color		GetBackColor (void) const;
	void			UseCellBackColor (void);

	void			SetFrameColor (const Gfx::Color& color);
	Gfx::Color		GetFrameColor (void) const;
	void			UseCellFrameColor (void);

	void			SetSeparatorColor (const Gfx::Color& color);	// #24094 TCS 2003.06.19
	Gfx::Color		GetSeparatorColor (void) const;
	void			UseCellSeparatorColor (void);

	void			ShowAndTrackPopup (void);

	void			SetVariousState (bool isVarious);
	bool			GetVariousState (void) const;
	void			SetVariousText (const GS::UniString& text);
	GS::UniString	GetVariousText (void) const;

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};


// --- TextPopup Control -------------------------------------------------------

class UC_DLL_EXPORT TextPopup: public DG::UserControl
{
protected:
	bool	bInitialized;
	ULong	ucFlags;

public:

	enum TextStyle {
		Normal,
		Bold,
		Italic,
		ItalicUnderline,
		Underline
	};

			 TextPopup (const DG::Panel& panel, short item);
			 TextPopup (const DG::Panel& panel, const DG::Rect& rect);
	virtual ~TextPopup ();

	virtual void	Initialize (const GS::UniString& missingItem, USize minWidth, USize columnNr);

	bool			IsInitialized (void) const;
	void			SetMissingItemText (const GS::UniString& text);
	GS::UniString	GetMissingItemText (void);

	void	SetUserData (const void* userData);
	void*	GetUserData (void) const;

	void	SetStyle (const UChar style);
	UChar	GetStyle (void) const;

	bool	AppendItem (const GS::UniString& text, UIndex* resultIndex = nullptr, bool noTrack = false);
	bool	AppendSeparatorItem (UIndex* resultIndex = nullptr);
	bool	InsertItem (UIndex index, const GS::UniString& text, bool reIndex = false, bool noTrack = false);
	bool	InsertSeparatorItem (UIndex index, bool reIndex = false);
	bool	DeleteItem (UIndex index, bool reIndex = false);
	void	DisableItem (UIndex index);
	void	EnableItem (UIndex index);
	void	SetItemStatus (UIndex index, bool enable);
	bool	IsItemEnabled (UIndex index) const;

	void		SetItemText (UIndex index, const GS::UniString& text);
	GS::UniString	GetItemText (UIndex index) const;
	Int32		GetItemTextLength (UIndex index) const;
	void		SetItemTextStyle (UIndex index, TextStyle style);
	TextStyle	GetItemTextStyle (UIndex index) const;

	void	SetItemValue (UIndex index, short value);
	short	GetItemValue (UIndex index) const;
	void	SetItemUserData (UIndex index, void* userData);
	void*	GetItemUserData (UIndex index) const;

	Int32	GetItemCount (void) const;

	void	ShowAndTrackPopup (void);

	void			SetVariousState (bool isVarious);
	bool			GetVariousState (void) const;
	void			SetVariousText (const GS::UniString& text);
	GS::UniString	GetVariousText (void) const;
};


// --- IconTextPopup Control ---------------------------------------------------

class UC_DLL_EXPORT IconTextPopup: public TextPopup
{
public:

	enum IconType {
		First,
		Second,
		Third
	};

	IconTextPopup (const DG::Panel& panel, short item);
	IconTextPopup (const DG::Panel& panel, const DG::Rect& rect);
	virtual ~IconTextPopup ();

	virtual void	Initialize (const GS::UniString& missingItem, USize minWidth, USize columnNr) override;

	void	SetItemIcon (UIndex index, GSResModule iconResModule, short iconRes, IconType iconType = Second);
	short	GetItemIcon (UIndex index, GSResModule* iconResModule, IconType iconType = Second) const;
};


// --- UC258 Control -----------------------------------------------------------

class UC_DLL_EXPORT UC258: public DG::UserControl
{
public:
	enum HeaderType {
		NoHeader = 0,
		HasHeader
	};

	enum PalettePosition {
		OnControlRightEdge = 0,
		OnMouseClickPos
	};

	enum FrameType {
		NormalFrame = 0,
		SimpleFrame
	};

	UC258 (const DG::Panel& panel, short item);
	UC258 (const DG::Panel& panel, const DG::Rect& rect);
   ~UC258 ();

	void			SetHeaderType (HeaderType headerType);
	HeaderType		GetHeaderType (void) const;

	void			SetPalettePosition (PalettePosition palettePosition);
	PalettePosition	GetPalettePosition (void) const;

	void			SetPaletteFrame (FrameType frameType);
	FrameType		GetPaletteFrame (void) const;

	void			SetImageButtonCentered (bool buttonCentered);
	bool			IsImageButtonCentered () const;

	void			SetImage (const DG::Icon& image, short itemCount, short rowCount);
	DG::Icon		GetImage (void) const;
	short			GetItemCount (void) const;
	short			GetRowCount (void) const;

	void			EnableItem (short item);
	void			DisableItem (short item);
	void			SetItemStatus (short item, bool enable);
	bool			IsItemEnabled (short item) const;

	void			ShowAndTrackPopup (void);

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};


// --- UC259 Control -----------------------------------------------------------

class UC_DLL_EXPORT UC259: public DG::UserControl
{
public:
	UC259 (const DG::Panel& panel, short item);
	UC259 (const DG::Panel& panel, const DG::Rect& rect);
   ~UC259 ();

	void			SetImage (const DG::Icon& image, short itemCount, short rowCount);
	DG::Icon		GetImage (void) const;
	short			GetItemCount (void) const;
	short			GetRowCount (void) const;

	void			EnableItem (short item);
	void			DisableItem (short item);
	void			SetItemStatus (short item, bool enable);
	bool			IsItemEnabled (short item) const;

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};


// --- UC261 Control -----------------------------------------------------------

class UC_DLL_EXPORT UC261: public DG::UserControl
{
public:
	enum HeaderType {
		NoHeader = 0,
		HasHeader
	};

	enum ButtonType {
		LargeButton = 0,
		SmallButton
	};

	enum DataType {
		Normal = 0,
		Dynamic
	};

	UC261 (const DG::Panel& panel, short item);
	UC261 (const DG::Panel& panel, const DG::Rect& rect);
   ~UC261 ();

	void			SetCallBack (const UC261CallBack callBack);
	UC261CallBack	GetCallBack (void) const;

	void			SetHeaderType (HeaderType headerType);
	HeaderType		GetHeaderType (void) const;

	void			SetButtonType (ButtonType buttonType);
	ButtonType		GetButtonType (void) const;

	void			SetDataType (DataType dataType);
	DataType		GetDataType (void) const;

	void			SetUserFlags (UChar userFlags);
	UChar			GetUserFlags (void) const;

	void			SetUserData (const void* userData);
	void*			GetUserData (void) const;

	void			SetData (const void* data, Int32 offset, Int32 dataSize);
	Int32			GetData (void* data, Int32 offset, Int32 dataSize) const;

	void			ShowAndTrackPopup (void);

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};


// --- UC262 Control -----------------------------------------------------------

class UC_DLL_EXPORT UC262: public DG::UserControl
{
public:
	UC262 (const DG::Panel& panel, short item);
	UC262 (const DG::Panel& panel, const DG::Rect& rect);
   ~UC262 ();

	void			Setup (short itemCount, short rowCount, short columnCount);
	short			GetItemCount (void) const;
	short			GetRowCount (void) const;
	short			GetColumnCount (void) const;

	void			ShowAllPens (bool showAllPens);
	bool			GetShowAllPensState (void) const;

	void			SetCellData (short cellIndex, short value, bool selected, UChar flags,
								 UChar r, UChar g, UChar b, const GS::UniString& topText, const GS::UniString& bottomText);

	void			SetCellValue (short cellIndex, short cellValue);
	short			GetCellValue (short cellIndex) const;

	void			SelectCell (short cellIndex, bool selected);
	bool			IsCellSelected (short cellIndex) const;

	void			SetCellFlags (short cellIndex, UChar cellFlags);
	UChar			GetCellFlags (short cellIndex) const;

	void			SetCellColor (short cellIndex, const Gfx::Color& color);
	Gfx::Color		GetCellColor (short cellIndex) const;

	void			SetCellTopText (short cellIndex, const GS::UniString& text);
	GS::UniString	GetCellTopText (short cellIndex) const;

	void			SetCellBottomText (short cellIndex, const GS::UniString& text);
	GS::UniString	GetCellBottomText (short cellIndex) const;

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};

}	// namespace UC

#endif
