#ifndef	UDNEWITEMNAMEEDITDIALOG_HPP
#define	UDNEWITEMNAMEEDITDIALOG_HPP

#pragma once

#include "DGModule.hpp"
//#include "FloatingMenu.hpp"
#include "UDImprovedTextEdit.hpp"

namespace UD {

class UD_DLL_EXPORT NameEditDialog :	public DG::ModalDialog,
										public DG::PanelObserver,
										public DG::CompoundItemObserver,
										public DG::TextEditBaseObserver,
										public DG::ButtonItemObserver
{
public:

	class UD_DLL_EXPORT NameChecker {
	public:
		NameChecker ();
		virtual ~NameChecker ();
		virtual bool	GoodName (const GS::UniString& name, const GS::UniString& initialName) const = 0;
		virtual bool	UniqueGoodName (const GS::UniString& name, const GS::UniString& initialName) const = 0;
	};

private:
	static const GSResID	DialogId = 9005;

	enum {
		OkButtonId = 1,
		CancelButtonId = 2,
		NameStaticTextId = 3,
		NameTextEditId = 4
	};

	DG::Button		okButton;
	DG::Button		cancelButton;
	DG::LeftText	nameStaticText;

	class MyImprovedTextEdit : public UD::ImprovedTextEdit {
	private:
		GS::Ref<NameChecker> nameChecker;
	public:
		MyImprovedTextEdit (DG::Dialog&				dialog,
			short					item,
			GS::Ref<NameChecker>	nameChecker);

		virtual bool	GoodName () const override;

		virtual bool	UniqueGoodName () const override;
	} nameTextEdit;

public:
	NameEditDialog (GS::Ref<NameChecker> nameChecker, const GS::UniString& title, const GS::UniString& oldName = GS::UniString ());

	virtual void	PanelResized (const DG::PanelResizeEvent& ev) override;

	virtual void	TextEditChanged (const DG::TextEditChangeEvent& ev) override;

	virtual void	ButtonClicked (const DG::ButtonClickEvent& ev) override;

	GS::UniString GetNameOfItem () const;

private:
	void RefreshControls ();
};

}	// namespace UD

#endif
