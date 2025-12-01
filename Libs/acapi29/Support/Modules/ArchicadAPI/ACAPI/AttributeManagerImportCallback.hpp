#ifndef ACAPI_ATTRIBUTE_MANAGER_IMPORT_CALLBACK_HPP
#define ACAPI_ATTRIBUTE_MANAGER_IMPORT_CALLBACK_HPP

#include "AddonServiceInterface.hpp"
#include "Location.hpp"
#include "APIdefs_Attributes.h"
#include "Pair.hpp"


namespace ACAPI {


/**
 * @brief AttributeManagerImportCallback is responsible for registering and handling file types to the AttributeManager through API. You can make your own implementation to add the possibility to import attributes from your own file format.
 * @ingroup Attribute
 * @since Archicad 29
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AttributeManagerImportCallback-Example-Snippet
 */
class ARCHICADAPI_EXPORT AttributeManagerImportCallback : public ACAPI::AddonServiceInterface {
public:

	/**
	 * @brief Constructs a new attribute manager callback.
	 * @param fileExtension The extension of the registered file type.
	 */
	AttributeManagerImportCallback (const GS::UniString& fileExtension);

	/**
	 * @brief Provide the new file type, that should be registered on the AttributeManager dialog.
	 * @return The new file type.
	 */
	virtual API_AttributeManagerFormat GetFileTypeFormat () const = 0;

	/**
	 * @brief The import logic from the new file type.
	 * @param sourceFile Source File Location.
	 * @param result The result array where the new attributes are inserted by the import process.
	 * @return NoError, Cancel, or other Error code.
	 */
	virtual GSErrCode ImportAttributeProcess (const IO::Location& sourceFile, GS::Array<GS::Pair<API_Attribute, API_AttributeDefExt*>>& result) const = 0;

private:
	/**
	 * @brief The callback function for the interface registration phase.
	 * @return NoError if everything went well, otherwise the error code.
	 */
	virtual GSErrCode RegisterInterface () override;
};

} // ACAPI

#endif