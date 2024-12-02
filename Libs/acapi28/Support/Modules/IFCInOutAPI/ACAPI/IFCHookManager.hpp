#ifndef IFCAPI_IFCHOOKMANAGER_HPP
#define IFCAPI_IFCHOOKMANAGER_HPP

#pragma once

#include "IFCInOutAPIExport.hpp"

#include "IFCAttribute.hpp"
#include "IFCClassificationReference.hpp"
#include "IFCObjectID.hpp"
#include "IFCProperty.hpp"

#include "ACAPI/Object.hpp"


namespace IFCAPI {

namespace Impl { class HookManager; }

namespace v1 {

class HookAssignments;

/**
 * @brief To register an add-on for IFC hook callbacks, where one can provide their own data to the IFC export.
 * @ingroup IFC
 * @since Archicad 28
 * @remarks See IFCHook_Test.cpp for a complete example.
 */
class IFCINOUTAPI_DLL_EXPORT HookManager : ACAPI::Object {
public:
	/**
	 * @brief Function definition to add generated IFC properties to IFC objects.
	 * @ingroup IFC
	 * @since Archicad 28
	 */
	using PropertyHookFunction = std::function<void (const IFCAPI::ObjectID&, std::vector<IFCAPI::Property>&)>;

	/**
	 * @brief Function definition to fill IFC attributes with generated values in IFC objects.
	 * @ingroup IFC
	 * @since Archicad 28
	 */
	using AttributeHookFunction = std::function<void (const IFCAPI::ObjectID&, std::vector<IFCAPI::Attribute>&)>;

	/**
	 * @brief Function definition to add generated IFC classification references to IFC objects.
	 * @ingroup IFC
	 * @since Archicad 28
	 */
	using ClassificationReferenceHookFunction = std::function<void (const IFCAPI::ObjectID&, std::vector<IFCAPI::ClassificationReference>&)>;

	/**
	 * @brief Function definition to set up a generated IFC assignment structure for IFC export.
	 * @ingroup IFC
	 * @since Archicad 28
	 */
	using AssignmentsHookFunction = std::function<void (IFCAPI::v1::HookAssignments&)>;

private:
	HookManager (std::shared_ptr<Impl::HookManager> impl);

	static HookManager	GetHookManager (const API_Token& token);

public:
	friend HookManager	GetHookManager ();

	~HookManager ();

	/**
	 * @brief Register for the IFC property export hook.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param callback [in] the function which can be called, when querying an object's properties.
	 * @return Success of the operation
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - Function already registered.
	 * @remarks Make sure you call Register and Unregister function in pairs.
	 * 			Once registered, the addon has to stay loaded and have the function available until unregistering.
	 * @par Example
	 * 		@snippet IFCHook_Test.cpp IFCAPI RegisterPropertyHook example
	 */
	ACAPI::Result<void> RegisterPropertyHook (const IFCAPI::v1::HookManager::PropertyHookFunction& callback);

	/**
	 * @brief Unregister from the IFC property export hook.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Success of the operation
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - No registration found this hook.
	 * @remarks Make sure you call Register and Unregister function in pairs.
	 * 			Once registered, the addon has to stay loaded and have the function available until unregistering.
	 * @par Example
	* 	@snippet IFCHook_Test.cpp IFCAPI UnregisterPropertyHook example */
	ACAPI::Result<void> UnregisterPropertyHook ();

	/**
	 * @brief Register for the IFC attribute export hook.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param callback [in] the function which can be called, when querying an object's attributes.
	 * @return Success of the operation
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - Function already registered.
	 * @remarks Make sure you call Register and Unregister function in pairs.
	 * 			Once registered, the addon has to stay loaded and have the function available until unregistering.
	 * @par Example
	 * 		@snippet IFCHook_Test.cpp IFCAPI RegisterAttributeHook example
	 */
	ACAPI::Result<void> RegisterAttributeHook (const IFCAPI::v1::HookManager::AttributeHookFunction& callback);

	/**
	 * @brief Unregister from the IFC attribute export hook.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Success of the operation
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - No registration found this hook.
	 * @remarks Make sure you call Register and Unregister function in pairs.
	 * 			Once registered, the addon has to stay loaded and have the function available until unregistering.
	 * @par Example
	 * 		@snippet IFCHook_Test.cpp IFCAPI UnregisterAttributeHook example
	 */
	ACAPI::Result<void> UnregisterAttributeHook ();

	/**
	 * @brief Register for the IFC classification reference export hook.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param callback [in] the function which can be called, when querying an object's classification references.
	 * @return Success of the operation
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - Function already registered.
	 * @remarks Make sure you call Register and Unregister function in pairs.
	 * 			Once registered, the addon has to stay loaded and have the function available until unregistering.
	 * @par Example
	 * 		@snippet IFCHook_Test.cpp IFCAPI RegisterClassificationReferenceHook example
	 */
	ACAPI::Result<void> RegisterClassificationReferenceHook (const IFCAPI::v1::HookManager::ClassificationReferenceHookFunction& callback);

	/**
	 * @brief Unregister from the IFC classification reference export hook.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Success of the operation
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - No registration found this hook.
	 * @remarks Make sure you call Register and Unregister function in pairs.
	 * 			Once registered, the addon has to stay loaded and have the function available until unregistering.
	 * @par Example
	 * 		@snippet IFCHook_Test.cpp IFCAPI UnregisterClassificationReferenceHook example
	 */
	ACAPI::Result<void> UnregisterClassificationReferenceHook ();

	/**
	 * @brief Register for the IFC type objects' property export hook.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param callback [in] the function which can be called, when querying an element's IFC type object's properties.
	 * @return Success of the operation
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - Function already registered.
	 * @remarks Make sure you call Register and Unregister function in pairs.
	 * 			Once registered, the addon has to stay loaded and have the function available until unregistering.
	 * 			Type objects are generated for each element based on their data, and similar type objects are merged in the end.
	 * @par Example
	 * 		@snippet IFCHook_Test.cpp IFCAPI RegisterTypeObjectPropertyHook example
	 */
	ACAPI::Result<void> RegisterTypeObjectPropertyHook (const IFCAPI::v1::HookManager::PropertyHookFunction& callback);

	/**
	 * @brief Unregister from the IFC type objects' property export hook.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Success of the operation
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - No registration found this hook.
	 * @remarks Make sure you call Register and Unregister function in pairs.
	 * 			Once registered, the addon has to stay loaded and have the function available until unregistering.
	 * @par Example
	 * 		@snippet IFCHook_Test.cpp IFCAPI UnregisterTypeObjectPropertyHook example
	 */
	ACAPI::Result<void> UnregisterTypeObjectPropertyHook ();

	/**
	 * @brief Register for the IFC type objects' attribute export hook.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param callback [in] the function which can be called, when querying an element's IFC type object's attributes.
	 * @return Success of the operation
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - Function already registered.
	 * @remarks Make sure you call Register and Unregister function in pairs.
	 * 			Once registered, the addon has to stay loaded and have the function available until unregistering.
	 * 			Type objects are generated for each element based on their data, and similar type objects are merged in the end.
	 * @par Example
	 * 		@snippet IFCHook_Test.cpp IFCAPI RegisterTypeObjectAttributeHook example
	 */
	ACAPI::Result<void> RegisterTypeObjectAttributeHook (const IFCAPI::v1::HookManager::AttributeHookFunction& callback);

	/**
	 * @brief Unregister from the IFC type objects' attribute export hook.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Success of the operation
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - No registration found this hook.
	 * @remarks Make sure you call Register and Unregister function in pairs.
	 * 			Once registered, the addon has to stay loaded and have the function available until unregistering.
	 * @par Example
	 * 		@snippet IFCHook_Test.cpp IFCAPI UnregisterTypeObjectAttributeHook example
	 */
	ACAPI::Result<void> UnregisterTypeObjectAttributeHook ();

	/**
	 * @brief Register for the IFC type objects' classification reference export hook.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param callback [in] the function which can be called, when querying an element's IFC type object's classification references.
	 * @return Success of the operation
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - Function already registered.
	 * @remarks Make sure you call Register and Unregister function in pairs.
	 * 			Once registered, the addon has to stay loaded and have the function available until unregistering.
	 * 			Type objects are generated for each element based on their data, and similar type objects are merged in the end.
	 * @par Example
	 * 		@snippet IFCHook_Test.cpp IFCAPI RegisterTypeObjectClassificationReferenceHook example
	 */
	ACAPI::Result<void> RegisterTypeObjectClassificationReferenceHook (const IFCAPI::v1::HookManager::ClassificationReferenceHookFunction& callback);

	/**
	 * @brief Unregister from the IFC type objects' classification reference export hook.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Success of the operation
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - No registration found this hook.
	 * @remarks Make sure you call Register and Unregister function in pairs.
	 * 			Once registered, the addon has to stay loaded and have the function available until unregistering.
	 * @par Example
	 * 		@snippet IFCHook_Test.cpp IFCAPI UnregisterTypeObjectClassificationReferenceHook example
	 */
	ACAPI::Result<void> UnregisterTypeObjectClassificationReferenceHook ();

	/**
	 * @brief Register for the IFC assignments export hook.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param callback [in] the function which can be called, when querying the custom assignment structure.
	 * @return Success of the operation
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - Function already registered.
	 * @remarks Make sure you call Register and Unregister function in pairs.
	 * 			Once registered, the addon has to stay loaded and have the function available until unregistering.
	 * @par Example
	 * 		@snippet IFCHook_Test.cpp IFCAPI RegisterAssignmentsHook example
	 */
	ACAPI::Result<void> RegisterAssignmentsHook (const IFCAPI::v1::HookManager::AssignmentsHookFunction& callback);

	/**
	 * @brief Unregister from the IFC assignments export hook.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Success of the operation
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADPARS - No registration found this hook.
	 * @remarks Make sure you call Register and Unregister function in pairs.
	 * 			Once registered, the addon has to stay loaded and have the function available until unregistering.
	 * @par Example
	 * 		@snippet IFCHook_Test.cpp IFCAPI UnregisterAssignmentsHook example
	 */
	ACAPI::Result<void> UnregisterAssignmentsHook ();
};


/**
 * @brief Get HookManager to register an add-on for IFC hook callbacks.
 * @ingroup IFC
 * @since Archicad 28
 * @return The HookManager
 * @remarks See IFCHook_Test.cpp for a complete example.
 */
inline HookManager GetHookManager ()
{
	return HookManager::GetHookManager (ACAPI_GetToken ());
}


}

using v1::HookManager;
using v1::GetHookManager;

}

#endif