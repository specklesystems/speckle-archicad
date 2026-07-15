#include "HostToSpeckleConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"
#include "ConverterUtils.h"
#include "SpeckleConversionException.h"
#include "MeshFace.h"

#include <AttributeIndex.hpp>
#include <ConvexPolygon.hpp>
#include <CoordinateSystem.hpp>
#include <Model.hpp>
#include <ModelElement.hpp>
#include <ModelMeshBody.hpp>
#include <Transformation.hpp>

#include "picosha2.h"

#include <algorithm>
#include <array>
#include <cmath>
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

	// Modeler's 3x4 local->world matrix -> the bundle's row-major 4x4 (last row 0 0 0 1).
	// Column 3 of each row is the translation, matching Speckle's Matrix4x4 (M14/M24/M34).
	std::array<double, 16> ToRowMajor4x4(const ModelerAPI::Transformation& tr)
	{
		return {
			tr.matrix[0][0], tr.matrix[0][1], tr.matrix[0][2], tr.matrix[0][3],
			tr.matrix[1][0], tr.matrix[1][1], tr.matrix[1][2], tr.matrix[1][3],
			tr.matrix[2][0], tr.matrix[2][1], tr.matrix[2][2], tr.matrix[2][3],
			0.0,             0.0,             0.0,             1.0
		};
	}

	bool IsIdentity4x4(const std::array<double, 16>& m)
	{
		static const double I[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
		for (int i = 0; i < 16; ++i)
			if (std::fabs(m[i] - I[i]) > 1e-9)
				return false;
		return true;
	}

	// Stable geometry identity: SHA-256 over the quantized local meshes + material indices.
	// Vertices are quantized to 1e-6 m so float noise cannot split two identical definitions;
	// material index is folded in so shape-identical objects with different surfaces stay distinct
	// (material lives on the shared definition geometry).
	std::string ComputeDefinitionId(const ElementBody& body)
	{
		std::vector<unsigned char> buf;
		auto push = [&](const void* p, size_t n) {
			const auto* b = static_cast<const unsigned char*>(p);
			buf.insert(buf.end(), b, b + n);
		};
		for (const auto& m : body.meshes)
		{
			const int materialIndex = m.materialIndex;
			push(&materialIndex, sizeof(materialIndex));
			const int faceCount = static_cast<int>(m.faces.size());
			push(&faceCount, sizeof(faceCount));
			for (const int f : m.faces)
				push(&f, sizeof(f));
			const int vertCount = static_cast<int>(m.vertices.size());
			push(&vertCount, sizeof(vertCount));
			for (const double d : m.vertices)
			{
				const long long q = std::llround(d / 1e-6);
				push(&q, sizeof(q));
			}
		}
		return picosha2::hash256_hex_string(buf.begin(), buf.end());
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

// Extracts a GDL/library-part "Object" as an instance: untransformed (ElemLocal) geometry
// plus the Modeler's local->world transform, read straight from the API — no reconstruction
// and no matrix inversion. Returns an invalid ObjectInstance (valid == false) for anything
// that is not an instanceable object, so the caller can fall back to baked world geometry.
ObjectInstance HostToSpeckleConverter::GetObjectInstance(const std::string& elemId)
{
	ObjectInstance instance{};

	auto apiElem = ConverterUtils::GetElement(elemId);
	if (apiElem.header.type.typeID != API_ObjectID)
		return instance; // only library-part objects are instanced
	if (apiElem.header.type.variationID == APIVarId_GridElement)
		return instance; // grid elements are not converted (mirrors GetElementBody)

	auto acModel = ConverterUtils::GetArchiCadModel();
	auto partIDs = CollectPartIDs(apiElem.header.guid, API_ObjectID);

	ElementBody localBody{};
	bool haveTransform = false;
	ModelerAPI::Transformation transform{};
	bool haveSample = false;
	ModelerAPI::Vertex worldSample{};
	ModelerAPI::Vertex localSample{};

	Int32 nElements = acModel.GetElementCount();
	for (Int32 iElement = 1; iElement <= nElements; ++iElement)
	{
		ModelerAPI::Element elem{};
		acModel.GetElement(iElement, &elem);
		API_Guid apiGuid{ GSGuid2APIGuid(elem.GetElemGuid()) };
		if (partIDs.find(apiGuid) == partIDs.end())
			continue;

		if (!haveTransform)
		{
			transform = elem.GetElemLocalToWorldTransformation();
			haveTransform = true;
		}

		Int32 nBodies = elem.GetTessellatedBodyCount();
		for (Int32 bodyIndex = 1; bodyIndex <= nBodies; ++bodyIndex)
		{
			ModelerAPI::MeshBody body{};
			elem.GetTessellatedBody(bodyIndex, &body);
			const bool isHardBody = body.HasSharpEdge();

			std::map<int, std::vector<MeshFace>> materialMeshFaceMap;

			Int32 polyCount = body.GetPolygonCount();
			for (Int32 polyIndex = 1; polyIndex <= polyCount; ++polyIndex)
			{
				ModelerAPI::Polygon polygon{};
				body.GetPolygon(polyIndex, &polygon);

				ModelerAPI::AttributeIndex matIdx{};
				polygon.GetMaterialIndex(matIdx);
				const int materialIndex = matIdx.GetIndex();

				Int32 convexPolyCount = polygon.GetConvexPolygonCount();
				for (Int32 convPolyIndex = 1; convPolyIndex <= convexPolyCount; ++convPolyIndex)
				{
					ModelerAPI::ConvexPolygon convexPolygon{};
					polygon.GetConvexPolygon(convPolyIndex, &convexPolygon);

					MeshFace mFace{};
					Int32 vertexCount = convexPolygon.GetVertexCount();
					mFace.size = vertexCount;
					for (Int32 vertexIndex = 1; vertexIndex <= vertexCount; ++vertexIndex)
					{
						FaceVertex fVert{};
						fVert.archicadVertexIndex = convexPolygon.GetVertexIndex(vertexIndex);

						// Untransformed geometry, straight from the Modeler.
						ModelerAPI::Vertex localVertex{};
						body.GetVertex(fVert.archicadVertexIndex, &localVertex, ModelerAPI::CoordinateSystem::ElemLocal);
						fVert.x = localVertex.x;
						fVert.y = localVertex.y;
						fVert.z = localVertex.z;
						mFace.vertices.push_back(fVert);

						// Verification sample: read the SAME vertex in World space once, so a send
						// can prove ElemLocal != World for objects (see ObjectInstance / session log).
						if (!haveSample)
						{
							body.GetVertex(fVert.archicadVertexIndex, &worldSample, ModelerAPI::CoordinateSystem::World);
							localSample = localVertex;
							haveSample = true;
						}
					}
					materialMeshFaceMap[materialIndex].push_back(mFace);
				}
			}

			if (isHardBody)
				AddHardMeshesToElementBody(materialMeshFaceMap, localBody);
			else
				AddSoftMeshesToElementBody(materialMeshFaceMap, localBody);
		}
	}

	if (!haveTransform || localBody.meshes.empty())
		return instance; // nothing instanceable -> caller bakes world geometry

	instance.transform = ToRowMajor4x4(transform);
	instance.transformIsIdentity = IsIdentity4x4(instance.transform);
	if (haveSample)
	{
		instance.worldSample = { worldSample.x, worldSample.y, worldSample.z };
		instance.localSample = { localSample.x, localSample.y, localSample.z };
		instance.localWorldMaxDelta = std::max({
			std::fabs(worldSample.x - localSample.x),
			std::fabs(worldSample.y - localSample.y),
			std::fabs(worldSample.z - localSample.z) });
	}
	instance.definitionId = ComputeDefinitionId(localBody);
	instance.localBody = std::move(localBody);
	instance.valid = true;
	return instance;
}
