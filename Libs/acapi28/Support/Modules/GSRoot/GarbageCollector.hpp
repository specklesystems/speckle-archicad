
// *****************************************************************************
//
//                         Interface GarbageCollector
//
// It is not a "real" garbage collector, unused (unreferenced) objects should be
// explicitly registered for a later dispose.
// For example it can be used by active objects to register themselves when
// they recognize that their task has been finished, and are not referenced
// by other objects.
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB, AZS
//
// SG compatible
//
// *****************************************************************************


#if !defined GARBAGECOLLECTOR_HPP
#define GARBAGECOLLECTOR_HPP

#pragma once

#include "GSRootExport.hpp"

// ------------------------------ Predeclarations ------------------------------

namespace GS { class DisposableObject; }



// ======================== Interface GarbageCollector =========================

namespace GS {

class GSROOT_DLL_EXPORT GarbageCollector {
public:
	virtual ~GarbageCollector ();

	virtual void	Register (DisposableObject* object) = 0;
	virtual void	Unregister (DisposableObject* object) = 0;

	virtual void	DisposeContent (void) = 0;
};

}	// namespace GS

// ________________________ Interface GarbageCollector _________________________


#endif
