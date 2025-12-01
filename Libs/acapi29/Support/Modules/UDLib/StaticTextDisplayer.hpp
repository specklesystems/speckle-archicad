#ifndef STATIC_TEXT_DISPLAYER_HPP
#define STATIC_TEXT_DISPLAYER_HPP

// from UD
#include "StringDisplayer.hpp"

namespace DG {
	class StaticText;
}

namespace UD {

class UD_DLL_EXPORT StaticTextDisplayer : public StringDisplayer
{
public:
	StaticTextDisplayer (DG::StaticText& staticTextInit);

	virtual ~StaticTextDisplayer ();

	virtual void SetValue (GS::UniString newValue) override final;
	virtual void EnableDisplayer () override final;
	virtual void DisableDisplayer () override final;
	virtual void ShowDisplayer () override final;
	virtual void HideDisplayer () override final;

private:
	DG::StaticText& staticText;
};

}

#endif