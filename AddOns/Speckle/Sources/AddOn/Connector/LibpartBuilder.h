#pragma once
#pragma warning(disable : 4996)

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "BuiltInLibrary.hpp"
#include "Folder.hpp"

#include "UnpackedElement.h"

class LibpartBuilder
{
public:
	LibpartBuilder();
	std::string CreateLibPart(const UnpackedElement& element, const std::string& baseGroupName, int runningNumber);
	std::string CreateLibParts(const std::vector<UnpackedElement>& elements);
	void PlaceLibparts();

private:
	IO::Location* _location;

	GSErrCode GetLocation(IO::Location*& loc, bool useEmbeddedLibrary);
	GSErrCode PlaceLibpart(GS::Int32 libIndex);

	std::vector<Int32> libpartIndices;
};
