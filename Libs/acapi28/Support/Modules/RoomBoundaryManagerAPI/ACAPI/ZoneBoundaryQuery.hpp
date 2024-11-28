#ifndef GS_ACAPI_ZONEBOUNDARYQUERY_HPP
#define GS_ACAPI_ZONEBOUNDARYQUERY_HPP

#include "ZoneBoundary.hpp"
#include "ZoneBoundaryQueryAPIExport.hpp"

// from ArchicadAPI
#include "ACAPI/ModifyScope.hpp"
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"

// from Standard Library
#include <vector>


namespace GS { class ProcessControl; }


namespace ACAPI {
namespace v1 {


/**
 * @ingroup Element
 * @since Archicad 27
 * @brief This class can be used to query the boundaries of Zones. Before use an Update must be called on it.
 */
class ZONEBOUNDARYQUERYAPI_EXPORT ZoneBoundaryQuery : public Object {

	ZoneBoundaryQuery (API_Token);

	friend ZoneBoundaryQuery	CreateZoneBoundaryQuery ();

public:

	class Modifier;

	/**
	 * @param zoneId The unique identifier of the Zone.
	 * @return Returns the boundaries of the given Zone if it exists, otherwise Error.
	 */
	Result<std::vector<ZoneBoundary>>	GetZoneBoundaries (API_Guid zoneId) const;

	/**
	 * @brief Executes the given modifier scope in a NotUndoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template<typename ModifierFunc>
	Result<void>						Modify (ModifierFunc&& modifierFunc);
};


class ZONEBOUNDARYQUERYAPI_EXPORT ZoneBoundaryQuery::Modifier : public ModifierBase {
public:

	/**
	 * @brief Updates the boundaries of the Zones in the current view.
	 * 		  Works only on Floor Plan window and 3D Model window.
	 * @return Returns an error if the current window is not Floor Plan or 3D Model.
	 */
	[[nodiscard]]
	Result<void>	Update (GS::ProcessControl&);

private:

	ZoneBoundaryQuery& mZoneBoundaryQuery;

	friend ZoneBoundaryQuery;
	Modifier (ZoneBoundaryQuery&);

	~Modifier () override;
};


template<typename ModifierFunc>
Result<void>	ZoneBoundaryQuery::Modify (ModifierFunc&& modifierFunc)
{
	Modifier modifier { *this };
	return ACAPI::ExecuteNotUndoableScope (std::forward<ModifierFunc> (modifierFunc), modifier, *this);
}


/**
 * @ingroup Element
 * @since Archicad 27
 * @return Creates a ZoneBoundaryQuery object.
 */
inline ZoneBoundaryQuery	CreateZoneBoundaryQuery ()
{
	return ZoneBoundaryQuery { ACAPI_GetToken () };
}


} // namespace v1

using namespace v1;

} // namespace ACAPI


#endif /* GS_ACAPI_ZONEBOUNDARYQUERY_HPP */
