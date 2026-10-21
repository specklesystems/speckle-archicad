#pragma once

#ifndef RADIOANDTEXTANDCHECK_HPP
#define RADIOANDTEXTANDCHECK_HPP

#include "UDRadioAndText.hpp"


namespace UD {

class RadioAndTextAndCheck;


class UD_DLL_EXPORT RadioAndTextAndCheckObserver: public RadioAndTextObserver
{
	friend class RadioAndTextAndCheck;

private:
	virtual void CheckChanged (RadioAndTextAndCheck* source);
};


class UD_DLL_EXPORT RadioAndTextAndCheck:	public RadioAndText,
											private DG::CheckItemObserver
{
public:
	RadioAndTextAndCheck (RadioGroup& group, const DG::Panel& panel, short radioItem, short textItem, short checkItem);

	void Check ();
	void Uncheck ();
	bool IsChecked () const;

private:
	virtual void OnSelect () override;
	virtual void OnDeselect () override;

	virtual void CheckItemChanged (const DG::CheckItemChangeEvent&) override;

	DG::CheckBox	checkBox;
};

}

#endif