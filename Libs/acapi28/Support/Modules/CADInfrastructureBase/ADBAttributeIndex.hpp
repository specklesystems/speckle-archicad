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


namespace ADB {

class CADINFRASTRUCTURE_DLL_EXPORT AttributeIndex
{
	static GS::ClassInfo	classInfo;
private:
	Int32					attributeIndex;

	friend CADINFRASTRUCTURE_DLL_EXPORT AttributeIndex	CreateAttributeIndex (Int32 index);
	friend CADINFRASTRUCTURE_DLL_EXPORT AttributeIndex	CreateCompositeIndex_Deprecated (Int32 index);
	friend CADINFRASTRUCTURE_DLL_EXPORT AttributeIndex	CreateCompositeIndex_Deprecated (const AttributeIndex& index);
	friend CADINFRASTRUCTURE_DLL_EXPORT AttributeIndex	CreateCompositeIndexFromOldIndex_Deprecated (const AttributeIndex& index);

public:
	AttributeIndex ();

	bool					operator== (const AttributeIndex& rightOp) const;
	bool					operator!= (const AttributeIndex& rightOp) const;
	
	Int32					ToGSAttributeIndex_Deprecated (void) const;
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
CADINFRASTRUCTURE_DLL_EXPORT extern const AttributeIndex	GeneralLayerAttributeIndex;
CADINFRASTRUCTURE_DLL_EXPORT extern const AttributeIndex	MissingFillAttributeIndex;
CADINFRASTRUCTURE_DLL_EXPORT extern const AttributeIndex	GeneralMaterialAttributeIndex;

CADINFRASTRUCTURE_DLL_EXPORT AttributeIndex					CreateAttributeIndex		(Int32 index);
CADINFRASTRUCTURE_DLL_EXPORT short							LayerIndexAsFragmentIndex	(const AttributeIndex& index);
CADINFRASTRUCTURE_DLL_EXPORT AttributeIndex					FragmentIndexAsLayerIndex	(short fragmentIndex);


CADINFRASTRUCTURE_DLL_EXPORT AttributeIndex	GenerateUniqueAttributeIndex (const GS::HashSet<AttributeIndex>&	indicesAlreadyUsed,
																		  const AttributeIndex&					searchStartsFromIndex = InvalidAttributeIndex);

class CADINFRASTRUCTURE_DLL_EXPORT AttributeIndexComparator
{
public:
	AttributeIndexComparator () = default;
	~AttributeIndexComparator () = default;

	bool operator()		(const AttributeIndex& index1, const AttributeIndex& index2) const;

	static bool IsEqual	(const AttributeIndex& index1, const AttributeIndex& index2);

	static bool IsLess	(const AttributeIndex& index1, const AttributeIndex& index2);
};


// deprecated functions, do not use in new code!
CADINFRASTRUCTURE_DLL_EXPORT AttributeIndex CreateCompositeIndex_Deprecated				(Int32 index);
CADINFRASTRUCTURE_DLL_EXPORT AttributeIndex CreateCompositeIndex_Deprecated				(const AttributeIndex& index);
CADINFRASTRUCTURE_DLL_EXPORT AttributeIndex CreateCompositeIndexFromOldIndex_Deprecated	(const AttributeIndex& index);
CADINFRASTRUCTURE_DLL_EXPORT bool			IsCompositeIndex_Deprecated					(const AttributeIndex& index);


CADINFRASTRUCTURE_DLL_EXPORT AttributeIndex	IVAttributeIndex_Deprecated					(GS::PlatformSign inplatform, const AttributeIndex& index);
CADINFRASTRUCTURE_DLL_EXPORT AttributeIndex	IVAttributeIndex_Deprecated					(GS::PlatformSign from, GS::PlatformSign to, const AttributeIndex& index);


}	// namespace ADB



#endif
