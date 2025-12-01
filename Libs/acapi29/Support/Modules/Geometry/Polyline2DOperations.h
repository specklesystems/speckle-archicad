
#if !defined (POLYLINE2DOPERATIONS_H)
#define POLYLINE2DOPERATIONS_H

#include "Polygon2DData.h"
#include "Polygon2DOperations.h"

namespace Geometry {

GEOMETRY_DLL_EXPORT GSErr	ResizePolyLine2DDataContour(const Polygon2DData& poly, Int32 contourIdx, double offset, GS::VAArray<Polygon2DData>* resultPolys);
GEOMETRY_DLL_EXPORT GSErr	FilletPolyLine2DDataVertex (const Polygon2DData& poly, Int32 vertIdx, double filletRadius, GS::VAArray<Polygon2DData>* resultPolys);
GEOMETRY_DLL_EXPORT GSErr	ChamferPolyLine2DDataVertex (const Polygon2DData& poly, Int32 vertIdx, double chamferRadius, GS::VAArray<Polygon2DData>* resultPolys);

GEOMETRY_DLL_EXPORT void	CutPolyLine2D (HalfPlane2DData*					cutline,	/* -> line params. 			*/
										   const Polygon2DData*				poly,		/* -> polygon				*/
										   GS::VAArray<Polygon2DData>*		respoly, 	/* <- result polygons		*/
										   bool*							fullin,		/* <- full inside 			*/
										   Int32*							wrcode		/* <- warning error code   	*/);

inline GSErr ValidatePolyLine2DData (Polygon2DData*	poly)
{
	GSErr	err = NoError;

	if (!poly->status.isBoundBoxValid) {
		err = GetPolygon2DDataBoundBox (*poly, &poly->boundBox);
		if (err == NoError) {
			poly->status.isBoundBoxValid = true;
		}
	}

	return err;
}

}

#endif
