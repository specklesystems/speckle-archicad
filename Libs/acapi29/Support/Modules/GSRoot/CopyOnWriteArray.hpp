
// *****************************************************************************
//
// Declaration and implementation of CopyOnWriteArray<T> class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_COPYONWRITEARRAY_HPP
#define GS_COPYONWRITEARRAY_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Array.hpp"
#include "CountedPtr.hpp"
#include "Guard.hpp"
#include "Lock.hpp"



// --- CopyOnWriteArray class --------------------------------------------------

namespace GS {

template<class T>
class CopyOnWriteArray : public RandomContainer<T> {

// Nested classes:
public:
	class ConstIterator : public ConstForwardIterator<T>, public IConstForwardIterator<T> {

	// Type definitions:
	private:
		typedef GS::Array<T> ArrayT;
		typedef CountedPtr<ArrayT, GS::AtomicCounter> ArrayPtrT;
		typedef typename ArrayT::ConstIterator ConstArrayIteratorT;

	// Data members:
	private:
		ConstArrayIteratorT					m_iterator;
		ArrayPtrT							m_array;

	// Construction / destruction:
	public:
		explicit ConstIterator (const ArrayPtrT& array = nullptr);
				~ConstIterator ();

	// Operator overloading:
	public:
		bool								operator == (const ConstIterator& rhs) const;
		bool								operator != (const ConstIterator& rhs) const;

		bool								operator == (std::nullptr_t) const;
		bool								operator != (std::nullptr_t) const;

		const T&							operator *  () const;
		const T*							operator -> () const;

		ConstIterator&						operator ++ ();
		ConstIterator						operator ++ (int);

	// IConstForwardIterator<T> interface implementation:
	protected:
		virtual void						Assign (const IConstForwardIterator<T>* rhs) override;
		virtual void						Assign (const IForwardIterator<T>* rhs) override;

		virtual IConstForwardIterator<T>*	CreateClone () const override;

		virtual const T&					GetCurrent () const override;
		virtual void						Increment () override;
		virtual bool						IsEqual (const IConstForwardIterator<T>* rhs) const override;
		virtual bool						IsEnd () const override;

	// Implementation:
	private:
		IConstForwardIterator<T>*			GetIteratorInterface ();

	};

// Type definitions:
private:
	typedef GS::Array<T> ArrayT;
	typedef CountedPtr<ArrayT, GS::AtomicCounter> ArrayPtrT;

// Data members:
private:
	ArrayPtrT								m_array;
	Lock									m_lock;

// Construction / destruction:
public:
	CopyOnWriteArray ();
	CopyOnWriteArray (const CopyOnWriteArray& rhs);
	CopyOnWriteArray (CopyOnWriteArray&& rhs);

// Operator overloading:
public:
	CopyOnWriteArray&						operator = (const CopyOnWriteArray& rhs);
	CopyOnWriteArray&						operator = (CopyOnWriteArray&& rhs);

// Operations:
public:
	USize									GetSize () const;
	bool									IsEmpty () const;

	ConstIterator							Enumerate () const;
	ConstIterator							Begin () const;
	ConstIterator							End () const;

	bool									Contains (const T& item) const;

	UIndex									FindFirst (const T& item, UIndex from = 0, USize range = MaxUSize) const;
	UIndex									FindLast (const T& item) const;

	bool									GetFirst (T& item) const;
	bool									GetLast (T& item) const;

	bool									Get (UIndex index, T& item) const;
	void									Set (UIndex index, const T& item);

	void									Insert (UIndex to, const T& item);

	bool									AddIfAbsent (const T& item);
	void									Add (const T& item);

	UIndex									DeleteFirst (const T& item);
	UIndex									DeleteLast (const T& item);

	void									Delete (UIndex index, USize range);
	void									Delete (UIndex index);

	void									Clear ();

// Implementation:
private:
	ArrayPtrT								GetArrayPtrCopy () const;
	ArrayPtrT								GetArrayPtrCopy ();

	ArrayPtrT								GetArrayPtr () const;
	ArrayPtrT								GetArrayPtr ();

	void									SetArrayPtr (const ArrayPtrT& arrayPtr);

	const ArrayT&							GetArray () const;
	ArrayT&									GetArray ();

	USize									GetArraySize () const;

// Static implementation:
private:
	static const ArrayT&					GetArray (const ArrayPtrT& arrayPtr);
	static ArrayT&							GetArray (ArrayPtrT& arrayPtr);

	static  USize							GetArraySize (const ArrayPtrT& arrayPtr);

};

////////////////////////////////////////////////////////////////////////////////
// CopyOnWriteArray inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

template<class T>
inline CopyOnWriteArray<T>::CopyOnWriteArray () :
	m_array (),
	m_lock ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

template<class T>
inline CopyOnWriteArray<T>::CopyOnWriteArray (const CopyOnWriteArray& rhs) :
	m_array (),
	m_lock ()
{
	ArrayPtrT arrayPtr (rhs.GetArrayPtrCopy ());
	if (arrayPtr != nullptr) {
		SetArrayPtr (new ArrayT (GetArray (arrayPtr)));
	}
}

// -----------------------------------------------------------------------------
// Move constructor
// -----------------------------------------------------------------------------

template<class T>
inline CopyOnWriteArray<T>::CopyOnWriteArray (CopyOnWriteArray&& rhs) :
	m_array (std::move (rhs.m_array)),
	m_lock ()
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

template<class T>
inline CopyOnWriteArray<T>&		CopyOnWriteArray<T>::operator = (const CopyOnWriteArray& rhs)
{
	if (this != &rhs) {

		ArrayPtrT arrayPtr (rhs.GetArrayPtrCopy ());
		synchronized (m_lock) {
			if (arrayPtr != nullptr) {
				SetArrayPtr (new ArrayT (GetArray (arrayPtr)));
			} else {
				SetArrayPtr (nullptr);
			}
		}
	}

	return *this;
}

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

template<class T>
inline CopyOnWriteArray<T>&		CopyOnWriteArray<T>::operator = (CopyOnWriteArray&& rhs)
{
	m_array = std::move (rhs.m_array);

	return *this;
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetSize
// -----------------------------------------------------------------------------

template<class T>
inline USize	CopyOnWriteArray<T>::GetSize () const
{
	ArrayPtrT arrayPtr (GetArrayPtrCopy ());
	if (arrayPtr != nullptr) {
		return arrayPtr->GetSize ();
	}

	return 0;
}

// -----------------------------------------------------------------------------
// IsEmpty
// -----------------------------------------------------------------------------

template<class T>
inline bool		CopyOnWriteArray<T>::IsEmpty () const
{
	return (GetArrayPtrCopy () == nullptr);
}

// -----------------------------------------------------------------------------
// Enumerate
// -----------------------------------------------------------------------------

template<class T>
inline typename CopyOnWriteArray<T>::ConstIterator	CopyOnWriteArray<T>::Enumerate () const
{
	return ConstIterator (GetArrayPtrCopy ());
}

// -----------------------------------------------------------------------------
// Begin
// -----------------------------------------------------------------------------

template<class T>
inline typename CopyOnWriteArray<T>::ConstIterator	CopyOnWriteArray<T>::Begin () const
{
	return ConstIterator (GetArrayPtrCopy ());
}

// -----------------------------------------------------------------------------
// End
// -----------------------------------------------------------------------------

template<class T>
inline typename CopyOnWriteArray<T>::ConstIterator	CopyOnWriteArray<T>::End () const
{
	return ConstIterator (nullptr);
}

// -----------------------------------------------------------------------------
// Contains
// -----------------------------------------------------------------------------

template<class T>
inline bool		CopyOnWriteArray<T>::Contains (const T& item) const
{
	ArrayPtrT arrayPtr (GetArrayPtrCopy ());
	if (arrayPtr != nullptr) {
		return arrayPtr->Contains (item);
	}

	return false;
}

// -----------------------------------------------------------------------------
// FindFirst
// -----------------------------------------------------------------------------

template<class T>
inline UIndex	CopyOnWriteArray<T>::FindFirst (const T& item, UIndex from, USize range) const
{
	ArrayPtrT arrayPtr (GetArrayPtrCopy ());
	
	USize size = GetArraySize (arrayPtr);
	if (DBERROR (from >= size)) {
		throw GS::IllegalReferenceException ("Invalid index: index must be less than array size.", __FILE__, __LINE__);
	}
	if (DBERROR (range != MaxUIndex && from + range > size)) {
		throw GS::IllegalReferenceException ("Invalid range: range must be less than or equal to array size.", __FILE__, __LINE__);
	}
	
	return arrayPtr->FindFirst (item, from, range);
}

// -----------------------------------------------------------------------------
// FindLast
// -----------------------------------------------------------------------------

template<class T>
inline UIndex	CopyOnWriteArray<T>::FindLast (const T& item) const
{
	ArrayPtrT arrayPtr (GetArrayPtrCopy ());
	if (arrayPtr != nullptr) {
		return arrayPtr->FindLast (item);
	}
		
	return MaxUIndex;
}

// -----------------------------------------------------------------------------
// GetFirst
// -----------------------------------------------------------------------------

template<class T>
inline bool		CopyOnWriteArray<T>::GetFirst (T& item) const
{
	ArrayPtrT arrayPtr (GetArrayPtrCopy ());
	if (arrayPtr != nullptr && arrayPtr->GetSize () > 0) {
		item = arrayPtr->GetFirst ();
		return true;
	}

	return false;
}

// -----------------------------------------------------------------------------
// GetLast
// -----------------------------------------------------------------------------

template<class T>
inline bool		CopyOnWriteArray<T>::GetLast (T& item) const
{
	ArrayPtrT arrayPtr (GetArrayPtrCopy ());
	if (arrayPtr != nullptr && arrayPtr->GetSize () > 0) {
		item = arrayPtr->GetLast ();
		return true;
	}

	return false;
}

// -----------------------------------------------------------------------------
// Get
// -----------------------------------------------------------------------------

template<class T>
inline bool		CopyOnWriteArray<T>::Get (UIndex index, T& item) const
{
	ArrayPtrT arrayPtr (GetArrayPtrCopy ());
	if (arrayPtr != nullptr && index < arrayPtr->GetSize ()) {
		item = arrayPtr->Get (index);
		return true;
	}
	
	return false;
}

// -----------------------------------------------------------------------------
// Set
// -----------------------------------------------------------------------------

template<class T>
inline void		CopyOnWriteArray<T>::Set (UIndex index, const T& item)
{
	synchronized (m_lock) {
		if (DBERROR (index >= GetArraySize ())) {
			throw GS::IllegalReferenceException ("Invalid index: index must be less than array size.", __FILE__, __LINE__);
		}

		ArrayPtrT arrayPtr (new ArrayT (GetArray ()));
		arrayPtr->Set (index, item);
		SetArrayPtr (arrayPtr);
	}
}

// -----------------------------------------------------------------------------
// Insert
// -----------------------------------------------------------------------------

template<class T>
inline void		CopyOnWriteArray<T>::Insert (UIndex to, const T& item)
{
	synchronized (m_lock) {
		USize size = GetArraySize ();
		if (DBERROR (to > size)) {
			throw GS::IllegalReferenceException ("Invalid index: index must be less than or equal to array size.", __FILE__, __LINE__);
		}

		ArrayPtrT arrayPtr (new ArrayT (size + 1));
		if (m_array != nullptr) {
			const ArrayT& source = GetArray (m_array);
			ArrayT& target = GetArray (arrayPtr);
			if (to > 0) {
				for (UIndex i = 0; i < to; i ++) {
					target.Push (source [i]);
				}
			}
			
			target.Push (item);

			if (to < size) {
				for (UIndex i = to; i < size; i ++) {
					target.Push (source [i]);
				}
			}
		} else {
			arrayPtr->Push (item);
		}

		SetArrayPtr (arrayPtr);
	}
}

// -----------------------------------------------------------------------------
// AddIfAbsent
// -----------------------------------------------------------------------------

template<class T>
inline bool		CopyOnWriteArray<T>::AddIfAbsent (const T& item)
{
	synchronized (m_lock) {
		USize size = GetArraySize ();
		if (size == 0 || m_array->Contains (item) == false) {
			ArrayPtrT arrayPtr (new ArrayT (size + 1));
			if (m_array != nullptr) {
				ArrayT& target = GetArray (arrayPtr);
				for (typename ArrayT::ConstIterator i = m_array->Enumerate (); i != nullptr; ++ i) {
					target.Push (*i);
				}
			}

			arrayPtr->Push (item);

			SetArrayPtr (arrayPtr);

			return true;
		}
	}

	return false;
}

// -----------------------------------------------------------------------------
// Add
// -----------------------------------------------------------------------------

template<class T>
inline void		CopyOnWriteArray<T>::Add (const T& item)
{
	synchronized (m_lock) {
		USize size = GetArraySize ();
		
		ArrayPtrT arrayPtr (new ArrayT (size + 1));
		if (m_array != nullptr) {
			ArrayT& target = GetArray (arrayPtr);
			for (typename ArrayT::ConstIterator i = m_array->Enumerate (); i != nullptr; ++ i) {
				target.Push (*i);
			}
		}

		arrayPtr->Push (item);

		SetArrayPtr (arrayPtr);
	}
}

// -----------------------------------------------------------------------------
// DeleteFirst
// -----------------------------------------------------------------------------

template<class T>
inline UIndex	CopyOnWriteArray<T>::DeleteFirst (const T& item)
{
	synchronized (m_lock) {
		if (m_array != nullptr) {
			UIndex index = m_array->FindFirst (item);
			if (index != MaxUIndex) {
				if (GetArraySize () > 1) {
					ArrayPtrT arrayPtr (new ArrayT (GetArray ()));
					arrayPtr->DeleteFirst (item);
					SetArrayPtr (arrayPtr);
				} else {
					SetArrayPtr (nullptr);
				}
			}

			return index;
		}
	}

	return MaxUIndex;
}

// -----------------------------------------------------------------------------
// DeleteLast
// -----------------------------------------------------------------------------

template<class T>
inline UIndex	CopyOnWriteArray<T>::DeleteLast (const T& item)
{
	synchronized (m_lock) {
		if (m_array != nullptr) {
			UIndex index = m_array->FindLast (item);
			if (index != MaxUIndex) {
				if (GetArraySize () > 1) {
					ArrayPtrT arrayPtr (new ArrayT (GetArray ()));
					arrayPtr->DeleteLast (item);
					SetArrayPtr (arrayPtr);
				} else {
					SetArrayPtr (nullptr);
				}
			}

			return index;
		}
	}

	return MaxUIndex;
}

// -----------------------------------------------------------------------------
// Delete
// -----------------------------------------------------------------------------

template<class T>
inline void		CopyOnWriteArray<T>::Delete (UIndex index, USize range)
{
	synchronized (m_lock) {
		USize size = GetArraySize ();
		if (DBERROR (index >= size)) {
			throw GS::IllegalReferenceException ("Invalid index: index must be less than array size.", __FILE__, __LINE__);
		}
		if (DBERROR (index + range > size)) {
			throw GS::IllegalReferenceException ("Invalid range: range must be less than or equal to array size.", __FILE__, __LINE__);
		}

		ArrayPtrT arrayPtr (new ArrayT (GetArray ()));
		arrayPtr->Delete (index, range);
		SetArrayPtr (arrayPtr);
	}
}

// -----------------------------------------------------------------------------
// Delete
// -----------------------------------------------------------------------------

template<class T>
inline void		CopyOnWriteArray<T>::Delete (UIndex index)
{
	synchronized (m_lock) {
		USize size = GetArraySize ();
		if (DBERROR (index >= size)) {
			throw GS::IllegalReferenceException ("Invalid index: index must be less than array size.", __FILE__, __LINE__);
		}

		if (size > 1) {
			ArrayPtrT arrayPtr (new ArrayT (size - 1));

			const ArrayT& source = GetArray (m_array);
			ArrayT& target = GetArray (arrayPtr);
			if (index > 1) {
				for (UIndex i = 0; i < index; i ++) {
					target.Push (source [i]);
				}		
			}
			if (index < size - 1) {
				for (UIndex i = index + 1; i < size; i ++) {
					target.Push (source [i]);
				}
			}

			SetArrayPtr (arrayPtr);
		} else {
			SetArrayPtr (nullptr);
		}
	}
}

// -----------------------------------------------------------------------------
// Clear
// -----------------------------------------------------------------------------

template<class T>
inline void		CopyOnWriteArray<T>::Clear ()
{
	synchronized (m_lock) {
		SetArrayPtr (nullptr);
	}
}

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetArrayPtrCopy
// -----------------------------------------------------------------------------

template<class T>
inline typename CopyOnWriteArray<T>::ArrayPtrT	CopyOnWriteArray<T>::GetArrayPtrCopy () const
{
	// NOTE: mutual exclusion required during copy operation because the assignment 
	// operator of CountedPtr<T> class is not an atomic.

	ArrayPtrT arrayPtr;
	synchronized (const_cast<GS::Lock&> (m_lock)) {
		arrayPtr = GetArrayPtr ();
	}

	return arrayPtr;
}

// -----------------------------------------------------------------------------
// GetArrayPtrCopy
// -----------------------------------------------------------------------------

template<class T>
inline typename CopyOnWriteArray<T>::ArrayPtrT	CopyOnWriteArray<T>::GetArrayPtrCopy ()
{
	// NOTE: mutual exclusion required during copy operation because the assignment 
	// operator of CountedPtr<T> class is not an atomic.

	ArrayPtrT arrayPtr;
	synchronized (m_lock) {
		arrayPtr = GetArrayPtr ();
	}

	return arrayPtr;
}

// -----------------------------------------------------------------------------
// GetArrayPtr
// -----------------------------------------------------------------------------

template<class T>
inline typename CopyOnWriteArray<T>::ArrayPtrT	CopyOnWriteArray<T>::GetArrayPtr () const
{
	return m_array;
}

// -----------------------------------------------------------------------------
// GetArrayPtr
// -----------------------------------------------------------------------------

template<class T>
inline typename CopyOnWriteArray<T>::ArrayPtrT	CopyOnWriteArray<T>::GetArrayPtr ()
{
	return m_array;
}

// -----------------------------------------------------------------------------
// SetArrayPtr
// -----------------------------------------------------------------------------

template<class T>
inline void		CopyOnWriteArray<T>::SetArrayPtr (const ArrayPtrT& arrayPtr)
{
	m_array = arrayPtr;
}

// -----------------------------------------------------------------------------
// GetArray
// -----------------------------------------------------------------------------

template<class T>
inline const typename CopyOnWriteArray<T>::ArrayT&	CopyOnWriteArray<T>::GetArray () const
{
	return (*m_array);
}
	
// -----------------------------------------------------------------------------
// GetArray
// -----------------------------------------------------------------------------

template<class T>
inline typename CopyOnWriteArray<T>::ArrayT&	CopyOnWriteArray<T>::GetArray ()
{
	return (*m_array);
}

// -----------------------------------------------------------------------------
// GetArraySize
// -----------------------------------------------------------------------------

template<class T>
inline USize	CopyOnWriteArray<T>::GetArraySize () const
{
	return GetArraySize (m_array);
}

////////////////////////////////////////////////////////////////////////////////
// Static implementation
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetArray
// -----------------------------------------------------------------------------

template<class T>
inline const typename CopyOnWriteArray<T>::ArrayT&	CopyOnWriteArray<T>::GetArray (const ArrayPtrT& arrayPtr)
{
	return (*arrayPtr);
}

// -----------------------------------------------------------------------------
// GetArray
// -----------------------------------------------------------------------------

template<class T>
inline typename CopyOnWriteArray<T>::ArrayT&	CopyOnWriteArray<T>::GetArray (ArrayPtrT& arrayPtr)
{
	return (*arrayPtr);
}

// -----------------------------------------------------------------------------
// GetArraySize
// -----------------------------------------------------------------------------

template<class T>
inline USize	CopyOnWriteArray<T>::GetArraySize (const ArrayPtrT& arrayPtr)
{
	return (arrayPtr != nullptr ? arrayPtr->GetSize () : 0);
}



////////////////////////////////////////////////////////////////////////////////
// CopyOnWriteArray::ConstIterator inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<class T>
inline CopyOnWriteArray<T>::ConstIterator::ConstIterator (const ArrayPtrT& array) :
	ConstForwardIterator<T> (GetIteratorInterface ()),
	m_iterator (),
	m_array (array)
{
	if (array != nullptr) {
		m_iterator = array->Enumerate ();
	}
}

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------

template<class T>
inline CopyOnWriteArray<T>::ConstIterator::~ConstIterator ()
{
	this->target = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

template<class T>
inline bool		CopyOnWriteArray<T>::ConstIterator::operator == (const ConstIterator& rhs) const
{
	if (m_array != nullptr) {
		if (rhs.m_array != nullptr) {
			return (m_array == rhs.m_array && m_iterator == rhs.m_iterator);
		} else {
			return (m_iterator == nullptr);
		}
	} else {
		if (rhs.m_array != nullptr) {
			return (rhs.m_iterator == nullptr);
		} else {
			return (m_array == rhs.m_array);
		}
	}
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

template<class T>
inline bool		CopyOnWriteArray<T>::ConstIterator::operator != (const ConstIterator& rhs) const
{
	return !operator == (rhs);
}

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

template<class T>
inline bool		CopyOnWriteArray<T>::ConstIterator::operator == (std::nullptr_t) const
{
	return (m_array == nullptr || m_iterator == nullptr);
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

template<class T>
inline bool		CopyOnWriteArray<T>::ConstIterator::operator != (std::nullptr_t) const
{
	return !operator == (nullptr);
}

// -----------------------------------------------------------------------------
// operator *
// -----------------------------------------------------------------------------

template<class T>
inline const T&		CopyOnWriteArray<T>::ConstIterator::operator * () const
{
	return (*m_iterator);
}

// -----------------------------------------------------------------------------
// operator ->
// -----------------------------------------------------------------------------

template<class T>
inline const T*		CopyOnWriteArray<T>::ConstIterator::operator -> () const
{
	return m_iterator;
}

// -----------------------------------------------------------------------------
// operator ++
// -----------------------------------------------------------------------------

template<class T>
inline typename CopyOnWriteArray<T>::ConstIterator&		CopyOnWriteArray<T>::ConstIterator::operator ++ ()
{
	if (m_array != nullptr) {
		++m_iterator;
	}

	return *this;
}

// -----------------------------------------------------------------------------
// operator ++
// -----------------------------------------------------------------------------

template<class T>
inline typename CopyOnWriteArray<T>::ConstIterator		CopyOnWriteArray<T>::ConstIterator::operator ++ (int)
{
	ConstIterator result (*this);

	if (m_array != nullptr) {
		++m_iterator;
	}

	return result;
}

////////////////////////////////////////////////////////////////////////////////
// IConstForwardIterator<T> interface implementation
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Assign
// -----------------------------------------------------------------------------

template<class T>
void	CopyOnWriteArray<T>::ConstIterator::Assign (const IConstForwardIterator<T>* /*rhs*/)
{
	// ConstIterator contains own realization of the IConstForwardIterator interface 
	// working on members in this class which are copied from the source iterator.
}

// -----------------------------------------------------------------------------
// Assign
// -----------------------------------------------------------------------------

template<class T>
void	CopyOnWriteArray<T>::ConstIterator::Assign (const IForwardIterator<T>* /*rhs*/)
{
	// ConstIterator contains own realization of the IConstForwardIterator interface 
	// working on members in this class which are copied from the source iterator.
}

// -----------------------------------------------------------------------------
// CreateClone
// -----------------------------------------------------------------------------

template<class T>
IConstForwardIterator<T>*	CopyOnWriteArray<T>::ConstIterator::CreateClone () const
{
	return new ConstIterator (*this);
}

// -----------------------------------------------------------------------------
// GetCurrent
// -----------------------------------------------------------------------------

template<class T>
const T&	CopyOnWriteArray<T>::ConstIterator::GetCurrent () const
{
	return operator * ();
}

// -----------------------------------------------------------------------------
// Increment
// -----------------------------------------------------------------------------

template<class T>
void	CopyOnWriteArray<T>::ConstIterator::Increment ()
{
	operator ++ ();
}

// -----------------------------------------------------------------------------
// IsEqual
// -----------------------------------------------------------------------------

template<class T>
bool	CopyOnWriteArray<T>::ConstIterator::IsEqual (const IConstForwardIterator<T>* rhs) const
{
	NULL_PTR_CHECK (rhs);

	const ConstIterator* i = dynamic_cast<const ConstIterator*> (rhs);
	
	TYPE_CHECK (i != nullptr);

	return operator == (*i);
}

// -----------------------------------------------------------------------------
// IsEnd
// -----------------------------------------------------------------------------

template<class T>
bool	CopyOnWriteArray<T>::ConstIterator::IsEnd () const
{
	return operator == (nullptr);
}

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////
	
// -----------------------------------------------------------------------------
// GetIteratorInterface
// -----------------------------------------------------------------------------

template<class T>
inline IConstForwardIterator<T>*	CopyOnWriteArray<T>::ConstIterator::GetIteratorInterface ()
{
	return this;
}

}



// --- CopyOnWriteArray related global functions -------------------------------

namespace GS {

// -----------------------------------------------------------------------------
// begin
// -----------------------------------------------------------------------------

template<class T>
inline auto		begin (const CopyOnWriteArray<T>& copyOnWriteArray)
{
	return copyOnWriteArray.Begin ();
}

// -----------------------------------------------------------------------------
// end
// -----------------------------------------------------------------------------

template<class T>
inline auto		end (const CopyOnWriteArray<T>& copyOnWriteArray)
{
	return copyOnWriteArray.End ();
}

}

#endif // GS_COPYONWRITEARRAY_HPP