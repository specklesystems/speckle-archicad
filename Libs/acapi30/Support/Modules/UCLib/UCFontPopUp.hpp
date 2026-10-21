// *****************************************************************************
// File:			UCFontPopUp.hpp
//
// Description:		FontPopUp classes
//
// Project:			GRAPHISOFT User Controls (UCLib)
//
// Namespace:		UC
//
// Contact person:	TP
//
// SG compatible
// *****************************************************************************

#ifndef UCFONTPOPUP_HPP
#define UCFONTPOPUP_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "DGModule.hpp"
#include "DGPopUp.hpp"
#include "UC.h"

#include "Array.hpp"
#include "FontFamily.hpp"
#include "FontFamilyEnumerator.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace UC {
	class FontPopUp;
}


// --- Class declarations ------------------------------------------------------

namespace UC {

// --- FontPopUpChangeEvent --------------------------------------------------------

class UC_DLL_EXPORT FontPopUpChangeEvent: public DG::ItemChangeEvent
{
friend class FontPopUpObserver;					// To access protected constructor

private:
	const TE::FontFamily*	previousSelection;

protected:
	explicit FontPopUpChangeEvent (const DG::ItemChangeEvent& ev);

public:
	~FontPopUpChangeEvent ();

	FontPopUp*	GetSource (void) const;

	const TE::FontFamily&	GetPreviousSelection (void) const;
};


// --- FontPopUpObserver -----------------------------------------------------------

class UC_DLL_EXPORT FontPopUpObserver: public DG::ItemObserver
{
friend class FontPopUp;

protected:
	virtual	short	SpecChanged (const DG::ItemChangeEvent& ev) override;

	virtual void	FontPopUpChanged (const FontPopUpChangeEvent& ev);

	virtual void	FontPopUpSelected (void);

public:
	FontPopUpObserver ();
   ~FontPopUpObserver ();

};


// --- PopUp -------------------------------------------------------------------

class UC_DLL_EXPORT FontPopUp: public DG::PopUp
{
public:
	explicit FontPopUp (const DG::Panel& panel, short item, TE::FontFamily::SortMode mode = TE::FontFamily::DefaultSort);
	explicit FontPopUp (const DG::Panel& panel, const DG::Rect& rect, short vSize, short textOffset, TE::FontFamily::SortMode mode = TE::FontFamily::DefaultSort);
   ~FontPopUp ();

	void					Attach (FontPopUpObserver& observer);
	void					Detach (FontPopUpObserver& observer);

	void					SelectItem (const TE::FontFamily& fontFamily);
	const TE::FontFamily&	GetSelectedItem (void) const;
};

}	// namespace UC

#endif
