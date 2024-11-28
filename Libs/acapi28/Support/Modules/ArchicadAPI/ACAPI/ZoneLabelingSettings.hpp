#ifndef ACAPI_ZONELABELINGSETTINGS_HPP
#define ACAPI_ZONELABELINGSETTINGS_HPP

#include "ACAPI/ArchicadAPIExport.hpp"
#include "ACAPI/Object.hpp"
#include "UniqueID.hpp"
#include "Result.hpp"
#include "ModifyScope.hpp"


/**
 * @defgroup InputMethod Input Method
 * @brief Functions related to input methods in Archicad.
 *
 * 		  Input Methods
 * 		  ==================================
 *
 * 		  Archicad provides various input methods to allow users to interact with the software using their mouse and keyboard. These input methods enable users to perform operations, select elements, navigate the workspace, and execute commands.
 * 		  Add-ons can also utilize these input methods to enhance user interaction and extend functionality.
 *
 * 		  ## Functions
 *
 * 		  The following functions let you manipulate @ref ACAPI::v1::ZoneLabelingSettings
 *
 * 		  - @ref ACAPI::v1::ZoneLabelingSettings::IsAutomaticLabelingOn
 * 		  - @ref ACAPI::v1::ZoneLabelingSettings::SetAutomaticLabeling
 * 		  - @ref ACAPI::v1::ZoneLabelingSettings::GetSelectedFavoriteName
 * 		  - @ref ACAPI::v1::ZoneLabelingSettings::SetSelectedFavorite
 */


/**
 * @brief Returns the token associated with the AddOn.
 * @ingroup AddOnIdentification
 * @return The token associated with the add-on.
 * @remarks It is not guaranteed that this function will always return the same value. Always obtain your
 * 			token by calling this function on demand.
 */
API_Token ACAPI_GetToken ();
namespace ACAPI {
namespace Impl {
	class ObjectImpl;
}

namespace v1 {

/**
 * @brief A class that contains functions related to zone labeling by favorite.
 * @class ZoneLabelingSettings
 * @since Archicad 28
 * @ingroup InputMethod
 */
class ARCHICADAPI_EXPORT ZoneLabelingSettings : public Object {
	
	friend ZoneLabelingSettings CreateZoneLabelingSettings ();
	explicit ZoneLabelingSettings (const API_Token& token);

public:
	class Modifier;

	/**
	 * @brief A function to return if a label should automatically be placed onto new zone or not.
	 * @return Returns if a label should automatically be placed onto new zones or not.
	 */
	bool IsAutomaticLabelingOn () const;

	/**
	 * @brief A function to return the selected favorite from infobox for zone.
	 * @return Returns an error if the process fails for some reason, otherwise the selected favorite from infobox.
	 * 		   - APIERR_GENERAL - Label favorite could not find.
	 * @par Example
	 * 		@snippet Element_Basics.cpp ZoneAutoLabel_GetFavorite-Example
	 */
	Result<GS::UniString> GetSelectedFavoriteName () const;

	/**
	 * @brief Executes the given modifier scope in a NotUndoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template<class ModifierFunc>
	Result<void> Modify (ModifierFunc&& modifierFunc);
};

class ARCHICADAPI_EXPORT ZoneLabelingSettings::Modifier : public ACAPI::ModifierBase {
	ZoneLabelingSettings& parent;
	explicit Modifier (ZoneLabelingSettings& parent);
	virtual ~Modifier ();

public:
	friend ZoneLabelingSettings;

	/**
	 * @brief A function to set whether a label should automatically be placed onto new zones or not.
	 * @param labeling [in] The logical value to be set, if label should be placed or not.
	 * @par Example
	 * 		@snippet Element_Basics.cpp ZoneAutoLabel-Example
	 */
	void SetAutomaticLabeling (bool labeling);

	/**
	 * @brief A function to set the label favorite that should be used for the automatic labeling of zones.
	 * @param favoriteName [in] The name of the label favorite.
	 * @return Returns an error if the favoriteName is incorrect, otherwise nothing.
	 * 		   - APIERR_GENERAL - There is no favorite in the list.
	 * 		   - APIERR_BADNAME - Favorite for the favorite name does not exist.
	 * 		   - APIERR_BADELEMENTTYPE - Favorite is not a label favorite.
	 * @par Example
	 * 		@snippet Element_Basics.cpp ZoneAutoLabel_SetFavorite-Example
	 */
	Result<void> SetSelectedFavorite (const GS::UniString& favoriteName);
};

template<class ModifierFunc>
Result<void> ZoneLabelingSettings::Modify (ModifierFunc&& modifierFunc)
{
	Modifier modifier (*this);
	return CallDefaultModifier (modifierFunc, modifier);
}


/**
 * @brief A function to create zone labeling settings instance, that lets you query and manipulate zone label favorite related data.
 * @ingroup InputMethod
 * @return Returns the zone labeling settings instance.
 */
inline ZoneLabelingSettings CreateZoneLabelingSettings ()
{
	return ZoneLabelingSettings (ACAPI_GetToken ());
}


} // namespace v1

using namespace v1;

} // namespace ACAPI

#endif // ACAPI_ZONELABELINGSETTINGS_HPP