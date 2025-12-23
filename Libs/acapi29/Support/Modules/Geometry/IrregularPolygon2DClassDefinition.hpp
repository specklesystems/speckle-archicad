// *****************************************************************************
//
// Declaration of IrregularPolygon2D class
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	RA
//
// *****************************************************************************

#ifndef GEOMETRY_IRREGULARPOLYGON2D_CLASSDEFINITION_HPP_
#define GEOMETRY_IRREGULARPOLYGON2D_CLASSDEFINITION_HPP_

#if defined (_MSC_VER)
#pragma once
#endif

// --- Includes ----------------------------------------------------------------
// from GSRoot
#include "Definitions.hpp"
#include "Array.hpp"

// from Geometry
#include "Poly2DTypes.hpp"

#include "Polygon2DClassDefinition.hpp"
#include "Poly2DIterator.hpp"
#include "CorePolygon2D.hpp"

#include "CutElems.h"

namespace Geometry {

	class GEOMETRY_DLL_EXPORT IrregularPolygon2DPrivate {
	public:
		static GS::ClassInfo	classInfo;
	};

	template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
	class CustomIrregularPolygon2D
	{
		template <class VertexUserData1, class EdgeUserData1, class PolygonUserData1>
		friend class CustomPolyline2D;
		template <class VertexUserData1, class EdgeUserData1, class PolygonUserData1>
		friend class CustomMultiPolyline2D;
		template <class VertexUserData1, class EdgeUserData1, class ContourUserData1, class PolygonUserData1>
		friend class CustomIrregularPolygon2D;
		template <class VertexUserData1, class EdgeUserData1, class ContourUserData1, class PolygonUserData1>
		friend class CustomPolygon2D;
		template <class VertexUserData1, class EdgeUserData1, class ContourUserData1, class PolygonUserData1>
		friend class CustomMultiPolygon2D;
		template <class VertexUserData1, class EdgeUserData1, class ContourUserData1, class PolygonUserData1>
		friend class CustomMultiIrregularPolygon2D;

		friend class ConstPolyVertexInPolyState<CustomIrregularPolygon2D, VertexUserData>;
		friend class ConstPolyEdgeInPolyState<CustomIrregularPolygon2D, EdgeUserData>;
		friend class ConstPolyVertexInPoly<CustomIrregularPolygon2D, VertexUserData>;
		friend class ConstPolyEdgeInPoly<CustomIrregularPolygon2D, EdgeUserData>;
	public:
		typedef VertexUserData		VertexUserDataType;
		typedef EdgeUserData		EdgeUserDataType;
		typedef ContourUserData		ContourUserDataType;
		typedef PolygonUserData		PolygonUserDataType;

		typedef CorePolygon2DVertexVisitor		VertexVisitor;
		typedef CorePolygon2DConstVertexVisitor	ConstVertexVisitor;

		typedef CustomPolyVertex<VertexUserData>	Vertex;
		typedef CustomPolyEdge<EdgeUserData>		Edge;

		typedef GS::ConstBidirectionalItemIteratorBase <CustomIrregularPolygon2D, ConstPolyVertexInPolyState<CustomIrregularPolygon2D, VertexUserData>, ConstPolyVertexInPoly<CustomIrregularPolygon2D, VertexUserData> > ConstVertexIterator;
		typedef GS::ConstBidirectionalItemIteratorBase <CustomIrregularPolygon2D, ConstPolyEdgeInPolyState<CustomIrregularPolygon2D, EdgeUserData>, ConstPolyEdgeInPoly<CustomIrregularPolygon2D, EdgeUserData> > ConstEdgeIterator;

		using CorePolygon2DType				= CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>;
		using Polyline2DType				= CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>;
		using Polygon2DType					= CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>;
		using MultiPolygon2DType			= CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>;
		using MultiPolyline2DType			= CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>;
		using MultiIrregularPolygon2DType	= CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>;
		using IrregularPolygon2DCreatorType	= CustomIrregularPolygon2DCreator<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>;
		using Polyline2DCreatorType			= CustomPolyline2DCreator<VertexUserData, EdgeUserData, PolygonUserData>;

		class Contour
		{
			friend class CustomIrregularPolygon2D;
		private:
			enum FilterType
			{
				Filter_None			= 0x00,
				Filter_Range		= 0x01,
				Filter_PolyId		= 0x02
			};
		private:
			const CustomIrregularPolygon2D*		poly;
			UIndex							index;

			FilterType						filterType;
			UIndex							from;
			UIndex							to;
			ContourUserData					polyId;

			ConstVertexIterator				GetVertexIterator (UIndex vertexIdx) const;
			ConstEdgeIterator				GetEdgeIterator (UIndex edgeIdx) const;

		public:
			Contour () : poly (nullptr), index (0), filterType (Filter_None), from (0), to (0)
			{
			}
			Contour (const CustomIrregularPolygon2D* poly2D, UIndex idx) : poly (poly2D), index (idx), filterType (Filter_None), from (0), to (0)
			{
			}
			Contour (const CustomIrregularPolygon2D* poly2D, UIndex fromIdx, UIndex toIdx, UIndex idx) : poly (poly2D), index (idx), filterType (Filter_Range), from (fromIdx), to (toIdx)
			{
			}
			Contour (const CustomIrregularPolygon2D* poly2D, const ContourUserData& id) : poly (poly2D), index (0), filterType (Filter_PolyId), from (0), to (0), polyId (id)
			{
				index = poly->GetNextContourIndex (0, polyId);
			}

			Contour&  GetCurrent () { return *this; }
			const Contour&  GetCurrent () const { return *this; }
			void Next ()
			{
				if (filterType & Filter_PolyId) {
					index = poly->GetNextContourIndex (index, polyId);
					return;
				}
				index++;
			}
			void Prev ()
			{
				if (filterType & Filter_PolyId) {
					index = poly->GetPrevContourIndex (index, polyId);
					return;
				}
				index--;
			}
			UIndex GetIndex () const { return index; }
			bool IsEqual (const Contour& contour) const { return (poly == contour.poly && index == contour.index); }
			bool IsBegin () const
			{
				if (filterType & Filter_Range) {
					return (index < from);
				}
				return (index <= 0);
			}
			bool IsEnd () const
			{
				if (filterType & Filter_Range) {
					return (index >= to);
				}
				return (index > poly->GetContourNum ());
			}
			bool IsValid () const { return poly != nullptr; }
			bool CheckType (const Contour& contour) const { return poly == contour.poly; }
			const CustomIrregularPolygon2D* GetTarget () const { return poly; }

		public:
			const ContourUserData& GetPolyContourUserData () const;

			USize					GetVertexNum () const;
			ConstVertexIterator		EnumerateVertex () const;
			ConstVertexIterator		BeginVertex () const;
			ConstVertexIterator		EndVertex	() const;

			USize					GetEdgeNum () const;
			ConstEdgeIterator		EnumerateEdge () const;
			ConstEdgeIterator		BeginEdge () const;
			ConstEdgeIterator		EndEdge	() const;

			ConstVertexIterator		GetBeginVertex (const ConstEdgeIterator& edgeIterator) const;
			ConstVertexIterator		GetEndVertex (const ConstEdgeIterator& edgeIterator) const;

			ConstEdgeIterator		GetNextEdge (const ConstVertexIterator& vertexIterator) const;
			ConstEdgeIterator		GetPrevEdge (const ConstVertexIterator& vertexIterator) const;
		};

		typedef GS::ConstBidirectionalItemIteratorBase <CustomIrregularPolygon2D, Contour, Contour> ConstContourIterator;

		typedef CustomPolySegment<VertexUserData, EdgeUserData> Segment;
		typedef CustomPolyContourDescription<VertexUserData, EdgeUserData, ContourUserData> ContourDescription;
		typedef GS::Array<ContourDescription> ContourDescriptionArray;

	protected:
		GS::SharedPtr<CorePolygon2DType>	polygon;

	protected:
		CustomIrregularPolygon2D (const GS::SharedPtr<CorePolygon2DType>& polygon2D);

		static CustomIrregularPolygon2D		Create (const GS::SharedPtr<CorePolygon2DType>& polygon);
		static MultiIrregularPolygon2DType	Create (const GS::Array<GS::SharedPtr<CorePolygon2DType>>& polygonArray);
		CustomIrregularPolygon2D			CreateResult (typename CorePolygon2DType::PolygonResult polyResult, const GS::SharedPtr<CorePolygon2DType>& newPolygon) const;
		MultiIrregularPolygon2DType			CreateResult (typename CorePolygon2DType::PolygonResult polyResult, 
														  const CustomIrregularPolygon2D* firstParam, 
														  const GS::Array<GS::SharedPtr<CorePolygon2DType>>& polygonArray) const;

		void	SetResult	(typename CorePolygon2DType::PolygonResult polyResult, const GS::SharedPtr<CorePolygon2DType>& newPoly);
		void	CopyOnWrite	();

	protected:
		const Point2D& GetVertexCoordByIdx (UIndex vertexIdx) const
		{
			return polygon->GetCoord (vertexIdx);
		}
		const VertexUserData& GetVertexUserDataByIdx (UIndex vertexIdx) const
		{
			return *polygon->GetVertexUserData (vertexIdx);
		}
		UIndex GetNextVertexIndex (UIndex vertexIdx, const VertexUserData& id) const
		{
			return polygon->GetNextVertexIndex (vertexIdx, &id);
		}
		UIndex GetPrevVertexIndex (UIndex vertexIdx, const VertexUserData& id) const
		{
			return polygon->GetPrevVertexIndex (vertexIdx, &id);
		}

		double GetEdgeLengthByIdx (UIndex edgeIdx) const
		{
			return polygon->GetEdgeLength (edgeIdx);
		}
		double GetEdgeArcAngleByIdx (UIndex edgeIdx) const
		{
			return polygon->GetArcAngle (edgeIdx);
		}
		bool GetSectorById (UIndex edgeIdx, Sector& sect, GenArc& genArc) const
		{
			return polygon->GetSector (edgeIdx, sect, genArc);
		}
		GS::Optional<Sector> GetSectorById (UIndex edgeIdx) const
		{
			return polygon->GetSector (edgeIdx);
		}
		GS::Optional<GenArc> GetArcById (UIndex edgeIdx) const
		{
			return polygon->GetArc (edgeIdx);
		}
		const EdgeUserData& GetEdgeUserDataByIdx (UIndex edgeIdx) const
		{
			return *polygon->GetEdgeUserData (edgeIdx);
		}
		UIndex GetNextEdgeIndex (UIndex edgeIdx, const EdgeUserData& id) const
		{
			return polygon->GetNextEdgeIndex (edgeIdx, &id);
		}
		UIndex GetPrevEdgeIndex (UIndex edgeIdx, const EdgeUserData& id) const
		{
			return polygon->GetPrevEdgeIndex (edgeIdx, &id);
		}
		UIndex GetNextContourIndex (UIndex contourIdx, const ContourUserData& id) const
		{
			return polygon->GetNextContourIndex (contourIdx, &id);
		}
		UIndex GetPrevContourIndex (UIndex contourIdx, const ContourUserData& id) const
		{
			return polygon->GetPrevContourIndex (contourIdx, &id);
		}
		const ContourUserData& GetContourUserDataByIdx (UIndex contourIdx) const
		{
			return *polygon->GetContourUserData (contourIdx);
		}

		static typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Flags GetFlags (GS::UInt32 flags /*PolyFlags*/);
		static void CheckPolyFlags (GS::UInt32 flags /*PolyFlags*/);

	public:
		// Constructs an empty Polygon, where all sizes (number of vertices, arcs and contours) are 0 and corresponding data is uninitialized, PolyFlags all set to true values
		// For info on PolyFlags please, check Poly2D.hpp
		CustomIrregularPolygon2D ();
		CustomIrregularPolygon2D (const CustomIrregularPolygon2D& source);
		CustomIrregularPolygon2D (CustomIrregularPolygon2D&& source) = default;

		CustomIrregularPolygon2D (const Polygon2DType& poly);
		// Constructs a rectangle Polygon with the box parameter as bounds, PolyFlags all set to true values
		CustomIrregularPolygon2D (const Box2DData& box);
		CustomIrregularPolygon2D (const Circle2D& circ);
		CustomIrregularPolygon2D (const Ellipse& ell, ArcDivParams arcDivParams);

		// Constructs an empty Polygon, where all sizes (number of vertices, arcs and contours) are 0 and corresponding data is uninitialized, PolyFlags provided by caller
		// For info on PolyFlags please, check Poly2D.hpp
		explicit CustomIrregularPolygon2D (GS::UInt32 flags /*PolyFlags*/);
		// Constructs a rectangle Polygon with the box parameter as bounds, PolyFlags provided by caller
		CustomIrregularPolygon2D (GS::UInt32 flags /*PolyFlags*/, const Box2DData& box);

		~CustomIrregularPolygon2D ();

		GS::ClassVersion	GetClassVersion () const {return IrregularPolygon2DPrivate::classInfo.GetVersion ();}

		// Creates an irregular Polygon from a contour description array by using the first contour in the array as the main contour and the rest as holes
		// If the result of creation is empty then we get an empty irregular Polygon
		static CustomIrregularPolygon2D		Create (const ContourDescriptionArray& contourDescrArray);
		// Creates an irregular Polygon using the vertices and edges of the input Polyline sequentially
		static CustomIrregularPolygon2D		Create (const Polyline2DType& polyline);
		// The next six methods create an irregular Polygon from a list of coordinates, PolyArcs and contour end indices using several flags to determine the input format
		// See Poly2D.hpp for detailed info on PolyCreateFlags
		static CustomIrregularPolygon2D		Create (const GS::Array<Point2D>& coordList, const GS::Array<PolyArcRec>& arcList, const GS::Array<UIndex>& contourEndList, GS::UInt32 createFlags /*PolyCreateFlags*/);
		static CustomIrregularPolygon2D		Create (const GS::Array<Point2D>& coordList, GS::UInt32 createFlags /*PolyCreateFlags*/);
		static CustomIrregularPolygon2D		Create (const GS::Array<Point2D>& coordList, const GS::Array<PolyArcRec>& arcList, GS::UInt32 createFlags /*PolyCreateFlags*/);
		// nValuableCoords indicates the number of coords not counting the possible initial dummy blank coord
		// nValuableArcs indicates the number of arcs not counting the possible initial dummy blank arc
		// nContours indicates the number of contours in the resulting Polygon
		static CustomIrregularPolygon2D		Create (const Point2D* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nValuableArcs, const UIndex* contourEnds, USize nContours, GS::UInt32 createFlags /*PolyCreateFlags*/);
		static CustomIrregularPolygon2D		Create (const Point2D* coords, USize nValuableCoords, GS::UInt32 createFlags /*PolyCreateFlags*/);
		static CustomIrregularPolygon2D		Create (const Point2D* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nValuableArcs, GS::UInt32 createFlags /*PolyCreateFlags*/);

		// Creates an irregular Polygon from a contour description array by using the first contour in the array as the main contour and the rest as holes
		// If the result of creation is empty we get an empty irregular Polygon
		static CustomIrregularPolygon2D		Create (GS::UInt32 flags /*PolyFlags*/, const ContourDescriptionArray& contourDescrArray);
		// The next six methods create an irregular Polygon from a list of coordinates, PolyArcs and contour end indices using several flags to determine the input format, PolyFlags provided by caller
		// See Poly2D.hpp for detailed info on PolyFlags and PolyCreateFlags
		static CustomIrregularPolygon2D		Create (GS::UInt32 flags /*PolyFlags*/, const GS::Array<Point2D>& coordList, const GS::Array<PolyArcRec>& arcList, const GS::Array<UIndex>& contourEndList, GS::UInt32 createFlags /*PolyCreateFlags*/);
		static CustomIrregularPolygon2D		Create (GS::UInt32 flags /*PolyFlags*/, const GS::Array<Point2D>& coordList, GS::UInt32 createFlags /*PolyCreateFlags*/);
		static CustomIrregularPolygon2D		Create (GS::UInt32 flags /*PolyFlags*/, const GS::Array<Point2D>& coordList, const GS::Array<PolyArcRec>& arcList, GS::UInt32 createFlags /*PolyCreateFlags*/);
		// nValuableCoords indicates the number of coords not counting the possible initial dummy blank coord
		// nValuableArcs indicates the number of arcs not counting the possible initial dummy blank arc
		// nContours indicates the number of contours in the resulting Polygon
		static CustomIrregularPolygon2D		Create (GS::UInt32 flags /*PolyFlags*/, const Point2D* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nValuableArcs, const UIndex* contourEnds, USize nContours, GS::UInt32 createFlags /*PolyCreateFlags*/);
		static CustomIrregularPolygon2D		Create (GS::UInt32 flags /*PolyFlags*/, const Point2D* coords, USize nValuableCoords, GS::UInt32 createFlags /*PolyCreateFlags*/);
		static CustomIrregularPolygon2D		Create (GS::UInt32 flags /*PolyFlags*/, const Point2D* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nValuableArcs, GS::UInt32 createFlags /*PolyCreateFlags*/);

		// Converts the Polygon to an array of contour descriptions moving contour by contour starting with the main contour
		ContourDescriptionArray				ConvertToContourDescriptionArray () const;
		// Converts the Polygon to an array of Polylines moving contour by contour starting with the main contour
		MultiPolyline2DType					ConvertToPolylines () const;
		Polyline2DType						ConvertToPolyline (ConstContourIterator contourIterator) const;

		template <class VertexUserDataSrc, class EdgeUserDataSrc, class ContourUserDataSrc, class PolygonUserDataSrc>
		static CustomIrregularPolygon2D		ConvertFromIrregularPolygon2D (
			const CustomIrregularPolygon2D<VertexUserDataSrc, EdgeUserDataSrc, ContourUserDataSrc, PolygonUserDataSrc>& source, 
			Poly2DUserDataConverter<VertexUserDataSrc, EdgeUserDataSrc, ContourUserDataSrc, PolygonUserDataSrc,
									VertexUserDataType, EdgeUserDataType, ContourUserDataType, PolygonUserDataType>* converter = nullptr);

		// Copies the Polygon's vertices into a coord list, its curved edges into a PolyArcRec list and its vertex indices that are on contour ends into an index list
		// where the caller must specify several flags to indicate the output format - See Poly2D.hpp for detailed info on PolyCreateFlags
		// The reversedContours iterator list specifies which contours in the polygon should be copied as a reversed order contour (starting from the same vertex)
		// nValuableCoords indicates the expected number of resulting coords not counting the possible initial dummy blank coord
		// nValuableArcs indicates the expected number of resulting arcs not counting the possible initial dummy blank arc
		// nContours indicates the expected number of resulting contour ends not counting the possible initial dummy 0 index, this should match the number of contours in the Polygon
		// If the caller specifies either coords, arcs or contourEnds as nullptr, the corresponding size will still be returned but no copying will be done
		// If the caller specifies either nValuableCoords, nValuableArcs or nContours as a smaller number than the actual corresponding size but does actually expect a result
		// (pointer not nullptr) then an OutOfMemoryException is thrown
		void CopyPolygonData (Point2D* coords, USize& nValuableCoords, PolyArcRec* arcs, USize& nValuableArcs, UIndex* contourEnds, USize& nContours, const GS::Array<ConstContourIterator>& reversedContours, GS::UInt32 createFlags /*PolyCreateFlags*/) const;
		// Similar to previous but uses GS::Arrays instead of pointers
		// Copies the Polygon's vertices into a coord list, its curved edges into a PolyArcRec list and its vertex indices that are on contour ends into an index list
		// where the caller must specify several flags to indicate the output format - See Poly2D.hpp for detailed info on PolyCreateFlags
		// The reversedContours iterator list specifies which contours in the polygon should be copied as a reversed order contour
		void CopyPolygonData (GS::Array<Point2D>& coords, GS::Array<PolyArcRec>& arcs, GS::Array<UIndex>& contourEnds, const GS::Array<ConstContourIterator>& reversedContours, GS::UInt32 createFlags /*PolyCreateFlags*/) const;

		// Copies the Polygon's vertices into a coord list, its curved edges into a PolyArcRec list and its vertex indices that are on contour ends into an index list
		// where the caller must specify several flags to indicate the output format - See Poly2D.hpp for detailed info on PolyCreateFlags
		// The memory for the lists is allocated within the method
		// nValuableCoords indicates the expected number of resulting coords not counting the possible initial dummy blank coord
		// nValuableArcs indicates the expected number of resulting arcs not counting the possible initial dummy blank arc
		// nContours indicates the expected number of resulting contour ends not counting the possible initial dummy 0 index, this should match the number of contours in the Polygon
		// If the caller specifies either nValuableCoords, nValuableArcs or nContours as a smaller number than the actual corresponding size but does actually expect a result
		// (pointer not nullptr) then an OutOfMemoryException is thrown
		void AllocateAndCopyPolygonData (Point2D** coords, USize& nValuableCoords, PolyArcRec** arcs, USize& nValuableArcs, UIndex** contourEnds, USize& nContours, GS::UInt32 createFlags /*PolyCreateFlags*/) const;

		CustomIrregularPolygon2D&	operator= (const CustomIrregularPolygon2D& source);
		CustomIrregularPolygon2D&	operator= (CustomIrregularPolygon2D&& source) = default;

		bool	operator== (const CustomIrregularPolygon2D& rightOp) const;
		bool	operator!= (const CustomIrregularPolygon2D& rightOp) const;

		bool	GetSameDirEdgeLegal () const;
		bool	GetForce64BitPrecision () const;

		// Disables the possibility of two succeeding edges with the same direction (two edges in one line)
		// calling with false parameter ensures that there are none of these edges by removing edges and vertices if needed
		// For info on PolyFlags please, check Poly2D.hpp
		void		SetPolyFlags (GS::UInt32 flags /*PolyFlags*/);
		GS::UInt32	GetPolyFlags () const;

		ConstVertexIterator			GetVertexIterator (UIndex vertexIdx) const;
		ConstVertexIterator			GetVertexIterator (const Point2D& coord) const;
		ConstVertexIterator			EnumerateVertex () const;
		// Same as previous
		ConstVertexIterator			BeginVertex () const;
		ConstVertexIterator			EndVertex () const;
		ConstVertexIterator			EnumerateVertex (const VertexUserData& id) const;

		ConstEdgeIterator			GetEdgeIterator (UIndex edgeIdx) const;
		ConstEdgeIterator			EnumerateEdge () const;
		// Same as previous
		ConstEdgeIterator			BeginEdge () const;
		ConstEdgeIterator			EndEdge () const;
		ConstEdgeIterator			EnumerateEdge (const EdgeUserData& id) const;

		ConstContourIterator		GetContourIterator (UIndex contourIdx) const;
		ConstContourIterator		EnumerateContour () const;
		// Same as previous
		ConstContourIterator		BeginContour () const;
		ConstContourIterator		EndContour () const;
		ConstContourIterator		EnumerateContour (const ContourUserData& id) const;
		// Get first hole iterator
		ConstContourIterator		EnumerateHoleContour () const;

		const PolygonUserData&		GetPolyUserData () const;
		void						SetPolyUserData (const PolygonUserData& polyId);

		const VertexUserData&		GetVertexDefaultUserData () const;
		void						SetVertexDefaultUserData (const VertexUserData& userData);

		void						ResetUserData ();

		USize						GetVertexNum () const;
		Vertex						GetVertex (const ConstVertexIterator& vertexIterator) const;
		const Point2D&				GetCoord (const ConstVertexIterator& vertexIterator) const;

		const VertexUserData&		GetVertexUserData (const ConstVertexIterator& vertexIterator) const;
		void						SetVertexUserData (const ConstVertexIterator& vertexIterator, const VertexUserData& vertexId);

		const EdgeUserData&			GetEdgeDefaultUserData () const;
		void						SetEdgeDefaultUserData (const EdgeUserData& userData);

		USize						GetEdgeNum () const;
		Edge						GetEdge		(const ConstEdgeIterator& edgeIterator) const;
		// DEPRECATED! Returns true if the edge at edgeIterator is curved
		bool						GetSector	(const ConstEdgeIterator& edgeIterator, Sector& sect, GenArc& genArc) const;
		// DEPRECATED! Returns true if the edge at edgeIterator is curved
		bool						GetSector	(const ConstEdgeIterator& edgeIterator, Point2D& begC, Point2D& endC, double& angle) const;

		GS::Optional<Sector>		GetSector	(const ConstEdgeIterator& edgeIterator) const;
		GS::Optional<GenArc>		GetArc		(const ConstEdgeIterator& edgeIterator) const;

		const EdgeUserData&			GetEdgeUserData (const ConstEdgeIterator& edgeIterator) const;
		void						SetEdgeUserData (const ConstEdgeIterator& edgeIterator, const EdgeUserData& edgeId);

		const ContourUserData&		GetContourDefaultUserData () const;
		void						SetContourDefaultUserData (const ContourUserData& userData);

		USize						GetContourNum () const;
		CustomIrregularPolygon2D	GetContour (const ConstContourIterator& contourIterator) const;

		const ContourUserData&		GetContourUserData (const ConstContourIterator& contourIterator) const;
		void						SetContourUserData (const ConstContourIterator& contourIterator, const ContourUserData& contourId);

		ConstVertexIterator			GetBeginVertex (const ConstEdgeIterator& edgeIterator) const;
		ConstVertexIterator			GetEndVertex (const ConstEdgeIterator& edgeIterator) const;

		ConstEdgeIterator			GetNextEdge (const ConstVertexIterator& vertexIterator) const;
		ConstEdgeIterator			GetPrevEdge (const ConstVertexIterator& vertexIterator) const;

	protected:
		bool	IsVertexInContour	(UIndex contourIdx, UIndex vertexIdx) const;
		bool	IsEdgeInContour		(UIndex contourIdx, UIndex edgeIdx) const;

	public:
		bool	IsEmpty () const;
		bool	HasArcs () const;
		void	Clear	();

		// Returns true, if the polygon is a rectangle and its edges are parallel with the X and Y axises
		bool	IsABox () const;
		GS::Optional<Circle2D> GetMatchingCircle () const;

		// Regularizes the Polygon which may result in the irregular Polygon falling to regularized pieces
		MultiPolygon2DType	Regularize (PolyRegularizationMode mode = PolyRegularizationMode_Default) const;

		// Regularizes the Polygon which may result in the irregular Polygon falling to regularized pieces
		// It can also return whether the original Polygon was actually irregular and specific simple vertex,
		// edge and contour changes are also detected according to request using the regularizationResultsMask
		// See PolyRegularizationFlags in Poly2D.hpp for details
		// Be aware that if you do not need any of this additional information, you should use the previous
		// Regularize () method since gathering the regularization information makes this method much slower
		// for large polygons than the other!
		MultiPolygon2DType	Regularize (UIndex regularizationResultsMask,
										UIndex& regularizationResults,
										GS::Array<GS::Array<typename Polygon2DType::ConstContourIterator>>*	reversedContours = nullptr);

		GSErrCode	Read		(GS::IChannel& ic);
		GSErrCode	Write		(GS::OChannel& oc) const;
		GSErrCode	ReadXML		(GS::XMLIChannel& ic);
		GSErrCode	WriteXML	(GS::XMLOChannel& oc) const;
		

		GSErrCode	Store (GS::ObjectState& os) const
		{
			os.Add ("polygon", *polygon);
			return NoError;
		}

		GSErrCode	Restore (const GS::ObjectState& os)
		{
			typename Geometry::CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Flags flags;
			polygon = new Geometry::CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (flags);
			os.Get ("polygon", *polygon);
			return NoError;
		}

		//******************************* Calculate *******************************
		// Returns the bounding box of the Polygon (needs to check all contours)
		const Box2DData&	GetBoundBox		() const;
		// Returns the center of the bounding box of the Polygon
		Point2D				GetCenter		() const;
		// Returns the signed area of the Polygon
		double				CalcSignedArea	() const;
		// Returns true if the Polygon's orientation is positive (CCW)
		// In case of self intersection (where orientation loses its meaning anyway) part of the calculated area will be negative, the rest will be positive,
		// so the areas with greater absolute value "win"
		bool				HasPositiveOrientation	(const ConstContourIterator& contourIterator) const;
		// Returns the perimeter of the Polygon
		double				CalcPerimeter			() const;
		// Returns the perimeter of the contour at contourIterator
		double				CalcContourPerimeter	(const ConstContourIterator& contourIterator) const;
		// Returns the maximum fillet radius that can belong to the vertex at vertexIterator
		double				CalcMaxVertexFillet		(const ConstVertexIterator& vertexIterator) const;
		// Returns whether the given coordinate is on the polygon's contour
		bool				IsCoordOnEdge			(const Point2D& c, ConstEdgeIterator* edgeIt) const;
		// Returns the distance of the polygon's contour from given coordinate
		double				DistanceFromPoint		(const Point2D& c) const;

		// Returns the relative position of the Polygon and the point parameter
		// Find RelativePosition definitions in GeometricDefinitions.h
		RelativePosition	GetPosition (const Point2D& point,					Boundary boundaries, DetailedRelativePosition* detailed = nullptr) const;
		RelativePosition	GetPosition (const Sector& sect,					Boundary boundaries, DetailedRelativePosition* detailed = nullptr) const;
		RelativePosition	GetPosition (const GenArc& arc,						Boundary boundaries, DetailedRelativePosition* detailed = nullptr) const;
		RelativePosition	GetPosition (const Box2DData& box,					Boundary boundaries, DetailedRelativePosition* detailed = nullptr) const;
		RelativePosition	GetPosition (const CustomIrregularPolygon2D& poly,	Boundary boundaries, DetailedRelativePosition* detailed = nullptr) const;
		RelativePosition	GetPosition (const Polyline2DType& poly,			Boundary boundaries, DetailedRelativePosition* detailed = nullptr) const;

		// Returns the disposition of the sector parameter relative to the Polygon, if the resSectors parameter is not nullptr,
		// it also returns the pieces of the sector that are inside the Polygon
		PGPositionExt			SegmentIn (Sector sector, GS::Array<Sector>* resSectors = nullptr) const;
		// Returns the disposition of the sector parameter relative to the Polygon, if the resSectors parameter is not nullptr,
		// it also returns the pieces of the sector that are outside the Polygon
		PGPositionExt			SegmentOut (Sector sector, GS::Array<Sector>* resSectors = nullptr) const;
		// Returns the parts of a line - given by one of its points and its direction - that are inside the Polygon
		bool					Intersect (const Point2D& c, const Vector2D& dir, GS::Array<Sector>* result) const;
		// Returns the bounding box of the Polygon we would get if we applied tr as a transformation matrix on this Polygon
		// if invTr is not nullptr then invTr will be applied to the box result
		GS::FixArray<Point2D, 4>	GetTransformedBoundBox (const TRANMAT& tr, const TRANMAT& invTr = Geometry::IdentityTranMat) const;

		void	Visit (ConstVertexVisitor &visitor) const;

		//******************************* Modify polygon *******************************
		void	RemoveHoles ();
		void	DeleteHole (const ConstContourIterator& contourIterator);
		void	Move (Vector2D offset);
		// The next three clear user data
		void	MakeGoodOrientation ();
		void	ClearVertexIds ();
		void	ClearEdgeIds ();
		void	ClearContourIds ();

		void	RotateVerticeIndicesInContour (const ConstContourIterator& contourToRotate, const ConstVertexIterator& vertexToFirst);
		void	SwapContourOrder (const GS::Array<ConstContourIterator>& newContourOrder);
		void	SortArcsByIndices ();

		void	Stretch    (const Point2D& fixPoint,
							const Point2D& draggedPoint,
							const Vector2D& offsetAxisX,
							const Vector2D& offsetAxisY = Vector2D (0.0, 0.0),
							const ArcDivParams& arcDivParams = ArcDivParams (0.0));

		// Transforms the Polygon with tran - the transformation should preserve arcs
		void	TransformPreserveArcs	(const TRANMAT& tran);
		// Same as previous but only transforms the parts of the Polygon that intersect with the filter Polygon or is on its edge. Returns true if all is transformed
		bool	TransformPreserveArcs	(const CustomIrregularPolygon2D& filterWithPolygon, const TRANMAT& tran);
		// Same as first transform but only transforms the parts of the Polygon that intersect with any of the filter Polygons or is on the edge of any. Returns true if all is transformed
		bool	TransformPreserveArcs	(const MultiIrregularPolygon2DType& filterWithPolygon, const TRANMAT& tran);
		// Transforms the holes at contourIterators with a list of transformations, all transformations are applied to the original selected holes
		// results of all transformations create new holes and the originals may also be kept - the transformations should preserve arcs
		void	TransformHolePreserveArcs (const GS::Array <ConstContourIterator>& contourIterators, const GS::Array<TRANMAT>& trans, bool keepOriginals);

		// Segments up the Polygon - i.e. replaces all curves with line sections - using arcDivParams as granulation for the segmentation
		void	SegmentUp (const ArcDivParams& arcDivParams);
		// Makes all curved edges straight - this is not segmentation, number of edges and vertices remain the same!
		void	EliminateArcs ();
		void	MoveVertex (const ConstVertexIterator& vertexIterator, const Point2D& newPosition);
		void	InsertVertex (const ConstEdgeIterator& edgeIterator, const Point2D& newPosition);
		// New edge gets created by splitting one vertex.
		// The new edge is going to be zero length and straight
		void	InsertEdge (const ConstVertexIterator& vertexIterator);

		void	InsertVertexOnPolygon (const Point2D& newPosition, const ConstEdgeIterator& edgeIterator, CustomIrregularPolygon2D& result, ConstVertexIterator* vertexIterator = nullptr);
		void	DeleteVertex (const ConstVertexIterator& vertexIterator);
		// Sets the angle of the curve of the edge at edgeIterator to edgeAngle
		void	SetEdgeAngle (const ConstEdgeIterator& edgeIterator, double edgeAngle);
		void	MoveVertices (const GS::Array<GS::Pair<ConstVertexIterator, Point2D>>& newVertexPositions);
		void	ReplaceEdge (const ConstEdgeIterator& edgeIterator, const GS::Array<GenArc>& arcs, const ArcDivParams& arcDivParams);
		void	ReplaceEdge (const ConstEdgeIterator& edgeIterator, const GS::Array<double>& angles, const GS::Array<Point2D>& internalVerts);

		// Adds the hole at contourIterator from poly
		void	AddHole (const CustomIrregularPolygon2D& poly, const ConstContourIterator& contourIterator);
		// Disables the possibility of two succeeding edges with the same direction (two edges in one line)
		// it also ensures that there are none of these edges by removing edges and vertices if needed
		void	RemoveSameDirEdge ();
		void	RemoveZeroEdgesAndArcs (double minEdgeLength, double minArcAngle);

		void	Visit (VertexVisitor& visitor);

		//******************************* Create new polygons *******************************
		// Offsets the edge at edgeIterator with the given offset preserving connecting edge angles
		CustomIrregularPolygon2D		OffsetEdge (const ConstEdgeIterator& edgeIterator, double offset) const;
		// Offsets the edges at edgeIterators with the given offsets preserving connecting edge angles
		CustomIrregularPolygon2D		OffsetMultipleEdges (const GS::Array<GS::Pair<ConstEdgeIterator, double> >& offsets) const;
		// Offsets the edge at edgeIterator with the given offset preserving area
		CustomIrregularPolygon2D		OffsetEdgeFixArea (const ConstEdgeIterator& edgeIterator, const ConstVertexIterator& vertexIterator, double offset, double area) const;
		// Offsets all edges in the contour at contourIterator with the given offset preserving edge angles
		CustomIrregularPolygon2D		OffsetContour (const ConstContourIterator& contourIterator, double offset) const;
		// Creates fillets with given radius at all vertices in the Polygon
		CustomIrregularPolygon2D		FilletAllVertex (const double filletRadius) const;
		// Creates a fillet with given radius at the vertex at vertexIterator
		CustomIrregularPolygon2D		FilletVertex (const ConstVertexIterator& vertexIterator, const double filletRadius) const;
		// Creates fillets with given radius at all vertices in the contour at contourIterator
		CustomIrregularPolygon2D		FilletVertexInContour (const ConstContourIterator& contourIterator, const double filletRadius) const;
		// Creates chamfers with given radius at all vertices in the Polygon
		CustomIrregularPolygon2D		ChamferAllVertex (const double chamferRadius) const;
		// Creates a chamfer with given radius at the vertex at vertexIterator
		CustomIrregularPolygon2D		ChamferVertex (const ConstVertexIterator& vertexIterator, const double chamferRadius) const;
		// Creates chamfers with given radius at all vertices in the contour at contourIterator
		CustomIrregularPolygon2D		ChamferVertexInContour (const ConstContourIterator& contourIterator, const double chamferRadius) const;

		bool							DeleteEdge	(const ConstEdgeIterator& edgeIterator, CustomIrregularPolygon2D& result) const;
		MultiIrregularPolygon2DType		Unify		(const CustomIrregularPolygon2D& poly) const;
		MultiIrregularPolygon2DType		Intersect	(const CustomIrregularPolygon2D& poly, Boundary boundaries = Boundary_Closed, RelativePosition* relativePosition = nullptr, DetailedRelativePosition* detailed = nullptr) const;
		MultiIrregularPolygon2DType		Substract	(const CustomIrregularPolygon2D& poly, Boundary boundaries = Boundary_Closed, RelativePosition* relativePosition = nullptr, DetailedRelativePosition* detailed = nullptr) const;

		// Returns the parts of the Polygon that are on the given half plane, determines whether it is cut or not
		MultiIrregularPolygon2DType		Cut (const HalfPlane2DData& cutline, bool* fullin = nullptr, GS::Int32* wrcode = nullptr, bool* degen = nullptr) const;
		// Returns the parts of the Polygon that are on the given half planes, determines whether it is cut or not
		MultiIrregularPolygon2DType		Cut (const GS::Array<HalfPlane2DData>& cutlines, bool* fullin = nullptr, GS::Int32* wrcode = nullptr, bool* degen = nullptr) const;
		// Returns the parts of the Polygon that are on the given half planes
		MultiIrregularPolygon2DType		Strip (const HalfPlane2DData& cutline1, const HalfPlane2DData& cutline2, GS::Int32* wrcode = nullptr) const;
		// Returns the parts of the Polygon that are in the clip box
		MultiIrregularPolygon2DType		Clip (const Box2DData& box, GS::Int32* wrcode = nullptr) const;

		// Stores the intersections in the creators
		// See creator interfaces in Poly2D.hpp
		void							CutElem (const Sector& sector,						Boundary cutBoundaries, SectorCreator& creator) const;
		void							CutElem (const GenArc& genArc,						Boundary cutBoundaries, GenArcCreator& creator) const;
		void							CutElem (const Point2D& coord,						Boundary cutBoundaries, PointCreator& creator) const;
		void							CutElem (const BezierDetails& bezier,				Boundary cutBoundaries, SplineCreator& creator) const;
		void							CutElem (const CustomIrregularPolygon2D& polygon,	Boundary cutBoundaries, IrregularPolygon2DCreatorType& creator) const;
		void							CutElem (const Polyline2DType& polyline,			Boundary cutBoundaries, Polyline2DCreatorType& creator) const;

		// Stores the intersections in the results
		GS::Array<Sector>				CutElem (const Sector& sector,						Boundary cutBoundaries) const;
		GS::Array<GenArc>				CutElem (const GenArc& genArc,						Boundary cutBoundaries) const;
		GS::Array<Point2D>				CutElem (const Point2D& coord,						Boundary cutBoundaries) const;
		GS::Array<BezierDetails>		CutElem (const BezierDetails& bezier,				Boundary cutBoundaries) const;
		MultiIrregularPolygon2DType		CutElem (const CustomIrregularPolygon2D& poly,		Boundary cutBoundaries) const;
		MultiPolyline2DType				CutElem (const Polyline2DType& poly,				Boundary cutBoundaries) const;

		//intersect only with the edges of the polygon
		GS::Array<Sector>				IntersectElemBorderOnly (const Sector& sector) const;
		GS::Array<GenArc>				IntersectElemBorderOnly (const GenArc& genArc) const;

		// Stores the substraction results in the creator
		// See creator interfaces in Poly2D.hpp
		void							ElemPolyDifference (const Sector& sector,						Boundary cutBoundaries, SectorCreator& creator) const;
		void							ElemPolyDifference (const GenArc& genArc,						Boundary cutBoundaries, GenArcCreator& creator) const;
		void							ElemPolyDifference (const Point2D& coord,						Boundary cutBoundaries, PointCreator& creator) const;
		void							ElemPolyDifference (const BezierDetails& bezier,				Boundary cutBoundaries, SplineCreator& creator) const;
		void							ElemPolyDifference (const CustomIrregularPolygon2D& polygon,	Boundary cutBoundaries, IrregularPolygon2DCreatorType& creator) const;
		void							ElemPolyDifference (const Polyline2DType& polyline,				Boundary cutBoundaries, Polyline2DCreatorType& creator) const;

		GS::Array<Sector>				ElemPolyDifference (const Sector& sector,						Boundary cutBoundaries) const;
		GS::Array<GenArc>				ElemPolyDifference (const GenArc& genArc,						Boundary cutBoundaries) const;
		GS::Array<Point2D>				ElemPolyDifference (const Point2D& coord,						Boundary cutBoundaries) const;
		GS::Array<BezierDetails>		ElemPolyDifference (const BezierDetails& bezier,				Boundary cutBoundaries) const;
		MultiIrregularPolygon2DType		ElemPolyDifference (const CustomIrregularPolygon2D& polygon,	Boundary cutBoundaries) const;
		MultiPolyline2DType				ElemPolyDifference (const Polyline2DType& polyline,				Boundary cutBoundaries) const;

		GS::Array<Sector>				ElemPolyDiffBorderOnly (const Sector& sector) const;
		GS::Array<GenArc>				ElemPolyDiffBorderOnly (const GenArc& genArc) const;

		// Determines whether the given ... overlaps with the Polygon
		bool							ElemXPolygon (const Sector& sector,								Boundary cutBoundaries) const;
		bool							ElemXPolygon (const GenArc& genArc,								Boundary cutBoundaries) const;
		bool							ElemXPolygon (const Point2D& coord,								Boundary cutBoundaries) const;
		bool							ElemXPolygon (const BezierDetails& bezier,						Boundary cutBoundaries) const;
		bool							ElemXPolygon (const CustomIrregularPolygon2D& polygon,			Boundary cutBoundaries, bool& touching) const;
		bool							ElemXPolygon (const Polyline2DType& polyline,					Boundary cutBoundaries) const;


		// Inserts vertices into the given Polygons' edges where the two intersect
		static bool		CreateCommonEdgeSections (CustomIrregularPolygon2D& poly1, CustomIrregularPolygon2D& poly2);
		// Inserts vertices into the given Polygons' edges where the x line intersect. Return true if polygon is changed
		bool			InsertCommonXLineOnPolygon (double x, const EdgeSplitControl& cntrl = EdgeSplitControl ());
		// Inserts vertices into the given Polygons' edges where the x line intersect. Return true if polygon is changed
		bool			InsertCommonYLineOnPolygon (double y, const EdgeSplitControl& cntrl = EdgeSplitControl ());

		// Debug
		void				Dump3DGDL		(Geometry::Plane* thePlane = nullptr, GS::OChannel& oc = dbChannel) const;
		void				Print			(GS::OChannel& oc)	const;
		void				PrintDebug		()					const;
		void				PrintDebugXML	()					const;
		bool				Check			(PolyCheckFlags	checkFlags, double coordUpperRange) const;
		PolyRepairResult	CheckAndRepair	(PolyCheckFlags	checkFlags, double coordUpperRange);
	};

	typedef CustomIrregularPolygon2D<PolyId, PolyId, PolyId, PolyId> IrregularPolygon2D;

	class GEOMETRY_DLL_EXPORT MultiIrregularPolygon2DPrivate {
	public:
		static GS::ClassInfo	classInfo;
	};

	template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
	class CustomMultiIrregularPolygon2D : public GS::ArrayFB<CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>, 4>
	{
		template <class VertexUserData1, class EdgeUserData1, class ContourUserData1, class PolygonUserData1>
		friend class CustomIrregularPolygon2D;
		template <class VertexUserData1, class EdgeUserData1, class PolygonUserData1>
		friend class CustomPolyline2D;
		friend struct Polygon2DCutOperations;
	public:
		using PolyType					= CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>;
		using CorePolygon2DType			= CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>;
		using Polyline2DType			= CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>;
		using CustomMultiPolygon2DType	= CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>;

		CustomMultiIrregularPolygon2D () = default;
		CustomMultiIrregularPolygon2D (const CustomMultiIrregularPolygon2D& source) = default;
		CustomMultiIrregularPolygon2D (CustomMultiIrregularPolygon2D&& source) = default;

		CustomMultiIrregularPolygon2D (std::initializer_list<PolyType> items);

		CustomMultiIrregularPolygon2D (const CustomMultiPolygon2DType& polys);

		CustomMultiIrregularPolygon2D& operator= (const CustomMultiIrregularPolygon2D& other);
		CustomMultiIrregularPolygon2D& operator= (CustomMultiIrregularPolygon2D&& other) = default;

		virtual ~CustomMultiIrregularPolygon2D ();

		void Unify (PolyHoleHandling holeHandling = ReturnHoles);
		void SegmentUp (const ArcDivParams& arcDivParams);
		void Transform (const ArcDivParams& arcDivParams, const TRANMAT& tran);

		GSErrCode	Read (GS::IChannel& ic);
		GSErrCode	Write (GS::OChannel& oc) const;
		
		GSErrCode	ReadXML	(GS::XMLIChannel& ic);
		GSErrCode	WriteXML (GS::XMLOChannel& oc) const;

		Box2DData	GetBoundBox () const;
		double		CalcSignedArea () const;

		RelativePosition	GetPosition (const Point2D& point,			Boundary boundaries, DetailedRelativePosition* detailed = nullptr) const;
		RelativePosition	GetPosition (const Sector& sect,			Boundary boundaries, DetailedRelativePosition* detailed = nullptr) const;
		RelativePosition	GetPosition (const GenArc& arc,				Boundary boundaries, DetailedRelativePosition* detailed = nullptr) const;
		RelativePosition	GetPosition (const Box2DData& box,			Boundary boundaries, DetailedRelativePosition* detailed = nullptr) const;
		RelativePosition	GetPosition (const PolyType& poly,			Boundary boundaries, DetailedRelativePosition* detailed = nullptr) const;
		RelativePosition	GetPosition (const Polyline2DType& poly,	Boundary boundaries, DetailedRelativePosition* detailed = nullptr) const;

		// Substracts all poly2 Polygons from all poly1 Polygons
		// returns false if the result is the same as poly1
		static CustomMultiIrregularPolygon2D Substract (const CustomMultiIrregularPolygon2D& poly1, const CustomMultiIrregularPolygon2D& poly2, bool* changed = nullptr);
		// Intersects all poly1 Polygons with all poly2 Polygons
		// if poly1 and poly2 are disjunct, the result will also be disjunct and will be the intersection of the disjunct areas
		static CustomMultiIrregularPolygon2D Intersect (const CustomMultiIrregularPolygon2D& poly1, const CustomMultiIrregularPolygon2D& poly2);

	protected:
		void GetCorePolygon2DArray (GS::Array<GS::SharedPtr<CorePolygon2DType>>& polygonArray) const;
		void PushCorePolygon2DArray (const GS::Array<GS::SharedPtr<CorePolygon2DType>>& polygonArray);

		void PushResults (typename CorePolygon2DType::PolygonResult polyResult,
						  const GS::SharedPtr<CorePolygon2DType>& thisPoly,
						  const GS::SharedPtr<CorePolygon2DType>& firstParam,
						  const GS::Array<GS::SharedPtr<CorePolygon2DType>>& polygonArray);
	};

	typedef CustomMultiIrregularPolygon2D<PolyId, PolyId, PolyId, PolyId> MultiIrregularPolygon2D;


	
}		// namespace Geometry

#endif		// GEOMETRY_IRREGULARPOLYGON2D_CLASSDEFINITION_HPP_