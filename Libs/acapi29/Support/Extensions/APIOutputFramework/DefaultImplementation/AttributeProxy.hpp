#ifndef __ATTRIBUTEPROXY_HPP__
#define __ATTRIBUTEPROXY_HPP__

#include "APIFunctionsEnvironment.hpp"

// Framework includes
#include "IAttributeProxy.hpp"
#include "DatabaseGraph.hpp"
#include "GlobalOperators.hpp"
#include "LazySortedArray.hpp"

#include "HashTable.hpp"
#include "ProfileVectorImage.hpp"

namespace GSAPI {

// predeclarations
class IDatabaseSelector;


template <typename SelectorType>
class AttributeProxy : public IAttributeProxy
{
private:
	enum LoadAttributePartType {
		LoadOnlyAttribute,
		LoadOnlyAttributeDefExt,
		LoadBoth
	};

	struct AttributeDefinition {
	public:
		API_Attribute		attribute;
		API_AttributeDefExt	definition;

	public:
		AttributeDefinition () {
			attribute = {};
			definition = {};
		}

		bool operator< (const AttributeDefinition& attributeDef) const { return (attribute.header.index.ToInt32_Deprecated () < attributeDef.attribute.header.index.ToInt32_Deprecated ()); }
	};

	struct UsedAttributes {
	public:
		bool										listIsUnsorted;
		GS::HashTable<API_AttributeIndex, UIndex>	usedIndices;
		GS::Array<AttributeDefinition>				attributeList;

	public:
		UsedAttributes () : usedIndices (), attributeList (), listIsUnsorted (false) {}

		void SortIfNecessary (void) const	// const, so that the container interface stays consistent
		{
			if (listIsUnsorted) {
				UsedAttributes* object = const_cast<UsedAttributes*> (this);	// ugly hack
				GS::Sort (object->attributeList.Begin (), object->attributeList.End ());

				USize attributeCount = object->attributeList.GetSize ();
				object->usedIndices.Clear ();
				for (UIndex i = 0; i <  attributeCount; ++i) {
					object->usedIndices.Put (attributeList[i].attribute.header.index, i);
				}
				object->listIsUnsorted = false;
			}
		}
	};

private:
	// API_DatabaseUnIds, because we cannot handle drawing databases separately from their containing databases
    GS::HashTable<API_DatabaseUnId, bool>													outputInDatabases;

	GS::HashTable<API_DatabaseInfo, GS::ArrayFB <UsedAttributes, API_LastAttributeID + 1> >	attributeHash;
	GSAPI::LazySortedArray<API_DatabaseInfo>												usedDatabases;
	API_Attribute																			emptyAttribute;
	API_AttributeDefExt																		emptyAttributeDefExt;

private:
	void				CheckTemplateType (GSAPI::IDatabaseSelector*) {}
	UIndex				GetNextOutputDatabase (const API_DatabaseInfo& dbInfo) const;
	API_AttrTypeID		GetNextOutputAttributeType (const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType) const;
	API_AttributeIndex	GetNextOutputAttributeIndex (const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index) const;
	API_Attribute		GetEndAttribute (API_DatabaseInfo& dbInfo) const;

	GSErrCode			LoadAttribute (const API_DatabaseInfo& dbInfo, API_Attribute& attribute, API_AttributeDefExt& attributeDefExt, LoadAttributePartType loadWhat = LoadBoth) const;
	void				SetUsedDependentAttributes (const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index);
	API_AttributeDefExt	CopyAttributeDefExt (const API_AttributeDefExt& attributeDef) const;

public:
	AttributeProxy ();

	virtual ~AttributeProxy ();

	// IAPIPseudoContainer interface
	virtual void GetNext (GSAPI::IteratorElem <API_Attribute>&) const override;

    virtual PseudoIterator Begin () const override;
    virtual const PseudoIterator End () const override;

	// IAttributeProxy interface
	virtual void						SetUsedAttribute			(const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index) override;
    virtual API_Attribute				GetAttribute				(const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index) const override;
	virtual const API_Attribute&		GetProxiedAttribute			(const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index) const override;
	virtual API_AttributeDefExt			GetAttributeDefExt			(const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index) const override;
	virtual const API_AttributeDefExt&	GetProxiedAttributeDefExt	(const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index) const override;
	virtual GS::UniString				GetAttributeName			(const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index) const override;
	virtual GS::UniString				GetProxiedAttributeName		(const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index) const override;

	virtual PseudoIterator Begin (const API_DatabaseUnId& dbUnId) const override;
    virtual const PseudoIterator End (const API_DatabaseUnId& dbUnId) const override;

	virtual PseudoIterator Begin (const API_DatabaseInfo& dbInfo) const override;
    virtual const PseudoIterator End (const API_DatabaseInfo& dbInfo) const override;

	virtual PseudoIterator Begin (const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType) const override;
    virtual const PseudoIterator End (const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType) const override;
};

}


template <typename SelectorType>
GSAPI::AttributeProxy<SelectorType>::AttributeProxy ()
{
	CheckTemplateType ((SelectorType*) nullptr);

	BNFillMemory (&(this->typeFilter), sizeof (this->typeFilter), 1);

	SelectorType selector;
	GS::Array<API_DatabaseInfo> dbList = DatabaseGraph::Instance ().SelectDatabases (selector);

	GS::Array<API_DatabaseInfo>::Iterator dbListIt  = dbList.Begin ();
	GS::Array<API_DatabaseInfo>::Iterator dbListEnd = dbList.End ();
	for (; dbListIt != dbListEnd; ++dbListIt) {
		outputInDatabases.Put (StripDatabaseUnId (dbListIt->databaseUnId), true);
	}

	emptyAttribute = {};
	emptyAttribute.header.typeID = API_ZombieAttrID;
	emptyAttributeDefExt = {};
}


template <typename SelectorType>
GSAPI::AttributeProxy<SelectorType>::~AttributeProxy ()
{
	typename GS::HashTable<API_DatabaseInfo, GS::ArrayFB <UsedAttributes, API_LastAttributeID + 1> >::ValueIterator it;
	typename GS::HashTable<API_DatabaseInfo, GS::ArrayFB <UsedAttributes, API_LastAttributeID + 1> >::ValueIterator lastIt = attributeHash.EndValues ();
	for (it = attributeHash.BeginValues (); it != lastIt; ++it) {
		GS::ArrayFB <UsedAttributes, API_LastAttributeID + 1>& typeArray = *it;
		for (API_AttrTypeID attributeType = API_FirstAttributeID; attributeType <= API_LastAttributeID; attributeType = static_cast<API_AttrTypeID> (static_cast<int> (attributeType) + 1)) {
			GS::Array<AttributeDefinition>&	attributeList  = typeArray[attributeType].attributeList;
			USize							attributeCount = attributeList.GetSize ();
			for (UIndex i = 0; i < attributeCount; ++i) {
				if ((attributeList[i].attribute.header.typeID == API_MaterialID) &&
					(attributeList[i].attribute.material.texture.fileLoc != nullptr))
				{
					delete attributeList[i].attribute.material.texture.fileLoc;
				}
				ACAPI_DisposeAttrDefsHdlsExt (&(attributeList[i].definition));
			}
		}
	}
}


template <typename SelectorType>
GSErrCode GSAPI::AttributeProxy<SelectorType>::LoadAttribute (const API_DatabaseInfo& dbInfo, API_Attribute& attribute, API_AttributeDefExt& attributeDefExt, LoadAttributePartType loadWhat /*= LoadBoth*/) const
{
	API_DatabaseInfo savedDatabaseInfo = {};

	GSErrCode gsError = ACAPI_Database_GetCurrentDatabase (&savedDatabaseInfo);
    if (gsError != NoError) {
        // TODO: throw exception
        return gsError;
    }

	if (dbInfo.databaseUnId != savedDatabaseInfo.databaseUnId) {
		// shouldn't come here, but let's handle the situation...
		API_DatabaseInfo databaseInfo = dbInfo;
		gsError = ACAPI_Database_ChangeCurrentDatabase (&databaseInfo);
		if (gsError != NoError) {
			// TODO: throw exception
			return gsError;
		}
	}

	API_AttrTypeID		attributeType  = attribute.header.typeID;
	API_AttributeIndex	attributeIndex = attribute.header.index;

	attribute = {};
	attribute.header.typeID = attributeType;
	attribute.header.index = attributeIndex;

	if ((loadWhat == LoadOnlyAttribute) || (loadWhat == LoadBoth)) {
		gsError = ACAPI_Attribute_Get (&attribute);
		if (gsError != NoError) {
			// TODO: report error
			attribute = {};
			attribute.header.typeID = API_ZombieAttrID;
			attribute.header.index = APIInvalidAttributeIndex;
		}
	}

	attributeDefExt = {};
	if ((gsError == NoError) && ((loadWhat == LoadOnlyAttributeDefExt) || (loadWhat == LoadBoth))) {
		GSErrCode attributeErr = ACAPI_Attribute_GetDefExt (attributeType, attributeIndex, &attributeDefExt);
		if ((attributeErr != NoError) && (attributeErr != APIERR_BADID)) {
			// TODO: report error
			gsError = attributeErr;
			attributeDefExt = {};
		}
	}

	// switch back if necessary
	if (dbInfo.databaseUnId != savedDatabaseInfo.databaseUnId) {
		// shouldn't come here, but let's handle the situation...
		GSErrCode dbError = ACAPI_Database_ChangeCurrentDatabase (&savedDatabaseInfo);
		if (dbError != NoError) {
			// TODO: throw exception
			if (gsError == NoError) {
				gsError = dbError;
			}
		}
	}

	return gsError;
}


template <typename SelectorType>
void GSAPI::AttributeProxy<SelectorType>::SetUsedDependentAttributes (const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index)
{
	if ((attributeType == API_CompWallID) || (attributeType == API_ZoneCatID) || (attributeType == API_LayerCombID)) {
		GSErrCode           attributeErr = NoError;
		API_AttributeDefExt attributeDefExt = {};

		attributeErr = ACAPI_Attribute_GetDefExt (attributeType, index, &attributeDefExt);
		if (attributeErr != NoError) {
			// TODO: report error
		} else {
			if ((attributeDefExt.cwall_compItems != nullptr) && (*attributeDefExt.cwall_compItems != nullptr)) {
				Int32 num = BMGetHandleSize (reinterpret_cast<GSHandle> (attributeDefExt.cwall_compItems)) / sizeof (API_CWallComponent);
				for (Int32 i = 0; i < num; ++i) {
					SetUsedAttribute (dbInfo, API_BuildingMaterialID, (*attributeDefExt.cwall_compItems)[i].buildingMaterial);
				}
			}
			if ((attributeDefExt.cwall_compLItems != nullptr) && (*attributeDefExt.cwall_compLItems != nullptr)) {
				Int32 num = BMGetHandleSize (reinterpret_cast<GSHandle> (attributeDefExt.cwall_compLItems)) / sizeof (API_CWallLineComponent);
				for (Int32 i = 0; i < num; ++i) {
					SetUsedAttribute (dbInfo, API_LinetypeID, (*attributeDefExt.cwall_compLItems)[i].ltypeInd);
				}
			}
			if (attributeDefExt.layer_statItems != nullptr) {
				for (auto it = attributeDefExt.layer_statItems->BeginKeys (); it != nullptr; ++it) {
					SetUsedAttribute (dbInfo, API_LayerID, *it);
				}
			}
			ACAPI_DisposeAttrDefsHdlsExt (&attributeDefExt);
		}
	}
}


template <typename SelectorType>
void GSAPI::AttributeProxy<SelectorType>::SetUsedAttribute (const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index)
{
	if ((attributeType < API_FirstAttributeID) ||
		(attributeType > API_LastAttributeID))
	{
		return;
	}

	SetUsedDependentAttributes (dbInfo, attributeType, index);

	if (!this->typeFilter[attributeType]) {
		return;
	}

	API_DatabaseInfo strippedDBInfo = StripDatabaseInfo (dbInfo);
    if (attributeHash.ContainsKey (strippedDBInfo)) {
        UsedAttributes& usedAttributes = attributeHash[strippedDBInfo][attributeType];
        if (!usedAttributes.usedIndices.ContainsKey (index)) {
			AttributeDefinition attributeDef = {};
			attributeDef.attribute.header.typeID = attributeType;
			attributeDef.attribute.header.index = index;
			if (LoadAttribute (dbInfo, attributeDef.attribute, attributeDef.definition) == NoError) {
				usedAttributes.usedIndices.Put (index, static_cast<short> (usedAttributes.attributeList.GetSize ()));
				usedAttributes.attributeList.Push (attributeDef);
				usedAttributes.listIsUnsorted = true;
			}
        }
    } else {
		AttributeDefinition attributeDef = {};
		attributeDef.attribute.header.typeID = attributeType;
		attributeDef.attribute.header.index = index;
		if (LoadAttribute (dbInfo, attributeDef.attribute, attributeDef.definition) == NoError) {
			GS::ArrayFB<UsedAttributes, API_LastAttributeID + 1> startList;
			startList.SetSize (API_LastAttributeID + 1);
			startList[attributeType].usedIndices.Put (index, 0);
			startList[attributeType].attributeList.Push (attributeDef);
			attributeHash.Put (strippedDBInfo, startList);
			usedDatabases.Push (strippedDBInfo);
		}
    }
}


template <typename SelectorType>
API_Attribute GSAPI::AttributeProxy<SelectorType>::GetAttribute (const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index) const
{
	API_DatabaseInfo strippedDBInfo = StripDatabaseInfo (dbInfo);
    if (attributeHash.ContainsKey (strippedDBInfo)) {
        const UsedAttributes& usedAttributes = attributeHash[strippedDBInfo][attributeType];
        if (usedAttributes.usedIndices.ContainsKey (index)) {
			return usedAttributes.attributeList[usedAttributes.usedIndices[index]].attribute;
		}
	}

	API_Attribute		attribute = {};
	API_AttributeDefExt attributeDefExt = {};
	if (LoadAttribute (dbInfo, attribute, attributeDefExt, LoadOnlyAttribute) != NoError)
		attribute = {};

	return attribute;
}


template <typename SelectorType>
const API_Attribute& GSAPI::AttributeProxy<SelectorType>::GetProxiedAttribute (const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index) const
{
	API_DatabaseInfo strippedDBInfo = StripDatabaseInfo (dbInfo);
    if (attributeHash.ContainsKey (strippedDBInfo)) {
        const UsedAttributes& usedAttributes = attributeHash[strippedDBInfo][attributeType];
        if (usedAttributes.usedIndices.ContainsKey (index)) {
			return usedAttributes.attributeList[usedAttributes.usedIndices[index]].attribute;
		}
	}

	return emptyAttribute;
}


template <typename SelectorType>
API_AttributeDefExt GSAPI::AttributeProxy<SelectorType>::CopyAttributeDefExt (const API_AttributeDefExt& attributeDef) const
{
	API_AttributeDefExt attributeDefExt = {};

	if ((attributeDef.ltype_dashItems != nullptr) && (*(attributeDef.ltype_dashItems) != nullptr)) {
		attributeDefExt.ltype_dashItems = reinterpret_cast<API_DashItems**> (BMAllocateHandle (BMGetHandleSize (reinterpret_cast<GSHandle> (attributeDef.ltype_dashItems)), ALLOCATE_CLEAR, 0));
		BMHandleToHandle (reinterpret_cast<GSHandle> (attributeDef.ltype_dashItems),  reinterpret_cast<GSHandle*> (&(attributeDefExt.ltype_dashItems)));
	}

	if ((attributeDef.ltype_lineItems != nullptr) && (*(attributeDef.ltype_lineItems) != nullptr)) {
		attributeDefExt.ltype_lineItems = reinterpret_cast<API_LineItems**> (BMAllocateHandle (BMGetHandleSize (reinterpret_cast<GSHandle> (attributeDef.ltype_lineItems)), ALLOCATE_CLEAR, 0));
		BMHandleToHandle (reinterpret_cast<GSHandle> (attributeDef.ltype_lineItems),  reinterpret_cast<GSHandle*> (&(attributeDefExt.ltype_lineItems)));
	}

	if ((attributeDef.fill_lineItems != nullptr) && (*(attributeDef.fill_lineItems) != nullptr)) {
		attributeDefExt.fill_lineItems = reinterpret_cast<API_FillLine**> (BMAllocateHandle (BMGetHandleSize (reinterpret_cast<GSHandle> (attributeDef.fill_lineItems)), ALLOCATE_CLEAR, 0));
		BMHandleToHandle (reinterpret_cast<GSHandle> (attributeDef.fill_lineItems),  reinterpret_cast<GSHandle*> (&(attributeDefExt.fill_lineItems)));
	}

	if ((attributeDef.fill_lineLength != nullptr) && (*(attributeDef.fill_lineLength) != nullptr)) {
		attributeDefExt.fill_lineLength = reinterpret_cast<double**> (BMAllocateHandle (BMGetHandleSize (reinterpret_cast<GSHandle> (attributeDef.fill_lineLength)), ALLOCATE_CLEAR, 0));
		BMHandleToHandle (reinterpret_cast<GSHandle> (attributeDef.fill_lineLength),  reinterpret_cast<GSHandle*> (&(attributeDefExt.fill_lineLength)));
	}

	if ((attributeDef.sfill_Items.sfill_HotSpots != nullptr) && (*(attributeDef.sfill_Items.sfill_HotSpots) != nullptr)) {
		attributeDefExt.sfill_Items.sfill_HotSpots = reinterpret_cast<API_Coord**> (BMAllocateHandle (BMGetHandleSize (reinterpret_cast<GSHandle> (attributeDef.sfill_Items.sfill_HotSpots)), ALLOCATE_CLEAR, 0));
		BMHandleToHandle (reinterpret_cast<GSHandle> (attributeDef.sfill_Items.sfill_HotSpots),  reinterpret_cast<GSHandle*> (&(attributeDefExt.sfill_Items.sfill_HotSpots)));
	}

	if ((attributeDef.sfill_Items.sfill_Lines != nullptr) && (*(attributeDef.sfill_Items.sfill_Lines) != nullptr)) {
		attributeDefExt.sfill_Items.sfill_Lines = reinterpret_cast<API_SFill_Line**> (BMAllocateHandle (BMGetHandleSize (reinterpret_cast<GSHandle> (attributeDef.sfill_Items.sfill_Lines)), ALLOCATE_CLEAR, 0));
		BMHandleToHandle (reinterpret_cast<GSHandle> (attributeDef.sfill_Items.sfill_Lines),  reinterpret_cast<GSHandle*> (&(attributeDefExt.sfill_Items.sfill_Lines)));
	}

	if ((attributeDef.sfill_Items.sfill_Arcs != nullptr) && (*(attributeDef.sfill_Items.sfill_Arcs) != nullptr)) {
		attributeDefExt.sfill_Items.sfill_Arcs = reinterpret_cast<API_SFill_Arc**> (BMAllocateHandle (BMGetHandleSize (reinterpret_cast<GSHandle> (attributeDef.sfill_Items.sfill_Arcs)), ALLOCATE_CLEAR, 0));
		BMHandleToHandle (reinterpret_cast<GSHandle> (attributeDef.sfill_Items.sfill_Arcs),  reinterpret_cast<GSHandle*> (&(attributeDefExt.sfill_Items.sfill_Arcs)));
	}

	if ((attributeDef.sfill_Items.sfill_SolidFills != nullptr) && (*(attributeDef.sfill_Items.sfill_SolidFills) != nullptr)) {
		attributeDefExt.sfill_Items.sfill_SolidFills = reinterpret_cast<API_Polygon**> (BMAllocateHandle (BMGetHandleSize (reinterpret_cast<GSHandle> (attributeDef.sfill_Items.sfill_SolidFills)), ALLOCATE_CLEAR, 0));
		BMHandleToHandle (reinterpret_cast<GSHandle> (attributeDef.sfill_Items.sfill_SolidFills),  reinterpret_cast<GSHandle*> (&(attributeDefExt.sfill_Items.sfill_SolidFills)));
	}

	if ((attributeDef.sfill_Items.sfill_FillCoords != nullptr) && (*(attributeDef.sfill_Items.sfill_FillCoords) != nullptr)) {
		attributeDefExt.sfill_Items.sfill_FillCoords = reinterpret_cast<API_Coord**> (BMAllocateHandle (BMGetHandleSize (reinterpret_cast<GSHandle> (attributeDef.sfill_Items.sfill_FillCoords)), ALLOCATE_CLEAR, 0));
		BMHandleToHandle (reinterpret_cast<GSHandle> (attributeDef.sfill_Items.sfill_FillCoords),  reinterpret_cast<GSHandle*> (&(attributeDefExt.sfill_Items.sfill_FillCoords)));
	}

	if ((attributeDef.sfill_Items.sfill_SubPolys != nullptr) && (*(attributeDef.sfill_Items.sfill_SubPolys) != nullptr)) {
		attributeDefExt.sfill_Items.sfill_SubPolys = reinterpret_cast<Int32**> (BMAllocateHandle (BMGetHandleSize (reinterpret_cast<GSHandle> (attributeDef.sfill_Items.sfill_SubPolys)), ALLOCATE_CLEAR, 0));
		BMHandleToHandle (reinterpret_cast<GSHandle> (attributeDef.sfill_Items.sfill_SubPolys),  reinterpret_cast<GSHandle*> (&(attributeDefExt.sfill_Items.sfill_SubPolys)));
	}

	if ((attributeDef.sfill_Items.sfill_PolyArcs != nullptr) && (*(attributeDef.sfill_Items.sfill_PolyArcs) != nullptr)) {
		attributeDefExt.sfill_Items.sfill_PolyArcs = reinterpret_cast<API_PolyArc**> (BMAllocateHandle (BMGetHandleSize (reinterpret_cast<GSHandle> (attributeDef.sfill_Items.sfill_PolyArcs)), ALLOCATE_CLEAR, 0));
		BMHandleToHandle (reinterpret_cast<GSHandle> (attributeDef.sfill_Items.sfill_PolyArcs),  reinterpret_cast<GSHandle*> (&(attributeDefExt.sfill_Items.sfill_PolyArcs)));
	}

	if ((attributeDef.cwall_compItems != nullptr) && (*(attributeDef.cwall_compItems) != nullptr)) {
		attributeDefExt.cwall_compItems = reinterpret_cast<API_CWallComponent**> (BMAllocateHandle (BMGetHandleSize (reinterpret_cast<GSHandle> (attributeDef.cwall_compItems)), ALLOCATE_CLEAR, 0));
		BMHandleToHandle (reinterpret_cast<GSHandle> (attributeDef.cwall_compItems),  reinterpret_cast<GSHandle*> (&(attributeDefExt.cwall_compItems)));
	}

	if ((attributeDef.cwall_compLItems != nullptr) && (*(attributeDef.cwall_compLItems) != nullptr)) {
		attributeDefExt.cwall_compLItems = reinterpret_cast<API_CWallLineComponent**> (BMAllocateHandle (BMGetHandleSize (reinterpret_cast<GSHandle> (attributeDef.cwall_compLItems)), ALLOCATE_CLEAR, 0));
		BMHandleToHandle (reinterpret_cast<GSHandle> (attributeDef.cwall_compLItems),  reinterpret_cast<GSHandle*> (&(attributeDefExt.cwall_compLItems)));
	}

	if (attributeDef.layer_statItems != nullptr) {
		*attributeDefExt.layer_statItems = *attributeDef.layer_statItems;
	}

	if ((attributeDef.zone_addParItems != nullptr) && (*(attributeDef.zone_addParItems) != nullptr)) {
		GSSize addParHandleSize = BMGetHandleSize (reinterpret_cast<GSHandle> (attributeDef.zone_addParItems));

		attributeDefExt.zone_addParItems = reinterpret_cast<API_AddParType**> (BMAllocateHandle (addParHandleSize, ALLOCATE_CLEAR, 0));
		BMHandleToHandle (reinterpret_cast<GSHandle> (attributeDef.zone_addParItems),  reinterpret_cast<GSHandle*> (&(attributeDefExt.zone_addParItems)));

		Int32 parameterNum = addParHandleSize / sizeof (API_AddParType);
		for (Int32 i = 0; i < parameterNum; ++i) {
			if ((*(attributeDef.zone_addParItems))[i].typeMod == API_ParArray) {
				(*(attributeDefExt.zone_addParItems))[i].value.array = BMAllocateHandle (BMGetHandleSize ((*(attributeDef.zone_addParItems))[i].value.array), ALLOCATE_CLEAR, 0);
				BMHandleToHandle ((*(attributeDef.zone_addParItems))[i].value.array,  &((*(attributeDefExt.zone_addParItems))[i].value.array));
			}
		}
	}

	if (attributeDef.profile_vectorImageItems != nullptr) {
		attributeDefExt.profile_vectorImageItems = new ProfileVectorImage ();
		*attributeDefExt.profile_vectorImageItems = *attributeDef.profile_vectorImageItems;
	}

	if (attributeDef.profile_vectorImageParameterNames != nullptr) {
		attributeDefExt.profile_vectorImageParameterNames = new GS::HashTable<PVI::ProfileParameterId, GS::UniString>;
		*attributeDefExt.profile_vectorImageParameterNames = *attributeDef.profile_vectorImageParameterNames;
	}

	if ((attributeDef.penTable_Items != nullptr)) {
		attributeDefExt.penTable_Items = new GS::Array<API_Pen>;
		*attributeDef.penTable_Items = *attributeDefExt.penTable_Items;
	}

	if ((attributeDef.op_dailyProfiles != nullptr) && (*(attributeDef.op_dailyProfiles) != nullptr)) {
		attributeDefExt.op_dailyProfiles = reinterpret_cast<API_DailyProfile**> (BMAllocateHandle (BMGetHandleSize (reinterpret_cast<GSHandle> (attributeDef.op_dailyProfiles)), ALLOCATE_CLEAR, 0));
		BMHandleToHandle (reinterpret_cast<GSHandle> (attributeDef.op_dailyProfiles),  reinterpret_cast<GSHandle*> (&(attributeDefExt.op_dailyProfiles)));
	}

	if ((attributeDef.op_dailyProfileUsages != nullptr) && (*(attributeDef.op_dailyProfileUsages) != nullptr)) {
		attributeDefExt.op_dailyProfileUsages = reinterpret_cast<API_DailyProfileUsage**> (BMAllocateHandle (BMGetHandleSize (reinterpret_cast<GSHandle> (attributeDef.op_dailyProfileUsages)), ALLOCATE_CLEAR, 0));
		BMHandleToHandle (reinterpret_cast<GSHandle> (attributeDef.op_dailyProfileUsages),  reinterpret_cast<GSHandle*> (&(attributeDefExt.op_dailyProfileUsages)));
	}

	return attributeDefExt;
}


template <typename SelectorType>
API_AttributeDefExt GSAPI::AttributeProxy<SelectorType>::GetAttributeDefExt (const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index) const
{
	API_DatabaseInfo strippedDBInfo = StripDatabaseInfo (dbInfo);
    if (attributeHash.ContainsKey (strippedDBInfo)) {
        const UsedAttributes& usedAttributes = attributeHash[strippedDBInfo][attributeType];
        if (usedAttributes.usedIndices.ContainsKey (index)) {
			return CopyAttributeDefExt (usedAttributes.attributeList[usedAttributes.usedIndices[index]].definition);
		}
	}

	API_Attribute		attribute = {};
	API_AttributeDefExt attributeDefExt = {};
	if (LoadAttribute (dbInfo, attribute, attributeDefExt, LoadOnlyAttributeDefExt) != NoError)
		attributeDefExt = {};

	return attributeDefExt;
}


template <typename SelectorType>
const API_AttributeDefExt& GSAPI::AttributeProxy<SelectorType>::GetProxiedAttributeDefExt (const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index) const
{
	API_DatabaseInfo strippedDBInfo = StripDatabaseInfo (dbInfo);
    if (attributeHash.ContainsKey (strippedDBInfo)) {
        const UsedAttributes& usedAttributes = attributeHash[strippedDBInfo][attributeType];
        if (usedAttributes.usedIndices.ContainsKey (index)) {
			return usedAttributes.attributeList[usedAttributes.usedIndices[index]].definition;
		}
	}

	return emptyAttributeDefExt;
}


template <typename SelectorType>
GS::UniString GSAPI::AttributeProxy<SelectorType>::GetAttributeName (const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index) const
{
	API_Attribute attribute = GetAttribute (dbInfo, attributeType, index);
	return GS::UniString (attribute.header.name);
}


template <typename SelectorType>
GS::UniString GSAPI::AttributeProxy<SelectorType>::GetProxiedAttributeName (const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index) const
{
	API_Attribute attribute = GetProxiedAttribute (dbInfo, attributeType, index);
	return GS::UniString (attribute.header.name);
}


template <typename SelectorType>
UIndex GSAPI::AttributeProxy<SelectorType>::GetNextOutputDatabase (const API_DatabaseInfo& dbInfo) const
{
	API_DatabaseInfo strippedDBInfo = StripDatabaseInfo (dbInfo);
	if (!attributeHash.ContainsKey (strippedDBInfo)) {
		return MaxUIndex;
	}

	UIndex dbIndex = usedDatabases.FindFirst (strippedDBInfo);
	if (dbIndex == MaxUIndex) {
		return MaxUIndex;
	}

	USize size = usedDatabases.GetSize ();
	for (++dbIndex; (dbIndex < size) && (!outputInDatabases.ContainsKey (usedDatabases[dbIndex].databaseUnId)); ++dbIndex);

	if (dbIndex < size) {
		return dbIndex;
	} else {
		return MaxUIndex;
	}
}


template <typename SelectorType>
API_AttrTypeID GSAPI::AttributeProxy<SelectorType>::GetNextOutputAttributeType (const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType) const
{
	API_DatabaseInfo strippedDBInfo = StripDatabaseInfo (dbInfo);
	if (!attributeHash.ContainsKey (strippedDBInfo) ||
		!outputInDatabases.ContainsKey (strippedDBInfo.databaseUnId))
	{
		return API_ZombieAttrID;
	}

	const GS::ArrayFB <UsedAttributes, API_LastAttributeID + 1>& typeArray         = attributeHash[strippedDBInfo];
	API_AttrTypeID                                               nextAttributeType = API_FirstAttributeID;

	for (nextAttributeType = static_cast<API_AttrTypeID> (static_cast<int> (attributeType) + 1);
		 (nextAttributeType <= API_LastAttributeID) && (typeArray[nextAttributeType].attributeList.GetSize () == 0);
		 nextAttributeType = static_cast<API_AttrTypeID> (static_cast<int> (nextAttributeType) + 1));

	if (nextAttributeType <= API_LastAttributeID) {
		return nextAttributeType;
	} else {
		return API_ZombieAttrID;
	}
}


template <typename SelectorType>
API_AttributeIndex GSAPI::AttributeProxy<SelectorType>::GetNextOutputAttributeIndex (const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index) const
{
	API_DatabaseInfo strippedDBInfo = StripDatabaseInfo (dbInfo);
	if (!attributeHash.ContainsKey (strippedDBInfo) ||
		!outputInDatabases.ContainsKey (strippedDBInfo.databaseUnId))
	{
		return APIInvalidAttributeIndex;
	}

	const UsedAttributes& usedAttributes = attributeHash[strippedDBInfo][attributeType];
	USize                 attributeCount = static_cast<short> (usedAttributes.attributeList.GetSize ());

	if (attributeCount == 0) {
		return APIInvalidAttributeIndex;
	}

	usedAttributes.SortIfNecessary ();
	if (usedAttributes.usedIndices.ContainsKey (index)) {
		UIndex currentIndex = usedAttributes.usedIndices[index];
		if (currentIndex == attributeCount - 1) {	// last elem
			return APIInvalidAttributeIndex;
		} else {
			return usedAttributes.attributeList[currentIndex + 1].attribute.header.index;
		}
	}

	// shouldn't reach this point...
	return APIInvalidAttributeIndex;
}


template <typename SelectorType>
API_Attribute GSAPI::AttributeProxy<SelectorType>::GetEndAttribute (API_DatabaseInfo& dbInfo) const
{
	API_Attribute attribute = {};
	dbInfo = {};

	UIndex lastDBIndex = MaxUIndex;
	if (usedDatabases.GetSize () > 0) {
		usedDatabases.GetFirst ();	// to force sorting
		for (Int32 dbIndex = usedDatabases.GetSize () - 1; dbIndex >= 0; dbIndex--) {
			if (outputInDatabases.ContainsKey (usedDatabases[dbIndex].databaseUnId)) {
				lastDBIndex = dbIndex;
				break;
			}
		}
	}

	if (lastDBIndex != MaxUIndex) {
		dbInfo = usedDatabases[lastDBIndex];

		const GS::ArrayFB <UsedAttributes, API_LastAttributeID + 1>& typeArray     = attributeHash[dbInfo];
		API_AttrTypeID                                               attributeType = API_LastAttributeID;

		for (; (attributeType != API_ZombieAttrID) && (typeArray[attributeType].attributeList.GetSize () == 0); attributeType = static_cast<API_AttrTypeID> (static_cast<int> (attributeType) - 1));

		if (attributeType == API_ZombieAttrID) {
			// error -> return empty API_Attribute
			return attribute;
		} else {
			const UsedAttributes& usedAttributes = typeArray[attributeType];

			usedAttributes.SortIfNecessary ();
			attribute.header.typeID = attributeType;
			attribute.header.index = APIInvalidAttributeIndex;
			return attribute;
		}
	}

	// no attributes used at all -> return empty API_Attribute
	return attribute;
}


template <typename SelectorType>
void GSAPI::AttributeProxy<SelectorType>::GetNext (GSAPI::IteratorElem <API_Attribute>& attribute) const
{
	bool             setLastElem    = false;
	API_DatabaseInfo strippedDBInfo = StripDatabaseInfo (attribute.databaseInfo);

	API_AttributeIndex nextAttributeIndex = GetNextOutputAttributeIndex (strippedDBInfo, attribute.elem.header.typeID, attribute.elem.header.index);
	if (nextAttributeIndex == APIInvalidAttributeIndex) {
		API_AttrTypeID nextAttributeType = GetNextOutputAttributeType (strippedDBInfo, attribute.elem.header.typeID);
		if (nextAttributeType == API_ZombieAttrID) {
			UIndex nextOutputDB = GetNextOutputDatabase (strippedDBInfo);
			if (nextOutputDB == MaxUIndex) {
				setLastElem = true;
			} else {
				API_DatabaseInfo nextDBInfo = usedDatabases[nextOutputDB];
				if (!attributeHash.ContainsKey (nextDBInfo)) {
					// this shouldn't happen
					setLastElem = true;
				} else {
					attribute.databaseInfo = {};
					attribute.databaseInfo = nextDBInfo;
					nextAttributeType = GetNextOutputAttributeType (nextDBInfo, API_ZombieAttrID);
					if (nextAttributeType == API_ZombieAttrID) {
						// this shouldn't happen
						setLastElem = true;
					} else {
						const UsedAttributes& usedAttributes = attributeHash[nextDBInfo][nextAttributeType];

						usedAttributes.SortIfNecessary ();
						attribute.elem = usedAttributes.attributeList[0].attribute;
					}
				}
			}
		} else {
			const UsedAttributes& usedAttributes = attributeHash[strippedDBInfo][nextAttributeType];

			usedAttributes.SortIfNecessary ();
			attribute.elem = usedAttributes.attributeList[0].attribute;
		}
	} else {
		attribute.elem = GetProxiedAttribute (strippedDBInfo, attribute.elem.header.typeID, nextAttributeIndex);
	}

	if (setLastElem) {
		attribute.elem = GetEndAttribute (attribute.databaseInfo);
	}
}


template <typename SelectorType>
typename GSAPI::AttributeProxy<SelectorType>::PseudoIterator GSAPI::AttributeProxy<SelectorType>::Begin () const
{
	API_DatabaseInfo dbInfo = {};
	API_Attribute    apiAttribute = {};

	UIndex dbIndex = 0;
	USize  size    = usedDatabases.GetSize ();

	for (dbIndex = 0; (dbIndex < size) && (!outputInDatabases.ContainsKey (usedDatabases[dbIndex].databaseUnId)); ++dbIndex);
	while (dbIndex < size) {
		API_DatabaseInfo firstDBInfo = usedDatabases[dbIndex];

		const GS::ArrayFB <UsedAttributes, API_LastAttributeID + 1>& typeArray     = attributeHash[firstDBInfo];
		API_AttrTypeID                                               attributeType = API_FirstAttributeID;

		for (; (attributeType <= API_LastAttributeID) && (typeArray[attributeType].attributeList.GetSize () == 0); attributeType = static_cast<API_AttrTypeID> (static_cast<int> (attributeType) + 1));

		if (attributeType <= API_LastAttributeID) {
			typeArray[attributeType].SortIfNecessary ();
			dbInfo = firstDBInfo;
			apiAttribute = typeArray[attributeType].attributeList[0].attribute;
			break;
		} else {
			for (++dbIndex; (dbIndex < size) && (!outputInDatabases.ContainsKey (usedDatabases[dbIndex].databaseUnId)); ++dbIndex);
		}
	}

	GSAPI::IteratorElem <API_Attribute>	attribute = { dbInfo, apiAttribute };
    PseudoIterator::Parameters			parameters ((*this), attribute);

	return this->CreateIterator (parameters);
}


template <typename SelectorType>
const typename GSAPI::AttributeProxy<SelectorType>::PseudoIterator GSAPI::AttributeProxy<SelectorType>::End () const
{
	API_DatabaseInfo dbInfo = {};
	API_Attribute    apiAttribute = {};

	apiAttribute = GetEndAttribute (dbInfo);

	GSAPI::IteratorElem <API_Attribute> attribute = { dbInfo, apiAttribute };
    PseudoIterator::Parameters			parameters ((*this), attribute);

	return this->CreateIterator (parameters);
}


template <typename SelectorType>
typename GSAPI::AttributeProxy<SelectorType>::PseudoIterator GSAPI::AttributeProxy<SelectorType>::Begin (const API_DatabaseUnId& dbUnId) const
{
	bool             returnEnd      = false;
	API_DatabaseUnId strippedDBUnId = StripDatabaseUnId (dbUnId);
	USize			 databaseCount  = usedDatabases.GetSize ();
	API_Attribute    apiAttribute	= {};

	if (!outputInDatabases.ContainsKey (strippedDBUnId)) {
		returnEnd = true;
	} else {
		UIndex dbIndex  = MaxUIndex;
		for (UIndex i = 0; i < databaseCount; ++i) {
			if (usedDatabases[i].databaseUnId == strippedDBUnId) {
				dbIndex = i;
				break;
			}
		}

		if (dbIndex == MaxUIndex) {
			returnEnd = true;
		} else {
			do {
				const GS::ArrayFB <UsedAttributes, API_LastAttributeID + 1>& typeArray     = attributeHash[usedDatabases[dbIndex]];
				API_AttrTypeID                                               attributeType = API_FirstAttributeID;

				for (; (attributeType <= API_LastAttributeID) && (typeArray[attributeType].attributeList.GetSize () == 0); attributeType = static_cast<API_AttrTypeID> (static_cast<int> (attributeType) + 1));

				if (attributeType <= API_LastAttributeID) {
					typeArray[attributeType].SortIfNecessary ();
					apiAttribute = typeArray[attributeType].attributeList[0].attribute;

					GSAPI::IteratorElem <API_Attribute> attribute = { usedDatabases[dbIndex], apiAttribute };
					PseudoIterator::Parameters			parameters ((*this), attribute);

					return this->CreateIterator (parameters);
				} else {
					dbIndex++;
				}
			} while ((dbIndex < databaseCount) && (usedDatabases[dbIndex].databaseUnId == strippedDBUnId));

			if ((dbIndex == databaseCount) || (usedDatabases[dbIndex].databaseUnId != strippedDBUnId)) {
				returnEnd = true;
			}
		}
	}

	if (returnEnd) {
		UIndex nextDBIndex     = MaxUIndex;
		bool   foundSelectedDB = false;
		for (UIndex i = 0; i < databaseCount; ++i) {
			if (usedDatabases[i].databaseUnId == strippedDBUnId) {
				foundSelectedDB = true;
			}
			if (foundSelectedDB &&
				(usedDatabases[i].databaseUnId != strippedDBUnId) &&
				(outputInDatabases.ContainsKey (usedDatabases[i].databaseUnId)))
			{
				nextDBIndex = i;
				break;
			}
		}

		if (nextDBIndex != MaxUIndex) {
			return Begin (usedDatabases[nextDBIndex]);
		}
	}

	return End ();
}


template <typename SelectorType>
const typename GSAPI::AttributeProxy<SelectorType>::PseudoIterator GSAPI::AttributeProxy<SelectorType>::End (const API_DatabaseUnId& dbUnId) const
{
	API_DatabaseUnId strippedDBUnId  = StripDatabaseUnId (dbUnId);
	USize			 databaseCount   = usedDatabases.GetSize ();
	UIndex			 nextDBIndex     = MaxUIndex;
	bool			 foundSelectedDB = false;

	for (UIndex i = 0; i < databaseCount; ++i) {
		if (usedDatabases[i].databaseUnId == strippedDBUnId) {
			foundSelectedDB = true;
		}
		if (foundSelectedDB &&
			(usedDatabases[i].databaseUnId != strippedDBUnId) &&
			(outputInDatabases.ContainsKey (usedDatabases[i].databaseUnId)))
		{
			nextDBIndex = i;
			break;
		}
	}

	if (nextDBIndex != MaxUIndex) {
		return Begin (usedDatabases[nextDBIndex]);
	}
	return End ();
}


template <typename SelectorType>
typename GSAPI::AttributeProxy<SelectorType>::PseudoIterator GSAPI::AttributeProxy<SelectorType>::Begin (const API_DatabaseInfo& dbInfo) const
{
	bool             returnEnd      = false;
	API_DatabaseInfo strippedDBInfo = StripDatabaseInfo (dbInfo);
	API_Attribute    apiAttribute	= {};

	if (!attributeHash.ContainsKey (strippedDBInfo) ||
		!outputInDatabases.ContainsKey (strippedDBInfo.databaseUnId))
	{
		returnEnd = true;
	} else {
		const GS::ArrayFB <UsedAttributes, API_LastAttributeID + 1>& typeArray     = attributeHash[strippedDBInfo];
		API_AttrTypeID                                               attributeType = API_FirstAttributeID;

		for (; (attributeType <= API_LastAttributeID) && (typeArray[attributeType].attributeList.GetSize () == 0); attributeType = static_cast<API_AttrTypeID> (static_cast<int> (attributeType) + 1));

		if (attributeType <= API_LastAttributeID) {
			typeArray[attributeType].SortIfNecessary ();
			apiAttribute = typeArray[attributeType].attributeList[0].attribute;

			GSAPI::IteratorElem <API_Attribute> attribute = { strippedDBInfo, apiAttribute };
			PseudoIterator::Parameters			parameters ((*this), attribute);

			return this->CreateIterator (parameters);
		} else {
			returnEnd = true;
		}
	}

	if (returnEnd) {
		UIndex nextDBIndex = GetNextOutputDatabase (dbInfo);
		if (nextDBIndex != MaxUIndex) {
			return Begin (usedDatabases[nextDBIndex]);
		}
	}

	return End ();
}


template <typename SelectorType>
const typename GSAPI::AttributeProxy<SelectorType>::PseudoIterator GSAPI::AttributeProxy<SelectorType>::End (const API_DatabaseInfo& dbInfo) const
{
	UIndex nextDBIndex = GetNextOutputDatabase (dbInfo);
	if (nextDBIndex != MaxUIndex) {
		return Begin (usedDatabases[nextDBIndex]);
	}
	return End ();
}


template <typename SelectorType>
typename GSAPI::AttributeProxy<SelectorType>::PseudoIterator GSAPI::AttributeProxy<SelectorType>::Begin (const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType) const
{
	bool             returnEnd      = false;
	API_DatabaseInfo strippedDBInfo = StripDatabaseInfo (dbInfo);
	API_Attribute    apiAttribute	= {};

	if (!attributeHash.ContainsKey (strippedDBInfo) ||
		!outputInDatabases.ContainsKey (strippedDBInfo.databaseUnId))
	{
		returnEnd = true;
	} else {
		const UsedAttributes& usedAttributes = attributeHash[strippedDBInfo][attributeType];
		if (usedAttributes.attributeList.GetSize () > 0) {
			usedAttributes.SortIfNecessary ();
			apiAttribute = usedAttributes.attributeList[0].attribute;

			GSAPI::IteratorElem <API_Attribute> attribute = { strippedDBInfo, apiAttribute };
			PseudoIterator::Parameters			parameters ((*this), attribute);

			return this->CreateIterator (parameters);
		} else {
			returnEnd = true;
		}
	}

	if (returnEnd) {
		API_AttrTypeID nextAttribute = GetNextOutputAttributeType (dbInfo, attributeType);
		if (nextAttribute != API_ZombieAttrID) {
			return Begin (dbInfo, nextAttribute);
		} else {
			UIndex nextDBIndex = GetNextOutputDatabase (dbInfo);
			if (nextDBIndex != MaxUIndex) {
				return Begin (usedDatabases[nextDBIndex]);
			}
		}
	}

	return End ();
}


template <typename SelectorType>
const typename GSAPI::AttributeProxy<SelectorType>::PseudoIterator GSAPI::AttributeProxy<SelectorType>::End (const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType) const
{
	API_AttrTypeID nextAttribute = GetNextOutputAttributeType (dbInfo, attributeType);
	if (nextAttribute != API_ZombieAttrID) {
		return Begin (dbInfo, nextAttribute);
	} else {
		UIndex nextDBIndex = GetNextOutputDatabase (dbInfo);
		if (nextDBIndex != MaxUIndex) {
			return Begin (usedDatabases[nextDBIndex]);
		}
	}
	return End ();
}

#endif //__ATTRIBUTEPROXY_HPP__
