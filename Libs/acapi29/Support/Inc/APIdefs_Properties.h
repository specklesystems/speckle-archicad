// *********************************************************************************************************************
// API definitions - properties
//
// Module:			API
// Namespace:		-
// Contact person:	archicadapi@graphisoft.com
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APIDEFS_PROPERTIES_H)
#define	APIDEFS_PROPERTIES_H

#if defined (_MSC_VER)
#pragma once
#endif


// --- Includes	--------------------------------------------------------------------------------------------------------

#include	"APIdefs_Environment.h"

// from GSRoot
#include	"GSTime.hpp"

// from ARCHICAD
#include	"API_Guid.hpp"


// --- Compiler settings -----------------------------------------------------------------------------------------------

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

// GS Properties

/**
 * @brief Property group types.
 * @ingroup Property
 *
 * @remarks Defines different types of property groups.
 */
typedef enum {
	/** Represents a static built-in group type. */
	API_PropertyStaticBuiltInGroupType,

	/** Represents a dynamic built-in group type. */
	API_PropertyDynamicBuiltInGroupType,

	/** Represents a custom group type. */
	API_PropertyCustomGroupType
} API_PropertyGroupType;

/**
 * @brief Property definition types.
 * @ingroup Property
 *
 * @remarks Defines different types of property definitions.
 */
typedef enum {
	/** It is a built-in property (the definition itself is read only). The set of static built-in properties do not change. */
	API_PropertyStaticBuiltInDefinitionType,

	/** It is a built-in property (the definition itself is read only). The set of dynamic built-in properties may change as a result of Archicad operations. */
	API_PropertyDynamicBuiltInDefinitionType,

	/** It is a user-defined property definition (can be modified). */
	API_PropertyCustomDefinitionType
} API_PropertyDefinitionType;

/**
 * @brief Property collection types.
 * @ingroup Property
 *
 * @remarks Defines different types of property collections.
 */
typedef enum {
	/** Represents an undefined collection type. */
	API_PropertyUndefinedCollectionType,

	/** Represents a single collection type. */
	API_PropertySingleCollectionType,

	/** Represents a list collection type. */
	API_PropertyListCollectionType,

	/** Represents a single choice enumeration collection type. */
	API_PropertySingleChoiceEnumerationCollectionType,

	/** Represents a multiple choice enumeration collection type. */
	API_PropertyMultipleChoiceEnumerationCollectionType
} API_PropertyCollectionType;

/**
 * @brief Property measure types.
 * @ingroup Property
 * 
 * @remarks Defines different types of property measures.
 */
typedef enum {
	/** Represents an undefined measure type. */
	API_PropertyUndefinedMeasureType,

	/** Represents a default measure type. */
	API_PropertyDefaultMeasureType,

	/** Represents a length measure type. */
	API_PropertyLengthMeasureType,

	/** Represents an area measure type. */
	API_PropertyAreaMeasureType,

	/** Represents a volume measure type. */
	API_PropertyVolumeMeasureType,

	/** Represents an angle measure type. */
	API_PropertyAngleMeasureType
} API_PropertyMeasureType;

/**
 * @brief Variant value types.
 * @ingroup Property
 *
 * @remarks Defines different types of variant values.
 */
typedef enum {
	/** Represents an undefined value type. */
	API_PropertyUndefinedValueType,

	/** Represents an integer value type. */
	API_PropertyIntegerValueType,

	/** Represents a real number (double) value type. */
	API_PropertyRealValueType,

	/** Represents a string value type. */
	API_PropertyStringValueType,

	/** Represents a boolean value type. */
	API_PropertyBooleanValueType,

	/** Represents a GUID value type. */
	API_PropertyGuidValueType
} API_VariantType;

/**
 * @brief Describes the status of a variant value.
 * @ingroup Property
 */
typedef enum {
	/** 
	 * Indicates that the variant is invalid in some way, e.g., it is a
	 * result of an unsuccesful operation.
	 */
	API_VariantStatusNull,

	/** The variant is explicitly set to undefined by the user, but it is still valid. */
	API_VariantStatusUserUndefined,

	/** The variant has a usable and valid value. */
	API_VariantStatusNormal
} API_VariantStatus;


/**
 * @brief A container that can store different types of data.
 * @struct API_Variant
 * @ingroup Property
 */
struct API_Variant {

/**
 * @brief Type of the data that the variant stores
 * 		  |API_VariantType|Meaning|
 * 		  |--- |--- |
 * 		  |API_PropertyIntegerValueType|Variant with an integer value|
 * 		  |API_PropertyRealValueType|Variant with a real (double) value|
 * 		  |API_PropertyStringValueType|Variant with a string value|
 * 		  |API_PropertyBooleanValueType|Variant with a boolean value|
 * 		  |API_PropertyGuidValueType|Variant with a GUID value|
 *
 * @var type
 */
	API_VariantType		type;


/**
 * @brief Integer value
 * @var intValue
 */
	Int32			intValue;

/**
 * @brief Real value
 * @var doubleValue
 */
	double			doubleValue;

/**
 * @brief Boolean value
 * @var boolValue
 */
	bool			boolValue;

/**
 * @brief String value
 * @var uniStringValue
 */
	GS::UniString	uniStringValue;

/**
 * @brief GUID value
 * @var guidValue
 */
	API_Guid		guidValue;

	API_Variant () :
		type (API_PropertyUndefinedValueType),
		intValue (0),
		doubleValue (0.0),
		boolValue (false),
		guidValue (APINULLGuid)
	{ }

};

/**
 * @brief A container for storing a single value.
 * @struct API_SingleVariant
 * @ingroup Property
 */
struct API_SingleVariant {

/**
 * @brief The container that stores the value itself.
 * @var variant
 */
	API_Variant	variant;

};

/**
 * @brief A container for storing a list of values.
 * @struct API_ListVariant
 * @ingroup Property
 */
struct API_ListVariant {

/**
 * @brief The container that stores the values.
 * @var variants
 */
	GS::Array<API_Variant> variants;

};

/**
 * @brief A container for storing a single value from a list of allowed values.
 * @struct API_SingleEnumerationVariant
 * @ingroup Property
 */
struct API_SingleEnumerationVariant {

/**
 * @brief The key that refers to a possible enumeration value of the property definition.
 * @var keyVariant
 */
	API_Variant					keyVariant;

/**
 * @brief The display value of the variant.
 * @var displayVariant
 */
	API_Variant					displayVariant;

/**
 * @brief The non-localized value of the variant, if there is one (e.g. in enumeration built-in properties). This value is useful to handle a specific enum value with the same human-readable value in all localized versions.
 * @var nonLocalizedValue
 */
	GS::Optional<GS::UniString>	nonLocalizedValue;

};

/**
 * @brief A container for storing a property's value.
 * @struct API_PropertyValue
 * @ingroup Property
 * @remarks &nbsp; You can easily convert the evaluated property value to display string with the @ref ACAPI_Property_GetPropertyValueString function.
 * 			In Archicad 25 the singleEnumVariant and multipleEnumVariant members were removed. In case of enumeration values the keyVariant of the selected enum value is stored in the singleVariant or listVariant member instead. If you need to, you can retrieve the displayVariant or nonLocalizedValue of the enumeration from the property definition's possibleEnumValues member based on the stored keyVariant.
 */
struct API_PropertyValue {

/**
 * @brief The value of the property if the definition's collectionType is @c API_PropertySingleCollectionType or @c API_PropertySingleChoiceEnumerationCollectionType. In case of enumeration, the keyVariant of the selected enum value is stored here (added in
 * @var singleVariant
 */
	API_SingleVariant				singleVariant;

/**
 * @brief The value of the property if the definition's collectionType is @c API_PropertyListCollectionType or @c API_PropertyMultipleChoiceEnumerationCollectionType. In case of enumeration, the keyVariant of the selected enum values are stored here (added in
 * @var listVariant
 */
	API_ListVariant					listVariant;

/**
 * @brief The status of the property's currently valid value. If the status is not set to APIVariantStatusNormal, the property value is ignored.
 * @var variantStatus
 */
	API_VariantStatus				variantStatus;

	API_PropertyValue ():
		variantStatus (API_VariantStatusNormal)
	{ }

};

/**
 * @brief A structure representing a property default value.
 * @struct API_PropertyDefaultValue
 * @ingroup Property
 */
struct API_PropertyDefaultValue {

/**
 * @brief The basic default value when not using an expression. This content of this value is undefined when expression is used.
 * @var basicValue
 */
	API_PropertyValue			basicValue;

/**
 * @brief The list of expression strings in the default value. The content of this array is undefined when basic default value is used.
 * @var propertyExpressions
 */
	GS::Array<GS::UniString>	propertyExpressions;

/**
 * @brief Specifies if the default value holds expression or not.
 * @var hasExpression
 */
	bool						hasExpression;

	API_PropertyDefaultValue () :
		hasExpression (false)
	{ }

};

/**
 * @brief A structure representing a property group.
 * @struct API_PropertyGroup
 * @ingroup Property
 */
struct API_PropertyGroup {

/**
 * @brief The type of this property group
 * 		  |API_PropertyGroupType|Meaning|
 * 		  |--- |--- |
 * 		  |API_PropertyStaticBuiltInGroupType|All of the property definitions in this group are API_PropertyStaticBuiltInDefinitionType|
 * 		  |API_PropertyDynamicBuiltInGroupType|All of the property definitions in this group are API_PropertyDynamicBuiltInDefinitionType|
 * 		  |API_PropertyCustomGroupType|All of the property definitions in this group are API_PropertyCustomDefinitionType|
 *
 * @var groupType
 */
	API_PropertyGroupType	groupType;

/**
 * @brief The unique identifier of the property group
 * @var guid
 */
	API_Guid				guid;

/**
 * @brief The name of the property group
 * @remarks This name should only be used for user defined property groups.
 * @var name
 */
	GS::UniString			name;

/**
 * @brief The description of the property group
 * @var description
 */
	GS::UniString			description;

	API_PropertyGroup () :
		groupType (API_PropertyCustomGroupType),
		guid (APINULLGuid)
	{ }

};

/**
 * @brief A structure representing a property definition.
 * @struct API_PropertyDefinition
 * @ingroup Property
 * @remarks &nbsp; In Archicad v2018 the defaultValue 's type has been changed to @ref API_PropertyDefaultValue from @ref API_PropertyValue.
 */
struct API_PropertyDefinition {

/**
 * @brief The type of this property definition:
 * 		  |API_PropertyDefinitionType|Meaning|
 * 		  |--- |--- |
 * 		  |API_PropertyStaticBuiltInDefinitionType|It is a built-in property (the definition itself is read only). The set of static built-in properties do not change.|
 * 		  |API_PropertyDynamicBuiltInDefinitionType|It is a built-in property (the definition itself is read only). The set of dynamic built-in properties may change as a result of Archicad operations.|
 * 		  |API_PropertyCustomDefinitionType|It is a user-defined property definition (can be modified).|
 *
 * @var definitionType
 */
	API_PropertyDefinitionType					definitionType;

/**
 * @brief The unique identifier of the property definition
 * @var guid
 */
	API_Guid									guid;

/**
 * @brief The unique identifier of the property group that contains this definition
 * @var groupGuid
 */
	API_Guid									groupGuid;

/**
 * @brief The name of the property definition
 * @var name
 */
	GS::UniString								name;

/**
 * @brief The description of the property definition
 * @var description
 */
	GS::UniString								description;

/**
 * @brief The collection type of the property definition
 * 		  |API_PropertyCollectionType|Meaning|
 * 		  |--- |--- |
 * 		  |API_PropertySingleCollectionType|The property stores a single value|
 * 		  |API_PropertyListCollectionType|The property stores a list of values|
 * 		  |API_PropertySingleChoiceEnumerationCollectionType|The property stores a single value from a list of allowed values|
 * 		  |API_PropertyMultipleChoiceEnumerationCollectionType|The property stores a subset of values from a list of allowed values|
 *
 * @var collectionType
 */
	API_PropertyCollectionType					collectionType;

/**
 * @brief Type of the data that the property stores
 * 		  |API_VariantType|Meaning|
 * 		  |--- |--- |
 * 		  |API_PropertyIntegerValueType|The property has integer value(s)|
 * 		  |API_PropertyRealValueType|The property has real (double) value(s)|
 * 		  |API_PropertyBooleanValueType|The property has boolean value(s)|
 * 		  |API_PropertyStringValueType|The property has string value(s)|
 *
 * @var valueType
 */
	API_VariantType								valueType;

/**
 * @brief Measure type of the data that the property stores. Measure types other than @c API_PropertyDefaultMeasureType (and @c API_PropertyUndefinedMeasureType) are only valid for properties which are of a single real type (collectionType is @c API_PropertySingleCollectionType and valueType is @c API_PropertyRealValueType). @c API_PropertyMeasureType Meaning @c API_PropertyUndefinedMeasureType The property is in invalid state. @c API_PropertyDefaultMeasureType The property doesn't have special measure. @c API_PropertyLengthMeasureType The property has length value. @c API_PropertyAreaMeasureType The property has area value. @c API_PropertyVolumeMeasureType The property has volume value. @c API_PropertyAngleMeasureType The property has angle value.
 * 		  |API_PropertyMeasureType|Meaning|
 * 		  |--- |--- |
 * 		  |API_PropertyUndefinedMeasureType|The property is in invalid state.|
 * 		  |API_PropertyDefaultMeasureType|The property doesn't have special measure.|
 * 		  |API_PropertyLengthMeasureType|The property has length value.|
 * 		  |API_PropertyAreaMeasureType|The property has area value.|
 * 		  |API_PropertyVolumeMeasureType|The property has volume value.|
 * 		  |API_PropertyAngleMeasureType|The property has angle value.|
 *
 * @var measureType
 */
	API_PropertyMeasureType						measureType;

/**
 * @brief The default value of this property definition.
 * @var defaultValue
 */
	API_PropertyDefaultValue					defaultValue;

/**
 * @brief The list of classification GUIDs this property definition is available for.
 * @var availability
 */
	GS::Array<API_Guid>							availability;

/**
 * @brief The list of available values in case of an enumeration value type.
 * @var possibleEnumValues
 */
	GS::Array<API_SingleEnumerationVariant>		possibleEnumValues;

/**
 * @brief Specifies if the property values of this definition can possibly be edited. For custom properties it is always true, for built-ins, it might be false.
 * @var canValueBeEditable
 */
	bool										canValueBeEditable;

	API_PropertyDefinition () :
		definitionType (API_PropertyCustomDefinitionType),
		guid (APINULLGuid),
		groupGuid (APINULLGuid),
		collectionType (API_PropertyUndefinedCollectionType),
		valueType (API_PropertyUndefinedValueType),
		measureType (API_PropertyDefaultMeasureType),
		canValueBeEditable (false)
	{ }

};

/**
 * @brief Property definition filters.
 * @ingroup Property
 *
 * @remarks Defines different filters for property definitions.
 */
typedef enum {
	/** Represents a user-defined property definition filter. */
	API_PropertyDefinitionFilter_UserDefined,

	/** Represents a built-in property definition filter. */
	API_PropertyDefinitionFilter_BuiltIn,

	/** Represents a filter for all property definitions. */
	API_PropertyDefinitionFilter_All
} API_PropertyDefinitionFilter;

/**
 * @brief Property value status.
 * @ingroup Property
 *
 * @remarks Defines the status of a property value.
 */
typedef enum {
	/** Indicates that the property is not available. */
	API_Property_NotAvailable,

	/** Indicates that the property has not been evaluated. */
	API_Property_NotEvaluated,

	/** Indicates that the property has a value. */
	API_Property_HasValue
} API_PropertyValueStatus;


/**
 * @brief A container that can store different types of data.
 * @struct API_Property
 * @ingroup Property
 * @remarks You can easily convert the evaluated property value to display string with the @ref ACAPI_Property_GetPropertyValueString function.
 * 			In Archicad 25 the `singleEnumVariant` and `multipleEnumVariant` members were removed.
 * 			In case of enumeration values the `keyVariant` of the selected enum value is stored in the `singleVariant` or `listVariant` member instead.
 * 			If you need to, you can retrieve the `displayVariant` or `nonLocalizedValue` of the enumeration from the property definition's `possibleEnumValues`
 * 			member based on the stored `keyVariant`.
 */
struct API_Property {

/**
 * @brief The definition of the property
 * @var definition
 */
	API_PropertyDefinition	definition;

/**
 * @brief Tells whether the property could be evaluated or not.
 * 		  If yes, then the value always contains the evaluated value (independently from the `isDefault` field). If not, the content of the value field is undefined.
 * 		  | Status | Meaning |
 * 		  |--------|---------|
 * 		  | @c API_Property_NotAvailable | The property is not available for the element/attribute. Therefore the content of the value field is undefined.|
 * 		  | @c API_Property_NotEvaluated | The property could not be evaluated for the element/attribute. Therefore the content of the value field is undefined. This may be caused by several things, e.g. the property contains an expression which cannot be evaluated; a static built-in property is currently not evaluable (e.g. composite attribute index cannot be retrieved for a basic wall), etc.|
 * 		  | @c API_Property_HasValue | The property is available for the element/attribute and has been evaluated. The value field contains the evaluated value.|
 * @var status
 */
	API_PropertyValueStatus status;

/**
 * @brief The evaluated value of the property. Valid only if the status is @c API_Property_HasValue, in this case this field always contains the evaluated value even if it's a default or custom value.
 * @var value
 */
	API_PropertyValue		value;

/**
 * Tells whether the value comes from the default value of the property. Note that the value field always contains the evaluated value even if it's coming from the default value of the property.
 * @var isDefault
 */
	bool					isDefault;

	API_Property () : isDefault (true), status (API_Property_NotAvailable)  {}
};


#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif


/**
 * An interface for getting units of measurement for string to property value conversion. The class
 * which implements the interface has to return the appropriate units of measurement and delimiters. It is only
 * used for @ref ACAPI_Property_SetPropertyValueFromString.
 * @class API_PropertyConversionUtilsInterface
 * @ingroup Property
 * @since Archicad 25
 * @remarks Interface class for passing in the desired units of measurement to @ref ACAPI_Property_SetPropertyValueFromString.
 * 			For a detailed example see the Property_Test test add-on.
 */
class API_PropertyConversionUtilsInterface {
public:
	virtual ~API_PropertyConversionUtilsInterface () = default;

/**
 * @return Returns the degree symbol.
 * @ingroup Property
 */
	virtual const GS::UniString& GetDegreeSymbol1	() const = 0;

/**
 * @return Returns the degree symbol.
 * @ingroup Property
 */
	virtual const GS::UniString& GetDegreeSymbol2	() const = 0;

/**
 * @return Returns the minute symbol.
 * @ingroup Property
 */
	virtual const GS::UniString& GetMinuteSymbol	() const = 0;

/**
 * @return Returns the second symbol.
 * @ingroup Property
 */
	virtual const GS::UniString& GetSecondSymbol	() const = 0;

/**
 * @return Returns the gradient symbol.
 * @ingroup Property
 */
	virtual const GS::UniString& GetGradientSymbol	() const = 0;

/**
 * @return Returns the radian symbol.
 * @ingroup Property
 */
	virtual const GS::UniString& GetRadianSymbol	() const = 0;

/**
 * @return Returns the north symbol.
 * @ingroup Property
 */
	virtual const GS::UniString& GetNorthSymbol () const = 0;

/**
 * @return Returns the south symbol.
 * @ingroup Property
 */
	virtual const GS::UniString& GetSouthSymbol () const = 0;

/**
 * @return Returns the east symbol.
 * @ingroup Property
 */
	virtual const GS::UniString& GetEastSymbol	() const = 0;

/**
 * @return Returns the west symbol.
 * @ingroup Property
 */
	virtual const GS::UniString& GetWestSymbol	() const = 0;

/**
 * @return Returns the character of the decimal delimiter.
 * @ingroup Property
 */
	virtual GS::uchar_t					GetDecimalDelimiterChar		() const = 0;

/**
 * @return Returns the character of the thousands separator.
 * @ingroup Property
 */
	virtual GS::Optional<GS::UniChar>	GetThousandSeparatorChar	() const = 0;

/**
 * @return Returns the value for length unit preferences.
 * @ingroup Property
 */
	virtual API_LengthTypeID	GetLengthType	() const = 0;

/**
 * @return Returns the value for area unit preferences.
 * @ingroup Property
 */
	virtual API_AreaTypeID		GetAreaType		() const = 0;

/**
 * @return Returns the value for volume unit preferences.
 * @ingroup Property
 */
	virtual API_VolumeTypeID	GetVolumeType	() const = 0;

/**
 * @return Returns the value for angle unit preferences.
 * @ingroup Property
 */
	virtual API_AngleTypeID		GetAngleType	() const = 0;
};

#ifdef __clang__
#pragma clang diagnostic pop
#endif

// ---------------------------------------------------------------------------------------------------------------------

#endif
