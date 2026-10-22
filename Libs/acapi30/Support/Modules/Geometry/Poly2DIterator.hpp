// *****************************************************************************
//
// Declaration of Poly2DIterator class
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	RA
//
// *****************************************************************************

#ifndef GEOMETRY_POLY2DITERATOR_HPP
#define GEOMETRY_POLY2DITERATOR_HPP

#pragma once

// --- Includes ----------------------------------------------------------------

#include "Poly2D.hpp"
//#include "RandomItemIterator.hpp"
#include "BidirectionalItemIteratorBase.hpp"

namespace Geometry {

	template <class Poly2DType, class CustomData>
	class ConstPolyVertexInPolyState
	{
	private:
		enum FilterType
		{
			Filter_None			= 0x00,
			Filter_Range		= 0x01,
			Filter_PolyId		= 0x02
		};
	private:
		const Poly2DType*		poly;

		FilterType				filterType;
		UIndex					from;
		UIndex					to;

		ConstPolyVertexInPoly<Poly2DType, CustomData> value;

	public:
		ConstPolyVertexInPolyState () : poly (nullptr), filterType (Filter_None), from (0), to (0)
		{
		}
		ConstPolyVertexInPolyState (const Poly2DType* poly2D, UIndex idx) : poly (poly2D), filterType (Filter_None), from (0), to (0), value (poly2D, idx)
		{
		}
		ConstPolyVertexInPolyState (const Poly2DType* poly2D, UIndex fromIdx, UIndex toIdx, UIndex idx) : poly (poly2D), filterType (Filter_Range), from (fromIdx), to (toIdx), value (poly2D, idx)
		{
		}
		ConstPolyVertexInPolyState (const Poly2DType* poly2D, const CustomData& id) : poly (poly2D), filterType (Filter_PolyId), from (0), to (0), value (poly2D, 0)
		{
			value.SetIndex (poly->GetNextVertexIndex (0, id));
		}

		ConstPolyVertexInPoly<Poly2DType, CustomData>&  GetCurrent () { return value; }
		const ConstPolyVertexInPoly<Poly2DType, CustomData>&  GetCurrent () const { return value; }
		void Next ()
		{
			if (filterType & Filter_PolyId) {
				value.SetIndex (poly->GetNextVertexIndex (value.GetIndex (), value.GetPolyVertexUserData ()));
				return;
			}
			value.SetIndex (value.GetIndex () + 1);
		}
		void Prev ()
		{
			if (filterType & Filter_PolyId) {
				value.SetIndex (poly->GetPrevVertexIndex (value.GetIndex (), value.GetPolyVertexUserData ()));
				return;
			}
			value.SetIndex (value.GetIndex () - 1);
		}
		UIndex GetIndex () const { 
			return (value.GetIndex ());
		}
		bool IsEqual (const ConstPolyVertexInPolyState<Poly2DType, CustomData>& state) const { return (poly == state.poly && value.GetIndex () == state.value.GetIndex ()); }
		bool IsBegin () const
		{
			if (filterType & Filter_Range) {
				return (value.GetIndex () < from);
			}
			return (value.GetIndex () <= 0);
		}
		bool IsEnd () const
		{
			if (filterType & Filter_Range) {
				return (value.GetIndex () >= to);
			}
			return (value.GetIndex () > poly->GetVertexNum ());
		}
		bool IsValid () const { return poly != nullptr; }			// TODO   setSize != 0, de ez nem jo a polyline-ra
		bool CheckType (const ConstPolyVertexInPolyState& state) const { return poly == state.poly; }
		const Poly2DType* GetTarget () const { return poly; }

	};

	template <class Poly2DType, class CustomData>
	class ConstPolyEdgeInPolyState
	{
	private:
		enum FilterType
		{
			Filter_None			= 0x00,
			Filter_Range		= 0x01,
			Filter_PolyId		= 0x02
		};
	private:
		const Poly2DType*		poly;

		FilterType				filterType;
		UIndex					from;
		UIndex					to;
		
		ConstPolyEdgeInPoly<Poly2DType, CustomData> value;

	public:
		ConstPolyEdgeInPolyState () : poly (nullptr), filterType (Filter_None), from (0), to (0)
		{
		}
		ConstPolyEdgeInPolyState (const Poly2DType* poly2D, UIndex idx) : poly (poly2D), filterType (Filter_None), from (0), to (0), value (poly2D, idx)
		{
		}
		ConstPolyEdgeInPolyState (const Poly2DType* poly2D, UIndex fromIdx, UIndex toIdx, UIndex idx) : poly (poly2D), filterType (Filter_Range), from (fromIdx), to (toIdx), value (poly2D, idx)
		{
		}
		ConstPolyEdgeInPolyState (const Poly2DType* poly2D, const CustomData& id) : poly (poly2D), filterType (Filter_PolyId), from (0), to (0), value (poly2D, 0)
		{
			value.SetIndex (poly->GetNextEdgeIndex (0, id));
		}

		ConstPolyEdgeInPoly<Poly2DType, CustomData>&  GetCurrent () { return value; }
		const ConstPolyEdgeInPoly<Poly2DType, CustomData>&  GetCurrent () const { return value; }
		void Next ()
		{
			if (filterType & Filter_PolyId) {
				value.SetIndex (poly->GetNextEdgeIndex (value.GetIndex (), value.GetPolyEdgeUserData ()));
				return;
			}
			value.SetIndex (value.GetIndex () + 1);
		}
		void Prev ()
		{
			if (filterType & Filter_PolyId) {
				value.SetIndex (poly->GetPrevEdgeIndex (value.GetIndex (), value.GetPolyEdgeUserData ()));
				return;
			}
			value.SetIndex (value.GetIndex () - 1);
		}
		UIndex GetIndex () const { return (value.GetIndex ()); }
		bool IsEqual (const ConstPolyEdgeInPolyState<Poly2DType, CustomData>& state) const { return (poly == state.poly && value.GetIndex () == state.value.GetIndex ()); }
		bool IsBegin () const
		{
			if (filterType & Filter_Range) {
				return (value.GetIndex () < from);
			}
			return (value.GetIndex () <= 0);
		}
		bool IsEnd () const
		{
			if (filterType & Filter_Range) {
				return (value.GetIndex () >= to);
			}
			return (value.GetIndex () > poly->GetEdgeNum ());
		}
		bool IsValid () const { return poly != nullptr; }		// TODO   setSize != 0, de ez nem jo a polyline-ra
		bool CheckType (const ConstPolyEdgeInPolyState& state) const { return poly == state.poly; }
		const Poly2DType* GetTarget () const { return poly; }

	};

} //namespace Geometry

#endif //GEOMETRY_POLY2DITERATOR_HPP
