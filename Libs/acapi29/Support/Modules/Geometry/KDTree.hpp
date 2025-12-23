// *********************************************************************************************************************
// Description:		KD-Tree class
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	PP
//
// SG compatible
// *********************************************************************************************************************

#if !defined (KDTREE_HPP)
#define KDTREE_HPP

#pragma once


// --- Includes	--------------------------------------------------------------------------------------------------------
#include	"Definitions.hpp"

#include	"HashTable.hpp"
#include	"SmallObj.hpp"
#include	"Algorithms.hpp"
#include	"AssociativeContainer.hpp"

#include	"KDTreeTypes.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

namespace Geometry {

namespace Private {

// this class cannot be a member class of KDTree because of compiler issues:

template <class ElemType>
class	KDTreeHashTableElemWrapper
{
	public:
						KDTreeHashTableElemWrapper (void) : m_elem (nullptr)				{ }
						KDTreeHashTableElemWrapper (const ElemType *elem) : m_elem (elem)	{ }
		bool			operator == (const KDTreeHashTableElemWrapper& rOp) const			{ return *m_elem == *rOp.m_elem; }

		ULong			GenerateHashValue () const											{ return GS::CalculateHashValue (*m_elem); }
	private:

		const ElemType*	m_elem;
};

}	// namespace Private

template<typename TreeType, KDTreeStatistics StatisticsMode>
class KDTreeStatisticsData;


template<typename TreeType>
class KDTreeStatisticsData<TreeType, KDTreeStatisticsDisabled> {
public:
	class NodeBaseData {
	public:
		NodeBaseData (TreeType* /*ownerTree*/) {}
		void LeafFound () const		{}
		void NodeAccessed () const	{}
		void LeafAccessed () const	{}
	};

	void IncQueryCount () const	{}
	void Reset () const			{}
	void Print () const			{}
};


template<typename TreeType>
class KDTreeStatisticsData<TreeType, KDTreeStatisticsEnabled>
{
	mutable UInt32			m_visitedNodeCount;
	mutable UInt32			m_visitedLeafCount;
	mutable UInt32			m_foundLeafCount;
	mutable UInt32			m_queryCount;

public:
	class NodeBaseData {
	private:
		TreeType* ownerTree;
	public:
		NodeBaseData (TreeType* ownerTree) : ownerTree (ownerTree) {}

		void LeafFound () const		{ ++(ownerTree->m_statistics.m_foundLeafCount); }
		void NodeAccessed () const	{ ++(ownerTree->m_statistics.m_visitedNodeCount); }
		void LeafAccessed () const	{ ++(ownerTree->m_statistics.m_visitedLeafCount); }
	};

	KDTreeStatisticsData () : m_visitedNodeCount (0), m_visitedLeafCount (0), m_foundLeafCount (0), m_queryCount (0) {}

	void IncQueryCount () const	{ ++m_queryCount; }

	void Reset () const
	{
		m_visitedNodeCount = m_visitedLeafCount = m_foundLeafCount = m_queryCount = 0;
	}

	void Print () const
	{
		DBPrintf ("visited nodes: %f, visited leaves: %f, found leaves: %f, queries: %f\n",
			(double)m_visitedNodeCount, (double)m_visitedLeafCount, (double)m_foundLeafCount, (double)m_queryCount);
		DBPrintf ("avg. visited nodes: %f, avg. visited leaves: %f, avg. found leaves: %f\n",
			(double)m_visitedNodeCount / (double)m_queryCount, (double)m_visitedLeafCount / (double)m_queryCount, (double)m_foundLeafCount / (double)m_queryCount);
	}
};


template <typename ElemType, typename LeafType, KDTreeElemSetType ElemSetType>
class ElemLeafMap;

template <typename ElemType, typename LeafType>
class ElemLeafMap<ElemType, LeafType, KDTreeElemSet>
{
private:
	GS::HashTable<Private::KDTreeHashTableElemWrapper<ElemType>, LeafType *>	m_elemsInLeaves;
public:
	void Add (LeafType* leaf)
	{
		DBVERIFY (m_elemsInLeaves.Add (&leaf->GetAssoc ().GetElem (), leaf));
	}

	void Delete (LeafType* leaf)
	{
		DBVERIFY (m_elemsInLeaves.Delete (&leaf->GetAssoc ().GetElem ()));
	}

	bool Get (const ElemType& elem, LeafType** leaf) const
	{
		return m_elemsInLeaves.Get (&elem, leaf);
	}

	bool Check (const LeafType* leaf) const
	{
		return m_elemsInLeaves [&leaf->GetAssoc ().GetElem ()] == leaf;
	}

	void Clear ()
	{
		m_elemsInLeaves.Clear ();
	}

	void EnsureCapacity (USize capacity)
	{
		m_elemsInLeaves.EnsureCapacity (capacity);
	}

	bool CanAddDefault () const
	{
		ElemType elem;
		return !m_elemsInLeaves.ContainsKey (&elem);
	}

	bool CanAdd (const ElemType& elem) const
	{
		return !m_elemsInLeaves.ContainsKey (&elem);
	}
};


template <typename ElemType, typename LeafType>
class ElemLeafMap<ElemType, LeafType, KDTreeElemMultiset>
{
public:
	void Add (LeafType* /*leaf*/) {}

	void Delete (LeafType* /*leaf*/) {}

//	operation not supported
// 	bool Get (const ElemType& elem, LeafType** /*leaf*/) const	{}

	bool Check (const LeafType* /*leaf*/) const		{ return true; }

	void Clear ()									{}
	void EnsureCapacity (USize /*capacity*/)		{}

	bool CanAddDefault () const						{ return true; }
	bool CanAdd (const ElemType& /*elem*/) const	{ return true; }
};


enum LeafCount {
	LeafCountZero,
	LeafCountOne,
	LeafCountMoreThanOne
};

// KDTreeElemSet can only have const iterators
template<typename TreeType, KDTreeElemSetType ElemSetType>
struct KDTreeIterator;

template<typename TreeType>
struct KDTreeIterator<TreeType, KDTreeElemSet> {
	typedef GS::ConstGeneralForwardContainerIterator <TreeType, typename TreeType::ValueIteratorState, typename TreeType::AssociatedValueType>	IteratorType;
	typedef typename TreeType::ConstPairIteratorState																					PairIteratorStateType;
	typedef GS::ConstGeneralForwardContainerIterator <TreeType, PairIteratorStateType, typename TreeType::ConstAssoc>					PairIteratorType;

	typedef const typename TreeType::AssociatedValueType*																							NotConstValuePtrType;
};

template<typename TreeType>
struct KDTreeIterator<TreeType, KDTreeElemMultiset> {
	typedef GS::GeneralForwardContainerIterator <TreeType, typename TreeType::ValueIteratorState, typename TreeType::AssociatedValueType>			IteratorType;
	typedef typename TreeType::PairIteratorState																						PairIteratorStateType;
	typedef GS::GeneralForwardContainerIterator <TreeType, PairIteratorStateType, typename TreeType::Assoc>								PairIteratorType;

	typedef typename TreeType::AssociatedValueType*																								NotConstValuePtrType;
};


template<typename ValueType, KDTreeElemSetType ElemSetType>
struct KDTreeValuePtr;

template<typename ValueType>
struct KDTreeValuePtr<ValueType, KDTreeElemSet>
{
	typedef const ValueType* Type;
};

template<typename ValueType>
struct KDTreeValuePtr<ValueType, KDTreeElemMultiset>
{
	typedef ValueType* Type;
};


template <typename TreeType, KDTreeElemSetType ElemSetType, bool isConst>
struct QueryTypes;

template <typename TreeType, KDTreeElemSetType ElemSetType>
struct QueryTypes <TreeType, ElemSetType, true>
{
	typedef const TreeType						Tree;
	typedef const typename TreeType::NodeBase	NodeBase;
	typedef const typename TreeType::Node		Node;
	typedef const typename TreeType::Leaf		Leaf;
	typedef const typename TreeType::AssociatedValueType& ResultType;
};

template <typename TreeType>
struct QueryTypes <TreeType, KDTreeElemSet, false>
{
	typedef const TreeType						Tree;
	typedef const typename TreeType::NodeBase	NodeBase;
	typedef const typename TreeType::Node		Node;
	typedef const typename TreeType::Leaf		Leaf;
	typedef const typename TreeType::AssociatedValueType& ResultType;
};

template <typename TreeType>
struct QueryTypes <TreeType, KDTreeElemMultiset, false>
{
	typedef TreeType							Tree;
	typedef typename TreeType::NodeBase			NodeBase;
	typedef typename TreeType::Node				Node;
	typedef typename TreeType::Leaf				Leaf;
	typedef typename TreeType::AssociatedValueType&		ResultType;
};

template<typename KeyType>
class KDTreeBounds;

template<typename KeyType, KDTreeNodeBounds NodeBoundsMode>
struct KDTreeNodeIndex;

template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
class KDTree : public GS::AssociativeContainer <KeyType, ElemType>
{
public:
	class Leaf;
	class Allocator
	{
	private:

		friend class KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>;

		FixedAllocator nodeAllocator;
		FixedAllocator leafAllocator;

		void LeaveThread ()
		{
			LEAVETHREAD (nodeAllocator);
			LEAVETHREAD (leafAllocator);
		}

	public:
		Allocator (FixedAllocator::AllocationPolicy allocationPolicy) :
			nodeAllocator (sizeof (Node), AllocatorPurgePolicy::Auto, allocationPolicy),
			leafAllocator (sizeof (Leaf), AllocatorPurgePolicy::Auto, allocationPolicy)
		{
		}
	};

	class StoredElemPtr {
		friend class KDTree;
		const ElemType* ptr;
	public:
		explicit StoredElemPtr (const ElemType* ptr) : ptr (ptr) {}
	};

private:
	static Leaf*	GetLeafPtrFromStoredElemPtr (const StoredElemPtr& elemPtr);

public:
	static const KDTreeElemSetType	ElemSetTypeValue	= ElemSetType;
	static const KDTreeStatistics	StatistcsModeValue	= StatisticsMode;
	static const KDTreeNodeBounds	NodeBoundsModeValue	= NodeBoundsMode;

	/************************************************************************/
	/* Used for secondary comparison in case of equal keys.					*/
	/* By passing a proper comparer as a constructor parameter, 			*/
	/* the ordering of the tree becomes stable, thus platform-independent.	*/
	/************************************************************************/
	typedef std::function<bool (const ElemType&, const ElemType&)> ElemComparer;

	KDTree (Allocator* alloc = nullptr,
			FixedAllocator::AllocationPolicy allocationPolicy = FixedAllocator::FixedSize,
			ElemComparer elemComparer = AllElemsEqualComparer);

	KDTree (ElemComparer elemComparer);

	~KDTree (void);

	static Allocator* CreateAllocator (FixedAllocator::AllocationPolicy allocationPolicy = FixedAllocator::FixedSize);

	typedef typename KDTreeValuePtr<ElemType, ElemSetType>::Type		NotConstValuePtrType;

	StoredElemPtr			Add (const KeyType &key, const ElemType &elem);
	StoredElemPtr			Add (const KeyType &key);
	void					Delete (const StoredElemPtr &elemPtr);
	const KeyType&			GetKey (const StoredElemPtr& elemPtr) const;
	const ElemType*			GetValuePtr (const StoredElemPtr& elemPtr) const;
	NotConstValuePtrType	GetValuePtr (const StoredElemPtr& elemPtr);
	void					UpdateKey (const StoredElemPtr& elemPtr, const KeyType& newKey);
	void					UpdateElem (const StoredElemPtr& elemPtr, const ElemType& newEelem);

	// available only if tree type is KDTreeElemSet
	void			Put (const KeyType &key, const ElemType &elem);
	bool			Delete (const ElemType &elem);
	bool			Contains (const ElemType &elem) const;
	const KeyType&	GetKey (const ElemType &elem) const;
	bool			UpdateKey (const ElemType &elem, const KeyType& newKey);
	bool			UpdateElem (const ElemType &elem, const ElemType& newElem);


	// legacy KDTreeElemSet operations
	void			Insert (const KeyType &key, const ElemType &elem);
	void			Update (const KeyType &key, const ElemType &elem);


	template <typename SourceType>
	void			Rebuild (SourceType& source);

	template <typename ContainerType, typename GetKeyOpType, typename GetValueOpType>
	void			Rebuild (const ContainerType& container, GetKeyOpType& getKey, GetValueOpType& getValue);

	template <typename PairIteratorType>
	void			Rebuild (PairIteratorType source, USize capacityHint);

	USize			GetSize () const;

	void			SetCapacity (USize capacity);

	void			Clear (void);

	template <typename AdapterType>
	void			RangeQuery (const KeyType &keyMin, const KeyType &keyMax, AdapterType &adapter) const;
	template <typename AdapterType>
	void			RangeQuery (const KeyType &keyMin, const KeyType &keyMax, AdapterType &adapter);
	template <typename AdapterType>
	void			OrthogonalRangeQuery (const KeyType &key, AdapterType &adapter) const;
	template <typename AdapterType>
	void			OrthogonalRangeQuery (const KeyType &key, AdapterType &adapter);
	template <typename AdapterType>
	void			InterruptibleOrthogonalRangeQuery (const KeyType &key, AdapterType &adapter) const;
	template <typename AdapterType>
	void			InterruptibleOrthogonalRangeQuery (const KeyType &key, AdapterType &adapter);

	template <typename QueryType>
	void			CustomQuery (QueryType& query) const;

	template <typename QueryType>
	void			CustomQuery (QueryType& query);

	void			Dump (GS::OChannel &ch) const;
	bool			Check () const;

	bool			IsEmpty (void) const;

	void			LeaveThread () { m_allocator->LeaveThread (); }

	void			ForceUpdate ();

	typedef	typename KeyType::DimType	DimType;
	static const short	DimCnt = KeyType::DimCnt;

	class	KeyElemPair
	{
	private:
		friend	Leaf*	KDTree::GetLeafPtrFromStoredElemPtr (const StoredElemPtr&);

		KeyType		m_key;
		ElemType	m_elem;
	public:
		KeyElemPair (const KeyType &key, const ElemType &elem) : m_key (key), m_elem (elem) {}
		KeyElemPair (const KeyType &key) : m_key (key)										 {}
		const KeyType&	GetKey () const			{ return m_key; }
		const ElemType&	GetElem () const		{ return m_elem; }
			  ElemType&	GetElem ()				{ return m_elem; }
		void SetKey (const KeyType& key)		{ m_key = key; }
	};

	class	NodeBase;

	typedef KDTreeBounds<KeyType> Bounds;

	typedef KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode> TreeType;
	typedef typename KDTreeStatisticsData<TreeType, StatisticsMode>::NodeBaseData NodeBaseStatisticsDataType;

	class Node;

	static const UInt64 DeletedLeafBit = 1;
	static const UInt64 UpdatedLeafBit = 2;
	static const UInt64 NodeIndex = 0;

	class NodeBase : public NodeBaseStatisticsDataType
	{
	protected:
		UInt64	m_index;			// 0 -> node
									// if leaf is in the three -> m_index is a search index
									// if it is a deleted leaf in the -> m_index is ((search index) | DeletedLeafBit)		(the search index only uses the first 62 bits of the UInt64)
									// if it is an updated leaf in the -> m_index is ((search index) | UpdatedLeafBit)
									// if it is in the m_leavesToAdd list ->  m_index is (index of the leaf in m_elemsToAdd list) << 32		(the deleted and updated bits are 0)

									// search index (path to the leaf): the (64 - n)th bit of the search index is 0 (1) if the leaf is to the left (right) in the tree on the nth level
									// the max. depth of the tree is 62
	public:

#ifdef CHECKED_VERSION
		Node* node;
		Leaf* leaf;
#endif

		NodeBase (KDTree* ownerTree) : NodeBaseStatisticsDataType (ownerTree), m_index (0)
#ifdef CHECKED_VERSION
			, node (nullptr), leaf (nullptr)
#endif
		{}

		const Node* ToNode () const
		{
			DBASSERT (!IsLeaf ());
			NodeBaseStatisticsDataType::NodeAccessed ();
			return static_cast<const Node*> (this);
		}

		Node* ToNode ()
		{
			DBASSERT (!IsLeaf ());
			NodeBaseStatisticsDataType::NodeAccessed ();
			return static_cast<Node*> (this);
		}

		const Leaf* ToLeaf () const
		{
			DBASSERT (IsLeaf ());
			NodeBaseStatisticsDataType::LeafAccessed ();
			return static_cast<const Leaf*> (this);
		}

		Leaf* ToLeaf ()
		{
			DBASSERT (IsLeaf ());
			NodeBaseStatisticsDataType::LeafAccessed ();
			return static_cast<Leaf*> (this);
		}

		bool	IsLeaf () const					{ return m_index != NodeIndex; }
	};

	typedef KDTreeNodeIndex<KeyType, NodeBoundsMode> NodeIndexType;

	class Node : public NodeBase, public NodeIndexType::NodeData
	{
	private:
		NodeBase*	m_left;
		NodeBase*	m_right;
		USize		m_totalLeafCount;
		DimType		m_separatorVal;

	public:
		Node (KDTree* ownerTree, NodeBase* left, NodeBase* right, USize totalLeafCount, const DimType& separatorVal) :
			NodeBase (ownerTree), m_left (left), m_right (right), m_totalLeafCount (totalLeafCount), m_separatorVal (separatorVal)
		{
#ifdef CHECKED_VERSION
			this->node = this;
#endif
		}

		const NodeBase*		GetLeft () const							{ return m_left; }
		      NodeBase*&	GetLeft ()									{ return m_left; }
		void				SetLeft (NodeBase* left)					{ m_left = left; }
		const NodeBase*		GetRight () const							{ return m_right; }
			  NodeBase*&	GetRight ()									{ return m_right; }
		USize				GetTotalLeafCount () const					{ return m_totalLeafCount; }
		void				SetTotalLeafCount (USize totalLeafCount)	{ m_totalLeafCount = totalLeafCount; }
		const DimType&		GetSeparatorVal () const					{ return m_separatorVal; }
	};

	class Leaf : public NodeBase
	{
	private:
		friend	Leaf*	KDTree::GetLeafPtrFromStoredElemPtr (const StoredElemPtr&);

		KeyElemPair	m_assoc;

	public:
		Leaf (KDTree* ownerTree, const KeyType& key, const ElemType& elem) : NodeBase (ownerTree), m_assoc (key, elem)
		{
#ifdef CHECKED_VERSION
			this->leaf = this;
#endif
		}

		Leaf (KDTree* ownerTree, const KeyType& key) : NodeBase (ownerTree), m_assoc (key)
		{
#ifdef CHECKED_VERSION
			this->leaf = this;
#endif
		}

		const KeyElemPair& GetAssoc () const	{ return m_assoc; }
			  KeyElemPair& GetAssoc ()			{ return m_assoc; }

		void	SetSearchIndex (UInt64 index)	{ this->m_index = index; }
		UInt64	GetSearchIndex () const			{ return this->m_index; }

		void	SetAddListIndex (UInt32 index)
		{
			UInt32* intPtr = reinterpret_cast<UInt32*> (&this->m_index);
			intPtr [0] = 0;			// elems in add list are neither deleted, nor updated
			intPtr [1] = index;
		}
		UInt32	GetAddListIndex () const		{ return reinterpret_cast<const UInt32*> (&this->m_index) [1]; }
	};

	struct AllocatedNode {
		AllocatedNode* next;
		AllocatedNode (AllocatedNode* next) : next (next) {}
	};

	static short	NextDim (short dimIdx) { return (dimIdx == DimCnt - 1 ? 0 : dimIdx + 1); }

	void ResetStatistics () const;
	void PrintStatistics () const;
	void IncQueryCount () const;

private:

	static bool	AllElemsEqualComparer (const ElemType&, const ElemType&) { return false; }

	class	LeafComparer;
	class	SplitComparer;

	typedef	NodeBase*				NodeBasePtr;
	typedef NodeBasePtr*			NodeBasePtrPtr;
	typedef const NodeBase*			ConstNodeBasePtr;
	typedef GS::ArrayFB<Leaf *, 16>	LeafArray;

	typedef typename KDTreeNodeIndex<KeyType, NodeBoundsMode>::StackData NodeBuildStackData;

	KDTree (const KDTree &);				// disabled
	KDTree &operator = (const KDTree &);	// disabled

	Leaf*			CreateLeaf (const KeyType &key, const ElemType& elem);
	Leaf*			CreateLeaf (const KeyType &key);
	Node*			CreateNode (NodeBase *left, NodeBase *right, USize totalLeafCount, const DimType &separatorVal);
	void			DestroyLeaf (Leaf *leaf);
	void			DestroyNode (Node *node);

	template <bool DeleteAll>
	void			RecursiveDeleteTree (NodeBasePtr nb);
	void			RecursiveEnumerateAndUnlinkSubTree (NodeBasePtr& nb);

	template <typename LeafRandomAccesIteratorType>
	void			RecursiveBuildBalancedSubtree (NodeBasePtr &nb, short depth, UInt64 prevIndex, const LeafRandomAccesIteratorType& first, const LeafRandomAccesIteratorType& last, NodeBuildStackData& stackData);

	void			CleanUpDelayedData ();

	void			DeleteLeaf (Leaf* leaf);


	struct UpdateData {
		Leaf**				firstLeafToDelete;
		Leaf**				lastLeafToDelete;
		UInt32				firstLeafToAdd;
		UInt32				lastLeafToAdd;

		UpdateData ()
		{
		}
	};

	class			LeafIndexSmaller;


	void			MoveLeafToAddList (Leaf* leaf, UInt32& lastLeafToAdd);
	void			RemoveLeaf (Leaf* leaf);
	template <LeafCount DeletedLeafCount>
	void			UnlinkLeaf (Leaf* leaf, UInt32& lastLeafToAdd);

	template <LeafCount DeletedLeafCount>
	void			RecursiveUnlinkSubtree (NodeBasePtr& nb, UInt32& lastLeafToAdd);

	template <LeafCount PrevDeletedLeafCount, LeafCount PrevAddedLeafCount>
	void			RecursiveUpdateSwitch (NodeBasePtr& nb, short depth, UInt64 prevIndex, const UpdateData& updateData, NodeBuildStackData& newStackData);

	template <LeafCount DeletedLeafCount, LeafCount AddedLeafCount>
	void			RecursiveUpdate (NodeBasePtr& nb, short depth, UInt64 prevIndex, const UpdateData& updateData, NodeBuildStackData& newStackData);

	template <KDTreeUpdateMode ActUpdateMode>
	void			Update () const;
	void			UpdateNotConst ();

	void			RecursiveDump (const NodeBase *nb, USize currLevel, GS::Array<GS::Array<const NodeBase *> > &lineArray) const;
	bool			RecursiveCheck (const NodeBase* nb, short dimIdx, DimType* min, bool* minSet, DimType* max, bool* maxSet, NodeBuildStackData& stackData) const;

	static UInt64	RightIndex (UInt64 prevIndex, short depth);

	// iterator support

	template<typename TreeType_, KDTreeElemSetType ElemSetType_>
	friend struct KDTreeIterator;

	struct ValueIteratorState {
		static const UInt32		MaxStackSize = 64;

		NodeBase*	nodeStack [MaxStackSize];
		UInt32		stackSize;
		UInt32		nextLeafToAdd;

#ifdef CHECKED_VERSION
		UInt64		initialModificationStamp;
#endif

		explicit ValueIteratorState () : stackSize (0), nextLeafToAdd (0)
#ifdef CHECKED_VERSION
			, initialModificationStamp (0)
#endif
		{}
		explicit ValueIteratorState (const KDTree* tree);

		ValueIteratorState (const ValueIteratorState& src);

	private:
		ValueIteratorState& operator = (const ValueIteratorState& src);
	};

	void					UpdateIteratorState (ValueIteratorState& state) const;

	inline const ElemType&  GetCurrent (const ValueIteratorState& state) const;
	inline ElemType&		GetCurrent (const ValueIteratorState& state);
	inline void				Increment  (ValueIteratorState& state) const;
	inline bool				IsEqual    (const ValueIteratorState& state1, const ValueIteratorState& state2) const;
	inline bool				IsEnd      (const ValueIteratorState& state) const;

	friend class GS::GeneralForwardContainerIterator<KDTree, ValueIteratorState, ElemType>;
	friend class GS::ConstGeneralForwardContainerIterator<KDTree, ValueIteratorState, ElemType>;

	struct ConstAssoc {
		const KeyType*	key;
		const ElemType*	value;

		ConstAssoc (): key (nullptr), value (nullptr) {}
		ConstAssoc (const KeyType* k, const ElemType* v): key (k), value (v) {}
	};

	struct ConstPairIteratorState : public ValueIteratorState {
		mutable ConstAssoc assoc;
		ConstPairIteratorState () {}
		ConstPairIteratorState (const KDTree* tree) : ValueIteratorState (tree) {}
	};

	inline const ConstAssoc&	GetCurrent (const ConstPairIteratorState& state) const;
	inline ConstAssoc&			GetCurrent (const ConstPairIteratorState& state);

	friend class GS::GeneralForwardContainerIterator<KDTree, ConstPairIteratorState, ConstAssoc>;
	friend class GS::ConstGeneralForwardContainerIterator<KDTree, ConstPairIteratorState, ConstAssoc>;

	struct Assoc {
		const KeyType*	key;
		ElemType*	value;

		Assoc (): key (nullptr), value (nullptr) {}
		Assoc (const KeyType* k, ElemType* v): key (k), value (v) {}
	};

	struct PairIteratorState : public ValueIteratorState {
		mutable Assoc assoc;
		PairIteratorState () {}
		PairIteratorState (const KDTree* tree) : ValueIteratorState (tree) {}
	};

	inline const Assoc&			GetCurrent (const PairIteratorState& state) const;
	inline Assoc&				GetCurrent (const PairIteratorState& state);

	friend class GS::GeneralForwardContainerIterator<KDTree, PairIteratorState, Assoc>;
	friend class GS::ConstGeneralForwardContainerIterator<KDTree, PairIteratorState, Assoc>;

public:

	typedef GS::ConstGeneralForwardContainerIterator<KDTree, ValueIteratorState, ElemType> 			ConstIterator;
	typedef typename KDTreeIterator<KDTree, ElemSetType>::IteratorType								Iterator;

	ConstIterator		Enumerate () const;
	Iterator			Enumerate ();
	ConstIterator		LazyEnumerate () const;
	Iterator			LazyEnumerate ();

	typedef GS::ConstGeneralForwardContainerIterator<KDTree, ConstPairIteratorState, ConstAssoc>	ConstPairIterator;
	typedef typename KDTreeIterator<KDTree, ElemSetType>::PairIteratorType							PairIterator;

	ConstPairIterator	EnumeratePairs () const;
	PairIterator		EnumeratePairs () ;
	ConstPairIterator	LazyEnumeratePairs () const;
	PairIterator		LazyEnumeratePairs () ;


	KDTreeStatisticsData<TreeType, StatisticsMode>							m_statistics;

	friend class KDTreeStatisticsData<TreeType, StatisticsMode>;

private:
	bool																	ownAllocator;
	Allocator*																m_allocator;
	NodeBase*																m_root;
	AllocatedNode*															m_allocatedNodeChain;
	ElemComparer															m_leafElemComparer;

	ElemLeafMap <ElemType, Leaf, ElemSetType>								m_elemLeafMap;

	// delayed tree building
	LeafArray																m_leavesToDelete;
	LeafArray																m_leavesToAdd;
	UInt32																	m_updatedLeafCount;
	typedef GS::Pair<Leaf*, UInt64> LeafIndexPair;
	GS::ArrayFB<LeafIndexPair, 16>											m_updatedLeafIndices;
#ifdef CHECKED_VERSION
	UInt64																	m_modificationStamp;

	UInt32																	m_removedLeafCount;
#endif
};


template<typename KeyType>
class KDTreeBounds {
private:
	typedef typename KeyType::DimType DimType;
	static const short DimCnt = KeyType::DimCnt;

	DimType m_min[DimCnt];
	DimType m_max[DimCnt];

public:
	KDTreeBounds ()
	{
		for (short i = 0; i < DimCnt; ++i) {
			m_min[i] = m_max[i] = DimType ();
		}
	}

	KDTreeBounds (const KeyType& key)
	{
		for (short i = 0; i < DimCnt; ++i) {
			m_min[i] = m_max[i] = key.GetDimVal (i);
		}
	}

	void Set (const KDTreeBounds& bl, const KDTreeBounds& br)
	{
		for (short i = 0; i < DimCnt; ++i) {
			m_min[i] = GS::Min (bl.m_min[i], br.m_min[i]);
			m_max[i] = GS::Max (bl.m_max[i], br.m_max[i]);
		}
	}

	bool operator == (const KDTreeBounds& other) const
	{
		for (short i = 0; i < DimCnt; ++i) {
			if (m_min[i] < other.m_min[i] || other.m_min[i] < m_min[i] ||
				m_max[i] < other.m_max[i] || other.m_max[i] < m_max[i]) {
				return false;
			}
		}
		return true;
	}

	const DimType& GetMin (short dimIdx) const { return m_min[dimIdx]; }
	const DimType& GetMax (short dimIdx) const { return m_max[dimIdx]; }
};


template<typename KeyType>
struct KDTreeNodeIndex<KeyType, KDTreeNodeBoundsDisabled> {
	class StackData {
	public:
		void SetupFromKey (const KeyType& /*key*/)
		{
		}
	};

	class NodeData {
	public:
	};

	template<typename NodeType>
	static void Merge (short /*dimIdx*/, NodeType* /*node*/, StackData& /*leftStackDataInOut*/, const StackData& /*rightStackData*/)
	{
	}

	template<typename NodeType>
	static bool Check (short /*dimIdx*/, const NodeType* /*node*/, StackData& /*leftStackDataInOut*/, const StackData& /*rightStackData*/)
	{
		return true;
	}
};


template<typename KeyType>
struct KDTreeNodeIndex<KeyType, KDTreeNodeBoundsEnabled> {
	typedef KDTreeBounds<KeyType> BoundsType;

	class StackData {
	public:
		void SetupFromKey (const KeyType& /*key*/)
		{
		}
	};

	class NodeData {
		 BoundsType bounds;
	public:
		const BoundsType& GetBounds () const
		{
			return bounds;
		}

		void SetBounds (const BoundsType& bounds)
		{
			this->bounds = bounds;
		}
	};

	template<typename NodeBaseType>
	static BoundsType NodeBaseBounds (const NodeBaseType* nodeBase)
	{
		return nodeBase->IsLeaf () ? BoundsType (nodeBase->ToLeaf ()->GetAssoc ().GetKey ()) : nodeBase->ToNode ()->GetBounds ();
	}

	template<typename NodeType>
	static BoundsType NodeBounds (const NodeType* node)
	{
		auto* left = node->GetLeft ();
		auto* right = node->GetRight ();

		const BoundsType& leftBounds = NodeBaseBounds (left);
		const BoundsType& rightBounds = NodeBaseBounds (right);
		BoundsType bounds;
		bounds.Set (leftBounds, rightBounds);

		return bounds;
	}

	template<typename NodeType>
	static void Merge (short /*dimIdx*/, NodeType* node, StackData& /*leftStackDataInOut*/, const StackData& /*rightStackData*/)
	{
		node->SetBounds (NodeBounds (node));
	}


	template<typename NodeType>
	static bool Check (short /*dimIdx*/, const NodeType* node, StackData& /*leftStackDataInOut*/, const StackData& /*rightStackData*/)
	{
		return node->GetBounds () == NodeBounds (node);
	}
};


template<typename KeyType>
struct KDTreeNodeIndex<KeyType, KDTreeNodeBoundsOrthogonalPair> {
	typedef typename KeyType::DimType DimType;
	
	class StackData {
	public:
		typedef KDTreeBounds<KeyType> BoundsType;

	private:
		bool isValid; 
		bool isPartial; // contains only the updated part
		BoundsType bounds;

	public:

		StackData () : isValid (false), isPartial (true)
		{
		}

		void SetupFromKey (const KeyType& key)
		{
			DBASSERT (!isValid && isPartial && bounds == BoundsType ()); 
			bounds = BoundsType (key);
			isValid = true;
			isPartial = false;
		}

		const BoundsType& GetBounds () const
		{
			DBASSERT (isValid);
			return bounds;
		}

		bool IsValid () const
		{
			return isValid;
		}

		bool IsPartial () const
		{
			return isPartial;
		}

		void Merge (const StackData& other)
		{
			if (other.IsValid ()) {
				if (isValid) {
					bounds.Set (bounds, other.GetBounds ());
				} else {
					bounds = other.GetBounds ();
					isValid = true;
				}
			}
			isPartial = isPartial || other.isPartial;
		}
	};

	class NodeData {
		DimType orthogonalLimit;
	public:
		const DimType& GetOrthogonalLimit () const
		{
			return orthogonalLimit;
		}

		void SetOrthogonalLimit (const DimType& orthogonalLimit)
		{
			this->orthogonalLimit = orthogonalLimit;
		}
	};


	template<typename NodeType>
	static void Merge (short dimIdx, NodeType* node, StackData& leftStackDataInOut, const StackData& rightStackData)
	{
		const short dimIdxPair = dimIdx ^ 0x1;

		if (dimIdx & 0x1) {
			if (rightStackData.IsValid ()) {
				const DimType& val = rightStackData.GetBounds ().GetMin (dimIdxPair);
				if (rightStackData.IsPartial ()) {
					node->SetOrthogonalLimit (GS::Min (node->GetOrthogonalLimit (), val));
				} else {
					node->SetOrthogonalLimit (val);
				}
			}
		} else {
			if (leftStackDataInOut.IsValid ()) {
				const DimType& val = leftStackDataInOut.GetBounds ().GetMax (dimIdxPair);
				if (leftStackDataInOut.IsPartial ()) {
					node->SetOrthogonalLimit (GS::Max (node->GetOrthogonalLimit (), val));
				} else {
					node->SetOrthogonalLimit (val);
				}
			}
		}

		leftStackDataInOut.Merge (rightStackData);
	}


	template<typename NodeType>
	static bool Check (short dimIdx, const NodeType* node, StackData& leftStackDataInOut, const StackData& rightStackData)
	{
		DBASSERT (leftStackDataInOut.IsValid ());
		DBASSERT (!leftStackDataInOut.IsPartial ());
		DBASSERT (rightStackData.IsValid ());
		DBASSERT (!rightStackData.IsPartial ());

		const short dimIdxPair = dimIdx ^ 0x1;

		bool success = false;
		if (dimIdx & 0x1) {
			const DimType& val = rightStackData.GetBounds ().GetMin (dimIdxPair);
			success = node->GetOrthogonalLimit () <= val;
		} else {
			const DimType& val = leftStackDataInOut.GetBounds ().GetMax (dimIdxPair);
			success = val <= node->GetOrthogonalLimit ();
		}

		leftStackDataInOut.Merge (rightStackData);

		return success;
	}

	static_assert ((KeyType::DimCnt & 0x1) == 0, "KDTree with orthogonal range query support should have even number of dimensions!");
};


template <typename TreeType, typename AdapterType, typename QueryTypes, KDTreeNodeBounds NodeBoundsMode>
class RangeQueryImpl;

// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------

// --- Function definitions --------------------------------------------------------------------------------------------

template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
typename KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Allocator* KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::CreateAllocator (FixedAllocator::AllocationPolicy allocationPolicy /*= FixedAllocator::FixedSize*/)
{
	return new Allocator (allocationPolicy);
}


template <typename KeyType,
		  typename ElemType,
		  KDTreeNodeBounds NodeBoundsMode,
		  KDTreeUpdateMode UpdateMode,
		  KDTreeElemSetType ElemSetType,
		  KDTreeStatistics StatisticsMode>
KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::KDTree (Allocator* alloc /*= nullptr*/,
																							FixedAllocator::AllocationPolicy allocationPolicy /*= FixedAllocator::FixedSize*/,
																							ElemComparer elemComparer) :
	m_statistics (),
	ownAllocator (alloc == nullptr),
	m_allocator (alloc == nullptr ? CreateAllocator (allocationPolicy) : alloc),
	m_root (nullptr),
	m_allocatedNodeChain (nullptr),
	m_leafElemComparer (elemComparer),
	m_elemLeafMap (),
	m_updatedLeafCount (0)
#ifdef CHECKED_VERSION
	, m_modificationStamp (0),
	m_removedLeafCount (0)
#endif
{
}


template <typename KeyType,
	typename ElemType,
	KDTreeNodeBounds NodeBoundsMode,
	KDTreeUpdateMode UpdateMode,
	KDTreeElemSetType ElemSetType,
	KDTreeStatistics StatisticsMode>
KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::KDTree (ElemComparer elemComparer) :
	KDTree (nullptr, FixedAllocator::FixedSize, elemComparer)
{
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
USize KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::GetSize () const
{
	USize treeSize;
	if (m_root == nullptr) {
		treeSize = 0;
	} else if (m_root->IsLeaf ()) {
		treeSize =  1;
	} else {
		treeSize = m_root->ToNode ()->GetTotalLeafCount ();
	}
	return treeSize + m_leavesToAdd.GetSize () + m_updatedLeafCount - m_leavesToDelete.GetSize ();
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
void KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::SetCapacity (USize capacity)
{
	const USize size = GetSize ();
	if (capacity > size) {
		m_leavesToAdd.SetCapacity (capacity - size + m_leavesToAdd.GetSize ());
		m_elemLeafMap.EnsureCapacity (capacity);
	}
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::~KDTree (void)
{
	Clear ();
	if (ownAllocator) {
		delete m_allocator;
	}
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Insert (const KeyType &key, const ElemType &elem)
{
	Put (key, elem);
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
typename KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::StoredElemPtr	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Add (const KeyType &key, const ElemType &elem)
{
	Leaf* leaf;
	try {
		if (!m_elemLeafMap.CanAdd (elem)) {
			return StoredElemPtr (nullptr);
		}

		leaf = CreateLeaf (key, elem);
		try {
			m_leavesToAdd.Push (leaf);
			leaf->SetAddListIndex (m_leavesToAdd.GetSize ());
		} catch (const GS::Exception&) {
			DestroyLeaf (leaf);
		}

		Update<KDTreeNormalUpdate> ();
	} catch (const GS::Exception&) {
		DBBREAK ();
		Clear ();
		throw;
	}
	return StoredElemPtr (&leaf->GetAssoc ().GetElem ());
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
typename KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::StoredElemPtr	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Add (const KeyType &key)
{
	Leaf* leaf;
	try {
		if (!m_elemLeafMap.CanAddDefault ()) {
			return StoredElemPtr (nullptr);
		}

		leaf = CreateLeaf (key);
		try {
			m_leavesToAdd.Push (leaf);
			leaf->SetAddListIndex (m_leavesToAdd.GetSize ());
		} catch (const GS::Exception&) {
			DestroyLeaf (leaf);
		}

		Update<KDTreeNormalUpdate> ();
	} catch (const GS::Exception&) {
		DBBREAK ();
		Clear ();
		throw;
	}
	return StoredElemPtr (&leaf->GetAssoc ().GetElem ());
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Delete (const StoredElemPtr &elemPtr)
{
	Leaf* leaf = GetLeafPtrFromStoredElemPtr (elemPtr);
	try {
		DeleteLeaf (leaf);

		Update<KDTreeNormalUpdate> ();
	} catch (const GS::Exception&) {
		DBBREAK ();
		Clear ();
		throw;
	}
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
bool	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Delete (const ElemType &elem)
{
	Leaf *leaf;
	if (!m_elemLeafMap.Get (elem, &leaf)) {
		return false;
	}

	Delete (StoredElemPtr (&leaf->GetAssoc ().GetElem ()));
	return true;
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::UpdateKey (const StoredElemPtr& elemPtr, const KeyType& newKey)
{
	Leaf* leaf = GetLeafPtrFromStoredElemPtr (elemPtr);
	UInt32 addListIndex = leaf->GetAddListIndex ();
	--addListIndex;
	if (addListIndex < m_leavesToAdd.GetSize () && leaf == m_leavesToAdd [addListIndex]) {
		leaf->GetAssoc ().SetKey (newKey);
	} else {
		const KeyType& actKey = leaf->GetAssoc ().GetKey ();
		for (short dimIdx = 0; dimIdx < DimCnt; ++dimIdx) {
			if (actKey.GetDimVal (dimIdx) != newKey.GetDimVal (dimIdx)) {
				DBASSERT ((leaf->GetSearchIndex () & DeletedLeafBit) == 0);
				if ((leaf->GetSearchIndex () & UpdatedLeafBit) == 0) {
					m_leavesToDelete.Push (leaf);
					++m_updatedLeafCount;
					leaf->SetSearchIndex (leaf->GetSearchIndex () | UpdatedLeafBit);
				}
				leaf->GetAssoc ().SetKey (newKey);
				Update<KDTreeNormalUpdate> ();
				break;
			}
		}
	}
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::UpdateElem (const StoredElemPtr& elemPtr, const ElemType& newElem)
{
	Leaf* leaf = GetLeafPtrFromStoredElemPtr (elemPtr);
	m_elemLeafMap.Delete (leaf);
	leaf->GetAssoc ().GetElem () = newElem;
	m_elemLeafMap.Add (leaf);
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
bool	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::UpdateKey (const ElemType& elem, const KeyType& newKey)
{
	Leaf *leaf;
	if (!m_elemLeafMap.Get (elem, &leaf)) {
		return false;
	}

	UpdateKey (StoredElemPtr (&leaf->GetAssoc ().GetElem ()), newKey);

	return true;
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
bool	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::UpdateElem (const ElemType& elem, const ElemType& newElem)
{
	Leaf *leaf;
	if (!m_elemLeafMap.Get (elem, &leaf)) {
		return false;
	}
	if (m_elemLeafMap.CanAdd (newElem)) {
		UpdateElem (StoredElemPtr (&leaf->GetAssoc ().GetElem ()), newElem);
		return true;
	}
	return false;
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Update (const KeyType &key, const ElemType &elem)
{
	Put (key, elem);
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
template <typename SourceType>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Rebuild (SourceType& source)
{
	Clear ();

	const USize size = source.GetSize ();

	if (size < 1)
		return;

	SetCapacity (size);

	try {
		for (UIndex i = 0; i < size; ++i) {
			if (DBVERIFY (m_elemLeafMap.CanAdd (source.GetValue (i)))) {
				Leaf* leaf = CreateLeaf (source.GetKey (i), source.GetValue (i));
				m_leavesToAdd.Push (leaf);
				leaf->SetAddListIndex (m_leavesToAdd.GetSize ());
			}
		}

		Update<KDTreeNormalUpdate> ();
	} catch (const GS::Exception&) {
		DBBREAK ();
		Clear ();
		throw;
	}
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
template <typename ContainerType, typename GetKeyOpType, typename GetValueOpType>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Rebuild (const ContainerType& container, GetKeyOpType& getKey, GetValueOpType& getValue)
{
	Clear ();

	const USize size = container.GetSize ();

	if (size < 1)
		return;

	SetCapacity (size);

	try {
		for (typename ContainerType::ConstIterator it (container.Enumerate ()); it != nullptr; ++it) {
			if (DBVERIFY (m_elemLeafMap.CanAdd (getValue (*it)))) {
				Leaf* leaf = CreateLeaf (getKey (*it), getValue (*it));
				m_leavesToAdd.Push (leaf);
				leaf->SetAddListIndex (m_leavesToAdd.GetSize ());
			}
		}

		Update<KDTreeNormalUpdate> ();
	} catch (const GS::Exception&) {
		DBBREAK ();
		Clear ();
		throw;
	}
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
template <typename PairIteratorType>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Rebuild (PairIteratorType source, USize capacityHint)
{
	Clear ();

	SetCapacity (capacityHint);

	try {
		while (source != nullptr) {
			if (m_elemLeafMap.CanAdd (*(source->value))) {
				Leaf* leaf = CreateLeaf (*(source->key), *(source->value));
				m_leavesToAdd.Push (leaf);
				leaf->SetAddListIndex (m_leavesToAdd.GetSize ());
			}
			++source;
		}

		Update<KDTreeNormalUpdate> ();
	} catch (const GS::Exception&) {
		DBBREAK ();
		Clear ();
		throw;
	}
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Clear (void)
{
	RecursiveDeleteTree<true /*DeleteAll*/> (m_root);
	m_elemLeafMap.Clear ();
	m_root = nullptr;

	CleanUpDelayedData ();
}


template <typename TreeType, typename AdapterType, typename QueryTypes, KDTreeNodeBounds NodeBoundsMode>
class RangeQueryImpl {
private:
	typedef typename TreeType::AssociatedKeyType KeyType;
	static const short	DimCnt = KeyType::DimCnt;
	typedef typename KeyType::DimType DimType;
	typedef typename QueryTypes::NodeBase NodeBase;
	typedef typename QueryTypes::Node Node;
	typedef typename QueryTypes::Leaf Leaf;

	const KeyType& keyMin;
	const KeyType& keyMax;

	AdapterType& adapter;

public:
	RangeQueryImpl (const KeyType& keyMin, const KeyType& keyMax, AdapterType& adapter) : keyMin (keyMin), keyMax (keyMax), adapter (adapter) {}

	void operator () (NodeBase* nb)
	{
		DBASSERT (nb);

		const UInt32 NUM_STACK = 64;

		struct NodeItem {
			short			dimIdx;
			NodeBase*		nb;
			void Set (short dimIdx, NodeBase* nb)
			{
				this->dimIdx = dimIdx;
				this->nb = nb;
			}
		};


		NodeItem stack[NUM_STACK];
		NodeItem* currItem = stack;
		currItem->Set (0, nb);

		for (;;) {
			while (!currItem->nb->IsLeaf ()) {
				Node* node		= currItem->nb->ToNode ();
				const bool leftWay		= keyMin.GetDimVal (currItem->dimIdx) <= node->GetSeparatorVal ();
				const bool rightWay		= node->GetSeparatorVal () <= keyMax.GetDimVal (currItem->dimIdx);

				const short	nextDimIdx	= TreeType::NextDim (currItem->dimIdx);

				if (rightWay) {
					currItem->Set (nextDimIdx, node->GetRight ());
					if (leftWay) {
						++currItem;
						currItem->Set (nextDimIdx, node->GetLeft ());
					}
				} else {
					if (leftWay) {
						currItem->Set (nextDimIdx, node->GetLeft ());
					} else {
						DBBREAK ();
						if (currItem == stack)
							return;
						--currItem;
					}
				}
			}

			Leaf		*leaf	= currItem->nb->ToLeaf ();
			const KeyType&	elemKey = leaf->GetAssoc ().GetKey ();

			for (short i = 0; i < DimCnt; ++i) {
				if (!(keyMin.GetDimVal (i) <= elemKey.GetDimVal (i) && elemKey.GetDimVal (i) <= keyMax.GetDimVal (i))) {
					goto skipAdd;
				}
			}

			leaf->LeafFound ();
			adapter (static_cast<typename QueryTypes::ResultType> (leaf->GetAssoc ().GetElem ()));

	skipAdd:

			if (currItem == stack)
				break;

			--currItem;
		}
	}

};


template <typename TreeType, typename AdapterType, typename QueryTypes>
class RangeQueryImpl<TreeType, AdapterType, QueryTypes, KDTreeNodeBoundsEnabled> {
private:
	typedef typename TreeType::AssociatedKeyType KeyType;
	static const short	DimCnt = KeyType::DimCnt;
	typedef typename KeyType::DimType DimType;
	typedef typename QueryTypes::NodeBase NodeBase;
	typedef typename QueryTypes::Node Node;
	typedef typename QueryTypes::Leaf Leaf;

	const KeyType& keyMin;
	const KeyType& keyMax;

	AdapterType& adapter;

public:
	RangeQueryImpl (const KeyType& keyMin, const KeyType& keyMax, AdapterType& adapter) : keyMin (keyMin), keyMax (keyMax), adapter (adapter) {}

	void operator () (NodeBase* root)
	{
		DBASSERT (root);

		const UInt32 NUM_STACK = 128;

		struct NodeItem {
			short			dimIdx;
			NodeBase*		nb;
			void Set (short dimIdx, NodeBase* nb)
			{
				this->dimIdx = dimIdx;
				this->nb = nb;
			}
		};

		NodeItem stack[NUM_STACK];
		NodeItem* currItem = stack;
		currItem->Set (0, root);

		for (;;) {
			NodeBase* nb = currItem->nb;
			if (nb->IsLeaf ()) {
				Leaf* leaf = nb->ToLeaf ();
				const KeyType&	elemKey = leaf->GetAssoc ().GetKey ();
				for (short i = 0; i < DimCnt; ++i) {
					if (keyMin.GetDimVal (i) > elemKey.GetDimVal (i) || elemKey.GetDimVal (i) > keyMax.GetDimVal (i)) {
						goto skipCurrent;
					}
				}

				leaf->LeafFound ();
				adapter (static_cast<typename QueryTypes::ResultType> (leaf->GetAssoc ().GetElem ()));

			} else {
				Node* node = nb->ToNode ();
				for (short i = 0; i < DimCnt; ++i) {
					if (node->GetBounds ().GetMax (i) < keyMin.GetDimVal (i) || node->GetBounds ().GetMin (i) > keyMax.GetDimVal (i)) {
						goto skipCurrent;
					}
				}

				const bool leftWay		= keyMin.GetDimVal (currItem->dimIdx) <= node->GetSeparatorVal ();
				const bool rightWay		= node->GetSeparatorVal () <= keyMax.GetDimVal (currItem->dimIdx);
				const short	nextDimIdx	= TreeType::NextDim (currItem->dimIdx);


				if (rightWay) {
					currItem->Set (nextDimIdx, node->GetRight ());
					if (leftWay) {
						++currItem;
						currItem->Set (nextDimIdx, node->GetLeft ());
					}
				} else {
					if (leftWay) {
						currItem->Set (nextDimIdx, node->GetLeft ());
					} else {
						DBBREAK ();
						if (currItem == stack)
							return;
						--currItem;
					}
				}
				continue;
			}

	skipCurrent:
			if (currItem == stack)
				break;

			--currItem;
		}
	}

};


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
template <typename AdapterType>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::RangeQuery (const KeyType &keyMin, const KeyType &keyMax, AdapterType &adapter) const
{

#ifdef CHECKED_VERSION
	for (short i = 0; i < DimCnt; ++i) {
		DBASSERT (keyMin.GetDimVal (i) <= keyMax.GetDimVal (i));
	}
#endif

	RangeQueryImpl<TreeType, AdapterType, QueryTypes<KDTree, ElemSetType, true>, NodeBoundsMode> query (keyMin, keyMax, adapter);

	CustomQuery (query);
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
template <typename AdapterType>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::RangeQuery (const KeyType &keyMin, const KeyType &keyMax, AdapterType &adapter)
{

#ifdef CHECKED_VERSION
	for (short i = 0; i < DimCnt; ++i) {
		DBASSERT (keyMin.GetDimVal (i) <= keyMax.GetDimVal (i));
	}
#endif

	RangeQueryImpl<TreeType, AdapterType, QueryTypes<KDTree, ElemSetType, false>, NodeBoundsMode> query (keyMin, keyMax, adapter);

	CustomQuery (query);
}


enum class OrthogonalRangeQueryInterrupt {
	Disabled,
	Enabled	
};

template<KDTreeNodeBounds NodeBoundsMode>
struct KeyNodeBoundsIntersectTest {
	template<typename NodeType, typename KeyType>
	static GS_FORCE_INLINE bool Do (NodeType* /*node*/, const KeyType& /*key*/)
	{
		return true;
	}
};

template<>
struct KeyNodeBoundsIntersectTest<KDTreeNodeBoundsEnabled> {
	template<typename NodeType, typename KeyType>
	static GS_FORCE_INLINE bool Do (NodeType* node, const KeyType& key)
	{
		const short DimCnt = KeyType::DimCnt;
		for (short i = 0; i < DimCnt; i += 2) {
			if (!(key.GetDimVal (i) <= node->GetBounds ().GetMax (i + 1) && node->GetBounds ().GetMin (i) <= key.GetDimVal (i + 1)))
				return false;
		}
		return true;
	}
};

template<KDTreeNodeBounds NodeBoundsMode>
struct OrhogonalPairTest {
	template<typename NodeType, typename KeyType>
	static GS_FORCE_INLINE bool TestLeft (short /*dimIdx*/, NodeType* /*node*/, const KeyType& /*key*/)
	{
		return true;
	}
	template<typename NodeType, typename KeyType>
	static GS_FORCE_INLINE bool TestRight (short /*dimIdx*/, NodeType* /*node*/, const KeyType& /*key*/)
	{
		return true;
	}
};

template<>
struct OrhogonalPairTest<KDTreeNodeBoundsOrthogonalPair> {
	template<typename NodeType, typename KeyType>
	static GS_FORCE_INLINE bool TestLeft (short dimIdx, NodeType* node, const KeyType& key)
	{
		return key.GetDimVal (dimIdx) <= node->GetOrthogonalLimit ();
	}
	template<typename NodeType, typename KeyType>
	static GS_FORCE_INLINE bool TestRight (short dimIdx, NodeType* node, const KeyType& key)
	{
		return node->GetOrthogonalLimit () <= key.GetDimVal (dimIdx);
	}
};

template<>
struct KeyNodeBoundsIntersectTest<KDTreeNodeBoundsOrthogonalPair> {
	template<typename NodeType, typename KeyType>
	static GS_FORCE_INLINE bool Do (NodeType* /*node*/, const KeyType& /*key*/)
	{
		return true;
	}
};

template<OrthogonalRangeQueryInterrupt InterruptMode>
struct StoreValue;

template<>
struct StoreValue<OrthogonalRangeQueryInterrupt::Disabled> {
	template<typename AdapterType, typename ResultType>
	static GS_FORCE_INLINE auto Do (AdapterType& adapter, ResultType& result)
	{
		adapter (result);
		return true;
	}
};

template<>
struct StoreValue<OrthogonalRangeQueryInterrupt::Enabled> {
	template<typename AdapterType, typename ResultType>
	static GS_FORCE_INLINE auto Do (AdapterType& adapter, ResultType& result)
	{
		return adapter (result);
	}
};

template <typename TreeType, typename AdapterType, typename QueryTypes, OrthogonalRangeQueryInterrupt InterruptMode>
class OrthogonalRangeQueryImpl {
private:

	typedef typename TreeType::AssociatedKeyType KeyType;
	static const short	DimCnt = KeyType::DimCnt;
	typedef typename KeyType::DimType DimType;
	typedef typename QueryTypes::NodeBase NodeBase;
	typedef typename QueryTypes::Node Node;
	typedef typename QueryTypes::Leaf Leaf;

	AdapterType&	adapter;
	const KeyType	key;

public:
	OrthogonalRangeQueryImpl (AdapterType& adapter, const KeyType& key) : adapter (adapter), key (key) {}

	void operator () (NodeBase* root)
	{
		const UInt32 NUM_STACK = 128;

		struct NodeItem {
			short			dimIdx;
			NodeBase*	nb;
			void Set (short dimIdx, NodeBase* nb)
			{
				this->dimIdx = dimIdx;
				this->nb = nb;
			}
		};

		NodeItem stack[NUM_STACK];
		NodeItem* currItem = stack;
		currItem->Set (0, root);

		for (;;) {
			NodeBase* nb = currItem->nb;

			if (nb->IsLeaf ()) {
				Leaf *leaf = nb->ToLeaf ();
				const KeyType &elemKey = leaf->GetAssoc ().GetKey ();
				for (short i = 0; i < DimCnt; i+= 2) {
					if (!(key.GetDimVal (i) <= elemKey.GetDimVal (i + 1) && elemKey.GetDimVal (i) <= key.GetDimVal (i + 1)))
						goto skipCurrent;
				}
				leaf->LeafFound ();
				if (!StoreValue<InterruptMode>::Do (adapter, static_cast<typename QueryTypes::ResultType> (leaf->GetAssoc ().GetElem ()))) {
					return;
				}
			} else {
				Node *node = nb->ToNode ();
				if (!KeyNodeBoundsIntersectTest<TreeType::NodeBoundsModeValue>::Do (node, key)) {
					goto skipCurrent;
				}

				const short dimIdx = currItem->dimIdx;
				const short dimIdxPair = dimIdx ^ 0x1;
				const short nextDimIdx = TreeType::NextDim (dimIdx);

				if (dimIdx & 0x1) {
					// interval right end in node separator value
					const DimType& intervalLeftEnd = key.GetDimVal (dimIdxPair);

					DBASSERT (intervalLeftEnd <= key.GetDimVal (dimIdx));
					if (OrhogonalPairTest<TreeType::NodeBoundsModeValue>::TestRight (dimIdx, node, key)) {
						currItem->Set (nextDimIdx, node->GetRight ());
						if (intervalLeftEnd <= node->GetSeparatorVal ()) {
							++currItem;
							currItem->Set (nextDimIdx, node->GetLeft ());
						}
					} else {
						if (intervalLeftEnd <= node->GetSeparatorVal ()) {
							currItem->Set (nextDimIdx, node->GetLeft ());
						} else {
							goto skipCurrent;
						}
					}
				} else {
					// interval left end in node separator value
					const DimType& intervalRightEnd = key.GetDimVal (dimIdxPair);

					DBASSERT (key.GetDimVal (dimIdx) <= intervalRightEnd);
					if (OrhogonalPairTest<TreeType::NodeBoundsModeValue>::TestLeft (dimIdx, node, key)) {
						currItem->Set (nextDimIdx, node->GetLeft ());
						if (node->GetSeparatorVal () <= intervalRightEnd) {
							++currItem;
							currItem->Set (nextDimIdx, node->GetRight ());
						}
					} else {
						if (node->GetSeparatorVal () <= intervalRightEnd) {
							currItem->Set (nextDimIdx, node->GetRight ());
						} else {
							goto skipCurrent;
						}
					}
				}
				continue;
			}

skipCurrent:

			if (currItem == stack)
				break;
			--currItem;
		}
	}
};

template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
template <typename AdapterType>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::OrthogonalRangeQuery (const KeyType& key, AdapterType& adapter) const
{
	static_assert ((DimCnt & 0x1) == 0, "KDTree with orthogonal range query support should have even number of dimensions!");

	OrthogonalRangeQueryImpl<TreeType, AdapterType, QueryTypes<KDTree, ElemSetType, true>, OrthogonalRangeQueryInterrupt::Disabled> query (adapter, key);
	CustomQuery (query);
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
template <typename AdapterType>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::OrthogonalRangeQuery (const KeyType& key, AdapterType& adapter)
{
	static_assert ((DimCnt & 0x1) == 0, "KDTree with orthogonal range query support should have even number of dimensions!");

	OrthogonalRangeQueryImpl<TreeType, AdapterType, QueryTypes<KDTree, ElemSetType, false>, OrthogonalRangeQueryInterrupt::Disabled> query (adapter, key);
	CustomQuery (query);
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
template <typename AdapterType>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::InterruptibleOrthogonalRangeQuery (const KeyType& key, AdapterType& adapter) const
{
	static_assert ((DimCnt & 0x1) == 0, "KDTree with orthogonal range query support should have even number of dimensions!");

	OrthogonalRangeQueryImpl<TreeType, AdapterType, QueryTypes<KDTree, ElemSetType, true>, OrthogonalRangeQueryInterrupt::Enabled> query (adapter, key);
	CustomQuery (query);
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
template <typename AdapterType>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::InterruptibleOrthogonalRangeQuery (const KeyType& key, AdapterType& adapter)
{
	static_assert ((DimCnt & 0x1) == 0, "KDTree with orthogonal range query support should have even number of dimensions!");

	OrthogonalRangeQueryImpl<TreeType, AdapterType, QueryTypes<KDTree, ElemSetType, false>, OrthogonalRangeQueryInterrupt::Enabled> query (adapter, key);
	CustomQuery (query);
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline bool	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Contains (const ElemType &elem) const
{
	Leaf* leaf;
	return m_elemLeafMap.Get (elem, &leaf);
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline const KeyType&	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::GetKey (const StoredElemPtr& elemPtr) const
{
	return GetLeafPtrFromStoredElemPtr (elemPtr)->GetAssoc ().GetKey ();
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline const ElemType*	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::GetValuePtr (const StoredElemPtr& elemPtr) const
{
	return &GetLeafPtrFromStoredElemPtr (elemPtr)->GetAssoc ().GetElem ();
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline typename KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::NotConstValuePtrType	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::GetValuePtr (const StoredElemPtr& elemPtr)
{
	return &GetLeafPtrFromStoredElemPtr (elemPtr)->GetAssoc ().GetElem ();
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline const KeyType&	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::GetKey (const ElemType &elem) const
{
	Leaf* leaf;
	DBVERIFY (m_elemLeafMap.Get (elem, &leaf));
	return leaf->GetAssoc ().GetKey ();
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline typename KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::ConstIterator	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Enumerate () const
{
	Update<KDTreeLazyUpdate> ();
	return ConstIterator (*this, ValueIteratorState (this));
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline typename KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Iterator	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Enumerate ()
{
	Update<KDTreeLazyUpdate> ();
	return Iterator (*this, ValueIteratorState (this));
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline typename KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::ConstIterator	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::LazyEnumerate () const
{
	return ConstIterator (*this, ValueIteratorState (this));
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline typename KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Iterator	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::LazyEnumerate ()
{
	return Iterator (*this, ValueIteratorState (this));
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline typename KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::ConstPairIterator	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::EnumeratePairs () const
{
	Update<KDTreeLazyUpdate> ();
	return ConstPairIterator (*this, ConstPairIteratorState (this));
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline typename KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::PairIterator	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::EnumeratePairs ()
{
	Update<KDTreeLazyUpdate> ();

	typedef typename KDTreeIterator<KDTree, ElemSetType>::PairIteratorStateType PairIteratorStateType;
	return PairIterator (*this, PairIteratorStateType (this));
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline typename KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::ConstPairIterator	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::LazyEnumeratePairs () const
{
	return ConstPairIterator (*this, ConstPairIteratorState (this));
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline typename KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::PairIterator	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::LazyEnumeratePairs ()
{
	typedef typename KDTreeIterator<KDTree, ElemSetType>::PairIteratorStateType PairIteratorStateType;
	return PairIterator (*this, PairIteratorStateType (this));
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::ValueIteratorState::ValueIteratorState (const KDTree* tree) : nextLeafToAdd (0)
#ifdef CHECKED_VERSION
	, initialModificationStamp (tree->m_modificationStamp)
#endif
{
	if (tree->m_root != nullptr) {
		nodeStack [0] = tree->m_root;
		stackSize = 1;
	} else {
		stackSize = 0;
	}
	tree->UpdateIteratorState (*this);
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::ValueIteratorState::ValueIteratorState (const ValueIteratorState& src) :
	stackSize (src.stackSize), nextLeafToAdd (src.nextLeafToAdd)
#ifdef CHECKED_VERSION
	, initialModificationStamp (src.initialModificationStamp)
#endif
{
	for (UInt32 i = 0; i < src.stackSize; ++i) {
		nodeStack [i] = src.nodeStack [i];
	}
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
void KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::UpdateIteratorState (ValueIteratorState& state) const
{
	DBASSERT (m_modificationStamp == state.initialModificationStamp);
	while (state.stackSize > 0) {
		while (!state.nodeStack [state.stackSize - 1]->IsLeaf ()) {
			state.nodeStack [state.stackSize] = state.nodeStack [state.stackSize - 1]->ToNode ()->GetLeft ();
			state.nodeStack [state.stackSize - 1] = state.nodeStack [state.stackSize - 1]->ToNode ()->GetRight ();
			++state.stackSize;
			DBASSERT (state.stackSize <= state.MaxStackSize);
		}
		if ((state.nodeStack [state.stackSize - 1]->ToLeaf ()->GetSearchIndex () & DeletedLeafBit) == 0) {
			return;
		}
		--state.stackSize;
	}
	if (state.nextLeafToAdd < m_leavesToAdd.GetSize ()) {
		state.nodeStack [state.stackSize] = m_leavesToAdd [state.nextLeafToAdd];
		++state.stackSize;
		++state.nextLeafToAdd;
	}
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline const ElemType&  KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::GetCurrent (const ValueIteratorState& state) const
{
	DBASSERT (state.stackSize != 0);
	return state.nodeStack [state.stackSize - 1]->ToLeaf ()->GetAssoc ().GetElem ();
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline ElemType&  KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::GetCurrent (const ValueIteratorState& state)
{
	DBASSERT (state.stackSize != 0);
	return state.nodeStack [state.stackSize - 1]->ToLeaf ()->GetAssoc ().GetElem ();
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline void				KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Increment  (ValueIteratorState& state) const
{
	if (state.stackSize > 0) {
		--state.stackSize;
		UpdateIteratorState (state);
	} else {
		DBBREAK ();
	}
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline bool				KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::IsEqual    (const ValueIteratorState& state1, const ValueIteratorState& state2) const
{
	return state1.stackSize == state2.stackSize && (state1.stackSize == 0 || state1.nodeStack [state1.stackSize - 1] == state2.nodeStack [state2.stackSize - 1]);
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline bool				KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::IsEnd      (const ValueIteratorState& state) const
{
	return state.stackSize == 0;
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline const typename KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::ConstAssoc&	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::GetCurrent (const ConstPairIteratorState& state) const
{
	DBASSERT (state.stackSize != 0);
	state.assoc.key = &state.nodeStack [state.stackSize - 1]->ToLeaf ()->GetAssoc ().GetKey ();
	state.assoc.value = &state.nodeStack [state.stackSize - 1]->ToLeaf ()->GetAssoc ().GetElem ();
	return state.assoc;
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline typename KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::ConstAssoc&	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::GetCurrent (const ConstPairIteratorState& state)
{
	DBASSERT (state.stackSize != 0);
	state.assoc.key = &state.nodeStack [state.stackSize - 1]->ToLeaf ()->GetAssoc ().GetKey ();
	state.assoc.value = &state.nodeStack [state.stackSize - 1]->ToLeaf ()->GetAssoc ().GetElem ();
	return state.assoc;
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline const typename KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Assoc&	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::GetCurrent (const PairIteratorState& state) const
{
	DBASSERT (state.stackSize != 0);
	state.assoc.key = &state.nodeStack [state.stackSize - 1]->ToLeaf ()->GetAssoc ().GetKey ();
	state.assoc.value = &state.nodeStack [state.stackSize - 1]->ToLeaf ()->GetAssoc ().GetElem ();
	return state.assoc;
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline typename KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Assoc&	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::GetCurrent (const PairIteratorState& state)
{
	DBASSERT (state.stackSize != 0);
	state.assoc.key = &state.nodeStack [state.stackSize - 1]->ToLeaf ()->GetAssoc ().GetKey ();
	state.assoc.value = &state.nodeStack [state.stackSize - 1]->ToLeaf ()->GetAssoc ().GetElem ();
	return state.assoc;
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Dump (GS::OChannel &ch) const
{
	if (!m_root)
		return;

	GS::Array<GS::Array<const NodeBase *> > lineArray;

	RecursiveDump (m_root, 0, lineArray);

	for (UIndex i=0; i<lineArray.GetSize (); i++) {
		const GS::Array<const NodeBase *> &currLine = lineArray[i];
		ch << i << ".\t";
		for (UIndex j=0; j<currLine.GetSize (); j++) {
			const NodeBase *nb = currLine[j];
			ch << "(" << nb  << ")";
			if (nb->IsLeaf ()) {
				const Leaf *leaf = nb->ToLeaf ();

				ch << "L:";
				for (short k=0; k<DimCnt; k++)
					ch << " " << leaf->GetAssoc ().GetKey ().GetDimVal (k) << ";";

				ch << "   ";
			} else {
				const Node *node = nb->ToNode ();
				ch << "N: " << node->GetSeparatorVal () << ", LC=" << node->GetTotalLeafCount () << ";   ";
			}
		}
		ch << "\n";
	}
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline bool	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::IsEmpty (void) const
{
	return GetSize () == 0;
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::ForceUpdate (void)
{
	Update<KDTreeLazyUpdate> ();
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline typename KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Leaf*	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::CreateLeaf (const KeyType& key, const ElemType& elem)
{
	static_assert (sizeof (AllocatedNode) <= sizeof (Node), "nodeSize");
	m_allocatedNodeChain = new (m_allocator->nodeAllocator.Allocate ()) AllocatedNode (m_allocatedNodeChain);
	Leaf* leaf = new (m_allocator->leafAllocator.Allocate ()) Leaf (this, key, elem);
	try {
		m_elemLeafMap.Add (leaf);
	} catch (const GS::Exception&) {
		leaf->~Leaf ();
		FixedAllocator::Deallocate (leaf);
		throw;
	}
	return leaf;
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline typename KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Leaf*	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::CreateLeaf (const KeyType& key)
{
	static_assert (sizeof (AllocatedNode) <= sizeof (Node), "nodeSize");
	m_allocatedNodeChain = new (m_allocator->nodeAllocator.Allocate ()) AllocatedNode (m_allocatedNodeChain);
	Leaf* leaf = new (m_allocator->leafAllocator.Allocate ()) Leaf (this, key);
	try {
		m_elemLeafMap.Add (leaf);
	} catch (const GS::Exception&) {
		leaf->~Leaf ();
		FixedAllocator::Deallocate (leaf);
		throw;
	}
	return leaf;
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline typename KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Node*	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::CreateNode (NodeBase *left, NodeBase *right, USize totalLeafCount, const DimType &separatorVal)
{
	AllocatedNode* nextAllocatedNode = m_allocatedNodeChain->next;
	m_allocatedNodeChain->~AllocatedNode ();
	Node* node = new (m_allocatedNodeChain) Node (this, left, right, totalLeafCount, separatorVal);
	m_allocatedNodeChain = nextAllocatedNode;
	return node;
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::DestroyLeaf (Leaf *leaf)
{
	leaf->~Leaf ();
	FixedAllocator::Deallocate (leaf);
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
inline void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::DestroyNode (Node *node)
{
	node->~Node ();
	m_allocatedNodeChain = new (node) AllocatedNode (m_allocatedNodeChain);
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Put (const KeyType &key, const ElemType &elem)
{
	Leaf* storedLeaf;
	if (m_elemLeafMap.Get (elem, &storedLeaf)) {
		UpdateKey (StoredElemPtr (&storedLeaf->GetAssoc ().GetElem ()), key);
	} else {
		try {
			DBASSERT (m_elemLeafMap.CanAdd (elem));
			Leaf* leaf = CreateLeaf (key, elem);
			try {
				m_leavesToAdd.Push (leaf);
				leaf->SetAddListIndex (m_leavesToAdd.GetSize ());
			} catch (const GS::Exception&) {
				DestroyLeaf (leaf);
			}

			Update<KDTreeNormalUpdate> ();
		} catch (const GS::Exception&) {
			DBBREAK ();
			Clear ();
			throw;
		}
	}
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
void KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::CleanUpDelayedData ()
{

	for (UInt32 i = 0; i < m_leavesToAdd.GetSize (); ++i) {
		if (m_leavesToAdd [i] != nullptr) {
			DestroyLeaf (m_leavesToAdd [i]);
		}
	}
	m_leavesToAdd.Clear (UpdateMode == KDTreeLazyUpdate);

	m_leavesToDelete.Clear (UpdateMode == KDTreeLazyUpdate);
	m_updatedLeafCount = 0;

	while (m_allocatedNodeChain != nullptr) {
		AllocatedNode* nextAllocatedNode = m_allocatedNodeChain->next;
		m_allocatedNodeChain->~AllocatedNode ();
		FixedAllocator::Deallocate (m_allocatedNodeChain);
		m_allocatedNodeChain = nextAllocatedNode;
	}

	m_updatedLeafIndices.Clear (UpdateMode == KDTreeLazyUpdate);
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
class KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::SplitComparer {
private:
	const short dimIdx;
public:
	SplitComparer (short dimIdx) : dimIdx (dimIdx) {}

	bool operator () (const Leaf* leaf, const DimType& dimValue) const
	{
		return leaf->GetAssoc ().GetKey ().GetDimVal (dimIdx) < dimValue;
	}

	bool operator () (const DimType& dimValue, const Leaf* leaf) const
	{
		return dimValue < leaf->GetAssoc ().GetKey ().GetDimVal (dimIdx);
	}
};


#if defined (_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4127 )
#endif


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
template <bool DeleteAll>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::RecursiveDeleteTree (NodeBasePtr nb)
{
	if (nb != nullptr) {
		if (nb->IsLeaf ()) {
			Leaf* leaf = nb->ToLeaf ();
			if (DeleteAll || (leaf->GetSearchIndex () & DeletedLeafBit) != 0) {
				DestroyLeaf (leaf);
			}
		} else {
			Node *node = nb->ToNode ();

			RecursiveDeleteTree<DeleteAll> (node->GetLeft ());
			RecursiveDeleteTree<DeleteAll> (node->GetRight ());

			DestroyNode (node);
		}
	}
}


template <LeafCount ListLeafCount, typename BidirectionalIteratorType, typename PredType>
static BidirectionalIteratorType	PartitionList (BidirectionalIteratorType first,
												   BidirectionalIteratorType last,
												   PredType pred)
{
	if (ListLeafCount == LeafCountOne) {
		if (pred (*first)) {
			return last;
		} else {
			return first;
		}
	} else {
		DBASSERT (ListLeafCount == LeafCountMoreThanOne);
		return GS::Partition (first, last, pred);
	}
}


// Split a list of elems to < == and > parts
template <LeafCount ListLeafCount, typename BidirectionalIteratorType, typename CmpType, typename SplitValueType>
static void	SplitList (BidirectionalIteratorType first,
					   BidirectionalIteratorType last,
					   const SplitValueType& splitValue,
					   CmpType cmp,
					   BidirectionalIteratorType& firstEqual,
					   BidirectionalIteratorType& lastEqual)
{
	if (ListLeafCount == LeafCountOne) {
		if (!cmp (splitValue, *first)) {
			firstEqual = lastEqual = first + 1;
		} else {
			firstEqual = lastEqual = first;
		}
	} else {
		DBASSERT (ListLeafCount == LeafCountMoreThanOne);

#ifdef CHECKED_VERSION
		const BidirectionalIteratorType origFirst	= first;
		const BidirectionalIteratorType origLast	= last;

		// 	GS::Array<ValueType> savedList;
		// 	for (BidirectionalIteratorType it = origFirst; it != origLast; ++it) {
		// 		savedList.Push (*it);
		// 	}
		//
		// 	BidirectionalIteratorType targetIt = origFirst;
		// 	for (UInt32 i = 0; i < savedList.GetSize (); ++i) {
		// 		*targetIt = savedList [i];
		// 		++targetIt;
		// 	}
		// 	first = origFirst;
		// 	last = origLast;

#endif
		// Partition by cmp (val, splitValue). Separator is first (== last) after the loop.
		// During partitioning move !cmp (val, splitValue) && ! cmp (splitValue, val) elems to the end of the list. These elems are between firstEqual and lastEqual after the loop.
		firstEqual = last;
		lastEqual = last;
		for (;;) {
			while (first != last) {
				if (cmp (*first, splitValue)) {
					++first;
				} else if (!cmp (splitValue, *first)) {
					if (last == firstEqual) {
						--last;
					}
					--firstEqual;
					GS::Swap (*first, *firstEqual);
				} else {
					goto continue1;
				}
			}
			break;

continue1:
			--last;
			while (first != last) {
				if (cmp (splitValue, *last)) {
					--last;
				} else if (!cmp (*last, splitValue)) {
					--firstEqual;
					GS::Swap (*firstEqual, *last);
					--last;
				} else {
					goto continue2;
				}
			}
			break;

continue2:

			GS::Swap (*first,*last);

			++first;
		}

		// move !cmp (val, splitValue) && ! cmp (splitValue, val) to the middle of the list
		while (firstEqual != lastEqual && last != firstEqual) {
			--lastEqual;
			GS::Swap (*lastEqual, *last);
			++last;
		}

		if (firstEqual == lastEqual) {
			lastEqual = last;
		}
		firstEqual = first;

#ifdef CHECKED_VERSION
		BidirectionalIteratorType it = origFirst;
		for (; it != firstEqual; ++it) {
			DBASSERT (cmp (*it, splitValue));
		}
		for (; it != lastEqual; ++it) {
			DBASSERT (!cmp (*it, splitValue) && !cmp (splitValue, *it));
		}
		for (; it != origLast; ++it) {
			DBASSERT (cmp (splitValue, *it));
		}
#endif
	}
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
class KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::LeafIndexSmaller
{
private:
	UInt64 value;
public:
	LeafIndexSmaller (UInt64 value) : value (value) {}

	bool operator () (const Leaf* leaf)
	{
		return leaf->GetSearchIndex () < value;
	}
};


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
void KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::MoveLeafToAddList (Leaf* leaf, UInt32& lastLeafToAdd)
{
	DBASSERT ((leaf->GetSearchIndex () & DeletedLeafBit) == 0);
	DBASSERT ((leaf->GetSearchIndex () & UpdatedLeafBit) == 0);

	if (lastLeafToAdd < m_leavesToAdd.GetSize ()) {
		m_leavesToAdd [lastLeafToAdd] = leaf;
	} else {
		m_leavesToAdd.Push (leaf);
	}
	++lastLeafToAdd;
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
void KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::RemoveLeaf (Leaf* leaf)
{
	if ((leaf->GetSearchIndex () & DeletedLeafBit) != 0) {
		DestroyLeaf (leaf);
	} else {
		DBASSERT ((leaf->GetSearchIndex () & UpdatedLeafBit) != 0);
	}
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
template <LeafCount DeletedLeafCount>
void KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::UnlinkLeaf (Leaf* leaf, UInt32& lastLeafToAdd)
{
	if (DeletedLeafCount == LeafCountZero) {
		MoveLeafToAddList (leaf, lastLeafToAdd);
	} else {
		switch (leaf->GetSearchIndex () & (DeletedLeafBit | UpdatedLeafBit)) {
			case DeletedLeafBit:
				DestroyLeaf (leaf);
#ifdef CHECKED_VERSION
				++m_removedLeafCount;
#endif
				break;
			case UpdatedLeafBit:
#ifdef CHECKED_VERSION
				++m_removedLeafCount;
#endif
				break;
			default:
				MoveLeafToAddList (leaf, lastLeafToAdd);
				break;
		}
	}
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
UInt64	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::RightIndex (UInt64 prevIndex, short depth)
{
	DBASSERT (depth < 62); // lowest bits is reserved for DeletedLeafBit and UpdatedLeafBit
	UInt64 rightIndex = 1;
	rightIndex <<= (63 - depth);
	rightIndex |= prevIndex;
	return rightIndex;
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
template <LeafCount DeletedLeafCount>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::RecursiveUnlinkSubtree (NodeBasePtr& nb, UInt32& lastLeafToAdd)
{
	Node* node = nb->ToNode ();
	if (node->GetLeft ()->IsLeaf ()) {
		UnlinkLeaf<DeletedLeafCount> (node->GetLeft ()->ToLeaf (), lastLeafToAdd);
	} else {
		RecursiveUnlinkSubtree<DeletedLeafCount> (node->GetLeft (), lastLeafToAdd);
	}

	if (node->GetRight ()->IsLeaf ()) {
		UnlinkLeaf<DeletedLeafCount> (node->GetRight ()->ToLeaf (), lastLeafToAdd);
	} else {
		RecursiveUnlinkSubtree<DeletedLeafCount> (node->GetRight (), lastLeafToAdd);
	}

	DestroyNode (node);
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
template <LeafCount PrevDeletedLeafCount, LeafCount PrevAddedLeafCount>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::RecursiveUpdateSwitch (NodeBasePtr& nb, short depth, UInt64 prevIndex,
																												   const UpdateData& updateData, NodeBuildStackData& newStackData)
{
	if (PrevDeletedLeafCount == LeafCountZero) {
		switch (PrevAddedLeafCount) {
			case LeafCountZero:
				DBBREAK ();
				return;
				break;
			case LeafCountOne:
				DBASSERT (updateData.lastLeafToAdd - updateData.firstLeafToAdd <= 1);
				if (updateData.lastLeafToAdd - updateData.firstLeafToAdd > 0) {
					RecursiveUpdate<LeafCountZero, LeafCountOne> (nb, depth, prevIndex, updateData, newStackData);
				}
				break;
			case LeafCountMoreThanOne:
				switch (updateData.lastLeafToAdd - updateData.firstLeafToAdd) {
				case 0:
					return;
				case 1:
					RecursiveUpdate<LeafCountZero, LeafCountOne> (nb, depth, prevIndex, updateData, newStackData);
					break;
				default:
					RecursiveUpdate<LeafCountZero, LeafCountMoreThanOne> (nb, depth, prevIndex, updateData, newStackData);
					break;
				}
				break;
		}
		return;
	}

	if (PrevAddedLeafCount == LeafCountZero) {
		switch (PrevDeletedLeafCount) {
			case LeafCountZero:
				DBBREAK ();
				return;
				break;
			case LeafCountOne:
				DBASSERT (updateData.lastLeafToDelete - updateData.firstLeafToDelete <= 1);
				if (updateData.lastLeafToDelete - updateData.firstLeafToDelete > 0) {
					RecursiveUpdate<LeafCountOne, LeafCountZero> (nb, depth, prevIndex, updateData, newStackData);
				}
				break;
			case LeafCountMoreThanOne:
				switch (updateData.lastLeafToDelete - updateData.firstLeafToDelete) {
				case 0:
					return;
				case 1:
					RecursiveUpdate<LeafCountOne, LeafCountZero> (nb, depth, prevIndex, updateData, newStackData);
					break;
				default:
					RecursiveUpdate<LeafCountMoreThanOne, LeafCountZero> (nb, depth, prevIndex, updateData, newStackData);
					break;
				}
				break;
		}
		return;
	}

	switch (updateData.lastLeafToDelete - updateData.firstLeafToDelete)
	{
		case 0:
			switch (updateData.lastLeafToAdd - updateData.firstLeafToAdd) {
				case 0:
					break;
				case 1:
					RecursiveUpdate<LeafCountZero, LeafCountOne> (nb, depth, prevIndex, updateData, newStackData);
					break;
				default:
					RecursiveUpdate<LeafCountZero, LeafCountMoreThanOne> (nb, depth, prevIndex, updateData, newStackData);
					break;
			}
		break;
		case 1:
			switch (updateData.lastLeafToAdd - updateData.firstLeafToAdd) {
				case 0:
					RecursiveUpdate<LeafCountOne, LeafCountZero> (nb, depth, prevIndex, updateData, newStackData);
					break;
				case 1:
					RecursiveUpdate<LeafCountOne, LeafCountOne> (nb, depth, prevIndex, updateData, newStackData);
					break;
				default:
					RecursiveUpdate<LeafCountOne, LeafCountMoreThanOne> (nb, depth, prevIndex, updateData, newStackData);
					break;
			}
		break;

		default:
			switch (updateData.lastLeafToAdd - updateData.firstLeafToAdd) {
				case 0:
					RecursiveUpdate<LeafCountMoreThanOne, LeafCountZero> (nb, depth, prevIndex, updateData, newStackData);
					break;
				case 1:
					RecursiveUpdate<LeafCountMoreThanOne, LeafCountOne> (nb, depth, prevIndex, updateData, newStackData);
					break;
				default:
					RecursiveUpdate<LeafCountMoreThanOne, LeafCountMoreThanOne> (nb, depth, prevIndex, updateData, newStackData);
					break;
			}
		break;
	}

}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
template <LeafCount DeletedLeafCount, LeafCount AddedLeafCount>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::RecursiveUpdate (NodeBasePtr& nb, short depth, UInt64 prevIndex,
																											 const UpdateData& updateData, NodeBuildStackData& newStackData)
{
	if (nb->IsLeaf ()) {
		UInt32 lastLeafToAdd = updateData.lastLeafToAdd;
		if (DeletedLeafCount == LeafCountZero) {
			MoveLeafToAddList (nb->ToLeaf (), lastLeafToAdd);
		} else {
			RemoveLeaf (nb->ToLeaf ());
		}
		RecursiveBuildBalancedSubtree (nb, depth, prevIndex, m_leavesToAdd.GetContent () + updateData.firstLeafToAdd, m_leavesToAdd.GetContent () + lastLeafToAdd, newStackData);
	} else {
		Node* node = nb->ToNode ();

		const UInt64 rightIndex = RightIndex (prevIndex, depth);

		UpdateData leftUpdateData;
		UpdateData rightUpdateData;

		USize leftLeafCount = (node->GetLeft ()->IsLeaf () ? 1 : node->GetLeft ()->ToNode ()->GetTotalLeafCount ());
		USize rightLeafCount = (node->GetRight ()->IsLeaf () ? 1 : node->GetRight ()->ToNode ()->GetTotalLeafCount ());

		if (DeletedLeafCount != LeafCountZero) {
			Leaf** firstGreaterOrEqualLeafToDelete = PartitionList<DeletedLeafCount> (updateData.firstLeafToDelete,
																					  updateData.lastLeafToDelete,
																					  LeafIndexSmaller (rightIndex));

			leftUpdateData.firstLeafToDelete	= updateData.firstLeafToDelete;
			leftUpdateData.lastLeafToDelete		= firstGreaterOrEqualLeafToDelete;

			rightUpdateData.firstLeafToDelete	= firstGreaterOrEqualLeafToDelete;
			rightUpdateData.lastLeafToDelete	= updateData.lastLeafToDelete;

			leftLeafCount -= static_cast<UInt32> (leftUpdateData.lastLeafToDelete - leftUpdateData.firstLeafToDelete);
			rightLeafCount -= static_cast<UInt32> (rightUpdateData.lastLeafToDelete - rightUpdateData.firstLeafToDelete);
		}

		if (AddedLeafCount != LeafCountZero) {
			Leaf** firstEqualLeafToAdd;
			Leaf** lastEqualLeafToAdd;
			SplitList<AddedLeafCount> (m_leavesToAdd.GetContent () + updateData.firstLeafToAdd, m_leavesToAdd.GetContent () + updateData.lastLeafToAdd, node->GetSeparatorVal (),
									   SplitComparer (depth % DimCnt), firstEqualLeafToAdd, lastEqualLeafToAdd);

			UInt32 splitIndex = static_cast <UInt32> ((firstEqualLeafToAdd - m_leavesToAdd.GetContent ()) + (lastEqualLeafToAdd - firstEqualLeafToAdd) / 2);

			rightUpdateData.firstLeafToAdd	= splitIndex;
			leftUpdateData.firstLeafToAdd	= updateData.firstLeafToAdd;

			leftLeafCount += splitIndex - updateData.firstLeafToAdd;
			rightLeafCount += updateData.lastLeafToAdd - splitIndex;
		} else {
			rightUpdateData.firstLeafToAdd	= updateData.firstLeafToAdd;
			leftUpdateData.firstLeafToAdd	= updateData.firstLeafToAdd;
		}

		USize minLeafCount, maxLeafCount;
		if (leftLeafCount < rightLeafCount) {
			minLeafCount = leftLeafCount;
			maxLeafCount = rightLeafCount;
		} else {
			minLeafCount = rightLeafCount;
			maxLeafCount = leftLeafCount;
		}

		DBASSERT (leftLeafCount + rightLeafCount != 0);
		if (minLeafCount * 2 < maxLeafCount) {
			UInt32 addListCapacity = updateData.lastLeafToAdd + node->GetTotalLeafCount ();
			if (DeletedLeafCount != LeafCountZero) {
				addListCapacity -= static_cast<UInt32> (updateData.lastLeafToDelete - updateData.firstLeafToDelete);
			}
			m_leavesToAdd.SetCapacity (addListCapacity);

#ifdef CHECKED_VERSION
			m_removedLeafCount = 0;
#endif
			UInt32 lastLeafToAdd = updateData.lastLeafToAdd;
			RecursiveUnlinkSubtree<DeletedLeafCount> (nb, lastLeafToAdd);
#ifdef CHECKED_VERSION
			if (DeletedLeafCount != LeafCountZero) {
				DBASSERT (m_removedLeafCount == static_cast<UInt32> (updateData.lastLeafToDelete - updateData.firstLeafToDelete));
			} else {
				DBASSERT (m_removedLeafCount == 0);
			}
			DBASSERT (leftLeafCount  + rightLeafCount == lastLeafToAdd - updateData.firstLeafToAdd);
#endif
			RecursiveBuildBalancedSubtree (nb, depth, prevIndex, m_leavesToAdd.GetContent () + updateData.firstLeafToAdd, m_leavesToAdd.GetContent () + lastLeafToAdd, newStackData);
		} else {
			 // go right first, because RecursiveUpdate might overwrite leaves after lastLeafToAdd

			rightUpdateData.lastLeafToAdd	= updateData.lastLeafToAdd;
			NodeBuildStackData leftStackData;
			RecursiveUpdateSwitch<DeletedLeafCount, AddedLeafCount> (node->GetRight (), depth + 1, rightIndex, rightUpdateData, leftStackData);

			leftUpdateData.lastLeafToAdd	= rightUpdateData.firstLeafToAdd;			
			RecursiveUpdateSwitch<DeletedLeafCount, AddedLeafCount> (node->GetLeft (), depth + 1, prevIndex, leftUpdateData, newStackData);

			NodeIndexType::Merge (depth % DimCnt, node, newStackData, leftStackData);

#ifdef CHECKED_VERSION
			const USize resLeftLeafCount = (node->GetLeft ()->IsLeaf () ? 1 : node->GetLeft ()->ToNode ()->GetTotalLeafCount ());
			const USize resRightLeafCount = (node->GetRight ()->IsLeaf () ? 1 : node->GetRight ()->ToNode ()->GetTotalLeafCount ());
			DBASSERT (resLeftLeafCount == leftLeafCount);
			DBASSERT (resRightLeafCount == rightLeafCount);
#endif
			node->SetTotalLeafCount (leftLeafCount + rightLeafCount);
		}
	}
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
template <KDTreeUpdateMode ActUpdateMode>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Update () const
{
	if (UpdateMode != ActUpdateMode) {
		return;
	}

	const_cast<KDTree*> (this)->UpdateNotConst ();
}

#if defined (_MSC_VER)
#pragma warning( pop )
#endif


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::UpdateNotConst ()
{

	if (m_leavesToAdd.IsEmpty () && m_leavesToDelete.IsEmpty ()) {
		return;
	}

	if (m_root == nullptr) {
		DBASSERT (!m_leavesToAdd.IsEmpty ());
		NodeBuildStackData stackData;
		RecursiveBuildBalancedSubtree (m_root, 0, 0, m_leavesToAdd.GetContent (), m_leavesToAdd.GetContent () + m_leavesToAdd.GetSize (), stackData);
	} else if (m_leavesToDelete.GetSize () == (m_root->IsLeaf () ? 1 : m_root->ToNode ()->GetTotalLeafCount ())) {
		for (UInt32 i = 0; i < m_leavesToDelete.GetSize (); ++i) {
			Leaf* leaf = m_leavesToDelete [i];
			if ((leaf->GetSearchIndex () & UpdatedLeafBit) != 0) {
				leaf->SetSearchIndex (leaf->GetSearchIndex () & (~UpdatedLeafBit));
				m_leavesToAdd.Push (m_leavesToDelete [i]);
			}
		}
		RecursiveDeleteTree<false /*DeleteAll*/> (m_root);
		if (!m_leavesToAdd.IsEmpty ()) {
			NodeBuildStackData stackData;
			RecursiveBuildBalancedSubtree (m_root, 0, 0, m_leavesToAdd.GetContent (), m_leavesToAdd.GetContent () + m_leavesToAdd.GetSize (), stackData);
		} else {
			m_root = nullptr;
		}
	} else {
		m_updatedLeafIndices.SetCapacity (m_updatedLeafCount);
		for (UInt32 i = 0; i < m_leavesToDelete.GetSize (); ++i) {
			if ((m_leavesToDelete [i]->GetSearchIndex () & UpdatedLeafBit) != 0) {
				m_leavesToAdd.Push (m_leavesToDelete [i]);
				m_allocatedNodeChain = new (m_allocator->nodeAllocator.Allocate ()) AllocatedNode (m_allocatedNodeChain);
			}
		}

		UpdateData updateData;
		updateData.firstLeafToAdd		= 0;
		updateData.lastLeafToAdd		= m_leavesToAdd.GetSize ();
		updateData.firstLeafToDelete	= m_leavesToDelete.GetContent ();
		updateData.lastLeafToDelete		= m_leavesToDelete.GetContent () + m_leavesToDelete.GetSize ();

		NodeBuildStackData stackData;
		RecursiveUpdateSwitch<LeafCountMoreThanOne, LeafCountMoreThanOne> (m_root, 0, 0, updateData, stackData);

		// An updated leaf might be removed from its original location after it was reinserted to its new location.
		// Because of this the search index update of updated leaves is delayed.
		DBASSERT (m_updatedLeafCount == m_updatedLeafIndices.GetSize ());
		for (UInt32 i = 0; i < m_updatedLeafIndices.GetSize (); ++i) {
			m_updatedLeafIndices [i].first->SetSearchIndex (m_updatedLeafIndices [i].second);
		}
	}
	m_leavesToAdd.Clear (true);

	CleanUpDelayedData ();

#ifdef CHECKED_VERSION
	++m_modificationStamp;
#endif
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::DeleteLeaf (Leaf* leaf)
{
	UInt32 addListIndex = leaf->GetAddListIndex ();
	--addListIndex;
	m_elemLeafMap.Delete (leaf);
	if (addListIndex < m_leavesToAdd.GetSize () && leaf == m_leavesToAdd [addListIndex]) {
		m_leavesToAdd [addListIndex] = m_leavesToAdd.GetLast ();
		m_leavesToAdd [addListIndex]->SetAddListIndex (addListIndex + 1);
		m_leavesToAdd.Pop ();
		DestroyLeaf (leaf);
		AllocatedNode* nextAllocatedNode = m_allocatedNodeChain->next;
		m_allocatedNodeChain->~AllocatedNode ();
		FixedAllocator::Deallocate (m_allocatedNodeChain);
		m_allocatedNodeChain = nextAllocatedNode;
	} else {
		if ((leaf->GetSearchIndex () & UpdatedLeafBit) != 0) {
			--m_updatedLeafCount;
			leaf->SetSearchIndex (leaf->GetSearchIndex () & (~UpdatedLeafBit));
		} else {
			m_leavesToDelete.Push (leaf);
		}
		leaf->SetSearchIndex (leaf->GetSearchIndex () | DeletedLeafBit);
	}
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
typename KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Leaf*
	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::GetLeafPtrFromStoredElemPtr (const StoredElemPtr& elemPtr)
{
	const KeyElemPair* pair = reinterpret_cast<const KeyElemPair*> (reinterpret_cast<const char*>(elemPtr.ptr) - offsetof (KeyElemPair, m_elem));
	Leaf* leaf = const_cast<Leaf*> (reinterpret_cast<const Leaf*> (reinterpret_cast<const char*>(pair) - offsetof (Leaf, m_assoc)));
	return leaf;
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::RecursiveEnumerateAndUnlinkSubTree (NodeBasePtr& nb)
{
	if (nb->IsLeaf ()) {
		m_leavesToAdd.Push (nb->ToLeaf ());
	} else {
		Node *node = nb->ToNode ();
		RecursiveEnumerateAndUnlinkSubTree (node->GetLeft ());
		RecursiveEnumerateAndUnlinkSubTree (node->GetRight ());

		DestroyNode (node);
	}
	nb = nullptr;
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
template <typename QueryType>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::CustomQuery (QueryType& query) const
{
	IncQueryCount ();

	Update<KDTreeLazyUpdate> ();

#ifdef CHECKED_VERSION
	UInt64 savedModificationStamp = m_modificationStamp;
#endif

	if (m_root) {
		const NodeBase* node = m_root;
		query (node);
	}

	DBASSERT (m_modificationStamp == savedModificationStamp);
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
template <typename QueryType>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::CustomQuery (QueryType& query)
{
	IncQueryCount ();

	Update<KDTreeLazyUpdate> ();

#ifdef CHECKED_VERSION
	UInt64 savedModificationStamp = m_modificationStamp;
#endif

	if (m_root) {
		NodeBase* node = m_root;
		query (node);
	}

	DBASSERT (m_modificationStamp == savedModificationStamp);
}


template <typename KeyType,
		  typename ElemType,
		  KDTreeNodeBounds NodeBoundsMode,
		  KDTreeUpdateMode UpdateMode,
		  KDTreeElemSetType ElemSetType,
		  KDTreeStatistics StatisticsMode>
class	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::LeafComparer
{
public:

	LeafComparer (short dimIdx, const ElemComparer& leafElemCmp) :
		m_dimIdx (dimIdx),
		m_leafElemCmp (leafElemCmp)
	{
	}


	bool	operator () (const Leaf *l1, const Leaf *l2)
	{
		auto leaf1KeyDimVal = l1->GetAssoc ().GetKey ().GetDimVal (m_dimIdx);
		auto leaf2KeyDimVal = l2->GetAssoc ().GetKey ().GetDimVal (m_dimIdx);
		if (leaf1KeyDimVal < leaf2KeyDimVal) {
			return true;
		} else if (leaf1KeyDimVal > leaf2KeyDimVal) {
			return false;
		} else {
			const ElemType& leaf1Elem = l1->GetAssoc ().GetElem ();
			const ElemType& leaf2Elem = l2->GetAssoc ().GetElem ();
			return m_leafElemCmp (leaf1Elem, leaf2Elem);
		}
	}

private:
	short	m_dimIdx;
	const ElemComparer&	m_leafElemCmp;
};


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
template <typename LeafRandomAccesIteratorType>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::RecursiveBuildBalancedSubtree (NodeBasePtr &nb,
																							short depth,
																							UInt64 prevIndex,
																							const LeafRandomAccesIteratorType& first,
																							const LeafRandomAccesIteratorType& last,
																							NodeBuildStackData& stackData)
{
	const UInt64 rightIndex = RightIndex (prevIndex, depth);
	const UInt32 leafCount = static_cast<UInt32> (last - first);

	if (leafCount == 1) {
		Leaf* leaf = *first;
		if ((leaf->GetSearchIndex () & UpdatedLeafBit) == 0) {
			leaf->SetSearchIndex (rightIndex);
		} else {
			m_updatedLeafIndices.Push (LeafIndexPair (leaf, rightIndex));
		}
		nb = leaf;
		DBASSERT ((rightIndex & DeletedLeafBit) == 0);
		DBASSERT ((rightIndex & UpdatedLeafBit) == 0);
		stackData.SetupFromKey (leaf->GetAssoc ().GetKey ());
	} else {
		const short dimIdx = depth % DimCnt;

		// Split value can be taken as either "max of left", or "min of right".
		// For box trees it is better to take "min of right" for min dimension (even dimIdx), and "max of left" for max dimension (odd dimIdx) nodes.
		const USize offset = dimIdx & 0x1;

		LeafRandomAccesIteratorType median (first + leafCount / 2 - offset);		
		GS::NthElement (first, median, last, LeafComparer (dimIdx, m_leafElemComparer));

		Node* newNode = CreateNode (nullptr, nullptr, leafCount, (*median)->GetAssoc ().GetKey ().GetDimVal (dimIdx));
		nb = newNode;

		RecursiveBuildBalancedSubtree (newNode->GetLeft (), depth + 1, prevIndex, first, median + offset, stackData);
		NodeBuildStackData rightStackData;
		RecursiveBuildBalancedSubtree (newNode->GetRight (), depth + 1, rightIndex, median + offset, last, rightStackData);

		NodeIndexType::Merge (dimIdx, newNode, stackData, rightStackData);
	}
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
bool	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::Check () const
{
	Update<KDTreeLazyUpdate> ();

	DimType	min [DimCnt];
	bool	minSet [DimCnt] = {0};
	DimType	max [DimCnt];
	bool	maxSet [DimCnt] = {0};

	NodeBuildStackData stackData;
	return m_root == nullptr || RecursiveCheck (m_root, 0, min, minSet, max, maxSet, stackData);
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
bool	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::RecursiveCheck (const NodeBase* nb, short dimIdx,
																				   DimType* min, bool* minSet, DimType* max, bool* maxSet,
																				   NodeBuildStackData& stackData) const
{
	bool success = true;
	if (nb->IsLeaf ()) {
		const Leaf* leaf = nb->ToLeaf ();
		const KeyType& key = leaf->GetAssoc ().GetKey ();
		for (short i = 0; i < DimCnt; ++i) {
			success = success && DBVERIFY (!minSet [i] || !(key.GetDimVal (i) < min [i]));
			success = success && DBVERIFY (!maxSet [i] || !(max [i] < key.GetDimVal (i)));
		}		
		success = success && DBVERIFY (m_elemLeafMap.Check (leaf));
		stackData.SetupFromKey (key);
	} else {
		const Node* node = nb->ToNode ();
		const USize leftLeafCount = (node->GetLeft ()->IsLeaf () ? 1 : node->GetLeft ()->ToNode ()->GetTotalLeafCount ());
		const USize rightLeafCount = (node->GetRight ()->IsLeaf () ? 1 : node->GetRight ()->ToNode ()->GetTotalLeafCount ());
		success = success && DBVERIFY (node->GetTotalLeafCount () == leftLeafCount + rightLeafCount);
		const short nextDim = NextDim (dimIdx);
		{
			bool savedMaxSet	= maxSet [dimIdx];
			DimType savedMax	= max [dimIdx];
			success = success && DBVERIFY (!maxSet [dimIdx] || !(max [dimIdx] < node->GetSeparatorVal ()));
			maxSet [dimIdx]		= true;
			max [dimIdx]		= node->GetSeparatorVal ();

			success = success && DBVERIFY (RecursiveCheck (node->GetLeft (), nextDim, min, minSet, max, maxSet, stackData));

			max [dimIdx]		= savedMax;
			maxSet [dimIdx]		= savedMaxSet;
		}
		NodeBuildStackData rightStackData;
		{
			bool savedMinSet	= minSet [dimIdx];
			DimType savedMin	= min [dimIdx];
			success = success && DBVERIFY (!minSet [dimIdx] || !(node->GetSeparatorVal () < min [dimIdx]));
			minSet [dimIdx]		= true;
			min [dimIdx]		= node->GetSeparatorVal ();

			success = success && DBVERIFY (RecursiveCheck (node->GetRight (), nextDim, min, minSet, max, maxSet, rightStackData));

			min [dimIdx]		= savedMin;
			minSet [dimIdx]		= savedMinSet;
		}
		NodeIndexType::Check (dimIdx, node, stackData, rightStackData);
	}
	return success;
}


template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::RecursiveDump (const NodeBase *nb, USize currLevel, GS::Array<GS::Array<const NodeBase *> > &lineArray) const
{
	DBASSERT (nb);

	if (lineArray.GetSize () <= currLevel) {
		DBASSERT (lineArray.GetSize () == currLevel);
		lineArray.Push (GS::Array<const NodeBase *> ());
	}
	lineArray[currLevel].Push (nb);

	if (!nb->IsLeaf ()) {
		const Node *node = nb->ToNode ();
		RecursiveDump (node->GetLeft (), currLevel + 1, lineArray);
		RecursiveDump (node->GetRight (), currLevel + 1, lineArray);
	}
}

template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::ResetStatistics () const
{
	m_statistics.Reset ();
}

template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::PrintStatistics () const
{
	m_statistics.Print ();
}

template <typename KeyType, typename ElemType, KDTreeNodeBounds NodeBoundsMode, KDTreeUpdateMode UpdateMode, KDTreeElemSetType ElemSetType, KDTreeStatistics StatisticsMode>
void	KDTree<KeyType, ElemType, NodeBoundsMode, UpdateMode, ElemSetType, StatisticsMode>::IncQueryCount () const
{
	m_statistics.IncQueryCount ();
}


}	// namespace Geometry


#endif	//KDTREE_HPP
