// *********************************************************************************************************************
// File:			DGColor.hpp
//
// Description:		Utility functions for color handling
//
// *********************************************************************************************************************

#ifndef DGCOLOR_HPP
#define DGCOLOR_HPP

#pragma once

#include "Color.hpp"
#include "Definitions.hpp"
#include "DGDLLExport.h"

#include <tuple>

namespace DG {

DG_DLL_EXPORT std::tuple<UShort, UShort, UShort>	HSVFromColor (const Gfx::Color& color);
DG_DLL_EXPORT Gfx::Color							ColorFromHSV (UShort h, UShort s, UShort v);

// Adjusts the brightness of the given color by the specified percentage.  The percentage is clamped to the range [-100, 100].
// Positive values increase brightness towards white, while negative values decrease it towards black.
DG_DLL_EXPORT Gfx::Color	AdjustBrightness (const Gfx::Color& color, int brightnessPercent);

#if defined (WINDOWS)
DG_DLL_EXPORT COLORREF		AdjustBrightness (const COLORREF color, int brightnessPercent);
#endif

} // namespace DG

#endif
