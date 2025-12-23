#pragma once

#include "TypedValueApplier.hpp"
#include "DGUserControl.hpp"
#include "UDDefinitions.hpp"

#include <memory>

namespace UC {
	class UC257;
} // namespace UC

namespace UD {

using MaterialValueApplier = TypedValueApplier<Int32>;

class UD_DLL_EXPORT MaterialChangeObserver : public DG::UserControlObserver
{
public:
	MaterialChangeObserver (GS::Owner<MaterialValueApplier> valueApplierInit, UC::UC257& observedItem);
	virtual ~MaterialChangeObserver ();

private:
	virtual void UserControlChanged (const DG::UserControlChangeEvent& ev) override final;

	GS::Owner<MaterialValueApplier> valueApplier;
};

} // namespace UD
