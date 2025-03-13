#include "LibpartBuilder.h"
#include "APIHelper.hpp"
#include "Box3DData.h"
#include <CheckError.h>
#include <SpeckleConversionException.h>
#include <iostream>

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

	CHECK_ERROR(ACAPI_Element_Create(&element, &elementMemo));
	ACAPI_DisposeElemMemoHdls(&elementMemo);

	std::string elementId = APIGuidToString(element.header.guid).ToCStr().Get();
	return elementId;
}

void LibpartBuilder::CreateLibPart(const UnpackedElement& element)
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

	Box3D box = Box3D::CreateEmpty();

	// add vertices
	UInt32 vertexCount = static_cast<UInt32>(element.vertices.size());
	for (UInt32 vertexIndex = 0; vertexIndex < vertexCount; vertexIndex++)
	{
		double x = element.vertices[vertexIndex].x;
		double y = element.vertices[vertexIndex].y;
		double z = element.vertices[vertexIndex].z;

		line = GS::String::SPrintf("VERT %f, %f, %f\t!#%u%s", (float)x, (float)y, (float)z, vertexIndex + 1, GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		box.Extend(Point3D(x, y, z));
	}

	line = GS::String::SPrintf("%s", GS::EOL);
	ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());

	// add faces
	UInt32 currentEdge = 1;
	UInt32 faceCount = static_cast<UInt32>(element.faces.size());
	for (UInt32 faceIndex = 0; faceIndex < faceCount; faceIndex++)
	{
		Face face = element.faces[faceIndex];
		GS::UniString matName = face.materialName.c_str();
		line = GS::String::SPrintf("! Polygon #%u%s%sMATERIAL \"%s\"%s", faceIndex + 1, GS::EOL, GS::EOL, matName.ToCStr().Get(), GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());

		UInt32 edgeCount = static_cast<UInt32>(face.vertexCount);
		for (UInt32 edgeIndex = 0; edgeIndex < edgeCount; edgeIndex++)
		{
			Edge edge = face.edges[edgeIndex];
			UInt32 start = static_cast<UInt32>(edge.start + 1);
			UInt32 end = static_cast<UInt32>(edge.end + 1);

			line = GS::String::SPrintf("EDGE %d, %d, -1, -1, %s\t!#%u%s", start, end, "hiddenBodyEdge", currentEdge++, GS::EOL);
			//line = GS::String::SPrintf("EDGE %d, %d, -1, -1, %s\t!#%u%s", start, end, "visibleBodyEdge", currentEdge++, GS::EOL);
			ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		}

		line = GS::String::SPrintf("PGON %u, 0, -1", edgeCount);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		currentEdge -= edgeCount;
		for (UInt32 i = 0; i < edgeCount; i++)
		{
			line = GS::String::SPrintf(",%s%u", " ", currentEdge++);
			ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
		}

		line = GS::String::SPrintf("\t!#%u%s%s", faceIndex + 1, GS::EOL, GS::EOL);
		ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());
	}

	line = GS::String::SPrintf("BODY 4%s%s", GS::EOL, GS::EOL);
	ACAPI_LibraryPart_WriteSection(line.GetLength(), line.ToCStr());

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
		throw SpeckleConversionException("Could not set LibPart parameters section");
	}

	// Save the constructed library part
	CHECK_ERROR(ACAPI_LibraryPart_Save(&libPart));
	libpartIndices.push_back(libPart.index);
	_elementCount++;
}

void LibpartBuilder::CreateLibParts(const std::vector<UnpackedElement>& elements)
{
	ACAPI_CallUndoableCommand("Creating received objects",
		[&]() -> GSErrCode {
			LibraryHelper helper(false);
			
			for (const auto& elem : elements)
			{
				// Hack for very large objects (SketchUp)
				if (elem.faces.size() > 100000)
				{
					// this is not good
					continue;
				}

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

			for (const auto& idx : libpartIndices)
			{
				try
				{
					std::string elemId = PlaceLibpart(idx);
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
