#ifndef GS_ACAPI_MEP_SYSTEMBROWSERCALCULATIONCALLBACKINTERFACE_HPP
#define GS_ACAPI_MEP_SYSTEMBROWSERCALCULATIONCALLBACKINTERFACE_HPP

#include "MEPAPIExport.hpp"
#include "MEPEnums.hpp"

// ACAPI
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/AddonServiceInterface.hpp"

#include <vector>
#include <set>
#include <any>
#include <optional>


namespace ACAPI::MEP {


namespace Impl {
class ISystemBrowserCalculationCallbackInterfaceImpl;
}

class DistributionSystemsGraph;

/**
 * @brief Formatting for calculated values for use in ACAPI::MEP::SystemBrowserCalculationCallbackInterface::RegisterCalculatedColumns.
 * @since Archicad 29
 * @ingroup MEP
 * @see ACAPI::MEP::SystemBrowserCalculationCallbackInterface
 */
class MEPAPI_EXPORT ICalculationResultColumn
{
public:
	/**
	 * @brief Destructor.
	 */
	virtual ~ICalculationResultColumn ();
	
	/**
	 * @brief Globally unique ID for this column.
	 * @return The identifier for this column
	 * @remark This is only a technical ID, it won't be displayed anywhere on the GUI.
	 */
	virtual GS::UniString	GetId				() const = 0;
	
	/**
	 * @brief Starting width of the column to present the calculated data.
	 * @return The starting width of this column
	 */
	virtual GS::Int32		GetDefaultWidth		() const = 0;
	
	/**
	 * @brief Header title for this column without the unit.
	 * @return The displayable header title for this column
	 * @remark This is what will be displayed on the GUI (should be localized if possible). The actual header text will be a combination of this and the unit in the following format: "<title> [<unit>]"
	 */
	virtual GS::UniString	GetTitle			() const = 0;
	
	/**
	 * @brief Unit to display in the column's header title.
	 * @return The displayable header title for this column
	 * @remark This is what will be displayed on the GUI (should be localized if possible).
	 */
	virtual std::optional<GS::UniString>	GetUnitToDisplay		() const = 0;
	
	/**
	 * @brief Formats the value to a displayable text.
	 * @param value The value to format into a displayable text
	 * @return The displayable text
	 */
	virtual GS::UniString	FormatValueToDisplayText		(const std::any& value) const = 0;
	
	/**
	 * @brief True if value1 < value2.
	 * @param value1 first value that is checked if it is less than the second value
	 * @param value2 second value
	 * @return True if value1 is less than value2
	 */
	virtual bool			IsLess				(const std::any& value1, const std::any& value2) const = 0;
	
	/**
	 * @brief True if value1 = value2.
	 * @param value1 first value that is checked if it equals to the second value
	 * @param value2 second value
	 * @return True if value1 equals to value2
	 */
	virtual bool			IsEqual				(const std::any& value1, const std::any& value2) const = 0;

	/**
	 * @brief The domain of the column.
	 * @return The domain(s) of the column
	 */
	virtual std::set<ACAPI::MEP::Domain> GetDomain () const = 0;
};
 
 
/**
 * @brief Template typed version of the ICalculationResultColumn interface.
 * @since Archicad 28
 * @ingroup MEP
 * 
 * @snippet SystemBrowserCalculationCallbackInterface.cpp TypedCalculationResultColumn_Example
 */
template<typename T>
class TypedCalculationResultColumn : public ICalculationResultColumn {
public:

	/**
	 * @brief True if value1 < value2.
	 * @param value1 first value that is checked if it is less than the second value
	 * @param value2 second value
	 * @return True if value1 is less than value2
	 */
	virtual bool	IsLess	(const std::any& value1, const std::any& value2) const override
	{
		return std::any_cast<T> (value1) < std::any_cast<T> (value2);
	}
	
	/**
	 * @brief True if value1 = value2.
	 * @param value1 first value that is checked if it equals to the second value
	 * @param value2 second value
	 * @return True if value1 equals to value2
	 */
	virtual bool	IsEqual	(const std::any& value1, const std::any& value2) const override
	{
		return std::any_cast<T> (value1) == std::any_cast<T> (value2);
	}

	/**
	* @brief The domain(s) of the column.
	* @return The domain(s) of the column
	*/
	virtual std::set<ACAPI::MEP::Domain> GetDomain () const override
	{
		return {ACAPI::MEP::Domain::Ventilation};
	}

protected:
 
	/**
	 * @brief Formats the value to a displayable text.
	 * @param value The typed value to format into a displayable text
	 * @return The displayable text
	 */
	virtual GS::UniString  FormatValueToDisplayText (const T& value) const = 0;
 
private:
 
	/**
	 * @brief Formats the value to a displayable text.
	 * @param value The value to format into a displayable text
	 * @return The displayable text
	 */
	GS::UniString  FormatValueToDisplayText (const std::any& value) const override
	{
		return this->FormatValueToDisplayText (std::any_cast<T> (value));
	}
};


/**
 * @brief Interface for handling calculated columns in the system browser.
 * @details You can implement this interface in your add-on to provide custom columns in the system browser
 * that gets calculated on demand. This interface does two things:
 *  - It registers additional columns that should be displayed in the system browser.
 *  - It provides a system for updating the (registered) column values when system attributes change.
 * 
 * This communication between the browser and the add-on works both ways: The system browser will notify
 * any registered SystemBrowserCalculationCallbackInterface instances that it's registered columns might need
 * recalculation, and the add-on can inform the system browser to update it's displayed values for the
 * registered columns.
 * 
 * @since Archicad 29
 * @ingroup MEP
 * 
 * @snippet SystemBrowserCalculationCallbackInterface.cpp SystemBrowserCalculationCallbackInterface_Example
 * 
 * @see ACAPI::MEP::RegisterCalculationCallback
 * 
 * @remark This interface replaces the ACAPI::MEP::GraphCalculationInterface interface from Archicad 28. The new interface
 * supports the same functionality as the old one, but using a friendlier syntax. Here's a small guide on how to transition
 * your old implementation to this new interface:
 * @code{.cpp}
 * // Using ACAPI::MEP::GraphCalculationInterface:
 * std::shared_ptr<void> registrationInstance;
 * 
 * class MyCoolColumn : public ACAPI::MEP::TypedCalculationResultColumn<GS::UniString>
 * {
 * 	...
 * };
 * 
 * void CallbackHandlerFunction (const GS::Guid& root, const ACAPI::MEP::DistributionSystemsGraph& graph)
 * {
 * 	// Some code being executed when a calculation is requested from the browser...
 * 	...
 * 	
 * 	// Inform browser of changes to the columns:
 * 	ACAPI::Result<ACAPI::MEP::GraphCalculationInterface> calculationInterface = ACAPI::MEP::CreateCalculationInterface ();
 * 	calculationInterface->InvokeCalculationResults (changes);
 * }
 * 
 * void RegisterCalculationCallback ()
 * {
 * 	ACAPI::Result<ACAPI::MEP::GraphCalculationInterface> calculationInterface = ACAPI::MEP::CreateCalculationInterface ();
 * 
 * 	MyCoolColumn myCoolColumn;
 * 	std::vector<const ACAPI::MEP::ICalculationResultColumn*> columnsToShowInBrowser;
 * 	columnsToShowInBrowser.emplace_back (&myCoolColumn);
 * 
 * 	ACAPI::Result<std::shared_ptr<void>> registrationResult = calculationInterface->RegisterDoCalculationCallback (&CallbackHandlerFunction, columnsToShowInBrowser);
 * 	registrationInstance = registrationResult.Unwrap ();
 * }
 * 
 * 
 * // Using ACAPI::MEP::SystemBrowserCalculationCallbackInterface:
 * std::shared_ptr<void> registrationInstance;
 * 
 * class MyCoolColumn : public ACAPI::MEP::TypedCalculationResultColumn<GS::UniString>
 * {
 * 	...
 * };
 * 
 * class MyCalculationCallback : public ACAPI::MEP::SystemBrowserCalculationCallbackInterface
 * {
 * public:
 * 	MyCoolColumn myCoolColumn;
 * 
 * 	virtual std::vector<const ACAPI::MEP::ICalculationResultColumn*> RegisterCalculatedColumns () override
 * 	{
 * 		return { &myCoolColumn };
 * 	}
 * 
 * 	virtual void CalculationsRequested (const GS::Guid& root, const ACAPI::MEP::DistributionSystemsGraph& graph) override
 * 	{
 * 		// Some code being executed when a calculation is requested from the browser...
 * 		...
 * 		
 * 		// Inform browser of changes to the columns:
 * 		SubmitCalculations (changes);
 * 	}
 * };
 * 
 * MyCalculationCallback registrationInstance;
 * 
 * void RegisterCalculationCallback ()
 * {
 * 	ACAPI::MEP::RegisterCalculationCallback (registrationInstance);
 * }
 * @endcode
 */
class MEPAPI_EXPORT SystemBrowserCalculationCallbackInterface {
	friend Result<void> RegisterCalculationCallback (SystemBrowserCalculationCallbackInterface& callbackInterface);

private:
	std::shared_ptr<Impl::ISystemBrowserCalculationCallbackInterfaceImpl> mImpl;

	Result<void> Register (const API_Token& APIToken);

public:
	SystemBrowserCalculationCallbackInterface () = default;

	/**
	 * @brief Register columns that is managed by this interface.
	 * @details The system browser will invoke this once on initialization. The columns are unregistered when this interface instance goes
	 * out of scope and it's destructor is called. Deleting the memory pointed to by the pointers returned from this function before the
	 * interface goes out of scope leads to undefined behavior.
	 * @return A vector of pointers to the columns that this interface will manage.
	 * 
	 * @snippet SystemBrowserCalculationCallbackInterface.cpp SystemBrowserCalculationCallbackInterface_RegisterCalculatedColumns_Example
	 */
	virtual std::vector<const ICalculationResultColumn*> RegisterCalculatedColumns () = 0;

	/**
	 * @brief Function invoked every time the system browser detects that a system affecting some registered calculated columns was modified.
	 * @details The system browser will invoke this function whenever a system related parameter changes that could affect the calculated
	 * values. Examples when this occours include, but is not limited to, when elements are added or removed from the system and when element
	 * dimensions or certain element specific or system specific parameters are changed. The system browser is also free to skip invoking
	 * this function if the modified system is not covered by the registered columns. When calculations are finished, add-ons can choose
	 * to respond to this request by invoking SystemBrowserCalculationCallbackInterface::SubmitCalculations to update the displayed
	 * values in the system browser.
	 * @remark This function is invoked from the system browser based on model changes empirically determined to affect the calculated
	 * values. But as the displayed values are implementation defined, the detected changes may not always actually affect the displayed
	 * values. Therefore there's no requirement to "respond" to SubmitCalculations after receiving a CalculationsRequested call. Similarly,
	 * an add-on is free to invoke SubmitCalculations at any time, regardless of whether a CalculationsRequested call has been received.
	 * @param rootElement The "root" element of the system that has been modified.
	 * @param system The distribution systems graph that contains the modified system.
	 * 
	 * @snippet SystemBrowserCalculationCallbackInterface.cpp SystemBrowserCalculationCallbackInterface_CalculationsRequested_Example
	 */
	virtual void CalculationsRequested (const GS::Guid& rootElement, const DistributionSystemsGraph& system) = 0;

	/**
	 * @brief The signature of the entries in the result data.
	 * The row is decided by the system browser, so the entry is identified using the associated element id instead.
	 * @ingroup MEP
	 */
	struct ColumnRowEntry
	{
		/**
		 * @brief Unique ID of the element.
		 */
		GS::Guid elemId;
		/**
		 * @brief ID of the column. (should be the ID of one of the columns registered in RegisterCalculatedColumns)
		 */
		GS::UniString columnId;
		/**
		 * @brief The value of the column.Any value is accepted, but the value might not appear correctly in the browser
		 * if not implicitly convertible to a string.
		 */
		std::any value;
	};

	/**
	 * @brief The signature of the result data.
	 */
	using CalculationResultData = std::vector<ColumnRowEntry>;

	/**
	 * @brief Informs the system browser of modifications to the registered columns.
	 * Use this to to respond to a calculation request from the system browser.
	 * @param results A vector of column-row entries representing the results of the calculation.
	 * 
	 * @snippet SystemBrowserCalculationCallbackInterface.cpp SystemBrowserCalculationCallbackInterface_SubmitCalculations_Example
	 */
	void SubmitCalculations (const CalculationResultData& results) const;

	virtual ~SystemBrowserCalculationCallbackInterface () = default;
};

/**
 * @brief Registers a custom callback interface implementation.
 * @param callbackInterface The custom callback interface implementation to register.
 * @return Error if registration failed, otherwise nothing.
 * @since Archicad 29
 * @ingroup MEP
 * @snippet SystemBrowserCalculationCallbackInterface.cpp RegisterCalculationCallback_Example
 */
inline Result<void> RegisterCalculationCallback (SystemBrowserCalculationCallbackInterface& callbackInterface)
{
	return callbackInterface.Register (ACAPI_GetToken ());
}

} // ACAPI::MEP


#endif // GS_ACAPI_MEP_SYSTEMBROWSERCALCULATIONCALLBACKINTERFACE_HPP