// *********************************************************************************************************************
// File:			UC.h
//
// Description:		General external header file.
//
// Project:			GRAPHISOFT User Controls (UCLib)
//
// Contact person:	VM
// *********************************************************************************************************************

#ifndef	UC_H
#define	UC_H

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "DG.h"
#include "uchar_t.hpp"

#if defined (__cplusplus)
	extern "C" {
#endif

#include "UCDefs.h"

#include "PlatformDLLExport.hpp" // from GSRoot


// --- Module export defines -------------------------------------------------------------------------------------------

#if defined (UC_DLL_COMPILE)
	#define UC_DLL_EXPORT	PLATFORM_DLL_EXPORT
#else
	#define UC_DLL_EXPORT	PLATFORM_DLL_IMPORT
#endif


// --- Macros ----------------------------------------------------------------------------------------------------------

#define	UC257DataSize(n)	((Int32) sizeof (UC257HeadData) + (n - 1) * (Int32) sizeof (UC257CellData))
#define	UC261DataSize(n)	((Int32) sizeof (UC261HeadData) + (n - 1) * (Int32) sizeof (UC261CellData))
#define	UC262DataSize(n)	((Int32) sizeof (UC262HeadData) + (n - 1) * (Int32) sizeof (UC262CellData))


// --- Types -----------------------------------------------------------------------------------------------------------

struct UCInitData {
	Int32			filler1;				// Used on macintosh
};

class UC_DLL_EXPORT UC257CallBackRec: public DG::ItemUpdateEventArg {					// CallBack parameter record
public:
	UShort			type;					// T257_PEN, T257_FILL, T257_CFILL, T257_MATERIAL, T257_TEXT,
											// T257_ICONTEXT, T257_MENU, T257_ZONECAT, T257_BUILDINGMAT
	UChar			style;					// CS257_HEADER, CS257_SMALLBUTTON, CS257_PLAINPALETTE, CS257_SMALLFONT
	UChar			userFlags;				// User defined parameter
	UShort			id;						// UC257 menu resource ID
	GSResModule		resModule;				// UC257 menu resource module
	UChar			action;					// ACT_GETITEMSIZE, ACT_GETITEM, ACT_GETLISTSIZE, ACT_GETLIST
											// ACT_DRAWBUTTON
	Int32			value;					// Control value
	short			right;					// Draw rect right edge
	short			bottom;					// Draw rect bottom edge
	void*			userData;
	Int32			dataSize;				// Control data size
	void*			data;					// Control data

	void Init (void)
	{
		type = 0;

		style = 0;
		userFlags = 0;
		id = 0;
		resModule = 0;
		action = 0;

		value = 0;
		right = 0;
		bottom = 0;
		userData = nullptr;
		dataSize = 0;
		data = nullptr;
	}
	UC257CallBackRec ()
	{
		Init ();
	}

	virtual ~UC257CallBackRec ();
};

struct CellRGB {
	UChar			red;
	UChar			green;
	UChar			blue;
	UChar			filler;

	void Init (void)
	{
		red = 0;
		green = 0;
		blue = 0;
		filler = 0;
	}
	CellRGB ()
	{
		Init ();
	}
};

class UC_DLL_EXPORT UC261CallBackRec : public DG::ItemUpdateEventArg {					// CallBack parameter record
public:
	UChar			style;					// CS261_HEADER, CS261_SMALLBUTTON
	UChar			userFlags;				// User defined parameter
	UChar			action;					// ACT_GETITEMSIZE, ACT_GETITEM, ACT_GETLISTSIZE, ACT_GETLIST,
											// ACT_DRAWITEM, ACT_DRAWBUTTON
	UChar			filler;
	Int32			value;					// Control value
	short			right;					// Draw rect right edge
	short			bottom;					// Draw rect bottom edge
	void*			userData;
	Int32			dataSize;				// Control data size
	void*			data;					// Control data

	CellRGB			foreGroundColor;		// RGB values

	void Init (void)
	{
		style = 0;
		userFlags = 0;
		action = 0;

		filler = 0;
		value = 0;
		right = 0;
		bottom = 0;
		userData = nullptr;
		dataSize = 0;
		data = nullptr;
	}
	UC261CallBackRec ()
	{
		Init ();
	}
	virtual ~UC261CallBackRec ();
};

struct UC257CellData {
	GS::uchar_t		text[1024];				// Cell text in unicode
	CellRGB			foreGroundColor[48];	// RGB values		[VBAttr::MaxSkinNumber = 48]
	CellRGB			backGroundColor[48];	// RGB values		[VBAttr::MaxSkinNumber = 48]
	CellRGB			frameColor[48];			// RGB values		[VBAttr::MaxSkinNumber = 48]
	CellRGB			separatorColor[49];		// RGB values		[VBAttr::MaxSkinFaceLineNumber = 49]
	short			size[48];				// Cell item sizes	[VBAttr::MaxSkinNumber = 48]
	UChar			pattern[48][8];			// Patterns			[VBAttr::MaxSkinNumber = 48]
	short			skinType[48];			// The type of skin	[VBAttr::MaxSkinNumber = 48]
	ULong			flags;					// Cell flags
	GSResModule		icon1ResModule;			// Resource module of icon1
	GSResModule		icon2ResModule;			// Resource module of icon2
	GSResModule		icon3ResModule;			// Resource module of icon3
	GSResModule		icon4ResModule;			// Resource module of icon4
	GSResModule		icon5ResModule;			// Resource module of icon5
	GSResModule		icon6ResModule;			// Resource module of icon6
	short			icon1;					// Icon1 id
	short			icon2;					// Icon2 id
	short			icon3;					// Icon3 id
	short			icon4;					// Icon4 id
	short			icon5;					// Icon5 id
	short			icon6;					// Icon6 id
	Int32			connectionPriority;		// For building material
	short			dataType;				// For mixed type control cell data
	short			subType;				// SubType: fillType
	Int32			uniqueID;				// Unique ID of item
	Int32			value;					// Return value when selected
	Int32			connectionClassId;
	void*			userData;				// Used to store a custom data in a cell
};

struct UC257HeadData {
	Int32			minWidth;				// Minimum pixel width of cells
	Int32			nColumns;				// Number of columns, 0 = auto
	Int32			nCells;					// Number of cells
	GSResModule		layerIconResModule;		// Resource module of layerIcon
	short			layerIconId;			// Icon resource id of layer type control
	UChar			fontOfMissing;			// Font style of missing text
	UChar			filler;					//
	GS::uchar_t		layerName[32];			// Name of layer type control
	GS::uchar_t		missingName[64];		// Name of missing item
	GS::uchar_t		fillHeadText[32];		// Separator text preceding normal fills
	GS::uchar_t		cwallHeadText[32];		// Separator text preceding composites
	UC257CellData	cell[1];				// First cell data
};

struct UC261CellData {
	GS::uchar_t		text[1024];				// Cell text
	ULong			flags;					// Cell flags
	short			filler;
	short			width;					// Item width
	GS::uchar_t		scaledText[128];		// Scaled / scale independent
	Int32			value;					// Return value when selected
	Int32			uniqueID;				// Unique ID of item
};

struct UC261HeadData {
	Int32			nCells;					// Number of cells
	GS::uchar_t		missingName[64];		// Name of missing item
	UC261CellData	cell[1];				// First cell data
};

struct UC262CellData {
	short			value;					// Return value when selected
	bool			selected;				// Selection status
	UChar			flags;					// Cell flags
	CellRGB			color;					// Cell color
	GS::uchar_t		text1[8];				// Text for top left corner
	GS::uchar_t		text2[8];				// Text for bottom right corner
};

struct UC262HeadData {
	short			nCells;					// Number of cells
	short			nRows;					// Number of rows
	short			nColumns;				// Number of columns
	bool			showAllPens;			// Ignore CCF262_USEDPEN flag
	bool			filler;
	UC262CellData	cell[1];				// First cell data
};


typedef	void (CCALL *UC257CallBack) (UC257CallBackRec* uc257callBackRec);
typedef	void (CCALL *UC261CallBack) (UC261CallBackRec* uc261callBackRec);



// ... UC257 Control functions .........................................................................................

UC_DLL_EXPORT void CCALL			UC257SetCallBack (short dialId, short item, const UC257CallBack callBack);
UC_DLL_EXPORT UC257CallBack CCALL	UC257GetCallBack (short dialId, short item);

UC_DLL_EXPORT void CCALL			UC257SetType (short dialId, short item, UShort type);
UC_DLL_EXPORT UShort CCALL			UC257GetType (short dialId, short item);

UC_DLL_EXPORT void CCALL			UC257SetStyle (short dialId, short item, UChar style);
UC_DLL_EXPORT UChar CCALL			UC257GetStyle (short dialId, short item);

UC_DLL_EXPORT void CCALL			UC257SetUserFlags (short dialId, short item, UChar userFlags);
UC_DLL_EXPORT UChar CCALL			UC257GetUserFlags (short dialId, short item);

UC_DLL_EXPORT void CCALL			UC257SetMenuId (short dialId, short item, UShort menuId, GSResModule resModule = InvalidResModule);
UC_DLL_EXPORT UShort CCALL			UC257GetMenuId (short dialId, short item);
UC_DLL_EXPORT GSResModule CCALL		UC257GetMenuResModuleId (short dialId, short item);

UC_DLL_EXPORT void CCALL			UC257SetUserData (short dialId, short item, const void* userData);
UC_DLL_EXPORT void* CCALL			UC257GetUserData (short dialId, short item);

UC_DLL_EXPORT void CCALL			UC257SetData (short dialId, short item, const void* data, Int32 offset, Int32 dataSize);
UC_DLL_EXPORT Int32 CCALL			UC257GetData (short dialId, short item, void* data, Int32 offset, Int32 dataSize);

UC_DLL_EXPORT void CCALL			UC257SetColor (short dialId, short item, UChar colorIndex, UChar r, UChar g, UChar b);
UC_DLL_EXPORT void CCALL			UC257GetColor (short dialId, short item, UChar colorIndex, UChar* r, UChar* g, UChar* b);
UC_DLL_EXPORT void CCALL			UC257UseCellColor (short dialId, short item, UChar colorIndex);

UC_DLL_EXPORT void CCALL			UC257ShowAndTrackPopup (short dialId, short item);

UC_DLL_EXPORT void CCALL			UC257SetVariousState (short dialId, short item, bool isVarious);
UC_DLL_EXPORT bool CCALL			UC257GetVariousState (short dialId, short item);

UC_DLL_EXPORT void CCALL			UC257SetVariousText (short dialId, short itemId, const GS::UniString& text);

// ... UC258 Control functions .........................................................................................

UC_DLL_EXPORT void CCALL			UC258SetStyle (short dialId, short item, UChar style);
UC_DLL_EXPORT UChar CCALL			UC258GetStyle (short dialId, short item);

UC_DLL_EXPORT void CCALL			UC258SetImage (short dialId, short item, const DG::Icon& icon, short cellNum, short rowNum);
UC_DLL_EXPORT void CCALL			UC258SetTitleHeaderResModule (short dialId, short item, GSResModule resModule);

UC_DLL_EXPORT short CCALL			UC258GetCellNum (short dialId, short item);
UC_DLL_EXPORT short CCALL			UC258GetRowNum (short dialId, short item);

UC_DLL_EXPORT void CCALL			UC258SetCellEnable (short dialId, short item, short cellIndex, bool enable);
UC_DLL_EXPORT bool CCALL			UC258IsCellEnabled (short dialId, short item, short cellIndex);

UC_DLL_EXPORT void CCALL			UC258ShowAndTrackPopup (short dialId, short item);


// ... UC259 Control functions .........................................................................................

UC_DLL_EXPORT void CCALL			UC259SetImage (short dialId, short item, const DG::Icon& icon, short cellNum, short rowNum);

UC_DLL_EXPORT short CCALL			UC259GetCellNum (short dialId, short item);
UC_DLL_EXPORT short CCALL			UC259GetRowNum (short dialId, short item);

UC_DLL_EXPORT void CCALL			UC259SetCellEnable (short dialId, short item, short cellIndex, bool enable);
UC_DLL_EXPORT bool CCALL			UC259IsCellEnabled (short dialId, short item, short cellIndex);


// ... UCRollDown control (UC260) functions ............................................................................

UC_DLL_EXPORT void CCALL			UCRollDownSetStyle (short dialId, short item, short style);
UC_DLL_EXPORT short CCALL			UCRollDownGetStyle (short dialId, short item);

UC_DLL_EXPORT void CCALL			UCRollDownSetFont (short dialId, short item, short font);
UC_DLL_EXPORT short CCALL			UCRollDownGetFont (short dialId, short item);

UC_DLL_EXPORT void CCALL			UCRollDownSetIconFieldWidth (short dialId, short item, short width);
UC_DLL_EXPORT short CCALL			UCRollDownGetIconFieldWidth (short dialId, short item);

UC_DLL_EXPORT void CCALL			UCRollDownSetIcon (short dialId, short item, const DG::Icon& icon);

UC_DLL_EXPORT short CCALL			UCRollDownGetExpandedHeight (short dialId, short item);
UC_DLL_EXPORT short CCALL			UCRollDownGetCollapsedHeight (short dialId, short item);

UC_DLL_EXPORT void CCALL			UCRollDownSetText (short dialId, short item, const GS::UniString& text);

UC_DLL_EXPORT void CCALL			UCRollDownSetTextTruncation (short dialId, short item, short truncation);
UC_DLL_EXPORT short CCALL			UCRollDownGetTextTruncation (short dialId, short item);


// ... UC261 Control functions .........................................................................................

UC_DLL_EXPORT void CCALL			UC261SetCallBack (short dialId, short item, const UC261CallBack callBack);
UC_DLL_EXPORT UC261CallBack CCALL	UC261GetCallBack (short dialId, short item);

UC_DLL_EXPORT void CCALL			UC261SetStyle (short dialId, short item, UChar style);
UC_DLL_EXPORT UChar CCALL			UC261GetStyle (short dialId, short item);

UC_DLL_EXPORT void CCALL			UC261SetUserFlags (short dialId, short item, UChar userFlags);
UC_DLL_EXPORT UChar CCALL			UC261GetUserFlags (short dialId, short item);

UC_DLL_EXPORT void CCALL			UC261SetUserData (short dialId, short item, const void* userData);
UC_DLL_EXPORT void* CCALL			UC261GetUserData (short dialId, short item);

UC_DLL_EXPORT void CCALL			UC261SetData (short dialId, short item, const void* data, Int32 offset, Int32 dataSize);
UC_DLL_EXPORT Int32 CCALL			UC261GetData (short dialId, short item, void* data, Int32 offset, Int32 dataSize);

UC_DLL_EXPORT void CCALL			UC261ShowAndTrackPopup (short dialId, short item);


// ... UC262 Control functions .........................................................................................

UC_DLL_EXPORT void CCALL			UC262Setup (short dialId, short item, short cellNum, short rowNum, short colNum);
UC_DLL_EXPORT short CCALL			UC262GetCellNum (short dialId, short item);
UC_DLL_EXPORT short CCALL			UC262GetRowNum (short dialId, short item);
UC_DLL_EXPORT short CCALL			UC262GetColNum (short dialId, short item);

UC_DLL_EXPORT void CCALL			UC262ShowAllPens (short dialId, short item, bool showAllPens);
UC_DLL_EXPORT bool CCALL			UC262GetShowAllPensState (short dialId, short item);

UC_DLL_EXPORT void CCALL			UC262SetCellData (short dialId, short item, short cellIndex, short value, bool selected, UChar flags, UChar r, UChar g, UChar b, const GS::UniString& topText, const GS::UniString& bottomText);

UC_DLL_EXPORT void CCALL			UC262SetCellValue (short dialId, short item, short cellIndex, short cellValue);
UC_DLL_EXPORT short CCALL			UC262GetCellValue (short dialId, short item, short cellIndex);

UC_DLL_EXPORT void CCALL			UC262SelectCell (short dialId, short item, short cellIndex, bool selected);
UC_DLL_EXPORT bool CCALL			UC262IsCellSelected (short dialId, short item, short cellIndex);

UC_DLL_EXPORT void CCALL			UC262SetCellFlags (short dialId, short item, short cellIndex, UChar cellFlags);
UC_DLL_EXPORT UChar CCALL			UC262GetCellFlags (short dialId, short item, short cellIndex);

UC_DLL_EXPORT void CCALL			UC262SetCellColor (short dialId, short item, short cellIndex, UChar r, UChar g, UChar b);
UC_DLL_EXPORT void CCALL			UC262GetCellColor (short dialId, short item, short cellIndex, UChar* r, UChar* g, UChar* b);

UC_DLL_EXPORT void CCALL			UC262SetCellTopText (short dialId, short item, short cellIndex, const GS::UniString& text);

UC_DLL_EXPORT void CCALL			UC262SetCellBottomText (short dialId, short item, short cellIndex, const GS::UniString& text);


// ... UCPopup control (UC263) functions ...............................................................................

UC_DLL_EXPORT void CCALL			UCPopupSetControlKind (short dialId, short item, short controlKind);
UC_DLL_EXPORT short CCALL			UCPopupGetControlKind (short dialId, short item);

UC_DLL_EXPORT void CCALL			UCPopupSetButtonType (short dialId, short item, short buttonType);
UC_DLL_EXPORT short CCALL			UCPopupGetButtonType (short dialId, short item);
UC_DLL_EXPORT void CCALL			UCPopupOptimizeButtonType (short dialId, short item);

UC_DLL_EXPORT void CCALL			UCPopupSetButtonIcon (short dialId, short item, const void* icon);
UC_DLL_EXPORT bool CCALL			UCPopupGetButtonIcon (short dialId, short item, void* icon);

UC_DLL_EXPORT void CCALL			UCPopupSetButtonText (short dialId, short item, const GS::UniString& text);

UC_DLL_EXPORT void CCALL			UCPopupSetButtonTextStyle (short dialId, short item, short buttonStyle);
UC_DLL_EXPORT short CCALL			UCPopupGetButtonTextStyle (short dialId, short item);


UC_DLL_EXPORT bool CCALL			UCPopupAppendItem (short dialId, short item);
UC_DLL_EXPORT bool CCALL			UCPopupAppendSeparator (short dialId, short item);
UC_DLL_EXPORT bool CCALL			UCPopupInsertItem (short dialId, short item, UIndex popupItemIndex);
UC_DLL_EXPORT bool CCALL			UCPopupInsertSeparator (short dialId, short item, UIndex popupItemIndex);
UC_DLL_EXPORT bool CCALL			UCPopupDeleteItem (short dialId, short item, UIndex popupItemIndex);
UC_DLL_EXPORT void CCALL			UCPopupDeleteAllItems (short dialId, short item);

UC_DLL_EXPORT USize CCALL			UCPopupGetItemCount (short dialId, short item);

UC_DLL_EXPORT void CCALL			UCPopupSelectItem (short dialId, short item, UIndex popupItemIndex);
UC_DLL_EXPORT UIndex CCALL			UCPopupGetSelectedItem (short dialId, short item);

UC_DLL_EXPORT UIndex CCALL			UCPopupGetTrackedItem (short dialId, short item);

UC_DLL_EXPORT void CCALL			UCPopupSetItemIcon (short dialId, short item, UIndex popupItemIndex, const void* icon);
UC_DLL_EXPORT bool CCALL			UCPopupGetItemIcon (short dialId, short item, UIndex popupItemIndex, void* icon);

UC_DLL_EXPORT void CCALL			UCPopupSetItemText (short dialId, short item, UIndex popupItemIndex, const GS::UniString& text);

UC_DLL_EXPORT void CCALL			UCPopupSetItemTextStyle (short dialId, short item, UIndex popupItemIndex, short style);
UC_DLL_EXPORT short CCALL			UCPopupGetItemTextStyle (short dialId, short item, UIndex popupItemIndex);

UC_DLL_EXPORT void CCALL			UCPopupSetItemData (short dialId, short item, UIndex popupItemIndex, void* data);
UC_DLL_EXPORT void* CCALL			UCPopupGetItemData (short dialId, short item, UIndex popupItemIndex);

UC_DLL_EXPORT void CCALL			UCPopupCheckItem (short dialId, short item, UIndex popupItemIndex);
UC_DLL_EXPORT void CCALL			UCPopupUncheckItem (short dialId, short item, UIndex popupItemIndex);
UC_DLL_EXPORT void CCALL			UCPopupSetItemState (short dialId, short item, UIndex popupItemIndex, bool state);
UC_DLL_EXPORT bool CCALL			UCPopupIsItemChecked (short dialId, short item, UIndex popupItemIndex);

UC_DLL_EXPORT void CCALL			UCPopupEnableItem (short dialId, short item, UIndex popupItemIndex);
UC_DLL_EXPORT void CCALL			UCPopupDisableItem (short dialId, short item, UIndex popupItemIndex);
UC_DLL_EXPORT void CCALL			UCPopupSetItemStatus (short dialId, short item, UIndex popupItemIndex, bool status);
UC_DLL_EXPORT bool CCALL			UCPopupIsItemEnabled (short dialId, short item, UIndex popupItemIndex);

UC_DLL_EXPORT bool CCALL			UCPopupIsSeparatorItem (short dialId, short item, UIndex popupItemIndex);

UC_DLL_EXPORT void CCALL			UCPopupSetItemHeight (short dialId, short item, UShort itemHeight);
UC_DLL_EXPORT UShort CCALL			UCPopupGetItemHeight (short dialId, short item);

UC_DLL_EXPORT void CCALL			UCPopupShowAndTrackPopup (short dialId, short item);

UC_DLL_EXPORT void CCALL			UCPopupEnableDraw (short dialId, short item);
UC_DLL_EXPORT void CCALL			UCPopupDisableDraw (short dialId, short item);

UC_DLL_EXPORT void CCALL			UCPopupSetVariousState (short dialId, short itemId, bool isVarious);
UC_DLL_EXPORT bool CCALL			UCPopupGetVariousState (short dialId, short itemId);

UC_DLL_EXPORT void CCALL			UCPopupSetVariousText (short dialId, short itemId, const GS::UniString& text);

UC_DLL_EXPORT void CCALL            UCPopupSetAlignment (short dialId, short itemId, short alignment);
UC_DLL_EXPORT short CCALL           UCPopupGetAlignment (short dialId, short itemId);


// --- Dynamic Library functions ---------------------------------------------------------------------------------------

UC_DLL_EXPORT bool CCALL			UCInit (const UCInitData* initData);

UC_DLL_EXPORT void CCALL			UCExit (void);

UC_DLL_EXPORT GSResModule CCALL		GetUCResourceModule (void);


#if defined (__cplusplus)
	}
#endif


UC_DLL_EXPORT GS::UniString CCALL	UCRollDownGetText (short dialId, short item);

UC_DLL_EXPORT GS::UniString CCALL	UC262GetCellTopText (short dialId, short item, short cellIndex);

UC_DLL_EXPORT GS::UniString CCALL	UC262GetCellBottomText (short dialId, short item, short cellIndex);

UC_DLL_EXPORT GS::UniString CCALL	UCPopupGetItemText (short dialId, short item, UIndex popupItemIndex);

UC_DLL_EXPORT GS::UniString CCALL	UCPopupGetButtonText (short dialId, short item);

UC_DLL_EXPORT GS::UniString CCALL	UC257GetVariousText (short dialId, short itemId);

UC_DLL_EXPORT GS::UniString CCALL	UCPopupGetVariousText (short dialId, short itemId);

UC_DLL_EXPORT DG::Icon CCALL		UC258GetImage (short dialId, short item);

UC_DLL_EXPORT DG::Icon CCALL		UC259GetImage (short dialId, short item);

UC_DLL_EXPORT DG::Icon CCALL		UCRollDownGetIcon (short dialId, short item);

UC_DLL_EXPORT void CCALL					UCPopupSetItemObjectData (short dialId, short item, UIndex popupItemIndex, GS::Ref<GS::Object> data);

UC_DLL_EXPORT GS::Ref<GS::Object> CCALL		UCPopupGetItemObjectData (short dialId, short item, UIndex popupItemIndex);

#endif
