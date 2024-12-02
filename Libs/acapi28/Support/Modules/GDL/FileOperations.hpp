// *****************************************************************************
// File:			File Operations.hpp
//
// Description:		File operations for GDL Add-on.
//
// Contact person:	MAM
// *****************************************************************************

#ifndef	FILEOPERATIONS_HPP
#define FILEOPERATIONS_HPP

// from GSRoot
#include "RSTypes.hpp"
#include "HashSet.hpp"

// from IO
#include "File.hpp"
#include "FileTypeManager.hpp"

// from GSUtils
#include "comProc.h"

// from GDL
#include "GDLDefs.h"
#include "GDLExport.h"


namespace GDL
{
	namespace FileErrorCodes {
		enum {
			ERCREATE	= -1,	// Create error
			EROPEN		= -2, 	// Open error
			ERFNFINPUT	= -3,	// File not found, can't open for input
			ERREAD		= -4,	// Read error
			ERWRITE		= -5,	// Write error
			ERCLOSE		= -6,	// Close error
			ERMEMORY	= -7,	// Data extension memory full error
			ERUNKNOWN	= -8,	// Unknown file type
			ERLIBOPEN	= -9,	// File not found in the library
			ERPARAMLIST	= -10	// Wrong parameter list
		};
	}

class FileInfoRec
{
public:
	GS::UniString	identStr;
	IO::Location	location;

	FileInfoRec ();
	~FileInfoRec () {};
	bool operator== (const FileInfoRec& b) const;
	bool operator!= (const FileInfoRec& b) const;

	GSErrCode	Read (GS::IChannel& ic);
	GSErrCode	Write (GS::OChannel& oc) const;
};


class GDL_DLL_EXPORT FileInfoDB
{
private:
	GS::Array<FileInfoRec> fileInfoList;

protected:
	FileInfoDB ();

public:
	virtual ~FileInfoDB ();
	void SetHandle (GSHandle* optionsHandle);
	bool Find (const GS::UniString& fileIDStr, IO::Location* pFileLoc) const;
	void Store (const GS::UniString& fileIDStr, const IO::Location& fileLoc);
	void Extract (GSHandle* optionsHandle);

	virtual void Dummy (void);	// dummy function -> for mac build
};


class GDL_DLL_EXPORT FileOperations
{
private:
	GDL_ScriptType				scriptType;
	MessageProc*				reportProc;

protected:
	GDL_ScriptType		GetScriptType (void) const { return scriptType; }
	void				WriteReport (const GS::UniString& reportText);

	GSErrCode			OpenFileNoCheck (const IO::Location& location, IO::File::OnNotFound action, IO::File::OpenMode openMode, IO::File** ppFile);
	GSErrCode			MoveFileWithOverwriteNoCheck (const IO::Location& from, const IO::Location& to);

public:

class GDL_DLL_EXPORT FileAlertStrings {
public:
	GS::UniString strings[6]; //titleText, largeText, smallText, button1, button2, button3

	FileAlertStrings () {};
	void	FillStrings (GSResModule resModule, short resID, const GS::UniString& fileName);
};

	FileOperations ();
	virtual ~FileOperations ();

	void				SetScriptType (GDL_ScriptType inScriptType) { scriptType = inScriptType; }
	void				SetReportProc (MessageProc* inReportProc) { reportProc = inReportProc; }

	virtual GSErrCode	OpenFile (const IO::Location& location, IO::File::OnNotFound action, IO::File::OpenMode openMode, IO::File** ppFile);
	virtual GSErrCode	CloseFile (IO::File** ppFile);
	virtual GSErrCode	MoveFileWithOverwrite (const IO::Location& from, const IO::Location& to);

	short				GetFileFromRefList (FileInfoDB& fileInfoDB,
											GSHandle* optionhdl,
											const GS::UniString& fileIDStr,
											IO::File::OpenMode openMode,
											IO::Location* pFileLoc,
											const GS::UniString& titleString,
											FileAlertStrings* alertStrings = nullptr,
											GS::Array<FTM::TypeID>* fileTypeFilters = nullptr);

	virtual bool		GetFile (	const GS::UniString& fileIDStr,
									IO::File::OpenMode openMode,
									IO::Location* pFileLoc,
									const GS::UniString& titleString,
									FileAlertStrings* alertStrings = nullptr,
									GS::Array<FTM::TypeID>* fileTypeFilters = nullptr);

	short				GetFolderFromRefList (FileInfoDB& fileInfoDB,
												GSHandle* optionhdl,
												const GS::UniString& folderIDStr,
												IO::Location* pFolderLoc,
												FileAlertStrings* alertStrings = nullptr);

	virtual bool		GetFolder (const GS::UniString&	folderIDStr,
									IO::Location*	pFolderLoc,
									FileAlertStrings* alertStrings = nullptr);

static 	GS::UniString		GetNamedTitleString (GSResModule resModule, short resID, short stringID, const GS::UniString& fileName);

};

}

#endif // FILEOPERATIONS_HPP