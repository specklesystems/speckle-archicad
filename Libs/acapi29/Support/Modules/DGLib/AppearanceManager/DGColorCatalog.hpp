#ifndef DGCOLORCATALOG_HPP
#define DGCOLORCATALOG_HPP

#pragma once

#include "Color.hpp"

namespace DG {

/**
 * @enum ColorId
 * @brief Identifiers for various colors used in the application.
 */
enum class ColorId: UInt16
{
    LinkColor,                      ///< Color for links.
    VisitedLinkColor,               ///< Color for visited links.

    StandardTextColor,              ///< Color for standard text.
    StandardTextBackgroundColor,    ///< Background color for standard text.
    HighlightBackgroundColor,       ///< Background color for highlighted standard text.
	ScrollbarThumbColor,			///< Color for scrollbar thumb.
	ScrollbarTrackColor,			///< Color for scrollbar track.

    WindowBackgroundColor,          ///< Background color of windows.
    ControlBackgroundColor,         ///< Background color of controls.
    ControlTextColor,               ///< Text color of controls.
    DisabledControlTextColor,       ///< Text color for disabled control text.

    SelectedContentBackgroundColor, ///< Background color for selected controls.
    SelectedTextColor               ///< Text color for selected control text.
};

/**
 * @class ColorCatalog
 * @ingroup DG
 * @brief Provides access to colors for dark mode support.
 */
class DG_DLL_EXPORT ColorCatalog
{
public:
    // Deleted copy constructor and assignment operator
    ColorCatalog (const ColorCatalog& source) = delete;
    ColorCatalog& operator= (const ColorCatalog& source) = delete;

    /**
     * @brief Destructor for ColorCatalog.
     */
    ~ColorCatalog () = default;

    /**
     * @brief Gets the color (primarily system colors) associated with a given ColorId.
     * @param colorId The identifier of the color.
     * @return The color associated with the given ColorId.
     */
    static Gfx::Color GetColor (ColorId colorId);

private:
    /**
     * @brief Constructor for ColorCatalog.
     */
    ColorCatalog () = default;

    /**
     * @brief Gets the singleton instance of the ColorCatalog.
     * @return The singleton instance.
     */
    static ColorCatalog& GetInstance ();
};

} // namespace DG

#endif