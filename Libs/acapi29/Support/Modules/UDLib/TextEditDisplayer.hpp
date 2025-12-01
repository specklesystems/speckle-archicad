#ifndef TEXT_EDIT_DISPLAYER_HPP
#define TEXT_EDIT_DISPLAYER_HPP

// from UD
#include "StringDisplayer.hpp"

namespace DG {
class TextEdit;
}

namespace UD {

class UD_DLL_EXPORT TextEditDisplayer : public StringDisplayer
{
public:
	TextEditDisplayer (DG::TextEdit& textEditInit);

	virtual ~TextEditDisplayer ();

	virtual void SetValue (GS::UniString newValue) override final;
	virtual void EnableDisplayer () override final;
	virtual void DisableDisplayer () override final;
	virtual void ShowDisplayer () override final;
	virtual void HideDisplayer () override final;

private:
	DG::TextEdit& textEdit;
};

}

#endif