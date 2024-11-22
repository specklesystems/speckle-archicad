#ifndef DG_INPUT_FILTER__H
#define DG_INPUT_FILTER__H

#pragma once

#include "DG.h"
#include "DGItem.hpp"
#include "DGPanel.hpp"
#include "DGIterators.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace DG {
namespace InputFilter {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DG_DLL_EXPORT void			SetDefaultInputStatus (InputStatus status);
DG_DLL_EXPORT InputStatus	GetDefaultInputStatus (void);

DG_DLL_EXPORT void	ForceBusyCursorOn (Item* registeredPanel);
DG_DLL_EXPORT void	RemoveForcedItem (Item* item);

void	Register (Panel* panel);
void	Unregister (Panel* panel);
bool	IsRegistered (Panel* panel);
void	ForEachRegisteredPanel (PanelFn fn);

bool	IsWaitCursorEnabled ();

namespace Impl
{
	void	EnableUI (Panel* panel);
	void	DisableUI (Panel* panel);

	NativePoint		GetMouseInScreen (void);	// Retrieves screen coordinates
	bool	IsWindowEnabledUnderMouse (void);

	void	RegisterPanelWindow (Panel* panel);
	void	UnregisterPanelWindow (Panel* panel);
	Panel*	GetRegisteredPanelUnderMouse ();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace InputFilter
} // namespace DG
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // DG_INPUT_FILTER__H
