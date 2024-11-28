
// *****************************************************************************
//
//                             Base class for iterators
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined ITERATORBASE_HPP
#define ITERATORBASE_HPP

#include "Definitions.hpp"


namespace GS {


template <class T>
class IteratorBase {
public:
		// Definitions

	typedef T ValueType;	// type of the value iterator iterates on

	virtual ~IteratorBase () {}
};


// TODO C++20: Replace this with std::ranges::subrange.
template <class Iter, class Sentinel = Iter>
class IteratorRange {

	Iter	 mBeg;
	Sentinel mEnd;

public:

	IteratorRange (Iter beg, Sentinel end)
		: mBeg { std::move (beg) }, mEnd { std::move (end) }
	{}

	Iter		begin () const	{ return mBeg; }
	Sentinel	end () const	{ return mEnd; }
};


}	// namespace GS


#endif
