// *********************************************************************************************************************
// Description:		Functions in connection with quadrilaterals
//
// Module:			Geometry
// Namespace:		Geom
// Contact person:	BP, FGy
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GS_QUADRILATERAL_HPP)
#define GS_QUADRILATERAL_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"

// from Geometry
#include "GeometricDefinitions.h"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace Geom {

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------
GEOMETRY_DLL_EXPORT double	GetMaxTrapezoidHeight (double bottomBaseLength, double slantAlpha, double slantBeta, double minTopBaseLength);

}	// namespace Geom

#endif
