// *****************************************************************************
// File:			OctTree.hpp
//
// Contact person:	NZ
//
// SG compatible
// *****************************************************************************

#ifndef OCTTREE_HPP
#define OCTTREE_HPP


// --- Includes ----------------------------------------------------------------

#include "QuadTreeImplN.hpp"
#include "Box3DData.h"


// --- Class definitions -------------------------------------------------------

namespace QuadTree {

class Box3D: public QuadTreeN::Box<3>
{
public:
	Box3D (const ::Box3D& box3D)
	{
		Min (0) = box3D.xMin;
		Max (0) = box3D.xMax;
		Min (1) = box3D.yMin;
		Max (1) = box3D.yMax;
		Min (2) = box3D.zMin;
		Max (2) = box3D.zMax;
	}
};


typedef QuadTreeN::IteratorController<3> IteratorController3D;
typedef QuadTreeN::BoxIteratorController<3> BoxIteratorController3D;

template <class T>
class OutputAdapter3D: public QuadTreeN::OutputAdapter<T>
{
};


template <class Type>
class OctTree: private QuadTreeN::TreeImpl<3, Type, StandardContainer, DefaultComparator>
{
public:
	void Insert (const Box3D& box, const Type& elem)
	{
		QuadTreeN::TreeImpl<3, Type, StandardContainer, DefaultComparator>::InsertElem (box, elem);
	}

	void Delete (const Type& elem)
	{
		QuadTreeN::TreeImpl<3, Type, StandardContainer, DefaultComparator>::Delete (elem);
	}

	void Clear ()
	{
		QuadTreeN::TreeImpl<3, Type, StandardContainer, DefaultComparator>::Clear ();
	}

	template <class IteratorController>
	USize GetEnumeratedElemSizeWithController (IteratorController& iteratorController) const
	{
		return QuadTreeN::TreeImpl<3, Type, StandardContainer, DefaultComparator>::GetEnumeratedElemSize (iteratorController);
	}

	USize GetEnumeratedElemSize (const Box3D& box) const
	{
		BoxIteratorController3D controller (box);
		return GetEnumeratedElemSizeWithController (controller);
	}

	template <class IteratorController>
	void EnumerateWithController (IteratorController& iteratorController, OutputAdapter3D<Type>& outputAdapter) const
	{
		QuadTreeN::TreeImpl<3, Type, StandardContainer, DefaultComparator>::Enumerate (iteratorController, outputAdapter);
	}

	void Enumerate (const Box3D& box, OutputAdapter3D<Type>& outputAdapter) const
	{
		BoxIteratorController3D controller (box);
		EnumerateWithController (controller, outputAdapter);
	}

	template <class IteratorController>
	GS::Array<Type> EnumerateWithController (IteratorController& iteratorController) const
	{
		return QuadTreeN::TreeImpl<3, Type, StandardContainer, DefaultComparator>::Enumerate (iteratorController);
	}

	GS::Array<Type> Enumerate (const Box3D& box) const
	{
		BoxIteratorController3D controller (box);
		return EnumerateWithController (controller);
	}

	bool Contains (const Type& elem) const
	{
		return QuadTreeN::TreeImpl<3, Type, StandardContainer, DefaultComparator>::Contains (elem);
	}

	Box3D GetElemBox (const Type& elem) const
	{
		return QuadTreeN::TreeImpl<3, Type, StandardContainer, DefaultComparator>::GetElemBox (elem);
	}

	void LeaveThread ()
	{
		return QuadTreeN::TreeImpl<3, Type, StandardContainer, DefaultComparator>::LeaveThread ();
	}
};

}

#endif //	OCTTREE_HPP
