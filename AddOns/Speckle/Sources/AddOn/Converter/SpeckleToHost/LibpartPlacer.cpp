#include "LibpartPlacer.h"
#include "APIHelper.hpp"
#include "Box3DData.h"
#include <CheckError.h>
#include <SpeckleConversionException.h>
#include <iostream>
#include <Connector.h>
#include <ACAPI_Environment.h>

#include <thread>
#include <chrono>

#include "StopWatch.h"
#include <set>

namespace fs = std::filesystem;

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

std::vector<Int32> LibpartPlacer::RegisterLibparts(const std::string& libraryFolderPath)
{
	SW.Start();
	
	GS::Array<API_LibPart> libparts;
	std::vector<Int32> libIndices;
	auto filePaths = CollectFilePaths(libraryFolderPath);

	for (const auto& path : filePaths)
	{
		auto libPart = CreateLibPartFromFile(path);
		libparts.Push(libPart);
	}

	GSErrCode err = ACAPI_LibraryPart_RegisterAll(&libparts);
	if (err != NoError)
	{
		std::cout << "Error registering LibParts." << std::endl;
	}

	for (const auto& libPart : libparts)
	{
		libIndices.push_back(libPart.index);
	}

	std::string elapsed = SW.Stop();
	std::cout << elapsed;

	return libIndices;
}

std::vector<std::filesystem::path> LibpartPlacer::CollectFilePaths(const std::string& folderPath)
{
	std::vector<std::filesystem::path> files;

	try 
	{
		for (const auto& entry : fs::directory_iterator(folderPath)) 
		{
			if (fs::is_regular_file(entry.path())) 
			{
				//files.emplace_back(entry.path().filename().string(), entry.path().string());
				files.emplace_back(entry.path());
			}
		}
	}
	catch (const std::exception& e) 
	{
		std::cerr << "Error accessing folder: " << e.what() << std::endl;
	}

	return files;
}

#include <filesystem>

API_LibPart LibpartPlacer::CreateLibPartFromFile(const std::filesystem::path& filePath)
{
	GSErrCode err = NoError;

	IO::Location gsmFileLocation(filePath.string().c_str());
	GS::Array<API_LibraryInfo> libInfo;
	IO::Location* embeddedLibraryLocation = nullptr;

	API_LibPart libPart{};
	Int32 embeddedLibraryIndex = -1;

	std::string fileName = filePath.filename().string();

	if (ACAPI_LibraryManagement_GetLibraries(&libInfo, &embeddedLibraryIndex) == NoError && embeddedLibraryIndex >= 0)
	{
		try
		{
			embeddedLibraryLocation = new IO::Location(libInfo[embeddedLibraryIndex].location);
			err = embeddedLibraryLocation->AppendToLocal(IO::Name(fileName.c_str()));
			err = IO::fileSystem.Copy(gsmFileLocation, *embeddedLibraryLocation);

			BNZeroMemory(&libPart, sizeof(API_LibPart));
			libPart.typeID = APILib_ObjectID;
			libPart.location = embeddedLibraryLocation;
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

/*API_LibPart LibpartPlacer::CreateLibPartFromFile(const std::string& filePath, const std::string& fileName)
{
	GSErrCode err = NoError;

	IO::Location gsmFileLocation(filePath.c_str());
	GS::Array<API_LibraryInfo> libInfo;
	IO::Location* embeddedLibraryLocation = nullptr;

	API_LibPart libPart{};
	Int32 embeddedLibraryIndex = -1;

	if (ACAPI_LibraryManagement_GetLibraries(&libInfo, &embeddedLibraryIndex) == NoError && embeddedLibraryIndex >= 0)
	{
		try
		{
			embeddedLibraryLocation = new IO::Location(libInfo[embeddedLibraryIndex].location);
			err = embeddedLibraryLocation->AppendToLocal(IO::Name(fileName.c_str()));
			err = IO::fileSystem.Copy(gsmFileLocation, *embeddedLibraryLocation);

			BNZeroMemory(&libPart, sizeof(API_LibPart));
			libPart.typeID = APILib_ObjectID;
			libPart.location = embeddedLibraryLocation;
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
}*/
