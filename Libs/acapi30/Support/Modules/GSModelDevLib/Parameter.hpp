// =============================================================================
// Description:		  Parameter
// Project:           3D Model Access API Refactoring
// Contact person:    SJ
// =============================================================================
#if !defined (PARAMETER_HPP)
#define PARAMETER_HPP

// ----------------------- Includes --------------------------------------------
#include "ArrayParameter.hpp"
#include "GSModelerExport.h"
#include "SharedPtr.hpp"

// ----------------------- Predeclaration --------------------------------------
namespace ModelerAPI {
	class ParameterRelay;
}

// ----------------------- Class declaration -----------------------------------
namespace ModelerAPI {


class GSMODELER_DLL_EXPORT Parameter {
	friend class ParameterRelay;

private:
	GS::SharedPtr<ParameterRelay>		relay; //itt nem const referencia marad!

public:
	enum Type {
		UndefinedType		= 0,
		NumericType			= 1,
		StringType			= 2,
		NumericArrayType	= 3,
		StringArrayType		= 4
	};

	Parameter ();
	Parameter (const Parameter& other);
	~Parameter ();
					operator double () const;
	Parameter&		operator= (const Parameter& other);
	void			operator= (double value);
	void			operator= (const GS::UniString& uString);
	ArrayParameter	operator[] (Int32 index) const;
	

	void			GetName (char* name, Int32 bufferSize) const;
	GS::UniString	GetName () const;
	Type			GetType (void) const;
	void			SetType (Type t);
	bool			IsArray (void) const;
	void			GetArrayDimensions (Int32* dimension1, Int32* dimension2) const;
	void			SetArrayDimensions (Int32 dimension1, Int32 dimension2);
	void			GetStringValue (GS::UniString& uString) const;
	void			GetArrayItem (Int32 index1, Int32 index2, ArrayParameter* arrayItem) const;
};


} // namespace ModelerAPI


#endif
