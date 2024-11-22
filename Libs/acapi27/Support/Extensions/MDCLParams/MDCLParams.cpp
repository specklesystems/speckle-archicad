#ifndef ACExtension
	#define ACExtension
#endif
#include "ACAPinc.h"
#include "APIdefs_Goodies.h"
#include "MDCLParams.hpp"


namespace GSAPI {

static API_MDCLParameter	InitParam (const char *name, Int32 type = 0)
{
	API_MDCLParameter p;
	BNClear (p);
	p.name = name;
	p.type = type;
	return p;
}


MDCLParams::MDCLParams (bool freeHandle/* = true*/)
{
	params = nullptr;
	ownParams = freeHandle;
	ACAPI_AddOnAddOnCommunication_InitMDCLParameterList (&params);
}


MDCLParams::MDCLParams (GSHandle inParams)
{
	params = inParams;
	ownParams = false;
}


MDCLParams::~MDCLParams ()
{
	if (ownParams) {
		ACAPI_AddOnAddOnCommunication_FreeMDCLParameterList (&params);
	}
}


Int32	MDCLParams::GetNum () const
{
	Int32 num = 0;
	ACAPI_AddOnAddOnCommunication_GetMDCLParameterNum (params, &num);
	return num;
}


bool GetParam (GSHandle params, API_MDCLParameter& p)
{
	return ACAPI_AddOnAddOnCommunication_GetMDCLParameter (params, &p) == NoError;
}


bool ChangeParam (GSHandle params, API_MDCLParameter& p)
{
	return ACAPI_AddOnAddOnCommunication_ChangeMDCLParameter (params, &p) == NoError;
}


bool AddParam (GSHandle params, API_MDCLParameter& p)
{
	return ACAPI_AddOnAddOnCommunication_AddMDCLParameter (params, &p) == NoError;
}


GS::String	MDCLParams::GetParamName (const Int32 index) const
{
	API_MDCLParameter p;
	BNClear (p);
	p.index = index;
	if (ACAPI_AddOnAddOnCommunication_GetMDCLParameter (params, &p) == NoError)
		return p.name;
	return GS::String ();
}


bool	MDCLParams::GetInt (const char* name, Int32& value) const
{
	API_MDCLParameter p = InitParam (name);
	if (GetParam (params, p) && p.type == MDCLPar_int) {
		value = p.int_par;
		return true;
	}
	return false;
}


bool	MDCLParams::GetFloat (const char* name, double &value) const
{
	API_MDCLParameter p = InitParam (name);
	if (GetParam (params, p) && p.type == MDCLPar_float) {
		value = p.float_par;
		return true;
	}
	return false;
}


bool	MDCLParams::GetString (const char *name, const char*& value) const
{
	API_MDCLParameter p = InitParam (name);
	if (GetParam (params, p) && p.type == MDCLPar_string) {
		value = p.string_par;
		return true;
	}
	return false;
}


bool	MDCLParams::GetString (const char* name, GS::String& value) const
{
	API_MDCLParameter p = InitParam (name);
	if (GetParam (params, p) && p.type == MDCLPar_string) {
		value = p.string_par;
		return true;
	}
	return false;
}


bool MDCLParams::GetString (const char *name, GS::UniString &value, const GSCharCode& charCode) const
{
	GS::String string;
	bool result = GetString (name, string);
	if (result)
		value.Assign (string.ToCStr (), charCode);

	return result;
}


bool	MDCLParams::GetPtr (const char* name, void** value) const
{
	API_MDCLParameter p = InitParam (name);
	if (GetParam (params, p) && p.type == MDCLPar_pointer) {
		if (DBVERIFY (value != nullptr)) {
			*value = p.ptr_par;
			return true;
		}
	}
	return false;
}


bool	MDCLParams::GetBool (const char* name, bool& value) const
{
	Int32 tmp;
	bool result = GetInt (name, tmp);
	if (result)
		value = (tmp != 0);

	return result;
}


bool	MDCLParams::SetInt (const char* name, Int32 value)
{
	API_MDCLParameter p = InitParam (name);
	if (GetParam (params, p)) {
		if (p.type != MDCLPar_int) {
			return false;
		} else {
			p.int_par = value;
			return ChangeParam (params, p);
		}
	} else {
		p = InitParam (name, MDCLPar_int);
		p.int_par = value;
		return AddParam (params, p);
	}
}


bool	MDCLParams::SetFloat (const char* name, double value)
{
	API_MDCLParameter p = InitParam (name);
	if (GetParam (params, p)) {
		if (p.type != MDCLPar_float) {
			return false;
		} else {
			p.float_par = value;
			return ChangeParam (params, p);
		}
	} else {
		p = InitParam (name, MDCLPar_float);
		p.float_par = value;
		return AddParam (params, p);
	}
}


bool	MDCLParams::SetString (const char* name, const char* value)
{
	API_MDCLParameter p = InitParam (name);
	if (GetParam (params, p)) {
		if (p.type != MDCLPar_string) {
			return false;
		} else {
			p.string_par = value;
			return ChangeParam (params, p);
		}
	} else {
		p = InitParam (name, MDCLPar_string);
		p.string_par = value;
		return AddParam (params, p);
	}
}


bool	MDCLParams::SetPtr (const char* name, void* value)
{
	API_MDCLParameter p = InitParam (name);
	if (GetParam (params, p)) {
		if (p.type != MDCLPar_pointer) {
			return false;
		} else {
			p.ptr_par = value;
			return ChangeParam (params, p);
		}
	} else {
		p = InitParam (name, MDCLPar_pointer);
		p.ptr_par = value;
		return AddParam (params, p);
	}
}


bool	MDCLParams::SetBool (const char* name, bool value)
{
	return SetInt (name, value != 0);
}


}
