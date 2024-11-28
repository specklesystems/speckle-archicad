#ifndef	MULTILINEEDITPOPUPDIALOG_HPP
#define	MULTILINEEDITPOPUPDIALOG_HPP

#pragma once

//from GSRoot
#include "UniString.hpp"
#include "EventObserver.hpp"
#include "EventSource.hpp"

//from DG
#include "DGDialog.hpp"
#include "DGListBox.hpp"
#include "DGEditControl.hpp"

//from UD
#include "UDDefinitions.hpp"


namespace UD {

class UD_DLL_EXPORT MultiLineEditPopUpDialogObserver : public GS::EventObserver
{
public:
	virtual void TextChanged (const GS::UniString& text) = 0;

	virtual ~MultiLineEditPopUpDialogObserver ();
};


class UD_DLL_EXPORT MultiLineEditPopUpDialog : public DG::ModalDialog,
																public DG::PanelObserver,
																public DG::TextEditBaseObserver
{
private:
	enum {
		DialogResourceId = 2104
	};

	enum {
		MultiLineEditId = 1
	};

	DG::MultiLineEdit	multiLineEdit;

	const DG::Item&		parentItem;

	class UD_DLL_EXPORT MultiLineEditPopUpDialogEventSource : protected GS::EventSource
	{
	public:
		virtual ~MultiLineEditPopUpDialogEventSource ();

		void Attach (MultiLineEditPopUpDialogObserver& observer);
		void Detach (MultiLineEditPopUpDialogObserver& observer);

		void TextChanged (const GS::UniString& text) const;
	};

	MultiLineEditPopUpDialogEventSource eventSource;
public:

	MultiLineEditPopUpDialog   (const GS::UniString&	text,
								const DG::Item&			parentItem,
								short					width	= 200,
								short					height	= 150);

	~MultiLineEditPopUpDialog ();


	void Attach (MultiLineEditPopUpDialogObserver& observer);
	void Detach (MultiLineEditPopUpDialogObserver& observer);

private:
	virtual void	PanelOpened		(const DG::PanelOpenEvent& ev)		override;
	virtual void	TextEditChanged (const DG::TextEditChangeEvent& ev)	override;
};


class UD_DLL_EXPORT MultiLineEditPopUpDialogChanges : public MultiLineEditPopUpDialogObserver
{
private:
	bool	isTextChanged;

public:
	MultiLineEditPopUpDialogChanges (MultiLineEditPopUpDialog& multiLineEditPopUpDialog);

	virtual void	TextChanged (const GS::UniString& text) override;

	bool			IsTextChanged (void) const;
};

} // namespace UD

#endif // MULTILINEEDITPOPUPDIALOG_HPP