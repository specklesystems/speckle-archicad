// *********************************************************************************************************************
// Description:		IElevatedPolylineOffseter template class
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	AB
//
// *********************************************************************************************************************

#if !defined (GEOMETRY_IELEVATEDPOLYLINEOFFSETER_HPP)
#define GEOMETRY_IELEVATEDPOLYLINEOFFSETER_HPP

#pragma once

// from GSRoot
#include "GSRoot.hpp"
#include "HashSet.hpp"
#include "Vector3D.hpp"
#include "Polyline2D.hpp"


namespace Geometry {


// --- IElevatedPolylineOffseter -----------------------------------------------------------


template <typename P>
class IElevatedPolylineOffseter
{
public:
	using PolylineType = P;
	using ConstVertexIterator = typename PolylineType::ConstVertexIterator;


protected:
	virtual UInt32	GetVertexPolyId (const ConstVertexIterator& vertexIt) const = 0;
	virtual double	GetVertexZ		(const ConstVertexIterator& vertexIt) const = 0;
	virtual void	SetVertexZ		(PolylineType& polyline, const ConstVertexIterator& vertexIt, double z) = 0;


private:
	struct OffsetedGeometryData
	{
		Coord	coord;
		double	z;
		UIndex	edgeIndexInOffsetedPolyline;
		double	edgeArcAngle;
	};


	static bool GetPolylineCoordsAndArcs (const PolylineType& sourcePolyline, GS::Array<Coord>& coordArray, GS::Array<PolyArcRec>& arcArray)
	{
		if (sourcePolyline.IsEmpty ())
			return false;

		coordArray.Clear ();
		coordArray.EnsureCapacity (sourcePolyline.GetVertexNum ());
		coordArray.Push (Coord ());

		for (ConstVertexIterator sourceVertexIt = sourcePolyline.EnumerateVertex (); sourceVertexIt != nullptr; ++sourceVertexIt)
			coordArray.Push (sourceVertexIt->GetCoord ());

		if (DBERROR (coordArray.GetSize () < 3))
			return false;

		arcArray.Clear ();
		if (sourcePolyline.HasArcs ()) {
			for (UIndex edgeIndex = 1;  edgeIndex <= sourcePolyline.GetEdgeNum ();  ++edgeIndex) {
				typename PolylineType::ConstEdgeIterator edgeIt = sourcePolyline.GetEdgeIterator (edgeIndex);
				Sector sect;
				GenArc genArc;
				if (sourcePolyline.GetSector (edgeIt, sect, genArc)) {
					double angle = Geometry::CalcGenArcAngle (&genArc);
					if (Geometry::IsNotNearZero (angle))
						arcArray.PushNew (edgeIndex, edgeIndex + 1, angle);
				}
			}
		}

		return true;
	}


	//	Creates a new polyline where zero-length (vertical) edges are tilted a tiny bit into the direction of the following edge, so OffsetAllEdges will work as expected.
	static bool FixVerticalEdges (const PolylineType& sourcePolyline, PolylineType& resultPolyline, GS::HashTable<UIndex, Vector2D>* deltas = nullptr)
	{
		GS::Array<Coord>		coordArray;
		GS::Array<PolyArcRec>	arcArray;
		if (!GetPolylineCoordsAndArcs (sourcePolyline, coordArray, arcArray))
			return false;

		const double deltaLen = 2.0 * Eps;

		bool isVerticalPart = false;
		UIndex firstVertexOfVerticalPart = 0;	// keep compiler happy
		UIndex lastVertexOfVerticalPart;

		const USize arraySize = coordArray.GetSize ();
		for (UIndex i = 1, j = 2; j < arraySize; i = j++) {
			if (Geometry::IsNear (coordArray[i], coordArray[j])) {
				if (!isVerticalPart) {
					firstVertexOfVerticalPart = i;
					isVerticalPart = true;
				}
			} else if (isVerticalPart) {
				DBASSERT (firstVertexOfVerticalPart > 0);
				lastVertexOfVerticalPart = i;
				isVerticalPart = false;

				// Magic happens here:
				Vector dir;
				double arcAngle = sourcePolyline.GetEdgeIterator (i)->GetArcAngle ();
				if (Geometry::IsNearZero (arcAngle)) {
					dir = Geometry::UnitVector (coordArray[j] - coordArray[i]);
				} else {
					GenArc genArc = Geometry::GenArc::CreateCircleArc (coordArray[i], coordArray[j], arcAngle);
					dir = Geometry::GetGenArcBegDirection (genArc).ToVector2D ();
				}

				Vector delta = deltaLen * dir;
				Vector offs = delta;
				for (UIndex k = firstVertexOfVerticalPart + 1; k <= lastVertexOfVerticalPart; ++k, offs += delta) {
					coordArray[k] += offs;
					if (deltas != nullptr)
						deltas->Add (k, offs);
				}
			}
		}

		// Create resultPolyline from the coords and arcAngles collected above
		UInt32 polyCreateFlags = Geometry::PolyCreateFlags_VBElemPolygonDataRepresentation;
		UInt32 polyFlags = sourcePolyline.GetPolyFlags ();
		resultPolyline = PolylineType (polyFlags, coordArray, arcArray, polyCreateFlags);
		if (DBERROR (sourcePolyline.GetVertexNum () != resultPolyline.GetVertexNum ()))
			return false;

		// Also copy vertex & edge user data
		for (ConstVertexIterator sourceVertexIt = sourcePolyline.EnumerateVertex (), resultVertexIt = resultPolyline.EnumerateVertex (); sourceVertexIt != nullptr;  ++sourceVertexIt, ++resultVertexIt)
			resultPolyline.SetVertexUserData (resultVertexIt, sourcePolyline.GetVertexUserData (sourceVertexIt));

		for (typename PolylineType::ConstEdgeIterator sourceEdgeIt = sourcePolyline.EnumerateEdge (), resultEdgeIt = resultPolyline.EnumerateEdge (); sourceEdgeIt != nullptr;  ++sourceEdgeIt, ++resultEdgeIt)
			resultPolyline.SetEdgeUserData (resultEdgeIt, sourcePolyline.GetEdgeUserData (sourceEdgeIt));

		return true;
	}


	static void GetPolylineEdgeArcAngles (const PolylineType& polyline, GS::Array<double>& arcAngleArray)
	{
		arcAngleArray.Clear ();
		arcAngleArray.Push (0.0);

		if (polyline.HasArcs ()) {
			for (UIndex edgeIndex = 1;  edgeIndex <= polyline.GetEdgeNum ();  ++edgeIndex) {
				typename PolylineType::ConstEdgeIterator edgeIt = polyline.GetEdgeIterator (edgeIndex);
				Coord begC, endC;
				double angle = 0.0;
				polyline.GetSector (edgeIt, begC, endC, angle);
				arcAngleArray.Push (angle);
			}
		} else {
			// Fill with zeroes
			arcAngleArray.SetSize (polyline.GetEdgeNum () + 1);
		}
	}


	static bool CalculateOffsetedVertexZ	(const Coord& srcA,	 const double aZ,
											 const Coord& srcB,	 const double bZ,
											 const Coord& offsB,
											 const double srcAngle,
											 double& zOut)
	{
		double ratio;
		if (Geometry::IsNearZero (srcAngle)) {
			Vector ab = srcB - srcA;
			double abLenSqr = ab.GetLengthSqr ();
			if (Geometry::IsNearZero (abLenSqr, EPS*EPS))
				return false;

			ratio = (offsB - srcA) * (ab / abLenSqr);
		} else {
			Coord origo;
			if (DBERROR (!Geometry::ArcGetOrigo (&srcA, &srcB, srcAngle, &origo)))
				return false;

			Vector sa = srcA  - origo;
			Vector ob = offsB - origo;
			double sinAlpha = sa.GetUnitVector () ^ ob.GetUnitVector ();
			double alpha = Geometry::ArcSin (sinAlpha);

			ratio = alpha / srcAngle;
		}

		zOut = aZ + ratio * (bZ - aZ);
		return true;
	}


	static void AdjustOffsetedVertexZ (const GS::Array<Coord>&	sourceVertexCoordArray,
									   const GS::Array<double>&	sourceEdgeArcAngleArray,
									   const GS::Array<Coord>&	offsetedCoordArray,
									   GS::Array<double>&		offsetedZArray,
									   const UIndex				vertexIndex)
	{
		/*
			       i,j
			       / \
			      /   \
			 (f) /     \ (g)
			    /  b,c  \
			   /   / \   \
			  /   /   \   \
			 /   /     \   \
			e   a       d   h

			a,b,c,d: source
			e,i,j,h: offseted
			(f): b offseted perpendicularly
			(g): c offseted perpendicularly

			[vertexIndex - 2]: a, e
			[vertexIndex - 1]: b, i
			[vertexIndex    ]: c, j
			[vertexIndex + 1]: d, h
		*/
		const Coord& c = sourceVertexCoordArray[vertexIndex];		// assuming it has the same vertices as the offseted polyline
		const Coord& i = offsetedCoordArray[vertexIndex - 1];
		const Coord& j = offsetedCoordArray[vertexIndex];
		Vector ci = i - c;
		Vector cj = j - c;
		// Only do it if points i, c, j are NOT collinear
		if (Geometry::IsNearZero (ci ^ cj))
			return;

		// Adjust z value at i
		if (vertexIndex > 2) {
			double adjustedVertexZ;
			if (CalculateOffsetedVertexZ (sourceVertexCoordArray[vertexIndex - 2],	offsetedZArray[vertexIndex - 2],
										  sourceVertexCoordArray[vertexIndex - 1],	offsetedZArray[vertexIndex - 1],
										  offsetedCoordArray[vertexIndex - 1],
										  sourceEdgeArcAngleArray[vertexIndex - 2],
										  adjustedVertexZ))
			{
				offsetedZArray[vertexIndex - 1] = adjustedVertexZ;
			}
		}

		// Adjust z value at j
		if (vertexIndex < offsetedZArray.GetSize () - 1 &&
			DBVERIFY (vertexIndex < sourceVertexCoordArray.GetSize () - 1) &&
			DBVERIFY (vertexIndex < sourceEdgeArcAngleArray.GetSize ())) {
			double adjustedVertexZ;
			if (CalculateOffsetedVertexZ (sourceVertexCoordArray[vertexIndex + 1],	offsetedZArray[vertexIndex + 1],
										  sourceVertexCoordArray[vertexIndex],		offsetedZArray[vertexIndex],
										  offsetedCoordArray[vertexIndex],
										  sourceEdgeArcAngleArray[vertexIndex],
										  adjustedVertexZ))
			{
				offsetedZArray[vertexIndex] = adjustedVertexZ;
			}
		}
	}


	void GetOffsetedGeometryData (const PolylineType& polyline, GS::HashTable<UInt32, OffsetedGeometryData>& offsetedGeometryDataByVertexPolyId) const
	{
		for (ConstVertexIterator offsetedVertexIt = polyline.EnumerateVertex (); offsetedVertexIt != nullptr; ++offsetedVertexIt) {
			UInt32 vertexPolyId = GetVertexPolyId (offsetedVertexIt);
			if (!offsetedGeometryDataByVertexPolyId.ContainsKey (vertexPolyId)) {

				double offsetedEdgeArcAngle = 0.0;

				UIndex edgeIndex = offsetedVertexIt->GetIndex ();
				if (edgeIndex <= polyline.GetEdgeNum ()) {
					typename PolylineType::ConstEdgeIterator edgeIt = polyline.GetEdgeIterator (edgeIndex);
					Coord begC, endC;
					polyline.GetSector (edgeIt, begC, endC, offsetedEdgeArcAngle);
				}

				OffsetedGeometryData data {
					offsetedVertexIt->GetCoord (),
					GetVertexZ (offsetedVertexIt),
					offsetedVertexIt->GetIndex (),		// Index of edge starting at this vertex
					offsetedEdgeArcAngle
				};

				offsetedGeometryDataByVertexPolyId.Add (vertexPolyId, data);
			}
		}
	}


	void GetOffsetedArcData	   (const PolylineType&									sourcePolyline,
								const GS::HashTable<UInt32, OffsetedGeometryData>&	offsetedGeometryDataByVertexPolyId,
								GS::Array<PolyArcRec>&								offsetedArcArray) const
	{
		// Fill arc array from the offseted edge data
		for (ConstVertexIterator sourceVertexIt = sourcePolyline.EnumerateVertex (); sourceVertexIt != nullptr; ++sourceVertexIt) {

			// Find the arc angles of the edges after each vertex of sourcePolyline in offsetedTemporaryPolyline, and store them
			UInt32 sourceVertexPolyId = GetVertexPolyId (sourceVertexIt);
			if (DBVERIFY (offsetedGeometryDataByVertexPolyId.ContainsKey (sourceVertexPolyId))) {
				const OffsetedGeometryData& data = offsetedGeometryDataByVertexPolyId.Get (sourceVertexPolyId);

				UIndex edgeIndex = data.edgeIndexInOffsetedPolyline;
				if (Geometry::IsNotNearZero (data.edgeArcAngle))
					offsetedArcArray.PushNew (edgeIndex, edgeIndex + 1, data.edgeArcAngle);
			}
		}
	}


public:

	bool Offset (const PolylineType&		sourcePolyline,
				 const GS::Array<UIndex>&	edgeIndices,
				 double						offset,
				 PolylineType&				resultPolyline,
				 GS::HashSet<UIndex>*		verticalEdgeVertices = nullptr)
	{
		if (sourcePolyline.IsEmpty ())
			return false;

		PolylineType	offsetedTemporaryPolyline;

		GS::HashTable<UIndex, Vector2D>	deltas;

		{
			PolylineType temporaryPolyline;
			FixVerticalEdges (sourcePolyline, temporaryPolyline, &deltas);

			if (edgeIndices.IsEmpty ()) {
				// Offset all edges
				double newOffset = 0.0;
				offsetedTemporaryPolyline = temporaryPolyline.OffsetAllEdge (offset, &newOffset);
			} else {
				// Offset selected edges only
				DBASSERT (edgeIndices.GetSize () == 1);
				typename PolylineType::ConstEdgeIterator edgeIt = temporaryPolyline.GetEdgeIterator (edgeIndices.GetFirst () + 1);
				offsetedTemporaryPolyline = temporaryPolyline.OffsetEdge (edgeIt, offset);
			}
		}

		GS::HashTable<UInt32, OffsetedGeometryData>	offsetedGeometryDataByVertexPolyId;
		GetOffsetedGeometryData (offsetedTemporaryPolyline, offsetedGeometryDataByVertexPolyId);

		// Store edge arcAngles from sourcePolyline (vertex indices are the same as in resultPolyline)
		GS::Array<double> sourceEdgeArcAngleArray;
		GetPolylineEdgeArcAngles (sourcePolyline, sourceEdgeArcAngleArray);


		GS::Array<Coord> sourceVertexCoordArray;
		sourceVertexCoordArray.Push (Coord ());

		GS::Array<Coord> offsetedCoordArray;
		offsetedCoordArray.Push (Coord ());

		GS::Array<double> offsetedZArray;
		offsetedZArray.Push (0.0);

		for (ConstVertexIterator sourceVertexIt = sourcePolyline.EnumerateVertex (); sourceVertexIt != nullptr; ++sourceVertexIt) {
			OffsetedGeometryData data;

			// Find the offseted coords, elevation and arc angles for each vertex of sourcePolyline in offsetedTemporaryPolyline, and store them
			UInt32 sourceVertexPolyId = GetVertexPolyId (sourceVertexIt);
			if (DBVERIFY (offsetedGeometryDataByVertexPolyId.ContainsKey (sourceVertexPolyId))) {
				data = offsetedGeometryDataByVertexPolyId.Get (sourceVertexPolyId);
			} else {
				// Unlikely, but we still have to provide a sensible coord
				data.coord = offsetedCoordArray.GetLast ();
				data.z = offsetedZArray.GetLast ();
				data.edgeIndexInOffsetedPolyline = 0;
				data.edgeArcAngle = 0.0;
			}

			offsetedCoordArray.Push (data.coord);
			offsetedZArray.Push (data.z);

			// Also store source vertex coords
			sourceVertexCoordArray.Push (sourceVertexIt->GetCoord ());
		}

		// Undo shifts made by FixVerticalEdges
		for (const auto& delta : deltas)
			offsetedCoordArray[delta.key] -= delta.value;

		// Adjust Z values at intersection points
		for (const auto& delta : deltas) {
			const UIndex vertexIndex = delta.key;
			if (DBVERIFY (vertexIndex > 1)) {
				AdjustOffsetedVertexZ (sourceVertexCoordArray, sourceEdgeArcAngleArray, offsetedCoordArray, offsetedZArray, vertexIndex);
			}
		}

		if (verticalEdgeVertices != nullptr) {
			// Save vertex indices of vertical edges
			for (const auto& delta : deltas) {
				const UIndex vertexIndex = delta.key;
				if (DBVERIFY (vertexIndex > 1))
					verticalEdgeVertices->Add (vertexIndex - 1);	// bottom vertex

				verticalEdgeVertices->Add (vertexIndex);			// top vertex
			}
		}

		if (DBERROR (offsetedCoordArray.GetSize () < 3))
			return false;

		// Fill arc array from the offseted edge data
		GS::Array<PolyArcRec> offsetedArcArray;
		if (offsetedTemporaryPolyline.HasArcs ())
			GetOffsetedArcData (sourcePolyline, offsetedGeometryDataByVertexPolyId, offsetedArcArray);

		// Create resultPolyline from the offseted coords and arcAngles collected above
		UInt32 polyCreateFlags = Geometry::PolyCreateFlags_VBElemPolygonDataRepresentation;
		UInt32 polyFlags = sourcePolyline.GetPolyFlags ();
		resultPolyline = PolylineType (polyFlags, offsetedCoordArray, offsetedArcArray, polyCreateFlags);
		if (DBERROR (sourcePolyline.GetVertexNum () != resultPolyline.GetVertexNum ()))
			return false;

		// Also copy vertex & edge user data
		for (ConstVertexIterator sourceVertexIt = sourcePolyline.EnumerateVertex (), resultVertexIt = resultPolyline.EnumerateVertex (); sourceVertexIt != nullptr;  ++sourceVertexIt, ++resultVertexIt) {
			resultPolyline.SetVertexUserData (resultVertexIt, sourcePolyline.GetVertexUserData (sourceVertexIt));

			// Override Z values
			UIndex vertexIndex = sourceVertexIt->GetIndex ();
			SetVertexZ (resultPolyline, resultVertexIt, offsetedZArray[vertexIndex]);
		}

		for (typename PolylineType::ConstEdgeIterator sourceEdgeIt = sourcePolyline.EnumerateEdge (), resultEdgeIt = resultPolyline.EnumerateEdge (); sourceEdgeIt != nullptr;  ++sourceEdgeIt, ++resultEdgeIt)
			resultPolyline.SetEdgeUserData (resultEdgeIt, sourcePolyline.GetEdgeUserData (sourceEdgeIt));

		return true;
	}

};	// class IOffsetElevatedPolylineFunctor



}	// namespace

#endif
