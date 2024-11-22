// *********************************************************************************************************************
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	NZ
//
// SG compatible
//
// *********************************************************************************************************************

#if !defined CLUSTERHASH_HPP
#define CLUSTERHASH_HPP

#pragma once

#include "Array.hpp"
#include "HashTable.hpp"
#include "HashSet.hpp"
#include "Discretes.hpp"
#include "Ref.hpp"


namespace PointIndex
{

template <class LocationType, class DataType, class ContainerType>
class Cluster
{
public:
	typedef GS::HashSet<Cluster<LocationType, DataType, ContainerType>*>	PointerHash;
	typedef GS::Ref<Cluster<LocationType, DataType, ContainerType>>			Ref;

private:
	ContainerType					dataContainer;
	GS::ArrayFB<LocationType, 1>	locationReferences;
	PointerHash&					instanceReferences;

private:
	Cluster (const Cluster&);	// disabled

public:
	Cluster (const LocationType& location, PointerHash& instanceReferences):
		instanceReferences (instanceReferences)
	{
		locationReferences.Push (location);
		instanceReferences.Add (this);
	}

	~Cluster ()
	{
		instanceReferences.Delete (this);
	}

	void Put (const DataType& data)
	{
		PutData (dataContainer, data);
	}

	void ImportFrom (const Cluster& other)
	{
		MergeData (dataContainer, other.dataContainer);
		for (auto it = other.locationReferences.Enumerate (); it != nullptr; ++it) {
			locationReferences.Push (*it);
		}
	}

	void AddCell (const LocationType& location)
	{
		return locationReferences.Push (location);
	}

	GS::ConstForwardIterator<LocationType> EnumerateCells () const
	{
		return locationReferences.EnumerateGeneral ();
	}

	ContainerType& GetContainer ()
	{
		return dataContainer;
	}

	const ContainerType& GetContainer () const
	{
		return dataContainer;
	}
};


template <int I, class DataType, class ContainerType>
class ClusterHash
{
private:
	typedef Cluster<Discretes<I>, DataType, ContainerType> ClusterType;

private:
	GS::HashTable<Discretes<I>, typename ClusterType::Ref>	index;
	typename ClusterType::PointerHash						clusterInstances;

private:
	void ReplaceCells (GS::ConstForwardIterator<Discretes<I>> cells, typename ClusterType::Ref replaceWith)
	{
		GS::ArrayFB<Discretes<I>, 4> sCell (cells);
		for (auto it = sCell.Enumerate (); it != nullptr; ++it) {
			index.Set (*it, replaceWith);
		}
	}

	void CreateClusterAtPoint (const Point<I>& point)
	{
		typename ClusterType::Ref firstFound;

		auto proc = [this, &firstFound] (const Discretes<I>& discretes)
		{
			auto found = index.GetPtr (discretes);
			if (found != nullptr && firstFound != *found) {
				if (firstFound == nullptr) {
					firstFound = *found;
				} else {
					firstFound->ImportFrom (**found);
					ReplaceCells ((*found)->EnumerateCells (), firstFound);
				}
			}
		};

		Discretes<I> discretes (point);
		discretes.EnumerateNeighbours (proc);

		if (firstFound != nullptr) {
			firstFound->AddCell (point);
			index.Add (point, firstFound);
		} else {
			index.Add (point, new ClusterType (discretes, clusterInstances));
		}
	}

public:
	void Put (const Point<I>& point, const DataType& elem)
	{
		typename ClusterType::Ref ref;
		if (!index.ContainsKey (point)) {
			CreateClusterAtPoint (point);
		}
		
		index[point]->Put (elem);
	}

	ContainerType* GetContainer (const Point<I>& point)
	{
		if (index.ContainsKey (point)) {
			return &index[point]->GetContainer ();
		} else {
			return nullptr;
		}
	}

	const ContainerType* GetContainer (const Point<I>& point) const
	{
		if (index.ContainsKey (point)) {
			return &index[point]->GetContainer ();
		} else {
			return nullptr;
		}
	}

	void DeleteContainer (const Point<I>& point)
	{
		if (index.ContainsKey (point)) {
			GS::ArrayFB<Discretes<I>, 4> cells (index[point]->EnumerateCells ());
			for (auto it = cells.Enumerate (); it != nullptr; ++it) {
				index.Delete (*it);
			}
		}
	}

	template <class Enumerator>
	void EnumerateClusters (Enumerator enumerator)
	{
		for (auto it = clusterInstances.Enumerate (); it != nullptr; ++it) {
			enumerator ((*it)->GetContainer ());
		}
	}
};

}

#endif
