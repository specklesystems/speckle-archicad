// *********************************************************************************************************************
// Description:		Template utility functions for MeshBody, IMeshBody and CandidateElem
//
// Module:			GSModeler
// Namespace:		Modeler
// Contact person:	FGY
//
// SG compatible
// *********************************************************************************************************************

#if !defined (MESHBODYUTILTEMPLATES_HPP)
#define MESHBODYUTILTEMPLATES_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from C runtime
#include	<stdlib.h>

// from GSRoot
#include	"Definitions.hpp"
#include	"HashSet.hpp"
#include	"BaseAlgorithms.hpp"
#include	"GSProcessControl.hpp"

// from PointCloud
#include	"PointCloudBox.hpp"

#include	"MeshBrepAccessors.hpp"
#include	"Model3D/DataCmpOption.hpp"
#include	"Model3D/model.h"
#include	"Model3D/PolygonAttributes.hpp"
#include	"Model3D/EdgeAttributes.hpp"
#include	"Model3D/MeshBodyUtils.hpp"
#include	"Model3D/ModelerAttributes.hpp"
#include	"Model3D/MeshBody.hpp"
#include	"Model3D/BodyMemberComparator.hpp"
#include	"Model3D/TextureCoordSys.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

//namespace Modeler {

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------


template <typename Type, typename StructType, typename ContainerType, Type StructType::*MemberPointer>
class MemberArray
{
private:
	const ContainerType& container;
	const bool empty;
public:
	typedef Type ValueType;

	MemberArray (const ContainerType& container, bool empty) : container (container), empty (empty) {}

	const Type&	operator [] (UIndex index) const	{ DBASSERT (!empty); return container [index].*MemberPointer; }
	USize		GetSize () const					{ return empty ? 0 : container.GetSize (); }
};


// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------


template <class MeshBodyType>
void GetBegVertPosForPedgTemplate (const MeshBodyType& body, Int32 pedg, COORD3* pos)
{
	DBASSERT (pedg != 0);
	const EDGE& edge	= body.GetConstEdge (GS::Abs(pedg) - 1);
	Int32 vertIdx		= (pedg > 0) ? edge.vert1 : edge.vert2;
	body.GetVertexCoords (vertIdx, Geometry::IdentityTranMat, &pos->x, &pos->y, &pos->z);
}

template <class MeshBodyType>
void GetEndVertPosForPedgTemplate (const MeshBodyType& body, Int32 pedg, COORD3* pos)
{
	DBASSERT (pedg != 0);
	const EDGE& edge	= body.GetConstEdge (GS::Abs(pedg) - 1);
	Int32 vertIdx		= (pedg > 0) ? edge.vert2 : edge.vert1;
	body.GetVertexCoords (vertIdx, Geometry::IdentityTranMat, &pos->x, &pos->y, &pos->z);
}


template <class MeshBodyType>
class CompactConstPolygon {
public:
	enum VertexOrdering {Oriented, AsItIsStored};
private:
	const MeshBodyType&			body;
	const UInt32			polygonIdx;
	const Modeler::PGON&	pgon;

	Int32					actualPolygonEdgeIdx;
	Int32					actualPolyEdge;
	const TRANMAT*				tran;
public:
	//------------------
	//		ctor(s)
	//------------------
	CompactConstPolygon (const MeshBodyType& body, UInt32 polygonIdx, const TRANMAT& tran = Geometry::IdentityTranMat)
		:	body								(body),
			polygonIdx							(polygonIdx),
			pgon								(body.GetConstPolygon (polygonIdx)),

			actualPolygonEdgeIdx				(pgon.fpedg),
			actualPolyEdge						(body.GetConstPolyEdge (actualPolygonEdgeIdx)),
			tran								(&tran) // TODO TBa
	{
		DBERROR (actualPolygonEdgeIdx < 0 || static_cast<UInt32>(actualPolygonEdgeIdx) >= body.GetPolyEdgeCount ());
		DBERROR (actualPolyEdge == 0);
	}
	// ------------------
	//	Properties
	// ------------------
	inline bool IsValid () const							
	{ 
		return (pgon.lpedg - pgon.fpedg + 1/*Number of edges*/ >= 3);
	}
	// ------------------
	// Data Access
	// ------------------
	inline const Modeler::PGON& Get () const								
	{
		return pgon;															
	}
	inline const MeshBodyType& GetMeshBody () const
	{
		return body;
	}
	inline UInt32 GetPolygonIdx () const
	{
		return polygonIdx;
	}
	inline const TRANMAT* GetTran () const
	{
		return tran;
	}

	inline Int32 GetActualPolyEdge () const // It is known from the false Next return value if actualPolyEdge == 0					
	{ 
		DBERROR (IsEnd ());
		DBERROR (actualPolyEdge == 0);
		return actualPolyEdge;
	}
	inline const EDGE& GetActualEdge () const
	{
		DBERROR (IsEnd ());
		return body.GetConstEdge (GS::Abs (GetActualPolyEdge ()) - 1);
	}
	inline void GetActualEdgeVertices (Coord3D& v1, Coord3D& v2, VertexOrdering ordering = Oriented) const
	{
		DBERROR (IsEnd ());
		v1 = body.GetVertexPoint (ordering == Oriented && GetActualPolyEdge () < 0 ? GetActualEdge ().vert2 : GetActualEdge ().vert1, *tran);
		v2 = body.GetVertexPoint (ordering == Oriented && GetActualPolyEdge () < 0 ? GetActualEdge ().vert1 : GetActualEdge ().vert2, *tran);
	}
	inline Coord3D GetActualVertex () const
	{
		DBERROR (IsEnd ());
		return body.GetVertexPoint (GetActualPolyEdge () > 0 ? GetActualEdge ().vert1 : GetActualEdge ().vert2, *tran);
	}
	// ---------------
	//	  Iterators
	// ---------------
	inline void ResetIterator ()
	{ 
		actualPolygonEdgeIdx	= pgon.fpedg;
		actualPolyEdge			= body.GetConstPolyEdge (actualPolygonEdgeIdx);
	}
	inline bool IsEnd () const
	{
		return static_cast <Int32> (actualPolygonEdgeIdx) > pgon.lpedg;								
	}
	inline bool Next ()														
	{
		DBBREAK_STR ("Not tested yet!!! Test it! Fix it if necessary and remove this break!");
		++actualPolygonEdgeIdx;
		actualPolyEdge = body.GetConstPolyEdge (actualPolygonEdgeIdx);
		if (actualPolyEdge == 0){
			return false;
		}
		return true;
	}
	inline void NextNonHole ()														
	{
		++actualPolygonEdgeIdx;
		if (!IsEnd ()) {
			actualPolyEdge = body.GetConstPolyEdge (actualPolygonEdgeIdx);
			if (actualPolyEdge == 0){
				++actualPolygonEdgeIdx;
				if (!IsEnd ()) {
					actualPolyEdge = body.GetConstPolyEdge (actualPolygonEdgeIdx);
					if (actualPolyEdge == 0){
						DBBREAK_STR ("Invalid body: Empty hole!");
						while (actualPolyEdge == 0 && !IsEnd ()) {
							actualPolyEdge = body.GetConstPolyEdge (actualPolygonEdgeIdx++);
						}
					}
				}
			}
		}
		
	}
};

template <class MeshBodyType>
void CalcPolygonNormalAreaMidpoint (	CompactConstPolygon<MeshBodyType>&			compactPoly,
										Coord3D&								midpoint,
										Vector3D&								normal)


{
	// Preconidtion(s)
	DBASSERT (compactPoly.IsValid ());

	// Calculate the midpoint of the polygon.
	midpoint.Set (0, 0, 0);
	ULong numOfVertices	= 0;
	for (compactPoly.ResetIterator (); !compactPoly.IsEnd (); compactPoly.NextNonHole (), ++numOfVertices){ // Iterate over the vertices of the polygon.
		midpoint += compactPoly.GetActualVertex ();
	}
	midpoint /= static_cast<double> (numOfVertices);

	// Calculate the plane of the polygon based on the Newell's method (for a reference see ISBN 0-88175-108-1 p. 217.).
	// As a bypass the length of the normal vector will be equal to the surface of the polygon.
	normal.Set (0, 0, 0);
	Coord3D	v1, v2;
	for (compactPoly.ResetIterator (); !compactPoly.IsEnd (); compactPoly.NextNonHole ()){ // Iterate over the edges of the polygon.

		compactPoly.GetActualEdgeVertices (v1, v2);
		normal.x += (v1.y - v2.y) * (v1.z + v2.z - midpoint.z * 2);
		normal.y += (v1.z - v2.z) * (v1.x + v2.x - midpoint.x * 2);
		normal.z += (v1.x - v2.x) * (v1.y + v2.y - midpoint.y * 2);
	}
	normal /= 2.;
}


//Exporting in VTK format, use paraview to visualize the geometry. AACs
template <class MeshBodyPointer> 
void exportToVTK (MeshBodyPointer geometry, const char * fname, const bool addHardVertices = false, const bool addSharpEdges = false)
{
	FILE * fout = fopen (fname, "w");
	if (fout)
	{
		const USize numPoints = geometry->GetVertexCount (); 
		const USize numPolygons = geometry->GetPolygonCount (); 

		ULong i, NumPolDef; 
		GS::HashSet<ULong> hardVerts; 

		fprintf (fout, "# vtk DataFile Version 2.0\n"); 
		fprintf (fout, "FileName is '%s'\n", fname); 
		fprintf (fout, "ASCII\n"); 
		fprintf (fout, "DATASET POLYDATA\n"); 

		fprintf (fout, "POINTS %d float\n", (GS::IntForStdio) numPoints); 
		for (i = 0; i < numPoints; ++i)
		{
			double x, y, z; 
			geometry->GetVertexCoords (i, Geometry::IdentityTranMat, &x, &y, &z);
			fprintf (fout, "%g %g %g \n", x, y, z); 
			bool hf = geometry->GetVertexHardFlag (i);
			if (hf && addHardVertices) hardVerts.Add (i);
		}

		GS::Array<USize> nVerts;
		nVerts.SetSize (numPolygons);
		nVerts.Fill	(0);

		for (i = 0, NumPolDef = 0; i < numPolygons; ++i)
		{
			const Modeler::PGON & pgon = geometry->GetConstPolygon (i); 
			for (Int32 ipedg = pgon.fpedg; ipedg <= pgon.lpedg; ++ipedg) {
				const Int32	pedg = geometry->GetConstPolyEdge (ipedg);
				if (pedg != 0) {
					//just counting! 
					++NumPolDef;
					++nVerts[i];
				}
				else {
					break; //for now, we are not doing the holes!!! REVISIT!
				}
			}
			NumPolDef += 1;  //VTK!!!!
		}

		if (addHardVertices) {
			USize numHardVerts = hardVerts.GetSize ();
			fprintf (fout, "VERTICES %d %d \n", (GS::IntForStdio) numHardVerts, (GS::IntForStdio) (numHardVerts * 2));
			for (GS::HashSet<ULong>::ConstIterator it = hardVerts.Begin (); it != hardVerts.End (); ++it) {
				fprintf (fout, "1 %d\n", (GS::IntForStdio) *it ); 
			}
		}

		GS::HashSet<ULong> sharpEdges; 
		if (addSharpEdges)
		{
			for (i = 0; i < numPolygons; ++i)
			{
				const Modeler::PGON & pgon = geometry->GetConstPolygon (i); 
				for (Int32 ipedg = pgon.fpedg; ipedg <= pgon.lpedg; ++ipedg) {
					const Int32	pedg = geometry->GetConstPolyEdge (ipedg);
					if (pedg != 0) {
						const ULong	iedge = GS::Abs (pedg) - 1;
						if (geometry->GetConstEdgeAttributes (iedge).IsSharp ()) {
							sharpEdges.Add (iedge);
						}
					}
				}
			}

			USize numSharpEdge = sharpEdges.GetSize ();
			fprintf (fout, "LINES %d %d \n", (GS::IntForStdio) numSharpEdge, (GS::IntForStdio) (numSharpEdge * 3));
			for (GS::HashSet<ULong>::ConstIterator it = sharpEdges.Begin (); it != sharpEdges.End (); ++it) {
				const EDGE& edge = geometry->GetConstEdge (*it);
				fprintf (fout, "2 %d %d\n", (GS::IntForStdio) edge.vert1, (GS::IntForStdio) edge.vert2 ); 
			}
		}

		fprintf (fout, "POLYGONS %d %d \n", (GS::IntForStdio) numPolygons, (GS::IntForStdio) NumPolDef);

		for (i = 0; i < numPolygons; ++i)
		{
			fprintf (fout, "%d ", (GS::IntForStdio) nVerts[i]);

			const Modeler::PGON & pgon = geometry->GetConstPolygon (i); 
			for (Int32 ipedg = pgon.fpedg; ipedg <= pgon.lpedg; ++ipedg) {
				const Int32	pedg = geometry->GetConstPolyEdge (ipedg);
				if (pedg != 0) {
					const ULong	iedge = GS::Abs (pedg) - 1;
					const EDGE& edge = geometry->GetConstEdge (iedge);
					Int32 vert;
					if(pedg > 0)	vert = edge.vert1; 
					else			vert = edge.vert2;

					fprintf (fout, "%d ", (GS::IntForStdio) vert); 
				}
				else {
					break; //for now, we are not doing the holes!!! REVISIT!
				}
			}
			fprintf (fout, "\n"); 
		}


		fclose(fout);
	}
}

template<class MeshBodyType>
void	PolygonTransformationTemplate (MeshBodyType& body, Int32 rivect, double* coz, double* siz,
										  double* coxy, double* sixy)
{
	Int32	ivect;
	const Vector3D	*avect;
	double	x, y, z;

	ivect = (rivect > 0) ? - 1 + rivect : - 1 - rivect;
	avect = &body.GetConstPolyNormal (ivect);
	if (rivect > 0) {
		x = avect->x;
		y = avect->y;
		z = avect->z;
	} else {
		x = -avect->x;
		y = -avect->y;
		z = -avect->z;
	}

	Geometry::TMDirCoeffs (x, y, z, coz, siz, coxy, sixy);
}

// ---------------------------------------------------------------------------------------------------------------------
/*																			*/
/*							CHECK NORMAL VECTOR DIRECTION					*/
/*									0: good									*/
/*									1: opposite	contour						*/
/*									2: contour good, hole(s) wrong			*/
/*									3: Wrong pedg list ( 0,.)				*/
/*									4: Zero area							*/
/*																			*/
// ---------------------------------------------------------------------------------------------------------------------
template <class MeshBodyType, class PedgIteratorT>
short	CheckPgonNormalTemplate (const MeshBodyType& body, Int32 rivect,
						   PedgIteratorT pedgBegin, PedgIteratorT pedgEnd,
						   bool holecheck, bool strong)

{	Int32	i, ivert, v1, v2;
	Int32	apedg;
	double	coz, siz, coxy, sixy;
	double	vx, vy, vz, x, y, x0, y0, ig;
	bool	inhole, first, cw;
	const EDGE	*aedge;

	PolygonTransformationTemplate (body, rivect, &coz, &siz, &coxy, &sixy);

	ig = 0.0;
	x0 = 0.0;
	y0 = 0.0;
	inhole = false;
	first  = true;
	Int32 npedg = static_cast<Int32>(pedgEnd - pedgBegin);
	PedgIteratorT actPedg = pedgBegin;
	for (i = 0; i <= npedg /*Sic!*/; ++i) {
		if (i > npedg - 1) {
			apedg = 0;
		} else {			
			apedg = *actPedg;
			++actPedg;
		}

		if (apedg == 0) {
			if (first) {
				return 3;
			} else {
				if (fabs(ig) < SMALLEPS)
					return 4;

				cw = ig > 0.0;
				if (cw && !inhole) {
					if (strong || ig > EPS)
						return 1;
				}
				if (!cw && inhole) {
					if (strong || ig < -EPS)
						return 2;
				}
			}
			if (!holecheck)
				break;
			inhole = true;
			first = true;
			ig = 0.0;
		} else {
			aedge = &body.GetConstEdge (abs(apedg) - 1);
			v1 = aedge->vert1;
			v2 = aedge->vert2;
			if (first) {
				ivert = (apedg > 0 ? v1 : v2);
				body.GetVertexCoords (ivert, Geometry::IdentityTranMat, &vx, &vy, &vz);
				x0 =  vx * coz * coxy + vy * siz * coxy - vz * sixy;
				y0 = -vx * siz		+ vy * coz;
				first = false;
			}
			ivert = (apedg > 0 ? v2 : v1);
			body.GetVertexCoords (ivert, Geometry::IdentityTranMat, &vx, &vy, &vz);
			x  =  vx * coz * coxy + vy * siz * coxy - vz * sixy;
			y  = -vx * siz		  + vy * coz;
			ig += (x - x0)*(y + y0);
			x0 = x;
			y0 = y;
		}
	}
	return 0;
}

// ---------------------------------------------------------------------------------------------------------------------
/*																			*/
/*						ANGLE OF TWO POLYGON EDGES IS CONCAVE				*/
/*								 1: Concave									*/
/*								 0: Collinear								*/
/*								-1: Convex									*/
/*																			*/
// ---------------------------------------------------------------------------------------------------------------------
template <class MeshBodyType>
short	IsPgonApexConcaveTemplate (const MeshBodyType& body, Int32 ivect, Int32 v1, Int32 v2, Int32 v3)
{
	double	x1, y1, z1, x2, y2, z2, x3, y3, z3, nx, ny, nz, prod;
	double	ll, length;		/*bab410*/

	const Vector3D& avect = body.GetConstPolyNormal (ivect);
	nx = avect.x;
	ny = avect.y;
	nz = avect.z;
	body.GetVertexCoords (v2, Geometry::IdentityTranMat, &x1, &y1, &z1);
	const VERT& avert1 = body.GetConstVertex (v1);
	x2 = avert1.x - x1;
	y2 = avert1.y - y1;
	z2 = avert1.z - z1;
	length = sqrt (x2 * x2 + y2 * y2 + z2 * z2);		/*bab410*/
	if (length < SMALLEPS)
		return 0;
	if (length > 1.0) {
		ll = 1.0 / length;
		x2 *= ll;
		y2 *= ll;
		z2 *= ll;
	}
	const VERT& avert3 = body.GetConstVertex (v3);
	x3 = avert3.x - x1;
	y3 = avert3.y - y1;
	z3 = avert3.z - z1;
	length = sqrt (x3 * x3 + y3 * y3 + z3 * z3);		/*bab410*/
	if (length < SMALLEPS)
		return 0;
	if (length > 1.0) {
		ll = 1.0 / length;
		x3 *= ll;
		y3 *= ll;
		z3 *= ll;
	}
	x1 = y2*z3 - y3*z2;
	y1 = z2*x3 - z3*x2;
	z1 = x2*y3 - x3*y2;
	prod = x1*nx + y1*ny + z1*nz;
	if (fabs(prod) < EPS)		/* there was SMALLEPS */
		return 0;
	return (prod > 0 ? 1 : -1);
}


//////////////////////////////////////////////////////////////////////////////
// See if a loop is convex
//////////////////////////////////////////////////////////////////////////////

// To avoid use of maybe inaccurate normals, it is done by analysis of the sum of convex angles of edge lines at vertices
// It is known that the sum of all inner angles is (n-2)*PI
// If and only if the loop is concave, the sum of convex angles is smaller (convex angle at a concave vertex is smaller than the inner angle)
template<class MeshBodyType, class IteratorType>
bool	IsLoopConvex (const MeshBodyType& body, Int32 fromIPedg, Int32 toIPedg, IteratorType ipedg)
{
	if (DBERROR (*(ipedg + fromIPedg) == 0)) {
		++fromIPedg;
	}
	if (DBERROR (*(ipedg + toIPedg) == 0)) {
		--toIPedg;
	}
	if (DBERROR (fromIPedg >= toIPedg)) {
		return false;
	}
	for (Int32 i = fromIPedg; i <= toIPedg; ++i) {
		if (DBERROR (*(ipedg + i) == 0)) {
			return false;
		}
	}

	// Search last different vertex from first vertex
	Coord3D firstVertPoint;
	GetBegVertPosForPedgTemplate (body, *(ipedg + fromIPedg), &firstVertPoint);
	Vector3D lastEdgeVector (0.0, 0.0, 0.0);
	Int32 lastDifferentFromFirst = toIPedg;	// begin vertex for this pedg will be the last significantly different vertex from first vertex
	for ( ; lastDifferentFromFirst > fromIPedg; --lastDifferentFromFirst) {
		Coord3D currVertPoint;
		GetBegVertPosForPedgTemplate (body, *(ipedg + lastDifferentFromFirst), &currVertPoint);
		lastEdgeVector = firstVertPoint - currVertPoint;
		if (Geometry::UnitVectorPtr3D (&lastEdgeVector, &lastEdgeVector) > EPS) {
			break;
		}
	}

	if (lastDifferentFromFirst <= fromIPedg) {
		return false;
	}

	// Sum smaller (convex) angles at vertices
	Coord3D		prevVertPoint	= firstVertPoint;
	Vector3D	prevEdgeVector	= lastEdgeVector;
	double		angleSum		= 0.0;
	UInt32		angleNumber		= 0;
	for (Int32 i = fromIPedg; i <= lastDifferentFromFirst; ++i) {
		Coord3D currVertPoint;
		if (i == lastDifferentFromFirst) {
			currVertPoint = firstVertPoint;
		} else {
			GetEndVertPosForPedgTemplate (body, *(ipedg + i), &currVertPoint);
		}
		Vector3D currEdgeVector = currVertPoint - prevVertPoint;
		if (Geometry::UnitVectorPtr3D (&currEdgeVector, &currEdgeVector) < EPS) {
			continue;
		}

		// Add convex angle of the two lines of the edges
		double scalarProdNeg = -Geometry::MulsVectors3D (prevEdgeVector, currEdgeVector);
		double smallerAngleAtVert = Geometry::ArcCos (scalarProdNeg);
		angleSum += smallerAngleAtVert;
		++angleNumber;
		
		prevVertPoint	= currVertPoint;
		prevEdgeVector	= currEdgeVector;
	}

	double	expectedAngleSumIfConvex = (angleNumber - 2) * PI;
	return (GS::Abs (angleSum - expectedAngleSumIfConvex) < EPS);
}


/****************************************************************************/
/*																			*/
/*	SEE IF A POLYGON 														*/
/*	- IS CONCAVE, 															*/
/*	- HAS HOLES, 															*/
/*	- HAS CONVEX HOLES,														*/
/*																			*/
/****************************************************************************/
template<class MeshBodyType, class IteratorType>
STATL	CalcLoopConcaveAndHoleStatTemplate (const MeshBodyType& body, Int32 npedg, IteratorType ipedg)
{
	STATL pstat = NORMAL;

	if (npedg < 4) {
		return pstat;
	}

	for (Int32 i = 0; i < npedg; ++i) {
		if (*(ipedg + i) == 0) {
			pstat |= PHOLEBIT | HOLESCNVBIT;
		}
	}

	Int32	contourStart = 0;
	bool	outerContour = true;
	for (Int32 i = 0; i < npedg + 1 /*!!!*/ && ((pstat & CONCAVBIT) == 0 || (pstat & HOLESCNVBIT) != 0); ++i) {
		if (i == npedg || *(ipedg + i) == 0) {
			if (!IsLoopConvex (body, contourStart, i - 1, ipedg)) {
				if (outerContour) {
					pstat |= CONCAVBIT;
				} else {
					pstat &= ~HOLESCNVBIT;
				}
			}
			outerContour = false;
			contourStart = i + 1;
		}
	}
	return pstat;
}
// ---------------------------------------------------------------------------------------------------------------------
/*																			*/
/*								SEARCH FOR A VECTOR							*/
/*																			*/
// ---------------------------------------------------------------------------------------------------------------------
template <class MeshBodyType>
Int32 SearchPgonNormalTemplate (const MeshBodyType& body, Int32 sfvect, Int32 slvect,
					  double x, double y, double z)	/*vv20*/

/* x, y, z :		Unit vector												*/
/* It searches for the same length											*/

{	Int32	i, ivect;
	double	vx, vy, vz;

	if (sfvect > slvect)
		return 0;

	ivect = 0;
	for (i = sfvect; i <= slvect; ++i) {
		const Vector3D& avect = body.GetConstPolyNormal (i);
		vx = avect.x;
		vy = avect.y;
		vz = avect.z;
		if (fabs(x - vx) < VECTEPS &&
			fabs(y - vy) < VECTEPS &&
			fabs(z - vz) < VECTEPS) {
			ivect = i + 1;
			break;
		}
		if (fabs(x + vx) < VECTEPS &&
			fabs(y + vy) < VECTEPS &&
			fabs(z + vz) < VECTEPS) {
			ivect = -(i + 1);
			break;
		}
	}

	return ivect;
}


// ---------------------------------------------------------------------------
/*																			*/
/*							SEARCH FOR NOT SHARP EDGE						*/
/*																			*/
// ---------------------------------------------------------------------------
template <class MeshBodyType>
bool HasSmoothEdgeTemplate (const Modeler::PGON& pgon, const MeshBodyType& body)
{
	for (Int32 ipedg = pgon.fpedg; ipedg <= pgon.lpedg; ++ipedg) {
		const Int32 pedg = body.GetConstPolyEdge (ipedg);
		if (pedg != 0) {
			if (!body.GetConstEdgeAttributes (GS::Abs (pedg) - 1).IsSharp ()) {
				return true;
			}
		}
	}
	return false;
}


// ---------------------------------------------------------------------------
/*																			*/
/*							GET NORMAL VECTOR								*/
/*																			*/
// ---------------------------------------------------------------------------


template <typename MeshBodyType>
Vector3D GetPolygonNormal (const MeshBodyType& body, Int32 ivect)
{
	Vector3D normal = body.GetConstPolyNormal (GS::Abs (ivect) - 1);
	if (ivect < 0) {
		return -normal;
	} else {
		return normal;
	}
}


// ---------------------------------------------------------------------------
/*																			*/
/*							CALCULATING NORMAL VECTOR						*/
/*																			*/
// ---------------------------------------------------------------------------


// Creating (unit) normal vector for the pedg list
// Newell's Method
// Coordinates of result normal vector are proportional to the areas of the projections of polygon contour to the coordinate planes
// Only the outer contour is taken into account !
template <class MeshBodyType>
bool CalculateOneContourNormalTemplate (const MeshBodyType& body, Int32 npedg, const Int32* ipedg, double* nx, double* ny, double* nz)
{
	DBASSERT (ipedg != nullptr && nx != nullptr && ny != nullptr && nz != nullptr);
	if (npedg < 2)
		return false;
	
	if (ipedg [0] == 0) {
		return false;
	}

	double nxx = 0.0, nyy = 0.0, nzz = 0.0;	
	COORD3 prevVertPos, currVertPos;
	GetBegVertPosForPedgTemplate (body, ipedg[0], &prevVertPos);

	for (Int32 j = 0; j < npedg && ipedg[j] != 0; ++j) {
		GetEndVertPosForPedgTemplate (body, ipedg[j], &currVertPos);
		nxx += (prevVertPos.y - currVertPos.y) * (prevVertPos.z + currVertPos.z);
		nyy += (prevVertPos.z - currVertPos.z) * (prevVertPos.x + currVertPos.x);
		nzz += (prevVertPos.x - currVertPos.x) * (prevVertPos.y + currVertPos.y);
		prevVertPos = currVertPos;
	}

	double d = nxx*nxx + nyy*nyy + nzz*nzz;
	if (d > SMALLEPS * SMALLEPS) {
		d = sqrt (d);
		*nx = nxx / d;
		*ny = nyy / d;
		*nz = nzz / d;
		return true;
	} else {
		return false;
	}
}

// 1-dimensional interval with additional data associated with the bounds (cuurently index in pgon - may be templatized)
struct BoundInterval {
private:
	double	lowerValue, higherValue;
	Int32	lowerIdx, higherIdx;		// index of pedg in pgon, of which vertex is at lower/higher bounding value

public:
	BoundInterval () : lowerValue (1.0), higherValue (-1.0), lowerIdx (-1), higherIdx (-1) { }

	void Expand (double newValue, Int32 newBodyVertIdx)
	{
		if (higherValue < lowerValue) {
			SetAsLower (newValue, newBodyVertIdx);
			SetAsHigher (newValue, newBodyVertIdx);
		}
		if (newValue < lowerValue) {
			SetAsLower (newValue, newBodyVertIdx);
		} else if (newValue > higherValue) {
			SetAsHigher (newValue, newBodyVertIdx);
		}
	}

	double GetWidth () {
		if (lowerValue > higherValue) {
			return 0.0;
		} else {
			return higherValue - lowerValue;
		}
	}

	Int32 GetLowerIdx () { return lowerIdx; }
	Int32 GetHigherIdx () { return higherIdx; }

private:
	void SetAsLower (double newValue, Int32 newBodyVertIdx)
	{
		lowerValue	= newValue;
		lowerIdx	= newBodyVertIdx;
	}

	void SetAsHigher (double newValue, Int32 newBodyVertIdx)
	{
		higherValue	= newValue;
		higherIdx	= newBodyVertIdx;
	}
};

// Creating (unit) normal vector for the pedg list
// Look for a large triangle fitted on the vertices of the pedg list and create normal vector of this triangle
// pedg list direction is not taken into account -> normal may be in opposite direction !
template <class MeshBodyType>
bool CalculateLargeTriangleNormalTemplate (const MeshBodyType& body, Int32 npedg, const Int32* ipedg, double* nx, double* ny, double* nz)
{
	DBASSERT (ipedg != nullptr && nx != nullptr && ny != nullptr && nz != nullptr);
	double thisIsSmall = MEDEPS;

	// Look for two distant points - points on the most distant opposite ends of the bounding box will do
	BoundInterval xBounds, yBounds, zBounds;
	Coord3D point;
	bool hasEdge = false;
	for (Int32 i = 0; i < npedg; ++i) {
		if (ipedg[i] == 0) {
			continue;
		}
		hasEdge = true;
		GetBegVertPosForPedgTemplate (body, ipedg[i], &point);
		xBounds.Expand (point.x, i);
		yBounds.Expand (point.y, i);
		zBounds.Expand (point.z, i);
	}
	if (!hasEdge) {
		return false;
	}

	Int32 distantPointIdx1, distantPointIdx2;
	double xWidth = xBounds.GetWidth ();
	double yWidth = yBounds.GetWidth ();
	double zWidth = zBounds.GetWidth ();
	if (xWidth >= yWidth && xWidth >= zWidth) {
		distantPointIdx1 = xBounds.GetLowerIdx ();
		distantPointIdx2 = xBounds.GetHigherIdx ();
	} else if (yWidth >= xWidth && yWidth >= zWidth) {
		distantPointIdx1 = yBounds.GetLowerIdx ();
		distantPointIdx2 = yBounds.GetHigherIdx ();
	} else {
		distantPointIdx1 = zBounds.GetLowerIdx ();
		distantPointIdx2 = zBounds.GetHigherIdx ();
	}

	Coord3D distantPoint1, distantPoint2;
	GetBegVertPosForPedgTemplate (body, ipedg[distantPointIdx1], &distantPoint1);
	GetBegVertPosForPedgTemplate (body, ipedg[distantPointIdx2], &distantPoint2);

	Vector3D distantDiff = distantPoint2 - distantPoint1;
	if (Geometry::LenVector3D (distantDiff) < thisIsSmall) {
		return false;
	}

	// Look for a third point defining the largest triangle with the two distant points
	Vector3D	maxNormal		(0.0, 0.0, 0.0);		// normal         of triangle with the two distant points as corners and with maximal area among these
	double		maxAreaTwice	= 0.0;					// twice the area -- || --
	for (Int32 i = 0; i < npedg; ++i) {
		if (ipedg[i] == 0) {
			continue;
		}
		if (i == distantPointIdx1 || i == distantPointIdx2) {
			continue;
		}
		Coord3D actPoint;
		GetBegVertPosForPedgTemplate (body, ipedg[i], &actPoint);
		Vector3D	actNormal		= (actPoint - distantPoint1) ^ distantDiff;
		double		actAreaTwice	= Geometry::LenVector3D (actNormal);
		if (actAreaTwice > maxAreaTwice) {
			maxNormal		= actNormal;
			maxAreaTwice	= actAreaTwice;
		}
	}

	if (maxAreaTwice > thisIsSmall * thisIsSmall) {
		Geometry::UnitVectorPtr3D (&maxNormal, &maxNormal);
		*nx = maxNormal.x;
		*ny = maxNormal.y;
		*nz = maxNormal.z;
		return true;
	} else {
		return false;
	}
}


// Gets an orthogonal vector to an edge of a body
// Try to determine result in the plane of the edge and the given reference normal
template <class MeshBodyType>
bool CalculateEdgeNormalTemplate (const MeshBodyType& body, Int32 edgeIdx, double *nx, double *ny, double *nz, const Vector3D* referenceNormal = nullptr)
{
	Vector3D edgeUnitVect;
	{
		const EDGE& edge = body.GetConstEdge (edgeIdx);
		COORD3 vert1Pos, vert2Pos;
		body.GetVertexCoords (edge.vert1, Geometry::IdentityTranMat, &vert1Pos.x, &vert1Pos.y, &vert1Pos.z);
		body.GetVertexCoords (edge.vert2, Geometry::IdentityTranMat, &vert2Pos.x, &vert2Pos.y, &vert2Pos.z);
		edgeUnitVect = vert1Pos - vert2Pos;
		if (Geometry::UnitVectorPtr3D (&edgeUnitVect, &edgeUnitVect) < MEDEPS)
			return false;
	}

	Coord3D orthogonalVect;
	bool calcNewNormal = true;
	if (referenceNormal != nullptr) {
		orthogonalVect = (*referenceNormal) - edgeUnitVect * ((*referenceNormal) * edgeUnitVect);	// projection of reference normal to the orthogonal complementer plane of edge
		calcNewNormal = Geometry::UnitVectorPtr3D (&orthogonalVect, &orthogonalVect) < MEDEPS;		// if referenceNormal was collinear with the edge
	}
	if (calcNewNormal) {
		orthogonalVect = Geometry::GetOrthogonalVector3D (edgeUnitVect);
		Geometry::UnitVectorPtr3D (&orthogonalVect, &orthogonalVect);
	}
	
	*nx = orthogonalVect.x;
	*ny = orthogonalVect.y;
	*nz = orthogonalVect.z;

	return true;
}


// Calculates a vector which is perpendicular to a loop in a Body.
// The loop is assumed to be planar.
// reference normal: in case of degenerate collinear loops: an idea for the result, get normal in the plane of this and the line
// Return value: true if the loop is non-degerate i.e. has non-zero signed area
template <class MeshBodyType>
bool CalculateLoopNormalTemplate (const MeshBodyType& body, Int32 npedg, const Int32 *ipedg, double *nx, double *ny, double *nz, const Vector3D* referenceNormal = nullptr)
{
	DBASSERT (ipedg != nullptr && nx != nullptr && ny != nullptr && nz != nullptr);

 	if (CalculateOneContourNormalTemplate (body, npedg, ipedg, nx, ny, nz))
 		return true;

	if (CalculateLargeTriangleNormalTemplate (body, npedg, ipedg, nx, ny, nz))
		return false;

	// Creating an orthogonal vector to the first edge which is not very small
	for (Int32 i = 0; i < npedg; ++i) {
		if (ipedg [i] == 0)
			continue;
		Int32 edgeIdx = GS::Abs (ipedg [i]) - 1;
		if (CalculateEdgeNormalTemplate (body, edgeIdx, nx, ny, nz, referenceNormal))
			return false;
	}
	
	*nx = 0.0;
	*ny = 0.0;
	*nz = 1.0;
	return false;
}

template <typename MeshBodyType, typename PedgIteratorType>
bool	IsPolygonPerpendicularToVector (
	const MeshBodyType& body,
	const PedgIteratorType first,
	const PedgIteratorType last,
	const Vector3D& refVector,
	Int32* firstBadEdge) //returns true if the loop's edges are perpendicular to the referenceNormal vector
{
	for (PedgIteratorType i (first); i != last; ++i) {
		Int32 pedg = *i;
		if (pedg == 0)
			continue;

		double sp, x1, y1, z1, x2, y2, z2;
		Int32 iedge = GS::Abs (pedg) - 1;
		const EDGE& aedge = body.GetConstEdge (iedge);

		Int32 v1 = pedg > 0 ? aedge.vert1 : aedge.vert2;
		Int32 v2 = pedg > 0 ? aedge.vert2 : aedge.vert1;
		body.GetVertexCoords (v1, Geometry::IdentityTranMat, &x1, &y1, &z1);
		body.GetVertexCoords (v2, Geometry::IdentityTranMat, &x2, &y2, &z2);

		x2 -= x1;
		y2 -= y1;
		z2 -= z1;
		double len2 = x2*x2 + y2*y2 + z2*z2;
		sp = refVector.x*x2 + refVector.y*y2 + refVector.z*z2;

		if (len2 > BIGEPS*BIGEPS) {
			sp /= sqrt (len2);
			if (fabs (sp) > 10 * MEDEPS) {
				if (firstBadEdge != nullptr)
					*firstBadEdge = iedge;
				return false;
			}
		}
	}
	return true;

}

// ---------------------------------------------------------------------------------------------------------------------
// Emplaces the texture vertices given in @teves as polygon texture parameters on the given @body.
// Specifically, this function iterates through all vertex of all polygons of @body and, for all
// vertex, stores the U and V values from @teves to the @body as a polygon texture parameter (polygon UV).
// 
// Own texture parameters (coordinate system or texture UVs) of a polygon are stronger than that is coming from TEVE,
// so such polygons are not modified.
// 
// Note. @teves must have exactly the same size as body.GetVertexCount(). Otherwise, no conversion is performed.
// ---------------------------------------------------------------------------------------------------------------------
template <typename TeveCont, typename MeshBodyType>
void	ConvertTextureVerticesToPolygonTextureParamtersTemplate (MeshBodyType& body, const TeveCont& teves)
{
	// if no TEVE, nothing to convert, return
	if (teves.IsEmpty ())
		return;

	// if more vertex than TEVE, ignore TEVEs (see GDL manual) and return
	if (!DBVERIFY (teves.GetSize () == body.GetVertexCount ()))
		return;

	Wrapping bodyWrap = body.GetWrapping ();

	Wrapping polygonWrap = Wrapping (W_FROMBODY, W_QUADRICFIT);		// default UV wrapping flag

	// if the body has an UV flag...
	if (bodyWrap.HasAnyFlag (W_UVMASKS))
	{
		// put it on the polygons instead of the default
		polygonWrap = Wrapping (W_FROMBODY, bodyWrap.GetFlags () & W_UVMASKS);

		// remove UV flags from the body (UV flags on the body were only acceptable with the old TEVE feature)
		if (bodyWrap.HasMethod (W_UNKNOWN)) {
			bodyWrap = Wrapping::DefaultMinMax;		// if the body wrapping is unknown, set MinMax
		} else {
			bodyWrap.RemoveFlags (W_UVMASKS);		// else leave it as it was, except that remove the UV flags
		}
		body.SetWrapping (bodyWrap);
	}

	for (UIndex pgonIdx = 0; pgonIdx < body.GetPolygonCount (); ++pgonIdx)
	{
		const Modeler::PGON& actPgon = body.GetConstPolygon (pgonIdx);
		Modeler::PolygonAttributes actPolygonAttributes = body.GetConstPolygonAttributes (pgonIdx);

		// skip if polygon already has own texture parameters (for those are stronger than TEVE)
		if (actPolygonAttributes.HasTextureParameters ()) {
			continue;
		}

		// set UV-type wrapping on polygon
		actPolygonAttributes.SetWrapping (polygonWrap);

		// the index of the first parameter
		GS::Array<double> textureParameters (/*initialCapacity*/ 2 * actPgon.GetEdgeCount ());
		
		// for each vertex on the polygon...
		for (UInt32 edgeIdx = 0; edgeIdx < actPgon.GetEdgeCount (); ++edgeIdx)
		{
			// vertex index in the body
			Int32 bodyVertIdx = Brep::GetMeshVertexIndexFromPolyEdgeIndex (body, actPgon.fpedg + edgeIdx);

			if (bodyVertIdx >= 0)
			{
				// U and V for the vertex
				TEVE actTeve = teves[bodyVertIdx];
				textureParameters.Push (actTeve.u);
				textureParameters.Push (actTeve.v);
			}
			// contour separators are skipped
		}

		body.StoreTextureParametersAndSetPolygonAttributes (pgonIdx, actPolygonAttributes, &textureParameters);
	}
}


// Set pgon1, pgon2 references of edges according to which polygon has the edge in its edge list.
template <class MeshBodyType>
void AdjustEdgeNeighborPolygonsTemplate (MeshBodyType& body)
{
	for (UInt32 i = 0; i < body.GetPolygonCount (); ++i) {
		const Int32 fpedg = body.GetConstPolygon (i).fpedg;
		const Int32 lpedg = body.GetConstPolygon (i).lpedg;
		for (Int32 j = fpedg; j <= lpedg; ++j) {
			const Int32 apedg = body.GetConstPolyEdge (j);
			if (apedg == 0)
				continue;
			EDGE* edge = body.GetEdge (GS::Abs (apedg) - 1);
			if (edge->pgon1 < -1 && edge->pgon2 != static_cast<Int32> (i)) {
				edge->pgon1 = static_cast<Int32> (i);
			} else if (edge->pgon2 < -1 && edge->pgon1 != static_cast<Int32> (i)) {
				edge->pgon2 = static_cast<Int32> (i);
			}
		}
	}

	for (ULong i = 0; i < body.GetEdgeCount (); i++) {
		EDGE* aedge = body.GetEdge (i);
		if (aedge->pgon1 < -1) {
			aedge->pgon1 = -1;
		}
		if (aedge->pgon2 < -1) {
			aedge->pgon2 = -1;
		}
	}
}

template <class MeshBodyType>
bool IsOpenEdge (const MeshBodyType& body, ULong edgeIndex)
{
	// An edge is open if and only if it has 1(surface) or 0(wireframe) polygons and is not deleted.

	const EDGE& edge = body.GetConstEdge (edgeIndex);
	const Modeler::EdgeAttributes& edgeAttributes = body.GetConstEdgeAttributes (edgeIndex);

	DBASSERT (edge.pgon1 >= -1 && edge.pgon2 >= -1);  // Perhaps it is not an error, but it is strange enough to indicate that!
	return (edge.pgon1 < 0) != (edge.pgon2 < 0) || // boundary of surface
		edge.pgon1 < 0 && edge.pgon2 < 0 && !edgeAttributes.IsInvisible (); // wireframe edge and NOT deleted
}

template <class MeshBodyType>
bool CalculateClosedBodyTemplate (const MeshBodyType& body)
{
	if (!body.HasEdges ()) {
		return true;
	}

	for (ULong edgeIdx = 0; edgeIdx < body.GetEdgeCount (); ++edgeIdx) {
		if (IsOpenEdge (body, edgeIdx)) {
			return false;
		}
	}
	return true;
}


template <class MeshBodyType>
Int32	GetPolygonTextureParameterCount (const MeshBodyType& body, UIndex polygonIndex)
{
	if (body.GetConstPolygonAttributes (polygonIndex).HasTextureCoordinateSystem ()) {
		return 12;
	} else if (body.GetConstPolygonAttributes (polygonIndex).HasTextureUVs ()) {		
		return (body.GetConstPolygon (polygonIndex).GetEdgeCount () - Brep::GetMeshPolygonHoleCount (body, polygonIndex)) * 2;
	}
	return 0;
}


template <class MeshBodyType>
void GetPolygonTextureParametersTemplate (const MeshBodyType& body, UIndex polygonIndex, GS::Array<double>& result)
{
	if (DBERROR (polygonIndex >= body.GetPolygonCount ()))
		return;

	const Modeler::PolygonAttributes& apgonAttributes = body.GetConstPolygonAttributes (polygonIndex);
    GS_DEBUG_ONLY (const Modeler::PGON& apgon = body.GetConstPolygon (polygonIndex));
	DBASSERT (apgon.lpedg >= apgon.fpedg && apgon.lpedg >= 0 && apgon.fpedg >= 0);

	if (!apgonAttributes.HasTextureParameters ()) {
		return;
	}

	const USize polygonTextureParameterCount = GetPolygonTextureParameterCount (body, polygonIndex);
	DBASSERT (apgonAttributes.GetFirstTextureParameterIndex () + polygonTextureParameterCount <= body.GetPolygonTextureParameterCount ());
	for (UIndex index = 0; index < polygonTextureParameterCount; ++index) {
		result.Push (body.GetPolygonTextureParameter (UIndex (apgonAttributes.GetFirstTextureParameterIndex ()) + index));
	}
}


template <class MeshBodyType>
bool TransformPolygonTextureParametersTemplate (const MeshBodyType& body, Int32 ipgon, const TRANMAT* tran, GS::Array<double>& transformedParams)
{
	if (DBERROR (ipgon < 0 || UIndex (ipgon) >= body.GetPolygonCount ())) {
		return false;
	}

	if (tran == nullptr) {
		return false;
	}

	if (tran->IsIdentity ()) {
		return false;
	}

	if (!body.GetConstPolygonAttributes (ipgon).HasTextureCoordinateSystem ()) {
		return false;
	}

	GS::ArrayFB<double, 12> lcoo;
	body.GetPolygonTextureParameters (ipgon, &lcoo);
	if (DBERROR (lcoo.GetSize () != 12)) {
		return false;
	}

	Coord3D localCoords[NCOOR];
	for (UInt32 j = 0; j < NCOOR; ++j) {
		localCoords[j].x = lcoo[3 * j];
		localCoords[j].y = lcoo[3 * j + 1];
		localCoords[j].z = lcoo[3 * j + 2];
		if (j > 0) {
			// create absolute point
			localCoords[j] = localCoords[0] + localCoords[j];
		}
	}

	for (UInt32 j = 0; j < NCOOR; ++j) {
		localCoords[j] = Geometry::TransformPoint (*tran, localCoords[j]);
		if (j > 0) {
			// create relative vector
			localCoords[j] = localCoords[j] - localCoords[0];
		}
		transformedParams.Push (localCoords[j].x);
		transformedParams.Push (localCoords[j].y);
		transformedParams.Push (localCoords[j].z);
	}
	return true;
}


// Returns @false and does nothing else if the polygon with the given @ipgon has no UV texture parameters.
// Otherwise returns @true and produces the reoriented UV parameters in side@reorientedUVs. Method of reorientation
// is strictly connected to @MeshBrep::ReorientPolyEdges. The goal is to have the same UVs at the same VERTICES after
// @MeshBrep::ReorientPolyEdges.
template <class MeshBodyType>
bool ReorientPolygonTextureParametersTemplate (const MeshBodyType& body, Int32 ipgon, GS::Array<double>& reorientedUVs)
{
	if (DBERROR (ipgon < 0 || UIndex (ipgon) >= body.GetPolygonCount ())) {
		return false;
	}

	const Modeler::PGON& pgon = body.GetConstPolygon (ipgon);
	if (!body.GetConstPolygonAttributes (ipgon).HasTextureUVs ()) {
		return false;
	}

	body.GetPolygonTextureParameters (ipgon, &reorientedUVs);
	
	// for each poly edge
	//		find the next contour delimeter poly edge
	//		for each poly edge BUT THE FIRST in the contour swap the U and V values
	//			This is so because when reorienting poly edges, the order of vertices is not only reversed but it
	//			is also rotated ("shifted and wrapped around") by one to the right. E.g. the order of the start
	//			vertices of poly edges of a pentagon (=(x)=> represents the poly edge between two vertices):
	//				V0 =(1)=> V1 =(2)=> V2 =(3)=> V3 =(4)=> V4 =(5)=> V0
	//			after poly edge reorientation (reverse poly edge list and swap direction of each poly edge):
	//				V0 =(-5)=> V4 =(-4)=> V3 =(-3)=> V2 =(-2)=> V1 =(-1)=> V0

	const UIndex firstPolyEdge = pgon.fpedg;
	const UIndex lastPolyEdge = pgon.lpedg;
	const USize polyEdgeCount = 1 + lastPolyEdge - firstPolyEdge;
	if (DBERROR (firstPolyEdge >= lastPolyEdge)) {	// polygon has zero or one pedg
		return false;
	}
	if (DBERROR (body.GetConstPolyEdge (firstPolyEdge) == 0)) {	// empty outer contour of polygon
		return false;
	}

	USize holeCounter = 0;
	USize polyEdgeIndex, currContourStartIndex;
	for (polyEdgeIndex = currContourStartIndex = 0; currContourStartIndex <= polyEdgeCount; ++polyEdgeIndex) {
		// the order of the || operator is important: GetConstPolyEdge might be over-indexed if polyEdgeIndex == polyEdgeCount
		if (polyEdgeIndex >= polyEdgeCount || body.GetConstPolyEdge (firstPolyEdge + polyEdgeIndex) == 0) {
			const USize currContourEndIndex = polyEdgeIndex - 1;
			for (USize contourPolyEdgeIndex = 0;
				 currContourStartIndex + contourPolyEdgeIndex < currContourEndIndex - contourPolyEdgeIndex;
				 ++contourPolyEdgeIndex)
			{
				// sic! First value of the contour remains in its place, the rest is reversed, hence the (+ 1) in @leftUVIndex.
				// sic! Body does not store UVs for contour delimeter poly edges, hence the (- holeCounter) part.
				const UIndex leftUVIndex	= 2 * (1 + currContourStartIndex + contourPolyEdgeIndex - holeCounter);
				const UIndex rightUVIndex	= 2 * (currContourEndIndex - contourPolyEdgeIndex - holeCounter);
				DBASSERT (leftUVIndex <= rightUVIndex);
				DBASSERT (leftUVIndex < reorientedUVs.GetSize ());
				DBASSERT (rightUVIndex < reorientedUVs.GetSize ());

				GS::Swap (reorientedUVs[leftUVIndex],		reorientedUVs[rightUVIndex]);		// U
				GS::Swap (reorientedUVs[leftUVIndex + 1],	reorientedUVs[rightUVIndex + 1]);	// V
			}
			currContourStartIndex = polyEdgeIndex + 1;
			holeCounter += 1;
		}
	}

	return true;
}


template <class MeshBodyType>
Modeler::TextureCoordSys	GetPolygonTextureCoordinateSystemTemplate (const MeshBodyType& body, UIndex index)
{
	if (DBERROR (!body.GetConstPolygonAttributes (index).HasTextureCoordinateSystem ())) {
		return Modeler::TextureCoordSys ();
	}

	GS::ArrayFB<double, 3 * NCOOR> params;
	body.GetPolygonTextureParameters (index, &params);
	
	return Modeler::PolygonTextureParametersToTextureCoordinateSystem (params);
}


template <class MeshBodyType>
GS::Array<UV>	GetPolygonTextureUVsTemplate (const MeshBodyType& body, UIndex index)
{
	const Modeler::PolygonAttributes& polygonAttributes = body.GetConstPolygonAttributes (index);
	if (DBERROR (!polygonAttributes.HasTextureUVs ())) {
		return GS::Array<UV> ();
	}
    GS_DEBUG_ONLY (const ULong polygonHoleCount = Brep::GetMeshPolygonHoleCount (body, index));
    GS_DEBUG_ONLY (const Modeler::PGON& polygon = body.GetConstPolygon (index));
	DBASSERT (USize(GetPolygonTextureParameterCount (body, index)) == 2 * (polygon.GetEdgeCount () - polygonHoleCount));

	const USize uvCount = GetPolygonTextureParameterCount (body, index) / 2;
	GS::Array<UV> uvs (uvCount);
	for (UIndex uvIndex = 0; uvIndex < uvCount; ++uvIndex) {
		uvs.Push (UV (body.GetPolygonTextureParameter (polygonAttributes.GetFirstTextureParameterIndex () + 2 * uvIndex),
					  body.GetPolygonTextureParameter (polygonAttributes.GetFirstTextureParameterIndex () + 2 * uvIndex + 1)));
	}

	return uvs;
}


// ---------------------------------------------------------------------------------------------------------------------
// Converts vertex-based texture coordinate system (i.e. COOR) to an independent texture coordinate system.
// Since Body version 4.0
// ---------------------------------------------------------------------------------------------------------------------
template <typename VertexContainerT>
void	ConvertCoorToTextureCoordinateSystem (Modeler::TextureCoordSys&	textureCoordSys,
											  GS::Array<UIndex>&		unusedCoorVertices,
											  const VertexContainerT&	vertices,
											  const Int32 (&coor)[NCOOR])
{
	// Set texture coordinate system
	Coord3D coords[NCOOR] = { };
	for (UIndex i = 0; i < NCOOR; ++i) {
		Int32 vertInd = abs(coor[i]) - 1;
		if (vertInd < 0 || DBERROR (USize (vertInd) >= vertices.GetSize ())) {
			coords[i] = Coord3D (0.0, 0.0, 0.0);
		} else {
			if (coor[i] < 0) {
				unusedCoorVertices.Push (vertInd);
			}

			const VERT& v = vertices[vertInd];
			coords[i] = Coord3D (v.x, v.y, v.z);
		}
	}

	textureCoordSys = Modeler::TextureCoordSys (coords[0], coords[1], coords[2], coords[3]);
}


// ---------------------------------------------------------------------------
/*																			*/
/*							BOUND BOX										*/
/*																			*/
// ---------------------------------------------------------------------------

template <typename BoxType>
bool IsEmptyBoundingBox (const BoxType& box)
{
	return box.xMax < box.xMin
		&& box.yMax < box.yMin
		&& box.zMax < box.zMin;
}


// ---------------------------------------------------------------------------
/*																			*/
/*							BODY COMPARISON									*/
/*																			*/
// ---------------------------------------------------------------------------


template <typename MeshBodyType>
inline bool BodyDatasEqual (const MeshBodyType& body1, const MeshBodyType& body2)
{
	if (body1.GetStatus () != body2.GetStatus ())
		return false;
	if (body1.GetShapeType () != body2.GetShapeType ())
		return false;
	if (body1.GetEdgePenIdx () != body2.GetEdgePenIdx ())
		return false;
	if (body1.GetFatherBind () != body2.GetFatherBind ())
		return false;
	if (body1.GetMaterialIdx () != body2.GetMaterialIdx ())
		return false;
	if (body1.GetWrapping () != body2.GetWrapping ())
		return false;
	if (body1.GetLineEliminationBehaviour () != body2.GetLineEliminationBehaviour ())
		return false;
	
	if ((body1.GetBodyUserDataContainer () == nullptr) != (body2.GetBodyUserDataContainer () == nullptr)) {
		return false;
	} else if (body1.GetBodyUserDataContainer () != nullptr && (*body1.GetBodyUserDataContainer () != *body2.GetBodyUserDataContainer ())) {
		return false;
	}

	return true;
}


inline bool BodiesEqual_ReturnFailed ()
{
	return false;		// DEBUG: Place breakpoint here
}


inline bool BodyCmpStopped ()
{
	return false;			// DEBUG: Place breakpoint here
}


inline bool	CmpVertsAndAttributes (const VERT& v1, const VERT& v2, Modeler::IBodyMemberComparator& cmp,
									   DataCmpOption cmpOpt,
									   const bool vertHardFlag1, const bool vertHardFlag2,
									   const Int32 vertId1, const Int32 vertId2)
{
	if (!cmp.Compare (v1, v2)) {
		return false;
	}
	if (cmpOpt == GeometryAndAttributes) {
		return	cmp.Compare (vertHardFlag1, vertHardFlag2) && 
				cmp.Compare (vertId1, vertId2);
	}
	return true;
}


template <typename MeshBodyType>
inline bool CmpBodyVertices (const MeshBodyType& body1, const MeshBodyType& body2, Modeler::IBodyMemberComparator& cmp, DataCmpOption cmpOpt)
{
	if (!cmp.CompareItemCounts (body1.GetVertexCount (), body2.GetVertexCount ())) {
		return BodyCmpStopped ();
	}
	for (ULong i = 0; i < body1.GetVertexCount (); ++i) {
		if (!CmpVertsAndAttributes (body1.GetConstVertex (i), body2.GetConstVertex (i), cmp, 
									cmpOpt,
									body1.GetVertexHardFlag (i), body2.GetVertexHardFlag (i), 
									body1.GetVertexId (i).GetValue (), body2.GetVertexId (i).GetValue ())) 
		{
			return BodyCmpStopped ();
		}
	}
	return true;
}


template <typename MeshBodyType>
inline bool BodyVerticesEqual (const MeshBodyType& body1, const MeshBodyType& body2, Modeler::IBodyMemberComparator& cmp)
{
	return CmpBodyVertices (body1, body2, cmp, GeometryAndAttributes);
}


inline bool	CmpEdgesAndAttributes (const EDGE& e, const EDGE& oe, Modeler::IBodyMemberComparator& cmp, DataCmpOption cmpOpt,
								   const Modeler::EdgeAttributes& ea, const Modeler::EdgeAttributes& oea,
								   const Int32 edgeId1, const Int32 edgeId2)
{
	if (!cmp.Compare (e.vert1, oe.vert1) || 
		!cmp.Compare (e.vert2, oe.vert2) || 
		!cmp.Compare (e.pgon1, oe.pgon1) || 
		!cmp.Compare (e.pgon2, oe.pgon2)) 
	{
		return false;
	}

	if (cmpOpt == GeometryAndAttributes) {
		return	cmp.Compare (ea.GetStatus (), oea.GetStatus ()) &&
				cmp.Compare (ea.GetColor (), oea.GetColor ()) &&
				cmp.Compare (edgeId1, edgeId2);
	}
	return true;
}


template <typename MeshBodyType>
inline bool CmpBodyEdges (const MeshBodyType& body1, const MeshBodyType& body2, Modeler::IBodyMemberComparator& cmp, DataCmpOption cmpOpt)
{
	if (!cmp.CompareItemCounts (body1.GetEdgeCount (), body2.GetEdgeCount ())) {
		return BodyCmpStopped ();
	}
	for (ULong i = 0; i < body1.GetEdgeCount (); ++i) {
		const EDGE& e = body1.GetConstEdge (i);
		const EDGE& oe = body2.GetConstEdge (i);

		if (!CmpEdgesAndAttributes (e, oe, cmp, cmpOpt, body1.GetConstEdgeAttributes (i), body2.GetConstEdgeAttributes (i), body1.GetEdgeId (i).GetValue (), body2.GetEdgeId (i).GetValue ())) {
			return BodyCmpStopped ();
		}
	}
	return true;
}

template <typename MeshBodyType>
inline bool BodyEdgesEqual (const MeshBodyType& body1, const MeshBodyType& body2, Modeler::IBodyMemberComparator& cmp)
{
	return CmpBodyEdges (body1, body2, cmp, GeometryAndAttributes);
}


inline bool	CmpPGONAttributes (const Modeler::PolygonAttributes& pa, const Modeler::PolygonAttributes& opa, Modeler::IBodyMemberComparator& cmp,
								   const Int32 pgonId1, const Int32 pgonId2)
{
	return	cmp.Compare (pa.GetWrapping (), opa.GetWrapping ()) &&
			cmp.Compare (pa.GetStatus (), opa.GetStatus ()) &&
			cmp.Compare (pa.GetMaterialIndex (), opa.GetMaterialIndex ()) &&
			cmp.Compare (pa.GetTextureIndex (), opa.GetTextureIndex ()) &&
			cmp.Compare (pa.GetMpuid (), opa.GetMpuid ()) &&
			cmp.Compare (pa.GetFirstTextureParameterIndex (), opa.GetFirstTextureParameterIndex ()) &&
			cmp.Compare (pgonId1, pgonId2);
}


template <typename MeshBodyType>
inline bool CmpBodyPolygons (const MeshBodyType& body1, const MeshBodyType& body2, Modeler::IBodyMemberComparator& cmp, DataCmpOption cmpOpt)
{
	if (!cmp.CompareItemCounts (body1.GetPolyEdgeCount(), body2.GetPolyEdgeCount ())) {
		return BodyCmpStopped ();
	}
	for (ULong i = 0; i < body1.GetPolyEdgeCount(); ++i) {
		if (!cmp.Compare (body1.GetConstPolyEdge (i), body2.GetConstPolyEdge (i))) {
			return BodyCmpStopped ();
		}
	}

	if (!cmp.CompareItemCounts (body1.GetPolyNormalCount (), body2.GetPolyNormalCount ())) {
		return BodyCmpStopped ();
	}
	for (ULong i = 0; i < body1.GetPolyNormalCount (); ++i) {
		if (!cmp.Compare (body1.GetConstPolyNormal (i), body2.GetConstPolyNormal (i))) {
			return BodyCmpStopped ();
		}
	}

	if (cmpOpt == GeometryAndAttributes) {
		if (!cmp.CompareItemCounts (body1.GetPolygonTextureParameterCount (), body2.GetPolygonTextureParameterCount ())) {
			return BodyCmpStopped ();
		}
		for (ULong i = 0; i < body1.GetPolygonTextureParameterCount (); ++i) {
			if (!cmp.Compare (body1.GetPolygonTextureParameter (i), body2.GetPolygonTextureParameter (i))) {
				return BodyCmpStopped ();
			}
		}
	}

	if (!cmp.CompareItemCounts (body1.GetPolygonCount (), body2.GetPolygonCount ())) {
		return BodyCmpStopped ();
	}
	for (ULong i = 0; i < body1.GetPolygonCount (); ++i) {
		const Modeler::PGON& p = body1.GetConstPolygon(i);
		const Modeler::PGON& op = body2.GetConstPolygon(i);

		if (!cmp.Compare (p.fpedg, op.fpedg) ||
			!cmp.Compare (p.lpedg, op.lpedg) ||
			!cmp.Compare (p.ivect, op.ivect)) 
		{
			return BodyCmpStopped ();
		}

		if (cmpOpt == GeometryAndAttributes && !CmpPGONAttributes (body1.GetConstPolygonAttributes (i), body2.GetConstPolygonAttributes (i), cmp, body1.GetPolygonId (i).GetValue (), body2.GetPolygonId (i).GetValue ())) {
			return BodyCmpStopped ();
		}
	}

	return true;
}

template <typename MeshBodyType>
inline bool BodyPolygonsEqual (const MeshBodyType& body1, const MeshBodyType& body2, Modeler::IBodyMemberComparator& cmp)
{
	return CmpBodyPolygons (body1, body2, cmp, GeometryAndAttributes);
}


template <typename MeshBodyType>
inline bool BodiesEqual (const MeshBodyType& body1, const MeshBodyType& body2)
{
	Modeler::BodyMemberEqualityChecker epsEqChecker (EPS);

	if (!BodyDatasEqual (body1, body2))
		return BodiesEqual_ReturnFailed ();
	if (!Modeler::AreTextureCoordSysEqual (body1.GetTextureCoordSys (), body2.GetTextureCoordSys (), EPS))
		return BodiesEqual_ReturnFailed ();
	if (!Geometry::AreBox3DsEqual (body1.GetLocalBounds (), body2.GetLocalBounds (), EPS))
		return BodiesEqual_ReturnFailed ();
	if (!BodyVerticesEqual (body1, body2, epsEqChecker))
		return BodiesEqual_ReturnFailed ();
	if (!BodyEdgesEqual (body1, body2, epsEqChecker))
		return BodiesEqual_ReturnFailed ();
	if (!BodyPolygonsEqual (body1, body2, epsEqChecker))
		return BodiesEqual_ReturnFailed ();
	return true;
}


// =================================================================================================
//  Body equality check with subelement (vertex, edge, pgon) order shuffle
// =================================================================================================

// -----------------------------------------------------------------------------
// Testing geometrical equality of subelements of body
// -----------------------------------------------------------------------------


// Interface class
template <typename MeshBodyType>
class EqualityTester {
public:
	enum TestRigidity { TestOnlyGeomAndTopo, TestGeomTopoAndData };
	
protected:
	const MeshBodyType&	m_body1;
	const MeshBodyType&	m_body2;
	TestRigidity	m_testRigidity;

	EqualityTester (const MeshBodyType& body1, const MeshBodyType& body2, TestRigidity testRigidity) 
		: m_body1 (body1), m_body2 (body2), m_testRigidity (testRigidity)
	{ }

public:
	virtual bool EqualElems (ULong, ULong) const = 0;
};


// -------------------------------------
// Vertex comparison
// -------------------------------------

template <typename MeshBodyType>
class BodyVertEqualityTester : public EqualityTester<MeshBodyType> {
public:
	BodyVertEqualityTester (const MeshBodyType& body1, const MeshBodyType& body2,
							typename EqualityTester<MeshBodyType>::TestRigidity testRigidity)
	:	EqualityTester<MeshBodyType> (body1, body2, testRigidity)
	{ }

	virtual bool EqualElems (ULong index1, ULong index2) const override;
};

template <typename MeshBodyType>
bool BodyVertEqualityTester<MeshBodyType>::EqualElems (ULong index1, ULong index2) const
{
	if (this->m_testRigidity == EqualityTester<MeshBodyType>::TestGeomTopoAndData) {
		// Check non-geometry data
		const bool hardFlag1 = this->m_body1.GetVertexHardFlag (index1);
		const bool hardFlag2 = this->m_body2.GetVertexHardFlag (index2);
		const Modeler::VertexId vertId1 = this->m_body1.GetVertexId (index1);
		const Modeler::VertexId vertId2 = this->m_body2.GetVertexId (index2);
		if (hardFlag1 != hardFlag2 || vertId1 != vertId2) {
			return false;
		}
	}

	// Check location
	const VERT& v1 = this->m_body1.GetConstVertex (index1);
	const VERT& v2 = this->m_body2.GetConstVertex (index2);
	if (GS::Abs (v1.x - v2.x) > EPS || GS::Abs (v1.y - v2.y) > EPS || GS::Abs (v1.z - v2.z) > EPS) {
		return false;
	}

	return true;
}


// -------------------------------------
// Edge comparison
// -------------------------------------

template <typename MeshBodyType>
class BodyEdgeEqualityTester : public EqualityTester<MeshBodyType> {
	const GS::Array<ULong>& m_vertBijection;
public:
	BodyEdgeEqualityTester (const MeshBodyType& body1, const MeshBodyType& body2,
							const GS::Array<ULong>& vertBijection,
							typename EqualityTester<MeshBodyType>::TestRigidity testRigidity)
	:	EqualityTester<MeshBodyType> (body1, body2, testRigidity),
		m_vertBijection (vertBijection)
	{
		DBASSERT (m_vertBijection.GetSize () == this->m_body1.GetVertexCount ());
	}

	virtual bool EqualElems (ULong index1, ULong index2) const override;
};

template <typename MeshBodyType>
bool BodyEdgeEqualityTester<MeshBodyType>::EqualElems (ULong index1, ULong index2) const
{	
	const Modeler::EdgeAttributes&	ea1 = this->m_body1.GetConstEdgeAttributes (index1);
	const Modeler::EdgeAttributes&	ea2 = this->m_body2.GetConstEdgeAttributes (index2);

	if (this->m_testRigidity == EqualityTester<MeshBodyType>::TestGeomTopoAndData) {
		// Check non-geometry data
		if (ea1.GetColor () != ea2.GetColor ()) {
			return false;
		}
		if (ea1.GetStatus () != ea2.GetStatus ()) {
			return false;
		}
		const Modeler::EdgeId edgeId1 = this->m_body1.GetEdgeId (index1);
		const Modeler::EdgeId edgeId2 = this->m_body2.GetEdgeId (index2);
		if (edgeId1 != edgeId2) {
			return false;
		}
	}

	// Check endpoints
	const EDGE&	e1 = this->m_body1.GetConstEdge (index1);
	const EDGE&	e2 = this->m_body2.GetConstEdge (index2);
	ULong e1v1Mapped	= m_vertBijection[e1.vert1];
	ULong e1v2Mapped	= m_vertBijection[e1.vert2];
	ULong e2v1			= e2.vert1;
	ULong e2v2			= e2.vert2;
	if (!(e1v1Mapped == e2v1 && e1v2Mapped == e2v2) &&
		!(e1v1Mapped == e2v2 && e1v2Mapped == e2v1))
	{
		return false;
	}
	return true;
}


// -------------------------------------
// Pgon comparison
// -------------------------------------

// Data for an edge of pgon
struct EdgeIndexAndUV {
	ULong	edgeIndex;
	UV		uv;

	bool operator == (const EdgeIndexAndUV& other) const { return (edgeIndex == other.edgeIndex && GS::Abs (uv.u - other.uv.u) < EPS && GS::Abs (uv.v - other.uv.v) < EPS); }
	bool operator != (const EdgeIndexAndUV& other) const { return !(*this == other); }
};

typedef GS::ArrayFB<EdgeIndexAndUV, 16> PgonContourEdgesAndUVs;


template <typename MeshBodyType>
class BodyPgonEqualityTester : public EqualityTester<MeshBodyType> {
	const GS::Array<ULong>&		m_edgeBijection;
	Modeler::MeshBody::MPUIDCheck	m_mpuidCheck;
public:
	BodyPgonEqualityTester (const MeshBodyType& body1,
							const MeshBodyType& body2,
							const GS::Array<ULong>& edgeBijection,
							typename EqualityTester<MeshBodyType>::TestRigidity testRigidity,
							Modeler::MeshBody::MPUIDCheck mpuidCheck)
	:	EqualityTester<MeshBodyType> (body1, body2, testRigidity),
		m_edgeBijection (edgeBijection),
		m_mpuidCheck (mpuidCheck)
	{
		DBASSERT (m_edgeBijection.GetSize () == body1.GetEdgeCount ());
	}

	virtual bool EqualElems (ULong index1, ULong index2) const override;

private:

	// Helper class for comparing pgons: a structure storing edge index list of pgon; and sortable for easy comparison
	class PgonContourEdgeLists {
	private:
		GS::ArrayFB<PgonContourEdgesAndUVs, 4> m_contourEdgesAndUVs;	// first is the outer contour, the rest are hole contours

	public:
		PgonContourEdgeLists (const MeshBodyType& body, Int32 pgonIndex, typename EqualityTester<MeshBodyType>::TestRigidity testRigidity)
		{
			m_contourEdgesAndUVs.PushNew ();
			const Modeler::PGON& pgon = body.GetConstPolygon (pgonIndex);
			const Modeler::PolygonAttributes& polygonAttributes = body.GetConstPolygonAttributes (pgonIndex);
			USize holeCount = 0;
			for (Int32 pedgIdx = pgon.fpedg; pedgIdx <= pgon.lpedg; ++pedgIdx) {
				Int32 pedg = body.GetConstPolyEdge (pedgIdx);
				if (pedg == 0) {
					m_contourEdgesAndUVs.PushNew ();
					++holeCount;
				} else {
					EdgeIndexAndUV edgeIndexAndUV;
					edgeIndexAndUV.edgeIndex = static_cast<ULong> (GS::Abs (pedg) - 1);
					if (polygonAttributes.HasTextureUVs () && testRigidity == EqualityTester<MeshBodyType>::TestGeomTopoAndData) {
						edgeIndexAndUV.uv.u = body.GetPolygonTextureParameter (polygonAttributes.GetFirstTextureParameterIndex () + 2 * (pedgIdx - pgon.fpedg - holeCount));
						edgeIndexAndUV.uv.v = body.GetPolygonTextureParameter (polygonAttributes.GetFirstTextureParameterIndex () + 2 * (pedgIdx - pgon.fpedg - holeCount) + 1);
					} else {
						edgeIndexAndUV.uv.u = 0.0;
						edgeIndexAndUV.uv.v = 0.0;
					}
					m_contourEdgesAndUVs.GetLast ().Push (edgeIndexAndUV);
				}
			}
		}

		void ApplyEdgeBijection (const GS::Array<ULong>& m_edgeBijection)
		{
			for (ULong contIdx = 0; contIdx < m_contourEdgesAndUVs.GetSize (); ++contIdx) {
				PgonContourEdgesAndUVs& contourRef = m_contourEdgesAndUVs[contIdx];
				for (ULong edgeIdx = 0; edgeIdx < contourRef.GetSize (); ++edgeIdx) {
					EdgeIndexAndUV& edgeAndUVRef = contourRef[edgeIdx];
					edgeAndUVRef.edgeIndex = m_edgeBijection[edgeAndUVRef.edgeIndex];
				}
			}
		}

		void Order ()
		{
			// Make all contours start with its lowest edge index
			for (ULong contIdx = 0; contIdx < m_contourEdgesAndUVs.GetSize (); ++contIdx) {
				PgonContourEdgesAndUVs& contourRef = m_contourEdgesAndUVs[contIdx];
				PgonContourEdgesAndUVs::Iterator beg = contourRef.Begin ();
				PgonContourEdgesAndUVs::Iterator end = contourRef.End ();
				PgonContourEdgesAndUVs::Iterator min = GS::MinElement (beg, end, CompareEdgeAndUVsByEdge);
				GS::Rotate (beg, min, end);
			}
			// order hole contours by first edge index
			GS::Array<PgonContourEdgesAndUVs>::Iterator firstHole	= ++(m_contourEdgesAndUVs.Begin ());
			GS::Array<PgonContourEdgesAndUVs>::Iterator lastHole	= m_contourEdgesAndUVs.End ();
			GS::Sort (firstHole, lastHole, CompareHolesByFirstEdge);
		}

		bool Equals (const PgonContourEdgeLists& other) const {
			return (m_contourEdgesAndUVs == other.m_contourEdgesAndUVs);
		}

	private:
		static bool CompareHolesByFirstEdge (const PgonContourEdgesAndUVs& cont1, const PgonContourEdgesAndUVs& cont2)
		{
			if (DBERROR (cont1.IsEmpty ())) {
				return false;
			} else if (DBERROR (cont2.IsEmpty ())) {
				return true;
			} else {
				return CompareEdgeAndUVsByEdge (cont1[0], cont2[0]);
			}
		}

		static bool CompareEdgeAndUVsByEdge (const EdgeIndexAndUV& edgeAndUV1, const EdgeIndexAndUV& edgeAndUV2)
		{
			return (edgeAndUV1.edgeIndex < edgeAndUV2.edgeIndex);
		}

	};

};


template <typename MeshBodyType>
bool BodyPgonEqualityTester<MeshBodyType>::EqualElems (ULong index1, ULong index2) const
{
	const Modeler::PGON& pgon1 = this->m_body1.GetConstPolygon (index1);
	const Modeler::PGON& pgon2 = this->m_body2.GetConstPolygon (index2);
	const Modeler::PolygonAttributes& pgon1Attributes = this->m_body1.GetConstPolygonAttributes (index1);
	const Modeler::PolygonAttributes& pgon2Attributes = this->m_body2.GetConstPolygonAttributes (index2);
	
	if (this->m_testRigidity == EqualityTester<MeshBodyType>::TestGeomTopoAndData) {
		// Check non-geometry data
		const Modeler::PolygonId polyId1 = this->m_body1.GetPolygonId (index1);
		const Modeler::PolygonId polyId2 = this->m_body2.GetPolygonId (index2);
	
		if (pgon1Attributes.GetStatus () != pgon2Attributes.GetStatus ()
			|| pgon1Attributes.GetWrapping () != pgon2Attributes.GetWrapping ()
			|| pgon1Attributes.GetMaterialIndex () != pgon2Attributes.GetMaterialIndex ()
			|| pgon1Attributes.GetTextureIndex () != pgon2Attributes.GetTextureIndex ()			
			||	polyId1 != polyId2)
		{
			return false;
		}

		if (m_mpuidCheck == Modeler::MeshBody::CheckMPUID) {
			if (pgon1Attributes.GetMpuid () != pgon2Attributes.GetMpuid ()) {
				return false;
			}
		}
	}
	
	// Check normal vectors
	Vector3D normal1 = GetPolygonNormal (this->m_body1, pgon1.ivect);
	Vector3D normal2 = GetPolygonNormal (this->m_body2, pgon2.ivect);
	DBASSERT (Geometry::IsUnitVector3D (normal1));
	DBASSERT (Geometry::IsUnitVector3D (normal2));
	double dotProductTolerance = 1 - 1.5230E-4;	// ~= 1 - cos (1 degree)
	if (normal1 * normal2 < dotProductTolerance) {
		return false;
	}
				
	// Check edges
	PgonContourEdgeLists pgonContourEdgeLists1 (this->m_body1, index1, this->m_testRigidity);
	PgonContourEdgeLists pgonContourEdgeLists2 (this->m_body2, index2, this->m_testRigidity);
	pgonContourEdgeLists1.ApplyEdgeBijection (m_edgeBijection);
	pgonContourEdgeLists1.Order ();
	pgonContourEdgeLists2.Order ();
	if (!pgonContourEdgeLists1.Equals (pgonContourEdgeLists2)) {
		return false;
	}

	return true;
}


// -----------------------------------------------------------------------------
// Collect bijections mapping equal subelements
// -----------------------------------------------------------------------------


// Collect all bijections between two sets so that:
//  each element in set 1 (preimage) equals to the element in set 2 to which it is mapped to (image)
// Set 1, set 2 and the equality checking is wrapped in EqualityTester
template <typename MeshBodyType>
bool GetAllBijections (ULong sizeOfSets, const EqualityTester<MeshBodyType>& equalityTester, GS::Array<GS::Array<ULong> >* allBijections)
{
	allBijections->Clear ();

	GS::Array<GS::Array<ULong> > allMappings;	// All mappings from set1 to set2 where mapped elems are equal (not necessary one-to-one mapping)
	allMappings.PushNew ();
	allMappings[0].SetSize (sizeOfSets);

	for (ULong elem1Idx = 0; elem1Idx < sizeOfSets; ++elem1Idx) {
		GS::Array<ULong> equalElemsInSet2;		// To elem1
		for (ULong elem2Idx = 0; elem2Idx < sizeOfSets; ++elem2Idx) {
			if (equalityTester.EqualElems (elem1Idx, elem2Idx)) {
				equalElemsInSet2.Push (elem2Idx);
			}
		}

		ULong nEqualElemsInSet2 = equalElemsInSet2.GetSize ();
		if (nEqualElemsInSet2 == 0) {
			return false;
		} else if (nEqualElemsInSet2 == 1) {
			for (ULong mappingIdx = 0; mappingIdx < allMappings.GetSize (); ++mappingIdx) {
				allMappings[mappingIdx][elem1Idx] = equalElemsInSet2[0];
			}
		} else {
			// multiply mappings copying previous content
			ULong nMappings = allMappings.GetSize ();
			allMappings.SetSize (nEqualElemsInSet2 * nMappings);
			for (ULong equalElem2Idx = 1 /* !!! */; equalElem2Idx < nEqualElemsInSet2; ++equalElem2Idx) {
				for (ULong mappingIdx = 0; mappingIdx < nMappings; ++mappingIdx) {
					ULong copiedMappingIndex = nMappings * equalElem2Idx + mappingIdx;
					allMappings[copiedMappingIndex] = allMappings[mappingIdx];	// array copy
				}
			}
			// add values to mappings
			for (ULong equalElem2Idx = 0; equalElem2Idx < nEqualElemsInSet2; ++equalElem2Idx) {
				for (ULong mappingIdx = 0; mappingIdx < nMappings; ++mappingIdx) {
					ULong actMappingIndex = nMappings * equalElem2Idx + mappingIdx;
					allMappings[actMappingIndex][elem1Idx] = equalElemsInSet2[equalElem2Idx];
				}
			}
		}
	}

	// Filter mappings which are bijections
	for (ULong mappingIdx = 0; mappingIdx < allMappings.GetSize (); ++mappingIdx) {
		const GS::Array<ULong>&	currMapping				= allMappings[mappingIdx];
		bool					currMappingIsBijection	= true;
		GS::Array<bool> usedAtMapping;
		usedAtMapping.SetSize (sizeOfSets);
		usedAtMapping.Fill (false);
		for (ULong elemIdx = 0; elemIdx < sizeOfSets; ++elemIdx) {
			ULong mappedIdx = currMapping[elemIdx];
			if (usedAtMapping[mappedIdx]) {
				currMappingIsBijection = false;
			} else {
				usedAtMapping[mappedIdx] = true;
			}
		}

		if (currMappingIsBijection) {
			allBijections->Push (currMapping);
		}
	}

	return (!allBijections->IsEmpty ());
}



// Check if given vertex, edge and pgon bijections maps subelems of body 1 to equal subelems of body 2
template <typename MeshBodyType>
bool CheckWithBijections (	const MeshBodyType& body1, const MeshBodyType& body2,
							const GS::Array<ULong>& vertBijection, const GS::Array<ULong>& edgeBijection, const GS::Array<ULong>& pgonBijection,
							typename EqualityTester<MeshBodyType>::TestRigidity testRigidity,
							Modeler::MeshBody::MPUIDCheck mpuidCheck)
{
	BodyVertEqualityTester<MeshBodyType> vertTester (body1, body2, testRigidity);
	for (ULong vertIdx1 = 0; vertIdx1 < vertBijection.GetSize (); ++vertIdx1) {
		ULong vertIdx2 = vertBijection[vertIdx1];
		if (!vertTester.EqualElems (vertIdx1, vertIdx2)) {
			return false;
		}
	}
	BodyEdgeEqualityTester<MeshBodyType> edgeTester (body1, body2, vertBijection, testRigidity);
	for (ULong edgeIdx1 = 0; edgeIdx1 < edgeBijection.GetSize (); ++edgeIdx1) {
		ULong edgeIdx2 = edgeBijection[edgeIdx1];
		if (!edgeTester.EqualElems (edgeIdx1, edgeIdx2)) {
			return false;
		}
	}
	BodyPgonEqualityTester<MeshBodyType> pgonTester (body1, body2, edgeBijection, testRigidity, mpuidCheck);
	for (ULong pgonIdx1 = 0; pgonIdx1 < pgonBijection.GetSize (); ++pgonIdx1) {
		ULong pgonIdx2 = pgonBijection[pgonIdx1];
		if (!pgonTester.EqualElems (pgonIdx1, pgonIdx2)) {
			return false;
		}
	}

	return true;
}


// -----------------------------------------------------------------------------
// Main function for body equality check with shuffling
// -----------------------------------------------------------------------------

template <typename MeshBodyType>
inline bool BodiesEqualWithShuffle (const MeshBodyType& body1, const MeshBodyType& body2, Modeler::MeshBody::MPUIDCheck mpuidCheck = Modeler::MeshBody::CheckMPUID)
{
	try {
		if (!BodyDatasEqual (body1, body2)) {
			return BodiesEqual_ReturnFailed ();
		}
		if (!Geometry::AreBox3DsEqual (body1.GetLocalBounds (), body2.GetLocalBounds (), EPS)) {
			return BodiesEqual_ReturnFailed ();
		}
		if (!Modeler::AreTextureCoordSysEqual (body1.GetTextureCoordSys (), body2.GetTextureCoordSys (), EPS)) {
			return BodiesEqual_ReturnFailed ();
		}

		ULong nVertCommon = body1.GetVertexCount ();
		if (nVertCommon != body2.GetVertexCount ()) {
			return BodiesEqual_ReturnFailed ();
		}
		
		ULong nEdgeCommon = body1.GetEdgeCount ();
		if (nEdgeCommon != body2.GetEdgeCount ()) {
			return BodiesEqual_ReturnFailed ();
		}
		
		ULong nPgonCommon = body1.GetPolygonCount ();
		if (nPgonCommon != body2.GetPolygonCount ()) {
			return BodiesEqual_ReturnFailed ();
		}

#if defined (DEBUVERS_BeA) || defined (DEBUVERS_BoB)
		// For debug: find bijections with only geometrical equality first, check other data second
		typename EqualityTester<MeshBodyType>::TestRigidity firstTestRigidity = EqualityTester<MeshBodyType>::TestOnlyGeomAndTopo;
#else
		typename EqualityTester<MeshBodyType>::TestRigidity firstTestRigidity = EqualityTester<MeshBodyType>::TestGeomTopoAndData;
#endif

		GS::Array<GS::Array<ULong> > vertexBijections;
		BodyVertEqualityTester<MeshBodyType> bodyVertEqualityTester (body1, body2, firstTestRigidity);
		if (!GetAllBijections<MeshBodyType> (nVertCommon, bodyVertEqualityTester, &vertexBijections)) {
			// No bijection between vertices
			return BodiesEqual_ReturnFailed ();
		}

		for (ULong vertBijectionIdx = 0; vertBijectionIdx < vertexBijections.GetSize (); ++vertBijectionIdx) {
			const GS::Array<ULong>& vertBijection = vertexBijections[vertBijectionIdx];

			GS::Array<GS::Array<ULong> > edgeBijections;
			BodyEdgeEqualityTester<MeshBodyType> bodyEdgeEqualityTester (body1, body2, vertBijection, firstTestRigidity);
			if (!GetAllBijections<MeshBodyType> (nEdgeCommon, bodyEdgeEqualityTester, &edgeBijections)) {
				// No bijection between edges with this bijection of vertices - try next bijection of vertices
				continue;
			}

			for (ULong edgeBijectionIdx = 0; edgeBijectionIdx < edgeBijections.GetSize (); ++edgeBijectionIdx) {
				const GS::Array<ULong>& edgeBijection = edgeBijections[edgeBijectionIdx];

				GS::Array<GS::Array<ULong> > pgonBijections;
				BodyPgonEqualityTester<MeshBodyType> bodyPgonEqualityTester (body1, body2, edgeBijection, firstTestRigidity, mpuidCheck);
				if (!GetAllBijections<MeshBodyType> (nPgonCommon, bodyPgonEqualityTester, &pgonBijections)) {
					// No bijection between pgons with this bijection of edges - try next bijection of edges
					continue;
				}

				// If tests were only geometrical by this time, check strict equality now
				// Otherwise it is a safety check
				for (ULong pgonBijectionIdx = 0; pgonBijectionIdx < pgonBijections.GetSize (); ++pgonBijectionIdx) {
					const GS::Array<ULong>& pgonBijection = pgonBijections[pgonBijectionIdx];
					if (CheckWithBijections (body1, body2, vertBijection, edgeBijection, pgonBijection, 
											 EqualityTester<MeshBodyType>::TestGeomTopoAndData, mpuidCheck)) {
						return true;
					}
				}
			}
		}

	}
	catch (const GS::Exception&) {
		DBBREAK ();
		return BodiesEqual_ReturnFailed ();
	}
	return BodiesEqual_ReturnFailed ();
}


//}	// namespace Modeler


// ---------------------------------------------------------------------------
/*																			*/
/*			WRITE GDL CODE THAT GENERATES THE BODY							*/
/*																			*/
// ---------------------------------------------------------------------------


class ChannelWriter {
private:
	GS::OChannel&					outChannel;
	Modeler::MeshBody::WriteAsGDLLayout	layout;
public:
	ChannelWriter (GS::OChannel& oc, Modeler::MeshBody::WriteAsGDLLayout l) : outChannel (oc), layout (l) { }
	inline GSErrCode WriteLine (const GS::UniString& str) const
	{
		GSErrCode ret = NoError;
		const GS::UniString eol (GS::EOL);
		if (layout == Modeler::MeshBody::WriteAsUStr) {
			ret |= outChannel.WriteBin (reinterpret_cast<const char*> (str.ToUStr ().Get ()), str.GetLength () * sizeof (GS::UniChar::Layout));
			ret |= outChannel.WriteBin (reinterpret_cast<const char*> (eol.ToUStr ().Get ()), eol.GetLength () * sizeof (GS::UniChar::Layout));
		} else {
			ret |= outChannel.WriteBin (reinterpret_cast<const char*> (str.ToCStr ().Get ()), str.GetLength () * sizeof (char));
			ret |= outChannel.WriteBin (reinterpret_cast<const char*> (eol.ToCStr ().Get ()), eol.GetLength () * sizeof (char));
		}
		return ret;
	}
};


template <class MeshBodyType>
GSErrCode	WriteVertsAsGDLTemplate (GS::ProcessControl& processControl, const MeshBodyType& body, const ChannelWriter& channelWriter)
{
	GSErrCode errCode = NoError;

	for (ULong j = 0; j < body.GetVertexCount () && !processControl.TestBreak (); ++j) {
		const VERT& v		= body.GetConstVertex (j);
		Int32		vertId	= body.GetVertexId (j).GetValue ();
		if (body.GetVertexHardFlag (j)) {
			errCode |= channelWriter.WriteLine (GS::UniString::Printf ("vert{2}\t%12.*G, %12.*G, %12.*G, 1\t!\t#%-3u VertId=%d",
				MESHBODY_WRITE_NUM_PREC, v.x,
				MESHBODY_WRITE_NUM_PREC, v.y,
				MESHBODY_WRITE_NUM_PREC, v.z,
				j + 1,
				vertId));
		} else {
			errCode |= channelWriter.WriteLine (GS::UniString::Printf ("vert\t%12.*G, %12.*G, %12.*G\t!\t#%-3u VertId=%d",
				MESHBODY_WRITE_NUM_PREC, v.x,
				MESHBODY_WRITE_NUM_PREC, v.y,
				MESHBODY_WRITE_NUM_PREC, v.z,
				j + 1,
				vertId));
		}
	}

	return errCode;
}


template <class MeshBodyType>
GSErrCode	WriteEdgesAsGDLTemplate (GS::ProcessControl& processControl, 
	const MeshBodyType&								body,
	const ChannelWriter&					channelWriter,
	const Modeler::MeshBody::WriteAsGDLOption&	option,
	Modeler::MeshBody::IWriteAttributesToGDL&	writeAttributeToGDL,
	short&									edgeColor)
{
	GSErrCode errCode = NoError;
	const bool allCurved = (option == Modeler::MeshBody::AllCurved);
	const bool simpleOut = (option == Modeler::MeshBody::SimpleModelOutput);

	if (body.HasEdges()) {
		const short eColor = body.GetConstEdgeAttributes (0).GetColor ();
		if (eColor > 0) {
			edgeColor = eColor;
			GS::UniString	gdlLine;
			gdlLine = writeAttributeToGDL.Out_Pen (eColor);
			if (DBERROR (gdlLine.IsEmpty ()))
				gdlLine = GS::UniString::Printf ("pen \t%4d", eColor);
			errCode |= channelWriter.WriteLine (gdlLine);
		}
	}

	for (ULong j = 0; j < body.GetEdgeCount () && !processControl.TestBreak (); ++j) {
		const EDGE& aedge = body.GetConstEdge (j);
		const short eColor	= body.GetConstEdgeAttributes (j).GetColor ();
		const Int32	edgeId	= body.GetEdgeId (j).GetValue ();
		STATL	estat	= body.GetConstEdgeAttributes (j).GetStatus () & ~REBIT12;

		if (eColor > 0 && edgeColor != eColor && body.GetShapeType () != B_SHADOW) {
			edgeColor = eColor;
			GS::UniString	gdlLine;
			gdlLine = writeAttributeToGDL.Out_Pen (eColor);
			if (DBERROR (gdlLine.IsEmpty ()))
				gdlLine = GS::UniString::Printf ("pen \t%4d", eColor);
			errCode |= channelWriter.WriteLine (gdlLine);
		}

		if (allCurved)
			estat |= VISIBLEIFCONTOURBIT;

		if (simpleOut) {
			errCode |= channelWriter.WriteLine (GS::UniString::Printf ("edge\t%4d, %4d,   -1,   -1, %6u\t\t\t!\t#%-3u EdgeId=%d",
				aedge.vert1 + 1, aedge.vert2 + 1, estat, j + 1, edgeId));
		} else {
			errCode |= channelWriter.WriteLine (GS::UniString::Printf ("edge\t%4d, %4d, %4d, %4d, %6u\t\t\t!\t#%-3u EdgeId=%d",
				aedge.vert1 + 1, aedge.vert2 + 1, aedge.pgon1 + 1, aedge.pgon2 + 1, estat, j + 1, edgeId));
		}
	}

	return errCode;
}


template <class MeshBodyType>
GSErrCode	WritePolyNormalsAsGDLTemplate (GS::ProcessControl& processControl, const MeshBodyType& body, const ChannelWriter& channelWriter)
{
	GSErrCode errCode = NoError;

	for (ULong j = 0; j < body.GetPolyNormalCount () && !processControl.TestBreak (); ++j) {
		const Vector3D& n = body.GetConstPolyNormal (j);
		errCode |= channelWriter.WriteLine (GS::UniString::Printf ("vect\t%12.*G, %12.*G, %12.*G\t!\t#%-3u",
			MESHBODY_WRITE_NUM_PREC, n.x,
			MESHBODY_WRITE_NUM_PREC, n.y,
			MESHBODY_WRITE_NUM_PREC, n.z,
			j + 1));
	}

	return errCode;
}


template <class MeshBodyType>
GSErrCode	WritePolygonsAsGDLTemplate (GS::ProcessControl& processControl, 
	const MeshBodyType&							body,
	const ChannelWriter&						channelWriter,
	const Modeler::MeshBody::WriteAsGDLOption&	option,
	Modeler::MeshBody::WriteAsGDLTextureGetter	GetTextureInfo,
	Modeler::MeshBody::IWriteAttributesToGDL&	writeAttributeToGDL,
	void*										userData,
	GSAttributeIndex&							polyIumat)
{
	GSErrCode errCode = NoError;
	const bool contourOnly = (option == Modeler::MeshBody::CurvedPolygons ? ((body.GetStatus () & Modeler::MeshBody::CurvedBody) > 0) : false);
	const bool allCurved = (option == Modeler::MeshBody::AllCurved);
	const bool simpleOut = (option == Modeler::MeshBody::SimpleModelOutput);

	if (body.HasPolygons()) {
		polyIumat = body.GetConstPolygonAttributes (0).GetMaterialIndex ();
		GS::UniString	gdlLine;
		gdlLine = writeAttributeToGDL.Out_Mater (polyIumat);
		if (DBERROR (gdlLine.IsEmpty ())) {
			gdlLine = GS::UniString::Printf ("material \t%4d", polyIumat);
		}
		errCode |= channelWriter.WriteLine (gdlLine);
	}

	for (ULong j = 0; j < body.GetPolygonCount () && !processControl.TestBreak (); ++j) {
		const Modeler::PGON& apgon = body.GetConstPolygon (j);
		const Modeler::PolygonAttributes apgonAttributes = body.GetConstPolygonAttributes (j);
		Int32 fpedg = apgon.fpedg;
		Int32 lpedg = apgon.lpedg;
		Int32 ivect = apgon.ivect;
		STATL pstat = apgonAttributes.GetStatus () & ~REBIT12;
		GSAttributeIndex iumat = apgonAttributes.GetMaterialIndex ();
		Wrapping tproj = apgonAttributes.GetWrapping ();
		Int32 ftpar = apgonAttributes.GetFirstTextureParameterIndex ();
		Int32 polyId	= body.GetPolygonId (j).GetValue ();

		if (iumat != polyIumat && body.GetShapeType () != B_SHADOW) {
			polyIumat = iumat;
			GS::UniString	gdlLine;
			gdlLine = writeAttributeToGDL.Out_Mater (iumat);
			if (DBERROR (gdlLine.IsEmpty ())) {
				gdlLine = GS::UniString::Printf ("material \t%4d", iumat);
			}
			errCode |= channelWriter.WriteLine (gdlLine);
		}

		if (contourOnly) {
			lpedg = fpedg - 1;
			pstat &= ~(COMPLEXBITS | HOLESCNVBIT);
		}

		if (allCurved)
			pstat |= CURVEDBIT;

		if (simpleOut)
			ivect = 0;

		if (lpedg < fpedg && !simpleOut) {	/* Original ivect is important !!! */
			errCode |= channelWriter.WriteLine (GS::UniString::Printf ("pgon\t0, %4d, %6u\t\t\t\t\t!\t#%-3u PolyId=%d",
				ivect, pstat, j + 1, polyId));
			continue;
		}

		try {
			GS::UniString	name;
			double			width = 0;
			double			height = 0;
			bool			hasAlpha = false;
			Int32			irtxt = body.GetConstPolygonAttributes (j).GetTextureIndex ();

			if (GetTextureInfo != nullptr && irtxt > 0 && GetTextureInfo (userData, j, irtxt, &name, &width, &height, &hasAlpha) == NoError) {
				errCode |= channelWriter.WriteLine (GS::UniString::Printf ("pipg\t\"%s\", %12.*G, %12.*G, %1d,\t\t\t\t\t!\t#%-3u",
					name.ToCStr().Get (),
					MESHBODY_WRITE_NUM_PREC, width,
					MESHBODY_WRITE_NUM_PREC, height,
					hasAlpha ? 1 : 0, j + 1));
				errCode |= channelWriter.WriteLine (GS::UniString::Printf ("\t\t%4d, %4d, %6u,", lpedg - fpedg + 1, ivect, pstat));
			} else {
				if (tproj == Wrapping::NoWrapping) {
					errCode |= channelWriter.WriteLine (GS::UniString::Printf ("pgon\t%4d, %4d, %6u,\t\t\t\t\t!\t#%-3u PolyId=%d",
						lpedg - fpedg + 1, ivect, pstat, j + 1, polyId));
				} else {
					if (body.GetConstPolygonAttributes (j).HasTextureCoordinateSystem ()) {
						COORD3 c0;
						COORD3 e1;
						COORD3 e2;
						COORD3 e3;
						c0.x = body.GetPolygonTextureParameter (ftpar + 0);
						c0.y = body.GetPolygonTextureParameter (ftpar + 1);
						c0.z = body.GetPolygonTextureParameter (ftpar + 2);
						e1.x = body.GetPolygonTextureParameter (ftpar + 3);
						e1.y = body.GetPolygonTextureParameter (ftpar + 4);
						e1.z = body.GetPolygonTextureParameter (ftpar + 5);
						e2.x = body.GetPolygonTextureParameter (ftpar + 6);
						e2.y = body.GetPolygonTextureParameter (ftpar + 7);
						e2.z = body.GetPolygonTextureParameter (ftpar + 8);
						e3.x = body.GetPolygonTextureParameter (ftpar + 9);
						e3.y = body.GetPolygonTextureParameter (ftpar + 10);
						e3.z = body.GetPolygonTextureParameter (ftpar + 11);

						errCode |= channelWriter.WriteLine (GS::UniString::Printf (
							"pgon{3}    %4d, %4d, %4u, %4d, %4d, %12.*G, %12.*G, %12.*G, %12.*G, %12.*G, %12.*G, %12.*G, %12.*G, %12.*G, %12.*G, %12.*G, %12.*G,	!	#%-3u PolyId=%d",
							lpedg - fpedg + 1, ivect, pstat, 
							(int)tproj.GetMethod (), (int)tproj.GetFlags (),
							MESHBODY_WRITE_NUM_PREC, c0.x, MESHBODY_WRITE_NUM_PREC, c0.y, MESHBODY_WRITE_NUM_PREC, c0.z,
							MESHBODY_WRITE_NUM_PREC, e1.x, MESHBODY_WRITE_NUM_PREC, e1.y, MESHBODY_WRITE_NUM_PREC, e1.z,
							MESHBODY_WRITE_NUM_PREC, e2.x, MESHBODY_WRITE_NUM_PREC, e2.y, MESHBODY_WRITE_NUM_PREC, e2.z,
							MESHBODY_WRITE_NUM_PREC, e3.x, MESHBODY_WRITE_NUM_PREC, e3.y, MESHBODY_WRITE_NUM_PREC, e3.z,
							j + 1,
							polyId
							));
					} else if (body.GetConstPolygonAttributes (j).HasTextureUVs ()) {
						errCode |= channelWriter.WriteLine (GS::UniString::Printf ("pgon{3}    %4d, %4d, %6u, %4d, %4d,				!	#%-3u PolyId=%d",
							lpedg - fpedg + 1, ivect, pstat, (int)tproj.GetMethod (), (int)tproj.GetFlags (), j + 1, polyId));
					}
				}
			}
		}
		catch (GS::Exception& e) {
			e.Print (dbChannel);
		}

		GS::UniString outStr;
		USize holeCount = 0;
		for (Int32 k = fpedg; k <= lpedg; k++) {
			Int32 apedg = body.GetConstPolyEdge (k);
			if (body.GetConstPolygonAttributes (j).HasTextureUVs ()) {
				UV tcoord;
				if (apedg == 0) {
					++holeCount;
				} else {
					tcoord.u = body.GetPolygonTextureParameter (ftpar + 2 * (k - fpedg - holeCount));
					tcoord.v = body.GetPolygonTextureParameter (ftpar + 2 * (k - fpedg - holeCount) + 1);
				}
				outStr += GS::UniString::Printf (k < lpedg ? "\t\t%4d, %12.*G, %12.*G," : "\t\t%4d, %12.*G, %12.*G",
					apedg,
					MESHBODY_WRITE_NUM_PREC, tcoord.u,
					MESHBODY_WRITE_NUM_PREC, tcoord.v);
			} else {
				outStr += GS::UniString::Printf (k < lpedg ? "\t\t%4d," : "\t\t%4d", apedg);
			}
			if (outStr.GetLength () > 50) {
				errCode |= channelWriter.WriteLine (outStr);
				outStr.ClearContent ();
			}
		}
		errCode |= channelWriter.WriteLine (outStr);
	}

	return errCode;
}


template <class MeshBodyType>
GSErrCode WriteAsGDLTemplate (GS::ProcessControl& processControl, 
	const MeshBodyType&								body,
	GS::OChannel&							oc,
	Modeler::MeshBody::WriteAsGDLLayout			layout,
	Modeler::MeshBody::WriteAsGDLOption			option,
	Modeler::MeshBody::WriteAsGDLTextureGetter	GetTextureInfo,
	Modeler::MeshBody::IWriteAttributesToGDL&	writeAttributeToGDL,
	void *									userData
	)
{
	GSErrCode errCode = oc.GetOutputStatus ();
	if (errCode != NoError)
		return errCode;

	if (	body.GetShapeType () != B_SHADOW && option == Modeler::MeshBody::ShadowBodiesOnly
		||	body.GetShapeType () == B_SHADOW && option != Modeler::MeshBody::ShadowBodiesToo)
	{
		return OK;
	}

	const bool allCurved = (option == Modeler::MeshBody::AllCurved);
	const bool simpleOut = (option == Modeler::MeshBody::SimpleModelOutput);

	ULong bstat = body.GetStatus () & ~REBIT12;

	ChannelWriter channelWriter (oc, layout);

	errCode |= WriteVertsAsGDLTemplate (processControl, body, channelWriter);
	
	short edgeColor = 0;
	errCode |= WriteEdgesAsGDLTemplate (processControl, body, channelWriter, option, writeAttributeToGDL, edgeColor);

	if (!simpleOut) {
		errCode |= WritePolyNormalsAsGDLTemplate (processControl, body, channelWriter);
	}

	GSAttributeIndex polyIumat = 0;
	errCode |= WritePolygonsAsGDLTemplate (processControl, body, channelWriter, option, GetTextureInfo, writeAttributeToGDL, userData, polyIumat);

	GSAttributeIndex bodyIumat = body.GetMaterialIdx ();
	if (bodyIumat != polyIumat) {
		GS::UniString	gdlLine;
		gdlLine = writeAttributeToGDL.Out_Mater (bodyIumat);
		if (DBERROR (gdlLine.IsEmpty ()))
			gdlLine = GS::UniString::Printf ("material \t%4d", bodyIumat);
		errCode |= channelWriter.WriteLine (gdlLine);
	}

	const Wrapping wrap = body.GetWrapping ();
	if (wrap != W_UNKNOWN) {

		errCode |= channelWriter.WriteLine (GS::UniString::Printf ("coor{3}\t%4d, %4d,",
			(int)wrap.GetMethod (), (int)body.GetWrapping ().GetFlags ()));
		
		const Modeler::TextureCoordSys& coor = body.GetTextureCoordSys ();
		errCode |= channelWriter.WriteLine (GS::UniString::Printf ("\t%12.*G, %12.*G, %12.*G,\n"
																	"\t%12.*G, %12.*G, %12.*G,\n"
																	"\t%12.*G, %12.*G, %12.*G,\n"
																	"\t%12.*G, %12.*G, %12.*G\n",
			MESHBODY_WRITE_NUM_PREC, coor.origin.x, MESHBODY_WRITE_NUM_PREC, coor.origin.y, MESHBODY_WRITE_NUM_PREC, coor.origin.z,
			MESHBODY_WRITE_NUM_PREC, coor.pointX.x, MESHBODY_WRITE_NUM_PREC, coor.pointX.y, MESHBODY_WRITE_NUM_PREC, coor.pointX.z,
			MESHBODY_WRITE_NUM_PREC, coor.pointY.x, MESHBODY_WRITE_NUM_PREC, coor.pointY.y, MESHBODY_WRITE_NUM_PREC, coor.pointY.z,
			MESHBODY_WRITE_NUM_PREC, coor.pointZ.x, MESHBODY_WRITE_NUM_PREC, coor.pointZ.y, MESHBODY_WRITE_NUM_PREC, coor.pointZ.z));
	}

	if (allCurved)
		bstat |= CURVEDBIT;

	if (simpleOut) {
		errCode |= channelWriter.WriteLine (GS::UniString::Printf ("body -1"));
	} else {
		errCode |= channelWriter.WriteLine (GS::UniString::Printf ("body\t%4u", bstat));
	}
	errCode |= channelWriter.WriteLine (GS::UniString ());
	return errCode;
}


template <class MeshBodyType>
GSErrCode DumpBodyGDLTemplate (	const MeshBodyType&							body,
								GS::OChannel&							oc,
								Modeler::MeshBody::WriteAsGDLOption			option)
{
	try {
		class WriteAttributesToGDLForDebug : public Modeler::MeshBody::IWriteAttributesToGDL
		{
		public:
			virtual GS::UniString Out_Mater (Int32  i)	 override { return GS::UniString::Printf ("material %d", i);	}
			virtual GS::UniString Out_Pen (short i)		 override { return GS::UniString::Printf ("pen %d", i);		}
		} writeAttributesToGDLForDebug;
		GS::NonInterruptibleProcessControl processControl;
		return WriteAsGDLTemplate (processControl, body, oc, Modeler::MeshBody::WriteAsCStr, option, nullptr, writeAttributesToGDLForDebug, nullptr);
	} catch (...) {
		return Error;
	}
}

template <typename MeshBodyType>
bool	MeshBodyAttributeIndicesBelowLimits (const MeshBodyType& body, const Modeler::Attributes::CompatibilityLimits& compatibilityLimits)
{
	for (ULong j = 0; j < body.GetPolygonCount (); j++) {
		const Modeler::PolygonAttributes& polygonAttributes = body.GetConstPolygonAttributes (j);
		if (polygonAttributes.GetTextureIndex () > static_cast<Int32>(compatibilityLimits.textureLimit)) {
			return false;
		}
		if (polygonAttributes.GetMaterialIndex () > static_cast<Int32>(compatibilityLimits.materialLimit)) {
			return false;
		}
	}

	if (body.GetMaterialIdx () > static_cast<Int32>(compatibilityLimits.materialLimit)) {
		return false;
	}
	return true;
}

template <typename MeshBodyType>
void InvalidateEdge (MeshBodyType& body, ULong edgeIndex)
{
	EDGE edge = body.GetConstEdge (edgeIndex);
	edge.pgon1 = edge.pgon2 = -1;
	edge.vert1 = edge.vert2 = -1;
	body.SetEdge (edgeIndex, edge);
	Modeler::EdgeAttributes edgeAttributes = body.GetConstEdgeAttributes (edgeIndex);
	edgeAttributes.SetInvisible (true);
	body.SetEdgeAttributes (edgeIndex, edgeAttributes);
}

template <typename MeshBodyType>
bool IsInvalidatedEdge (const MeshBodyType& body, ULong edgeIndex)
{
	const EDGE& edge = body.GetConstEdge (edgeIndex);
	const Modeler::EdgeAttributes& edgeAttributes = body.GetConstEdgeAttributes (edgeIndex);
	return edge.pgon1 == -1 && edge.pgon2 == -1 && edgeAttributes.IsInvisible ();
}

#endif // #if !defined (MESHBODYUTILTEMPLATES_HPP)
