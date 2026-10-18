// *********************************************************************************************************************
// Base class for those NURBS primitives which are aware of some tolerance value.
// 
// Mainly introduced to generalize 3D tolerance transformation.
// *********************************************************************************************************************

#if !defined(NURBSELEMENTWITHTOLERANCE_HPP)
#define NURBSELEMENTWITHTOLERANCE_HPP

#pragma once

#include "BrepExport.hpp"

struct TRANMAT;

namespace Brep {

class BREP_DLL_EXPORT NurbsElementWithTolerance {
protected:
	double tolerance;
public:
	NurbsElementWithTolerance () : tolerance (0.0) {}
	NurbsElementWithTolerance (double tolerance) : tolerance (tolerance) {}
	double	GetTolerance () const { return tolerance; }
};


class BREP_DLL_EXPORT NurbsElementWithToleranceTransform : public NurbsElementWithTolerance {
public:
	NurbsElementWithToleranceTransform () = default;
	NurbsElementWithToleranceTransform (double tolerance) : NurbsElementWithTolerance (tolerance) {}
protected:
	void	TransformTolerance (const TRANMAT& tran);
};


bool AreTolerancesEqual (double tol1, double tol2);

double BREP_DLL_EXPORT CalculateTransformedTolerance (const TRANMAT& tran, double tolerance);


}		// namespace Brep

#endif	// NURBSELEMENTWITHTOLERANCE_HPP
