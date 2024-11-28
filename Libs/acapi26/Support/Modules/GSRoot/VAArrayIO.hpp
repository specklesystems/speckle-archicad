// *********************************************************************************************************************
// Description:		VAArray Read / Write
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	FGY
//
// SG compatible
// *********************************************************************************************************************

#if !defined (VAARRAYIO_HPP)
#define VAARRAYIO_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"vaarray.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace GS {

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------


template<class Type>
GSErrCode ReadVAArray (GS::VAArray<Type>* array, GS::IChannel& ic)
{
	GSErrCode	err;
	short		version;

	array->Clear ();
	VAFree (&array->desc);
	array->desc.size = sizeof (Type);

	err = ic.Read (version);
	if (err != NoError) {
		return err;
	}
	switch (version) {
		case 1: {
			err = ic.Read (array->desc.lastind);
			array->desc.maxind = array->desc.lastind;
			if (err == NoError)
				err = ic.Read (array->desc.npage);
			if (err == NoError) {
				Int32 longValue;
				err = ic.Read (longValue);
			}

			array->desc.arrhdl = BMXhAll ((array->desc.maxind + 1) * array->desc.size);
			BNZeroMemory (*array->desc.arrhdl, array->desc.size);
			if (err == NoError) {
				for (UIndex idx = 1; idx <= static_cast<USize> (array->desc.lastind); idx++) {
					Type& elemRef = reinterpret_cast<Type*>(*array->desc.arrhdl) [idx];
					new (*array->desc.arrhdl + idx * sizeof (Type)) Type;
					err = ic.Read (elemRef);
					if (err != NoError) {
						array->desc.lastind = idx;
						break;
					}
				}
			}
#if defined (DEBUVERS)
			if (array->desc.arrhdl != nullptr) {
				array->itemArray = reinterpret_cast<Type*> (*array->desc.arrhdl);
			}
#endif
		}
		break;

		default:
			err = Error;
	}

	return err;
}


template<class Type>
GSErrCode WriteVAArray (const GS::VAArray<Type>& array, GS::OChannel& oc)
{
	GSErrCode	err;
	short		version = 1;

	err = oc.Write (version);		// currVersion
	if (err == NoError)
		err = oc.Write (array.desc.lastind);
	if (err == NoError)
		err = oc.Write (array.desc.npage);
	if (err == NoError)
		err = oc.Write (array.desc.size);

	if (err == NoError) {
		for (UIndex idx = 1; idx <= static_cast<USize> (array.desc.lastind); idx++) {
			Type* elemRef = reinterpret_cast<Type*>(*array.desc.arrhdl) + idx;
			err = oc.Write (*elemRef);
		}
	}

	return err;
}

}	// namespace GS

#endif /* VAARRAYIO_HPP */
