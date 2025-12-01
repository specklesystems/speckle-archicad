// =============================================================================
// Description:		  Array Parameter
// Project:           3D Model Access API Refactoring
// Contact person:    SJ
// =============================================================================
#if !defined (ARRAYPARAMETER_HPP)
#define ARRAYPARAMETER_HPP


// ----------------------- Includes --------------------------------------------
#include "UniString.hpp"
#include "GSModelerExport.h"
#include "SharedPtr.hpp"

// ----------------------- Predeclaration    -----------------------------------
namespace ModelerAPI {
	class ArrayParameterRelay;
}

// ----------------------- Class declaration -----------------------------------

namespace ModelerAPI {


class GSMODELER_DLL_EXPORT ArrayParameter {
	friend class ArrayParameterRelay;

private:
	GS::SharedPtr<ArrayParameterRelay>	relay;

public:
	enum Type {
		UndefinedType		= 0,
		NumericType			= 1,
		StringType			= 2,
		NumericArrayType	= 3,
		StringArrayType		= 4
	};

	ArrayParameter ();
	ArrayParameter (const ArrayParameter& other);
	~ArrayParameter ();

	ArrayParameter&	operator= (const ArrayParameter& other);
	ArrayParameter	operator[] (Int32 index) const;
					operator double () const;
	void			operator= (double value);
	void			operator= (const GS::UniString& uString);

	Type			GetType (void) const;
	void			GetStringValue (GS::UniString& uString) const;
	void			GetArrayItem (Int32 index, ArrayParameter* arrayItem) const;
};


} // namespace ModelerAPI


#endif
