// *********************************************************************************************************************
// File:			DG.h
//
// Description:		Main include file of the GRAPHISOFT Dialog Manager
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Contact person:	BM
// *********************************************************************************************************************

#ifndef DG_H
#define DG_H

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "Color.hpp"
#include "GSGuid.hpp"
#include "GSRoot.hpp"
#include "Ref.hpp"
#include "UniString.hpp"
#include "RSTypes.hpp"

#include "DGDLLExport.h"
#include "DGItemEventArgs.hpp"
#include "DGPanelEventArgs.hpp"

#include "DGNativeUnit.hpp"

namespace IO {
	class Location;
}

namespace DG {
	class Image;
	class Icon;
	class NumericInputLimitHandler;
}

namespace TE {
	class CharStyle;
	class ICharStyle;
	class IParagraph;
	class Paragraph;
	class FontFamily;
}

namespace NewDisplay {
	class NativeImage;
}

//#if defined (__cplusplus)
//	extern "C" {
//#endif

#include "DGDefs.h"


// --- Macros ----------------------------------------------------------------------------------------------------------

#define DGGetLoShort(longData)	((short) (longData))
#if defined (WINDOWS)
	#define DGGetHiShort(longData)	((short) (((ULong) (longData) >> 16) & 0xFFFF))
#endif
#if defined (macintosh)
	#define DGGetHiShort(longData)	((short) ((Int32) (longData) >> 16))		// #19942 hg 02.12.03  macen optimalizalasi hiba volt a fenti kifejezesnel
#endif

#define DGGetHGrow				DGGetLoShort
#define DGGetVGrow				DGGetHiShort

#define DGGetHCoord				DGGetLoShort
#define DGGetVCoord				DGGetHiShort

#define DGListGetOldDragPos		DGGetLoShort
#define DGListGetNewDragPos		DGGetHiShort

#define DGGetPrevItemVal		DGGetLoShort
#define DGGetPrevMenuItem		DGGetHiShort


// --- MSGData typedefs ------------------------------------------------------------------------------------------------

typedef DG::ListBoxItemMouseEventArg			DGListMsgData;
typedef DG::ListBoxHeaderEventArg				DGListHeaderMsgData;
typedef DG::ItemUpdateEventArg					IDGItemUpdateData;
typedef DG::ListBoxUpdateEventArg				DGListUpdateData;
typedef DG::ListViewUpdateEventArg				DGListViewUpdateData;
typedef DG::UserItemUpdateEventArg				DGUserUpdateData;
typedef DG::UserItemMouseEventArg				DGUserMsgData;
typedef DG::StaticItemMouseEventArg				DGStaticItemMsgData;
typedef DG::TreeViewChangeEventArg				DGTreeViewChangeData;
typedef DG::TreeViewItemClickEventArg			DGTreeViewItemClickData;
typedef DG::ShortcutEditChangeEventArg			DGShortcutEditMsgData;
typedef DG::TabBarMouseEventArg					DGTabBarClickItemMsgData;
typedef DG::TabBarItemDragEventArg				DGTabBarDragItemMsgData;
typedef DG::SplitterDragEventArg				DGSplitterMsgData;
typedef DG::RulerClickEventArg					DGRulerClickData;
typedef DG::RulerChangeEventArg					DGRulerChangeData;
typedef DG::UserItemResolutionChangeEventArg	DGResolutionFactorChangeData;
typedef DG::RichEditChangeEventArg 				DGRichEditChangeData;
typedef DG::UniRichEditChangeEventArg 			DGUniRichEditChangeData;

typedef DG::PanelBackgroundPaintEventArg		DGBackgroundPaintMsgData;
typedef DG::ResizeEventArg						DGResizeMsgData;
typedef DG::PanelTopStatusChangeEventArg		DGTopStatusMsgData;
typedef DG::DialogScaleChangeEventArg			DGDialogScaleMsgData;

typedef DG::DragDropEventArg					DGDragDropMsgData;
typedef DG::ContextMenuEventArg					DGContextMenuMsgData;
typedef DG::WheelEventArg						DGWheelMsgData;
typedef DG::HelpEventArg						DGItemHelpMsgData;


// --- Types -----------------------------------------------------------------------------------------------------------

typedef	GS::IntPtr				DGMessageData;
typedef	GS::IntPtr				DGUserData;

struct DGMenuChoiceDialogUniStrings {
	GS::UniString	selectItemText;		// 'Select Item' lefttext for dynamic menu item choice dialog
	GS::UniString	selectText;			// 'Select' text for dynamic menu item choice dialog
	GS::UniString	cancelText;			// 'Cancel' text for dynamic menu item choice dialog

	void Init (void)
	{
		selectItemText.Clear ();
		selectText.Clear ();
		cancelText.Clear ();
	}

	DGMenuChoiceDialogUniStrings ()
	{
		Init ();
	}
};

struct DGRulerUniStrings {
	GS::UniString	mmText;						// mm text for the ruler
	GS::UniString	cmText;						// cm text for the ruler
	GS::UniString	dmText;						// dm text for the ruler
	GS::UniString	mText;						// m text for the ruler
	GS::UniString	kmText;						// km text for the ruler
	GS::UniString	leftTabText;				// left tabulator text for the ruler
	GS::UniString	rightTabText;				// right tabulator text for the ruler
	GS::UniString	middleTabText;				// middle tabulator text for the ruler
	GS::UniString	decimalTabText;				// deciaml tabulator text for the ruler
	GS::UniString	firstLineIndentText;		// first line indent text for the ruler
	GS::UniString	leftIndentText;				// left indent text for the ruler
	GS::UniString	rightIndentText;			// right indent text for the ruler

	void Init (void)
	{
		mmText.Clear ();
		cmText.Clear ();
		dmText.Clear ();
		mText.Clear ();
		kmText.Clear ();
		leftTabText.Clear ();
		rightTabText.Clear ();
		middleTabText.Clear ();
		decimalTabText.Clear ();
		firstLineIndentText.Clear ();
		leftIndentText.Clear ();
		rightIndentText.Clear ();
	}
	DGRulerUniStrings ()
	{
		Init ();
	}
};

struct DGFileDialogUniStrings {
	GS::UniString	openText;					// 'Open' text for the OpenFolder dialog OK button
	GS::UniString	chooseText;					// 'Choose' text for the OpenFolder dialog OK button
	GS::UniString	fileNameText;				// 'File name:' text for the OpenFolder dialog static text
	GS::UniString	folderNameText;				// 'Folder name:' text for the OpenFolder dialog static text
	GS::UniString	fileOrFolderText;			// 'File or folder:' text for the OpenFolder dialog static text
	GS::UniString	warningCaptionText;			// 'Warning' title of the alert
	GS::UniString	warningAlertText;			// Alert text of the Warning in the file dialog
	GS::UniString 	warningAlertAllTypeText;	// Alert text of the Warning in the file dialog when "All file type (*.*)" selected

	void Init (void)
	{
		openText.Clear ();
		chooseText.Clear ();
		fileNameText.Clear ();
		folderNameText.Clear ();
		fileOrFolderText.Clear ();
		warningCaptionText.Clear ();
		warningAlertText.Clear ();
		warningAlertAllTypeText.Clear ();
	}
	DGFileDialogUniStrings ()
	{
		Init ();
	}
};

struct DGApplMenuUniStrings {
	GS::UniString	servicesText;				// Services menu text for application menu
	GS::UniString	hideText;					// Hide menuitem text for application menu
	GS::UniString	hideothersText;				// Hide Others menuitem text for application menu
	GS::UniString	showAllText;				// Show All menuitem text for application menu
	GS::UniString	quitText;					// Quit menuitem text for application menu
	GS::UniString	helpMenuText;				// Help menu text

	void Init (void)
	{
		servicesText.Clear ();
		hideText.Clear ();
		hideothersText.Clear ();
		showAllText.Clear ();
		quitText.Clear ();
		helpMenuText.Clear ();
	}
	DGApplMenuUniStrings ()
	{
		Init ();
	}
};

struct DGColorPanelUniStrings {
	GS::UniString	okText;						// OK button text for Color panel
	GS::UniString	cancelText;					// Cancel button text for Color panel

	void Init (void)
	{
		okText.Clear ();
		cancelText.Clear ();
	}
	DGColorPanelUniStrings ()
	{
		Init ();
	}
};

struct DGNumericInputLimitHandlers {
	DG::NumericInputLimitHandler* realHandler;
	DG::NumericInputLimitHandler* angleHandler;
	DG::NumericInputLimitHandler* polarAngleHandler;
	DG::NumericInputLimitHandler* lengthHandler;
	DG::NumericInputLimitHandler* areaHandler;
	DG::NumericInputLimitHandler* volumeHandler;
	DG::NumericInputLimitHandler* mmPointHandler;
	DG::NumericInputLimitHandler* mmInchHandler;

	void Init (void)
	{
		realHandler			= nullptr;
		angleHandler		= nullptr;
		polarAngleHandler	= nullptr;
		lengthHandler		= nullptr;
		areaHandler			= nullptr;
		volumeHandler		= nullptr;
		mmPointHandler		= nullptr;
		mmInchHandler		= nullptr;
	}
	DGNumericInputLimitHandlers ()
	{
		Init ();
	}
};

struct DGInitData {
	UChar							mainVersion;			// Main version number of DG DLL (0-9)
	UChar							subVersion;				// Sub version number of DG DLL (0-9)
	UChar							revision;				// Revision number of DG DLL (0-9)
	Int8							filler1;				//
	GS::UniString					northSymb;				// North symbol for angle edit text
	GS::UniString					southSymb;				// South symbol for angle edit text
	GS::UniString					eastSymb;				// East symbol for angle edit text
	GS::UniString					westSymb;				// West symbol for angle edit text
	GS::UniString					gradSymb;				// Grad symbol for angle edit text
	GS::UniString					radSymb;				// Radian symbol for angle edit text
	GS::UniString					degSymb;				// Degree #1 symbol for angle edit text
	GS::UniString					degreeSymb;				// Degree #2 symbol for angle edit text
	GS::UniString					minuteSymb;				// Minute symbol for angle edit text
	GS::UniString					secondSymb;				// Second symbol for angle edit text
	double							internalUnit;			// Application's internal unit in mm
	IO::Location*					pPrefsFileLoc;			// Dialog positions prefs file    (MAC only)
	IO::Location*					cacheFolderParentLoc;	// Web browser control cache folder parent location
	GSResModule						contextMenuResModule;	// Context Menu Resource Module
	short							contextMenuStrListId;	// Edittext, Drag & drop and Help context strings list ID
	GSResModule						applIconResModule;		// Application's icon resource module (WIN only)
	short							applIconId;				// Application's icon ID          (WIN only)
	UInt32							applLanguageId;			// Application's language ID	  (WIN only)
	Int32							fontCharSet;			// Character set of dialog fonts  (WIN only)
	Int32							largeFontSize;			// Size of the large dialog font  (WIN only)
	Int32							smallFontSize;			// Size of the small dialog font  (WIN only)
	Int32							xSmallFontSize;			// Size of the extra small font   (WIN only)
	Int32							largeBoldFontWeight;	// Weight of the Bold large font  (WIN only)
	Int32							smallBoldFontWeight;	// Weight of the Bold small font  (WIN only)
	Int32							xSmallFontWeight;		// Weight of the extra small font (WIN only)
	GS::UniString					largeFontName;			// Name of the large dialog font  (WIN only)
	GS::UniString					smallFontName;			// Name of the small dialog font  (WIN only)
	GS::UniString					xSmallFontName;			// Name of the extra small font   (WIN only)
	GS::UniString					closeMenuText;			// Close system menu item text    (WIN only)
	GS::UniString					nextMenuText;			// Next system menu item text     (WIN only)
	GS::UniString					errorText;				// Title of Error alert           (WIN only)
	GS::UniString					warningText;			// Title of Warning alert         (WIN only)
	GS::UniString					infoText;				// Title of Information alert     (WIN only)
	GS::UniString					applRegKey;				// Application's registry key     (WIN only)
	GS::UniString					allFilesText;			// 'All Files' text for file dialog
	GS::UniString					allTypesText;			// 'All Types' text for shortcut printing
	DGMenuChoiceDialogUniStrings	menuChoiceTexts;		// menu choice dialog texts
	GSResModule						fileNameAlertResModule;	// Alert Resource Module
	short							fileNameAlertId;		// Alert ID for too long (WIN) / invalid (MAC) filename
	DGRulerUniStrings				rulerStrings;			// Special strings for the ruler
	GS::UniString					charPaletteName;		// Name of Character Palette	  (MAC only)
	GS::Int32						rtlOrder;				// Right to Left order (arabic, hebrew system) 0 or 1
	GS::UniString					openingBracket;			// Opening Bracket for shortcut hint (with space)
	GS::UniString					closingBracket;			// Closing Bracket for shortcut hint
	DGFileDialogUniStrings			fileDialogStrings;		// Special strings for the file dialog
	DGApplMenuUniStrings			applMenuStrings;		// Special strings for application menu		(MAC only)
	DGColorPanelUniStrings			colorPanelStrings;		// Special strings for Color Panel			(MAC only)
	GS::UniString					fileTypeTitleOpen;		// Title of file type popup in open dialogs	(MAC only)
	GS::UniString					fileTypeTitleSave;		// Title of file type popup in save dialogs	(MAC only)
	GS::UniString					chooseButtonTitle;		// default title of Ok Button and default window title of folder selection dialog	(MAC only)
	GS::UniString					fontCollections;		// Title of font popup's collection item	(MAC only)
	DGNumericInputLimitHandlers		numericInputLimitHandlers;  // Handlers for limit the number inputs
	bool							externalCefInit;		// Can CEF initialization be ignored? (For DGUnitTest)


	void Init (void)
	{
		mainVersion = 0;
		subVersion = 0;
		revision = 0;
		filler1 = 0;

		northSymb.Clear ();
		southSymb.Clear ();
		eastSymb.Clear ();
		westSymb.Clear ();
		gradSymb.Clear ();
		radSymb.Clear ();
		degSymb.Clear ();
		degreeSymb.Clear ();
		minuteSymb.Clear ();
		secondSymb.Clear ();

		internalUnit = 0.0;
		pPrefsFileLoc = nullptr;
		cacheFolderParentLoc = nullptr;
		contextMenuResModule = InvalidResModule;
		contextMenuStrListId = 0;
		applIconResModule = InvalidResModule;
		applIconId = DG_NO_ICON;
		applLanguageId = 0;
		fontCharSet = 0;
		largeFontSize = 0;
		smallFontSize = 0;
		xSmallFontSize = 0;
		largeBoldFontWeight = 0;
		smallBoldFontWeight = 0;
		xSmallFontWeight = 0;
		largeFontName.Clear ();
		smallFontName.Clear ();
		xSmallFontName.Clear ();

		closeMenuText.Clear ();
		nextMenuText.Clear ();
		errorText.Clear ();
		warningText.Clear ();
		infoText.Clear ();
		applRegKey.Clear ();
		allFilesText.Clear ();
		allTypesText.Clear ();
		menuChoiceTexts.Init ();

		fileNameAlertResModule = InvalidResModule;
		fileNameAlertId = 0;

		rulerStrings.Init ();
		charPaletteName.Clear ();
		rtlOrder = 0;
		openingBracket.Clear ();
		closingBracket.Clear ();
		fileDialogStrings.Init ();
		applMenuStrings.Init ();
		colorPanelStrings.Init ();
		fileTypeTitleOpen.Clear ();
		fileTypeTitleSave.Clear ();
		chooseButtonTitle.Clear ();
		fontCollections.Clear ();

		externalCefInit = false;
	}

	DGInitData ()
	{
		Init ();
	}
};

//struct DGFontData {
//	float			angle;					// Angle of base line from X-axis in radian
//	short			size;					// Character size of the font
//	UChar			bold;					// Bold flag (0 / 1)
//	UChar			italic;					// Italic flag (0 / 1)
//	UChar			underline;				// Underline flag (0 / 1)
//	UChar			outline;				// Outline flag (0 / 1)           (MAC only)
//	UChar			shadow;					// Shadow flag (0 / 1)            (MAC only)
//	UChar			strikeOut;				// Strikeout flag (0 / 1)         (WIN only)
//	UChar			charSet;				// Character set of the font      (WIN only)
//	Int8			filler[3];				//
//	Int8			faceName[256];			// Facename of the font
//};


class DGTEFontData;		// see DGTEFontData.hpp

struct DGListTabData {
	short			begPos;					// Tab field left position relative to the client rect
	short			endPos;					// Tab field right position relative to the client rect
	short			justFlag;				// DG_IS_LEFT, DG_IS_CENTER, DG_IS_RIGHT
	short			truncFlag;				// DG_IS_NOTRUNC, DG_IS_TRUNCEND, DG_IS_TRUNCMIDDLE
	bool			hasSeparator;			// There is a vertical separator on the right side of the fab field
	bool			disabled;				// Is the fab field disabled or enabled
};

struct DGMousePosData
{
	short			dialId;					// Id of the dialog above which the mouse currently is
	short			itemId;					// Id of the item above which the mouse currently is
	short			left;					// Dialog or item client rect left position
	short			top;					// Dialog or item client rect top position
	short			right;					// Dialog or item client rect right position
	short			bottom;					// Dialog or item client rect bottom position
	short			xPos;					// Horizontal mouse position relative to the client rect
	short			yPos;					// Vertical mouse position relative to the client rect
	short			keyFlag;				// DG_MOD_COMMAND, DG_MOD_OPTION, DG_MOD_SHIFT
	short			buttonFlag;				// DG_BUTTON_LEFT, DG_BUTTON_RIGHT, DG_BUTTON_WHEEL
	DG::NativeUnit	nativeXPos;				// Mouse position in the native coordinate system
	DG::NativeUnit	nativeYPos;				// Mouse position in the native coordinate system

	DGMousePosData ()
	{
		Clear ();
	}

	void	Clear (void)
	{
		dialId = 0;
		itemId = 0;
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
		xPos = 0;
		yPos = 0;
		keyFlag = 0;
		buttonFlag = 0;
		nativeXPos = DG::NativeUnit (0);
		nativeYPos = DG::NativeUnit (0);
	}
};

struct DGUnitData {
	double			north;
	Int32			lengthType;
	Int32			lengthDigits;
	Int32			lengthFractions;
	Int32			areaType;
	Int32			areaDigits;
	Int32			volumeType;
	Int32			volumeDigits;
	Int32			nonUnitDigits;
	Int32			angleType;
	Int32			angleDigits;
	Int32			angleAccuracy;
	Int32			polarAngleType;
	Int32			polarAngleDigits;
	Int32			polarAngleAccuracy;
	bool			show0whole;
	bool			show0inch;

	struct SAMUnits {
		short	ptStiffnessType;
		short	ptStiffnessDigits;
		short	prStiffnessType;
		short	prStiffnessDigits;
		short	ltStiffnessType;
		short	ltStiffnessDigits;
		short	lrStiffnessType;
		short	lrStiffnessDigits;
		short	stStiffnessType;
		short	stStiffnessDigits;
		short	trForceType;
		short	trForceDigits;
		short	rrMomentType;
		short	rrMomentDigits;
		short	plForceType;
		short	plForceDigits;
		short	plMomentType;
		short	plMomentDigits;
		short	elForceType;
		short	elForceDigits;
		short	elMomentType;
		short	elMomentDigits;
		short	slForceType;
		short	slForceDigits;
	} samUnits;
};

struct DGCharRange {
	Int32			startPos;				// Start position
	Int32			endPos;					// End position
};

struct DGTabulatorItem {
	short			tabType;
	double			tabPosition;
};

struct DGBrowserClickItemMsgData {
	Int32			browserItemId;			// The Browser item identifier above the help is requested
	short			itemLeft;				// TabBar control relative logical coordinate
	short			itemTop;				// TabBar control relative logical coordinate
	short			itemRight;				// TabBar control relative logical coordinate
	short			itemBottom;				// TabBar control relative logical coordinate
	short			clickPosX;				// TabBar control relative logical coordinate
	short			clickPosY;				// TabBar control relative logical coordinate
	short			keyFlag;
	bool			isCloseClicked;
};

struct DGTestData {
	short		testFlags;					// GSAutoTester test On/Off
	char*		bufferAddr;					// Output buffer address allocated by tester
};

struct DGUCItemData
{
	GSResModule		locResModule;
	GSResModule		fixResModule;
	short			ucType;
#if defined (WINDOWS)
	short			dialId;
	short			item;
	short			frameType;
#endif

	void	Init (void)
	{
		locResModule = InvalidResModule;
		fixResModule = InvalidResModule;
#if defined (WINDOWS)
		dialId		= 0;
		item		= 0;
		frameType	= DG_BF_FRAME;
#endif
	}

	DGUCItemData ()
	{
		Init ();
	}
};

enum AppearanceType {
	LightAppearance = 0,
	DarkAppearance
};

namespace DG {

class DG_DLL_EXPORT OnlyUpdateGuard
{
	bool onlyUpdate = false;
public:
	OnlyUpdateGuard (bool onlyUpdateIn);
	~OnlyUpdateGuard ();
};

}

typedef	short (DGCALLBACK *DGDialCallBack) (short message, short dialId, short itemId, DGUserData userData, DGMessageData msgData);

#define DG_HELPCENTER_DEFAULT       0
#define DG_HELPCENTER_DYNAMICLOADER 1
#define DG_HELPCENTER_ONLY_LOCAL    2
#define DG_HELPCENTER_ONLY_WEB      3
#define DG_HELPCENTER_NONE          4

typedef	short (DGCALLBACK *DGHelpCenterCallBack) (const GS::UniString* helpURL, const GS::UniString* helpAnchor);

typedef std::function<void (void)>	DGIdleCallBack;


// --- Exported functions ----------------------------------------------------------------------------------------------

// --- General functions and utilities ---------------------------------------------------------------------------------

DG_DLL_EXPORT bool CCALL		DGInit (const DGInitData* initData);

#ifdef macintosh
DG_DLL_EXPORT void CCALL		DGDetectWindowLeaks (void);

DG_DLL_EXPORT GS::UniString  CCALL DGGetFullPathNameOfBaseApplication (void);
#endif

DG_DLL_EXPORT void CCALL		DGExit (void);


DG_DLL_EXPORT short CCALL		DGGetMousePosition (short dialId, DGMousePosData* mPosData);

DG_DLL_EXPORT void CCALL		DGImAlive (void);

DG_DLL_EXPORT GSResModule CCALL GetDGResourceModule (void);

DG_DLL_EXPORT GS::uchar_t CCALL DGGetLanguageDependentDecimalChar (void);

DG_DLL_EXPORT void CCALL		DGGetAngleSymbols (GS::UniString& degree, GS::UniString& north, GS::UniString& south, GS::UniString& east, GS::UniString& west);

DG_DLL_EXPORT bool CCALL		UISetCursor (GSResModule cursorResModule, Int32 cursorId);

DG_DLL_EXPORT void CCALL		DGEnableRunnableMessageProcessing (void);

DG_DLL_EXPORT void CCALL		DGDisableRunnableMessageProcessing (void);

DG_DLL_EXPORT bool CCALL		DGIsRunnableMessageProcessingEnabled (void);


DG_DLL_EXPORT void CCALL		DGStoreUserDataToRegistry (const GS::UniString& keyName, const void* data, ULong size);

DG_DLL_EXPORT ULong CCALL		DGRetrieveUserDataFromRegistry (const GS::UniString& keyName, void* data, ULong size);

DG_DLL_EXPORT ULong CCALL		DGRetrieveUserDataFromRegistry (const GS::UniString& keyName, std::nullptr_t);


template <typename T>
ULong DGRetrieveUserDataFromRegistry (const GS::UniString& keyName, T* data)
{
	if constexpr (std::disjunction_v<std::is_void<T>,
									 std::is_same<std::remove_cv_t<T>, wchar_t>,
									 std::is_same<std::remove_cv_t<T>, char>,
									 std::is_same<std::remove_cv_t<T>, unsigned char>,
									 std::is_same<std::remove_cv_t<T>, std::byte>>)
	{
		static_assert (GS::AlwaysFalse<T>, "Missing buffer size argument");
	} else {
		static_assert (std::is_trivially_copyable_v<T>);
		return DGRetrieveUserDataFromRegistry (keyName, data, sizeof (T));
	}
}


DG_DLL_EXPORT bool CCALL		DGPostCommandToApplication (ULong commandIdParam, Int32 developerIdParam, Int32 productIdParam, UIndex multiCmdIndex);


DG_DLL_EXPORT bool CCALL		DGSetTestEnvironment (DGTestData* testData);

DG_DLL_EXPORT void CCALL		DGRegisterIdleCallBack (const DGIdleCallBack& idleCallBack);

DG_DLL_EXPORT void CCALL		DGCallIdleCallBack (void);

DG_DLL_EXPORT bool CCALL		DGIsInModalState (void);

// --- Unit handling and string conversion -----------------------------------------------------------------------------

DG_DLL_EXPORT void CCALL		DGSetUnit (const DGUnitData* uData);

DG_DLL_EXPORT void CCALL		DGGetUnit (DGUnitData* uData);

DG_DLL_EXPORT bool CCALL		DGIsMetricLengthUnit (void);


DG_DLL_EXPORT Int32 CCALL		DGStringToDouble (const GS::UniString& str, double &value, short type);

DG_DLL_EXPORT Int32 CCALL		DGStringToDoubleUnit (const DGUnitData* uData, const GS::UniString& str, double &value, short type);


// --- General help, tooltip and context menu utilities ----------------------------------------------------------------

DG_DLL_EXPORT void CCALL		DGEnableToolTips (void);

DG_DLL_EXPORT void CCALL		DGDisableToolTips (void);

DG_DLL_EXPORT bool CCALL		DGIsToolTipsEnabled (void);


DG_DLL_EXPORT void CCALL		DGRegisterHelpCenter (const DGHelpCenterCallBack hcCallBack);

DG_DLL_EXPORT bool CCALL		DGRegisterAdditionalHelpLocation (Int32 developerId, Int32 localId,
																  const GS::UniString* localHelpPath,
																  const GS::UniString* localHelpFile,
																  const GS::UniString* addonHelpWebAddress,
																  const GS::UniString* tmpPath,
																  const GS::UniString* additionalHelpParameters);

DG_DLL_EXPORT bool CCALL		DGUnregisterAdditionalHelpLocation (Int32 developerId, Int32 localId);

DG_DLL_EXPORT bool CCALL		DGGetDynamicHelpStrings (GSResModule resModule, GSResID resID, short index, GS::UniString* toolTipStr, GS::UniString* anchorStr = nullptr);

DG_DLL_EXPORT bool CCALL		DGDisplayContextHelp (void);

DG_DLL_EXPORT bool CCALL		DGShowContextHelpWithAnchor (Int32 developerId, Int32 localId, const GS::UniString& helpAnchor);

DG_DLL_EXPORT bool CCALL		DGShowOnlineOnlyHelpWithAnchor (Int32 developerId, Int32 localId, const GS::UniString& helpAnchor);

DG_DLL_EXPORT GS::UniString CCALL	DGGetWebHelpQueryUrlWithAnchor (Int32 developerId, Int32 localId, const GS::UniString& helpAnchor);

DG_DLL_EXPORT bool CCALL		DGIsURLReachable (const GS::UniString& url);

// --- Drag and Drop functions -----------------------------------------------------------------------------------------

DG_DLL_EXPORT bool CCALL		DGDragHasFormat (DGDragFormat format);

DG_DLL_EXPORT bool CCALL		DGDragSetData (DGDragFormat format, void* data, ULong size, short scope);

DG_DLL_EXPORT bool CCALL		DGDragSetDelayedData (DGDragFormat format, short scope);

DG_DLL_EXPORT bool CCALL		DGDragGetData (DGDragFormat format, void* data, ULong* size);

DG_DLL_EXPORT const void* CCALL	DGDragGetDataPtr (DGDragFormat format, ULong* dataSize);

DG_DLL_EXPORT bool CCALL		DGDragGetFileData (DGDragFormat format, const GS::uchar_t* folderPath, void* data, ULong* size);

DG_DLL_EXPORT bool CCALL		DGDragModifyBaseFormat (DGDragFormat format, short scope);

DG_DLL_EXPORT short CCALL		DGDragGetSourceDialog (void);

DG_DLL_EXPORT short CCALL		DGDragGetSourceItem (void);

DG_DLL_EXPORT ULong CCALL		DGDragGetItemCount (void);

DG_DLL_EXPORT Int32 CCALL		DGDragGetTreeViewItem (ULong index);

DG_DLL_EXPORT short CCALL		DGDragGetListBoxItem (ULong index);

DG_DLL_EXPORT short CCALL		DGDragGetListViewItem (ULong index);


// --- Alert handling --------------------------------------------------------------------------------------------------

DG_DLL_EXPORT short CCALL		DGResAlert (GSResModule resModule, short alertId);

DG_DLL_EXPORT short CCALL		DGResAlertParam (GSResModule resModule, short alertId,
												   const GS::UniString& paramText1, const GS::UniString& paramText2 = GS::UniString(),
												   const GS::UniString& paramText3 = GS::UniString(), const GS::UniString& paramText4 = GS::UniString());
DG_DLL_EXPORT short CCALL		DGAlert (short alertType,
										 const GS::UniString& titleText = GS::UniString(), const GS::UniString& largeText = GS::UniString(),
										 const GS::UniString& smallText = GS::UniString(), const GS::UniString& button1Text = GS::UniString(),
										 const GS::UniString& button2Text = GS::UniString(), const GS::UniString& button3Text = GS::UniString());


// --- Dialog Functions ------------------------------------------------------------------------------------------------

DG_DLL_EXPORT void CCALL		DGSetDialogResourceModules (short dialId, GSResModule dialResModule, GSResModule dialIconResModule);

DG_DLL_EXPORT void CCALL		DGSetDialogResourceModule (short dialId, GSResModule resModule);

DG_DLL_EXPORT GSResModule CCALL DGGetDialogResourceModule (short dialId);

DG_DLL_EXPORT GSResModule CCALL DGGetDialogIconResourceModule (short dialId);


DG_DLL_EXPORT void CCALL		DGResetDialogRectangles (void);


DG_DLL_EXPORT void CCALL		DGEnableAutoClose (void);

DG_DLL_EXPORT void CCALL		DGDisableAutoClose (void);

DG_DLL_EXPORT void CCALL		DGSetAutoCloseState (Int32 state);


DG_DLL_EXPORT bool CCALL		DGIsAutoCloseEnabled (void);

DG_DLL_EXPORT void CCALL		DGSetAutoCloseDelay (ULong closeDelay);

DG_DLL_EXPORT ULong CCALL		DGGetAutoCloseDelay (void);


DG_DLL_EXPORT void CCALL		DGSetEditUpdateDelay (ULong delay);

DG_DLL_EXPORT ULong CCALL		DGGetEditUpdateDelay (void);

DG_DLL_EXPORT void CCALL		DGFlushDelayedEditItemChange (void);


DG_DLL_EXPORT short CCALL		DGGetColor (const GS::UniString& title, UShort* red, UShort* green, UShort* blue);


DG_DLL_EXPORT short CCALL		DGModalDialog (GSResModule dialResModule, short resId, GSResModule dialIconResModule, const DGDialCallBack dCallBack, DGUserData userData);

DG_DLL_EXPORT short CCALL		DGBlankModalDialog (short hSize, short vSize, short growFlag, short captionFlag, short frameFlag,
													const DGDialCallBack dCallBack, DGUserData userData);

DG_DLL_EXPORT void CCALL		DGAbortModalDialog (short dialId);


DG_DLL_EXPORT short CCALL		DGModelessInit (GSResModule dialResModule, short resId, GSResModule dialIconResModule, const DGDialCallBack dCallBack, DGUserData userData, short show);

DG_DLL_EXPORT bool CCALL		DGModelessHandler (const void* sysMessage, bool onlyUpdate);

DG_DLL_EXPORT void CCALL		DGModelessClose (short dialId);

DG_DLL_EXPORT short CCALL		DGGetModelessToClose (void);

DG_DLL_EXPORT void CCALL		DGSetOnlyUpdateFlag (bool onlyUpdate);

DG_DLL_EXPORT bool CCALL		DGGetOnlyUpdateFlag ();


DG_DLL_EXPORT short CCALL		DGCreateModelessDialog (GSResModule dialResModule, short resId, GSResModule dialIconResModule, const DGDialCallBack dCallBack, DGUserData userData);

DG_DLL_EXPORT short CCALL		DGCreateBlankModelessDialog (short hSize, short vSize, short growFlag, short closeFlag,
															 short minimizeFlag, short maximizeFlag, short captionFlag,
															 short frameFlag, const DGDialCallBack dCallBack, DGUserData userData);

DG_DLL_EXPORT void CCALL		DGDestroyModelessDialog (short dialId);


DG_DLL_EXPORT short CCALL		DGCreatePalette (GSResModule dialResModule, short resId, GSResModule dialIconResModule, const DGDialCallBack dCallBack, DGUserData userData);

DG_DLL_EXPORT short CCALL		DGCreateDockablePalette (GSResModule dialResModule, short resId, GSResModule dialIconResModule, const DGDialCallBack dCallBack, DGUserData userData, const GS::Guid& guid);

DG_DLL_EXPORT short CCALL		DGCreateBlankPalette (short hSize, short vSize, short growFlag, short closeFlag, short captionFlag,
													  short frameFlag, const DGDialCallBack dCallBack, DGUserData userData);

DG_DLL_EXPORT short CCALL		DGCreateBlankDockablePalette (short hSize, short vSize, short growFlag, short closeFlag, short captionFlag,
															  short frameFlag, const DGDialCallBack dCallBack, DGUserData userData, const GS::Guid& guid);

DG_DLL_EXPORT void CCALL		DGDestroyPalette (short dialId);


DG_DLL_EXPORT short CCALL		DGDisablePaletteDock (const GS::Guid& paletteGuid, short orientationFlag);

DG_DLL_EXPORT void CCALL		DGSetPaletteDockState (const GS::Guid& paletteGuid, bool isDocked);

DG_DLL_EXPORT bool CCALL		DGIsPaletteDocked (const GS::Guid& paletteGuid);

DG_DLL_EXPORT short CCALL		DGGetPaletteCaptionType (const GS::Guid& paletteGuid);

DG_DLL_EXPORT void CCALL		DGGetDialogGuid (short dialId, GS::Guid* guid);


DG_DLL_EXPORT void CCALL		DGBeginProcessEvents (short dialId);

DG_DLL_EXPORT void CCALL		DGEndProcessEvents (short dialId);


DG_DLL_EXPORT short CCALL		DGSendUserMessage (short dialId, short itemId, DG::EventArg& msgData);


DG_DLL_EXPORT short CCALL		DGGetDialogType (short dialId);

DG_DLL_EXPORT short CCALL		DGIsDialogOpen (short dialId);

DG_DLL_EXPORT short CCALL		DGIsDialIdExist (short dialId);


DG_DLL_EXPORT short CCALL		DGGetDialogResourceId (short dialId);

DG_DLL_EXPORT void* CCALL		DGGetDialogWindow (short dialId);

DG_DLL_EXPORT short CCALL		DGGetDialogWindowId (const void* dialWindow);


DG_DLL_EXPORT short CCALL		DGGetDialogId (short refDialId, short dialFlag, short dialType);

DG_DLL_EXPORT short CCALL		DGGetDialogIds (short refDialId, bool visibleOnly, bool reversed, short dialType, short* dialIds);

DG_DLL_EXPORT void CCALL		DGSetDialogZPosition (short dialId, short refDialId);

DG_DLL_EXPORT bool CCALL		DGGetDialItemVisibilityMask (short dialId);


DG_DLL_EXPORT void* CCALL		DGGetActiveWindow (void);


DG_DLL_EXPORT void CCALL		DGSetNextModalParent (const void* parentWindow);

DG_DLL_EXPORT void* CCALL		DGGetNextModalParent (void);


DG_DLL_EXPORT void CCALL		DGShowModelessDialog (short dialId, short refDialId);

DG_DLL_EXPORT void CCALL		DGHideModelessDialog (short dialId);

DG_DLL_EXPORT short CCALL		DGIsModelessDialogVisible (short dialId);


DG_DLL_EXPORT void CCALL		DGActivateModelessDialog (short dialId);

DG_DLL_EXPORT short CCALL		DGIsModelessDialogActive (short dialId);

DG_DLL_EXPORT void CCALL		DGSetModelessDialogStatus (short dialId, short dialStatus);

DG_DLL_EXPORT short CCALL		DGGetModelessDialogStatus (short dialId);

DG_DLL_EXPORT void CCALL		DGSetModelessDialogState (short dialId, short dialState, bool beforeDock = false);

DG_DLL_EXPORT short CCALL		DGGetModelessDialogState (short dialId);

DG_DLL_EXPORT void CCALL		DGSetModelessDialogDockState (short dialId, short dialState);

DG_DLL_EXPORT short CCALL		DGGetModelessDialogDockState (short dialId);

#ifdef macintosh
DG_DLL_EXPORT void CCALL		DGModelessDialogUpdateAllTrackingAreas ();
#endif

DG_DLL_EXPORT double CCALL		DGGetFrameWindowScaleFactor (void);	// Scale factor for the application frame


DG_DLL_EXPORT short CCALL		DGRegisterHotKey (short dialId, short modifier, short keyCode);

DG_DLL_EXPORT void CCALL		DGUnregisterHotKey (short dialId, short hotKeyId);

DG_DLL_EXPORT void CCALL		DGEnableHotKeys (short dialId);

DG_DLL_EXPORT void CCALL		DGDisableHotKeys (short dialId);


DG_DLL_EXPORT void CCALL		DGCenterDialog (short dialId);

DG_DLL_EXPORT void CCALL		DGMoveDialog (short dialId, short hDisp, short vDisp);
DG_DLL_EXPORT void CCALL		DGMoveDialog (short dialId, const DG::NativeUnit& hDisp, const DG::NativeUnit& vDisp);


DG_DLL_EXPORT void CCALL		DGSetDialogClientPosition (short dialId, short posType, const DG::NativeUnit& hPos, const DG::NativeUnit& vPos);
DG_DLL_EXPORT void CCALL		DGGetDialogClientPosition (short dialId, short rectType, short posType, DG::NativeUnit* hPos, DG::NativeUnit* vPos); // posType: DG_GLOBAL or DG_SCREEN, rectType: DG_CLIENT or DG_RESTCLIENT

DG_DLL_EXPORT void CCALL		DGSetDialogFramePosition (short dialId, short posType, const DG::NativeUnit& hPos, const DG::NativeUnit& vPos); // posType: DG_GLOBAL or DG_SCREEN
DG_DLL_EXPORT void CCALL		DGGetDialogFramePosition (short dialId, short rectType, short posType, DG::NativeUnit* hPos, DG::NativeUnit* vPos); // posType: DG_GLOBAL vagy DG_SCREEN, rectType: DG_FRAME vagy DG_RESTFRAME


DG_DLL_EXPORT void CCALL		DGSetDialogGrowType (short dialId, short growType);

DG_DLL_EXPORT short CCALL		DGGetDialogGrowType (short dialId);


DG_DLL_EXPORT void CCALL		DGGrowDialog (short dialId, short hGrow, short vGrow);

DG_DLL_EXPORT void CCALL		DGSetDialogClientSize (short dialId, short hSize, short vSize, short fixPoint, bool keepOld);
DG_DLL_EXPORT void CCALL		DGSetDialogClientSize (short dialId, const DG::NativeUnit& hSize, const DG::NativeUnit& vSize, short fixPoint, bool keepOld);

DG_DLL_EXPORT void CCALL		DGGetDialogClientSize (GSResModule dialResModule, short dialId, short rectType, short* hSize, short* vSize);
DG_DLL_EXPORT void CCALL		DGGetDialogClientSize (GSResModule dialResModule, short dialId, short rectType, DG::NativeUnit* hSize, DG::NativeUnit* vSize);

DG_DLL_EXPORT void CCALL		DGSetDialogClientMinSize (short dialId, short hMinSize, short vMinSize);
DG_DLL_EXPORT void CCALL		DGSetDialogClientMinSize (short dialId, const DG::NativeUnit& hMinSize, const DG::NativeUnit& vMinSize);

DG_DLL_EXPORT void CCALL		DGGetDialogClientMinSize (GSResModule dialResModule, short dialId, short* hMinSize, short* vMinSize);
DG_DLL_EXPORT void CCALL		DGGetDialogClientMinSize (GSResModule dialResModule, short dialId, DG::NativeUnit* hMinSize, DG::NativeUnit* vMinSize);

DG_DLL_EXPORT void CCALL		DGSetDialogFrameSize (short dialId, const DG::NativeUnit& hSize, const DG::NativeUnit& vSize, short fixPoint, bool keepOld);
DG_DLL_EXPORT void CCALL		DGGetDialogFrameSize (GSResModule dialResModule, short dialId, short rectType, DG::NativeUnit* hSize, DG::NativeUnit* vSize);

DG_DLL_EXPORT void CCALL		DGSetDialogFrameMinSize (short dialId, const DG::NativeUnit& hMinSize, const DG::NativeUnit& vMinSize);
DG_DLL_EXPORT void CCALL		DGGetDialogFrameMinSize (GSResModule dialResModule, short dialId, DG::NativeUnit* hMinSize, DG::NativeUnit* vMinSize);

DG_DLL_EXPORT void CCALL		DGGetDialogClientOffset (GSResModule dialResModule, short dialId, DG::NativeUnit* hOffset, DG::NativeUnit* vOffset);


DG_DLL_EXPORT void CCALL		DGSetDialogTitle (short dialId, const GS::UniString& title);

DG_DLL_EXPORT void CCALL		DGSetDialogIcon (short dialId, const DG::Icon& icon);

DG_DLL_EXPORT void CCALL		DGSetDialogUserData (short dialId, DGUserData userData);

DG_DLL_EXPORT DGUserData CCALL	DGGetDialogUserData (short dialId);


DG_DLL_EXPORT void CCALL		DGSetDialogData (short dialId, void* dialData);

DG_DLL_EXPORT void* CCALL		DGGetDialogData (short dialId);


DG_DLL_EXPORT bool CCALL		DGGetDialogMDID (short dialId, UInt32* developerId, UInt32* localId);


DG_DLL_EXPORT void CCALL		DGEnableNormalUpdate (short dialId);

DG_DLL_EXPORT void CCALL		DGDisableNormalUpdate (short dialId);


DG_DLL_EXPORT void CCALL		DGSetDialogPopupStyle (short dialId);

DG_DLL_EXPORT bool CCALL		DGHasDialogPopupStyle (short dialId);


DG_DLL_EXPORT void CCALL		DGGrowBoxEnable (short dialId);

DG_DLL_EXPORT void CCALL		DGGrowBoxDisable (short dialId);

DG_DLL_EXPORT bool CCALL		DGGrowBoxIsEnabled (short dialId);


DG_DLL_EXPORT void CCALL		DGGrowBoxSetSize (short dialId, short size);

DG_DLL_EXPORT short CCALL		DGGrowBoxGetSize (short dialId);


DG_DLL_EXPORT void CCALL		DGGrowBoxSetForm (short dialId, short form);

DG_DLL_EXPORT short CCALL		DGGrowBoxGetForm (short dialId);


DG_DLL_EXPORT void CCALL		DGEnableDialogDraw (short dialId);

DG_DLL_EXPORT void CCALL		DGDisableDialogDraw (short dialId);

DG_DLL_EXPORT void CCALL		DGRedrawDialog (short dialId);


DG_DLL_EXPORT NewDisplay::NativeImage CCALL DGCaptureDialogToNativeImage (short dialId, bool withFrame);


DG_DLL_EXPORT AppearanceType CCALL	DGGetDialogAppearanceType (short dialId);


// --- Tab page functions ----------------------------------------------------------------------------------------------

DG_DLL_EXPORT short CCALL		DGCreateTabPage (short mainDialId, short tabControlId, short tabItem, GSResModule dialResModule, short resId, GSResModule dialIconResModule);

DG_DLL_EXPORT short CCALL		DGCreateBlankTabPage (short mainDialId, short tabControlId, short tabItem, short hSize, short vSize);

DG_DLL_EXPORT void CCALL		DGDestroyTabPage (short dialId);


DG_DLL_EXPORT short CCALL		DGGetTabPageParentId (short dialId);


DG_DLL_EXPORT void CCALL		DGSetTabPageGrowType (short dialId, short growType);

DG_DLL_EXPORT short CCALL		DGGetTabPageGrowType (short dialId);

DG_DLL_EXPORT void CCALL		DGSetTabPageFixPoint (short dialId, short fixPoint);

DG_DLL_EXPORT short CCALL		DGGetTabPageFixPoint (short dialId);


DG_DLL_EXPORT void CCALL		DGSetTabPageSize (short dialId, short hSize, short vSize);

DG_DLL_EXPORT void CCALL		DGGetTabPageSize (short dialId, short* hSize, short* vSize);

DG_DLL_EXPORT void CCALL		DGGetTabPageRect (short dialId, short* left, short* top, short* right, short* bottom);

DG_DLL_EXPORT void CCALL		DGSetTabPageMinSize (short dialId, short hMinSize, short vMinSize);

DG_DLL_EXPORT void CCALL		DGGetTabPageMinSize (GSResModule dialResModule, short dialId, short* hMinSize, short* vMinSize);


// --- Dialog item functions -------------------------------------------------------------------------------------------

DG_DLL_EXPORT short CCALL		DGAppendDialogItem (short dialId, short itemType, short itemSubType, short itemData,
													 short hPos, short vPos, short hSize, short vSize);

DG_DLL_EXPORT void CCALL		DGRemoveDialogItem (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGRemoveDialogItems (short dialId, short startItem);

DG_DLL_EXPORT short CCALL		DGGetDialogItemCount (short dialId);


DG_DLL_EXPORT void CCALL		DGSetDefaultOrCancelButton (short dialId, short item, bool asDefault);


DG_DLL_EXPORT void CCALL		DGEnableMessage (short dialId, short item, short message, short modifier = DG_EMM_NONE);


DG_DLL_EXPORT void CCALL		DGEnableItem (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGDisableItem (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGSetItemEnable (short dialId, short item, Int32 isEnabled);

DG_DLL_EXPORT bool CCALL		DGIsItemEnabled (short dialId, short item);


DG_DLL_EXPORT void CCALL		DGShowItem (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGHideItem (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGSetItemVisible (short dialId, short item, Int32 isVisible);

DG_DLL_EXPORT short CCALL		DGIsItemVisible (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGFlashItem (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGSetItemVisibilityMask (short dialId, bool mask);


DG_DLL_EXPORT void CCALL		DGMoveItem (short dialId, short item, short hDisp, short vDisp);

DG_DLL_EXPORT void CCALL		DGGrowItem (short dialId, short item, short hGrow, short vGrow);

DG_DLL_EXPORT void CCALL		DGMoveGrowItem (short dialId, short item, short hDisp, short vDisp, short hGrow, short vGrow);

DG_DLL_EXPORT void CCALL		DGBeginMoveGrowItems (short dialId);

DG_DLL_EXPORT void CCALL		DGEndMoveGrowItems (short dialId);


DG_DLL_EXPORT void CCALL		DGGetItemRect (short dialId, short item, short* left, short* top, short* right, short* bottom);

DG_DLL_EXPORT void CCALL		DGInvalidateItem (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGRedrawItem (short dialId, short item);


DG_DLL_EXPORT void CCALL		DGSetItemText (short dialId, short item, const GS::UniString& text);

DG_DLL_EXPORT void CCALL		DGSetItemDescription (short dialId, short itemId, const GS::UniString& description);

DG_DLL_EXPORT void CCALL		DGCatItemText (short dialId, short item, const GS::UniString& text);

DG_DLL_EXPORT void CCALL		DGSetItemUniText (short dialId, short item, const GS::uchar_t* text);

DG_DLL_EXPORT void CCALL		DGCatItemUniText (short dialId, short item, const GS::uchar_t* text);

DG_DLL_EXPORT Int32 CCALL		DGGetItemUniText (short dialId, short item, GS::uchar_t* text, Int32 size, short eolType);


DG_DLL_EXPORT void CCALL		DGSetItemTextColor (short dialId, short item, UShort red, UShort green, UShort blue);

DG_DLL_EXPORT bool CCALL		DGGetItemTextColor (short dialId, short item, UShort* red, UShort* green, UShort* blue);

DG_DLL_EXPORT void CCALL		DGSetItemBackgroundColor (short dialId, short item, UShort red, UShort green, UShort blue);

DG_DLL_EXPORT bool CCALL		DGGetItemBackgroundColor (short dialId, short item, UShort* red, UShort* green, UShort* blue);

DG_DLL_EXPORT void CCALL		DGResetDefaultTextColor (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGResetDefaultBackgroundColor (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGSetItemImage (short dialId, short item, const DG::Image& image);

DG_DLL_EXPORT void CCALL		DGSetItemMinLong (short dialId, short item, Int32 value);

DG_DLL_EXPORT void CCALL		DGSetItemMaxLong (short dialId, short item, Int32 value);

DG_DLL_EXPORT void CCALL		DGSetItemValLong (short dialId, short item, Int32 value);

DG_DLL_EXPORT Int32 CCALL		DGGetItemMinLong (short dialId, short item);

DG_DLL_EXPORT Int32 CCALL		DGGetItemMaxLong (short dialId, short item);

DG_DLL_EXPORT Int32 CCALL		DGGetItemValLong (short dialId, short item);


DG_DLL_EXPORT void CCALL		DGSetItemMinDouble (short dialId, short item, double value);

DG_DLL_EXPORT void CCALL		DGSetItemMaxDouble (short dialId, short item, double value);

DG_DLL_EXPORT void CCALL		DGSetItemValDouble (short dialId, short item, double value);

DG_DLL_EXPORT double CCALL		DGGetItemMinDouble (short dialId, short item);

DG_DLL_EXPORT double CCALL		DGGetItemMaxDouble (short dialId, short item);

DG_DLL_EXPORT double CCALL		DGGetItemValDouble (short dialId, short item);


DG_DLL_EXPORT short CCALL		DGModified (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGResetModified (short dialId, short item);


DG_DLL_EXPORT void CCALL		DGSetItemFont (short dialId, short item, short fontType);

DG_DLL_EXPORT short CCALL		DGGetItemFont (short dialId, short item);

DG_DLL_EXPORT void				DGFontTypeToNameAndSize (short fontSize, GS::UniString* name, short* size);


DG_DLL_EXPORT void CCALL		DGSetFocus (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGGetFocus (short dialId, short* focusDial, short* focusItem);

DG_DLL_EXPORT void CCALL		DGGetRealFocus (short& focusDial, short& focusItem);


DG_DLL_EXPORT void CCALL		DGSetItemHelpIndex (short dialId, short item, short helpIndex);

DG_DLL_EXPORT short CCALL		DGGetDialogItemType (short dialId, short item);

DG_DLL_EXPORT short CCALL		DGGetDialogItemSubType (short dialId, short item);

DG_DLL_EXPORT short CCALL		DGGetUCItemType (short dialId, short item);


DG_DLL_EXPORT void CCALL		DGSetItemVariousState (short dialId, short itemId, bool isVarious);

DG_DLL_EXPORT bool CCALL		DGGetItemVariousState (short dialId, short itemId);

DG_DLL_EXPORT void CCALL		DGSetItemVariousText (short dialId, short itemId, const GS::UniString& text);


DG_DLL_EXPORT double CCALL		DGGetDialogScaleFactor (short dialId);

DG_DLL_EXPORT double CCALL		DGGetItemResolutionFactor (short dialId, short item);


DG_DLL_EXPORT void CCALL		DGScrollBarSetPageSize (short dialId, short item, Int32 pageSize);

DG_DLL_EXPORT Int32 CCALL		DGScrollBarGetPageSize (short dialId, short item);


DG_DLL_EXPORT void CCALL		DGSelectRadio (short dialId, short item);

DG_DLL_EXPORT short CCALL		DGGetCheckedRadio (short dialId, short groupId);


DG_DLL_EXPORT void CCALL		DGSetCheckBoxState (short dialId, short item, Int32 state);

DG_DLL_EXPORT short CCALL		DGGetCheckBoxState (short dialId, short item);


DG_DLL_EXPORT void CCALL		DGDateTimeSetMin (short dialId, short item, GSTime minValue);

DG_DLL_EXPORT void CCALL		DGDateTimeSetMax (short dialId, short item, GSTime maxValue);

DG_DLL_EXPORT void CCALL		DGDateTimeSetValue (short dialId, short item, GSTime value);

DG_DLL_EXPORT GSTime CCALL		DGDateTimeGetMin (short dialId, short item);

DG_DLL_EXPORT GSTime CCALL		DGDateTimeGetMax (short dialId, short item);

DG_DLL_EXPORT GSTime CCALL		DGDateTimeGetValue (short dialId, short item);

DG_DLL_EXPORT NewDisplay::NativeImage CCALL DGCaptureItemToNativeImage (short dialId, short item);


// --- User Item functions ---------------------------------------------------------------------------------------------

DG_DLL_EXPORT void CCALL		DGUserSetBackgroundColor (short dialId, short item, UShort red, UShort green, UShort blue);

DG_DLL_EXPORT bool CCALL		DGUserGetBackgroundColor (short dialId, short item, UShort* red, UShort* green, UShort* blue);

DG_DLL_EXPORT void CCALL		DGUserGetClientRect (short dialId, short item, short* left, short* top, short* right, short* bottom);

DG_DLL_EXPORT void CCALL		DGUserRedrawItem (short dialId, short item, bool erase = true, bool displayImmediately = false);

DG_DLL_EXPORT void* CCALL		DGUserGetControl (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGUserItemUpdateToolTip (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGUserItemEnableDraw (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGUserItemDisableDraw (short dialId, short item);

// --- List functions --------------------------------------------------------------------------------------------------

DG_DLL_EXPORT bool CCALL		DGListInsertItem (short dialId, short item, short listItem);

DG_DLL_EXPORT bool CCALL		DGListInsertSeparator (short dialId, short item, short listItem);

DG_DLL_EXPORT bool CCALL		DGListIsSeparatorItem (short dialId, short item, short listItem);

DG_DLL_EXPORT void CCALL		DGListDeleteItem (short dialId, short item, short listItem);

DG_DLL_EXPORT short CCALL		DGListGetItemCount (short dialId, short item);


DG_DLL_EXPORT bool CCALL		DGListSetTabFieldCount (short dialId, short item, short nTabFields);

DG_DLL_EXPORT short CCALL		DGListGetTabFieldCount (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGListSetTabFieldData (short dialId, short item, short tabIndex, short begPos, short endPos,
													   short justFlag, short truncFlag, bool hasSeparator, bool status);

DG_DLL_EXPORT void CCALL		DGListGetTabFieldData (short dialId, short item, short tabIndex, short* begPos, short* endPos,
													   short* justFlag, short* truncFlag, bool* hasSeparator, bool* status);

DG_DLL_EXPORT bool CCALL		DGListSetTabData (short dialId, short item, short nTabFields, const DGListTabData* tabData);


DG_DLL_EXPORT void CCALL		DGListSetTabFieldOwnerDrawFlag (short dialId, short item, short tabIndex, bool isOwnerDrawn);

DG_DLL_EXPORT bool CCALL		DGListGetTabFieldOwnerDrawFlag (short dialId, short item, short tabIndex);

DG_DLL_EXPORT void CCALL		DGListSetTabFieldToSearch (short dialId, short item, short tabIndex);

DG_DLL_EXPORT short CCALL		DGListGetTabFieldToSearch (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGListSetDialItemOnTabField (short dialId, short item, short tabIndex, short dialItem);

DG_DLL_EXPORT short CCALL		DGListGetDialItemOnTabField (short dialId, short item, short tabIndex);


DG_DLL_EXPORT void CCALL		DGListSetItemText (short dialId, short item, short listItem, const GS::UniString& text);

DG_DLL_EXPORT void CCALL		DGListSetTabItemText (short dialId, short item, short listItem, short tabIndex, const GS::UniString& text);

DG_DLL_EXPORT void CCALL		DGListSetTabItemIcon (short dialId, short item, short listItem, short tabIndex, const DG::Icon& icon);

DG_DLL_EXPORT void CCALL		DGListSetTabItemStyle (short dialId, short item, short listItem, short tabIndex, short style);

DG_DLL_EXPORT short CCALL		DGListGetTabItemStyle (short dialId, short item, short listItem, short tabIndex);

DG_DLL_EXPORT void CCALL		DGListSetTabItemColor (short dialId, short item, short listItem, short tabIndex, UShort red, UShort green, UShort blue);

DG_DLL_EXPORT bool CCALL		DGListGetTabItemColor (short dialId, short item, short listItem, short tabIndex, UShort* red, UShort* green, UShort* blue);

DG_DLL_EXPORT void CCALL		DGListSetTabItemBackgroundColor (short dialId, short item, short listItem, short tabIndex, UShort red, UShort green, UShort blue);

DG_DLL_EXPORT bool CCALL		DGListGetTabItemBackgroundColor (short dialId, short item, short listItem, short tabIndex, UShort* red, UShort* green, UShort* blue);

DG_DLL_EXPORT void CCALL			DGListSetTabItemDescription (short dialId, short item, short listItem, short tabIndex, const GS::UniString& description);

DG_DLL_EXPORT GS::UniString CCALL	DGListGetTabItemDescription (short dialId, short item, short listItem, short tabIndex);


DG_DLL_EXPORT void CCALL		DGListSetItemStyle (short dialId, short item, short listItem, short style);

DG_DLL_EXPORT short CCALL		DGListGetItemStyle (short dialId, short item, short listItem);

DG_DLL_EXPORT void CCALL		DGListSetItemStatus (short dialId, short item, short listItem, short status);

DG_DLL_EXPORT short CCALL		DGListGetItemStatus (short dialId, short item, short listItem);

DG_DLL_EXPORT void CCALL		DGListSetItemColor (short dialId, short item, short listItem, UShort red, UShort green, UShort blue);

DG_DLL_EXPORT void CCALL		DGListResetItemColor (short dialId, short item, short listItem);

DG_DLL_EXPORT bool CCALL		DGListGetItemColor (short dialId, short item, short listItem, UShort* red, UShort* green, UShort* blue);

DG_DLL_EXPORT void CCALL		DGListSetItemBackgroundColor (short dialId, short item, short listItem, UShort red, UShort green, UShort blue);

DG_DLL_EXPORT void CCALL		DGListResetItemBackgroundColor (short dialId, short item, short listItem);

DG_DLL_EXPORT bool CCALL		DGListGetItemBackgroundColor (short dialId, short item, short listItem, UShort* red, UShort* green, UShort* blue);

DG_DLL_EXPORT void CCALL		DGListSetItemUserData (short dialId, short item, short listItem, DGUserData value);

DG_DLL_EXPORT DGUserData CCALL	DGListGetItemUserData (short dialId, short item, short listItem);

DG_DLL_EXPORT void CCALL		DGListSetItemOwnerDrawFlag (short dialId, short item, short listItem, bool isOwnerDrawn);

DG_DLL_EXPORT bool CCALL		DGListGetItemOwnerDrawFlag (short dialId, short item, short listItem);


DG_DLL_EXPORT void CCALL		DGListSelectItem (short dialId, short item, short listItem);

DG_DLL_EXPORT void CCALL		DGListSelectItems (short dialId, short item, const GS::Array<short>& listItems);

DG_DLL_EXPORT void CCALL		DGListDeselectItem (short dialId, short item, short listItem);

DG_DLL_EXPORT short CCALL		DGListGetSelected (short dialId, short item, short listItem);

DG_DLL_EXPORT short CCALL		DGListGetSelCount (short dialId, short item);

DG_DLL_EXPORT short CCALL		DGListGetSelItems (short dialId, short item, short* selItems, short maxCount);


DG_DLL_EXPORT void CCALL		DGListSetItemHeight (short dialId, short item, short itemHeight);

DG_DLL_EXPORT short CCALL		DGListGetItemHeight (short dialId, short item);

DG_DLL_EXPORT short CCALL		DGListGetItemWidth (short dialId, short item);

DG_DLL_EXPORT short CCALL		DGListGetItemRect (short dialId, short item, short listItem, short* left, short* top, short* right, short* bottom);

DG_DLL_EXPORT void CCALL		DGListSetNoPartialItems (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGListEnableSeparatorLines (short dialId, short item, bool hasSeparatorLines);

DG_DLL_EXPORT bool CCALL		DGListHasSeparatorLines (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGListSetSeparatorLineColor (short dialId, short item, UShort red, UShort green, UShort blue);

DG_DLL_EXPORT void CCALL		DGListGetSeparatorLineColor (short dialId, short item, UShort* red, UShort* green, UShort* blue);


DG_DLL_EXPORT void CCALL		DGListEnableDraw (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGListDisableDraw (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGListRedrawItem (short dialId, short item, short listItem);

DG_DLL_EXPORT void CCALL		DGListRedrawTabItem (short dialId, short item, short listItem, short tabIndex);


DG_DLL_EXPORT void CCALL		DGListSetScrollPosition (short dialId, short item, short scrollPosition);

DG_DLL_EXPORT short CCALL		DGListGetScrollPosition (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGListScrollUp (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGListScrollDown (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGListSetHScrollPosition (short dialId, short item, short scrollPosition);

DG_DLL_EXPORT short CCALL		DGListGetHScrollPosition (short dialId, short item);


DG_DLL_EXPORT short CCALL		DGListGetItemFromPosition (short dialId, short item, short xPos, short yPos);


DG_DLL_EXPORT void CCALL		DGListSetHelpStyle (short dialId, short item, Int32 helpStyle);

DG_DLL_EXPORT Int32 CCALL		DGListGetHelpStyle (short dialId, short item);


DG_DLL_EXPORT void CCALL		DGListSetHeaderFlags (short dialId, short item, bool isSynchron, bool isPushable, bool isDragable);

DG_DLL_EXPORT void CCALL		DGListGetHeaderFlags (short dialId, short item, bool* isSynchron, bool* isPushable, bool* isDragable);

DG_DLL_EXPORT short CCALL		DGListGetHeaderHeight (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGListSetHeaderItemCount (short dialId, short item, short itemCount);

DG_DLL_EXPORT short CCALL		DGListGetHeaderItemCount (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGListSetHeaderItemText (short dialId, short item, short headerItem, const GS::UniString& text);

DG_DLL_EXPORT void CCALL		DGListSetHeaderItemIcon (short dialId, short item, short headerItem, const DG::Icon& icon);

DG_DLL_EXPORT void CCALL		DGListSetHeaderItemFont (short dialId, short item, short headerItem, short font);

DG_DLL_EXPORT short CCALL		DGListGetHeaderItemFont (short dialId, short item, short headerItem);

DG_DLL_EXPORT void CCALL		DGListSetHeaderItemFlags (short dialId, short item, short headerItem, short style, bool isSizeable);

DG_DLL_EXPORT void CCALL		DGListGetHeaderItemFlags (short dialId, short item, short headerItem, short* style, bool* isSizeable);

DG_DLL_EXPORT short CCALL		DGListSetHeaderItemSize (short dialId, short item, short headerItem, short size);

DG_DLL_EXPORT short CCALL		DGListGetHeaderItemSize (short dialId, short item, short headerItem);

DG_DLL_EXPORT void CCALL		DGListSetHeaderItemMinSize (short dialId, short item, short headerItem, short minSize);

DG_DLL_EXPORT short CCALL		DGListGetHeaderItemMinSize (short dialId, short item, short headerItem);

DG_DLL_EXPORT void  CCALL		DGListSetHeaderItemArrowType (short dialId, short item, short headerItem, short arrowType);

DG_DLL_EXPORT short CCALL		DGListGetHeaderItemArrowType (short dialId, short item, short headerItem);


DG_DLL_EXPORT void CCALL		DGListSetHeaderButtonIcon (short dialId, short item, const DG::Icon& icon);

DG_DLL_EXPORT void CCALL		DGListEnableHeaderButton (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGListDisableHeaderButton (short dialId, short item);

DG_DLL_EXPORT bool CCALL		DGListIsHeaderButtonEnabled (short dialId, short item);


// --- PopUp control functions -----------------------------------------------------------------------------------------

DG_DLL_EXPORT void CCALL		DGPopUpInsertItem (short dialId, short item, short popupItem);

DG_DLL_EXPORT void CCALL		DGPopUpInsertSeparator (short dialId, short item, short popupItem);

DG_DLL_EXPORT void CCALL		DGPopUpDeleteItem (short dialId, short item, short popupItem);

DG_DLL_EXPORT short CCALL		DGPopUpGetItemCount (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGPopUpSelectItem (short dialId, short item, short popupItem);

DG_DLL_EXPORT short CCALL		DGPopUpGetSelected (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGPopUpSetItemText (short dialId, short item, short popupItem, const GS::UniString& text);

DG_DLL_EXPORT void CCALL		DGPopUpSetItemIcon (short dialId, short item, short popupItem, const DG::Icon& icon);

DG_DLL_EXPORT void CCALL		DGPopUpSetItemStyle (short dialId, short item, short popupItem, short style);

DG_DLL_EXPORT short CCALL		DGPopUpGetItemStyle (short dialId, short item, short popupItem);

DG_DLL_EXPORT void CCALL		DGPopUpSetItemStatus (short dialId, short item, short popupItem, short status);

DG_DLL_EXPORT short CCALL		DGPopUpGetItemStatus (short dialId, short item, short popupItem);

DG_DLL_EXPORT void CCALL		DGPopUpSetItemUserData (short dialId, short item, short popupItem, DGUserData value);

DG_DLL_EXPORT DGUserData CCALL	DGPopUpGetItemUserData (short dialId, short item, short popupItem);

DG_DLL_EXPORT void CCALL		DGPopUpSetItemCharCode (short dialId, short item, short popupItem, GSCharCode charCode);

DG_DLL_EXPORT GSCharCode CCALL	DGPopUpGetItemCharCode (short dialId, short item, short popupItem);

DG_DLL_EXPORT void CCALL		DGPopUpEnableDraw (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGPopUpDisableDraw (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGPopUpInitAsFontPopupWithSortMode (short dialId, short item, /*TE::FontFamily::SortMode*/Int32 inSortMode);

DG_DLL_EXPORT void CCALL		DGPopUpAddFont (short dialId, short item, const TE::FontFamily& fontFamily);

DG_DLL_EXPORT void CCALL		DGPopUpSelectFont (short dialId, short item, const TE::FontFamily& fontFamily);

DG_DLL_EXPORT const TE::FontFamily* CCALL	DGPopUpGetSelectedFont (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGPopUpRefreshFontFavorites (short dialId, short item);

DG_DLL_EXPORT bool CCALL		DGPopUpIsSeparatorItem (short dialId, short item, short popupItem);

// --- TabControl functions --------------------------------------------------------------------------------------------

DG_DLL_EXPORT bool CCALL		DGTabControlInsertItem (short dialId, short item, short tabItem);

DG_DLL_EXPORT bool CCALL		DGTabControlDeleteItem (short dialId, short item, short tabItem);

DG_DLL_EXPORT short CCALL		DGTabControlGetItemCount (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGTabControlSetItemText (short dialId, short item, short tabItem, const GS::UniString& text);

DG_DLL_EXPORT void CCALL		DGTabControlSetItemIcon (short dialId, short item, short tabItem, const DG::Icon& icon);

DG_DLL_EXPORT void CCALL		DGTabControlEnableItem (short dialId, short item, short tabItem);

DG_DLL_EXPORT void CCALL		DGTabControlDisableItem (short dialId, short item, short tabItem);

DG_DLL_EXPORT void CCALL		DGTabControlSetItemStatus (short dialId, short item, short tabItem, bool enable);

DG_DLL_EXPORT bool CCALL		DGTabControlIsItemEnabled (short dialId, short item, short tabItem);

DG_DLL_EXPORT void CCALL		DGTabControlSelectItem (short dialId, short item, short tabItem);

DG_DLL_EXPORT short CCALL		DGTabControlGetSelectedItem (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGTabControlSetClientSize (short dialId, short item, short hSize, short vSize);

DG_DLL_EXPORT void CCALL		DGTabControlGetClientSize (short dialId, short item, short* hSize, short* vSize);

DG_DLL_EXPORT void CCALL		DGTabControlGetClientRect (short dialId, short item, short* left, short* top, short* right, short* bottom);

DG_DLL_EXPORT void CCALL		DGTabControlClientToFrame (short dialId, short item, short* hSize, short* vSize);

DG_DLL_EXPORT void CCALL		DGTabControlFrameToClient (short dialId, short item, short* hSize, short* vSize);

DG_DLL_EXPORT short CCALL		DGTabControlGetTabPageId (short dialId, short item, short tabItem);


// --- PushMenu control functions --------------------------------------------------------------------------------------

DG_DLL_EXPORT void CCALL		DGPushMenuSetItemCount (short dialId, short item, short itemCount);

DG_DLL_EXPORT short CCALL		DGPushMenuGetItemCount (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGPushMenuSelectItem (short dialId, short item, short menuItem);

DG_DLL_EXPORT short CCALL		DGPushMenuGetSelected (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGPushMenuCheck (short dialId, short item, short pushMenuItem);

DG_DLL_EXPORT short CCALL		DGPushMenuIsChecked (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGPushMenuEnableItem (short dialId, short item, short menuItem);

DG_DLL_EXPORT void CCALL		DGPushMenuDisableItem (short dialId, short item, short menuItem);

DG_DLL_EXPORT void CCALL		DGPushMenuSetItemEnable (short dialId, short item, short pushMenuItem, short isEnabled);

DG_DLL_EXPORT bool CCALL		DGPushMenuIsItemEnabled (short dialId, short item, short menuItem);

DG_DLL_EXPORT void CCALL		DGPushMenuSetItemIcon (short dialId, short item, short menuItem, const DG::Icon& icon);


// --- TreeView functions ----------------------------------------------------------------------------------------------

DG_DLL_EXPORT Int32 CCALL		DGTreeViewInsertItem (short dialId, short item, Int32 parentItem, Int32 treeItem);

DG_DLL_EXPORT void CCALL		DGTreeViewDeleteItem (short dialId, short item, Int32 treeItem);

DG_DLL_EXPORT Int32 CCALL		DGTreeViewGetItemCount (short dialId, short item);

DG_DLL_EXPORT Int32 CCALL		DGTreeViewGetItem (short dialId, short item, Int32 treeItem, short itemFlag);

DG_DLL_EXPORT Int32 CCALL		DGTreeViewGetItemFromPosition (short dialId, short item, short xPos, short yPos);

DG_DLL_EXPORT Int32 CCALL		DGTreeViewGetTopMostParent (short dialId, short item, Int32 treeItem);

DG_DLL_EXPORT bool CCALL		DGTreeViewHasAncestor (short dialId, short item, Int32 treeItem, Int32 ancestorItem);

DG_DLL_EXPORT Int32 CCALL		DGTreeViewGetLastVisibleChild (short dialId, short item, Int32 treeItem);

DG_DLL_EXPORT void CCALL		DGTreeViewSetItemText (short dialId, short item, Int32 treeItem, const GS::UniString& text);

DG_DLL_EXPORT void CCALL		DGTreeViewSetItemIcon (short dialId, short item, Int32 treeItem, short iconType, const DG::Icon& icon);

DG_DLL_EXPORT void CCALL		DGTreeViewSetIconSize (short dialId, short item, short iconType, short hSize, short vSize);

DG_DLL_EXPORT short CCALL		DGTreeViewGetIconSize (short dialId, short item, short iconType, short* hSize, short* vSize);

DG_DLL_EXPORT void CCALL		DGTreeViewSetItemStyle (short dialId, short item, Int32 treeItem, short style);

DG_DLL_EXPORT short CCALL		DGTreeViewGetItemStyle (short dialId, short item, Int32 treeItem);

DG_DLL_EXPORT void CCALL		DGTreeViewSetItemStatus (short dialId, short item, Int32 treeItem, short status);

DG_DLL_EXPORT short CCALL		DGTreeViewGetItemStatus (short dialId, short item, Int32 treeItem);

DG_DLL_EXPORT void CCALL		DGTreeViewSetItemTextColor (short dialId, short item, Int32 treeItem,
															UShort red, UShort green, UShort blue);

DG_DLL_EXPORT void CCALL		DGTreeViewResetItemTextColor (short dialId, short item, Int32 treeItem);

DG_DLL_EXPORT bool CCALL		DGTreeViewGetItemTextColor (short dialId, short item, Int32 treeItem,
															UShort* red, UShort* green, UShort* blue);

DG_DLL_EXPORT void CCALL		DGTreeViewSetItemBackgroundColor (short dialId, short item, Int32 treeItem,
																  UShort red, UShort green, UShort blue);

DG_DLL_EXPORT void CCALL		DGTreeViewResetItemBackgroundColor (short dialId, short item, Int32 treeItem);

DG_DLL_EXPORT bool CCALL		DGTreeViewGetItemBackgroundColor (short dialId, short item, Int32 treeItem,
																  UShort* red, UShort* green, UShort* blue);

DG_DLL_EXPORT void CCALL		DGTreeViewSetItemUserData (short dialId, short item, Int32 treeItem, DGUserData value);

DG_DLL_EXPORT DGUserData CCALL	DGTreeViewGetItemUserData (short dialId, short item, Int32 treeItem);


DG_DLL_EXPORT void CCALL		DGTreeViewExpandItem (short dialId, short item, Int32 treeItem);

DG_DLL_EXPORT void CCALL		DGTreeViewCollapseItem (short dialId, short item, Int32 treeItem);

DG_DLL_EXPORT short CCALL		DGTreeViewIsItemExpanded (short dialId, short item, Int32 treeItem);

DG_DLL_EXPORT void CCALL		DGTreeViewBeginItemEdit (short dialId, short item, Int32 treeItem);

DG_DLL_EXPORT void CCALL		DGTreeViewSelectItem (short dialId, short item, Int32 treeItem);

DG_DLL_EXPORT void CCALL		DGTreeViewDeselectItem (short dialId, short item, Int32 treeItem);

DG_DLL_EXPORT Int32 CCALL		DGTreeViewGetSelected (short dialId, short item, Int32 treeItem);

DG_DLL_EXPORT Int32 CCALL		DGTreeViewGetSelCount (short dialId, short item);

DG_DLL_EXPORT Int32 CCALL		DGTreeViewGetSelItems (short dialId, short item, Int32* selItems, Int32 maxCount);

DG_DLL_EXPORT Int32 CCALL		DGTreeViewGetScrollPosition (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGTreeViewSetScrollPosition (short dialId, short item, Int32 scrollPos);

DG_DLL_EXPORT void CCALL		DGTreeViewEnableDraw (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGTreeViewDisableDraw (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGTreeViewRedrawItem (short dialId, short item, Int32 treeItem);

DG_DLL_EXPORT short CCALL		DGTreeViewGetItemRect (short dialId, short item, Int32 treeItem,
													   short* left, short* top, short* right, short* bottom);
DG_DLL_EXPORT void CCALL		DGTreeViewSetHelpStyle (short dialId, short item, Int32 helpStyle);

DG_DLL_EXPORT Int32 CCALL		DGTreeViewGetHelpStyle (short dialId, short item);


// --- ListView functions ----------------------------------------------------------------------------------------------

DG_DLL_EXPORT void CCALL		DGListViewInsertItem (short dialId, short item, short listItem);

DG_DLL_EXPORT void CCALL		DGListViewDeleteItem (short dialId, short item, short listItem);

DG_DLL_EXPORT short CCALL		DGListViewGetItemCount (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGListViewSetItemText (short dialId, short item, short listItem, const GS::UniString& text);

DG_DLL_EXPORT void CCALL		DGListViewSetItemDescription (short dialId, short item, short listItem, const GS::UniString& description);

DG_DLL_EXPORT GS::UniString CCALL	DGListViewGetItemDescription (short dialId, short item, short listItem);

DG_DLL_EXPORT short CCALL		DGListViewGetItemImageType (short dialId, short item, short listItem);

DG_DLL_EXPORT void CCALL		DGListViewSetItemImage (short dialId, short item, short listItem, short imageType, const DG::Image& image);

DG_DLL_EXPORT void CCALL		DGListViewSetItemImageIndex (short dialId, short item, short listItem, short imageIndex);

DG_DLL_EXPORT short CCALL		DGListViewGetItemImageIndex (short dialId, short item, short listItem);

DG_DLL_EXPORT void CCALL		DGListViewSetItemOwnerDrawFlag (short dialId, short item, short listItem);

DG_DLL_EXPORT void CCALL		DGListViewSetItemStyle (short dialId, short item, short listItem, short style);

DG_DLL_EXPORT short CCALL		DGListViewGetItemStyle (short dialId, short item, short listItem);

DG_DLL_EXPORT void CCALL		DGListViewSetItemStatus (short dialId, short item, short listItem, short status);

DG_DLL_EXPORT short CCALL		DGListViewGetItemStatus (short dialId, short item, short listItem);

DG_DLL_EXPORT void CCALL		DGListViewSetItemColor (short dialId, short item, short listItem, UShort red,
														UShort green, UShort blue);

DG_DLL_EXPORT short CCALL		DGListViewGetItemColor (short dialId, short item, short listItem, UShort* red,
														UShort* green, UShort* blue);

DG_DLL_EXPORT void CCALL		DGListViewSetBackground (short dialId, short item, Int32 background);

DG_DLL_EXPORT Int32 CCALL		DGListViewGetBackground (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGListViewSetSelectionStyle (short dialId, short item, Int32 selectionStyle);

DG_DLL_EXPORT Int32 CCALL		DGListViewGetSelectionStyle (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGListViewSetHelpStyle (short dialId, short item, Int32 helpStyle);

DG_DLL_EXPORT Int32 CCALL		DGListViewGetHelpStyle (short dialId, short item);

DG_DLL_EXPORT short CCALL		DGListViewGetClientWidth (short dialId, short item);

DG_DLL_EXPORT short CCALL		DGListViewGetClientHeight (short dialId, short item);

DG_DLL_EXPORT short CCALL		DGListViewGetRowHeight (short dialId, short item);

DG_DLL_EXPORT bool CCALL		DGListViewHasVerticalScrollBar (short dialId, short item);

DG_DLL_EXPORT bool CCALL		DGListViewIsVerticalScrollbarVisible (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGListViewSetItemUserData (short dialId, short item, short listItem, DGUserData value);

DG_DLL_EXPORT DGUserData CCALL	DGListViewGetItemUserData (short dialId, short item, short listItem);

DG_DLL_EXPORT void CCALL		DGListViewSelectItem (short dialId, short item, short listItem);

DG_DLL_EXPORT void CCALL		DGListViewDeselectItem (short dialId, short item, short listItem);

DG_DLL_EXPORT short CCALL		DGListViewGetSelected (short dialId, short item, short listItem);

DG_DLL_EXPORT short CCALL		DGListViewGetSelCount (short dialId, short item);

DG_DLL_EXPORT short CCALL		DGListViewGetSelItems (short dialId, short item, short* selItems, short maxCount);

DG_DLL_EXPORT void CCALL		DGListViewSetScrollPosition (short dialId, short item, short scrollPosition);

DG_DLL_EXPORT short CCALL		DGListViewGetScrollPosition (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGListViewScrollUp (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGListViewScrollDown (short dialId, short item);

DG_DLL_EXPORT short CCALL		DGListViewGetItemFromPosition (short dialId, short item, short xPos, short yPos);

DG_DLL_EXPORT short CCALL		DGListViewGetItemRect (short dialId, short item, short listItem, short* left, short* top, short* right, short* bottom);

DG_DLL_EXPORT void CCALL		DGListViewSetViewMode (short dialId, short item, short viewMode);

DG_DLL_EXPORT short CCALL		DGListViewGetViewMode (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGListViewSetItemSize (short dialId, short item, short itemWidth, short itemHeight);

DG_DLL_EXPORT void CCALL		DGListViewGetItemSize (short dialId, short item, short* itemWidth, short* itemHeight);

DG_DLL_EXPORT void CCALL		DGListViewSetImageSize (short dialId, short item, short imageWidth, short imageHeight);

DG_DLL_EXPORT void CCALL		DGListViewSetImageGap (short dialId, short item, short imageGap);

DG_DLL_EXPORT short CCALL		DGListViewGetImageGap (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGListViewSetTextTruncateWidth (short dialId, short item, short textTruncateWidth);

DG_DLL_EXPORT short CCALL		DGListViewGetTextTruncateWidth (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGListViewGetImageSize (short dialId, short item, short* imageWidth, short* imageHeight);

DG_DLL_EXPORT short CCALL		DGListViewGetImageType (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGListViewSetImage (short dialId, short item, short imageType, const DG::Image& image,
													short nImages, short nRows);

DG_DLL_EXPORT void CCALL		DGListViewGetImageLayout (short dialId, short item, short* nImages, short* nRows);


DG_DLL_EXPORT void CCALL		DGListViewEnableDraw (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGListViewDisableDraw (short dialId, short item);


DG_DLL_EXPORT void CCALL		DGListViewClearHover (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGListViewSetHoverInWaitMillisecs (short dialId, short item, Int32 hoverInMillisecs);


// --- EditText functions ----------------------------------------------------------------------------------------------

DG_DLL_EXPORT void CCALL		DGEditTextCut (void);

DG_DLL_EXPORT void CCALL		DGEditTextCopy (void);

DG_DLL_EXPORT void CCALL		DGEditTextPaste (void);

DG_DLL_EXPORT void CCALL		DGEditTextClear (void);

DG_DLL_EXPORT void CCALL		DGEditTextUndo (void);

DG_DLL_EXPORT void CCALL		DGEditTextRedo (void);

DG_DLL_EXPORT short CCALL		DGEditTextCanUndo (void);

DG_DLL_EXPORT short CCALL		DGEditTextCanRedo (void);

DG_DLL_EXPORT void CCALL		DGEditTextClearUndo (void);

DG_DLL_EXPORT void CCALL		DGEditTextSetSelect (short dialId, short item, Int32 selStart, Int32 selEnd);

DG_DLL_EXPORT void CCALL		DGEditTextGetSelect (short dialId, short item, Int32* selStart, Int32* selEnd);

DG_DLL_EXPORT void CCALL		DGEditTextSetMaxLength (short dialId, short item, const UInt32 maxLength);

DG_DLL_EXPORT UInt32 CCALL		DGEditTextGetMaxLength (short dialId, short item);

DG_DLL_EXPORT bool CCALL		DGEditControlChangeIsPending (void);


// --- RichEdit functions ----------------------------------------------------------------------------------------------

DG_DLL_EXPORT void CCALL		DGRichEditSetSelect (short dialId, short item, Int32 selStart, Int32 selEnd);

DG_DLL_EXPORT void CCALL		DGRichEditGetSelect (short dialId, short item, Int32* selStart, Int32* selEnd);

DG_DLL_EXPORT void CCALL		DGRichEditEnableDraw (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGRichEditDisableDraw (short dialId, short item);

DG_DLL_EXPORT Int32 CCALL		DGRichEditGetLength (short dialId, short item);

DG_DLL_EXPORT Int32 CCALL		DGRichEditGetLineCount (short dialId, short item);

DG_DLL_EXPORT Int32 CCALL		DGRichEditGetLineFromPos (short dialId, short item, Int32 pos);

DG_DLL_EXPORT Int32 CCALL		DGRichEditGetLinePos (short dialId, short item, Int32 lineIndex);

DG_DLL_EXPORT Int32 CCALL		DGRichEditGetLineLength (short dialId, short item, Int32 lineIndex);

DG_DLL_EXPORT void CCALL		DGRichEditSetLineMaxLength (short dialId, short item, short lineLength);

DG_DLL_EXPORT void CCALL		DGRichEditSetText (short dialId, short item, const GS::UniString& text);

DG_DLL_EXPORT void CCALL		DGRichEditCatText (short dialId, short item, const GS::UniString& text);

DG_DLL_EXPORT void CCALL		DGRichEditSetTextRange (short dialId, short item, Int32 startPos, Int32 endPos, const GS::UniString& text);

DG_DLL_EXPORT short CCALL		DGRichEditFindText (short dialId, short item, Int32* startPos, Int32* endPos,
													 GS::UniString* text, short findFlag);

DG_DLL_EXPORT void CCALL		DGRichEditSetTabSize (short dialId, short item, short tabSize);

DG_DLL_EXPORT short CCALL		DGRichEditGetTabSize (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGRichEditSetFont (short dialId, short item, const DGTEFontData* fontData);

DG_DLL_EXPORT short CCALL		DGRichEditGetFont (short dialId, short item, DGTEFontData* fontData);

DG_DLL_EXPORT void CCALL 		DGRichEditSetWordWrap (short dialId, short item, bool wordWrap);

DG_DLL_EXPORT bool CCALL 		DGRichEditGetWordWrap (short dialId, short item);



#if defined macintosh
DG_DLL_EXPORT short CCALL		DGRichEditGetRequiredHeight (short dialId, short item);
#endif

DG_DLL_EXPORT void CCALL		DGRichEditSetCharCode (short dialId, short item, GSCharCode charCode);

DG_DLL_EXPORT GSCharCode CCALL	DGRichEditGetCharCode (short dialId, short item);


// --- UniRichEdit functions -------------------------------------------------------------------------------------------

DG_DLL_EXPORT void CCALL		DGUniRichEditSetSelect (short dialId, short item, Int32 selStart, Int32 selEnd);

DG_DLL_EXPORT void CCALL		DGUniRichEditGetSelect (short dialId, short item, Int32* selStart, Int32* selEnd);

DG_DLL_EXPORT Int32 CCALL		DGUniRichEditGetLineCount (short dialId, short item);

DG_DLL_EXPORT Int32 CCALL		DGUniRichEditGetLineFromPos (short dialId, short item, Int32 pos);

DG_DLL_EXPORT Int32 CCALL		DGUniRichEditGetLinePos (short dialId, short item, Int32 lineIndex);

DG_DLL_EXPORT Int32 CCALL		DGUniRichEditGetLineLength (short dialId, short item, Int32 lineIndex);

DG_DLL_EXPORT bool CCALL		DGUniRichEditHasText (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGUniRichEditSetText (short dialId, short item, const GS::uchar_t* text);

DG_DLL_EXPORT void CCALL		DGUniRichEditCatText (short dialId, short item, const GS::uchar_t* text);

DG_DLL_EXPORT Int32 CCALL		DGUniRichEditGetText (short dialId, short item, GS::uchar_t* text, Int32 size, short eolType);

DG_DLL_EXPORT void CCALL		DGUniRichEditSetTextRange (short dialId, short item, Int32 startPos, Int32 endPos, const GS::uchar_t* text);

DG_DLL_EXPORT Int32 CCALL		DGUniRichEditGetTextRange (short dialId, short item, Int32 startPos, Int32 endPos, GS::uchar_t* text,
														   Int32 size, short eolType);

DG_DLL_EXPORT short CCALL		DGUniRichEditFindText (short dialId, short item, Int32* startPos, Int32* endPos, const GS::uchar_t* text,
													   short findFlag);

DG_DLL_EXPORT void CCALL		DGUniRichEditSetDefaultTabSize (short dialId, short item, double tabSize);

DG_DLL_EXPORT double CCALL		DGUniRichEditGetDefaultTabSize (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGUniRichEditSetTextBoxWidth (short dialId, short item, double boxWidth);

DG_DLL_EXPORT double CCALL		DGUniRichEditGetTextBoxWidth (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGUniRichEditSetDefaultCharcode (short dialId, short item, GSCharCode charcode);

DG_DLL_EXPORT void CCALL		DGUniRichEditSetCharStyle (short dialId, short item, Int32 startPos, Int32 endPos, Int32 effect,
														   double size, UChar red, UChar green, UChar blue, Int32 style,
														   const GS::UniString& fontName, UShort styleFlag);

DG_DLL_EXPORT Int32 CCALL		DGUniRichEditGetCharStyle (short dialId, short item, Int32 startPos, Int32 endPos, Int32* effect,
														   double* size, UChar* red, UChar* green, UChar* blue, Int32* style,
														   GS::UniString* fontName, Int32 nameLength, UShort styleFlag);

DG_DLL_EXPORT void CCALL		DGUniRichEditSetParagraph (short dialId, short item, Int32 startPos, Int32 endPos, Int32 justification,
														   double firstIndent, double leftIndent, double rightIndent, double leading,
														   Int32 numTab, const DGTabulatorItem* tabs, UShort paraFlags);

DG_DLL_EXPORT Int32 CCALL		DGUniRichEditGetParagraph (short dialId, short item, Int32 startPos, Int32 endPos, Int32* justification,
														   double* firstIndent, double* leftIndent, double* rightIndent,
														   double* leading, DGTabulatorItem* tabs, Int32 size, UShort paraFlags);


DG_DLL_EXPORT Int32 CCALL		DGUniRichEditGetRuns (short dialId, short item, Int32 startPos, Int32 endPos,
													  DGCharRange* bounds, Int32 size);

DG_DLL_EXPORT Int32 CCALL		DGUniRichEditGetParagraphBounds (short dialId, short item, Int32 startPos, Int32 endPos,
																 DGCharRange* bounds, Int32 size);

DG_DLL_EXPORT Int32 CCALL		DGUniRichEditGetOffsetFromPoint (short dialId, short item, short xPos, short yPos, bool pointIsRelativeToControl);

DG_DLL_EXPORT void CCALL		DGUniRichEditClearUndo (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGUniRichEditBeginUndoAction (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGUniRichEditEndUndoAction (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGUniRichEditSetBackground (short dialId, short item, UChar red, UChar green, UChar blue);

#if defined (WINDOWS)
DG_DLL_EXPORT void CCALL		DGSetUniRichEditHotkeys (wchar_t bold, wchar_t italic, wchar_t underline);
#endif

DG_DLL_EXPORT void CCALL		DGUniRichEditGetCharBounds (short dialId, short item, UIndex charPosition, short& left, short& top, short& right, short& bottom);


// --- RulerControl functions ------------------------------------------------------------------------------------------

DG_DLL_EXPORT void CCALL		DGRulerInit (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGRulerEnableDraw (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGRulerDisableDraw (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGRulerSetUnitType (short dialId, short item, Int32 unitType);

DG_DLL_EXPORT Int32 CCALL		DGRulerGetUnitType (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGRulerSetTenUnitInPixels (short dialId, short item, double tenUnitInPixels);

DG_DLL_EXPORT double CCALL		DGRulerGetTenUnitInPixels (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGRulerSetSnapDistanceSI (short dialId, short item, double snapDistanceSI);

DG_DLL_EXPORT double CCALL		DGRulerGetSnapDistanceSI (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGRulerSetSnapDistanceUS (short dialId, short item, double snapDistanceUS);

DG_DLL_EXPORT double CCALL		DGRulerGetSnapDistanceUS (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGRulerSetDefaultTabDistance (short dialId, short item, double defTabDistance);

DG_DLL_EXPORT double CCALL		DGRulerGetDefaultTabDistance (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGRulerSetFirstLineIndent (short dialId, short item, double firstLineIndent);

DG_DLL_EXPORT double CCALL		DGRulerGetFirstLineIndent (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGRulerSetLeftIndent (short dialId, short item, double leftIndent);

DG_DLL_EXPORT double CCALL		DGRulerGetLeftIndent (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGRulerSetRightIndent (short dialId, short item, double rightIndent);

DG_DLL_EXPORT double CCALL		DGRulerGetRightIndent (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGRulerSetRightIndentDisabled (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGRulerSetRightIndentEnabled (short dialId, short item);

DG_DLL_EXPORT bool CCALL		DGRulerIsRightIndentDisabled (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGRulerSetTextBoxWidth (short dialId, short item, double textBoxWidth);

DG_DLL_EXPORT double CCALL		DGRulerGetTextBoxWidth (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGRulerSetScrollPosition (short dialId, short item, double scrollPosition);

DG_DLL_EXPORT double CCALL		DGRulerGetScrollPosition (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGRulerSetTabulators (short dialId, short item, short tabulatorCount, const DGTabulatorItem* tabulators);

DG_DLL_EXPORT short CCALL		DGRulerGetTabulatorCount (short dialId, short item);

DG_DLL_EXPORT short CCALL		DGRulerGetTabulators (short dialId, short item, short tabulatorCount, DGTabulatorItem* tabulators);

DG_DLL_EXPORT void CCALL		DGRulerSetRTLLayout (short dialId, short item, bool flag);

DG_DLL_EXPORT void CCALL		DGRulerDrawHairline (short dialId, short item, Int32 pos);


// --- Splitter Control functions --------------------------------------------------------------------------------------

DG_DLL_EXPORT void CCALL		DGSplitterEnableDrag (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGSplitterDisableDrag (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGSplitterSetDragStatus (short dialId, short item, bool isEnabled);

DG_DLL_EXPORT bool CCALL		DGSplitterIsDragEnabled (short dialId, short item);


// --- Button Control functions ----------------------------------------------------------------------------------------

DG_DLL_EXPORT void CCALL		DGButtonSetAlignment (short dialId, short itemId, short alignment);

DG_DLL_EXPORT short CCALL		DGButtonGetAlignment (short dialId, short itemId);


// --- SplitButton Control functions -----------------------------------------------------------------------------------

DG_DLL_EXPORT void CCALL		DGSplitButtonSetAlignment (short dialId, short itemId, short alignment);

DG_DLL_EXPORT short CCALL		DGSplitButtonGetAlignment (short dialId, short itemId);

DG_DLL_EXPORT void CCALL		DGSplitButtonAppendItem (short dialId, short item, const GS::UniString& itemText, const void* itemIcon);

DG_DLL_EXPORT void CCALL		DGSplitButtonAppendSeparator (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGSplitButtonInsertItem (short dialId, short item, short poupItem, const GS::UniString& itemText, const void* itemIcon);

DG_DLL_EXPORT void CCALL		DGSplitButtonInsertSeparator (short dialId, short item, short popupItem);

DG_DLL_EXPORT void CCALL		DGSplitButtonDeleteItem (short dialId, short item, short popupItem);

DG_DLL_EXPORT USize CCALL		DGSplitButtonGetItemCount (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGSplitButtonSetItemIcon (short dialId, short item, short popupItem, const void* icon);

DG_DLL_EXPORT bool CCALL		DGSplitButtonGetItemIcon (short dialId, short item, short popupItem, void* icon);

DG_DLL_EXPORT void CCALL		DGSplitButtonSetItemText (short dialId, short item, short popupItem, const GS::UniString& text);

DG_DLL_EXPORT void CCALL		DGSplitButtonSetItemFont (short dialId, short item, short popupItem, short fontType);

DG_DLL_EXPORT short CCALL		DGSplitButtonGetItemFont (short dialId, short item, short popupItem);

DG_DLL_EXPORT void CCALL		DGSplitButtonSetItemData (short dialId, short item, short popupItem, DGUserData value);

DG_DLL_EXPORT DGUserData CCALL	DGSplitButtonGetItemData (short dialId, short item, short popupItem);

DG_DLL_EXPORT void CCALL		DGSplitButtonEnableItem (short dialId, short item, short popupItem);

DG_DLL_EXPORT void CCALL		DGSplitButtonDisableItem (short dialId, short item, short popupItem);

DG_DLL_EXPORT void CCALL		DGSplitButtonSetItemStatus (short dialId, short item, short popupItem, bool status);

DG_DLL_EXPORT bool CCALL		DGSplitButtonIsItemEnabled (short dialId, short item, short popupItem);

DG_DLL_EXPORT bool CCALL		DGSplitButtonIsSeparatorItem (short dialId, short item, short popupItem);

DG_DLL_EXPORT void CCALL		DGSplitButtonShowAndTrackPopup (short dialId, short item);

DG_DLL_EXPORT void CCALL        DGSplitButtonEnableDraw (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGSplitButtonDisableDraw (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGSplitButtonSetType (short dialId, short item, bool custom);

DG_DLL_EXPORT bool CCALL		DGSplitButtonIsCustomType (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGSplitButtonSetArrowPartWidth (short dialId, short item, short width);

DG_DLL_EXPORT short CCALL		DGSplitButtonGetArrowPartWidth (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGSplitButtonEnableArrowPart (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGSplitButtonDisableArrowPart (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGSplitButtonSetArrowPartStatus (short dialId, short item, bool status);

DG_DLL_EXPORT bool CCALL		DGSplitButtonIsArrowPartEnabled (short dialId, short item);


// --- PushCheck Control functions ----------------------------------------------------------------------------------------

DG_DLL_EXPORT void CCALL		DGPushCheckSetArrowType (short dialId, short itemId, short arrowType);

DG_DLL_EXPORT short CCALL		DGPushCheckGetArrowType (short dialId, short itemId);


// --- TabBar Control functions ----------------------------------------------------------------------------------------

DG_DLL_EXPORT void CCALL		DGTabBarSetType (short dialId, short item, short type);

DG_DLL_EXPORT short CCALL		DGTabBarGetType (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGTabBarSetItemAlignment (short dialId, short item, short itemAlignment);

DG_DLL_EXPORT short CCALL		DGTabBarGetItemAlignment (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGTabBarSetIconButtonVisibility (short dialId, short item, bool isVisible);

DG_DLL_EXPORT bool CCALL		DGTabBarIsIconButtonVisible (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGTabBarSetIconButtonContent (short dialId, short item, const DG::Icon& icon);

DG_DLL_EXPORT void CCALL		DGTabBarSetSpecialCursors (short dialId, short item, GSResModule cursorResModule, Int32 pickUpCursorId, Int32 injectCursorId, Int32 tickOKCursorId);

DG_DLL_EXPORT void CCALL		DGTabBarSetForcedSpecialCursor (short dialId, short item, Int32 forcedCursorId);

#ifdef macintosh
DG_DLL_EXPORT bool CCALL		DGTabBarHandleFlagsChanged (short dialId, short item, Int32 modifierFlags);
#endif

DG_DLL_EXPORT void CCALL		DGTabBarSetItemMinWidth (short dialId, short item, Int32 minWidth);

DG_DLL_EXPORT Int32 CCALL		DGTabBarGetItemMinWidth (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGTabBarSetItemMaxWidth (short dialId, short item, Int32 maxWidth);

DG_DLL_EXPORT Int32 CCALL		DGTabBarGetItemMaxWidth (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGTabBarSetItemPreferredWidth (short dialId, short item, Int32 preferredWidth);

DG_DLL_EXPORT Int32 CCALL		DGTabBarGetItemPreferredWidth (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGTabBarSetCloseButtonVisibility (short dialId, short item, bool isVisible);

DG_DLL_EXPORT bool CCALL		DGTabBarIsCloseButtonVisible (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGTabBarSetDragEnabled (short dialId, short item, bool isEnabled);

DG_DLL_EXPORT bool CCALL		DGTabBarIsDragEnabled (short dialId, short item);

DG_DLL_EXPORT bool CCALL		DGTabBarIsBeingDragged (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGTabBarEnableDraw (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGTabBarDisableDraw (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGTabBarSetStatus (short dialId, short item, short status);

DG_DLL_EXPORT short CCALL		DGTabBarGetStatus (short dialId, short item);

DG_DLL_EXPORT Gfx::Color CCALL	DGTabBarGetItemSystemBackColor (short dialId, short item, Int32 itemControlState, bool isSelected);

#ifdef WINDOWS

DG_DLL_EXPORT Gfx::Color CCALL	DGTabBarGetCloseButtonSystemBackColor (short dialId, short item, Int32 itemControlState, bool isSelected);

DG_DLL_EXPORT Gfx::Color CCALL	DGTabBarGetCloseButtonSystemForeColor (short dialId, short item, Int32 itemControlState, bool isSelected);

#else

DG_DLL_EXPORT NewDisplay::NativeImage CCALL	DGTabBarGetCloseButtonSystemImage (short dialId, short item, Int32 itemControlState, bool isSelected);

#endif

DG_DLL_EXPORT Int32 CCALL		DGTabBarInsertBeforeItem (short dialId, short item, Int32 beforeItemId, const GS::UniString& itemText, const DG::Icon& itemIcon);

DG_DLL_EXPORT Int32 CCALL		DGTabBarInsertAfterItem (short dialId, short item, Int32 afterItemId, const GS::UniString& itemText, const DG::Icon& itemIcon);

DG_DLL_EXPORT void CCALL		DGTabBarDeleteItem (short dialId, short item, Int32 tabBarItemId);

DG_DLL_EXPORT void CCALL		DGTabBarDeleteAllItems (short dialId, short item);

DG_DLL_EXPORT Int32 CCALL		DGTabBarGetEnabledItemCount (short dialId, short item);

DG_DLL_EXPORT Int32 CCALL		DGTabBarGetItemCount (short dialId, short item);

DG_DLL_EXPORT Int32 CCALL		DGTabBarGetItemIndex (short dialId, short item, Int32 tabBarItemId);	// 1-based index

DG_DLL_EXPORT Int32 CCALL		DGTabBarGetItemId (short dialId, short item, Int32 tabBarItemIndex);	// 1-based index

DG_DLL_EXPORT Int32 CCALL		DGTabBarGetNextItemId (short dialId, short item, Int32 tabBarItemId, bool cycle, bool skipDisabled);

DG_DLL_EXPORT Int32 CCALL		DGTabBarGetPreviousItemId (short dialId, short item, Int32 tabBarItemId, bool cycle, bool skipDisabled);

DG_DLL_EXPORT void CCALL		DGTabBarSelectItem (short dialId, short item, Int32 tabBarItemId);

DG_DLL_EXPORT Int32 CCALL		DGTabBarGetSelectedItem (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGTabBarMoveItem (short dialId, short item, Int32 tabBarItemId, Int32 newIndex);	// 1-based index

DG_DLL_EXPORT void CCALL		DGTabBarSetItemText (short dialId, short item, Int32 tabBarItemId, const GS::UniString& text);

DG_DLL_EXPORT void CCALL		DGTabBarSetItemIcon (short dialId, short item, Int32 tabBarItemId, const DG::Icon& itemIcon);

DG_DLL_EXPORT void CCALL		DGTabBarSetItemTextColor (short dialId, short item, Int32 tabBarItemId, const Gfx::Color& color);

DG_DLL_EXPORT void CCALL		DGTabBarResetItemTextColor (short dialId, short item, Int32 tabBarItemId);

DG_DLL_EXPORT void CCALL		DGTabBarSetItemOverlayColor (short dialId, short item, Int32 tabBarItemId, const Gfx::Color& color);

DG_DLL_EXPORT void CCALL		DGTabBarResetItemOverlayColor (short dialId, short item, Int32 tabBarItemId);

DG_DLL_EXPORT Gfx::Color CCALL	DGTabBarGetItemOverlayColor (short dialId, short item, Int32 tabBarItemId);

DG_DLL_EXPORT void CCALL		DGTabBarSetItemUserData (short dialId, short item, Int32 tabBarItemId, DGUserData value);

DG_DLL_EXPORT DGUserData CCALL	DGTabBarGetItemUserData (short dialId, short item, Int32 tabBarItemId);

DG_DLL_EXPORT void CCALL		DGTabBarSetItemStatus (short dialId, short item, Int32 tabBarItemId, bool status);

DG_DLL_EXPORT bool CCALL		DGTabBarIsItemEnabled (short dialId, short item, Int32 tabBarItemId);

DG_DLL_EXPORT void CCALL		DGTabBarSetSpecialCursorsStatus (short dialId, short item, Int32 tabBarItemId, bool status);

DG_DLL_EXPORT bool CCALL		DGTabBarAreSpecialCursorsEnabled (short dialId, short item, Int32 tabBarItemId);

DG_DLL_EXPORT void CCALL		DGTabBarSetItemFont (short dialId, short item, Int32 tabBarItemId, short fontType);

DG_DLL_EXPORT short CCALL		DGTabBarGetItemFont (short dialId, short item, Int32 tabBarItemId);

DG_DLL_EXPORT void CCALL		DGTabBarSetItemOverlayIcon (short dialId, short item, Int32 tabBarItemId, const DG::Icon& overlayIcon);

DG_DLL_EXPORT void CCALL		DGTabBarSetOverlayIconVisibility (short dialId, short item, Int32 tabBarItemId, bool isOverlayIconVisible);

DG_DLL_EXPORT bool CCALL		DGTabBarIsOverlayIconVisible (short dialId, short item, Int32 tabBarItemId);

DG_DLL_EXPORT void CCALL		DGTabBarSetItemBusyState (short dialId, short item, Int32 tabBarItemId, bool isBusy);

DG_DLL_EXPORT bool CCALL		DGTabBarGetItemBusyState (short dialId, short item, Int32 tabBarItemId);

DG_DLL_EXPORT Int32 CCALL		DGTabBarGetItemWidth (short dialId, short item, Int32 tabBarItemId);

DG_DLL_EXPORT bool CCALL		DGTabBarGetItemRect (short dialId, short item, Int32 tabBarItemId, short& left, short& top, short& right, short& bottom);	// Retrieves rect in control relative logical units

DG_DLL_EXPORT void CCALL		DGTabBarSetItemIsClosing (short dialId, short item, Int32 tabBarItemId);

DG_DLL_EXPORT bool CCALL		DGTabBarIsItemClosing (short dialId, short item, Int32 tabBarItemId);

DG_DLL_EXPORT void CCALL		DGTabBarSetHoverInWaitMillisecs (short dialId, short item, Int32 hoverInWaitMillisecs);

DG_DLL_EXPORT Int32 CCALL		DGTabBarGetHoverInWaitMillisecs (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGTabBarIncrImmediateHoveringLevel (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGTabBarDecrImmediateHoveringLevel (short dialId, short item);

DG_DLL_EXPORT bool CCALL		DGTabBarGetImmediateHovering (short dialId, short item);

DG_DLL_EXPORT void CCALL		DGTabBarSetCloseButtonVisibilityMode (short dialId, short item, Int32 tabBarItemId, Int32 closeButtonVisibilityMode);

DG_DLL_EXPORT void CCALL		DGTabBarSetVerticalAlignmentRuleUsage (short dialId, short item, Int32 tabBarItemId, Int32 verticalAlignmentRuleUsage);

DG_DLL_EXPORT bool CCALL		DGTabBarIsForcedToFirstPosition (short dialId, short item, Int32 tabBarItemId);

DG_DLL_EXPORT void CCALL		DGTabBarSetForcedToFirstPosition (short dialId, short item, Int32 tabBarItemId);

// --- Test functions --------------------------------------------------------------------------------------------------

DG_DLL_EXPORT void CCALL		DGConvertTextUnitTest (void);

//#if defined (__cplusplus)
//	}
//#endif


// --- Functions outside with C++ linkage ------------------------------------------------------------------------------

DG_DLL_EXPORT void CCALL			DGGetMonitorRectFromRect (DG::NativeUnit* left, DG::NativeUnit* top, DG::NativeUnit* right, DG::NativeUnit* bottom);

DG_DLL_EXPORT GS::UniString	CCALL	DGGetMultiLineText (short dialId, short item, short eolType = DG_EOL_DEFAULT);

DG_DLL_EXPORT GS::UniString CCALL	DGRichEditGetText (short dialId, short item, short eolType = DG_EOL_DEFAULT);

DG_DLL_EXPORT GS::UniString CCALL	DGGetItemText (short dialId, short item);

DG_DLL_EXPORT GS::UniString CCALL	DGGetItemDescription (short dialId, short itemId);

DG_DLL_EXPORT void			CCALL	DGGetItemNativeRectInScreenSpace (short dialId, short item, DG::NativeUnit* left, DG::NativeUnit* top, DG::NativeUnit* right, DG::NativeUnit* bottom);

DG_DLL_EXPORT GS::UniString CCALL	DGGetDialogAnchorString (short dialId, GSResModule dialResModule = InvalidResModule);

DG_DLL_EXPORT GS::UniString CCALL	DGGetDialogTitle (short dialId);

DG_DLL_EXPORT GS::UniString CCALL	DGGetItemTooltipString (short dialId, short item, GSResModule dialResModule = InvalidResModule);

DG_DLL_EXPORT GS::UniString CCALL	DGGetItemAnchorString (short dialId, short item, GSResModule dialResModule = InvalidResModule);

DG_DLL_EXPORT GS::Array<short> CCALL	DGListGetSelectedItems (short dialId, short item);

DG_DLL_EXPORT GS::UniString CCALL	DGListGetItemText (short dialId, short item, short listItem);

DG_DLL_EXPORT GS::UniString CCALL	DGListGetTabItemText (short dialId, short item, short listItem, short tabIndex);

DG_DLL_EXPORT GS::UniString CCALL	DGListGetHeaderItemText (short dialId, short item, short headerItem);

DG_DLL_EXPORT DG::Icon CCALL		DGListGetHeaderItemIcon (short dialId, short item, short headerItem);

DG_DLL_EXPORT DG::Icon CCALL		DGListGetHeaderButtonIcon (short dialId, short item);

DG_DLL_EXPORT GS::UniString CCALL	DGPopUpGetItemText (short dialId, short item, short popupItem);

DG_DLL_EXPORT GS::UniString CCALL	DGTreeViewGetItemText (short dialId, short item, Int32 treeItem);

DG_DLL_EXPORT GS::UniString CCALL	DGListViewGetItemText (short dialId, short item, short listItem);

DG_DLL_EXPORT GS::UniString CCALL	DGTabControlGetItemText (short dialId, short item, short tabItem);

DG_DLL_EXPORT GS::UniString CCALL	DGDoubleToString (double value, short type);

DG_DLL_EXPORT GS::UniString CCALL	DGDoubleToStringUnit (const DGUnitData* uData, double value, short type);

DG_DLL_EXPORT GS::UniString CCALL	DGLongToString (Int32 value, short type);

DG_DLL_EXPORT GS::UniString CCALL	DGRichEditGetTextRange (short dialId, short item, Int32 startPos, Int32 endPos, short eolType);

DG_DLL_EXPORT GS::UniString CCALL	DGSplitButtonGetItemText (short dialId, short item, short popupItem);

DG_DLL_EXPORT GS::UniString CCALL	DGGetItemVariousText (short dialId, short item);

DG_DLL_EXPORT DG::Icon		CCALL	DGTreeViewGetItemIcon (short dialId, short item, Int32 treeItem, short iconType);

DG_DLL_EXPORT DG::Icon		CCALL	DGListGetTabItemIcon (short dialId, short item, short listItem, short tabIndex);

DG_DLL_EXPORT DG::Icon		CCALL	DGPopUpGetItemIcon (short dialId, short item, short popupItem);

DG_DLL_EXPORT DG::Icon		CCALL	DGTabControlGetItemIcon (short dialId, short item, short tabItem);

DG_DLL_EXPORT DG::Icon		CCALL	DGPushMenuGetItemIcon (short dialId, short item, short menuItem);

DG_DLL_EXPORT DG::Icon		CCALL	DGGetDialogIcon (short dialId);

DG_DLL_EXPORT DG::Image		CCALL	DGGetItemImage (short dialId, short item);

DG_DLL_EXPORT DG::Image		CCALL	DGListViewGetItemImage (short dialId, short item, short listItem);

DG_DLL_EXPORT DG::Image		CCALL	DGListViewGetImage (short dialId, short item);

DG_DLL_EXPORT DG::Icon		CCALL	DGTabBarGetIconButtonContent (short dialId, short item);

DG_DLL_EXPORT GS::UniString CCALL	DGTabBarGetItemText (short dialId, short item, Int32 tabBarItemId);

DG_DLL_EXPORT DG::Icon		CCALL	DGTabBarGetItemIcon (short dialId, short item, Int32 tabBarItemId);

DG_DLL_EXPORT Gfx::Color	CCALL	DGTabBarGetItemTextColor (short dialId, short item, Int32 tabBarItemId);

DG_DLL_EXPORT DG::Icon		CCALL	DGTabBarGetItemOverlayIcon (short dialId, short item, Int32 tabBarItemId);

DG_DLL_EXPORT void					CCALL	DGTabBarSetItemObjectData (short dialId, short item, Int32 tabBarItemId, GS::Ref<GS::Object> object);

DG_DLL_EXPORT GS::Ref<GS::Object>	CCALL	DGTabBarGetItemObjectData (short dialId, short item, Int32 tabBarItemId);

DG_DLL_EXPORT void					CCALL	DGListSetItemObjectData (short dialId, short item, short listItem, GS::Ref<GS::Object> object);

DG_DLL_EXPORT GS::Ref<GS::Object>	CCALL	DGListGetItemObjectData (short dialId, short item, short listItem);

DG_DLL_EXPORT void					CCALL	DGPopUpSetItemObjectData (short dialId, short item, short popupItem, GS::Ref<GS::Object> object);

DG_DLL_EXPORT GS::Ref<GS::Object>	CCALL	DGPopUpGetItemObjectData (short dialId, short item, short popupItem);

DG_DLL_EXPORT void					CCALL	DGListViewSetItemObjectData (short dialId, short item, short listItem, GS::Ref<GS::Object> object);

DG_DLL_EXPORT GS::Ref<GS::Object>	CCALL	DGListViewGetItemObjectData (short dialId, short item, short listItem);

DG_DLL_EXPORT void					CCALL	DGSplitButtonSetItemObjectData (short dialId, short item, short popupItem, GS::Ref<GS::Object> object);

DG_DLL_EXPORT GS::Ref<GS::Object>	CCALL	DGSplitButtonGetItemObjectData (short dialId, short item, short popupItem);

DG_DLL_EXPORT void					CCALL	DGTreeViewSetItemObjectData (short dialId, short item, Int32 treeItem, GS::Ref<GS::Object> object);

DG_DLL_EXPORT GS::Ref<GS::Object>	CCALL	DGTreeViewGetItemObjectData (short dialId, short item, Int32 treeItem);

DG_DLL_EXPORT bool					CCALL	DGAreAllBrowserControlsIdle ();

#endif
