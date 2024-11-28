
// *****************************************************************************
//
//            Connection between our iterators and STLPort iterators
//            Should be included after STLPort algorithms
//
// Module:			GSRoot
// Namespace:		std
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined STLITERATORCONNECTION_HPP
#define STLITERATORCONNECTION_HPP

#pragma once

// -----------------------------------------------------------------------------

namespace GS {	// predeclarations -> to avoid including all our iterators to algorithms

template <class Cont, class State, class Type>
class ForwardContainerIterator;

template <class Cont, class State, class Type>
class ConstForwardContainerIterator;

template <class Cont>
class BidirectionalContainerIterator;

template <class Cont>
class ConstBidirectionalContainerIterator;

template <class RndCont>
class RandomContainerIterator;

template <class RndCont>
class ConstRandomContainerIterator;

template <class RndCont>
class RandomContainerReverseIterator;

template <class RndCont>
class ConstRandomContainerReverseIterator;

template <class Type>
class IteratorBase;

template <class Type>
class ForwardIterator;

template <class Type>
class ConstForwardIterator;

template <class Type>
class BidirectionalIterator;

template <class Type>
class ConstBidirectionalIterator;

template <class Type>
class RandomIterator;

template <class Type>
class ConstRandomIterator;

}	// namespace GS


namespace std {

template <class Cont, class State, class Type>
struct iterator_traits<GS::ForwardContainerIterator<Cont, State, Type>> {
	typedef forward_iterator_tag						 iterator_category;
	typedef Type										 value_type;
	typedef GS::IteratorOffset							 difference_type;
	typedef Type*										 pointer;
	typedef Type&										 reference;
};


template <class Cont, class State, class Type>
struct iterator_traits<GS::ConstForwardContainerIterator<Cont, State, Type>> {
	typedef		   forward_iterator_tag					 iterator_category;
	typedef const Type									 value_type;
	typedef		  GS::IteratorOffset					 difference_type;
	typedef const Type*									 pointer;
	typedef const Type&									 reference;
};


template <class Cont>
struct iterator_traits<GS::BidirectionalContainerIterator<Cont>> {
	typedef			 bidirectional_iterator_tag			 iterator_category;
	typedef typename Cont::ValueType					 value_type;
	typedef			 GS::IteratorOffset					 difference_type;
	typedef typename Cont::ValueType*					 pointer;
	typedef typename Cont::ValueType&					 reference;
};


template <class Cont>
struct iterator_traits<GS::ConstBidirectionalContainerIterator<Cont>> {
	typedef				   bidirectional_iterator_tag	 iterator_category;
	typedef const typename Cont::ValueType				 value_type;
	typedef				   GS::IteratorOffset			 difference_type;
	typedef const typename Cont::ValueType*				 pointer;
	typedef const typename Cont::ValueType&				 reference;
};


template <class RndCont>
struct iterator_traits<GS::RandomContainerIterator<RndCont>> {
	typedef			 random_access_iterator_tag			 iterator_category;
	typedef typename RndCont::ValueType			         value_type;
	typedef			 GS::IteratorOffset					 difference_type;
	typedef typename RndCont::ValueType*				 pointer;
	typedef typename RndCont::ValueType&				 reference;
};


template <class RndCont>
struct iterator_traits<GS::ConstRandomContainerIterator<RndCont>> {
	typedef				   random_access_iterator_tag	 iterator_category;
	typedef const typename RndCont::ValueType			 value_type;
	typedef				   GS::IteratorOffset			 difference_type;
	typedef const typename RndCont::ValueType*			 pointer;
	typedef const typename RndCont::ValueType&			 reference;
};


template <class RndCont>
struct iterator_traits<GS::RandomContainerReverseIterator<RndCont>> {
	typedef			 random_access_iterator_tag		iterator_category;
	typedef typename RndCont::ValueType				value_type;
	typedef			 GS::IteratorOffset				difference_type;
	typedef typename RndCont::ValueType*			pointer;
	typedef typename RndCont::ValueType&			reference;
};


template <class RndCont>
struct iterator_traits<GS::ConstRandomContainerReverseIterator<RndCont>> {
	typedef				   random_access_iterator_tag	iterator_category;
	typedef const typename RndCont::ValueType			value_type;
	typedef				   GS::IteratorOffset			difference_type;
	typedef const typename RndCont::ValueType*			pointer;
	typedef const typename RndCont::ValueType&			reference;
};


template <class Type>
struct iterator_traits<GS::IteratorBase<Type>> {
	typedef forward_iterator_tag						 iterator_category;
	typedef Type										 value_type;
	typedef GS::IteratorOffset							 difference_type;
	typedef Type*										 pointer;
	typedef Type&										 reference;
};


template <class Type>
struct iterator_traits<GS::ForwardIterator<Type>> {
	typedef forward_iterator_tag						 iterator_category;
	typedef Type										 value_type;
	typedef GS::IteratorOffset							 difference_type;
	typedef Type*										 pointer;
	typedef Type&										 reference;
};


template <class Type>
struct iterator_traits<GS::ConstForwardIterator<Type>> {
	typedef		  forward_iterator_tag					 iterator_category;
	typedef const Type									 value_type;
	typedef		  GS::IteratorOffset					 difference_type;
	typedef const Type*									 pointer;
	typedef const Type&									 reference;
};


template <class Type>
struct iterator_traits<GS::BidirectionalIterator<Type>> {
	typedef bidirectional_iterator_tag					 iterator_category;
	typedef Type										 value_type;
	typedef GS::IteratorOffset							 difference_type;
	typedef Type*										 pointer;
	typedef Type&										 reference;
};


template <class Type>
struct iterator_traits<GS::ConstBidirectionalIterator<Type>> {
	typedef		  bidirectional_iterator_tag			 iterator_category;
	typedef const Type									 value_type;
	typedef		  GS::IteratorOffset					 difference_type;
	typedef const Type*									 pointer;
	typedef const Type&									 reference;
};


template <class Type>
struct iterator_traits<GS::RandomIterator<Type>> {
	typedef random_access_iterator_tag					 iterator_category;
	typedef Type										 value_type;
	typedef GS::IteratorOffset							 difference_type;
	typedef Type*										 pointer;
	typedef Type&										 reference;
};


template <class Type>
struct iterator_traits<GS::ConstRandomIterator<Type>> {
	typedef		  random_access_iterator_tag			iterator_category;
	typedef const Type									value_type;
	typedef		  GS::IteratorOffset					difference_type;
	typedef const Type*									pointer;
	typedef const Type&									reference;
};


}	// namespace GS


#endif
