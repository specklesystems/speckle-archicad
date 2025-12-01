// *****************************************************************************
//
//                            Double classification
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	FGY
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_DOUBLECLASSIFICATION_HPP
#define GS_DOUBLECLASSIFICATION_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "GSRootExport.hpp"

#include "Definitions.hpp"


// =============================================================================

namespace GS {

namespace DoubleClass {		// with C++11 this should be changed to: enum class DoubleClass

enum Value {
	NaN,
	Infinite,
	Zero,
	Normal,
	Denormal
};

}

GSROOT_DLL_EXPORT DoubleClass::Value	ClassifyDouble (const double& d);				// parameter is reference to not to take wrong format number to the floating-point stack FGY

GSROOT_DLL_EXPORT bool					IsDoubleClassNaN (const double& d);				// parameter is reference to not to take wrong format number to the floating-point stack FGY

GSROOT_DLL_EXPORT bool					CheckDouble (const double& d, double maxValue);	// parameter is reference to not to take wrong format number to the floating-point stack FGY
GSROOT_DLL_EXPORT bool					CheckNormalDouble (const double& d);			// parameter is reference to not to take wrong format number to the floating-point stack FGY

GSROOT_DLL_EXPORT void					FixDouble (double& d, double correction = 0.0);
GSROOT_DLL_EXPORT void					FixFloat  (float& f, float correction = 0.0);

}	// namespace GS


#endif
