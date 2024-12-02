#ifndef GS_ACAPI_MEP_GRAPHCALCULATIONINTERFACE_HPP
#define GS_ACAPI_MEP_GRAPHCALCULATIONINTERFACE_HPP

#include "MEPAPIExport.hpp"
#include "MEPUniqueID.hpp"
#include "MEPEnums.hpp"

// ACAPI
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <any>
#include <optional>


namespace ACAPI::MEP {

namespace Impl {
class IGraphCalculationInterfaceImpl;
}

namespace v1 {

class DistributionSystemsGraph;

/**
 * @brief Measurement systems supported by the Systems Browser. Used for formatting values appropriately to the user's preference.
 * @since Archicad 28
 * @ingroup MEP
 */
 enum class MeasurementSystem
 {
	Metric,
	Imperial
 };


/**
 * @brief Formatting for calculated values
 * @since Archicad 28
 * @ingroup MEP
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
	 * @param system The selected measurement system
	 * @remark This is what will be displayed on the GUI (should be localized if possible).
	 */
	virtual std::optional<GS::UniString>	GetUnitToDisplay		(MeasurementSystem system) const = 0;
	
	/**
	 * @brief Formats the value to a displayable text.
	 * @param value The value to format into a displayable text
	 * @param system The measurement system in which the displayed text is interpeted
	 * @return The displayable text
	 */
	virtual GS::UniString	FormatValueToDisplayText		(const std::any& value, MeasurementSystem system) const = 0;
	
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
};
 
 
/**
 * @brief Template typed version of the ICalculationResultColumn interface.
 * @since Archicad 28
 * @ingroup MEP
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

protected:
 
	/**
	 * @brief Formats the value to a displayable text.
	 * @param value The typed value to format into a displayable text
	 * @param system The measurement system in which the displayed text is interpeted
	 * @return The displayable text
	 */
	virtual GS::UniString  FormatValueToDisplayText (const T& value, MeasurementSystem system) const = 0;
 
private:
 
	/**
	 * @brief Formats the value to a displayable text.
	 * @param value The value to format into a displayable text
	 * @return The displayable text
	 */
	GS::UniString  FormatValueToDisplayText (const std::any& value, MeasurementSystem system) const override
	{
		return this->FormatValueToDisplayText (std::any_cast<T> (value), system);
	}
};


/**
 * @brief A class to communicate between registered calculating addons and those using the calculations.
 * @details When a new calculation needs to be done, the requestor calls a function to invoke a new calculation. When the calculator
 * 			is finished with it's calculations, it calls a function to return the results to registered result wanters.
 * @since Archicad 28
 * @ingroup MEP
 * @par Example code snippets from Test / New MEP
 * 		CreateCalculationInterface @snippet GraphCalculationInterface.cpp CreateCalculationInterface_Example
 * 		RegisterDoCalculationCallback @snippet GraphCalculationInterface.cpp RegisterDoCalculationCallback_Example
 * 		InvokeCalculationResults @snippet GraphCalculationInterface.cpp InvokeCalculationResults_Example
 */
class MEPAPI_EXPORT GraphCalculationInterface final : public Object {
private:
	GraphCalculationInterface (std::shared_ptr<Impl::IGraphCalculationInterfaceImpl> impl);

	static Result<GraphCalculationInterface> Create (const API_Token& APIToken);

public:
	/**
	 * @brief The signature of the calculation callback.
	 * @details The callback caller supplies the GUID of the "root element" for the system to perform
	 * 			calculations on, which is an element contained in the system to perform calculations on and
	 * 			also the first element DistributionSystem::TraverseTree will traverse through.
	 */
	using DoCalculationCallback = void (*)(const GS::Guid&, const ACAPI::MEP::v1::DistributionSystemsGraph&);

	/**
	 * @brief The signature of the result data in the form (element guid, column ID, value).
	 */
	using CalculationResultData = std::vector<std::tuple<GS::Guid, GS::UniString, std::any>>;

	friend Result<GraphCalculationInterface> CreateCalculationInterface ();

	/**
	 * @brief Registers a callback function for performing calculations.
	 * @details The callback is invoked every time the system browser requests calculated values,
	 * 			which happens everytime a system becomes visible or changes in the system browser tree view.
	 * @param callback The function to be called when a calculation needs to be performed.
	 * @param resultColumns Implementations of the ICalculationResultColumn interface to integrate values into the Systems Browser.
	 * @return A shared_ptr to void used as a guard object. When the return value object goes out of scope, the callback
	 * 		   will be ungeristered.
	 *
	 * 		   @snippet GraphCalculationInterface.cpp RegisterDoCalculationCallback_Example
	 */
	ACAPI::Result<std::shared_ptr<void>> RegisterDoCalculationCallback (DoCalculationCallback callback, const std::vector<const ICalculationResultColumn*>& resultColumns);

	/**
	 * @brief Invokes the function to deliver calculation results.
	 * @param results A vector of (elemId, column ID and value) objects representing the results of the calculation.
	 *
	 * 				  @snippet GraphCalculationInterface.cpp InvokeCalculationResults_Example
	 */
    void InvokeCalculationResults (const CalculationResultData& results) const;
};

/**
 * @brief Creates an instance of the GraphCalculationInterface.
 *
 * 		  This function is used to get the singleton instance of the GraphCalculationInterface.
 * 		  It is a friend function of the GraphCalculationInterface class, allowing it to access
 * 		  the private members of the class.
 *
 * @return A reference to the GraphCalculationInterface instance.
 * 		   @snippet GraphCalculationInterface.cpp CreateCalculationInterface_Example
 * @ingroup MEP
 */
inline Result<GraphCalculationInterface> CreateCalculationInterface ()
{
	return GraphCalculationInterface::Create (ACAPI_GetToken ());
}

} // v1

using v1::MeasurementSystem;
using v1::ICalculationResultColumn;
using v1::GraphCalculationInterface;
using v1::TypedCalculationResultColumn;
using v1::CreateCalculationInterface;

} // ACAPI::MEP

#endif // GS_ACAPI_MEP_GRAPHCALCULATIONINTERFACE_HPP