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

// IFC Properties & Attributes

typedef enum {
	API_IFCPropertySingleValueType,
	API_IFCPropertyListValueType,
	API_IFCPropertyBoundedValueType,
	API_IFCPropertyEnumeratedValueType,
	API_IFCPropertyTableValueType
} API_IFCPropertyType;

/**
 * @brief IFC property header structure.
 * @struct API_IFCPropertyHead
 * @ingroup Element
 * @remarks This structure holds common information of all IFC Property types. propertyName and propertySetName shall not be empty strings. propertyName and propertySetName pairs of an element are unique.
 */
struct API_IFCPropertyHead {

/**
 * @brief Name of the containing propertyset
 * @var propertySetName
 */
	GS::UniString					propertySetName;

/**
 * @brief Name of the property
 * @var propertyName
 */
	GS::UniString					propertyName;

/**
 * @brief Description of the property
 * @var propertyDescription
 */
	GS::UniString					propertyDescription;

/**
 * @brief Type of the IFC property
 * 		  |API_IFCPropertyType|Meaning|
 * 		  |--- |--- |
 * 		  |API_IFCPropertySingleValueType|Property with a single value|
 * 		  |API_IFCPropertyListValueType|Property with a list of values|
 * 		  |API_IFCPropertyBoundedValueType|Property with a lower bound, upper bound and set point value|
 * 		  |API_IFCPropertyEnumeratedValueType|Property with a list of possible and selected values|
 * 		  |API_IFCPropertyTableValueType|Property with a list of value pairs|
 * @var propertyType
 */
	API_IFCPropertyType				propertyType;

/**
 * @brief Indicate that the property is writeable or readOnly.
 * @var readOnly
 */
	bool							readOnly;

};

typedef enum {
	API_IFCPropertyAnyValueIntegerType,
	API_IFCPropertyAnyValueRealType,
	API_IFCPropertyAnyValueBooleanType,
	API_IFCPropertyAnyValueLogicalType,
	API_IFCPropertyAnyValueStringType
} API_IFCPropertyValuePrimitiveType;

/**
 * @brief IFC property base value data container.
 * @struct API_IFCPropertyAnyValue
 * @ingroup Element
 * @remarks This structure contains the base value of an IFC property in one of it's members.
 * 			The `primitiveType` field is an output parameter only, shall not be set when setting up a new @ref API_IFCPropertyValue structure.
 */
struct API_IFCPropertyAnyValue {

/**
 * @brief Primitive type
 * 		  |API_IFCPropertyValuePrimitiveType|Meaning|
 * 		  |--- |--- |
 * 		  |API_IFCPropertyAnyValueIntegerType|Value is stored as an integer|
 * 		  |API_IFCPropertyAnyValueRealType|Value is stored as a double|
 * 		  |API_IFCPropertyAnyValueBooleanType|Value is stored as a boolean|
 * 		  |API_IFCPropertyAnyValueLogicalType|Value is stored as an integer, see @ref API_IFCPropertyValue for possible values|
 * 		  |API_IFCPropertyAnyValueStringType|Value is stored as a string|
 * @var primitiveType
 */
	API_IFCPropertyValuePrimitiveType primitiveType;

/**
 * @brief If the optional value is filled
 * @var hasValue
 */
	bool							hasValue;

/**
 * @brief Double value
 * @var doubleValue
 */
	double							doubleValue;

/**
 * @brief Integer value
 * @var intValue
 */
	Int64							intValue;

/**
 * @brief Boolean value
 * @var boolValue
 */
	bool							boolValue;

/**
 * @brief String value
 * @var stringValue
 */
	GS::UniString					stringValue;

};

/**
 * @brief IFC property value data container.
 * @struct API_IFCPropertyValue
 * @ingroup Element
 * @remarks This structure contains the value of an IFC property. The valueType field determines which field of the value structure contains the base value. Each IFC type has a primitive type, e.g. IfcLabel and IfcText both contain a string, IfcReal and IfcPositiveLengthMeasure both contain a real value and so on. IfcLogical type is stored as an integer:
 * 			| FALSE | 0 |
 * 			| UNKNOWN | 1 |
 * 			| TRUE | 2 |
 */
struct API_IFCPropertyValue {

/**
 * @brief Base value container
 * @var value
 */
	API_IFCPropertyAnyValue			value;

/**
 * @brief IFC type of the value in string format
 * @var valueType
 */
	GS::UniString					valueType;

};

/**
 * @brief IFC property with a single value.
 * @struct API_IFCPropertySingleValue
 * @ingroup Element
 * @remarks This structure contains the value of an IfcPropertySingleValue
 */
struct API_IFCPropertySingleValue {

/**
 * @brief Value of the property
 * @var nominalValue
 */
	API_IFCPropertyValue			nominalValue;

};

/**
 * @brief IFC property with a lowerbound and an upperbound value.
 * @struct API_IFCPropertyBoundedValue
 * @ingroup Element
 * @remarks This structure contains the lowerbound and upperbound values of an IfcPropertyBoundedValue. Both values shall have the same type.
 */
struct API_IFCPropertyBoundedValue {

/**
 * @brief Lower bound value of the property
 * @var lowerBoundValue
 */
	API_IFCPropertyValue			lowerBoundValue;

/**
 * @brief Upper bound value of the property
 * @var upperBoundValue
 */
	API_IFCPropertyValue			upperBoundValue;

/**
 * @brief Set point value of the property
 * @var setPointValue
 */
	API_IFCPropertyValue			setPointValue;

};

/**
 * @brief IFC property with a list of values.
 * @struct API_IFCPropertyListValue
 * @ingroup Element
 * @remarks This structure contains the list of values of an IfcPropertyListValue. At least one value shall be set. All values shall have the same type.
 */
struct API_IFCPropertyListValue {

/**
 * @brief Values of the property
 * @var listValues
 */
	GS::Array<API_IFCPropertyValue>	listValues;

};

/**
 * @brief IFC property with a list of possible and selected value.
 * @struct API_IFCPropertyEnumeratedValue
 * @ingroup Element
 * @remarks This structure contains the list of&nbsp; possible and selected values of an IfcPropertyEnumeratedValue. All values shall have the same type. The enumerationReference shall contain all the values of enumerationValues, which shall contain at least one value.
 */
struct API_IFCPropertyEnumeratedValue {

/**
 * @brief List of possible values of the property
 * @var enumerationReference
 */
	GS::Array<API_IFCPropertyValue>	enumerationReference;

/**
 * @brief List of selected values of the property
 * @var enumerationValues
 */
	GS::Array<API_IFCPropertyValue>	enumerationValues;

};

/**
 * @brief IFC property with a list of value pairs.
 * @struct API_IFCPropertyTableValue
 * @ingroup Element
 * @remarks This structure contains a list of&nbsp; value pairs of an IfcPropertTableValue. The definingValues and definedValues shall have the same type inside, but the two types can differ. The size of the two arrays shall be the same, at least one pair of values shall be set.
 */
struct API_IFCPropertyTableValue {

/**
 * @brief List of defning values, must be unique
 * @var definingValues
 */
	GS::Array<API_IFCPropertyValue>	definingValues;

/**
 * @brief List of defined values, does not have to be unique
 * @var definedValues
 */
	GS::Array<API_IFCPropertyValue>	definedValues;

};

/**
 * @brief IFC property container structure.
 * @struct API_IFCProperty
 * @ingroup Element
 * @remarks This structure contains the data of an Ifc(Simple)Property. head contains common information for each type. head.propertyType determines which value member contains value data.
 */
struct API_IFCProperty {

/**
 * @brief Property header information
 * @var head
 */
	API_IFCPropertyHead				head;


/**
 * @brief IfcPropertySingleValue values
 * @var singleValue
 */
	API_IFCPropertySingleValue		singleValue;

/**
 * @brief IfcPropertyBoundedValue values
 * @var boundedValue
 */
	API_IFCPropertyBoundedValue		boundedValue;

/**
 * @brief IfcPropertyListValue values
 * @var listValue
 */
	API_IFCPropertyListValue		listValue;

/**
 * @brief IfcPropertyEnumeratedValue values
 * @var enumeratedValue
 */
	API_IFCPropertyEnumeratedValue	enumeratedValue;

/**
 * @brief IfcPropertyTableValue values
 * @var tableValue
 */
	API_IFCPropertyTableValue		tableValue;

};

/**
 * @brief IFC attribute structure.
 * @struct API_IFCAttribute
 * @ingroup Element
 * @remarks This structure contains the data of an IFC attribute. Attributes of an IFC type are a fix list, so this structure can be used to get and modify attributes only. readOnly flag of an attribute cannot be changed, it is informational only.
 */
struct API_IFCAttribute {

/**
 * @brief Name of the attribute
 * @var attributeName
 */
	GS::UniString					attributeName;

/**
 * @brief IFC type of the attribute in string format
 * @var attributeType
 */
	GS::UniString					attributeType;

/**
 * @brief Value of the attribute in string format
 * @var attributeValue
 */
	GS::UniString					attributeValue;

/**
 * @brief In case of optional attributes it says if the attribute is set and checked on the user interface
 * @var hasValue
 */
	bool							hasValue;

/**
 * @brief Whether the attribute is read-only
 * @var readOnly
 */
	bool							readOnly;

};

/**
 * @brief IFC classification structure.
 * @struct API_IFCClassification
 * @ingroup Element
 * @remarks This structure contains the data of an IfcClassification.
 */
struct API_IFCClassification {

/**
 * @brief source of classification
 * @var source
 */
	GS::Optional<GS::UniString>		source;

/**
 * @brief edition of classification
 * @var edition
 */
	GS::Optional<GS::UniString>		edition;

/**
 * @brief the date on which the edition of the classification used became valid
 * @var editionDate
 */
	GS::Optional<GS::UniString>		editionDate;

/**
 * @brief name of classification
 * @var name
 */
	GS::UniString					name;

/**
 * @brief description of the classification
 * @var description
 */
	GS::Optional<GS::UniString>		description;

/**
 * @brief resource identifier or locator of the classification
 * @var location
 */
	GS::Optional<GS::UniString>		location;

};

/**
 * @brief IFC classificationreference structure.
 * @struct API_IFCClassificationReference
 * @ingroup Element
 * @remarks This structure contains the data of an IfcClassificationReference. referenceName is unique for classificationreferences of an element.
 */
struct API_IFCClassificationReference {

/**
 * @brief name of the IfcRelAssociatesClassification
 * @var referenceName
 */
	GS::UniString					referenceName;

/**
 * @brief whether the classificationreference is read-only on user interface
 * @var readOnly
 */
	bool							readOnly;


/**
 * @brief location of the classificationreference
 * @var location
 */
	GS::Optional<GS::UniString>		location;

/**
 * @brief name of the classificationreference
 * @var name
 */
	GS::Optional<GS::UniString>		name;

/**
 * @brief identification of the classificationreference
 * @var identification
 */
	GS::Optional<GS::UniString>		identification;


/**
 * @brief referencedsource of the classificationreference
 * @var referencedSource
 */
	API_IFCClassification			referencedSource;

};

// GS Properties

typedef enum {
	API_PropertyStaticBuiltInGroupType,
	API_PropertyDynamicBuiltInGroupType,
	API_PropertyCustomGroupType
} API_PropertyGroupType;

typedef enum {
	API_PropertyStaticBuiltInDefinitionType,
	API_PropertyDynamicBuiltInDefinitionType,
	API_PropertyCustomDefinitionType
} API_PropertyDefinitionType;

typedef enum {
	API_PropertyUndefinedCollectionType,
	API_PropertySingleCollectionType,
	API_PropertyListCollectionType,
	API_PropertySingleChoiceEnumerationCollectionType,
	API_PropertyMultipleChoiceEnumerationCollectionType
} API_PropertyCollectionType;

typedef enum {
	API_PropertyUndefinedMeasureType,
	API_PropertyDefaultMeasureType,
	API_PropertyLengthMeasureType,
	API_PropertyAreaMeasureType,
	API_PropertyVolumeMeasureType,
	API_PropertyAngleMeasureType
} API_PropertyMeasureType;

typedef enum {
	API_PropertyUndefinedValueType,
	API_PropertyIntegerValueType,
	API_PropertyRealValueType,
	API_PropertyStringValueType,
	API_PropertyBooleanValueType,
	API_PropertyGuidValueType
} API_VariantType;

/**
 * @brief Describes the status of a variant value.
 * @enum API_VariantStatus
 * @ingroup Property
 */
typedef enum {
	API_VariantStatusNull,
	API_VariantStatusUserUndefined,
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

typedef enum
{
	API_PropertyDefinitionFilter_UserDefined,
	API_PropertyDefinitionFilter_BuiltIn,
	API_PropertyDefinitionFilter_All
} API_PropertyDefinitionFilter;


typedef enum {
	API_Property_NotAvailable,
	API_Property_NotEvaluated,
	API_Property_HasValue,
}  API_PropertyValueStatus;

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
