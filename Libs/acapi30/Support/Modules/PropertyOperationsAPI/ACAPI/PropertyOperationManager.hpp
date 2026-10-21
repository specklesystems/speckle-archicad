#ifndef GS_ACAPI_PROPERTYOPERATIONMANAGER_HPP
#define GS_ACAPI_PROPERTYOPERATIONMANAGER_HPP

#include "PropertyOperationsAPIExport.hpp"
#include "PropertyOperationAPIEnums.hpp"
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "APIdefs_Registration.h"
#include "API_Guid.hpp"
#include "DGUtility.hpp"
#include "UniString.hpp"
#include "Definitions.hpp"
#include <functional>
#include <variant>

/**********************************************************************************************************************/

namespace DG { class Icon; }

/**********************************************************************************************************************/

namespace ACAPI {
namespace v1 {

/**
 * @brief Class that represents a property.
 * @ingroup APIInfrastructure
 * @since Archicad 29
 */
class PROPERTYOPERATIONSAPI_EXPORT APIProperty : public Object {

	friend class APIPropertyGroup;

	APIProperty (
		const API_Token& token,
		const GS::Guid& propertyGuid,
		GS::UniString propertyName,
		PropertyOperations::CriteriaEnvironmentType criteriaEnvironmentType,
		PropertyOperations::GroupAvailability groupAvailability,
		PropertyOperations::PropertyToUseInContext propertyToUseInContext,
		PropertyOperations::PropertyValueType valueType,
		bool isSummable,
		const GS::Array<API_ElemType>& availableForElemsOfTypes,
		const DG::Icon& icon,
		std::function<bool (const API_Guid&)> isEvaluableFor,
		std::function<std::variant<Int32, double, GS::UniString, bool> (const API_Guid&)> getValueFrom
	);

};


/**
 * @brief Class that represents a group of properties.
 * @ingroup APIInfrastructure
 * @since Archicad 29
 */
class PROPERTYOPERATIONSAPI_EXPORT APIPropertyGroup : public Object {

	friend class PropertyOperationManager;

private:

	APIPropertyGroup (const API_Token& token, const GS::Guid& groupGuid, GS::UniString groupName, const DG::Icon& icon);

	[[nodiscard]] Result<APIProperty> CreateAndAddAPIProperty (
		const GS::Guid& propertyGuid,
		GS::UniString propertyName,
		PropertyOperations::CriteriaEnvironmentType criteriaEnvironmentType,
		PropertyOperations::GroupAvailability groupAvailability,
		PropertyOperations::PropertyToUseInContext propertyToUseInContext,
		PropertyOperations::PropertyValueType valueType,
		bool isSummable,
		const GS::Array<API_ElemType>& availableForElemsOfTypes,
		const DG::Icon& icon,
		std::function<bool (const API_Guid&)> isEvaluableFor,
		std::function<std::variant<Int32, double, GS::UniString, bool> (const API_Guid&)> getValueFrom
	);

};


/**
 * @brief Class that administrates the properties of the add-on. Created using CreatePropertyOperationManager.
 * @ingroup APIInfrastructure
 * @since Archicad 29
 */
class PROPERTYOPERATIONSAPI_EXPORT [[nodiscard]] PropertyOperationManager : public Object {
	friend Result<PropertyOperationManager> PROPERTYOPERATIONSAPI_EXPORT CreatePropertyOperationManager (const API_Token&);

private:

	UInt32 m_addOnId { 0 };

private:

	PropertyOperationManager (const API_Token& token, UInt32 addOnId);
	
public:

	/**
	 * @brief Registers all properties of the add-on.
	 * @ingroup APIInfrastructure
	 * @since Archicad 29
	 * @return Error when registration failed (e.g. because already registered earlier).
	 */
	Result<void> RegisterAllProperties ();

	/**
	 * @brief Unregisters all properties of the add-on.
	 * @ingroup APIInfrastructure 
	 * @since Archicad 29
	 * @return Error when unregistration failed (e.g. because already unregistered earlier).
	 */
	Result<void> UnregisterAllProperties ();

	/**
	 * @brief Creates a property group (but does not yet add it).
 	 * @ingroup APIInfrastructure
 	 * @since Archicad 29
	 * @param groupGuid is the guid of the group (must be unique).
	 * @param groupName is the name of the group (must be not empty).
	 * @param icon is the icon of the group (must be not empty).
	 * @return Created property group is all input was valid. Error otherwise.
 	 */
	[[nodiscard]] Result<APIPropertyGroup> CreateAPIPropertyGroup (const GS::Guid& groupGuid, GS::UniString groupName, const DG::Icon& icon);
	
	/**
	 * @brief Creates a new property.
	 * @ingroup APIInfrastructure
	 * @since Archicad 29
	 * @param propertyGroup is the group where to property is added to.
	 * @param propertyGuid is the guid of the property (must be unique).
	 * @param propertyName is the name of the property (must be not empty).
	 * @param criteriaEnvironmentType is the criteria environment type of the property.
	 * @param groupAvailability is the group availability of the property.
	 * @param propertyToUseInContext is the property to use in context of the property.
	 * @param valueType is the value type of the property.
	 * @param isSummable is the property summable.
	 * @param availableForElemsOfTypes is a list of all elements that this property should be available for (must be not empty).
	 * @param icon is the icon of the property (must be not empty).
	 * @param isEvaluableFor function to check if property is evaluable for given elem.
	 * @param getValueFrom function to get the value of property from elem. Must return Int32 for Integer properties, double for Numeric properties, GS::UniString for String properties and bool for Boolean properties.
	 * @return The created property if all input was valid. Error otherwise.
	 */
	[[nodiscard]] Result<APIProperty> CreateAndAddAPIProperty (
		APIPropertyGroup& propertyGroup,
		const GS::Guid& propertyGuid,
		GS::UniString propertyName,
		PropertyOperations::CriteriaEnvironmentType criteriaEnvironmentType,
		PropertyOperations::GroupAvailability groupAvailability,
		PropertyOperations::PropertyToUseInContext propertyToUseInContext,
		PropertyOperations::PropertyValueType valueType,
		bool isSummable,
		const GS::Array<API_ElemType>& availableForElemsOfTypes,
		const DG::Icon& icon,
		std::function<bool (const API_Guid&)> isEvaluableFor,
		std::function<std::variant<Int32, double, GS::UniString, bool> (const API_Guid&)> getValueFrom
	);

	/**
	 * @brief Adds a property group.
 	 * @ingroup APIInfrastructure
 	 * @since Archicad 29
	 * @param propertyGroup is the property group to add.
	 * @return Error when adding failes (e.g. due to a duplicate guid).
 	 */
	Result<void> AddPropertyGroup (APIPropertyGroup propertyGroup);

};

/**
 * @brief Create a PropertyOperationManager object that administrates the properties of the add-on.
 * @ingroup APIInfrastructure
 * @since Archicad 29
 * @param token is the token of the add-on.
 * @return The PropertyOperationManager object. Must stay alive as long as the add-on is alive. Error if token does not belong to add-on.
 */
[[nodiscard]] Result<PropertyOperationManager> PROPERTYOPERATIONSAPI_EXPORT CreatePropertyOperationManager (const API_Token& token);


} // namespace v1

using namespace v1;

} // namespace ACAPI

#endif /* GS_ACAPI_PROPERTYOPERATIONMANAGER_HPP */
