#ifndef IFCAPI_IFCASSIGNMENTS_HPP
#define IFCAPI_IFCASSIGNMENTS_HPP

#pragma once

#include "IFCInOutAPIExport.hpp"

#include "IFCObjectID.hpp"

// ACAPI
#include "ACAPI/Object.hpp"

#include <unordered_set>
#include <unordered_map>


namespace IFCAPI {

namespace Impl { class Assignments; }

namespace v1 {

/**
 * @brief Represents the persistent Assignment Tree in IFC.
 * @ingroup IFC
 * @since Archicad 28
 * @remarks Provides access the root IFC groups and a table of their nested child and parent hierarchy.
 */
class IFCINOUTAPI_DLL_EXPORT Assignments final : public ACAPI::Object {
private:
	Assignments (std::shared_ptr<Impl::Assignments> impl);

public:
	friend class ObjectAccessor;

	~Assignments ();

	/**
	 * @brief Returns all root IFC groups.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Root IFC groups.
	 * @par Example
	 * 		@snippet IFCAPI_Test.cpp IFCAPI Assignments GetRootGroups example
	 */
	std::unordered_set<IFCAPI::ObjectID> GetRootGroups () const;

	/**
	 * @brief Returns a table representing the nested child hierarchy.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return A table representing the nested child hierarchy.
	 * @par Example
	 * 		@snippet IFCAPI_Test.cpp IFCAPI Assignments GetChildObjectTable example
	 */
	std::unordered_map<IFCAPI::ObjectID, std::unordered_set<IFCAPI::ObjectID>> GetChildObjectTable () const;

	/**
	 * @brief Returns a table representing the parent hierarchy.
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return A table representing the parent hierarchy.
	 * @remarks Some Objects may be connected to multiple parents.
	 * @par Example
	 * 		@snippet IFCAPI_Test.cpp IFCAPI Assignments GetParentObjectTable example
	 */
	std::unordered_map<IFCAPI::ObjectID, std::unordered_set<IFCAPI::ObjectID>> GetParentObjectTable () const;
};

}

using v1::Assignments;

}

#endif