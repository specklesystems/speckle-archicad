// *****************************************************************************
// File:
//
// Description:
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		UD
//
// Contact person:	NZ
//
// SG compatible
// *****************************************************************************

#ifndef UDSTANDARDSTATUSBARPANELS_HPP
#define UDSTANDARDSTATUSBARPANELS_HPP

// --- Includes --------------------------------------------------------------------------------------------------------

#include "DGStatusBar.hpp"

#include "UDDefinitions.hpp"


// --- Class declarations ----------------------------------------------------------------------------------------------

namespace UD {


// --- DiskStatusBarPanel ----------------------------------------------------------------------------------------------

class UD_DLL_EXPORT DiskStatusBarPanel : public DG::StatusBarPanel
{
private:
	DG::StatusBarPanelIconItem*	icon;
	DG::StatusBarPanelTextItem*	text;

	char					currentDrive;

	GS::UniString			megaByteText;
	GS::UniString			gigaByteText;
	GS::UniString			diskInfoToolTipText;

private:
	void					NextDiskDrive (void);
	double					GetFreeDiskSpace (void);

public:
	DiskStatusBarPanel (DG::StatusBar& statusBar);
	virtual ~DiskStatusBarPanel ();

	virtual void			Clicked () override;
	virtual GS::UniString	GetHelp () override;

	void					Refresh ();
	void					SetDrive (const IO::Path&);
};


// --- MemoryStatusBarPanel --------------------------------------------------------------------------------------------

class UD_DLL_EXPORT MemoryStatusBarPanel : public DG::StatusBarPanel
{
private:
	enum MemoryInfoMode {
		TotalMemory,
		PhysicalMemory
	};

private:
	DG::StatusBarPanelIconItem*	icon;
	DG::StatusBarPanelTextItem*	text;

	MemoryInfoMode			memoryInfoMode;

	GS::UniString			megaByteText;
	GS::UniString			gigaByteText;
	GS::UniString			physicalMemoryToolTipText;
	GS::UniString			totalMemoryToolTipText;

private:
	double					GetFreeMemory (void);

public:
	MemoryStatusBarPanel (DG::StatusBar& statusBar);
	virtual ~MemoryStatusBarPanel ();

	virtual void			Clicked () override;
	virtual GS::UniString	GetHelp () override;

	void					Refresh ();
};


// --- GUIResourcesStatusBarPanel --------------------------------------------------------------------------------------

class UD_DLL_EXPORT GUIResourcesStatusBarPanel : public DG::StatusBarPanel
{
private:
	DG::StatusBarPanelIconItem*	icon;
	DG::StatusBarPanelTextItem*	text;

	GS::UniString	gdiInfoText;
	GS::UniString	usrInfoText;
	GS::UniString	toolTipText;
	GS::UniString	imgCountText;

public:
	GUIResourcesStatusBarPanel (DG::StatusBar& statusBar);
	virtual ~GUIResourcesStatusBarPanel ();

	virtual GS::UniString	GetHelp () override;

	void					Refresh ();
};

}	// namespace UD


#endif
