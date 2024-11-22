#ifndef GS_ACAPI_MEP_ADAPTER_HPP
#define GS_ACAPI_MEP_ADAPTER_HPP

#include "MEPAPIExport.hpp"
#include "MEPUniqueID.hpp"

#include "API_Guid.hpp"

/** @brief Returns the token associated with the AddOn.
	@ingroup AddOnIdentification
	@return The token associated with the add-on.
	@remarks It is not guaranteed that this function will always return the same value. Always obtain your
	token by calling this function on demand.
*/
API_Token ACAPI_GetToken (void);

namespace ACAPI::MEP {

/** @file
	It contains the raw guids of MEP elements that can be used in the old API of Archicad.
*/
MEPAPI_EXPORT extern const API_Guid VentilationBranchID;
MEPAPI_EXPORT extern const API_Guid PipingBranchID;
MEPAPI_EXPORT extern const API_Guid CableCarrierBranchID;
MEPAPI_EXPORT extern const API_Guid VentilationTerminalID;
MEPAPI_EXPORT extern const API_Guid PipingTerminalID;
MEPAPI_EXPORT extern const API_Guid VentilationAccessoryID;
MEPAPI_EXPORT extern const API_Guid PipingAccessoryID;
MEPAPI_EXPORT extern const API_Guid EquipmentID;
MEPAPI_EXPORT extern const API_Guid VentilationRoutingID;
MEPAPI_EXPORT extern const API_Guid PipingRoutingID;
MEPAPI_EXPORT extern const API_Guid CableCarrierRoutingID;
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
MEPAPI_EXPORT extern const API_Guid VentilationBendID;
MEPAPI_EXPORT extern const API_Guid PipingBendID;
MEPAPI_EXPORT extern const API_Guid CableCarrierBendID;
MEPAPI_EXPORT extern const API_Guid VentilationTransitionID;
MEPAPI_EXPORT extern const API_Guid PipingTransitionID;
MEPAPI_EXPORT extern const API_Guid CableCarrierTransitionID;
MEPAPI_EXPORT extern const API_Guid VentilationFlexibleSegmentID;

/** @brief Returns the localized name of MEP element types
	@ingroup MEP
	@since Archicad 26
	@param typeID The guid of the element type
	@return If the typeID belongs to an MEP element, it returns its name, otherwise an empty string.
*/
MEPAPI_EXPORT GS::UniString GetLocalizedElemTypeName (const API_Guid& typeID);

/** @ingroup MEP
	@param typeID The guid of the element type
	@since Archicad 26
	@return Decides if the typeID belongs to a Branch
*/
MEPAPI_EXPORT bool IsBranch (const API_Guid& typeID);

/** @ingroup MEP
	@param typeID The guid of the element type
	@since Archicad 26
	@return Decides if the typeID belongs to an Accessory
*/
MEPAPI_EXPORT bool IsAccessory (const API_Guid& typeID);

/** @ingroup MEP
	@param typeID The guid of the element type
	@since Archicad 26
	@return Decides if the typeID belongs to an Equipment
*/
MEPAPI_EXPORT bool IsEquipment (const API_Guid& typeID);

/** @ingroup MEP
	@param typeID The guid of the element type
	@since Archicad 26
	@return Decides if the typeID belongs to a Terminal
*/
MEPAPI_EXPORT bool IsTerminal (const API_Guid& typeID);

/** @ingroup MEP
	@param typeID The guid of the element type
	@since Archicad 26
	@return Decides if the typeID belongs to a RoutingElement
*/
MEPAPI_EXPORT bool IsRoutingElement (const API_Guid& typeID);

/** @ingroup MEP
	@param typeID The guid of the element type
	@since Archicad 26
	@return Decides if the typeID belongs to a Fitting
*/
MEPAPI_EXPORT bool IsFitting (const API_Guid& typeID);

/** @ingroup MEP
	@param typeID The guid of the element type
	@since Archicad 26
	@return Decides if the typeID belongs to a RigidSegment
*/
MEPAPI_EXPORT bool IsRigidSegment (const API_Guid& typeID);

/** @ingroup MEP
	@param typeID The guid of the element type
	@return Decides if the typeID belongs to a Bend
*/
MEPAPI_EXPORT bool IsBend (const API_Guid& typeID);

/** @ingroup MEP
	@param typeID The guid of the element type
	@return Decides if the typeID belongs to a Transition
*/
MEPAPI_EXPORT bool IsTransition (const API_Guid& typeID);

/** @ingroup MEP
	@param typeID The guid of the element type
	@return Decides if the typeID belongs to a FlexibleSegment
*/
MEPAPI_EXPORT bool IsFlexibleSegment (const API_Guid& typeID);

namespace Adapter {

	/** @brief It is a helper class that converts a simple GS::Guid or API_Guid into an MEP::UniqueID.
		@ingroup MEP
	*/
	class UniqueID : public ACAPI::MEP::UniqueID {
	public:
		UniqueID (const GS::Guid& guid) : ACAPI::MEP::UniqueID (guid, ACAPI_GetToken ()) {}
		UniqueID (const API_Guid& guid) : ACAPI::MEP::UniqueID (APIGuid2GSGuid (guid), ACAPI_GetToken ()) {}
	};

}

} // ACAPI::MEP

#endif // GS_ACAPI_MEP_ADAPTER_HPP