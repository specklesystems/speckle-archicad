#ifndef ACAPI_KEYNOTEITEM_HPP
#define ACAPI_KEYNOTEITEM_HPP

#include "UniString.hpp"
#include "API_Guid.hpp"
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "KeynoteAPIExport.hpp"

namespace ACAPI {
	
namespace Impl {
class KeynoteItemImpl;
class KeynoteFolderImpl;
} // namespace Impl

namespace Keynote {

namespace v1 {

using Reference = GS::UniString;
using ItemKey = GS::UniString;
using Title = GS::UniString;
using Description = GS::UniString;

/**
 * @brief A class that represents an item in the keynote tree structure.
 * @since Archicad 28
 * @ingroup Keynote
 */
class KEYNOTEAPI_DLL_EXPORT KeynoteItem : public Object {
	friend class Impl::KeynoteFolderImpl;
	friend class KeynoteFolder;

public:
	/** @returns The database Id of the item */
	API_Guid 							GetId () const;

	/** @returns The key of the item */
	ItemKey								GetKey () const;

	/**
	 * @brief Modifies the Key of the item
	 * @param newKey The key to be set
	 * @returns The result of the modification
	 * 			@snippet Keynote_Test.cpp Modify-Item-Example
	 */
	Result<void>						SetKey (const ItemKey& newKey);

	/** @returns The title of the item */
	Title								GetTitle () const;
	
	/**
	 * @brief Modifies the Title of the item
	 * @param newTitle The Title to be set
	 * @returns The result of the modification
	 * 			@snippet Keynote_Test.cpp Modify-Item-Example
	 */
	Result<void>						SetTitle (const Title& newTitle);
	
	/** @returns The description of the item */
	Description							GetDescription () const;
	
	/**
	 * @brief Modifies the Description of the item
	 * @param newDescription The Description to be set
	 * @returns The result of the modification
	 * 			@snippet Keynote_Test.cpp Modify-Item-Example
	 */
	Result<void>						SetDescription (const Description& newDescription);

	/** @returns The reference of the item */
	Reference							GetReference () const;
	
	/**
	 * @brief Modifies the Reference of the item
	 * @param newReference The Reference to be set
	 * @returns The result of the modification
	 * 			@snippet Keynote_Test.cpp Modify-Item-Example
	 */
	Result<void>						SetReference (const Reference& newReference);

	/** @returns The text representation of the item, used on UI elements */
	GS::UniString						GetUIText () const;

private:
	explicit KeynoteItem (std::shared_ptr<Impl::KeynoteItemImpl> impl);
};

} // namespace v1


using namespace v1;

} // namespace Keynote
} // namespace ACAPI


#endif /* ACAPI_KEYNOTEITEM_HPP */
