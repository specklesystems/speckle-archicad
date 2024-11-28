#ifndef UDIMPROVEDTEXTEDIT_HPP
#define UDIMPROVEDTEXTEDIT_HPP

#pragma once

#include "UDDefinitions.hpp"
#include "UDItemContentValidityProperty.hpp"

namespace UD {

class UD_DLL_EXPORT ImprovedTextEdit :	public DG::TextEdit,
										public ItemContentValidityProperty,
										public DG::TextEditBaseObserver
{
protected:
	GS::UniString					initialText;

public:
	ImprovedTextEdit (DG::Dialog& dialog, short item);
	ImprovedTextEdit (DG::Dialog& dialog, DG::TabPage& tabPage, short item);
	ImprovedTextEdit (DG::Dialog& dialog, const DG::Rect& rect, DG::EditControl::FrameType frame = DG::EditControl::Frame, DG::EditControl::UpdateType update = DG::EditControl::Update);
	ImprovedTextEdit (DG::Dialog& dialog, DG::TabPage& tabPage, const DG::Rect& rect, DG::EditControl::FrameType frame = DG::EditControl::Frame, DG::EditControl::UpdateType update = DG::EditControl::Update);
	~ImprovedTextEdit ();

	void	SetTextAndInit (const GS::UniString& initialText, const GS::UniString& alreadyExistsAlertText);
	void	Show ();
	void	Hide ();
	void	SetVisibility (bool show);
	void	Disable ();
	void	Enable ();
	void	SetStatus (bool enable);
	void	UpdateTextAlreadyExistsFloatingMenu ();

	virtual bool	GoodName () const = 0;
	virtual bool	UniqueGoodName () const = 0;

protected:
	virtual const DG::Item& GetDGItem ()	const override;
	virtual bool ShouldShowFloatingMenu () const override;

private:
	//DG::TextEditBaseObserver
	virtual void	TextEditChanged (const DG::TextEditChangeEvent& ev) override;
};

}

#endif //UDIMPROVEDTEXTEDIT_HPP
