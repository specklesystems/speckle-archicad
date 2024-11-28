#if !defined GS_APIDEFS_COMPONENT_H
#define GS_APIDEFS_COMPONENT_H


#include "API_Guid.hpp"


#ifdef __cplusplus
extern "C" {
#endif


struct API_ComponentID {
	API_Guid	componentGuid;
};


struct API_ElemComponentID {
	API_Guid		elemGuid;
	API_ComponentID	componentID;
};


#ifdef __cplusplus
}
#endif

#endif
