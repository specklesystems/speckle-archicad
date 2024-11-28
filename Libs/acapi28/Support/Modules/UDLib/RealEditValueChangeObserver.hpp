#ifndef REAL_EDIT_VALUE_CHANGE_OBSERVER_HPP
#define REAL_EDIT_VALUE_CHANGE_OBSERVER_HPP

// from GSRoot
#include "Owner.hpp"

// from DG
#include "DGEditControl.hpp"

// from UD
#include "UDDefinitions.hpp"

namespace UD {
	template<typename Type>
	class TypedValueApplier;
}

namespace UD {

class UD_DLL_EXPORT RealEditValueChangeObserver : public DG::RealEditObserver
{
public:
	RealEditValueChangeObserver (GS::Owner<TypedValueApplier<double>> valueApplierInit, DG::RealEdit& observedEdit);

	virtual ~RealEditValueChangeObserver ();

private:
	virtual void RealEditChanged (const DG::RealEditChangeEvent& ev) override final;

	GS::Owner<TypedValueApplier<double>> valueApplier;
};

}

#endif