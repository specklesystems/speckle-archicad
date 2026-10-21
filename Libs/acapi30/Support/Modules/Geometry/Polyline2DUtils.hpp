#ifndef GEOMETRY_POLYLINE2DUTILS_HPP
#define GEOMETRY_POLYLINE2DUTILS_HPP

#include "GenArc2DData.h"
#include "Sector2DData.h"
#include "CutElems.h"

namespace Geometry {

template<typename PolylineType>
GS::Optional<CutParam> FindCutParamOnSpecificEdge (const PolylineType& polyline, const UIndex edgeIndex, const Point2D& cutPointCoord)
{
	GS::Array<CutParam> possibleCutParams = polyline.CutPointToCutParam (cutPointCoord);
	if (possibleCutParams.IsEmpty ())
		return GS::NoValue;

	for (const CutParam& cutParam : possibleCutParams) {
		if (cutParam.edgeIndex == edgeIndex) {
			return cutParam;
		}
	}

	DBBREAK_STR ("CutPoint not found on specific edge!");
	return possibleCutParams.GetFirst ();
}

template <typename PolyType>
class PolyEdgeOverlapCalculator
{
public:
	void SetPoly (const PolyType* polyIn) { poly = polyIn; }
	virtual void SetEdgeOnPoly (const typename PolyType::ConstEdgeIterator& edge) = 0;
	virtual bool IsOverlap () = 0;
	virtual const Point2D& GetOverlapStart () = 0;
	virtual const Point2D& GetOverlapEnd () = 0;
	virtual void StoreOverlapInResults () = 0;

protected:
	const PolyType* poly;
};

template <typename PolyType>
class PolyEdgeSectorOverlapCalculator : public PolyEdgeOverlapCalculator<PolyType>
{
public:
	PolyEdgeSectorOverlapCalculator (const Sector& sec, GS::Array<Sector>& overlapResults) : sector (sec), resultCollector (overlapResults) {};

	void SetEdgeOnPoly (const typename PolyType::ConstEdgeIterator& edge) override
	{
		polyEdgeSec = this->poly->GetSector (edge);
		overlap = GS::NoValue;
	}

	bool IsOverlap () override { return polyEdgeSec.HasValue () && DoSectorsOverlap (polyEdgeSec.Get (), sector); }
	const Point2D& GetOverlapStart () override { return GetOverlapSector ().c1; }
	const Point2D& GetOverlapEnd () override { return GetOverlapSector ().c2; }
	void StoreOverlapInResults () override { resultCollector.Push (GetOverlapSector ()); }

private:
	const Sector& GetOverlapSector ()
	{
		DBASSERT (IsOverlap ());

		if (!overlap.HasValue ()) { 
			GS::Array<Sector> dummy;
			overlap = Sector ();
			CutSectorWithOtherSector (polyEdgeSec.Get (), sector, *overlap, dummy);
		}
		return overlap.Get ();
	}

	const Sector& sector;
	GS::Optional<Sector> polyEdgeSec;
	GS::Optional<Sector> overlap;
	GS::Array<Sector>& resultCollector;
};

template <typename PolyType>
class PolyEdgeArcOverlapCalculator : public PolyEdgeOverlapCalculator<PolyType>
{
public:
	PolyEdgeArcOverlapCalculator (const GenArc& cutterArc, GS::Array<GenArc>& overlapResults) : arc (cutterArc), resultCollector (overlapResults) {};

	void SetEdgeOnPoly (const typename PolyType::ConstEdgeIterator& edge) override
	{
		polyEdgeArc = this->poly->GetArc (edge);
		overlap = GS::NoValue;
	}

	bool IsOverlap () override { return polyEdgeArc.HasValue () && DoArcsOverlap (polyEdgeArc.Get (), arc); }
	const Point2D& GetOverlapStart () override { return GetOverlapArc ().GetBegC (); }
	const Point2D& GetOverlapEnd () override { return GetOverlapArc ().GetEndC (); }
	void StoreOverlapInResults () override { resultCollector.Push (GetOverlapArc ()); }

private:
	const GenArc& GetOverlapArc ()
	{
		DBASSERT (IsOverlap ());

		if (!overlap.HasValue ()) {
			GS::Array<GenArc> dummy;
			overlap = GenArc ();
			CutArcWithOtherArc (polyEdgeArc.Get (), arc, *overlap, dummy);
		}
		return overlap.Get ();
	}

	const GenArc& arc;
	GS::Optional<GenArc> polyEdgeArc;
	GS::Optional<GenArc> overlap;
	GS::Array<GenArc>& resultCollector;
};

template<typename PolylineType>
void CutPolylineAtOverlappingParts (const PolylineType& target, PolyEdgeOverlapCalculator<PolylineType>& overlapCalculator, GS::Array<PolylineType>& remainders)
{
	remainders.Clear ();

	PolylineType polyLineToProcess = target;
	bool anythingLeftToProcess = true;
	while (anythingLeftToProcess) {
		bool intersectionFound = false;
		overlapCalculator.SetPoly (&polyLineToProcess);
		UIndex edgeIndex = 0;
		for (typename PolylineType::ConstEdgeIterator edgeIt = polyLineToProcess.BeginEdge (); edgeIt != polyLineToProcess.EndEdge (); ++edgeIt) {
			++edgeIndex;
			overlapCalculator.SetEdgeOnPoly (edgeIt);

			if (overlapCalculator.IsOverlap ()) {
				const Point2D begC = overlapCalculator.GetOverlapStart ();
				const Point2D endC = overlapCalculator.GetOverlapEnd ();
				if (Geometry::IsNear (begC, endC))
					continue;
				GS::Optional<CutParam> firstRemainderEnd = FindCutParamOnSpecificEdge (polyLineToProcess, edgeIndex, begC);
				GS::Optional<CutParam> lastRemainderBeg = FindCutParamOnSpecificEdge (polyLineToProcess, edgeIndex, endC);
				if (!firstRemainderEnd.HasValue () || !lastRemainderBeg.HasValue ())
					continue;
				if (fabs (lastRemainderBeg->param - firstRemainderEnd->param) < Eps && fabs (lastRemainderBeg->param) < Eps)
					continue;
				overlapCalculator.StoreOverlapInResults ();
				PolylineType polylineRemainder1 = polyLineToProcess.CutPiece (CutParam{ 0, 1 }, *firstRemainderEnd);
				PolylineType polylineRemainder2 = polyLineToProcess.CutPiece (*lastRemainderBeg, CutParam{ 1, polyLineToProcess.GetEdgeNum () });

				if (polyLineToProcess.GetClosed () == true) {
					if (!IsPositive (polylineRemainder2.CalcLength ())) {
						polylineRemainder2 = polylineRemainder1;
					} else if (IsPositive (polylineRemainder1.CalcLength ())) {
						polylineRemainder2.Append (polylineRemainder1);
					}
					polylineRemainder1.Clear ();
				}

				if (IsPositive (polylineRemainder1.CalcLength ())) {
					remainders.Push (polylineRemainder1);
				}
				polyLineToProcess = polylineRemainder2;
				intersectionFound = true;
				break;
			}
		}

		if (!intersectionFound) {
			if (IsPositive (polyLineToProcess.CalcLength ())) {
				remainders.Push (polyLineToProcess);
			}
			anythingLeftToProcess = false;
		}
	}
}

template<typename PolylineType>
void CutPolylineWhereArcOverlaps (const PolylineType& target, const GenArc& cutter, GS::Array<GenArc>& intersection, GS::Array<PolylineType>& remainders)
{
	intersection.Clear ();
	remainders.Clear ();
	PolyEdgeArcOverlapCalculator<PolylineType> overlapCalculator (cutter, intersection);

	CutPolylineAtOverlappingParts (target, overlapCalculator, remainders);
}

template<typename PolylineType>
void CutPolylineWhereSectorOverlaps (const PolylineType& target, const Sector& cutter, GS::Array<Sector>& intersection, GS::Array<PolylineType>& remainders)
{

	intersection.Clear ();
	remainders.Clear ();
	PolyEdgeSectorOverlapCalculator<PolylineType> overlapCalculator (cutter, intersection);

	CutPolylineAtOverlappingParts (target, overlapCalculator, remainders);
}

}

#endif