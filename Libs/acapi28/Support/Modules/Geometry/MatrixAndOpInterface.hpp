// *****************************************************************************
// Geometry, platform-independent
//
// Namespaces:    LinAlg   
// Contact person: AACs
// *****************************************************************************
#ifndef MatrixAndOpInterface_hpp 
#define MatrixAndOpInterface_hpp
#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------
#include "SharedObject.hpp"
#include "GeometricDefinitions.h"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace LinAlg {

	// --- Constant definitions	--------------------------------------------------------------------------------------------

	// --- Type definitions	------------------------------------------------------------------------------------------------

	//Might need to be implemented, these are assumed to be there for the ElemType:
	//const ElemType GetZeroOf ( ElemType & dummy ); 
	//const ElemType GetOneOf ( ElemType & dummy ); 
	//void Report ( ElemType & val, const char * format );

	class ABool  //Aritmetic bool (+ implements OR , * implement AND)
	{
	public: 
		ABool (bool init = false) : val ( init )
		{
		}

		bool Val () const { return val; }
		bool IsTrue () const { return val; }
		bool IsFalse () const { return !val; }

		const ABool & operator += (const ABool & rhs)
		{
			val = val || rhs.val; 
			return *this;
		}

		const ABool & operator -= (const ABool & rhs)
		{
			val = val || !rhs.val; 
			return *this;
		}

		const ABool & operator *= (const ABool & rhs)
		{
			val = val && rhs.val; 
			return *this;
		}

		const ABool & operator /= (const ABool & rhs)
		{
			if (DBVERIFY (rhs.val)) {
				return *this;
			}
			
			throw Geometry::GeometryIllegalArgumentException();
		}

		bool operator < (const ABool & rhs) const
		{
			return !val && rhs.val;
		}

		bool operator > (const ABool & rhs) const
		{
			return val && !rhs.val;
		}

		bool operator == (const ABool & rhs) const
		{
			return val == rhs.val;
		}

		bool operator != (const ABool & rhs) const
		{
			return val != rhs.val;
		}

		const ABool operator - () const
		{
			return ABool (!val); 
		}

	private: 
		bool val; 
	};
} //namespace LinAlg

	GS_FORCE_INLINE LinAlg::ABool operator + (const LinAlg::ABool a, const LinAlg::ABool b) { return a.Val () || b.Val (); }
	GS_FORCE_INLINE LinAlg::ABool operator * (const LinAlg::ABool a, const LinAlg::ABool b) { return a.Val () && b.Val (); }

namespace LinAlg {
	GEOMETRY_DLL_EXPORT const LinAlg::ABool	GetZeroOf ( const LinAlg::ABool & /*dummy*/ );
	GEOMETRY_DLL_EXPORT const LinAlg::ABool	GetOneOf ( const LinAlg::ABool & /*dummy*/ );
	GEOMETRY_DLL_EXPORT void Report (const LinAlg::ABool & val, const char * format );

	GEOMETRY_DLL_EXPORT double	GetZeroOf ( const double & /*dummy*/ );
	GEOMETRY_DLL_EXPORT double	GetOneOf ( const double & /*dummy*/ );
	GEOMETRY_DLL_EXPORT void	Simplify (double & /*val*/);
	GEOMETRY_DLL_EXPORT void	Report ( const double & val, const char * format );

	template<typename ElemType>
	bool IsZero (const ElemType & val) { return val == GetZeroOf (val); }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class ElemType>
	class MatrixEntryIterator //can be row or column iterator, this is just an interface!
		: public GS::SharedObject
	{
	public:
		virtual ~MatrixEntryIterator () {} 

		virtual bool IsAtEnd () const = 0; 
		virtual MatrixEntryIterator& operator ++ () = 0;		//to the next entry
		virtual USize GetRowIndex () const = 0;
		virtual USize GetColIndex () const = 0;
		virtual ElemType & GetValue () = 0; 
		virtual const ElemType & GetValue () const = 0; 
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class ElemType, class MatrixType>	
	class MatrixAndOpInterface 
	{
	public:

		//get the size:
		virtual USize GetNumRows () const = 0;
		virtual USize GetNumCols () const = 0;

		//Iterators, these are not efficient, they do mem allocation!: 
		virtual GS::SharedPtr<MatrixEntryIterator<ElemType> > GetRowIterator (const USize rowIndex) = 0;	
		virtual GS::SharedPtr<MatrixEntryIterator<ElemType> > GetRowIterator (const USize rowIndex, const USize colIndex) = 0;
		virtual GS::SharedPtr<MatrixEntryIterator<ElemType> > GetColIterator (const USize colIndex) = 0;
		virtual GS::SharedPtr<MatrixEntryIterator<ElemType> > GetColIterator (const USize rowIndex, const USize colIndex) = 0;

		//operators:
		virtual void Reset (USize m, USize n) = 0;
		virtual void SetUnit () = 0;
		virtual MatrixType & operator = (const MatrixType &rhs) = 0; 
		virtual MatrixType & operator += (const MatrixType &rhs) = 0;
		virtual MatrixType & operator -= (const MatrixType &rhs) = 0;
		virtual MatrixType & operator *= (const MatrixType &rhs) = 0;
		virtual MatrixType & operator *= (const ElemType &rhs) = 0;


		//block operations, the target is always this object!
		virtual void CopyBlock (
			const MatrixType & src, 
			USize src_i, USize src_j, 
			USize trg_i, USize trg_j,
			USize blckRows, USize blckCols  //this is the block's size
			) = 0;

		virtual void AddBlock (
			const MatrixType & src, 
			USize src_i, USize src_j, 
			USize trg_i, USize trg_j,
			USize blckRows, USize blckCols  //this is the block's size
			) = 0;

		virtual void SubBlock (
			const MatrixType & src, 
			USize src_i, USize src_j, 
			USize trg_i, USize trg_j,
			USize blckRows, USize blckCols  //this is the block's size
			) = 0;

		virtual void MultBlock (
			const MatrixType & src, 
			USize src_i, USize src_j, 
			USize trg_i, USize trg_j,
			USize blckSize  //Only quadratic is possible!
			) = 0;

		virtual void SetBlockZero (
			USize trg_i, USize trg_j,
			USize blckRows, USize blckCols 
			) = 0;
		//Norms: 
		virtual ElemType GetAbsMaxValue () const = 0; 
		virtual ElemType FrobeniusSqr () const = 0;

		//swaps: 
		virtual void SwapRows (USize r1, USize r2) = 0;
		virtual void SwapCols (USize c1, USize c2) = 0;
		virtual void Transpose () = 0;

		//Solve: 
		virtual bool SolveUTR (const MatrixType & rhs, MatrixType & x) const = 0;  //matrix is Upper Triangular already!
#ifdef DEBUVERS
		virtual void CheckSolution (const MatrixType & rhs, MatrixType & x) const = 0;
#endif

		//access by elements: 
		virtual ElemType & operator () (USize i, USize j) = 0;
		virtual const ElemType & operator () (USize i, USize j) const = 0;

		//debug
		virtual void Check () const {}
		virtual void Report (const char * matrixName, const char * format = "%5.5lf") const = 0;
		virtual void ReportDiag (const char * matrixName, const char * format = "%5.5lf") const = 0;
	};

	// --- Variable declarations -------------------------------------------------------------------------------------------

	// --- Function declarations -------------------------------------------------------------------------------------------


} //namespace LinAlg

#endif //MatrixAndOpInterface_hpp
