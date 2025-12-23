#ifndef IGEOMELEMIDRESOLVER_HPP
#define IGEOMELEMIDRESOLVER_HPP

#pragma once
#include "GeomElemIDOneToManyAssocMap.hpp"
#include "CountedPtr.hpp"

class IGeomElemIDResolver
{
public:
	virtual ~IGeomElemIDResolver ();

	virtual void	ResolveVertexID (const GeomElemIDOneToManyAssocMap& fromToMap) = 0;
	virtual void	ResolveEdgeID (const GeomElemIDOneToManyAssocMap& fromToMap) = 0;
};

typedef GS::CountedPtr<IGeomElemIDResolver> IGeomElemIDResolverPtr;

#endif //IGEOMELEMIDRESOLVER_HPP