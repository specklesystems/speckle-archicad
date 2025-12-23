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

// STL
#include <vector>

namespace ACAPI::Impl {
	class ObjectCreator;
}

namespace ACAPI::MEP {

namespace Impl {
	class IDistributionSystemImpl;
}

class DistributionSystemsGraphTreeNode;


/**
 * @brief A helper object representing a "distribution system", which is a set of connected MEP elements sharing
   		  the same system category index and MEP domain. (E.g. "hot water pipes" or "cold air ducts")
 * @details A DistributionSystem is a lightweight wrapper object for use within the API and does not represent
 * 			any actual database objects and will thus never be serialized to a pln file. The lifetime of a
 * 			DistributionSystem object is controlled by the DistributionSystemsGraph object that created it,
 * 			meaning all functions of DistributionSystem will return an APIERR_DELETED error after the owning
 * 			DistributionSystemsGraph object has gone out of scope.
 * 
 * 			Instance specific attributes of a DistributionSystem can be fetched via its possibly associated
 * 			PhysicalSystem object.
 * @see PhysicalSystem
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

	/**
	 * @brief Traverses a distribution system from a graph through a tree layout with a traversal function
	 *		  invoked for each generated node in the tree, starting with the supplied root element.
	 * @details Functions the same as the previous overload, but allows you to manually specify the root node in the form of the ID of
	 *			an element instead of relying on the system's defined root node.
	 * @param traversalFunction A callable that will be invoked once per tree node. Return false in callable to exit traversal early.
	 * @param rootElement The ID of the element part of the DistributionSystem to start the traversal from.
	 * @return Returns an Error if the distribution system does not belong to a DistributionSystemsGraph instance or if traversal failed, otherwise nothing
	 */
	Result<void> TraverseTree (std::function<bool (const DistributionSystemsGraphTreeNode&)> traversalFunction, const UniqueID& rootElement) const;

	/**
	 * @brief Fetch the IDs of the PhysicalSystem instances connected to this DistributionSystem
	 * @details A DistributionSystem represents a logical grouping of connected elements. A PhysicalSystem on the other hand, describes
	 *			an instance of a system defined by the user. As such, while they describe different properties of the set of elements,
	 *			it's possible to fetch the PhysicalSystems associated with a DistributionSystem. Multiple PhysicalSystems can define
	 *			the same root element as their root element, which means multiple PhysicalSystems can be associated with the same
	 *			DistributionSystem.
	 * @return The IDs of the PhysicalSystem instances associated with this DistributionSystem
	 */
	Result<std::vector<UniqueID>> GetPhysicalSystemIDs () const;
};

} // ACAPI::MEP

#endif // GS_ACAPI_MEP_DISTRIBUTIONSYSTEM_HPP