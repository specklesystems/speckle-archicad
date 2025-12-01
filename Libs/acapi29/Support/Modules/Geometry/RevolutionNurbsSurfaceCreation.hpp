#if ! defined REVOLUTION_NURBS_SURFACE_CREATION_HPP
#define REVOLUTION_NURBS_SURFACE_CREATION_HPP


// from Geometry
#include "DirectedPartOfNurbsCurve.hpp"
#include "NurbsSurface.hpp"


namespace Geometry {
	class Plane;
}



namespace Geometry {


class RevolutionNurbsSurfaceCreator {
public:
	static GEOMETRY_DLL_EXPORT GSErrCode	Create (const Plane&		localPlaneInGlobal,
													const Plane&		axisPlaneInLocal,
													const NurbsCurve3D&	inputCurveInLocalSys,
													NurbsSurface&		resultNurbsSurface,
													const GS::Array<DirectedPartOfNurbsCurve3D>* seamRepellingCurvesInGlobalSys);

private:
	TRANMAT			trafoFromAxisToGlobal;
	NurbsCurve3D	inputCurveInAxisSys;

	double	inputCurveOrigRotationAngle;
	double	seamRotationAngle;
	bool	reversedRotation;

	KnotVector						knotVectorU;
	KnotVector						knotVectorV;
	GS::Array<GS::Array<Point3D> >	controlPoints;
	GS::Array<GS::Array<double> >	weights;

	GS::Owner<NurbsSurface>	resultSurface;


	RevolutionNurbsSurfaceCreator (const Geometry::Plane&						localPlaneInGlobal,
								   const Geometry::Plane&						axisPlaneInLocal,
								   const Geometry::NurbsCurve3D&				inputCurveInLocalSys,
								   const GS::Array<DirectedPartOfNurbsCurve3D>*	seamRepellingCurvesInGlobalSys);

	void	Create ();
	void	CreateKnotVectorU ();
	void	CreateKnotVectorV ();
	void	CreateControlPoints ();
	void	CreateWeights ();
	TRANMAT	CalcRotationTrafo (UIndex i) const;
	bool	IsToReverseRotation () const;
	double	CalcAngleFarFromCurves (const GS::Array<DirectedPartOfNurbsCurve3D>& seamRepellingCurves,
									const TRANMAT& trafo);

	void	CheckCurveCPointsAreJoined (const GS::Array<DirectedPartOfNurbsCurve3D>& directedCurveParts);
	GS::Owner<NurbsSurface>	PassResultSurface () { return resultSurface.Pass (); }

#if defined (DEBUVERS)
	void	DumpInputCurveGDL (UInt32 segmentCount = 10) const;
#endif
};


GEOMETRY_DLL_EXPORT
double	CalcOneControlPointZRotationAngle (const NurbsCurve3D& curve);

GEOMETRY_DLL_EXPORT
void	PushPolarAngleToArray (const Point3D& cartesianCoords, GS::Array<double>& polarAngleArray);

GEOMETRY_DLL_EXPORT
GS::Array<double>	CalcBeginPointPolarAngles (const GS::Array<DirectedPartOfNurbsCurve3D>& curves,
											   const TRANMAT& trafoToAxisSys);

GEOMETRY_DLL_EXPORT
GS::Array<double>	CalcControlPointPolarAngles (const GS::Array<DirectedPartOfNurbsCurve3D>& curves,
												 const TRANMAT& trafoToAxisSys);

GEOMETRY_DLL_EXPORT
double	FixSecondPolarAngle_MaxPiJump (double polarAngle1, double polarAngle2);

GEOMETRY_DLL_EXPORT
bool	FindUncoveredPolarAngleRegionMiddle (GS::Array<double>&& polarAngles, double* uncoveredRegionMiddle);

GEOMETRY_DLL_EXPORT
bool	FindPolarAngleMaxGapMiddle (GS::Array<double>&& polarAngles, double* maxGapMiddle);

}	// namespace Geometry


#endif
