// *****************************************************************************
// Matrix class with fixed buffer.
//
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          FGY
//
// SG compatible
// *****************************************************************************
#if !defined (MATRIX_HPP)
#define MATRIX_HPP

#pragma once

#include "GSRoot.hpp"
#include "Array.hpp"
#include "Real.hpp"

namespace Geometry {

// =============================================================================
//
// The Matrix class
//
// =============================================================================

	template<USize RowCount, USize ColumnCount, class ElementType> class Matrix;

	template<USize RowCount, USize ColumnCount, class ElementType>
	struct TemporaryMatrixCalcObject {
		enum OpCode { Add, Subtract, Multiply, Invert, ScalarMultiply};

		const Matrix<RowCount, ColumnCount, ElementType>*				operand1;
		const Matrix<RowCount, ColumnCount, ElementType>*				operand2;
		const ElementType*		scalar;
		OpCode	opCode;
	};

	template<USize RowCount, USize ColumnCount, class ElementType>
	class Matrix
	{
		public:
			enum Type {
				Undetermined	= 0,
				GeneralMatrix	= 1,
				ZeroMatrix		= 2,
				UnitMatrix		= 3,
				ZeroDeterminant	= 4,
				UnitDeterminant	= 5
			};

			typedef		ElementType		ElemType;
			class Row {
				private:
					Matrix<RowCount, ColumnCount, ElementType>&	matrix;
					UIndex rowNum;

				public:
					Row (Matrix<RowCount, ColumnCount, ElementType>& matrix, UIndex rowNum) : matrix (matrix), rowNum(rowNum) {}
					Row (const Row& source) : matrix (source.matrix), rowNum(source.rowNum) {}

					Row& operator= (const Row& source) { rowNum = source.rowNum; &matrix = &source.matrix; return *this; };

					ElementType& operator[] (UIndex idx) { return matrix(rowNum, idx); }
					const ElementType& operator[] (UIndex idx) const { return matrix(rowNum, idx); }
			};

			class ConstRow {
				private:
					const Matrix<RowCount, ColumnCount, ElementType>&	matrix;
					UIndex rowNum;

				public:
					ConstRow (const Matrix<RowCount, ColumnCount, ElementType>& matrix, UIndex rowNum) : matrix (matrix), rowNum(rowNum) {}
					ConstRow (const ConstRow& source) : matrix (source.matrix), rowNum(source.rowNum) {}

					ConstRow& operator= (const ConstRow& source) { rowNum = source.rowNum; &matrix = &source.matrix; return *this; };

					const ElementType& operator[] (UIndex idx) const { return matrix(rowNum, idx); }
			};

		private:
			char		type;
			char		reserved1;
			short		reserved2;

			ElementType storage[RowCount][ColumnCount];

			inline void			CalculateType (void);

		public:
			inline Matrix (void);
			inline Matrix (const Matrix& source);
			inline ~Matrix (void);

			inline Matrix (Type type);

			inline Matrix&		operator= (const Matrix& source);
			inline Matrix<RowCount, ColumnCount, ElementType>&		operator= (const TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType>& source);

			inline ElemType&	operator() (UIndex i, UIndex j);
			inline const ElemType&	operator() (UIndex i, UIndex j) const;

			Row operator[] (UIndex idx) { return Row (*this, idx); }
			ConstRow operator[] (UIndex idx) const { return ConstRow (*this, idx); }

			inline USize										GetRowCount (void) const;
			inline USize										GetColumnCount (void) const;
			inline Type											GetType () const;

			inline ElementType									Get (UIndex i, UIndex j) const;
			inline void											Set (UIndex i, UIndex j, const ElemType& x);

			inline Matrix<ColumnCount, RowCount, ElementType>	Transpose (void) const;
	};

// =============================================================================
//
// Overloaded matrix operations
//
// =============================================================================

	template<USize RowCount, USize ColumnCount, class ElementType>
	inline TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType> operator+ (const Matrix<RowCount, ColumnCount, ElementType>& a, const Matrix<RowCount, ColumnCount, ElementType>& b);

	template<USize RowCount, USize ColumnCount, class ElementType>
	inline TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType> operator- (const Matrix<RowCount, ColumnCount, ElementType>& a, const Matrix<RowCount, ColumnCount, ElementType>& b);

	template<USize RowCount, USize ColumnCount, class ElementType>
	inline TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType> operator* (const Matrix<RowCount, ColumnCount, ElementType>& a, const Matrix<RowCount, ColumnCount, ElementType>& b);

	template<USize RowCount, USize ColumnCount, class ElementType>
	inline TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType> operator~ (const Matrix<RowCount, ColumnCount, ElementType>& operand);

	template<USize RowCount, USize ColumnCount, class ElementType>
	inline TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType> operator* (const ElementType& scale, const Matrix<RowCount, ColumnCount, ElementType>& operand);


// =============================================================================
//
// Matrix operations as functions
//
// =============================================================================

	template<USize RowCount, USize ColumnCount, class ElementType>
	void Add (Matrix<RowCount, ColumnCount, ElementType>* result, const Matrix<RowCount, ColumnCount, ElementType>& operand1, const Matrix<RowCount, ColumnCount, ElementType>& operand2);

	template<USize RowCount, USize ColumnCount, class ElementType>
	void Subtract (Matrix<RowCount, ColumnCount, ElementType>* result, const Matrix<RowCount, ColumnCount, ElementType>& operand1, const Matrix<RowCount, ColumnCount, ElementType>& operand2);

	template<USize RowCount, USize ColumnCount, class ElementType>
	void UnaryMinus (Matrix<RowCount, ColumnCount, ElementType>* result, const Matrix<RowCount, ColumnCount, ElementType>& operand);

	template<USize RowCount, USize ColumnCount, class ElementType>
	void Multiply (Matrix<RowCount, ColumnCount, ElementType>* result, const Matrix<RowCount, ColumnCount, ElementType>& operand1, const Matrix<RowCount, ColumnCount, ElementType>& operand2);

	enum InvertResult { SingularMatrix, NonSingularMatrix };
	template<USize RowCount, USize ColumnCount, class ElementType>
	InvertResult Invert (Matrix<RowCount, ColumnCount, ElementType>* result, const Matrix<RowCount, ColumnCount, ElementType>& operand);

	template<USize RowCount, USize ColumnCount, class ElementType>
	void ScalarMultiply (Matrix<RowCount, ColumnCount, ElementType>* result, const ElementType&, const Matrix<RowCount, ColumnCount, ElementType>& operand);


	template<USize RowCount, USize ColumnCount, class ElementType>
	void Evaluate (Matrix<RowCount, ColumnCount, ElementType>* result, const TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType>& source);



// =============================================================================
//
// The main Matrix class implementation
//
// =============================================================================


	template<USize RowCount, USize ColumnCount, class ElementType>
	inline Matrix<RowCount, ColumnCount, ElementType>::Matrix (void) : type (Undetermined), reserved1 (0), reserved2 (0)
	{
		for (UIndex i = 0; i < RowCount; i++) {
			for (UIndex j = 0; j < ColumnCount; j++) {
				storage[i][j] = ElementType();
			}
		}
	}

	template<USize RowCount, USize ColumnCount, class ElementType>
	inline Matrix<RowCount, ColumnCount, ElementType>::Matrix (const Matrix<RowCount, ColumnCount, ElementType>& source)
	: type (source.type), reserved1 (source.reserved1), reserved2 (source.reserved2)
	{
		for (UIndex i = 0; i < RowCount; i++) {
			for (UIndex j = 0; j < ColumnCount; j++) {
				storage[i][j] = source.storage[i][j];
			}
		}
	}

	template<USize RowCount, USize ColumnCount, class ElementType>
	Matrix<RowCount, ColumnCount, ElementType>::Matrix (Type type) : type (0), reserved1 (0), reserved2 (0)
	{
		if (type == ZeroMatrix || type == UnitMatrix) {
				for (UIndex i = 0; i < RowCount; i++) {
					for (UIndex j = 0; j < ColumnCount; j++) {
						storage[i][j] = ElementType();
					}
				}

			if (type == UnitMatrix)	{
				UIndex count = RowCount < ColumnCount ? RowCount : ColumnCount;
				for (UIndex i = 0; i < count; i++) {
					storage[i][i] = ElementType(1.0);
				}
			}
		}
		 else
			DBBREAK();

	}

	template<USize RowCount, USize ColumnCount, class ElementType>
	Matrix<RowCount, ColumnCount, ElementType>::~Matrix (void)
	{
	}

	template<USize RowCount, USize ColumnCount, class ElementType>
	Matrix<RowCount, ColumnCount, ElementType>& Matrix<RowCount, ColumnCount, ElementType>::operator= (const TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType>& source)
	{
		Evaluate (this, source);
		return *this;
	}


	template<USize RowCount, USize ColumnCount, class ElementType>
	Matrix<RowCount, ColumnCount, ElementType>& Matrix<RowCount, ColumnCount, ElementType>::operator= (const Matrix& source)
	{
		for (UIndex i = 0; i < RowCount; i++) {
			for (UIndex j = 0; j < ColumnCount; j++) {
				storage[i][j] = source.storage[i][j];
			}
		}
		return *this;
	}

	template<USize RowCount, USize ColumnCount, class ElementType>
	ElementType& Matrix<RowCount, ColumnCount, ElementType>::operator() (UIndex i, UIndex j)
	{
		return storage[i][j];
	}

	template<USize RowCount, USize ColumnCount, class ElementType>
	const ElementType& Matrix<RowCount, ColumnCount, ElementType>::operator() (UIndex i, UIndex j) const
	{
		return storage[i][j];
	}

	template<USize RowCount, USize ColumnCount, class ElementType>
	USize Matrix<RowCount, ColumnCount, ElementType>::GetRowCount (void) const
	{
		return RowCount;
	}

	template<USize RowCount, USize ColumnCount, class ElementType>
	USize Matrix<RowCount, ColumnCount, ElementType>::GetColumnCount (void) const
	{
		return ColumnCount;
	}


	template<USize RowCount, USize ColumnCount, class ElementType>
	typename Matrix<RowCount, ColumnCount, ElementType>::Type Matrix<RowCount, ColumnCount, ElementType>::GetType (void) const
	{
		if (type == Undetermined) {
			CalculateType ();
		}
		return type;
	}


	template<USize RowCount, USize ColumnCount, class ElementType>
	void Matrix<RowCount, ColumnCount, ElementType>::Set (UIndex i, UIndex j, const ElemType& x)
	{
		storage[i][j] = x;
	}

	template<USize RowCount, USize ColumnCount, class ElementType>
	ElementType Matrix<RowCount, ColumnCount, ElementType>::Get (UIndex i, UIndex j) const
	{
		return storage[i][j];
	}


	template<USize RowCount, USize ColumnCount, class ElementType>
	Matrix<ColumnCount, RowCount, ElementType> Matrix<RowCount, ColumnCount, ElementType>::Transpose (void) const
	{
		Matrix<ColumnCount, RowCount, ElementType> result;

		for (UIndex i = 0; i < RowCount; ++i) {
			for (UIndex j = 0; j < ColumnCount; ++j) {
				result.Set (j, i, storage[i][j]);
			}
		}

		return result;
	}

// =============================================================================
//
// Overloaded matrix operations implementation
//
// =============================================================================

	template<USize RowCount, USize ColumnCount, class ElementType>
	inline TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType> operator+ (const Matrix<RowCount, ColumnCount, ElementType>& a, const Matrix<RowCount, ColumnCount, ElementType>& b)
	{
		TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType>	result;

		result.opCode = TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType>::Add;
		result.operand1 = &a;
		result.operand2 = &b;

		return result;
	}

	template<USize RowCount, USize ColumnCount, class ElementType>
	inline TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType> operator- (const Matrix<RowCount, ColumnCount, ElementType>& a, const Matrix<RowCount, ColumnCount, ElementType>& b)
	{
		TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType>	result;

		result.opCode = TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType>::Subtract;
		result.operand1 = &a;
		result.operand2 = &b;

		return result;
	}


	template<USize RowCount, USize ColumnCount, class ElementType>
	inline TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType> operator* (const Matrix<RowCount, ColumnCount, ElementType>& a, const Matrix<RowCount, ColumnCount, ElementType>& b)
	{
		TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType>	result;

		result.opCode = TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType>::Multiply;
		result.operand1 = &a;
		result.operand2 = &b;

		return result;
	}


	template<USize RowCount, USize ColumnCount, class ElementType>
	inline TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType> operator~ (const Matrix<RowCount, ColumnCount, ElementType>& operand)
	{
		TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType>	result;

		result.opCode = TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType>::Invert;
		result.operand1 = &operand;
		result.operand2 = nullptr;

		return result;
	}

	template<USize RowCount, USize ColumnCount, class ElementType>
	inline TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType> operator* (const ElementType& scalar, const Matrix<RowCount, ColumnCount, ElementType>& b)
	{
		TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType>	result;

		result.opCode = TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType>::ScalarMultiply;
		result.scalar = &scalar;
		result.operand2 = &b;

		return result;
	}


// =============================================================================
//
// Matrix operations as functions implementation (all can receive the same object in the different parameters)
//
// =============================================================================

	template<USize RowCount, USize ColumnCount, class ElementType>
	void Add (Matrix<RowCount, ColumnCount, ElementType>* result, const Matrix<RowCount, ColumnCount, ElementType>& a, const Matrix<RowCount, ColumnCount, ElementType>& b)
	{
		for (UIndex i = 0; i < RowCount; i++) {
			for (UIndex j = 0; j < ColumnCount; j++) {
				(*result)[i][j] = a[i][j] + b[i][j];
			}
		}
	}

	template<USize RowCount, USize ColumnCount, class ElementType>
	void Subtract (Matrix<RowCount, ColumnCount, ElementType>* result, const Matrix<RowCount, ColumnCount, ElementType>& a, const Matrix<RowCount, ColumnCount, ElementType>& b)
	{
		for (UIndex i = 0; i < RowCount; i++) {
			for (UIndex j = 0; j < ColumnCount; j++) {
				(*result)[i][j] = a[i][j] - b[i][j];
			}
		}
	}

	template<USize RowCount, USize ColumnCount, class ElementType>
	void Multiply (Matrix<RowCount, ColumnCount, ElementType>* resultOut, const Matrix<RowCount, ColumnCount, ElementType>& a, const Matrix<RowCount, ColumnCount, ElementType>& b)
	{
		Matrix<RowCount, ColumnCount, ElementType>*	result = resultOut;
		if (&a == result || &b == resultOut) {
			result = new Matrix<RowCount, ColumnCount, ElementType>;
		}

		USize	firstRowNum		= a.GetRowCount ();
		USize	rowColumnNum	= a.GetColumnCount ();
		USize	secondColumnNum	= b.GetColumnCount ();

		if (a.GetColumnCount () != b.GetRowCount ()) {
			throw GeometryIllegalArgumentException ("Matrix row - column mismatch in Multiply.", __FILE__, __LINE__);
		}

		for (UIndex i = 0; i < firstRowNum; i++) {
			for (UIndex j = 0; j < secondColumnNum; j++) {

				ElementType sum {};

				for (UIndex sumIdx = 0; sumIdx < rowColumnNum; sumIdx++) {
					sum += a[i][sumIdx] * b[sumIdx][j];
				}
				(*result)[i][j] = sum;
			}
		}
		if (result != resultOut) {
			*resultOut = *result;
			delete result;
		}
	}

	template<USize RowCount, USize ColumnCount, class ElementType>
	void UnaryMinus (Matrix<RowCount, ColumnCount, ElementType>* result, const Matrix<RowCount, ColumnCount, ElementType>& operand)
	{
		for (UIndex i = 0; i < RowCount; i++) {
			for (UIndex j = 0; j < ColumnCount; j++) {
				(*result)[i][j] = -operand[i][j];
			}
		}
	}


	template<USize RowCount, USize ColumnCount, class ElementType>
	InvertResult Invert (Matrix<RowCount, ColumnCount, ElementType>* result, const Matrix<RowCount, ColumnCount, ElementType>& operand)
	{
		typedef	typename Matrix<RowCount, ColumnCount, ElementType>::ElemType ElemType;
		const ElemType ZeroElem = ElemType ();
		const ElemType UnitElem = ElemType (1.0);

		USize	rowNum = (*result).GetRowCount ();
		USize	columnNum = (*result).GetColumnCount ();
		if (rowNum != columnNum) {
			throw GeometryIllegalArgumentException (
				"Matrix row - column inequal in Invert.", __FILE__, __LINE__);
		}

		UIndex				i, ii, j, k, l;
		GS::Array<ElemType>	firstMatrix;
		GS::Array<UIndex>	cols;
		GS::Array<ElemType>	x;
		ElemType			*xj, *xRaw;
		ElemType			p, ab;

		firstMatrix.SetSize (rowNum * columnNum);
		cols.SetSize (rowNum);
		x.SetSize (rowNum);
		xRaw = x.GetContent ();


		// copy operand into the modifiable table
		for (i = 0; i < rowNum; i++) {
			for (j = 0; j < columnNum; j++) {
				firstMatrix[i * columnNum + j] = operand[i][j];
			}
		}

		// make the result to be a unit-matrix
		for (i = 0; i < rowNum; i++) {
			for (j = 0; j < columnNum; j++) {
				if (i == j)
					(*result)[i][j] = UnitElem;
				else
					(*result)[i][j] = ZeroElem;
			}
		}

		for (i = 0; i < rowNum; i++) {
			p = ZeroElem;
			k = 0;
			bool isFoundNonZero = false;
			// find the maximal abs value in the row
			for (j = 0; j < columnNum; j++) {
				ab = Abs (firstMatrix[i * columnNum + j]);
				if (IsGreater (ab, p)) {
					isFoundNonZero = true;
					p = ab;
					k = j;
				}
			}
			// if all the row is zero then singular matrix => error
			if (!isFoundNonZero) {
				return SingularMatrix;
			}
			cols[i] = k;

			// divide the first and second matrix in the actual row
			// with the maximal element
			p = UnitElem / firstMatrix[i * columnNum + k];
			for (j = 0; j < columnNum; j++)
				firstMatrix[i * columnNum + j] *= p;
			for (l = 0; l < columnNum; l++)
				(*result)[i][l] = (*result)[i][l] * p;

			// divide all other rows too
			for (ii = 0; ii < rowNum; ii++) {
				p = firstMatrix[ii * columnNum + k];
				if (ii != i && IsGreater (Abs (p), ZeroElem)) {
					for (j = 0; j < columnNum; j++)
						firstMatrix[ii * columnNum + j] -= p * firstMatrix[i * columnNum + j];
					for (l = 0; l < columnNum; l++)
						(*result)[ii][l] = (*result)[ii][l] - p * (*result)[i][l];
				}
			}
		}
		for (l = 0; l < rowNum; l++) {
			for (i = 0, xj = xRaw; i < rowNum; i++, xj++)
				*xj = ZeroElem;
			for (Int32 ii = rowNum-1; ii >= 0; ii--) {	/*mm-bck*/
				p = (*result)[ii][l];
				for (j = 0, xj = xRaw; j < rowNum; j++, xj++)
					p -= firstMatrix[ii * columnNum + j] * *xj;
				*(xRaw + cols[ii]) = p;
			}
			for (i = 0; i < rowNum; i++)
				(*result)[i][l] = *(xRaw + i);
		}
		return NonSingularMatrix;
	}

	template<USize RowCount, USize ColumnCount, class ElementType>
	void ScalarMultiply (Matrix<RowCount, ColumnCount, ElementType>* result, const ElementType& scalar, const Matrix<RowCount, ColumnCount, ElementType>& b)
	{
		for (UIndex i = 0; i < RowCount; i++) {
			for (UIndex j = 0; j < ColumnCount; j++) {
				(*result)[i][j] = scalar * b[i][j];
			}
		}
	}

	template<USize RowCount, USize ColumnCount, class ElementType>
	void Evaluate (Matrix<RowCount, ColumnCount, ElementType>* result, const TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType>& source)
	{
		switch (source.opCode) {
		case TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType>::Add:
			Add (result, *source.operand1, *source.operand2);
			break;

		case TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType>::Subtract:
			Subtract (result, *source.operand1, *source.operand2);
			break;

		case TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType>::Multiply:
			Multiply (result, *source.operand1, *source.operand2);
			break;

		case TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType>::Invert: {
				InvertResult resultType = Invert (result, *source.operand1);
				if (resultType == SingularMatrix)
					throw GeometryIllegalArgumentException (
										"Matrix is singular in Invert.", __FILE__, __LINE__);
			}
			break;

		case TemporaryMatrixCalcObject<RowCount, ColumnCount, ElementType>::ScalarMultiply:
			ScalarMultiply (result, *source.scalar, *source.operand2);
			break;
		}
	}

	typedef Matrix<4, 4, double> Matrix44d;

} // namespace Geometry


#endif
