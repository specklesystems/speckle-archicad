// *****************************************************************************
// File:			DGDialog.hpp
//
// Description:		Dialog related classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	BM, AZS
//
// SG compatible
// *****************************************************************************

#ifndef DGDIALOG_HPP
#define DGDIALOG_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "DGPanel.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class TabControl;
}


namespace DG {

// --- Class declarations ------------------------------------------------------

// --- Dialog ------------------------------------------------------------------

class DG_DLL_EXPORT Dialog: public Panel
{
public:
	enum DialogType {
		Modal			= DG_DT_MODAL,
		Modeless		= DG_DT_MODELESS,
		Palette			= DG_DT_PALETTE
	};

	enum GrowType {
		NoGrow			= DG_DLG_NOGROW,
		HGrow			= DG_DLG_HGROW,
		VGrow			= DG_DLG_VGROW,
		HVGrow			= DG_DLG_HGROW | DG_DLG_VGROW
	};

	enum CloseType {
		NoClose			= DG_DLG_NOCLOSE,
		Close			= DG_DLG_CLOSE
	};

	enum MinimizeType {
		NoMinimize		= DG_DLG_NOMINIMIZE,
		Minimize		= DG_DLG_MINIMIZE
	};

	enum MaximizeType {
		NoMaximize		= DG_DLG_NOMAXIMIZE,
		Maximize		= DG_DLG_MAXIMIZE
	};

	enum CaptionType {
		TopCaption		= DG_DLG_TOPCAPTION,
		LeftCaption		= DG_DLG_LEFTCAPTION,
		NoCaption		= DG_DLG_NOCAPTION
	};

	enum FrameType {
		NormalFrame		= DG_DLG_NORMALFRAME,
		ThickFrame		= DG_DLG_THICKFRAME,
		NoFrame			= DG_DLG_NOFRAME
	};

	enum FixPoint {
		CenterPoint		= DG_CENTER,
		TopLeft			= DG_TOPLEFT,
		CenterLeft		= DG_CENTERLEFT,
		BottomLeft		= DG_BOTTOMLEFT,
		BottomCenter	= DG_BOTTOMCENTER,
		BottomRight		= DG_BOTTOMRIGHT,
		CenterRight		= DG_CENTERRIGHT,
		TopRight		= DG_TOPRIGHT,
		TopCenter		= DG_TOPCENTER
	};

	enum GrowBoxForm {
		Triangle		= DG_GROWBOX_TRIANGLE,
		Square			= DG_GROWBOX_SQUARE
	};

	enum SpecialFeatures {
		NothingSpecial	= 0,
		NoUpdate		= 1,
		FrameDialog		= 2
	};

	struct DialogId {
		short id;
		explicit DialogId (short dialId): id (dialId) {}
	};

	class DG_DLL_EXPORT AutoResizeBlockStore : public EventTarget
	{
		GS::Array<AutoResizeFunction> resizers;

	public:
		AutoResizeBlockStore 	(const AutoResizeBlockStore&) = delete;
		AutoResizeBlockStore& 	operator= (const AutoResizeBlockStore&) = delete;
		AutoResizeBlockStore		() = default;

		AutoResizeBlockStore&	operator+= (const AutoResizeFunction& resizer);
		void ResizeFunction (const Panel& panel, ResizeEventArg& ev);

		~AutoResizeBlockStore ();
	};

private:
	Dialog (const Dialog& dialog);					// Disable
	Dialog&		operator= (const Dialog& dialog);	// Disable

	AutoResizeBlockStore autoResizeBlockStore;
	bool temporary = false;

protected:
	explicit Dialog (DialogId dialId);
			 Dialog ();

			 Dialog (DialogType dialType, GSResModule resModule, short resId, GSResModule dialIconResModule);
			 Dialog (DialogType dialType, GSResModule resModule, short resId, GSResModule dialIconResModule, const GS::Guid& guid);

			 Dialog (DialogType dialType, const DG::NativePoint& position, short width, short height, const GS::Guid& guid,
					 GrowType growType = NoGrow, CloseType closeType = NoClose,
					 MinimizeType minimizeType = NoMinimize, MaximizeType maximizeType = NoMaximize,
					 CaptionType captionType = TopCaption, FrameType frameType = NormalFrame, SpecialFeatures specialFeatures = NothingSpecial);

	virtual void AddResizerFunction (const AutoResizeFunction& resizer) override;

public:
	const std::function<void (const Panel&, ResizeEventArg&)> ResizeStart;
	const std::function<void (const Panel&, ResizeEventArg&)> ResizeEnd;

	~Dialog ();

	DialogType	GetDialogType (void) const;
	virtual bool	IsDGDialog (void) const override;

	void*	GetWindow (void) const;

	void	Center (void);
	void	Move (short hDisp, short vDisp);
	void	Move (const DG::NativeUnit& hDisp, const DG::NativeUnit& vDisp);
	void	Resize (short hGrow, short vGrow, FixPoint fixPoint = TopLeft, bool keepOld = false);

	void		SetGrowType (GrowType growType);
	GrowType	GetGrowType (void) const;

	short	GetOriginalClientWidth (void) const;
	short	GetOriginalClientHeight (void) const;

	void	SetMinClientSize (short minWidth, short minHeight);
	void	SetMinClientWidth (short minWidth);
	void	SetMinClientHeight (short minHeight);

	short	GetMinClientWidth (void) const;
	short	GetMinClientHeight (void) const;

	void	SetClientPosition (const NativePoint& pt);
	void	SetClientPosition (const NativeUnit& hPos, const NativeUnit& vPos);

	void	SetClientRect (const NativeRect& rect, FixPoint fixPoint = TopLeft, bool keepOld = false);

	void	SetClientSize (short width, short height, FixPoint fixPoint = TopLeft, bool keepOld = false);
	void	SetClientWidth (short width, FixPoint fixPoint = TopLeft, bool keepOld = false);
	void	SetClientHeight (short height, FixPoint fixPoint = TopLeft, bool keepOld = false);

	NativePoint		GetClientPosition (void) const;

	NativeRect	GetClientRect (void) const;

	short	GetClientWidth (void) const;
	short	GetClientHeight (void) const;

	NativeUnit	GetOriginalFrameWidth (void) const;
	NativeUnit	GetOriginalFrameHeight (void) const;

	void	SetMinFrameSize (const NativeUnit& minWidth, const NativeUnit& minHeight);
	void	SetMinFrameWidth (const NativeUnit& minWidth);
	void	SetMinFrameHeight (const NativeUnit& minHeight);

	NativeUnit	GetMinFrameWidth (void) const;
	NativeUnit	GetMinFrameHeight (void) const;

	void	SetFramePosition (const NativePoint& pt);
	void	SetFramePosition (const NativeUnit& hPos, const NativeUnit& vPos);

	void	SetFrameRect (const NativeRect& rect, FixPoint fixPoint = TopLeft, bool keepOld = false);
	void	SetFrameSize (const NativeUnit& width, const NativeUnit& height, FixPoint fixPoint = TopLeft, bool keepOld = false);
	void	SetFrameWidth (const NativeUnit& width, FixPoint fixPoint = TopLeft, bool keepOld = false);
	void	SetFrameHeight (const NativeUnit& height, FixPoint fixPoint = TopLeft, bool keepOld = false);

	NativePoint	GetFramePosition (void) const;
	NativeRect	GetFrameRect (void) const;
	NativeUnit	GetFrameWidth (void) const;
	NativeUnit	GetFrameHeight (void) const;

	void	BeginMoveResizeItems (void);
	void	EndMoveResizeItems (void);

	void	SetTitle (const GS::UniString& title);
	GS::UniString GetTitle () const;

	void		SetIcon (const DG::Icon& icon);
	DG::Icon	GetIcon (void) const;

	void	EnableIdleEvent (bool sendForInactiveApp = false);

	void	EnableNormalUpdate (void);
	void	DisableNormalUpdate (void);

	void	SetPopupStyle (void);
	bool	HasPopupStyle (void) const;

	void	EnableGrowBox (void);
	void	DisableGrowBox (void);
	bool	IsGrowBoxEnabled (void) const;

	void	SetGrowBoxSize (short size);
	short	GetGrowBoxSize (void) const;

	void			SetGrowBoxForm (GrowBoxForm form);
	GrowBoxForm		GetGrowBoxForm (void) const;

	void	RegisterDragAndDrop (void);
	void	RevokeDragAndDrop (void);

	void	EnableDraw (void);
	void	DisableDraw (void);
	void	Redraw (void);

	void	SetCursorPosition (const Point& pt);

	void	KeepInScreen (void);

	bool	HasChangedDialogItems (void) const;
	void	ResetDialogItemChanges (void);

	template <typename... Args>
	void AutoResizeBlock (Args... args);

	virtual GSErrCode Store (GS::ObjectState& os) const override;
};


template <typename... Args>
void Dialog::AutoResizeBlock (Args... args)
{
	AddResizerFunction (ResizeStart);
	AutoResizeHelper (std::forward<Args>(args)...);
	AddResizerFunction (ResizeEnd);
	onResized.Add (&AutoResizeBlockStore::ResizeFunction, &autoResizeBlockStore);
}


// --- ModalDialog -------------------------------------------------------------

class DG_DLL_EXPORT ModalDialog: public Dialog
{
protected:
	explicit ModalDialog (DialogId dialId);
	ModalDialog () = default;

public:
	enum ModalResponse {
		Accept	= DG_OK,
		Cancel	= DG_CANCEL
	};

	explicit ModalDialog (GSResModule resModule, short resId, GSResModule dialIconResModule);
			 ModalDialog (const DG::NativePoint& position, short width, short height, const GS::Guid& guid, GrowType growType = NoGrow, CaptionType captionType = TopCaption,
						  FrameType frameType = NormalFrame);
			~ModalDialog ();

	bool	Invoke (void);
	void	Abort (void);

	void	PostCloseRequest (ModalResponse response);

	ModalDialog*	GetNextModalDialog (void) const;
	ModalDialog*	GetPrevModalDialog (void) const;

	virtual GSErrCode Store (GS::ObjectState& os) const override;
};


// --- ModelessBase ------------------------------------------------------------

class DG_DLL_EXPORT ModelessBase: public Dialog
{
protected:
	ModelessBase () = default;
	explicit ModelessBase (DialogId dialId);

			 ModelessBase (DialogType dialType, GSResModule resModule, short resId, GSResModule dialIconResModule);
			 ModelessBase(DialogType dialType, GSResModule resModule, short resId, GSResModule dialIconResModule, const GS::Guid& guid);

			 ModelessBase (DialogType dialType, const DG::NativePoint& position, short width, short height, const GS::Guid& guid,
						   GrowType growType = NoGrow, CloseType closeType = NoClose,
						   MinimizeType minimizeType = NoMinimize, MaximizeType maximizeType = NoMaximize,
						   CaptionType captionType = TopCaption, FrameType frameType = NormalFrame, SpecialFeatures specialFeatures = NothingSpecial);

public:
	enum DialogStatus {
		Normal		= DG_DS_NORMAL,
		Enabled		= DG_DS_ENABLED,
		Disabled	= DG_DS_DISABLED,
		Edited		= DG_DS_EDITED
	};

	enum {
		First		= DG_DF_FIRST,
		Last		= DG_DF_LAST
	};

	~ModelessBase ();

	void	BeginEventProcessing (void);
	void	EndEventProcessing (void);
	void	SendCloseRequest (void);

	void	BringToFront (void);
	void	SendToBack (void);

	void	Show (short refDialId = First);
	void	Hide (void);
	void	SetVisibility (bool show);
	bool	IsVisible (void) const;

	void	Activate (void);
	bool	IsActive (void) const;

	void			SetStatus (DialogStatus status);
	DialogStatus	GetStatus (void) const;

	virtual GSErrCode Store (GS::ObjectState& os) const override;
};


// --- ModelessDialog ----------------------------------------------------------

class DG_DLL_EXPORT ModelessDialog: public ModelessBase
{
protected:
	explicit ModelessDialog (DialogId dialId);
	explicit ModelessDialog () = default;

public:
	enum DialogState {
		Maximized	= DG_DST_MAXIMIZED,
		Minimized	= DG_DST_MINIMIZED,
		Restored	= DG_DST_RESTORED
	};

	enum DockState {
		Docked		= DG_DKS_DOCKED,
		Undocked	= DG_DKS_UNDOCKED
	};

	explicit ModelessDialog (GSResModule resModule, short resId, GSResModule dialIconResModule);
	explicit ModelessDialog(GSResModule resModule, short resId, GSResModule dialIconResModule, const GS::Guid&);
			 ModelessDialog (const DG::NativePoint& position, short width, short height, const GS::Guid& guid, GrowType growType = NoGrow, CloseType closeType = NoClose,
							 MinimizeType minimizeType = NoMinimize, MaximizeType maximizeType = NoMaximize,
							 CaptionType captionType = TopCaption, FrameType frameType = NormalFrame, SpecialFeatures specialFeatures = NothingSpecial);
			~ModelessDialog ();

	void	SendBehind (const ModelessDialog& behindModeless);

	ModelessDialog*		GetNextModelessDialog (void) const;
	ModelessDialog*		GetPrevModelessDialog (void) const;
	ModelessDialog*		GetNextVisibleModelessDialog (void) const;
	ModelessDialog*		GetPrevVisibleModelessDialog (void) const;

	NativePoint		GetRestoredClientPosition (void) const;
	short			GetRestoredClientWidth (void) const;
	short			GetRestoredClientHeight (void) const;

	NativePoint		GetRestoredFramePosition (void) const;
	NativeRect		GetRestoredFrameRect (void) const;
	NativeUnit		GetRestoredFrameWidth (void) const;
	NativeUnit		GetRestoredFrameHeight (void) const;

	void	Maximize (bool beforeDock = false);
	void	Minimize (void);
	void	Restore (void);
	void	SetState (DialogState state, bool beforeDock = false);

	bool			IsMaximizedState (void) const;
	bool			IsMinimizedState (void) const;
	bool			IsRestoredState (void) const;
	DialogState		GetState (void) const;

	void		Dock (void);
	void		Undock (void);
	bool		IsDocked (void) const;
	void		SetDockState (DockState dockState);
	DockState	GetDockState (void) const;

	virtual GSErrCode Store (GS::ObjectState& os) const override;

#ifdef macintosh
	void		UpdateTrackingArea (void);
#endif

};


// --- Palette -----------------------------------------------------------------

class DG_DLL_EXPORT Palette: public ModelessBase
{
protected:
	explicit Palette (DialogId dialId);
	Palette () = default;

public:

	explicit Palette (GSResModule resModule, short resId, GSResModule dialIconResModule);
	explicit Palette (GSResModule resModule, short resId, GSResModule dialIconResModule, const GS::Guid& guid);
			 Palette (const DG::NativePoint& position, short width, short height, const GS::Guid& guid, GrowType growType = NoGrow, CloseType closeType = NoClose,
					  CaptionType captionType = TopCaption, FrameType frameType = NormalFrame, SpecialFeatures specialFeatures = NothingSpecial);
			~Palette ();

	void	SendBehind (const Palette& behindPalette);

	Palette*	GetNextPalette (void) const;
	Palette*	GetPrevPalette (void) const;
	Palette*	GetNextVisiblePalette (void) const;
	Palette*	GetPrevVisiblePalette (void) const;

	short		DisableDock (short orientationFlag);

	void		Dock (void);
	void		UnDock (void);

	bool		IsDocked (void) const;

	short		GetCaptionType (void) const;

	virtual GSErrCode Store (GS::ObjectState& os) const;
};

}	// namespace DG

#endif
