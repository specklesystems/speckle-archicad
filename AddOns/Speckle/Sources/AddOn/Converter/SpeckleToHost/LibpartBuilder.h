#pragma once
#pragma warning(disable : 4996)

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "BuiltInLibrary.hpp"
#include "Folder.hpp"
#include "UnpackedElement.h"
#include <ReceiveConversionResult.h>

class LibpartBuilder
{
public:
	LibpartBuilder(const std::string& baseGroupName);
	void CreateLibParts(const std::vector<UnpackedElement>& elements);
	void PlaceLibparts();

	std::vector<ReceiveConversionResult> conversionResults;
	std::vector<std::string> bakedObjectIds;

private:
	IO::Location* _location;
	UInt32 _elementCount = 1;
	std::string _baseGroupName;

	void GetLocation();
	void CreateLibPart(const UnpackedElement& element);
	std::string PlaceLibpart(GS::Int32 libIndex);

	std::vector<Int32> libpartIndices;
	std::vector<std::string> placedElementIds;
};
