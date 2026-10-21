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
		MultiLineEditId = 1,
		MultiLineEditReadOnlyId = 2
	};

	DG::MultiLineEdit	multiLineEdit;
	DG::MultiLineEdit	multiLineEditReadOnly;
	DG::MultiLineEdit*	activeMultiLineEdit = nullptr;

	bool firstSetSelection = false;

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
	enum TextSelectionMode {
		NoSelection,
		SelectAll
	};

	MultiLineEditPopUpDialog   (const GS::UniString&	text,
								const DG::Item&			parentItem,
								const bool				isEditable = true,
								short					width	= 200,
								short					height	= 150,
								TextSelectionMode		mode = SelectAll);

	~MultiLineEditPopUpDialog ();

	void Attach (MultiLineEditPopUpDialogObserver& observer);
	void Detach (MultiLineEditPopUpDialogObserver& observer);
	void SetSelection (const DG::CharRange& selRange);

private:
	virtual void	PanelOpened		(const DG::PanelOpenEvent& ev)					override;
	virtual void	TextEditChanged (const DG::TextEditChangeEvent& ev)				override;
	virtual void	PanelIdle (const DG::PanelIdleEvent&)							override;
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