#include "HostToSpeckleConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"
#include "ConverterUtils.h"
#include "SpeckleConversionException.h"
#include "MeshFace.h"

#include <AttributeIndex.hpp>
#include <ConvexPolygon.hpp>
#include <Model.hpp>
#include <ModelElement.hpp>
#include <ModelMeshBody.hpp>

#include <set>

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

	void AddHardMeshesToElementBody(const std::map<int, std::vector<MeshFace>>& materialMeshFaceMap, ElementBody& elementBody)
	{
		for (const auto& item : materialMeshFaceMap)
		{
			Mesh mesh{};
			int currVertex = 0;
			mesh.materialIndex = item.first;
			for (const auto& face : item.second)
			{
				mesh.faces.push_back(face.size);
				for (const auto& v : face.vertices)
				{
					mesh.faces.push_back(currVertex);
					currVertex++;

					mesh.vertices.push_back(v.x);
					mesh.vertices.push_back(v.y);
					mesh.vertices.push_back(v.z);
				}
			}
			elementBody.meshes.push_back(mesh);
		}
	}

	void AddSoftMeshesToElementBody(const std::map<int, std::vector<MeshFace>>& materialMeshFaceMap, ElementBody& elementBody)
	{
		for (const auto& item : materialMeshFaceMap)
		{
			Mesh mesh{};
			int vertexIndexCount = 0;
			std::map<int, int> vertexIndexMap;

			mesh.materialIndex = item.first;
			for (const auto& face : item.second)
			{
				mesh.faces.push_back(face.size);
				for (const auto& v : face.vertices)
				{
					bool newIndex = (vertexIndexMap.count(v.archicadVertexIndex) == 0);
					if (newIndex)
					{
						vertexIndexMap[v.archicadVertexIndex] = vertexIndexCount;
						vertexIndexCount++;
						mesh.vertices.push_back(v.x);
						mesh.vertices.push_back(v.y);
						mesh.vertices.push_back(v.z);
					}

					mesh.faces.push_back(vertexIndexMap[v.archicadVertexIndex]);				
				}
			}
			elementBody.meshes.push_back(mesh);
		}
	}
}

ElementBody HostToSpeckleConverter::GetElementBody(const std::string& elemId)
{
	auto acModel = ConverterUtils::GetArchiCadModel();
	auto apiElem = ConverterUtils::GetElement(elemId);
	auto elemType = apiElem.header.type.typeID;
	auto partIDs = CollectPartIDs(apiElem.header.guid, elemType);

	// the body to return
	ElementBody elementBody{};

	// POC: remove this once we are ready to convert Grid Elements
	if (elemType == API_ObjectID && apiElem.header.type.variationID == APIVarId_GridElement)
		throw SpeckleConversionException("Converting Grid elements in ArchiCAD is not supported yet.");

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
			bool isHardBody = body.HasSharpEdge();

			std::map<int, std::vector<MeshFace>> materialMeshFaceMap;

			// Get polygons
			Int32 polyCount = body.GetPolygonCount();
			for (Int32 polyIndex = 1; polyIndex <= polyCount; ++polyIndex)
			{
				ModelerAPI::Polygon polygon{};
				body.GetPolygon(polyIndex, &polygon);

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
					MeshFace mFace{};
					Int32 vertexCount = convexPolygon.GetVertexCount();
					mFace.size = vertexCount;
					for (Int32 vertexIndex = 1; vertexIndex <= vertexCount; ++vertexIndex)
					{
						ModelerAPI::Vertex vertex{};
						FaceVertex fVert{};
						fVert.archicadVertexIndex = convexPolygon.GetVertexIndex(vertexIndex);
						body.GetVertex(fVert.archicadVertexIndex, &vertex);
						fVert.x = vertex.x;
						fVert.y = vertex.y;
						fVert.z = vertex.z;
						mFace.vertices.push_back(fVert);
					}
					materialMeshFaceMap[materialIndex].push_back(mFace);
				}
			}

			// Add Meshes to elementBody
			// This logic is potentially buggy
			// We need to find a better way to decide if an edge is soft or hard
			if (apiElem.header.type.typeID == API_ObjectID)
			{
				if (isHardBody)
				{
					AddHardMeshesToElementBody(materialMeshFaceMap, elementBody);
				}
				else
				{
					AddSoftMeshesToElementBody(materialMeshFaceMap, elementBody);
				}
			}
			else
			{
				AddHardMeshesToElementBody(materialMeshFaceMap, elementBody);
			}

		}
	}

	return elementBody;
}
