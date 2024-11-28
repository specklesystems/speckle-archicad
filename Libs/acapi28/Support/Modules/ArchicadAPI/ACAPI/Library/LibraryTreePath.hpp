#ifndef ACAPI__LM_LIBRARYPATH_HPP
#define ACAPI__LM_LIBRARYPATH_HPP

#include "ACAPI/ArchicadAPIExport.hpp"
#include "ACAPI/ModifyScope.hpp"
#include "ACAPI/Object.hpp"

#include <vector>

namespace GS { class UniString; }

namespace ACAPI {
namespace Library {

namespace Impl { class LibraryTreePathImpl; }
namespace Impl { class LibraryManagerImpl; }

namespace v1 {

/**
 * @brief Library tree location (E.g. folder, Library Part)
 * @ingroup LibraryManagement
 * @since Archicad 28
 */
class ARCHICADAPI_EXPORT LibraryTreePath final : public Object
{
	friend class Impl::LibraryManagerImpl;
	friend class Impl::LibraryTreePathImpl;
private:
	
	explicit LibraryTreePath (std::shared_ptr<Impl::LibraryTreePathImpl> libraryTreePathImpl);

public:

	/**
	 * @brief Root path of the library tree.
	 * @ingroup LibraryManagement
	 * @return Returns true if the path is the library root node, false otherwise.
	 */
	bool IsRoot () const;

	/**
	 * @brief The name of the current node.
	 * @ingroup LibraryManagement
	 * @return Returns the name of the last node/libpart of library tree path.
	 */
	GS::UniString GetLastPart () const;

	/**
	 * @brief The parent of the represented node.
	 * @ingroup LibraryManagement
	 * @return Returns a new LibraryTreePath without the last part of the path if it is not the root; otherwise, return a copy of itself.
	 */
	LibraryTreePath GetParent () const;
    
	/**
	 * @brief The parts of the path.
	 * @ingroup LibraryManagement
	 * @return Returns the names of the parts of the path in vector.
	 */
	std::vector<GS::UniString> GetParts () const;
};

}  // namespace v1
using namespace v1;

}  // namespace Library
}  // namespace ACAPI


#endif /* ACAPI__LM_LIBRARYPATH_HPP */