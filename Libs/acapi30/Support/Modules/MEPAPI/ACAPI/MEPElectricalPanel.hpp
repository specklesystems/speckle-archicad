#ifndef GS_ACAPI_MEP_ELECTRICAL_PANEL_HPP
#define GS_ACAPI_MEP_ELECTRICAL_PANEL_HPP

#include "MEPAPIExport.hpp"

#include "MEPModifiableElementBase.hpp"
#include "MEPElectricalPanelDefault.hpp"

#include <vector>
#include <optional>


namespace ACAPI::MEP {


/**
 * @brief The ElectricalPanel is an element that represents a distribution board.
 * @details An ElectricalPanel owns ElectricalCircuits as sub-elements. It can optionally be connected to a parent circuit.
 * @since Archicad 30
 * @ingroup MEP
 */
class MEPAPI_EXPORT ElectricalPanel final : public ModifiableElementBase {
	ElectricalPanel (const UniqueID&);

public:
	class Modifier;
	~ElectricalPanel ();

	/**
	 * @brief Returns an ElectricalPanel.
	 * @param uniqueId The UniqueID of the requested ElectricalPanel.
	 * @return If the uniqueId belongs to an ElectricalPanel, returns the object associated to it, otherwise Error.
	 */
	static Result<ElectricalPanel> Get (const UniqueID& uniqueId);

	/**
	 * @brief Picks up the Default from the ElectricalPanel.
	 * @return Returns an ElectricalPanelDefault with the parameters of the object it was called for.
	 */
	ElectricalPanelDefault PickUpDefault () const;

	/** @return Returns the name of the panel. */
	GS::UniString GetPanelName () const;

	/** @return Returns the circuit name prefix used when creating circuits under this panel. */
	GS::UniString GetCircuitNamePrefix () const;

	/** @return Returns the circuit id style index. */
	short GetCircuitIdStyle () const;

	/** @return Returns the UniqueIDs of the circuits owned by this panel. */
	std::vector<UniqueID> GetCircuitIds () const;

	/** @return Returns the UniqueID of the parent ElectricalCircuit, or std::nullopt if unassigned. */
	std::optional<UniqueID> GetParentCircuitId () const;

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
 * @brief Modifier of the ElectricalPanel.
 * @ingroup MEP
 */
class MEPAPI_EXPORT ElectricalPanel::Modifier : public ModifiableElementBase::Modifier {
	ElectricalPanel& parent;

	Modifier (ElectricalPanel&);
	virtual ~Modifier ();

	friend ElectricalPanel;
public:

	/**
	 * @brief Injects the Default settings into the ElectricalPanel.
	 * @param electricalPanelDefault The Default what will be injected.
	 * @return Returns an error if the injection fails for some reason, otherwise nothing.
	 */
	Result<void> Inject (const ElectricalPanelDefault& electricalPanelDefault);

	/**
	 * @brief Sets the panel name.
	 * @param panelName The name to set.
	 */
	void SetPanelName (const GS::UniString& panelName);

	/**
	 * @brief Sets the circuit name prefix.
	 * @param circuitNamePrefix The prefix to set.
	 */
	void SetCircuitNamePrefix (const GS::UniString& circuitNamePrefix);

	/**
	 * @brief Sets the circuit id style.
	 * @param circuitIdStyle The style index to set.
	 */
	void SetCircuitIdStyle (short circuitIdStyle);

	/**
	 * @brief Connects the panel to a circuit.
	 * @param circuitId The UniqueID of the ElectricalCircuit to connect to.
	 */
	void ConnectToCircuit (const UniqueID& circuitId);

	/**
	 * @brief Adds a new circuit to the panel.
	 * @return Returns the UniqueID of the newly created circuit, or Error.
	 */
	Result<UniqueID> AddCircuit ();

	/**
	 * @brief Removes a circuit from the panel.
	 * @param circuitId The UniqueID of the circuit to remove.
	 * @return Returns an error if the circuit cannot be removed, otherwise nothing.
	 */
	Result<void> RemoveCircuit (const UniqueID& circuitId);
};


template <typename ModifierFunc>
Result<void> ElectricalPanel::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}

} // ACAPI::MEP


#endif /* GS_ACAPI_MEP_ELECTRICAL_PANEL_HPP */
