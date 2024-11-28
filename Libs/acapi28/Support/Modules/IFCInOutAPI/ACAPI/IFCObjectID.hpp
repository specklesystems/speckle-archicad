#ifndef IFCAPI_IFCOBJECTID_HPP
#define IFCAPI_IFCOBJECTID_HPP

#pragma once

#include "IFCInOutAPIExport.hpp"

// ACAPI
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"


namespace IFCAPI {

namespace Impl { class ObjectID; }

namespace v1 {

/**
 * @brief Identifies an IFC entity (e.g: IfcBuildingStorey, IfcBeam, IfcZone, etc.)
 * @ingroup IFC
 * @since Archicad 28
 * @remarks Use it to query additional IFC related information for the specific entity.
 */
class IFCINOUTAPI_DLL_EXPORT ObjectID final : public ACAPI::Object {
private:
	ObjectID (std::shared_ptr<Impl::ObjectID> impl);

public:
	friend class Assignments;
	friend class HookAssignments;
	friend class HookDataProvider;
	friend class ObjectAccessor;

	~ObjectID ();

	/**
	 * @brief For use as Hash key
	 * @ingroup IFC
	 * @since Archicad 28
	 * @return Hash code
	 */
	ULong	GenerateHashValue () const;

	/**
	 * @brief Equality operator
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param other [in] other
	 * @return Equality result
	 */
	bool	operator== (const IFCAPI::v1::ObjectID& other) const;

	/**
	 * @brief Inequality operator
	 * @ingroup IFC
	 * @since Archicad 28
	 * @param other [in] other
	 * @return Inequality result
	 */
	bool	operator!= (const IFCAPI::v1::ObjectID& other) const;
};

}

using v1::ObjectID;

}


template<>
struct ::std::hash<IFCAPI::ObjectID>
{
	size_t operator() (const IFCAPI::ObjectID& objectID) const
	{
		return objectID.GenerateHashValue ();
	}
};


#endif
