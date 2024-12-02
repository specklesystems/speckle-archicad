// *********************************************************************************************************************
// File:			DGModule.hpp
//
// Description:		Main include file of the DG C++ interface
//					Also contains module global definitions and functions
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	BM, AZS
// *********************************************************************************************************************

#ifndef DGMODULE_HPP
#define DGMODULE_HPP

#pragma once


// --- Inlcudes --------------------------------------------------------------------------------------------------------

#include "DG.h"
#include "DGBarControl.hpp"
#include "DGButton.hpp"
#include "DGCheckItem.hpp"
#include "DGDateTime.hpp"
#include "DGDialog.hpp"
#include "DGEditControl.hpp"
#include "DGFileDialog.hpp"
#include "DGImage.hpp"
#include "DGItem.hpp"
#include "DGItemGroup.hpp"
#include "DGItemProperty.hpp"
#include "DGListBox.hpp"
#include "DGListView.hpp"
#include "DGPanel.hpp"
#include "DGPopUp.hpp"
#include "DGPushMenu.hpp"
#include "DGRadioItem.hpp"
#include "DGRichEdit.hpp"
#include "DGRuler.hpp"
#include "DGSplitter.hpp"
#include "DGStaticItem.hpp"
#include "DGTabBar.hpp"
#include "DGTabControl.hpp"
#include "DGTabPage.hpp"
#include "DGTreeView.hpp"
#include "DGUniRichEdit.hpp"
#include "DGUserControl.hpp"
#include "DGUserItem.hpp"
#include "DGUtility.hpp"


// --- Predeclarations -------------------------------------------------------------------------------------------------

namespace TE {
	class Font;
}


namespace DG {

// === Global definitions and constants ================================================================================

enum AlertResponse {
	Accept	= DG_OK,
	Cancel	= DG_CANCEL,
	Third	= DG_THIRD
};


enum PropertyHint {
	UnitSet,
	OnlyUpdate,
	NextModalParent,
	EditUpdateDelay,
	AutoCloseEnabled,
	AutoCloseDisabled,
	AutoCloseDelay,
	NormalUpdateEnabled,
	NormalUpdateDisabled,
	ToolTipsEnabled,
	ToolTipsDisabled,
	DialogRectangleReset,
	SelectionClear,
	SelectionCopy,
	SelectionCut,
	SelectionPaste,
	UndoEdit,
	RedoEdit
};


// === Property Event Source - Observer ================================================================================

class DG_DLL_EXPORT PropertyObserver: public GS::EventObserver
{
public:
	PropertyObserver ();
	virtual ~PropertyObserver ();

	virtual void	PropertyChanged (PropertyHint hint);
};


class DG_DLL_EXPORT PropertyEventSource: public GS::EventSource
{
public:
	PropertyEventSource ();
	virtual	~PropertyEventSource ();

	void	Send (PropertyHint hint);

	void	Attach (PropertyObserver& observer);
	void	Detach (PropertyObserver& observer);
};


typedef bool	(CCALL *DialogEnumCallbackConst) (const Dialog* dial, void* userData);


// === Global functions ================================================================================================

// --- DG module management functions ----------------------------------------------------------------------------------

DG_DLL_EXPORT void	InitModule (const DGInitData* initData);

DG_DLL_EXPORT void	ExitModule (void);


// --- Alert and special dialog functions ------------------------------------------------------------------------------

DG_DLL_EXPORT AlertResponse	ErrorAlert (const GS::UniString& largeText, const GS::UniString& smallText, const GS::UniString& button1Text,
										const GS::UniString& button2Text = GS::UniString (), const GS::UniString& button3Text = GS::UniString ());

DG_DLL_EXPORT AlertResponse	WarningAlert (const GS::UniString& largeText, const GS::UniString& smallText, const GS::UniString& button1Text,
										  const GS::UniString& button2Text = GS::UniString (), const GS::UniString& button3Text = GS::UniString ());

DG_DLL_EXPORT AlertResponse	InformationAlert (const GS::UniString& largeText, const GS::UniString& smallText, const GS::UniString& button1Text,
											  const GS::UniString& button2Text = GS::UniString (), const GS::UniString& button3Text = GS::UniString ());

DG_DLL_EXPORT AlertResponse	CustomAlert (short iconId, GSResModule resModule, const GS::UniString& titleText, const GS::UniString& largeText,
										 const GS::UniString& smallText, const GS::UniString& button1Text,
										 const GS::UniString& button2Text = GS::UniString (), const GS::UniString& button3Text = GS::UniString ());

DG_DLL_EXPORT AlertResponse	Alert (GSResModule resModule, short alertId, const GS::UniString& paramText1 = GS::UniString (), const GS::UniString& paramText2 = GS::UniString (),
								   const GS::UniString& paramText3 = GS::UniString (), const GS::UniString& paramText4 = GS::UniString ());


DG_DLL_EXPORT bool		GetColor (const GS::UniString& title, Gfx::Color* color);


// --- Dialog Z order functions ----------------------------------------------------------------------------------------

DG_DLL_EXPORT ModalDialog*		GetFirstModalDialog (void);

DG_DLL_EXPORT ModalDialog*		GetLastModalDialog (void);


DG_DLL_EXPORT ModelessDialog*	GetFirstModelessDialog (void);

DG_DLL_EXPORT ModelessDialog*	GetLastModelessDialog (void);

DG_DLL_EXPORT ModelessDialog*	GetFirstVisibleModelessDialog (void);

DG_DLL_EXPORT ModelessDialog*	GetLastVisibleModelessDialog (void);


DG_DLL_EXPORT Palette*	GetFirstPalette (void);

DG_DLL_EXPORT Palette*	GetLastPalette (void);

DG_DLL_EXPORT Palette*	GetFirstVisiblePalette (void);

DG_DLL_EXPORT Palette*	GetLastVisiblePalette (void);


DG_DLL_EXPORT bool		EnumerateDialogs (DG::Dialog::DialogType	dialType,
										  short						refDiaId,
										  bool						visibleOnly,
										  bool						reversed,
										  DialogEnumCallbackConst	dialEC,
										  void*						userData);



// --- Other dialog functions ------------------------------------------------------------------------------------------

DG_DLL_EXPORT bool		ModelessHandler (const void* sysMessage, bool onlyUpdate);

DG_DLL_EXPORT void		SetOnlyUpdateFlag (bool onlyUpdate);


DG_DLL_EXPORT Dialog*	GetDialogFromId (short dialId);

DG_DLL_EXPORT Dialog*	GetDialogFromWindow (const void* dialWindow);


DG_DLL_EXPORT void*		GetActiveWindow (void);


DG_DLL_EXPORT void		SetNextModalParent (const void* parentWindow);

DG_DLL_EXPORT void*		GetNextModalParent (void);

DG_DLL_EXPORT bool		GetPropertyEventSource (PropertyEventSource** eventSource);


// --- Number to srting conversion functions ---------------------------------------------------------------------------

DG_DLL_EXPORT GS::UniString	RealToString (double value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT GS::UniString	AngleToString (double value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT GS::UniString	PolarAngleToString (double value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT GS::UniString	LengthToString (double value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT GS::UniString	AreaToString (double value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT GS::UniString	VolumeToString (double value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT GS::UniString	MmOrPtToString (double value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT GS::UniString	MmOrInchToString (double value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT GS::UniString	LongToString (Int32 value);

DG_DLL_EXPORT GS::UniString	ULongToString (ULong value);


// --- String to number conversion functions ---------------------------------------------------------------------------

DG_DLL_EXPORT Int32	StringToReal (const GS::UniString& str, double& value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT Int32	StringToAngle (const GS::UniString& str, double& value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT Int32	StringToPolarAngle (const GS::UniString& str, double& value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT Int32	StringToLength (const GS::UniString& str, double& value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT Int32	StringToArea (const GS::UniString& str, double& value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT Int32	StringToVolume (const GS::UniString& str, double& value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT Int32	StringToMmOrPt (const GS::UniString& str, double& value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT Int32	StringToMmOrInch (const GS::UniString& str, double& value, const DGUnitData* uData = nullptr);


// --- Miscellaneous functions -----------------------------------------------------------------------------------------

DG_DLL_EXPORT Item*	GetFocusedItem (void);


DG_DLL_EXPORT void	GetFont (Font::Size size, Font::Style style, TE::Font *font);


DG_DLL_EXPORT void	SetEditUpdateDelay (ULong delay);

DG_DLL_EXPORT ULong	GetEditUpdateDelay (void);

DG_DLL_EXPORT void	FlushDelayedEditItemChange (void);


DG_DLL_EXPORT void	EnableAutoClose (void);

DG_DLL_EXPORT void	DisableAutoClose (void);

DG_DLL_EXPORT void	SetAutoCloseState (bool enable);

DG_DLL_EXPORT bool	IsAutoCloseEnabled (void);

DG_DLL_EXPORT void	SetAutoCloseDelay (ULong closeDelay);

DG_DLL_EXPORT ULong	GetAutoCloseDelay (void);


DG_DLL_EXPORT void	EnableNormalUpdate (void);

DG_DLL_EXPORT void	DisableNormalUpdate (void);


DG_DLL_EXPORT void	EnableToolTips (void);

DG_DLL_EXPORT void	DisableToolTips (void);

DG_DLL_EXPORT bool	IsToolTipsEnabled (void);

DG_DLL_EXPORT bool	DisplayContextHelp (void);

DG_DLL_EXPORT bool	ShowContextHelpWithAnchor (Int32 developerId, Int32 localId,
											   const GS::UniString& helpAnchor);


DG_DLL_EXPORT bool	RegisterAdditionalHelpLocation (Int32 developerId, Int32 localId,
													const IO::Location* helpLocation,
													const GS::UniString* localHelpFile,
                                                    const GS::UniString* addonHelpWebAddress,
													const IO::Location* tmpLocation,
													const GS::UniString* additionalHelpParameters);

DG_DLL_EXPORT bool	UnregisterAdditionalHelpLocation (Int32 developerId, Int32 localId);

DG_DLL_EXPORT bool	GetDynamicHelpStrings (GSResModule resModule, GSResID resID, short index,
										   GS::UniString* toolTipStr, GS::UniString* anchorStr);


DG_DLL_EXPORT void	SetUnit (const DGUnitData* uData);

DG_DLL_EXPORT void	GetUnit (DGUnitData* uData);

DG_DLL_EXPORT bool	IsMetricLengthUnit (void);

DG_DLL_EXPORT NativeRect	GetMonitorRectFromRect (const NativeRect& rect);


DG_DLL_EXPORT void	ResetDialogRectangles (void);


DG_DLL_EXPORT void	EnableRunnableMessageProcessing (void);

DG_DLL_EXPORT void	DisableRunnableMessageProcessing (void);

DG_DLL_EXPORT bool	IsRunnableMessageProcessingEnabled (void);


DG_DLL_EXPORT void	StoreUserDataToRegistry (const GS::UniString& keyName, const void* data, ULong size);

DG_DLL_EXPORT bool	RetrieveUserDataFromRegistry (const GS::UniString& keyName, void* data, ULong size);


template <typename T>
bool RetrieveUserDataFromRegistry (const GS::UniString& keyName, T* data)
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
		return RetrieveUserDataFromRegistry (keyName, data, sizeof (T));
	}
}


DG_DLL_EXPORT ULong	GetUserDataSizeInRegistry (const GS::UniString& keyName);


// --- Clipboard functions ---------------------------------------------------------------------------------------------

DG_DLL_EXPORT void	ClearSelection (void);

DG_DLL_EXPORT void	CopySelection (void);

DG_DLL_EXPORT void	CutSelection (void);

DG_DLL_EXPORT void	PasteClipboard (void);

DG_DLL_EXPORT void	UndoEditOperation (void);

DG_DLL_EXPORT void	RedoEditOperation (void);

DG_DLL_EXPORT short	CanUndoEditOperation (void);

DG_DLL_EXPORT short	CanRedoEditOperation (void);

DG_DLL_EXPORT void	ClearUndoEditOperation (void);


// --- Coordinate mapping functions ------------------------------------------------------------------------------------

DG_DLL_EXPORT void	MapFromApplicationToScreen (NativePoint* pt);

DG_DLL_EXPORT void	MapFromScreenToApplication (NativePoint* pt);


DG_DLL_EXPORT void	MapFromApplicationToScreen (NativeRect* rect);

DG_DLL_EXPORT void	MapFromScreenToApplication (NativeRect* rect);


// --- Cursor handling functions ---------------------------------------------------------------------------------------

DG_DLL_EXPORT void	HideCursor (void);

DG_DLL_EXPORT void	ShowCursor (void);

DG_DLL_EXPORT void	SetCursorPosition (const NativePoint& pt);



// --- Other TabPage functions -----------------------------------------------------------------------------------------

DG_DLL_EXPORT TabPage*	GetTabPageFromId (short dialId);

}	// namespace DG

#endif
