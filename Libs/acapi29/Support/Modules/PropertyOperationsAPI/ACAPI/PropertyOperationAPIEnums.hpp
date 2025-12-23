#ifndef GS_ACAPI_PROPERTYOPERATION_ENUMS_HPP
#define GS_ACAPI_PROPERTYOPERATION_ENUMS_HPP

namespace ACAPI::PropertyOperations {

/**
 * @brief GroupAvailability.
 * @enum GroupAvailability
 * 
 */
enum class GroupAvailability {
	EveryTypesAvailable,
	OnlyAll_All2DTypesAvailable,
	OnlyAll3DTypesAvailable,
	OnlyAll_All3DTypesAvailable,
	OnlyAllTypesAvailable,
	OnlyElemAvailable
};


/**
 * @brief CriteriaEnvironmentType.
 * @enum CriteriaEnvironmentType
 * 
 */
enum class CriteriaEnvironmentType {
	OverrideAvailable,
	NotificationNotAvailable,
	OnlyOverrideAndCollisionDetectionAvailable,
	OnlyCollisionDetectionAvailable,
	OverrideNotAvailable
};


/**
 * @brief PropertyToUseInContext.
 * @enum PropertyToUseInContext
 * 
 */
enum class PropertyToUseInContext {
	FieldOnly,
	CriteriaOnly,
	FieldAndCriteria
};


/**
 * @brief PropertyValueType.
 * @enum PropertyValueType
 * 
 */
enum class PropertyValueType {
	Integer,
	Numeric,
	String,
	Boolean
};

} // namespace ACAPI::PropertyOperations

#endif // GS_ACAPI_PROPERTYOPERATION_ENUMS_HPP