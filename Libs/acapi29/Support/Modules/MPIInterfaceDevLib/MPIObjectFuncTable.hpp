// *****************************************************************************
// Interface function table head
// GSUtils, Platform independent
//
// Namespaces:        Contact person:
//                         PCS
//
// SG compatible
// *****************************************************************************

#if !defined (MPIOBJECTFUNCTABLE_HPP)
#define MPIOBJECTFUNCTABLE_HPP

// ----------------------- Includes --------------------------------------------

#include "MPIFuncTableHead.hpp"


// ----------------------- Types -----------------------------------------------

namespace MPI {

typedef void MPI_ADD_ON_CALL AddReferenceFunc (Int32 id);
typedef void MPI_ADD_ON_CALL DeleteReferenceFunc (Int32 id);


struct ObjectFuncTable {
	FuncTableHead	head;

	AddReferenceFunc*		addReference;
	DeleteReferenceFunc*	deleteReference;
};

} // namespace


#endif
