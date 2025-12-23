// *****************************************************************************
// Geometry, platform-independent
//
// Namespaces: LinAlg   
// Contact person: AACs
// *****************************************************************************
#ifndef GaussUTR_hpp  
#define GaussUTR_hpp

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------
#include "MatrixAndOpInterface.hpp"
#include "PermutationMatrix.hpp"
#include "HashSet.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace LinAlg {

	// --- Constant definitions	--------------------------------------------------------------------------------------------

	// --- Type definitions	------------------------------------------------------------------------------------------------

	class GaussUTROptions
	{
	public: 
		GaussUTROptions ()
		{
			pivoting_considerNZPattern = false;
			pivoting_considerColNorm = false;
			pivoting_preferRowSwaps = false;
		}

		bool  pivoting_considerNZPattern; 
		bool  pivoting_considerColNorm; 
		bool  pivoting_preferRowSwaps;
	};

	template<class ElemType, class MatrixType> 
	class GaussUTR					//transform to an Upper Triangular or Trapezoid form.
	{
	public: 
		GaussUTR (const MatrixType & src, const GaussUTROptions & options);

		bool						SolveEqu (const MatrixType &rhs, MatrixType & sol) const;

		const MatrixType &			GetR () const { return R; }
		USize						GetRank () const { return rankOfR; }
		const PermutationMatrix	&	GetColPermut () const { return colPermutMatrix; } 
		const GS::Array<GS::HashSet<USize> > &
									GetEquCombinations () const { return rowFromOriginalEquations; }
	private: 
		void							CombineRows (USize src, USize target);
		MatrixType						R;
		MatrixType						rhsMatrix; 
		USize							rankOfR; 
		PermutationMatrix				colPermutMatrix; 
		GS::Array<GS::HashSet<USize> >	rowFromOriginalEquations;
	};

	// --- Variable declarations -------------------------------------------------------------------------------------------

	// --- Function declarations -------------------------------------------------------------------------------------------

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//  Implementations: 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class ElemType,class MatrixType>
	void GaussUTR<ElemType,MatrixType>::CombineRows (USize src, USize target)
	{
		if (src != target) {
			const GS::HashSet<USize> &srcSet = rowFromOriginalEquations[src]; 
			GS::HashSet<USize> &trgSet = rowFromOriginalEquations[target]; 

			for (GS::HashSet<USize>::ConstIterator it = srcSet.Begin (); it != srcSet.End (); ++it) {
				trgSet.Add (*it); 
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class ElemType,class MatrixType>
	bool GaussUTR<ElemType,MatrixType>::SolveEqu (const MatrixType & rhs_init, MatrixType & sol) const
	{
		MatrixType rhs (rhsMatrix);
		rhs *= rhs_init;
		const bool succ = R.SolveUTR (rhs, sol); 
		colPermutMatrix.RevertPermutationFromRows (sol);
		return succ; 
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class ElemType,class MatrixType>
	GaussUTR<ElemType,MatrixType>::GaussUTR (const MatrixType & src, const GaussUTROptions & options)
		: R( src )
		, rhsMatrix (src.GetNumRows (), src.GetNumRows ())
		, colPermutMatrix (src.GetNumCols ())
	{
		USize i, j, jj, kk;
		ElemType mxAbsElem {}, w {}, tmp {}, Rii {}, one {}; 
		const USize m = R.GetNumRows (); 
		const USize n = R.GetNumCols (); 
		GS::Array<ElemType> colNZStrength; 
		GS::Array<ElemType> colNorm; 
		typename MatrixType::Iterator itCol, itRow;

		rowFromOriginalEquations.SetSize (m); 
		tmp = LinAlg::GetZeroOf (tmp);
		one = LinAlg::GetOneOf (one);
		for (i = 0; i < m; ++i) {
			rowFromOriginalEquations[i].Add (i);
			for (j = 0; j < m; ++j) {
				rhsMatrix (i,j) = tmp;
			}
			rhsMatrix (i, i) = one;
		}

		colNZStrength.SetSize (n);
		colNZStrength.Fill (1);

		colNorm.SetSize (n);
		if (options.pivoting_considerColNorm) {
			for (j = 0; j < n; ++j) {
				tmp = LinAlg::GetZeroOf (tmp);
				for (R.InitColIterator (j, itCol); !itCol.IsAtEnd (); ++itCol) {
					if (!LinAlg::IsZero (itCol.GetValue ())) {
						tmp += itCol.GetValue () * itCol.GetValue ();
					}
				}
				colNorm[j] = tmp;
			}
		}
		else {
			colNorm.Fill (1);
		}

		for (i = 0, rankOfR = 0; i < m && i < n; ++i, ++rankOfR) {

			if (options.pivoting_considerNZPattern) {
				//find the number of nonzero for each column (from i and up):
				for (j = i; j < n; ++j) {
					tmp = LinAlg::GetOneOf (tmp);
					for (R.InitColIterator (i, j, itCol); !itCol.IsAtEnd (); ++itCol) {
						if (!LinAlg::IsZero (itCol.GetValue ())) {
							tmp *= 2;
						}
					}
					colNZStrength[j] = tmp;
				}
			}

			//pivoting, the more nonzero in the column the more we are willing to select it!
			jj = i;	//nothing selected
			kk = i;	//nothing selected
			mxAbsElem = LinAlg::GetZeroOf (mxAbsElem);
			for (j = i; j < n; ++j) {
				w = colNorm[j] / colNZStrength[j];
				for (R.InitColIterator (i, j, itCol); !itCol.IsAtEnd (); ++itCol) {
					tmp = itCol.GetValue () * w; 
					if (tmp < 0) tmp = -tmp;
					if (tmp > mxAbsElem) {
						mxAbsElem = tmp;
						jj = j; 
						kk = itCol.GetRowIndex ();
					}
				}

				if (options.pivoting_preferRowSwaps && !LinAlg::IsZero (mxAbsElem)) {
					break;
				}
			}

			if (jj != i) {
				R.SwapCols (i,jj);
				GS::Swap (colNorm[i], colNorm[jj]); 
				colPermutMatrix.Swap (i,jj); 
			}
			if (kk != i) {
				R.SwapRows (i, kk);
				rhsMatrix.SwapRows (i, kk);
				GS::Swap (rowFromOriginalEquations[i], rowFromOriginalEquations[kk]); 
			}

			Rii = R(i,i);

			if (LinAlg::IsZero (Rii)) {
				return;
			}

			//Eliminate all the elements under the diagonal: 
			for (R.InitColIterator (i+1, i, itCol); !itCol.IsAtEnd (); ++itCol) {
				if (LinAlg::IsZero (itCol.GetValue ())) { 
					continue;
				}
				tmp = itCol.GetValue () / Rii; 
				//Simplify (tmp);
				
				for (R.InitRowIterator (i, i, itRow); !itRow.IsAtEnd (); ++itRow) {
					R(itCol.GetRowIndex (), itRow.GetColIndex ()) -= tmp * itRow.GetValue ();
					CombineRows (i, itCol.GetRowIndex ()); 
					//Simplify (R(j,k));
				}

				for (rhsMatrix.InitRowIterator (i, 0, itRow); !itRow.IsAtEnd (); ++itRow) {
					rhsMatrix(itCol.GetRowIndex (), itRow.GetColIndex ()) -= tmp * itRow.GetValue ();
				}
			}

			if (i+1 < m) {
				R.SetBlockZero (i+1, i, m-i-1, 1);
			}
		}
	}

} //namespace LinAlg


#endif //GaussUTR_hpp
