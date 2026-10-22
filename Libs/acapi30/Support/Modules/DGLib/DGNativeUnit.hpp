// *********************************************************************************************************************
// File:			DGNativeUnit.hpp
//
// Description:		Main include file of the GRAPHISOFT Dialog Manager
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Contact person:	VM
// *********************************************************************************************************************

#ifndef DG_NATIVE_UNIT_HPP
#define DG_NATIVE_UNIT_HPP

#pragma once

#include "DGDLLExport.h"

// === class NativeUnit ================================================================================================

namespace DG
{

class DG_DLL_EXPORT NativeUnit
{
private:
	short value;

public:
	NativeUnit (): value (0) { }
	explicit NativeUnit (short value) { this->value = value; }
	explicit NativeUnit (short value, double scale);
	bool operator== (const NativeUnit& rightOp) const { return value == rightOp.value; }
	bool operator!= (const NativeUnit& rightOp) const { return value != rightOp.value; }
	bool operator> (const NativeUnit& rightOp) const { return value > rightOp.value; }
	bool operator>= (const NativeUnit& rightOp) const { return value >= rightOp.value; }
	bool operator< (const NativeUnit& rightOp) const { return value < rightOp.value; }
	bool operator<= (const NativeUnit& rightOp) const { return value <= rightOp.value; }

	NativeUnit& operator+= (const NativeUnit& rightOp) { value += rightOp.value; return *this; }
	NativeUnit& operator-= (const NativeUnit& rightOp) { value -= rightOp.value; return *this; }

	NativeUnit operator+ (const NativeUnit& rightOp) const { return NativeUnit (value + rightOp.value); }
	NativeUnit operator- (const NativeUnit& rightOp) const { return NativeUnit (value - rightOp.value); }
	NativeUnit operator/ (short rightOp) const { return NativeUnit (value / rightOp); }
	NativeUnit operator* (short rightOp) const { return NativeUnit (value * rightOp); }
	NativeUnit operator- () const { return NativeUnit (-value); }	// Unary minus

	void	Add (const NativeUnit& unit) { value += unit.value; }
	short	GetValue (void) const { return value; }

	GSErrCode	Read (GS::IChannel& ic) { GSErrCode result = ic.Read (value); return result; }
	GSErrCode	Write (GS::OChannel& oc) const { return oc.Write (value); }
};

}


#endif
