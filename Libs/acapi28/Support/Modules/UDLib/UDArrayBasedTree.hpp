#ifndef GS_UD_ARRAYBASEDTREE_HPP
#define GS_UD_ARRAYBASEDTREE_HPP
#pragma once

#include "PagedArray.hpp"
#include "DGDefs.h"
#include "UDDefinitions.hpp"

#include <queue>
#include <deque>

#if defined (_INC_WINDOWSX)
#undef GetFirstChild //in windows.h, this is a define!
#endif

namespace UD {

class UD_DLL_EXPORT ArrayBasedTreeBase {
public:
	static constexpr Int32 ExternalIndexBaseIndex = -65536;

	enum GetItemFlag {
		First				= DG_TVG_FIRST,
		Next				= DG_TVG_NEXT,
		Previous			= DG_TVG_PREVIOUS,
		Parent				= DG_TVG_PARENT,
		Child				= DG_TVG_CHILD
	};

	enum ItemType : Int32 {
		AllItems		= DG_ALL_ITEMS,
		NoItem			= DG_TVI_NONE,
		RootItem		= DG_TVI_ROOT,
		TopItem			= DG_TVI_TOP,
		BottomItem		= DG_TVI_BOTTOM
	};

	enum class LevelEnumerationMode {
		FullDepth,
		OnlyDirectChildren
	};

public:
	virtual ~ArrayBasedTreeBase ();

	bool	IsOwnIndex (const Int32 index) const;

protected:
	virtual USize GetInternalContainerSize () const = 0;

	Int32 GetInternalIndex (const Int32 externalIndex) const;

};


template<class Type>
class ArrayBasedTree : public ArrayBasedTreeBase {
public:
	class Node {
	private:
		Type	value;
		Node*	parent;
		Int32	numChildren;
		Int32	arrayIndex;
		Node*	firstChild;
		Node*	lastChild;
		Node*	previous;
		Node*	next;

	public:

		Node ();
		Node (const Type& newValue);
		virtual ~Node ();

		const Node* GetParent () const;
		Node* GetParent ();

		Int32	GetNumChildren () const;

		const Node* GetFirstChild () const;
		Node* GetFirstChild ();

		const Node* GetLastChild () const;
		Node* GetLastChild ();

		const Node* GetPrevious () const;
		Node* GetPrevious ();

		const Node* GetNext () const;
		Node* GetNext ();

		Int32 GetIndex () const;

		const Type& Get () const;
		Type& Get ();
		void Set (const Type& newValue);

		operator const Type& () const;
		operator Type& ();

		friend class ArrayBasedTreeBase;
		template<class U> friend class ArrayBasedTree;

	private:
		void Reset ();
	};

private:
	GS::PagedArray<Node>	items;
	USize					numItems;

public:
	ArrayBasedTree ();

	using EnumerateFunction = std::function<void (Node&)>;
	using ConstEnumerateFunction = std::function<void (const Node&)>;
	using SearchConditionFunction = std::function<bool (const Node&)>;

	Int32 AppendItem (const Int32 parentIndex);
	Int32 InsertItem (const Int32 parentIndex, const Int32 targetIndex);
	void  DeleteItem (const Int32 itemIndex);

	const Node& AccessItem (const Int32 targetIndex) const;
	Node& AccessItem (const Int32 targetIndex);

	const Type& AccessItemValue (const Int32 targetIndex) const;
	Type& AccessItemValue (const Int32 targetIndex);

	Int32	GetItem (const Int32 itemIndex, const ArrayBasedTreeBase::GetItemFlag flag) const;

	Int32	GetTopMostParent (const Int32 itemIndex) const;

	USize	GetItemCount () const;

	void	EnumerateInDepth (const Int32 fromIndex, const ConstEnumerateFunction& enumerateFn) const;
	void	EnumerateInDepth (const Int32 fromIndex, const EnumerateFunction& enumerateFn);
	void	EnumerateInDepth (const Node& fromItem, const ConstEnumerateFunction& enumerateFn) const;
	void	EnumerateInDepth (Node& fromItem, const EnumerateFunction& enumerateFn);

	void	EnumerateInLevel (const Int32 fromIndex, const ConstEnumerateFunction& enumerateFn, LevelEnumerationMode levelEnumerationMode = LevelEnumerationMode::FullDepth) const;
	void	EnumerateInLevel (const Int32 fromIndex, const EnumerateFunction& enumerateFn, LevelEnumerationMode levelEnumerationMode = LevelEnumerationMode::FullDepth);
	void	EnumerateInLevel (const Node& fromItem, const ConstEnumerateFunction& enumerateFn, LevelEnumerationMode levelEnumerationMode = LevelEnumerationMode::FullDepth) const;
	void	EnumerateInLevel (Node& fromItem, const EnumerateFunction& enumerateFn, LevelEnumerationMode levelEnumerationMode = LevelEnumerationMode::FullDepth);

	void	EnumerateFromTopmosParent (const Int32 fromIndex, const ConstEnumerateFunction& enumerateFn) const;
	void	EnumerateFromTopmosParent (const Int32 fromIndex, const EnumerateFunction& enumerateFn);
	void	EnumerateFromTopmosParent (const Node& fromItem, const ConstEnumerateFunction& enumerateFn) const;
	void	EnumerateFromTopmosParent (Node& fromItem, const EnumerateFunction& enumerateFn);

	void	EnumerateToTopmosParent (const Int32 fromIndex, const ConstEnumerateFunction& enumerateFn) const;
	void	EnumerateToTopmosParent (const Int32 fromIndex, const EnumerateFunction& enumerateFn);
	void	EnumerateToTopmosParent (const Node& fromItem, const ConstEnumerateFunction& enumerateFn) const;
	void	EnumerateToTopmosParent (Node& fromItem, const EnumerateFunction& enumerateFn);

	bool	HasParentWithCondition (const Int32 fromIndex, const SearchConditionFunction& searchConditionFn) const;
	bool	HasParentWithCondition (const Node& fromItem, const SearchConditionFunction& searchConditionFn) const;

	bool	HasChildWithCondition (const Int32 fromIndex, const SearchConditionFunction& searchConditionFn) const;
	bool	HasChildWithCondition (const Node& fromItem, const SearchConditionFunction& searchConditionFn) const;

private:
	virtual USize GetInternalContainerSize () const override;

	void UnchainTreeItem (Node* parent, Node* workItem);

	void ChainTreeItem (Node* parentItem, Node* itemToInsert, const Int32 internalIndex);

};


template<class Type>
ArrayBasedTree<Type>::Node::Node () :
	value (),
	parent (nullptr),
	numChildren (0),
	firstChild (nullptr),
	lastChild (nullptr),
	next (nullptr),
	previous (nullptr),
	arrayIndex (-1)
{}


template<class Type>
ArrayBasedTree<Type>::Node::Node (const Type& newValue) :
	value (newValue),
	parent (nullptr),
	numChildren (0),
	firstChild (nullptr),
	lastChild (nullptr),
	next (nullptr),
	previous (nullptr),
	arrayIndex (-1)
{}


template<class Type>
ArrayBasedTree<Type>::Node::~Node () = default;


template<class Type>
const typename ArrayBasedTree<Type>::Node* ArrayBasedTree<Type>::Node::GetParent () const
{
	return parent;
}


template<class Type>
typename ArrayBasedTree<Type>::Node* ArrayBasedTree<Type>::Node::GetParent ()
{
	return parent;
}


template<class Type>
Int32		ArrayBasedTree<Type>::Node::GetNumChildren () const
{
	return numChildren;
}


template<class Type>
const typename ArrayBasedTree<Type>::Node* ArrayBasedTree<Type>::Node::GetFirstChild () const
{
	return firstChild;
}


template<class Type>
typename ArrayBasedTree<Type>::Node* ArrayBasedTree<Type>::Node::GetFirstChild ()
{
	return firstChild;
}


template<class Type>
const typename ArrayBasedTree<Type>::Node* ArrayBasedTree<Type>::Node::GetLastChild () const
{
	return lastChild;
}


template<class Type>
typename ArrayBasedTree<Type>::Node* ArrayBasedTree<Type>::Node::GetLastChild ()
{
	return lastChild;
}


template<class Type>
const typename ArrayBasedTree<Type>::Node* ArrayBasedTree<Type>::Node::GetPrevious () const
{
	return previous;
}


template<class Type>
typename ArrayBasedTree<Type>::Node* ArrayBasedTree<Type>::Node::GetPrevious ()
{
	return previous;
}


template<class Type>
const typename ArrayBasedTree<Type>::Node* ArrayBasedTree<Type>::Node::GetNext () const
{
	return next;
}


template<class Type>
typename ArrayBasedTree<Type>::Node* ArrayBasedTree<Type>::Node::GetNext ()
{
	return next;
}


template<class Type>
Int32 ArrayBasedTree<Type>::Node::GetIndex () const
{
	return arrayIndex == -1 ? ArrayBasedTreeBase::ItemType::RootItem : ArrayBasedTreeBase::ExternalIndexBaseIndex - arrayIndex;
}


template<class Type>
const Type& ArrayBasedTree<Type>::Node::Get () const
{
	return value;
}


template<class Type>
Type& ArrayBasedTree<Type>::Node::Get ()
{
	return value;
}


template<class Type>
void ArrayBasedTree<Type>::Node::Set (const Type& newValue)
{
	value = newValue;
}


template<class Type>
ArrayBasedTree<Type>::Node::operator const Type& () const
{
	return value;
}


template<class Type>
ArrayBasedTree<Type>::Node::operator Type& ()
{
	return value;
}


template<class Type>
void ArrayBasedTree<Type>::Node::Reset ()
{
	firstChild = lastChild = next = previous = parent = nullptr;
	numChildren = 0;
	arrayIndex = -1;
	value = Type ();
}


template<class Type>
ArrayBasedTree<Type>::ArrayBasedTree () :
	numItems (0)
{
	items.Push (Type ());
	items.GetLast ().arrayIndex = 0;
}


template<class Type>
Int32 ArrayBasedTree<Type>::AppendItem (const Int32 parentIndex)
{
	return InsertItem (parentIndex, ArrayBasedTreeBase::ItemType::BottomItem);
}


template<class Type>
Int32 ArrayBasedTree<Type>::InsertItem (const Int32 parentIndex, const Int32 targetIndex)
{
	Int32 internalParentIndex = GetInternalIndex (parentIndex);
	Int32 internalTargetIndex = GetInternalIndex (targetIndex);
	if (DBVERIFY_GUID (internalParentIndex >= 0 && static_cast<UIndex> (internalParentIndex) < items.GetSize () &&
					   ((internalTargetIndex > 0 && static_cast<UIndex> (internalTargetIndex) < items.GetSize ()) ||
						(internalTargetIndex == ArrayBasedTreeBase::ItemType::TopItem || internalTargetIndex == ArrayBasedTreeBase::ItemType::BottomItem)),
					   "{5F103C07-66A8-423A-B4B5-CC597639D9C9}"))
	{
		Node* workParent = &items[internalParentIndex];
		Node	treeItem;
		treeItem.arrayIndex = items.GetSize ();
		items.Push (treeItem);
		ChainTreeItem (workParent, &items.GetLast (), internalTargetIndex);
		++numItems;
		return treeItem.GetIndex ();
	} else {
		return ArrayBasedTreeBase::ItemType::NoItem;
	}
}


template<class Type>
void ArrayBasedTree<Type>::DeleteItem (const Int32 itemIndex)
{
	Int32 internalIndex = GetInternalIndex (itemIndex);
	if (DBVERIFY (internalIndex == ArrayBasedTreeBase::AllItems || internalIndex == ArrayBasedTreeBase::TopItem || internalIndex == ArrayBasedTreeBase::BottomItem ||
				  (internalIndex > 0 && static_cast<UIndex> (internalIndex) < items.GetSize ())))
	{
		if (itemIndex == ArrayBasedTreeBase::AllItems) {
			items.Clear (false);
			items.Push (Type ());
			numItems = 0;
			return;
		}

		Node& treeItem = AccessItem (itemIndex);

		if (treeItem.parent == nullptr) {
			return;
		}

		Node* parent = treeItem.parent;

		UnchainTreeItem (parent, &treeItem);

		std::vector<Node*> itemPtrs;

		if (treeItem.firstChild != nullptr) {
			EnumerateInDepth (treeItem, [&] (Node& item) {
				if (&treeItem != &item) {
					itemPtrs.push_back (&item);
				}
			});
		}
		for (auto& itemPtr : itemPtrs) {
			itemPtr->Reset ();
			numItems--;
		}

		treeItem.Reset ();
		numItems--;
	}
}


template<class Type>
const typename ArrayBasedTree<Type>::Node& ArrayBasedTree<Type>::AccessItem (const Int32 targetIndex) const
{
	Int32 internalIndex = ArrayBasedTreeBase::ItemType::NoItem;
	if (targetIndex == ArrayBasedTreeBase::ItemType::TopItem && GetItemCount () > 0) {
		internalIndex = items[0].GetFirstChild ()->arrayIndex;
	} else if (targetIndex == ArrayBasedTreeBase::ItemType::BottomItem && GetItemCount () > 0) {
		auto lastChild = items[0].GetLastChild ();
		while (lastChild->GetLastChild () != nullptr) {
			lastChild = lastChild->GetLastChild ();
		}
		internalIndex = lastChild->arrayIndex;
	} else {
		internalIndex = GetInternalIndex (targetIndex);
	}

	if (DBVERIFY_GUID (internalIndex > 0 && static_cast<UIndex> (internalIndex) < items.GetSize (), "{22075E88-BA05-4EE0-8C49-B1226D62F673}")) {
		return items[internalIndex];
	} else {
		throw GS::IllegalArgumentException ();
	}
}


template<class Type>
typename ArrayBasedTree<Type>::Node& ArrayBasedTree<Type>::AccessItem (const Int32 targetIndex)
{
	Int32 internalIndex = ArrayBasedTreeBase::ItemType::NoItem;
	if (targetIndex == ArrayBasedTreeBase::ItemType::TopItem && GetItemCount () > 0) {
		internalIndex = items[0].GetFirstChild ()->arrayIndex;
	} else if (targetIndex == ArrayBasedTreeBase::ItemType::BottomItem && GetItemCount () > 0) {
		auto lastChild = items[0].GetLastChild ();
		while (lastChild->GetLastChild () != nullptr) {
			lastChild = lastChild->GetLastChild ();
		}
		internalIndex = lastChild->arrayIndex;
	} else {
		internalIndex = GetInternalIndex (targetIndex);
	}

	if (DBVERIFY_GUID (internalIndex > 0 && static_cast<UIndex> (internalIndex) < items.GetSize (), "{0AB29B3B-A1ED-4B99-86E0-7CDCEBD5F4F9}")) {
		return items[internalIndex];
	} else {
		throw GS::IllegalArgumentException ();
	}
}


template<class Type>
const Type& ArrayBasedTree<Type>::AccessItemValue (const Int32 targetIndex) const
{
	return AccessItem (targetIndex).Get ();
}


template<class Type>
Type& ArrayBasedTree<Type>::AccessItemValue (const Int32 targetIndex)
{
	return AccessItem (targetIndex).Get ();
}



template<class Type>
Int32 ArrayBasedTree<Type>::GetItem (const Int32 itemIndex, const ArrayBasedTreeBase::GetItemFlag flag) const
{
	Int32 internalIndex = GetInternalIndex (itemIndex);

	if (DBERROR_GUID (internalIndex < 0 || static_cast<UIndex> (internalIndex) >= items.GetSize (), "{37F5B890-DBA0-4D82-A59C-1E08855980E2}")) {
		return ArrayBasedTreeBase::ItemType::NoItem;
	}

	auto& item = flag == ArrayBasedTreeBase::GetItemFlag::First ? items[0] : items[internalIndex];

	switch (flag) {
		case ArrayBasedTreeBase::GetItemFlag::First:
			return (item.firstChild != nullptr) ? item.firstChild->GetIndex () : ArrayBasedTreeBase::ItemType::NoItem;

		case ArrayBasedTreeBase::GetItemFlag::Next:
			return (item.next != nullptr) ? item.next->GetIndex () : ArrayBasedTreeBase::ItemType::NoItem;

		case ArrayBasedTreeBase::GetItemFlag::Previous:
			return (item.previous != nullptr) ? item.previous->GetIndex () : ArrayBasedTreeBase::ItemType::NoItem;

		case ArrayBasedTreeBase::GetItemFlag::Parent:
			return (item.parent != nullptr) ? item.parent->GetIndex () : ArrayBasedTreeBase::ItemType::NoItem;

		case ArrayBasedTreeBase::GetItemFlag::Child:
			return (item.firstChild != nullptr) ? item.firstChild->GetIndex () : ArrayBasedTreeBase::ItemType::NoItem;

		default:
			DBBREAK_GUID ("{37777A7C-C014-4EA0-BA24-A0C0FBA27C3A}");
			return ArrayBasedTreeBase::ItemType::NoItem;
	}
}


template<class Type>
Int32	ArrayBasedTree<Type>::GetTopMostParent (const Int32 itemIndex) const
{
	Int32 internalIndex = GetInternalIndex (itemIndex);

	if (DBERROR_GUID (internalIndex < 0 || static_cast<UIndex> (internalIndex) >= items.GetSize (), "{A30FF74C-1EFF-4985-B7D1-09C8737AF1A6}")) {
		return ArrayBasedTreeBase::ItemType::NoItem;
	}

	auto item = &items[internalIndex];

	Int32 parentIndex = ArrayBasedTreeBase::ItemType::NoItem;
	while (item->GetParent () != nullptr) {
		parentIndex = item->GetIndex ();
		item = item->GetParent ();
	}

	return parentIndex;
}



template<class Type>
USize	ArrayBasedTree<Type>::GetItemCount () const
{
	return numItems;
}


template<class Type>
void	ArrayBasedTree<Type>::EnumerateInDepth (const Int32 fromIndex, const ConstEnumerateFunction& enumerateFn) const
{
	Int32 internalIndex = GetInternalIndex (fromIndex);
	if (DBVERIFY (internalIndex >= 0) && static_cast<UIndex> (internalIndex) < items.GetSize ()) {
		EnumerateInDepth (items[internalIndex], enumerateFn);
	}
}


template<class Type>
void	ArrayBasedTree<Type>::EnumerateInDepth (const Int32 fromIndex, const EnumerateFunction& enumerateFn)
{
	Int32 internalIndex = GetInternalIndex (fromIndex);
	if (DBVERIFY (internalIndex >= 0) && static_cast<UIndex> (internalIndex) < items.GetSize ()) {
		EnumerateInDepth (items[internalIndex], enumerateFn);
	}
}



template<class Type>
void	ArrayBasedTree<Type>::EnumerateInDepth (const Node& fromItem, const ConstEnumerateFunction& enumerateFn) const
{
	std::deque<const Node*> items;

	items.push_back (&fromItem);

	while (!items.empty ()) {
		auto item = items.front ();
		items.pop_front ();
		if (item->GetParent () != nullptr) {
			enumerateFn (*item);
		}
		if (item->lastChild != nullptr) {
			items.push_front (item->lastChild);
			auto prevItem = item->lastChild->previous;
			while (prevItem != nullptr) {
				items.push_front (prevItem);
				prevItem = prevItem->previous;
			}
		}
	}
}


template<class Type>
void	ArrayBasedTree<Type>::EnumerateInDepth (Node& fromItem, const EnumerateFunction& enumerateFn)
{
	std::deque<Node*> items;

	items.push_back (&fromItem);

	while (!items.empty ()) {
		auto item = items.front ();
		items.pop_front ();
		if (item->GetParent () != nullptr) {
			enumerateFn (*item);
		}
		if (item->lastChild != nullptr) {
			items.push_front (item->lastChild);
			auto prevItem = item->lastChild->previous;
			while (prevItem != nullptr) {
				items.push_front (prevItem);
				prevItem = prevItem->previous;
			}
		}
	}
}


template<class Type>
void	ArrayBasedTree<Type>::EnumerateInLevel (const Int32 fromIndex, const ConstEnumerateFunction& enumerateFn, LevelEnumerationMode levelEnumerationMode) const
{
	Int32 internalIndex = GetInternalIndex (fromIndex);
	if (DBVERIFY (internalIndex >= 0) && static_cast<UIndex> (internalIndex) < items.GetSize ()) {
		EnumerateInLevel (items[internalIndex], enumerateFn, levelEnumerationMode);
	}
}


template<class Type>
void	ArrayBasedTree<Type>::EnumerateInLevel (const Int32 fromIndex, const EnumerateFunction& enumerateFn, LevelEnumerationMode levelEnumerationMode)
{
	Int32 internalIndex = GetInternalIndex (fromIndex);
	if (DBVERIFY (internalIndex >= 0) && static_cast<UIndex> (internalIndex) < items.GetSize ()) {
		EnumerateInLevel (items[internalIndex], enumerateFn, levelEnumerationMode);
	}
}


template<class Type>
void	ArrayBasedTree<Type>::EnumerateInLevel (const Node& fromItem, const ConstEnumerateFunction& enumerateFn, LevelEnumerationMode levelEnumerationMode) const
{
	std::queue<const Node*> items;

	items.push (&fromItem);

	bool enumerateChildren = true;

	while (!items.empty ()) {
		auto item = items.front ();
		items.pop ();
		if (item->GetParent () != nullptr) {
			enumerateFn (*item);
		}
		if (enumerateChildren && item->firstChild != nullptr) {
			items.push (item->firstChild);
			auto nextItem = item->firstChild->next;
			while (nextItem != nullptr) {
				items.push (nextItem);
				nextItem = nextItem->next;
			}
			if (levelEnumerationMode == LevelEnumerationMode::OnlyDirectChildren) {
				enumerateChildren = false;
			}
		}
	}
}


template<class Type>
void	ArrayBasedTree<Type>::EnumerateInLevel (Node& fromItem, const EnumerateFunction& enumerateFn, LevelEnumerationMode levelEnumerationMode)
{
	std::queue<Node*> items;

	items.push (&fromItem);

	bool enumerateChildren = true;

	while (!items.empty ()) {
		auto item = items.front ();
		items.pop ();
		if (item->GetParent () != nullptr) {
			enumerateFn (*item);
		}
		if (enumerateChildren && item->firstChild != nullptr) {
			items.push (item->firstChild);
			auto nextItem = item->firstChild->next;
			while (nextItem != nullptr) {
				items.push (nextItem);
				nextItem = nextItem->next;
			}
			if (levelEnumerationMode == LevelEnumerationMode::OnlyDirectChildren) {
				enumerateChildren = false;
			}
		}
	}
}


template<class Type>
void	ArrayBasedTree<Type>::EnumerateFromTopmosParent (const Int32 fromIndex, const ConstEnumerateFunction& enumerateFn) const
{
	Int32 internalIndex = GetInternalIndex (fromIndex);
	if (DBVERIFY (internalIndex >= 0) && static_cast<UIndex> (internalIndex) < items.GetSize ()) {
		EnumerateFromTopmosParent (items[internalIndex], enumerateFn);
	}
}


template<class Type>
void	ArrayBasedTree<Type>::EnumerateFromTopmosParent (const Int32 fromIndex, const EnumerateFunction& enumerateFn)
{
	Int32 internalIndex = GetInternalIndex (fromIndex);
	if (DBVERIFY (internalIndex >= 0) && static_cast<UIndex> (internalIndex) < items.GetSize ()) {
		EnumerateFromTopmosParent (items[internalIndex], enumerateFn);
	}
}


template<class Type>
void	ArrayBasedTree<Type>::EnumerateFromTopmosParent (const Node& fromItem, const ConstEnumerateFunction& enumerateFn) const
{
	std::deque<const Node*> items;

	auto item = &fromItem;

	while (item->GetParent () != nullptr) {
		items.push_front (item);
		item = item->GetParent ();
	}

	for (auto item : items) {
		enumerateFn (*item);
	}
}


template<class Type>
void	ArrayBasedTree<Type>::EnumerateFromTopmosParent (Node& fromItem, const EnumerateFunction& enumerateFn)
{
	std::deque<Node*> items;

	auto item = &fromItem;

	while (item->GetParent () != nullptr) {
		items.push_front (item);
		item = item->GetParent ();
	}

	for (auto item : items) {
		enumerateFn (*item);
	}
}


template<class Type>
void	ArrayBasedTree<Type>::EnumerateToTopmosParent (const Int32 fromIndex, const ConstEnumerateFunction& enumerateFn) const
{
	Int32 internalIndex = GetInternalIndex (fromIndex);
	if (DBVERIFY (internalIndex >= 0) && static_cast<UIndex> (internalIndex) < items.GetSize ()) {
		EnumerateToTopmosParent (items[internalIndex], enumerateFn);
	}
}


template<class Type>
void	ArrayBasedTree<Type>::EnumerateToTopmosParent (const Int32 fromIndex, const EnumerateFunction& enumerateFn)
{
	Int32 internalIndex = GetInternalIndex (fromIndex);
	if (DBVERIFY (internalIndex >= 0) && static_cast<UIndex> (internalIndex) < items.GetSize ()) {
		EnumerateToTopmosParent (items[internalIndex], enumerateFn);
	}
}


template<class Type>
void	ArrayBasedTree<Type>::EnumerateToTopmosParent (const Node& fromItem, const ConstEnumerateFunction& enumerateFn) const
{
	auto item = &fromItem;

	while (item->GetParent () != nullptr) {
		enumerateFn (*item);
		item = item->GetParent ();
	}
}


template<class Type>
void	ArrayBasedTree<Type>::EnumerateToTopmosParent (Node& fromItem, const EnumerateFunction& enumerateFn)
{
	auto item = &fromItem;

	while (item->GetParent () != nullptr) {
		enumerateFn (*item);
		item = item->GetParent ();
	}
}


template<class Type>
bool	ArrayBasedTree<Type>::HasParentWithCondition (const Int32 fromIndex, const SearchConditionFunction& searchConditionFn) const
{
	Int32 internalIndex = GetInternalIndex (fromIndex);
	if (DBVERIFY_GUID (internalIndex > 0 && static_cast<UIndex> (internalIndex) < items.GetSize (), "{3E3BE547-F4C0-4CEA-9B81-A221F0ECA661}")) {
		return HasParentWithCondition (items[internalIndex], searchConditionFn);
	} else {
		return false;
	}
}


template<class Type>
bool	ArrayBasedTree<Type>::HasParentWithCondition (const Node& fromItem, const SearchConditionFunction& searchConditionFn) const
{
	if (fromItem.GetParent () != nullptr) {
		std::queue<const Node*> items;

		items.push (fromItem.GetParent ());

		while (!items.empty ()) {
			auto item = items.front ();
			items.pop ();
			if (searchConditionFn (*item)) {
				return true;
			} else if (item->GetParent () != nullptr) {
				items.push (item->GetParent ());
			} else {
				return false;
			}
		}
	} 
	return false;
}


template<class Type>
bool	ArrayBasedTree<Type>::HasChildWithCondition (const Int32 fromIndex, const SearchConditionFunction& searchConditionFn) const
{
	Int32 internalIndex = GetInternalIndex (fromIndex);
	if (DBVERIFY_GUID (internalIndex >= 0 && static_cast<UIndex> (internalIndex) < items.GetSize (), "{060C303B-1060-4305-8205-9AE69B890D5A}")) {
		return HasChildWithCondition (items[internalIndex], searchConditionFn);
	} else {
		return false;
	}
}


template<class Type>
bool	ArrayBasedTree<Type>::HasChildWithCondition (const Node& fromItem, const SearchConditionFunction& searchConditionFn) const
{
	std::queue<const Node*> items;

	items.push (&fromItem);

	while (!items.empty ()) {
		auto item = items.front ();
		items.pop ();
		if (item->GetParent () != nullptr) {
			if (searchConditionFn (*item)) {
				return true;
			}
		}
		if (item->firstChild != nullptr) {
			items.push (item->firstChild);
			auto nextItem = item->firstChild->next;
			while (nextItem != nullptr) {
				items.push (nextItem);
				nextItem = nextItem->next;
			}
		}
	}

	return false;
}


template<class Type>
USize ArrayBasedTree<Type>::GetInternalContainerSize () const
{
	return items.GetSize ();
}


template<class Type>
void ArrayBasedTree<Type>::UnchainTreeItem (Node* parent, Node* workItem)
{
	if (DBERROR (parent->numChildren == 0)) {
		return;
	} else if (parent->numChildren == 1) {
		parent->firstChild = parent->lastChild = nullptr;
	} else {
		Node* prevItem = nullptr;
		Node* itemPtr = parent->firstChild;
		while (DBVERIFY (itemPtr != nullptr)) {
			if (itemPtr == workItem) {
				if (itemPtr == parent->firstChild) {
					parent->firstChild = itemPtr->next;
					itemPtr->next->previous = nullptr;
				} else if (itemPtr == parent->lastChild) {
					prevItem->next = nullptr;
					parent->lastChild = prevItem;
				} else {
					prevItem->next = itemPtr->next;
					itemPtr->next->previous = prevItem;
				}
				break;
			}
			prevItem = itemPtr;
			itemPtr = itemPtr->next;
		}
		itemPtr->next = nullptr;
		itemPtr->previous = nullptr;
		itemPtr->parent = nullptr;
	}
	--parent->numChildren;
}


template<class Type>
void ArrayBasedTree<Type>::ChainTreeItem (Node* parentItem, Node* itemToInsert, const Int32 internalIndex)
{
	if (internalIndex == ArrayBasedTreeBase::ItemType::TopItem || internalIndex == ArrayBasedTreeBase::ItemType::BottomItem) {
		if (internalIndex == ArrayBasedTreeBase::ItemType::TopItem) {
			if (parentItem->firstChild != nullptr) {
				parentItem->firstChild->previous = itemToInsert;
				itemToInsert->next = parentItem->firstChild;
			}
		} else if (internalIndex == ArrayBasedTreeBase::ItemType::BottomItem) {
			if (parentItem->lastChild != nullptr) {
				parentItem->lastChild->next = itemToInsert;
				itemToInsert->previous = parentItem->lastChild;
			}
		}
	} else {
		auto successorItem = &items[internalIndex];
		if (DBVERIFY (successorItem->parent == parentItem)) {
			itemToInsert->previous = successorItem->previous;
			itemToInsert->next = successorItem;
			if (successorItem->previous != nullptr) {
				successorItem->previous->next = itemToInsert;
			}
			successorItem->previous = itemToInsert;
		}
	}
	itemToInsert->parent = parentItem;
	if (itemToInsert->next == nullptr) {
		parentItem->lastChild = itemToInsert;
	}
	if (itemToInsert->previous == nullptr) {
		parentItem->firstChild = itemToInsert;
	}
	parentItem->numChildren++;
}


}	// namespace

#endif //GS_UD_ARRAYBASEDTREE_HPP
