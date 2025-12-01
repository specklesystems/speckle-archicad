// =============================================================================
// Description:		  Parameter List
// Project:           3D Model Access API Refactoring
// Contact person:    SJ
// =============================================================================
#if !defined (PARAMETERLIST_HPP)
#define PARAMETERLIST_HPP

// ----------------------- Includes --------------------------------------------
#include "GSModelerExport.h"
#include "SharedPtr.hpp"

// ----------------------- Predeclaration --------------------------------------
namespace ModelerAPI {
	class ParameterListRelay;
	class Parameter;
}

// ----------------------- Class declaration -----------------------------------
namespace ModelerAPI {


class GSMODELER_DLL_EXPORT ParameterList {
	friend class ParameterListRelay;

private:
	GS::SharedPtr<ParameterListRelay>		relay;	//itt nem const referencia marad! AACS

public:
	ParameterList ();
	ParameterList (const ParameterList& other);
	~ParameterList ();

	bool			operator== (const ParameterList& other) const;
	bool			operator!= (const ParameterList& other) const	{ return !(*this == other); }
	bool			operator< (const ParameterList& other) const;
	Parameter		operator[] (Int32 index) const;
	Parameter		operator[] (const char* name) const;
	Parameter		operator[] (const GS::UniString& name) const;
	ParameterList&	operator= (const ParameterList& other);
	
	ULong		GenerateHashValue () const;
	Int32		GetParameterCount (void) const;
	bool		GetParameter (Int32 index, ModelerAPI::Parameter* parameter) const;
	bool		GetParameter (const char* name, ModelerAPI::Parameter* parameter) const;
	bool		GetParameter (const GS::UniString& name, ModelerAPI::Parameter* parameter) const;
	void		DeleteParameter (Int32 index);
	void		DeleteParameter (const char* name);
	void		DeleteParameter (const GS::UniString& name);
};


} // namespace ModelerAPI


#endif
