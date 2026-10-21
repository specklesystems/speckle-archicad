// *********************************************************************************************************************
// Description:		Dumping Model3D structures into file in different formats
//
// Module:			Modeler
// Namespace:		Modeler
// Contact person:	MA
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GS_MODELER_DUMP_FILE)
#define GS_MODELER_DUMP_FILE

#pragma once

#include "Model3DExport.h"

#include "Owner.hpp"
#include "UniString.hpp"


namespace IO {
	class File;
}


namespace Modeler {


class MeshBody;


class MODEL3D_DLL_EXPORT DumpFile {
public:
	enum NotificationLevel {SilentMode, NotifyIfFileOpened};

	class MODEL3D_DLL_EXPORT FullPath : public GS::UniString {
	public:
		FullPath (const char* str);
		FullPath (const GS::UniString & str);
		virtual ~FullPath ();
	};

private:
	GS::Owner<IO::File>		file;
	static Int32			dumpFileGlobalCounter;
	NotificationLevel		notificationLevel;

	void CreateFile (GS::UniString fileName);
	void CreateFile (FullPath fileName);

	bool IsFileOpened ();

	void FinalizeFile ();

public:
	// IO::File creation methods
	DumpFile ();
	DumpFile (GS::UniString fileName, NotificationLevel notificationLevel = SilentMode);
	DumpFile (FullPath fileName, NotificationLevel notificationLevel = SilentMode);

	DumpFile& NewFile (GS::UniString fileName, NotificationLevel newNotificationLevel = SilentMode);
	DumpFile& NewFile (FullPath fileName, NotificationLevel newNotificationLevel = SilentMode);

	static void RemoveFile (FullPath fileName);
	// and helper(s)

	static GS::UniString Decorate (GS::UniString fileName);


	// Open and write file
	void WriteGDL (const MeshBody& body);
	void WriteCPP (const MeshBody& body);
	void WriteXML (const MeshBody& body);
	void Printf (const char * format, ...);

	static void WriteBodyGDL (GS::UniString fileName, const MeshBody& body, NotificationLevel notificationLevel = SilentMode);
	static void WriteBodyCPP (GS::UniString fileName, const MeshBody& body, NotificationLevel notificationLevel = SilentMode);
	static void WriteBodyXML (GS::UniString fileName, const MeshBody& body, NotificationLevel notificationLevel = SilentMode);

	// cleanup
	~DumpFile ();
};

} // namespace Modeler {

#endif
