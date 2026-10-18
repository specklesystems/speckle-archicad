// *****************************************************************************
// File:			Range.hpp
//
// Description:		Range template class
//
// Project:			GSRoot
//
// Namespace:		GS
//
// Contact person:	AZS, BM
//
// SG compatible
// *****************************************************************************

#ifndef RANGE_HPP
#define RANGE_HPP

#pragma once

// --- Includes ----------------------------------------------------------------
#include "ObjectState.hpp"


namespace GS {

// --- Range class declaration -------------------------------------------------

template<class TYPE>
class Range {
private:
	TYPE	lowerBound;
	TYPE	upperBound;

	void	Normalize (void);

public:
	Range ();
	Range (const TYPE& bound1, const TYPE& bound2);

	void	Set (const TYPE& bound1, const TYPE& bound2);
	void	SetWithLength (const TYPE& bound, const TYPE& length);

	TYPE	GetMin (void) const;
	TYPE	GetMax (void) const;
	TYPE	GetLength (void) const;

	bool	operator== (const Range<TYPE>&) const;
	bool	operator!= (const Range<TYPE>&) const;
	bool	IsOverlapping (const Range<TYPE>&) const;
	bool	IsInside (const TYPE& position) const;
	bool	IsEmpty (void) const;

	Range<TYPE>		Union (const Range<TYPE>&) const;
	Range<TYPE>		Intersection (const Range<TYPE>&) const;

	void	Unify (const Range<TYPE>&);
	void	Intersect (const Range<TYPE>&);

	GSErrCode Store (GS::ObjectState& os) const;
};

template <class TYPE>
inline ULong	GenerateHashValue (const Range<TYPE>& Range);

// --- Private methods ---------------------------------------------------------

template <class TYPE>
void	Range<TYPE>::Normalize (void)
{
	if (lowerBound > upperBound) {
		TYPE temp = lowerBound;
		lowerBound = upperBound;
		upperBound = temp;
	}
}


// --- Public methods ----------------------------------------------------------

template <class TYPE>
Range<TYPE>::Range ():
	lowerBound (0),
	upperBound (0)
{
}


template <class TYPE>
Range<TYPE>::Range (const TYPE& bound1, const TYPE& bound2):
	lowerBound (bound1),
	upperBound (bound2)
{
	Normalize ();
}


template <class TYPE>
void	Range<TYPE>::Set (const TYPE& bound1, const TYPE& bound2)
{
	lowerBound = bound1;
	upperBound = bound2;

	Normalize ();
}


template <class TYPE>
void	Range<TYPE>::SetWithLength (const TYPE& bound, const TYPE& length)
{
	lowerBound = bound;
	upperBound = lowerBound + length;

	Normalize ();
}


template <class TYPE>
TYPE	Range<TYPE>::GetMin (void) const
{
	return lowerBound;
}


template <class TYPE>
TYPE	Range<TYPE>::GetMax (void) const
{
	return upperBound;
}


template <class TYPE>
TYPE	Range<TYPE>::GetLength (void) const
{
	return upperBound - lowerBound;
}


template <class TYPE>
bool	Range<TYPE>::operator== (const Range<TYPE>& toCompare) const
{
	return (toCompare.lowerBound == lowerBound && toCompare.upperBound == upperBound);
}


template <class TYPE>
bool	Range<TYPE>::operator!= (const Range<TYPE>& toCompare) const
{
	return (toCompare.lowerBound != lowerBound || toCompare.upperBound != upperBound);
}


template <class TYPE>
bool	Range<TYPE>::IsOverlapping (const Range<TYPE>& toCompare) const
{
	return (IsInside (toCompare.lowerBound) || toCompare.IsInside (lowerBound));
}


template <class TYPE>
bool	Range<TYPE>::IsInside (const TYPE& position) const
{
	return (lowerBound <= position && position < upperBound);
}


template <class TYPE>
bool	Range<TYPE>::IsEmpty (void) const
{
	return (upperBound == lowerBound);
}


template <class TYPE>
Range<TYPE>		Range<TYPE>::Union (const Range<TYPE>& toUnion) const
{
	Range<TYPE> t (toUnion);

	if (lowerBound < t.lowerBound)
		t.lowerBound = lowerBound;

	if (upperBound > t.upperBound)
		t.upperBound = upperBound;

	return t;
}


template <class TYPE>
Range<TYPE>		Range<TYPE>::Intersection (const Range<TYPE>& toIntersect) const
{
	if (!IsOverlapping (toIntersect))
		return Range<TYPE> ();

	Range<TYPE> t (toIntersect);

	if (lowerBound > t.lowerBound)
		t.lowerBound = lowerBound;

	if (upperBound < t.upperBound)
		t.upperBound = upperBound;

	return t;
}


template <class TYPE>
void	Range<TYPE>::Unify (const Range<TYPE>& toUnify)
{
	if (toUnify.lowerBound < lowerBound)
		lowerBound = toUnify.lowerBound;

	if (toUnify.upperBound > upperBound)
		upperBound = toUnify.upperBound;
}


template <class TYPE>
void	Range<TYPE>::Intersect (const Range<TYPE>& toIntersect)
{
	if (!IsOverlapping (toIntersect)) {
		lowerBound = 0;
		upperBound = 0;
		return;
	}

	if (toIntersect.lowerBound > lowerBound)
		lowerBound = toIntersect.lowerBound;

	if (toIntersect.upperBound < upperBound)
		upperBound = toIntersect.upperBound;
}


template <class TYPE>
GSErrCode Range<TYPE>::Store (GS::ObjectState& os) const
{
	os.Add ("min", GetMin ());
	os.Add ("max", GetMax ());
	return NoError;
}


template <class TYPE>
inline ULong	GenerateHashValue (const Range<TYPE>& range)
{
	static const UInt32 HashPrime = 65599;

	return GS::CalculateHashValue (range.GetMin ()) * HashPrime + GS::CalculateHashValue (range.GetMax ());
}


}	// namespace GS

#endif
