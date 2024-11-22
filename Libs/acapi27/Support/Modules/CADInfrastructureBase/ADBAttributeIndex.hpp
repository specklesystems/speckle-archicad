// *****************************************************************************
// Attribute Index Reference
// AttributeManager, platform-independent
//
// Namespaces:        Contact person:
//		ADB					JG
//
// [SG compatible]
// *****************************************************************************

#if !defined (ADBATTRIBUTEINDEX_HPP)
#define ADBATTRIBUTEINDEX_HPP

#pragma once

#include "CADInfrastructureExport.hpp"

// from GSRoot
#include "Object.hpp"
#include "HashCommon.hpp"

typedef GSIndex GSAttributeIndex;

namespace ADB {

class CADINFRASTRUCTURE_DLL_EXPORT AttributeIndex
{
	static GS::ClassInfo	classInfo;
private:
	GSAttributeIndex		attributeIndex;

public:
	AttributeIndex ();
	AttributeIndex (const GSAttributeIndex& gsAttrInd);

	AttributeIndex&			operator= (const GSAttributeIndex& value);

	inline bool				operator== (const AttributeIndex& rightOp) const	{	return (attributeIndex == rightOp.attributeIndex);	}
	inline bool				operator!= (const AttributeIndex& rightOp) const	{	return !(attributeIndex == rightOp.attributeIndex);	}
	
	GSAttributeIndex		ToGSAttributeIndex (void) const;
	GS::UniString			ToUniString (void) const;

	ULong					GenerateHashValue (void) const;

	// I/O methods
	GSErrCode				Read (GS::IChannel& ic);
	GSErrCode				Write (GS::OChannel& oc) const;
    GS::ErrorStatus			Store   (GS::ObjectState& os) const;
    GS::ErrorStatus			Restore (const GS::ObjectState& os);

	// Compatibility methods
	GSErrCode				ReadAsShortInteger (GS::IChannel& ic);
	GSErrCode				WriteAsShortInteger (GS::OChannel& oc) const;
	GSErrCode				ReadAsGSAttributeIndex (GS::IChannel& ic);
	GSErrCode				WriteAsGSAttributeIndex (GS::OChannel& oc) const;

	// XML I/O methods
	GSErrCode				ReadXML (GS::XMLIChannel& ic, const char* tagName);
	GSErrCode				WriteXML (GS::XMLOChannel& oc, const char* tagName) const;
	GSErrCode				ReadXMLAttr (GS::XMLIChannel& ic, const char* tagName);
	GSErrCode				WriteXMLAttr (GS::XMLOChannel& oc, const char* tagName) const;

	// Debug
	void					Print (GS::OChannel& oc) const;
};


CADINFRASTRUCTURE_DLL_EXPORT extern const AttributeIndex	InvalidAttributeIndex;
CADINFRASTRUCTURE_DLL_EXPORT extern const AttributeIndex	SolidLineAttributeIndex;
CADINFRASTRUCTURE_DLL_EXPORT extern const AttributeIndex	MissingFillAttributeIndex;

CADINFRASTRUCTURE_DLL_EXPORT AttributeIndex	GenerateUniqueAttributeIndex (const GS::HashSet<AttributeIndex>&	indicesAlreadyUsed,
																  const AttributeIndex&					searchStartsFromIndex = InvalidAttributeIndex);

class AttributeIndexComparator {

public:

	AttributeIndexComparator () = default;
	~AttributeIndexComparator () = default;

	bool operator() (const ADB::AttributeIndex& index1, const ADB::AttributeIndex& index2) const {
		return index1.ToGSAttributeIndex () < index2.ToGSAttributeIndex ();
	}

	static bool IsEqual (const ADB::AttributeIndex& index1, const ADB::AttributeIndex& index2) {
		return index1.ToGSAttributeIndex () == index2.ToGSAttributeIndex ();
	}

	static bool IsLess (const ADB::AttributeIndex& index1, const ADB::AttributeIndex& index2) {
		return index1.ToGSAttributeIndex () < index2.ToGSAttributeIndex ();
	}

	
};

}	// namespace ADB



#endif
