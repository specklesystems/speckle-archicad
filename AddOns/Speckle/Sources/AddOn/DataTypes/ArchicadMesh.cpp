#include "ArchicadMesh.h"
#include <unordered_set>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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
	CalculatePolyNormals();
	ComputeEdgeVisibility();
}

// TODO move these functions into Vertex/Vector3 class or use built in classes
static double DotProduct(const ArchicadVertex& a, const ArchicadVertex& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

static ArchicadVertex CrossProduct(const ArchicadVertex& a, const ArchicadVertex& b)
{
	return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
}

static ArchicadVertex Subtract(const ArchicadVertex& a, const ArchicadVertex& b)
{
	return { a.x - b.x, a.y - b.y, a.z - b.z };
}

static bool IsCoplanar(const std::vector<ArchicadVertex>& polyVertices)
{
	if (polyVertices.size() < 4) return true; // Any three points are always coplanar

	const ArchicadVertex& v0 = polyVertices[0];
	const ArchicadVertex& v1 = polyVertices[1];
	const ArchicadVertex& v2 = polyVertices[2];

	ArchicadVertex normal = CrossProduct(Subtract(v1, v0), Subtract(v2, v0));
	double normLength = std::sqrt(DotProduct(normal, normal));
	if (normLength == 0) return true;

	normal = { normal.x / normLength, normal.y / normLength, normal.z / normLength };

	for (size_t i = 3; i < polyVertices.size(); ++i)
	{
		ArchicadVertex viVec = Subtract(polyVertices[i], v0);
		double dot = DotProduct(viVec, normal);
		// TODO review threshold
		if (std::abs(dot) > 1e-6) return false; // Not coplanar
	}
	return true;
}

void ArchicadMesh::CreateMesh(const Mesh& mesh)
{
    int vertexIndex = 1;
	int polyIndex = 0;

	for (size_t i = 0; i < mesh.faces.size(); )
	{
		int polySize = mesh.faces[i++];
		std::vector<int> faceVertices;

		if (polySize < 3)
		{
			polySize += 3;
		}

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

		// there are duplicate vertices in some polygons which is weird
		// the below function call is needed to remove duplications
		RemoveDuplicates(faceVertices);
		polySize = static_cast<int>(faceVertices.size());

		if (polySize > 2)
		{
			std::vector<ArchicadVertex> actualPoly;
			for (const auto& vi : faceVertices)
			{
				actualPoly.push_back(vertices[vi - 1]);
			}

			// TODO remove code duplications from if-else
			if (IsCoplanar(actualPoly))
			{
				++polyIndex;
				std::vector<int> polyEdges;
				for (int j = 0; j < polySize; ++j)
				{
					ArchicadEdge acEdge{ faceVertices[j], faceVertices[(j + 1) % polySize] };
					int foundEdgeIndex = 1;
					bool newEdge = true;

					// checking if edge already exists
					for (auto& existingEdge : edges)
					{
						if (acEdge.Equals(existingEdge) || acEdge.Opposite(existingEdge))
						{
							if (existingEdge.poly2 == -1)
							{
								existingEdge.poly2 = polyIndex;
								polyEdges.push_back(acEdge.Equals(existingEdge) ? foundEdgeIndex : -foundEdgeIndex);
								newEdge = false;
							}
							break;
						}
						++foundEdgeIndex;
					}

					if (newEdge)
					{
						acEdge.poly1 = polyIndex;
						edges.push_back(acEdge);
						polyEdges.push_back(static_cast<int>(edges.size()));
					}
				}
				polys.push_back({ polySize, polyEdges, mesh.materialName });
			}
			else
			{
				for (size_t j = 1; j < faceVertices.size() - 1; ++j)
				{
					++polyIndex;
					std::vector<int> triEdges;
					ArchicadEdge e1 = { faceVertices[0], faceVertices[j] };
					ArchicadEdge e2 = { faceVertices[j], faceVertices[j + 1] };
					ArchicadEdge e3 = { faceVertices[j + 1], faceVertices[0] };

					std::vector<ArchicadEdge> triEdgesList = { e1, e2, e3 };
					for (auto& triEdge : triEdgesList)
					{
						bool newEdge = true;
						int foundEdgeIndex = 1;

						for (auto& existingEdge : edges)
						{
							if (triEdge.Equals(existingEdge) || triEdge.Opposite(existingEdge))
							{
								if (existingEdge.poly2 == -1)
								{
									existingEdge.poly2 = polyIndex;
									triEdges.push_back(triEdge.Equals(existingEdge) ? foundEdgeIndex : -foundEdgeIndex);
									newEdge = false;
								}							
								break;
							}
							++foundEdgeIndex;
						}
						if (newEdge)
						{
							triEdge.poly1 = polyIndex;
							edges.push_back(triEdge);
							triEdges.push_back(static_cast<int>(edges.size()));
						}
					}
					polys.push_back({ 3, triEdges, mesh.materialName });
				}
			}	
		}
	}
}

static ArchicadVertex ComputeNormal(const ArchicadVertex& v1, const ArchicadVertex& v2, const ArchicadVertex& v3) 
{
	ArchicadVertex normal;

	double ux = v2.x - v1.x;
	double uy = v2.y - v1.y;
	double uz = v2.z - v1.z;

	double vx = v3.x - v1.x;
	double vy = v3.y - v1.y;
	double vz = v3.z - v1.z;

	normal.x = uy * vz - uz * vy;
	normal.y = uz * vx - ux * vz;
	normal.z = ux * vy - uy * vx;

	// Normalize the normal vector
	double length = std::sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
	if (length > 0.0) 
	{
		normal.x /= length;
		normal.y /= length;
		normal.z /= length;
	}

	return normal;
}

void ArchicadMesh::CalculatePolyNormals() 
{
	for (auto& poly : polys) 
	{
		if (poly.edges.size() < 3) 
		{
			poly.normal = { 0.0, 0.0, 0.0 };
			continue;
		}

		int ei1 = poly.edges[0];
		int ei2 = poly.edges[1];
		int ei3 = poly.edges[2];

		int vi1 = (ei1 >= 0) ? edges[ei1-1].start - 1 : edges[-ei1-1].end - 1;
		int vi2 = (ei2 >= 0) ? edges[ei2-1].start - 1 : edges[-ei2-1].end - 1;
		int vi3 = (ei3 >= 0) ? edges[ei3-1].start - 1 : edges[-ei3-1].end - 1;

		const ArchicadVertex& v1 = vertices[vi1];
		const ArchicadVertex& v2 = vertices[vi2];
		const ArchicadVertex& v3 = vertices[vi3];

		poly.normal = ComputeNormal(v1, v2, v3);
	}
}

static double ComputeAngleBetweenNormals(const ArchicadVertex& n1, const ArchicadVertex& n2) 
{
	double dotProduct = n1.x * n2.x + n1.y * n2.y + n1.z * n2.z;
	double length1 = std::sqrt(n1.x * n1.x + n1.y * n1.y + n1.z * n1.z);
	double length2 = std::sqrt(n2.x * n2.x + n2.y * n2.y + n2.z * n2.z);

	if (length1 == 0.0 || length2 == 0.0) 
	{
		return 0.0;
	}

	double cosine = dotProduct / (length1 * length2);
	return std::acos(std::max(-1.0, std::min(1.0, cosine))); // Clamp to avoid precision issues
}

void ArchicadMesh::ComputeEdgeVisibility() 
{
	const double visibleThresholdAngle = M_PI / 3;
	const double hiddenThresholdAngle = 0.0001;

	// smoothBodyEdge/hiddenBodyEdge/visibleBodyEdge
	for (auto& edge : edges) 
	{
		// Boundary edges are always visible
		if (edge.poly1 == -1 || edge.poly2 == -1) 
		{
			edge.visibilityType = "visibleBodyEdge";
			continue;
		}

		const ArchicadVertex& normal1 = polys[edge.poly1 - 1].normal;
		const ArchicadVertex& normal2 = polys[edge.poly2 - 1].normal;
		double angle = ComputeAngleBetweenNormals(normal1, normal2);

		// TODO move strings to enum
		edge.visibilityType = "smoothBodyEdge";
		if (angle > visibleThresholdAngle)
		{
			edge.visibilityType = "visibleBodyEdge";
		}
		else if (angle < hiddenThresholdAngle)
		{
			edge.visibilityType = "hiddenBodyEdge";
		}
	}
}
