// ****************************************************************************
// File:			LowLevelFactory.hpp
//
// Description:		Main interface for G3x GPU factoring interface
//
// Contact person:	DG
//
// SG compatible
// ****************************************************************************

#ifndef	LOWLEVELFACTORYG3x_HPP
#define	LOWLEVELFACTORYG3x_HPP

// --- Includes ---------------------------------------------------------------

#include "LowLevelFactory.hpp"
#include "LowLevelObjectsG3x.hpp"


namespace	Graphix	{

// --- G3x factory class  -----------------------------------------------------

class	GRAPHIX_DLL_EXPORT	ResourceFactoryG3x:	public ResourceFactory
{
public:
	virtual	~ResourceFactoryG3x ();

	virtual		BlendState*			CreateBlendState (UInt64 contextId, const BlendG3x& state) = 0;
	virtual		RasterizerState*	CreateRasterizerState (UInt64 contextId, const RasterizerG3x& state) = 0;
	virtual		GeometryShader*		CreateGeometryShader (UInt64 contextId, const void* data, UInt32 length) = 0;
	virtual		Program*			CreateProgram (UInt64 contextId, InputLayout* pInputLayout, GeometryShader* geometryShader, PixelShader* pPixelShader) = 0;
	virtual		UniformBuffer*		CreateUniformBuffer (UInt64 contextId, const void* buffer, UInt32 length) = 0;
};


} // namespace Graphix

#endif	// LOWLEVELFACTORYG3x_HPP