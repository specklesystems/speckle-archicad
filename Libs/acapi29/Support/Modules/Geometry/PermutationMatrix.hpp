// *****************************************************************************
// Geometry, platform-independent
//
// Namespaces:    LinAlg
// Contact person: AACs
// *****************************************************************************
#ifndef PermutationMatrix_hpp
#define PermutationMatrix_hpp
#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------
#include "GeometricDefinitions.h"
#include "MatrixAndOp.hpp"
#include "Array.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------


namespace LinAlg {

	// --- Constant definitions	--------------------------------------------------------------------------------------------

	// --- Type definitions	------------------------------------------------------------------------------------------------

	//In linear algebra it is useful to keep track of permutations of rows or columns resulting from swapping them.
	//Mathematically these permutations are represented as matrices and are used as multipliers in order to apply or revert the permutation.
	//These matrices however have special structure (and properties): Each column and row has only one nonzero element which is always one.
	//This structure allows for a compressed storage which is used here.
	//Also, since the utility of these matrices is restricted, we restrict the operations on these and with these matrices as appropriate.
	class GEOMETRY_DLL_EXPORT PermutationMatrix
	{
	public:
		PermutationMatrix (USize sz);
		virtual ~PermutationMatrix ();

		//Build your matrix by calling this method (keep track of your swaps):
		void Swap (USize i, USize j);

		//Operations: Use your matrix in order to apply or revert the same permutation as appropriate.
		template<typename Elem>
		void ApplyPermutation (GS::Array<Elem> & v) const;

		template<typename Elem>
		void RevertPermutation (GS::Array<Elem> & v) const;

		inline USize RevertPermutation (const USize permutatedIndex) const { return originalIndex[permutatedIndex]; }

		template<typename MatrixType>
		void ApplyPermutationToRows (MatrixType & mat) const;

		template<typename MatrixType>
		void ApplyPermutationToCols (MatrixType & mat) const;

		template<typename MatrixType>
		void RevertPermutationFromRows (MatrixType & mat) const;

		template<typename MatrixType>
		void RevertPermutationFromCols (MatrixType & mat) const;

	private:
		USize				size;
		GS::Array<USize>	originalIndex;	//Instead of the matrix, we store the permutation which is equivalent!
	};

	// --- Variable declarations -------------------------------------------------------------------------------------------

	// --- Function declarations -------------------------------------------------------------------------------------------

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//  Implementations:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename Elem>
	void PermutationMatrix::ApplyPermutation ( GS::Array<Elem> & v ) const
	{
		DBASSERT (size == v.GetSize ());
		GS::Array<Elem> tmp(v);
		for (USize i = 0; i < size; ++i) {
			v[i] = tmp[originalIndex[i]];
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename Elem>
	void PermutationMatrix::RevertPermutation ( GS::Array<Elem> & v ) const
	{
		DBASSERT (size == v.GetSize ());
		GS::Array<Elem> tmp(v);
		for (USize i = 0; i < size; ++i) {
			v[originalIndex[i]] = tmp[i];
		}
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename MatrixType>
	void PermutationMatrix::ApplyPermutationToRows (MatrixType & mat) const
	{
		const USize m = mat.GetNumRows ();

		DBASSERT (m == size);

		USize i, j;
		GS::Array<USize> index;
		index.SetSize (size);
		for (i = 0; i < m; ++i) {
			index[i] = i;
		}

		for (i = 0; i < m; ++i) {
			if (index[i] != originalIndex[i]) {//must swap!
				for (j = i+1; j < m; ++j) {
					if (index[j] == originalIndex[i]) {
						GS::Swap (index[i], index[j]);
						mat.SwapRows (i, j);
						break;
					}
				}
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename MatrixType>
	void PermutationMatrix::ApplyPermutationToCols (MatrixType & mat) const
	{
		const USize n = mat.GetNumCols ();

		DBASSERT (n == size);

		USize i, j;
		GS::Array<USize> index;
		index.SetSize (size);
		for (i = 0; i < n; ++i) {
			index[i] = i;
		}

		for (i = 0; i < n; ++i) {
			if (index[i] != originalIndex[i]) {//must swap!
				for (j = i+1; j < n; ++j) {
					if (index[j] == originalIndex[i]) {
						GS::Swap (index[i], index[j]);
						mat.SwapCols (i, j);
						break;
					}
				}
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename MatrixType>
	void PermutationMatrix::RevertPermutationFromRows (MatrixType & mat) const
	{
		const USize m = mat.GetNumRows ();

		DBASSERT (m == size);
		GS::Array<USize> index (originalIndex);

		USize i, j;
		for (i = 0; i < m; ++i) {
			if (index[i] != i) {
				for (j = i+1; j < m; ++j) {
					if (index[j] == i) {
						GS::Swap (index[i], index[j]);
						mat.SwapRows (i, j);
						break;
					}
				}
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename MatrixType>
	void PermutationMatrix::RevertPermutationFromCols (MatrixType & mat) const
	{
		const USize n = mat.GetNumRows ();

		DBASSERT (n == size);
		GS::Array<USize> index (originalIndex);

		USize i, j;
		for (i = 0; i < n; ++i) {
			if (index[i] != i) {
				for (j = i+1; j < n; ++j) {
					if (index[j] == i) {
						GS::Swap (index[i], index[j]);
						mat.SwapCols (i, j);
						break;
					}
				}
			}
		}
	}

} //namespace LinAlg


#endif //PermutationMatrix_hpp
