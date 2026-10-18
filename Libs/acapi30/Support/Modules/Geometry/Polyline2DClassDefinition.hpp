// *****************************************************************************
//
// Declaration of Polyline2D class
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	RA
//
// *****************************************************************************

#ifndef GEOMETRY_POLYLINE2D_CLASSDEFINITION_HPP
#define GEOMETRY_POLYLINE2D_CLASSDEFINITION_HPP

#if defined (_MSC_VER)
#pragma once
#endif

// --- Includes ----------------------------------------------------------------
// from GSRoot
#include "Definitions.hpp"
#include "Array.hpp"

// from Geometry
#include "Poly2DTypes.hpp"

#include "Poly2D.hpp"
#include "Poly2DIterator.hpp"
#include "CorePolyline2D.hpp"

#include "IrregularPolygon2DClassDefinition.hpp"

#include "CutElems.h"

namespace Geometry {

	class GEOMETRY_DLL_EXPORT Polyline2DPrivate {
	public:
		static GS::ClassInfo	classInfo;
	};

	template <class VertexUserData, class EdgeUserData, class PolygonUserData>
	class CustomPolyline2D
	{
		template <class VertexUserData1, class EdgeUserData1, class ContourUserData1, class PolygonUserData1>
		friend class CustomPolygon2D;
		template <class VertexUserData1, class EdgeUserData1, class ContourUserData1, class PolygonUserData1>
		friend class CustomIrregularPolygon2D;
		template <class VertexUserData1, class EdgeUserData1, class ContourUserData1, class PolygonUserData1>
		friend class CustomMultiPolygon2D;
		template <class VertexUserData1, class EdgeUserData1, class ContourUserData1, class PolygonUserData1>
		friend class CustomMultiIrregularPolygon2D;
		template <class VertexUserData1, class EdgeUserData1, class PolygonUserData1>
		friend class CustomPolyline2D;
		template <class VertexUserData1, class EdgeUserData1, class PolygonUserData1>
		friend class CustomMultiPolyline2D;

		friend class ConstPolyVertexInPolyState<CustomPolyline2D, VertexUserData>;
		friend class ConstPolyEdgeInPolyState<CustomPolyline2D, EdgeUserData>;
		friend class ConstPolyVertexInPoly<CustomPolyline2D, VertexUserData>;
		friend class ConstPolyEdgeInPoly<CustomPolyline2D, EdgeUserData>;

	public:
		typedef VertexUserData		VertexUserDataType;
		typedef EdgeUserData		EdgeUserDataType;
		typedef PolygonUserData		PolylineUserDataType;

		enum PolylinePointPosition {PointOnRightSide, PointOnPolyline, PointOnLeftSide};

		typedef CorePolyline2DVertexVisitor			VertexVisitor;
		typedef CorePolyline2DConstVertexVisitor	ConstVertexVisitor;
		
		typedef CustomPolyVertex<VertexUserData>	Vertex;
		typedef CustomPolyEdge<EdgeUserData>		Edge;

		typedef CustomPolySegment<VertexUserData, EdgeUserData> Segment;
		typedef CustomPolyContourDescription<VertexUserData, EdgeUserData, PolygonUserData> ContourDescription;

		typedef GS::ConstBidirectionalItemIteratorBase <CustomPolyline2D, ConstPolyVertexInPolyState<CustomPolyline2D, VertexUserData>, ConstPolyVertexInPoly<CustomPolyline2D, VertexUserData>> ConstVertexIterator;
		typedef GS::ConstBidirectionalItemIteratorBase <CustomPolyline2D, ConstPolyEdgeInPolyState<CustomPolyline2D, EdgeUserData>, ConstPolyEdgeInPoly<CustomPolyline2D, EdgeUserData>> ConstEdgeIterator;

		template <class ContourUserData>
		using Polygon2DType				= CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>;
		template <class ContourUserData>
		using IrregularPolygon2DType	= CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>;
		template <class ContourUserData>
		using MultiPolygon2DType		= CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>;
		using MultiPolyline2DType		= CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>;
		using CorePolyline2DType		= CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>;

	protected:
		GS::SharedPtr<CorePolyline2DType>		polyline;

	protected:
		CustomPolyline2D	(const GS::SharedPtr<CorePolyline2DType>& polyline2D);

		static MultiPolyline2DType		Create		 (const GS::Array<GS::SharedPtr<CorePolyline2DType>>& polylineArray);
		CustomPolyline2D				CreateResult (typename CorePolyline2DType::PolylineResult polyResult, const GS::SharedPtr<CorePolyline2DType>& newPolyline) const;
		MultiPolyline2DType				CreateResult (typename CorePolyline2DType::PolylineResult polyResult, const GS::Array<GS::SharedPtr<CorePolyline2DType>>& polylineArray) const;

		void CopyOnWrite ();
	protected:
		const Point2D& GetVertexCoordByIdx (UIndex vertexIdx) const
		{
			return const_cast<const CorePolyline2DType*> (&*polyline)->GetCoord (vertexIdx);
		}
		const VertexUserData& GetVertexUserDataByIdx (UIndex vertexIdx) const
		{
			return *polyline->GetVertexUserData (vertexIdx);
		}
		UIndex GetNextVertexIndex (UIndex vertexIdx, const VertexUserData& id) const
		{
			return polyline->GetNextVertexIndex (vertexIdx, &id);
		}
		UIndex GetPrevVertexIndex (UIndex vertexIdx, const VertexUserData& id) const
		{
			return polyline->GetPrevVertexIndex (vertexIdx, &id);
		}

		double GetEdgeArcAngleByIdx (UIndex edgeIdx) const
		{
			return polyline->GetArcAngle (edgeIdx);
		}
		double GetEdgeLengthByIdx (UIndex edgeIdx) const
		{
			return polyline->GetEdgeLength (edgeIdx);
		}
		bool GetSectorById (UIndex edgeIdx, Sector& sect, GenArc& genArc) const
		{
			return polyline->GetSector (edgeIdx, sect, genArc);
		}
		GS::Optional<Sector> GetSectorById (UIndex edgeIdx) const
		{
			return polyline->GetSector (edgeIdx);
		}
		GS::Optional<GenArc> GetArcById (UIndex edgeIdx) const
		{
			return polyline->GetArc (edgeIdx);
		}
		const EdgeUserData& GetEdgeUserDataByIdx (UIndex edgeIdx) const
		{
			return *polyline->GetEdgeUserData (edgeIdx);
		}
		UIndex GetNextEdgeIndex (UIndex edgeIdx, const EdgeUserData& id) const
		{
			return polyline->GetNextEdgeIndex (edgeIdx, &id);
		}
		UIndex GetPrevEdgeIndex (UIndex edgeIdx, const EdgeUserData& id) const
		{
			return polyline->GetPrevEdgeIndex (edgeIdx, &id);
		}

		static typename CorePolyline2DType::Flags GetFlags (GS::UInt32 flags /*PolyFlags*/);

	public:
		// Constructs an empty Polyline, where all sizes (number of vertices and arcs) are 0 and corresponding data is uninitialized, PolyFlags all set to true values
		// For info on PolyFlags please, check Poly2D.hpp
		CustomPolyline2D ();
		CustomPolyline2D (const CustomPolyline2D& source);
		CustomPolyline2D (CustomPolyline2D&& source) = default;
		// The next two construct a Polyline from a Polygon contour
		template <class ContourUserData>
		CustomPolyline2D (const Polygon2DType<ContourUserData>& polygon, typename Polygon2DType<ContourUserData>::ConstContourIterator contourIterator);
		template <class ContourUserData>
		CustomPolyline2D (const IrregularPolygon2DType<ContourUserData>& polygon, typename IrregularPolygon2DType<ContourUserData>::ConstContourIterator contourIterator);

		// Constructs a rectangle Polyline with the box parameter as bounds, PolyFlags all set to true values
		explicit CustomPolyline2D (const Box2DData& box);
		// Constructs a Polyline from a contour description, PolyFlags all set to true values
		// If the result of creation is empty then we get an empty Polyline
		explicit CustomPolyline2D (const ContourDescription& contourDesc);
		// The next four methods construct a Polyline from a list of coordinates and PolyArcs using several flags to determine the input format
		// See Poly2D.hpp for detailed info on PolyCreateFlag
		CustomPolyline2D (const GS::Array<Point2D>& coordList, const GS::Array<PolyArcRec>& arcList, GS::UInt32 createFlags /*PolyCreateFlags*/);
		CustomPolyline2D (const GS::Array<Point2D>& coordList, GS::UInt32 createFlags /*PolyCreateFlags*/);
		// nValuableCoords indicates the number of coords not counting the possible initial dummy blank coord
		// nValuableArcs indicates the number of arcs not counting the possible initial dummy blank arc
		CustomPolyline2D (const Point2D* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nValuableArcs, GS::UInt32 createFlags /*PolyCreateFlags*/);
		CustomPolyline2D (const Point2D* coords, USize nValuableCoords, GS::UInt32 createFlags /*PolyCreateFlags*/);
		// Constructs a Polyline by segmenting up a GenArc - i.e. replaces the curve with line sections - using arcDivParams as granulation for the segmentation
		CustomPolyline2D (const GenArc genArc, const ArcDivParams& arcDivParams);

		// Constructs an empty Polyline, where all sizes (number of vertices and arcs) are 0 and corresponding data is uninitialized, PolyFlags provided by caller
		// For info on PolyFlags please, check Poly2D.hpp
		explicit CustomPolyline2D (GS::UInt32 flags /*PolyFlags*/);
		// Constructs a rectangle Polyline with the box parameter as bounds, PolyFlags provided by caller
		CustomPolyline2D (GS::UInt32 flags /*PolyFlags*/, const Box2DData& box);
		// Constructs a Polyline from a contour description, PolyFlags provided by caller
		// If the result of creation is empty then we get an empty Polyline
		CustomPolyline2D (GS::UInt32 flags /*PolyFlags*/, const ContourDescription& contourDesc);
		// The next four methods create a Polyline from a list of coordinates and PolyArcs using several flags to determine the input format, PolyFlags provided by caller
		// See Poly2D.hpp for detailed info on PolyFlags and PolyCreateFlags
		CustomPolyline2D (GS::UInt32 flags /*PolyFlags*/, const GS::Array<Point2D>& coordList, const GS::Array<PolyArcRec>& arcList, GS::UInt32 createFlags /*PolyCreateFlags*/);
		CustomPolyline2D (GS::UInt32 flags /*PolyFlags*/, const GS::Array<Point2D>& coordList, GS::UInt32 createFlags /*PolyCreateFlags*/);
		// nValuableCoords indicates the number of coords not counting the possible initial dummy blank coord
		// nValuableArcs indicates the number of arcs not counting the possible initial dummy blank arc
		CustomPolyline2D (GS::UInt32 flags /*PolyFlags*/, const Point2D* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nValuableArcs, GS::UInt32 createFlags /*PolyCreateFlags*/);
		CustomPolyline2D (GS::UInt32 flags /*PolyFlags*/, const Point2D* coords, USize nValuableCoords, GS::UInt32 createFlags /*PolyCreateFlags*/);
		// Constructs a Polyline by segmenting up a GenArc - i.e. replaces the curve with line sections - using arcDivParams as granulation for the segmentation, PolyFlags provided by caller
		// See Poly2D.hpp for detailed info on PolyFlags
		CustomPolyline2D (GS::UInt32 flags /*PolyFlags*/, const GenArc genArc, const ArcDivParams& arcDivParams);

		~CustomPolyline2D ();

		GS::ClassVersion	GetClassVersion () const {return Polyline2DPrivate::classInfo.GetVersion ();}

		// See corresponding constructor (same parameter list)
		static CustomPolyline2D		Create (const ContourDescription& contourDesc);
		static CustomPolyline2D		Create (const GS::Array<Point2D>& coordList, const GS::Array<PolyArcRec>& arcList, GS::UInt32 createFlags /*PolyCreateFlags*/);
		static CustomPolyline2D		Create (const GS::Array<Point2D>& coordList, GS::UInt32 createFlags /*PolyCreateFlags*/);
		static CustomPolyline2D		Create (const Point2D* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nValuableArcs, GS::UInt32 createFlags /*PolyCreateFlags*/);
		static CustomPolyline2D		Create (const Point2D* coords, USize nValuableCoords, GS::UInt32 createFlags /*PolyCreateFlags*/);
		static CustomPolyline2D		Create (const GenArc genArc, const ArcDivParams& arcDivParams);
		// Creates a Polyline from a contour description array
		// If the result of creation is empty then we get an empty MultiPolyline
		static MultiPolyline2DType	Create (const GS::Array<ContourDescription>& contourDesc);
		// The next two methods create a MultiPolyline2D from a list of coordinates, PolyArcs and contour end indices (one contour - one Polyline) using several flags to determine the input format
		// See Poly2D.hpp for detailed info on PolyCreateFlags
		// nValuableCoords indicates the number of coords not counting the possible initial dummy blank coord
		// nValuableArcs indicates the number of arcs not counting the possible initial dummy blank arc
		// nContours indicates the number of resulting Polylines
		static MultiPolyline2DType	Create (const Point2D* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nValuableArcs, const UIndex* contourEnds, USize nContours, GS::UInt32 createFlags /*PolyCreateFlags*/);
		static MultiPolyline2DType	Create (const GS::Array<Point2D>& coordList, const GS::Array<PolyArcRec>& arcList, const GS::Array<UIndex>& contourEndList, GS::UInt32 createFlags /*PolyCreateFlags*/);

		// See corresponding constructor (same parameter list without the last)
		template <class ContourUserData>
		static CustomPolyline2D		Create (const Polygon2DType<ContourUserData>& polygon, typename Polygon2DType<ContourUserData>::ConstContourIterator contourIterator);
		// Creates a Polyline from each contour of the input Polygon
		template <class ContourUserData>
		static MultiPolyline2DType	Create (const Polygon2DType<ContourUserData>& polygon);
		// See corresponding constructor (same parameter list without the last)
		template <class ContourUserData>
		static CustomPolyline2D		Create (const IrregularPolygon2DType<ContourUserData>& polygon, typename IrregularPolygon2DType<ContourUserData>::ConstContourIterator contourIterator);
		// Creates a Polyline from each contour of the input Polygon
		template <class ContourUserData>
		static MultiPolyline2DType	Create (const IrregularPolygon2DType<ContourUserData>& polygon);

		// See corresponding constructor (same parameter list without the last)
		static CustomPolyline2D		Create (GS::UInt32 flags /*PolyFlags*/, const ContourDescription& contourDesc);
		// See corresponding constructor (same parameter list without the last)
		static CustomPolyline2D		Create (GS::UInt32 flags /*PolyFlags*/, const GS::Array<Point2D>& coordList, const GS::Array<PolyArcRec>& arcList, GS::UInt32 createFlags /*PolyCreateFlags*/);
		// See corresponding constructor (same parameter list without the last)
		static CustomPolyline2D		Create (GS::UInt32 flags /*PolyFlags*/, const GS::Array<Point2D>& coordList, GS::UInt32 createFlags /*PolyCreateFlags*/);
		// See corresponding constructor (same parameter list without the last)
		static CustomPolyline2D		Create (GS::UInt32 flags /*PolyFlags*/, const Point2D* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nValuableArcs, GS::UInt32 createFlags /*PolyCreateFlags*/);
		// See corresponding constructor (same parameter list without the last)
		static CustomPolyline2D		Create (GS::UInt32 flags /*PolyFlags*/, const Point2D* coords, USize nValuableCoords, GS::UInt32 createFlags /*PolyCreateFlags*/);
		// See corresponding constructor (same parameter list without the last)
		static CustomPolyline2D		Create (GS::UInt32 flags /*PolyFlags*/, const GenArc genArc, const ArcDivParams& arcDivParams);
		// Creates a Polyline from a contour description array, PolyFlags provided by caller
		// If the result of creation is empty then we get an empty MultiPolyline
		static MultiPolyline2DType	Create (GS::UInt32 flags /*PolyFlags*/, const GS::Array<ContourDescription>& contourDesc);

		// The next two methods create a MultiPolyline2D from a list of coordinates, PolyArcs and contour end indices (one contour - one Polyline) using several flags to determine the input format,
		// PolyFlags provided by caller
		// See Poly2D.hpp for detailed info on PolyFlags and PolyCreateFlags
		// nValuableCoords indicates the number of coords not counting the possible initial dummy blank coord
		// nValuableArcs indicates the number of arcs not counting the possible initial dummy blank arc
		// nContours indicates the number of resulting Polylines
		static MultiPolyline2DType	Create (GS::UInt32 flags /*PolyFlags*/, const Point2D* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nValuableArcs, const UIndex* contourEnds, USize nContours, GS::UInt32 createFlags /*PolyCreateFlags*/);
		static MultiPolyline2DType	Create (GS::UInt32 flags /*PolyFlags*/, const GS::Array<Point2D>& coordList, const GS::Array<PolyArcRec>& arcList, const GS::Array<UIndex>& contourEndList, GS::UInt32 createFlags /*PolyCreateFlags*/);

		// Converts the Polyline to a contour description
		ContourDescription	ConvertToContourDescription () const;
		void				ArcToNurbs ();
		// Converts the Polyline to an array of Polygons (if the Polyline is self intersecting it will result in more than one Polygon)
		template <class ContourUserData>
		MultiPolygon2DType<ContourUserData>		ConvertToPolygon () const;

		template <class VertexUserData1, class EdgeUserData1, class PolygonUserData1>
		static CustomPolyline2D					ConvertFromPolyline2D (const CustomPolyline2D<VertexUserData1, EdgeUserData1, PolygonUserData1>& source);

		// Copies the Polyline's vertices into a coord list and its curved edges into a PolyArcRec list
		// where the caller must specify several flags to indicate the output format - See Poly2D.hpp for detailed info on PolyCreateFlags
		// nValuableCoords indicates the expected number of resulting coords not counting the possible initial dummy blank coord
		// nValuableArcs indicates the expected number of resulting arcs not counting the possible initial dummy blank arc
		// If the caller specifies either coords or arcs as nullptr, the corresponding size will still be returned but no copying will be done
		// If the caller specifies either nValuableCoords or nValuableArcs as a smaller number than the actual corresponding size but does actually expect a result
		// (pointer not nullptr) then an OutOfMemoryException is thrown
		void CopyPolylineData (Point2D* coords, USize& nValuableCoords, PolyArcRec* arcs, USize& nValuableArcs, GS::Array<NurbsCurve2D>& nurbs, GS::UInt32 createFlags /*PolyCreateFlags*/) const;
		// Similar to previous but uses GS::Arrays instead of pointers
		// Copies the Polygon's vertices into a coord list and its curved edges into a PolyArcRec list
		// where the caller must specify several flags to indicate the output format - See Poly2D.hpp for detailed info on PolyCreateFlags
		void CopyPolylineData (GS::Array<Point2D>& coords, GS::Array<PolyArcRec>& arcs, GS::Array<NurbsCurve2D>& nurbs, GS::UInt32 createFlags /*PolyCreateFlags*/) const;

		// Copies the Polyline's vertices into a coord list and its curved edges into a PolyArcRec list
		// where the caller must specify several flags to indicate the output format - See Poly2D.hpp for detailed info on PolyCreateFlags
		// The memory for the lists is allocated within the method
		// nValuableCoords indicates the expected number of resulting coords not counting the possible initial dummy blank coord
		// nValuableArcs indicates the expected number of resulting arcs not counting the possible initial dummy blank arc
		// If the caller specifies either nValuableCoords or nValuableArcs as a smaller number than the actual corresponding size but does actually expect a result
		// (pointer not nullptr) then an OutOfMemoryException is thrown
		void AllocateAndCopyPolylineData (Point2D** coords, USize& nValuableCoords, PolyArcRec** arcs, USize& nValuableArcs, GS::UInt32 createFlags /*PolyCreateFlags*/) const;

		CustomPolyline2D&	operator= (const CustomPolyline2D& source);
		CustomPolyline2D&	operator= (CustomPolyline2D&& source) = default;

		bool	operator== (const CustomPolyline2D& rightOp) const;
		bool	operator!= (const CustomPolyline2D& rightOp) const;

		// Enables or disables the possibility of two succeeding edges with the same direction (two edges in one line)
		// calling with false parameter ensures that there are none of these edges by removing edges and vertices if needed
		void		SetSameDirEdgeLegal (bool isSameDirEdgeLegal);
		// Returns whether it is possible for two succeeding edges to have the same direction (two edges in one line)
		bool		GetSameDirEdgeLegal () const;
		// For info on PolyFlags please, check Poly2D.hpp
		void		SetPolyFlags (GS::UInt32 flags /*PolyFlags*/);
		GS::UInt32	GetPolyFlags () const;

		void		SetClosed (bool isClosed);
		bool		GetClosed () const;
		void		DetectAndSetClosed ();

		ConstVertexIterator		GetVertexIterator (UIndex vertexIdx) const;
		ConstVertexIterator		GetVertexIterator (const Point2D& coord) const;
		ConstVertexIterator		EnumerateVertex () const;
		// Same as previous
		ConstVertexIterator		BeginVertex () const;
		ConstVertexIterator		EndVertex	() const;
		ConstVertexIterator		EnumerateVertex (const VertexUserData& id) const;

		ConstEdgeIterator		GetEdgeIterator (UIndex edgeIdx) const;
		ConstEdgeIterator		EnumerateEdge () const;
		// Same as previous
		ConstEdgeIterator		BeginEdge () const;
		ConstEdgeIterator		EndEdge	() const;
		ConstEdgeIterator		EnumerateEdge (const EdgeUserData& id) const;

		void	ResetUserData ();

		void					SetPolyUserData (const PolygonUserData& polyId);
		const PolygonUserData&	GetPolyUserData () const;

		const VertexUserData&	GetVertexDefaultUserData () const;
		void					SetVertexDefaultUserData (const VertexUserData& userData);

		USize			GetVertexNum () const;
		Vertex			GetVertex (const ConstVertexIterator& vertexIterator) const;
		const Point2D&	GetCoord (const ConstVertexIterator& vertexIterator) const;

		void					SetVertexUserData (const ConstVertexIterator& vertexIterator, const VertexUserData& vertexId);
		const VertexUserData&	GetVertexUserData (const ConstVertexIterator& vertexIterator) const;

		const EdgeUserData&		GetEdgeDefaultUserData () const;
		void					SetEdgeDefaultUserData (const EdgeUserData& userData);

		USize	GetEdgeNum () const;
		Edge	GetEdge (const ConstEdgeIterator& edgeIterator) const;
		// Returns true if the edge at edgeIterator is curved
		bool	GetSector (const ConstEdgeIterator& edgeIterator, Sector& sect, GenArc& genArc) const;
		// Returns true if the edge at edgeIterator is curved
		bool	GetSector (const ConstEdgeIterator& edgeIterator, Point2D& begC, Point2D& endC, double& angle) const;

		GS::Optional<Sector>	GetSector	(const ConstEdgeIterator& edgeIterator) const;
		GS::Optional<GenArc>	GetArc		(const ConstEdgeIterator& edgeIterator) const;

		void					SetEdgeUserData (const ConstEdgeIterator& edgeIterator, const EdgeUserData& edgeId);
		const EdgeUserData&		GetEdgeUserData (const ConstEdgeIterator& edgeIterator) const;

		ConstVertexIterator		GetBeginVertex (const ConstEdgeIterator& edgeIterator) const;
		ConstVertexIterator		GetEndVertex (const ConstEdgeIterator& edgeIterator) const;

		ConstEdgeIterator		GetNextEdge (const ConstVertexIterator& vertexIterator) const;
		ConstEdgeIterator		GetPrevEdge (const ConstVertexIterator& vertexIterator) const;

		bool	IsEmpty () const;
		bool	HasArcs () const;
		void	Clear ();

		// Returns true, if the polygon is a rectangle and its edges are parallel with the X and Y axises
		bool IsABox () const;

		GSErrCode	Read (GS::IChannel& ic);
		GSErrCode	Write (GS::OChannel& oc) const;
		GSErrCode	ReadXML	(GS::XMLIChannel& ic);
		GSErrCode	WriteXML (GS::XMLOChannel& oc) const;


		GSErrCode	Store (GS::ObjectState& os) const
		{
			os.Add ("polyline", *(polyline));
			return NoError;
		}

		GSErrCode	Restore (const GS::ObjectState& os)
		{
			typename Geometry::CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Flags flags;
			polyline = new Geometry::CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> (flags);
			os.Get ("polyline", *(polyline));
			return NoError;
		}

		//******************************* Calculate *******************************
		const Box2DData&	GetBoundBox () const;
		// Returns the center of the bounding box of the Polyline
		Point2D				GetCenter () const;
		// Returns the signed area of the Polyline (if it is not closed the area is calculated by closing it by a straight edge)
		double				CalcArea () const;
		// IsClockwise == IsNegativeOrder
		bool				IsClockwise () const;
		// Returns the accumulated length of the Polyline segments
		double				CalcLength () const;
		// Returns the maximum fillet radius that can belong to the vertex at vertexIterator
		double				CalcMaxVertexFillet (const ConstVertexIterator& vertexIterator) const;
		// Returns wether the given coordinate is on the polyline
		bool				IsCoordOnEdge (const Point2D& c, GS::Array<ConstEdgeIterator>* edgeIt = nullptr) const;
		// Returns the tangent of the polyline at the given point, throws exception if point not on polyline
		GS::Array<GS::Pair<ConstEdgeIterator, Vector2D>> GetTangentAtPoint (const Point2D& c) const;
		// Returns the middle point of a polyine, throws exception if empty
		Point2D				GetMiddlePoint () const;
		// Returns the bounding box of the Polyline we would get if we applied tr as a transformation matrix on this Polyline
		// if invTr is not nullptr then invTr will be applied to the box result
		GS::FixArray<Point2D, 4>	GetTransformedBoundBox (const TRANMAT& tr, const TRANMAT& invTr = Geometry::IdentityTranMat) const;
		// Returns the distance from polyline, throws exception if empty
		double				DistanceFromPoint (const Point2D& co, ConstEdgeIterator* edgeItOfMin = nullptr, GS::Array<bool>* filter = nullptr) const;
		//Returns the difference between the last edge's end direction, and the next edge's beginning direction (left turn : positive)
		double				GetTurningAngleAtVertex (const ConstVertexIterator& vertexIterator) const;

		void	Visit (ConstVertexVisitor &visitor) const;

		//******************************* Modify polyline *******************************
		void	Move (Vector2D offset);
		void	TransformPreserveArcs (const TRANMAT& tran);
		void	ClearVertexIds ();
		void	ClearEdgeIds ();
		void	Reverse ();  //Change vertex order

		void Stretch (	const Point2D& fixPoint,
						const Point2D& draggedPoint,
						const Vector2D& offsetAxisX,
						const Vector2D& offsetAxisY = Vector2D (0.0, 0.0),
						const ArcDivParams& arcDivParams = ArcDivParams (0.0));

		void	RotateVerticeIndices (const ConstVertexIterator& vertexToFirst);
		void	SortArcsByIndices ();
		void	Append (const CustomPolyline2D& polylineToAppend);
		void	Append (const Point2D& c, const bool atEnd = true);

		void	Visit (VertexVisitor &visitor);

		//******************************* Create new polylines *******************************
		// Transforms the Polyline with tran - if the transformation does not preserve arcs then arcDivParams is used as granulation to segment up the Polyline
		CustomPolyline2D	Transform (const ArcDivParams& arcDivParams, const TRANMAT& tran) const;
		// Same as previous but only transforms the parts of the Polyline that intersect with the filter Polygon or is on its edge
		template <class ContourUserData>
		CustomPolyline2D	Transform (const Polygon2DType<ContourUserData>& filterWithPolygon, const ArcDivParams& arcDivParams, const TRANMAT& tran, bool& isTransformedAll) const;
		// Same as first transform but only transforms the parts of the Polyline that intersect with any of the filter Polygons or is on the edge of any
		template <class ContourUserData>
		CustomPolyline2D	Transform (const MultiPolygon2DType<ContourUserData>& filterWithPolygon, const ArcDivParams& arcDivParams, const TRANMAT& tran, bool& isTransformedAll) const;
		// Segments up the Polyline - i.e. replaces all curves with line sections - using arcDivParams as granulation for the segmentation
		CustomPolyline2D	SegmentUp (const ArcDivParams& arcDivParams) const;
		// Makes all curved edges straight - this is not segmentation, number of edges and vertices remain the same!
		CustomPolyline2D	EliminateArcs () const;

		// Change vertex order
		// Reverses the direction of the Polyline (goes from last vertex to first vertex; in closed case last = first) into a copy
		CustomPolyline2D	GetReversed () const;

		// Offsets all edges in the Polyline with the given offset preserving edge angles
		CustomPolyline2D	OffsetAllEdge		(double offset, double* newOffset = nullptr) const;
		CustomPolyline2D	OffsetEdge			(const ConstEdgeIterator& edgeIterator, double offset) const;

		CustomPolyline2D	MoveVertex			(const ConstVertexIterator& vertexIterator, const Point2D& newPosition) const;
		CustomPolyline2D	FilletAllVertex		(const double filletRadius) const;
		CustomPolyline2D	FilletVertex		(const ConstVertexIterator& vertexIterator, const double filletRadius) const;
		CustomPolyline2D	ChamferAllVertex	(const double chamferRadius) const;
		CustomPolyline2D	ChamferVertex		(const ConstVertexIterator& vertexIterator, const double chamferRadius) const;

		// Inserts a vertex on the edge at edgeIterator to newPosition
		CustomPolyline2D	InsertVertex (const ConstEdgeIterator& edgeIterator, const Point2D& newPosition) const;
		// Inserts a vertex if vertex is on polyline, otherwise exception
		CustomPolyline2D	InsertVertexOnPolyline (const Point2D& newPosition, const ConstEdgeIterator& edgeIterator, UIndex* vertexIndex = nullptr) const;
		// Deletes the vertex at vertexIterator, connects the neighboring vertices
		CustomPolyline2D	DeleteVertex (const ConstVertexIterator& vertexIterator) const;
		// Sets the angle of the curve of the edge at edgeIterator to edgeAngle
		CustomPolyline2D	SetEdgeAngle (const ConstEdgeIterator& edgeIterator, double edgeAngle) const;
		// Replace edge at edgeIterator to genArc definition
		CustomPolyline2D	ReplaceEdge (const ConstEdgeIterator& edgeIterator, const GenArc& genArc, const ArcDivParams& arcDivParams) const;
		// Deletes the edge at edgeIterator, connects the neighboring edges (the intersection creates a new Polyline vertex)
		bool				DeleteEdge (const ConstEdgeIterator& edgeIterator, CustomPolyline2D& result) const;
		// lengthens the first (last) edge while shortens the last (first) edge, so the total length of the polyline is preserved
		CustomPolyline2D	ShiftPolyline (double length, bool firstEdge) const;

		// Cut the Polyline at given vertices
		MultiPolyline2DType		CutAtVertices (const GS::Array<ConstVertexIterator>& vertexIteratorArray) const;
		// Gives back the parts of the Polyline that are on the given half plane, determines whether it is cut or not
		MultiPolyline2DType		Cut (const HalfPlane2DData& cutline, bool* fullin = nullptr, GS::Int32* wrcode = nullptr) const;
		// Gives back the parts of the Polyline that are on the given half planes
		MultiPolyline2DType		Strip (const HalfPlane2DData& cutline1, const HalfPlane2DData& cutline2, GS::Int32* wrcode = nullptr) const;
		// Gives back the parts of the Polyline that are in the clip box
		MultiPolyline2DType		Clip (const Box2DData& box, GS::Int32* wrcode = nullptr) const;
		// Cuts out one part of the Polyline between param t1..t2 and gives it back
		CustomPolyline2D		CutPiece (const CutParam& t1, const CutParam& t2) const;
		// cutPoint to CutParam, throws exception if point not on polyline
		GS::Array<CutParam>		CutPointToCutParam (const Point2D& cutPoint) const;
		// CutParam  to cutPoint, throws exception if invalid cutParam
		Point2D					CutParamToCutPoint (const CutParam& cutParam) const;
		// calculates the distance of the cutPoint from the start
		double					CutParamToDistance (const CutParam& cutParam) const;
		// calculates the cutPoint from the start
		CutParam				DistanceToCutParam (double distance)	const;

		// Returns whether the Coord parameter is on the left or on the right side of the Polyline
		PolylinePointPosition	PointPosition (const Point2D& sidePoint) const;

		// Removes same directional edges from polygon if EdgeUserData is equal or comparable with a comparator
		template<class EdgeUserDataComparator>
		static void RemoveSameDirEdgesOnlyWithSameUserData (CustomPolyline2D& poly, const EdgeUserDataComparator& comparator);
		static void RemoveSameDirEdgesOnlyWithSameUserData (CustomPolyline2D& poly);

		// Debug
		void				Print			(GS::OChannel& oc)	const;
		void				PrintDebug		()				const;
		void				PrintDebugXML	()				const;
		bool				Check			(PolyCheckFlags checkFlags,
											 double			coordUpperRange) const;
		PolyRepairResult	CheckAndRepair	(PolyCheckFlags checkFlags,
											 double			coordUpperRange);
	};

	typedef CustomPolyline2D<PolyId, PolyId, PolyId> Polyline2D;

	class GEOMETRY_DLL_EXPORT MultiPolyline2DPrivate {
	public:
		static GS::ClassInfo	classInfo;
	};

	template <class VertexUserData, class EdgeUserData, class PolygonUserData>
	class CustomMultiPolyline2D : public GS::Array<CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>>
	{
		template <class VertexUserData1, class EdgeUserData1, class PolygonUserData1>
		friend class CustomPolyline2D;
	public:
		typedef CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData> PolyType;
		using CorePolyline2DType = CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>;

		CustomMultiPolyline2D () = default;
		CustomMultiPolyline2D (const CustomMultiPolyline2D&) = default;
		CustomMultiPolyline2D (CustomMultiPolyline2D&&) = default;

		virtual ~CustomMultiPolyline2D ();

		CustomMultiPolyline2D& operator= (const CustomMultiPolyline2D& other) = default;
		CustomMultiPolyline2D& operator= (CustomMultiPolyline2D&& other) = default;
		
		void SegmentUp (const ArcDivParams& arcDivParams);
		void Transform (const ArcDivParams& arcDivParams, const TRANMAT& tran);

		GSErrCode	Read (GS::IChannel& ic);
		GSErrCode	Write (GS::OChannel& oc) const;
		
		GSErrCode	ReadXML	(GS::XMLIChannel& ic);
		GSErrCode	WriteXML (GS::XMLOChannel& oc) const;

		// Returns the largest area Polyline and deletes it from the MultiPolyline
		CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData> PopLargest ();
		// Returns overall bounding box
		Box2DData GetBoundBox () const;
		
	protected:
		void GetCorePolyline2DArray (GS::Array<GS::SharedPtr<CorePolyline2DType>>& polylineArray) const;
		void PushResults (	typename CorePolyline2DType::PolylineResult polyResult,
							const GS::SharedPtr<CorePolyline2DType>& thisPoly,
							const GS::SharedPtr<CorePolyline2DType>& newPolyline);
	};

	typedef CustomMultiPolyline2D<PolyId, PolyId, PolyId> MultiPolyline2D;

} //Geometry namespace

#endif //GEOMETRY_POLYLINE2D_CLASSDEFINITION_HPP
