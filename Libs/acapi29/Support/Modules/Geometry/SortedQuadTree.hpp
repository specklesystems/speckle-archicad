// *****************************************************************************
// File:			SortedQuadTree.hpp
//
// Description:
//
// Project:			B-504
//
// Contact person:	NZ
//
// SG compatible
// *****************************************************************************

#ifndef SORTEDQUADTREE_HPP
#define SORTEDQUADTREE_HPP

#pragma once

#include "SortedQuadTreeN.hpp"


namespace QuadTree {

template <class Type, class Comparator = std::less<Type>>
class SortedQuadTree : private QuadTreeN::TreeImpl<2, Type, SortedContainer, Comparator> {

public:

	void Insert (const Box& box, const Type& elem)
	{
		QuadTreeN::TreeImpl<2, Type, SortedContainer, Comparator>::InsertElem (box, elem);
	}

	void Delete (const Type& elem)
	{
		QuadTreeN::TreeImpl<2, Type, SortedContainer, Comparator>::Delete (elem);
	}

	void Clear ()
	{
		QuadTreeN::TreeImpl<2, Type, SortedContainer, Comparator>::Clear ();
	}

	template <class IteratorController>
	USize GetEnumeratedElemSizeWithController (IteratorController& iteratorController) const
	{
		return QuadTreeN::TreeImpl<2, Type, SortedContainer, Comparator>::GetEnumeratedElemSize (iteratorController);
	}

	USize GetEnumeratedElemSize (const Box& box) const
	{
		BoxIteratorController controller (box);
		return GetEnumeratedElemSizeWithController (controller);
	}

	template <class IteratorController>
	void EnumerateWithController (IteratorController& iteratorController, OutputAdapter<Type>& outputAdapter) const
	{
		QuadTreeN::TreeImpl<2, Type, SortedContainer, Comparator>::Enumerate (iteratorController, outputAdapter);
	}

	void Enumerate (const Box& box, OutputAdapter<Type>& outputAdapter) const
	{
		BoxIteratorController controller (box);
		EnumerateWithController (controller, outputAdapter);
	}

	template <class IteratorController>
	GS::Array<Type> EnumerateWithController (IteratorController& iteratorController) const
	{
		return QuadTreeN::TreeImpl<2, Type, SortedContainer, Comparator>::Enumerate (iteratorController);
	}

	GS::Array<Type> Enumerate (const Box& box) const
	{
		BoxIteratorController controller (box);
		return EnumerateWithController (controller);
	}

	bool Contains (const Type& elem) const
	{
		return QuadTreeN::TreeImpl<2, Type, SortedContainer, Comparator>::Contains (elem);
	}

	Box GetElemBox (const Type& elem) const
	{
		return QuadTreeN::TreeImpl<2, Type, SortedContainer, Comparator>::GetElemBox (elem);
	}

	void LeaveThread ()
	{
		return QuadTreeN::TreeImpl<2, Type, SortedContainer, Comparator>::LeaveThread ();
	}

	class BatchWriteScope: public QuadTreeN::TreeImpl<2, Type, SortedContainer, Comparator>::BatchWriteScope {
	public:
		BatchWriteScope (SortedQuadTree& tree):
			QuadTreeN::TreeImpl<2, Type, SortedContainer, Comparator>::BatchWriteScope (tree)
		{
		}
	};
};

} // namespace QuadTree

#endif // SORTEDQUADTREE_HPP



