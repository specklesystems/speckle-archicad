#include "SpeckleToHostConverter.h"
#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"


std::string SpeckleToHostConverter::CreateMorph(const Mesh& mesh, const int materialIndex, const std::string& baseGroupName)
{
    API_Element element = {};
    element.header.type = API_MorphID;
    CHECK_ERROR(ACAPI_Element_GetDefaults(&element, nullptr));

    // Create identity matrix
    double* tmx = element.morph.tranmat.tmx;
    tmx[0] = 1.0; tmx[4] = 0.0; tmx[8] = 0.0;
    tmx[1] = 0.0; tmx[5] = 1.0; tmx[9] = 0.0;
    tmx[2] = 0.0; tmx[6] = 0.0; tmx[10] = 1.0;
    tmx[3] = 0.0; tmx[7] = 0.0; tmx[11] = 1.0;

    void* bodyData = nullptr;
    ACAPI_Body_Create(nullptr, nullptr, &bodyData);

    // Add vertices
    UInt32 vertexCount = static_cast<UInt32>(mesh.vertices.size() / 3);
    std::vector<UInt32> vertices(vertexCount);
    for (UInt32 i = 0; i < vertexCount; i++)
    {
        API_Coord3D coord = { mesh.vertices[i * 3], mesh.vertices[i * 3 + 1], mesh.vertices[i * 3 + 2] };
        ACAPI_Body_AddVertex(bodyData, coord, vertices[i]);
    }

    // Add edges
    std::vector<Int32> edges;
    for (size_t i = 0; i < mesh.faces.size();)
    {
        int polySize = mesh.faces[i];
        i++;
        std::vector<Int32> polygonEdges;
        for (int j = 0; j < polySize; j++)
        {
            UInt32 v1 = vertices[mesh.faces[i + j]];
            UInt32 v2 = vertices[mesh.faces[i + (j + 1) % polySize]];
            Int32 edge;
            ACAPI_Body_AddEdge(bodyData, v1, v2, edge);
            polygonEdges.push_back(edge);
        }
        edges.insert(edges.end(), polygonEdges.begin(), polygonEdges.end());
        i += polySize;
    }

    API_OverriddenAttribute material;
    material = ACAPI_CreateAttributeIndex(materialIndex);
    // Add polygons
    std::vector<UInt32> polygons;
    size_t faceIndex = 0;
    size_t edgeIndex = 0;
    while (faceIndex < mesh.faces.size())
    {
        int polySize = mesh.faces[faceIndex];
        faceIndex++;
        GS::Array<Int32> polyEdges;
        for (int j = 0; j < polySize; j++)
        {
            polyEdges.Push(edges[edgeIndex + j]);
        }
        faceIndex += polySize;
        edgeIndex += polySize;
        UInt32 poly;
        ACAPI_Body_AddPolygon(bodyData, polyEdges, 0, material, poly);
        polygons.push_back(poly);
    }

    API_ElementMemo memo = {};
    // TODO check if we can set individual body edges to soft/invisible here
    ACAPI_Body_Finish(bodyData, &memo.morphBody, &memo.morphMaterialMapTable);
    ACAPI_Body_Dispose(&bodyData);

    // TODO move undoable command to wrap all element creations instead of just a single one
    CHECK_ERROR(ACAPI_CallUndoableCommand("Create Morph",
        [&]() -> GSErrCode {
            return ACAPI_Element_Create(&element, &memo);
        }));

    ACAPI_DisposeElemMemoHdls(&memo);

    GS::UniString infoString = baseGroupName.c_str();
    CHECK_ERROR(ACAPI_CallUndoableCommand("Set InfoString",
        [&]() -> GSErrCode {
            return ACAPI_Element_ChangeElementInfoString(&element.header.guid, &infoString);
        }));

    return APIGuidToString(element.header.guid).ToCStr().Get();
}
