// *****************************************************************************
// File:			DGFontPopUpObservers.hpp
//
// Description:		Favorite font for text editing
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	BL
//
// SG compatible
// *****************************************************************************

#ifndef DGFONTPOPUPOBSERVERS_HPP
#define DGFONTPOPUPOBSERVERS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "FontRegistryObserver.hpp"
#include "DGFontFavorites.hpp"

namespace DG {

// --- Class declarations ------------------------------------------------------


// ============================== Class FontFavoritesObserver =============================


class PopUpFontRegistryObserver : public TE::FontRegistryObserver {

private:
	short	dialId;
	short	item;
public:
	PopUpFontRegistryObserver (short inDialId, short inItem) { dialId = inDialId; item = inItem; }
   ~PopUpFontRegistryObserver () {}

	virtual void FontAdded (const TE::FontFamily& fontFamily) override;
};

// ============================== Class FontFavoritesObserver =============================


class PopUpFontFavoritesObserver : public DG::FontFavoritesObserver {

private:
	short	dialId;
	short	item;
public:
	PopUpFontFavoritesObserver (short inDialId, short inItem) { dialId = inDialId; item = inItem; }
   ~PopUpFontFavoritesObserver () {}

	virtual void FontFavoritesChanged (void) override;
};

}


#endif
