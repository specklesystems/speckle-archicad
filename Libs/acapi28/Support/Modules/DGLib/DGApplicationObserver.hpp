// *********************************************************************************************************************
// File:			DGApplicationObserver.hpp
//
// Description:		DG-based (windowed) application observer class
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	NZ
//
// SG compatible
// *********************************************************************************************************************

#ifndef DGAPPLICATONOBSERVER_HPP
#define DGAPPLICATONOBSERVER_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "DG.h"					// DG_DLL_EXPORT
#include "EventObserver.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class EventDispatcher;
}


// --- Class declarations ------------------------------------------------------

namespace DG {

// --- Application Observer class --------------------------------------------------------------------------------------

class DG_DLL_EXPORT ApplicationObserver: public GS::EventObserver
{
	friend class	EventDispatcher;		// To access private event processing methods

protected:
	virtual bool	ApplicationQuitRequested (void);

	virtual	void	ApplicationActivated (void);
	virtual	void	ApplicationDeactivated (void);

	virtual void	ApplicationMinimizeEntered (void);
	virtual	void	ApplicationMinimized (void);

	virtual void	ApplicationRestoreEntered (void);
	virtual	void	ApplicationRestored (void);

	virtual void	ApplicationMoveEntered (void);
	virtual void	ApplicationMoving (Int32 horMove, Int32 verMove);
	virtual void	ApplicationMoved (void);

	virtual void	ApplicationResizeEntered (void);
	virtual void	ApplicationResizing (Int32 leftResize, Int32 topResize, Int32 rightResize, Int32 bottomResize);
	virtual void	ApplicationResized (void);

	virtual void	ApplicationFullScreenChangeEntered (bool toFullScreen);
	virtual	void	ApplicationFullScreenChanged (bool toFullScreen);

	virtual	void	ApplicationScaleFactorChanged (void);

	virtual	void	OpenFilesRequested (const GS::Array<IO::Location>& files);
	virtual	void	PrintFilesRequested (const GS::Array<IO::Location>& files);
	virtual	bool	ReopenRequested (void);
	virtual	bool	CloseAllWindowsRequested (void);

	virtual	bool	PaletteDockOrientationChanged (const GS::Guid& paletteGuid, bool isDocked, bool horizontal);

	virtual void	ModalStateBegin (void);
	virtual void	ModalStateEnd (void);
	virtual void	ModalStateIncreased (void);
	virtual void	ModalStateDecreased (void);

	virtual void	MenuDidClose ();

	virtual void	ContextMenuOpened (void);
	virtual void	ContextMenuClosed (void);

public:
	ApplicationObserver ();
	virtual ~ApplicationObserver ();
};

}	// namespace DG

#endif
