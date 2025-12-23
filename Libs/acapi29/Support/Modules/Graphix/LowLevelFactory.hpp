// ******************************************************************************
// File:			LowLevelFactory.hpp
//
// Description:		Main interface for common low level GPU factoring interface
//
// Contact person:	DG
//
// SG compatible
// ******************************************************************************

#ifndef	LOWLEVELFACTORY_HPP
#define	LOWLEVELFACTORY_HPP

// --- Includes -----------------------------------------------------------------

#include "LowLevelObjects.hpp"

// --- Predeclarations ----------------------------------------------------------

namespace	Graphix	{
	
class	ResourceFactory;

}


namespace	Graphix	{

// --- Feature models (GPU generations) -----------------------------------------

enum FeatureModel	{
	G0x		=	0,						// Not supported (fixed function with 1 texture stage, no vertex and indexbuffers)
	G1x,								// Not supported (fixed function)			(OGL 1.x, DX7)
	G2x,								// Not supported: shader based rendering	(OGL 2.x, DX9)
	G3x									// Advanced shader based rendering			(OGL 3.x, DX FL 10.x/11)
};


// --- Resource factory observer ------------------------------------------------

class	GRAPHIX_DLL_EXPORT	ResourceFactoryObserver
{
public:
	virtual	~ResourceFactoryObserver ();

	virtual		void				APIContextIsAboutToBeDeleted (const ResourceFactory* pFactory, UInt64 contextId) = 0;
};


// --- Base Resource factory clas  ----------------------------------------------

class	GRAPHIX_DLL_EXPORT	ResourceFactory
{
public:
	enum	Type
	{
		D3D11		=	0
	};

public:
	virtual	~ResourceFactory ();

	static		UInt32				GetNumberOfResourceFactories ();
	static		ResourceFactory*	EnumResourceFactory (UInt32 idx);

	virtual		void				AddObserver (ResourceFactoryObserver* pObserver) = 0;
	virtual		void				RemoveObserver (ResourceFactoryObserver* pObserver) = 0;

	virtual		Type				GetType () = 0;
	virtual		FeatureModel		GetFeatureModel () = 0;

	// --- Arbitrary Model ----------------------------------------------------

	virtual		UInt32				GetMaxVertexBufferSize () = 0;

	virtual		DepthStencilState*	CreateDepthStencilState (UInt64 contextId, const DepthStencil& state) = 0;
	virtual		BlendState*			CreateBlendState (UInt64 contextId, const Blend& state) = 0;
	virtual		RasterizerState*	CreateRasterizerState (UInt64 contextId, const Rasterizer& state) = 0;
	virtual		InputLayout*		CreateInputLayout (UInt64 contextId, const void* vertexShaderData, UInt32 length, const InputElement* vertexElements, UInt32 numOfElements, UInt32 sizeOfVertex) = 0;
	virtual		PixelShader*		CreatePixelShader (UInt64 contextId, const void* data, UInt32 length) = 0;
	virtual		Program*			CreateProgram (UInt64 contextId, InputLayout* pInputLayout, PixelShader* pPixelShader) = 0;
	virtual		VertexBuffer*		CreateVertexBuffer (UInt64 contextId, UInt32 sizeOfVertex, UInt32 numberOfVertices, bool dynamicUsage) = 0;
	virtual		IndexBuffer*		CreateIndexBuffer (UInt64 contextId, UInt32 numberOfIndices, bool _16bitIndices, bool dynamicUsage) = 0;
};


} // namespace Graphix

#endif	// LOWLEVELFACTORY_HPP