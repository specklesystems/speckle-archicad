
// ****************************************************************************
//
// Declaration of Queue generic class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// ****************************************************************************

#ifndef GS_QUEUE_HPP
#define GS_QUEUE_HPP

#pragma once


// --- Includes ---------------------------------------------------------------

#include "BaseAlgorithms.hpp"
#include "ForwardContainerIterator.hpp"
#include "PagedArray.hpp"
#include "Inserter.hpp"


// --- Queue class ------------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT QueuePrivate {
public:
	static GS::ClassInfo	classInfo;
};

template<typename T>
class Queue: public Container<T> {

// Static constants:
private:
	static const UIndex		null	= 0xFFFFFFFF;
	static const UIndex		free	= 0xFFFFFFFE;

// Type definitions:
private:
	class IteratorState {

	// Data members:
	public:
		UIndex		m_current;

	// Construction / destruction:
	public:
		explicit IteratorState (UIndex current) noexcept : m_current (current) {};

	};

private:
	class Node {

	// Data members:
	private:
		alignas (T) char	m_item [sizeof (T)];
		UIndex				m_next;

	// Construction / destruction:
	public:
		Node () noexcept;
		Node (const T& item);
		~Node ();

	// Operator overloading:
	public:
		bool				operator == (const T& item) const;
		bool				operator != (const T& item) const;

	// Operations:
	public:
		const T&			Get () const noexcept;
		T&					Get () noexcept;
		void				Set (const T& item);
		void				Set (T&& item);

		UIndex				GetNext () const noexcept;
		void				SetNext (UIndex next) noexcept;

		bool				IsFree () const noexcept;
		void				Free () noexcept;

		GSErrCode			Read (IChannel& ic);
		GSErrCode			Write (OChannel& oc) const;
	};

public:
	typedef ConstGeneralForwardContainerIterator<Queue, IteratorState, T> 	ConstIterator;

// Friend classes:
friend class Node;
friend class ConstGeneralForwardContainerIterator<Queue, IteratorState, T>;
friend class GeneralForwardContainerIterator<Queue, IteratorState, T>;

// Data members:
private:
	PagedArray<Node>	m_nodes;
	PagedArray<UIndex>	m_free;

	USize				m_size;

	UIndex				m_head;
	UIndex				m_tail;

// Construction / destruction:
public:
	Queue ();
	Queue (std::initializer_list<T> source);
	Queue (const Queue& rhs);

	template<typename T2>
	explicit Queue (const Queue<T2> &rhs);

// Operator overloading:
public:
	bool				operator == (const Queue& rhs) const;
	bool				operator != (const Queue& rhs) const;
	Queue&				operator = (const Queue& rhs);

// Operations:
public:
	USize				GetSize	() const noexcept;
	bool				IsEmpty () const noexcept;

	bool				Contains (const T& item) const;
	bool				Contains (std::initializer_list<T> items) const;

	ConstIterator		Enumerate () const;
	ConstIterator		Begin () const;
	ConstIterator		End	() const;

	const T&			Peek () const gs_lifebound;
	T&					Peek () gs_lifebound;
	bool				Peek (T* item) const;

	T					Pop ();
	void				Pop (T* item);

	void				Push (const T& item);
	void				Push (T&& item);

	void				Delete (const T& item);

	void				Swap (Queue& rhs);

	void				Clear ();

// Object overrides:
public:
	GSErrCode	Read  (IChannel& ic);
	GSErrCode	Write (OChannel& oc) const;

	bool		CheckState () const;

// Implementation:
private:
	const Node&			GetNode (UIndex node) const;
	Node&				GetNode (UIndex node);

	UIndex				GetNext (UIndex node) const;

	UIndex				AllocateNode ();
	void				FreeNode (UIndex node);

	const T&			GetCurrent (const IteratorState& state) const;
	T&					GetCurrent (const IteratorState& state);
	void				Increment  (IteratorState& state) const;
	bool				IsEqual    (const IteratorState& state1, const IteratorState& state2) const;
	bool				IsEnd      (const IteratorState& state) const;
};

///////////////////////////////////////////////////////////////////////////////
// Queue inlines

///////////////////////////////////////////////////////////////////////////////
// Construction / destruction
///////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
// Default constructor
// ----------------------------------------------------------------------------

template<typename T>
inline Queue<T>::Queue () :
	m_nodes (),
	m_free (),
	m_size (0),
	m_head (null),
	m_tail (null)
{
	// Empty constructor body
}

// ----------------------------------------------------------------------------
// Copy constructor
// ----------------------------------------------------------------------------

template<typename T>
inline Queue<T>::Queue (const Queue& rhs) : Queue ()
{
	for (auto i = rhs.Enumerate (); i != nullptr; ++ i) {
		Push (*i);
	}
}


template<typename T>
Queue<T>::Queue (std::initializer_list<T> source) : Queue ()
{
	for (const auto& item : source)
		Push (item);
}


template<typename T>
template<typename T2>
inline Queue<T>::Queue (const Queue<T2>& rhs) : Queue ()
{
	static_assert (IsConvertible<T, T2>, "'T' is not convertible to 'T2'.");

	for (const auto& item : rhs)
		Push (item);
}

///////////////////////////////////////////////////////////////////////////////
// Operator overloading
///////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
// operator ==
// ----------------------------------------------------------------------------

template<typename T>
inline bool		Queue<T>::operator == (const Queue<T>& rhs) const
{
	NULL_REF_CHECK (rhs);

	if (m_size == rhs.m_size) {
		return (GS::IsEqual (Begin (), End (), rhs.Begin ()));
	}

	return false;
}

// ----------------------------------------------------------------------------
// operator !=
// ----------------------------------------------------------------------------

template<typename T>
inline bool		Queue<T>::operator != (const Queue<T>& rhs) const
{
	return !operator == (rhs);
}

// ----------------------------------------------------------------------------
// operator =
// ----------------------------------------------------------------------------

template<typename T>
inline Queue<T>&	Queue<T>::operator = (const Queue<T>& rhs)
{
	if (this != &rhs) {
		Queue (rhs).Swap (*this);
	}

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
// Operations
///////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
// GetSize
// ----------------------------------------------------------------------------

template<typename T>
inline USize	Queue<T>::GetSize () const noexcept
{
	return m_size;
}

// ----------------------------------------------------------------------------
// IsEmpty
// ----------------------------------------------------------------------------

template<typename T>
inline bool		Queue<T>::IsEmpty () const noexcept
{
	return (m_size == 0);
}

// ----------------------------------------------------------------------------
// Contains
// ----------------------------------------------------------------------------

template<typename T>
inline bool		Queue<T>::Contains (const T& item) const
{
	NULL_REF_CHECK (item);

	return (GS::Find (Begin (), End (), item) != nullptr);
}


template <typename T>
bool	Queue<T>::Contains (std::initializer_list<T> items) const
{
	for (const auto& item : items) {
		if (!Contains (item))
			return false;
	}

	return true;
}

// ----------------------------------------------------------------------------
// Enumerate
// ----------------------------------------------------------------------------

template<typename T>
inline typename Queue<T>::ConstIterator		Queue<T>::Enumerate () const
{
	return ConstIterator (*this, IteratorState (m_head));
}

// ----------------------------------------------------------------------------
// Begin
// ----------------------------------------------------------------------------

template<typename T>
inline typename Queue<T>::ConstIterator		Queue<T>::Begin () const
{
	return ConstIterator (*this, IteratorState (m_head));
}

// ----------------------------------------------------------------------------
// End
// ----------------------------------------------------------------------------

template<typename T>
inline typename Queue<T>::ConstIterator		Queue<T>::End () const
{
	return ConstIterator (*this, IteratorState (null));
}

// ----------------------------------------------------------------------------
// Peek
// ----------------------------------------------------------------------------

template<typename T>
inline const T&		Queue<T>::Peek () const
{
	REF_CHECK_R (m_size > 0);

	return GetNode (m_head).Get ();
}

// ----------------------------------------------------------------------------
// Peek
// ----------------------------------------------------------------------------

template<typename T>
inline T&		Queue<T>::Peek ()
{
	REF_CHECK_R (m_size > 0);

	return GetNode (m_head).Get ();
}

// ----------------------------------------------------------------------------
// Peek
// ----------------------------------------------------------------------------

template<typename T>
inline bool		Queue<T>::Peek (T* item) const
{
	NULL_PTR_CHECK (item);

	if (m_size == 0) {
		return false;
	}

	*item = GetNode (m_head).Get ();

	return true;
}

// ----------------------------------------------------------------------------
// Pop
// ----------------------------------------------------------------------------

template<typename T>
inline T	Queue<T>::Pop ()
{
	REF_CHECK_R (m_size > 0);

	T	first = std::move (GetNode (m_head).Get ());

	UIndex head = m_head;
	if (m_head == m_tail) {
		m_head = null;
		m_tail = null;
	} else {
		m_head = GetNode (m_head).GetNext ();
	}

	FreeNode (head);

	m_size --;

	return first;
}

// ----------------------------------------------------------------------------
// Pop
// ----------------------------------------------------------------------------

template<typename T>
inline void		Queue<T>::Pop (T* item)
{
	NULL_PTR_CHECK (item);
	REF_CHECK_R (m_size > 0);

	*item = std::move (GetNode (m_head).Get ());

	UIndex head = m_head;
	if (m_head == m_tail) {
		m_head = null;
		m_tail = null;
	} else {
		m_head = GetNode (m_head).GetNext ();
	}

	FreeNode (head);

	m_size --;
}

// ----------------------------------------------------------------------------
// Push
// ----------------------------------------------------------------------------

template<typename T>
inline void		Queue<T>::Push (const T& item)
{
	NULL_REF_CHECK (item);

	UIndex node = AllocateNode ();

	try {
		GetNode (node).Set (item);
	}
	catch (Exception&) {
		FreeNode (node);
		throw;
	}
	catch (...) {
		DBBREAK ();
	}

	if (m_tail == null) {
		m_head = node;
	} else {
		GetNode (m_tail).SetNext (node);
	}
	m_tail = node;

	m_size ++;
}

// ----------------------------------------------------------------------------
// Push
// ----------------------------------------------------------------------------

template<typename T>
inline void		Queue<T>::Push (T&& item)
{
	NULL_REF_CHECK (item);

	UIndex node = AllocateNode ();

	try {
		GetNode (node).Set (std::move (item));
	}
	catch (Exception&) {
		FreeNode (node);
		throw;
	}
	catch (...) {
		DBBREAK ();
	}

	if (m_tail == null) {
		m_head = node;
	} else {
		GetNode (m_tail).SetNext (node);
	}
	m_tail = node;

	m_size ++;
}

// ----------------------------------------------------------------------------
// Delete
// ----------------------------------------------------------------------------

template<typename T>
inline void		Queue<T>::Delete (const T& item)
{
	NULL_REF_CHECK (item);

	UIndex node = m_head;
	UIndex prev = null;

	while (node != null) {
		if (GetNode (node) == item) {
			if (node == m_head) {
				m_head = GetNext (node);
			}
			if (node == m_tail) {
				m_tail = prev;
			}
			if (prev != null) {
				GetNode (prev).SetNext (GetNext (node));
			}
			FreeNode (node);
			m_size --;
			break;
		}

		prev = node;
		node = GetNext (node);
	}
}

// ----------------------------------------------------------------------------
// Swap
// ----------------------------------------------------------------------------

template<typename T>
inline void		Queue<T>::Swap (Queue& rhs)
{
	m_nodes.Swap (rhs.m_nodes);
	m_free.Swap (rhs.m_free);

	GS::Swap (m_size, rhs.m_size);
	GS::Swap (m_head, rhs.m_head);
	GS::Swap (m_tail, rhs.m_tail);
}

// ----------------------------------------------------------------------------
// Clear
// ----------------------------------------------------------------------------

template<typename T>
inline void		Queue<T>::Clear ()
{
	try {
		m_nodes.Clear ();
	}
	catch (Exception&) {
		// Empty handler
	}

	m_free.Clear ();
	m_size = 0;
	m_head = null;
	m_tail = null;
}

// ----------------------------------------------------------------------------
// Read
// ----------------------------------------------------------------------------

template<typename T>
GSErrCode	Queue<T>::Read (IChannel& ic)
{
	NULL_REF_CHECK (ic);

	Clear ();

	GS::InputFrame frame (ic, QueuePrivate::classInfo);
	if (frame.GetStatus () != NoError)
		return frame.GetStatus ();

	GSErrCode error = ic.Read (m_size);
	if (error == NoError) {
		m_nodes.SetSize (m_size);
	}

	for (UIndex i = 0; i < m_size && error == NoError; i ++) {
		error = ic.Read (m_nodes [i]);
	}
	for (UIndex i = 1; i < m_size; i ++) {
		m_nodes [i - 1].SetNext (i);
	}

	if (m_size > 0) {
		m_nodes.GetLast ().SetNext (null);
	}

	m_head = 0;
	m_tail = (m_size == 0) ? null : (m_size - 1);

	return error;
}

// ----------------------------------------------------------------------------
// Write
// ----------------------------------------------------------------------------

template<typename T>
GSErrCode	Queue<T>::Write (OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	GS::OutputFrame frame (oc, QueuePrivate::classInfo);

	GSErrCode error = oc.Write (m_size);

	UIndex node = m_head;
	for (UIndex i = 0; i < m_size && error == NoError; i ++) {
		error = oc.Write (GetNode (node));
		node = GetNext (node);
	}

	return error;
}

// ----------------------------------------------------------------------------
// CheckState
// ----------------------------------------------------------------------------

template<typename T>
bool	Queue<T>::CheckState () const
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
// GetCurrent
// ----------------------------------------------------------------------------

template<typename T>
inline const T&		Queue<T>::GetCurrent (const IteratorState& state) const
{
	return GetNode (state.m_current).Get ();
}

// ----------------------------------------------------------------------------
// GetCurrent
// ----------------------------------------------------------------------------

template<typename T>
inline T&	Queue<T>::GetCurrent (const IteratorState& state)
{
	return GetNode (state.m_current).Get ();
}

// ----------------------------------------------------------------------------
// Increment
// ----------------------------------------------------------------------------

template<typename T>
inline void		Queue<T>::Increment (IteratorState& state) const
{
	state.m_current = GetNext (state.m_current);
}

// ----------------------------------------------------------------------------
// IsEqual
// ----------------------------------------------------------------------------

template<typename T>
inline bool		Queue<T>::IsEqual (const IteratorState& state1, const IteratorState& state2) const
{
	return (state1.m_current == state2.m_current);
}

// ----------------------------------------------------------------------------
// IsEnd
// ----------------------------------------------------------------------------

template<typename T>
inline bool		Queue<T>::IsEnd (const IteratorState& state) const
{
	return (state.m_current == null);
}

// ----------------------------------------------------------------------------
// GetNode
// ----------------------------------------------------------------------------

template<typename T>
inline const typename Queue<T>::Node&	Queue<T>::GetNode (UIndex node) const
{
	DBASSERT (node != null);
	DBASSERT (node < m_nodes.GetSize ());

	return m_nodes [node];
}

// ----------------------------------------------------------------------------
// GetNode
// ----------------------------------------------------------------------------

template<typename T>
inline typename Queue<T>::Node&		Queue<T>::GetNode (UIndex node)
{
	DBASSERT (node != null);
	DBASSERT (node < m_nodes.GetSize ());

	return m_nodes [node];
}

// ----------------------------------------------------------------------------
// GetNext
// ----------------------------------------------------------------------------

template<typename T>
inline UIndex	Queue<T>::GetNext (UIndex node) const
{
	if (node != null) {
		return GetNode (node).GetNext ();
	}

	return null;
}


// ----------------------------------------------------------------------------
// AllocateNode
// ----------------------------------------------------------------------------

template<typename T>
inline UIndex	Queue<T>::AllocateNode ()
{
	UIndex node = null;
	if (m_free.GetSize () > 0) {
		node = m_free.GetLast ();
		m_free.Delete (m_free.GetSize () - 1);
	} else {
		node = m_nodes.GetSize ();
		m_nodes.Push (Node ());
	}

	return node;
}

// ----------------------------------------------------------------------------
// FreeNode
// ----------------------------------------------------------------------------

template<typename T>
inline void		Queue<T>::FreeNode (UIndex node)
{
	DBASSERT (node != null);
	DBASSERT (node < m_nodes.GetSize ());

	m_nodes [node].Free ();
	m_free.Push (node);
}



///////////////////////////////////////////////////////////////////////////////
// Queue::Node inlines

///////////////////////////////////////////////////////////////////////////////
// Construction / destruction
///////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------

template<typename T>
inline Queue<T>::Node::Node () noexcept :
	m_next (free)
{
	// Empty constructor body
}

// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------

template<typename T>
inline Queue<T>::Node::Node (const T& item) :
	m_next (null)
{
	::new (m_item) T (item);
}

// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------

template<typename T>
inline Queue<T>::Node::~Node ()
{
	Free ();
}

///////////////////////////////////////////////////////////////////////////////
// Operator overloading
///////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
// operator ==
// ----------------------------------------------------------------------------

template<typename T>
inline bool		Queue<T>::Node::operator == (const T& item) const
{
	return (*reinterpret_cast<const T*> (m_item) == item);
}

// ----------------------------------------------------------------------------
// operator !=
// ----------------------------------------------------------------------------

template<typename T>
inline bool		Queue<T>::Node::operator != (const T& item) const
{
	return (*reinterpret_cast<const T*> (m_item) != item);
}

///////////////////////////////////////////////////////////////////////////////
// Operations
///////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
// Get
// ----------------------------------------------------------------------------

template<typename T>
inline const T&		Queue<T>::Node::Get () const noexcept
{
	return *reinterpret_cast<const T*> (m_item);
}

// ----------------------------------------------------------------------------
// Get
// ----------------------------------------------------------------------------

template<typename T>
inline T&	Queue<T>::Node::Get () noexcept
{
	return *reinterpret_cast<T*> (m_item);
}

// ----------------------------------------------------------------------------
// Set
// ----------------------------------------------------------------------------

template<typename T>
inline void		Queue<T>::Node::Set (const T& item)
{
	if (m_next == free) {
		::new (m_item) T (item);
		m_next = null;
	} else {
		*reinterpret_cast<T*> (m_item) = item;
	}
}

// ----------------------------------------------------------------------------
// Set
// ----------------------------------------------------------------------------

template<typename T>
inline void		Queue<T>::Node::Set (T&& item)
{
	if (m_next == free) {
		::new (m_item) T (std::move (item));
		m_next = null;
	} else {
		*reinterpret_cast<T*> (m_item) = std::move (item);
	}
}

// ----------------------------------------------------------------------------
// GetNext
// ----------------------------------------------------------------------------

template<typename T>
inline UIndex	Queue<T>::Node::GetNext () const noexcept
{
	return m_next;
}

// ----------------------------------------------------------------------------
// SetNext
// ----------------------------------------------------------------------------

template<typename T>
inline void		Queue<T>::Node::SetNext (UIndex next) noexcept
{
	m_next = next;
}

// ----------------------------------------------------------------------------
// IsFree
// ----------------------------------------------------------------------------

template<typename T>
inline bool		Queue<T>::Node::IsFree () const noexcept
{
	return (m_next == free);
}

// ----------------------------------------------------------------------------
// Free
// ----------------------------------------------------------------------------

template<typename T>
inline void		Queue<T>::Node::Free () noexcept
{
	if (m_next != free) {
		reinterpret_cast<T*> (m_item)->~T ();
	}

	m_next = free;
}

// ----------------------------------------------------------------------------
// Read
// ----------------------------------------------------------------------------

template<typename T>
inline GSErrCode	Queue<T>::Node::Read (IChannel& ic)
{
	if (IsFree ())
		::new (m_item) T ();

	return ic.Read (Get ());
}

// ----------------------------------------------------------------------------
// Write
// ----------------------------------------------------------------------------

template<typename T>
inline GSErrCode	Queue<T>::Node::Write (OChannel& oc) const
{
	return oc.Write (Get ());
}

///////////////////////////////////////////////////////////////////////////////
// Global functions

// ----------------------------------------------------------------------------
// begin
// ----------------------------------------------------------------------------

template <typename T>
auto	begin (Queue<T>& queue)
{
	return queue.Begin ();
}

// ----------------------------------------------------------------------------
// end
// ----------------------------------------------------------------------------

template <typename T>
auto	end (Queue<T>& queue)
{
	return queue.End ();
}

// ----------------------------------------------------------------------------
// begin
// ----------------------------------------------------------------------------

template <typename T>
auto	begin (const Queue<T>& queue)
{
	return queue.Begin ();
}

// ----------------------------------------------------------------------------
// end
// ----------------------------------------------------------------------------

template <typename T>
auto	end (const Queue<T>& queue)
{
	return queue.End ();
}

// ----------------------------------------------------------------------------
// GetInserter
// ----------------------------------------------------------------------------

template <class Type>
auto	GetInserter (Queue<Type>& queue)
{
	return PushInserter<Queue<Type>> (&queue);
}

}

#endif // GS_QUEUE_HPP
