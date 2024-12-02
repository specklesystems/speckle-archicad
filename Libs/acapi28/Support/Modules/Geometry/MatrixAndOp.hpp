// *****************************************************************************
// Geometry, platform-independent
//
// Namespaces:    LinAlg   
// Contact person: AACs
// *****************************************************************************
#ifndef MatrixAndOp_hpp 
#define MatrixAndOp_hpp
#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------
#include "MatrixAndOpInterface.hpp"
#include "Array.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace LinAlg {

	// --- Constant definitions	--------------------------------------------------------------------------------------------

	// --- Type definitions	------------------------------------------------------------------------------------------------

	template<class ElemType>
	class DenseMatrixEntryIterator; 



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>	
	class MatrixAndOp 
		: public MatrixAndOpInterface<ElemType, MatrixAndOp<ElemType> >
	{
	public: 
		typedef DenseMatrixEntryIterator<ElemType> Iterator;

		explicit MatrixAndOp (USize m = 1, USize n = 1);
		MatrixAndOp (const MatrixAndOp & src);
		virtual ~MatrixAndOp () {}

		//get the size:
		virtual USize GetNumRows () const  override { return nRow; }
		virtual USize GetNumCols () const  override { return nCol; }

		//Iterators: 
		virtual GS::SharedPtr<MatrixEntryIterator<ElemType> > GetRowIterator (const USize rowIndex) override;
		virtual GS::SharedPtr<MatrixEntryIterator<ElemType> > GetRowIterator (const USize rowIndex, const USize colIndex) override;
		virtual GS::SharedPtr<MatrixEntryIterator<ElemType> > GetColIterator (const USize colIndex) override;
		virtual GS::SharedPtr<MatrixEntryIterator<ElemType> > GetColIterator (const USize rowIndex, const USize colIndex) override;
		
		void InitRowIterator (const USize rowIndex, Iterator & it) const;
		void InitRowIterator (const USize rowIndex, const USize colIndex, Iterator & it) const;
		void InitColIterator (const USize colIndex, Iterator & it) const;
		void InitColIterator (const USize rowIndex, const USize colIndex, Iterator & it) const;

		void InitRowIterator (const USize rowIndex, Iterator & it);
		void InitRowIterator (const USize rowIndex, const USize colIndex, Iterator & it);
		void InitColIterator (const USize colIndex, Iterator & it);
		void InitColIterator (const USize rowIndex, const USize colIndex, Iterator & it);

		//operators:
		virtual void Reset (USize m, USize n) override;
		virtual void SetUnit () override; 
		virtual MatrixAndOp<ElemType> & operator = (const MatrixAndOp<ElemType> &rhs) override; 
		virtual MatrixAndOp<ElemType> & operator += (const MatrixAndOp<ElemType> &rhs) override; 
		virtual MatrixAndOp<ElemType> & operator -= (const MatrixAndOp<ElemType> &rhs) override; 
		virtual MatrixAndOp<ElemType> & operator *= (const MatrixAndOp<ElemType> &rhs) override; 
		virtual MatrixAndOp<ElemType> & operator *= (const ElemType &rhs) override; 

		ElemType CalcQuadFrom (const MatrixAndOp<ElemType> &vector) const;

		//block operations, the target is always this object!
		virtual void CopyBlock (
			const MatrixAndOp<ElemType> & src, 
			USize src_i, USize src_j, 
			USize trg_i, USize trg_j,
			USize blckRows, USize blckCols  //this is the block's size
			) override;
		
		virtual void AddBlock (
			const MatrixAndOp<ElemType> & src, 
			USize src_i, USize src_j, 
			USize trg_i, USize trg_j,
			USize blckRows, USize blckCols  //this is the block's size
			) override;

		virtual void SubBlock (
			const MatrixAndOp<ElemType> & src, 
			USize src_i, USize src_j, 
			USize trg_i, USize trg_j,
			USize blckRows, USize blckCols  //this is the block's size
			) override;

		virtual void MultBlock (
			const MatrixAndOp<ElemType> & src, 
			USize src_i, USize src_j, 
			USize trg_i, USize trg_j,
			USize blckSize  //Only quadratic is possible!
			) override;

		virtual void SetBlockZero (
			USize trg_i, USize trg_j,
			USize blckRows, USize blckCols 
			) override;

		//Norms: 
		virtual ElemType GetAbsMaxValue () const override; 
		virtual ElemType FrobeniusSqr () const override;


		//swaps: 
		virtual void SwapRows (USize r1, USize r2) override; 
		virtual void SwapCols (USize c1, USize c2) override; 
		virtual void Transpose () override; 

		//Solve: 
		virtual bool SolveUTR (const MatrixAndOp<ElemType> & rhs, MatrixAndOp<ElemType> & x) const override;  //matrix is Upper Triangular already!
#ifdef DEBUVERS
		//for debugging only:
		virtual void CheckSolution (const MatrixAndOp<ElemType> & rhs, MatrixAndOp<ElemType> & x) const override;
#endif
		void CalcSolutionResidual (const MatrixAndOp<ElemType> & rhs, const MatrixAndOp<ElemType> & x, MatrixAndOp<ElemType> &residual) const;

		//access by elements: 
		virtual ElemType & operator () (USize i, USize j) override;
		virtual const ElemType & operator () (USize i, USize j) const override;

		void BFGS_Update (const MatrixAndOp<ElemType> & Stp, const MatrixAndOp<ElemType> & GrdChng); 

		//debug
		virtual void Report (const char * matrixName, const char * format = "%5.5lf") const override; 
		virtual void ReportDiag (const char * matrixName, const char * format = "%5.5lf") const override; 

	private:
		USize nRow, nCol; 
		GS::Array < GS::Array <ElemType> > Mtrx;
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class ElemType>
	class DenseMatrixEntryIterator //can be row or column iterator, this is just an interface!
		: public MatrixEntryIterator<ElemType>
	{
	public:
		DenseMatrixEntryIterator (); 
		DenseMatrixEntryIterator (MatrixAndOp<ElemType> * mtrx_init, const bool rowIterator, USize startRowIndex_init, USize startColIndex_init, USize endRowIndex_init, USize endColIndex_init); 
		virtual ~DenseMatrixEntryIterator () {} 
		void Init (MatrixAndOp<ElemType> * mtrx_init, const bool rowIterator, USize startRowIndex_init, USize startColIndex_init, USize endRowIndex_init, USize endColIndex_init); 
		void Init (const MatrixAndOp<ElemType> * mtrx_init, const bool rowIterator, USize startRowIndex_init, USize startColIndex_init, USize endRowIndex_init, USize endColIndex_init); 

		virtual bool IsAtEnd () const override; 
		virtual DenseMatrixEntryIterator& operator ++ () override;		//to the next entry
		virtual USize GetRowIndex () const override;
		virtual USize GetColIndex () const override;
		virtual ElemType & GetValue () override; 
		virtual const ElemType & GetValue () const override; 

	private:
		MatrixAndOp<ElemType> * mtrx; 
		bool isRowIt; 
		bool isConstIterator;
		USize startRowIndex, startColIndex;
		USize endRowIndex, endColIndex;
		USize index;

		ElemType retForConstIter; 
	};

	// --- Variable declarations -------------------------------------------------------------------------------------------

	// --- Function declarations -------------------------------------------------------------------------------------------

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//  Implementations: 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	DenseMatrixEntryIterator<ElemType>::DenseMatrixEntryIterator () :
		mtrx (nullptr),
		isRowIt (true),
		isConstIterator (true),
		startRowIndex (0),
		startColIndex (0),
		endRowIndex (0),
		endColIndex (0),
		index (0),
		retForConstIter ()
	{
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	DenseMatrixEntryIterator<ElemType>::DenseMatrixEntryIterator (
		MatrixAndOp<ElemType> * mtrx_init, 
		const bool rowIterator, 
		USize startRowIndex_init, USize startColIndex_init, USize endRowIndex_init, USize endColIndex_init)

	{
		Init (mtrx_init, rowIterator, startRowIndex_init, startColIndex_init, endRowIndex_init, endColIndex_init);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void DenseMatrixEntryIterator<ElemType>::Init (
		MatrixAndOp<ElemType> * mtrx_init, 
		const bool rowIterator, 
		USize startRowIndex_init, USize startColIndex_init, USize endRowIndex_init, USize endColIndex_init)
	{
		mtrx = mtrx_init;
		isRowIt = rowIterator;
		isConstIterator = false;
		startRowIndex = startRowIndex_init;
		startColIndex = startColIndex_init;
		endRowIndex = endRowIndex_init;
		endColIndex = endColIndex_init;

		index = isRowIt ? startColIndex : startRowIndex; 
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void DenseMatrixEntryIterator<ElemType>::Init (
		const MatrixAndOp<ElemType> * mtrx_init, 
		const bool rowIterator, 
		USize startRowIndex_init, USize startColIndex_init, USize endRowIndex_init, USize endColIndex_init)
	{
		mtrx = (MatrixAndOp<ElemType> *) mtrx_init; //cast out the const!
		isRowIt = rowIterator;
		isConstIterator = true;
		startRowIndex = startRowIndex_init;
		startColIndex = startColIndex_init;
		endRowIndex = endRowIndex_init;
		endColIndex = endColIndex_init;

		index = isRowIt ? startColIndex : startRowIndex; 
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	bool DenseMatrixEntryIterator<ElemType>::IsAtEnd () const
	{
		return isRowIt ? (startRowIndex >= endRowIndex || index >= endColIndex) : (index >= endRowIndex || startColIndex >= endColIndex);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	DenseMatrixEntryIterator<ElemType>& DenseMatrixEntryIterator<ElemType>::operator ++ ()
	{
		++index;
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	USize DenseMatrixEntryIterator<ElemType>::GetRowIndex () const
	{
		return isRowIt ? startRowIndex : index; 
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	USize DenseMatrixEntryIterator<ElemType>::GetColIndex () const
	{
		return isRowIt ? index : startColIndex; 
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	ElemType & DenseMatrixEntryIterator<ElemType>::GetValue ()
	{
		if (isConstIterator) {
			retForConstIter = isRowIt ? (*mtrx) (startRowIndex, index) : (*mtrx) (index, startColIndex); 
			return retForConstIter; 
		}

		return isRowIt ? (*mtrx) (startRowIndex, index) : (*mtrx) (index, startColIndex);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	const ElemType & DenseMatrixEntryIterator<ElemType>::GetValue () const
	{
		return isRowIt ? (*mtrx) (startRowIndex, index) : (*mtrx) (index, startColIndex);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	GS::SharedPtr<MatrixEntryIterator<ElemType> > MatrixAndOp<ElemType>::GetRowIterator (USize rowIndex)
	{
		return new DenseMatrixEntryIterator<ElemType> (this, true, rowIndex, 0, GetNumRows (), GetNumCols ());
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	GS::SharedPtr<MatrixEntryIterator<ElemType> > MatrixAndOp<ElemType>::GetRowIterator (USize rowIndex, USize colIndex)
	{
		return new DenseMatrixEntryIterator<ElemType> (this, true, rowIndex, colIndex, GetNumRows (), GetNumCols ());
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	GS::SharedPtr<MatrixEntryIterator<ElemType> > MatrixAndOp<ElemType>::GetColIterator (USize colIndex)
	{
		return new DenseMatrixEntryIterator<ElemType> (this, false, 0, colIndex, GetNumRows (), GetNumCols ());
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	GS::SharedPtr<MatrixEntryIterator<ElemType> > MatrixAndOp<ElemType>::GetColIterator (USize rowIndex, USize colIndex)
	{
		return new DenseMatrixEntryIterator<ElemType> (this, false, rowIndex, colIndex, GetNumRows (), GetNumCols ());
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void MatrixAndOp<ElemType>::InitRowIterator (const USize rowIndex, Iterator & it) const
	{
		it.Init (this, true, rowIndex, 0, GetNumRows (), GetNumCols ());
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void MatrixAndOp<ElemType>::InitRowIterator (const USize rowIndex, const USize colIndex, Iterator & it) const
	{
		it.Init (this, true, rowIndex, colIndex, GetNumRows (), GetNumCols ());
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void MatrixAndOp<ElemType>::InitColIterator (const USize colIndex, Iterator & it) const
	{
		it.Init (this, false, 0, colIndex, GetNumRows (), GetNumCols ());
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void MatrixAndOp<ElemType>::InitColIterator (const USize rowIndex, const USize colIndex, Iterator & it) const
	{
		it.Init (this, false, rowIndex, colIndex, GetNumRows (), GetNumCols ());
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void MatrixAndOp<ElemType>::InitRowIterator (const USize rowIndex, Iterator & it)
	{
		it.Init (this, true, rowIndex, 0, GetNumRows (), GetNumCols ());
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void MatrixAndOp<ElemType>::InitRowIterator (const USize rowIndex, const USize colIndex, Iterator & it)
	{
		it.Init (this, true, rowIndex, colIndex, GetNumRows (), GetNumCols ());
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void MatrixAndOp<ElemType>::InitColIterator (const USize colIndex, Iterator & it)
	{
		it.Init (this, false, 0, colIndex, GetNumRows (), GetNumCols ());
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void MatrixAndOp<ElemType>::InitColIterator (const USize rowIndex, const USize colIndex, Iterator & it)
	{
		it.Init (this, false, rowIndex, colIndex, GetNumRows (), GetNumCols ());
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	MatrixAndOp<ElemType>::MatrixAndOp (USize m, USize n) 
	{
		Reset ( m, n );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	MatrixAndOp<ElemType>::MatrixAndOp (const MatrixAndOp & src)
	{
		nRow = src.nRow;
		nCol = src.nCol; 
		Mtrx = src.Mtrx;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void MatrixAndOp<ElemType>::Reset (USize m, USize n) 
	{
		nRow = m;
		nCol = n;

		ElemType zero {};
		zero = GetZeroOf (zero);
		Mtrx.SetSize (nRow); 
		for (USize i = 0; i < nRow; ++i ) {
			Mtrx[i].SetSize (nCol);
			Mtrx[i].Fill ( zero );
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void MatrixAndOp<ElemType>::SetUnit () 
	{
		ElemType zero {}, one {};
		zero = GetZeroOf (zero);
		one = GetOneOf (one);

		for (USize i = 0; i < nRow; ++i ) {
			Mtrx[i].Fill ( zero );
			Mtrx[i][i] = one;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	MatrixAndOp<ElemType> & MatrixAndOp<ElemType>::operator = (const MatrixAndOp<ElemType> & rhs)
	{
		nRow = rhs.nRow;
		nCol = rhs.nCol; 
		Mtrx = rhs.Mtrx; 
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	MatrixAndOp<ElemType> & MatrixAndOp<ElemType>::operator += (const MatrixAndOp<ElemType> & rhs)
	{
		DBASSERT (nRow == rhs.nRow);
		DBASSERT (nCol == rhs.nCol);

		for (USize i = 0; i < nRow; ++i) {
			for (USize j = 0; j < nCol; ++j) {
				Mtrx[i][j] += rhs.Mtrx[i][j]; 
			}
		}
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	MatrixAndOp<ElemType> & MatrixAndOp<ElemType>::operator -= (const MatrixAndOp<ElemType> & rhs)
	{
		DBASSERT (nRow == rhs.nRow);
		DBASSERT (nCol == rhs.nCol);

		for (USize i = 0; i < nRow; ++i) {
			for (USize j = 0; j < nCol; ++j) {
				Mtrx[i][j] -= rhs.Mtrx[i][j]; 
			}
		}
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	MatrixAndOp<ElemType> & MatrixAndOp<ElemType>::operator *= (const MatrixAndOp<ElemType> & rhs)
	{
		const USize m = nRow; 
		const USize n = nCol; 
		const USize l = rhs.nCol; 
		ElemType lc; 

		DBASSERT (nCol == rhs.nRow);
		const GS::Array<GS::Array<ElemType> > Mtrx_orig(Mtrx); 
		
		Reset (m,l);

		for (USize i = 0; i < nRow; ++i) {
			for (USize j = 0; j < nCol; ++j) {
				lc = GetZeroOf (lc);
				for (USize k = 0; k < n; ++k) { 
					lc += Mtrx_orig[i][k] * rhs(k,j);
				}

				Mtrx[i][j] = lc; 
			}
		}
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	MatrixAndOp<ElemType> & MatrixAndOp<ElemType>::operator *= (const ElemType & rhs)
	{
		for (USize i = 0; i < nRow; ++i) {
			for (USize j = 0; j < nCol; ++j) {
				Mtrx[i][j] *= rhs; 
			}
		}
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	ElemType MatrixAndOp<ElemType>::CalcQuadFrom (const MatrixAndOp<ElemType> &vector) const
	{
		DBASSERT (vector.GetNumCols () == 1); 
		DBASSERT (vector.GetNumRows () == nRow); 
		DBASSERT (nCol == nRow); 

		ElemType res {}; 
		res = LinAlg::GetZeroOf (res); 

		for (USize i = 0; i < nRow; ++i) {
			for (USize j = 0; j < nCol; ++j) {
				res += Mtrx[i][j] * vector (i, 0) * vector (j, 0); 
			}
		}

		return res;
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void MatrixAndOp<ElemType>::CopyBlock (
		const MatrixAndOp<ElemType> & src, 
		USize src_i, USize src_j, 
		USize trg_i, USize trg_j,
		USize blckRows, USize blckCols  //this is the block's size
		)
	{
		DBASSERT (trg_i + blckRows <= nRow);
		DBASSERT (trg_j + blckCols <= nCol);
		DBASSERT (src_i + blckRows <= src.nRow);
		DBASSERT (src_j + blckCols <= src.nCol);
		
		for (USize i = 0; i < blckRows; ++i) {
			for (USize j = 0; j < blckCols; ++j) {
				Mtrx[trg_i+i][trg_j+j] = src.Mtrx[src_i+i][src_j+j];
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void MatrixAndOp<ElemType>::AddBlock (
		const MatrixAndOp<ElemType> & src, 
		USize src_i, USize src_j, 
		USize trg_i, USize trg_j,
		USize blckRows, USize blckCols  //this is the block's size
		)
	{
		DBASSERT (trg_i + blckRows <= nRow);
		DBASSERT (trg_j + blckCols <= nCol);
		DBASSERT (src_i + blckRows <= src.nRow);
		DBASSERT (src_j + blckCols <= src.nCol);
		for (USize i = 0; i < blckRows; ++i) {
			for (USize j = 0; j < blckCols; ++j) {
				Mtrx[trg_i+i][trg_j+j] += src.Mtrx[src_i+i][src_j+j];
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void MatrixAndOp<ElemType>::SubBlock (
		const MatrixAndOp<ElemType> & src, 
		USize src_i, USize src_j, 
		USize trg_i, USize trg_j,
		USize blckRows, USize blckCols  //this is the block's size
		)
	{
		DBASSERT (trg_i + blckRows <= nRow);
		DBASSERT (trg_j + blckCols <= nCol);
		DBASSERT (src_i + blckRows <= src.nRow);
		DBASSERT (src_j + blckCols <= src.nCol);
		for (USize i = 0; i < blckRows; ++i) {
			for (USize j = 0; j < blckCols; ++j) {
				Mtrx[trg_i+i][trg_j+j] -= src.Mtrx[src_i+i][src_j+j];
			}
		}		
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void MatrixAndOp<ElemType>::MultBlock (
		const MatrixAndOp<ElemType> & src, 
		USize src_i, USize src_j, 
		USize trg_i, USize trg_j,
		USize blckSize  //Only quadratic is possible!
		)
	{
		DBASSERT (trg_i + blckSize <= nRow);
		DBASSERT (trg_j + blckSize <= nCol);
		DBASSERT (src_i + blckSize <= src.nRow);
		DBASSERT (src_j + blckSize <= src.nCol);
		
		MatrixAndOp<ElemType> blockOrig(blckSize, blckSize);
		blockOrig.CopyBlock (*this, trg_i, trg_j, 0, 0, blckSize, blckSize);
		ElemType tmp; 

		for (USize i = 0; i < blckSize; ++i) {
			for (USize j = 0; j < blckSize; ++j) {
				tmp = LinAlg::GetZeroOf (tmp);
				for (USize k = 0; k < blckSize; ++k) {
					tmp += blockOrig(i,k) * src(src_i+k,src_j+j);
				}
				Mtrx[trg_i+i][trg_j+j] = tmp;
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void MatrixAndOp<ElemType>::SetBlockZero (
		USize trg_i, USize trg_j,
		USize blckRows, USize blckCols )
	{
		ElemType zero {}; 
		zero = LinAlg::GetZeroOf (zero);

		for (USize i = 0; i < blckRows; ++i) {
			for (USize j = 0; j < blckCols; ++j) {
				Mtrx[trg_i+i][trg_j+j] = zero;
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType> 
	ElemType MatrixAndOp<ElemType>::GetAbsMaxValue () const
	{
		ElemType res {}, tmp {};
		res = GetZeroOf (res);

		for (USize i = 0; i < nRow; ++i) {
			for (USize j = 0; j < nCol; ++j) {
				tmp = Mtrx[i][j];
				if (tmp < 0) {
					tmp = -tmp;
				}
				if (tmp > res) {
					res = tmp;
				}
			}
		}
		return res;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType> 
	ElemType MatrixAndOp<ElemType>::FrobeniusSqr () const
	{
		ElemType res {}, tmp {};
		res = GetZeroOf (res);

		for (USize i = 0; i < nRow; ++i) {
			for (USize j = 0; j < nCol; ++j) {
				tmp = Mtrx[i][j];
				if (tmp < 0) {
					tmp = -tmp;
				}

				res += tmp * tmp;
			}
		}
		return res;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void MatrixAndOp<ElemType>::SwapRows (USize r1, USize r2)
	{
		DBASSERT (r1<nRow);
		DBASSERT (r2<nRow);

		if (r1 != r2) {
			for (USize j = 0; j < nCol; ++j) {
				GS::Swap (Mtrx[r1][j], Mtrx[r2][j]); 
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void MatrixAndOp<ElemType>::SwapCols (USize c1, USize c2)
	{
		DBASSERT (c1<nCol);
		DBASSERT (c2<nCol);

		if (c1 != c2) {
			for (USize i = 0; i < nRow; ++i) {
				GS::Swap (Mtrx[i][c1], Mtrx[i][c2]); 
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void MatrixAndOp<ElemType>::Transpose ()
	{
		const USize m = nRow; 
		const USize n = nCol;
		GS::Array<GS::Array<ElemType> > Old(Mtrx);
		USize i, j;

		if (m != n) {
			Reset (n,m); 
		}

		for (i = 0; i < m; ++i) {
			for (j = 0; j < n; ++j) {
				Mtrx[j][i] = Old[i][j];
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	bool MatrixAndOp<ElemType>::SolveUTR (const MatrixAndOp<ElemType> & rhs, MatrixAndOp<ElemType> & x) const
	{
		//matrix is Upper Triangular already!
		DBASSERT (nRow == nCol); 
		const USize n = nRow; 
		x = rhs;
		const USize nRhs = x.GetNumCols ();
		USize i, j, k;

		for (i = 0; i < n; ++i ) {
			const USize equ = n-i-1;
			ElemType M_equ_equ = Mtrx[equ][equ]; 
			if ( IsZero (M_equ_equ) ) {
				return false;
			}

			for (j = 0; j < nRhs; ++j) {
				const ElemType tmp = ( x (equ, j) /= M_equ_equ ); 

				for (k = 0; k < equ; ++k) {
					x (k,j) -= tmp * Mtrx[k][equ];
				}
			}
		}

		return true;
	}

#ifdef DEBUVERS
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void MatrixAndOp<ElemType>::CheckSolution (const MatrixAndOp<ElemType> & rhs, MatrixAndOp<ElemType> & x) const
	{
		MatrixAndOp<ElemType> residual (*this);
		residual *= x; 
		residual -= rhs; 

		DBBREAK_STR ("Check residual!"); 
	}
#endif
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void MatrixAndOp<ElemType>::CalcSolutionResidual (const MatrixAndOp<ElemType> & rhs, const MatrixAndOp<ElemType> & x, MatrixAndOp<ElemType> &residual) const
	{
		residual = *this;
		residual *= x; 
		residual -= rhs; 
	}



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	ElemType & MatrixAndOp<ElemType>::operator () (USize i, USize j)
	{
		DBASSERT (i<nRow);
		DBASSERT (j<nCol);
		return Mtrx[i][j];
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	const ElemType &  MatrixAndOp<ElemType>::operator () (USize i, USize j) const
	{
		DBASSERT (i<nRow);
		DBASSERT (j<nCol);
		return Mtrx[i][j];
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void MatrixAndOp<ElemType>::BFGS_Update (const MatrixAndOp<ElemType> & Stp, const MatrixAndOp<ElemType> & GrdChng)
	{
		DBASSERT (nRow == nCol);
		DBASSERT (Stp.GetNumCols() == 1); 
		DBASSERT (GrdChng.GetNumCols() == 1); 		
		DBASSERT (Stp.GetNumRows() == nRow); 
		DBASSERT (GrdChng.GetNumRows() == nRow); 

		ElemType nom1 = GetZeroOf (ElemType {});
		ElemType nom2 = GetZeroOf (ElemType {});
		MatrixAndOp<ElemType>  M_Stp (nRow, 1);
		for (USize i = 0; i < nRow; ++i) {
			nom1 += Stp (i, 0) * GrdChng (i, 0); 
			for (USize j = 0; j < nRow; ++j) {
				nom2 += Stp (i, 0) * Mtrx[i][j] * Stp (j, 0); 
				M_Stp (i, 0) += Mtrx[i][j] * Stp (j, 0); 
			}
		}

		DBASSERT (nom1 > 0.0); 
		DBASSERT (nom2 > 0.0); 

		for (USize i = 0; i < nRow; ++i) {
			for (USize j = 0; j < nRow; ++j) {
				Mtrx[i][j] += GrdChng (i, 0) * GrdChng (j, 0) / nom1 - M_Stp (i, 0) * M_Stp (j, 0) / nom2;
			}
		}

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void  MatrixAndOp<ElemType>::Report (const char * matrixName, const char * format) const
	{
		DBPrintf ("\nMatrix '%s':\n", matrixName);
		for (USize i = 0; i < nRow; ++i) {
			DBPrintf ("Row# %d :", i );
			for (USize j = 0; j < nCol; ++j) {
				LinAlg::Report (Mtrx[i][j], format);
				DBPrintf ("\t");
			}
			DBPrintf( "\n" );
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void  MatrixAndOp<ElemType>::ReportDiag (const char * matrixName, const char * format) const
	{
		DBPrintf ("\nDiag of Matrix '%s':\n", matrixName);
		for (USize i = 0; i < nRow && i < nCol; ++i) {
			LinAlg::Report (Mtrx[i][i], format);
			DBPrintf ("\t");
		}
		DBPrintf( "\n" );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType>
	void InnerProduct (const LinAlg::MatrixAndOp<ElemType> & a, const LinAlg::MatrixAndOp<ElemType> & b, LinAlg::MatrixAndOp<ElemType> & res)
	{
		USize m = a.GetNumCols();
		USize n = b.GetNumCols();
		USize l = b.GetNumRows();
		DBASSERT (l == a.GetNumRows());
		res.Reset (m, n); 

		for (USize i = 0; i < m; ++i) {
			for (USize j = 0; j < n; ++j) {
				ElemType tmp = GetZeroOf (tmp);
				for (USize k = 0; k < l; ++k) {
					tmp += a (k,i) * b (k,j);
				}
				res (i, j) = tmp;
			}
		}
	}

} //namespace LinAlg 

#endif //MatrixAndOp_hpp
