// *********************************************************************************************************************
// Description:		IntegerImp.hpp
//
// Module:			Modeler
// Contact person:	HK, PP
//
// *********************************************************************************************************************

#ifndef	INTEGERIMP_HPP
#define	INTEGERIMP_HPP

#include <math.h> // floor
#include <float.h>
#include "BaseAlgorithms.hpp"

namespace QXTools {

template<typename Int>
GS_FORCE_INLINE typename Integer<Int>::UInt*	Integer<Int>::AllocateBuffer (USize digitCnt) const
{
	return static_cast<UInt *> (smallObjAllocThreadLocal.Get ().Allocate (DigitSize * digitCnt));
}

template<typename Int>
GS_FORCE_INLINE void	Integer<Int>::Reallocate (USize newSize, bool copy)
{
	if (newSize <= FixWidth || newSize <= used)
		return;

	ReallocateBuffer (newSize, copy);
}

template<typename Int>
void	Integer<Int>::ReallocateBuffer (USize newSize, bool copy)
{
	UInt* oldDigits = digits;
	digits = AllocateBuffer (newSize);

	if (copy)
		memcpy (digits, oldDigits, DigitSize * used);

	if (oldDigits != reinterpret_cast<UInt*> (fixedDigitsBuffer))
		DestroyBuffer (oldDigits);
}

template<typename Int>
GS_FORCE_INLINE void	Integer<Int>::DestroyBuffer (void *buffer)
{
	smallObjAllocThreadLocal.Get ().Deallocate (buffer);
}

template<typename Int>
GS_FORCE_INLINE bool Integer<Int>::Valid (ULong i) const
{
	return i < used;
}

template<typename Int>
GS_FORCE_INLINE typename Integer<Int>::UInt& Integer<Int>::Digit (ULong i)
{
	return digits[i];
}

template<typename Int>
GS_FORCE_INLINE const typename Integer<Int>::UInt& Integer<Int>::Digit (ULong i) const
{
	return digits[i];
}

template<typename Int>
void Integer<Int>::ShortenLength ()
{
	while (used > 1) {
		if (Digit (used - 1) == 0)
			used--;
		else
			break;
	}
}

template<typename Int>
GS_FORCE_INLINE bool Integer<Int>::IsZero () const
{
	return used == 1 && digits[0] == 0;
}

template<>
GS_FORCE_INLINE UInt64 Integer<Int64>::UMul (UInt64 a, UInt64 b, UInt64* highRes)
{
	return UInt64 (UMul128 (a, b, highRes));
}

template<>
GS_FORCE_INLINE UInt32 Integer<Int32>::UMul (UInt32 a, UInt32 b, UInt32* highRes)
{
	UInt64 res = UInt64 (a) * UInt64 (b);
	*highRes = UInt32 (res >> 32);
	return UInt32 (res);
}

template<typename Int>
void Integer<Int>::ShiftLeft (Integer& a, short bitCnt)
{
	if (bitCnt == 0)
		return;

	short rightShiftCnt = BaseTypeBitNum - bitCnt;
	ULong currIdx = a.used - 1;
	a.Digit (currIdx) <<= bitCnt;

	for (; currIdx > 0; --currIdx) {
		UInt &nextDigit = a.Digit (currIdx - 1);
		a.Digit (currIdx) |= nextDigit >> rightShiftCnt;
		nextDigit <<= bitCnt;
	}
}

template<typename Int>
void Integer<Int>::ShiftLeftExpand (ULong bitCnt)
{
	ULong shiftDigits = bitCnt / BaseTypeBitNum;
	short shiftBits = static_cast <short> (bitCnt - shiftDigits * BaseTypeBitNum);

	Reallocate (used + shiftDigits + 1, true);
	if (shiftDigits > 0) {
		for (ULong i = 1; i <= used; ++i) {
			Digit (used + shiftDigits - i) = Digit (used - i);
		}
		//coming in zeros from the right:
		for (ULong i = 0; i < shiftDigits; ++i) {
			Digit (i) = 0;
		}
	}

	Digit (used + shiftDigits) = 0;
	used += shiftDigits + 1;

	ShiftLeft (*this, shiftBits);
	ShortenLength ();
}

template<typename Int>
void Integer<Int>::ShiftRight (Integer& a)
{
	ULong i = 0;
	for (;;) {
		a.Digit (i) >>= 1;
		i++;
		if (!a.Valid (i))
			break;
		if (a.Digit (i) & 1)
			a.Digit (i-1) |= HighBit;
	}
}

template<typename Int>
void Integer<Int>::GCDSubtract (Integer& a, const Integer& b)
{
	bool overflow = false, temp;
	ULong idx = 0, lastDigit = a.used - 1;
	for (;;) {
		temp = a.Digit (idx) < b.Digit (idx);
		bool eq = a.Digit (idx) == b.Digit (idx);
		a.Digit (idx) -= b.Digit (idx);

		if (overflow)
			a.Digit (idx)--;

		if (idx == lastDigit)
			break;

		overflow = temp || eq && overflow;
		idx++;
	}
}

template<>
GS_FORCE_INLINE  short Integer<Int32>::GetMostSignificantBitIdx (UInt digit)
{
	static_assert (BaseTypeBitNum == 32, "baseTypeSizeAssert");

	return GetMostSignificantBitIdx32 (digit);
}

template<>
GS_FORCE_INLINE  short Integer<Int64>::GetMostSignificantBitIdx (UInt digit)
{
	static_assert (BaseTypeBitNum == 64, "baseTypeSizeAssert");

	short retVal = 0;

	UInt32 x = (UInt32) (UInt64 (digit) >> 32);
	if (x == 0)
		x = (UInt32) digit;
	else
		retVal = 32;

	return retVal + GetMostSignificantBitIdx32 (x);
}

template<typename Int>
void Integer<Int>::AddAbs (const Integer& a, const Integer& b)
{
	// this pointer can be either a or b

	const Integer *a2, *b2;
	if (a.used >= b.used) {
		a2 = &a;
		b2 = &b;
	} else {
		a2 = &b;
		b2 = &a;
	}

	ULong a2Used = a2->used, b2Used = b2->used, max = GS::Max (a.used, b.used), i;
	Reallocate (max + 1, true);
	used = max;
	digits[used] = 0;

	bool carryIn = false;
	for (i = 0; i < b2Used; i++) {
		UInt temp = a2->digits[i] + b2->digits[i];
		bool carryOut = (temp < a2->digits[i]);

		if (carryIn) {
			temp++;
			carryOut |= (temp == 0);
		}

		digits[i] = temp;
		carryIn = carryOut;
	}

	for (; i < a2Used && carryIn; i++) {
		UInt temp = a2->digits[i] + 1;
		carryIn = (temp == 0);
		digits[i] = temp;
	}

	for (; i < a2Used; i++)
		digits[i] = a2->digits[i];

	if (carryIn)
		digits[used++] = 1;
}

template<typename Int>
void Integer<Int>::SubtractAbs (const Integer& a, const Integer& b)
{
	// a SHOULD BE greater or equal than b
	// this pointer can be either a or b

	ULong aUsed = a.used, bUsed = b.used, i;
	Reallocate (aUsed, true);
	used = aUsed;

	bool borrowIn = false;
	for (i = 0; i < bUsed; i++) {
		UInt temp = a.digits[i] - b.digits[i];
		bool borrowOut = (temp > a.digits[i]);

		if (borrowIn) {
			borrowOut |= (temp == 0);
			temp--;
		}

		digits[i] = temp;
		borrowIn = borrowOut;
	}

	for (; i < aUsed && borrowIn; i++) {
		borrowIn = (a.digits[i] == 0);
		digits[i] = a.digits[i] - 1;
	}

	if (borrowIn) {
		// I told you "a SHOULD BE greater or equal than b"...
		throw GS::Exception (nullptr, __FILE__, __LINE__);
	} else
		for (; i < aUsed; i++)
			digits[i] = a.digits[i];

	ShortenLength ();
}

template<typename Int>
void Integer<Int>::CopyLessAdd (const Integer &a, const Integer &b)
{
	// no need to check if this == &a or &b

	if (a.negative == b.negative) {
		AddAbs (a, b);
		negative = a.negative;
	} else {
		bool absSmaller = a.CompareAbs (b) < 0;
		if (absSmaller)
			SubtractAbs (b, a);
		else
			SubtractAbs (a, b);

		negative = IsZero () ? false : a.negative ? !absSmaller : absSmaller;
	}
}

template<typename Int>
void Integer<Int>::CopyLessSubtract (const Integer &a, const Integer &b)
{
	// no need to check if this == &a or &b

	if (a.negative == b.negative) {
		bool absSmaller = a.CompareAbs (b) < 0;
		if (absSmaller)
			SubtractAbs (b, a);
		else
			SubtractAbs (a, b);

		negative = IsZero () ? false : a.negative ? !absSmaller : absSmaller;
	} else {
		AddAbs (a, b);
		negative = a.negative;
	}
}

template<typename Int>
void Integer<Int>::CopyLessMultiply (const Integer &a, const Integer &b)
{
	// no need to check if this == &a or &b while CopyLessMultiply is a private function and nobody else calls,
	// inner calling does not trigger this kind of situation (this == &a or &b)

	if (b.used == 1) {
		if (b.digits[0] == 1) {
			*this = a;
			if (a.negative == b.negative)
				negative = false;
			else
				negative = IsZero () ? false : true;
			return;
		} else if (b.digits[0] == 0) {
			*this = 0;
			return;
		}
	}
	if (a.used == 1) {
		if (a.digits[0] == 1) {
			*this = b;
			if (a.negative == b.negative)
				negative = false;
			else
				negative = IsZero () ? false : true;
			return;
		} else if (a.digits[0] == 0) {
			*this = 0;
			return;
		}
	}

	ULong cnt = a.used + b.used, switchCode = cnt < 5 ? (a.used << 2) + b.used : 0;
	Reallocate (cnt, false);
	used = cnt;

	switch (switchCode) {
		case 5: // a.used == 1, b.used == 1
		{
			digits[0] = UMul (a.digits[0], b.digits[0], &digits[1]);
			if (digits[1] == 0)
				used = 1;
		};
		break;

		case 6: // a.used == 1, b.used == 2
		{
			digits[0] = UMul (a.digits[0], b.digits[0], &digits[1]);
			UInt temp = digits[1];

			digits[1] += UMul (a.digits[0], b.digits[1], &digits[2]);

			if (digits[1] < temp)
				digits[2]++;
			else if (digits[2] == 0)
				used = 2;
		};
		break;

		case 9: // a.used == 2, b.used == 1
		{
			digits[0] = UMul (a.digits[0], b.digits[0], &digits[1]);
			UInt temp = digits[1];

			digits[1] += UMul (a.digits[1], b.digits[0], &digits[2]);

			if (digits[1] < temp)
				digits[2]++;
			else if (digits[2] == 0)
				used = 2;
		};
		break;

		case 10: // a.used == 2, b.used == 2
		{
			digits[0] = UMul (a.digits[0], b.digits[0], &digits[1]);

			UInt temp = digits[1], t1, t2;
			digits[1] += UMul (a.digits[1], b.digits[0], &t1);
			if (digits[1] < temp)
				t1++;

			temp = digits[1];
			digits[1] += UMul (a.digits[0], b.digits[1], &t2);
			if (digits[1] < temp)
				t2++;

			digits[2] = UMul (a.digits[1], b.digits[1], &digits[3]);
			temp = digits[2];
			digits[2] += t1;
			if (digits[2] < temp)
				digits[3]++;
			temp = digits[2];
			digits[2] += t2;
			if (digits[2] < temp)
				digits[3]++;
			else if (digits[3] == 0)
				used = 3;
		};
		break;

		default:
		{
			memset (digits, 0, DigitSize * used);
			ULong aIdx = 0, raIdx = 0;

			do {
				ULong bIdx = 0, rIdx = raIdx;
				do {
					UInt high, low;
					low = UMul (a.Digit (aIdx), b.Digit (bIdx), &high);

					UInt s = low + Digit (rIdx);
					bool overflow = ((((low ^ Digit (rIdx)) & ~s) | (low & Digit (rIdx))) & HighBit) != 0;
					Digit (rIdx) = s;

					rIdx++;

					s = high + Digit (rIdx);
					if (overflow)
						s++;
					overflow = ((((high ^ Digit (rIdx)) & ~s) | (high & Digit (rIdx))) & HighBit) != 0;
					Digit (rIdx) = s;

					if (overflow) {
						for (ULong k = rIdx + 1; Valid (k); k++) {
							if (++Digit (k) != 0)
								break;
						}
					}

					bIdx++;
				} while (b.Valid (bIdx));

				aIdx++;
				raIdx++;
			} while (a.Valid (aIdx));

			ShortenLength ();
		};
		break;
	};

	negative = IsZero () ? false : a.negative != b.negative;
}

template<typename Int>
void Integer<Int>::CopyLessDivide (const Integer &dividend, const Integer &divisor)
{
	bool neg = dividend.negative != divisor.negative;

	if (divisor.used == 1) {
		if (divisor.digits[0] == 1) {
			*this = dividend;
			negative = IsZero () ? false : neg;
			return;
		} else if (divisor.digits[0] == 0) {
			// you bastard...
			throw GS::Exception (nullptr, __FILE__, __LINE__);
		}
	}

	if (dividend.used == 1 && divisor.used == 1) {
		digits[0] = dividend.digits[0] / divisor.digits[0];
		used = 1;
	} else {
		if (dividend.used < divisor.used || (dividend.used == divisor.used && dividend.digits[dividend.used-1] < divisor.digits[divisor.used-1])) {
			*this = 0;
			return;
		}

		short mostSigA = GetMostSignificantBitIdx (dividend.digits[dividend.used-1]);
		short mostSigB = GetMostSignificantBitIdx (divisor.digits[divisor.used-1]);

		Integer a = dividend;
		Integer b (a.used, divisor.used);
		memcpy (b.digits, divisor.digits, DigitSize * divisor.used);
		a.negative = b.negative = false;

		Reallocate (a.used + 1, false);
		used = a.used;
		memset (digits, 0, DigitSize * (used + 1));

		ULong digitsAdded = a.used - b.used;
		memset (&(b.digits[b.used]), 0, DigitSize * digitsAdded);
		b.used = a.used;
		const ULong abLastDigit = a.used - 1;

		if (mostSigA < mostSigB)
			digitsAdded--;

		short shift = 0;
		ULong retIdx = 0;

		if (digitsAdded > 0) {
			ULong to = abLastDigit, from = to - digitsAdded;
			retIdx += digitsAdded;
			shift += (short) digitsAdded * BaseTypeBitNum;

			do {
				b.Digit (to) = b.Digit (from);
				to--;
				from--;
			} while (b.Valid (from));

			memset (&(b.digits[0]), 0, (to + 1) * DigitSize);
		}

		const UInt& aLast = a.Digit (abLastDigit), &bLast = b.Digit (abLastDigit);
		short sigBitDiff = mostSigA - mostSigB;
		if (sigBitDiff < 0)
			sigBitDiff += BaseTypeBitNum;

		ShiftLeft (b, sigBitDiff);
		shift = shift + sigBitDiff;
		UInt bitMask = UInt (1) << sigBitDiff;
		mostSigB = mostSigA;
		short t = sigBitDiff;

		bool carry = false;
		do {
			if (carry || aLast > bLast || (aLast == bLast && a.CompareEqLenAbs (b, 1) >= 0)) {
				Digit (retIdx) |= bitMask;
				GCDSubtract (a, b);
			}

			carry = (aLast & HighBit) != 0;

			ULong aFirstSigDigit = a.used;
			while (aFirstSigDigit > 0 && a.Digit (aFirstSigDigit - 1) == 0) aFirstSigDigit--;
			if (aFirstSigDigit == 0)
				break;
			else
				aFirstSigDigit--;

			ULong mostSigDigitDiff = abLastDigit - aFirstSigDigit;
			mostSigA = GetMostSignificantBitIdx (a.Digit (aFirstSigDigit));
			sigBitDiff = mostSigB - mostSigA;
			if (sigBitDiff < 0) {
				if (mostSigDigitDiff == 0) {
					DBBREAK ();	// ez itt nem reprodukalhato, inkonzisztens allapot, mindenkeppen szolj nekem! (PP)
					throw GS::Exception (nullptr, __FILE__, __LINE__);
				}

				mostSigDigitDiff--;
				sigBitDiff += BaseTypeBitNum;
			} else if (sigBitDiff == 0 && mostSigDigitDiff == 0) {
				sigBitDiff++;
			}

			if (mostSigDigitDiff > 0) {
				ULong to = abLastDigit, from = to - mostSigDigitDiff;
				retIdx -= mostSigDigitDiff;
				shift -= (short) mostSigDigitDiff * BaseTypeBitNum;

				do {
					a.Digit (to) = a.Digit (from);
					to--;
					from--;
				} while (a.Valid (from));

				memset (&(a.digits[0]), 0, (to + 1) * DigitSize);
			}

			ShiftLeft (a, sigBitDiff);
			shift = shift - sigBitDiff;

			if (t - sigBitDiff < 0) {
				bitMask <<= BaseTypeBitNum - sigBitDiff;
				t = t + BaseTypeBitNum - sigBitDiff;
				retIdx--;
			} else {
				bitMask >>= sigBitDiff;
				t = t - sigBitDiff;
			}
		} while (shift >= 0);

		ShortenLength ();
	}

	negative = IsZero () ? false : neg;
}

template<typename Int>
GS_FORCE_INLINE Integer<Int>::Integer (ULong buffDigitCnt, ULong usedDigits) :
	used (usedDigits),
	negative (false)
{
	if (buffDigitCnt > FixWidth) {
		digits = AllocateBuffer (buffDigitCnt);
	} else {
		digits = reinterpret_cast<UInt*> (fixedDigitsBuffer);
	}
}

template<typename Int>
GS_FORCE_INLINE Integer<Int>::Integer (Int op /*= 0*/)
{
	digits = reinterpret_cast<UInt*> (fixedDigitsBuffer);
	digits[0] = UInt (GS::Abs (op));
	used = 1;
	negative = op < 0;
}

template<typename Int>
GS_FORCE_INLINE Integer<Int>::Integer (const Integer& op) :
	used (op.used),
	negative (op.negative)
{
	if (used > FixWidth)
		digits = AllocateBuffer (used);
	else
		digits = reinterpret_cast<UInt*> (fixedDigitsBuffer);

	memcpy (digits, op.digits, DigitSize * used);	//lint !e669 [Possible data overrun]
}

template<typename Int>
GS_FORCE_INLINE Integer<Int>::Integer (Integer&& op) :
	used (op.used),
	negative (op.negative)
{
	if (used > FixWidth) {
		digits = op.digits;
		op.digits = reinterpret_cast<UInt*> (op.fixedDigitsBuffer);
	} else {
		digits = reinterpret_cast<UInt*> (fixedDigitsBuffer);
		memcpy (digits, op.digits, DigitSize * used);	//lint !e669 [Possible data overrun]
	}
}

template<typename Int>
template<class LeftOp, class RightOp, class Evaluator>
GS_FORCE_INLINE Integer<Int>::Integer (const BinaryIntOperator<LeftOp, RightOp, Evaluator, Int>& op) :
	digits (reinterpret_cast<UInt*> (fixedDigitsBuffer)),
	used (0),
	negative (false)
{
	op.Evaluate (*this);
}

template<typename Int>
GS_FORCE_INLINE Integer<Int>::~Integer ()
{
	if (digits != reinterpret_cast<UInt*> (fixedDigitsBuffer))
		DestroyBuffer (digits);
}

template<typename Int>
GS_FORCE_INLINE const Integer<Int>& Integer<Int>::operator= (const Integer& op)
{
	if (this != &op) {
		Reallocate (op.used, false);
		used = op.used;
		negative = op.negative;
		memcpy (digits, op.digits, DigitSize * used);
	}

	return *this;
}

template<typename Int>
GS_FORCE_INLINE const Integer<Int>& Integer<Int>::operator= (Integer&& op)
{
	if (this != &op) {
		used = op.used;
		negative = op.negative;

		if (digits != reinterpret_cast<UInt*> (fixedDigitsBuffer))
			DestroyBuffer (digits);

		if (used > FixWidth) {
			digits = op.digits;
			op.digits = reinterpret_cast<UInt*> (op.fixedDigitsBuffer);
		} else {
			digits = reinterpret_cast<UInt*> (fixedDigitsBuffer);
			memcpy (digits, op.digits, DigitSize * used);	//lint !e669 [Possible data overrun]
		}
	}

	return *this;
}

template<typename Int>
template<class LeftOp, class RightOp, class Evaluator>
GS_FORCE_INLINE const Integer<Int>& Integer<Int>::operator= (const BinaryIntOperator<LeftOp, RightOp, Evaluator, Int>& op)
{
	Integer temp;
	op.Evaluate (temp);
	return *this = temp;
}

template<typename Int>
GS_FORCE_INLINE const Integer<Int>& Integer<Int>::operator= (Int op)
{
	digits[0] = UInt (GS::Abs (op));
	used = 1;
	negative = op < 0;

	return *this;
}

template<typename Int>
GS_FORCE_INLINE bool Integer<Int>::operator== (const Integer& op) const
{
	if (negative != op.negative || used != op.used)
		return false;

	ULong idx = 0;
	do {
		if (Digit (idx) != op.Digit (idx))
			return false;
		idx++;
	} while (Valid (idx));

	return true;
}

template<typename Int>
GS_FORCE_INLINE bool Integer<Int>::operator!= (const Integer& op) const
{
	return !(*this == op);
}

template<typename Int>
GS_FORCE_INLINE bool Integer<Int>::operator< (const Integer& op) const
{
	return Compare (op) < 0;
}

template<typename Int>
GS_FORCE_INLINE bool Integer<Int>::operator> (const Integer& op) const
{
	return Compare (op) > 0;
}

template<typename Int>
GS_FORCE_INLINE bool Integer<Int>::operator<= (const Integer& op) const
{
	return Compare (op) <= 0;
}

template<typename Int>
GS_FORCE_INLINE bool Integer<Int>::operator>= (const Integer& op) const
{
	return Compare (op) >= 0;
}

template<typename Int>
Integer<Int> Integer<Int>::operator- () const
{
	Integer retVal (*this);
	retVal.negative = IsZero () ? false : !retVal.negative;

	return retVal;
}

template<typename Int>
template<class RightOpType>
GS_FORCE_INLINE BinaryIntOperator<Integer<Int>, RightOpType, BinaryAdder, Int> Integer<Int>::operator+ (const RightOpType& op) const
{
	return BinaryIntOperator<Integer<Int>, RightOpType, BinaryAdder, Int> (*this, op);
}

template<typename Int>
template<class RightOpType>
GS_FORCE_INLINE BinaryIntOperator<Integer<Int>, RightOpType, BinarySubtractor, Int> Integer<Int>::operator- (const RightOpType& op) const
{
	return BinaryIntOperator<Integer<Int>, RightOpType, BinarySubtractor, Int> (*this, op);
}

template<typename Int>
template<class RightOpType>
GS_FORCE_INLINE BinaryIntOperator<Integer<Int>, RightOpType, BinaryMultiplier, Int> Integer<Int>::operator* (const RightOpType& op) const
{
	return BinaryIntOperator<Integer<Int>, RightOpType, BinaryMultiplier, Int> (*this, op);
}

template<typename Int>
template<class RightOpType>
GS_FORCE_INLINE BinaryIntOperator<Integer<Int>, RightOpType, BinaryDivider, Int> Integer<Int>::operator/ (const RightOpType& op) const
{
	return BinaryIntOperator<Integer<Int>, RightOpType, BinaryDivider, Int> (*this, op);
}

template<typename Int>
GS_FORCE_INLINE const Integer<Int>& Integer<Int>::operator+= (const Integer& op)
{
	CopyLessAdd (*this, op);
	return *this;
}

template<typename Int>
GS_FORCE_INLINE const Integer<Int>& Integer<Int>::operator-= (const Integer& op)
{
	CopyLessSubtract (*this, op);
	return *this;
}

template<typename Int>
GS_FORCE_INLINE const Integer<Int>& Integer<Int>::operator*= (const Integer& op)
{
	Integer retVal;
	retVal.CopyLessMultiply (*this, op);
	return *this = retVal;
}

template<typename Int>
GS_FORCE_INLINE const Integer<Int>& Integer<Int>::operator/= (const Integer& op)
{
	CopyLessDivide (*this, op);
	return *this;
}

template<typename Int>
Integer<Int> Integer<Int>::GCD (const Integer& op) const
{
	if (IsZero ()) {
		if (op.IsZero ())
			return 1;
		return op.Abs ();
	}
	if (op.IsZero ())
		return this->Abs ();

	ULong maxSize = GS::Max (used, op.used) + 1;

	Integer u (maxSize, used);
	Integer v (maxSize, op.used);

	memcpy (u.digits, digits, DigitSize * used);
	memcpy (v.digits, op.digits, DigitSize * op.used);
	u.digits[maxSize - 1] = 0;
	v.digits[maxSize - 1] = 0;

	short shift = 0;
	for (; ((u.digits[0] | v.digits[0]) & 1) == 0; shift++) {
		ShiftRight (u);
		ShiftRight (v);
	}

	while ((u.digits[0] & 1) == 0)
		ShiftRight (u);

	if (u.used > v.used) {
		do
			v.digits[v.used++] = 0;
		while (u.used > v.used);
	} else {
		while (u.used < v.used)
			u.digits[u.used++] = 0;
	}

	Integer* pu = &u;
	Integer* pv = &v;

	for (;;) {
		while ((pv->digits[0] & 1) == 0)
			ShiftRight (*pv);

		while (pu->Digit (pu->used - 1) == 0 && pv->Digit (pv->used - 1) == 0) {
			pu->used--;
			pv->used--;
		}

		if (pu->digits[0] == 1) {
			ULong idx = 1;
			for (; pu->Valid (idx); idx++)
				if (pu->Digit (idx) != 0)
					break;
			if (!pu->Valid (idx))
				break;
		}

		if (pv->digits[0] == 1) {
			ULong idx = 1;
			for (; pv->Valid (idx); idx++)
				if (pv->Digit (idx) != 0)
					break;
			if (!pv->Valid (idx)) {
				GS::Swap (pu, pv);
				break;
			}
		}

		if (pu->CompareAbs (*pv) < 0)
			GCDSubtract (*pv, *pu);
		else {
			GCDSubtract (*pu, *pv);
			GS::Swap (pu, pv);
		}

		ShiftRight (*pv);

		ULong idx = 0;
		do {
			if (pv->Digit (idx) != 0)
				break;
			idx++;
		} while (pv->Valid (idx));

		if (!pv->Valid (idx))
			break;
	}

	for (; shift > 0; shift--) {
		if (pu->Digit (pu->used - 1) & HighBit)
			pu->digits[pu->used++] = 0;
		ShiftLeft (*pu, 1);
	}

	pu->ShortenLength ();
	return *pu;
}

template<typename Int>
GS_FORCE_INLINE bool Integer<Int>::IsNegative () const
{
	return negative;
}

template<typename Int>
inline short Integer<Int>::Sgn () const
{
	if (IsZero ())
		return 0;
	else if (negative)
		return -1;
	else
		return 1;
}

template<typename Int>
inline Integer<Int> Integer<Int>::Abs () const
{
	if (!negative)
		return *this;

	Integer retVal (*this);
	retVal.negative = false;
	return retVal;
}

template<typename Int>
inline void Integer<Int>::ToAbs ()
{
	negative = false;
}

template<typename Int>
inline void Integer<Int>::InvertSign ()
{
	if (!IsZero ())
		negative = !negative;
}

template<typename Int>
inline Integer<Int>	Integer<Int>::Sqrt (void) const
{
	// Newton's method
	if (IsNegative ()) {
		// Integer is not a complex number...
		throw GS::Exception (nullptr, __FILE__, __LINE__);
	}

	Integer x_k = *this;
	bool done = false; // csak a compilernek kell
	do {
		Integer x_k_prev = x_k;
		x_k = (x_k_prev + (*this)/x_k_prev) / 2;
		if (x_k >= x_k_prev)
			return x_k_prev;
	} while (!done);

	return x_k; // csak a compilernek kell
}

template<typename Int>
inline Integer<Int>	Integer<Int>::InverseModP (const Integer<Int>& p) const
{
	Integer s = 0, old_s = 1;
	Integer r = p, old_r = *this;
	Integer temp;

	while (r != 0) {
		Integer quotient = old_r/r;

		temp = r;
		r = old_r - quotient * temp;
		old_r = temp;

		temp = s;
		s = old_s - quotient * temp;
		old_s = temp;
	}
	if (old_s.IsNegative ())
		old_s += p;
	return old_s;
}
	
template<typename Int>
inline Integer<Int>	Integer<Int>::Pow (Integer<Int> exp) const
{
	if (exp.IsNegative ()) {
		// not supported this way
		throw GS::Exception (nullptr, __FILE__, __LINE__);
	}

	Integer base = *this;
	Integer result = 1;
	while (exp != 0)
	{
		if (exp.Digit (0) & 1)
			result *= base;
		exp /= 2;
		base *= base;
	}

	return result;
}

template<typename Int>
inline Integer<Int>	Integer<Int>::PowModP (Integer<Int> exp, const Integer<Int>& p) const
{
	if (exp.IsNegative ()) {
		// not supported this way
		throw GS::Exception (nullptr, __FILE__, __LINE__);
	}

	Integer base = *this;
	Integer result = 1;
	while (exp != 0)
	{
		if (exp.Digit (0) & 1) {
			result *= base;
			result.Mod (p);
		}
		exp /= 2;
		base *= base;
		base.Mod (p);
	}

	return result;
}
	
template<typename Int>
inline Int	Integer<Int>::Log (const Base base /* = B10 */) const
{
	if (IsNegative () || IsZero ())
		throw GS::Exception (nullptr, __FILE__, __LINE__);

	Int log_2_num = BaseTypeBitNum * (Width () - 1) + GetMostSignificantBitIdx (Digit (used - 1)) + 1;
	if (base == B02) {
		return log_2_num;
	} else if (base == B04) {
		return static_cast<Int> (ceil (log_2_num / 2.));
	} else if (base == B08) {
		return static_cast<Int> (ceil (log_2_num / 3.));
	} else if (base == B16) {
		return static_cast<Int> (ceil (log_2_num / 4.));
	}

	Integer temp = *this;
	Int log_base_num = 0;
	do {
		temp /= base;
		++log_base_num;
	} while (temp != 0);
	return log_base_num;
}

template<typename Int>
inline Integer<Int>	Integer<Int>::Mod (const Integer<Int>& p) const
{
	if (p.IsNegative () || p.IsZero ())
		throw GS::Exception (nullptr, __FILE__, __LINE__);

	return *this - *this/p*p;
}

template<typename Int>
inline void	Integer<Int>::Mod (const Integer<Int>& p)
{
	*this = static_cast<const Integer<Int>*> (this)->Mod (p);
}
	
template<typename Int>
inline bool	Integer<Int>::SetupFromString (const char* buff, const USize length, const Base base /* = B10 */)
{
	if (buff == nullptr)
		return false;

	Integer temp;
	for (UIndex i = 0; i < length; ++i) {
		Int add;
		switch (buff[i]) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				add = buff[i] - '0';
				if (base < add)
					return false;
				break;
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
				add = buff[i] - 'A';
				if (base < add + 10)
					return false;
				break;
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
				add = buff[i] - 'a';
				if (base < add + 10)
					return false;
				break;
			default:
				// invalid string
				return false;
		};

		temp = temp * base + add;
	}

	*this = temp;
	return true;
}

template<typename Int>
inline void	Integer<Int>::Print (char* buff, Int buffSize, const Base base /* = B10 */, Int* written /* = nullptr */) const
{
	static const char Digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

	if (written != nullptr)
		*written = 0;

	Int len = Log (base); // not power-of-2 bases are time consuming!
	if (len > buffSize)
		return;

	Integer temp = *this;
	char* ptr = buff + len - 1;
	GS_DEBUG_ONLY (Int counter = 0;);

	do {
		*ptr-- = Digits[((temp - temp/base*base).ConvertToInt ())];
		temp /= base;
		GS_DEBUG_ONLY (++counter;);
	} while (temp != 0);
	DBASSERT (counter == len);

	if (written != nullptr)
		*written = len;
}

template<typename Int>
short Integer<Int>::Compare (const Integer& op) const
{
	if (used != op.used) {
		bool opNeg = op.negative;
		if (negative) {
			if (!opNeg)
				return -1;
			return used > op.used ? -1 : 1;
		} else {
			if (opNeg)
				return 1;
			return used < op.used ? -1 : 1;
		}
	}

	if (negative != op.negative)
		return negative ? -1 : 1;

	short cmp = CompareAbs (op);
	cmp *= negative ? -1 : 1;

	return cmp;
}

template<typename Int>
GS_FORCE_INLINE short Integer<Int>::CompareAbs (const Integer& op) const
{
	if (used != op.used)
		return used < op.used ? -1 : 1;

	return CompareEqLenAbs (op, 0);
}

template<typename Int>
short Integer<Int>::CompareEqLenAbs (const Integer& op, ULong shift) const
{
	for (ULong idx = used - shift - 1; Valid (idx); idx--) {
		if (Digit (idx) < op.Digit (idx))
			return -1;
		if (Digit (idx) > op.Digit (idx))
			return 1;
	}

	return 0;
}

template<typename Int>
void Integer<Int>::ConvertFromDouble (double op)
{
	*this = 0;

	if (!DBVERIFY (	GS::ClassifyDouble (op) == GS::DoubleClass::Zero ||
					GS::ClassifyDouble (op) == GS::DoubleClass::Normal ||
					GS::ClassifyDouble (op) == GS::DoubleClass::Denormal))
	{
		return;
	}

	op = floor (op + 0.5);
	bool neg = op < 0;
	op = GS::Abs (op);

	ULong DBLBitNum = DBL_MANT_DIG-1; //-1 for the sign bit!
	ULong BitNum = (DBLBitNum < BaseTypeBitNum) ? DBLBitNum : BaseTypeBitNum; //64 or 32 bit Integers and double must be able to represent highVal!!!
	const Int highValInt = UInt (1) << (BitNum - 2);
	const double highVal = static_cast <double> (highValInt);
	Integer m = 1;
	for (;;) {
		if (op < highVal) {
			*this += m * Int (op);
			break;
		}

		double r = floor (op / highVal);
		*this += m * Int (op - r * highVal);
		op = r;
		m *= highValInt;
	}

	this->negative = neg;
}

template<typename Int>
Int Integer<Int>::ConvertToInt () const
{
	Int retVal (digits[0]);
	if (negative)
		retVal = ~retVal + 1;

	return retVal;
}

template<typename Int>
double Integer<Int>::ConvertToDouble () const
{
	Int64 exponent; 
	double m = Frexp (exponent); 
	DBASSERT (DBL_MAX_EXP >= exponent); 
	DBASSERT (DBL_MIN_EXP <= exponent); 
	return ldexp (m, (int) exponent); 
}

template<typename Int>
double Integer<Int>::Frexp (Int64 & exponent) const
{
	double multiplier = UInt (1) << (BaseTypeBitNum / 2);
	multiplier = multiplier * multiplier;

	ULong idx = used - 1;

	while (Digit (idx) == 0 && idx > 0) --idx; //Skip zero digits

	double resAbs = double (Digit (idx));
	exponent = 0;  

	ULong totalBitsAfterFirstDigit = 0;

	for (idx--; Valid (idx); idx--) {
		resAbs = resAbs * multiplier + Digit (idx);

		totalBitsAfterFirstDigit += BaseTypeBitNum;	//counts the bits of just-added digit!
		if (totalBitsAfterFirstDigit > DBL_MANT_DIG) { //totalBits does not count for the highest digit, only for digits below. This way we can be sure that we have filled up the double...
			exponent = idx * BaseTypeBitNum; 
			break;
		}
	}

	int addExponent;
	double mantissa = frexp (resAbs, &addExponent);
	exponent += addExponent;

	return negative ? -mantissa : mantissa;
}

template<typename Int>
void Integer<Int>::DBDump () const
{
	DBPrintf ("%c", negative ? '-' : '+');
	UInt dig;
	for (USize i = 0; i < used; ++i) {
		dig = digits[used-i-1];
		if (dig != 0) {
			DBPrintf ("%u ", dig);
		}
	}
}

template<typename Int>
ULong Integer<Int>::Width () const
{
	return used;
}

}	// namespace QXTools

#endif	// INTEGERIMP_HPP
