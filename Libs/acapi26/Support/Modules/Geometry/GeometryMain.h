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

	typedef void (*ProcessingUnderWayProc) (void);
	typedef bool (*IsProcessingBreakedProc) (void);

	struct ProcessingIndications {
		ProcessingUnderWayProc	processingUnderWay;
		IsProcessingBreakedProc	isProcessingBreaked;
	};

	GEOMETRY_DLL_EXPORT GSErr	SetProcessingIndicators (const ProcessingIndications& pis);


	GEOMETRY_DLL_EXPORT void	SetDebugMode (Int32 variable);
	GEOMETRY_DLL_EXPORT Int32	GetDebugMode (void);

}

#endif
