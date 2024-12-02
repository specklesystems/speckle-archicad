#ifndef IFCAPI_IFCPROPERTY_HPP
#define IFCAPI_IFCPROPERTY_HPP

#pragma once

#include "IFCInOutAPIExport.hpp"

#include "IFCValue.hpp"

// ACAPI
#include "ACAPI/Object.hpp"

#include <vector>


namespace IFCAPI {

namespace Impl { class PropertyValue; }

namespace v1 {

/**
 * @brief Represents an IfcPropertySingleValue.
 * @ingroup IFC
 * @since Archicad 28
 */
class IFCINOUTAPI_DLL_EXPORT PropertySingleValue final : public ACAPI::Object {
private:
	PropertySingleValue (std::shared_ptr<Impl::PropertyValue> impl);

public:
	friend class Property;

	~PropertySingleValue ();

	/**
	 * @brief Get the property value.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Value of PropertySingleValue.
	 */
	IFCAPI::Value	GetNominalValue () const;
};

}

using v1::PropertySingleValue;

}


namespace IFCAPI {

namespace Impl { class PropertyValue; }

namespace v1 {

/**
 * @brief Represents an IfcPropertyListValue.
 * @ingroup IFC
 * @since Archicad 28
 */
class IFCINOUTAPI_DLL_EXPORT PropertyListValue final : public ACAPI::Object {
private:
	PropertyListValue (std::shared_ptr<Impl::PropertyValue> impl);

public:
	friend class Property;

	~PropertyListValue ();

	/**
	 * @brief Get list of property value.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return List of Value.
	 */
	std::vector<IFCAPI::Value>	GetListValues () const;
};

}

using v1::PropertyListValue;

}


namespace IFCAPI {

namespace Impl { class PropertyValue; }

namespace v1 {

/**
 * @brief Represents an IfcPropertyBoundedValue.
 * @ingroup IFC
 * @since Archicad 28
 */
class IFCINOUTAPI_DLL_EXPORT PropertyBoundedValue final : public ACAPI::Object {
private:
	PropertyBoundedValue (std::shared_ptr<Impl::PropertyValue> impl);

public:
	friend class Property;

	~PropertyBoundedValue ();

	/**
	 * @brief Get the upper bound of the property bounded value.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Value of the upper bound.
	 */
	IFCAPI::Value GetUpperBoundValue () const;

	/**
	 * @brief Get the lower bound of the property bounded value.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Value of the lower bound.
	 */
	IFCAPI::Value GetLowerBoundValue () const;
	
	/**
	 * @brief Get the set point of the property bounded value.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Value of the set point.
	 */
	IFCAPI::Value GetSetPointValue () const;
};

}

using v1::PropertyBoundedValue;

}


namespace IFCAPI {

namespace Impl { class PropertyValue; }

namespace v1 {

/**
 * @brief Represents an IfcPropertyEnumeratedValue.
 * @ingroup IFC
 * @since Archicad 28
 */
class IFCINOUTAPI_DLL_EXPORT PropertyEnumeratedValue final : public ACAPI::Object {
private:
	PropertyEnumeratedValue (std::shared_ptr<Impl::PropertyValue> impl);

public:
	friend class Property;

	~PropertyEnumeratedValue ();

	/**
	 * @brief Get list of property values of the enumeration.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return List of Values.
	 */
	std::vector<IFCAPI::Value>		GetEnumerationValues () const;

	/**
	 * @brief Get list of property values of the enumeration reference.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return list of Values.
	 */
	std::vector<IFCAPI::Value>		GetEnumerationReference () const;
};

}

using v1::PropertyEnumeratedValue;

}


namespace IFCAPI {

namespace Impl { class PropertyValue; }

namespace v1 {

/**
 * @brief Represents an IfcPropertyTableValue.
 * @ingroup IFC
 * @since Archicad 28
 */
class IFCINOUTAPI_DLL_EXPORT PropertyTableValue final : public ACAPI::Object {
private:
	PropertyTableValue (std::shared_ptr<Impl::PropertyValue> impl);

public:
	friend class Property;

	~PropertyTableValue ();

	/**
	 * @brief Get list of defining property values.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return List of Value.
	 */
	std::vector<IFCAPI::Value>		GetDefiningValues () const;

	/**
	 * @brief Get list of defined property values.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return List of Value.
	 */
	std::vector<IFCAPI::Value>		GetDefinedValues () const;
};

}

using v1::PropertyTableValue;

}


namespace IFCAPI {

namespace Impl { class PropertyValue; }

namespace v1 {

/**
 * @brief Type definition to describe any IfcProperty.
 * @ingroup IFC
 * @since Archicad 28
 */
using PropertyByType = std::variant<PropertySingleValue, PropertyListValue, PropertyBoundedValue, PropertyEnumeratedValue, PropertyTableValue>;

/**
 * @brief Represents an IfcProperty.
 * @ingroup IFC
 * @since Archicad 28
 */
class IFCINOUTAPI_DLL_EXPORT Property final : public ACAPI::Object {
private:
	Property (std::shared_ptr<Impl::PropertyValue> impl);

public:
	friend class PropertyAccessor;
	friend class PropertyBuilder;

	~Property ();

	/**
	 * @brief Name of the container IfcPropertySet.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Name of the container IfcPropertySet.
	 */
	GS::UniString GetPropertySetName () const;

	/**
	 * @brief Name of the IfcProperty.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Name of the IfcProperty.
	 */
	GS::UniString GetName () const;

	/**
	 * @brief Instance of the specific property type.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Instance of the specific property type.
	 */
	PropertyByType GetTyped () const;
};

}

using v1::PropertyByType;
using v1::Property;

}

#endif



