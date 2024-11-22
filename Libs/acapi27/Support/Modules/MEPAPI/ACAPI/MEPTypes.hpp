#ifndef GS_ACAPI_MEP_TYPES_HPP
#define GS_ACAPI_MEP_TYPES_HPP

#include "MEPEnums.hpp"

// ARCHICADAPI
#include "APIdefs_Base.h"
#include "ACAPI/Object.hpp"

/** @brief Returns the token associated with the AddOn.
	@ingroup AddOnIdentification
	@return The token associated with the add-on.
	@remarks It is not guaranteed that this function will always return the same value. Always obtain your
   token by calling this function on demand.
*/
API_Token ACAPI_GetToken (void);

namespace ACAPI::MEP {


class UniqueID;

/**	@brief Defines the orientation with the help of a direction and rotation vector.
	@struct Orientation
	@ingroup MEP
*/
struct Orientation {
	API_Vector3D direction;
	API_Vector3D rotation;
};

/**	@brief Defines the necessary data for placing RoutingSegments of a RouteElement.
	@struct RoutingSegmentCrossSectionData
	@ingroup MEP
*/
struct RoutingSegmentCrossSectionData {
	double width;
	double height;
	ConnectorShape shape;
};


} // ACAPI::MEP


#endif