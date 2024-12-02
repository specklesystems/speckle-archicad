
// *****************************************************************************
//
//                    Random iterator interfaces and wrappers
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined RANDOMITERATOR_HPP
#define RANDOMITERATOR_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "BidirectionalIterator.hpp"



// ========================= Interface IRandomIterator =========================

namespace GS {

template <class Type>
class IRandomIterator: public IBidirectionalIterator<Type> {
public:
	virtual Type&	Get (IteratorOffset offset) const = 0;

	virtual void	Add (IteratorOffset offset) = 0;
	virtual void	Sub (IteratorOffset offset) { Add (-offset); }

	virtual IteratorOffset	GetDifference (const IRandomIterator* rightOp) const = 0;

	virtual bool	IsLess	  (const IRandomIterator* rightOp) const { return (GetDifference (rightOp) < 0); }
	virtual bool	IsGreater (const IRandomIterator* rightOp) const { return (GetDifference (rightOp) > 0); }

		// Default implementations for some of the inherited operations

	virtual Type&	GetCurrent (void) const  override { return Get (0); }
	virtual void	Increment  (void)		 override { Add (1); }
	virtual void	Decrement  (void)		 override { Add (-1); }
	virtual bool	IsEqual	   (const IForwardIterator<Type>* rightOp) const  override { return (GetDifference (static_cast<const IRandomIterator*> (rightOp)) == 0); }

	// ----------------------------------------------------------------
	// Core operations to be implemented are:
	//
	//   CreateClone, CreateConstClone, IsEnd, Get, Add, GetDifference
	// ----------------------------------------------------------------
};

}	// namespace GS
// _________________________ Interface IRandomIterator _________________________



// =========================== Class RandomIterator ============================

namespace GS {

template <class Type>
class RandomIterator: public BidirectionalIterator<Type> {
public:
		// Constructors

	inline RandomIterator (IRandomIterator<Type>* wrapperTarget);
	inline RandomIterator (const RandomIterator& source);
	inline RandomIterator&	operator= (const RandomIterator& source);

		// User interface

	inline Type&	operator[] (IteratorOffset offset) const;

	inline RandomIterator&	operator++ ();
	inline RandomIterator	operator++ (int);

	inline RandomIterator&	operator-- ();
	inline RandomIterator	operator-- (int);

	inline RandomIterator	operator+  (IteratorOffset offset) const;
	inline RandomIterator	operator-  (IteratorOffset offset) const;
	inline IteratorOffset	operator-  (const RandomIterator& rightOp) const;
	inline RandomIterator&	operator+= (IteratorOffset offset);
	inline RandomIterator&	operator-= (IteratorOffset offset);

	inline bool		operator<  (const RandomIterator& rightOp) const;
	inline bool		operator<= (const RandomIterator& rightOp) const;
	inline bool		operator>  (const RandomIterator& rightOp) const;
	inline bool		operator>= (const RandomIterator& rightOp) const;
};



template <class Type>
inline RandomIterator<Type>::RandomIterator (IRandomIterator<Type>* wrapperTarget):
	BidirectionalIterator<Type> (wrapperTarget)
{
	NULL_PTR_CHECK (wrapperTarget);
}


template <class Type>
inline RandomIterator<Type>::RandomIterator (const RandomIterator& source):
	BidirectionalIterator<Type> (source)
{
	NULL_REF_CHECK (source);
}


template <class Type>
inline RandomIterator<Type>&	RandomIterator<Type>::operator= (const RandomIterator& source)
{
	NULL_REF_CHECK (source);

	BidirectionalIterator<Type>::operator= (source);

	return *this;
}


template <class Type>
inline Type&	RandomIterator<Type>::operator[] (IteratorOffset offset) const
{
	return static_cast<IRandomIterator<Type>*> (this->target)->Get (offset);
}


template <class Type>
inline RandomIterator<Type>&	RandomIterator<Type>::operator++ ()
{
	PRECOND_DEPRECATED (!this->target->IsEnd ());

	static_cast<IRandomIterator<Type>*> (this->target)->Increment ();

	return *this;
}


template <class Type>
inline RandomIterator<Type>		RandomIterator<Type>::operator++ (int)
{
	PRECOND_DEPRECATED (!this->target->IsEnd ());

	RandomIterator result = *this;

	static_cast<IRandomIterator<Type>*> (this->target)->Increment ();

	return result;
}


template <class Type>
inline RandomIterator<Type>&	RandomIterator<Type>::operator-- ()
{
	static_cast<IRandomIterator<Type>*> (this->target)->Decrement ();

	return *this;
}


template <class Type>
inline RandomIterator<Type>		RandomIterator<Type>::operator-- (int)
{
	RandomIterator result = *this;

	static_cast<IRandomIterator<Type>*> (this->target)->Decrement ();

	return result;
}


template <class Type>
inline RandomIterator<Type>		RandomIterator<Type>::operator+ (IteratorOffset offset) const
{
	RandomIterator<Type> result = *this;

	result += static_cast<Offset> (offset);

	return result;
}


template <class Type>
inline RandomIterator<Type>		RandomIterator<Type>::operator- (IteratorOffset offset) const
{
	RandomIterator<Type> result = *this;

	result -= static_cast<Offset> (offset);

	return result;
}


template <class Type>
inline IteratorOffset	RandomIterator<Type>::operator- (const RandomIterator& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	return static_cast<IRandomIterator<Type>*> (this->target)->GetDifference (static_cast<IRandomIterator<Type>*> (rightOp.target));
}


template <class Type>
inline RandomIterator<Type>&	RandomIterator<Type>::operator+= (IteratorOffset offset)
{
	static_cast<IRandomIterator<Type>*> (this->target)->Add (offset);

	return *this;
}


template <class Type>
inline RandomIterator<Type>&	RandomIterator<Type>::operator-= (IteratorOffset offset)
{
	static_cast<IRandomIterator<Type>*> (this->target)->Sub (offset);

	return *this;
}


template <class Type>
inline bool		RandomIterator<Type>::operator< (const RandomIterator& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	return static_cast<IRandomIterator<Type>*> (this->target)->IsLess (static_cast<IRandomIterator<Type>*> (rightOp.target));
}


template <class Type>
inline bool		RandomIterator<Type>::operator<= (const RandomIterator& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	return !static_cast<IRandomIterator<Type>*> (this->target)->IsGreater (static_cast<IRandomIterator<Type>*> (rightOp.target));
}


template <class Type>
inline bool		RandomIterator<Type>::operator> (const RandomIterator& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	return static_cast<IRandomIterator<Type>*> (this->target)->IsGreater (static_cast<IRandomIterator<Type>*> (rightOp.target));
}


template <class Type>
inline bool		RandomIterator<Type>::operator>= (const RandomIterator& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	return !static_cast<IRandomIterator<Type>*> (this->target)->IsLess (static_cast<IRandomIterator<Type>*> (rightOp.target));
}

}	// namespace GS
// ___________________________ Class RandomIterator ____________________________



// ====================== Interface IConstRandomIterator =======================

namespace GS {

template <class Type>
class IConstRandomIterator: public IConstBidirectionalIterator<Type> {
public:
	virtual const Type&		Get (IteratorOffset offset) const = 0;

	virtual void	Add (IteratorOffset offset) = 0;
	virtual void	Sub (IteratorOffset offset) { Add (-offset); }

	virtual IteratorOffset	GetDifference (const IConstRandomIterator* rightOp) const = 0;

	virtual bool	IsLess	  (const IConstRandomIterator* rightOp) const { return (GetDifference (rightOp) < 0); }
	virtual bool	IsGreater (const IConstRandomIterator* rightOp) const { return (GetDifference (rightOp) > 0); }

			// Default implementations for some of the inherited operations

	virtual const Type&	 GetCurrent  (void) const  override { return Get (0); }
	virtual void	Increment (void)  override { Add (1); }
	virtual void	Decrement (void)  override { Add (-1); }
	virtual bool	IsEqual	  (const IConstForwardIterator<Type>* rightOp) const  override { return (GetDifference (static_cast<const IConstRandomIterator*> (rightOp)) == 0); }

	// ----------------------------------------------
	// Core operations to be implemented are:
	//
	//   CreateClone, IsEnd, Get, Add, GetDifference
	// ----------------------------------------------
};

}	// namespace GS
// ______________________ Interface IConstRandomIterator _______________________



// ========================= Class ConstRandomIterator =========================

namespace GS {

template <class Type>
class ConstRandomIterator: public ConstBidirectionalIterator<Type> {
public:
		// Constructors

	inline ConstRandomIterator (IConstRandomIterator<Type>* wrapperTarget);
	inline ConstRandomIterator (const ConstRandomIterator& source);
	inline ConstRandomIterator (const RandomIterator<Type>& source);
	inline ConstRandomIterator&	operator= (const ConstRandomIterator& source);
	inline ConstRandomIterator&	operator= (const RandomIterator<Type>& source);

		// User interface

	inline const Type&	operator[] (IteratorOffset offset) const;

	inline ConstRandomIterator&	operator++ ();
	inline ConstRandomIterator	operator++ (int);

	inline ConstRandomIterator&	operator-- ();
	inline ConstRandomIterator	operator-- (int);

	inline ConstRandomIterator	operator+  (IteratorOffset offset) const;
	inline ConstRandomIterator	operator-  (IteratorOffset offset) const;
	inline IteratorOffset				operator-  (const ConstRandomIterator& rightOp) const;
	inline ConstRandomIterator&	operator+= (IteratorOffset offset);
	inline ConstRandomIterator&	operator-= (IteratorOffset offset);

	inline bool		operator<  (const ConstRandomIterator& rightOp) const;
	inline bool		operator<= (const ConstRandomIterator& rightOp) const;
	inline bool		operator>  (const ConstRandomIterator& rightOp) const;
	inline bool		operator>= (const ConstRandomIterator& rightOp) const;
};



template <class Type>
inline ConstRandomIterator<Type>::ConstRandomIterator (IConstRandomIterator<Type>* wrapperTarget):
	ConstBidirectionalIterator<Type> (wrapperTarget)
{
	NULL_PTR_CHECK (wrapperTarget);
}


template <class Type>
inline ConstRandomIterator<Type>::ConstRandomIterator (const ConstRandomIterator& source):
	ConstBidirectionalIterator<Type> (source)
{
	NULL_REF_CHECK (source);
}


template <class Type>
inline ConstRandomIterator<Type>::ConstRandomIterator (const RandomIterator<Type>& source):
	ConstBidirectionalIterator<Type> (source)
{
	NULL_REF_CHECK (source);
}


template <class Type>
inline ConstRandomIterator<Type>&	ConstRandomIterator<Type>::operator= (const ConstRandomIterator& source)
{
	NULL_REF_CHECK (source);

	ConstBidirectionalIterator<Type>::operator= (source);

	return *this;
}


template <class Type>
inline ConstRandomIterator<Type>&	ConstRandomIterator<Type>::operator= (const RandomIterator<Type>& source)
{
	NULL_REF_CHECK (source);

	ConstBidirectionalIterator<Type>::operator= (source);

	return *this;
}


template <class Type>
inline const Type&	ConstRandomIterator<Type>::operator[] (IteratorOffset offset) const
{
	return static_cast<IConstRandomIterator<Type>*> (this->target)->Get (offset);
}


template <class Type>
inline ConstRandomIterator<Type>&	ConstRandomIterator<Type>::operator++ ()
{
	PRECOND_DEPRECATED (!this->target->IsEnd ());

	static_cast<IConstRandomIterator<Type>*> (this->target)->Increment ();

	return *this;
}


template <class Type>
inline ConstRandomIterator<Type>	ConstRandomIterator<Type>::operator++ (int)
{
	PRECOND_DEPRECATED (!this->target->IsEnd ());

	ConstRandomIterator result = *this;

	static_cast<IConstRandomIterator<Type>*> (this->target)->Increment ();

	return result;
}


template <class Type>
inline ConstRandomIterator<Type>&	ConstRandomIterator<Type>::operator-- ()
{
	static_cast<IConstRandomIterator<Type>*> (this->target)->Decrement ();

	return *this;
}


template <class Type>
inline ConstRandomIterator<Type>	ConstRandomIterator<Type>::operator-- (int)
{
	ConstRandomIterator result = *this;

	static_cast<IConstRandomIterator<Type>*> (this->target)->Decrement ();

	return result;
}


template <class Type>
inline ConstRandomIterator<Type>	ConstRandomIterator<Type>::operator+ (IteratorOffset offset) const
{
	ConstRandomIterator<Type> result = *this;

	result += static_cast<Offset> (offset);

	return result;
}


template <class Type>
inline ConstRandomIterator<Type>	ConstRandomIterator<Type>::operator- (IteratorOffset offset) const
{
	ConstRandomIterator<Type> result = *this;

	result -= static_cast<Offset> (offset);

	return result;
}


template <class Type>
inline IteratorOffset	ConstRandomIterator<Type>::operator- (const ConstRandomIterator& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	return static_cast<IConstRandomIterator<Type>*> (this->target)->GetDifference (static_cast<IConstRandomIterator<Type>*> (rightOp.target));
}


template <class Type>
inline ConstRandomIterator<Type>&	ConstRandomIterator<Type>::operator+= (IteratorOffset offset)
{
	static_cast<IConstRandomIterator<Type>*> (this->target)->Add (offset);

	return *this;
}


template <class Type>
inline ConstRandomIterator<Type>&	ConstRandomIterator<Type>::operator-= (IteratorOffset offset)
{
	static_cast<IConstRandomIterator<Type>*> (this->target)->Sub (offset);

	return *this;
}


template <class Type>
inline bool		ConstRandomIterator<Type>::operator< (const ConstRandomIterator& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	return static_cast<IConstRandomIterator<Type>*> (this->target)->IsLess (static_cast<IConstRandomIterator<Type>*> (rightOp.target));
}


template <class Type>
inline bool		ConstRandomIterator<Type>::operator<= (const ConstRandomIterator& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	return !static_cast<IConstRandomIterator<Type>*> (this->target)->IsGreater (static_cast<IConstRandomIterator<Type>*> (rightOp.target));
}


template <class Type>
inline bool		ConstRandomIterator<Type>::operator> (const ConstRandomIterator& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	return static_cast<IConstRandomIterator<Type>*> (this->target)->IsGreater (static_cast<IConstRandomIterator<Type>*> (rightOp.target));
}


template <class Type>
inline bool		ConstRandomIterator<Type>::operator>= (const ConstRandomIterator& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	return !static_cast<IConstRandomIterator<Type>*> (this->target)->IsLess (static_cast<IConstRandomIterator<Type>*> (rightOp.target));
}

}	// namespace GS
// _________________________ Class ConstRandomIterator _________________________


#endif
