// *****************************************************************************
// Basic Geometry module definitions. Needed for all files.
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// *****************************************************************************
#if !defined (GEOMETRICDEFINITIONS_H)
#define GEOMETRICDEFINITIONS_H

#pragma once

#include "GSException.hpp"
#include "PlatformDLLExport.hpp"

#if defined (GEOMETRY_NOT_DLL)
	#define GEOMETRY_DLL_EXPORT

#else
	#if defined (GEOMETRY_DLL_COMPILE)
		#define GEOMETRY_DLL_EXPORT PLATFORM_DLL_EXPORT
	#elif defined (GEOMETRY_STATIC_COMPILE)
		#define GEOMETRY_DLL_EXPORT
	#else
		#define GEOMETRY_DLL_EXPORT	PLATFORM_DLL_IMPORT
	#endif
#endif

namespace Geometry {

	const Int32	ModuleID = 71;

	enum Boundary {
		Boundary_Excluded = 0, Boundary_Opened  = 0,
		Boundary_Included = 1, Boundary_Closed  = 1,
		//Boundary_Mixed   = 2,
		Boundary_Unknown = 3
	};

	enum Orientation {
		Orientation_Unknown,
		Orientation_Clockwise,
		Orientation_CounterClockwise
	};

	enum RelativePosition {
		RelativePosition_Unknown,
		RelativePosition_Overlap,
		RelativePosition_Disjunct
	};

	enum DetailedRelativePosition {
		DetailedRelativePosition_Unknown, 
		DetailedRelativePosition_Overlap_FirstCoversSecond,
		DetailedRelativePosition_Overlap_SecondCoversFirst,
		DetailedRelativePosition_Overlap_Equal,
		DetailedRelativePosition_Overlap_OnBoundary
	};

	inline bool IsOverlap (RelativePosition position)
	{
		return position == RelativePosition_Overlap;
	}

	inline bool IsDisjunct (RelativePosition position)
	{
		return position == RelativePosition_Disjunct;
	}

	const Int32	ErrorCodeBase = ModuleID * 0x10;
	enum GeneralError {	AlgorithmError = ErrorCodeBase + 0 };

DECLARE_EXCEPTION_CLASS (GeometryException,			GS::RootException, Error, GEOMETRY_DLL_EXPORT)

DECLARE_EXCEPTION_CLASS2 (GeometryLogicErrorException,		GeometryException, GS::LogicErrorException,		Error,	GEOMETRY_DLL_EXPORT)
	DECLARE_EXCEPTION_CLASS (GeometryAlgorithmErrorException,	GeometryLogicErrorException,		AlgorithmError,		GEOMETRY_DLL_EXPORT)
DECLARE_EXCEPTION_CLASS2 (GeometryIllegalArgumentException,	GeometryException, GS::IllegalArgumentException,	ErrParam, GEOMETRY_DLL_EXPORT)

}

#endif
