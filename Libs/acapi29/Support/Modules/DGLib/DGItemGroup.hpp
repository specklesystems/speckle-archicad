// *****************************************************************************
// File:			DGItemGroup.hpp
//
// Description:		ItemGroup classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	AZS, BM
//
// SG compatible
// *****************************************************************************

#ifndef DGITEMGROUP_HPP
#define DGITEMGROUP_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "DG.h"


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class Panel;
	class Item;
}


// --- Class declarations ------------------------------------------------------

namespace DG {

// --- Class ItemGroup ---------------------------------------------------------

class DG_DLL_EXPORT ItemGroup
{
private:
	Item**	items;

public:
	explicit ItemGroup (Item** group);
	virtual ~ItemGroup ();

	void	Enable (void);
	void	Disable (void);
	void	SetStatus (bool enable);

	void	Show (void);
	void	Hide (void);
	void	SetVisibility (bool show);

	void	Move (short hDisp, short vDisp);
	void	Resize (short hGrow, short vGrow);
	void	MoveAndResize (short hDisp, short vDisp, short hGrow, short vGrow);

	void	Validate (void);
	void	Invalidate (void);
	void	Redraw (void);

	void	ResetModified (void);
};


// --- RadioItemGroup ----------------------------------------------------------

class DG_DLL_EXPORT RadioItemGroup
{
private:
	short	panelId;
	short	groupId;

public:
			RadioItemGroup (const Panel& panel, short group);
	virtual ~RadioItemGroup ();

	Item*	GetSelectedRadio (void) const;
};

}	// namespace DG

#endif
