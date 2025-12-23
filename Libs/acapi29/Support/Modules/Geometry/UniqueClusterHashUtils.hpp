// *********************************************************************************************************************
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	NZ
//
// SG compatible
//
// *********************************************************************************************************************

#if !defined UNIQUECLUSTERHASHUTILS_HPP
#define UNIQUECLUSTERHASHUTILS_HPP

#pragma once

#include "QuadTreeN.hpp"


namespace PointIndex
{

template <int I, class T>
void DeleteData (QuadTreeN::QuadTree<I, T>& quadTree, const T& data)
{
	quadTree.Delete (data);
}

template <int I, class T>
bool IsEmptyData (const QuadTreeN::QuadTree<I, T>& quadTree)
{
	return quadTree.GetSize () == 0;
}

}

#endif
