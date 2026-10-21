// =============================================================================
// Description:		  Base Element Identifier   
// Project:           
// Contact person:    PP
// =============================================================================
#if !defined (BASEELEMENTID_HPP)
#define BASEELEMENTID_HPP

#include "GSModelerExport.h"
#include "SharedPtr.hpp"

// ----------------------- Predeclarations -------------------------------------

// ----------------------- Class declaration -----------------------------------

namespace ModelerAPI {
class BaseElemIdRelay;

class GSMODELER_DLL_EXPORT BaseElemId {
	friend class BaseElemIdRelay;

private:
	GS::ConstSharedPtr<ModelerAPI::BaseElemIdRelay>	relay;

public:
	BaseElemId ();
	BaseElemId (const BaseElemId& other);
	~BaseElemId ();

	BaseElemId&			operator= (const BaseElemId& other);
	bool				operator== (const BaseElemId& other) const;
	bool				operator!= (const BaseElemId& other) const	{ return !(*this == other); }
	bool				operator< (const BaseElemId& other) const;
	ULong				GenerateHashValue () const;
};


} // namespace ModelerAPI


#endif
