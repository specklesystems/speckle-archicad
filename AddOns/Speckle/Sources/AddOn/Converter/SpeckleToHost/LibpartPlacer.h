#pragma once
#pragma warning(disable : 4996)

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "BuiltInLibrary.hpp"
#include "Folder.hpp"
#include "UnpackedElement.h"
#include <ReceiveConversionResult.h>

#include "ArchicadElement.h"

class LibpartPlacer
{
public:
	std::vector<std::pair<std::string, std::string>> CollectFiles(const std::string& folderPath);
	API_LibPart Create(const std::string& path, const std::string& fn);
	void AddLibparts();
	void SetLibs();

private:
	API_DatabaseInfo GetCurrentDB();
	void SetCurrentDB(API_DatabaseInfo& databaseInfo);
	void SwitchToFloorPlanDB();
	std::string PlaceLibpart(GS::Int32 libIndex);
	void PlaceLibparts(const std::vector<Int32>& libIndices);
};
