#ifndef GS_ACAPI_MEP_ENUMS_HPP
#define GS_ACAPI_MEP_ENUMS_HPP


#include "MEPAPIExport.hpp"


namespace ACAPI::MEP {


/** @ingroup MEP */
enum class Domain {
	Ventilation,
	Piping,
	CableCarrier
};


/** @ingroup MEP */
enum class ConnectorShape {
	Rectangular,
	Circular,
	UShape
};


/** @ingroup MEP */
enum class ConnectionStyle {
	NoConnector,
	Flanged,
	Overlap
};


/** @ingroup MEP */
enum class FlowDirection {
	FlowNotDefined,
	FlowIn,
	FlowOut
};


/** @ingroup MEP */
enum class ConnectionSex {
	Unisex,
	Male,
	Female
};


/** @ingroup MEP */
enum class PreferredTransitionPlacement {
	SmallToLarge,
	LargeToSmall
};


/** @ingroup MEP */
enum class PreferenceTableShape {
	Rectangular,
	Circular
};


} // namespace ACAPI::MEP

#endif // GS_ACAPI_MEP_ENUMS_HPP