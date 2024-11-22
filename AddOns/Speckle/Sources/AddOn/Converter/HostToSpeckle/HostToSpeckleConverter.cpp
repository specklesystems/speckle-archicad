#include "HostToSpeckleConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

#include <exp.h>
#include <AttributeIndex.hpp>
#include <ConvexPolygon.hpp>
#include <Model.hpp>
#include <ModelElement.hpp>
#include <ModelMaterial.hpp>
#include <ModelMeshBody.hpp>
#include <Sight.hpp>

#include <set>

// POC organize method implementations of the HostToSpeckleConverter into separate files

namespace
{
	template<typename T>
	void GetPartIDs(T* parts, std::set<API_Guid>& partIDs)
	{
		GSSize nSubElements = BMGetPtrSize(reinterpret_cast<GSPtr>(parts)) / sizeof(T);
		for (Int32 idx = 0; idx < nSubElements; ++idx)
			partIDs.insert(parts[idx].head.guid);
	}

	std::set<API_Guid> CollectPartIDs(const API_Guid& elemId, API_ElemTypeID typeID)
	{
		API_ElementMemo memo{};
		ACAPI_Element_GetMemo(elemId, &memo, APIMemoMask_All);

		std::set<API_Guid> partIDs{};
		partIDs.insert(elemId);

		switch (typeID) {
		case API_StairID:
			GetPartIDs(memo.stairRisers, partIDs);
			GetPartIDs(memo.stairTreads, partIDs);
			GetPartIDs(memo.stairStructures, partIDs);
			break;
		case API_RailingID:
			GetPartIDs(memo.railingSegments, partIDs);
			GetPartIDs(memo.railingPatterns, partIDs);
			GetPartIDs(memo.railingRails, partIDs);
			GetPartIDs(memo.railingHandrails, partIDs);
			GetPartIDs(memo.railingToprails, partIDs);
			GetPartIDs(memo.railingBalusterSets, partIDs);
			GetPartIDs(memo.railingBalusters, partIDs);
			GetPartIDs(memo.railingPanels, partIDs);
			GetPartIDs(memo.railingInnerPosts, partIDs);

			GetPartIDs(memo.railingNodes, partIDs);
			GetPartIDs(memo.railingRailConnections, partIDs);
			GetPartIDs(memo.railingHandrailConnections, partIDs);
			GetPartIDs(memo.railingToprailConnections, partIDs);
			GetPartIDs(memo.railingPosts, partIDs);
			GetPartIDs(memo.railingRailEnds, partIDs);
			GetPartIDs(memo.railingHandrailEnds, partIDs);
			GetPartIDs(memo.railingToprailEnds, partIDs);
			break;
		case API_CurtainWallID:
			GetPartIDs(memo.cWallSegments, partIDs);
			GetPartIDs(memo.cWallFrames, partIDs);
			GetPartIDs(memo.cWallPanels, partIDs);
			GetPartIDs(memo.cWallJunctions, partIDs);
			GetPartIDs(memo.cWallAccessories, partIDs);
			break;
		case API_ColumnID:
			GetPartIDs(memo.columnSegments, partIDs);
			break;
		case API_BeamID:
			GetPartIDs(memo.beamSegments, partIDs);
			break;
		default:
			break;
		}
		return partIDs;
	}
}

std::vector<std::string> HostToSpeckleConverter::GetSelection()
{
	std::vector<std::string> selectedElements;
	API_SelectionInfo selectionInfo{};
	GS::Array<API_Neig> selection;
	if (auto err = ACAPI_Selection_Get(&selectionInfo, &selection, true); err == NoError)
	{
		for (const auto& item : selection)
		{
			std::string guid = APIGuidToString(item.guid).ToCStr().Get();
			selectedElements.push_back(guid);
		}
	}
	return selectedElements;
}

ElementBody HostToSpeckleConverter::GetElementMesh(const std::string& elemId)
{
	// POC move the get sight part to a function, it's repeated code
	
	//*******************************************************************

	void* dummy = nullptr;
	GSErrCode err = ACAPI_Sight_GetCurrentWindowSight(&dummy);
	if (err != NoError) {
		// TODO: should this throw?
	}
	Modeler::SightPtr currentSightPtr((Modeler::Sight*)dummy); // init the shared ptr with the raw pointer
	ModelerAPI::Model acModel;
	Modeler::IAttributeReader* attrReader = ACAPI_Attribute_GetCurrentAttributeSetReader();
	err = EXPGetModel(currentSightPtr, &acModel, attrReader);
	if (err != NoError) {
		// TODO: should this throw?
	}
	//*******************************************************************

	// Get AC element by id
	API_Element apiElem{};
	apiElem.header.guid = APIGuidFromString(elemId.c_str());
	ACAPI_Element_Get(&apiElem);

	auto partIDs = CollectPartIDs(apiElem.header.guid, apiElem.header.type.typeID);

	ElementBody elementBody;

	//Get elements
	Int32 nElements = acModel.GetElementCount();
	for (Int32 iElement = 1; iElement <= nElements; iElement++)
	{
		ModelerAPI::Element elem{};
		acModel.GetElement(iElement, &elem);
		API_Guid apiGuid{ GSGuid2APIGuid(elem.GetElemGuid()) };
		if (partIDs.find(apiGuid) == partIDs.end())
			continue;

		// Get bodies
		Int32 nBodies = elem.GetTessellatedBodyCount();
		for (Int32 bodyIndex = 1; bodyIndex <= nBodies; ++bodyIndex)
		{
			ModelerAPI::MeshBody body{};
			elem.GetTessellatedBody(bodyIndex, &body);

			// Get polygons
			Int32 polyCount = body.GetPolygonCount();
			for (Int32 polyIndex = 1; polyIndex <= polyCount; ++polyIndex)
			{
				ModelerAPI::Polygon polygon{};
				body.GetPolygon(polyIndex, &polygon);

				std::vector<double> vertices;
				ModelerAPI::AttributeIndex matIdx{};
				polygon.GetMaterialIndex(matIdx);
				int materialIndex = matIdx.GetIndex();

				// Get convex polygons
				Int32 convexPolyCount = polygon.GetConvexPolygonCount();
				for (Int32 convPolyIndex = 1; convPolyIndex <= convexPolyCount; ++convPolyIndex)
				{
					ModelerAPI::ConvexPolygon convexPolygon{};
					polygon.GetConvexPolygon(convPolyIndex, &convexPolygon);

					// Get vertices
					Int32 vertexCount = convexPolygon.GetVertexCount();
					for (Int32 vertexIndex = 1; vertexIndex <= vertexCount; ++vertexIndex)
					{
						ModelerAPI::Vertex vertex{};
						body.GetVertex(convexPolygon.GetVertexIndex(vertexIndex), &vertex);

						vertices.push_back(vertex.x);
						vertices.push_back(vertex.y);
						vertices.push_back(vertex.z);
					}

					elementBody.AddFace(vertices, materialIndex);
					vertices.clear();
				}
			}
		}
	}

	return elementBody;
}

Material HostToSpeckleConverter::GetModelMaterial(int materialIndex)
{
	// POC move the get sight part to a function, it's repeated code

	//*******************************************************************
	void* dummy = nullptr;
	GSErrCode err = ACAPI_Sight_GetCurrentWindowSight(&dummy);
	if (err != NoError) {
		// TODO: should this throw?
	}
	Modeler::SightPtr currentSightPtr((Modeler::Sight*)dummy); // init the shared ptr with the raw pointer
	ModelerAPI::Model acModel;
	Modeler::IAttributeReader* attrReader = ACAPI_Attribute_GetCurrentAttributeSetReader();
	err = EXPGetModel(currentSightPtr, &acModel, attrReader);
	if (err != NoError) {
		// TODO: should this throw?
	}
	//*******************************************************************

	ModelerAPI::AttributeIndex matIdx(ModelerAPI::AttributeIndex::MaterialIndex, materialIndex);
	ModelerAPI::Material material{};
	acModel.GetMaterial(matIdx, &material);

	auto c = material.GetSurfaceColor();
	Material m;
	m.diffuse = Utils::PackARGB(1.0, c.red, c.green, c.blue);
	m.opacity = 1.0 - (static_cast<double>(material.GetTransparency()) / 100.0);
	m.roughness = 1.0 - (static_cast<double>(material.GetShining()) / 10000.0);

	return m;
}
