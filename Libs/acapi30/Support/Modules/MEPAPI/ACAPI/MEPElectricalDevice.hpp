#ifndef GS_ACAPI_MEP_ELECTRICAL_DEVICE_HPP
#define GS_ACAPI_MEP_ELECTRICAL_DEVICE_HPP

#include "MEPAPIExport.hpp"

#include "MEPModifiableElementBase.hpp"
#include "MEPElectricalDeviceDefault.hpp"


namespace ACAPI::MEP {


/**
 * @brief The ElectricalDevice is an element that represents an electrical consumer (e.g. lamp, socket).
 * @since Archicad 30
 * @ingroup MEP
 */
class MEPAPI_EXPORT ElectricalDevice final : public ModifiableElementBase {
	ElectricalDevice (const UniqueID&);

public:
	class Modifier;
	~ElectricalDevice ();

	/**
	 * @brief Returns an ElectricalDevice.
	 * @param uniqueId The UniqueID of the requested ElectricalDevice.
	 * @return If the uniqueId belongs to an ElectricalDevice, returns the object associated to it, otherwise Error.
	 */
	static Result<ElectricalDevice> Get (const UniqueID& uniqueId);

	/**
	 * @brief Picks up the Default from the ElectricalDevice.
	 * @return Returns an ElectricalDeviceDefault with the parameters of the object it was called for.
	 */
	ElectricalDeviceDefault PickUpDefault () const;

	/** @return Returns the load classification name of the device. */
	GS::UniString GetLoadClassificationName () const;

	/** @return Returns the apparent power of the device in VA. */
	uint32_t GetApparentPower () const;

	/** @return Returns whether the apparent power is enabled for this device. */
	bool GetApparentPowerEnabled () const;

	/** @return Returns the demand load of the device. */
	double GetDemandLoad () const;

	/** @return Returns the UniqueID of the parent ElectricalCircuit, or std::nullopt if unassigned. */
	std::optional<UniqueID> GetParentCircuitId () const;

	/**
	 * @brief Executes the passed modifier scope in an Undoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @param undoString The text which appears in the undo queue of Archicad after executing the command.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template <typename ModifierFunc>
	Result<void> Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString);
};


/**
 * @brief Modifier of the ElectricalDevice.
 * @ingroup MEP
 */
class MEPAPI_EXPORT ElectricalDevice::Modifier : public ModifiableElementBase::Modifier {
	ElectricalDevice& parent;

	Modifier (ElectricalDevice&);
	virtual ~Modifier ();

	friend ElectricalDevice;
public:

	/**
	 * @brief Injects the Default settings into the ElectricalDevice.
	 * @param electricalDeviceDefault The Default what will be injected.
	 * @return Returns an error if the injection fails for some reason, otherwise nothing.
	 */
	Result<void> Inject (const ElectricalDeviceDefault& electricalDeviceDefault);

	/**
	 * @brief Sets the load classification name of the device.
	 * @param name The load classification name to set.
	 */
	void SetLoadClassificationName (const GS::UniString& name);

	/**
	 * @brief Sets the apparent power of the device in VA.
	 * @param apparentPower The apparent power value to set.
	 */
	void SetApparentPower (uint32_t apparentPower);

	/**
	 * @brief Sets whether the apparent power is enabled for this device.
	 * @param enabled True to enable, false to disable.
	 */
	void SetApparentPowerEnabled (bool enabled);

	/**
	 * @brief Connects the device to a circuit.
	 * @param circuitId The UniqueID of the ElectricalCircuit to connect to.
	 */
	void ConnectToCircuit (const UniqueID& circuitId);
};


template <typename ModifierFunc>
Result<void> ElectricalDevice::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}

} // ACAPI::MEP


#endif /* GS_ACAPI_MEP_ELECTRICAL_DEVICE_HPP */
