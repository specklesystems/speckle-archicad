// *********************************************************************************************************************
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	NZ
//
// SG compatible
//
// *********************************************************************************************************************

#if !defined UNIQUECLUSTERHASH_HPP
#define UNIQUECLUSTERHASH_HPP

#pragma once

#include "ClusterHash.hpp"


namespace PointIndex
{

template <int I, class DataType, class ContainerType>
class UniqueClusterHash
{
private:
	ClusterHash<I, DataType, ContainerType>		clusterHash;
	GS::HashTable<DataType, Point<I>>			dataToLocationHash;

public:
	void Put (const Point<I>& point, const DataType& elem)
	{
		clusterHash.Put (point, elem);

		DBVERIFY (dataToLocationHash.Add (elem, point));
	}

	bool Contains (const DataType& elem) const
	{
		return dataToLocationHash.ContainsKey (elem);
	}

	void Delete (const DataType& elem)
	{
		const Point<I>	location	= dataToLocationHash[elem]; 
		ContainerType*	container	= clusterHash.GetContainer (location);

		DeleteData (*container, elem);
		dataToLocationHash.Delete (elem);

		if (IsEmptyData (*container)) {
			clusterHash.DeleteContainer (location);
		}
	}

	ContainerType* GetContainer (const DataType& elem)
	{
		return clusterHash.GetContainer (dataToLocationHash[elem]);
	}

	const ContainerType* GetContainer (const DataType& elem) const
	{
		return clusterHash.GetContainer (dataToLocationHash[elem]);
	}

	ContainerType* GetContainer (const Point<I>& point)
	{
		return clusterHash.GetContainer (point);
	}

	const ContainerType* GetContainer (const Point<I>& point) const
	{
		return clusterHash.GetContainer (point);
	}

	template <class Enumerator>
	void EnumerateClusters (Enumerator enumerator)
	{
		clusterHash.EnumerateClusters (enumerator);
	}
};

}

#endif
