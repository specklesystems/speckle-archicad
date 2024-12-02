
// *****************************************************************************
//
//                                Class BiHashTable
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined BIHASHTABLE_HPP
#define BIHASHTABLE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "AssociativeContainer.hpp"
#include "TypeTraits.hpp"
#include "GSAssert.hpp"
#include "HashTable.hpp"
#include "ForwardContainerIterator.hpp"
#include "AddInserter.hpp"
#include "Inserter.hpp"

// ------------------------------ Predeclarations ------------------------------

namespace GS {

class ObjectState;

template <class Type1, class Type2>
GSErrCode	StorePair (ObjectState& os, const Type1& first, const Type2& second);

}

// ============================== Class BiHashTable ==============================

namespace GS {

class GSROOT_DLL_EXPORT BiHashTablePrivate {
public:
	static GS::ClassInfo	classInfo;	// BiHashTable's private classInfo
};


template <class LeftKey, class RightKey>
class GS_EXPORT_TYPEINFO BiHashTableBase : public AssociativeContainer<LeftKey, RightKey> {
public:
	BiHashTableBase ()
	{
		static_assert (GS::HasGenerateHashValue<LeftKey>,  "'LeftKey' has no GenerateHashValue ().");
		static_assert (GS::HasGenerateHashValue<RightKey>, "'RightKey' has no GenerateHashValue ().");

		static_assert (GS::HasOperatorEquals<LeftKey>,  "'LeftKey' has no operator== ().");
		static_assert (GS::HasOperatorEquals<RightKey>, "'RightKey' has no operator== ().");
	}
};


template <class LeftKey, class RightKey>
class BiHashTable : public BiHashTableBase<LeftKey, RightKey> {
	using EnableLeft = GS::Conditional<GS::IsSame<LeftKey, RightKey>, int, bool>;
	using EnableRight = GS::Conditional<GS::IsSame<LeftKey, RightKey>, bool, int>;

private:
	HashTable<LeftKey, RightKey>  leftTable;
	HashTable<RightKey, LeftKey>  rightTable;

	// Iterator Adapter

	struct ConstCurrentPairAdapter {
		const LeftKey*		leftKey;
		const RightKey*		rightKey;

		ConstCurrentPairAdapter ():													leftKey (nullptr), rightKey (nullptr)	 {}
		ConstCurrentPairAdapter (const LeftKey* leftKey, const RightKey* rightKey):	leftKey (leftKey), rightKey (rightKey)   {}
	};

	struct HashTableConstIteratorAdapter {
		mutable typename HashTable<LeftKey, RightKey>::ConstIterator	currentIterator;
		mutable typename BiHashTable::ConstCurrentPairAdapter			currentIteratorAdapter;

		explicit HashTableConstIteratorAdapter (const typename HashTable<LeftKey, RightKey>::ConstIterator& initialIterator): currentIterator (initialIterator) {}
	};

	void							Increment  (HashTableConstIteratorAdapter& state) const;
	bool							IsEqual    (const HashTableConstIteratorAdapter& state1, const HashTableConstIteratorAdapter& state2) const;
	bool							IsEnd      (const HashTableConstIteratorAdapter& state) const;
	const ConstCurrentPairAdapter&	GetCurrent (const HashTableConstIteratorAdapter& state) const;

	friend class ConstForwardContainerIterator<BiHashTable, HashTableConstIteratorAdapter, ConstCurrentPairAdapter>;

public:

	typedef ConstForwardContainerIterator<BiHashTable, HashTableConstIteratorAdapter, ConstCurrentPairAdapter>	ConstIterator;
	typedef typename HashTable<LeftKey, RightKey>::KeyConversionEnumerator										LeftKeyConversionEnumerator;
	typedef typename HashTable<RightKey, LeftKey>::KeyConversionEnumerator										RightKeyConversionEnumerator;

		// Constructors

	BiHashTable ();
	explicit BiHashTable (float averageSeekFactorLimit, float minFillFactor = 0.0);
	BiHashTable (std::initializer_list<Pair<LeftKey, RightKey>> source);
	BiHashTable (const BiHashTable& source);
	BiHashTable (BiHashTable&& source);
	BiHashTable (const BiHashTable&&) = delete;
   ~BiHashTable ();
	BiHashTable&	operator= (const BiHashTable& source);
	BiHashTable&	operator= (BiHashTable&& source);

	void	Move (BiHashTable& source);

		// LeftKey access

	template <bool = EnableLeft ()> const LeftKey&	operator[] (const RightKey& rightKey) const gs_lifebound;

	template <bool = EnableLeft ()> const LeftKey&	Get (const RightKey& rightKey) const gs_lifebound;
	template <bool = EnableLeft ()> bool			Get (const RightKey& rightKey, LeftKey* leftKey) const;
	template <bool = EnableLeft ()> bool			Get (const RightKey& rightKey, LeftKey** leftKey);
	template <bool = EnableLeft ()> bool			Get (const RightKey& rightKey, const LeftKey** leftKey) const;

	template <bool = EnableLeft ()> const LeftKey*	GetPtr (const RightKey& rightKey) const gs_lifebound;

		// Specified LeftKey access

	const LeftKey&	GetLeft (const RightKey& rightKey) const gs_lifebound;
	bool			GetLeft (const RightKey& rightKey, LeftKey* leftKey) const;
	bool			GetLeft (const RightKey& rightKey, const LeftKey** leftKey) const;

	const LeftKey*	GetLeftPtr (const RightKey& rightKey) const gs_lifebound;

		// RightKey access

	template <int = EnableRight ()> const RightKey&	operator[] (const LeftKey& leftKey) const gs_lifebound;

	template <int = EnableRight ()> const RightKey&	Get (const LeftKey& leftKey) const gs_lifebound;
	template <int = EnableRight ()> bool			Get (const LeftKey& leftKey, RightKey* rightKey) const;
	template <int = EnableRight ()> bool			Get (const LeftKey& leftKey, RightKey** rightKey);
	template <int = EnableRight ()> bool			Get (const LeftKey& leftKey, const RightKey** rightKey) const;

	template <int = EnableRight ()> const RightKey*	GetPtr (const LeftKey& leftKey) const gs_lifebound;

		// Specified RightKey access

	const RightKey&	GetRight (const LeftKey& leftKey) const gs_lifebound;
	bool			GetRight (const LeftKey& leftKey, RightKey* rightKey) const;
	bool			GetRight (const LeftKey& leftKey, const RightKey** rightKey) const;

	const RightKey*	GetRightPtr (const LeftKey& leftKey) const gs_lifebound;

		// Content management

	bool			Add	(const LeftKey& leftKey, const RightKey& rightKey);
	bool			Add (const Pair<LeftKey, RightKey>& pair);
	void			Put	(const LeftKey& leftKey, const RightKey& rightKey);

	void			Set (const LeftKey& leftKey, const RightKey& rightKey);

	template <bool = EnableLeft ()>	 bool	Delete (const LeftKey& leftKey);
	template <int = EnableRight ()>  bool	Delete (const RightKey& rightKey);

	bool			DeleteLeft (const LeftKey& leftKey);
	bool			DeleteRight (const RightKey& rightKey);

	void			Clear (void);

	void			Swap (BiHashTable& rightOp);

	template <bool = EnableLeft ()>	void	SetEquivalent (const LeftKey& oldKey, const LeftKey& newKey);
	template <int = EnableRight ()> void	SetEquivalent (const RightKey& oldKey, const RightKey& newKey);

	void			SetEquivalentLeftKey (const LeftKey& oldKey, const LeftKey& newKey);
	void			SetEquivalentRightKey (const RightKey& oldKey, const RightKey& newKey);

	USize			GetSize (void) const;
	bool			IsEmpty (void) const;

	ConstIterator	Enumerate (void) const;
	ConstIterator	Begin (void) const;
	ConstIterator	End (void) const;

		// Range-based for loop support

	auto&			AsConst (void) const gs_lifebound;

		// Conversion

	LeftKeyConversionEnumerator		ConvertLeftKeys (void) const;
	RightKeyConversionEnumerator	ConvertRightKeys (void) const;

		// Content query

	template <bool = EnableLeft ()>	 bool	Contains (const LeftKey& leftKey) const;
	template <int = EnableRight ()>  bool	Contains (const RightKey& rightKey) const;

	bool			ContainsLeftKey  (const LeftKey& leftKey) const;
	bool			ContainsRightKey (const RightKey& rightKey) const;

	bool			operator== (const BiHashTable& rightOp) const;
	bool			operator!= (const BiHashTable& rightOp) const;

		// I/O

	GSErrCode		Read  (IChannel& ic);
	GSErrCode		Write (OChannel& oc) const;

		// Performance tuning

	void			EnsureCapacity (USize minCapacity);

	// Friend declarations

	friend GSErrCode 	Store (ObjectState& os, const typename BiHashTable<LeftKey, RightKey>::ConstCurrentPairAdapter& pair)
	{
		return StorePair (os, *pair.leftKey, *pair.rightKey);
	}

	friend GSErrCode 	Restore (const ObjectState& os, typename BiHashTable<LeftKey, RightKey>::ConstCurrentPairAdapter& pair);    // Not used - needed for ObjectStateTraits
};


// === BiHashTable methods ===============================================================================================

template <class LeftKey, class RightKey>
BiHashTable<LeftKey, RightKey>::BiHashTable ():
	BiHashTable (0.0, 0.0)
{
}


template <class LeftKey, class RightKey>
BiHashTable<LeftKey, RightKey>::BiHashTable (float averageSeekFactorLimit, float minFillFactor /*= 0.0*/):
	leftTable (averageSeekFactorLimit, minFillFactor),
	rightTable (averageSeekFactorLimit, minFillFactor)
{
}


template <class LeftKey, class RightKey>
BiHashTable<LeftKey, RightKey>::BiHashTable (const BiHashTable& source)
{
	NULL_REF_CHECK (source);

	leftTable = source.leftTable;
	rightTable = source.rightTable;
}


template <class LeftKey, class RightKey>
BiHashTable<LeftKey, RightKey>::BiHashTable (std::initializer_list<Pair<LeftKey, RightKey>> source):
	BiHashTable ()
{
	EnsureCapacity (USize (source.size ()));

	for (const auto& pair : source)
		Add (pair.first, pair.second);
}


template <class LeftKey, class RightKey>
BiHashTable<LeftKey, RightKey>::BiHashTable (BiHashTable&& source):
	BiHashTable ()
{
	Move (source);
}


template <class LeftKey, class RightKey>
BiHashTable<LeftKey, RightKey>::~BiHashTable ()
{
}


template <class LeftKey, class RightKey>
BiHashTable<LeftKey, RightKey>&		BiHashTable<LeftKey, RightKey>::operator= (const BiHashTable& source)
{
	NULL_REF_CHECK (source);

	BiHashTable copy = source;
	leftTable.Move (copy.leftTable);
	rightTable.Move (copy.rightTable);

	return *this;
}


template <class LeftKey, class RightKey>
BiHashTable<LeftKey, RightKey>&		BiHashTable<LeftKey, RightKey>::operator= (BiHashTable&& source)
{
	NULL_REF_CHECK (source);

	Move (source);

	return *this;
}


template <class LeftKey, class RightKey>
void	BiHashTable<LeftKey, RightKey>::Move (BiHashTable& source)
{
	if (DBERROR (&source == this))
		return;

	leftTable.Move (source.leftTable);
	rightTable.Move (source.rightTable);

	source.Clear ();
}


template <class LeftKey, class RightKey>
template <bool /* = EnableLeft () */>
const LeftKey&	BiHashTable<LeftKey, RightKey>::operator[] (const RightKey& rightKey) const
{
	return rightTable[rightKey];
}


template <class LeftKey, class RightKey>
template <bool /* = EnableLeft () */>
const LeftKey&	BiHashTable<LeftKey, RightKey>::Get (const RightKey& rightKey) const
{
	return rightTable.Get (rightKey);
}


template <class LeftKey, class RightKey>
template <bool /* = EnableLeft () */>
bool	BiHashTable<LeftKey, RightKey>::Get (const RightKey& rightKey, LeftKey* leftKey) const
{
	return rightTable.Get (rightKey, leftKey);
}


template <class LeftKey, class RightKey>
template <bool /* = EnableLeft () */>
bool	BiHashTable<LeftKey, RightKey>::Get (const RightKey& rightKey, const LeftKey** leftKey) const
{
	return rightTable.Get (rightKey, leftKey);
}


template <class LeftKey, class RightKey>
template <bool /* = EnableLeft () */>
const LeftKey*	BiHashTable<LeftKey, RightKey>::GetPtr (const RightKey& rightKey) const
{
	return rightTable.GetPtr (rightKey);
}


template <class LeftKey, class RightKey>
const LeftKey&	BiHashTable<LeftKey, RightKey>::GetLeft (const RightKey& rightKey) const
{
	return rightTable.Get (rightKey);
}


template <class LeftKey, class RightKey>
bool	BiHashTable<LeftKey, RightKey>::GetLeft (const RightKey& rightKey, LeftKey* leftKey) const
{
	return rightTable.Get (rightKey, leftKey);
}


template <class LeftKey, class RightKey>
bool	BiHashTable<LeftKey, RightKey>::GetLeft (const RightKey& rightKey, const LeftKey** leftKey) const
{
	return rightTable.Get (rightKey, leftKey);
}


template <class LeftKey, class RightKey>
const LeftKey*	BiHashTable<LeftKey, RightKey>::GetLeftPtr (const RightKey& rightKey) const
{
	return rightTable.GetPtr (rightKey);
}


template <class LeftKey, class RightKey>
template <int /* = EnableRight () */>
const RightKey&	BiHashTable<LeftKey, RightKey>::operator[] (const LeftKey& leftKey) const
{
	return leftTable[leftKey];
}


template <class LeftKey, class RightKey>
template <int /* = EnableRight () */>
const RightKey&	BiHashTable<LeftKey, RightKey>::Get (const LeftKey& leftKey) const
{
	return leftTable.Get (leftKey);
}


template <class LeftKey, class RightKey>
template <int /* = EnableRight () */>
bool	BiHashTable<LeftKey, RightKey>::Get (const LeftKey& leftKey, RightKey* rightKey) const
{
	return leftTable.Get (leftKey, rightKey);
}


template <class LeftKey, class RightKey>
template <int /* = EnableRight () */>
bool	BiHashTable<LeftKey, RightKey>::Get (const LeftKey& leftKey, const RightKey** rightKey) const
{
	return leftTable.Get (leftKey, rightKey);
}


template <class LeftKey, class RightKey>
template <int /* = EnableRight () */>
const RightKey*	BiHashTable<LeftKey, RightKey>::GetPtr (const LeftKey& leftKey) const
{
	return leftTable.GetPtr (leftKey);
}


template <class LeftKey, class RightKey>
const RightKey&	BiHashTable<LeftKey, RightKey>::GetRight (const LeftKey& leftKey) const
{
	return leftTable.Get (leftKey);
}


template <class LeftKey, class RightKey>
bool	BiHashTable<LeftKey, RightKey>::GetRight (const LeftKey& leftKey, RightKey* rightKey) const
{
	return leftTable.Get (leftKey, rightKey);
}


template <class LeftKey, class RightKey>
bool	BiHashTable<LeftKey, RightKey>::GetRight (const LeftKey& leftKey, const RightKey** rightKey) const
{
	return leftTable.Get (leftKey, rightKey);
}


template <class LeftKey, class RightKey>
const RightKey*	BiHashTable<LeftKey, RightKey>::GetRightPtr (const LeftKey& leftKey) const
{
	return leftTable.GetPtr (leftKey);
}


template <class LeftKey, class RightKey>
void		BiHashTable<LeftKey, RightKey>::Set (const LeftKey& leftKey, const RightKey& rightKey)
{
	bool isValid = rightTable.Delete (leftTable[leftKey]);
	DBVERIFY (isValid);

	leftTable.Set (leftKey, rightKey);

	isValid = rightTable.Add (rightKey, leftKey);
	DBVERIFY (isValid);
}


template <class LeftKey, class RightKey>
bool	BiHashTable<LeftKey, RightKey>::Add (const LeftKey& leftKey, const RightKey& rightKey)
{
	if (!rightTable.Add (rightKey, leftKey))
		return false;

	if (leftTable.Add (leftKey, rightKey))
		return true;

	rightTable.Delete (rightKey);
	return false;
}


template <class LeftKey, class RightKey>
bool GS::BiHashTable<LeftKey, RightKey>::Add (const Pair<LeftKey, RightKey>& pair)
{
	return Add (pair.first, pair.second);
}


template <class LeftKey, class RightKey>
void	BiHashTable<LeftKey, RightKey>::Put (const LeftKey& leftKey, const RightKey& rightKey)
{
	NULL_REF_CHECK (leftKey);
	NULL_REF_CHECK (rightKey);

	LeftKey* leftKeyPtr = nullptr;
	RightKey* rightKeyPtr = nullptr;

	if (leftTable.Get (leftKey, &rightKeyPtr)) {
		rightTable.Delete (*rightKeyPtr);
		*rightKeyPtr = rightKey;
	}

	if (rightTable.Get (rightKey, &leftKeyPtr)) {
		leftTable.Delete (*leftKeyPtr);
		*leftKeyPtr = leftKey;
	}

	rightTable.Add (rightKey, leftKey);
	leftTable.Add (leftKey, rightKey);
}


template <class LeftKey, class RightKey>
template <bool /* = EnableLeft () */>
bool	BiHashTable<LeftKey, RightKey>::Delete (const LeftKey& leftKey)
{
	return DeleteLeft (leftKey);
}


template <class LeftKey, class RightKey>
template <int /* = EnableRight () */>
bool	BiHashTable<LeftKey, RightKey>::Delete (const RightKey& rightKey)
{
	return DeleteRight (rightKey);
}


template <class LeftKey, class RightKey>
bool	BiHashTable<LeftKey, RightKey>::DeleteLeft (const LeftKey& leftKey)
{
	RightKey* rightKeyPtr = nullptr;
	if (leftTable.Get (leftKey, &rightKeyPtr)) {
		DBVERIFY (rightTable.Delete (*rightKeyPtr));
		DBVERIFY (leftTable.Delete (leftKey));
		return true;
	}

	return false;
}


template <class LeftKey, class RightKey>
bool	BiHashTable<LeftKey, RightKey>::DeleteRight (const RightKey& rightKey)
{
	LeftKey* leftKeyPtr = nullptr;
	if (rightTable.Get (rightKey, &leftKeyPtr)) {
		DBVERIFY (leftTable.Delete (*leftKeyPtr));
		DBVERIFY (rightTable.Delete (rightKey));
		return true;
	}

	return false;
}


template <class LeftKey, class RightKey>
void	BiHashTable<LeftKey, RightKey>::Clear (void)
{
	leftTable.Clear ();
	rightTable.Clear ();
}


template <class LeftKey, class RightKey>
void	BiHashTable<LeftKey, RightKey>::Swap (BiHashTable& rightOp)
{
	leftTable.Swap (rightOp.leftTable);
	rightTable.Swap (rightOp.rightTable);
}


template <class LeftKey, class RightKey>
template <bool /* = EnableLeft () */>
void	BiHashTable<LeftKey, RightKey>::SetEquivalent (const LeftKey& oldKey, const LeftKey& newKey)
{
	SetEquivalentLeftKey (oldKey, newKey);
}


template <class LeftKey, class RightKey>
template <int /* = EnableRight () */>
void	BiHashTable<LeftKey, RightKey>::SetEquivalent (const RightKey& oldKey, const RightKey& newKey)
{
	SetEquivalentRightKey (oldKey, newKey);
}


template <class LeftKey, class RightKey>
void	BiHashTable<LeftKey, RightKey>::SetEquivalentLeftKey (const LeftKey& oldKey, const LeftKey& newKey)
{
	leftTable.SetEquivalentKey (oldKey, newKey);
	rightTable.Get (leftTable[oldKey]) = newKey;
}


template <class LeftKey, class RightKey>
void	BiHashTable<LeftKey, RightKey>::SetEquivalentRightKey (const RightKey& oldKey, const RightKey& newKey)
{
	rightTable.SetEquivalentKey (oldKey, newKey);
	leftTable.Get (rightTable[oldKey]) = newKey;
}


template <class LeftKey, class RightKey>
USize	BiHashTable<LeftKey, RightKey>::GetSize (void) const
{
	return leftTable.GetSize ();
}


template <class LeftKey, class RightKey>
bool		BiHashTable<LeftKey, RightKey>::IsEmpty (void) const
{
	return leftTable.IsEmpty ();
}


template <class LeftKey, class RightKey>
typename BiHashTable<LeftKey, RightKey>::ConstIterator		BiHashTable<LeftKey, RightKey>::Enumerate (void) const
{
	return Begin ();
}


template <class LeftKey, class RightKey>
typename BiHashTable<LeftKey, RightKey>::ConstIterator		BiHashTable<LeftKey, RightKey>::Begin (void) const
{
	return ConstIterator (*this, HashTableConstIteratorAdapter (leftTable.Begin ()));
}


template <class LeftKey, class RightKey>
typename BiHashTable<LeftKey, RightKey>::ConstIterator		BiHashTable<LeftKey, RightKey>::End (void) const
{
	return ConstIterator (*this, HashTableConstIteratorAdapter (leftTable.End ()));
}


template <class LeftKey, class RightKey>
auto&	BiHashTable<LeftKey, RightKey>::AsConst (void) const
{
	using ConstValueType = typename BiHashTable<LeftKey, RightKey>::template MakeConstPtr<RightKey>::ConstType;

	return reinterpret_cast<const BiHashTable<LeftKey, ConstValueType>&> (*this);
}


template <class LeftKey, class RightKey>
typename BiHashTable<LeftKey, RightKey>::LeftKeyConversionEnumerator		BiHashTable<LeftKey, RightKey>::ConvertLeftKeys (void) const
{
	return LeftKeyConversionEnumerator (leftTable);
}


template <class LeftKey, class RightKey>
typename BiHashTable<LeftKey, RightKey>::RightKeyConversionEnumerator		BiHashTable<LeftKey, RightKey>::ConvertRightKeys (void) const
{
	return RightKeyConversionEnumerator (rightTable);
}


template <class LeftKey, class RightKey>
template <bool /* = EnableLeft () */>
bool	BiHashTable<LeftKey, RightKey>::Contains (const LeftKey& leftKey) const
{
	return leftTable.ContainsKey (leftKey);
}


template <class LeftKey, class RightKey>
template <int /* = EnableRight () */>
bool	BiHashTable<LeftKey, RightKey>::Contains (const RightKey& rightKey) const
{
	return rightTable.ContainsKey (rightKey);
}


template <class LeftKey, class RightKey>
bool	BiHashTable<LeftKey, RightKey>::ContainsLeftKey (const LeftKey& leftKey) const
{
	return leftTable.ContainsKey (leftKey);
}


template <class LeftKey, class RightKey>
bool	BiHashTable<LeftKey, RightKey>::ContainsRightKey (const RightKey& rightKey) const
{
	return rightTable.ContainsKey (rightKey);
}


template <class LeftKey, class RightKey>
bool	BiHashTable<LeftKey, RightKey>::operator== (const BiHashTable& rightOp) const
{
	return leftTable == rightOp.leftTable;
}


template <class LeftKey, class RightKey>
bool	BiHashTable<LeftKey, RightKey>::operator!= (const BiHashTable& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	return !operator== (rightOp);
}


template <class LeftKey, class RightKey>
GSErrCode	BiHashTable<LeftKey, RightKey>::Read (IChannel& ic)
{
	NULL_REF_CHECK (ic);

	Clear ();

	GS::InputFrame frame (ic, BiHashTablePrivate::classInfo);
	if (frame.GetStatus () != NoError)
		return frame.GetStatus ();

	HashTable<LeftKey, RightKey> source;
	GSErrCode err = source.Read (ic);
	if (DBERROR (err != NoError))
		return err;

	for (const auto& entry : source) {
		if (!Add (entry.key, entry.value))
			return Error;
	}

	return NoError;
}


template <class LeftKey, class RightKey>
GSErrCode	BiHashTable<LeftKey, RightKey>::Write (OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	GS::OutputFrame frame (oc, BiHashTablePrivate::classInfo);

	return leftTable.Write (oc);
}


template <class LeftKey, class RightKey>
void	BiHashTable<LeftKey, RightKey>::EnsureCapacity (USize minCapacity)
{
	leftTable.EnsureCapacity (minCapacity);
	rightTable.EnsureCapacity (minCapacity);
}


template <class LeftKey, class RightKey>
void			BiHashTable<LeftKey, RightKey>::Increment (HashTableConstIteratorAdapter& state) const
{
	state.currentIterator++;
}


template <class LeftKey, class RightKey>
bool			BiHashTable<LeftKey, RightKey>::IsEqual (const HashTableConstIteratorAdapter& state1, const HashTableConstIteratorAdapter& state2) const
{
	return state1.currentIterator == state2.currentIterator;
}


template <class LeftKey, class RightKey>
bool			BiHashTable<LeftKey, RightKey>::IsEnd (const HashTableConstIteratorAdapter& state) const
{
	return IsEqual (state, HashTableConstIteratorAdapter (leftTable.End ()));
}


template <class LeftKey, class RightKey>
const typename BiHashTable<LeftKey, RightKey>::ConstCurrentPairAdapter&	BiHashTable<LeftKey, RightKey>::GetCurrent (const HashTableConstIteratorAdapter& state) const
{
	state.currentIteratorAdapter.leftKey = &state.currentIterator->key;
	state.currentIteratorAdapter.rightKey = &state.currentIterator->value;

	return state.currentIteratorAdapter;
}


// === Global functions ================================================================================================


template <class LeftKey, class RightKey>
auto		begin (const BiHashTable<LeftKey, RightKey>& biHashTable)
{
	return biHashTable.Begin ();
}


template <class LeftKey, class RightKey>
auto		end (const BiHashTable<LeftKey, RightKey>& biHashTable)
{
	return biHashTable.End ();
}


template <class LeftKey, class RightKey>
auto		GetInserter (BiHashTable<LeftKey, RightKey>& biHashTable)
{
	return AddInserter<BiHashTable<LeftKey, RightKey>> (&biHashTable);
}


}	// namespace GS


#endif
