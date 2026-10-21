// *********************************************************************************************************************
// File:			DGFrameWindow.hpp
//
// Description:		FrameWindow class of DG based applications
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	MD, BM
//
// SG compatible
// *********************************************************************************************************************

#ifndef DGFRAMEWINDOW_HPP
#define DGFRAMEWINDOW_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "DG.h"
#include "DGStatusBar.hpp"
#include "DGTabBar.hpp"
#include "DGUtility.hpp"
#include "Location.hpp"
#include "UniString.hpp"


// --- Predeclarations -------------------------------------------------------------------------------------------------

namespace DG {
	class Application;
	class FrameWindow;
	class FrameWindowImpl;
	class ModelessBase;
}


// --- Class declarations ----------------------------------------------------------------------------------------------

namespace DG {

// --- FrameWindow -----------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT FrameWindow
{
public:
	enum ShowState {
		Minimized	=	1,
		Maximized	=	2,
		Restored	=	3
	};

	enum TabBarStatus	{
		TabBarNormal	=	1,
		TabBarEnabled	=	2
	};

private:
	FrameWindowImpl*		impl;
	Application*			application;

	bool					visible;
	GS::UniString			representedFile;
	GS::UniString			title;
	Icon					icon;

	GS::UniString			statusText;
	StatusBar*				statusBar;

	bool					fullScreenMode;

	FrameWindow	(const FrameWindow& source);					// disabled

public:
	explicit		FrameWindow (Application* application);
	virtual		   ~FrameWindow ();

	bool			Init (void);
	void			Exit (void);
	Application*	GetApplication (void) const;

	void*			GetWindow	(void) const;
	NativeRect		GetWorkAreaRect (bool returnGlobalCoords = false) const;	// Retrieves work area rect either with screen or global origin
	void			SetSize (const Int32 w, const Int32 h);
	void			SetPositionToCenter (void);

	double			GetScaleFactor (void) const;

	void			Show (void);
	void			Hide (void);
	void			SetVisibility (bool show);
	bool			IsVisible (void) const;

	ShowState		GetShowState (void) const;
	void			SetShowState (ShowState showState);

	void			SetRepresentedFile	(const GS::UniString& filePath);
	GS::UniString	GetRepresentedFile	(void) const;

	void			SetTitle (const GS::UniString& title);
	GS::UniString	GetTitle (void) const;

	void			SetIcon (const Icon& icon);
	Icon			GetIcon (void) const;

	void			CreateStatusBar	(void);
	StatusBar*		GetStatusBar	(void);

	void			CreateTabBar (void);
	void			DestroyTabBar (void);
	DG::TabBar*		GetTabBarControl (void);
	void			SetTabBarStatus (TabBarStatus);

	short			GetTabBarHeight (void);
	void			SetTabBarHeight (short height);

	void			SwitchToFullScreenMode (void);
	void			SwitchToNormalScreenMode (void);

	void			StartFlashWindow (void);
	void			StopFlashWindow (void);

	virtual void	ContextMenuRequested (const NativePoint& coord);

	virtual bool	SwitchWindow (Int32 command);

	void			BringToForeground ();
	void			AllowSetForegroundWindow (Int32 processId);

	void			SetSingleWindowMode	(bool singleWindow);
	bool			IsSingleWindowMode	(void) const;
};

}	// namespace DG

#endif
