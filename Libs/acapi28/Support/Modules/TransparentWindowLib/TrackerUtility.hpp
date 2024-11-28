// *********************************************************************************************************************
// File:			TrackerUtility.hpp
//
// Contact person:
//
// SG compatible
// *********************************************************************************************************************

#ifndef TRACKERUTILITY_HPP
#define TRACKERUTILITY_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "Font.hpp"
#include "DGModule.hpp"
#include "TransparentWindowLibDefinitions.hpp"	// TRANSPARENTWINDOWLIB_DLL_EXPORT


// --- Variables -------------------------------------------------------------------------------------------------------

namespace Tracking {

// Item sizes

extern DG::Font::Size TRANSPARENTWINDOWLIB_DLL_EXPORT EditFontSizeForDraw;
extern DG::Font::Size TRANSPARENTWINDOWLIB_DLL_EXPORT EditFontSizeForItem;

extern short	TRANSPARENTWINDOWLIB_DLL_EXPORT		TextLeftGap;
extern short	TRANSPARENTWINDOWLIB_DLL_EXPORT		EditLeftGap;


inline TE::Font	TEFontFromDGFont (DG::Font::Size size, bool selected, bool enabled)
{
	TE::Font txtFont;
	if (selected) {
		DG::GetFont (size, DG::Font::Bold, &txtFont);
	} else if (enabled) {
		DG::GetFont (size, DG::Font::Plain, &txtFont);
	} else {
		DG::GetFont (size, DG::Font::Italic, &txtFont);
	}

	return txtFont;
}

}

#endif
