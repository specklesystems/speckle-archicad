#ifndef GS_ACAPI_ELEMDESIGNOPTIONSTATUS_HPP
#define GS_ACAPI_ELEMDESIGNOPTIONSTATUS_HPP

#include "DesignOption.hpp"

#include <variant>


namespace ACAPI::DesignOptions {

/**
 * @brief This expresses that an element had some design option linked to it, but this is missing now.
 *		This situation can occur for example if in teamwork, user A links an element to a design option, and meanwhile user B deletes this design option.
 * @ingroup DesignOptions
 */
struct MissingDesignOption {};

/**
 * @brief This expresses that an element is not linked to any design option, therefore this element is in the Main Model.
 * @ingroup DesignOptions
 */
struct MainModelDesignOption {};

/**
 * @brief Status of the element's design option.
 * @ingroup DesignOptions
 */
using ElemDesignOptionStatus = std::variant<DesignOption, MissingDesignOption, MainModelDesignOption>;

} // namespace ACAPI::DesignOptions

#endif  // GS_ACAPI_ELEMDESIGNOPTIONSTATUS_HPP
