#ifndef TEXT_EDIT_VALUE_CHANGE_OBSERVER_HPP
#define TEXT_EDIT_VALUE_CHANGE_OBSERVER_HPP

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

class UD_DLL_EXPORT TextEditValueChangeObserver : public DG::TextEditBaseObserver
{
public:
	TextEditValueChangeObserver (GS::Owner<TypedValueApplier<GS::UniString>> valueApplierInit, DG::TextEdit& observedEdit);

	virtual ~TextEditValueChangeObserver ();

private:
	virtual void TextEditChanged (const DG::TextEditChangeEvent& ev) override final;

	GS::Owner<TypedValueApplier<GS::UniString>> valueApplier;
};

}

#endif