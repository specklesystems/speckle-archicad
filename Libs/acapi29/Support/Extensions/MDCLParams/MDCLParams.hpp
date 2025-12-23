#ifndef __MDCLPARAMS_HPP__
#define __MDCLPARAMS_HPP__

#pragma once

#include "Definitions.hpp"
#include "String.hpp"
#include "UniString.hpp"


namespace GSAPI {

class MDCLParams {
private:
					MDCLParams		(const MDCLParams&);	// disabled
	void			operator=		(const MDCLParams&);	// disabled

public:
					MDCLParams		(bool freeHandle = true);					// used by callers
					MDCLParams		(GSHandle params);	// used by callees
					~MDCLParams		();

	Int32			GetNum			() const;
	GSHandle		GetParams		() { return params; }
	GS::String		GetParamName	(const Int32 index) const;

	// these fail if the parameter does not exists or type is different
	bool			GetInt			(const char* name,	Int32& value) const;
	bool			GetFloat		(const char* name,	double& value) const;
	bool			GetString		(const char* name,	const char*& value) const;
	bool			GetString		(const char* name,	GS::String& value) const;
	bool			GetString		(const char* name,	GS::UniString& value, const GSCharCode& charCode = GSCharCode::CC_Default) const;
	bool			GetPtr			(const char* name,	void** value) const;
	bool			GetBool			(const char* name,	bool& value) const;

	// fails if parameter is not pointer, but not fails if different type is behind that void* pointer
	template<typename T>
	bool			GetPtrTyped		(const char* name,	T& value) const;

	// these fail if parameter already exists with different type
	bool			SetInt			(const char *name,	Int32 value);
	bool			SetFloat		(const char *name,	double value);
	bool			SetString		(const char *name,	const char* value);
	bool			SetPtr			(const char *name,	void* value);
	bool			SetBool			(const char* name,	bool value);

private:
	GSHandle		params;
	bool			ownParams;
};


template<typename T>
bool GSAPI::MDCLParams::GetPtrTyped (const char* name, T& value) const
{
	T* valuePtr = nullptr;
	if (GetPtr (name, reinterpret_cast<void**> (&valuePtr)) && valuePtr != nullptr) {
		value = *valuePtr;
		return true;
	}
	return false;
}

}

#endif
