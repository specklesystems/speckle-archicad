#pragma once
#pragma warning(disable : 4996)

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "BuiltInLibrary.hpp"
#include "Folder.hpp"
#include "UnpackedElement.h"
#include <ReceiveConversionResult.h>

#include "ArchicadElement.h"

class LibpartBuilder
{
public:
	LibpartBuilder(const std::string& baseGroupName);
	void CreateLibParts(const std::vector<ArchicadElement>& elements);
	void PlaceLibparts();

	std::vector<ReceiveConversionResult> conversionResults;
	std::vector<std::string> bakedObjectIds;

	UInt32 _elementCount = 1;
private:
	IO::Location* _location;
	std::string _baseGroupName;

	void GetLocation();
	void CreateLibPart(const ArchicadElement& element);
	std::string PlaceLibpart(GS::Int32 libIndex);

	std::vector<Int32> libpartIndices;
	std::vector<std::string> placedElementIds;
};
