// *********************************************************************************************************************
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	NZ
//
// SG compatible
//
// *********************************************************************************************************************

#if !defined CLUSTERHASHUTILS_HPP
#define CLUSTERHASHUTILS_HPP

#pragma once

#include "Array.hpp"
#include "QuadTreeN.hpp"


namespace PointIndex
{

template <class T>
void PutData (GS::Array<T>& array, const T& data)
{
	array.Push (data);
}

template <class T>
void MergeData (GS::Array<T>& array1, const GS::Array<T>& array2)
{
	for (auto it = array2.Enumerate (); it != nullptr; ++it) {
		array1.Push (*it);
	}
}


template <int I, class T>
void PutData (QuadTreeN::QuadTree<I, T>& quadTree, const T& data)
{
	quadTree.Insert (GetElemBox (data), data);
}

template <int I, class T>
void MergeData (QuadTreeN::QuadTree<I, T>& quadTree1, const QuadTreeN::QuadTree<I, T>& quadTree2)
{
	class:	public QuadTreeN::IteratorController<I>,
			public QuadTreeN::OutputAdapter<T>
	{
	public:
		QuadTreeN::QuadTree<I, T>*			quadTree1;
		const QuadTreeN::QuadTree<I, T>*	quadTree2;

		virtual typename QuadTreeN::IteratorController<I>::Type Visit (const QuadTreeN::Box<I>&) const override
		{
			return QuadTreeN::IteratorController<I>::VisitWithoutTesting_;
		}

		virtual void ElemFound (const T& data) override
		{
			quadTree1->Insert (quadTree2->GetElemBox (data), data);
		}
	} conrtoller;

	conrtoller.quadTree1 = &quadTree1;
	conrtoller.quadTree2 = &quadTree2;

	quadTree2.EnumerateWithController (conrtoller, conrtoller);
}

}

#endif
