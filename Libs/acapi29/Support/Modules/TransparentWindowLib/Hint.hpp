// *****************************************************************************
// File:			Hint.hpp
//
// Description:
//
// Project:			ARCHICAD
//
// Namespace:
//
// Contact person:	NZ, SP
//
// SG compatible
// *****************************************************************************

#ifndef HINT_HPP
#define HINT_HPP

#pragma once


// --- Includes ----------------------------------------------------------------


namespace Tracking {

// --- Class declarations ------------------------------------------------------

enum Hint {
	NoInfo,
	ContinueInput,
	ContinueInputWithNumericValue,
	ContinueInputWithFocusLost,
	ContinueInputWithRelativeInput,
	EndInput
};

}	//namespace Tracker

#endif
