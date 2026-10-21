#if !defined (SmoothPatchFinisher_H)
#define SmoothPatchFinisher_H
#pragma once

#include "HashSet.hpp"
#include "TrgMeshData.hpp"
#include "GeometricDefinitions.h"

#include <list>

//template<class T>
//class RingContainer
//{
//public:
//	typedef typename std::list<T>::iterator Iterator;
//	typedef typename std::list<T>::const_iterator ConstIterator;
//
//	RingContainer () {}
//	virtual ~RingContainer () {}
//
//	Iterator GetIterator () { return myList.begin(); }
//	ConstIterator GetIterator () const { return myList.begin(); }
//
//	void StepNext (Iterator & it) { ++it; if (it == myList.end ()) it = myList.begin(); }
//	void StepNext (ConstIterator & it) const { ++it; if (it == myList.end ()) it = myList.begin(); }
//
//	void StepPrevious (Iterator &it) { if (it == myList.begin ()) { it = myList.end(); } --it; }
//	void StepPrevious (ConstIterator &it) const { if (it == myList.begin ()) { it = myList.end(); } --it; }
//
//	void InsertAfter (Iterator &it, const T &val) { if (myList.empty ()) { myList.push_back (val); it = myList.begin (); } else it = myList.insert (++it, val); }
//	void InsertBefore (Iterator &it, const T &val) { it = myList.insert (it, val); }
//	void InsertAfter (ConstIterator &it, const T &val) { if (myList.empty ()) { myList.push_back(val); it = myList.begin (); } else it = myList.insert (++it, val); }
//	void InsertBefore (ConstIterator &it, const T &val) { it = myList.insert (it, val); }
//
//	void Erase (Iterator &it) { Iterator toErase = it; StepNext (it); myList.erase (toErase); }
//	void Erase (ConstIterator &it) { ConstIterator toErase = it; StepNext (it); myList.erase (toErase); }
//
//	USize GetSize () const { return static_cast<USize> (myList.size ()); }
//	void Clear () { myList.clear (); }
//private:
//	std::list<T> myList;
//};

template<class T>
class RingContainer
{
private:
	class LLNode;

public:
	class Iterator;
	class ConstIterator;

	class Iterator
	{
	public:
		Iterator () : ptr (nullptr) {}

		T* operator-> () const { DBASSERT (ptr!=nullptr); return &(ptr->val); }
		T& operator* () const  { DBASSERT (ptr!=nullptr); return ptr->val; }

		bool operator != (const Iterator & rhs) const { return ptr != rhs.ptr; }
		bool operator == (const Iterator & rhs) const { return ptr == rhs.ptr; }

		Iterator & operator ++ () { if (ptr != nullptr) ptr = ptr->next; return *this; }
		Iterator & operator -- () { if (ptr != nullptr) ptr = ptr->prev; return *this; }

		Iterator Next() { if (ptr != nullptr) return Iterator (ptr->next); return *this; }
		Iterator Prev() { if (ptr != nullptr) return Iterator (ptr->prev); return *this; }
	private:
		friend class RingContainer;
		friend class ConstIterator;
		explicit Iterator (LLNode *p) : ptr (p) {}
		LLNode * ptr;
	};

	class ConstIterator
	{
	public:
		ConstIterator () : ptr (nullptr) {}
		ConstIterator (const Iterator & src) : ptr (src.ptr) {}

		const T* operator-> () const { DBASSERT (ptr!=nullptr); return &(ptr->val); }
		const T& operator* () const  { DBASSERT (ptr!=nullptr); return ptr->val; }

		bool operator != (const ConstIterator & rhs) const { return ptr != rhs.ptr; }
		bool operator == (const ConstIterator & rhs) const { return ptr == rhs.ptr; }

		ConstIterator & operator ++ () { if (ptr != nullptr) ptr = ptr->next; return *this; }
		ConstIterator & operator -- () { if (ptr != nullptr) ptr = ptr->prev; return *this; }

		ConstIterator Next() { if (ptr != nullptr) return ConstIterator (ptr->next); return *this; }
		ConstIterator Prev() { if (ptr != nullptr) return ConstIterator (ptr->prev); return *this; }
	private:
		friend class RingContainer;
		explicit ConstIterator (LLNode *p) : ptr (p) {}
		LLNode * ptr;
	};

	RingContainer () : size (0), head (nullptr) {}
	virtual ~RingContainer () { Clear(); }

	RingContainer (const RingContainer&) = delete;

	Iterator GetIterator () { return Iterator (head); }
	ConstIterator GetIterator () const { return ConstIterator (head); }

	void InsertAfter (Iterator &it, const T &val)
	{
		LLNode * ths = it.ptr;
		if (ths == nullptr) {
			DBASSERT (head == nullptr);
			DBASSERT (size == 0);
			head = new LLNode (val);
			head->next = head;
			head->prev = head;
			size = 1;
			it.ptr = head;
			return;
		}


		++it;
		LLNode * nxt = it.ptr;
		DBASSERT (ths != nullptr);
		DBASSERT (nxt != nullptr);
		DBASSERT (ths->next == nxt);
		DBASSERT (nxt->prev == ths);

		head = new LLNode (val, nxt, ths);
		ths->next = head;
		nxt->prev = head;

		it.ptr = head;
		++size;
	}

	void InsertBefore (Iterator &it, const T &val)
	{
		LLNode * ths = it.ptr;
		if (ths == nullptr) {
			DBASSERT (head == nullptr);
			DBASSERT (size == 0);
			head = new LLNode (val);
			head->next = head;
			head->prev = head;
			size = 1;
			it.ptr = head;
			return;
		}
		--it;
		LLNode * prv = it.ptr;
		DBASSERT (ths != nullptr);
		DBASSERT (prv != nullptr);
		DBASSERT (ths->prev == prv);
		DBASSERT (prv->next == ths);

		head = new LLNode (val, ths, prv);
		ths->prev = head;
		prv->next = head;

		it.ptr = head;
		++size;
	}

	void InsertAfter (ConstIterator &it, const T &val)
	{
		LLNode * ths = it.ptr;
		if (ths == nullptr) {
			DBASSERT (head == nullptr);
			DBASSERT (size == 0);
			head = new LLNode (val);
			head->next = head;
			head->prev = head;
			size = 1;
			it.ptr = head;
			return;
		}
		++it;
		LLNode * nxt = it.ptr;
		DBASSERT (ths != nullptr);
		DBASSERT (nxt != nullptr);
		DBASSERT (ths->next == nxt);
		DBASSERT (nxt->prev == ths);

		head = new LLNode (val, nxt, ths);
		ths->next = head;
		nxt->prev = head;

		it.ptr = head;
		++size;
	}

	void InsertBefore (ConstIterator &it, const T &val)
	{
		LLNode * ths = it.ptr;
		if (ths == nullptr) {
			DBASSERT (head == nullptr);
			DBASSERT (size == 0);
			head = new LLNode (val);
			head->next = head;
			head->prev = head;
			size = 1;
			it.ptr = head;
			return;
		}
		--it;
		LLNode * prv = it.ptr;
		DBASSERT (ths != nullptr);
		DBASSERT (prv != nullptr);
		DBASSERT (ths->prev == prv);
		DBASSERT (prv->next == ths);

		head = new LLNode (val, ths, prv);
		ths->prev = head;
		prv->next = head;

		it.ptr = head;
		++size;
	}

	void Erase (Iterator &it)
	{
		LLNode * ths = it.ptr;
		if (ths == nullptr) return;

		LLNode * nxt = ths->next;
		LLNode * prv = ths->prev;
		DBASSERT (nxt != nullptr);
		DBASSERT (prv != nullptr);
		DBASSERT (nxt->prev == ths);
		DBASSERT (prv->next == ths);

		nxt->prev = prv;
		prv->next = nxt;

		head = nxt;
		delete ths;

		it.ptr = nxt;
		--size;
		if (size == 0) {
			it.ptr = nullptr;
			head = nullptr;
		}
	}

	void Erase (ConstIterator &it)
	{
		LLNode * ths = it.ptr;
		if (ths == nullptr) return;

		LLNode * nxt = ths->next;
		LLNode * prv = ths->prev;
		DBASSERT (nxt != nullptr);
		DBASSERT (prv != nullptr);
		DBASSERT (nxt->prev == ths);
		DBASSERT (prv->next == ths);

		nxt->prev = prv;
		prv->next = nxt;

		head = nxt;
		delete ths;

		it.ptr = nxt;
		--size;
		if (size == 0) {
			it.ptr = nullptr;
			head = nullptr;
		}
	}

	USize GetSize () const { return size; }
	void Clear ()
	{
		while (head != nullptr) {
			Iterator del(head);
			Erase (del);
		}
	}
private:

	class LLNode
	{
	public:
		LLNode (const T & v, LLNode * n = nullptr, LLNode * p = nullptr)
			: val (v), next(n), prev(p)
		{
		}

		//LLNode (LLNode * n = nullptr, LLNode * p = nullptr)
		//	: next(n), prev(p)
		//{
		//}

	private:
		friend 	class Iterator;
		friend	class ConstIterator;
		friend	class RingContainer;

		T			val;
		LLNode *	next;
		LLNode *	prev;
	};

	USize		size;
	LLNode *	head;
};

namespace Geometry {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class GEOMETRY_DLL_EXPORT SmoothPatchFinisher
	{
	public:
		class GEOMETRY_DLL_EXPORT CoordinateGetSet //in order to get and set the coordinates of the external vertices, inherit from this and implement the two methods if  LoadCrds() or SaveCrds() will be used.
		{
		public:
			virtual	~CoordinateGetSet ();

			virtual const Vector3D & GetCrds(const USize vrtIndex) const = 0;
			virtual void SetCrds(const USize vrtIndex, const Vector3D & crds) = 0;
			virtual void IssueCrds(const Vector3D & crds, USize &vrtIndex) = 0;			//supposed to create a new vertex with the coordinates above, and then return it's external index!
		};
		SmoothPatchFinisher ();
		virtual										~SmoothPatchFinisher ();
		void										Reset ();
		void										AddPerimeterPoint (const USize atVertexIndex, const Vector3D &surfNormal);
		void										IssueTriangle (const USize trgVert1, const USize trgVert2, const USize trgVert3);
		bool										GetTriangle (const USize trgIndex, USize & trgVert1, USize & trgVert2, USize & trgVert3) const;	//to visit all the triangles!
		void										LoadCrds (const CoordinateGetSet & srcs);
		void										SaveCrds (CoordinateGetSet & target);
		void										RoundAndSmooth (USize maxSmoothIter = 20000, double CurvatureErrorConvergenceCriteria = 1E-10);
		void										MeshAndRoundAndSmooth (const char *strId, CoordinateGetSet & srcs, USize maxSmoothIter = 20000, double CurvatureErrorConvergenceCriteria = 1E-10);
		void										LaplaceSmooth (USize nIter, const double strength = 0.25, const double keepVolumeFactor = 0.0);

		class GEOMETRY_DLL_EXPORT PerimeterData
		{
		public:
													PerimeterData ();
			virtual									~PerimeterData ();

			void									SetOldPerimCorner (const bool v = true) { oldPerimCorner = v; }
			bool									IsOldPerimCorner () const { return oldPerimCorner; }
			Vector3D								location;
			Vector3D								externalNormal;
			Vector3D								surfaceTangent;
			TrgMesh::ExternalVertIndex				extVertexIndex;				//at which the normal is defined, and which is part of the perimeter.
			USize									internalIndex;
		private:
			bool									oldPerimCorner;
		};

	private:
		class RoundAndSmoothOptions
		{
		public:
			RoundAndSmoothOptions ()
			{
				maxSmoothIter = 20000;
				curvatureErrorConvergenceCriteria = 1E-10;

				goalNormalSmoothCount = 2;
				goalNormalAdjustFactor = 0.2;

				preLaplaceIterCount = 100;
				preLaplaceKeepShapeFactor = 0.7;
				laplaceKeepShapeFactor = 1.0;
				interlacedLaplaceIterCount = 2;
				postLaplaceIterCount = 2;
				laplaceStrength = 1.0;
			}



			USize				maxSmoothIter;
			double				goalNormalAdjustFactor;
			USize				goalNormalSmoothCount;
			USize				preLaplaceIterCount;
			double				preLaplaceKeepShapeFactor;
			double				laplaceKeepShapeFactor;
			USize				interlacedLaplaceIterCount;
			USize				postLaplaceIterCount;
			double				laplaceStrength;
			double				curvatureErrorConvergenceCriteria;
		};

		double										RoundAndSmooth_iter_costEval (USize indexOfVertex, double a, Vector3D & t) const;
		Vector3D									RoundAndSmooth_iter_optForStep (USize indexOfVertex) const;
		void										RoundAndSmooth_iter (const RoundAndSmoothOptions & options);
		void										UpdateFromMesh (RingContainer<PerimeterData> &perimeter);
		bool										SplitPerimeter (const RingContainer<PerimeterData> & perimeter, RingContainer<PerimeterData> & p1, RingContainer<PerimeterData> & p2);
		bool										XNewTrgAndPerimeter (RingContainer<PerimeterData>::Iterator it1, RingContainer<PerimeterData>::Iterator it2, const Vector3D & vert3, RingContainer<PerimeterData> &perimeter);
		void										FillSharpCorners (RingContainer<PerimeterData> & perimeter, bool & changeDetected);
		TrgMesh::ExternalVertIndex					IssuePoint (const Vector3D & location, const Vector3D & normal, TrgMesh::VrtIndex & vIndex);
		bool										MeshAndRoundAndSmoothRecursive (RingContainer<PerimeterData> &perimeter);

		void										SmoothPerimeterNormals (const USize nIter);
		void										FixPerimeterNormals (); // in case some of them is zero..

		void										SmoothPerimeterQuantities (const USize nIter, RingContainer<PerimeterData> &perimeter, const bool smthNormal, const bool smthTangent);
		void										SetupSmoothingDomain ();
		void										AdjustGoalNormals (const double adjustFactor /* 0 - 1 */);
		void										SmoothGoalNormals (USize nIter, const bool immediateNormalization);
		void										SuggestNormal (const Vector3D &at, Vector3D &normal) const;


		GS::HashSet<USize>							thePerimeterPointIndexes;
		GS::Array<PerimeterData>					thePerimeter;				//the perimeter, there we do not smooth!
		Geometry::TrgMesh::Mesh						theMesh;
		GS::Array<Vector3D>							goalNormals;				//at each vertex of the mesh!
		GS::Array<Geometry::TrgMesh::VrtIndex>		smoothingMeshVertIndexes;	//vertex indexes in the mesh, that are moving due to smoothing operations.
		Vector3D									upVector;
		double										avPerimDist;

		bool										mustSetupDomainForSmoothing;
		CoordinateGetSet							*theCoordSrcs;
		USize										theMaxSmoothIter;
		double										theCurvatureErrorConvergenceCriteria;
		double										theAverageEdgeLengthGoal;
		const char									*thePatchID;				//for debugging it is good to know.
	};

}

#endif

