#ifndef REIDMAPCOLLECTOR_HPP
#define REIDMAPCOLLECTOR_HPP

#pragma once
#include "GeomElemID.hpp"
#include "GeomElemIDSet.hpp"
#include "IGeomElemIDResolver.hpp"
#include "GeomElemIDOneToManyAssocMap.hpp"


class ReIDMapCollector //is a guard!
{
public:
	ReIDMapCollector (IGeomElemIDResolverPtr resolverInit);
	virtual ~ReIDMapCollector ();

	void AddPolyRenumEntry (const GS::Guid& oldPolyGUID, const GS::Guid& newPolyGUID);

	void AddVertexRenumEntry (const GS::Guid& oldPolyGUID, const UInt32 oldVertexID, const GS::Guid& newPolyGUID, const UInt32 newVertexID);
	void AddEdgeRenumEntry (const GS::Guid& oldPolyGUID, const UInt32 oldEdgeID, const GS::Guid& newPolyGUID, const UInt32 newEdgeID);

private:
	GeomElemIDOneToManyAssocMap vertexReIDMap;
	GeomElemIDOneToManyAssocMap edgeReIDMap;
	IGeomElemIDResolverPtr resolver;
};

#endif //REIDMAPCOLLECTOR_HPP