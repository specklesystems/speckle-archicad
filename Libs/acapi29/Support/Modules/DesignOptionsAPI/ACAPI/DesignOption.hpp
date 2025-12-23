#ifndef GS_ACAPI_DESIGNOPTION_HPP
#define GS_ACAPI_DESIGNOPTION_HPP

#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "DesignOptionAPIExport.hpp"

namespace ACAPI {

namespace Impl {
class DesignOptionImpl;
class DesignOptionManagerImpl;
} // namespace Impl

namespace DesignOptions {

/**
 * @brief A class that represents the design option.
 * @since Archicad 29
 * @ingroup DesignOptions
 */
class DESIGNOPTIONAPI_EXPORT DesignOption : public Object {
    friend class DesignOptionManager;
	friend class Impl::DesignOptionManagerImpl;

public:

	/**
	 * @brief Checks whether the Design Option is editable
	 * @returns Ok if editable. Otherwise Error, with the reason why the option is not editable.
	 */
	Result<void> IsEditable () const;

    /** @returns The name of the design option. */
    GS::UniString GetName () const;

    /** @returns The id of the design option. */
    GS::UniString GetId () const;

    /** @returns The guid of the design option. */
    GS::Guid GetGuid () const;

	/** @returns The name of the owner design option set. */
	GS::UniString GetOwnerSetName () const;

	/**
	* @brief Sets the name of the Design Option.
	* @returns Result of the modification.
	* @param newName The new name to be set.
	* @pre This call needs undo scope. The object set should be modifiable.
	* @par Example code snippets from Test / Design Options
	*		@snippet DesignOptions_Test.cpp Modify-Design-Options-Name-Example
	*/
	Result<void> SetName (const GS::UniString & newName);

	/**
	 * @brief Sets the id of the Design Option.
	 * @returns Result of the modification.
	 * @param newId The new id to be set.
	 * @pre This call needs undo scope. The object set should be modifiable.
	 * @par Example code snippets from Test / Design Options
	 *		@snippet DesignOptions_Test.cpp Modify-Design-Options-Id-Example
	 */
	Result<void> SetId (const GS::UniString & newId);

private:
    explicit DesignOption (std::shared_ptr<Impl::DesignOptionImpl> impl);
};

} // namespace DesignOptions

} // namespace ACAPI


#endif  /* ACAPI_DESIGNOPTION_HPP */