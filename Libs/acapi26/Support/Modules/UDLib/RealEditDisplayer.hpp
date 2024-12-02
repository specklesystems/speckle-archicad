#ifndef REAL_EDIT_DISPLAYER_HPP
#define REAL_EDIT_DISPLAYER_HPP

// from UD
#include "DoubleDisplayer.hpp"

namespace DG {
	class RealEdit;
}

namespace UD {

class UD_DLL_EXPORT RealEditDisplayer : public DoubleDisplayer
{
public:
	RealEditDisplayer (DG::RealEdit& realEditInit);

	virtual ~RealEditDisplayer ();

	virtual void SetValue (double newValue) override final;
	virtual void EnableDisplayer () override final;
	virtual void DisableDisplayer () override final;
	virtual void SetValueToNotAvailable () override final;
	virtual void SetValueToNotAvailable (const GS::UniString& notAvailableText) override final;

private:
	DG::RealEdit& realEdit;
};

}

#endif