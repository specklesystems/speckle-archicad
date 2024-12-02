
// *****************************************************************************
//
//     Classes BidirectionalItemIteratorBase and ConstBidirectionalItemIteratorBase
//
// Module:			Geometry?GSRoot
// Namespace:		GS
// Contact person:	RA
//
// SG compatible
//
// Requirements:
//   Target item should have the following methods:
//     - Type&        GetCurrent (const Item& item);          -> for non-const iterators
//     - const Type&  GetCurrent (const Item& item) const;    -> for const iterators
//     - void         Next       (Item& item) const;
//     - void         Prev       (Item& item) const;
//     - bool         IsEqual    (const Item& item1, const Item& item2) const;
//     - bool         IsBegin    (const Item& item) const;
//     - bool         IsEnd      (const Item& item) const;
//     - bool         IsValid    () const;
//     - bool         CheckType  (const Item& item) const;
//
// *****************************************************************************


#if !defined BIDIRECTIONALITEMITERATORBASE_HPP
#define BIDIRECTIONALITEMITERATORBASE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "BidirectionalIterator.hpp"



// ====================== Class BidirectionalItemIteratorBase ======================

namespace GS {

template <class Cont, class Item, class Type>
class ConstBidirectionalItemIteratorBase;


template <class Cont, class Item, class Type>
class BidirectionalItemIteratorBase: public BidirectionalIterator<Type>,
									 public IBidirectionalIterator<Type>
{
private:
	Item	item;	// current item of the iterator

	inline bool		CheckType (const BidirectionalItemIteratorBase& rightOp) const;

	inline IBidirectionalIterator<Type>*	GetIteratorInterface (void) { return this; }

	friend class ConstBidirectionalItemIteratorBase<Cont, Item, Type>;

protected:
	virtual void	Assign (const IForwardIterator<Type>* source) override;

	virtual IBidirectionalIterator<Type>*		CreateClone      (void) const override;
	virtual IConstBidirectionalIterator<Type>*	CreateConstClone (void) const override;

	virtual Type&	GetCurrent (void) const override;
	virtual void	Increment  (void) override;
	virtual void	Decrement  (void) override;
	virtual bool	IsEqual	   (const IForwardIterator<Type>* rightOp) const override;
	virtual bool	IsEnd	   (void) const override;

public:
		// Constructors

	inline BidirectionalItemIteratorBase ();
	inline BidirectionalItemIteratorBase (const Item& initialItem);
	inline BidirectionalItemIteratorBase (const BidirectionalItemIteratorBase& source);
	inline BidirectionalItemIteratorBase&	operator= (const BidirectionalItemIteratorBase& source);
	inline ~BidirectionalItemIteratorBase ();

		// User interface

	inline Type&	operator*  ();
	inline Type*	operator-> ();

	inline BidirectionalItemIteratorBase&	operator++ ();
	inline BidirectionalItemIteratorBase	operator++ (int);

	inline BidirectionalItemIteratorBase&	operator-- ();
	inline BidirectionalItemIteratorBase	operator-- (int);

	inline bool		operator== (const BidirectionalItemIteratorBase& rightOp) const;
	inline bool		operator!= (const BidirectionalItemIteratorBase& rightOp) const;

	inline bool		operator== (std::nullptr_t) const;
	inline bool		operator!= (std::nullptr_t) const;

	inline Cont*	GetTarget (void) const;
	inline const Item& GetItem () const;
};

}	// namespace GS
// ______________________ Class BidirectionalItemIteratorBase ______________________



// =================== Class ConstBidirectionalItemIteratorBase ====================

namespace GS {

template <class Cont, class Item, class Type>
class ConstBidirectionalItemIteratorBase: public ConstBidirectionalIterator<Type>,
									  public IConstBidirectionalIterator<Type>
{
private:
	Item		item;	// current item of the iterator

	inline bool		CheckType (const ConstBidirectionalItemIteratorBase& rightOp) const;

	inline IConstBidirectionalIterator<Type>*	GetIteratorInterface (void) { return this; }

protected:
	virtual void	Assign (const IConstForwardIterator<Type>* source) override;
	virtual void	Assign (const IForwardIterator<Type>* source) override;

	virtual IConstBidirectionalIterator<Type>*	CreateClone (void) const override;

	virtual const Type&	GetCurrent (void) const override;
	virtual void		Increment  (void) override;
	virtual void		Decrement  (void) override;
	virtual bool		IsEqual	   (const IConstForwardIterator<Type>* rightOp) const override;
	virtual bool		IsEnd	   (void) const override;
public:
		// Constructors

	inline ConstBidirectionalItemIteratorBase ();
	inline ConstBidirectionalItemIteratorBase (const Item& initialItem);
	inline ConstBidirectionalItemIteratorBase (const ConstBidirectionalItemIteratorBase& source);
	inline ConstBidirectionalItemIteratorBase (const BidirectionalItemIteratorBase<Cont, Item, Type>& source);
	inline ConstBidirectionalItemIteratorBase&	operator= (const ConstBidirectionalItemIteratorBase& source);
	inline ConstBidirectionalItemIteratorBase&	operator= (const BidirectionalItemIteratorBase<Cont, Item, Type>& source);
	inline ~ConstBidirectionalItemIteratorBase ();

		// User interface

	inline const Type&	operator*  () const;
	inline const Type*	operator-> () const;

	inline ConstBidirectionalItemIteratorBase&	operator++ ();
	inline ConstBidirectionalItemIteratorBase	operator++ (int);

	inline ConstBidirectionalItemIteratorBase&	operator-- ();
	inline ConstBidirectionalItemIteratorBase	operator-- (int);

	inline bool		operator== (const ConstBidirectionalItemIteratorBase& rightOp) const;
	inline bool		operator!= (const ConstBidirectionalItemIteratorBase& rightOp) const;

	inline bool		operator== (std::nullptr_t) const;
	inline bool		operator!= (std::nullptr_t) const;

	inline const Cont*	GetTarget (void) const;
	inline const Item& GetItem () const;
};

}	// namespace GS
// ___________________ Class ConstBidirectionalItemIteratorBase ____________________



// ====================== Class BidirectionalItemIteratorBase ======================

namespace GS {

template <class Cont, class Item, class Type>
inline BidirectionalItemIteratorBase<Cont, Item, Type>::BidirectionalItemIteratorBase ():
	BidirectionalIterator<Type> (GetIteratorInterface ())
{
}


template <class Cont, class Item, class Type>
inline BidirectionalItemIteratorBase<Cont, Item, Type>::BidirectionalItemIteratorBase (const Item& initialItem):
	BidirectionalIterator<Type> (GetIteratorInterface ()),
	item (initialItem)
{
	NULL_REF_CHECK (initialItem);
}


template <class Cont, class Item, class Type>
inline BidirectionalItemIteratorBase<Cont, Item, Type>::BidirectionalItemIteratorBase (const BidirectionalItemIteratorBase& source):
	BidirectionalIterator<Type> (GetIteratorInterface ()),
	item (source.item)
{
	NULL_REF_CHECK (source);
}


template <class Cont, class Item, class Type>
inline BidirectionalItemIteratorBase<Cont, Item, Type>&	BidirectionalItemIteratorBase<Cont, Item, Type>::operator= (const BidirectionalItemIteratorBase& source)
{
	NULL_REF_CHECK (source);

	if (this != static_cast<const void*> (&source)) {
		BidirectionalIterator<Type>::operator= (source);

		item  = source.item;
	}

	return *this;
}


template <class Cont, class Item, class Type>
void	BidirectionalItemIteratorBase<Cont, Item, Type>::Assign (const IForwardIterator<Type>* /*source*/)
{
	// BidirectionalItemIteratorBase contains own realization of the IBidirectionalterator interface
	// working on members in this class which are copied from the source iterator
}


template <class Cont, class Item, class Type>
inline BidirectionalItemIteratorBase<Cont, Item, Type>::~BidirectionalItemIteratorBase ()
{
	this->target = nullptr;
}


template <class Cont, class Item, class Type>
inline Type&	BidirectionalItemIteratorBase<Cont, Item, Type>::operator* ()
{
	PRECOND_DEPRECATED (item.IsValid ());
	PRECOND_DEPRECATED (!item.IsEnd ());

	return item.GetCurrent ();
}


template <class Cont, class Item, class Type>
inline Type*	BidirectionalItemIteratorBase<Cont, Item, Type>::operator-> ()
{
	PRECOND_DEPRECATED (item.IsValid ());
	PRECOND_DEPRECATED (!item.IsEnd ());

	return &item.GetCurrent ();
}


template <class Cont, class Item, class Type>
inline BidirectionalItemIteratorBase<Cont, Item, Type>&	BidirectionalItemIteratorBase<Cont, Item, Type>::operator++ ()
{
	PRECOND_DEPRECATED (item.IsValid ());
	PRECOND_DEPRECATED (!item.IsEnd ());

	item.Next ();

	return *this;
}


template <class Cont, class Item, class Type>
inline BidirectionalItemIteratorBase<Cont, Item, Type>		BidirectionalItemIteratorBase<Cont, Item, Type>::operator++ (int)
{
	PRECOND_DEPRECATED (item.IsValid ());
	PRECOND_DEPRECATED (!item.IsEnd ());

	BidirectionalItemIteratorBase result = *this;

	item.Next ();

	return result;
}


template <class Cont, class Item, class Type>
inline BidirectionalItemIteratorBase<Cont, Item, Type>&	BidirectionalItemIteratorBase<Cont, Item, Type>::operator-- ()
{
	PRECOND_DEPRECATED (item.IsValid ());
	PRECOND_DEPRECATED (!item.IsBegin ());

	item.Prev ();

	return *this;
}


template <class Cont, class Item, class Type>
inline BidirectionalItemIteratorBase<Cont, Item, Type>		BidirectionalItemIteratorBase<Cont, Item, Type>::operator-- (int)
{
	PRECOND_DEPRECATED (item.IsValid ());
	PRECOND_DEPRECATED (!item.IsBegin ());

	BidirectionalItemIteratorBase result = *this;

	item.Prev ();

	return result;
}


template <class Cont, class Item, class Type>
inline bool		BidirectionalItemIteratorBase<Cont, Item, Type>::operator== (const BidirectionalItemIteratorBase& rightOp) const
{
	PRECOND_DEPRECATED (item.IsValid ());
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.item.IsValid ());
	TYPE_CHECK (CheckType (rightOp));

	return item.IsEqual (rightOp.item);
}


template <class Cont, class Item, class Type>
inline bool		BidirectionalItemIteratorBase<Cont, Item, Type>::operator!= (const BidirectionalItemIteratorBase& rightOp) const
{
	PRECOND_DEPRECATED (item.IsValid ());
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.item.IsValid ());
	TYPE_CHECK (CheckType (rightOp));

	return !item.IsEqual (rightOp.item);
}


template <class Cont, class Item, class Type>
inline bool		BidirectionalItemIteratorBase<Cont, Item, Type>::operator== (std::nullptr_t) const
{
	PRECOND_DEPRECATED (item.IsValid ());

	return item.IsEnd ();
}


template <class Cont, class Item, class Type>
inline bool		BidirectionalItemIteratorBase<Cont, Item, Type>::operator!= (std::nullptr_t) const
{
	PRECOND_DEPRECATED (item.IsValid ());

	return !item.IsEnd ();
}


template <class Cont, class Item, class Type>
inline Cont*	BidirectionalItemIteratorBase<Cont, Item, Type>::GetTarget (void) const
{
	return item.GetTarget ();
}

template <class Cont, class Item, class Type>
inline const Item&	BidirectionalItemIteratorBase<Cont, Item, Type>::GetItem (void) const
{
	return item;
}

template <class Cont, class Item, class Type>
IBidirectionalIterator<Type>*	BidirectionalItemIteratorBase<Cont, Item, Type>::CreateClone (void) const
{
	return new BidirectionalItemIteratorBase (*this);
}


template <class Cont, class Item, class Type>
IConstBidirectionalIterator<Type>*	BidirectionalItemIteratorBase<Cont, Item, Type>::CreateConstClone (void) const
{
	return new ConstBidirectionalItemIteratorBase<Cont, Item, Type> (*this);
}


template <class Cont, class Item, class Type>
Type&	BidirectionalItemIteratorBase<Cont, Item, Type>::GetCurrent (void) const
{
	PRECOND_DEPRECATED (item.IsValid ());
	PRECOND_DEPRECATED (!item.IsEnd ());

	return const_cast<Item*> (&item)->GetCurrent ();
}


template <class Cont, class Item, class Type>
void	BidirectionalItemIteratorBase<Cont, Item, Type>::Increment (void)
{
	operator++ ();
}


template <class Cont, class Item, class Type>
void	BidirectionalItemIteratorBase<Cont, Item, Type>::Decrement (void)
{
	operator-- ();
}


template <class Cont, class Item, class Type>
bool	BidirectionalItemIteratorBase<Cont, Item, Type>::IsEqual (const IForwardIterator<Type>* rightOp) const
{
	NULL_PTR_CHECK (rightOp);

	const BidirectionalItemIteratorBase* ro = dynamic_cast<const BidirectionalItemIteratorBase*> (rightOp);
	TYPE_CHECK (ro != nullptr);

	return operator== (*ro);
}


template <class Cont, class Item, class Type>
bool	BidirectionalItemIteratorBase<Cont, Item, Type>::IsEnd (void) const
{
	return operator== (nullptr);
}


template <class Cont, class Item, class Type>
inline bool		BidirectionalItemIteratorBase<Cont, Item, Type>::CheckType (const BidirectionalItemIteratorBase& rightOp) const
{
	return item.CheckType (rightOp.item);
}

}	// namespace GS
// ______________________ Class BidirectionalItemIteratorBase ______________________



// =================== Class ConstBidirectionalItemIteratorBase ====================

namespace GS {

template <class Cont, class Item, class Type>
inline ConstBidirectionalItemIteratorBase<Cont, Item, Type>::ConstBidirectionalItemIteratorBase ():
	ConstBidirectionalIterator<Type> (GetIteratorInterface ())
{
}


template <class Cont, class Item, class Type>
inline ConstBidirectionalItemIteratorBase<Cont, Item, Type>::ConstBidirectionalItemIteratorBase (const Item& initialItem):
	ConstBidirectionalIterator<Type> (GetIteratorInterface ()),
	item (initialItem)
{
	NULL_REF_CHECK (initialItem);
}


template <class Cont, class Item, class Type>
inline ConstBidirectionalItemIteratorBase<Cont, Item, Type>::ConstBidirectionalItemIteratorBase (const ConstBidirectionalItemIteratorBase& source):
	ConstBidirectionalIterator<Type> (GetIteratorInterface ()),
	item (source.item)
{
	NULL_REF_CHECK (source);
}


template <class Cont, class Item, class Type>
inline ConstBidirectionalItemIteratorBase<Cont, Item, Type>::ConstBidirectionalItemIteratorBase (const BidirectionalItemIteratorBase<Cont, Item, Type>& source):
	ConstBidirectionalIterator<Type> (GetIteratorInterface ()),
	item (source.item)
{
	NULL_REF_CHECK (source);
}


template <class Cont, class Item, class Type>
inline ConstBidirectionalItemIteratorBase<Cont, Item, Type>&	ConstBidirectionalItemIteratorBase<Cont, Item, Type>::operator= (const ConstBidirectionalItemIteratorBase& source)
{
	NULL_REF_CHECK (source);

	if (this != &source) {
		ConstBidirectionalIterator<Type>::operator= (source);

		item = source.item;
	}

	return *this;
}


template <class Cont, class Item, class Type>
void	ConstBidirectionalItemIteratorBase<Cont, Item, Type>::Assign (const IConstForwardIterator<Type>* /*source*/)
{
	// ConstBidirectionalItemIteratorBase contains own realization of the IConstBidirectionalterator interface
	// working on members in this class which are copied from the source iterator
}


template <class Cont, class Item, class Type>
inline ConstBidirectionalItemIteratorBase<Cont, Item, Type>&	ConstBidirectionalItemIteratorBase<Cont, Item, Type>::operator= (const BidirectionalItemIteratorBase<Cont, Item, Type>& source)
{
	NULL_REF_CHECK (source);

	if (this != &source) {
		ConstBidirectionalIterator<Type>::operator= (source);

		item = source.item;
	}

	return *this;
}


template <class Cont, class Item, class Type>
void	ConstBidirectionalItemIteratorBase<Cont, Item, Type>::Assign (const IForwardIterator<Type>* /*source*/)
{
	// ConstBidirectionalItemIteratorBase contains own realization of the IConstBidirectionalterator interface
	// working on members in this class which are copied from the source iterator
}


template <class Cont, class Item, class Type>
inline ConstBidirectionalItemIteratorBase<Cont, Item, Type>::~ConstBidirectionalItemIteratorBase ()
{
	this->target = nullptr;
}


template <class Cont, class Item, class Type>
inline const Type&	ConstBidirectionalItemIteratorBase<Cont, Item, Type>::operator* () const
{
	PRECOND_DEPRECATED (item.IsValid ());
	PRECOND_DEPRECATED (!item.IsEnd ());

	return item.GetCurrent ();
}


template <class Cont, class Item, class Type>
inline const Type*	ConstBidirectionalItemIteratorBase<Cont, Item, Type>::operator-> () const
{
	PRECOND_DEPRECATED (item.IsValid ());
	PRECOND_DEPRECATED (!item.IsEnd ());

	return &item.GetCurrent ();
}


template <class Cont, class Item, class Type>
inline ConstBidirectionalItemIteratorBase<Cont, Item, Type>&	ConstBidirectionalItemIteratorBase<Cont, Item, Type>::operator++ ()
{
	PRECOND_DEPRECATED (item.IsValid ());
	PRECOND_DEPRECATED (!item.IsEnd ());

	item.Next ();

	return *this;
}


template <class Cont, class Item, class Type>
inline ConstBidirectionalItemIteratorBase<Cont, Item, Type>	ConstBidirectionalItemIteratorBase<Cont, Item, Type>::operator++ (int)
{
	PRECOND_DEPRECATED (item.IsValid ());
	PRECOND_DEPRECATED (!item.IsEnd ());

	ConstBidirectionalItemIteratorBase result = *this;

	item.Next ();

	return result;
}


template <class Cont, class Item, class Type>
inline ConstBidirectionalItemIteratorBase<Cont, Item, Type>&	ConstBidirectionalItemIteratorBase<Cont, Item, Type>::operator-- ()
{
	PRECOND_DEPRECATED (item.IsValid ());
	PRECOND_DEPRECATED (!item.IsBegin ());

	item.Prev ();

	return *this;
}


template <class Cont, class Item, class Type>
inline ConstBidirectionalItemIteratorBase<Cont, Item, Type>	ConstBidirectionalItemIteratorBase<Cont, Item, Type>::operator-- (int)
{
	PRECOND_DEPRECATED (item.IsValid ());
	PRECOND_DEPRECATED (!item.IsBegin ());

	ConstBidirectionalItemIteratorBase result = *this;

	item.Prev ();

	return result;
}


template <class Cont, class Item, class Type>
inline bool		ConstBidirectionalItemIteratorBase<Cont, Item, Type>::operator== (const ConstBidirectionalItemIteratorBase& rightOp) const
{
	PRECOND_DEPRECATED (item.IsValid ());
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.item.IsValid ());
	TYPE_CHECK (CheckType (rightOp));

	return item.IsEqual (rightOp.item);
}


template <class Cont, class Item, class Type>
inline bool		ConstBidirectionalItemIteratorBase<Cont, Item, Type>::operator!= (const ConstBidirectionalItemIteratorBase& rightOp) const
{
	PRECOND_DEPRECATED (item.IsValid ());
	NULL_REF_CHECK (rightOp);
	PRECOND_DEPRECATED (rightOp.item.IsValid ());
	TYPE_CHECK (CheckType (rightOp));

	return !item.IsEqual (rightOp.item);
}


template <class Cont, class Item, class Type>
inline bool		ConstBidirectionalItemIteratorBase<Cont, Item, Type>::operator== (std::nullptr_t) const
{
	PRECOND_DEPRECATED (item.IsValid ());

	return item.IsEnd ();
}


template <class Cont, class Item, class Type>
inline bool		ConstBidirectionalItemIteratorBase<Cont, Item, Type>::operator!= (std::nullptr_t) const
{
	PRECOND_DEPRECATED (item.IsValid ());

	return !item.IsEnd ();
}


template <class Cont, class Item, class Type>
inline const Cont*	ConstBidirectionalItemIteratorBase<Cont, Item, Type>::GetTarget (void) const
{
	return item.GetTarget ();
}


template <class Cont, class Item, class Type>
inline const Item&	ConstBidirectionalItemIteratorBase<Cont, Item, Type>::GetItem (void) const
{
	return item;
}


template <class Cont, class Item, class Type>
IConstBidirectionalIterator<Type>*	ConstBidirectionalItemIteratorBase<Cont, Item, Type>::CreateClone (void) const
{
	return new ConstBidirectionalItemIteratorBase (*this);
}


template <class Cont, class Item, class Type>
const Type&		ConstBidirectionalItemIteratorBase<Cont, Item, Type>::GetCurrent (void) const
{
	return operator* ();
}


template <class Cont, class Item, class Type>
void	ConstBidirectionalItemIteratorBase<Cont, Item, Type>::Increment (void)
{
	operator++ ();
}


template <class Cont, class Item, class Type>
void	ConstBidirectionalItemIteratorBase<Cont, Item, Type>::Decrement (void)
{
	operator-- ();
}


template <class Cont, class Item, class Type>
bool	ConstBidirectionalItemIteratorBase<Cont, Item, Type>::IsEqual (const IConstForwardIterator<Type>* rightOp) const
{
	NULL_PTR_CHECK (rightOp);

	const ConstBidirectionalItemIteratorBase* ro = dynamic_cast<const ConstBidirectionalItemIteratorBase*> (rightOp);
	TYPE_CHECK (ro != nullptr);

	return operator== (*ro);
}


template <class Cont, class Item, class Type>
bool	ConstBidirectionalItemIteratorBase<Cont, Item, Type>::IsEnd (void) const
{
	return operator== (nullptr);
}


template <class Cont, class Item, class Type>
inline bool		ConstBidirectionalItemIteratorBase<Cont, Item, Type>::CheckType (const ConstBidirectionalItemIteratorBase& rightOp) const
{
	return item.CheckType (rightOp.item);
}

}	// namespace GS
// ___________________ Class ConstBidirectionalItemIteratorBase ____________________


#endif
