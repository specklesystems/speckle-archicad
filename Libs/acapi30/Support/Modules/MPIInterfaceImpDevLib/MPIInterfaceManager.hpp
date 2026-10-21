// *****************************************************************************
// MPI Add-On interface manager
// GSUtils, Platform independent
//
// Namespaces:        Contact person:
//                         PCS
//
// SG compatible
// *****************************************************************************

#if !defined (MPIINTERFACEMANAGER_HPP)
#define MPIINTERFACEMANAGER_HPP


// --- Includes ---------------------------------------------------------------

#include "Definitions.hpp"


// ----------------------- Predeclarations -------------------------------------

namespace MPI {
	class InterfaceImpBase;
}


// ----------------------- Class declaration -----------------------------------

namespace MPI {


class InterfaceManager {
private:
	InterfaceImpBase*	interfaces;		// set of connected interfaces

public:
	static InterfaceManager*		manager;

	InterfaceManager ();

	void	RegisterInterfaceImp (InterfaceImpBase* interf);
	void*	GetInterface (Int32 type, Int32 version);
};

} // namespace MPI

#endif
