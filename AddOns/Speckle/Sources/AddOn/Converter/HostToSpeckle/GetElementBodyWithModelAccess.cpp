#include "HostToSpeckleConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"
#include "ConverterUtils.h"
#include "SpeckleConversionException.h"

#include "Transformation.hpp"
#include "TRANMAT.h"
#include "TM.h"
#include "Vertex.hpp"

#include <set>
#include <functional>

#include "StopWatch.h"

namespace
{
	void GetComponent(API_Component3D& component, API_3DTypeID typeId, Int32 index) {
		component = API_Component3D{};
		component.header.typeID = typeId;
		component.header.index = index;
		if (ACAPI_ModelAccess_GetComponent(&component) != NoError) {
			// TODO: throw
		}
	}

	bool getDecomposedVertexIndices(int polygonIndex, API_Component3D& component, std::vector<std::vector<int>>& indices)
	{
		GetComponent(component, API_PgonID, polygonIndex);

		Int32** cpoly = nullptr;
		GSErrCode err = ACAPI_ModelAccess_DecomposePgon(polygonIndex, &cpoly);

		if (err != NoError || cpoly == nullptr)
			return false;

		int numSubPolygons = -cpoly[0][0];  // First element is -n, the number of subpolygons

		int idx = 1;
		for (int i = 0; i < numSubPolygons; ++i) {
			int numVertices = -cpoly[0][idx];  // Each subpolygon starts with -m, the number of vertices

			std::vector<int> currentIndices;
			currentIndices.clear();

			for (int j = 1; j <= numVertices; ++j) {
				int vertIndex = cpoly[0][idx + j];  // Get the vertex index
				currentIndices.push_back(vertIndex + 1);
			}
			indices.push_back(currentIndices);
			idx += numVertices + 1;
		}

		BMKillHandle(reinterpret_cast<GSHandle*>(&cpoly));
		return true;
	}

	void getVertexIndices(int polygonIndex, API_Component3D& component, std::vector<std::vector<int>>& indices)
	{
		GetComponent(component, API_PgonID, polygonIndex);
		Int32 fpedg = component.pgon.fpedg;
		Int32 lpedg = component.pgon.lpedg;

		std::vector<int> currentIndices;
		currentIndices.clear();

		for (Int32 ie = fpedg; ie <= lpedg; ie++)
		{
			GetComponent(component, API_PedgID, ie);
			bool wasNegative = component.pedg.pedg < 0;
			Int32 edgeIndex = std::abs(component.pedg.pedg);

			GetComponent(component, API_EdgeID, edgeIndex);
			Int32 vertexIndex = wasNegative ? component.edge.vert2 : component.edge.vert1;
			currentIndices.push_back(vertexIndex);
		}

		indices.push_back(currentIndices);
	}

	void API2AC_Tranmat(TRANMAT* tranmat, const API_Tranmat& api_tranmat)
	{
		tranmat->status = 0;
		tranmat->dummy1 = tranmat->dummy2 = tranmat->dummy3 = 0;
		Geometry::Vector3d vec1(api_tranmat.tmx[0], api_tranmat.tmx[4], api_tranmat.tmx[8]), vec2(api_tranmat.tmx[1], api_tranmat.tmx[5], api_tranmat.tmx[9]), vec3(api_tranmat.tmx[2], api_tranmat.tmx[6], api_tranmat.tmx[10]), vec4(api_tranmat.tmx[3], api_tranmat.tmx[7], api_tranmat.tmx[11]);
		tranmat->SetMatrix(Geometry::Matrix34::CreateFromColVectors(vec1, vec2, vec3, vec4));
	}
}

ElementBody HostToSpeckleConverter::GetElementBodyWithModelAccess(const std::string& elemId)
{
	auto apiElem = ConverterUtils::GetElement(elemId);
	API_ElemInfo3D info3D = {};
	ACAPI_ModelAccess_Get3DInfo(apiElem.header, &info3D);

	// the body to return
	ElementBody elementBody{};

	for (Int32 ib = info3D.fbody; ib <= info3D.lbody; ib++)
	{
		std::hash<std::string> hasher;
		STOPWATCH.Start();
		std::vector<std::vector<int>> indices;
		API_Component3D component = {};
		GetComponent(component, API_BodyID, ib);

		Int32 nPgon = component.body.nPgon;
		API_Tranmat tmx = component.body.tranmat;
		for (Int32 ip = 1; ip <= nPgon; ip++)
		{
			bool decomp = getDecomposedVertexIndices(ip, component, indices);

			if (!decomp)
			{
				getVertexIndices(ip, component, indices);
			}
		}

		// create hash from vertexindices
		std::stringstream ss;
		for (int i = 0; i < indices.size(); i++)
		{
			for (int j = 0; j < indices[i].size(); j++) 
			{
				ss << indices[i][j];
			}
		}

		// Compute the hash value
		size_t hash_value = hasher(ss.str());
		auto elapsed = STOPWATCH.Stop();

		if (hash_value == 0) return{};

		std::vector<double> vertices;
		for (int i = 0; i < indices.size(); i++)
		{
			for (int j = 0; j < indices[i].size(); j++)
			{
				GetComponent(component, API_VertID, indices[i][j]);
				TRANMAT	tm;
				API2AC_Tranmat(&tm, tmx);
				Point3D p1(component.vert.x, component.vert.y, component.vert.z);
				p1 = Geometry::TransformPoint(tm, p1);
				vertices.push_back(p1.x);
				vertices.push_back(p1.y);
				vertices.push_back(p1.z);
			}

			elementBody.AddFace(vertices, 1);
			vertices.clear();
		}
	}

	return elementBody;
}
