#ifndef ACAPI__LM_LIBPART_HPP
#define ACAPI__LM_LIBPART_HPP

#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/ArchicadAPIExport.hpp"

namespace ACAPI {
namespace Library {

namespace Impl { class LibPartImpl; }
namespace Impl { class LibraryManagerImpl; }

namespace v1 {

/**
 * @brief File type of a library part
 * @ingroup LibraryManagement
 * @details Values can be: Object, Image, Text, BinaryListCrit, Other
 */
enum class LibPartType {
	Object,
	Image,
	Text,
	BinaryListCrit,
	Other
};


/**
 * @brief LibPart is the representation of a file-like item in a Library (.gsm, .png, .lis, etc..)
 * @ingroup LibraryManagement
 * @since Archicad 28
 */
class ARCHICADAPI_EXPORT LibPart : public Object
{
	friend class Impl::LibraryManagerImpl;

private:
	explicit LibPart (std::shared_ptr<Impl::LibPartImpl> libPartImpl);
	bool IsValid () const;

public:
	/**
	 * @brief The name of the library part.
	 * @details The name is the (localized) name of the library part with file extension which is displayed in the Library Manager dialog.
	 * @ingroup LibraryManagement
	 * @return Returns the name if the library part is valid, otherwise error.
	 */
	ACAPI::Result<GS::UniString> GetName () const;

	/**
	 * @brief The location of the library part file.
	 * @remarks The most cases this is not the same as the LibraryTreePath of the library part.
	 * 			If you need the structure which is displayed in the Library Manager dialog, use the GetLibraryTreePathOfLibPart method of LibraryManager.
	 * @ingroup LibraryManagement
	 * @return Returns the (physical) location of the library part file if the library part is valid, otherwise error.
	 */
	ACAPI::Result<IO::Location> GetLocation () const;

	/**
	 * @brief The file type of the library part.
	 * @ingroup LibraryManagement
	 * @return Returns the file type of the library part if the library part is valid, otherwise error.
	 */
	ACAPI::Result<LibPartType> GetType () const;
};

}  // namespace v1
using namespace v1;

}  // namespace Library
}  // namespace ACAPI

#endif
