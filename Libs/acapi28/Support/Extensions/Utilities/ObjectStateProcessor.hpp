
#if !defined (OBJECTSTATEPROCESSOR_HPP)
#define OBJECTSTATEPROCESSOR_HPP

#pragma once

// --- Includes --------------------------------------------------------------------------------------------------------

// from JSON
#include	"JSON/Value.hpp"

// from JSONConversion
#include	"JSON/ObjectStateJSONConversion.hpp"

// from GSXMLUtils
#include	"GSXMLConversion.hpp"

// from GSRoot
#include	"GSPref.hpp"
#include	"HashSet.hpp"
#include	"ObjectState.hpp"
#include	"String.hpp"
#include	"UniString.hpp"
#include	"FileSystem.hpp"


// --- Predeclarations -------------------------------------------------------------------------------------------------

// --- Constant definitions --------------------------------------------------------------------------------------------

// --- Type definitions ------------------------------------------------------------------------------------------------

namespace Extensions {

namespace Utilities {


class ObjectStateProcessor : public GS::ObjectState::Processor
{
private:
	enum LastParentItemType {
		Array,
		Object
	};
	struct LastParent {
		LastParentItemType type;
		GS::String fieldName;
		LastParent (LastParentItemType lastType, const GS::String& lastFieldName) :
			type (lastType),
			fieldName (lastFieldName)
		{}
	};

	GS::ObjectState							os;
	GS::ArrayFB<GS::ObjectState, 8>			subObjects;
	GS::Array<GS::Array<GS::ObjectState>>	subLists;
	GS::Array<LastParent>					lastParentItems;
	GS::HashTable<GS::UniString, GS::Array<GS::Array<GS::ObjectState>>>	nestedSubListsHash;

	GS::HashSet<GS::UniString> fieldNamesToModify;
	GS::HashSet<GS::Pair<GS::UniString, GS::UniString>> modifierKeys;
	GS::HashTable<GS::Pair<GS::UniString,GS::UniString>, bool> boolValuesToModify;
	GS::HashTable<GS::Pair<GS::UniString,GS::UniString>, Int64> int64ValuesToModify;
	GS::HashTable<GS::Pair<GS::UniString,GS::UniString>, UInt64>uint64ValuesToModify;
	GS::HashTable<GS::Pair<GS::UniString,GS::UniString>, double> doubleValuesToModify;
	GS::HashTable<GS::Pair<GS::UniString, GS::UniString>, GS::UniString> stringValuesToModify;
	GS::HashTable<GS::Pair<GS::UniString, GS::UniString>, GS::ObjectState> subObjectValuesToModify;
	GS::HashTable<GS::Pair<GS::UniString, GS::UniString>, GS::Array<GS::ObjectState>> subListValuesToModify;
	
	template <class T*>
	void AddValue (const GS::Pair<GS::UniString, GS::UniString>& modifierKey, T* newValue) = delete;

	template <class T*>
	void AddValue (const GS::Pair<GS::UniString, GS::UniString>& modifierKey, const T* newValue) = delete;

	void AddValue (const GS::Pair<GS::UniString, GS::UniString>& modifierKey, const bool& newValue)
	{
		boolValuesToModify.Add (modifierKey, newValue);
	}

	void AddValue (const GS::Pair<GS::UniString, GS::UniString>& modifierKey, const Int64& newValue)
	{
		int64ValuesToModify.Add (modifierKey, newValue);
	}

	void AddValue (const GS::Pair<GS::UniString, GS::UniString>& modifierKey, const UInt64& newValue)
	{
		uint64ValuesToModify.Add (modifierKey, newValue);
	}

	void AddValue (const GS::Pair<GS::UniString, GS::UniString>& modifierKey, const double& newValue)
	{
		doubleValuesToModify.Add (modifierKey, newValue);
	}

	void AddValue (const GS::Pair<GS::UniString, GS::UniString>& modifierKey, const GS::UniString& newValue)
	{
		stringValuesToModify.Add (modifierKey, newValue);
	}

	void AddValue (const GS::Pair<GS::UniString, GS::UniString>& modifierKey, const GS::ObjectState& newValue)
	{
		subObjectValuesToModify.Add (modifierKey, newValue);
	}

	void AddValue (const GS::Pair<GS::UniString, GS::UniString>& modifierKey, const  GS::Array<GS::ObjectState>& newValue)
	{
		subListValuesToModify.Add (modifierKey, newValue);
	}

public:
	ObjectStateProcessor ();
	virtual ~ObjectStateProcessor ();
	
	GS::ObjectState& GetCopiedObjectState ();
	
	virtual void	BoolFound (const GS::String& fieldName, bool value) override;
	virtual void	IntFound (const GS::String& fieldName, Int64 value) override;
	virtual void	UIntFound (const GS::String& fieldName, UInt64 value) override;
	virtual void	RealFound (const GS::String& fieldName, double value) override;
	virtual void	StringFound (const GS::String& fieldName, const GS::UniString& value) override;
	virtual void	ObjectEntered (const GS::String& fieldName) override;
	virtual void	ObjectExited (const GS::String& fieldName) override;
	virtual void	ListEntered (const GS::String& fieldName) override;
	virtual void	ListExited (const GS::String& fieldName) override;

	template<class T>
	void AddValueToModify (const GS::String& fieldName, const GS::String& parentFieldName, const T& newValue)
	{
		GS::Pair<GS::UniString, GS::UniString> modifierKey (fieldName, parentFieldName);
		if (DBVERIFY (!modifierKeys.Contains (modifierKey) && !fieldName.IsEmpty () && !parentFieldName.IsEmpty ())) {
			fieldNamesToModify.Add (fieldName);
			modifierKeys.Add (modifierKey);
			AddValue (modifierKey, newValue);
		}
	}

	template<typename TKey, typename TValue>
	static void HashTableToObjectStateArray (const GS::HashTable<TKey, TValue>& hashTable, GS::Array<GS::ObjectState>& objectStateArray)
	{
		if (DBERROR (!objectStateArray.IsEmpty ()))
			objectStateArray.Clear ();

		for (auto it = hashTable.EnumeratePairs (); it != nullptr; ++it) {
			objectStateArray.PushNew ();
			GS::StorePair (objectStateArray.GetLast (), it->key, it->value);
		}
	}
};


GSErrCode	GetJSONFileLoc (IO::Location &location, bool askForFileDialog, bool forSave, const GS::UniString& jsonFilesFilterString = GS::UniString (), const GS::UniString& extensionString = GS::UniString ());
GSErrCode	WriteObjectStateToJSONFile (const GS::ObjectState& objectState, bool askForFileDialog);
GSErrCode	WriteObjectStateToJSONFile (const GS::ObjectState& objectState, const IO::Location& location);
GSErrCode	ReadObjectStateFromJSONFile (GS::ObjectState& objectState);

GSErrCode	WriteObjectStateToXMLFile (const GS::ObjectState& objectState, const IO::Location& location, const GS::String& topLevelTagName);
GSErrCode	ReadObjectStateFromXMLFile (const IO::Location location, const GS::String& topLevelTagName, GS::ObjectState& objectState);

}	// namespace Utilities

}	// namespace Extensions


// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------


#endif // OBJECTSTATEPROCESSOR_HPP
