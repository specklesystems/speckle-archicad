#ifndef GS_ACAPI_MEP_VENTILATION_PORT_DEFAULT_HPP
#define GS_ACAPI_MEP_VENTILATION_PORT_DEFAULT_HPP

#include "MEPPortDefaultBase.hpp"


namespace ACAPI::Impl { class ObjectCreator; }

namespace ACAPI::MEP {

namespace Impl { class IVentilationPortDefaultImpl; }

namespace v1 {

/**
 * @brief Through this VentilationPortDefault you can access and configure the VentilationPorts of MEPElementDefaults before placement.
 * @since Archicad 28
 * @ingroup MEP
 * @par Example code snippet from Test / New MEP
 * 		Take a look at @ref PortDefaultBase "PortDefaultBase"
 */
class MEPAPI_EXPORT VentilationPortDefault final : public PortDefaultBase {
	/**
	 * @brief Constructs a VentilationPortDefault with the given VentilationPortDefault implementation.
	 * @param impl The VentilationPortDefault implementation.
	 */
	VentilationPortDefault (std::shared_ptr<Impl::IVentilationPortDefaultImpl> impl);
	friend class ACAPI::Impl::ObjectCreator;

public:
	class Modifier;

	/** @return Returns the height of the VentilationPort. */
	double GetHeight () const;

	/** @return Returns the wall thickness of the VentilationPort. */
	double GetWallThickness () const;

	/** @return Returns the flow direction of the VentilationPort. */
	FlowDirection GetFlowDirection () const;

	/**
	 * @brief Executes the given modifier scope in a NotUndoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template<class ModifierFunc>
	Result<void> Modify (ModifierFunc&& modifierFunc);
};


class MEPAPI_EXPORT VentilationPortDefault::Modifier : public PortDefaultBase::Modifier {
	VentilationPortDefault& parent;
protected:
	/**
	 * @brief Constructs a Modifier with the given VentilationPortDefault parent.
	 * @param parent The parent VentilationPortDefault.
	 */
	Modifier (VentilationPortDefault& parent);

public:
	~Modifier ();

	friend VentilationPortDefault;

	/**
	 * @brief Sets the height of the VentilationPort.
	 * @param height The value to be set.
	 */
	void SetHeight (double height);

	/**
	 * @brief Sets the thickness of the VentilationPort's wall.
	 * @param thickness The value to be set.
	 */
	void SetWallThickness (double thickness);

	/**
	 * @brief Sets the flow direction of the VentilationPort.
	 * @param flowDirection The value to be set.
	 */
	void SetFlowDirection (FlowDirection flowDirection);
};


template <typename ModifierFunc>
Result<void> VentilationPortDefault::Modify (ModifierFunc&& modifierFunc)
{
	Modifier modifier (*this);
	return CallDefaultModifier (modifierFunc, modifier);
}


} // v1

using v1::VentilationPortDefault;

} // ACAPI::MEP


#endif // GS_ACAPI_MEP_VENTILATION_PORT_DEFAULT_HPP