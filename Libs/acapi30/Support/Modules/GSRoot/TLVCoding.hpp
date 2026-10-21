
// *****************************************************************************
// Description:		Type-Length-Value serialization
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
// *****************************************************************************


#ifndef TLVCODING_HPP
#define TLVCODING_HPP


// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"

#include "Channel.hpp"
#include "TypeTraits.hpp"


// =============================================================================

namespace GS {

namespace TLV {

template <bool IsFunctor>
struct Writer;

template <>
struct Writer<false> {
	template <class Type>
	static GSErrCode	Do (GS::OChannel& oc, const Type& value) { return oc.Write (value); }
};


template <>
struct Writer<true> {
	template <class ValueWriter>
	static GSErrCode	Do (GS::OChannel& oc, const ValueWriter& valueWriter) { return valueWriter (oc); }
};


template <class Type>
inline GSErrCode	Write (GS::OChannel& oc, const GS::Guid& typeId, const Type& value)		// accepts types that can be written to OChannel and lambdas (functors) of type: [] (GS::OChannel& oc) -> GSErrCode { ... }
{
	oc.Write (typeId);

	oc.OpenBlock ();
	GSErrCode errorCode = Writer<IsInvocableR<GSErrCode, Type, GS::OChannel&>>::Do (oc, value);
	oc.CloseBlock ();

	if (errorCode != NoError)
		return errorCode;
	else
		return oc.GetOutputStatus ();
}

}	// namespace TLV

}	// namespace GS

#endif
