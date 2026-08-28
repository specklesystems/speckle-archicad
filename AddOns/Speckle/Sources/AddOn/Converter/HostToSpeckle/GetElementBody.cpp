#include "HostToSpeckleConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"
#include "ConverterUtils.h"
#include "SpeckleConversionException.h"

#include <AttributeIndex.hpp>
#include <ConvexPolygon.hpp>
#include <CoordinateSystem.hpp>
#include <Model.hpp>
#include <ModelElement.hpp>
#include <ModelMeshBody.hpp>
#include <Transformation.hpp>

#include "picosha2.h"

#include <array>
#include <cmath>
#include <map>
#include <set>
#include <unordered_map>

namespace
{
	template<typename T>
	void GetPartIDs(T* parts, std::set<API_Guid>& partIDs)
	{
		GSSize nSubElements = BMGetPtrSize(reinterpret_cast<GSPtr>(parts)) / sizeof(T);
		for (Int32 idx = 0; idx < nSubElements; ++idx)
			partIDs.insert(parts[idx].head.guid);
	}

	// Memo mask covering exactly the sub-part arrays read below — pulling
	// APIMemoMask_All per element (polygons, parameters, ...) was a hot spot.
	// 0 = the type has no sub-parts and the memo fetch is skipped entirely.
	UInt64 PartMemoMask(API_ElemTypeID typeID)
	{
		switch (typeID) {
		case API_StairID:
			return APIMemoMask_StairRiser | APIMemoMask_StairTread | APIMemoMask_StairStructure;
		case API_RailingID:
			return APIMemoMask_RailingSegment | APIMemoMask_RailingPattern |
				APIMemoMask_RailingRail | APIMemoMask_RailingHandrail | APIMemoMask_RailingToprail |
				APIMemoMask_RailingBalusterSet | APIMemoMask_RailingBaluster | APIMemoMask_RailingPanel |
				APIMemoMask_RailingInnerPost | APIMemoMask_RailingNode |
				APIMemoMask_RailingRailConnection | APIMemoMask_RailingHandrailConnection |
				APIMemoMask_RailingToprailConnection | APIMemoMask_RailingPost |
				APIMemoMask_RailingRailEnd | APIMemoMask_RailingHandrailEnd | APIMemoMask_RailingToprailEnd;
		case API_CurtainWallID:
			return APIMemoMask_CWallSegments | APIMemoMask_CWallFrames | APIMemoMask_CWallPanels |
				APIMemoMask_CWallJunctions | APIMemoMask_CWallAccessories;
		case API_ColumnID:
			return APIMemoMask_ColumnSegment;
		case API_BeamID:
			return APIMemoMask_BeamSegment;
		default:
			return 0;
		}
	}

	std::set<API_Guid> CollectPartIDs(const API_Guid& elemId, API_ElemTypeID typeID)
	{
		std::set<API_Guid> partIDs{};
		partIDs.insert(elemId);

		const UInt64 memoMask = PartMemoMask(typeID);
		if (memoMask == 0)
			return partIDs; // no sub-parts for this type

		API_ElementMemo memo{};
		ACAPI_Element_GetMemo(elemId, &memo, memoMask);

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
		ACAPI_DisposeElemMemoHdls(&memo); // the masked arrays were copied into partIDs above
		return partIDs;
	}

	// Appends one tessellated body's polygons straight into per-material flat
	// meshes — single copy, ACAPI vertex -> Mesh arrays (the old path built
	// per-vertex FaceVertex objects grouped into MeshFace lists, then copied
	// them into the flat arrays in a second pass).
	//
	// softEdges: shared vertices dedup'd by their body vertex index (smooth
	// shading); otherwise every face gets its own copy of each corner (faceted
	// shading) — identical to the old AddSoftMeshes/AddHardMeshes outputs,
	// including mesh emission order (ascending material index) and local
	// vertex numbering.
	void AppendBodyMeshes(
		ModelerAPI::MeshBody& body,
		bool softEdges,
		ModelerAPI::CoordinateSystem coordinateSystem,
		ElementBody& elementBody)
	{
		struct MeshAccum
		{
			Mesh mesh;
			std::unordered_map<Int32, int> vertexIndexMap; // body vertex index -> local index (soft only)
		};
		std::map<int, MeshAccum> byMaterial;                       // ordered: meshes emit per material index
		std::unordered_map<Int32, ModelerAPI::Vertex> vertexCache; // one GetVertex per unique body vertex

		auto getVertex = [&](Int32 bodyVertexIndex) -> const ModelerAPI::Vertex&
		{
			auto [it, isNew] = vertexCache.try_emplace(bodyVertexIndex);
			if (isNew)
				body.GetVertex(bodyVertexIndex, &it->second, coordinateSystem);
			return it->second;
		};

		Int32 polyCount = body.GetPolygonCount();
		for (Int32 polyIndex = 1; polyIndex <= polyCount; ++polyIndex)
		{
			ModelerAPI::Polygon polygon{};
			body.GetPolygon(polyIndex, &polygon);

			ModelerAPI::AttributeIndex matIdx{};
			polygon.GetMaterialIndex(matIdx);
			MeshAccum& accum = byMaterial[matIdx.GetIndex()];
			Mesh& mesh = accum.mesh;

			Int32 convexPolyCount = polygon.GetConvexPolygonCount();
			for (Int32 convPolyIndex = 1; convPolyIndex <= convexPolyCount; ++convPolyIndex)
			{
				ModelerAPI::ConvexPolygon convexPolygon{};
				polygon.GetConvexPolygon(convPolyIndex, &convexPolygon);

				Int32 vertexCount = convexPolygon.GetVertexCount();
				mesh.faces.push_back(vertexCount);
				for (Int32 vertexIndex = 1; vertexIndex <= vertexCount; ++vertexIndex)
				{
					const Int32 bodyVertexIndex = convexPolygon.GetVertexIndex(vertexIndex);

					if (softEdges)
					{
						const auto [it, isNew] = accum.vertexIndexMap.try_emplace(
							bodyVertexIndex, static_cast<int>(mesh.vertices.size() / 3));
						if (isNew)
						{
							const ModelerAPI::Vertex& vertex = getVertex(bodyVertexIndex);
							mesh.vertices.push_back(vertex.x);
							mesh.vertices.push_back(vertex.y);
							mesh.vertices.push_back(vertex.z);
						}
						mesh.faces.push_back(it->second);
					}
					else
					{
						const ModelerAPI::Vertex& vertex = getVertex(bodyVertexIndex);
						mesh.faces.push_back(static_cast<int>(mesh.vertices.size() / 3));
						mesh.vertices.push_back(vertex.x);
						mesh.vertices.push_back(vertex.y);
						mesh.vertices.push_back(vertex.z);
					}
				}
			}
		}

		for (auto& item : byMaterial)
		{
			item.second.mesh.materialIndex = item.first;
			elementBody.meshes.push_back(std::move(item.second.mesh));
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

	// Stable geometry identity: SHA-256 over the quantized local meshes + material indices.
	// Vertices are quantized to 1e-6 m so float noise cannot split two identical definitions;
	// material index is folded in so shape-identical objects with different surfaces stay distinct
	// (material lives on the shared definition geometry).
	std::string ComputeDefinitionId(const ElementBody& body)
	{
		size_t total = 0;
		for (const auto& m : body.meshes)
			total += 2 * sizeof(int) + m.faces.size() * sizeof(int) + sizeof(int) + m.vertices.size() * sizeof(long long);

		std::vector<unsigned char> buf;
		buf.reserve(total); // one allocation (the incremental inserts used to realloc-churn)
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

	//Get elements — index lookup per part GUID instead of a full model scan per element
	for (Int32 iElement : ConverterUtils::GetModelElementIndices(acModel, partIDs))
	{
		ModelerAPI::Element elem{};
		acModel.GetElement(iElement, &elem);

		// Get bodies
		Int32 nBodies = elem.GetTessellatedBodyCount();
		for (Int32 bodyIndex = 1; bodyIndex <= nBodies; ++bodyIndex)
		{
			ModelerAPI::MeshBody body{};
			elem.GetTessellatedBody(bodyIndex, &body);

			// This logic is potentially buggy
			// We need to find a better way to decide if an edge is soft or hard
			const bool softEdges = (elemType == API_ObjectID) && !body.HasSharpEdge();
			AppendBodyMeshes(body, softEdges, ModelerAPI::CoordinateSystem::World, elementBody);
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

	for (Int32 iElement : ConverterUtils::GetModelElementIndices(acModel, partIDs))
	{
		ModelerAPI::Element elem{};
		acModel.GetElement(iElement, &elem);

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

			// Untransformed geometry, straight from the Modeler.
			const bool softEdges = !body.HasSharpEdge();
			AppendBodyMeshes(body, softEdges, ModelerAPI::CoordinateSystem::ElemLocal, localBody);
		}
	}

	if (!haveTransform || localBody.meshes.empty())
		return instance; // nothing instanceable -> caller bakes world geometry

	instance.transform = ToRowMajor4x4(transform);
	instance.definitionId = ComputeDefinitionId(localBody);
	instance.localBody = std::move(localBody);
	instance.valid = true;
	return instance;
}
