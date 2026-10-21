#ifndef GS_ACAPI_MEP_ELECTRICAL_PROJECT_SETTINGS_HPP
#define GS_ACAPI_MEP_ELECTRICAL_PROJECT_SETTINGS_HPP

#include "MEPAPIExport.hpp"
#include "MEPTypes.hpp"

// ACAPI
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/ModifyScope.hpp"

#include <memory>
#include <vector>


namespace ACAPI::MEP {

namespace Impl { class IElectricalProjectSettingsImpl; }


/**
 * @brief ElectricalProjectSettings holds the project-level electrical configuration:
 *        load classification descriptions, wiring type descriptions, and default voltage.
 * @details This object is a singleton per project. Use @ref GetElectricalProjectSettings to retrieve it.
 *          It provides read access to the defined load classifications and wiring types, which are
 *          referenced by @ref ElectricalDevice and @ref ElectricalCircuit respectively.
 * @since Archicad 30
 * @ingroup MEP
 */
class MEPAPI_EXPORT ElectricalProjectSettings final : public Object {
private:
    ElectricalProjectSettings (std::shared_ptr<Impl::IElectricalProjectSettingsImpl> impl);

    const Impl::IElectricalProjectSettingsImpl& GetImpl () const;
    Impl::IElectricalProjectSettingsImpl& GetImpl ();

public:
    class Modifier;
    ~ElectricalProjectSettings ();

    /**
     * @brief Returns the ElectricalProjectSettings for the current project.
     * @param token The API token of the calling add-on.
     * @return If the MEP plugin is loaded, returns the project settings object, otherwise Error.
     */
    static Result<ElectricalProjectSettings> Get (const API_Token& token);

    /**
     * @brief Checks whether the settings are editable.
     * @return Returns nothing if the settings are editable, otherwise the error code and error message containing information about the reason.
     */
    Result<void> IsEditable () const;

    // ---------------------------------
    // Voltage
    // ---------------------------------

    /** @return Returns the default project voltage. */
    double GetVoltage () const;

    // ---------------------------------
    // Load Classification Descriptions
    // ---------------------------------

    /** @return Returns the names of all defined load classifications. */
    std::vector<GS::UniString> GetLoadClassificationNames () const;

    /**
     * @brief Returns the demand factor for a load classification by name.
     * @param name The name of the load classification.
     * @return The demand factor, or 0.0 if not found.
     */
    double GetLoadClassificationDemandFactor (const GS::UniString& name) const;

    // ---------------------------------
    // Wiring Type Descriptions
    // ---------------------------------

    /** @return Returns the names of all defined wiring types. */
    std::vector<GS::UniString> GetWiringTypeNames () const;

    /**
     * @brief Returns the cross-sectional area for a wiring type by name.
     * @param name The name of the wiring type.
     * @return The cross-sectional area (mm²), or 0.0 if not found.
     */
    double GetWiringTypeCrossSectionalArea (const GS::UniString& name) const;

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
 * @brief Modifier of the ElectricalProjectSettings.
 * @ingroup MEP
 */
class MEPAPI_EXPORT ElectricalProjectSettings::Modifier : public ACAPI::ModifierBase {
private:
    friend class ElectricalProjectSettings;

    ElectricalProjectSettings& parent;
    Modifier (ElectricalProjectSettings& parent);

public:
    virtual ~Modifier ();

    /**
     * @brief Sets the default project voltage.
     * @param voltage The voltage value to set.
     */
    void SetVoltage (double voltage);

    /**
     * @brief Adds a new load classification description.
     * @param name The name of the load classification.
     * @param demandFactor The demand factor (0.0 – 1.0).
     */
    void AddLoadClassification (const GS::UniString& name, double demandFactor);

    /**
     * @brief Removes a load classification description by name.
     * @param name The name of the load classification to remove.
     * @return Returns an error if no classification with that name exists, otherwise nothing.
     */
    Result<void> RemoveLoadClassification (const GS::UniString& name);

    /** @brief Removes all load classification descriptions. */
    void ClearLoadClassifications ();

    /**
     * @brief Adds a new wiring type description.
     * @param name The name of the wiring type.
     * @param crossSectionalArea The cross-sectional area (mm²).
     */
    void AddWiringType (const GS::UniString& name, double crossSectionalArea);

    /**
     * @brief Removes a wiring type description by name.
     * @param name The name of the wiring type to remove.
     * @return Returns an error if no wiring type with that name exists, otherwise nothing.
     */
    Result<void> RemoveWiringType (const GS::UniString& name);

    /** @brief Removes all wiring type descriptions. */
    void ClearWiringTypes ();
};


template <typename ModifierFunc>
Result<void> ElectricalProjectSettings::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
    Result<void> editableResult = IsEditable ();
    if (editableResult.IsErr ())
        return editableResult;

    Modifier modifier (*this);
    return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}


/**
 * @brief Returns the ElectricalProjectSettings for the current project.
 * @param token The API token of the calling add-on.
 * @ingroup MEP
 * @return If the MEP plugin is loaded, returns the project settings object, otherwise Error.
 */
MEPAPI_EXPORT Result<ElectricalProjectSettings> GetElectricalProjectSettings (const API_Token& token);


} // ACAPI::MEP


#endif /* GS_ACAPI_MEP_ELECTRICAL_PROJECT_SETTINGS_HPP */
