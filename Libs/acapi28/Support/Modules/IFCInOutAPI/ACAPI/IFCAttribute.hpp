#ifndef IFCAPI_IFCATTRIBUTE_HPP
#define IFCAPI_IFCATTRIBUTE_HPP

#pragma once

#include "IFCInOutAPIExport.hpp"

#include "IFCDefinitions.hpp"

// ACAPI
#include "ACAPI/Object.hpp"


namespace IFCAPI {

namespace Impl { class Attribute; }

namespace v1 {

/**
 * @brief Represents an IFC Attribute.
 * @ingroup IFC
 * @since Archicad 28
 */
class IFCINOUTAPI_DLL_EXPORT Attribute final : public ACAPI::Object {
private:
	Attribute (std::shared_ptr<Impl::Attribute> impl);

public:
	friend class PropertyAccessor;
	friend class PropertyBuilder;

	~Attribute ();

	/**
	 * @brief Name of the Attribute.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Name of the Attribute.
	 */
	GS::UniString GetName () const;

	/**
	 * @brief Value of the Attribute.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Value of the Attribute.
	 * @remarks Optional attributes can have no value.
	 */
	std::optional<GS::UniString> GetValue () const;

	/**
	 * @brief Value type of the Attribute.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Value type of the Attribute.
	 */
	IFCAPI::IFCType GetValueType () const;
};

}

using v1::Attribute;

}

#endif



