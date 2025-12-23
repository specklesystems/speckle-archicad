// *****************************************************************************
// File:			QuadTree.hpp
//
// Description:
//
// Project:			GRAPHISOFT Dialog Manager test application (DGTest)
//
// Contact person:	NZ
//
// SG compatible
// *****************************************************************************

#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#pragma once

// --- Includes ----------------------------------------------------------------

#include "QuadTreeN.hpp"


namespace QuadTree {

template<class Type>
class QuadTree: private QuadTreeN::TreeImpl<2, Type, StandardContainer, DefaultComparator> {

public:

	virtual ~QuadTree () override
	{
	}

	void Insert (const Box& box, const Type& elem)
	{
		QuadTreeN::TreeImpl<2, Type, StandardContainer, DefaultComparator>::InsertElem (box, elem);
	}

	void Delete (const Type& elem)
	{
		QuadTreeN::TreeImpl<2, Type, StandardContainer, DefaultComparator>::Delete (elem);
	}

	void Clear ()
	{
		QuadTreeN::TreeImpl<2, Type, StandardContainer, DefaultComparator>::Clear ();
	}

	template <class IteratorController>
	USize GetEnumeratedElemSizeWithController (IteratorController& iteratorController) const
	{
		return QuadTreeN::TreeImpl<2, Type, StandardContainer, DefaultComparator>::GetEnumeratedElemSize (iteratorController);
	}

	USize GetEnumeratedElemSize (const Box& box) const
	{
		BoxIteratorController controller (box);
		return GetEnumeratedElemSizeWithController (controller);
	}

	template <class IteratorController>
	void EnumerateWithController (IteratorController& iteratorController, OutputAdapter<Type>& outputAdapter) const
	{
		QuadTreeN::TreeImpl<2, Type, StandardContainer, DefaultComparator>::Enumerate (iteratorController, outputAdapter);
	}

	void Enumerate (const Box& box, OutputAdapter<Type>& outputAdapter) const
	{
		BoxIteratorController controller (box);
		EnumerateWithController (controller, outputAdapter);
	}

	template <class IteratorController>
	GS::Array<Type> EnumerateWithController (IteratorController& iteratorController) const
	{
		return QuadTreeN::TreeImpl<2, Type, StandardContainer, DefaultComparator>::Enumerate (iteratorController);
	}

	GS::Array<Type> Enumerate (const Box& box) const
	{
		BoxIteratorController controller (box);
		return EnumerateWithController (controller);
	}

	bool Contains (const Type& elem) const
	{
		return QuadTreeN::TreeImpl<2, Type, StandardContainer, DefaultComparator>::Contains (elem);
	}

	Box GetElemBox (const Type& elem) const
	{
		return QuadTreeN::TreeImpl<2, Type, StandardContainer, DefaultComparator>::GetElemBox (elem);
	}

	void LeaveThread ()
	{
		return QuadTreeN::TreeImpl<2, Type, StandardContainer, DefaultComparator>::LeaveThread ();
	}
};


} // namespace QuadTree

#endif // QUADTREE_HPP
