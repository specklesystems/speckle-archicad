#ifndef ACAPI_MODEL_CHECK_MANAGER_HPP
#define ACAPI_MODEL_CHECK_MANAGER_HPP

#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"


namespace ACAPI {

/**
 * @brief ModelCheckManager is a class to access the Model Quality Check services
 * @ingroup ModelCheck
 * @since Archicad 29
 */
class ARCHICADAPI_EXPORT ModelCheckManager : public Object {
private:
	friend ModelCheckManager GetModelCheckManager ();
	explicit ModelCheckManager (const API_Token&);

public:

	/**
	 * @brief Registers a new Model Check Method Group.
	 * @param modelCheckTypeId The parent Model Check Type id where the new group will be registered.
	 * @param groupId Unique identifier of the group. Later it can be used to register Model Check Method in the group.
	 * @param groupName Localized name of the new Model Check Group. It will be presented on the user interface.
	 * @note This function should be called only from the RegisterInterface () function of the AddOn.
	 * @return Error with error code and message if there was any, otherwise nothing.
	 */
	ACAPI::Result<void> RegisterGroup (const API_Guid& modelCheckTypeId, const API_Guid& groupId, const GS::UniString& groupName) const;
};

/**
 * @brief A function to create ModelCheckManager instance.
 * @ingroup ModelCheck
 * @since Archicad 29
 * @return Returns the ModelCheckManager instance.
 */
inline ModelCheckManager GetModelCheckManager ()
{
	return ModelCheckManager (ACAPI_GetToken ());
}

} // ACAPI

#endif // ACAPI_MODEL_CHECK_MANAGER_HPP
