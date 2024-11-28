#ifndef IFCAPI_OBJECTACCESSOR_HPP
#define IFCAPI_OBJECTACCESSOR_HPP

#pragma once

#include "IFCInOutAPIExport.hpp"

#include "IFCAssignments.hpp"
#include "IFCDefinitions.hpp"
#include "IFCObjectID.hpp"

#include <unordered_set>

// ACAPI
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"


namespace IFCAPI {

namespace Impl { class ObjectAccessor; }

namespace v1 {

/**
 * @brief To handle IFC objects, identifications and types.
 * @ingroup IFC
 * @since Archicad 28
 */
class IFCINOUTAPI_DLL_EXPORT ObjectAccessor final : public ACAPI::Object {
private:
	ObjectAccessor (std::shared_ptr<Impl::ObjectAccessor> impl);

	static ObjectAccessor	GetObjectAccessor (const API_Token& token);

public:
	friend ObjectAccessor	GetObjectAccessor ();

public:
	~ObjectAccessor ();

	/**
	 * @brief Create ObjectID for IfcProject.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return If able, creates an ObjectID, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC In-Out add-on is not present.
	 * @remarks It can be used to identify the IfcProject.
	 * @par Example
	 * 		@snippet IFCAPI_Test.cpp IFCAPI CreateIfcProjectObjectID example
	 */
	ACAPI::Result<ObjectID>		CreateIfcProjectObjectID () const;

	/**
	 * @brief Create ObjectID for IfcSite.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return If able, creates an ObjectID, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC In-Out add-on is not present.
	 * @remarks It can be used to identify the IfcSite.
	 * @par Example
	 * 		@snippet IFCAPI_Test.cpp IFCAPI CreateIfcSiteObjectID example
	 */
	ACAPI::Result<ObjectID>		CreateIfcSiteObjectID () const;

	/**
	 * @brief Create ObjectID for IfcBuilding.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return If able, creates an ObjectID, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC In-Out add-on is not present.
	 * @remarks It can be used to identify the IfcBuilding.
	 * @par Example
	 * 		@snippet IFCAPI_Test.cpp IFCAPI CreateIfcBuildingObjectID example
	 */
	ACAPI::Result<ObjectID>		CreateIfcBuildingObjectID () const;

	/**
	 * @brief Create ObjectID based on Archicad story.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param floorNumber [in] Archicad story floor number.
	 * @return If able, creates an ObjectID, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - Invalid value passed in the floorNumber parameter.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC In-Out add-on is not present.
	 * @remarks It can be used to identify an IfcBuildingStorey.
	 * @par Example
	 * 		@snippet IFCAPI_Test.cpp IFCAPI CreateIfcBuildingStoreyObjectID example
	 */
	ACAPI::Result<ObjectID>		CreateIfcBuildingStoreyObjectID (short floorNumber) const;

	/**
	 * @brief Create ObjectID based on Archicad element.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param elementHead [in] Archicad element.
	 * @return If able, creates an ObjectID, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - Invalid value passed in the elementHead parameter.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC In-Out add-on is not present.
	 * @remarks It can be used to identify an IfcElement or IfcSpace.
	 * @par Example
	 * 		@snippet IFCAPI_Test.cpp IFCAPI CreateElementObjectID example
	 */
	ACAPI::Result<ObjectID>		CreateElementObjectID (const API_Elem_Head& elementHead) const;

	/**
	 * @brief Get IFC Identifier for an IFC entity.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param objectID [in] to identify the IFC entity.
	 * @return If able, IfcGloballyUniqueId, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADID - Invalid value passed in the objectID parameter.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC add-on is not present.
	 * @remarks This value will be used during the export process.
	 * @par Example
	 * 		@snippet IFCAPI_Test.cpp IFCAPI GetGlobalId example
	 */
	ACAPI::Result<IfcGloballyUniqueId>	GetGlobalId (const IFCAPI::ObjectID& objectID) const;

	/**
	 * @brief Get external IFC Identifier for an IFC entity.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param objectID [in] to identify the IFC entity.
	 * @return If able, IfcGloballyUniqueId, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADID - Invalid value passed in the objectID parameter.
	 * 		   - APIERR_CANCEL - The entity wasn't imported from IFC.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC add-on is not present.
	 * @remarks If the entity was imported from IFC, it results the external IfcGloballyUniqueId, otherwise APIERR_CANCEL. This value can also be seen in IFC Project Manager.
	 */
	ACAPI::Result<IfcGloballyUniqueId>	GetExternalGlobalId (const IFCAPI::ObjectID& objectID) const;

	/**
	 * @brief Find elements having a certain IFC identifier.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param globalId [in] IFC entity identifier.
	 * @return If able, a set of ObjectID, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC In-Out add-on is not present.
	 * @remarks This function searches for elements having the passed IFC identifier.
	 * 			- It returns only one element, if the given parameter is a unique GlobalId. (for example the element was created in Archicad)
	 * 			- It can return multiple elements, if the given parameter is an external GlobalId. (for example an IFC file was imported more then once, or was placed as multiple instances of the same hotlink module)
	 * @par Example
	 * 		@snippet IFCAPI_Test.cpp IFCAPI FindElementsByGlobalId example
	 */
	ACAPI::Result<std::unordered_set<IFCAPI::ObjectID>>		FindElementsByGlobalId (const IfcGloballyUniqueId& globalId) const;

	/**
	 * @brief Get Archicad element guid from an IFC ObjectID.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param objectID [in] to identify the IFC entity.
	 * @return If able, an API_Guid, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - Project doesn't contain an element with the given objectID.
	 * 		   - APIERR_BADELEMENTTYPE - ObjectID does not identify an Archicad element.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC In-Out add-on is not present.
	 * @remarks Result can be used with API_Elem_Head and related ACAPI functions
	 * @par Example
	 * 		@snippet IFCAPI_Test.cpp IFCAPI GetAPIElementID example
	 */
	ACAPI::Result<API_Guid>		GetAPIElementID (const IFCAPI::ObjectID& objectID) const;

	/**
	 * @brief Get Archicad story index from an IFC ObjectID.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param objectID [in] to identify the IFC entity.
	 * @return If able, the index, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - Project doesn't contain a story with the given index.
	 * 		   - APIERR_BADELEMENTTYPE - ObjectID does not identify an Archicad story.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC In-Out add-on is not present.
	 * @remarks Result can be used to identify a story and use it's info in IFC hook based mapping
	 * @par Example
	 * 		@snippet IFCHook_Test.cpp IFCAPI GetStoryIndex example
	 */
	ACAPI::Result<short>	GetStoryIndex (const IFCAPI::ObjectID& objectID) const;

	/**
	 * @brief Get IFC type of an IFC entity.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param objectID [in] to identify the IFC entity.
	 * @return If able, IFCType, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADID - Invalid value passed in the objectID parameter.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC add-on is not present.
	 * @par Example
	 * 		@snippet IFCAPI_Test.cpp IFCAPI GetIFCType example
	 */
	ACAPI::Result<IFCType>	GetIFCType (const IFCAPI::ObjectID& objectID) const;

	/**
	 * @brief Get IFC type of the IfcTypeObject of an IFC entity.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param objectID [in] to identify the IFC entity.
	 * @return If able, IFCType, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADID - Invalid value passed in the objectID parameter.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC add-on is not present.
	 */
	ACAPI::Result<IFCType>	GetTypeObjectIFCType (const IFCAPI::ObjectID& objectID) const;

	/**
	 * @brief Get the persistent Assignment Tree.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return If able, the Assignment descriptor object, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC add-on is not present.
	 * @par Example
	 * 		@snippet IFCAPI_Test.cpp IFCAPI GetAssignments example
	 */
	ACAPI::Result<IFCAPI::Assignments>	GetAssignments () const;
};


/**
 * @brief Get the ObjectAccessor for handle IFC objects, identifications and types.
 * @ingroup IFC
 * @since Archicad 28
 * @return The ObjectAccessor
 */
inline ObjectAccessor GetObjectAccessor ()
{
	return ObjectAccessor::GetObjectAccessor (ACAPI_GetToken ());
}

}

using v1::ObjectAccessor;
using v1::GetObjectAccessor;

}

#endif