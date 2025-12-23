// ********************************************************************************************************************
// File:			TWClientUtilities.hpp
//
// Description:		Utilities for TeamWork Client Module
//
// Project:			TeamWork Client Module (TWClientLib)
//
// Namespace:		TWC
//
// Contact person:	CSZ
//
// SG compatible
// ********************************************************************************************************************

#ifndef TWCLIENTUTILITIES_HPP
#define TWCLIENTUTILITIES_HPP

#pragma once


// --- Includes -------------------------------------------------------------------------------------------------------
#include "TWClientExport.hpp"

	// from GSRoot
#include "String.hpp"
#include "PagedArray.hpp"

	// from TWRoot
#include "TWPermissionIDs.h"

	// from InputOutput
#include "Location.hpp"


namespace GS
{
	class XMLIChannel;
	class XMLOChannel;
}

namespace TWCB
{
	class SignalClient;

namespace Management {
namespace Entities {
	class ProjectFolder;
	typedef GS::Ref<ProjectFolder, GS::AtomicCounter> ProjectFolderRef;
}
}

namespace DataQuery {
	class DataQueryResult;
	typedef GS::Ref<DataQueryResult, GS::AtomicCounter> DataQueryResultRef;
}

}


namespace TWC {
namespace UI {
	class DataQueryResultCache;
	typedef GS::Ref<DataQueryResultCache, GS::AtomicCounter> DataQueryResultCacheRef;
}

namespace Mailbox {
	class UserContact;
}

}

// --- Declarations ---------------------------------------------------------------------------------------------------

namespace TWC {

typedef GS::Ref<GS::Exception, GS::AtomicCounter> ExceptionRef;


enum BIMServerType
{
	BST_BIMUnknown	= 0,
	BST_BIMCloud	= 1,
	BST_BIMServer	= 2
};

enum UserStatus
{
	OnlineUser		= 0,
	OfflineUser		= 1,
	ACOffBIMxOnUser = 2,
	BIMxOnlineUser	= 3,
	BIMxOfflineUser	= 4
};

struct ReshareStatus
{
	enum Value {
		Ok = 0,
		UnknownProject,
		MissingProject,
		LockedProject,
		ClosedProject,
		IncompatibleModelServer,
		LibraryNameError,
		FolderNameError,
		ChangeHostProject,
		FolderPermissionError
	};
};

namespace SessionAttributeNames {
	TWCLIENT_API	extern const GS::UniString ComputerName;
	TWCLIENT_API	extern const GS::UniString UserPreferencesData;
	TWCLIENT_API	extern const GS::UniString RevisionNumber;
	TWCLIENT_API	extern const GS::UniString TransactionCount;
	TWCLIENT_API	extern const GS::UniString VisitCount;
}

bool			TWCLIENT_API GetServerFriendlyName (const IO::Location& teamworkLocation, GS::UniString& friendlyName);
bool			TWCLIENT_API GetServerFriendlyName (const GS::UniString& serverUrl, GS::UniString& friendlyName);
bool			TWCLIENT_API GetServerUrl (const GS::UniString& serverAddress, GS::UniString& portalServerUrl);
bool			TWCLIENT_API GetServerLocation (const GS::UniString& portalServerUrl, IO::Location& portalServerLocation);
bool			TWCLIENT_API GetUserFullName (const IO::Location& teamworkLocation, GS::UniString& fullName); // TODO NB: Teszt
bool			TWCLIENT_API GetUserFullName (const GS::UniString& serverUrl, const GS::UniString& userName, GS::UniString& fullName);
GS::UniString	TWCLIENT_API GetRootFolderId ();
IO::Location	TWCLIENT_API GetRoamingProfileFolderLocation ();
bool			TWCLIENT_API FileExist (const IO::Location& location);

bool			TWCLIENT_API HasLibraryUploadToFolderPermission (const GS::HashSet<TWCB::PermissionID>* libraryParentFolderPermissions);
bool			TWCLIENT_API HasLibraryModifyInFolderPermission (const GS::HashSet<TWCB::PermissionID>* libraryParentFolderPermissions);
bool			TWCLIENT_API HasLibraryDeleteFromFolderPermission (const GS::HashSet<TWCB::PermissionID>* libraryParentFolderPermissions);
bool			TWCLIENT_API HasLibraryModifyPermission (const GS::HashSet<TWCB::PermissionID>* libraryPermissions);
bool			TWCLIENT_API HasLibraryDeletePermission (const GS::HashSet<TWCB::PermissionID>* libraryPermissions);

BIMServerType	TWCLIENT_API GetBIMServerType (const TWCB::DataQuery::DataQueryResult& serverData);
BIMServerType	TWCLIENT_API GetBIMServerType (const UI::DataQueryResultCache& serverData);
BIMServerType	TWCLIENT_API GetBIMServerType (const GS::UniString& serverTypeStr);
bool			TWCLIENT_API GetBIMServerTypeByUrl (const GS::UniString& serverUrl, BIMServerType& type);
bool			TWCLIENT_API IsServerActivated (const GS::UniString& serverUrl);
bool			TWCLIENT_API IsBIMCloud (const GS::UniString& serverUrl); 

UserStatus		TWCLIENT_API GetUserStatus (const TWCB::SignalClient* SignalClient, const TWC::Mailbox::UserContact* userContact);

ReshareStatus::Value	TWCLIENT_API ReshareCheck (const TWCB::Management::Entities::ProjectFolderRef& parentFolder,
												   const GS::UniString& projectName,
												   const TWC::UI::DataQueryResultCacheRef& serverData,
												   const GS::UniString& defaultModelServerId,
												   bool& projectFound,
												   GS::UniString& projectModelServerId,
												   ExceptionRef& checkException);

void			TWCLIENT_API InitTWClient (const GS::PagedArray <GS::UniString>& libraryFolderNames);
void			TWCLIENT_API CloseTWClient ();

class	InfoXMLsIChannel {
private:
	typedef GS::StringFB<16> StringType;

	IO::Location		xmlFileLoc;
	StringType			topLevelTagName;
	GS::XMLIChannel*	xmlIChannel;

public:
	InfoXMLsIChannel (const IO::Location& infoXMLFileLoc, const StringType& infoTopLevelTagName);
	~InfoXMLsIChannel ();

	GS::XMLIChannel*	Open (void);
	void				Close (void);
};


class	InfoXMLsOChannel {
private:
	typedef GS::StringFB<16> StringType;

	IO::Location		xmlFileLoc;
	StringType			topLevelTagName;
	GS::XMLOChannel*	xmlOChannel;

public:
	InfoXMLsOChannel (const IO::Location& infoXMLFileLoc, const StringType& infoTopLevelTagName);
	~InfoXMLsOChannel ();

	GS::XMLOChannel*	Open (void);
	void				Close (void);
};

}	// namespace TWC

#endif
