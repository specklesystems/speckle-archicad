// *****************************************************************************
//
//                         Interface DisposeHandler
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined DISPOSEHANDLER_HPP
#define DISPOSEHANDLER_HPP

#pragma once


// ---------------------------------- Includes ---------------------------------

#include	"GSRootExport.hpp"

// ------------------------------ Predeclarations ------------------------------

namespace GS { class DisposableObject; }



// ======================== Interface DisposeHandler ===========================

namespace GS {

class GSROOT_DLL_EXPORT DisposeHandler {
public:
	virtual			~DisposeHandler ();

	virtual void	DisposeRequested (DisposableObject& source) = 0;
};

}	// namespace GS

// ________________________ Interface DisposeHandler ___________________________


#endif
