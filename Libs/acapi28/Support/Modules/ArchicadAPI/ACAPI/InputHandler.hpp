#ifndef ACAPI_INPUTHANDLER_HPP
#define ACAPI_INPUTHANDLER_HPP

#include "ACAPI/ArchicadAPIExport.hpp"
#include "ACAPI/Object.hpp"
#include "UniqueID.hpp"
#include "Result.hpp"

namespace ACAPI {

namespace v1 {

/**
 * @brief A class to handle input related operations, like manipulating the input position and starting an input
 * @class InputHandler
 * @since Archicad 28
 * @ingroup UserInput
 */
class ARCHICADAPI_EXPORT InputHandler : public Object {
	
	friend Result<InputHandler> CreateInputHandler ();
	explicit InputHandler (const API_Token& token);

public:
	/**
	 * @brief A function to get the current input position in model coordinates.
	 * @return Returns the input position in 3D coordinates.
	 * @remark The input position can be different from the cursor's position, because:
	 * 		   - The input position snaps to nearby elements
	 * 		   - The input position can be set without moving the cursor's position
	 */
	Result<API_Coord3D>	GetInputPosition () const;

	/**
	 * @brief Sets the current input position with or without the cursor
	 * @param position [in] The 3D coordinate of the new position.
	 * @param withCursor [in] Sets if the cursor is needed to be moved to the new position.
	 * @return Returns an error if setting the input position above the current front window is not applicable, otherwise nothing.
	 * 		   - APIERR_BADWINDOW -  the operation cannot be performed in the current front window of the application. Currently only the floorplan (`APIWind_FloorPlanID`) is supported
	 */
	Result<void>		SetInputPosition (const API_Coord3D& position, bool withCursor) const;

	/**
	 * @brief Applies the current input position by performing a mouse click at it
	 * @return Returns an error if the input above the current front window is not applicable, otherwise nothing.
	 * 		   - APIERR_BADWINDOW -  the operation cannot be performed in the current front window of the application. Currently only the floorplan (`APIWind_FloorPlanID`) is supported
	 */
	Result<void>		ApplyInputPosition () const;
};


/**
 * @brief A function to create an @ref InputHandler instance, that lets you handle input related operations
 * @ingroup UserInput
 * @return Returns the @ref InputHandler instance. This process cannot fail.
 */
inline Result<InputHandler> CreateInputHandler ()
{
	return Ok (InputHandler (ACAPI_GetToken ()));
}


} // namespace v1

using namespace v1;

} // namespace ACAPI

#endif // ACAPI_INPUTHANDLER_HPP