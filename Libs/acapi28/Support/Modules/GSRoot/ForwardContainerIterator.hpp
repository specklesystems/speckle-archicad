
// *********************************************************************************************************************
//
//     Classes ForwardContainerIterator,
//			   ConstForwardContainerIterator,
//			   GeneralForwardContainerIterator,
//			   ConstGeneralForwardContainerIterator
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// Requirements:
//   Target container should have the following methods:
//     - Type&        GetCurrent (const State& state);          -> for non-const iterators
//     - const Type&  GetCurrent (const State& state) const;    -> for const iterators
//     - void         Increment  (State& state) const;
//     - bool         IsEqual    (const State& state1, const State& state2) const;
//     - bool         IsEnd      (const State& state) const;
//
// *********************************************************************************************************************


#if !defined FORWARDCONTAINERITERATOR_HPP
#define FORWARDCONTAINERITERATOR_HPP

#pragma once

// --- Includes --------------------------------------------------------------------------------------------------------

#include "ForwardIterator.hpp"



// === Class ForwardContainerIterator ==================================================================================

namespace GS {

template <class Cont, class State, class Type>
class ConstForwardContainerIterator;


template <class Cont, class State, class Type>
class ForwardContainerIterator {
private:
	Cont*	cont;	// target container iterator is connected to
	State	state;	// current state of the iterator

	friend class ConstForwardContainerIterator<Cont, State, Type>;

public:
	typedef Type ValueType;

		// Constructors

	inline ForwardContainerIterator ();
	inline ForwardContainerIterator (Cont& targetContainer, const State& initialState);
	inline ForwardContainerIterator (const ForwardContainerIterator& source);
	inline ForwardContainerIterator&	operator= (const ForwardContainerIterator& source);

		// User interface

	inline ValueType&					operator*  () const;
	inline ValueType*					operator-> () const;

	inline ForwardContainerIterator&	operator++ ();
	inline ForwardContainerIterator		operator++ (int);

	inline bool							operator== (const ForwardContainerIterator& rightOp) const;
	inline bool							operator!= (const ForwardContainerIterator& rightOp) const;

	inline bool							operator== (std::nullptr_t) const;
	inline bool							operator!= (std::nullptr_t) const;
};

}	// namespace GS



// === Class ConstForwardContainerIterator =============================================================================

namespace GS {

template <class Cont, class State, class Type>
class ConstForwardContainerIterator {
	template <class C, class S, class T> friend class ConstForwardContainerIterator;

private:
	const Cont*	cont;	// target container iterator is connected to
	State		state;	// current state of the iterator

public:
	typedef Type ValueType;

		// Constructors

	inline ConstForwardContainerIterator ();
	inline ConstForwardContainerIterator (const Cont& targetContainer, const State& initialState);
	inline ConstForwardContainerIterator (const ConstForwardContainerIterator& source);
	inline ConstForwardContainerIterator (const ForwardContainerIterator<Cont, State, Type>& source);
	template <class SourceState, class SourceType> inline ConstForwardContainerIterator (const ConstForwardContainerIterator<Cont, SourceState, SourceType>& source);
	inline ConstForwardContainerIterator&	operator= (const ConstForwardContainerIterator& source);
	inline ConstForwardContainerIterator&	operator= (const ForwardContainerIterator<Cont, State, Type>& source);
	template <class SourceState, class SourceType> inline ConstForwardContainerIterator& operator= (const ConstForwardContainerIterator<Cont, SourceState, SourceType>& source);

		// User interface

	inline const ValueType&					operator*  () const;
	inline const ValueType*					operator-> () const;

	inline ConstForwardContainerIterator&	operator++ ();
	inline ConstForwardContainerIterator	operator++ (int);

	inline bool								operator== (const ConstForwardContainerIterator& rightOp) const;
	inline bool								operator!= (const ConstForwardContainerIterator& rightOp) const;

	inline bool								operator== (std::nullptr_t) const;
	inline bool								operator!= (std::nullptr_t) const;
};

}	// namespace GS



// === Class GeneralForwardContainerIterator ===========================================================================

namespace GS {

template <class Cont, class State, class Type>
class ConstGeneralForwardContainerIterator;


template <class Cont, class State, class Type>
class GeneralForwardContainerIterator: public ForwardIterator<Type>,
									   public IForwardIterator<Type>
{
private:
	Cont*	cont;	// target container iterator is connected to
	State	state;	// current state of the iterator

	inline IForwardIterator<Type>*	GetIteratorInterface (void) { return this; }

	friend class ConstGeneralForwardContainerIterator<Cont, State, Type>;

protected:
	virtual void	Assign (const IForwardIterator<Type>* source) override;

	virtual IForwardIterator<Type>*			CreateClone      (void) const override;
	virtual IConstForwardIterator<Type>*	CreateConstClone (void) const override;

	virtual Type&	GetCurrent (void) const override;
	virtual void	Increment  (void) override;
	virtual bool	IsEqual	   (const IForwardIterator<Type>* rightOp) const override;
	virtual bool	IsEnd	   (void) const override;

public:
		// Constructors

	inline GeneralForwardContainerIterator ();
	inline GeneralForwardContainerIterator (Cont& targetContainer, const State& initialState);
	inline GeneralForwardContainerIterator (const GeneralForwardContainerIterator& source);
	inline GeneralForwardContainerIterator&	operator= (const GeneralForwardContainerIterator& source);
	inline ~GeneralForwardContainerIterator ();

		// User interface

	inline Type&							operator*  () const;
	inline Type*							operator-> () const;

	inline GeneralForwardContainerIterator&	operator++ ();
	inline GeneralForwardContainerIterator	operator++ (int);

	inline bool								operator== (const GeneralForwardContainerIterator& rightOp) const;
	inline bool								operator!= (const GeneralForwardContainerIterator& rightOp) const;

	inline bool								operator== (std::nullptr_t) const;
	inline bool								operator!= (std::nullptr_t) const;

	inline Cont*							GetTarget (void) const;
};

}	// namespace GS



// === Class ConstGeneralForwardContainerIterator ======================================================================

namespace GS {

template <class Cont, class State, class Type>
class ConstGeneralForwardContainerIterator: public ConstForwardIterator<Type>,
											public IConstForwardIterator<Type>
{
private:
	const Cont*	cont;	// target container iterator is connected to
	State		state;	// current state of the iterator

	inline IConstForwardIterator<Type>*		GetIteratorInterface (void) { return this; }

protected:
	virtual void	Assign (const IConstForwardIterator<Type>* source) override;
	virtual void	Assign (const IForwardIterator<Type>* source) override;

	virtual IConstForwardIterator<Type>*	CreateClone (void) const override;

	virtual const Type&	GetCurrent (void) const override;
	virtual void		Increment  (void) override;
	virtual bool		IsEqual	   (const IConstForwardIterator<Type>* rightOp) const override;
	virtual bool		IsEnd	   (void) const override;
public:
		// Constructors

	inline ConstGeneralForwardContainerIterator ();
	inline ConstGeneralForwardContainerIterator (const Cont& targetContainer, const State& initialState);
	inline ConstGeneralForwardContainerIterator (const ConstGeneralForwardContainerIterator& source);
	inline ConstGeneralForwardContainerIterator (const GeneralForwardContainerIterator<Cont, State, Type>& source);
	inline ConstGeneralForwardContainerIterator&	operator= (const ConstGeneralForwardContainerIterator& source);
	inline ConstGeneralForwardContainerIterator&	operator= (const GeneralForwardContainerIterator<Cont, State, Type>& source);
	inline ~ConstGeneralForwardContainerIterator ();

		// User interface

	inline const Type&								operator*  () const;
	inline const Type*								operator-> () const;

	inline ConstGeneralForwardContainerIterator&	operator++ ();
	inline ConstGeneralForwardContainerIterator		operator++ (int);

	inline bool										operator== (const ConstGeneralForwardContainerIterator& rightOp) const;
	inline bool										operator!= (const ConstGeneralForwardContainerIterator& rightOp) const;

	inline bool										operator== (std::nullptr_t) const;
	inline bool										operator!= (std::nullptr_t) const;

	inline const Cont*								GetTarget (void) const;
};

}	// namespace GS



// === Class ForwardContainerIterator ==================================================================================

namespace GS {

template <class Cont, class State, class Type>
inline ForwardContainerIterator<Cont, State, Type>::ForwardContainerIterator ():
	cont (nullptr)
{
}


template <class Cont, class State, class Type>
inline ForwardContainerIterator<Cont, State, Type>::ForwardContainerIterator (Cont& targetContainer, const State& initialState):
	cont  (&targetContainer),
	state (initialState)
{
	NULL_REF_CHECK (targetContainer);
	NULL_REF_CHECK (initialState);
}


template <class Cont, class State, class Type>
inline ForwardContainerIterator<Cont, State, Type>::ForwardContainerIterator (const ForwardContainerIterator& source):
	cont  (source.cont),
	state (source.state)
{
	NULL_REF_CHECK (source);
}


template <class Cont, class State, class Type>
inline ForwardContainerIterator<Cont, State, Type>&		ForwardContainerIterator<Cont, State, Type>::operator= (const ForwardContainerIterator& source)
{
	NULL_REF_CHECK (source);

	if (this != &source) {
		cont   = source.cont;
		state  = source.state;
	}

	return *this;
}


template <class Cont, class State, class Type>
inline typename ForwardContainerIterator<Cont, State, Type>::ValueType&		ForwardContainerIterator<Cont, State, Type>::operator* () const
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	return cont->GetCurrent (state);
}


template <class Cont, class State, class Type>
inline typename ForwardContainerIterator<Cont, State, Type>::ValueType*		ForwardContainerIterator<Cont, State, Type>::operator-> () const
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	return &cont->GetCurrent (state);
}


template <class Cont, class State, class Type>
inline ForwardContainerIterator<Cont, State, Type>&		ForwardContainerIterator<Cont, State, Type>::operator++ ()
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	cont->Increment (state);

	return *this;
}


template <class Cont, class State, class Type>
inline ForwardContainerIterator<Cont, State, Type>	ForwardContainerIterator<Cont, State, Type>::operator++ (int)
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	ForwardContainerIterator result = *this;

	cont->Increment (state);

	return result;
}


template <class Cont, class State, class Type>
inline bool		ForwardContainerIterator<Cont, State, Type>::operator== (const ForwardContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (cont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.cont != nullptr);
	PRECOND_DEPRECATED (cont == rightOp.cont);

	return cont->IsEqual (state, rightOp.state);
}


template <class Cont, class State, class Type>
inline bool		ForwardContainerIterator<Cont, State, Type>::operator!= (const ForwardContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (cont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.cont != nullptr);
	PRECOND_DEPRECATED (cont == rightOp.cont);

	return !cont->IsEqual (state, rightOp.state);
}


template <class Cont, class State, class Type>
inline bool		ForwardContainerIterator<Cont, State, Type>::operator== (std::nullptr_t) const
{
	PRECOND_DEPRECATED (cont != nullptr);

	return cont->IsEnd (state);
}


template <class Cont, class State, class Type>
inline bool		ForwardContainerIterator<Cont, State, Type>::operator!= (std::nullptr_t) const
{
	PRECOND_DEPRECATED (cont != nullptr);

	return !cont->IsEnd (state);
}

}	// namespace GS



// === Class ConstForwardContainerIterator =============================================================================

namespace GS {

template <class Cont, class State, class Type>
inline ConstForwardContainerIterator<Cont, State, Type>::ConstForwardContainerIterator ():
	cont (nullptr)
{
}


template <class Cont, class State, class Type>
inline ConstForwardContainerIterator<Cont, State, Type>::ConstForwardContainerIterator (const Cont& targetContainer, const State& initialState):
	cont  (&targetContainer),
	state (initialState)
{
	NULL_REF_CHECK (targetContainer);
	NULL_REF_CHECK (initialState);
}


template <class Cont, class State, class Type>
inline ConstForwardContainerIterator<Cont, State, Type>::ConstForwardContainerIterator (const ConstForwardContainerIterator& source):
	cont  (source.cont),
	state (source.state)
{
	NULL_REF_CHECK (source);
}


template <class Cont, class State, class Type>
inline ConstForwardContainerIterator<Cont, State, Type>::ConstForwardContainerIterator (const ForwardContainerIterator<Cont, State, Type>& source):
	cont  (source.cont),
	state (source.state)
{
	NULL_REF_CHECK (source);
}


template <class Cont, class State, class Type>
template <class SourceState, class SourceType>
inline ConstForwardContainerIterator<Cont, State, Type>::ConstForwardContainerIterator (const ConstForwardContainerIterator<Cont, SourceState, SourceType>& source):
	cont  (source.cont),
	state (source.state)
{
	NULL_REF_CHECK (source);
}


template <class Cont, class State, class Type>
inline ConstForwardContainerIterator<Cont, State, Type>&	ConstForwardContainerIterator<Cont, State, Type>::operator= (const ConstForwardContainerIterator& source)
{
	NULL_REF_CHECK (source);

	if (this != &source) {
		cont  = source.cont;
		state = source.state;
	}

	return *this;
}


template <class Cont, class State, class Type>
inline ConstForwardContainerIterator<Cont, State, Type>&	ConstForwardContainerIterator<Cont, State, Type>::operator= (const ForwardContainerIterator<Cont, State, Type>& source)
{
	NULL_REF_CHECK (source);

	if (this != static_cast<const void*> (&source)) {
		cont  = source.cont;
		state = source.state;
	}

	return *this;
}


template <class Cont, class State, class Type>
template <class SourceState, class SourceType>
inline ConstForwardContainerIterator<Cont, State, Type>&	ConstForwardContainerIterator<Cont, State, Type>::operator= (const ConstForwardContainerIterator<Cont, SourceState, SourceType>& source)
{
	NULL_REF_CHECK (source);

	if (this != static_cast<const void*> (&source)) {
		cont  = source.cont;
		state = source.state;
	}

	return *this;
}


template <class Cont, class State, class Type>
inline const typename ConstForwardContainerIterator<Cont, State, Type>::ValueType&	ConstForwardContainerIterator<Cont, State, Type>::operator* () const
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	return cont->GetCurrent (state);
}


template <class Cont, class State, class Type>
inline const typename ConstForwardContainerIterator<Cont, State, Type>::ValueType*	ConstForwardContainerIterator<Cont, State, Type>::operator-> () const
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	return &cont->GetCurrent (state);
}


template <class Cont, class State, class Type>
inline ConstForwardContainerIterator<Cont, State, Type>&	ConstForwardContainerIterator<Cont, State, Type>::operator++ ()
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	cont->Increment (state);

	return *this;
}


template <class Cont, class State, class Type>
inline ConstForwardContainerIterator<Cont, State, Type>		ConstForwardContainerIterator<Cont, State, Type>::operator++ (int)
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	ConstForwardContainerIterator result = *this;

	cont->Increment (state);

	return result;
}


template <class Cont, class State, class Type>
inline bool		ConstForwardContainerIterator<Cont, State, Type>::operator== (const ConstForwardContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (cont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.cont != nullptr);
	PRECOND_DEPRECATED (cont == rightOp.cont);

	return cont->IsEqual (state, rightOp.state);
}


template <class Cont, class State, class Type>
inline bool		ConstForwardContainerIterator<Cont, State, Type>::operator!= (const ConstForwardContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (cont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.cont != nullptr);
	PRECOND_DEPRECATED (cont == rightOp.cont);

	return !cont->IsEqual (state, rightOp.state);
}


template <class Cont, class State, class Type>
inline bool		ConstForwardContainerIterator<Cont, State, Type>::operator== (std::nullptr_t) const
{
	PRECOND_DEPRECATED (cont != nullptr);

	return cont->IsEnd (state);
}


template <class Cont, class State, class Type>
inline bool		ConstForwardContainerIterator<Cont, State, Type>::operator!= (std::nullptr_t) const
{
	PRECOND_DEPRECATED (cont != nullptr);

	return !cont->IsEnd (state);
}

}	// namespace GS



// === Class GeneralForwardContainerIterator ===========================================================================

namespace GS {

template <class Cont, class State, class Type>
inline GeneralForwardContainerIterator<Cont, State, Type>::GeneralForwardContainerIterator ():
	ForwardIterator<Type> (GetIteratorInterface ()),
	cont (nullptr)
{
}


template <class Cont, class State, class Type>
inline GeneralForwardContainerIterator<Cont, State, Type>::GeneralForwardContainerIterator (Cont& targetContainer, const State& initialState):
	ForwardIterator<Type> (GetIteratorInterface ()),
	cont  (&targetContainer),
	state (initialState)
{
	NULL_REF_CHECK (targetContainer);
	NULL_REF_CHECK (initialState);
}


template <class Cont, class State, class Type>
inline GeneralForwardContainerIterator<Cont, State, Type>::GeneralForwardContainerIterator (const GeneralForwardContainerIterator& source):
	ForwardIterator<Type> (GetIteratorInterface ()),
	cont  (source.cont),
	state (source.state)
{
	NULL_REF_CHECK (source);
}


template <class Cont, class State, class Type>
inline GeneralForwardContainerIterator<Cont, State, Type>&	GeneralForwardContainerIterator<Cont, State, Type>::operator= (const GeneralForwardContainerIterator& source)
{
	NULL_REF_CHECK (source);

	if (this != &source) {
		ForwardIterator<Type>::operator= (source);

		cont   = source.cont;
		state  = source.state;
	}

	return *this;
}


template <class Cont, class State, class Type>
void	GeneralForwardContainerIterator<Cont, State, Type>::Assign (const IForwardIterator<Type>* /*source*/)
{
	// GeneralForwardContainerIterator contains own realization of the IForwardterator interface
	// working on members in this class which are copied from the source iterator
}


template <class Cont, class State, class Type>
inline GeneralForwardContainerIterator<Cont, State, Type>::~GeneralForwardContainerIterator ()
{
	this->target = nullptr;
}


template <class Cont, class State, class Type>
inline Type&	GeneralForwardContainerIterator<Cont, State, Type>::operator* () const
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	return cont->GetCurrent (state);
}


template <class Cont, class State, class Type>
inline Type*	GeneralForwardContainerIterator<Cont, State, Type>::operator-> () const
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	return &cont->GetCurrent (state);
}


template <class Cont, class State, class Type>
inline GeneralForwardContainerIterator<Cont, State, Type>&	GeneralForwardContainerIterator<Cont, State, Type>::operator++ ()
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	cont->Increment (state);

	return *this;
}


template <class Cont, class State, class Type>
inline GeneralForwardContainerIterator<Cont, State, Type>	GeneralForwardContainerIterator<Cont, State, Type>::operator++ (int)
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	GeneralForwardContainerIterator result = *this;

	cont->Increment (state);

	return result;
}


template <class Cont, class State, class Type>
inline bool		GeneralForwardContainerIterator<Cont, State, Type>::operator== (const GeneralForwardContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (cont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.cont != nullptr);
	PRECOND_DEPRECATED (cont == rightOp.cont);

	return cont->IsEqual (state, rightOp.state);
}


template <class Cont, class State, class Type>
inline bool		GeneralForwardContainerIterator<Cont, State, Type>::operator!= (const GeneralForwardContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (cont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.cont != nullptr);
	PRECOND_DEPRECATED (cont == rightOp.cont);

	return !cont->IsEqual (state, rightOp.state);
}


template <class Cont, class State, class Type>
inline bool		GeneralForwardContainerIterator<Cont, State, Type>::operator== (std::nullptr_t) const
{
	PRECOND_DEPRECATED (cont != nullptr);

	return cont->IsEnd (state);
}


template <class Cont, class State, class Type>
inline bool		GeneralForwardContainerIterator<Cont, State, Type>::operator!= (std::nullptr_t) const
{
	PRECOND_DEPRECATED (cont != nullptr);

	return !cont->IsEnd (state);
}


template <class Cont, class State, class Type>
inline Cont*	GeneralForwardContainerIterator<Cont, State, Type>::GetTarget (void) const
{
	return cont;
}


template <class Cont, class State, class Type>
IForwardIterator<Type>*		GeneralForwardContainerIterator<Cont, State, Type>::CreateClone (void) const
{
	return new GeneralForwardContainerIterator (*this);
}


template <class Cont, class State, class Type>
IConstForwardIterator<Type>*	GeneralForwardContainerIterator<Cont, State, Type>::CreateConstClone (void) const
{
	return new ConstGeneralForwardContainerIterator<Cont, State, Type> (*this);
}


template <class Cont, class State, class Type>
Type&	GeneralForwardContainerIterator<Cont, State, Type>::GetCurrent (void) const
{
	return operator* ();
}


template <class Cont, class State, class Type>
void	GeneralForwardContainerIterator<Cont, State, Type>::Increment (void)
{
	operator++ ();
}


template <class Cont, class State, class Type>
bool	GeneralForwardContainerIterator<Cont, State, Type>::IsEqual (const IForwardIterator<Type>* rightOp) const
{
	NULL_PTR_CHECK (rightOp);

	const GeneralForwardContainerIterator* ro = dynamic_cast<const GeneralForwardContainerIterator*> (rightOp);
	TYPE_CHECK (ro != nullptr);

	return operator== (*ro);
}


template <class Cont, class State, class Type>
bool	GeneralForwardContainerIterator<Cont, State, Type>::IsEnd (void) const
{
	return operator== (nullptr);
}

}	// namespace GS



// === Class ConstGeneralForwardContainerIterator ======================================================================

namespace GS {

template <class Cont, class State, class Type>
inline ConstGeneralForwardContainerIterator<Cont, State, Type>::ConstGeneralForwardContainerIterator ():
	ConstForwardIterator<Type> (GetIteratorInterface ()),
	cont (nullptr)
{
}


template <class Cont, class State, class Type>
inline ConstGeneralForwardContainerIterator<Cont, State, Type>::ConstGeneralForwardContainerIterator (const Cont& targetContainer, const State& initialState):
	ConstForwardIterator<Type> (GetIteratorInterface ()),
	cont  (&targetContainer),
	state (initialState)
{
	NULL_REF_CHECK (targetContainer);
	NULL_REF_CHECK (initialState);
}


template <class Cont, class State, class Type>
inline ConstGeneralForwardContainerIterator<Cont, State, Type>::ConstGeneralForwardContainerIterator (const ConstGeneralForwardContainerIterator& source):
	ConstForwardIterator<Type> (GetIteratorInterface ()),
	cont  (source.cont),
	state (source.state)
{
	NULL_REF_CHECK (source);
}


template <class Cont, class State, class Type>
inline ConstGeneralForwardContainerIterator<Cont, State, Type>::ConstGeneralForwardContainerIterator (const GeneralForwardContainerIterator<Cont, State, Type>& source):
	ConstForwardIterator<Type> (GetIteratorInterface ()),
	cont  (source.cont),
	state (source.state)
{
	NULL_REF_CHECK (source);
}


template <class Cont, class State, class Type>
inline ConstGeneralForwardContainerIterator<Cont, State, Type>&		ConstGeneralForwardContainerIterator<Cont, State, Type>::operator= (const ConstGeneralForwardContainerIterator& source)
{
	NULL_REF_CHECK (source);

	if (this != &source) {
		ConstForwardIterator<Type>::operator= (source);

		cont  = source.cont;
		state = source.state;
	}

	return *this;
}


template <class Cont, class State, class Type>
void	ConstGeneralForwardContainerIterator<Cont, State, Type>::Assign (const IConstForwardIterator<Type>* /*source*/)
{
	// ConstGeneralForwardContainerIterator contains own realization of the IConstForwardterator interface
	// working on members in this class which are copied from the source iterator
}


template <class Cont, class State, class Type>
inline ConstGeneralForwardContainerIterator<Cont, State, Type>&		ConstGeneralForwardContainerIterator<Cont, State, Type>::operator= (const GeneralForwardContainerIterator<Cont, State, Type>& source)
{
	NULL_REF_CHECK (source);

	if (this != static_cast<const void*> (&source)) {
		ConstForwardIterator<Type>::operator= (source);

		cont  = source.cont;
		state = source.state;
	}

	return *this;
}


template <class Cont, class State, class Type>
void	ConstGeneralForwardContainerIterator<Cont, State, Type>::Assign (const IForwardIterator<Type>* /*source*/)
{
	// ConstGeneralForwardContainerIterator contains own realization of the IConstForwardterator interface
	// working on members in this class which are copied from the source iterator
}


template <class Cont, class State, class Type>
inline ConstGeneralForwardContainerIterator<Cont, State, Type>::~ConstGeneralForwardContainerIterator ()
{
	this->target = nullptr;
}


template <class Cont, class State, class Type>
inline const Type&	ConstGeneralForwardContainerIterator<Cont, State, Type>::operator* () const
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	return cont->GetCurrent (state);
}


template <class Cont, class State, class Type>
inline const Type*	ConstGeneralForwardContainerIterator<Cont, State, Type>::operator-> () const
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	return &cont->GetCurrent (state);
}


template <class Cont, class State, class Type>
inline ConstGeneralForwardContainerIterator<Cont, State, Type>&		ConstGeneralForwardContainerIterator<Cont, State, Type>::operator++ ()
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	cont->Increment (state);

	return *this;
}


template <class Cont, class State, class Type>
inline ConstGeneralForwardContainerIterator<Cont, State, Type>	ConstGeneralForwardContainerIterator<Cont, State, Type>::operator++ (int)
{
	PRECOND_DEPRECATED (cont != nullptr);
	PRECOND_DEPRECATED (!cont->IsEnd (state));

	ConstGeneralForwardContainerIterator result = *this;

	cont->Increment (state);

	return result;
}


template <class Cont, class State, class Type>
inline bool		ConstGeneralForwardContainerIterator<Cont, State, Type>::operator== (const ConstGeneralForwardContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (cont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.cont != nullptr);
	PRECOND_DEPRECATED (cont == rightOp.cont);

	return cont->IsEqual (state, rightOp.state);
}


template <class Cont, class State, class Type>
inline bool		ConstGeneralForwardContainerIterator<Cont, State, Type>::operator!= (const ConstGeneralForwardContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (cont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.cont != nullptr);
	PRECOND_DEPRECATED (cont == rightOp.cont);

	return !cont->IsEqual (state, rightOp.state);
}


template <class Cont, class State, class Type>
inline bool		ConstGeneralForwardContainerIterator<Cont, State, Type>::operator== (std::nullptr_t) const
{
	PRECOND_DEPRECATED (cont != nullptr);

	return cont->IsEnd (state);
}


template <class Cont, class State, class Type>
inline bool		ConstGeneralForwardContainerIterator<Cont, State, Type>::operator!= (std::nullptr_t) const
{
	PRECOND_DEPRECATED (cont != nullptr);

	return !cont->IsEnd (state);
}


template <class Cont, class State, class Type>
inline const Cont*	ConstGeneralForwardContainerIterator<Cont, State, Type>::GetTarget (void) const
{
	return cont;
}


template <class Cont, class State, class Type>
IConstForwardIterator<Type>*	ConstGeneralForwardContainerIterator<Cont, State, Type>::CreateClone (void) const
{
	return new ConstGeneralForwardContainerIterator (*this);
}


template <class Cont, class State, class Type>
const Type&		ConstGeneralForwardContainerIterator<Cont, State, Type>::GetCurrent (void) const
{
	return operator* ();
}


template <class Cont, class State, class Type>
void	ConstGeneralForwardContainerIterator<Cont, State, Type>::Increment (void)
{
	operator++ ();
}


template <class Cont, class State, class Type>
bool	ConstGeneralForwardContainerIterator<Cont, State, Type>::IsEqual (const IConstForwardIterator<Type>* rightOp) const
{
	NULL_PTR_CHECK (rightOp);

	const ConstGeneralForwardContainerIterator* ro = dynamic_cast<const ConstGeneralForwardContainerIterator*> (rightOp);
	TYPE_CHECK (ro != nullptr);

	return operator== (*ro);
}


template <class Cont, class State, class Type>
bool	ConstGeneralForwardContainerIterator<Cont, State, Type>::IsEnd (void) const
{
	return operator== (nullptr);
}

}	// namespace GS


#endif
