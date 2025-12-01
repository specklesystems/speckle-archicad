// *****************************************************************************
// File:			DGFunctions.hpp
//
// Description:
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:
//
// SG compatible
// *****************************************************************************

#ifndef DGFUNCTIONS_HPP
#define DGFUNCTIONS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "DG.h"


// --- Predeclarations ---------------------------------------------------------


// --- Typedefs ----------------------------------------------------------------


// --- Class declarations ------------------------------------------------------

namespace DG {

class DG_DLL_EXPORT Functions {
public:
	static void	GetRealFocus (short& focusDial, short& focusItem);

	static void	ImAlive ();	// prevents the operating system to change the applications state to "Not responding"

	static void	ResetWheelTrackTimer ();

	static void NotifyModalStateBegin ();
	static void NotifyModalStateEnd ();
};

}	// namespace DG

#endif
