#pragma warning(disable : 4996)

#include "SpeckleToHostConverter.h"
#include "APIEnvir.h"
#include "ACAPinc.h"
#include "APIHelper.hpp"

#include "CheckError.h"
#include "ConverterUtils.h"

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

GSErrCode	SetLibPartAsDefaultObject(GS::Int32 idx)
{
	GSErrCode			err = NoError;
	API_Element			element;
	API_Element			mask;
	API_ElementMemo		memo;

	element = {};
	memo = {};

	element.header.type = API_ObjectID;

	API_ParamOwnerType paramOwner;
	BNZeroMemory(&paramOwner, sizeof(API_ParamOwnerType));
	paramOwner.libInd = idx;
	err = ACAPI_LibraryPart_OpenParameters(&paramOwner);
	if (err == NoError) {
		API_GetParamsType getParams;
		BNZeroMemory(&getParams, sizeof(API_GetParamsType));
		err = ACAPI_LibraryPart_GetActParameters(&getParams);
		if (err == NoError) {
			ACAPI_DisposeAddParHdl(&memo.params);
			memo.params = getParams.params;
		}
		ACAPI_LibraryPart_CloseParameters();
	}

	element.object.libInd = idx;
	ACAPI_ELEMENT_MASK_CLEAR(mask);
	ACAPI_ELEMENT_MASK_SET(mask, API_ObjectType, libInd);

	err = ACAPI_Element_ChangeDefaults(&element, &memo, &mask);
	if (err != NoError)
	{
		err = 0;
	}

	ACAPI_DisposeElemMemoHdls(&memo);

	return err;
}

static void Place(GS::Int32 libIndex)
{
	SetLibPartAsDefaultObject(libIndex);

	API_Element element;
	BNZeroMemory(&element, sizeof(API_Element));
	element.header.type.typeID = API_ObjectID;

	API_ElementMemo elementMemo;
	BNZeroMemory(&elementMemo, sizeof(API_ElementMemo));
	ACAPI_Element_GetDefaults(&element, &elementMemo);

	element.object.libInd = libIndex;
	element.object.pos.x = 0;
	element.object.pos.y = 0;
	element.object.level = 0;

	//ACAPI_Element_Create(&element, &elementMemo);

	GSErrCode err = (ACAPI_CallUndoableCommand("Create Morph",
		[&]() -> GSErrCode {
			return ACAPI_Element_Create(&element, &elementMemo);
		}));

	if (err != NoError)
	{
		libIndex = 0;
	}

	ACAPI_DisposeElemMemoHdls(&elementMemo);
}

std::string SpeckleToHostConverter::CreateLibPart(const Mesh& mesh, const int /*materialIndex*/, const std::string& baseGroupName, int runningNumber)
{
	auto total_start = std::chrono::high_resolution_clock::now();
	auto loc_start = std::chrono::high_resolution_clock::now();

	LibraryHelper helper(false);

	API_LibPart libPart{};
	GSErrCode err = NoError;
	BNZeroMemory(&libPart, sizeof(API_LibPart));
	libPart.typeID = APILib_ObjectID;
	libPart.isTemplate = false;
	libPart.isPlaceable = true;
	err = GetLocation(libPart.location, true);

	auto loc_end = std::chrono::high_resolution_clock::now();
	auto init_start = std::chrono::high_resolution_clock::now();
	// todo use Speckle types here
	const GS::UnID unID = BL::BuiltInLibraryMainGuidContainer::GetInstance().GetUnIDWithNullRevGuid(BL::BuiltInLibPartID::BuildingElementLibPartID);
	CHCopyC(unID.ToUniString().ToCStr(), libPart.parentUnID);

	GS::ucscpy(libPart.docu_UName, GS::UniString::SPrintf("Speckle Object %u", runningNumber).ToUStr());

	ACAPI_LibraryManagement_OverwriteLibPart((void*)(Int32)true);
	err = ACAPI_LibraryPart_Create(&libPart);
	ACAPI_LibraryManagement_OverwriteLibPart((void*)(Int32)false);
	if (err == NoError) {
		API_LibPartSection section;
		GS::String line;

		// Comment script section
		BNZeroMemory(&section, sizeof(API_LibPartSection));
		section.sectType = API_SectComText;
		ACAPI_LibraryPart_NewSection(&section);
		line = "Speckle";
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		ACAPI_LibraryPart_EndSection();

		// Keyword section
		BNZeroMemory(&section, sizeof(API_LibPartSection));
		section.sectType = API_SectKeywords;
		ACAPI_LibraryPart_NewSection(&section);
		line = "Speckle";
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		ACAPI_LibraryPart_EndSection();

		// Copyright section
		BNZeroMemory(&section, sizeof(API_LibPartSection));
		section.sectType = API_SectCopyright;
		ACAPI_LibraryPart_NewSection(&section);
		line = "Speckle Systems";	// Author
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		ACAPI_LibraryPart_EndSection();

		// Master script section
		BNZeroMemory(&section, sizeof(API_LibPartSection));
		section.sectType = API_Sect1DScript;
		ACAPI_LibraryPart_NewSection(&section);
		line = "";
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		ACAPI_LibraryPart_EndSection();

		// 3D script section
		BNZeroMemory(&section, sizeof(API_LibPartSection));
		section.sectType = API_Sect3DScript;
		ACAPI_LibraryPart_NewSection(&section);

		line = GS::String::SPrintf("!%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("! 3D Script (Generated by Speckle Connector)%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("!%s%s", GS::EOL, GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());

		line = GS::String::SPrintf("defaultResolution = 36%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("RESOL defaultResolution%s%s", GS::EOL, GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());

		line = GS::String::SPrintf("hiddenProfileEdge = 0%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("hiddenBodyEdge = 0%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("smoothBodyEdge = 0%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("visibleBodyEdge = 262144%s%s", GS::EOL, GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());

		line = GS::String::SPrintf("IF (GLOB_CONTEXT %% 10 >= 2 AND GLOB_CONTEXT %% 10 <= 4) AND showOnlyContourEdgesIn3D <> 0 THEN%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("\thiddenProfileEdge = 1%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("\thiddenBodyEdge = 1%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("\tsmoothBodyEdge = 2%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("ENDIF%s%s", GS::EOL, GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());

		line = GS::String::SPrintf("!%s%s", GS::EOL, GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("RESOL defaultResolution%s%s", GS::EOL, GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("XFORM map_xform[1][1], map_xform[2][1], map_xform[3][1], map_xform[4][1],%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("\tmap_xform[1][2], map_xform[2][2], map_xform[3][2], map_xform[4][2],%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("\tmap_xform[1][3], map_xform[2][3], map_xform[3][3], map_xform[4][3]%s%s", GS::EOL, GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());

		auto init_end = std::chrono::high_resolution_clock::now();
		auto verts_start = std::chrono::high_resolution_clock::now();

		Box3D box = Box3D::CreateEmpty();

		// add Vertices
		UInt32 vertexCount = static_cast<UInt32>(mesh.vertices.size() / 3);

		for (UInt32 i = 0; i < vertexCount; i++)
		{
			int vi = i * 3;
			double x = mesh.vertices[vi];
			double y = mesh.vertices[vi + 1];
			double z = mesh.vertices[vi + 2];

			line = GS::String::SPrintf("VERT %f, %f, %f\t!#%u%s", (float)x, (float)y, (float)z, i + 1, GS::EOL);
			ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
			box.Extend(Point3D(x, y, z));
		}

		line = GS::String::SPrintf("%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());

		auto verts_end = std::chrono::high_resolution_clock::now();

		auto edges_start = std::chrono::high_resolution_clock::now();
		// Add edges
		UInt32 edgeIndex = 1;
		UInt32 polygonIndex = 1;

		double ed_elps = 0.0;
		double poly_elps = 0.0;

		UInt32 mesh_size = (UInt32)mesh.faces.size();
		for (UInt32 i = 0; i < mesh_size;)
		{
			int polySize = mesh.faces[i];
			i++;
			std::vector<Int32> polygonEdges;

			//line = GS::String::SPrintf("! Polygon #%u%s%sMATERIAL \"%s\"%s", polygonIndex, GS::EOL, GS::EOL, materialName.ToCStr().Get(), GS::EOL);
			//ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());

			UInt32 poly_size = (UInt32)polySize;
			for (UInt32 j = 0; j < poly_size; j++)
			{
				Int32 start = mesh.faces[i + j];
				Int32 end = mesh.faces[i + (j + 1) % poly_size];

				bool smooth = false;
				bool hidden = true;

				auto ed_start = std::chrono::high_resolution_clock::now();

				line = GS::String::SPrintf("EDGE %d, %d, -1, -1, %s\t!#%u%s", start + 1, end + 1, (smooth ? "smoothBodyEdge" : (hidden ? "hiddenBodyEdge" : "visibleBodyEdge")), edgeIndex + i, GS::EOL);

				auto ed_end = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double> ed_elapsed = (ed_end - ed_start);
				ed_elps += ed_elapsed.count();

				auto poly_start = std::chrono::high_resolution_clock::now();

				ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());

				auto poly_end = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double> poly_elapsed = (poly_end - poly_start);
				poly_elps += poly_elapsed.count();

			}

			line = GS::String::SPrintf("PGON %u, 0, -1", poly_size);
			ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());

			for (UInt32 k = 0; k < poly_size; k++)
			{
				line = GS::String::SPrintf(",%s%u", ((k + 1) % 10 == 0 ? GS::EOL : " "), edgeIndex + k);
				ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
			}

			line = GS::String::SPrintf("\t!#%u%s%s", polygonIndex, GS::EOL, GS::EOL);
			ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());

			edgeIndex += polySize;
			polygonIndex++;
			i += poly_size;
		}

		std::cout << ed_elps;
		std::cout << poly_elps;

		line = GS::String::SPrintf("BODY 4%s%s", GS::EOL, GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());

		auto edges_end = std::chrono::high_resolution_clock::now();
		auto rest_start = std::chrono::high_resolution_clock::now();

		// add HotSpots
		line = GS::String::SPrintf("HOTSPOT %f, %f, %f%s", (float)box.GetMinX(), (float)box.GetMinY(), (float)box.GetMinZ(), GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("HOTSPOT %f, %f, %f%s", (float)box.GetMinX(), (float)box.GetMinY(), (float)box.GetMaxZ(), GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("HOTSPOT %f, %f, %f%s", (float)box.GetMinX(), (float)box.GetMaxY(), (float)box.GetMinZ(), GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("HOTSPOT %f, %f, %f%s", (float)box.GetMinX(), (float)box.GetMaxY(), (float)box.GetMaxZ(), GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("HOTSPOT %f, %f, %f%s", (float)box.GetMaxX(), (float)box.GetMinY(), (float)box.GetMinZ(), GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("HOTSPOT %f, %f, %f%s", (float)box.GetMaxX(), (float)box.GetMinY(), (float)box.GetMaxZ(), GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("HOTSPOT %f, %f, %f%s", (float)box.GetMaxX(), (float)box.GetMaxY(), (float)box.GetMinZ(), GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("HOTSPOT %f, %f, %f%s%s", (float)box.GetMaxX(), (float)box.GetMaxY(), (float)box.GetMaxZ(), GS::EOL, GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());

		line = "DEL TOP";
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());

		ACAPI_LibraryPart_EndSection();

		// 2D script section
		BNZeroMemory(&section, sizeof(API_LibPartSection));
		section.sectType = API_Sect2DScript;
		ACAPI_LibraryPart_NewSection(&section);
		line = GS::String::SPrintf("!%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("! 2D Script (Generated by Speckle Connector)%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("!%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("PEN gs_cont_pen%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("SET FILL gs_fill_type%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		line = GS::String::SPrintf("PROJECT2{2} 3, 270.0, 3+32, gs_back_pen, 0, 0, 0%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		ACAPI_LibraryPart_EndSection();

		// Parameter script section
		BNZeroMemory(&section, sizeof(API_LibPartSection));
		section.sectType = API_SectVLScript;
		ACAPI_LibraryPart_NewSection(&section);
		ACAPI_LibraryPart_EndSection();

		// Parameters section
		BNZeroMemory(&section, sizeof(API_LibPartSection));
		section.sectType = API_SectParamDef;

		short nPars = 3;
		API_AddParType** addPars = reinterpret_cast<API_AddParType**>(BMAllocateHandle(nPars * sizeof(API_AddParType), ALLOCATE_CLEAR, 0));
		if (addPars != nullptr)
		{
			API_AddParType* pAddPar = &(*addPars)[0];
			pAddPar->typeID = APIParT_Boolean;
			pAddPar->typeMod = 0;
			CHTruncate("showOnlyContourEdgesIn3D", pAddPar->name, sizeof(pAddPar->name));
			GS::ucscpy(pAddPar->uDescname, L("Show Only Contour Edges In 3D"));
			pAddPar->value.real = 1;

			pAddPar = &(*addPars)[1];
			pAddPar->typeID = APIParT_RealNum;
			pAddPar->typeMod = API_ParArray;
			pAddPar->dim1 = 4;
			pAddPar->dim2 = 3;
			CHTruncate("map_xform", pAddPar->name, sizeof(pAddPar->name));
			GS::ucscpy(pAddPar->uDescname, L("General Transformation"));
			pAddPar->value.array = BMAllocateHandle(pAddPar->dim1 * pAddPar->dim2 * sizeof(double), ALLOCATE_CLEAR, 0);
			double** arrHdl = reinterpret_cast<double**>(pAddPar->value.array);
			for (Int32 k = 0; k < pAddPar->dim1; k++)
				for (Int32 j = 0; j < pAddPar->dim2; j++)
					(*arrHdl)[k * pAddPar->dim2 + j] = (k == j ? 1.0 : 0.0);

			pAddPar = &(*addPars)[2];
			pAddPar->typeID = APIParT_Boolean;
			CHTruncate("AC_show2DHotspotsIn3D", pAddPar->name, sizeof(pAddPar->name));
			GS::ucscpy(pAddPar->uDescname, L("Show 2D Hotspots in 3D"));
			pAddPar->value.real = 0;

			double aa = 1.0;
			double bb = 1.0;
			GSHandle sectionHdl = nullptr;
			ACAPI_LibraryPart_GetSect_ParamDef(&libPart, addPars, &aa, &bb, nullptr, &sectionHdl);

			API_LibPartDetails details;
			BNZeroMemory(&details, sizeof(API_LibPartDetails));
			details.object.autoHotspot = false;
			details.object.fixSize = true;
			ACAPI_LibraryPart_SetDetails_ParamDef(&libPart, sectionHdl, &details);

			ACAPI_LibraryPart_AddSection(&section, sectionHdl, nullptr);

			BMKillHandle(reinterpret_cast<GSHandle*>(&arrHdl));
			BMKillHandle(reinterpret_cast<GSHandle*>(&addPars));
			BMKillHandle(&sectionHdl);
		}
		else
		{
			err = APIERR_MEMFULL;
		}

		auto rest_end = std::chrono::high_resolution_clock::now();
		auto save_start = std::chrono::high_resolution_clock::now();

		// Save the constructed library part
		if (err == NoError)
		{
			err = ACAPI_LibraryPart_Save(&libPart);

			if (true)
			{
				Place(libPart.index);
			}
		}

		auto save_end = std::chrono::high_resolution_clock::now();
		auto total_end = std::chrono::high_resolution_clock::now();

		auto total = ((std::chrono::duration<double>)(total_end - total_start)).count();
		auto init = ((std::chrono::duration<double>)(init_end - init_start)).count();
		auto verts = ((std::chrono::duration<double>)(verts_end - verts_start)).count();
		auto edges = ((std::chrono::duration<double>)(edges_end - edges_start)).count();
		auto rest = ((std::chrono::duration<double>)(rest_end - rest_start)).count();
		auto save = ((std::chrono::duration<double>)(save_end - save_start)).count();
		auto locat = ((std::chrono::duration<double>)(loc_end - loc_start)).count();
		
		auto dur = total + init + verts + edges + rest + save + locat;
		std::cout << "Elapsed time: " << dur << " seconds\n";
	}

	return baseGroupName;
}
