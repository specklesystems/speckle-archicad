#ifndef GS_COMMONUI_UDLISTBOX_COLORS_HPP
#define GS_COMMONUI_UDLISTBOX_COLORS_HPP


#include "UDDefinitions.hpp"
#include "HashTable.hpp"

namespace UD {

/**
 * @enum ListBoxColorId
 * @brief Identifiers for various colors used in list boxes and tree views.
 */
enum class ListBoxColorId: UInt16
{
	DefaultText,			///< Defalut text color, same as DG::ColorId::ControlTextColor
	DisabledText,			///< Disabled text color, same as DG::ColorId::DisabledControlTextColor
	DefaultBackground,		///< Defalut background color, same as DG::ColorId::ControlBackgroundColor

	RedText,				///< Red text color.
	GreenText,				///< Green text color.
	BlueText,				///< Blue text color.

	PinkText,				///< Pink text color.
	OrangeText,				///< Orange text color.
	LightGrayText,			///< Light Gray text color.
	GrayText,				///< Gray text color.

	RedBackground,			///< Background red color.
	GreenBackground,		///< Background green color.
	BlueBackground,			///< Background blue color.

	LightPinkBackground,	///< Background light pink color.

	DefaultSectionHeader,	///< Background color used for section headers.
	GreenSectionHeader		///< Background color used for green section headers
};

/**
 * @brief Gets the color associated with a given ColorId.
 * @ingroup DG
 * @param colorId The identifier of the color.
 * @return The color associated with the given ColorId and the current application appearance mode (light-dark mode).
 */
UD_DLL_EXPORT Gfx::Color GetListBoxColor (const UD::ListBoxColorId colorId);

}

#endif
