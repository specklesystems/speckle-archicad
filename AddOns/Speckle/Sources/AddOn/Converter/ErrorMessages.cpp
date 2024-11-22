#include "ErrorMessages.h"

std::string ErrorMessages::Get(const int errCode)
{
	switch (errCode)
	{
		case -7004:			return "The operation has been canceled by the user";
		case -2130313215:	return "General error code.";
		case -2130313214:	return "Insufficient memory.";
		case -2130313213:	return "The operation has been canceled by the user, in case of a long process.";

		case -2130313115:	return "The passed identifier is not a valid one, or valid, but not proper for the given operation.";
		case -2130313114:	return "The passed index is out of range.";
		case -2130313113:	return "The passed name is not proper or not found in the existing list.";
		case -2130313112:	return "The passed parameters are inconsistent.";
		case -2130313111:	return "The passed polygon cannot be interpreted.";
		case -2130313110:	return "The command cannot be executed on the current database.";
		case -2130313109:	return "The command cannot be executed while the current window is active.";
		case -2130313108:	return "The key code cannot be found in the listing database.";
		case -2130313107:	return "The passed platform sign is not valid.";
		case -2130313106:	return "The plane equation is incorrect.";
		case -2130313105:	return "The passed user ID (TeamWork client) is not valid.";
		case -2130313104:	return "The passed autotext value is not valid.";
		case -2130313103:	return "The function cannot be applied to the passed element type.";
		case -2130313102:	return "The passed polygon or polyline is irregular.";
		case -2130313101:	return "The passed expression string is syntactically incorrect.";
		case -2130313100:	return "The passed guid is invalid or valid, but not proper for the given operation.";

		case -2130313015:	return "There is no 3D information assigned to the passed element.";
		case -2130313014:	return "No more database items can be returned.";
		case -2130313013:	return "There is no open project. The operation cannot be executed without an open project.";
		case -2130313012:	return "No library was loaded. The operation cannot be executed without a loaded library.";
		case -2130313011:	return "The requested LibPart section is not found.";
		case -2130313010:	return "No selection. The operation cannot be executed without any element selected.";
		case -2130313009:	return "The referenced element is not editable.";
		case -2130313008:	return "The specified first library part unique ID does not refer to a subtype of the second unique ID.";
		case -2130313007:	return "The main GUID parts of the specified two library part unique IDs are not equal.";
		case -2130313006:	return "The main GUID parts of the specified two library part unique IDs are equal but their revision IDs differ.";
		case -2130313005:	return "There is no open project, or not in Teamwork mode.";

		case -2130312996:	return "Attempt to get user data assigned to an element, but there isn’t any.";
		case -2130312995:	return "The user data cannot be assigned to the element, since there is no free storage block avaliable.";
		case -2130312994:	return "The link already exists.";
		case -2130312993:	return "The link doesn’t exist.";
		case -2130312992:	return "The window to be opened already exists.";
		case -2130312991:	return "The referenced window does not exist.";
		case -2130312990:	return "No undoable entry has got into the opened undo operation.";
		case -2130312989:	return "The reference already exists.";
		case -2130312988:	return "The resource must have a unique name but the specified one is already taken.";

		case -2130312915:	return "The attribute already exists.";
		case -2130312914:	return "Reference to a deleted, purged or non-existent database item.";
		case -2130312913:	return "The referenced layer is locked.";
		case -2130312912:	return "The referenced layer is hidden.";
		case -2130312911:	return "The passed floor index is out of range.";
		case -2130312910:	return "The database item is not in the user’s workspace.";
		case -2130312909:	return "Can’t access / create / modify / delete an item in a teamwork server.";
		case -2130312908:	return "The property for the passed element or attribute is not available.";
		case -2130312907:	return "Can’t set the classification for the passed element or attribute.";

		case -2130312815:	return "The referenced add-on is not installed.";
		case -2130312814:	return "The target add-on is the caller add-on.";
		case -2130312813:	return "The referenced command is not supported by the target add-on.";
		case -2130312812:	return "The requested command version is newer than the version of the command that the target add-on can support.";
		case -2130312811:	return "No custom data section is saved into the project file identified by the add-on’s unique ID.";

		case -2130312715:	return "Two or more paragraphs are overlapped. The end offset of one is greater than the beginner offset of the next one.";
		case -2130312714:	return "Number of paragraphs – the size of paragraphs handle – is zero.";
		case -2130312713:	return "Paragraph end offset is run over the content length.";
		case -2130312712:	return "The content string contains line end character (CR) at invalid position (inside the paragraph range).";
		case -2130312706:	return "Two or more runs are overlapped. The end offset of one is greater than the beginner offset of the next one.";
		case -2130312705:	return "Number of runs – the size of run pointer – is zero.";
		case -2130312704:	return "Run end offset is run over the content length.";
		case -2130312703:	return "The beginner offset of one is greater than the end offset of the previous one.";
		case -2130312702:	return "Attempted to overwrite a protected text run (not used yet).";
		case -2130312696:	return "The EOL array is not a monotonous ascendant sequence.";
		case -2130312686:	return "The tabulator array is not a monotonous ascendant sequence.";

		case -2130312315:	return "The command needs initialization by an other API call.";
		case -2130312314:	return "The API function is not reentrant. Nesting occurred.";
		case -2130312313:	return "The command is not supported by the server application. It is not environment dependent. The server application cannot execute the command generally.";
		case -2130312312:	return "The passed identifier is not subject to the operation.";
		case -2130312311:	return "The command cannot be executed with the passed parameters.";
		case -2130312310:	return "The specified location is read-only.";
		case -2130312309:	return "The invoked Teamwork service has failed.";
		case -2130312308:	return "The invoked undoable command threw an exception.";
		case -2130312307:	return "The called command should be encapsulated in a ACAPI_CallUndoableCommand scope.";

		case -2130312215:	return "The function is not implemented yet.";
		case -2130312214:	return "The originating library part file is missing. The document name is still filled.";

		default:			return "Unknown error code: " + std::to_string(errCode);
	}
}
