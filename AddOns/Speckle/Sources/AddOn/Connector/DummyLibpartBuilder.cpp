#pragma warning(disable : 4996)

#include "DummyLibpartBuilder.h"
#include "APIEnvir.h"
#include "ACAPinc.h"
#include "APIHelper.hpp"

#include "BuiltInLibrary.hpp"
#include "FileSystem.hpp"
#include "Folder.hpp"
#include "GSUnID.hpp"

#include <ModelMaterial.hpp>
#include <AttributeIndex.hpp>

#include <iostream>
#include <chrono>
#include <thread>

static GSErrCode GetLocation(IO::Location*& loc, bool useEmbeddedLibrary)
{
	GS::Array<API_LibraryInfo>	libInfo;
	loc = nullptr;

	GSErrCode err = NoError;

	if (useEmbeddedLibrary) {
		Int32 embeddedLibraryIndex = -1;
		// get embedded library location
		if (ACAPI_LibraryManagement_GetLibraries(&libInfo, &embeddedLibraryIndex) == NoError && embeddedLibraryIndex >= 0) {
			loc = new IO::Location(libInfo[embeddedLibraryIndex].location);

			if (loc != nullptr) {
				IO::Location ownFolderLoc(*loc);
				ownFolderLoc.AppendToLocal(IO::Name("LibPart_Test Library"));
				err = IO::fileSystem.CreateFolder(ownFolderLoc);
				if (err == NoError || err == IO::FileSystem::TargetExists)
					loc->AppendToLocal(IO::Name("LibPart_Test Library"));
			}
		}
	}
	else {
		// register our own folder and create the library part in it
		if (ACAPI_LibraryManagement_GetLibraries(&libInfo) == NoError) {
			IO::Location folderLoc;
			API_SpecFolderID specID = API_UserDocumentsFolderID;
			ACAPI_ProjectSettings_GetSpecFolder(&specID, &folderLoc);
			folderLoc.AppendToLocal(IO::Name("LibPart_Test Library"));
			IO::Folder destFolder(folderLoc, IO::Folder::Create);
			if (destFolder.GetStatus() != NoError || !destFolder.IsWriteable())
				return APIERR_GENERAL;

			loc = new IO::Location(folderLoc);

			for (UInt32 ii = 0; ii < libInfo.GetSize(); ii++) {
				if (folderLoc == libInfo[ii].location)
					return NoError;
			}

			API_LibraryInfo		li;
			li.location = folderLoc;

			libInfo.Push(li);

			ACAPI_LibraryManagement_SetLibraries(&libInfo);
		}
	}

	return NoError;
}

// -----------------------------------------------------------------------------
//  Creates a simple Library Part
// -----------------------------------------------------------------------------

static GS::Int32 Do_CreateLibraryPart(void)
{
	LibraryHelper helper(false);

	GSErrCode err = NoError;

	API_LibPart libPart;
	libPart = {};
	libPart.typeID = APILib_ObjectID;
	libPart.isTemplate = false;
	libPart.isPlaceable = true;

	const GS::UnID unID = BL::BuiltInLibraryMainGuidContainer::GetInstance().GetUnIDWithNullRevGuid(BL::BuiltInLibPartID::ModelElementLibPartID);

	CHCopyC(unID.ToUniString().ToCStr(), libPart.parentUnID);	// Model Element subtype

	GSTimeRecord timeRecord;
	TIGetTimeRecord(0, &timeRecord, TI_CURRENT_TIME);
	UInt32 fraction = TIGetTicks() % TIGetTicksPerSec();
	GS::snuprintf(libPart.docu_UName, sizeof(libPart.docu_UName) / sizeof(GS::uchar_t), L("LPTest_%d-%02d-%02d_%02d%02d%02d_%d"),
		timeRecord.year, timeRecord.month, timeRecord.day, timeRecord.hour, timeRecord.minute, timeRecord.second, fraction);

	err = GetLocation(libPart.location, true);
	if (err != NoError) {
		return 0;
	}

	ACAPI_LibraryManagement_OverwriteLibPart((Int32)true);
	err = ACAPI_LibraryPart_Create(&libPart);
	ACAPI_LibraryManagement_OverwriteLibPart((Int32)false);

	if (err == NoError) {
		char buffer[1000];

		API_LibPartSection section;

		// Comment script section
		BNZeroMemory(&section, sizeof(API_LibPartSection));
		section.sectType = API_SectComText;
		ACAPI_LibraryPart_NewSection(&section);
		sprintf(buffer, "Library Part written by LibPart_Test add-on");
		ACAPI_LibraryPart_WriteSection(Strlen32(buffer), buffer);
		ACAPI_LibraryPart_EndSection();

		// Keyword section
		BNZeroMemory(&section, sizeof(API_LibPartSection));
		section.sectType = API_SectKeywords;
		ACAPI_LibraryPart_NewSection(&section);
		sprintf(buffer, "API LibPart_Test");
		ACAPI_LibraryPart_WriteSection(Strlen32(buffer), buffer);
		ACAPI_LibraryPart_EndSection();

		// Copyright section
		BNZeroMemory(&section, sizeof(API_LibPartSection));
		section.sectType = API_SectCopyright;
		ACAPI_LibraryPart_NewSection(&section);
		sprintf(buffer, "LibPart_Test");	// Author
		ACAPI_LibraryPart_WriteSection(Strlen32(buffer), buffer);
		ACAPI_LibraryPart_EndSection();

		// Master script section
		BNZeroMemory(&section, sizeof(API_LibPartSection));
		section.sectType = API_Sect1DScript;
		ACAPI_LibraryPart_NewSection(&section);
		buffer[0] = '\0';
		ACAPI_LibraryPart_WriteSection(Strlen32(buffer), buffer);
		ACAPI_LibraryPart_EndSection();

		// 3D script section
		BNZeroMemory(&section, sizeof(API_LibPartSection));
		section.sectType = API_Sect3DScript;
		ACAPI_LibraryPart_NewSection(&section);
		sprintf(buffer, "MATERIAL mat%s%s", GS::EOL, GS::EOL);
		ACAPI_LibraryPart_WriteSection(Strlen32(buffer), buffer);
		sprintf(buffer, "BLOCK a, b, 1%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(Strlen32(buffer), buffer);
		sprintf(buffer, "ADD a * 0.5, b* 0.5, 1%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(Strlen32(buffer), buffer);
		sprintf(buffer, "CYLIND zzyzx - 3, MIN (a, b) * 0.5%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(Strlen32(buffer), buffer);
		sprintf(buffer, "ADDZ zzyzx - 3%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(Strlen32(buffer), buffer);
		sprintf(buffer, "CONE 2, MIN (a, b) * 0.5, 0.0, 90, 90%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(Strlen32(buffer), buffer);
		ACAPI_LibraryPart_EndSection();

		// 2D script section
		BNZeroMemory(&section, sizeof(API_LibPartSection));
		section.sectType = API_Sect2DScript;
		ACAPI_LibraryPart_NewSection(&section);
		sprintf(buffer, "PROJECT2 3, 270, 2%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(Strlen32(buffer), buffer);
		ACAPI_LibraryPart_EndSection();

		// Parameter script section
		BNZeroMemory(&section, sizeof(API_LibPartSection));
		section.sectType = API_SectVLScript;
		ACAPI_LibraryPart_NewSection(&section);
		sprintf(buffer, "VALUES \"zzyzx\" RANGE [6,]%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(Strlen32(buffer), buffer);
		ACAPI_LibraryPart_EndSection();

		// Parameters section
		BNZeroMemory(&section, sizeof(API_LibPartSection));
		section.sectType = API_SectParamDef;

		short nPars = 4;
		API_AddParType** addPars = reinterpret_cast<API_AddParType**>(BMAllocateHandle(nPars * sizeof(API_AddParType), ALLOCATE_CLEAR, 0));
		API_AddParType* pAddPar = &(*addPars)[0];
		pAddPar->typeID = APIParT_Mater;
		pAddPar->typeMod = 0;
		CHTruncate("mat", pAddPar->name, sizeof(pAddPar->name));
		GS::ucscpy(pAddPar->uDescname, L("Material"));
		pAddPar->value.real = 1;

		pAddPar = &(*addPars)[1];
		pAddPar->typeID = APIParT_Length;
		pAddPar->typeMod = 0;
		CHTruncate("len", pAddPar->name, sizeof(pAddPar->name));
		GS::ucscpy(pAddPar->uDescname, L("Length"));
		pAddPar->value.real = 2.5;

		pAddPar = &(*addPars)[2];
		pAddPar->typeID = APIParT_CString;
		pAddPar->typeMod = 0;
		CHTruncate("myStr", pAddPar->name, sizeof(pAddPar->name));
		GS::ucscpy(pAddPar->uDescname, L("String parameter"));
		GS::ucscpy(pAddPar->value.uStr, L("this is a string"));

		pAddPar = &(*addPars)[3];
		pAddPar->typeID = APIParT_RealNum;
		pAddPar->typeMod = API_ParArray;
		pAddPar->dim1 = 3;
		pAddPar->dim2 = 4;
		CHTruncate("matrix", pAddPar->name, sizeof(pAddPar->name));
		GS::ucscpy(pAddPar->uDescname, L("Array parameter with real numbers"));
		pAddPar->value.array = BMAllocateHandle(pAddPar->dim1 * pAddPar->dim2 * sizeof(double), ALLOCATE_CLEAR, 0);
		double** arrHdl = reinterpret_cast<double**>(pAddPar->value.array);
		for (Int32 k = 0; k < pAddPar->dim1; k++)
			for (Int32 j = 0; j < pAddPar->dim2; j++)
				(*arrHdl)[k * pAddPar->dim2 + j] = (k == j ? 1.1 : 0.0);

		double aa = 1.0;
		double bb = 1.0;
		GSHandle sectionHdl = nullptr;
		ACAPI_LibraryPart_GetSect_ParamDef(&libPart, addPars, &aa, &bb, nullptr, &sectionHdl);

		API_LibPartDetails details;
		BNZeroMemory(&details, sizeof(API_LibPartDetails));
		details.object.autoHotspot = false;
		ACAPI_LibraryPart_SetDetails_ParamDef(&libPart, sectionHdl, &details);

		ACAPI_LibraryPart_AddSection(&section, sectionHdl, nullptr);

		BMKillHandle(reinterpret_cast<GSHandle*>(&arrHdl));
		BMKillHandle(reinterpret_cast<GSHandle*>(&addPars));
		BMKillHandle(&sectionHdl);

		IO::Location    	folderLoc;
		API_SpecFolderID	specID = API_UserDocumentsFolderID;
		ACAPI_ProjectSettings_GetSpecFolder(&specID, &folderLoc);

		if (libPart.location != nullptr) {
			delete libPart.location;
			libPart.location = nullptr;
		}


		auto save_start = std::chrono::high_resolution_clock::now();

		// Save the constructed library part
		if (err == NoError)
			err = ACAPI_LibraryPart_Save(&libPart);

		auto save_end = std::chrono::high_resolution_clock::now();
		auto save = ((std::chrono::duration<double>)(save_end - save_start)).count();
		std::cout << "Elapsed time: " << save << " seconds\n";

		if (libPart.location != nullptr) {
			delete libPart.location;
			libPart.location = nullptr;
		}
	}
	return libPart.index;
}		// Do_CreateLibraryPart

void DummyLibpartBuilder::Build()
{
	Do_CreateLibraryPart();
}
