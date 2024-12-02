#ifndef GS_ACAPI_MEP_CABLECARRIER_PORT_DEFAULT_HPP
#define GS_ACAPI_MEP_CABLECARRIER_PORT_DEFAULT_HPP

#include "MEPPortDefaultBase.hpp"


namespace ACAPI::Impl { class ObjectCreator; }

namespace ACAPI::MEP {

namespace Impl { class ICableCarrierPortDefaultImpl; }

namespace v1 {

/**
 * @brief Through this CableCarrierPortDefault you can access and configure the CableCarrierPorts of MEPElementDefaults before placement.
 * @since Archicad 28
 * @ingroup MEP
 * @par Example code snippet from Test / New MEP
 * 		Take a look at @ref PortDefaultBase "PortDefaultBase"
 */
class MEPAPI_EXPORT CableCarrierPortDefault final : public PortDefaultBase {
	/**
	 * @brief Constructs a CableCarrierPortDefault with the given CableCarrierPortDefault implementation.
	 * @param impl The CableCarrierPortDefault implementation.
	 */
	CableCarrierPortDefault (std::shared_ptr<Impl::ICableCarrierPortDefaultImpl> impl);
	friend class ACAPI::Impl::ObjectCreator;

public:
	class Modifier;

	/** @return Returns the height of the CableCarrierPort. */
	double GetHeight () const;

	/**
	 * @brief Executes the given modifier scope in a NotUndoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template<class ModifierFunc>
	Result<void> Modify (ModifierFunc&& modifierFunc);
};


class MEPAPI_EXPORT CableCarrierPortDefault::Modifier : public PortDefaultBase::Modifier {
	CableCarrierPortDefault& parent;
protected:
	/**
	 * @brief Constructs a Modifier with the given CableCarrierPortDefault parent.
	 * @param parent The parent CableCarrierPortDefault.
	 */
	Modifier (CableCarrierPortDefault& parent);

public:
	~Modifier ();

	friend CableCarrierPortDefault;

	/**
	 * @brief Sets the height of the CableCarrierPort.
	 * @param height The value to be set.
	 */
	void SetHeight (double height);
};


template <typename ModifierFunc>
Result<void> CableCarrierPortDefault::Modify (ModifierFunc&& modifierFunc)
{
	Modifier modifier (*this);
	return CallDefaultModifier (modifierFunc, modifier);
}


} // v1

using v1::CableCarrierPortDefault;

} // ACAPI::MEP


#endif // GS_ACAPI_MEP_CABLECARRIER_PORT_DEFAULT_HPP