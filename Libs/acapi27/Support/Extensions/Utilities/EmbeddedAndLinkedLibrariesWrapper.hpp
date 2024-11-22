
#if !defined (EMBEDDEDANDLINKEDLIBRARIESWRAPPER_HPP)
#define EMBEDDEDANDLINKEDLIBRARIESWRAPPER_HPP

#pragma once

//from GSRoot
#include "HashSet.hpp"

//from InputOutput
#include "Location.hpp"

// from ODB
#include "ODBDelta.hpp"

// --- Includes --------------------------------------------------------------------------------------------------------

// --- Predeclarations -------------------------------------------------------------------------------------------------

// --- Constant definitions --------------------------------------------------------------------------------------------

// --- Type definitions ------------------------------------------------------------------------------------------------

namespace Extensions {

namespace Utilities {

// =================== Class EmbeddedAndLinkedLibrariesWrapper =============================================================================
//
// Class for temporarily saving then restoring the effective EmbeddedLibContainer's Library Items and the Linked Libraries via API
//
//==========================================================================================================================================

class EmbeddedAndLinkedLibrariesWrapper {
public:
	EmbeddedAndLinkedLibrariesWrapper ();
	virtual ~EmbeddedAndLinkedLibrariesWrapper ();

private:
	GS::HashSet<ODB::ObjectRef> savedEmbeddedLibraryItems;
	GS::HashSet<IO::Location> savedLinkedLibraryLocations;
};


}	// namespace Utilities

}	// namespace Extensions


// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------


#endif // EMBEDDEDANDLINKEDLIBRARIESWRAPPER_HPP
