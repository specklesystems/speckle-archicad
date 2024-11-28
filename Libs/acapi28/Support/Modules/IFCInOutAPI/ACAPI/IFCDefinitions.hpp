#ifndef IFCAPI_IFCDEFINITIONS_HPP
#define IFCAPI_IFCDEFINITIONS_HPP

#pragma once

#include <optional>
#include <variant>

#include "UniString.hpp"


namespace IFCAPI {

namespace v1 {

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
 */
enum class IfcLogical {True, Unknown, False};

/**
 * @brief Type definition to represent a value.
 * @ingroup IFC
 * @since Archicad 28
 */
using AnyValue = std::optional<std::variant<bool, IfcLogical, Int64, double, GS::UniString>>;

}

using v1::IfcGloballyUniqueId;
using v1::IFCType;
using v1::IfcLogical;
using v1::AnyValue;

}

#endif