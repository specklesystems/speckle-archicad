// *****************************************************************************
// File:			UDTextInputDialog.hpp
//
// Description:		Dialog for text input
//
// Project:			GRAPHISOFT User Dialog Module (UDLib)
//
// Namespace:		UD
//
// Contact person:	BLA
//
// SG compatible
// *****************************************************************************

#ifndef UDTEXTINPUTDIALOG_HPP
#define UDTEXTINPUTDIALOG_HPP

// --- Includes ----------------------------------------------------------------

#include "UniString.hpp"
#include "DGEditControl.hpp"
#include "DGButton.hpp"
#include "DGDialog.hpp"
#include "DGStaticItem.hpp"

#include "UDDefinitions.hpp"

// --- Predeclarations ---------------------------------------------------------

// --- Class declarations ------------------------------------------------------

namespace UD {

// --- TextInputDialog -----------------------------------------------------

class UD_DLL_EXPORT TextInputDialog	:	public DG::ModalDialog,
										public DG::PanelObserver,
										public DG::ButtonItemObserver,
										public DG::CompoundItemObserver

{
private:
	enum  {
		OkButtonId			=	1,
		CancelButtonId		=	2,
		NewTextId			=	3,
		NewTextEditId		=	4
	};

	DG::Button			okButton;
	DG::Button			cancelButton;
	DG::LeftText		newText;
	DG::TextEdit		newTextEdit;

	GS::UniString			text;

protected:
	virtual void	ButtonClicked	(const DG::ButtonClickEvent& ev) override;
	virtual void	PanelClosed		(const DG::PanelCloseEvent& ev) override;

public:
		TextInputDialog (const GS::UniString& title,
						 const GS::UniString& leftText,
						 const GS::UniString& defaultText);
	   ~TextInputDialog ();

		GS::UniString		GetText (void) const;
};

}	// namespace UD

#endif
