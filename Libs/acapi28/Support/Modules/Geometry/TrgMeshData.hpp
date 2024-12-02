#if !defined (TRGMESHDATA_H)
#define TRGMESHDATA_H

#pragma once
#include "GeometricDefinitions.h"
#include "Vector3D.hpp"

// from GSRoot
#include "Array.hpp"
#include "HashTable.hpp"
#include "String.hpp"
#include "GSMalloc.hpp"

namespace Geometry {
	namespace TrgMesh {	//one based indexing, 0 means no element!

		typedef USize VrtIndex;
		typedef USize EdgeIndex;
		typedef USize TrgIndex;
		typedef USize ExternalVertIndex;

		class Vertex;
		class Edge;
		class Triangle;
		class Mesh;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		class GEOMETRY_DLL_EXPORT Vertex
		{
		public:
											Vertex ();
			virtual							~Vertex ();
			inline VrtIndex					GetIndex () const { return index; }
			inline ExternalVertIndex		GetExternalIndex () const { return externalIndex; }
			inline USize					GetNumConnTrgs () const { return connTrgIndexes.GetSize (); }
			inline TrgIndex					ConnTrgIndexes (USize i) const { return connTrgIndexes[i]; }
			inline USize					GetNumConnEdges () const { return connEdgeIndexes.GetSize (); }
			inline EdgeIndex				ConnEdgeIndexes (USize i) const { return connEdgeIndexes[i]; }
			const Vector3D &				GetCrds () const { return crds; }
			const Vector3D &				GetApproxNormal () const { return approxNormal; } //approximate surface normal. Here at the vertex the surface normal is not continuous!
		private:
			friend class Mesh;

			GS::Array<TrgIndex>				connTrgIndexes;
			GS::Array<EdgeIndex>			connEdgeIndexes;
			Vector3D						crds;
			Vector3D						shft;
			double							weight;
			VrtIndex						index;
			ExternalVertIndex				externalIndex;
			Vector3D						approxNormal;

			void							AddTrg (const TrgIndex t);
			void							AddEdge (const EdgeIndex e);
		};

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		class GEOMETRY_DLL_EXPORT Edge
		{
		public:
											Edge ();
			virtual							~Edge ();

			ULong							GenerateHashValue () const { ULong rt = vert1Index; rt += vert2Index; return rt; }
			VrtIndex						GetOtherVertexIndx (const VrtIndex index) const;
			bool							IsFlipped (const VrtIndex frst, const VrtIndex scnd) const;
			bool							IsNotFlipped (const VrtIndex frst, const VrtIndex scnd) const;
			bool							IsOnPerimeter () const;
			VrtIndex						GetVertexIndex (const USize indx) const;
		private:
			friend class Mesh;

			VrtIndex						vert1Index;			//init when issued!
			VrtIndex						vert2Index;			//init when issued!
			//sides:
			TrgIndex						trg1Index;
			TrgIndex						trg2Index;

			void							AddTrg (const TrgIndex t);
		};

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		class GEOMETRY_DLL_EXPORT Triangle
		{
		public:
											Triangle ();
			virtual							~Triangle ();

			VrtIndex						GetThirdVrtxIndex (VrtIndex i, VrtIndex j);
			bool							GetOtherTwoVertices(const VrtIndex v0, VrtIndex & v1, VrtIndex & v2); //return false if failed!
			VrtIndex						VertIndexes (USize i) const { DBASSERT(i < 3); return vertIndexes[i]; }
			const Vector3D &				GetNormal () const { return normal; }
			double							GetArea () const { return area; }
		private:
			friend class Mesh;

			VrtIndex						vertIndexes[3];		//init when issuued!
			EdgeIndex						edgeIndexes[3];		//init when issuued!   edge_i is across vertex_i, connecting the other two verices!
			Vector3D						normal;
			double						    area;
		};

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		class GEOMETRY_DLL_EXPORT Mesh
		{
		public:
											Mesh ();
			virtual							~Mesh ();

			void							SetVTKFileName (const char * vtkFileName_init) { vtkFileName = strdup (vtkFileName_init); }
			void							SaveVTK();

			void							Clear ();
			Edge &							GetEdge (ExternalVertIndex i, ExternalVertIndex j);
			const Edge &					GetEdge (ExternalVertIndex i, ExternalVertIndex j) const;
			VrtIndex						IssueVertex (ExternalVertIndex externalIndex_in);
			Triangle &						IssueTriangle (ExternalVertIndex v1, ExternalVertIndex v2, ExternalVertIndex v3, TrgIndex & ti);
			USize							GetEdgeNeighborTrgCount (ExternalVertIndex v1, ExternalVertIndex v2) const;


			void							SetVertexCrds (const USize iVert, const Vector3D & val);

			GS::Array< Vertex > &			GetVertices () { return vertices; }
			GS::Array< Edge >	&			GetEdges () { return edges; }
			GS::Array< Triangle > &			GetTriangles () { return triangles; }

			const GS::Array< Vertex > &		GetVertices () const { return vertices; }
			const GS::Array< Edge >	&		GetEdges () const { return edges; }
			const GS::Array< Triangle > &	GetTriangles () const { return triangles; }

			Vertex &						GetVertex (VrtIndex index) { return vertices[index]; }
			Edge &							GetEdge (EdgeIndex index) { return edges[index]; }
			Triangle &						GetTriangle (TrgIndex index) { return triangles[index]; }

			const Vertex &					GetVertex (VrtIndex index) const { return vertices[index]; }
			const Edge &					GetEdge (EdgeIndex index) const { return edges[index]; }
			const Triangle &				GetTriangle (TrgIndex index) const { return triangles[index]; }

			VrtIndex						GetMshVrtIndex (ExternalVertIndex index) const;
			bool							GetOtherTwoVerticesIn(const USize connectingTrg, const VrtIndex v0, VrtIndex & v1, VrtIndex & v2) const; //return false if trg > sizeof connTrgIndexes

			void							GetPerimeterLoop (GS::Array<ExternalVertIndex> & loop) const;
			double							CalcEdgeLength (const Edge & e) const;
			inline Vector3D					CalcNormalArea (TrgIndex tIndex) const { return CalcNormalArea (GetTriangle (tIndex)); }
			Vector3D						CalcNormalArea (const Triangle & t) const;
			void							UpdateNormals ();
			void							UpdateNormals (const GS::Array< TrgMesh::TrgIndex > & trgsIndexes);
			void							LaplaceSmoothStep (const GS::Array< VrtIndex > & toSmooth, const double strength = 0.25, const double keepVolumeFactor = 0.0);
			void							exportToVTK (const char * fname);
			bool							CheckMesh () const;

			//in order to save with the mesh (VTK):
			void							ClearFields ();
			void							AddVectorField (const char *fieldName, const GS::Array<Vector3D> & samples);
			void							AddScalarField (const char *fieldName, const GS::Array<double> & samples);
		private:
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			class GEOMETRY_DLL_EXPORT MshVIndexKey
			{
			public:
				MshVIndexKey () : v1 (0), v2 (0), v3 (0) {}
				MshVIndexKey (VrtIndex i, VrtIndex j, VrtIndex k = 0);
				ULong GenerateHashValue () const;
				bool operator == (const MshVIndexKey & rhs) const { return v1 == rhs.v1 && v2 == rhs.v2 && v3 == rhs.v3; }

				bool operator < (const MshVIndexKey & rhs) const;
			private:
				VrtIndex v1, v2, v3;
			};

			EdgeIndex							IssueEdge (VrtIndex i, VrtIndex j);
			const Edge &						GetEdge (const Vertex & v1, const Vertex & v2) const;

			GS::HashTable< MshVIndexKey, EdgeIndex >
												edgeMap;
			GS::HashTable< MshVIndexKey, TrgIndex >
												trgMap;
			GS::HashTable< ExternalVertIndex, VrtIndex >
												externalVertexIndxToVertexIndex;
			GS::Array<Vertex>					vertices;
			GS::Array<Edge>						edges;
			GS::Array<Triangle>					triangles;
			const char *						vtkFileName;

			//quantities which will be saved along with the mesh:
			GS::HashTable<GS::String, GS::Array<Vector3D> >
												vectorsOverMesh;
			GS::HashTable<GS::String, GS::Array<double> >
												scalarsOverMesh;

		};

	}  //end namespace TrgMesh
}

#endif
