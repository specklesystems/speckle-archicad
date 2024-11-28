#ifndef GS_ACAPI_MEP_DISTRIBUTIONSYSTEM_HPP
#define GS_ACAPI_MEP_DISTRIBUTIONSYSTEM_HPP

#include "MEPAPIExport.hpp"
#include "MEPUniqueID.hpp"
#include "MEPEnums.hpp"

// ACAPI
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"

// from APICore
#include "APIdefs_AttributeIndex.hpp"

//#include <memory>
#include <vector>

namespace ACAPI::Impl {
	class ObjectCreator;
}

namespace ACAPI::MEP {

namespace Impl {
	class IDistributionSystemImpl;
}

namespace v1 {

class DistributionSystemsGraphTreeNode;


/**
 * @brief A helper object representing a "distribution system", which is a set of MEP elements sharing the
 * 		  same system category index and MEP domain. (E.g. "hot water pipes" or "cold air ducts")
 * @details A DistributionSystem is a lightweight wrapper object for use within the API and does not represent
 * 			any actual database objects and will thus never be serialized to a pln file. The lifetime of a
 * 			DistributionSystem object is controlled by the DistributionSystemsGraph object that created it,
 * 			meaning all functions of DistributionSystem will return an APIERR_DELETED error after the owning
 * 			DistributionSystemsGraph object has gone out of scope.
 * @since Archicad 28
 * @ingroup MEP
 */
class MEPAPI_EXPORT DistributionSystem final : public Object {
private:
	friend class ACAPI::Impl::ObjectCreator;

	DistributionSystem (std::shared_ptr<Impl::IDistributionSystemImpl> impl);

public:
	~DistributionSystem ();

	/** @return Returns the system category this distribution system belongs to */
	Result<API_AttributeIndex> GetSystemCategory () const;

	/** @return Returns the MEP domain this distribution system belongs to */
	Result<Domain> GetMEPDomain () const;

	/** @return Returns IDs of the element contained by this distribution system */
	Result<std::vector<UniqueID>> GetElements () const;

	/**
	 * @brief Traverses a distribution system from a graph through a tree layout with a traversal function
	 * 		  invoked for each generated node in the tree.
	 * @details Traversal is done in a depth first search (DFS) pattern starting with a
	 * 			root node defined by the system itself.
	 * @param traversalFunction A callable that will be invoked once per tree node. Return false in callable to exit traversal early.
	 * @return Returns an Error if the distribution system does not belong to a DistributionSystemsGraph instance or if traversal failed, otherwise nothing
	 * 		   @snippet DistributionSystemsGraph.cpp TraverseTree_Example
	 */
	Result<void> TraverseTree (std::function<bool (const DistributionSystemsGraphTreeNode&)> traversalFunction) const; 
};


} // v1

using v1::DistributionSystem;

} // ACAPI::MEP

#endif // GS_ACAPI_MEP_DISTRIBUTIONSYSTEM_HPP