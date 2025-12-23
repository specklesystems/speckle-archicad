// *****************************************************************************
//
//			Initialize and Terminate routines for the QGDrawing module
//
// Module:			QGDrawing
// Namespace:		QG
// Contact person:	SN
//
// SG compatible
//
// *****************************************************************************


#ifndef QGMAIN_HPP
#define QGMAIN_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "QGBase.hpp"

	// from GSRoot
#include "Definitions.hpp"

// -------------------------------- Definitions --------------------------------

namespace QG {

QG_DLL_EXPORT	Int32 CCALL Initialize ();
QG_DLL_EXPORT	Int32 CCALL Terminate ();

}

#endif // QGMAIN_HPP
