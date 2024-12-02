// *******************************************************************************************
// Improved Search TextEdit
//
// Module:			DG
// Namespace:		
// Contact person:	ZA
//
// [SG compatible]
// ******************************************************************************************


#ifndef UDIMPROVEDSEARCHTEXTEDIT_HPP
#define UDIMPROVEDSEARCHTEXTEDIT_HPP

#pragma once

#include "UDDefinitions.hpp"
#include "UDTextEditWithHintText.hpp"

#include "DGButton.hpp"

namespace GS { class UniString; }

namespace UD {

// ========================= Class ImprovedSearchTextEditEventObserver ======================

class UD_DLL_EXPORT ImprovedSearchTextEditEventObserver : public GS::EventObserver {
public:
	virtual ~ImprovedSearchTextEditEventObserver ();

	virtual	void ImprovedSearchTextEditChanged		(const GS::UniString& searchText, bool changedByUser = true) = 0;
	virtual void ImprovedSearchTextEditFocusGained	();
};


// ========================= Class ImprovedSearchTextEditEventSource ======================

class UD_DLL_EXPORT ImprovedSearchTextEditEventSource : public GS::EventSource
{
public:
	virtual ~ImprovedSearchTextEditEventSource ();

	void	Attach (ImprovedSearchTextEditEventObserver& observer);
	void	Detach (ImprovedSearchTextEditEventObserver& observer);
};


class UD_DLL_EXPORT ImprovedSearchTextEdit : public DG::ButtonItemObserver,
											 public DG::TextEditBaseObserver,
											 public ImprovedSearchTextEditEventSource
{
private:
	UD::TextEditWithHintText			textEdit;
	DG::IconButton						clearButton;

	bool								isTextEditShortened;
public:
 	ImprovedSearchTextEdit (const DG::Panel& panel, short textEditItem, const GS::UniString& textForEmptyNotFocusedField, short buttonItem);
	virtual ~ImprovedSearchTextEdit ();

	void NotifyImprovedSearchTextEditChanged (const GS::UniString& searchText, bool changedByUser = true);

	// ButtonItemObserver
	virtual void ButtonClicked (const DG::ButtonClickEvent& ev) override;

	// TextEditBaseObserver
	virtual void TextEditChanged (const DG::TextEditChangeEvent& ev) override;

	// ItemObserver
	virtual void ItemFocusGained (const DG::ItemFocusEvent& ev) override;

	void				 MoveAndResizeHorizontally (short hGrow);
	void				 Move (short hDisp, short vDisp);
	void				 Resize (short hDisp, short vDisp);

	GS::UniString		 GetText () const;
	void				 Hide ();
	void				 Disable ();

	void				 SetFocus ();

	short				 GetTextEditHeight () const;

	void				 Reset (bool changedByUser = true);

	void				 SetEmptyNotFocusedText (const GS::UniString& textForEmptyNotFocusedField);
};

}

#endif //UDIMPROVEDSEARCHTEXTEDIT_HPP
