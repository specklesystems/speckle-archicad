// *****************************************************************************
// MPI Add-On interface implementer base class
// GSUtils, Platform independent
//
// Namespaces:        Contact person:
//                         PCS
//
// SG compatible
// *****************************************************************************

#if !defined (MPIINTERFACEIMPBASE_HPP)
#define MPIINTERFACEIMPBASE_HPP

#include "Definitions.hpp"

// ----------------------- Class declaration -----------------------------------

namespace MPI {

class InterfaceImpBase {
private:
	friend class InterfaceManager;

	InterfaceImpBase*	nextInterface;

public:
	virtual ~InterfaceImpBase ();

	virtual void*	GetInterface (Int32 type, Int32 version) = 0;
};

} // namespace


#endif
