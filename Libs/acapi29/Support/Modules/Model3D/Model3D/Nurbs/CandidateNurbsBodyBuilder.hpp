#ifndef CANDIDATENURBSBODYBUILDER_HPP
#define CANDIDATENURBSBODYBUILDER_HPP

#include "CandidateNurbsBody.hpp"

namespace BrepOperations {
	class NurbsBrepWithLibData;
}

namespace Modeler {

class MODEL3D_DLL_EXPORT CandidateNurbsBodyBuilder {
private:


	NurbsVertexDataContainerT			 vertexData;
	NurbsEdgeDataContainerT				 edgeData;
	NurbsFaceDataContainerT				 faceData;

	const NurbsVertexData				defaultVertexData;
	const NurbsEdgeData					defaultEdgeData;
	const NurbsFaceData					defaultFaceData;

	const STATL							shadowStatus;

	const NurbsBodyLevelAttrs			bodyLevelAttrs;

	void EnsureVertexSize (UInt32 size);
	void EnsureEdgeSize (UInt32 size);
	void EnsureFaceSize (UInt32 size);


public:
	CandidateNurbsBodyBuilder (const NurbsVertexData& defaultVertexData,
							   const NurbsEdgeData&	 defaultEdgeData,
							   const NurbsFaceData&	 defaultFaceData
	);
	CandidateNurbsBodyBuilder (const NurbsBodyBase&	bodyLevelDataSource);
	
	NurbsVertexData&	GetVertexData (UInt32 index);
	NurbsEdgeData&		GetEdgeData (UInt32 index);
	NurbsFaceData&		GetFaceData (UInt32 index);

	GS::Owner<CandidateNurbsBody> CreateCandidateNurbsBody (BrepOperations::NurbsBrepWithLibData&& brepWithLibData);
	CandidateNurbsBodyPtr CreateCandidateNurbsBodyPtr (BrepOperations::NurbsBrepWithLibData&& brepWithLibData);
};

}

#endif // CANDIDATENURBSBODYBUILDER_HPP