// *****************************************************************************
//
// File:			PreferencesHandling.hpp
//
// Description:		Helper classes for registry handling.
//
// *****************************************************************************

#if !defined(PREFERENCESHANDLING_HPP)
#define PREFERENCESHANDLING_HPP

#pragma once

#include "GSUtilsExport.h"
#include "UniString.hpp"
#include "GSPref.hpp"
#include "SpinLock.hpp"

namespace Preferences
{

// http://wiki/w/Preferences::Value
template <typename ValueType>
class Value
{
public:
	Value (const GS::UniString&			keyPath,
		   const GS::UniString&			valueName,
		   const ValueType&				defaultValue,
		   GSPref::IRoot::WriteBackMode writeBackMode);

	Value (GSPref::RootKeyDomain		domain,
		   const GS::UniString&			keyPath,
		   const GS::UniString&			valueName,
		   const ValueType&				defaultValue,
		   GSPref::IRoot::WriteBackMode writeBackMode);

	const ValueType&	GetValue ();
	void				SetValue (const ValueType& newValue);

	operator const ValueType& ();

private:
	Value ();
	Value (const Value& source);
	const Value& operator= (const Value& source);

	GS::ErrCode						GetRegistryValue (GSPref::IRoot* rootKey);
	GS::ErrCode						SetRegistryValue (GSPref::IRoot* rootKey, const ValueType& newValue);

	const GSPref::RootKeyDomain		domain;
	const GS::UniString				keyPath;
	const GS::UniString				valueName;
	GSPref::IRoot::WriteBackMode	writeBackMode;
	
	bool							initialized;
	ValueType						resultValue;
};

template <typename ValueType>
Value<ValueType>::Value (const GS::UniString&			keyPath,
						 const GS::UniString&			valueName,
						 const ValueType&				defaultValue,
						 GSPref::IRoot::WriteBackMode	writeBackMode) :
	domain			(GSPref::CurrentUserLocalDomain),
	keyPath			(keyPath),
	valueName		(valueName),
	writeBackMode	(writeBackMode),
	initialized		(false),
	resultValue		(defaultValue)
{

}



template <typename ValueType>
Value<ValueType>::Value (GSPref::RootKeyDomain			domain,
						 const GS::UniString&			keyPath,
						 const GS::UniString&			valueName,
						 const ValueType&				defaultValue,
						 GSPref::IRoot::WriteBackMode	writeBackMode) :
	domain (domain),
	keyPath (keyPath),
	valueName (valueName),
	writeBackMode (writeBackMode),
	initialized (false),
	resultValue (defaultValue)
{

}


template <typename ValueType>
const ValueType& Value<ValueType>::GetValue ()
{
	if (!initialized) {
		GSPref::IRoot* rootKey = GSPref::OpenRootKey (domain);
		if (DBVERIFY (rootKey != nullptr)) {
			GSErrCode err = GetRegistryValue (rootKey);
			if (err != NoError) {
				if (writeBackMode == GSPref::IRoot::WriteBack || err != GSPref::IRoot::ValueNotFound) {
					DBBREAK_STR ("Failed to get registry value.");
				}
			}
			GSPref::CloseRootKey (&rootKey);
		}
		initialized = true;
	}
	return resultValue;
}

template <typename ValueType>
void Value<ValueType>::SetValue (const ValueType& newValue)
{
	GSPref::IRoot* rootKey = GSPref::OpenRootKey (domain);
	if (rootKey != nullptr) {
		if (SetRegistryValue (rootKey, newValue) != NoError) {
			DBBREAK_STR ("Failed to get registry value.");
		} else {
			resultValue = newValue;
		}
		GSPref::CloseRootKey (&rootKey);
	}
}

template <typename ValueType>
Value<ValueType>::operator const ValueType& ()
{
	return GetValue ();
}

template <>
inline GS::ErrCode Value<bool>::GetRegistryValue (GSPref::IRoot* rootKey)
{
	return rootKey->GetBoolValue (keyPath.ToCStr ().Get (), valueName.ToCStr ().Get (), &resultValue, resultValue, writeBackMode);
}

template <>
inline GS::ErrCode Value<Int32>::GetRegistryValue (GSPref::IRoot* rootKey)
{
	return rootKey->GetLongValue (keyPath.ToCStr ().Get (), valueName.ToCStr ().Get (), &resultValue, resultValue, writeBackMode);
}

template <>
inline GS::ErrCode Value<double>::GetRegistryValue (GSPref::IRoot* rootKey)
{
	GS::UniString valueAsString;
	GS::UniString defaultAsString = GS::UniString::Printf ("%lf", resultValue);
	GS::ErrCode errCode = rootKey->GetStringValue (keyPath.ToCStr ().Get (), valueName.ToCStr ().Get (), &valueAsString, defaultAsString, writeBackMode);
	if (errCode == NoError) {
		valueAsString.SScanf ("%lf", &resultValue);	// leaves resultValue unchanged on error
	}
	return errCode;
}

template <>
inline GS::ErrCode Value<GS::UniString>::GetRegistryValue (GSPref::IRoot* rootKey)
{
	return rootKey->GetStringValue (keyPath.ToCStr ().Get (), valueName.ToCStr ().Get (), &resultValue, resultValue, writeBackMode);
}

template <>
inline GS::ErrCode Value<bool>::SetRegistryValue (GSPref::IRoot* rootKey, const bool& newValue)
{
	return rootKey->SetBoolValue (keyPath.ToCStr ().Get (), valueName.ToCStr ().Get (), newValue);
}

template <>
inline GS::ErrCode Value<Int32>::SetRegistryValue (GSPref::IRoot* rootKey, const Int32& newValue)
{
	return rootKey->SetLongValue (keyPath.ToCStr ().Get (), valueName.ToCStr ().Get (), newValue);
}

template <>
inline GS::ErrCode Value<GS::UniString>::SetRegistryValue (GSPref::IRoot* rootKey, const GS::UniString& newValue)
{
	return rootKey->SetStringValue (keyPath.ToCStr ().Get (), valueName.ToCStr ().Get (), newValue);
}

template <>
inline GS::ErrCode Value<double>::SetRegistryValue (GSPref::IRoot* rootKey, const double& newValue)
{
	const GS::UniString valueAsString = GS::UniString::Printf ("%lf", newValue);
	return rootKey->SetStringValue (keyPath.ToCStr ().Get (), valueName.ToCStr ().Get (), valueAsString);
}

}

#endif // PREFERENCESHANDLING_HPP