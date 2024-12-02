#ifndef GS_ACAPI_MEP_DISTRIBUTIONSYSTEMSGRAPH_TREELAYOUT_HPP
#define GS_ACAPI_MEP_DISTRIBUTIONSYSTEMSGRAPH_TREELAYOUT_HPP

#include "MEPAPIExport.hpp"
#include "MEPUniqueID.hpp"

// ACAPI
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"

#include <optional>
#include <vector>

namespace ACAPI::Impl {
	class ObjectCreator;
}

namespace ACAPI::MEP {

namespace Impl {
	class IDistributionSystemsGraphTreeNodeImpl;
}
	
namespace v1 {


/**
 * @brief A structural helper class used when iterating through a DistributionSystem in the
 * 		  DistributionSystemsGraph as a tree.
 * @details In addition to the element itself, this class also describes the parent-child
 * 			relationship to other elements during traversal. Note that this parent-child relationship
 * 			has no correlation to additional parameters like IFC flow direction or element creation
 * 			order and the "next" and "previous" elements purely refers to the order they appear in
 * 			the generated tree structure.
 *
 * 			The tree itself is constructed from the DistributionSystemsGraph class in a depth-first search
 * 			approach (DFS) starting from a specified root node.
 * @since Archicad 28
 * @ingroup MEP
 * @par Example code snippets from Test / New MEP
 * 		TraverseTree @snippet DistributionSystemsGraph.cpp TraverseTree_Example
 */
class MEPAPI_EXPORT DistributionSystemsGraphTreeNode final : public Object {
private:
	friend class ACAPI::Impl::ObjectCreator;

	DistributionSystemsGraphTreeNode (std::shared_ptr<Impl::IDistributionSystemsGraphTreeNodeImpl> impl);

public:

	/** @return Returns the ID of the current element being traversed */
	UniqueID							GetElement () const;

	/** @return Returns the IDs of the next elements in the tree structure. */
	std::vector<UniqueID>				GetNextElements () const;

	/**
	 * @return If the current element has a parent element in the tree structure, returns the parent element's
	 * 		   ID. Otherwise returns std::nullopt.
	 */
	std::optional<UniqueID>				GetPreviousElement () const;

	/**
	 * @return If the current element has a parent element in the tree structure, returns the ID of the parent
	 * 		   element's port that is connected to this element's port. Otherwise returns std::nullopt.
	 */
	std::optional<UniqueID>				GetConnectedPortFromPreviousElement () const;

	/**
	 * @return If the current element has a parent element in the tree structure, returns the ID of this
	 * 		   element's port that is connected to the parent element's port. Otherwise returns std::nullopt.
	 */
	std::optional<UniqueID>				GetConnectedPortFromThisElement () const;

	/** @return Returns the zero-based distance from the root node in the tree structure. */
	std::size_t							GetDepthFromRootNode () const;
};


} // v1

using v1::DistributionSystemsGraphTreeNode;

} // ACAPI::MEP


#endif // GS_ACAPI_MEP_DISTRIBUTIONSYSTEMSGRAPH_TREELAYOUT_HPP