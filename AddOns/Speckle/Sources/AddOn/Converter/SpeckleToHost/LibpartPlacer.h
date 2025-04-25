#pragma once
#pragma warning(disable : 4996)

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "BuiltInLibrary.hpp"
#include "Folder.hpp"
#include "UnpackedElement.h"
#include <ReceiveConversionResult.h>
#include <filesystem>

class LibpartPlacer
{
public:
	std::vector<std::string> bakedObjectIds;
	std::vector<ReceiveConversionResult> conversionResults;

	LibpartPlacer(const std::string& baseGroupName);
	std::vector<Int32> RegisterLibparts(const std::string& libraryFolderPath);
	std::vector<Int32> RegisterLibpartsBatched(const std::string& libraryFolderPath);
	void PlaceLibparts(const std::vector<Int32>& libIndices);

private:
	IO::Location* _location;
	std::string _baseGroupName;
	void GetLocation();

	API_LibPart CreateLibPartFromFile(const std::filesystem::path& filePath);
	std::vector<std::filesystem::path> CollectFilePaths(const std::string& folderPath);
	API_DatabaseInfo GetCurrentDB();
	void SetCurrentDB(API_DatabaseInfo& databaseInfo);
	void SwitchToFloorPlanDB();
	std::string PlaceLibpart(GS::Int32 libIndex);
};
