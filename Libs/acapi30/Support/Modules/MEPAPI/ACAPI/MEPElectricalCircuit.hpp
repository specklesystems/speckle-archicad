#ifndef GS_ACAPI_MEP_ELECTRICAL_CIRCUIT_HPP
#define GS_ACAPI_MEP_ELECTRICAL_CIRCUIT_HPP

#include "MEPAPIExport.hpp"
#include "MEPUniqueID.hpp"

#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/ModifyScope.hpp"

#include <vector>
#include <optional>
#include <memory>


namespace ACAPI::Impl { class ObjectCreator; }

namespace ACAPI::MEP {

namespace Impl { class IElectricalCircuitImpl; }


/**
 * @brief The ElectricalCircuit is a sub-element owned by an ElectricalPanel.
 * @details It groups ElectricalDevices and optionally child ElectricalPanels. It is not independently placeable.
 * @since Archicad 30
 * @ingroup MEP
 */
class MEPAPI_EXPORT ElectricalCircuit final : public Object {
private:
	friend class ACAPI::Impl::ObjectCreator;

	ElectricalCircuit (std::shared_ptr<Impl::IElectricalCircuitImpl> impl);

	const Impl::IElectricalCircuitImpl& GetImpl () const;
	Impl::IElectricalCircuitImpl& GetImpl ();

public:
	class Modifier;
	~ElectricalCircuit ();

	/**
	 * @brief Returns an ElectricalCircuit.
	 * @param uniqueId The UniqueID of the requested ElectricalCircuit.
	 * @return If the uniqueId belongs to an ElectricalCircuit, returns the object associated to it, otherwise Error.
	 */
	static Result<ElectricalCircuit> Get (const UniqueID& uniqueId);

	/** @return Returns the circuit description. */
	GS::UniString GetCircuitDescription () const;

	/** @return Returns the circuit name including the prefix from the owner panel. */
	GS::UniString GetCircuitNameWithPrefix () const;

	/** @return Returns the wiring type name. */
	GS::UniString GetWiringTypeName () const;

	/** @return Returns the phase usage as a human-readable string. */
	GS::UniString GetPhaseString () const;

	/** @return Returns true if Phase A is used. */
	bool IsPhaseAUsed () const;

	/** @return Returns true if Phase B is used. */
	bool IsPhaseBUsed () const;

	/** @return Returns true if Phase C is used. */
	bool IsPhaseCUsed () const;

	/** @return Returns the UniqueID of the owner ElectricalPanel. */
	UniqueID GetOwnerPanelId () const;

	/** @return Returns the UniqueIDs of the child ElectricalDevices. */
	std::vector<UniqueID> GetChildDeviceIds () const;

	/** @return Returns the UniqueIDs of the child ElectricalPanels. */
	std::vector<UniqueID> GetChildPanelIds () const;

	/** @return Returns the total connected load. */
	double GetConnectedLoad () const;

	/** @return Returns the total demand load. */
	double GetDemandLoad () const;

	/** @return Returns the connected load on Phase A. */
	double GetConnectedLoadPhaseA () const;

	/** @return Returns the connected load on Phase B. */
	double GetConnectedLoadPhaseB () const;

	/** @return Returns the connected load on Phase C. */
	double GetConnectedLoadPhaseC () const;

	/** @return Returns the demand load on Phase A. */
	double GetDemandLoadPhaseA () const;

	/** @return Returns the demand load on Phase B. */
	double GetDemandLoadPhaseB () const;

	/** @return Returns the demand load on Phase C. */
	double GetDemandLoadPhaseC () const;

	/** @return Returns the estimated cable length. */
	double GetEstimatedCableLength () const;

	/** @return Returns the voltage drop. */
	double GetVoltageDrop () const;

	/** @return Returns the voltage. */
	double GetVoltage () const;

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
 * @brief Modifier of the ElectricalCircuit.
 * @ingroup MEP
 */
class MEPAPI_EXPORT ElectricalCircuit::Modifier : public ACAPI::ModifierBase {
private:
	friend class ElectricalCircuit;

	ElectricalCircuit& parent;
	Modifier (ElectricalCircuit& parent);

public:
	virtual ~Modifier ();

	/**
	 * @brief Sets the circuit description.
	 * @param description The description to set.
	 */
	void SetCircuitDescription (const GS::UniString& description);

	/**
	 * @brief Sets the wiring type name.
	 * @param wiringTypeName The wiring type name to set.
	 */
	void SetWiringTypeName (const GS::UniString& wiringTypeName);

	/**
	 * @brief Sets whether Phase A is used.
	 * @param isUsed True if Phase A is used.
	 */
	void SetIsPhaseAUsed (bool isUsed);

	/**
	 * @brief Sets whether Phase B is used.
	 * @param isUsed True if Phase B is used.
	 */
	void SetIsPhaseBUsed (bool isUsed);

	/**
	 * @brief Sets whether Phase C is used.
	 * @param isUsed True if Phase C is used.
	 */
	void SetIsPhaseCUsed (bool isUsed);

	/**
	 * @brief Sets the voltage of the circuit.
	 * @param voltage The voltage value to set.
	 */
	void SetVoltage (double voltage);
};


template <typename ModifierFunc>
Result<void> ElectricalCircuit::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}

} // ACAPI::MEP


#endif /* GS_ACAPI_MEP_ELECTRICAL_CIRCUIT_HPP */
