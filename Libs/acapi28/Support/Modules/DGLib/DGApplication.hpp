// *********************************************************************************************************************
// File:			DGApplication.hpp
//
// Description:		DG-based (windowed) application class
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	MD, BM
//
// SG compatible
// *********************************************************************************************************************

#ifndef DGAPPLICATON_HPP
#define DGAPPLICATON_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "Array.hpp"
#include "Application.hpp"
#include "EventSource.hpp"

#include "DG.h"
#include "DGMenu.hpp"
#include "DGUtility.hpp"
#include "ModuleInfo.hpp"


// --- Predeclarations -------------------------------------------------------------------------------------------------

namespace IO {
	class Location;
}

namespace DG {
	class ModelessBase;
	class ApplicationImpl;
	class FrameWindow;
	class MenuBar;
	class Menu;
	class ToolBar;
	class ApplicationObserver;
	class EventDispatcher;
	class TrayImpl;
}

namespace LearningContent {
	class ITooltipController;
	class ICoachmarkController;
}


namespace DG {

// --- Application class -----------------------------------------------------------------------------------------------

class DG_DLL_EXPORT Application:	public GS::Application,
									protected GS::EventSource
{
	friend class			ApplicationImpl;
	friend class			EventDispatcher;		// To access private event processing methods

	// Typedefs
public:
	class DG_DLL_EXPORT CheckSharedLibraryVersionFilter {
	public:
		virtual bool IsOutOfCheck (const GS::ModuleInfo::ModuleInfoStructure& moduleInfoStructure) = 0;
		virtual ~CheckSharedLibraryVersionFilter ();
	};

	enum TrayBalloonIconId {
		NoIcon		= 0,
		InfoIcon	= 1,
		WarningIcon	= 2,
		ErrorIcon	= 3
	};

private:
	ApplicationImpl*		impl;

	FrameWindow*			frameWindow;
	MenuBar*				activeMenuBar;

	TrayImpl*				tray;

	LearningContent::ITooltipController*	learningTooltipController;
	LearningContent::ICoachmarkController*	coachmarkController;

	void					HandleMenuChoice (void);

	void					ReportSharedLibraryVersionMismach (const GS::UniString& moduleName);
	void					SharedLibraryVersionMismach (const GS::UniString& moduleName, bool largeBuildNumDiff = true);
	void					CheckSharedLibrariesVersions (CheckSharedLibraryVersionFilter* filter = nullptr);

protected:
	bool					SendQuitRequest (void);
	bool					IsCommandRegistered (const DG::CommandEvent& cmdEvent) const;

	// ... Overwritten virtual methods (GS::MainThread) ...................................................................

	virtual bool			Init (bool sharedLibraryCheckNeeded = false, CheckSharedLibraryVersionFilter* filter = nullptr);
	virtual void			Exit (void) override;

	// ... Overwritten virtual methods (GS::MessageTarget) ................................................................

	virtual void			ProcessSysMessage (GS::SysMessage* sysMsg) override;

	virtual void			IsBusy () override;
	virtual void			IsResponsive () override;

	// ... Overwriteable virtual methods ..................................................................................

	virtual void			ProcessSysMessage (GS::SysMessage* sysMsg, bool onlyUpdate);
	virtual FrameWindow*	CreateFrameWindow (void);

	virtual	bool			ApplicationQuitRequested (void);

	virtual	void			ApplicationActivated (void);
	virtual	void			ApplicationDeactivated (void);

	virtual void			ApplicationMinimizeEntered (void);
	virtual	void			ApplicationMinimized (void);

	virtual void			ApplicationRestoreEntered (void);
	virtual	void			ApplicationRestored (void);

	virtual void			ApplicationMoveEntered (void);
	virtual void			ApplicationMoving (Int32 horMove, Int32 verMove);
	virtual void			ApplicationMoved (void);

	virtual void			ApplicationResizeEntered (void);
	virtual void			ApplicationResizing (Int32 leftResize, Int32 topResize, Int32 rightResize, Int32 bottomResize);
	virtual void			ApplicationResized (void);

	virtual void			ApplicationFullScreenChangeEntered (bool toFullScreen);
	virtual	void			ApplicationFullScreenChanged (bool toFullScreen);

	virtual void			ApplicationScaleFactorChanged (void);

	virtual	bool			PaletteDockOrientationChanged (const GS::Guid& paletteGuid, bool isDocked, bool horizontal);

	virtual	void			OpenFilesRequested (const GS::Array<IO::Location>& files);
	virtual	void			PrintFilesRequested (const GS::Array<IO::Location>& files);
	virtual	bool			ReopenRequested (void);
	virtual	bool			CloseAllWindowsRequested (void);
	virtual void			MenuDidClose ();

public:
	static	void			GetMenuList	(GS::Array<Menu*>* menuList,
										 const GS::Array<MenuBar*>& menuBars,
										 const GS::Array<Menu*>& menus,
										 const GS::Array<ToolBar*>& toolBars,
										 const GS::Array<ContextMenu*>& contextMenus);

	static Application*		GetInstance ();

							Application ();
	virtual				   ~Application ();

	bool					PostCommandMessage (const Command& command, GS::Message::Priority priority = GS::Message::Normal);
	bool					PostCommandEvent (const CommandEvent& commandEvent, GS::Message::Priority priority = GS::Message::Normal);

	inline FrameWindow*		GetFrameWindow (void) const;
	bool					IsApplicationMinimized (void) const;

	void					SetActiveMenuBar (MenuBar* menuBar);
	inline MenuBar*			GetActiveMenuBar (void) const;

	bool					GetModifierKeyState (Key::Modifier modifier) const;
	bool					GetKeyState (Key::Modifier modifier, bool asyncRead = true) const;
	bool					GetKeyState (const Key::Code& key, bool asyncRead = true) const;
	bool					IsModifierPressed (void) const;
	bool					KeyboardBreakTest (void) const;

	bool					IsLeftButtonPressed (void) const;
	bool					IsRightButtonPressed (void) const;
	bool					IsWheelButtonPressed (void) const;

	bool					RegisterHelpLocation (const IO::Location* helpLocation = nullptr,
												  const GS::UniString* localHelpFile = nullptr,
												  const IO::Location* tmpLocation = nullptr,
												  const GS::UniString* additionalHelpParameters = nullptr);
	bool					UnregisterHelpLocation (void);

	void					RegisterHelpCenterFunction (const DGHelpCenterCallBack hcCallBack);
	void					OpenHelpCenterWithAnchor (const GS::UniString anchor);
	void					OpenOnlineOnlyHelpCenterWithAnchor (const GS::UniString& anchor);
	GS::UniString			GetWebHelpQueryUrlWithAnchor (const GS::UniString& anchor);

	void									SetLearningTooltipController (LearningContent::ITooltipController* tooltipController);
	LearningContent::ITooltipController*	GetLearningTooltipController ();

	void									SetCoachmarkController (LearningContent::ICoachmarkController* coachmarkController);
	LearningContent::ICoachmarkController*	GetCoachmarkController (void);

	void					CreateTrayWIN (const DG::Icon& trayIcon);
	void					CreateTrayMAC (const DG::Icon& trayBlackIcon, const DG::Icon& trayWhiteIcon);
	void					RemoveTray (void);
	bool					IsTrayCreated (void) const;
	void					SetTrayIconWIN (const DG::Icon& trayIcon);
	void					SetTrayIconMAC (const DG::Icon& trayBlackIcon, const DG::Icon& trayWhiteIcon);
	void					SetTrayToolTip (const GS::UniString& trayToolTipText);
	void					RemoveTrayToolTip (void);
	void					SetTrayMenu (DG::Menu& trayMenu);
	void					RemoveTrayMenu (void);
	void					ShowTrayBallon (const GS::UniString& title, const GS::UniString& text, TrayBalloonIconId iconId);
	void					ShowTrayBallon (const GS::UniString& title, const GS::UniString& text, const DG::Icon& icon);
	void					HideTrayBallon (void);

	void					Attach (ApplicationObserver& observer);
	void					Detach (ApplicationObserver& observer);

	virtual void			DisabledWindowClicked (DG::ModelessBase&);

	virtual	GS::UniString	GetDialogNameByGuid (const GS::Guid& guid);

	GS::UniString			GetOnboardingCMSHostUrl () const;
};


// --- Inlime implementations ------------------------------------------------------------------------------------------

inline FrameWindow*		Application::GetFrameWindow (void) const
{
	return frameWindow;
}


inline MenuBar*		Application::GetActiveMenuBar (void) const
{
	return activeMenuBar;
}

}	// namespace DG

#endif
