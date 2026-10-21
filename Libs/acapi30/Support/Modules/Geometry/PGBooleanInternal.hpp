// *****************************************************************************
// Polygon Boolean Operations
//
// Module: Geometry
// Contact person: HK
//
// *****************************************************************************

#ifndef PGBOOLEANINTERNAL_H
#define PGBOOLEANINTERNAL_H

#include "GeometricDefinitions.h"
#include "Integer.hpp"
#include "GSDebug.hpp"

using namespace Geometry;

namespace PolygonBoolean {

typedef Int32 SignedInt32;
typedef UInt32 UnsignedInt32;

class UDoubleInt32;

class SDoubleInt32
{
	signed long long l;

	friend class UDoubleInt32;
	friend SDoubleInt32 Mul (const SignedInt32 a, const SignedInt32 b);

public:
	static const SignedInt32 minCoordVal =				-0x0fffff00;
	static const SignedInt32 maxCoordVal =				 0x0fffff00;
	static const SignedInt32 nodeGridMask =				 0xfffffff8;
	static const SignedInt32 nodeGridRound =			 4;
	static const SignedInt32 radiusGridMask =			 0xfffffff8;
	static const SignedInt32 radiusGridRound =			 4;
	static const SignedInt32 radiusGridCeil =			 7;
	static const SignedInt32 minSnapDist =				 25;
	static const SignedInt32 angleCalcPrecision =		 0x20000000;

	SDoubleInt32 ();
	SDoubleInt32 (const SDoubleInt32& a);
	SDoubleInt32 (const UDoubleInt32& a);
	SDoubleInt32 (SignedInt32 a);
	SDoubleInt32 (UnsignedInt32 a);

	const SDoubleInt32& operator= (const SDoubleInt32& a);
	const SDoubleInt32& operator= (const UDoubleInt32& a);
	const SDoubleInt32& operator= (SignedInt32 a);
	const SDoubleInt32& operator= (UnsignedInt32 a);

	const SDoubleInt32& operator+= (const SDoubleInt32& a);
	const SDoubleInt32& operator-= (const SDoubleInt32& a);

	SDoubleInt32 operator- () const;
	SDoubleInt32 operator+ (const SDoubleInt32& op) const;
	SDoubleInt32 operator- (const SDoubleInt32& op) const;
	bool operator== (const SDoubleInt32& op) const;
	bool operator!= (const SDoubleInt32& op) const;
	bool operator< (const SDoubleInt32& op) const;
	bool operator<= (const SDoubleInt32& op) const;
	bool operator> (const SDoubleInt32& op) const;
	bool operator>= (const SDoubleInt32& op) const;
	SignedInt32 operator/ (SignedInt32 b) const;
};

class UDoubleInt32
{
	unsigned long long l;

	friend class SDoubleInt32;
	friend UDoubleInt32 Mul (UnsignedInt32 a, UnsignedInt32 b);

public:
	UDoubleInt32 ();
	UDoubleInt32 (const UDoubleInt32& a);
	UDoubleInt32 (const SDoubleInt32& a);
	UDoubleInt32 (UnsignedInt32 a);
	UDoubleInt32 (SignedInt32 a);

	const UDoubleInt32& operator= (const UDoubleInt32& a);
	const UDoubleInt32& operator= (const SDoubleInt32& a);
	const UDoubleInt32& operator= (UnsignedInt32 a);
	const UDoubleInt32& operator= (SignedInt32 a);

	SDoubleInt32 operator- () const;
	UDoubleInt32 operator+ (const UDoubleInt32& op) const;
	UDoubleInt32 operator- (const UDoubleInt32& op) const;
	bool operator== (const UDoubleInt32& op) const;
	bool operator!= (const UDoubleInt32& op) const;
	bool operator< (const UDoubleInt32& op) const;
	bool operator<= (const UDoubleInt32& op) const;
	bool operator> (const UDoubleInt32& op) const;
	bool operator>= (const UDoubleInt32& op) const;
	UnsignedInt32 operator/ (UnsignedInt32 b) const;
};

SDoubleInt32 Mul (SignedInt32 a, SignedInt32 b);
UDoubleInt32 Mul (UnsignedInt32 a, UnsignedInt32 b);
SignedInt32 Sqrt (const SDoubleInt32& a);
UnsignedInt32 Sqrt (const UDoubleInt32& a);


GS_FORCE_INLINE SDoubleInt32::SDoubleInt32 () : l (0)
{
}

GS_FORCE_INLINE SDoubleInt32::SDoubleInt32 (const SDoubleInt32& a)
{
	l = a.l;
}

GS_FORCE_INLINE SDoubleInt32::SDoubleInt32 (const UDoubleInt32& a)
{
	l = (signed long long) (a.l);
}

GS_FORCE_INLINE SDoubleInt32::SDoubleInt32 (const SignedInt32 a)
{
	l = a;
}

GS_FORCE_INLINE SDoubleInt32::SDoubleInt32 (const UnsignedInt32 a)
{
	l = a;
}

GS_FORCE_INLINE const SDoubleInt32& SDoubleInt32::operator= (const SDoubleInt32& a)
{
	l = a.l;

	return *this;
}

GS_FORCE_INLINE const SDoubleInt32& SDoubleInt32::operator= (const UDoubleInt32& a)
{
	l = (signed long long) (a.l);

	return *this;
}

GS_FORCE_INLINE const SDoubleInt32& SDoubleInt32::operator= (const SignedInt32 a)
{
	l = a;

	return *this;
}

GS_FORCE_INLINE const SDoubleInt32& SDoubleInt32::operator= (const UnsignedInt32 a)
{
	l = a;

	return *this;
}

GS_FORCE_INLINE const SDoubleInt32& SDoubleInt32::operator+= (const SDoubleInt32& a)
{
	return *this = *this + a;
}

GS_FORCE_INLINE const SDoubleInt32& SDoubleInt32::operator-= (const SDoubleInt32& a)
{
	return *this = *this - a;
}

GS_FORCE_INLINE SDoubleInt32 SDoubleInt32::operator- () const
{
	SDoubleInt32 res;

	res.l = -l;

	return res;
}

GS_FORCE_INLINE SDoubleInt32 SDoubleInt32::operator+ (const SDoubleInt32& op) const
{
	SDoubleInt32 res;

	res.l = l + op.l;

	return res;
}

GS_FORCE_INLINE SDoubleInt32 SDoubleInt32::operator- (const SDoubleInt32& op) const
{
	SDoubleInt32 res;

	res.l = l - op.l;

	return res;
}

GS_FORCE_INLINE bool SDoubleInt32::operator== (const SDoubleInt32& op) const
{
	return l == op.l;
}

GS_FORCE_INLINE bool SDoubleInt32::operator!= (const SDoubleInt32& op) const
{
	return !(*this == op);
}

GS_FORCE_INLINE bool SDoubleInt32::operator< (const SDoubleInt32& op) const
{
	return l < op.l;
}

GS_FORCE_INLINE bool SDoubleInt32::operator<= (const SDoubleInt32& op) const
{
	return l <= op.l;
}

GS_FORCE_INLINE bool SDoubleInt32::operator> (const SDoubleInt32& op) const
{
	return !(*this <= op);
}

GS_FORCE_INLINE bool SDoubleInt32::operator>= (const SDoubleInt32& op) const
{
	return !(*this < op);
}

GS_FORCE_INLINE SignedInt32 SDoubleInt32::operator/ (const SignedInt32 b) const
{
	if (b == 0)
		throw GeometryAlgorithmErrorException ("Divide by 0", __FILE__, __LINE__);

	return (Int32) (l / b);
}

GS_FORCE_INLINE UDoubleInt32::UDoubleInt32 () : l(0)
{
}

GS_FORCE_INLINE UDoubleInt32::UDoubleInt32 (const UDoubleInt32& a)
{
	l = a.l;
}

GS_FORCE_INLINE UDoubleInt32::UDoubleInt32 (const SDoubleInt32& a)
{
	l = (unsigned long long) (a.l);
}

GS_FORCE_INLINE UDoubleInt32::UDoubleInt32 (const UnsignedInt32 a)
{
	l = a;
}

GS_FORCE_INLINE UDoubleInt32::UDoubleInt32 (const SignedInt32 a)
{
	l = (unsigned long long) (a);
}

GS_FORCE_INLINE const UDoubleInt32& UDoubleInt32::operator= (const UDoubleInt32& a)
{
	l = a.l;

	return *this;
}

GS_FORCE_INLINE const UDoubleInt32& UDoubleInt32::operator= (const SDoubleInt32& a)
{
	l = (unsigned long long) (a.l);

	return *this;
}

GS_FORCE_INLINE const UDoubleInt32& UDoubleInt32::operator= (UnsignedInt32 a)
{
	l = a;

	return *this;
}

GS_FORCE_INLINE const UDoubleInt32& UDoubleInt32::operator= (SignedInt32 a)
{
	l = (unsigned long long) (a);

	return *this;
}

GS_FORCE_INLINE SDoubleInt32 UDoubleInt32::operator- () const
{
	return -SDoubleInt32 (*this);
}

GS_FORCE_INLINE UDoubleInt32 UDoubleInt32::operator+ (const UDoubleInt32& op) const
{
	UDoubleInt32 res;

	res.l = l + op.l;

	return res;
}

GS_FORCE_INLINE UDoubleInt32 UDoubleInt32::operator- (const UDoubleInt32& op) const
{
	UDoubleInt32 res;

	res.l = l - op.l;

	return res;
}

GS_FORCE_INLINE bool UDoubleInt32::operator== (const UDoubleInt32& op) const
{
	return l == op.l;
}

GS_FORCE_INLINE bool UDoubleInt32::operator!= (const UDoubleInt32& op) const
{
	return !(*this == op);
}

GS_FORCE_INLINE bool UDoubleInt32::operator< (const UDoubleInt32& op) const
{
	return l < op.l;
}

GS_FORCE_INLINE bool UDoubleInt32::operator<= (const UDoubleInt32& op) const
{
	return l <= op.l;
}

GS_FORCE_INLINE bool UDoubleInt32::operator> (const UDoubleInt32& op) const
{
	return !(*this <= op);
}

GS_FORCE_INLINE bool UDoubleInt32::operator>= (const UDoubleInt32& op) const
{
	return !(*this < op);
}

inline UnsignedInt32 UDoubleInt32::operator/ (const UnsignedInt32 b) const
{
	if (b == 0)
		throw GeometryAlgorithmErrorException ("Divide by 0", __FILE__, __LINE__);

	return (UInt32) ((l + b / 2) / b);
}

GS_FORCE_INLINE SDoubleInt32 Mul (const SignedInt32 a, const SignedInt32 b)
{
	SDoubleInt32 res;
	res.l = (signed long long) (a) * (signed long long) (b);

	return res;
}

GS_FORCE_INLINE UDoubleInt32 Mul (const UnsignedInt32 a, const UnsignedInt32 b)
{
	UDoubleInt32 res;
	res.l = (unsigned long long) (a) * (unsigned long long) (b);

	return res;
}

inline SignedInt32 Sqrt (const SDoubleInt32& a)
{
	if (a < SignedInt32 (0))
		throw GeometryAlgorithmErrorException ("Sqrt of negativ value", __FILE__, __LINE__);

	return SignedInt32 (Sqrt (UDoubleInt32 (a)));
}

inline UnsignedInt32 Sqrt (const UDoubleInt32& a)
{
	UnsignedInt32 max = 0xffffffff;
	UnsignedInt32 min = 0;

	while (max - min > 2) {
		UnsignedInt32 mid = max / 2 + min / 2;
		if (Mul (mid, mid) > a)
			max = mid;
		else
			min = mid;
	}

	if (max - min < 2)
		return min;
	if (Mul ((min + 1), (min + 1)) > a)
		return min;
	else
		return min + 1;
}

typedef signed long long SignedInt64;
typedef unsigned long long UnsignedInt64;

class UDoubleInt64;

class SDoubleInt64
{
	UnsignedInt64 lo;
	SignedInt64 hi;

	friend class UDoubleInt64;

public:
	static const SignedInt64 minCoordVal =				-0x0fffffffffffff00LL;
	static const SignedInt64 maxCoordVal =				 0x0fffffffffffff00LL;
	static const SignedInt64 nodeGridMask =				 0xffffffffffffffc0LL;
	static const SignedInt64 nodeGridRound =			 32;
	static const SignedInt64 radiusGridMask =			 0xfffffffffffffff0LL;
	static const SignedInt64 radiusGridRound =			 8;
	static const SignedInt64 radiusGridCeil =			 15;
	static const SignedInt64 minSnapDist =				 200;
	static const SignedInt64 angleCalcPrecision =		 0x0800000000000000LL;

	SDoubleInt64 ();
	SDoubleInt64 (const SDoubleInt64& a);
	SDoubleInt64 (const UDoubleInt64& a);
	SDoubleInt64 (SignedInt64 a);
	SDoubleInt64 (UnsignedInt64 a);


	const SDoubleInt64& operator= (const SDoubleInt64& a);
	const SDoubleInt64& operator= (const UDoubleInt64& a);
	const SDoubleInt64& operator= (SignedInt64 a);
	const SDoubleInt64& operator= (UnsignedInt64 a);

	const SDoubleInt64& operator+= (const SDoubleInt64& a);
	const SDoubleInt64& operator-= (const SDoubleInt64& a);

	SDoubleInt64 operator- () const;
	SDoubleInt64 operator+ (const SDoubleInt64& op) const;
	SDoubleInt64 operator- (const SDoubleInt64& op) const;
	bool operator== (const SDoubleInt64& op) const;
	bool operator!= (const SDoubleInt64& op) const;
	bool operator< (const SDoubleInt64& op) const;
	bool operator<= (const SDoubleInt64& op) const;
	bool operator> (const SDoubleInt64& op) const;
	bool operator>= (const SDoubleInt64& op) const;
	SignedInt64 operator/ (SignedInt64 b) const;
};

class UDoubleInt64
{
	UnsignedInt64 lo;
	UnsignedInt64 hi;

	friend class SDoubleInt64;
	friend UDoubleInt64 Mul (const UnsignedInt64 a, const UnsignedInt64 b);

public:
	UDoubleInt64 ();
	UDoubleInt64 (const UDoubleInt64& a);
	UDoubleInt64 (const SDoubleInt64& a);
	UDoubleInt64 (UnsignedInt64 a);
	UDoubleInt64 (SignedInt64 a);

	const UDoubleInt64& operator= (const UDoubleInt64& a);
	const UDoubleInt64& operator= (const SDoubleInt64& a);
	const UDoubleInt64& operator= (UnsignedInt64 a);
	const UDoubleInt64& operator= (SignedInt64 a);

	SDoubleInt64 operator- () const;
	UDoubleInt64 operator+ (const UDoubleInt64& op) const;
	UDoubleInt64 operator- (const UDoubleInt64& op) const;
	bool operator== (const UDoubleInt64& op) const;
	bool operator!= (const UDoubleInt64& op) const;
	bool operator< (const UDoubleInt64& op) const;
	bool operator<= (const UDoubleInt64& op) const;
	bool operator> (const UDoubleInt64& op) const;
	bool operator>= (const UDoubleInt64& op) const;
	UnsignedInt64 operator/ (UnsignedInt64 b) const;
};

SDoubleInt64 Mul (SignedInt64 a, SignedInt64 b);
UDoubleInt64 Mul (UnsignedInt64 a, UnsignedInt64 b);
SignedInt64 Sqrt (const SDoubleInt64& a);
UnsignedInt64 Sqrt (const UDoubleInt64& a);

typedef SignedInt64 Int64;
typedef SDoubleInt64 DInt64;

GS_FORCE_INLINE SDoubleInt64::SDoubleInt64 () : lo (0), hi (0)
{
}

GS_FORCE_INLINE SDoubleInt64::SDoubleInt64 (const SDoubleInt64& a)
{
	hi = a.hi;
	lo = a.lo;
}

GS_FORCE_INLINE SDoubleInt64::SDoubleInt64 (const UDoubleInt64& a)
{
	hi = SignedInt64 (a.hi);
	lo = a.lo;
}

GS_FORCE_INLINE SDoubleInt64::SDoubleInt64 (const SignedInt64 a)
{
	hi = a < 0 ? -1 : 0;
	lo = UnsignedInt64 (a);
}

GS_FORCE_INLINE SDoubleInt64::SDoubleInt64 (const UnsignedInt64 a)
{
	hi = 0;
	lo = a;
}

GS_FORCE_INLINE const SDoubleInt64& SDoubleInt64::operator= (const SDoubleInt64& a)
{
	hi = a.hi;
	lo = a.lo;

	return *this;
}

GS_FORCE_INLINE const SDoubleInt64& SDoubleInt64::operator= (const UDoubleInt64& a)
{
	hi = SignedInt64 (a.hi);
	lo = a.lo;

	return *this;
}

inline const SDoubleInt64& SDoubleInt64::operator= (const SignedInt64 a)
{
	hi = a < 0 ? -1 : 0;
	lo = UnsignedInt64 (a);

	return *this;
}

GS_FORCE_INLINE const SDoubleInt64& SDoubleInt64::operator= (const UnsignedInt64 a)
{
	hi = 0;
	lo = a;

	return *this;
}

GS_FORCE_INLINE const SDoubleInt64& SDoubleInt64::operator+= (const SDoubleInt64& a)
{
	return *this = *this + a;
}

GS_FORCE_INLINE const SDoubleInt64& SDoubleInt64::operator-= (const SDoubleInt64& a)
{
	return *this = *this - a;
}

inline SDoubleInt64 SDoubleInt64::operator- () const
{
	SDoubleInt64 res;

	res.lo = ~lo;
	res.hi = ~hi;
	res.lo++;
	if (res.lo == 0)
		res.hi++;

	return res;
}

inline SDoubleInt64 SDoubleInt64::operator+ (const SDoubleInt64& op) const
{
	return SDoubleInt64 (UDoubleInt64 (*this) + UDoubleInt64 (op));
}

GS_FORCE_INLINE SDoubleInt64 SDoubleInt64::operator- (const SDoubleInt64& op) const
{
	return *this + -op;
}

GS_FORCE_INLINE bool SDoubleInt64::operator== (const SDoubleInt64& op) const
{
	return lo == op.lo && hi == op.hi;
}

GS_FORCE_INLINE bool SDoubleInt64::operator!= (const SDoubleInt64& op) const
{
	return !(*this == op);
}

inline bool SDoubleInt64::operator< (const SDoubleInt64& op) const
{
	return hi < op.hi || (hi == op.hi && lo < op.lo);
}

inline bool SDoubleInt64::operator<= (const SDoubleInt64& op) const
{
	return hi < op.hi || (hi == op.hi && lo <= op.lo);
}

GS_FORCE_INLINE bool SDoubleInt64::operator> (const SDoubleInt64& op) const
{
	return !(*this <= op);
}

GS_FORCE_INLINE bool SDoubleInt64::operator>= (const SDoubleInt64& op) const
{
	return !(*this < op);
}

inline SignedInt64 SDoubleInt64::operator/ (const SignedInt64 b) const
{
	UDoubleInt64 e;
	UnsignedInt64 f;
	bool pos;

	if (hi < 0)
		e = -*this, pos = false;
	else
		e = *this, pos = true;
	if (b < 0)
		f = -b, pos = !pos;
	else
		f = b;

	return pos ? SignedInt64 (e / f) : -SignedInt64 (e / f);
}

GS_FORCE_INLINE UDoubleInt64::UDoubleInt64 () : lo (0), hi (0)
{
}

GS_FORCE_INLINE UDoubleInt64::UDoubleInt64 (const UDoubleInt64& a)
{
	hi = a.hi;
	lo = a.lo;
}

GS_FORCE_INLINE UDoubleInt64::UDoubleInt64 (const SDoubleInt64& a)
{
	hi = UnsignedInt64 (a.hi);
	lo = a.lo;
}

GS_FORCE_INLINE UDoubleInt64::UDoubleInt64 (const UnsignedInt64 a)
{
	hi = 0;
	lo = a;
}

GS_FORCE_INLINE UDoubleInt64::UDoubleInt64 (const SignedInt64 a)
{
	hi = 0;
	lo = UnsignedInt64 (a);
}

GS_FORCE_INLINE const UDoubleInt64& UDoubleInt64::operator= (const UDoubleInt64& a)
{
	hi = a.hi;
	lo = a.lo;

	return *this;
}

GS_FORCE_INLINE const UDoubleInt64& UDoubleInt64::operator= (const SDoubleInt64& a)
{
	hi = UnsignedInt64 (a.hi);
	lo = a.lo;

	return *this;
}

GS_FORCE_INLINE const UDoubleInt64& UDoubleInt64::operator= (UnsignedInt64 a)
{
	hi = 0;
	lo = a;

	return *this;
}

GS_FORCE_INLINE const UDoubleInt64& UDoubleInt64::operator= (SignedInt64 a)
{
	hi = 0;
	lo = UnsignedInt64 (a);

	return *this;
}

GS_FORCE_INLINE SDoubleInt64 UDoubleInt64::operator- () const
{
	return -SDoubleInt64 (*this);
}

inline UDoubleInt64 UDoubleInt64::operator+ (const UDoubleInt64& op) const
{
#if defined (_MSC_VER) && !defined (_WIN64)
	UDoubleInt64 res;

	const Int32& a0 = ((Int32*)&lo)[0];
	const Int32& b0 = ((Int32*)&op.lo)[0];

	Int32& res0 = ((Int32*)&res.lo)[0];

	_asm
	{
		push edi;
		push esi;
		push ebx;
		push eax;

		mov edi, [a0];
		mov esi, [b0];
		mov ebx, [res0];

		mov eax, [edi];
		add eax, [esi];
		mov [ebx], eax;

		mov eax, [edi + 4];
		adc eax, [esi + 4];
		mov [ebx + 4], eax;

		mov eax, [edi + 8];
		adc eax, [esi + 8];
		mov [ebx + 8], eax;

		mov eax, [edi + 12];
		adc eax, [esi + 12];
		mov [ebx + 12], eax;

		pop eax;
		pop ebx;
		pop esi;
		pop edi;
	}

	return res;

#else
	UDoubleInt64 res;

	res.lo = lo + op.lo;
	res.hi = hi + op.hi;
	if ((((lo ^ op.lo) & ~res.lo) | (lo & op.lo)) & 0x8000000000000000ULL)
		res.hi++;

	return res;
#endif
}

inline UDoubleInt64 UDoubleInt64::operator- (const UDoubleInt64& op) const
{
#if defined (_MSC_VER) && !defined (_WIN64)
	UDoubleInt64 res;

	const Int32& a0 = ((Int32*)&lo)[0];
	const Int32& b0 = ((Int32*)&op.lo)[0];

	Int32& res0 = ((Int32*)&res.lo)[0];

	_asm
	{
		push edi;
		push esi;
		push ebx;
		push eax;

		mov edi, [a0];
		mov esi, [b0];
		mov ebx, [res0];

		mov eax, [edi];
		sub eax, [esi];
		mov [ebx], eax;

		mov eax, [edi + 4];
		sbb eax, [esi + 4];
		mov [ebx + 4], eax;

		mov eax, [edi + 8];
		sbb eax, [esi + 8];
		mov [ebx + 8], eax;

		mov eax, [edi + 12];
		sbb eax, [esi + 12];
		mov [ebx + 12], eax;

		pop eax;
		pop ebx;
		pop esi;
		pop edi;
	}

	return res;

#else
	UDoubleInt64 res;

	res.lo = lo - op.lo;
	res.hi = hi - op.hi;
	if ((((~lo ^ op.lo) & res.lo) | (~lo & op.lo)) & 0x8000000000000000ULL)
		res.hi--;

	return res;
#endif
}

GS_FORCE_INLINE bool UDoubleInt64::operator== (const UDoubleInt64& op) const
{
	return lo == op.lo && hi == op.hi;
}

GS_FORCE_INLINE bool UDoubleInt64::operator!= (const UDoubleInt64& op) const
{
	return !(*this == op);
}

inline bool UDoubleInt64::operator< (const UDoubleInt64& op) const
{
	return hi < op.hi || (hi == op.hi && lo < op.lo);
}

inline bool UDoubleInt64::operator<= (const UDoubleInt64& op) const
{
	return hi < op.hi || (hi == op.hi && lo <= op.lo);
}

GS_FORCE_INLINE bool UDoubleInt64::operator> (const UDoubleInt64& op) const
{
	return !(*this <= op);
}

GS_FORCE_INLINE bool UDoubleInt64::operator>= (const UDoubleInt64& op) const
{
	return !(*this < op);
}

inline UnsignedInt64 UDoubleInt64::operator/ (UnsignedInt64 b) const
{
	if (b == 0)
		throw GeometryAlgorithmErrorException ("Divide by 0", __FILE__, __LINE__);

	UDoubleInt64 a = *this + b / 2;

	if (a.hi == 0)
		return a.lo / b;

	if ((b & 0xffffffff00000000ULL) == 0) {
		b = b << 32;
		a.hi = (a.hi << 32) | (a.lo >> 32);
		a.lo = a.lo << 32;
	}
	if ((b & 0xffff000000000000ULL) == 0) {
		b = b << 16;
		a.hi = (a.hi << 16) | (a.lo >> 48);
		a.lo = a.lo << 16;
	}
	if ((b & 0xff00000000000000ULL) == 0) {
		b = b << 8;
		a.hi = (a.hi << 8) | (a.lo >> 56);
		a.lo = a.lo << 8;
	}
	if ((b & 0xf000000000000000ULL) == 0) {
		b = b << 4;
		a.hi = (a.hi << 4) | (a.lo >> 60);
		a.lo = a.lo << 4;
	}
	if ((b & 0xc000000000000000ULL) == 0) {
		b = b << 2;
		a.hi = (a.hi << 2) | (a.lo >> 62);
		a.lo = a.lo << 2;
	}
	if ((b & 0x8000000000000000ULL) == 0) {
		b = b << 1;
		a.hi = (a.hi << 1) | (a.lo >> 63);
		a.lo = a.lo << 1;
	}

	int i;
	UnsignedInt64 bh1 = (b >> 32) + 1;
	UnsignedInt64 d1 = a.hi / bh1;

	UDoubleInt64 aL32;
	aL32.hi = a.hi >> 32;
	aL32.lo = (a.hi << 32) | (a.lo >> 32);

	i = 0;
	while (Mul ((d1 + 1), b) <= aL32) {
		d1++;
		if (++i == 10)
			return UnsignedInt64 (SDoubleInt64::maxCoordVal);
	}

	if ((d1 & 0xffffffff00000000ULL) != 0)
		return UnsignedInt64 (SDoubleInt64::maxCoordVal);

	UDoubleInt64 rem = a - Mul ((d1 << 32), b);

	UnsignedInt64 d2 = ((rem.hi << 32) | (rem.lo >> 32)) / bh1;

	UnsignedInt64 res = (d1 << 32) | (d2 & 0xffffffff);
	i = 0;
	while (Mul ((res + 1), b) <= a) {
		res++;
		if (++i == 10)
			return UnsignedInt64 (SDoubleInt64::maxCoordVal);
	}

	return res;
}

inline SDoubleInt64 Mul (const SignedInt64 a, const SignedInt64 b)
{
	UnsignedInt64 e, f;
	bool pos;

	if (a < 0)
		e = -a, pos = false;
	else
		e = a, pos = true;
	if (b < 0)
		f = -b, pos = !pos;
	else
		f = b;

	return pos ? SDoubleInt64 (Mul (e, f)) : -Mul (e, f);
}

GS_FORCE_INLINE UDoubleInt64 Mul (const UnsignedInt64 a, const UnsignedInt64 b)
{
	UDoubleInt64 res;
	res.lo = QXTools::UMul128 (a, b, &res.hi);
	return res;
}

inline SignedInt64 Sqrt (const SDoubleInt64& a)
{
	if (a < SignedInt64 (0))
		throw GeometryAlgorithmErrorException ("Sqrt of negativ value", __FILE__, __LINE__);

	return SignedInt64 (Sqrt (UDoubleInt64 (a)));
}

inline UnsignedInt64 Sqrt (const UDoubleInt64& a)
{
	UnsignedInt64 max = 0xffffffffffffffffULL;
	UnsignedInt64 min = 0;

	while (max - min > 2) {
		UnsignedInt64 mid = max / 2 + min / 2;
		if (Mul (mid, mid) > a)
			max = mid;
		else
			min = mid;
	}

	if (max - min < 2)
		return min;
	if (Mul ((min + 1), (min + 1)) > a)
		return min;
	else
		return min + 1;
}

template<class DInt, class Int>
struct Point
{
	Int x, y;

	Point ();
	Point (Int x, Int y);

	Point operator+ (const Point&) const;
	Point operator- (const Point&) const;
	Point operator* (Int32) const;
	Point operator/ (Int32) const;
	const Point& operator+= (const Point&);
	const Point& operator-= (const Point&);
	bool operator== (const Point&) const;
	bool operator!= (const Point&) const;
	DInt operator* (const Point&) const;
	DInt operator^ (const Point&) const;
	DInt LenSqr () const;
	Int Len () const;
};

template<class Int>
struct BoundBox
{
	Int maxX, minX, maxY, minY;
};

template<class Int>
inline Int Abs (const Int &i)
{
	if (i < 0)
		return -i;
	else
		return i;
}

template<class Int>
inline QXTools::Integer<Int> Abs (const QXTools::Integer<Int> &i)
{
	return i.Abs ();
}

GS_FORCE_INLINE DInt64 Abs (const DInt64 &i)
{
	if (i < Int64 (0))
		return -i;
	else
		return i;
}

GS_FORCE_INLINE SDoubleInt32 Abs (const SDoubleInt32 &i)
{
	if (i < SignedInt32 (0))
		return -i;
	else
		return i;
}


template<class DInt, class Int>
GS_FORCE_INLINE Point<DInt,Int>::Point () : x (0), y (0)
{
}

template<class DInt, class Int>
GS_FORCE_INLINE Point<DInt,Int>::Point (Int x, Int y)
{
	this->x = x;
	this->y = y;
}

template<class DInt, class Int>
inline Point<DInt,Int> Point<DInt,Int>::operator+ (const Point<DInt,Int>& v) const
{
	Point<DInt,Int> p;
	p.x = x + v.x;
	p.y = y + v.y;
	return p;
}

template<class DInt, class Int>
inline Point<DInt,Int> Point<DInt,Int>::operator- (const Point<DInt,Int>& v) const
{
	Point<DInt,Int> p;
	p.x = x - v.x;
	p.y = y - v.y;
	return p;
}

template<class DInt, class Int>
inline Point<DInt,Int> Point<DInt,Int>::operator* (Int32 a) const
{
	Point<DInt,Int> p;
	p.x = x * a;
	p.y = y * a;
	return p;
}

template<class DInt, class Int>
inline Point<DInt,Int> Point<DInt,Int>::operator/ (Int32 a) const
{
	Point<DInt,Int> p;
	p.x = x / a;
	p.y = y / a;
	return p;
}

template<class DInt, class Int>
GS_FORCE_INLINE const Point<DInt,Int>& Point<DInt,Int>::operator+= (const Point<DInt,Int>& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

template<class DInt, class Int>
GS_FORCE_INLINE const Point<DInt,Int>& Point<DInt,Int>::operator-= (const Point<DInt,Int>& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

template<class DInt, class Int>
GS_FORCE_INLINE bool Point<DInt,Int>::operator== (const Point<DInt,Int>& v) const
{
	return x == v.x && y == v.y;
}

template<class DInt, class Int>
GS_FORCE_INLINE bool Point<DInt,Int>::operator!= (const Point<DInt,Int>& v) const
{
	return x != v.x || y != v.y;
}

template<class DInt, class Int>
inline DInt Point<DInt,Int>::operator* (const Point<DInt,Int>& v) const
{
	return Mul (x, v.x) + Mul (y, v.y);
}

template<class DInt, class Int>
inline DInt Point<DInt,Int>::operator^ (const Point<DInt,Int>& v) const
{
	return Mul (x, v.y) - Mul (y, v.x);
}

template<class DInt, class Int>
GS_FORCE_INLINE DInt Point<DInt,Int>::LenSqr () const
{
	return *this * *this;
}

template<class DInt, class Int>
inline Int Point<DInt,Int>::Len () const
{
	return Sqrt (LenSqr ());
}

}

#endif
