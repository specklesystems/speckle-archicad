// *********************************************************************************************************************
// Description:		Integer.hpp
//
// Module:			Modeler
// Contact person:	HK, PP
//
// *********************************************************************************************************************

#ifndef INTEGER_HPP
#define INTEGER_HPP

#pragma once

#include "ThreadLocal.hpp"
#include "GeometricDefinitions.h"
#include "DoubleClassification.hpp"

class SmallObjAllocator;

namespace QXTools {

GEOMETRY_DLL_EXPORT
UInt64	UMul128 (UInt64 a, UInt64 b, UInt64* highRes);

GEOMETRY_DLL_EXPORT
short	GetMostSignificantBitIdx32 (UInt32);

template<typename Int>
class Rational;

template<typename Int>
struct UIntType;

template<>
struct UIntType<Int64>
{
	typedef UInt64 UInt;
};

template<>
struct UIntType<Int32>
{
	typedef UInt32 UInt;
};

template<typename Int>
class Integer;


/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************************************************************/


template<class LeftOp, class RightOp, class Evaluator, class Int>
class BinaryIntOperator;

struct BinaryAdder
{
	template<typename Int>
	static void Evaluate (const Integer<Int> &lOp, const Integer<Int> &rOp, Integer<Int> &result)
	{
		result.CopyLessAdd (lOp, rOp);
	}

	template<typename Int1, typename Int2>
	static void Evaluate (const Integer<Int1> &lOp, const Int2 &rOp, Integer<Int1> &result)
	{
		result.CopyLessAdd (lOp, rOp);
	}

	template<typename Int1, typename Int2>
	static void Evaluate (const Int2 &lOp, const Integer<Int1> &rOp, Integer<Int1> &result)
	{
		result.CopyLessAdd (lOp, rOp);
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int1, class Int2>
	static void Evaluate (const BinaryIntOperator<LeftOp, RightOp, Evaluator, Int2> &lOp, const Int1 &rOp, Integer<Int2> &result)
	{
		lOp.Evaluate (result);
		result += rOp;
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int1, class Int2>
	static void Evaluate (const Int1 &lOp, const BinaryIntOperator<LeftOp, RightOp, Evaluator, Int2> &rOp, Integer<Int2> &result)
	{
		rOp.Evaluate (result);
		result += lOp;
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int>
	static void Evaluate (const Integer<Int> &lOp, const BinaryIntOperator<LeftOp, RightOp, Evaluator, Int> &rOp, Integer<Int> &result)
	{
		rOp.Evaluate (result);
		result += lOp;
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int>
	static void Evaluate (const BinaryIntOperator<LeftOp, RightOp, Evaluator, Int> &lOp, const Integer<Int> &rOp, Integer<Int> &result)
	{
		lOp.Evaluate (result);
		result += rOp;
	}

	template<class LO1, class RO1, class Eval1, class LO2, class RO2, class Eval2, class Int>
	static void Evaluate (const BinaryIntOperator<LO1, RO1, Eval1, Int> &lOp, const BinaryIntOperator<LO2, RO2, Eval2, Int> &rOp, Integer<Int> &result)
	{
		lOp.Evaluate (result);
		Integer<Int> temp;
		rOp.Evaluate (temp);
		result += temp;
	}
};


struct BinarySubtractor
{
	template<typename Int>
	static void Evaluate (const Integer<Int> &lOp, const Integer<Int> &rOp, Integer<Int> &result)
	{
		result.CopyLessSubtract (lOp, rOp);
	}

	template<typename Int1, typename Int2>
	static void Evaluate (const Integer<Int1> &lOp, const Int2 &rOp, Integer<Int1> &result)
	{
		result.CopyLessSubtract (lOp, rOp);
	}

	template<typename Int1, typename Int2>
	static void Evaluate (const Int2 &lOp, const Integer<Int1> &rOp, Integer<Int1> &result)
	{
		result.CopyLessSubtract (lOp, rOp);
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int1, class Int2>
	static void Evaluate (const BinaryIntOperator<LeftOp, RightOp, Evaluator, Int2> &lOp, const Int1 &rOp, Integer<Int2> &result)
	{
		lOp.Evaluate (result);
		result -= rOp;
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int1, class Int2>
	static void Evaluate (const Int1 &lOp, const BinaryIntOperator<LeftOp, RightOp, Evaluator, Int2> &rOp, Integer<Int2> &result)
	{
		Integer<Int2> temp;
		rOp.Evaluate (temp);
		result.CopyLessSubtract (lOp, temp);
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int>
	static void Evaluate (const Integer<Int> &lOp, const BinaryIntOperator<LeftOp, RightOp, Evaluator, Int> &rOp, Integer<Int> &result)
	{
		Integer<Int> temp;
		rOp.Evaluate (temp);
		result.CopyLessSubtract (lOp, temp);
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int>
	static void Evaluate (const BinaryIntOperator<LeftOp, RightOp, Evaluator, Int> &lOp, const Integer<Int> &rOp, Integer<Int> &result)
	{
		lOp.Evaluate (result);
		result -= rOp;
	}

	template<class LO1, class RO1, class Eval1, class LO2, class RO2, class Eval2, class Int>
	static void Evaluate (const BinaryIntOperator<LO1, RO1, Eval1, Int> &lOp, const BinaryIntOperator<LO2, RO2, Eval2, Int> &rOp, Integer<Int> &result)
	{
		lOp.Evaluate (result);
		Integer<Int> temp;
		rOp.Evaluate (temp);
		result -= temp;
	}
};


struct BinaryMultiplier
{
	template<typename Int>
	static void Evaluate (const Integer<Int> &lOp, const Integer<Int> &rOp, Integer<Int> &result)
	{
		result.CopyLessMultiply (lOp, rOp);
	}

	template<typename Int1, typename Int2>
	static void Evaluate (const Integer<Int1> &lOp, const Int2 &rOp, Integer<Int1> &result)
	{
		result.CopyLessMultiply (lOp, rOp);
	}

	template<typename Int1, typename Int2>
	static void Evaluate (const Int2 &lOp, const Integer<Int1> &rOp, Integer<Int1> &result)
	{
		result.CopyLessMultiply (lOp, rOp);
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int1, class Int2>
	static void Evaluate (const BinaryIntOperator<LeftOp, RightOp, Evaluator, Int2> &lOp, const Int1 &rOp, Integer<Int2> &result)
	{
		lOp.Evaluate (result);
		result *= rOp;
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int1, class Int2>
	static void Evaluate (const Int1 &lOp, const BinaryIntOperator<LeftOp, RightOp, Evaluator, Int2> &rOp, Integer<Int2> &result)
	{
		rOp.Evaluate (result);
		result *= lOp;
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int>
	static void Evaluate (const Integer<Int> &lOp, const BinaryIntOperator<LeftOp, RightOp, Evaluator, Int> &rOp, Integer<Int> &result)
	{
		rOp.Evaluate (result);
		result *= lOp;
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int>
	static void Evaluate (const BinaryIntOperator<LeftOp, RightOp, Evaluator, Int> &lOp, const Integer<Int> &rOp, Integer<Int> &result)
	{
		lOp.Evaluate (result);
		result *= rOp;
	}

	template<class LO1, class RO1, class Eval1, class LO2, class RO2, class Eval2, class Int>
	static void Evaluate (const BinaryIntOperator<LO1, RO1, Eval1, Int> &lOp, const BinaryIntOperator<LO2, RO2, Eval2, Int> &rOp, Integer<Int> &result)
	{
		lOp.Evaluate (result);
		Integer<Int> temp;
		rOp.Evaluate (temp);
		result *= temp;
	}
};


struct BinaryDivider
{
	template<typename Int>
	static void Evaluate (const Integer<Int> &lOp, const Integer<Int> &rOp, Integer<Int> &result)
	{
		result.CopyLessDivide (lOp, rOp);
	}

	template<typename Int1, typename Int2>
	static void Evaluate (const Integer<Int1> &lOp, const Int2 &rOp, Integer<Int1> &result)
	{
		result.CopyLessDivide (lOp, rOp);
	}

	template<typename Int1, typename Int2>
	static void Evaluate (const Int2 &lOp, const Integer<Int1> &rOp, Integer<Int1> &result)
	{
		result.CopyLessDivide (lOp, rOp);
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int1, class Int2>
	static void Evaluate (const BinaryIntOperator<LeftOp, RightOp, Evaluator, Int2> &lOp, const Int1 &rOp, Integer<Int2> &result)
	{
		lOp.Evaluate (result);
		result /= rOp;
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int1, class Int2>
	static void Evaluate (const Int1 &lOp, const BinaryIntOperator<LeftOp, RightOp, Evaluator, Int2> &rOp, Integer<Int2> &result)
	{
		Integer<Int2> temp;
		rOp.Evaluate (temp);
		result.CopyLessDivide (lOp, temp);
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int>
	static void Evaluate (const Integer<Int> &lOp, const BinaryIntOperator<LeftOp, RightOp, Evaluator, Int> &rOp, Integer<Int> &result)
	{
		Integer<Int> temp;
		rOp.Evaluate (temp);
		result.CopyLessDivide (lOp, temp);
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int>
	static void Evaluate (const BinaryIntOperator<LeftOp, RightOp, Evaluator, Int> &lOp, const Integer<Int> &rOp, Integer<Int> &result)
	{
		lOp.Evaluate (result);
		result /= rOp;
	}

	template<class LO1, class RO1, class Eval1, class LO2, class RO2, class Eval2, class Int>
	static void Evaluate (const BinaryIntOperator<LO1, RO1, Eval1, Int> &lOp, const BinaryIntOperator<LO2, RO2, Eval2, Int> &rOp, Integer<Int> &result)
	{
		lOp.Evaluate (result);
		Integer<Int> temp;
		rOp.Evaluate (temp);
		result /= temp;
	}
};


template<class LeftOp, class RightOp, class Evaluator, class Int>
class BinaryIntOperator
{
	typedef	Integer<Int>	IntegerInt;

	public:
				BinaryIntOperator (const LeftOp &lOp, const RightOp &rOp) : leftOp (lOp), rightOp (rOp) {}

		void	Evaluate (IntegerInt &result) const
		{
			Evaluator::Evaluate (leftOp, rightOp, result);
		}

		// integer functionality

		IntegerInt GCD (const IntegerInt& op) const
		{
			IntegerInt temp;
			Evaluate (temp);
			return temp.GCD (op);
		}

		bool	IsNegative (void) const
		{
			IntegerInt temp;
			Evaluate (temp);
			return temp.IsNegative ();
		}

		short	Sgn (void) const
		{
			IntegerInt temp;
			Evaluate (temp);
			return temp.Sgn ();
		}

		IntegerInt	Abs (void) const
		{
			IntegerInt temp;
			Evaluate (temp);
			temp.ToAbs ();
			return temp;
		}

		template<class RightOpType>
		short Compare (const RightOpType& op) const
		{
			IntegerInt temp;
			Evaluate (temp);
			return temp.Compare (op);
		}

		template<class RightOpType>
		short CompareAbs (const RightOpType& op) const
		{
			IntegerInt temp;
			Evaluate (temp);
			return temp.CompareAbs (op);
		}

		Int ConvertToInt (void) const
		{
			IntegerInt temp;
			Evaluate (temp);
			return temp.ConvertToInt ();
		}

		double ConvertToDouble (void) const
		{
			IntegerInt temp;
			Evaluate (temp);
			return temp.ConvertToDouble ();
		}

		ULong Width (void) const
		{
			IntegerInt temp;
			Evaluate (temp);
			return temp.Width ();
		}

		// operators

		template<class RightOpType>
		BinaryIntOperator<BinaryIntOperator, RightOpType, BinaryAdder, Int> operator+ (const RightOpType& op) const
		{
			return BinaryIntOperator<BinaryIntOperator, RightOpType, BinaryAdder, Int> (*this, op);
		}

		template<class RightOpType>
		BinaryIntOperator<BinaryIntOperator, RightOpType, BinarySubtractor, Int> operator- (const RightOpType& op) const
		{
			return BinaryIntOperator<BinaryIntOperator, RightOpType, BinarySubtractor, Int> (*this, op);
		}

		template<class RightOpType>
		BinaryIntOperator<BinaryIntOperator, RightOpType, BinaryMultiplier, Int> operator* (const RightOpType& op) const
		{
			return BinaryIntOperator<BinaryIntOperator, RightOpType, BinaryMultiplier, Int> (*this, op);
		}

		template<class RightOpType>
		BinaryIntOperator<BinaryIntOperator, RightOpType, BinaryDivider, Int> operator/ (const RightOpType& op) const
		{
			return BinaryIntOperator<BinaryIntOperator, RightOpType, BinaryDivider, Int> (*this, op);
		}

		bool operator== (const BinaryIntOperator& op) const
		{
			IntegerInt temp, opTemp;
			Evaluate (temp);
			op.Evaluate (opTemp);
			return temp == opTemp;
		}

		bool operator== (const IntegerInt &op) const
		{
			IntegerInt temp;
			Evaluate (temp);
			return temp == op;
		}

		bool operator!= (const BinaryIntOperator& op) const
		{
			IntegerInt temp, opTemp;
			Evaluate (temp);
			op.Evaluate (opTemp);
			return temp != opTemp;
		}

		bool operator!= (const IntegerInt &op) const
		{
			IntegerInt temp;
			Evaluate (temp);
			return temp != op;
		}

		bool operator< (const BinaryIntOperator& op) const
		{
			IntegerInt temp, opTemp;
			Evaluate (temp);
			op.Evaluate (opTemp);
			return temp < opTemp;
		}

		bool operator< (const IntegerInt &op) const
		{
			IntegerInt temp;
			Evaluate (temp);
			return temp < op;
		}

		bool operator> (const BinaryIntOperator& op) const
		{
			IntegerInt temp, opTemp;
			Evaluate (temp);
			op.Evaluate (opTemp);
			return temp > opTemp;
		}

		bool operator> (const IntegerInt &op) const
		{
			IntegerInt temp;
			Evaluate (temp);
			return temp > op;
		}

		bool operator<= (const BinaryIntOperator& op) const
		{
			IntegerInt temp, opTemp;
			Evaluate (temp);
			op.Evaluate (opTemp);
			return temp <= opTemp;
		}

		bool operator<= (const IntegerInt &op) const
		{
			IntegerInt temp;
			Evaluate (temp);
			return temp <= op;
		}

		bool operator>= (const BinaryIntOperator& op) const
		{
			IntegerInt temp, opTemp;
			Evaluate (temp);
			op.Evaluate (opTemp);
			return temp >= opTemp;
		}

		bool operator>= (const IntegerInt &op) const
		{
			IntegerInt temp;
			Evaluate (temp);
			return temp >= op;
		}

	private:
		const LeftOp	&leftOp;
		const RightOp	&rightOp;
};


/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************************************************************/


template<typename Int>
class Integer
{
	friend struct BinaryAdder;
	friend struct BinarySubtractor;
	friend struct BinaryMultiplier;
	friend struct BinaryDivider;
	friend class Rational<Int>;

	typedef typename UIntType<Int>::UInt UInt;

	static const ULong FixWidth = 12;
	static const ULong BaseTypeBitNum = sizeof (Int) * 8;
	static const ULong DigitSize = sizeof (UInt);
	static const UInt  HighBit = UInt (1) << (BaseTypeBitNum - 1);	//lint !e598 [Excessive shift value (precision 2 shifted left by 7)]

	char	fixedDigitsBuffer [FixWidth * sizeof (UInt)];
	UInt*	digits;
	ULong	used;
	bool	negative;

	UInt*	AllocateBuffer (USize) const;
	void	Reallocate (USize, bool);
	void	ReallocateBuffer (USize, bool);
	void	DestroyBuffer (void *);

	bool Valid (ULong) const;
	UInt& Digit (ULong);
	const UInt& Digit (ULong) const;

	void ShortenLength ();

	static UInt UMul (UInt a, UInt b, UInt* highRes);
	static void ShiftLeft (Integer& a, short bitCnt);
	static void ShiftRight (Integer& a);
	static void GCDSubtract (Integer& a, const Integer& b);
	static short GetMostSignificantBitIdx (UInt);

	short	CompareEqLenAbs (const Integer&, ULong) const;

	void	AddAbs (const Integer&, const Integer&);
	void	SubtractAbs (const Integer&, const Integer&);
	void	CopyLessAdd (const Integer &, const Integer &);
	void	CopyLessSubtract (const Integer &, const Integer &);
	void	CopyLessMultiply (const Integer &, const Integer &);
	void	CopyLessDivide (const Integer &, const Integer &);

	Integer (ULong, ULong);

public:
	enum Base {
		B02 =  2,
		B03 =  3,
		B04 =  4,
		B05 =  5,
		B06 =  6,
		B07 =  7,
		B08 =  8,
		B09 =  9,
		B10 = 10,
		B11 = 11,
		B12 = 12,
		B13 = 13,
		B14 = 14,
		B15 = 15,
		B16 = 16
	};

	Integer (Int = 0);
	Integer (const Integer&);
	Integer (Integer&&);
	template<class LeftOp, class RightOp, class Evaluator>
	Integer (const BinaryIntOperator<LeftOp, RightOp, Evaluator, Int> &);
	~Integer ();

	const Integer& operator= (const Integer&);
	const Integer& operator= (Integer&&);
	template<class LeftOp, class RightOp, class Evaluator>
	const Integer& operator= (const BinaryIntOperator<LeftOp, RightOp, Evaluator, Int> &);
	const Integer& operator= (Int);

	bool operator== (const Integer&) const;
	bool operator!= (const Integer&) const;
	bool operator< (const Integer&) const;
	bool operator> (const Integer&) const;
	bool operator<= (const Integer&) const;
	bool operator>= (const Integer&) const;

	Integer operator- () const;

	template<class RightOpType>
	BinaryIntOperator<Integer<Int>, RightOpType, BinaryAdder, Int> operator+ (const RightOpType&) const;
	template<class RightOpType>
	BinaryIntOperator<Integer<Int>, RightOpType, BinarySubtractor, Int> operator- (const RightOpType&) const;
	template<class RightOpType>
	BinaryIntOperator<Integer<Int>, RightOpType, BinaryMultiplier, Int> operator* (const RightOpType&) const;
	template<class RightOpType>
	BinaryIntOperator<Integer<Int>, RightOpType, BinaryDivider, Int> operator/ (const RightOpType&) const;

	const Integer& operator+= (const Integer&);
	const Integer& operator-= (const Integer&);
	const Integer& operator*= (const Integer&);
	const Integer& operator/= (const Integer&);
	void ShiftLeftExpand (ULong bitCnt); //does not lose most significant bits! 

	Integer GCD (const Integer&) const;

	bool	IsNegative () const;
	bool	IsZero () const;
	short	Sgn () const;
	Integer	Abs () const;
	void	ToAbs ();
	void	InvertSign ();

	Integer	Sqrt (void) const;
	Integer	InverseModP (const Integer& p) const;
	Integer	Pow (Integer exp) const;
	Integer	PowModP (Integer exp, const Integer& p) const;
	Int		Log (const Base base = B10) const;
	Integer	Mod (const Integer& p) const;
	void	Mod (const Integer& p);
	
	// setups from a plain string in a given base, no preceeding 0x or anything else are allowed!
	bool	SetupFromString (const char* buff, const USize length, const Base base = B10);
	// does not write trailing 0!
	void	Print (char* buff, const Int buffSize, const Base base = B10, Int* written = nullptr) const;

	short Compare (const Integer&) const;
	short CompareAbs (const Integer&) const;

	void ConvertFromDouble (double);
	Int ConvertToInt () const;
	double ConvertToDouble () const;
	double Frexp (Int64 & exponent) const;
	ULong Width () const;

	void DBDump () const;
};


// SmallObjectAllocator for faster reprezentation

class GEOMETRY_DLL_EXPORT SmallObjAllocatorWrapper {
public:
	SmallObjAllocatorWrapper ();
	~SmallObjAllocatorWrapper ();
		
	void* Allocate (size_t bytes);
	static void Deallocate (void* ptr);

private:
	SmallObjAllocator*	m_allocator;
};

class GEOMETRY_DLL_EXPORT SmallObjAllocatorThreadLocalWrapper
	: public GS::ThreadLocal<SmallObjAllocatorWrapper, GS::ThreadLocal<SmallObjAllocatorWrapper>::DefaultInitializator>
{
public:
	virtual	~SmallObjAllocatorThreadLocalWrapper ();
};

extern GEOMETRY_DLL_EXPORT SmallObjAllocatorThreadLocalWrapper smallObjAllocThreadLocal;


}	// namespace QXTools

#include "IntegerImp.hpp"

#endif
