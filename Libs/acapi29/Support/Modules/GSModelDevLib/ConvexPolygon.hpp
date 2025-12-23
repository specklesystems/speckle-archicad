// =============================================================================
// Description:		  ConvexPolygon    
// Project:           3D Model Access API Refactoring
// Contact person:    SJ
// =============================================================================
#if !defined (CONVEXPOLYGON_HPP)
#define CONVEXPOLYGON_HPP


// ----------------------- Includes --------------------------------------------

#include "ModelVector.hpp"
#include "GSModelerExport.h"
#include "Definitions.hpp"
#include "SharedPtr.hpp"
#include "CoordinateSystem.hpp"

// ----------------------- Class predeclaration -----------------------------------
namespace ModelerAPI {
	class ConvexPolygonRelay;
	class Transformation;
}

// ----------------------- Class declaration -----------------------------------
namespace ModelerAPI {


class GSMODELER_DLL_EXPORT ConvexPolygon {
	friend class ModelerAPI::ConvexPolygonRelay;

private:
	GS::SharedPtr<ModelerAPI::ConvexPolygonRelay>		relay;

public:
	ConvexPolygon ();
	ConvexPolygon (const ConvexPolygon& other);
	~ConvexPolygon ();
	
	ConvexPolygon&	operator= (const ConvexPolygon& other);

	Int32			GetVertexCount (void) const;
	Int32			GetVertexIndex (Int32 vertexIndex) const;
	Vector			GetNormalVectorByVertex (Int32 vertexIndex, const ModelerAPI::CoordinateSystem coordinateSystem = ModelerAPI::CoordinateSystem::World) const;
};


} // namespace ModelerAPI


#endif
