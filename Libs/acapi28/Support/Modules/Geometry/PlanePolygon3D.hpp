// *****************************************************************************
// A 3D polygon defined by a 2D polygon and a plane.
//
// Source Unit:		Geometry
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	KiP
//
// [SG compatible]
// *****************************************************************************

#ifndef	PLANEPOLYGON3D_HPP
#define	PLANEPOLYGON3D_HPP

#pragma once

#include "Polygon2D.hpp"
#include "PG.h"
#include "Plane3D.hpp"

namespace Geometry {

// =====================================================================================================================
//								 TransformVertexVisitor for transformation between planes 			
// =====================================================================================================================

class GEOMETRY_DLL_EXPORT TransformVertexVisitor : public CorePolygon2DVertexVisitor {
private:
	const Plane&	oldPlane;
	const Plane&	newPlane;
public:
	TransformVertexVisitor (const Plane& _oldPlane, const Plane& _newPlane) : oldPlane (_oldPlane), newPlane (_newPlane) {}
	virtual ~TransformVertexVisitor ();
	virtual void operator () (Point2D& coord) override
	{
		Point3D c = oldPlane.PlaneToWorld (coord);
		coord = SetCoord2D (newPlane.WorldToPlane (c));
	}
};

// =====================================================================================================================
//										CustomPlanePolygon3D class definition			
// =====================================================================================================================

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
class CustomPlaneMultiPolygon3D;

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
class CustomPlanePolygon3D {

private:
	Plane m_plane;
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> m_polygon2D;

public:
	// constructors
	CustomPlanePolygon3D ();
	CustomPlanePolygon3D (const Plane& plane, const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> polygon2D);

	// comparison
	bool operator== (const CustomPlanePolygon3D& other) const;
	bool operator!= (const CustomPlanePolygon3D& other) const;

	// set/get functions
	Plane GetPlane (void) const { return m_plane; }
	void SetPlane (const Plane& plane) { m_plane.SetPlane (plane.GetBasePoint (), plane.GetZAxis (), plane.GetXAxis (), plane.GetYAxis ()); }
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> GetPolygon2D (void) const { return m_polygon2D; }
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& GetPolygon2DRef (void) { return m_polygon2D; }
	const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& GetPolygon2DConstRef (void) const { return m_polygon2D; }
	void SetPolygon2D (const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& polygon2D) { m_polygon2D = polygon2D; }

	// operations
	short GetRelativeToPlanePosition (const Plane3D& plane) const;
	void CutByPlane (const Plane3D& cutPlane, CustomPlaneMultiPolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& result, bool& fullin, GS::Int32& wrcode, bool* degen = nullptr);
	void TransformToPlane (const Plane& plane, CustomPlaneMultiPolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& result);

	// I/O
	GSErrCode Read (GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;
			  
	GSErrCode ReadXML (GS::XMLIChannel& ic);
	GSErrCode WriteXML (GS::XMLOChannel& oc) const;
};

typedef	CustomPlanePolygon3D<PolyId, PolyId, PolyId, PolyId> PlanePolygon3D;

// =====================================================================================================================
//										   CustomPlanePolygon3D class implementation			
// =====================================================================================================================

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomPlanePolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomPlanePolygon3D ()
{

}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomPlanePolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomPlanePolygon3D (const Plane& plane, const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> polygon2D) :
	m_plane (plane),
	m_polygon2D (polygon2D)
{

}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomPlanePolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::operator== (const CustomPlanePolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& other) const
{
	return	IsEqualCoord3D (m_plane.GetBasePoint (), other.m_plane.GetBasePoint ()) &&
			IsEqualCoord3D (m_plane.GetXAxis (), other.m_plane.GetXAxis ()) &&
			IsEqualCoord3D (m_plane.GetYAxis (), other.m_plane.GetYAxis ()) &&
			IsEqualCoord3D (m_plane.GetZAxis (), other.m_plane.GetZAxis ()) &&
			m_polygon2D == other.m_polygon2D;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomPlanePolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::operator!= (const CustomPlanePolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& other) const
{
	return !(operator== (other));
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
short CustomPlanePolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetRelativeToPlanePosition (const Plane3D& plane) const
{
	const PlaneEq planeEq = plane.GetPlaneEq_Deprecated ();

	bool infront = false;
	bool behind = false;
	for (auto it = m_polygon2D.BeginVertex (); it != nullptr; ++it) {
		Point2D c = it->GetCoord ();
		Point3D cc = m_plane.PlaneToWorld (c);
		double dist = planeEq.pa * cc.x + planeEq.pb * cc.y + planeEq.pc * cc.z + planeEq.pd;
		if (IsNegative (dist)) {
			behind = true;
		} else if (IsPositive (dist)) {
			infront = true;
		}
		if (behind && infront) {
			return SplitPlane;
		}
	}

	if (behind) {
		return BehindPlane;
	} else if (infront) {
		return InfrontPlane;
	} else {
		return OnPlane;
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPlanePolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutByPlane (const Plane3D& cutPlane, CustomPlaneMultiPolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& result, bool& fullin, GS::Int32& wrcode, bool* degen /*= nullptr*/) 
{
	HalfPlane2DData cutLine;
	if (CalcCutLineFromPlanes (m_plane, cutPlane, cutLine)) {
		CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> resultMultiPolygon2D;
		m_polygon2D.Cut (cutLine, resultMultiPolygon2D, &fullin, &wrcode, degen);
		result.SetPlane (m_plane);
		result.SetMultiPolygon2D (resultMultiPolygon2D);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPlanePolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::TransformToPlane (const Plane& plane, CustomPlaneMultiPolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& result)
{
	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> resultMultiPolygon2D;
	TransformVertexVisitor visitor (m_plane, plane);
	m_polygon2D.Visit (visitor, resultMultiPolygon2D);
	result.SetPlane (plane);
	result.SetMultiPolygon2D (resultMultiPolygon2D);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode CustomPlanePolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Read (GS::IChannel& ic)
{
	GSErrCode errCode = NoError;

	if (errCode == NoError)
		errCode = m_plane.QuickRead (ic);
	if (errCode == NoError)
		errCode = m_polygon2D.Read (ic);
	
	return errCode;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode CustomPlanePolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Write (GS::OChannel& oc) const
{
	GSErrCode errCode = NoError;

	if (errCode == NoError)
		errCode = m_plane.QuickWrite (oc);
	if (errCode == NoError)
		errCode = m_polygon2D.Write (oc);

	return errCode;
}

extern GEOMETRY_DLL_EXPORT const char*	XMLPolygon_Tag_PlanePolygon3D;

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode CustomPlanePolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReadXML (GS::XMLIChannel& ic)
{
	GSErrCode errCode = NoError;
	GS::XMLITag tag (ic, XMLPolygon_Tag_PlanePolygon3D);

	if (errCode == NoError)
		errCode = m_plane.ReadXML (ic);
	if (errCode == NoError)
		errCode = m_polygon2D.ReadXML (ic);

	return errCode;	
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode CustomPlanePolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::WriteXML (GS::XMLOChannel& oc) const
{
	GSErrCode errCode = NoError;
	GS::XMLTag tag (oc, XMLPolygon_Tag_PlanePolygon3D);

	if (errCode == NoError)
		errCode = m_plane.WriteXML (oc);
	if (errCode == NoError)
		errCode = m_polygon2D.WriteXML (oc);

	return errCode;
}

// =====================================================================================================================
//										 CustomPlaneMultiPolygon3D class definition			
// =====================================================================================================================

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
class CustomPlaneMultiPolygon3D {

private:
	Plane m_plane;
	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> m_multiPolygon2D;

public:
	// constructors
	CustomPlaneMultiPolygon3D ();
	CustomPlaneMultiPolygon3D (const CustomPlaneMultiPolygon3D& source);
	CustomPlaneMultiPolygon3D (const Plane& plane, const CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> multiPolygon2D);

	// assingment
	CustomPlaneMultiPolygon3D& operator= (const CustomPlaneMultiPolygon3D& source);

	// comparison
	bool operator== (const CustomPlaneMultiPolygon3D& other) const;
	bool operator!= (const CustomPlaneMultiPolygon3D& other) const;

	// set/get functions
	Plane GetPlane (void) const { return m_plane; }
	void SetPlane (const Plane& plane) { m_plane.SetPlane (plane.GetBasePoint (), plane.GetZAxis (), plane.GetXAxis (), plane.GetYAxis ()); }
	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> GetMultiPolygon2D (void) const { return m_multiPolygon2D; }
	void SetMultiPolygon2D (const CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& multiPolygon2D) 
	{ 
		m_multiPolygon2D.Clear (); 
		for (UIndex i = 0; i < multiPolygon2D.GetSize (); ++i)
			m_multiPolygon2D.Push (multiPolygon2D[i]);
	}

	// operations
	short GetRelativeToPlanePosition (const Plane3D& plane) const;
	void CutByPlane (const Plane3D& cutPlane, CustomPlaneMultiPolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& result, bool& fullin, GS::Int32& wrcode, bool* degen = nullptr);
	void TransformToPlane (const Plane& plane, CustomPlaneMultiPolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& result);

	// I/O
	GSErrCode Read (GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;
			  
	GSErrCode ReadXML (GS::XMLIChannel& ic);
	GSErrCode WriteXML (GS::XMLOChannel& oc) const;
};

typedef	CustomPlaneMultiPolygon3D<PolyId, PolyId, PolyId, PolyId> PlaneMultiPolygon3D;

// =====================================================================================================================
//										CustomPlaneMultiPolygon3D class implementation			
// =====================================================================================================================

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomPlaneMultiPolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomPlaneMultiPolygon3D ()
{

}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomPlaneMultiPolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomPlaneMultiPolygon3D (const CustomPlaneMultiPolygon3D& source) :
	m_plane (source.m_plane),
	m_multiPolygon2D (source.m_multiPolygon2D)
{

}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomPlaneMultiPolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomPlaneMultiPolygon3D (const Plane& plane, const CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> multiPolygon2D) :
	m_plane (plane),
	m_multiPolygon2D (multiPolygon2D)
{

}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomPlaneMultiPolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& CustomPlaneMultiPolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::operator= (const CustomPlaneMultiPolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& source)
{
	if (this != &source) {
		m_plane = source.m_plane;
		m_multiPolygon2D = source.m_multiPolygon2D;
	}
	return *this;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomPlaneMultiPolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::operator== (const CustomPlaneMultiPolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& other) const
{
	return	IsEqualCoord3D (m_plane.GetBasePoint (), other.m_plane.GetBasePoint ()) &&
			IsEqualCoord3D (m_plane.GetXAxis (), other.m_plane.GetXAxis ()) &&
			IsEqualCoord3D (m_plane.GetYAxis (), other.m_plane.GetYAxis ()) &&
			IsEqualCoord3D (m_plane.GetZAxis (), other.m_plane.GetZAxis ()) &&
			m_multiPolygon2D == other.m_multiPolygon2D;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomPlaneMultiPolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::operator!= (const CustomPlaneMultiPolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& other) const
{
	return !(operator== (other));
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
short CustomPlaneMultiPolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetRelativeToPlanePosition (const Plane3D& plane) const
{
	const PlaneEq planeEq = plane.GetPlaneEq_Deprecated ();

	bool infront = false;
	bool behind = false;
	for (UIndex i = 0; i < m_multiPolygon2D.GetSize (); ++i) {
		for (auto it = m_multiPolygon2D[i].BeginVertex (); it != nullptr; ++it) {
			Point2D c = it->GetCoord ();
			Point3D cc = m_plane.PlaneToWorld (c);
			double dist = planeEq.pa * cc.x + planeEq.pb * cc.y + planeEq.pc * cc.z + planeEq.pd;
			if (IsNegative (dist)) {
				behind = true;
			} else if (IsPositive (dist)) {
				infront = true;
			}
			if (behind && infront) {
				return SplitPlane;
			}
		}
	}

	if (behind) {
		return BehindPlane;
	} else if (infront) {
		return InfrontPlane;
	} else {
		return OnPlane;
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPlaneMultiPolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutByPlane (const Plane3D& cutPlane, CustomPlaneMultiPolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& result, bool& fullin, GS::Int32& wrcode, bool* degen /*= nullptr*/) 
{
	HalfPlane2DData cutLine;
	if (CalcCutLineFromPlanes (m_plane, cutPlane, cutLine)) {
		CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> resultMultiPolygon2D;
		for (UIndex i = 0; i < m_multiPolygon2D.GetSize (); ++i) {
			CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> tmpResult;
			tmpResult = m_multiPolygon2D[i].Cut (cutLine, &fullin, &wrcode, degen);
			resultMultiPolygon2D.Append (tmpResult);
		}
		result.SetPlane (m_plane);
		result.SetMultiPolygon2D (resultMultiPolygon2D);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPlaneMultiPolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::TransformToPlane (const Plane& plane, CustomPlaneMultiPolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& result)
{
	TransformVertexVisitor visitor (m_plane, plane);
	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> resultMultiPolygon2D;
	for (UIndex i = 0; i < m_multiPolygon2D.GetSize (); ++i) {
		CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> tmpResult;
		tmpResult = m_multiPolygon2D[i].Visit (visitor);
		resultMultiPolygon2D.Append (tmpResult);
	}
	result.SetPlane (plane);
	result.SetMultiPolygon2D (resultMultiPolygon2D);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode CustomPlaneMultiPolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Read (GS::IChannel& ic)
{
	GSErrCode errCode = NoError;

	if (errCode == NoError)
		errCode = m_plane.QuickRead (ic);
	if (errCode == NoError)
		errCode = m_multiPolygon2D.Read (ic);

	return errCode;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode CustomPlaneMultiPolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Write (GS::OChannel& oc) const
{
	GSErrCode errCode = NoError;

	if (errCode == NoError)
		errCode = m_plane.QuickWrite (oc);
	if (errCode == NoError)
		errCode = m_multiPolygon2D.Write (oc);

	return errCode;
}

extern GEOMETRY_DLL_EXPORT const char*	XMLPolygon_Tag_PlaneMultiPolygon3D;

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode CustomPlaneMultiPolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReadXML (GS::XMLIChannel& ic)
{
	GSErrCode errCode = NoError;
	GS::XMLITag tag (ic, XMLPolygon_Tag_PlaneMultiPolygon3D);

	if (errCode == NoError)
		errCode = m_plane.ReadXML (ic);
	if (errCode == NoError)
		errCode = m_multiPolygon2D.ReadXML (ic);

	return errCode;	
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode CustomPlaneMultiPolygon3D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::WriteXML (GS::XMLOChannel& oc) const
{
	GSErrCode errCode = NoError;
	GS::XMLTag tag (oc, XMLPolygon_Tag_PlaneMultiPolygon3D);

	if (errCode == NoError)
		errCode = m_plane.WriteXML (oc);
	if (errCode == NoError)
		errCode = m_multiPolygon2D.WriteXML (oc);

	return errCode;
}

} // namespace Geometry

#endif
