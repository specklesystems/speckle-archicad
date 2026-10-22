
#if !defined (NURBSUTILITY_HPP)
#define NURBSUTILITY_HPP

#pragma once

// --- Includes --------------------------------------------------------------------------------------------------------

//From GSRoot
#include	"GSRoot.hpp"
#include	"Array.hpp"

//From Geometry
#include	"AngleData.h"
#include	"Vector3D.hpp"
#include	"GeometricDefinitions.h"
#include	"NurbsCurveBase.hpp"
#include	"NurbsCurve3D.hpp"
#include	"NurbsSurface.hpp"
#include	"Plane.hpp"
#include	"DirectedPartOfNurbsCurve.hpp"


// --- Predeclarations -------------------------------------------------------------------------------------------------

// --- Constant definitions --------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------

namespace Geometry {

	namespace NurbsUtility {
		//Surface functions
		GEOMETRY_DLL_EXPORT GSErrCode CreateCylindricalSurface	(const Geometry::Plane& globalPlane,
																 double radius,
																 double height,
																 Geometry::NurbsSurface& nurbsSurface,
																 const GS::Array<DirectedPartOfNurbsCurve3D>* seamRepellingCurves);

		GEOMETRY_DLL_EXPORT GSErrCode CreateSphericalSurface	(const Geometry::Plane& globalPlane,
																 double radius,
																 Geometry::NurbsSurface& nurbsSurface,
																 const GS::Array<DirectedPartOfNurbsCurve3D>* seamRepellingCurves);

		GEOMETRY_DLL_EXPORT GSErrCode CreateToroidalSurface		(const Geometry::Plane& globalPlane,
																 double majorRadius,
																 double minorRadius,
																 Geometry::NurbsSurface& nurbsSurface,
																 const GS::Array<DirectedPartOfNurbsCurve3D>* seamRepellingCurves);

		//Curve functions
		GEOMETRY_DLL_EXPORT GSErrCode CreateNurbsCurve3DLine	(const Geometry::Point3D& pos1,
																 const Geometry::Point3D& pos2,
																 Geometry::NurbsCurve3D& nurbsCurve3D);

		GEOMETRY_DLL_EXPORT GSErrCode CreateNurbsCurve3DArc		(const Geometry::Plane& globalPlane,
																 double radius,
																 double angle0,
																 double angle1,
																 Geometry::NurbsCurve3D& nurbsCurve3D);

		GEOMETRY_DLL_EXPORT GSErrCode CreateNurbsCurve3DArc		(const Geometry::Plane& globalPlane,
																 double semiAxis1,
																 double semiAxis2,
																 double angle0,
																 double angle1,
																 Geometry::NurbsCurve3D& nurbsCurve3D);

		}	//namespace NurbsUtility

}	//namespace Geometry

#endif // NURBSUTILITY_HPP