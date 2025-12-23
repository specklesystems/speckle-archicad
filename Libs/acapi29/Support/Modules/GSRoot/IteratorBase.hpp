
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

// from Standard Library
#include <iterator>


namespace GS {


template <class T>
class IteratorBase {
public:
		// Definitions

	typedef T ValueType;	// type of the value iterator iterates on

	virtual ~IteratorBase () = default;
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


template <class Type>
struct std::iterator_traits<GS::IteratorBase<Type>> {
	typedef forward_iterator_tag						 iterator_category;
	typedef Type										 value_type;
	typedef GS::IteratorOffset							 difference_type;
	typedef Type*										 pointer;
	typedef Type&										 reference;
};


#endif
