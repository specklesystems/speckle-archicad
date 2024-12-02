// *********************************************************************************************************************
// Description:		Polygon convex decomposition data structure
//
// Module:			Modeler
// Namespace:		Modeler
// Contact person:	BeA
//
// *********************************************************************************************************************

#if !defined (POLYGONCONVEXDECOMPOSITION_HPP)
#define POLYGONCONVEXDECOMPOSITION_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"
#include	"MemoryBarrier.hpp"
#include	"Channel.hpp"

// from Model3D
#include	"Model3DExport.h"

#include <functional>

// --- Predeclarations	------------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------
namespace Modeler {

class MODEL3D_DLL_EXPORT PolygonConvexDecomposition {
private:
	mutable const Int32* volatile triIpedgs;

public:
	PolygonConvexDecomposition (void) : triIpedgs (nullptr) {}
	PolygonConvexDecomposition (const PolygonConvexDecomposition& src);
	~PolygonConvexDecomposition ();

	PolygonConvexDecomposition& operator = (const PolygonConvexDecomposition& src);

	// for reporting only
	Int32			GetCacheSize (void) const;
	void			ClearCache (void);
	void			PrintDecompositionCache (GS::OChannel& oc) const;
	const Int32*	GetOrCreateTriIpedgs (const std::function<Int32* ()>& createFunction) const;
	bool			HasConvexDecomposition  (void) const;
};



}	// namespace Modeler


#endif // POLYGONCONVEXDECOMPOSITION_HPP

