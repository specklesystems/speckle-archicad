#include "LibpartPlacer.h"
#include "APIHelper.hpp"
#include "Box3DData.h"
#include <CheckError.h>
#include <SpeckleConversionException.h>
#include <iostream>
#include <Connector.h>
#include <ACAPI_Environment.h>

#include <filesystem>
#include "StopWatch.h"

namespace fs = std::filesystem;

std::vector<std::pair<std::string, std::string>> LibpartPlacer::CollectFiles(const std::string& folderPath)
{
	std::vector<std::pair<std::string, std::string>> files;

	try {
		for (const auto& entry : fs::directory_iterator(folderPath)) {
			if (fs::is_regular_file(entry.path())) {
				files.emplace_back(entry.path().filename().string(), entry.path().string());
			}
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error accessing folder: " << e.what() << std::endl;
	}

	return files;
}

API_LibPart LibpartPlacer::Create(const std::string& path, const std::string& fn)
{
	GSErrCode err = NoError;

	IO::Location rab(path.c_str());
	GS::Array<API_LibraryInfo> libInfo;
	IO::Location* loc = nullptr;

	API_LibPart libPart{};
	Int32 embeddedLibraryIndex = -1;

	if (ACAPI_LibraryManagement_GetLibraries(&libInfo, &embeddedLibraryIndex) == NoError && embeddedLibraryIndex >= 0)
	{
		try
		{
			loc = new IO::Location(libInfo[embeddedLibraryIndex].location);
			err = loc->AppendToLocal(IO::Name(fn.c_str()));
			err = IO::fileSystem.Copy(rab, *loc);

			BNZeroMemory(&libPart, sizeof(API_LibPart));
			libPart.typeID = APILib_ObjectID;
			libPart.location = loc;
		}
		catch (std::bad_alloc&)
		{
			std::cout << "Could not get location" << std::endl;
		}
	}

	if (err != NoError)
	{
		std::cout << "Error in Create()" << std::endl;
	}

	return libPart;
}

API_DatabaseInfo LibpartPlacer::GetCurrentDB()
{
	API_DatabaseInfo databaseInfo;
	BNZeroMemory(&databaseInfo, sizeof(API_DatabaseInfo));
	GSErrCode err = ACAPI_Database_GetCurrentDatabase(&databaseInfo);

	if (err != NoError)
		databaseInfo.typeID = API_ZombieWindowID;

	return databaseInfo;
}

void LibpartPlacer::SetCurrentDB(API_DatabaseInfo& databaseInfo)
{
	GSErrCode err = ACAPI_Database_ChangeCurrentDatabase(&databaseInfo);
	if (err != NoError)
		return;
}

void LibpartPlacer::SwitchToFloorPlanDB()
{
	API_DatabaseInfo databaseInfo;
	BNZeroMemory(&databaseInfo, sizeof(API_DatabaseInfo));
	databaseInfo.typeID = APIWind_FloorPlanID;
	SetCurrentDB(databaseInfo);
}

std::string LibpartPlacer::PlaceLibpart(GS::Int32 libIndex)
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

void LibpartPlacer::PlaceLibparts(const std::vector<Int32>& libIndices)
{
	ACAPI_CallUndoableCommand("Placing received objects",
		[&]() -> GSErrCode {
			LibraryHelper helper(false);
			auto originalDB = GetCurrentDB();
			SwitchToFloorPlanDB();

			int placed = 0;
			for (const auto& idx : libIndices)
			{
				try
				{
					std::string elemId = PlaceLibpart(idx);
					placed++;
					CONNECTOR.GetProcessWindow().SetProcessValue(placed);
				}
				catch (const std::exception& ex)
				{
					std::cout << "Could not place LibPart: " << ex.what();
				}
			}

			SetCurrentDB(originalDB);
			return NoError;
		});
}

void LibpartPlacer::AddLibparts()
{
	std::string t;
	std::vector<Int32> libIndices;
	std::vector<Int32> libIndices0;

	SW.Start();

	auto files = CollectFiles("C:\\poc\\out");
	GS::Array<API_LibPart> libparts;

	for (const auto& f : files)
	{
		auto part = Create(f.second, f.first);
		libparts.Push(part);
		libIndices0.push_back(part.index);
	}

	GSErrCode err = ACAPI_LibraryPart_RegisterAll(&libparts);
	if (err != NoError)
	{
		std::cout << "Error registering LibParts." << std::endl;
	}

	for (const auto& p : libparts)
	{
		libIndices.push_back(p.index);
	}

	PlaceLibparts(libIndices);

	t = SW.Stop();
	std::cout << t;
}

void LibpartPlacer::SetLibs()
{
	GS::Array<API_LibraryInfo> libInfo;

	if (ACAPI_LibraryManagement_GetLibraries(&libInfo) == NoError)
	{
		API_LibraryInfo li;
		li.location = IO::Location("C:\\gsm\\in");
		libInfo.Push(li);

		ACAPI_LibraryManagement_SetLibraries(&libInfo);
	}
}

