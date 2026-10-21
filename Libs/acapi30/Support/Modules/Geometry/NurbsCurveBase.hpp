// *********************************************************************************************************************
// Description:		NurbsCurveBase class
//
// Module:			Geometry
// Namespace:		Geometry
//
// SG compatible
// *********************************************************************************************************************

#ifndef NURBSCURVEBASETEMPLATE_HPP
#define NURBSCURVEBASETEMPLATE_HPP

#include "GSRoot.hpp"
#include "GetUsedBytesUtilities.hpp"
#include "GeometricDefinitions.h"
#include "Point2D.hpp"
#include "Array.hpp"
#include "XMLChannel.hpp"
#include "TM.h"
#include "ClassInfo.hpp"
#include "Box2DData.h"
#include "Box3DData.h"
#include "KnotVector.hpp"
#include "BSpline.hpp"

namespace Geometry {
	class PolyId;

	template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData> 
	class CustomPolygon2D;
	typedef CustomPolygon2D<PolyId, PolyId, PolyId, PolyId> Polygon2D;

	template <class VertexUserData, class EdgeUserData, class PolygonUserData>
	class CustomPolyline2D;
	typedef CustomPolyline2D<PolyId, PolyId, PolyId> Polyline2D;
}

namespace Geometry {

	class GEOMETRY_DLL_EXPORT  NurbsCurveBasePrivate {
		public:
			static GS::ClassInfo	classInfo;	// NurbsCurveBase's private classInfo 

			static const char* XMLTag_BoundBoxValid;
			static const char* XMLTag_NURBS;
			static const char* XMLTag_Degree;
			static const char* XMLTag_ControlPointCount;
			static const char* XMLTag_ControlPoints;
			static const char* XMLTag_ControlPoint;
			static const char* XMLTag_WeightCount;
			static const char* XMLTag_Weights;
			static const char* XMLTag_Weight;
			static const char* XMLTag_KnotCount;
			static const char* XMLTag_Knots;
			static const char* XMLTag_Knot;

	};


	template<class CoordinateN, class BoxDataN, class VectorN>
	class NurbsCurveBase
	{
	public:
		enum EqualValue {
			NotEqual,
			EqualData,
			EqualDataReversed,
			EqualCurve,
			EqualCurveReversed
		};

	protected:
		GS::Array<CoordinateN>				controlPoints;
		GS::Array<double>					weights;
		KnotVector							knotVector;

		bool areControlPointsEqual(const NurbsCurveBase& other, double eps = SmallEps) const;
		bool areWeightsEqual(const NurbsCurveBase& other, double eps = SmallEps) const;

	public: 
		NurbsCurveBase ();
		NurbsCurveBase (const GS::Array<CoordinateN>& controlPoints_, UInt32 degree);
		NurbsCurveBase (const GS::Array<CoordinateN>& controlPoints_, const GS::Array<double>& knotvector_, const GS::Array<double>& weights_ = GS::Array<double>());
		
		NurbsCurveBase (const NurbsCurveBase& src) = default;
		NurbsCurveBase (NurbsCurveBase&& src) = default;
		NurbsCurveBase&	operator= (const NurbsCurveBase& src) = default;
		NurbsCurveBase&	operator= (NurbsCurveBase&& src) = default;

		virtual ~NurbsCurveBase () = default;

		void	Clear ();
		bool	IsEmpty () const; 

		bool	IsEqual (const NurbsCurveBase& other, double eps = SmallEps) const;
		
		bool	Check () const;
		bool	IsQuasiUniform () const;
		bool	IsRational () const;
		bool	IsPeriodic () const;
		bool	IsFloatBegin () const;
		bool	IsFloatEnd () const;
		bool	IsFloat () const;
		UInt32	GetDegree () const;

	//// ControlPoint 
		UInt32		GetControlPointCount () const;
		CoordinateN	GetControlPoint (UInt32 index) const;
		void		SetControlPoint (CoordinateN coord, UInt32 index);

	//// Knot
		void	ReScaleKnotInterval (double low, double high);
		void	GetKnotValuesAndMultiplicities (GS::Array <double>* knotValues, GS::Array <Int32>* multiplicities) const;
		double	GetFirstKnot () const;
		double	GetLastKnot () const;
		double	GetKnot (UInt32 index) const;
		void	SetKnot (UInt32 index, double knot);
		UInt32	GetKnotCount () const;

	//// Weight
		UInt32	GetWeightCount () const;
		double	GetWeight (UInt32 index) const;
		void	SetWeight (double weight, UInt32 index);

		double		GetDomainStart () const;
		double		GetDomainEnd ()	const;
		void		GetDomain (double& start, double& end) const;
		UIndex		GetLowestEffectiveControlPointIndexAtParam (double t) const;
		UIndex		GetHighestEffectiveControlPointIndexAtParam (double t) const;
		CoordinateN	CalculateAt (double t) const;
		void		SetReverseDirection ();
		void		Transform (const TRANMAT& tran);
		void		Move (VectorN a);
		void		Append (const NurbsCurveBase& other, double smoothness = 0);
		void		Split (NurbsCurveBase& left, NurbsCurveBase& right) const;
		void		Split (NurbsCurveBase& left, NurbsCurveBase& right, double newKnot) const;
		void		InsertKnot (double newKnot);
		BoxDataN	CalculateTightBoundingBox (const TRANMAT& tran = Geometry::IdentityTranMat) const;
		BoxDataN	CalculateControlPointsBoundingBox (const TRANMAT& tran = Geometry::IdentityTranMat) const;

		ULong		GetUsedBytes		() const;
		ULong		GetHeapUsedBytes		() const;

		virtual	GSErrCode Read			(GS::IChannel& ic);
		virtual	GSErrCode Write			(GS::OChannel& oc) const;
		virtual	GSErrCode ReadXML		(GS::XMLIChannel& ic);
		virtual	GSErrCode WriteXML		(GS::XMLOChannel& oc) const;


		
		GSErrCode	Store (GS::ObjectState& os) const
		{
			for (UIndex i = 0; i < controlPoints.GetSize (); ++i)
				os.Add (GS::String::SPrintf("controlPoints[%d]", i), controlPoints[i]);
			for (UIndex i = 0; i < weights.GetSize (); ++i)
				os.Add (GS::String::SPrintf ("weights[%d]", i), weights[i]);
			os.Add ("knotVector", knotVector);
			return NoError;
		}
		

		GSErrCode	Restore (const GS::ObjectState& os)
		{
			for (UIndex i = 0; i < controlPoints.GetSize (); ++i)
				os.Get (GS::String::SPrintf ("controlPoints[%d]", i), controlPoints[i]);
			for (UIndex i = 0; i < weights.GetSize (); ++i)
				os.Get (GS::String::SPrintf ("weights[%d]", i), weights[i]);
			os.Get ("knotVector", knotVector);
			return NoError;
		}

	protected:
		void		SetCalculatedDegree ();
		UInt32		CalculateDegree () const;

		GS::Array<CoordinateN> GetTransformatedControlPoints (const TRANMAT& tran) const;
		static BoxDataN	CalculateControlPointsBoundingBoxNoTransformation (const GS::Array<CoordinateN>& cp);
	private:
		GSErrCode ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
		GSErrCode ReadVersion2 (GS::IChannel& ic, const GS::InputFrame& frame);
		GSErrCode ReadVersion3 (GS::IChannel& ic, const GS::InputFrame& frame);
		GSErrCode WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
		GSErrCode WriteVersion2 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
		GSErrCode WriteVersion3 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	};

	template <class VectorN>
	VectorN	GetVectorWithCoordinates (double d);

	template <class BoxDataN>
	BoxDataN InvalidBoundingBox ();

	GEOMETRY_DLL_EXPORT bool AreClose (const Vector2D& v1, const Vector2D& v2);
	GEOMETRY_DLL_EXPORT bool AreClose (const Point2D& v1, const Point2D& v2);
	GEOMETRY_DLL_EXPORT bool AreClose (const Vector3D& v1, const Vector3D& v2);
	 
	GEOMETRY_DLL_EXPORT void MoveBox (Box2DData* boundingBox, const Vector2D& a);
	GEOMETRY_DLL_EXPORT void MoveBox (Box3D* boundingBox, const Vector3D& a);
	
	GEOMETRY_DLL_EXPORT void BoundingBoxUnion (const Box2DData& addBox, Box2DData* dstBox);
	GEOMETRY_DLL_EXPORT void BoundingBoxUnion (const Box3D& addBox, Box3D* dstBox);
	
	GEOMETRY_DLL_EXPORT bool BoundingBoxHull (const Box2DData&, Box2DData&, double threshold);
	GEOMETRY_DLL_EXPORT bool BoundingBoxHull (const Box3D&, Box3D&, double threshold);
	
	GEOMETRY_DLL_EXPORT GSErrCode WriteToXMLBox (GS::XMLOChannel& oc, const Box2DData& box);
	GEOMETRY_DLL_EXPORT GSErrCode WriteToXMLBox (GS::XMLOChannel& oc, const Box3D& box);
	
	GEOMETRY_DLL_EXPORT GSErrCode WriteToXMLPoint (GS::XMLOChannel& oc, const Point2D& c);
	GEOMETRY_DLL_EXPORT GSErrCode WriteToXMLPoint (GS::XMLOChannel& oc, const Point3D& c);
	
	GEOMETRY_DLL_EXPORT GSErrCode ReadFromXMLBox (GS::XMLIChannel& oc, Box2DData& box);
	GEOMETRY_DLL_EXPORT GSErrCode ReadFromXMLBox (GS::XMLIChannel& oc, Box3D& box);
	
	GEOMETRY_DLL_EXPORT GSErrCode ReadFromXMLPoint (GS::XMLIChannel& oc, Point2D& c);
	GEOMETRY_DLL_EXPORT GSErrCode ReadFromXMLPoint (GS::XMLIChannel& oc, Point3D& c);

	  /*	out:
   *		logical value, true if boxes touches each other
   *	if any of the two boxes same side are closer to each other than EPS, returns true
   */

	GEOMETRY_DLL_EXPORT bool IsBoundingBoxesConnect (const Box2DData& inner, const Box2DData& outer);
	GEOMETRY_DLL_EXPORT bool IsBoundingBoxesConnect (const Box3D& inner, const Box3D& outer);

}


template<>
inline Vector2D Geometry::GetVectorWithCoordinates <Vector2D> (double d) {
	return Vector2D (d, d);
}

template<>
inline Vector3D Geometry::GetVectorWithCoordinates <Vector3D>  (double d) {
	return Vector3D (d, d, d);
}

template <>
inline Box2DData Geometry::InvalidBoundingBox <Box2DData> () {
	return Box2DData ();
}

template <>
inline Box3D Geometry::InvalidBoundingBox <Box3D> () {
	Box3D box;
	InitBox3D (&box);
	return box;
}
	
/*
*	Creates an empty (also invalid) NURBS
*/
template<class CoordinateN, class BoxDataN, class VectorN>
Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::NurbsCurveBase ()
{
	Clear ();
}
  
/*	in: 
*		controlPoints_ : array of 2D points, that will be used as the controlpolygon of the NURBS
*		degree : degree of the curve generated
*	Creates a NURBS with the controlpoints, and given degree
*	knots will be uniformly spaced, and all weights will be 1 (therefore output is non rational, and uniform NURBS)
*	if the in datas are invalid, or the generated NURBS is invalid, the output is an empty NURBS
*/
template<class CoordinateN, class BoxDataN, class VectorN>
Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::NurbsCurveBase (const GS::Array<CoordinateN>& controlPoints_, UInt32 degree) :
  	controlPoints (controlPoints_)
{
  	if (degree + 1 > controlPoints.GetSize ()) {
  		DBBREAK_STR ("Invalid parameters in NURBS constructor. Not enough controlpoint.");
  		Clear ();
  		return;
  	}
  		
  	weights.SetSize (controlPoints.GetSize ());
  	weights.Fill (1);
  		
	{
		const USize KnotCount = controlPoints.GetSize () + degree + 1;
		GS::Array<double> knotValues (KnotCount);
		knotValues.SetSize (KnotCount);
		knotValues.Fill (0, 0, degree + 1);
		UInt32 i = degree + 1;
		for (; i < knotValues.GetSize () - degree - 1; i++) {
			knotValues[i] = i - degree;
		}
		knotValues.Fill (i - degree, knotValues.GetSize () - degree - 1);
		knotVector = KnotVector (std::move (knotValues), degree);
	}

  	SetCalculatedDegree ();

	DBASSERT (degree == GetDegree ());
  	DBASSERT (IsQuasiUniform ());

  	if (!Check ())
  		Clear ();
}
  
/*	in: 
*		controlPoints_ : array of 2D points, that will be used as the controlpolygon of the NURBS
*		knotVector_ : knot vector that will be used when creating the corresponding BSplines
*		weights_ : corresponding weights to the controlpoints
*	Creates a NURBS with the controlpoints, knotvector, and weights
*	if weights are not given, all weights will be set to 0
*	if created NURBS is invalid, output will be empty
*/
template<class CoordinateN, class BoxDataN, class VectorN>
Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::NurbsCurveBase (const GS::Array<CoordinateN>& controlPoints_, const GS::Array<double>& knotVector_, const GS::Array<double>& weights_) :
  	controlPoints (controlPoints_),
  	weights (weights_),
	knotVector (knotVector_)
{

  	if (weights_.GetSize () == 0) {
  		weights.SetSize (controlPoints_.GetSize ());
  		weights.Fill (1);
  	}
  		
	SetCalculatedDegree ();

  	if (!Check ())
  		Clear ();
}
  
/*	
*	clears all arrays, and set degree to 0, so the NURBS will be empty
*/
template <class CoordinateN, class BoxDataN, class VectorN>
void Geometry::NurbsCurveBase< CoordinateN,  BoxDataN,  VectorN>::Clear () 
{
	controlPoints.Clear ();
	knotVector.Clear ();
	weights.Clear ();
}
//
///*	out:
// *		true if the NURBS is considered to be empty
// *	check if all arrays are empty, and degree is 0.
// */
template<class CoordinateN, class BoxDataN, class VectorN>
bool Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::IsEmpty () const
{
	return	weights.IsEmpty () &&
			controlPoints.IsEmpty () &&
			knotVector.IsEmpty ();
}


/*	in:
*		other : NURBS reference
*	out: 
*		bool : is the structure of the objects equal (control points, their weights and the knot vector)
*/
template<class CoordinateN, class BoxDataN, class VectorN>
bool Geometry::NurbsCurveBase<CoordinateN, BoxDataN, VectorN>::IsEqual (const Geometry::NurbsCurveBase<CoordinateN, BoxDataN, VectorN>& other, double eps) const
{
	return areControlPointsEqual(other, eps) &&
		areWeightsEqual(other, eps) &&
		knotVector.IsEqual(other.knotVector, eps);
}


template<class CoordinateN, class BoxDataN, class VectorN>
bool Geometry::NurbsCurveBase<CoordinateN, BoxDataN, VectorN>::areWeightsEqual(const NurbsCurveBase& other, double eps /*= SmallEps*/) const
{
	UInt32 size = weights.GetSize();
	if (size != other.weights.GetSize())
	{
		return false;
	}
	for (UInt32 i = 0; i < size; ++i)
	{
		const double& twi = weights.Get(i);
		const double& owi = other.weights.Get(i);
		if (GS::Abs(twi - owi) > eps)
		{
			return false;
		}
	}
	return true;
}


template<class CoordinateN, class BoxDataN, class VectorN>
bool Geometry::NurbsCurveBase<CoordinateN, BoxDataN, VectorN>::areControlPointsEqual(const NurbsCurveBase& other, double eps /*= SmallEps*/) const
{
	UInt32 size = controlPoints.GetSize();
	if (size != other.controlPoints.GetSize())
	{
		return false;
	}
	for (UInt32 i = 0; i < size; ++i)
	{

		if (!controlPoints.Get(i).IsNear(other.controlPoints.Get(i), eps))
		{
			return false;
		}
	}
	return true;
}

  
/*	out: 
*		logical value, true if the NURBS is consistent
*	determine if the NURBS is consistent. The NURBS is consistent when
*		- its degree is greater than 1
*		- interpolates first and last controlpoints
*		- have the same number of controlpoints and weights
*		- all weights are positive
*		- knotvector is increasing
*		- multiplicity of first and last knot is not greater than degree+1
*		- multiplicity of internal knots are not greater than degree
*/
template<class CoordinateN, class BoxDataN, class VectorN>
bool	Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::Check () const
{
	if (IsEmpty ())
		return true;
	if (GetDegree () == 0)
		return false;
	if (CalculateDegree () != knotVector.GetDegree ())
		return false;
	if (!knotVector.IsValid ())
		return false;
	if (controlPoints.GetSize () <= GetDegree ())
		return false;
	if (knotVector.GetSize () != controlPoints.GetSize () + GetDegree () + 1)
		return false;
	if (weights.GetSize () != controlPoints.GetSize  ())
		return false;
	for (UInt32 i = 0; i < weights.GetSize (); i++)
		if (weights[i] <= 0) 
			return false;
	return true;
}

/*	out: 
*		logical value, true if the knot vector is uniform
*	determine if the knot vector is uniform, that means all gap between different knots next to each other are the same
*/
template<class CoordinateN, class BoxDataN, class VectorN>
bool Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::IsQuasiUniform () const
{
	return knotVector.IsQuasiUniform ();
}
  
/*	out: 
*		logical value, true if the NURBS is rational
*	determine if the NURBS is rational, that means one or more weight(s) are not equal to zero
*/
template<class CoordinateN, class BoxDataN, class VectorN>
bool	Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::IsRational () const
{
  	for (UInt32 i = 0; i < weights.GetSize (); i++)
  		if (GS::Abs (GetWeight (i) - 1) > EPS)
  			return true;
  	return false;
}
  
template<class CoordinateN, class BoxDataN, class VectorN>
bool	Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::IsPeriodic () const
{
	if (knotVector.IsPeriodic ()) {
		for (UInt32 i = 0; i < GetDegree (); ++i) {
			if (!AreClose (GetControlPoint (i), GetControlPoint (GetControlPointCount () - GetDegree () + i)))
				return false;
		}
		return true;
	}
	return false;
}

  
/*	out: 
*		logical value, false if the NURBS interpolates its first controlpoint
*	determine if the NURBS doesnt interpolate its first controlpoint, that means the first knot's multiplicity is less than degree+1
*/

template<class CoordinateN, class BoxDataN, class VectorN>
bool Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::IsFloatBegin () const
{
  	return knotVector.IsFloatBegin ();
}
  
/*	out: 
*		logical value, false if the NURBS interpolates its last controlpoint
*	determine if the NURBS doesnt interpolate its last controlpoint, that means the last knot's multiplicity is less than degree+1
*/
template<class CoordinateN, class BoxDataN, class VectorN>
bool Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::IsFloatEnd () const
{
  	return knotVector.IsFloatEnd ();
}
  
/*	out: 
*		logical value, true if NURBS is floating
*	determine if the NURBS doesnt interpolate its first or last controlpoint
*/
template<class CoordinateN, class BoxDataN, class VectorN>
bool Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::IsFloat () const
{
	return (IsFloatEnd () || IsFloatBegin ());
}

/*	out: 
*		unsigned int, the degree of the curve
*/
template<class CoordinateN, class BoxDataN, class VectorN>
UInt32	Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::GetDegree () const
{
  	return knotVector.GetDegree ();
}
  
/*	out: 
*		unsigned int, the number of controlpoints
*/
template<class CoordinateN, class BoxDataN, class VectorN>
UInt32	Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::GetControlPointCount () const
{
  	return controlPoints.GetSize ();
}
  
/*	in:
*		index : index of controlpoint to get
*	out: 
*		2D Coord, the index-th coordinate in the controlpoints vector
*		or (0,0) if the index is invalid
*/
template<class CoordinateN, class BoxDataN, class VectorN>
CoordinateN	Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::GetControlPoint (UInt32 index) const
{
  	if (DBERROR (index >= controlPoints.GetSize ()))
  		return CoordinateN (GetVectorWithCoordinates <VectorN> (0));
  	return controlPoints[index];
}
  
/*	in:
*		coord : coordinate to set to the controlpoints vector
*		index : index of controlpoint to set
*	Check if the index is valid, if so, update the index-th controlpoint to coord, and set boundingBox invalid.
*/
template<class CoordinateN, class BoxDataN, class VectorN>
void	Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::SetControlPoint (CoordinateN coord, UInt32 index)
{
  	if (DBERROR (index >= controlPoints.GetSize ()))
  		return;
  	controlPoints[index] = coord;
}
  
/*	in:
*		low : first knot's value in the new knotvector (less than high)
*		high : last knot's value in the new knotvector (greater than low)
*	Creates a new knotvector, on the intervall (low, high), according to the old's gaps.
*  The curve wont change
*/
template<class CoordinateN, class BoxDataN, class VectorN>
void	Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::ReScaleKnotInterval (double low, double high)
{
  	if (low > high)
  		return;
  
  	GS::Array<double> newKnots;
  	newKnots.SetSize (knotVector.GetSize ());
  
  	double lowOld = GetFirstKnot ();
  	double highOld = GetLastKnot ();
  
  	for (UInt32 i = 0; i < knotVector.GetSize (); i++) {
  		double percent = (GetKnot (i) - lowOld) / (highOld - lowOld);
  		newKnots[i] = low + ((high - low) * percent);
  	}
  
  	knotVector = KnotVector (newKnots);
	SetCalculatedDegree ();

	DBASSERT (Check ());
}
  
/*	in:
*		start : double reference, the start of the domain will be set here
*		end : double reference, the end of the domain will be set here
*/
template<class CoordinateN, class BoxDataN, class VectorN>
void	Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::GetDomain (double& start, double& end) const
{
  	start	= GetDomainStart ();
  	end		= GetDomainEnd ();
}

template<class CoordinateN, class BoxDataN, class VectorN>
void	Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::GetKnotValuesAndMultiplicities (GS::Array <double>* knotValues, GS::Array <Int32>* multiplicities) const {
	knotVector.GetKnotValuesAndMultiplicities (knotValues, multiplicities);
}

/*	out:
*		the fist knot's value, or 0 if empty
*/
template<class CoordinateN, class BoxDataN, class VectorN>
double Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::GetFirstKnot () const
{
   	return knotVector.GetFirst ();
}
   
/*	out:
*		the last knot's value, or 0 if empty
*/
template<class CoordinateN, class BoxDataN, class VectorN>
double Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::GetLastKnot () const
{
   	return knotVector.GetLast ();
}

/*	in:
*		index, the index of the knot to get
*	out:
*		the index-th knot's value, or 0 if index is invalid
*/
template<class CoordinateN, class BoxDataN, class VectorN>
double Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::GetKnot (UInt32 index) const
{
	return knotVector[index];
}
  
/*	in:
*		index, the index of the knot to set
*		knot, the new value to set
*	if the index is valid save the old knot, and replace it with the new. 
*  if the NURBS is still valid, returns, else undo the change
*/
template<class CoordinateN, class BoxDataN, class VectorN>
void	Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::SetKnot (UInt32 index, double knot)
{
  	double oldKnot = GetKnot (index);
  	knotVector[index] = knot;
  	if (!Check ()) {
  		knotVector[index] = oldKnot;
  		DBBREAK_STR ("invalid knot value in SetKnot");
  	}
}
  
/*	out:
*		the number of knots in the knotvector
*/
template<class CoordinateN, class BoxDataN, class VectorN>
UInt32	Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::GetKnotCount () const
{
  	return knotVector.GetSize ();
}


// Index of the first control point which has geometrical effect on the curve at param (changing that control point changes curve there)
template<class CoordinateN, class BoxDataN, class VectorN>
UIndex	Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::GetLowestEffectiveControlPointIndexAtParam (double t) const
{
	GS::CutToRange (t, GetDomainStart (), GetDomainEnd ());
	UIndex knotSpanIndex = knotVector.FindMaxKnotSpan (t);
	DBASSERT (knotSpanIndex >= GetDegree ());
	UIndex result = knotSpanIndex - GetDegree ();
	DBASSERT (result < GetControlPointCount ());
	return result;
}


// Index of the last control point which has geometrical effect on the curve at param (changing that control point changes curve there)
template<class CoordinateN, class BoxDataN, class VectorN>
UIndex	Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::GetHighestEffectiveControlPointIndexAtParam (double t) const
{
	GS::CutToRange (t, GetDomainStart (), GetDomainEnd ());
	UIndex knotSpanIndex = knotVector.FindMinKnotSpan (t);
	UIndex result = knotSpanIndex;
	DBASSERT (result < GetControlPointCount ());
	return result;
}

template<class CoordinateN, class BoxDataN, class VectorN>
double Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::GetDomainStart () const
{
	return knotVector[GetDegree ()];		// skip the first degree knot points
}

template<class CoordinateN, class BoxDataN, class VectorN>
double Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::GetDomainEnd () const
{
	return knotVector[knotVector.GetSize () - 1 - GetDegree ()];	// skip the last degree knot points
}
  
/*	out:
*		the number of weights
*/
template<class CoordinateN, class BoxDataN, class VectorN>
UInt32	Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::GetWeightCount () const
{
  	return weights.GetSize ();
}
  
/*	in:
*		index, the index of the weight to get
*	out:
*		the index-th weight's value, or 0 if index is invalid
*/
template<class CoordinateN, class BoxDataN, class VectorN>
double	Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::GetWeight (UInt32 index) const
{
	return weights[index];
}
  
/*	in:
*		index, the index of the weight to set
*		weight, the new value to set
*	if the index is valid, and the new weight is positive, replace the index-th weight with the given, 
*	and set boundingBox invalid
*/
template<class CoordinateN, class BoxDataN, class VectorN>
void	Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::SetWeight (double weight, UInt32 index)
{
  	if (DBERROR (weight < 0))
  		return;
  	weights[index] = weight;
}
  
/*	in:
*		double, point from the knot interval
*	out:
*		CoordinateN : the result of evaluating the NURBS curve at t
*	if the point is the first, or last knot, returns the corresponding controlpoint,
*	if the point is outside the knot interval, returns the first or last controlpoint,
*	else creates the non-vanishing BSpline base values from knotvector and degree,
*	and calculates the linear combination of the controlpoints, weights, and BSpline values
*/
template<class CoordinateN, class BoxDataN, class VectorN>
CoordinateN		Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::CalculateAt (double t) const {
	DBASSERT (t > GetDomainStart () - EPS && t < GetDomainEnd () + EPS);

	if (t < GetDomainStart ()) 
		t = GetDomainStart ();
	else if (t > GetDomainEnd  ())
		t = GetDomainEnd ();

	if (GS::Abs (t - GetDomainStart ()) < EPS && !IsFloatBegin ()) //the non-floating curve interpolates the first and last controlpoints
		return GetControlPoint (0);

	if (GS::Abs (t - GetDomainEnd ()) < EPS && !IsFloatEnd ())	//the non-floating curve interpolates the first and last controlpoints
		return GetControlPoint (GetControlPointCount () - 1);

	// Find knot span that contains the t parameter and also get B-Spline values that affect the calculation.
	BSpline spline (knotVector);
	GS::ArrayFB<double, BSpline::AssumedMaxDegree + 1> bSplineValues;
	const UIndex spanIndex = spline.GetEffectiveBSplineValues (bSplineValues, t);

	// Calculate linear combination of B-Spline values and relevant control points to get the final result.
	double norm = 0.0;
	VectorN result = GetVectorWithCoordinates <VectorN> (0);

	for (UIndex i = 0; i <= GetDegree (); ++i) {
		double factor = bSplineValues[i] * weights[spanIndex - GetDegree () + i];
		norm += factor;
		result += factor * VectorN (controlPoints[spanIndex - GetDegree () + i]);
	}

	return CoordinateN (result / norm);
}


/*	if the point is the first, or last knot, returns the corresponding controlpoint,
*	if the point is outside the knot intervall, returns the first or last controlpoint
*	else creates the BSpline base with degree, and knotvector, 
*	 and calculates the linear combination of the controlpoints, weights, and BSpline values
*/
template<class CoordinateN, class BoxDataN, class VectorN>
void	Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::SetReverseDirection ()
{
  	GS::Array<CoordinateN> newControlPoints;
  	newControlPoints.SetSize (controlPoints.GetSize ());
  	for (UInt32 i = 0; i < controlPoints.GetSize (); i++)
  		newControlPoints[i] = GetControlPoint (controlPoints.GetSize () - i - 1);
  
  	GS::Array<double> newWeights;
  	newWeights.SetSize (weights.GetSize ());
  	for (UInt32 i = 0; i < weights.GetSize (); i++)
  		newWeights[i] = GetWeight (weights.GetSize () - i - 1);
  
  	GS::Array<double> newKnotVector;
  	newKnotVector.SetSize (knotVector.GetSize ());
  	for (UInt32 i = 0; i < knotVector.GetSize (); i++)
  		newKnotVector[i] = GetLastKnot () - GetKnot (knotVector.GetSize () - i - 1);
  
  	controlPoints = newControlPoints;
  	weights = newWeights;
  	knotVector = KnotVector (newKnotVector);

	SetCalculatedDegree ();

	DBASSERT (Check ());
}
/*	in:
*		transformation matrix reference
*	transforms all controlpoints
*/
template<>
inline void	Geometry::NurbsCurveBase <Point2D, Box2DData, Vector2D>::Transform (const TRANMAT& tran)
{
	if (tran.IsIdentity ())
		return;
	for (UInt32 i = 0; i < controlPoints.GetSize (); i++)
		controlPoints[i] = Geometry::Transform2dPoint (tran, controlPoints[i]);
}
template<>
inline void	Geometry::NurbsCurveBase <Point3D, Box3D, Vector3D>::Transform (const TRANMAT& tran)
{
	if (tran.IsIdentity ())
		return;
	for (UInt32 i = 0; i < controlPoints.GetSize (); i++)
		controlPoints[i] = Geometry::TransformPoint (tran, controlPoints[i]);
}
template<>
inline GS::Array<Point2D>	Geometry::NurbsCurveBase <Point2D, Box2DData, Vector2D>::GetTransformatedControlPoints (const TRANMAT& tran) const
{
	if (tran.IsIdentity ())
		return controlPoints;

	GS::Array<Point2D> res = controlPoints;
	for (UInt32 i = 0; i < res.GetSize (); i++) {
		res[i] = Geometry::Transform2dPoint (tran, res[i]);
	}
	return res;
}
template<>
inline GS::Array<Point3D> Geometry::NurbsCurveBase <Point3D, Box3D, Vector3D>::GetTransformatedControlPoints (const TRANMAT& tran) const
{
	if (tran.IsIdentity ())
		return controlPoints;

	GS::Array<Point3D> res = controlPoints;
	for (UInt32 i = 0; i < res.GetSize (); i++) {
		res[i] = Geometry::TransformPoint (tran, res[i]);
	}
	return res;
}

/*	out:
*		boundingbox of the controlpolygon
*	if the controlpoints is not empty initializes 4 doubles with the firstcoord's x and y values (both twice),  
*  then iterates the controlpoints, and if any is outside the box made of the four values, the corresponding value will be modified.
*/

template<class CoordinateN, class BoxDataN, class VectorN>
BoxDataN Geometry::NurbsCurveBase<CoordinateN, BoxDataN, VectorN>::CalculateControlPointsBoundingBox(const TRANMAT& tran /*= Geometry::IdentityTranMat*/) const
{
	GS::Array<CoordinateN> transformatedControlPoints = GetTransformatedControlPoints (tran);
	return CalculateControlPointsBoundingBoxNoTransformation (transformatedControlPoints);
}


template<>
inline Box2DData	Geometry::NurbsCurveBase <Point2D, Box2DData, Vector2D>::CalculateControlPointsBoundingBoxNoTransformation (const GS::Array<Point2D>& cp)
{
	if (cp.IsEmpty ())
		return InvalidBoundingBox <Box2DData> ();
	
	Box2DData res = {};
	Geometry::BoxBoundCoords (cp, &res);
	return res;
}
template<>
inline Box3D	Geometry::NurbsCurveBase <Point3D, Box3D, Vector3D>::CalculateControlPointsBoundingBoxNoTransformation (const GS::Array<Point3D>& cp)
{
	if (cp.IsEmpty ())
		return InvalidBoundingBox <Box3D> ();

	Box3D res = {};
	Geometry::Box3DBoundCoords (cp, &res);
	return res;
}
 
/*	in:
*		2DCoord move vector
*	add move vector to all controlpoints
*/
template<class CoordinateN, class BoxDataN, class VectorN>
void	Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::Move(VectorN a) 
{
  	for (UInt32 i = 0; i < controlPoints.GetSize (); i++) {
  		controlPoints[i] += a;
  	}
}
  
/*	in:
*		other : NURBS reference
*		smoothnes : smoothness at the connecting points
*	Append the other-s begin to this end. remove the last knot point, and append others all knotpoints+this's last knot
*	move others all controlpoint with other's first controlopoint - this's last controlpoint, and append others controlpoints, and weights
*	to this controlpoint array and weight array
*	if smoothness is not zero the connection point wont be interpolated, as the first corresponding knots will decreased, the last will be increased with smoothness
*	(so far it wont make the NURBS invalid)
*/
template<class CoordinateN, class BoxDataN, class VectorN>
void	Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::Append (const Geometry::NurbsCurveBase<CoordinateN, BoxDataN, VectorN>& other, double smoothness)
{
  	if (DBERROR (GetDegree () != other.GetDegree ()))
  		return;
  
	if (DBERROR (IsFloatEnd () || other.IsFloatBegin ()))
		return;

	GS::Array<double> knotValues = knotVector.GetValues ();
  	knotValues.Pop ();
  
  	double endSize = knotValues.GetLast ();
  
  	for (UInt32 i = GetDegree () + 1; i < other.GetKnotCount (); i++)
  		knotValues.Push (other.GetKnot (i) + endSize - other.GetFirstKnot ());
  
  	if (smoothness > EPS) {
  		UInt32 first = knotValues.FindFirst (endSize);
  		UInt32 last  = knotValues.FindLast (endSize);
  		if (knotValues[first] - smoothness > knotValues[first - 1] &&
  			knotValues[last] + smoothness < knotValues[last + 1])
		{
  			knotValues[first] = knotValues[first] - smoothness;
  			knotValues[last] = knotValues[last] + smoothness;
  		} else {
  			DBBREAK_STR ("Invalid smoothness value in NurbsCurveBase::Append");
  		}
  	}
	knotVector = KnotVector (std::move (knotValues), GetDegree ());

  	VectorN firstCoordVector = VectorN (other.controlPoints.GetFirst ());
  	VectorN endCoordVector = VectorN (controlPoints.GetLast ());
  
  	for (UInt32 i = 1; i < other.controlPoints.GetSize (); i++) {
  		VectorN x = endCoordVector + VectorN(other.GetControlPoint (i)) - firstCoordVector;
  		controlPoints.Push (CoordinateN (x));
  		weights.Push (other.GetWeight (i));
  	}
  		
	DBASSERT (Check ());
}
  
/*	in:
*		newknot : new knot to insert into knotvector
*	Insert a new knot into the knotvector (and a new controlpoint, and weight)
*	see: http://www.cs.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/NURBS/NURBS-knot-insert.html
*  the curve wont change
*/
template<class CoordinateN, class BoxDataN, class VectorN>
void	Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::InsertKnot (double newKnot)
{
  	if (DBERROR (newKnot < GetFirstKnot () || newKnot > GetLastKnot ()))
  		return;
  
  	UInt32 lastIdx = 0;
  	while (GetKnot (lastIdx) <= newKnot)
  			lastIdx++;
  
  	UInt32 firstIdx = lastIdx - GetDegree ();
  		
  	GS::Array<VectorN> QS;
  	GS::Array<double> WS;
  		
  	for (UInt32 i = firstIdx; i < lastIdx; i++) {
  		double alpha = (newKnot - GetKnot (i)) / (GetKnot (i + GetDegree ()) - GetKnot (i));
  		VectorN nextQ = (1 - alpha) * VectorN (GetControlPoint (i - 1))  * GetWeight (i - 1) + alpha * VectorN (GetControlPoint (i)) * GetWeight (i);
  		double nextW = (1 - alpha) * GetWeight (i - 1) + alpha * GetWeight (i);
  		QS.Push (nextQ / nextW);
  		WS.Push (nextW);
  	}
  
  	for (UInt32 i = firstIdx; i < lastIdx - 1; i++) {
  		weights[i] = WS[i - lastIdx + GetDegree ()];
  		controlPoints[i] = CoordinateN (QS[i - lastIdx + GetDegree ()]);
  	}
  
  	weights.Insert (lastIdx - 1, WS[GetDegree () - 1]);
  	controlPoints.Insert (lastIdx - 1, CoordinateN (QS[GetDegree () - 1]));
  	knotVector.Insert (lastIdx, newKnot);
}
  
/*	in:
    *		left : NURBS reference
    *		right : NURBS reference
    *	Split NURBS into two at the midpoint of the knotvector
    */
template<class CoordinateN, class BoxDataN, class VectorN>
void	Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::Split (Geometry::NurbsCurveBase<CoordinateN, BoxDataN, VectorN>& left, Geometry::NurbsCurveBase<CoordinateN, BoxDataN, VectorN>& right) const
{
    double newKnot = (GetFirstKnot () + GetLastKnot ()) / 2;
    Split (left, right, newKnot);
}
    
/*	in:
    *		left : NURBS reference
    *		right : NURBS reference
    *		knot : knot determining where to cut
    *	create a copy of the NURBS, insert the cut points knot while its multiplicity is not equal degree+1
    *  then create left nurbs from the first point to the cutpoint, and right from cut point to last point.
    */
template<class CoordinateN, class BoxDataN, class VectorN>
void	Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::Split (Geometry::NurbsCurveBase<CoordinateN, BoxDataN, VectorN>& left, Geometry::NurbsCurveBase<CoordinateN, BoxDataN, VectorN>& right, double knot) const
{
    	if (DBERROR (knot < GetFirstKnot () || knot > GetLastKnot ()))
    		return;
    
		if (knot == GetFirstKnot ()) {
    		left.Clear ();
			right = *this;
			return;
		}
		if (knot == GetLastKnot ()) {
			left = *this;
    		right.Clear ();
			return;
		}

    	Geometry::NurbsCurveBase<CoordinateN, BoxDataN, VectorN> tempCopy (*this);
    	
    	while (tempCopy.knotVector.GetMultiplicity (knot) < GetDegree () + 1)
    		tempCopy.InsertKnot (knot);
    		
    	UInt32 k = 0;
    	while (GetKnot (k) < knot)
    		k++;
    // left
		{
			GS::Array<CoordinateN>	leftControlPoints;
			GS::Array<double>		leftWeights;
			GS::Array<double>		leftKnotVector;
    		for (UInt32 i = 0; i < k; i++) {
    			leftControlPoints.Push (tempCopy.GetControlPoint (i));
    			leftWeights.Push (tempCopy.GetWeight (i));
    		}
    		for (UInt32 i = 0; i < k + GetDegree () + 1; i++) {
    			leftKnotVector.Push (tempCopy.GetKnot (i));
    		}
    			
			left = NurbsCurveBase<CoordinateN, BoxDataN, VectorN> (leftControlPoints, leftKnotVector, leftWeights);
			DBASSERT (GetDegree () == left.GetDegree ());
		}
    
    // right 
		{
			GS::Array<CoordinateN>	rightControlPoints;
			GS::Array<double>		rightWeights;
			GS::Array<double>		rightKnotVector;
    		const UInt32 r = tempCopy.controlPoints.GetSize ();
    		for (UInt32 i = k; i < r ; i++) {
    			rightControlPoints.Push (tempCopy.GetControlPoint (i));
    			rightWeights.Push (tempCopy.GetWeight (i));
    		}
    		for (UInt32 i = k; i < r + GetDegree () + 1; i++) {
    			rightKnotVector.Push (tempCopy.GetKnot (i));
    		}
    		right = NurbsCurveBase<CoordinateN, BoxDataN, VectorN> (rightControlPoints, rightKnotVector, rightWeights);
    		DBASSERT (GetDegree () == right.GetDegree ());
		}
}
  

/*	out:
*		boundingbox of the NURBS
*	if the boundingbox is invalid, get the controlpoints boundingbox, intersect the NURBS, then get the union of the parts controlpoints boundingbox
*	if any of the unions side is smaller than the one calculated before, the iteration goes on, we cut the NURBSpart thats controlpoints bounding box
*  touches the previously calculated.
*/
template<class CoordinateN, class BoxDataN, class VectorN>
BoxDataN	Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::CalculateTightBoundingBox (const TRANMAT& tran /*= Geometry::IdentityTranMat*/) const
{
  	if (controlPoints.IsEmpty ())
  		return InvalidBoundingBox <BoxDataN> ();
  
  	GS::Array<Geometry::NurbsCurveBase<CoordinateN, BoxDataN, VectorN>> nurbsParts;
  	nurbsParts.Push (*this);
	BoxDataN calculatedBoundingBox = CalculateControlPointsBoundingBox (tran);
	bool isBoundBoxValid = false;
  	UInt32 counter = 0;
  	while (!isBoundBoxValid || counter < 5) {
  		if (counter++ > 200)
  			break;
  		UInt32 startSize = nurbsParts.GetSize ();
  		for (UInt32 i = 0; i < startSize; i++) {
  			if (!IsBoundingBoxesConnect(nurbsParts[i].CalculateControlPointsBoundingBox (tran), calculatedBoundingBox))
  				continue;
  			Geometry::NurbsCurveBase<CoordinateN, BoxDataN, VectorN> left;
  			Geometry::NurbsCurveBase<CoordinateN, BoxDataN, VectorN> right;
  			nurbsParts[i].Split (left, right);
  			nurbsParts[i] = left;
  			nurbsParts.Push (right);			
  		}
		BoxDataN tempBox = InvalidBoundingBox<BoxDataN> ();
  		for (UInt32 i = 0; i < nurbsParts.GetSize (); i++)
  			BoundingBoxUnion (nurbsParts[i].CalculateControlPointsBoundingBox (tran), &tempBox);
  
		// do not stop if the bounding box have shrinked
  		isBoundBoxValid = !BoundingBoxHull (tempBox, calculatedBoundingBox, EPS);
  	}
  	isBoundBoxValid = true;
  	return calculatedBoundingBox;
}


template<class CoordinateN, class BoxDataN, class VectorN>
void Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::SetCalculatedDegree ()
{
	knotVector.SetDegree (CalculateDegree ());
}


/*	Calculate the degree of the NURBS according to controlpoints, and knots number
*/
template<class CoordinateN, class BoxDataN, class VectorN>
UInt32 Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::CalculateDegree () const
{
	UInt32 degree = 0;
	if (DBVERIFY (GetKnotCount () > GetControlPointCount ())) {
		degree = GetKnotCount () - GetControlPointCount () - 1;
	}
	return degree;
}


template<class CoordinateN, class BoxDataN, class VectorN>
ULong Geometry::NurbsCurveBase<CoordinateN, BoxDataN, VectorN>::GetUsedBytes() const
{
	return sizeof(*this) + GetHeapUsedBytes();
}


template<class CoordinateN, class BoxDataN, class VectorN>
ULong Geometry::NurbsCurveBase<CoordinateN, BoxDataN, VectorN>::GetHeapUsedBytes() const
{
	return GetContainerHeapUsedBytes (controlPoints) + GetContainerHeapUsedBytes (weights) + knotVector.GetHeapUsedBytes();
}


template<class CoordinateN, class BoxDataN, class VectorN>
GSErrCode Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::Read (GS::IChannel& ic)
{
	GS::InputFrame frame (ic, NurbsCurveBasePrivate::classInfo);
	if (frame.GetStatus () != NoError)
		return frame.GetStatus ();
	GSErrCode err;
	switch (frame.GetMainVersion ()) {
		case 1:
			err = ReadVersion1 (ic, frame);
			break;
		case 2:
			err = ReadVersion2 (ic, frame);
			break;
		case 3:
			err = ReadVersion3 (ic, frame);
			break;
		default:
			err = GS::Error;
			DBBREAK_STR ("Geometry::NurbsCurveBase::Read: Unsupported object version");
			break;
	}
	DBASSERT (Check ());
	return err;
}


template<class CoordinateN, class BoxDataN, class VectorN>
GSErrCode Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& /*frame*/)
{
	bool isBoundBoxValid = false;
	BoxDataN readBox;
	GSErrCode err = ic.Read (isBoundBoxValid);
	if (err == NoError)
		err = ic.Read (readBox);
	if (err == NoError)
		err = controlPoints.Read (ic);
	if (err == NoError)
		err = weights.Read (ic);
	if (err == NoError)
		err = knotVector.ReadVersion1 (ic);
	SetCalculatedDegree ();
	return err;
}


template<class CoordinateN, class BoxDataN, class VectorN>
GSErrCode Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::ReadVersion2 (GS::IChannel& ic, const GS::InputFrame& /*frame*/)
{
	bool isBoundBoxValid = false;
	BoxDataN readBox;
	GSErrCode err = ic.Read (isBoundBoxValid);
	if (err == NoError)
		err = ic.Read (readBox);
	if (err == NoError)
		err = controlPoints.Read (ic);
	if (err == NoError)
		err = weights.Read (ic);
	if (err == NoError)
		err = knotVector.ReadVersion1 (ic);
	UInt32 degree = 0;
	if (err == NoError)
		err = ic.Read (degree);

	SetCalculatedDegree ();
	DBASSERT (degree == GetDegree ());

	return err;
}


template<class CoordinateN, class BoxDataN, class VectorN>
GSErrCode Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::ReadVersion3 (GS::IChannel& ic, const GS::InputFrame& /*frame*/)
{
	GSErrCode err = controlPoints.Read (ic);
	if (err == NoError)
		err = weights.Read (ic);
	if (err == NoError)
		err = knotVector.ReadVersion2 (ic);
	return err;
}


template<class CoordinateN, class BoxDataN, class VectorN>
GSErrCode Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::Write (GS::OChannel& oc) const
{
	GS::OutputFrame frame (oc, NurbsCurveBasePrivate::classInfo);
	GSErrCode err;
	switch (frame.GetMainVersion ()) {
		case 1:
			err = WriteVersion1 (oc, frame);
			break;
		case 2:
			err = WriteVersion2 (oc, frame);
			break;
		case 3:
			err = WriteVersion3 (oc, frame);
			break;
		default:
			err = GS::Error;
			DBBREAK_STR ("Geometry::NurbsCurveBase::Write: Unsupported object version");
			break;
	}
	return err;
}


template<class CoordinateN, class BoxDataN, class VectorN>
GSErrCode Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& /*frame*/) const
{
	BoxDataN boundingBoxToWrite;
	const bool isBoundBoxValid = false;
	GSErrCode err = oc.Write (isBoundBoxValid);
	if (err == NoError)	
		err = oc.Write (boundingBoxToWrite);
	if (err == NoError)
		err = controlPoints.Write (oc);
	if (err == NoError)
		err = weights.Write (oc);
	if (err == NoError)
		err = knotVector.WriteVersion1 (oc);
	return err;
}


template<class CoordinateN, class BoxDataN, class VectorN>
GSErrCode Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::WriteVersion2 (GS::OChannel& oc, const GS::OutputFrame& /*frame*/) const
{
	BoxDataN boundingBoxToWrite;
	const bool isBoundBoxValid = false;
	GSErrCode err = oc.Write (isBoundBoxValid);
	if (err == NoError)	
		err = oc.Write (boundingBoxToWrite);
	if (err == NoError)
		err = controlPoints.Write (oc);
	if (err == NoError)
		err = weights.Write (oc);
	if (err == NoError)
		err = knotVector.WriteVersion1 (oc);
	if (err == NoError) {
		UInt32 degree = knotVector.GetDegree ();
		err = oc.Write (degree);
	}
	return err;
}


template<class CoordinateN, class BoxDataN, class VectorN>
GSErrCode Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::WriteVersion3 (GS::OChannel& oc, const GS::OutputFrame& /*frame*/) const
{
	GSErrCode err = controlPoints.Write (oc);
	if (err == NoError)
		err = weights.Write (oc);
	if (err == NoError)
		err = knotVector.WriteVersion2 (oc);
	return err;
}


template<class CoordinateN, class BoxDataN, class VectorN>
GSErrCode  Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::ReadXML (GS::XMLIChannel& ic)
{
	UInt32 temp = 0;
	GS::XMLITag iTag (ic, NurbsCurveBasePrivate::XMLTag_NURBS);

	GSErrCode err = NoError;
	UInt32 degree = 0;
 	if (err == NoError)
 		err = ic.ReadXML (NurbsCurveBasePrivate::XMLTag_Degree, degree);
	knotVector.SetDegree (degree);
	if (err == NoError)
		err = ic.ReadXML (NurbsCurveBasePrivate::XMLTag_ControlPointCount, temp);
	if (err == NoError) {
		controlPoints.SetSize (temp);
		err = ic.ReadStartElement (NurbsCurveBasePrivate::XMLTag_ControlPoints);
	}
	for (UInt32 i = 0; i < temp; i++) {
		if (err == NoError)
			err = ic.ReadStartElement (NurbsCurveBasePrivate::XMLTag_ControlPoint);
		if (err == NoError)
			err = ReadFromXMLPoint (ic, controlPoints[i]);
		if (err == NoError)
			err = ic.ReadEndElement (NurbsCurveBasePrivate::XMLTag_ControlPoint);
	}
	if (err == NoError)
		err = ic.ReadEndElement (NurbsCurveBasePrivate::XMLTag_ControlPoints);

	if (err == NoError)
		err = ic.ReadXML (NurbsCurveBasePrivate::XMLTag_WeightCount, temp);
	if (err == NoError) {
		weights.SetSize (temp);
		err = ic.ReadStartElement (NurbsCurveBasePrivate::XMLTag_Weights);
	}
	for (UInt32 i = 0; i < temp; i++) {
		if (err == NoError)
			err = ic.ReadXML (NurbsCurveBasePrivate::XMLTag_Weight, weights[i]);
	}
	if (err == NoError)
		err = ic.ReadEndElement (NurbsCurveBasePrivate::XMLTag_Weights);

	if (err == NoError)
		err = ic.ReadXML (NurbsCurveBasePrivate::XMLTag_KnotCount, temp);
	if (err == NoError) {
		knotVector.SetSize (temp);
		err = ic.ReadStartElement (NurbsCurveBasePrivate::XMLTag_Knots);
	}
	for (UInt32 i = 0; i < temp; i++) {
		if (err == NoError)
			err = ic.ReadXML (NurbsCurveBasePrivate::XMLTag_Knot, knotVector[i]);
	}
	if (err == NoError)
		err = ic.ReadEndElement (NurbsCurveBasePrivate::XMLTag_Knots);

	DBASSERT_GUID (Check (), "{9621A3FB-8DDC-4D2F-A0B2-B051DACDE498}");

	return err;
}
		
template<class CoordinateN, class BoxDataN, class VectorN>
GSErrCode  Geometry::NurbsCurveBase <CoordinateN, BoxDataN, VectorN>::WriteXML (GS::XMLOChannel& oc) const
{
	GS::XMLTag tagContour (oc, NurbsCurveBasePrivate::XMLTag_NURBS);
	GSErrCode err = NoError;
	const UInt32 degree = GetDegree ();
	if (err == NoError)
		err = oc.WriteXML (NurbsCurveBasePrivate::XMLTag_Degree, degree);
	if (err == NoError)
		err = oc.WriteXML (NurbsCurveBasePrivate::XMLTag_ControlPointCount, GetControlPointCount ());
	if (err == NoError)
		err = oc.WriteStartElement (NurbsCurveBasePrivate::XMLTag_ControlPoints);
	for (UInt32 i = 0; i < GetControlPointCount (); i++) {
		if (err == NoError) 
			err = oc.WriteStartElement (NurbsCurveBasePrivate::XMLTag_ControlPoint);
		if (err == NoError) 
			err = WriteToXMLPoint (oc, GetControlPoint (i));
		if (err == NoError) 
			err = oc.WriteEndElement ();
	}
	if (err == NoError)
		err = oc.WriteEndElement ();

	if (err == NoError)
		err = oc.WriteXML (NurbsCurveBasePrivate::XMLTag_WeightCount, GetWeightCount ());
	if (err == NoError)
		err = oc.WriteStartElement (NurbsCurveBasePrivate::XMLTag_Weights);
	for (UInt32 i = 0; i < GetWeightCount (); i++) {
		if (err == NoError)
			err = oc.WriteXML (NurbsCurveBasePrivate::XMLTag_Weight, weights[i]);
	}
	if (err == NoError)
		err = oc.WriteEndElement ();

	if (err == NoError)
		err = oc.WriteXML (NurbsCurveBasePrivate::XMLTag_KnotCount, GetKnotCount ());
	if (err == NoError)
		err = oc.WriteStartElement (NurbsCurveBasePrivate::XMLTag_Knots);
	for (UInt32 i = 0; i < GetKnotCount (); i++) {
		if (err == NoError)
			err = oc.WriteXML (NurbsCurveBasePrivate::XMLTag_Knot, knotVector[i]);
	}
	if (err == NoError)
		err = oc.WriteEndElement ();

	return err;
}	


#endif
