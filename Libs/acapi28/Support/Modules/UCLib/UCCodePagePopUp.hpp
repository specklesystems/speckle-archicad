// *****************************************************************************
// File:			UCCodePagePopUp.hpp
//
// Description:		CodePagePopUp classes
//
// Project:			GRAPHISOFT User Controls (UCLib)
//
// Namespace:		UC
//
// Contact person:	TP
//
// SG compatible
// *****************************************************************************

#ifndef UCCODEPAGEPOPUP_HPP
#define UCCODEPAGEPOPUP_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "DGModule.hpp"
#include "DGPopUp.hpp"
#include "UC.h"

// --- Predeclarations ---------------------------------------------------------

namespace UC {
	class CodePagePopUp;
}

namespace TE {
	class FontFamily;
}

// --- Class declarations ------------------------------------------------------

namespace UC {

// --- CodePagePopUpChangeEvent --------------------------------------------------------

class UC_DLL_EXPORT CodePagePopUpChangeEvent: public DG::ItemChangeEvent
{
friend class CodePagePopUpObserver;					// To access protected constructor

private:
	short	previousSelection;

protected:
	explicit CodePagePopUpChangeEvent (const DG::ItemChangeEvent& ev);

public:
	~CodePagePopUpChangeEvent ();

	CodePagePopUp*	GetSource (void) const;

	short		GetPreviousSelection (void) const;
};


// --- CodePagePopUpObserver -----------------------------------------------------------

class UC_DLL_EXPORT CodePagePopUpObserver: public DG::ItemObserver
{
protected:
	virtual	short	SpecChanged (const DG::ItemChangeEvent& ev) override;

	virtual void	CodePagePopUpChanged (const CodePagePopUpChangeEvent& ev);

public:
	CodePagePopUpObserver ();
   ~CodePagePopUpObserver ();
};


// --- PopUp -------------------------------------------------------------------

class UC_DLL_EXPORT CodePagePopUp: public	DG::PopUp
{
private:

	void			AppendItem (void);
	void			SetItemText (const GS::UniString& text);
	void			SetItemValue (GSCharCode charCode);

public:

	CodePagePopUp (const DG::Panel& panel, short item);
   ~CodePagePopUp ();

	void			Attach (CodePagePopUpObserver& observer);
	void			Detach (CodePagePopUpObserver& observer);

	void			InitCodePages (const TE::FontFamily& family);
	void			SelectItem (GSCharCode charCode);
	GSCharCode		GetSelectedItem (void);
};

}	// namespace UC

#endif
