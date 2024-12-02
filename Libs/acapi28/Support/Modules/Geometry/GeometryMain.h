// *****************************************************************************
// Set processing indicator functions like spin cursor or slider palette, and
// process breaked inspectors.
//
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// [SG compatible]
// *****************************************************************************

#if !defined (GEOMETRYMAIN_H)
#define GEOMETRYMAIN_H

#pragma once

#include "GeometricDefinitions.h"


namespace Geometry {

	GEOMETRY_DLL_EXPORT void	SetDebugMode (Int32 variable);
	GEOMETRY_DLL_EXPORT Int32	GetDebugMode (void);

}

#endif
