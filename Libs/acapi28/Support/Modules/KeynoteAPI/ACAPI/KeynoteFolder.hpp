#ifndef ACAPI_KEYNOTEFOLDER_HPP
#define ACAPI_KEYNOTEFOLDER_HPP

#include "UniString.hpp"
#include "API_Guid.hpp"
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "KeynoteItem.hpp"
#include "KeynoteAPIExport.hpp"
#include <vector>

namespace ACAPI {

namespace Impl {
class KeynoteFolderImpl;
class KeynoteManagerImpl;
} // namespace Impl

namespace Keynote {
namespace v1 {

using Reference = GS::UniString;
using FolderKey = GS::UniString;
using Title = GS::UniString;
using SubFolderUserId = GS::Pair<FolderKey, Title>;

/**
 * @brief A class that represents a folder in the keynote tree structure.
 * @since Archicad 28
 * @ingroup Keynote
 */
class KEYNOTEAPI_DLL_EXPORT KeynoteFolder : public Object {
	friend class ACAPI::Impl::KeynoteManagerImpl;
	friend class KeynoteManager;

public:
	/** @returns The database Id of the folder */
	API_Guid 							GetId () const;

	/** @returns The key of the folder */
	FolderKey							GetKey () const;
	
	/**
	 * @brief Modifies the Key of the folder
	 * @param newKey The key to be set
	 * @returns The result of the modification
	 * 			@snippet Keynote_Test.cpp Modify-Folder-Example
	 */
	Result<void>						SetKey (const FolderKey& newKey);

	/** @returns The title of the folder */
	Title								GetTitle () const;
	
	/**
	 * @brief Modifies the Title of the folder
	 * @param newTitle The Title to be set
	 * @returns The result of the modification
	 * 			@snippet Keynote_Test.cpp Modify-Folder-Example
	 */
	Result<void>						SetTitle (const Title& newTitle);

	/** @returns The reference of the folder */
	Reference							GetReference () const;
	
	/**
	 * @brief Modifies the Reference of the folder
	 * @param newReference The Reference to be set
	 * @returns The result of the modification
	 * 			@snippet Keynote_Test.cpp Modify-Folder-Example
	 */
	Result<void>						SetReference (const Reference& newReference);

	/** @returns The text representation of the folder, used on UI elements */
	GS::UniString						GetUIText () const;

	/** @returns The parent folder of the folder */
	Result<KeynoteFolder>				GetParentFolder () const;

	/** @returns A list of the direct subfolders of the folder */
	Result<std::vector<KeynoteFolder>>	GetDirectSubFolders () const;

	/**
	 * @brief Adds a new subfolder to the folder
	 * @param key The key of the new subfolder
	 * @param title The title of the new subfodler
	 * @returns The created folder
	 * 			@snippet Keynote_Test.cpp Add-Folder-Example
	 */
	Result<KeynoteFolder>				AddSubFolder (const FolderKey& key, const Title& title);

	/**
	 * @brief Removes an existing subfolder of the folder
	 * @param key The key of the subfolder to remove
	 * @param title The title of the subfolder to remove
	 * @returns The result of the modification
	 * 			@snippet Keynote_Test.cpp Remove-Folder-Example
	 */
	Result<void>						RemoveSubFolder (const FolderKey& key, const Title& title);

	/** @returns A list of items in the folder */
	Result<std::vector<KeynoteItem>>	GetDirectItems () const;

	/**
	 * @brief Adds a new item to the folder
	 * @param key The key of the new item
	 * @returns The created item
	 * 			@snippet Keynote_Test.cpp Add-Item-Example
	 */
	Result<KeynoteItem>					AddItem (const ItemKey& key);

	/**
	 * @brief Removes an existing item of the folder
	 * @param key The key of the item to remove
	 * @returns The result of the modification
	 * 			@snippet Keynote_Test.cpp Remove-Item-Example
	 */
	Result<void>						RemoveItem (const ItemKey& key);

private:
	explicit KeynoteFolder (std::shared_ptr<ACAPI::Impl::KeynoteFolderImpl> impl);
};

} // namespace v1
} // namespace Keynote

using namespace v1;

} // namespace ACAPI


#endif /* ACAPI_KEYNOTEFOLDER_HPP */
