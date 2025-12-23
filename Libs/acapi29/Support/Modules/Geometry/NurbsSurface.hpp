// *********************************************************************************************************************
// Description:		NurbsSurface class
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	BkB
//
// SG compatible
// *********************************************************************************************************************

#ifndef NURBSSURFACE_HPP
#define NURBSSURFACE_HPP

#include	"GSRoot.hpp"
#include	"GeometricDefinitions.h"
#include	"NurbsCurveBase.hpp"
#include	"Vector3D.hpp"
#include	"Array.hpp"
#include	"XMLChannel.hpp"
#include	"TM.h"
#include	"ClassInfo.hpp"


namespace Geometry {

	class GEOMETRY_DLL_EXPORT NurbsSurface {
		KnotVector						knotVectorU;
		KnotVector						knotVectorV;
		GS::Array<GS::Array<Point3D> >	controlPoints;
		GS::Array<GS::Array<double> >	weights;

		DECLARE_ROOT_CLASS_INFO

		bool areControlPointsEqual (const NurbsSurface& other, double eps = SmallEps) const;
		bool areWeightsEqual (const NurbsSurface& other, double eps = SmallEps) const;

	public:		
		NurbsSurface (
			const GS::Array<double>&				knotValuesU,
			const GS::Array<double>&				knotValuesV,
			const GS::Array<GS::Array<Point3D> >&	controlPoints,
			const GS::Array<GS::Array<double> >&	weights);

		NurbsSurface () = default;
		NurbsSurface (const NurbsSurface&) = default;
		NurbsSurface (NurbsSurface&&) = default;
		NurbsSurface& operator= (const NurbsSurface&) = default;
		NurbsSurface& operator= (NurbsSurface&&) = default;

		virtual ~NurbsSurface ();
		
		bool	Check () const;
		void	Clear ();
		bool	IsEmpty () const;
		bool	IsEqual (const NurbsSurface& other, double eps) const;

		bool	IsRational () const;
		bool	IsPeriodicU () const;
		bool	IsPeriodicV () const;
		UInt32	GetDegreeU () const;
		UInt32	GetDegreeV () const;

	////ControlPoint
		UInt32	GetControlPointUCount () const;
		UInt32	GetControlPointVCount () const;
		Point3D	GetControlPoint (UInt32 indexU, UInt32 indexV) const;

	////Knot
		double		GetKnotU (UInt32 index) const;
		double		GetKnotV (UInt32 index) const;
		UInt32		GetKnotUCount () const;
		UInt32		GetKnotVCount () const;
		void		GetKnotValuesAndMultiplicitiesU (GS::Array <double>* knotValues, GS::Array <Int32>* multiplicities) const;
		void		GetKnotValuesAndMultiplicitiesV (GS::Array <double>* knotValues, GS::Array <Int32>* multiplicities) const;

	////Weight
		double	GetWeight (UInt32 indexU, UInt32 indexV) const;
		UInt32	GetWeightUCount () const;
		UInt32	GetWeightVCount () const;

		Box2DData	GetUVDomain () const;
		Point3D		CalculateAt (double t, double s) const;

		void Transform (const TRANMAT& tran);

		// boundbox based on only the controlpoints and ignoring trims
		Box3D CalculateControlPointsBoundingBox (const TRANMAT& tran) const;

		ULong GetUsedBytes		() const;
		ULong GetHeapUsedBytes	() const;

		GSErrCode Read			(GS::IChannel& ic);
		GSErrCode Write			(GS::OChannel& oc) const;

		GSErrCode ReadXML	(GS::XMLIChannel& ic);
		GSErrCode WriteXML	(GS::XMLOChannel& oc) const;

		static const char* XMLTag_NurbsSurface;

	private:
		static const char* XMLTag_ControlPointUCount;
		static const char* XMLTag_ControlPointVCount;
		static const char* XMLTag_DegreeU;
		static const char* XMLTag_DegreeV;
		static const char* XMLTag_ControlPoints;
		static const char* XMLTag_ControlPoint;
		static const char* XMLTag_WeightUCount;
		static const char* XMLTag_WeightVCount;
		static const char* XMLTag_Weights;
		static const char* XMLTag_Weight;
		static const char* XMLTag_KnotUCount;
		static const char* XMLTag_KnotVCount;
		static const char* XMLTag_KnotsU;
		static const char* XMLTag_KnotsV;
		static const char* XMLTag_Knot;

		GSErrCode ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
		GSErrCode WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
		GSErrCode ReadVersion2 (GS::IChannel& ic, const GS::InputFrame& frame);
		GSErrCode WriteVersion2 (GS::OChannel& oc, const GS::OutputFrame& frame) const;

		UInt32	CalculateDegreeU () const;
		UInt32	CalculateDegreeV () const;

		void	SetCalculatedDegree ();
		double	GetDomainStartU () const;
		double	GetDomainStartV () const;
		double	GetDomainEndU () const;
		double	GetDomainEndV () const;
	};
}

#endif