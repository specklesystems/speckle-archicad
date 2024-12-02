#ifndef __LAZYSORTEDARRAY_HPP__
#define __LAZYSORTEDARRAY_HPP__

#include "GlobalOperators.hpp"
#include "Array.hpp"
#include "Algorithms.hpp"

namespace GSAPI {

class LazySortedArrayPrivate {
public:
	static GS::ClassInfo	classInfo;	// LazySortedArray's private classInfo
};


template <class Type>
class LazySortedArray : public GS::Object {
private:
	GS::Array<Type> array;
	bool            isSorted;

private:
	void SortIfNecessary ();

public:
		// Definitions

	typedef typename GS::Array<Type>::Iterator		Iterator;
	typedef typename GS::Array<Type>::ConstIterator	ConstIterator;

		// Constructors

	explicit LazySortedArray (USize initialCapacity = 0)		: array (initialCapacity), isSorted (true) {}
	LazySortedArray (const LazySortedArray& source)				: array (source.array), isSorted (source.isSorted) {}
	LazySortedArray (const GS::Array<Type>& source)				: array (source), isSorted (false) {}
	LazySortedArray (const GS::RandomContainer<Type>& source)	: array (source), isSorted (false) {}
	LazySortedArray (const GS::Container<Type>& source)			: array (source), isSorted (false) {}
	~LazySortedArray ()											{}

	LazySortedArray&	operator= (const LazySortedArray& source)			{ array = source.array; isSorted = source.isSorted; return (*this); }
	LazySortedArray&	operator= (const GS::Array<Type>& source)			{ array = source; isSorted = false; return (*this); }
	LazySortedArray&	operator= (const GS::RandomContainer<Type>& source)	{ array = source; isSorted = false; return (*this); }
	LazySortedArray&	operator= (const GS::Container<Type>& source)		{ array = source; isSorted = false; return (*this); }

	virtual	LazySortedArray*	Clone (void) const	 override { return new LazySortedArray (*this); }

		// Item access

	inline Type&		operator[] (UIndex idx);
	inline const Type&	operator[] (UIndex idx) const;

	inline Type&		Get (UIndex idx);
	inline const Type&	Get (UIndex idx) const;

	inline Type&		GetFirst (void);
	inline const Type&	GetFirst (void) const;

	inline Type&		GetLast (void);
	inline const Type&	GetLast (void) const;

	inline void			Set (UIndex idx, const Type& item);

		// Content management

	inline void		Fill (const Type& item, UIndex from = 0, USize range = MaxUSize);

	inline USize	Replace (const Type& oldItem, const Type& newItem, UIndex from = 0, USize range = MaxUSize);

	inline void	Insert (UIndex to, const Type& item);
	inline void	Insert (UIndex to, GS::ConstForwardIterator<Type> begin);
	inline void	Insert (UIndex to, GS::ConstForwardIterator<Type> begin, GS::ConstForwardIterator<Type> end);

	inline void		Delete		(UIndex idx);
	inline void		Delete		(UIndex from, USize range);
	inline UIndex	DeleteFirst	(const Type& item);
	inline UIndex	DeleteLast	(const Type& item);

	void	DeleteAll	(const Type& item)	{ isSorted = true; array.DeleteAll (item); }

	void	Clear (void)	{ isSorted = true; array.Clear (); }

	virtual inline void	Swap (LazySortedArray& rightOp);

	void	Push (const Type& item)	{ isSorted = false; array.Push (item); }

	inline void	Pop	 (Type* item);
	inline Type	Pop	 (void);

	inline USize	GetSize	(void) const	{ return array.GetSize (); }
	inline bool		IsEmpty (void) const	{ return array.IsEmpty (); }
	void			SetSize (USize newSize)	{ array.SetSize (newSize); }

		// Content query

	inline Iterator			Enumerate (void);
	inline ConstIterator	Enumerate (void) const;

	inline Iterator			Begin (void);
	inline ConstIterator	Begin (void) const;

	inline Iterator			End	(void);
	inline ConstIterator	End	(void) const;

	inline UIndex	FindFirst (const Type& item, UIndex from = 0, USize range = MaxUSize) const;
	inline UIndex	FindLast  (const Type& item) const;

	inline bool		Contains (const Type& item) const											{ return array.Contains (item); }
	inline USize	Count	 (const Type& item, UIndex from = 0, USize range = MaxUSize) const;

	bool	operator== (const LazySortedArray& rightOp) const			{ return (array == rightOp.array); }
	bool	operator== (const GS::Array<Type>& rightOp) const			{ return (array == rightOp); }
	bool	operator== (const GS::RandomContainer<Type>& rightOp) const	{ return (array == rightOp); }
	bool	operator!= (const LazySortedArray& rightOp) const			{ return (array != rightOp.array); }
	bool	operator!= (const GS::Array<Type>& rightOp) const			{ return (array != rightOp); }
	bool	operator!= (const GS::RandomContainer<Type>& rightOp) const	{ return (array != rightOp); }

		// Performance tuning

	virtual USize	GetCapacity	(void) const			{ return array.GetCapacity (); }
	virtual void	SetCapacity (USize newCapacity)		{ array.SetCapacity (newCapacity); }
//	virtual void	SetMinCapacity (USize minCapacity)	{ array.SetMinCapacity (minCapacity); }

		// I/O

	virtual	GSErrCode	Read  (GS::IChannel& ic) override
	{
		NULL_REF_CHECK (ic);

		array.Clear ();

		GS::InputFrame frame (ic, LazySortedArrayPrivate::classInfo);
		if (frame.GetStatus () != NoError) {
			return frame.GetStatus ();
		}

		USize newSize;
		GSErrCode errorCode = ic.Read (newSize);
		if (errorCode == NoError) {
			array.SetSize (newSize);
		}

		for (UIndex i = 0; i < newSize && errorCode == NoError; i++) {
			errorCode = ic.Read (array[i]);
		}

		bool sorted = false;
		if (errorCode == NoError) {
			errorCode = ic.Read (sorted);
		}
		isSorted = (sorted == 0);

		return errorCode;
	}

	virtual	GSErrCode	Write (GS::OChannel& oc) const override
	{
		NULL_REF_CHECK (oc);

		GS::OutputFrame frame (oc, LazySortedArrayPrivate::classInfo);

		GSErrCode errorCode = oc.Write (array.GetSize ());

		for (UIndex i = 0; i < array.GetSize () && errorCode == NoError; i++) {
			errorCode = oc.Write (array[i]);
		}

		if (errorCode == NoError) {
			bool sorted = isSorted;
			errorCode = oc.Write (sorted);
		}

		return errorCode;
	}

		// Connection with external code

	inline const Type*	GetContent (void) const	{ return array.GetContent (); }

		// Debug

	virtual void		Print	   (GS::OChannel& oc) const override
	{
		oc << "isSorted: " << isSorted << '\n';
	}

	virtual bool		CheckState (void) const			 override { return array.CheckState (); }
};

}	// namespace GSAPI

template <class Type>
inline void GSAPI::LazySortedArray<Type>::SortIfNecessary ()
{
	if (!isSorted) {
		GS::Sort (array.Begin (), array.End ());
		isSorted = true;
	}
}

template <class Type>
inline Type& GSAPI::LazySortedArray<Type>::operator[] (UIndex idx)
{
	SortIfNecessary ();
	return array[idx];
	// returns non-const reference
	isSorted = false;
}

template <class Type>
inline const Type& GSAPI::LazySortedArray<Type>::operator[] (UIndex idx) const
{
	const_cast<LazySortedArray<Type>*> (this)->SortIfNecessary ();
	return array[idx];
}

template <class Type>
inline Type& GSAPI::LazySortedArray<Type>::Get (UIndex idx)
{
	SortIfNecessary ();
	return array.Get (idx);
	// returns non-const reference
	isSorted = false;
}

template <class Type>
inline const Type& GSAPI::LazySortedArray<Type>::Get (UIndex idx) const
{
	const_cast<LazySortedArray<Type>*> (this)->SortIfNecessary ();
	return array.Get (idx);
}

template <class Type>
inline Type& GSAPI::LazySortedArray<Type>::GetFirst (void)
{
	SortIfNecessary ();
	return array.GetFirst ();
	// returns non-const reference
	isSorted = false;
}

template <class Type>
inline const Type& GSAPI::LazySortedArray<Type>::GetFirst (void) const
{
	const_cast<LazySortedArray<Type>*> (this)->SortIfNecessary ();
	return array.GetFirst ();
}

template <class Type>
inline Type& GSAPI::LazySortedArray<Type>::GetLast (void)
{
	SortIfNecessary ();
	return array.GetLast ();
	// returns non-const reference
	isSorted = false;
}

template <class Type>
inline const Type& GSAPI::LazySortedArray<Type>::GetLast (void) const
{
	const_cast<LazySortedArray<Type>*> (this)->SortIfNecessary ();
	return array.GetLast ();
}

template <class Type>
inline void GSAPI::LazySortedArray<Type>::Set (UIndex idx, const Type& item)
{
	SortIfNecessary ();
	array.Set (idx, item);
	isSorted = false;
}

template <class Type>
inline void GSAPI::LazySortedArray<Type>::Fill (const Type& item, UIndex from /*= 0*/, USize range /*= MaxUSize*/)
{
	SortIfNecessary ();
	array.Fill (item, from, range);
	if ((from != 0) || ((range != MaxUSize) && (range < GetSize ()))) {
		isSorted = false;
	}
}

template <class Type>
inline USize GSAPI::LazySortedArray<Type>::Replace (const Type& oldItem, const Type& newItem, UIndex from /*= 0*/, USize range /*= MaxUSize*/)
{
	SortIfNecessary ();
	isSorted = false;
	return array.Replace (oldItem, newItem, from, range);
}

template <class Type>
inline void	GSAPI::LazySortedArray<Type>::Insert (UIndex to, const Type& item)
{
	SortIfNecessary ();
	array.Insert (to, item);
	isSorted = false;
}

template <class Type>
inline void	GSAPI::LazySortedArray<Type>::Insert (UIndex to, GS::ConstForwardIterator<Type> begin)
{
	SortIfNecessary ();
	array.Insert (to, begin);
	isSorted = false;
}

template <class Type>
inline void	GSAPI::LazySortedArray<Type>::Insert (UIndex to, GS::ConstForwardIterator<Type> begin, GS::ConstForwardIterator<Type> end)
{
	SortIfNecessary ();
	array.Insert (to, begin, end);
	isSorted = false;
}

template <class Type>
inline void GSAPI::LazySortedArray<Type>::Delete (UIndex idx)
{
	SortIfNecessary ();
	array.Delete (idx);
	isSorted = false;
}

template <class Type>
inline void GSAPI::LazySortedArray<Type>::Delete (UIndex from, USize range)
{
	SortIfNecessary ();
	array.Delete (from, range);
	isSorted = false;
}

template <class Type>
inline UIndex GSAPI::LazySortedArray<Type>::DeleteFirst (const Type& item)
{
	SortIfNecessary ();
	isSorted = false;
	return array.DeleteFirst (item);
}

template <class Type>
inline UIndex GSAPI::LazySortedArray<Type>::DeleteLast (const Type& item)
{
	SortIfNecessary ();
	isSorted = false;
	return array.DeleteLast (item);
}

template <class Type>
inline void GSAPI::LazySortedArray<Type>::Swap (LazySortedArray& rightOp)
{
	array.Swap (rightOp.array);
	bool tempSorted = isSorted;
	isSorted = rightOp.isSorted;
	rightOp.isSorted = tempSorted;
}

template <class Type>
inline void GSAPI::LazySortedArray<Type>::Pop (Type* item)
{
	SortIfNecessary ();
	array.Pop (item);
}

template <class Type>
inline Type	GSAPI::LazySortedArray<Type>::Pop (void)
{
	SortIfNecessary ();
	return array.Pop ();
}

template <class Type>
inline typename GSAPI::LazySortedArray<Type>::Iterator GSAPI::LazySortedArray<Type>::Enumerate (void)
{
	SortIfNecessary ();
	// returns non-const iterator
	isSorted = false;
	return array.Enumerate ();
}

template <class Type>
inline typename GSAPI::LazySortedArray<Type>::ConstIterator GSAPI::LazySortedArray<Type>::Enumerate (void) const
{
	const_cast<LazySortedArray<Type>*> (this)->SortIfNecessary ();
	return array.Enumerate ();
}

template <class Type>
inline typename GSAPI::LazySortedArray<Type>::Iterator GSAPI::LazySortedArray<Type>::Begin (void)
{
	SortIfNecessary ();
	// returns non-const iterator
	isSorted = false;
	return array.Begin ();
}

template <class Type>
inline typename GSAPI::LazySortedArray<Type>::ConstIterator GSAPI::LazySortedArray<Type>::Begin (void) const
{
	const_cast<LazySortedArray<Type>*> (this)->SortIfNecessary ();
	return array.Begin ();
}

template <class Type>
inline typename GSAPI::LazySortedArray<Type>::Iterator GSAPI::LazySortedArray<Type>::End (void)
{
	SortIfNecessary ();
	// returns non-const iterator
	isSorted = false;
	return array.End ();
}

template <class Type>
inline typename GSAPI::LazySortedArray<Type>::ConstIterator GSAPI::LazySortedArray<Type>::End (void) const
{
	const_cast<LazySortedArray<Type>*> (this)->SortIfNecessary ();
	return array.End ();
}

template <class Type>
inline UIndex GSAPI::LazySortedArray<Type>::FindFirst (const Type& item, UIndex from /*= 0*/, USize range /*= MaxUSize*/) const
{
	const_cast<LazySortedArray<Type>*> (this)->SortIfNecessary ();
	return array.FindFirst (item, from, range);
}

template <class Type>
inline UIndex GSAPI::LazySortedArray<Type>::FindLast (const Type& item) const
{
	const_cast<LazySortedArray<Type>*> (this)->SortIfNecessary ();
	return array.FindLast (item);
}

template <class Type>
inline USize GSAPI::LazySortedArray<Type>::Count (const Type& item, UIndex from /*= 0*/, USize range /*= MaxUSize*/) const
{
	const_cast<LazySortedArray<Type>*> (this)->SortIfNecessary ();
	return array.Count (item, from, range);
}

#endif	// __LAZYSORTEDARRAY_HPP__
