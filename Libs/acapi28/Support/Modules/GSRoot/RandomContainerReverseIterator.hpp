
// *****************************************************************************
//
//       Classes RandomContainerReverseIterator and ConstRandomContainerReverseIterator
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB, PP
//
// SG compatible
//
// Requirements:
//   Target random container should have conventional operator[] and GetSize
//   operations and type ValueType.
//
// *****************************************************************************


#if !defined RANDOMCONTAINERREVERSEITERATOR_HPP
#define RANDOMCONTAINERREVERSEITERATOR_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "RandomIterator.hpp"



// ======================= Class RandomContainerReverseIterator =======================

namespace GS {

template <class RndCont>
class ConstRandomContainerReverseIterator;

template <class RndCont>
class RandomContainerReverseIterator:	public RandomIterator<typename RndCont::ValueType>,
										public IRandomIterator<typename RndCont::ValueType>
{
public:
	typedef typename RandomIterator<typename RndCont::ValueType>::ValueType	ValueType;	// repeated because of Mac

private:
	RndCont*	rndCont;	// target random container iterator is connected to
	Int32		current;	// index of the current item in the random container

	inline bool		CheckType (const RandomContainerReverseIterator& rightOp) const;

	inline IRandomIterator<ValueType>*	GetIteratorInterface (void) { return this; }

	friend class ConstRandomContainerReverseIterator<RndCont>;

protected:
	virtual void	Assign (const IForwardIterator<ValueType>* source) override;

	virtual IForwardIterator<ValueType>*		CreateClone      (void) const override;
	virtual IConstForwardIterator<ValueType>*	CreateConstClone (void) const override;

	virtual bool		IsEnd (void) const override;

	virtual ValueType&	Get (IteratorOffset offset) const override;

	virtual void		Add (IteratorOffset offset) override;

	virtual IteratorOffset	GetDifference (const IRandomIterator<ValueType>* rightOp) const override;

public:
		// Constructors

	inline RandomContainerReverseIterator ();
	inline RandomContainerReverseIterator (RndCont& target, Int32 idx);
	inline RandomContainerReverseIterator (const RandomContainerReverseIterator& source);
	inline RandomContainerReverseIterator&		operator= (const RandomContainerReverseIterator& source);
	inline ~RandomContainerReverseIterator ();

		// User interface

	inline ValueType&	operator*  () const;
	inline ValueType*	operator-> () const;
	inline ValueType&	operator[] (IteratorOffset offset) const;

	inline RandomContainerReverseIterator&	operator++ ();
	inline RandomContainerReverseIterator	operator++ (int);

	inline RandomContainerReverseIterator&	operator-- ();
	inline RandomContainerReverseIterator	operator-- (int);

	inline RandomContainerReverseIterator	operator+  (IteratorOffset offset) const;
	inline RandomContainerReverseIterator	operator-  (IteratorOffset offset) const;
	inline IteratorOffset					operator-  (const RandomContainerReverseIterator& rightOp) const;
	inline RandomContainerReverseIterator&	operator+= (IteratorOffset offset);
	inline RandomContainerReverseIterator&	operator-= (IteratorOffset offset);

	inline bool		operator== (const RandomContainerReverseIterator& rightOp) const;
	inline bool		operator!= (const RandomContainerReverseIterator& rightOp) const;
	inline bool		operator<  (const RandomContainerReverseIterator& rightOp) const;
	inline bool		operator<= (const RandomContainerReverseIterator& rightOp) const;
	inline bool		operator>  (const RandomContainerReverseIterator& rightOp) const;
	inline bool		operator>= (const RandomContainerReverseIterator& rightOp) const;

	inline bool		operator== (std::nullptr_t) const;
	inline bool		operator!= (std::nullptr_t) const;

	inline RndCont*	GetTarget (void) const;
	inline Int32	GetIndex  (void) const;
};

}	// namespace GS
// _______________________ Class RandomContainerReverseIterator _______________________



// ==================== Class ConstRandomContainerReverseIterator =====================

namespace GS {

template <class RndCont>
class ConstRandomContainerReverseIterator:	public ConstRandomIterator<typename RndCont::ValueType>,
											public IConstRandomIterator<typename RndCont::ValueType>
{
public:
	typedef typename ConstRandomIterator<typename RndCont::ValueType>::ValueType	ValueType;	// repeated because of Mac

private:
	const RndCont*	rndCont;	// target random container iterator is connected to
	Int32			current;	// index of the current item in the random container

	inline bool		CheckType (const ConstRandomContainerReverseIterator& rightOp) const;

	inline IConstRandomIterator<ValueType>*		GetIteratorInterface (void) { return this; }

protected:
	virtual void	Assign (const IConstForwardIterator<ValueType>* source) override;
	virtual void	Assign (const IForwardIterator<ValueType>* source) override;

	virtual IConstForwardIterator<ValueType>*	CreateClone (void) const override;

	virtual bool	IsEnd (void) const override;

	virtual const ValueType&	Get (IteratorOffset offset) const override;

	virtual void	Add (IteratorOffset offset) override;

	virtual IteratorOffset	GetDifference (const IConstRandomIterator<ValueType>* rightOp) const override;

public:
		// Constructors

	inline ConstRandomContainerReverseIterator ();
	inline ConstRandomContainerReverseIterator (const RndCont& target, Int32 idx);
	inline ConstRandomContainerReverseIterator (const ConstRandomContainerReverseIterator& source);
	inline ConstRandomContainerReverseIterator (const RandomContainerReverseIterator<RndCont>& source);
	inline ConstRandomContainerReverseIterator&	operator= (const ConstRandomContainerReverseIterator& source);
	inline ConstRandomContainerReverseIterator&	operator= (const RandomContainerReverseIterator<RndCont>& source);
	inline ~ConstRandomContainerReverseIterator ();

		// User interface

	inline const ValueType&		operator*  () const;
	inline const ValueType*		operator-> () const;
	inline const ValueType&		operator[] (IteratorOffset offset) const;

	inline ConstRandomContainerReverseIterator&	operator++ ();
	inline ConstRandomContainerReverseIterator	operator++ (int);

	inline ConstRandomContainerReverseIterator&	operator-- ();
	inline ConstRandomContainerReverseIterator	operator-- (int);

	inline ConstRandomContainerReverseIterator	operator+  (IteratorOffset offset) const;
	inline ConstRandomContainerReverseIterator	operator-  (IteratorOffset offset) const;
	inline IteratorOffset						operator-  (const ConstRandomContainerReverseIterator& rightOp) const;
	inline ConstRandomContainerReverseIterator&	operator+= (IteratorOffset offset);
	inline ConstRandomContainerReverseIterator&	operator-= (IteratorOffset offset);

	inline bool		operator== (const ConstRandomContainerReverseIterator& rightOp) const;
	inline bool		operator!= (const ConstRandomContainerReverseIterator& rightOp) const;
	inline bool		operator<  (const ConstRandomContainerReverseIterator& rightOp) const;
	inline bool		operator<= (const ConstRandomContainerReverseIterator& rightOp) const;
	inline bool		operator>  (const ConstRandomContainerReverseIterator& rightOp) const;
	inline bool		operator>= (const ConstRandomContainerReverseIterator& rightOp) const;

	inline bool		operator== (std::nullptr_t) const;
	inline bool		operator!= (std::nullptr_t) const;

	inline const RndCont*	GetTarget (void) const;
	inline Int32			GetIndex (void) const;
};

}	// namespace GS
// ____________________ Class ConstRandomContainerReverseIterator _____________________



// ======================= Class RandomContainerReverseIterator =======================

namespace GS {

template <class RndCont>
inline RandomContainerReverseIterator<RndCont>::RandomContainerReverseIterator ():
	RandomIterator<typename RandomContainerReverseIterator<RndCont>::ValueType> (GetIteratorInterface ()),
	rndCont (nullptr),
	current (0)
{
}


template <class RndCont>
inline RandomContainerReverseIterator<RndCont>::RandomContainerReverseIterator (RndCont& target_, Int32 idx):
	RandomIterator<typename RandomContainerReverseIterator<RndCont>::ValueType> (GetIteratorInterface ()),
	rndCont (&target_),
	current (idx)
{
	NULL_REF_CHECK (target_);
	REF_CHECK (idx < Int32 (target_.GetSize ()) && idx >= -1);
}


template <class RndCont>
inline RandomContainerReverseIterator<RndCont>::RandomContainerReverseIterator (const RandomContainerReverseIterator& source):
	RandomIterator<typename RandomContainerReverseIterator<RndCont>::ValueType> (GetIteratorInterface ()),
	rndCont (source.rndCont),
	current (source.current)
{
	NULL_REF_CHECK (source);
}


template <class RndCont>
inline RandomContainerReverseIterator<RndCont>&	RandomContainerReverseIterator<RndCont>::operator= (const RandomContainerReverseIterator& source)
{
	NULL_REF_CHECK (source);

	if (this != &source) {
		RandomIterator<ValueType>::operator= (source);

		rndCont = source.rndCont;
		current = source.current;
	}

	return *this;
}


template <class RndCont>
void	RandomContainerReverseIterator<RndCont>::Assign (const IForwardIterator<ValueType>* /*source*/)
{
	// RandomContainerReverseIterator contains own realization of the IRandomIterator interface
	// working on members in this class which are copied from the source iterator
}


template <class RndCont>
inline RandomContainerReverseIterator<RndCont>::~RandomContainerReverseIterator ()
{
	this->target = nullptr;
}


template <class RndCont>
inline typename RandomContainerReverseIterator<RndCont>::ValueType&	RandomContainerReverseIterator<RndCont>::operator* () const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= 0);

	return (*rndCont)[current];
}


template <class RndCont>
inline typename  RandomContainerReverseIterator<RndCont>::ValueType*	RandomContainerReverseIterator<RndCont>::operator-> () const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= 0);

	return &(*rndCont)[current];
}


template <class RndCont>
inline typename  RandomContainerReverseIterator<RndCont>::ValueType&	RandomContainerReverseIterator<RndCont>::operator[] (IteratorOffset offset) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current - static_cast<Offset> (offset) < Int32 (rndCont->GetSize ()) && current - static_cast<Offset> (offset) >= 0);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);	// to detect when container manipulation causes invalid index

	return (*rndCont)[current - static_cast<Offset> (offset)];
}


template <class RndCont>
inline RandomContainerReverseIterator<RndCont>&	RandomContainerReverseIterator<RndCont>::operator++ ()
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= 0);	// also detects when container manipulation causes invalid index

	--current;

	return *this;
}


template <class RndCont>
inline RandomContainerReverseIterator<RndCont>		RandomContainerReverseIterator<RndCont>::operator++ (int)
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= 0);	// also detects when container manipulation causes invalid index

	RandomContainerReverseIterator result = *this;

	--current;

	return result;
}


template <class RndCont>
inline RandomContainerReverseIterator<RndCont>&	RandomContainerReverseIterator<RndCont>::operator-- ()
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);	// to detect when container manipulation causes invalid index

	++current;

	return *this;
}


template <class RndCont>
inline RandomContainerReverseIterator<RndCont>		RandomContainerReverseIterator<RndCont>::operator-- (int)
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);	// to detect when container manipulation causes invalid index

	RandomContainerReverseIterator result = *this;

	++current;

	return result;
}


template <class RndCont>
inline RandomContainerReverseIterator<RndCont>		RandomContainerReverseIterator<RndCont>::operator+ (IteratorOffset offset) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current - static_cast<Offset> (offset) < Int32 (rndCont->GetSize ()) && current - static_cast<Offset> (offset) >= -1);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);	// to detect when container manipulation causes invalid index

	return RandomContainerReverseIterator (*rndCont, current - static_cast<Offset> (offset));
}


template <class RndCont>
inline RandomContainerReverseIterator<RndCont>		RandomContainerReverseIterator<RndCont>::operator- (IteratorOffset offset) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) < Int32 (rndCont->GetSize ()) && current + static_cast<Offset> (offset) >= -1);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);	// to detect when container manipulation causes invalid index

	return RandomContainerReverseIterator (*rndCont, current + static_cast<Offset> (offset));
}


template <class RndCont>
inline IteratorOffset	RandomContainerReverseIterator<RndCont>::operator- (const RandomContainerReverseIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	TYPE_CHECK (CheckType (rightOp));
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);							// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current < Int32 (rightOp.rndCont->GetSize ()) && rightOp.current >= -1);	// to detect when container manipulation causes invalid index

	return static_cast<IteratorOffset> (rightOp.current) - static_cast<IteratorOffset> (current);
}


template <class RndCont>
inline RandomContainerReverseIterator<RndCont>&	RandomContainerReverseIterator<RndCont>::operator+= (IteratorOffset offset)
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current - static_cast<Offset> (offset) < Int32 (rndCont->GetSize ()) && current - static_cast<Offset> (offset) >= -1);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);	// to detect when container manipulation causes invalid index

	current -= static_cast<Offset> (offset);

	return *this;
}


template <class RndCont>
inline RandomContainerReverseIterator<RndCont>&	RandomContainerReverseIterator<RndCont>::operator-= (IteratorOffset offset)
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) < Int32 (rndCont->GetSize ()) && current + static_cast<Offset> (offset) >= -1);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);	// to detect when container manipulation causes invalid index

	current += static_cast<Offset> (offset);

	return *this;
}


template <class RndCont>
inline bool		RandomContainerReverseIterator<RndCont>::operator== (const RandomContainerReverseIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	TYPE_CHECK (CheckType (rightOp));
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);							// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current < Int32 (rightOp.rndCont->GetSize ()) && rightOp.current >= -1);	// to detect when container manipulation causes invalid index

	return (current == rightOp.current);
}


template <class RndCont>
inline bool		RandomContainerReverseIterator<RndCont>::operator!= (const RandomContainerReverseIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	TYPE_CHECK (CheckType (rightOp));
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);							// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current < Int32 (rightOp.rndCont->GetSize ()) && rightOp.current >= -1);	// to detect when container manipulation causes invalid index

	return (current != rightOp.current);
}


template <class RndCont>
inline bool		RandomContainerReverseIterator<RndCont>::operator< (const RandomContainerReverseIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	TYPE_CHECK (CheckType (rightOp));
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);							// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current < Int32 (rightOp.rndCont->GetSize ()) && rightOp.current >= -1);	// to detect when container manipulation causes invalid index

	return (current > rightOp.current);
}


template <class RndCont>
inline bool		RandomContainerReverseIterator<RndCont>::operator<= (const RandomContainerReverseIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	TYPE_CHECK (CheckType (rightOp));
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);							// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current < Int32 (rightOp.rndCont->GetSize ()) && rightOp.current >= -1);	// to detect when container manipulation causes invalid index

	return (current >= rightOp.current);
}


template <class RndCont>
inline bool		RandomContainerReverseIterator<RndCont>::operator> (const RandomContainerReverseIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	TYPE_CHECK (CheckType (rightOp));
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);							// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current < Int32 (rightOp.rndCont->GetSize ()) && rightOp.current >= -1);	// to detect when container manipulation causes invalid index

	return (current < rightOp.current);
}


template <class RndCont>
inline bool		RandomContainerReverseIterator<RndCont>::operator>= (const RandomContainerReverseIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	TYPE_CHECK (CheckType (rightOp));
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);							// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current < Int32 (rightOp.rndCont->GetSize ()) && rightOp.current >= -1);	// to detect when container manipulation causes invalid index

	return (current <= rightOp.current);
}


template <class RndCont>
inline bool		RandomContainerReverseIterator<RndCont>::operator== (std::nullptr_t) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);	// to detect when container manipulation causes invalid index

	return (current <= -1 || current >= Int32 (rndCont->GetSize ()));
}


template <class RndCont>
inline bool		RandomContainerReverseIterator<RndCont>::operator!= (std::nullptr_t) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);	// to detect when container manipulation causes invalid index

	return (current > -1 && current < Int32 (rndCont->GetSize ()));
}


template <class RndCont>
inline RndCont*		RandomContainerReverseIterator<RndCont>::GetTarget (void) const
{
	return rndCont;
}


template <class RndCont>
inline Int32	RandomContainerReverseIterator<RndCont>::GetIndex (void) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);

	return current;
}


template <class RndCont>
IForwardIterator<typename RandomContainerReverseIterator<RndCont>::ValueType>*		RandomContainerReverseIterator<RndCont>::CreateClone (void) const
{
	return new RandomContainerReverseIterator (*this);
}


template <class RndCont>
IConstForwardIterator<typename RandomContainerReverseIterator<RndCont>::ValueType>*	RandomContainerReverseIterator<RndCont>::CreateConstClone (void) const
{
	return new ConstRandomContainerReverseIterator<RndCont> (*this);
}


template <class RndCont>
bool	RandomContainerReverseIterator<RndCont>::IsEnd (void) const
{
	return operator== (nullptr);
}


template <class RndCont>
typename RandomContainerReverseIterator<RndCont>::ValueType&	RandomContainerReverseIterator<RndCont>::Get (IteratorOffset offset) const
{
	return operator[] (offset);
}


template <class RndCont>
void	RandomContainerReverseIterator<RndCont>::Add (IteratorOffset offset)
{
	operator+= (offset);
}


template <class RndCont>
IteratorOffset	RandomContainerReverseIterator<RndCont>::GetDifference (const IRandomIterator<ValueType>* rightOp) const
{
	NULL_PTR_CHECK (rightOp);

	const RandomContainerReverseIterator* ro = dynamic_cast<const RandomContainerReverseIterator*> (rightOp);
	TYPE_CHECK (ro != nullptr);

	return operator- (*ro);
}


template <class RndCont>
inline bool		RandomContainerReverseIterator<RndCont>::CheckType (const RandomContainerReverseIterator& rightOp) const
{
	return (rndCont == rightOp.rndCont);
}

}	// namespace GS
// _______________________ Class RandomContainerReverseIterator _______________________



// ==================== Class ConstRandomContainerReverseIterator =====================

namespace GS {

template <class RndCont>
inline ConstRandomContainerReverseIterator<RndCont>::ConstRandomContainerReverseIterator ():
	ConstRandomIterator<typename ConstRandomContainerReverseIterator<RndCont>::ValueType> (GetIteratorInterface ()),
	rndCont (nullptr),
	current (0)
{
}


template <class RndCont>
inline ConstRandomContainerReverseIterator<RndCont>::ConstRandomContainerReverseIterator (const RndCont& target_, Int32 idx):
	ConstRandomIterator<typename ConstRandomContainerReverseIterator<RndCont>::ValueType> (GetIteratorInterface ()),
	rndCont (&target_),
	current (idx)
{
	NULL_REF_CHECK (target_);
	REF_CHECK (idx < Int32 (target_.GetSize ()) && idx >= -1);
}


template <class RndCont>
inline ConstRandomContainerReverseIterator<RndCont>::ConstRandomContainerReverseIterator (const ConstRandomContainerReverseIterator& source):
	ConstRandomIterator<typename ConstRandomContainerReverseIterator<RndCont>::ValueType> (GetIteratorInterface ()),
	rndCont (source.rndCont),
	current (source.current)
{
	NULL_REF_CHECK (source);
}


template <class RndCont>
inline ConstRandomContainerReverseIterator<RndCont>::ConstRandomContainerReverseIterator (const RandomContainerReverseIterator<RndCont>& source):
	ConstRandomIterator<typename ConstRandomContainerReverseIterator<RndCont>::ValueType> (GetIteratorInterface ()),
	rndCont (source.rndCont),
	current (source.current)
{
	NULL_REF_CHECK (source);
}


template <class RndCont>
inline ConstRandomContainerReverseIterator<RndCont>&	ConstRandomContainerReverseIterator<RndCont>::operator= (const ConstRandomContainerReverseIterator& source)
{
	NULL_REF_CHECK (source);

	if (this != &source) {
		ConstRandomIterator<ValueType>::operator= (source);

		rndCont = source.rndCont;
		current = source.current;
	}

	return *this;
}


template <class RndCont>
void	ConstRandomContainerReverseIterator<RndCont>::Assign (const IConstForwardIterator<ValueType>* /*source*/)
{
	// ConstRandomContainerReverseIterator contains own realization of the IConstRandomIterator interface
	// working on members in this class which are copied from the source iterator
}


template <class RndCont>
inline ConstRandomContainerReverseIterator<RndCont>&	ConstRandomContainerReverseIterator<RndCont>::operator= (const RandomContainerReverseIterator<RndCont>& source)
{
	NULL_REF_CHECK (source);

	if (this != static_cast<const void*> (&source)) {
		ConstRandomIterator<ValueType>::operator= (source);

		rndCont = source.rndCont;
		current = source.current;
	}

	return *this;
}


template <class RndCont>
void	ConstRandomContainerReverseIterator<RndCont>::Assign (const IForwardIterator<ValueType>* /*source*/)
{
	// ConstRandomContainerReverseIterator contains own realization of the IConstRandomIterator interface
	// working on members in this class which are copied from the source iterator
}


template <class RndCont>
inline ConstRandomContainerReverseIterator<RndCont>::~ConstRandomContainerReverseIterator ()
{
	this->target = nullptr;
}


template <class RndCont>
inline const typename ConstRandomContainerReverseIterator<RndCont>::ValueType&		ConstRandomContainerReverseIterator<RndCont>::operator* () const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= 0);

	return (*rndCont)[current];
}


template <class RndCont>
inline const typename ConstRandomContainerReverseIterator<RndCont>::ValueType*		ConstRandomContainerReverseIterator<RndCont>::operator-> () const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= 0);

	return &(*rndCont)[current];
}


template <class RndCont>
inline const typename ConstRandomContainerReverseIterator<RndCont>::ValueType&		ConstRandomContainerReverseIterator<RndCont>::operator[] (IteratorOffset offset) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current - static_cast<Offset> (offset) < Int32 (rndCont->GetSize ()) && current - static_cast<Offset> (offset) >= 0);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);	// to detect when container manipulation causes invalid index

	return (*rndCont)[current - static_cast<Offset> (offset)];
}


template <class RndCont>
inline ConstRandomContainerReverseIterator<RndCont>&	ConstRandomContainerReverseIterator<RndCont>::operator++ ()
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= 0);	// also detects when container manipulation causes invalid index

	--current;

	return *this;
}


template <class RndCont>
inline ConstRandomContainerReverseIterator<RndCont>	ConstRandomContainerReverseIterator<RndCont>::operator++ (int)
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= 0);	// also detects when container manipulation causes invalid index

	ConstRandomContainerReverseIterator result = *this;

	--current;

	return result;
}


template <class RndCont>
inline ConstRandomContainerReverseIterator<RndCont>&	ConstRandomContainerReverseIterator<RndCont>::operator-- ()
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);	// to detect when container manipulation causes invalid index

	++current;

	return *this;
}


template <class RndCont>
inline ConstRandomContainerReverseIterator<RndCont>	ConstRandomContainerReverseIterator<RndCont>::operator-- (int)
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);	// to detect when container manipulation causes invalid index

	ConstRandomContainerReverseIterator result = *this;

	++current;

	return result;
}


template <class RndCont>
inline ConstRandomContainerReverseIterator<RndCont>	ConstRandomContainerReverseIterator<RndCont>::operator+ (IteratorOffset offset) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current - static_cast<Offset> (offset) < Int32 (rndCont->GetSize ()) && current - static_cast<Offset> (offset) >= -1);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);	// to detect when container manipulation causes invalid index

	return ConstRandomContainerReverseIterator (*rndCont, current - static_cast<Offset> (offset));
}


template <class RndCont>
inline ConstRandomContainerReverseIterator<RndCont>	ConstRandomContainerReverseIterator<RndCont>::operator- (IteratorOffset offset) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) < Int32 (rndCont->GetSize ()) && current + static_cast<Offset> (offset) >= -1);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);					// to detect when container manipulation causes invalid index

	return ConstRandomContainerReverseIterator (*rndCont, current + static_cast<Offset> (offset));
}


template <class RndCont>
inline IteratorOffset	ConstRandomContainerReverseIterator<RndCont>::operator- (const ConstRandomContainerReverseIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	TYPE_CHECK (CheckType (rightOp));
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);							// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current < Int32 (rightOp.rndCont->GetSize ()) && rightOp.current >= -1);	// to detect when container manipulation causes invalid index

	return static_cast<IteratorOffset> (rightOp.current) - static_cast<IteratorOffset> (current);
}


template <class RndCont>
inline ConstRandomContainerReverseIterator<RndCont>&	ConstRandomContainerReverseIterator<RndCont>::operator+= (IteratorOffset offset)
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current - static_cast<Offset> (offset) < Int32 (rndCont->GetSize ()) && current - static_cast<Offset> (offset) >= -1);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);	// to detect when container manipulation causes invalid index

	current -= static_cast<Offset> (offset);

	return *this;
}


template <class RndCont>
inline ConstRandomContainerReverseIterator<RndCont>&	ConstRandomContainerReverseIterator<RndCont>::operator-= (IteratorOffset offset)
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) < Int32 (rndCont->GetSize ()) && current + static_cast<Offset> (offset) >= -1);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);	// to detect when container manipulation causes invalid index

	current += static_cast<Offset> (offset);

	return *this;
}


template <class RndCont>
inline bool		ConstRandomContainerReverseIterator<RndCont>::operator== (const ConstRandomContainerReverseIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	TYPE_CHECK (CheckType (rightOp));
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);							// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current < Int32 (rightOp.rndCont->GetSize ()) && rightOp.current >= -1);	// to detect when container manipulation causes invalid index

	return (current == rightOp.current);
}


template <class RndCont>
inline bool		ConstRandomContainerReverseIterator<RndCont>::operator!= (const ConstRandomContainerReverseIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	TYPE_CHECK (CheckType (rightOp));
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);							// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current < Int32 (rightOp.rndCont->GetSize ()) && rightOp.current >= -1);	// to detect when container manipulation causes invalid index

	return (current != rightOp.current);
}


template <class RndCont>
inline bool		ConstRandomContainerReverseIterator<RndCont>::operator< (const ConstRandomContainerReverseIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	TYPE_CHECK (CheckType (rightOp));
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);							// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current < Int32 (rightOp.rndCont->GetSize ()) && rightOp.current >= -1);	// to detect when container manipulation causes invalid index

	return (current > rightOp.current);
}


template <class RndCont>
inline bool		ConstRandomContainerReverseIterator<RndCont>::operator<= (const ConstRandomContainerReverseIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	TYPE_CHECK (CheckType (rightOp));
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);							// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current < Int32 (rightOp.rndCont->GetSize ()) && rightOp.current >= -1);	// to detect when container manipulation causes invalid index

	return (current >= rightOp.current);
}


template <class RndCont>
inline bool		ConstRandomContainerReverseIterator<RndCont>::operator> (const ConstRandomContainerReverseIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	TYPE_CHECK (CheckType (rightOp));
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);							// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current < Int32 (rightOp.rndCont->GetSize ()) && rightOp.current >= -1);	// to detect when container manipulation causes invalid index

	return (current < rightOp.current);
}


template <class RndCont>
inline bool		ConstRandomContainerReverseIterator<RndCont>::operator>= (const ConstRandomContainerReverseIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	TYPE_CHECK (CheckType (rightOp));
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);							// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current < Int32 (rightOp.rndCont->GetSize ()) && rightOp.current >= -1);	// to detect when container manipulation causes invalid index

	return (current <= rightOp.current);
}


template <class RndCont>
inline bool		ConstRandomContainerReverseIterator<RndCont>::operator== (std::nullptr_t) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);	// to detect when container manipulation causes invalid index

	return (current <= -1 || current >= Int32 (rndCont->GetSize ()));
}


template <class RndCont>
inline bool		ConstRandomContainerReverseIterator<RndCont>::operator!= (std::nullptr_t) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < Int32 (rndCont->GetSize ()) && current >= -1);	// to detect when container manipulation causes invalid index

	return (current > -1 && current < Int32 (rndCont->GetSize ()));
}


template <class RndCont>
inline const RndCont*	ConstRandomContainerReverseIterator<RndCont>::GetTarget (void) const
{
	return rndCont;
}


template <class RndCont>
inline Int32	ConstRandomContainerReverseIterator<RndCont>::GetIndex (void) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);

	return current;
}


template <class RndCont>
IConstForwardIterator<typename ConstRandomContainerReverseIterator<RndCont>::ValueType>*	ConstRandomContainerReverseIterator<RndCont>::CreateClone (void) const
{
	return new ConstRandomContainerReverseIterator (*this);
}


template <class RndCont>
bool	ConstRandomContainerReverseIterator<RndCont>::IsEnd (void) const
{
	return operator== (nullptr);
}


template <class RndCont>
const typename ConstRandomContainerReverseIterator<RndCont>::ValueType&	ConstRandomContainerReverseIterator<RndCont>::Get (IteratorOffset offset) const
{
	return operator[] (offset);
}


template <class RndCont>
void	ConstRandomContainerReverseIterator<RndCont>::Add (IteratorOffset offset)
{
	operator+= (offset);
}


template <class RndCont>
IteratorOffset	ConstRandomContainerReverseIterator<RndCont>::GetDifference (const IConstRandomIterator<ValueType>* rightOp) const
{
	NULL_PTR_CHECK (rightOp);

	const ConstRandomContainerReverseIterator* ro = dynamic_cast<const ConstRandomContainerReverseIterator*> (rightOp);
	TYPE_CHECK (ro != nullptr);

	return operator- (*ro);
}


template <class RndCont>
inline bool		ConstRandomContainerReverseIterator<RndCont>::CheckType (const ConstRandomContainerReverseIterator& rightOp) const
{
	return (rndCont == rightOp.rndCont);
}

}	// namespace GS
// ____________________ Class ConstRandomContainerReverseIterator _____________________


#endif
