// *********************************************************************************************************************
// Description:		Specific intersection queries for box-keyed KD-Trees
//
// Module:			GSModeler
// Namespace:		Modeler
// Contact person:	PP
//
// SG compatible
// *********************************************************************************************************************

#if !defined (BOXKDTREEQUERIES_HPP)
#define BOXKDTREEQUERIES_HPP

#pragma once

#include	"Model3DExport.h"

// from GSRoot
#include	"GSProcessControl.hpp"

// from Geometry
#include	"KDTreeTypes.hpp"
#include	"Plane3DData.h"


namespace Modeler {


struct PolygonModelReferences;

enum QueryFlowControl : bool {
	FinishQuery		= false,
	ContinueQuery	= true
};


// helper class for speeding up AABB-plane intersection tests
// for a given plane, there is a corner in an AABB that is the nearest/farthest to the plane
// this corner is the same for all AABB-s with a given plane
// this class stores the corner id and gives functions to determine AABB-plane positions
class	MODEL3D_DLL_EXPORT	AABBoxPlaneInfo {
public:
	AABBoxPlaneInfo (const PlaneEq& plane) : pEq (plane), pVert (0)
	{
		if (pEq.pa > 0.0)
			pVert += 1;
		if (pEq.pb > 0.0)
			pVert += 2;
		if (pEq.pc > 0.0)
			pVert += 4;
	}

	template<typename BoxType>
	double		GetPositiveVertDist (const BoxType& box) const {
		return DistToPlane (pEq, GetPVert (box));
	}

	template<typename BoxType>
	double		GetNegativeVertDist (const BoxType& box) const {
		return DistToPlane (pEq, GetNVert (box));
	}

	template<typename BoxType>
	bool		IsInNegativeHalfSpace (const BoxType& box, const double epsilon) const
	{
		return GetPositiveVertDist (box) < -epsilon;
	}

private:
	double		DistToPlane (const PlaneEq& pEq, const Coord3D& c) const
	{
		return pEq.pa*c.x + pEq.pb*c.y + pEq.pc*c.z + pEq.pd;
	}

	template<typename BoxType>
	Coord3D		GetIVert (const BoxType& box, UInt32 i) const
	{
		const double x = ((i >> 0) % 2) == 0 ? box.xMin : box.xMax;
		const double y = ((i >> 1) % 2) == 0 ? box.yMin : box.yMax;
		const double z = ((i >> 2) % 2) == 0 ? box.zMin : box.zMax;

		return Coord3D (x, y, z);
	}

	template<typename BoxType>
	Coord3D		GetPVert (const BoxType& box) const
	{
		return GetIVert (box, pVert);
	}

	template<typename BoxType>
	Coord3D		GetNVert (const BoxType& box) const
	{
		return GetIVert (box, 7-pVert);
	}

private:
	PlaneEq		pEq;
	UInt32		pVert;	// p-vert for axis aligned bounding boxes for the plane above; n-vert is in the opposite corner of the bbox
						// p-vert is the one that has the highest value substituted into the plane equation
						// n-vert has the less value <-> it is exactly the opposite corner in an AABB
};


template <typename QueriedKDTree, Geometry::KDTreeNodeBounds ElemSetType>
struct CurrentBox {
	static typename QueriedKDTree::AssociatedKeyType GetCurrentBoxStatic (const typename QueriedKDTree::AssociatedKeyType& bbox, const short dimIdx, const typename QueriedKDTree::Node *node);
};

template <typename QueriedKDTree>
struct CurrentBox<QueriedKDTree, Geometry::KDTreeNodeBoundsDisabled> {
	static typename QueriedKDTree::AssociatedKeyType GetCurrentBoxStatic (const typename QueriedKDTree::AssociatedKeyType& bbox, const short dimIdx, const typename QueriedKDTree::Node *node)
	{
		typename QueriedKDTree::AssociatedKeyType currBox = bbox;
		currBox.SetDimVal (dimIdx, node->GetSeparatorVal ());
		return currBox;
	}
};


template <typename QueriedKDTree>
struct CurrentBox<QueriedKDTree, Geometry::KDTreeNodeBoundsEnabled> {
	static typename QueriedKDTree::AssociatedKeyType GetCurrentBoxStatic (const typename QueriedKDTree::AssociatedKeyType& /*bbox*/, const short /*dimIdx*/, const typename QueriedKDTree::Node *node)
	{
		const typename QueriedKDTree::Bounds& bounds = node->GetBounds ();
		typename QueriedKDTree::AssociatedKeyType box (bounds.GetMin (0), bounds.GetMax (1), bounds.GetMin (2),
											 bounds.GetMax (3), bounds.GetMin (4), bounds.GetMax (5));
		return box;
	}
};


template <typename QueriedKDTree, Geometry::KDTreeNodeBounds ElemSetType>
typename QueriedKDTree::AssociatedKeyType GetCurrentBox (const typename QueriedKDTree::AssociatedKeyType& bbox, const short dimIdx, const typename QueriedKDTree::Node *node)
{
	return CurrentBox<QueriedKDTree, ElemSetType>::GetCurrentBoxStatic (bbox, dimIdx, node);
}


template<typename QueriedKDTree, typename AdapterFunction>
void	EnumeratePolygonKDTree (GS::ProcessControl&													processControl,
								const typename QueriedKDTree::NodeBase*								nb,
								const Box3D&														treeBoundBox,
								AdapterFunction&													adapter,
								std::function<bool (const typename QueriedKDTree::AssociatedKeyType& boxKey)>	intersectFunction)
{
	using KeyType = typename QueriedKDTree::AssociatedKeyType;

	DBASSERT (nb != nullptr);

	const UInt32 NUM_STACK = 128;

	struct NodeItem {
		short									dimIdx;
		const typename QueriedKDTree::NodeBase*	nb;
		KeyType									bbox;

		void Set (short dimIdx, const typename QueriedKDTree::NodeBase* nb, const typename QueriedKDTree::AssociatedKeyType& bbox)
		{
			this->dimIdx	= dimIdx;
			this->nb		= nb;
			this->bbox		= bbox;
		}
	};


	NodeItem stack[NUM_STACK];
	NodeItem* currItem = stack;
	KeyType currBoxKey (treeBoundBox);
	currItem->Set (0, nb, currBoxKey);

	unsigned char testBreakCounter = 0;

	for (;;) {
		if (testBreakCounter++ == 0 && processControl.TestBreak ())
			return;

		const typename QueriedKDTree::NodeBase* nb = currItem->nb;

		if (nb->IsLeaf ()) {
			const typename QueriedKDTree::Leaf *leaf = nb->ToLeaf ();

			if (intersectFunction (leaf->GetAssoc ().GetKey ())) {
				leaf->LeafFound ();
				if (adapter (leaf->GetAssoc ().GetElem ()) != ContinueQuery) {
					return;
				}
			}
			if (currItem == stack) {
				break;
			}
			--currItem;
		} else {
			const typename QueriedKDTree::Node *node = nb->ToNode ();

			const short dimIdx = currItem->dimIdx;
			const short nextDimIdx = QueriedKDTree::NextDim (dimIdx);

			// Create the limited box
			KeyType currBox = GetCurrentBox<QueriedKDTree, QueriedKDTree::NodeBoundsModeValue> (currItem->bbox, dimIdx, node);

			DBASSERT (currBox.GetDimVal (0) <= currBox.GetDimVal (1) && currBox.GetDimVal (2) <= currBox.GetDimVal (3) && currBox.GetDimVal (4) <= currBox.GetDimVal (5));
			const bool smallerBoxIntersects = intersectFunction (currBox);

			if (dimIdx & 0x1) {
				// interval right end in node separator value

				currItem->Set (nextDimIdx, node->GetRight (), currItem->bbox);
				if (smallerBoxIntersects) {
					++currItem;
					currItem->Set (nextDimIdx, node->GetLeft (), currBox);
				}
			} else {
				// interval left end in node separator value

				currItem->Set (nextDimIdx, node->GetLeft (), currItem->bbox);
				if (smallerBoxIntersects) {
					++currItem;
					currItem->Set (nextDimIdx, node->GetRight (), currBox);
				}
			}
		}
	}
}


class LineIntersectionQueryAlgorithmBase
{
protected:
	enum BoxNormal {
		XPos = 0,
		XNeg = 1,
		YPos = 2,
		YNeg = 3,
		ZPos = 4,
		ZNeg = 5
	};

	// algorithm parameters
	const Coord3D	m_rayStartPos;
	const Vector3D	m_rayDir;
	const double	m_epsilon;
	const double	m_tLimit;		// @m_tLimit is an upper limit for the distance of intersection point measured 
									// from @m_rayStartPos in @m_rayDir direction, scaled by the length of @m_rayDir.
									// The value 0.0 means no limit (std::optional would be better but it is unavailable yet).
									// All other (positive and negative) values are considered valid.

	// caching some constants
	double			m_boxNormalsDotRayCache[6];
	double			m_boxNormalsDotRayStartPosCache[6];
	bool			m_isBoxNormalsDotRayNonnegCache[6];

	bool			BoxSideIsParallelOrBackfacing (const BoxNormal boxNormal) const {
		// m_boxNormalsDotRayCache[boxNormal] > -m_epsilon
		return m_isBoxNormalsDotRayNonnegCache[boxNormal];
	}

	double			GetIntersectionParameter (const BoxNormal boxNormal, const double d) const {
		// Substitute parametric ray equation into plane equation
		//		Ray equation:	rayStartPos + t * rayDir
		//		Plane equation:	boxNormal * X + d = 0
		//		Substitute:		boxNormal * (rayStartPos + t * rayDir) + d = 0
		//		Expand:			boxNormal * rayStartPos + t * boxNormal * rayDir + d = 0
		//		Arrange to t:	t = - (d + boxNormal * rayStartPos) / (boxNormal * rayDir)

		// m_boxNormalsDotRayStartPosCache[boxNormal] = boxNormals[boxNormal] * m_rayStartPos
		//  m_boxNormalsDotRayCache[boxNormal] = boxNormals[boxNormal] * m_rayDir
		return - (m_boxNormalsDotRayStartPosCache[boxNormal] + d) /  m_boxNormalsDotRayCache[boxNormal];
	}

	Coord3D			GetIntersectionPoint (const double intersectionParameter) const {
		return m_rayStartPos + intersectionParameter * m_rayDir;
	}

	bool			ParameterIsOffLimit (const double intersectionParameter) const {
		// 0.0 means the limit is invalid
		return m_tLimit != 0.0 && intersectionParameter > m_tLimit;
	}

	bool			RayIsGoingAwayFromBox (const Box3D& box) const {
		return	m_rayStartPos.x < box.xMin && m_rayDir.x < 0.0 ||
				m_rayStartPos.x > box.xMax && m_rayDir.x > 0.0 ||
				m_rayStartPos.y < box.yMin && m_rayDir.y < 0.0 ||
				m_rayStartPos.y > box.yMax && m_rayDir.y > 0.0 ||
				m_rayStartPos.z < box.zMin && m_rayDir.z < 0.0 ||
				m_rayStartPos.z > box.zMax && m_rayDir.z > 0.0;
	}

public:
	LineIntersectionQueryAlgorithmBase (const Coord3D& rayStartPos, const Vector3D& rayDir, const double tLimit, const double epsilon = Eps);
};


class MODEL3D_DLL_EXPORT	IntersectionQueryAlgorithm
{
public:
	virtual ~IntersectionQueryAlgorithm ();
	virtual bool Intersect (const Box3D& box) const = 0;
};


// Intersects with full line given by @startPos and @rayDir
class	MODEL3D_DLL_EXPORT	LineIntersectionQueryAlgorithm : public IntersectionQueryAlgorithm, private LineIntersectionQueryAlgorithmBase
{
private:
	using LineIntersectionQueryAlgorithmBase::BoxNormal;
	bool  DoPlaneAndRayIntersect (const BoxNormal boxNormal, const double d, Coord3D& intersectionPoint) const;

public:
	LineIntersectionQueryAlgorithm (const Coord3D& rayStartPos, const Vector3D& rayDir, const double tLimit, const double epsilon = Eps)
		: LineIntersectionQueryAlgorithmBase (rayStartPos, rayDir, tLimit, epsilon)
	{
		// do nothing
	}

	virtual ~LineIntersectionQueryAlgorithm ();

	virtual bool	Intersect (const Box3D& box) const override;
};


// Intersects with half-line (ray) starting from @startPos towards @rayDir
class	MODEL3D_DLL_EXPORT	RayIntersectionQueryAlgorithm : public IntersectionQueryAlgorithm, private LineIntersectionQueryAlgorithmBase
{
private:
	using LineIntersectionQueryAlgorithmBase::BoxNormal;

	bool	DoPlaneAndRayIntersect (const BoxNormal boxNormal, const double d, Coord3D& intersectionPoint) const;

public:
	RayIntersectionQueryAlgorithm (const Coord3D& rayStartPos, const Vector3D& rayDir, const double tLimit, const double epsilon = Eps)
		: LineIntersectionQueryAlgorithmBase (rayStartPos, rayDir, tLimit, epsilon)
	{
		// do nothing
	}

	virtual ~RayIntersectionQueryAlgorithm ();

	virtual bool	Intersect (const Box3D& box) const override;
};


// returns the values whose bbox may intersect the given convex polyhedron
class	MODEL3D_DLL_EXPORT	ConvexPolyhedronIntersectionQueryAlgorithm : public IntersectionQueryAlgorithm
{
private:
	GS::Array<AABBoxPlaneInfo>	m_sides;
	const double				m_epsilon;

public:
	// convention: plane equation is "ax + by + cz + d = 0"
	// (a; b; c) is the normal vector of the plane pointing the positive half-space
	// everything that intersects the polyhedron is not on the negative half-space of any planes, so false positives may occure
	// the given convex space can be infinite
	ConvexPolyhedronIntersectionQueryAlgorithm (const GS::Array<PlaneEq>& sides, const double epsilon = Eps);
	virtual ~ConvexPolyhedronIntersectionQueryAlgorithm ();

	virtual bool	Intersect (const Box3D& box) const override;
};


// wraps a query algorithm
template<typename QueriedKDTree, typename AdapterFunction>
class	BoxIntersectionQuery
{
private:
	const IntersectionQueryAlgorithm&	m_intersectionAlgorithm;
	const Box3D&						m_treeBoundBox;
	AdapterFunction&					m_adapter;
	GS::ProcessControl&					m_processControl;

public:
	BoxIntersectionQuery (const IntersectionQueryAlgorithm& intersectionAlgorithm, const Box3D& treeBoundBox, AdapterFunction& adapter, GS::ProcessControl& processControl);

	void operator () (const typename QueriedKDTree::NodeBase* nb);
};


template<typename QueriedKDTree, typename AdapterFunction>
void	QueryKDTree (const QueriedKDTree& tree, const Box3D& treeBoundBox, const IntersectionQueryAlgorithm& intersectionQueryAlgorithm, AdapterFunction& adapter, GS::ProcessControl& processControl)
{
	BoxIntersectionQuery<QueriedKDTree, AdapterFunction> query (intersectionQueryAlgorithm, treeBoundBox, adapter, processControl);
	tree.CustomQuery (query);
}

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ template class member definitions ------------------------------------
// -----------------------------------------------------------------------------------------------------------



// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ RayIntersectionQueryAlgorithm     ------------------------------------


inline	LineIntersectionQueryAlgorithmBase::LineIntersectionQueryAlgorithmBase (const Coord3D& rayStartPos,
																				const Vector3D& rayDir,
																				const double tLimit,
																				const double epsilon /*= Eps*/) :
	m_rayStartPos (rayStartPos),
	m_rayDir (rayDir),
	m_tLimit (tLimit),
	m_epsilon (epsilon)
{
	static const Vector3D boxNormals[6] = {
		Vector3D (1.0, 0.0, 0.0),		// LineIntersectionQueryAlgorithmBase::XPos
		Vector3D (-1.0, 0.0, 0.0),		// LineIntersectionQueryAlgorithmBase::XNeg
		Vector3D (0.0, 1.0, 0.0),		// LineIntersectionQueryAlgorithmBase::YPos
		Vector3D (0.0, -1.0, 0.0),		// LineIntersectionQueryAlgorithmBase::YNeg
		Vector3D (0.0, 0.0, 1.0),		// LineIntersectionQueryAlgorithmBase::ZPos
		Vector3D (0.0, 0.0, -1.0)		// LineIntersectionQueryAlgorithmBase::ZNeg
	};

	m_boxNormalsDotRayCache[XPos] = boxNormals[XPos] * m_rayDir;
	m_isBoxNormalsDotRayNonnegCache[XPos] = m_boxNormalsDotRayCache[XPos] > -m_epsilon;
	m_boxNormalsDotRayCache[XNeg] = boxNormals[XNeg] * m_rayDir;
	m_isBoxNormalsDotRayNonnegCache[XNeg] = m_boxNormalsDotRayCache[XNeg] > -m_epsilon;
	m_boxNormalsDotRayCache[YPos] = boxNormals[YPos] * m_rayDir;
	m_isBoxNormalsDotRayNonnegCache[YPos] = m_boxNormalsDotRayCache[YPos] > -m_epsilon;
	m_boxNormalsDotRayCache[YNeg] = boxNormals[YNeg] * m_rayDir;
	m_isBoxNormalsDotRayNonnegCache[YNeg] = m_boxNormalsDotRayCache[YNeg] > -m_epsilon;
	m_boxNormalsDotRayCache[ZPos] = boxNormals[ZPos] * m_rayDir;
	m_isBoxNormalsDotRayNonnegCache[ZPos] = m_boxNormalsDotRayCache[ZPos] > -m_epsilon;
	m_boxNormalsDotRayCache[ZNeg] = boxNormals[ZNeg] * m_rayDir;
	m_isBoxNormalsDotRayNonnegCache[ZNeg] = m_boxNormalsDotRayCache[ZNeg] > -m_epsilon;

	m_boxNormalsDotRayStartPosCache[XPos] = boxNormals[XPos] * m_rayStartPos;
	m_boxNormalsDotRayStartPosCache[XNeg] = boxNormals[XNeg] * m_rayStartPos;
	m_boxNormalsDotRayStartPosCache[YPos] = boxNormals[YPos] * m_rayStartPos;
	m_boxNormalsDotRayStartPosCache[YNeg] = boxNormals[YNeg] * m_rayStartPos;
	m_boxNormalsDotRayStartPosCache[ZPos] = boxNormals[ZPos] * m_rayStartPos;
	m_boxNormalsDotRayStartPosCache[ZNeg] = boxNormals[ZNeg] * m_rayStartPos;
}


inline bool LineIntersectionQueryAlgorithm::DoPlaneAndRayIntersect (const BoxNormal boxNormal, const double d, Coord3D& intersectionPoint) const
{
	// convention: parallel ray and plane do not intersect -> intersectionPoint is unambiguous
	// convention: ray can only hit a plane from the plane's positive half-space towards the negative (backface culling)
	//			   (this is because we assume that the start point of the ray is not inside the box)

	if (BoxSideIsParallelOrBackfacing (boxNormal)) {
		return false;
	}

	const double t = GetIntersectionParameter (boxNormal, d);	

	if (ParameterIsOffLimit (t)) {
		return false;
	}

	intersectionPoint = GetIntersectionPoint (t);

	return true;
}


inline bool LineIntersectionQueryAlgorithm::Intersect (const Box3D& box) const
{
	if (Geometry::IsBox3DPointIntersect (box, m_rayStartPos, Geometry::Boundary_Closed, m_epsilon)) {
		return true;
	}

	Coord3D intersectionPoint;
	auto CheckIntersectionWithBBoxSide = [&] (const BoxNormal boxNormal, const double d) -> bool {
		return DoPlaneAndRayIntersect (boxNormal, d, intersectionPoint) && Geometry::IsBox3DPointIntersect (box, intersectionPoint, Geometry::Boundary_Closed, m_epsilon);
	};

	return	CheckIntersectionWithBBoxSide (XPos, -box.xMax) ||
			CheckIntersectionWithBBoxSide (XNeg, box.xMin)  ||
			CheckIntersectionWithBBoxSide (YPos, -box.yMax) ||
			CheckIntersectionWithBBoxSide (YNeg, box.yMin)  ||
			CheckIntersectionWithBBoxSide (ZPos, -box.zMax) ||
			CheckIntersectionWithBBoxSide (ZNeg, box.zMin);
}


inline	bool	RayIntersectionQueryAlgorithm::DoPlaneAndRayIntersect (const BoxNormal boxNormal, const double d, Coord3D& intersectionPoint) const
{
	// convention: parallel ray and plane do not intersect -> intersectionPoint is unambiguous
	// convention: ray can only hit a plane from the plane's positive half-space towards the negative (backface culling)

	if (BoxSideIsParallelOrBackfacing (boxNormal)) {
		return false;
	}

	const double t = GetIntersectionParameter (boxNormal, d);

	// check if intersection is in the positive direction
	if (t < -m_epsilon) {
		return false;
	}

	if (ParameterIsOffLimit (t)) {
		return false;
	}

	intersectionPoint = GetIntersectionPoint (t);

	return true;
}


inline	bool	RayIntersectionQueryAlgorithm::Intersect (const Box3D& box) const
{
	if (Geometry::IsBox3DPointIntersect (box, m_rayStartPos, Geometry::Boundary_Closed, m_epsilon)) {
		return true;
	}

	if (RayIsGoingAwayFromBox (box)) {
		return false;
	}

	Coord3D intersectionPoint;
	auto CheckIntersectionWithBBoxSide = [&] (const BoxNormal boxNormal, const double d) -> bool {
		return DoPlaneAndRayIntersect (boxNormal, d, intersectionPoint) && Geometry::IsBox3DPointIntersect (box, intersectionPoint, Geometry::Boundary_Closed, m_epsilon);
	};

	return	CheckIntersectionWithBBoxSide (XPos, -box.xMax) ||
			CheckIntersectionWithBBoxSide (XNeg,  box.xMin) ||
			CheckIntersectionWithBBoxSide (YPos, -box.yMax) ||
			CheckIntersectionWithBBoxSide (YNeg,  box.yMin) ||
			CheckIntersectionWithBBoxSide (ZPos, -box.zMax) ||
			CheckIntersectionWithBBoxSide (ZNeg,  box.zMin);
}


// -----------------------------------------------------------------------------------------------------------
// -------------------------------- ConvexPolyhedronIntersectionQueryAlgorithm -------------------------------


inline	ConvexPolyhedronIntersectionQueryAlgorithm::ConvexPolyhedronIntersectionQueryAlgorithm (const GS::Array<PlaneEq>& sides, const double epsilon /*= Eps*/) :
	m_sides (sides.GetSize ()),
	m_epsilon (epsilon)
{
	for (UIndex i = 0; i < sides.GetSize (); ++i)
		m_sides.Push (sides[i]);
}


inline	bool	ConvexPolyhedronIntersectionQueryAlgorithm::Intersect (const Box3D& box) const
{
	for (UIndex i = 0; i < m_sides.GetSize (); ++i) {
		if (m_sides[i].IsInNegativeHalfSpace (box, m_epsilon))
			return false;
	}
	return true;
}


// -----------------------------------------------------------------------------------------------------------
// ----------------------------------------- BoxIntersectionQuery     ----------------------------------------


template<typename QueriedKDTree, typename AdapterFunction>
BoxIntersectionQuery<QueriedKDTree, AdapterFunction>::BoxIntersectionQuery (const IntersectionQueryAlgorithm& intersectionAlgorithm, const Box3D& treeBoundBox, AdapterFunction& adapter, GS::ProcessControl& processControl) :
	m_intersectionAlgorithm (intersectionAlgorithm),
	m_treeBoundBox (treeBoundBox),
	m_adapter (adapter),
	m_processControl (processControl)
{
}


template<typename QueriedKDTree, typename AdapterFunction>
void	BoxIntersectionQuery<QueriedKDTree, AdapterFunction>::operator () (const typename QueriedKDTree::NodeBase* nb)
{
	EnumeratePolygonKDTree<QueriedKDTree> (m_processControl, nb, m_treeBoundBox, m_adapter, [&] (const typename QueriedKDTree::AssociatedKeyType& boxKey) -> bool
		{
			// NOT STORED IN THE SAME ORDER!
			const Box3D box (boxKey.GetDimVal (0), boxKey.GetDimVal (2), boxKey.GetDimVal (1), boxKey.GetDimVal (3), boxKey.GetDimVal (4), boxKey.GetDimVal (5));

			return m_intersectionAlgorithm.Intersect (box);
		}
	);
}


}	// namespace Modeler

#endif	// BOXKDTREEQUERIES_HPP
