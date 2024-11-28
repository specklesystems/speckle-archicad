#if !defined GS_APIDEFS_COMPONENT_H
#define GS_APIDEFS_COMPONENT_H


#include "API_Guid.hpp"



struct API_ComponentID {
	API_Guid	componentGuid;
};


struct API_ElemComponentID {
	API_Guid		elemGuid;
	API_ComponentID	componentID;
};


#endif
