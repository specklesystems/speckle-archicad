#ifndef FAVORITE_HPP
#define FAVORITE_HPP

#include "ACAPI/ElementDefault.hpp"
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "APIdefs_Elements.h"
#include "APIdefs_Environment.h"

#include "GXImage.hpp"

#include <vector>
#include <memory>
#include <optional>

//! @cond Doxygen_Suppress
API_Token ACAPI_GetToken ();
//! @endcond

union API_Element;
struct API_Favorite;
struct API_SubElement;
struct API_ElementMemo;
struct API_Property;
struct API_Guid;
struct API_ElemCategoryValue;


namespace ACAPI {

namespace Impl {
class FavoriteImpl;
class FavoriteFolderImpl;
class FavoriteManagerImpl;
}

namespace Favorite {

class FavoriteFolder;

/**
 * @brief Favorite class represents a favorite element in the Archicad Favorite Manager.
 * @ingroup Favorite
 * @since Archicad 29
 */
class ARCHICADAPI_EXPORT Favorite final : public ACAPI::Object {
	friend Impl::FavoriteManagerImpl;
	friend Impl::FavoriteFolderImpl;
	friend Impl::FavoriteImpl;
	explicit Favorite (std::shared_ptr<Impl::FavoriteImpl>);

public:
	/**
	 * @return True if the Favorite refers to a valid favorite instance, otherwise false.
	 */
	bool IsValid () const;

	/**
	 * @return The name of the favorite. If the favorite is not valid, an error is returned.
	 */
	Result<GS::UniString>  GetName () const;

	/**
	 * @return The parent folder of the favorite. If the favorite is not valid, an error is returned.
	 */
	Result<FavoriteFolder> GetParentFolder () const;

	/**
	 * @return The element type of the favorite. If the favorite is not valid, an error is returned.
	 */
	Result<API_ElemType>   GetElementType () const;

	/**
	 * @return The default of the favorite in API_Element format. If the favorite is not valid, an error is returned.
	 */
	Result<API_Element>			  GetOldElementDefault () const;

	/**
	 * @return The subelement defaults of the favorite if the element type has subelements. If the favorite is not valid, an error is returned.
	 */
	Result<std::vector<API_SubElement>> GetSubElements () const;

	/**
	 * @return The API_ElementMemo of the favorite. If the favorite is not valid, an error is returned.
	 */
	Result<API_ElementMemo>			  GetMemo () const;

	/**
	 * @return The API_Element of the favorite marker if the element type has a marker element. If the favorite is not valid, an error is returned.
	 */
	Result<API_Element>				  GetElementMarker () const;

	/**
	 * @return The API_ElementMemo of the favorite marker if the element type has a marker element. If the favorite is not valid, an error is returned.
	 */
	Result<API_ElementMemo>			  GetMemoMarker () const;

	/**
	 * @return The ElementDefault of the favorite. If the favorite is not valid, an error is returned.
	 */
	Result<ACAPI::ElementDefault> GetElementDefault () const;

	/**
	 * @return The properties of the favorite. If the favorite is not valid, an error is returned.
	 */
	Result<std::vector<API_Property>>					GetProperties () const;

	/**
	 * @return The classifications of the favorite. If the favorite is not valid, an error is returned.
	 */
	Result<std::vector<GS::Pair<API_Guid, API_Guid>>> GetClassifications () const;

	/**
	 * @return The element category values of the favorite. If the favorite is not valid, an error is returned.
	 */
	Result<std::vector<API_ElemCategoryValue>>		GetElemCategoryValues () const;

	/**
	 * @brief Get the preview image of the favorite.
	 * @param viewType The view type of the preview image. The available view types are defined in APIdefs_Environment.h.
	 * @param img The preview image of the favorite.
	 * @return Success if the preview image is successfully retrieved, otherwise an error.
	 */
	Result<void> GetPreviewImage (API_ImageViewID viewType, NewDisplay::NativeImage& img) const;
};

/**
 * @brief FavoriteFolder class represents a favorite folder in the Archicad Favorite Manager.
 * @ingroup Favorite
 * @since Archicad 29
 */
class ARCHICADAPI_EXPORT FavoriteFolder final : public ACAPI::Object {
	friend Impl::FavoriteManagerImpl;
	friend Impl::FavoriteFolderImpl;
	friend Impl::FavoriteImpl;
	explicit FavoriteFolder (std::shared_ptr<Impl::FavoriteFolderImpl>);
public:
	/**
	 * @return True if the FavoriteFolder refers to a valid favorite folder instance, otherwise false.
	 */
	bool IsValid () const;

	/**
	 * @return The name of the favorite folder. If the favorite folder is not valid, an error is returned.
	 */
	Result<GS::UniString> GetName () const;

	/**
	 * @return True if the favorite folder is the root folder, otherwise false.
	 */
	Result<bool>		  IsRoot () const;

	/**
	 * @return The parent folder of the favorite folder. If the favorite folder is not valid or the root folder, an error is returned.
	 */
	Result<FavoriteFolder> GetParentFolder () const;

	/**
	 * @return The part of the path of the favorite folder.
	 */
	std::vector<GS::UniString> GetPath () const;

	/**
	 * @return The subfolders of the favorite folder.
	 */
	std::vector<FavoriteFolder> GetSubFolders () const;

	/**
	 * @return The favorites from the favorite folder.
	 */
	std::vector<Favorite> GetFavorites () const;
};

/**
 * @brief FavoriteManager class is the manager class for the Archicad Favorite Manager.
 * @ingroup Favorite
 * @since Archicad 29
 */
class ARCHICADAPI_EXPORT FavoriteManager : public ACAPI::Object {
protected:
//! @cond Doxygen_Suppress
	explicit FavoriteManager (const API_Token&);
	friend FavoriteManager GetFavoriteManager ();
//! @endcond
public:
	/**
	 * @brief Get a favorite by its name.
	 * @param name The name of the favorite.
	 * @return The favorite with the given name if it exists, otherwise an error.
	 */
	Result<Favorite> GetFavoriteByName (const GS::UniString& name) const;

	/**
	 * @brief Get all favorites of a specific elem type.
	 * @param type The type of the favorites.
	 * @return The favorites of the given type.
	 */
	std::vector<Favorite> GetFavoritesByElementType (API_ElemType type) const;

	/**
	 * @brief Get all favorites.
	 * @return Vector of all favorites.
	 */
	std::vector<Favorite> GetAllFavorites () const;

	/**
	 * @brief Get the root folder of the favorite manager.
	 * @return The root folder of the favorite manager.
	 */
	Result<FavoriteFolder> GetRootFolder () const;

	/**
	 * @brief Options for handling conflicts while creating and importing favorites
	 * @ingroup Favorite
	 */
	enum class ConflictPolicy {
		/**
		 * @brief The create/import process will fail if a conflict is detected.
		 */
		Error,

		/**
		 * @brief The create/import process will skip the conflicting favorites.
		 */
		Skip,

		/**
		 * @brief The create/import process will overwrite the conflicting favorites.
		 */
		OverwriteExisting,

		/**
		 * @brief The create/import process will create a unique name for the new conflicting favorites.
		 */
		RenameNew
	};

	/**
	 * @brief Export a list of favorites to XML files.
	 * @param favorites The list of favorites to export.
	 * @param targetFolder The target folder where the XML files will be saved.
	 * @return Success if the export is successful, otherwise an error.
	 */
	Result<void> ExportFavorites (const std::vector<ACAPI::Favorite::Favorite>& favorites, const IO::Location& targetFolder) const;
	
	/** 
	 * @brief Export a list of favorites to a PRF file.
	 * @param favorites The list of favorites to export.
	 * @param targetFile The target PRF file. The file extension should be ".prf" or "pref".
	 * @return Success if the export is successful, otherwise an error.
	 */
	Result<void> ExportFavoritesToLegacyPRF (const std::vector<ACAPI::Favorite::Favorite>& favorites, IO::Location& targetFile) const;

	/**
	 * @brief Import favorites from specific XML files.
	 * @param favoriteXMLs The list of XML files to import.
	 * @param conflictPolicy The conflict policy to handle name conflicts.
	 * @param targetOrKeep The target folder where the favorites will be imported. If it is empty, the favorites will be imported to the root folder.
	 * @pre This function requires an opened NotUndoable command scope.
	 * @return Success if the import is successful, otherwise an error.
	 */
	Result<void> ImportFavorites (const std::vector<IO::Location>&						favoriteXMLs,
								  ACAPI::Favorite::FavoriteManager::ConflictPolicy		conflictPolicy,
								  const std::optional<ACAPI::Favorite::FavoriteFolder>& targetOrKeep) const;

	/**
	 * @brief Import all favorites from a specific folder.
	 * @param sourceFolder The source folder where the favorites are located.
	 * @param conflictPolicy The conflict policy to handle name conflicts.
	 * @param targetOrKeep The target folder where the favorites will be imported. If it is empty, the favorites will be imported to the root folder.
	 * @pre This function requires an opened NotUndoable command scope.
	 * @return Success if the import is successful, otherwise an error.
	 */
	Result<void> ImportAllFavorites (const IO::Location&								   sourceFolder,
									 ACAPI::Favorite::FavoriteManager::ConflictPolicy	   conflictPolicy,
									 const std::optional<ACAPI::Favorite::FavoriteFolder>& targetOrKeep) const;

	/**
	 * @brief Import favorites from a specific PRF file.
	 * @param prfFile The PRF file to import.
	 * @param conflictPolicy The conflict policy to handle name conflicts.
	 * @param targetOrKeep The target folder where the favorites will be imported. If it is empty, the favorites will be imported to the root folder.
	 * @pre This function requires an opened NotUndoable command scope.
	 * @return Success if the import is successful, otherwise an error.
	 */
	Result<void> ImportFavoritesFromLegacyPRF (const IO::Location&									 prfFile,
											   ACAPI::Favorite::FavoriteManager::ConflictPolicy		 conflictPolicy,
											   const std::optional<ACAPI::Favorite::FavoriteFolder>& targetOrKeep) const;

	/**
	 * @brief Delete a favorite.
	 * @param favorite The favorite to delete.
	 * @pre This function requires an opened NotUndoable command scope.
	 * @return Success if the delete is successful, otherwise an error.
	 */
	Result<void> DeleteFavorite (const ACAPI::Favorite::Favorite& favorite) const;

	/**
	 * @brief Delete a favorite folder and its content recursively.
	 * @param folder The favorite folder to delete.
	 * @pre This function requires an opened NotUndoable command scope.
	 * @return Success if the delete is successful, otherwise an error.
	 */
	Result<void> DeleteFavoriteFolder (const ACAPI::Favorite::FavoriteFolder& folder) const;

	/**
	 * @brief Create a favorite with the given name and default.
	 * @param name The name of the favorite.
	 * @param folder The parent folder of the favorite.
	 * @param defaultElem The default of the favorite.
	 * @pre This function requires an opened NotUndoable command scope.
	 * @return The created favorite if the creation is successful, otherwise an error.
	 */
	Result<ACAPI::Favorite::Favorite> CreateFavorite (const GS::UniString& name,
													  const ACAPI::Favorite::FavoriteFolder& folder,
													  const ACAPI::ElementDefault& defaultElem) const;

	/**
	 * @brief Create a favorite with the given name and element as the default.
	 * @param name The name of the favorite.
	 * @param folder The parent folder of the favorite.
	 * @param element The element as the default of the favorite.
	 * @param subElements The subelements of the element if needed.
	 * @param memo The element memo of the element if needed.
	 * @param markerElement The marker element of the element if needed.
	 * @param markerMemo The element memo of the marker element if needed.
	 * @param properties The properties of the element.
	 * @param classifications The classifications of the element.
	 * @param elemCategoryValues The element category values of the element.
	 * @pre This function requires an opened NotUndoable command scope.
	 * @return The created favorite if the creation is successful, otherwise an error.
	 */
	Result<ACAPI::Favorite::Favorite> CreateFavorite (const GS::UniString&											  name,
													  const ACAPI::Favorite::FavoriteFolder&						  folder,
													  API_Element													  element,
													  const std::optional<std::vector<API_SubElement>>&				  subElements,
													  const std::optional<API_ElementMemo>&							  memo,
													  const std::optional<API_Element>&								  markerElement,
													  const std::optional<API_ElementMemo>&							  markerMemo,
													  const std::optional<std::vector<API_Property>>&				  properties,
													  const std::optional<std::vector<GS::Pair<API_Guid, API_Guid>>>& classifications,
													  const std::optional<std::vector<API_ElemCategoryValue>>&		  elemCategoryValues) const;

	/**
	 * @brief Change a favorite with the given default.
	 * @param favorite The favorite to change.
	 * @param defaultElem The new default of the favorite.
	 * @pre This function requires an opened NotUndoable command scope.
	 * @return Success if the change is successful, otherwise an error.
	 */
	Result<void> ChangeFavorite (const ACAPI::Favorite::Favorite& favorite, const ACAPI::ElementDefault& defaultElem) const;

	/**
	 * @brief Change a favorite with the given element and optional parameters.
	 * @param favorite The favorite to change.
	 * @param element The new element of the favorite.
	 * @param subElements The new subelements of the element if needed.
	 * @param memo The new element memo of the element if needed.
	 * @param markerElement The new marker element of the element if needed.
	 * @param markerMemo The new element memo of the marker element if needed.
	 * @param properties The new properties of the element.
	 * @param classifications The new classifications of the element.
	 * @param elemCategoryValues The new element category values of the element.
	 * @pre This function requires an opened NotUndoable command scope.
	 * @return Success if the change is successful, otherwise an error.
	 */
	Result<void> ChangeFavorite (const ACAPI::Favorite::Favorite&								 favorite,
								 API_Element													 element,
								 const std::optional<std::vector<API_SubElement>>&				 subElements,
								 const std::optional<API_ElementMemo>&							 memo,
								 const std::optional<API_Element>&								 markerElement,
								 const std::optional<API_ElementMemo>&							 markerMemo,
								 const std::optional<std::vector<API_Property>>&				 properties,
								 const std::optional<std::vector<GS::Pair<API_Guid, API_Guid>>>& classifications,
								 const std::optional<std::vector<API_ElemCategoryValue>>&		 elemCategoryValues) const;

	/**
	 * @brief Create a favorite folder with the given name.
	 * @param parent The parent folder of the new folder.
	 * @param name The name of the new folder.
	 * @pre This function requires an opened NotUndoable command scope.
	 * @return The created favorite folder if the creation is successful, otherwise an error.
	 */
	Result<ACAPI::Favorite::FavoriteFolder> CreateFolder (const ACAPI::Favorite::FavoriteFolder& parent, const GS::UniString& name) const;

	/**
	 * @brief Move a favorite to a new folder.
	 * @param favorite The favorite to move.
	 * @param targetFolder The target folder where the favorite will be moved.
	 * @pre This function requires an opened NotUndoable command scope.
	 * @return Success if the move is successful, otherwise an error.
	 */
	Result<void> MoveFavorite (const ACAPI::Favorite::Favorite& favorite, const ACAPI::Favorite::FavoriteFolder& targetFolder) const;
	
	/**
	 * @brief Move a favorite folder to a new folder.
	 * @param folder The folder to move.
	 * @param targetFolder The target folder where the folder will be moved.
	 * @pre This function requires an opened NotUndoable command scope.
	 * @return Success if the move is successful, otherwise an error.
	 */
	Result<void> MoveFolder (const ACAPI::Favorite::FavoriteFolder& folder, const ACAPI::Favorite::FavoriteFolder& targetFolder) const;

	/**
	 * @brief Rename a favorite.
	 * @param favorite The favorite to rename.
	 * @param newName The new name of the favorite.
	 * @pre This function requires an opened NotUndoable command scope.
	 * @return Success if the rename is successful, otherwise an error.
	 */
	Result<void> RenameFavorite (const ACAPI::Favorite::Favorite& favorite, const GS::UniString& newName) const;
	
	/**
	 * @brief Rename a favorite folder.
	 * @param folder The folder to rename.
	 * @param newName The new name of the folder.
	 * @pre This function requires an opened NotUndoable command scope.
	 * @return Success if the rename is successful, otherwise an error.
	 */
	Result<void> RenameFolder (const ACAPI::Favorite::FavoriteFolder& folder, const GS::UniString& newName) const;
};


/**
 * @brief Creates a Favorite Manager instance
 * @ingroup Favorite
 * @return FavoriteManager
 */
inline FavoriteManager GetFavoriteManager ()
{
	return FavoriteManager (ACAPI_GetToken ());
}


} // namespace Favorite
} // namespace ACAPI


#endif // FAVORITE_HPP