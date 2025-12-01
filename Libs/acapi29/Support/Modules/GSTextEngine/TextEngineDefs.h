// *****************************************************************************
// File:			TextEngineDefs.h
//
// Description:		Common constants of the TextEngine
//
// Project:			TextEngine
//
// Contact person:	HG
//
// SG compatible
// *****************************************************************************

#ifndef TEXTENGINEDEFS_H
#define TEXTENGINEDEFS_H

#pragma once

// --- Includes ----------------------------------------------------------------

namespace TE {
	const double SuperSizeRate		=   0.6600;
	const double SuperLiftRate		=   0.4800;
	const double SubSizeRate		=   0.6600;
	const double SubLiftRate		= - 0.2200;
	const double StrikeOutLiftRate	=   0.3600;
	const double StrikeOutWidthRate	=   0.0800;
	const double UnderlineLiftRate	= - 0.2200;
	const double UnderlineWidthRate	=   0.0800;

enum IOMode : int {
	NormalMode		= 0,
	TWIsolatedMode	= 1
};

}

#endif	// #ifndef TEXTENGINEDEFS_H
