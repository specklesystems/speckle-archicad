#include "LibpartBuilder.h"
#include "APIHelper.hpp"
#include "Box3DData.h"
#include <CheckError.h>
#include <SpeckleConversionException.h>
#include <iostream>
#include <Connector.h>

static API_DatabaseInfo GetCurrentDB(void)
{
	API_DatabaseInfo databaseInfo;
	BNZeroMemory(&databaseInfo, sizeof(API_DatabaseInfo));
	GSErrCode err = ACAPI_Database_GetCurrentDatabase(&databaseInfo);

	if (err != NoError)
	{
		databaseInfo.typeID = API_ZombieWindowID;
	}

	return databaseInfo;
}

static void SetCurrentDB(API_DatabaseInfo& databaseInfo)
{
	GSErrCode err = ACAPI_Database_ChangeCurrentDatabase(&databaseInfo);
	if (err != NoError)
	{
		return;
	}
}

static void SwitchToFloorPlanDB()
{
	API_DatabaseInfo databaseInfo;
	BNZeroMemory(&databaseInfo, sizeof(API_DatabaseInfo));
	databaseInfo.typeID = APIWind_FloorPlanID;
	SetCurrentDB(databaseInfo);
}

static GSErrCode CreateSubFolder(const GS::UniString& name, IO::Location& location)
{
	GSErrCode err = NoError;

	if (location.IsEmpty() || name.IsEmpty())
	{
		return err;
	}

	IO::Name folderName(name);
	IO::Folder folder(location);

	GSErrCode folderExistsErr = -2130640378;
	err = folder.CreateFolder(folderName);
	if (err == NoError)
	{
		location.AppendToLocal(folderName);
	}
	else if (err == folderExistsErr)
	{
		location.AppendToLocal(folderName);
		{
			LibraryHelper helper(false);
			err = ACAPI_LibraryManagement_DeleteEmbeddedLibItem(&location, false, true);
		}
		LibraryHelper helper(true);
		err = folder.CreateFolder(folderName);
	}

	return err;
}

LibpartBuilder::LibpartBuilder(const std::string& baseGroupName) : _baseGroupName(baseGroupName)
{
	GetLocation();
}

void LibpartBuilder::GetLocation()
{
	GS::Array<API_LibraryInfo>	libInfo;
	IO::Location* loc = nullptr;

	Int32 embeddedLibraryIndex = -1;
	// get embedded library location
	if (ACAPI_LibraryManagement_GetLibraries(&libInfo, &embeddedLibraryIndex) == NoError && embeddedLibraryIndex >= 0)
	{
		try
		{
			loc = new IO::Location(libInfo[embeddedLibraryIndex].location);
		}
		catch (std::bad_alloc&)
		{
			std::cout << "could not get location";
		}

		if (loc != nullptr)
		{
			GS::UniString folderName = _baseGroupName.c_str();
			CreateSubFolder(folderName, *loc);
		}
	}

	_location = loc;
}

std::string LibpartBuilder::PlaceLibpart(GS::Int32 libIndex)
{
	API_Element element;
	BNZeroMemory(&element, sizeof(API_Element));
	element.header.type.typeID = API_ObjectID;

	API_ElementMemo elementMemo;
	BNZeroMemory(&elementMemo, sizeof(API_ElementMemo));
	CHECK_ERROR(ACAPI_Element_GetDefaults(&element, &elementMemo));

	element.object.libInd = libIndex;
	element.object.pos.x = 0;
	element.object.pos.y = 0;
	element.object.level = 0;
	element.object.xRatio = 1.0;
	element.object.yRatio = 1.0;

	API_StoryVisibility vis;
	vis.showAllAbove = true;
	vis.showAllBelow = true;
	vis.showOnHome = true;
	element.object.visibility = vis;

	CHECK_ERROR(ACAPI_Element_Create(&element, &elementMemo));
	ACAPI_DisposeElemMemoHdls(&elementMemo);

	std::string elementId = APIGuidToString(element.header.guid).ToCStr().Get();
	return elementId;
}

void LibpartBuilder::CreateLibPart(const ArchicadElement& element)
{
	API_LibPart libPart{};
	BNZeroMemory(&libPart, sizeof(API_LibPart));
	libPart.typeID = APILib_ObjectID;
	libPart.isTemplate = false;
	libPart.isPlaceable = true;
	libPart.location = _location;

	// todo use Speckle types here
	const GS::UnID unID = BL::BuiltInLibraryMainGuidContainer::GetInstance().GetUnIDWithNullRevGuid(BL::BuiltInLibPartID::BuildingElementLibPartID);
	CHCopyC(unID.ToUniString().ToCStr(), libPart.parentUnID);

	GS::ucscpy(libPart.docu_UName, GS::UniString::SPrintf("Speckle Object %u", _elementCount).ToUStr());

	ACAPI_LibraryManagement_OverwriteLibPart((void*)(Int32)true);
	CHECK_ERROR(ACAPI_LibraryPart_Create(&libPart));
	ACAPI_LibraryManagement_OverwriteLibPart((void*)(Int32)false);
	
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

	// create bodies
	for (const auto& mesh : element.archicadMeshes)
	{
		// add vertices
		UInt32 vertexIndex = 1;
		for (const auto& v : mesh.vertices)
		{
			line = GS::String::SPrintf("VERT %f, %f, %f\t!#%u%s", (float)v.x, (float)v.y, (float)v.z, vertexIndex++, GS::EOL);
			ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		}

		line = GS::String::SPrintf("%s", GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());

		// add edges
		UInt32 edgeIndex = 1;
		for (const auto& edge : mesh.edges)
		{
			UInt32 start = static_cast<UInt32>(edge.start);
			UInt32 end = static_cast<UInt32>(edge.end);
			UInt32 pgon1 = static_cast<UInt32>(edge.poly1);
			UInt32 pgon2 = static_cast<UInt32>(edge.poly2);
			GS::UniString edgeVisibility = edge.visibilityType.c_str();
			line = GS::String::SPrintf("EDGE %d, %d, %d, %d, %s\t!#%u%s", start, end, pgon1, pgon2, edgeVisibility.ToCStr().Get(), edgeIndex++, GS::EOL);
			ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		}

		// add polys
		UInt32 polyIndex = 1;
		for (const auto& p : mesh.polys)
		{
			GS::UniString matName = p.materialName.c_str();
			line = GS::String::SPrintf("%s! Polygon #%u%sMATERIAL \"%s\"%s", GS::EOL, polyIndex, GS::EOL, matName.ToCStr().Get(), GS::EOL);
			ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());

			// TODO normals (VECT) look OK in GDL script, but using them breaks polygons, needs investigation
			//line = GS::String::SPrintf("VECT %f, %f, %f%s", (float)p.normal.x, (float)p.normal.y, (float)p.normal.z, GS::EOL);
			//ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());

			UInt32 polySize = static_cast<UInt32>(p.size);
			line = GS::String::SPrintf("PGON %u, 0, -1", polySize);
			ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());

			++polyIndex;
			UInt32 edgeIndex = 1;
			for (const auto& edge : p.edges)
			{
				Int32 iEdge = static_cast<Int32>(edge);

				// add a linebreak after 10 items to avoid lines longer than 256 chars in the GDL script
				line = GS::String::SPrintf(",%s%d", (edgeIndex % 10 == 0) ? GS::EOL : " ", iEdge);
				ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
				++edgeIndex;
			}

			line = GS::String::SPrintf("%s", GS::EOL);
			ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		}

		line = GS::String::SPrintf("BODY 4%s%s%s", GS::EOL, "BASE", GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
	}

	line = "DEL TOP";
	ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());

	ACAPI_LibraryPart_EndSection();

	// 2D script section
	BNZeroMemory(&section, sizeof(API_LibPartSection));
	section.sectType = API_Sect2DScript;
	ACAPI_LibraryPart_NewSection(&section);
	line = GS::String::SPrintf("!%s", GS::EOL);
	ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());

	line = GS::String::SPrintf("cutPlaneHeight	= (GLOB_CSTORY_ELEV + GLOB_CUTPLANES_INFO[1]) - GLOB_HSTORY_ELEV%s", GS::EOL);
	ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
	line = GS::String::SPrintf("cutHeight = 0.01%s", GS::EOL);
	ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
	line = GS::String::SPrintf("iCutPlanes = 1%s", GS::EOL);
	ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
	line = GS::String::SPrintf("%sfor i = 1 to iCutPlanes%s", GS::EOL, GS::EOL);
	ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
	line = GS::String::SPrintf("\tput cutPlaneHeight + (i-1) * cutHeight%s", GS::EOL);
	ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
	line = GS::String::SPrintf("next i%s", GS::EOL);
	ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
	line = GS::String::SPrintf("%sfor i = 0 to iCutPlanes%s", GS::EOL, GS::EOL);
	ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());

	line = GS::String::SPrintf(
		"\tput 1+32,\t\t\t! method%s"
		"\t\t2,\t\t\t\t! parts%s"
		"\t\t1,\t\t\t\t! cutFillIndex%s"
		"\t\t1,\t\t\t\t! cutFillFgPen%s"
		"\t\t1,\t\t\t\t! cutFillBgPen%s"
		"\t\t0.0,\t\t\t! cutFillOrigoX%s"
		"\t\t0.0,\t\t\t! cutFillOrigoY%s"
		"\t\t0.0,\t\t\t! cutFillDirection%s"
		"\t\t1,\t\t\t\t! cutLinePen%s"
		"\t\t1,\t\t\t\t! cutLineType%s"
		"\t\t1,\t\t\t\t! projectedFillIndex%s"
		"\t\t1,\t\t\t\t! projectedFillFgPen%s"
		"\t\t1,\t\t\t\t! projectedFillBgPen%s"
		"\t\t0.0,\t\t\t! projectedFillOrigoX%s"
		"\t\t0.0,\t\t\t! projectedFillOrigoY%s"
		"\t\t0.0,\t\t\t! projectedFillDirection%s"
		"\t\t1,\t\t\t\t! projectedLinePen%s"
		"\t\t1\t\t\t\t! projectedLineType%s",
		GS::EOL, GS::EOL, GS::EOL, GS::EOL, GS::EOL, GS::EOL, GS::EOL, GS::EOL, GS::EOL, GS::EOL, GS::EOL, GS::EOL, GS::EOL, GS::EOL, GS::EOL, GS::EOL, GS::EOL, GS::EOL);
	ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());

	line = GS::String::SPrintf("next i%s", GS::EOL);
	ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());

	line = GS::String::SPrintf(
		"%sproject2{4} 3, 270,%s"
		"\t0,\t\t\t! useTransparency%s"
		"\t0,\t\t\t! statusParts%s"
		"\tiCutPlanes,\t! numCutplanes%s"
		"\tget (nsp)%s",
		GS::EOL, GS::EOL, GS::EOL, GS::EOL, GS::EOL);
	ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());


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
		throw SpeckleConversionException("Could not set LibPart parameters section");
	}

	// Save the constructed library part
	CHECK_ERROR(ACAPI_LibraryPart_Save(&libPart));
	libpartIndices.push_back(libPart.index);
	_elementCount++;
	CONNECTOR.GetProcessWindow().SetProcessValue(_elementCount);
}

void LibpartBuilder::CreateLibParts(const std::vector<ArchicadElement>& elements)
{
	ACAPI_CallUndoableCommand("Creating received objects",
		[&]() -> GSErrCode {
			LibraryHelper helper(false);
			
			for (const auto& elem : elements)
			{
				ReceiveConversionResult conversionResult{};

				try
				{
					CreateLibPart(elem);
				}
				catch (const std::exception& ex)
				{
					conversionResult.status = ConversionResultStatus::CONVERSION_ERROR;
					conversionResult.error.message = ex.what();
				}

				conversionResults.push_back(conversionResult);
			}
			return NoError;
		});
}

void LibpartBuilder::PlaceLibparts()
{
	ACAPI_CallUndoableCommand("Placing received objects",
		[&]() -> GSErrCode {
			LibraryHelper helper(false);
			auto originalDB = GetCurrentDB();
			SwitchToFloorPlanDB();

			int placed = 0;
			for (const auto& idx : libpartIndices)
			{
				try
				{
					std::string elemId = PlaceLibpart(idx);
					placed++;
					CONNECTOR.GetProcessWindow().SetProcessValue(placed);
					bakedObjectIds.push_back(elemId);
				}
				catch (const std::exception& ex)
				{
					std::cout << "Could not palce LibPart: " << ex.what();
				}
			}

			SetCurrentDB(originalDB);

			return NoError;
		});
}
