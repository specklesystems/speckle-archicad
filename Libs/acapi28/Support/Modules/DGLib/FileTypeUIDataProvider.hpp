// *********************************************************************************************************************
// Description:		Interface for getting data necessary to open a certain file type
//
// Module:			DGLib
// Namespace:		DG
// Contact person:	CsAd
//
// SG compatible
// *********************************************************************************************************************


#ifndef DG_FILETYPEUIDATAPROVIDER_HPP
#define DG_FILETYPEUIDATAPROVIDER_HPP

#pragma once


// from DG
#include "DGDLLExport.h"

// from GSRoot
#include "Definitions.hpp"
#include "UniString.hpp"


namespace FTM {
	class GeneralID;
}


namespace DG {
	class PopUp;
	class LeftText;
	class RightText;
	class Button;
	class RadioButton;
	class CheckBox;
	class IconItem;


// Abstract interface for providing the necessary information for selecting a file format handled by an AddOn
class DG_DLL_EXPORT FileTypeUIDataProvider {
public:
	struct UIControls {
		LeftText*	primaryText;
		PopUp*		primaryPopup;
		Button*		primaryButton;
		Button*		primaryButton2;		// deprecated
		Button*		primaryLongButton;
		
		LeftText*	secondaryText;
		PopUp*		secondaryPopup;
		Button*		secondaryButton;
		Button*		secondaryLongButton;

		RadioButton*	firstRadioButton;
		RadioButton*	secondRadioButton;

		CheckBox*	checkBox;

		LeftText*	alternativeDescriptionLeftText;
		RightText*	alternativeDescriptionRightText;
		IconItem*	infoIcon;
		LeftText*	infoText;

		const void*		parentModalDialogWindow;

		UIControls (const void* parentModalDialogWindow = nullptr) :
			primaryText						(nullptr),
			primaryPopup					(nullptr),
			primaryButton					(nullptr),
			primaryButton2					(nullptr),
			primaryLongButton				(nullptr),
			secondaryText					(nullptr),
			secondaryPopup					(nullptr),
			secondaryButton					(nullptr),
			secondaryLongButton				(nullptr),
			firstRadioButton				(nullptr),
			secondRadioButton				(nullptr),
			checkBox						(nullptr),
			alternativeDescriptionLeftText	(nullptr),
			alternativeDescriptionRightText (nullptr),
			infoIcon						(nullptr),
			infoText						(nullptr),
			parentModalDialogWindow			(parentModalDialogWindow)
		{}

		UIControls (LeftText* primaryText, PopUp* primaryPopup, LeftText* alternativeDescriptionLeftText, RightText* alternativeDescriptionRightText, Button* primaryButton, Button* primaryButton2, Button* primaryLongButton,
                    LeftText* secondaryText, PopUp* secondaryPopup, Button* secondaryButton, Button* secondaryLongButton,
					RadioButton* firstRadioButton, RadioButton* secondRadioButton, CheckBox* checkBox, IconItem* infoIcon, LeftText* infoText, const void* parentModalDialogWindow) :
			primaryText			(primaryText),
			primaryPopup		(primaryPopup),
			primaryButton		(primaryButton),
			primaryButton2		(primaryButton2),
			primaryLongButton	(primaryLongButton),
			secondaryText		(secondaryText),
			secondaryPopup		(secondaryPopup),
			secondaryButton		(secondaryButton),
			secondaryLongButton	(secondaryLongButton),
			firstRadioButton	(firstRadioButton),
			secondRadioButton	(secondRadioButton),
			checkBox			(checkBox),
			infoIcon			(infoIcon),
			infoText			(infoText),
			alternativeDescriptionLeftText	(alternativeDescriptionLeftText),
			alternativeDescriptionRightText	(alternativeDescriptionRightText),
			parentModalDialogWindow	(parentModalDialogWindow)
		{}
	};

public:
	FileTypeUIDataProvider ();
	virtual ~FileTypeUIDataProvider ();

	virtual void			SetUIControls				(DG::FileTypeUIDataProvider::UIControls uiControls) = 0;
	virtual void			OnFileTypeSelection			(const FTM::GeneralID& selectedFileType) = 0;

	virtual bool			NeedsAdditionalData		()		{	return false;		}
	virtual GSPtr			GetAdditionalData		()		{	return nullptr;		}

	virtual void			UpdateUI						()	{}		// responsible for showing/hiding as well
	virtual void			OnPrimaryPopupItemSelected		()	{}
	virtual GS::UniString	GetPrimaryPopupTooltip			()	{	return "";	}
	virtual void			OnPrimaryButtonPressed			()	{}
	virtual void			OnPrimaryLongButtonPressed		()	{}
	virtual void			OnSecondaryPopupItemSelected	()	{}
	virtual GS::UniString	GetSecondaryPopupTooltip		()	{	return "";	}
	virtual void			OnSecondaryButtonPressed		()	{}
	virtual void			OnSecondaryLongButtonPressed	()	{}
	virtual void			OnRadioButtonSelected			()	{}
	virtual void			OnCheckBoxChanged				()	{}
};


class DG_DLL_EXPORT DummyFileTypeUIDataProvider : public FileTypeUIDataProvider
{
protected:
	DG::FileTypeUIDataProvider::UIControls uiControls;

public:
	DummyFileTypeUIDataProvider ();
	virtual ~DummyFileTypeUIDataProvider ();
	virtual void SetUIControls (DG::FileTypeUIDataProvider::UIControls value) override	{	uiControls = value;	}
	virtual void OnFileTypeSelection (const FTM::GeneralID& /*selectedFileType*/) override {}
	virtual void UpdateUI () override;
};


} 	// namespace DG


#endif	// DG_FILETYPEUIDATAPROVIDER_HPP
