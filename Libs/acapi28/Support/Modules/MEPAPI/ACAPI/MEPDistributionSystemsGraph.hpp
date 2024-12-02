#ifndef GS_ACAPI_MEP_DISTRIBUTIONSYSTEMSGRAPH_HPP
#define GS_ACAPI_MEP_DISTRIBUTIONSYSTEMSGRAPH_HPP


#include "MEPAPIExport.hpp"
#include "MEPUniqueID.hpp"
#include "MEPEnums.hpp"

// ACAPI
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"

#include <memory>
#include <vector>
#include <functional>

namespace ACAPI::Impl {
class ObjectCreator;
}

namespace ACAPI::MEP {

namespace Impl {
	class IDistributionSystemsGraphImpl;
}

namespace v1 {

class DistributionSystem;
class DistributionSystemsGraphTreeNode;


/**
 * @brief A graph data structure to display MEP distribution systems data.
 * @details A "distribution system" is defined as a connected set of elements sharing
 * 			a common system category and MEP domain. (E.g. "hot water pipes" or "cold
 * 			air ducts")
 * @since Archicad 28
 * @ingroup MEP
 * @par Example code snippets from Test / New MEP
 * 		TraverseTree @snippet DistributionSystemsGraph.cpp TraverseTree_Example
 * 		GetElements @snippet DistributionSystemsGraph.cpp GetElements_Example
 * 		GetSystems @snippet DistributionSystemsGraph.cpp GetSystems_Example
 */
class MEPAPI_EXPORT DistributionSystemsGraph final : public Object {
	friend class ACAPI::Impl::ObjectCreator;
private:
	DistributionSystemsGraph (std::shared_ptr<Impl::IDistributionSystemsGraphImpl> impl);

	static Result<DistributionSystemsGraph> Create (const API_Token& APIToken);

public:
	friend Result<DistributionSystemsGraph> CreateDistributionSystemsGraph ();

	~DistributionSystemsGraph ();

	/**
	 * @return Returns the distribution systems collected by the graph structure
	 * 		   @snippet DistributionSystemsGraph.cpp GetSystems_Example
	 */
	std::vector<DistributionSystem> GetSystems () const;

	/**
	 * @return Returns the unique IDs of all the elements collected by the graph structure
	 * 		   @snippet DistributionSystemsGraph.cpp GetElements_Example
	 */
	std::vector<UniqueID> GetElements () const;

	/** @return Returns the unique IDs of all the ports collected by the graph structure */
	std::vector<UniqueID> GetPorts () const;

	/**
	 * @brief Traverses a distribution system in the graph through a tree layout with a traversal function
	 * 		  invoked for each generated node in the tree.
	 * @details Traversal is done in a depth first search (DFS) pattern starting with a
	 * 			root node defined by the system itself.
	 * @param system The desired distribution system to traverse
	 * @param traversalFunction A callable that will be invoked once per tree node. Return false in callable to exit traversal early.
	 * @return Returns an Error if the distribution system could not be found or if traversal failed, otherwise nothing
	 * 		   @snippet DistributionSystemsGraph.cpp TraverseTree_Example
	 */
	Result<void> TraverseTree (const DistributionSystem& system, std::function<bool (const DistributionSystemsGraphTreeNode&)> traversalFunction) const;

};


/**
 * @brief Creates a DistributionSystemsGraph
 * @ingroup MEP
 * @return If able, creates a new DistributionSystemsGraph, otherwise Error.
 * 		   @snippet DistributionSystemsGraph.cpp CreateDistributionSystemsGraph_Example
 */
inline Result<DistributionSystemsGraph> CreateDistributionSystemsGraph ()
{
	return DistributionSystemsGraph::Create (ACAPI_GetToken ());
}

} // v1

using v1::DistributionSystemsGraph;
using v1::CreateDistributionSystemsGraph;

} // ACAPI::MEP


#endif // GS_ACAPI_MEP_DISTRIBUTIONSYSTEMSGRAPH_HPP