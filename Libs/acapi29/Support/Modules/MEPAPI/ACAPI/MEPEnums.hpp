#ifndef GS_ACAPI_MEP_ENUMS_HPP
#define GS_ACAPI_MEP_ENUMS_HPP


#include "MEPAPIExport.hpp"


namespace ACAPI::MEP {


/**
 * @brief Type of the domain.
 * @ingroup MEP
 *
 * @remarks Specifies the type of domain within the Mechanical, Electrical, and Plumbing (MEP) context.
 */
enum class Domain {

    /** Ventilation domain, typically involves HVAC systems and related components. */
    Ventilation,

    /** Piping domain, generally includes plumbing and other fluid transport systems. */
    Piping,

    /** Cable carrier domain, encompasses systems for routing and supporting electrical cables. */
    CableCarrier
};


/**
 * @brief Shape of the connector.
 * @ingroup MEP
 *
 * @remarks Specifies the shape of connectors used in Mechanical, Electrical, and Plumbing (MEP) systems.
 */
enum class ConnectorShape {

    /** Rectangular shape, commonly used in ductwork and rectangular piping systems. */
    Rectangular,

    /** Circular shape, often used for pipes and round ducts. */
    Circular,

    /** Oval shape, used in specific applications where space constraints or aerodynamic properties are considered. */
    Oval,

    /** U-shape, typically used for specialized connectors and fittings in various MEP systems. */
    UShape
};


/**
 * @brief Style of the connection.
 * @ingroup MEP
 *
 * @remarks Specifies the style of connections used in Mechanical, Electrical, and Plumbing (MEP) systems.
 */
enum class ConnectionStyle {

    /** Simple body connection, typically used for straightforward and direct connections without additional features. */
    SimpleBody,

    /** Flanged connection, featuring flanges for bolting connections, commonly used in piping systems for easy assembly and disassembly. */
    Flanged,

    /** Welded connection, where the components are joined by welding, providing a strong and permanent connection. */
    Welded
};


/**
 * @brief Direction of the flow.
 * @ingroup MEP
 *
 * @remarks Specifies the direction of the flow in Mechanical, Electrical, and Plumbing (MEP) systems.
 */
enum class FlowDirection {

    /** The flow direction is not defined. */
    FlowNotDefined,

    /** The flow is directed inward. */
    FlowIn,

    /** The flow is directed outward. */
    FlowOut
};


/**
 * @brief Sex of the connection.
 * @ingroup MEP
 *
 * @remarks Defines the sex of the connections in Mechanical, Electrical, and Plumbing (MEP) systems.
 */
enum class ConnectionSex {

    /** Unisex connection, suitable for both male and female counterparts. */
    Unisex,

    /** Male connection, designed to connect with a female counterpart. */
    Male,

    /** Female connection, designed to connect with a male counterpart. */
    Female
};


/**
 * @brief Placement type of the preferred transition.
 * @ingroup MEP
 *
 * @remarks Determines the preferred transition placement type in Mechanical, Electrical, and Plumbing (MEP) systems.
 */
enum class PreferredTransitionPlacement {

    /** Transition from a smaller size to a larger size. */
    SmallToLarge,

    /** Transition from a larger size to a smaller size. */
    LargeToSmall
};


} // namespace ACAPI::MEP

#endif // GS_ACAPI_MEP_ENUMS_HPP