#ifndef GEOMELEMIDONETOMANYASSOCMAP_HPP
#define GEOMELEMIDONETOMANYASSOCMAP_HPP
#pragma once

#include "GeomElemID.hpp"
#include "GeomElemIDSet.hpp"
#include "HashTable.hpp"

typedef GS::HashTable<GeomElemID, GeomElemIDSet> GeomElemIDOneToManyAssocMap;

#endif //GEOMELEMIDONETOMANYASSOCMAP_HPP
