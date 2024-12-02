#if !defined GS_APIDEFS_COMPONENT_H
#define GS_APIDEFS_COMPONENT_H


#include "API_Guid.hpp"



/**
 * @brief Identifies a component.
 * @struct API_ComponentID
 * @ingroup Element
 * @remarks Use @ref API_ElemComponentID to identify a component of an element.
 */
struct API_ComponentID {

/**
 * @brief Guid of the component.
 * @var componentGuid
 */
	API_Guid	componentGuid;

};


/**
 * @brief Identifies a component of an element.
 * @struct API_ElemComponentID
 * @ingroup Element
 */
struct API_ElemComponentID {

/**
 * @brief Guid of the element. componentID identifies a component that belongs to it.
 * @var elemGuid
 */
	API_Guid		elemGuid;

/**
 * @brief Identifier of the component.
 * @var componentID
 */
	API_ComponentID	componentID;

};


#endif
