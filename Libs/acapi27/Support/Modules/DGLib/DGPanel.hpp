// *****************************************************************************
// File:			DGPanel.hpp
//
// Description:		Panel related classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	BM, MB
// *****************************************************************************

#ifndef DGPANEL_HPP
#define DGPANEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Event.hpp"
#include "EventObserver.hpp"
#include "EventSource.hpp"
#include "UniString.hpp"

#include "DGUtility.hpp"

#include "DGPanelEventArgs.hpp"
#include "DGEventNotifier.hpp"

#include "DGAutoResizer.hpp"

// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class Panel;
	class Item;
	class EventDispatcher;
}


namespace DG {

// --- Class declarations ------------------------------------------------------

// --- PanelEvent --------------------------------------------------------------

class DG_DLL_EXPORT PanelEvent: public GS::Event
{
friend class Panel;							// To access protected constructor

protected:
	PanelEvent (Panel* source, const DG::EventArg& msgData);

public:
	~PanelEvent ();

	Panel*	GetSource (void) const;
};


// --- PanelCloseEvent ---------------------------------------------------------

class DG_DLL_EXPORT PanelCloseEvent: public PanelEvent
{
friend class Panel;							// To access protected constructor

private:
	short	retCode;

protected:
	PanelCloseEvent (Panel* source, const DG::EventArg& msgData);

public:
	~PanelCloseEvent ();

	bool	IsAccepted (void) const;
	bool	IsCancelled (void) const;
};


// --- PanelCloseRequestEvent --------------------------------------------------

class DG_DLL_EXPORT PanelCloseRequestEvent: public PanelEvent
{
friend class Panel;							// To access protected constructor

private:
	short	retCode;

protected:
	PanelCloseRequestEvent (Panel* source, const DG::EventArg& msgData);

public:
	~PanelCloseRequestEvent ();

	bool	IsAccepted (void) const;
	bool	IsCancelled (void) const;
};


// --- PanelContextMenuEvent ---------------------------------------------------

class DG_DLL_EXPORT PanelContextMenuEvent: public PanelEvent
{
friend class Panel;							// To access protected constructor

private:
	const DG::ContextMenuEventArg*	contextMenuMsgData;

protected:
	PanelContextMenuEvent (Panel* source, const DG::EventArg& msgData);

public:
	~PanelContextMenuEvent ();

	Panel*	GetPanel (void) const;
	Item*	GetItem (void) const;

	NativePoint	GetPosition (void) const;
};


// --- PanelDropTargetEvent ----------------------------------------------------

class DG_DLL_EXPORT PanelDropTargetEvent: public PanelEvent,
										  public DropTargetEventProperty
{
friend class Panel;							// To access protected constructor

protected:
	PanelDropTargetEvent (Panel* source, const DG::EventArg& msgData);

public:
	~PanelDropTargetEvent ();
};


// --- PanelHelpEvent ----------------------------------------------------------

class DG_DLL_EXPORT PanelHelpEvent: public PanelEvent
{
friend class Panel;							// To access protected constructor

private:
	const DG::HelpEventArg*	itemHelpMsgData;

protected:
	PanelHelpEvent (Panel* source, const DG::EventArg& msgData);

public:
	~PanelHelpEvent ();

	Item*	GetItem (void) const;
};


// --- PanelHotKeyEvent --------------------------------------------------------

class DG_DLL_EXPORT PanelHotKeyEvent: public PanelEvent
{
friend class Panel;							// To access protected constructor

private:
	short	keyId;

protected:
	PanelHotKeyEvent (Panel* source, const DG::EventArg& msgData);

public:
	~PanelHotKeyEvent ();

	short	GetKeyId (void) const;
};


// --- PanelIdleEvent ----------------------------------------------------------

class DG_DLL_EXPORT PanelIdleEvent: public PanelEvent
{
friend class Panel;							// To access protected constructor

protected:
	PanelIdleEvent (Panel* source, const DG::EventArg& msgData);

public:
	~PanelIdleEvent ();
};


// --- PanelOpenEvent ----------------------------------------------------------

class DG_DLL_EXPORT PanelOpenEvent: public PanelEvent
{
friend class Panel;							// To access protected constructor

private:
	short	initPosition;

protected:
	PanelOpenEvent (Panel* source, const DG::EventArg& msgData);

public:
	~PanelOpenEvent ();

	bool	IsSavedPosition (void) const;
	bool	IsDefaultPosition (void) const;
	bool	IsAdjustedPosition (void) const;
};


// --- PanelResizeEvent --------------------------------------------------------

class DG_DLL_EXPORT PanelResizeEvent: public PanelEvent
{
friend class Panel;							// To access protected constructor

private:
	const DG::ResizeEventArg*	resizeMsgData;

protected:
	PanelResizeEvent (Panel* source, const DG::EventArg& msgData);

public:
	~PanelResizeEvent ();

	bool	IsUserResize (void) const;

	short	GetHorizontalChange (void) const;
	short	GetVerticalChange (void) const;
};


// --- PanelScaleChangeEvent ---------------------------------------------------

class DG_DLL_EXPORT PanelScaleChangeEvent: public PanelEvent
{
friend class Panel;

private:
	const DG::DialogScaleChangeEventArg* scaleMsgData;

protected:
	PanelScaleChangeEvent (Panel* source, const DG::EventArg& msgData);

public:
	~PanelScaleChangeEvent ();

	double	GetOldScale (void) const;
	double	GetNewScale (void) const;
};


// --- PanelMoveEvent ----------------------------------------------------------

class DG_DLL_EXPORT PanelMoveEvent: public PanelEvent
{
friend class EventDispatcher;				// To access protected constructor

protected:
	PanelMoveEvent (Panel* source);

public:
	~PanelMoveEvent ();
};


// --- PanelTopStatusEvent -----------------------------------------------------

class DG_DLL_EXPORT PanelTopStatusEvent: public PanelEvent
{
friend class Panel;							// To access protected constructor

private:
	const DG::PanelTopStatusChangeEventArg* topStatusMsgData;

protected:
	PanelTopStatusEvent (Panel* source, const DG::EventArg& msgData);

public:
	~PanelTopStatusEvent ();

	Panel*	GetPreviousTopStatusPanel (void) const;
	Panel*	GetNextTopStatusPanel (void) const;

	bool	ByUser (void) const;
};


// --- PanelWheelEvent ---------------------------------------------------------

class DG_DLL_EXPORT PanelWheelEvent: public PanelEvent
{
friend class Panel;							// To access protected constructor

protected:
	const DG::WheelEventArg*		wheelMsgData;

	PanelWheelEvent (Panel* source, const DG::EventArg& msgData);

public:
	~PanelWheelEvent ();

	Item*	GetItem (void) const;
};


// --- PanelWheelTrackEvent ----------------------------------------------------

class DG_DLL_EXPORT PanelWheelTrackEvent: public PanelWheelEvent
{
friend class Panel;							// To access protected constructor

protected:
	PanelWheelTrackEvent (Panel* source, const DG::EventArg& msgData);

public:
	~PanelWheelTrackEvent ();

	short	GetXTrackValue (void) const;
	short	GetYTrackValue (void) const;

	Point	GetMouseOffset (void) const;

	bool	IsCommandPressed (void) const;
	bool	IsOptionPressed (void) const;
	bool	IsShiftPressed (void) const;
};


// --- PanelBackgroundPaintEvent -----------------------------------------------

class DG_DLL_EXPORT PanelBackgroundPaintEvent: public PanelEvent
{
friend class Panel;							// To access protected constructor

private:
	const DG::PanelBackgroundPaintEventArg* paintMsgData;

protected:
	PanelBackgroundPaintEvent (Panel* source, const DG::EventArg& msgData);

public:
	~PanelBackgroundPaintEvent ();

	void*	GetDrawContext (void) const;

	short	GetWidth (void) const;
	short	GetHeight (void) const;
};


// --- PanelActivateEvent -----------------------------------------------

class DG_DLL_EXPORT PanelActivateEvent : public PanelEvent
{
	friend class Panel;							// To access protected constructor

protected:
	PanelActivateEvent (Panel* source, const DG::EventArg& msgData);
public:
	~PanelActivateEvent ();
};


enum InputStatus {
	InputStatus_Enabled,
	InputStatus_Disabled,
	InputStatus_Default
};


// --- PanelObserver -----------------------------------------------------------

class DG_DLL_EXPORT PanelObserver: public GS::EventObserver
{
friend class Panel;						// To access protected observer methods
friend class EventDispatcher;			// To access protected observer methods


protected:
	virtual void	PanelClosed (const PanelCloseEvent& ev);
	virtual	void	PanelCloseRequested (const PanelCloseRequestEvent& ev, bool* accepted);
	virtual	void	PanelContextHelpRequested (const PanelHelpEvent& ev, GS::UniString* contextHelpAnchor);
	virtual	void	PanelContextMenuRequested (const PanelContextMenuEvent& ev, bool* needHelp, bool* processed);
	virtual void	PanelDragEntered (const PanelDropTargetEvent& ev, DragDrop::Effect* effect, bool* handleEvent);
	virtual void	PanelDragEntered (const PanelDropTargetEvent& ev, DragDrop::Effect* effect, bool* handleEvent,
									  bool* rightDragMenu);
	virtual void	PanelDragMoved (const PanelDropTargetEvent& ev, DragDrop::Effect* effect, bool* handleEvent);
	virtual void	PanelDragLeft (const PanelDropTargetEvent& ev, bool* handleEvent);
	virtual void	PanelDropped (const PanelDropTargetEvent& ev, DragDrop::Effect* effect, bool* handleEvent);
	virtual void	PanelHotkeyPressed (const PanelHotKeyEvent& ev, bool* processed);
	virtual void	PanelIdle (const PanelIdleEvent& ev);
	virtual void	PanelOpened (const PanelOpenEvent& ev);
	virtual void	PanelResizeEntered (const PanelResizeEvent& ev);
	virtual void	PanelResizing (const PanelResizeEvent& ev, Point* growValues);
	virtual void	PanelResized (const PanelResizeEvent& ev);
	virtual void	PanelResizeExited (const PanelResizeEvent& ev);
	virtual void	PanelMoveEntered (const PanelMoveEvent& ev);
	virtual void	PanelMoving (const PanelMoveEvent& ev);
	virtual void	PanelMoved (const PanelMoveEvent& ev);
	virtual void	PanelMoveExited (const PanelMoveEvent& ev);
	virtual void 	PanelScaleChanged (const PanelScaleChangeEvent& ev);
	virtual	void	PanelToolTipRequested (const PanelHelpEvent& ev, GS::UniString* toolTipText);
	virtual void	PanelTopStatusGained (const PanelTopStatusEvent& ev);
	virtual void	PanelTopStatusLost (const PanelTopStatusEvent& ev);
	virtual	void	PanelWheelTrackEntered (const PanelWheelEvent& ev, bool* processed);
	virtual	void	PanelWheelTracked (const PanelWheelTrackEvent& ev, bool* processed);
	virtual	void	PanelWheelTrackExited (const PanelWheelEvent& ev, bool* processed);
	virtual	void	PanelBackgroundPaint (const PanelBackgroundPaintEvent& ev, bool* processed);
	virtual	void	PanelBackgroundPostPaint (const PanelBackgroundPaintEvent& ev);
	virtual void	PanelActivated (const PanelActivateEvent& ev);
	virtual	void	PanelChangeRegistrationRequested (const Item* item, bool* allowRegistration);

	virtual InputStatus	IsInputEnabled (const Item& item) const;
};


// --- Panel -------------------------------------------------------------------

class DG_DLL_EXPORT Panel: public GS::EventSource,
						   public DG::PanelNotifyHandler,
						   public DG::EventTarget,
						   public DG::DefaultEventTargetProvider
{
friend class ItemChangeTracker;		// To access private event processing methods
friend class EventDispatcher;		// To access private event processing methods
friend class Dialog;				// To set private data member panelId
friend class TabPage;				// To set private data member panelId
friend class SystemDialogPanel;		// To set private data member panelId
friend class PanelCtoCppBridge;		// To set private data member panelId
friend class PanelResizeBlock;

private:
	short	panelId;
	bool	inResize = false;
	bool	hasAutoResizeSupport = false;

	GS::Array<GS::Ref<AutoResizer>>	resizers;

	virtual short	ProcessCloseEvent (const DG::EventArg& msgData);
	virtual short	ProcessCloseRequestEvent (const DG::EventArg& msgData);
	virtual	short	ProcessContextMenuEvent (DG::EventArg& msgData);
	virtual short	ProcessDragDropEvent (DG::EventArg& msgData);
	virtual short	ProcessHotKeyEvent (const DG::EventArg& msgData);
	virtual short	ProcessIdleEvent (const DG::EventArg& msgData);
	virtual	short	ProcessItemHelpEvent (DG::EventArg& msgData);
	virtual short	ProcessOpenEvent (const DG::EventArg& msgData);
	virtual short	ProcessResizeEvent (DG::EventArg& msgData);
	virtual short 	ProcessScaleChangeEvent (const DG::EventArg& msgData);
	virtual short	ProcessTopStatusEvent (const DG::EventArg& msgData);
	virtual	short	ProcessWheelTrackEvent (const DG::EventArg& msgData);
	virtual	short	ProcessBackgroundPaintEvent (const DG::EventArg& msgData);
	virtual short	ProcessActivateEvent (const DG::EventArg& msgData);
	virtual void	ProcessChangeEventRegistration (const Item* item);

	virtual void	NotifyIdleEvent (const PanelIdleEventArg& eventArg) override;
	virtual void	NotifyOpenEvent (const PanelOpenEventArg& eventArg) override;
	virtual void	NotifyCloseEvent (const PanelCloseEventArg& eventArg) override;
	virtual bool	NotifyCloseRequestEvent (const PanelCloseRequestEventArg& eventArg) override;
	virtual void	NotifyActivateEvent (const PanelActivateEventArg& eventArg) override;
	virtual bool	NotifyHotKeyEvent (const PanelHotKeyEventArg& eventArg) override;
	virtual bool	NotifyBackgroundPaintEvent (const PanelBackgroundPaintEventArg& eventArg) override;
	virtual void	NotifyBackgroundPostPaintEvent (const PanelBackgroundPaintEventArg& eventArg) override;
	virtual void	NotifyResizeEvent (ResizeEventArg& eventArg) override;
	virtual void	NotifyTopStatusChangeEvent (const PanelTopStatusChangeEventArg& eventArg) override;
	virtual short	NotifyDragDropEvent (DragDropEventArg& eventArg) override;
	virtual void	NotifyDialogScaleChangEvent (const DialogScaleChangeEventArg& eventArg) override;
	virtual bool	NotifyContextMenuRequestEvent (ContextMenuEventArg& eventArg) override;
	virtual short	NotifyWheelEvent (const WheelEventArg& eventArg) override;
	virtual short	NotifyHelpRequestEvent (HelpEventArg& eventArg) override;
	virtual short	NotifyToolTipRequestEvent (HelpEventArg& eventArg) override;
	virtual short	NotifyUserDefinedEvent (const UserDefinedEventArg& eventArg) override;

	Panel (const Panel& panel);				// Disable
	Panel&	operator= (const Panel& panel);	// Disable

	void 	InitNotifiers ();

protected:
	const Panel&	GetReference (void) const;

	typedef std::function<void (const Panel&, ResizeEventArg&)> AutoResizeFunction;

	virtual void AddResizerFunction (const AutoResizeFunction& resizer);

	void AutoResizeHelper ();

	template <typename... Args>
	void AutoResizeHelper(GS::Ref<AutoResizer> resizer, Args... args);

	template <typename... Args>
	void AutoResizeHelper(const AutoResizeFunction resizer, Args... args);

public:
			 Panel ();
	virtual	~Panel ();

	EventNotifier<Panel, const PanelIdleEventArg> onIdle;
	EventNotifier<Panel, const PanelOpenEventArg> onOpened;
	EventNotifier<Panel, const PanelCloseEventArg> onClosed;
	EventNotifier<Panel, const PanelCloseRequestEventArg, bool, false> onCloseRequested;
	EventNotifier<Panel, const PanelActivateEventArg> onActivated;
	EventNotifier<Panel, const PanelHotKeyEventArg, bool, false> onHotKeyPressed;

	EventNotifier<Panel, const PanelBackgroundPaintEventArg, bool, false> onBackgroundPaint;
	EventNotifier<Panel, const PanelBackgroundPaintEventArg> onBackgroundPostPaint;

	EventNotifier<Panel, ResizeEventArg> onResized;
	EventNotifier<Panel, ResizeEventArg> onResizeEntered;
	EventNotifier<Panel, ResizeEventArg> onWillResize;
	EventNotifier<Panel, ResizeEventArg> onResizeExited;

	EventNotifier<Panel, const PanelTopStatusChangeEventArg> onTopStatusGained;
	EventNotifier<Panel, const PanelTopStatusChangeEventArg> onTopStatusLost;

	EventNotifier<Panel, DragDropEventArg, short> onDragEntered;
	EventNotifier<Panel, DragDropEventArg, short> onDragMoved;
	EventNotifier<Panel, DragDropEventArg, short> onDragLeft;
	EventNotifier<Panel, DragDropEventArg, short> onDragDropped;

	EventNotifier<Panel, const DialogScaleChangeEventArg> onScaleChanged;
	EventNotifier<Panel, ContextMenuEventArg, bool, false> onContextMenuRequested;

	EventNotifier<Panel, const WheelEventArg, short> onWheelEntered;
	EventNotifier<Panel, const WheelEventArg, short> onWheelTracked;
	EventNotifier<Panel, const WheelEventArg, short> onWheelExited;

	EventNotifier<Panel, HelpEventArg, short> onHelpRequested;
	EventNotifier<Panel, HelpEventArg, short> onToolTipRequested;

	EventNotifier<Panel, const UserDefinedEventArg, short> onUserDefinedEvent;

	void	Attach (PanelObserver& observer);
	void	Detach (PanelObserver& observer);

	bool	IsValid (void) const;
	bool	IsExist (void) const;

	short	GetId (void) const;
	short	GetResourceId (void) const;

	void			SetResourceModule (GSResModule resModule);
	GSResModule		GetResourceModule (void) const;

	GS::UniString	GetAnchorString (void) const;

	short	GetWidth (void) const;
	short	GetHeight (void) const;

	void	ClearFocus (void);

	void	ShowItems (void);
	void	HideItems (void);
	void	SetItemVisibility (bool show);
	void	MaskItemsVisibility (bool mask);

	void	EnableItems (void);
	void	DisableItems (void);
	void	SetItemStatus (bool enable);

	void	MoveItems (short hDisp, short vDisp);

	void	RedrawItems (void);

	short	RegisterHotKey (Key::Special keyCode, Key::Modifier mod1 = Key::NoModifier,
							Key::Modifier mod2 = Key::NoModifier, Key::Modifier mod3 = Key::NoModifier);

	short	RegisterHotKey (short keyCode, Key::Modifier mod1 = Key::NoModifier,
							Key::Modifier mod2 = Key::NoModifier, Key::Modifier mod3 = Key::NoModifier);

	void	UnregisterHotKey (short hotKeyId);
	void	EnableHotKeys (void);
	void	DisableHotKeys (void);

	void	EnableDragAndDropEvent (void);

	void	EnableInputFiltering (void);
	void	DisableInputFiltering (void);

	double	GetScaleFactor (void) const;

	short	GetItemCount (void) const;
	virtual Item*	GetItem (short index) const;

	virtual bool	IsDGDialog (void) const;
	virtual bool	IsSystemDialog (void) const;
	virtual	bool	IsTabPage (void) const;

	template <typename... Args>
	void	AutoResize (Args... args);

	bool	IsInResize () const;
	bool	HasAutoResizeSupport () const;

	virtual NewDisplay::NativeImage		CaptureToNativeImage (bool withFrame = false) const;

	virtual EventTarget*	GetDefaultEventTarget () const override;

	AppearanceType	GetAppearanceType () const;

	virtual GSErrCode Store (GS::ObjectState& os) const;
};

template <typename... Args>
void Panel::AutoResizeHelper (GS::Ref<AutoResizer> resizer, Args... args)
{
	resizers.Push (resizer);
	auto& onResize = resizer->GetResizeFunction ();
	if (onResize)
		AddResizerFunction (onResize);
	auto& onResizeEnteredFunction = resizer->GetResizeEnteredFunction ();
	if (onResizeEnteredFunction)
		onResizeEntered += onResizeEnteredFunction;
	auto& onResizeExitedFunction = resizer->GetResizeExitedFunction ();
	if (onResizeExitedFunction)
		onResizeExited += onResizeExitedFunction;
	AutoResizeHelper (std::forward<Args>(args)...);
}

template <typename... Args>
void Panel::AutoResizeHelper (const AutoResizeFunction resizer, Args... args)
{
	AddResizerFunction (resizer);
	AutoResizeHelper (std::forward<Args>(args)...);
}

template <typename... Args>
void Panel::AutoResize (Args... args)
{
	AutoResizeHelper (std::forward<Args>(args)...);
}

}	// namespace DG

#endif
