// *****************************************************************************
// File:			QuadTreeN.hpp
//
// Description:
//
// Project:			GRAPHISOFT Dialog Manager test application (DGTest)
//
// Contact person:	NZ
//
// SG compatible
// *****************************************************************************

#ifndef QUADTREEN_HPP
#define QUADTREEN_HPP

#pragma once

// --- Includes ----------------------------------------------------------------

#include "QuadTreeImplN.hpp"

// --- Class definitions -------------------------------------------------------

namespace QuadTreeN {

template <int I, class Type>
class QuadTree : private TreeImpl<I, Type, ::QuadTree::StandardContainer, ::QuadTree::DefaultComparator> {
public:
	void Insert (const Box<I>& box, const Type& elem)
	{
		TreeImpl<I, Type, ::QuadTree::StandardContainer, ::QuadTree::DefaultComparator>::InsertElem (box, elem);
	}

	void Delete (const Type& elem)
	{
		TreeImpl<I, Type, ::QuadTree::StandardContainer, ::QuadTree::DefaultComparator>::Delete (elem);
	}

	void Clear ()
	{
		TreeImpl<I, Type, ::QuadTree::StandardContainer, ::QuadTree::DefaultComparator>::Clear ();
	}

	template <class IteratorController>
	USize GetEnumeratedElemSizeWithController (IteratorController& iteratorController) const
	{
		return TreeImpl<I, Type, ::QuadTree::StandardContainer, ::QuadTree::DefaultComparator>::GetEnumeratedElemSize (iteratorController);
	}

	USize GetEnumeratedElemSize (const Box<I>& box) const
	{
		BoxIteratorController<I> controller (box);
		GetEnumeratedElemSizeWithController (controller);
	}

	template <class IteratorController>
	void EnumerateWithController (IteratorController& iteratorController, OutputAdapter<Type>& outputAdapter) const
	{
		TreeImpl<I, Type, ::QuadTree::StandardContainer, ::QuadTree::DefaultComparator>::Enumerate (iteratorController, outputAdapter);
	}

	void Enumerate (const Box<I>& box, OutputAdapter<Type>& outputAdapter) const
	{
		BoxIteratorController<I> controller (box);
		EnumerateWithController (controller, outputAdapter);
	}

	template <class IteratorController>
	GS::Array<Type> EnumerateWithController (IteratorController& iteratorController) const
	{
		return TreeImpl<I, Type, ::QuadTree::StandardContainer, ::QuadTree::DefaultComparator>::Enumerate (iteratorController);
	}

	GS::Array<Type> Enumerate (const Box<I>& box) const
	{
		BoxIteratorController<I> controller (box);
		return EnumerateWithController (controller);
	}

	bool Contains (const Type& elem) const
	{
		return TreeImpl<I, Type, ::QuadTree::StandardContainer, ::QuadTree::DefaultComparator>::Contains (elem);
	}

	USize GetSize () const
	{
		return TreeImpl<I, Type, ::QuadTree::StandardContainer, ::QuadTree::DefaultComparator>::GetSize ();
	}

	Box<I> GetElemBox (const Type& elem) const
	{
		return TreeImpl<I, Type, ::QuadTree::StandardContainer, ::QuadTree::DefaultComparator>::GetElemBox (elem);
	}

	void LeaveThread ()
	{
		return TreeImpl<I, Type, ::QuadTree::StandardContainer, ::QuadTree::DefaultComparator>::LeaveThread ();
	}
};

} // namespace QuadTreeN
#endif // QUADTREEN_HPP