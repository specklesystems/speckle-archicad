
// *****************************************************************************
//
//                 Bidirectional iterator interfaces and wrappers
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined BIDIRECTIONALITERATOR_HPP
#define BIDIRECTIONALITERATOR_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "ForwardIterator.hpp"



// ===================== Interface IBidirectionalIterator ======================

namespace GS {

template <class Type>
class IBidirectionalIterator: public IForwardIterator<Type> {
public:
	virtual void	Decrement (void) = 0;

	// ----------------------------------------------------------------------------------
	// Core operations to be implemented are:
	//
	//   CreateClone, CreateConstClone, GetCurrent, Increment, Decrement, IsEqual, IsEnd
	// ----------------------------------------------------------------------------------
};

}	// namespace GS
// _____________________ Interface IBidirectionalIterator ______________________



// ======================== Class BidirectionalIterator ========================

namespace GS {

template <class Type>
class BidirectionalIterator: public ForwardIterator<Type> {
public:
		// Constructors

	inline BidirectionalIterator (IBidirectionalIterator<Type>* wrapperTarget);
	inline BidirectionalIterator (const BidirectionalIterator& source);
	inline BidirectionalIterator&	operator= (const BidirectionalIterator& source);

		// User interface

	inline BidirectionalIterator&	operator++ ();
	inline BidirectionalIterator	operator++ (int);

	inline BidirectionalIterator&	operator-- ();
	inline BidirectionalIterator	operator-- (int);
};



template <class Type>
inline BidirectionalIterator<Type>::BidirectionalIterator (IBidirectionalIterator<Type>* wrapperTarget):
	ForwardIterator<Type> (wrapperTarget)
{
	NULL_PTR_CHECK (wrapperTarget);
}


template <class Type>
inline BidirectionalIterator<Type>::BidirectionalIterator (const BidirectionalIterator& source):
	ForwardIterator<Type> (source)
{
	NULL_REF_CHECK (source);
}


template <class Type>
inline BidirectionalIterator<Type>&		BidirectionalIterator<Type>::operator= (const BidirectionalIterator& source)
{
	NULL_REF_CHECK (source);

	ForwardIterator<Type>::operator= (source);

	return *this;
}


template <class Type>
inline BidirectionalIterator<Type>&		BidirectionalIterator<Type>::operator++ ()
{
	PRECOND_DEPRECATED (!this->target->IsEnd ());

	this->target->Increment ();

	return *this;
}


template <class Type>
inline BidirectionalIterator<Type>	BidirectionalIterator<Type>::operator++ (int)
{
	PRECOND_DEPRECATED (!this->target->IsEnd ());

	BidirectionalIterator result = *this;

	this->target->Increment ();

	return result;
}


template <class Type>
inline BidirectionalIterator<Type>&		BidirectionalIterator<Type>::operator-- ()
{
	static_cast<IBidirectionalIterator<Type>*> (this->target)->Decrement ();

	return *this;
}


template <class Type>
inline BidirectionalIterator<Type>	BidirectionalIterator<Type>::operator-- (int)
{
	BidirectionalIterator result = *this;

	static_cast<IBidirectionalIterator<Type>*> (this->target)->Decrement ();

	return result;
}

}	// namespace GS
// ________________________ Class BidirectionalIterator ________________________



// =================== Interface IConstBidirectionalIterator ===================

namespace GS {

template <class Type>
class IConstBidirectionalIterator: public IConstForwardIterator<Type> {
public:
	virtual void	Decrement (void) = 0;

	// ----------------------------------------------------------------
	// Core operations to be implemented are:
	//
	//   CreateClone, GetCurrent, Increment, Decrement, IsEqual, IsEnd
	// ----------------------------------------------------------------
};

}	// namespace GS
// ___________________ Interface IConstBidirectionalIterator ___________________



// ===================== Class ConstBidirectionalIterator ======================

namespace GS {

template <class Type>
class ConstBidirectionalIterator: public ConstForwardIterator<Type> {
public:
		// Constructors

	inline ConstBidirectionalIterator (IConstBidirectionalIterator<Type>* wrapperTarget);
	inline ConstBidirectionalIterator (const ConstBidirectionalIterator& source);
	inline ConstBidirectionalIterator (const BidirectionalIterator<Type>& source);
	inline ConstBidirectionalIterator&	operator= (const ConstBidirectionalIterator& source);
	inline ConstBidirectionalIterator&	operator= (const BidirectionalIterator<Type>& source);

		// User interface

	inline ConstBidirectionalIterator&	operator++ ();
	inline ConstBidirectionalIterator	operator++ (int);

	inline ConstBidirectionalIterator&	operator-- ();
	inline ConstBidirectionalIterator	operator-- (int);
};



template <class Type>
inline ConstBidirectionalIterator<Type>::ConstBidirectionalIterator (IConstBidirectionalIterator<Type>* wrapperTarget):
	ConstForwardIterator<Type> (wrapperTarget)
{
	NULL_PTR_CHECK (wrapperTarget);
}


template <class Type>
inline ConstBidirectionalIterator<Type>::ConstBidirectionalIterator (const ConstBidirectionalIterator& source):
	ConstForwardIterator<Type> (source)
{
	NULL_REF_CHECK (source);
}


template <class Type>
inline ConstBidirectionalIterator<Type>::ConstBidirectionalIterator (const BidirectionalIterator<Type>& source):
	ConstForwardIterator<Type> (source)
{
	NULL_REF_CHECK (source);
}


template <class Type>
inline ConstBidirectionalIterator<Type>&	ConstBidirectionalIterator<Type>::operator= (const ConstBidirectionalIterator& source)
{
	NULL_REF_CHECK (source);

	ConstForwardIterator<Type>::operator= (source);

	return *this;
}


template <class Type>
inline ConstBidirectionalIterator<Type>&	ConstBidirectionalIterator<Type>::operator= (const BidirectionalIterator<Type>& source)
{
	NULL_REF_CHECK (source);

	ConstForwardIterator<Type>::operator= (source);

	return *this;
}


template <class Type>
inline ConstBidirectionalIterator<Type>&	ConstBidirectionalIterator<Type>::operator++ ()
{
	PRECOND_DEPRECATED (!this->target->IsEnd ());

	this->target->Increment ();

	return *this;
}


template <class Type>
inline ConstBidirectionalIterator<Type>		ConstBidirectionalIterator<Type>::operator++ (int)
{
	PRECOND_DEPRECATED (!this->target->IsEnd ());

	ConstBidirectionalIterator result = *this;

	this->target->Increment ();

	return result;
}


template <class Type>
inline ConstBidirectionalIterator<Type>&	ConstBidirectionalIterator<Type>::operator-- ()
{
	static_cast<IConstBidirectionalIterator<Type>*> (this->target)->Decrement ();

	return *this;
}


template <class Type>
inline ConstBidirectionalIterator<Type>		ConstBidirectionalIterator<Type>::operator-- (int)
{
	ConstBidirectionalIterator result = *this;

	static_cast<IConstBidirectionalIterator<Type>*> (this->target)->Decrement ();

	return result;
}

}	// namespace GS
// _____________________ Class ConstBidirectionalIterator ______________________


#endif
