#ifndef IFCAPI_IFCVALUE_HPP
#define IFCAPI_IFCVALUE_HPP

#pragma once

#include "IFCInOutAPIExport.hpp"

#include "IFCDefinitions.hpp"

// ACAPI
#include "ACAPI/Object.hpp"


namespace IFCAPI {

namespace Impl { class Value; }

/**
 * @brief Represents an IFC value.
 * @ingroup IFC
 * @since Archicad 28
 */
class IFCINOUTAPI_DLL_EXPORT Value final : public ACAPI::Object {
private:
	Value (std::shared_ptr<Impl::Value> impl);

public:
	friend class PropertySingleValue;
	friend class PropertyListValue;
	friend class PropertyBoundedValue;
	friend class PropertyEnumeratedValue;
	friend class PropertyTableValue;
	friend class PropertyBuilder;

	~Value ();

	/**
	 * @brief Returns the type of the Value (For example: IfcLabel, IfcPositiveLengthMeasure, ...)
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return IFCType of Value.
	 */
	IFCAPI::IFCType GetType () const;

	/**
	 * @brief Returns the value.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Value of Value.
	 * @remarks It could be std::nullopt.
	 */
	IFCAPI::AnyValue GetAnyValue () const;
};

}

#endif