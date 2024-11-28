#ifndef IFCAPI_IFCCLASSIFICATIONREFERENCE_HPP
#define IFCAPI_IFCCLASSIFICATIONREFERENCE_HPP

#pragma once

#include "IFCInOutAPIExport.hpp"

// ACAPI
#include "ACAPI/Object.hpp"

#include <optional>


namespace IFCAPI {

namespace Impl { class Classification; }

namespace v1 {

/**
 * @brief Represents an IfcClassification.
 * @ingroup IFC
 * @since Archicad 28
 */
class IFCINOUTAPI_DLL_EXPORT Classification final : public ACAPI::Object {
private:
	Classification (std::shared_ptr<Impl::Classification> impl);

public:
	friend class PropertyBuilder;
	friend class ClassificationReference;

	~Classification ();

	/**
	 * @brief Name of the IfcClassification.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Name of the IfcClassification.
	 */
	GS::UniString	GetName () const;

	/**
	 * @brief Source of the IfcClassification.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Source of the IfcClassification or std::nullopt if it's not filled.
	 */
	std::optional<GS::UniString>	GetSource () const;

	/**
	 * @brief Edition of the IfcClassification.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Edition of the IfcClassification or std::nullopt if it's not filled.
	 */
	std::optional<GS::UniString>	GetEdition () const;

	/**
	 * @brief EditionDate of the IfcClassification.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return EditionDate of the IfcClassification or std::nullopt if it's not filled.
	 */
	std::optional<GS::UniString>	GetEditionDate () const;

	/**
	 * @brief Description of the IfcClassification.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Description of the IfcClassification or std::nullopt if it's not filled.
	 */
	std::optional<GS::UniString>	GetDescription () const;

	/**
	 * @brief Location of the IfcClassification.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Location of the IfcClassification or std::nullopt if it's not filled.
	 */
	std::optional<GS::UniString>	GetLocation () const;
};

}

using v1::Classification;

}


namespace IFCAPI {

namespace Impl { class ClassificationReference; }

namespace v1 {

/**
 * @brief Represents an IfcClassificationReference.
 * @ingroup IFC
 * @since Archicad 28
 */
class IFCINOUTAPI_DLL_EXPORT ClassificationReference final : public ACAPI::Object {
private:
	ClassificationReference (std::shared_ptr<Impl::ClassificationReference> impl);

public:
	friend class PropertyAccessor;
	friend class PropertyBuilder;

	~ClassificationReference ();

	/**
	 * @brief Location of the IfcClassificationReference.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Location of the IfcClassificationReference or std::nullopt if it's not filled.
	 */
	std::optional<GS::UniString>	GetLocation () const;

	/**
	 * @brief Name of the IfcClassificationReference.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Name of the IfcClassificationReference or std::nullopt if it's not filled.
	 */
	std::optional<GS::UniString>	GetName () const;

	/**
	 * @brief Identification of the IfcClassificationReference.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Identification of the IfcClassificationReference or std::nullopt if it's not filled.
	 */
	std::optional<GS::UniString>	GetIdentification () const;

	/**
	 * @brief ReferencedSource of the IfcClassificationReference.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return ReferencedSource of the IfcClassificationReference.
	 */
	IFCAPI::Classification	GetReferencedSource () const;

	/**
	 * @brief Name of the IfcRelAssociatesClassification.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Name of the IfcRelAssociatesClassification.
	 */
	GS::UniString	GetIfcRelAssociatesClassificationName () const;
};

}

using v1::ClassificationReference;

}

#endif
