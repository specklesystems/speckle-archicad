// *****************************************************************************
// File:			QuadTreeImplN.hpp
//
// Contact person:	NZ
//
// SG compatible
// *****************************************************************************

#ifndef QUADTREEIMPLN_HPP
#define QUADTREEIMPLN_HPP

#pragma once

#include "QuadTreeUtils.hpp"

#include "GSException.hpp"

#include "Array.hpp"
#include "PagedArray.hpp"

#include "Ref.hpp"

#include "SmallObj.hpp"
#include "ThreadingDebug.hpp"


namespace QuadTreeN {

const double		MinCellWidth = 0.1;
const USize			GrowMinSize = 64;
const USize			ShrinkMinSize = 32;


template <int I, class Type, template <class, class>class Container, class Comparator>
class Cell;

template <int I, class Type, template <class, class>class Container, class Comparator>
class ElemAndItsParentCell;

template <int I, class Type, template <class, class>class Container, class Comparator>
class TreeImpl;


// --- ElemAndItsParentCell ----------------------------------------------------

template <int I, class Type, template <class, class>class Container, class Comparator>
class ElemAndItsParentCell {
public:
	Type			data;
	Box<I>			box;
	Cell<I, Type, Container, Comparator>*	parent;

public:
	void operator delete (void* ptr)
	{
		FixedAllocator::Deallocate (ptr);
	}

	void operator delete (void* ptr, void*)
	{
		FixedAllocator::Deallocate (ptr);
	}

	ElemAndItsParentCell ()
	{
	}

	ElemAndItsParentCell (const Box<I>& box, const Type& data):
		data (data),
		box (box),
		parent (nullptr)
	{
	}
};


// --- PlainCell ---------------------------------------------------------------

template <int I, class Type, template <class, class>class Container, class Comparator>
class PlainCell {
public:
	const Box<I>	box;
	USize			elemCount;

private:
	PlainCell& operator= (const PlainCell&);

public:
	PlainCell (const Box<I>& box):
		box (box),
		elemCount (0)
	{
	}

	virtual ~PlainCell ()
	{
	}

	virtual void Enumerate (OutputAdapter<Type>&) const
	{
	}

	virtual void Enumerate (IteratorController<I>&, OutputAdapter<Type>&) const
	{
	}

	virtual void Enumerate (BoxIteratorController<I>&, OutputAdapter<Type>&) const
	{
	}

	virtual void GetEnumeratedElemSize (USize*) const
	{
	}

	virtual void GetEnumeratedElemSize (IteratorController<I>&, USize*) const
	{
	}

	virtual void GetEnumeratedElemSize (BoxIteratorController<I>&, USize*) const
	{
	}

#ifdef CHECKED_VERSION
	bool CheckElemIsInsideBox (const Box<I>& elemBox) const
	{
		Box<I> inflatedBox = box;
		inflatedBox.Inflate (Tolerance);

		return inflatedBox.IsInside (elemBox);
	}
#endif

	virtual void InsertElemRef (ElemAndItsParentCell<I, Type, Container, Comparator>* GS_DEBUG_ONLY (elemRef))
	{
		DBASSERT (CheckElemIsInsideBox (elemRef->box));

		++elemCount;
	}

	virtual void DeleteElemRef (ElemAndItsParentCell<I, Type, Container, Comparator>* GS_DEBUG_ONLY (elemRef))
	{
		DBASSERT (CheckElemIsInsideBox (elemRef->box));

		--elemCount;
	}

	virtual bool CanContainElems () const
	{
		return false;
	}
};


// --- Cell --------------------------------------------------------------------

template <int I, class Type, template <class, class> class Container, class Comparator>
class Cell: public PlainCell<I, Type, Container, Comparator> {
	friend class TreeImpl<I, Type, Container, Comparator>;

private:
	static const UIndex		SubCellCount = 1 << I;
	static const UIndex		InvalidCellIndex = SubCellCount + 1;

private:
	Cell<I, Type, Container, Comparator>*				parentCell;
	const Point<I>										center;
	GS::Ref<PlainCell<I, Type, Container, Comparator>>	cells[SubCellCount];

	struct ComparePrivate {
		Comparator compare;
		bool operator()(const ElemAndItsParentCell<I, Type, Container, Comparator>* lhs,
						const ElemAndItsParentCell<I, Type, Container, Comparator>* rhs) const {
			return compare (lhs->data, rhs->data);
		}

		virtual ~ComparePrivate (){}
	};

	Container<ElemAndItsParentCell<I, Type, Container, Comparator>*, ComparePrivate> elems;

private:
	Cell& operator= (const Cell&);

private:

	virtual void Enumerate (OutputAdapter<Type>& outputAdapter) const override
	{
		outputAdapter.BlockBegin ();
		for (auto elemIterator = elems.Begin (); elemIterator != elems.End (); ++elemIterator) {
			outputAdapter.ElemFound ((*elemIterator)->data);
		}
		outputAdapter.BlockEnd ();
		for (UIndex i = 0; i < SubCellCount; ++i) {
			cells[i]->Enumerate (outputAdapter);
		}
	}

	virtual void GetEnumeratedElemSize (USize* size) const override
	{
		*size += elems.GetSize ();
		for (UIndex i = 0; i < SubCellCount; ++i) {
			cells[i]->GetEnumeratedElemSize (size);
		}
	}

GS_DEBUG_ONLY (public:)
		UIndex GetCellIndex (const Box<I>& box)
	{
		UIndex index = 0;
		for (UIndex i = 0; i < I; ++i) {
			const bool minGreater = box.Min (i) > center.coords[i];
			const bool maxGreater = box.Max (i) > center.coords[i];
			if (minGreater != maxGreater) {	// atlog a felezon
				return InvalidCellIndex;
			} else if (minGreater) {
				index += 1 << i;
			}
		}

		return index;
	}

private:
	Cell<I, Type, Container, Comparator>* TurnCellIntoRealOne (UIndex iCell)
	{
		Cell<I, Type, Container, Comparator>* cellPtr = new Cell (cells[iCell]->box, this);
		cells[iCell] = cellPtr;
		GS::ArrayFB<ElemAndItsParentCell<I, Type, Container, Comparator>*, GrowMinSize> movedElems;
		for (auto elemIterator = elems.Begin (); elemIterator != elems.End (); ++elemIterator) {
			if (GetCellIndex ((*elemIterator)->box) == iCell) {
				movedElems.Push (*elemIterator);
			}
		}
		for (UIndex iElem = 0; iElem < movedElems.GetSize (); ++iElem) {
			movedElems[iElem]->parent = nullptr;
			cellPtr->InsertElemRef (movedElems[iElem]);
			elems.Delete (movedElems[iElem]);
		}
		return cellPtr;
	}

	Box<I> OffsetBox (const Box<I>& box, const Point<I>& offset, UIndex forIndex)
	{
		Box<I> offsetBox = box;

		for (UIndex i = 0; i < I; ++i) {
			if (((1 << i) & forIndex) != 0) {
				offsetBox.Min (i) += offset.coords[i];
				offsetBox.Max (i) += offset.coords[i];
			}
		}

		return offsetBox;
	}

public:
	Cell (const Box<I>& box, Cell* parentCell):
		PlainCell<I, Type, Container, Comparator> (box),
		parentCell (parentCell),
		center (box.GetCenter ())
	{
		const Box<I> quaterBox (box.GetMins (), box.GetCenter ());
		const Point<I> diagonal = quaterBox.GetDiagonal ();
		for (UIndex i = 0; i < SubCellCount; ++i) {
			cells[i] = new PlainCell<I, Type, Container, Comparator> (OffsetBox (quaterBox, diagonal, i));
		}
	}

	virtual bool CanContainElems () const override
	{
		return true;
	}

	virtual void InsertElemRef (ElemAndItsParentCell<I, Type, Container, Comparator>* elemRef) override
	{
		DBASSERT ((PlainCell<I, Type, Container, Comparator>::CheckElemIsInsideBox (elemRef->box)));

		UIndex iCell = GetCellIndex (elemRef->box);
		if (iCell != InvalidCellIndex) {
			PlainCell<I, Type, Container, Comparator>* cellPtr = cells[iCell];
			cellPtr->InsertElemRef (elemRef);
			if (!cellPtr->CanContainElems ()) {
				if (cellPtr->elemCount == GrowMinSize && cellPtr->box.GetWidth (0) > MinCellWidth) {
					Cell<I, Type, Container, Comparator>* newCellPtr = TurnCellIntoRealOne (iCell);
					newCellPtr->InsertElemRef (elemRef);
				} else {
					elems.Insert (elemRef);
					DBASSERT (elemRef->parent == nullptr);
					elemRef->parent = this;
				}
			}
		} else {
			elems.Insert (elemRef);
			DBASSERT (elemRef->parent == nullptr);
			elemRef->parent = this;
		}
	}

	virtual void DeleteElemRef (ElemAndItsParentCell<I, Type, Container, Comparator>* elemRef) override
	{
		DBASSERT ((PlainCell<I, Type, Container, Comparator>::CheckElemIsInsideBox (elemRef->box)));

		elems.Delete (elemRef);
	}

	template <class T>
	void EnumerateT (T& iteratorController, OutputAdapter<Type>& outputAdapter) const
	{
		if (!iteratorController.DontVisit (PlainCell<I, Type, Container, Comparator>::box)) {
			outputAdapter.BlockBegin ();
			for (auto elemIterator = elems.Begin (); elemIterator != elems.End (); ++elemIterator) {
				if (!iteratorController.DontVisitElem ((*elemIterator)->box)) {
					outputAdapter.ElemFound ((*elemIterator)->data);
				}
			}
			outputAdapter.BlockEnd ();
			for (UIndex i = 0; i < SubCellCount; ++i) {
				if (iteratorController.VisitWithoutTesting (cells[i]->box)) {
					cells[i]->Enumerate (outputAdapter);
				} else {
					cells[i]->Enumerate (iteratorController, outputAdapter);
				}
			}
		}
	}

	virtual void Enumerate (IteratorController<I>& iteratorController,
							OutputAdapter<Type>& outputAdapter) const override
	{
		EnumerateT (iteratorController, outputAdapter);
	}

	virtual void Enumerate (BoxIteratorController<I>& boxIteratorController,
							OutputAdapter<Type>& outputAdapter) const override
	{
		EnumerateT (boxIteratorController, outputAdapter);
	}

	template <class T>
	void GetEnumeratedElemSizeT (T& iteratorController, USize* size) const
	{
		if (!iteratorController.DontVisit (PlainCell<I, Type, Container, Comparator>::box)) {
			for (auto elemIterator = elems.Begin (); elemIterator != elems.End (); ++elemIterator) {
				if (!iteratorController.DontVisit ((*elemIterator)->box)) {
					++(*size);
				}
			}
			for (UIndex i = 0; i < SubCellCount; ++i) {
				if (iteratorController.VisitWithTesting (cells[i]->box)) {
					cells[i]->GetEnumeratedElemSize (size);
				} else {
					cells[i]->GetEnumeratedElemSize (iteratorController, size);
				}
			}
		}
	}

	virtual void GetEnumeratedElemSize (IteratorController<I>& iteratorController,
										USize* size) const override
	{
		GetEnumeratedElemSizeT (iteratorController, size);
	}

	virtual void GetEnumeratedElemSize (BoxIteratorController<I>& boxIteratorController,
										USize* size) const override
	{
		GetEnumeratedElemSizeT (boxIteratorController, size);
	}


};


// --- TreeImpl ----------------------------------------------------------------

template <int I, class Type, template <class, class>class Container, class Comparator>
class TreeImpl: private NonThreadSafeClass {
protected:
	class ArrayOutputAdapter : public OutputAdapter<Type> {
	public:
		GS::Array<Type> array;

		ArrayOutputAdapter () {}

		ArrayOutputAdapter (USize size)
		{
			array = GS::Array<Type> (size);
		}

	public:
		virtual void ElemFound (const Type& elem) override
		{
			array.Push (elem);
		}
	};

private:
	FixedAllocator																allocator;
	GS::HashTable<Type, ElemAndItsParentCell<I, Type, Container, Comparator>*>	elemToParentHash;
	GS::HashTable<Type, ElemAndItsParentCell<I, Type, Container, Comparator>*>	elemsWithExtremeBounds;
	GS::Ref<Cell<I, Type, Container, Comparator>>								root;

private:
	static GS::Ref<Cell<I, Type, Container, Comparator>> GrowRootToFit (GS::Ref<Cell<I, Type, Container, Comparator>> root, const Box<I>& box)
	{
		if (root == nullptr) {
			double maxSize = MinCellWidth;
			for (UIndex i = 0; i < I; ++i) {
				maxSize = GS::Max (maxSize, box.GetWidth (i));
			}
			return new Cell<I, Type, Container, Comparator> (Box<I> (box.GetCenter (), maxSize + 2 * Tolerance), nullptr);
		} else if (root->box.IsInside (box)) {
			return root;
			//} else if (dynamic_cast<PlainCell*> (root) != nullptr && root->elemNum < GrowMin) {
			//	at kell siman meretezni a gyokeret
		} else {
			UIndex index = 0;
			Point<I> newCenter;
			for (UIndex i = 0; i < I; ++i) {
				if (box.Min (i) < root->box.Min (i)) {
					index += 1 << i;
					newCenter.coords[i] = root->box.Min (i);
				} else {
					newCenter.coords[i] = root->box.Max (i);
				}
			}

			GS::Ref<Cell<I, Type, Container, Comparator>> newRoot (new Cell<I, Type, Container, Comparator> (Box<I> (newCenter, 2.0 * root->box.GetWidth (0)), nullptr));

			DBASSERT (root->parentCell == nullptr);
			DBASSERT ((newRoot->GetCellIndex (root->box) == index || newRoot->GetCellIndex (root->box) == Cell<I, Type, Container, Comparator>::InvalidCellIndex));

			root->parentCell = newRoot;
			newRoot->cells[index] = root;

			return GrowRootToFit (newRoot, box);
		}
	}

public:
	TreeImpl ():
		allocator (sizeof (ElemAndItsParentCell<I, Type, Container, Comparator>))
	{
	}

	virtual ~TreeImpl ()
	{
		Clear ();
	}

	void InsertElem (const Box<I>& box, const Type& elem)
	{
		FUNCTIONCALLEDCHECKTHREAD ();

		DBASSERT (!Contains (elem));

		Box<I> inflatedBox = box;
		inflatedBox.Inflate (Tolerance);

		ElemAndItsParentCell<I, Type, Container, Comparator>* newElem = new (allocator.Allocate ()) ElemAndItsParentCell<I, Type, Container, Comparator> (inflatedBox, elem);
		if (inflatedBox.IsValid ()) {
			root = GrowRootToFit (root, inflatedBox);
			root->InsertElemRef (newElem);
			elemToParentHash.Add (elem, newElem);
		} else {
			elemsWithExtremeBounds.Add (elem, newElem);
		}
	}

	void Delete (const Type& elem)
	{
		FUNCTIONCALLEDCHECKTHREAD ();

		if (elemToParentHash.ContainsKey (elem)) {
			ElemAndItsParentCell<I, Type, Container, Comparator>* deletedElem = elemToParentHash[elem];
			Cell<I, Type, Container, Comparator>* deletedElemsParent = deletedElem->parent;
			deletedElemsParent->DeleteElemRef (deletedElem);
			delete deletedElem;
			elemToParentHash.Delete (elem);

			while ((deletedElemsParent->elems.GetSize () < ShrinkMinSize) && (deletedElemsParent != root)) {
				bool subCellStoresItems = false;
				for (UInt32 cellInd = 0; cellInd < Cell<I, Type, Container, Comparator>::SubCellCount; cellInd++) {
					subCellStoresItems |= deletedElemsParent->cells[cellInd]->CanContainElems ();
				}
				if (!subCellStoresItems) {
					UInt32 cellInd = 0;
					for (; cellInd < Cell<I, Type, Container, Comparator>::SubCellCount; cellInd++) {
						if (deletedElemsParent->parentCell->cells[cellInd] == deletedElemsParent) {
							for (auto elemIterator = deletedElemsParent->elems.Begin (); elemIterator != deletedElemsParent->elems.End (); ++elemIterator) {
								deletedElemsParent->parentCell->elems.Insert (*elemIterator);
								(*elemIterator)->parent = deletedElemsParent->parentCell;
							}
							PlainCell<I, Type, Container, Comparator>* newCell = new PlainCell<I, Type, Container, Comparator> (deletedElemsParent->box);
							deletedElemsParent = deletedElemsParent->parentCell;
							deletedElemsParent->cells[cellInd] = newCell;
							break;
						}
					}
					DBASSERT ((cellInd < Cell<I, Type, Container, Comparator>::SubCellCount));
				} else {
					break;
				}
			}
		} else {
			DBASSERT (elemsWithExtremeBounds.ContainsKey (elem));

			delete elemsWithExtremeBounds[elem];
			elemsWithExtremeBounds.Delete (elem);
		}
	}

	void Clear ()
	{
		for (auto elemIterator = elemToParentHash.EnumerateValues (); elemIterator != nullptr; ++elemIterator) {
			delete *elemIterator;
		}
		elemToParentHash.Clear ();
		for (auto elemIterator = elemsWithExtremeBounds.EnumerateValues (); elemIterator != nullptr; ++elemIterator) {
			delete *elemIterator;
		}
		elemsWithExtremeBounds.Clear ();
		root = nullptr;
	}

	template <class T>
	void Enumerate (T& iteratorController, OutputAdapter<Type>& outputAdapter) const
	{
		if (root != nullptr) {
			root->Enumerate (iteratorController, outputAdapter);
		}

		outputAdapter.BlockBegin ();
		for (auto elemIterator = elemsWithExtremeBounds.EnumerateValues (); elemIterator != nullptr; ++elemIterator) {
			if (!iteratorController.DontVisitElem ((*elemIterator)->box)) {
				outputAdapter.ElemFound ((*elemIterator)->data);
			}
		}
		outputAdapter.BlockEnd ();
	}

	template <class T>
	GS::Array<Type> Enumerate (T& iteratorController) const
	{
		ArrayOutputAdapter arrayOutputAdapter;

		Enumerate (iteratorController, arrayOutputAdapter);

		return arrayOutputAdapter.array;
	}

	template <class T>
	USize GetEnumeratedElemSize (T& iteratorController) const
	{
		USize retVal = 0;

		if (root != nullptr) {
			root->GetEnumeratedElemSize (iteratorController, &retVal);
		}

		for (auto elemIterator = elemsWithExtremeBounds.EnumerateValues (); elemIterator != nullptr; ++elemIterator) {
			if (!iteratorController.DontVisit ((*elemIterator)->box)) {
				++retVal;
			}
		}

		return retVal;
	}

	bool Contains (const Type& elem) const
	{
		return elemToParentHash.ContainsKey (elem) || elemsWithExtremeBounds.ContainsKey (elem);
	}

	USize GetSize () const
	{
		return elemToParentHash.GetSize () + elemsWithExtremeBounds.GetSize ();
	}

	Box<I> GetElemBox (const Type& elem) const
	{
		if (elemToParentHash.ContainsKey (elem)) {
			return elemToParentHash[elem]->box;
		} else {
			DBASSERT (elemsWithExtremeBounds.ContainsKey (elem));

			return elemsWithExtremeBounds[elem]->box;
		}
	}

	const Type&	GetElem (const Type& elem) const
	{
		if (elemToParentHash.ContainsKey (elem)) {
			return elemToParentHash.GetKey (elem);
		} else {
			DBASSERT (elemsWithExtremeBounds.ContainsKey (elem));

			return elemsWithExtremeBounds.GetKey (elem);
		}
	}

	void LeaveThread ()
	{
		NonThreadSafeClass::LeaveThread ();
		LEAVETHREAD (allocator);
	}

	class BatchWriteScope {
	public:
		BatchWriteScope (TreeImpl& tree):
			manualPurgeScope (new FixedAllocator::ManualPurgeScope (tree.allocator))
		{
		}

	private:
		GS::Owner<FixedAllocator::ManualPurgeScope> manualPurgeScope;
	};
};

} // namespace QuadTreeN


#endif // QUADTREEIMPLN_HPP
