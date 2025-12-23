
#include "ObjectStateProcessor.hpp"

// from DG
#include "DGModule.hpp"

// from GSXMLUtils
#include "GSXMLConversion.hpp"
#include "GSXMLInterface.hpp" 


// --- Predeclarations -------------------------------------------------------------------------------------------------

// --- Type definitions ------------------------------------------------------------------------------------------------


// --- Variable definitions --------------------------------------------------------------------------------------------

// --- Function definitions --------------------------------------------------------------------------------------------

// =====================================================================================================================
//
// Main Function group
//
// =====================================================================================================================


Extensions::Utilities::ObjectStateProcessor::ObjectStateProcessor ()
{
}


Extensions::Utilities::ObjectStateProcessor::~ObjectStateProcessor ()
{
}


GS::ObjectState& Extensions::Utilities::ObjectStateProcessor::GetCopiedObjectState ()
{
	return os;
}


void	Extensions::Utilities::ObjectStateProcessor::BoolFound (const GS::String& fieldName, bool value)
{
	bool newValue = value;
	if (fieldNamesToModify.Contains (fieldName)) {
		for (auto it = lastParentItems.Enumerate (); it != nullptr; ++it) {
			GS::Pair<GS::UniString, GS::UniString> actKey (fieldName, (*it).fieldName);
			bool boolData;
			if (boolValuesToModify.Get (actKey, &boolData)) {
				newValue = boolData;
				break;
			}
		}
	}

	if (!subLists.IsEmpty () && lastParentItems.GetLast ().type == Array) {
		GS::ObjectState os;
		os.Add (fieldName, newValue);
		subLists.GetLast ().Push (os);
		return;
	}

	if (!subObjects.IsEmpty ()) {
		subObjects.GetLast ().Add (fieldName, newValue);
		return;
	}

	os.Add (fieldName, newValue);
}


void	Extensions::Utilities::ObjectStateProcessor::IntFound (const GS::String& fieldName, Int64 value)
{
	Int64 newValue = value;
	if (fieldNamesToModify.Contains (fieldName)) {
		for (auto it = lastParentItems.Enumerate (); it != nullptr; ++it) {
			GS::Pair<GS::UniString, GS::UniString> actKey (fieldName, (*it).fieldName);
			Int64 int64Data;
			if (int64ValuesToModify.Get (actKey, &int64Data)) {
				newValue = int64Data;
				break;
			}
		}
	}

	if (!subLists.IsEmpty () && lastParentItems.GetLast ().type == Array) {
		GS::ObjectState os;
		os.Add (fieldName, newValue);
		subLists.GetLast ().Push (os);
		return;
	}

	if (!subObjects.IsEmpty ()) {
		subObjects.GetLast ().Add (fieldName, newValue);
		return;
	}

	os.Add (fieldName, newValue);
}


void	Extensions::Utilities::ObjectStateProcessor::UIntFound (const GS::String& fieldName, UInt64 value)
{
	UInt64 newValue = value;
	if (fieldNamesToModify.Contains (fieldName)) {
		for (auto it = lastParentItems.Enumerate (); it != nullptr; ++it) {
			GS::Pair<GS::UniString, GS::UniString> actKey (fieldName, (*it).fieldName);
			UInt64 uint64Data;
			if (uint64ValuesToModify.Get (actKey, &uint64Data)) {
				newValue = uint64Data;
				break;
			}
		}
	}

	if (!subLists.IsEmpty () && lastParentItems.GetLast ().type == Array) {
		GS::ObjectState os;
		os.Add (fieldName, newValue);
		subLists.GetLast ().Push (os);
		return;
	}

	if (!subObjects.IsEmpty ()) {
		subObjects.GetLast ().Add (fieldName, newValue);
		return;
	}

	os.Add (fieldName, newValue);
}


void	Extensions::Utilities::ObjectStateProcessor::RealFound (const GS::String& fieldName, double value)
{
	double newValue = value;
	if (fieldNamesToModify.Contains (fieldName)) {
		for (auto it = lastParentItems.Enumerate (); it != nullptr; ++it) {
			GS::Pair<GS::UniString, GS::UniString> actKey (fieldName, (*it).fieldName);
			double doubleData;
			if (doubleValuesToModify.Get (actKey, &doubleData)) {
				newValue = doubleData;
				break;
			}
		}
	}

	if (!subLists.IsEmpty () && lastParentItems.GetLast ().type == Array) {
		GS::ObjectState os;
		os.Add (fieldName, newValue);
		subLists.GetLast ().Push (os);
		return;
	}

	if (!subObjects.IsEmpty ()) {
		subObjects.GetLast ().Add (fieldName, newValue);
		return;
	}

	os.Add (fieldName, newValue);
}


void	Extensions::Utilities::ObjectStateProcessor::StringFound (const GS::String& fieldName, const GS::UniString& value)
{
	GS::UniString newValue = value;
	if (fieldNamesToModify.Contains (fieldName)) {
		for (auto it = lastParentItems.Enumerate (); it != nullptr; ++it) {
			GS::Pair<GS::UniString, GS::UniString> actKey (fieldName, (*it).fieldName);
			GS::UniString stringData;
			if (stringValuesToModify.Get (actKey, &stringData)) {
				newValue = stringData;
				break;
			}
		}
	}

	if (!subLists.IsEmpty () && lastParentItems.GetLast ().type == Array) {
		GS::ObjectState os;
		os.Add (fieldName, newValue);
		subLists.GetLast ().Push (os);
		return;
	}

	if (!subObjects.IsEmpty ()) {
		subObjects.GetLast ().Add (fieldName, newValue);
		return;
	}

	os.Add (fieldName, newValue);
}

void	Extensions::Utilities::ObjectStateProcessor::ObjectEntered (const GS::String& fieldName) 
{
	lastParentItems.Push (LastParent (Object, fieldName));
	subObjects.Push (GS::ObjectState ());
}

void	Extensions::Utilities::ObjectStateProcessor::ObjectExited (const GS::String& fieldName)
{
	lastParentItems.Pop ();

	GS::ObjectState subObj = subObjects.Pop ();
	if (fieldNamesToModify.Contains (fieldName)) {
		for (auto it = lastParentItems.Enumerate (); it != nullptr; ++it) {
			GS::Pair<GS::UniString, GS::UniString> actKey (fieldName, (*it).fieldName);
			GS::ObjectState newValue;
			if (subObjectValuesToModify.Get (actKey, &newValue)) {
				subObj = newValue;
				break;
			}
		}
	}

	if (!subLists.IsEmpty () && lastParentItems.GetLast ().type == Array) {
		subLists.GetLast ().Push (subObj);
		return;
	}

	if (!subObjects.IsEmpty ()) {
		subObjects.GetLast ().Add (fieldName, subObj);
		return;
	}

	os.Add (fieldName, subObj);
}

void	Extensions::Utilities::ObjectStateProcessor::ListEntered (const GS::String& fieldName)
{
	lastParentItems.Push (LastParent (Array, fieldName));
	GS::Array<GS::ObjectState> sublist;
	subLists.Push (sublist);
}

void	Extensions::Utilities::ObjectStateProcessor::ListExited (const GS::String& fieldName)
{
	lastParentItems.Pop ();

	GS::Array<GS::ObjectState> subList = subLists.Pop ();
	if (fieldNamesToModify.Contains (fieldName)) {
		for (auto it = lastParentItems.Enumerate (); it != nullptr; ++it) {
			GS::Pair<GS::UniString, GS::UniString> actKey (fieldName, (*it).fieldName);
			if (subListValuesToModify.ContainsKey (actKey)) {
				subList = subListValuesToModify[actKey];
				break;
			}
		}
	}

	GS::HashSet<GS::ObjectState::Type> types;
	GS::HashSet<GS::String> fieldNames;
	GS::String singleFieldName;
	GS::UniString key (fieldName);
	if (subList.GetSize () > 0) {
		for (auto it = subList.Enumerate (); it != nullptr; ++it) {
			GS::ObjectState tempOs (*it);
			tempOs.EnumerateFields ([&](const GS::String& fieldName) {
				types.Add (tempOs.GetType (fieldName));
				fieldNames.Add (fieldName);
				singleFieldName = fieldName;
			});
		}
	}
	
	GS::ObjectState::Type specificType = GS::ObjectState::Bool;
	if (types.GetSize () > 1 || fieldNames.GetSize () > 1) {
		specificType = GS::ObjectState::Type::Object;	//simple Object type, containing multiple types and different fields - do nothing with it, keep this ObjectState as it is.
	} else if (types.GetSize () == 1) {
			for (auto it = types.Enumerate (); it != nullptr; ++it)
				specificType = *it;

			if (lastParentItems.GetLast ().type == Array && specificType == GS::ObjectState::Object) {
				specificType = GS::ObjectState::Type::List;	//this is an Array within an Array which contains Objects -> this is not just an Object, and might need to be stored within the nestedSubListsHash with its fieldName "key", not withing the subLists
			}
	} else {	//the current sublist is empty
		if (nestedSubListsHash.GetSize () > 0 && nestedSubListsHash.ContainsKey (key) && nestedSubListsHash.Get (key).GetSize () > 0) {	// if it is the empty parent object of fieldName stored within nestedSubListsHash
			specificType = GS::ObjectState::Type::List;
		} else {	//then it doesn't really matter, empty list is just an empty list.
			DBVERIFY (subList.IsEmpty () && types.IsEmpty ());
			specificType = GS::ObjectState::Type::Bool; 
		}
	}	

	switch (specificType) {
		case GS::ObjectState::Bool:
		{
			GS::Array<bool> valueArray;
			for (auto it = subList.Enumerate (); it != nullptr; ++it) {
				bool value = false;
				(*it).Get (singleFieldName, value, false);
				valueArray.Push (value);
			}

			if (subLists.GetSize () > 1 && lastParentItems.GetLast ().type == Array)
				subLists.GetLast ().GetLast ().Add (fieldName, valueArray);
			else if (!subObjects.IsEmpty ())
				subObjects.GetLast ().Add (fieldName, valueArray);
			else
				os.Add (fieldName, valueArray);

			break;
		}
		case GS::ObjectState::UInt:
		{
			GS::Array<UInt64> valueArray;
			for (auto it = subList.Enumerate (); it != nullptr; ++it) {
				UInt64 value = 0;
				(*it).Get (singleFieldName, value, 0);
				valueArray.Push (value);
			}

			if (subLists.GetSize () > 1 && lastParentItems.GetLast ().type == Array)
				subLists.GetLast ().GetLast ().Add (fieldName, valueArray);
			else if (!subObjects.IsEmpty ())
				subObjects.GetLast ().Add (fieldName, valueArray);
			else
				os.Add (fieldName, valueArray);

			break;
		}
		case GS::ObjectState::Int:
		{
			GS::Array<Int64> valueArray;
			for (auto it = subList.Enumerate (); it != nullptr; ++it) {
				Int64 value = 0;
				(*it).Get (singleFieldName, value, 0);
				valueArray.Push (value);
			}

			if (subLists.GetSize () > 1 && lastParentItems.GetLast ().type == Array)
				subLists.GetLast ().GetLast ().Add (fieldName, valueArray);
			else if (!subObjects.IsEmpty ())
				subObjects.GetLast ().Add (fieldName, valueArray);
			else
				os.Add (fieldName, valueArray);
			break;
		}
		case GS::ObjectState::Real:
		{
			GS::Array<double> valueArray;
			for (auto it = subList.Enumerate (); it != nullptr; ++it) {
				double value = 0.0;
				(*it).Get (singleFieldName, value, 0.0);
				valueArray.Push (value);
			}

			if (subLists.GetSize () > 1 && lastParentItems.GetLast ().type == Array)
				subLists.GetLast ().GetLast ().Add (fieldName, valueArray);
			else if (!subObjects.IsEmpty ())
				subObjects.GetLast ().Add (fieldName, valueArray);
			else
				os.Add (fieldName, valueArray);
			break;
		}
		case GS::ObjectState::String:
		{
			GS::Array<GS::UniString> valueArray;
			for (auto it = subList.Enumerate (); it != nullptr; ++it) {
				GS::UniString value, defValue;
				(*it).Get (singleFieldName, value, defValue);
				valueArray.Push (value);
			}

			if (subLists.GetSize () > 1 && lastParentItems.GetLast ().type == Array)
				subLists.GetLast ().GetLast ().Add (fieldName, valueArray);
			else if (!subObjects.IsEmpty ())
				subObjects.GetLast ().Add (fieldName, valueArray);
			else
				os.Add (fieldName, valueArray);
			break;
		}
		case GS::ObjectState::Object:
		{
			if (subLists.GetSize () > 1 && lastParentItems.GetLast ().type == Array) {
				subLists.GetLast ().GetLast ().Add (fieldName, subList);
			} else if (!subObjects.IsEmpty ()) {
				subObjects.GetLast ().Add (fieldName, subList);
			} else {
				os.Add (fieldName, subList);
			}
			break;
		}
		case GS::ObjectState::List:
		{
			if (subLists.GetSize () > 1 && lastParentItems.GetLast ().type == Array) {
				if (!subLists.GetLast ().IsEmpty ()) {
					subLists.GetLast ().GetLast ().Add (fieldName, subList);
				} else {
					nestedSubListsHash.Add (key, GS::Array<GS::Array<GS::ObjectState>> ());
					nestedSubListsHash[key].Push (subList);
				}
			} else if (!subObjects.IsEmpty ()) {
				if (nestedSubListsHash.ContainsKey (key)) {
					subObjects.GetLast ().Add (fieldName, nestedSubListsHash.Get (key));
					nestedSubListsHash.Delete (key);
				} else {
					subObjects.GetLast ().Add (fieldName, subList);
				}
			} else {
				if (nestedSubListsHash.ContainsKey (key)) {
					os.Add (fieldName, nestedSubListsHash.Get (key));
					nestedSubListsHash.Delete (key);
				} else {
					os.Add (fieldName, subList);
				}
			}
			break;
		}
		default:
			DBBREAK ();
			break;
	}
}


// =============================================================================
//
// Write json Schema and Result to a file - add the location with Save Dialog
//
// =============================================================================
GSErrCode	Extensions::Utilities::GetJSONFileLoc (IO::Location &location, bool askForFileDialog, bool forSave, const GS::UniString& jsonFilesFilterString, const GS::UniString& extensionString)
{
	static IO::Location	lastResultFile;
	if (askForFileDialog || lastResultFile.IsEmpty ()) {
		static IO::Location	lastFolder;
		if (lastFolder.IsEmpty ())
			IO::fileSystem.GetSpecialLocation (IO::FileSystem::UserDocuments, &lastFolder);

		// Browse for file
		DG::FileDialog	fileDialog (forSave ? DG::FileDialog::Save : DG::FileDialog::OpenFile);
		FTM::FileTypeManager ftm ("ObjectStateProcessor");
		FTM::GroupID lesGroup = ftm.AddGroup ("");

		GS::UniString filter;
		GS::UniString extension;
		if (!jsonFilesFilterString.IsEmpty ())
			filter = jsonFilesFilterString;
		else
			filter = "JSON Files";

		if (!extensionString.IsEmpty ())
			extension = extensionString;
		else
			extension = "json";
		
		FTM::FileType typeJSON (filter.ToCStr (), extension.ToCStr (), 0, 0, 0);
		FTM::TypeID idJSON = FTM::FileTypeManager::SearchForType (typeJSON);
		if (idJSON == FTM::UnknownType)
			idJSON = ftm.AddType (typeJSON);
		ftm.AddTypeToGroup (idJSON, lesGroup);

		fileDialog.AddFilter (idJSON);
		fileDialog.SetFilterRoot (lesGroup);

		fileDialog.SetFolder (lastFolder);

		if (!fileDialog.Invoke ())
			return Error;

		fileDialog.GetFolder (&lastFolder);
		location = fileDialog.GetSelectedFile ();
		if (forSave)
			lastResultFile = location;
	} else {
		location = lastResultFile;
	}

	return NoError;
}


// =============================================================================
//
// Write ObjectState into a file - add the location with Save Dialog
//
// =============================================================================
GSErrCode	Extensions::Utilities::WriteObjectStateToJSONFile (const GS::ObjectState& objectState, bool askForFileDialog)
{
	//Define a location to export the json file
	IO::Location loc;
	if (GetJSONFileLoc (loc, askForFileDialog, true) != NoError)
		return NoError;	//Cancel button was clicked - user does not want to export
	if (loc.IsEmpty ())
		return Error;	// Ok button was clicked without a location

	return WriteObjectStateToJSONFile (objectState, loc);	//export could not run
}		/* WriteObjectStateToJSONFile */



// =============================================================================
//
// Write ObjectState into a file - with given location
//
// =============================================================================
GSErrCode	Extensions::Utilities::WriteObjectStateToJSONFile (const GS::ObjectState& objectState, const IO::Location& location)
{
	if (location.IsEmpty () || objectState.IsEmpty ())
		return Error;

	//print out resultString
	IO::File file (location, IO::File::Create);
	if (file.GetStatus () == NoError && file.Open (IO::File::WriteEmptyMode) == NoError) {
		GSErrCode err = JSON::CreateFromObjectState (objectState, file, true);
		file.Close ();
		return err; //export is finished
	}
	return Error;	//export could not run
}		/* WriteObjectStateToJSONFile */


// =============================================================================
//
// Read JSON file to an ObjectState - add the location with Open Dialog
//
// =============================================================================
GSErrCode	Extensions::Utilities::ReadObjectStateFromJSONFile (GS::ObjectState& objectState)
{
	//Define a location to export the json file
	IO::Location loc;
	if (GetJSONFileLoc (loc, true, false) != NoError)
		return NoError;	//Cancel button was clicked - user does not want to export
	if (loc.IsEmpty ())
		return Error;	// Ok button was clicked without a location

						//print out resultString
	if (objectState.IsEmpty ()) {
		IO::File file (loc, IO::File::Fail);
		if (file.GetStatus () == NoError && file.Open (IO::File::ReadMode) == NoError) {
			GSErrCode err = JSON::ConvertToObjectState (file, objectState);
			file.Close ();
			return err;	//import is finished
		}
	}
	return Error;	//import could not run
}		/* ReadObjectStateFromJSONFile */


// =============================================================================
//
// Write ObjectState into a file - with given location
//
// =============================================================================
GSErrCode	Extensions::Utilities::WriteObjectStateToXMLFile (const GS::ObjectState& objectState, const IO::Location& location, const GS::String& topLevelTagName)
{
	if (location.IsEmpty () || objectState.IsEmpty ())
		return Error;

	GSErrCode err = NoError;

	GS::XMLOChannel* ox = GSXML::CreateXMLOChannel (location, topLevelTagName.ToCStr ());
	if (ox != nullptr) {
		err = GSXML::CreateFromObjectState (objectState, *ox);
		GSXML::DisposeXMLOChannel (ox);
	}

	return err;
}		/* WriteObjectStateToXMLFile */


// =============================================================================
//
// Read XML file to an ObjectState
//
// =============================================================================
GSErrCode	Extensions::Utilities::ReadObjectStateFromXMLFile (const IO::Location 	location,
															   const GS::String& 	topLevelTagName,
															   GS::ObjectState& 	objectState)
{
	GSErrCode err = NoError;

	GS::XMLIChannel* ix = GSXML::CreateXMLIChannel (location, topLevelTagName.ToCStr ());
	if (ix != nullptr) {
		err = GSXML::ConvertToObjectState (*ix, objectState);
		GSXML::DisposeXMLIChannel (ix);
	}

	return err;
}		/* ReadObjectStateFromXMLFile */
