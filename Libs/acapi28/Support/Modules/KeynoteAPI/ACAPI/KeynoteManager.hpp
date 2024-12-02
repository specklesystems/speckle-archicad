#ifndef GS_ACAPI_KEYNOTEMANAGER_HPP
#define GS_ACAPI_KEYNOTEMANAGER_HPP

#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "KeynoteAPIExport.hpp"
#include "KeynoteFolder.hpp"
#include <vector>


namespace ACAPI {
namespace Keynote {
	
//! @cond Doxygen_Suppress
namespace v1 {
class KeynoteManager;
inline Result<KeynoteManager> CreateKeynoteManager ();
}
//! @endcond


namespace v1 {

/**
 * @brief A class that contains keynote related functions.
 * @since Archicad 28
 * @ingroup Keynote
 */
class KEYNOTEAPI_DLL_EXPORT KeynoteManager : public Object {
	friend Result<KeynoteManager> CreateKeynoteManager ();

public:

	/**
	 * @returns The root folder object of the keynote tree.
	 * @par Example code snippets from Test / Keynote
	 * 		@snippet Keynote_Test.cpp Get-Root-Folder-Example
	 */
	Result<KeynoteFolder>	GetRootFolder () const;

	/**
	 * @brief Part of the keynote, an autotext should refer to.
	 * @enum AutoTextTokenSelector
	 * @ingroup Keynote
	 */
	enum class AutoTextTokenSelector {
		Key,
		Title,
		Description,
		Reference,
	};

	/**
	 * @returns Token, that an autotext label can interpret as a field of the given keynote.
	 * @param keynoteItemId The ID of the referred keynote item.
	 * @param tokenSelector The selector specifies, which part of the keynote item should be referred.
	 * @par Example code snippets from Test / Keynote
	 * 		@snippet Keynote_Test.cpp Get-Autotext-Label-Content-From-Keynote
	 */
	Result<GS::UniString>	GetAutoTextTokenFor (const API_Guid& keynoteItemId, AutoTextTokenSelector tokenSelector) const;


private:
	explicit KeynoteManager (const API_Token& token);
	static Result<KeynoteManager> Create (const API_Token& token);
};


/**
 * @brief A function to create keynote manager instance, that lets you query and manipulate keynote related data.
 * @ingroup Keynote
 * @return The keynote manager instance.
 */
inline Result<KeynoteManager> CreateKeynoteManager ()
{
	return KeynoteManager::Create (ACAPI_GetToken ());
}


} // namespace v1


using namespace v1;

} // namespace Keynote
} // namespace ACAPI


#endif
