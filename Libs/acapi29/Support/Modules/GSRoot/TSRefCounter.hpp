
// *****************************************************************************
//
//                              Class TSRefCounter
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined TSREFCOUNTER_HPP
#define TSREFCOUNTER_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"
#include "GSRootExport.hpp"



// ============================ Class TSRefCounter =============================

namespace GS {

class GSROOT_DLL_EXPORT TSRefCounter {	// thread safe reference counter - it has atomic operations
private:
	volatile Int32	refCounter;		// the reference counter

public:
	inline TSRefCounter ();
	inline explicit TSRefCounter (Int32 initialValue);

	Int32	operator++ ();
	Int32	operator-- ();

	inline Int32		UnsafeIncrementIf1 (void);
	inline Int32		UnsafeDecrementIf1 (void);

	inline bool		operator== (Int32 rightOp) const;
	inline bool		operator!= (Int32 rightOp) const;
	inline bool		operator>  (Int32 rightOp) const;
	inline bool		operator>= (Int32 rightOp) const;
	inline bool		operator<  (Int32 rightOp) const;
	inline bool		operator<= (Int32 rightOp) const;

	inline void		SetValue (Int32 newValue);
	inline Int32		GetValue (void) const;
};

}	// namespace GS



inline GS::TSRefCounter::TSRefCounter ():
	refCounter (0)
{
}


inline GS::TSRefCounter::TSRefCounter (Int32 initialValue):
	refCounter (initialValue)
{
}


inline Int32		GS::TSRefCounter::UnsafeIncrementIf1 (void)
{
	if (refCounter == 1)
		return ++refCounter;
	else
		return operator++ ();
}


inline Int32		GS::TSRefCounter::UnsafeDecrementIf1 (void)
{
	if (refCounter == 1)
		return --refCounter;
	else
		return operator-- ();
}


inline bool		GS::TSRefCounter::operator== (Int32 rightOp) const
{
	return (refCounter == rightOp);
}


inline bool		GS::TSRefCounter::operator!= (Int32 rightOp) const
{
	return (refCounter != rightOp);
}


inline bool		GS::TSRefCounter::operator>  (Int32 rightOp) const
{
	return (refCounter > rightOp);
}


inline bool		GS::TSRefCounter::operator>= (Int32 rightOp) const
{
	return (refCounter >= rightOp);
}


inline bool		GS::TSRefCounter::operator<  (Int32 rightOp) const
{
	return (refCounter < rightOp);
}


inline bool		GS::TSRefCounter::operator<= (Int32 rightOp) const
{
	return (refCounter <= rightOp);
}


inline void		GS::TSRefCounter::SetValue (Int32 newValue)
{
	refCounter = newValue;
}


inline Int32		GS::TSRefCounter::GetValue (void) const
{
	return refCounter;
}
// ____________________________ Class TSRefCounter _____________________________


#endif
