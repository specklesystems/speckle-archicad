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

#ifndef SORTEDQUADTREEN_HPP
#define SORTEDQUADTREEN_HPP

#pragma once

#include "QuadTreeImplN.hpp"


namespace QuadTreeN {

template <int I, class Type, class Comparator>
class SortedQuadTree : private TreeImpl<I, Type, ::QuadTree::SortedContainer, Comparator> {
	Comparator compare;
public:
	void Insert (const Box<I>& box, const Type& elem)
	{
		TreeImpl<I, Type, ::QuadTree::SortedContainer, Comparator>::InsertElem (box, elem);
	}

	void Delete (const Type& elem)
	{
		TreeImpl<I, Type, ::QuadTree::SortedContainer, Comparator>::Delete (elem);
	}

	void Clear ()
	{
		TreeImpl<I, Type, ::QuadTree::SortedContainer, Comparator>::Clear ();
	}

	template <class IteratorController>
	USize GetEnumeratedElemSizeWithController (IteratorController& iteratorController) const
	{
		return TreeImpl<I, Type, ::QuadTree::SortedContainer, Comparator>::GetEnumeratedElemSize (iteratorController);
	}

	USize GetEnumeratedElemSize (const Box<I>& box) const
	{
		BoxIteratorController<I> controller (box);
		return GetEnumeratedElemSizeWithController (controller);
	}

	template <class IteratorController>
	void EnumerateWithController (IteratorController& iteratorController, OutputAdapter<Type>& outputAdapter) const
	{
		TreeImpl<I, Type, ::QuadTree::SortedContainer, Comparator>::Enumerate (iteratorController, outputAdapter);
	}

	void Enumerate (const Box<I>& box, OutputAdapter<Type>& outputAdapter) const
	{
		BoxIteratorController<I> controller (box);
		EnumerateWithController (controller, outputAdapter);
	}

	template <class IteratorController>
	GS::Array<Type> EnumerateWithController (IteratorController& iteratorController) const
	{
		return TreeImpl<I, Type, ::QuadTree::SortedContainer, Comparator>::Enumerate (iteratorController);
	}

	GS::Array<Type> Enumerate (const Box<I>& box) const
	{
		BoxIteratorController<I> controller (box);
		return EnumerateWithController (controller);
	}

	bool Contains (const Type& elem) const
	{
		return TreeImpl<I, Type, ::QuadTree::SortedContainer, Comparator>::Contains (elem);
	}

	USize GetSize () const
	{
		return TreeImpl<I, Type, ::QuadTree::SortedContainer, Comparator>::GetSize ();
	}

	Box<I> GetElemBox (const Type& elem) const
	{
		return TreeImpl<I, Type, ::QuadTree::SortedContainer, Comparator>::GetElemBox (elem);
	}

	void LeaveThread ()
	{
		return TreeImpl<I, Type, ::QuadTree::SortedContainer, Comparator>::LeaveThread ();
	}

	class BatchWriteScope: public QuadTreeN::TreeImpl<I, Type, ::QuadTree::SortedContainer, Comparator>::BatchWriteScope {
	public:
		BatchWriteScope (SortedQuadTree& tree):
			QuadTreeN::TreeImpl<I, Type, ::QuadTree::SortedContainer, Comparator>::BatchWriteScope (tree)
		{
		}
	};
};

} // namespace SortedQuadTreeN




#endif // SORTEDQUADTREEN_HPP



