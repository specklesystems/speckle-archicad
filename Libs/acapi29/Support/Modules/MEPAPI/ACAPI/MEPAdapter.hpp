#ifndef GS_ACAPI_MEP_ADAPTER_HPP
#define GS_ACAPI_MEP_ADAPTER_HPP

#include "MEPAPIExport.hpp"
#include "MEPUniqueID.hpp"
#include "MEPEnums.hpp"

// ARCHICADAPI
#include "ACAPI/Object.hpp"
#include "API_Guid.hpp"
#include "APIdefs_Attributes.h"


namespace ACAPI::MEP {

/**
 * @file
 * 			It contains the raw guids of MEP elements that can be used in the old API of Archicad.
 */
MEPAPI_EXPORT extern const API_Guid VentilationBranchID;
MEPAPI_EXPORT extern const API_Guid PipingBranchID;
MEPAPI_EXPORT extern const API_Guid CableCarrierBranchID;
MEPAPI_EXPORT extern const API_Guid VentilationTerminalID;
MEPAPI_EXPORT extern const API_Guid PipingTerminalID;
MEPAPI_EXPORT extern const API_Guid VentilationAccessoryID;
MEPAPI_EXPORT extern const API_Guid PipingAccessoryID;
MEPAPI_EXPORT extern const API_Guid EquipmentID;
MEPAPI_EXPORT extern const API_Guid VentilationRoutingElementID;
MEPAPI_EXPORT extern const API_Guid PipingRoutingElementID;
MEPAPI_EXPORT extern const API_Guid CableCarrierRoutingElementID;
MEPAPI_EXPORT extern const API_Guid VentilationFittingID;
MEPAPI_EXPORT extern const API_Guid PipingFittingID;
MEPAPI_EXPORT extern const API_Guid CableCarrierFittingID;
MEPAPI_EXPORT extern const API_Guid VentilationRoutingSegmentID;
MEPAPI_EXPORT extern const API_Guid PipingRoutingSegmentID;
MEPAPI_EXPORT extern const API_Guid CableCarrierRoutingSegmentID;
MEPAPI_EXPORT extern const API_Guid VentilationRoutingNodeID;
MEPAPI_EXPORT extern const API_Guid PipingRoutingNodeID;
MEPAPI_EXPORT extern const API_Guid CableCarrierRoutingNodeID;
MEPAPI_EXPORT extern const API_Guid VentilationRigidSegmentID;
MEPAPI_EXPORT extern const API_Guid PipingRigidSegmentID;
MEPAPI_EXPORT extern const API_Guid CableCarrierRigidSegmentID;
MEPAPI_EXPORT extern const API_Guid VentilationElbowID;
MEPAPI_EXPORT extern const API_Guid PipingElbowID;
MEPAPI_EXPORT extern const API_Guid CableCarrierElbowID;
MEPAPI_EXPORT extern const API_Guid VentilationTransitionID;
MEPAPI_EXPORT extern const API_Guid PipingTransitionID;
MEPAPI_EXPORT extern const API_Guid CableCarrierTransitionID;
MEPAPI_EXPORT extern const API_Guid VentilationFlexibleSegmentID;
MEPAPI_EXPORT extern const API_Guid VentilationTakeOffID;
MEPAPI_EXPORT extern const API_Guid PipingFlexibleSegmentID;

MEPAPI_EXPORT extern const API_Guid MEPModelCheckTypeID;
MEPAPI_EXPORT extern const API_Guid MEPModelCheckVentilationGroupID;


/**
 * @brief Returns every MEP element
 * @ingroup MEP
 * @since Archicad 28
 * @return Gives back every MEP element's GUID in an array
 */
MEPAPI_EXPORT GS::Array<API_Guid> CollectAllMEPElements ();

/**
 * @ingroup MEP
 * @param typeID The guid of the element type
 * @since Archicad 26
 * @return Decides if the typeID belongs to a Branch
 */
MEPAPI_EXPORT bool IsBranch (const API_Guid& typeID);

/**
 * @ingroup MEP
 * @param typeID The guid of the element type
 * @since Archicad 26
 * @return Decides if the typeID belongs to an Accessory
 */
MEPAPI_EXPORT bool IsAccessory (const API_Guid& typeID);

/**
 * @ingroup MEP
 * @param typeID The guid of the element type
 * @since Archicad 26
 * @return Decides if the typeID belongs to an Equipment
 */
MEPAPI_EXPORT bool IsEquipment (const API_Guid& typeID);

/**
 * @ingroup MEP
 * @param typeID The guid of the element type
 * @since Archicad 26
 * @return Decides if the typeID belongs to a Terminal
 */
MEPAPI_EXPORT bool IsTerminal (const API_Guid& typeID);

/**
 * @ingroup MEP
 * @param typeID The guid of the element type
 * @since Archicad 26
 * @return Decides if the typeID belongs to a RoutingElement
 */
MEPAPI_EXPORT bool IsRoutingElement (const API_Guid& typeID);

/**
 * @ingroup MEP
 * @param typeID The guid of the element type
 * @since Archicad 26
 * @return Decides if the typeID belongs to a Fitting
 */
MEPAPI_EXPORT bool IsFitting (const API_Guid& typeID);

/**
 * @ingroup MEP
 * @param typeID The guid of the element type
 * @since Archicad 26
 * @return Decides if the typeID belongs to a RigidSegment
 */
MEPAPI_EXPORT bool IsRigidSegment (const API_Guid& typeID);

/**
 * @ingroup MEP
 * @param typeID The guid of the element type
 * @return Decides if the typeID belongs to an Elbow
 */
MEPAPI_EXPORT bool IsElbow (const API_Guid& typeID);

/**
 * @ingroup MEP
 * @param typeID The guid of the element type
 * @return Decides if the typeID belongs to a Transition
 */
MEPAPI_EXPORT bool IsTransition (const API_Guid& typeID);

/**
 * @ingroup MEP
 * @param typeID The guid of the element type
 * @return Decides if the typeID belongs to a FlexibleSegment
 */
MEPAPI_EXPORT bool IsFlexibleSegment (const API_Guid& typeID);

/**
 * @ingroup MEP
 * @param typeID The guid of the element type
 * @since Archicad 28
 * @return Decides if the typeID belongs to a Take-off
 */
MEPAPI_EXPORT bool IsTakeOff (const API_Guid& typeID);

/**
 * @ingroup MEP
 * @param typeID The guid of the element type
 * @since Archicad 28
 * @return Decides if the typeID belongs to a Piping
 */
MEPAPI_EXPORT bool IsPiping (const API_Guid& typeID);

/**
 * @ingroup MEP
 * @param typeID The guid of the element type
 * @since Archicad 28
 * @return Decides if the typeID belongs to a Cable carrier
 */
MEPAPI_EXPORT bool IsCableCarrier (const API_Guid& typeID);

/**
 * @ingroup MEP
 * @param typeID The guid of the element type
 * @since Archicad 28
 * @return Decides if the typeID belongs to a Ventilation
 */
MEPAPI_EXPORT bool IsVentilation (const API_Guid& typeID);

/**
 * @ingroup MEP
 * @ingroup ModelCheck
 * @since Archicad 29
 * @return Returns the unique identifier of the MEP Model Check Type
 */
MEPAPI_EXPORT API_Guid GetMEPModelCheckTypeId ();


namespace Adapter {

	/**
	 * @brief It is a helper class that converts a simple GS::Guid or API_Guid into an MEP::UniqueID.
	 * @ingroup MEP
	 */
	class UniqueID : public ACAPI::MEP::UniqueID {
	public:
		/**
		 * @brief Constructs a UniqueID from GS::Guid.
		 * @param guid The GUID to convert.
		 * @ingroup MEP
		 */
		UniqueID (const GS::Guid& guid) : ACAPI::MEP::UniqueID (guid, ACAPI_GetToken ()) {}

		/**
		 * @brief Constructs a UniqueID from API_Guid.
		 * @param guid The GUID to convert.
		 * @ingroup MEP
		 */
		UniqueID (const API_Guid& guid) : ACAPI::MEP::UniqueID (APIGuid2GSGuid (guid), ACAPI_GetToken ()) {}
	};

}

/**
 * @brief Converts from the attribute management's API_MEPDomainID to ACAPI::MEP::Domain.
 * @details For implementation reasons, MEP systems are managed through our public C-API.
 * To withold compatibility with our more modern C++ API, the MEP domain enum is duplicated
 * both places. Outside of the C/C++ language interface, the enum is otherwise identical.
 * @param domain The attribute domain
 * @ingroup MEP
 * @since Archicad 29
 * @return The ACAPI::MEP::Domain corresponding to a API_MEPDomainID.
 */
MEPAPI_EXPORT ACAPI::MEP::Domain FromAttributeEnum (API_MEPDomainID domain);

} // ACAPI::MEP

#endif // GS_ACAPI_MEP_ADAPTER_HPP