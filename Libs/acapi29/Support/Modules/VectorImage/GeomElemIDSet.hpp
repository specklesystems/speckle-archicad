#ifndef	GEOMELEMIDSET_HPP
#define	GEOMELEMIDSET_HPP

#pragma once
#include "GeomElemID.hpp"
#include "HashTable.hpp"
#include "HashSet.hpp"
// from VectorImage
#include "VectorImageExport.h"

class GeomElemIDSet;
typedef GS::HashTable<GeomElemID, GeomElemIDSet> GeomElemIDOneToManyAssocMap;

class VI_DLL_CLASS_EXPORT GeomElemIDSet : public GS::HashSet<GeomElemID>
{
public:
	GeomElemIDSet ();
	virtual ~GeomElemIDSet ();

	void Resolve (const GeomElemIDOneToManyAssocMap& fromToMap, GeomElemIDSet& unresolved);
private:
};

#endif //GEOMELEMIDSET_HPP
