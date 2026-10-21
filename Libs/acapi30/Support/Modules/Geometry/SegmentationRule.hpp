// *****************************************************************************
//
//				Rule for arc segmentation
//
// Module:			GSUtils
// Namespace:
// Contact person:	BeA
//
// SG compatible
//
// *****************************************************************************
#if !defined (SEGMENTATIONRULE_HPP)
#define SEGMENTATIONRULE_HPP

#pragma once


#include "GeometricDefinitions.h"

namespace Geometry {

class GEOMETRY_DLL_EXPORT SegmentationRule {
public:
	typedef enum {
		Radius,
		Toler,
		Resol,
		ExternalTangentToler,
		ExternalTangentTolerMaxByArc
	}	Approx;

	typedef enum {
		OK = 0,
		Ok = 0,
		NegativePar = 1,
		NegativeOrZeroPar,
		InvalidResol,
		NullPar,
		InvalidApprox
	} Error;

private:
	Approx		cirtype;		/* Type of the circle approximation			*/
	double		radmin;			/* Minimal radius or tolerance				*/
	double		radmax;			/* Maximal radius							*/
	Int32		smomin;			/* Minimal smoothness						*/
	Int32		smomax;			/* Maximal smoothness						*/

	void	Clear ();
public:
	SegmentationRule ();
	enum RadiusSelectorType { RadiusSelector };
	SegmentationRule (RadiusSelectorType /*selector*/,
					  double rmin,
					  double rmax,
					  Int32 smin,
					  Int32 smax);
	enum TolerSelectorType { TolerSelector };
	SegmentationRule (TolerSelectorType /*selector*/, double rmin);
	enum ResolSelectorType { ResolSelector };
	SegmentationRule (ResolSelectorType /*selector*/, Int32 smin);
	enum ExternalTangentTolerSelectorType { ExternalTangentTolerSelector };
	SegmentationRule (ExternalTangentTolerSelectorType /*selector*/,
					  double rmin,
					  Int32 smin,
					  Int32 smax);
	enum ExternalTangentTolerMaxByArcSelectorType { ExternalTangentTolerMaxByArcSelector };
	SegmentationRule (ExternalTangentTolerMaxByArcSelectorType /*selector*/,
					  double percentage,
					  Int32 smin,
					  Int32 smax);

	Int32 GetSmoothness (void) const;
	Int32 CalcSmoothness (double r, double arc) const;

	Error	SetRadiusApprox (double rmin, double rmax, Int32 smin, Int32 smax);
	Error	SetResolApprox (Int32 smin);
	Error	SetTolerApprox (double rmin);
	Error	SetExternalTangentTolerApprox (double rmin, Int32 smin, Int32 smax);
	Error	SetExternalTangentTolerMaxByArcApprox (double rmin, Int32 smin, Int32 smax);

	Approx	GetApprox () const { return cirtype; }
	Error	GetRadiusApprox (double* rmin, double* rmax, Int32* smin, Int32* smax) const;
	Error	GetResolApprox (Int32* smin) const;
	Error	GetTolerApprox (double* rmin) const;
	Error	GetExternalTangentTolerApprox (double* rmin, Int32* smin, Int32* smax) const;
	Error	GetExternalTangentTolerMaxByArcApprox (double* rmin, Int32* smin, Int32* smax) const;

	static const double PolygonDefaultSegmentationTolerance;
	static const SegmentationRule polygonDefault;
};

}

using Geometry::SegmentationRule;

#endif
