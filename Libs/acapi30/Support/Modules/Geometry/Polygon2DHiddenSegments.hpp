#ifndef GEOMETRY_POLYGON2DHIDDENSEGMENTS_HPP
#define GEOMETRY_POLYGON2DHIDDENSEGMENTS_HPP

#pragma once

#include "GeometricDefinitions.h"
#include "Angle.hpp"
#include "Point2D.hpp"
#include "GenArc2DData.h"
#include "Sector2DData.h"
#include "Sector3DData.h"
#include "Point2DData.h"
#include "Poly2DTypes.hpp"

#include "QuadTree.hpp"


namespace Geometry {
 
template<class T>
struct ItemWithHeight {
	T item;
	double z;

	constexpr ItemWithHeight (const T& item, double z = 0.0)
		: item { item }, z { z }
	{}
};

template<typename T>
struct ItemWithHeightAndIdx {
	T item;
	UIndex idx;
	double z;

	constexpr ItemWithHeightAndIdx (const T& item, UIndex idx = 0, double z = 0.0)
		: item { item }, idx { idx }, z { z }
	{}
};

template<>
struct ItemWithHeightAndIdx<Sector3D> {
	Sector3D item;
	UIndex idx;
	double z;

	constexpr ItemWithHeightAndIdx (const Sector3D& s, UIndex idx)
		: item { s }, idx { idx }, z { GS::Min (s.c1.z, s.c2.z) }
	{}
};

template<class T>
struct ItemWithIdx {
	T item;
	UIndex idx;
	bool isOrientationReversed;

	constexpr ItemWithIdx (const T& item, UIndex idx = 0, bool isOrientationReversed = false)
		: item { item }, idx { idx }, isOrientationReversed { isOrientationReversed }
	{}
};

//az (InputType, OutputType) par lehet: (Sector, Sector), (Sector3D, Sector), (GenArc, GenArc)
template <class PolygonType, class InputSegmentType, class OutputSegmentType>
class VisiblePartsFinder {

private:
	GS::Array<ItemWithHeight<PolygonType>> polys;
	GS::Array<ItemWithHeightAndIdx<InputSegmentType>> inputItems;

public:
	VisiblePartsFinder(const GS::Array<ItemWithHeight<PolygonType>>& p,
						const GS::Array<ItemWithHeightAndIdx<InputSegmentType>>& i) :
		polys (p),
		inputItems(i)
	{
		GS::Sort (polys.BeginFast (), polys.EndFast (), [](const ItemWithHeight<PolygonType>& poly1, const ItemWithHeight<PolygonType>& poly2) -> bool {return poly1.z > poly2.z; });
		GS::Sort (inputItems.BeginFast (), inputItems.EndFast (), [](const ItemWithHeightAndIdx<InputSegmentType>& s1, const ItemWithHeightAndIdx<InputSegmentType>& s2) -> bool {return s1.z > s2.z; });
	}

	void GetVisibleParts (
		GS::Array<ItemWithIdx<OutputSegmentType>>& visible,
		GS::Array<ItemWithIdx<OutputSegmentType>>& hidden)
	{

		if (inputItems.IsEmpty())
			return;

		if (polys.IsEmpty()) {
			PutEverythingIntoVisible(visible, inputItems);
			return;
		}

		visible.SetCapacity(visible.GetCapacity() + inputItems.GetSize());
		hidden.SetCapacity(visible.GetCapacity() + inputItems.GetSize());

		QuadTree::QuadTree<UIndex> quadTreeOfPolys;
		UIndex endIdx = 0;

		for (UIndex itemIdx = 0; itemIdx < inputItems.GetSize(); ++itemIdx) {

			OutputSegmentType projectedItem;
			ProjectTo2D(inputItems[itemIdx].item, projectedItem);
			
			if (IsTooShort(projectedItem))
				continue;

			bool isOrientationReversed = IsOrientationReversed(projectedItem);
			UIndex idx = inputItems[itemIdx].idx;

			while (endIdx < polys.GetSize() && IsGreaterOrNear(polys[endIdx].z, inputItems[itemIdx].z)) {
				quadTreeOfPolys.Insert(polys[endIdx].item.GetBoundBox(), endIdx);
				++endIdx;
			}

			GS::Array<UIndex> relevantPolys = GetRelevantPolys(quadTreeOfPolys, projectedItem);

			if (relevantPolys.IsEmpty()) {
				visible.PushNew(projectedItem, idx, false);
				continue;
			}

			GS::Array<OutputSegmentType> hiddenItems;
			for (UIndex i = 0; i < relevantPolys.GetSize(); ++i) {
				UIndex polyIdx = relevantPolys[i];
				CutElemThis(polys[polyIdx], inputItems[itemIdx].item, hiddenItems);
			}

			if (hiddenItems.IsEmpty()) {
				visible.PushNew(projectedItem, idx, false);
				continue;
			}

			GetUnionOfIntervalsAndGetRemainingParts(projectedItem, hiddenItems, visible, hidden, idx, isOrientationReversed);
		}
	}

private:

	static void GetUnionOfIntervalsAndGetRemainingParts (const Sector& thisSect, GS::Array<Sector>& hiddenSectors, GS::Array<ItemWithIdx<Sector>>& visible, GS::Array<ItemWithIdx<Sector>>& hidden, const  UIndex idx, const  bool isOrientationReversed)
	{
		GS::Sort (hiddenSectors.BeginFast (), hiddenSectors.EndFast (), [](const Sector& sect1, const Sector& sect2) -> bool
		{ return IsLessByXY(GetMinEndC(sect1), GetMinEndC(sect2)) || (IsNear(GetMinEndC(sect1), GetMinEndC(sect2)) && IsLessByXY(GetMaxEndC(sect1), GetMaxEndC(sect2))); });
		Coord begC = GetMinEndC(hiddenSectors[0]), endC = GetMaxEndC(hiddenSectors[0]);
		if (IsGreaterByXY(begC, GetMinEndC(thisSect))) {
			visible.PushNew(Sector(GetMinEndC(thisSect), begC), idx, isOrientationReversed);
		}
		UIndex i = 1;
		while (i < hiddenSectors.GetSize()) {
			if (IsLessOrNearByXY(GetMinEndC(hiddenSectors[i]), endC) && IsGreaterByXY(GetMaxEndC(hiddenSectors[i]), endC)) {
				endC = GetMaxEndC(hiddenSectors[i]);
			}
			if (IsGreaterByXY(GetMinEndC(hiddenSectors[i]), endC)) {
				hidden.PushNew(Sector(begC, endC), idx, isOrientationReversed);
				visible.PushNew(Sector(endC, GetMinEndC(hiddenSectors[i])), idx, isOrientationReversed);
				begC = GetMinEndC(hiddenSectors[i]);
				endC = GetMaxEndC(hiddenSectors[i]);
			}
			++i;
		}
		hidden.PushNew(Sector(begC, endC), idx, isOrientationReversed);
		if (IsLessByXY(endC, GetMaxEndC(thisSect))) {
			visible.PushNew(Sector(endC, GetMaxEndC(thisSect)), idx, isOrientationReversed);
		}
	}

	static void GetUnionOfIntervalsAndGetRemainingParts (const GenArc& thisArc, GS::Array<GenArc>& hiddenArcs, GS::Array<ItemWithIdx<GenArc>>& visible, GS::Array<ItemWithIdx<GenArc>>& hidden, const  UIndex idx, const  bool isOrientationReversed)
	{
		double start = GetMinEndAng(thisArc);

		GS::Sort (hiddenArcs.BeginFast (), hiddenArcs.EndFast (), [&start](const GenArc& arc1, const GenArc& arc2) -> bool {
			return (IsStrictlyBetweenAng(GetMinEndAng(arc1), start, GetMinEndAng(arc2)) || (IsNear(GetMinEndAng(arc1), start) && !IsNear(GetMinEndAng(arc2), start))) ||
				(IsNear(GetMinEndAng(arc1), GetMinEndAng(arc2)) && IsStrictlyBetweenAng(GetMaxEndAng(arc1), GetMinEndAng(arc1), GetMaxEndAng(arc2)));
		});

		//the endpoints of the arcs in hiddenArcs lie on thisArc
		Coord begC = GetMinEndC(hiddenArcs[0]), endC = GetMaxEndC(hiddenArcs[0]);
		double begAng = GetMinEndAng(hiddenArcs[0]), endAng = GetMaxEndAng(hiddenArcs[0]);
		if (IsNotNear(begAng, start)) {
			GenArc newItem;
			newItem.SetToCircleArc(thisArc.GetOrigo(), GetMinEndC(thisArc), begC, false);
			visible.PushNew(newItem, idx, isOrientationReversed);
		}
		UIndex i = 1;
		while (i < hiddenArcs.GetSize()) {
			if (IsBetweenAng(GetMinEndAng(hiddenArcs[i]), start, endAng) && IsBetweenAng(endAng, start, GetMaxEndAng(hiddenArcs[i]))) {
				endC = GetMaxEndC(hiddenArcs[i]);
				endAng = GetMaxEndAng(hiddenArcs[i]);
			}
			//if (IsGreater(GetMinEndAng(hiddenArcs[i]), endAng)) { 
			// Itt azt akarjuk eldonteni, hogy hiddenArcs[i] es az eddigiek veget jelzo endAng kozott van-e hezag.
			// A szogeknel a ciklikussagot figyelni kell, tehat a Real::IsGreater () alkalmatlan erre.
			// Elvileg az Angle::IsGreater () jo lehetne, ha az ugy lenne megirva, de az sem figyeli.

			if (SubAngle (GetMinEndAng(hiddenArcs[i]), endAng) < PI) {
				GenArc newItem;
				newItem.SetToCircleArc(thisArc.GetOrigo(), begC, endC, false);
				hidden.PushNew(newItem, idx, isOrientationReversed);
				newItem.SetToCircleArc(thisArc.GetOrigo(), endC, GetMinEndC(hiddenArcs[i]), false);
				visible.PushNew(newItem, idx, isOrientationReversed);
				begC = GetMinEndC(hiddenArcs[i]);
				endC = GetMaxEndC(hiddenArcs[i]);
				begAng = GetMinEndAng(hiddenArcs[i]);
				endAng = GetMaxEndAng(hiddenArcs[i]);
			}
			++i;
		}
		GenArc newItem;
		newItem.SetToCircleArc(thisArc.GetOrigo(), begC, endC, false);
		hidden.PushNew(newItem, idx, isOrientationReversed);
		if (IsNotNear(endAng, GetMaxEndAng(thisArc))) {
			GenArc newItem;
			newItem.SetToCircleArc(thisArc.GetOrigo(), endC, GetMaxEndC(thisArc), false);
			visible.PushNew(newItem, idx, isOrientationReversed);
		}
	}

	template<typename ProjectedSegmentType, typename SegmentType>
	static void PutEverythingIntoVisible (GS::Array<ItemWithIdx<ProjectedSegmentType>>& visible, const  GS::Array<ItemWithHeightAndIdx<SegmentType>>& items)
	{
		for (UIndex i = 0; i < items.GetSize(); ++i) {
			visible.PushNew(items[i].item, items[i].idx, false);
		}
	}

	static void PutEverythingIntoVisible(GS::Array<ItemWithIdx<Sector>>& visible, const  GS::Array<ItemWithHeightAndIdx<Sector3D>>& sectors)
	{
		for (UIndex sectIdx = 0; sectIdx < sectors.GetSize(); ++sectIdx) {
			Sector sect2D = Sector(Coord(sectors[sectIdx].item.c1.x, sectors[sectIdx].item.c1.y), Coord(sectors[sectIdx].item.c2.x, sectors[sectIdx].item.c2.y));
			if (IsTooShort(sect2D))
				continue;
			bool isOrientationReversed = IsOrientationReversed(sect2D);
			visible.PushNew(Sector(GetMinEndC(sect2D), GetMaxEndC(sect2D)), sectIdx, isOrientationReversed);
		}
	}

	template<typename ProjectedSegmentType, typename SegmentType>
	static void ProjectTo2D (const SegmentType& s, ProjectedSegmentType& projection)
	{
		projection = s;
	}

	static void ProjectTo2D (const Sector3D& sect, Sector& projection)
	{
		projection = Sector(Coord(sect.c1.x, sect.c1.y), Coord(sect.c2.x, sect.c2.y));
	}

	static bool IsTooShort (const Sector& sect)
	{
		return sect.GetLength() < Eps;
	}

	static bool IsTooShort (const GenArc& arc)
	{
		return fabs(arc.GetArcAngle()) < RadEps;
	}

	template<typename ProjectedSegmentType, typename SegmentType>
	static void CutElemThis (const ItemWithHeight<PolygonType>& poly, const  SegmentType& s, GS::Array<ProjectedSegmentType>& hiddenItems)
	{
		hiddenItems.Append(poly.item.CutElem(s, Boundary_Closed));
	}

	static void CutElemThis (const ItemWithHeight<PolygonType>& poly, const  Sector3D& sect, GS::Array<Sector>& hiddenSectors)
	{
		Sector projectedSect;
		ProjectTo2D(sect, projectedSect);
		if (IsLess (poly.z, sect.c1.z)|| IsLess (poly.z, sect.c2.z) ){
			double lambda = (poly.z - sect.c2.z) / (sect.c1.z - sect.c2.z);
			Coord intersectionPoint = Coord(lambda*(sect.c1.x) + (1 - lambda)*(sect.c2.x), lambda*(sect.c1.y) + (1 - lambda)*(sect.c2.y));
			projectedSect = (sect.c1.z < sect.c2.z) ? Sector(projectedSect.c1, intersectionPoint) : Sector(intersectionPoint, projectedSect.c2);
		}
		hiddenSectors.Append(poly.item.CutElem(projectedSect, Boundary_Closed));
	}

	static bool IsOrientationReversed (const GenArc& arc)
	{
		return arc.IsReflected();
	}

	static bool IsOrientationReversed (const Sector& sect)
	{
		return IsGreaterByXY(sect.c1, sect.c2);
	}

	static GS::Array<UIndex> GetRelevantPolys (const QuadTree::QuadTree<UIndex>& quadTreeOfPolys, const Sector& sect)
	{
		return quadTreeOfPolys.Enumerate(SectorBox(&sect));
	}

	static GS::Array<UIndex> GetRelevantPolys (const QuadTree::QuadTree<UIndex>& quadTreeOfPolys, const GenArc& arc)
	{
		return quadTreeOfPolys.Enumerate(GetGenArcBoundBox(arc));
	}

};

} // namespace Geometry

#endif