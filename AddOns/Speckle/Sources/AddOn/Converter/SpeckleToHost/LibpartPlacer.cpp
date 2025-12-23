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
#include <filesystem>
#include <string>

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

LibpartPlacer::LibpartPlacer(const std::string& baseGroupName) : _baseGroupName(baseGroupName)
{
	GetLocation();
}

void LibpartPlacer::GetLocation()
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
					bakedObjectIds.push_back(elemId);
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

	CONNECTOR.GetProcessWindow().SetProcessValue(1);
	for (const auto& path : filePaths)
	{
		auto libPart = CreateLibPartFromFile(path);
		libparts.Push(libPart);
	}

	CONNECTOR.GetProcessWindow().SetProcessValue(2);
	GSErrCode err = ACAPI_LibraryPart_RegisterAll(&libparts);
	if (err != NoError)
	{
		std::cout << "Error registering LibParts." << std::endl;
	}

	CONNECTOR.GetProcessWindow().SetProcessValue(3);
	for (const auto& libPart : libparts)
	{
		libIndices.push_back(libPart.index);
	}
	CONNECTOR.GetProcessWindow().SetProcessValue(4);

	std::string elapsed = SW.Stop();
	std::cout << elapsed;

	return libIndices;
}

std::vector<Int32> LibpartPlacer::RegisterLibpartsBatched(const std::string& libraryFolderPath)
{
	SW.Start();
	
	std::vector<Int32> libIndices;
	auto filePaths = CollectFilePaths(libraryFolderPath);

	USize batchCount = 1;

	if (filePaths.size() > 2000)
	{
		batchCount = 4;
	}
	else if (filePaths.size() > 10000)
	{
		batchCount = 10;
	}

	CONNECTOR.GetProcessWindow().SetNextProcessPhase("Registering GDL objects", batchCount);

	GS::Array<API_LibPart> allLibParts;
	for (const auto& path : filePaths)
	{
		auto libPart = CreateLibPartFromFile(path);
		allLibParts.Push(libPart);
	}

	const USize totalCount = allLibParts.GetSize();
	
	const USize batchSize = (totalCount + batchCount - 1) / batchCount; // Ceiling division

	for (USize i = 0; i < batchCount; ++i)
	{
		CONNECTOR.GetProcessWindow().SetProcessValue(i + 1);
		USize startIndex = i * batchSize;
		USize endIndex = std::min(startIndex + batchSize, totalCount);

		GS::Array<API_LibPart> batch;
		for (USize j = startIndex; j < endIndex; ++j)
		{
			batch.Push(allLibParts[j]);
		}

		CONNECTOR.GetProcessWindow().SetProcessValue(i + 1);
		GSErrCode err = ACAPI_LibraryPart_RegisterAll(&batch);
		if (err != NoError)
		{
			std::cout << "Error registering LibParts in batch " << i + 1 << "." << std::endl;
		}

		// Collect the indices after registration
		for (const auto& libPart : batch)
		{
			libIndices.push_back(libPart.index);
		}
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

API_LibPart LibpartPlacer::CreateLibPartFromFile(const std::filesystem::path& filePath)
{
	GSErrCode err = NoError;

	IO::Location gsmFileLocation(filePath.string().c_str());
	GS::Array<API_LibraryInfo> libInfo;
	API_LibPart libPart{};
	std::string fileName = filePath.filename().string();

	try
	{
		IO::Location* embeddedFileLocation = new IO::Location(*_location);
		err = embeddedFileLocation->AppendToLocal(IO::Name(fileName.c_str()));
		err = IO::fileSystem.Copy(gsmFileLocation, *embeddedFileLocation);

		BNZeroMemory(&libPart, sizeof(API_LibPart));
		libPart.typeID = APILib_ObjectID;
		libPart.location = embeddedFileLocation;
	}
	catch (std::bad_alloc&)
	{
		std::cout << "Could not get location" << std::endl;
	}	

	if (err != NoError)
	{
		std::cout << "Error in Create()" << std::endl;
	}

	return libPart;
}
