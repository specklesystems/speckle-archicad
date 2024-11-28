// *****************************************************************************
// MPI Add-On interface manager
// GSUtils, Platform independent
//
// Namespaces:        Contact person:
//                         PCS
//
// SG compatible
// *****************************************************************************


// ----------------------- Includes --------------------------------------------

#include "MPIInterfaceManager.hpp"
#include "MPIInterfaceImpBase.hpp"


// ----------------------- Static data members ---------------------------------

namespace MPI {

InterfaceManager*		InterfaceManager::manager = nullptr;


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

InterfaceImpBase::~InterfaceImpBase ()
{
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

InterfaceManager::InterfaceManager () :
	interfaces (nullptr)
{
	manager = this;
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

void	InterfaceManager::RegisterInterfaceImp (InterfaceImpBase* mpiInterface)
{
	mpiInterface->nextInterface = interfaces;
	interfaces = mpiInterface;
	return;
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

void*	InterfaceManager::GetInterface (Int32 type, Int32 version)
{
	void* ret = nullptr;
	for (InterfaceImpBase* mpiInterface = interfaces; mpiInterface != nullptr && ret == nullptr; mpiInterface = mpiInterface->nextInterface) {
		ret = mpiInterface->GetInterface (type, version);
	}
	return ret;
}


} // namespace
