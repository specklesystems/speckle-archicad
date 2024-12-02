// *********************************************************************************************************************
// File:			DGPanelEventArgs.hpp
//
// Description:		Dialog manager event handling.
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Contact person:	SZM
// *********************************************************************************************************************

#ifndef DG_PANEL_EVENTARGS_HPP
#define DG_PANEL_EVENTARGS_HPP

#include "DGCommonEventArgs.hpp"

namespace DG {

class DG_DLL_EXPORT ResizeEventArg: public EventArg
{
public:
	short			subMessage = 0;				// DG_RSM_RESIZEENTER, DG_RSM_ABOUTTORESIZE, DG_RSM_RESIZING, DG_RSM_RESIZEEXIT
	bool			userResize = 0;				// True if the dialog is resizing by the user
	Int8			filler = 0;					//
	short			hGrow = 0;					// Change of the dialog width in pixels
	short			vGrow = 0;					// Change of the dialog height in pixels

	virtual ~ResizeEventArg();
};


class DG_DLL_EXPORT PanelTopStatusChangeEventArg: public EventArg
{
public:
	short			subMessage = 0;				// DG_TSM_TOPSTATUSLOST, DG_TSM_TOPSTATUSGAINED
	short			prevDialId = 0;				// Id of the dialog losing the top status
	short			nextDialId = 0;				// Id of the dialog gaining the top status
	bool			byUser = 0;					// True if the top status is changing by a user action

	virtual ~PanelTopStatusChangeEventArg ();
};


class DG_DLL_EXPORT PanelBackgroundPaintEventArg: public EventArg
{
public:
	void*			drawContext;			// GrafPtr (MAC) / HDC (Windows)
	short			subMessage;				// DG_PSM_PAINT, DG_PSM_POSTPAINT
	short			width;					// Width of the client area to paint
	short			height;					// Height of the client area to paint

	PanelBackgroundPaintEventArg ();
	virtual ~PanelBackgroundPaintEventArg ();
};


class DG_DLL_EXPORT DialogScaleChangeEventArg: public EventArg
{
public:
	double 			oldScale = 1.0;
	double 			newScale = 1.0;

	virtual ~DialogScaleChangeEventArg ();
};


typedef IntBasedEventArg	PanelIdleEventArg;
typedef IntBasedEventArg	PanelOpenEventArg;
typedef IntBasedEventArg	PanelCloseEventArg;
typedef IntBasedEventArg	PanelCloseRequestEventArg;
typedef IntBasedEventArg	PanelHotKeyEventArg;
typedef IntBasedEventArg	PanelActivateEventArg;


class PanelNotifyHandler
{
public:
	virtual ~PanelNotifyHandler ();

	virtual void	NotifyIdleEvent (const PanelIdleEventArg& /*eventArg*/) = 0;
	virtual void	NotifyOpenEvent (const PanelOpenEventArg& /*eventArg*/) = 0;
	virtual void	NotifyCloseEvent (const PanelCloseEventArg& /*eventArg*/) = 0;
	virtual bool	NotifyCloseRequestEvent (const PanelCloseRequestEventArg& /*eventArg*/) = 0;
	virtual bool	NotifyHotKeyEvent (const PanelHotKeyEventArg& /*eventArg*/) = 0;
	virtual void	NotifyActivateEvent (const PanelActivateEventArg& /*eventArg*/) = 0;
	virtual bool	NotifyBackgroundPaintEvent (const PanelBackgroundPaintEventArg& /*eventArg*/) = 0;
	virtual void	NotifyBackgroundPostPaintEvent (const PanelBackgroundPaintEventArg& /*eventArg*/) = 0;
	virtual void	NotifyResizeEvent (ResizeEventArg& /*eventArg*/) = 0;
	virtual void	NotifyTopStatusChangeEvent (const PanelTopStatusChangeEventArg& /*eventArg*/) = 0;
	virtual short	NotifyDragDropEvent (DragDropEventArg& /*eventArg*/) = 0;
	virtual void	NotifyDialogScaleChangEvent (const DialogScaleChangeEventArg& /*eventArg*/) = 0;
	virtual bool	NotifyContextMenuRequestEvent (ContextMenuEventArg& /*eventArg*/) = 0;
	virtual short	NotifyWheelEvent (const WheelEventArg& /*eventArg*/) = 0;
	virtual short	NotifyHelpRequestEvent (HelpEventArg& /*eventArg*/) = 0;
	virtual short	NotifyToolTipRequestEvent (HelpEventArg& /*eventArg*/) = 0;
	virtual short	NotifyUserDefinedEvent (const UserDefinedEventArg& /*eventArg*/) = 0;
};

}

#endif // DG_PANEL_EVENTARGS_HPP
