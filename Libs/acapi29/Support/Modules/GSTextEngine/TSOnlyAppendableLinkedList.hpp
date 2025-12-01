// *********************************************************************************************************************
// Description:		OnlyAppendableLinkedList
//
// Module:			
// Namespace:		TE :: ThreadSafe
// Contact person:	PM
//
// Note:			Arra epitjuk az egesz strukturat, hogy head es Node::next ertekek alapbol nullptr-k, es max 1x valtoznak a container letezese alatt.
//					Az iteralas TS, de 1 iterator tobb threadbol valo hasznalata nem.
//
// SG compatible
// *********************************************************************************************************************

#if !defined (ONLYAPPENDABLELINKEDLIST_HPP)
#define ONLYAPPENDABLELINKEDLIST_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"
#include	"ForwardContainerIterator.hpp"
#include	"Container.hpp"
#include	"MemoryBarrier.hpp"
#include	"Atomic.hpp"
#include	<functional>

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace TE { namespace TS {

	// --- Constant definitions	--------------------------------------------------------------------------------------------

	// --- Type definitions	------------------------------------------------------------------------------------------------

	template <class Type>
	class OnlyAppendableLinkedList : private GS::Container<Type> {

	private:
		struct Node {

			Type	value;
			Node	*next;

			explicit Node (const Type& val)
				: value	(val)
				, next	(nullptr) 
			{}

			explicit Node (Type&& val)
				: value	(val)
				, next	(nullptr)
			{}
		};


		// Iterator support

		struct IteratorState {

			Node	*current;
			explicit IteratorState (Node* const initNode) : current (initNode) {}
		};

		Type&			GetCurrent (const IteratorState& state);
		const Type&		GetCurrent (const IteratorState& state) const;

		void			Increment	(IteratorState& state) const;
		bool			IsEnd		(const IteratorState& state) const;
		bool			IsEqual		(const IteratorState& state1, const IteratorState& state2) const;

		friend class GS::GeneralForwardContainerIterator<OnlyAppendableLinkedList, IteratorState, Type>;
		friend class GS::ConstGeneralForwardContainerIterator<OnlyAppendableLinkedList, IteratorState, Type>;

		OnlyAppendableLinkedList& operator=(const OnlyAppendableLinkedList&); //disabled

	private:
		Node	*head;

	public:
		// Types

		typedef GS::ConstForwardIterator<Type>	ConstIterator;
		typedef GS::ForwardIterator<Type>		Iterator;


		// Constructors, Destructor 

		OnlyAppendableLinkedList ();
		OnlyAppendableLinkedList (const OnlyAppendableLinkedList& source);
		OnlyAppendableLinkedList (OnlyAppendableLinkedList&& source);
		OnlyAppendableLinkedList (GS::ConstForwardIterator<Type> iterator);

		~OnlyAppendableLinkedList ();


		// Functions

		Type&	Append (const Type& value);
		Type&	Append (Type&& value);
		void	Append (GS::ConstForwardIterator<Type> iterator);

		bool FindFirst (const std::function<bool(const Type&)>& condition, const Type** const found = nullptr) const;
		bool FindFirst (const std::function<bool(const Type&)>& condition, Type** const found = nullptr);

		bool FindLast (const std::function<bool(const Type&)>& condition, const Type** const found = nullptr) const;
		bool FindLast (const std::function<bool(const Type&)>& condition, Type** const found = nullptr);

		ConstIterator	Enumerate (void) const;
		Iterator		Enumerate (void);
		void			Enumerate (std::function<void (const Type&)> processor) const;
		void			Enumerate (std::function<void (Type&)> processor);

		bool	IsEmpty (void) const;
		USize	GetSize (void) const;

	private:
						void AddNode				(Node* const newNode);
		static inline	bool IsNullAndSwapIfNull	(Node ** const node, Node* const newValue);

	};



	// --- Variable declarations -------------------------------------------------------------------------------------------

	// --- Function declarations -------------------------------------------------------------------------------------------

	template <class Type>
	OnlyAppendableLinkedList<Type>::OnlyAppendableLinkedList ()
		: head (nullptr)
	{}


	template <class Type>
	OnlyAppendableLinkedList<Type>::OnlyAppendableLinkedList (const OnlyAppendableLinkedList<Type>& source)
		: head (nullptr)
	{
		for (OnlyAppendableLinkedList<Type>::ConstIterator it = source.Enumerate (); it != nullptr; ++it) {
			Append (*it);
		}
	}
	
	
	template <class Type>
	OnlyAppendableLinkedList<Type>::OnlyAppendableLinkedList (OnlyAppendableLinkedList<Type>&& source)
		: head (nullptr)
	{
		head = source.head;
		source.head = nullptr;
	}


	template <class Type>
	OnlyAppendableLinkedList<Type>::OnlyAppendableLinkedList (GS::ConstForwardIterator<Type> iterator)
		: head (nullptr)
	{
		while (iterator != nullptr)
			Append (*iterator++);
	}


	template <class Type>
	OnlyAppendableLinkedList<Type>::~OnlyAppendableLinkedList ()
	{
		while (head != nullptr) 
		{
			Node* tmp = head;
			head = head->next;
			delete tmp;
		}
	}


	template <class Type>
	Type& OnlyAppendableLinkedList<Type>::Append (const Type& value)
	{
		Node* newNode = new Node (value);
		GS::MemoryBarrierForNonVolatile ();

		AddNode (newNode);

		return newNode->value;
	}


	template <class Type>
	Type& OnlyAppendableLinkedList<Type>::Append (Type&& value)
	{
		Node* newNode = new Node (std::move (value));
		GS::MemoryBarrierForNonVolatile ();

		AddNode (newNode);

		return newNode->value;
	}


	template <class Type>
	void OnlyAppendableLinkedList<Type>::Append (GS::ConstForwardIterator<Type> iterator)
	{
		while (iterator != nullptr)
			Append (*iterator++);
	}


	template <class Type>
	bool OnlyAppendableLinkedList<Type>::FindFirst (const std::function<bool(const Type&)>& condition, const Type** const found /*= nullptr*/) const
	{
		Node* it = head;

		while (it != nullptr) {

			GS::MemoryBarrierForNonVolatile ();
			if (condition (it->value)) {

				if (found != nullptr)
					*found = &it->value;
				return true;
			}

			it = it->next;
		}

		return false;
	}


	template <class Type>
	bool OnlyAppendableLinkedList<Type>::FindFirst (const std::function<bool(const Type&)>& condition, Type** const found/*= nullptr*/) {
		const Type** const tmp = const_cast<const Type**> (found);
		return FindFirst (condition, tmp);
	}


	template <class Type>
	bool OnlyAppendableLinkedList<Type>::FindLast (const std::function<bool(const Type&)>& condition, const Type** const found/*= nullptr*/) const
	{
		Node* it = head;
		bool isFound = false;

		while (it != nullptr) {

			GS::MemoryBarrierForNonVolatile ();		
			if (condition (it->value)) {

				if (found != nullptr)
					*found = &it->value;
				isFound = true;
			}

			it = it->next;
		}

		return isFound;
	}


	template <class Type>
	bool OnlyAppendableLinkedList<Type>::FindLast (const std::function<bool(const Type&)>& condition, Type** const found/*= nullptr*/) {
		const Type** const tmp = const_cast<const Type**> (found);
		return FindLast (condition, tmp);
	}
	

	template <class Type>
	typename GS::ConstForwardIterator<Type>	OnlyAppendableLinkedList<Type>::Enumerate (void) const
	{
		Node* tmp = head;
		GS::MemoryBarrierForNonVolatile ();
		return GS::ConstForwardIterator<Type> (new GS::ConstGeneralForwardContainerIterator<OnlyAppendableLinkedList, IteratorState, Type> (*this, IteratorState (tmp)));
	}


	template <class Type>
	typename GS::ForwardIterator<Type> OnlyAppendableLinkedList<Type>::Enumerate (void)
	{
		Node* tmp = head;
		GS::MemoryBarrierForNonVolatile ();
		return GS::ForwardIterator<Type> (new GS::GeneralForwardContainerIterator<OnlyAppendableLinkedList, IteratorState, Type> (*this, IteratorState (tmp)));
	}


	template <class Type>
	void OnlyAppendableLinkedList<Type>::Enumerate (std::function<void (const Type&)> processor) const
	{
		for (ConstIterator it = Enumerate (); it != nullptr; ++it)
			processor (*it);
	}


	template <class Type>
	void OnlyAppendableLinkedList<Type>::Enumerate (std::function<void (Type&)> processor)
	{
		for (Iterator it = Enumerate (); it != nullptr; ++it)
			processor (*it);
	}


	template <class Type>
	bool	OnlyAppendableLinkedList<Type>::IsEmpty (void) const
	{
		OnlyAppendableLinkedList<Type>::ConstIterator it = Enumerate ();
		return (it == nullptr);
	}


	template <class Type>
	USize	OnlyAppendableLinkedList<Type>::GetSize (void) const
	{
		USize size = 0;
		for (OnlyAppendableLinkedList<Type>::ConstIterator it = Enumerate (); it != nullptr; ++it)
			++size;

		return size;
	}


	template <class Type>
	void OnlyAppendableLinkedList<Type>::AddNode (Node* const newNode)
	{
		Node** it = &head;

		while ( ! IsNullAndSwapIfNull (it, newNode) ) {
			GS::MemoryBarrierForNonVolatile ();
			it = &( (**it).next );
		}
	}


	template <class Type>
	inline bool OnlyAppendableLinkedList<Type>::IsNullAndSwapIfNull (Node ** const node, Node* const newValue)
	{
		if (*node == nullptr)
			return GS::AtomicCompareAndSwap (reinterpret_cast<void **> (node), newValue, nullptr);
		else
			return false;
	}


	template <class Type>
	Type&	OnlyAppendableLinkedList<Type>::GetCurrent (const IteratorState& state)
	{
		return state.current->value;
	}


	template <class Type>
	const Type&	OnlyAppendableLinkedList<Type>::GetCurrent (const IteratorState& state) const
	{
		return state.current->value;	
	}


	template <class Type>
	void	OnlyAppendableLinkedList<Type>::Increment (IteratorState& state) const
	{ 
		Node* tmp = state.current->next;
		GS::MemoryBarrierForNonVolatile ();
		state.current = tmp;
	}


	template <class Type>
	bool	OnlyAppendableLinkedList<Type>::IsEnd (const IteratorState& state) const
	{
		return (state.current == nullptr);
	}


	template <class Type>
	bool	OnlyAppendableLinkedList<Type>::IsEqual (const IteratorState& state1, const IteratorState& state2) const
	{
		return (state1.current == state2.current);
	}


} /* namespace ThreadSafe */ } /* namespace TE */

#endif
