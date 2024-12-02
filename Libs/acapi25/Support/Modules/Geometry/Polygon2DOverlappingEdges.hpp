#ifndef GEOMETRY_POLYGON2DOVERLAPPINGEDGES_HPP
#define GEOMETRY_POLYGON2DOVERLAPPINGEDGES_HPP

#pragma once

#include "Array.hpp"
#include "SkipMap.hpp"

#include "CoordinateSystem2D.hpp"
#include "Line2D.hpp"
#include "Point2DData.h"
#include "Poly2DTypes.hpp"
#include "Polygon2DOverlappingEdgeResult.hpp"
#include "Sector2DData.h"
#include "QuadTree.hpp"

namespace Geometry {

template <class MultiPolygonType>
class OverlappingSectorsAndArcsFinder {

private:
	const MultiPolygonType			polys;

public:

	OverlappingSectorsAndArcsFinder (const MultiPolygonType& p) :
		polys(p)
	{
	}

	void  GetOverlapsSectorsAndArcs (GS::Array<SectorOfTwoPolys>&	commonSectors,
									 GS::Array<SectorOfAPoly>&		otherSectors,
									 GS::Array<ArcOfTwoPolys>&		commonArcs,
									 GS::Array<ArcOfAPoly>&			otherArcs) const
	{
		GS::Array<GS::SkipMap<UIndex, Polygon2DOverlappingEdgeResults>> edgeResults;
		if (DBERROR (GetResult (edgeResults) != NoError))
			return;

		GS::Array<SectorOfAPoly>	commonSectorCandidates;
		GS::Array<ArcOfAPoly>		commonArcCandidates;

		edgeResults.Enumerate ([&](const GS::SkipMap<UIndex, Polygon2DOverlappingEdgeResults>& singlePolyResult) -> void {
			singlePolyResult.EnumerateValues ([&] (const Polygon2DOverlappingEdgeResults& polyEdges) -> void {
				 polyEdges.Enumerate ([&](const IOverlappingEdgeResult* singleEdgeResult) -> void {
					if (dynamic_cast<const OverlappingSectorResult*>(singleEdgeResult) != nullptr) {
						const OverlappingSectorResult* overlappingSector = static_cast<const OverlappingSectorResult*>(singleEdgeResult);
						HandleOverlappingEdgeCandidate<Sector> (overlappingSector->GetItem (),
																overlappingSector->IsItOverlapping (),
																[](const Sector& edge1, const Sector& edge2) -> bool {
																	return IsNear (edge1.c1, edge2.c1) && IsNear (edge1.c2, edge2.c2);
																},
																commonSectorCandidates,
																commonSectors,
																otherSectors);
					} else {
						const OverlappingArcResult* overlappingArc = static_cast<const OverlappingArcResult*>(singleEdgeResult);
						HandleOverlappingEdgeCandidate<GenArc> (overlappingArc->GetItem (),
																overlappingArc->IsItOverlapping (),
																[](const GenArc& edge1, const GenArc& edge2) -> bool {
																	return edge1.IsEqual (edge2);
																},
																commonArcCandidates,
																commonArcs,
																otherArcs);
					}
				});
			});
		});
	}



	GSErrCode  GetResult (GS::Array<GS::SkipMap<UIndex, Polygon2DOverlappingEdgeResults>>& results) const
	{
		USize numOfPolys = polys.GetSize ();
		results.SetSize (numOfPolys);

		GS::Array<GS::Array<SectorOfAPoly>> sectorsOfPolys;
		sectorsOfPolys.SetSize (numOfPolys);
		GS::Array<GS::Array<ArcOfAPoly>> arcsOfPolys;
		arcsOfPolys.SetSize (numOfPolys);

		QuadTree::QuadTree<UIndex> quadTreeForPolys;
		for (UIndex polyIdx = 0; polyIdx < numOfPolys; ++polyIdx) {
			quadTreeForPolys.Insert (polys[polyIdx].GetBoundBox (), polyIdx);
		}

		for (UIndex polyIdx1 = 0; polyIdx1 < numOfPolys; ++polyIdx1) {

			GS::Array<UIndex> relevantPolys = quadTreeForPolys.Enumerate (polys[polyIdx1].GetBoundBox ());

			if (relevantPolys.IsEmpty ())
				continue;

			CollectSectorsAndArcsOfPolys (polys[polyIdx1], polyIdx1, sectorsOfPolys[polyIdx1], arcsOfPolys[polyIdx1]);

			GS::Array<GS::Array<SectorOfAPoly>> sectors;
			GS::Array<GS::Array<ArcOfAPoly>> arcs;
			sectors.SetSize (polys[polyIdx1].GetEdgeNum ());
			arcs.SetSize (polys[polyIdx1].GetEdgeNum ());

			for (UIndex i = 0; i < relevantPolys.GetSize (); ++i) {

				UIndex polyIdx2 = relevantPolys[i];

				if (polyIdx2 == polyIdx1)
					continue;

				CollectSectorsAndArcsOfPolys (polys[polyIdx2], polyIdx2, sectorsOfPolys[polyIdx2], arcsOfPolys[polyIdx2]);

				CollectOverlappingEdges (sectors, sectorsOfPolys[polyIdx1], sectorsOfPolys[polyIdx2]);

				CollectOverlappingEdges (arcs, arcsOfPolys[polyIdx1], arcsOfPolys[polyIdx2]);
			}

			for (auto edgeIt = polys[polyIdx1].EnumerateEdge (); edgeIt != nullptr; ++edgeIt) {
				UIndex edgeIdx = EdgeIdxInPolyToArrayIdx (edgeIt->GetIndex ());

				if (!sectors[edgeIdx].IsEmpty () || !arcs[edgeIdx].IsEmpty ()) {
					results[polyIdx1].Add (edgeIdx, Polygon2DOverlappingEdgeResults ());
				}
			}


			for (auto edgeIt = polys[polyIdx1].EnumerateEdge (); edgeIt != nullptr; ++edgeIt) {

				Sector sect;
				GenArc arc;

				UIndex edgeIdx = EdgeIdxInPolyToArrayIdx (edgeIt->GetIndex ());

				edgeIt->GetSector (sect, arc);
				if (!sectors[edgeIdx].IsEmpty ()) {
					GetOverlapOfCollinearSectors (SectorOfAPoly (sect, polyIdx1, edgeIdx, IsOrientationReversed (sect)), sectors[edgeIdx], results);
				} else if (!arcs[edgeIdx].IsEmpty ()) {
					GetOverlapOfConcyclicArcs (ArcOfAPoly (arc, polyIdx1, edgeIdx, arc.IsReflected ()), arcs[edgeIdx], results);
				}
			}
		}

		GSErrCode errorCode = NoError;
		for (auto& result : results) {
			result.EnumerateValues ([&] (Polygon2DOverlappingEdgeResults& edgeResults) {
				GSErrCode err = edgeResults.OrderEdgeParts (polys);
				if (DBERROR (err != NoError))
					errorCode = Error;
			});
		}	

		return errorCode;
	}

private:

	static UIndex EdgeIdxInPolyToArrayIdx (UIndex idx)
	{
		return idx - 1;
	}

	template <class PolygonType>
	static void CollectSectorsAndArcsOfPolys (const PolygonType&			poly,
											  const UIndex					polyIdx,
											  GS::Array<SectorOfAPoly>&		sectorsOfPoly,
											  GS::Array<ArcOfAPoly>&		arcsOfPoly)
	{
		if (!(sectorsOfPoly.IsEmpty () && arcsOfPoly.IsEmpty ()))
			return;

		for (auto edgeIt = poly.EnumerateEdge (); edgeIt != nullptr; ++edgeIt) {
			if (IsNearZero (edgeIt->GetLength ()))
				continue;
			Sector sect;
			GenArc arc;
			if (edgeIt->GetSector (sect, arc)) {
				arcsOfPoly.PushNew (ArcOfAPoly (arc, polyIdx, EdgeIdxInPolyToArrayIdx (edgeIt->GetIndex ()), arc.IsReflected ()));
			} else {
				sectorsOfPoly.PushNew (SectorOfAPoly (sect, polyIdx, EdgeIdxInPolyToArrayIdx (edgeIt->GetIndex ()), IsOrientationReversed (sect)));
			}
		}
	}


	template <class EdgeType>
	static void CollectOverlappingEdges (GS::Array<GS::Array<EdgeOfAPoly<EdgeType>>>&	edges,
										 const GS::Array<EdgeOfAPoly<EdgeType>>&		edgesOfPoly1,
										  const GS::Array<EdgeOfAPoly<EdgeType>>&		edgesOfPoly2)
	{
		for (const auto& edge1 : edgesOfPoly1) {
			for (const auto& edge2 : edgesOfPoly2) {
				if (DoTheyOverlap (edge1, edge2))
					edges[edge1.edgeIdx].Push (edge2);
			}
		}
	}

	static GS::Array<SectorOfAPoly>	SortSectorsOnSameLineByStartPoint (const Sector& sector0, bool isOrientationReversed, const GS::Array<SectorOfAPoly>& sectors)
	{
		if (sectors.GetSize () <= 1)
			return sectors;

		try {
			Vector xAxis = SectorVector (sector0);
			if (isOrientationReversed)
				xAxis *= -1.0;

			const OrthonormalizedCoordinateSystem2D coordSysOfSector = OrthonormalizedCoordinateSystem2D::Create (sector0.c1, xAxis);
			const OrthogonalTransformation2D globalToLocal = coordSysOfSector.GetGlobalToLocalTrafo ();
	
			GS::Array<GS::Pair<SectorOfAPoly, UIndex>> sortedSectorsOnXAxis (sectors.GetSize ());
			for (UIndex i = 0; i < sectors.GetSize (); ++i) {
				sortedSectorsOnXAxis.Push ({ sectors[i], i });
				sortedSectorsOnXAxis[i].first.item = sortedSectorsOnXAxis[i].first.item.Transform (globalToLocal);
			}

			GS::Sort (sortedSectorsOnXAxis.Begin (), sortedSectorsOnXAxis.End (), [] (const GS::Pair<SectorOfAPoly, UIndex>& s1, const GS::Pair<SectorOfAPoly, UIndex>& s2) -> bool { 
				return s1.first.item.c1.x < s2.first.item.c1.x; 
			});

			GS::Array<SectorOfAPoly> sortedSectors (sortedSectorsOnXAxis.GetSize ());
			for (UIndex i = 0; i < sortedSectorsOnXAxis.GetSize (); ++i)
				sortedSectors.Push (sectors[sortedSectorsOnXAxis[i].second]);
			return sortedSectors;
		} catch (...) {
			DBBREAK ();
			return {};
		}
	}
	
	static void GetOverlapOfCollinearSectors (const SectorOfAPoly&												sect0,
											  const GS::Array<SectorOfAPoly>&									sectorsParam,
											  GS::Array<GS::SkipMap<UIndex, Polygon2DOverlappingEdgeResults>>&	edgeResults)
	{
		const bool isOrientationReversed = IsOrientationReversed (sect0.item);
		const GS::Array<SectorOfAPoly> sectors = SortSectorsOnSameLineByStartPoint (sect0.item, isOrientationReversed, sectorsParam);
		if (DBERROR (sectors.IsEmpty ()))
			return;

		if (IsLessByXY (GetMinEndC (sect0.item), GetMinEndC (sectors[0].item))) {
			SectorOfAPoly s (Sector (GetMinEndC (sect0.item), GetMinEndC (sectors[0].item)), sect0.polyIdx, sect0.edgeIdx, isOrientationReversed);
			edgeResults[sect0.polyIdx][sect0.edgeIdx].AddResult (s, false);
		}

		Coord cMin = MAXByXY (GetMinEndC (sectors[0].item), GetMinEndC (sect0.item));
		Coord cMax = GetMaxEndC (sectors[0].item), cMax2 = cMin;
		UIndex maxIdx = 0;

		UIndex i = 0;
		while (i < sectors.GetSize ()) {
			while (i < sectors.GetSize () && IsLessOrNearByXY (GetMinEndC (sectors[i].item), cMax)) {
				if (IsGreaterByXY (GetMaxEndC (sectors[i].item), cMax)) {
					cMax2 = cMax;
					cMax = GetMaxEndC (sectors[i].item);
					maxIdx = i;
				} else if (IsNear (GetMaxEndC (sectors[i].item), cMax)) {
					maxIdx = i;
				}
				++i;
			}

			if (IsGreaterByXY (cMax, GetMaxEndC (sect0.item))) {
			
				SectorOfAPoly s (Sector (cMax2, GetMaxEndC (sect0.item)), sect0.polyIdx, sect0.edgeIdx, isOrientationReversed);
					
				bool isOrientationReversed2 = IsOrientationReversed (sectors[maxIdx].item);
				SectorOfAPoly s2 (Sector (cMax2, GetMaxEndC (sect0.item)), sectors[maxIdx].polyIdx, sectors[maxIdx].edgeIdx, isOrientationReversed2);

				bool firstVisible = sect0.polyIdx < sectors[maxIdx].polyIdx;
			
				edgeResults[sect0.polyIdx][sect0.edgeIdx].AddResult (s, true, firstVisible);

				if (!edgeResults[sectors[maxIdx].polyIdx].ContainsKey (sectors[maxIdx].edgeIdx))
					edgeResults[sectors[maxIdx].polyIdx].Add (sectors[maxIdx].edgeIdx, Polygon2DOverlappingEdgeResults ());
				edgeResults[sectors[maxIdx].polyIdx][sectors[maxIdx].edgeIdx].AddResult (s2, true, !firstVisible);
				break;
			}

			if (IsNear (cMax, GetMaxEndC (sect0.item))) {
				if (sect0.polyIdx < sectors[maxIdx].polyIdx) {
					SectorOfAPoly s (Sector (cMax2, GetMaxEndC (sect0.item)), sect0.polyIdx, sect0.edgeIdx, isOrientationReversed);

					bool isOrientationReversed2 = IsOrientationReversed (sectors[maxIdx].item);
					SectorOfAPoly s2 (Sector (cMax2, GetMaxEndC (sect0.item)), sectors[maxIdx].polyIdx, sectors[maxIdx].edgeIdx, isOrientationReversed2);
					bool firstVisible = sect0.polyIdx < sectors[maxIdx].polyIdx;

					edgeResults[sect0.polyIdx][sect0.edgeIdx].AddResult (s, true, firstVisible);

					if (!edgeResults[sectors[maxIdx].polyIdx].ContainsKey (sectors[maxIdx].edgeIdx))
						edgeResults[sectors[maxIdx].polyIdx].Add (sectors[maxIdx].edgeIdx, Polygon2DOverlappingEdgeResults ());

					edgeResults[sectors[maxIdx].polyIdx][sectors[maxIdx].edgeIdx].AddResult (s2, true, !firstVisible);
				}
				break;
			}

			if (i != sectors.GetSize ()) {			//if we got this far, cMax < sect0.GetMaxEnd()
				SectorOfAPoly s (Sector (cMax, GetMinEndC (sectors[i].item)), sect0.polyIdx, sect0.edgeIdx, isOrientationReversed);
				edgeResults[sect0.polyIdx][sect0.edgeIdx].AddResult (s, false);
				cMin = GetMinEndC (sectors[i].item);
				cMax = GetMaxEndC (sectors[i].item);
				cMax2 = cMin;
				continue;
			} else {
				SectorOfAPoly s (Sector (cMax, GetMaxEndC (sect0.item)), sect0.polyIdx, sect0.edgeIdx, isOrientationReversed);
				edgeResults[sect0.polyIdx][sect0.edgeIdx].AddResult (s, false);
				continue;
			}
		}
	}

	static SectorOfAPoly ArcToSectorOnXAxis (const ArcOfAPoly& arc)
	{
		DBASSERT (arc.item.IsReflected () == arc.isOrientationReversed);

		double begAng = arc.item.GetBegAng ();
		double endAng = arc.item.GetEndAng ();

		if (arc.item.IsReflected ()) {
			while (endAng > begAng)
				endAng -= 2.0 * PI;
		} else {
			while (begAng > endAng)
				endAng += 2.0 * PI;
		}

		return SectorOfAPoly (Sector (Coord (begAng, 0.0), Coord (endAng, 0.0)), arc.polyIdx, arc.edgeIdx, arc.isOrientationReversed);
	}

	static SectorOfAPoly OffsetSectorOnXAxis (const SectorOfAPoly& sector, const double offset)
	{
		SectorOfAPoly result (sector);

		result.item.c1.x += offset;
		result.item.c2.x += offset;

		return result;
	}

	static ArcOfAPoly SectorOnXAxisToArc (const SectorOfAPoly& sector, const Point2D& origo, const double radius)
	{
		DBASSERT (IsNearZero (sector.item.c1.y));
		DBASSERT (IsNearZero (sector.item.c2.y));

		double begAng = NormFi02Pi (sector.item.c1.x);
		double endAng = NormFi02Pi (sector.item.c2.x);

		return ArcOfAPoly (GenArc::CreateCircleArc (origo, radius, begAng, endAng, IsOrientationReversed (sector.item)), 
							sector.polyIdx,
							sector.edgeIdx,
							sector.isOrientationReversed);			// this refers to the orientation of the original edge, not the actual
	}

	static void GetOverlapOfConcyclicArcs  (const ArcOfAPoly&												arc0,
											const GS::Array<ArcOfAPoly>&									arcs,
											GS::Array<GS::SkipMap<UIndex,Polygon2DOverlappingEdgeResults>>& edgeResults)
	{
		if (DBERROR (arcs.IsEmpty ()))
			return;

		const SectorOfAPoly sect0 = ArcToSectorOnXAxis (arc0);
		GS::Array<SectorOfAPoly> sectors (arcs.GetSize () * 3);
		{
			for (const ArcOfAPoly& arc : arcs) {
				const SectorOfAPoly sector = ArcToSectorOnXAxis (arc);
				if (DoSectorsOverlap (sect0.item, sector.item))
					sectors.Push (sector);
				const SectorOfAPoly offsettedMin2PI = OffsetSectorOnXAxis (sector, -2.0 * PI);
				if (DoSectorsOverlap (sect0.item, offsettedMin2PI.item))
					sectors.Push (offsettedMin2PI);
				const SectorOfAPoly offsettedPlus2PI = OffsetSectorOnXAxis (sector, 2.0 * PI);
				if (DoSectorsOverlap (sect0.item, offsettedPlus2PI.item))
					sectors.Push (offsettedPlus2PI);
			}
		}

		GS::Array<GS::SkipMap<UIndex,Polygon2DOverlappingEdgeResults>> edgeResultsTmp;
		{
			edgeResultsTmp.SetSize (edgeResults.GetSize ());
			edgeResultsTmp[arc0.polyIdx].Add (arc0.edgeIdx, Polygon2DOverlappingEdgeResults ());
		}

		GetOverlapOfCollinearSectors (sect0, sectors, edgeResultsTmp);

		for (UIndex polyIndex = 0; polyIndex < edgeResultsTmp.GetSize (); ++polyIndex) {
			const GS::SkipMap<UIndex, Polygon2DOverlappingEdgeResults>& singlePolyResult = edgeResultsTmp[polyIndex];
			singlePolyResult.Enumerate ([&] (const UIndex edgeIndex, const Polygon2DOverlappingEdgeResults& polyEdges) -> void {
				if (!edgeResults[polyIndex].ContainsKey (edgeIndex))
					edgeResults[polyIndex].Add (edgeIndex, Polygon2DOverlappingEdgeResults ());
				polyEdges.Enumerate ([&](const IOverlappingEdgeResult* singleEdgeResult) -> void {
					const OverlappingSectorResult* overlappingSector = static_cast<const OverlappingSectorResult*>(singleEdgeResult);
					edgeResults[polyIndex][edgeIndex].AddResult (SectorOnXAxisToArc (overlappingSector->GetItem (), arc0.item.GetOrigo (), arc0.item.GetMainAxisLength ()), 
																 overlappingSector->IsItOverlapping (),
																 overlappingSector->IsVisible ());
				});
			});
		}
	}

	static bool DoTheyOverlap (const SectorOfAPoly& edge1, const SectorOfAPoly& edge2)
	{
		return DoSectorsOverlap (edge1.item, edge2.item);
	}

	static bool DoTheyOverlap (const ArcOfAPoly& edge1, const ArcOfAPoly& edge2)
	{
		return DoArcsOverlap (edge1.item, edge2.item);
	}

	template<typename EdgeType>
	static void	HandleOverlappingEdgeCandidate (const EdgeOfAPoly<EdgeType>&			currentEdge,
												const bool								isOverlap,
												const std::function<bool (const EdgeType& edge1, const EdgeType& edge2)>& candidateMatcher,
												GS::Array<EdgeOfAPoly<EdgeType>>&		commonEdgeCandidates,
												GS::Array<EdgeOfTwoPolys<EdgeType>>&	commonEdges,
												GS::Array<EdgeOfAPoly<EdgeType>>&		otherEdges)
	{
		if (isOverlap) {
			const UIndex candidateIndex = commonEdgeCandidates.FindFirst ([&](const EdgeOfAPoly<EdgeType>& candidateEdge) -> bool {
				return candidateMatcher (candidateEdge.item, currentEdge.item);
			});
			if (candidateIndex == MaxUIndex) {
				commonEdgeCandidates.Push (currentEdge);
			} else {
				const EdgeOfAPoly<EdgeType>& cachedItem = commonEdgeCandidates[candidateIndex];
				EdgeOfTwoPolys<EdgeType> edgefTwoPolys (currentEdge.GetItem (), cachedItem.polyIdx, cachedItem.edgeIdx, currentEdge.polyIdx, currentEdge.edgeIdx, cachedItem.isOrientationReversed, currentEdge.isOrientationReversed);
				commonEdges.Push (edgefTwoPolys);
			}
		} else {
			otherEdges.Push (currentEdge);
		}
	}
};

} // namespace Geometry

#endif