#ifndef GS_ACAPI_MEP_PIPING_PORT_DEFAULT_HPP
#define GS_ACAPI_MEP_PIPING_PORT_DEFAULT_HPP

#include "MEPPortDefaultBase.hpp"


namespace ACAPI::Impl { class ObjectCreator; }

namespace ACAPI::MEP {

namespace Impl { class IPipingPortDefaultImpl; }

namespace v1 {

/**
 * @brief Through this PipingPortDefault you can access and configure the PipingPorts of MEPElementDefaults before placement.
 * @since Archicad 28
 * @ingroup MEP
 * @par Example code snippet from Test / New MEP
 * 		Take a look at @ref PortDefaultBase "PortDefaultBase"
 */
class MEPAPI_EXPORT PipingPortDefault final : public PortDefaultBase {
	/**
	 * @brief Constructs a PipingPortDefault with the given PipingPortDefault implementation.
	 * @param impl The PipingPortDefault implementation.
	 */
	PipingPortDefault (std::shared_ptr<Impl::IPipingPortDefaultImpl> impl);
	friend class ACAPI::Impl::ObjectCreator;

public:
	class Modifier;

	/** @return Returns the diameter of the PipingPort. */
	double GetDiameter () const;

	/** @return Returns the wall thickness of the PipingPort. */
	double GetWallThickness () const;

	/** @return Returns the flow direction of the PipingPort. */
	FlowDirection GetFlowDirection () const;

	/**
	 * @brief Executes the given modifier scope in a NotUndoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template<class ModifierFunc>
	Result<void> Modify (ModifierFunc&& modifierFunc);
};


class MEPAPI_EXPORT PipingPortDefault::Modifier : public PortDefaultBase::Modifier {
	PipingPortDefault& parent;
protected:
	/**
	 * @brief Constructs a Modifier with the given PipingPortDefault parent.
	 * @param parent The parent PipingPortDefault.
	 */
	Modifier (PipingPortDefault& parent);

public:
	~Modifier ();

	friend PipingPortDefault;

	/**
	 * @brief Sets the diameter of the PipingPort.
	 * @param diameter The value to be set.
	 */
	void SetDiameter (double diameter);

	/**
	 * @brief Sets the thickness of the PipingPort's wall.
	 * @param thickness The value to be set.
	 */
	void SetWallThickness (double thickness);

	/**
	 * @brief Sets the flow direction of the PipingPort.
	 * @param flowDirection The value to be set.
	 */
	void SetFlowDirection (FlowDirection flowDirection);
};


template <typename ModifierFunc>
Result<void> PipingPortDefault::Modify (ModifierFunc&& modifierFunc)
{
	Modifier modifier (*this);
	return CallDefaultModifier (modifierFunc, modifier);
}


} // v1

using v1::PipingPortDefault;

} // ACAPI::MEP


#endif // GS_ACAPI_MEP_PIPING_PORT_DEFAULT_HPP