// *****************************************************************************
//
// Declaration of Poly2D class
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	RA
//
// *****************************************************************************

#ifndef GEOMETRY_POLY2D_HPP
#define GEOMETRY_POLY2D_HPP

#pragma once

// --- Includes --------------------------------------------------------------------------------------------------------

// from GSRoot
#include "XMLChannel.hpp"
#include "Channel.hpp"

// from Geometry
#include "Poly2DTypes.hpp"
#include "Point2D.hpp"
#include "PolyArcRec.h"
#include "NurbsCurve2D.hpp"
#include "GenArc2DData.h"

// --- predeclarations -------------------------------------------------------------------------------------------------

namespace Geometry {

class BezierDetails;

#define WHO_USE_IT DBBREAK_STR ("Szolj, ha ezt barki is hasznalja")
#define HAVE_TO_TEST_IT DBBREAK_STR ("Ez meg nem volt sosem tesztelve")

	// Flags (properties) that can be set in (Irregular)Polygon2D/Polyline2D, their validity is always ensured
	enum PolyFlags {
		PolyFlags_Default				= 0x0000,
		PolyFlags_IsSameDirEdgeLegal	= 0x0001,	// Polyline2D and Polygon2D only - Set if two succeeding edges with the same direction (two edges in one line) are allowed
		PolyFlags_NoSameDirEdgeLegal	= 0x0002,	// Polyline2D and Polygon2D only - Set if two succeeding edges with the same direction (two edges in one line) are not allowed
		PolyFlags_IsClosed				= 0x0004,	// Polyline2D only - Set if Polyline is closed
		PolyFlags_NoClosed				= 0x0008,	// Polyline2D only - Set if Polyline is open (Polyline can be open even though first and last coordinates are the same)
		PolyFlags_IsSameCoord			= 0x0010,	// Polyline2D only - Set if two succeeding vertices in the Polyline may have the same coordinates
		PolyFlags_NoSameCoord			= 0x0020,	// Polyline2D only - Set if two succeeding vertices in the Polyline may not have the same coordinates
		PolyFlags_IsVertexUserData		= 0x0040,	// Set if there is user data associated to the vertices
		PolyFlags_NoVertexUserData		= 0x0080,	// Set if there is no user data associated to the vertices
		PolyFlags_IsEdgeUserData		= 0x0100,	// Set if there is user data associated to the edges
		PolyFlags_NoEdgeUserData		= 0x0200,	// Set if there is no user data associated to the edges
		PolyFlags_IsContourUserData		= 0x0400,	// (Irregular)Polygon2D only - Set if there is user data associated to the Polygon contours
		PolyFlags_NoContourUserData		= 0x0800,	// (Irregular)Polygon2D only - Set if there is no user data associated to the Polygon contours
		PolyFlags_IsPolygonUserData		= 0x1000,	// Set if there is user data associated to the Polygon/Polyline
		PolyFlags_NoPolygonUserData		= 0x2000,	// Set if there is no user data associated to the Polygon/Polyline
		PolyFlags_Force64BitPrecision   = 0x4000,	// Set if boolean operations with the polygon are forced to be done with 64 bit precision, otherwise use default precision
		PolyFlags_NoForce64BitPrecision = 0x8000,	// Set if boolean operations with the polygon are never to be be done with 64 bit precision.

		PolyFlags_NoUserData			= PolyFlags_NoVertexUserData
										| PolyFlags_NoEdgeUserData
										| PolyFlags_NoContourUserData
										| PolyFlags_NoPolygonUserData
	};

	// Flags used when creating Polygons/Polylines from coord lists, PolyArcRec lists and contour end index lists or vice versa
	// They determine the format of the lists
	enum PolyCreateFlags {
		PolyCreateFlags_DummyCoordAtIdxZero			= 0x0001,	// Coord list format flag - Set if the coord list starts with a blank ((0, 0)) coord that does not correspond
																// with any of the Polygon's/Polyline's vertices
		PolyCreateFlags_DummyArcAtIdxZero			= 0x0002,	// Arc list format flag - Set if the PolyArcRec list starts with a blank PolyArcRec that does not correspond
																// with any of the Polygon's/Polyline's edges
		PolyCreateFlags_1stCoordDuplAtContourEnd	= 0x0004,	// Coord list format flag - Set if the first vertex coordinate of every Polygon/Polyline contour is duplicated
																// after the last vertex coordinate of the contour
		PolyCreateFlags_IdxRefInArcFromZero			= 0x0008,	// Arc list format flag - Set if the coord list indices referenced in the PolyArcRecs run
																// from 0 to (coord list size - 1)
		PolyCreateFlags_IdxRefInContourEndFromZero	= 0x0010,	// Contour end list format flag - Set if the coord list indices referenced by the contour ends run
																// from 0 to (coord list size - 1)
		PolyCreateFlags_DummyContourEndAtIdxZero	= 0x0020,	// Contour end list format flag - Set if the contour end list starts with a 0 contour end which does not
																// reference any of the Polygon's/Polyline's vertices

		PolyCreateFlags_Polygon2DDataRepresentation		= PolyCreateFlags_DummyCoordAtIdxZero
														| PolyCreateFlags_DummyArcAtIdxZero
														| PolyCreateFlags_1stCoordDuplAtContourEnd
														| PolyCreateFlags_IdxRefInArcFromZero
														| PolyCreateFlags_IdxRefInContourEndFromZero
														| PolyCreateFlags_DummyContourEndAtIdxZero,

		PolyCreateFlags_VBElemPolygonDataRepresentation = PolyCreateFlags_DummyCoordAtIdxZero
														| PolyCreateFlags_1stCoordDuplAtContourEnd
														| PolyCreateFlags_IdxRefInArcFromZero
														| PolyCreateFlags_IdxRefInContourEndFromZero
														| PolyCreateFlags_DummyContourEndAtIdxZero
	};

	//Flags used when regularizing IrregularPolygon2Ds, function: for requesting and for returning as results
	enum PolyRegularizationFlags {
		PolyRegularizationFlags_WasIrregular	= 0x0001,	//indicates whether the regularized Polygon was actually irregular before regularization
		PolyRegularizationFlags_NewVertex		= 0x0002,	//indicates if new vertices appeared as a result of regularization
		PolyRegularizationFlags_NewEdge			= 0x0004,	//indicates if new edges appeared as a result of regularization
		PolyRegularizationFlags_NewContour		= 0x0010,	//indicates if new contours appeared as a result of regularization
		PolyRegularizationFlags_LostVertex		= 0x0020,	//indicates whether any vertices were lost during regularization
		PolyRegularizationFlags_LostEdge		= 0x0040,	//indicates whether any edges were lost during regularization
		PolyRegularizationFlags_LostContour		= 0x0200,	//indicates whether any contours were lost during regularization
		PolyRegularizationFlags_SplitEdge		= 0x0400,	//indicates whether there were any split edges during regularization
		PolyRegularizationFlags_SplitContour	= 0x0800,	//indicates whether there were any split contours during regularization
		PolyRegularizationFlags_ReversedContour	= 0x1000,	//indicates whether there were any reversed contours during regularization
		PolyRegularizationFlags_OnlyReversed	= 0x2000,	//indicates whether the original Polygon was only irregular because of reversed contours

		PolyRegularizationFlags_All				= PolyRegularizationFlags_WasIrregular
												| PolyRegularizationFlags_NewVertex
												| PolyRegularizationFlags_NewEdge
												| PolyRegularizationFlags_NewContour
												| PolyRegularizationFlags_LostVertex
												| PolyRegularizationFlags_LostEdge
												| PolyRegularizationFlags_LostContour
												| PolyRegularizationFlags_SplitEdge
												| PolyRegularizationFlags_SplitContour
												| PolyRegularizationFlags_ReversedContour
												| PolyRegularizationFlags_OnlyReversed
	};

	enum PolyCheckFlags {
		PolyCheckFlags_Zero0thElements			= 0x0001,
		PolyCheckFlags_InvalidDoubles			= 0x0002,
		PolyCheckFlags_DenormalDoubles			= 0x0004,
		PolyCheckFlags_CoordRange				= 0x0008,
		PolyCheckFlags_ContourHasFewVertices	= 0x0010,
		PolyCheckFlags_TooSmallArcs				= 0x0020,

		PolyCheckFlags_All_Polygon				= PolyCheckFlags_Zero0thElements
												| PolyCheckFlags_InvalidDoubles
												| PolyCheckFlags_DenormalDoubles
												| PolyCheckFlags_CoordRange
												| PolyCheckFlags_ContourHasFewVertices
												| PolyCheckFlags_TooSmallArcs,

		PolyCheckFlags_All_Polyline				= PolyCheckFlags_Zero0thElements
												| PolyCheckFlags_InvalidDoubles
												| PolyCheckFlags_DenormalDoubles
												| PolyCheckFlags_CoordRange
												| PolyCheckFlags_TooSmallArcs
	};

	struct PolyRepairResult {
		bool succeeded;
		bool modified;
	};

	inline void ThrowGeometryExceptionAtError (GSErrCode errorCode, const char* msg, const char* srcFile, int srcLineNum)
	{
		if (errorCode == NoError)
			return;
		if (errorCode == ErrMemoryFull)
			throw GS::OutOfMemoryException (msg, srcFile, srcLineNum);
		throw GeometryException (msg, srcFile, srcLineNum);
	}

	// Represents an id that is used for Polygons/Polylines and their components (Contour, Vertex, Edge)
	class GEOMETRY_DLL_EXPORT PolyId {
	protected:
		static const char*		XMLTag_PolyId;

		UInt32 id = 0;
	public:
		PolyId () = default;
		explicit PolyId (UInt32 polyId) { id = polyId; }

		bool operator== (const PolyId& polyId) const {return id == polyId.id;}
		bool operator!= (const PolyId& polyId) const {return id != polyId.id;}
		PolyId& operator++() {id++; return *this;}
		bool operator< (const PolyId& polyId) const {return (id < polyId.id);}

		UInt32 Get () const { return id; }

		GSErrCode	Read (GS::IChannel& ic)
		{
			return ic.Read (id);
		}
		
		GSErrCode	Write (GS::OChannel& oc) const
		{
			return oc.Write (id);
		}

		GSErrCode	ReadXML	(GS::XMLIChannel& ic, const char* tagName = nullptr)
		{
			return ic.ReadXML (tagName == nullptr ? XMLTag_PolyId : tagName, id);
		}
		GSErrCode	WriteXML (GS::XMLOChannel& oc, const char* tagName = nullptr) const
		{
			return oc.WriteXML (tagName == nullptr ? XMLTag_PolyId : tagName, id);
		}

		template <class Output>
		void	Print	(Output& oc) const
		{
			oc << "\t" << id;
		}

		ULong	GenerateHashValue () const
		{
			return  GS::CalculateHashValue (id);
		}

		GSErrCode Store (GS::ObjectState& os) const;
		GSErrCode Restore (const GS::ObjectState& os);
		
	};
	inline GSErrCode	ReadXML (GS::XMLIChannel& ic, const char* /*tagName*/, PolyId& userData)		{ return userData.ReadXML (ic); }
	inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const char* /*tagName*/, const PolyId& userData)	{ return userData.WriteXML (oc); }

	GEOMETRY_DLL_EXPORT extern const PolyId NullPolyId;

	template <class Poly2DType, class CustomData>
	class ConstPolyVertexInPoly
	{
	private:
		const Poly2DType*		poly;
		UIndex					index;

	public:
		ConstPolyVertexInPoly () : poly (nullptr), index (0) {};
		ConstPolyVertexInPoly (const Poly2DType* poly2D, UIndex idx) : poly (poly2D), index (idx) {};

		void SetIndex (UIndex idx) { index = idx; }
		UIndex GetIndex () const { return index; }

		const Point2D& GetCoord () const
		{
			return poly->GetVertexCoordByIdx (index);
		}

		const CustomData& GetPolyVertexUserData () const
		{
			if ((poly->GetPolyFlags () & PolyFlags_IsVertexUserData) != 0)
				return poly->GetVertexUserDataByIdx (index);
			static  CustomData id;
			return id;
		}
	};

	template <class Poly2DType, class CustomData>
	class ConstPolyEdgeInPoly
	{
	private:
		const Poly2DType*		poly;
		UIndex					index;

	public:
		ConstPolyEdgeInPoly () : poly (nullptr), index (0) {};
		ConstPolyEdgeInPoly (const Poly2DType* poly2D, UIndex idx) : poly (poly2D), index (idx) {};

		void SetIndex (UIndex idx) { index = idx; }
		UIndex GetIndex () const { return index; }

		double GetArcAngle () const { return poly->GetEdgeArcAngleByIdx (index);}
		bool GetSector (Sector& sect, GenArc& genArc) const { return poly->GetSectorById (index, sect, genArc);}
		GS::Optional<Sector> GetSector	() const { return poly->GetSectorById	(index); }
		GS::Optional<GenArc> GetArc		() const { return poly->GetArcById		(index); }
		const CustomData& GetPolyEdgeUserData () const { 
			if ((poly->GetPolyFlags () & PolyFlags_IsEdgeUserData) != 0)
				return poly->GetEdgeUserDataByIdx (index);
			static  CustomData id;
			return id;
		}

		bool IsStraight () const
		{
			return (fabs (GetArcAngle ()) < EPS);
		}

		double	GetLength () const
		{
			return poly->GetEdgeLengthByIdx (index);
		}

		Box2DData GetBoundingBox () const
		{
			if (IsStraight ()) {
				GS::Optional<Sector> sector = GetSector ();
				return Geometry::SectorBox (&sector.Get ());
			} else {
				GS::Optional<GenArc> arc = GetArc ();
				return Geometry::GetGenArcBoundBox (arc.Get ());
			}
		}

		Coord GetBeginCoord () const
		{
			if (IsStraight ()) {
				GS::Optional<Sector> sector = GetSector ();
				return sector.Get ().c1;
			} else {
				GS::Optional<GenArc> arc = GetArc ();
				return arc.Get ().GetBegC ();
			}
		}


		Coord GetEndCoord () const
		{
			if (IsStraight ()) {
				GS::Optional<Sector> sector = GetSector ();
				return sector.Get ().c2;
			} else {
				GS::Optional<GenArc> arc = GetArc ();
				return arc.Get ().GetEndC ();
			}
		}
	};

	template <class CustomData>
	class CustomPolyVertex
	{
	private:
		Point2D				coord;
		CustomData			id;

	public:
		CustomPolyVertex () = default;

		template <class Poly2DType1, class CustomData1>
		CustomPolyVertex (const ConstPolyVertexInPoly<Poly2DType1, CustomData1>& source)
		{
			coord = source.GetCoord ();
			id = source.GetPolyVertexUserData ();
		}

		CustomPolyVertex (const Point2D& c, const CustomData& pId = CustomData ())
		{
			coord = c;
			id = pId;
		}

		const Point2D& GetCoord () const
		{
			return coord;
		}
		Point2D& GetCoordRef ()
		{
			return coord;
		}
		void SetCoord (const Point2D& newCoord)
		{
			coord = newCoord;
		}

		const CustomData& GetPolyVertexUserData () const
		{
			return id;
		}
		void SetPolyVertexUserData (const CustomData& newId)
		{
			id = newId;
		}

		void Clear ()
		{
			coord.x = coord.y = 0.0;
			id = CustomData ();
		}
	};

	template <class CustomData>
	class CustomPolyEdge
	{
	private:
		double arcAngle;
		CustomData id;

	public:

		CustomPolyEdge ()
		{
			arcAngle = 0.0;
		}

		template <class Poly2DType1, class CustomData1>
		CustomPolyEdge (const ConstPolyEdgeInPoly<Poly2DType1, CustomData1>& source)
		{
			arcAngle = source.GetArcAngle ();
			id = source.GetPolyEdgeUserData ();
		}

		CustomPolyEdge (double angle, const CustomData& pId = CustomData ())
		{
			arcAngle = angle;
			id = pId;
		}

		const double& GetArcAngle () const
		{
			return arcAngle;
		}

		void SetArcAngle (double newArc)
		{
			arcAngle = newArc;
		}

		const CustomData& GetPolyEdgeUserData () const
		{
			return id;
		}
		void SetPolyEdgeUserData (const CustomData& newId)
		{
			id = newId;
		}

		void Clear ()
		{
			arcAngle = 0.0;
			id = CustomData ();
		}

		bool IsStraight () const
		{
			return fabs (arcAngle) <= RadEps;
		}

		bool HasInvalidAngle () const
		{
			return arcAngle == GetInvalidAngle ();
		}
		static double GetInvalidAngle ()
		{
			return INF;
		}
	};

	template <class CustomDataVertex, class CustomDataEdge>
	class CustomPolySegment
	{
	protected:
		CustomPolyVertex <CustomDataVertex>	vertex;
		CustomPolyEdge <CustomDataEdge>		edge;
		Geometry::NurbsCurve2D				nurbs;

	public:
		CustomPolySegment () = default;

		CustomPolySegment (const CustomPolyVertex<CustomDataVertex>& v, const CustomPolyEdge<CustomDataEdge>& e) :
			vertex (v),
			edge (e)
		{	
			nurbs.Clear ();
		}

		CustomPolySegment (const CustomPolyVertex<CustomDataVertex>& v, const CustomPolyEdge<CustomDataEdge>& e, const NurbsCurve2D& nurbs) :
			vertex (v),
			edge (e),
			nurbs (nurbs)
		{
		}

		const CustomPolyVertex<CustomDataVertex>& GetVertex () const
		{
			return vertex;
		}
		CustomPolyVertex<CustomDataVertex>& GetVertexRef ()
		{
			return vertex;
		}
		const CustomPolyEdge<CustomDataEdge>& GetEdge () const
		{
			return edge;
		}
		CustomPolyEdge<CustomDataEdge>& GetEdgeRef ()
		{
			return edge;
		}
		const NurbsCurve2D& GetNurbs () const
		{
			return nurbs;
		}
		NurbsCurve2D& GetNurbsRef ()
		{
			return nurbs;
		}

		void Clear ()
		{
			vertex = CustomPolyVertex<CustomDataVertex> ();
			edge = CustomPolyEdge<CustomDataEdge> ();
			nurbs.Clear ();
		}
	};

	template <class CustomDataVertex, class CustomDataEdge, class CustomDataContour>
	class CustomPolyContourDescription
	{
	protected:
		CustomDataContour							id;
		GS::Array<CustomPolySegment <CustomDataVertex, CustomDataEdge> >			segmentList;
	public:
		const CustomDataContour& GetPolyContourUserData () const
		{
			return id;
		}
		void SetPolyContourUserData (const CustomDataContour& newId)
		{
			id = newId;
		}
		const GS::Array<CustomPolySegment<CustomDataVertex, CustomDataEdge> >& GetSegmentList () const
		{
			return segmentList;
		}
		GS::Array<CustomPolySegment<CustomDataVertex, CustomDataEdge> >& GetSegmentListRef ()
		{
			return segmentList;
		}

		void Clear ()
		{
			id = CustomDataContour ();
			segmentList.Clear ();
		}
	};

	typedef CustomPolyContourDescription<PolyId, PolyId, PolyId> PolyContourDescription;
	typedef CustomPolyVertex<PolyId> PolyVertex;
	typedef CustomPolyEdge<PolyId> PolyEdge;
	typedef CustomPolySegment<PolyId, PolyId> PolySegment;

	// below interfaces are used in CutElem and ElemPolyDifference
	class GEOMETRY_DLL_EXPORT SectorCreator
	{
	public:
		virtual ~SectorCreator ();
		virtual void CreateSector (const Sector& sector) = 0;
	};
	class GEOMETRY_DLL_EXPORT GenArcCreator
	{
	public:
		virtual ~GenArcCreator ();
		virtual void CreateGenArc (const GenArc& genArc) = 0;
	};
	class GEOMETRY_DLL_EXPORT PointCreator
	{
	public:
		virtual ~PointCreator ();
		virtual void CreatePoint (const Point2D& coord) = 0;
	};
	class GEOMETRY_DLL_EXPORT SplineCreator
	{
	public:
		virtual ~SplineCreator ();
		virtual void CreateSpline (const BezierDetails& bezier) = 0;
	};

	template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
	class CustomPolygon2DCreator
	{
	public:
		CustomPolygon2DCreator () {}
		virtual void CreatePolygon2D (const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & polygon) = 0;
	};
	typedef CustomPolygon2DCreator<PolyId, PolyId, PolyId, PolyId> Polygon2DCreator;

	template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
	class CustomIrregularPolygon2DCreator
	{
	public:
		CustomIrregularPolygon2DCreator () {}
		virtual void CreateIrregularPolygon2D (const CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & polygon) = 0;
	};
	typedef CustomIrregularPolygon2DCreator<PolyId, PolyId, PolyId, PolyId> IrregularPolygon2DCreator;

	template <class VertexUserData, class EdgeUserData, class PolygonUserData>
	class CustomPolyline2DCreator
	{
	public:
		CustomPolyline2DCreator () {}
		virtual void CreatePolyline2D (const CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData> & polyline) = 0;
	};
	typedef CustomPolyline2DCreator<PolyId, PolyId, PolyId> Polyline2DCreator;

	template <typename TData>
	static void CopyInfo_Data (GS::Array <TData>& toData, USize toIndex, const GS::Array <TData>& fromData, USize fromIndex, USize size)
	{
		if (fromIndex > toIndex) {
			for (USize i = 0; i < size; i++)
				toData[toIndex + i] = fromData[fromIndex + i];
		} else {
			for (USize i = 0; i < size; i++)
				toData[toIndex + size - 1 - i] = fromData[fromIndex + size - 1 - i];
		}
	}
	template <typename TData>
	static void ZeroInfo_Data (GS::Array <TData>& toData, USize toIndex, USize size, const TData& data)
	{
		for (USize i = 0; i < size; i++)
			toData[toIndex + i] = data;
	}
	
	
	template<typename VertexUserData, typename EdgeUserData, typename ContourUserData>
	struct ContourForSwap {
		USize						nVertices;
		GS::Array <Point2D>			vertices;
		GS::Array <VertexUserData>	vertexInfos;
		
		USize						nArcs;
		GS::Array <PolyArcRec>		arcs;
		GS::Array <EdgeUserData>	inhEdgeInfos;
		
		ContourUserData				contourInfo;
		
		ContourForSwap () : nVertices(0), nArcs(0), contourInfo () {}
	};
}		// namespace Geometry


#endif //GEOMETRY_POLY2D_HPP
