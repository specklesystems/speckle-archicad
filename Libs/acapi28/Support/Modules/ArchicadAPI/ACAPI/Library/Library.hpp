#ifndef ACAPI_LIBRARY_HPP
#define ACAPI_LIBRARY_HPP

#include "ACAPI/ArchicadAPIExport.hpp"
#include "ACAPI/ModifyScope.hpp"
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"

#include "APIdefs_ErrorCodes.h"

#include <vector>
#include <tuple>

namespace GS { class UniString; }

namespace ACAPI {
namespace Library {

namespace Impl { class LibraryImpl; }
namespace Impl { class LibraryManagerImpl; }

namespace v1 {


/**
 * @brief Library is the representation of an item in the library list of an ArchiCAD project.
 * @ingroup LibraryManagement
 * @since Archicad 28
 */
class ARCHICADAPI_EXPORT Library final : public Object
{
	friend class Impl::LibraryManagerImpl;

	explicit Library (std::shared_ptr<Impl::LibraryImpl> libraryImpl);
	bool IsValid () const;

public:

	/**
	 * @brief The name of the library.
	 * @ingroup LibraryManagement
	 * @return Returns the name of the Library if the Library is valid, otherwise error.
	 */
	ACAPI::Result<GS::UniString> GetName () const;

	/**
	 * @brief Location of the Library. If the library is a teamwork library, the location is the local cache location.
	 * @ingroup LibraryManagement
	 * @return Returns the location of the Library if the Library is valid, otherwise error.
	 */
	ACAPI::Result<IO::Location> GetLocation () const;

	/**
	 * @brief The teamwork server URL is the URL of the BIMcloud where the library is located, like "http://example.com"
	 * @ingroup LibraryManagement
	 * @return Returns the teamwork server URL if the library is valid, otherwise error.
	 */
	ACAPI::Result<GS::UniString> GetTWServerUrl () const;

	/**
	 * @brief The relative location of the library from the root of the BIMcloud server, like "Libraries/The shared library.lcf"
	 * @ingroup LibraryManagement
	 * @return Returns the relative location of the library if the library is valid, otherwise error.
	 */
	ACAPI::Result<GS::UniString> GetTWServerPath () const;

	/**
	 * @brief The library is loaded from local (or netwrork) file system.
	 * @ingroup LibraryManagement
	 * @return Returns true if the library is local, false otherwise. If the library reference is not valid, returns error.
	 */
	ACAPI::Result<bool> IsLocal () const;

	/**
	 * @brief The library is built-in, if it is the Archicad's or any add-ons built-in library.
	 * @ingroup LibraryManagement
	 * @return Returns true if the library is built-in, false otherwise. If the library reference is not valid, returns error.
	 */
	ACAPI::Result<bool> IsBuiltIn () const;

	/**
	 * @brief The library is embedded, if it is the one embedded in the plan file.
	 * @ingroup LibraryManagement
	 * @return Returns true if the library is the Embedded library, false otherwise. If the library reference is not valid, returns error.
	 */
	ACAPI::Result<bool> IsEmbedded () const;

	/**
	 * @brief The library is a server library, if it is loaded from a BIMcloud server.
	 * @ingroup LibraryManagement
	 * @return Returns true if the library is server library, false otherwise. If the library reference is not valid, returns error.
	 */
	ACAPI::Result<bool> IsServer () const;

	/**
	 * @brief The library is a library package, if it is a .libpack file.
	 * @ingroup LibraryManagement
	 * @return Returns true if the library is a library package, false otherwise. If the library reference is not valid, returns error.
	 */
	ACAPI::Result<bool> IsPackage () const;

	/**
	 * @brief The package ID of the library package.
	 * @ingroup LibraryManagement
	 * @return Returns the package ID of the library package if the library is a package, otherwise error.
	 */
	ACAPI::Result<GS::Guid> GetPackageID () const;
	
	/**
	 * @brief The main version of the library package. Different main versions are incompatible and have different package IDs.
	 * @ingroup LibraryManagement
	 * @return Returns the main version of the library package if the library is a package, otherwise error.
	 */
	ACAPI::Result<UInt32>	GetPackageMainVersion () const;

	/**
	 * @brief The sub version of the library package.
	 * @ingroup LibraryManagement
	 * @return Returns the subversion of the library package if the library is a package, otherwise error.
	 */
	ACAPI::Result<UInt32>	GetPackageSubVersion () const;

	/**
	 * @brief The minimum Archicad version of the library package.
	 * @ingroup LibraryManagement
	 * @return Returns the minimum Archicad version of the library package if the library is a package, otherwise error.
	 */
	ACAPI::Result<UInt32>	GetPackageMinACVersion () const;

	/**
	 * @brief The minimum Archicad build number of the library package.
	 * @ingroup LibraryManagement
	 * @return Returns the minimum Archicad build number of the library package if the library is a package, otherwise error.
	 */
	ACAPI::Result<UInt32>	GetPackageMinACBuildNumber () const;

	/**
	 * @brief The dependencies of the library package. The dependencies are a list of name, package ID, subversion tuple. 
	 * @ingroup LibraryManagement
	 * @return Returns the dependencies of the library package if the library is a package, otherwise error.
	 */
	ACAPI::Result<std::vector<std::tuple<GS::UniString, GS::Guid, UInt32>>> GetPackageDependencies () const;
};

}  // namespace v1
using namespace v1;

}  // namespace Library
}  // namespace ACAPI

#endif /* ACAPI__LM_LIBRARY_HPP */