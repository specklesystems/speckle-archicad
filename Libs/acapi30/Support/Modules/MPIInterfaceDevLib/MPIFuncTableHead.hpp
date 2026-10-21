// *****************************************************************************
// Interface function table head
// GSUtils, Platform independent
//
// Namespaces:        Contact person:
//                         PCS
//
// SG compatible
// *****************************************************************************

#if !defined (MPIFUNCTABLEHEAD_HPP)
#define MPIFUNCTABLEHEAD_HPP

#pragma once

// ----------------------- Includes --------------------------------------------

#include "MPIInterfaceBaseTypes.hpp"
#include "GSRoot.hpp"


// ----------------------- Types -----------------------------------------------

typedef bool MPI_ADD_ON_CALL CheckVersionFunc (Int32 version);

namespace MPI {

struct FuncTableHead {
	Int32	type;
	Int32	version;

	CheckVersionFunc*	checkVersion;
};

} // namespace


#endif
