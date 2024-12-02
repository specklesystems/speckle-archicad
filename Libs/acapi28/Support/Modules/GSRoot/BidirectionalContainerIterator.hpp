
// *********************************************************************************************************************
//
//     Classes BidirectionalContainerIterator,
//			   ConstBidirectionalContainerIterator,
//			   GeneralBidirectionalContainerIterator,
//			   ConstGeneralBidirectionalContainerIterator
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// Requirements:
//   Target container should have the following types:
//     - IteratorState
//     - ValueType
//   Target container should have the following methods:
//     - ValueType&        GetCurrent (const IteratorState& state);          -> for non-const iterators
//     - const ValueType&  GetCurrent (const IteratorState& state) const;    -> for const iterators
//     - void              Increment  (IteratorState& state) const;
//     - void              Decrement  (IteratorState& state) const;
//     - bool              IsEqual    (const IteratorState& state1, const IteratorState& state2) const;
//     - bool              IsBegin    (const IteratorState& state) const;
//     - bool              IsEnd      (const IteratorState& state) const;
//
// *********************************************************************************************************************


#if !defined BIDIRECTIONALCONTAINERITERATOR_HPP
#define BIDIRECTIONALCONTAINERITERATOR_HPP

#pragma once

// --- Includes --------------------------------------------------------------------------------------------------------

#include "BidirectionalIterator.hpp"



// === Class BidirectionalContainerIterator ============================================================================

namespace GS {

template <class Cont>
class ConstBidirectionalContainerIterator;


template <class Cont>
class BidirectionalContainerIterator {
private:
	typedef typename Cont::IteratorState	IteratorState;

	Cont*			cont;	// target container iterator is connected to
	IteratorState	state;	// current state of the iterator

	friend class ConstBidirectionalContainerIterator<Cont>;

public:
	typedef typename Cont::ValueType		ValueType;

		// Constructors

	inline BidirectionalContainerIterator ();
	inline BidirectionalContainerIterator (Cont& targetContainer, const IteratorState& initialState);
	inline BidirectionalContainerIterator (const BidirectionalContainerIterator& source);
	inline BidirectionalContainerIterator&	operator= (const BidirectionalContainerIterator& source);

		// User interface

	inline ValueType&						operator*  () const;
	inline ValueType*						operator-> () const;

	inline BidirectionalContainerIterator&	operator++ ();
	inline BidirectionalContainerIterator	operator++ (int);

	inline BidirectionalContainerIterator&	operator-- ();
	inline BidirectionalContainerIterator	operator-- (int);

	inline bool								operator== (const BidirectionalContainerIterator& rightOp) const;
	inline bool								operator!= (const BidirectionalContainerIterator& rightOp) const;

	inline bool								operator== (std::nullptr_t) const;
	inline bool								operator!= (std::nullptr_t) const;
};

}	// namespace GS



// === Class ConstBidirectionalContainerIterator =======================================================================

namespace GS {

template <class Cont>
class ConstBidirectionalContainerIterator {
private:
	typedef typename Cont::IteratorState	IteratorState;

	const Cont*		cont;	// target container iterator is connected to
	IteratorState	state;	// current state of the iterator

public:
	typedef typename Cont::ValueType	ValueType;

		// Constructors

	inline ConstBidirectionalContainerIterator ();
	inline ConstBidirectionalContainerIterator (const Cont& targetContainer, const IteratorState& initialState);
	inline ConstBidirectionalContainerIterator (const ConstBidirectionalContainerIterator& source);
	inline ConstBidirectionalContainerIterator (const BidirectionalContainerIterator<Cont>& source);
	inline ConstBidirectionalContainerIterator&	operator= (const ConstBidirectionalContainerIterator& source);
	inline ConstBidirectionalContainerIterator&	operator= (const BidirectionalContainerIterator<Cont>& source);

		// User interface

	inline const ValueType&						operator*  () const;
	inline const ValueType*						operator-> () const;

	inline ConstBidirectionalContainerIterator&	operator++ ();
	inline ConstBidirectionalContainerIterator	operator++ (int);

	inline ConstBidirectionalContainerIterator&	operator-- ();
	inline ConstBidirectionalContainerIterator	operator-- (int);

	inline bool									operator== (const ConstBidirectionalContainerIterator& rightOp) const;
	inline bool									operator!= (const ConstBidirectionalContainerIterator& rightOp) const;

	inline bool									operator== (std::nullptr_t) const;
	inline bool									operator!= (std::nullptr_t) const;
};

}	// namespace GS



// === Class GeneralBidirectionalContainerIterator =====================================================================

namespace GS {

template <class Cont>
class ConstGeneralBidirectionalContainerIterator;


template <class Cont>
class GeneralBidirectionalContainerIterator: public BidirectionalIterator<typename Cont::ValueType>,
											 public IBidirectionalIterator<typename Cont::ValueType>
{
public:
	typedef typename Cont::ValueType		ValueType;

private:
	typedef typename Cont::IteratorState	IteratorState;

	Cont*			cont;	// target container iterator is connected to
	IteratorState	state;	// current state of the iterator

	inline IBidirectionalIterator<ValueType>*	GetIteratorInterface (void) { return this; }

	friend class ConstGeneralBidirectionalContainerIterator<Cont>;

protected:
	virtual void	Assign (const IForwardIterator<ValueType>* source) override;

	virtual IBidirectionalIterator<ValueType>*		CreateClone      (void) const override;
	virtual IConstBidirectionalIterator<ValueType>*	CreateConstClone (void) const override;

	virtual ValueType&	GetCurrent (void) const override;
	virtual void		Increment  (void) override;
	virtual void		Decrement  (void) override;
	virtual bool		IsEqual	   (const IForwardIterator<ValueType>* rightOp) const override;
	virtual bool		IsEnd	   (void) const override;

public:
	// Constructors

	inline GeneralBidirectionalContainerIterator ();
	inline GeneralBidirectionalContainerIterator (Cont& targetContainer, const IteratorState& initialState);
	inline GeneralBidirectionalContainerIterator (const GeneralBidirectionalContainerIterator& source);
	inline GeneralBidirectionalContainerIterator&	operator= (const GeneralBidirectionalContainerIterator& source);
	inline ~GeneralBidirectionalContainerIterator ();

		// User interface

	inline ValueType&								operator*  () const;
	inline ValueType*								operator-> () const;

	inline GeneralBidirectionalContainerIterator&	operator++ ();
	inline GeneralBidirectionalContainerIterator	operator++ (int);

	inline GeneralBidirectionalContainerIterator&	operator-- ();
	inline GeneralBidirectionalContainerIterator	operator-- (int);

	inline bool										operator== (const GeneralBidirectionalContainerIterator& rightOp) const;
	inline bool										operator!= (const GeneralBidirectionalContainerIterator& rightOp) const;

	inline bool										operator== (std::nullptr_t) const;
	inline bool										operator!= (std::nullptr_t) const;

	inline Cont*									GetTarget (void) const;
};

}	// namespace GS



// === Class ConstGeneralBidirectionalContainerIterator ================================================================

namespace GS {

template <class Cont>
class ConstGeneralBidirectionalContainerIterator: public ConstBidirectionalIterator<typename Cont::ValueType>,
												  public IConstBidirectionalIterator<typename Cont::ValueType>
{
public:
	typedef typename Cont::ValueType		ValueType;

private:
	typedef typename Cont::IteratorState	IteratorState;

	const Cont*			cont;	// target container iterator is connected to
	IteratorState		state;	// current state of the iterator

	inline IConstBidirectionalIterator<ValueType>*	GetIteratorInterface (void) { return this; }

protected:
	virtual void	Assign (const IConstForwardIterator<ValueType>* source) override;
	virtual void	Assign (const IForwardIterator<ValueType>* source) override;

	virtual IConstBidirectionalIterator<ValueType>*	CreateClone (void) const override;

	virtual const ValueType&	GetCurrent (void) const override;
	virtual void				Increment  (void) override;
	virtual void				Decrement  (void) override;
	virtual bool				IsEqual	   (const IConstForwardIterator<ValueType>* rightOp) const override;
	virtual bool				IsEnd	   (void) const override;

public:
		// Constructors

	inline ConstGeneralBidirectionalContainerIterator ();
	inline ConstGeneralBidirectionalContainerIterator (const Cont& targetContainer, const IteratorState& initialState);
	inline ConstGeneralBidirectionalContainerIterator (const ConstGeneralBidirectionalContainerIterator& source);
	inline ConstGeneralBidirectionalContainerIterator (const GeneralBidirectionalContainerIterator<Cont>& source);
	inline ConstGeneralBidirectionalContainerIterator&	operator= (const ConstGeneralBidirectionalContainerIterator& source);
	inline ConstGeneralBidirectionalContainerIterator&	operator= (const GeneralBidirectionalContainerIterator<Cont>& source);
	inline ~ConstGeneralBidirectionalContainerIterator ();

		// User interface

	inline const ValueType&								operator*  () const;
	inline const ValueType*								operator-> () const;

	inline ConstGeneralBidirectionalContainerIterator&	operator++ ();
	inline ConstGeneralBidirectionalContainerIterator	operator++ (int);

	inline ConstGeneralBidirectionalContainerIterator&	operator-- ();
	inline ConstGeneralBidirectionalContainerIterator	operator-- (int);

	inline bool											operator== (const ConstGeneralBidirectionalContainerIterator& rightOp) const;
	inline bool											operator!= (const ConstGeneralBidirectionalContainerIterator& rightOp) const;

	inline bool											operator== (std::nullptr_t) const;
	inline bool											operator!= (std::nullptr_t) const;

	inline const Cont*									GetTarget (void) const;
};

}	// namespace GS



// === Class BidirectionalContainerIterator ============================================================================

namespace GS {

template <class Cont>
inline BidirectionalContainerIterator<Cont>::BidirectionalContainerIterator ():
	cont (nullptr)
{
}


template <class Cont>
inline BidirectionalContainerIterator<Cont>::BidirectionalContainerIterator (Cont& targetContainer, const IteratorState& initialState):
	cont  (&targetContainer),
	state (initialState)
{
	NULL_REF_CHECK (targetContainer);
	NULL_REF_CHECK (initialState);
}


template <class Cont>
inline BidirectionalContainerIterator<Cont>::BidirectionalContainerIterator (const BidirectionalContainerIterator& source):
	cont  (source.cont),
	state (source.state)
{
	NULL_REF_CHECK (source);
}


template <class Cont>
inline BidirectionalContainerIterator<Cont>&	BidirectionalContainerIterator<Cont>::operator= (const BidirectionalContainerIterator& source)
{
	NULL_REF_CHECK (source);

	if (this != &source) {
		cont   = source.cont;
		state  = source.state;
	}

	return *this;
}


template <class Cont>
inline typename BidirectionalContainerIterator<Cont>::ValueType&	BidirectionalContainerIterator<Cont>::operator* () const
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	return cont->GetCurrent (state);
}


template <class Cont>
inline typename BidirectionalContainerIterator<Cont>::ValueType*	BidirectionalContainerIterator<Cont>::operator-> () const
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	return &cont->GetCurrent (state);
}


template <class Cont>
inline BidirectionalContainerIterator<Cont>&	BidirectionalContainerIterator<Cont>::operator++ ()
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	cont->Increment (state);

	return *this;
}


template <class Cont>
inline BidirectionalContainerIterator<Cont>		BidirectionalContainerIterator<Cont>::operator++ (int)
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	BidirectionalContainerIterator result = *this;

	cont->Increment (state);

	return result;
}


template <class Cont>
inline BidirectionalContainerIterator<Cont>&	BidirectionalContainerIterator<Cont>::operator-- ()
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsBegin (state));

	cont->Decrement (state);

	return *this;
}


template <class Cont>
inline BidirectionalContainerIterator<Cont>		BidirectionalContainerIterator<Cont>::operator-- (int)
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsBegin (state));

	BidirectionalContainerIterator result = *this;

	cont->Decrement (state);

	return result;
}


template <class Cont>
inline bool		BidirectionalContainerIterator<Cont>::operator== (const BidirectionalContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (cont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.cont != nullptr);
	PRECOND_DEPRECATED (cont == rightOp.cont);

	return cont->IsEqual (state, rightOp.state);
}


template <class Cont>
inline bool		BidirectionalContainerIterator<Cont>::operator!= (const BidirectionalContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (cont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.cont != nullptr);
	PRECOND_DEPRECATED (cont == rightOp.cont);

	return !cont->IsEqual (state, rightOp.state);
}


template <class Cont>
inline bool		BidirectionalContainerIterator<Cont>::operator== (std::nullptr_t) const
{
	PRECOND_DEPRECATED (cont != nullptr);

	return cont->IsEnd (state);
}


template <class Cont>
inline bool		BidirectionalContainerIterator<Cont>::operator!= (std::nullptr_t) const
{
	PRECOND_DEPRECATED (cont != nullptr);

	return !cont->IsEnd (state);
}

}	// namespace GS



// === Class ConstBidirectionalContainerIterator =======================================================================

namespace GS {

template <class Cont>
inline ConstBidirectionalContainerIterator<Cont>::ConstBidirectionalContainerIterator ():
	cont (nullptr)
{
}


template <class Cont>
inline ConstBidirectionalContainerIterator<Cont>::ConstBidirectionalContainerIterator (const Cont& targetContainer, const IteratorState& initialState):
	cont  (&targetContainer),
	state (initialState)
{
	NULL_REF_CHECK (targetContainer);
	NULL_REF_CHECK (initialState);
}


template <class Cont>
inline ConstBidirectionalContainerIterator<Cont>::ConstBidirectionalContainerIterator (const ConstBidirectionalContainerIterator& source):
	cont  (source.cont),
	state (source.state)
{
	NULL_REF_CHECK (source);
}


template <class Cont>
inline ConstBidirectionalContainerIterator<Cont>::ConstBidirectionalContainerIterator (const BidirectionalContainerIterator<Cont>& source):
	cont  (source.cont),
	state (source.state)
{
	NULL_REF_CHECK (source);
}


template <class Cont>
inline ConstBidirectionalContainerIterator<Cont>&	ConstBidirectionalContainerIterator<Cont>::operator= (const ConstBidirectionalContainerIterator& source)
{
	NULL_REF_CHECK (source);

	if (this != &source) {
		cont  = source.cont;
		state = source.state;
	}

	return *this;
}


template <class Cont>
inline ConstBidirectionalContainerIterator<Cont>&	ConstBidirectionalContainerIterator<Cont>::operator= (const BidirectionalContainerIterator<Cont>& source)
{
	NULL_REF_CHECK (source);

	if (this != static_cast<const void*> (&source)) {
		cont  = source.cont;
		state = source.state;
	}

	return *this;
}


template <class Cont>
inline const typename ConstBidirectionalContainerIterator<Cont>::ValueType&		ConstBidirectionalContainerIterator<Cont>::operator* () const
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	return cont->GetCurrent (state);
}


template <class Cont>
inline const typename ConstBidirectionalContainerIterator<Cont>::ValueType*		ConstBidirectionalContainerIterator<Cont>::operator-> () const
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	return &cont->GetCurrent (state);
}


template <class Cont>
inline ConstBidirectionalContainerIterator<Cont>&	ConstBidirectionalContainerIterator<Cont>::operator++ ()
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	cont->Increment (state);

	return *this;
}


template <class Cont>
inline ConstBidirectionalContainerIterator<Cont>	ConstBidirectionalContainerIterator<Cont>::operator++ (int)
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	ConstBidirectionalContainerIterator result = *this;

	cont->Increment (state);

	return result;
}


template <class Cont>
inline ConstBidirectionalContainerIterator<Cont>&	ConstBidirectionalContainerIterator<Cont>::operator-- ()
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsBegin (state));

	cont->Decrement (state);

	return *this;
}


template <class Cont>
inline ConstBidirectionalContainerIterator<Cont>	ConstBidirectionalContainerIterator<Cont>::operator-- (int)
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsBegin (state));

	ConstBidirectionalContainerIterator result = *this;

	cont->Decrement (state);

	return result;
}


template <class Cont>
inline bool		ConstBidirectionalContainerIterator<Cont>::operator== (const ConstBidirectionalContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (cont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.cont != nullptr);
	PRECOND_DEPRECATED (cont == rightOp.cont);

	return cont->IsEqual (state, rightOp.state);
}


template <class Cont>
inline bool		ConstBidirectionalContainerIterator<Cont>::operator!= (const ConstBidirectionalContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (cont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.cont != nullptr);
	PRECOND_DEPRECATED (cont == rightOp.cont);

	return !cont->IsEqual (state, rightOp.state);
}


template <class Cont>
inline bool		ConstBidirectionalContainerIterator<Cont>::operator== (std::nullptr_t) const
{
	PRECOND_DEPRECATED (cont != nullptr);

	return cont->IsEnd (state);
}


template <class Cont>
inline bool		ConstBidirectionalContainerIterator<Cont>::operator!= (std::nullptr_t) const
{
	PRECOND_DEPRECATED (cont != nullptr);

	return !cont->IsEnd (state);
}

}	// namespace GS



// === Class GeneralBidirectionalContainerIterator =====================================================================

namespace GS {

template <class Cont>
inline GeneralBidirectionalContainerIterator<Cont>::GeneralBidirectionalContainerIterator ():
	BidirectionalIterator<ValueType> (GetIteratorInterface ()),
	cont (nullptr)
{
}


template <class Cont>
inline GeneralBidirectionalContainerIterator<Cont>::GeneralBidirectionalContainerIterator (Cont& targetContainer, const IteratorState& initialState):
	BidirectionalIterator<ValueType> (GetIteratorInterface ()),
	cont  (&targetContainer),
	state (initialState)
{
	NULL_REF_CHECK (targetContainer);
	NULL_REF_CHECK (initialState);
}


template <class Cont>
inline GeneralBidirectionalContainerIterator<Cont>::GeneralBidirectionalContainerIterator (const GeneralBidirectionalContainerIterator& source):
	BidirectionalIterator<ValueType> (GetIteratorInterface ()),
	cont  (source.cont),
	state (source.state)
{
	NULL_REF_CHECK (source);
}


template <class Cont>
inline GeneralBidirectionalContainerIterator<Cont>&		GeneralBidirectionalContainerIterator<Cont>::operator= (const GeneralBidirectionalContainerIterator& source)
{
	NULL_REF_CHECK (source);

	if (this != &source) {
		BidirectionalIterator<ValueType>::operator= (source);

		cont   = source.cont;
		state  = source.state;
	}

	return *this;
}


template <class Cont>
void	GeneralBidirectionalContainerIterator<Cont>::Assign (const IForwardIterator<ValueType>* /*source*/)
{
	// GeneralBidirectionalContainerIterator contains own realization of the IBidirectionalterator interface
	// working on members in this class which are copied from the source iterator
}


template <class Cont>
inline GeneralBidirectionalContainerIterator<Cont>::~GeneralBidirectionalContainerIterator ()
{
	this->target = nullptr;
}


template <class Cont>
inline typename GeneralBidirectionalContainerIterator<Cont>::ValueType&		GeneralBidirectionalContainerIterator<Cont>::operator* () const
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	return cont->GetCurrent (state);
}


template <class Cont>
inline typename GeneralBidirectionalContainerIterator<Cont>::ValueType*		GeneralBidirectionalContainerIterator<Cont>::operator-> () const
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	return &cont->GetCurrent (state);
}


template <class Cont>
inline GeneralBidirectionalContainerIterator<Cont>&		GeneralBidirectionalContainerIterator<Cont>::operator++ ()
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	cont->Increment (state);

	return *this;
}


template <class Cont>
inline GeneralBidirectionalContainerIterator<Cont>		GeneralBidirectionalContainerIterator<Cont>::operator++ (int)
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	GeneralBidirectionalContainerIterator result = *this;

	cont->Increment (state);

	return result;
}


template <class Cont>
inline GeneralBidirectionalContainerIterator<Cont>&		GeneralBidirectionalContainerIterator<Cont>::operator-- ()
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsBegin (state));

	cont->Decrement (state);

	return *this;
}


template <class Cont>
inline GeneralBidirectionalContainerIterator<Cont>	GeneralBidirectionalContainerIterator<Cont>::operator-- (int)
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsBegin (state));

	GeneralBidirectionalContainerIterator result = *this;

	cont->Decrement (state);

	return result;
}


template <class Cont>
inline bool		GeneralBidirectionalContainerIterator<Cont>::operator== (const GeneralBidirectionalContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (cont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.cont != nullptr);
	PRECOND_DEPRECATED (cont == rightOp.cont);

	return cont->IsEqual (state, rightOp.state);
}


template <class Cont>
inline bool		GeneralBidirectionalContainerIterator<Cont>::operator!= (const GeneralBidirectionalContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (cont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.cont != nullptr);
	PRECOND_DEPRECATED (cont == rightOp.cont);

	return !cont->IsEqual (state, rightOp.state);
}


template <class Cont>
inline bool		GeneralBidirectionalContainerIterator<Cont>::operator== (std::nullptr_t) const
{
	PRECOND_DEPRECATED (cont != nullptr);

	return cont->IsEnd (state);
}


template <class Cont>
inline bool		GeneralBidirectionalContainerIterator<Cont>::operator!= (std::nullptr_t) const
{
	PRECOND_DEPRECATED (cont != nullptr);

	return !cont->IsEnd (state);
}


template <class Cont>
inline Cont*	GeneralBidirectionalContainerIterator<Cont>::GetTarget (void) const
{
	return cont;
}


template <class Cont>
IBidirectionalIterator<typename GeneralBidirectionalContainerIterator<Cont>::ValueType>*	GeneralBidirectionalContainerIterator<Cont>::CreateClone (void) const
{
	return new GeneralBidirectionalContainerIterator (*this);
}


template <class Cont>
IConstBidirectionalIterator<typename GeneralBidirectionalContainerIterator<Cont>::ValueType>*	GeneralBidirectionalContainerIterator<Cont>::CreateConstClone (void) const
{
	return new ConstGeneralBidirectionalContainerIterator<Cont> (*this);
}


template <class Cont>
typename GeneralBidirectionalContainerIterator<Cont>::ValueType&	GeneralBidirectionalContainerIterator<Cont>::GetCurrent (void) const
{
	return operator* ();
}


template <class Cont>
void	GeneralBidirectionalContainerIterator<Cont>::Increment (void)
{
	operator++ ();
}


template <class Cont>
void	GeneralBidirectionalContainerIterator<Cont>::Decrement (void)
{
	operator-- ();
}


template <class Cont>
bool	GeneralBidirectionalContainerIterator<Cont>::IsEqual (const IForwardIterator<ValueType>* rightOp) const
{
	NULL_PTR_CHECK (rightOp);

	const GeneralBidirectionalContainerIterator* ro = dynamic_cast<const GeneralBidirectionalContainerIterator*> (rightOp);
	TYPE_CHECK (ro != nullptr);

	return operator== (*ro);
}


template <class Cont>
bool	GeneralBidirectionalContainerIterator<Cont>::IsEnd (void) const
{
	return operator== (nullptr);
}

}	// namespace GS



// === Class ConstGeneralBidirectionalContainerIterator ================================================================

namespace GS {

template <class Cont>
inline ConstGeneralBidirectionalContainerIterator<Cont>::ConstGeneralBidirectionalContainerIterator ():
	ConstBidirectionalIterator<ValueType> (GetIteratorInterface ()),
	cont (nullptr)
{
}


template <class Cont>
inline ConstGeneralBidirectionalContainerIterator<Cont>::ConstGeneralBidirectionalContainerIterator (const Cont& targetContainer, const IteratorState& initialState):
	ConstBidirectionalIterator<ValueType> (GetIteratorInterface ()),
	cont  (&targetContainer),
	state (initialState)
{
	NULL_REF_CHECK (targetContainer);
	NULL_REF_CHECK (initialState);
}


template <class Cont>
inline ConstGeneralBidirectionalContainerIterator<Cont>::ConstGeneralBidirectionalContainerIterator (const ConstGeneralBidirectionalContainerIterator& source):
	ConstBidirectionalIterator<ValueType> (GetIteratorInterface ()),
	cont  (source.cont),
	state (source.state)
{
	NULL_REF_CHECK (source);
}


template <class Cont>
inline ConstGeneralBidirectionalContainerIterator<Cont>::ConstGeneralBidirectionalContainerIterator (const GeneralBidirectionalContainerIterator<Cont>& source):
	ConstBidirectionalIterator<ValueType> (GetIteratorInterface ()),
	cont  (source.cont),
	state (source.state)
{
	NULL_REF_CHECK (source);
}


template <class Cont>
inline ConstGeneralBidirectionalContainerIterator<Cont>&	ConstGeneralBidirectionalContainerIterator<Cont>::operator= (const ConstGeneralBidirectionalContainerIterator& source)
{
	NULL_REF_CHECK (source);

	if (this != &source) {
		ConstBidirectionalIterator<ValueType>::operator= (source);

		cont  = source.cont;
		state = source.state;
	}

	return *this;
}


template <class Cont>
void	ConstGeneralBidirectionalContainerIterator<Cont>::Assign (const IConstForwardIterator<ValueType>* /*source*/)
{
	// ConstGeneralBidirectionalContainerIterator contains own realization of the IConstBidirectionalterator interface
	// working on members in this class which are copied from the source iterator
}


template <class Cont>
inline ConstGeneralBidirectionalContainerIterator<Cont>&	ConstGeneralBidirectionalContainerIterator<Cont>::operator= (const GeneralBidirectionalContainerIterator<Cont>& source)
{
	NULL_REF_CHECK (source);

	if (this != static_cast<const void*> (&source)) {
		ConstBidirectionalIterator<ValueType>::operator= (source);

		cont  = source.cont;
		state = source.state;
	}

	return *this;
}


template <class Cont>
void	ConstGeneralBidirectionalContainerIterator<Cont>::Assign (const IForwardIterator<ValueType>* /*source*/)
{
	// ConstGeneralBidirectionalContainerIterator contains own realization of the IConstBidirectionalterator interface
	// working on members in this class which are copied from the source iterator
}


template <class Cont>
inline ConstGeneralBidirectionalContainerIterator<Cont>::~ConstGeneralBidirectionalContainerIterator ()
{
	this->target = nullptr;
}


template <class Cont>
inline const typename ConstGeneralBidirectionalContainerIterator<Cont>::ValueType&	ConstGeneralBidirectionalContainerIterator<Cont>::operator* () const
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	return cont->GetCurrent (state);
}


template <class Cont>
inline const typename ConstGeneralBidirectionalContainerIterator<Cont>::ValueType*	ConstGeneralBidirectionalContainerIterator<Cont>::operator-> () const
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	return &cont->GetCurrent (state);
}


template <class Cont>
inline ConstGeneralBidirectionalContainerIterator<Cont>&	ConstGeneralBidirectionalContainerIterator<Cont>::operator++ ()
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	cont->Increment (state);

	return *this;
}


template <class Cont>
inline ConstGeneralBidirectionalContainerIterator<Cont>		ConstGeneralBidirectionalContainerIterator<Cont>::operator++ (int)
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	ConstGeneralBidirectionalContainerIterator result = *this;

	cont->Increment (state);

	return result;
}


template <class Cont>
inline ConstGeneralBidirectionalContainerIterator<Cont>&	ConstGeneralBidirectionalContainerIterator<Cont>::operator-- ()
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsBegin (state));

	cont->Decrement (state);

	return *this;
}


template <class Cont>
inline ConstGeneralBidirectionalContainerIterator<Cont>		ConstGeneralBidirectionalContainerIterator<Cont>::operator-- (int)
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsBegin (state));

	ConstGeneralBidirectionalContainerIterator result = *this;

	cont->Decrement (state);

	return result;
}


template <class Cont>
inline bool		ConstGeneralBidirectionalContainerIterator<Cont>::operator== (const ConstGeneralBidirectionalContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (cont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.cont != nullptr);
	PRECOND_DEPRECATED (cont == rightOp.cont);

	return cont->IsEqual (state, rightOp.state);
}


template <class Cont>
inline bool		ConstGeneralBidirectionalContainerIterator<Cont>::operator!= (const ConstGeneralBidirectionalContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (cont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.cont != nullptr);
	PRECOND_DEPRECATED (cont == rightOp.cont);

	return !cont->IsEqual (state, rightOp.state);
}


template <class Cont>
inline bool		ConstGeneralBidirectionalContainerIterator<Cont>::operator== (std::nullptr_t) const
{
	PRECOND_DEPRECATED (cont != nullptr);

	return cont->IsEnd (state);
}


template <class Cont>
inline bool		ConstGeneralBidirectionalContainerIterator<Cont>::operator!= (std::nullptr_t) const
{
	PRECOND_DEPRECATED (cont != nullptr);

	return !cont->IsEnd (state);
}


template <class Cont>
inline const Cont*	ConstGeneralBidirectionalContainerIterator<Cont>::GetTarget (void) const
{
	return cont;
}


template <class Cont>
IConstBidirectionalIterator<typename ConstGeneralBidirectionalContainerIterator<Cont>::ValueType>*	ConstGeneralBidirectionalContainerIterator<Cont>::CreateClone (void) const
{
	return new ConstGeneralBidirectionalContainerIterator (*this);
}


template <class Cont>
const typename ConstGeneralBidirectionalContainerIterator<Cont>::ValueType&		ConstGeneralBidirectionalContainerIterator<Cont>::GetCurrent (void) const
{
	return operator* ();
}


template <class Cont>
void	ConstGeneralBidirectionalContainerIterator<Cont>::Increment (void)
{
	operator++ ();
}


template <class Cont>
void	ConstGeneralBidirectionalContainerIterator<Cont>::Decrement (void)
{
	operator-- ();
}


template <class Cont>
bool	ConstGeneralBidirectionalContainerIterator<Cont>::IsEqual (const IConstForwardIterator<ValueType>* rightOp) const
{
	NULL_PTR_CHECK (rightOp);

	const ConstGeneralBidirectionalContainerIterator* ro = dynamic_cast<const ConstGeneralBidirectionalContainerIterator*> (rightOp);
	TYPE_CHECK (ro != nullptr);

	return operator== (*ro);
}


template <class Cont>
bool	ConstGeneralBidirectionalContainerIterator<Cont>::IsEnd (void) const
{
	return operator== (nullptr);
}

}	// namespace GS


#endif
