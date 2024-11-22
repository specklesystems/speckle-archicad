// *********************************************************************************************************************
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	NZ
//
// SG compatible
//
// *********************************************************************************************************************

#if !defined POINTMULTIHASH_HPP
#define POINTMULTIHASH_HPP

#pragma once

#include "Array.hpp"
#include "Discretes.hpp"
#include "StableHashTable.hpp"


namespace PointIndex
{

template <int I, class T>
class PointMultiHash
{
public:
	PointMultiHash ():
		switchedToLarge (false)
	{
	}

	GS::Array<T> Get (const Point<I>& point) const
	{
		GS::Array<T> result;

		if (switchedToLarge) {
			pointMultiHashLarge.Get (point, result);
		} else {
			pointMultiHashSmall.Get (point, result);
		}

		return result;
	}

	GS::Array<T> GetDirect (const Point<I>& point) const
	{
		GS::Array<T> result;

		if (switchedToLarge) {
			pointMultiHashLarge.GetDirect (point, result);
		} else {
			pointMultiHashSmall.GetDirect (point, result);
		}

		return result;
	}

	void Put (const Point<I>& point, const T& elem)
	{
		const ListElem<I, T> listElem (point, elem);
		if (switchedToLarge) {
			pointMultiHashLarge.Put (listElem);
		} else {
			if (pointMultiHashSmall.GetSize () < Pow3<I>::Result) {
				pointMultiHashSmall.Put (listElem);
			} else {
				SwitchToLarge ();
				pointMultiHashLarge.Put (listElem);
			}
		}
	}

private:
	template <int II, class TI>
	struct ListElem
	{
		Discretes<II>	first;
		const TI		second;

		ListElem (const Discretes<II>& first, const TI& second):
			first (first),
			second (second)
		{
		}
	};

	template <int II, class TI>
	class PointMultiHashLarge
	{
	private:
		typedef GS::ArrayFB<TI, 1>	ArrayType;
	
	private:
		GS::StableHashTable<Discretes<II>, ArrayType>	arrayHash;

	public:
		GS::Array<TI> Get (const Point<II>& point) const
		{
			GS::Array<TI> result;
			Get (point, result);

			return result;
		}

		GS::Array<TI> GetDirect (const Point<II>& point) const
		{
			GS::Array<TI> result;
			GetDirect (point, result);

			return result;
		}

		void Put (const Point<II>& point, const TI& elem)
		{
			Put (ListElem<II, TI> (point, elem));
		}

		void Get (const Point<II>& point, GS::Array<TI>& result) const
		{
			auto proc = [this, &result] (const Discretes<II>& discretes)
			{
				const ArrayType* array = arrayHash.GetPtr (discretes);
				if (array != nullptr) {
					for (auto it = array->Enumerate (); it != nullptr; ++it) {
						result.Push (*it);
					}
				}
			};

			Discretes<II> discretes (point);
			discretes.EnumerateNeighbours (proc);
		}

		void GetDirect (const Point<II>& point, GS::Array<TI>& result) const
		{
			Discretes<II> discretes (point);
			const ArrayType* array = arrayHash.GetPtr (discretes);
			if (array != nullptr) {
				for (auto it = array->Enumerate (); it != nullptr; ++it) {
					result.Push (*it);
				}
			}
		}

		void Put (const ListElem<II, TI>& listElem)
		{
			ArrayType* array = arrayHash.GetPtr (listElem.first);
			if (array == nullptr) {
				arrayHash.Add (listElem.first, ArrayType ());
				array = arrayHash.GetPtr (listElem.first);
			}

			array->Push (listElem.second);
		}
	};

	template <int II, class TI>
	class PointMultiHashSmall
	{
	private:
		GS::ArrayFB<ListElem<II, TI>, Pow3<II>::Result>	arrayList;

	public:
		GS::Array<TI> Get (const Point<II>& point) const
		{
			GS::Array<TI> result;
			Get (point, result);

			return result;
		}

		GS::Array<TI> GetDirect (const Point<II>& point) const
		{
			GS::Array<TI> result;
			GetDirect (point, result);

			return result;
		}

		void Put (const Point<II>& point, const TI& elem)
		{
			Put (ListElem<II, TI> (point, elem));
		}

		void Clear ()
		{
			arrayList.Clear ();
		}

		USize GetSize () const
		{
			return arrayList.GetSize ();
		}

		GS::ConstForwardIterator<ListElem<II, TI>> Enumerate () const
		{
			return arrayList.EnumerateGeneral ();
		}

		void Get (const Point<II>& point, GS::Array<TI>& result) const
		{
			const Discretes<II> discretes (point);
			for (auto it = arrayList.Enumerate (); it != nullptr; ++it) {
				if (discretes.IsNeighbour (it->first)) {
					result.Push (it->second);
				}
			}
		}

		void GetDirect (const Point<II>& point, GS::Array<TI>& result) const
		{
			const Discretes<II> discretes (point);
			for (auto it = arrayList.Enumerate (); it != nullptr; ++it) {
				if (discretes == it->first) {
					result.Push (it->second);
				}
			}
		}

		void Put (const ListElem<II, TI>& listElem)
		{
			arrayList.Push (listElem);
		}
	};

private:
	PointMultiHashSmall<I, T>	pointMultiHashSmall;
	PointMultiHashLarge<I, T>	pointMultiHashLarge;
	bool						switchedToLarge;

private:
	void SwitchToLarge ()
	{
		for (auto it = pointMultiHashSmall.Enumerate (); it != nullptr; ++it) {
			pointMultiHashLarge.Put (*it);
		}
		pointMultiHashSmall.Clear ();
		switchedToLarge = true;
	}
};

}

#endif
