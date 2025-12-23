#ifndef ACAPI_MODEL_CHECK_METHOD_CALLBACK_HPP
#define ACAPI_MODEL_CHECK_METHOD_CALLBACK_HPP

#include "AddonServiceInterface.hpp"

#include <optional>

#include "RSIcon.hpp"


namespace ACAPI {

/**
 * @brief The type of the model check criteria.
 * @ingroup ModelCheck
 */
enum class ModelCheckSettingType {
	OnlySelection,
	Angle,
	Length,
	Area,
	Real,
	Interval
};


/**
 * @brief The type of the check result returned by the AddOn.
 * @ingroup ModelCheck
 * @since Archicad 29
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AttributeManagerImportCallback-Example-Snippet
 */
class ARCHICADAPI_EXPORT ModelCheckResult {
	API_Guid element1;
	API_Guid element2;

public:
	/**
	 * @brief Creates a ModelCheckResult from a single element.
	 */
	ModelCheckResult (const API_Guid&);

	/**
	 * @brief Creates a ModelCheckResult from two elements.
	 */
	ModelCheckResult (const API_Guid&, const API_Guid&);

	/**
	 * @return Returns the first element from the ModelCheckResult.
	 */
	const API_Guid& GetFirstElement () const;

	/**
	 * @return Returns the second element from the ModelCheckResult.
	 */
	const API_Guid& GetSecondElement () const;
};


/**
 * @brief ModelCheckMethodCallback is responsible for registering and handling Model Quality Check methods through API. You can make your own implementation to extend the list of Model Check Methods with your own check logic.
 * @ingroup ModelCheck
 * @since Archicad 29
 */
class ARCHICADAPI_EXPORT ModelCheckMethodCallback : public ACAPI::AddonServiceInterface {
	const API_Guid modelCheckTypeId;

public:

	/**
	 * @brief Constructs a new Model Check Method callback.
	 * @param modelCheckTypeId The identifier of the parent Model Check Type where the new method will be registered.
	 * @param nonLocalizedModelCheckMethodName Non-localized name of the new Model Check Method. It should be unique, it's used for identification.
	 */
	ModelCheckMethodCallback (const API_Guid& modelCheckTypeId, const GS::UniString& nonLocalizedModelCheckMethodName);

	/**
	 * @brief Callback function. The AddOn should return the localized name of the new Model Check Method.
	 * @return Returns the localized name that will be presented on the Model Check UI.
	 */
	virtual GS::UniString GetLocalizedCheckMethodName () const = 0;

	/**
	 * @brief Callback function. The AddOn should return the localized name of the new Model Check Method.
	 * @return Returns the localized name that will be presented on the Model Check Result palette.
	 */
	virtual GS::UniString GetLocalizedCheckMethodResultName () const = 0;

	/**
	 * @brief Callback function. The AddOn can return a localized text that will pop up when the user hovers on the info icon.
	 * @return Returns the localized info text or std::nullopt.
	 */
	virtual std::optional<GS::UniString> GetLocalizedCheckMethodInfoText () const = 0;

	/**
	 * @brief Callback function. The AddOn can return an icon that will showed on the Model Check dialog.
	 * @return The icon or std::nullopt.
	 */
	virtual std::optional<RS::Icon> GetIcon () const = 0;

	/**
	 * @brief Callback function. The AddOn can return a Model Check GroupId where the Model Check Method will be enrolled.
	 * @details New group can be registered with the ACAPI::ModelCheckManager::RegisterGroup () function.
	 * @return Returns the groupId or std::nullopt.
	 */
	virtual std::optional<API_Guid> GetGroupId () const = 0;

	/**
	 * @brief Callback function. The AddOn should return the default state of the new Model Check Method.
	 * @return Returns the default state of the methods checkbox.
	 */
	virtual bool GetDefaultSelectionStatus () const = 0;

	/**
	 * @brief Callback function. Controls the type of the editbox displayed on the Model Check dialog.
	 * @return Returns the value of ModelCheckSettingType enum.
	 */
	virtual ModelCheckSettingType GetCheckSettingType () const = 0;
	
	/**
	 * @brief Callback function. Provide the default value for the editbox displayed on the Model Check Dialog.
	 * @return Returns a vector of double values. The number of elements in the vector depends on the selected ModelCheckSettingType.
	 */
	virtual std::vector<double> GetDefaultValues () const;

	/**
	 * @brief Callback function. The check logic should be placed here. It is called when the new Model Check Method is executed.
	 * @param processControl Process Control
	 * @param values Values representing the settings
	 * @return Returns a vector of ModelCheckResult representing the elements that are filtered out by the check.
	 */
	virtual std::vector<ModelCheckResult> CheckProcess (GS::ProcessControl& processControl, const std::vector<double>& values) = 0;

protected:
	/**
	 * @brief The callback function for the interface registration phase.
	 * @return Returns NoError if everything went well, otherwise the error code.
	 */
	virtual GSErrCode RegisterInterface () override;
};

} // ACAPI

#endif //ACAPI_MODEL_CHECK_METHOD_CALLBACK_HPP