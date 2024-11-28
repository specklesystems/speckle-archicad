
// *****************************************************************************
//
//                    Forward iterator interfaces and wrappers
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined FORWARDITERATOR_HPP
#define FORWARDITERATOR_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "IteratorBase.hpp"

#include "GSException.hpp"



// ======================== Interface IForwardIterator =========================

namespace GS {

template <class Type>
class IConstForwardIterator;

template <class Type>
class IForwardIterator {
public:
	virtual IForwardIterator*				CreateClone      (void) const = 0;
	virtual IConstForwardIterator<Type>*	CreateConstClone (void) const = 0;
	virtual ~IForwardIterator () {}

	virtual Type&	GetCurrent (void) const = 0;
	virtual void	Increment  (void) = 0;
	virtual bool	IsEqual	   (const IForwardIterator* rightOp) const = 0;
	virtual bool	IsEnd	   (void) const = 0;

	// -----------------------------------------------------------------------
	// Core operations to be implemented are:
	//
	//   CreateClone, CreateConstClone, GetCurrent, Increment, IsEqual, IsEnd
	// -----------------------------------------------------------------------
};

}	// namespace GS
// ________________________ Interface IForwardIterator _________________________



// =========================== Class ForwardIterator ===========================

namespace GS {

template <class Type>
class ConstForwardIterator;

template <class Type>
class ForwardIterator: public IteratorBase<Type> {
protected:
	IForwardIterator<Type>* target;	// target implementation of the wrapper

	friend class ConstForwardIterator<Type>;

	virtual void	Assign (const IForwardIterator<Type>* source);

public:
		// Constructors

	ForwardIterator (IForwardIterator<Type>* wrapperTarget);
	ForwardIterator (const ForwardIterator& source);

	ForwardIterator&	operator= (const ForwardIterator& source);

	~ForwardIterator ();

		// User interface

	Type&	operator*  () const;
	Type*	operator-> () const;

	ForwardIterator&	operator++ ();
	ForwardIterator		operator++ (int);

	bool		operator== (const ForwardIterator& rightOp) const;
	bool		operator!= (const ForwardIterator& rightOp) const;

	bool		operator== (std::nullptr_t) const;
	bool		operator!= (std::nullptr_t) const;
};



template <class Type>
ForwardIterator<Type>::ForwardIterator (IForwardIterator<Type>* wrapperTarget)
{
	NULL_PTR_CHECK (wrapperTarget);

	target = wrapperTarget;
}


template <class Type>
ForwardIterator<Type>::ForwardIterator (const ForwardIterator& source):
	IteratorBase<Type> (source)
{
	NULL_REF_CHECK (source);

	target = source.target->CreateClone ();
}


template <class Type>
ForwardIterator<Type>&	ForwardIterator<Type>::operator= (const ForwardIterator& source)
{
	NULL_REF_CHECK (source);

	if (this != &source) {
		IteratorBase<Type>::operator= (source);

		Assign (source.target);
	}

	return *this;
}


template <class Type>
void	ForwardIterator<Type>::Assign (const IForwardIterator<Type>* source)
{
	delete target;
	target = source->CreateClone ();
}


template <class Type>
ForwardIterator<Type>::~ForwardIterator ()
{
	delete target;
}


template <class Type>
Type&	ForwardIterator<Type>::operator* () const
{
	PRECOND_DEPRECATED (!target->IsEnd ());

	return target->GetCurrent ();
}


template <class Type>
Type*	ForwardIterator<Type>::operator-> () const
{
	PRECOND_DEPRECATED (!target->IsEnd ());

	return &target->GetCurrent ();
}


template <class Type>
ForwardIterator<Type>&	ForwardIterator<Type>::operator++ ()
{
	PRECOND_DEPRECATED (!target->IsEnd ());

	target->Increment ();

	return *this;
}


template <class Type>
ForwardIterator<Type>	ForwardIterator<Type>::operator++ (int)
{
	PRECOND_DEPRECATED (!target->IsEnd ());

	ForwardIterator result = *this;

	target->Increment ();

	return result;
}


template <class Type>
bool		ForwardIterator<Type>::operator== (const ForwardIterator& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	return target->IsEqual (rightOp.target);
}


template <class Type>
bool		ForwardIterator<Type>::operator!= (const ForwardIterator& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	return !target->IsEqual (rightOp.target);
}


template <class Type>
bool		ForwardIterator<Type>::operator== (std::nullptr_t) const
{
	return target->IsEnd ();
}


template <class Type>
bool		ForwardIterator<Type>::operator!= (std::nullptr_t) const
{
	return !target->IsEnd ();
}

}	// namespace GS
// ___________________________ Class ForwardIterator ___________________________



// ====================== Interface IConstForwardIterator ======================

namespace GS {

template <class Type>
class IConstForwardIterator {
public:
	virtual IConstForwardIterator*	CreateClone (void) const = 0;
	virtual ~IConstForwardIterator () {}

	virtual const Type&	GetCurrent (void) const = 0;
	virtual void		Increment  (void) = 0;
	virtual bool		IsEqual	   (const IConstForwardIterator* rightOp) const = 0;
	virtual bool		IsEnd	   (void) const = 0;

	// -----------------------------------------------------
	// Core operations to be implemented are:
	//
	//   CreateClone, GetCurrent, Increment, IsEqual, IsEnd
	// -----------------------------------------------------
};

}	// namespace GS
// ______________________ Interface IConstForwardIterator ______________________



// ======================== Class ConstForwardIterator =========================

namespace GS {

template <class Type>
class ConstForwardIterator: public IteratorBase<Type> {
protected:
	IConstForwardIterator<Type>* target;	// target implementation of the wrapper

	virtual void	Assign (const IConstForwardIterator<Type>* source);
	virtual void	Assign (const IForwardIterator<Type>* source);

public:
		// Constructors

	explicit ConstForwardIterator (IConstForwardIterator<Type>* wrapperTarget);
			 ConstForwardIterator (const ConstForwardIterator& source);
			 ConstForwardIterator (const ForwardIterator<Type>& source);

	ConstForwardIterator&	operator= (const ConstForwardIterator& source);
	ConstForwardIterator&	operator= (const ForwardIterator<Type>& source);

	~ConstForwardIterator ();

		// User interface

	const Type&		operator*  () const;
	const Type*		operator-> () const;

	ConstForwardIterator&	operator++ ();
	ConstForwardIterator	operator++ (int);

	bool		operator== (const ConstForwardIterator& rightOp) const;
	bool		operator!= (const ConstForwardIterator& rightOp) const;

	bool		operator== (std::nullptr_t) const;
	bool		operator!= (std::nullptr_t) const;
};



template <class Type>
ConstForwardIterator<Type>::ConstForwardIterator (IConstForwardIterator<Type>* wrapperTarget)
{
	NULL_PTR_CHECK (wrapperTarget);

	target = wrapperTarget;
}


template <class Type>
ConstForwardIterator<Type>::ConstForwardIterator (const ConstForwardIterator& source):
	IteratorBase<Type> (source)
{
	NULL_REF_CHECK (source);

	target = source.target->CreateClone ();
}


template <class Type>
ConstForwardIterator<Type>::ConstForwardIterator (const ForwardIterator<Type>& source):
	IteratorBase<Type> (source)
{
	NULL_REF_CHECK (source);

	target = source.target->CreateConstClone ();
}


template <class Type>
ConstForwardIterator<Type>&	ConstForwardIterator<Type>::operator= (const ConstForwardIterator& source)
{
	NULL_REF_CHECK (source);

	if (this != &source) {
		IteratorBase<Type>::operator= (source);

		Assign (source.target);
	}

	return *this;
}


template <class Type>
void	ConstForwardIterator<Type>::Assign (const IConstForwardIterator<Type>* source)
{
	delete target;
	target = source->CreateClone ();
}


template <class Type>
ConstForwardIterator<Type>&	ConstForwardIterator<Type>::operator= (const ForwardIterator<Type>& source)
{
	NULL_REF_CHECK (source);

	IteratorBase<Type>::operator= (source);

	Assign (source.target);

	return *this;
}


template <class Type>
void	ConstForwardIterator<Type>::Assign (const IForwardIterator<Type>* source)
{
	delete target;
	target = source->CreateConstClone ();
}


template <class Type>
ConstForwardIterator<Type>::~ConstForwardIterator ()
{
	delete target;
}


template <class Type>
const Type&		ConstForwardIterator<Type>::operator* () const
{
	PRECOND_DEPRECATED (!target->IsEnd ());

	return target->GetCurrent ();
}


template <class Type>
const Type*		ConstForwardIterator<Type>::operator-> () const
{
	PRECOND_DEPRECATED (!target->IsEnd ());

	return &target->GetCurrent ();
}


template <class Type>
ConstForwardIterator<Type>&		ConstForwardIterator<Type>::operator++ ()
{
	PRECOND_DEPRECATED (!target->IsEnd ());

	target->Increment ();

	return *this;
}


template <class Type>
ConstForwardIterator<Type>		ConstForwardIterator<Type>::operator++ (int)
{
	PRECOND_DEPRECATED (!target->IsEnd ());

	ConstForwardIterator result = *this;

	target->Increment ();

	return result;
}


template <class Type>
bool		ConstForwardIterator<Type>::operator== (const ConstForwardIterator& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	return target->IsEqual (rightOp.target);
}


template <class Type>
bool		ConstForwardIterator<Type>::operator!= (const ConstForwardIterator& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	return !target->IsEqual (rightOp.target);
}


template <class Type>
bool		ConstForwardIterator<Type>::operator== (std::nullptr_t) const
{
	return target->IsEnd ();
}


template <class Type>
bool		ConstForwardIterator<Type>::operator!= (std::nullptr_t) const
{
	return !target->IsEnd ();
}

}	// namespace GS
// ________________________ Class ConstForwardIterator _________________________


#endif
