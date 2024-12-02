#ifndef ACAPI_LIBRARYMANAGER_HPP
#define ACAPI_LIBRARYMANAGER_HPP

#include <functional>

#include "ACAPI/ArchicadAPIExport.hpp"
#include "ACAPI/Library/LibPart.hpp"
#include "ACAPI/Library/Library.hpp"
#include "ACAPI/ModifyScope.hpp"
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"

#include "APIdefs_ErrorCodes.h"

//! @cond Doxygen_Suppress
API_Token ACAPI_GetToken ();
//! @endcond

namespace ACAPI {
namespace Library {
namespace v1 {

class LibraryTreePath;
class GSMObject;

/**
 * @brief LibraryManager is the central point of the Library and the LibPart management.
 * @ingroup LibraryManagement
 * @since Archicad 28
 */
class ARCHICADAPI_EXPORT LibraryManager final : public Object
{
	friend Result<LibraryManager> GetLibraryManager ();
	explicit LibraryManager (const API_Token&);
	bool IsValid () const;

public:
	class Modifier;

	/**
	 * @brief Executed the passed modifier scope in a NotUndoable command.
	 * @ingroup LibraryManagement
	 * @param modifierFunc Reference of the ModifierFunc.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 * @remarks In Teamwork, the project's library list should be reserved before calling this function.
	 */
	Result<void> ModifyLibraryList (const std::function<GSErrCode (Modifier&)>& modifierFunc);

	// ---- Library Query functions --------------------------------------------

	/**
	 * @brief Find Libraries using a custom selector function.
	 * @ingroup LibraryManagement
	 * @param selector Reference of the selector function.
	 * @return Returns the libraries which meet the condition in the selector.
	 */
	std::vector<Library> FindLibraries (const std::function<bool (const Library&)>& selector) const;

	/**
	 * @brief Find Library using a custom selector function.
	 * @ingroup LibraryManagement
	 * @param selector Reference of the selector function.
	 * @return Returns the first Library which meets the condition in the selector or an error if the Library can not be found.
	 */
	Result<Library> FindLibrary (const std::function<bool (const Library&)>& selector) const;

	/**
	 * @brief Returns the Library with the given name.
	 * @ingroup LibraryManagement
	 * @param name Name of the library.
	 * @return Returns the Library or an error if the Library can not be found.
	 */
	Result<Library> GetLibraryByName (const GS::UniString& name) const;

	/**
	 * @brief A faster way to get the embedded library.
	 * @ingroup LibraryManagement
	 * @return Returns the Embedded Library, Error if the LibraryManager is invalid.
	 */
	Result<Library> GetEmbeddedLibrary () const;

	/**
	 * @brief Returns the Library containing the Library Part
	 * @ingroup LibraryManagement
	 * @param libPart Reference of the library part.
	 * @return Returns the Library or an error if the LibPart is not loaded, or the LibraryManager is invalid
	 */
	Result<Library> GetLibraryOfLibPart (const LibPart& libPart) const;

	// ---- LibPart Query functions --------------------------------------------

	/**
	 * @brief Find LibParts using a custom selector function.
	 * @ingroup LibraryManagement
	 * @param selector Reference of the selector function.
	 * @return Returns the libparts which meet the condition in the selector.
	 */
	std::vector<LibPart> FindLibParts (const std::function<bool (const LibPart&)>& selector) const;

	/**
	 * @brief Find Library Part using a custom selector function.
	 * @ingroup LibraryManagement
	 * @param selector Reference of the selector function.
	 * @return Returns the first Library Part which meets the condition in the selector or an error if the LibPart can not be found.
	 */
	Result<LibPart> FindLibPart (const std::function<bool (const LibPart&)>& selector) const;

	/**
	 * @brief Returns a library part with the filename.
	 * @ingroup LibraryManagement
	 * @param name The name of the libpart with file extension.
	 * @return Returns the LibPart or an error if the LibraryManager is invalid, or the LibPart can not be found in the libraries.
	 * @remarks The name is the (localized) file name of the library part which is shown in the Library Manager.
	 */
	Result<LibPart>	GetLibPartByName (const GS::UniString& name) const;

	/**
	 * @brief Returns the Library Part of the GSMObject.
	 * @ingroup LibraryManagement
	 * @param gsmObject Reference of the GSMObject.
	 * @return Returns the LibPart or an error if the LibraryManager is invalid, or the GSMObject is invalid.
	 * @remarks The function returns the LibPart which contains the GSMObject. The GSMObject should be loaded from a library part.
	 */
	Result<LibPart>	GetLibPartByGSMObject (const GSMObject& gsmObject) const;

	// ---- Library Tree Path functions --------------------------------------------

	/**
	 * @brief Returns the LibraryTreePath of the LibPart.
	 * @ingroup LibraryManagement
	 * @param libPart Reference of the LibPart.
	 * @return Returns the LibraryTreePath or an error if the LibraryManager is invalid, or the LibPart is invalid.
	 */
	Result<LibraryTreePath>	GetLibraryTreePathOfLibPart (const LibPart& libPart) const;

	/**
	 * @brief Returns the Teamwork Identifier of the Library Tree location.
	 * @ingroup LibraryManagement
	 * @param libraryTreePath Library Tree location.
	 * @return Returns the Teamwork Identifier or an error if the LibraryManager is invalid, or the libraryTreePath does not point to a Teamwork library location.
	 */
	Result<GS::Guid>	GetTWID (const LibraryTreePath& libraryTreePath) const;

	// ---- Object Query functions --------------------------------------------

	/**
	 * @brief Returns the .gsm object representation of the Library Part
	 * @ingroup LibraryManagement
	 * @param libPart Reference of the library part.
	 * @return Returns the GSMObject or an error if the LibPart is not of object type, or the LibraryManager is invalid
	 */
	Result<GSMObject>		GetGSMObjectOfLibPart (const LibPart& libPart) const;

	/**
	 * @brief Loads a .gsm object from a file.
	 * @ingroup LibraryManagement
	 * @param location The file location.
	 * @return Returns the GSMObject or an error if the file cannot be loaded.
	 * @remarks The key difference between this function and the GetGSMObjectOfLibPart is that this function loads the object directly from a file,
	 * 			while the other function returns the object representation of a loaded library part which can be localized or modified.
	 */
	Result<GSMObject>		LoadGSMObjectFromFile (const IO::Location& location) const;

	
	// ---- Old API compatibility --------------------------------------------
	/**
	 * @brief Returns a library part with the given index.
	 * @ingroup LibraryManagement
	 * @param libPartIndex Index of the library part.
	 * @return Returns the LibPart or an error if the LibraryManager is invalid, or the LibPart can not be found in the libraries
	 * @remarks This function is here for compatibility reasons. Should only be used where collaboration with old API functions is necessary.
	 * 			The index is not a stable identifier of the library part, it can change when the library list is modified.
	 */
	Result<LibPart> GetLibPartByLibInd (Int32 libPartIndex) const;

	/**
	 * @brief Returns the index of the library part.
	 * @ingroup LibraryManagement
	 * @param libPart Reference of the library part.
	 * @return Returns the index or an error if the LibraryManager is invalid, or the LibPart can not be found in the libraries or does not have an
	 * 		   index.
	 * @remarks This function is here for compatibility reasons. Should only be used where collaboration with old API functions is necessary.
	 * 			The index is not a stable identifier of the library part, it can change when the library list is modified.
	 */
	Result<Int32> GetLibIndOfLibPart (const LibPart& libPart) const;
};


/**
 * @brief Creates a @ref LibraryManager instance.
 * @ingroup LibraryManagement
 * @return The new LibraryManager instance a plan is loaded otherwise APIERR_NOPLAN.
 * @remarks This is the entry point of the Library Management on the API.
 */
inline Result<LibraryManager> GetLibraryManager ()
{
	LibraryManager lm (ACAPI_GetToken ());
	if (lm.IsValid ())
		return Ok (lm);
	else
		return {Error (APIERR_NOPLAN, "Library Manager cannot be initialised without plan."), ACAPI_GetToken ()};
}


/**
 * @brief The Modifier object of the LibraryManager.
 * @ingroup LibraryManagement
 * @since Archicad 28
 */
class ARCHICADAPI_EXPORT LibraryManager::Modifier final : public ACAPI::ModifierBase
{
	friend LibraryManager;
	LibraryManager& parent;
	Modifier (LibraryManager& parent);
	virtual ~Modifier ();
	virtual void FinalizeModification () override;

public:

	/**
	 * @brief Add a libary to the actual library list.
	 * @ingroup LibraryManagement
	 * @param libraryPath Reference of library location.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	Result<void> AddLibrary (const IO::Location& libraryPath);

	/**
	 * @brief Add a server libary to the actual library list.
	 * @ingroup LibraryManagement
	 * @param twServerURL The teamwork server URL.
	 * @param twServerPath Relative location of the library from the root of the BIM Server.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	Result<void> AddLibrary (const GS::UniString& twServerURL, const GS::UniString& twServerPath);

	/**
	 * @brief Remove a libary from the actual library list. Embedded and Built-In libraries cannot be removed.
	 * @ingroup LibraryManagement
	 * @param library The library to be removed.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	Result<void> RemoveLibrary (const Library& library);
};

// ---- Library selectors ---------------------------------------------------

/**
 * @brief A selector for the FindLibraries function. It selects all libraries.
 * @ingroup LibraryManagement
 * @return Always true.
 */
inline bool SelectAllLibraries (const Library&) { return true; };

/**
 * @brief A selector for the FindLibraries function. It selects all libraries which are not embedded and not built-in.
 * @ingroup LibraryManagement
 * @param lib Reference of the library.
 * @return True if the library is not embedded and not built-in, otherwise false.
 */
inline bool SelectLoadedLibraries (const Library& lib) { return !*lib.IsEmbedded () && !*lib.IsBuiltIn ();};


// ---- LibPart selectors ---------------------------------------------------

/**
 * @brief A selector for the FindLibParts function. It selects all libparts.
 * @ingroup LibraryManagement
 * @return Always true.
 */
inline bool SelectAllLibParts (const LibPart&) {	return true; }


/**
 * @brief A selector for the FindLibParts function. It selects all object libparts.
 * @ingroup LibraryManagement
 * @param lp Reference of the libpart.
 * @return True if the libpart is a GSM object, otherwise false.
 */
inline bool SelectObjectLibParts (const LibPart& lp) { return *lp.GetType () == LibPartType::Object; }


/**
 * @brief A selector for the FindLibParts function. It selects all text libparts.
 * @ingroup LibraryManagement
 * @param lp Reference of the libpart.
 * @return True if the libpart is a text file, otherwise false.
 */
inline bool SelectTextLibParts (const LibPart& lp) { return *lp.GetType () == LibPartType::Text; }


/**
 * @brief A selector for the FindLibParts function. It selects all image libparts.
 * @ingroup LibraryManagement
 * @param lp Reference of the libpart.
 * @return True if the libpart is an image file, otherwise false.
 */
inline bool SelectImageLibParts (const LibPart& lp) { return *lp.GetType () == LibPartType::Image; }


}	 // namespace v1
using namespace v1;

}	 // namespace Library
}	 // namespace ACAPI


#endif