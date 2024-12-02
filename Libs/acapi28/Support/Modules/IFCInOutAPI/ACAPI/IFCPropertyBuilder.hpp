#ifndef IFCAPI_PROPERTYBUILDER_HPP
#define IFCAPI_PROPERTYBUILDER_HPP

#pragma once

#include "IFCInOutAPIExport.hpp"

#include "IFCAttribute.hpp"
#include "IFCClassificationReference.hpp"
#include "IFCProperty.hpp"

// ACAPI
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"

#include <optional>


namespace IFCAPI {

namespace Impl { class PropertyBuilder; }

namespace v1 {

/**
 * @brief To create IFC attribute, property or classification reference.
 * @ingroup IFC
 * @since Archicad 28
 * @remarks See IFCHook_Test.cpp for a complete example.
 */
class IFCINOUTAPI_DLL_EXPORT PropertyBuilder final : public ACAPI::Object {
private:
	PropertyBuilder (std::shared_ptr<Impl::PropertyBuilder> impl);

	static PropertyBuilder	GetPropertyBuilder (const API_Token& token);

public:
	friend PropertyBuilder	GetPropertyBuilder ();

public:
	~PropertyBuilder ();

	/**
	 * @brief Create an IFC value.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param valueType [in] type of the value as defined in the IFC schema, e.g. "IfcBoolean".
	 * @param anyValue [in] value of the IFC value.
	 * @return If able, an IFC value object, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - Invalid parameter passed.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC add-on is not present.
	 * @remarks Result can be used to create IFC properties.
	 */
	ACAPI::Result<Value> CreateValue (const IFCAPI::IFCType& valueType, const IFCAPI::AnyValue& anyValue) const;

	//! @cond Doxygen_Suppress
	ACAPI::Result<Value> CreateValue (const IFCAPI::IFCType&, const char*) = delete;
	//! @endcond

	/**
	 * @brief Create an empty IFC value.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return an empty IFC value.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC add-on is not present.
	 * @remarks Result can be used when creating a bounded property value.
	 */
	Value CreateEmptyValue () const;

	/**
	 * @brief Create an IFC attribute from scratch.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param name [in] name of the IFC attribute as defined in the IFC schema, e.g. "Description".
	 * @param value [in] value of the IFC attribute.
	 * @return If able, an IFC attribute object, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - Invalid name passed.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC add-on is not present.
	 * @remarks Result can be used to map data to Objects' IFC attributes using IFC Hooks.
	 */
	ACAPI::Result<IFCAPI::Attribute>	CreateAttribute (const GS::UniString& name, const std::optional<GS::UniString>& value) const;

	/**
	 * @brief Create an IFC property single value.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param propertySetName [in] name of the property set which contains the property.
	 * @param name [in] name of the IFC property.
	 * @param value [in] value of the IFC property.
	 * @return If able, an IFC property object, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - Invalid parameter passed.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC add-on is not present.
	 * @remarks Result can be used to map data to Objects' IFC properties using IFC Hooks.
	 */
	ACAPI::Result<IFCAPI::Property>		CreatePropertySingleValue (const GS::UniString& propertySetName, const GS::UniString& name, const IFCAPI::Value& value) const;

	/**
	 * @brief Create an IFC property table value.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param propertySetName [in] name of the property set which contains the property.
	 * @param name [in] name of the IFC property.
	 * @param definingValues [in] list of defining values of the IFC property table value.
	 * @param definedValues [in] list of defined values of the IFC property table value.
	 * @return If able, an IFC property object, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - Invalid parameter passed.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC add-on is not present.
	 * @remarks Result can be used to map data to Objects' IFC properties using IFC Hooks.
	 */
	ACAPI::Result<IFCAPI::Property>		CreatePropertyTableValue (const GS::UniString& propertySetName, const GS::UniString& name, const std::vector<IFCAPI::Value>& definingValues, const std::vector<IFCAPI::Value>& definedValues) const;

	/**
	 * @brief Create an IFC property list value.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param propertySetName [in] name of the property set which contains the property.
	 * @param name [in] name of the IFC property.
	 * @param listValues [in] list of values of the IFC property list value.
	 * @return If able, an IFC property object, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - Invalid parameter passed.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC add-on is not present.
	 * @remarks Result can be used to map data to Objects' IFC properties using IFC Hooks.
	 */
	ACAPI::Result<IFCAPI::Property>		CreatePropertyListValue (const GS::UniString& propertySetName, const GS::UniString& name, const std::vector<IFCAPI::Value>& listValues) const;
	
	/**
	 * @brief Create an IFC property bounded value.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param propertySetName [in] name of the property set which contains the property.
	 * @param name [in] name of the IFC property.
	 * @param lowerBoundValue [in] lower bound value of the IFC property bounded value.
	 * @param upperBoundValue [in] upper bound value of the IFC property bounded value.
	 * @param setPointValue [in] set point value of the IFC property bounded value.
	 * @return If able, an IFC property object, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - Invalid parameter passed.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC add-on is not present.
	 * @remarks At least one of the three values must be set, the rest may be empty
	 * 			Result can be used to map data to Objects' IFC properties using IFC Hooks.
	 */
	ACAPI::Result<IFCAPI::Property>		CreatePropertyBoundedValue (const GS::UniString& propertySetName, const GS::UniString& name, const IFCAPI::Value& lowerBoundValue, const IFCAPI::Value& upperBoundValue, const IFCAPI::Value& setPointValue) const;

	/**
	 * @brief Create an IFC property enumerated value.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param propertySetName [in] name of the property set which contains the property.
	 * @param name [in] name of the IFC property.
	 * @param enumerationReference [in] possible enumeration values of the IFC property enumerated value.
	 * @param enumeratedValues [in] enumerated values of the IFC property enumerated value, shall be a subset of enumerationReference.
	 * @return If able, an IFC property object, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - Invalid parameter passed.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC add-on is not present.
	 * @remarks Result can be used to map data to Objects' IFC properties using IFC Hooks.
	 */
	ACAPI::Result<IFCAPI::Property>		CreatePropertyEnumeratedValue (const GS::UniString& propertySetName, const GS::UniString& name, const std::vector<IFCAPI::Value>& enumerationReference, const std::vector<IFCAPI::Value>& enumeratedValues) const;

	/**
	 * @brief Create an IFC classification from scratch.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param name [in] name of the IFC classification reference.
	 * @param source [in] source of the IFC classification reference.
	 * @param edition [in] edition of the IFC classification reference.
	 * @param editionDate [in] editionDate of the IFC classification reference.
	 * @param description [in] description of the IFC classification reference.
	 * @param location [in] location of the IFC classification reference.
	 * @return If able, an IFC classification object, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC add-on is not present.
	 * @remarks Result can be used to create an IFC classification reference to use with IFC Hooks
	 */
	ACAPI::Result<IFCAPI::Classification>	CreateClassification (const GS::UniString& name,
																  const std::optional<GS::UniString>& source,
																  const std::optional<GS::UniString>& edition,
																  const std::optional<GS::UniString>& editionDate,
																  const std::optional<GS::UniString>& description,
																  const std::optional<GS::UniString>& location) const;

	/**
	 * @brief Create an IFC classification reference from scratch.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param location [in] location of the IFC classification reference.
	 * @param identification [in] identification of the IFC classification reference.
	 * @param name [in] name of the IFC classification reference.
	 * @param referencedSource [in] referencedSource of the IFC classification reference.
	 * @param relAssociatesClassificationName [in] name of the IfcRelAssociatesClassification to export the IFC classification reference with.
	 * 										  Must be unique for each classification reference used on the same object.
	 * @return If able, an IFC classification reference object, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - Invalid relAssociatesClassificationName or valueType passed.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC add-on is not present.
	 * @remarks Result can be used to map data to Objects' IFC classification references using IFC Hooks
	 */
	ACAPI::Result<ClassificationReference>	CreateClassificationReference (const std::optional<GS::UniString>& location,
																		   const std::optional<GS::UniString>& identification,
																		   const std::optional<GS::UniString>& name,
																		   const IFCAPI::Classification& referencedSource,
																		   const GS::UniString& relAssociatesClassificationName) const;
};


/**
 * @brief Get PropertyBuilder to create IFC attribute, property or classification reference.
 * @ingroup IFC
 * @since Archicad 28
 * @return The PropertyBuilder
 * @remarks See IFCHook_Test.cpp for a complete example.
 */
inline PropertyBuilder GetPropertyBuilder ()
{
	return PropertyBuilder::GetPropertyBuilder (ACAPI_GetToken ());
}

}

using v1::PropertyBuilder;
using v1::GetPropertyBuilder;

}

#endif