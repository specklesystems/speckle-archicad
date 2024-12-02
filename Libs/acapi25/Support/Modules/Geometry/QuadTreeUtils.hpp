// File:			SortedQuadTree.hpp
//
// Description:     Utility structures for Quadtree implementation.
//
// Project:			B-504
//
// Contact person:	NZ
//
// SG compatible
// *****************************************************************************


#ifndef QUADTREEUTILS_HPP
#define QUADTREEUTILS_HPP

#pragma once

#include "Box2DData.h"
#include "Rect.hpp"

#include <set>

#include "HashSet.hpp"


// --- Class definitions -------------------------------------------------------

// --- SortedContainer ---------------------------------------------------------

namespace QuadTreeN {

const double Tolerance = 0.0001;

// --- Point -------------------------------------------------------------------

template <int I>
class Point {
public:
	double coords[I];

public:
	Point ()
	{
		for (UIndex i = 0; i < I; ++i) {
			coords[i] = 0.0;
		}
	}
};

template <int I>
class Box {
protected:
	double bounds[I * 2];	// xMin, xMax, yMin...

public:
	Box ()
	{
		for (UIndex i = 0; i < I; ++i) {
			Min (i) = Max (i) = 0.0;
		}
	}

	Box (const Point<I>& mins, const Point<I>& maxs)
	{
		for (UIndex i = 0; i < I; ++i) {
			Min (i) = mins.coords[i];
			Max (i) = maxs.coords[i];
		}
	}

	Box (const Point<I>& center, const double width)
	{
		const double sizePer2 = width / 2.0;

		for (UIndex i = 0; i < I; ++i) {
			Min (i) = center.coords[i] - sizePer2;
			Max (i) = center.coords[i] + sizePer2;
		}
	}

	const double& Min (int i) const
	{
		return bounds[2 * i];
	}

	const double& Max (int i) const
	{
		return bounds[2 * i + 1];
	}

	double& Min (int i)
	{
		return bounds[2 * i];
	}

	double& Max (int i)
	{
		return bounds[2 * i + 1];
	}

	void Inflate (double value)
	{
		for (UIndex i = 0; i < I; ++i) {
			Min (i) -= value;
			Max (i) += value;
		}
	}

	bool IsInside (const Box<I>& toTest) const
	{
		for (UIndex i = 0; i < I; ++i) {
			if (Min (i) > toTest.Min (i) || Max (i) < toTest.Max (i)) {
				return false;
			}
		}

		return true;
	}

	bool IsOverlapping (const Box<I>& toTest) const
	{
		for (UIndex i = 0; i < I; ++i) {
			if (toTest.Max (i) < Min (i) || toTest.Min (i) > Max (i)) {
				return false;
			}
		}

		return true;
	}

	bool IsOutside (const Box<I>& toTest) const
	{
		for (UIndex i = 0; i < I; ++i) {
			if (toTest.Max (i) < Min (i) || toTest.Min (i) > Max (i)) {
				return true;
			}
		}

		return false;
	}

	Point<I> GetMins () const
	{
		Point<I> p;
		for (UIndex i = 0; i < I; ++i) {
			p.coords[i] = Min (i);
		}

		return p;
	}

	Point<I> GetCenter () const
	{
		Point<I> p;
		for (UIndex i = 0; i < I; ++i) {
			p.coords[i] = (Min (i) + Max (i)) / 2.0;
		}

		return p;
	}

	Point<I> GetDiagonal () const
	{
		Point<I> p;
		for (UIndex i = 0; i < I; ++i) {
			p.coords[i] = Max (i) - Min (i);
		}

		return p;
	}

	double GetWidth (UIndex i) const
	{
		return Max (i) - Min (i);
	}

	bool IsValid () const
	{
		for (UIndex i = 0; i < I; ++i) {
			if (Min (i) > Max (i) || Min (i) < -1e15 || Max (i) > 1e15) {
				return false;
			}
		}

		return true;
	}
};

// --- IteratorController ------------------------------------------------------

template <int I>
class IteratorController {
public:
	bool VisitWithoutTesting (const Box<I>& boxToTest) const
	{
		return Visit (boxToTest) == VisitWithoutTesting_;
	}

	bool DontVisit (const Box<I>& boxToTest) const
	{
		return Visit (boxToTest) == DontVisit_;
	}

	bool VisitWithTesting (const Box<I>& boxToTest) const
	{
		return Visit (boxToTest) == VisitWithTesting_;
	}

	bool DontVisitElem (const Box<I>& boxToTest) const
	{
		return VisitElem (boxToTest) == DontVisit_;
	}

	virtual bool DontTestBox ()
	{
		return false;
	}

	virtual void CellBegin ()
	{
	}

	virtual void CellEnd ()
	{
	}

protected:
	enum Type {
		DontVisit_,
		VisitWithTesting_,
		VisitWithoutTesting_
	};

	virtual Type Visit (const Box<I>&) const = 0;
	virtual Type VisitElem (const Box<I>& box) const
	{
		return Visit (box);
	}
};

// --- BoxIteratorController ---------------------------------------------------

template <int I>
class BoxIteratorController {
public:
	const Box<I> box;

public:
	BoxIteratorController (const Box<I>& box) :
		box (GetInflatedBox (box))
	{
	}

	bool VisitWithoutTesting (const Box<I>& boxToTest) const
	{
		return box.IsInside (boxToTest);
	}

	bool DontVisit (const Box<I>& boxToTest) const
	{
		return box.IsOutside (boxToTest);
	}

	bool VisitWithTesting (const Box<I>& boxToTest) const
	{
		return box.IsOverlapping (boxToTest);
	}

	bool DontVisitElem (const Box<I>& boxToTest) const
	{
		return box.IsOutside (boxToTest);
	}

private:
	static Box<I> GetInflatedBox (const Box<I>& box)
	{
		Box<I> inflatedBox = box;
		inflatedBox.Inflate (Tolerance);

		return inflatedBox;
	}
};

// --- OutputAdapter -----------------------------------------------------------

template <class Type>
class OutputAdapter {
public:
	virtual void BlockBegin () {}
	virtual void BlockEnd () {}

	virtual void ElemFound (const Type&) = 0;
};

} // namespace QuadTreeN


namespace QuadTree {

typedef QuadTreeN::IteratorController<2> IteratorController;
typedef QuadTreeN::BoxIteratorController<2> BoxIteratorController;

template <class T>
class OutputAdapter : public QuadTreeN::OutputAdapter<T> {
};

template <class Type, class Comparator>
class SortedContainer {
	std::set<Type, Comparator> elems;

public:
	void Insert (Type elemRef)
	{
		elems.insert (elemRef);
	}

	void Delete (Type elemRef)
	{
		elems.erase (elemRef);
	}

	USize GetSize () const
	{
		return static_cast<USize> (elems.size ());
	}

	typename std::set<Type>::const_iterator Begin () const
	{
		return elems.cbegin ();
	}

	typename std::set<Type>::const_iterator End () const
	{
		return elems.cend ();
	}

	virtual ~SortedContainer () {}
};

// --- StandardContainer ---------------------------------------------------

template <class Type, class>
class StandardContainer {
	GS::HashSet<Type> elems;

public:
	void Insert (Type elemRef)
	{
		elems.Add (elemRef);
	}

	void Delete (Type elemRef)
	{
		elems.Delete (elemRef);
	}

	USize GetSize () const
	{
		return elems.GetSize ();
	}

	typename GS::HashSet<Type>::ConstIterator Begin () const
	{
		return elems.Begin ();
	}

	typename GS::HashSet<Type>::ConstIterator End () const
	{
		return elems.End ();
	}

	virtual ~StandardContainer () {}
};

// DefaultComparator - Default struct for StandardContainer class

struct DefaultComparator {
	template<class Type>
	bool operator()(const Type&, const Type&) const
	{
		return true;
	}

	~DefaultComparator () {}
};

// --- Box ---------------------------------------------------------------------

class Box : public QuadTreeN::Box<2> {
public:
	Box (const QuadTreeN::Box<2>& box) :
		QuadTreeN::Box<2> (box)
	{
	}

	Box (const Box2DData& boxData)
	{
		Min (0) = boxData.xMin;
		Max (0) = boxData.xMax;
		Min (1) = boxData.yMin;
		Max (1) = boxData.yMax;
	}

	Box (double x1, double y1, double x2, double y2)
	{
		Min (0) = x1;
		Max (0) = x2;
		Min (1) = y1;
		Max (1) = y2;
	}

	Box (const GS::Rect<double>& box)
	{
		Min (0) = box.GetLeft ();
		Max (0) = box.GetRight ();
		Min (1) = box.GetTop ();
		Max (1) = box.GetBottom ();
	}

	double GetLeft () const
	{
		return Min (0);
	}

	double GetRight () const
	{
		return Max (0);
	}

	double GetTop () const
	{
		return Max (1);
	}

	double GetBottom () const
	{
		return Min (1);
	}

	Box2DData ToBox2DData () const
	{
		return Box2DData (GetLeft (), GetBottom (), GetRight (), GetTop ());
	}
};

} // namespace QuadTree

#endif // ifndef QUADTREEUTILS_HPP