
// *********************************************************************************************************************
//
//     Classes RandomContainerIterator,
//			   ConstRandomContainerIterator,
//			   GeneralRandomContainerIterator,
//			   ConstGeneralRandomContainerIterator
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// Requirements:
//   Target random container should have conventional operator[] and GetSize
//   operations and type ValueType.
//
// *********************************************************************************************************************


#if !defined RANDOMCONTAINERITERATOR_HPP
#define RANDOMCONTAINERITERATOR_HPP

#pragma once

// --- Includes --------------------------------------------------------------------------------------------------------

#include "RandomIterator.hpp"



// === Class RandomContainerIterator ===================================================================================

namespace GS {

template <class RndCont>
class ConstRandomContainerIterator;


template <class RndCont>
class RandomContainerIterator {
private:
	RndCont*	rndCont;	// target random container iterator is connected to
	UIndex		current;	// index of the current item in the random container

	friend class ConstRandomContainerIterator<RndCont>;

public:
		// Constructors

	inline RandomContainerIterator ();
	inline RandomContainerIterator (RndCont& target, UIndex idx);
	inline RandomContainerIterator (const RandomContainerIterator& source);
	inline RandomContainerIterator&		operator= (const RandomContainerIterator& source);

		// Types

	typedef typename RndCont::ValueType	ValueType;

		// User interface

	inline ValueType&					operator*  () const;
	inline ValueType*					operator-> () const;
	inline ValueType&					operator[] (IteratorOffset offset) const;

	inline RandomContainerIterator&		operator++ ();
	inline RandomContainerIterator		operator++ (int);

	inline RandomContainerIterator&		operator-- ();
	inline RandomContainerIterator		operator-- (int);

	inline RandomContainerIterator		operator+  (IteratorOffset offset) const;
	inline RandomContainerIterator		operator-  (IteratorOffset offset) const;
	inline IteratorOffset				operator-  (const RandomContainerIterator& rightOp) const;
	inline RandomContainerIterator&		operator+= (IteratorOffset offset);
	inline RandomContainerIterator&		operator-= (IteratorOffset offset);

	inline bool							operator== (const RandomContainerIterator& rightOp) const;
	inline bool							operator!= (const RandomContainerIterator& rightOp) const;
	inline bool							operator<  (const RandomContainerIterator& rightOp) const;
	inline bool							operator<= (const RandomContainerIterator& rightOp) const;
	inline bool							operator>  (const RandomContainerIterator& rightOp) const;
	inline bool							operator>= (const RandomContainerIterator& rightOp) const;

	inline bool							operator== (std::nullptr_t) const;
	inline bool							operator!= (std::nullptr_t) const;

	inline UIndex						GetIndex (void) const;
};

}	// namespace GS



// === Class ConstRandomContainerIterator ==============================================================================

namespace GS {

template <class RndCont>
class ConstRandomContainerIterator {
private:
	const RndCont*	rndCont;	// target random container iterator is connected to
	UIndex			current;	// index of the current item in the random container

public:
		// Constructors

	inline ConstRandomContainerIterator ();
	inline ConstRandomContainerIterator (const RndCont& target, UIndex idx);
	inline ConstRandomContainerIterator (const ConstRandomContainerIterator& source);
	inline ConstRandomContainerIterator (const RandomContainerIterator<RndCont>& source);
	inline ConstRandomContainerIterator&	operator= (const ConstRandomContainerIterator& source);
	inline ConstRandomContainerIterator&	operator= (const RandomContainerIterator<RndCont>& source);

		// Types

	typedef typename RndCont::ValueType	ValueType;

		// User interface

	inline const ValueType&					operator*  () const;
	inline const ValueType*					operator-> () const;
	inline const ValueType&					operator[] (IteratorOffset offset) const;

	inline ConstRandomContainerIterator&	operator++ ();
	inline ConstRandomContainerIterator		operator++ (int);

	inline ConstRandomContainerIterator&	operator-- ();
	inline ConstRandomContainerIterator		operator-- (int);

	inline ConstRandomContainerIterator		operator+  (IteratorOffset offset) const;
	inline ConstRandomContainerIterator		operator-  (IteratorOffset offset) const;
	inline IteratorOffset					operator-  (const ConstRandomContainerIterator& rightOp) const;
	inline ConstRandomContainerIterator&	operator+= (IteratorOffset offset);
	inline ConstRandomContainerIterator&	operator-= (IteratorOffset offset);

	inline bool								operator== (const ConstRandomContainerIterator& rightOp) const;
	inline bool								operator!= (const ConstRandomContainerIterator& rightOp) const;
	inline bool								operator<  (const ConstRandomContainerIterator& rightOp) const;
	inline bool								operator<= (const ConstRandomContainerIterator& rightOp) const;
	inline bool								operator>  (const ConstRandomContainerIterator& rightOp) const;
	inline bool								operator>= (const ConstRandomContainerIterator& rightOp) const;

	inline bool								operator== (std::nullptr_t) const;
	inline bool								operator!= (std::nullptr_t) const;

	inline UIndex							GetIndex (void) const;
};

}	// namespace GS



// === Class GeneralRandomContainerIterator ============================================================================

namespace GS {

template <class RndCont>
class ConstGeneralRandomContainerIterator;

template <class RndCont>
class GeneralRandomContainerIterator: public RandomIterator<typename RndCont::ValueType>,
									  public IRandomIterator<typename RndCont::ValueType>
{
public:
	typedef typename RandomIterator<typename RndCont::ValueType>::ValueType	ValueType;	// repeated because of Mac

private:
	RndCont*	rndCont;	// target random container iterator is connected to
	UIndex		current;	// index of the current item in the random container

	inline IRandomIterator<ValueType>*	GetIteratorInterface (void) { return this; }

	friend class ConstGeneralRandomContainerIterator<RndCont>;

protected:
	virtual void	Assign (const IForwardIterator<ValueType>* source) override;

	virtual IForwardIterator<ValueType>*		CreateClone      (void) const override;
	virtual IConstForwardIterator<ValueType>*	CreateConstClone (void) const override;

	virtual bool		IsEnd (void) const override;

	virtual ValueType&	Get (IteratorOffset offset) const override;

	virtual void		Add (IteratorOffset offset) override;

	virtual IteratorOffset		GetDifference (const IRandomIterator<ValueType>* rightOp) const override;

public:
		// Constructors

	inline GeneralRandomContainerIterator ();
	inline GeneralRandomContainerIterator (RndCont& target, UIndex idx);
	inline GeneralRandomContainerIterator (const GeneralRandomContainerIterator& source);
	inline GeneralRandomContainerIterator&	operator= (const GeneralRandomContainerIterator& source);
	inline ~GeneralRandomContainerIterator ();

		// User interface

	inline ValueType&	operator*  () const;
	inline ValueType*	operator-> () const;
	inline ValueType&	operator[] (IteratorOffset offset) const;

	inline GeneralRandomContainerIterator&	operator++ ();
	inline GeneralRandomContainerIterator	operator++ (int);

	inline GeneralRandomContainerIterator&	operator-- ();
	inline GeneralRandomContainerIterator	operator-- (int);

	inline GeneralRandomContainerIterator	operator+  (IteratorOffset offset) const;
	inline GeneralRandomContainerIterator	operator-  (IteratorOffset offset) const;
	inline IteratorOffset					operator-  (const GeneralRandomContainerIterator& rightOp) const;
	inline GeneralRandomContainerIterator&	operator+= (IteratorOffset offset);
	inline GeneralRandomContainerIterator&	operator-= (IteratorOffset offset);

	inline bool		operator== (const GeneralRandomContainerIterator& rightOp) const;
	inline bool		operator!= (const GeneralRandomContainerIterator& rightOp) const;
	inline bool		operator<  (const GeneralRandomContainerIterator& rightOp) const;
	inline bool		operator<= (const GeneralRandomContainerIterator& rightOp) const;
	inline bool		operator>  (const GeneralRandomContainerIterator& rightOp) const;
	inline bool		operator>= (const GeneralRandomContainerIterator& rightOp) const;

	inline bool		operator== (std::nullptr_t) const;
	inline bool		operator!= (std::nullptr_t) const;

	inline RndCont*	GetTarget (void) const;
	inline UIndex	GetIndex  (void) const;
};

}	// namespace GS



// === Class ConstGeneralRandomContainerIterator =======================================================================

namespace GS {

template <class RndCont>
class ConstGeneralRandomContainerIterator: public ConstRandomIterator<typename RndCont::ValueType>,
										   public IConstRandomIterator<typename RndCont::ValueType>
{
public:
	typedef typename ConstRandomIterator<typename RndCont::ValueType>::ValueType	ValueType;	// repeated because of Mac

private:
	const RndCont*	rndCont;	// target random container iterator is connected to
	UIndex			current;	// index of the current item in the random container

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

	inline ConstGeneralRandomContainerIterator ();
	inline ConstGeneralRandomContainerIterator (const RndCont& target, UIndex idx);
	inline ConstGeneralRandomContainerIterator (const ConstGeneralRandomContainerIterator& source);
	inline ConstGeneralRandomContainerIterator (const GeneralRandomContainerIterator<RndCont>& source);
	inline ConstGeneralRandomContainerIterator&	operator= (const ConstGeneralRandomContainerIterator& source);
	inline ConstGeneralRandomContainerIterator&	operator= (const GeneralRandomContainerIterator<RndCont>& source);
	inline ~ConstGeneralRandomContainerIterator ();

		// User interface

	inline const ValueType&		operator*  () const;
	inline const ValueType*		operator-> () const;
	inline const ValueType&		operator[] (IteratorOffset offset) const;

	inline ConstGeneralRandomContainerIterator&	operator++ ();
	inline ConstGeneralRandomContainerIterator	operator++ (int);

	inline ConstGeneralRandomContainerIterator&	operator-- ();
	inline ConstGeneralRandomContainerIterator	operator-- (int);

	inline ConstGeneralRandomContainerIterator	operator+  (IteratorOffset offset) const;
	inline ConstGeneralRandomContainerIterator	operator-  (IteratorOffset offset) const;
	inline IteratorOffset								operator-  (const ConstGeneralRandomContainerIterator& rightOp) const;
	inline ConstGeneralRandomContainerIterator&	operator+= (IteratorOffset offset);
	inline ConstGeneralRandomContainerIterator&	operator-= (IteratorOffset offset);

	inline bool		operator== (const ConstGeneralRandomContainerIterator& rightOp) const;
	inline bool		operator!= (const ConstGeneralRandomContainerIterator& rightOp) const;
	inline bool		operator<  (const ConstGeneralRandomContainerIterator& rightOp) const;
	inline bool		operator<= (const ConstGeneralRandomContainerIterator& rightOp) const;
	inline bool		operator>  (const ConstGeneralRandomContainerIterator& rightOp) const;
	inline bool		operator>= (const ConstGeneralRandomContainerIterator& rightOp) const;

	inline bool		operator== (std::nullptr_t) const;
	inline bool		operator!= (std::nullptr_t) const;

	inline const RndCont*	GetTarget (void) const;
	inline UIndex			GetIndex (void) const;
};

}	// namespace GS



// === Class RandomContainerIterator ===================================================================================

namespace GS {

template <class RndCont>
inline RandomContainerIterator<RndCont>::RandomContainerIterator ():
	rndCont (nullptr),
	current (0)
{
}


template <class RndCont>
inline RandomContainerIterator<RndCont>::RandomContainerIterator (RndCont& target_, UIndex idx):
	rndCont (&target_),
	current (idx)
{
	NULL_REF_CHECK (target_);
	REF_CHECK (idx <= target_.GetSize ());
}


template <class RndCont>
inline RandomContainerIterator<RndCont>::RandomContainerIterator (const RandomContainerIterator& source):
	rndCont (source.rndCont),
	current (source.current)
{
	NULL_REF_CHECK (source);
}


template <class RndCont>
inline RandomContainerIterator<RndCont>&	RandomContainerIterator<RndCont>::operator= (const RandomContainerIterator& source)
{
	NULL_REF_CHECK (source);

	if (this != &source) {
		rndCont = source.rndCont;
		current = source.current;
	}

	return *this;
}


template <class RndCont>
inline typename RandomContainerIterator<RndCont>::ValueType&	RandomContainerIterator<RndCont>::operator* () const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < rndCont->GetSize ());

	return (*rndCont)[current];
}


template <class RndCont>
inline typename RandomContainerIterator<RndCont>::ValueType*	RandomContainerIterator<RndCont>::operator-> () const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < rndCont->GetSize ());

	return &(*rndCont)[current];
}


template <class RndCont>
inline typename RandomContainerIterator<RndCont>::ValueType&	RandomContainerIterator<RndCont>::operator[] (IteratorOffset offset) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) >= 0);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) < rndCont->GetSize ());
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (*rndCont)[current + static_cast<Offset> (offset)];
}


template <class RndCont>
inline RandomContainerIterator<RndCont>&	RandomContainerIterator<RndCont>::operator++ ()
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < rndCont->GetSize ());	// also detects when container manipulation causes invalid index

	current++;

	return *this;
}


template <class RndCont>
inline RandomContainerIterator<RndCont>		RandomContainerIterator<RndCont>::operator++ (int)
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < rndCont->GetSize ());	// also detects when container manipulation causes invalid index

	RandomContainerIterator result = *this;

	current++;

	return result;
}


template <class RndCont>
inline RandomContainerIterator<RndCont>&	RandomContainerIterator<RndCont>::operator-- ()
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current > 0);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	current--;

	return *this;
}


template <class RndCont>
inline RandomContainerIterator<RndCont>		RandomContainerIterator<RndCont>::operator-- (int)
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current > 0);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	RandomContainerIterator result = *this;

	current--;

	return result;
}


template <class RndCont>
inline RandomContainerIterator<RndCont>		RandomContainerIterator<RndCont>::operator+ (IteratorOffset offset) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) >= 0);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) <= rndCont->GetSize ());
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return RandomContainerIterator (*rndCont, current + static_cast<Offset> (offset));
}


template <class RndCont>
inline RandomContainerIterator<RndCont>		RandomContainerIterator<RndCont>::operator- (IteratorOffset offset) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current - static_cast<Offset> (offset) >= 0);
	PRECOND_DEPRECATED (current - static_cast<Offset> (offset) <= rndCont->GetSize ());
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return RandomContainerIterator (*rndCont, current - static_cast<Offset> (offset));
}


template <class RndCont>
inline IteratorOffset	RandomContainerIterator<RndCont>::operator- (const RandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return static_cast<IteratorOffset> (current) - static_cast<IteratorOffset> (rightOp.current);
}


template <class RndCont>
inline RandomContainerIterator<RndCont>&	RandomContainerIterator<RndCont>::operator+= (IteratorOffset offset)
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) >= 0);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) <= rndCont->GetSize ());
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	current += static_cast<Offset> (offset);

	return *this;
}


template <class RndCont>
inline RandomContainerIterator<RndCont>&	RandomContainerIterator<RndCont>::operator-= (IteratorOffset offset)
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current - static_cast<Offset> (offset) >= 0);
	PRECOND_DEPRECATED (current - static_cast<Offset> (offset) <= rndCont->GetSize ());
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	current -= static_cast<Offset> (offset);

	return *this;
}


template <class RndCont>
inline bool		RandomContainerIterator<RndCont>::operator== (const RandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current == rightOp.current);
}


template <class RndCont>
inline bool		RandomContainerIterator<RndCont>::operator!= (const RandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current != rightOp.current);
}


template <class RndCont>
inline bool		RandomContainerIterator<RndCont>::operator< (const RandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current < rightOp.current);
}


template <class RndCont>
inline bool		RandomContainerIterator<RndCont>::operator<= (const RandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current <= rightOp.current);
}


template <class RndCont>
inline bool		RandomContainerIterator<RndCont>::operator> (const RandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current > rightOp.current);
}


template <class RndCont>
inline bool		RandomContainerIterator<RndCont>::operator>= (const RandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current >= rightOp.current);
}


template <class RndCont>
inline bool		RandomContainerIterator<RndCont>::operator== (std::nullptr_t) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current >= rndCont->GetSize ());
}


template <class RndCont>
inline bool		RandomContainerIterator<RndCont>::operator!= (std::nullptr_t) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current < rndCont->GetSize ());
}


template <class RndCont>
inline UIndex	RandomContainerIterator<RndCont>::GetIndex (void) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);

	return current;
}

}	// namespace GS



// === Class ConstRandomContainerIterator ==============================================================================

namespace GS {

template <class RndCont>
inline ConstRandomContainerIterator<RndCont>::ConstRandomContainerIterator ():
	rndCont (nullptr),
	current (0)
{
}


template <class RndCont>
inline ConstRandomContainerIterator<RndCont>::ConstRandomContainerIterator (const RndCont& target_, UIndex idx):
	rndCont (&target_),
	current (idx)
{
	NULL_REF_CHECK (target_);
	REF_CHECK (idx <= target_.GetSize ());
}


template <class RndCont>
inline ConstRandomContainerIterator<RndCont>::ConstRandomContainerIterator (const ConstRandomContainerIterator& source):
	rndCont (source.rndCont),
	current (source.current)
{
	NULL_REF_CHECK (source);
}


template <class RndCont>
inline ConstRandomContainerIterator<RndCont>::ConstRandomContainerIterator (const RandomContainerIterator<RndCont>& source):
	rndCont (source.rndCont),
	current (source.current)
{
	NULL_REF_CHECK (source);
}


template <class RndCont>
inline ConstRandomContainerIterator<RndCont>&	ConstRandomContainerIterator<RndCont>::operator= (const ConstRandomContainerIterator& source)
{
	NULL_REF_CHECK (source);

	if (this != &source) {
		rndCont = source.rndCont;
		current = source.current;
	}

	return *this;
}


template <class RndCont>
inline ConstRandomContainerIterator<RndCont>&	ConstRandomContainerIterator<RndCont>::operator= (const RandomContainerIterator<RndCont>& source)
{
	NULL_REF_CHECK (source);

	if (this != static_cast<const void*> (&source)) {
		rndCont = source.rndCont;
		current = source.current;
	}

	return *this;
}


template <class RndCont>
inline const typename ConstRandomContainerIterator<RndCont>::ValueType&		ConstRandomContainerIterator<RndCont>::operator* () const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < rndCont->GetSize ());

	return (*rndCont)[current];
}


template <class RndCont>
inline const typename ConstRandomContainerIterator<RndCont>::ValueType*		ConstRandomContainerIterator<RndCont>::operator-> () const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < rndCont->GetSize ());

	return &(*rndCont)[current];
}


template <class RndCont>
inline const typename ConstRandomContainerIterator<RndCont>::ValueType&		ConstRandomContainerIterator<RndCont>::operator[] (IteratorOffset offset) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) >= 0);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) < rndCont->GetSize ());
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (*rndCont)[current + static_cast<Offset> (offset)];
}


template <class RndCont>
inline ConstRandomContainerIterator<RndCont>&	ConstRandomContainerIterator<RndCont>::operator++ ()
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < rndCont->GetSize ());	// also detects when container manipulation causes invalid index

	current++;

	return *this;
}


template <class RndCont>
inline ConstRandomContainerIterator<RndCont>	ConstRandomContainerIterator<RndCont>::operator++ (int)
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < rndCont->GetSize ());	// also detects when container manipulation causes invalid index

	ConstRandomContainerIterator result = *this;

	current++;

	return result;
}


template <class RndCont>
inline ConstRandomContainerIterator<RndCont>&	ConstRandomContainerIterator<RndCont>::operator-- ()
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current > 0);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	current--;

	return *this;
}


template <class RndCont>
inline ConstRandomContainerIterator<RndCont>	ConstRandomContainerIterator<RndCont>::operator-- (int)
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current > 0);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	ConstRandomContainerIterator result = *this;

	current--;

	return result;
}


template <class RndCont>
inline ConstRandomContainerIterator<RndCont>	ConstRandomContainerIterator<RndCont>::operator+ (IteratorOffset offset) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) >= 0);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) <= rndCont->GetSize ());
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return ConstRandomContainerIterator (*rndCont, current + static_cast<Offset> (offset));
}


template <class RndCont>
inline ConstRandomContainerIterator<RndCont>	ConstRandomContainerIterator<RndCont>::operator- (IteratorOffset offset) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current - static_cast<Offset> (offset) >= 0);
	PRECOND_DEPRECATED (current - static_cast<Offset> (offset) <= rndCont->GetSize ());
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index

	return ConstRandomContainerIterator (*rndCont, current - static_cast<Offset> (offset));
}


template <class RndCont>
inline IteratorOffset	ConstRandomContainerIterator<RndCont>::operator- (const ConstRandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return static_cast<IteratorOffset> (current) - static_cast<IteratorOffset> (rightOp.current);
}


template <class RndCont>
inline ConstRandomContainerIterator<RndCont>&	ConstRandomContainerIterator<RndCont>::operator+= (IteratorOffset offset)
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) >= 0);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) <= rndCont->GetSize ());
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	current += static_cast<Offset> (offset);

	return *this;
}


template <class RndCont>
inline ConstRandomContainerIterator<RndCont>&	ConstRandomContainerIterator<RndCont>::operator-= (IteratorOffset offset)
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current - static_cast<Offset> (offset) >= 0);
	PRECOND_DEPRECATED (current - static_cast<Offset> (offset) <= rndCont->GetSize ());
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	current -= static_cast<Offset> (offset);

	return *this;
}


template <class RndCont>
inline bool		ConstRandomContainerIterator<RndCont>::operator== (const ConstRandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current == rightOp.current);
}


template <class RndCont>
inline bool		ConstRandomContainerIterator<RndCont>::operator!= (const ConstRandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current != rightOp.current);
}


template <class RndCont>
inline bool		ConstRandomContainerIterator<RndCont>::operator< (const ConstRandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current < rightOp.current);
}


template <class RndCont>
inline bool		ConstRandomContainerIterator<RndCont>::operator<= (const ConstRandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current <= rightOp.current);
}


template <class RndCont>
inline bool		ConstRandomContainerIterator<RndCont>::operator> (const ConstRandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current > rightOp.current);
}


template <class RndCont>
inline bool		ConstRandomContainerIterator<RndCont>::operator>= (const ConstRandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current >= rightOp.current);
}


template <class RndCont>
inline bool		ConstRandomContainerIterator<RndCont>::operator== (std::nullptr_t) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current >= rndCont->GetSize ());
}


template <class RndCont>
inline bool		ConstRandomContainerIterator<RndCont>::operator!= (std::nullptr_t) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current < rndCont->GetSize ());
}


template <class RndCont>
inline UIndex	ConstRandomContainerIterator<RndCont>::GetIndex (void) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);

	return current;
}

}	// namespace GS



// === Class GeneralRandomContainerIterator ============================================================================

namespace GS {

template <class RndCont>
inline GeneralRandomContainerIterator<RndCont>::GeneralRandomContainerIterator ():
	RandomIterator<typename GeneralRandomContainerIterator<RndCont>::ValueType> (GetIteratorInterface ()),
	rndCont (nullptr),
	current (0)
{
}


template <class RndCont>
inline GeneralRandomContainerIterator<RndCont>::GeneralRandomContainerIterator (RndCont& target_, UIndex idx):
	RandomIterator<typename GeneralRandomContainerIterator<RndCont>::ValueType> (GetIteratorInterface ()),
	rndCont (&target_),
	current (idx)
{
	NULL_REF_CHECK (target_);
	REF_CHECK (idx <= target_.GetSize ());
}


template <class RndCont>
inline GeneralRandomContainerIterator<RndCont>::GeneralRandomContainerIterator (const GeneralRandomContainerIterator& source):
	RandomIterator<typename GeneralRandomContainerIterator<RndCont>::ValueType> (GetIteratorInterface ()),
	rndCont (source.rndCont),
	current (source.current)
{
	NULL_REF_CHECK (source);
}


template <class RndCont>
inline GeneralRandomContainerIterator<RndCont>&		GeneralRandomContainerIterator<RndCont>::operator= (const GeneralRandomContainerIterator& source)
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
void	GeneralRandomContainerIterator<RndCont>::Assign (const IForwardIterator<ValueType>* /*source*/)
{
	// GeneralRandomContainerIterator contains own realization of the IRandomIterator interface
	// working on members in this class which are copied from the source iterator
}


template <class RndCont>
inline GeneralRandomContainerIterator<RndCont>::~GeneralRandomContainerIterator ()
{
	this->target = nullptr;
}


template <class RndCont>
inline typename GeneralRandomContainerIterator<RndCont>::ValueType&		GeneralRandomContainerIterator<RndCont>::operator* () const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < rndCont->GetSize ());

	return (*rndCont)[current];
}


template <class RndCont>
inline typename GeneralRandomContainerIterator<RndCont>::ValueType*		GeneralRandomContainerIterator<RndCont>::operator-> () const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < rndCont->GetSize ());

	return &(*rndCont)[current];
}


template <class RndCont>
inline typename GeneralRandomContainerIterator<RndCont>::ValueType&		GeneralRandomContainerIterator<RndCont>::operator[] (IteratorOffset offset) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) >= 0);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) < rndCont->GetSize ());
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (*rndCont)[current + static_cast<Offset> (offset)];
}


template <class RndCont>
inline GeneralRandomContainerIterator<RndCont>&		GeneralRandomContainerIterator<RndCont>::operator++ ()
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < rndCont->GetSize ());	// also detects when container manipulation causes invalid index

	current++;

	return *this;
}


template <class RndCont>
inline GeneralRandomContainerIterator<RndCont>		GeneralRandomContainerIterator<RndCont>::operator++ (int)
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < rndCont->GetSize ());	// also detects when container manipulation causes invalid index

	GeneralRandomContainerIterator result = *this;

	current++;

	return result;
}


template <class RndCont>
inline GeneralRandomContainerIterator<RndCont>&		GeneralRandomContainerIterator<RndCont>::operator-- ()
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current > 0);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	current--;

	return *this;
}


template <class RndCont>
inline GeneralRandomContainerIterator<RndCont>		GeneralRandomContainerIterator<RndCont>::operator-- (int)
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current > 0);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	GeneralRandomContainerIterator result = *this;

	current--;

	return result;
}


template <class RndCont>
inline GeneralRandomContainerIterator<RndCont>		GeneralRandomContainerIterator<RndCont>::operator+ (IteratorOffset offset) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) >= 0);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) <= rndCont->GetSize ());
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return GeneralRandomContainerIterator (*rndCont, current + static_cast<Offset> (offset));
}


template <class RndCont>
inline GeneralRandomContainerIterator<RndCont>		GeneralRandomContainerIterator<RndCont>::operator- (IteratorOffset offset) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current - static_cast<Offset> (offset) >= 0);
	PRECOND_DEPRECATED (current - static_cast<Offset> (offset) <= rndCont->GetSize ());
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return GeneralRandomContainerIterator (*rndCont, current - static_cast<Offset> (offset));
}


template <class RndCont>
inline IteratorOffset	GeneralRandomContainerIterator<RndCont>::operator- (const GeneralRandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return static_cast<IteratorOffset> (current) - static_cast<IteratorOffset> (rightOp.current);
}


template <class RndCont>
inline GeneralRandomContainerIterator<RndCont>&		GeneralRandomContainerIterator<RndCont>::operator+= (IteratorOffset offset)
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) >= 0);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) <= rndCont->GetSize ());
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	current += static_cast<Offset> (offset);

	return *this;
}


template <class RndCont>
inline GeneralRandomContainerIterator<RndCont>&		GeneralRandomContainerIterator<RndCont>::operator-= (IteratorOffset offset)
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current - static_cast<Offset> (offset) >= 0);
	PRECOND_DEPRECATED (current - static_cast<Offset> (offset) <= rndCont->GetSize ());
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	current -= static_cast<Offset> (offset);

	return *this;
}


template <class RndCont>
inline bool		GeneralRandomContainerIterator<RndCont>::operator== (const GeneralRandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current == rightOp.current);
}


template <class RndCont>
inline bool		GeneralRandomContainerIterator<RndCont>::operator!= (const GeneralRandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current != rightOp.current);
}


template <class RndCont>
inline bool		GeneralRandomContainerIterator<RndCont>::operator< (const GeneralRandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current < rightOp.current);
}


template <class RndCont>
inline bool		GeneralRandomContainerIterator<RndCont>::operator<= (const GeneralRandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current <= rightOp.current);
}


template <class RndCont>
inline bool		GeneralRandomContainerIterator<RndCont>::operator> (const GeneralRandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current > rightOp.current);
}


template <class RndCont>
inline bool		GeneralRandomContainerIterator<RndCont>::operator>= (const GeneralRandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current >= rightOp.current);
}


template <class RndCont>
inline bool		GeneralRandomContainerIterator<RndCont>::operator== (std::nullptr_t) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current >= rndCont->GetSize ());
}


template <class RndCont>
inline bool		GeneralRandomContainerIterator<RndCont>::operator!= (std::nullptr_t) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current < rndCont->GetSize ());
}


template <class RndCont>
inline RndCont*		GeneralRandomContainerIterator<RndCont>::GetTarget (void) const
{
	return rndCont;
}


template <class RndCont>
inline UIndex	GeneralRandomContainerIterator<RndCont>::GetIndex (void) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);

	return current;
}


template <class RndCont>
IForwardIterator<typename GeneralRandomContainerIterator<RndCont>::ValueType>*		GeneralRandomContainerIterator<RndCont>::CreateClone (void) const
{
	return new GeneralRandomContainerIterator (*this);
}


template <class RndCont>
IConstForwardIterator<typename GeneralRandomContainerIterator<RndCont>::ValueType>*		GeneralRandomContainerIterator<RndCont>::CreateConstClone (void) const
{
	return new ConstGeneralRandomContainerIterator<RndCont> (*this);
}


template <class RndCont>
bool	GeneralRandomContainerIterator<RndCont>::IsEnd (void) const
{
	return operator== (nullptr);
}


template <class RndCont>
typename GeneralRandomContainerIterator<RndCont>::ValueType&	GeneralRandomContainerIterator<RndCont>::Get (IteratorOffset offset) const
{
	return operator[] (offset);
}


template <class RndCont>
void	GeneralRandomContainerIterator<RndCont>::Add (IteratorOffset offset)
{
	operator+= (offset);
}


template <class RndCont>
IteratorOffset	GeneralRandomContainerIterator<RndCont>::GetDifference (const IRandomIterator<ValueType>* rightOp) const
{
	NULL_PTR_CHECK (rightOp);

	const GeneralRandomContainerIterator* ro = dynamic_cast<const GeneralRandomContainerIterator*> (rightOp);
	TYPE_CHECK (ro != nullptr);

	return operator- (*ro);
}

}	// namespace GS



// === Class ConstGeneralRandomContainerIterator =======================================================================

namespace GS {

template <class RndCont>
inline ConstGeneralRandomContainerIterator<RndCont>::ConstGeneralRandomContainerIterator ():
	ConstRandomIterator<typename ConstGeneralRandomContainerIterator<RndCont>::ValueType> (GetIteratorInterface ()),
	rndCont (nullptr),
	current (0)
{
}


template <class RndCont>
inline ConstGeneralRandomContainerIterator<RndCont>::ConstGeneralRandomContainerIterator (const RndCont& target_, UIndex idx):
	ConstRandomIterator<typename ConstGeneralRandomContainerIterator<RndCont>::ValueType> (GetIteratorInterface ()),
	rndCont (&target_),
	current (idx)
{
	NULL_REF_CHECK (target_);
	REF_CHECK (idx <= target_.GetSize ());
}


template <class RndCont>
inline ConstGeneralRandomContainerIterator<RndCont>::ConstGeneralRandomContainerIterator (const ConstGeneralRandomContainerIterator& source):
	ConstRandomIterator<typename ConstGeneralRandomContainerIterator<RndCont>::ValueType> (GetIteratorInterface ()),
	rndCont (source.rndCont),
	current (source.current)
{
	NULL_REF_CHECK (source);
}


template <class RndCont>
inline ConstGeneralRandomContainerIterator<RndCont>::ConstGeneralRandomContainerIterator (const GeneralRandomContainerIterator<RndCont>& source):
	ConstRandomIterator<typename ConstGeneralRandomContainerIterator<RndCont>::ValueType> (GetIteratorInterface ()),
	rndCont (source.rndCont),
	current (source.current)
{
	NULL_REF_CHECK (source);
}


template <class RndCont>
inline ConstGeneralRandomContainerIterator<RndCont>&	ConstGeneralRandomContainerIterator<RndCont>::operator= (const ConstGeneralRandomContainerIterator& source)
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
void	ConstGeneralRandomContainerIterator<RndCont>::Assign (const IConstForwardIterator<ValueType>* /*source*/)
{
	// ConstGeneralRandomContainerIterator contains own realization of the IConstRandomIterator interface
	// working on members in this class which are copied from the source iterator
}


template <class RndCont>
inline ConstGeneralRandomContainerIterator<RndCont>&	ConstGeneralRandomContainerIterator<RndCont>::operator= (const GeneralRandomContainerIterator<RndCont>& source)
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
void	ConstGeneralRandomContainerIterator<RndCont>::Assign (const IForwardIterator<ValueType>* /*source*/)
{
	// ConstGeneralRandomContainerIterator contains own realization of the IConstRandomIterator interface
	// working on members in this class which are copied from the source iterator
}


template <class RndCont>
inline ConstGeneralRandomContainerIterator<RndCont>::~ConstGeneralRandomContainerIterator ()
{
	this->target = nullptr;
}


template <class RndCont>
inline const typename ConstGeneralRandomContainerIterator<RndCont>::ValueType&		ConstGeneralRandomContainerIterator<RndCont>::operator* () const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < rndCont->GetSize ());

	return (*rndCont)[current];
}


template <class RndCont>
inline const typename ConstGeneralRandomContainerIterator<RndCont>::ValueType*		ConstGeneralRandomContainerIterator<RndCont>::operator-> () const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < rndCont->GetSize ());

	return &(*rndCont)[current];
}


template <class RndCont>
inline const typename ConstGeneralRandomContainerIterator<RndCont>::ValueType&		ConstGeneralRandomContainerIterator<RndCont>::operator[] (IteratorOffset offset) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) >= 0);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) < rndCont->GetSize ());
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (*rndCont)[current + static_cast<Offset> (offset)];
}


template <class RndCont>
inline ConstGeneralRandomContainerIterator<RndCont>&	ConstGeneralRandomContainerIterator<RndCont>::operator++ ()
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < rndCont->GetSize ());	// also detects when container manipulation causes invalid index

	current++;

	return *this;
}


template <class RndCont>
inline ConstGeneralRandomContainerIterator<RndCont>		ConstGeneralRandomContainerIterator<RndCont>::operator++ (int)
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current < rndCont->GetSize ());	// also detects when container manipulation causes invalid index

	ConstGeneralRandomContainerIterator result = *this;

	current++;

	return result;
}


template <class RndCont>
inline ConstGeneralRandomContainerIterator<RndCont>&	ConstGeneralRandomContainerIterator<RndCont>::operator-- ()
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current > 0);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	current--;

	return *this;
}


template <class RndCont>
inline ConstGeneralRandomContainerIterator<RndCont>		ConstGeneralRandomContainerIterator<RndCont>::operator-- (int)
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current > 0);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	ConstGeneralRandomContainerIterator result = *this;

	current--;

	return result;
}


template <class RndCont>
inline ConstGeneralRandomContainerIterator<RndCont>		ConstGeneralRandomContainerIterator<RndCont>::operator+ (IteratorOffset offset) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) >= 0);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) <= rndCont->GetSize ());
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return ConstGeneralRandomContainerIterator (*rndCont, current + static_cast<Offset> (offset));
}


template <class RndCont>
inline ConstGeneralRandomContainerIterator<RndCont>		ConstGeneralRandomContainerIterator<RndCont>::operator- (IteratorOffset offset) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current - static_cast<Offset> (offset) >= 0);
	PRECOND_DEPRECATED (current - static_cast<Offset> (offset) <= rndCont->GetSize ());
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index

	return ConstGeneralRandomContainerIterator (*rndCont, current - static_cast<Offset> (offset));
}


template <class RndCont>
inline IteratorOffset	ConstGeneralRandomContainerIterator<RndCont>::operator- (const ConstGeneralRandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return static_cast<IteratorOffset> (current) - static_cast<IteratorOffset> (rightOp.current);
}


template <class RndCont>
inline ConstGeneralRandomContainerIterator<RndCont>&	ConstGeneralRandomContainerIterator<RndCont>::operator+= (IteratorOffset offset)
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) >= 0);
	PRECOND_DEPRECATED (current + static_cast<Offset> (offset) <= rndCont->GetSize ());
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	current += static_cast<Offset> (offset);

	return *this;
}


template <class RndCont>
inline ConstGeneralRandomContainerIterator<RndCont>&	ConstGeneralRandomContainerIterator<RndCont>::operator-= (IteratorOffset offset)
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current - static_cast<Offset> (offset) >= 0);
	PRECOND_DEPRECATED (current - static_cast<Offset> (offset) <= rndCont->GetSize ());
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	current -= static_cast<Offset> (offset);

	return *this;
}


template <class RndCont>
inline bool		ConstGeneralRandomContainerIterator<RndCont>::operator== (const ConstGeneralRandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current == rightOp.current);
}


template <class RndCont>
inline bool		ConstGeneralRandomContainerIterator<RndCont>::operator!= (const ConstGeneralRandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current != rightOp.current);
}


template <class RndCont>
inline bool		ConstGeneralRandomContainerIterator<RndCont>::operator< (const ConstGeneralRandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current < rightOp.current);
}


template <class RndCont>
inline bool		ConstGeneralRandomContainerIterator<RndCont>::operator<= (const ConstGeneralRandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current <= rightOp.current);
}


template <class RndCont>
inline bool		ConstGeneralRandomContainerIterator<RndCont>::operator> (const ConstGeneralRandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current > rightOp.current);
}


template <class RndCont>
inline bool		ConstGeneralRandomContainerIterator<RndCont>::operator>= (const ConstGeneralRandomContainerIterator& rightOp) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.rndCont != nullptr);
	PRECOND_DEPRECATED (rndCont == rightOp.rndCont);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());					// to detect when container manipulation causes invalid index
	PRECOND_DEPRECATED (rightOp.current <= rightOp.rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current >= rightOp.current);
}


template <class RndCont>
inline bool		ConstGeneralRandomContainerIterator<RndCont>::operator== (std::nullptr_t) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current >= rndCont->GetSize ());
}


template <class RndCont>
inline bool		ConstGeneralRandomContainerIterator<RndCont>::operator!= (std::nullptr_t) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);
	PRECOND_DEPRECATED (current <= rndCont->GetSize ());	// to detect when container manipulation causes invalid index

	return (current < rndCont->GetSize ());
}


template <class RndCont>
inline const RndCont*	ConstGeneralRandomContainerIterator<RndCont>::GetTarget (void) const
{
	return rndCont;
}


template <class RndCont>
inline UIndex	ConstGeneralRandomContainerIterator<RndCont>::GetIndex (void) const
{
	PRECOND_DEPRECATED (rndCont != nullptr);

	return current;
}


template <class RndCont>
IConstForwardIterator<typename ConstGeneralRandomContainerIterator<RndCont>::ValueType>*	ConstGeneralRandomContainerIterator<RndCont>::CreateClone (void) const
{
	return new ConstGeneralRandomContainerIterator (*this);
}


template <class RndCont>
bool	ConstGeneralRandomContainerIterator<RndCont>::IsEnd (void) const
{
	return operator== (nullptr);
}


template <class RndCont>
const typename ConstGeneralRandomContainerIterator<RndCont>::ValueType&		ConstGeneralRandomContainerIterator<RndCont>::Get (IteratorOffset offset) const
{
	return operator[] (offset);
}


template <class RndCont>
void	ConstGeneralRandomContainerIterator<RndCont>::Add (IteratorOffset offset)
{
	operator+= (offset);
}


template <class RndCont>
IteratorOffset	ConstGeneralRandomContainerIterator<RndCont>::GetDifference (const IConstRandomIterator<ValueType>* rightOp) const
{
	NULL_PTR_CHECK (rightOp);

	const ConstGeneralRandomContainerIterator* ro = dynamic_cast<const ConstGeneralRandomContainerIterator*> (rightOp);
	TYPE_CHECK (ro != nullptr);

	return operator- (*ro);
}

}	// namespace GS


#endif
