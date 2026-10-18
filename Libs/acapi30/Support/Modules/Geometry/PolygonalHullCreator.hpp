#if !defined POLYGONAL_HULL_CREATOR
#define POLYGONAL_HULL_CREATOR

//from GSRoot
#include "HashTable.hpp"
#include "Pair.hpp"

//from Geometry
#include "Point2D.hpp"
#include "CorePolyline2DClassDefinition.hpp"
#include "UnitVector2DClassDeclaration.hpp"
#include "Polygon2D.hpp"
#include "IrregularPolygon2D.hpp"
#include "UnitVector2D.hpp"

namespace Geometry {


class GEOMETRY_DLL_EXPORT DirectionComparator {
public:
	enum RelativeDirection {
		Left,
		Right,
		OnIt
	};

	DirectionComparator (const Point2D& refPoint, const UnitVector_2D& forwardDir);
	bool operator () (const Point2D& first, const Point2D& second) const;
	RelativeDirection WhichSideOfCurve (const Point2D& point, const Curve2DData& curve) const;
	RelativeDirection WhichSideOfArc (const Point2D& point, const GenArc& arc, GS::Array<Point2D>* innerCrossPoints) const;
	RelativeDirection CompareSecondToFirstCurve (const Curve2DData& first, const Curve2DData& second) const;
	RelativeDirection CompareSecondToFirstVector (const UnitVector_2D& first, const UnitVector_2D& second) const;
	double GetRightTurnFromForwardDir (const UnitVector_2D& dir) const;
	UnitVector_2D GetDirectionAtBegin (const Curve2DData& curve) const;
	const UnitVector_2D& GetForwardDir ();

	static bool IsColinearWithSameDir (const UnitVector_2D& vec1, const UnitVector_2D& vec2);
	static bool IsColinearWithOppositeDir (const UnitVector_2D& vec1, const UnitVector_2D& vec2);

private:
	const Point2D		m_referencePoint;
	const UnitVector_2D m_forwardDir;

	UnitVector_2D GetTangentDirectionAtBeg (GenArc arc) const;
	RelativeDirection Mirror (RelativeDirection dir) const;
};

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
class PolygonalHullCreator {
public:
	typedef CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> PolyType;
	typedef CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> MultiPolyType;

	PolygonalHullCreator (Point2D origo = Point2D (0.0, 0.0), UnitVector_2D generalForwardDir = UnitVector_2D::YAxis);
	~PolygonalHullCreator () {};

	void InitializeWithPolygons (const MultiPolyType& multiPolygon);
	void AddPointWithEdges (const HashableCoord& c, VertexUserData vertexData, Curve2DData prevEdge, EdgeUserData prevEdgeData, Curve2DData nextEdge, EdgeUserData nextEdgeData);
	void ClearPoints ();

	GS::Optional<PolyType> CalculatePolygonalHull ();

private:
	static Curve2DData CalculateCurveData (const PolyType& poly, const typename PolyType::ConstEdgeIterator& edgeIt);

	HashableCoord m_origo;
	UnitVector_2D m_generalForwardDir;

	GS::HashTable <HashableCoord, VertexUserData> vertexUserDatas;
	GS::HashTable <HashableCoord, GS::Pair<Curve2DData, EdgeUserData>> firstEdges;
	GS::HashTable <HashableCoord, GS::Pair<Curve2DData, EdgeUserData>> secondEdges;

	class PolygonDataContainer {
	public:
		void AddVertexWithNextEdge (Point2D point, VertexUserData pointData, Curve2DData edge, EdgeUserData edgeData) {
			DBASSERT_STR (GetCurve2DDataBegPosition (edge).IsNear (point), "The new edge should start from the new point!");
			DBASSERT_STR (edges.GetSize () == 0 || GetCurve2DDataEndPosition (edges.GetLast ()).IsNear (point), "The new point should be connected to the last edge!");
			
			vertices.Push (point);
			verticesUserData.Push (pointData);
			edges.Push (edge);
			edgesUserData.Push (edgeData);
		}

		void Clear () { vertices.Clear (); verticesUserData.Clear (); edges.Clear (); edgesUserData.Clear (); }
		bool IsClosed () { return (GetCurve2DDataBegPosition (edges.GetLast ()).IsNear (vertices.GetFirst ()) || GetCurve2DDataEndPosition (edges.GetLast ()).IsNear (vertices.GetFirst ())); }

		GS::Optional<PolyType> GetPolygon () {
			//check whether the vertex/edge lists have the same legth
			DBASSERT (vertices.GetSize () == verticesUserData.GetSize () &&
					  vertices.GetSize () == edges.GetSize () &&
					  vertices.GetSize () == edgesUserData.GetSize ());

			//look for arcs
			GS::Array<PolyArcRec> arcList;
			for (UIndex i = 0; i < edges.GetSize (); i++) {
				if (edges[i].type == CURVE2D_GenArc) {
					PolyArcRec newArcRec (i + 1, i + 2, edges[i].genArc.GetArcAngle ());
					arcList.Push (newArcRec);
				}
			}

			CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> tmpIrregPoly;
			tmpIrregPoly = CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (vertices, arcList, 0);

			//put up edge and user data
			UInt32 j = 0;
			for (auto it = tmpIrregPoly.EnumerateVertex (); it != nullptr; ++it, ++j) {
				if (DBVERIFY (j < verticesUserData.GetSize ())) {
					tmpIrregPoly.SetVertexUserData (it, verticesUserData[j]);
				}
			}

			j = 0;
			for (auto it = tmpIrregPoly.EnumerateEdge (); it != nullptr; ++it, ++j) {
				if (DBVERIFY (j < edgesUserData.GetSize ())) {
					tmpIrregPoly.SetEdgeUserData (it, edgesUserData[j]);
				}
			}

			//regularize polygon
			CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> tmpMultiPoly;
			tmpMultiPoly = tmpIrregPoly.Regularize ();

			if (DBERROR_STR (tmpMultiPoly.GetSize () != 1, "Result polygon was irregular!")) {
				if (tmpMultiPoly.GetSize () > 1)
					return tmpMultiPoly[1];
				else
					return GS::NoValue;
			} else
				return tmpMultiPoly.GetFirst ();
		}

		bool IsPointInPolygon (const Point2D point) const
		{ 
			return vertices.Contains ([&](const Point2D& polyVertex) -> bool {
				return polyVertex.IsNear (point);
			});
		}

		bool IsOppositeOfLastEdgeInPoly (const Curve2DData& edge) const
		{
			if (edges.IsEmpty ())
				return false;

			Curve2DData lastEdgeInPoly = edges.GetLast ();
			if (lastEdgeInPoly.type == CURVE2D_Sector && edge.type == CURVE2D_Sector) {
				Sector lastEdgeInverted = lastEdgeInPoly.sector.InvertDirection ();
				if (lastEdgeInverted.BegPoint ().IsNear (edge.sector.BegPoint ()) && lastEdgeInverted.EndPoint ().IsNear (edge.sector.EndPoint ())) {
					return true;
				}
			} else if (lastEdgeInPoly.type == CURVE2D_GenArc && edge.type == CURVE2D_GenArc) {
				GenArc lastEdgeInverted = lastEdgeInPoly.genArc;
				lastEdgeInverted.Reflect ();
				if (lastEdgeInverted.IsEqual (edge.genArc)) {
					return true;
				}
			}
			return false;
		}

		void DeleteFirstEdgesUntilPoint (const Point2D firstPointToRemain)
		{
			if (!IsPointInPolygon (firstPointToRemain)) {
				return;
			}

			UIndex firstIndexToRemain = vertices.FindFirst ([&](const Point2D& polyVertex) -> bool {
				return polyVertex.IsNear (firstPointToRemain);
			});

			vertices.Delete (0, firstIndexToRemain);
			verticesUserData.Delete (0, firstIndexToRemain);
			edges.Delete (0, firstIndexToRemain);
			edgesUserData.Delete (0, firstIndexToRemain);
		}

		void CleanUpNewEdgesIfUglyConcave (EdgeUserData newEdgeData)
		{
			for (UInt32 edgeIndex = 0; edgeIndex < vertices.GetSize (); edgeIndex++) {
				UInt32 previousEdgeIndex = (edgeIndex > 0) ? edgeIndex - 1 : vertices.GetSize () - 1;
				UInt32 nextEdgeIndex = (edgeIndex < vertices.GetSize () - 1) ? edgeIndex + 1 : 0;
			
				if ((edgesUserData[previousEdgeIndex] == newEdgeData || edgesUserData[edgeIndex] == newEdgeData)
				 	 && edges[edgeIndex].type == CURVE2D_Sector
					 && edges[previousEdgeIndex].type == CURVE2D_Sector) {

					UnitVector_2D lastEdgeDir = UnitVector_2D::Create (vertices[edgeIndex] - vertices[previousEdgeIndex]);
					UnitVector_2D nextEdgeDir = UnitVector_2D::Create (vertices[nextEdgeIndex] - vertices[edgeIndex]);

					double rightTurn = DirectionComparator (vertices[edgeIndex], lastEdgeDir).GetRightTurnFromForwardDir (nextEdgeDir);
					if (rightTurn > 0.5) { //this was an arbitrary value, we don't accept vertices with a more than 270degree inside angle
						RemoveVertexAndConnectNeighbours (edgeIndex, newEdgeData);
					}
				}

			}
		}

	private:
		void RemoveVertexAndConnectNeighbours (UInt32 vertexIndex, EdgeUserData newEdgeData)
		{
			DBASSERT (vertices.GetSize () >= 3);

			const USize vertexCountAfterDelete = vertices.GetSize () - 1;
			const UInt32 previousVertexIndexAfterDelete = (vertexCountAfterDelete + vertexIndex - 1) % vertexCountAfterDelete;
			const UInt32 nextVertexIndexAfterDelete = vertexIndex % vertexCountAfterDelete;

			vertices.Delete (vertexIndex);
			verticesUserData.Delete (vertexIndex);
			edges.Delete (vertexIndex);
			edgesUserData.Delete (vertexIndex);

			Sector sector (vertices[previousVertexIndexAfterDelete], vertices[nextVertexIndexAfterDelete]);
			Curve2DData curve;
			InitCurve2DData (&curve, sector, Geometry::Curve2DDataType::CURVE2D_Sector);
			edges[previousVertexIndexAfterDelete] = curve;
			edgesUserData[previousVertexIndexAfterDelete] = newEdgeData;
		}

		GS::Array<Point2D> vertices;
		GS::Array<VertexUserData> verticesUserData;
		GS::Array<Curve2DData> edges;
		GS::Array<EdgeUserData> edgesUserData;
	};

	PolygonDataContainer polygonInTheMaking;

	void CalculateMidPoint (const MultiPolyType& multiPolygon);
	void ConnectAlongEdge (HashableCoord& firstPoint, Point2D lastPoint, bool firstEdge);
	void ConnectWithDefaultEdge (HashableCoord& firstPoint, HashableCoord& lastPoint);
	void DrawCurvedEdgeAlongArc (const Point2D startPoint, const VertexUserData startPointUserData, const Point2D endPoint, const Point2D arcOrigo, const bool isArcReflected, const EdgeUserData edgeData);

};

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
Curve2DData PolygonalHullCreator<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalculateCurveData (const PolyType& poly, const typename PolyType::ConstEdgeIterator& edgeIt)
{
	Curve2DData result;
	Sector sector;
	GenArc arc;
	bool isArc = poly.GetSector (edgeIt, sector, arc);
	if (isArc) {
		InitCurve2DData (&result, arc);
	} else {
		InitCurve2DData (&result, sector, Curve2DDataType::CURVE2D_Sector);
	}
	return result;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void Geometry::PolygonalHullCreator<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InitializeWithPolygons (const MultiPolyType& multiPolygon)
{
	ClearPoints ();

	MultiPolyType newMultiPoly (multiPolygon);
	newMultiPoly.Unify (PolyHoleHandling::WithoutHoles);

	CalculateMidPoint (newMultiPoly);

	for (const PolyType& poly : newMultiPoly) {
		for (typename PolyType::ConstVertexIterator it = poly.BeginVertex (); it != poly.EndVertex (); ++it)
		{
			HashableCoord c (poly.GetVertex (it).GetCoord ());

			const typename PolyType::ConstEdgeIterator prevEdgeIt = poly.GetPrevEdge (it);
			const typename PolyType::ConstEdgeIterator nextEdgeIt = poly.GetNextEdge (it);

			const Curve2DData prevEdgeData = CalculateCurveData (poly, prevEdgeIt);
			const Curve2DData nextEdgeData = CalculateCurveData (poly, nextEdgeIt);

			AddPointWithEdges (c, poly.GetVertexUserData (it), prevEdgeData, poly.GetEdgeUserData (prevEdgeIt), nextEdgeData, poly.GetEdgeUserData (nextEdgeIt));
		}
	}

}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void Geometry::PolygonalHullCreator<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalculateMidPoint (const MultiPolyType& multiPolygon)
{
	MultiPolyType segmentedMultiPoly = multiPolygon;
	segmentedMultiPoly.SegmentUp (ArcDivParams (0.1));
	Point2D newOrigo = Point2D (0.0, 0.0);
	Int32 sum = 0;
	for (const PolyType& poly : segmentedMultiPoly) {
		for (typename PolyType::ConstVertexIterator it = poly.BeginVertex (); it != poly.EndVertex (); ++it) {
			newOrigo.x += poly.GetVertex (it).GetCoord ().x;
			newOrigo.y += poly.GetVertex (it).GetCoord ().y;
			sum++;
		}
	}
	newOrigo.x /= sum;
	newOrigo.y /= sum;

	m_origo = newOrigo;
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
PolygonalHullCreator<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonalHullCreator (Point2D origo /*= Point2D (0.0, 0.0)*/, UnitVector_2D generalForwardDir /*= UnitVector_2D::YAxis*/)
	: m_origo (HashableCoord (origo)),
	m_generalForwardDir (generalForwardDir)
{
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void PolygonalHullCreator<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::AddPointWithEdges (const HashableCoord& c, VertexUserData vertexData, Curve2DData prevEdge, EdgeUserData prevEdgeData, Curve2DData nextEdge, EdgeUserData nextEdgeData)
{
	auto checkAndCorrectEdgeDirection = [](Curve2DData* edge, Point2D startPoint) {
		switch (edge->type) {
		case CURVE2D_Sector: {
			if (edge->sector.c2.IsNear (startPoint))
				InvertSectorOrientation (edge->sector);
			else
				DBASSERT_STR (edge->sector.c1.IsNear (startPoint), "Edge should start or end in polygon vertex!");
			break;
		}
		case CURVE2D_GenArc: {
			if (edge->genArc.GetEndC ().IsNear (startPoint))
				edge->genArc.Reflect ();
			else
				DBASSERT_STR (edge->genArc.GetBegC ().IsNear (startPoint), "Edge should start or end in polygon vertex!");
			break;
		}
		default:
			DBBREAK_STR ("Polygon edges should be sectors or arcs!");
			break;
		}
	};

	checkAndCorrectEdgeDirection (&prevEdge, c);
	checkAndCorrectEdgeDirection (&nextEdge, c);

	vertexUserDatas.Add (c, vertexData);
	firstEdges.Add (c, GS::Pair<Curve2DData, EdgeUserData> (prevEdge, prevEdgeData));
	secondEdges.Add (c, GS::Pair<Curve2DData, EdgeUserData> (nextEdge, nextEdgeData));
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void PolygonalHullCreator<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ClearPoints ()
{
	vertexUserDatas.Clear ();
	firstEdges.Clear ();
	secondEdges.Clear ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::Optional<CustomPolygon2D <VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>> PolygonalHullCreator<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalculatePolygonalHull ()
{
	DBASSERT (vertexUserDatas.GetSize () > 2); //assert if we have less than three points!
	
	GS::Array<HashableCoord> pointsToConnect;
	for (auto it = vertexUserDatas.Enumerate (); it != nullptr; it++)
		pointsToConnect.Push (it->key);

	//sort all the points according to how 'right' they lay from the startingpoint and the forward line
	DirectionComparator comparator (m_origo, m_generalForwardDir);
	GS::Sort (pointsToConnect.Begin (), pointsToConnect.End (), comparator);
	GS::Reverse (pointsToConnect.Begin (), pointsToConnect.End ());

	pointsToConnect.Push (pointsToConnect.GetFirst ()); //we have to connect the first point in the line to the last..

	//go through the sorted array of points, connect point to the line if its not on the left side of the edge

	polygonInTheMaking.Clear ();

	HashableCoord  currentLastPoint = pointsToConnect.GetFirst ();

#ifdef DEBUVERS_GZs
	DBPrintf ("Midpoint coordinates: %f, %f", m_origo.x, m_origo.y);
	DBPrintf ("Points to connect in the polygonial hull: \n");
	for (auto it = pointsToConnect.Enumerate (); it != nullptr; ++it) {
		DBPrintf ("%f, %f \n", (*it).x, (*it).y);
	}
#endif

	for (UIndex i = 1; i < pointsToConnect.GetSize (); i++) {
		HashableCoord nextPointToConnect = pointsToConnect[i];
		DirectionComparator comp (currentLastPoint, ConvertToUnitVector (m_origo - currentLastPoint, m_generalForwardDir));
		
		const Curve2DData& firstEdgeFromCurrPoint = firstEdges.Get (currentLastPoint).first;
		const Curve2DData& secondEdgeFromCurrPoint = secondEdges.Get (currentLastPoint).first;
		
		DirectionComparator::RelativeDirection dirToFirstEdge = comp.WhichSideOfCurve (nextPointToConnect, firstEdgeFromCurrPoint);
		DirectionComparator::RelativeDirection dirToSecondEdge = comp.WhichSideOfCurve (nextPointToConnect, secondEdgeFromCurrPoint);
		if (polygonInTheMaking.IsOppositeOfLastEdgeInPoly (firstEdgeFromCurrPoint)) {
			dirToFirstEdge = DirectionComparator::RelativeDirection::Right;
		} else if (polygonInTheMaking.IsOppositeOfLastEdgeInPoly (secondEdgeFromCurrPoint)) {
			dirToSecondEdge = DirectionComparator::RelativeDirection::Right;
		}

		if (dirToFirstEdge == DirectionComparator::RelativeDirection::Left || dirToSecondEdge == DirectionComparator::RelativeDirection::Left) {
			//if this is the last point, we have to finish the line somehow:
			if (i == (pointsToConnect.GetSize () - 1)) {
				if (comp.CompareSecondToFirstCurve (firstEdgeFromCurrPoint, secondEdgeFromCurrPoint) == DirectionComparator::Right 
					&& polygonInTheMaking.IsPointInPolygon (GetCurve2DDataEndPosition (secondEdgeFromCurrPoint))) {
					ConnectAlongEdge (currentLastPoint, GetCurve2DDataEndPosition (secondEdgeFromCurrPoint), false);
					polygonInTheMaking.DeleteFirstEdgesUntilPoint (GetCurve2DDataEndPosition (secondEdgeFromCurrPoint));

				} else if (comp.CompareSecondToFirstCurve (firstEdgeFromCurrPoint, secondEdgeFromCurrPoint) != DirectionComparator::Right 
					&& polygonInTheMaking.IsPointInPolygon (GetCurve2DDataEndPosition (firstEdgeFromCurrPoint))) {
					ConnectAlongEdge (currentLastPoint, GetCurve2DDataEndPosition (firstEdgeFromCurrPoint), true);
					polygonInTheMaking.DeleteFirstEdgesUntilPoint (GetCurve2DDataEndPosition (firstEdgeFromCurrPoint));

				} else {
					ConnectWithDefaultEdge (currentLastPoint, nextPointToConnect);
					DBBREAK_STR ("We could not close the line along existing edges, ask GZs if this happens!");
				}
				//else: do nothing
				currentLastPoint = nextPointToConnect;
			}
		} else if (dirToFirstEdge == DirectionComparator::RelativeDirection::OnIt && dirToSecondEdge == DirectionComparator::RelativeDirection::OnIt) {
			//connect along "righter" edge
			if (comp.CompareSecondToFirstCurve (firstEdgeFromCurrPoint, secondEdgeFromCurrPoint) == DirectionComparator::Right)
				ConnectAlongEdge (currentLastPoint, nextPointToConnect, false);
			else
				ConnectAlongEdge (currentLastPoint, nextPointToConnect, true);
			currentLastPoint = nextPointToConnect;
		} else if (dirToFirstEdge == DirectionComparator::RelativeDirection::OnIt) {
			//connect along first edge
			ConnectAlongEdge (currentLastPoint, nextPointToConnect, true);
			currentLastPoint = nextPointToConnect;
		} else if (dirToSecondEdge == DirectionComparator::RelativeDirection::OnIt) {
			//connect along second edge
			ConnectAlongEdge (currentLastPoint, nextPointToConnect, false);
			currentLastPoint = nextPointToConnect;
		} else {
			//connect with default sector
			ConnectWithDefaultEdge(currentLastPoint, nextPointToConnect);
			currentLastPoint = nextPointToConnect;
		}

	}

	polygonInTheMaking.CleanUpNewEdgesIfUglyConcave (EdgeUserData ());
	return polygonInTheMaking.GetPolygon ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void PolygonalHullCreator<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConnectAlongEdge (HashableCoord& firstPoint, Point2D lastPoint, bool firstEdge)
{
	GS::HashTable <HashableCoord, GS::Pair<Curve2DData, EdgeUserData>> edgesWithData = firstEdge ? firstEdges : secondEdges;
	Geometry::Curve2DData curve;

	switch (edgesWithData.Get (firstPoint).first.type) {
		case CURVE2D_GenArc:
		{
			GenArc origArc = edgesWithData.Get (firstPoint).first.genArc;
			GenArc newArc = GenArc::CreateCircleArc (origArc.GetOrigo (), firstPoint, lastPoint, origArc.IsReflected ()); //only circle, beacuse the polygon cannot handle ellipse!
			InitCurve2DData (&curve, newArc);
			break;
		}
		case CURVE2D_Sector:
		default:
		{
			Sector sector (firstPoint, lastPoint);
			InitCurve2DData (&curve, sector, Geometry::Curve2DDataType::CURVE2D_Sector);
			break;
		}
	}

	polygonInTheMaking.AddVertexWithNextEdge (firstPoint, vertexUserDatas.Get (firstPoint), curve, edgesWithData.Get (firstPoint).second);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void PolygonalHullCreator<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConnectWithDefaultEdge (HashableCoord& startPoint, HashableCoord& endPoint)
{
	struct CrossedArc {
		GenArc arc;
		EdgeUserData userData;
		Point2D crossPoint;

		CrossedArc (GenArc _arc, EdgeUserData _userData, Point2D _crossPoint) : arc (_arc), userData (_userData), crossPoint (_crossPoint) {};
	};

	//look for arcs that pop out at the beginning of the line
	DirectionComparator compFromStartPoint (startPoint, ConvertToUnitVector (m_origo - startPoint, m_generalForwardDir));
	GS::Array<CrossedArc> crossingArcsFromStartPoint;

	GS::Pair <Point2D, VertexUserData> startOfNewEdge = GS::NewPair (startPoint, vertexUserDatas.Get (startPoint));
	GS::Array <Point2D> innerCrossPoints;

	if (firstEdges.Get (startPoint).first.type == CURVE2D_GenArc) {
		DirectionComparator::RelativeDirection side = compFromStartPoint.WhichSideOfArc (endPoint, firstEdges.Get (startPoint).first.genArc, &innerCrossPoints);
		if (side == DirectionComparator::RelativeDirection::Right && innerCrossPoints.GetSize () > 0)
			crossingArcsFromStartPoint.Push (CrossedArc (firstEdges.Get (startPoint).first.genArc, firstEdges.Get (startPoint).second, innerCrossPoints[0]));
	}
	if (secondEdges.Get (startPoint).first.type == CURVE2D_GenArc) {
		DirectionComparator::RelativeDirection side = compFromStartPoint.WhichSideOfArc (endPoint, secondEdges.Get (startPoint).first.genArc, &innerCrossPoints);
		if (side == DirectionComparator::RelativeDirection::Right && innerCrossPoints.GetSize () > 0)
			crossingArcsFromStartPoint.Push (CrossedArc (secondEdges.Get (startPoint).first.genArc, secondEdges.Get (startPoint).second, innerCrossPoints[0]));
	}

	if (crossingArcsFromStartPoint.GetSize () > 0) {
		GS::Sort (crossingArcsFromStartPoint.Begin (), crossingArcsFromStartPoint.End (), [&startPoint](CrossedArc arc1, CrossedArc arc2)
		{return (arc1.crossPoint - startPoint).GetLength () > (arc2.crossPoint - startPoint).GetLength (); });
	
		DrawCurvedEdgeAlongArc (startOfNewEdge.first, startOfNewEdge.second, crossingArcsFromStartPoint[0].crossPoint, crossingArcsFromStartPoint[0].arc.GetOrigo (), 
			crossingArcsFromStartPoint[0].arc.IsReflected (), crossingArcsFromStartPoint[0].userData);

		startOfNewEdge = GS::NewPair (crossingArcsFromStartPoint[0].crossPoint, VertexUserData ());
	}



	//look for arcs that pop out at the end of the straight edge
	DirectionComparator compFromEndPoint (endPoint, ConvertToUnitVector (m_origo - endPoint, m_generalForwardDir));
	GS::Array<CrossedArc> crossingArcsFromEndPoint;
	GS::Pair <Point2D, VertexUserData> endOfNewEdge = GS::NewPair (endPoint, vertexUserDatas.Get (endPoint));

	if (firstEdges.Get (endPoint).first.type == CURVE2D_GenArc) {
		DirectionComparator::RelativeDirection side = compFromEndPoint.WhichSideOfArc (startPoint, firstEdges.Get (endPoint).first.genArc, &innerCrossPoints); //use startOfNewEdge instead of startPoint??
		if (side == DirectionComparator::RelativeDirection::Left && innerCrossPoints.GetSize () > 0) {
			crossingArcsFromEndPoint.Push (CrossedArc (firstEdges.Get (endPoint).first.genArc, firstEdges.Get (endPoint).second, innerCrossPoints[0]));
		}
	}
	if (secondEdges.Get (endPoint).first.type == CURVE2D_GenArc) {
		DirectionComparator::RelativeDirection side = compFromEndPoint.WhichSideOfArc (startPoint, secondEdges.Get (endPoint).first.genArc, &innerCrossPoints);
		if (side == DirectionComparator::RelativeDirection::Left && innerCrossPoints.GetSize () > 0) {
			crossingArcsFromEndPoint.Push (CrossedArc (secondEdges.Get (endPoint).first.genArc, secondEdges.Get (startPoint).second, innerCrossPoints[0]));
		}
	}

	if (crossingArcsFromEndPoint.GetSize () > 0) {
		GS::Sort (crossingArcsFromEndPoint.Begin (), crossingArcsFromEndPoint.End (), [&endPoint](CrossedArc arc1, CrossedArc arc2)
		{return (arc1.crossPoint - endPoint).GetLength () > (arc2.crossPoint - endPoint).GetLength (); });

		endOfNewEdge = GS::NewPair (crossingArcsFromEndPoint[0].crossPoint, VertexUserData ());
	}


	//draw the straight edge
	Sector sector (startOfNewEdge.first, endOfNewEdge.first);
	Curve2DData curve;
	InitCurve2DData (&curve, sector, Geometry::Curve2DDataType::CURVE2D_Sector);
	polygonInTheMaking.AddVertexWithNextEdge (startOfNewEdge.first, startOfNewEdge.second, curve, EdgeUserData ());

	//draw the last curved edge, if necessary
	if (crossingArcsFromEndPoint.GetSize () > 0) {
		DrawCurvedEdgeAlongArc (endOfNewEdge.first, endOfNewEdge.second, endPoint, crossingArcsFromEndPoint[0].arc.GetOrigo (), !crossingArcsFromEndPoint[0].arc.IsReflected (), crossingArcsFromEndPoint[0].userData);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void PolygonalHullCreator<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::DrawCurvedEdgeAlongArc (const Point2D startPoint, const VertexUserData startPointUserData, const Point2D endPoint, const Point2D arcOrigo, const bool isArcReflected, const EdgeUserData edgeData)
{
	Curve2DData newArcAsCurve;
	GenArc newArc = GenArc::CreateCircleArc (arcOrigo, startPoint, endPoint, isArcReflected);
	InitCurve2DData (&newArcAsCurve, newArc);

	polygonInTheMaking.AddVertexWithNextEdge (startPoint, startPointUserData, newArcAsCurve, edgeData);
}

} //namespace Geometry
#endif