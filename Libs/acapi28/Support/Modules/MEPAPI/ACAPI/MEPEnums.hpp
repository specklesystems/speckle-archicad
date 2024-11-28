#ifndef GS_ACAPI_MEP_ENUMS_HPP
#define GS_ACAPI_MEP_ENUMS_HPP


#include "MEPAPIExport.hpp"


namespace ACAPI::MEP {


/**
 * @brief Type of the domain.
 * @enum Domain
 * @ingroup MEP
 */
enum class Domain {
	Ventilation,
	Piping,
	CableCarrier
};


/**
 * @brief Shape of the connector.
 * @enum ConnectorShape
 * @ingroup MEP
 */
enum class ConnectorShape {
	Rectangular,
	Circular,
	Oval,
	UShape
};


/**
 * @brief Style of the connection.
 * @enum ConnectionStyle
 * @ingroup MEP
 */
enum class ConnectionStyle {
	SimpleBody,
	Flanged,
	Welded
};


/**
 * @brief Direction of the flow.
 * @enum FlowDirection
 * @ingroup MEP
 */
enum class FlowDirection {
	FlowNotDefined,
	FlowIn,
	FlowOut
};


/**
 * @brief Sex of the connection.
 * @enum ConnectionSex
 * @ingroup MEP
 */
enum class ConnectionSex {
	Unisex,
	Male,
	Female
};


/**
 * @brief Placement type of the preferred transition.
 * @enum PreferredTransitionPlacement
 * @ingroup MEP
 */
enum class PreferredTransitionPlacement {
	SmallToLarge,
	LargeToSmall
};


} // namespace ACAPI::MEP

#endif // GS_ACAPI_MEP_ENUMS_HPP