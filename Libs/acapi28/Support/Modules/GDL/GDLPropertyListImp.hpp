// *********************************************************************************************************************
// Description:		GDLPropertyListImp.hpp
//
// Module:			GDL
// Namespace:		GDL
// Contact person:	HK
//
// *********************************************************************************************************************

#if !defined GDLPROPERTYLISTIMP_HPP
#define GDLPROPERTYLISTIMP_HPP

#include	"GSRoot.hpp"

#include "CommonSize.h"
#include "GDLDefs.h"
#include "GDLPars.h"
#include "GDLParamInterface.hpp"

namespace GDL {

template<class UserDataType>
void PropertyList<UserDataType>::Create (ULong nr)
{
	this->Clear ();
	while (nr--)
		this->PushEntry ("", GS::PropertyList<UserDataType>::Integer, GS::PropertyList<UserDataType>::Scalar, 0, 0);
}


template<class UserDataType>
GDL::Parameters GDL::PropertyList<UserDataType>::WriteToParameters () const
{
	const ULong enNum = this->GetEntryNum ();
	GDL::Parameters addPar (enNum);
	if (addPar.IsNull ()) {
		throw GS::GSException ();
	}

	for (ULong i = 0; i < enNum; ++i) {
		addPar.ModifyVarName (i, this->GetEntryName (i));

		typename GS::PropertyList<UserDataType>::ArrayType at;
		ULong dim1, dim2;
		typename GS::PropertyList<UserDataType>::StorageType st = this->GetEntryType (i, &at, &dim1, &dim2);
		if (at == GS::PropertyList<UserDataType>::Scalar) {
			dim1 = dim2 = 0;
		} else if (at == GS::PropertyList<UserDataType>::OneDimensional) {
			dim2 = 0;
		}

		const short dataType =	(st == GS::PropertyList<UserDataType>::Integer) ? ParT_Integer :
								(st == GS::PropertyList<UserDataType>::Numeric) ? ParT_RealNum : ParT_CString;
		addPar.ModifyVarType (i, dataType, at != GS::PropertyList<UserDataType>::Scalar, dim1, dim2);

		if (at == GS::PropertyList<UserDataType>::Scalar) {
			if (st == GS::PropertyList<UserDataType>::Integer) {
				addPar.ModifyIntVar (i, this->GetIntEntry (i));
			} else if (st == GS::PropertyList<UserDataType>::Numeric) {
				addPar.ModifyNumVar (i, this->GetNumEntry (i));
			} else if (st == GS::PropertyList<UserDataType>::String) {
				addPar.ModifyUStrVar (i, this->GetStringEntry (i));
			} else {
				DBBREAK_STR ("Invalid storage category. Maybe dictionary? Dictionaries are not and should not be supported by PropertyList. You should make sure that there are no Dictionary parameters in the addPar.");
			}
		} else {
			if (st == GS::PropertyList<UserDataType>::Integer) {
				addPar.ModifyIntArray (i, this->GetIntArray (i), nullptr);
			} else if (st == GS::PropertyList<UserDataType>::Numeric) {
				addPar.ModifyNumArray (i, this->GetNumArray (i), nullptr);
			} else if (st == GS::PropertyList<UserDataType>::String) {
				addPar.ModifyUStrArray (i, this->GetStringArray (i));
			} else {
				DBBREAK_STR ("Invalid storage category. Maybe dictionary? Dictionaries are not and should not be supported by PropertyList. You should make sure that there are no Dictionary parameters in the addPar.");
			}
		}

		addPar.SetVarFix (i, this->IsEntryFix (i));
	}

	return addPar;
}


template<class UserDataType>
void PropertyList<UserDataType>::ReadFromParameters (const GDL::ParameterGetter& addPar)
{
	for (ULong i = 0; i < this->GetEntryNum (); i++)
		this->SetEntryFix (i, false);
	this->DeleteEntries (0, this->GetEntryNum () - 1);

	try {
		for (ULong i = 0; i < ULong (addPar.GetVarNumber ()); i++) {
			bool isArray;
			Int32 dim1, dim2;
			char name[MAXNAMUTF8];
			short dataType = addPar.GetVarType (i, &isArray, &dim1, &dim2);
			addPar.GetVarName (i, name, sizeof (name));

			typename GS::PropertyList<UserDataType>::ArrayType at;
			typename GS::PropertyList<UserDataType>::StorageType st = GS::PropertyList<UserDataType>::Numeric;

			if (!isArray)
				at = GS::PropertyList<UserDataType>::Scalar;
			else if (dim2 <= 0)
				at = GS::PropertyList<UserDataType>::OneDimensional;
			else
				at = GS::PropertyList<UserDataType>::TwoDimensional;

			if (GDLIsIntType (dataType)) {
				st = GS::PropertyList<UserDataType>::Integer;
			} else if (GDLIsNumType (dataType)) {
				st = GS::PropertyList<UserDataType>::Numeric;
			} else if (GDLIsStringType (dataType)) {
				st = GS::PropertyList<UserDataType>::String;
			} else if (DBERROR_STR (GDLIsDictType (dataType), "Dictionaries are not and should not be supported by PropertyList. You should make sure that there are no Dictionary parameters in the addPar.")) {
				st = GS::PropertyList<UserDataType>::Numeric; //fallback type, as in ParamList::GetStorageType
			} else {
				INVALID_STORAGE_CATEGORY;
			}
			this->PushEntry (name, st, at, dim1, dim2);

			switch (at) {
				case GS::PropertyList<UserDataType>::Scalar:
					switch (st) {
						case GS::PropertyList<UserDataType>::Integer:
							this->SetIntEntry (i, addPar.GetIntVar (i));
							break;
						case GS::PropertyList<UserDataType>::Numeric:
							this->SetNumEntry (i, addPar.GetNumVar (i));
							break;
						case GS::PropertyList<UserDataType>::String:
							this->SetStringEntry (i, addPar.GetUStrVarRef (i));
							break;
						default:
							DBBREAK_STR ("Invalid storage category.");
							break;
					}
					break;
				case GS::PropertyList<UserDataType>::OneDimensional:
				case GS::PropertyList<UserDataType>::TwoDimensional:
					switch (st) {
						case GS::PropertyList<UserDataType>::Integer:
							this->SetIntArray (i, (const Int32*) addPar.GetUArrayRef (i));
							break;
						case GS::PropertyList<UserDataType>::Numeric:
							this->SetNumArray (i, (const double*) addPar.GetUArrayRef (i));
							break;
						case GS::PropertyList<UserDataType>::String:
							this->SetStringArray (i, (const GS::uchar_t*) addPar.GetUArrayRef (i));
							break;
						default:
							DBBREAK_STR ("Invalid storage category.");
							break;
					}
					break;
			}

			this->SetEntryFix (i, addPar.IsVarFix (i));
		}
	} catch (...) {
		this->Clear ();
		throw;
	}
}

}

#endif