#include "ArchicadMesh.h"
#include <unordered_set>
#include <cmath>

static void RemoveDuplicates(std::vector<int>& vec) 
{
	std::unordered_set<int> seen;
	std::vector<int> uniqueVec;

	for (int num : vec) 
	{
		if (seen.insert(num).second) 
		{
			uniqueVec.push_back(num);
		}
	}

	vec = std::move(uniqueVec);
}

size_t ArchicadMesh::ArchicadVertexHash(const ArchicadVertex& vertex) const 
{
    std::hash<double> hasher;
    return hasher(vertex.x) ^ (hasher(vertex.y) << 1) ^ (hasher(vertex.z) << 2);
}

ArchicadMesh::ArchicadMesh(const Mesh& mesh)
{
    CreateMesh(mesh);
}

void ArchicadMesh::CreateMesh(const Mesh& mesh)
{
    int vertexIndex = 1;

	for (size_t i = 0; i < mesh.faces.size(); )
	{
		int polySize = mesh.faces[i++];
		std::vector<int> faceVertices;

		for (int j = 0; j < polySize; ++j)
		{
			int originalIndex = mesh.faces[i++];
			ArchicadVertex vertex = { mesh.vertices[originalIndex * 3], mesh.vertices[originalIndex * 3 + 1], mesh.vertices[originalIndex * 3 + 2] };
			size_t hash = ArchicadVertexHash(vertex);

			if (vertexMap.find(hash) == vertexMap.end())
			{
				vertices.push_back(vertex);
				faceVertices.push_back(vertexIndex);
				vertexMap[hash] = vertexIndex++;
			}
			else
			{
				faceVertices.push_back(vertexMap[hash]);
			}
		}

		// there are duplicate vertices in some polygons
		// which is weird but the below function call is needed
		RemoveDuplicates(faceVertices);
		polySize = static_cast<int>(faceVertices.size());

		if (polySize > 2)
		{
			std::vector<int> polyEdges;
			for (int j = 0; j < polySize; ++j)
			{
				ArchicadEdge acEdge;
				acEdge.start = faceVertices[j];
				acEdge.end = faceVertices[(j + 1) % faceVertices.size()];

				bool newEdge = true;
				int foundEdgeIndex = 1;
				for (const auto& e : edges)
				{
					if (acEdge.Equals(e))
					{
						polyEdges.push_back(foundEdgeIndex);
						newEdge = false;
						break;
					}

					if (acEdge.Opposite(e))
					{
						polyEdges.push_back(-foundEdgeIndex);
						newEdge = false;
						break;
					}

					foundEdgeIndex++;
				}
				if (newEdge)
				{
					edges.push_back(acEdge);
					foundEdgeIndex = static_cast<int>(edges.size());
					polyEdges.push_back(foundEdgeIndex);
				}
			}
			polys.push_back({ polySize, polyEdges, mesh.materialName });
			// TODO add poly index to edges
			// if poly1 == -1 else if poly2 == -1...
		}
	}
}
