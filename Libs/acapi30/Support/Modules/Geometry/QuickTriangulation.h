/****************************************************************************/
/*																			*/
/*						PROTOTYPES FOR CX ROUTINES							*/
/*																			*/
/****************************************************************************/

#ifndef _QUICKTRIANGULATION_H_
#define _QUICKTRIANGULATION_H_

#pragma once

#include "GeometricDefinitions.h"

#include "VA.hpp"
#include "PagedArray.hpp"
/*================================	  TYPES		============================*/

typedef	struct {
	Int32	type;		/* valid if x < vx */
	Int32	from, to;
	Int32	id;
	Int32	contour;
	double	vx, vy;
}	PNOD;

typedef GS::PagedArray<Int32> DecArray;

template <typename Type, template<typename> class BaseContainer> class VATLikeArray : public BaseContainer<Type> {
	private:
		UIndex freeInd;
		UIndex lastInd;
	public:
		VATLikeArray () : freeInd (0), lastInd (0) {}
		void Init (USize size) {
			BaseContainer<Type>::Clear ();
			BaseContainer<Type>::SetSize (size);
			for (UIndex i = 0; i < size; i++) {
				BaseContainer<Type>::operator [] (i).type = VAT_FREE;
			}
			lastInd = freeInd = 0;
		}
		inline void Update ()	{
			USize size = BaseContainer<Type>::GetSize ();
			for (freeInd = 0; freeInd < size; freeInd++) {
				if (BaseContainer<Type>::operator [] (freeInd).type == VAT_FREE)
					break;
			}
			for (lastInd = size; lastInd > 0; lastInd--) {
				if (BaseContainer<Type>::operator [] (lastInd - 1).type != VAT_FREE) {
					break;
				}
			}
		}
		inline UIndex LastInd () {
			return lastInd;
		}
		inline UIndex Find () {
			USize size = BaseContainer<Type>::GetSize ();
			if (freeInd < size && BaseContainer<Type>::operator [] (freeInd).type != VAT_FREE) {
				for (freeInd = 0; freeInd < size; freeInd++) {
					if (BaseContainer<Type>::operator [] (freeInd).type == VAT_FREE)
						break;
				}
			}
			UIndex foundIndex;
			if (freeInd >= size) {
				foundIndex = size;
				BaseContainer<Type>::Push (Type ());

			} else {
				foundIndex = freeInd;
			}
			BaseContainer<Type>::operator [] (foundIndex).type = 0L;
			if (foundIndex >= lastInd) {
				lastInd = foundIndex + 1;
			}
			size = BaseContainer<Type>::GetSize ();
			for (freeInd = foundIndex + 1; freeInd < size; freeInd++) {
				if (BaseContainer<Type>::operator [] (freeInd).type == VAT_FREE)
					break;
			}
			return foundIndex;
		}
		inline void Clear (UIndex index) {
			BaseContainer<Type>::operator [] (index).type = VAT_FREE;
			if (index < freeInd)
				freeInd = index;
		}
};

typedef VATLikeArray<PNOD, GS::DefaultPagedArray> PNODArray;

typedef struct {
	Int32	index;
	PNODArray* pnod;
} CXcmpStruct;

/*================================	  MACROS	============================*/

#define MAXCONV			30

/*================================	PROTOTYPES	============================*/


GEOMETRY_DLL_EXPORT
void	CXPrepare2DData (PNODArray& pnod, Int32 npb, const Int32* pends,
						 Int32 npc, const double* pcoos, double* xxmax, Int32* npnod);
GEOMETRY_DLL_EXPORT
Int32	CXdpMain (DecArray& convexdp, PNODArray& pnod, bool gentris,
				  Int32 npnod, double xmax, bool* selfintsect, Int32 nlimit);
GEOMETRY_DLL_EXPORT
GSErr	CXPolySelfIntersection (Int32 npb, Int32* pends, Int32 npc, double* pcoos);

GEOMETRY_DLL_EXPORT
short	CXCorrectPolyCCW (Int32 npb, Int32* pends, Int32 npc, double* pcoos);

GEOMETRY_DLL_EXPORT
Int32	CXPoly2Triangles (Int32 npb, const Int32* pends, Int32 npc, const double* pcoos, double** tricoos);

#endif
