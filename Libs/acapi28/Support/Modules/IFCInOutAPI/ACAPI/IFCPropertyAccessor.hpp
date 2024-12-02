#ifndef IFCAPI_PROPERTYACCESSOR_HPP
#define IFCAPI_PROPERTYACCESSOR_HPP

#pragma once

#include "IFCInOutAPIExport.hpp"

#include "IFCAttribute.hpp"
#include "IFCClassificationReference.hpp"
#include "IFCObjectID.hpp"
#include "IFCProperty.hpp"

// ACAPI
#include "ACAPI/Object.hpp"

#include <vector>


namespace IFCAPI {

namespace Impl { class PropertyAccessor; }

namespace v1 {

/**
 * @brief To access IFC attributes, properties and classification references.
 * @ingroup IFC
 * @since Archicad 28
 */
class IFCINOUTAPI_DLL_EXPORT PropertyAccessor final : public ACAPI::Object {
private:
	PropertyAccessor (std::shared_ptr<Impl::PropertyAccessor> impl);

public:
	/**
	 * @brief Get PropertyAccessor to access IFC attributes, properties and classification references.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param objectID [in] identifies the IFC entity.
	 */
	PropertyAccessor (const IFCAPI::ObjectID& objectID);

	~PropertyAccessor ();

	/**
	 * @brief Get the entity's IFC attributes.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return If able, a list of Attribute objects, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADID - Invalid value passed in the objectID parameter.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC add-on is not present.
	 * @par Example
	 * 		@snippet IFCAPI_Test.cpp IFCAPI GetAttributes example
	 */
	ACAPI::Result<std::vector<Attribute>>	GetAttributes () const;

	/**
	 * @brief Get the entity's preview IFC properties.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return If able, a list of Property object, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADID - Invalid value passed in the objectID parameter.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC add-on is not present.
	 * @remarks Returns exportable IFC properties, even mapped and calculated ones according to the preview Export Translator.
	 * 			The same can be seen in IFC Project Manager.
	 * @par Example
	 * 		@snippet IFCAPI_Test.cpp IFCAPI GetPreviewProperties example
	 */
	ACAPI::Result<std::vector<Property>> GetPreviewProperties () const;
	
	/**
	 * @brief Get the entity's local IFC properties.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return If able, a list of Property object, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADID - Invalid value passed in the objectID parameter.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC add-on is not present.
	 * @remarks Returns only IFC properties stored within the object, not calculated ones.
	 * 			Such properties are currently created for objects, when they're being imported from IFC, or you're editing their IFC properties manually.
	 * @par Example
	 * 		@snippet IFCAPI_Test.cpp IFCAPI GetLocalProperties example
	 */
	ACAPI::Result<std::vector<Property>> GetLocalProperties () const;

	/**
	 * @brief Get the entity's preview IFC classification references.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return If able, a list of ClassificationReference objects, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADID - Invalid value passed in the objectID parameter.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC add-on is not present.
	 * @remarks Returns exportable IFC classification references, even mapped and calculated ones according to the preview Export Translator.
	 * 			The same can be seen in IFC Project Manager.
	 * @par Example
	 * 		@snippet IFCAPI_Test.cpp IFCAPI GetPreviewClassificationReferences example
	 */
	ACAPI::Result<std::vector<ClassificationReference>>		GetPreviewClassificationReferences () const;
	
	/**
	 * @brief Get the entity's IFC classification references.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return If able, a list of ClassificationReference object, otherwise Error.
	 * 		   - NoError - The function has completed with success.
	 * 		   - APIERR_BADID - Invalid value passed in the objectID parameter.
	 * 		   - APIERR_MODULNOTINSTALLED - IFC add-on is not present.
	 * @remarks Returns only IFC classification references stored within the object, not calculated ones.
	 * 			Such classification references are currently created for objects, when they're being imported from IFC, or you're editing their IFC classification references manually.
	 * @par Example
	 * 		@snippet IFCAPI_Test.cpp IFCAPI GetLocalClassificationReferences example
	 */
	ACAPI::Result<std::vector<ClassificationReference>>		GetLocalClassificationReferences () const;
};

}

using v1::PropertyAccessor;

}

#endif