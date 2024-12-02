#ifndef GEOMETRY_POLYGON2D_OVERLAPPINGEDGE_RESULT_HPP
#define GEOMETRY_POLYGON2D_OVERLAPPINGEDGE_RESULT_HPP
#pragma once

// from GSRoot
#include "Algorithms.hpp"
#include "Owner.hpp"

// from Geometry
#include "GeometricDefinitions.h"
#include "Point2D.hpp"
#include "GenArc2DData.h"
#include "Sector2DData.h"


namespace Geometry {


template <class EdgeType>
class EdgeOfTwoPolys
{
public:
	EdgeType item;
	UIndex polyIdx1, edgeIdx1, polyIdx2, edgeIdx2;
	bool isOrientationReversed1, isOrientationReversed2;

	EdgeOfTwoPolys (const EdgeType& item, UIndex polyIdx1, UIndex edgeIdx1, UIndex polyIdx2, UIndex edgeIdx2, bool isOrientationReversed1, bool isOrientationReversed2)
	{
		this->item = item;
		this->polyIdx1 = polyIdx1;
		this->edgeIdx1 = edgeIdx1;
		this->isOrientationReversed1 = isOrientationReversed1;
		this->polyIdx2 = polyIdx2;
		this->edgeIdx2 = edgeIdx2;
		this->isOrientationReversed2 = isOrientationReversed2;
	}

};

template <class EdgeType>
class EdgeOfAPoly
{
public:
	EdgeType item;
	UIndex polyIdx, edgeIdx;
	bool isOrientationReversed;

	EdgeOfAPoly (const EdgeType& item, UIndex polyIdx, UIndex edgeIdx, bool isOrientationReversed)
	{
		this->item = item;
		this->polyIdx = polyIdx;
		this->edgeIdx = edgeIdx;
		this->isOrientationReversed = isOrientationReversed;
	}

	const EdgeType& GetItem (void) const { return item; }
};

typedef EdgeOfAPoly<Sector> SectorOfAPoly;
typedef EdgeOfAPoly<GenArc> ArcOfAPoly;
typedef EdgeOfTwoPolys<Sector> SectorOfTwoPolys;
typedef EdgeOfTwoPolys<GenArc> ArcOfTwoPolys;



class GEOMETRY_DLL_EXPORT IOverlappingEdgeResult {
private:
	bool isItOverlapping;
	bool isVisible;
public:
	IOverlappingEdgeResult (bool overlapping, bool visible) :
		isItOverlapping (overlapping),
		isVisible (visible)
	{
	}

	virtual ~IOverlappingEdgeResult ();

	virtual const Point2D& GetStartPoint (void) const = 0;
	virtual const Point2D& GetEndPoint (void) const = 0;
	virtual bool IsOrientationReversed (void) const = 0;
	virtual UIndex GetPolyIndex () const = 0;
	virtual UIndex GetEdgeIndex () const = 0;

	bool IsVisible (void) const
	{
		return isVisible;
	}

	bool IsItOverlapping (void) const
	{
		return isItOverlapping;
	}
};


class GEOMETRY_DLL_EXPORT OverlappingSectorResult : public IOverlappingEdgeResult
{
private:
	SectorOfAPoly item;
public:
	OverlappingSectorResult (const SectorOfAPoly& val, bool overlapping, bool visible) :
		IOverlappingEdgeResult (overlapping, visible),
		item (val)
	{
	}

	const SectorOfAPoly& GetItem (void) const
	{
		return item;
	}

	virtual const Point2D& GetStartPoint (void) const override
	{
		return !item.isOrientationReversed ? item.item.c1 : item.item.c2;
	}

	virtual const Point2D& GetEndPoint (void) const override
	{
		return !item.isOrientationReversed ? item.item.c2 : item.item.c1;
	}

	virtual bool IsOrientationReversed (void) const override;

	virtual UIndex GetPolyIndex () const override
	{
		return item.polyIdx;
	}

	virtual UIndex GetEdgeIndex () const override
	{
		return item.edgeIdx + 1;
	}
};


class GEOMETRY_DLL_EXPORT OverlappingArcResult : public IOverlappingEdgeResult {
private:
	ArcOfAPoly item;
public:
	OverlappingArcResult (const ArcOfAPoly& val, bool overlapping, bool visible) :
		IOverlappingEdgeResult (overlapping, visible),
		item (val)
	{
	}

	const ArcOfAPoly& GetItem (void) const
	{
		return item;
	}

	virtual const Point2D& GetStartPoint (void) const override
	{
		return !item.isOrientationReversed ? item.item.GetBegC () : item.item.GetEndC ();
	}

	virtual const Point2D& GetEndPoint (void) const override
	{
		return !item.isOrientationReversed ? item.item.GetEndC () : item.item.GetBegC ();
	}

	virtual bool IsOrientationReversed (void) const override;

	virtual UIndex GetPolyIndex () const override
	{
		return item.polyIdx;
	}

	virtual UIndex GetEdgeIndex () const override
	{
		return item.edgeIdx + 1;
	}
};


class Polygon2DOverlappingEdgeResults
{
public:
	void AddResult (const SectorOfAPoly& val, bool overlapping, bool isVisible = true)
	{	
		if (val.GetItem ().GetLength () < Eps)
			return;

		edgeParts.Push (Pass (new OverlappingSectorResult (val, overlapping, isVisible)));
	}

	void AddResult (const ArcOfAPoly& val, bool overlapping, bool isVisible = true)
	{
		if (Geometry::IsNear (val.GetItem ().GetBegC (), val.GetItem ().GetEndC ()))
			return;

		edgeParts.Push (Pass (new OverlappingArcResult (val, overlapping, isVisible)));
	}

	const IOverlappingEdgeResult* GetEdgePartFromEndPoint (const Point2D& endPoint) const
	{
		USize results = 0;
		const IOverlappingEdgeResult* result = nullptr;
		for (const auto& edgePart : edgeParts) {
			if (Geometry::IsNear (edgePart->GetEndPoint (), endPoint)) { 
				++results;
				result = edgePart.Get ();
			}
		}

		if (results != 1) {
			DBBREAK ();
			throw GS::GeneralException ();
		}

		return result;
	}

	void Enumerate (const std::function<void (const IOverlappingEdgeResult*)>& enumerator) const
	{
		edgeParts.Enumerate ([&](const GS::Owner<IOverlappingEdgeResult>& edge) -> void {
			enumerator (edge.Get ());
		});
	}

	bool IsEdgeStartingAsHidden () const
	{
		if (DBVERIFY (!edgeParts.IsEmpty () && edgeParts[0] != nullptr)) {
			return edgeParts[0]->IsItOverlapping ();
		}
		return false;
	}

	GS::Array<GS::Pair<Point2D, bool>> GetCutPoints (bool currentCutHidden, bool nextCutHidden) const
	{
		if (DBERROR (edgeParts.IsEmpty ()))
			return {};

		GS::Array<GS::Pair<Point2D, bool>> cutPoints;

		for (const GS::Owner<IOverlappingEdgeResult>& edgePart : edgeParts) {
			if (edgePart->IsItOverlapping () != currentCutHidden) {
				cutPoints.PushNew (edgePart->GetStartPoint (), true);
				currentCutHidden = !currentCutHidden;
			} else if (edgePart.Get () != edgeParts[0].Get ()){
				cutPoints.PushNew (edgePart->GetStartPoint (), false);
			}
		}

		if (currentCutHidden && !nextCutHidden) {
			cutPoints.PushNew (edgeParts.GetLast()->GetEndPoint(), true);
		} else {
			cutPoints.PushNew (edgeParts.GetLast()->GetEndPoint(), false);
		}

		return cutPoints;
	}

	template <class MultiPolygonType>
	GSErrCode OrderEdgeParts (const MultiPolygonType& polys)
	{
		if (DBERROR (edgeParts.IsEmpty ()))
			return Error;

		if (edgeParts.GetSize () == 1) 
			return NoError;

		const UIndex edgeIdx = edgeParts[0]->GetEdgeIndex ();
		const UIndex polyIdx = edgeParts[0]->GetPolyIndex ();

		GS::Optional<GS::Owner<IOverlappingEdgeResult>> nextEdgePart;

		Sector sector;
		GenArc genArc;
		if (polys[polyIdx].GetEdgeIterator (edgeIdx)->GetSector (sector, genArc))		// arc
			nextEdgePart = RetrieveEdgePartFromStartPoint (genArc.GetBegC ());
		else
			nextEdgePart = RetrieveEdgePartFromStartPoint (sector.c1);

		if (DBERROR (!nextEdgePart.HasValue ()))
			return Error;

		GS::Array<GS::Owner<IOverlappingEdgeResult>> orderedEdgeParts (edgeParts.GetSize ());
		orderedEdgeParts.Push (std::move (*nextEdgePart));

		for (UIndex i = 0; i < edgeParts.GetSize () - 1 && nextEdgePart.HasValue (); ++i) {
			nextEdgePart = RetrieveEdgePartFromStartPoint (orderedEdgeParts[i]->GetEndPoint ());
			if (DBVERIFY (nextEdgePart.HasValue ()))
				orderedEdgeParts.Push (std::move (*nextEdgePart));
		}

		if (DBVERIFY (nextEdgePart.HasValue ())) {
			edgeParts = std::move (orderedEdgeParts);
			return NoError;
		} else {
			edgeParts.DeleteAll ([](const GS::Owner<IOverlappingEdgeResult>& edgePiece) -> bool {
				return edgePiece == nullptr;
			});
			return Error;
		}
	}

private:
	GS::Optional<GS::Owner<IOverlappingEdgeResult>> RetrieveEdgePartFromStartPoint (const Point2D& startPoint)
	{
		GS::Array<UIndex> results (1);
		for (UIndex i = 0; i < edgeParts.GetSize (); ++i) {
			if (edgeParts[i] != nullptr && Geometry::IsNear (edgeParts[i]->GetStartPoint (), startPoint))
				results.Push (i);
		}

		if (DBERROR (results.GetSize () != 1))
			return GS::NoValue;

		return GS::Optional<GS::Owner<IOverlappingEdgeResult>> (std::move (edgeParts[results[0]]));
	}

	GS::Array<GS::Owner<IOverlappingEdgeResult>>	edgeParts;
};

}
#endif