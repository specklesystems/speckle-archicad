#ifndef	GEOMELEMIDDESCENDENCYMAP_HPP
#define	GEOMELEMIDDESCENDENCYMAP_HPP

#pragma once
#include "HashTable.hpp"

#include "GeomElemID.hpp"
#include "GeomElemIDSet.hpp"
// from VectorImage
#include "VectorImageExport.h"
#include "GeomElemIDOneToManyAssocMap.hpp"


class VI_DLL_CLASS_EXPORT GeomElemIDDescendencyMap
{
	//Assuming that the descendant sets of one and another root elem are disjoint sets (no common members!),
	//therefore the size of currentDescendantToRoot mapping must always be equal to the total size of all Descendant sets.
public:
	GeomElemIDDescendencyMap ();
	virtual ~GeomElemIDDescendencyMap ();

	void											Clear (); 

	void											AddNewGeomElemID (const GeomElemID& elemID);

	void											Resolve (const GeomElemIDOneToManyAssocMap& fromToMap);

	GeomElemID										GetRootID (const GeomElemID& currentID) const;
	const GeomElemIDSet&							GetDescendents (const GeomElemID& rootID) const;
	const GS::HashTable<GeomElemID, GeomElemID>&	GetCurrentDescendantToRoot () const { return currentDescendantToRoot; }

private:
	GeomElemIDOneToManyAssocMap						rootToCurrentDescendants;	//root (the key) is the original ID
	GS::HashTable<GeomElemID, GeomElemID>			currentDescendantToRoot;
};

#endif //GEOMELEMIDDESCENDENCYMAP_HPP

