#ifndef IFCAPI_IFCDEFINITIONS_HPP
#define IFCAPI_IFCDEFINITIONS_HPP

#pragma once

#include <optional>
#include <variant>

#include "UniString.hpp"


namespace IFCAPI {

/**
 * @brief Type definition for IfcGloballyUniqueId.
 * @ingroup IFC
 * @since Archicad 28
 * @details Can be used to identify elements between Archicad and IFC.
 */
using IfcGloballyUniqueId = GS::UniString;


/**
 * @brief Type definition for IFC type.
 * @ingroup IFC
 * @since Archicad 28
 */
using IFCType = GS::UniString;


/**
 * @brief Type definition for IfcLogical value.
 * @ingroup IFC
 * @since Archicad 28
 *
 * @remarks Represents the logical values used in the Industry Foundation Classes (IFC) data model.
 *          This enum is used to denote the logical state of a value in IFC,
 *          which can be true, false, or unknown.
 */
enum class IfcLogical {

    /** Represents a true logical value. */
    True,

    /** Represents an unknown logical value. */
    Unknown,

    /** Represents a false logical value. */
    False
};

/**
 * @brief Type definition to represent a value.
 * @ingroup IFC
 * @since Archicad 28
 */
using AnyValue = std::optional<std::variant<bool, IfcLogical, Int64, double, GS::UniString>>;

}

#endif