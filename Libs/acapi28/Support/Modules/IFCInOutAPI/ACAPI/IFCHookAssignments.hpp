#ifndef IFCAPI_IFCHOOKS_HPP
#define IFCAPI_IFCHOOKS_HPP

#pragma once

#include "IFCInOutAPIExport.hpp"

#include "IFCDefinitions.hpp"
#include "IFCObjectID.hpp"

#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"

#include <optional>


namespace IFCAPI {

namespace Impl { class HookAssignments; }

namespace v1 {

/**
 * @brief Class to set up an assignment structure for the assignments export hook
 * @ingroup IFC
 * @since Archicad 28
 * @remarks See IFCHook_Test.cpp for a complete example.
 */
class IFCINOUTAPI_DLL_EXPORT HookAssignments final : public ACAPI::Object {
private:
	HookAssignments (std::shared_ptr<Impl::HookAssignments> impl);

	static HookAssignments Create (const API_Token& token);

public:
	friend class HookDataProvider;

	~HookAssignments ();
/**
 * @brief Add an IFC Group definition to the assignment hook structure.
 * @ingroup IFC
 * @since Archicad 28
 * @param guid [in] A deterministic and unique id of the group to have a stable identification throughout the hook process, shall be fixed or content-based, not random.
 * @param ifcType [in] IFC type of the group, one of the group subtypes visible in IFC Project Manager.
 * 				  Can be: IfcGroup, IfcSystem, IfcBuildingSystem, IfcDistributionSystem or IfcZone
 * @param name [in] Name of the group, if omitted the default naming applies, or the one set up for the group in the attribute hook.
 * @param addAsRoot [in] Whether the group shall be one of the root groups, in the assignments structure, usually true.
 * 					Ifc a group is only a subgroup of another, set to false.
 * @return An ObjectID identifier generated for the group. Keep it, to recognize the reference later (in a property hook call for example).
 * 		   - NoError - The function has completed with success.
 * 		   - APIERR_BADPARS - Invalid/existing guid passed, or passed ifcType is incorrect.
 * @remarks When a group is created, the necessary relations are also added.
 * 			You can ignore them, unless you want to manipulate their properties with the hook. If you do, use the Get functions here to find out which one is queried in the hook.
 * 			Check the IFC schema on the web for further info about IfcGroup and it's subtypes.
 * @par Example
 * 		@snippet IFCHook_Test.cpp IFCAPI CreateIfcGroup example
 */
	ACAPI::Result<IFCAPI::ObjectID> CreateIfcGroup (const API_Guid& guid, const IFCType& ifcType, const std::optional<GS::UniString>& name, bool addAsRoot);

/**
 * @brief Get the IFC RelAssignsToGroup object of the passed group object.
 * @ingroup IFC
 * @since Archicad 28
 * @param groupObjectID [in] ObjectID of the group object.
 * @return An ObjectID identifier of the owner group.
 * 		   - NoError - The function has completed with success.
 * 		   - APIERR_BADPARS - Passed object is not a group.
 * @remarks When a group is created, the necessary relations are also added.
 * 			You can ignore them, unless you want to manipulate their properties with the hook. If you do, use the Get functions here to find out which one is queried in the hook.
 * 			Check the IFC schema on the web for further info about GetIfcRelAssignsToGroup.
 * @par Example
 * 		@snippet IFCHook_Test.cpp IFCAPI GetIfcRelAssignsToGroup example
 */
	ACAPI::Result<IFCAPI::ObjectID> GetIfcRelAssignsToGroup (const IFCAPI::ObjectID groupObjectID) const;

/**
 * @brief Get the IFC RelServicesBuildings object of the passed system object.
 * @ingroup IFC
 * @since Archicad 28
 * @param systemObjectID [in] ObjectID of the system object.
 * @return An ObjectID identifier of the owner system.
 * 		   - NoError - The function has completed with success.
 * 		   - APIERR_BADPARS - Passed object is not a system subtype.
 * @remarks When a group is created, the necessary relations are also added.
 * 			You can ignore them, unless you want to manipulate their properties with the hook. If you do, use the Get functions here to find out which one is queried in the hook.
 * 			Check the IFC schema on the web for further info about IfcRelServicesBuildings.
 * @par Example
 * 		@snippet IFCHook_Test.cpp IFCAPI GetIfcRelServicesBuildings example
 */
	ACAPI::Result<IFCAPI::ObjectID> GetIfcRelServicesBuildings (const IFCAPI::ObjectID systemObjectID) const;

/**
 * @brief Assign objects to the passed group object.
 * @ingroup IFC
 * @since Archicad 28
 * @param groupID [in] ObjectID of the group object.
 * @param assignedObjectIDs [in] List of objects to assign to the group.
 * @return Success of the operation
 * 		   - NoError - The function has completed with success.
 * 		   - APIERR_BADPARS - Passed object is not a group subtype, or assignedObjectIDs contains an objectID, which can't be assigned.
 * @remarks Not all invalid assignment cases are represented in the return value here, but no invalid result will be generated in the IFC export.
 * 			Check the IFC schema on the web for further info about IfcRelAssignsToGroup
 * @par Example
 * 		@snippet IFCHook_Test.cpp IFCAPI AssignObjects example
 */
	ACAPI::Result<void>	AssignObjects (const IFCAPI::ObjectID groupID, const std::vector<IFCAPI::ObjectID>& assignedObjectIDs);

/**
 * @brief Set serviced spatial element objects to the passed system object.
 * @ingroup IFC
 * @since Archicad 28
 * @param systemID [in] ObjectID of the system object.
 * @param servicedObjectIDs [in] List of spatial elements serviced by the passed system.
 * @return Success of the operation
 * 		   - NoError - The function has completed with success.
 * 		   - APIERR_BADPARS - Passed object is not a system subtype, or servicedObjectIDs contains an objectID, which can't be connected.
 * @remarks Not all invalid assignment cases are represented in the return value here, but no invalid result will be generated in the IFC export.
 * 			Check the IFC schema on the web for further info about IfcRelServicesBuildings.
 * @par Example
 * 		@snippet IFCHook_Test.cpp IFCAPI ServiceBuildings example
 */
	ACAPI::Result<void>	ServiceBuildings (const IFCAPI::ObjectID systemID, const std::vector<IFCAPI::ObjectID>& servicedObjectIDs);
};

}

using v1::HookAssignments;

}

#endif